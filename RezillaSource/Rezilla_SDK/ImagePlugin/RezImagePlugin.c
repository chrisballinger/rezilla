// ===========================================================================
// File: "RezImagePlugin.c"
// 
//                        Created: 2006-02-20 14:15:30
//              Last modification: 2006-03-02 14:18:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <QuickTime/ImageCompression.h>			// For image loading and decompression
#include <QuickTime/QuickTimeComponents.h>		// For DataRef extensions

#include "RezillaPluginInterface.h"
#include "RezImagePluginID.h"


// ID of the Image menu
#define kRezJpegPluginMenuID 500

// Default dimensions of the plugin window
#define kRezImg_WinBoundsTop		50;
#define kRezImg_WinBoundsLeft		50;
#define kRezImg_WinBoundsBottom		600;
#define kRezImg_WinBoundsRight		500;

#define MAX_IMAGE_WIDTH		500
#define MAX_IMAGE_HEIGHT	600


// Image plugin record
typedef struct RezImg_Rec {
	SPluginEditorInterface *	_rezillaPlugInterface;
	CFUUIDRef					_factoryID;
	UInt32						_refCount;
} RezImg_Rec;


// Image editor info struct
typedef struct RezImg_EditInfo {
	ResType				type;
	short				id;
	Handle				handle;
	WindowRef			winref;
	ControlRef			controlref;
	Boolean				modified;
	Boolean				readonly;
	OSType				imageType;
	size_t				width;
	size_t				height;
	size_t				bitsPerComponent;
	size_t				bitsPerPixel;
	size_t				bytesPerRow;
	size_t				size;
	unsigned char *		bitmapData;
	CGImageAlphaInfo	alphaInfo;
	CGColorSpaceRef		colorSpace;
	CMProfileRef		profileRef;
} RezImg_EditInfo;


// Menu items
enum {
	menu_RotateLeft = 1,
	menu_RotateRight = 2,
	menu_FlipHorizontal = 4,
	menu_FlipVertical = 5,
	menu_Erase = 7
} RezImg_MenuItems;


// Image plugin error codes
static enum {
	err_InvalidImageSize		= 10001,
	err_CannotAllocateHandleDataRef,
	err_CannotGetGraphicsImporter,
	err_RetrievingImageDescriptionFailed,
	err_CannotOpenProfile,
	err_InvalidProfile,
	err_CreatingEmbeddedColorSpaceWithCsyncFailed,
	err_NoBitmapBufferAvailable,
	err_CreatingNewGworldFailed,
	err_SettingGworldFailed,
	err_ImageCreateFailed,
	err_DrawingImageThroughQuickTimeFailed
} RezImg_Errors;


// Statics
static MenuID		RezImg_MenuID;
static MenuRef		RezImg_MenuRef;


// Prototypes
// ----------
static RezImg_Rec*	_RezImg_allocRec( CFUUIDRef factoryID );
static void			_RezImg_deallocRec( RezImg_Rec *myInstance );
static OSErr		_RezImg_readBitmapInfo(GraphicsImportComponent gi, RezImg_EditInfo *bi);
static OSErr		_RezImg_getBitmapData(GraphicsImportComponent gi, RezImg_EditInfo *bi);
static void 		_RezImg_rescaleImage( size_t* imageWidthPtr, size_t* imageHeightPtr, size_t maxWidth, size_t maxHeight );
static Handle		_RezImg_createHandleDataRef(Handle dataHandle, OSType fileType, StringPtr mimeTypeString);

static HRESULT		RezImg_QueryInterface(void *myInstance, REFIID iid, LPVOID *ppv );
static ULONG		RezImg_AddRef(void *myInstance );
static ULONG		RezImg_Release(void *myInstance );
static Boolean		RezImg_AcceptResource(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo);
static OSErr		RezImg_EditResource(RezPlugRef inPlugref, RezHostInfo inInfo);
static Handle		RezImg_ReturnResource(RezPlugRef inPlugref, Boolean * releaseIt, OSErr * outError);
static OSErr		RezImg_RevertResource(RezPlugRef inPlugref, Handle inDataH);
static Boolean		RezImg_IsModified(RezPlugRef inPlugref);
static 	void		RezImg_CleanUp(RezPlugRef inPlugref);
static 	void		RezImg_Refresh(RezPlugRef inPlugref);
static 	void		RezImg_ResizeBy(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta);
static void			RezImg_HandleMenu(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem);
static void			RezImg_HandleClick(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords);
static void			RezImg_HandleKeyDown(RezPlugRef inPlugref, const EventRecord * inKeyEvent);
static Boolean		RezImg_HandleCommand(RezPlugRef inPlugref, SInt16 inCommand);


