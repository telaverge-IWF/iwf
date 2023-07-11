#!/bin/bash

. ./etc/profile.d/iwf.sh
source $ROOT/scripts/package_functions.sh 


SOURCE=/var/log/tmp/
DEST=/var/log/archive/
CNF=/opt/diametriq/${S_PRODUCT_NAME}/config/${S_PRODUCT_NAME}_logrotate
mkdir -p $DEST

LIST=$(cat $CNF | grep '\.log' | tr -d '{')
N=$(cat $CNF | grep '\.log' | tr -d '{' | wc -l)
LOG_ROTATE_NUM=`cat $CNF | grep rotate | grep -v postrotate| tr -s " " | cut -d " " -f 3`

#Argument for the functions
DIRARG=NOHOUR
CPARG=TIMESTAMP

makedirstruct()
{

    DIR1=`echo $DEST``date | tr -s ':' ' ' | cut -d ' ' -f 8`
    DIR2=`echo $DIR1`/`date | tr -s ':' ' ' | cut -d ' ' -f 2`
    DIR3=`echo $DIR2`/`date | tr -s ':' ' ' | cut -d ' ' -f 3`
    if [ "$1" = "HOUR" ]
    then
        TARGET=`echo $DIR3`/`date | tr -s ':' ' ' | cut -d ' ' -f 4`
    else
        TARGET=$DIR3
    fi

    TARGET=$TARGET/${S_PRODUCT_NAME}
    mkdir -p $TARGET
}

copy()
{
    if [ $1 = "TIMESTAMP" ]
    then
        STAMP=`date  | tr ':' '_' | tr -s ' ' | cut -d ' ' -f 4`
        TMP=$(echo $FILE | cut -d '/' -f 5 )
        NO_OF_DOT=`echo $FILE| tr "." " "| wc -w`
        NO_OF_DOT_MINUS_ONE=`expr $NO_OF_DOT - 1`
        PART_1=`echo $TMP | cut -d "." -f 1-$NO_OF_DOT_MINUS_ONE`
        PART_2=`echo $TMP | cut -d "." -f $NO_OF_DOT`
        #TARGET=$TARGET/$STAMP\_$TMP
        TARGET=$TARGET/$PART_1\_$STAMP"."$PART_2
        /bin/cp -f $FILE $TARGET
    else
        /bin/cp -f $FILE $TARGET
    fi
}

#Create tmp directory for copying the files
mkdir -p `echo $SOURCE`

#Copy the files
for((i=0;i<$N;i++))
do
    /bin/cp -f $(echo $LIST | tr ' ' '\n' | tail -`expr $N - $i` | head -1)* `echo $SOURCE` 2> /dev/null
done

for i in `echo $SOURCE`*
do

    FIELD=`echo $i | cut -d '.' -f 3`
    if [ "$FIELD" = "$LOG_ROTATE_NUM" ]
    then
        FILE=$i
        makedirstruct $DIRARG
        copy $CPARG
        DELETE=$(echo $FILE | cut -d '/' -f 5 )
        FILENAME=$(echo $LIST | tr " " "\n" | grep `echo $DELETE |  cut -d "." -f 1,2`)
        ACTUAL_DIR=`dirname $FILENAME`
        /bin/rm -f  $ACTUAL_DIR/$DELETE
    fi
done

#Cleaning up the tmp directory
rm -rf $SOURCE

#deleting the older files and folders
DAYS=30
DIR=$DEST
# Delete directories older than DAYS 
find $DIR -type d -mtime +$DAYS -exec rm -rf {} \; > /dev/null 2>&1
# Delete files older than DAYS 
find $DIR -type f -mtime +$DAYS -exec rm {} \; > /dev/null 2>&1
