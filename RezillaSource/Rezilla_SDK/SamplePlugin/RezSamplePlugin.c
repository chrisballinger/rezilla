// ===========================================================================
// File: "RezSamplePlugin..c"
// 
//                        Created: 2005-09-08 18:51:53
//              Last modification: 2005-09-09 07:08:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#import <CoreFoundation/CoreFoundation.h>
#import <Carbon/Carbon.h>

#include "RezillaPluginInterface.h"

#include <stdio.h>
#include <stdlib.h>

// Constants
enum {
	kBallWidth			= 20,
	kBallHeight			= 20,
	kBobSize			= 11	// Width of text in each ball
};

// The UUID for the factory function: 
// "306B89A8-206E-11DA-8320-000A95B1FF7C"
// It is used as a key of the CFPlugInFactories dictionary in the property
// list file (Info.plist).
#define kRezillaSampleFactoryID (CFUUIDGetConstantUUIDWithBytes(NULL,0x30,0x6B,0x89,0xA8,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


// The layout for an instance of SampleType
typedef struct _SampleType {
	SRezillaPluginInterface *	_rezillaPlugInterface;
	CFUUIDRef					_factoryID;
	UInt32						_refCount;
} SampleType;

// Forward declaration for the IUnknown implementation.
static void _deallocSampleType( SampleType *myInstance );



// -------------------------------------------------------------------------------------------
//
//  Implementation of the IUnknown QueryInterface function
//
// -------------------------------------------------------------------------------------------

static HRESULT sample_QueryInterface( void *myInstance, REFIID iid, LPVOID *ppv )
{
	// Create an UUIDRef for the requested interface
	CFUUIDRef interfaceID = CFUUIDCreateFromUUIDBytes( NULL, iid );

	// Test the requested ID against the valid interfaces

	if ( CFEqual( interfaceID, kRezillaEditorInterfaceID ) ) {
		// If the RezillaPluginInterface was requested, bump the ref count,
		// set the ppv parameter equal to the instance, and return good status
		( (SampleType *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
		*ppv = myInstance;
		CFRelease( interfaceID );
		return S_OK;
	} else if ( CFEqual( interfaceID, IUnknownUUID ) ) {
		// If the IUnknown interface was requested, same as above
		( (SampleType *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
		*ppv = myInstance;
		CFRelease( interfaceID );
		return S_OK;
	} else {
		// Requested interface unknown, bail with error
		*ppv = NULL;
		CFRelease( interfaceID );
		return E_NOINTERFACE;
	}
}


// -------------------------------------------------------------------------------------------
//
//  Implementation of reference counting for this type.
//  Whenever an interface is requested, bump the refCount for the instance.
//  NOTE: returning the refcount is a convention but is not required so don't rely on it.
//
// -------------------------------------------------------------------------------------------

static ULONG sample_AddRef( void *myInstance )
{
	( (SampleType *) myInstance )->_refCount += 1;
	return ( (SampleType *) myInstance )->_refCount;
}


// -------------------------------------------------------------------------------------------
//
//  When an interface is released, decrement the refCount.
//  If the refCount goes to zero, deallocate the instance.
//
// -------------------------------------------------------------------------------------------

static ULONG sample_Release( void *myInstance )
{
	( (SampleType *) myInstance )->_refCount -= 1;
	if ( ( (SampleType *) myInstance )->_refCount == 0 ) {
		_deallocSampleType( (SampleType *) myInstance );
		return 0;
	} else {
		return ( (SampleType *) myInstance )->_refCount;
	}
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the editResource function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

static void sample_editResource( void *myInstance, ResType inType, short inID )
{
	Str255      message = "\pHello! this is the Sample plugin for Rezilla. It can edit 'PStr' and 'STR ' types :-)";
	SInt16      alertItemHit = 0;
	Str255		typeStr;

	char theType[5];
	theType[4] = 0;
	*(OSType*)theType = inType;
	CopyCStringToPascal(theType, typeStr);	
	
	StandardAlert(kAlertStopAlert, typeStr, message, NULL, &alertItemHit);
}


/************************************************
*                                               *
*   The RezillaEditorInterface function table   *
*                                               *
************************************************/
static SRezillaPluginInterface rezillaPlugInterfaceFtbl = {
		NULL,                    // Required padding for COM
		sample_QueryInterface,   // These three are the required COM functions
		sample_AddRef,
		sample_Release,
		sample_editResource };   // Interface implementation of the editResource function



// -------------------------------------------------------------------------------------------
//
//  Utility function that allocates a new instance
//
// -------------------------------------------------------------------------------------------

static SampleType *_allocSampleType( CFUUIDRef factoryID )
{
	// Allocate memory for the new instance
	SampleType *newOne = (SampleType *) malloc( sizeof(SampleType) );

	// Point to the function table
	newOne->_rezillaPlugInterface = &rezillaPlugInterfaceFtbl;

	// Retain and keep an open instance refcount for each factory
	if (factoryID) {
		newOne->_factoryID = (CFUUIDRef) CFRetain( factoryID );
		CFPlugInAddInstanceForFactory( factoryID );
	}

	// This function returns the IUnknown interface so set the refCount to one
	newOne->_refCount = 1;
	return newOne;
}


// -------------------------------------------------------------------------------------------
//
//  Utility function that deallocates the instance when the refCount goes to zero
//
// -------------------------------------------------------------------------------------------

static void _deallocSampleType( SampleType *myInstance )
{
	CFUUIDRef factoryID = myInstance->_factoryID;
	free( myInstance );
	if ( factoryID ) {
		CFPlugInRemoveInstanceForFactory( factoryID );
		CFRelease( factoryID );
	}
}


// -------------------------------------------------------------------------------------------
//
//  Implementation of the factory function for this type.
//  From the doc 
//  (/documentation/CoreFoundation/Conceptual/CFPlugIns/Concepts/conceptual.html):
//      "When called by the plug-in host, the factory function allocates
//      memory for an instance of the type being requested, sets up the
//      function tables for its interfaces, and returns a pointer to the
//      type’s IUnknown interface. The plug-in host can then use the
//      IUnknown interface to search for other interfaces supported by the
//      type."
//      
//  The return value is a void* but is in fact a pointer to a SampleType 
//  structure.
//
// -------------------------------------------------------------------------------------------
/* extern "C"  */
extern void * RezSampleFactory(CFAllocatorRef allocator, CFUUIDRef typeID);

void * RezSampleFactory( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	// If correct type is being requested, allocate an instance of
	// SampleType and return the IUnknown interface
	if ( CFEqual( typeID, kRezillaEditorTypeID ) ) {
		SampleType *result = _allocSampleType( kRezillaSampleFactoryID );
		return result;
	}
	else 
	{
		// If the requested type is incorrect, return NULL
		return NULL;
	}
}