// ===========================================================================
// CMENU_EditorTable.h
// 
//                       Created: 2005-03-09 17:16:53
//             Last modification: 2005-03-10 08:42:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CMENU_EditorTable
#define _H_CMENU_EditorTable
#pragma once

#include <LTable.h>
#include <LDragAndDrop.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CMENU_EditorWindow;

// ---------------------------------------------------------------------------

class CMENU_EditorTable : public LTable, public LDragAndDrop  {
public:
	enum { class_ID = FOUR_CHAR_CODE('DnDT') };

	static CMENU_EditorTable	*CreateDragAndDropTableStream( LStream *inStream );

								CMENU_EditorTable( LStream *inStream );
			virtual				~CMENU_EditorTable();


// 	virtual Boolean			HandleKeyPress(
// 									const EventRecord& 	inKeyEvent);

// 	virtual Boolean			ObeyCommand(
// 									CommandT			inCommand,
// 									void*				ioParam);
	
	virtual void 			FindCommandStatus(
									CommandT			inCommand,
									Boolean&			outEnabled,
									Boolean&			outUsesMark,
									UInt16&				outMark,
									Str255				outName);

	virtual void			Click( SMouseDownEvent &inMouseDown );

	CMENU_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CMENU_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}


protected:
		CMENU_EditorWindow *	mOwnerWindow;
		TableIndexT				mDropRow;

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
