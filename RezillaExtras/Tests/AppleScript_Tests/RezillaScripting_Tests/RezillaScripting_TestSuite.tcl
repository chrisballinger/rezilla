# ------------------------------------------------------------
# File: "Rezilla_TestSuite.tcl"
#                        Created: 2005-05-22 09:54:33
#              Last modification: 2006-10-09 19:36:17
# Author: Bernard Desgraupes
# e-mail: <bdesgraupes@easyconnect.fr>
# www: <http://webperso.easyconnect.fr/bdesgraupes/>
# (c) Copyright: Bernard Desgraupes, 2005, 2006
# All rights reserved.
# This software is free software with BSD licence.
# Versions history: see the Changes.Log file.
# 
# Test suite for Rezilla's scripting terminology and AppleScript support.
# To execute this test suite, you need to have a Tcl installation (8.4 or
# greater) with the tcltest extension (2.2 or greater), the Tclresource
# extension (1.1 or greater), and the Tclapplescript extension (1.0 or
# greater). The Tclresource extension is needed only if you want to
# regenerate the sample files inside the Forks subfolder; it is not used by
# the tests themselves. Simply source this file in a Tcl interpreter to run
# all the tests.
# 
# ------------------------------------------------------------

# Check that we are on OSX
if {$tcl_platform(platform) != "unix" || $tcl_platform(os) != "Darwin"} {
	puts stdout "The Rezilla application is for the MacOSX platform only. Exiting now."
	return
} 

# Package requirements
package require Tcl 8.4
if {[lsearch [namespace children] ::tcltest] == -1} {
	package require tcltest 2.2
}
package require resource 1.1
package require Tclapplescript 1.0
package require tclAE

# # # Configurable variables # # #
# --------------------------------
namespace eval ::rezilla::test {
	variable rezillaName "Rezilla_D"
}
# --------------------------------



namespace eval ::rezilla::test {
	variable DFname "TestRezillaDF.rsrc"
	variable RFname "TestRezillaRF.rsrc"
	variable NFname "TestRezillaNF.rsrc"
	
	# Borrowed from AlphaTcl
	proc unixPathToFinder {path} {
		if {![regexp / $path]} {return $path}
		return [tclAE::getHFSPath $path]
	}

	# Data fork
	variable rezfileDF [unixPathToFinder [file join [file dir [info script]] Forks $DFname]]
	# Resource fork
	variable rezfileRF [unixPathToFinder [file join [file dir [info script]] Forks $RFname]]
	# No fork
	variable rezfileNF [unixPathToFinder [file join [file dir [info script]] Forks $NFname]]

	variable BEGIN "tell application \"$rezillaName\"\r"
	variable END "\rend tell"
	
	# Launch Rezilla (this is an Alpha command)
	if {[info exists alpha::macos]} {
		app::launchFore Rzil
	} 

	proc ASExec {cmd} {
		variable BEGIN 
		variable END
		return [AppleScript execute "$BEGIN $cmd\r$END"]
	}
	
	proc ASQuote {txt} {
		return "\"$txt\""
	}
	
	proc DeleteIfExists {fname} {
		set f [file join [file dir [info script]] Forks $fname]
		if {[file exists $f]} {
			file delete $f
		} 
	}
	
	proc TestFile {cmd num} {
		return "[string totitle ${cmd}]Test${num}.rsrc"
	}

	proc getPathOfExecutable {} {
		variable rezillaName
		set prs [processes]
		set path ""
		set found 0
		foreach p $prs {
			if {[lindex $p 0] eq $rezillaName} {
				set path [lindex $p 5]
				set found 1
				break
			} 
		} 
		if {!$found} {
			alertnote "Process not found"
		} 
		return $path
	}

	proc getBundleContentsFolder {} {
		return [file dir [file dir [getPathOfExecutable]]]
	}

	proc getPluginsList {} {
		set plugFolder [file join [getBundleContentsFolder] PlugIns]
		return [lsort [glob -tail -dir $plugFolder *.plugin]]
	}
}


# # # document [ASQuote [ASTail $rezfileRF]] of application [ASQuote $rezillaName]
# # # editor [ASQuote "[ASTail $rezfileRF] - 'MENU' #128"] of map document 1
# # # window [ASQuote [ASTail $rezfileRF]] of application [ASQuote $rezillaName]

tcltest::configure -testdir [file dirname [file normalize [info script]]]

puts stdout "Tests running in Tcl $tcl_patchLevel interpreter"
puts stdout "Starting tests [clock format [clock seconds]]"


# # Now execute the tests suite

namespace eval ::rezilla::test {
	namespace import ::tcltest::*


	# "Open" tests
	# ------------
	test RezillaOpen-1-1 {Open RF file} -setup {
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -body {
		set result [ASExec "name of map document 1"]
	} -cleanup {
		ASExec "close first map document saving no"
	} -result "[ASQuote TestRezillaRF.rsrc]"
		
	test RezillaOpen-1-2 {Open DF file} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
	} -body {
		set result [ASExec "name of map document 1"]
	} -cleanup {
		ASExec "close first map document saving no"
	} -result "[ASQuote TestRezillaDF.rsrc]"
		
