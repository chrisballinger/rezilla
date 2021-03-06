// ===========================================================================
// CICNS_Family.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-11-09 20:00:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_Family
#define _H_CICNS_Family
#pragma once


class LHandleStream;
class CICNS_Member;

class CICNS_Family {
public:
				CICNS_Family();
				CICNS_Family(OSType inType);
				CICNS_Family(LHandleStream * inStream);
				~CICNS_Family();

		CICNS_Member *	AddMember(OSType inType);
		void			AddMember(CICNS_Member * inMember);
		void			AddMember(OSType inType, Handle inHandle);
		void			DeleteMember( ArrayIndexT inAtIndex );
		void			DeleteMember( CICNS_Member * inMember );

		void			InstallDataStream(LHandleStream * inStream);
		OSErr			RetrieveData(IconFamilyHandle & outIconFamilyH);

		CICNS_Member *	FindMember(OSType inType) const;
		
		SInt32			CountMembers() { return mMembers.GetCount(); }
		
		TArray<CICNS_Member*> *	GetMembers() { return &mMembers;}

		OSType			GetIconType() { return mIconType;}
		void			SetIconType(OSType inIconType) {mIconType = inIconType;}
			
protected:
		OSType					mIconType;	// Should be kIconFamilyType = 'icns'
		TArray<CICNS_Member*>	mMembers;


private:


};


#endif
