// ===========================================================================
// CInspectorWindow.h				
// 
//                       Created: 2003-05-02 07:33:06
//             Last modification: 2003-05-02 17:24:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>
#include "UResources.h"

class LStaticText;
class LEditText;
class CRezIconPane;
class LCheckBox;
class LPushButton;
class CRezObjItem;

class CInspectorWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'InsW' };

							CInspectorWindow();
							CInspectorWindow( const SWindowInfo &inWindowInfo );
							CInspectorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CInspectorWindow( LStream *inStream );
							~CInspectorWindow();
			
	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	void			AttemptClose();
	void			DoClose();

	void			InstallValues(SResourceObjInfoPtr inRezInfoPtr);
	void			InstallValues(CRezObjItem * inRezObjItem);
	void			InstallValues();
	void			ClearValues();

	SResourceObjInfoPtr		GetSavedRezInfo() { return &mSavedRezInfo;}
	void					SetSavedRezInfo(SResourceObjInfoPtr inRezInfoPtr);

	virtual CRezObjItem*	GetRezObjItem() { return mRezObjItem;}
	void					SetRezObjItem(CRezObjItem* inRezObjItem) {mRezObjItem = inRezObjItem;}

protected:
	SResourceObjInfo	mSavedRezInfo;
	CRezObjItem *		mRezObjItem;
	LStaticText *		mTypeItem;
	LStaticText *		mIDItem;
	LStaticText *		mSizeItem;
// 	LStaticText *		mMapItem;
	LEditText *			mIDEdit;
	LEditText *			mNameEdit;
	CRezIconPane *		mIconItem;
	LCheckBox *			mSysHeapItem;
	LCheckBox *			mPurgeableItem;
	LCheckBox *			mLockedItem;
	LCheckBox *			mProtectedItem;
	LCheckBox *			mPreloadItem;
	LCheckBox *			mCompressedItem;
	LPushButton *		mRevertButton;
	LPushButton *		mModifyButton;
	
	
	virtual void		FinishCreateSelf();
	virtual void		ShowSelf();
	void				RetrieveValues(SResourceObjInfo & outRezInfo);
	void				RetrieveValues();

private:
	void				InitializeRezInfo();
	void				UpdateRezObj();
	
};


