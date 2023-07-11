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
# ID: $Id: Makefile,v 1.2 2008/12/19 05:55:37 chandrabs Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.2  2008/12/19 05:55:37  chandrabs
# LOG: Added NOWHOLEARCHIVE flag to resolve run time error-undefined symbol:__init_array_start
# LOG:
# LOG: Revision 1.1  2008/12/05 12:08:41  nvijikumar
# LOG: Initial draft for Alarm support
# LOG:
# LOG:
############################################################################
#
# Include the standard definitions
#
include $(IMS_ROOT)/make.dirs

DEFINES:=$(DEFINES)

INCLS:=$(INCLS) -I../include \
        -I$(IMS_ROOT)/common/include \
        -I$(ITS_ROOT)/common/include

COBJS:= dia_oam_server.o

all: ../lib/libDiaOAMServer$(DBGSUFFIX).so 

clean:
	rm $(COBJS) \
           ../lib/libDiaOAMServer$(DBGSUFFIX).so 

../lib/libDiaOAMServer$(DBGSUFFIX).so: $(COBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) \
        ../lib/libDiaOAMServer$(DBGSUFFIX).so \
        $(COBJS) ${NOWHOLEARCHIVE}

