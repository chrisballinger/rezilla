// ===========================================================================
// UFontSizeDialog.cp
//                       Created: 2004-12-11 18:57:26
//             Last modification: 2004-12-24 00:01:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UModalDialogs.h"
#include "UFontSizeDialog.h"
#include "UIconMisc.h"
#include "UMessageDialogs.h"


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
		StDialogHandler			theHandler( rPPob_FontSizeDialog, LCommander::GetTopCommander() );
		LWindow	*				theWindow = theHandler.GetDialog();
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