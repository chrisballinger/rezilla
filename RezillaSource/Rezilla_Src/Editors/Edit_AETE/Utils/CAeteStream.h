// ===========================================================================
// CAeteStream.h					
// 
//                       Created : 2002-05-14 13:01:10
//             Last modification : 2005-01-23 09:32:34
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2002-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteStream
#define _H_CAeteStream
#pragma once

#include <LHandleStream.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CAeteSuite;


class	CAeteStream : public LHandleStream {
public:
						CAeteStream();
						CAeteStream( const CAeteStream& inOriginal);
						CAeteStream(Handle	inHandle);
						CAeteStream(AEDesc * inAete);
						virtual				~CAeteStream();
						
	void					ReadOSType( char outString[5] );

	virtual ExceptionCode	AlignBytesRead();
	virtual void			AlignBytesWrite();

	SInt32					MoveToNextTerm( SInt32 inKind);

protected:
	
private:
	void			SkipPreambule();
	
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

