// ===========================================================================
// CAeteStream.cp					
// 
//                       Created : 2002-05-14 13:01:10
//             Last modification : 2005-01-20 13:49:39
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2002-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CAeteStream.h"
#include "RezillaConstants.h"


PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CAeteStream							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CAeteStream::CAeteStream()
	: LHandleStream()
{	
}


// ---------------------------------------------------------------------------
//	¥ CAeteStream							Copy Constructor		  [public]
// ---------------------------------------------------------------------------
//	Copy points to the same buffer as the original

CAeteStream::CAeteStream(const CAeteStream&	inOriginal)
	: LHandleStream(inOriginal)
{
}


// ---------------------------------------------------------------------------
//	¥ CAeteStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct from an existing Handle.
//	The LHandleStream object assumes ownership of the Handle.

CAeteStream::CAeteStream(Handle	inHandle)
	: LHandleStream(inHandle)
{
}


// ---------------------------------------------------------------------------
//	¥ CAeteStream							Constructor				  [public]
// ---------------------------------------------------------------------------
//	Construct from an AEDesc of type typeAete.

CAeteStream::CAeteStream(AEDesc * inAeteDesc)
	: LHandleStream( (Handle) inAeteDesc->dataHandle)
{
}


// ---------------------------------------------------------------------------
//	¥ ~CAeteStream							Destructor				  [public]
// ---------------------------------------------------------------------------

CAeteStream::~CAeteStream()
{}


// ---------------------------------------------------------------------------
//	¥ AlignBytes													 [public]
// ---------------------------------------------------------------------------
//	If the marker is odd, move it 1 step forward.
//	Errors: 
//		writErr		Attempt to write past end of DataStream

ExceptionCode
CAeteStream::AlignBytes()
{
	ExceptionCode	err = noErr;
	
	if (GetMarker() % 2 != 0) {
		if (GetMarker() + 1 > GetLength()) {
			err = writErr;
		} else {
			SetMarker(1, streamFrom_Marker);
		}
	}
	
	return err;
}


// ---------------------------------------------------------------------------
//	¥ ReadOSType
// ---------------------------------------------------------------------------
//	Read a four chars string from a Stream into outString.

void
CAeteStream::ReadOSType(
	char	outString[5])
{
	ReadBlock(outString, 4);
	outString[4] = '\0';	// Null terminator
}


// ---------------------------------------------------------------------------
//	¥ MoveToNextTerm
// ---------------------------------------------------------------------------
//	Returns the mark of the next term's position in the stream. Here 'term'
//	means event, class, comparison operator or enumeration. 
//	
//	Event structure: Pascal string + Pascal string + possible alignment byte + 4 4 4
//	   + Pascal string + possible alignment byte + 2 (flags) + 4 
//	   + Pascal string + possible alignment byte + 2 (flags) 
//	Then next is nb of additional params. Struct of add parms:
//	   Pascal string + possible alignment byte + 4 4 
//     + Pascal string + possible alignment byte + 2 (flags)
//     
//	Class structure: 

SInt32
CAeteStream::MoveToNextTerm( SInt32 inKind)
{
	SInt32	thePos = 0;
	UInt8	theUInt8;
	UInt16	theUInt16, theSubUInt16, theIndex, theSubIndex;
	UInt8	theAlign = 0;
	
	switch (inKind) {
		
	  case kind_AeteEvent:
		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( 12 + theAlign, streamFrom_Marker);

		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( 6 + theAlign, streamFrom_Marker);

		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( 2 + theAlign, streamFrom_Marker);

		*this >> theUInt16; // nb of additional params
		if (theUInt16) {
			for (theIndex = 1; theIndex <= theUInt16; theIndex++) {
				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				SetMarker( 8 + theAlign, streamFrom_Marker);

				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				SetMarker( 2 + theAlign, streamFrom_Marker);
			}
		}
		break;
		
		
	  case kind_AeteClass:
		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( 4 + theAlign, streamFrom_Marker);

		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( theAlign, streamFrom_Marker);

		*this >> theUInt16; // nb of class properties
		if (theUInt16) {
			for (theIndex = 1; theIndex <= theUInt16; theIndex++) {
				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				// Add ID (4), class (4)
				SetMarker( 8 + theAlign, streamFrom_Marker);
				
				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				// Add flags (2)
				SetMarker( 2 + theAlign, streamFrom_Marker);
			}
		}

		*this >> theUInt16; // nb of class elements
		if (theUInt16) {
			for (theIndex = 1; theIndex <= theUInt16; theIndex++) {
				SetMarker( 4, streamFrom_Marker);
				*this >> theSubUInt16; // nb of key forms
				// Each key form occupies 4 bytes
				SetMarker( 4*theSubUInt16, streamFrom_Marker);
			}
		}
		break;
		
		
	  case kind_AeteCompOp:
		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( 4 + theAlign, streamFrom_Marker);

		*this >> theUInt8; // length of Pascal string
		SetMarker( theUInt8 , streamFrom_Marker);
		// Check for an alignment byte
		theAlign = ( GetMarker() % 2 == 1) ? 1:0;
		SetMarker( theAlign, streamFrom_Marker);
		break;
		
		
	  case kind_AeteEnum:
		SetMarker( 4, streamFrom_Marker);
		*this >> theUInt16; // nb of class enumerators
		if (theUInt16) {
			for (theSubIndex = 1; theSubIndex <= theUInt16; theSubIndex++) {
				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				SetMarker( 4 + theAlign, streamFrom_Marker);

				*this >> theUInt8; // length of Pascal string
				SetMarker( theUInt8 , streamFrom_Marker);
				// Check for an alignment byte
				theAlign = ( GetMarker() % 2 == 1) ? 1:0;
				SetMarker( theAlign, streamFrom_Marker);
			}
		}
		break;
	}
	
	return GetMarker();
}


// ---------------------------------------------------------------------------
//	¥ SkipPreambule()
// ---------------------------------------------------------------------------
//	Moves to the position of the first item's (event, class, comparison 
//	operator or enumeration) position in the current suite. 
//	The preambule of a suite contains:  a Pascal string for the title,
//	a Pascal string for the description + possible alignment byte +
//	the ID (4 chars), the level (2) and the version (2)

void
CAeteStream::SkipPreambule()
{
	UInt8	theUInt8;
	UInt8	theAlign = 0;

	*this >> theUInt8; // length of the first Pascal string
	SetMarker( theUInt8 , streamFrom_Marker);
	*this >> theUInt8; // length of the second Pascal string
	SetMarker( theUInt8 , streamFrom_Marker);
	// Check for an alignment byte at the end of the second Pascal string
	theAlign = ( GetMarker() % 2 == 1) ? 1:0;
	SetMarker( 8 + theAlign, streamFrom_Marker);
}


PP_End_Namespace_PowerPlant

