
#ifndef _INTERFACE_USERACCESS_CALLER_H
#define _INTERFACE_USERACCESS_CALLER_H


#include "MeSSComponent.h"
#include "test_def.h"
#include "Interface.h"

using namespace eAccelero;

namespace Stub{
class UserAccessRespCbk
{
public:
    UserAccessRespCbk() { }

    virtual int LoginRespCbk(Result *resCode) = 0;

    virtual int LogoutRespCbk(Result *resCode) = 0;

    virtual int GetUsersRespCbk(Users *users) = 0;

    void RegisterUserAccessRespHandler();
    virtual ~UserAccessRespCbk() { }
};

class UserAccess
{
public: 
    UserAccess(MeSSEndpoint loc_dest,unsigned loc_flags = 0):
    m_dest(loc_dest),
    flags(loc_flags)
    {
    }

    int Login(User& user,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_USERACCESS,M_USERACCESS_LOGIN);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, user, cookie);
        return 0;
    }

    int Logout(User& user,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_USERACCESS,M_USERACCESS_LOGOUT);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, user, cookie);
        return 0;
    }

    int GetUsers(Req& req,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_USERACCESS,M_USERACCESS_GETUSERS);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, req, cookie);
        return 0;
    }

    template <typename C>
    static void SetLoginRespHandler(C *obj, int (C::*cbkFn)(Result*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_LOGIN),
        CallbackSlot<C, Result, PBEncodingTraits, PBEncodingPolicy>(obj, cbkFn));
    }

    template <typename C>
    static void SetLogoutRespHandler(C *obj, int (C::*cbkFn)(Result*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_LOGOUT),
        CallbackSlot<C, Result, PBEncodingTraits, PBEncodingPolicy>(obj, cbkFn));
    }

    template <typename C>
    static void SetGetUsersRespHandler(C *obj, int (C::*cbkFn)(Users*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_GETUSERS),
        CallbackSlot<C, Users, PBEncodingTraits, PBEncodingPolicy>(obj, cbkFn));
    }

private:
    MeSSEndpoint m_dest;
    unsigned flags;
};
}//namespace Stub
#endif
