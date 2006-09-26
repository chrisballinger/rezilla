// ===========================================================================
// CDragTable.h
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2006-09-21 18:05:41
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CDragTable
#define _H_CDragTable
#pragma once

#include <LTable.h>
#include <LBroadcaster.h>
#include <LCommander.h>
#include <LDragAndDrop.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant



class CDragTable :	public LTable, 
					public LBroadcaster,
					public LCommander,
					public LDragAndDrop  {
public:
	enum { class_ID = FOUR_CHAR_CODE('DnDT') };

	static CDragTable	*CreateDnDTableStream( LStream *inStream );

								CDragTable( LStream *inStream );
			virtual				~CDragTable();


	virtual Boolean			HandleKeyPress(
									const EventRecord& 	inKeyEvent);

// 	virtual void			SelectCell( const TableCellT& inCell );
	
	virtual void			Click( SMouseDownEvent &inMouseDown );

	void					DrawSeparator( TableIndexT	inRow );
	
	void					RemoveSelectedRow();
	

protected:
		TableIndexT		mDropRow;
		ResIDT			mTxtrID;

// 		virtual void		FinishCreateSelf();

		virtual void		DrawCell( const TableCellT &inCell );
		virtual void		ClickCell( const TableCellT &inCell,
								const SMouseDownEvent &inMouseDown );
		virtual void		UnhiliteCell( const TableCellT &inCell );

		virtual void		ActivateSelf();
		virtual void		DeactivateSelf();
		
		virtual void		RefreshCell( const TableCellT &inCell );

		virtual Boolean		ItemIsAcceptable( DragReference inDragRef,
								ItemReference inItemRef );
		virtual void		ReceiveDragItem( DragReference inDragRef,
								DragAttributes inDragAttrs, ItemReference inItemRef,
								Rect &inItemBounds );
		virtual void		EnterDropArea( DragReference inDragRef, Boolean inDragHasLeftSender );
		virtual void		LeaveDropArea( DragReference inDragRef );
		virtual void		InsideDropArea( DragReference inDragRef);
		virtual void		HiliteDropArea( DragReference inDragRef );

		void				GetDividingLineGivenPoint( const Point &inPortPoint,
								TableIndexT &outRow );
		void				DrawDividingLine( TableIndexT inRow );
		
};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
