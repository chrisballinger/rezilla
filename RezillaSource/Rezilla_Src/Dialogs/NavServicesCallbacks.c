// ===========================================================================
// NavServicesCallbacks.c					
//                       Created: 2003-05-07 15:58:27
//             Last modification: 2004-03-23 15:48:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "NavServicesCallbacks.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"

extern const Str255 Rzil_NavExportItems[];

#define kNavCustomDITLWidth 400
#define kNavCustomDITLHeight 40


// ---------------------------------------------------------------------------
//  ¥ Rzil_NewMapNavEventFilterUPP										
// ---------------------------------------------------------------------------

pascal void
Rzil_NewMapNavEventFilterUPP(NavEventCallbackMessage inCBSelector, 
						   NavCBRecPtr inCBParams, 
						   void *ioCallBackUD)
{
	SInt16		theItemIndex = *(SInt16 *)ioCallBackUD;
	short		firstItem;
	ControlHandle	theControlH;

	switch (inCBSelector)
	{
		case kNavCBCustomize:
		{
			if (inCBParams->customRect.right < inCBParams->customRect.left + kNavCustomDITLWidth)
			{
				inCBParams->customRect.right = inCBParams->customRect.left + kNavCustomDITLWidth;
			}
			
			if (inCBParams->customRect.bottom < inCBParams->customRect.top + kNavCustomDITLHeight)
			{
				inCBParams->customRect.bottom = inCBParams->customRect.top + kNavCustomDITLHeight;
			}
		}
		break;

		case kNavCBStart:
		{
			Handle theList = ::GetResource( ResType_DITL, DITL_NewMap);
			OSErr theResult;
			
			theResult = ::NavCustomControl( inCBParams->context, kNavCtlAddControlList, theList);
			::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);

			if (theItemIndex == fork_rezfork)
			{
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapRF + firstItem, &theControlH);
			}
			else 
			{
				Assert_(theItemIndex == fork_datafork);
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapDF + firstItem, &theControlH);
			}
			::SetControlValue(theControlH, TRUE);
		}
		break;
		
		case kNavCBEvent:
		{
			Rzil_NewMapHandleEvent(inCBParams, ioCallBackUD);
		}
		break;
		
		default:
		{
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_OpenNavEventFilterUPP										
// ---------------------------------------------------------------------------

pascal void
Rzil_OpenNavEventFilterUPP(NavEventCallbackMessage inCBSelector, 
						   NavCBRecPtr inCBParams, 
						   void *ioCallBackUD)
{
	Rzil_OpenFileUD *	theUserData = (Rzil_OpenFileUD *) ioCallBackUD;
	short			firstItem;
	ControlHandle	theControlH;

	switch (inCBSelector)
	{
		case kNavCBCustomize:
		{
			if (inCBParams->customRect.right < inCBParams->customRect.left + kNavCustomDITLWidth)
			{
				inCBParams->customRect.right = inCBParams->customRect.left + kNavCustomDITLWidth;
			}
			
			if (inCBParams->customRect.bottom < inCBParams->customRect.top + kNavCustomDITLHeight)
			{
				inCBParams->customRect.bottom = inCBParams->customRect.top + kNavCustomDITLHeight;
			}
		}
		break;

		case kNavCBStart:
		{
			Handle theList = ::GetResource( ResType_DITL, DITL_OpenMap);
			OSErr theResult;
						
			theResult = ::NavCustomControl( inCBParams->context, kNavCtlAddControlList, theList);
			::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);

			if (theUserData->whichFork == fork_anyfork)
			{
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapAny + firstItem, &theControlH);
			}
			else if (theUserData->whichFork == fork_rezfork)
			{
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRF + firstItem, &theControlH);
			}
			else 
			{
				Assert_(theUserData->whichFork == fork_datafork);
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapDF + firstItem, &theControlH);
			}
			::SetControlValue(theControlH, TRUE);

			::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRO + firstItem, &theControlH);
			::SetControlValue(theControlH, theUserData->isReadOnly);
		}
		break;
		
		case kNavCBEvent:
		{
			Rzil_OpenMapHandleEvent(inCBParams, ioCallBackUD);
		}
		break;
		
		default:
		{
		}
		break;
	}

}


