// ===========================================================================
// UCompareUtils.h
// 				
//                       Created: 2005-01-02 15:16:34
//             Last modification: 2005-01-02 15:25:34
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// ===========================================================================

#ifndef _H_UCompareUtils
#define _H_UCompareUtils
#pragma once

#include <PP_Prefix.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
// CompareUtils: just as it says...

class UCompareUtils {

public:
	static SInt16	CompareStr255(Str255 * leftString, Str255 * rightString);	
	static Boolean	HandlesAreIdentical(const Handle leftHndl, const Handle rightHndl);
	static Boolean	HasExtension(FSSpec * inFSSpec, char * inExtension);
	
};



// ================================================================
//      Comparator classes
// ================================================================

// ---------------------------------------------------------------------------
// String comparator class to build tables of types sorted alphabetically

class	LComparator;

class CTypeComparator : public LComparator {
public:

						CTypeComparator();
	virtual				~CTypeComparator();

	virtual SInt32		Compare(
								const void*			inItemOne,
								const void* 		inItemTwo,
								UInt32				inSizeOne,
								UInt32				inSizeTwo) const;

};



// ---------------------------------------------------------------------------
// String comparator class to build outline tables of typeItems 
// sorted alphabetically

class CTypeItemComparator : public LComparator {
public:

						CTypeItemComparator();
	virtual				~CTypeItemComparator();

	virtual SInt32		Compare(
								void*		inItemOne,
								void* 		inItemTwo,
								UInt32		inSizeOne,
								UInt32		inSizeTwo) const;

};





PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
