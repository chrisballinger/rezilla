// ===========================================================================
// CAeteCompOp.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 10:53:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteCompOp
#define _H_CAeteCompOp
#pragma once

class CAeteStream;

class CAeteCompOp {

public:
				CAeteCompOp();
				CAeteCompOp(Str255 inName, 
							OSType inType, 
							Str255 inDescription);
				CAeteCompOp(CAeteStream *	inStream);
				~CAeteCompOp();

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

		void		GetValues(Str255 outName, OSType & outType, Str255 outDescription);
		
		void 		SetValues(Str255 inName, OSType inType, Str255 inDescription);

protected:
		Str255		mName;
		OSType		mType;
		Str255		mDescription;

private:

};


#endif
