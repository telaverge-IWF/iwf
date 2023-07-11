#!/bin/bash
source /opt/diametriq/dre/scripts/package_functions.sh
if [ $# != 4 ]
then
    echo "Enter the MySQL parameters as arugments"
    echo "Usage:- ./createtable UserName Password IP-Address Port"
    exit 1
fi

LOG_INFO "" $LINENO
LOG_DEBUG "Begining of createtables.sh" $LINENO
USERNAME=$1
PASSWORD=$2
IP=$3
PORT=$4

LOG_DEBUG "Values Passed: Username=$USERNAME, Password=$PASSWORD, IP=$IP, Port=$PORT" $LINENO

MYSQL_DUMP_FILE="mysql_dump_"
DATE=`date | tr -s " " | tr " " "_"`
MYSQL_DUMP_FILE=$MYSQL_DUMP_FILE$DATE".sql"
PLOG_INFO "$MYSQL_DUMP_FILE" $LINENO

my="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT -se"
${my} "set @@global.sql_log_bin=0"
${my} "set @@session.sql_log_bin=0"
mysqldump --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ >> $MYSQL_DUMP_FILE 2>/dev/null
${my} "drop database DIAMETRIQ" 2>/dev/null
if [ $? != 0 ];then 
    LOG_INFO "DIAMETRIQ database not available to take dump" $LINENO 
else 
    LOG_INFO "DIAMETRIQ database dropped!" $LINENO 
fi

${my} "create database DIAMETRIQ"
if [ $? != 0 ];then
    PLOG_ERROR "Wrong Mysql configuration" $LINENO
    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
	${my} "set @@global.sql_log_bin=1"
	${my} "set @@session.sql_log_bin=1"
    exit 1
fi
${my} "use DIAMETRIQ"
if [ $? != 0 ];then
    PLOG_ERROR "Wrong Mysql configuration" $LINENO
    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
	${my} "set @@global.sql_log_bin=1"
	${my} "set @@session.sql_log_bin=1"
    exit 1
fi

#${my} "GRANT ALL PRIVILEGES ON DIAMETRIQ.* TO $USERNAME@'$IP' IDENTIFIED BY '$PASSWORD'"
#if [ $? != 0 ];then
#    PLOG_ERROR "Wrong Mysql configuration" $LINENO
#    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
#	${my} "set @@global.sql_log_bin=1"
#	${my} "set @@session.sql_log_bin=1"
#    exit 1
#fi

${my} "set @@global.sql_log_bin=0"
${my} "set @@session.sql_log_bin=0"
my2="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --database=DIAMETRIQ -se"

RES=`${my2} "show tables"`
LOG_DEBUG "CURRENT TABLES IN DATABASE" $LINENO
LOG_DEBUG "$RES" $LINENO
${my2} "create table LocalHostConfigT(LocalHostConfigID int not null AUTO_INCREMENT,HostName varchar(128) not null ,RealmName varchar(128) not null ,AuthLifeTime int default '400',AuthGraceTime int default '300',AuthTimeOut int default '600',AcctInterim int default '30',AcctTimeOut int default '30', primary key (LocalHostConfigID,HostName,RealmName), CONSTRAINT LOCAL_HOST UNIQUE(HostName,RealmName))"

${my2} "create table LOCAL_TRANSPORT_TB(TRANSPORT_ID int not null AUTO_INCREMENT,TRANSPORT_TYPE int not null,PUBLIC_SERVER_IP varchar(128) default null,IP_ADDRESS varchar(128) not null,PORT int not null default 0,LocalHostConfigID int not null,SecurePort int default 0,primary key(TRANSPORT_ID),foreign key (LocalHostConfigID) references LocalHostConfigT(LocalHostConfigID) on delete cascade,CONSTRAINT TRANS_TYPE UNIQUE(TRANSPORT_TYPE,IP_ADDRESS,PORT,SecurePort))"

${my2} "create table MULTIHOMING_TB(MULTIHOMING_ID int not null AUTO_INCREMENT, OTHERHOME_IPADDR varchar(128) not null, TRANSPORT_ID int not null, primary key(MULTIHOMING_ID), foreign key (TRANSPORT_ID) references LOCAL_TRANSPORT_TB(TRANSPORT_ID) on delete cascade,CONSTRAINT MULTI_HOMING_IP UNIQUE(TRANSPORT_ID,OTHERHOME_IPADDR))"

${my2} "create table DynamicDiscoveryT(RealmName varchar(128) not null,PeerHostIdentity varchar(128),primary key (RealmName))"

${my2} "create table REALM_TB(REALM_ID int not null AUTO_INCREMENT,REALM_NAME varchar(128) not null,LOCAL_ACTION int,REDIRECT_HOST_USAGE int,REDIRECT_MAX_CACHE_TIME int,PROXY_INFO_AVP boolean default '0',CONSTRAINT REALM_N UNIQUE(REALM_NAME),primary key (REALM_ID))"

${my2} "create table PeerGlobalConfigT(DiscoveryInterval int,ComponentID int not null,primary key (ComponentID))"

${my2} "create table PeerT(PeerID int not null AUTO_INCREMENT,PeerHostIdentity varchar(128) not null,RealmName varchar(128) not null,PeerIP varchar(128),PeerPort int default '0',FailoverEnable boolean default true not null,FailBackEnable boolean default false not null,TLSEnabled boolean default false not null,TransportType int default '0',AltPeerID varchar(128) ,isMate boolean default false not null,Enable int default '1',IsSupportDisconnectCause int default '0',SecurePort int default '0',primary key (PeerID), CONSTRAINT PEER_REALM UNIQUE(PeerHostIdentity,RealmName), CONSTRAINT IP_PORT UNIQUE(PeerIP,PeerPort,SecurePort))"

${my2} "create table PeerTimersT(PeerHostIdentity varchar(128) not null,RealmName varchar(128) not null,WdVal int default '30',TcVal int default '30',Eval int default '60',BusyReconnectTimer int default '1000',DoNotwantToTalkToYouTimer int default '1000',primary key (PeerHostIdentity,RealmName))"

${my2} "create table PEER_MULTIHOMING_TB(PEER_MULTIHOMING_ID int not null AUTO_INCREMENT,PEER_ID int not null,OTHERHOME_IPADDR varchar(200) not null, primary key(PEER_MULTIHOMING_ID), foreign key(PEER_ID) references PeerT(PeerID) on delete cascade, CONSTRAINT OTHER_HOME_IP UNIQUE(PEER_ID,OTHERHOME_IPADDR))"

${my2} "create table REALM_ROUTING_TB (ROUTING_ID int not null AUTO_INCREMENT,REALM_ID int not null,PEER_ID int not null,APP_ID int, VENDOR_ID int, PRIORITY int, DYNAMICALLY_DISCOVERED int,DYN_DISCOVERY_EXPIRY int,primary key(ROUTING_ID),foreign key (REALM_ID) references REALM_TB (REALM_ID) on delete cascade,foreign key (PEER_ID) references PeerT(PeerID) on delete cascade)" 

${my2} "create table DEFAULT_ROUTE_TB (REALM_ID int not null, PEER_ID int not null,foreign key (REALM_ID) references REALM_TB (REALM_ID) on delete cascade,foreign key (PEER_ID) references PeerT(PeerID) on delete cascade);"
#Dictionary Table
${my2} "create table DICTIONARY_TB(DICTIONARY_ID int not null,DICTIONARY_NAME varchar(128),INTERFACE_NAME varchar(50),RELEASE_NUMBER varchar(100),primary key (DICTIONARY_ID),APP_TYPE int default '1', CONSTRAINT INTF_RLS UNIQUE(INTERFACE_NAME,RELEASE_NUMBER))"
#Peer to Dictionary Mapping Table
${my2} "create table PEER_DICTIONARY_MAP_TB(PEER_DICTIONARY_ASSN_ID int not null AUTO_INCREMENT,PEER_ID int not null,DICTIONARY_ID int not null,primary key(PEER_DICTIONARY_ASSN_ID),CONSTRAINT PE_DICT_ID UNIQUE(PEER_ID,DICTIONARY_ID),foreign key(DICTIONARY_ID) references DICTIONARY_TB(DICTIONARY_ID) on delete cascade, foreign key(PEER_ID) references PeerT(PeerID) on delete cascade)"

${my2} "create table AvailabilityManagerConfigT(ComponentID int not
null,PingPeriodicity smallint unsigned default
'256',PingPeriodicityForArbitrator smallint unsigned default
'32',VirtualInterfaceActivationTime smallint unsigned default
'64',NumberOfConsecutivePingAckRcvFailuresFromPeer tinyint unsigned
default '3',NumberOfConsecutivePingAckRcvFailuresFromArbitrator tinyint
unsigned default '3',ProcessRestartMaxAllowedInterval smallint unsigned
default '5',ProcessRestartMaxAllowedCount tinyint unsigned default
'3',UseIpV6 boolean default 0,PrimaryVirtualIpAddress varchar(128) default
'0.0.0.0',SecondaryVirtualIpAddress varchar(128) default
'0.0.0.0',NearHopGatewayIpAddress varchar(128) default '0.0.0.0',primary key (ComponentID))"


