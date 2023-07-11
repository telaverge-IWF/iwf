#!/bin/bash

#script to generate enums 
OUTPUT_FILE="cmn_mgmt.h"

FLAG=0
processLine(){
  line="$@" # get all args
	if [ `echo "$line" | grep -c "Add_CLI"` -eq 1 ]; then
		
		read -r line
			if [ `echo "$line" | grep -c "_cmd"` -eq 1 ]; then
				if [ $FLAG -eq 0 ];then
				echo $line | tr -d ',\b\r\n'  >> $OUTPUT_FILE 
				echo "= 1," >> $OUTPUT_FILE
				FLAG=1
				else
				echo $line | tr -d '\b\r'  >> $OUTPUT_FILE 
				fi
			
				#temp="$temp1=1,"
				#echo $temp | tr -d '\b\r' >> $OUTPUT_FILE
			fi
		#echo $line >> $OUTPUT_FILE
	fi
  #echo $line
}
 
# Store file name
#INPUT_FILE=""
 
   INPUT_FILE="$1"
   if [ ! -f $INPUT_FILE ]; then
  	echo "$INPUT_FILE : does not exists"
	exit 1
   fi
 
# Set loop separator to end of line
BAKIFS=$IFS
IFS=$(echo -en "\n\b")
exec 3<&0
exec 0<"$INPUT_FILE"
echo "enum COMMAND_IDS {" > $OUTPUT_FILE
while read -r line
do
	# use $line variable to process line in processLine() function
	processLine $line
done
echo "		dummy" >> $OUTPUT_FILE
echo "};" >> $OUTPUT_FILE
 
# restore $IFS which was used to determine what the field separators are
IFS=$BAKIFS
exit 0
