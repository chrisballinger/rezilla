// =================================================================================
// CWindowMenu.h					
// 
// © 2002, Bernard Desgraupes, All rights reserved.
//                       Created : 2002-04-19 13:40:15
//             Last modification : 2002-04-19 13:40:19
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
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
