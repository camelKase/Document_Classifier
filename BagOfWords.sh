#!/bin/sh
#shell script that checks the word frequecy of each file in a directory

for file in "$@"
do		
	sed 's/[,\.]*//g' $file | tr -s ' ' '\n' | sort | uniq -ic | sort -nr
	echo "NEW ARTICLE"
	echo "BELOW"
	echo "***********************"
done
