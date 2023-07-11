#!/bin/sh
########################################################################
#
# Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.
#          Manufactured in the United States of America.
#   1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.
#
########################################################################
#
# ID: $Id: removelog.sh,v 3.2 2010/10/07 09:48:49 nvijikumar Exp $
#
# LOG: $Log: removelog.sh,v $
# LOG: Revision 3.2  2010/10/07 09:48:49  nvijikumar
# LOG: Scripts to build SOURCE PKG
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:15  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.5  2008/03/27 11:47:56  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.2.8.1  2007/03/13 05:05:13  rrath
# LOG: Changes for clean-upremovelog.sh
# LOG:
# LOG: Revision 2.2  2006/12/05 08:39:33  chandral
# LOG: Baseline build scripts for ITS Diameter.
# LOG:
# LOG: Revision 1.4  2006/08/01 11:49:48  rrath
# LOG: Modify for new Interface
# LOG:
# LOG: Revision 1.3  2006/07/31 04:45:32  nvijikumar
# LOG: Changes to remove comments from Java files.
# LOG:
# LOG: Revision 1.2  2006/05/16 10:25:15  nvijikumar
# LOG: changes to support for both OS.
# LOG:
# LOG: Revision 1.1  2006/05/11 13:24:38  rrath
# LOG: Added file to remove log information from source files.
# LOG:
########################################################################

pattern="LOG:"
libpattern="LD_LIBRARY"
hfile=`find . -name *.h`
cfile=`find . -name *.cpp`
jfile=`find . -name *.java`
mfile=`find . -name Makefile`
rfile=`find . -name Run.*`

echo "Executing....please wait"
echo ""

for fname in $hfile
do
   cp $fname $fname.bak
   cat $fname | grep -v $pattern >> $fname.new
   mv $fname.new $fname
   rm $fname.bak
done

for fname in $cfile
do
   cp $fname $fname.bak
   cat $fname | grep -v $pattern >> $fname.new
   mv $fname.new $fname
   rm $fname.bak
done

for fname in $jfile
do
   cp $fname $fname.bak
   cat $fname | grep -v $pattern >> $fname.new
   mv $fname.new $fname
   rm $fname.bak
done

for fname in $mfile
do
   cp $fname $fname.bak
   cat $fname | grep -v $pattern >> $fname.new
   mv $fname.new $fname
   rm $fname.bak
done
if [ $interface ]
then
   x=1
else
{
   for fname in $rfile
   do
   cp $fname $fname.bak
   cat $fname | grep -v $libpattern >> $fname.new
   mv $fname.new $fname
   chmod 775 $fname
   rm $fname.bak
done
}
fi
echo "DONE"
echo ""

