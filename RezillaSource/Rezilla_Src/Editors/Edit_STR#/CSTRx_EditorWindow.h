// ===========================================================================
// CSTRx_EditorWindow.h
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2006-09-18 19:53:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LDragAndDrop.h>

class CIndexedEditField;
class LEditText;
class LStaticText;
class LHandleStream;
/* class LTabGroupView; */


class CSTRx_EditorWindow :	public CEditorWindow, 
							public LDragAndDrop {
public:
	enum { class_ID = FOUR_CHAR_CODE('STRW') };

							CSTRx_EditorWindow();
							CSTRx_EditorWindow( const SWindowInfo &inWindowInfo );
							CSTRx_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CSTRx_EditorWindow( LStream *inStream );
							~CSTRx_EditorWindow();

	virtual void	Click( SMouseDownEvent &inMouseDown );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual Boolean	HandleKeyPress( const EventRecord& inKeyEvent );
	
	OSErr			InstallResourceData(Handle inHandle);
	Handle			CollectResourceData();
	
	virtual void	RevertContents();

	UInt16			GetFirstSelected();
	
	LView*			GetContentsView() const { return mContentsView;}
	
	static SPaneInfo 			sPaneInfo;
	static SViewInfo			sViewInfo;

protected:
	LHandleStream *				mOutStream;
	LView *						mContentsView;
	TArray<CIndexedEditField*>	mIndexedFields;
	UInt16						mDropIndex;

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

	void			GetIndexFromPoint(
							  const Point	&inPortPoint,
							  UInt16		&outItemIndex,
							  UInt16		&outDropRow );
	
	void			DrawDividingLine( UInt16 inRow );

private:	
	void			AddStringItem(Str255 inString);
	void			InsertStringItemAtIndex(UInt16 index, Str255 inString);
	void			CreateItemAtIndex(UInt16 index, Str255 inString, SInt32 inHowMany);
	
	UInt16			DeleteSelectedItems();
	
	void			RecalcPositionsInRange(UInt16 inStart, UInt16 inEnd);
	void			RecalcPositionAtIndex(UInt16 index);
	void			RecalcAllPositions();
};


