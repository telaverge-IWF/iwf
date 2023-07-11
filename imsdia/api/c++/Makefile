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
# ID: $Id: Makefile,v 3.20.2.5.2.8.4.4.2.2.2.2.4.3.8.1 2015/05/18 05:15:09 kpnithin Exp $
# ID: $Id: Makefile,v 3.20.2.5.2.8.4.4.2.2.2.2.4.3.8.1 2015/05/18 05:15:09 kpnithin Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.2.4.3.8.1  2015/05/18 05:15:09  kpnithin
# LOG: cxdx v12 Test tool developed with new protocol file
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.2.4.3  2014/02/12 13:16:24  jkchaitanya
# LOG: modified make file linking for IWF
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.2.4.2  2014/02/12 11:13:58  jkchaitanya
# LOG: added s13 for IWF
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.2.4.1  2014/02/12 07:03:52  millayaraja
# LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.2  2013/10/26 07:47:51  ncshivakumar
# LOG: RFC 6733 changes
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2.2.1  2013/08/15 05:00:28  ncshivakumar
# LOG: Updated for sy Application
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.2  2013/05/22 09:59:50  ncshivakumar
# LOG: Merged from 300 Branch
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4.2.1  2013/05/10 05:59:49  ncshivakumar
# LOG: Fix for bug1507
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.5  2013/05/10 05:58:30  jsarvesh
# LOG: changed dictionaryid for gx release 8
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.4  2013/04/10 04:30:50  millayaraja
# LOG: added s6ar11 and s9r11 interfaces to Makefiles
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.3  2013/04/05 12:58:34  jvikram
# LOG: Changes related to cx/dx/sh have been included
# LOG:
# LOG: Revision 3.20.2.5.2.8.4.2  2013/04/03 07:02:06  millayaraja
# LOG: updated for gz interface
# LOG:
# LOG: Revision 3.20.2.5.2.8  2012/12/20 18:35:45  rsanjay
# LOG: Dictionary name changes
# LOG:
# LOG: Revision 3.20.2.5.2.7  2012/12/06 14:46:08  cprem
# LOG: Commented out compilation of dictionaries that are not required for DRE.
# LOG:
# LOG: Revision 3.20.2.5.2.6  2012/11/20 17:39:44  pramana
# LOG: Merged from CMAPI branch for 212-07 release
# LOG:
# LOG: Revision 3.20.2.5.2.2.12.1  2012/11/20 10:18:27  rgovardhan
# LOG: merge from 00 Nov20Rel
# LOG:
# LOG: Revision 3.20.2.5.2.4  2012/11/06 16:31:20  pramana
# LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
# LOG:
# LOG: Revision 3.20.2.5.2.2.18.1  2012/11/06 11:02:32  pramana
# LOG: Merged from 00 branch
# LOG:
# LOG: Revision 3.20.2.5.2.3  2012/11/05 11:50:49  jvikas
# LOG: Changed indentation
# LOG:
# LOG: Revision 3.20.2.5.2.2  2012/10/03 15:10:43  cprem
# LOG: Merged from ERLBF branch B-DRE-0212-02
# LOG:
# LOG: Revision 3.20.2.5.2.1.2.1  2012/09/14 15:40:19  cprem
# LOG: Added additional compilation flags for inclusion of unordered map in dictionary.
# LOG:
# LOG: Revision 3.20.2.5.2.1  2012/09/06 11:30:45  jvikas
# LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
# LOG:
# LOG: Revision 3.20.2.5.4.5  2012/08/30 10:24:52  cprem
# LOG: Commented out transform plugin lib compilation as this is done in dre/transformPlugins folder.
# LOG:
# LOG: Revision 3.20.2.5.4.4  2012/08/28 03:59:26  cprem
# LOG: Uncommented compilation.
# LOG:
# LOG: Revision 3.20.2.5.4.3  2012/08/27 10:03:40  cprem
# LOG: Added Json includes.
# LOG:
# LOG: Revision 3.20.2.5.4.2  2012/08/22 09:31:13  cprem
# LOG: Added target for sample plugin for s6a to s6a rel10 transformation. Also added includes for same.
# LOG:
# LOG: Revision 3.20.2.5.4.1  2012/08/16 11:19:17  cprem
# LOG: Added DTF includes and blocks include.
# LOG:
# LOG: Revision 3.20.2.5  2012/07/09 09:36:41  pramana
# LOG: Fixed issue with compilation
# LOG:
# LOG: Revision 3.20.2.4  2012/07/09 08:41:17  pramana
# LOG: Added support for Release 10 to S13, S6a interfaces (Bug 48).
# LOG:
# LOG: Revision 3.20.2.3  2012/07/09 07:35:33  pramana
# LOG: Changes done for release 10 support of Gy, Gz (Bug 49).
# LOG:
# LOG: Revision 3.20.2.2  2012/07/09 05:18:13  pramana
# LOG: Changes done for release 10 support of Gx, Gxx interfaces (Bug 47).
# LOG:
# LOG: Revision 3.20.2.1  2012/07/06 13:08:05  pramana
# LOG: Changes done for S9 and Rx interfaces to support release 10 (Bug 50).
# LOG:
# LOG: Revision 3.20  2011/07/14 11:47:37  vkumara
# LOG: Rs and Rw interfaces included.
# LOG:
# LOG: Revision 3.19  2011/06/29 06:21:38  vkumara
# LOG: rr_requestmodel,rr_delegatedmodel and a4 interfaces.
# LOG:
# LOG: Revision 3.18  2011/06/14 05:19:58  vkumara
# LOG: Gmb and Mm10 interfaces support.
# LOG:
# LOG: Revision 3.17  2011/06/02 04:03:16  vkumara
# LOG: Zh and Zn interface support.
# LOG:
# LOG: Revision 3.16  2011/05/26 08:25:45  vkumara
# LOG: Gi Interface Support.
# LOG:
# LOG: Revision 3.15  2011/05/20 04:11:05  vkumara
# LOG: Re interface support.
# LOG:
# LOG: Revision 3.14  2011/05/09 11:08:48  vkumara
# LOG: Wg and Pr interfaces support
# LOG:
# LOG: Revision 3.12  2011/05/03 04:48:33  vkumara
# LOG: SWm and SWx interfaces support.
# LOG:
# LOG: Revision 3.11  2011/04/27 11:37:52  vkumara
# LOG: STa,SWa,S6b interfaces support.
# LOG:
# LOG: Revision 3.10  2011/04/18 08:09:02  vkumara
# LOG: Wa interface support
# LOG:
# LOG: Revision 3.9  2011/03/10 09:32:43  vkumara
# LOG: Gy Interface Support
# LOG:
# LOG: Revision 3.8  2010/07/29 09:19:24  nvijikumar
# LOG: TS29214 support
# LOG:
# LOG: Revision 3.7  2010/07/13 10:08:55  nvijikumar
# LOG: wd interface support
# LOG:
# LOG: Revision 3.6  2010/04/16 12:04:11  nvijikumar
# LOG: S9 Interface Support
# LOG:
# LOG: Revision 3.5  2009/01/07 10:51:20  nvijikumar
# LOG: Updates to remove interfaces object files in target "clean"
# LOG:
# LOG: Revision 3.4  2008/08/27 09:38:25  sureshj
# LOG: NOWHOLEARCHIVE added to s6a and s13.
# LOG:
# LOG: Revision 3.3  2008/08/18 10:16:11  sureshj
# LOG: Changes to compile intefaces s6a and s13 generated code.
# LOG:
# LOG: Revision 3.2  2008/08/12 04:23:25  nvijikumar
# LOG: Defined NOWHOLEARCHIVE to remove libc_nonshared dependency. gdalawai
# LOG:
# LOG: Revision 3.1  2008/03/31 10:33:05  nvijikumar
# LOG: Start GA 3.0
# LOG:
# LOG: Revision 2.17  2008/03/27 11:31:37  hbhatnagar
# LOG: Converting 2.1 branch to CURRENT
# LOG:
# LOG: Revision 2.13.2.1  2007/03/02 07:37:38  hbhatnagar
# LOG: only including NasreqAVP and EapAVP object files in Wm codec lib
# LOG:
# LOG: Revision 2.13  2007/02/28 10:58:31  hbhatnagar
# LOG: Chnages to compile Wm interface generated code.
# LOG:
# LOG: Revision 2.12  2007/01/17 06:50:28  nvijikumar
# LOG: Seperated nasreqapi library it can be linked with applications.
# LOG:
# LOG: Revision 2.11  2007/01/11 05:56:47  kamakshilk
# LOG: sh and cx 3gpp2 library names changed to sh_3gpp2 and cx_3gpp2
# LOG:
# LOG: Revision 2.10  2007/01/03 11:35:43  hbhatnagar
# LOG: added targets for the Rq interface.
# LOG:
# LOG: Revision 2.9  2007/01/01 14:08:11  nanaparthi
# LOG: NASREQ is updated & EAP target added
# LOG:
# LOG: Revision 2.8  2007/01/01 12:56:26  hbhatnagar
# LOG: adding the targets for mip(RFC4004), e2 and e4 interfaces.
# LOG:
# LOG: Revision 2.7  2006/12/19 07:35:42  kamakshilk
# LOG: Cx and Sh 3GPP2 targets added
# LOG:
# LOG: Revision 2.6  2006/10/29 10:37:08  kamakshilk
# LOG: NASREQ OBJS added to WX, GX and TY OBJS
# LOG:
# LOG: Revision 2.5  2006/10/28 07:47:42  yranade
# LOG: Library linking reorganisation, codec lib so generation
# LOG:
# LOG: Revision 2.4  2006/10/26 17:00:23  hbhatnagar
# LOG: made changes in CMNOBJS and added BCGI targets for ITS.( Hemant)
# LOG:
# LOG: Revision 2.2  2006/10/16 15:57:22  tpanda
# LOG: Merging with ITS-Diameter
# LOG:
# LOG: Revision 1.4.2.6  2006/09/28 06:59:29  nvijikumar
# LOG: Wx Target Added
# LOG:
# LOG: Revision 1.4.2.5  2006/09/28 06:37:08  nvijikumar
# LOG: Added gx library
# LOG:
# LOG: Revision 1.4.2.4  2006/09/28 05:43:55  nvijikumar
# LOG: Modified to make common library (badri)
# LOG:
# LOG: Revision 1.4.2.3  2006/09/27 12:32:20  hbhatnagar
# LOG: Changes for bcgi release (badri)
# LOG:
# LOG: Revision 1.4.2.2  2006/09/27 10:03:10  hbhatnagar
# LOG: Added support for bcgi namespace (badri)
# LOG:
# LOG: Revision 1.4.2.1  2006/09/16 05:31:44  nvijikumar
# LOG: Added dcca module for generating DCCA API (badri)
# LOG:
# LOG: Revision 1.4  2006/07/26 09:20:40  kamakshilk
# LOG: Changes to compile new interfaces code.
# LOG:
# LOG: Revision 1.3  2006/06/02 09:18:50  yranade
# LOG: Add RfRo Compilation.
# LOG:
# LOG: Revision 1.2  2006/02/21 13:20:17  yranade
# LOG: GqGqprime specifics (VijiKumar)
# LOG:
# LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
# LOG: Create baseline imsdia project in CVS.
# LOG:
#
############################################################################
#
# Makefile for IntelliNet Diameter Messaging API Libraries
#
include $(IMS_ROOT)/make.dirs

