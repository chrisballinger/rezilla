// ===========================================================================
// CAeteClass.cp
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-20 12:42:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CAeteClass.h"
#include "CAeteStream.h"
#include "CAeteProperty.h"
#include "CAeteElement.h"
#include "RezillaConstants.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CAeteClass												[public]
// ---------------------------------------------------------------------------

CAeteClass::CAeteClass()
{
	mName[0] = 0;
	mID = 0;
	mDescription[0] = 0;
	mPropertyIndex = 0;
	mElementIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteClass												[public]
// ---------------------------------------------------------------------------

CAeteClass::CAeteClass(	Str255	inName,
						OSType	inID,
						Str255	inDescription)
{
	SetValues( inName, inID, inDescription);
	mPropertyIndex = 0;
	mElementIndex = 0;
}


// ---------------------------------------------------------------------------
//  CAeteClass												[public]
// ---------------------------------------------------------------------------

CAeteClass::CAeteClass(CAeteStream * inStream)
{
	InstallDataStream(inStream);
}


// ---------------------------------------------------------------------------
//  ~CAeteClass												[public]
// ---------------------------------------------------------------------------

CAeteClass::~CAeteClass()
{
	TArrayIterator<CAeteProperty*> iterarorProp(mProperties, LArrayIterator::from_End);
	CAeteProperty *	theProp;
	while (iterarorProp.Previous(theProp)) {
		mProperties.RemoveItemsAt(1, iterarorProp.GetCurrentIndex());
		delete theProp;
	}

	TArrayIterator<CAeteElement*> iterarorElem(mElements, LArrayIterator::from_End);
	CAeteElement *	theElement;
	while (iterarorElem.Previous(theElement)) {
		mElements.RemoveItemsAt(1, iterarorElem.GetCurrentIndex());
		delete theElement;
	}
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddProperty()
{
	mProperties.AddItem( new CAeteProperty() );
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddProperty( CAeteProperty * inProperty )
{
	mProperties.AddItem(inProperty);
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddProperty(Str255	inName,
						OSType	inID, 
						OSType	inType, 
						Str255	inDescription, 
						UInt16	inFlags)
{
	mProperties.AddItem( new CAeteProperty( inName, inID, inType,
											inDescription, inFlags) );
}


// ---------------------------------------------------------------------------
//  AddProperty												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteClass::AddProperty(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	CAeteProperty * theProperty = new CAeteProperty();
	mProperties.AddItem(theProperty);
	error = theProperty->GetDataFromXml(inTreeNode);
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveProperty												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::RemoveProperty( ArrayIndexT inAtIndex )
{
	CAeteProperty *	theProperty;
	if ( mProperties.FetchItemAt( inAtIndex, theProperty) ) {
		if (theProperty != NULL) {
			delete theProperty;
		} 
		mProperties.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement()
{
	mElements.AddItem( new CAeteElement() );
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement( CAeteElement * inElement )
{
	mElements.AddItem(inElement);
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AddElement( OSType inKeyForms[], UInt16 inCount )
{
	UInt16	i;
	CAeteElement * theElement = new CAeteElement();
	
	for (i = 0 ; i < inCount; i++) {
		theElement->AddKeyForm( inKeyForms[i] );
	}	
}


// ---------------------------------------------------------------------------
//  AddElement												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteClass::AddElement(CFXMLTreeRef inTreeNode)
{
	OSErr	error = noErr;
	CAeteElement * theElement = new CAeteElement();
	mElements.AddItem(theElement);
	error = theElement->GetDataFromXml(inTreeNode);
	return error;
}


// ---------------------------------------------------------------------------
//  RemoveElement												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::RemoveElement( ArrayIndexT inAtIndex )
{
	CAeteElement *	theElement;
	if ( mElements.FetchItemAt( inAtIndex, theElement) ) {
		if (theElement != NULL) {
			delete theElement;
		} 
		mElements.RemoveItemsAt(1, inAtIndex);
	} 
}


// ---------------------------------------------------------------------------
//  InstallDataStream												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::InstallDataStream(CAeteStream * inStream)
{
	UInt16	theCount, i;
	CAeteProperty *	theProperty;
	CAeteElement *	theElement;
	
	*inStream >> mName;
	inStream->AlignBytesRead();

	*inStream >> mID;
	
	*inStream >> mDescription;
	inStream->AlignBytesRead();
	
	// Get the count of properties
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theProperty = new CAeteProperty(inStream);
		AddProperty(theProperty);
	}
	// Initialize to 1 if there are parameters, 0 otherwise
	mPropertyIndex = (theCount > 0);

	// Get the count of elements
	*inStream >> theCount;
	for (i = 0 ; i < theCount; i++) {
		theElement = new CAeteElement(inStream);
		AddElement(theElement);
	}
	// Initialize to 1 if there are parameters, 0 otherwise
	mElementIndex = (theCount > 0);
}


// ---------------------------------------------------------------------------
//  SendDataToStream												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::SendDataToStream(CAeteStream * outStream)
{
	*outStream << mName;
	outStream->AlignBytesWrite();
	*outStream << mID;
	*outStream << mDescription;
	outStream->AlignBytesWrite();
	
	// Properties data
	*outStream << (UInt16) mProperties.GetCount();

	TArrayIterator<CAeteProperty*> iterProp( mProperties );
	CAeteProperty *	theProperty;
	
	while (iterProp.Next(theProperty)) {
		theProperty->SendDataToStream(outStream);
	}

	// Elements data
	*outStream << (UInt16) mElements.GetCount();

	TArrayIterator<CAeteElement*> iterElem( mElements );
	CAeteElement *	theElement;
	
	while (iterElem.Next(theElement)) {
		theElement->SendDataToStream(outStream);
	}
}


// ---------------------------------------------------------------------------
//  GetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::GetValues(Str255 outName, OSType & outID, Str255 outDescription)
{
	LString::CopyPStr(mName, outName);
	LString::CopyPStr(mDescription, outDescription);
	outID = mID;
}
 

// ---------------------------------------------------------------------------
//  SetValues												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::SetValues(Str255 inName, OSType inID, Str255 inDescription)
{
	LString::CopyPStr(inName, mName);
	LString::CopyPStr(inDescription, mDescription);
	mID = inID;
}


// ---------------------------------------------------------------------------
//  NewProperty													[public]
// ---------------------------------------------------------------------------
// Returns the new count of properties after addition. This is also the
// index of the new property.

SInt32
CAeteClass::NewProperty()
{	
	AddProperty();	
	return CountProperties();
}
 

// ---------------------------------------------------------------------------
// DeleteProperty 													[public]
// ---------------------------------------------------------------------------
// Deletes the property at current index. Returns the new count of
// properties after deletion.

SInt32
CAeteClass::DeleteProperty()
{
	RemoveProperty(mPropertyIndex);
	mPropertyIndex = -1;
	return CountProperties();
}
 

// ---------------------------------------------------------------------------
//  NewElement													[public]
// ---------------------------------------------------------------------------
// Returns the new count of elements after addition. This is also the
// index of the new element.

SInt32
CAeteClass::NewElement()
{	
	AddElement();
	return CountElements();
}
 

// ---------------------------------------------------------------------------
// DeleteElement 													[public]
// ---------------------------------------------------------------------------
// Deletes the element at current index. Returns the new count of
// elements after deletion.

SInt32
CAeteClass::DeleteElement()
{
	RemoveElement(mElementIndex);
	mElementIndex = -1;
	return CountElements();
}
 

// ---------------------------------------------------------------------------
//  AdjustCurrentIndex												[public]
// ---------------------------------------------------------------------------

void
CAeteClass::AdjustCurrentIndex(SInt8 inKind)
{
	switch (inKind) {
		case kind_AeteProperty:
		if ( mPropertyIndex == 0 ) {
			mPropertyIndex = (CountProperties() > 0);
		} else if ( mPropertyIndex > CountProperties() ) {
			mPropertyIndex = CountProperties();
		} 
		break;
		
		case kind_AeteElement:
		if ( mElementIndex == 0 ) {
			mElementIndex = (CountElements() > 0);
		} else if ( mElementIndex > CountElements() ) {
			mElementIndex = CountElements();
		} 
		break;
		
	}	
}
 

// ---------------------------------------------------------------------------
//  GetDataFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteClass::GetDataFromXml(CFXMLTreeRef inTreeNode)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;
	
	childCount = CFTreeGetChildCount(inTreeNode);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeNode, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ClassName"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mName);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ClassID"), 0) ) {
					error = UMiscUtils::GetOSTypeFromXml(xmlTree, mID);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ClassDescription"), 0) ) {
					UMiscUtils::GetStringFromXml(xmlTree, mDescription);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayProperties"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteProperty);
				} else if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("ArrayElements"), 0) ) {
					error = GetArrayFromXml(xmlTree, kind_AeteElement);
				} else {
					CFShow(CFXMLNodeGetString(xmlNode));
					error = err_ImportUnknownAeteClassTag;	
				}
				
				if (error != noErr) { break; } 
			} 
		} 
	}
	
	return error;
}


// ---------------------------------------------------------------------------
//  GetArrayFromXml												[public]
// ---------------------------------------------------------------------------

OSErr
CAeteClass::GetArrayFromXml(CFXMLTreeRef inTreeRef, SInt8 inKind)
{
	OSErr			error = noErr;
	int             childCount;
	CFXMLTreeRef    xmlTree;
	CFXMLNodeRef    xmlNode;
	int             index;

	childCount = CFTreeGetChildCount(inTreeRef);
	for (index = 0; index < childCount; index++) {
		xmlTree = CFTreeGetChildAtIndex(inTreeRef, index);
		if (xmlTree) {
			xmlNode = CFXMLTreeGetNode(xmlTree);
			if (xmlNode) {
				switch (inKind) {
					case kind_AeteProperty:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("Property"), 0) ) {
						error = AddProperty(xmlTree);
					}
					break;
					
					case kind_AeteElement:
					if ( ! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("Element"), 0) ) {
						error = AddElement(xmlTree);
					}
					break;
					
				}	
			} 			
		} 
		if (error != noErr) { break; } 
	}
	AdjustCurrentIndex(inKind);

	return error;
}



