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
# ID: $Id: Makefile,v 3.1 2008/03/31 10:33:16 nvijikumar Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.1  2008/03/31 10:33:16  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 1.2  2006/12/06 09:11:00  chandral
# LOG: Modified Build scripts as GA Rel1.2
# LOG:
# LOG: Revision 1.1  2006/10/03 09:21:28  rrath
# LOG: Baseline distributed demo for new IMS Interfaces.
# LOG:
#
############################################################################
# components under this project
#
COMPONENTS=gx/src rx/src wx/src tx/src ty/src


.PHONY: all clean realclean test

all clean realclean test:
	@for p in $(COMPONENTS); do \
	    if [ -d $$p ]; then \
            $(MAKE) -C $$p $@ || exit 1; \
	    else \
	        echo make[$(MAKELEVEL)]: Ignoring \`$$p\': not a directory; \
	    fi; \
	done
