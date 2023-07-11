
/* ****************-*-CPP-******************
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
 * **************************************/


#include "string"
#include "CMAPICommon.h"
#include "CMApiComp.h"
#include "Compo.h"
#include "ComponentDefines.h"
#include "ErrorResp.h"

using namespace std;

int CMApiComponents::GetASFConfigurationRespCbk(ASFConfigResp *Resp)
{
    string strVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL )
    {
        ASFConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_ERROR);
        // Fill ErrorDetails here
        ErrorResponse.SerializeToString(&strVal); 
    } else {
        Resp->SerializeToString(&strVal);
    }
    m_CMgrResponse->Set(strVal);
    return 0;
}

int CMApiComponents::SetASFConfigurationRespCbk(ASFConfigResp *Resp)
{
    string strVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }

    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL )
    {
        ASFConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_SRVERROR);
        // Fill ErrorDetails here
        ErrorResponse.SerializeToString(&strVal); 
        m_CMgrResponse->Set(strVal);
    } else if (Resp->has_responseid() && (Resp->responseid() != CMAPI_SUCCESS))
    {
        Resp->SerializeToString(&strVal);
        m_CMgrResponse->Set(strVal);
    }
    return 0;
}

int CMApiComponents::SendCMgrRequest(ASFConfigReq& Req, ASFConfigResp *Resp, bool GetReq)
{
    int retVal = CMAPI_SUCCESS;
    std::string strVal;

    m_SendSuccess = true;

    if (GetReq == true )
    {
        // Implies SET type of Operation
        m_CmgrObj->GetASFConfiguration(Req);
    } else {
        // Implies GET type of Operation
        m_CmgrObj->SetASFConfiguration(Req);
    }
    if (m_SendSuccess == false)
    {
        ErrorDetails *err = Resp->add_errordetails();
        retVal = CMAPI_MESSERROR;
        Resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if (m_CMgrResponse->Get(strVal, m_waitTime))
    {
        if (!strVal.empty())
        {
            Resp->ParseFromString(strVal);
            retVal = Resp->responseid();
        } else {
            retVal = CMAPI_ERROR;
            // Add ErrorDetails here
        }

    } else {
        ErrorDetails *err = Resp->add_errordetails();
        retVal = CMAPI_TIMEOUT;
        Resp->set_responseid(retVal); 
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}

int CMApiComponents::AddASGroup(ASGroupsCfg& ASGroupCfgInfo)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(ADD_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }

    return retVal;
}

int CMApiComponents::AddASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(ADD_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }

    return retVal;
}

int CMApiComponents::ModifyASGroup(ASGroupsCfg& ASGroupCfgInfo)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }

    return retVal;
}
int CMApiComponents::ModifyASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }

    return retVal;
}

