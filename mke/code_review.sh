#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage:  $0  <filename>"
	exit 1
fi

test -e $1
if [ $? -eq 1 ]; then
	echo "file $1 not exist."
	exit 2
fi

which splint 
ret=$?
if [ $ret -ne 0 ]; then
	echo "splint not found."
	exit 3;
fi

#splint $1 -warnposix -paramuse -nullret -exportlocal -compdestroy \
#		  -mustfreeonly -retvalint -fullinitblock -mustfreefresh \
#		  -boolops -predboolint -nullpass -infloops

splint $1 -warnposix -predboolint -nullpass -nullret
