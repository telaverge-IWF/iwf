
export SANDBOX=$PWD

# Exports for eAccelero related
export EACC_ROOT=$SANDBOX/eAccelero
export LD_LIBRARY_PATH=$EACC_ROOT/3rdparty/lib:$LD_LIBRARY_PATH
export PATH=$EACC_ROOT/3rdparty/bin:$PATH
export MAP_IWF_CONFIG_FILE=$SANDBOX/IWF/test/map/bin/map_tools.json
export CAP_IWF_CONFIG_FILE=$SANDBOX/IWF/test/map/bin/cap_tools.json
export CAP_IWFPERF_CONFIG_FILE=$SANDBOX/IWF/test/PerfSim/bin/cap_tools.json
export S6A_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/s6a_r10/bin/s6a_tools.json
export RO_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10/bin/ro_r10_tools.json
export RO_TRANSATEL_IWF_CONFIG_FILE=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10_transatel/bin/ro_r10_tools.json
export RO_ROOT=$SANDBOX/imsdia/api/c++/mtest/diameter/ro_r10/bin/
export CAP_ROOt=$SANDBOX/IWF/test/map/bin/
export IWF_CONFIG_FILE=$SANDBOX/IWF/bin/iwf.json

 #DRE related
export PRODUCT="iwf"
export IWF_ROOT=$SANDBOX/IWF
export SSG_LOG_DIR="/var/log/iwf/"

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

# Package Related
export PRODUCT="iwf"
unset ISS7_CONFIG_DIR
export ISS7_CONFIG_DIR=$IWF_ROOT/bin
