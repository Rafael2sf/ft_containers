#!/bin/bash
set -m

# ./run_test.sh vector
#
# -d (output the diferrence of output)
# -h (hide output)
# -t (show runtime)

#options
__D=0
__H=0
__T=0

#initialize
FT_OUT=""
STD_OUT=""
DIFF_OUT=""

function time_program ()
{
	if [ $# -eq 2 ]
	then
		if [ $__H -eq 0 ]; then
			printf "executing\t$1\n"
		fi
		TIME_START=`date +%s.%N`
		if [ ! -z "$2" ]; then
			$1 > $2
		elif [ $__H -eq 0 ]; then
			$1
		else
			$1 > /dev/null
		fi
		TIME_END=`date +%s.%N`
		RUNTIME=$(echo "$TIME_END - $TIME_START" | bc -l)
	fi
}

function show_usage()
{
	printf "Usage: ./run_test.sh [ -t # showtime ] [ -h # hide output ] [ -d diff output ] <file_basename>\n"
	exit 1
}

function is_executable()
{
	if [ ! -f $1 ] || [ ! -x $1 ]
	then
		printf "error: $1: no such executable file\n"
		exit 1
	fi
}

if [ $# -eq 0 ]
then
	show_usage
fi

while getopts "htd" options; do
	case "${options}" in
		h)
			__H=1
			;;
		t)
			__T=1
			;;
		d)
			__D=1
			;;
		:)
			printf "error: -${OPTARG} requires an argument.\n"
			exit 1
			;;
		*)
			printf "error: -${OPTARG} unknown option.\n"
			exit 1
			;;
	esac
done
shift $((OPTIND-1))

FT=./bin/ft_$1
STD=./bin/std_$1
make $FT
make $STD
is_executable $FT
is_executable $STD

if [ $__D -eq 1 ]
then
	STD_OUT=$(mktemp output.std.$1.XXXX)
	printf "$STD > $STD_OUT\n"
	FT_OUT=$(mktemp output.ft.$1.XXXX)
	printf "$FT > $FT_OUT\n"
	DIFF_OUT=$(mktemp diff.$1.XXXX)
fi

time_program "$FT" "$FT_OUT"
FT_RUNTIME="$RUNTIME"
time_program "$STD" "$STD_OUT"
STD_RUNTIME="$RUNTIME"

if [ $__D -eq 1 ]
then
	diff $FT_OUT $STD_OUT > $DIFF_OUT
	printf "diff $FT_OUT $STD_OUT > $DIFF_OUT\n"
fi

if [ $__T -eq 1 ]
then
	printf "$FT:\t${FT_RUNTIME}s\n"
	printf "$STD:\t${STD_RUNTIME}s\n"
fi
