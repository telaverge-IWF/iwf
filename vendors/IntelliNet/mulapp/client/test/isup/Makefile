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
#     FILE: Makefile                                                       #
#                                                                          #
############################################################################
#
# $Id: Makefile,v 1.1 2005/05/25 10:13:58 mmanikandan Exp $
#
# $Log: Makefile,v $
# Revision 1.1  2005/05/25 10:13:58  mmanikandan
# Initial Commit Multiple Application Binding.
#
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) 

VARIANT=95

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL) \
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/ISUP/include/ansi      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I . \
	-I$(ITS_ROOT)/tools/include  \
        -I$(VENDOR_ROOT)/IntelliNet/mulapp/client/include

LIBS:= -L$(ITS_ROOT)/common/lib\
       -L$(ITS_ROOT)/tools/lib \
       -L$(VENDOR_ROOT)/IntelliNet/mulapp/client/lib \
       -lDRIVER$(DBGSUFFIX) \
       -lENGINE$(DBGSUFFIX) \
       -lClient-Layer_$(PROTOCOL)$(DBGSUFFIX)

OBJS:= sendISUPMsg.o printISUPMsg.o readISUPMsg.o test.o dbc_server.o 

# Restrict the user to give explicit targets
all:   $(PROTOCOL)_Test$(DBGSUFFIX) 

$(PROTOCOL)_Test$(DBGSUFFIX): $(OBJS)
			$(CC) $(CFLAGS) -o \
			$@ $(OBJS) $(LIBS) $(THREADLIBS) $(SOCKLIBS) $(SYSLIBS) 

clean:
	$(RM) $(PROTOCOL)_Test$(DBGSUFFIX) $(OBJS) 

#
# get the rules
#
include	$(ITS_ROOT)/config.rules

