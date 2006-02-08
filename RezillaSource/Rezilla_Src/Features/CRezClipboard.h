// ===========================================================================
// CRezClipboard.h					
//                       Created: 2003-05-11 21:05:08
//             Last modification: 2004-03-15 20:26:44
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
	scrap_pictedit,
	scrap_hexeditHex,
	scrap_hexeditTxt,
	scrap_bitmap
};


class CRezFile;
class CRezMap;

// ---------------------------------------------------------------------------

class CRezClipboard : public LClipboard {
public:
						CRezClipboard();
	virtual				~CRezClipboard();

	static Boolean		ContentsIsValidHex();
	
	static SInt32		GetScrapContext() { return sScrapContext;}
	static void			SetScrapContext(SInt32 inScrapContext) {sScrapContext = inScrapContext;}

	static CRezFile *	GetScrapRezFile() { return sScrapRezFile;}
	static CRezMap *	GetScrapRezMap() { return sScrapRezMap;}
	static short		GetScrapRefNum() { return sScrapRefnum;}
	
protected:
	static SInt32		sScrapContext;
	static CRezFile *	sScrapRezFile;
	static CRezMap *	sScrapRezMap;
	static short		sScrapRefnum;

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
	virtual void		DataArrayToScrapRezMap(
								ResType		inDataType,
								Ptr			inDataPtr,
								SInt32		inDataLength,
								Boolean		inReset);

	OSErr				DeleteLocalScrap();
	OSErr				NewLocalScrap();
};


// ===========================================================================
//	¥ Stack-based class
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StClipboardContext
// ---------------------------------------------------------------------------

class StClipboardContext {
public:
						StClipboardContext();
						StClipboardContext( SInt32 inContext, Boolean inResetPrevious = false );
						~StClipboardContext();

	void		SetContext( SInt32 inContext ) { mOriginalContext = inContext; }
	
	void		Restore();
	
private:
	SInt16		mOriginalContext;
	Boolean		mResetPrevious;

};



PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
