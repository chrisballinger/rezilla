// =================================================================================
// CWindowMenu.h					
// 
//                       Created: 2002-04-19 13:40:15
//             Last modification: 2006-11-17 23:49:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2002-2006
// All rights reserved.
// ===========================================================================
// Adapted from PowerPlant's Book Code (chap. 15)


#pragma once

#include <LMenu.h>
#include <LArray.h>
#include <PP_Types.h>

class LWindow;

class CWindowMenu : public LMenu {
public:
					CWindowMenu();
					CWindowMenu( ResIDT inMenuID );
					CWindowMenu( SInt16 inMenuID, Str255 inTitle );
					~CWindowMenu();
	
	void			InsertWindow( const LWindow *inWindow );
	void			RemoveWindow( const LWindow *inWindow );

	LWindow *		MenuItemToWindow( SInt16 inMenuItem );
	SInt16			WindowToMenuItem( const LWindow *inWindow );
	void			SetCommandKeys();
	SInt16			GetBaseItems() { return mBaseItems;}
	void			SetBaseItems(SInt16 theBaseItems) {mBaseItems = theBaseItems ;}
	void			ForceMarkWindow(LWindow * inWindow);

protected:
	SInt16			mBaseItems;
	LArray			mWindowList;
};


// =================================================================================
//	CWindowMenuAttachment
// =================================================================================

#include <LAttachment.h>

class CWindowMenuAttachment : public LAttachment {
public:
					CWindowMenuAttachment( CWindowMenu *inWindowMenu );
					~CWindowMenuAttachment();
	
protected:
	CWindowMenu *	mWindowMenu;

	void			ExecuteSelf( MessageT inMessage, void *ioParam );
};
