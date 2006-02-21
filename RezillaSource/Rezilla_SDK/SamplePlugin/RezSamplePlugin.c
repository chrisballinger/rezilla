// ===========================================================================
// File: "RezSamplePlugin.c"
// 
//                        Created: 2005-09-08 18:51:53
//              Last modification: 2006-02-20 13:48:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================


#import <CoreFoundation/CoreFoundation.h>
#import <Carbon/Carbon.h>

#include "RezillaPluginInterface.h"
#include "RezSamplePluginID.h"

// The UUID for the factory function: 
// "306B89A8-206E-11DA-8320-000A95B1FF7C"
// It is used as a key of the CFPlugInFactories dictionary in the property
// list file (Info.plist).
#define kRezillaSampleFactoryID (CFUUIDGetConstantUUIDWithBytes(NULL,0x30,0x6B,0x89,0xA8,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))

#define kSamplePluginMenuID 500


// Layout for an instance of SampleRec
typedef struct _SampleRec {
	SRezillaPluginInterface *	_rezillaPlugInterface;
	CFUUIDRef					_factoryID;
	UInt32						_refCount;
} SampleRec;


// Prototypes
// ----------
static SampleRec *	_allocSampleRec( CFUUIDRef factoryID );
static void			_deallocSampleRec( SampleRec *myInstance );
static HRESULT		sample_QueryInterface( void *myInstance, REFIID iid, LPVOID *ppv );
static ULONG		sample_AddRef( void *myInstance );
static ULONG		sample_Release( void *myInstance );
static Boolean		sample_AcceptResource( void *myInstance, ResType inType, short inID, Handle inDataH, RezPluginRequirements * ioReq);
static void			sample_EditResource( void *myInstance, RezPluginInfo inInfo);
static Handle		sample_ReturnResource( void *myInstance, Boolean * releaseIt, OSErr * outError);
static void			sample_HandleMenu(MenuRef menu, SInt16 inMenuItem);
static void			sample_HandleClick(const EventRecord * inMacEvent, Point inPortCoords);
static void			sample_HandleKeyDown(const EventRecord * inKeyEvent);


// The RezillaEditorInterface function table
// -----------------------------------------
static SRezillaPluginInterface sSamplePlugFuncTable = {
		NULL,                    // Required padding for COM
		sample_QueryInterface,   // These three are the required COM functions
		sample_AddRef,
		sample_Release,
		sample_AcceptResource,
		sample_EditResource,
		sample_ReturnResource,
		sample_HandleMenu,
		sample_HandleClick,
		sample_HandleKeyDown
};

// Static variables
static ResType sampleType;
static short sampleID;
static Handle sampleHandle;
static MenuID sampleMenuID;



// -------------------------------------------------------------------------------------------
//
//  Implementation of the IUnknown QueryInterface function
//
// -------------------------------------------------------------------------------------------

