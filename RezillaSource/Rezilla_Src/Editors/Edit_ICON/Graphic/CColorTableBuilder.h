// ===========================================================================
// CColorTableBuilder.h
//                       Created: 2004-12-11 18:57:16
//             Last modification: 2004-12-14 18:57:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "RezillaConstants.h"

class COffscreen;
class CColorHash;

class CColorTableBuilder
{
	public:
		/*********************************************
			this is the only routine many will need
		*********************************************/
		static COffscreen *	DownSampleBuffer( COffscreen *inSource, SInt32 inMaxDepth,
													Boolean inIncludeBW, Boolean inMinimizeTable, 
													Boolean biggerInverseTable );
													
		/*********************************************
			constructor & destructor
		*********************************************/
								CColorTableBuilder( Boolean inIncludeBW = false );
		virtual					~CColorTableBuilder();
		
		/*********************************************
			changing the settings
		*********************************************/
		virtual void			SetBuffer( COffscreen * );
		virtual void			SetIncludeBW( Boolean );
		virtual void			SetMinimizeTable( Boolean );
		virtual void			SetPictUtilMethod( short inMethod );
		virtual void			SetLargerInverseTable( Boolean );
	
		/*********************************************
			retrieving information
		*********************************************/
		virtual SInt32			GetColorCount();
		virtual CTabHandle		GetColorTable( SInt32 inMaxDepth, SInt32 *outDepth );
		virtual COffscreen *	CreateDownSampledBuffer( SInt32 inMaxDepth );
	
															
	protected:
		COffscreen	*			mBuffer;
		CColorHash *			mColorHash;
		
		Boolean					mIncludeBW;
		Boolean					mMinimizeTable;
		Boolean					mLargerInverseTable;
		short					mPictUtilMethod;
		
		Boolean					mScanIsDone;
		Boolean					mUseCopyBits;
		
		virtual void			DoScan();
};