	test RezillaOpen-1-3 {Open data fork, DF specified} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias from data fork"
	} -body {
		set result [ASExec "name of map document 1"]
	} -cleanup {
		ASExec "close first map document saving no"
	} -result "[ASQuote TestRezillaDF.rsrc]"

	test RezillaOpen-1-4 {Open data fork, RF specified} -setup {
	} -body {
		ASExec "open [ASQuote $rezfileDF] as alias from resource fork"
	} -cleanup {
	}  -returnCodes error -match glob \
	  -result "An AppleScript error was encountered*"
		
	test RezillaOpen-1-5 {Open resource fork, RF specified} -setup {
		ASExec "open [ASQuote $rezfileRF] as alias from resource fork"
	} -body {
		set result [ASExec "name of map document 1"]
	} -cleanup {
		ASExec "close first map document saving no"
	} -result "[ASQuote TestRezillaRF.rsrc]"
		
	test RezillaOpen-1-6 {Open resource fork, DF specified} -setup {
	} -body {
		ASExec "open [ASQuote $rezfileRF] as alias from data fork"
	} -cleanup {
	}  -returnCodes error -match glob \
	  -result "An AppleScript error was encountered*"
		
	test RezillaOpen-1-7 {File with no fork} -setup {
	} -body {
		ASExec "open [ASQuote $rezfileNF] as alias"
	} -cleanup {
	} -returnCodes error -match glob \
	  -result "An AppleScript error was encountered*"
		
	test RezillaOpen-1-8 {Open read only} -setup {
		ASExec "open [ASQuote $rezfileRF] as alias with readOnly"
	} -body {
		set result [ASExec "readOnly of map document 1"]
	} -cleanup {
	} -result "true"
		
	test RezillaOpen-1-9 {Open with w but already opened with r} -setup {
		ASExec "open [ASQuote $rezfileRF] as alias with readOnly"
	} -body {
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -cleanup {
		ASExec "close first map document saving no"
	} -result ""
		
		
		
	# "Close" map docs tests
	# ----------------------
	test RezillaClose-1-1 {Open RF and close} -setup {
	} -body {
		set precount [ASExec "count documents"]
		ASExec "open [ASQuote $rezfileRF] as alias"
		set postcount [ASExec "count documents"]
		set result [expr $postcount - $precount]
	} -cleanup {
		ASExec "close map document [ASQuote $RFname] saving no"
	} -result "1"
		
	test RezillaClose-1-2 {Open DF and close} -setup {
	} -body {
		set precount [ASExec "count documents"]
		ASExec "open [ASQuote $rezfileDF] as alias"
		set postcount [ASExec "count documents"]
		set result [expr $postcount - $precount]
	} -cleanup {
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "1"
		

# From now on the $rezfileRF document is opened
# ---------------------------------------------
	
#################################################

	ASExec "open [ASQuote $rezfileRF] as alias"

#################################################

	
	# "MapDocument" tests
	# -------------------
	test RezillaMapDocument-1-1 {Get map document by index} -setup {
	} -body {
		ASExec "get map document 1"
	} -cleanup {
	} -result "document [ASQuote $RFname] of application [ASQuote $rezillaName]"

	test RezillaMapDocument-1-2 {Get map document by name} -setup {
	} -body {
		ASExec "get map document [ASQuote $RFname]"
	} -cleanup {
	} -result "document [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaMapDocument-1-3 {Get readOnly flag of map doc} -setup {
	} -body {
		ASExec "get the readOnly of map document 1"
	} -cleanup {
	} -result "false"
		
	test RezillaMapDocument-1-4 {Get window of map doc} -setup {
	} -body {
		ASExec "get the window of map document 1"
	} -cleanup {
	} -result "window [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaMapDocument-1-5 {Get map of map doc} -setup {
	} -body {
		ASExec "get the map of map document 1"
	} -cleanup {
	} -match regexp -result "map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaMapDocument-1-6 {Get fork of RF map doc} -setup {
	} -body {
		ASExec "get the fork of map document 1"
	} -cleanup {
	} -result "ResourceFork"
		
	test RezillaMapDocument-1-7 {Get fork of DF map doc} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
	} -body {
		ASExec "get the fork of map document 2"
	} -cleanup {
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "DataFork"
		
	test RezillaMapDocument-1-8 {Get refnum of map doc} -setup {
	} -body {
		ASExec "get the refnum of map document 1"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaMapDocument-1-9 {Get file of map doc} -setup {
	} -body {
		ASExec "get the file of map document 1"
	} -cleanup {
	} -result "file [ASQuote $rezfileRF]"
		
	test RezillaMapDocument-1-10 {Get format of map doc} -setup {
	} -body {
		ASExec "get the format of map document 1"
	} -cleanup {
	} -result "xml"
		
	test RezillaMapDocument-1-11 {Set format of map doc} -setup {
	} -body {
		set orig [ASExec "get the format of map document 1"]
		ASExec "set the format of map document 1 to html"
		set result [ASExec "get the format of map document 1"]
		ASExec "set the format of map document 1 to $orig"
		return $result
	} -cleanup {
	} -result "html"
		
	test RezillaMapDocument-1-12 {Get all map documents} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
# 		ASExec "open [ASQuote $rezfileRF] as alias"
	} -body {
		set reply [ASExec "get map documents"]
		set expectedRes "{document [ASQuote $RFname] of application [ASQuote $rezillaName], "
		append expectedRes "document [ASQuote $DFname] of application [ASQuote $rezillaName]}"
		return [expr $reply eq $expectedRes]
	} -cleanup {
# 		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "1"

	# "Map" tests
	# -----------
	test RezillaMap-1-1 {Map specifier} -setup {
	} -body {
		set result [ASExec "map of map document 1"]
	} -cleanup {
	} -match regexp -result "map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaMap-1-2 {Get the refnum} -setup {
	} -body {
		set result [ASExec "get refnum of the map of map document 1"]
	} -cleanup {
	} -match regexp -result "\\d+"
		
	test RezillaMap-1-3 {Get the attributes} -setup {
	} -body {
		set result [ASExec "get attributes of the map of map document 1"]
	} -cleanup {
	} -result "0"
		
	test RezillaMap-1-4 {Get the readOnly bit} -setup {
	} -body {
		set result [ASExec "get readOnly of the map of map document 1"]
	} -cleanup {
	} -result "false"
		
	test RezillaMap-1-5 {Get the compact bit} -setup {
	} -body {
		set result [ASExec "get compact of the map of map document 1"]
	} -cleanup {
	} -result "false"
		
	test RezillaMap-1-6 {Get the changed bit} -setup {
	} -body {
		set result [ASExec "get changed of the map of map document 1"]
	} -cleanup {
	} -result "false"
		
	test RezillaMap-1-7 {Set the attributes} -setup {
	} -body {
		ASExec "set the attributes of the map of map document 1 to 100"
		set result [ASExec "get attributes of the map of map document 1"]
	} -cleanup {
		ASExec "set the attributes of the map of map document 1 to 0"
	} -result "100"
		
	test RezillaMap-1-8 {Set the readOnly bit} -setup {
	} -body {
		ASExec "set readOnly of the map of map document 1 to true"
		set result [ASExec "get readOnly of the map of map document 1"]
	} -cleanup {
		ASExec "set readOnly of the map of map document 1 to false"
	} -result "true"
		
	test RezillaMap-1-9 {Set the compact bit} -setup {
	} -body {
		ASExec "set compact of the map of map document 1 to true"
		set result [ASExec "get compact of the map of map document 1"]
	} -cleanup {
		ASExec "set compact of the map of map document 1 to false"
	} -result "true"
		
	test RezillaMap-1-10 {Set the changed bit} -setup {
	} -body {
		ASExec "set changed of the map of map document 1 to true"
		set result [ASExec "get changed of the map of map document 1"]
	} -cleanup {
		ASExec "set changed of the map of map document 1 to false"
	} -result "true"
		

	# "Type" tests
	# ------------
	test RezillaType-1-1 {List of types as text} -setup {
	} -body {
		ASExec "get all types of map 1"
	} -cleanup {
	} -result "{\"Abou\", \"ALRT\", \"ckid\", \"MENU\", \"MPSR\", \"STR#\", \"TEXT\"}"
		
	test RezillaType-1-2 {Count the types} -setup {
	} -body {
		ASExec "count types of map 1"
	} -cleanup {
	} -result "7"
		
	test RezillaType-1-3 {First type as object} -setup {
	} -body {
		set cmd "set theList to types of map 1
		first item of theList"
		ASExec $cmd
	} -cleanup {
	} -match regexp \
	  -result "type \"Abou\" of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaType-1-4 {Last type as object} -setup {
	} -body {
		set cmd "set theList to types of map 1
		last item of theList"
		ASExec $cmd
	} -cleanup {
	} -match regexp \
	  -result "type \"TEXT\" of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaType-1-5 {Type object by name} -setup {
	} -body {
		ASExec "type \"MENU\" of map 1"
	} -cleanup {
	} -match regexp \
	  -result "type \"MENU\" of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaType-1-6 {Index by ordinal} -setup {
	} -body {
		set cmd "get the index of third type of map 1"
		ASExec $cmd
	} -cleanup {
	} -result "3"
		
	test RezillaType-1-7 {Get the name of a type by index} -setup {
	} -body {
		set cmd "get the name of type 4 of map 1"
		ASExec $cmd
	} -cleanup {
	} -result [ASQuote MENU]
		
	test RezillaType-1-8 {Get the index of a type} -setup {
	} -body {
		set cmd "get the index of type \"MENU\" of map 1"
		ASExec $cmd
	} -cleanup {
	} -result "4"
		
	test RezillaType-1-9 {Get all IDs of a type by name} -setup {
	} -body {
		ASExec "get all IDs of last type of map 1"
	} -cleanup {
	} -result "{128, 129, 130}"
		
	test RezillaType-1-10 {The type as unsigned long} -setup {
	} -body {
		ASExec "get ID of last type of map 1"
	} -cleanup {
	} -result "1.41383074E+9"
		


	# "Resource" tests
	# ----------------
# # Getting properties

	test RezillaResource-1-1 {Get a resource by index} -setup {
	} -body {
		ASExec "get first resource of type \"TEXT\" of map 1"
	} -cleanup {
	} -match regexp \
	  -result "resource id 128 of type \"TEXT\" of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaResource-1-2 {Get last resource} -setup {
	} -body {
		set cmd "set theList to resources of type \"TEXT\" of map 1
		last item of theList"
		ASExec $cmd
	} -cleanup {
	} -match regexp \
	  -result "resource id 130 of type \"TEXT\" of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaResource-1-3 {Get resource by ID} -setup {
	} -body {
		ASExec "get resource id 129 of type \"TEXT\" of map 1"
	} -cleanup {
	} -match regexp \
	  -result "resource id 129 of type \"TEXT\" of map id \\d+ of application [ASQuote $rezillaName]"

# 	test RezillaResource-1-4 {Not existing resource} -setup {
# 	} -body {
# 		ASExec "get resource id 250 of type \"TEXT\" of map 1"
# 	} -cleanup {
# 	} -returnCodes error -match glob \
# 	  -result "An AppleScript error was encountered*"
		
	test RezillaResource-1-5 {Count resources of a certain type} -setup {
	} -body {
		ASExec "count resources of type \"MENU\" of map 1"
	} -cleanup {
	} -result "2"
		
	test RezillaResource-1-6 {Get resource name} -setup {
	} -body {
		ASExec "get the name of resource id 128 of type \"TEXT\" of map 1"
	} -cleanup {
	} -result "[ASQuote Hello]"
		
	test RezillaResource-1-7 {Get resource ID by position} -setup {
	} -body {
		ASExec "get the ID of second resource of type \"TEXT\" of map 1"
	} -cleanup {
	} -result "129"
		
	test RezillaResource-1-8 {Get resource sizes} -setup {
	} -body {
		set cmd "set therez to first resource of type \"TEXT\" of map 1
		set a to the size of therez
		set b to the sizeOnDisc of therez
		{a, b}"
		ASExec $cmd
	} -cleanup {
	} -result "{29, 29}"
		
	test RezillaResource-1-9 {Get resource attributes} -setup {
	} -body {
		ASExec "get the attributes of resource id 1005 of type \"MPSR\" of map 1"
	} -cleanup {
	} -result "4"
		
	test RezillaResource-1-10 {Get resource flags} -setup {
	} -body {
		set cmd "set therez to first resource of type \"TEXT\" of map 1
		set a to the changed of therez
		set b to the sysHeap of therez
		set c to the purgeable of therez
		set d to the locked of therez
		set e to the preload of therez
		set f to the protected of therez
		{a, b, c, d, e, f}"
		ASExec $cmd
	} -cleanup {
	} -result "{false, false, false, false, false, false}"
		
	test RezillaResource-1-11 {Resource by specifier} -setup {
	} -body {
		ASExec "get resource {\"TEXT\", 128} of map 1"
	} -cleanup {
	} -match regexp \
	  -result "resource id 128 of type \"TEXT\" of map id \\d+ of application [ASQuote $rezillaName]"
	
	test RezillaResource-1-12 {Get resource hexadecimal data} -setup {
	} -body {
		 set cmd "set theRez to resource {\"ALRT\", 128} of map 1
			get the hex data of theRez"
		ASExec $cmd
	} -cleanup {
	} -result "[ASQuote 002800280087017c00805555300a]"
	
	test RezillaResource-1-13 {Get data from TEXT resource} -setup {
	} -body {
		 set cmd "set theRez to resource {\"TEXT\", 129} of map 1
			get the hex data of theRez"
		ASExec $cmd
	} -cleanup {
	} -result "[ASQuote "Viva Rezilla!"]"
	
	test RezillaResource-1-14 {Get data from STR# resource} -setup {
	} -body {
		 set cmd "set theRez to resource {\"STR#\", 129} of map 1
			get the hex data of theRez"
		ASExec $cmd
	} -cleanup {
	} -result "{[ASQuote Hello], [ASQuote Salud]}"
	

