############################################################################
#                                                                          #
#     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
#  ID: $Id: Makefile,v 9.1 2005/03/23 12:53:58 cvsadmin Exp $
#
############################################################################

include $(ITS_ROOT)/config.vars

OBJS = ftm_sample1_main.o

ITS_LIBS = -lGCS-CLIENT$(DBGSUFFIX)    \
           -lDSM-STUB$(DBGSUFFIX)      \
           -lDSM-GCS$(DBGSUFFIX)       \
           -lENGINE$(DBGSUFFIX)        \
           -lCORE$(DBGSUFFIX)          \
           -lSUPPORT$(DBGSUFFIX)       \
           -lCORE$(DBGSUFFIX)
 
LDFLAGS := $(LDFLAGS) -L$(ITS_ROOT)/common/lib 

CFLAGS := $(CFLAGS) -I.

all: ftm_sample1$(DBGSUFFIX)

ftm_sample1$(DBGSUFFIX): $(OBJS)
	$(CC) $(LDFLAGS) -o ftm_sample1$(DBGSUFFIX)             \
                    $(OBJS)                                 \
                    $(ITS_LIBS)                             \
                    $(SOCKLIBS)                             \
                    $(THREADLIBS)                           \
                    $(SYSLIBS)
                    

clean:
	$(RM) ftm_sample1$(DBGSUFFIX) $(OBJS) .depend


include $(ITS_ROOT)/config.rules

