#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";


// read 'TEXT' (250 , "About Text", purgeable) "Rezilla_About.text";
data 'TEXT' (250, "About Text", purgeable) {
$$Format("Rezilla\nResource editor \n© 2003-%d by Bernard Desgraupes\n<bdesgraupes@users.sourceforge.net>\n\nRezilla project:\n<http://sourceforge.net/projects/rezilla>\n\nRezilla is a free software",  $$YEAR)
};