# # Setting properties
	test RezillaResource-2-1 {Set resource name} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get name of $rez"]
		set cmd "set theRez to $rez
			set the name of theRez to [ASQuote "Test menu"]"
		ASExec $cmd
		set result [ASExec "get name of $rez"]
		set cmd "set theRez to $rez
			set the name of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "[ASQuote "Test menu"]"
		
	test RezillaResource-2-2 {Set resource attributes} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get attributes of $rez"]
		set cmd "set theRez to $rez
			set the attributes of theRez to 12"
		ASExec $cmd
		set result [ASExec "get attributes of $rez"]
		set cmd "set theRez to $rez
			set the attributes of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "12"
		
	test RezillaResource-2-3 {Set resource resChanged flag} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get the changed of $rez"]
		set cmd "set theRez to $rez
			set the changed of theRez to true"
		ASExec $cmd
		set result [ASExec "get the changed of $rez"]
		set cmd "set theRez to $rez
			set the changed of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "true"
		
	test RezillaResource-2-4 {Set resource resProtected flag} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get the protected of $rez"]
		set cmd "set theRez to $rez
			set the protected of theRez to true"
		ASExec $cmd
		set result [ASExec "get the protected of $rez"]
		set cmd "set theRez to $rez
			set the protected of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "true"
		
	test RezillaResource-2-5 {Set resource resPurgeable flag} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get the purgeable of $rez"]
		set cmd "set theRez to $rez
			set the purgeable of theRez to true"
		ASExec $cmd
		set result [ASExec "get the purgeable of $rez"]
		set cmd "set theRez to $rez
			set the purgeable of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "true"
		
	test RezillaResource-2-6 {Set resource resLocked flag} -setup {
	} -body {
		set rez "resource {\"MENU\", 128} of map document 1"
		set orig [ASExec "get the locked of $rez"]
		set cmd "set theRez to $rez
			set the locked of theRez to true"
		ASExec $cmd
		set result [ASExec "get the locked of $rez"]
		set cmd "set theRez to $rez
			set the locked of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "true"
		
	test RezillaResource-2-7 {Set resource hexadecimal data} -setup {
	} -body {
		set rez "resource {\"ALRT\", 128} of map document 1"
		set orig [ASExec "get the hex data of $rez"]
		set cmd "set theRez to $rez
			set the hex data of theRez to [ASQuote 001400140087016800805555300a]"
		ASExec $cmd
		set result [ASExec "get the hex data of $rez"]
		set cmd "set theRez to $rez
			set the hex data of theRez to $orig"
		ASExec $cmd
		return $result
	} -cleanup {
	} -result "[ASQuote 001400140087016800805555300a]"
		
	test RezillaResource-2-8 {Set data in TEXT resource} -setup {
	} -body {
	set rez "resource {\"TEXT\", 129} of map document 1"
	set orig [ASExec "get the hex data of $rez"]
	set cmd "set theRez to $rez
		set the hex data of theRez to [ASQuote "Happy Rezing!"]"
	ASExec $cmd
	set result [ASExec "get the hex data of $rez"]
	set cmd "set theRez to $rez
		set the hex data of theRez to $orig"
	ASExec $cmd
	return $result
	} -cleanup {
	} -result "[ASQuote "Happy Rezing!"]"
		
	test RezillaResource-2-9 {Set data in STR# resource} -setup {
	} -body {
	set rez "resource {\"STR#\", 129} of map document 1"
	set orig [ASExec "get the hex data of $rez"]
	set cmd "set theRez to $rez
		set the hex data of theRez to {\"alpha\", \"beta\", \"gamma\"}"
	ASExec $cmd
	set result [ASExec "get the hex data of $rez"]
	set cmd "set theRez to $rez
		set the hex data of theRez to $orig"
	ASExec $cmd
	return $result
	} -cleanup {
	} -result "{\"alpha\", \"beta\", \"gamma\"}"

	
	# "Editor" tests
	# --------------
	test RezillaEditor-1-1 {Get index of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the index of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "1"
		
	test RezillaEditor-1-2 {Get kind of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the kind of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -match regexp -result "(hexadecimal|template|interface)"
		
	test RezillaEditor-1-3 {Get readOnly of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the readOnly of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "false"
		
	test RezillaEditor-1-4 {Get window of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the window of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "editing window 1 of editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
	
	test RezillaEditor-1-5 {Get resource of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the resource of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -match regexp \
	  -result "resource id 128 of type [ASQuote TEXT] of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaEditor-1-6 {Get owner doc of editor} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get the owner doc of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "map document 1 of application [ASQuote $rezillaName]"
	
	test RezillaEditor-1-7 {All editors of map document} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
		ASExec "edit resource {\"ALRT\",128} of map document 1"
		ASExec "edit resource {\"MENU\",128} of map document 1"
	} -body {
		set reply [ASExec "get editors of map document 1"]
		set expectRes "{editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName], "
		append expectRes "editor [ASQuote "$RFname - 'ALRT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName], "
		append expectRes "editor [ASQuote "$RFname - 'MENU' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]}"
		set result [expr $reply eq $expectRes]
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
	} -result "1"

	test RezillaEditor-1-8 {Editor self specifier} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1"
	} -body {
		ASExec "get first editor of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"


	# "HexadecimalEditor" tests
	# -------------------------
	test RezillaHexadecimalEditor-1-1 {Get hexadecimal editor by index} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		ASExec "get first hexadecimal editor of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		
	test RezillaHexadecimalEditor-1-2 {Get hexadecimal editor by name} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		ASExec "get hexadecimal editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		

	# "InterfaceEditor" tests
	# -----------------------
	test RezillaInterfaceEditor-1-1 {Get interface editor by index} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using interface"
	} -body {
		ASExec "get first interface editor of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		
	test RezillaInterfaceEditor-1-2 {Get interface editor by name} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using interface"
	} -body {
		ASExec "get interface editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		

	# "TemplateEditor" tests
	# ----------------------
	test RezillaTemplateEditor-1-1 {Get template editor by index} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using template"
	} -body {
		ASExec "get first template editor of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		
	test RezillaTemplateEditor-1-2 {Get template editor by name} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using template"
	} -body {
		ASExec "get template editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
	} -result "editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote "$RFname"] of application [ASQuote $rezillaName]"
		

	# "MapWindow" tests
	# -----------------
	test RezillaMapWindow-1-1 {Get map window by index} -setup {
	} -body {
		ASExec "get map window 1"
	} -cleanup {
	} -result "window [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaMapWindow-1-2 {Get types count} -setup {
	} -body {
		ASExec "get the types count of map window 1"
	} -cleanup {
	} -result "7"
		
	test RezillaMapWindow-1-3 {Get resources count} -setup {
	} -body {
		ASExec "get the resources count of map window 1"
	} -cleanup {
	} -result "10"
		
	test RezillaMapWindow-1-4 {Get all map windows} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
	} -body {
		set reply [ASExec "get map windows"]
		set expectedRes "{window [ASQuote $DFname] of application [ASQuote $rezillaName], "
		append expectedRes "window [ASQuote $RFname] of application [ASQuote $rezillaName]}"
		return [expr $reply eq $expectedRes]
	} -cleanup {
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "1"
		
	test RezillaMapWindow-1-5 {Count map windows} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
	} -body {
		set reply [ASExec "count map windows"]
	} -cleanup {
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "2"



	# "EditingWindow" tests
	# ---------------------
	test RezillaEditingWindow-1-1 {Get all editing windows} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"TEXT\",129} of map document 1 using interface"
		ASExec "edit resource {\"TEXT\",130} of map document 1 using template"
	} -body {
		set reply [ASExec "get editing windows"]
		set expectedRes "{editing window 1 of editor [ASQuote "$RFname - 'TEXT' #130"] of document [ASQuote $RFname] of application [ASQuote $rezillaName], "
		append expectedRes "editing window 2 of editor [ASQuote "$RFname - 'TEXT' #129"] of document [ASQuote $RFname] of application [ASQuote $rezillaName], "
		append expectedRes "editing window 3 of editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote $RFname] of application [ASQuote $rezillaName]}"
		return [expr $reply eq $expectedRes]
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #130"] of map document 1"
	} -result "1"
	
	test RezillaEditingWindow-1-2 {Get editing window by index} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"TEXT\",129} of map document 1 using interface"
		ASExec "edit resource {\"TEXT\",130} of map document 1 using template"
	} -body {
		set reply [ASExec "get third editing window"]
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #130"] of map document 1"
	} -result "editing window 3 of editor [ASQuote "$RFname - 'TEXT' #128"] of document [ASQuote $RFname] of application [ASQuote $rezillaName]"

	test RezillaEditingWindow-1-3 {Kind of editing windows} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"TEXT\",129} of map document 1 using interface"
		ASExec "edit resource {\"TEXT\",130} of map document 1 using template"
	} -body {
		set cmd "set a to the kind of first editing window of map document 1
			set b to the kind of second editing window of map document 1
			set c to the kind of third editing window of map document 1
			{a, b, c}
			"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #130"] of map document 1"
	} -result "{hexadecimal, interface, template}"


	# "HexWindow" tests
	# -----------------
	# # # window of editor "TestRezillaRF.rsrc - 'TEXT' #128" of map document 1

	test RezillaHexWindow-1-1 {Get positions} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set a to the startPos of win
			set b to the endPos of win
			set c to the maxPos of win
			{a, b, c}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "{0, 0, 29}"
	
	test RezillaHexWindow-1-2 {Get selected region's contents} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set a to the hex selection of win
			set b to the text selection of win
			{a, b}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "{\"\", \"\"}"
	
	test RezillaHexWindow-1-3 {Set positions} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set the startPos of win to 6
			set the endPos of win to 14
			set a to the startPos of win
			set b to the endPos of win
			{a, b}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "{6, 14}"

	test RezillaHexWindow-1-3 {Set positions and get contents} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set the startPos of win to 6
			set the endPos of win to 14
			set a to the hex selection of win
			set b to the text selection of win
			{a, b}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "{\"52657a696c6c6120\", \"Rezilla.\"}"
	
	test RezillaHexWindow-1-5 {Set contents in hex pane} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set the startPos of win to 6
			set the endPos of win to 13
			set the hex selection of win to \"656469746f72\"
			set the endPos of win to 12
			set the startPos of win to 0
			get the text selection of win"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "[ASQuote "Hello.editor"]"
	
	test RezillaHexWindow-1-6 {Set contents in text pane} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		set cmd "set win to hexadecimal window 1 of map document 1
			set the startPos of win to 6
			set the endPos of win to 13
			set the text selection of win to \"editor\"
			set the endPos of win to 12
			set the startPos of win to 0
			get the hex selection of win"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1 saving no"
	} -result "[ASQuote 48656c6c6f20656469746f72]"
	


	# "InspectorWindow" tests
	# -----------------------
	test RezillaInspectorWindow-1-1 {Open the inspector for a resource} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		ASExec "get last window"
	} -cleanup {
	} -result "inspector window 1 of application [ASQuote $rezillaName]"
		
	test RezillaInspectorWindow-1-2 {Close the inspector} -setup {
	} -body {
		ASExec "close the inspector"
		ASExec "get the visible of inspector window 1"
	} -cleanup {
	} -result "false"
		
	test RezillaInspectorWindow-1-3 {Get ID and Name fields} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		set cmd "set a to the ID field of the inspector
			set b to the name field of the inspector
			{a, b}"
		ASExec $cmd
	} -cleanup {
	} -result "{128, [ASQuote "Apple menu"]}"
		
	test RezillaInspectorWindow-1-4 {Get checkboxes} -setup {
	} -body {
		ASExec "inspect resource {\"MPSR\", 1005} of map 1"
		set cmd "set a to the system heap of the inspector
			set b to the purgeable of the inspector
			set c to the locked of the inspector
			set d to the preload of the inspector
			set e to the protected of the inspector
			{a, b, c, d, e}"
		ASExec $cmd
	} -cleanup {
	} -result "{false, false, false, true, false}"
		
	test RezillaInspectorWindow-1-5 {Set the name field} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		ASExec "set the name field of inspector to [ASQuote "Viva Rezilla!!!"]"
		ASExec "get the name field of the inspector"
	} -cleanup {
	} -result "[ASQuote "Viva Rezilla!!!"]"
		
	test RezillaInspectorWindow-1-6 {Set the ID field} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		ASExec "set the ID field of inspector to 250"
		ASExec "get the ID field of the inspector"
	} -cleanup {
	} -result "250"
		
	test RezillaInspectorWindow-1-7 {Set the checkboxes} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		set cmd "set the system heap of inspector to true
		set the purgeable of inspector to true
		set the locked of inspector to true
		set the preload of inspector to true
		set the protected of inspector to true"
		ASExec $cmd
		set cmd "set a to the system heap of the inspector
			set b to the purgeable of the inspector
			set c to the locked of the inspector
			set d to the preload of the inspector
			set e to the protected of the inspector
			{a, b, c, d, e}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, true, true, true, true}"
		
	test RezillaInspectorWindow-1-8 {Revert checkboxes} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		set cmd "set the system heap of inspector to true
		set the purgeable of inspector to true
		set the locked of inspector to true
		set the preload of inspector to true
		set the protected of inspector to true"
		ASExec $cmd
		set cmd "set a to the system heap of the inspector
			set b to the purgeable of the inspector
			set c to the locked of the inspector
			set d to the preload of the inspector
			set e to the protected of the inspector
			{a, b, c, d, e}"
		set result [ASExec $cmd]
		# Now revert
		ASExec "revert the inspector"
		set cmd "set a to the system heap of the inspector
			set b to the purgeable of the inspector
			set c to the locked of the inspector
			set d to the preload of the inspector
			set e to the protected of the inspector
			{a, b, c, d, e}"
		append result [ASExec $cmd]
	} -cleanup {
	} -result "{true, true, true, true, true}{false, false, false, false, false}"
		
	test RezillaInspectorWindow-1-9 {Revert ID and name} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		set cmd "set the name field of inspector to [ASQuote "Viva Rezilla!!!"]
		set the ID field of inspector to 250"
		ASExec $cmd
		set cmd "set a to the ID field of the inspector
			set b to the name field of the inspector
			{a, b}"
		set result [ASExec $cmd]
		# Now revert
		ASExec "revert the inspector"
		set cmd "set a to the ID field of the inspector
			set b to the name field of the inspector
			{a, b}"
		append result [ASExec $cmd]
	} -cleanup {
	} -result "{250, [ASQuote "Viva Rezilla!!!"]}{128, [ASQuote "Apple menu"]}"
		
