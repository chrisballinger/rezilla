// ===========================================================================
// CICNS_Family.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-26 22:18:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_Family
#define _H_CICNS_Family
#pragma once


class CICNS_Stream;
class CICNS_Member;


class CICNS_Family {
public:
				CICNS_Family();
				CICNS_Family(OSType inType);
				CICNS_Family(CICNS_Stream * inStream);
				~CICNS_Family();

		void		AddMember(OSType inType);
		void		AddMember(CICNS_Member * inMember);
		void		AddMember(OSType inType, SInt32 inSize, Handle inHandle);
		void		DeleteMember( ArrayIndexT inAtIndex );
		
		void		InstallDataStream(CICNS_Stream * inStream);
		void		SendDataToStream(CICNS_Stream * outStream);

		ArrayIndexT		GetCurrentIndex();
		void			SetCurrentIndex(ArrayIndexT inIndex);
		void			AdjustCurrentIndex();

		CICNS_Member *	FindIconForType(OSType inType) const;
		
		ArrayIndexT		GetMemberIndex() { return mMemberIndex;}
		void			SetMemberIndex(ArrayIndexT inMemberIndex) {mMemberIndex = inMemberIndex;}

		SInt32			CountMembers() { return mMembers.GetCount(); }
		
		TArray<CICNS_Member*> *	GetMembers() { return &mMembers;}

		OSType			GetIconType() { return mIconType;}
		void			SetIconType(OSType inIconType) {mIconType = inIconType;}
			
protected:
		OSType					mIconType;	// Should be 'icns'
		ArrayIndexT				mMemberIndex;
		TArray<CICNS_Member*>	mMembers;


private:


};


#endif
