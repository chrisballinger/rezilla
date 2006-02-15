// ===========================================================================
// CSharedPalette.cp
//                       Created: 2004-12-11 18:52:58
//             Last modification: 2004-12-14 22:27:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#include "CSharedPalette.h"


// ---------------------------------------------------------------------------
// 	Constructor
// ---------------------------------------------------------------------------

CSharedPalette::CSharedPalette( CTabHandle inTable, GrafPtr inPort, short inUpdates )
{
	ThrowIfNil_( inTable );
	
	mPaletteH = ::NewPalette( (**inTable).ctSize + 1, inTable, pmTolerant | pmExplicit, 0 );
	ThrowIfMemFail_( mPaletteH );
	
	if ( inPort )
		this->AttachToPort( inPort, inUpdates );
		
	mRefCount = 1;			// (change back from 2 if inPort != nil)
}


// ---------------------------------------------------------------------------
// 	Destructor
// ---------------------------------------------------------------------------

CSharedPalette::~CSharedPalette()
{
	if ( mPaletteH )
		::DisposePalette( mPaletteH );
}


// ---------------------------------------------------------------------------
// 	AttachToPort
// ---------------------------------------------------------------------------

void
CSharedPalette::AttachToPort( GrafPtr inPort, short inUpdates )
{
	if ( inPort && mPaletteH )
	{
		WindowRef theWindow = ::GetWindowFromPort(inPort);
		::NSetPalette(theWindow, mPaletteH, inUpdates );
		this->IncrementRefCount();
	}
}


// ---------------------------------------------------------------------------
// 	GetPalette
// ---------------------------------------------------------------------------

PaletteHandle
CSharedPalette::GetPalette()
{
	return mPaletteH;
}

