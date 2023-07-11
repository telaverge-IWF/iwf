
#ifndef _INTERFACE_TEST_H
#define _INTERFACE_TEST_H


#include "test_def.h"
#include "MeSSComponent.h"


class FlatUserAccess:public eAccelero::Interface
{
public:
    FlatUserAccess():Interface(I_FLATUSERACCESS)
    { 
        eAccelero::MeSSComponent::Instance().MeSSObj().RegisterInterface(this);
    }

    virtual int Login(FlatUser *user,FlatResult *resCode) = 0;

    virtual int Logout(FlatUser *user,FlatResult *resCode) = 0;

    void RegisterMethods();
    virtual ~FlatUserAccess() { }
};


class UserAccess:public eAccelero::Interface
{
public:
    UserAccess():Interface(I_USERACCESS)
    { 
        eAccelero::MeSSComponent::Instance().MeSSObj().RegisterInterface(this);
    }

    virtual int Login(User *user,Result *resCode) = 0;

    virtual int Logout(User *user,Result *resCode) = 0;

    virtual int GetUsers(Req *req,Users *users) = 0;

    void RegisterMethods();
    virtual ~UserAccess() { }
};

#endif
