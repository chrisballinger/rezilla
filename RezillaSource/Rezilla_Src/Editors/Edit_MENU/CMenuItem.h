// ===========================================================================
// CMenuItem.h
// 
//                       Created: 2005-03-10 09:12:57
//             Last modification: 2005-03-10 18:52:23
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
				CMenuItem(Str255	inTitle,
							UInt8	inIconID, 
							UInt8	inShortcut, 
							UInt8	inMark, 
							UInt8	inStyle);
				CMenuItem(LHandleStream * inStream);
				~CMenuItem();

		void		InstallDataStream(LHandleStream * inStream);
		void		SendDataToStream(LHandleStream * outStream);
		
		void		GetValues(Str255 outTitle, UInt8 & outIconID, UInt8 & outShortcut, 
					   UInt8 outMark, UInt8 & outStyle);
		
		void 		SetValues(Str255 inTitle, UInt8 inIconID, UInt8 inShortcut, 
					   UInt8 inMark, UInt8 inStyle);

protected:
		Str255		mTitle;
		UInt8		mIconID;
		UInt8		mShortcut;
		UInt8		mMark;
		UInt8		mStyle;

private:


};


#endif
