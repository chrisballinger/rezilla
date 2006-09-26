// ===========================================================================
// CRecentItemsMenu.h					
//                       Created: 2004-03-02 13:18:30
//             Last modification: 2006-09-26 06:15:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================


#ifndef CRECENTITEMSMENU_H
#define CRECENTITEMSMENU_H


#include <LAttachment.h>
#include <TArray.h>

class	CAlias;

class CRecentItemsMenu : public LAttachment {
	public:
		
					CRecentItemsMenu(ResIDT inMenuID, 
									 UInt32 inMaxRecentItems, 
									 CFStringRef inApplicationID);
		
					virtual	~CRecentItemsMenu();
		
		virtual void 	ExecuteSelf( MessageT inMessage, void *ioParam );
		
		OSErr	AddFile(AliasHandle inAliasHandle, Boolean inRebuild);
		void	AddFile(FSSpec& inFSSpec, Boolean inRebuild);
		
		void	RemoveFile(AliasHandle inAliasHandle);	
		void	RemoveFile(FSSpec& inFSSpec);	
		
		OSErr		GetSelectedItem(UInt16 inMenuItem, FSSpec& outFSSpec);
		virtual void	OpenSelectedItem(FSSpec& inFSSpec);
		
		void	Reset();
		
		UInt32	CountItems();

		virtual void 	StoreInPreferences();
		virtual void 	RetrieveFromPreferences();
		
		virtual UInt32	GetMaxRecentItems() { return mMaxRecentItems;}
		void 			SetMaxRecentItems(UInt32 inMaxRecentItems);

	protected:
		
		ResIDT				mMenuID;
		MenuHandle			mMenuHandle;
		CFStringRef			mAppIdentifier;
		UInt32				mMaxRecentItems;		
		TArray<CAlias*>		mAliasArray;
		
		virtual void 	RebuildMenu();
		void 			DeleteAllItems();
};


#endif