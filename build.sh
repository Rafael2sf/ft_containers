
if [ $# == 1 ]
then
	if [ -f "$1" ]
	then
		STD_FILE=$(echo "$1" | sed 's/ft/std/g')
		touch "$STD_FILE"; cat "$1" | sed 's/ft::/std::/g' >> "$STD_FILE"
		#COMPILE="c++ -Wall -Werror -Wextra -std=c++98 $STD_FILE -o "$(echo $STD_FILE | cut -f 1 -d '.')".cpp"
		echo $STD_FILE
		echo "$(echo $STD_FILE | cut -f 1 -d '.')"
	else
		printf "$1: either no such file or file is not regular\n"
	fi
else
	printf "Usage: ./prog <infile-path>\n"
fi

# compile ft from makefile, call sh -- create std copy, compile it, run diff