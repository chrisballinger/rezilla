// ===========================================================================
// CAeteProperty.h
// 
//                       Created: 2005-01-20 09:35:10
//             Last modification: 2005-01-22 10:40:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAeteProperty
#define _H_CAeteProperty
#pragma once

class CAeteStream;

class CAeteProperty {

public:
				CAeteProperty();
				CAeteProperty(Str255 inName, 
							  OSType inID, 
							  OSType inType, 
							  Str255 inDescription, 
							  UInt16 inFlags);
				CAeteProperty(CAeteStream *	inStream);
				~CAeteProperty();

		void		InstallDataStream();
		void		SendDataToStream(CAeteStream * outStream);

		void		GetValues(Str255 outName, OSType & outID, OSType & outType, 
					   Str255 outDescription, UInt16 & outFlags);
		
		void 		SetValues(Str255 inName, OSType inID, OSType inType, 
					   Str255 inDescription, UInt16 inFlags);
			
protected:
		Str255		mName;
		OSType		mID;		// like pnam, imod, pidx etc.
		OSType		mType;		// like itxt, bool, long etc.
		Str255		mDescription;
		UInt16		mFlags;

private:

};


#endif
