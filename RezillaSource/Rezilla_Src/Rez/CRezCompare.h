// ===========================================================================
// CRezCompare.h					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2004-02-29 18:17:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CREZCOMPARE
#define _H_CREZCOMPARE
#pragma once

class CRezMap;

struct RezTypId {
	ResType	type;
	short	id;
};


class CRezCompare {
	
public:

	enum {
		list_OnlyInOld,
		list_OnlyInNew,
		list_Differ
	};
	
				CRezCompare(LCommander* inSuper);
				CRezCompare(LCommander* inSuper,
							CRezMap * inOldMap, 
							CRezMap * inNewMap);
				CRezCompare(LCommander* inSuper,
							FSSpec& inOldFileSpec, 
							FSSpec& inNewFileSpec);
				~CRezCompare();

		void			RunRezCompareDialog();
		void			DoCompareRezMaps();
		void			CompareTypes(ResType inType);
		UInt32			CompareTwoResources(ResType inType, short theID);

		Boolean			HasDifferences();
		
protected:
		LCommander* 		mSuperCommander;
		Boolean				mIgnoreNames;
		Boolean				mIgnoreAttrs;
		CRezMap * 			mOldMap;
		CRezMap * 			mNewMap;
		TArray<RezTypId *>	mOnlyInOldList;
		TArray<RezTypId *>	mOnlyInNewList;
		TArray<RezTypId *>	mDifferList;

		void		AddTypeToArray(ResType inType, SInt16 inWhichList);
		void		AddResourceToArray(ResType inType, short inID, SInt16 inWhichList);
		
};


#endif

