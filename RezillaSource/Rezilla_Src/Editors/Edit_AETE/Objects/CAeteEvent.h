// ===========================================================================
// CAeteEvent.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 09:36:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteEvent
#define _H_CAeteEvent
#pragma once

class CAeteStream;
class CAeteParameter;

class CAeteEvent {

public:
					CAeteEvent();
					CAeteEvent(
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
					CAeteEvent(CAeteStream * inStream);
					~CAeteEvent();

		void	AddParameter();
		void	AddParameter(CAeteParameter * inParameter);
		void	AddParameter(Str255	inName,
								OSType	inKeyword, 
								OSType	inType, 
								Str255	inDescription, 
								UInt16	inFlags);
		void	RemoveParameter( ArrayIndexT inAtIndex );
		
		void	InstallDataStream();
		void	SendDataToStream(CAeteStream * outStream);

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
		void			GetParameterIndex(ArrayIndexT inParameterIndex) {mParameterIndex = inParameterIndex;}

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
