// ===========================================================================
// CHexEditorWindow.cp					
// 
//                       Created: 2003-05-02 07:33:10
//             Last modification: 2005-06-15 10:27:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#include "CHexEditorWindow.h"
#include "CHexDataSubView.h"
#include "CTxtDataSubView.h"
#include "CDualDataView.h"
#include "CHexEditorActions.h"
#include "CHexEditorDoc.h"
#include "CRangeEditText.h"
#include "CRezObj.h"
#include "CRezillaApp.h"
#include "CRezillaPrefs.h"
#include "CRezClipboard.h"
#include "CWasteEditView.h"
#include "CSingleScrollBar.h"
#include "RezillaConstants.h"
#include "UCodeTranslator.h"
#include "UMessageDialogs.h"

#include <LScrollBar.h>
#include <LStaticText.h>
#include <LTextGroupBox.h>
#include <LUndoer.h>
#include <UExtractFromAEDesc.h>
#include <UAppleEventsMgr.h>
#include <UCursor.h>

#include <AppleHelp.h>


// ---------------------------------------------------------------------------
//		¥ CHexEditorWindow				[public]
// ---------------------------------------------------------------------------

CHexEditorWindow::CHexEditorWindow()
{
	SetModelKind(rzom_cHexWindow);
}


// ---------------------------------------------------------------------------
//		¥ CHexEditorWindow				[public]
// ---------------------------------------------------------------------------

CHexEditorWindow::CHexEditorWindow(
	const SWindowInfo &inWindowInfo )
		: CEditorWindow( inWindowInfo )
{
	SetModelKind(rzom_cHexWindow);
}


// ---------------------------------------------------------------------------
//		¥ CHexEditorWindow				[public]
// ---------------------------------------------------------------------------

CHexEditorWindow::CHexEditorWindow(
	ResIDT		inWINDid,
	UInt32		inAttributes,
	LCommander	*inSuperCommander )
		: CEditorWindow( inWINDid, inAttributes, inSuperCommander )
{
	SetModelKind(rzom_cHexWindow);
}


// ---------------------------------------------------------------------------
//		¥ CHexEditorWindow				[public]
// ---------------------------------------------------------------------------

CHexEditorWindow::CHexEditorWindow(
			       LStream *inStream )
		: CEditorWindow( inStream )
{
	SetModelKind(rzom_cHexWindow);
}


// ---------------------------------------------------------------------------
//		¥ ~CHexEditorWindow				[public]
// ---------------------------------------------------------------------------

CHexEditorWindow::~CHexEditorWindow()
{
	// Remove the window from the list of listeners to the prefs object
	CRezillaApp::sPrefs->RemoveListener(this);
}


// ---------------------------------------------------------------------------
//		¥ FinishCreateSelf				[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::FinishCreateSelf()
{		
	mOwnerDoc = dynamic_cast<CHexEditorDoc*>(GetSuperCommander());

	// Get the Waste edit subviews
	CHexDataSubView * theHexDataWE = dynamic_cast<CHexDataSubView *>(this->FindPaneByID( item_HexDataWE ));
	ThrowIfNil_(theHexDataWE);
		
	CTxtDataSubView * theTxtDataWE = dynamic_cast<CTxtDataSubView *>(this->FindPaneByID( item_TxtDataWE ));
	ThrowIfNil_(theTxtDataWE);
		
	// Get the scrollbar controlling the data panes
	CSingleScrollBar * theScroller = dynamic_cast<CSingleScrollBar *>(this->FindPaneByID( item_HexScroller ));
	ThrowIfNil_(theScroller);
	
	// Get the dual view object
	mDualView = dynamic_cast<CDualDataView *>(this->FindPaneByID( item_HexEditGroupBox ));
	ThrowIfNil_(mDualView);
	
	// Install the subviews and the scroller in the dual view
	mDualView->InstallSubViews(theHexDataWE, theTxtDataWE, theScroller, mOwnerDoc->IsReadOnly() );

	// Set the geometry for the dual subpanes
	DualGeometry geo;
	geo.hinst = kRzilHexEditLeftRidge;
	geo.vinst = kRzilHexEditTopRidge;
	geo.hsep = kTmplHorizSep;
	geo.scrlw = kTmplScrollWidth;
	mDualView->SetGeometry(geo);
	
	mDualView->SetWindowRef(mMacWindowP);
	mDualView->SetSuperCommander(this);

	// Use the style specified in the preferences and calculate the capacities of the editing panes
	TextTraitsRecord theTraits = CRezillaPrefs::GetStyleElement( CRezillaPrefs::prefsType_Curr );
	mDualView->ResizeDataPanes();
	mDualView->UpdatePaneCounts();
	theHexDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	theTxtDataWE->ApplyStyleValues( theTraits.size, theTraits.fontNumber);
	
	// Editable text
	mLineField = dynamic_cast<CRangeEditText *>(this->FindPaneByID( item_HexLineEdit ));
	ThrowIfNil_( mLineField );
		
	mOffsetField = dynamic_cast<CRangeEditText *>(this->FindPaneByID( item_HexOffsetEdit ));
	ThrowIfNil_( mOffsetField );
		
	// Set the line and offset fields
	theScroller->SetMinValue(1);	
	theScroller->SetLinesPerPage( mDualView->GetPaneCount(count_LinesPerPane) - 1);
	SetLineValues();
	SetOffsetValues();

	// Let the window listen to the text edit fields
	mLineField->AddListener(this);	
	mOffsetField->AddListener(this);	
	mDualView->AddListener(this);	

	// Make the window a listener to the prefs object
	CRezillaApp::sPrefs->AddListener(this);
	
	// Attach an LUndoer to each of the subpanes
	theHexDataWE->AddAttachment( new LUndoer );
	theTxtDataWE->AddAttachment( new LUndoer );
}
	

