/* ********************************-*-CPP-*-***********************************
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

/**
 *
 *   @file  CMAPIIwfConfig.cpp
 *
 *  @brief  Implementation Methods from IWF towards CMAPI Library
 *
 **/

#include <iwf_mess.h>
#include "ErrorResp.h"
#include "iwf.h"
#include "iwf_prot_utils.h"
#include "CMAPIIwfConfig.h"
#include <ssg_trace.h>
#include <ssg_statistics.h>
#include <ssg_configuration.h>

#include <sstream>
class CAPToRoHandler;
using namespace eAccelero;
using namespace std;
extern SsgConfiguration& GetSsgConfiguration();


CMAPIIwfConfig::CMAPIIwfConfig()
{
    // Register Server Methods
    // RegisterMethods();

    CLOG_DEBUG(">>CMAPIIwfConfig Constructor");
    //Get pointer to Diameter Management Object;
    //m_diaMgtObj = DiaMgmt::GetDiaMgmt();
}

CMAPIIwfConfig::~CMAPIIwfConfig()
{

}

int CMAPIIwfConfig::HandleLocalHostConfigReqs(IwfLocalHostsConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleLocalHostConfigReqs Entry");
    int retVal = (int) CMAPI_SUCCESS;
    int errorCode;
    switch (req->operreqid())
    {
        case MOD_LOCAL_HOST:
            if(req->has_localhostinfo())
            {
                IwfLocalHostConfig localHostCfg =  req->localhostinfo();
                retVal = ModifyLocalHost(localHostCfg);
                if(retVal != ITS_SUCCESS)
                {
                    ErrorDetails* err = resp->add_errordetails();
                    errorCode = retVal;
                    err->set_errorcode(errorCode);
                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            else
            {
                DLOG_ERROR("CMAPIIwfConfig::HandleLocalHostConfigReqs: Failed to Modify LocalHost Information");
                retVal = CMAPI_ERROR;
            }
            break;
        case SET_LOCAL_HOST:
            if(req->has_localhostinfo())
            {
                IwfLocalHostConfig localHostCfg =  req->localhostinfo();
                retVal = SetLocalHost(localHostCfg);
                if(retVal != ITS_SUCCESS)
                {
                    ErrorDetails* err = resp->add_errordetails();
                    errorCode = retVal;
                    err->set_errorcode(errorCode);
                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            else
            {
                DLOG_ERROR("CMAPIIwfConfig::HandleLocalHostConfigReqs: Failed to set LocalHost Information");
                retVal = CMAPI_SRVERROR;
            }
            break;
        case SET_LOCAL_INVK_TIMER:
            {
                IwfLocalHostConfig localHostCfg =  req->localhostinfo();
                if(localHostCfg.has_tcapinvoketimer())
                {
                    unsigned invokeTimer = localHostCfg.tcapinvoketimer();
                    IwfController::Instance().Config().LocalConfig().SetInvokeTimeout(invokeTimer);
                }
                else
                {
                    ErrorDetails* err = resp->add_errordetails();
                    errorCode = SET_LOCALHOST_ERR_MISSING_MANDATORY_PARAM;
                    err->set_errorcode(errorCode);
                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_LOCAL_HOST_SSN:
            break;
        case GET_LOCAL_HOST:
            {
                IwfLocalHostsConfig* LocalHostsConfig = resp->mutable_localhostinfo();
                IwfLocalHostConfig* LocalHostInfo = LocalHostsConfig->mutable_localhostinfo();

                int ni = IwfController::Instance().Config().LocalConfig().LocalNetworkIndicator();
                LocalHostInfo->set_networkindicator(ni);
            }
            break;
        default:
            DLOG_ERROR("CMAPIIwfConfig::HandleLocalHostConfigReqs : Invalid Request for LocalHost Configuration");

    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleLocalHostConfigReqs Exit");
    return 0;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  To Modify LocalHost Parameters such as SelcetionCriteria
 *  , GT Configuration and timers
 *
 *  Input Parameters:
 *      None. CMAPI IwfLocalHostConfig Structuers
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  On Success return CMAPI_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/


int CMAPIIwfConfig::ModifyLocalHost(IwfLocalHostConfig localhost)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::ModifyLocalHost Entry");
    int retVal = CMAPI_SUCCESS;
    SelectionCriteria selectionCriteria = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();
    if(localhost.has_tcapinvoketimer())
    {
        unsigned invokeTimer = localhost.tcapinvoketimer();
        IwfController::Instance().Config().LocalConfig().SetInvokeTimeout(invokeTimer);
    }

    if(localhost.has_usesccpcdpafromincommingmsg())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost UseSccpCdPaFromIncommingMsg: %d", localhost.usesccpcdpafromincommingmsg());
        IwfController::Instance().Config().LocalConfig().SetIsUseSccpCdPAFromInMsg(localhost.usesccpcdpafromincommingmsg());
    }

    if(localhost.has_selectcriteria())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost Selection Criteria: %d", (SelectionCriteria)localhost.selectcriteria());
        if(selectionCriteria != (SelectionCriteria)localhost.selectcriteria())
        {
            retVal = IwfController::Instance().Config().RoutingRules().CleanRoutingRuleMap();
            if(retVal == ITS_SUCCESS)
            {
                DLOG_DEBUG("All Translation Rules as part of Modify Selection Criteria Deleted from IWF");
            }
            else
            {
                DLOG_ERROR("Failed to delete Translation Rules as part of Modify Selection Criteria");
                return CMAPI_ERROR;
            }
        }
        else
        {
            DLOG_ERROR("Existing SelectionCriteria is same as Incoming SelectionCriteria, Hence not flushing the rules");
        }

        IwfController::Instance().Config().LocalConfig().SetSelectionCriteria((SelectionCriteria)localhost.selectcriteria());
    }

    if(localhost.has_addresstype())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost AddressType : %s", localhost.addresstype().c_str());
        if(!strcasecmp(localhost.addresstype().c_str(), "GT"))
        {
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetRouteByGT(true);
        }
        else
        {
            IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetRouteByGT(false);
        }
    }

    if(localhost.has_localgtusefromconfig())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost LocalGTUseFromConfig: %d", localhost.localgtusefromconfig());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetUseFromConfig(localhost.localgtusefromconfig());
    }

    if(localhost.has_includepc())
    {
        DLOG_DEBUG("IwfController::ModifyLocalHost IncludePC in GT: %d", localhost.includepc());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetLocalPCIndicator(localhost.includepc());
    }

    if(localhost.has_gti())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGTI(localhost.gti());
    }
    if(localhost.has_translationtype())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetTranslationType(localhost.translationtype());
    }
    if(localhost.has_numberingplan())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetNumberingPlan(localhost.numberingplan());
    }
    if(localhost.has_encodingscheme())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetEncodingScheme(localhost.encodingscheme());
    }
    if(localhost.has_natureofaddrind())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetAddressIndicator(localhost.natureofaddrind());
    }
    if(localhost.has_gtaddrdigits())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGtDigits(localhost.gtaddrdigits());
    }


    DLOG_DEBUG("CMAPIIwfConfig::ModifyLocalHost Exit");
    return retVal;
}

int CMAPIIwfConfig::SetLocalHost(IwfLocalHostConfig localhost)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::SetLocalHost Entry");
    int retVal = CMAPI_SUCCESS;

    if(localhost.has_gti() && localhost.has_translationtype()
            && localhost.has_numberingplan() && localhost.has_encodingscheme()
            && localhost.has_natureofaddrind() && localhost.has_gtaddrdigits())
    {
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGTI(localhost.gti());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetTranslationType(localhost.translationtype());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetNumberingPlan(localhost.numberingplan());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetEncodingScheme(localhost.encodingscheme());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetAddressIndicator(localhost.natureofaddrind());
        IwfController::Instance().Config().LocalConfig().SelfSccpAddress().SetGtDigits(localhost.gtaddrdigits());
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetLocalHost Missing mandatory Parameter of GTT..!!");
        retVal = SET_LOCALHOST_ERR_MISSING_MANDATORY_PARAM;
    }
    DLOG_DEBUG("CMAPIIwfConfig::SetLocalHost Exit");
    return retVal;
}

