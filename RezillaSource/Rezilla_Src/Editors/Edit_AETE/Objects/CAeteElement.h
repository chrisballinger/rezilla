// ===========================================================================
// CAeteElement.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-02 07:04:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteElement
#define _H_CAeteElement
#pragma once

class CAeteStream;

class CAeteElement {

public:
				CAeteElement(OSType inID = 0);
				CAeteElement(CAeteStream *	inStream);
				~CAeteElement();

		void		InstallDataStream(CAeteStream * inStream);
		void		SendDataToStream(CAeteStream *	outStream);

		ArrayIndexT	AddKeyForm( OSType inKey = 0);
		void		RemoveKeyForm( ArrayIndexT inAtIndex );
		
		SInt32		NewKeyForm();
		SInt32		DeleteKeyForm();

		OSType		GetKeyForm(ArrayIndexT inKeyFormIndex);
		
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