${my2} "create table ReplicationManagerConfigT(ComponentID int not null,ReplicationState int default '1', primary key (ComponentID))"

${my2} "create table ROLE_TB (ROLE_ID int not null AUTO_INCREMENT,ROLE varchar(128),DESCRIPTION varchar(200),primary key (ROLE_ID),CONSTRAINT USER_ROLE UNIQUE(ROLE))"

${my2} "create table UserT(UserID int not null AUTO_INCREMENT,UserName varchar(128) not null,Password blob,Previlage
int,RoleID int,CreatedBy int,CreationTime DATETIME,ModifiedBy
int,ModificationTime DATETIME,Status int,primary key (UserID),foreign key(RoleID) references ROLE_TB(ROLE_ID),CONSTRAINT USER UNIQUE(UserName))"

${my2} "create table LB_ALGORITHM_TB(LB_METHOD_ID int not null AUTO_INCREMENT,LB_METHOD varchar(128) not null,DESCRIPTION varchar(200),SUPPORTED_MODULES int not null,primary key(LB_METHOD_ID))"

${my2} "create table APPLICATION_GRP_TB(APP_GRP_ID int not null AUTO_INCREMENT,APP_GRP_NAME
varchar(128) not null,PRIORITY int not null default '1',IS_HOSTED_APP_GRP boolean not
null default '1',MAX_APP_INSTANCES int not null default '8',LB_METHOD_ID int not null default '1',CREATED_BY
int,CREATION_TIME DATETIME,MODIFIED_BY int,MODIFICATION_TIME DATETIME,primary key (APP_GRP_ID),foreign key(LB_METHOD_ID) references LB_ALGORITHM_TB(LB_METHOD_ID))"

