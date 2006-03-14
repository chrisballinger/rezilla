// ===========================================================================
// CColorTableChoice.cp
//                       Created: 2004-12-11 18:50:13
//             Last modification: 2005-06-28 20:07:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2005
// All rights reserved.
// ===========================================================================
// 	* Most of the color resource types are edited using 32-bit buffers.
// 		This means that they support all of the various color table choices.
// 		
// 	* B&W buffers (including masks) don't support any choices (b&w only).
// 	
// 	* Icon families are the only place where the editor uses 4 & 8-bit
// 		buffers. Things are enabled as follows for them:
// 		  icl8, ics8, icm8	-> Apple 256 table or Apple Icon Colors
// 		  icl4, ics4, icm4	-> Apple 16 table
// 		  b&w				-> No tables

#include "CColorPane.h"
#include "CColorTableChoice.h"
#include "CIcon_EditorWindow.h"
#include "CRezillaPrefs.h"
#include "RezillaConstants.h"
#include "UColorUtils.h"
#include "UIconMisc.h"
#include "UMiscUtils.h"
#include "UResources.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CColorTableChoice::CColorTableChoice( CIcon_EditorWindow *inPaintView, Boolean inUsesIconColors )
{
	mPaintWindow = inPaintView;
	mCurrentTable = nil;
	this->InitTableCommands( inUsesIconColors );
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CColorTableChoice::~CColorTableChoice()
{
	this->DisposeCurrentTable();
}


// ---------------------------------------------------------------------------
// 	GetCurrentTable
// ---------------------------------------------------------------------------

CTabHandle
CColorTableChoice::GetCurrentTable()
{
	return( mCurrentTable );
}



// ---------------------------------------------------------------------------
// 	FindCommandStatus
// ---------------------------------------------------------------------------

Boolean
CColorTableChoice::FindCommandStatus( SInt32 inDepth, CommandT inCommand, 
										Boolean &outEnabled, Boolean &outUsesMark, 
										UInt16 &outMark, Str255  )
{
	Boolean		handled = false;
	Boolean		isLocked = mPaintWindow->GetLockFlag();
	
	outEnabled = false;
	
	switch( inCommand )
	{
		case cmd_ColorTableAppleIcon:
		outEnabled = (inDepth >= 8) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTableApple256:
		outEnabled = (inDepth >= 8) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTableApple16:
		outEnabled = (inDepth >= 16) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTableApple256Gray:
		outEnabled = (inDepth >= 16) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTableApple16Gray:
		outEnabled = (inDepth >= 16) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTableApple4Gray:
		outEnabled = (inDepth >= 16) && !isLocked;
		handled = true;
		break;	
		
		case cmd_ColorTablePicker:
		outEnabled = (inDepth >= 16) && !isLocked;
		handled = true;
		break;	
		
		case cmd_IconRecolorCurrentImage:
		Boolean usingPicker = (mTableCommands[inDepth] == cmd_ColorTablePicker);
		outEnabled = (inDepth >=16) && !usingPicker && !isLocked;
		handled = true;
		break;	
	}
	
	if ( handled )
	{
		if ( mTableCommands[inDepth] == inCommand )
		{
			outUsesMark = true;
			outMark = checkMark;
		}
		else
		{
			// We have to set outUsesMark to true or the checkmarks never
			// go away
			outUsesMark = true;
			outMark = 0;
		}
	}
	
	return( handled );
}


// ---------------------------------------------------------------------------
// 	ObeyCommand
// ---------------------------------------------------------------------------

Boolean
CColorTableChoice::ObeyCommand( SInt32 inDepth, CommandT inCommand )
{
	Boolean		didIt = false;
	ResIDT		theID;
	
	// Watch out for recursion when we get the recolor command
	static Boolean busy = false;
	if ( busy ) return( false );
	
	try
	{
		busy = true;

		if ( inCommand == cmd_IconRecolorCurrentImage )
		{
			if ( mCurrentTable )
				mPaintWindow->ObeyCommand( cmd_IconRecolorCurrentImage, mCurrentTable );
			didIt = true;
		}
		else
		{
			if ( this->MapCommandToTableID( inCommand, &theID ) )
			{
				this->ChangePopupColorTables( theID );
				mTableCommands[ inDepth ] = inCommand;
				didIt = true;
			}
		}
	}
	catch(...)
	{
		busy = false;
		throw;
	}
	
	busy = false;	
	return( didIt );
}


// ---------------------------------------------------------------------------
// 	MapCommandToTableID
// ---------------------------------------------------------------------------

Boolean
CColorTableChoice::MapCommandToTableID( CommandT inCommand, ResIDT *outResID )
{
	ResIDT		returnID = 0;
	
	switch( inCommand )
	{
		case cmd_ColorTableAppleIcon:
			*outResID = Clut_IconColors;
			return( true );
			
		case cmd_ColorTableApple256:
			*outResID = 8;
			return( true );
			
		case cmd_ColorTableApple16:
			*outResID = 4;
			return( true );
			
		case cmd_ColorTableApple256Gray:
			*outResID = 40;
			return( true );
			
		case cmd_ColorTableApple16Gray:
			*outResID = 36;
			return( true );
			
		case cmd_ColorTableApple4Gray:
			*outResID = 34;
			return( true );
			
		case cmd_ColorTablePicker:
			*outResID = ColorTable_UsePicker;
			return( true );
			
		case cmd_ColorTableApple2:
			*outResID = 1;
			return( true );
	}
	
	return( false );
}


// ---------------------------------------------------------------------------
// 	ChangePopupColorTables
// ---------------------------------------------------------------------------

void
CColorTableChoice::ChangePopupColorTables( ResIDT inResID )
{
	StRezRefSaver	aSaver;
	CTabHandle		theTable = nil;
	
	this->DisposeCurrentTable();

	if ( inResID == ColorTable_UsePicker )
		mCurrentTable = nil;
	else
		mCurrentTable = UColorUtils::GetColorTable( inResID );

	// Change the color table popups. If this results in a change of the
	// current color, they will broadcast a message to the paint view which
	// will also redraw the pattern popup.
	CColorPane *	forePane = (CColorPane*) mPaintWindow->FindPaneByID( tool_ForeColor );
	CColorPane *	backPane = (CColorPane*) mPaintWindow->FindPaneByID( tool_BackColor );
	
	if ( forePane )
		forePane->SetColorTable( mCurrentTable, true, redraw_Now );

	if ( backPane )
		backPane->SetColorTable( mCurrentTable, true, redraw_Now );

	LCommander::SetUpdateCommandStatus(true);
}


// ---------------------------------------------------------------------------
// 	ImageChanged
// ---------------------------------------------------------------------------
// 	Whenever the displayed image is changed, we may have to change
// 	the color table to a more suitable one.

void
CColorTableChoice::ImageChanged( SInt32 inNewDepth )
{
	this->ObeyCommand( inNewDepth, mTableCommands[ inNewDepth ] );
	LCommander::SetUpdateCommandStatus(true);
}


// ---------------------------------------------------------------------------
// 	DisposeCurrentTable
// ---------------------------------------------------------------------------

void
CColorTableChoice::DisposeCurrentTable()
{
	if ( mCurrentTable ) {
		::DisposeCTable( mCurrentTable );

		// This disposes the mCurrentTable. Warn the color panes, which may
		// keep a copy of the pointer to the color table, in order to avoid
		// a double free.
		CColorPane *	forePane = (CColorPane*) mPaintWindow->FindPaneByID( tool_ForeColor );
		CColorPane *	backPane = (CColorPane*) mPaintWindow->FindPaneByID( tool_BackColor );
		
		if ( forePane && forePane->GetColorTable() == mCurrentTable) {
			forePane->UnsetColorTable();
		}
		if ( backPane && backPane->GetColorTable() == mCurrentTable) {
			backPane->UnsetColorTable();
		}
		
		mCurrentTable = nil;
	}
}


// ---------------------------------------------------------------------------
// 	InitTableCommands
// ---------------------------------------------------------------------------

void
CColorTableChoice::InitTableCommands( Boolean inIconColors )
{
	CommandT	preferredCmd;
	
	( mTableCommands, sizeof( mTableCommands ) );
	
	// Icons default to Apple's preferred icon colors
	if ( inIconColors && ! CRezillaPrefs::GetPrefValue(kPref_editors_fullTables)  )
		preferredCmd = cmd_ColorTableAppleIcon;
	else
		preferredCmd = cmd_ColorTableApple256;

	mTableCommands[ 1 ] 	=	cmd_ColorTableApple2;
	mTableCommands[ 2 ] 	=	cmd_ColorTableApple4Gray;
	mTableCommands[ 4 ] 	=	cmd_ColorTableApple16;
	mTableCommands[ 8 ] 	=	preferredCmd;
	mTableCommands[ 16 ] 	=	preferredCmd;
	mTableCommands[ 24 ]	= 	preferredCmd;		// not used, but can't hurt
	mTableCommands[ 32 ] 	=	preferredCmd;
}

