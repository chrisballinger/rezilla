// ===========================================================================
// COffscreenDragTask.h
//                       Created: 2004-12-11 18:57:44
//             Last modification: 2004-12-15 06:51:16
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// ===========================================================================

#ifndef _H_COffscreenDragTask
#define _H_COffscreenDragTask

class COffscreen;



class COffscreenDragTask : public LDragTask {
	public:
							COffscreenDragTask( const EventRecord &, const Rect &inRect, COffscreen * );
		virtual				~COffscreenDragTask();
		
	protected:
		static pascal OSErr	 SendProc( FlavorType, void *refCon, ItemReference, DragReference );
};


#endif // _H_COffscreenDragTask