CXXFLAGS:=$(CXXFLAGS) -std=c++0x -DJSON_IS_AMALGAMATION -DHAVE_THROW_SPECS -DHAVE_NAMESPACES -DHAVE_STD_NAMESPACE -DHAVE_STL -Iinclude -I$(IMS_ROOT)/dtf/include -I$(EACC_ROOT)/blocks/include \
			-I$(ITS_ROOT)/common/include -I$(IMS_ROOT)/common/include \
			-I$(IMS_ROOT)/vendors/IntelliNet/include/  \
			-I$(EACC_ROOT)/3rdparty/jsoncpp_0.6.0-rc2/

#
# Protocols to be built
#
BASEPROTO=diameter \
          diameter.base \

CXDXPROTO=diameter.cxdx 

SHPROTO=diameter.sh 

GQGQPROTO=diameter.gqgqprime 

RFROPROTO=diameter.rfro \
          diameter.rfro.ims

CXDX_R7PROTO=diameter.cxdx_v7
SH_R7PROTO=diameter.sh_v7

ifeq ($(DIASTACK) , OD)
RFROPROTO += diameter.rfro.ietf 
endif

DCCAPROTO=diameter.dcca 

WXPROTO=diameter.wx 
ifeq ($(DIASTACK) , OD)
WXPROTO += diameter.wx.ietf
endif

RXPROTO=diameter.rx 
ifeq ($(DIASTACK) , OD)
RXPROTO += diameter.rx.base
endif

RX_R10PROTO=diameter.rx_r10
ifeq ($(DIASTACK) , OD)
RX_R10PROTO += diameter.rx_r10.base
endif

GXPROTO=diameter.gx 
ifeq ($(DIASTACK) , OD)
GXPROTO += diameter.gx.base
endif

GX_R10PROTO=diameter.gx_r10 
ifeq ($(DIASTACK) , OD)
GX_R10PROTO += diameter.gx_r10.base
endif

GXX_R10PROTO=diameter.gxx_r10 
ifeq ($(DIASTACK) , OD)
GXX_R10PROTO += diameter.gxx_r10.base
endif

SYPROTO=diameter.sy 
ifeq ($(DIASTACK) , OD)
SYPROTO += diameter.sy.base
endif

CUAPROTO=diameter.cua 
ifeq ($(DIASTACK) , OD)
CUAPROTO += diameter.cua.base
endif

GYPROTO=diameter.gy
ifeq ($(DIASTACK) , OD)
GYPROTO += diameter.gy.base
endif

TXPROTO=diameter.tx 
ifeq ($(DIASTACK) , OD)
TXPROTO += diameter.tx.base
endif

TYPROTO=diameter.ty 
ifeq ($(DIASTACK) , OD)
TYPROTO += diameter.ty.base
endif

BCGIDCCAPROTO=diameter.bcgi 

NASREQPROTO=diameter.nasreq 

EAPPROTO=diameter.eap

CX3GPP2PROTO=diameter.cx_3gpp2

SH3GPP2PROTO=diameter.sh_3gpp2 

MIPPROTO=diameter.mip

E2PROTO=diameter.e2

E4PROTO=diameter.e4

RQPROTO=diameter.rq

WMPROTO=diameter.wm

WDPROTO=diameter.wd

S6APROTO=diameter.s6a

S6AR10PROTO=diameter.s6a_r10

ROR10PROTO=diameter.ro_r10

S6AR11PROTO=diameter.s6a_r11

S13PROTO=diameter.s13

S13R10PROTO=diameter.s13_r10

S9PROTO=diameter.s9

S9_R10PROTO=diameter.s9_r10

S9_R11PROTO=diameter.s9_r11

RX29214PROTO=diameter.rx_ts29214

GYPROTO=diameter.gy

GYREL10PROTO=diameter.gy_rel_10

WAPROTO=diameter.wa

STAPROTO=diameter.sta

SWAPROTO=diameter.swa

S6BPROTO=diameter.s6b

SWMPROTO=diameter.swm

SWXPROTO=diameter.swx

S6DPROTO=diameter.s6d

WGPROTO=diameter.wg

PRPROTO=diameter.pr

REPROTO=diameter.re

GIPROTO=diameter.gi

ZHPROTO=diameter.zh

ZNPROTO=diameter.zn

GMBPROTO=diameter.gmb

MM10PROTO=diameter.mm10

RR_REQUESTMODELPROTO=diameter.rr_requestmodel

RR_DELEGATEDMODELPROTO=diameter.rr_delegatedmodel

A4PROTO=diameter.a4

RWPROTO=diameter.rw

RSPROTO=diameter.rs

RFROR10PROTO=diameter.rfro_r10 

GZPROTO=diameter.gz

GZR10PROTO=diameter.gz_r10

ifeq ($(PRODUCT), iwf)
TRANSATELAVPSPROTO=diameter.transatel_custom_avps
ROR10TRANSATELPROTO=diameter.ro_r10_transatel
CXDXV12PROTO=diameter.cxdx_v12
endif

BASESRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(BASEPROTO))))
BASEOBJS=$(BASESRCS:.cpp=.o)

CXDXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(CXDXPROTO))))
CXDXOBJS=$(CXDXSRCS:.cpp=.o)

SHSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SHPROTO))))
SHOBJS=$(SHSRCS:.cpp=.o)

CXDX_R7SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(CXDX_R7PROTO))))
CXDX_R7OBJS=$(CXDX_R7SRCS:.cpp=.o)

SH_R7SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SH_R7PROTO))))
SH_R7OBJS=$(SH_R7SRCS:.cpp=.o)

GQGQSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GQGQPROTO))))
GQGQOBJS=$(GQGQSRCS:.cpp=.o)

RFROSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RFROPROTO))))
RFROOBJS=$(RFROSRCS:.cpp=.o)

RFROR10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RFROR10PROTO))))
RFROR10OBJS=$(RFROR10SRCS:.cpp=.o)

DCCASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(DCCAPROTO))))
DCCAOBJS=$(DCCASRCS:.cpp=.o)

WXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(WXPROTO))))
WXOBJS=$(WXSRCS:.cpp=.o)

RXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RXPROTO))))
RXOBJS=$(RXSRCS:.cpp=.o)

RX_R10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RX_R10PROTO))))
RX_R10OBJS=$(RX_R10SRCS:.cpp=.o)

GXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GXPROTO))))
GXOBJS=$(GXSRCS:.cpp=.o)

GX_R10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GX_R10PROTO))))
GX_R10OBJS=$(GX_R10SRCS:.cpp=.o)

