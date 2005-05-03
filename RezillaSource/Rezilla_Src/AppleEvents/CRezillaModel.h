// ===========================================================================
// CRezillaModel.h
//                       Created: 2005-05-03 07:38:23
//             Last modification: 2005-05-03 08:01:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRezillaModel
#define _H_CRezillaModel
#pragma once

#include <LModelDirector.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif




PP_Begin_Namespace_PowerPlant

class LModelObject;

// ---------------------------------------------------------------------------

class CRezillaModel : public LModelDirector {
public:
						CRezillaModel();

						CRezillaModel( LModelObject* inDefaultModel );

	virtual				~CRezillaModel();


// 	virtual void		InstallCallBacks();

// 	virtual void		AccessModelObject(
// 								DescType			inDesiredClass,
// 								const AEDesc&		inContainerToken,
// 								DescType			inContainerClass,
// 								DescType			inKeyForm,
// 								const AEDesc&		inKeyData,
// 								AEDesc&				outToken,
// 								SInt32				inRefCon);

	virtual void		DisposeToken(
								AEDesc&				ioToken);


protected:


// 	static pascal OSErr	ModelObjectAccessor(
// 								DescType			inDesiredClass,
// 								const AEDesc*		inContainerToken,
// 								DescType			inContainerClass,
// 								DescType			inKeyForm,
// 								const AEDesc*		inKeyData,
// 								AEDesc*				outToken,
// 								SInt32				inRefCon);

// 	static pascal OSErr	OSLDisposeToken(
// 								AEDesc*				inToken);


// 	static void			StoreReplyErrorString(
// 								ConstStringPtr		inErrorString,
// 								AppleEvent*			ioReply);
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
