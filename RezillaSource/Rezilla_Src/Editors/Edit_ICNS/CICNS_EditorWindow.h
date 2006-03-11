// ===========================================================================
// CICNS_EditorWindow.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-10 12:32:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CIcon_EditorWindow.h"
#include "UResources.h"

// #include <LDragAndDrop.h>


class LView;
class LHandleStream;
class CICNS_Family;
class CICNS_Member;
class LStaticText;
class LPopupButton;


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
	Handle			CollectResourceData();
	
	virtual void	InitializeFromResource( CRezMap *inMap, ResIDT );
	virtual void	SaveAsResource( CRezMap *, ResIDT );

	SInt32			GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
		
	virtual void	RevertContents();
	
	LView*			GetContentsView() const { return mContentsView;}
	
	TArray<OSType> *	GetIconTypes() { return &mIconTypes;}
	
	ArrayIndexT		GetCurrentIndex() { return mCurrentIndex;}
	void			SetCurrentIndex(ArrayIndexT inIconIndex) {mCurrentIndex = inIconIndex;}
	void			AdjustCurrentIndex();

protected:
	LHandleStream *			mOutStream;
	LView *					mContentsView;
	LStaticText *			mTypeField;
	LStaticText *			mSizeField;
	LPopupButton *			mIconPopup;
	CICNS_Family *			mIcnsFamily;
	UInt16					mDropIndex;
	ArrayIndexT				mCurrentIndex;
	TArray<OSType>			mIconTypes;

	virtual void	FinishCreateSelf();
	
	
private:	
	Boolean			SelectIconAtIndex(ArrayIndexT inMenuIndex);
	void			DeleteIconAtIndex(ArrayIndexT inMenuIndex);
	void			InstallIcon(ArrayIndexT inMenuIndex, CICNS_Member * inMember);
	CICNS_Member *	CreateIcon(ArrayIndexT inMenuIndex, OSType inType);
	
	void			AppendTypeToMenu(Str255 inString);
	void			FillPopup();
	void			UpdatePopupStyle();
	void			UpdateInfoFields(OSType inType, SInt32 inSize);
	
};


