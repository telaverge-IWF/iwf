#!/bin/bash

source /opt/diametriq/dre/scripts/package_functions.sh

SOURCE=/var/log/tmp/
DEST=/var/log/archive/
CNF=/opt/diametriq/dre/config/dre_trace_logrotate
mkdir -p $DEST

DIRPATH=$(cat $CNF | grep 'trace' | tr -d '{' | tr -d '*'| tr -d ' ')
DIRNAME=$(cat $CNF | grep 'olddir' | tr -s ' ' | cut -d ' ' -f 3)
LOG_ROTATE_NUM=`cat $CNF | grep rotate | grep -v postrotate| tr -s " " | cut -d " " -f 3`
LIST=$(ls $DIRPATH$DIRNAME/ | grep `echo $LOG_ROTATE_NUM`)
N=$(ls $DIRPATH$DIRNAME/ | grep `echo $LOG_ROTATE_NUM` | wc -l)

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

    TARGET=$TARGET/trace
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
        TARGET=$TARGET/$PART_1\_$STAMP"."$PART_2
        /bin/cp -f $FILE $TARGET
    else
        /bin/cp -f $FILE $TARGET
    fi
}
#Create tmp directory for copying the files
mkdir -p `echo $SOURCE`

#If the number of files are 0 exit
if [ $N -eq 0 ]
then
    exit 0
fi

#Copy the files
for((i=0;i<$N;i++))
do
    /bin/cp -f $DIRPATH$DIRNAME/$(echo $LIST | tr ' ' '\n' | tail -`expr $N - $i` | head -1) $SOURCE 
done

for i in `echo $SOURCE`*
do

    FIELD=`echo $i`
        FILE=$i
        makedirstruct $DIRARG
        copy $CPARG
        DELETE=$(echo $FILE | cut -d '/' -f 5 )
        FILENAME=$(echo $LIST | tr " " "\n" | grep `echo $DELETE |  cut -d "." -f 1,2`)
        /bin/rm -f  $DIRPATH$DIRNAME/$DELETE
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
