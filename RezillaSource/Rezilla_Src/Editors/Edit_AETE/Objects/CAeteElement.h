// ===========================================================================
// CAeteElement.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:44:49
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
				CAeteElement(CAeteStream *	inStream);
				~CAeteElement();

		ArrayIndexT	AddKeyForm( OSType inKey);
		void		RemoveKeyForm( ArrayIndexT inAtIndex );
		void		InstallDataStream();
		void		SendDataToStream(CAeteStream *	outStream);

protected:
	OSType			mID;
	ArrayIndexT		mCurrKeyFormIndex;
	TArray<OSType>  mKeyForms;


private:


};


#endif