int CMApiComponents::RemoveASGroup(ASGroupsCfg& ASGroupCfgInfo)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(DEL_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::RemoveASGroup(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgInfo.asgroups_size() <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(DEL_ASGRP);
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::GetASGroupConfig(ASGroupsCfg& ASGroupCfgInfo)
{
    int retVal = CMAPI_SUCCESS;
    ASFConfigReq Request;
    ASFConfigResp Response;

    Request.set_requestid(GET_ASGRP);
    // 0 indicates to get all AS Groups
    if (ASGroupCfgInfo.asgroups_size() > 0)
    {
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
    }
    

    retVal = SendCMgrRequest(Request, &Response, true);
    if (retVal == CMAPI_SUCCESS)
    {
        ASGroupCfgInfo.Clear();
        for (int idx=0; idx<Response.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = ASGroupCfgInfo.add_asgroups();
            asgrp->CopyFrom(Response.asgroups(idx));
        }
        if(Response.asgroups_size() == 0)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    else
    {
        if(Response.errordetails_size())
        {
            m_cErr.CopyFrom(Response.errordetails(0));
        }
    }

    return retVal;
}

int CMApiComponents::GetASGroupConfig(ASGroupsCfg& ASGroupCfgInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    ASFConfigReq Request;
    ASFConfigResp Response;

    Request.set_requestid(GET_ASGRP);
    // 0 indicates to get all AS Groups
    if (ASGroupCfgInfo.asgroups_size() > 0)
    {
        for (int idx=0; idx<ASGroupCfgInfo.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = Request.add_asgroups();
            asgrp->CopyFrom(ASGroupCfgInfo.asgroups(idx));
        }
    }
    

    retVal = SendCMgrRequest(Request, &Response, true);
    if (retVal == CMAPI_SUCCESS)
    {
        ASGroupCfgInfo.Clear();
        for (int idx=0; idx<Response.asgroups_size();idx++)
        {
            ASGroupCfg* asgrp = ASGroupCfgInfo.add_asgroups();
            asgrp->CopyFrom(Response.asgroups(idx));
        }
        if(Response.asgroups_size() == 0)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    else
    {
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }

    return retVal;
}

int CMApiComponents::SetASFAppResponseTimeout(int AppRespTimeout)
{
    int retVal = CMAPI_SUCCESS;

    if (AppRespTimeout <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(SET_ASF);
        ASFConfiguration *asf = Request.mutable_asfinfo();
        asf->set_appresponsetimeout(AppRespTimeout);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASFAppResponseTimeout(int AppRespTimeout, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (AppRespTimeout <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(SET_ASF);
        ASFConfiguration *asf = Request.mutable_asfinfo();
        asf->set_appresponsetimeout(AppRespTimeout);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::GetASFAppResponseTimeout(int& AppRespTimeout)
{
    int retVal = CMAPI_SUCCESS;
    ASFConfigReq Request;
    ASFConfigResp Response;
    Request.set_requestid(GET_ASF);
    retVal = SendCMgrRequest(Request, &Response, true);
    if (Response.has_asfinfo())
    {
        ASFConfiguration asf = Response.asfinfo();
        if (asf.has_appresponsetimeout())
            AppRespTimeout = asf.appresponsetimeout();

        if(Response.errordetails_size())
        {
            m_cErr.CopyFrom(Response.errordetails(0));
        }
    }
    else
    {
        if(Response.errordetails_size())
        {
            m_cErr.CopyFrom(Response.errordetails(0));
        }
    }
    return retVal;
}

int CMApiComponents::GetASFAppResponseTimeout(int& AppRespTimeout, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    ASFConfigReq Request;
    ASFConfigResp Response;
    Request.set_requestid(GET_ASF);
    retVal = SendCMgrRequest(Request, &Response, true);
    if (Response.has_asfinfo())
    {
        ASFConfiguration asf = Response.asfinfo();
        if (asf.has_appresponsetimeout())
            AppRespTimeout = asf.appresponsetimeout();

        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    else
    {
        if(Response.errordetails_size())
        {
            err.CopyFrom(Response.errordetails(0));
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupPriority(string ASGroupName, int Priority)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty() || Priority <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_priority(Priority);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupPriority(string ASGroupName, int Priority, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty() || Priority <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_priority(Priority);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupToHostedType(string ASGroupName)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_ishostedapp(true);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupToHostedType(string ASGroupName, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_ishostedapp(true);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupToExternalType(string ASGroupCfgName)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupCfgName);
        asgrp->set_ishostedapp(false);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupToExternalType(string ASGroupCfgName, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupCfgName);
        asgrp->set_ishostedapp(false);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupMaxInstances(string ASGroupName, int MaxInstances)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty() || MaxInstances <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_maxappinstances(MaxInstances);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupMaxInstances(string ASGroupName, int MaxInstances, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupName.empty() || MaxInstances <= 0)
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupName);
        asgrp->set_maxappinstances(MaxInstances);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupLBAlgorithm(string ASGroupCfgName, LBAlgorithm& LBAlgo)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgName.empty() || !LBAlgo.has_lbmethod())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupCfgName);
        LBAlgorithm *algo = asgrp-> mutable_lbalgo();
        algo->CopyFrom(LBAlgo);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                m_cErr.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::SetASGroupLBAlgorithm(string ASGroupCfgName, LBAlgorithm& LBAlgo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;

    if (ASGroupCfgName.empty() || !LBAlgo.has_lbmethod())
    {
        retVal = CMAPI_INVALIDPARAMS;
        // Fill ErrorDetails here

    } else {
        ASFConfigReq Request;
        ASFConfigResp Response;
        Request.set_requestid(MOD_ASGRP);
        ASGroupCfg* asgrp = Request.add_asgroups();
        asgrp->set_appgroup(ASGroupCfgName);
        LBAlgorithm *algo = asgrp-> mutable_lbalgo();
        algo->CopyFrom(LBAlgo);
        retVal = SendCMgrRequest(Request, &Response);
        if(retVal != CMAPI_SUCCESS)
        {
            if(Response.errordetails_size())
            {
                err.CopyFrom(Response.errordetails(0));
            }
        }
    }
    return retVal;
}

int CMApiComponents::GetLastCallErrorDetails(ErrorDetails& Err)
{
    int retVal = CMAPI_SUCCESS;
    Err.CopyFrom(m_cErr);
    return retVal;
}

int CMApiComponents::SendASFConfigResult(ASFConfigResp *Resp, CMAPIRes *result)
{
    string strVal;
    if (Resp != NULL)
    {
        Resp->SerializeToString(&strVal);
        result->set_responsecode(CMAPI_SUCCESS);
    } else {
        ASFConfigResp ErrorResponse;
        ErrorResponse.set_responseid(CMAPI_SRVERROR);
        //Fill ErrorDetails here
        ErrorResponse.SerializeToString(&strVal);
    }
    // Indicate Response from CMGR
    m_CMgrResponse->Set(strVal);
    return 0;
}


