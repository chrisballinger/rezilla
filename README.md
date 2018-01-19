Rezilla
=======

Rezilla is a resource forks editor for the Macintosh. 
This is version 1.1.

This new version is a major upgrade and brings the following new features:

* new plugin architecture to support the addition of third party editors

* new image editor (implemented as a plugin) to display and manipulate
image resources. It supports the following image formats: JPEG, TIFF,
GIF, PNG, BMP.

* new 'icns' editor to manage icon suite resources. You can create,
modify, redraw, delete, etc. any of the bitmaps included in an 'icns'
resource suite. Possibility of importing from or exporting to a ".icns"
image data file. Possibility of exploding or imploding the contents of
an 'icns'.

* introduced resource pickers for displaying graphically and easily
manipulating all the resources of a particular type. Pickers have been
defined for the following types:
	 'TEXT', 'MENU', 'STR#', 'MBAR', 'RID#', 'Mcmd', 'RidL', 'cicn',
	 'ICON', 'SICN', 'icns', 'PICT', 'PAT ', 'ppat', 'PAT#', 'ICN#',
	 'icl4', 'icl8', 'icm#', 'icm4', 'icm8', 'ics#', 'ics4', 'ics8',
	 'CURS', 'crsr'

* new Plugins command in the File menu to get info about the plugins
and rearrange their order

* possibility of importing/exporting an entire resource map from/to XML

* new Import command in the File menu to import data in some resource
editors

* XML export now correctly escapes the standard entities and writes in
utf-8 encoding

* new WCOL and LCOL tags in the Template editor for RGB colors stored on
  2 or 4 bytes respectively

* improved Unique ID algorithm: it now returns the first available value
  (above the current one) when calculating a unique ID rather than a
  random number

* aliases are now followed for templates located in Application Support
  folders

* improved edition of resource ID tags (RSID) in the Template editor. A dynamic
  popup offers the currently available choices.

* added new templates for the Templates editor (there are now more than 
  400 templates)

* improved clipboard handling of hexadecimal data strings

* Tab key navigation through the fields of the Template editor's windows

* in the Template editor, the "+" key simulates a click on the Plus Button

* extended AppleScript terminology to support plugins and pickers

* more sample AppleScript scripts to demonstrate the new commands

* many interface improvements...

* many bug fixes...


Previous versions already implemented the following features:

* Rezilla lets you edit, create, modify, duplicate, remove resources
contained in any fork (data fork or resource fork), copy, cut and paste
them from a resource map to the other, drag and drop resources etc.

* Rezilla comes equipped with an Hexadecimal Editor and a Template
Editor. The template editor ships with no less than 400 predefined
templates and lets you easily define and add more.

* Rezilla has several dedicated editors:
    * a Text Editor to edit 'TEXT' and 'styl' resources

    * a Bitmap Editor to edit any of the following types:
'cicn', 'crsr', 'CURS', 'icl4', 'icl8', 'icm#', 'icm4', 'icm8', 'ICN#',
'ICON', 'ics#', 'ics4', 'ics8', 'PAT#', 'PAT ', 'ppat', 'SICN'

    * an Unicode Editor to edit 'utxt' resources containing Unicode
data in UTF-16 encoding form

    * a List Editor to edit 'STR#', 'MBAR', 'Mcmd' and 'RidL' resources

	* an Aete Editor to edit AppleScript terminology resources
	(resources with type 'aete' or 'aeut'). It can generate Scripting
	Definition files (sdef) and export to Xml, DeRez, Html, and Text
	formats. It can also import an aete from an Xml file.

    * a Pict Viewer to visualize, copy, cut and paste 'PICT' resources

    * a Sound Player to play 'snd ' resources

    * a Menu Editor (which supports 'xmnu' menu extension resources)


* complete scriptability to drive Rezilla from AppleScript scripts

* Rezilla can export resource maps in text, HTML, XML or DeRez formats

* Rezilla can compare two resource maps.

* various values and properties can be set via the Preferences.





The Rezilla project is a work in progress. It comes without any warranty
(see the license terms). That said, it has been thoroughly tested and has
proven quite stable and reliable.

Please read the doc contained in the help files. It is accessible via the
Rezilla Help command in the Help menu when Rezilla is running. You can also
read it online
in english <http://perso.orange.fr/bdesgraupes/DocHTML/EN/RezillaHelp/index.html> or 
in french <http://perso.orange.fr/bdesgraupes/DocHTML/FR/RezillaHelp/index.html>.

Rezilla is a free software.

See the licensing terms in the License.terms file or click on the License
button in the About box of the application.

The official home page for the project is at SourceForge:
 <http://sourceforge.net/projects/rezilla>

There is a users mailing list where any kind of problems about Rezilla can
be discussed, in particular the questions related to its scriptability and
AppleScript syntax.
Subscribe here <http://lists.sourceforge.net/lists/listinfo/rezilla-users>


Please e-mail me any problem you encounter with this software:
 <bdesgraupes@users.sourceforge.net>

(c) Copyright: Bernard Desgraupes, 2003-2006
 All rights reserved.

Last updated: 2006-11-25