int CMAPIIwfConfig::HandleUalManagerConfigReqs(IwfSigtranUalManagerConfig* req, IWFCfgResp* resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleUalManagerConfigReqs Entry");
    int retVal = ITS_SUCCESS;
    int errorCode;
    switch (req->operreqid())
    {
        case SET_UAL_CONFIG:
        case MOD_UAL_CONFIG:
            {
                if(req->has_acktimer() && req->has_sigtranmode())
                {
                    UALConfigMgmt *ualConfigMgmt;
                    ualConfigMgmt = (UALConfigMgmt*)calloc(1, sizeof(UALConfigMgmt));

                    DLOG_DEBUG("CMAPIIwfConfig::HandleUalManagerConfigReqs: Incoming InterWorking Mode: %s", req->sigtranmode().c_str());
                    strncpy(ualConfigMgmt->interworkingMode, req->sigtranmode().c_str(), MAX_STRING_SIZE);
                    strncpy(ualConfigMgmt->protocolType, "M3UA", MAX_STRING_SIZE);
                    //strncpy(ualConfigMgmt->ipspExchangeType, "single", MAX_STRING_SIZE);
                    //strncpy(ualConfigMgmt->ipspType, "client", MAX_STRING_SIZE);
                    strncpy(ualConfigMgmt->ipspExchangeType, "-", MAX_STRING_SIZE);
                    strncpy(ualConfigMgmt->ipspType, "-", MAX_STRING_SIZE);
                    strncpy(ualConfigMgmt->heartbeatFlag, "off", MAX_STRING_SIZE);
                    ualConfigMgmt->protocolVersion = 1;
                    ualConfigMgmt->localPointCode = 1;
                    ualConfigMgmt->heartbeatInterval = 5;
                    DLOG_DEBUG("CMAPIIwfConfig::HandleUalManagerConfigReqs: Incoming Ack Timer: %d", req->acktimer());
                    ualConfigMgmt->ackTimer = req->acktimer();
                    ualConfigMgmt->auditTimer = 10;
                    ualConfigMgmt->pendingTimer = 2;

                    if((retVal = ConfigureUalManagement(ualConfigMgmt)) != ITS_SUCCESS)
                    {
                        DLOG_ERROR("CMAPIIwfConfig::HandleUalManagerConfigReqs: UAL General Configuration failed: Error %d", retVal);
                        ErrorDetails* err = resp->add_errordetails();
                        errorCode = ADD_UALCONFIG_ERR_ADD_GENERAL_CONFIG_FAILED_AT_BACKEND;
                        err->set_errorcode(errorCode);
                        err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                        retVal = CMAPI_SRVERROR;
                    }
                    if(ualConfigMgmt)
                    {
                        free(ualConfigMgmt);
                        ualConfigMgmt = NULL;
                    }
                }
                else
                {
                    DLOG_ERROR("CMAPIIwfConfig::HandleUalManagerConfigReqs : Missing Mandatory Parameter");
                    ErrorDetails* err = resp->add_errordetails();
                    errorCode = ADD_UALCONFIG_ERR_MISSING_MANDATORY_PARAM;
                    err->set_errorcode(errorCode);
                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        default:
            DLOG_ERROR("CMAPIIwfConfig::HandleUalManagerConfigReqs : Invalid Request for UalManager Configuration");
    }

    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleUalManagerConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::HandleAssociationSetConfigReqs(IwfSigtranAssociationSetsConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationSetConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    int errorCode;
    int totalAssociationSetNum = req->associationsetinfo_size();
    if(totalAssociationSetNum > 0)
    {
        for (int assocSetNum = 0; assocSetNum < totalAssociationSetNum; assocSetNum++)
        {
            try
            {
                IwfSigtranAssociationSetConfig assocSetCfg = req->associationsetinfo(assocSetNum);
                switch(req->operreqid())
                {
                    case SET_ASSOC_SET:
                        if(assocSetCfg.has_associationsetid())
                        {
                            retVal = SetAssociationSet(assocSetCfg);
                            if(retVal != ITS_SUCCESS)
                            {
                                ErrorDetails* err = resp->add_errordetails();
                                errorCode = retVal;
                                err->set_errorcode(errorCode);
                                err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                err->add_variables(assocSetCfg.associationsetname());
                                retVal = CMAPI_SRVERROR;
                            }
                        }
                        else
                        {
                            DLOG_ERROR("CMAPIIwfConfig::HandleAssociationSetConfigReqs: Missing Mandatory Parameters AssociationSetId");
                            retVal = CMAPI_INVALIDPARAMS;
                        }
                        break;
                    case MOD_ASSOC_SET:
                        if(assocSetCfg.has_associationsetid())
                        {
                            retVal = ModifyAssociationSet(assocSetCfg);
                            if(retVal != ITS_SUCCESS)
                            {
                                ErrorDetails* err = resp->add_errordetails();
                                //errorCode = MOD_ASSOCIATIONSET_NOT_SUPPORTED;
                                errorCode = retVal;
                                err->set_errorcode(errorCode);
                                err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                err->add_variables(assocSetCfg.associationsetname());
                                retVal = CMAPI_SRVERROR;
                            }
                        }
                        else
                        {
                            retVal = CMAPI_INVALIDPARAMS;
                        }
                        break;
                    case DEL_ASSOC_SET:
                        if(assocSetCfg.has_associationsetid())
                        {
                            retVal = DeleteAssociationSet(assocSetCfg);
                            if(retVal != ITS_SUCCESS)
                            {
                                ErrorDetails* err = resp->add_errordetails();
                                //errorCode = DEL_ASSOCIATIONSET_NOT_SUPPORTED;
                                errorCode = retVal;
                                err->set_errorcode(errorCode);
                                err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                err->add_variables(assocSetCfg.associationsetname());
                                retVal = CMAPI_SRVERROR;
                            }
                        }
                        else
                        {
                            retVal = CMAPI_INVALIDPARAMS;
                        }
                        break;
                    default:
                        DLOG_ERROR("CMAPIIwfConfig::HandleAssociationSetConfigReqs : Invalid Request for AssociationSet Configuration");
                }
            }
            catch (...)
            {
                DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationSetConfigReqs : Exception ");
            }
        }
    }
    /* ackTimer
     * interworkingMode
     * aspId
     * asTrafficMode
     * routing key
     * create the association set configuration
     * create routing key route
     */
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationSetConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::SetAssociationSet(IwfSigtranAssociationSetConfig associationSet)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet Entry");
    int retVal = CMAPI_SUCCESS;
    ITS_UINT rkey = 0;
    ITS_UINT lpc = IwfController::Instance().Config().LocalConfig().OriginPointCode();
    ITS_UINT ni;
    ITS_UINT sio;
    string localFamily = "ITU";
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    UAL_TRAFFIC_TYPE trafficMode;

    if(family == FAMILY_ITU)
    {
        localFamily = "ITU";
    }
    else if(family == FAMILY_ANSI)
    {
        localFamily = "ANSI";
    }

    if(associationSet.has_associationsetid() && associationSet.has_networkindicator() &&
            associationSet.has_adjacenpointcode() && associationSet.has_routingcontext())
    {
        ITS_OCTET linkSetId = associationSet.associationsetid();
        DLOG_DEBUG("Incoming associationmappingid : %d", associationSet.associationsetid());
        ITS_UINT apc = associationSet.adjacenpointcode();
        DLOG_DEBUG("Incoming APC : %d", associationSet.adjacenpointcode());
        if(IwfController::Instance().Config().LocalConfig().LocalNetworkIndicator() != associationSet.networkindicator())
        {
            DLOG_ERROR("Incoming NetworkIndicator does not match to Local NetworkIndicator");
            return ADD_ASSOCIATIONSET_ERR_NI_NOT_SAME_AS_LOCAL_NI;
        }
        if(associationSet.networkindicator())
        {
            DLOG_DEBUG("Network Indicator is National");
            ni = IWF_NATIONAL_INDICATOR;
            sio = IWF_NATIONAL_SIO;
        }
        else
        {
            DLOG_DEBUG("Network Indicator is International");
            ni = IWF_INTERNATIONAL_INDICATOR;
            sio = IWF_INTERNATIONAL_SIO;
        }
        rkey = associationSet.routingcontext();
        DLOG_DEBUG("Incoming RoutingKey : %d", associationSet.routingcontext());

        /* setting the apc for localConfig to be used for GTT routing */
        IwfController::Instance().Config().LocalConfig().SetAdjacentPointCode(apc);

        /* TODO : To call the Sigtran Api's for ANSI in else case same as CCITT */
        if((retVal = MTP3_OSS_AddLinkset_CCITT(linkSetId, family, lpc, apc, ni)) != ITS_SUCCESS)
        {
            DLOG_ERROR("Addition of AssociationSet failed, Error %d", retVal);
            return retVal;
        }

        std::vector<unsigned> ssn = IwfController::Instance().Config().LocalConfig().LocalSSN();
        if(!ssn.empty())
        {
            if((retVal = MTP3_OSS_AddRoutingKeyroutePC_CCITT(lpc, sio, ssn.front(), rkey, family)) != ITS_SUCCESS)
            {
                DLOG_ERROR("Addition of RoutingKeyRoute failed, Error %d", retVal);
                return retVal;
            }
        }
        else
        {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing ..!!");
            retVal = ADD_ASSOCIATIONSET_ERR_MISSING_MANDATORY_PARAM;
            return retVal;
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing ..!!");
        retVal = ADD_ASSOCIATIONSET_ERR_MISSING_MANDATORY_PARAM;
        return retVal;
    }

    /* UAL Manager Configuration */
    if(associationSet.has_trafficmode() && associationSet.has_routingcontext() &&
            associationSet.has_ismember())
    {
        if(UAL_GL_ITW_MODE == UAL_ITW_IPSP && !associationSet.has_homeip())
    {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: HomeIp is not set in req as IWF is configured as IPSP Mode");
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing in UAL Configuration..!!");
            retVal = ADD_UALCONFIG_ERR_MISSING_MANDATORY_PARAM;
            return retVal;;
        }

        DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming Traffic Mode: %s", associationSet.trafficmode().c_str());

        if(strcmp(associationSet.trafficmode().c_str(), UAL_LOAD_SHARE_MODE_STRING) == 0)
        {
            trafficMode = UAL_LOADSHARE;
        }
        else if(strcmp(associationSet.trafficmode().c_str(), UAL_OVERIDE_MODE_STRING) == 0)
        {
            trafficMode = UAL_OVERRIDE;
        }
        else
        {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Invalid Traffic Mode Configured");
            retVal = ADD_ASSOCIATIONSET_ERR_INVALID_TRAFFIC_MODE;
            return retVal;
        }

        DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming isMember Value : %d", associationSet.ismember());
        ITS_BOOLEAN isMem = ITS_TRUE;
        if(associationSet.ismember() == 0)
        {
            isMem = ITS_FALSE;
        }

        if((retVal = CreateApplicationServer(rkey, (char *)localFamily.c_str(), trafficMode, ni, isMem)) != ITS_SUCCESS)
        {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server: Error %d", retVal);
            return retVal;
        }

        const char* homeIp = NULL;
        if(associationSet.has_homeip())
        {
            DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming HomeIp Address Value : %s", associationSet.homeip().c_str());
            homeIp = associationSet.homeip().c_str();
        }
        if(UAL_GL_ITW_MODE != UAL_ITW_IPSP)
        {
            if((retVal = CreateApplicationServerProcess(rkey, IwfController::Instance().Config().LocalConfig().GetASPId(), homeIp)) != ITS_SUCCESS)
            {
                DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server Process: Error %d", retVal);
                return retVal;
            }
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing in UAL Configuration..!!");
        retVal = ADD_UALCONFIG_ERR_MISSING_MANDATORY_PARAM;
        return retVal;;
    }

    DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet Exit");
    return retVal;
}
int CMAPIIwfConfig::ModifyAssociationSet(IwfSigtranAssociationSetConfig associationSet)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::ModifyAssociationSet Entry");
    int retVal = CMAPI_SUCCESS;
    ITS_UINT rkey = 0;
    ITS_UINT lpc = IwfController::Instance().Config().LocalConfig().OriginPointCode();;
    ITS_UINT ni;
    ITS_UINT apc;
    string localFamily = "ITU";
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    UAL_TRAFFIC_TYPE trafficMode;

    if(family == FAMILY_ITU)
    {
        localFamily = "ITU";
    }
    else if(family == FAMILY_ANSI)
    {
        localFamily = "ANSI";
    }

    ITS_OCTET linkSetId = associationSet.associationsetid();

    /* TODO check if linkset is activated, deactivate it and modify */
    //if(MTP3_OSS_GetLinkset_CCITT(linkSetId, &linkSetInfo, &numLinkSet) != ITS_SUCCESS)
    if(MTP3_OSS_RemoveLinkset_CCITT(linkSetId) != ITS_SUCCESS)
    {
        DLOG_ERROR("Failed to fetch AssociationSet Error : %d", retVal);
    }

    if(associationSet.has_networkindicator())
    {
        if(IwfController::Instance().Config().LocalConfig().LocalNetworkIndicator() != associationSet.networkindicator())
        {
            DLOG_ERROR("Incoming NetworkIndicator does not match to Local NetworkIndicator");
            return MOD_ASSOCIATIONSET_ERR_NI_NOT_SAME_AS_LOCAL_NI;
        }
        if(associationSet.networkindicator())
        {
            DLOG_DEBUG("Network Indicator is National");
            ni = 128;
        }
        else
        {
            ni = 0;
        }
    }

    if(associationSet.has_adjacenpointcode())
    {
        apc = associationSet.adjacenpointcode();
    }
    /* TODO : To call the Sigtran Api's for ANSI in else case same as CCITT */
    if((retVal = MTP3_OSS_AddLinkset_CCITT(linkSetId, family, lpc, apc,
                    ni)) != ITS_SUCCESS)
    {
        switch(retVal)
        {
            case ADD_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND:
                {
                    retVal = MOD_ASSOCIATIONSET_ERR_FAILED_AT_BACKEND;
                    break;
                }
            default:
                {
                    retVal = MOD_ASSOCIATIONSET_ERR_GENERIC_ERROR;
                }
        }
        //NOTE: Returning success eventhough modify fails because, user is prompted for restart for modification.
        DLOG_ERROR("CMAPIIwfConfig::ModifyAssociationSet: Modification of AssociationSet with AssociationSetId - %d failed, Error %d", linkSetId, retVal);
        return ITS_SUCCESS;
    }

    if(associationSet.has_routingcontext())
    {
        if(associationSet.has_trafficmode())
        {
            DLOG_DEBUG("CMAPIIwfConfig::SetAssociationSet: Incoming Traffic Mode: %s", associationSet.trafficmode().c_str());
            if(strcmp(associationSet.trafficmode().c_str(), UAL_LOAD_SHARE_MODE_STRING) == 0)
            {
                trafficMode = UAL_LOADSHARE;
            }
            else if(strcmp(associationSet.trafficmode().c_str(), UAL_OVERIDE_MODE_STRING) == 0)
            {
                trafficMode = UAL_OVERRIDE;
            }
            else
            {
                DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Invalid Traffic Mode Configured");
                retVal = ADD_ASSOCIATIONSET_ERR_INVALID_TRAFFIC_MODE;
                return retVal;
            }

            rkey = associationSet.routingcontext();

            if((retVal = CreateApplicationServer(rkey, (char *)localFamily.c_str(), trafficMode, ni, ITS_YES)) != ITS_SUCCESS)
            {
                DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server: Error %d", retVal);
                return retVal;
            }
        }
#if 0
        if(associationSet.has_aspid())
        {
            if((retVal = CreateApplicationServerProcess(rkey, associationSet.aspid())) != ITS_SUCCESS)
            {
                DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Unable to create Application Server Process: Error %d", retVal));
                return retVal;
            }
        }
#endif
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet: Mandatory Parameters missing in UAL Configuration..!!");
        retVal = ADD_UALCONFIG_ERR_MISSING_MANDATORY_PARAM;
        return retVal;;
    }

    DLOG_DEBUG("CMAPIIwfConfig::ModifyAssociationSet Exit");
    return retVal;
}
int  CMAPIIwfConfig::DeleteAssociationSet(IwfSigtranAssociationSetConfig associationSet)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::DeleteAssociationSet Entry");
    int retVal = CMAPI_SUCCESS;
    ITS_UINT rkey = 0;
    if(associationSet.has_routingcontext())
    {
        rkey = associationSet.routingcontext();
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::DeleteAssociationSet: Routing Context not present");
        return !ITS_SUCCESS;
    }

    /* TODO check if linkset is activated, deactivate it and delete */
    if((retVal = MTP3_OSS_RemoveLinkset_CCITT(associationSet.associationsetid())) != ITS_SUCCESS)
    {
        DLOG_ERROR("Deletion of AssociationSet failed, Error %d", retVal);
    }

    /* As RoutingKeyRoute will be same for multiple AssocaitionSet so
     * not removing the below configuartion */

    /*if(MTP3_OSS_RemoveRoutingKeyRoute_CCITT(rkey) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::SetAssociationSet Deletion of RoutingKey Route failed%d", retVal);
      }

      if(associationSet.has_aspid())
      {
      if((retVal = DeleteApplicationServerProcess(rkey, associationSet.aspid())) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::DeleteAssociationSet: Deletion of ApplicationServerProcess failed, Error %d", retVal);
      }
      }

      if((retVal = DeleteApplicationServer(rkey)) != ITS_SUCCESS)
      {
      DLOG_ERROR("CMAPIIwfConfig::DeleteAssociationSet: Deletion of ApplicationServer failed, Error %d", retVal);
      }*/

    DLOG_DEBUG("CMAPIIwfConfig::DeleteAssociationSet Exit");
    return retVal;
}
int CMAPIIwfConfig::HandleAssociationConfigReqs(IwfSigtranAssociationsConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    int errorCode;
    int totalAssoicationNum = req->associationinfo_size();
    if(totalAssoicationNum > 0)
    {
        for (int assocNum = 0; assocNum < totalAssoicationNum; assocNum++)
        {
            try
            {
                IwfSigtranAssociationConfig assocCfg = req->associationinfo(assocNum);
                switch(req->operreqid())
                {
                    case SET_ASSOC:
                        {
                            if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                            {
                                retVal = SetAssociationConfig(assocCfg);
                                if(retVal != ITS_SUCCESS)
                                {
                                    ErrorDetails* err = resp->add_errordetails();
                                    errorCode = retVal;
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(assocCfg.associationname());
                                    err->add_variables(assocCfg.associationsetname());
                                    retVal = CMAPI_SRVERROR;
                                }
                            }
                            else
                            {
                                retVal = CMAPI_INVALIDPARAMS;
                            }
                            break;
                        }
                    case MOD_ASSOC:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = ModifyAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = MOD_ASSOCIATION_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case MOD_SCTP_ENDPOINT:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = ModifyAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = MOD_SCTPENDPOINT_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case MOD_SCTP_PROFILE:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = ModifyAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = MOD_SCTPPROFILE_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case DEL_ASSOC:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = DeleteAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = DEL_ASSOCIATION_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case DEL_SCTP_ENDPOINT:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = DeleteAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = DEL_SCTPENDPOINT_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case DEL_SCTP_PROFILE:
                        {
                            /*if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                              {
                              retVal = DeleteAssociationConfig(assocCfg);
                              if(retVal != ITS_SUCCESS)
                              {*/
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = DEL_SCTPPROFILE_NOT_SUPPORTED;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(assocCfg.associationname());
                            err->add_variables(assocCfg.associationsetname());
                            retVal = CMAPI_SRVERROR;
                            /*}
                              }
                              else
                              {
                              retVal = CMAPI_INVALIDPARAMS;
                              }*/
                            break;
                        }
                    case ACTIVATE_ASSOC:
                        {
                            if(assocCfg.has_associationmappingid() && assocCfg.has_associationsetid())
                            {
                            }
                            else
                            {
                                retVal = CMAPI_INVALIDPARAMS;
                            }
                            break;
                        }
                    default:
                        DLOG_ERROR("CMAPIIwfConfig::HandleAssociationConfigReqs : Invalid Request for Association Configuration");
                }
            }
            catch(...)
            {
                DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationSetConfigReqs : Exception ");
            }
        }
    }
    /* BorderPool
     * localtransport - ip, port
     * sctp profile for local
     * Associate value to be taken from remote endpoint name
     * remote endpoint - name, ip, port
     * modifiers to be set as is of xml.
     * link id will be taken association tb
     * socketDomain to be as INET
     */
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleAssociationConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::SetAssociationConfig(IwfSigtranAssociationConfig association)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::SetAssociationConfig Entry");
    int retVal = ITS_SUCCESS;
    ITS_OCTET linkSet;
    std::string remoteTransportName = "";
    std::string localTransportName = "";
    std::string endPointType = "";
    ENGINE_TransportSpecificsPart localInfo;
    ENGINE_TransportSpecificsPart virtualInfo;
    int transportInstance = 0;

    std::string family = "";
    if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ITU)
    {
        family = "ITU";
    }
    else if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ANSI)
    {
        family = "ANSI";
    }

    if(association.has_aspid())
    {
        if(IwfController::Instance().Config().LocalConfig().GetASPId() != association.aspid())
        {
            DLOG_DEBUG("Incoming ASPId  %d does not does not matches Locally Configured ASPId %d",
                    association.aspid(), IwfController::Instance().Config().LocalConfig().GetASPId());
            return CMAPI_SUCCESS;
        }
    }

    if(association.has_associationsetid())
    {
        linkSet = (ITS_OCTET)association.associationsetid();
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing AssociationSet Configuration..!!");
        retVal = ADD_ASSOCIATION_ERR_ASSOCIATION_SET_NOT_PRESENT;
        return retVal;
    }

    if(association.has_sctpprofile())
    {
        IwfSigtranSctpProfileConfig sctpProfileCfg = association.sctpprofile();
        if(sctpProfileCfg.has_maxinstreams())
        {
            localInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.maxInStreams, "%d", sctpProfileCfg.maxinstreams());

            virtualInfo.data.sctpSpecs.maxInStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.maxInStreams, "%d", sctpProfileCfg.maxinstreams());
        }
        if(sctpProfileCfg.has_numoutstreams())
        {
            localInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.numOutStreams, "%d", sctpProfileCfg.numoutstreams());

            virtualInfo.data.sctpSpecs.numOutStreams =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.numOutStreams, "%d", sctpProfileCfg.numoutstreams());
        }
        if(sctpProfileCfg.has_maxattempt())
        {
            localInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.maxAttempts, "%d", sctpProfileCfg.maxattempt());

            virtualInfo.data.sctpSpecs.maxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.maxAttempts, "%d", sctpProfileCfg.maxattempt());
        }
        if(sctpProfileCfg.has_assocmaxattempt())
        {
            localInfo.data.sctpSpecs.assoMaxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.assoMaxAttempts, "%d", sctpProfileCfg.assocmaxattempt());

            virtualInfo.data.sctpSpecs.assoMaxAttempts =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.assoMaxAttempts, "%d", sctpProfileCfg.assocmaxattempt());
        }
        if(sctpProfileCfg.has_cookielife())
        {
            localInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.cookieLife, "%d", sctpProfileCfg.cookielife());

            virtualInfo.data.sctpSpecs.cookieLife =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.cookieLife, "%d", sctpProfileCfg.cookielife());
        }
        if(sctpProfileCfg.has_heartbeatenable())
        {
            localInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(localInfo.data.sctpSpecs.hbOn, ((sctpProfileCfg.heartbeatenable() == 1) ? "yes" : "no"));

            virtualInfo.data.sctpSpecs.hbOn =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(virtualInfo.data.sctpSpecs.hbOn, ((sctpProfileCfg.heartbeatenable() == 1) ? "yes" : "no"));
        }
        if(sctpProfileCfg.has_inittimeout())
        {
            uint32_t initTimeOut = (sctpProfileCfg.inittimeout());
            localInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(initTimeOut)
                sprintf(localInfo.data.sctpSpecs.initTimeOut, "%d,%d", initTimeOut/1000,initTimeOut%1000);
            else
                sprintf(localInfo.data.sctpSpecs.initTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.initTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(initTimeOut)
                sprintf(virtualInfo.data.sctpSpecs.initTimeOut, "%d,%d", initTimeOut/1000,initTimeOut%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.initTimeOut, "0,0");
        }
        if(sctpProfileCfg.has_sendtimeout())
        {
            uint32_t sendTimeOut = (sctpProfileCfg.sendtimeout());
            localInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(sctpProfileCfg.sendtimeout())
                sprintf(localInfo.data.sctpSpecs.sendTimeOut, "%d,%d", sendTimeOut/1000,sendTimeOut%1000);
            else
                sprintf(localInfo.data.sctpSpecs.sendTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.sendTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(sctpProfileCfg.sendtimeout())
                sprintf(virtualInfo.data.sctpSpecs.sendTimeOut, "%d,%d", sendTimeOut/1000,sendTimeOut%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.sendTimeOut, "0,0");
        }
        if(sctpProfileCfg.has_receivetimeout())
        {
            localInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(sctpProfileCfg.receivetimeout())
                sprintf(localInfo.data.sctpSpecs.recvTimeOut, "%d,%d", sctpProfileCfg.receivetimeout()/1000,sctpProfileCfg.receivetimeout()%1000);
            else
                sprintf(localInfo.data.sctpSpecs.recvTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.recvTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(sctpProfileCfg.receivetimeout())
                sprintf(virtualInfo.data.sctpSpecs.recvTimeOut, "%d,%d", sctpProfileCfg.receivetimeout()/1000,sctpProfileCfg.receivetimeout()%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.recvTimeOut, "0,0");
        }
        if(sctpProfileCfg.has_heartbeattimeout())
        {
            uint32_t hbTimeOut = (sctpProfileCfg.heartbeattimeout());
            localInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(hbTimeOut)
                sprintf(localInfo.data.sctpSpecs.hbTimeOut, "%d,%d", hbTimeOut/1000,hbTimeOut%1000);
            else
                sprintf(localInfo.data.sctpSpecs.hbTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.hbTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(hbTimeOut)
                sprintf(virtualInfo.data.sctpSpecs.hbTimeOut, "%d,%d", hbTimeOut/1000,hbTimeOut%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.hbTimeOut, "0,0");

        }
        if(sctpProfileCfg.has_shutdowntimeout())
        {
            uint32_t shutdownTimeOut = (sctpProfileCfg.shutdowntimeout());
            localInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(shutdownTimeOut)
                sprintf(localInfo.data.sctpSpecs.shutdownTimeOut, "%d,%d", shutdownTimeOut/1000,shutdownTimeOut%1000);
            else
                sprintf(localInfo.data.sctpSpecs.shutdownTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.shutdownTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(shutdownTimeOut)
                sprintf(virtualInfo.data.sctpSpecs.shutdownTimeOut, "%d,%d", shutdownTimeOut/1000,shutdownTimeOut%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.shutdownTimeOut, "0,0");
        }
        if(sctpProfileCfg.has_pmtutimeout())
        {
            uint32_t pmtuTimeOut = (sctpProfileCfg.pmtutimeout());
            localInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(pmtuTimeOut)
                sprintf(localInfo.data.sctpSpecs.pmtuTimeOut, "%d,%d", pmtuTimeOut/1000,pmtuTimeOut%1000);
            else
                sprintf(localInfo.data.sctpSpecs.pmtuTimeOut, "0,0");

            virtualInfo.data.sctpSpecs.pmtuTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            if(pmtuTimeOut)
                sprintf(virtualInfo.data.sctpSpecs.pmtuTimeOut, "%d,%d", pmtuTimeOut/1000,pmtuTimeOut%1000);
            else
                sprintf(virtualInfo.data.sctpSpecs.pmtuTimeOut, "0,0");
        }
        if(sctpProfileCfg.has_rtomax())
        {
            localInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());

            virtualInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());
        }
        if(sctpProfileCfg.has_rtomin())
        {
            localInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());

            virtualInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());
        }
        if(sctpProfileCfg.has_rtoinitial())
        {
            localInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoInitial, "%d", sctpProfileCfg.rtoinitial());

            virtualInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoInitial , "%d", sctpProfileCfg.rtoinitial());
        }
        if(sctpProfileCfg.has_sackdelay())
        {
            localInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());

            virtualInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());
        }
        if(sctpProfileCfg.has_sendbufsize())
        {
            localInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.sendBufSize , "%d", sctpProfileCfg.sendbufsize());

            virtualInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.sendBufSize, "%d", sctpProfileCfg.sendbufsize());
        }
        if(sctpProfileCfg.has_recvbufsize())
        {
            localInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.recvBufSize , "%d", sctpProfileCfg.recvbufsize());

            virtualInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.recvBufSize, "%d", sctpProfileCfg.recvbufsize());
        }
        if(sctpProfileCfg.has_reconnecttimeout())
        {
            localInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());

            virtualInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());
        }
        if(sctpProfileCfg.has_pathfailureretrycount())
        {
            localInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.pathmaxrxt , "%d", sctpProfileCfg.pathfailureretrycount());

            virtualInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.pathmaxrxt , "%d", sctpProfileCfg.pathfailureretrycount());
        }
        if(sctpProfileCfg.has_rtomax())
        {
            localInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());

            virtualInfo.data.sctpSpecs.rtoMax =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoMax , "%d", sctpProfileCfg.rtomax());
        }
        if(sctpProfileCfg.has_rtomin())
        {
            localInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());

            virtualInfo.data.sctpSpecs.rtoMin =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoMin, "%d", sctpProfileCfg.rtomin());
        }
        if(sctpProfileCfg.has_rtoinitial())
        {
            localInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.rtoInitial, "%d", sctpProfileCfg.rtoinitial());

            virtualInfo.data.sctpSpecs.rtoInitial =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.rtoInitial , "%d", sctpProfileCfg.rtoinitial());
        }
        if(sctpProfileCfg.has_sackdelay())
        {
            localInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());

            virtualInfo.data.sctpSpecs.sackDelay =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.sackDelay , "%d", sctpProfileCfg.sackdelay());
        }
        if(sctpProfileCfg.has_sendbufsize())
        {
            localInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.sendBufSize , "%d", sctpProfileCfg.sendbufsize());

            virtualInfo.data.sctpSpecs.sendBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.sendBufSize, "%d", sctpProfileCfg.sendbufsize());
        }
        if(sctpProfileCfg.has_recvbufsize())
        {
            localInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.recvBufSize , "%d", sctpProfileCfg.recvbufsize());

            virtualInfo.data.sctpSpecs.recvBufSize =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.recvBufSize, "%d", sctpProfileCfg.recvbufsize());
        }
        if(sctpProfileCfg.has_reconnecttimeout())
        {
            localInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());

            virtualInfo.data.sctpSpecs.reconnectTimeOut =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.reconnectTimeOut, "%d", sctpProfileCfg.reconnecttimeout());
        }
        if(sctpProfileCfg.has_pathfailureretrycount())
        {
            localInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.pathmaxrxt , "%d", sctpProfileCfg.pathfailureretrycount());

            virtualInfo.data.sctpSpecs.pathmaxrxt =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.pathmaxrxt , "%d", sctpProfileCfg.pathfailureretrycount());
        }

        /* Payload type to be filled based on the family configured to be discusseed */
        localInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
        strcpy(localInfo.data.sctpSpecs.payloadType, "CCITT");
        strcat(localInfo.data.sctpSpecs.payloadType , "-M3UA");

        virtualInfo.data.sctpSpecs.payloadType =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
        strcpy(virtualInfo.data.sctpSpecs.payloadType, "CCITT");
        strcat(virtualInfo.data.sctpSpecs.payloadType , "-M3UA");

        /* isClient to be filled in sctp profile or not */
        localInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
        strcpy(localInfo.data.sctpSpecs.isClient, "yes");

        virtualInfo.data.sctpSpecs.isClient =  (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
        strcpy(virtualInfo.data.sctpSpecs.isClient, "yes");
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing Sctp Profile..!!");
        retVal = ADD_ASSOCIATION_ERR_SCTP_PROFILE_NOT_PRESENT;
        return retVal;
    }
    /* validate all localhost's ip address before adding the remote/local
     * endpoint into association */
    if( association.has_localendpoint() )
    {
        std::vector<std::string> localIp;
        int port = 0;
        IwfSigtranSctpEndPointConfig localEndPoint = association.localendpoint();
        if( localEndPoint.has_ipaddress() && localEndPoint.has_port() )
        {
            /* first entry in the vector will the localhost's primay ip */
            localIp.push_back(localEndPoint.ipaddress());
            if (localEndPoint.multihominginfo_size() >  0)
            {
                for(int numExtrahomes = 0; numExtrahomes < localEndPoint.multihominginfo_size() ; numExtrahomes++)
                {
                    IwfSigtranMultihomingConfig multiHomingInfo = localEndPoint.multihominginfo(numExtrahomes);
                    if(multiHomingInfo.has_otheripaddress())
                    {
                        localIp.push_back(multiHomingInfo.otheripaddress());
                    }
                }
            }

            /* validate the localhost ip's recieved from configuration to ensure
             * all ip's are valid ip if not send error response to CMGR */
            if ( !ITS_SUCCESS == IWFUtils::ValidateLocalHostIP(localIp, port) )
            {
                DLOG_ERROR("Validation of LocalHost IP(s) configured failed, unable to add Asscociation");
                retVal = ADD_ASSOCIATION_ERR_FAILED_INVALID_LOCAL_ENDPOINT_IP;
                return retVal;
            }
        }
        else
        {
            DLOG_ERROR("Missing LocalEndPoint configuration ");
        }
    }

    if(association.has_remoteendpoint())
    {
        IwfSigtranSctpEndPointConfig remoteEndPoint = association.remoteendpoint();

        virtualInfo.data.sctpSpecs.numExtraHomes = remoteEndPoint.multihominginfo_size();
        if (virtualInfo.data.sctpSpecs.numExtraHomes > 0)
        {
            virtualInfo.data.sctpSpecs.extraHomes = (char**)malloc
                ((remoteEndPoint.multihominginfo_size()) * sizeof(char*));
            for(int numExtrahomes = 0; numExtrahomes < virtualInfo.data.sctpSpecs.numExtraHomes; numExtrahomes++)
            {
                IwfSigtranMultihomingConfig multiHomingInfo = remoteEndPoint.multihominginfo(numExtrahomes);
                if(multiHomingInfo.has_otheripaddress())
                {
                    virtualInfo.data.sctpSpecs.extraHomes[numExtrahomes] = (char*)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                    strcpy(virtualInfo.data.sctpSpecs.extraHomes[numExtrahomes],
                            multiHomingInfo.otheripaddress().c_str());
                }
            }
        }

        virtualInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
        virtualInfo.data.sctpSpecs.udpPart.numAssociates = 0;
        virtualInfo.data.sctpSpecs.numExtraHomes = 0;

        if(remoteEndPoint.has_endpointtype())
        {
            endPointType = remoteEndPoint.endpointtype();
        }
        if(remoteEndPoint.has_endpointname() && remoteEndPoint.has_ipaddress() && remoteEndPoint.has_port())
        {
            remoteTransportName = remoteEndPoint.endpointname();

            virtualInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(virtualInfo.data.sctpSpecs.udpPart.localHost, remoteEndPoint.ipaddress().c_str());

            virtualInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(virtualInfo.data.sctpSpecs.udpPart.localPort,"%d", (remoteEndPoint.port()));

            retVal = SetBorderPoolTransport_CCITT((char *)remoteTransportName.c_str(), (char *)"Virtual", (char *)family.c_str(), (char *)"MTP3 SCTP", virtualInfo);
            if(retVal == ITS_ENOMEM)
            {
                DLOG_ERROR(" Failed to Set BorderPool for Remote EndPoint errorCode = %d ", retVal);
                retVal = ADD_ASSOCIATION_ERR_FAILED_TO_ADD_REMOTE_ENDPOINT;
                return retVal;
            }
            transportInstance = retVal;
        }
        else
        {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Mandatory Paramter Missing in Remote EndPoint..!!");
            retVal = ADD_ASSOCIATION_ERR_MISSING_MANDATORY_PARAM;
            return retVal;
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing  Remote EndPoint..!!");
        retVal = ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        return retVal;
    }

    if(association.has_localendpoint())
    {
        IwfSigtranSctpEndPointConfig localEndPoint = association.localendpoint();

        localInfo.data.sctpSpecs.numExtraHomes = localEndPoint.multihominginfo_size();
        if (localInfo.data.sctpSpecs.numExtraHomes > 0)
        {
            localInfo.data.sctpSpecs.extraHomes = (char**)malloc
                ((localEndPoint.multihominginfo_size()) * sizeof(char*));
            for(int numExtrahomes = 0; numExtrahomes < localInfo.data.sctpSpecs.numExtraHomes; numExtrahomes++)
            {
                IwfSigtranMultihomingConfig multiHomingInfo = localEndPoint.multihominginfo(numExtrahomes);
                if(multiHomingInfo.has_otheripaddress())
                {
                    localInfo.data.sctpSpecs.extraHomes[numExtrahomes] = (char*)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
                    strcpy(localInfo.data.sctpSpecs.extraHomes[numExtrahomes],
                            multiHomingInfo.otheripaddress().c_str());
                }
            }
        }

        localInfo.mask = ITS_TRANSPORT_SCTP_SOCKET;
        if(localEndPoint.has_endpointtype())
        {
            endPointType = localEndPoint.endpointtype();
        }
        if(localEndPoint.has_endpointname() && localEndPoint.has_ipaddress() && localEndPoint.has_port())
        {
            localTransportName = localEndPoint.endpointname();
            localTransportName += association.associationname();

            localInfo.data.sctpSpecs.udpPart.localHost = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(localInfo.data.sctpSpecs.udpPart.localHost, localEndPoint.ipaddress().c_str());

            localInfo.data.sctpSpecs.udpPart.localPort = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            sprintf(localInfo.data.sctpSpecs.udpPart.localPort,"%d", (localEndPoint.port()));

            localInfo.data.sctpSpecs.udpPart.associates = (char **)malloc(sizeof(char *));
            localInfo.data.sctpSpecs.udpPart.associates[0] = (char *)malloc(IWF_ASSOC_MAX_STR_LEN * sizeof(char));
            strcpy(localInfo.data.sctpSpecs.udpPart.associates[0], remoteTransportName.c_str());
            localInfo.data.sctpSpecs.udpPart.numAssociates = 1;

            retVal = SetBorderPoolTransport_CCITT((char *)localTransportName.c_str(), (char *)"Datagram", (char *)family.c_str(), (char *)"MTP3 SCTP", localInfo);
            if(retVal == ITS_ENOMEM)
            {
                DLOG_ERROR(" Failed to Set BorderPool for Local EndPoint errorCode = %d ", retVal);
                retVal = ADD_ASSOCIATION_ERR_FAILED_TO_ADD_LOCAL_ENDPOINT;
                return retVal;
            }
        }
        else
        {
            DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Mandatory Paramter Missing in Local EndPoint..!!");
            retVal = ADD_ASSOCIATION_ERR_MISSING_MANDATORY_PARAM;
            return retVal;
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing Local EndPoint..!!");
        retVal = ADD_ASSOCIATION_ERR_SCTP_END_POINT_NOT_PRESENT;
        return retVal;
    }

    TRANSPORT_Control   *tc = NULL;
    while(tc == NULL)
    {
        usleep(100);
        DLOG_DEBUG("Entering TRANSPORT Find LOOP");
        tc = TRANSPORT_FindTransport(transportInstance);
    }

    if(association.has_associationmappingid())
    {
        if((retVal = MTP3_OSS_AddLink_CCITT(linkSet, (ITS_OCTET) association.associationmappingid(), transportInstance)) != ITS_SUCCESS)
        {
            DLOG_ERROR("Addition of Association falied, Error %d", retVal);
            return retVal;
        }
        if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
        {
            IwfSigtranSctpEndPointConfig remoteEndPoint = association.remoteendpoint();
            if(remoteEndPoint.has_ipaddress() && remoteEndPoint.has_port() && association.has_routingkey() && association.has_homeip())
            {
                DLOG_DEBUG("Adding entry to RoutingKey Map with Ip %s port %d routingKey %d homeIp %s",remoteEndPoint.ipaddress().c_str(),
                        remoteEndPoint.port(),association.routingkey(), association.homeip().c_str());
                IwfController::Instance().Config().LocalConfig().InsertEntryinRoutkingKeyMap(remoteEndPoint.ipaddress().c_str(),
                        remoteEndPoint.port(),association.routingkey(), association.homeip().c_str());
                for(int numExtrahomes = 0; numExtrahomes < remoteEndPoint.multihominginfo_size(); numExtrahomes++)
                {
                    IwfSigtranMultihomingConfig multiHomingInfo = remoteEndPoint.multihominginfo(numExtrahomes);
                    if(multiHomingInfo.has_otheripaddress())
                    {
                        DLOG_DEBUG("Adding entry to RoutingKey Map with Secondary Ip %s port %d routingKey %d homeIp %s",
                                multiHomingInfo.otheripaddress().c_str(),remoteEndPoint.port(),association.routingkey(),
                                association.homeip().c_str());
                        IwfController::Instance().Config().LocalConfig().InsertEntryinRoutkingKeyMap(
                                multiHomingInfo.otheripaddress().c_str(),remoteEndPoint.port(),association.routingkey(),
                                association.homeip().c_str());
                    }
                }
            }
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::SetAssociationConfig: Missing AssociationMappingId..!!");
        retVal = ADD_ASSOCIATION_ERR_MISSING_MANDATORY_PARAM;
        return retVal;
    }

    DLOG_DEBUG("CMAPIIwfConfig::SetAssociationConfig Exit");
    return retVal;
}

int CMAPIIwfConfig::ModifyAssociationConfig(IwfSigtranAssociationConfig association)
{
    int retVal = ITS_SUCCESS;
    return retVal;
}
int CMAPIIwfConfig::DeleteAssociationConfig(IwfSigtranAssociationConfig association)
{
    int retVal = ITS_SUCCESS;
    //MTP3_OSS_RemoveLink_CCITT((ITS_OCTET)1,(ITS_OCTET)2);
    /*TRANSPORT_Control *transport = TRANSPORT_FindTransportByName("sg1");
      SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)transport, 20002);
      SOCKTRAN_DeleteEndPointTransport((SOCKTRAN_Manager *)transport);
      transport = TRANSPORT_FindTransportByName("iwf1");
      SOCKTRAN_DeleteEndPointTransport((SOCKTRAN_Manager *)transport);*/

    //retVal = DeleteBorderPoolTransport_CCITT(20003);

    return retVal;
}

int CMAPIIwfConfig::HandleRemoteRouteConfigReqs(IwfSigtranRemoteRoutesConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleRemoteRouteConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    int errorCode = MAX_ERROR_MOD_TRANS_RULES;
    int numOfRoute = 0;
    IwfSigtranRemoteRouteConfig remoteRoute;
    IwfSigtranDestinationConfig destInfo;
    ITS_OCTET linkSet;
    ITS_UINT priority = 0;
    ITS_UINT rpc;
    ITS_OCTET ssn;
    ITS_OCTET sio;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();

    /* iwf will receive route and destination data in single request
     * for pc-ssn
     * create remote route
     * style dpc-sio-ssn because tcap
     * type will be filled by iwf - remoteroute
     * linkset and priority will get
     * DPC from pointcode from destination_tb
     *
     * for gtt
     * create remote route as above
     * fill DPC of remote route from APC coming in associationset_tb*/

    /* at iwf side
     * fil the IWF structure with incoming values of GTT in destination structure
     * and create map of gtt-apc*/
    numOfRoute = req->remoterouteinfo_size();
    switch(req->operreqid())
    {
        case SET_REMOTE_ROUTE:
            {
                DLOG_DEBUG("HandleRemotRouteConfigReqs:: Add Remote Route Info");
                if( numOfRoute > 0)
                {
                    for( int currRoute = 0 ; currRoute < numOfRoute; currRoute++ )
                    {
                        remoteRoute = req->remoterouteinfo(currRoute);
                        /* this part of code will handle adding of Remote
                         * Route to the Sigtran stack once it is success we
                         * will proceed in adding the IWFDestination info
                         */
                        if(remoteRoute.has_associationsetid() && remoteRoute.has_destinationinfo() && remoteRoute.has_priority())
                        {
                            destInfo = remoteRoute.destinationinfo();
                            if(destInfo.has_pointcode() && destInfo.has_ssn() && destInfo.has_networkindicator())
                            {
                                linkSet = (ITS_OCTET)remoteRoute.associationsetid();
                                priority = remoteRoute.priority();
                                rpc = destInfo.pointcode();
                                ssn = (ITS_OCTET)destInfo.ssn();
                                if(destInfo.networkindicator())
                                {
                                    DLOG_DEBUG("Network Indicator is National");
                                    sio = IWF_NATIONAL_SIO;
                                }
                                else
                                {
                                    DLOG_DEBUG("Network Indicator is International");
                                    sio = IWF_INTERNATIONAL_SIO;
                                }

                                /* TODO : To call the Sigtran Api's for ANSI in else case same as CCITT */
                                if((retVal = MTP3_OSS_AddRemotePC_CCITT(rpc, sio, ssn, linkSet, priority, family)) != ITS_SUCCESS)
                                {
                                    DLOG_ERROR("HandleRemotRouteConfigReqs:: Failed to add RemoteRoute Error %d", retVal);
                                    ErrorDetails* err = resp->add_errordetails();
                                    errorCode = retVal;
                                    err->set_errorcode(errorCode);
                                    err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                    err->add_variables(remoteRoute.remoteroutename());
                                    retVal = CMAPI_SRVERROR;
                                }
                                if( remoteRoute.has_destinationinfo() && retVal == ITS_SUCCESS)
                                {
                                    destInfo = remoteRoute.destinationinfo();
                                    retVal = IwfController::Instance().Config().
                                        Destinations().SetIwfDestinationConfig(&destInfo);
                                    if ( retVal != CMAPI_SUCCESS )
                                    {
                                        ErrorDetails* error = resp->add_errordetails();
                                        errorCode = retVal;
                                        error->set_errorcode(errorCode);
                                        error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                        retVal = CMAPI_SRVERROR;
                                    }
                                }
                            }
                            else
                            {
                                DLOG_ERROR("HandleRemotRouteConfigReqs:: Missing Mandatory Parameter in DestinationInfo");
                                ErrorDetails* err = resp->add_errordetails();
                                errorCode = ADD_DESTINATION_ERR_MISSING_MANDATORY_PARAM;
                                err->set_errorcode(errorCode);
                                err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                err->add_variables(destInfo.destinationname());
                                retVal = CMAPI_SRVERROR;
                            }
                        }
                        else
                        {
                            DLOG_ERROR("HandleRemotRouteConfigReqs:: Missing Mandatory Parameter in RemoteRouteInfo");
                            ErrorDetails* err = resp->add_errordetails();
                            errorCode = ADD_ROUTE_ERR_MISSING_MANDATORY_PARAM;
                            err->set_errorcode(errorCode);
                            err->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            err->add_variables(remoteRoute.remoteroutename());
                            retVal = CMAPI_SRVERROR;
                        }
                    }
                }
                else
                {
                    DLOG_ERROR("HandleRemoteRoute no remote route data in request");
                    retVal = CMAPI_INVALIDPARAMS;
                }
            }
            break;
        case MOD_REMOTE_ROUTE:
            {
                DLOG_DEBUG("HandleRemotRouteConfigReqs:: Modify Remote Route Info");
                if( numOfRoute > 0)
                {
                    for( int currRoute = 0 ; currRoute < numOfRoute; currRoute++ )
                    {
                        remoteRoute = req->remoterouteinfo(currRoute);
                        /* this part of code will handle adding of Remote
                         * Route to the Sigtran stack once it is success we
                         * will proceed in adding the IWFDestination info
                         */
                        retVal = ModifyRemoteRoute(remoteRoute);
                        if (retVal != ITS_SUCCESS)
                        {
                            ErrorDetails* error = resp->add_errordetails();
                            errorCode = retVal;
                            error->set_errorcode(errorCode);
                            error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            retVal = CMAPI_SRVERROR;
                        }

                        if(remoteRoute.has_destinationinfo())
                        {
                            destInfo = remoteRoute.destinationinfo();
                            retVal = IwfController::Instance().Config().
                                Destinations().ModifyIwfDestinationConfig(&destInfo);

                            if ( retVal != CMAPI_SUCCESS )
                            {
                                ErrorDetails* error = resp->add_errordetails();
                                errorCode = retVal;
                                error->set_errorcode(errorCode);
                                error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                                retVal = CMAPI_SRVERROR;
                            }
                        }
                    }
                }
                else
                {
                    DLOG_ERROR("HandleRemoteRoute no remote route data in request");
                    retVal = CMAPI_INVALIDPARAMS;
                }
            }
            break;
        case DEL_REMOTE_ROUTE:
            {
                DLOG_DEBUG("HandleRemotRouteConfigReqs:: Delete Remote Route Info");
                if( numOfRoute > 0)
                {
                    for( int currRoute = 0 ; currRoute < numOfRoute; currRoute++ )
                    {
                        remoteRoute = req->remoterouteinfo(currRoute);
                        /* this part of code will handle adding of Remote
                         * Route to the Sigtran stack once it is success we
                         * will proceed in adding the IWFDestination info
                         */
                        retVal = DeleteRemoteRoute(remoteRoute);
                        if (retVal != ITS_SUCCESS)
                        {
                            ErrorDetails* error = resp->add_errordetails();
                            errorCode = retVal;
                            error->set_errorcode(errorCode);
                            error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                            retVal = CMAPI_SRVERROR;
                        }

                        /*if( remoteRoute.has_destinationinfo() )
                          {
                          destInfo = remoteRoute.destinationinfo();
                          retVal = IwfController::Instance().Config().
                          Destinations().DeleteIwfDestinationConfig(&destInfo);

                          if ( retVal != CMAPI_SUCCESS )
                          {
                          ErrorDetails* error = resp->add_errordetails();
                          errorCode = retVal;
                          error->set_errorcode(errorCode);
                          error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                          retVal = CMAPI_SRVERROR;
                          }
                          }*/
                    }
                }
                else
                {
                    DLOG_ERROR("HandleRemoteRoute no remote route data in request");
                    retVal = CMAPI_INVALIDPARAMS;
                }
            }
            break;
        default:
            {
                DLOG_ERROR("CMAPIIwfConfig::HandleRemoteRouteConfig invalid request received");
                retVal = CMAPI_INVALIDPARAMS;

            }
            break;
    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleRemoteRouteConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::ModifyRemoteRoute(IwfSigtranRemoteRouteConfig remoteRouteConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(("CMAPIIwfConfig::ModifyRemoteRoute: Entry"));
    int retVal = ITS_SUCCESS;
    ITS_UINT oldPointCode;
    ITS_UINT currPointCode;
    ITS_OCTET ssn;
    IwfSigtranDestinationConfig destInfo;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    SS7_Destination *sS7dest;
    ITS_OCTET linkSet;
    ITS_OCTET sio;
    ITS_UINT priority;

    if(remoteRouteConfig.has_oldpointcode())
    {
        oldPointCode = remoteRouteConfig.oldpointcode();
    }
    else
    {
        DLOG_ERROR("Missing OldPointCode");
        return MOD_ROUTE_ERR_MISSING_MANDATORY_PARAMETER;
    }

    if(remoteRouteConfig.has_destinationinfo())
    {
        destInfo = remoteRouteConfig.destinationinfo();
        if(destInfo.has_pointcode())
        {
            currPointCode = destInfo.pointcode();
        }
        if(destInfo.has_ssn())
        {
            ssn = (ITS_OCTET)destInfo.ssn();
        }
        if(destInfo.has_networkindicator())
        {
            if(destInfo.networkindicator())
            {
                DLOG_DEBUG("Network Indicator is National");
                sio = IWF_NATIONAL_SIO;
            }
            else
            {
                DLOG_DEBUG("Network Indicator is International");
                sio = IWF_INTERNATIONAL_SIO;
            }
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::ModifyRemoteRoute: Missing DestinationInfo");
        return MOD_ROUTE_ERR_MISSING_DEST_INFO;
    }



    if((retVal = MTP3_OSS_GetRemoteRoute_CCITT(oldPointCode, sio, family, &sS7dest)) != ITS_SUCCESS)
    {
        DLOG_ERROR("RemoteRoute Not found with OldPointCode");
        return MOD_ROUTE_ERR_ROUTE_NOT_PRESENT;
    }

    for(unsigned i = 0; i < sS7dest->numEntries; i++)
    {
        if (sS7dest->entries[i]->basic.type == REMOTE_ROUTE)
        {
            linkSet = sS7dest->entries[i]->linkSet->linkSet;
            priority = sS7dest->entries[i]->priority;
            ssn = sS7dest->entries[i]->basic.criteria.ssn;
        }
    }

    if(remoteRouteConfig.has_associationsetid())
    {
        linkSet = (ITS_OCTET)remoteRouteConfig.associationsetid();
    }
    if(remoteRouteConfig.has_priority())
    {
        priority = remoteRouteConfig.priority();
    }

    if((retVal = MTP3_OSS_AddRemotePC_CCITT(currPointCode, sio, ssn, linkSet,
                    priority, family)) != ITS_SUCCESS)
    {
        switch(retVal)
        {
            case ADD_ROUTE_ERR_ASSOCIATION_NOT_PRESENT:
                {
                    retVal = MOD_ROUTE_ERR_ASSOCIATION_NOT_PRESENT;
                }
                break;
            case ADD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT:
                {
                    retVal = MOD_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
                }
                break;
            case ADD_ROUTE_ERR_GENERIC_ERROR:
                {
                    retVal = MOD_ROUTE_ERR_GENERIC_ERROR;
                }
        }
        DLOG_ERROR("Failed to modify RemoteRoute");
    }
    DLOG_DEBUG("CMAPIIwfConfig::ModifyRemoteRoute: Exit");
    return retVal;
}

int CMAPIIwfConfig::DeleteRemoteRoute(IwfSigtranRemoteRouteConfig remoteRouteConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::DeleteRemoteRoute: Entry");
    int retVal = ITS_SUCCESS;
    ITS_OCTET linkSet;
    ITS_UINT remotePointCode;
    ITS_OCTET ssn;
    ITS_OCTET sio;
    ITS_OCTET priority;
    IwfSigtranDestinationConfig destInfo;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    if(remoteRouteConfig.has_associationsetid())
    {
        linkSet = (ITS_OCTET)remoteRouteConfig.associationsetid();
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::DeleteRemoteRoute: AssociationSetId not present");
        return DEL_ROUTE_ERR_ASSOCIATION_SET_NOT_PRESENT;
    }

    if(remoteRouteConfig.has_priority())
    {
        priority = remoteRouteConfig.priority();
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::DeleteRemoteRoute: Priority not present");
        return DEL_ROUTE_ERR_PRIORITY_NOT_PRESENT;
    }

    if(remoteRouteConfig.has_destinationinfo())
    {
        destInfo = remoteRouteConfig.destinationinfo();
        if(destInfo.has_pointcode() && destInfo.has_ssn() && destInfo.has_networkindicator())
        {
            remotePointCode = destInfo.pointcode();
            ssn = (ITS_OCTET)destInfo.ssn();

            if(destInfo.networkindicator())
            {
                DLOG_DEBUG("Network Indicator is National");
                sio = IWF_NATIONAL_SIO;
            }
            else
            {
                DLOG_DEBUG("Network Indicator is International");
                sio = IWF_INTERNATIONAL_SIO;
            }
        }
        else
        {
            DLOG_ERROR("CMAPIIwfConfig::DeleteRemoteRoute: Remote PointCode or SSN or NI not present");
            return DEL_ROUTE_ERR_POINTCODE_OR_SSN_NOT_PRESENT_IN_DEST_INFO;
        }
    }
    else
    {
        DLOG_ERROR("CMAPIIwfConfig::DeleteRemoteRoute: Destination Info not present");
        return DEL_ROUTE_ERR_DESTINATION_NOT_PRESENT;
    }

    if((retVal = MTP3_OSS_RemoveRemotePC_CCITT(remotePointCode, sio, ssn, linkSet, priority, family)) != ITS_SUCCESS)
    {
        DLOG_ERROR("CMAPIIwfConfig::DeleteRemoteRoute: Failed to Delete RemoteRoute Error = %d", retVal);
        return DEL_ROUTE_ERR_DESTINATION_NOT_PRESENT;
    }
    return retVal;
}

int CMAPIIwfConfig::HandleDestinationConfigReqs(IwfSigtranDestinationsConfig *req,IWFCfgResp *resp)
{
    int retVal = CMAPI_SUCCESS;
    return retVal;
}

int CMAPIIwfConfig::HandleTranslatorRuleConfigReqs(IwfTranslatorRulesConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleTranslatorRuleConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    int errorCode = MAX_ERROR_MOD_TRANS_RULES;
    switch(req->operreqid())
    {
        case SET_TRANSLATOR_RULE:
            {
                retVal = IwfController::Instance().Config().RoutingRules().SetRoutingRulesConfig(req);
                if( retVal != CMAPI_SUCCESS)
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = retVal;
                    error->set_errorcode(errorCode);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case MOD_TRANSLATOR_RULE:
            {
                retVal = IwfController::Instance().Config().RoutingRules().ModifyRoutingRulesConfig(req);
                if( retVal != CMAPI_SUCCESS)
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = retVal;
                    error->set_errorcode(errorCode);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_TRANSLATOR_RULE:
            {
                retVal = IwfController::Instance().Config().RoutingRules().DeleteRoutingRulesConfig(req);
                if( retVal != CMAPI_SUCCESS)
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = retVal;
                    error->set_errorcode(errorCode);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_VPLMN_ID:
            {
                retVal = IwfController::Instance().Config().RoutingRules().DeleteAllowedVplmnIdFromRoutingRulesConfig(req);
                if( retVal != CMAPI_SUCCESS)
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = retVal;
                    error->set_errorcode(errorCode);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        default:
            {
                DLOG_ERROR("CMAPIIwfConfig::HandleTranslatorRulesConfig invalid Request received");
                retVal = CMAPI_INVALIDPARAMS;
                ErrorDetails* error = resp->add_errordetails();
                errorCode = MAX_ERROR_MOD_TRANS_RULES;
                error->set_errorcode(retVal);
                error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                retVal = CMAPI_SRVERROR;
            }

    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleTranslatorRuleConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::HandleTranslationDataConfigReqs(IwfTranslationDataConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleTranslationDataConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    int errorCode = MAX_ERROR_MOD_TRANS_DATA;
    switch (req->operreqid())
    {
        case SET_CAPRO_DATA:
        case MOD_CAPRO_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR);
                retVal = translator->SetConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_MOD_CAPRO_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case SET_MAPS6A_DATA:
        case MOD_MAPS6A_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
                retVal = translator->SetConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_MOD_MAPS6A_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case SET_S6AMAP_DATA:
        case MOD_S6AMAP_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(S6A_TO_MAP_STR);
                retVal = translator->SetConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_MOD_S6AMAP_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_CAPRO_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR);
                retVal = translator->DeleteConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_DEL_CAPRO_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_MAPS6A_DATA:
        case DEL_MAPS6A_VPLMN_ID_DATA:
        case DEL_VPLMN_ID_SGSN_MAP_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
                retVal = translator->DeleteConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_DEL_MAPS6A_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case DEL_S6AMAP_DATA:
            {
                IwfTranslator* translator = IwfController::Instance().GetTranslator(S6A_TO_MAP_STR);
                retVal = translator->DeleteConfig(req);
                if( retVal != CMAPI_SUCCESS )
                {
                    ErrorDetails* error = resp->add_errordetails();
                    errorCode = MAX_ERROR_DEL_S6AMAP_DATA;
                    error->set_errorcode(retVal);
                    error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                    retVal = CMAPI_SRVERROR;
                }
            }
            break;
        case CLEAR_SESSION:
            {
                ITS_EVENT event;
                std::string strIMSIToClear = req->imsiforsessionclearance();
                DLOG_DEBUG("Imsi for session clearance = %s", strIMSIToClear.c_str());
                ITS_EVENT_INIT(&event, ITS_DEFAULT_USER_SRC, (sizeof(ITS_UINT) +
                            strIMSIToClear.size()));
                event.data[0] = 0xde;
                event.data[1] = 0xad;
                event.data[2] = 0xbe;
                event.data[3] = 0xef;
                memcpy(event.data + sizeof(ITS_UINT), strIMSIToClear.c_str(),
                        strIMSIToClear.size());
                TRANSPORT_PutEvent(ITS_DEFAULT_USER_SRC, &event);
                retVal = CMAPI_SUCCESS;
            }
            break;
        default:
            {
                DLOG_DEBUG("CMAPIIwfConfig::HandleTranslationDataConfigReqs: Invalid request for TranslationData config");
                retVal = CMAPI_INVALIDPARAMS;
            }
            break;
    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleTranslationDataConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::HandleFeaturesConfigReqs(IwfFeaturesConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleFeaturesConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;

    if(req->IsInitialized() && req->has_operreqid() && req->operreqid() == DUMP_SYSTEM_INFO)
    {
        DLOG_DEBUG("Request Received to Dump IWF System Info");
        ITS_EVENT event;
        ITS_EVENT_INIT(&event, ITS_DEFAULT_USER_SRC, sizeof(ITS_UINT));
        event.data[0] = 0xde;
        event.data[1] = 0xad;
        event.data[2] = 0xbe;
        event.data[3] = 0xed;
        TRANSPORT_PutEvent(ITS_DEFAULT_USER_SRC, &event);
        retVal = CMAPI_SUCCESS;
    }
    else if(!req->IsInitialized() || !req->has_operreqid() || req->iwffeatureinfo_size()<=0)
    {
        DLOG_ERROR("Error Invalid IWF Features request contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        switch(req->operreqid())
        {
            case SET_IWF_FEATURES:
            case MOD_IWF_FEATURES:
                {
                    DLOG_DEBUG("Received IWF Features configuration");
                    for( int curFeature = 0 ; curFeature < req->iwffeatureinfo_size() ; curFeature++ )
                    {
                        IwfFeatureConfig featureConfig = req->iwffeatureinfo(curFeature);
                        if( featureConfig.has_featurename() && featureConfig.has_statusvalue() )
                        {
                            if( featureConfig.featurename() == CDR || featureConfig.featurename() == TANS_TRIGGER)
                            {
                                IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                                retVal = translator->SetFeaturesConfig(&featureConfig);
                            }
                            else if(featureConfig.featurename() == CONGESTION_MANAGEMENT)
                            {
                                if(featureConfig.has_statusvalue())
                                DLOG_DEBUG("Feature %s - status %d",CONGESTION_MANAGEMENT,featureConfig.statusvalue());
                                IwfController::Instance().Config().LocalConfig().SetCongestionManagementConfig(featureConfig.statusvalue());
                                DLOG_DEBUG("Success in setting the Congestion Management config");
                            }
                            else if(featureConfig.featurename() == MAX_NUMBER_OF_SESSIONS)
                            {
                                if(featureConfig.has_statusvalue())
                                DLOG_DEBUG("Feature %s - Max Number Of Sessions to Hold %ld",MAX_NUMBER_OF_SESSIONS,featureConfig.statusvalue());
                                IwfController::Instance().Config().LocalConfig().SetMaxNumberOfSessionsToHold(featureConfig.statusvalue());
                                DLOG_DEBUG("Success in setting the limit for Max IWF sessions to hold");
                            }
                        }
                        else
                        {
                            DLOG_ERROR("Invalid Feature configuration");
                            retVal = !ITS_SUCCESS;
                        }
                    }

                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in configuring Iwf Features ");
                        ErrorDetails* error = resp->add_errordetails();
                        error->set_errorcode(retVal);
                        //error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                        retVal = CMAPI_SRVERROR;
                    }
                }
                break;
            default:
                {
                    DLOG_ERROR("Iwf Feature operation : %d not supported",req->operreqid());
                    retVal = CMAPI_INVALIDPARAMS;
                    break;
                }


        }
    }
    resp->set_respid(retVal);
    return retVal;
}

int CMAPIIwfConfig::HandleTimersConfigReqs(IwfTimersConfig *req,IWFCfgResp *resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleTimersConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;
    if(!req->IsInitialized() || !req->has_operreqid() || req->iwftimersinfo_size() <=0)
    {
        DLOG_ERROR("Error Invalid IWF timer request contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        switch(req->operreqid())
        {
            case SET_CAP_PROTO_TIMERS:
            case MOD_CAP_PROTO_TIMERS:
                {
                    DLOG_DEBUG("Received CAP_PROTO timer configuration");
                    IwfTranslator* translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                    retVal = translator->SetTimerConfig(req);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in configuring CAP_PROTO timers");
                        ErrorDetails* error = resp->add_errordetails();
                        error->set_errorcode(retVal);
                        //error->set_errormsgkey(IwfMeSS::errorMap[errorCode]);
                        retVal = CMAPI_SRVERROR;
                    }
                }
                break;
            default:
                {
                    DLOG_ERROR("Timer operation : %d not supported",req->operreqid());
                    retVal = CMAPI_INVALIDPARAMS;
                    break;
                }
        }
    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleTimersConfigReqs Exit");
    return 0;
}

int CMAPIIwfConfig::SetComponentLoggingConf(LoggerConfReq* Req, LoggerConfResp* Resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(">CMAPIIwfConfig::SetComponentLoggingConf");

    int retVal = CMAPI_SUCCESS;
    if(!Req->IsInitialized() || !Req->has_requestid() || Req->loggerconfig_size() <= 0)
    {
        DLOG_DEBUG("Error Invalid Request Contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        int ReqID = Req->requestid();
        DLOG_DEBUG("SetcomponentLoggingConf: Request : %d", ReqID);
        switch(ReqID)
        {
            case SET_LOGGERCONFIG:
                {
                    int numComp = Req->loggerconfig_size();
                    if(numComp > 0)
                    {
                        for(int curComp = 0 ; curComp < numComp ; curComp++)
                        {
                            LoggerConf loggerConfig = Req->loggerconfig(curComp);
                            DLOG_DEBUG("SetComponentLogginConf::In SET_LOGGERCONFIG ");
                            if((loggerConfig.has_channel()) && (loggerConfig.has_level())
                                    && loggerConfig.has_componentname())
                            {
                                string compName = loggerConfig.componentname();
                                const unsigned int channel =(unsigned int)loggerConfig.channel();
                                const unsigned int level = (unsigned int)loggerConfig.level();
                                if((compName.compare("IWF")) == 0)
                                {
                                    if( IwfController::Instance().SetDiaStackLogLevel(level))
                                    {
                                        DLOG_DEBUG("Diameter Stack Logs are set successfully");
                                    }
                                    else
                                    {
                                        DLOG_DEBUG("Failed to Set Diameter Stack Logs level");
                                    }
                                    IwfController::Instance().SetLogConfig(channel, level);
                                    Resp->set_responseid(CMAPI_SUCCESS);
                                }
                                else
                                {
                                    Resp->set_responseid(CMAPI_ERROR);
                                    retVal = CMAPI_ERROR;
                                    DLOG_ERROR("Failed to Set Logger Config Invalid Component");
                                }
                            }
                            else
                            {
                                Resp->set_responseid(CMAPI_ERROR);
                                retVal = CMAPI_ERROR;
                                DLOG_ERROR("Invalid Logger configuration");
                            }
                        }
                    }
                    else
                    {
                        Resp->set_responseid(CMAPI_ERROR);
                        retVal = CMAPI_ERROR;
                        DLOG_ERROR("No Logger configuration");
                    }
                }
                break;
            case MOD_LOGGERCONFIG:
                {
                    int numComp = Req->loggerconfig_size();
                    if(numComp  > 0)
                    {
                        for(int curComp = 0 ; curComp < numComp ; curComp++)
                        {
                            LoggerConf loggerConfig = Req->loggerconfig(0);
                            DLOG_DEBUG("SetComponentLoggingConf::In MOD_LOGGERCONFIG");
                            if(loggerConfig.has_channel() && loggerConfig.LogChannel_IsValid(loggerConfig.channel())
                                    && loggerConfig.has_componentname())
                            {
                                string compName = loggerConfig.componentname();
                                const unsigned int channel = (unsigned int)loggerConfig.channel();

                                if((compName.compare("IWF")) == 0)
                                {
                                    IwfController::Instance().SetLogChannel(channel);
                                    Resp->set_responseid(CMAPI_SUCCESS);
                                    DLOG_DEBUG("Successfully set Log channel for DRE");
                                }
                                else
                                {
                                    Resp->set_responseid(CMAPI_ERROR);
                                    retVal = CMAPI_ERROR;
                                    DLOG_ERROR("Failed to set Log Channel, Invalid Component");
                                }
                            }
                            else if(loggerConfig.has_level() && loggerConfig.LogLevel_IsValid(loggerConfig.level())
                                    && loggerConfig.has_componentname())
                            {
                                string compName = loggerConfig.componentname();
                                const unsigned int level = (unsigned int)loggerConfig.level();

                                if((compName.compare("IWF")) == 0)
                                {
                                    IwfController::Instance().SetLogLevel(level);
                                    Resp->set_responseid(CMAPI_SUCCESS);
                                    DLOG_DEBUG("Successfully set the Log Level for DRE");
                                }
                                else
                                {
                                    /* Success reponse is sent to avoid failure
                                     * response for GUI as there will be
                                     * multiple request from GUI */
                                    retVal = CMAPI_SUCCESS;
                                    Resp->set_responseid(CMAPI_SUCCESS);
                                    DLOG_ERROR("Failed to set Logger Config Invalid Component ");

                                }
                            }
                            else
                            {
                                DLOG_DEBUG("Invalid Logger Config");
                                retVal = CMAPI_ERROR;
                                Resp->set_responseid(CMAPI_ERROR);
                            }
                        }
                    }
                    else
                    {

                        Resp->set_responseid(CMAPI_ERROR);
                        retVal = CMAPI_ERROR;
                        DLOG_ERROR("No Logger configuration");
                    }
                }
                break;
            default:
                {
                    DLOG_ERROR("Unsupported CMAPI Request received");
                    Resp->set_responseid(CMAPI_ERROR);
                    retVal = CMAPI_ERROR;
                }
                break;
        }
    }
    return retVal;
}

int CMAPIIwfConfig::HandleIwfProtocolActionsConfigReqs(IwfProtocolActionsConfig* req, IWFCfgResp* resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleIwfProtocolActionsConfigReqs Entry");

    int retVal = CMAPI_SUCCESS;
    if(!req->IsInitialized() || !req->has_operreqid() || req->iwfprotactioncfgval_size() <= 0)
    {
        DLOG_ERROR("Error Invalid IWF Protocol Actions config request contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        switch(req->operreqid())
        {
            case SET_IWF_PROT_ACTIONS:
                {
                    DLOG_DEBUG("Received IWF Protocol Actions Add configuration");
                    int prot_actions_count = req->iwfprotactioncfgval_size();
                    DLOG_DEBUG("ProtocolActionsReq Count = %d",prot_actions_count);
                    retVal = IwfController::Instance().Config().GetIwfProtActionCfg().SetProtActionConfig(req);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Adding Iwf Protocol Actions Configuration ");
                        ErrorDetails* error = resp->add_errordetails();
                        error->set_errorcode(retVal);
                        error->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                        retVal = CMAPI_SRVERROR;
                    }
                    break;
                }
            case MOD_IWF_PROT_ACTIONS:
                {
                    DLOG_DEBUG("Received IWF Protocol Actions Modify configuration");
                    int prot_actions_count = req->iwfprotactioncfgval_size();
                    DLOG_DEBUG("ProtocolActionsReq Count = %d",prot_actions_count);
                    retVal = IwfController::Instance().Config().GetIwfProtActionCfg().ModifyProtActionConfig(req);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Modifying Iwf Protocol Actions Configuration ");
                        ErrorDetails* error = resp->add_errordetails();
                        error->set_errorcode(retVal);
                        error->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                        retVal = CMAPI_SRVERROR;
                    }
                    break;
                }
            case DEL_IWF_PROT_ACTIONS:
            case DEL_IWF_CALL_SCENARIO:
            case DEL_IWF_EVENT_TYPE:
            case DEL_IWF_EVENT_TYPE_CONFIG:
                {
                    DLOG_DEBUG("Received IWF Protocol Actions Delete configuration");
                    int prot_actions_count = req->iwfprotactioncfgval_size();
                    DLOG_DEBUG("ProtocolActionsReq Count = %d",prot_actions_count);
                    retVal = IwfController::Instance().Config().GetIwfProtActionCfg().DeleteProtActionConfig(req);
                    if( retVal != CMAPI_SUCCESS )
                    {
                        DLOG_ERROR("Error in Deleting Iwf Protocol Actions Configuration ");
                        ErrorDetails* error = resp->add_errordetails();
                        error->set_errorcode(retVal);
                        error->set_errormsgkey(IwfMeSS::errorMap[retVal]);
                        retVal = CMAPI_SRVERROR;
                    }
                    break;
                }
            default:
                {
                    DLOG_ERROR("Iwf Protocol Actions Config operation : %d not supported",req->operreqid());
                    retVal = CMAPI_INVALIDPARAMS;
                    break;
                }
        }
    }
    resp->set_respid(retVal);
    DLOG_DEBUG("CMAPIIwfConfig::HandleIwfProtocolActionsConfigReqs Exit");
    return retVal;
}

int CMAPIIwfConfig::HandleIwfDccaGenConfigReqs(IwfDccaGenConfig* req, IWFCfgResp* resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleIwfDccaGenConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;

    if(!req->IsInitialized() || !req->has_operreqid() || req->iwfdccafeatures_size() <= 0)
    {
        DLOG_ERROR("Error Invalid IWF Dcca general config request contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        switch(req->operreqid())
        {
            case SET_IWF_DCCA_FEATURES :
            case MOD_IWF_DCCA_FEATURES :
                {
                    DLOG_DEBUG("Received IWF Dcca General configuration");
                    for( int currConfig = 0 ; currConfig < req->iwfdccafeatures_size(); currConfig++)
                    {
                        IwfDccaFeatureConfig dccaConfig = req->iwfdccafeatures(currConfig);
                        if (dccaConfig.dccafeaturename() == TX_TIMEOUT_STR)
                        {
                            DLOG_DEBUG("Received Dcca Tx timeout %d sec",dccaConfig.dccavalue());
                            IwfController::Instance().Config().DCCAConfig().SetTxTimeout(dccaConfig.dccavalue());

                        }
                        else if (dccaConfig.dccafeaturename() == INITIAL_ACTION_STR)
                        {
                            DLOG_DEBUG("Received Dcca Initial Action %d ",dccaConfig.dccavalue());
                            IwfController::Instance().Config().DCCAConfig().SetInitialCCFHAction((IwfCCFHAction)dccaConfig.dccavalue());
                        }
                        else if (dccaConfig.dccafeaturename() == UPDATE_ACTION_STR)
                        {
                            DLOG_DEBUG("Received Dcca Update Action %d ",dccaConfig.dccavalue());
                            IwfController::Instance().Config().DCCAConfig().SetUpdateCCFHAction((IwfCCFHAction)dccaConfig.dccavalue());
                        }
                        else
                        {
                            DLOG_ERROR("Invalid Dcca feature :%s value : %d",dccaConfig.dccafeaturename().c_str(), dccaConfig.dccavalue());
                        }
                    }
                }
                break;
            default:
                {
                    DLOG_ERROR("Iwf Dcca General Config operation : %d not supported",req->operreqid());
                    retVal = CMAPI_INVALIDPARAMS;
                    break;
                }
        }
    }
    resp->set_respid(retVal);
    return retVal;
}

int CMAPIIwfConfig::HandleIwfDccaDestConfigReqs(IwfDccaDestsConfig* req, IWFCfgResp* resp)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CMAPIIwfConfig::HandleIwfDccaDestConfigReqs Entry");
    int retVal = CMAPI_SUCCESS;

    if(!req->IsInitialized() || !req->has_operreqid() || req->iwfdccadestinfo_size() <= 0)
    {
        DLOG_ERROR("Error Invalid IWF Dcca Destination endpoints config request contents");
        retVal = CMAPI_ERROR;
    }
    else
    {
        switch(req->operreqid())
        {
            case SET_IWF_DCCA_DEST :
                {
                    DLOG_DEBUG("Received IWF Dcca Destination configuration");
                    for( int currConfig = 0 ; currConfig < req->iwfdccadestinfo_size(); currConfig++)
                    {
                        IwfDccaDestConfig dccaDest = req->iwfdccadestinfo(currConfig);
                        if( dccaDest.iwfdccaendpoints_size() > 0 && dccaDest.has_destname() && dccaDest.has_sendccrtindicator())
                        {
                            std::string dccaDestName = dccaDest.destname();
                            DLOG_DEBUG("Received Dcca Destination Name %s",dccaDest.destname().c_str());
                            if (IwfController::Instance().Config().DCCAConfig().
                                    GetDestinations().RemoveDestination(dccaDestName))
                            {
                                DLOG_DEBUG("Removed Dcca Destination Configuration Successfully");
                            }
                            for( int currDest = 0 ; currDest < dccaDest.iwfdccaendpoints_size() ; currDest++ )
                            {
                                IwfDccaEndPointConfig dccaEndpoint = dccaDest.iwfdccaendpoints(currDest);
                                DLOG_DEBUG("Dcca Endpoint name : %s priority : %d",dccaEndpoint.endpointname().c_str(),dccaEndpoint.priority());
                                bool sendCCRTFlg;
                                DLOG_DEBUG("SendCCRTFlag = %d",dccaDest.sendccrtindicator());
                                if(dccaDest.sendccrtindicator())
                                    sendCCRTFlg = true;
                                else
                                    sendCCRTFlg = false;
                                if ( IwfController::Instance().Config().DCCAConfig().
                                        GetDestinations().AddEndpoint(dccaDestName,dccaEndpoint.endpointname(),dccaEndpoint.priority(),sendCCRTFlg) )
                                {
                                    DLOG_DEBUG("Successfully added Dcca Destination Endpoint Configuration");
                                }
                                else
                                {
                                    DLOG_ERROR("Failed to add Dcca Destination Endpoint %s",dccaEndpoint.endpointname().c_str());
                                    ErrorDetails* err = resp->add_errordetails();
                                    err->set_errorcode(ADD_DCCA_DEST_ERR_ENDPOINT_ALREADY_PRESENT);
                                    err->set_errormsgkey(IwfMeSS::errorMap[ADD_DCCA_DEST_ERR_ENDPOINT_ALREADY_PRESENT]);
                                    err->add_variables(dccaDestName);
                                    err->add_variables(dccaEndpoint.endpointname());
                                    retVal = CMAPI_ERROR;
                                }
                            }
                        }
                        else
                        {
                            DLOG_ERROR("Invalid Dcca Destination configuration missing mandatory parameter");
                            ErrorDetails* err = resp->add_errordetails();
                            err->set_errorcode(ADD_DCCA_DEST_ERR_DATA_NOT_SET);
                            err->set_errormsgkey(IwfMeSS::errorMap[ADD_DCCA_DEST_ERR_DATA_NOT_SET]);
                            retVal = CMAPI_INVALIDPARAMS;
                        }
                    }
                    break;
                }
            case DEL_IWF_DCCA_ENDPOINT:
                {
                    DLOG_DEBUG("Delete IWF Dcca Destination endpoint configuration");
                    for( int currConfig = 0 ; currConfig < req->iwfdccadestinfo_size(); currConfig++)
                    {
                        IwfDccaDestConfig dccaDest = req->iwfdccadestinfo(currConfig);
                        if( dccaDest.iwfdccaendpoints_size() > 0 && dccaDest.has_destname() )
                        {
                            std::string dccaDestName = dccaDest.destname();
                            DLOG_DEBUG("Received Dcca Destination Name %s",dccaDest.destname().c_str());
                            for( int currDest = 0 ; currDest < dccaDest.iwfdccaendpoints_size() ; currDest++ )
                            {
                                IwfDccaEndPointConfig dccaEndpoint = dccaDest.iwfdccaendpoints(currDest);
                                if(dccaEndpoint.has_endpointname() && dccaEndpoint.has_priority())
                                {
                                    DLOG_DEBUG("Dcca Endpoint name : %s with priotity : %d",dccaEndpoint.endpointname().c_str(),dccaEndpoint.priority());
                                    if (IwfController::Instance().Config().DCCAConfig().
                                            GetDestinations().RemoveEndpoint(dccaDestName,dccaEndpoint.endpointname(),dccaEndpoint.priority()))
                                    {
                                        DLOG_DEBUG("Removed Dcca Endpoint configuration successfully");
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to remove Dcca Endpoint %s configuration",
                                                dccaEndpoint.endpointname().c_str());
                                        ErrorDetails* err = resp->add_errordetails();
                                        err->set_errorcode(DEL_DCCA_DEST_ERR_ENDPOINT_NOT_PRESENT);
                                        err->set_errormsgkey(IwfMeSS::errorMap[DEL_DCCA_DEST_ERR_ENDPOINT_NOT_PRESENT]);
                                        err->add_variables(dccaDestName);
                                        err->add_variables(dccaEndpoint.endpointname());
                                        retVal = CMAPI_ERROR;
                                    }
                                }
                            }
                        }
                        else
                        {
                            DLOG_ERROR("Invalid Dcca Destination configuration missing mandatory parameter");
                            retVal = CMAPI_INVALIDPARAMS;
                        }
                    }
                    break;
                }
            case DEL_IWF_DCCA_DEST :
                {
                    DLOG_DEBUG("Delete IWF Dcca Destination configuration");
                    for( int currConfig = 0 ; currConfig < req->iwfdccadestinfo_size(); currConfig++)
                    {
                        IwfDccaDestConfig dccaDest = req->iwfdccadestinfo(currConfig);
                        std::string dccaDestName = dccaDest.destname();
                        DLOG_DEBUG("Received Dcca Destination Name %s",dccaDestName.c_str());
                        if (IwfController::Instance().Config().DCCAConfig().
                                GetDestinations().RemoveDestination(dccaDestName))
                        {
                            DLOG_DEBUG("Removed Dcca Destination Configuration Successfully");
                        }
                        else
                        {
                            DLOG_ERROR("Failed to remove Dcca destination %s ",dccaDestName.c_str());
                        }
                    }
                    break;
                }
            default:
                {
                    DLOG_ERROR("Iwf Dcca Destination operation : %d not supported",req->operreqid());
                    retVal = CMAPI_INVALIDPARAMS;
                    break;
                }
        }
    }
    resp->set_respid(retVal);
    return retVal;
}


