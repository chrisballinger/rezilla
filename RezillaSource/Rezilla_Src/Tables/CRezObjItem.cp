// ===========================================================================
// CRezObjItem.cp					
//                       Created: 2003-04-18 09:34:02
//             Last modification: 2005-06-09 11:28:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004, 2005
// All rights reserved.
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
//   CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(CRezType * inRezType,
				short inID,
				Str255* inName)
{
	mIconH = nil;
	mRezObj = new CRezObj( inRezType, inID, inName );
	mRezObj->IncrRefCount();
}


// ---------------------------------------------------------------------------
//   CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(Handle inResHandle, short inRefnum)
{
	mIconH = nil;
	mRezObj = new CRezObj(inResHandle, inRefnum);
	mRezObj->IncrRefCount();
}


// ---------------------------------------------------------------------------
//   CRezObjItem							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CRezObjItem::CRezObjItem(CRezObj * inRezObj)
{
	mIconH = nil;
	mRezObj = inRezObj;
	mRezObj->IncrRefCount();
}


// ---------------------------------------------------------------------------
//     ~CRezObjItem							Destructor				  [public]
// ---------------------------------------------------------------------------

CRezObjItem::~CRezObjItem()
{
	if ( mIconH != nil ) {
		::DisposeIconSuite(mIconH, true);
	}

	if (mRezObj != nil) {
		// Clear the Inspector if it contains info about this resource item
		CRezillaApp::sInspectorWindow->ClearIfNecessary(mRezObj);
		
		mRezObj->DecrRefCount();
		if (mRezObj->GetRefCount() == 0) {
			delete mRezObj;
		} 
	}
}


// ---------------------------------------------------------------------------
//   GetDrawContentsSelf
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
// 			ioDrawContents.outTextTraits.justification = teJustRight;
			
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
//   DrawRowAdornments
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
//   GetOwnerRezMapTable
// ---------------------------------------------------------------------------

CRezMapTable *
CRezObjItem::GetOwnerRezMapTable()
{
	CRezMapTable *theRezMapTable = dynamic_cast<CRezMapTable*>(mOutlineTable);
	return theRezMapTable;
// 	return GetSuperItem()->GetOwnerRezMapTable();
}



// ---------------------------------------------------------------------------
//   SingleClick												   [protected]
// ---------------------------------------------------------------------------
// If the command key is down, open the inspector window and display the
// corresponding info about the resource. Versions prior to 1.0.5b
// (included) used the control key but this should be reserved for the
// contextual menus.

void
CRezObjItem::SingleClick(
	const STableCell&			/* inCell */,
	const SMouseDownEvent&		inMouseDown,
	const SOutlineDrawContents&	/* inDrawContents */,
	Boolean						/* inHitText */)
{
// 	LOutlineItem::SingleClick(inCell, inMouseDown, inDrawContents, inHitText);
	if (inMouseDown.macEvent.modifiers & cmdKey) {
		CRezillaApp::sInspectorWindow->Show();
		CRezillaApp::sInspectorWindow->InstallValues(this);
		// Bring the window to the front.
		UDesktop::SelectDeskWindow( CRezillaApp::sInspectorWindow );
	} else if (CRezillaApp::sInspectorWindow->IsVisible()) {
		CRezillaApp::sInspectorWindow->InstallValues(this);
	}
}


// ---------------------------------------------------------------------------
//   DoubleClick
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
	CRezMapTable *theRezMapTable = GetOwnerRezMapTable();
	
	if (inMouseDown.macEvent.modifiers & optionKey) {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_HexEditRez);
	} else if (inMouseDown.macEvent.modifiers & shiftKey) {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_TmplEditRez);
	} else {
		theRezMapTable->GetOwnerDoc()->TryEdit(this, cmd_EditRez);
	}
}

