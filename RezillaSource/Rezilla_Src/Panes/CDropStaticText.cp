// ===========================================================================
// CDropStaticText.cp					
// 
//                       Created : 2003-04-12 10:45:24
//             Last modification : 2004-02-29 18:50:16
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass implementing drag and drop of a file from the Finder onto a 
// text edit field.

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CDropStaticText.h"

#include <LDragTask.h>
#include <LControlImp.h>
#include <LStream.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CDropStaticText								Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CDropStaticText::CDropStaticText(
	LStream*	inStream)
	: LStaticText(inStream), 
	LDragAndDrop( UQDGlobals::GetCurrentWindowPort(), this )
{}



// ---------------------------------------------------------------------------
//	¥ ~CDropStaticText								Destructor				  [public]
// ---------------------------------------------------------------------------

CDropStaticText::~CDropStaticText()
{
}

#pragma mark -

// ---------------------------------------------------------------------------
//	¥ ItemIsAcceptable										  [protected]
// ---------------------------------------------------------------------------
// Diff and patch dialogs accept files of type 'TEXT' dragged onto the static 
// text from the Finder. Cmp dialog accepts all files.

Boolean 
CDropStaticText::ItemIsAcceptable(DragReference inDragRef, ItemReference inItemRef)
{
	FlavorFlags	theFlags;
	Boolean isDirectory = false;
	
	if (::GetFlavorFlags(inDragRef, inItemRef, flavorTypeHFS, &theFlags) == noErr)
	{
		CInfoPBRec theInfo;
		HFSFlavor fileData;
		GetFileData(inDragRef, inItemRef, fileData);
		theInfo.hFileInfo.ioCompletion = nil;
		theInfo.hFileInfo.ioVRefNum = fileData.fileSpec.vRefNum;
		theInfo.hFileInfo.ioDirID = fileData.fileSpec.parID;
		theInfo.hFileInfo.ioNamePtr = fileData.fileSpec.name;
		theInfo.hFileInfo.ioFDirIndex = 0;
		
		ThrowIfOSErr_(::PBGetCatInfoSync( &theInfo ));
		if ( theInfo.hFileInfo.ioFlAttrib & ioDirMask ) {
			// It's a directory
			isDirectory = true;
		}
		
// 		if ( CDiffPatchApp::sMainCmpWindow != nil 
// 			&& CDiffPatchApp::sMainCmpWindow->GetMacWindow() == GetMacWindow() 
// 			&& !isDirectory) {
// 			return true;
// 		} else if ( CDiffPatchApp::sMainDiffWindow != nil 
// 				   && CDiffPatchApp::sMainDiffWindow->GetMacWindow() == GetMacWindow() ) {
// 			if (CDiffPatchApp::sMainDiffWindow->GetComparisonType() == comp_Folders && isDirectory) {
// 				return true;
// 			} else if (CDiffPatchApp::sMainDiffWindow->GetComparisonType() == comp_Files && !isDirectory) {
// 				return (fileData.fileType == 'TEXT');
// 			}
// 		} else { 
// 			return (fileData.fileType == 'TEXT');
// 		}
	}
	return false;
}
		

// ---------------------------------------------------------------------------
//	¥ ReceiveDragItem										  [protected]
// ---------------------------------------------------------------------------
// Retrieve the dragged item's file system specification
// and insert the full path in the static text pane.

void 
CDropStaticText::ReceiveDragItem(DragReference inDragRef, 
								 DragAttributes inDragAttrs, 
								 ItemReference inItemRef, 
								 Rect & inItemBounds)
{
	HFSFlavor fileData;
	Str255	thePath;
	
	if ( GetFileData(inDragRef, inItemRef, fileData) )
	{
// 		if ( CDiffPatchApp::MakePath(&fileData.fileSpec, thePath, 450) == noErr ) {
// 			SetDescriptor(thePath);
// 		} 
		// Identify the containing window and update the relevant file members
		WindowPtr theCurrWPtr = GetMacWindow() ;
// 		if ( CDiffPatchApp::sMainDiffWindow != nil 
// 			&& CDiffPatchApp::sMainDiffWindow->GetMacWindow() == theCurrWPtr ) {
// 			CDiffPatchApp::sMainDiffWindow->SetFileSpecifier(& fileData.fileSpec, mPaneID);
// 		} else if ( CDiffPatchApp::sMainPatchWindow != nil 
// 				   && CDiffPatchApp::sMainPatchWindow->GetMacWindow() == theCurrWPtr ) {
// 			CDiffPatchApp::sMainPatchWindow->SetFileSpecifier(& fileData.fileSpec, mPaneID);
// 		} else if ( CDiffPatchApp::sMainCmpWindow != nil 
// 				   && CDiffPatchApp::sMainCmpWindow->GetMacWindow() == theCurrWPtr ) {
// 			CDiffPatchApp::sMainCmpWindow->SetFileSpecifier(& fileData.fileSpec, mPaneID);
// 		}
	}
}


// ---------------------------------------------------------------------------
//	¥ GetFileData										  [protected]
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
