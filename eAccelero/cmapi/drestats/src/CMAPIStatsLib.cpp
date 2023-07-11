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
#include "CMAPIStatsLib.h"
#include "ComponentDefines.h"
#include "CMgrMethods_caller.h"
#include "StackStats_caller.h"
#include "StackStats_def.h"
#include "InterfaceStat_caller.h"
#include "InterfaceStat_def.h"
#include "ErrorResp.h"


//#define CMGR_INSTANCE_ID  MESS_MIN_ACTIVE_INSTANCE
//#define DRE_INSTANCE_ID   MESS_MIN_ACTIVE_INSTANCE

int CMAPIStatsConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMAPIProdConfig: InitializeLibrary\n");

    CLOG_DEBUG("InitializeLibrary: Initializing DRE Application Interface");
    MeSSEndpoint Dredest = {COMP_DRE_APP, DRE_INSTANCE_ID};

    m_StackStatsObj = new Stub::StackStats(Dredest,0);
    Stub::StackStatsRespCbk::RegisterStackStatsRespHandler();

    m_InterfaceStatObj = new Stub::InterfaceStat(Dredest,0);
    Stub::InterfaceStatRespCbk::RegisterInterfaceStatRespHandler();

    m_CMAPIResponse = new CMAPIIntSync();

    return retVal;
}


