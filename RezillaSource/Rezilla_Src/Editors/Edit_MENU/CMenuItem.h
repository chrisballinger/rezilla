// ===========================================================================
// CMenuItem.h
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 09:56:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CMenuItem
#define _H_CMenuItem
#pragma once


class LHandleStream;

class CMenuItem {

public:
				CMenuItem();
				CMenuItem(Str255	inName,
							OSType	inKeyword, 
							OSType	inType, 
							Str255	inDescription, 
							UInt16	inFlags);
				CMenuItem(LHandleStream * inStream);
				~CMenuItem();

		void		InstallDataStream(LHandleStream * inStream);
		void		SendDataToStream(LHandleStream * outStream);
		
		void		GetValues(Str255 outName, OSType & outKeyword, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags);
		
		void 		SetValues(Str255 inName, OSType inKeyword, OSType inType, 
					   Str255 inDescription, UInt16 inFlags);

protected:
		Str255		mName;
		OSType		mKeyword;
		OSType		mType;
		Str255		mDescription;
		UInt16		mFlags;

private:


};


#endif
