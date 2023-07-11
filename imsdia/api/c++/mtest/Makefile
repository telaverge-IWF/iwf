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
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.17.2.3.2.2.38.2  2014/02/26 05:56:07  jkchaitanya
# LOG: changes for new tool for perfomance for tsl
# LOG:
# LOG: Revision 3.17.2.3.2.2.38.1  2014/02/12 07:04:29  millayaraja
# LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
# LOG:
# LOG: Revision 3.17.2.3.2.2  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG:
# LOG: Revision 3.17.2.4  2012/07/24 03:38:38  ksalil
# LOG: *** empty log message ***
# LOG:
# LOG: Revision 3.17.2.3.4.2  2012/08/28 06:46:44  cprem
# LOG: Commented out gx and other test compilation.
# LOG:
# LOG: Revision 3.17.2.3.4.1  2012/08/22 12:58:37  jvikas
# LOG: Fixed Linking and Compilation Issues
# LOG:
# LOG: Revision 3.17.2.3.2.1  2012/08/21 08:55:57  ksalil
# LOG: Merge from branch B-DRE-IDIA-0100-00
# LOG:
# LOG: Revision 3.17.2.3  2012/07/09 08:43:50  pramana
# LOG: Changes done to support release 10 for S6a, S13 interfaces (Bug 48).
# LOG:
# LOG: Revision 3.17.2.2  2012/07/09 07:20:33  pramana
# LOG: Changes done for release 10 update (Bug 49).
# LOG:
# LOG: Revision 3.17.2.1  2012/06/22 03:55:30  ncshivakumar
# LOG: TLS compilation changes
# LOG:
# LOG: Revision 3.17  2011/07/14 11:48:23  vkumara
# LOG: Rw and Rs interfaces included.
# LOG:
# LOG: Revision 3.16  2011/06/29 06:22:19  vkumara
# LOG: rr_requestmodel,rr_delegatedmodel and a4 interfaces.
# LOG:
# LOG: Revision 3.15  2011/06/14 05:20:32  vkumara
# LOG: Gmb and Mm10 interfaces support.
# LOG:
# LOG: Revision 3.14  2011/06/02 04:04:13  vkumara
# LOG: Zh and Zn interface support.
# LOG:
# LOG: Revision 3.13  2011/05/26 08:26:55  vkumara
# LOG: Gi Interface Support
# LOG:
# LOG: Revision 3.12  2011/05/20 04:11:39  vkumara
# LOG: Re interface support.
# LOG:
# LOG: Revision 3.11  2011/05/09 11:09:11  vkumara
# LOG: Wg and Pr interfaces support.
# LOG:
# LOG: Revision 3.9  2011/05/03 04:49:04  vkumara
# LOG: SWm and SWx interfaces support.
# LOG:
# LOG: Revision 3.8  2011/04/27 11:38:22  vkumara
# LOG: STa,SWa,S6b interfaces support.
# LOG:
# LOG: Revision 3.7  2011/04/18 08:10:02  vkumara
# LOG: Wa interface support
# LOG:
# LOG: Revision 3.6  2011/03/10 09:28:40  vkumara
# LOG: Included Gy Interface
# LOG:
# LOG: Revision 3.5  2010/07/29 09:18:46  nvijikumar
# LOG: RX sample app for TS29214 support
# LOG:
# LOG: Revision 3.4  2010/07/13 10:07:07  nvijikumar
# LOG: Added wd interface
# LOG:
# LOG: Revision 3.3  2009/03/19 16:31:59  ssaxena
# LOG: Added the target to compile the Redirect Application
# LOG:
# LOG: Revision 3.2  2008/08/19 07:13:41  sureshj
# LOG: Changes for compiling S6a and s13 demo applications.
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:05  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.10  2007/02/28 11:04:59  hbhatnagar
# LOG: Changes to compile Wm Demo Application.
# LOG:
# LOG: Revision 2.9  2007/01/12 04:52:07  kamakshilk
# LOG: nasreq src added
# LOG:
# LOG: Revision 2.8  2007/01/11 10:29:18  kamakshilk
# LOG: eap src added
# LOG:
# LOG: Revision 2.7  2007/01/08 07:43:10  hbhatnagar
# LOG: added component for the rq interface.
# LOG:
# LOG: Revision 2.6  2007/01/04 16:07:15  hbhatnagar
# LOG: added component for the e4 interface
# LOG:
# LOG: Revision 2.5  2007/01/04 12:59:13  hbhatnagar
# LOG: added component for the e2 interface
# LOG:
# LOG: Revision 2.4  2007/01/01 15:29:10  hbhatnagar
# LOG: added component for the mip app
# LOG:
# LOG: Revision 2.3  2006/12/19 07:36:32  kamakshilk
# LOG: All interfaces added
# LOG:
# LOG: Revision 2.2  2006/10/25 11:11:02  nvijikumar
# LOG: Added DCCA module for compilation.
# LOG:
# LOG: Revision 2.1  2006/09/13 09:22:40  yranade
# LOG: Start GA 1.1
# LOG:
# LOG: Revision 1.2  2006/07/26 05:56:00  nvijikumar
# LOG: Changes to compile all new interfaces.
# LOG:
# LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
# LOG: Create baseline imsdia project in CVS.
# LOG:
#
############################################################################
#
# components under this project
#
#COMPONENTS=diameter/app/src diameter/app_stat/src diameter/app_dist/src diameter/cxdx/src diameter/sh/src diameter/gqgqprime/src diameter/rfro/src diameter/gx/src diameter/rx/src diameter/wx/src diameter/tx/src diameter/ty/src diameter/dcca/src diameter/cx_3gpp2/src diameter/sh_3gpp2/src diameter/eap/src diameter/nasreq/src diameter/mip/src diameter/e2/src diameter/e4/src diameter/rq/src diameter/wm/src diameter/s6a/src diameter/s13/src diameter/redirect/src diameter/wd/src diameter/rx_ts29214/src diameter/gy/src diameter/wa/src diameter/sta/src diameter/swa/src diameter/s6b/src diameter/swm/src diameter/swx/src diameter/s6d/src diameter/wg/src diameter/pr/src diameter/re/src diameter/gi/src diameter/zh/src/ diameter/zn/src/  diameter/gmb/src/  diameter/mm10/src/  diameter/rr_requestmodel/src/  diameter/rr_delegatedmodel/src/  diameter/a4/src/  diameter/rw/src/ diameter/rs/src/

#COMPONENTS=diameter/app/src diameter/app_stat/src diameter/app_dist/src diameter/gx/src diameter/dcca/src diameter/nasreq/src diameter/gy/src diameter/gy_rel_10/src diameter/s6a_r10/src diameter/s13_r10/src
ifeq ($(PRODUCT), iwf)
	COMPONENTS=diameter/app/src diameter/app_stat/src diameter/ro_r10_perf_sim/src diameter/ro_r10_sim/src diameter/ro_r10/src diameter/s6a_r10/src diameter/ro_r10_transatel/src diameter/ro_tsl_perf/src
else 
	COMPONENTS=diameter/app/src diameter/app_stat/src diameter/app_dist/src 
endif
#diameter/gx/src diameter/dcca/src 
#diameter/nasreq/src diameter/gy/src diameter/gy_rel_10/src diameter/s6a_r10/src diameter/s13_r10/src


.PHONY: all clean realclean test

all clean realclean test:
	@for p in $(COMPONENTS); do \
	    if [ -d $$p ]; then \
            $(MAKE) -C $$p $@ || exit 1; \
	    else \
	        echo make[$(MAKELEVEL)]: Ignoring \`$$p\': not a directory; \
	    fi; \
	done
