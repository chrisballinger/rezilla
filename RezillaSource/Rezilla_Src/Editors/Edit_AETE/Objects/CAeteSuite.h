// ===========================================================================
// CAeteSuite.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-21 06:58:59
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteSuite
#define _H_CAeteSuite
#pragma once

class CAeteStream;
class CAeteEvent;
class CAeteClass;
class CAeteCompOp;
class CAeteEnumeration;


class CAeteSuite {

public:
				CAeteSuite(CAeteStream * inStream);
				~CAeteSuite();

		void		AddEvent(CAeteEvent * inEvent);
		void		RemoveEvent( ArrayIndexT inAtIndex );
		
		void		AddClass(CAeteClass * inClass);
		void		RemoveClass( ArrayIndexT inAtIndex );
		
		void		AddCompOp(CAeteCompOp * inCompOp);
		void		RemoveCompOp( ArrayIndexT inAtIndex );
		
		void		AddEnumeration(CAeteEnumeration * inEnum);
		void		RemoveEnumeration( ArrayIndexT inAtIndex );

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

protected:
		Str255						mName;
		Str255						mDescription;
		OSType						mID;		// like reqd, core, Rzil etc.
		UInt16						mLevel;
		UInt16						mVersion;
	
		ArrayIndexT					mCurrEventIndex;
		ArrayIndexT					mCurrClassIndex;
		ArrayIndexT					mCurrCompOpIndex;
		ArrayIndexT					mCurrEnumerationIndex;

		TArray<CAeteEvent*>			mEvents;
		TArray<CAeteClass*>			mClasses;
		TArray<CAeteCompOp*>		mCompOperators;
		TArray<CAeteEnumeration*>	mEnumerations;


private:


};


#endif
