#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";


// read 'TEXT' (250 , "About Text", purgeable) "Rezilla_About.text";
data 'TEXT' (250, "About Text", purgeable) {
$$Format("Rezilla\nResource editor \n\n© 2003-%d by Bernard Desgraupes\n<bdesgraupes@users.sourceforge.net>\n\nRezilla is a free software", $$YEAR)
};

data 'TEXT' (251, "Project URL", purgeable) {
"Rezilla project:\n<http://sourceforge.net/projects/rezilla>"
};