// The Rezilla Editor Interface function table
// -------------------------------------------
static SPluginEditorInterface sImagePlugFuncTable = {
		NULL,						// Required padding for COM
		RezImg_QueryInterface,		// These three are the required COM functions
		RezImg_AddRef,
		RezImg_Release,
		RezImg_AcceptResource,
		RezImg_EditResource,
		RezImg_ReturnResource,
		RezImg_RevertResource,
		RezImg_IsModified,
		RezImg_CleanUp,
		RezImg_Refresh,
		RezImg_ResizeBy,
		RezImg_HandleMenu,
		RezImg_HandleClick,
		RezImg_HandleKeyDown,
		RezImg_HandleCommand
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
RezImg_QueryInterface(void *myInstance, REFIID iid, LPVOID *ppv )
{
	HRESULT	res;
	
	// Create an UUIDRef for the requested interface
	CFUUIDRef interfaceID = CFUUIDCreateFromUUIDBytes( NULL, iid );

	// Test the requested ID against the valid interfaces
	if ( CFEqual( interfaceID, kRezillaPluginEditorInterfaceID ) ) {
		// If the RezillaPluginInterface was requested, bump the ref count,
		// set the ppv parameter equal to the instance, and return good status
		( (RezImg_Rec *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
		*ppv = myInstance;
		res = S_OK;
	} else if ( CFEqual( interfaceID, IUnknownUUID ) ) {
		// If the IUnknown interface was requested, same as above
		( (RezImg_Rec *) myInstance )->_rezillaPlugInterface->AddRef( myInstance );
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
RezImg_AddRef(void *myInstance )
{
	( (RezImg_Rec *) myInstance )->_refCount += 1;
	return ( (RezImg_Rec *) myInstance )->_refCount;
}


// -------------------------------------------------------------------------------------------
//
//  When an interface is released, decrement the refCount.
//  If the refCount goes to zero, deallocate the instance.
//
// -------------------------------------------------------------------------------------------

ULONG
RezImg_Release(void *myInstance )
{
	( (RezImg_Rec *) myInstance )->_refCount -= 1;
	if ( ( (RezImg_Rec *) myInstance )->_refCount == 0 ) {
		_RezImg_deallocRec( (RezImg_Rec *) myInstance );
		return 0;
	} else {
		return ( (RezImg_Rec *) myInstance )->_refCount;
	}
}



/************************
*                       *
*   Rezilla Interface   *
*                       *
************************/

// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the AcceptResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------
// From: QuickTime/ImageCompression.h
// 		kBMPCodecType		= 'WRLE',
// 		kGIFCodecType		= 'gif ',
// 		kJPEGCodecType		= 'jpeg',
// 		kPNGCodecType		= 'png ',
// 		kPhotoCDCodecType	= 'kpcd',
// 		kTIFFCodecType		= 'tiff', 

Boolean
RezImg_AcceptResource(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo)
{
	Boolean accepted = true;
	OSType	imgType;
	
	RezImg_MenuID = kRezJpegPluginMenuID;

	if (inType == 'JPEG' || inType == 'jpeg' || inType == 'JPG ' || inType == 'jpg ') {
		imgType = kJPEGCodecType;
	} else if (inType == 'TIFF' || inType == 'tiff') {
		imgType = kTIFFCodecType;
	} else if (inType == 'GIF ' || inType == 'gif ') {
		imgType = kGIFCodecType;
	} else if (inType == 'PNG ' || inType == 'png ') {
		imgType = kPNGCodecType;
	} else if (inType == 'BMP ' || inType == 'bmp ') {
		imgType = kBMPCodecType;
	}  else if (inType == 'kpcd') {
		imgType = kPhotoCDCodecType;
	} else {
		outInfo->error = plugErr_UnsupportedType;
		accepted = false;
	}
	
	if (accepted) {
		RezImg_EditInfo * editInfo = (RezImg_EditInfo *) malloc( sizeof(RezImg_EditInfo) );	
		
		if (editInfo == NULL) {
			outInfo->error = plugErr_InitializationFailed;
			accepted = false;
		} else {
			size_t		imageWidth, imageHeight;
			OSErr		error;
			Handle		dataRef = nil;
			GraphicsImportComponent	gi;
			
			// Initialize the RezImg_EditInfo struct
			editInfo->type			= inType;
			editInfo->id			= inID;
			editInfo->handle		= inDataH;
			editInfo->winref		= NULL;
			editInfo->controlref	= NULL;
			editInfo->modified		= false;
			editInfo->imageType		= imgType;
			editInfo->bitmapData	= NULL;
			
			dataRef = _RezImg_createHandleDataRef(inDataH, imgType, NULL);
			if (dataRef) {
				error = GetGraphicsImporterForDataRef(dataRef, HandleDataHandlerSubType, &gi);
			} else {
				outInfo->error = err_CannotAllocateHandleDataRef;
				return false;
			}
			
			if (error != noErr) {
				outInfo->error = err_CannotGetGraphicsImporter;
				return false;
			} 			
			
			// Get info about the image
			error = _RezImg_readBitmapInfo(gi, editInfo);
			if (error != noErr) {
				outInfo->error = error;
				return false;
			} 
			error = _RezImg_getBitmapData(gi, editInfo);
			if (error != noErr) {
				outInfo->error = error;
				return false;
			} 
			
			CloseComponent(gi);
			
			if( editInfo->width <= 0 || editInfo->width > 32767 || editInfo->height <= 0 || editInfo->height > 32767) {
				outInfo->error = err_InvalidImageSize;
				return false;
			}
			
			//	We should check and make sure that the image isn't too large to fit comfortably onscreen
			imageWidth = editInfo->width;
			imageHeight = editInfo->height;
			if ( imageWidth > MAX_IMAGE_WIDTH || imageHeight > MAX_IMAGE_HEIGHT ) {
				_RezImg_rescaleImage( &imageWidth, &imageHeight, MAX_IMAGE_WIDTH, MAX_IMAGE_HEIGHT );
			}
			
			// Fill the RezPlugInfo
			outInfo->plugref			= (RezPlugRef) editInfo;
			outInfo->attributes			= kPluginWinStandardAttributes 
											| kPluginWinHasNameField 
											| kPluginWinIsResizable
											| kPluginSupportEditCommands;
			outInfo->winbounds.top		= kRezImg_WinBoundsTop;
			outInfo->winbounds.left		= kRezImg_WinBoundsLeft;
			outInfo->winbounds.bottom	= kRezImg_WinBoundsBottom;
			outInfo->winbounds.right	= kRezImg_WinBoundsRight;
			outInfo->menucount			= 1;
			outInfo->menuIDs			= &RezImg_MenuID;
		}
	}
	
	return accepted;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the EditResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

OSErr
RezImg_EditResource(RezPlugRef inPlugref, RezHostInfo inInfo)
{
	OSErr					error = noErr;
	HIRect					theViewRect;
	HIViewRef				theImageView, theScrollView, theContentView;
	CGDataProviderRef		theProvider = NULL;
	CGColorSpaceRef			theColorspace = NULL;
	CGImageRef				theImage = NULL;

	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	
	editInfo->winref = inInfo.winref;
	editInfo->readonly = inInfo.readonly;
	RezImg_MenuRef = *inInfo.menurefs;
	
	// Quartz stuff to put the image into an image view
	theProvider = CGDataProviderCreateWithData(NULL, editInfo->bitmapData, editInfo->size, NULL);
	if (editInfo->colorSpace != NULL) {
		theColorspace = editInfo->colorSpace;
	} else {
		theColorspace = CGColorSpaceCreateDeviceRGB();
	}
	
	if (theProvider && theColorspace) {
		theImage = CGImageCreate(editInfo->width, editInfo->height, editInfo->bitsPerComponent, editInfo->bitsPerPixel,
								  editInfo->bytesPerRow, theColorspace, editInfo->alphaInfo, theProvider, NULL, 0, kCGRenderingIntentDefault);
	} 
	
	if (theProvider) { CGDataProviderRelease( theProvider ); } 
	if (theColorspace) { CGColorSpaceRelease( theColorspace ); } 

	if (theImage == NULL) {
		return err_ImageCreateFailed;
	}
		
	// Create the scroll view and image view
	HIScrollViewCreate(kHIScrollViewOptionsVertScroll | kHIScrollViewOptionsHorizScroll, &theScrollView);
	HIViewSetVisible(theScrollView, true);
	HIViewFindByID(HIViewGetRoot(editInfo->winref), kHIViewWindowContentID, &theContentView);
	
	HIViewAddSubview(theContentView, theScrollView);
	
	theViewRect.origin.x = inInfo.contents.left;
	theViewRect.origin.y = inInfo.contents.top;
	theViewRect.size.width = inInfo.contents.right - inInfo.contents.left;
	theViewRect.size.height = inInfo.contents.bottom - inInfo.contents.top;
	HIViewSetFrame(theScrollView, &theViewRect);
	
	HIImageViewCreate(theImage, &theImageView);
	CGImageRelease(theImage);
	
	HIViewSetVisible(theImageView, true);
	HIViewAddSubview(theScrollView, theImageView);
	
	return error;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the ReturnResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

Handle
RezImg_ReturnResource(RezPlugRef inPlugref, Boolean * releaseIt, OSErr * outError)
{
	Handle		theHandle = NULL;
	Size		theSize;
	Str255		theString;
	char		buffer[256];
	OSErr		error = noErr;
	
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	
	error = GetControlData(editInfo->controlref, kControlNoPart, kControlEditTextTextTag, sizeof(buffer), buffer, &theSize);
	
	if (error == noErr) {
		buffer[theSize] = 0;
		theHandle = NewHandle(theSize+1);
		CopyCStringToPascal(buffer, theString);
		BlockMoveData(theString, *theHandle, theSize+1);
		*releaseIt = true;
	} 
	
	*outError = error;
	return theHandle;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the RevertResource function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

OSErr
RezImg_RevertResource(RezPlugRef inPlugref, Handle inDataH)
{
	OSErr		error = noErr;
	
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
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
RezImg_IsModified(RezPlugRef inPlugref)
{
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	return editInfo->modified;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the CleanUp function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_CleanUp(RezPlugRef inPlugref)
{
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	DisposeControl(editInfo->controlref);
	if ( editInfo->bitmapData != NULL ) {
		free(editInfo->bitmapData);
	}
	free(editInfo);
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the Refresh function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_Refresh(RezPlugRef inPlugref)
{
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	UpdateControls(editInfo->winref, NULL);
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the ResizeBy function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_ResizeBy(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the HandleMenu function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_HandleMenu(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem)
{
	OSErr		error = noErr;
	
	RezImg_EditInfo * editInfo = (RezImg_EditInfo *) inPlugref;
	
	switch (inMenuItem) {
		case menu_RotateLeft:
		break;
		
		case menu_RotateRight:
		break;
		
		case menu_FlipHorizontal:
		break;
		
		case menu_FlipVertical:
		break;
		
		case menu_Erase:
		break;
		
	}
	
	editInfo->modified = true;
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the HandleClick function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_HandleClick(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the HandleKeyDown function
//  declared in the interface (SPluginEditorInterface structure)
//
// -------------------------------------------------------------------------------------------

void
RezImg_HandleKeyDown(RezPlugRef inPlugref, const EventRecord * inKeyEvent)
{
}


// -------------------------------------------------------------------------------------------
//
//  The implementation by the Image plugin of the HandleCommand function
//  declared in the interface (SPluginEditorInterface structure)
//
//  The Image plugin handles the following commands:
// 		kPluginCommandCut
// 		kPluginCommandCopy
// 		kPluginCommandPaste
// 		kPluginCommandClear
// -------------------------------------------------------------------------------------------

Boolean
RezImg_HandleCommand(RezPlugRef inPlugref, SInt16 inCommand)
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
//  From the doc 
//  (/documentation/CoreFoundation/Conceptual/CFPlugIns/Concepts/conceptual.html):
//      "When called by the plug-in host, the factory function allocates
//      memory for an instance of the type being requested, sets up the
//      function tables for its interfaces, and returns a pointer to the
//      typeÕs IUnknown interface. The plug-in host can then use the
//      IUnknown interface to search for other interfaces supported by the
//      type."
//      
//  The return value is a void* but is in fact a pointer to a RezImg_Rec structure.
//
// -------------------------------------------------------------------------------------------

extern void * RezillaImageFactory(CFAllocatorRef allocator, CFUUIDRef typeID);

void * RezillaImageFactory( CFAllocatorRef allocator, CFUUIDRef typeID )
{
	if ( CFEqual( typeID, kRezillaPluginEditorTypeID ) ) {
		// If correct type is being requested, allocate an instance of
		// the RezImg_Rec struct and return the IUnknown interface
		RezImg_Rec * result = _RezImg_allocRec( kRezillaImageFactoryID );
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

RezImg_Rec *
_RezImg_allocRec( CFUUIDRef factoryID )
{
	// Allocate memory for the new instance
	RezImg_Rec * newType = (RezImg_Rec *) malloc( sizeof(RezImg_Rec) );

	// Point to the function table
	newType->_rezillaPlugInterface = &sImagePlugFuncTable;

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

void 
_RezImg_deallocRec( RezImg_Rec *myInstance )
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
// Adapted from Apple's QTtoCG sample code
//
// -------------------------------------------------------------------------------------------

OSErr
_RezImg_readBitmapInfo(GraphicsImportComponent gi, RezImg_EditInfo * editInfo)
{
	ComponentResult result;
	ImageDescriptionHandle imageDescH = NULL;
	ImageDescription *desc;
	Handle profile = NULL;
	OSErr					error = noErr;
	
	result = GraphicsImportGetImageDescription(gi, &imageDescH);
	if( noErr != result || imageDescH == NULL ) {
		return err_RetrievingImageDescriptionFailed;
	}
	
	desc = *imageDescH;
	
	editInfo->width = desc->width;
	editInfo->height = desc->height;
	editInfo->bitsPerComponent = 8;
	editInfo->bitsPerPixel = 32;
	editInfo->bytesPerRow = (editInfo->bitsPerPixel * editInfo->width + 7)/8;
	editInfo->alphaInfo = (desc->depth == 32) ? kCGImageAlphaFirst : kCGImageAlphaNoneSkipFirst;
	editInfo->size = editInfo->bytesPerRow * editInfo->height;
	editInfo->bitmapData = malloc(editInfo->size);
	
	// Look for any embedded profile
	editInfo->colorSpace = NULL;
	editInfo->profileRef = NULL;
	GraphicsImportGetColorSyncProfile(gi, &profile);
	if( profile != NULL ) {
		CMError err;
		CMProfileLocation profLoc;
		Boolean bValid, bPreferredCMMNotFound;
		
		profLoc.locType = cmHandleBasedProfile;
		profLoc.u.handleLoc.h = profile;
		
		err = CMOpenProfile(&editInfo->profileRef, &profLoc);
		if( err != noErr ) {
			error = err_CannotOpenProfile;
			goto bail;
		}
		
		// Not necessary to validate profile, but good for debugging
		err = CMValidateProfile(editInfo->profileRef, &bValid, &bPreferredCMMNotFound);
		if( err != noErr ) {
			error = err_InvalidProfile;
			goto bail;
		}
		
		editInfo->colorSpace = CGColorSpaceCreateWithPlatformColorSpace( &editInfo->profileRef );
		
		if( editInfo->colorSpace == NULL ) {
			error = err_CreatingEmbeddedColorSpaceWithCsyncFailed;
			goto bail;
		}
	}	
	
bail:
	if ( profile != NULL) {
		DisposeHandle(profile);
	}
	if ( imageDescH != NULL) {
		DisposeHandle((Handle)imageDescH);
	}

	return error;
}


// -------------------------------------------------------------------------------------------
//
// Adapted from Apple's QTtoCG sample code
//
// -------------------------------------------------------------------------------------------

OSErr
_RezImg_getBitmapData(GraphicsImportComponent gi, RezImg_EditInfo * editInfo)
{
	GWorldPtr		gWorld;
	QDErr			error = noErr;
	Rect			boundsRect = { 0, 0, editInfo->height, editInfo->width };
	ComponentResult	result;
	
	if ( editInfo->bitmapData == NULL ) {
		return err_NoBitmapBufferAvailable;
	}
	
	error = NewGWorldFromPtr( &gWorld, k32ARGBPixelFormat, &boundsRect, NULL, NULL, 0, 
						   editInfo->bitmapData, editInfo->bytesPerRow );
	if (noErr != error) {
		return err_CreatingNewGworldFailed;
	}
	
	if ( (result = GraphicsImportSetGWorld(gi, gWorld, NULL)) != noErr ) {
		error = err_SettingGworldFailed;
		goto bail;
	}
	
	if ( (result = GraphicsImportDraw(gi)) != noErr ) {
		error = err_DrawingImageThroughQuickTimeFailed;
		goto bail;
	}
	
bail:
	DisposeGWorld(gWorld);
	
	return error;
}


// -------------------------------------------------------------------------------------------
//
// Adapted from Apple's QTtoCG sample code
//
// -------------------------------------------------------------------------------------------

void 
_RezImg_rescaleImage( size_t* imageWidthPtr, size_t* imageHeightPtr, size_t maxWidth, size_t maxHeight )
{
	size_t	width = *imageWidthPtr;
	size_t	height = *imageHeightPtr;
	double	widthFactor = (double)width / (double)maxWidth;
	double	heightFactor = (double)height / (double)maxHeight;
	
	if ( widthFactor > heightFactor ) {
		// We're further off in the x axis than we are in the y
		*imageWidthPtr = width / widthFactor;
		*imageHeightPtr = height / widthFactor;
	} else {
		// We're further off in the y axis than we are in the x
		*imageWidthPtr = width / heightFactor;
		*imageHeightPtr = height / heightFactor;
	}
}


// -------------------------------------------------------------------------------------------
//
// Adapted from Apple's Technical Q&A QTMTB56
//
// -------------------------------------------------------------------------------------------
// With QuickTime 4, the handle data handler can also be told the
// filetype and/or MIME type by adding data ref extensions. These help
// the importer finding process.

Handle 
_RezImg_createHandleDataRef(
					Handle             dataHandle,
					OSType             fileType,
					StringPtr          mimeTypeString)
{
	 OSErr		error;
	 Handle		dataRef = nil;
	 Str31		name;
	 long		atoms[3];

	// First create a data reference handle for our data
	error = PtrToHand( &dataHandle, &dataRef, sizeof(Handle));
	if (error) goto bail;

	name[0] = 0;

	// Add an empty file name (if we are also adding a file type, or MIME type)
	if ((fileType) || (mimeTypeString)) {
		error = PtrAndHand(name, dataRef, name[0]+1);
		if (error) goto bail;
	}

	// To add file type, add a classic atom followed by the MacOS filetype
	// for the kind of file
	if (fileType) {
		atoms[0] = EndianU32_NtoB(sizeof(long) * 3);
		atoms[1] = EndianU32_NtoB(kDataRefExtensionMacOSFileType);
		atoms[2] = EndianU32_NtoB(fileType);

		error = PtrAndHand(atoms, dataRef, sizeof(long) * 3);
		if (error) goto bail;
	}

	// To add MIME type information, add a classic atom followed by a
	// Pascal string holding the MIME type
	if (mimeTypeString) {
		atoms[0] = EndianU32_NtoB(sizeof(long) * 2 + mimeTypeString[0]+1);
		atoms[1] = EndianU32_NtoB(kDataRefExtensionMIMEType);

		error = PtrAndHand(atoms, dataRef, sizeof(long) * 2);
		if (error) goto bail;

		error = PtrAndHand(mimeTypeString, dataRef, mimeTypeString[0]+1);
		if (error) goto bail;
	}

	return dataRef;

bail:
	if (dataRef) {
		// Dispose the data reference handle
		// once we are done with it
		DisposeHandle(dataRef);
	}

	return nil;
}

