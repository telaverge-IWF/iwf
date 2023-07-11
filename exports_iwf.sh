
#Get the version of sctp to set the flag for compilation

#SCTP_MAJOR=`rpm -qa | grep lksctp-tools- | grep -v devel | grep -v doc  | cut -d - -f 3 | cut -d . -f 1`
#SCTP_MINOR=`rpm -qa | grep lksctp-tools- | grep -v devel | grep -v doc | cut -d - -f 3 | cut -d . -f 2`
#SCTP_PATCH=`rpm -qa | grep lksctp-tools- | grep -v devel | grep -v doc | cut -d - -f 3 | cut -d . -f 3`


#GCC_MAJOR=`rpm -qa | grep libgcc- | grep -v compat | cut -d '-' -f2 | cut -d . -f 1 | tail -1`
#GCC_MINOR=`rpm -qa | grep libgcc- | grep -v compat | cut -d '-' -f2 | cut -d . -f 2 | tail -1`
#GCC_PATCH=`rpm -qa | grep libgcc- | grep -v compat | cut -d '-' -f2 | cut -d . -f 3 | tail -1`

export CVSROOT=:pserver:jkchaitanya@172.16.23.16:/export/home/.indiacvsroot
function determine_gcc_version_details
{

    if [ $GCC_MAJOR -gt 0 ];then
        if [ $GCC_MINOR -gt 3 ];then
                echo "no"
            else
                echo "yes"
            fi
        else
            echo "yes"
        fi
}


function determine_sctp_version_details
{

    if [ $SCTP_MAJOR -gt 0 ];then
        if [ $SCTP_MINOR -gt -1 ];then
            if [ $SCTP_PATCH -gt 9 ];then
                echo "no"
            else
                echo "yes"
            fi
        else
            echo "yes"
        fi
    else
        echo "yes"
    fi
}

export SANDBOX=$PWD

# Exports for eAccelero related
export PRODUCT="iwf"
export SSG_LOG_DIR="/home/krishna/sandbox/TSL_S6a_MAP/IWF/bin/"
export EACC_ROOT=$SANDBOX/eAccelero
export LD_LIBRARY_PATH=$EACC_ROOT/3rdparty/lib:$LD_LIBRARY_PATH
export PATH=$EACC_ROOT/3rdparty/bin:$PATH
export MAP_IWF_CONFIG_FILE=$SANDBOX/IWF/test/map/bin/map_tools.json
export CAP_IWF_CONFIG_FILE=$SANDBOX/IWF/test/map/bin/cap_tools.json
export S6A_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/s6a_r10/bin/s6a_tools.json
export S6A2_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/s6a_r10_mme2/bin/s6a_tools.json
export RO_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10/bin/ro_r10_tools.json
export RO_TRANSATEL_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10_transatel/bin/ro_r10_tools.json
export RO_ROOT=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10/bin/
export CAP_ROOt=$SANDBOX/IWF/test/map/bin/
#export SCTP_LIB_VERSION_LESS_THAN_1_0_10=`determine_sctp_version_details`
#export GCC_LIB_VERSION_LESS_THAN_4_3=`determine_gcc_version_details`

# DRE related
export IWF_ROOT=$SANDBOX/IWF

# Set the accelero core
export ITS_ROOT=$SANDBOX/IntelliSS7
export VENDOR_ROOT=$SANDBOX/vendors
export PLATFORM=linux
export STACK=INTELLINET
export BUILD_TYPE=INTEGRATED
export DEBUG_BUILD=yes
export LINUX64=yes
export ENALBE_DNS=yes
export platform=x86
export PROTOCOL=CCITT
#export SCCP_PROTO=CCITT
export USE_INAP_CS2=yes

# WebGUI related
export WEBGUI_ROOT=$SANDBOX/WebGUI

# Tools root directories
export IMS_TOOLS=$SANDBOX/imstools

# TLS related
export GPGERR_ROOT=/usr
export GCRYPT_ROOT=/usr
export GAA_ROOT=/usr
export GNUTLS_ROOT=/usr
export OPENSSL_ROOT=/usr

export LKSCTP_ROOT=/usr
export SNMP_ROOT=$IMS_TOOLS/net-snmp-5.4.2.1
export XERCESCROOT=$IMS_TOOLS/xerces-c-src_2_7_0
export ACE_ROOT=$IMS_TOOLS/ACE_wrappers-5.4.7
export BOOST_ROOT=$IMS_TOOLS/boost_1_33_1

# IMS Dia
export IMS_ROOT=$SANDBOX/imsdia

export PATH=$PATH:$IMS_ROOT/demo/bin:$IMS_ROOT/scripts
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/lib:$IMS_ROOT/demo/lib:../../lib

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ITS_ROOT/common/lib
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$VENDOR_ROOT/IntelliNet/lib

# For execution, add the lib path for new applications here
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/dframe/lib/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/lib/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/val/c++/lib/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/vendors/IntelliNet/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/vendors/IntelliNet/dcca/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/aim/client/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/gx/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/s6a/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/wa/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/sta/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/swa/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/api/c++/mtest/diameter/s6d/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IMS_ROOT/dtf/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EACC_ROOT/3rdparty/mysql/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$EACC_ROOT/3rdparty/mysql-connector-c++-1.1.0/driver
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ITS_ROOT/tls/lib
export LD_LIBRARY_PATH

export ISS7_CONFIG_DIR=$ITS_ROOT/common/bin/

# Rule engine path
export RE_CONFDIR=$DRE_ROOT/controller/bin/configuration
export ERLBF_RE_CONFDIR=$DRE_ROOT/ruleEngine/erlbfConfiguration
export TLS=no
export SSL_VERSION="SSL_NEW"
export RO_ROOT=$IMS_ROOT/api/c++/mtest/diameter/ro_r10_transatel/bin
export MSC_ROOT=$IWF_ROOT/test/map/bin
export CTAGS=$PWD/tags
