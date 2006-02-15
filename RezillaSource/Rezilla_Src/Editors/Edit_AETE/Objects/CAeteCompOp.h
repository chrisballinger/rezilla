// ===========================================================================
// CAeteCompOp.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-02-19 15:09:28
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CAeteCompOp
#define _H_CAeteCompOp
#pragma once

#include <CFXMLNode.h>

class CAeteStream;

class CAeteCompOp {

public:
				CAeteCompOp();
				CAeteCompOp(Str255 inName, 
							OSType inID, 
							Str255 inDescription);
				CAeteCompOp(CAeteStream *	inStream);
				~CAeteCompOp();

		void		InstallDataStream(CAeteStream * inStream);
		void		SendDataToStream(CAeteStream * outStream);

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		void		GetValues(Str255 outName, OSType & outID, Str255 outDescription);
		
		void 		SetValues(Str255 inName, OSType inID, Str255 inDescription);

protected:
		Str255		mName;
		OSType		mID;
		Str255		mDescription;

private:

};


#endif
