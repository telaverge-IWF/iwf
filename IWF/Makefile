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
############################################################################
#
# ID: $Id: Makefile,v 1.1.1.1.4.1.2.2.2.5.4.2.2.5.2.3.2.1 2015/02/17 06:26:03 jkchaitanya Exp $
#
# LOG: $Log: Makefile,v $
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.5.2.3.2.1  2015/02/17 06:26:03  jkchaitanya
# LOG: changes for new script included
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.5.2.3  2014/10/30 08:42:56  jkchaitanya
# LOG: including ro json
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.5.2.2  2014/10/27 11:11:06  jkchaitanya
# LOG: changes for adding ahocorasick in make file
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.5.2.1  2014/10/27 08:36:22  millayaraja
# LOG: changes for HA HotStandBy and selection criteria enhancements
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.5  2014/08/26 07:03:22  jkchaitanya
# LOG: size varification of target machine before installing iwf
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.4  2014/08/06 15:56:05  jkchaitanya
# LOG: changes for including the json file as part of ro_tsl_perf sim
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.3  2014/07/30 08:32:52  jkchaitanya
# LOG: Fix for bugs 4422 and 4266
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.2  2014/07/29 11:04:13  jkchaitanya
# LOG: changes for cap_sample to include for compilation
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2.2.1  2014/07/03 06:06:46  millayaraja
# LOG: integrated SNMP/Subagent with IWF
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.2  2014/06/03 05:28:52  jkchaitanya
# LOG: copying pre-dre script
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5.4.1  2014/05/26 11:41:15  jkchaitanya
# LOG: IWF: PRODUCT flag merge reorganizing scripts( all scripts common to IWF and DRE are moved to eAccelero)
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.5  2014/02/26 06:33:55  jkchaitanya
# LOG: changes for make file and package.sh for new tool changes
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.4  2014/02/25 07:19:49  rsanjay
# LOG: IWF HA packaging(coldstandby) changes
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.3  2014/02/14 06:09:40  jkchaitanya
# LOG: changes in packaging scripts
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.2  2014/02/13 04:56:14  jkchaitanya
# LOG: changes to copy error messages file to /opt/diametriq/iwf/config
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2.2.1  2014/02/12 10:57:19  jkchaitanya
# LOG: changes for TSL
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.2  2013/12/18 07:25:36  jkchaitanya
# LOG:  changes for IWF packaging in Make file and packaging directory
# LOG:
# LOG: Revision 1.1.1.1.4.1.2.1  2013/12/06 10:21:00  jsarvesh
# LOG: Makefile change for PerSim in test directory
# LOG:
# LOG: Revision 1.1.1.1.4.1  2013/08/21 11:56:53  jkchaitanya
# LOG: changes for New Directory capsim in test
# LOG:
# LOG: Revision 1.1.1.1  2013/01/09 16:41:35  brajappa
# LOG: Initial import
# LOG:
# LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
# LOG: Initial Draft for SSG
# LOG:
# LOG:
#
############################################################################

# components under this project
#

ifndef IWF_ROOT
    export IWF_ROOT=$(shell pwd)
endif

COMPONENTS=$(IWF_ROOT)/common/src $(IWF_ROOT)/ahocorasick $(IWF_ROOT)/src $(IWF_ROOT)/test/map/src $(IWF_ROOT)/test/capsim/src $(IWF_ROOT)/test/PerfSim/src $(IWF_ROOT)/test/cap_SampleApp/src $(IWF_ROOT)/subagent/src

.PHONY: all clean realclean test