HRESULT
sample_QueryInterface( void *myInstance, REFIID iid, LPVOID *ppv )
{
	HRESULT	res;
	
	// Create an UUIDRef for the requested interface
	CFUUIDRef interfaceID = CFUUIDCreateFromUUIDBytes( NULL, iid );

	// Test the requested ID against the valid interfaces
	if ( CFEqual( interfaceID, kRezillaEditorInterfaceID ) ) {
		// If the RezillaPluginInterface was requested, bump the ref count,
		// set the ppv parameter equal to the instance, and return good status
		( (SampleRec *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
		*ppv = myInstance;
		res = S_OK;
	} else if ( CFEqual( interfaceID, IUnknownUUID ) ) {
		// If the IUnknown interface was requested, same as above
		( (SampleRec *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
		*ppv = myInstance;
		res = S_OK;
	} else {
		// Requested interface unknown, bail with error
		*ppv = NULL;
		res = E_NOINTERFACE;
	}
	
	CFRelease( interfaceID );
	
	return res;
}


// -------------------------------------------------------------------------------------------
//
//  Implementation of reference counting for this type.
//  Whenever an interface is requested, bump the refCount for the instance.
//  NOTE: returning the refcount is a convention but is not required so don't rely on it.
//
// -------------------------------------------------------------------------------------------

ULONG
sample_AddRef( void *myInstance )
{
	( (SampleRec *) myInstance )->_refCount += 1;
	return ( (SampleRec *) myInstance )->_refCount;
}


// -------------------------------------------------------------------------------------------
//
//  When an interface is released, decrement the refCount.
//  If the refCount goes to zero, deallocate the instance.
//
// -------------------------------------------------------------------------------------------

ULONG
sample_Release( void *myInstance )
{
	( (SampleRec *) myInstance )->_refCount -= 1;
	if ( ( (SampleRec *) myInstance )->_refCount == 0 ) {
		_deallocSampleRec( (SampleRec *) myInstance );
		return 0;
	} else {
		return ( (SampleRec *) myInstance )->_refCount;
	}
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the AcceptResource function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

Boolean
sample_AcceptResource( void *myInstance, ResType inType, short inID, Handle inDataH, RezPluginRequirements * ioReq)
{
	Boolean accepted = true;
	sampleMenuID = kSamplePluginMenuID;
	
	if (inType != 'PStr' && inType != 'STR ') {
		ioReq->error = plugErr_UnsupportedType;
		return false;
	} 
	
	ioReq->winattrs = kPlugWinHasSaveButton | kPlugWinHasCancelButton | kPlugWinHasLockIcon;
	ioReq->winbounds.top = 50;
	ioReq->winbounds.left = 50;
	ioReq->winbounds.bottom = 500;
	ioReq->winbounds.right = 300;
	ioReq->menucount = 1;
	ioReq->menuIDs = &sampleMenuID;
	
	sampleType = inType;
	sampleID = inID;
	sampleHandle =inDataH ;

	return accepted;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the EditResource function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_EditResource( void *myInstance, RezPluginInfo inInfo)
{
	Str255      message = "\pHello! this is the Sample plugin for Rezilla. It can edit 'PStr' and 'STR ' types :-)";
	SInt16      alertItemHit = 0;
	Str255		typeStr;

	char theType[5];
	theType[4] = 0;
	*(OSType*)theType = sampleType;
	CopyCStringToPascal(theType, typeStr);	
	
	StandardAlert(kAlertNoteAlert, typeStr, message, NULL, &alertItemHit);
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the ReturnResource function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

Handle
sample_ReturnResource( void *myInstance, Boolean * releaseIt, OSErr * outError)
{
	Handle	theHandle = NULL;
	
	return theHandle;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleMenu function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleMenu(MenuRef menu, SInt16 inMenuItem)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleClick function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleClick(const EventRecord * inMacEvent, Point inPortCoords)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleKeyDown function
//  declared in the interface (via the SRezillaPluginInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleKeyDown(const EventRecord * inKeyEvent){
}


// -------------------------------------------------------------------------------------------
//
//  Utility function that allocates a new instance
//
// -------------------------------------------------------------------------------------------

static SampleRec *
_allocSampleRec( CFUUIDRef factoryID )
{
	// Allocate memory for the new instance
	SampleRec * newType = (SampleRec *) malloc( sizeof(SampleRec) );

	// Point to the function table
	newType->_rezillaPlugInterface = &sSamplePlugFuncTable;

	// Retain and keep an open instance refcount for each factory
	if (factoryID) {
		newType->_factoryID = (CFUUIDRef) CFRetain( factoryID );
		CFPlugInAddInstanceForFactory( factoryID );
	}

	// This function returns the IUnknown interface so set the refCount to one
	newType->_refCount = 1;
	return newType;
}


// -------------------------------------------------------------------------------------------
//
//  Utility function that deallocates the instance when the refCount goes to zero
//
// -------------------------------------------------------------------------------------------

static void 
_deallocSampleRec( SampleRec *myInstance )
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
//  Implementation of the factory function for the kRezillaEditorTypeID type.
//  From the doc 
//  (/documentation/CoreFoundation/Conceptual/CFPlugIns/Concepts/conceptual.html):
//      "When called by the plug-in host, the factory function allocates
//      memory for an instance of the type being requested, sets up the
//      function tables for its interfaces, and returns a pointer to the
//      type’s IUnknown interface. The plug-in host can then use the
//      IUnknown interface to search for other interfaces supported by the
//      type."
//      
//  The return value is a void* but is in fact a pointer to a SampleRec structure.
//
// -------------------------------------------------------------------------------------------
/* extern "C"  */
extern void * RezSampleFactory(CFAllocatorRef allocator, CFUUIDRef typeID);

void * RezSampleFactory( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	if ( CFEqual( typeID, kRezillaEditorTypeID ) ) {
		// If correct type is being requested, allocate an instance of
		// the SampleRec struct and return the IUnknown interface
		SampleRec * result = _allocSampleRec( kRezillaSampleFactoryID );
		return result;
	} else {
		// If the requested type is incorrect, return NULL
		return NULL;
	}
}