# # 	test RezillaInspectorWindow-1-10 {Apply checkboxes changes} -setup {
# # 	} -body {
# # 		ASExec "inspect resource {\"MENU\", 128} of map 1"
# # 		set cmd "set the system heap of inspector to true
# # 		set the purgeable of inspector to true
# # 		set the locked of inspector to true
# # 		set the preload of inspector to true
# # 		set the protected of inspector to true"
# # 		# Now apply
# # 		ASExec "save the inspector"
# # 		set cmd "set theRez to resource {\"MENU\", 128} of map 1
# # 			set a to the system heap of theRez
# # 			set b to the purgeable of theRez
# # 			set c to the locked of theRez
# # 			set d to the preload of theRez
# # 			set e to the protected of theRez
# # 			{a, b, c, d, e}"
# # 		ASExec $cmd
# # 	} -cleanup {
# # 		# Close and reopen
# # 		ASExec "close map document [ASQuote $RFname] saving no"
# # 		ASExec "open [ASQuote $rezfileRF] as alias"
# # 	} -result "{true, true, true, true, true}"
# # 		
# # 	test RezillaInspectorWindow-1-11 {Apply ID and name changes} -setup {
# # 	} -body {
# # 		ASExec "inspect resource {\"MENU\", 128} of map 1"
# # 		set cmd "set the name field of inspector to [ASQuote "Viva Rezilla!!!"]
# # 		set the ID field of inspector to 250"
# # 		# Now apply
# # 		ASExec "save the inspector"
# # 		set cmd "set theRez to resource {\"MENU\", 128} of map 1
# # 			set a to the ID of theRez
# # 			set b to the name of theRez
# # 			{a, b}"
# # 		ASExec $cmd
# # 	} -cleanup {
# # 		# Close and reopen
# # 		ASExec "close map document [ASQuote $RFname] saving no"
# # 		ASExec "open [ASQuote $rezfileRF] as alias"
# # 	} -result "{250, [ASQuote "Viva Rezilla!!!"]}"
		

	# "Application" tests
	# -------------------
	test RezillaApplication-1-1 {Get the version number} -setup {
	} -body {
		ASExec "get the version"
	} -cleanup {
	} -match regexp -result {\d+\.\d+(\.\d+)?[dabf]?(\.\d+)?}
		
	test RezillaApplication-1-2 {Get the inspector as object} -setup {
	} -body {
		ASExec "get the inspector"
	} -cleanup {
	} -match regexp \
	  -result "inspector window \\d+ of application [ASQuote $rezillaName]"
		

	# "Document" tests
	# ----------------
	test RezillaDocument-1-1 {Get document by index} -setup {
	} -body {
		ASExec "get document 1"
	} -cleanup {
	} -result "document [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaDocument-1-2 {Get document by index} -setup {
	} -body {
		ASExec "get document [ASQuote $RFname]"
	} -cleanup {
	} -result "document [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaDocument-1-3 {Get name of document} -setup {
	} -body {
		ASExec "get the name of document 1"
	} -cleanup {
	} -result "[ASQuote $RFname]"
		
	test RezillaDocument-1-4 {Get modified flag of document} -setup {
	} -body {
		ASExec "get the modified of document 1"
	} -cleanup {
	} -result "false"
		
	test RezillaDocument-1-5 {Get all documents} -setup {
		ASExec "open [ASQuote $rezfileDF] as alias"
	} -body {
		set reply [ASExec "get documents"]
		set expectedRes "{document [ASQuote $RFname] of application [ASQuote $rezillaName], "
		append expectedRes "document [ASQuote $DFname] of application [ASQuote $rezillaName]}"
		return [expr $reply eq $expectedRes]
	} -cleanup {
		ASExec "close map document [ASQuote $DFname] saving no"
	} -result "1"
		

	# "Window" tests
	# --------------
	test RezillaWindow-1-1 {Get window by index} -setup {
	} -body {
		ASExec "get window 1"
	} -cleanup {
	} -result "window [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaWindow-1-2 {Get window by name} -setup {
	} -body {
		ASExec "get window [ASQuote $RFname]"
	} -cleanup {
	} -result "window [ASQuote $RFname] of application [ASQuote $rezillaName]"
		
	test RezillaWindow-1-3 {Get the title of the window} -setup {
	} -body {
		ASExec "get the name of window 1"
	} -cleanup {
	} -result "[ASQuote $RFname]"
		
	test RezillaWindow-1-4 {Get the index of the window} -setup {
	} -body {
		ASExec "get the index of window [ASQuote $RFname]"
	} -cleanup {
	} -result "1"
		
	test RezillaWindow-1-5 {Get the boundary rectangle} -setup {
	} -body {
		ASExec "get the bounds of window 1"
	} -cleanup {
	} -match regexp -result "{\\d+, \\d+, \\d+, \\d+}"
		
	test RezillaWindow-1-6 {Get the upper left coordinates of the window} -setup {
	} -body {
		ASExec "get the position of window 1"
	} -cleanup {
	} -match regexp -result "{\\d+, \\d+}"
		
	test RezillaWindow-1-7 {Get boolean properties of the window} -setup {
	} -body {
		set cmd "set win to window 1
			set a to the closeable of win
			set b to the titled of win
			set c to the floating of win
			set d to the modal of win
			set e to the resizable of win
			set f to the zoomable of win
			set g to the zoomed of win
			set h to the visible of win
			{a, b, c, d, e, f, g, h}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, true, false, false, true, true, false, true}"
		
	test RezillaWindow-1-8 {Set the title} -setup {
	} -body {
	set orig [ASExec "get the name of window 1"]
	ASExec "set the name of window 1 to [ASQuote "New title"]"
	set result [ASExec "get the name of window 1"]
	ASExec "set the name of window 1 to $orig"
	return $result
	} -cleanup {
	} -result "[ASQuote "New title"]"
		
	test RezillaWindow-1-9 {Set the bounds} -setup {
	} -body {
		set orig [ASExec "get the bounds of window 1"]
		ASExec "set the bounds of window 1 to {50, 150, 200, 300}"
		set result [ASExec "get the bounds of window 1"]
		ASExec "set the bounds of window 1 to $orig"
		return $result
	} -cleanup {
	} -result "{50, 150, 200, 300}"
		
	test RezillaWindow-1-10 {Resize the window to maximum} -setup {
	} -body {
		set orig [ASExec "get the zoomed of window 1"]
		ASExec "set the zoomed of window 1 to true"
		set result [ASExec "get the zoomed of window 1"]
		ASExec "set the zoomed of window 1 to $orig"
		return $result
	} -cleanup {
	} -result "true"
		
	test RezillaWindow-1-11 {Reposition the window} -setup {
	} -body {
		set orig [ASExec "get the position of window 1"]
		ASExec "set the position of window 1 to {200, 100}"
		set result [ASExec "get the position of window 1"]
		ASExec "set the position of window 1 to $orig"
		return $result
	} -cleanup {
	} -result "{200, 100}"
		
	test RezillaWindow-1-12 {Hide the window} -setup {
	} -body {
		set orig [ASExec "get the visible of window 1"]
		ASExec "set the visible of window 1 to false"
		set result [ASExec "get the visible of window 1"]
		ASExec "set the visible of window 1 to $orig"
		return $result
	} -cleanup {
	} -result "false"
		

	# "Quit" tests
	# ------------
