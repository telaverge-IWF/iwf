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
#  LOG: $Log: Makefile,v $
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2.2.2.4.2.8.1  2015/05/18 05:15:09  kpnithin
#  LOG: cxdx v12 Test tool developed with new protocol file
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2.2.2.4.2  2014/02/12 11:12:30  jkchaitanya
#  LOG: changes for s13 and s13_r10
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2.2.2.4.1  2014/02/12 07:08:10  millayaraja
#  LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2.2.2  2013/10/26 07:43:30  ncshivakumar
#  LOG: RFC 6733 Changes
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2.2.1  2013/08/15 04:59:25  ncshivakumar
#  LOG: Updated for sy application
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.2  2013/05/22 09:59:50  ncshivakumar
#  LOG: Merged from 300 Branch
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4.2.1  2013/05/10 06:02:24  ncshivakumar
#  LOG: Fix for bug1507
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.5  2013/05/10 05:58:09  jsarvesh
#  LOG: changed dictionaryid for gx release 8
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.4  2013/04/06 08:14:50  jvikram
#  LOG: Reverting back sh_r7 inclusions. Will checkin after fixing java compilation issue
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.3  2013/04/05 12:58:34  jvikram
#  LOG: Changes related to cx/dx/sh have been included
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.2  2013/04/03 05:59:10  millayaraja
#  LOG: added gz interface instead of rfro
#  LOG:
#  LOG: Revision 3.18.2.4.2.5.4.1  2013/04/02 06:04:54  jsarvesh
#  LOG: release 11
#  LOG:
#  LOG: Revision 3.18.2.4.2.5  2012/12/20 18:36:23  rsanjay
#  LOG: Dictionary name changes
#  LOG:
#  LOG: Revision 3.18.2.4.2.4  2012/12/06 15:09:28  cprem
#  LOG: Made sure that dictInfo.txt is cleaned even for incremental build so that dictionaries are generated without any issues.
#  LOG:
#  LOG: Revision 3.18.2.4.2.3  2012/12/06 14:43:42  cprem
#  LOG: Commented out compilation of dictionaries which are not required for DRE.
#  LOG:
#  LOG: Revision 3.18.2.4.2.2  2012/10/01 09:01:03  rsanjay
#  LOG:  opendiameter code removal changes:bugzilla-id 300
#  LOG:
#  LOG: Revision 3.18.2.4.2.1  2012/09/06 11:30:45  jvikas
#  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
#  LOG:
#  LOG: Revision 3.18.2.4.4.5  2012/09/03 09:20:56  cprem
#  LOG: Removed DEBUGSUFFIX in pluginName argument passed to MAG for Transform code generation.
#  LOG:
#  LOG: Revision 3.18.2.4.4.4  2012/08/30 09:17:56  cprem
#  LOG: Added new argument for rfro_standalone target to generate dictionary.
#  LOG:
#  LOG: Revision 3.18.2.4.4.3  2012/08/23 05:07:41  cprem
#  LOG: Added sample plugin for S6a Rel-8 to Rel-10 Transformation plugin code generation.
#  LOG:
#  LOG: Revision 3.18.2.4.4.2  2012/08/22 09:35:42  cprem
#  LOG: Added target for s6a to s6a_r10 sample plugin generation
#  LOG:
#  LOG: Revision 3.18.2.4.4.1  2012/08/16 11:22:52  cprem
#  LOG: Added dictname as new parameter to MAG to generate dictionary classes for respective interface.
#  LOG:
#  LOG: Revision 3.18.2.4  2012/07/09 08:49:08  pramana
#  LOG: Changes done for Release 10 support for S6a, S13 interfaces (Bug 48).
#  LOG:
#  LOG: Revision 3.18.2.3  2012/07/09 07:37:54  pramana
#  LOG: Changes done for release 10 support of Gy, Gz interfaces (Bug 49).
#  LOG:
#  LOG: Revision 3.18.2.2  2012/07/09 05:16:50  pramana
#  LOG: Changes done for release 10 support of Gx, Gxx interface (Bug 47).
#  LOG:
#  LOG: Revision 3.18.2.1  2012/07/06 13:15:07  pramana
#  LOG: Changes done to S9 and Rx interfaces to support release 10 (Bug 50).
#  LOG:
#  LOG: Revision 3.18  2011/07/14 11:46:51  vkumara
#  LOG: Rw and Rs interface included.
#  LOG:
#  LOG: Revision 3.17  2011/06/29 06:20:06  vkumara
#  LOG: rr_requestmodel,rr_delegatedmodel and a4 interfaces.
#  LOG:
#  LOG: Revision 3.16  2011/06/14 05:18:34  vkumara
#  LOG: Gmb and Mm10 interfaces support.
#  LOG:
#  LOG: Revision 3.15  2011/06/02 04:00:46  vkumara
#  LOG: Zh and Zn interfaces support.
#  LOG:
#  LOG: Revision 3.14  2011/05/26 08:24:09  vkumara
#  LOG: Gi interface support.
#  LOG:
#  LOG: Revision 3.13  2011/05/20 04:09:56  vkumara
#  LOG: Re interface support.
#  LOG:
#  LOG: Revision 3.12  2011/05/09 11:08:19  vkumara
#  LOG: Wg and Pr interfaces support.
#  LOG:
#  LOG: Revision 3.10  2011/05/03 04:46:51  vkumara
#  LOG: SWm and SWx interfaces support.
#  LOG:
#  LOG: Revision 3.9  2011/04/27 11:36:57  vkumara
#  LOG: STa,SWa,S6b interfaces support.
#  LOG:
#  LOG: Revision 3.8  2011/04/18 08:07:51  vkumara
#  LOG: Wa interface support
#  LOG:
#  LOG: Revision 3.7  2011/03/10 09:31:08  vkumara
#  LOG: Gy Interface Support
#  LOG:
#  LOG: Revision 3.6  2010/07/29 09:21:20  nvijikumar
#  LOG: TS29214 RX interface support
#  LOG:
#  LOG: Revision 3.5  2010/07/13 10:10:31  nvijikumar
#  LOG: wd interface support
#  LOG:
#  LOG: Revision 3.4  2010/06/24 08:38:14  nvijikumar
#  LOG: RFRO release 8 updates
#  LOG:
#  LOG: Revision 3.3  2010/04/16 12:05:17  nvijikumar
#  LOG: S9 Interface Support
#  LOG:
#  LOG: Revision 3.2  2008/08/18 09:27:31  sureshj
#  LOG: Added Targets for s6a(MME-HSS) and s13(MME-EIR) interfaces.
#  LOG:
#  LOG: Revision 3.1  2008/03/31 10:33:27  nvijikumar
#  LOG: Start GA 3.0
#  LOG:
#  LOG: Revision 2.13  2008/03/27 12:01:55  hbhatnagar
#  LOG: Converting 2.1 branch to CURRENT
#  LOG:
#  LOG: Revision 2.9  2007/02/28 10:55:53  hbhatnagar
#  LOG: Changes to generate code for Wm interface.
#  LOG:
#  LOG: Revision 2.8  2007/01/03 11:31:17  hbhatnagar
#  LOG: Added targets for generating the Rq interface through abnf.
#  LOG:
#  LOG: Revision 2.7  2007/01/01 14:06:13  nanaparthi
#  LOG: adding targets for NASREQ & EAP
#  LOG:
#  LOG: Revision 2.6  2007/01/01 12:52:41  hbhatnagar
#  LOG: adding targets for mip, e2 and e4 interfaces and removing conflicts.
#  LOG:
#  LOG: Revision 2.5  2007/01/01 11:14:06  hbhatnagar
#  LOG: adding targets for mip, e2 and e4 interfaces.
#  LOG:
#  LOG: Revision 2.3  2006/10/26 12:16:07  kamakshilk
#  LOG: Added Bcgidcca target
#  LOG:
#  LOG: Revision 2.2  2006/10/16 15:55:40  tpanda
#  LOG: Merging with ITS-Diameter
#  LOG:
#  LOG: Revision 1.10.2.2  2006/09/27 11:19:35  hbhatnagar
#  LOG: Added new targets for bcgi dictionary (badri)
#  LOG:
#  LOG: Revision 1.10.2.1  2006/09/16 07:44:21  nvijikumar
#  LOG: Added DCCA protocol to generate code (badri)
#  LOG:
#  LOG: Revision 1.10  2006/08/03 13:24:08  brianhu
#  LOG: Support of vendor id in derived AVP spec
#  LOG:
#  LOG: Revision 1.9  2006/08/01 15:30:19  rrath
#  LOG: Changes for new interfaces
#  LOG:
#  LOG: Revision 1.8  2006/07/31 12:40:41  kamakshilk
#  LOG: Added target for dcca compilation
#  LOG:
#  LOG: Revision 1.7  2006/07/21 09:38:59  kamakshilk
#  LOG: Changes for new interface files
#  LOG:
#  LOG: Revision 1.6  2006/07/19 12:25:39  kamakshilk
#  LOG: Targets added for new interfaces
#  LOG:
#  LOG: Revision 1.5  2006/06/07 22:40:31  brianhu
#  LOG: Included command to generate Java API source.
#  LOG:
#  LOG: Revision 1.4  2006/06/02 04:36:01  kamakshilk
#  LOG: Includes rules for RfRo compilation and common dictionary generation
#  LOG:
#  LOG: Revision 1.3  2006/03/20 06:30:34  yranade
#  LOG: Correct paths.
#  LOG:
#  LOG: Revision 1.2  2006/03/02 13:19:16  tpanda
#  LOG: Update to correctly build dictionary.xml for all protocols
#  LOG:
#  LOG: Revision 1.1.1.1  2006/02/16 12:16:39  yranade
#  LOG: Create baseline imsdia project in CVS.
#  LOG:
#
############################################################################

