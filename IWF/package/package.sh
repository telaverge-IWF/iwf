#!/bin/bash
DEPENDENCY_PATH=./Dependencies
PACKAGE_ROOT=`pwd`
# Get the version and release from spec file

echo $PRODUCT
PRODUCT=iwf
if [ -z $PRODUCT ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "dre" ];then
    S_PRODUCT_NAME=dre
    PRODUCT_NAME=DRE
elif [ $PRODUCT = "iwf" ];then
    S_PRODUCT_NAME=iwf
    PRODUCT_NAME=IWF
fi

if [ -e ${S_PRODUCT_NAME}.spec ]; then
DRE_VERSION=`echo \`grep -e "^Version: " ${S_PRODUCT_NAME}.spec | cut -d' ' -f 2 | cut -d' ' -f 1\``
DRE_RELEASE=`echo \`grep -e "^Release: " ${S_PRODUCT_NAME}.spec | cut -d' ' -f 2 | cut -d' ' -f 1\``
fi

function dependency_list_check()
{

    echo "CHECK THE FOLLOWING DEPENDENCIES FOR THIS RELEASE($DRE_VERSION-$DRE_RELEASE)"
    echo "-------------------------------------------------"
    REL_DEP="${S_PRODUCT_NAME}-"$DRE_VERSION-$DRE_RELEASE"_dep.txt"
    if [ ! -e $DEPENDENCY_PATH/$REL_DEP ];then
        cp $DEPENDENCY_PATH/dep.txt $DEPENDENCY_PATH/$REL_DEP
    fi
    cat $DEPENDENCY_PATH/$REL_DEP
    echo "-------------------------------------------------"
    echo ""
    echo "Plz add any missing dependencies for this release($DRE_VERSION-$DRE_RELEASE) to $DEPENDENCY_PATH/$REL_DEP "

    read -p "Enter \"yes\" if dependencies are confirmed for this release($DRE_VERSION-$DRE_RELEASE) :Enter \"no\" to exit and edit dependency list ($DEPENDENCY_PATH/$REL_DEP): " ch
    flag=1
    while [ $flag -eq 1 ]
    do
        if [ "$ch" == "yes" ];then
            break
        elif [ "$ch" == "no" ];then
	    exit 1
 	else
            read -p "Wrong Choice! Enter Yes/No : " ch

        fi
    done
}

function set_db_upgrade_flag()
{
    read -p "Is there a database schema change between previous release and this release($DRE_VERSION-$DRE_RELEASE) : yes/no :" ch
    flag=1
    while [ $flag -eq 1 ]
    do
        if [ "$ch" == "yes" -o "$ch" == "no" ];then
            break
        else
            read -p "Wrong Choice! Enter yes/no :" ch

        fi
    done

    if [ "$ch" == "yes" ];then
        #set DB_UPGRADE=true in product.spec file
        sed -i "s/^DB_UPGRADE=.*/DB_UPGRADE=true/g" ./${S_PRODUCT_NAME}.spec
    elif [ "$ch" == "no" ];then
	#set DB_UPGRADE=false in product.spec file
        sed -i "s/^DB_UPGRADE=.*/DB_UPGRADE=false/g" ./${S_PRODUCT_NAME}.spec    
    fi

}

