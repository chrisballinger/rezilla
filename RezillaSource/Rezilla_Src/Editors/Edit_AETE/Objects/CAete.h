// ===========================================================================
// CAete.h
// 
//                       Created: 2005-01-21 07:27:26
//             Last modification: 2005-02-19 13:25:13
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAete
#define _H_CAete
#pragma once

#include <CFXMLNode.h>

class CAeteStream;
class CAeteSuite;


class CAete {

public:
				CAete();
				CAete(CAeteStream *	inStream);
				~CAete();

		void		AddSuite();
		void		AddSuite( CAeteSuite * inSuite );
		void		AddSuite(Str255		inName,
							 Str255		inDescription,
							 OSType		inID, 
							 UInt16		inLevel,
							 UInt16		inVersion);
		void		RemoveSuite( ArrayIndexT inAtIndex );

		void		InstallDataStream(CAeteStream * inStream);
		void		SendDataToStream(CAeteStream * outStream);

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		void		GetValues(UInt8 & outMajorVersion, UInt8 & outMinorVersion,
							SInt16 & outLanguage, SInt16 & outScript);
		
		void		SetValues(UInt8 inMajorVersion, UInt8 inMinorVersion,
							SInt16 inLanguage, SInt16 inScript);
			
		ArrayIndexT		GetSuiteIndex() { return mSuiteIndex;}
		void			SetSuiteIndex(ArrayIndexT inSuiteIndex) {mSuiteIndex = inSuiteIndex;}
		void			AdjustSuiteIndex();
		
		SInt32			CountSuites() { return mSuites.GetCount(); }
		
		TArray<CAeteSuite*> *	GetSuites() { return &mSuites;}

protected:
		UInt8					mMajorVersion;
		UInt8					mMinorVersion;
		SInt16					mLanguage;
		SInt16					mScript;
		ArrayIndexT				mSuiteIndex;
		TArray<CAeteSuite*>		mSuites;
		

private:


};


#endif
