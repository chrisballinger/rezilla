// ===========================================================================
// CAeteEnumeration.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 07:40:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteEnumeration
#define _H_CAeteEnumeration
#pragma once

struct AeteEnumerator {
	Str255	name;
	OSType	type;
	Str255	description;
};

class CAeteStream;
	
class CAeteEnumeration {

public:
				CAeteEnumeration(CAeteStream *	inStream);
				~CAeteEnumeration();

		ArrayIndexT		AddEnumerator(Str255 inName, OSType inType, Str255 inDescription);
		void			RemoveEnumerator( ArrayIndexT inAtIndex );
		void			InstallDataStream();
		void			SendDataToStream(CAeteStream *	outStream);

protected:
		OSType					mEnumerationID;
		ArrayIndexT				mCurrEnumeratorIndex;
		TArray<AeteEnumerator>	mEnumerators;


private:


};


#endif
