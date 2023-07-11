############################################################################
#                                                                          #
#     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                          #
############################################################################
#
# ID: $Id: Makefile,v 3.4.6.2.12.1.6.2 2014/10/27 09:59:09 jkchaitanya Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.4.6.2.12.1.6.2  2014/10/27 09:59:09  jkchaitanya
# LOG: added mag direcotry for compilation
# LOG:
# LOG: Revision 3.4.6.2.12.1.6.1  2014/10/27 08:28:37  pramana
# LOG: changes for HA HotStandBy
# LOG:
# LOG: Revision 3.4.6.2.12.1  2014/02/12 07:03:07  millayaraja
# LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
# LOG:
# LOG: Revision 3.4.6.2  2012/12/06 14:42:56  cprem
# LOG: Commented out compilation of itsdemo and other demo apps which are not required for DRE.
# LOG:
# LOG: Revision 3.4.6.1  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.4.8.2  2012/08/23 04:52:38  cprem
# LOG: Added dtf directory to be compiled with imsdia.
# LOG:
# LOG: Revision 3.4.8.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.4  2010/06/17 05:32:01  nvijikumar
# LOG: Included OAM lib generation
# LOG:
# LOG: Revision 3.3  2009/03/03 10:37:58  nvijikumar
# LOG: Added mgmt dirs for MML API Support
# LOG:
# LOG: Revision 3.2  2008/12/04 11:30:01  gdalawai
# LOG: Added api/c++/mtest to compile interfaces.  gdalawai
# LOG:
# LOG: Revision 3.1  2008/03/31 10:32:59  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.12  2008/03/27 12:05:43  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.6  2006/10/31 09:46:52  nvijikumar
# LOG: Changes to compile monitor/src for DiaMon.
# LOG:
# LOG: Revision 2.5  2006/10/30 15:33:30  hbhatnagar
# LOG: changes for dcca
# LOG:
# LOG: Revision 2.4  2006/10/27 14:02:56  hbhatnagar
# LOG: made changes to include the dcca module for compilation.(Hemant)
# LOG:
# LOG: Revision 2.3  2006/10/17 06:38:41  tpanda
# LOG: Merging with ITS Diameter.
# LOG:
# LOG: Revision 2.2  2006/09/26 09:09:48  sumag
# LOG: Added components aim/jclient/src, aim/jclient/native and aim/jclient
# LOG:
# LOG: Revision 2.1  2006/09/13 09:13:24  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.8  2006/06/21 10:37:29  nvijikumar
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.7  2006/06/13 16:27:57  brianhu
# LOG: 0 as non-base application id; AVP vendor id overriding protocol-level vendor id.
# LOG: Toplevel Makefile forgives subdirectories without "realclean" targets.
# LOG:
# LOG: Revision 1.6  2006/06/06 01:21:01  brianhu
# LOG: Adding Java implementation into main Makefile
# LOG:
# LOG: Revision 1.5  2006/04/24 10:33:15  nvijikumar
# LOG: Included aim/client/demo for compilation in the root Makefile
# LOG:
# LOG: Revision 1.4  2006/03/20 06:30:13  yranade
# LOG: Added mag in COMPONENTS.
# LOG:
# LOG: Revision 1.3  2006/03/15 10:16:06  yranade
# LOG: 1. Split OD Specifics and move them to vendors
# LOG: 2. Support Diameter Client Capability
# LOG: 3. Code Reorganization.
# LOG: 4. Added Demo and Aim dirs.
# LOG:
# LOG: Revision 1.2  2006/03/02 13:29:22  tpanda
# LOG: Added to build common dframe sources
# LOG:
# LOG: Revision 1.1.1.1  2006/02/16 12:16:38  yranade
# LOG: Create baseline imsdia project in CVS.
# LOG:
#
############################################################################

# components under this project
#
ifeq ($(COMPILE),javac++)
COMPONENTS=mag/src mag val/c++ val/java/src api/c++ api/java/src common/src \
           vendors/opendiameter dframe/src val/java/native demo/src         \
           aim/server/src monitor/src aim/client/src aim/client/demo        \
           aim/jclient/src aim/jclient/native aim/jclient

else
ifeq ($(PRODUCT),iwf)
COMPONENTS= mag/src mag val/c++ common/src vendors/IntelliNet/src dframe/src \
		    api/c++ vendors/IntelliNet/dcca  vendors/IntelliNet/oam/server/src \
		    mgmt/dms/src mgmt/dmc/src dtf/src api/c++/mtest
else
COMPONENTS= mag/src mag val/c++ api/c++ common/src vendors/IntelliNet/src \
            vendors/IntelliNet/dcca  vendors/IntelliNet/oam/server/src \
	        dframe/src mgmt/dms/src mgmt/dmc/src dtf/src \
            aim/server/src monitor/src aim/client/src         \
            api/c++/mtest
endif
endif

.PHONY: all clean realclean test

all clean realclean test:
	@for p in $(COMPONENTS); do \
	    if [ -d $$p ]; then \
            $(MAKE) -C $$p $@ || if [ $@ = realclean ]; then $(MAKE) -C $$p clean; else exit 1; fi || exit 1; \
	    else \
	        echo make[$(MAKELEVEL)]: Ignoring \`$$p\': not a directory; \
	    fi; \
	done