// ---------------------------------------------------------------------------
//		¥ ListenToMessage				[public]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::ListenToMessage(MessageT inMessage, void *ioParam ) 
{
	SInt32 theRangeStart, theRangeEnd;
	
	switch (inMessage) {
		
		case msg_HexLineEdit: {
			SInt32 lineStart, lineEnd;
			SInt32 bytesPerLine = mDualView->GetPaneCount(count_BytesPerLine);

			mLineField->GetRangeValues(theRangeStart, theRangeEnd);
			if (theRangeEnd == -1) {
				theRangeEnd = mDualView->CountLines() + 1;
			} 
			lineStart = (theRangeStart - 1) * bytesPerLine;
			lineEnd = theRangeEnd * bytesPerLine;
			DisplayBothSelections(lineStart, lineEnd);
			break;
		}
		
		case msg_HexOffsetEdit: {
			mOffsetField->GetRangeValues(theRangeStart, theRangeEnd);
			if (theRangeEnd == -1) {
				theRangeEnd = mDualView->GetTxtView()->GetTextLength();
			} 
			DisplayBothSelections(theRangeStart, theRangeEnd);
			break;
		}
		
		case msg_DualViewEdited: {
			SetLineValues();
			SetOffsetValues();
			break;
		}
		
		default:
		dynamic_cast<CHexEditorDoc *>(GetSuperCommander())->ListenToMessage(inMessage, ioParam);
		break;
				
	}
}


// ---------------------------------------------------------------------------
//	¥ FindCommandStatus
// ---------------------------------------------------------------------------
//	Pass back whether a Command is enabled and/or marked (in a Menu)

void
CHexEditorWindow::FindCommandStatus(
	CommandT	inCommand,
	Boolean		&outEnabled,
	Boolean		&outUsesMark,
	UInt16		&outMark,
	Str255		outName)
{
	switch (inCommand) {

		case cmd_EditRez:
		case cmd_EditRezAsType:
		case cmd_TmplEditRez:
		case cmd_HexEditRez:
		case cmd_RemoveRez:
		case cmd_DuplicateRez:
			outEnabled = false;
			break;		
		
		default:
			LCommander::FindCommandStatus(inCommand, outEnabled,
									outUsesMark, outMark, outName);
			break;
	}
}


// ---------------------------------------------------------------------------
//	¥ ObeyCommand							[public, virtual]
// ---------------------------------------------------------------------------

Boolean
CHexEditorWindow::ObeyCommand(
	CommandT	inCommand,
	void*		ioParam)
{
	Boolean		cmdHandled = true;
	
	switch (inCommand) {

		default:
			cmdHandled = LCommander::ObeyCommand(inCommand, ioParam);
			break;
	}

	return cmdHandled;
}


