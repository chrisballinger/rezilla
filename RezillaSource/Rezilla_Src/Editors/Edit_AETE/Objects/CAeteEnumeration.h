// ===========================================================================
// CAeteEnumeration.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-20 14:50:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CAeteEnumeration
#define _H_CAeteEnumeration
#pragma once

#include <CFXMLNode.h>

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
		OSErr			AddEnumerator(CFXMLTreeRef inTreeNode);
		void			RemoveEnumerator( ArrayIndexT inAtIndex );

		SInt32			NewEnumerator();
		SInt32			DeleteEnumerator();

		OSErr			GetDataFromXml(CFXMLTreeRef inTreeNode);
		
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
