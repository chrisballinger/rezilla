// ===========================================================================
// CICNS_Member.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_Member
#define _H_CICNS_Member
#pragma once

#include <CFXMLNode.h>

class CAeteStream;
class CAeteParameter;

class CICNS_Member {

public:
					CICNS_Member();
					CICNS_Member(
							   Str255	inName,
							   Str255	inDescription,
							   OSType	inClass, 
							   OSType	inID,
							   OSType	inReplyType,
							   Str255	inReplyDescription,
							   UInt16	inReplyFlags,
							   OSType	inDirectType,
							   Str255	inDirectDescription,
							   UInt16	inDirectFlags);
					CICNS_Member(CAeteStream * inStream);
					~CICNS_Member();

		void	AddParameter();
		void	AddParameter(CAeteParameter * inParameter);
		void	AddParameter(Str255	inName,
								OSType	inKeyword, 
								OSType	inType, 
								Str255	inDescription, 
								UInt16	inFlags);
		OSErr	AddParameter(CFXMLTreeRef inTreeNode);
		void	RemoveParameter( ArrayIndexT inAtIndex );
		
		SInt32		NewParameter();
		SInt32		DeleteParameter();

		void	InstallDataStream(CAeteStream * inStream);
		void	SendDataToStream(CAeteStream * outStream);

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		void	GetValues(
					   Str255 & outName, Str255 outDescription,
					   OSType & outClass, OSType & outID,
					   OSType & outReplyType, Str255 outReplyDescription, UInt16 & outReplyFlags,
					   OSType & outDirectType, Str255 outDirectDescription, UInt16 & outDirectFlags);
		
		void	SetValues(
					   Str255 inName, Str255 inDescription,
					   OSType inClass, OSType inID,
					   OSType inReplyType, Str255 inReplyDescription, UInt16 inReplyFlags,
					   OSType inDirectType, Str255 inDirectDescription, UInt16 inDirectFlags);

		ArrayIndexT		GetParameterIndex() { return mParameterIndex;}
		void			SetParameterIndex(ArrayIndexT inParameterIndex) {mParameterIndex = inParameterIndex;}

		SInt32			CountParameters() { return mParameters.GetCount(); }

		TArray<CAeteParameter*> *	GetParameters() { return &mParameters;}

protected:
		Str255					mName;
		Str255					mDescription;
		OSType					mClass;			// like aevt, core, misc etc.
		OSType					mID;			// like odoc, clon, slct etc.
		OSType					mReplyType;		// like null, bool, long etc.
		Str255					mReplyDescription;
		UInt16					mReplyFlags;
		OSType					mDirectType;
		Str255					mDirectDescription;
		UInt16					mDirectFlags;
		ArrayIndexT				mParameterIndex;		
		TArray<CAeteParameter*>	mParameters;

private:


};


#endif
