#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";


// read 'TEXT' (250 , "About Text", purgeable) "Rezilla_About.text";
data 'TEXT' (250, "About Text", purgeable) {
$$Format("A resource maps editor\n\n© 2003-%d by Bernard Desgraupes\n<bdesgraupes@users.sourceforge.net>", $$YEAR)
};

data 'TEXT' (251, "Free software", purgeable) {
"Rezilla is a free software"
};

