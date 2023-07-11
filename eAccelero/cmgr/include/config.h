#ifndef CONFIG_H
#define CONFIG_H

#include "Component.h"
#include "Logger.h"

#include "Socket.h"
#include <netinet/sctp.h>

#define HOST "localhost"
#define USER "root"
#define PASS "intelliss7"
#define LOCAL_HOST_IP "127.0.0.1"
#define DATABASE "DIAMETRIQ"

#define MAX_SPECIAL_STATEMENT_SIZE 6144 // 6K, 6*1024 = 6144
#ifdef FOR_IWF
#define DRE 0
#else
#define DRE 1
#endif

#define MAX_TABLENAME_LEN 128
#define MAX_FIELDNAME_LEN 1024
#define MAX_STATEMENT_SIZE 2045
#define MAX_FILTER_ID 32
#define MAX_ASSOCIATION_MAPPING_ID 15

#define INVALID_NUM (-1)
#define INVALID_STR ('\0')
#define PRINTF printf
#ifdef DEBUG
#define DLOG_NONE DLOG_DEBUG 
#else
#define DLOG_NONE(...) 
#endif

#define TABLE_DELIMITER '#'
#define FIELD_DELIMITER '\t'
#define ROW_DELIMITER '\n'

#define DRE_DB_FAIL 0
#define DRE_DB_SUCCESS 1

#define MAX_VHOST_SUPPORTED 2
#define MAX_USER_ALLOWED 32

#define IWF_DB_FAIL 0
#define IWF_DB_SUCCESS 1
#define IWF_DB_SUCCESS_SEND 2

#define DRE_FAIL 0
#define DRE_SUCCESS 1

#define MAX_DICT_SUPPORTED 8
#define MAX_MULTIHOMING_IP 4
#define MAX_SSN_SUPPORTED 3
#define MAX_SECONDARY_IP_SUPPORTED 4
#define REMOVE_FOUR_CHARATERS 4
#define MAX_IP_ADDRS 10

typedef uint64_t DbStatus_e;

typedef enum _ConfigReqType
{
    DRE_DB_ADD,
    DRE_DB_MOD,
    DRE_DB_DEL,
    DRE_DB_GET,
    DRE_DB_ERR
}ConfigReqType_e;

typedef enum _dreTableName
{
    DRE_AVAILABILITY_MANAGER_CONFIG_T,
    DRE_DEFAULT_ROUTE_T,
    DRE_DYNAMIC_DISCOVERY_T,
    DRE_LOCAL_HOST_CONFIG_T,
    DRE_PEER_GLOBAL_CONFIG_T,
    DRE_PEER_T,
    DRE_PEER_TIMERS_T,
    DRE_REALM_ROUTING_T,
    DRE_REPLICATION_MANAGER_CONFIG_T,
    DRE_USER_T,
    DRE_ASF_T,
    DRE_ASFCONFIG_T,
    DRE_ASFFEATURE_T,
    DRE_PEER_DICT_MAP_T,
    DRE_TABLE_COUNT
}dreTableName_e;

typedef enum _dreDataType
{
    DRE_AVAILABILITY_MANAGER_CONFIG,
    DRE_DEFAULT_ROUTE,
    DRE_DYNAMIC_DISCOVERY,
    DRE_LOCAL_HOST_CONFIG,
    DRE_PEER_GLOBAL_CONFIG,
    DRE_PEER_AND_TIMER,
    DRE_REALM_ROUTING,
    DRE_REPLICATION_MANAGER_CONFIG,
    DRE_USER,
    DRE_ASF,
    DRE_ASFCONFIG,
    DRE_ASFFEATURE,
    DRE_PEER_DICT_MAP,
    DRE_DATATYPE_COUNT
}dreDataType_e;



#endif
