// $Date$
// $Revision$
// =================================================================================
//	UDragAndDropUtils.cp			¬©1995-2000 Metrowerks Inc. All rights reserved.
// =================================================================================

#include <UMemoryMgr.h>
#include <UExtractFromAEDesc.h>
#include <Folders.h>

#include "UDragAndDropUtils.h"

// ---------------------------------------------------------------------------------
//		¬€ DroppedInTrash
// ---------------------------------------------------------------------------------

Boolean
UDragAndDropUtils::DroppedInTrash(
	DragReference	inDragRef )
{
	Boolean	isTrash = false;
	
	try {

#ifdef	Debug_Throw
		// It's okay to fail here, so 
		// temporarily turn off debug actions.
		StValueChanger<EDebugAction>
			theDebugAction( UDebugging::gDebugThrow, debugAction_Nothing );
#endif

		// Get the drop location from the drag ref.
		AEDesc	theDropDestination;
		ThrowIfOSErr_( ::GetDropLocation( inDragRef, &theDropDestination ) );

		// Make sure we're dealing with an alias.
		ThrowIf_( theDropDestination.descriptorType != typeAlias );

		// Get the file spec of the destination to
		// which the user dragged the item.
		FSSpec	theDestinationFSSpec;
		{
			AliasHandle	theAliasH;

			UExtractFromAEDesc::TheAlias(theDropDestination, theAliasH);
			StHandleLocker	theLock((Handle) theAliasH);
			
			// Attempt to resolve the alias.
			Boolean	isChanged;
			ThrowIfOSErr_( ::ResolveAlias( nil, theAliasH,
				&theDestinationFSSpec, &isChanged ) );
		}
		
		// Get the file spec for the trash.
		FSSpec	theTrashFSSpec;
		SInt16	theTrashVRefNum;
		SInt32	theTrashDirID;
		ThrowIfOSErr_( ::FindFolder( kOnSystemDisk, kTrashFolderType,
			kDontCreateFolder, &theTrashVRefNum, &theTrashDirID ) );
		ThrowIfOSErr_( ::FSMakeFSSpec( theTrashVRefNum,
			theTrashDirID, nil, &theTrashFSSpec ) );

		// Compare the two file specs.
		isTrash =
			(theDestinationFSSpec.vRefNum == theTrashFSSpec.vRefNum ) &&
			(theDestinationFSSpec.parID	 ==	theTrashFSSpec.parID ) &&
			(::EqualString( theDestinationFSSpec.name,
				theTrashFSSpec.name, false, true ));
	
	} catch ( const LException& inErr ) {
	
		// Nothing to do here.
	
	}

	return isTrash;
}


// ---------------------------------------------------------------------------------
//		¬€ CheckForOptionKey
// ---------------------------------------------------------------------------------

Boolean
UDragAndDropUtils::CheckForOptionKey(
	DragReference	inDragRef )
{
	// Get the drag modifiers.
	SInt16	theModifiersNow;
	SInt16	theModifiersAtMouseDown;
	SInt16	theModifiersAtMouseUp;
	::GetDragModifiers( inDragRef, &theModifiersNow,
		&theModifiersAtMouseDown, &theModifiersAtMouseUp );
	
	// Return true if the option key was down at the
	// beginning or the end of the drag.
	return ( (theModifiersAtMouseDown & optionKey) != 0 ) ||
		( (theModifiersAtMouseUp & optionKey) != 0 );
}


// ---------------------------------------------------------------------------------
//		¬€ CheckIfViewIsAlsoSender
// ---------------------------------------------------------------------------------

Boolean
UDragAndDropUtils::CheckIfViewIsAlsoSender(
	DragReference	inDragRef )
{
	// Get the drag attributes.
	DragAttributes theDragAttributes;
	::GetDragAttributes(inDragRef, &theDragAttributes);
	
	// Return true if the drag is in the 
	// same window as the originator of the drag.
	return (theDragAttributes & kDragInsideSenderWindow) != 0;
}



