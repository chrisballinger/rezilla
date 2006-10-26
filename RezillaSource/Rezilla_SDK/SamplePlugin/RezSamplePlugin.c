// ===========================================================================
// File: "RezSamplePlugin.c"
// 
//                        Created: 2005-09-08 18:51:53
//              Last modification: 2006-10-12 06:22:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================


#import <CoreFoundation/CoreFoundation.h>
#import <Carbon/Carbon.h>

#include "RezillaPluginInterface.h"


// The UUID for the factory function: 
// "306B89A8-206E-11DA-8320-000A95B1FF7C"
// It is used as a key of the CFPlugInFactories dictionary in the property list file (Info.plist).
#define kRezillaSampleFactoryID (CFUUIDGetConstantUUIDWithBytes(NULL,0x30,0x6B,0x89,0xA8,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))

// ID of the plugin menu
#define kSamplePluginMenuID		500

// Default dimensions of the plugin window
#define kSampleBoundsTop		50;
#define kSampleBoundsLeft		50;
#define kSampleBoundsBottom		300;
#define kSampleBoundsRight		500;


// Layout for an instance of SampleRec
typedef struct _SampleRec {
	SPluginEditorInterface *	_rezillaPlugInterface;
	CFUUIDRef					_factoryID;
	UInt32						_refCount;
} SampleRec;


// Prototypes
// ----------
static SampleRec *	_allocSampleRec( CFUUIDRef factoryID );
static void			_deallocSampleRec( SampleRec *myInstance );
static HRESULT		sample_QueryInterface(void *myInstance, REFIID iid, LPVOID *ppv);
static ULONG		sample_AddRef(void *myInstance);
static ULONG		sample_Release(void *myInstance);
static Boolean		sample_AcceptResource(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo);
static OSErr		sample_EditResource(RezPlugRef inPlugref, RezHostInfo inInfo);
static Handle		sample_ReturnResource(RezPlugRef inPlugref, Boolean * outRelease, OSErr * outError);
static OSErr		sample_RevertResource(RezPlugRef inPlugref, Handle inDataH);
static Boolean		sample_IsModified(RezPlugRef inPlugref);
static void			sample_CleanUp(RezPlugRef inPlugref);
static void			sample_Refresh(RezPlugRef inPlugref);
static OSErr		sample_ResizeBy(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta);
static void			sample_HandleMenu(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem);
static void			sample_HandleClick(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords);
static void			sample_HandleKeyDown(RezPlugRef inPlugref, const EventRecord * inKeyEvent);
static Boolean		sample_HandleCommand(RezPlugRef inPlugref, SInt16 inCommand);

pascal OSStatus		_sampleTextInputHandler(EventHandlerCallRef inHandler, EventRef inEvent, void *userData);


// The RezillaEditorInterface function table
// -----------------------------------------
static SPluginEditorInterface sSamplePlugFuncTable = {
		NULL,                    // Required padding for COM
		sample_QueryInterface,   // These three are the required COM functions
		sample_AddRef,
		sample_Release,
		sample_AcceptResource,
		sample_EditResource,
		sample_ReturnResource,
		sample_RevertResource,
		sample_IsModified,
		sample_CleanUp,
		sample_Refresh,
		sample_ResizeBy,
		sample_HandleMenu,
		sample_HandleClick,
		sample_HandleKeyDown,
		sample_HandleCommand
};

// Statics
static MenuID		sampleMenuID;
static MenuRef		sampleMenuRef;

// A structure to hold the edit data for a particular resource
typedef struct SampleEditInfo {
	ResType		type;
	short		id;
	Handle		data;
	WindowRef	winref;
	ControlRef	controlref;
	Boolean		modified;
	Boolean		readonly;
} SampleEditInfo;


enum {
	kSampleMenu_ReverseText = 1,
	kSampleMenu_RotateText = 2
};



/*************************
*                        *
*   IUnknown Interface   *
*                        *
*************************/

// -------------------------------------------------------------------------------------------
//
//  Implementation of the IUnknown QueryInterface function
//
// -------------------------------------------------------------------------------------------