include $(IMS_ROOT)/make.dirs

BASEDIR=base
SHDIR=sh
CXDXDIR=cxdx
CXDXDIR_v12=cxdx_v12
GQGQDIR=gqgqprime
RFRODIR=rfro
MIPDIR = mip
E2DIR = e2
E4DIR = e4
RQDIR = rq
WMDIR = wm
WDDIR = wd
S6ADIR = s6a
S6AR10DIR = s6a_r10
ROR10DIR = ro_r10
ifeq ($(PRODUCT), iwf)
TRANSATEL_CUSTOMAVPDIR = transatel_custom_avps
ROR10_TRANSATELDIR = ro_r10_transatel
endif
S6AR11DIR = s6a_r11
S13DIR = s13
S13R10DIR = s13_r10
WADIR = wa
STADIR = sta
SWADIR = swa
S6BDIR = s6b
SWMDIR = swm
SWXDIR = swx
S6DDIR = s6d
WGDIR = wg
PRDIR = pr
REDIR = re
GIDIR = gi
ZHDIR = zh
ZNDIR = zn
GMBDIR = gmb
MM10DIR = mm10
RR_REQUESTMODELDIR = rr_requestmodel
RR_DELEGATEDMODELDIR = rr_delegatedmodel
A4DIR= a4
RWDIR= rw
RSDIR= rs
GYR10DIR= gy_rel_10
GZDIR= gz
GZR10DIR= gz_r10
SYDIR = sy
APIDIR=../api
CAPIDIR=$(APIDIR)/c++
JAPIDIR=$(APIDIR)/java

