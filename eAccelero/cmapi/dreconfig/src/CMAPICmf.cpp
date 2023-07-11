/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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

#include "ErrorResp.h"
#include "CMAPICmf.h"
#include "ComponentDefines.h"

int CMAPICMFConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > CMAPICMFConfig: InitializeLibrary\n");

    CLOG_DEBUG("InitializeLibrary: Initializing Config Manager Interface");
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CMgrCMFCallerObj = new Stub::CMgrCMFConfig(dest, 0);
    Stub::CMgrCMFConfigRespCbk::RegisterCMgrCMFConfigRespHandler();

    MeSSEndpoint dest1 = {COMP_DRE_APP, 0};
    m_cmfStatsObj = new Stub::CMFStats(dest1,0);
    Stub::CMFStatsRespCbk::RegisterCMFStatsRespHandler();

    m_CMAPIResponse = new CMAPIIntSync();

    CLOG_DEBUG(" < CMAPICMFConfig: InitializeLibrary\n");
    return retVal;
}

int CMAPICMFConfig::GetCMFPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    Req.set_requestid(GET_CMF_DIA_PRIORITY);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchCMFPriorityConfiguration(Req,
            new CMAPICookie(GET_CMF_DIA_PRIORITY, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFActionsAndTriggers(CMFActionTriggerReq& Req, CMFActionTriggerResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    Req.set_requestid(GET_CMF_ACTIONS_AND_TRIGGERS);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchCMFActionsForTrigger(Req,
            new CMAPICookie(GET_CMF_ACTIONS_AND_TRIGGERS, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFLevels(CMFLevelReq& Req, CMFLevelResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    Req.set_requestid(GET_CMF_LEVEL);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchAllCMFLevels(Req,
            new CMAPICookie(GET_CMF_LEVEL, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFTriggers(string& TriggerName, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    CMFTriggerReq Req;
    Req.set_requestid(GET_CMF_TRIGGER);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchAllCMFTriggers(Req,
            new CMAPICookie(GET_CMF_TRIGGER, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFActions(string& ActionName, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    CMFActionReq Req;
    if(!ActionName.empty())
        Req.add_actionnames(ActionName);
    Req.set_requestid(GET_CMF_ACTION);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchAllCMFActions(Req,
            new CMAPICookie(GET_CMF_ACTION, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFRules(string& RuleName, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    RuleConfigReq Req;
    if(!RuleName.empty())
    {
        RuleConfig* pRuleConfig = Req.add_rules();
        pRuleConfig->set_rulename(RuleName);
    }
    Req.set_requestid(GET_CMF_RULE);
    m_SendSuccess = true;

    // Call CMGR Method Implementation
    m_CMgrCMFCallerObj->FetchCMFRuleConfiguration(Req,
            new CMAPICookie(GET_CMF_RULE, (void *) &Req));
    std::string StrVal;
    //DRECfgResp Response;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //DRECfgResp Response;
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }


    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::AddCMFRule(RuleConfigReq& Req, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized() ||
            Req.rules_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPICMFConfig::AddCMFRule Invalid Params");
    }
    else
    {
        Req.set_requestid(ADD_CMF_RULE);
        CLOG_DEBUG(">CMAPICMFConfig:  ADD_CMF_RULE Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetRuleConfig(Req,
                new CMAPICookie(ADD_CMF_RULE, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::ModifyCMFRule(RuleConfigReq& Req, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized() ||
            Req.rules_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::ModifyCMFRule Invalid Params");
    }
    else
    {
        Req.set_requestid(MODIFY_CMF_RULE);
        CLOG_DEBUG(">CMAPICMFConfig:  MODIFY_CMF_RULE Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetRuleConfig(Req,
                new CMAPICookie(MODIFY_CMF_RULE, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::DeleteCMFRule(string& RuleName, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (RuleName.empty())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::DeleteCMFRule Invalid Params");
    }
    else
    {
        RuleConfigReq Req;
        RuleConfig *pRuleConfig = Req.add_rules();
        pRuleConfig->set_rulename(RuleName);
        Req.set_requestid(DELETE_CMF_RULE);
        CLOG_DEBUG(">CMAPICMFConfig: DELETE_CMF_RULE Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleDeleteRuleConfig(Req,
                new CMAPICookie(DELETE_CMF_RULE, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::SetCMFRuleStatus(RuleConfigReq& Req, RuleConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized() ||
            Req.rules_size() <= 0 )
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetCMFRuleStatus Invalid Params");
    }
    else
    {
        Req.set_requestid(SET_CMF_RULE_STATUS);
        CLOG_DEBUG(">CMAPICMFConfig: SET_CMF_RULE_STATUS Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetRuleConfig(Req,
                new CMAPICookie(SET_CMF_RULE_STATUS, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::ModifyPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::ModifyPriorityConfig Invalid Params");
    }
    else
    {
        Req.set_requestid(MOD_CMF_DIA_PRIORITY);

        CLOG_DEBUG(">CMAPICMFConfig:  Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetPriorityConfig(Req,
                new CMAPICookie(MOD_CMF_DIA_PRIORITY, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::DeletePriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::deletePriorityConfig Invalid Params");
    }
    else
    {
        Req.set_requestid(DEL_CMF_DIA_PRIORITY);

        CLOG_DEBUG(">CMAPICMFConfig:  Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetPriorityConfig(Req,
                new CMAPICookie(DEL_CMF_DIA_PRIORITY, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::AddPriorityConfig(PriorityConfigReq& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::AddPriorityConfig Invalid Params");
    }
    else
    {
        Req.set_requestid(ADD_CMF_DIA_PRIORITY);

        CLOG_DEBUG(">CMAPICMFConfig:  Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetPriorityConfig(Req,
                new CMAPICookie(ADD_CMF_DIA_PRIORITY, (void *) &Req));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::SetCommandCodePriority(CCPriority& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetCommandCodePriority Invalid Params");
    }
    else
    {
        PriorityConfigReq lPriorityConfigReq;
        PriorityConfig *pPriorityConfig = lPriorityConfigReq.add_priorities();
        CCPriority *pCCPriority = pPriorityConfig->add_ccpriorities();
        if(Req.has_cmdcode())
        {
            pCCPriority->set_cmdcode(Req.cmdcode());
        }
        if(Req.has_priority())
        {
            pCCPriority->set_priority(Req.priority());
        }
        lPriorityConfigReq.set_requestid(SET_CMD_CODE_PRIORITY);

        CLOG_DEBUG(">CMAPICMFConfig: SET_CMD_CODE_PRIORITY Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetPriorityConfig(lPriorityConfigReq,
                new CMAPICookie(SET_CMD_CODE_PRIORITY, (void *) &lPriorityConfigReq));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::SetApplicationIdPriority(AppIdPriority& Req, PriorityConfigResp& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;

    if (!Req.IsInitialized())
    {
        retVal = CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">CMAPIProdConfig::SetApplicationIdPriority Invalid Params");
    }
    else
    {
        PriorityConfigReq lPriorityConfigReq;
        PriorityConfig *pPriorityConfig = lPriorityConfigReq.add_priorities();
        AppIdPriority *pAppIdPriority = pPriorityConfig->add_apppriorities();
        if(Req.has_appid())
        {
            pAppIdPriority->set_appid(Req.appid());
        }
        if(Req.has_priority())
        {
            pAppIdPriority->set_priority(Req.priority());
        }
        lPriorityConfigReq.set_requestid(SET_CMF_RULE_STATUS);
        CLOG_DEBUG(">CMAPICMFConfig: SET_APP_PRIORITY Request");
        // Call CMGR Method Implementation
        m_CMgrCMFCallerObj->HandleSetPriorityConfig(lPriorityConfigReq,
                new CMAPICookie(SET_APP_PRIORITY, (void *) &lPriorityConfigReq));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            ErrorDetails *err =Resp.add_errordetails();
            retVal = CMAPI_MESSERROR;
            CLOG_ERROR("Error: Mess Not Ready");
            err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            err->set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }
        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            ErrorDetails *err =Resp.add_errordetails();
            //DRECfgResp Response;
            Resp.ParseFromString(StrVal);
            retVal = Resp.responseid();
            if(Resp.errordetails_size())
            {
                err->CopyFrom(Resp.errordetails(0));
            }
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            ErrorDetails *err =Resp.add_errordetails();
            CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
            Resp.set_responseid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}


//Response Callbacks
int CMAPICMFConfig::HandleSetTemplateConfigReqsRespCbk(TemplateResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            TemplateResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::HandleGetTemplateConfigReqsRespCbk(TemplateResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            TemplateResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::HandleSetRuleConfigRespCbk(RuleConfigResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            RuleConfigResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::HandleDeleteRuleConfigRespCbk(RuleConfigResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            RuleConfigResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::HandleSetPriorityConfigRespCbk(PriorityConfigResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            PriorityConfigResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFRuleConfigurationRespCbk(RuleConfigResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            RuleConfigResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFPriorityConfigurationRespCbk(PriorityConfigResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            PriorityConfigResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchAllCMFTriggersRespCbk(CMFTriggerResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            CMFTriggerResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchAllCMFActionsRespCbk(CMFActionResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            CMFActionResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchAllCMFLevelsRespCbk(CMFLevelResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            CMFLevelResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFActionsForTriggerRespCbk(CMFActionTriggerResp *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            CMFActionTriggerResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::SendCMFPriorityConfigResult(PriorityConfigResp *Req, CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

int CMAPICMFConfig::SendDreTemplateConfigResult(TemplateResp *Req, CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;

}
int CMAPICMFConfig::SendCMFRuleConfigResult(RuleConfigResp *Req, CMAPIRes *Resp)
{
    CLOG_DEBUG("DREConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

int CMAPICMFConfig::GetSystemTriggerStates (TriggerStateRequest& Req, TriggerStateResponse& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    Req.set_requestid(GET_CMF_SYSTEM_TRIGGER_STATES);
    m_SendSuccess = true;

    // Call DRE Method Implementation
    m_cmfStatsObj->FetchCMFSystemTriggerStates(Req,
            new CMAPICookie(GET_CMF_SYSTEM_TRIGGER_STATES,(void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetDiaPeerTriggerStates(std::string peerName,std::string RealmName, PeerTriggerStateResponse& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    PeerTriggerStateRequest Req;
    Req.set_requestid(GET_CMF_PEER_TRIGGER_STATES);
    Req.set_peername(peerName);
    Req.set_realmname(RealmName);

    // Call DRE Method Implementation
    m_cmfStatsObj->FetchCMFDiaPeerTriggerStates(Req,
            new CMAPICookie(GET_CMF_PEER_TRIGGER_STATES,(void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetDiaRealmTriggerStates(std::string realmName, RealmTriggerStateResponse& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    RealmTriggerStateRequest Req;
    Req.set_requestid(GET_CMF_REALM_TRIGGER_STATES);
    Req.set_realmname(realmName);

    // Call DRE Method Implementation
    m_cmfStatsObj->FetchCMFDiaRealmTriggerStates(Req,
            new CMAPICookie(GET_CMF_REALM_TRIGGER_STATES,(void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::GetCMFLevelConfig(uint32_t  triggerID, CMFLevelConfigResponse& Resp)
{
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    m_SendSuccess = true;
    CMFLevelConfigRequest Req;
    Req.set_requestid(GET_CMF_LEVEL_CONFIG);
    Req.set_triggerid(triggerID);

    // Call DRE Method Implementation
    m_cmfStatsObj->FetchCMFLevelConfig(Req,
            new CMAPICookie(GET_CMF_LEVEL_CONFIG,(void *) &Req));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        CLOG_ERROR("Error: Mess Not Ready");
        Resp.set_responseid(retVal);
        ErrorDetails* err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        Resp.Clear();
        Resp.ParseFromString(StrVal);
        CLOG_DEBUG(" Resp: %s ",StrVal.c_str());
        CLOG_DEBUG(" Resp: %s ",Resp.DebugString().c_str());
        retVal = Resp.responseid();
    }
    else
    {
        Resp.set_responseid(CMAPI_TIMEOUT);
        CLOG_ERROR("Error: Condition wait time-out (CMAPI_TIMEOUT)");
        // Fill in errordetails in Response
        ErrorDetails *err = Resp.add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFSystemTriggerStatesRespCbk(TriggerStateResponse *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error  state is %d ",__FUNCTION__,MeSS::Handle().m_state);
        if (Resp == NULL )
        {
            TriggerStateResponse ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFDiaPeerTriggerStatesRespCbk(PeerTriggerStateResponse *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            PeerTriggerStateResponse ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}

int CMAPICMFConfig::FetchCMFDiaRealmTriggerStatesRespCbk(RealmTriggerStateResponse *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            RealmTriggerStateResponse ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}
int CMAPICMFConfig::FetchCMFLevelConfigRespCbk(CMFLevelConfigResponse *Resp)
{
    int retVal = 0;
    CLOG_DEBUG(" > %s ",__FUNCTION__);

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            Resp == NULL || Resp->responseid() != CMAPI_SUCCESS )
    {
        CLOG_ERROR(" %s : MeSS Error ",__FUNCTION__);
        if (Resp == NULL )
        {
            CMFLevelConfigResponse ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_responseid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            Resp->SerializeToString(&StrVal);
            CLOG_DEBUG(" Resp: %s ",Resp->DebugString().c_str());
        }
    }
    else
    {
        Resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie;

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    return retVal;
}