# 	test RezillaQuit-1-1 {} -setup {
# 	} -body {
# 		ASExec "quit"
# 	} -cleanup {
# 	} -result ""
		
		
	# "Close" tests
	# -------------
	test RezillaClose-1-1 {Close a map document} -setup {
	} -body {
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "exists map document [ASQuote $RFname]"
	} -cleanup {
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "false"
		
	test RezillaClose-1-2 {Close editor documents} -setup {
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
	} -body {
		set cmd "set a to hexadecimal window 1 of document 1 exists
			set b to template window 1 of document 1 exists
			set c to interface window 1 of document 1 exists
			{a, b, c}"
		set result [ASExec $cmd]
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ckid' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
		append result [ASExec $cmd]
	} -cleanup {
	} -result "{true, true, true}{false, false, false}"
		
	test RezillaClose-1-3 {Close a map window} -setup {
	} -body {
		ASExec "close map window 1"
		ASExec "exists map window 1"
	} -cleanup {
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "false"
		
	test RezillaClose-1-4 {Close editing windows} -setup {
		ASExec "edit resource {\"Abou\",128} of map document 1"
		ASExec "edit resource {\"ALRT\",128} of map document 1"
		ASExec "edit resource {\"MENU\",128} of map document 1"
	} -body {
		set cmd "set a to editing window 1 of document 1 exists
			set b to editing window 2 of document 1 exists
			set c to editing window 3 of document 1 exists
			{a, b, c}"
		set result [ASExec $cmd]
		# Using index 1 for all of them
		ASExec "close editing window 1 of map document 1"
		ASExec "close editing window 1 of map document 1"
		ASExec "close editing window 1 of map document 1"
		append result [ASExec $cmd]
	} -cleanup {
	} -result "{true, true, true}{false, false, false}"
		
	test RezillaClose-1-5 {Close editing windows of particular kind} -setup {
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
	} -body {
		set cmd "set a to hexadecimal window 1 of document 1 exists
			set b to template window 1 of document 1 exists
			set c to interface window 1 of document 1 exists
			{a, b, c}"
		set result [ASExec $cmd]
		ASExec "close template window 1 of map document 1"
		ASExec "close hexadecimal window 1 of map document 1"
		ASExec "close interface window 1 of map document 1"
		append result [ASExec $cmd]
	} -cleanup {
	} -result "{true, true, true}{false, false, false}"
		
	test RezillaClose-1-6 {Close a comparison window} -setup {
	} -body {
		ASExec "compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias"
		ASExec "close window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
		ASExec "exists window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
	} -cleanup {
	} -result "false"
	
	test RezillaClose-1-7 {Close the inspector} -setup {
	} -body {
		ASExec "inspect resource {\"MENU\", 128} of map 1"
		set result [ASExec "get the visible of the inspector"]
		ASExec "close the inspector"
		append result "-"
		append result [ASExec "get the visible of the inspector"]
	} -cleanup {
	} -result "true-false"
		

	# "Count" tests
	# -------------
	test RezillaCount-1-1 {Count windows and documents} -setup {
		ASExec "edit resource {\"Abou\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
		ASExec "edit resource {\"MENU\",129} of map document 1 using template"
		ASExec "edit resource {\"MPSR\",1005} of map document 1 using hexadecimal"
		ASExec "edit resource {\"STR#\",129} of map document 1 using template"
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"TEXT\",129} of map document 1 using interface"
		ASExec "edit resource {\"TEXT\",130} of map document 1 using template"
	} -body {
		set cmd "-- windows count
			set a to count windows
			set b to count map windows
			set c to count editing windows
			set d to count hexadecimal windows
			set e to count template windows
			set f to count interface windows
			set g to count comparison windows
			-- documents count
			set h to count documents
			set i to count map documents
			set j to count editors
			set k to count hexadecimal editors
			set l to count template editors
			set m to count interface editors

			{a, b, c, d, e, f, g, h, i, j, k, l, m}
			"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'Abou' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ckid' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MPSR' #1005"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'STR#' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #129"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'TEXT' #130"] of map document 1"
	} -result "{12, 1, 10, 4, 4, 2, 0, 11, 1, 10, 4, 4, 2}"
		
	test RezillaCount-1-2 {} -setup {
	} -body {
		set cmd "set a to count maps
			set b to count types of map 1
			set c to count resources of type \"TEXT\" of map 1
			{a, b, c}
			"
		ASExec $cmd
	} -cleanup {
	} -result "{1, 7, 3}"


	# "DataSize" tests
	# ----------------
	test RezillaDataSize-1-1 {Data size of window} -setup {
	} -body {
		ASExec "data size of first window"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaDataSize-1-2 {Data size of map window} -setup {
	} -body {
		ASExec "data size of map window 1"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaDataSize-1-3 {Data size of document} -setup {
	} -body {
		ASExec "data size of first document"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaDataSize-1-4 {Data size of map} -setup {
	} -body {
		ASExec "data size of first map"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaDataSize-1-5 {Data size of type} -setup {
	} -body {
		ASExec "data size of type \"TEXT\" of first map"
	} -cleanup {
	} -match regexp -result {\d+}
		
	test RezillaDataSize-1-6 {Data size of editor} -setup {
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
	} -body {
		set cmd "set a to data size of hexadecimal editor 1 of first document
			set b to data size of template editor 1 of first document
			set c to data size of interface editor 1 of first document
			{a, b, c}"
			ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ckid' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
	} -match regexp -result "{\\d+, \\d+, \\d+}"
		
	test RezillaDataSize-1-7 {} -setup {
	} -body {
		ASExec "data size of resource {\"MENU\",128} of map document 1"
	} -cleanup {
	} -match regexp -result "36"
		
	test RezillaDataSize-1-8 {} -setup {
	} -body {
		ASExec "data size of inspector"
	} -cleanup {
	} -match regexp -result {\d+}
		

	# "Exists" tests
	# --------------
	test RezillaExists-1-1 {Existence of windows} -setup {
	} -body {
		set cmd "set a to first window exists
		set b to second window exists
		set c to third window exists
		{a, b, c}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, true, false}"
		
	test RezillaExists-1-2 {Existence of map window} -setup {
	} -body {
		ASExec "exists map window 1"
	} -cleanup {
	} -result "true"
		
	test RezillaExists-1-3 {Existence of inspector window} -setup {
	} -body {
		ASExec "exists the inspector"
	} -cleanup {
	} -result "true"
		
	test RezillaExists-1-4 {Existence of editing windows} -setup {
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
	} -body {
		set cmd "set a to first editing window of document 1 exists
		set b to hexadecimal window 1 of document 1 exists
		set c to template window 1 of document 1 exists
		set d to interface window 1 of document 1 exists
		{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ckid' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
	} -result "{true, true, true, true}"
		
	test RezillaExists-1-5 {Non existing editing windows} -setup {
	} -body {
		set cmd "set a to first editing window of document 1 exists
		set b to hexadecimal window 1 of document 1 exists
		set c to template window 1 of document 1 exists
		set d to interface window 1 of document 1 exists
		{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
	} -result "{false, false, false, false}"
		
	test RezillaExists-1-6 {Existence of documents} -setup {
	} -body {
		set cmd "set a to first document exists
		set b to second document exists
		{a, b}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, false}"
		
	test RezillaExists-1-7 {Existence of editors} -setup {
		ASExec "edit resource {\"ALRT\",128} of map document 1 using template"
		ASExec "edit resource {\"ckid\",128} of map document 1 using hexadecimal"
		ASExec "edit resource {\"MENU\",128} of map document 1 using interface"
	} -body {
		set cmd "set a to first editor of document 1 exists
		set b to hexadecimal editor 1 of document 1 exists
		set c to template editor 1 of document 1 exists
		set d to interface editor 1 of document 1 exists
		{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close editor [ASQuote "$RFname - 'ALRT' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'ckid' #128"] of map document 1"
		ASExec "close editor [ASQuote "$RFname - 'MENU' #128"] of map document 1"
	} -result "{true, true, true, true}"
		
	test RezillaExists-1-8 {Non existing editors} -setup {
	} -body {
		set cmd "set a to first editor of document 1 exists
		set b to hexadecimal editor 1 of document 1 exists
		set c to template editor 1 of document 1 exists
		set d to interface editor 1 of document 1 exists
		{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
	} -result "{false, false, false, false}"
		
	test RezillaExists-1-9 {Existence of maps} -setup {
	} -body {
		set cmd "set a to first map exists
		set b to second map exists
		set c to map of document 1 exists
		{a, b, c}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, false, true}"
		
	test RezillaExists-1-10 {Existence of types} -setup {
	} -body {
		set cmd "set a to type \"MENU\" of first map exists
		set b to type \"XYZT\" of first map exists
		set c to type 7 of first map exists
		set d to type 8 of first map exists
		{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, false, true, false}"
		
	test RezillaExists-1-11 {Existence of resources} -setup {
	} -body {
		set cmd "set theType to type \"TEXT\" of map 1
			set a to exists resource id 128 of theType
			set b to exists resource id 150 of theType
			set c to exists resource \"Vivat\" of theType
			set d to exists resource id 128 of type \"MENU\" of map 1
			set e to exists resource {\"MENU\", 128} of map document 1
		{a, b, c, d, e}"
		ASExec $cmd
	} -cleanup {
	} -result "{true, false, true, true, true}"
		
	test RezillaExists-1-12 {Existence of comparison window} -setup {
	} -body {
		ASExec "compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias"
		ASExec "exists window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
	} -cleanup {
		ASExec "close window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
# # # 		ASExec "close window 1"
	} -result "true"
		

	# "Make" tests
	# ------------
	test RezillaMake-1-1 {Make a new rezmap in default fork} -setup {
	} -body {
		DeleteIfExists [TestFile make 1]
			# Caveat: use "as alias" to create the folder because this
			# "make" command explicitely looks for an 'alis'. This raises a
			# warning, in the debug build, which can be ignored.
		
		set cmd "tell application [ASQuote Finder]
				set theFolder to folder [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias
			end tell
			make new map document in theFolder with properties {name:[ASQuote [TestFile make 1]]}"
		set result [ASExec $cmd]
	} -cleanup {
		ASExec "close map document [ASQuote [TestFile make 1]]"
		DeleteIfExists [TestFile make 1]
	} -result "document [ASQuote [TestFile make 1]] of application [ASQuote $rezillaName]"

	test RezillaMake-1-2 {Make a new rezmap in specified fork} -setup {
	} -body {
		DeleteIfExists [TestFile make 2]
		set cmd "tell application [ASQuote Finder]
				set theFolder to folder [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias
			end tell
			make new map document in theFolder with properties {name:[ASQuote [TestFile make 2]],fork:resource fork}"
		ASExec $cmd
		ASExec "get the fork of document [ASQuote [TestFile make 2]]"
	} -cleanup {
		ASExec "close map document [ASQuote [TestFile make 2]]"
		DeleteIfExists [TestFile make 2]
	} -result "ResourceFork"
		
	test RezillaMake-1-3 {Make a read-only rezmap in default fork} -setup {
	} -body {
		DeleteIfExists [TestFile make 3]
		set cmd "tell application [ASQuote Finder]
				set theFolder to folder [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias
			end tell
			make new map document in theFolder with properties {name:[ASQuote [TestFile make 3]],readOnly:true}"
		ASExec $cmd
		set cmd "set a to the fork of document [ASQuote [TestFile make 3]]
			set b to the readOnly of document [ASQuote [TestFile make 3]]
			{a, b}"
		ASExec $cmd
	} -cleanup {
		ASExec "close map document [ASQuote [TestFile make 3]]"
		DeleteIfExists [TestFile make 3]
	} -result "{DataFork, true}"
		
	test RezillaMake-1-4 {Create an empty resource of specified type} -setup {
	} -body {
		ASExec "make new resource in map document 1 with properties {type:[ASQuote ckid]}"
	} -cleanup {
	} -match regexp \
	  -result "resource id \\d+ of type [ASQuote ckid] of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaMake-1-5 {Create a new resource with properties} -setup {
	} -body {
		set cmd "make new resource in map document 1 "
		append cmd "with properties {ID:150, type:[ASQuote MENU], name:[ASQuote "New menu"], protected:true}"
		set reply [ASExec $cmd]
		set cmd "set a to the ID of $reply
			set b to the type of $reply
			set c to the name of $reply
			set d to the protected of $reply
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
	} -result "{150, [ASQuote MENU], [ASQuote "New menu"], true}"
		
	test RezillaMake-1-6 {Create a new resource with data} -setup {
	} -body {
		set cmd "make new resource in map document 1 "
		append cmd "with properties {type:[ASQuote ALRT]}"
		append cmd "with data [ASQuote 001400140087016800805555300a]"
		set reply [ASExec $cmd]
		ASExec "set a to the hex data of $reply"
	} -cleanup {
	} -result "[ASQuote 001400140087016800805555300a]"
		
	test RezillaMake-1-7 {Create a new TEXT resource with string} -setup {
	} -body {
		set cmd "make new resource in map document 1 "
		append cmd "with properties {type:[ASQuote TEXT]}"
		append cmd "with data [ASQuote "Rezilla is great"]"
		set reply [ASExec $cmd]
		ASExec "set a to the hex data of $reply"
	} -cleanup {
	} -result "[ASQuote "Rezilla is great"]"
		
	test RezillaMake-1-8 {Create a new resource with default type (TEXT)} -setup {
	} -body {
		ASExec "make new resource in map document 1"
	} -cleanup {
	} -match regexp \
	  -result "resource id \\d+ of type [ASQuote TEXT] of map id \\d+ of application [ASQuote $rezillaName]"
		
	test RezillaMake-1-9 {} -setup {
	} -body {
		set cmd "make new resource in map document 1 "
		append cmd "with properties {type:[ASQuote "STR#"]}"
		append cmd "with data {[ASQuote "alpha"], [ASQuote "beta"]}"
		set reply [ASExec $cmd]
		ASExec "set a to the hex data of $reply"
	} -cleanup {
	} -result "{[ASQuote "alpha"], [ASQuote "beta"]}"
		

# # # Cleanup after "Make" tests

#################################################
	
	# 	for {set i 1} {$i <= 3} {incr i} {
	# 		DeleteIfExists [TestFile make $i]
	# 	}

	### Close and reopen the map
	ASExec "close map document [ASQuote $RFname] saving no"
	ASExec "open [ASQuote $rezfileRF] as alias"

#################################################


	# "Save" tests
	# ------------
	test RezillaSave-1-1 {Save a map document} -setup {
		DeleteIfExists [TestFile save 1]		
	} -body {
		# Create a rezmap
		set cmd "tell application [ASQuote Finder]
				set theFolder to folder [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias
			end tell
			make new map document in theFolder with properties {name:[ASQuote [TestFile save 1]]}"
		set newDoc [ASExec $cmd]
		# Add a resource
		ASExec "make new resource in map $newDoc with data [ASQuote "Save map test"]"
		# Save and close
		ASExec "save document [ASQuote [TestFile save 1]]"
		ASExec "close document [ASQuote [TestFile save 1]] saving no"
		# Reopen it
		ASExec "open [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks [TestFile save 1]]]] as alias"
		ASExec "get all types of map of map document [ASQuote [TestFile save 1]]"	
	} -cleanup {
		ASExec "close document [ASQuote [TestFile save 1]] saving no"
		DeleteIfExists [TestFile save 1]		
	} -result "{[ASQuote TEXT]}"
		
	test RezillaSave-1-2 {Save a resource modified in an editor} -setup {
		DeleteIfExists [TestFile save 2]		
	} -body {
		# Create a rezmap
		set cmd "tell application [ASQuote Finder]
				set theFolder to folder [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias
			end tell
			make new map document in theFolder with properties {name:[ASQuote [TestFile save 2]]}"
		set newDoc [ASExec $cmd]
		# Add a resource
		ASExec "make new resource in map $newDoc with data [ASQuote "Save map test"] with properties {ID:128}"
		# Modify this resource in the hex editor
		set hexDoc [ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"]
		set cmd "set win to hexadecimal window 1 of map document 1
			set the startPos of win to 5
			set the endPos of win to 8
			set the text selection of win to [ASQuote Rezilla]"
		ASExec $cmd
		# Save it
		ASExec "save $hexDoc"
		set result [ASExec "get modified of $hexDoc"]
	} -cleanup {
		ASExec "close document [ASQuote [TestFile save 2]] saving no"
		DeleteIfExists [TestFile save 2]
	} -result "false"
		
	test RezillaSave-1-3 {Save modifications in the inspector} -setup {
	} -body {
		ASExec "inspect resource {\"TEXT\", 128} of map 1"
		set orig [ASExec "get the name of resource {\"TEXT\", 128} of map 1"]
		ASExec "set the name field of inspector to [ASQuote "New name"]"
		ASExec "save the inspector"
		# set result [ASExec "get the name of resource {\"TEXT\", 128} of map 1"]
		# ASExec "set the name field of inspector to $orig"
		# return $result
	} -cleanup {
		ASExec "close the inspector"
	} -result ""
		
	test RezillaSave-1-4 {Save forbidden ID in inspector} -setup {
	} -body {
		ASExec "inspect resource {\"TEXT\", 128} of map 1"
		ASExec "set the ID field of inspector to 130"
		catch {ASExec "save the inspector"} result
		return $result
	} -cleanup {
		ASExec "close the inspector"
	} -match glob -result "An AppleScript error was encountered*"
		

	# "Revert" tests
	# --------------
	# Note 1: there are other "revert" tests with the Inspector Window tests
	# 
	# Note 2: some editors understand the "revert" command (template, aete, 
	# and menu editors). Don't know how to test that.

	test RezillaRevert-1-1 {} -setup {
	} -body {
		set precount [ASExec "count resources of type \"TEXT\" of map 1"]
		ASExec "make new resource in map document 1"
		set midcount [ASExec "count resources of type \"TEXT\" of map 1"]
		ASExec "revert map document 1"
		set postcount [ASExec "count resources of type \"TEXT\" of map 1"]
		return "[expr {$midcount - $precount}]-[expr {$postcount - $precount}]"
	} -cleanup {
	} -result "1-0"

	test RezillaRevert-1-2 {} -setup {
	} -body {
	} -cleanup {
	} -result ""
		
	test RezillaRevert-1-3 {} -setup {
	} -body {
	} -cleanup {
	} -result ""
		

	# "Compare" tests
	# ---------------
	test RezillaCompare-1-1 {Compare two files and check comparison window} -setup {
	} -body {
		ASExec "compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias"
		ASExec "get window 1"
	} -cleanup {
		# # ASExec "close window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
		ASExec "close window 1"
	} -result "window [ASQuote "Comparison window \[1\]"] of application [ASQuote $rezillaName]"
		
	test RezillaCompare-1-2 {Get the comparison criteria} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias
			get the criteria of theComp"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{ignoreName:true, ignoreAttrs:true, ignoreData:false}"
		
	test RezillaCompare-1-3 {Get modified comparison criteria} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias "
		append cmd "without ignoreName without ignoreAttrs with ignoreData\r"
		append cmd "get the criteria of theComp"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{ignoreName:false, ignoreAttrs:false, ignoreData:true}"
		
	test RezillaCompare-1-4 {Lists of compared resources} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias
			set a to the old only resources of theComp
			set b to the new only resources of theComp
			set c to the differing resources of theComp
			set d to the identical resources of theComp
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{{{\"TEXT\", 130}}, {{\"TEXT\", 131}}, {{\"Abou\", 128}, {\"TEXT\", 128}}, {{\"ALRT\", 128}, {\"ckid\", 128}, {\"MENU\", 128}, {\"MENU\", 129}, {\"MPSR\", 1005}, {\"STR#\", 129}, {\"TEXT\", 129}}}"
		
	test RezillaCompare-1-5 {Lists of compared resources with ignoreName:false} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias without ignoreName
			set a to the old only resources of theComp
			set b to the new only resources of theComp
			set c to the differing resources of theComp
			set d to the identical resources of theComp
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{{{\"TEXT\", 130}}, {{\"TEXT\", 131}}, {{\"Abou\", 128}, {\"STR#\", 129}, {\"TEXT\", 128}}, {{\"ALRT\", 128}, {\"ckid\", 128}, {\"MENU\", 128}, {\"MENU\", 129}, {\"MPSR\", 1005}, {\"TEXT\", 129}}}"
		
	test RezillaCompare-1-6 {Lists of compared resources with ignoreAttrs:false} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias without ignoreAttrs
			set a to the old only resources of theComp
			set b to the new only resources of theComp
			set c to the differing resources of theComp
			set d to the identical resources of theComp
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{{{\"TEXT\", 130}}, {{\"TEXT\", 131}}, {{\"Abou\", 128}, {\"ckid\", 128}, {\"MPSR\", 1005}, {\"TEXT\", 128}}, {{\"ALRT\", 128}, {\"MENU\", 128}, {\"MENU\", 129}, {\"STR#\", 129}, {\"TEXT\", 129}}}"
		
	test RezillaCompare-1-7 {Lists of compared resources with ignoreData:true} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias with ignoreData
			set a to the old only resources of theComp
			set b to the new only resources of theComp
			set c to the differing resources of theComp
			set d to the identical resources of theComp
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{{{\"TEXT\", 130}}, {{\"TEXT\", 131}}, {}, {{\"Abou\", 128}, {\"ALRT\", 128}, {\"ckid\", 128}, {\"MENU\", 128}, {\"MENU\", 129}, {\"MPSR\", 1005}, {\"STR#\", 129}, {\"TEXT\", 128}, {\"TEXT\", 129}}}"
		
	test RezillaCompare-1-8 {Lists of compared resources ignoring only data diffs} -setup {
	} -body {
		set cmd "set theComp to compare [ASQuote $rezfileRF] as alias and [ASQuote $rezfileDF] as alias with ignoreData without ignoreName without ignoreAttrs
			set a to the old only resources of theComp
			set b to the new only resources of theComp
			set c to the differing resources of theComp
			set d to the identical resources of theComp
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
		ASExec "close window 1"
	} -result "{{{\"TEXT\", 130}}, {{\"TEXT\", 131}}, {{\"Abou\", 128}, {\"ckid\", 128}, {\"MPSR\", 1005}, {\"STR#\", 129}}, {{\"ALRT\", 128}, {\"MENU\", 128}, {\"MENU\", 129}, {\"TEXT\", 128}, {\"TEXT\", 129}}}"
		

	# "Delete" tests
	# --------------
	test RezillaDelete-1-1 {Delete a resource among several of same type} -setup {
	} -body {
		ASExec "delete resource {\"MENU\", 128} of map 1
			set a to exists resource {\"MENU\", 128} of map 1
			set b to exists type \"MENU\" of map 1
			{a, b}"
	} -cleanup {
		# Close and reopen
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "{false, true}"
		
	test RezillaDelete-1-2 {Delete a resource unique in its type} -setup {
	} -body {
		ASExec "delete resource {\"Abou\", 128} of map 1
			set a to exists resource {\"Abou\", 128} of map 1
			set b to exists type \"Abou\" of map 1
			{a, b}"
	} -cleanup {
		# Close and reopen
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "{false, false}"
		
	test RezillaDelete-1-3 {Delete a type (with single resource included)} -setup {
	} -body {
		ASExec "delete type \"Abou\" of map 1
			set a to exists resource {\"Abou\", 128} of map 1
			set b to exists type \"Abou\" of map 1
			{a, b}"
	} -cleanup {
		# Close and reopen
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "{false, false}"
		
	test RezillaDelete-1-4 {Delete a type (with several resources included)} -setup {
	} -body {
		ASExec "delete type \"MENU\" of map 1
			set a to exists resource {\"MENU\", 128} of map 1
			set b to exists type \"MENU\" of map 1
			{a, b}"
	} -cleanup {
		# Close and reopen
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "{false, false}"
		

	# "Duplicate" tests
	# -----------------
	test RezillaDuplicate-1-1 {} -setup {
	} -body {
		ASExec "set theDup to duplicate resource {\"ALRT\", 128} of map 1
			set a to the name of theDup
			set b to the size of theDup
			set c to the attributes of theDup
			set d to the hex data of theDup
			{a, b, c, d}"
	} -cleanup {
		# Close and reopen
		ASExec "close map document [ASQuote $RFname] saving no"
		ASExec "open [ASQuote $rezfileRF] as alias"
	} -result "{[ASQuote "Alert copy"], 14, 2, [ASQuote 002800280087017c00805555300a]}" 


	# "Edit" tests
	# ------------
		
	test RezillaEdit-1-1 {} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using hexadecimal"
	} -body {
		ASExec "get the kind of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "hexadecimal"
		
	test RezillaEdit-1-2 {} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using template"
	} -body {
		ASExec "get the kind of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "template"
		
	test RezillaEdit-1-3 {} -setup {
		ASExec "edit resource {\"TEXT\",128} of map document 1 using interface"
	} -body {
		ASExec "get the kind of editor 1 of map document 1"
	} -cleanup {
		ASExec "close editor 1 of map document 1"
	} -result "interface"
		
	test RezillaEdit-1-4 {Edit as other type} -setup {
	} -body {
		ASExec "edit resource {\"Abou\",128} of map document 1"
		set result [ASExec "get the kind of editor 1 of map document 1"]
		ASExec "close editor 1 of map document 1"
		ASExec "edit resource {\"Abou\",128} of map document 1 like \"TEXT\""
		append result "-"
		append result [ASExec "get the kind of editor 1 of map document 1"]
		ASExec "close editor 1 of map document 1"
		return $result
	} -cleanup {
	} -result "hexadecimal-interface"
		
	test RezillaEdit-1-5 {Edit as other type using specified editor} -setup {
	} -body {
		ASExec "edit resource {\"Abou\",128} of map document 1"
		set result [ASExec "get the kind of editor 1 of map document 1"]
		ASExec "close editor 1 of map document 1"
		ASExec "edit resource {\"Abou\",128} of map document 1 like \"TEXT\" using template"
		append result "-"
		append result [ASExec "get the kind of editor 1 of map document 1"]
		ASExec "close editor 1 of map document 1"
		return $result
	} -cleanup {
	} -result "hexadecimal-template"
		

	# "Export" tests
	# --------------
	test RezillaExport-1-1 {Exporting a resource map with default format} -setup {
	} -body {
		set ext [ASExec "get the format of map document 1"]
		set cmd "export map document 1 in [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias "
		append cmd "with properties {name:[ASQuote exportedMap.$ext]}"
		ASExec $cmd
	} -cleanup {
	} -result ""
		
	test RezillaExport-1-2 {Exporting a resource map with default name} -setup {
	} -body {
		set cmd "export map document 1 in [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias"
		ASExec $cmd
	} -cleanup {
	} -result ""
		
	test RezillaExport-1-3 {Exporting a resource map in html format} -setup {
	} -body {
		set cmd "export map document 1 in [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias "
		append cmd "with properties {name:[ASQuote exportedMap.html], format:html}"
		ASExec $cmd
	} -cleanup {
	} -result ""
		
	test RezillaExport-1-4 {Exporting a resource map in text format} -setup {
	} -body {
		set cmd "export map document 1 in [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias "
		append cmd "with properties {name:[ASQuote exportedMap.txt], format:text}"
		ASExec $cmd
	} -cleanup {
	} -result ""
		
	test RezillaExport-1-5 {Exporting a resource map in DeRez format} -setup {
	} -body {
		set cmd "export map document 1 in [ASQuote [unixPathToFinder [file join [file dir [info script]] Forks]]] as alias "
		append cmd "with properties {name:[ASQuote exportedMap.r], format:DeRez}"
		ASExec $cmd
	} -cleanup {
	} -result ""
	
		
	# # Cleanup after "Export" tests
	foreach ext [list xml html txt r] {
		DeleteIfExists exportedMap.$ext
	} 
	
	
	# "Plugin" tests
	# --------------
	test RezillaPlugin-1-1 {Get the list of plugins} -setup {
	} -body {
		set success 1
		set getplug [ASExec "get plugins"]
		foreach p [getPluginsList] {
			set line "plugin [ASQuote $p] of application [ASQuote $rezillaName]"
			if {![string match "*${line}*" $getplug]} {
				set success 0
				break
			} 
		} 
		return $success
	} -cleanup {
	} -result "1"

	test RezillaPlugin-1-2 {Count the plugins} -setup {
	} -body {
		ASExec "count plugins"
	} -cleanup {
	} -result "[llength [getPluginsList]]"

	test RezillaPlugin-1-3 {Existence of RezImage plugin} -setup {
	} -body {
		ASExec "exists plugin [ASQuote RezImagePlugin.plugin] of application [ASQuote $rezillaName]"
	} -cleanup {
	} -result "true"

	test RezillaPlugin-1-4 {Properties of the RezImage plugin} -setup {
	} -body {
		set cmd "set thePlug to plugin [ASQuote RezImagePlugin.plugin] of application [ASQuote $rezillaName]
			set a to name of thePlug
			set b to typecode of thePlug
			set c to creator of thePlug
			set d to loaded of thePlug
			{a, b, c, d}"
		ASExec $cmd
	} -cleanup {
	} -result "{[ASQuote RezImagePlugin.plugin], [ASQuote BNDL], [ASQuote Rzil], false}"

	test RezillaPlugin-1-5 {Supported types of the RezImage plugin} -setup {
	} -body {
		ASExec "get supported types of plugin [ASQuote RezImagePlugin.plugin] of application [ASQuote $rezillaName]"
	} -cleanup {
	} -result "{[ASQuote "JPEG"], [ASQuote "jpeg"], [ASQuote "JPG "], [ASQuote "jpg "], [ASQuote "TIFF"], [ASQuote "tiff"], [ASQuote "GIF "], [ASQuote "gif "], [ASQuote "PNG "], [ASQuote "png "], [ASQuote "BMP "], [ASQuote "bmp "]}"

	test RezillaPlugin-1-6 {List of preferred plugins} -setup {
	} -body {
		set reco [ASExec "get preferred plugin"]
		return [string match "*JPEG picture:*" $reco"]
	} -cleanup {
	} -result "1"

	test RezillaPlugin-1-7 {} -setup {
	} -body {
# 		ASExec "set preferred plugin to {\\U00ABclass tiff\\U00BB:[ASQuote RezImagePlugin.plugin], \\U00ABclass jpg \\U00BB:[ASQuote RezImagePlugin.plugin]}"
# 		ASExec "set preferred plugin to {Çclass tiffÈ:[ASQuote RezImagePlugin.plugin], Çclass jpg È:[ASQuote RezImagePlugin.plugin]}"
	} -cleanup {
	} -result ""

	test RezillaPlugin-1-8 {Version of the RezImage plugin} -setup {
	} -body {
		ASExec "get version of plugin [ASQuote RezImagePlugin.plugin] of application [ASQuote $rezillaName]"
	} -cleanup {
	} -match regexp -result "\\d+\\.\\d+"

	test RezillaPlugin-1-9 {Get index by name} -setup {
	} -body {
		set cmd "set theName to name of plugin 1
			get index of plugin theName"
		ASExec $cmd
	} -cleanup {
	} -result "1"

	test RezillaPlugin-1-10 {Name of all the plugins} -setup {
	} -body {
		set success 1
		set namelist [ASExec "get name of plugins"]
		foreach p [getPluginsList] {
			if {![string match "*[ASQuote $p]*" $namelist]} {
				set success 0
				break
			} 
		} 
		return $success
	} -cleanup {
	} -result "1"
	


	
# # # Closing $rezfileRF

#################################################

	ASExec "close map document [ASQuote $RFname] saving no"

#################################################

}

namespace delete ::rezilla::test


# Cleanup
puts stdout "\nEnd of tests [clock format [clock seconds]]"
::tcltest::cleanupTests 0