APIINC=$(APIDIR)/c++/include/diameter
APISRC=$(APIDIR)/c++/src/diameter

ifeq ($(DIASTACK), OD)

ABNFSPECDIR=$(APIDIR)/abnf/OD

#DIRLIST=sh base cxdx gqgqprime rfro

.PHONY: all rest dict

##
#
##

all: disp dict rest rfro_standalone wx rx rx_r10 tx ty gx gx_r10 gxx_r10 dcca

disp:
	@echo "Generating for OpenDiameter"

rest:
	mkdir -p dict
	@echo "Generating the code for base,CxDx,Sh and GqGqprime Protocols"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx.protocol \
        $(ABNFSPECDIR)/sh.protocol \
        $(ABNFSPECDIR)/gqgqprime.protocol 

dict:   
	mkdir -p dict
	@echo "Generating dictionary for all Protocols"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/cmndictionary.xml \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/rfro_standalone_3gppavps.protocol\
        $(ABNFSPECDIR)/rfro_standalone.protocol \
        $(ABNFSPECDIR)/cxdx.protocol \
        $(ABNFSPECDIR)/sh.protocol \
        $(ABNFSPECDIR)/gqgqprime.protocol 

bcgidccadict:   
	mkdir -p dict
	@echo "Generating dictionary for BCGI DCCA Protocols"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/bcgimtestdictionary.xml \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/bcgi_dcca.protocol 

