// ===========================================================================
// CAeteParameter.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 08:53:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteParameter
#define _H_CAeteParameter
#pragma once

class CAeteStream;

class CAeteParameter {

public:
				CAeteParameter();
				CAeteParameter(Str255	inName,
							OSType	inKeyword, 
							OSType	inType, 
							Str255	inDescription, 
							UInt16	inFlags);
				CAeteParameter(CAeteStream * inStream);
				~CAeteParameter();

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

protected:
		Str255		mName;
		OSType		mKeyword;		// like kfil, kocl, data etc.
		OSType		mType;			// like alis, type, **** etc.
		Str255		mDescription;
		UInt16		mFlags;

private:


};


#endif
