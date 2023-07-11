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
# LOG: $Log: Makefile,v $
# LOG: Revision 3.3.28.2  2012/12/21 05:55:12  ncshivakumar
# LOG: Modified for Tracing
# LOG:
# LOG: Revision 3.3.28.1  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.3.30.2  2012/08/28 04:50:11  cprem
# LOG: Added jsoncpp lib path.
# LOG:
# LOG: Revision 3.3.30.1  2012/08/22 12:53:43  jvikas
# LOG: Fixed Linking Errors and Included XML Config for Transformation.
# LOG:
# LOG: Revision 3.3  2008/08/12 04:24:28  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.2  2008/06/13 11:15:16  hbhatnagar
# LOG: Added TLS wrapper include path for compilation
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.9  2006/12/05 13:34:07  hbhatnagar
# LOG: made changes for the different name of library for BCGI
# LOG:
# LOG: Revision 2.8  2006/11/24 16:36:30  hbhatnagar
# LOG: Made changes for SessionId as Key and corresponding changes
# LOG:
# LOG: Revision 2.7  2006/11/13 06:33:47  hbhatnagar
# LOG: made changes for the new files to compile and removed the dcca_mml from the list
# LOG:
# LOG: Revision 2.6  2006/11/06 09:30:47  hbhatnagar
# LOG: made changes for the separation of BCGI and RFRO related functionality with core.
# LOG:
# LOG: Revision 2.5  2006/11/03 14:06:46  nvijikumar
# LOG: Remove dcca_message_handler.o while make clean. ( Hemanth).
# LOG:
# LOG: Revision 2.4  2006/10/31 08:28:50  hbhatnagar
# LOG: Made changes for Different Libs.
# LOG:
# LOG: Revision 2.3  2006/10/30 15:35:58  hbhatnagar
# LOG: Changes for DCCA to work with ITSDEMO
# LOG:
# LOG: Revision 2.2  2006/10/26 14:42:09  hbhatnagar
# LOG: set the Compilation variable for BCGI (Hemant)
# LOG:
# LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
# LOG: Integration with ITS-Diameter
# LOG:
# LOG: Revision 1.1.2.4  2006/09/27 09:26:30  hbhatnagar
# LOG: Added support for bcgi namespace (badri)
# LOG:
# LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
# LOG: Converted file from DOS 2 UNIX (badri)
# LOG:
# LOG: Revision 1.1.2.2  2006/09/25 08:40:04  nvijikumar
# LOG: Added dcca_conf.cpp for compilation (badri)
# LOG:
# LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
# LOG: DCCA First Cut (badri)
# LOG:
#
# ID: $Id: Makefile,v 3.3.28.2 2012/12/21 05:55:12 ncshivakumar Exp $
#
############################################################################/



#
# include
#
include $(IMS_ROOT)/make.dirs



#
# define
#

# To use the compilation for BCGI use: make TARGET=BCGI BCGI instead of make


ifeq ($(TARGET), BCGI)
DCCA_FLAGS= -D_BCGI
endif


DEFINES :=	$(ITS_DEFINES) $(DEFINES) $(DCCA_FLAGS) -D_LINUX 
LIBRARY :=	../lib/libdccacore$(DBGSUFFIX).so

# TODO use the INCLS from the make.dir, this is overriding it
INCLS   :=	-I../include \
		-I$(IMS_ROOT)/common/include \
		-I$(ITS_ROOT)/common/include \
		-I$(ITS_ROOT)/ENGINE/include \
		-I$(ITS_ROOT)/tls/include \
		-I$(IMS_ROOT)/val/c++/include \
		-I$(IMS_ROOT)/api/c++/include \
		-I$(IMS_ROOT)/api/c++/include/diameter/dcca \
		-I$(IMS_ROOT)/vendors/IntelliNet/include \
		-I$(IMS_ROOT)/dtf/include \
		-I$(EACC_ROOT)/blocks/include \
		-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2 \
		-I$(EACC_ROOT)/utils/rule/include


SO_OBJS=dcca_feature.o \
		dcca_common.o \
		dcca_module.o \
		dcca_context.o \
		dcca_trace.o \
		dcca_fsm.o \
		dcca_stats.o \
		dcca_api.o \
		dcca_conf.o \
		dcca_message_handler.o \
                common_cc_decode.o 


#
# target
#

# Always use make clean before make
all :   $(SO_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $(LIBRARY) $(SO_OBJS) $(NOWHOLEARCHIVE)

# use make TARGET=BCGI BCGI to build target
BCGI :../lib/libbcgidccacore$(DBGSUFFIX).so

../lib/libbcgidccacore$(DBGSUFFIX).so :$(SO_OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) $@ $(SO_OBJS) $(NOWHOLEARCHIVE)



clean:
	rm -f $(LIBRARY) $(SO_OBJS) \
	rm -f ../lib/libbcgidccacore$(DBGSUFFIX).so