bcgidemodict:   
	mkdir -p dict
	@echo "Generating dictionary for Sh and BCGI DCCA Protocols"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/bcgidemodictionary.xml \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx.protocol \
        $(ABNFSPECDIR)/sh.protocol \
        $(ABNFSPECDIR)/bcgi_dcca.protocol 

rfro_standalone:	
	mkdir -p dict 
	@echo "Generating the code using RFRO standalone Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/rfro_standalone_3gppavps.protocol\
        $(ABNFSPECDIR)/rfro_standalone.protocol

wx:	
	mkdir -p dict 
	@echo "Generating the code using WX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.wx.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/wx_ietf.protocol \
        $(ABNFSPECDIR)/wx.protocol

tx:	
	mkdir -p dict 
	@echo "Generating the code using TX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.tx.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/tx_base.protocol \
        $(ABNFSPECDIR)/tx.protocol

ty:	
	mkdir -p dict 
	@echo "Generating the code using TY Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.ty.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/ty_base.protocol \
        $(ABNFSPECDIR)/ty.protocol

rx:	
	mkdir -p dict 
	@echo "Generating the code using RX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.rx.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rx_base.protocol \
        $(ABNFSPECDIR)/rx.protocol
rx_r10: 
	mkdir -p dict
	@echo "Generating the code using RX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.rx.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
		$(ABNFSPECDIR)/rx_base.protocol \
		$(ABNFSPECDIR)/rx.protocol

gx:	
	mkdir -p dict 
	@echo "Generating the code using GX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.gx.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/gx_base.protocol \
        $(ABNFSPECDIR)/gx.protocol

#Added here
gx_r10:	
	mkdir -p dict 
	@echo "Generating the code using GX_R10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.gx_r10.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/gx_base.protocol \
        $(ABNFSPECDIR)/gx_r10.protocol
dcca:	
	mkdir -p dict 
	@echo "Generating the code using DCCA Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.dcca.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/rfc4006.protocol

bcgidcca:	
	mkdir -p dict 
	@echo "Generating the code using DCCA Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/bcgi_dcca.protocol

sh:	
	mkdir -p dict 
	@echo "Generating the code using CXDX and SH Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx.protocol \
        $(ABNFSPECDIR)/sh.protocol

bcgidemo: bcgidemodict sh bcgidcca
bcgimtest: bcgidccadict bcgidcca

sh_v5protocol: baseprotocol cxdx_v5protocol  sh_v5dummy

sh_v5dummy:	
	mkdir -p dict 
	@echo "Generating the code using SH V5 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v5.protocol $(ABNFSPECDIR)/sh_v5.protocol
	
sh_v6protocol: baseprotocol cxdx_v6protocol  sh_v6dummy

sh_v6dummy:	
	mkdir -p dict 
	@echo "Generating the code using SH V6 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v6.protocol $(ABNFSPECDIR)/sh_v6.protocol
	
sh_v7protocol: baseprotocol cxdx_v7protocol  sh_v7dummy

