// ===========================================================================
// CAete.cp
// 
//                       Created: 2005-01-21 07:27:26
//             Last modification: 2005-01-30 21:00:58
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
#include "RezillaConstants.h"
#include "UMiscUtils.h"


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
//  AddSuite												[public]
// ---------------------------------------------------------------------------

OSErr
CAete::AddSuite(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	CAeteSuite * theSuite = new CAeteSuite();
	mSuites.AddItem(theSuite);
	error = theSuite->GetDataFromXml(inTreeNode);
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveSuite														[public]
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


// ---------------------------------------------------------------------------
//  AdjustSuiteIndex												[public]
// ---------------------------------------------------------------------------

void
CAete::AdjustSuiteIndex()
{
	if ( mSuiteIndex == 0 ) {
		mSuiteIndex = (mSuites.GetCount() > 0);
	} else if ( mSuiteIndex > mSuites.GetCount() ) {
		mSuiteIndex = mSuites.GetCount();
	} 
}


// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAete::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount, subCount;
	CFXMLTreeRef    xmlTree, subTree;
	CFXMLNodeRef    xmlNode, subNode;
	int             index, subIndex;
	SInt32			theLong;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("MajorVersion"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mMajorVersion = theLong;			
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("MinorVersion"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mMinorVersion = theLong;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("LanguageCode"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mLanguage = theLong;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ScriptCode"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mScript = theLong;
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArraySuites"), 0) ) {
					subCount = CFTreeGetChildCount(xmlTree);
					for (subIndex = 0; subIndex < subCount; subIndex++) {
						subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
						if (subTree) {
							subNode = CFXMLTreeGetNode(subTree);
							if (subNode) {
								if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Suite"), 0) ) {
									error = AddSuite(subTree);
									if (error != noErr) { break; } 
								}
							} 
						} 
					}
					AdjustSuiteIndex();
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					// At this level, ignore unknown tags. This allows to 
					// insert AeteResID and AeteResTitle extraneous tags.
// 					error = err_ImportUnknownAeteResourceTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}

	return error;
}


