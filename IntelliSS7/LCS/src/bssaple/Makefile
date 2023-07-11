#################################-*-make-*-###################################
#                                                                            #
#      Copyright 2009 IntelliNet Technologies, Inc. All Rights Reserved.     #
#              Manufactured in the United States of America.                 #
#        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        #
#                                                                            #
#    This product and related documentation is protected by copyright and    #
#    distributed under licenses restricting its use, copying, distribution   #
#    and decompilation.  No part of this product or related documentation    #
#    may be reproduced in any form by any means without prior written        #
#    authorization of IntelliNet Technologies and its licensors, if any.     #
#                                                                            #
#    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       #
#    government is subject to restrictions as set forth in subparagraph      #
#    (c)(1)(ii) of the Rights in Technical Data and Computer Software        #
#    clause at DFARS 252.227-7013 and FAR 52.227-19.                         #
#                                                                            #
##############################################################################
#                                                                            #
#  CONTRACT: INTELLINET                                                      #
#                                                                            #
##############################################################################
# 
#  ID: $Id: Makefile,v 1.1.2.4 2010/04/29 13:02:11 pvenkatarao Exp $
# 
#  LOG: $Log: Makefile,v $
#  LOG: Revision 1.1.2.4  2010/04/29 13:02:11  pvenkatarao
#  LOG: Added code to make LCS Codec traces on/off based on env LCS_CODEC_TRACE=ON/OFF
#  LOG:
#  LOG: Revision 1.1.2.3  2010/03/23 05:41:53  rajeshak
#  LOG: Release-8 Codec changes.
#  LOG:
#  LOG: Revision 1.1.2.2  2010/03/19 11:41:02  rajeshak
#  LOG: Removing IntelliSS7 dependency from Codec
#  LOG:
#  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
#  LOG: Adding Codec files to LCS folder
#  LOG:
#  LOG:
# 
##############################################################################

PLATFORM=solaris
include $(ITS_ROOT)/config.vars
CXXSHAREDAR=$(CXX)
O=.o

ifeq ($(LCS_CODEC_TRACE),ON)
    DEFINES:= $(DEFINES) -DCODEC_TRACE_ON
endif


OBJS =  ie/infoelement$(O) \
        ie/apdu$(O) \
        ie/cause$(O)  \
        ie/lcscause$(O) \
        ie/imsi$(O) \
        ie/isdnaddress$(O) \
        ie/lcsclienttype$(O) \
        ie/lcspriority$(O) \
        ie/lcsqos$(O) \
        ie/gansspositioningdata$(O) \
        ie/ganssassistancedata$(O) \
        ie/gansslocationtype$(O) \
        ie/velocitydata$(O) \
        ie/lcscapability$(O) \
        ie/imei$(O) \
        ie/cellidentitylist$(O) \
        ie/packetmeasurementreport$(O) \
        ie/locationtype$(O) \
        ie/positioningdata$(O) \
        ie/returnerrorcause$(O) \
        ie/returnerrorrequest$(O) \
        ie/security$(O) \
        ie/chosenchannel$(O) \
        ie/cellidentifier$(O) \
        ie/geographiclocation$(O) \
        ie/segmentation$(O) \
        ie/decipheringkeys$(O) \
        ie/gpsassistancedata$(O) \
        ie/networkelementidentity$(O)\
        ie/signalingpointcode$(O) \
        ie/lmucause$(O) \
        ie/facility$(O) \
        ie/releaseforbidden$(O) \
        ie/releasecompletecause$(O) \
        message$(O) \
        resetacknowledge$(O) \
        reset$(O) \
        performlocationabort$(O) \
        connectionorientedinformation$(O) \
        connectionlessinformation$(O) \
        performlocationresponse$(O) \
        performlocationrequest$(O) \
        performlocationinformation$(O) \
        lmuconnectionaccept$(O) \
        lmuconnectionreject$(O) \
        lmuconnectionrelease$(O) \
        lmuconnectionrequest$(O) \
        dtapmessage$(O) \
        facility$(O) \
        register$(O) \
        releasecomplete$(O)


CFLAGS := $(CFLAGS) \
          -I$(ITS_ROOT)/LCS/include

CXXFLAGS := $(CXXFLAGS) \
          -I$(ITS_ROOT)/LCS/include

#
# release build with debug information
#
ifneq ($(DEBUG_BUILD),yes)
    ifeq ($(RELEASE_G),yes)
        CXXFLAGS := -g $(CXXFLAGS)
    endif
endif

all: ../../lib/libbssaple$(DBGSUFFIX).so ../../lib/libbssaple$(DBGSUFFIX).a

clean:
	$(RM) $(OBJS)
	$(RM) -r core SunWS_cache ir.out ie/SunWS_cache ie/ir.out
	$(RM) -r ../../lib/libbssaple$(DBGSUFFIX).* ../../lib/SunWS_cache

../../lib/libbssaple$(DBGSUFFIX).a: $(OBJS)
	$(CXXAR) $(CXXARFLAGS) ../../lib/libbssaple$(DBGSUFFIX).a $(OBJS)

../../lib/libbssaple$(DBGSUFFIX).so: $(OBJS)
	$(CXXSHAREDAR) $(CXXSHAREDARFLAGS) ../../lib/libbssaple$(DBGSUFFIX).so -h libbssaple$(DBGSUFFIX).so $(OBJS)


#
# the rules
#
include $(ITS_ROOT)/config.rules
