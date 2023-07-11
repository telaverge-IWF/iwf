#!/bin/ksh
########################################################################
#
# Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.
#          Manufactured in the United States of America.
#   1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.
#
########################################################################
#                   #
# CONTRACT: INTERNAL#
#                   #
############################################################################
#
# ID: $Id: MFGenerator.sh,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
#
# LOG: $Log: MFGenerator.sh,v $
# LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.3  2008/03/27 12:09:57  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:43  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.1  2006/07/31 05:02:20  nvijikumar
# LOG: Manifest file for java package.
# LOG:
# LOG:
#
#ident "$Id: MFGenerator.sh,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $"
#
############################################################################


echo "Generating the META-INF/MANIFEST.MF...."

export JAVOCLASSPATH=$IMS_ROOT/api/jar/javolution.jar
export JAPPCLASSPATH=$IMS_ROOT/api/jar/JSampleApp.jar
export JIDCCLASSPATH=$IMS_ROOT/api/jar/JIDC.jar
export JAPICLASSPATH=$IMS_ROOT/api/jar/diaapi.jar
export JVALCLASSPATH=$IMS_ROOT/api/jar/diameter.jar

mkdir -p $IMS_ROOT/demo/META-INF

echo "Main-Class: demo.AppMain" > $IMS_ROOT/demo/META-INF/MANIFEST.MF
echo "Class-Path:" $JAVOCLASSPATH $JIDCCLASSPATH $JAPPCLASSPATH $JAPICLASSPATH $JVALCLASSPATH >> $IMS_ROOT/demo/META-INF/MANIFEST.MF
echo "Name: ." >> $IMS_ROOT/demo/META-INF/MANIFEST.MF
echo >> $IMS_ROOT/demo/META-INF/MANIFEST.MF
