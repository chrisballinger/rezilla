// ===========================================================================
// UResources.cp					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2003-04-24 07:15:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UResources.h"


// ---------------------------------------------------------------------------
//  ¬€ GetCurrentResFile													[public]
// ---------------------------------------------------------------------------

OSErr
UResources::GetCurrentResFile(short & outRefNum)
{
	outRefNum = ::CurResFile();
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ CountForType													[public]
// ---------------------------------------------------------------------------
// Count the number of resources of a given type in all opened resource 
// maps.

OSErr
UResources::CountForType(ResType inType, short & outCount)
{
	outCount = ::CountResources(inType);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ CountAllTypes													[public]
// ---------------------------------------------------------------------------
// Count the number of types in all opened resource maps.

OSErr
UResources::CountAllTypes(short & outCount)
{
	outCount = ::CountTypes();
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ CountAllResources												[public]
// ---------------------------------------------------------------------------
// Count the number of resources of any type in all opened resource maps.

OSErr
UResources::CountAllResources(short & outCount)
{
	short numTypes;
	short subCount;
	ResType theType;

	OSErr error = CountAllTypes(numTypes);
	outCount = 0;
	
	if (error == noErr) {
		for ( UInt16 i = 1; i <= numTypes; i++ )
		{
			::GetIndType( &theType, i );
			CountForType(theType, subCount);
			outCount += subCount;
		}
	} 
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetWithID													[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given ID
// from any of the opened resource maps.

OSErr
UResources::GetWithID(ResType inType, short inID, Handle & outHandle)
{
	outHandle = ::GetResource(inType, inID);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetNamed														[public]
// ---------------------------------------------------------------------------
// Get a handle to a resource of a given type with a given name
// from any of the opened resource maps.

OSErr
UResources::GetNamed(ResType inType, ConstStr255Param inName, Handle & outHandle)
{
	outHandle = ::GetNamedResource(inType, inName);
	return ::ResError();
}


// ---------------------------------------------------------------------------
//  ¬€ GetAllTypes													[public]
// ---------------------------------------------------------------------------

OSErr
UResources::GetAllTypes( TArray<ResType>* & outArray )
{
	short numTypes;
	ResType theType;
	
	OSErr error = CountAllTypes(numTypes);
	
	if (error == noErr) {
		for ( UInt16 i = 1; i <= numTypes; i++ )
		{
			::GetIndType( &theType, i );
			error = ::ResError();
			if (error != noErr) {
				break;
			} 
			outArray->AddItem(theType);
		}
	} 
	return error;
}


// ---------------------------------------------------------------------------
//  ¬€ UniqueID														[public]
// ---------------------------------------------------------------------------

OSErr
UResources::UniqueID(ResType inType, short & outID)
{
	outID = ::UniqueID(inType);
	return ::ResError();
}



// ===========================================================================
//	StRezReferenceSaver stack-based class
// ===========================================================================
//
//	Constructor saves current resource refnum. Destructor restores it.

StRezReferenceSaver::StRezReferenceSaver()
{
	mOriginalRefNum = ::CurResFile();
}


StRezReferenceSaver::StRezReferenceSaver(
	SInt16 inRefNum)
{
	mOriginalRefNum = ::CurResFile();
	
	// refNum_Undef is always an invalid refNum
	if (inRefNum != UResources::refNum_Undef) {
		::UseResFile(inRefNum);
	}
}


StRezReferenceSaver::~StRezReferenceSaver()
{
	Restore();
}


void
StRezReferenceSaver::Restore()
{
	::UseResFile(mOriginalRefNum);
}


// ===========================================================================
//	¬€ StRezLoadSaver stack-based class
// ===========================================================================
//	See PP's StResLoad

StRezLoadSaver::StRezLoadSaver(
	Boolean inResLoad)
{
	mOriginalResLoad = ::LMGetResLoad();
	::SetResLoad(inResLoad);
}


StRezLoadSaver::~StRezLoadSaver()
{
	::SetResLoad(mOriginalResLoad);
}


