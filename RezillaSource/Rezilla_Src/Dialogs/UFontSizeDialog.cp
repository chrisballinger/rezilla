// ===========================================================================
// UFontSizeDialog.cp
//                       Created: 2004-12-11 18:57:26
//             Last modification: 2005-03-09 07:11:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004, 2005
// All rights reserved.
// ===========================================================================

#include "CThreeButtonsBox.h"
#include "UModalDialogs.h"
#include "UFontSizeDialog.h"
#include "UIconMisc.h"
#include "UMessageDialogs.h"
#include "UDialogBoxHandler.h"


// ---------------------------------------------------------------------------
// 	DoSizeDialog
// ---------------------------------------------------------------------------

Boolean 
UFontSizeDialog::DoSizeDialog( SInt16 inSize, SInt16 *outSize )
{
	try
	{
		// Ensure that the window is created properly (Window Manager bug)
		StGWorldSaver		aSaver;
		::SetGDevice( ::GetMainDevice() );
		
		// Create the dialog
		StDialogBoxHandler		theHandler( PPob_FontSizeDialog, LCommander::GetTopCommander() );
		CThreeButtonsBox	*	theWindow = theHandler.GetDialog();
		LEditField *			sizeField =  (LEditField*) theWindow->FindPaneByID( item_SizeField );
		ThrowIfNil_( sizeField );
		
		// Initialize the values & show the window
		sizeField->SetValue( inSize );
		theWindow->Show();
		
		// Go into an event loop
		Boolean 	done = false;
		MessageT	theMessage;
		SInt16		newSize;
		
		while( !done )
		{
			theMessage = theHandler.DoDialog();
			
			if ( theMessage == msg_Cancel )
				done = true;
			else if ( theMessage == msg_OK )
			{
				newSize = sizeField->GetValue();

				if ( (newSize <= 4) || (newSize >= 512) )
				{
					theWindow->SwitchTarget( sizeField );
					sizeField->SelectAll();
					UMessageDialogs::AlertWithValue(CFSTR("BadFontSize"), newSize);
				}
				else
					done = true;
			}
		};
		
		// Return values to the caller
		if ( theMessage == msg_OK )
		{
			*outSize = newSize;
			return( true );
		}
		else
			return( false );
	}
	catch( ... )
	{
		UMessageDialogs::AlertWithValue(CFSTR("ErrorSettingSize"), err_IconGeneric);
		return( false );	
	}
}