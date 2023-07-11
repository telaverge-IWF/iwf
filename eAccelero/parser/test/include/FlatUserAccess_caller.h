
#ifndef _INTERFACE_FLATUSERACCESS_CALLER_H
#define _INTERFACE_FLATUSERACCESS_CALLER_H


#include "MeSSComponent.h"
#include "test_def.h"
#include "Interface.h"

using namespace eAccelero;

namespace Stub{
class FlatUserAccessRespCbk
{
public:
    FlatUserAccessRespCbk() { }

    virtual int LoginRespCbk(FlatResult *resCode) = 0;

    virtual int LogoutRespCbk(FlatResult *resCode) = 0;

    void RegisterFlatUserAccessRespHandler();
    virtual ~FlatUserAccessRespCbk() { }
};

class FlatUserAccess
{
public: 
    FlatUserAccess(MeSSEndpoint loc_dest,unsigned loc_flags = 0):
    m_dest(loc_dest),
    flags(loc_flags)
    {
    }

    int Login(FlatUser& user,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_FLATUSERACCESS,M_FLATUSERACCESS_LOGIN);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, (void*)&user, sizeof(user), (void *)cookie,flags);
        return 0;
    }

    int Logout(FlatUser& user,void *cookie = NULL)
    {
        MessageId msgid = MakeMsgId(I_FLATUSERACCESS,M_FLATUSERACCESS_LOGOUT);
        MeSSComponent::Instance().MeSSObj().Send(m_dest, msgid, (void*)&user, sizeof(user), (void *)cookie,flags);
        return 0;
    }

    template <typename C>
    static void SetLoginRespHandler(C *obj, int (C::*cbkFn)(FlatResult*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_FLATUSERACCESS, M_FLATUSERACCESS_LOGIN),
        CallbackSlot<C, FlatResult, FlatEncodingTraits, FlatEncodingPolicy>(obj, cbkFn));
    }

    template <typename C>
    static void SetLogoutRespHandler(C *obj, int (C::*cbkFn)(FlatResult*))
    {
        MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_FLATUSERACCESS, M_FLATUSERACCESS_LOGOUT),
        CallbackSlot<C, FlatResult, FlatEncodingTraits, FlatEncodingPolicy>(obj, cbkFn));
    }

private:
    MeSSEndpoint m_dest;
    unsigned flags;
};
}//namespace Stub
#endif