sh_v7dummy:	
	mkdir -p dict 
	@echo "Generating the code using SH V7 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v7.protocol $(ABNFSPECDIR)/sh_v7.protocol
	
shprotocol: baseprotocol cxdxprotocol  shdummy

shdummy:	
	mkdir -p dict 
	@echo "Generating the code using SH Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx.protocol $(ABNFSPECDIR)/sh.protocol
	
cxdx_v5protocol: baseprotocol cxdx_v5dummy

cxdx_v5dummy:
	mkdir -p dict
	@echo "Generating the code using CXDX-V5 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v5.protocol

cxdx_v6protocol: baseprotocol cxdx_v6dummy

cxdx_v6dummy:
	mkdir -p dict
	@echo "Generating the code using CXDX-V6 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v6.protocol

cxdx_v7protocol: baseprotocol cxdx_v7dummy

cxdx_v7dummy:
	mkdir -p dict
	@echo "Generating the code using CXDX-V7 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx_v7.protocol

cxdxprotocol: baseprotocol cxdxdummy

cxdxdummy:
	mkdir -p dict
	@echo "Generating the code using CXDX Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/cxdx.protocol


gqgqdash_v0protocol:baseprotocol gqgq_v0dummy

gqgq_v0dummy:
	mkdir -p dict
	@echo "Generating the code using GQGQ Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/gqgqprime_v6_gqprimev0.protocol

gqgqdashprotocol:baseprotocol gqgqdummy

gqgqdummy:
	mkdir -p dict
	@echo "Generating the code using GQGQ Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol $(ABNFSPECDIR)/gqprime.protocol \
        $(ABNFSPECDIR)/gqgqprime_v6_gqprime.protocol

baseprotocol:
	mkdir -p dict 
	@echo "Generating the code using BASE Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictionary:dict/dictionary.xml \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) $(ABNFSPECDIR)/rfc6733.protocol 

