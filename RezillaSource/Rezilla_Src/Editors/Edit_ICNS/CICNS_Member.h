// ===========================================================================
// CICNS_Member.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-02-26 11:08:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_Member
#define _H_CICNS_Member
#pragma once

class CICNS_Stream;

class CICNS_Member {

public:
					CICNS_Member(OSType inType);
					CICNS_Member(OSType inType, SInt32 inSize, Handle inHandle);
					CICNS_Member(CICNS_Stream * inStream);
					~CICNS_Member();

	virtual void	InstallDataStream(CICNS_Stream * inStream);
	virtual void	SendDataToStream(CICNS_Stream * outStream);

	void			GetValues(OSType & outType, SInt32 & outSize, Handle & outHandle);
	void			SetValues(OSType inType, SInt32 inSize, Handle inHandle);

	OSType			GetType() { return mType;}

	SInt32			GetIconSize() { return mIconSize;}

protected:
		OSType			mType;		// Like 'it32', 'ih32', 'tile' etc.
		SInt32			mIconSize;		// Real size of the icon data
		      			      		// Warning: 
		      			      		//   the size field in the resource
		      			      		//   also counts the size of the OSType
		      			      		//   and of the SInt32 (this would be
		      			      		//   mIconSize + 8).
		Handle			mIconData;

private:


};


#endif
