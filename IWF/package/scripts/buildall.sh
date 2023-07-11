#!/bin/bash

cp exports.sh ../../
cd ../..

source ./exports.sh

DIRS="IntelliSS7 vendors imsdia SSG"
RET=0

echo "Building IntelliSS7"
cd IntelliSS7
make > err 2>&1
cd -

echo "Building vendors"
cd vendors
echo "  with ANSI SCCP"
make SCCP_PROT=ANSI > err 2>&1
cd IntelliNet/src
rm -f *.o 
echo "  with CCITT SCCP"
make SCCP_PROT=CCITT > err 2>&1
cd ../../..

#echo "Building CAP"
#cd IntelliSS7/CAMEL/src
#make TARGET=CAP-V3 > err 2>&1
#cd -

#echo "Building INAP"
#cd IntelliSS7/INAP/src
#make TARGET=INAP-CS2 > err 2>&1
#cd -

echo "Building MAP"
cd IntelliSS7/GSMMAP/src
make TARGET=MAP-V13 > err 2>&1
cd -

echo "Building imsdia"
cd imsdia
make > err 2>&1
cd -

echo "Building IWF"
cd IWF
make SCCP_PROT=CCITT clean; make SCCP_PROT=CCITT > err 2>&1
cd -