// ---------------------------------------------------------------------------
//  ¥ Rzil_SaveAsNavEventFilterUPP										
// ---------------------------------------------------------------------------

pascal void
Rzil_SaveAsNavEventFilterUPP(NavEventCallbackMessage inCBSelector, 
						   NavCBRecPtr inCBParams, 
						   void *ioCallBackUD)
{

	SInt16			theItemIndex = *(SInt16 *)ioCallBackUD;
	short			firstItem;
	ControlHandle	theControlH;

	switch (inCBSelector)
	{
		case kNavCBCustomize:
		{
			if (inCBParams->customRect.right < inCBParams->customRect.left + kNavCustomDITLWidth)
			{
				inCBParams->customRect.right = inCBParams->customRect.left + kNavCustomDITLWidth;
			}
			
			if (inCBParams->customRect.bottom < inCBParams->customRect.top + kNavCustomDITLHeight)
			{
				inCBParams->customRect.bottom = inCBParams->customRect.top + kNavCustomDITLHeight;
			}
		}
		break;

		case kNavCBStart:
		{
			Handle theList = ::GetResource( ResType_DITL, DITL_SaveMap);
			OSErr theResult;
						
			theResult = ::NavCustomControl( inCBParams->context, kNavCtlAddControlList, theList);
			::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);

			if (theItemIndex == fork_samefork)
			{
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapSame + firstItem, &theControlH);
			}
			else if (theItemIndex == fork_rezfork)
			{
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapRF + firstItem, &theControlH);
			}
			else 
			{
				Assert_(theItemIndex == fork_datafork);
				::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapDF + firstItem, &theControlH);
			}
			::SetControlValue(theControlH, TRUE);
		}
		break;
		
		case kNavCBEvent:
		{
			Rzil_SaveMapHandleEvent(inCBParams, ioCallBackUD);
		}
		break;
		
		default:
		{
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_ExportNavEventFilterUPP										
// ---------------------------------------------------------------------------

pascal void
Rzil_ExportNavEventFilterUPP(NavEventCallbackMessage inCBSelector, 
						   NavCBRecPtr inCBParams, 
						   void *ioCallBackUD)
{
	SInt16				theOutputIndex = *(SInt16 *)ioCallBackUD;
	NavMenuItemSpec		theMenuItemSpec;
	Str255				theFileName;
	static Str15		theExtension[4];
	
	if (inCBSelector == kNavCBStart) {
		// Get the filename extensions
		GetIndString(theExtension[0], STRx_FileExtensions, index_ExtXml);
		GetIndString(theExtension[1], STRx_FileExtensions, index_ExtText);
		GetIndString(theExtension[2], STRx_FileExtensions, index_ExtHtml);
		GetIndString(theExtension[3], STRx_FileExtensions, index_ExtR);
		// Set Xml (i-e Rzil_NavExportItems[0]) as the default
		theMenuItemSpec.version = kNavMenuItemSpecVersion;
		theMenuItemSpec.menuCreator = FOUR_CHAR_CODE('Rzil');
		theMenuItemSpec.menuType = 'TEXT';
		BlockMoveData(Rzil_NavExportItems[0], theMenuItemSpec.menuItemName, Rzil_NavExportItems[0][0] + 1);
		::NavCustomControl(inCBParams->context, kNavCtlSelectCustomType, &theMenuItemSpec);
		*(SInt16 *)ioCallBackUD = -1;
	}
	
	if (inCBSelector == kNavCBPopupMenuSelect) {
		theMenuItemSpec = *(NavMenuItemSpec *)inCBParams->eventData.eventDataParms.param;
		// Find the index of the selected item
		for (theOutputIndex = 0; theOutputIndex < 4; theOutputIndex++) {
			if (EqualString(theMenuItemSpec.menuItemName, Rzil_NavExportItems[theOutputIndex], true, false)) {
				break;
			}
		}
	}
	
	if (*(SInt16 *)ioCallBackUD != theOutputIndex) {
		// the popup item selected
		short			theIndex;
		short			theCount;
		
		// get the current filename
		NavCustomControl(inCBParams->context, kNavCtlGetEditFileName, &theFileName);
		
		// find the position of the last filename separator in the current filename
		theIndex = theFileName[0];
		while ((theFileName[theIndex] != kFileExtSeparator) && (theIndex > 0))
		theIndex--;
		
		if (theIndex == 0) {
			theIndex = theFileName[0]+1;
			theFileName[theIndex] = kFileExtSeparator;
		}			
		for (theCount = 1; theCount <= theExtension[theOutputIndex][0]; theCount++)
		theFileName[theIndex + theCount - 1] = theExtension[theOutputIndex][theCount];
		
		theFileName[0] = theIndex + theCount - 2;
		NavCustomControl(inCBParams->context, kNavCtlSetEditFileName, &theFileName);
		
		*(SInt16 *)ioCallBackUD = theOutputIndex;
	}
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_NavObjectFilterUPP									
// ---------------------------------------------------------------------------

pascal Boolean
Rzil_NavObjectFilterUPP(AEDesc *theItem, 
					 void *theInfo, 
					 void *ioCallBackUD, 
					 NavFilterModes theFilterMode)
{
#pragma unused(ioCallBackUD, theFilterMode)
	NavFileOrFolderInfo		*myInfo = (NavFileOrFolderInfo *)theInfo;
	
	if (theItem->descriptorType == typeFSS) {
		if (!myInfo->isFolder) {
			OSType myType = myInfo->fileAndFolder.fileInfo.finderInfo.fdType;
			
			// see whether the file type is in the list of file types that our application can open 
			if ((myType == 'TEXT') || (myType == 'PICT'))
				return(true);

			// if we got to here, it's a file we cannot open
			return(false);		
		}
	}
	
	// if we got to here, it's a folder or non-HFS object
	return(true);
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_NewMapHandleEvent									
// ---------------------------------------------------------------------------

void Rzil_NewMapHandleEvent(NavCBRecPtr inCBParams, void * ioCallBackUD)
{
	switch (inCBParams->eventData.eventDataParms.event->what)
	{
		case mouseDown:
		{
			OSErr theErr = noErr;
			Point where = inCBParams->eventData.eventDataParms.event->where;
			short theItem = 0;
			UInt16 firstItem = 0;
			short realItem = 0;
			short partCode = 0;
			ControlHandle theControlH;
			
			GlobalToLocal(&where);
			
			theItem = ::FindDialogItem( ::GetDialogFromWindow(inCBParams->window), where);
			theControlH = ::FindControlUnderMouse(where, inCBParams->window, &partCode);
			
			if (inCBParams->context != 0)
			{
				
				theErr = ::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);
				realItem = theItem - firstItem + 1;

				switch (realItem)
				{
					case DITLitm_NewMapRF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapRF + firstItem, &theControlH);
						::SetControlValue(theControlH, TRUE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapDF + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						*(SInt16 *)ioCallBackUD = fork_rezfork;
					}
					break;
					case DITLitm_NewMapDF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_NewMapDF + firstItem,&theControlH);
						::SetControlValue(theControlH, TRUE);
						*(SInt16 *)ioCallBackUD = fork_datafork;
					}
					break;
				}
			}	
		}
		break;
		
		case updateEvt:
		{
// 			do_update(inCBParams->eventData.eventDataParms.event);
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_OpenMapHandleEvent									
// ---------------------------------------------------------------------------

void Rzil_OpenMapHandleEvent(NavCBRecPtr inCBParams, void * ioCallBackUD)
{
	Rzil_OpenFileUD *	theUserData = (Rzil_OpenFileUD *) ioCallBackUD;

 	switch (inCBParams->eventData.eventDataParms.event->what)
	{
		case mouseDown:
		{
			OSErr theErr = noErr;
			Point where = inCBParams->eventData.eventDataParms.event->where;
			short theItem = 0;
			UInt16 firstItem = 0;
			short realItem = 0;
			short partCode = 0;
			ControlHandle theControlH;
			
			GlobalToLocal(&where);
			
			theItem = ::FindDialogItem( ::GetDialogFromWindow(inCBParams->window), where);
			theControlH = ::FindControlUnderMouse(where, inCBParams->window, &partCode);
			
			if (inCBParams->context != 0)
			{
				
				theErr = ::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);
				realItem = theItem - firstItem + 1;

				switch (realItem)
				{
					case DITLitm_OpenMapAny:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapAny + firstItem, &theControlH);
						::SetControlValue(theControlH, TRUE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapDF + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						theUserData->whichFork = fork_samefork;
					}
					break;
					case DITLitm_OpenMapRF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapAny + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, TRUE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapDF + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						theUserData->whichFork = fork_rezfork;
					}
					break;
					case DITLitm_OpenMapDF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapAny + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapDF + firstItem,&theControlH);
						::SetControlValue(theControlH, TRUE);
						theUserData->whichFork = fork_datafork;
					}
					break;
					case DITLitm_OpenMapRO:
					{
						SInt16 theCurrentValue;
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_OpenMapRO + firstItem,&theControlH);
						theCurrentValue = GetControlValue(theControlH);
						if (theCurrentValue == kControlCheckBoxCheckedValue)
						{
							::SetControlValue(theControlH, kControlCheckBoxUncheckedValue);
							theUserData->isReadOnly = false;
						}
						else if (theCurrentValue == kControlCheckBoxUncheckedValue)
						{
							::SetControlValue(theControlH, kControlCheckBoxCheckedValue);
							theUserData->isReadOnly = true;
						}
					}
					break;
				}
			}	
		}
		break;
		
		case updateEvt:
		{
// 			do_update(inCBParams->eventData.eventDataParms.event);
		}
		break;
	}
}