if [ $# -eq 1 -o $# -eq 2 ]; then
    if [ `echo $1 | grep -wi "rpm" | wc -w` -eq 1 ]; then
        if [ $# -eq 2 -a "$2" == "--defaults" ];then
 	    #default dependency list
	    echo "Creating default dependency rpm list..."
   	    REL_DEP="${S_PRODUCT_NAME}-"$DRE_VERSION-$DRE_RELEASE"_dep.txt"
            if [ ! -e $DEPENDENCY_PATH/$REL_DEP ];then
            cp $DEPENDENCY_PATH/dep.txt $DEPENDENCY_PATH/$REL_DEP
            fi
 	    
	    echo "Setting default value for DB_UPGRADE as DB_UPGRADE=false..."
	    #set default value for db upgrade macro:DB_UPGRADE=false in product.spec file
            sed -i "s/^DB_UPGRADE=.*/DB_UPGRADE=false/g" ./${S_PRODUCT_NAME}.spec
	elif [ $# -eq 2 -a "$2" != "--defaults" ];then
	    echo "Invalid argument \"$2\" passed"
	    exit 1
	else
            dependency_list_check
        #    set_db_upgrade_flag
        fi
	#update the product version and release information in the pacakage_functions.sh script
    if [ $S_PRODUCT_NAME = "dre" ];then
	    sed -i "s/^CUR_DRE_VER=.*/CUR_DRE_VER=${S_PRODUCT_NAME}-$DRE_VERSION-$DRE_RELEASE/g" $EACC_ROOT/scripts/utils/package/package_functions.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/package_functions.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/log/logrotate.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/tracer.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/install_dre.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/configCmgr.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/install.sh.in
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/validate_my_cnf_file.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/iptables_rules
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/reconfigure.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/update_mysql_and_localhost.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/querysubscriber
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/querydiametriq
        sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/mysql_memc_connect.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $DRE_ROOT/package/scripts/upgrade_database.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/utils/package/rollback.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/cli/createtables.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/cli/install.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/cli/database_dump.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/avamgr/script/dre
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/avamgr/script/pre-dre
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/3rdparty/tipc1*/install.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/ip-bond.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/cb_flock.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/check_mysql_in_sync.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/couchbase
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/couchbase_monitor.sh  
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/dump_mysql_and_load.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/file_replication.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/file_sync
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/heartbeat_ha.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/mysql_ha.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/reset_mysql_master_ip.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=dre/g" $EACC_ROOT/scripts/ha/standalone_to_ha.sh

    fi
    if [ $S_PRODUCT_NAME = "iwf" ];then
	    sed -i "s/^CUR_IWF_VER=.*/CUR_IWF_VER=${S_PRODUCT_NAME}-$DRE_VERSION-$DRE_RELEASE/g" ${EACC_ROOT}/scripts/utils/package/package_functions.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/package_functions.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/log/logrotate.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/tracer.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/install_dre.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/configCmgr.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/install.sh.in
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/validate_my_cnf_file.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/iptables_rules
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/reconfigure.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/update_mysql_and_localhost.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/querysubscriber
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/querydiametriq
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $IWF_ROOT/package/scripts/upgrade_database.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" ${EACC_ROOT}/scripts/utils/package/rollback.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/utils/package/mysql_memc_connect.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/cli/createtables.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/cli/install.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/cli/database_dump.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/avamgr/script/dre
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/avamgr/script/pre-dre
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/3rdparty/tipc1*/install.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/ip-bond.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/cb_flock.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/check_mysql_in_sync.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/couchbase
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/couchbase_monitor.sh  
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/dump_mysql_and_load.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/file_replication.sh
        sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/file_sync
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/heartbeat_ha.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/mysql_ha.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/reset_mysql_master_ip.sh
	    sed -i "s/^PRODUCT=.*/PRODUCT=iwf/g" $EACC_ROOT/scripts/ha/standalone_to_ha.sh
    fi
        #debug build and release build decisions
     if [ "$DEBUG_BUILD" == "yes" ];then
	    echo "debug build"
        if [ $S_PRODUCT_NAME = "dre" ];then
    	    sed -i "s/\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/dre_app./\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/dre_appD /g" $EACC_ROOT/avamgr/cfg/avamgr.json

            sed -i "s/libDiaOAMServer.so/libDiaOAMServerD.so/g" $DRE_ROOT/controller/bin/demo.xml.proxy
	        sed -i "s/s6a_3gpp_r8_5.*/s6a_3gpp_r8_5D\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
	        sed -i "s/s6a_3gpp_r10_6.*/s6a_3gpp_r10_6D\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
	        sed -i "s/gy_3gpp_r8_10.*/gy_3gpp_r8_10D\"/"  $DRE_ROOT/controller/bin/itsdiaproxy.xml
	        sed -i "s/gy_3gpp_r10_5.*/gy_3gpp_r10_5D\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
        fi
        if [ $S_PRODUCT_NAME = "iwf" ];then
    	    sed -i "s/\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/IWF-CCITT./\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/IWF-CCITTD /g" $EACC_ROOT/avamgr/cfg/avamgr_iwf.json

            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf_dia.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/TCAP-COA-SG.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/map/bin/Run-SG-ITU
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/TCAP-COA-SG.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/capsim/bin/Run-SG-ITU
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/TCAP-COA-SG.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/PerfSim/bin/Run-SG-ITU
            
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10AppD/sampleRo_r10App/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/demo_debug.xml.client
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroAppD/sampleroApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/demo_debug.xml.client
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroAppD/sampleroApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/demo_debug.xml.client
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_transatelAppD/sampleRo_r10_transatelApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/demo_debug.xml.client
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_tsl_perf_simAppD/sampleRo_r10_tsl_perf_simApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/demo_debug.xml.client


            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/bin/iwf_itu.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/bin/iwf.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/bin/iwf_dia.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu2.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/map/bin/TCAP-COA-SG.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITT/sampleAppCCITTD/g" $IWF_ROOT/test/map/bin/Run-SG-ITU
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu2.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/capsim/bin/TCAP-COA-SG.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITT/sampleAppCCITTD/g" $IWF_ROOT/test/capsim/bin/Run-SG-ITU
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu2.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/PerfSim/bin/TCAP-COA-SG.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu.xml
            sed -i "s/.so\"/D.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITT/sampleAppCCITTD/g" $IWF_ROOT/test/PerfSim/bin/Run-SG-ITU
            
            sed -i "s/.so\"/D.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10App/sampleRo_r10AppD/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/Run.client.debug
            sed -i "s/.so\"/D.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroApp/sampleroAppD/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/Run.client.debug
            sed -i "s/.so\"/D.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroApp/sampleroAppD/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/Run.client.debug
            sed -i "s/.so\"/D.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_transatelApp/sampleRo_r10_transatelAppD/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/Run.client.debug
            sed -i "s/.so\"/D.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_tsl_perf_simApp/sampleRo_r10_tsl_perf_simAppD/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/Run.client.debug

        fi
	elif [ "$DEBUG_BUILD" == "no" ];then
	    echo "debug build "$DEBUG_BUILD
        if [ $S_PRODUCT_NAME = "dre" ];then
	        sed -i "s/\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/dre_app./\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/dre_app /g" $EACC_ROOT/avamgr/cfg/avamgr.json

            sed -i "s/libDiaOAMServerD.so/libDiaOAMServer.so/g" $DRE_ROOT/controller/bin/demo.xml.proxy
	        sed -i "s/s6a_3gpp_r8_5.*/s6a_3gpp_r8_5\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
            sed -i "s/s6a_3gpp_r10_6.*/s6a_3gpp_r10_6\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
            sed -i "s/gy_3gpp_r8_10.*/gy_3gpp_r8_10\"/"  $DRE_ROOT/controller/bin/itsdiaproxy.xml
            sed -i "s/gy_3gpp_r10_5.*/gy_3gpp_r10_5\"/" $DRE_ROOT/controller/bin/itsdiaproxy.xml
        fi
        if [ $S_PRODUCT_NAME = "iwf" ];then
	        sed -i "s/\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/IWF-CCITT./\/opt\/diametriq\/${S_PRODUCT_NAME}\/bin\/IWF-CCITT /g" $EACC_ROOT/avamgr/cfg/avamgr_iwf.json

            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/bin/iwf_dia.xml
#sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/TCAP-COA-SG.xml
#sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/map/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/map/bin/Run-SG-ITU
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/TCAP-COA-SG.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/capsim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/capsim/bin/Run-SG-ITU
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu2.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/TCAP-COA-SG.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf_itu.xml
            sed -i "s/D.so\"/.so\"/g" $IWF_ROOT/test/PerfSim/bin/tcap_iwf.xml
            sed -i "s/sampleAppCCITTD/sampleAppCCITT/g" $IWF_ROOT/test/PerfSim/bin/Run-SG-ITU
            
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10AppD/sampleRo_r10App/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10/bin/Run.client.debug
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroAppD/sampleroApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_sim/bin/Run.client.debug
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/demo_debug.xml.client
            sed -i "s/sampleroAppD/sampleroApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_perf_sim/bin/Run.client.debug
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_transatelAppD/sampleRo_r10_transatelApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin/Run.client.debug
            sed -i "s/D.so\"/.so\"/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/demo_debug.xml.client
            sed -i "s/sampleRo_r10_tsl_perf_simAppD/sampleRo_r10_tsl_perf_simApp/g" $IMS_ROOT/api/c++/mtest/diameter/ro_tsl_perf/bin/Run.client.debug

        fi
        
	fi
        cd ~/rpmbuild/RPMS/x86_64
        rm -f *.rpm
        cd $PACKAGE_ROOT
        rpmbuild -bb ${S_PRODUCT_NAME}.spec
        if [ $? != 0 ];then
            exit 1
        fi
        echo "rpm created"
        #Size of package
        sed -i "s/^SIZE_OF_IWF=.*/SIZE_OF_IWF=`cat ~/iwf_size`/g" ${EACC_ROOT}/scripts/utils/package/install.sh.in
        rm -f ~/iwf_size
        
        mkdir -p ./bin/.${S_PRODUCT_NAME}_tmp
        mkdir -p ./bin/.${S_PRODUCT_NAME}_tmp/System
        cp ~/rpmbuild/RPMS/x86_64/${S_PRODUCT_NAME}* ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/install_dre.sh ./bin/.${S_PRODUCT_NAME}_tmp 
        cp $EACC_ROOT/scripts/utils/package/package_functions.sh ./bin/.${S_PRODUCT_NAME}_tmp
	#copy all 3rd party startup scripts
        cp $EACC_ROOT/scripts/utils/package/memcached.conf ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/apache-tomcat.conf ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/snmpd.conf ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/incrond.conf ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/mysqld.conf ./bin/.${S_PRODUCT_NAME}_tmp
        cp $EACC_ROOT/scripts/utils/package/pre-${S_PRODUCT_NAME}.conf ./bin/.${S_PRODUCT_NAME}_tmp
	#copy the upgrade database to validate whether db upgrade
	#is supported
        cp scripts/upgrade_database.sh ./bin/.${S_PRODUCT_NAME}_tmp
        cp $DEPENDENCY_PATH/$REL_DEP ./bin/.${S_PRODUCT_NAME}_tmp
	#copy the ethernet bonding scripts
        cp $EACC_ROOT/scripts/ha/ip-bond.sh ./bin/.${S_PRODUCT_NAME}_tmp
        #move all the dependencies into the folder dependencies 
        cp $DEPENDENCY_PATH/*.rpm ./bin/.${S_PRODUCT_NAME}_tmp/System
        cd ./bin/
        tar czvf ${S_PRODUCT_NAME}.tar.gz .${S_PRODUCT_NAME}_tmp/
        rm -rf .${S_PRODUCT_NAME}_tmp/

        #create a product install script with binary rpm payload
        cd $EACC_ROOT/scripts/utils/package/
        echo "creating ${S_PRODUCT_NAME}.bin..."
        ./addpayload.sh --binary $PACKAGE_ROOT/bin/${S_PRODUCT_NAME}.tar.gz
        mv install.sh ${S_PRODUCT_NAME}.bin
        chmod +x ${S_PRODUCT_NAME}.bin
        mv ${S_PRODUCT_NAME}.bin $PACKAGE_ROOT/bin/${S_PRODUCT_NAME}-$DRE_VERSION-$DRE_RELEASE.bin
        cd $PACKAGE_ROOT/bin
        rm -f ${S_PRODUCT_NAME}.tar.gz

        exit
    fi
fi

