
#ifndef _INTERFACE_TEST_DEF_H
#define _INTERFACE_TEST_DEF_H


#define I_FLATUSERACCESS 1000

#define M_FLATUSERACCESS_LOGIN 1

#define M_FLATUSERACCESS_LOGOUT 2

#include "test.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>


#define I_USERACCESS 1001

#define M_USERACCESS_LOGIN 1

#define M_USERACCESS_LOGOUT 2

#define M_USERACCESS_GETUSERS 3
enum FlatPriviledge
{
    FLAT_PRIV_ADMIN = 0,
    FLAT_PRIV_USER  = 1,
    FLAT_PRIV_OPERATOR = 2
};

struct FlatUser
{
    unsigned int userId;
    char userName[100];
    FlatPriviledge priviledge;
};

struct FlatResult
{
    int resCode;
    char descr[100];
};

#endif
