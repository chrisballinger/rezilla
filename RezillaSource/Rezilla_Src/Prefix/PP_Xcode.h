// ===========================================================================
// PP_Xcode.h
// 
//                       Created: 2005-09-11 21:56:40
//             Last modification: 2005-09-12 09:01:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================
// Use as a prefix file to make a precompile header in order to compile
// PowerPlant with XCode. This also includes <Carbon/Carbon.h>.
// In the target's settings, define:
//     GCC_PREFIX_HEADER = Rezilla_Src/Prefix/PP_Xcode.h
//     GCC_PRECOMPILE_PREFIX_HEADER = YES
// 	
// 	Also set this target's setting:
// 		Compile sources as:  C++
// 		(instead of "according to file suffix")
	

#define _STD std
#define _CSTD std
#define __dest_os __mac_os_x
	
#define PP_Target_Carbon 1

#define PP_Target_Classic (!PP_Target_Carbon)

#define TARGET_API_MAC_CARBON PP_Target_Carbon
#define TARGET_API_MAC_OS8 PP_Target_Classic
#define TARGET_API_MAC_OSX PP_Target_Carbon


// (bd 2005-09-11) See in 
// "/Volumes/im2/CodeWarrior_9.0/CodeWarrior/MSL/MSL_C++/MSL_Common/Include/mslconfig"
#define _MSL_LITTLE_ENDIAN 0

// ------------------------------------------------------------------
//  Options

#define PP_Uses_PowerPlant_Namespace 0
#define PP_Supports_Pascal_Strings 1
#define PP_StdDialogs_Option PP_StdDialogs_NavServicesOnly

#define PP_Uses_Old_Integer_Types 0
#define PP_Obsolete_AllowTargetSwitch 0
#define PP_Obsolete_ThrowExceptionCode 0
#define PP_Warn_Obsolete_Classes 1

#define PP_Suppress_Notes_222	1

//
// Carbon headers
#include <Carbon/Carbon.h>
//
// PowerPlantheaders
	// Action Classes
#include <LAction.h>
#include <LUndoer.h>
#include <UTETextAction.h>
#include <UTEViewTextAction.h>
	// AppleEvent Classes
#include <LModelDirector.h>
#include <LModelObject.h>
#include <LModelProperty.h>
#include <UAppleEventsMgr.h>
#include <UExtractFromAEDesc.h>
	// Array Classes
#include <LArray.h>
#include <LArrayIterator.h>
#include <LComparator.h>
#include <LRunArray.h>
#include <LVariableArray.h>
#include <TArray.h>
#include <TArrayIterator.h>
	// Commander Classes
#include <LApplication.h>
#include <LCommander.h>
#include <LDocApplication.h>
#include <LDocument.h>
#include <LSingleDoc.h>
	// Feature Classes
#include <LAttachable.h>
#include <LAttachment.h>
#include <LBroadcaster.h>
#include <LDragAndDrop.h>
#include <LDragTask.h>
#include <LEventDispatcher.h>
#include <LListener.h>
#include <LPeriodical.h>
#include <LSharable.h>
	// File & Stream Classes
#include <LDataStream.h>
#include <LFile.h>
#include <LFileStream.h>
#include <LHandleStream.h>
#include <LStream.h>
	// Pane Classes
#include <LButton.h>
#include <LCaption.h>
#include <LCicnButton.h>
#include <LControl.h>
#include <LDialogBox.h>
#include <LEditField.h>
#include <LFocusBox.h>
#include <LGrafPortView.h>
#include <LListBox.h>
#include <LOffscreenView.h>
#include <LPane.h>
#include <LPicture.h>
#include <LPlaceHolder.h>
#include <LPrintout.h>
#include <LRadioGroupView.h>
#include <LScroller.h>
#include <LStdControl.h>
#include <LTabGroupView.h>
#include <LTableView.h>
#include <LTextEditView.h>
#include <LView.h>
#include <LWindow.h>
#include <UGWorld.h>
#include <UQuickTime.h>
	// PowerPlant Headers
#include <PP_Constants.h>
#include <PP_KeyCodes.h>
#include <PP_Macros.h>
#include <PP_Messages.h>
#include <PP_Prefix.h>
#include <PP_Resources.h>
#include <PP_Types.h>
									// Support Classes
#include <LClipboard.h>
#include <LFileTypeList.h>
#include <LGrowZone.h>
#include <LMenu.h>
#include <LMenuBar.h>
#include <LRadioGroup.h>
#include <LString.h>
#include <LTabGroup.h>
#include <UDesktop.h>
									// Utility Classes
#include <UAttachments.h>
#include <UCursor.h>
#include <UDebugging.h>
#include <UDrawingState.h>
#include <UDrawingUtils.h>
#include <UEnvironment.h>
#include <UException.h>
#include <UKeyFilters.h>
#include <UMemoryMgr.h>
#include <UModalDialogs.h>
#include <UPrinting.h>
#include <UReanimator.h>
#include <URegions.h>
#include <URegistrar.h>
#include <UScrap.h>
#include <UScreenPort.h>
#include <UTextEdit.h>
#include <UTextTraits.h>
#include <UWindows.h>