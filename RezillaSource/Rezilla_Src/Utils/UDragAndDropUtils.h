// =================================================================================
//	UDragAndDropUtils.h				©1995-2000 Metrowerks Inc. All rights reserved.
// =================================================================================

#pragma once

#ifndef __MACH__
#include <Drag.h>
#endif

class UDragAndDropUtils {
public:
	static Boolean	DroppedInTrash( DragReference inDragRef );
	static Boolean	CheckForOptionKey( DragReference inDragRef );
	static Boolean	CheckIfViewIsAlsoSender( DragReference inDragRef );
};
