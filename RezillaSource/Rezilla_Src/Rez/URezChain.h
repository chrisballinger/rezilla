// ===========================================================================
// URezChain.h					
// 
//                       Created: 2003-04-24 14:17:20
//             Last modification: 2003-04-24 17:08:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_URezChain
#define _H_URezChain
#pragma once


class URezChain {

public:

		static short	Count();
		
		static TArray<ResType>*	GetChainList();
		
		static OSErr	InsertFile( SInt16 inRefNum,
								   RsrcChainLocation inWhere);
		
		static OSErr	DetachFile(SInt16 inRefNum);
		
		static OSErr	GetTopFile(SInt16 & outRefNum);
		
		static OSErr	GetNextFile(SInt16 inCurRefNum, 
									SInt16 & outNextRefNum);

protected:


private:

};


#endif
