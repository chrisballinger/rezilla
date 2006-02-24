// ===========================================================================
// CPickersController.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 23:46:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once


class CRezMapDoc;
class CRezTypeItem;

class CPickersController {
public:
						CPickersController();
						~CPickersController();
	
	static Boolean	HasPickerForType(ResType inType);

	static void		InvokeCustomPicker(CRezMapDoc* inRezMapDoc, 
									   CRezTypeItem * inRezTypeItem);

protected:	

};