clean:
	$(RM) -rf $(APIINC)/*; \
	$(RM) -rf $(APISRC)/*; \
	$(MAKE) -C ../api/java/src realclean; \
	$(RM) -rf dict

else

ABNFSPECDIR=$(APIDIR)/abnf/ITS

.PHONY: all 

ifeq ($(PRODUCT), iwf)
all: disp base dcca nasreq s6a s6a_r10 ro_r10 s6a_r11 cxdx_v12 \
     gy gy_rel_10 s6a_r10_conversion s13 s13_r10 cua \
	 transatel_custom_avps ro_r10_transatel  
else
all: disp base rx_r10 gx gx_r10 gxx_r10 dcca \
     nasreq s6a s6a_r10 ro_r10 s6a_r11 cxdx_v12 s13 s13_r10 s9 s9_r10 s9_r11 \
     gy gy_rel_10 s6a_r10_conversion gz gz_r10  cxdx_v7 sy cua 
endif


disp:
	@echo "Generating for ITSDiameter" \
	echo "" > ../api/c++/src/dictInfo.txt

base:
	@echo "Generating the code for Base Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol 

cxdx:
	@echo "Generating the code for CxDx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx.protocol

sh:
	@echo "Generating the code for Sh Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx.protocol \
        $(ABNFSPECDIR)/sh.protocol \

gqgq:
	@echo "Generating the code for GqGq' Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gqgqprime.protocol 

rfro_standalone:	
	@echo "Generating the code using RfRo standalone Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/rfro_standalone_v8.protocol

wx:	
	@echo "Generating the code using Wx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/wx.protocol

rx:	
	@echo "Generating the code using Rx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:rxapi$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/rx.protocol

rx_r10:
	@echo "Generating the code using Rx_r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:rx_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
		$(ABNFSPECDIR)/rfc6733.protocol \
		$(ABNFSPECDIR)/nasreq.protocol \
		$(ABNFSPECDIR)/rx_r10.protocol
							

rx_ts29214:	
	@echo "Generating the code using Rx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/rx_ts29214.protocol

gx:	
	@echo "Generating the code using Gx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gx_3gpp_r8_15$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gx.protocol

#Added here
gx_r10:	
	@echo "Generating the code using Gx_r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gx_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gx_r10.protocol

sy:	
	mkdir -p dict 
	@echo "Generating the code using SY Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:sy_3gpp_r11_4$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/sy.protocol
cua:	
	@echo "Generating the code using Capabilities Update Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:cua$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/rfc6737.protocol
gxx_r10:	
	@echo "Generating the code using Gxx_r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gxx_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gxx_r10.protocol

gy:
	@echo "Generating the code using Gy Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gy_3gpp_r8_10$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/gy.protocol

gy_rel_10:
	@echo "Generating the code using Gy r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gy_3gpp_r10_5$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/gy_rel_10.protocol 

tx:	
	@echo "Generating the code using Tx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/tx.protocol

ty:	
	@echo "Generating the code using Ty Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/ty.protocol

dcca:	
	@echo "Generating the code using DCCA Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/rfc4006.protocol

bcgidcca:	
	@echo "Generating the code using BCGI DCCA Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/bcgi_dcca.protocol

cx3gpp2:
	@echo "Generating the code for Cx 3GPP2 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cx_3gpp2.protocol
 
sh3gpp2:
	@echo "Generating the code for Sh 3GPP2 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cx_3gpp2.protocol \
        $(ABNFSPECDIR)/sh_3gpp2.protocol \

cxdx_v5:
	@echo "Generating the code using CXDX-V5 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v5.protocol

cxdx_v6:
	@echo "Generating the code using CXDX-V6 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v6.protocol

cxdx_v7:
	@echo "Generating the code using CXDX-V7 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:cxdx_3gpp_r7_1$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v7.protocol

cxdx_v12:
	@echo "Generating the code for CxDx v12 Protocol Release 10"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:cxdx_3gpp_r12_2$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/cxdx_v12.protocol


sh_v5:	
	@echo "Generating the code using SH-V5 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v5.protocol \
        $(ABNFSPECDIR)/sh_v5.protocol
	
sh_v6:	
	@echo "Generating the code using SH-V6 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v6.protocol \
        $(ABNFSPECDIR)/sh_v6.protocol
	
sh_v7:	
	@echo "Generating the code using SH-V7 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:sh_3gpp_r7_1$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/cxdx_v7.protocol \
        $(ABNFSPECDIR)/sh_v7.protocol
	
gqgq_v6:
	@echo "Generating the code using GQGQ' V6 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gqprime.protocol \
        $(ABNFSPECDIR)/gqgqprime_v6_gqprime.protocol

mip:
	@echo "Generating the code using Mobile IP RFC4004 "
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/mip.protocol

e2:
	@echo "Generating the code using e2 protocol "
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/e2.protocol

e4:
	@echo "Generating the code using e4 protocol "
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/e4.protocol

nasreq: 
	@echo "Generating the code for NASREQ Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol

eap:    
	@echo "Generating the code for eap Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol

rq:
	@echo "Generating the code for Rq Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/rq.protocol

wm:
	@echo "Generating the code for Wm Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/eap.protocol \
	$(ABNFSPECDIR)/wm.protocol

wd:
	@echo "Generating the code for Wd Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/eap.protocol \
	$(ABNFSPECDIR)/wd.protocol

s6a:
	@echo "Generating the code for s6a Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s6a_3gpp_r8_5$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/s6a.protocol

s6a_r10:
	@echo "Generating the code for s6a Protocol Release 10"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s6a_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/s6a_r10.protocol




transatel_custom_avps:
	@echo "Generating the code for transatel custom AVP's Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/transatel_custom_avps.protocol

ro_r10_transatel:
	@echo "Generating the code for Transatel Ro Protocol Release 10"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:ro_3gpp_r10_5_transatel$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/transatel_custom_avps.protocol \
	$(ABNFSPECDIR)/ro_r10_transatel.protocol

ro_r10:
	@echo "Generating the code for Ro Protocol Release 10"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:ro_3gpp_r10_5$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/ro_r10.protocol

s6a_r11:
	@echo "Generating the code for s6a Protocol Release 11"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s6a_3gpp_r11_5$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/s6a_r11.protocol


s13:
	@echo "Generating the code for s13 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s13_3gpp_r8_11$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/s13.protocol

s13_r10:
	@echo "Generating the code for s13 Protocol Release 10"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s13_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/s13_r10.protocol

s9:    
	@echo "Generating the code for s9 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s9_3gpp_r9_1$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/s9.protocol

s9_r10:
	@echo "Generating the code for s9_r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s9_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/s9_r10.protocol

s9_r11:
	@echo "Generating the code for s9_r11 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:s9_3gpp_r11_4$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/s9_r11.protocol

wa:
	@echo "Generating the code for Wa Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/wa.protocol

sta:
	@echo "Generating the code for STa Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/sta.protocol

swa:
	@echo "Generating the code for SWa Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/swa.protocol

s6b:
	@echo "Generating the code for SWa Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/s6b.protocol

swm:
	@echo "Generating the code for SWm Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/swm.protocol

swx:
	@echo "Generating the code for SWx Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/swx.protocol

s6d:
	@echo "Generating the code for s6d Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/s6d.protocol

wg:
	@echo "Generating the code for Wg Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/eap.protocol \
        $(ABNFSPECDIR)/wg.protocol

pr:
	@echo "Generating the code for Pr Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/pr.protocol

re:
	@echo "Generating the code for Re Protocol"
	$(JAVACMD) $(DIAJARFILE) \
        --c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/re.protocol

gi:
	@echo "Generating the code for Gi Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/gi.protocol
zh:
	@echo "Generating the code for Zh Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/zh.protocol

zn:
	@echo "Generating the code for Zn  Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/zn.protocol

gmb:
	@echo "Generating the code for Gmb  Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/gmb.protocol
mm10:

	@echo "Generating the code for Mm10  Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/mm10.protocol

rr_requestmodel:
	@echo "Generating the code for Rr_requestmodel  Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/rr_requestmodel.protocol
       
rr_delegatedmodel:
	@echo "Generating the code for Rr_delegatedmodel  Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/rr_delegatedmodel.protocol

a4:
	@echo "Generating the code for A4 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/a4.protocol

rw:
	@echo "Generating the code for RW Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/rw.protocol

rs:
	@echo "Generating the code for RS Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
	$(ABNFSPECDIR)/rfc6733.protocol \
	$(ABNFSPECDIR)/nasreq.protocol \
	$(ABNFSPECDIR)/rs.protocol

rfro_r10:	
	@echo "Generating the code using RfRo standalone Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/rfro_r10.protocol

s6a_r10_conversion:
	@echo "Generating the code for s6a Protocol Release 10 conversion"
	$(JAVACMD) $(DIAJARFILE) \
		--conversion:$(CAPIDIR) \
		--java:$(JAPIDIR) \
		--dict1:$(ABNFSPECDIR)/s6a.protocol \
		--dict2:$(ABNFSPECDIR)/s6a_r10.protocol \
		--pluginName:s6ar8_s6ar10_transform

gz:	
	@echo "Generating the code using gz Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gz_3gpp_r8_1$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gz.protocol

gz_r10:	
	@echo "Generating the code using gz_r10 Protocol"
	$(JAVACMD) $(DIAJARFILE) \
	--dictname:gz_3gpp_r10_6$(DBGSUFFIX) \
	--c++:$(CAPIDIR) --java:$(JAPIDIR) \
        $(ABNFSPECDIR)/rfc6733.protocol \
        $(ABNFSPECDIR)/nasreq.protocol \
        $(ABNFSPECDIR)/gz_r10.protocol

clean:
	$(RM) -rf $(APIINC)/*; \
	$(RM) -rf $(APISRC)/*; \
	$(MAKE) -C ../api/java/src realclean; \
	echo "" > ../api/c++/src/dictInfo.txt



endif
