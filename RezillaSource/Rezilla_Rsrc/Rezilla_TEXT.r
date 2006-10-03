// ===========================================================================
// Rezilla_TEXT.r
//                       Created: 2004-02-28 22:51:23
//             Last modification: 2006-09-30 17:10:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2006
// All rights reserved.
// ===========================================================================

#include <MacTypes.r>

read 'TEXT' (130 , "License Terms", purgeable)  "Rezilla_License.text";

data 'TEXT' (250, "About Text", purgeable) {
$$Format("Resource map editor\n\n(c) 2003-%d", $$YEAR)
};

data 'TEXT' (251, "Free software", purgeable) {
"Rezilla is a free software"
};

