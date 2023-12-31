############################################################################
#                                                                          #
#     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# $Id: Makefile,v 1.2 2005/05/25 10:19:33 mmanikandan Exp $
#
# $Log: Makefile,v $
# Revision 1.2  2005/05/25 10:19:33  mmanikandan
# Modified according to config.vars
#
# Revision 1.1  2005/05/25 10:13:58  mmanikandan
# Initial Commit Multiple Application Binding.
#
############################################################################


#
# get the vars
#
include	$(ITS_ROOT)/config.vars

DEFINES:=$(DEFINES) 

CFLAGS:=$(CFLAGS) -g -I./include -DUNIX -DSOLARIS -D$(PROTOCOL)\
	-I$(ITS_ROOT)/common/include    \
        -I$(VENDOR_ROOT)/IntelliNet/include    \
        -I$(ITS_ROOT)/MTP2/include      \
        -I$(ITS_ROOT)/MTP3/include      \
	-I$(ITS_ROOT)/SCCP/include      \
        -I$(ITS_ROOT)/ISUP/include      \
        -I$(ITS_ROOT)/TCAP/include      \
        -I../include \
        -DINCLUDE_CODEC -DTCAP_CODEC\
	-I$(ITS_ROOT)/tools/include

LIBS:= -L$(ITS_ROOT)/common/lib  \
       -L$(ITS_ROOT)/ISUP/lib  \
       -L$(ITS_ROOT)/TCAP/lib/\
       $(ITS_ROOT)/SCCP/lib/lib$(PROTOCOL)-SCCP$(DBGSUFFIX).a \
       $(ITS_ROOT)/common/lib/libASN$(DBGSUFFIX).a\
       -l$(PROTOCOL)-TCAP\
       -l$(PROTOCOL)-ISUPD\
       -lCORE$(DBGSUFFIX)

COBJS:= mab_cmn.o mab_client.o mab_tcap_client.o mab_isup_client.o

# Restrict the user to give explicit targets
all:  ../lib/libClient-Layer_$(PROTOCOL)$(DBGSUFFIX).so 

../lib/libClient-Layer_$(PROTOCOL)$(DBGSUFFIX).so: $(COBJS)
			$(SHAREDAR) $(SHAREDARFLAGS) \
			$@ $(COBJS) $(LIBS) $(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

OBJS=


ifeq ($(PROTOCOL),ANSI)
client: cleanso  print
print:
	@echo ----- Building ANSI TCAP library. -----

ifneq ($(PROTOCOL),CCITT)
cleanso:
	$(RM) $(OBJS)\
        ../lib/*.so \
		.depend
else
clean:
endif
endif

clean:
	$(RM) ../lib/libClient-Layer_$(PROTOCOL)$(DBGSUFFIX).so $(COBJS) 

#
# get the rules
#
include	$(ITS_ROOT)/config.rules
