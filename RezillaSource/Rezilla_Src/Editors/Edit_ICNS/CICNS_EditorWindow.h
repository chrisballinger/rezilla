// ===========================================================================
// CICNS_EditorWindow.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-27 07:28:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LDragAndDrop.h>


class LView;
class CICNS_Stream;
class CICNS_Family;
class CICNS_Member;
class LStaticText;
class LPopupButton;


class CICNS_EditorWindow :	public CEditorWindow, 
							public LDragAndDrop {
public:
	enum { class_ID = FOUR_CHAR_CODE('ICSW') };

							CICNS_EditorWindow();
							CICNS_EditorWindow( LStream *inStream );
							~CICNS_EditorWindow();

	virtual void	Click( SMouseDownEvent &inMouseDown );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	OSErr			InstallResourceData(Handle inHandle);
	Handle			CollectResourceData();
	
	virtual void	RevertContents();
	
	LView*			GetContentsView() const { return mContentsView;}
	
	TArray<OSType> *	GetIconTypes() { return &mIconTypes;}
	
	ArrayIndexT		GetCurrentIndex() { return mCurrentIndex;}
	void			SetCurrentIndex(ArrayIndexT inIconIndex) {mCurrentIndex = inIconIndex;}
	void			AdjustCurrentIndex();

protected:
	CICNS_Stream *			mOutStream;
	LView *					mContentsView;
	LStaticText *			mTypeField;
	LStaticText *			mSizeField;
	LPopupButton *			mIconPopup;
	CICNS_Family *			mIcnsFamily;
	UInt16					mDropIndex;
	ArrayIndexT				mCurrentIndex;
	TArray<OSType>			mIconTypes;

	virtual void	FinishCreateSelf();

	virtual Boolean	ItemIsAcceptable( DragReference inDragRef,
							ItemReference inItemRef );
	virtual void	ReceiveDragItem( DragReference inDragRef,
							DragAttributes inDragAttrs, ItemReference inItemRef,
							Rect &inItemBounds );
	virtual void	EnterDropArea( DragReference inDragRef, Boolean inDragHasLeftSender );
	virtual void	LeaveDropArea( DragReference inDragRef );
	virtual void	InsideDropArea( DragReference inDragRef);
	virtual void	HiliteDropArea( DragReference inDragRef );


	
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


