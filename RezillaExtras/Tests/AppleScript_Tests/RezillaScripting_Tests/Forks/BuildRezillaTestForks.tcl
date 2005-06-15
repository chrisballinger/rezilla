# -------------------------------------------------------
# BuildRezillaTestForks.tcl
#                        Created: 2005-04-17 07:54:17
#              Last modification: 2005-06-01 08:08:36
# Author: Bernard Desgraupes
# e-mail: <bdesgraupes@easyconnect.fr>
# www: <http://webperso.easyconnect.fr/bdesgraupes/>
# (c) Copyright: Bernard Desgraupes, 2005
# All rights reserved.
# 
# $Date$
# $Revision$
# -------------------------------------------------------

package require resource 1.1

namespace eval tmp {}

set tmp::date [clock format [clock seconds]]

set tmp::testdir [file dir [info script]]

# Build a datafork and a resourcefork resource file
foreach tmp::suffix [list DF RF] {
	if {$tmp::suffix eq "DF"} {
		set tmp::whichfork datafork
	} else {
		set tmp::whichfork resourcefork
	}
	
	set tmp::resfile [file join $tmp::testdir TestRezilla${tmp::suffix}.rsrc]
	if {[file exists $tmp::resfile]} {
		file delete $tmp::resfile
	} 
	set tmp::rid [resource open -$tmp::whichfork $tmp::resfile w+]
	# TEXT
	resource write -id 128 -name "Hello" -file $tmp::rid TEXT "Hello Rezilla ($tmp::whichfork)!"
	resource write -id 129 -name "Vivat" -file $tmp::rid TEXT "Viva Rezilla!"
	resource write -id [expr {($tmp::suffix eq "RF")? 130:131}] -name "$tmp::suffix wishes" -file $tmp::rid TEXT "Happy rezing with Rezilla!"
	# STR#
	resource write -id 129 -name "$tmp::suffix Greetings" -file $tmp::rid "STR#" "\x00\x02\x05Hello\x05Salud"
	# MENU
	set hexdata  "\x00\x80\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\x01\x14\x0e\x41\x62\x6f\x75\x74\x20\x52\x65\x7a\x69\x6c\x6c\x61\xc9\x00\x00\x00\x00\x00"
	resource write -id 128 -name "Apple menu" -file $tmp::rid MENU $hexdata
	set hexdata  "\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\x05\x53\x74\x79\x6c\x65\x05\x50\x6c\x61\x69\x6e\x00\x00\x00\x00\x04\x42\x6f\x6c\x64\x00\x00\x00\x01\x06\x49\x74\x61\x6c\x69\x63\x00\x00\x00\x02\x09\x55\x6e\x64\x65\x72\x6c\x69\x6e\x65\x00\x00\x00\x04\x00"
	resource write -id 129 -name "Style menu" -file $tmp::rid MENU $hexdata
	# ALRT
	set hexdata "\x00\x28\x00\x28\x00\x87\x01\x7c\x00\x80\x55\x55\x30\x0a"
	resource write -id 128 -name "Alert" -file $tmp::rid ALRT $hexdata
	# MPSR - this resource intentionally has no name
	set hexdata "\x00\x09\x4d\x6f\x6e\x61\x63\x6f\x00\x4c\x25\xb0\x00\x05\x00\x00\xbf\x80\x00\x00\x00\x00\x00\x00\x43\xcc\x80\x00\x00\x00\x00\x00\x00\x00\x00\x06\x00\x04\x00\x3b\x00\x1e\x01\xbe\x02\xff\x00\x3b\x00\x1e\x01\xbe\x02\xff\xbd\x5f\xe3\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00"
	resource write -id 1005 -file $tmp::rid MPSR $hexdata
	# ckid - "2f637673726f6f742f74636c" means "/cvsroot/tcl"
	set hexdata  "\x76\x52\x90\x1a\x3f\xe5\x32\x30\x00\x04\x00\x00\x00\x00\x00\x00\x00\x00\xbd\x28\x04\x36\xbd\x28\x04\x36\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x2a\x2f\x63\x76\x73\x72\x6f\x6f\x74\x2f\x74\x63\x6c\x2f\x54\x63\x6c\x2f\x4d\x65\x6e\x75\x73\x2f\x63\x6f\x6c\x6f\x72\x73\x4d\x65\x6e\x75\x2e\x74\x63\x6c\x00\x09\x61\x6e\x6f\x6e\x79\x6d\x6f\x75\x73\x00\x04\x31\x2e\x32\x35\x00\x0e\x63\x6f\x6c\x6f\x72\x73\x4d\x65\x6e\x75\x2e\x74\x63\x6c\x00\x00\x00\x00\x00\x00"
	resource write -id 128 -name "CVS info" -file $tmp::rid ckid $hexdata
	# Abou
	resource write -id 128 -name "About [file tail $tmp::resfile]" -file $tmp::rid Abou "This is a $tmp::whichfork resource file for the Rezilla AppleScript test suite. Date $tmp::date"

	# Modify the attributes of the MPSR and ckid resource in the RF file
	# 4 is "preload" and 8 is "protected"
	if {$tmp::suffix eq "RF"} {
		resource attributes $tmp::rid -id 1005 MPSR 4
		resource attributes $tmp::rid -id 128 ckid 8
	} 
	
	resource close $tmp::rid	
} 

# Build a file with no forks
set tmp::resfile [file join $tmp::testdir TestRezillaNF.rsrc]
if {[file exists $tmp::resfile]} {
	file delete $tmp::resfile
} 
close [open $tmp::resfile w+]

namespace delete ::tmp

# unset -nocomplain tmp::date tmp::testdir tmp::suffix tmp::resfile tmp::rid tmp::whichfork