
#include "test.h"


void FlatUserAccess::RegisterMethods()
{

    this->RegisterMethod(M_FLATUSERACCESS_LOGIN,eAccelero::MethodSlot<FlatUserAccess,
    FlatUser,FlatResult,eAccelero::FlatEncodingTraits,eAccelero::FlatEncodingPolicy>(this,&FlatUserAccess::Login));

    this->RegisterMethod(M_FLATUSERACCESS_LOGOUT,eAccelero::MethodSlot<FlatUserAccess,
    FlatUser,FlatResult,eAccelero::FlatEncodingTraits,eAccelero::FlatEncodingPolicy>(this,&FlatUserAccess::Logout));
}

void UserAccess::RegisterMethods()
{

    this->RegisterMethod(M_USERACCESS_LOGIN,eAccelero::MethodSlot<UserAccess,
    User,Result,eAccelero::PBEncodingTraits,eAccelero::PBEncodingPolicy>(this,&UserAccess::Login));

    this->RegisterMethod(M_USERACCESS_LOGOUT,eAccelero::MethodSlot<UserAccess,
    User,Result,eAccelero::PBEncodingTraits,eAccelero::PBEncodingPolicy>(this,&UserAccess::Logout));

    this->RegisterMethod(M_USERACCESS_GETUSERS,eAccelero::MethodSlot<UserAccess,
    Req,Users,eAccelero::PBEncodingTraits,eAccelero::PBEncodingPolicy>(this,&UserAccess::GetUsers));
}
