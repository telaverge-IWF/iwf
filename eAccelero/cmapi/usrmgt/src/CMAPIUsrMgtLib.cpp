/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#include "CMAPICommon.h"
#include "ErrorResp.h"
#include "CMAPIUsrMgtLib.h"
#include "ComponentDefines.h"
#include "CMgrUserManagementMethods_caller.h"
#include "UserManagement_def.h"
#include "UserManagement.h"


int CMAPIUserConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMAPIUserConfig: InitializeLibrary\n");
    CLOG_DEBUG("InitializeLibrary: Initializing Config Manager Interface");
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CMgrUserMgmtCallerObj = new Stub::CMgrUserManagementMethods(dest, 0);
    Stub::CMgrUserManagementMethodsRespCbk::RegisterCMgrUserManagementMethodsRespHandler();

    m_CMAPIResponse = new CMAPIIntSync();

    return retVal;
}

int CMAPIUserConfig::IsResponseOK(EmailServerResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIUserConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        EmailServerResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::IsResponseOK(EmailContentResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIUserConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        EmailContentResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::IsResponseOK(UserDetailResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIUserConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL
            || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        UserDetailResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);

        if ( Resp!=NULL && Resp->has_responseid() )
        {
            retVal = Resp->responseid();
            Resp->SerializeToString(&StrVal);
        }
        else
        {
            retVal = CMAPI_MESSERROR;
            ErrResp.SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::GetEmailContentDetails(EmailContentReq Req, EmailContentResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIUserConfig: GetEmailContentDetails");

    Req.set_requestid(GET_EMAIL_CONTENT);

    CLOG_DEBUG("Sending Email request ");

    m_CMgrUserMgmtCallerObj->HandleGetEmailContentReqs(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetEmailContentDetails: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetEmailContentDetails: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Resp->ParseFromString(strVal);
    if (Resp->responseid() == CMAPI_SUCCESS)
    {
        retVal = Resp->responseid();
        CLOG_DEBUG("GetEmailContentDetails: Successfully returned Users");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetEmailContentDetails: Failed to fetch Users");
    }

    return retVal;
}

int CMAPIUserConfig::GetEmailServerDetails(EmailServerReq Req, EmailServerResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIUserConfig: GetEmailServerDetails");

    Req.set_requestid(GET_EMAIL_SERVER);

    CLOG_DEBUG("Sending User request ");

    m_CMgrUserMgmtCallerObj->HandleGetEmailServerReqs(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetEmailServerDetails: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetEmailServerDetails: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Resp->ParseFromString(strVal);
    if (Resp->responseid() == CMAPI_SUCCESS)
    {
        DecryptEmailServerPassword(Req,Resp);
        retVal = Resp->responseid();
        CLOG_DEBUG("GetEmailServerDetails: Successfully returned Users");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetEmailServerDetails: Failed to fetch Users");
    }

    return retVal;
}

int CMAPIUserConfig::GetUser(UserDetails UserList, UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    UserDetailReq Req;
    int numOfUser;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIUserConfig: GetUser");

    Req.set_requestid(GET_USER);

    numOfUser = UserList.userinfo_size();
    if(numOfUser > 0 )
    {
        UserDetails *usersInfo = Req.mutable_usersinfo();
        usersInfo->CopyFrom(UserList);
    }

    CLOG_DEBUG("Sending User request ");

    m_CMgrUserMgmtCallerObj->HandleGetUserConfigReqs(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetUser: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetUser: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Resp->ParseFromString(strVal);
    if (Resp->responseid() == CMAPI_SUCCESS)
    {
        retVal = Resp->responseid();
        CLOG_DEBUG("GetUser: Successfully returned Users");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetUser: Failed to fetch Users");
    }

    return retVal;
}

int CMAPIUserConfig::GetPrevilage(Previlages PrevilageList, UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    UserDetailReq Req;
    int numOfPrevilege;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIUserConfig: GetPrevilage");

    Req.set_requestid(GET_USER_PRIVILEGE);

    numOfPrevilege = PrevilageList.previlageinfo_size();
    if(numOfPrevilege > 0 )
    {
        Previlages *previlageInfo = Req.mutable_previlageinfo();
        previlageInfo->CopyFrom(PrevilageList);
    }

    CLOG_DEBUG("Sending Previlage request ");

    m_CMgrUserMgmtCallerObj->HandleGetUserConfigReqs(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetPrevilage: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetPrevilage: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Resp->ParseFromString(strVal);
    if (Resp->responseid() == CMAPI_SUCCESS)
    {
        retVal = Resp->responseid();
        CLOG_DEBUG("GetPrevilage: Successfully returned Roles");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetPrevilage: Failed to fetch Roles");
    }

    return retVal;
}

int CMAPIUserConfig::GetUserRole(Roles RoleList, UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;
    UserDetailReq Req;
    int numOfRole;
    m_SendSuccess = true;

    CLOG_DEBUG("CMAPIUserConfig: GetUserRole");

    Req.set_requestid(GET_USER_ROLE);

    numOfRole = RoleList.roleinfo_size();
    if(numOfRole > 0 )
    {
        Roles *rolesInfo = Req.mutable_rolesinfo();
        rolesInfo->CopyFrom(RoleList);
    }

    CLOG_DEBUG("Sending Role request ");

    m_CMgrUserMgmtCallerObj->HandleGetUserConfigReqs(Req,
            new CMAPICookie(Req.requestid(), (void *) &Req));
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        ErrorDetails* err = Resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    CLOG_DEBUG("GetUserRole: Waiting for Response");

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetUserRole: Response Received");
    if(strVal.empty())
    {
        return CMAPI_ERROR;
    }

    Resp->ParseFromString(strVal);
    if (Resp->responseid() == CMAPI_SUCCESS)
    {
        retVal = Resp->responseid();
        CLOG_DEBUG("GetUserRole: Successfully returned Roles");
    }
    else
    {
        retVal = CMAPI_SRVERROR;
        CLOG_ERROR("GetUserRole: Failed to fetch Roles");
    }

    return retVal;
}

int CMAPIUserConfig::ModEmailContentDetails(EmailContentReq Req,EmailContentResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    string StrVal;
    int numOfEmail;

    CLOG_DEBUG("CMAPIUserConfig::ModEmailContentDetails");

    Req.set_requestid(MOD_EMAIL_CONTENT);
    numOfEmail = Req.emailcontents_size();
    if(numOfEmail > 0 )
    {

        m_CMgrUserMgmtCallerObj->HandleSetEmailContentReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("ModEmailContentDetails::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("ModEmailContentDetails::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("ModEmailContentDetails::Successfully modify EmailContent");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("ModEmailContentDetails::Failed to modify EmailContent");
            }
        }
    }
    else
    {
        DLOG_ERROR("ModEmailContentDetails::No Data");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIUserConfig::DelEmailServerDetails(EmailServerReq Req,EmailServerResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    string StrVal;
    int numOfServer;

    CLOG_DEBUG("CMAPIUserConfig::DelEmailServerDetails");

    Req.set_requestid(DEL_EMAIL_SERVER);
    numOfServer = Req.emailservers_size();
    if(numOfServer > 0 )
    {

        m_CMgrUserMgmtCallerObj->HandleSetEmailServerReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("DelEmailServerDetails::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("DelEmailServerDetails::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("DelEmailServerDetails::Successfully delete EmailServer");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("DelEmailServerDetails::Failed to delete EmailServer");
            }
        }
    }
    else
    {
        DLOG_ERROR("DelEmailServerDetails::No Data");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

#define KEY 27
#define MAX_PASSWORD_LEN 16

/*
 * User has to give te correct iLength, there is no validation for the same
 * and undefined behaviour will be observed
 */
void CMAPIUserConfig::DecryptString(char *sInBuffer, char *sOutBuffer,int iLength)
{
    for(int i=0;i<iLength;i++)
    {
        sOutBuffer[i] = sInBuffer[i] - KEY;
    }
}

/*
 * User has to give te correct iLength, there is no validation for the same
 * and undefined behaviour will be observed
 */
void CMAPIUserConfig::EncryptString(char *sInBuffer, char *sOutBuffer,int iLength)
{
    for(int i=0;i<iLength;i++)
    {
        sOutBuffer[i] = sInBuffer[i] + KEY;
    }
}

void CMAPIUserConfig::DecryptEmailServerPassword(EmailServerReq Req,EmailServerResp *Resp)
{
    int iCount;
    iCount = Resp->emailservers_size();

    for(int i=0;i<iCount;i++)
    {
        EmailServer *pEmailServer = Resp->mutable_emailservers(i);

        char sInBuffer[20];
        char sOutBuffer[20];
        memset(sOutBuffer,0,sizeof(sOutBuffer));
        memcpy(sInBuffer,pEmailServer->mutable_password()->c_str(),MAX_PASSWORD_LEN);
        DecryptString(sInBuffer,sOutBuffer,MAX_PASSWORD_LEN);
        pEmailServer->set_passwordstring(sOutBuffer);
        pEmailServer->clear_password();

    }
}


void CMAPIUserConfig::EncryptEmailServerPassword(EmailServerReq *Req,EmailServerResp *Resp)
{
    int iCount;
    iCount = Req->emailservers_size();

    for(int i=0;i<iCount;i++)
    {
        EmailServer *pEmailServer = Req->mutable_emailservers(i);

        if (pEmailServer->has_passwordstring())
        {
            char sInBuffer[20];
            char sOutBuffer[20];
            memset(sOutBuffer,0,sizeof(sOutBuffer));
            strcpy(sInBuffer,pEmailServer->mutable_passwordstring()->c_str());
            EncryptString(sInBuffer,sOutBuffer,MAX_PASSWORD_LEN);
            pEmailServer->set_password(sOutBuffer,MAX_PASSWORD_LEN);
            pEmailServer->clear_passwordstring();
        }
    }
}

int CMAPIUserConfig::SetEmailServerDetails(EmailServerReq Req,EmailServerResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    string StrVal;
    int numOfServer;

    CLOG_DEBUG("CMAPIUserConfig::SetEmailServerDetails");

    Req.set_requestid(SET_EMAIL_SERVER);
    numOfServer = Req.emailservers_size();
    if(numOfServer > 0 )
    {

        EncryptEmailServerPassword(&Req,Resp);
        m_CMgrUserMgmtCallerObj->HandleSetEmailServerReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("SetEmailServerDetails::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("SetEmailServerDetails::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("SetEmailServerDetails::Successfully add/modify EmailServer");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("SetEmailServerDetails::Failed to modify/add EmailServer");
            }
        }
    }
    else
    {
        DLOG_ERROR("SetEmailServerDetails::No Data");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIUserConfig::ModUser(UserDetails UserList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfUser;

    CLOG_DEBUG("CMAPIUserConfig::ModUser");

    Req.set_requestid(MOD_USER);
    numOfUser = UserList.userinfo_size();
    if(numOfUser > 0 )
    {
        UserDetails *usersInfo = Req.mutable_usersinfo();
        usersInfo->CopyFrom(UserList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("ModUser::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("ModUser::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("ModUser::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("ModUser::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("ModUser::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}


int CMAPIUserConfig::ModUserRole(Roles RoleList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfRole;

    CLOG_DEBUG("CMAPIUserConfig::ModUserRole");

    Req.set_requestid(MOD_USER_ROLE);
    numOfRole = RoleList.roleinfo_size();
    if(numOfRole > 0 )
    {
        Roles *rolesInfo = Req.mutable_rolesinfo();
        rolesInfo->CopyFrom(RoleList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("ModUserRole::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("ModUserRole::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("ModUserRole::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("ModUserRole::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("ModUserRole::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}


int CMAPIUserConfig::DelUser(UserDetails UserList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfUser;

    CLOG_DEBUG("CMAPIUserConfig::DelUser");

    Req.set_requestid(DEL_USER);
    numOfUser = UserList.userinfo_size();
    if(numOfUser > 0 )
    {
        UserDetails *usersInfo = Req.mutable_usersinfo();
        usersInfo->CopyFrom(UserList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("DelUser::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("DelUser::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("DelUser::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("DelUser::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("DelUser::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}


int CMAPIUserConfig::DelUserRole(Roles RoleList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfRole;

    CLOG_DEBUG("CMAPIUserConfig::DelUserRole");

    Req.set_requestid(DEL_USER_ROLE);
    numOfRole = RoleList.roleinfo_size();
    if(numOfRole > 0 )
    {
        Roles *rolesInfo = Req.mutable_rolesinfo();
        rolesInfo->CopyFrom(RoleList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("DelUserRole::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("DelUserRole::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("DelUserRole::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("DelUserRole::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("DelUserRole::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}


int CMAPIUserConfig::AddUser(UserDetails UserList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfUser;

    CLOG_DEBUG("CMAPIUserConfig::AddUser");

    Req.set_requestid(SET_USER);
    numOfUser = UserList.userinfo_size();
    if(numOfUser > 0 )
    {
        UserDetails *usersInfo = Req.mutable_usersinfo();
        usersInfo->CopyFrom(UserList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("AddUser::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("AddUser::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("AddUser::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("AddUser::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("AddUser::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}


int CMAPIUserConfig::AddUserRole(Roles RoleList,UserDetailResp* Resp)
{
    int retVal = CMAPI_SUCCESS;
    UserDetailReq Req;
    m_SendSuccess = true;
    //UserResp Resp;
    string StrVal;
    int numOfRole;

    CLOG_DEBUG("CMAPIUserConfig::AddUserRole");

    Req.set_requestid(ADD_USER_ROLE);
    numOfRole = RoleList.roleinfo_size();
    if(numOfRole > 0 )
    {
        Roles *rolesInfo = Req.mutable_rolesinfo();
        rolesInfo->CopyFrom(RoleList);

        m_CMgrUserMgmtCallerObj->HandleSetUserConfigReqs(Req,
                new CMAPICookie(Req.requestid(), (void *) &Req));
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            ErrorDetails *err = Resp->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        CLOG_DEBUG("AddUserRole::Waiting for Response");

        m_CMAPIResponse->Get(StrVal);
        CLOG_DEBUG("AddUserRole::Response received");
        if(StrVal.empty())
        {
            retVal = CMAPI_ERROR;
        }
        else
        {
            Resp->ParseFromString(StrVal);
            if(Resp->responseid() == CMAPI_SUCCESS)
            {
                retVal = Resp->responseid();
                CLOG_DEBUG("AddUserRole::Successfully added Role");
            }
            else
            {
                retVal = CMAPI_SRVERROR;
                CLOG_DEBUG("AddUserRole::Failed to add role");
            }
        }
    }
    else
    {
        DLOG_ERROR("AddUserRole::No UserName or Password");
        retVal = CMAPI_INVALIDPARAMS;
    }
    return retVal;
}

int CMAPIUserConfig::HandleGetUserConfigReqsRespCbk(UserDetailResp *Resp)
{
    CLOG_DEBUG("HandleGetUserConfigReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::HandleSetUserConfigReqsRespCbk(UserDetailResp *Resp)
{
    CLOG_DEBUG("HandleSetUserConfigReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::HandleSetEmailContentReqsRespCbk(EmailContentResp *Resp)
{
    CLOG_DEBUG("HandleSetEmailContentReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}


int CMAPIUserConfig::HandleGetEmailContentReqsRespCbk(EmailContentResp *Resp)
{
    CLOG_DEBUG("HandleGetEmailContentReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}

int CMAPIUserConfig::HandleSetEmailServerReqsRespCbk(EmailServerResp *Resp)
{
    CLOG_DEBUG("HandleSetEmailServerReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}


int CMAPIUserConfig::HandleGetEmailServerReqsRespCbk(EmailServerResp *Resp)
{
    CLOG_DEBUG("HandleGetEmailServerReqsRespCbk");
    int retVal = IsResponseOK(Resp);
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    if (retVal == CMAPI_SUCCESS)
    {
        CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
        std::string StrVal;
        Resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
        delete lCookie;
    }
    return retVal;
}