HRESULT
sample_QueryInterface(void *myInstance, REFIID iid, LPVOID *ppv )
{
	HRESULT	res;
	
	// Create an UUIDRef for the requested interface
	CFUUIDRef interfaceID = CFUUIDCreateFromUUIDBytes( NULL, iid );

	// Test the requested ID against the valid interfaces
	if ( CFEqual( interfaceID, kRezillaPluginEditorInterfaceVs1 ) ) {
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
sample_AddRef(void *myInstance )
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
sample_Release(void *myInstance )
{
	( (SampleRec *) myInstance )->_refCount -= 1;
	if ( ( (SampleRec *) myInstance )->_refCount == 0 ) {
		_deallocSampleRec( (SampleRec *) myInstance );
		return 0;
	} else {
		return ( (SampleRec *) myInstance )->_refCount;
	}
}



/************************
*                       *
*   Rezilla Interface   *
*                       *
************************/

// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the AcceptResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

Boolean
sample_AcceptResource(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo)
{
	Boolean accepted = true;
	
	sampleMenuID = kSamplePluginMenuID;
	
	if (inType != 'PStr' && inType != 'STR ') {
		outInfo->error = plugErr_UnsupportedType;
		accepted = false;
	} else {
		SampleEditInfo * editInfo = (SampleEditInfo *) malloc( sizeof(SampleEditInfo) );	
		
		if (editInfo == NULL) {
			outInfo->error = plugErr_InitializationFailed;
			accepted = false;
		} else {
			// Initialize the SampleEditInfo struct
			editInfo->type			= inType;
			editInfo->id			= inID;
			editInfo->data			= inDataH;
			editInfo->winref		= NULL;
			editInfo->controlref	= NULL;
			editInfo->modified		= false;
		
			// Fill the RezPlugInfo struct
			outInfo->plugref			= (RezPlugRef) editInfo;
			outInfo->attributes			= kPluginEditorStandardControls | kPluginSupportEditCommands;
			outInfo->winbounds.top		= kSampleBoundsTop;
			outInfo->winbounds.left		= kSampleBoundsLeft;
			outInfo->winbounds.bottom	= kSampleBoundsBottom;
			outInfo->winbounds.right	= kSampleBoundsRight;
			outInfo->menucount			= 1;
			outInfo->menuIDs			= &sampleMenuID;
		}
	}
	
	return accepted;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the EditResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

OSErr
sample_EditResource(RezPlugRef inPlugref, RezHostInfo inInfo)
{
	Rect			theRect;
	CFStringRef		theTextRef = NULL;
	ControlRef		staticRef;
	OSErr			error = noErr;
	
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	
	// Retreive info from the RezHostInfo struct
	editInfo->winref	= inInfo.winref;
	editInfo->readonly	= inInfo.readonly;
	sampleMenuRef		= *inInfo.menurefs;
	
	SetRect(&theRect, 80, 50, 300, 70);
	error = CreateStaticTextControl(editInfo->winref, &theRect, CFSTR("Pascal string:"),  NULL, &staticRef);
	
	SetRect(&theRect, 80, 80, 400, 170);
	if ( editInfo->data == NULL || GetHandleSize(editInfo->data) == 0) {
		theTextRef = CFSTR("");
	} else if ( GetHandleSize(editInfo->data) == (*(editInfo->data))[0] + 1) {
		theTextRef = CFStringCreateWithPascalString(kCFAllocatorDefault, *(editInfo->data), kCFStringEncodingMacRoman);
	}
	if (theTextRef) {
		error = CreateEditTextControl(editInfo->winref, &theRect, theTextRef, false, false, NULL, &(editInfo->controlref));
		CFRelease(theTextRef);
		
		if (error == noErr) {
			HIViewRef		theContentView;
			OSStatus		status;
			
			static const EventTypeSpec fieldEvents[] = {
				{kEventClassTextInput, kEventTextInputUnicodeForKeyEvent}
			};
			
			// Install a handler to be notified when text is typed in the field
			if (editInfo->controlref) {
				status = InstallEventHandler( GetControlEventTarget(editInfo->controlref),
											 NewEventHandlerUPP( _sampleTextInputHandler ), GetEventTypeCount(fieldEvents),
											 fieldEvents, inPlugref, NULL);
			} 
			
			HIViewSetVisible(editInfo->controlref, true);
			HIViewFindByID(HIViewGetRoot(editInfo->winref), kHIViewWindowContentID, &theContentView);
			HIViewAddSubview(theContentView, editInfo->controlref);
			EnableControl(editInfo->controlref);
		} 
	} else {
		error = plugErr_InvalidData;
	}
	
	return error;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the ReturnResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

Handle
sample_ReturnResource(RezPlugRef inPlugref, Boolean * releaseIt, OSErr * outError)
{
	Handle		theHandle = NULL;
	Size		theSize;
	Str255		theString;
	char		buffer[256];
	OSErr		error = noErr;
	
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	
	error = GetControlData(editInfo->controlref, kControlNoPart, kControlEditTextTextTag, sizeof(buffer), buffer, &theSize);
	
	if (error == noErr) {
		buffer[theSize] = 0;
		theHandle = NewHandle(theSize+1);
		CopyCStringToPascal(buffer, theString);
		BlockMoveData(theString, *theHandle, theSize+1);
		*releaseIt = true;
		// This function is called when saving the data, so we must reset the 
		// modified flag to false
		editInfo->modified = false;
	} 
	
	*outError = error;
	return theHandle;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the RevertResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

OSErr
sample_RevertResource(RezPlugRef inPlugref, Handle inDataH)
{
	OSErr	error = noErr;
	
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	
	error = SetControlData(editInfo->controlref, kControlNoPart, kControlEditTextTextTag, 
						   GetHandleSize(inDataH)-1, (*inDataH) +1);
	Draw1Control(editInfo->controlref);
	
	editInfo->data = inDataH;
	editInfo->modified = false;
	
	return error;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the IsModified function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

Boolean
sample_IsModified(RezPlugRef inPlugref)
{
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	return editInfo->modified;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the CleanUp function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_CleanUp(RezPlugRef inPlugref)
{
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	
	free(editInfo);
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the Refresh function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_Refresh(RezPlugRef inPlugref)
{
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	UpdateControls(editInfo->winref, NULL);
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the ResizeBy function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

OSErr
sample_ResizeBy(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta)
{
	// Our sample window is not resizable
	return plugErr_CantResizeWindow;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleMenu function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleMenu(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem)
{
	int			i;
	Size		len;
	char		oldStr[256];
	char		newStr[256];
	OSErr		error = noErr;
	
	SampleEditInfo * editInfo = (SampleEditInfo *) inPlugref;
	
	error = GetControlData(editInfo->controlref, kControlNoPart, kControlEditTextTextTag, sizeof(oldStr), oldStr, &len);
	
	oldStr[len] = 0;
	
	if (len > 0) {
		switch (inMenuItem) {
			case kSampleMenu_ReverseText:
			for (i = 0; i < len; i++) {
				newStr[i] = oldStr[len-i-1];
			}
			break;
			
			case kSampleMenu_RotateText:
			for (i = 0; i < len-1; i++) {
				newStr[i] = oldStr[i+1];
			}
			newStr[len-1] = oldStr[0];
			break;
		}
		
		error = SetControlData(editInfo->controlref, kControlNoPart, kControlEditTextTextTag, len, newStr);
		Draw1Control(editInfo->controlref);
	} 
	
	editInfo->modified = true;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleClick function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleClick(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleKeyDown function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
sample_HandleKeyDown(RezPlugRef inPlugref, const EventRecord * inKeyEvent)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Sample plugin of the HandleCommand function
//  declared in the interface (SPluginEditorInterface structure)
//
//  A plugin could handle one of the following commands:
// 		kPluginCommandCut
// 		kPluginCommandCopy
// 		kPluginCommandPaste
// 		kPluginCommandClear
// 		kPluginCommandSelectAll
// 		kPluginCommandFind
// 		kPluginCommandFindNext
// 		kPluginCommandExport
//  Which command it supports is declared in sample_AcceptResource via the 
//  "attributes" member of the RezPlugInfo struct.
// -------------------------------------------------------------------------------------------

Boolean
sample_HandleCommand(RezPlugRef inPlugref, SInt16 inCommand)
{
	Boolean cmdHandled = true;
	
	switch (inCommand) {
		case kPluginCommandCut:
		break;
		
		case kPluginCommandCopy:
		break;
		
		case kPluginCommandPaste:
		break;
		
		case kPluginCommandClear:
		break;
		
		case kPluginCommandSelectAll:
		break;
		
		default:
		cmdHandled = false;
		break;
		
	}
	
	return cmdHandled;
}



/***********************
*                      *
*   Factory function   *
*                      *
***********************/

// -------------------------------------------------------------------------------------------
//
//  Implementation of the factory function for the kRezillaPluginEditorTypeID type.
//  
//  From the doc 
//  (see /documentation/CoreFoundation/Conceptual/CFPlugIns/Concepts/conceptual.html):
//      "When called by the plug-in host, the factory function allocates
//      memory for an instance of the type being requested, sets up the
//      function tables for its interfaces, and returns a pointer to the
//      typeÕs IUnknown interface. The plug-in host can then use the
//      IUnknown interface to search for other interfaces supported by the
//      type."
//      
//  The return value is a void* but it is in fact a pointer to a SampleRec structure.
//
// -------------------------------------------------------------------------------------------

extern void * RezSampleFactory(CFAllocatorRef allocator, CFUUIDRef typeID);

void * RezSampleFactory( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	if ( CFEqual( typeID, kRezillaPluginEditorTypeID ) ) {
		// If correct type is being requested, allocate an instance of
		// the SampleRec struct and return the IUnknown interface
		SampleRec * result = _allocSampleRec( kRezillaSampleFactoryID );
		return result;
	} else {
		// If the requested type is incorrect, return NULL
		return NULL;
	}
}



/************************
*                       *
*   Utility functions   *
*                       *
************************/

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
//  Handler for text input which simply sets the modified flag and passes
//  the event to the default handler
//
// -------------------------------------------------------------------------------------------

pascal OSStatus 
_sampleTextInputHandler(EventHandlerCallRef inHandler, EventRef inEvent, void *userData)
{
	OSStatus 		result = eventNotHandledErr;
	UInt32			eventClass = GetEventClass( inEvent );
	UInt32			eventKind = GetEventKind( inEvent );
	ControlRef		ctrlRef;

	SampleEditInfo * editInfo = (SampleEditInfo *) userData;

	if ( eventClass == kEventClassTextInput && eventKind == kEventTextInputUnicodeForKeyEvent ) {
		GetEventParameter(inEvent, kEventParamDirectObject, typeControlRef, NULL, sizeof(ControlRef), NULL, &ctrlRef);
		editInfo->modified = true;
		result = CallNextEventHandler(inHandler, inEvent);
	}
	return result;
}


