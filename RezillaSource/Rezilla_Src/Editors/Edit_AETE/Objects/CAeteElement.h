// ===========================================================================
// CAeteElement.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-20 15:05:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CAeteElement
#define _H_CAeteElement
#pragma once

#include <CFXMLNode.h>

class CAeteStream;

class CAeteElement {

public:
				CAeteElement(OSType inID = 0);
				CAeteElement(CAeteStream *	inStream);
				~CAeteElement();

		void		InstallDataStream(CAeteStream * inStream);
		void		SendDataToStream(CAeteStream *	outStream);

		ArrayIndexT	AddKeyForm( OSType inKey = 0);
		OSErr		AddKeyForm(CFXMLTreeRef inTreeNode);
		void		RemoveKeyForm( ArrayIndexT inAtIndex );
		
		SInt32		NewKeyForm();
		SInt32		DeleteKeyForm();

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		Boolean		GetCurrentKeyForm(OSType & outKeyForm);
		void		SetCurrentKeyForm(OSType inKeyForm);
		
		OSType		GetID() { return mID;}
		void		SetID(OSType inID) {mID = inID;}

		ArrayIndexT	GetKeyFormIndex() { return mKeyFormIndex;}
		void		SetKeyFormIndex(ArrayIndexT inKeyFormIndex) {mKeyFormIndex = inKeyFormIndex;}

		SInt32		CountKeyForms() { return mKeyForms.GetCount(); }
	
		TArray<OSType> *	GetKeyForms() { return &mKeyForms;}

protected:
	OSType			mID;
	ArrayIndexT		mKeyFormIndex;
	TArray<OSType>  mKeyForms;

private:

};


#endif
