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
#  ID: $Id: Makefile,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
# 
#  LOG: $Log: Makefile,v $
#  LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
#  LOG: Adding Codec files to LCS folder
#  LOG:
#  LOG:
#  LOG:
# 
##############################################################################

##
include $(ITS_ROOT)/config.vars
DOC=doc++
#
# standard variables included
#

PROTOCOLS=bssaple bsslap

all:
	for protocol in $(PROTOCOLS); do $(MAKE) -C $$protocol all;   done

clean:
	for protocol in $(PROTOCOLS); do $(MAKE) -C $$protocol clean; done; \
	$(RM) -r ../doc/api

doc: ../doc/api/index.html

docclean:
	$(RM) -r ../doc/api

#
# rules for building the documents
#

ALLHEADERS=$(wildcard ../include/*/*.h) $(wildcard ../include/*/ie/*.h)

../doc/api/index.html: ../doc/doc.dxx $(ALLHEADERS)
	$(DOC) -d ../doc/api ../doc/doc.dxx

.PHONY: all clean doc docclean

#
# standard rules follow
#
include $(ITS_ROOT)/config.rules

