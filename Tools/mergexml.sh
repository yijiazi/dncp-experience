#!/bin/bash
SRCFILE=$1
DSTFILE=$2
INCLUDEPATTERN2="rfc include="

if [[ $DSTFILE == "" ]]; then
	echo "Error: No SOURCE or DESTINATION filename given";
	echo "Usage: $0 <sourcefile> <destinationfile>";
	exit 1;
fi
if [[ $SRCFILE == "" ]]; then
	echo "Error: No SOURCE or DESTINATION filename given";
	echo "Usage: $0 <sourcefile> <destinationfile>";
	exit 1;
fi
cat /dev/null > $DSTFILE
cat $SRCFILE | while read line; do
	if [[ "$line" =~ $INCLUDEPATTERN2 ]]; then
		toinclude=${line#*=\'};
		toinclude=${toinclude%\'*};
		toinclude=$toinclude".xml";
		#echo "Include: $toinclude";
		cat $toinclude >> $DSTFILE;
	else
		echo $line >> $DSTFILE;
	fi;
done;

exit 0;