// ---------------------------------------------------------------------------
//	¥ SetLineValues											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetLineValues()
{
	SInt32  firstLine, lastLine;
	
	mDualView->GetCurrLines(firstLine, lastLine);
	firstLine += (mDualView->GetCurrFirstLine() - 1);
	lastLine += (mDualView->GetCurrFirstLine() - 1);
	
	SetLineRange(firstLine, lastLine);
}


// ---------------------------------------------------------------------------
//	¥ SetLineRange											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetLineRange(SInt32 inStart, SInt32 inEnd)
{
	Str255	theString;
	LStr255	theLine("\p");
	
	::NumToString( inStart, theString);
	theLine.Append(theString);
	if ( inStart != inEnd ) {
		theLine += "\p-";
		::NumToString( inEnd, theString);
		theLine.Append(theString);
	} 
	mLineField->SetDescriptor(theLine);
}


// ---------------------------------------------------------------------------
//	¥ SetOffsetValues											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetOffsetValues()
{
	SInt32  selStart, selEnd;
	SInt32	bytesPerLine = mDualView->GetPaneCount(count_BytesPerLine);
	SInt32  offset = (mDualView->GetCurrFirstLine() - 1) * bytesPerLine;
	
	mDualView->GetCurrHexPos(selStart, selEnd);
	selStart += offset;
	selEnd += offset;
	SetOffsetRange(selStart, selEnd);
}


// ---------------------------------------------------------------------------
//	¥ SetOffsetRange											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetOffsetRange(SInt32 inStart, SInt32 inEnd)
{
	Str255 theString;
	LStr255 theLine("\p");
	
	::NumToString( inStart, theString);
	theLine.Append(theString);
	if ( inStart != inEnd ) {
		theLine += "\p-";
		::NumToString( inEnd, theString);
		theLine.Append(theString);
	} 
	mOffsetField->SetDescriptor(theLine);
}


// ---------------------------------------------------------------------------
//	¥ ClearFields											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::ClearFields()
{
	mLineField->SetDescriptor("\p");
	mOffsetField->SetDescriptor("\p");
}


// ---------------------------------------------------------------------------
//	¥ InstallResourceData											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::InstallResourceData(Handle inHandle)
{
	mDualView->InstallBackStoreData(inHandle);
	mDualView->SetMaxScrollerValue();
	InstallContentsFromLine(1);
	// Set the positions internally to 0
	::WESetSelection( 0, 0, mDualView->GetInMemoryWE());
	// Mark window as dirty
	mDualView->SetDirty( false );
}


// ---------------------------------------------------------------------------
//	¥ DisplayBothSelections											[protected]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::DisplayBothSelections(SInt32 inStart, SInt32 inEnd)
{
	mDualView->DisplayBothSelections(inStart, inEnd);
									  
	SetOffsetRange(inStart, inEnd);
	SetLineRange(mDualView->PosToLine(inStart), mDualView->PosToLine(inEnd));
}


// ---------------------------------------------------------------------------
//	¥ InstallContentsFromLine											[public]
// ---------------------------------------------------------------------------

SInt32
CHexEditorWindow::InstallContentsFromLine(SInt32 inFromLine)
{
	SInt32 charOffset = mDualView->InstallContentsFromLine(inFromLine);

// 	SetLineRange(inFromLine, inFromLine);
// 	SetOffsetRange(charOffset, charOffset);
	return charOffset;
}


// ---------------------------------------------------------------------------
//	¥ IsDirty														[public]
// ---------------------------------------------------------------------------

Boolean
CHexEditorWindow::IsDirty()
{
	return mDualView->IsDirty();
}


// ---------------------------------------------------------------------------
//  SetDirty														[public]
// ---------------------------------------------------------------------------

void
CHexEditorWindow::SetDirty(Boolean inDirty) 
{
	CEditorWindow::SetDirty(inDirty);
	mDualView->SetDirty(inDirty);
}


// // ---------------------------------------------------------------------------
// //	¥ DoSetBounds
// // ---------------------------------------------------------------------------
// 
// void
// CHexEditorWindow::DoSetBounds(
// 	const Rect&		inBounds)
// {
// 	LWindow::DoSetBounds(inBounds);
// 	mDualView->ResetBounds();
// }