${my2} "create table ASF_CONFIGURATION_TB(ASF_CONFIG_ID int not null AUTO_INCREMENT,APP_RESPONSE_TIMEOUT int not null,primary key (ASF_CONFIG_ID))"
${my2} "create table FEATURE_TB(FEATURE_ID int not null AUTO_INCREMENT,ENABLE_ASF boolean not
null,ENABLE_ERLBF boolean not null,primary key (FEATURE_ID))"
${my2} "create table PEER_GRP_TB(PEER_GRP_ID int not null AUTO_INCREMENT,PEER_GRP_NAME varchar(50) not null,ENABLE_PCRF_BINDING boolean not null,LB_METHOD_ID int not null,
primary key (PEER_GRP_ID),foreign key(LB_METHOD_ID) references LB_ALGORITHM_TB(LB_METHOD_ID))"
${my2} "create table PEER_GRP_MAP_TB(PEER_GRP_MAP_ID int not null AUTO_INCREMENT,PEER_GRP_ID int not null, PEER_ID int not null,PEER_WEIGHT int not null,PEER_PRIORITY int not null,primary key(PEER_GRP_MAP_ID),foreign key(PEER_GRP_ID) references PEER_GRP_TB(PEER_GRP_ID) on delete cascade,foreign key(PEER_ID) references PeerT(PeerID) on delete cascade)"
${my2} "create table TRACING_TB(ENABLE_TRACING int not null,primary key(ENABLE_TRACING))"
${my2} "create table TRACING_FILTER_TB(FILTER_ID int not null AUTO_INCREMENT,FILTER_NAME varchar(250),RULE text,PRIORITY int ,EXP_DURATION int,EXP_MESSAGES int,FILTER_STATUS int default '1',LOG_LEVEL int default '6',primary key(FILTER_ID),CONSTRAINT FIL_NAME UNIQUE(FILTER_NAME))"
${my2} "create table LOGGING_CONFIG_TB(LOG_ID int not null AUTO_INCREMENT,COMPONENT_NAME varchar(20),LOG_LEVEL int default '3',LOG_CHANNEL int default '0',primary key(LOG_ID),CONSTRAINT COMP_NAME UNIQUE(COMPONENT_NAME))"

