#!/bin/bash

if [ $# != 4 ]
then
    echo "Enter the MySQL parameters as arugments"
    echo "Usage:- ./createtable UserName Password IP-Address Port"
    exit 1
fi

PRODUCT=iwf

source /opt/diametriq/${PRODUCT}/scripts/package_functions.sh





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
mysqldump --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --databases DIAMETRIQ >> $MYSQL_DUMP_FILE 2>/dev/null
unset_sess_repl="set @@session.sql_log_bin=0;"
${my} "${unset_sess_repl} drop database DIAMETRIQ" 2>/dev/null
if [ $? != 0 ];then 
    LOG_INFO "DIAMETRIQ database not available to take dump" $LINENO 
else 
    LOG_INFO "DIAMETRIQ database dropped!" $LINENO 
fi

${my} "${unset_sess_repl} create database DIAMETRIQ"
if [ $? != 0 ];then
    PLOG_ERROR "Wrong Mysql configuration" $LINENO
    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
    exit 1
fi
${my} "${unset_sess_repl} use DIAMETRIQ"
if [ $? != 0 ];then
    PLOG_ERROR "Wrong Mysql configuration" $LINENO
    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
    exit 1
fi

#${my} "${unset_sess_repl} GRANT ALL PRIVILEGES ON DIAMETRIQ.* TO $USERNAME@'$IP' IDENTIFIED BY '$PASSWORD'"
#if [ $? != 0 ];then
#    PLOG_ERROR "Wrong Mysql configuration" $LINENO
#    PLOG_INFO "Retry entering correct mysql configuration details!" $LINENO
#    exit 1
#fi

my2="mysql  --host=$IP --user=$USERNAME --password=$PASSWORD --port=$PORT --database=DIAMETRIQ -se"

RES=`${my2} "${unset_sess_repl} show tables"`
LOG_DEBUG "CURRENT TABLES IN DATABASE" $LINENO
LOG_DEBUG "$RES" $LINENO
${my2} "${unset_sess_repl} create table LocalHostConfigT(LocalHostConfigID int not null AUTO_INCREMENT,
            HostName varchar(128) not null ,
            RealmName varchar(128) not null ,
            AuthLifeTime int default '400',
            AuthGraceTime int default '300',
            AuthTimeOut int default '600',
            AcctInterim int default '30',
            AcctTimeOut int default '30',
            primary key (LocalHostConfigID,
                    HostName,
                    RealmName),
            CONSTRAINT LOCAL_HOST UNIQUE(HostName,
                    RealmName)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table LOCAL_TRANSPORT_TB(TRANSPORT_ID int not null AUTO_INCREMENT,
            TRANSPORT_TYPE int not null,
            PUBLIC_SERVER_IP varchar(128) default null,
            IP_ADDRESS varchar(128) not null,
            PORT int not null default 0,
            LocalHostConfigID int not null,
            SecurePort int default 0,
            primary key(TRANSPORT_ID),
            foreign key (LocalHostConfigID) references LocalHostConfigT(LocalHostConfigID) on delete cascade,
            CONSTRAINT TRANS_TYPE UNIQUE(TRANSPORT_TYPE,
                    IP_ADDRESS,
                    PORT,
                    SecurePort)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table MULTIHOMING_TB(MULTIHOMING_ID int not null AUTO_INCREMENT,
            OTHERHOME_IPADDR varchar(128) not null,
            TRANSPORT_ID int not null,
            primary key(MULTIHOMING_ID),
            foreign key (TRANSPORT_ID) references LOCAL_TRANSPORT_TB(TRANSPORT_ID) on delete cascade,
            CONSTRAINT MULTI_HOMING_IP UNIQUE(TRANSPORT_ID,
                    OTHERHOME_IPADDR)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table DynamicDiscoveryT(RealmName varchar(128) not null,
            PeerHostIdentity varchar(128),
            primary key (RealmName)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table REALM_TB(REALM_ID int not null AUTO_INCREMENT,
            REALM_NAME varchar(128) not null,
            LOCAL_ACTION int,
            REDIRECT_HOST_USAGE int,
            REDIRECT_MAX_CACHE_TIME int,
            PROXY_INFO_AVP boolean default '0',
            CONSTRAINT REALM_N UNIQUE(REALM_NAME),
            primary key (REALM_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table PeerGlobalConfigT(DiscoveryInterval int,
            ComponentID int not null,
            primary key (ComponentID))"

${my2} "${unset_sess_repl} create table PeerT(PeerID int not null AUTO_INCREMENT,
            PeerHostIdentity varchar(128) not null,
            RealmName varchar(128) not null,
            PeerIP varchar(128),
            PeerPort int default '0',
            FailoverEnable boolean default true not null,
            FailBackEnable boolean default false not null,
            TLSEnabled boolean default false not null,
            TransportType int default '0',
            AltPeerID varchar(128) ,
            isMate boolean default false not null,
            Enable int default '1',
            IsSupportDisconnectCause int default '0',
            SecurePort int default '0',
            primary key (PeerID),
            CONSTRAINT PEER_REALM UNIQUE(PeerHostIdentity,
                    RealmName),
            CONSTRAINT IP_PORT UNIQUE(PeerIP,
                    PeerPort,
                    SecurePort)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table PeerTimersT(PeerHostIdentity varchar(128) not null,
            RealmName varchar(128) not null,
            WdVal int default '30',
            TcVal int default '30',
            Eval int default '60',
            BusyReconnectTimer int default '1000',
            DoNotwantToTalkToYouTimer int default '1000',
            primary key (PeerHostIdentity,
                    RealmName)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table PEER_MULTIHOMING_TB(PEER_MULTIHOMING_ID int not null AUTO_INCREMENT,
            PEER_ID int not null,
            OTHERHOME_IPADDR varchar(200) not null,
            primary key(PEER_MULTIHOMING_ID),
            foreign key(PEER_ID) references PeerT(PeerID) on delete cascade,
            CONSTRAINT OTHER_HOME_IP UNIQUE(PEER_ID,
                    OTHERHOME_IPADDR)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table REALM_ROUTING_TB (ROUTING_ID int not null AUTO_INCREMENT,
            REALM_ID int not null,
            PEER_ID int not null,
            APP_ID int,
            VENDOR_ID int,
            PRIORITY int,
            DYNAMICALLY_DISCOVERED int,
            DYN_DISCOVERY_EXPIRY int,
            primary key(ROUTING_ID),
            foreign key (REALM_ID) references REALM_TB (REALM_ID) on delete cascade,
            foreign key (PEER_ID) references PeerT(PeerID) on delete cascade
            )ENGINE = INNODB" 

${my2} "${unset_sess_repl} create table DEFAULT_ROUTE_TB (REALM_ID int not null,
            PEER_ID int not null,
            foreign key (REALM_ID) references REALM_TB (REALM_ID) on delete cascade,
            foreign key (PEER_ID) references PeerT(PeerID) on delete cascade
            )ENGINE = INNODB;"

#Dictionary Table
${my2} "${unset_sess_repl} create table DICTIONARY_TB(DICTIONARY_ID int not null,
            DICTIONARY_NAME varchar(128),
            INTERFACE_NAME varchar(50),
            RELEASE_NUMBER varchar(100),
            primary key (DICTIONARY_ID),
            APP_TYPE int default '1', 
            CONSTRAINT INTF_RLS UNIQUE(INTERFACE_NAME,
                    RELEASE_NUMBER)
            )ENGINE = INNODB"

#Peer to Dictionary Mapping Table
${my2} "${unset_sess_repl} create table PEER_DICTIONARY_MAP_TB(PEER_DICTIONARY_ASSN_ID int not null AUTO_INCREMENT,
            PEER_ID int not null,
            DICTIONARY_ID int not null,
            primary key(PEER_DICTIONARY_ASSN_ID),
            CONSTRAINT PE_DICT_ID UNIQUE(PEER_ID,
                    DICTIONARY_ID),
            foreign key(DICTIONARY_ID) references DICTIONARY_TB(DICTIONARY_ID) on delete cascade,
            foreign key(PEER_ID) references PeerT(PeerID) on delete cascade
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table AvailabilityManagerConfigT(ComponentID int not null,
            PingPeriodicity smallint unsigned default '256',
            PingPeriodicityForArbitrator smallint unsigned default '32',
            VirtualInterfaceActivationTime smallint unsigned default '64',
            NumberOfConsecutivePingAckRcvFailuresFromPeer tinyint unsigned default '3',
            NumberOfConsecutivePingAckRcvFailuresFromArbitrator tinyint unsigned default '3',
            ProcessRestartMaxAllowedInterval smallint unsigned default '5',
            ProcessRestartMaxAllowedCount tinyint unsigned default '3',
            UseIpV6 boolean default 0,
            PrimaryVirtualIpAddress varchar(128) default '0.0.0.0',
            SecondaryVirtualIpAddress varchar(128) default '0.0.0.0',
            NearHopGatewayIpAddress varchar(128) default '0.0.0.0',
            primary key (ComponentID)
            )ENGINE = INNODB"


${my2} "${unset_sess_repl} create table ReplicationManagerConfigT(ComponentID int not null,
            ReplicationState int default '1',
            primary key (ComponentID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table ROLE_TB (ROLE_ID int not null AUTO_INCREMENT,
            ROLE varchar(128),
            DESCRIPTION varchar(200),
            primary key (ROLE_ID),
            CONSTRAINT USER_ROLE UNIQUE(ROLE)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table UserT(UserID int not null AUTO_INCREMENT,
            UserName varchar(128) not null,
            Password blob,
            Previlage int,
            RoleID int,
            CreatedBy int,
            CreationTime DATETIME,
            ModifiedBy int,
            ModificationTime DATETIME,
            Status int,
            primary key (UserID),
            foreign key(RoleID) references ROLE_TB(ROLE_ID),
            CONSTRAINT USER UNIQUE(UserName)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table LB_ALGORITHM_TB(LB_METHOD_ID int not null AUTO_INCREMENT,
            LB_METHOD varchar(128) not null,
            DESCRIPTION varchar(200),
            SUPPORTED_MODULES int not null,
            primary key(LB_METHOD_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table APPLICATION_GRP_TB(APP_GRP_ID int not null AUTO_INCREMENT,
            APP_GRP_NAME varchar(128) not null,
            PRIORITY int not null default '1',
            IS_HOSTED_APP_GRP boolean not null default '1',
            MAX_APP_INSTANCES int not null default '8',
            LB_METHOD_ID int not null default '1',
            CREATED_BY int,
            CREATION_TIME DATETIME,
            MODIFIED_BY int,
            MODIFICATION_TIME DATETIME,
            primary key (APP_GRP_ID),
            foreign key(LB_METHOD_ID) references LB_ALGORITHM_TB(LB_METHOD_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table ASF_CONFIGURATION_TB(ASF_CONFIG_ID int not null AUTO_INCREMENT,
            APP_RESPONSE_TIMEOUT int not null,
            primary key (ASF_CONFIG_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table FEATURE_TB(FEATURE_ID int not null AUTO_INCREMENT,
            ENABLE_ASF boolean not null,
            ENABLE_ERLBF boolean not null,
            primary key (FEATURE_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table PEER_GRP_TB(PEER_GRP_ID int not null AUTO_INCREMENT,
            PEER_GRP_NAME varchar(50) not null,
            ENABLE_PCRF_BINDING boolean not null,
            LB_METHOD_ID int not null, 
            primary key (PEER_GRP_ID),
            foreign key(LB_METHOD_ID) references LB_ALGORITHM_TB(LB_METHOD_ID)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table PEER_GRP_MAP_TB(PEER_GRP_MAP_ID int not null AUTO_INCREMENT,
            PEER_GRP_ID int not null,
            PEER_ID int not null,
            PEER_WEIGHT int not null,
            PEER_PRIORITY int not null,
            primary key(PEER_GRP_MAP_ID),
            foreign key(PEER_GRP_ID) references PEER_GRP_TB(PEER_GRP_ID) on delete cascade,
            foreign key(PEER_ID) references PeerT(PeerID) on delete cascade
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table TRACING_TB(ENABLE_TRACING int not null,
            primary key(ENABLE_TRACING)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table TRACING_FILTER_TB(FILTER_ID int not null AUTO_INCREMENT,
            FILTER_NAME varchar(250),
            RULE text,
            PRIORITY int ,
            EXP_DURATION int,
            EXP_MESSAGES int,
            FILTER_STATUS int default '1',
            LOG_LEVEL int default '6',
            primary key(FILTER_ID),
            CONSTRAINT FIL_NAME UNIQUE(FILTER_NAME)
            )ENGINE = INNODB"

${my2} "${unset_sess_repl} create table LOGGING_CONFIG_TB(LOG_ID int not null AUTO_INCREMENT,
            COMPONENT_NAME varchar(20),
            LOG_LEVEL int default '3',
            LOG_CHANNEL int default '0',
            primary key(LOG_ID),
            CONSTRAINT COMP_NAME UNIQUE(COMPONENT_NAME))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table TRUSTED_CA_TB(CA_ID int not null AUTO_INCREMENT,
            CA_FILE varchar(50) not null,
            CRL_FILE varchar(50),
            primary key(CA_ID),
            CONSTRAINT C_FILE UNIQUE(CA_FILE))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table STACK_GEN_CONFIG(GEN_CONFIG_ID int not null AUTO_INCREMENT,
            PEER_IP_CHECK_ENABLE boolean not null default '1',
            IS_PREDICTIVE_LOOP_AVD_REQUIRED boolean not null default '0',
            IS_SNAPTR_SUPPORTED boolean not null default '0',
            primary key(GEN_CONFIG_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table TLS_CONFIG(TLS_CONFIG_ID int not null AUTO_INCREMENT,
            IDENTITY_VERIFICATION_ENABLE boolean not null default '0',
            CRL_VERIFICATION_ENABLE boolean not null default '0',
            primary key(TLS_CONFIG_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table CIPHER_SUITE_TB(CIPHER_SUITE_ID int not null AUTO_INCREMENT,
            CIPHER_SUITE_NAME varchar(50) not null,
            Enable boolean not null default '1',
            primary key(CIPHER_SUITE_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table SCTP_CONFIG(SCTP_CONFIG_ID int not null AUTO_INCREMENT,
            HEARTBEAT_ENABLE boolean not null default '1',
            HEARTBEAT_TIMEOUT int not null default '10000',
            INIT_TIMEOUT int not null default '3000',
            ASSOC_MAX_ATTEMPTS int not null default '16',
            RTO_MAX int not null default '60000',
            RTO_MIN int not null default '2000',
            RTO_INITIAL int not null default '3000',
            PATH_FAILURE_RETRY_COUNT int not null default '16',
            primary key(SCTP_CONFIG_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table STATIC_ROUTE_TB(STATIC_ROUTE_ID int not null AUTO_INCREMENT,
            PEER_ID int not null,
            DESTINATION_HOST varchar(200) not null,
            DESTINATION_REALM varchar(200) not null,
            APPLICATION_ID int default 0,
            PRIORITY int,
            primary key(STATIC_ROUTE_ID),
            foreign key(PEER_ID) references PeerT(PeerID) on delete cascade,
            CONSTRAINT PEER_ID_DEST_HOST UNIQUE(PEER_ID,
                    DESTINATION_HOST,
                    APPLICATION_ID))ENGINE = INNODB"

#Table create query for IWF
${my2} "${unset_sess_repl} create table IWF_PROTOCOL_FAMILY_TB (
            IWF_PROTOCOL_FAMILY_ID int not null AUTO_INCREMENT,
            FAMILY_NAME varchar(20),
            CONSTRAINT PRO_NAME UNIQUE(FAMILY_NAME),
            primary key (IWF_PROTOCOL_FAMILY_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_LOCAL_SSN_TABLE(
            IWF_LOCAL_SSN_ID int not null AUTO_INCREMENT,
            SSN int not null,
            SSN_NAME varchar(20),
            CONSTRAINT SSN_NAME UNIQUE(SSN_NAME),
            primary key (IWF_LOCAL_SSN_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_LOCAL_CONFIG_TB(
            IWF_LOCAL_CONFIG_ID int not null AUTO_INCREMENT,
            IWF_PROTOCOL_FAMILY_ID int default '1',
            NI int,
            POINTCODE int,
            TCAP_INVOKE_TIMER int,
            ADDRESS_TYPE varchar(10),
            GTI int,
            TRANSLATION_TYPE int,
            NUMBERING_PLAN int,
            ENCODING_SCHEME int,
            NATURE_OF_ADDRESS_INDICATOR int,
            SELECTION_CRITERIA int,
            GT_ADDR_DIGITS varchar(20),
            USE_LOCAL_GT_FROM_CONFIG int default '1',
            USE_SCCP_CDPA_FROM_INCOMMING_MSG int default '1',
            INCLUDE_SSN int default '1',
            INCLUDE_PC int default '1',
            HOST_NAME_1 varchar(256),
            HOST_NAME_2 varchar(256),
            ASP_ID_1 int,
            ASP_ID_2 int,
            foreign key(IWF_PROTOCOL_FAMILY_ID) references IWF_PROTOCOL_FAMILY_TB(IWF_PROTOCOL_FAMILY_ID),
            primary key (IWF_LOCAL_CONFIG_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_LOCAL_SSN_MAPPING_TB(
            IWF_LOCAL_SSN_MAPPING_ID int not null AUTO_INCREMENT,
            IWF_LOCAL_CONFIG_ID int,
            IWF_LOCAL_SSN_ID int,
            foreign key (IWF_LOCAL_CONFIG_ID) references IWF_LOCAL_CONFIG_TB(IWF_LOCAL_CONFIG_ID),
            foreign key (IWF_LOCAL_SSN_ID) references IWF_LOCAL_SSN_TABLE(IWF_LOCAL_SSN_ID),
            CONSTRAINT LOCAL_MAPPING  UNIQUE(IWF_LOCAL_CONFIG_ID,
                IWF_LOCAL_SSN_ID),
            primary key (IWF_LOCAL_SSN_MAPPING_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_SCTP_PROFILE_TB(
            IWF_SIGTRAN_SCTP_PROFILE_ID int not null AUTO_INCREMENT,
            IWF_SIGTRAN_SCTP_PROFILE_NAME varchar(120),
            HEARTBEAT_ENABLE int default '1',
            HEARTBEAT_TIMEOUT int default '30000',
            INIT_TIMEOUT int default '5000',
            ASSOC_MAX_ATTEMPTS int default '10',
            MAX_ATTEMPTS int default '8',
            RTO_MAX int default '2000',
            RTO_MIN int default '60',
            RTO_INITIAL int default '2000',
            PATH_FAILURE_RETRY_COUNT int default '5',
            MAX_IN_STREAMS int default '32',
            NUM_OUT_STREAMS int default '32',
            COOKIE_LIFE int default '60',
            SEND_TIME_OUT int default '1000',
            RECEIVE_TIME_OUT int default '300',
            SHUTDOWN_TIMEOUT int default '5000',
            PMTU_TIMEOUT int default '6000',
            SEND_BUF_SIZE int default '102400',
            RECV_BUF_SIZE int default '102400',
            SACK_DELAY int default '200',
            RECONNECT_TIMEOUT int default '5000',
            CONSTRAINT SCTP_NAME UNIQUE(IWF_SIGTRAN_SCTP_PROFILE_NAME),
            primary key (IWF_SIGTRAN_SCTP_PROFILE_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SCTP_ENDPOINT_TB(
            IWF_SCTP_ENDPOINT_ID int not null AUTO_INCREMENT,
            ENDPOINT_NAME varchar(120),
            ENDPOINT_TYPE varchar(6),
            IP_ADDRESS varchar(20),
            PORT int,
            TRANSPORT_TYPE varchar(10),
            IS_CLIENT boolean default '1',
            CONSTRAINT ENDPOINT_NAME UNIQUE(ENDPOINT_NAME),
            primary key (IWF_SCTP_ENDPOINT_ID))ENGINE = INNODB"


${my2} "${unset_sess_repl} create table IWF_SIGTRAN_ASSOCIATION_TB(
            IWF_SIGTRAN_ASSOC_ID int not null AUTO_INCREMENT,
            IWF_SIGTRAN_ASSOC_NAME varchar(120),
            IWF_SIGTRAN_SCTP_PROFILE_ID int default '1',
            IWF_LOCAL_SCTP_ENDPOINT_ID int,
            IWF_REMOTE_SCTP_ENDPOINT_ID int,
            ASP_ID int,
            STATUS boolean default '0',
            foreign key (IWF_SIGTRAN_SCTP_PROFILE_ID) references IWF_SIGTRAN_SCTP_PROFILE_TB(IWF_SIGTRAN_SCTP_PROFILE_ID),
            foreign key (IWF_LOCAL_SCTP_ENDPOINT_ID) references IWF_SCTP_ENDPOINT_TB(IWF_SCTP_ENDPOINT_ID),
            foreign key (IWF_REMOTE_SCTP_ENDPOINT_ID) references IWF_SCTP_ENDPOINT_TB(IWF_SCTP_ENDPOINT_ID),
            CONSTRAINT ASSOC_NAME UNIQUE(IWF_SIGTRAN_ASSOC_NAME),
            primary key (IWF_SIGTRAN_ASSOC_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_MULTIHOMING_TB(
            IWF_SIGTRAN_MULTIHOMING_ID int not null AUTO_INCREMENT,
            IWF_SCTP_ENDPOINT_ID int,
            OTHERHOME_IPADDR varchar(20),
            foreign key (IWF_SCTP_ENDPOINT_ID) references IWF_SCTP_ENDPOINT_TB(IWF_SCTP_ENDPOINT_ID),
            primary key (IWF_SIGTRAN_MULTIHOMING_ID))ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_UAL_MANAGER_TB(
            IWF_SIGTRAN_UAL_MANAGER_ID int not null AUTO_INCREMENT,
            ACK_TIMER int,
            SIGTRAN_MODE varchar(20),
            primary key (IWF_SIGTRAN_UAL_MANAGER_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_ASSOC_SET_TB(
            IWF_SIGTRAN_ASSOC_SET_ID int not null AUTO_INCREMENT,
            IWF_SIGTRAN_ASSOC_SET_NAME varchar(120),
            NI int,
            APC int,
            ROUTING_CONTEXT int,
            TRAFFIC_MODE varchar(20),
            ASP_ID int,
            STATUS boolean default 0,
            HOME_IP varchar(120),
            IS_MEMBER int default 1,
            CONSTRAINT ASSOCSET_NAME UNIQUE(IWF_SIGTRAN_ASSOC_SET_NAME),
            primary key (IWF_SIGTRAN_ASSOC_SET_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_ASSOC_SET_MAPPING_TB(
            IWF_SIGTRAN_ASSOC_SET_MAPPING_ID int not null AUTO_INCREMENT,
            IWF_SIGTRAN_ASSOC_SET_ID int not null,
            IWF_SIGTRAN_ASSOC_ID int not null,
            IWF_SIGTRAN_ASSOC_MAPPING_ID int not null,
            foreign key (IWF_SIGTRAN_ASSOC_SET_ID) references IWF_SIGTRAN_ASSOC_SET_TB(IWF_SIGTRAN_ASSOC_SET_ID),
            foreign key (IWF_SIGTRAN_ASSOC_ID) references IWF_SIGTRAN_ASSOCIATION_TB(IWF_SIGTRAN_ASSOC_ID),
            CONSTRAINT ASSOC_ASSOCSET UNIQUE(IWF_SIGTRAN_ASSOC_SET_ID,IWF_SIGTRAN_ASSOC_ID),
            primary key (IWF_SIGTRAN_ASSOC_SET_MAPPING_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_DESTINATION_TB(
            IWF_SIGTRAN_DESTINATION_ID int not null AUTO_INCREMENT,
            DEST_NAME varchar(120),
            IWF_PROTOCOL_FAMILY_ID int,
            ADDRESS_STYLE varchar(20),
            POINTCODE int,
            NI int,
            ADDRESS_TYPE varchar(20),
            SSN int,
            GTI int,
            TRANSLATION_TYPE int,
            NUMBERING_PLAN int,
            ENCODING_SCHEME int,
            NATURE_OF_ADDRESS_INDICATOR int,
            SIO int,
            GT_ADDR_DIGITS varchar(120),
            CONSTRAINT DEST_NAME UNIQUE(DEST_NAME),
            primary key (IWF_SIGTRAN_DESTINATION_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_SIGTRAN_REMOTE_ROUTE_TB(
            IWF_SIGTRAN_REMOTE_ROUTE_ID int not null AUTO_INCREMENT,
            REMOTE_ROUTE_NAME varchar(120),
            IWF_SIGTRAN_ASSOC_SET_ID int,
            IWF_SIGTRAN_DESTINATION_ID int,
            PRIORITY int,
            foreign key (IWF_SIGTRAN_ASSOC_SET_ID) references IWF_SIGTRAN_ASSOC_SET_TB(IWF_SIGTRAN_ASSOC_SET_ID),
            foreign key (IWF_SIGTRAN_DESTINATION_ID) references IWF_SIGTRAN_DESTINATION_TB(IWF_SIGTRAN_DESTINATION_ID),
            CONSTRAINT REMOTE_NAME UNIQUE(REMOTE_ROUTE_NAME),
            primary key (IWF_SIGTRAN_REMOTE_ROUTE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_TRANSLATOR_TYPE_TB(
            IWF_TRANSLATOR_TYPE_ID int not null AUTO_INCREMENT,
            IWF_TRANSLATOR_TYPE varchar(120),
            CONSTRAINT TRANS_TYPE UNIQUE(IWF_TRANSLATOR_TYPE),
            primary key (IWF_TRANSLATOR_TYPE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_TRANSLATOR_TB(
            IWF_TRANSLATOR_ID int not null AUTO_INCREMENT,
            IWF_TRANSLATOR varchar(20),
            CONSTRAINT TRANS UNIQUE(IWF_TRANSLATOR),
            primary key (IWF_TRANSLATOR_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_TRANSLATOR_RULE_TB(
            IWF_TRANSLATOR_RULE_ID int not null AUTO_INCREMENT,
            RULE_NAME varchar(120),
            IWF_TRANSLATOR_TYPE_ID int,
            IWF_TRANSLATOR_ID int,
            DESTINATION_NAME varchar(1024),
            DESTINATION_HOST varchar(1024),
            ALTERNATE_REALM varchar(1024),
            ALTERNATE_HOST varchar(1024),
            MNC varchar(3),
            MCC varchar(4),
            APPLICATION_ID varchar(10),
            OSSN int,
            DSSN int,
            HTTP_URL varchar(30),
            WEB_SERVICE varchar(30),
            IS_RANGE bool,
            SERVICE_KEY_START_VALUE int,
            SERVICE_KEY_END_VALUE int,
            CALLING_GT_ADDR_DIGITS varchar(60),
            SERVICE_CONTEXT_ID varchar(60),
            SERVICE_KEY varchar(2048),
            IMSI_PREFIX varchar(15),
            PRO_ACTION_RULE varchar(256),
            foreign key (IWF_TRANSLATOR_TYPE_ID) references IWF_TRANSLATOR_TYPE_TB(IWF_TRANSLATOR_TYPE_ID),
            foreign key (IWF_TRANSLATOR_ID) references IWF_TRANSLATOR_TB(IWF_TRANSLATOR_ID),
            CONSTRAINT RULE UNIQUE(RULE_NAME),
            CONSTRAINT MNC_MCC_APPID UNIQUE(MNC,
                MCC,
                APPLICATION_ID),
            primary key (IWF_TRANSLATOR_RULE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_TRANSLATOR_VPLMN_ID_TB(
	        IWF_TRANSLATOR_VPLMN_ID int not null AUTO_INCREMENT,
	        VPLMN_ID varchar(25),
	        IWF_TRANSLATOR_RULE_ID int,
	        foreign key (IWF_TRANSLATOR_RULE_ID) references IWF_TRANSLATOR_RULE_TB(IWF_TRANSLATOR_RULE_ID) on delete cascade,
	        CONSTRAINT VPLMN UNIQUE(VPLMN_ID, IWF_TRANSLATOR_RULE_ID),
	        primary key (IWF_TRANSLATOR_VPLMN_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_TIMER_TB(
            IWF_TIMER_ID int not null AUTO_INCREMENT,
            IWF_TIMER_NAME varchar(125),
            IWF_TIMER_VALUE int,
            CONSTRAINT TIMER_NAME UNIQUE(IWF_TIMER_NAME),
            primary key (IWF_TIMER_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_FEATURE_TB(
            IWF_FEATURE_ID int not null AUTO_INCREMENT,
            IWF_FEATURE_NAME varchar(125),
            IWF_FEATURE_STATUS BIGINT,
            CONSTRAINT TIMER_NAME UNIQUE(IWF_FEATURE_NAME),
            primary key (IWF_FEATURE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_DCCA_GENERAL_CONFIG_TB(
            IWF_DCCA_FEATURE_ID int not null AUTO_INCREMENT,
            IWF_DCCA_FEATURE_NAME varchar(125),
            IWF_DCCA_FEATURE_VALUE int,
            CONSTRAINT DCCA_FEATURE UNIQUE(IWF_DCCA_FEATURE_NAME),
            primary key (IWF_DCCA_FEATURE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_DCCA_ENDPOINTS_TB (
            IWF_DCCA_ENDPOINT_ID int not null AUTO_INCREMENT,
            DEST_REALM_ID int not null,
            ENDPOINT_NAME varchar(128) NOT NULL,
            PRIORITY int not null default 1,
            SEND_CCRT_INDICATOR int not null default 1,
            FOREIGN KEY (DEST_REALM_ID) REFERENCES REALM_TB(REALM_ID) ON DELETE RESTRICT,
            CONSTRAINT DCCA_ENDPOINT UNIQUE(DEST_REALM_ID, ENDPOINT_NAME),
            PRIMARY KEY (IWF_DCCA_ENDPOINT_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_MAPS6A_CONFIG_TB(
            IWF_MAPS6A_CONFIG_ID int not null AUTO_INCREMENT,
            IWF_TRANSLATOR_ID int,
            HLR_NUMBER varchar(120),
            foreign key (IWF_TRANSLATOR_ID) references IWF_TRANSLATOR_TB(IWF_TRANSLATOR_ID),
            CONSTRAINT TRANS_HLR UNIQUE(IWF_TRANSLATOR_ID,
                HLR_NUMBER),
            primary key (IWF_MAPS6A_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_MAPS6A_VPLMN_ID_CONFIG_TB(
	        IWF_MAPS6A_VPLMN_CONFIG_ID int not null AUTO_INCREMENT,
	        IWF_MAPS6A_CONFIG_ID int,
	        ALLOWED_VPLMN_ID varchar(25),
	        foreign key (IWF_MAPS6A_CONFIG_ID) references IWF_MAPS6A_CONFIG_TB(IWF_MAPS6A_CONFIG_ID) on delete cascade,
	        CONSTRAINT MAPS6A_VPLMN UNIQUE(IWF_MAPS6A_CONFIG_ID, ALLOWED_VPLMN_ID),
	        primary key (IWF_MAPS6A_VPLMN_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_MAPS6A_VPLMN_ID_SGSN_MAP_TB(
	        SGSN_MAP_ID int not null AUTO_INCREMENT,
	        IWF_MAPS6A_VPLMN_CONFIG_ID int,
	        SGSN_NUMBER varchar(25),
	        foreign key (IWF_MAPS6A_VPLMN_CONFIG_ID) references IWF_MAPS6A_VPLMN_ID_CONFIG_TB(IWF_MAPS6A_VPLMN_CONFIG_ID) on delete cascade,
	        CONSTRAINT SGSN_VPLMN UNIQUE(IWF_MAPS6A_VPLMN_CONFIG_ID, SGSN_NUMBER),
	        primary key (SGSN_MAP_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_S6AMAP_CONFIG_TB(
            IWF_S6AMAP_CONFIG_ID int not null AUTO_INCREMENT,
            IWF_TRANSLATOR_ID int,
            SGSN_NUMBER varchar(120),
            ROUTING_PREFIX varchar(20),
            foreign key (IWF_TRANSLATOR_ID) references IWF_TRANSLATOR_TB(IWF_TRANSLATOR_ID),
            CONSTRAINT TRANS_SGSN UNIQUE(IWF_TRANSLATOR_ID,
                SGSN_NUMBER),
            primary key (IWF_S6AMAP_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_CAPRO_CONFIG_TB(
            IWF_CAPRO_CONFIG_ID int not null AUTO_INCREMENT,
            IWF_TRANSLATOR_ID int,
            foreign key (IWF_TRANSLATOR_ID) references IWF_TRANSLATOR_TB(IWF_TRANSLATOR_ID),
            CONSTRAINT TRANS UNIQUE(IWF_TRANSLATOR_ID),
            primary key (IWF_CAPRO_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_S6AMAP_SGSN_ADDR_MAP(
            SGSN_ADDR_MAP_ID int not null AUTO_INCREMENT,
            IWF_S6AMAP_CONFIG_ID int,
            ORIGIN_HOST varchar(767),
            IPADDRESS varchar(20),
            foreign key (IWF_S6AMAP_CONFIG_ID) references IWF_S6AMAP_CONFIG_TB(IWF_S6AMAP_CONFIG_ID),
            CONSTRAINT ORIGIN UNIQUE(ORIGIN_HOST),
            primary key (SGSN_ADDR_MAP_ID)

)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table IWF_S6AMAP_SGSN_PREFIX_MAP(
            SGSN_PREFIX_MAP_ID int not null AUTO_INCREMENT,
            IWF_S6AMAP_CONFIG_ID int,
            VPLMN_ID varchar(20),
            SGSN_PREFIX varchar(20),
            foreign key (IWF_S6AMAP_CONFIG_ID) references IWF_S6AMAP_CONFIG_TB(IWF_S6AMAP_CONFIG_ID),
            CONSTRAINT ORIGIN UNIQUE(VPLMN_ID),
            primary key (SGSN_PREFIX_MAP_ID)

)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table CAPRO_IDP_CONFIG_TB(
            CAPRO_IDP_CONFIG_ID int not null AUTO_INCREMENT,
            CAPRO_CONFIG_ID int,
            NODE_FUNCTIONALITY int,
            SIP_METHOD varchar(20),
            ORIGINATING_TOI varchar(20),
            TERMINATING_TOI varchar(20),
            SERVICE_CONTEXT_ID varchar(30),
            CAUSE_CODE varchar(20),
            MSC_SERVICE_SPECIFIC_TYPE int,
            GMSC_SERVICE_SPECIFIC_TYPE int,
            CPC_SERVICE_SPECIFIC_TYPE int,
            MULTIPLE_SERVICES_INDICATOR int,
            foreign key (CAPRO_CONFIG_ID) references IWF_CAPRO_CONFIG_TB(IWF_CAPRO_CONFIG_ID),
            CONSTRAINT CAPRO_ID UNIQUE(CAPRO_CONFIG_ID),
            primary key (CAPRO_IDP_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table CAPRO_IDPSMS_CONFIG_TB(
            CAPRO_IDPSMS_CONFIG_ID int not null AUTO_INCREMENT,
            CAPRO_CONFIG_ID int,
            SMS_NODE int,
            CLIENT_ADDRESS varchar(20),
            ORIGINATOR_SCCP_ADDRESS varchar(20),
            REPLY_PATH_REQUESTED int,
            MSC_SERVICE_SPECIFIC_TYPE int,
            SGSN_SERVICE_SPECIFIC_TYPE int,
            SERVICE_CONTEXT_ID varchar(30),
            foreign key (CAPRO_CONFIG_ID) references IWF_CAPRO_CONFIG_TB(IWF_CAPRO_CONFIG_ID),
            CONSTRAINT CAPRO_ID UNIQUE(CAPRO_CONFIG_ID),
            primary key (CAPRO_IDPSMS_CONFIG_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table EXT_TELESERVICE_TO_SERVICE_ID_MAP_TB(
            EXT_TELESERVICE_TO_SERVICE_ID_MAP_ID int not null AUTO_INCREMENT,
            CAPRO_IDP_CONFIG_ID int,
            EXT_TELESERVICE int,
            SERVICE_ID int,
            foreign key (CAPRO_IDP_CONFIG_ID) references CAPRO_IDP_CONFIG_TB(CAPRO_IDP_CONFIG_ID),
            CONSTRAINT TELESERVICE UNIQUE(EXT_TELESERVICE),
            primary key (EXT_TELESERVICE_TO_SERVICE_ID_MAP_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl} create table EXT_BEARERSERVICE_TO_SERVICE_ID_MAP_TB(
            EXT_BEARERSERVICE_TO_SERVICE_ID_MAP_ID int not null AUTO_INCREMENT,
            CAPRO_IDP_CONFIG_ID int,
            EXT_BEARERSERVICE int,
            SERVICE_ID int,
            foreign key (CAPRO_IDP_CONFIG_ID) references CAPRO_IDP_CONFIG_TB(CAPRO_IDP_CONFIG_ID),
            CONSTRAINT BEARERSERVICE UNIQUE(EXT_BEARERSERVICE),
            primary key (EXT_BEARERSERVICE_TO_SERVICE_ID_MAP_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_PROTOCOL_TB(
			IWF_PROTOCOL_ID int not null AUTO_INCREMENT,
			IWF_PROTOCOL_NAME varchar (128),
			CONSTRAINT PROTOCOLID UNIQUE(IWF_PROTOCOL_NAME),
			primary key (IWF_PROTOCOL_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_PROTOCOL_ACTION_RULE_TB(
			IWF_PROTOCOL_ACTION_RULE_ID int not null AUTO_INCREMENT,
			ACTION_RULE_NAME varchar(256),
			PROTOCOL_ID int,
			ACTION_ID int,
			foreign key (PROTOCOL_ID) references IWF_PROTOCOL_TB(IWF_PROTOCOL_ID),
			CONSTRAINT PROTOCOLRULE UNIQUE(ACTION_RULE_NAME),
			primary key (IWF_PROTOCOL_ACTION_RULE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_CALL_SCENARIO_TB(
			IWF_CALL_SCENARIO_ID int not null AUTO_INCREMENT,
			CALL_SCENARIO varchar(256),
			CONSTRAINT SCENARIO UNIQUE(CALL_SCENARIO),
			primary key (IWF_CALL_SCENARIO_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_CALL_SCENARIO_MAPPING_TB(
			IWF_CALL_SCENARIO_MAPPING_ID int not null AUTO_INCREMENT,
			IWF_PROTOCOL_ACTION_RULE_ID int,
			IWF_CALL_SCENARIO_ID int,
			foreign key (IWF_PROTOCOL_ACTION_RULE_ID) references IWF_PROTOCOL_ACTION_RULE_TB(IWF_PROTOCOL_ACTION_RULE_ID) on delete cascade,
			foreign key (IWF_CALL_SCENARIO_ID) references IWF_CALL_SCENARIO_TB(IWF_CALL_SCENARIO_ID) on delete cascade,
			CONSTRAINT CALLSCENARIO UNIQUE(IWF_PROTOCOL_ACTION_RULE_ID, IWF_CALL_SCENARIO_ID),
			primary key (IWF_CALL_SCENARIO_MAPPING_ID)
)ENGINE = INNODB"
			
${my2} "${unset_sess_repl}create table IWF_EVENT_TYPE_TB(
			IWF_EVENT_TYPE_ID int not null AUTO_INCREMENT,
			IWF_EVENT_TYPE_NAME varchar(128),
			primary key (IWF_EVENT_TYPE_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_EVENT_TYPE_MAPPING_TB(
            IWF_EVENT_TYPE_MAPPING_ID int not null AUTO_INCREMENT,
            IWF_CALL_SCENARIO_MAPPING_ID int,
            IWF_EVENT_TYPE_ID int,
            foreign key (IWF_CALL_SCENARIO_MAPPING_ID) references IWF_CALL_SCENARIO_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID) on delete cascade,
			foreign key (IWF_EVENT_TYPE_ID) references IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_ID) on delete cascade,
            CONSTRAINT EVENTTYPEMAPPING UNIQUE(IWF_CALL_SCENARIO_MAPPING_ID, IWF_EVENT_TYPE_ID),
            primary key (IWF_EVENT_TYPE_MAPPING_ID)
)ENGINE = INNODB"

${my2} "${unset_sess_repl}create table IWF_EVENT_TYPE_DETAILS_TB(
			IWF_EVENT_TYPE_DETAILS_ID int not null AUTO_INCREMENT,
			IWF_EVENT_TYPE_MAPPING_ID int,
			MONITOR_MODE varchar(128),
			LEG_ID varchar(128),
            foreign key (IWF_EVENT_TYPE_MAPPING_ID) references IWF_EVENT_TYPE_MAPPING_TB(IWF_EVENT_TYPE_MAPPING_ID) on delete cascade,
			CONSTRAINT EVENTDETAILS UNIQUE(IWF_EVENT_TYPE_MAPPING_ID, MONITOR_MODE, LEG_ID),  
			primary key (IWF_EVENT_TYPE_DETAILS_ID)
)ENGINE = INNODB"


LOG_INFO "SUCCESFULLY CREATED TABLES IN DATABASE" $LINENO
echo "--------------------------------------"
echo "SUCCESFULLY CREATED TABLES IN DATABASE"
echo "--------------------------------------"
${my2} "${unset_sess_repl} show tables"

echo "--------------------------------"
echo "INSERTING DEFAULT ROWS IN TABLES "
echo "--------------------------------"
LOG_INFO "INSERTING DEFAULT ROWS IN TABLES" $LINENO
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(1,'round-robin','Round Robin Algorithm.',3);"
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(2,'imsi-db','Routing based on IMSI configuration.',2);"
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(3,'weighted','Weight Based distribution Algorithm.',2);"
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(4,'priority','Priority Based Algorithm.',2);"
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(5,'multicast','Multi cast Based Algorithm.',1);"
${my2} "${unset_sess_repl} INSERT INTO LB_ALGORITHM_TB VALUES(6,'failover','Failover Algorithm.',1);"

# Inserting default dictionary details.


if [ $PRODUCT = "iwf" ];then
    ${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(18,'s6a_3gpp_r11_5','S6a-Interface','Release-11.5.0',1);"
    ${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(6,'s6a_3gpp_r8_5','S6a-Interface','Release-8.5.0',1);"
    ${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(22,'ro_3gpp_r10_5','Ro-Interface','Release-10.5.0',1);"
    ${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(25,'ro_3gpp_r10_5_transatel','Ro-Transatel-Interface','Release-10.5.0',1);"
    ${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(7,'s6a_3gpp_r10_6','S6a-Interface','Release-10.6.0',1);"
else

${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(1,'gy_3gpp_r8_10','Gy-Interface','Release-8.10.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(2,'gy_3gpp_r10_5','Gy-Interface','Release-10.5.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(3,'gx_3gpp_r8_15','Gx-Interface','Release-8.15.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(4,'gx_3gpp_r10_6','Gx-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(5,'gxx_3gpp_r10_6','Gxx-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(6,'s6a_3gpp_r8_5','S6a-Interface','Release-8.5.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(7,'s6a_3gpp_r10_6','S6a-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(8,'s9_3gpp_r9_1','S9-Interface','Release-9.1.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(9,'s9_3gpp_r10_6','S9-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(15,'gz_3gpp_r8_1','Gz-Interface','Release-8.1.0',2);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(10,'gz_3gpp_r10_6','Gz-Interface','Release-10.6.0',2);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(11,'s13_3gpp_r8_11','S13-Interface','Release-8.11.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(12,'s13_3gpp_r10_6','S13-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(14,'rx_3gpp_r10_6','Rx-Interface','Release-10.6.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(16,'cxdx_3gpp_r7_1','CXDX-Interface','Release-7.1.0',1);"
#${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(17,'sh_3gpp_r7_1','SH-Interface','Release-7.1.0');"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(18,'s6a_3gpp_r11_5','S6a-Interface','Release-11.5.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(19,'s9_3gpp_r11_4','S9-Interface','Release-11.4.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(20,'sy_3gpp_r11_4','Sy-Interface','Release-11.4.0',1);"
${my2} "${unset_sess_repl} INSERT INTO DICTIONARY_TB VALUES(21,'cua','RFC6737-Support','Release-Initial',1);"

fi

    ${my2} "${unset_sess_repl} insert into ROLE_TB (ROLE,DESCRIPTION) VALUES ('admin','administrator')"
${my2} "${unset_sess_repl} insert into ROLE_TB (ROLE,DESCRIPTION) VALUES ('operator','operator')"

if [ $PRODUCT = "iwf" ];then
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('AVAMGR',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CMGR',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CLI',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('IWF',3)"
fi

if [ $PRODUCT = "dre" ] || [ -z $PRODUCT ];then
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('ASF',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('AVAMGR',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CMGR',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('CLI',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('DRE',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('DTF',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('ERLBF',3)"
    ${my2} "${unset_sess_repl} insert into LOGGING_CONFIG_TB (COMPONENT_NAME,LOG_LEVEL) VALUES ('WEBAGENT',3)"
fi


${my2} "${unset_sess_repl} insert into TRACING_TB VALUES (1)"
# Inserting default Cipher_suite_names

${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_NULL_MD5')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_NULL_SHA')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_RC4_128_SHA')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_RC4_128_MD5')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_DES_CBC_SHA')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_3DES_EDE_CBC_SHA')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_AES_128_CBC_SHA')"
${my2} "${unset_sess_repl} insert into CIPHER_SUITE_TB(CIPHER_SUITE_NAME) VALUES('TLS_RSA_WITH_AES_256_CBC_SHA')"

# Inserting default rows for Stack related Configuration with default values.
${my2} "${unset_sess_repl} insert into STACK_GEN_CONFIG(PEER_IP_CHECK_ENABLE,IS_PREDICTIVE_LOOP_AVD_REQUIRED) values(1,0)"
${my2} "${unset_sess_repl} insert into TLS_CONFIG(IDENTITY_VERIFICATION_ENABLE,CRL_VERIFICATION_ENABLE) values(0,0)"
${my2} "${unset_sess_repl} insert into SCTP_CONFIG(HEARTBEAT_ENABLE,HEARTBEAT_TIMEOUT,INIT_TIMEOUT,ASSOC_MAX_ATTEMPTS,RTO_MAX,RTO_MIN,RTO_INITIAL,PATH_FAILURE_RETRY_COUNT) values(1,10000,3000,16,60000,2000,3000,16)"

${my2} "${unset_sess_repl} INSERT INTO UserT (UserName,Password,RoleID) VALUES ('root',cast(0x707d050dd6ad530670254ad3369eca6e as binary),(select ROLE_ID from ROLE_TB where ROLE='admin'))"

#Insert session for IWF
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TB (IWF_TRANSLATOR) VALUES ('CAP-Ro')"
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TB (IWF_TRANSLATOR) VALUES ('CAP-Ro-TSL')"
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TB (IWF_TRANSLATOR) VALUES ('s6a-MAP')"
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TB (IWF_TRANSLATOR) VALUES ('MAP-s6a')"

${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TYPE_TB (IWF_TRANSLATOR_TYPE) VALUES ('SS7')"
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TYPE_TB (IWF_TRANSLATOR_TYPE) VALUES ('DIAMETER')"
${my2} "${unset_sess_repl} INSERT INTO IWF_TRANSLATOR_TYPE_TB (IWF_TRANSLATOR_TYPE) VALUES ('HTTP')"

${my2} "${unset_sess_repl} INSERT INTO IWF_LOCAL_SSN_TABLE (SSN,SSN_NAME) VALUES (6,'HLR')"
${my2} "${unset_sess_repl} INSERT INTO IWF_LOCAL_SSN_TABLE (SSN,SSN_NAME) VALUES (149,'SGSN')"
${my2} "${unset_sess_repl} INSERT INTO IWF_LOCAL_SSN_TABLE (SSN,SSN_NAME) VALUES (146,'CAP')"

${my2} "${unset_sess_repl} INSERT INTO IWF_PROTOCOL_FAMILY_TB (IWF_PROTOCOL_FAMILY_ID,FAMILY_NAME) VALUES (1,'ITU')"
${my2} "${unset_sess_repl} INSERT INTO IWF_PROTOCOL_FAMILY_TB (IWF_PROTOCOL_FAMILY_ID,FAMILY_NAME) VALUES (2,'ANSI')"

${my2} "${unset_sess_repl} INSERT INTO IWF_SIGTRAN_SCTP_PROFILE_TB(IWF_SIGTRAN_SCTP_PROFILE_ID,
	IWF_SIGTRAN_SCTP_PROFILE_NAME,
	HEARTBEAT_ENABLE,
	HEARTBEAT_TIMEOUT,
	INIT_TIMEOUT,
	ASSOC_MAX_ATTEMPTS,
	RTO_MAX,
	RTO_MIN,
	RTO_INITIAL,
	PATH_FAILURE_RETRY_COUNT,
	MAX_IN_STREAMS,
	NUM_OUT_STREAMS,
	COOKIE_LIFE,
	SEND_TIME_OUT,
	RECEIVE_TIME_OUT,
	SHUTDOWN_TIMEOUT,
	PMTU_TIMEOUT,
	SEND_BUF_SIZE,
	RECV_BUF_SIZE) VALUES (1,'default_sctp',1,30000,5000,10,2000,60,2000,5,32,32,60,1000,300,5000,6000,102400,102400)"

${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('VOICE_NO_ANSWER_TIMER',180)"
${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('NETWORK_DELAY_TIMER',5)"
${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('SMS_NO_EVENT_TIMER',180)"
${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('NO_ACTIVITY_TIMER',60)"
${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('ACTIVITY_RETRY_COUNT',3)"
${my2} "${unset_sess_repl} INSERT INTO IWF_TIMER_TB (IWF_TIMER_NAME,IWF_TIMER_VALUE) VALUES ('ACTIVITY_RESPONSE_TIMEOUT',10)"

${my2} "${unset_sess_repl} INSERT INTO IWF_FEATURE_TB (IWF_FEATURE_NAME,IWF_FEATURE_STATUS) VALUES ('LOG_CDR',2)"
${my2} "${unset_sess_repl} INSERT INTO IWF_FEATURE_TB (IWF_FEATURE_NAME,IWF_FEATURE_STATUS) VALUES ('FOLLOWON_TANS_TRIGGER',1)"
${my2} "${unset_sess_repl} INSERT INTO IWF_FEATURE_TB (IWF_FEATURE_NAME,IWF_FEATURE_STATUS) VALUES ('CONGESTION_MANAGEMENT',1)"
${my2} "${unset_sess_repl} INSERT INTO IWF_FEATURE_TB (IWF_FEATURE_NAME,IWF_FEATURE_STATUS) VALUES ('MAX_NUMBER_OF_SESSIONS',10000)"

${my2} "${unset_sess_repl} INSERT INTO IWF_DCCA_GENERAL_CONFIG_TB (IWF_DCCA_FEATURE_NAME,IWF_DCCA_FEATURE_VALUE) VALUES ('TX_TIMEOUT',10)"
${my2} "${unset_sess_repl} INSERT INTO IWF_DCCA_GENERAL_CONFIG_TB (IWF_DCCA_FEATURE_NAME,IWF_DCCA_FEATURE_VALUE) VALUES ('INITIAL_ACTION',2)"
${my2} "${unset_sess_repl} INSERT INTO IWF_DCCA_GENERAL_CONFIG_TB (IWF_DCCA_FEATURE_NAME,IWF_DCCA_FEATURE_VALUE) VALUES ('UPDATE_ACTION',2)"

${my2} "${unset_sess_repl} INSERT INTO IWF_PROTOCOL_TB(IWF_PROTOCOL_NAME) VALUES ('CAP')"

#${my2} "INSERT INTO IWF_ACTION_TB(IWF_ACTION_NAME) VALUES ('RRB')"

${my2} "${unset_sess_repl} INSERT INTO IWF_CALL_SCENARIO_TB(CALL_SCENARIO) VALUES ('MO_CAPV1')"
${my2} "${unset_sess_repl} INSERT INTO IWF_CALL_SCENARIO_TB(CALL_SCENARIO) VALUES ('MO_CAPV2')"
${my2} "${unset_sess_repl} INSERT INTO IWF_CALL_SCENARIO_TB(CALL_SCENARIO) VALUES ('MT_CAPV1')"
${my2} "${unset_sess_repl} INSERT INTO IWF_CALL_SCENARIO_TB(CALL_SCENARIO) VALUES ('MT_CAPV2')"
${my2} "${unset_sess_repl} INSERT INTO IWF_CALL_SCENARIO_TB(CALL_SCENARIO) VALUES ('SMS_CAPV3')"

${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('oAnswer')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('oNoAnswer')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('oDisconnect')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('oAbandon')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('oCalledPartyBusy')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('routeSelectFailure')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('tAnswer')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('tNoAnswer')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('tDisconnect')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('tAbandon')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('tBusy')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('o-smsSubmitted')"
${my2} "${unset_sess_repl} INSERT INTO IWF_EVENT_TYPE_TB(IWF_EVENT_TYPE_NAME) VALUES ('o-smsFailure')"

## Default RRB RULE
${my2} "${unset_sess_repl} insert into IWF_PROTOCOL_ACTION_RULE_TB(ACTION_RULE_NAME,PROTOCOL_ID,ACTION_ID) value ('default-rrb-rule',(select IWF_PROTOCOL_ID from IWF_PROTOCOL_TB where IWF_PROTOCOL_NAME = 'CAP'),1)"

${my2} "${unset_sess_repl} insert into IWF_CALL_SCENARIO_MAPPING_TB(IWF_PROTOCOL_ACTION_RULE_ID,IWF_CALL_SCENARIO_ID ) value ((select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = 'default-rrb-rule'),(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')),(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oCalledPartyBusy') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oCalledPartyBusy')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oNoAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oNoAnswer')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')),(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oAnswer')),'notifyAndContinue','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oDisconnect') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oDisconnect')),'notifyAndContinue','1' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oDisconnect')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'routeSelectFailure') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='routeSelectFailure')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_CALL_SCENARIO_MAPPING_TB(IWF_PROTOCOL_ACTION_RULE_ID,IWF_CALL_SCENARIO_ID ) value ((select IWF_PROTOCOL_ACTION_RULE_ID from           IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = 'default-rrb-rule'),(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO =         'MT_CAPV2') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tBusy') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tBusy')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tNoAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tNoAnswer')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tAnswer')),'notifyAndContinue','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tDisconnect') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tDisconnect')),'notifyAndContinue','1' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tDisconnect')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tAbandon') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV2')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tAbandon')),'notifyAndContinue','1' )"

${my2} "${unset_sess_repl} insert into IWF_CALL_SCENARIO_MAPPING_TB(IWF_PROTOCOL_ACTION_RULE_ID,IWF_CALL_SCENARIO_ID ) value ((select IWF_PROTOCOL_ACTION_RULE_ID from           IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = 'default-rrb-rule'),(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO =         'MO_CAPV1') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV1')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oAnswer')),'notifyAndContinue','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV1')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'oDisconnect') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oDisconnect')),'notifyAndContinue','1' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MO_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='oDisconnect')),'transparent','2' )"

${my2} "${unset_sess_repl} insert into IWF_CALL_SCENARIO_MAPPING_TB(IWF_PROTOCOL_ACTION_RULE_ID,IWF_CALL_SCENARIO_ID ) value ((select IWF_PROTOCOL_ACTION_RULE_ID from           IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME = 'default-rrb-rule'),(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO =         'MT_CAPV1') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV1')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tAnswer') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tAnswer')),'notifyAndContinue','2' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from               IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME    ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV1')),(select               IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'tDisconnect') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tDisconnect')),'notifyAndContinue','1' )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE,LEG_ID ) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'MT_CAPV1')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='tDisconnect')),'interrupted','2' )"

${my2} "${unset_sess_repl} insert into IWF_CALL_SCENARIO_MAPPING_TB(IWF_PROTOCOL_ACTION_RULE_ID,IWF_CALL_SCENARIO_ID ) value ((select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB   where ACTION_RULE_NAME = 'default-rrb-rule'),(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'SMS_CAPV3') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'SMS_CAPV3')),(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'o-smsSubmitted') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'SMS_CAPV3')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='o-smsSubmitted')),'interrupted')"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_MAPPING_TB(IWF_CALL_SCENARIO_MAPPING_ID,IWF_EVENT_TYPE_ID ) value ((select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'SMS_CAPV3')),(select IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME = 'o-smsFailure') )"

${my2} "${unset_sess_repl} insert into IWF_EVENT_TYPE_DETAILS_TB(IWF_EVENT_TYPE_MAPPING_ID,MONITOR_MODE) value ((select IWF_EVENT_TYPE_MAPPING_ID from                   IWF_EVENT_TYPE_MAPPING_TB where IWF_CALL_SCENARIO_MAPPING_ID = (select IWF_CALL_SCENARIO_MAPPING_ID from IWF_CALL_SCENARIO_MAPPING_TB where                   IWF_PROTOCOL_ACTION_RULE_ID=(select IWF_PROTOCOL_ACTION_RULE_ID from IWF_PROTOCOL_ACTION_RULE_TB where ACTION_RULE_NAME ='default-rrb-rule') and              IWF_CALL_SCENARIO_ID=(select IWF_CALL_SCENARIO_ID from IWF_CALL_SCENARIO_TB where CALL_SCENARIO = 'SMS_CAPV3')) and IWF_EVENT_TYPE_ID = (select                IWF_EVENT_TYPE_ID from IWF_EVENT_TYPE_TB where IWF_EVENT_TYPE_NAME='o-smsFailure')),'interrupted')"

echo "-------------------------------------------"
echo "SUCCESFULLY INSERTED DEFAULT ROWS IN TABLES "
echo "-------------------------------------------"
LOG_INFO "SUCCESFULLY INSERTED DEFAULT ROWS IN TABLES" $LINENO
