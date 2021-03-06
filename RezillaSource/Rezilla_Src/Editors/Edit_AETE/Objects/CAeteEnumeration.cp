// ===========================================================================
// CAeteEnumeration.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-07-05 08:33:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#include "CAeteEnumeration.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::CAeteEnumeration(OSType inID)
{
	mEnumerationID = inID;
	mEnumeratorIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::CAeteEnumeration(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteEnumeration												[public]
// ---------------------------------------------------------------------------

CAeteEnumeration::~CAeteEnumeration()
{
}


// ---------------------------------------------------------------------------
//  AddEnumerator												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteEnumeration::AddEnumerator()
{
	AeteEnumerator	numerator;
	
	numerator.type = 0;
	numerator.name[0] = 0;
	numerator.description[0] = 0;
	
	return ( mEnumerators.AddItem(numerator) );
}


// ---------------------------------------------------------------------------
//  AddEnumerator												[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteEnumeration::AddEnumerator(Str255 inName, OSType inType, Str255 inDescription)
{
	AeteEnumerator	numerator;
	
	numerator.type = inType;
	LString::CopyPStr(inName, numerator.name);
	LString::CopyPStr(inDescription, numerator.description);
	
	return ( mEnumerators.AddItem(numerator) );
}


// ---------------------------------------------------------------------------
//  AddEnumerator												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteEnumeration::AddEnumerator(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	AeteEnumerator	numerator;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;
	
	numerator.type = 0;
	numerator.name[0] = 0;
	numerator.description[0] = 0;

	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EnumeratorName"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, numerator.name);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EnumeratorID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, numerator.type);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EnumeratorDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, numerator.description);
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteEnumeratorTag;	
				}
				
				if (error != noErr) { break; } 
			} 
		} 
	}
	
	if (error == noErr) {
		mEnumerators.AddItem(numerator);
		mEnumeratorIndex = (CountEnumerators() > 0);
	} 

	return error;
}


// ---------------------------------------------------------------------------
//  RemoveEnumerator												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::RemoveEnumerator( ArrayIndexT inAtIndex )
{
	mEnumerators.RemoveItemsAt(1, inAtIndex);
}


// ---------------------------------------------------------------------------
//  GetEnumerator												[public]
// ---------------------------------------------------------------------------

Boolean
CAeteEnumeration::GetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator & outEnumerator)
{
	Boolean hasEnumerator = mEnumerators.FetchItemAt(inAtIndex, outEnumerator);
	if (!hasEnumerator) {
		outEnumerator.type = 0;
		outEnumerator.name[0] = 0;
		outEnumerator.description[0] = 0;
	} 
	return hasEnumerator;
}


// ---------------------------------------------------------------------------
//  SetEnumerator												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::SetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator inEnumerator)
{
	if (inAtIndex == 0) { return; } 
	RemoveEnumerator(inAtIndex);
	mEnumerators.InsertItemsAt(1, inAtIndex, inEnumerator);
}

	
// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::InstallDataStream(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;
	Str255	theName, theDescr;
	
	*inStream >> mEnumerationID;
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		*inStream >> theName;
		inStream->AlignBytesRead();

		*inStream >> theType;
		
		*inStream >> theDescr;
		inStream->AlignBytesRead();
		
		AddEnumerator(theName, theType, theDescr);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mEnumeratorIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteEnumeration::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mEnumerationID;
	
	// KeyForms data
	*outStream << (UInt16) mEnumerators.GetCount();
	
	TArrayIterator<AeteEnumerator> iterator( mEnumerators );
	AeteEnumerator 	numerator;
	
	while (iterator.Next(numerator)) {
		*outStream << numerator.name;
		outStream->AlignBytesWrite();
		*outStream << numerator.type;
		*outStream << numerator.description;
		outStream->AlignBytesWrite();
	}
	
}


// ---------------------------------------------------------------------------
//  NewEnumerator													[public]
// ---------------------------------------------------------------------------
// Returns the new count of enumerators after addition. This is also the
// index of the new enumerator.

SInt32
CAeteEnumeration::NewEnumerator()
{	
	AddEnumerator();
	return CountEnumerators();
}
 

// ---------------------------------------------------------------------------
// DeleteEnumerator 												[public]
// ---------------------------------------------------------------------------
// Deletes the enumerator at current index. Returns the new count of
// enumerators after deletion.

SInt32
CAeteEnumeration::DeleteEnumerator()
{
	RemoveEnumerator(mEnumeratorIndex);
	mEnumeratorIndex = -1;
	return CountEnumerators();
}
 

// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteEnumeration::GetDataFromXml(CFXMLTreeRef inTreeNode)
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
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("EnumerationID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mEnumerationID);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayEnumerators"), 0) ) {
					subCount = CFTreeGetChildCount(xmlTree);
					for (subIndex = 0; subIndex < subCount; subIndex++) {
						subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
						if (subTree) {
							subNode = CFXMLTreeGetNode(subTree);
							if (subNode) {
								if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("Enumerator"), 0) ) {
									error = AddEnumerator(subTree);
									if (error != noErr) { break; } 
								}
							} 
						} 
					}
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteEnumerationTag;	
				}
				
				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}