${my2} "create table TRUSTED_CA_TB(CA_ID int not null AUTO_INCREMENT,CA_FILE varchar(50) not null,CRL_FILE varchar(50), primary key(CA_ID),CONSTRAINT C_FILE UNIQUE(CA_FILE))"
${my2} "create table STACK_GEN_CONFIG(GEN_CONFIG_ID int not null AUTO_INCREMENT,PEER_IP_CHECK_ENABLE boolean not null default '1',IS_PREDICTIVE_LOOP_AVD_REQUIRED boolean not null default '0',IS_SNAPTR_SUPPORTED boolean not null default '0',primary key(GEN_CONFIG_ID))"
${my2} "create table TLS_CONFIG(TLS_CONFIG_ID int not null AUTO_INCREMENT,IDENTITY_VERIFICATION_ENABLE boolean not null default '0',CRL_VERIFICATION_ENABLE boolean not null default '0',primary key(TLS_CONFIG_ID))"
${my2} "create table CIPHER_SUITE_TB(CIPHER_SUITE_ID int not null AUTO_INCREMENT,CIPHER_SUITE_NAME varchar(50) not null,Enable boolean not null default '1',primary key(CIPHER_SUITE_ID))"
${my2} "create table SCTP_CONFIG(SCTP_CONFIG_ID int not null AUTO_INCREMENT,HEARTBEAT_ENABLE boolean not null default '1',HEARTBEAT_TIMEOUT int not null default '10000',INIT_TIMEOUT int not null default '3000',ASSOC_MAX_ATTEMPTS int not null default '16',RTO_MAX int not null default '60000',RTO_MIN int not null default '2000',RTO_INITIAL int not null default '3000',PATH_FAILURE_RETRY_COUNT int not null default '16',primary key(SCTP_CONFIG_ID))"
${my2} "create table STATIC_ROUTE_TB(STATIC_ROUTE_ID int not null AUTO_INCREMENT,PEER_ID int not null,DESTINATION_HOST varchar(200) not null, DESTINATION_REALM varchar(200) not null, APPLICATION_ID int default 0, PRIORITY int,primary key(STATIC_ROUTE_ID), foreign key(PEER_ID) references PeerT(PeerID) on delete cascade,CONSTRAINT PEER_ID_DEST_HOST UNIQUE(PEER_ID,DESTINATION_HOST,APPLICATION_ID))"

LOG_INFO "SUCCESFULLY CREATED TABLES IN DATABASE" $LINENO
echo "--------------------------------------"
echo "SUCCESFULLY CREATED TABLES IN DATABASE"
echo "--------------------------------------"
${my2} "show tables"

echo "--------------------------------"
echo "INSERTING DEFAULT ROWS IN TABLES "
echo "--------------------------------"
LOG_INFO "INSERTING DEFAULT ROWS IN TABLES" $LINENO
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(1,'round-robin','Round Robin Algorithm.',3);"
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(2,'imsi-db','Routing based on IMSI configuration.',2);"
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(3,'weighted','Weight Based distribution Algorithm.',2);"
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(4,'priority','Priority Based Algorithm.',2);"
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(5,'multicast','Multi cast Based Algorithm.',1);"
${my2} "INSERT INTO LB_ALGORITHM_TB VALUES(6,'failover','Failover Algorithm.',1);"

