// ===========================================================================
// CAeteProperty.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-19 17:05:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteProperty.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty()
{
	mName[0] = 0;
	mID = 0;
	mType = 0;
	mDescription[0] = 0;
	mFlags = 0;
}


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty(Str255 inName, 
							  OSType inID, 
							  OSType inType, 
							  Str255 inDescription, 
							  UInt16 inFlags)
{
	SetValues( inName, inID, inType, inDescription, inFlags);
}


// ---------------------------------------------------------------------------
//  CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::CAeteProperty(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteProperty												[public]
// ---------------------------------------------------------------------------

CAeteProperty::~CAeteProperty()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::InstallDataStream(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytesRead();

	*inStream >> mID;
	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytesRead();

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	outStream->AlignBytesWrite();
	*outStream << mID;
	*outStream << mType;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	*outStream << mFlags;
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::GetValues(Str255 outName, OSType & outID, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outID = mID;
	outType = mType;
	outFlags = mFlags;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteProperty::SetValues(Str255 inName, OSType inID, OSType inType, 
					   Str255 inDescription, UInt16 inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mID = inID;
	mType = inType;
	mFlags = inFlags;
}


// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteProperty::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;
	SInt32			theLong;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		xmlNode = CFXMLTreeGetNode(xmlTree);

		if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("PropertyName"), 0) ) {
			UMiscUtils::GetStringFromXml(xmlTree, mName);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("PropertyID"), 0) ) {
			UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("PropertyClass"), 0) ) {
			UMiscUtils::GetOSTypeFromXml(xmlTree, mType);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("PropertyDescription"), 0) ) {
			UMiscUtils::GetStringFromXml(xmlTree, mDescription);
		} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("PropertyFlags"), 0) ) {
			UMiscUtils::GetValueFromXml(xmlTree, theLong);
			mFlags = theLong;
		} 
	}
	
	return error;
}


