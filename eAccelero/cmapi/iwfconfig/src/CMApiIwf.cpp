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
#include "ComponentDefines.h"
#include "CMApiIwf.h"
#include "iwfconfig_def.h"
#include "CMgrIwfMethods_caller.h"
#include "IwfSigtranMethods_caller.h"
#include "iwfconfig.h"
#include "IwfConfigResults_caller.h"

int CMApiIwfConfig::InitializeLibrary()
{
    int retVal = CMAPI_SUCCESS;

    CLOG_DEBUG(">CMApiIwfConfig: InitializeLibrary\n");
    CLOG_DEBUG("InitializeLibrary: Initializing Config Manager Interface");
    MeSSEndpoint dest = {COMP_CONFIG_MANAGER, CMGR_INSTANCE_ID};
    m_CMgrCallerObj = new Stub::CMgrIwfMethods(dest, 0);  
    Stub::CMgrIwfMethodsRespCbk::RegisterCMgrIwfMethodsRespHandler();

    //This Interface can be used in future for IWF application
    CLOG_DEBUG("InitializeLibrary: Initializing IWF Application Interface");
    //MeSSEndpoint Iwfdest = {COMP_IWF_APP, IWF_INSTANCE_ID};

    m_CMAPIResponse = new CMAPIIntSync();

    return retVal;
}

int CMApiIwfConfig::GetLastCallErrorDetails(ErrorDetails& Err)
{

    Err.CopyFrom(m_lastError);
    return 0;
}

