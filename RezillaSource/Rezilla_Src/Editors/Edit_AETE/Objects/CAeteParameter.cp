// ===========================================================================
// CAeteParameter.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-19 17:02:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteParameter.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"

#include <LString.h>

// ---------------------------------------------------------------------------
//  CAeteParameter												[public]
// ---------------------------------------------------------------------------

CAeteParameter::CAeteParameter()
{
	mName[0] = 0;
	mKeyword = 0;
	mType = 0;
	mDescription[0] = 0;
	mFlags = 0;
}


// ---------------------------------------------------------------------------
//  CAeteParameter												[public]
// ---------------------------------------------------------------------------

CAeteParameter::CAeteParameter(Str255	inName,
							OSType	inKeyword, 
							OSType	inType, 
							Str255	inDescription, 
							UInt16	inFlags)
{
	SetValues( inName, inKeyword, inType, inDescription, inFlags);
}


// ---------------------------------------------------------------------------
//  CAeteParameter												[public]
// ---------------------------------------------------------------------------

CAeteParameter::CAeteParameter(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteParameter												[public]
// ---------------------------------------------------------------------------

CAeteParameter::~CAeteParameter()
{
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::InstallDataStream(CAeteStream * inStream)
{
	*inStream >> mName;
	inStream->AlignBytesRead();

	*inStream >> mKeyword;
	*inStream >> mType;
	
	*inStream >> mDescription;
	inStream->AlignBytesRead();

	*inStream >> mFlags;
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	outStream->AlignBytesWrite();
	*outStream << mKeyword;
	*outStream << mType;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	*outStream << mFlags;
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::GetValues(Str255 outName, OSType & outKeyword, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outKeyword = mKeyword;
	outType = mType;
	outFlags = mFlags;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteParameter::SetValues(Str255 inName, OSType inKeyword, OSType inType, 
					   Str255 inDescription, UInt16 inFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mKeyword = inKeyword;
	mType = inType;
	mFlags = inFlags;
}


// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteParameter::GetDataFromXml(CFXMLTreeRef inTreeNode)
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
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ParameterName"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mName);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ParameterID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mKeyword);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ParameterType"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mType);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ParameterDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ParameterFlags"), 0) ) {
					UMiscUtils::GetValueFromXml(xmlTree, theLong);
					mFlags = theLong;
				} else {
					error = err_ImportUnknownAeteParameterTag;	
				}
				
				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}