int CMAPIStatsConfig::GetApplicationSpecificStats(ApplicationspecStatsReq& req, ApplicationspecStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(GET_APPSPECIFICSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::GetApplicationSpecificStats");

    m_StackStatsObj->FetchApplicationSpecificMessageStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("CMAPIStatsConfig::GetApplicationSpecificStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    std::string strVal;
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::GetApplicationSpecificStats : Response Received");
    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }
    resp.ParseFromString(strVal);
    retVal = resp.responseid();
    return retVal;
}

int CMAPIStatsConfig::GetStackIndicationStats(StackIndicationStatsReq& req, StackIndicationStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(GET_STACKINDICATIONSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::GetStackIndicationStats");

    m_StackStatsObj->FetchStackIndicationStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));
    CLOG_DEBUG("CMAPIStatsConfig::GetStackIndicationStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::GetStackIndicationStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             
    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::GetGenericErrorStats(GenericErrorStatsReq& req, GenericErrorStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(GET_GENERICERRORSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericErrorStats");

    m_StackStatsObj->FetchGenericErrorStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericErrorStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    std::string strVal;
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericErrorStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             
    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::GetGenericStats(GenericStatsReq& req, GenericStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(GET_GENERICSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericStats");

    m_StackStatsObj->FetchGenericStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }
    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::GetGenericStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             

    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::ResetApplicationspecStats(ResetApplicationspecStatsReq& req, ResetApplicationspecStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(RESET_APPSPECIFICSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::ResetApplicationspecStats");

    m_StackStatsObj->ResetApplicationSpecificMessageStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::ResetApplicationspecStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }
    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::ResetApplicationspecStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             

    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}


int CMAPIStatsConfig::ResetStackIndicationStats(ResetStackIndicationStatsReq& req, ResetStackIndicationStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(RESET_STACKINDICATIONSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::ResetStackIndicationStats");

    m_StackStatsObj->ResetStackIndicationStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::ResetStackIndicationStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }
    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::ResetStackIndicationStats : Response Received");

    (m_CMAPIResponse->Get(strVal));

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             

    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::ResetGenericErrorStats(ResetGenericErrorStatsReq& req, ResetGenericErrorStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(RESET_GENERICERRORSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericErrorStats");

    m_StackStatsObj->ResetGenericErrorStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericErrorStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }
    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericErrorStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             

    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::ResetGenericStats(ResetGenericStatsReq& req, ResetGenericStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    req.set_requestid(RESET_GENERICSTATS);

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericStats");

    m_StackStatsObj->ResetGenericStats(req,
            new CMAPICookie(req.requestid(), (void *) &req));

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericStats : Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }
    std::string strVal; 
    (m_CMAPIResponse->Get(strVal));

    CLOG_DEBUG("CMAPIStatsConfig::ResetGenericStats : Response Received");

    if(strVal.empty())
    {
        CLOG_ERROR("No Data in Response Received");
        return CMAPI_SRVERROR;
    }                                                                                             

    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}

int CMAPIStatsConfig::FetchApplicationSpecificMessageStatsRespCbk(ApplicationspecStatsResp *resp)
{
    std::string StrVal;
    CLOG_DEBUG("FetchApplicationSpecificMessageStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }

    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchApplicationSpecificMessageStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchApplicationSpecificMessageStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("FetchApplicationSpecificMessageStats : MeSS - Failed");
        ApplicationspecStatsResp errorResponse;
        errorResponse.set_responseid(CMAPI_MESSERROR);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::FetchStackIndicationStatsRespCbk(StackIndicationStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchStackIndicationStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchStackIndicationStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchStackIndicationStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("FetchStackIndicationStats : MeSS - Failed");
        StackIndicationStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::FetchGenericErrorStatsRespCbk(GenericErrorStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchGenericErrorStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchGenericErrorStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchGenericErrorStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("FetchGenericErrorStats : MeSS - Failed");
        GenericErrorStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::FetchGenericStatsRespCbk(GenericStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("FetchGenericStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("FetchGenericStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("FetchGenericStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("FetchGenericStats : MeSS - Failed");
        GenericStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::ResetApplicationSpecificMessageStatsRespCbk(ResetApplicationspecStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("ResetApplicationSpecificMessageStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("ResetApplicationSpecificMessageStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("ResetApplicationSpecificMessageStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("ResetApplicationSpecificMessageStats : MeSS - Failed");
        ResetApplicationspecStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::ResetStackIndicationStatsRespCbk(ResetStackIndicationStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("ResetStackIndicationStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("ResetStackIndicationStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("ResetStackIndicationStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("ResetStackIndicationStats : MeSS - Failed");
        ResetStackIndicationStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::ResetGenericErrorStatsRespCbk(ResetGenericErrorStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("ResetGenericErrorStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("ResetGenericErrorStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("ResetGenericErrorStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("ResetGenericErrorStats : MeSS - Failed");
        ResetGenericErrorStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::ResetGenericStatsRespCbk(ResetGenericStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("ResetGenericStatsRespCbk");

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS && resp != NULL)
    {
        if (resp->responseid() == CMAPI_SUCCESS)
        {
            CLOG_DEBUG("ResetGenericStats : DRE operation - Successful");
            resp->SerializeToString(&StrVal);
        }
        else
        {
            CLOG_ERROR("ResetGenericStats : DRE operation - Failed");
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        CLOG_DEBUG("ResetGenericStats : MeSS - Failed");
        ResetGenericStatsResp errorResponse;
        retVal = CMAPI_SRVERROR;
        errorResponse.set_responseid(retVal);
        errorResponse.SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);


    return 0;
}

int CMAPIStatsConfig::GetInterfaceStats(InterfaceStatsReq& req, InterfaceStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    std::string strVal;

    CLOG_DEBUG("CMAPIStatsConfig::GetInterfaceStats");
    req.set_requestid(GET_INTERFACESTATS);


    CLOG_DEBUG("Sending GetInterfaceStats Request ");

    m_InterfaceStatObj->FetchInterfaceStats(req);
    CLOG_DEBUG("GetInterfaceStats: Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("GetInterfaceStats: Response Received");
    if(strVal.empty())
    {
        return CMAPI_SRVERROR;
    }
    resp.ParseFromString(strVal);
    if (resp.has_responseid())
    {
        retVal = resp.responseid();
    }
    return retVal;
}

int CMAPIStatsConfig::ResetInterfaceStats(InterfaceStatsReq& req, ResetInterfaceStatsResp& resp)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    std::string strVal;

    CLOG_DEBUG("CMAPIStatsConfig::GetInterfaceStats");
    req.set_requestid(RESET_INTERFACESTATS);

    CLOG_DEBUG("Sending ResetInterfaceStats Request ");

    m_InterfaceStatObj->ResetInterfaceStats(req);
    CLOG_DEBUG("ResetInterfaceStats: Waiting for Response");

    if (m_SendSuccess == false)
    {
        ::ErrorDetails* Err = resp.add_errordetails();
        Err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        Err->set_errormsgkey("config.common.mess.not.ready");
        retVal = CMAPI_MESSERROR;
        resp.set_responseid(retVal);
        m_SendSuccess = true;
        return retVal;
    }

    (m_CMAPIResponse->Get(strVal));
    CLOG_DEBUG("ResetInterfaceStats: Response Received");
    if(strVal.empty())
    {
        resp.set_responseid(CMAPI_ERROR);
        return CMAPI_SRVERROR;
    }
    resp.ParseFromString(strVal);
    retVal = resp.responseid();

    return retVal;
}


int CMAPIStatsConfig::IsResponseOK(InterfaceStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIStatsConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        InterfaceStatsResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);

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
    }
    return retVal;
}


int CMAPIStatsConfig::IsResponseOK(ResetInterfaceStatsResp *Resp)
{
    int retVal = CMAPI_SUCCESS;
    std::string StrVal;
    CLOG_DEBUG("CMAPIStatsConfig: IsResponseOK");
    if ( ( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Resp == NULL )
    {
        CLOG_DEBUG("IsResponseOK: CMAPI  Error ");
        ResetInterfaceStatsResp ErrResp;
        ErrResp.set_responseid(CMAPI_ERROR);

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
    }
    return retVal;
}

int CMAPIStatsConfig::FetchInterfaceStatsRespCbk(InterfaceStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    retVal = IsResponseOK(resp);
    if(retVal == CMAPI_SUCCESS)
    {
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
    return 0;
}

int CMAPIStatsConfig::ResetInterfaceStatsRespCbk(ResetInterfaceStatsResp *resp)
{
    int retVal = CMAPI_SUCCESS;

    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {   
        m_SendSuccess = false;
        return 0;
    }
    retVal = IsResponseOK(resp);
    if(retVal == CMAPI_SUCCESS)
    {
        std::string StrVal;
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
    return 0;
}

