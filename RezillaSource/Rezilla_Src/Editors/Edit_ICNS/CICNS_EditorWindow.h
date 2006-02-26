// ===========================================================================
// CICNS_EditorWindow.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
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


class CICNS_EditorWindow :	public CEditorWindow, 
							public LDragAndDrop {
public:
	enum { class_ID = FOUR_CHAR_CODE('STRW') };

							CICNS_EditorWindow();
							CICNS_EditorWindow( const SWindowInfo &inWindowInfo );
							CICNS_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CICNS_EditorWindow( LStream *inStream );
							~CICNS_EditorWindow();

	virtual void	Click( SMouseDownEvent &inMouseDown );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	OSErr			InstallResourceData(Handle inHandle);
	Handle			CollectResourceData();
	
	virtual void	RevertContents();
	
	LView*			GetContentsView() const { return mContentsView;}
	
	
protected:
	CICNS_Stream *			mOutStream;
	LView *					mContentsView;
	CICNS_Family *			mIcnsFamily;
	UInt16					mDropIndex;

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
	void			CreateIconAtIndex(UInt16 index);		
	void			InstallIconAtIndex(UInt16 index);
	void			DeleteIconAtIndex(UInt16 index);
};


