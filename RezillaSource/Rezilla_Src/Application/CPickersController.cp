// ===========================================================================
// CPickersController.cp					
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CPickersController.h"
#include "CRezillaApp.h"
// // #include "CTEXT_PickerDoc.h"
// // #include "CPICT_PickerDoc.h"
// // #include "CIcon_PickerDoc.h"
// // #include "CMENU_PickerDoc.h"
#include "CTemplatesController.h"
#include "CRezMap.h"
#include "CRezMapDoc.h"
#include "CRezMapWindow.h"
#include "CRezMapTable.h"
#include "CRezTypeItem.h"
#include "CRezType.h"
#include "CRezObjItem.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"



// ---------------------------------------------------------------------------
//   CPickersController					Constructor				  [public]
// ---------------------------------------------------------------------------

CPickersController::CPickersController()
{
}


// ---------------------------------------------------------------------------
//     ~CPickersController					Destructor				  [public]
// ---------------------------------------------------------------------------

CPickersController::~CPickersController()
{	
}


// ---------------------------------------------------------------------------
//   HasPickerForType												[public]
// ---------------------------------------------------------------------------

Boolean
CPickersController::HasPickerForType(ResType inType)
{
	Boolean result = false;
	
	switch (inType) {
		case 'TEXT':
		case 'PICT':
		case 'CURS':
		case 'ICN#':
		case 'ICON':
		case 'PAT ':
		case 'PAT#':
		case 'SICN':
		case 'cicn':
		case 'crsr':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		case 'ppat':
		case 'MENU':
		result = true;
		break;
	}
	
	return result;
}


// ---------------------------------------------------------------------------
//   InvokeCustomPicker											[public]
// ---------------------------------------------------------------------------

void
CPickersController::InvokeCustomPicker(CRezMapDoc* inRezMapDoc, 
									   CRezTypeItem * inRezTypeItem)
{
	CRezMapTable *	inSuperMap = inRezMapDoc->GetRezMapWindow()->GetRezMapTable();
	Boolean			inReadOnly = inRezMapDoc->IsReadOnly();
	ResType			theType = inRezTypeItem->GetRezType()->GetType();
	
	switch (theType) {

		case 'TEXT':
// 		  new CTEXT_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;

		
		case 'PICT':
// 		  new CPICT_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'MENU':
// 		  new CMENU_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'STR#':
		case 'MBAR':
		case 'Mcmd':
		case 'RidL':
// 		  new CSTRx_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
		break;
		
		case 'CURS':
		case 'ICN#':
		case 'ICON':
		case 'PAT ':
		case 'PAT#':
		case 'SICN':
		case 'cicn':
		case 'crsr':
		case 'icl4':
		case 'icl8':
		case 'icm#':
		case 'icm4':
		case 'icm8':
		case 'ics#':
		case 'ics4':
		case 'ics8':
		case 'ppat':
// 		new CIcon_PickerDoc( (LCommander *) inRezMapDoc, inSuperMap, inRezTypeItem, inReadOnly);
	  break;
	  
	}
}



PP_End_Namespace_PowerPlant


