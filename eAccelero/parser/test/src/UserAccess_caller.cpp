
#include "UserAccess_caller.h"

using namespace Stub;

void UserAccessRespCbk::RegisterUserAccessRespHandler()
{
    
    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_LOGIN),
        CallbackSlot<UserAccessRespCbk, Result, PBEncodingTraits, PBEncodingPolicy>(this, &UserAccessRespCbk::LoginRespCbk));

    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_LOGOUT),
        CallbackSlot<UserAccessRespCbk, Result, PBEncodingTraits, PBEncodingPolicy>(this, &UserAccessRespCbk::LogoutRespCbk));

    MeSSComponent::Instance().MeSSObj().RegisterRespHandler (MakeMsgId(I_USERACCESS, M_USERACCESS_GETUSERS),
        CallbackSlot<UserAccessRespCbk, Users, PBEncodingTraits, PBEncodingPolicy>(this, &UserAccessRespCbk::GetUsersRespCbk));

}
