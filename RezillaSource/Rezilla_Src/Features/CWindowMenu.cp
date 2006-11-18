// ===========================================================================
// CWindowMenu.cp					
// 
//                       Created: 2002-04-19 13:40:15
//             Last modification: 2002-04-19 13:40:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2002
// ===========================================================================
// Adapted from PowerPlant's Book Code (chap. 15)

#include <LCommander.h>
#include <LWindow.h>
#include <PP_Messages.h>
#include <UDesktop.h>

#include "CWindowMenu.h"

// ---------------------------------------------------------------------------------
//   CWindowMenu
// ---------------------------------------------------------------------------------

CWindowMenu::CWindowMenu()
	: mBaseItems( 0 )
{
}


// ---------------------------------------------------------------------------------
//   CWindowMenu
// ---------------------------------------------------------------------------------

CWindowMenu::CWindowMenu(
	ResIDT	inMenuID )
		: LMenu( inMenuID ), mBaseItems( 0 )
{
}


// ---------------------------------------------------------------------------------
//   CWindowMenu
// ---------------------------------------------------------------------------------

CWindowMenu::CWindowMenu(
	SInt16	inMenuID,
	Str255	inTitle )
		: LMenu( inMenuID, inTitle ), mBaseItems( 0 )
{
}


// ---------------------------------------------------------------------------------
//     ~CWindowMenu
// ---------------------------------------------------------------------------------

CWindowMenu::~CWindowMenu()
{
}


// ---------------------------------------------------------------------------------
//   InsertWindow
// ---------------------------------------------------------------------------------

void
CWindowMenu::InsertWindow(
	const LWindow	*inWindow )
{
	// If window is not in list already.
	if ( mWindowList.FetchIndexOf( &inWindow ) == LArray::index_Bad ) {
	
		// If this is the first window in the list.
		if ( mWindowList.GetCount() == 0 ) {
		
			// Get the base item count.
			mBaseItems = ::CountMenuItems( GetMacMenuH() );
			
			if ( mBaseItems > 0 ) {
	
				// Add a separator and increment the number of base items.
				InsertCommand( "\p(-", cmd_Nothing, mBaseItems );
				mBaseItems++;
			
			}
		
		}
		
		// Add the window to the list.
		mWindowList.InsertItemsAt( 1, LArray::index_Last, &inWindow );
		
		// Get the window title.
		Str255	theTitle;
		inWindow->GetDescriptor( theTitle );
		
		// Insert the window title into the menu as a synthetic item.
		// First, insert a blank item, since InsertCommand uses
		// the toolbox InsertMenuItem which interprets metacharacters,
		// then set the item text manually.
		InsertCommand( "\p ", cmd_UseMenuItem, 16000 );
		::SetMenuItemText( GetMacMenuH(), ::CountMenuItems( GetMacMenuH() ), theTitle );

		// Renumber the command keys.
		SetCommandKeys();
	
	} else {

		// Get the window title.
		Str255	theTitle;
		inWindow->GetDescriptor( theTitle );
	
		// Change the menu item text.
		Assert_( mWindowList.FetchIndexOf( &inWindow ) != LArray::index_Bad );
		::SetMenuItemText( GetMacMenuH(), WindowToMenuItem( inWindow ), theTitle );
	
	}
}


// ---------------------------------------------------------------------------------
//   RemoveWindow
// ---------------------------------------------------------------------------------

void
CWindowMenu::RemoveWindow(
	const LWindow	*inWindow )
{
	// Remove the item from the menu.
	Assert_( mWindowList.FetchIndexOf( &inWindow ) != LArray::index_Bad );
	RemoveItem( mWindowList.FetchIndexOf( &inWindow ) + mBaseItems );

	// Remove the window from the list.
	mWindowList.Remove( &inWindow );

	if ( mWindowList.GetCount() == 0 && mBaseItems > 1 ) {
	
		// Remove the separator and decrement the number of base items.
		RemoveItem( mBaseItems );
		mBaseItems--;
		Assert_( ::CountMenuItems( GetMacMenuH() ) == mBaseItems );

	}

	// Renumber the command keys.
	SetCommandKeys();
}



// ---------------------------------------------------------------------------------
//   MenuItemToWindow
// ---------------------------------------------------------------------------------

LWindow *
CWindowMenu::MenuItemToWindow(
	SInt16	inMenuItem )
{
	LWindow	*theWindow = nil;

	// Get the window from the list.
	mWindowList.FetchItemAt( inMenuItem - mBaseItems, &theWindow );
	
	return theWindow;
}


// ---------------------------------------------------------------------------------
//   WindowToMenuItem
// ---------------------------------------------------------------------------------

