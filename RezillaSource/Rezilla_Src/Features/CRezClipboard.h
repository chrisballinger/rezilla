// ===========================================================================
// CRezClipboard.h					
//                       Created: 2003-05-11 21:05:08
//             Last modification: 2004-03-10 19:42:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRezClipboard
#define _H_CRezClipboard
#pragma once

#include <UScrap.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// Local scrap context
enum
{	
	scrap_default = 0,
	scrap_rezmap,
	scrap_hexeditHexdata,
	scrap_hexeditTxtdata
};


class CRezFile;

// ---------------------------------------------------------------------------

class CRezClipboard : public LClipboard {
public:
						CRezClipboard();
	virtual				~CRezClipboard();

	static Boolean		ContentsIsValidHex();
	
	static  SInt32		GetScrapContext() { return sScrapContext;}
	static void			SetScrapContext(SInt32 inScrapContext) {sScrapContext = inScrapContext;}

	static CRezFile *	GetScrapRezFile() { return sScrapRezFile;}
	
protected:
	static SInt32		sScrapContext;
	static CRezFile *	sScrapRezFile;
	
	virtual void		SetDataSelf(
								ResType		inDataType,
								Ptr			inDataPtr,
								SInt32		inDataLength,
								Boolean		inReset);

	virtual SInt32		GetDataSelf(
								ResType		inData,
								Handle		ioDataH);

	virtual void		ImportSelf();
	virtual void		ExportSelf();

private:
	OSErr				InitScrapRezMap();
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif


