// ===========================================================================
// CAeteEvent.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 07:26:30
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
				CAeteEvent(CAeteStream * inStream);
				~CAeteEvent();

		void		AddParameter(CAeteParameter * inParameter);
		void		AddParameter(Str255	inName,
								OSType	inKeyword, 
								OSType	inType, 
								Str255	inDescription, 
								UInt16	inFlags);
		void		RemoveParameter( ArrayIndexT inAtIndex );
		
		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

protected:
		Str255					mName;
		Str255					mDescription;
		OSType					mClass;		// like aevt, core, misc etc.
		OSType					mID;		// like odoc, clon, slct etc.
		UInt16					mFlags;
		ArrayIndexT				mCurrParameterIndex;		
		TArray<CAeteParameter*>	mParameters;

private:


};


#endif
