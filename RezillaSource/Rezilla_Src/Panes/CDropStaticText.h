// ===========================================================================
// CDropStaticText.h					
// 
//                       Created : 2003-04-12 10:45:24
//             Last modification : 2003-04-12 10:45:43
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Subclass the LSlider class to define a HotSpotResult function
// to update the collate WEViews after the slider has been tracked.


#ifndef _H_CDropStaticText
#define _H_CDropStaticText
#pragma once

#include <LStaticText.h>
#include <LDragAndDrop.h>



PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------

class CDropStaticText : public LStaticText, public LDragAndDrop {
public:
	enum { class_ID		= FOUR_CHAR_CODE('Dstx'),
		   imp_class_ID	= FOUR_CHAR_CODE('istx')};

						CDropStaticText(
								LStream*		inStream);

	virtual				~CDropStaticText();


protected:
		virtual Boolean			ItemIsAcceptable(DragReference inDragRef, ItemReference inItemRef);
		virtual void			ReceiveDragItem(DragReference inDragRef, DragAttributes inDragAttrs, ItemReference inItemRef, Rect &inItemBounds);
		
		Boolean					GetFileData(DragReference inDragRef, ItemReference inItemRef, HFSFlavor& fileData);
		

};

PP_End_Namespace_PowerPlant




#endif