GXX_R10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GXX_R10PROTO))))
GXX_R10OBJS=$(GXX_R10SRCS:.cpp=.o)

SYSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SYPROTO))))
SYOBJS=$(SYSRCS:.cpp=.o)

CUASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(CUAPROTO))))
CUAOBJS=$(CUASRCS:.cpp=.o)

GYSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GYPROTO))))
GYOBJS=$(GYSRCS:.cpp=.o)

GYREL10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GYREL10PROTO))))
GYREL10OBJS=$(GYREL10SRCS:.cpp=.o)

TXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(TXPROTO))))
TXOBJS=$(TXSRCS:.cpp=.o)

TYSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(TYPROTO))))
TYOBJS=$(TYSRCS:.cpp=.o)

BCGIDCCASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(BCGIDCCAPROTO))))
BCGIDCCAOBJS=$(BCGIDCCASRCS:.cpp=.o)

NASREQSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(NASREQPROTO))))
NASREQOBJS=$(NASREQSRCS:.cpp=.o)

EAPSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(EAPPROTO))))
EAPOBJS=$(EAPSRCS:.cpp=.o)

CX3GPP2SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(CX3GPP2PROTO))))
CX3GPP2OBJS=$(CX3GPP2SRCS:.cpp=.o)

SH3GPP2SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SH3GPP2PROTO))))
SH3GPP2OBJS=$(SH3GPP2SRCS:.cpp=.o)

MIPSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(MIPPROTO))))
MIPOBJS=$(MIPSRCS:.cpp=.o)

E2SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(E2PROTO))))
E2OBJS=$(E2SRCS:.cpp=.o)

E4SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(E4PROTO))))
E4OBJS=$(E4SRCS:.cpp=.o)

RQSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RQPROTO))))
RQOBJS=$(RQSRCS:.cpp=.o)

WMSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(WMPROTO))))
WMOBJS=$(WMSRCS:.cpp=.o)

WDSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(WDPROTO))))
WDOBJS=$(WDSRCS:.cpp=.o)

S6ASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6APROTO))))
S6AOBJS=$(S6ASRCS:.cpp=.o)

S6AR10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6AR10PROTO))))
S6AR10OBJS=$(S6AR10SRCS:.cpp=.o)

ROR10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(ROR10PROTO))))
ROR10OBJS=$(ROR10SRCS:.cpp=.o)

S6AR11SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6AR11PROTO))))
S6AR11OBJS=$(S6AR11SRCS:.cpp=.o)

S13SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S13PROTO))))
S13OBJS=$(S13SRCS:.cpp=.o)

S13R10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S13R10PROTO))))
S13R10OBJS=$(S13R10SRCS:.cpp=.o)

S9SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S9PROTO))))
S9OBJS=$(S9SRCS:.cpp=.o)

S9_R10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S9_R10PROTO))))
S9_R10OBJS=$(S9_R10SRCS:.cpp=.o)

S9_R11SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S9_R11PROTO))))
S9_R11OBJS=$(S9_R11SRCS:.cpp=.o)

RX29214SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RX29214PROTO))))
RX29214OBJS=$(RX29214SRCS:.cpp=.o)

WASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(WAPROTO))))
WAOBJS=$(WASRCS:.cpp=.o)

STASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(STAPROTO))))
STAOBJS=$(STASRCS:.cpp=.o)

SWASRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SWAPROTO))))
SWAOBJS=$(SWASRCS:.cpp=.o)

S6BSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6BPROTO))))
S6BOBJS=$(S6BSRCS:.cpp=.o)

SWMSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SWMPROTO))))
SWMOBJS=$(SWMSRCS:.cpp=.o)

SWXSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(SWXPROTO))))
SWXOBJS=$(SWXSRCS:.cpp=.o)

S6DSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6DPROTO))))
S6DOBJS=$(S6DSRCS:.cpp=.o)

WGSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(WGPROTO))))
WGOBJS=$(WGSRCS:.cpp=.o)

PRSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(PRPROTO))))
PROBJS=$(PRSRCS:.cpp=.o)

RESRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(REPROTO))))
REOBJS=$(RESRCS:.cpp=.o)

GISRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GIPROTO))))
GIOBJS=$(GISRCS:.cpp=.o)

ZHSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(ZHPROTO))))
ZHOBJS=$(ZHSRCS:.cpp=.o)

ZNSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(ZNPROTO))))
ZNOBJS=$(ZNSRCS:.cpp=.o)

GMBSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GMBPROTO))))
GMBOBJS=$(GMBSRCS:.cpp=.o)

MM10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(MM10PROTO))))
MM10OBJS=$(MM10SRCS:.cpp=.o)

RR_REQUESTMODELSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RR_REQUESTMODELPROTO))))
RR_REQUESTMODELOBJS=$(RR_REQUESTMODELSRCS:.cpp=.o)

RR_DELEGATEDMODELSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RR_DELEGATEDMODELPROTO))))
RR_DELEGATEDMODELOBJS=$(RR_DELEGATEDMODELSRCS:.cpp=.o)

A4SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(A4PROTO))))
A4OBJS=$(A4SRCS:.cpp=.o)

RWSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RWPROTO))))
RWOBJS=$(RWSRCS:.cpp=.o)

RSSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(RSPROTO))))
RSOBJS=$(RSSRCS:.cpp=.o)

GZSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GZPROTO))))
GZOBJS=$(GZSRCS:.cpp=.o)

GZR10SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(GZR10PROTO))))
GZR10OBJS=$(GZR10SRCS:.cpp=.o)

ifeq ($(PRODUCT), iwf)
TRANSATELAVPSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(TRANSATELAVPSPROTO))))
TRANSATELAVPOBJS=$(TRANSATELAVPSRCS:.cpp=.o)
ROR10TRANSATELSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(ROR10TRANSATELPROTO))))
ROR10TRANSATELOBJS=$(ROR10TRANSATELSRCS:.cpp=.o)
CXDXV12SRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(CXDXV12PROTO))))
CXDXV12BJS=$(CXDXV12SRCS:.cpp=.o)

endif

ifeq ($(PRODUCT), iwf)
CMNOBJECTS=$(BASEOBJS) $(DCCAOBJS) $(NASREQOBJS) \
		   $(S6AOBJS) $(S6AR10OBJS) $(S6AR11OBJS) $(GYOBJS) $(ROR10OBJS) \
		   $(S13OBJS) $(S13R10OBJS) $(GYREL10OBJS) $(CUAOBJS) \
		   $(TRANSATELAVPOBJS) $(ROR10TRANSATELOBJS)\
		   $(CXDXV12BJS)
else
CMNOBJECTS=$(BASEOBJS) $(RFROOBJS)     \
           $(DCCAOBJS) $(RX_R10OBJS) $(GXOBJS)  \
           $(NASREQOBJS) \
		   $(S6AOBJS) $(S6AR10OBJS) $(S6AR11OBJS) $(S13OBJS) $(S13R10OBJS) $(S9OBJS) $(S9_R10OBJS) $(S9_R11OBJS) $(GYOBJS) \
		   $(S6BOBJS) $(ROR10OBJS) \
		   $(GYREL10OBJS) $(RFROR10OBJS) \
		   $(GX_R10OBJS) $(GXX_R10OBJS) $(GZOBJS) $(GZR10OBJS) $(SYOBJS) $(CUAOBJS) 
endif

