// ===========================================================================
// CAete.h
// 
//                       Created: 2005-01-21 07:27:26
//             Last modification: 2005-01-21 07:45:06
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

class CAeteStream;
class CAeteSuite;


class CAete {

public:
				CAete(CAeteStream *	inStream);
				~CAete();

		void		AddSuite( CAeteSuite * inSuite );
		void		AddSuite(Str255		inName,
							 Str255		inDescription,
							 OSType		inID, 
							 UInt16		inLevel,
							 UInt16		inVersion);
		void		RemoveSuite( ArrayIndexT inAtIndex );

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);


protected:
		UInt8					mMajorVersion;
		UInt8					mMinorVersion;
		SInt16					mLanguage;
		SInt16					mMScript;
		
		ArrayIndexT				mCurrSuiteIndex;
		TArray<CAeteSuite*>		mSuites;


private:


};


#endif
