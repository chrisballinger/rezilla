// ===========================================================================
// CWindow_IconFamily.h
//                       Created: 2004-12-11 18:56:28
//             Last modification: 2004-12-30 09:44:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CWindow_IconFamily
#define _H_CWindow_IconFamily
#pragma once

#include "CIcon_EditorWindow.h"

class CRezMap;


// ----------------------------------------------------------------------------
// Structs PaintFamilyMember, PaintFamilyList
// 	  These data structures describe how the icon family and ICON windows
// 	  work -- which resources are displayed in which sample panes, etc.
// 	
// 	  This allows us to add/remove additional resource types simply by
// 	  editing the resource rather than changing the code.
// 	
//    Everything is a long, so we have no alignment problems (68k vs. PowerPC)

typedef struct
{
	ResType				resourceType;		// icl8, ICN#, etc
	UInt32				flags;				
	SInt32				width, height;		// in pixels
	SInt32				depth, rowBytes;
	PaneIDT				samplePaneID;
	
		// if it has a mask also
	SInt32				maskOffset;			// # bytes into resource where the mask lives
	SInt32				maskRowBytes;
	PaneIDT				maskSamplePaneID;
} PaintFamilyMember;


typedef struct
{
	PaneIDT				defaultPane;		// which one is the initial sample pane
	SInt32				numEntries;			// 1..n
	PaintFamilyMember	members[1];	
} PaintFamilyList, **PaintFamilyListH;

// ----------------------------------------------------------------------------


class CWindow_IconFamily : public CIcon_EditorWindow {
	public:
		enum { class_ID = FOUR_CHAR_CODE('FamV') };

								CWindow_IconFamily( LStream * );
		virtual					~CWindow_IconFamily();
		
		static CWindow_IconFamily *	OpenPaintWindow( ResIDT inPPobID, CRezMap *inMap, ResIDT );
		static CWindow_IconFamily *	CreateFromStream( LStream *inStream );

		virtual void			FinishCreateSelf();
		
		virtual void			InitializeFromResource( CRezMap *inMap, ResIDT );
		virtual void			SaveAsResource( CRezMap *, ResIDT );
	
		SInt32					GetZoomFactor( SInt32, SInt32, Boolean *outShowGrid );
			
		SInt32					GetFamilyMemberCount();
		void					GetFamilyMemberInfo( SInt32 index, PaintFamilyMember * );
	
	protected:
		PaintFamilyListH		mFamilyListH;
		
		virtual Boolean			InitializeOneMember( 
										CRezMap *inMap, ResType inResType, ResIDT inResID,
										SInt32 inWidth, SInt32 inHeight, SInt32 inDepth,
										SInt32 inOffset, SInt32 inRowBytes,
										PaneIDT inSamplePaneID, Boolean inIsMask );

};

#endif // _H_CWindow_IconFamily
