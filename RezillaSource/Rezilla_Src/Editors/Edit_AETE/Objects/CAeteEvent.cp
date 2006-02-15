// ===========================================================================
// CAeteEvent.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-19 16:46:30
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#include "CAeteEvent.h"
#include "CAeteStream.h"
#include "CAeteParameter.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent()
{
	mName[0] = 0;
	mDescription[0] = 0;
	mClass = 0;
	mID = 0;
	mReplyType = 0;
	mReplyDescription[0] = 0;
	mReplyFlags = 0;
	mDirectType = 0;
	mDirectDescription[0] = 0;
	mDirectFlags = 0;
	mParameterIndex = 0;	
}


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent(	Str255	inName,
						Str255	inDescription,
						OSType	inClass, 
						OSType	inID,
						OSType	inReplyType,
						Str255	inReplyDescription,
						UInt16	inReplyFlags,
						OSType	inDirectType,
						Str255	inDirectDescription,
						UInt16	inDirectFlags)
{
	SetValues(inName, inDescription, inClass, inID, 
			  inReplyType, inReplyDescription, inReplyFlags,
			  inDirectType, inDirectDescription, inDirectFlags);
	mParameterIndex = 0;	
}


// ---------------------------------------------------------------------------
//  CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::CAeteEvent(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteEvent												[public]
// ---------------------------------------------------------------------------

CAeteEvent::~CAeteEvent()
{
	TArrayIterator<CAeteParameter*> iteraror(mParameters, LArrayIterator::from_End);
	CAeteParameter *	theParam;
	while (iteraror.Previous(theParam)) {
		mParameters.RemoveItemsAt(1, iteraror.GetCurrentIndex());
		delete theParam;
	}
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter()
{
	mParameters.AddItem( new CAeteParameter() );
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter(CAeteParameter * inParameter)
{
	mParameters.AddItem(inParameter);
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::AddParameter(Str255	inName,
						OSType	inKeyword, 
						OSType	inType, 
						Str255	inDescription, 
						UInt16	inFlags)
{
	mParameters.AddItem( new CAeteParameter( inName, inKeyword, inType,
											inDescription, inFlags) );
}


// ---------------------------------------------------------------------------
//  AddParameter												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteEvent::AddParameter(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	CAeteParameter * theParameter = new CAeteParameter();
	mParameters.AddItem(theParameter);
	error = theParameter->GetDataFromXml(inTreeNode);
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveParameter												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::RemoveParameter( ArrayIndexT inAtIndex )
{
	CAeteParameter *	theParameter;
	if ( mParameters.FetchItemAt( inAtIndex, theParameter) ) {
		if (theParameter != NULL) {
			delete theParameter;
		} 
		mParameters.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::InstallDataStream(CAeteStream * inStream)
{
	UInt16				theCount, i;
	CAeteParameter *	theParameter;
	
	*inStream >> mName;
	*inStream >> mDescription;
	inStream->AlignBytesRead();
	
	*inStream >> mClass;
	*inStream >> mID;

	*inStream >> mReplyType;
	*inStream >> mReplyDescription;
	inStream->AlignBytesRead();
	*inStream >> mReplyFlags;

	*inStream >> mDirectType;
	*inStream >> mDirectDescription;
	inStream->AlignBytesRead();
	*inStream >> mDirectFlags;

	// Get the count of parameters
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theParameter = new CAeteParameter(inStream);
		AddParameter(theParameter);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mParameterIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	
	*outStream << mClass;
	*outStream << mID;
	*outStream << mReplyType;
	*outStream << mReplyDescription;
	outStream->AlignBytesWrite();
	*outStream << mReplyFlags;
	
	*outStream << mDirectType;
	*outStream << mDirectDescription;
	outStream->AlignBytesWrite();
	*outStream << mDirectFlags;

	// Parameters data
	*outStream << (UInt16) mParameters.GetCount();

	TArrayIterator<CAeteParameter*> iterator( mParameters );
	CAeteParameter *	theParameter;
	
	while (iterator.Next(theParameter)) {
		theParameter->SendDataToStream(outStream);
	}
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::GetValues( Str255 & outName, Str255 outDescription,
					   OSType & outClass, OSType & outID,
					   OSType & outReplyType, Str255 outReplyDescription, UInt16 & outReplyFlags,
					   OSType & outDirectType, Str255 outDirectDescription, UInt16 & outDirectFlags)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	LString::CopyPStr(mReplyDescription, outReplyDescription);
	LString::CopyPStr(mDirectDescription, outDirectDescription);
	outClass = mClass;
	outID = mID;
	outReplyType = mReplyType;
	outReplyFlags = mReplyFlags;
	outDirectType = mDirectType;
	outDirectFlags = mDirectFlags;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteEvent::SetValues( Str255 inName, Str255 inDescription,
					   OSType inClass, OSType inID,
					   OSType inReplyType, Str255 inReplyDescription, UInt16 inReplyFlags,
					   OSType inDirectType, Str255 inDirectDescription, UInt16 inDirectFlags)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	LString::CopyPStr(inReplyDescription, mReplyDescription);
	LString::CopyPStr(inDirectDescription, mDirectDescription);
	mClass = inClass;
	mID = inID;
	mReplyType = inReplyType;
	mReplyFlags = inReplyFlags;
	mDirectType = inDirectType;
	mDirectFlags = inDirectFlags;
}


// ---------------------------------------------------------------------------
//  NewParameter													[public]
// ---------------------------------------------------------------------------
// Returns the new count of parameters after addition. This is also the
// index of the new parameter.

SInt32
CAeteEvent::NewParameter()
{	
	AddParameter();
	return CountParameters();
}
 

// ---------------------------------------------------------------------------
// DeleteParameter 													[public]
// ---------------------------------------------------------------------------
// Deletes the parameter at current index. Returns the new count of
// parameters after deletion.

SInt32
CAeteEvent::DeleteParameter()
{
	RemoveParameter(mParameterIndex);
	mParameterIndex = -1;
	return CountParameters();
}
 

// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteEvent::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount, subCount;
	CFXMLTreeRef    xmlTree, subTree;
	CFXMLNodeRef    xmlNode, subNode;
	int             index, subIndex;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EventName"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mName);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EventDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EventClass"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mClass);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EventID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ReplyType"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mReplyType);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ReplyDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mReplyDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ReplyFlags"), 0) ) {
					error = UMiscUtils::GetFlagsFromXml(xmlTree, mReplyFlags);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("DirectParamType"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mDirectType);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("DirectParamDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mDirectDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("DirectFlags"), 0) ) {
					error = UMiscUtils::GetFlagsFromXml(xmlTree, mDirectFlags);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayOtherParams"), 0) ) {
					subCount = CFTreeGetChildCount(xmlTree);
					for (subIndex = 0; subIndex < subCount; subIndex++) {
						subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
						if (subTree) {
							subNode = CFXMLTreeGetNode(subTree);
							if (subNode) {
								if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Parameter"), 0) ) {
									error = AddParameter(subTree);
									if (error != noErr) { break; } 
								}
							} 
						} 
					}
					mParameterIndex = (CountParameters() > 0);
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteEventTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}


