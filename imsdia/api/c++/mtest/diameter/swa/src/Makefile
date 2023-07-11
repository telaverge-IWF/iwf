############################################################################
#                                                                          #
#     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    #
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
# FILE: Makefile                                                           #
#                                                                          #
############################################################################
#                                                                          #
# ID: $Id: Makefile,v 1.1.4.1 2012/10/01 09:00:47 rsanjay Exp $
# LOG:
#
############################################################################
#ident "$Id: Makefile,v 1.1.4.1 2012/10/01 09:00:47 rsanjay Exp $"

#
# components under this project
#
.PHONY: all clean realclean test

all :
	$(MAKE) -f Makefile.stat ; \
	$(MAKE) -f Makefile.dist ; \

clean:
	$(MAKE) clean -f Makefile.stat ; \
	$(MAKE) clean -f Makefile.dist ; \

