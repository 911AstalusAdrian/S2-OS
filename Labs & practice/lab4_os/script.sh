#!/bin/sh
#checks command line for directories and lists the contents
for a in $@
do
	if test -d "$a"; then
	   ls -1 "$a" | grep "^[0-9]"	
	fi
done
