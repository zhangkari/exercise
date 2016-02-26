#! /bin/bash

#
# define function for get argument list for app
#
function getArguments()
{
	echo "shitf before" $@ ;
	shift 2 ;
	echo "shift after" $@ ;
	return $@
}


argc=$# ;
arg1=$1 ;
arg2=$2 ;
#getArguments $@;

if [ $? -ne 0 ]; then
	echo "Failed get arguments"
	exit 0
fi

# make once anyway
make

if [ 0 -ne $? ] ; then
	echo "Errors in make, Interrupted"
	exit 1
fi

# excute erlang app
ERL=erl 


cd target

# argument count
if [ $argc -lt 1 ]; then 
	${ERL} -noshell -s dk_server start -s init stop
elif [ $argc -lt 2 ]; then
	echo "Invalid argument"
	exit 1;
elif [ $argc -ge 2 ]; then
	shift 2
	args=$@
	echo "run" $arg1 $arg2 $args; 
	${ERL} -noshell -s $arg1 $arg2 $args -s init stop
fi

