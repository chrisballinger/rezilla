// ===========================================================================
// CICNS_Member.h
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-03-13 15:55:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================
// 	type 'icns' {
// 		iconFamilyBegin:
// 			literal longint = 'icns';
// 			unsigned longint = (iconFamilyEnd - iconFamilyBegin) >> 3;
// 			array elementArray {
// 				literal longint;
// 				elementBegin:
// 					longint =   (elementEnd[$$ArrayIndex(elementArray)] 
// 						- elementBegin[$$ArrayIndex(elementArray)] >> 3) + 4;
// 					hex string;
// 				elementEnd:
// 			};
// 		iconFamilyEnd:
// 	};
// 	
// 	
// Icons.h in the ApplicationServices framework defines the
// IconFamilyElement struct like this:
// 
// 		struct IconFamilyElement {
// 		  OSType              elementType;      /* 'ICN#', 'icl8', etc...*/
// 		  Size                elementSize;      /* Size of this element*/
// 		  unsigned char       elementData[1];
// 		};
// 		
// Note: elementSize includes the size of the OSType, the size of the
// SInt32 and the size of the compressed icon



#ifndef _H_CICNS_Member
#define _H_CICNS_Member
#pragma once

class LHandleStream;

class CICNS_Member {

public:
					CICNS_Member(OSType inType, Handle inHandle = NULL);
					~CICNS_Member();

	void			GetValues(OSType & outType, Handle & outHandle);
	void			SetValues(OSType inType, Handle inHandle);

	OSType			GetType() { return mType;}

	virtual Handle	GetIconData() { return mIconData;}
	void			SetIconData(Handle inIconData) {mIconData = inIconData;}

	virtual Boolean	IsModified() { return mModified;}
	void			SetModified(Boolean inModified) {mModified = inModified;}

protected:
		OSType			mType;		// Like 'it32', 'ih32', 'tile' etc.
		Handle			mIconData;	// A handle to the icon member 
		      			          	// data after decompression
		Boolean			mModified;

private:


};


#endif
