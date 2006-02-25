// ===========================================================================
// CICNS_Family.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-23 15:12:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_Family
#define _H_CICNS_Family
#pragma once

#include <CFXMLNode.h>

class CICNS_Stream;
class CICNS_Member;


class CICNS_Family {

public:
				CICNS_Family();
				CICNS_Family(
							Str255	inName,
							Str255	inDescription,
							OSType	inID, 
							UInt16	inLevel,
							UInt16	inVersion);
				CICNS_Family(CICNS_Stream * inStream);
				~CICNS_Family();

		void		AddMember();
		void		AddMember(CICNS_Member * inMember);
		void		AddMember(
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
		OSErr		AddMember(CFXMLTreeRef inTreeNode);
		void		RemoveMember( ArrayIndexT inAtIndex );
		
		SInt32		NewItem(SInt8 inKind);
		SInt32		DeleteItem(SInt8 inKind);

		void		InstallDataStream(CICNS_Stream * inStream);
		void		SendDataToStream(CICNS_Stream * outStream);

		OSErr		GetDataFromXml(CFXMLTreeRef inTreeNode);
		
		OSErr		GetArrayFromXml(CFXMLTreeRef inTreeRef, SInt8 inKind);

		StringPtr	GetName( Str255	outName ) const;
	
		void		GetValues(Str255 outName, Str255 outDescription, OSType & outID, 
							  UInt16 & outLevel, UInt16 & outVersion);
		
		void 		SetValues(Str255 inName, Str255 inDescription, OSType inID, 
							  UInt16 inLevel, UInt16 inVersion);
			
		ArrayIndexT		GetCurrentIndex(SInt8 inKind);
		void			SetCurrentIndex(SInt8 inKind, ArrayIndexT inIndex);
		void			AdjustCurrentIndex(SInt8 inKind);

		ArrayIndexT		GetMemberIndex() { return mMemberIndex;}
		void			SetMemberIndex(ArrayIndexT inMemberIndex) {mMemberIndex = inMemberIndex;}

		SInt32			CountMembers() { return mMembers.GetCount(); }
		SInt32			GetCurrentCount(SInt8 inKind);
		
		TArray<CICNS_Member*> *	GetMembers() { return &mMembers;}

protected:
		Str255						mName;
		Str255						mDescription;
		OSType						mID;		// like reqd, core, Rzil etc.
		UInt16						mLevel;
		UInt16						mVersion;
	
		ArrayIndexT					mMemberIndex;

		TArray<CICNS_Member*>		mMembers;


private:


};


#endif