int CMApiIwfConfig::GetLocalHostConfig(IwfLocalHostConfig& LocalHost, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetLocalHostConfig "); 
    IwfLocalHostsConfig lHost;
    lHost.set_operreqid(GET_LOCAL_HOST);

    CLOG_DEBUG("Sending Locahost Host Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
            new CMAPICookie(GET_LOCAL_HOST, (void *) &lHost));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_localhostinfo())
    {
        LocalHost.CopyFrom(Response.localhostinfo().localhostinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetLocalHostConfig(IwfLocalHostConfig& LHostInfo,IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">SetLocalHostSSN : ERROR: Invalid Parameters");
    }
    else
    {
        IwfLocalHostsConfig lHost;
        lHost.set_operreqid(SET_LOCAL_HOST);
        IwfLocalHostConfig *localHost = lHost.mutable_localhostinfo();
        localHost->CopyFrom(LHostInfo);
        CLOG_DEBUG("Sending SET_HOST for LocalHostConfig");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(SET_LOCAL_HOST, (void *) &lHost ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyLocalHostConfig(IwfLocalHostConfig& LHostInfo,IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!LHostInfo.IsInitialized())
    {
        retVal = (int) CMAPI_INVALIDPARAMS;
        CLOG_DEBUG(">ModifyLocalHostSSN : ERROR: Invalid Parameters");
    }
    else
    {
        IwfLocalHostsConfig lHost;
        lHost.set_operreqid(MOD_LOCAL_HOST);
        IwfLocalHostConfig *localHost = lHost.mutable_localhostinfo();
        localHost->CopyFrom(LHostInfo);
        CLOG_DEBUG("Sending MOD_HOST for LocalHostConfig");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(MOD_LOCAL_HOST, (void *) &lHost ));
        std::string StrVal;
	if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteLocalHostSSN(IwfLocalHostConfig& LHostInfo,IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">DeleteLocalHostSSN ");
    if (!LHostInfo.IsInitialized())
    {
        CLOG_DEBUG(">DeleteLocalHostSSN : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        // Build Request Information
        IwfLocalHostsConfig lHost;
        lHost.set_operreqid(DEL_LOCAL_HOST_SSN);
        IwfLocalHostConfig *localHost = lHost.mutable_localhostinfo();
        localHost->CopyFrom(LHostInfo);
        IwfLocalSSNConfig lSsn = LHostInfo.ssn_config(0);

        CLOG_DEBUG("Sending DEL_LOCAL_HOST_SSN request for Local Host SSN : - %d", lSsn.ssn());

        // Call CMgr Method Implementation. 
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(DEL_LOCAL_HOST_SSN, (void *) &lHost));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // return
    return retVal;
}

int CMApiIwfConfig::SetLocalHostInvokeTimer(int Time, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">SetLocalHostInvokeTimers ");
    if ( Time <= 0)
    {
        CLOG_DEBUG(">SetLocalHost Invoke Timer : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfLocalHostsConfig lHost;
        lHost.set_operreqid(SET_LOCAL_INVK_TIMER);
        IwfLocalHostConfig *localHost = lHost.mutable_localhostinfo();
        localHost->set_tcapinvoketimer(Time);

        CLOG_DEBUG(">SetLocalHost Invoke Timer : INVOKE Timers %d ", Time);
        // Call CMgr Method Implementation. 
        m_CMgrCallerObj->HandleSetLocalHostConfigReqs(lHost,
                new CMAPICookie(SET_LOCAL_INVK_TIMER, (void *) &lHost));
        std::string StrVal;
	if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }

    }

    // Return
    return retVal;
}

int CMApiIwfConfig::GetDestination(IwfSigtranDestinationsConfig& DestInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetDestinationConfig"); 
    DestInfo.set_operreqid(GET_SIGTRAN_DEST);

    CLOG_DEBUG("Sending Destination Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetDestinationConfigReqs(DestInfo,
            new CMAPICookie(GET_SIGTRAN_DEST, (void *) &DestInfo));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_destionationinfo())
    {
        DestInfo.CopyFrom(Response.destionationinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if ( DestInfo.destioninfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetDestinationConfig : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DestInfo.set_operreqid(SET_SIGTRAN_DEST);
        CLOG_DEBUG("Sending SET_SIGTRAN_DEST for DestinationConfig");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetDestinationConfigReqs(DestInfo,
                new CMAPICookie(SET_SIGTRAN_DEST, (void *) &DestInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;

    if ( DestInfo.destioninfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyDestinationConfig : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DestInfo.set_operreqid(MOD_SIGTRAN_DEST);
        CLOG_DEBUG("Sending SET_SIGTRAN_DEST for DestinationConfig");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetDestinationConfigReqs(DestInfo,
                new CMAPICookie(MOD_SIGTRAN_DEST, (void *) &DestInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteDestination(IwfSigtranDestinationsConfig& DestInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if ( DestInfo.destioninfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetDestinationConfig : ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DestInfo.set_operreqid(DEL_SIGTRAN_DEST);
        CLOG_DEBUG("Sending DEL_SIGTRAN_DEST for DestinationConfig");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetDestinationConfigReqs(DestInfo,
                new CMAPICookie(DEL_SIGTRAN_DEST, (void *) &DestInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetAssociationSetConfig"); 
    AssocSet.set_operreqid(GET_ASSOC_SET);

    CLOG_DEBUG("Sending AssociationSet Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetAssociationSetConfigReqs(AssocSet,
            new CMAPICookie(GET_ASSOC_SET, (void *) &AssocSet));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_associationsetinfo())
    {
        AssocSet.CopyFrom(Response.associationsetinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocSet.associationsetinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetAssociationSetConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocSet.set_operreqid(SET_ASSOC_SET);
        CLOG_DEBUG("Sending SET_ASSOC_SET for Association Set");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationSetConfigReqs(AssocSet,
                new CMAPICookie(SET_ASSOC_SET, (void *) &AssocSet ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocSet.associationsetinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyAssociationSetConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocSet.set_operreqid(MOD_ASSOC_SET);
        CLOG_DEBUG("Sending MOD_ASSOC_SET for Association Set");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationSetConfigReqs(AssocSet,
                new CMAPICookie(MOD_ASSOC_SET, (void *) &AssocSet ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocSet.associationsetinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteAssociationSetConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocSet.set_operreqid(DEL_ASSOC_SET);
        CLOG_DEBUG("Sending DEL_ASSOC_SET for Association Set");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationSetConfigReqs(AssocSet,
                new CMAPICookie(MOD_ASSOC_SET, (void *) &AssocSet ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ActivateAssociationSet(IwfSigtranAssociationSetsConfig& AssocSet, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocSet.associationsetinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ActivateAssociationSetConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocSet.set_operreqid(ACTIVATE_ASSOC_SET);
        CLOG_DEBUG("Sending ACTIVATE_ASSOC_SET for Association Set");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationSetConfigReqs(AssocSet,
                new CMAPICookie(ACTIVATE_ASSOC_SET, (void *) &AssocSet ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetAssociation(IwfSigtranAssociationsConfig& AssocInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetAssociation"); 
    AssocInfo.set_operreqid(GET_ASSOC);

    CLOG_DEBUG("Sending Association Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetAssociationConfigReqs(AssocInfo,
            new CMAPICookie(GET_ASSOC, (void *) &AssocInfo));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_associationinfo())
    {
        AssocInfo.CopyFrom(Response.associationinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocInfo.associationinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetAssociation: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocInfo.set_operreqid(SET_ASSOC);
        CLOG_DEBUG("Sending SET_ASSOC for Association ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationConfigReqs(AssocInfo,
                new CMAPICookie(SET_ASSOC, (void *) &AssocInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ActivateAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocInfo.associationinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ActivateAssociation: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocInfo.set_operreqid(ACTIVATE_ASSOC);
        CLOG_DEBUG("Sending ACTIVATE_ASSOC for Association ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationConfigReqs(AssocInfo,
                new CMAPICookie(ACTIVATE_ASSOC, (void *) &AssocInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocInfo.associationinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyAssociation: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocInfo.set_operreqid(MOD_ASSOC);
        CLOG_DEBUG("Sending MOD_ASSOC for Association ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationConfigReqs(AssocInfo,
                new CMAPICookie(MOD_ASSOC, (void *) &AssocInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteAssociation(IwfSigtranAssociationsConfig& AssocInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( AssocInfo.associationinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteAssociation: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        AssocInfo.set_operreqid(DEL_ASSOC);
        CLOG_DEBUG("Sending DEL_ASSOC for Association ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetAssociationConfigReqs(AssocInfo,
                new CMAPICookie(DEL_ASSOC, (void *) &AssocInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfSctpEndPoint"); 
    SctpEndPoint.set_operreqid(GET_SCTP_ENDPOINT);

    CLOG_DEBUG("Sending SctpEndPoint Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetSctpEndPointConfigReqs(SctpEndPoint,
            new CMAPICookie(GET_SCTP_ENDPOINT, (void *) &SctpEndPoint));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_sctpendpointinfo())
    {
        SctpEndPoint.CopyFrom(Response.sctpendpointinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpEndPoint.sctpendpointinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetIwfSctpEndPoint: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpEndPoint.set_operreqid(SET_SCTP_ENDPOINT);
        CLOG_DEBUG("Sending SET_SCTP_ENDPOINT for EndPoint configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpEndPointConfigReqs(SctpEndPoint,
                new CMAPICookie(SET_SCTP_ENDPOINT, (void *) &SctpEndPoint ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpEndPoint.sctpendpointinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfSctpEndPoint: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpEndPoint.set_operreqid(MOD_SCTP_ENDPOINT);
        CLOG_DEBUG("Sending MOD_SCTP_ENDPOINT for Sctp Endpoint configuration");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpEndPointConfigReqs(SctpEndPoint,
                new CMAPICookie(MOD_SCTP_ENDPOINT, (void *) &SctpEndPoint ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfSctpEndPoint(IwfSigtranSctpEndPointsConfig& SctpEndPoint, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpEndPoint.sctpendpointinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfSctpEndPoint: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpEndPoint.set_operreqid(DEL_SCTP_ENDPOINT);
        CLOG_DEBUG("Sending DEL_SCTP_ENDPOINT for Sctp Endpoint configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpEndPointConfigReqs(SctpEndPoint,
                new CMAPICookie(DEL_SCTP_ENDPOINT, (void *) &SctpEndPoint ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfSigtranSctpProfileConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfSctpProfile"); 
    SctpInfo.set_operreqid(GET_SCTP_PROFILE);

    CLOG_DEBUG("Sending SctpEndProfile Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetSctpProfileConfigReqs(SctpInfo,
            new CMAPICookie(GET_SCTP_PROFILE, (void *) &SctpInfo));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_sctpprofileinfo())
    {
        SctpInfo.CopyFrom(Response.sctpprofileinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpInfo.sctpprofileinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetSctpProfile: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpInfo.set_operreqid(SET_SCTP_PROFILE);
        CLOG_DEBUG("Sending SET_SCTP_PROFILE for sctp profile configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpProfileConfigReqs(SctpInfo,
                new CMAPICookie(SET_SCTP_PROFILE, (void *) &SctpInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifySctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpInfo.sctpprofileinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfSctpProfile: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpInfo.set_operreqid(MOD_SCTP_PROFILE);
        CLOG_DEBUG("Sending MOD_SCTP_PROFILE for sctp profile configuration");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpProfileConfigReqs(SctpInfo,
                new CMAPICookie(MOD_SCTP_PROFILE, (void *) &SctpInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteSctpProfile(IwfSigtranSctpProfilesConfig& SctpInfo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( SctpInfo.sctpprofileinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfSctpProfile: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        SctpInfo.set_operreqid(DEL_SCTP_PROFILE);
        CLOG_DEBUG("Sending DEL_SCTP_PROFILE for sctp profile configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpProfileConfigReqs(SctpInfo,
                new CMAPICookie(DEL_SCTP_PROFILE, (void *) &SctpInfo ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetSigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfSigtranSctpProfileConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetSigtranMultihoming"); 
    IwfMultihoming.set_operreqid(GET_SIG_MULTIHOMING);

    CLOG_DEBUG("Sending SigtranMultihoming Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetSigtranMultihomingConfigReqs(IwfMultihoming,
            new CMAPICookie(GET_SIG_MULTIHOMING, (void *) &IwfMultihoming));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_multihominginfo())
    {
        IwfMultihoming.CopyFrom(Response.multihominginfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal; 
}

int CMApiIwfConfig::SetSigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( IwfMultihoming.multihominginfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetSigtranMultihoming: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfMultihoming.set_operreqid(SET_SIG_MULTIHOMING);
        CLOG_DEBUG("Sending SET_SIG_MULTIHOMING for sigtran multihoming configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSigtranMultihomingConfigReqs(IwfMultihoming,
                new CMAPICookie(SET_SIG_MULTIHOMING, (void *) &IwfMultihoming ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifySigtranMultihoming(IwfSigtransMultihomingConfig& IwfMultihoming, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( IwfMultihoming.multihominginfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifySigtranMultihoming: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfMultihoming.set_operreqid(MOD_SIG_MULTIHOMING);
        CLOG_DEBUG("Sending MOD_SIG_MULTIHOMING for sigtran multihoming configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSigtranMultihomingConfigReqs(IwfMultihoming,
                new CMAPICookie(MOD_SIG_MULTIHOMING, (void *) &IwfMultihoming ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteSigtranMultihoming(IwfSigtranSctpEndPointsConfig& IwfMultihoming, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( IwfMultihoming.sctpendpointinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteSigtranMultihoming: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfMultihoming.set_operreqid(DEL_AND_ADD_SIG_MULTIHOMING);
        CLOG_DEBUG("Sending DEL_AND_ADD_SIG_MULTIHOMING for sigtran multihoming configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetSctpEndPointConfigReqs(IwfMultihoming,
                new CMAPICookie(DEL_AND_ADD_SIG_MULTIHOMING, (void *) &IwfMultihoming ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetRemoteRoute"); 
    RemoteRoute.set_operreqid(GET_REMOTE_ROUTE);

    CLOG_DEBUG("Sending RemoteRoute Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetRemoteRouteConfigReqs(RemoteRoute,
            new CMAPICookie(GET_REMOTE_ROUTE, (void *) &RemoteRoute));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_remoterouteinfo())
    {
        RemoteRoute.CopyFrom(Response.remoterouteinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( RemoteRoute.remoterouteinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetRemoteRoute: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        RemoteRoute.set_operreqid(SET_REMOTE_ROUTE);
        CLOG_DEBUG("Sending SET_REMOTE_ROUTE for RoutingConfig ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetRemoteRouteConfigReqs(RemoteRoute,
                new CMAPICookie(SET_REMOTE_ROUTE, (void *) &RemoteRoute ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( RemoteRoute.remoterouteinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyRemoteRoute: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        RemoteRoute.set_operreqid(MOD_REMOTE_ROUTE);
        CLOG_DEBUG("Sending MOD_REMOTE_ROUTE for RoutingConfig ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetRemoteRouteConfigReqs(RemoteRoute,
                new CMAPICookie(MOD_REMOTE_ROUTE, (void *) &RemoteRoute ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteRemoteRoute(IwfSigtranRemoteRoutesConfig& RemoteRoute, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( RemoteRoute.remoterouteinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteRemoteRoute: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        RemoteRoute.set_operreqid(DEL_REMOTE_ROUTE);
        CLOG_DEBUG("Sending DEL_REMOTE_ROUTE for RoutingConfig ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetRemoteRouteConfigReqs(RemoteRoute,
                new CMAPICookie(DEL_REMOTE_ROUTE, (void *) &RemoteRoute ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetTranslatorRules(IwfTranslatorRulesConfig& Rule, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetTranslatorRule"); 
    Rule.set_operreqid(GET_TRANSLATOR_RULE);

    CLOG_DEBUG("Sending Translator Rule Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslatorRuleConfigReqs(Rule,
            new CMAPICookie(GET_TRANSLATOR_RULE, (void *) &Rule));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translatorrulesinfo())
    {
        Rule.CopyFrom(Response.translatorrulesinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">SetTranslatorVplmnIds: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(SET_VPLMN_ID);
        CLOG_DEBUG("Sending SET_VPLMN_ID for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(SET_VPLMN_ID, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">ModTranslatorVplmnIds: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(MOD_VPLMN_ID);
        CLOG_DEBUG("Sending MOD_VPLMN_ID for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(MOD_VPLMN_ID, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteTranslatorVplmnIds(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">DeleteTranslatorVplmnIds: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(DEL_VPLMN_ID);
        CLOG_DEBUG("Sending DEL_VPLMN_ID for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(DEL_VPLMN_ID, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">SetTranslatorRule: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(SET_TRANSLATOR_RULE);
        CLOG_DEBUG("Sending SET_TRANSLATOR_RULE for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(SET_TRANSLATOR_RULE, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">ModifyTranslatorRule: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(MOD_TRANSLATOR_RULE);
        CLOG_DEBUG("Sending MOD_TRANSLATOR_RULE for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(MOD_TRANSLATOR_RULE, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}


int CMApiIwfConfig::DeleteTranslatorRules(IwfTranslatorRulesConfig& Rule, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Rule.ruleinfo_size() <= 0)
    {
        CLOG_DEBUG(">DeleteTranslatorRule: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Rule.set_operreqid(DEL_TRANSLATOR_RULE);
        CLOG_DEBUG("Sending DEL_TRANSLATOR_RULE for Translator rules");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslatorRuleConfigReqs(Rule,
                new CMAPICookie(DEL_TRANSLATOR_RULE, (void *) &Rule ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a S6aToMap Request
    CLOG_DEBUG(">CMApiIwfConfig: GetS6aMapTranslationData"); 
    IwfTranslationDataConfig TransData;
    TransData.set_operreqid(GET_S6AMAP_DATA);

    CLOG_DEBUG("Sending GET_S6AMAP Translation data Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslationDataConfigReqs(TransData,
            new CMAPICookie(GET_S6AMAP_DATA, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translationdatainfo())
    {
        if(Response.translationdatainfo().has_s6atomapinfo())
        {
            S6aMap.CopyFrom(Response.translationdatainfo().s6atomapinfo());
        }
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!S6aMap.IsInitialized())
    {
        CLOG_DEBUG(">SetS6aMapTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(SET_S6AMAP_DATA);
        IwfS6aToMapConfig* s6amap = TransData.mutable_s6atomapinfo();
        s6amap->CopyFrom(S6aMap);
        CLOG_DEBUG("Sending SET_S6AMAP_DATA for S6aToMap Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_S6AMAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!S6aMap.IsInitialized())
    {
        CLOG_DEBUG(">ModifyS6aMapTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(MOD_S6AMAP_DATA);
        IwfS6aToMapConfig* s6amap = TransData.mutable_s6atomapinfo();
        s6amap->CopyFrom(S6aMap);
        CLOG_DEBUG("Sending MOD_S6AMAP_DATA for S6aToMap Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_S6AMAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteS6aMapTranslationData(IwfS6aToMapConfig& S6aMap, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!S6aMap.IsInitialized())
    {
        CLOG_DEBUG(">DeleteS6aMapTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(DEL_S6AMAP_DATA);
        IwfS6aToMapConfig* s6amap = TransData.mutable_s6atomapinfo();
        s6amap->CopyFrom(S6aMap);
        CLOG_DEBUG("Sending DEL_S6AMAP_DATA for S6aToMap Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_S6AMAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a S6aToMap Request
    CLOG_DEBUG(">CMApiIwfConfig: GetMapS6aTranslationData"); 
    IwfTranslationDataConfig TransData;
    TransData.set_operreqid(GET_MAPS6A_DATA);

    CLOG_DEBUG("Sending GET_MAPS6A_DATA Translation data Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslationDataConfigReqs(TransData,
            new CMAPICookie(GET_MAPS6A_DATA, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translationdatainfo())
    {
        if(Response.translationdatainfo().has_maptos6ainfo())
        {
            MapS6a.CopyFrom(Response.translationdatainfo().maptos6ainfo());
        }
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">SetMapS6aVplmnIdData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(SET_MAPS6A_VPLMN_ID_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending SET_MAPS6A_VPLMN_ID_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_MAPS6A_VPLMN_ID_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">ModifyMapS6aVplmnIdData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(MOD_MAPS6A_VPLMN_ID_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending MOD_MAPS6A_VPLMN_ID_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_MAPS6A_VPLMN_ID_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteMapS6aVplmnIdData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">DeleteMapS6aVplmnIdData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(DEL_MAPS6A_VPLMN_ID_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending DEL_MAPS6A_VPLMN_ID_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_MAPS6A_VPLMN_ID_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">SetMapS6aVplmnIdSgsnMapData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(SET_VPLMN_ID_SGSN_MAP_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending SET_VPLMN_ID_SGSN_MAP_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_VPLMN_ID_SGSN_MAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">ModifyMapS6aVplmnIdSgsnMapData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(MOD_VPLMN_ID_SGSN_MAP_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending MOD_VPLMN_ID_SGSN_MAP_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_VPLMN_ID_SGSN_MAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteMapS6aVplmnIdSgsnMapData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">DeleteMapS6aVplmnIdSgsnMapData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(DEL_VPLMN_ID_SGSN_MAP_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending DEL_VPLMN_ID_SGSN_MAP_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_VPLMN_ID_SGSN_MAP_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">SetMapS6aTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(SET_MAPS6A_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending SET_MAPS6A_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_MAPS6A_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ClearSessionContext(string imsi, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    
    IwfTranslationDataConfig TransData;
    TransData.set_operreqid(CLEAR_SESSION);
    TransData.set_imsiforsessionclearance(imsi);
    CLOG_DEBUG("Sending SESSION CLEARANCE Req");
    // Call CMgr Method Implementation.
    m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
            new CMAPICookie(CLEAR_SESSION, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //IWFCfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respid();
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_respid(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyMapS6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">ModifyMapS6aTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(MOD_MAPS6A_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending MOD_MAPS6A_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_MAPS6A_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteMaps6aTranslationData(IwfMapToS6aConfig& MapS6a, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!MapS6a.IsInitialized())
    {
        CLOG_DEBUG(">DeleteMapS6aTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(DEL_MAPS6A_DATA);
        IwfMapToS6aConfig* maps6a = TransData.mutable_maptos6ainfo();
        maps6a->CopyFrom(MapS6a);
        CLOG_DEBUG("Sending DEL_MAPS6A_DATA for MapToS6a Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_MAPS6A_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetCapRoIDPTranslationData(IwfCapToRoConfig& CapRo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a S6aToMap Request
    CLOG_DEBUG(">CMApiIwfConfig: GetCapRoIDPTranslationData"); 
    IwfTranslationDataConfig TransData;
    TransData.set_operreqid(GET_CAPRO_IDP_DATA);

    CLOG_DEBUG("Sending GET_CAPRO_IDP_DATA Translation data Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslationDataConfigReqs(TransData,
            new CMAPICookie(GET_CAPRO_IDP_DATA, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translationdatainfo())
    {
        if(Response.translationdatainfo().has_captoroinfo())
        {
            CapRo.CopyFrom(Response.translationdatainfo().captoroinfo());
        }
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetCapRoIDPSMSTranslationData(IwfCapToRoConfig& CapRo, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a S6aToMap Request
    CLOG_DEBUG(">CMApiIwfConfig: GetCapRoIDPSMSTranslationData"); 
    IwfTranslationDataConfig TransData;
    TransData.set_operreqid(GET_CAPRO_IDPSMS_DATA);

    CLOG_DEBUG("Sending GET_CAPRO_IDPSMS_DATA Translation data Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslationDataConfigReqs(TransData,
            new CMAPICookie(GET_CAPRO_IDPSMS_DATA, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translationdatainfo())
    {
        if(Response.translationdatainfo().has_captoroinfo())
        {
            CapRo.CopyFrom(Response.translationdatainfo().captoroinfo());
        }
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CapRo.IsInitialized())
    {
        CLOG_DEBUG(">SetCapRoTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(SET_CAPRO_DATA);
        IwfCapToRoConfig* capro = TransData.mutable_captoroinfo();
        capro->CopyFrom(CapRo);
        CLOG_DEBUG("Sending SET_CAPRO_DATA for CapToRo Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_CAPRO_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CapRo.IsInitialized())
    {
        CLOG_DEBUG(">ModifyCapRoTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(MOD_CAPRO_DATA);
        IwfCapToRoConfig* capro = TransData.mutable_captoroinfo();
        capro->CopyFrom(CapRo);
        CLOG_DEBUG("Sending MOD_CAPRO_DATA for CapToRo Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_CAPRO_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteCapRoTranslationData(IwfCapToRoConfig& CapRo, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!CapRo.IsInitialized())
    {
        CLOG_DEBUG(">DeleteCapRoTranslationData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        IwfTranslationDataConfig TransData;
        TransData.set_operreqid(DEL_CAPRO_DATA);
        IwfCapToRoConfig* capro = TransData.mutable_captoroinfo();
        capro->CopyFrom(CapRo);
        CLOG_DEBUG("Sending DEL_CAPRO_DATA for CapToRo Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_CAPRO_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetAllTranslationData(IwfTranslationDataConfig& TransData, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetTranslationData"); 
    TransData.set_operreqid(GET_ALL_TRANSLATOR_DATA);

    CLOG_DEBUG("Sending Translator Data Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetTranslationDataConfigReqs(TransData,
            new CMAPICookie(GET_ALL_TRANSLATOR_DATA, (void *) &TransData));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_translationdatainfo())
    {
        TransData.CopyFrom(Response.translationdatainfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

/*int CMApiIwfConfig::SetTranslationData(IwfTranslationDataConfig& TransData, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!TransData.IsInitialized())
    {
        CLOG_DEBUG(">SetTranslatorData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        TransData.set_operreqid(SET_TRANSLATOR_DATA);
        CLOG_DEBUG("Sending SET_TRANSLATOR_DATA for Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(SET_TRANSLATOR_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyTranslationData(IwfTranslationDataConfig& TransData, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!TransData.IsInitialized())
    {
        CLOG_DEBUG(">ModifyTranslatorData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        TransData.set_operreqid(MOD_TRANSLATOR_DATA);
        CLOG_DEBUG("Sending MOD_TRANSLATOR_DATA for Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(MOD_TRANSLATOR_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteTranslationData(IwfTranslationDataConfig& TransData, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if (!TransData.IsInitialized())
    {
        CLOG_DEBUG(">DeleteTranslatorData: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        TransData.set_operreqid(DEL_TRANSLATOR_DATA);
        CLOG_DEBUG("Sending DEL_TRANSLATOR_DATA for Translation");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetTranslationDataConfigReqs(TransData,
                new CMAPICookie(DEL_TRANSLATOR_DATA, (void *) &TransData));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }

    // Return appropriate Return value.
    return retVal;
}
*/
int CMApiIwfConfig::GetIwfCapProtoTimers(IwfTimersConfig& Timers, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfTimersConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfCapProtoTimers"); 
    Timers.set_operreqid(GET_CAP_PROTO_TIMERS);

    CLOG_DEBUG("Sending IwfCapProtoTimers Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfTimersConfigReqs(Timers,
            new CMAPICookie(GET_CAP_PROTO_TIMERS, (void *) &Timers));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_timersinfo())
    {
        Timers.CopyFrom(Response.timersinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfDccaGenConfig"); 
    DccaGenConfig.set_operreqid(GET_IWF_DCCA_FEATURES);

    CLOG_DEBUG("Sending IwfDccaGen Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfDccaGenConfigReqs(DccaGenConfig,
            new CMAPICookie(GET_IWF_DCCA_FEATURES, (void *) &DccaGenConfig));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_iwfdccainfo())
    {
        if (Response.iwfdccainfo().has_iwfdccageninfo())
        {
#if 0
            IwfDccaConfig ldccaConfig;
            ldccaConfig.CopyFrom(Response.iwfdccainfo());
            IwfDccaGenConfig ldcca;
            ldcca.CopyFrom(ldccaConfig.iwfdccageninfo());
            //DccaGenConfig.CopyFrom(Response.iwfdccainfo().iwfdccageninfo());
            DccaGenConfig.CopyFrom(ldcca);
#endif
            IwfDccaConfig* DccaConfig = Response.mutable_iwfdccainfo();
            IwfDccaGenConfig* lDccaGenConfig = DccaConfig->mutable_iwfdccageninfo();
            DccaGenConfig.CopyFrom(*lDccaGenConfig);
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaGenConfig.iwfdccafeatures_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfDccaGenConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaGenConfig.set_operreqid(MOD_IWF_DCCA_FEATURES);
        CLOG_DEBUG("Sending MOD_IWF_DCCA_FEATURES for iwf Dcca General configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaGenConfigReqs(DccaGenConfig,
                new CMAPICookie(MOD_IWF_DCCA_FEATURES, (void *) &DccaGenConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::AddIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaGenConfig.iwfdccafeatures_size() <= 0 )
    {
        CLOG_DEBUG(">AddIwfDccaGenConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaGenConfig.set_operreqid(SET_IWF_DCCA_FEATURES);
        CLOG_DEBUG("Sending SET_IWF_DCCA_FEATURES for iwf Dcca General configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaGenConfigReqs(DccaGenConfig,
                new CMAPICookie(SET_IWF_DCCA_FEATURES, (void *) &DccaGenConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfDccaGenConfig(IwfDccaGenConfig& DccaGenConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaGenConfig.iwfdccafeatures_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfDccaGenConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaGenConfig.set_operreqid(DEL_IWF_DCCA_FEATURES);
        CLOG_DEBUG("Sending DEL_IWF_DCCA_FEATURES for iwf Dcca General configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaGenConfigReqs(DccaGenConfig,
                new CMAPICookie(DEL_IWF_DCCA_FEATURES, (void *) &DccaGenConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfDccaDestConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfDccaDestConfig"); 
    DccaDestConfig.set_operreqid(GET_IWF_DCCA_DEST);

    CLOG_DEBUG("Sending IwfDccaDest Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfDccaDestConfigReqs(DccaDestConfig,
            new CMAPICookie(GET_IWF_DCCA_DEST, (void *) &DccaDestConfig));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_iwfdccainfo())
    {
        if (Response.iwfdccainfo().has_iwfdccadestsinfo())
        {
            DccaDestConfig.CopyFrom(Response.iwfdccainfo().iwfdccadestsinfo());
        }
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaDestConfig.iwfdccadestinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfDccaDestConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaDestConfig.set_operreqid(SET_IWF_DCCA_DEST);
        CLOG_DEBUG("Sending SET_IWF_DCCA_DEST for iwf Dcca Destination configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaDestConfigReqs(DccaDestConfig,
                new CMAPICookie(SET_IWF_DCCA_DEST, (void *) &DccaDestConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::AddIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaDestConfig.iwfdccadestinfo_size() <= 0 )
    {
        CLOG_DEBUG(">AddIwfDccaDestConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaDestConfig.set_operreqid(SET_IWF_DCCA_DEST);
        CLOG_DEBUG("Sending SET_IWF_DCCA_DEST for iwf Dcca Destination configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaDestConfigReqs(DccaDestConfig,
                new CMAPICookie(SET_IWF_DCCA_DEST, (void *) &DccaDestConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfDccaDestConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaDestConfig.iwfdccadestinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfDccaDestConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaDestConfig.set_operreqid(DEL_IWF_DCCA_DEST);
        CLOG_DEBUG("Sending DEL_IWF_DCCA_DEST for iwf Dcca Destination configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaDestConfigReqs(DccaDestConfig,
                new CMAPICookie(DEL_IWF_DCCA_DEST, (void *) &DccaDestConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfDccaEndpointConfig(IwfDccaDestsConfig& DccaDestConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( DccaDestConfig.iwfdccadestinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfDccaEndpointConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        DccaDestConfig.set_operreqid(DEL_IWF_DCCA_ENDPOINT);
        CLOG_DEBUG("Sending DEL_IWF_DCCA_ENDPOINT for iwf Dcca Destination configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfDccaDestConfigReqs(DccaDestConfig,
                new CMAPICookie(DEL_IWF_DCCA_ENDPOINT, (void *) &DccaDestConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetIwfCapProtoTimers(IwfTimersConfig& Timers, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Timers.iwftimersinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetIwfCapProtoTimers: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Timers.set_operreqid(SET_CAP_PROTO_TIMERS);
        CLOG_DEBUG("Sending SET_CAP_PROTO_TIMERS for iwf cap-proto-timers configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfTimersConfigReqs(Timers,
                new CMAPICookie(SET_CAP_PROTO_TIMERS, (void *) &Timers ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfCapProtoTimers(IwfTimersConfig& Timers, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Timers.iwftimersinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfCapProtoTimers: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Timers.set_operreqid(MOD_CAP_PROTO_TIMERS);
        CLOG_DEBUG("Sending MOD_CAP_PROTO_TIMERS for iwf timers configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfTimersConfigReqs(Timers,
                new CMAPICookie(MOD_CAP_PROTO_TIMERS, (void *) &Timers ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfTimers(IwfTimersConfig& Timers, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfTimersConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfTimers"); 
    Timers.set_operreqid(GET_IWF_TIMERS);

    CLOG_DEBUG("Sending IwfTimers Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfTimersConfigReqs(Timers,
            new CMAPICookie(GET_IWF_TIMERS, (void *) &Timers));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_timersinfo())
    {
        Timers.CopyFrom(Response.timersinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Timers.iwftimersinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetIwfTimers: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Timers.set_operreqid(SET_IWF_TIMERS);
        CLOG_DEBUG("Sending SET_IWF_TIMERS for iwf timers configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfTimersConfigReqs(Timers,
                new CMAPICookie(SET_IWF_TIMERS, (void *) &Timers ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Timers.iwftimersinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfTimers: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Timers.set_operreqid(MOD_IWF_TIMERS);
        CLOG_DEBUG("Sending MOD_IWF_TIMERS for iwf timers configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfTimersConfigReqs(Timers,
                new CMAPICookie(MOD_IWF_TIMERS, (void *) &Timers ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfTimers(IwfTimersConfig& Timers, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Timers.iwftimersinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfTimers: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Timers.set_operreqid(DEL_IWF_TIMERS);
        CLOG_DEBUG("Sending DEL_IWF_TIMERS for iwf timers configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfTimersConfigReqs(Timers,
                new CMAPICookie(DEL_IWF_TIMERS, (void *) &Timers ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetUalConfig(IwfSigtranUalManagerConfig& Ual, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a LocalHostConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetUalConfig"); 
    Ual.set_operreqid(GET_UAL_CONFIG);

    CLOG_DEBUG("Sending Ual Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfUalManagerConfigReqs(Ual,
            new CMAPICookie(GET_UAL_CONFIG, (void *) &Ual));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_ualinfo())
    {
        Ual.CopyFrom(Response.ualinfo());
    }
    if(Response.errordetails_size())                
    {                                              
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetUalConfig(IwfSigtranUalManagerConfig& Ual, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    Ual.set_operreqid(SET_UAL_CONFIG);
    CLOG_DEBUG("Sending SET_UAL_CONFIG for UAL Manager");
    // Call CMgr Method Implementation.
    m_CMgrCallerObj->HandleSetIwfUalManagerConfigReqs(Ual,
            new CMAPICookie(SET_UAL_CONFIG, (void *) &Ual ));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //IWFCfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respid();
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_respid(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyUalConfig(IwfSigtranUalManagerConfig& Ual, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    Ual.set_operreqid(MOD_UAL_CONFIG);
    CLOG_DEBUG("Sending MOD_UAL_CONFIG for UAL Manager");
    // Call CMgr Method Implementation.
    m_CMgrCallerObj->HandleSetIwfUalManagerConfigReqs(Ual,
            new CMAPICookie(MOD_UAL_CONFIG, (void *) &Ual ));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //IWFCfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respid();
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_respid(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }

    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfFeatures(IwfFeaturesConfig& Features, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfTimersConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfFeatures"); 
    Features.set_operreqid(GET_IWF_FEATURES);

    CLOG_DEBUG("Sending IwfFeatures Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfFeaturesConfigReqs(Features,
            new CMAPICookie(GET_IWF_FEATURES, (void *) &Features));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_featuresinfo())
    {
        Features.CopyFrom(Response.featuresinfo());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::SetIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Features.iwffeatureinfo_size() <= 0 )
    {
        CLOG_DEBUG(">SetIwfFeatures: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Features.set_operreqid(SET_IWF_FEATURES);
        CLOG_DEBUG("Sending SET_IWF_FEATURES for iwf features configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfFeaturesConfigReqs(Features,
                new CMAPICookie(SET_IWF_FEATURES, (void *) &Features ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Features.iwffeatureinfo_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfFeatures: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Features.set_operreqid(MOD_IWF_FEATURES);
        CLOG_DEBUG("Sending MOD_IWF_FEATURES for iwf features configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfFeaturesConfigReqs(Features,
                new CMAPICookie(MOD_IWF_FEATURES, (void *) &Features ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfFeatures(IwfFeaturesConfig& Features, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( Features.iwffeatureinfo_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfFeatures: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        Features.set_operreqid(DEL_IWF_FEATURES);
        CLOG_DEBUG("Sending DEL_IWF_FEATURES for iwf features configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfFeaturesConfigReqs(Features,
                new CMAPICookie(DEL_IWF_FEATURES, (void *) &Features ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::ModifyIwfProtocolActionsConfig(IwfProtocolActionsConfig &ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">ModifyIwfProtocolActionsConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(MOD_IWF_PROT_ACTIONS);
        CLOG_DEBUG("Sending MOD_IWF_PROT_ACTIONS for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(MOD_IWF_PROT_ACTIONS, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfProtocolActionsConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfProtocolActionsConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(DEL_IWF_PROT_ACTIONS);
        CLOG_DEBUG("Sending DEL_IWF_PROT_ACTIONS for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(DEL_IWF_PROT_ACTIONS, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;

}

int CMApiIwfConfig::DeleteIwfCallScenarioConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfCallScenarioConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(DEL_IWF_CALL_SCENARIO);
        CLOG_DEBUG("Sending DEL_IWF_CALL_SCENARIO for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(DEL_IWF_CALL_SCENARIO, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;


}

int CMApiIwfConfig::DeleteIwfProtocolEventType(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfProtocolEventType: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(DEL_IWF_EVENT_TYPE);
        CLOG_DEBUG("Sending DEL_IWF_EVENT_TYPE for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(DEL_IWF_EVENT_TYPE, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::DeleteIwfEventTypeConfig(IwfProtocolActionsConfig& ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">DeleteIwfEventTypeConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(DEL_IWF_EVENT_TYPE_CONFIG);
        CLOG_DEBUG("Sending DEL_IWF_EVENT_TYPE_CONFIG for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(DEL_IWF_EVENT_TYPE_CONFIG, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;

}

int CMApiIwfConfig::AddIwfProtocolActionsConfig(IwfProtocolActionsConfig &ProtActionsConfig, IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    if( ProtActionsConfig.iwfprotactioncfgval_size() <= 0 )
    {
        CLOG_DEBUG(">AddIwfProtocolActionsConfig: ERROR: Invalid Parameters");
        retVal = (int) CMAPI_INVALIDPARAMS;
    }
    else
    {
        ProtActionsConfig.set_operreqid(SET_IWF_PROT_ACTIONS);
        CLOG_DEBUG("Sending SET_IWF_PROT_ACTIONS for iwf protocol actions configuration ");
        // Call CMgr Method Implementation.
        m_CMgrCallerObj->HandleSetIwfProtocolActionsConfigReqs(ProtActionsConfig,
                new CMAPICookie(SET_IWF_PROT_ACTIONS, (void *) &ProtActionsConfig ));
        std::string StrVal;
        if(m_SendSuccess == false)
        {
            retVal = CMAPI_MESSERROR;
            m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
            m_lastError.set_errormsgkey("config.common.mess.not.ready");
            m_SendSuccess = true;
            return retVal;
        }

        if(m_CMAPIResponse->Get(StrVal,m_waitTime))
        {
            //IWFCfgResp Response;
            Response->ParseFromString(StrVal);
            retVal = Response->respid();
        }
        else
        {
            retVal = CMAPI_TIMEOUT;
            Response->set_respid(CMAPI_TIMEOUT);
            // Fill in errordetails in Response
            ErrorDetails *err = Response->add_errordetails();
            err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
            err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
        }
    }
    // Return appropriate Return value.
    return retVal;
}

int CMApiIwfConfig::GetIwfProtocolActionsConfig(IwfProtocolActionsConfig& ProtActionsConfig, ErrorDetails& err)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    // Build a IwfProtocolActionsConfig Request
    CLOG_DEBUG(">CMApiIwfConfig: GetIwfProtocolActionsConfig"); 
    ProtActionsConfig.set_operreqid(GET_IWF_PROT_ACTIONS);

    CLOG_DEBUG("Sending IwfDccaDest Config Info");
    // Call Caller Method to Call Server Implementation. 
    m_CMgrCallerObj->HandleGetIwfProtocolActionsConfigReqs(ProtActionsConfig,
            new CMAPICookie(GET_IWF_PROT_ACTIONS, (void *) &ProtActionsConfig));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    m_CMAPIResponse->Get(StrVal);
    IWFCfgResp Response;
    Response.ParseFromString(StrVal);
    retVal = Response.respid();
    if (Response.has_iwfprotocolactionsinfo())
    {
        ProtActionsConfig.CopyFrom(Response.iwfprotocolactionsinfo());
    }
    if(Response.errordetails_size())
    {
        err.CopyFrom(Response.errordetails(0)); 
    }                                              
    // Return appropriate Return value.
    return retVal;
}
// ***********************************************************************
// Config Manager Methods Response Handlers Implementation
// ***********************************************************************

int CMApiIwfConfig::HandleGetLocalHostConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetLocalHostConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}


int CMApiIwfConfig::HandleSetLocalHostConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetLocalHostConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || ( resp->respid() != CMAPI_SUCCESS && resp->respid() != CMAPI_DB_SUCCESS) ) 
    {
        CLOG_DEBUG("HandleSetLocalHostConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    /* This is because the localhost configuration will not be sent to IWF
     * it will be modified/added only in DB and CMGR will not invoke 
     * SendIWFConfigResp in this casem hence the set is done in callback */
    else if ( resp != NULL && resp->respid() == CMAPI_DB_SUCCESS )
    {
        CLOG_DEBUG("HandleSetLocalHostConfigReqs success in DB");
        resp->set_respid(CMAPI_SUCCESS);
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetDestinationConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetDestinationConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetDestinationConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetDestinationConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetDestinationConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || ( resp->respid() != CMAPI_SUCCESS && resp->respid() != CMAPI_DB_SUCCESS) ) 
    {
        CLOG_DEBUG("HandleSetDestinationConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    /* This is because the DestinationInfo configuration will not be sent to IWF
     * it will be modified/added only in DB and CMGR will not invoke 
     * SendIWFConfigResp in this casem hence the set is done in callback */
    else if ( resp != NULL && resp->respid() == CMAPI_DB_SUCCESS )
    {
        CLOG_DEBUG("HandleSetDestinationConfigReqs success in DB");
        resp->set_respid(CMAPI_SUCCESS);
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
 

    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetAssociationSetConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetAssociationSetConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetAssociationSetConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetAssociationSetConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetAssociationSetConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetAssociationSetConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetAssociationConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetAssociationConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetAssociationConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetAssociationConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetAssociationConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL ||  ( resp->respid() != CMAPI_SUCCESS && resp->respid() != CMAPI_DB_SUCCESS) )
    {
        CLOG_DEBUG("HandleSetAssociationConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    /* This is because the ModifyAssociation configuration will not be sent to IWF
     * it will be modified/added only in DB and CMGR will not invoke 
     * SendIWFConfigResp in this case hence the set is done in callback */
    else if ( resp != NULL && resp->respid() == CMAPI_DB_SUCCESS )
    {
        CLOG_DEBUG("HandleSetAssociationConfigReqs success in DB");
        resp->set_respid(CMAPI_SUCCESS);
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }

    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetRemoteRouteConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetRemoteRouteConfigReqsRespCbk ");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetRemoteRouteConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetRemoteRouteConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetRemoteRouteConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetRemoteRouteConfigReqs message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetTranslatorRuleConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetTranslatorRuleConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetTranslatorRuleConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetTranslatorRuleConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetTranslatorRuleConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetTranslatorRuleConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetTranslationDataConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetTranslationDataConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetTranslationDataConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetTranslationDataConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetTranslationDataConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetTranslationDataConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::SendIWFConfigResult(IWFCfgResp *Req, CMAPIRes *Resp)
{
    CLOG_DEBUG("IWFConfig ReportResult");
    string StrVal;
    if (Req != NULL)
    {
        Req->SerializeToString(&StrVal);
    }
    m_CMAPIResponse->Set(StrVal);
    Resp->set_responsecode(CMAPI_SUCCESS);
    return 0;
}

int CMApiIwfConfig::HandleGetSctpEndPointConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetSctpEndPointConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetSctpEndPointConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetSctpEndPointConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetSctpEndPointConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || ( resp->respid() != CMAPI_SUCCESS && resp->respid() != CMAPI_DB_SUCCESS) ) 
    {
        CLOG_DEBUG("HandleSetSctpEndPointConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    /* This is because the SctpEndPoint configuration will not be sent to IWF
     * it will be modified/added only in DB and CMGR will not invoke 
     * SendIWFConfigResp in this casem hence the set is done in callback */
    else if ( resp != NULL && resp->respid() == CMAPI_DB_SUCCESS )
    {
        CLOG_DEBUG("HandleSetSctpEndPointConfigReqs success in DB");
        resp->set_respid(CMAPI_SUCCESS);
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
 
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetSctpProfileConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetSctpProfileConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetSctpProfileConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetSctpProfileConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetSctpProfileConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || ( resp->respid() != CMAPI_SUCCESS && resp->respid() != CMAPI_DB_SUCCESS) ) 
    {
        CLOG_DEBUG("HandleSetSctpProfileConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    /* This is because the SctpProfile configuration will not be sent to IWF
     * it will be modified/added only in DB and CMGR will not invoke 
     * SendIWFConfigResp in this casem hence the set is done in callback */
    else if ( resp != NULL && resp->respid() == CMAPI_DB_SUCCESS )
    {
        CLOG_DEBUG("HandleSetSctpProfileConfigReqs success in DB");
        resp->set_respid(CMAPI_SUCCESS);
        resp->SerializeToString(&StrVal);
        m_CMAPIResponse->Set(StrVal);
    }
 
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetSigtranMultihomingConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetSigtranMultihomingConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetSigtranMultihomingConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetSigtranMultihomingConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetSigtranMultihomingConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetSigtranMultihomingConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfDccaGenConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfDccaGenConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfDccaGenConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfDccaGenConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfDccaGenConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfDccaGenConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfDccaDestConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfDccaDestConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfDccaDestConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfDccaDestConfigReqsRespCbk(IWFCfgResp* resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfDccaDestConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfDccaDestConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfTimersConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfTimersConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfTimersConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfTimersConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfTimersConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfTimersConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfFeaturesConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfFeaturesConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfFeaturesConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }

        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfFeaturesConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfFeaturesConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfFeaturesConfigReqsRespCbk failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfProtocolActionsConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfProtocolActionConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG("<HandleGetIwfProtocolActionConfigReqsRespCbk");
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfProtocolActionConfigReqsRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    CLOG_DEBUG("<HandleGetIwfProtocolActionConfigReqsRespCbk");
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfProtocolActionsConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfProtocolActionConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        CLOG_DEBUG("<HandleSetIwfProtocolActionConfigReqsRespCbk");
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfProtocolActionConfigReqsRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    CLOG_DEBUG("<HandleSetIwfProtocolActionConfigReqsRespCbk");
    return retVal;
}

int CMApiIwfConfig::HandleGetIwfUalManagerConfigReqsRespCbk(IWFCfgResp *resp)
{

    int retVal = 0;
    CLOG_DEBUG(">HandleGetIwfUalConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleGetIwfUalConfigReqsRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
    }
    else
    {
        resp->SerializeToString(&StrVal);
    }

    m_CMAPIResponse->Set(StrVal);
    delete lCookie; 
    return retVal;
}

int CMApiIwfConfig::HandleSetIwfUalManagerConfigReqsRespCbk(IWFCfgResp *resp)
{
    int retVal = 0;
    CLOG_DEBUG(">HandleSetIwfUalConfigReqsRespCbk");

    std::string StrVal;
    if ( MeSS::Handle().m_state == MESS_STATUS_NOT_READY )
    {
        m_SendSuccess = false;
        return 0;
    }
    // Retrieve our saved cookie
    CMAPICookie *lCookie = reinterpret_cast <CMAPICookie *> (MeSS::Handle().m_cookie);
    if ( (MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || 
            resp == NULL || resp->respid() != CMAPI_SUCCESS ) 
    {
        CLOG_DEBUG("HandleSetIwfUalConfigReqsRespCbk message failed. Error: ");
        if (resp == NULL ) 
        {
            IWFCfgResp ErrorResponse;
            retVal = CMAPI_SRVERROR;
            ErrorResponse.set_respid(retVal);
            ErrorResponse.SerializeToString(&StrVal);
        } else {
            resp->SerializeToString(&StrVal);
        }
        m_CMAPIResponse->Set(StrVal);
    }
    delete lCookie;
    return retVal;
}

int CMApiIwfConfig::DumpSystemInfo(IWFCfgResp* Response)
{
    int retVal = CMAPI_SUCCESS;
    m_SendSuccess = true;
    IwfFeaturesConfig Features;

    Features.set_operreqid(DUMP_SYSTEM_INFO);
    CLOG_DEBUG("Sending DUMP_SYSTEM_INFO for iwf");
    // Call CMgr Method Implementation.
    m_CMgrCallerObj->HandleSetIwfFeaturesConfigReqs(Features,
            new CMAPICookie(DUMP_SYSTEM_INFO, (void *) &Features ));
    std::string StrVal;
    if(m_SendSuccess == false)
    {
        retVal = CMAPI_MESSERROR;
        m_lastError.set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        m_lastError.set_errormsgkey("config.common.mess.not.ready");
        m_SendSuccess = true;
        return retVal;
    }

    if(m_CMAPIResponse->Get(StrVal,m_waitTime))
    {
        //IWFCfgResp Response;
        Response->ParseFromString(StrVal);
        retVal = Response->respid();
    }
    else
    {
        retVal = CMAPI_TIMEOUT;
        Response->set_respid(CMAPI_TIMEOUT);
        // Fill in errordetails in Response
        ErrorDetails *err = Response->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_ERR_CMAPI_CONDVAR_TIMEOUT);
        err->set_errormsgkey("config.common.err.cmapi.condvar.timeout");
    }
    return retVal;
}
