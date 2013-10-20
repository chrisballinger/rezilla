// ===========================================================================
// CICNS_EditorWindow.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-11-10 07:39:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CIcon_EditorWindow.h"
#include "CWindow_IconFamily.h"
#include "UResources.h"


class CIcon_EditorView;
class CICNS_Family;
class CICNS_Member;
class CDraggableTargetView;
class LHandleStream;
class LStaticText;
class LPopupButton;
class LPushButton;


class CICNS_EditorWindow :	public CIcon_EditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('ICSW') };

							CICNS_EditorWindow( LStream *inStream );
							~CICNS_EditorWindow();

	static CICNS_EditorWindow *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT );
	static CICNS_EditorWindow *	CreateFromStream( LStream *inStream );
							
	virtual void	Click( SMouseDownEvent &inMouseDown );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	OSErr			InstallResourceData(Handle inHandle);
	OSErr			CollectResourceData(IconFamilyHandle & outIconFamilyH);
	void			FinishInstallData();
	
	virtual void	SaveAsResource( CRezMap *, ResIDT );

	SInt32			GetFamilyMemberCount();
	void			GetFamilyMemberInfo( OSType inType, Rez_IconMemberInfo *oRec );

	SInt32			GetZoomFactor( SInt32 inImageWidth, SInt32 inImageHeight, Boolean *outShowGrid );
		
	virtual void	RevertContents();
	
	CICNS_Member *	GetCurrentMember();
	
	TArray<OSType> *	GetIconTypes() { return &mIconTypes;}
	
	ArrayIndexT		GetCurrentIndex() { return mCurrentIndex;}
	void			SetCurrentIndex(ArrayIndexT inIconIndex) {mCurrentIndex = inIconIndex;}
	void			AdjustCurrentIndex();

	virtual void	SetDirty(Boolean inDirty);

	OSErr			ImportData(Handle inHandle);

	CICNS_Family*	GetIcnsFamily() { return mIcnsFamily;}

protected:
	Rez_IconFamilyInfoH		mFamilyInfoH;
	CDraggableTargetView *	mIconSample;
	CDraggableTargetView *	mMaskSample;
	LStaticText *			mTypeField;
	LPopupButton *			mIconPopup;
	LPushButton *			mRemoveButton;
	CICNS_Family *			mIcnsFamily;
	ArrayIndexT				mCurrentIndex;
	TArray<OSType>			mIconTypes;

	virtual void	FinishCreateSelf();
		
	void			EndianConvertIconFamilyInfoHandle();
	
private:	
	Boolean			ShowIconAtIndex(ArrayIndexT inMenuIndex);
	Boolean			ShowIconForType(OSType inType);
	void			ResizeWindowIfNecessary(OSType inType);
	void			ResizeSamplesIfNecessary(SInt16 inWidth, SInt16 inHeight, Boolean hasMask);
	
	void			DeleteIconAtIndex(ArrayIndexT inMenuIndex, Boolean askYesNo = true);
	void			InstallMemberIcon(CICNS_Member * inMember);
	void			StoreMemberIcon(CICNS_Member * inMember);
	CICNS_Member *	CreateNewMember(OSType inType);
	
	void			AppendTypeToPopup(Str255 inString);
	void			FillPopup();
	void			UpdatePopup();
	void			UpdateMemberInPopup(CICNS_Member * inMember);
	void			UpdateTypeField(OSType inType);
	void			GetIconMemberParams(OSType inType, SInt32 &inDepth, SInt32 &inWidth, SInt32 &inHeight, 
										SInt32 &inRowBytes, SInt32 &inMaskOffset, SInt32 &inMaskRowBytes);
	ArrayIndexT		GetMenuIndexForType(OSType inType);
	
};


