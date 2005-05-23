// ===========================================================================
// CRezTypeItem.h				
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2005-05-02 09:42:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A concrete LOutlineItem for items of type "resource category"

#pragma once

#include <LOutlineItem.h>

class CRezType;
class CRezObjItem;
class CRezMapTable;

class CRezTypeItem : public LOutlineItem {

public:
										CRezTypeItem(CRezType * inRezType);
				virtual					~CRezTypeItem();
		
		virtual Boolean			CanExpand() const;
		
		Boolean					HasSelectedRezObjItems();

		UInt32					GetSelectedRezObjItems(LArray* & outArray);

		virtual CRezType*		GetRezType() { return mRezType;}
		void					SetRezType(CRezType* theRezType) {mRezType = theRezType ;}

		CRezMapTable *			GetOwnerRezMapTable();

		Boolean					ExistsItemForID(short inID, CRezObjItem * & outRezObjItem);

protected:
				CRezType*		mRezType;
				Handle			mIconH;
				
		virtual void			GetDrawContentsSelf(
									const STableCell&		inCell,
									SOutlineDrawContents&	ioDrawContents);

		virtual void			DrawRowAdornments(
									const Rect&				inLocalRowRect);
		
		virtual	void			ExpandSelf();

		virtual void			DoubleClick(
									const STableCell&			inCell,
									const SMouseDownEvent&		inMouseDown,
									const SOutlineDrawContents&	inDrawContents,
									Boolean						inHitText);

		virtual void			TrackDisclosureTriangle(
									const SMouseDownEvent&		inMouseDown);
		
private:
								CRezTypeItem();
								CRezTypeItem( const CRezTypeItem &inOriginal );
		CRezTypeItem&			operator=( const CRezTypeItem &inOriginal );
};

// 		CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
