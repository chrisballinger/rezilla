// ===========================================================================
// CDropStaticText.cp					
// 
//                       Created : 2003-04-12 10:45:24
//             Last modification : 2004-06-09 10:42:08
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// ===========================================================================
// Subclass implementing drag and drop of a file from the Finder onto a 
// text edit field.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CDropStaticText.h"
#include "CRezCompare.h"
#include "UMiscUtils.h"
#include "RezillaConstants.h"

#include <LDragTask.h>
#include <LControlImp.h>
#include <LStream.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CDropStaticText						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CDropStaticText::CDropStaticText(
	LStream*	inStream)
	: LStaticText(inStream), 
	LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{}



// ---------------------------------------------------------------------------
//	¥ ~CDropStaticText						Destructor				  [public]
// ---------------------------------------------------------------------------

CDropStaticText::~CDropStaticText()
{
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ItemIsAcceptable											  [protected]
// ---------------------------------------------------------------------------
// Accept only files.

Boolean 
CDropStaticText::ItemIsAcceptable(DragReference inDragRef, ItemReference inItemRef)
{
	FlavorFlags	theFlags;
	Boolean result = false;
	
	if (::GetFlavorFlags(inDragRef, inItemRef, flavorTypeHFS, &theFlags) == noErr) {
		CInfoPBRec theInfo;
		HFSFlavor fileData;
		GetFileData(inDragRef, inItemRef, fileData);
		theInfo.hFileInfo.ioCompletion = nil;
		theInfo.hFileInfo.ioVRefNum = fileData.fileSpec.vRefNum;
		theInfo.hFileInfo.ioDirID = fileData.fileSpec.parID;
		theInfo.hFileInfo.ioNamePtr = fileData.fileSpec.name;
		theInfo.hFileInfo.ioFDirIndex = 0;
		
		ThrowIfOSErr_(::PBGetCatInfoSync( &theInfo ));
		if ( !(theInfo.hFileInfo.ioFlAttrib & ioDirMask) ) {
			// It's not a directory
			result = true;
		}
	}
	return result;
}
		

// ---------------------------------------------------------------------------
//	¥ ReceiveDragItem											  [protected]
// ---------------------------------------------------------------------------
// Retrieve the dragged item's file system specification
// and insert the full path in the static text pane.

void 
CDropStaticText::ReceiveDragItem(DragReference inDragRef, 
								 DragAttributes inDragAttrs, 
								 ItemReference inItemRef, 
								 Rect & inItemBounds)
{
	HFSFlavor	fileData;
	Str255		thePath;
	
	if ( GetFileData(inDragRef, inItemRef, fileData) ) {
		if ( UMiscUtils::MakePath(&fileData.fileSpec, thePath, 450) == noErr ) {
			switch ( GetPaneID() ) {
			  case item_RezCompEditOld:
			    UMiscUtils::CopyFSSpec(fileData.fileSpec, CRezCompare::sOldFSSpec);
				break;
				
				case item_RezCompEditNew:
				  UMiscUtils::CopyFSSpec(fileData.fileSpec, CRezCompare::sNewFSSpec);
				  break;
			}
			SetDescriptor(thePath);
		} 
	}
}


// ---------------------------------------------------------------------------
//	¥ GetFileData												  [protected]
// ---------------------------------------------------------------------------
// If the flavour data is an HFSFlavor structure, retrieve it.

Boolean 
CDropStaticText::GetFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData)
{
	Size size;
	OSErr err = ::GetFlavorDataSize(inDragRef, inItemRef, flavorTypeHFS, &size);
	
	return (err == noErr 
			&& size == sizeof(HFSFlavor) 
			&& ::GetFlavorData(inDragRef, inItemRef, 
							flavorTypeHFS, &fileData, &size, 0) == noErr);
}


PP_End_Namespace_PowerPlant
