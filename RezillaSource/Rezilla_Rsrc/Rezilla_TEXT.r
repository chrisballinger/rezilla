#include <MacTypes.r>

read 'TEXT' (130 , "Licence Terms", purgeable)  "Rezilla_Licence.text";

data 'TEXT' (250, "About Text", purgeable) {
$$Format("Resource map editor\n\n© 2003-%d", $$YEAR)
};

data 'TEXT' (251, "Free software", purgeable) {
"Rezilla is a free software"
};

