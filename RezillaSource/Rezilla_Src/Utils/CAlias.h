// ===========================================================================
// CAlias.h					
//                       Created: 2004-03-02 13:18:30
//             Last modification: 2004-03-12 22:24:19
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================


#ifndef _H_CAlias
#define _H_CAlias

#ifndef __MACH__
#include <Aliases.h>
#endif
	
class CAlias {
		
public:
			CAlias();
			CAlias(AliasHandle inAliasHandle);
			CAlias(FSSpec& inFSSpec);
			
			~CAlias();
	
	OSErr 			GetFileSpec(FSSpec& outFileSpec);
	OSErr 			GetFileName(Str255 outFileName);
	OSErr 			Resolve();
	
	AliasHandle 	GetAliasHandle() {return mAliasH;}
	
	CAlias& operator = (AliasHandle inAliasHandle);
	CAlias& operator = (const FSSpec& inFSSpec);
		
protected:

	AliasHandle		mAliasH;
	
	void			Dispose();
};
	
	
#endif