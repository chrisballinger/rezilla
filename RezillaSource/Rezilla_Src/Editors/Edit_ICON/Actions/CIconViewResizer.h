// ===========================================================================
// CIconViewResizer.h
//                       Created: 2004-12-11 18:57:06
//             Last modification: 2004-12-21 22:31:42
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================
#ifndef _H_CIconViewResizer
#define _H_CIconViewResizer

#include "COffscreen.h"

typedef struct
{
	LPane			*thePane;
	SInt32			top, left;
	SInt32			width, height;
	COffscreen 		*buffer;
} SSavedPaneInfo;

class OffScreen;
class CIcon_EditorWindow;

class CIconViewResizer {
	public:
							CIconViewResizer();
		virtual				~CIconViewResizer();
		
		virtual void		Initialize( CIcon_EditorWindow * );
		virtual void		RestoreWindowState();
		virtual	void		DeleteAllBuffers();

	protected:
		CIcon_EditorWindow	*mPaintView;
		Rect				mWindowBounds;
		COffscreen			*mImageBuffer;
		SSavedPaneInfo		mSampleWellInfo;
		SInt32				mNumSamplePanes;
		SSavedPaneInfo		mSamplePaneInfo[ kMaxIconSamplePanes ];
		
		virtual void		GetPaneInfoByID( PaneIDT, Boolean isTargetView, SSavedPaneInfo * );
		virtual void		GetPaneInfo( LPane *, Boolean isTargetView, SSavedPaneInfo * );
		virtual void		SetPaneInfo( SSavedPaneInfo & );
};

#endif // _H_CIconViewResizer
