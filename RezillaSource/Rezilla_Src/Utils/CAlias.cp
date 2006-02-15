// ===========================================================================
// CAlias.cp					
//                       Created: 2004-03-02 13:18:30
//             Last modification: 2004-03-13 11:48:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================


#include "CAlias.h"


// -----------------------------------------------------------------
//	¥	Constructor 
// -----------------------------------------------------------------
//	NULLs AliasHandle member

CAlias::CAlias()
{
	mAliasH = NULL;
}


// -----------------------------------------------------------------
//	¥	Constructor 
// -----------------------------------------------------------------

CAlias::CAlias(AliasHandle inAliasHandle)
{
	mAliasH = NULL;
	
	// Use overloaded = operator
	*this = inAliasHandle;
}


// -----------------------------------------------------------------
//	¥	Constructor 
// -----------------------------------------------------------------
//	Construct from FSSpec

CAlias::CAlias(FSSpec& inFSSpec)
{
	mAliasH = NULL;
	
	// Use overloaded = operator
	*this = inFSSpec;
}


// -----------------------------------------------------------------
//	¥	Destructor
// -----------------------------------------------------------------

CAlias::~CAlias()
{
	Dispose();
}


// -----------------------------------------------------------------
//	¥	GetFileSpec()
// -----------------------------------------------------------------

OSErr
CAlias::GetFileSpec(FSSpec& outFileSpec)
{
	OSErr 	result 	= noErr;
	Boolean	wasChanged 	= false;
	
	if (mAliasH != NULL) {
		result = ::ResolveAlias(NULL, mAliasH, &outFileSpec, &wasChanged);
	} else {
		result = nilHandleErr;
	}
	
	return result;
}


// -----------------------------------------------------------------
//	¥	GetFileName()
// -----------------------------------------------------------------

OSErr
CAlias::GetFileName(Str255 outFileName)
{
	FSSpec	theFileSpec;
	OSErr		result = noErr;
	
	outFileName[0] = 0;	
	result = GetFileSpec(theFileSpec);
	
	if (result == noErr) {
		::BlockMove(theFileSpec.name, outFileName, theFileSpec.name[0] + 1);
	}
		
	return result;
}


// -----------------------------------------------------------------
//	¥	Resolve()
// -----------------------------------------------------------------
//	Result is error code from AliasManager's ResolveAlias().
//	If AliasHandle member was NULL (object hasn't beeen initialized),
//	result is nilHandleErr.

OSErr
CAlias::Resolve()
{
	OSErr 	result 	= noErr;
	Boolean	wasChanged 	= false;
	FSSpec	theFSSpec;
	
	if (mAliasH != NULL) {
		result = ::ResolveAlias(NULL, mAliasH, &theFSSpec, &wasChanged);
	} else {	
		result = nilHandleErr;
	}
	
	return result;
}


// -----------------------------------------------------------------
//	¥	Dispose
// -----------------------------------------------------------------

void
CAlias::Dispose()
{
	if (mAliasH != NULL) {
		::DisposeHandle((Handle) mAliasH);
		mAliasH = NULL;
	}
}


// -----------------------------------------------------------------
//	¥	operator =
// -----------------------------------------------------------------
//	Assignment operator with AliasHandle.

CAlias&
CAlias::operator = (
	AliasHandle inAliasHandle)
{
	Dispose();
	
	if (inAliasHandle) {
		mAliasH = inAliasHandle;
		::HandToHand((Handle*) &mAliasH);
	}
	
	return *this;
}


// -----------------------------------------------------------------
//	¥	operator =
// -----------------------------------------------------------------
//	Assignment operator with FSSpec.

CAlias&
CAlias::operator = (
	const FSSpec& inFSSpec)
{
	Dispose();
	
	::NewAlias(NULL, &inFSSpec, &mAliasH);
	
	return *this;
}


