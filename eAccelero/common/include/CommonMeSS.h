#ifndef __MeSSTest_h__
#define __MeSSTest_h__

#include "CommonStructure.h"

#define SERVER_COMP_ID  100
#define CLIENT_COMP_ID  200

#if 0
#define I_TEST_ID       10
#define M_GET_CONFIG    1
#define M_SET_CONFIG    2
#define M_MULTICAST_REQ 3
#define M_GET_CONFIG_PEER    4
#define M_SET_CONFIG_PEER    5
#endif


#if 0
struct GetConfigReq
{
    int id;
    char str[100];
};

struct testConfigReq
{
    int id;
    char str[100];
};

struct GetConfigResp
{
    int id;
    int val;
    char result[100];
};
struct testConfigResp
{
    int id;
    int val;
    char result[100];
};

struct SetConfigReq
{
    int id;
    int val;
    char descr[100];
};

struct SetConfigResp
{
    int id;
    char result[100];
};

typedef struct _GetConfigRsp {
    int cmd_id;
    int num_rec;
    //DrePeerPayload RspPayload[10];
    DrePeerPayload RspPayload;
}GetConfigRsp;
#endif

#endif
