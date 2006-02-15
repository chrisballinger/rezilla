// ===========================================================================
// URezChain.cp					
// 
//                       Created: 2003-04-24 14:17:20
//             Last modification: 2003-04-24 17:08:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// ===========================================================================

#include "URezChain.h"


// ---------------------------------------------------------------------------
//  ¥ InsertFile														[public]
// ---------------------------------------------------------------------------
// Possible values for inWhere argument are:
//   kRsrcChainBelowSystemMap			Below the system's resource map
//   kRsrcChainBelowApplicationMap		Below the application's resource map
//   kRsrcChainAboveApplicationMap		Above the application's resource map
//   kRsrcChainAboveAllMaps				Above all resource maps

OSErr
URezChain::InsertFile( SInt16 inRefNum, RsrcChainLocation inWhere)
{
	return ::InsertResourceFile(inRefNum, inWhere);
}


// ---------------------------------------------------------------------------
//  ¥ DetachFile														[public]
// ---------------------------------------------------------------------------

OSErr
URezChain::DetachFile(SInt16 inRefNum)
{
	return ::DetachResourceFile(inRefNum);
}


// ---------------------------------------------------------------------------
//  ¥ GetTopFile														[public]
// ---------------------------------------------------------------------------

OSErr
URezChain::GetTopFile(SInt16 & outRefNum)
{
	return ::GetTopResourceFile(&outRefNum);
}


// ---------------------------------------------------------------------------
//  ¥ GetNextFile														[public]
// ---------------------------------------------------------------------------

OSErr
URezChain::GetNextFile(SInt16 inCurRefNum, SInt16 & outNextRefNum)
{
	return ::GetNextResourceFile(inCurRefNum, &outNextRefNum);
}


// ---------------------------------------------------------------------------
//  ¥ Count														[public]
// ---------------------------------------------------------------------------
// If the resource chain is empty, resFNotFound is returned.

short
URezChain::Count()
{
	short	theCount = 0;
	SInt16	curRefNum;
	SInt16	nextRefNum;
	
	if ( ::GetTopResourceFile(&curRefNum) == noErr ) {
		theCount++;
		::GetNextResourceFile(curRefNum,&nextRefNum);
		while (nextRefNum != nil) {
			theCount++;
			curRefNum = nextRefNum;
			::GetNextResourceFile(curRefNum,&nextRefNum);
		}
	}
	return theCount;
}


// ---------------------------------------------------------------------------
//  ¥ GetChainList														[public]
// ---------------------------------------------------------------------------

TArray<ResType>*
URezChain::GetChainList()
{
	TArray<ResType>* theChainArrayPtr = nil;
	SInt16	curRefNum;
	SInt16	nextRefNum;
	
	if ( ::GetTopResourceFile(&curRefNum) == noErr ) {
		theChainArrayPtr->AddItem(curRefNum);
		::GetNextResourceFile(curRefNum,&nextRefNum);
		
		while (nextRefNum != nil) {
			theChainArrayPtr->AddItem(nextRefNum);
			curRefNum = nextRefNum;
			::GetNextResourceFile(curRefNum,&nextRefNum);
		}
	}
	return theChainArrayPtr;
}


