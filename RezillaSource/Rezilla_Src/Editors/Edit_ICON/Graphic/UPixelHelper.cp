// ===========================================================================
// UPixelHelper.cp
//                       Created: 2004-12-11 18:52:53
//             Last modification: 2004-12-15 13:47:31
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "UPixelHelper.h"


// ============================================================
// 	GetPixelFunctions
// ============================================================

void UPixelHelper::GetPixelFunctions( SInt32 inDepth, SUPixelGetter *outGetter, SUPixelSetter *outSetter )
{
	switch( inDepth )
	{
		case 32:
			*outGetter = GetColor32;
			*outSetter = SetColor32;
			break;
		case 16:
			*outGetter = GetColor16;
			*outSetter = SetColor16;
			break;
		case 8:
			*outGetter = GetColor8;
			*outSetter = SetColor8;
			break;
		case 4:
			*outGetter = GetColor4;
			*outSetter = SetColor4;
			break;
		case 2:
			*outGetter = GetColor2;
			*outSetter = SetColor2;
			break;
		case 1:
			*outGetter = GetColor1;
			*outSetter = SetColor1;
			break;
		default:
			throw( paramErr );
	}
}