all clean realclean test:
	@for p in $(COMPONENTS); do \
	    if [ -d $$p ]; then \
            $(MAKE) -C $$p $@ || if [ $@ = realclean ]; then $(MAKE) -C $$p clean; else exit 1; fi || exit 1; \
	    else \
	        echo make[$(MAKELEVEL)]: Ignoring \`$$p\': not a directory; \
	    fi; \
	done

S6A_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/s6a_r10/bin/
RO_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/ro_r10/bin/
RO_SIM_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/ro_r10_sim/bin/
RO_PERF_SIM_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/ro_r10_perf_sim/bin/
RO_TRANSATEL_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/ro_r10_transatel/bin/
RO_TRANSATEL_PERF_SIM_TDIR=$(IMS_ROOT)/api/c++/mtest/diameter/ro_tsl_perf/bin/
IWF_PATH=$(IWF_ROOT)
DIAMETRIQ_ROOT=/opt/diametriq
install: all
	@echo "ITS_ROOT=${ITS_ROOT}"
	@echo "IMS_ROOT=${IMS_ROOT}"
	@echo "EACC_ROOT=${EACC_ROOT}"
	@echo "IWF_ROOT=${IWF_ROOT}"
	@echo "IWF_PATH=${IWF_PATH}"
	@echo "WEBGUI_ROOT=${WEBGUI_ROOT}"
	@rm -rf ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/ca
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/crl
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/mibs
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/own
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/cache
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/mysql
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/avamgr
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/heartbeat
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/WEB-GUI
	@mkdir -p ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/utils
	@cp -urf `find ${ITS_ROOT} -name "*.so"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf `find ${VENDOR_ROOT} -name "*.so*"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf `find ${IMS_ROOT} -name "*.so"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf `find ${EACC_ROOT} -name "*.so.*"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf `find ${IWF_ROOT} -name "*.so*"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf `find ${EACC_ROOT}/3rdparty/lib -name "*"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf ${EACC_ROOT}/3rdparty/tipc-1.7.7 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	#@cp -urf ${EACC_ROOT}/3rdparty/tipc1.7.7_`uname -r` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
#	@cp -urf `find ${IWF_ROOT}/transformPlugins/ -name "*.json"` ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@cp -urf ${ITS_ROOT}/common/bin/dbc_console.ini ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${IWF_ROOT}/subagent/lib/libsubagent.so ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/lib/
	@echo "Copying iwf bin files..."
ifeq ($(DEBUG_BUILD),yes)
	@echo "DEBUG=yes"
	@cp -urf ${IWF_PATH}/bin/IWF-CCITTD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
#	@cp -urf ${IWF_PATH}/bin/IWF-COAD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${ITS_ROOT}/common/bin/DBGConsoleD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
else
	@echo "DEBUG=no"
	@cp -urf ${IWF_PATH}/bin/IWF-CCITT ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
#	@cp -urf ${IWF_PATH}/bin/IWF-COA ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${ITS_ROOT}/common/bin/DBGConsole ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
endif
	@echo "Copying eAccelero bin files..."
	@cp -urf ${EACC_ROOT}/cli/bin/debug/* ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/cmgr/bin/debug/* ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	#Avamgr related
	@cp -urf ${EACC_ROOT}/avamgr/bin/debug/avamgr ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${IWF_PATH}/bin/iwf.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${IWF_PATH}/bin/iwf_dia.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${IWF_PATH}/bin/iwf.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${IWF_PATH}/bin/iwf_itu.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${IWF_PATH}/bin/iwf_itu_2hlr.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${IWF_PATH}/subagent/config/alarm.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${IWF_PATH}/subagent/bin/subagent ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/


	@echo "Copying iwf config files..."
	@cp -urf ${EACC_ROOT}/scripts/my.cnf ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${EACC_ROOT}/cli/config/MessageResources_iwf.properties ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/MessageResources.properties

	@echo "Copying CapSim config files..."
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	#@cp -urf ${IWF_PATH}/test/capsim/bin/sampleAppCOAD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/sampleAppCCITTD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/

else
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	#@cp -urf ${IWF_PATH}/test/capsim/bin/sampleAppCOA ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/sampleAppCCITT ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
endif
	@cp -urf ${IWF_PATH}/test/capsim/bin/tcap_iwf_itu2.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/TCAP-COA-SG.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/tcap_iwf_itu.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/tcap_iwf.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/map_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/
	@cp -urf ${IWF_PATH}/test/capsim/bin/cap_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/capsim/bin/

	@echo "Copying PerfSim config files..."
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	#@cp -urf ${IWF_PATH}/test/PerfSim/bin/sampleAppCOAD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/sampleAppCCITTD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/

else
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	#@cp -urf ${IWF_PATH}/test/PerfSim/bin/sampleAppCOA ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/sampleAppCCITT ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
endif
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/tcap_iwf_itu2.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/TCAP-COA-SG.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/tcap_iwf_itu.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/tcap_iwf.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/map_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/
	@cp -urf ${IWF_PATH}/test/PerfSim/bin/cap_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/PerfSim/bin/

	@echo "Copying S6a config files..."
	@cp -urf ${S6A_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
	@cp -urf ${S6A_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
	@cp -urf ${S6A_TDIR}/s6a_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
	@cp -urf ${S6A_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${S6A_TDIR}/sampleS6a_r10AppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
else
	@cp -urf ${S6A_TDIR}/sampleS6a_r10App ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/s6a_r10/bin/
endif

	@echo "Copying RoTest config files..."
	@cp -urf ${RO_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
	@cp -urf ${RO_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
	@cp -urf ${RO_TDIR}/ro_r10_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
	@cp -urf ${RO_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${RO_TDIR}/sampleRo_r10AppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
else
	@cp -urf ${RO_TDIR}/sampleRo_r10App ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10/bin/
endif

	@echo "Copying RoSim config files..."
	@cp -urf ${RO_SIM_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
	@cp -urf ${RO_SIM_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
	@cp -urf ${RO_SIM_TDIR}/ro_r10_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
	@cp -urf ${RO_SIM_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${RO_SIM_TDIR}/sampleroAppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
else
	@cp -urf ${RO_SIM_TDIR}/sampleroApp ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_sim/bin/
endif

	@echo "Copying RoPerfSim config files..."
	@cp -urf ${RO_PERF_SIM_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
	@cp -urf ${RO_PERF_SIM_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
	@cp -urf ${RO_PERF_SIM_TDIR}/ro_r10_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
	@cp -urf ${RO_PERF_SIM_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${RO_PERF_SIM_TDIR}/sampleroAppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
else
	@cp -urf ${RO_PERF_SIM_TDIR}/sampleroApp ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_perf_sim/bin/
endif

	@echo "Copying RoTransatel config files..."
	@cp -urf ${RO_TRANSATEL_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
	@cp -urf ${RO_TRANSATEL_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
	@cp -urf ${RO_TRANSATEL_TDIR}/ro_r10_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
	@cp -urf ${RO_TRANSATEL_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${RO_TRANSATEL_TDIR}/sampleRo_r10_transatelAppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
else
	@cp -urf ${RO_TRANSATEL_TDIR}/sampleRo_r10_transatelApp ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_r10_transatel/bin/
endif

	@echo "Copying RoTransatel_PerfSim config files..."
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/demo_debug.xml.client ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/itsdiaclient_debug.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/Run.client.debug ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/ro_r10_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/sampleRo_r10_tsl_perf_simAppD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
else
	@cp -urf ${RO_TRANSATEL_PERF_SIM_TDIR}/sampleRo_r10_tsl_perf_simApp ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/ro_tsl_perf/bin/
endif

	@echo "Copying Map config files..."
ifeq ($(DEBUG_BUILD),yes)
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	#@cp -urf ${IWF_PATH}/test/map/bin/sampleAppCOAD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/sampleAppCCITTD ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
else
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG-ITU2 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/Run-SG-ITU ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	#@cp -urf ${IWF_PATH}/test/map/bin/sampleAppCOA ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/sampleAppCCITT ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
endif
	@cp -urf ${IWF_PATH}/test/map/bin/tcap_iwf_itu2.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/TCAP-COA-SG.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/tcap_iwf_itu.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/tcap_iwf.xml ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/map_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/
	@cp -urf ${IWF_PATH}/test/map/bin/cap_tools.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/test/map/bin/

	@echo "Copying AvaMgr config files..."
	@cp -urf ${EACC_ROOT}/avamgr/cfg/avamgr_iwf.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/avamgr/avamgr.json
	@echo "Copying Cmgr config files..."
	@cp -urf ${EACC_ROOT}/cmgr/configuration/mysql.cfg ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/mysql/
	@echo "Copying snmp config files..."
	@cp -urf ${IWF_PATH}/subagent/config/snmpd.conf ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@echo "Copying snmp MIB files..."
	@cp -urf ${IWF_PATH}/subagent/mibs/*.mib ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/mibs/

	@echo "Copying iwf script files..."
	@cp -urf ${EACC_ROOT}/scripts/cli/createtables_iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/createtables.sh
	@cp -urf ${EACC_ROOT}/scripts/cli/database_dump_iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/database_dump.sh
	@cp -urf ${EACC_ROOT}/scripts/cli/telnet.expect ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${EACC_ROOT}/scripts/cli/install_iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/install.sh
	@cp -urf ${EACC_ROOT}/scripts/cli/resettables.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	#avamgr
	#@cp -urf ${EACC_ROOT}/avamgr/scripts/file_replication.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	#@cp -urf ${IWF_PATH}/cache/script/*.sql ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/configCmgr.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${IWF_PATH}/package/scripts/upgrade_database.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/package_functions.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	#@cp -urf ${IWF_PATH}/statsLogger/scripts/archive_purge.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${IWF_PATH}/package/scripts/user_iwf.cnf ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${IWF_PATH}/config/replicationConfig.json ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/validate_my_cnf_file.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/tracer.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/ha/standalone_to_ha.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/ha/check_mysql_in_sync.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/querydiametriq ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/querysubscriber ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/create_user_config.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/config_cb.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/log/archive_iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/archive.sh
	@cp -urf ${EACC_ROOT}/scripts/log/archive_iwf_console.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/log/archive_trace.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/log/run_iwf_logrotate.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	#@cp -urf ${EACC_ROOT}/scripts/log/run_iwf_trace_logrotate.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/log/logrotate_iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/logrotate.sh
	@cp -urf ${EACC_ROOT}/scripts/log/iwf_logrotate ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	#@cp -urf ${EACC_ROOT}/scripts/log/iwf_trace_logrotate ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/
	@cp -urf ${EACC_ROOT}/scripts/ha/cb_flock.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/ha/couchbase_monitor.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/ha/couchbase ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin

	@echo "Copying profile file..."
	@cp -urf ${IWF_PATH}/package/iwf.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/
	@echo "Copying iwf service script..."
	@cp -urf ${EACC_ROOT}/avamgr/script/dre ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/avamgr/script/pre-dre ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/avamgr/script/iwf.env ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/uninstall_dre.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/uninstall_iwf.sh
	@cp -urf ${EACC_ROOT}/scripts/utils/package/rollback.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/update_mysql_and_localhost.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/reconfigure.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/iptables_rules ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	@cp -urf ${EACC_ROOT}/scripts/utils/package/mysql_memc_connect.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@echo "Copying Ethernet bonding and mysql heartbeat scripts..."
	@cp -urf ${EACC_ROOT}/scripts/ha/*.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@echo "Copying heartbeat config files..."
	@cp -urf ${EACC_ROOT}/scripts/heartbeat/haresources ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/heartbeat/
	@cp -urf ${EACC_ROOT}/scripts/heartbeat/ha.cf ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/heartbeat/
	@cp -urf ${EACC_ROOT}/scripts/heartbeat/authkeys ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/heartbeat/
	@echo "Copying 3rd party processes..."
	@echo "Copying incron files..."
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incrond ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incrontab ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incrontab.1 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incrontab.5 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incrond.8 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incron.conf.5 ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/incron.conf.example ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/VERSION ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/3rdparty/incron-0.5.10/install_incron.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/3rdparty/incron/
	@cp -urf ${EACC_ROOT}/scripts/ha/config_dir_file_iwf.cfg ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/config/config_dir_file.cfg
	@cp -urf ${EACC_ROOT}/scripts/ha/file_replication.sh ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/ha/ssh_Automator.tcl ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/scripts/
	@cp -urf ${EACC_ROOT}/scripts/ha/file_sync ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL}/bin/
	-@find ${RPM_BUILD_ROOT}/${DIAMETRIQ_ROOT}/${IWF_REL} -ignore_readdir_race -name CVS -type d -exec rm -rf {} \; 2>/dev/null
	@echo "You can ignore the above error!"
	@du -k ${RPM_BUILD_ROOT}| tail -1 | tr '\t' ' ' | cut -d ' ' -f 1 >~/iwf_size
	@echo "IWF_SIZE=`cat ~/iwf_size`"
