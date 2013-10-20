// ===========================================================================
// CAeteParameter.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-19 16:56:14
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CAeteParameter
#define _H_CAeteParameter
#pragma once

#ifndef	__MACH__
#include <CFXMLNode.h>
#endif

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

		void		InstallDataStream(CAeteStream * inStream);
		void		SendDataToStream(CAeteStream * outStream);

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		void		GetValues(Str255 outName, OSType & outKeyword, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags);
		
		void 		SetValues(Str255 inName, OSType inKeyword, OSType inType, 
					   Str255 inDescription, UInt16 inFlags);

protected:
		Str255		mName;
		OSType		mKeyword;		// like kfil, kocl, data etc.
		OSType		mType;			// like alis, type, **** etc.
		Str255		mDescription;
		UInt16		mFlags;

private:


};


#endif
