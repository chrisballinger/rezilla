// ===========================================================================
// CAeteEnumeration.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 10:24:17
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
				CAeteEnumeration(OSType inID = 0);
				CAeteEnumeration(CAeteStream *	inStream);
				~CAeteEnumeration();

		ArrayIndexT		AddEnumerator();
		ArrayIndexT		AddEnumerator(Str255 inName, OSType inType, Str255 inDescription);
		void			RemoveEnumerator( ArrayIndexT inAtIndex );
		void			InstallDataStream();
		void			SendDataToStream(CAeteStream *	outStream);

		OSType			GetEnumerationID() { return mEnumerationID;}
		void			SetEnumerationID(OSType inEnumerationID) {mEnumerationID = inEnumerationID;}

		ArrayIndexT		GetEnumeratorIndex() { return mEnumeratorIndex;}
		void			SetEnumeratorIndex(ArrayIndexT inEnumeratorIndex) {mEnumeratorIndex = inEnumeratorIndex;}

		TArray<AeteEnumerator> *	GetEnumerators() { return &mEnumerators;}

protected:
		OSType					mEnumerationID;
		ArrayIndexT				mEnumeratorIndex;
		TArray<AeteEnumerator>	mEnumerators;

private:

};


#endif
