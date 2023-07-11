
#include "FlatUserAccess_caller.h"

using namespace Stub;

void FlatUserAccessRespCbk::RegisterFlatUserAccessRespHandler()
{
    
    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_FLATUSERACCESS, M_FLATUSERACCESS_LOGIN),
        CallbackSlot<FlatUserAccessRespCbk, FlatResult, FlatEncodingTraits, FlatEncodingPolicy>(this, &FlatUserAccessRespCbk::LoginRespCbk));

    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_FLATUSERACCESS, M_FLATUSERACCESS_LOGOUT),
        CallbackSlot<FlatUserAccessRespCbk, FlatResult, FlatEncodingTraits, FlatEncodingPolicy>(this, &FlatUserAccessRespCbk::LogoutRespCbk));

}
