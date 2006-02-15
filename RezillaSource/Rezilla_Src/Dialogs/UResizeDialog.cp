// ===========================================================================
// UResizeDialog.cp
//                       Created: 2004-12-11 18:57:29
//             Last modification: 2005-06-03 06:17:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================


#include "CThreeButtonsBox.h"
#include "UDialogBoxHandler.h"
#include "UResizeDialog.h"
#include "UModalDialogs.h"
#include "UIconMisc.h"
#include "UMessageDialogs.h"

#include <stdio.h>


// ---------------------------------------------------------------------------
// 	DoResizeDialog
// ---------------------------------------------------------------------------

Boolean 
UResizeDialog::DoResizeDialog(	SInt32 inWidth, SInt32 inMinWidth, SInt32 inMaxWidth,
								SInt32 inHeight, SInt32 inMinHeight, SInt32 inMaxHeight,
								SInt32 *outWidth, SInt32 *outHeight )
{
	// Ensure that the window is created properly (Window Manager bug)
	StGWorldSaver		aSaver;
	::SetGDevice( ::GetMainDevice() );
	
	// Create the dialog
	StDialogBoxHandler		theHandler( PPob_ImageResizeDialog, LCommander::GetTopCommander() );
	CThreeButtonsBox *		theWindow = theHandler.GetDialog();
	LEditField *			widthField =  (LEditField*) theWindow->FindPaneByID( item_WidthField );
	LEditField *			heightField = (LEditField*) theWindow->FindPaneByID( item_HeightField );
	
	ThrowIf_( !widthField || !heightField );
	
	// Initialize the values & show the window
	widthField->SetValue( inWidth );
	heightField->SetValue( inHeight );
	theWindow->Show();
	
	// Go into an event loop
	Boolean 	done = false;
	MessageT	theMessage;
	SInt32		newWidth, newHeight;
	
	while( !done )
	{
		theMessage = theHandler.DoDialog();
		
		if ( theMessage == msg_Cancel )
			done = true;
		else if ( theMessage == msg_OK )
		{
			newWidth = widthField->GetValue();
			newHeight = heightField->GetValue();
			
			if ( (newWidth < inMinWidth) || (newWidth > inMaxWidth) )
			{
				theWindow->SwitchTarget( widthField );
				widthField->SelectAll();
				ShowResizeError( inMinWidth, inMaxWidth, inMinHeight, inMaxHeight );
			}
			else if ( (newHeight < inMinHeight) || (newHeight > inMaxHeight) )
			{
				theWindow->SwitchTarget( heightField );
				heightField->SelectAll();
				ShowResizeError( inMinWidth, inMaxWidth, inMinHeight, inMaxHeight );
			}
			else
				done = true;
		}
	};
	
	// Return values to the caller
	if ( theMessage == msg_OK )
	{
		*outWidth = newWidth;
		*outHeight = newHeight;
		return( true );
	}
	else
		return( false );
}


// ---------------------------------------------------------------------------
// 	ShowResizeError
// ---------------------------------------------------------------------------
// 	Doesn't deal with case where width & height don't match, but they do
// 	for all of the image types we handle. 

void 
UResizeDialog::ShowResizeError( SInt32 inMinWidth, SInt32 inMaxWidth,
								SInt32 /*inMinHeight*/, SInt32 /*inMaxHeight*/ )
{
	CFStringRef formatStr = NULL, messageStr = NULL;
	
	formatStr = CFCopyLocalizedString(CFSTR("ErrorResizingImage"), NULL);
	if (formatStr != NULL) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, inMinWidth, inMaxWidth);
		if (messageStr != NULL) {
			UMessageDialogs::SimpleMessageFromCFString(messageStr, PPob_SimpleMessage);
			CFRelease(messageStr);                     
		}
		CFRelease(formatStr);                             
	}		  	
}



