// ===========================================================================
// CICNS_Member.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-11 17:33:31
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
// Icons.h in the ApplicationServices framework defines the
// IconFamilyElement struct like this:
// 		struct IconFamilyElement {
// 		  OSType              elementType;      /* 'ICN#', 'icl8', etc...*/
// 		  Size                elementSize;      /* Size of this element*/
// 		  unsigned char       elementData[1];
// 		};


#ifndef _H_CICNS_Member
#define _H_CICNS_Member
#pragma once

class LHandleStream;

class CICNS_Member {

public:
					CICNS_Member(OSType inType);
					CICNS_Member(OSType inType, SInt32 inSize, Handle inHandle);
// 					CICNS_Member(LHandleStream * inStream);
					~CICNS_Member();

// 	virtual void	InstallDataStream(LHandleStream * inStream);
// 	virtual void	SendDataToStream(LHandleStream * outStream);

	void			GetValues(OSType & outType, SInt32 & outSize, Handle & outHandle);
	void			SetValues(OSType inType, SInt32 inSize, Handle inHandle);

	OSType			GetType() { return mType;}

	SInt32			GetIconSize() { return mIconSize;}
	void			SetIconSize(SInt32 inIconSize) {mIconSize = inIconSize;}

	virtual Handle	GetIconData() { return mIconData;}
	void			SetIconData(Handle inIconData) {mIconData = inIconData;}

protected:
		OSType			mType;		// Like 'it32', 'ih32', 'tile' etc.
		SInt32			mIconSize;	// Size of the icon member
		      			      		// Warning: 
		      			      		//   this includes the size of the 
		      			      		//   OSType, the size of this SInt32 
		      			      		//   and the size of the compressed 
		      			      		//   icon
		Handle			mIconData;	// A handle to the icon member 
		      			          	// data after decompression

private:


};


#endif
