// ===========================================================================
// CAete.cp
// 
//                       Created: 2005-01-21 07:27:26
//             Last modification: 2005-01-21 07:45:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAete.h"
#include "CAeteStream.h"
#include "CAeteSuite.h"


// ---------------------------------------------------------------------------
//  CAete												[public]
// ---------------------------------------------------------------------------

CAete::CAete()
{
	mMajorVersion = 1;
	mMinorVersion = 0;
	mLanguage = 0;			// 0 is English
	mScript = 0;			// 0 is Roman
	mSuiteIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAete												[public]
// ---------------------------------------------------------------------------

CAete::CAete(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAete												[public]
// ---------------------------------------------------------------------------

CAete::~CAete()
{

	TArrayIterator<CAeteSuite*> iteraror(mSuites, LArrayIterator::from_End);
	CAeteSuite *	theSuite;
	while (iteraror.Previous(theSuite)) {
		mSuites.RemoveItemsAt(1, iteraror.GetCurrentIndex());
		delete theSuite;
	}
}


// ---------------------------------------------------------------------------
//  AddSuite												[public]
// ---------------------------------------------------------------------------

void
CAete::AddSuite()
{
	mSuites.AddItem( new CAeteSuite() );
}


// ---------------------------------------------------------------------------
//  AddSuite												[public]
// ---------------------------------------------------------------------------

void
CAete::AddSuite( CAeteSuite * inSuite )
{
	mSuites.AddItem(inSuite);
}


// ---------------------------------------------------------------------------
//  AddSuite												[public]
// ---------------------------------------------------------------------------

void
CAete::AddSuite(Str255	inName,
				 Str255	inDescription,
				 OSType	inID, 
				 UInt16	inLevel,
				 UInt16	inVersion)
{
	mSuites.AddItem( new CAeteSuite( inName, inDescription, inID,
											inLevel, inVersion) );
}


// ---------------------------------------------------------------------------
//  RemoveProperty												[public]
// ---------------------------------------------------------------------------

void
CAete::RemoveSuite( ArrayIndexT inAtIndex )
{
	CAeteSuite *	theSuite;
	if ( mSuites.FetchItemAt( inAtIndex, theSuite) ) {
		if (theSuite != NULL) {
			delete theSuite;
		} 
		mSuites.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAete::InstallDataStream(CAeteStream * inStream)
{	
	UInt16			theCount, i;
	CAeteSuite *	theSuite;
	
	*inStream >> mMajorVersion;
	*inStream >> mMinorVersion;
	*inStream >> mLanguage;
	*inStream >> mScript;
		
	// Get the count of suites
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theSuite = new CAeteSuite(inStream);
		AddSuite(theSuite);
	}
	// Initialize to 1 if there are parameters, 0 otherwise
	mSuiteIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAete::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mMajorVersion;
	*outStream << mMinorVersion;
	*outStream << mLanguage;
	*outStream << mScript;
	
	// Suites data
	*outStream << (UInt16) mSuites.GetCount();

	TArrayIterator<CAeteSuite*> iteraror( mSuites );
	CAeteSuite *	theSuite;
	
	while (iteraror.Next(theSuite)) {
		theSuite->SendDataToStream(outStream);
	}
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAete::GetValues(UInt8 & outMajorVersion, UInt8 & outMinorVersion,
					SInt16 & outLanguage, SInt16 & outScript)
{
	outMajorVersion = mMajorVersion;
	outMinorVersion = mMinorVersion;
	outLanguage = mLanguage;
	outScript = mScript;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAete::SetValues(UInt8 inMajorVersion, UInt8 inMinorVersion,
					SInt16 inLanguage, SInt16 inScript)
{
	mMajorVersion = inMajorVersion;
	mMinorVersion = inMinorVersion;
	mLanguage = inLanguage;
	mScript = inScript;
}

