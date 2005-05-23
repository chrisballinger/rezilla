// ===========================================================================
// CRezMapTable.h					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2005-05-21 08:34:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#pragma once

#include "CRezMapDragDrop.h"

#include <LOutlineTable.h>
#include <LCommander.h>

class CRezTypeItem;
class CRezObjItem;
class CRezMap;
class CRezMapDoc;
class CRezMapWindow;

class CRezMapTable : public LOutlineTable,
					  public LCommander, 
					  public CRezMapDragDrop {
public:
	enum { class_ID = FOUR_CHAR_CODE('RzMT') };

								CRezMapTable( LStream *inStream );
			virtual				~CRezMapTable();

	void					Populate(TArray<ResType>* inTypesArray);

	Boolean					TypeExists(ResType inType, CRezTypeItem * & outRezTypeItem);

	void					InsertRezTypeItem(CRezTypeItem * inRezTypeItem);
	void					InsertRezObjItem(CRezObjItem * inRezObjItem, CRezTypeItem * inRezTypeItem);

	virtual void			Click( SMouseDownEvent &inMouseDown );
	virtual Boolean			HandleKeyPress( const EventRecord& inKeyEvent );

	Boolean					HasSelection();
	Boolean					HasSelectedRezTypeItems();
	Boolean					HasSelectedRezObjItems();

	UInt32					CountSelectedRezTypeItems();
	UInt32					CountAllSelectedRezObjItems();

	UInt32					GetSelectedRezTypeItems(LArray* & outArray);
	UInt32					GetAllSelectedRezObjItems(LArray* & outArray);
	void					GetFirstSelectedRezObjItem(CRezObjItem* & outRezObjItem);
	
	void					ExpandAll();
	void					CollapseAll();
	
	void					RemoveAllItems();

	CRezObjItem *			CreateItemIfNecessary(ResType inType, 
												  short inID, 
												  Str255* inName);
	
	CRezTypeItem *			GetRezTypeItem(ResType inType, 
										  Boolean expandIfClosed = false);
	
	CRezObjItem *			GetRezObjItem(ResType inType, 
										  short inID, 
										  Boolean expandIfClosed = false);

	virtual CRezMap*		GetRezMap() { return mRezMap;}
	void					SetRezMap(CRezMap* theRezMap) {mRezMap = theRezMap ;}

	CRezMapDoc *			GetOwnerDoc();
	
	CRezMapWindow *			GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CRezMapWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	// Used in Drag & Drop
	static Boolean			sApplyToOthers;
	static MessageT			sConflictAction;
	
protected:
	// Cache the rezmap of the owning document for faster retrieval. It is 
	// set by the caller (i-e CRezMapWindow::FinishCreateSelf).
	CRezMap *			mRezMap;
	CRezMapWindow *		mOwnerWindow;
	
	virtual void			DrawSelf();

	virtual	void			FinishCreateSelf();

	virtual Boolean			ItemIsAcceptable(DragReference inDragRef, ItemReference inItemRef);
	virtual void			ReceiveDragItem(DragReference inDragRef, 
											DragAttributes inDragAttrs, 
											ItemReference inItemRef, 
											Rect &inItemBounds);
	
	Boolean					GetFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData);
		
	virtual void			TrackDrag(
									const STableCell&			inCell,
									const SMouseDownEvent&		inMouseDown);

private:
				// Defensive programming
						CRezMapTable();
						CRezMapTable( const CRezMapTable &inOriginal );
	CRezMapTable&		operator=( const CRezMapTable &inOriginal );

};