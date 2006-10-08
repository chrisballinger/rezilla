// ===========================================================================
// CInspectorWindow.h				
// 
//                       Created: 2003-05-02 07:33:06
//             Last modification: 2006-10-08 08:36:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include <LWindow.h>
#include "UResources.h"

class LStaticText;
class LEditText;
class LCheckBox;
class LPushButton;
class CRezObjItem;
class CRezObj;
class CRezMapTable;

class CInspectorWindow : public LWindow, public LListener {
public:
	enum { class_ID = FOUR_CHAR_CODE('InsW') };

							CInspectorWindow();
							CInspectorWindow( const SWindowInfo &inWindowInfo );
							CInspectorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CInspectorWindow( LStream *inStream );
							~CInspectorWindow();
			
	virtual void	FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );

	void			AttemptClose();
	
	void			DoClose();

	void			InstallValues(CRezObjItem * inRezObjItem);
	
	void			InstallValues(CRezObj * inRezObj);
	
	void			InstallValues();
	
	void			RetrieveValues(SResourceObjInfoPtr inRezInfoPtr);
	
	void			ClearValues();

	void			SetValueForAttribute(short inFlag, Boolean inState);
	
	void			UpdateIfNecessary(CRezObj * inRezObj);
	void			ClearIfNecessary(CRezObj * inRezObj);

	// Apple events
	virtual void	MakeSelfSpecifier(
								AEDesc&			inSuperSpecifier,
								AEDesc&			outSelfSpecifier) const;

	virtual void	GetAEProperty(
								DescType		inProperty,
								const AEDesc&	inRequestedType,
								AEDesc&			outPropertyDesc) const;

	void			SetAEProperty(
								DescType		inProperty,
								const AEDesc&	inValue,
								AEDesc&			outAEReply);
	
	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual void	HandleAppleEvent(
								const AppleEvent&	inAppleEvent,
								AppleEvent&			outAEReply,
								AEDesc&				outResult,
								SInt32				inAENumber);

	SResourceObjInfoPtr		GetSavedInfo() { return &mSavedInfo;}
	void					SetSavedInfo(SResourceObjInfoPtr inRezInfoPtr);

	CRezMapTable*		GetOwnerTable() { return mOwnerTable;}
	void				SetOwnerTable(CRezMapTable* inOwnerTable) {mOwnerTable = inOwnerTable;}

protected:
	SResourceObjInfo	mSavedInfo;
	CRezMapTable *		mOwnerTable;
	LStaticText *		mTypeField;
	LStaticText *		mSizeField;
	LEditText *			mIDField;
	LEditText *			mNameField;
	LCheckBox *			mSysHeapItem;
	LCheckBox *			mPurgeableItem;
	LCheckBox *			mLockedItem;
	LCheckBox *			mProtectedItem;
	LCheckBox *			mPreloadItem;
	LPushButton *		mRevertButton;
	LPushButton *		mModifyButton;
	
	virtual void		FinishCreateSelf();
	virtual void		ShowSelf();

	virtual LModelObject*	GetModelProperty(DescType inProperty) const;

private:
	void				InitializeRezInfo();
	OSErr				UpdateRezMapTable();
	
	void				GetAEAttribute(
							   DescType	inProperty,
							   AEDesc&		outPropertyDesc) const;
	void				SetAEAttribute(
							   const AEDesc& inValue, 
							   short inFlag);
	
};