# Inserting default dictionary details.

${my2} "INSERT INTO DICTIONARY_TB VALUES(1,'gy_3gpp_r8_10','Gy-Interface','Release-8.10.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(2,'gy_3gpp_r10_5','Gy-Interface','Release-10.5.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(3,'gx_3gpp_r8_15','Gx-Interface','Release-8.15.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(4,'gx_3gpp_r10_6','Gx-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(5,'gxx_3gpp_r10_6','Gxx-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(6,'s6a_3gpp_r8_5','S6a-Interface','Release-8.5.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(7,'s6a_3gpp_r10_6','S6a-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(8,'s9_3gpp_r9_1','S9-Interface','Release-9.1.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(9,'s9_3gpp_r10_6','S9-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(15,'gz_3gpp_r8_1','Gz-Interface','Release-8.1.0',2);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(10,'gz_3gpp_r10_6','Gz-Interface','Release-10.6.0',2);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(11,'s13_3gpp_r8_11','S13-Interface','Release-8.11.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(12,'s13_3gpp_r10_6','S13-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(14,'rx_3gpp_r10_6','Rx-Interface','Release-10.6.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(16,'cxdx_3gpp_r7_1','CXDX-Interface','Release-7.1.0',1);"
#${my2} "INSERT INTO DICTIONARY_TB VALUES(17,'sh_3gpp_r7_1','SH-Interface','Release-7.1.0');"
${my2} "INSERT INTO DICTIONARY_TB VALUES(18,'s6a_3gpp_r11_5','S6a-Interface','Release-11.5.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(19,'s9_3gpp_r11_4','S9-Interface','Release-11.4.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(20,'sy_3gpp_r11_4','Sy-Interface','Release-11.4.0',1);"
${my2} "INSERT INTO DICTIONARY_TB VALUES(21,'cua','RFC6737-Support','Release-Initial',1);"


${my2} "insert into ROLE_TB (ROLE,DESCRIPTION) VALUES ('admin','administrator')"
${my2} "insert into ROLE_TB (ROLE,DESCRIPTION) VALUES ('operator','operator')"

${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('ASF',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('AVAMGR',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CMGR',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CLI',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('DRE',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('DTF',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('ERLBF',3)"
${my2} "insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('WEBAGENT',3)"


${my2} "insert into TRACING_TB VALUES (1)"
# Inserting default Cipher_suite_names

${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_NULL_MD5')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_NULL_SHA')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_RC4_128_SHA')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_RC4_128_MD5')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_DES_CBC_SHA')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_3DES_EDE_CBC_SHA')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_AES_128_CBC_SHA')"
${my2} "insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_AES_256_CBC_SHA')"

# Inserting default rows for Stack related Configuration with default values.
${my2} "insert into STACK_GEN_CONFIG(PEER_IP_CHECK_ENABLE,IS_PREDICTIVE_LOOP_AVD_REQUIRED) values(1,0)"
${my2} "insert into TLS_CONFIG(IDENTITY_VERIFICATION_ENABLE,CRL_VERIFICATION_ENABLE) values(0,0)"
${my2} "insert into SCTP_CONFIG(HEARTBEAT_ENABLE,HEARTBEAT_TIMEOUT,INIT_TIMEOUT,ASSOC_MAX_ATTEMPTS,RTO_MAX,RTO_MIN,RTO_INITIAL,PATH_FAILURE_RETRY_COUNT) values(1,10000,3000,16,60000,2000,3000,16)"

${my2} "INSERT INTO UserT (UserName,Password,RoleID) VALUES ('root',cast(0x707d050dd6ad530670254ad3369eca6e as binary),(select ROLE_ID from ROLE_TB where ROLE='admin'))"

${my} "set @@global.sql_log_bin=1"
${my} "set @@session.sql_log_bin=1"
echo "-------------------------------------------"
echo "SUCCESFULLY INSERTED DEFAULT ROWS IN TABLES "
echo "-------------------------------------------"
LOG_INFO "SUCCESFULLY INSERTED DEFAULT ROWS IN TABLES" $LINENO


