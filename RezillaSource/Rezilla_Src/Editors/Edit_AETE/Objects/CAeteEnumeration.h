// ===========================================================================
// CAeteEnumeration.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-26 06:53:36
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

		void			InstallDataStream(CAeteStream * inStream);
		void			SendDataToStream(CAeteStream *	outStream);

		ArrayIndexT		AddEnumerator();
		ArrayIndexT		AddEnumerator(Str255 inName, OSType inType, Str255 inDescription);
		void			RemoveEnumerator( ArrayIndexT inAtIndex );

		OSType			GetEnumerationID() { return mEnumerationID;}
		void			SetEnumerationID(OSType inEnumerationID) {mEnumerationID = inEnumerationID;}

		ArrayIndexT		GetEnumeratorIndex() { return mEnumeratorIndex;}
		void			SetEnumeratorIndex(ArrayIndexT inEnumeratorIndex) {mEnumeratorIndex = inEnumeratorIndex;}

		Boolean			GetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator & outEnumerator);
		void			SetEnumerator(ArrayIndexT inAtIndex, AeteEnumerator inEnumerator);
	
		SInt32			CountEnumerators() { return mEnumerators.GetCount(); }

		TArray<AeteEnumerator> *	GetEnumerators() { return &mEnumerators;}

protected:
		OSType					mEnumerationID;
		ArrayIndexT				mEnumeratorIndex;
		TArray<AeteEnumerator>	mEnumerators;

private:

};


#endif