SInt16
CWindowMenu::WindowToMenuItem(
	const LWindow	*inWindow )
{
	SInt16		theItem;
	ArrayIndexT	theIndex;
	
	// Get the window index in the list.
	theIndex = mWindowList.FetchIndexOf( &inWindow );
	
	if ( theIndex != LArray::index_Bad ) {
		// Calculate the menu item number.
		theItem = mBaseItems + theIndex;
		Assert_( theItem <= ::CountMenuItems( GetMacMenuH() ) );
	}

	return theItem;
}


// ---------------------------------------------------------------------------------
//   SetCommandKeys
// ---------------------------------------------------------------------------------

void
CWindowMenu::SetCommandKeys()
{
	SInt16	theItem = mBaseItems + 1;
	SInt16	theItemCount = ::CountMenuItems( GetMacMenuH() );
	SInt16	theCommand = '1';

	while ( theItem <= theItemCount && theCommand <= '9' ) {
		// Set the menu item command key.
		::SetItemCmd( GetMacMenuH(), theItem, theCommand );		
		// Increment the menu item index and command number.
		++theItem;
		++theCommand;
	}
}


// ---------------------------------------------------------------------------------
//   ForceMarkWindow
// ---------------------------------------------------------------------------------

void
CWindowMenu::ForceMarkWindow(LWindow * inWindow)
{
	MenuRef		theMenuRef = this->GetMacMenuH();
	SInt16		theItemCount = ::CountMenuItems(theMenuRef);
	SInt16		theItem = 1;
	
	while ( theItem <= theItemCount ) {
		::MacCheckMenuItem(theMenuRef, theItem, 0);
		++theItem;
	}
	theItem = WindowToMenuItem(inWindow);		 
	::MacCheckMenuItem(theMenuRef , theItem, 1);
}


// =================================================================================
//	CWindowMenuAttachment
// =================================================================================

// ---------------------------------------------------------------------------------
//   CWindowMenuAttachment
// ---------------------------------------------------------------------------------

CWindowMenuAttachment::CWindowMenuAttachment(
	CWindowMenu	*inWindowMenu )
		: LAttachment( msg_AnyMessage, true ), mWindowMenu( inWindowMenu )
{
}


// ---------------------------------------------------------------------------------
//     ~CWindowMenuAttachment
// ---------------------------------------------------------------------------------

CWindowMenuAttachment::~CWindowMenuAttachment()
{
}


// ---------------------------------------------------------------------------------
//   ExecuteSelf
// ---------------------------------------------------------------------------------

void
CWindowMenuAttachment::ExecuteSelf(
	MessageT	inMessage,
	void		*ioParam )
{
	// Turn on host execution by default.
	mExecuteHost = true;

	if ( inMessage == msg_CommandStatus ) {

		// Handle commander status just like in FindCommandStatus
		ResIDT			theMenuID;
		SInt16			theMenuItem;
		SCommandStatus	*theStatus = static_cast<SCommandStatus *> (ioParam);

		if ( LCommander::IsSyntheticCommand( theStatus->command, theMenuID,
			theMenuItem ) && theMenuID == mWindowMenu->GetMenuID() ) {
			
			// Find the window corresponding to the menu item.
			LWindow	*theWindow = mWindowMenu->MenuItemToWindow( theMenuItem );
			
			if ( theWindow != nil ) {
				// Since the item corresponds to an entry in the window menu
				// we'll handle it's status here. Note: there may be other
				// items at the top of window menu that are the responsibility
				// of some commander.
				mExecuteHost = false;
			
				// All window menu items should be enabled and use a mark.
				*theStatus->enabled = true;
				*theStatus->usesMark = true;
				*theStatus->mark = noMark;

				if ( theWindow == UDesktop::FetchTopRegular() ) {
					// Check the menu item since it
					// represents the top regular window.
					*theStatus->mark = checkMark;
				}
			}
		}
	} else {
		// Handle commands similar to ObeyCommand
		ResIDT	theMenuID;
		SInt16	theMenuItem;

		if ( LCommander::IsSyntheticCommand( inMessage, theMenuID,
			theMenuItem ) && theMenuID == mWindowMenu->GetMenuID() ) {

			// Find the window selected.
			LWindow	*theWindow = mWindowMenu->MenuItemToWindow( theMenuItem );
			
			if ( theWindow != nil ) {
				// Since the item corresponds to an entry in the window menu
				// we'll handle the command here. Note: there may be other
				// items at the top of the window menu that are the
				// responsibility of a commander.
				mExecuteHost = false;

				if ( theWindow->IsVisible() ) {
					// Bring the window to the front.
					UDesktop::SelectDeskWindow( theWindow );
				}
			}
		}
	}
}
