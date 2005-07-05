// ===========================================================================
// CAeteElement.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-07-05 08:33:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteElement.h"
#include "CAeteStream.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::CAeteElement(OSType inID)
{
	mID = inID;
	mKeyFormIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::CAeteElement(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteElement													[public]
// ---------------------------------------------------------------------------

CAeteElement::~CAeteElement()
{
}


// ---------------------------------------------------------------------------
//  AddKeyForm														[public]
// ---------------------------------------------------------------------------

ArrayIndexT
CAeteElement::AddKeyForm( OSType inKey )
{
	return ( mKeyForms.AddItem(inKey) );
}


// ---------------------------------------------------------------------------
//  AddKeyForm														[public]
// ---------------------------------------------------------------------------

OSErr
CAeteElement::AddKeyForm(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	OSType	theKey = 0;
	
	error = UMiscUtils::GetOSTypeFromXml(inTreeNode, theKey);

	if (error == noErr) {
		mKeyForms.AddItem(theKey);
		mKeyFormIndex = (CountKeyForms() > 0);
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveKeyForm													[public]
// ---------------------------------------------------------------------------

void
CAeteElement::RemoveKeyForm( ArrayIndexT inAtIndex )
{
	mKeyForms.RemoveItemsAt(1, inAtIndex);
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::InstallDataStream(CAeteStream * inStream)
{
	UInt16	theCount, i;
	OSType	theType;

	*inStream >> mID;

	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		*inStream >> theType;
		AddKeyForm(theType);
	}

	// Initialize to 1 if there are parameters, 0 otherwise
	mKeyFormIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mID;
	
	// KeyForms data
	*outStream << (UInt16) mKeyForms.GetCount();

	TArrayIterator<OSType> iterator( mKeyForms );
	OSType 	theKeyForm;
	
	while (iterator.Next(theKeyForm)) {
		*outStream << theKeyForm;
	}
}


// ---------------------------------------------------------------------------
//  NewKeyForm													[public]
// ---------------------------------------------------------------------------
// Returns the new count of KeyForms after addition. This is also the
// index of the new KeyForm.

SInt32
CAeteElement::NewKeyForm()
{	
	AddKeyForm();
	return CountKeyForms();
}
 

// ---------------------------------------------------------------------------
// DeleteKeyForm 													[public]
// ---------------------------------------------------------------------------
// Deletes the KeyForm at current index. Returns the new count of
// KeyForms after deletion.

SInt32
CAeteElement::DeleteKeyForm()
{
	RemoveKeyForm(mKeyFormIndex);
	mKeyFormIndex = -1;
	return CountKeyForms();
}


// ---------------------------------------------------------------------------
// GetCurrentKeyForm 												[public]
// ---------------------------------------------------------------------------

Boolean
CAeteElement::GetCurrentKeyForm(OSType & outKeyForm)
{
	Boolean	found = false;
	if ( mKeyForms.FetchItemAt(mKeyFormIndex, outKeyForm) ) {
		found = true;
	} 
	
	return found;
}


// ---------------------------------------------------------------------------
// SetCurrentKeyForm 												[public]
// ---------------------------------------------------------------------------

void
CAeteElement::SetCurrentKeyForm(OSType inKeyForm)
{
	mKeyForms.AssignItemsAt(1, mKeyFormIndex, inKeyForm);
}


// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteElement::GetDataFromXml(CFXMLTreeRef inTreeNode)
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
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ElementClass"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayKeyForms"), 0) ) {
					subCount = CFTreeGetChildCount(xmlTree);
					for (subIndex = 0; subIndex < subCount; subIndex++) {
						subTree = CFTreeGetChildAtIndex(xmlTree, subIndex);
						if (subTree) {
							subNode = CFXMLTreeGetNode(subTree);
							if (subNode) {
								if ( ! CFStringCompare( CFXMLNodeGetString(subNode), CFSTR("KeyFormID"), 0) ) {
									error = AddKeyForm(subTree);
									if (error != noErr) { break; } 
								}
							} 
						} 
					}
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteElementTag;	
				} 

				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}


