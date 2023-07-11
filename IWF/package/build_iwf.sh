#!/bin/bash

. exports_iwf.sh

#echo $ITS_ROOT
#echo $IMS_ROOT
#echo $EACC_ROOT
#echo $IWF_ROOT
#echo $VENDOR_ROOT
export HOME=/home/tomcat
#
#export CVSROOT=:pserver:jenkins:jenkins123@172.16.23.16:/export/home/.indiacvsroot
#export TAG_TO_CHECKOUT_1=B-IWF-0100-04
##export TAG_TO_CHECKOUT_2=B-DRE-IWF-DIA-STACK-0100
#
#if [ "$checkout_from_CVS" == "yes" ]; then
##cvs login -p jenkins123
#cvs co -r $TAG_TO_CHECKOUT_1 imsdia
#cvs co -r $TAG_TO_CHECKOUT_1 eAccelero
#cvs co -r $TAG_TO_CHECKOUT_1 vendors
#cvs co -r $TAG_TO_CHECKOUT_1 IWF
#cvs co -r $TAG_TO_CHECKOUT_1 IntelliSS7
#fi

echo "Building IntelliSS7"
cd IntelliSS7
#make > err 2>&1
make
cd -

echo "Building vendors"
cd vendors
echo "  with ANSI SCCP"
#make SCCP_PROT=ANSI > err 2>&1
make SCCP_PROT=ANSI
cd IntelliNet/src
rm -f *.o
echo "  with CCITT SCCP"
#make SCCP_PROT=CCITT > err 2>&1
make SCCP_PROT=CCITT
cd ../../..

echo "Building CAPV1"
cd IntelliSS7/CAMEL/src
#make TARGET=CAP-V1 > err 2>&1
make TARGET=CAP-V1
cd -

echo "Building CAPV2"
cd IntelliSS7/CAMEL/src
#make TARGET=CAP-V2 > err 2>&1
make TARGET=CAP-V2
cd -

echo "Building CAPV3"
cd IntelliSS7/CAMEL/src
#make TARGET=CAP-V3 > err 2>&1
make TARGET=CAP-V3
cd -

echo "Building INAP"
cd IntelliSS7/INAP/src
#make TARGET=INAP-CS2 > err 2>&1
make TARGET=INAP-CS2
cd -

echo "Building MAPV13"
cd IntelliSS7/GSMMAP/src
#make TARGET=MAP-V13 > err 2>&1
make TARGET=MAP-V13
cd -

echo "Building MAPV9"
cd IntelliSS7/GSMMAP/src
#make TARGET=MAP-V9 > err 2>&1
make TARGET=MAP-V9
cd -

echo "Building MAP3"
cd IntelliSS7/GSMMAP/src
#make TARGET=MAP-V3 > err 2>&1
make TARGET=MAP-V3
cd -

echo "Building eAccelero"
cd eAccelero
#make > err 2>&1
make
cd -

echo "Building imsdia"
cd imsdia
#make > err 2>&1
make
cd -

echo "Building IWF"
cd IWF/common/src
make SCCP_PROT=CCITT clean all;
make SCCP_PROT=ANSI clean all;
cd ../../
make SCCP_PROT=CCITT
make SCCP_PROT=ANSI
cd -

cd $IWF_ROOT/package
./package.sh rpm --defaults
expect -f copy_iwf_64bin.tcl
