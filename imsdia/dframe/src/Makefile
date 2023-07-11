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
# ID: $Id: Makefile,v 3.2.28.5 2012/11/20 17:39:44 pramana Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.2.28.5  2012/11/20 17:39:44  pramana
# LOG: Merged from CMAPI branch for 212-07 release
# LOG:
# LOG: Revision 3.2.28.2.12.1  2012/11/20 10:24:28  rgovardhan
# LOG: merge from 00 Nov20Rel
# LOG:
# LOG: Revision 3.2.28.3  2012/11/06 16:31:20  pramana
# LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
# LOG:
# LOG: Revision 3.2.28.2.16.1  2012/11/05 03:42:39  vsarath
# LOG: Added for TLS enhancements
# LOG:
# LOG: Revision 3.2.28.2  2012/10/01 09:01:01  rsanjay
# LOG:  opendiameter code removal changes:bugzilla-id 300
# LOG:
# LOG: Revision 3.2.28.1  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.2.30.2  2012/08/28 03:58:21  cprem
# LOG: Added Json include directory.
# LOG:
# LOG: Revision 3.2.30.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.2  2008/08/12 04:24:49  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.3  2006/10/05 13:26:36  yranade
# LOG: Don't link in diaapi here.
# LOG:
# LOG: Revision 2.2  2006/10/05 12:11:07  yranade
# LOG: Updates for ITS-Diameter.
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:42  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.11  2006/07/02 06:58:34  yranade
# LOG: Don't link in its-dia just yet.
# LOG:
# LOG: Revision 1.10  2006/06/21 10:44:32  nvijikumar
# LOG: Modification for Copyright info.
# LOG:
# LOG: Revision 1.9  2006/06/21 09:22:45  yranade
# LOG: Split diavendor into 2 libraries. libitsdia.a contains all vendor
# LOG: abstraction code, and the new libdiavendor contains linking of only
# LOG: open source libraries.
# LOG:
# LOG: Revision 1.8  2006/04/27 16:07:14  yranade
# LOG: Update small typo
# LOG:
# LOG: Revision 1.7  2006/03/15 09:56:05  yranade
# LOG: 1. Split OD Specifics and move them to vendors
# LOG: 2. Support Diameter Client Capability
# LOG: 3. Code Reorganization
# LOG:
# LOG: Revision 1.6  2006/03/13 16:31:34  yranade
# LOG: Updates.
# LOG:
# LOG: Revision 1.5  2006/03/09 11:52:39  tpanda
# LOG: reference to dia_codec files were removed
# LOG:
# LOG: Revision 1.4  2006/03/09 11:47:32  tpanda
# LOG: Encode/Decode feature provided by wei's api replaced our encode/decode function.Hence dia_codec.* files are redundant
# LOG:
# LOG: Revision 1.3  2006/03/06 08:59:52  nvijikumar
# LOG: Create a static codec library.
# LOG:
# LOG: Revision 1.2  2006/03/03 13:06:46  tpanda
# LOG: Makefile is modified becuase of code reorganisation
# LOG:
# LOG: Revision 1.1  2006/03/02 13:08:15  tpanda
# LOG: Building IMS Diameter Infrastructure
# LOG:
#
############################################################################
#
include $(IMS_ROOT)/make.dirs

#
# Library base name
#
DEFINES:=$(DEFINES) -DVENDOR_ITS -DJSON_IS_AMALGAMATION
INCLS:=$(INCLS) -I../../vendors/IntelliNet/include \
                -I$(IMS_ROOT)/dtf/include \
                -I$(EACC_ROOT)/blocks/include \
                -I$(ITS_ROOT)/tls/include
LIBRARY=../lib/libITSDFrame

CXXFLAGS:=$(CXXFLAGS) $(ITS_DEFINES) \
          $(ITS_INCLS) -I../../common/include \
		  -I../include -I../../val/c++/include -I../../api/c++/include \
		  -I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2


LIBS=../../common/lib/libdiacommon$(DBGSUFFIX).a \
     ../../val/c++/lib/libdiaval$(DBGSUFFIX).a


OBJECTS := dia_frame.o dia_frame_stats.o 

#
# Targets
#
.PHONY: all clean

all: $(LIBRARY)$(DBGSUFFIX).so 

realclean clean:
	rm -f $(LIBRARY)$(DBGSUFFIX).so \
        $(OBJECTS)

$(LIBRARY)$(DBGSUFFIX).so: $(OBJECTS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $(LIBRARY)$(DBGSUFFIX).so $(OBJECTS) $(LIBS) $(NOWHOLEARCHIVE)
