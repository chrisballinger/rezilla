// ===========================================================================
// CRezObjItem.cp					
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2004-06-26 08:56:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A concrete LOutlineItem for items of type "resource"


#include "CRezObjItem.h"
#include "CRezObj.h"
#include "CRezMapTable.h"
#include "CRezMapDoc.h"
#include "RezillaConstants.h"
#include "CRezillaApp.h"
#include "CInspectorWindow.h"
#include "CHexEditorDoc.h"
#include "CRezMapWindow.h"
// #include "GetFileIcon.h"

#include <LOutlineItem.h>
#include <LOutlineTable.h>
#include <UGAColorRamp.h>

#include <UDesktop.h>

// ---------------------------------------------------------------------------
//	¥ CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(CRezType * inRezType,
				short inID,
				Str255* inName)
{
	mIconH = nil;
	mRezObj = new CRezObj( inRezType, inID, inName );
}


// ---------------------------------------------------------------------------
//	¥ CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(Handle inResHandle, short inRefnum)
{
	mRezObj = new CRezObj(inResHandle, inRefnum);
	mIconH = nil;
}


// ---------------------------------------------------------------------------
//	¥ CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(CRezObj * inRezObj)
{
	mRezObj = inRezObj;
	mIconH = nil;
}


// ---------------------------------------------------------------------------
//	¥ ~CRezObjItem							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezObjItem::~CRezObjItem()
{
	if ( mIconH != nil ) {
		::DisposeIconSuite(mIconH, true);
	}
	// Clear the Inspector if it contains info about this resource item
	if (CRezillaApp::sInspectorWindow != nil &&
		CRezillaApp::sInspectorWindow->GetRezObjItem() == this
	) {
		CRezillaApp::sInspectorWindow->ClearValues();
	} 
}


// ---------------------------------------------------------------------------
//	¥ GetDrawContentsSelf
// ---------------------------------------------------------------------------
// this is the routine called to know what to draw within the
// table cell. See the comments in LOutlineItem.cp for more info.

void
CRezObjItem::GetDrawContentsSelf(
	const STableCell&		inCell,
	SOutlineDrawContents&	ioDrawContents)
{
	
	Str255	tempString;
	
	switch (inCell.col)
	{
		case 1:
		{
			::NumToString(mRezObj->GetID(), tempString);
			
			ioDrawContents.outShowSelection = true;
			ioDrawContents.outHasIcon = false;
			// 			ioDrawContents.outIconSuite = mIconH;
			ioDrawContents.outTextTraits.style = 0;
			
			LString::CopyPStr(tempString, ioDrawContents.outTextString);
			
			break;
		}
		
		case 2:
		{
			::NumToString(mRezObj->GetSize(), tempString);
			
			ioDrawContents.outShowSelection = true;
			ioDrawContents.outHasIcon = false;
			ioDrawContents.outTextTraits.style = 0;
			
			LString::CopyPStr(tempString, ioDrawContents.outTextString);
			
			break;
		}
		
		case 3:
		{
			ioDrawContents.outShowSelection = true;
			ioDrawContents.outHasIcon = false;
			ioDrawContents.outTextTraits.style = 0;
			
			LString::CopyPStr(*mRezObj->GetName(), ioDrawContents.outTextString);
			
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//	¥ DrawRowAdornments
// ---------------------------------------------------------------------------
// just to be cute, we'll draw an adornment (again, see the LOutlineItem.cp
// comments for more information). We'll draw a groovy gray background

void
CRezObjItem::DrawRowAdornments(
	const Rect&		inLocalRowRect )
{
	ShadeRow(UGAColorRamp::GetColor(colorRamp_Gray1), inLocalRowRect);
}


// ---------------------------------------------------------------------------
//	¥ GetOwnerRezMapTable
// ---------------------------------------------------------------------------

CRezMapTable *
CRezObjItem::GetOwnerRezMapTable()
{
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
	return theRezMapTable;
// 	return GetSuperItem()->GetOwnerRezMapTable();
}



// ---------------------------------------------------------------------------
//	¥ SingleClick												   [protected]
// ---------------------------------------------------------------------------
// If the option key is down, open the inspector window and display the 
// corresponding info about the resource

void
CRezObjItem::SingleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		inMouseDown,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
// 	LOutlineItem::SingleClick(inCell, inMouseDown, inDrawContents, inHitText);
	if (inMouseDown.macEvent.modifiers & optionKey) {
		CRezillaApp::sInspectorWindow->Show();
		CRezillaApp::sInspectorWindow->InstallValues(this);
		// Bring the window to the front.
		UDesktop::SelectDeskWindow( CRezillaApp::sInspectorWindow );
	}
}


// ---------------------------------------------------------------------------
//	¥ DoubleClick
// ---------------------------------------------------------------------------
// During a double click:
// - if the shift key is down, try to edit with the template editor.
// - if the option key is down, try to edit with the hex editor.
// - otherwise try any editor in the usual order (gui, tmpl, hex).

void
CRezObjItem::DoubleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		inMouseDown,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
	int countEdit;
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
	
	if (inMouseDown.macEvent.modifiers & optionKey) {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_HexEditRez, countEdit);
	} else if (inMouseDown.macEvent.modifiers & shiftKey) {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_TmplEditRez, countEdit);
	} else {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_EditRez, countEdit);
	}
}

