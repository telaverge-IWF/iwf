
export SANDBOX=`pwd`

# Exports for eAccelero related
export EACC_ROOT=$SANDBOX/eAccelero
export LD_LIBRARY_PATH=$EACC_ROOT/3rdparty/lib:$LD_LIBRARY_PATH
export PATH=$EACC_ROOT/3rdparty/bin:$PATH

#MAP-Tool
export IWF_MAP_CONFIG_FILE=$SANDBOX/test/map/bin/map_tools.json

# DRE related
export DRE_ROOT=$SANDBOX/dre

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

