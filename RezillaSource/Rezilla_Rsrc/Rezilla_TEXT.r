#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";


// read 'TEXT' (250 , "About Text", purgeable) "Rezilla_About.text";
data 'TEXT' (250, "About Text", purgeable) {
$$Format("Rezilla\nResource editor \n¬© %d by Bernard Desgraupes\n<bdesgraupes@easyconnect.fr>\n\nRezilla is a free software",  $$YEAR)
};