#Diameter Transformer Objects
S6AR8R10=diameter.transform.s6ar8_s6ar10_transform
S6AR8R10TRANSFORMSRCS=$(wildcard $(patsubst %,src/%/*.cpp,$(subst .,/,$(S6AR8R10))))
S6AR8R10TRANSFORMOBJS=$(S6AR8R10TRANSFORMSRCS:.cpp=.o)
           

ifeq ($(DIASTACK) , OD)
else
endif

WMOBJS += src/diameter/nasreq/NasreqAVP.o
WMOBJS += src/diameter/eap/EapAVP.o

#
# Library names
#

ifeq ($(DIASTACK), OD)
CMNLIB=lib/libdiacmnapi
else
CMNLIB=lib/libdiaapi
endif

BASELIB=lib/libbaseapi
CXDXLIB=lib/libcxdxapi
CXDX_R7LIB=lib/libcxdx_3gpp_r7_1
SHLIB=lib/libshapi
SH_R7LIB=lib/libsh_3gpp_r7_1
GQGQLIB=lib/libgqgqapi
RFROLIB=lib/librfro_3gpp_r8_1
RFROR10LIB=lib/librfro_3gpp_r10_6
DCCALIB=lib/libdccaapi
WXLIB=lib/libwxapi
RXLIB=lib/librxapi
RX_R10LIB=lib/librx_3gpp_r10_6
GXLIB=lib/libgx_3gpp_r8_15
GX_R10LIB=lib/libgx_3gpp_r10_6
GXX_R10LIB=lib/libgxx_3gpp_r10_6
SYLIB=lib/libsy_3gpp_r11_4
CUALIB=lib/libcua
GYLIB=lib/libgy_3gpp_r8_10
TXLIB=lib/libtxapi
TYLIB=lib/libtyapi
RX29214LIB=lib/librx29214api

BCGIDCCALIB=lib/libbcgidccaapi

NASREQLIB=lib/libnasreqapi
EAPLIB=lib/libeapapi

CX3GPP2LIB=lib/libcx_3gpp2api
SH3GPP2LIB=lib/libsh_3gpp2api

MIPLIB=lib/libmipapi
E2LIB=lib/libe2api
E4LIB=lib/libe4api
RQLIB=lib/librqapi
WMLIB=lib/libwmapi
WDLIB=lib/libwdapi
S6ALIB=lib/libs6a_3gpp_r8_5
S6AR10LIB=lib/libs6a_3gpp_r10_6
ROR10LIB=lib/libro_3gpp_r10_5
S6AR11LIB=lib/libs6a_3gpp_r11_5
S13LIB=lib/libs13_3gpp_r8_11
S13R10LIB=lib/libs13_3gpp_r10_6
S9LIB=lib/libs9_3gpp_r9_1
S9_R10LIB=lib/libs9_3gpp_r10_6
S9_R11LIB=lib/libs9_3gpp_r11_4
WALIB=lib/libwaapi
STALIB=lib/libstaapi
SWALIB=lib/libswaapi
S6BLIB=lib/libs6bapi
SWMLIB=lib/libswmapi
SWXLIB=lib/libswxapi
S6DLIB=lib/libs6dapi
WGLIB=lib/libwgapi
PRLIB=lib/libprapi
RELIB=lib/libreapi
GILIB=lib/libgiapi
ZHLIB=lib/libzhapi
ZNLIB=lib/libznapi
GMBLIB=lib/libgmbapi
MM10LIB=lib/libmm10api
RR_REQUESTMODELLIB=lib/librr_requestmodelapi
RR_DELEGATEDMODELLIB=lib/librr_delegatedmodelapi
A4LIB=lib/liba4api
RWLIB=lib/librwapi
RSLIB=lib/librsapi
GYREL10LIB=lib/libgy_3gpp_r10_5
GZLIB=lib/libgz_3gpp_r8_1
GZR10LIB=lib/libgz_3gpp_r10_6

ifeq ($(PRODUCT), iwf)
TRANSATELAVPLIB=lib/libtransatel_custom_avps
ROR10TRANSATELLIB=lib/libro_3gpp_r10_5_transatel
CXDXV12LIB=lib/libcxdx_3gpp_r12_2
endif

# Added for Transformer. Please note that the name provided here should match the 
# one mentioned in mag/Makefile for the transformation plugin.


#
# Targets
#
.PHONY: all clean

COMMONLIB=$(BASELIB)$(DBGSUFFIX).a $(BASELIB)$(DBGSUFFIX).so \
		  $(DCCALIB)$(DBGSUFFIX).a $(DCCALIB)$(DBGSUFFIX).so \
		  $(CUALIB)$(DBGSUFFIX).a   $(CUALIB)$(DBGSUFFIX).so \
		  $(NASREQLIB)$(DBGSUFFIX).a $(NASREQLIB)$(DBGSUFFIX).so 

ifeq ($(DIASTACK), OD)
all: $(BASELIB)$(DBGSUFFIX).a $(CXDXLIB)$(DBGSUFFIX).a \
     $(SHLIB)$(DBGSUFFIX).a  $(GQGQLIB)$(DBGSUFFIX).a \
     $(DCCALIB)$(DBGSUFFIX).a \
     $(WXLIB)$(DBGSUFFIX).a  $(RXLIB)$(DBGSUFFIX).a $(RX_R10LIB)$(DBGSUFFIX).a \
     $(GXLIB)$(DBGSUFFIX).a $(GYLIB)$(DBGSUFFIX).a $(TXLIB)$(DBGSUFFIX).a \
     $(TYLIB)$(DBGSUFFIX).a $(GX_R10LIB)$(DBGSUFFIX).a\
     $(CMNLIB)$(DBGSUFFIX).a $(GXX_R10LIB)$(DBGSUFFIX).a
else
ifeq ($(PRODUCT), iwf)
all: $(COMMONLIB) \
     $(GYLIB)$(DBGSUFFIX).a   $(GYLIB)$(DBGSUFFIX).so \
     $(S6ALIB)$(DBGSUFFIX).a $(S6ALIB)$(DBGSUFFIX).so \
     $(S6AR10LIB)$(DBGSUFFIX).a $(S6AR10LIB)$(DBGSUFFIX).so \
	 $(S6AR11LIB)$(DBGSUFFIX).a $(S6AR11LIB)$(DBGSUFFIX).so \
     $(S13LIB)$(DBGSUFFIX).a  $(S13LIB)$(DBGSUFFIX).so \
     $(S13R10LIB)$(DBGSUFFIX).a  $(S13R10LIB)$(DBGSUFFIX).so \
     $(ROR10LIB)$(DBGSUFFIX).a $(ROR10LIB)$(DBGSUFFIX).so \
	 $(GYREL10LIB)$(DBGSUFFIX).a $(GYREL10LIB)$(DBGSUFFIX).so \
	 $(TRANSATELAVPLIB)$(DBGSUFFIX).a  $(TRANSATELAVPLIB)$(DBGSUFFIX).so \
	 $(ROR10TRANSATELLIB)$(DBGSUFFIX).a  $(ROR10TRANSATELLIB)$(DBGSUFFIX).so \
	 $(CXDXV12LIB)$(DBGSUFFIX).a  $(CXDXV12LIB)$(DBGSUFFIX).so

else
all: $(COMMONLIB) \
     $(RX_R10LIB)$(DBGSUFFIX).a   $(RX_R10LIB)$(DBGSUFFIX).so \
     $(GXLIB)$(DBGSUFFIX).a   $(GXLIB)$(DBGSUFFIX).so \
     $(GX_R10LIB)$(DBGSUFFIX).a   $(GX_R10LIB)$(DBGSUFFIX).so \
     $(GXX_R10LIB)$(DBGSUFFIX).a   $(GXX_R10LIB)$(DBGSUFFIX).so \
     $(SYLIB)$(DBGSUFFIX).a   $(SYLIB)$(DBGSUFFIX).so \
     $(GYLIB)$(DBGSUFFIX).a   $(GYLIB)$(DBGSUFFIX).so \
     $(S6ALIB)$(DBGSUFFIX).a $(S6ALIB)$(DBGSUFFIX).so \
     $(S6AR10LIB)$(DBGSUFFIX).a $(S6AR10LIB)$(DBGSUFFIX).so \
     $(ROR10LIB)$(DBGSUFFIX).a $(ROR10LIB)$(DBGSUFFIX).so \
	 $(S6AR11LIB)$(DBGSUFFIX).a $(S6AR11LIB)$(DBGSUFFIX).so \
     $(S13LIB)$(DBGSUFFIX).a  $(S13LIB)$(DBGSUFFIX).so \
     $(S13R10LIB)$(DBGSUFFIX).a  $(S13R10LIB)$(DBGSUFFIX).so \
     $(S9LIB)$(DBGSUFFIX).a  $(S9LIB)$(DBGSUFFIX).so \
	 $(S9_R10LIB)$(DBGSUFFIX).a  $(S9_R10LIB)$(DBGSUFFIX).so \
	 $(S9_R11LIB)$(DBGSUFFIX).a  $(S9_R11LIB)$(DBGSUFFIX).so \
	 $(GYREL10LIB)$(DBGSUFFIX).a $(GYREL10LIB)$(DBGSUFFIX).so \
     $(GZLIB)$(DBGSUFFIX).a  $(GZLIB)$(DBGSUFFIX).so \
	 $(SH_R7LIB)$(DBGSUFFIX).a  $(SH_R7LIB)$(DBGSUFFIX).so \
	 $(SHLIB)$(DBGSUFFIX).a  $(SHLIB)$(DBGSUFFIX).so \
	 $(CXDXLIB)$(DBGSUFFIX).a  $(CXDXLIB)$(DBGSUFFIX).so \
	 $(CXDX_R7LIB)$(DBGSUFFIX).a  $(CXDX_R7LIB)$(DBGSUFFIX).so \
	 $(GZR10LIB)$(DBGSUFFIX).a  $(GZR10LIB)$(DBGSUFFIX).so 
endif
endif


ifeq ($(DIASTACK), OD)
realclean clean:
	rm -f $(BASELIB)$(DBGSUFFIX).a $(CXDXLIB)$(DBGSUFFIX).a \
              $(SHLIB)$(DBGSUFFIX).a  $(GQGQLIB)$(DBGSUFFIX).a \
              $(RFROLIB)$(DBGSUFFIX).a  $(DCCALIB)$(DBGSUFFIX).a \
              $(RFROR10LIB)$(DBGSUFFIX).a \
              $(WXLIB)$(DBGSUFFIX).a  $(RXLIB)$(DBGSUFFIX).a $(RX_R10LIB)$(DBGSUFFIX).a \
              $(GXLIB)$(DBGSUFFIX).a $(GYLIB)$(DBGSUFFIX).a $(TXLIB)$(DBGSUFFIX).a \
              $(TYLIB)$(DBGSUFFIX).a \
              $(CMNLIB)$(DBGSUFFIX).a $(GX_R10LIB)$(DBGSUFFIX).a $(GXX_R10LIB)$(DBGSUFFIX).a\
              $(CMNOBJECTS )

else
realclean clean:
	rm -f $(BASELIB)$(DBGSUFFIX).a \
              $(RFROLIB)$(DBGSUFFIX).a  $(DCCALIB)$(DBGSUFFIX).a \
              $(RFROR10LIB)$(DBGSUFFIX).a \
			  $(RX_R10LIB)$(DBGSUFFIX).a \
			  $(S9_R10LIB)$(DBGSUFFIX).a \
			  $(S9_R11LIB)$(DBGSUFFIX).a \
              $(GXLIB)$(DBGSUFFIX).a $(GYLIB)$(DBGSUFFIX).a \
              $(GX_R10LIB)$(DBGSUFFIX).a $(GXX_R10LIB)$(DBGSUFFIX).a \
              $(S6ALIB)$(DBGSUFFIX).a $(SYLIB)$(DBGSUFFIX).a \
              $(S6AR10LIB)$(DBGSUFFIX).a $(CUALIB)$(DBGSUFFIX).a \
              $(ROR10LIB)$(DBGSUFFIX).a \
			  $(S6AR11LIB)$(DBGSUFFIX).a \
              $(S13LIB)$(DBGSUFFIX).a \
			  $(S13R10LIB)$(DBGSUFFIX).a \
			  $(NASREQLIB)$(DBGSUFFIX).a \
			  $(GZLIB)$(DBGSUFFIX).a \
			  $(GZR10LIB)$(DBGSUFFIX).a \
              $(BASELIB)$(DBGSUFFIX).so \
              $(RFROLIB)$(DBGSUFFIX).so  $(DCCALIB)$(DBGSUFFIX).so \
              $(RFROR10LIB)$(DBGSUFFIX).so \
			  $(RX_R10LIB)$(DBGSUFFIX).so \
			  $(S9_R10LIB)$(DBGSUFFIX).so \
			  $(S9_R11LIB)$(DBGSUFFIX).so \
              $(GXLIB)$(DBGSUFFIX).so $(GYLIB)$(DBGSUFFIX).so \
              $(GX_R10LIB)$(DBGSUFFIX).so $(GXX_R10LIB)$(DBGSUFFIX).so \
			  $(NASREQLIB)$(DBGSUFFIX).so $(SYLIB)$(DBGSUFFIX).so \
			  $(S6ALIB)$(DBGSUFFIX).so $(CUALIB)$(DBGSUFFIX).so\
			  $(S6AR10LIB)$(DBGSUFFIX).so \
			  $(ROR10LIB)$(DBGSUFFIX).so \
			  $(S6AR11LIB)$(DBGSUFFIX).so \
              $(S13LIB)$(DBGSUFFIX).so \
              $(S13R10LIB)$(DBGSUFFIX).so \
              $(GYREL10LIB)$(DBGSUFFIX).a \
              $(GYREL10LIB)$(DBGSUFFIX).so \
              $(CMNOBJECTS) \
   			  $(S6AR8R10TRANSFORMLIB)$(DBGSUFFIX).so \
              $(S6AR8R10TRANSFORMOBJS)\
			  $(GZLIB)$(DBGSUFFIX).so \
			  $(GZR10LIB)$(DBGSUFFIX).so \
			  $(TRANSATELAVPLIB)$(DBGSUFFIX).so \
			  $(TRANSATELAVPLIB)$(DBGSUFFIX).a \
			  $(ROR10TRANSATELLIB)$(DBGSUFFIX).so \
			  $(ROR10TRANSATELLIB)$(DBGSUFFIX).a  \
			  $(CXDXV12LIB)$(DBGSUFFIX).so \
			  $(CXDXV12LIB)$(DBGSUFFIX).a  
			  
			
endif

# TODO this is only temporary, need to seperate the dependancy libs properly
# This will not work with distributed mode or to use only the codec seperately
ifeq ($(PRODUCT), iwf)
DIASTACK=-L$(IMS_ROOT)/vendors/IntelliNet/lib -L$(IMS_ROOT)/dframe/lib -lITSDFrame$(DBGSUFFIX)
ifeq ($(TLS),yes)
DIASTACK+= -ldiastackt$(DBGSUFFIX) 
else
DIASTACK+= -ldiastack$(DBGSUFFIX)
endif

$(CMNLIB)$(DBGSUFFIX).a: $(CMNOBJECTS)
	$(CXXAR) $(CXXARFLAGS) $(CMNLIB)$(DBGSUFFIX).a $(CMNOBJECTS)

$(CMNLIB)$(DBGSUFFIX).so: $(CMNOBJECTS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CMNLIB)$(DBGSUFFIX).so $(CMNOBJECTS) $(NOWHOLEARCHIVE)

$(BASELIB)$(DBGSUFFIX).a: $(BASEOBJS)
	$(CXXAR) $(CXXARFLAGS) $(BASELIB)$(DBGSUFFIX).a $(BASEOBJS) 

$(BASELIB)$(DBGSUFFIX).so: $(BASEOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(BASELIB)$(DBGSUFFIX).so $(BASEOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(DCCALIB)$(DBGSUFFIX).a: $(DCCAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(DCCALIB)$(DBGSUFFIX).a $(DCCAOBJS)

$(DCCALIB)$(DBGSUFFIX).so: $(DCCAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(DCCALIB)$(DBGSUFFIX).so $(DCCAOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(CUALIB)$(DBGSUFFIX).a: $(CUAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CUALIB)$(DBGSUFFIX).a $(CUAOBJS)

$(CUALIB)$(DBGSUFFIX).so: $(CUAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CUALIB)$(DBGSUFFIX).so $(CUAOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(GYLIB)$(DBGSUFFIX).a: $(GYOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GYLIB)$(DBGSUFFIX).a $(GYOBJS)

$(GYLIB)$(DBGSUFFIX).so: $(GYOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GYLIB)$(DBGSUFFIX).so $(GYOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(BCGIDCCALIB)$(DBGSUFFIX).a: $(BCGIDCCAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(BCGIDCCALIB)$(DBGSUFFIX).a $(BCGIDCCAOBJS)

$(BCGIDCCALIB)$(DBGSUFFIX).so: $(BCGIDCCAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(BCGIDCCALIB)$(DBGSUFFIX).so $(BCGIDCCAOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(NASREQLIB)$(DBGSUFFIX).a: $(NASREQOBJS)
	$(CXXAR) $(CXXARFLAGS) $(NASREQLIB)$(DBGSUFFIX).a $(NASREQOBJS)

$(NASREQLIB)$(DBGSUFFIX).so: $(NASREQOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(NASREQLIB)$(DBGSUFFIX).so $(NASREQOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(EAPLIB)$(DBGSUFFIX).a: $(EAPOBJS)
	$(CXXAR) $(CXXARFLAGS) $(EAPLIB)$(DBGSUFFIX).a $(EAPOBJS)

$(EAPLIB)$(DBGSUFFIX).so: $(EAPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(EAPLIB)$(DBGSUFFIX).so $(EAPOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(S6ALIB)$(DBGSUFFIX).a: $(S6AOBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6ALIB)$(DBGSUFFIX).a $(S6AOBJS)

$(S6ALIB)$(DBGSUFFIX).so: $(S6AOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6ALIB)$(DBGSUFFIX).so $(S6AOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(S6AR10LIB)$(DBGSUFFIX).a: $(S6AR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6AR10LIB)$(DBGSUFFIX).a $(S6AR10OBJS)

$(S6AR10LIB)$(DBGSUFFIX).so: $(S6AR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6AR10LIB)$(DBGSUFFIX).so $(S6AR10OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(ROR10LIB)$(DBGSUFFIX).a: $(ROR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(ROR10LIB)$(DBGSUFFIX).a $(ROR10OBJS)

$(ROR10LIB)$(DBGSUFFIX).so: $(ROR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(ROR10LIB)$(DBGSUFFIX).so $(ROR10OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(S6AR11LIB)$(DBGSUFFIX).a: $(S6AR11OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6AR11LIB)$(DBGSUFFIX).a $(S6AR11OBJS)
	
$(S6AR11LIB)$(DBGSUFFIX).so: $(S6AR11OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6AR11LIB)$(DBGSUFFIX).so $(S6AR11OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(S13LIB)$(DBGSUFFIX).a: $(S13OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S13LIB)$(DBGSUFFIX).a $(S13OBJS)

$(S13LIB)$(DBGSUFFIX).so: $(S13OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S13LIB)$(DBGSUFFIX).so $(S13OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(S13R10LIB)$(DBGSUFFIX).a: $(S13R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S13R10LIB)$(DBGSUFFIX).a $(S13R10OBJS)

$(S13R10LIB)$(DBGSUFFIX).so: $(S13R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S13R10LIB)$(DBGSUFFIX).so $(S13R10OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(GYREL10LIB)$(DBGSUFFIX).a: $(GYREL10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(GYREL10LIB)$(DBGSUFFIX).a $(GYREL10OBJS)

$(GYREL10LIB)$(DBGSUFFIX).so: $(GYREL10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GYREL10LIB)$(DBGSUFFIX).so $(GYREL10OBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(TRANSATELAVPLIB)$(DBGSUFFIX).a: $(TRANSATELAVPOBJS)
	$(CXXAR) $(CXXARFLAGS) $(TRANSATELAVPLIB)$(DBGSUFFIX).a $(TRANSATELAVPOBJS)

$(TRANSATELAVPLIB)$(DBGSUFFIX).so: $(TRANSATELAVPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(TRANSATELAVPLIB)$(DBGSUFFIX).so $(TRANSATELAVPOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)

$(ROR10TRANSATELLIB)$(DBGSUFFIX).a: $(ROR10TRANSATELOBJS)
	$(CXXAR) $(CXXARFLAGS) $(ROR10TRANSATELLIB)$(DBGSUFFIX).a $(ROR10TRANSATELOBJS)

$(ROR10TRANSATELLIB)$(DBGSUFFIX).so: $(ROR10TRANSATELOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(ROR10TRANSATELLIB)$(DBGSUFFIX).so $(ROR10TRANSATELOBJS) $(DIASTACK) $(NOWHOLEARCHIVE)
	
$(CXDXV12LIB)$(DBGSUFFIX).a: $(CXDXV12BJS)
	$(CXXAR) $(CXXARFLAGS) $(CXDXV12LIB)$(DBGSUFFIX).a $(CXDXV12BJS)

$(CXDXV12LIB)$(DBGSUFFIX).so: $(CXDXV12BJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXDXV12LIB)$(DBGSUFFIX).so $(CXDXV12BJS) $(DIASTACK) $(NOWHOLEARCHIVE)

else

$(CMNLIB)$(DBGSUFFIX).a: $(CMNOBJECTS)
	$(CXXAR) $(CXXARFLAGS) $(CMNLIB)$(DBGSUFFIX).a $(CMNOBJECTS)

$(CMNLIB)$(DBGSUFFIX).so: $(CMNOBJECTS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CMNLIB)$(DBGSUFFIX).so $(CMNOBJECTS) $(NOWHOLEARCHIVE)

$(BASELIB)$(DBGSUFFIX).a: $(BASEOBJS)
	$(CXXAR) $(CXXARFLAGS) $(BASELIB)$(DBGSUFFIX).a $(BASEOBJS) 

$(BASELIB)$(DBGSUFFIX).so: $(BASEOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(BASELIB)$(DBGSUFFIX).so $(BASEOBJS) $(NOWHOLEARCHIVE)

$(CXDXLIB)$(DBGSUFFIX).a: $(CXDXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CXDXLIB)$(DBGSUFFIX).a $(CXDXOBJS)

$(CXDXLIB)$(DBGSUFFIX).so: $(CXDXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXDXLIB)$(DBGSUFFIX).so $(CXDXOBJS) $(NOWHOLEARCHIVE)

$(SHLIB)$(DBGSUFFIX).a: $(SHOBJS)
	$(CXXAR) $(CXXARFLAGS) $(SHLIB)$(DBGSUFFIX).a $(SHOBJS)

$(SHLIB)$(DBGSUFFIX).so: $(SHOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SHLIB)$(DBGSUFFIX).so $(SHOBJS) $(NOWHOLEARCHIVE)

$(GQGQLIB)$(DBGSUFFIX).a: $(GQGQOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GQGQLIB)$(DBGSUFFIX).a $(GQGQOBJS)

$(GQGQLIB)$(DBGSUFFIX).so: $(GQGQOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GQGQLIB)$(DBGSUFFIX).so $(GQGQOBJS) $(NOWHOLEARCHIVE)

$(RFROLIB)$(DBGSUFFIX).a: $(RFROOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RFROLIB)$(DBGSUFFIX).a $(RFROOBJS)

$(RFROLIB)$(DBGSUFFIX).so: $(RFROOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RFROLIB)$(DBGSUFFIX).so $(RFROOBJS) $(NOWHOLEARCHIVE)

$(RFROR10LIB)$(DBGSUFFIX).a: $(RFROR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(RFROR10LIB)$(DBGSUFFIX).a $(RFROR10OBJS)

$(RFROR10LIB)$(DBGSUFFIX).so: $(RFROR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RFROR10LIB)$(DBGSUFFIX).so $(RFROR10OBJS) $(NOWHOLEARCHIVE)

$(DCCALIB)$(DBGSUFFIX).a: $(DCCAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(DCCALIB)$(DBGSUFFIX).a $(DCCAOBJS)

$(DCCALIB)$(DBGSUFFIX).so: $(DCCAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(DCCALIB)$(DBGSUFFIX).so $(DCCAOBJS) $(NOWHOLEARCHIVE)

$(WXLIB)$(DBGSUFFIX).a: $(WXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(WXLIB)$(DBGSUFFIX).a $(WXOBJS)

$(WXLIB)$(DBGSUFFIX).so: $(WXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(WXLIB)$(DBGSUFFIX).so $(WXOBJS) $(NOWHOLEARCHIVE)

$(RXLIB)$(DBGSUFFIX).a: $(RXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RXLIB)$(DBGSUFFIX).a $(RXOBJS)

$(RXLIB)$(DBGSUFFIX).so: $(RXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RXLIB)$(DBGSUFFIX).so $(RXOBJS) $(NOWHOLEARCHIVE)

$(RX_R10LIB)$(DBGSUFFIX).a: $(RX_R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(RX_R10LIB)$(DBGSUFFIX).a $(RX_R10OBJS)

$(RX_R10LIB)$(DBGSUFFIX).so: $(RX_R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RX_R10LIB)$(DBGSUFFIX).so $(RX_R10OBJS) $(NOWHOLEARCHIVE)

$(GXLIB)$(DBGSUFFIX).a: $(GXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GXLIB)$(DBGSUFFIX).a $(GXOBJS)

$(GXLIB)$(DBGSUFFIX).so: $(GXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GXLIB)$(DBGSUFFIX).so $(GXOBJS) $(NOWHOLEARCHIVE)

$(GX_R10LIB)$(DBGSUFFIX).a: $(GX_R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(GX_R10LIB)$(DBGSUFFIX).a $(GX_R10OBJS)

$(GX_R10LIB)$(DBGSUFFIX).so: $(GX_R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GX_R10LIB)$(DBGSUFFIX).so $(GX_R10OBJS) $(NOWHOLEARCHIVE)

$(GXX_R10LIB)$(DBGSUFFIX).a: $(GXX_R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(GXX_R10LIB)$(DBGSUFFIX).a $(GXX_R10OBJS)

$(GXX_R10LIB)$(DBGSUFFIX).so: $(GXX_R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GXX_R10LIB)$(DBGSUFFIX).so $(GXX_R10OBJS) $(NOWHOLEARCHIVE)

$(SYLIB)$(DBGSUFFIX).a: $(SYOBJS)
	$(CXXAR) $(CXXARFLAGS) $(SYLIB)$(DBGSUFFIX).a $(SYOBJS)

$(SYLIB)$(DBGSUFFIX).so: $(SYOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SYLIB)$(DBGSUFFIX).so $(SYOBJS) $(NOWHOLEARCHIVE)

$(CUALIB)$(DBGSUFFIX).a: $(CUAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(CUALIB)$(DBGSUFFIX).a $(CUAOBJS)

$(CUALIB)$(DBGSUFFIX).so: $(CUAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CUALIB)$(DBGSUFFIX).so $(CUAOBJS) $(NOWHOLEARCHIVE)

$(GYLIB)$(DBGSUFFIX).a: $(GYOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GYLIB)$(DBGSUFFIX).a $(GYOBJS)

$(GYLIB)$(DBGSUFFIX).so: $(GYOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GYLIB)$(DBGSUFFIX).so $(GYOBJS) $(NOWHOLEARCHIVE)

$(TXLIB)$(DBGSUFFIX).a: $(TXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(TXLIB)$(DBGSUFFIX).a $(TXOBJS)

$(TXLIB)$(DBGSUFFIX).so: $(TXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(TXLIB)$(DBGSUFFIX).so $(TXOBJS) $(NOWHOLEARCHIVE)

$(TYLIB)$(DBGSUFFIX).a: $(TYOBJS)
	$(CXXAR) $(CXXARFLAGS) $(TYLIB)$(DBGSUFFIX).a $(TYOBJS)

$(TYLIB)$(DBGSUFFIX).so: $(TYOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(TYLIB)$(DBGSUFFIX).so $(TYOBJS) $(NOWHOLEARCHIVE)

$(BCGIDCCALIB)$(DBGSUFFIX).a: $(BCGIDCCAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(BCGIDCCALIB)$(DBGSUFFIX).a $(BCGIDCCAOBJS)

$(BCGIDCCALIB)$(DBGSUFFIX).so: $(BCGIDCCAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(BCGIDCCALIB)$(DBGSUFFIX).so $(BCGIDCCAOBJS) $(NOWHOLEARCHIVE)

$(NASREQLIB)$(DBGSUFFIX).a: $(NASREQOBJS)
	$(CXXAR) $(CXXARFLAGS) $(NASREQLIB)$(DBGSUFFIX).a $(NASREQOBJS)

$(NASREQLIB)$(DBGSUFFIX).so: $(NASREQOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(NASREQLIB)$(DBGSUFFIX).so $(NASREQOBJS) $(NOWHOLEARCHIVE)

$(EAPLIB)$(DBGSUFFIX).a: $(EAPOBJS)
	$(CXXAR) $(CXXARFLAGS) $(EAPLIB)$(DBGSUFFIX).a $(EAPOBJS)

$(EAPLIB)$(DBGSUFFIX).so: $(EAPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(EAPLIB)$(DBGSUFFIX).so $(EAPOBJS) $(NOWHOLEARCHIVE)

$(CX3GPP2LIB)$(DBGSUFFIX).a: $(CX3GPP2OBJS)
	$(CXXAR) $(CXXARFLAGS) $(CX3GPP2LIB)$(DBGSUFFIX).a $(CX3GPP2OBJS)

$(CX3GPP2LIB)$(DBGSUFFIX).so: $(CX3GPP2OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CX3GPP2LIB)$(DBGSUFFIX).so $(CX3GPP2OBJS) $(NOWHOLEARCHIVE)

$(SH3GPP2LIB)$(DBGSUFFIX).a: $(SH3GPP2OBJS)
	$(CXXAR) $(CXXARFLAGS) $(SH3GPP2LIB)$(DBGSUFFIX).a $(SH3GPP2OBJS)

$(SH3GPP2LIB)$(DBGSUFFIX).so: $(SH3GPP2OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SH3GPP2LIB)$(DBGSUFFIX).so $(SH3GPP2OBJS) $(NOWHOLEARCHIVE)

$(MIPLIB)$(DBGSUFFIX).a: $(MIPOBJS)
	$(CXXAR) $(CXXARFLAGS) $(MIPLIB)$(DBGSUFFIX).a $(MIPOBJS)

$(MIPLIB)$(DBGSUFFIX).so: $(MIPOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(MIPLIB)$(DBGSUFFIX).so $(MIPOBJS) $(NOWHOLEARCHIVE)

$(E2LIB)$(DBGSUFFIX).a: $(E2OBJS)
	$(CXXAR) $(CXXARFLAGS) $(E2LIB)$(DBGSUFFIX).a $(E2OBJS)

$(E2LIB)$(DBGSUFFIX).so: $(E2OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(E2LIB)$(DBGSUFFIX).so $(E2OBJS) $(NOWHOLEARCHIVE)

$(E4LIB)$(DBGSUFFIX).a: $(E4OBJS)
	$(CXXAR) $(CXXARFLAGS) $(E4LIB)$(DBGSUFFIX).a $(E4OBJS)

$(E4LIB)$(DBGSUFFIX).so: $(E4OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(E4LIB)$(DBGSUFFIX).so $(E4OBJS) $(NOWHOLEARCHIVE)

$(RQLIB)$(DBGSUFFIX).a: $(RQOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RQLIB)$(DBGSUFFIX).a $(RQOBJS)

$(RQLIB)$(DBGSUFFIX).so: $(RQOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RQLIB)$(DBGSUFFIX).so $(RQOBJS) $(NOWHOLEARCHIVE)

$(WMLIB)$(DBGSUFFIX).a: $(WMOBJS)
	$(CXXAR) $(CXXARFLAGS) $(WMLIB)$(DBGSUFFIX).a $(WMOBJS)

$(WMLIB)$(DBGSUFFIX).so: $(WMOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(WMLIB)$(DBGSUFFIX).so $(WMOBJS) $(NOWHOLEARCHIVE)

$(WDLIB)$(DBGSUFFIX).a: $(WDOBJS)
	$(CXXAR) $(CXXARFLAGS) $(WDLIB)$(DBGSUFFIX).a $(WDOBJS)

$(WDLIB)$(DBGSUFFIX).so: $(WDOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(WDLIB)$(DBGSUFFIX).so $(WDOBJS) $(NOWHOLEARCHIVE)

$(S6ALIB)$(DBGSUFFIX).a: $(S6AOBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6ALIB)$(DBGSUFFIX).a $(S6AOBJS)

$(S6ALIB)$(DBGSUFFIX).so: $(S6AOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6ALIB)$(DBGSUFFIX).so $(S6AOBJS) $(NOWHOLEARCHIVE)

$(S6AR10LIB)$(DBGSUFFIX).a: $(S6AR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6AR10LIB)$(DBGSUFFIX).a $(S6AR10OBJS)

$(S6AR10LIB)$(DBGSUFFIX).so: $(S6AR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6AR10LIB)$(DBGSUFFIX).so $(S6AR10OBJS) $(NOWHOLEARCHIVE)

$(ROR10LIB)$(DBGSUFFIX).a: $(ROR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(ROR10LIB)$(DBGSUFFIX).a $(ROR10OBJS)

$(ROR10LIB)$(DBGSUFFIX).so: $(ROR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(ROR10LIB)$(DBGSUFFIX).so $(ROR10OBJS) $(NOWHOLEARCHIVE)

$(S6AR11LIB)$(DBGSUFFIX).a: $(S6AR11OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6AR11LIB)$(DBGSUFFIX).a $(S6AR11OBJS)
	
$(S6AR11LIB)$(DBGSUFFIX).so: $(S6AR11OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6AR11LIB)$(DBGSUFFIX).so $(S6AR11OBJS) $(NOWHOLEARCHIVE)

$(S13LIB)$(DBGSUFFIX).a: $(S13OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S13LIB)$(DBGSUFFIX).a $(S13OBJS)

$(S13LIB)$(DBGSUFFIX).so: $(S13OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S13LIB)$(DBGSUFFIX).so $(S13OBJS) $(NOWHOLEARCHIVE)

$(S13R10LIB)$(DBGSUFFIX).a: $(S13R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S13R10LIB)$(DBGSUFFIX).a $(S13R10OBJS)

$(S13R10LIB)$(DBGSUFFIX).so: $(S13R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S13R10LIB)$(DBGSUFFIX).so $(S13R10OBJS) $(NOWHOLEARCHIVE)

$(S9LIB)$(DBGSUFFIX).a: $(S9OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S9LIB)$(DBGSUFFIX).a $(S9OBJS)

$(S9LIB)$(DBGSUFFIX).so: $(S9OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S9LIB)$(DBGSUFFIX).so $(S9OBJS) $(NOWHOLEARCHIVE)

$(S9_R10LIB)$(DBGSUFFIX).a: $(S9_R10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S9_R10LIB)$(DBGSUFFIX).a $(S9_R10OBJS)

$(S9_R10LIB)$(DBGSUFFIX).so: $(S9_R10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S9_R10LIB)$(DBGSUFFIX).so $(S9_R10OBJS) $(NOWHOLEARCHIVE)

$(S9_R11LIB)$(DBGSUFFIX).a: $(S9_R11OBJS)
	$(CXXAR) $(CXXARFLAGS) $(S9_R11LIB)$(DBGSUFFIX).a $(S9_R11OBJS)
	
$(S9_R11LIB)$(DBGSUFFIX).so: $(S9_R11OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S9_R11LIB)$(DBGSUFFIX).so $(S9_R11OBJS) $(NOWHOLEARCHIVE)

$(RX29214LIB)$(DBGSUFFIX).a: $(RX29214OBJS)
	$(CXXAR) $(CXXARFLAGS) $(RX29214LIB)$(DBGSUFFIX).a $(RX29214OBJS)

$(RX29214LIB)$(DBGSUFFIX).so: $(RX29214OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RX29214LIB)$(DBGSUFFIX).so $(RX29214OBJS) $(NOWHOLEARCHIVE)

$(WALIB)$(DBGSUFFIX).a: $(WAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(WALIB)$(DBGSUFFIX).a $(WAOBJS)

$(WALIB)$(DBGSUFFIX).so: $(WAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(WALIB)$(DBGSUFFIX).so $(WAOBJS) $(NOWHOLEARCHIVE)

$(STALIB)$(DBGSUFFIX).a: $(STAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(STALIB)$(DBGSUFFIX).a $(STAOBJS)

$(STALIB)$(DBGSUFFIX).so: $(STAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(STALIB)$(DBGSUFFIX).so $(STAOBJS) $(NOWHOLEARCHIVE)

$(SWALIB)$(DBGSUFFIX).a: $(SWAOBJS)
	$(CXXAR) $(CXXARFLAGS) $(SWALIB)$(DBGSUFFIX).a $(SWAOBJS)

$(SWALIB)$(DBGSUFFIX).so: $(SWAOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SWALIB)$(DBGSUFFIX).so $(SWAOBJS) $(NOWHOLEARCHIVE)

$(S6BLIB)$(DBGSUFFIX).a: $(S6BOBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6BLIB)$(DBGSUFFIX).a $(S6BOBJS)

$(S6BLIB)$(DBGSUFFIX).so: $(S6BOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6BLIB)$(DBGSUFFIX).so $(S6BOBJS) $(NOWHOLEARCHIVE)

$(SWMLIB)$(DBGSUFFIX).a: $(SWMOBJS)
	$(CXXAR) $(CXXARFLAGS) $(SWMLIB)$(DBGSUFFIX).a $(SWMOBJS)

$(SWMLIB)$(DBGSUFFIX).so: $(SWMOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SWMLIB)$(DBGSUFFIX).so $(SWMOBJS) $(NOWHOLEARCHIVE)

$(SWXLIB)$(DBGSUFFIX).a: $(SWXOBJS)
	$(CXXAR) $(CXXARFLAGS) $(SWXLIB)$(DBGSUFFIX).a $(SWXOBJS)

$(SWXLIB)$(DBGSUFFIX).so: $(SWXOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SWXLIB)$(DBGSUFFIX).so $(SWXOBJS) $(NOWHOLEARCHIVE)

$(S6DLIB)$(DBGSUFFIX).a: $(S6DOBJS)
	$(CXXAR) $(CXXARFLAGS) $(S6DLIB)$(DBGSUFFIX).a $(S6DOBJS)

$(S6DLIB)$(DBGSUFFIX).so: $(S6DOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(S6DLIB)$(DBGSUFFIX).so $(S6DOBJS) $(NOWHOLEARCHIVE)

$(WGLIB)$(DBGSUFFIX).a: $(WGOBJS)
	$(CXXAR) $(CXXARFLAGS) $(WGLIB)$(DBGSUFFIX).a $(WGOBJS)

$(WGLIB)$(DBGSUFFIX).so: $(WGOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(WGLIB)$(DBGSUFFIX).so $(WGOBJS) $(NOWHOLEARCHIVE)

$(PRLIB)$(DBGSUFFIX).a: $(PROBJS)
	$(CXXAR) $(CXXARFLAGS) $(PRLIB)$(DBGSUFFIX).a $(PROBJS)

$(PRLIB)$(DBGSUFFIX).so: $(PROBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(PRLIB)$(DBGSUFFIX).so $(PROBJS) $(NOWHOLEARCHIVE)

$(RELIB)$(DBGSUFFIX).a: $(REOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RELIB)$(DBGSUFFIX).a $(REOBJS)

$(RELIB)$(DBGSUFFIX).so: $(REOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RELIB)$(DBGSUFFIX).so $(REOBJS) $(NOWHOLEARCHIVE)

$(GILIB)$(DBGSUFFIX).a: $(GIOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GILIB)$(DBGSUFFIX).a $(GIOBJS)

$(GILIB)$(DBGSUFFIX).so: $(GIOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GILIB)$(DBGSUFFIX).so $(GIOBJS) $(NOWHOLEARCHIVE)

$(ZHLIB)$(DBGSUFFIX).a: $(ZHOBJS)
	$(CXXAR) $(CXXARFLAGS) $(ZHLIB)$(DBGSUFFIX).a $(ZHOBJS)

$(ZHLIB)$(DBGSUFFIX).so: $(ZHOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(ZHLIB)$(DBGSUFFIX).so $(ZHOBJS) $(NOWHOLEARCHIVE)

$(ZNLIB)$(DBGSUFFIX).a: $(ZNOBJS)
	$(CXXAR) $(CXXARFLAGS) $(ZNLIB)$(DBGSUFFIX).a $(ZNOBJS)

$(ZNLIB)$(DBGSUFFIX).so: $(ZNOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(ZNLIB)$(DBGSUFFIX).so $(ZNOBJS) $(NOWHOLEARCHIVE)

$(GMBLIB)$(DBGSUFFIX).a: $(GMBOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GMBLIB)$(DBGSUFFIX).a $(GMBOBJS)

$(GMBLIB)$(DBGSUFFIX).so: $(GMBOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GMBLIB)$(DBGSUFFIX).so $(GMBOBJS) $(NOWHOLEARCHIVE)


$(MM10LIB)$(DBGSUFFIX).a: $(MM10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(MM10LIB)$(DBGSUFFIX).a $(MM10OBJS)

$(MM10LIB)$(DBGSUFFIX).so: $(MM10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(MM10LIB)$(DBGSUFFIX).so $(MM10OBJS) $(NOWHOLEARCHIVE)

$(RR_REQUESTMODELLIB)$(DBGSUFFIX).a: $(RR_REQUESTMODELOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RR_REQUESTMODELLIB)$(DBGSUFFIX).a $(RR_REQUESTMODELOBJS)

$(RR_REQUESTMODELLIB)$(DBGSUFFIX).so: $(RR_REQUESTMODELOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RR_REQUESTMODELLIB)$(DBGSUFFIX).so $(RR_REQUESTMODELOBJS) $(NOWHOLEARCHIVE)

$(RR_DELEGATEDMODELLIB)$(DBGSUFFIX).a: $(RR_DELEGATEDMODELOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RR_DELEGATEDMODELLIB)$(DBGSUFFIX).a $(RR_DELEGATEDMODELOBJS)

$(RR_DELEGATEDMODELLIB)$(DBGSUFFIX).so: $(RR_DELEGATEDMODELOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RR_DELEGATEDMODELLIB)$(DBGSUFFIX).so $(RR_DELEGATEDMODELOBJS) $(NOWHOLEARCHIVE)

$(A4LIB)$(DBGSUFFIX).a: $(A4OBJS)
	$(CXXAR) $(CXXARFLAGS) $(A4LIB)$(DBGSUFFIX).a $(A4OBJS)

$(A4LIB)$(DBGSUFFIX).so: $(A4OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(A4LIB)$(DBGSUFFIX).so $(A4OBJS) $(NOWHOLEARCHIVE)

$(RWLIB)$(DBGSUFFIX).a: $(RWOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RWLIB)$(DBGSUFFIX).a $(RWOBJS)

$(RWLIB)$(DBGSUFFIX).so: $(RWOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RWLIB)$(DBGSUFFIX).so $(RWOBJS) $(NOWHOLEARCHIVE)

$(RSLIB)$(DBGSUFFIX).a: $(RSOBJS)
	$(CXXAR) $(CXXARFLAGS) $(RSLIB)$(DBGSUFFIX).a $(RSOBJS)

$(RSLIB)$(DBGSUFFIX).so: $(RSOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(RSLIB)$(DBGSUFFIX).so $(RSOBJS) $(NOWHOLEARCHIVE)

$(GYREL10LIB)$(DBGSUFFIX).a: $(GYREL10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(GYREL10LIB)$(DBGSUFFIX).a $(GYREL10OBJS)

$(GYREL10LIB)$(DBGSUFFIX).so: $(GYREL10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GYREL10LIB)$(DBGSUFFIX).so $(GYREL10OBJS) $(NOWHOLEARCHIVE)

$(GZLIB)$(DBGSUFFIX).a: $(GZOBJS)
	$(CXXAR) $(CXXARFLAGS) $(GZLIB)$(DBGSUFFIX).a $(GZOBJS)

$(GZLIB)$(DBGSUFFIX).so: $(GZOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GZLIB)$(DBGSUFFIX).so $(GZOBJS) $(NOWHOLEARCHIVE)

$(GZR10LIB)$(DBGSUFFIX).a: $(GZR10OBJS)
	$(CXXAR) $(CXXARFLAGS) $(GZR10LIB)$(DBGSUFFIX).a $(GZR10OBJS)

$(GZR10LIB)$(DBGSUFFIX).so: $(GZR10OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(GZR10LIB)$(DBGSUFFIX).so $(GZR10OBJS) $(NOWHOLEARCHIVE)

$(CXDX_R7LIB)$(DBGSUFFIX).a: $(CXDX_R7OBJS)
	$(CXXAR) $(CXXARFLAGS) $(CXDX_R7LIB)$(DBGSUFFIX).a $(CXDX_R7OBJS)

$(CXDX_R7LIB)$(DBGSUFFIX).so: $(CXDX_R7OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(CXDX_R7LIB)$(DBGSUFFIX).so $(CXDX_R7OBJS) $(NOWHOLEARCHIVE)

$(SH_R7LIB)$(DBGSUFFIX).a: $(SH_R7OBJS)
	$(CXXAR) $(CXXARFLAGS) $(SH_R7LIB)$(DBGSUFFIX).a $(SH_R7OBJS)

$(SH_R7LIB)$(DBGSUFFIX).so: $(SH_R7OBJS)
	$(CXX) $(CXXSHAREDARFLAGS) $(SH_R7LIB)$(DBGSUFFIX).so $(SH_R7OBJS) $(NOWHOLEARCHIVE)

endif
