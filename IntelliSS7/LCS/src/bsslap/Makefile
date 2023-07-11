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
#  LOG: Revision 1.1.2.3  2010/03/23 05:43:46  rajeshak
#  LOG: Release-8 Codec changes.
#  LOG:
#  LOG: Revision 1.1.2.2  2010/03/19 11:41:02  rajeshak
#  LOG: Removing IntelliSS7 dependency from Codec
#  LOG:
#  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
#  LOG: Adding Codec files to LCS folder
#  LOG:
#  LOG:
##############################################################################

##

#
# the standard variables
#
PLATFORM=solaris
include $(ITS_ROOT)/config.vars

#
# use $(CXX) to create shared object libraries
#
CXXSO=$(CXX)
O=.o

ifeq ($(LCS_CODEC_TRACE),ON)
    DEFINES:= $(DEFINES) -DCODEC_TRACE_ON
endif

PRJPREFIX=$(ITS_ROOT)/LCS

CFLAGS := $(CFLAGS) \
            -I$(PRJPREFIX)/include

CXXFLAGS := $(CXXFLAGS) \
            -I$(PRJPREFIX)/include

#
# release build with debug information
#
ifneq ($(DEBUG_BUILD),yes)
    ifeq ($(RELEASE_G),yes)
        CXXFLAGS := -g $(CXXFLAGS)
    endif
endif

#
# list of objects to be archieved into the library
#
OBJS=ie/infoelement$(O) \
     ie/cause$(O) \
     ie/cellidentity$(O) \
     ie/deltatimer$(O) \
     ie/channeldescription$(O) \
     ie/measurementreport$(O) \
     ie/timingadvance$(O) \
     ie/handovertype$(O) \
     ie/handoverreference$(O) \
     ie/startingtime$(O) \
     ie/neighborcellidentity$(O) \
     ie/neighborstarttime$(O) \
     ie/mspower$(O) \
     ie/frequencylist$(O) \
     ie/rrlpflag$(O) \
     ie/locationareacode$(O) \
     ie/cellidentitylist$(O) \
     ie/frequencylistrel8$(O) \
     ie/ciphermodesetting$(O) \
     ie/encryptionkey$(O) \
     ie/servingcellidentifier$(O) \
     ie/mspowerrel8$(O) \
     ie/deltatimerrel8$(O) \
     ie/channelmode$(O) \
     ie/multirateconfig$(O) \
     ie/pollingrepetition$(O) \
     ie/packetchanneldesc$(O) \
     ie/tlli$(O) \
     ie/tfi$(O) \
     ie/powerupstartuptime$(O) \
     ie/tbfstartingtime$(O) \
     ie/enhancedmeasurementreport$(O) \
     message$(O) \
     tarequest$(O) \
     taresponse$(O) \
     talayer3$(O) \
     reset$(O) \
     reject$(O) \
     abort$(O) \
     toarequest$(O) \
     toaresponse$(O) 
#     mspositioncommand$(O) \
#     mspositionresponse$(O)

#
# build target specification
#
all: $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).a \
     $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).so

clean:
	$(RM) -r $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).a \
             $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).so \
             $(OBJS) SunWS_cache ir.out ie/SunWS_cache ie/ir.out core

#
# additional object-header dependencies
#

#
# rules for the targets
#
$(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).a: $(OBJS)
	$(CXXAR) $(CXXARFLAGS) $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).a $(OBJS)

$(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).so: $(OBJS)
	$(CXXSO) $(CXXSHAREDARFLAGS) $(PRJPREFIX)/lib/libbsslap$(DBGSUFFIX).so -h libbsslap$(DBGSUFFIX).so $(OBJS)

#
# the standard rules
#
include $(ITS_ROOT)/config.rules

