// ===========================================================================
// CRezObjItem.h					
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2003-05-27 16:14:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// ¬© Copyright: Bernard Desgraupes 2002-2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A concrete LOutlineItem for items of type "resource"

#pragma once

#include <LOutlineItem.h>
#include <LString.h>

class CRezType;
class CRezObj;
class CRezMapTable;

class CRezObjItem : public LOutlineItem {

public:
							CRezObjItem(CRezType * inRezType, 
										short inID, 
										Str255* inName = nil);
							CRezObjItem(Handle inResHandle, short inRefnum);
							CRezObjItem( CRezObj * inRezObj );
	virtual					~CRezObjItem();

	virtual CRezObj*	GetRezObj() { return mRezObj;}
	void				SetRezObj(CRezObj* theRezObj) {mRezObj = theRezObj;}
	
	CRezMapTable *			GetOwnerRezMapTable();

protected:

				CRezObj *		mRezObj;
				Handle			mIconH;

	virtual void		GetDrawContentsSelf(
									const STableCell&		inCell,
									SOutlineDrawContents&	ioDrawContents);

	virtual void		DrawRowAdornments(
									const Rect&				inLocalRowRect);
		
	virtual void		SingleClick(
									const STableCell&			inCell,
									const SMouseDownEvent&		inMouseDown,
									const SOutlineDrawContents&	inDrawContents,
									Boolean						inHitText);

	virtual void		DoubleClick(
									const STableCell&			inCell,
									const SMouseDownEvent&		inMouseDown,
									const SOutlineDrawContents&	inDrawContents,
									Boolean						inHitText);

private:
			// defensive programming
			
							CRezObjItem();
							CRezObjItem( const CRezObjItem &inOriginal );
		CRezObjItem&			operator=( const CRezObjItem &inOriginal );
};
