// ===========================================================================
// CRezCompare.h					
// 
//                       Created: 2004-02-29 18:17:07
//             Last modification: 2004-03-02 12:42:58
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
class CRezType;
class CCompResultWindow;


// -------------------------------------------------------------------------------------------------

// Small class to wrap around (type, id) pairs
class CRezTypId {
public:
	CRezTypId(ResType inType, short inID) {
		mType = inType;
		mID = inID;
	}
	~CRezTypId();

	ResType	mType;
	short	mID;
};


// -------------------------------------------------------------------------------------------------

class CRezCompare : public LCommander {
	
public:
	enum {
		list_OnlyInOld,
		list_OnlyInNew,
		list_Differing
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
		void			CompareTwoResources(CRezType * inOldRezType, 
											CRezType * inNewRezType, 
											short inID,
											SInt16 * outCompResult);

		Boolean			HasDifferences();
		void			DisplayResults();
		
		virtual Boolean		GetIgnoreNames() { return mIgnoreNames;}
        void                SetIgnoreNames(Boolean inIgnoreNames) {mIgnoreNames = inIgnoreNames;}

		virtual Boolean		GetIgnoreAttrs() { return mIgnoreAttrs;}
		void				SetIgnoreAttrs(Boolean inIgnoreAttrs) {mIgnoreAttrs = inIgnoreAttrs;}

		ConstStringPtr		GetOldPath() const;
		ConstStringPtr		GetNewPath() const;

			virtual TArray<CRezTypId*>*		GetOnlyInOldList() { return &mOnlyInOldList;}

		
protected:
		CCompResultWindow*	mResultWindow;
		Boolean				mIgnoreNames;
		Boolean				mIgnoreAttrs;
		Boolean				mIgnoreData;
		CRezMap * 			mOldMap;
		CRezMap * 			mNewMap;
		TArray<CRezTypId *>	mOnlyInOldList;
		TArray<CRezTypId *>	mOnlyInNewList;
		TArray<CRezTypId *>	mDifferingList;
		Str255				mOldPath;
		Str255				mNewPath;

		void		AddTypeToArray(ResType inType, SInt16 inWhichList);
		void		AddResourceToArray(ResType inType, short inID, SInt16 inWhichList);
};


// ---------------------------------------------------------------------------
//	¥ GetOldPath										 [inline] [public]
// ---------------------------------------------------------------------------

inline ConstStringPtr
CRezCompare::GetOldPath() const
{
	return mOldPath;
}


// ---------------------------------------------------------------------------
//	¥ GetNewPath										 [inline] [public]
// ---------------------------------------------------------------------------

inline ConstStringPtr
CRezCompare::GetNewPath() const
{
	return mNewPath;
}



#endif

