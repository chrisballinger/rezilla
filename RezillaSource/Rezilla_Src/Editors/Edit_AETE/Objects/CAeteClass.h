// ===========================================================================
// CAeteClass.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:45:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteClass
#define _H_CAeteClass
#pragma once

class CAeteStream;
class CAeteProperty;
class CAeteElement;


class CAeteClass {

public:
				CAeteClass(CAeteStream *	inStream);
				~CAeteClass();

		void		AddProperty( CAeteProperty * inProperty );
		void		AddProperty(Str255	inName,
								OSType	inID, 
								OSType	inType, 
								Str255	inDescription, 
								UInt16	inFlags);
		void		RemoveProperty( ArrayIndexT inAtIndex );

		void		AddElement( CAeteElement * inElement );
		void		AddElement( OSType inKeyForms[] );
		void		AddElement();
		void		RemoveElement( ArrayIndexT inAtIndex );

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);


protected:
		Str255					mName;
		OSType					mID;		// like capp, docu, cwin etc.
		Str255					mDescription;
		
		ArrayIndexT				mCurrPropertyIndex;
		ArrayIndexT				mCurrElementIndex;
		TArray<CAeteProperty*>	mProperties;
		TArray<CAeteElement*>	mElements;


private:


};


#endif