// ---------------------------------------------------------------------------
//  ¥ Rzil_SaveMapHandleEvent									
// ---------------------------------------------------------------------------

void Rzil_SaveMapHandleEvent(NavCBRecPtr inCBParams, void * ioCallBackUD)
{
	switch (inCBParams->eventData.eventDataParms.event->what)
	{
		case mouseDown:
		{
			OSErr theErr = noErr;
			Point where = inCBParams->eventData.eventDataParms.event->where;
			short theItem = 0;
			UInt16 firstItem = 0;
			short realItem = 0;
			short partCode = 0;
			ControlHandle theControlH;
			
			GlobalToLocal(&where);
			
			theItem = ::FindDialogItem( ::GetDialogFromWindow(inCBParams->window), where);
			theControlH = ::FindControlUnderMouse(where, inCBParams->window, &partCode);
			
			if (inCBParams->context != 0)
			{
				
				theErr = ::NavCustomControl(inCBParams->context, kNavCtlGetFirstControlID, &firstItem);
				realItem = theItem - firstItem + 1;

				switch (realItem)
				{
					case DITLitm_SaveMapSame:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapSame + firstItem, &theControlH);
						::SetControlValue(theControlH, TRUE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapDF + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						*(SInt16 *)ioCallBackUD = fork_samefork;
					}
					break;
					case DITLitm_SaveMapRF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapSame + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, TRUE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapDF + firstItem, &theControlH);
						::SetControlValue(theControlH, FALSE);
						*(SInt16 *)ioCallBackUD = fork_rezfork;
					}
					break;
					case DITLitm_SaveMapDF:
					{
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapSame + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapRF + firstItem,&theControlH);
						::SetControlValue(theControlH, FALSE);
						::GetDialogItemAsControl(::GetDialogFromWindow(inCBParams->window), DITLitm_SaveMapDF + firstItem,&theControlH);
						::SetControlValue(theControlH, TRUE);
						*(SInt16 *)ioCallBackUD = fork_datafork;
					}
					break;
				}
			}	
		}
		break;
		
		case updateEvt:
		{
// 			do_update(inCBParams->eventData.eventDataParms.event);
		}
		break;
	}
}

