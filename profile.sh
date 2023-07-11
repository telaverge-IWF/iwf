#export ISS7_CONFIG_DIR=$DRE_ROOT/controller/bin/
export ASF_RE_CONFDIR=$DRE_ROOT/controller/bin/configuration
#export ERLBF_RE_CONFDIR=$DRE_ROOT/controller/bin/erlbfConfiguration
export ERLBF_RE_CONFDIR=/opt/diametriq/dre/config/erlbfrls
export DRE_CACHE_SERVICE_CONFDIR=$DRE_ROOT/cache/configuration
export DRE_MYSQL_SERVER_CONFDIR=$EACC_ROOT/cmgr/configuration
export DRE_JSON=$DRE_ROOT/controller/bin/dre.json
export DRE_LOG_DIR=/var/log/dre
export DRE_STATS_DIR=/var/log/dre/stats
export PATH=$PATH:$ISS7_CONFIG_DIR:$EACC_ROOT/cmgr/bin/debug:$EACC_ROOT/cli/bin/debug
export JRE_HOME=`rpm -ql jre | grep "/bin/java" | sed 's/bin\/java//' | awk 'NR<2{ print $1 }'`
export USE_OLDER_SCTP_LIB=no
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/AcceleroCore/common/lib:$PWD/imsdia/dframe/lib:$PWD/imsdia/vendors/IntelliNet/lib:$PWD/imsdia/vendors/IntelliNet/dcca/lib:$PWD/imsdia/api/c++/mtest/diameter/app_stat/lib:$PWD/imsdia/api/c++/lib:$PWD/AcceleroCore/tls/lib:$IMS_ROOT/val/c++/lib/:$IMS_ROOT/aim/client/lib/:$EACC_ROOT/3rdparty/lib:$IMS_ROOT/dtf/lib:$EACC_ROOT/3rdparty/mysql-connector-c++-1.1.0/driver:$EACC_ROOT/3rdparty/mysql/lib:$IMS_ROOT/vendors/IntelliNet/oam/server/lib:$PWD/IWF/subagent/lib
echo $LD_LIBRARY_PATH
