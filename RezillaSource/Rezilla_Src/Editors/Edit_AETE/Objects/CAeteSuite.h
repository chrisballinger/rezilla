// ===========================================================================
// CAeteSuite.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 09:35:35
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
				CAeteSuite();
				CAeteSuite(
							Str255	inName,
							Str255	inDescription,
							OSType	inID, 
							UInt16	inLevel,
							UInt16	inVersion);
				CAeteSuite(CAeteStream * inStream);
				~CAeteSuite();

		void		AddEvent();
		void		AddEvent(CAeteEvent * inEvent);
		void		AddEvent(
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
		void		RemoveEvent( ArrayIndexT inAtIndex );
		
		void		AddClass();
		void		AddClass(CAeteClass * inClass);
		void		AddClass(Str255	inName,
							OSType	inID,
							Str255	inDescription);
		void		RemoveClass( ArrayIndexT inAtIndex );
		
		void		AddCompOp();
		void		AddCompOp(CAeteCompOp * inCompOp);
		void		AddCompOp(Str255 inName, 
							 OSType inType, 
							 Str255 inDescription);
		void		RemoveCompOp( ArrayIndexT inAtIndex );
		
		void		AddEnumeration();
		void		AddEnumeration(CAeteEnumeration * inEnum);
		void		AddEnumeration(OSType inID);
		void		RemoveEnumeration( ArrayIndexT inAtIndex );

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

		StringPtr	GetName( Str255	outName ) const;
	
		void		GetValues(Str255 outName, Str255 outDescription, OSType & outID, 
							  UInt16 & outLevel, UInt16 & outVersion);
		
		void 		SetValues(Str255 inName, Str255 inDescription, OSType inID, 
							  UInt16 inLevel, UInt16 inVersion);
			
		ArrayIndexT		GetEventIndex() { return mEventIndex;}
		void			GetEventIndex(ArrayIndexT inEventIndex) {mEventIndex = inEventIndex;}

		ArrayIndexT		GetClassIndex() { return mClassIndex;}
		void			GetClassIndex(ArrayIndexT inClassIndex) {mClassIndex = inClassIndex;}

		ArrayIndexT		GetCompOpIndex() { return mCompOpIndex;}
		void			GetCompOpIndex(ArrayIndexT inCompOpIndex) {mCompOpIndex = inCompOpIndex;}

		ArrayIndexT		GetEnumerationIndex() { return mEnumerationIndex;}
		void			GetEnumerationIndex(ArrayIndexT inEnumerationIndex) {mEnumerationIndex = inEnumerationIndex;}

		TArray<CAeteEvent*> *	GetEvents() { return &mEvents;}

		TArray<CAeteClass*> *	GetClasses() { return &mClasses;}

		TArray<CAeteCompOp*> *	GetCompOperators() { return &mCompOperators;}

		TArray<CAeteEnumeration*> *	GetEnumerations() { return &mEnumerations;}

protected:
		Str255						mName;
		Str255						mDescription;
		OSType						mID;		// like reqd, core, Rzil etc.
		UInt16						mLevel;
		UInt16						mVersion;
	
		ArrayIndexT					mEventIndex;
		ArrayIndexT					mClassIndex;
		ArrayIndexT					mCompOpIndex;
		ArrayIndexT					mEnumerationIndex;

		TArray<CAeteEvent*>			mEvents;
		TArray<CAeteClass*>			mClasses;
		TArray<CAeteCompOp*>		mCompOperators;
		TArray<CAeteEnumeration*>	mEnumerations;


private:


};


#endif
