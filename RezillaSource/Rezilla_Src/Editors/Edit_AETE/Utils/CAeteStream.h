// ===========================================================================
// CAeteStream.h					
// 
//                       Created : 2002-05-14 13:01:10
//             Last modification : 2005-01-20 13:50:26
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

#include <LDataStream.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CAeteSuite;


class	CAeteStream : public LDataStream {
public:
						CAeteStream();
						CAeteStream( const CAeteStream& inOriginal);
						CAeteStream(void*		inBuffer,
									SInt32		inLength);
						CAeteStream(AEDesc * inAete);
						virtual				~CAeteStream();
						

	CAeteStream&		operator = ( const CAeteStream& inOriginal );

	void					ReadOSType( char	outString[5] );

	virtual ExceptionCode	AlignBytes();

	SInt32					NextTerm( SInt32 inType);

	
	// Accessors

	virtual TArray<CAeteSuite*> *	GetSuitesArrayPtr() { return mSuitesArrayPtr;}

	virtual Handle		GetAeteDataH() { return mAeteDataH;}
	void				SetAeteDataH(Handle theAeteDataH) {mAeteDataH = theAeteDataH ;}


protected:
	TArray<CAeteSuite*>*   		mSuitesArrayPtr;
	Handle						mAeteDataH;
	
	
private:
	void			SkipSuitePreambule();
	
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

