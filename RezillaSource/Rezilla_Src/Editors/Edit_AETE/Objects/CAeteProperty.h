// ===========================================================================
// CAeteProperty.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-20 14:22:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteProperty
#define _H_CAeteProperty
#pragma once

class CAeteStream;

class CAeteProperty {

public:
				CAeteProperty(CAeteStream *	inStream);
				~CAeteProperty();

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

protected:
		Str255		mName;
		OSType		mID;		// like pnam, imod, pidx etc.
		OSType		mType;		// like itxt, bool, long etc.
		Str255		mDescription;
		UInt16		mFlags;

private:


};


#endif
