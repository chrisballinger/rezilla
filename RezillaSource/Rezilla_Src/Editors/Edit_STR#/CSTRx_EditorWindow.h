// ===========================================================================
// CSTRx_EditorWindow.h
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2005-09-05 09:33:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LDragAndDrop.h>

class CIndexedEditField;
class LEditText;
class LStaticText;
class LHandleStream;
class LTabGroupView;


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

	virtual void		Click( SMouseDownEvent &inMouseDown );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT	inCommand,
								Boolean&	outEnabled,
								Boolean&	outUsesMark,
								UInt16&		outMark,
								Str255		outName);

	virtual Boolean	ObeyCommand(
							CommandT		inCommand,
							void*			ioParam);

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
// 	LTabGroupView *				mTGV;
	TArray<CIndexedEditField*>	mIndexedFields;
	UInt16						mDropIndex;

	virtual void	FinishCreateSelf();

	virtual Boolean		ItemIsAcceptable( DragReference inDragRef,
							ItemReference inItemRef );
	virtual void		ReceiveDragItem( DragReference inDragRef,
							DragAttributes inDragAttrs, ItemReference inItemRef,
							Rect &inItemBounds );
	virtual void		EnterDropArea( DragReference inDragRef, Boolean inDragHasLeftSender );
	virtual void		LeaveDropArea( DragReference inDragRef );
	virtual void		InsideDropArea( DragReference inDragRef);
	virtual void		HiliteDropArea( DragReference inDragRef );

	void				GetIndexFromPoint(	const Point &inPortPoint,
											UInt16 &outRow );
	void				DrawDividingLine( UInt16 inRow );

private:	
	void			AddStringItem(Str255 inString);
	void			InsertStringItemAtIndex(UInt16 index, Str255 inString);
	void			RecalcPositionsFrom(UInt16 index);
	void			RecalcAllPositions();
	UInt16			DeleteSelected();
	
};


