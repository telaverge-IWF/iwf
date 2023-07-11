export DRE_PATH=/opt/diametriq/dre
export ISS7_CONFIG_DIR=$DRE_PATH/config/
export ASF_RE_CONFDIR=$DRE_PATH/config/asfrules
export ERLBF_RE_CONFDIR=$DRE_PATH/config/erlbfrules
export DRE_CACHE_SERVICE_CONFDIR=$DRE_PATH/config/cache
export LD_LIBRARY_PATH=$DRE_PATH/lib:$LD_LIBRARY_PATH
export DRE_MYSQL_SERVER_CONFDIR=$DRE_PATH/config/mysql
export DRE_JSON=$DRE_PATH/config/dre.json
export PATH=$DRE_PATH/bin:$PATH


chown -R tomcat:tomcat $ERLBF_RE_CONFDIR
chown -R tomcat:tomcat $ASF_RE_CONFDIR

export JRE_HOME=`rpm -ql jre | grep "/bin/java" | sed 's/bin\/java//' | awk 'NR<2{ print $1 }'`

