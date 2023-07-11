#ifndef __MeSSTest_h__
#define __MeSSTest_h__


#define SERVER_COMP_ID  100
#define SERVER_COMP_ID1  300
#define CLIENT_COMP_ID  200

#define I_TEST_ID         10
#define I_TEST_ID1        20
#define M_GET_CONFIG      1
#define M_GET_CONFIG1     11
#define M_SET_CONFIG      2
#define M_SET_CONFIG1     22
#define M_MULTICAST_REQ   3
#define M_MULTICAST_REQ1  33
#define M_DELAY_RESP      4
#define M_TIMEOUT_RESP    5
#define M_WRONGCOMP_RESP  6
#define M_WRONG_IFACE_RESP  7
#define M_WRONG_METHOD_RESP  8
#define M_CBK_RGS_FAILED   12
#define M_MULTICAST_DELAY_REQ   26

struct GetConfigReq
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

unsigned int gTest = 0;
#endif // __MeSSTest_h__
