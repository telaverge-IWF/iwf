#!/bin/bash

USAGE="Usage: `basename $0` --idir='<IDL-FILES-PATH> --odir='<OUTPUT-PATH>"
echo "Converting IDL files to c++ ..."
num=0
for i in $*
do
        case $i in
        --idir=*)
                INPUT_DIR=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
                echo $PREFIX
                num=$(($num + 1))
                ;;
        --odir=*)
                OUTPUT_DIR=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
                num=$(($num + 1))
                ;;
        --help)
                echo $USAGE

                ;;
        *)
                echo $USAGE
                # unknown option
                ;;
        esac
done
if [ $# -eq 0 ]; then
    echo $USAGE >&2
    exit 1
else
        if [ $num -ne 2 ];then
		echo $USAGE >&2
		exit 1
	else 
		ct_dir=$PWD
		cp $INPUT_DIR/*.idl .
		ls *.idl
		if [ $? -eq 0 ];then
        		echo "IDL files found ..."
			echo $ct_dir
			python dq_idl_parser.py *.idl
			sleep 2
			mv *.h $OUTPUT_DIR/include
			mv *.cpp $OUTPUT_DIR/src
#			rm *.idl                           
			echo "Convertion complete ..."
		else
        		echo "IDL files not found ... "
        		exit 1
		fi
	fi
fi
