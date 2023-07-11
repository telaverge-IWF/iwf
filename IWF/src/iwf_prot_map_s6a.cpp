/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2014 Diametriq LLC                                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 */
#include "iwf.h"
#include "iwf_prot_map_s6a.h"
#include "iwf_prot_utils.h"
#include "iwf_transaction_manager.h"

#include <dia_frame.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <ssg_trace.h>
#include <ssg_statistics.h>

/* MAP Error codes */
#include <map_c.h>

#include <sstream>

extern ITSDiaConfig itsDiaConfig;
static ITS_OCTET invkId = 0;

SsgStackStatistics mapStats;
/* holds whether Regional-Subscrition-Withdraw recieved in request */
bool isRegionalSubWithdraw = false;

    template <typename T>
void SetDefaultAVPs(IwfFsm *ctxt, T *cmd, const char* imsiStr = NULL)
{
    std::string sessId = ctxt->GetDiaSessionId();
    std::string origHost;
    if (sessId.empty())
    {
        /* allocate new session id */
        uint32_t sIdx = 0;
        int ret = DiaFrame::GetDiaFrame()->AllocateSessionIndex(
                0U, sIdx, sessId);
        if (ret != ITS_SUCCESS)
        {
            /* log an error and thrown an exception */
        }
        cmd->setSessionIndex(sIdx);
    }

    cmd->setSessionId(diameter::base::SessionId(sessId));
    ctxt->SetDiaSessionId(sessId);

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    if (itsDiaConfig.IsInterWorkingMode() && ctxt->GetDiameterIdentityFromCallingPartyAddr(origHost))
    {
        origHost.append(".");
        origHost.append(lcer->getOriginRealm().value());
        diameter::base::OriginHost originHost(origHost);
        cmd->setOriginHost(originHost);
    }
    else
    {
        cmd->setOriginHost(lcer->getOriginHost());
    }
    cmd->setOriginRealm(lcer->getOriginRealm());
}

    template <typename T>
void SetDefaultAVPsInAns(IwfFsm *ctxt, T *cmd)
{
    std::string origHost;
    std::string sessId = ctxt->GetDiaSessionId();
    if (sessId.empty())
    {
        /* allocate new session id */
        uint32_t sIdx = 0;
        int ret = DiaFrame::GetDiaFrame()->AllocateSessionIndex(
                0U, sIdx, sessId);
        if (ret != ITS_SUCCESS)
        {
            /* log an error an thrown an exception */
        }
        cmd->setSessionIndex(sIdx);
    }

    cmd->setSessionId(diameter::base::SessionId(sessId));

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    if (itsDiaConfig.IsInterWorkingMode() && ctxt->IsDestHostSetFromRequest() &&
        ctxt->GetOriginHostFromRequest(origHost))
    {
        //origHost.append(".");
        //origHost.append(lcer->getOriginRealm().value());
        diameter::base::OriginHost originHost(origHost);
        cmd->setOriginHost(originHost);
    }
    else
    {
        cmd->setOriginHost(lcer->getOriginHost());
    }
    cmd->setOriginRealm(lcer->getOriginRealm());
}

    template<typename T>
int SetDestinationHostAndRealm(IwfFsm *ctxt, std::string simsi, T *cmd)
{

    /* Now fetch SessionCtxt using IMSI for Destination Host&Realm */
    SessionCtxt *sctxt= ctxt->GetTransactionManager()->GetSessionCtxt(simsi);
    if(sctxt != NULL)
    {
        DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Found for: %s Routing to DestinationHost: %s and DestinationRealm: %s",
                simsi.c_str(),sctxt->GetOriginHost().c_str(),sctxt->GetOriginRealm().c_str());

        if(TransactionManager::Instance()->CheckPeerStateForRouting(sctxt->GetOriginHost(), sctxt->GetOriginRealm()))
        {
            DLOG_DEBUG("SetDestinationHostAndRealm: DestRealm %s and DestHost %s are set in out message.",
                    sctxt->GetOriginHost().c_str(), sctxt->GetOriginRealm().c_str());
            diameter::base::DestinationRealm dr(sctxt->GetOriginRealm());
            diameter::base::DestinationHost ds(sctxt->GetOriginHost());
            cmd->setDestinationHost(ds);
            cmd->setDestinationRealm(dr);
            return ITS_SUCCESS;
        }
    }

    //NOTE: Take Destination details from TranslatorRule
    //1) If SessionContext is not found or
    //2) DestinationHost taken from SessionContext is not up
    std::string mcc = "", mnc = "";
    std::string appId = DIAMETER_S6A_APPLICATION_ID;
    IWFUtils::ExtractMncMcc(simsi, mcc, mnc);
    std::string RuleName("");
    int32_t serviceKey = WILDCARD_SERVICE_KEY;
    int32_t ossn = SGSN_SSN;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(simsi,serviceKey,RuleName,ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return !ITS_SUCCESS;
    }
    std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName)->destRealm();
    std::string desthost = IwfController::Instance().Config().RoutingRules().Route(RuleName)->destHost();

    if(!destrealm.empty() && desthost.empty())
    {
        DLOG_DEBUG("SetDestinationHostAndRealm: Routing to Realm: %s Based on MCC: %s MNC: %s & AppId: %s Configured in Rules",
                destrealm.c_str(), mcc.c_str(), mnc.c_str() , appId.c_str());
        diameter::base::DestinationRealm dr(destrealm);
        cmd->setDestinationRealm(dr);
    }
    else if(!destrealm.empty() && !desthost.empty())
    {
        if(TransactionManager::Instance()->CheckPeerStateForRouting(desthost, destrealm))
        {
            DLOG_DEBUG("SetDestinationHostAndRealm: DestRealm %s and DestHost %s are set in out message.", destrealm.c_str(), desthost.c_str());
            diameter::base::DestinationRealm dr(destrealm);
            diameter::base::DestinationHost ds(desthost);
            cmd->setDestinationHost(ds);
            cmd->setDestinationRealm(dr);
            return ITS_SUCCESS;
        }

        std::string altdesthost = IwfController::Instance().Config().RoutingRules().Route(RuleName)->altHost();
        std::string altdestrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName)->altRealm();

        if(!altdestrealm.empty() && !altdesthost.empty())
        {
            if(TransactionManager::Instance()->CheckPeerStateForRouting(altdesthost, altdestrealm))
            {
                DLOG_DEBUG("SetDestinationHostAndRealm: AltDestRealm %s and AltDestHost %s are set in out message.", altdestrealm.c_str(), altdesthost.c_str());
                diameter::base::DestinationRealm dr(altdestrealm);
                diameter::base::DestinationHost ds(altdesthost);
                cmd->setDestinationHost(ds);
                cmd->setDestinationRealm(dr);
                return ITS_SUCCESS;
            }
        }
        DLOG_ERROR("SetDestinationHostAndRealm: Both the destination hosts are down, failed to set destination configurations.");
        return !ITS_SUCCESS;
    }
    else
    {
        DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Not Found for:%s, hence doing Realm Based Routing ..", simsi.c_str());
        diameter::base::DestinationRealm dr(itsDiaConfig.getLocalRealmName());
        cmd->setDestinationRealm(dr);
    }

    return ITS_SUCCESS;
}

inline void LogS6aDiaMsg(diameter::Command& cmd, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "MAP-S6aHandler RECEIVED S6a message\n";
    }
    else
    {
        str << "MAP-S6aHandler SENDING S6a message\n";
    }

    str << cmd << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

inline void LogMAPAsnObj(AsnObject& asn, bool incoming = true)
{
    stringstream str;
    if (incoming)
    {
        str << "MAP-S6aHandler RECEIVED MAP message\n";
    }
    else
    {
        str << "MAP-S6aHandler SENDING MAP message\n";
    }

    str << asn << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

void MAPS6aConfig::Parse(Json::Value& val, IwfConfig& conf)
{
#if 0
    Json::Value entry = val["hlr-number"];
    if(entry.empty())
    {
        throw IwfConfigException("'hlr-number' not part "
                "of '/proto-translator/CAP-Ro/'");
    }
    m_hlrNumber = entry.asString();
#endif
}

    MAPToS6aHandler::MAPToS6aHandler()
: IwfTranslator(MAP_TO_S6A_STR)
{
}

MAPToS6aHandler::~MAPToS6aHandler()
{
}

void MAPToS6aHandler::BuildTCAPErrorCpt(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TCAP_Component *&cpt)
{
    DLOG_DEBUG("MAPToS6aHandler::BuildTCAPErrorCpt Entry");
    Octets *enc2 = 0;
    ITS_OCTET  mapErr = 0;

    try
    {

        if (cmd != 0)
        {
            TCAP_Error *terr = new TCAP_Error();
            terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
            diameter::base::BaseGenericCommand *bgc = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();
            int erc = bgc->countExperimentalResult();

            /* get proper Error Code */
            int eridx = 0;
            if(erc)
            {
                while (eridx < erc)
                {
                    const diameter::base::ExperimentalResult *er = bgc->getExperimentalResult(eridx++);
                    /* Interested only in 3GPP vendor defined errors. */
                    if (er->getVendorId().value() == DIAMETER_3GPP_VENDOR_ID)
                    {
                        /* Check possible error codes
                         * Find the right values for the map */

                        switch(er->getExperimentalResultCode().value())
                        {
                            case DIAMETER_ERROR_USER_UNKNOWN:
                                {
                                    map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                                    map_v13::UnknownSubscriberDiagnostic unknsubdia(map_v13::UnknownSubscriberDiagnostic
                                            ::UNKNOWN_SUBSCRIBER_DIAGNOSTIC_IMSI_UNKNOWN);
                                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                                    EncodeMsg(unkwnSubs, &enc2);
                                    terr->SetParameter(enc2->GetArray());
                                    mapErr = MAP_ERR_UNKNOWN_SUBSCRIBER;

                                    delete unkwnSubs;
                                    unkwnSubs = NULL;
                                    if(enc2 != NULL)
                                    {
                                        delete enc2;
                                        enc2 = 0;
                                    }
                                    break;
                                }
                            case DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION:
                                {
                                    map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                                    map_v13::UnknownSubscriberDiagnostic unknsubdia(map_v13::UnknownSubscriberDiagnostic
                                            ::UNKNOWN_SUBSCRIBER_DIAGNOSTIC_GPRS_EPS_SUBSCRIPTION_UNKNOWN);
                                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                                    EncodeMsg(unkwnSubs, &enc2);
                                    terr->SetParameter(enc2->GetArray());
                                    mapErr = MAP_ERR_UNKNOWN_SUBSCRIBER;

                                    delete unkwnSubs;
                                    unkwnSubs = NULL;
                                    if(enc2 != NULL)
                                    {
                                        delete enc2;
                                        enc2 = 0;
                                    }
                                    break;
                                }
                            case DIAMETER_ERROR_RAT_NOT_ALLOWED:
                                {
                                    map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                                    map_v13::RoamingNotAllowedCause rnac(map_v13::RoamingNotAllowedCause::
                                            ROAMING_NOT_ALLOWED_CAUSE_OPERATOR_DETERMINED_BARRING);
                                    map_v13::AdditionalRoamingNotAllowedCause arnac(map_v13::
                                            AdditionalRoamingNotAllowedCause::ADDITIONAL_ROAMING_NOT_ALLOWED_CAUSE_SUPPORTED_RAT_TYPES_NOT_ALLOWED);
                                    roamNot->SetRoamingNotAllowedCause(rnac);
                                    roamNot->SetAdditionalRoamingNotAllowedCause(arnac);
                                    EncodeMsg(roamNot, &enc2);
                                    terr->SetParameter(enc2->GetArray());
                                    mapErr = MAP_ERR_ROAMING_NOT_ALLOWED;

                                    delete roamNot;
                                    roamNot = NULL;
                                    if(enc2 != NULL)
                                    {
                                        delete enc2;
                                        enc2 = 0;
                                    }
                                    break;
                                }
                            case DIAMETER_ERROR_ROAMING_NOT_ALLOWED:
                                {
                                    map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                                    map_v13::RoamingNotAllowedCause rnac(map_v13::RoamingNotAllowedCause::
                                            ROAMING_NOT_ALLOWED_CAUSE_PLMN_ROAMING_NOT_ALLOWED);
                                    roamNot->SetRoamingNotAllowedCause(rnac);
                                    EncodeMsg(roamNot, &enc2);
                                    terr->SetParameter(enc2->GetArray());
                                    mapErr = MAP_ERR_ROAMING_NOT_ALLOWED;

                                    delete roamNot;
                                    roamNot = NULL;
                                    if(enc2 != NULL)
                                    {
                                        delete enc2;
                                        enc2 = 0;
                                    }
                                    break;
                                }
                            default:
                                {
                                    mapErr = MAP_ERR_UNEXPECTED_DATA_VALUE;
                                    break;
                                }
                        }
                        break;
                    }
                }
            }
            else if(!bgc->countResultCode())
            {
                map_v13::DataMissingParam *dataMissing = new map_v13::DataMissingParam();
                EncodeMsg(dataMissing, &enc2);
                terr->SetParameter(enc2->GetArray());
                mapErr = MAP_ERR_DATA_MISSING;

                delete dataMissing;
                dataMissing = NULL;
                if(enc2 != NULL)
                {
                    delete enc2;
                    enc2 = 0;
                }
            }

            terr->SetError(mapErr);
            cpt = terr;
        }
        else
        {
            BuildTcapError(ctxt, cpt);
        }
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
    }
    catch(...)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("Unknown exception thrown");
    }
    UPDATE_SSG_STATS_NUM_OF_TCCOMP_ERR_SENT;
    DLOG_DEBUG("MAPToS6aHandler::BuildTCAPErrorCpt Exit");
}

void MAPToS6aHandler::BuildTcapError(IwfFsm *ctxt, TCAP_Component *&cpt)
{
    DLOG_DEBUG("MAPToS6aHandler::BuildTCAPError Entry ");
    Octets *enc2 = 0;
    ITS_OCTET  Err = 0;
    TCAP_Error *terr = new TCAP_Error();
    terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
    try
    {
        switch(ctxt->GetErrorCode())
        {
            case MAP_ERR_UNKNOWN_SUBSCRIBER:
                {
                    map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                    map_v13::UnknownSubscriberDiagnostic unknsubdia(map_v13::UnknownSubscriberDiagnostic
                            ::UNKNOWN_SUBSCRIBER_DIAGNOSTIC_IMSI_UNKNOWN);
                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                    EncodeMsg(unkwnSubs, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_UNKNOWN_SUBSCRIBER;

                    delete unkwnSubs;
                    unkwnSubs = NULL;
                    if(enc2 != NULL)
                    {
                        delete enc2;
                        enc2 = 0;
                    }
                    ctxt->SetErrorCode(0);
                    break;
                }

            case MAP_ERR_ROAMING_NOT_ALLOWED:
                {
                    map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                    map_v13::RoamingNotAllowedCause rnac(map_v13::RoamingNotAllowedCause::
                            ROAMING_NOT_ALLOWED_CAUSE_PLMN_ROAMING_NOT_ALLOWED);
                    roamNot->SetRoamingNotAllowedCause(rnac);
                    EncodeMsg(roamNot, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_ROAMING_NOT_ALLOWED;

                    delete roamNot;
                    roamNot = NULL;
                    if(enc2 != NULL)
                    {
                        delete enc2;
                        enc2 = 0;
                    }
                    break;
                }
            case IWF_EBASE_MAND_AVP_MISSING:
            case ITS_DIA_MISSING_AVP:
                {
                    map_v13::DataMissingParam *dataMissing = new map_v13::DataMissingParam();
                    EncodeMsg(dataMissing, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_DATA_MISSING;

                    delete dataMissing;
                    dataMissing = NULL;
                    if(enc2 != NULL)
                    {
                        delete enc2;
                        enc2 = 0;
                    }
                    break;
                }
            default:
                {
                    Err = MAP_ERR_UNEXPECTED_DATA_VALUE;
                    DLOG_ERROR("No Specific Error Set, Returning Unexpected Data Value..!!");
                }
        }

        terr->SetError(Err);
        // TODO: More granualr error can be set but usually that is not much looked into.
        cpt = terr;
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
    }
    catch(...)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("Unknown exception thrown");
    }


    DLOG_DEBUG("MAPToS6aHandler::BuildTCAPError Exit");
}

int MAPToS6aHandler::BuildTCAPMsg(IwfFsm *ctxt, DIA_BASE_CMD *bcmd, TcapCptList *out,
        DIA_BASE_CMD *&outCmd, IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    TCAP_Component *cpt  = NULL;

    ret.dir = IWF_RD_TCAP;

    try
    {
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
        /* the diameter message is s6a, assuming that the MAP function is called */
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (cmd->isRequest())
        {
            /* Request message */
            switch(code)
            {
                case DIA_CMD_ID:
                    {
                        s6a::InsertSubscriberDataRequest isdr(cmd->getImpl());
                        ctxt->SaveDestHostFromRequest(isdr.getDestinationHost().value());

                        if((isdr.getSubscriptionData().containsTraceData()))
                        {
                            ActivateTraceModeArg atmarg;

                            LogS6aDiaMsg(isdr);
                            DLOG_DEBUG("[S6a:InsertSubscriberDataRequest] -> [MAP:ActivateTraceModeArg]");

                            IDR_To_ActivateTraceModeArg(ctxt, &isdr, &atmarg);

                            Octets* buf = atmarg.Encode();

                            TCAP_Invoke *ivk = new TCAP_Invoke();
                            ivk->SetClass(TCAP_OPERATION_CLASS);
                            ivk->SetOperation(map_common::OP_activateTraceMode);
                            ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                            ivk->SetParameter(buf->GetArray());
                            cpt = ivk;
                            cpt->SetInvokeID(++invkId);
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(ivk != NULL)
                            {
                                delete ivk;
                                ivk = NULL;
                                cpt = NULL;
                            }
                            UPDATE_SSG_STATS_ATM_ARG_SENT;
                            ctxt->SetLastSentTcapCptOpcode(map_common::OP_activateTraceMode);
                            LogMAPAsnObj(atmarg, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::tracingContext_v3;
                            break;
                        }

                        if(isdr.containsIDRFlags())
                        {
                            const uint32_t idrFlags = isdr.getIDRFlags().value();
                            DLOG_DEBUG("InsertSubscriberDataRequest IDRFlag = %d\n",idrFlags);
                            if((idrFlags & IDR_FLAG_UE_REACH_REQ) || (idrFlags == 0))
                            {
                                InsertSubscriberDataArg isdarg;

                                LogS6aDiaMsg(isdr);
                                DLOG_DEBUG("[S6a:InsertSubscriberDataRequest] -> [MAP:InsertSubscriberDataArg]");

                                IDR_To_InsertSubscriberDataArg(ctxt, &isdr, &isdarg);

                                if(TransactionManager::Instance()->IsDestinationAvailable(ctxt) == false)
                                {
                                    rc = !ITS_SUCCESS;
                                }
                                else
                                {
                                    Octets* buf = isdarg.Encode();

                                    TCAP_Invoke *ivk = new TCAP_Invoke();
                                    ivk->SetClass(TCAP_OPERATION_CLASS);
                                    ivk->SetOperation(map_common::OP_insertSubscriberData);
                                    ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                                    ivk->SetParameter(buf->GetArray());
                                    cpt = ivk;
                                    cpt->SetInvokeID(++invkId);
                                    out->BuildTcapCptList(*cpt);
                                    if(buf != NULL)
                                    {
                                        delete buf;
                                        buf = NULL;
                                    }
                                    if(ivk != NULL)
                                    {
                                        delete ivk;
                                        ivk = NULL;
                                        cpt = NULL;
                                    }
                                    LogMAPAsnObj(isdarg, false);
                                    UPDATE_SSG_STATS_ISD_ARG_SENT;
                                    ctxt->SetLastSentTcapCptOpcode(map_common::OP_insertSubscriberData);

                                    ret.action = IWF_RA_FORWARD;
                                    ret.appContext = map_common::subscriberDataMngtContext_v3;
                                }
                                break;
                            }

                            if((idrFlags & IDR_FLAG_TADS_DATA_REQ) ||
                                    (idrFlags & IDR_FLAG_EPS_USER_STATE_REQ) ||
                                    (idrFlags & IDR_FLAG_EPS_LOC_INFO_REQ) ||
                                    (idrFlags & IDR_FLAG_CUR_LOC_REQ))
                            {
                                ProvideSubscriberInfoArg psia;

                                LogS6aDiaMsg(isdr);
                                DLOG_DEBUG("[S6a:InsertSubscriberDataRequest] -> [MAP:ProvideSubscriberInfoArg]");

                                IDR_To_ProvideSubscriberInfoArg(ctxt, &isdr, &psia);

                                if(TransactionManager::Instance()->IsDestinationAvailable(ctxt) == false)
                                {
                                    rc = !ITS_SUCCESS;
                                }
                                else
                                {
                                    Octets* buf = psia.Encode();

                                    TCAP_Invoke *ivk = new TCAP_Invoke();
                                    ivk->SetClass(TCAP_OPERATION_CLASS);
                                    ivk->SetOperation(map_common::OP_provideSubscriberInfo);
                                    ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                                    ivk->SetParameter(buf->GetArray());
                                    cpt = ivk;
                                    cpt->SetInvokeID(++invkId);
                                    out->BuildTcapCptList(*cpt);
                                    if(buf != NULL)
                                    {
                                        delete buf;
                                        buf = NULL;
                                    }
                                    if(ivk != NULL)
                                    {
                                        delete ivk;
                                        ivk = NULL;
                                        cpt = NULL;
                                    }
                                    UPDATE_SSG_STATS_PSD_ARG_SENT;
                                    ctxt->SetLastSentTcapCptOpcode(map_common::OP_provideSubscriberInfo);
                                    LogMAPAsnObj(psia, false);

                                    ret.action = IWF_RA_FORWARD;
                                    ret.appContext = map_common::subscriberInfoEnquiryContext_v3;
                                }
                            }
                            else
                            {
                                rc = !ITS_SUCCESS;
                            }
                        }
                        else
                        {
                            //TODO: Return Error in this case
                        }
                        break;
                    }

                case DIA_CMD_DS:
                    {
                        s6a::DeleteSubscriberDataRequest dsdr(cmd->getImpl());
                        ctxt->SaveDestHostFromRequest(dsdr.getDestinationHost().value());

                        const uint32_t dsrFlags = dsdr.getDSRFlags().value();

                        DLOG_DEBUG("DeleteSubscriberDataRequest DSRFlag = %d\n",dsrFlags);
                        if( dsrFlags &  DSR_FLAG_TRACE_DATA_WITHDRAW )
                        {
                            DeactivateTraceModeArg dtma;

                            LogS6aDiaMsg(dsdr);

                            DLOG_DEBUG("[S6a:DeleteSubscriberDataRequest] -> [MAP:DeactivateTraceModeArg]");
                            DSR_To_DeactivateTraceModeArg(ctxt, &dsdr, &dtma);

                            if(TransactionManager::Instance()->IsDestinationAvailable(ctxt) == false)
                            {
                                rc = !ITS_SUCCESS;
                            }
                            else
                            {
                                Octets* buf = dtma.Encode();

                                TCAP_Invoke *ivk = new TCAP_Invoke();
                                ivk->SetClass(TCAP_OPERATION_CLASS);
                                ivk->SetOperation(map_common::OP_deactivateTraceMode);
                                ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                                ivk->SetParameter(buf->GetArray());
                                cpt = ivk;
                                cpt->SetInvokeID(++invkId);
                                out->BuildTcapCptList(*cpt);
                                if(buf != NULL)
                                {
                                    delete buf;
                                    buf = NULL;
                                }
                                if(ivk != NULL)
                                {
                                    delete ivk;
                                    ivk = NULL;
                                    cpt = NULL;
                                }
                                UPDATE_SSG_STATS_DATM_ARG_SENT;
                                ctxt->SetLastSentTcapCptOpcode(map_common::OP_deactivateTraceMode);

                                LogMAPAsnObj(dtma, false);

                                ret.action = IWF_RA_FORWARD;
                                ret.appContext = map_common::tracingContext_v3;
                            }
                        }
                        else
                        {
                            DeleteSubscriberDataArg dsda;

                            LogS6aDiaMsg(dsdr);
                            DLOG_DEBUG("[S6a:DeleteSubscriberDataRequest] -> [MAP:DeleteSubscriberDataArg]");

                            DSR_To_DeleteSubscriberDataArg(ctxt, &dsdr, &dsda);

                            if(TransactionManager::Instance()->IsDestinationAvailable(ctxt) == false)
                            {
                                rc = !ITS_SUCCESS;
                            }
                            else
                            {
                                Octets* buf = dsda.Encode();

                                TCAP_Invoke *ivk = new TCAP_Invoke();
                                ivk->SetClass(TCAP_OPERATION_CLASS);
                                ivk->SetOperation(map_common::OP_deleteSubscriberData);
                                ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                                ivk->SetParameter(buf->GetArray());
                                cpt = ivk;
                                cpt->SetInvokeID(++invkId);
                                out->BuildTcapCptList(*cpt);
                                if(buf != NULL)
                                {
                                    delete buf;
                                    buf = NULL;
                                }
                                if(ivk != NULL)
                                {
                                    delete ivk;
                                    ivk = NULL;
                                    cpt = NULL;
                                }
                                LogMAPAsnObj(dsda, false);
                                UPDATE_SSG_STATS_DSD_ARG_SENT;
                                ctxt->SetLastSentTcapCptOpcode(map_common::OP_deleteSubscriberData);

                                ret.action = IWF_RA_FORWARD;
                                ret.appContext = map_common::subscriberDataMngtContext_v3;
                            }
                        }
                        break;
                    }

                case DIA_CMD_CL:
                    {
                        s6a::CancelLocationRequest clr(cmd->getImpl());
                        ctxt->SaveDestHostFromRequest(clr.getDestinationHost().value());
                        CancelLocationArg cla;

                        LogS6aDiaMsg(clr);
                        DLOG_DEBUG("[S6a:CancelLocationRequest] -> [MAP:CancelLocationArg]");

                        CLR_To_CancelLocationArg(ctxt, &clr, &cla);
                        if(TransactionManager::Instance()->IsDestinationAvailable(ctxt) == false)
                        {
                            rc = !ITS_SUCCESS;
                        }
                        else
                        {
                            Octets* buf = cla.Encode();

                            TCAP_Invoke *ivk = new TCAP_Invoke();
                            ivk->SetClass(TCAP_OPERATION_CLASS);
                            ivk->SetOperation(map_common::OP_cancelLocation);
                            ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                            ivk->SetParameter(buf->GetArray());
                            cpt = ivk;
                            cpt->SetInvokeID(++invkId);
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(ivk != NULL)
                            {
                                delete ivk;
                                ivk = NULL;
                                cpt = NULL;
                            }
                            LogMAPAsnObj(cla, false);
                            UPDATE_SSG_STATS_CLR_ARG_SENT;

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::locationCancellationContext_v3;
                        }
                        break;
                    }
                case DIA_CMD_RS:
                    {
                        s6a::ResetRequest rsr(cmd->getImpl());
                        ctxt->SaveDestHostFromRequest(rsr.getDestinationHost().value());
                        ResetArg rsarg;

                        LogS6aDiaMsg(rsr);
                        DLOG_DEBUG("[S6a:ResetRequest] -> [MAP:ResetArg]");

                        ResetReq_To_ResetArg(ctxt, &rsr, &rsarg);

                        Octets* buf = rsarg.Encode();

                        TCAP_Invoke *ivk = new TCAP_Invoke();
                        ivk->SetClass(TCAP_OPERATION_CLASS);
                        ivk->SetOperation(map_common::OP_reset);
                        ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                        ivk->SetParameter(buf->GetArray());
                        cpt = ivk;
                        cpt->SetInvokeID(++invkId);
                        out->BuildTcapCptList(*cpt);

                        LogMAPAsnObj(rsarg, false);
                        if(buf != NULL)
                        {
                            delete buf;
                            buf = NULL;
                        }
                        if(ivk != NULL)
                        {
                            delete ivk;
                            ivk = NULL;
                            cpt = NULL;
                        }
                        UPDATE_SSG_STATS_RESET_ARG_SENT;

                        ret.action = IWF_RA_RESPOND_AND_FORWARD;
                        ret.appContext = map_common::resetContext_v2;
                        break;
                    }

                default:
                    {
                        DLOG_ERROR("S6aToMAPHandler::Unhandled diameter request %d", code);
                        ret.action = IWF_RA_ERROR;
                        ret.dir = IWF_RD_DIA;
                    }
            }
        }
        else
        {
            /* Response or error */
            switch(code)
            {
                case DIA_CMD_AI:
                    {
                        s6a::AuthenticationInformationAnswer aia(cmd->getImpl());
                        LogS6aDiaMsg(aia);

                        if(!aia.containsResultCode() || aia.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }

                        SendAuthenticationInfoRes saiRes;
                        DLOG_DEBUG("[s6a:AuthenticationInformationAnswer] -> [MAP:SendAuthenticationInfoRes]");
                        AIA_To_SendAuthenticationInfoRes(ctxt, &aia, &saiRes);
                        Octets* buf = saiRes.Encode();

                        TCAP_Result *res = new TCAP_Result();
                        /*Note: Setting invokeId for the Tcap Response Built */
                        res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                        res->SetOperation(map_common::OP_sendAuthenticationInfo);
                        res->SetParameter(buf->GetArray());
                        cpt = res;
                        out->BuildTcapCptList(*cpt);
                        UPDATE_SSG_STATS_SAI_RES_SENT;
                        if(buf != NULL)
                        {
                            delete buf;
                            buf = NULL;
                        }
                        if(res != NULL)
                        {
                            delete res;
                            res = NULL;
                            cpt = NULL;
                        }
                        LogMAPAsnObj(saiRes, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::infoRetrievalContext_v3;
                        break;

                    }
                case DIA_CMD_PU:
                    {
                        s6a::PurgeUEAnswer pua(cmd->getImpl());
                        LogS6aDiaMsg(pua);

                        if (!pua.containsResultCode() ||
                                pua.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }

                        PurgeMS_Res pmRes;
                        DLOG_DEBUG("[s6a:PurgeUEAnswer] -> [MAP:PurgeMSRes]");
                        PUA_To_PurgeMSRes(ctxt, &pua, &pmRes);
                        Octets* buf = pmRes.Encode();

                        TCAP_Result *res = new TCAP_Result();
                        /*Note: Setting invokeId for the Tcap Response Built */
                        res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                        res->SetOperation(map_common::OP_purgeMS);
                        res->SetParameter(buf->GetArray());
                        cpt = res;
                        out->BuildTcapCptList(*cpt);
                        UPDATE_SSG_STATS_PURGE_RES_SENT;
                        if(buf != NULL)
                        {
                            delete buf;
                            buf = NULL;
                        }
                        if(res != NULL)
                        {
                            delete res;
                            res = NULL;
                            cpt = NULL;
                        }
                        LogMAPAsnObj(pmRes, false);
                        TransactionManager::Instance()->PurgeSessionCtxt(ctxt->GetImsi().c_str());
                        ctxt->PurgeSession(true);
                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::msPurgingContext_v3;
                        break;

                    }
                case DIA_CMD_UL:
                    {
                        s6a::UpdateLocationAnswer ula(cmd->getImpl());
                        LogS6aDiaMsg(ula);

                        if (!ula.containsResultCode() ||
                                ula.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }
                        UpdateGprsLocationRes uglr;
                        DLOG_DEBUG("[s6a:UpdateLocationAnswerAnswer] -> [MAP:UpdateGprsLocationRes]");
                        ULA_To_UpdateGprsLocationRes(ctxt, &ula, &uglr);
                        Octets* buf = uglr.Encode();

                        TCAP_Result *res = new TCAP_Result();
                        /*Note: Setting invokeId for the Tcap Response Built */
                        res->SetInvokeID(ctxt->GetInvokeId());
                        res->SetOperation(map_common::OP_updateGprsLocation);
                        res->SetParameter(buf->GetArray());
                        cpt = res;
                        out->BuildTcapCptList(*cpt);
                        UPDATE_SSG_STATS_UGL_RES_SENT;
                        if(buf != NULL)
                        {
                            delete buf;
                            buf = NULL;
                        }
                        if(res != NULL)
                        {
                            delete res;
                            res = NULL;
                            cpt = NULL;
                        }
                        LogMAPAsnObj(uglr, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::gprsLocationUpdateContext_v3;
                        break;
                    }
                case DIA_CMD_NO:
                    {
                        DLOG_DEBUG("Received [S6a::NotifyAnswer]. Nothing to do.");
                        cpt = NULL;
                        ret.action = IWF_RA_CONSUME;
                        ret.appContext = map_common::UNKNOWN;

                        break;
                    }
                default:
                    {
                        DLOG_ERROR("S6aToMAPHandler::Unhandled diameter answer %d", code);
                    }
            }
        }
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
    }
    catch (diameter::CodecExceptionToApp& e)
    {
        //fixing Big parameter passing by value
        DLOG_ERROR("Exception Caught: %s Error Cause: %s ",
                e.name() ,e.what());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
        ctxt->SetErrorCode(ITS_DIA_MISSING_AVP);
    }
    catch(...)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("Unknown exception thrown");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
    }

    if(cpt!= NULL)

    {
        delete cpt;
        cpt = NULL;
    }


    return rc;
}

int MAPToS6aHandler::BuildDiaMsg(IwfFsm *ctxt, TCAP_Component *cpt, DIA_BASE_CMD *&cmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = cpt->GetComponentType();
    cmd = NULL;

    ret.dir = IWF_RD_DIA;
    ret.appContext = map_common::UNKNOWN;
    ret.action = IWF_RA_FORWARD;

    try
    {
        switch(cptType)
        {
            case TCPPT_TC_INVOKE:
                {
                    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(cpt);
                    tcapIvk->GetOperation(opCode);
                    tcapIvk->GetParameter(buf);
                    /* For request messages initiated by the server */
                    switch (opCode)
                    {
                        case map_common::OP_sendAuthenticationInfo:
                            {
                                s6a::AuthenticationInformationRequest *air =
                                    new s6a::AuthenticationInformationRequest();
                                SendAuthenticationInfoArg sais;
                                Octets octs(buf);
                                sais.Decode(octs);

                                LogMAPAsnObj(sais);
                                DLOG_DEBUG("[MAP:SendAuthenticationInfoArg] - [s6a:AuthenticationInformationRequest]");

                                int result = SendAuthenticationInfoArg_To_AIR(ctxt, &sais, air);
                                if(result != ITS_SUCCESS)
                                {
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    if(air != NULL)
                                    {
                                        delete air;
                                        air = NULL;
                                    }
                                    break;
                                }
                                SetDefaultAVPs(ctxt, air, air->getUserName().value().c_str());
                                if(SetDestinationHostAndRealm(ctxt, air->getUserName().value(), air) != ITS_SUCCESS)
                                {
                                    DLOG_ERROR("Failed to set Destination configuration in out message");
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    if(air != NULL)
                                    {
                                        delete air;
                                        air = NULL;
                                    }
                                    break;
                                }
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)air);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);
                                UPDATE_SSG_STATS_SAI_ARG_RECVD;

                                LogS6aDiaMsg(*air, false);
                                break;

                            }
                        case map_common::OP_purgeMS:
                            {
                                s6a::PurgeUERequest *pur =
                                    new s6a::PurgeUERequest();
                                PurgeMS_Arg pmsa;
                                Octets octs(buf);
                                pmsa.Decode(octs);

                                LogMAPAsnObj(pmsa);
                                DLOG_DEBUG("[MAP:PurgeMSArg] - [s6a:PurgeUERequest]");

                                PurgeMSArg_To_PUR(ctxt, &pmsa, pur);
                                SetDefaultAVPs(ctxt, pur, pur->getUserName().value().c_str());

                                if(SetDestinationHostAndRealm(ctxt, pur->getUserName().value(), pur) != ITS_SUCCESS)
                                {
                                    DLOG_ERROR("Failed to set Destination configuration in out message");
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    if(pur != NULL)
                                    {
                                        delete pur;
                                        pur = NULL;
                                    }
                                    break;
                                }
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)pur);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);
                                UPDATE_SSG_STATS_PURGE_ARG_RECVD;

                                LogS6aDiaMsg(*pur, false);
                                break;

                            }
                        case map_common::OP_updateGprsLocation:
                            {
                                UpdateGprsLocationArg ugla;
                                Octets octs(buf);
                                ugla.Decode(octs);

                                LogMAPAsnObj(ugla);

                                UPDATE_SSG_STATS_UGL_ARG_RECVD;
                                /* UGL-ULR :
                                 *    a) without a pdn-gw-update parameter within eps-info &&
                                 *    b) without an isr-Information parameter within eps-info not indicating updateLocation ||
                                 *    c) without a skipSubscriberDataUpdate parameter within add-info */


                                if((ugla.OptionEps_info() && !(ugla.GetEps_info().ChoicePdn_gw_update()) &&
                                            ((ugla.GetEps_info().ChoiceIsr_Information()) &&
                                             !(ugla.GetEps_info().GetChoiceIsr_Information().IsUpdateMMESet()))) ||
                                        (ugla.OptionAdd_info() && !(ugla.GetAdd_info().OptionSkipSubscriberDataUpdate())))
                                {
                                    s6a::UpdateLocationRequest *ulr =
                                        new s6a::UpdateLocationRequest();
                                    DLOG_DEBUG("[MAP:UpdateGprsLocationArg] - [s6a:UpdateLocationRequest]");
                                    int result = UpdateGprsLocationArg_To_ULR(ctxt, &ugla, ulr);
                                    if(result != ITS_SUCCESS)
                                    {
                                        ret.action = IWF_RA_ERROR;
                                        ret.dir = IWF_RD_TCAP;
                                        rc = !ITS_SUCCESS;
                                        if(ulr != NULL)
                                        {
                                            delete ulr;
                                            ulr = NULL;
                                        }
                                        break;
                                    }
                                    /* For UGL to ULR case we always set it to IwfFsm
                                     * this is to make getting of invokeId generic for normal UGL
                                     * and intermediate ISD case*/
                                    ctxt->SetInvokeId(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                                    SetDefaultAVPs(ctxt, ulr, ulr->getUserName().value().c_str());
                                    if(SetDestinationHostAndRealm(ctxt, ulr->getUserName().value(), ulr) != ITS_SUCCESS)
                                    {
                                        DLOG_ERROR("Failed to set Destination configuration in out message");
                                        ret.action = IWF_RA_ERROR;
                                        ret.dir = IWF_RD_TCAP;
                                        rc = !ITS_SUCCESS;
                                        if(ulr != NULL)
                                        {
                                            delete ulr;
                                            ulr = NULL;
                                        }
                                        break;
                                    }
                                    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ulr);
                                    cmd->SetDictId(DIA_S6A_REL10_DICTID);
                                    LogS6aDiaMsg(*ulr, false);

                                    break;
                                }
                                /* UGL - NOR :
                                 *   a) With a pdn-gw-update parameter within eps-info ||
                                 *   b) With an isr-Information parameter within eps-info not indicating updateLocation ||
                                 *   c) With a skipSubscriberDataUpdate parameter within add-info  ||
                                 *   d) With ue-srvcc-Capability parameter but without usedRAT-Type parameter */

                                else if((ugla.OptionEps_info() && (ugla.GetEps_info().ChoiceIsr_Information()) &&
                                            !(ugla.GetEps_info().GetChoiceIsr_Information().IsUpdateMMESet())) ||
                                        (ugla.OptionEps_info() && (ugla.GetEps_info().ChoicePdn_gw_update())) ||
                                        (ugla.OptionAdd_info() && (ugla.GetAdd_info().OptionSkipSubscriberDataUpdate())) ||
                                        (ugla.OptionUe_srvcc_Capability() && !(ugla.OptionUsedRAT_Type())))
                                {
                                    s6a::NotifyRequest *nor =
                                        new s6a::NotifyRequest();
                                    DLOG_DEBUG("[MAP:UpdateGprsLocationArg] - [s6a:NotifyRequest]");
                                    UpdateGprsLocationArg_To_NOR(ctxt, &ugla, nor);
                                    SetDefaultAVPs(ctxt, nor, nor->getUserName().value().c_str());
                                    if(SetDestinationHostAndRealm(ctxt, nor->getUserName().value(), nor) != ITS_SUCCESS)
                                    {
                                        DLOG_ERROR("Failed to set Destination configuration in out message");
                                        ret.action = IWF_RA_ERROR;
                                        ret.dir = IWF_RD_TCAP;
                                        rc = !ITS_SUCCESS;
                                        if(nor != NULL)
                                        {
                                            delete nor;
                                            nor = NULL;
                                        }
                                        break;
                                    }
                                    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)nor);
                                    cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                    LogS6aDiaMsg(*nor, false);
                                    ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                }
                                else
                                {
                                    rc = !ITS_SUCCESS;
                                }

                                break;
                            }

                        case map_common::OP_readyForSM:
                            {
                                s6a::NotifyRequest *nor =
                                    new s6a::NotifyRequest();
                                ReadyForSM_Arg rfsarg;
                                Octets octs(buf);
                                rfsarg.Decode(octs);

                                LogMAPAsnObj(rfsarg);
                                DLOG_DEBUG("[MAP:ReadyForSM_Arg] - [s6a:NotifyRequest]");
                                UPDATE_SSG_STATS_READY_FOR_SM_ARG_RECVD;

                                ReadyForSMArg_To_NOR(ctxt, &rfsarg, nor);
                                SetDefaultAVPs(ctxt, nor, nor->getUserName().value().c_str());
                                if(SetDestinationHostAndRealm(ctxt, nor->getUserName().value(), nor) != ITS_SUCCESS)
                                {
                                    DLOG_ERROR("Failed to set Destination configuration in out message");
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    if(nor != NULL)
                                    {
                                        delete nor;
                                        nor = NULL;
                                    }
                                    break;
                                }
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)nor);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*nor, false);
                                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                break;
                            }
                        default:
                            {
                                DLOG_ERROR("Unexpected opCode %d on TC_Invoke", opCode);
                                rc = !ITS_SUCCESS;
                                break;
                            }
                    }
                    break;
                }
            case TCPPT_TC_RESULT_L:
                {
                    TCAP_Result *tcapRes = static_cast<TCAP_Result*>(cpt);
                    tcapRes->GetOperation(opCode);
                    tcapRes->GetParameter(buf);
                    switch(opCode)
                    {
                        case map_common::OP_insertSubscriberData:
                            {
                                InsertSubscriberDataRes isdr;
                                Octets octs(buf);
                                isdr.Decode(octs);

                                LogMAPAsnObj(isdr);

                                DLOG_DEBUG("[MAP:InsertSubscriberDataRes] -> "
                                        "[S6a:IDA]");
                                UPDATE_SSG_STATS_ISD_RES_RECVD;
                                s6a::InsertSubscriberDataAnswer* isda = new s6a::InsertSubscriberDataAnswer();
                                InsertSubscriberDataRes_To_IDA(ctxt, &isdr, isda);
                                SetDefaultAVPsInAns(ctxt, isda);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)isda);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*isda, false);

                                break;
                            }
                        case map_common::OP_provideSubscriberInfo:
                            {
                                ProvideSubscriberInfoRes psir;

                                Octets octs(buf);
                                psir.Decode(octs);

                                LogMAPAsnObj(psir);

                                DLOG_DEBUG("[MAP:ProvideSubscriberInfoRes] -> "
                                        "[S6a:IDA]");

                                UPDATE_SSG_STATS_PSD_RES_RECVD;
                                s6a::InsertSubscriberDataAnswer* isda = new s6a::InsertSubscriberDataAnswer();
                                ProvideSubscriberInfoRes_To_IDA(ctxt, &psir, isda);

                                SetDefaultAVPsInAns(ctxt, isda);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)isda);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*isda, false);

                                break;
                            }
                        case map_common::OP_deleteSubscriberData:
                            {
                                DeleteSubscriberDataRes dsdr;
                                Octets octs(buf);
                                dsdr.Decode(octs);

                                LogMAPAsnObj(dsdr);


                                DLOG_DEBUG("[MAP:DeleteSubscriberDataRes] -> "
                                        "[S6a:DeleteSubscriberDataAnswer]");

                                UPDATE_SSG_STATS_DSD_RES_RECVD;
                                s6a::DeleteSubscriberDataAnswer* dsda = new s6a::DeleteSubscriberDataAnswer();
                                DeleteSubscriberDataRes_To_DSA(ctxt, &dsdr, dsda);
                                SetDefaultAVPsInAns(ctxt, dsda);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsda);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*dsda, false);

                                break;
                            }

                        case map_common::OP_cancelLocation:
                            {
                                CancelLocationRes clr;
                                Octets octs(buf);
                                clr.Decode(octs);

                                LogMAPAsnObj(clr);


                                DLOG_DEBUG("[MAP:CancelLocationRes] -> "
                                        "[S6a:CancelLocationAnswer]");

                                UPDATE_SSG_STATS_CLR_RES_RECVD;
                                s6a::CancelLocationAnswer* cla = new s6a::CancelLocationAnswer();
                                CancelLocationRes_To_CLA(ctxt, &clr, cla);
                                SetDefaultAVPsInAns(ctxt, cla);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cla);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*cla, false);

                                break;
                            }
                        case map_common::OP_activateTraceMode:
                            {
                                ActivateTraceModeRes atmr;
                                Octets octs(buf);
                                atmr.Decode(octs);

                                LogMAPAsnObj(atmr);


                                DLOG_DEBUG("[MAP:ActivateTraceModeRes] -> "
                                        "[S6a:InsertSubscriberDataAnswer]");

                                UPDATE_SSG_STATS_ATM_RES_RECVD;
                                s6a::InsertSubscriberDataAnswer* isda = new s6a::InsertSubscriberDataAnswer();
                                ActivateTraceModeRes_To_IDA(ctxt, &atmr, isda);
                                SetDefaultAVPsInAns(ctxt, isda);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)isda);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*isda, false);

                                break;
                            }
                        case map_common::OP_deactivateTraceMode:
                            {
                                DeactivateTraceModeRes dtmr;
                                Octets octs(buf);
                                dtmr.Decode(octs);

                                LogMAPAsnObj(dtmr);


                                DLOG_DEBUG("[MAP:DeactivateTraceModeRes] -> "
                                        "[S6a:DeleteSubscriberDataAnswer]");

                                UPDATE_SSG_STATS_DATM_RES_RECVD;
                                s6a::DeleteSubscriberDataAnswer* dsda = new s6a::DeleteSubscriberDataAnswer();
                                DeactivateTraceModeRes_To_DSA(ctxt, &dtmr, dsda);
                                SetDefaultAVPsInAns(ctxt, dsda);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsda);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*dsda, false);

                                break;
                            }
                        default:
                            {
                                DLOG_ERROR("Unexpected opCode %d on TC_Result", opCode);
                                ret.action = IWF_RA_ERROR;
                                ret.dir = IWF_RD_TCAP;
                                break;
                            }
                    }

                    break;
                }
            case TCPPT_TC_U_ERROR:
                {

                    TCAP_Error *tcapError = static_cast<TCAP_Error*>(cpt);

                    DiaCommandCode code = GetLastDiaOperation(ctxt);
                    switch(code)
                    {
                        case DIA_CMD_CL:
                            {
                                s6a::CancelLocationAnswer* cla = new s6a::CancelLocationAnswer(true);
                                UPDATE_SSG_STATS_CLR_ERROR_RECVD;
                                BuildErrorResponse(tcapError, cla);
                                SetDefaultAVPsInAns(ctxt, cla);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cla);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*cla, false);
                                break;
                            }

                        case DIA_CMD_ID:
                            {
                                s6a::InsertSubscriberDataAnswer* ida = new s6a::InsertSubscriberDataAnswer(true);
                                if(ctxt->HasLastSentTcapCptOpcode())
                                {
                                    opCode = ctxt->GetLastSentTcapCptOpcode();
                                    switch(opCode)
                                    {
                                        case map_common::OP_activateTraceMode:
                                            UPDATE_SSG_STATS_ATM_ERROR_RECVD;
                                            break;

                                        case map_common::OP_provideSubscriberInfo:
                                            UPDATE_SSG_STATS_PSD_ERROR_RECVD;
                                            break;

                                        default:
                                            UPDATE_SSG_STATS_ISD_ERROR_RECVD;
                                            break;
                                    }
                                }
                                else
                                {
                                    UPDATE_SSG_STATS_ISD_ERROR_RECVD;
                                }
                                BuildErrorResponse(tcapError, ida);
                                SetDefaultAVPsInAns(ctxt, ida);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ida);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*ida, false);
                                break;
                            }

                        case DIA_CMD_DS:
                            {
                                s6a::DeleteSubscriberDataAnswer* dsa = new s6a::DeleteSubscriberDataAnswer(true);
                                if(ctxt->HasLastSentTcapCptOpcode())
                                {
                                    opCode = ctxt->GetLastSentTcapCptOpcode();
                                    if(opCode == map_common::OP_deactivateTraceMode)
                                    {
                                        UPDATE_SSG_STATS_DATM_ERROR_RECVD;
                                    }
                                    else
                                    {
                                        UPDATE_SSG_STATS_DSD_ERROR_RECVD;
                                    }
                                }
                                else
                                {
                                    UPDATE_SSG_STATS_DSD_ERROR_RECVD;
                                }
                                BuildErrorResponse(tcapError, dsa);
                                SetDefaultAVPsInAns(ctxt, dsa);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsa);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogS6aDiaMsg(*dsa, false);
                                break;
                            }

                        default:
                            {
                                DLOG_ERROR("Unknown OpCode received ..!!");
                                break;
                            }
                    }

                    break;
                }
            default:
                {
                    rc = !ITS_SUCCESS;
                    ret.action = IWF_RA_ERROR;
                    ret.dir = IWF_RD_TCAP;
                }
        }

    }
    catch(AsnDecodeError &exc)
    {
        DLOG_ERROR("### ASN Decode Error ### <%s>", exc.GetDescription().c_str());
        if(cmd != NULL)
        {
            delete cmd;
            cmd = NULL;
        }
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
        if(cmd != NULL)
        {
            delete cmd;
            cmd = NULL;
        }
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
        if(cmd != NULL)
        {
            delete cmd;
            cmd = NULL;
        }
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }

    return rc;
}

int MAPToS6aHandler::BuildInterimTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = in->GetComponentType();

    if (cptType != TCPPT_TC_INVOKE)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }


    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(in);
    tcapIvk->GetOperation(opCode);
    if (opCode != map_common::OP_updateGprsLocation)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }

    try
    {
        DIA_BASE_CMD *cmd = ctxt->GetCurrRcvdDiaMsg();
        const diameter::Command* bcmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();
        if((DiaCommandCode)bcmd->getCommandCode() == DIA_CMD_UL)
        {
            s6a::UpdateLocationAnswer ula(bcmd->getImpl());
            LogS6aDiaMsg(ula);
            if (!ula.containsResultCode() ||
                    ula.getResultCode().value() != ITS_DIA_SUCCESS)
            {
                BuildTCAPErrorCpt(ctxt, cmd, out);
                ret.action = IWF_RA_ERROR;
                ret.appContext = map_common::UNKNOWN;
                rc = !ITS_SUCCESS;
            }
            else
            {
                if((ula.getSubscriptionData().containsTraceData()))
                {
                    ActivateTraceModeArg atmarg;
                    DLOG_DEBUG("[S6a:UpdateLocationAnswer] -> [MAP:ActivateTraceModeArg]");

                    TraceData_To_ActivateTraceModeArg(ctxt, &ula, &atmarg);
                    Octets* buf = atmarg.Encode();

                    TCAP_Invoke *ivk = new TCAP_Invoke();
                    ivk->SetClass(TCAP_OPERATION_CLASS);
                    ivk->SetOperation(map_common::OP_activateTraceMode);
                    ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                    ivk->SetParameter(buf->GetArray());
                    out = ivk;
                    if(buf != NULL)
                    {
                        delete buf;
                        buf = NULL;
                    }
                    UPDATE_SSG_STATS_ATM_ARG_SENT;
                    LogMAPAsnObj(atmarg, false);

                    ret.action = IWF_RA_FORWARD;
                    ret.appContext = map_common::tracingContext_v3;
                }
                else
                {
                    InsertSubscriberDataArg isdarg;
                    DLOG_DEBUG("[s6a:UpdateLocationAnswer] -> [MAP:InsertSubscriberDataArg");

                    SubscriptionData_To_InsertSubscriberDataArg(ctxt, &ula, &isdarg);
                    Octets* buf = isdarg.Encode();

                    TCAP_Invoke *ivk = new TCAP_Invoke();
                    ivk->SetClass(TCAP_OPERATION_CLASS);
                    ivk->SetOperation(map_common::OP_insertSubscriberData);
                    ivk->SetTimeOut(IwfController::Instance().Config().LocalConfig().InvokeTimeout());
                    ivk->SetParameter(buf->GetArray());
                    out = ivk;
                    if(buf != NULL)
                    {
                        delete buf;
                        buf = NULL;
                    }

                    LogMAPAsnObj(isdarg, false);

                    ret.action = IWF_RA_FORWARD;
                    ret.appContext = map_common::subscriberDataMngtContext_v3;

                }
                ctxt->SetInvokeId(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
            }
        }
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;

        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
    }

    return rc;
}

int MAPToS6aHandler::BuildTcapResponse(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = in->GetComponentType();
    out = NULL;

    if (cptType != TCPPT_TC_INVOKE)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }


    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(in);
    tcapIvk->GetOperation(opCode);

    try
    {
        if(opCode == map_common::OP_updateGprsLocation)
        {
            UpdateGprsLocationRes uglr;
            DLOG_DEBUG("Constructing MAP UpdateGprsLocationRes");

            ConstructUpdateGprsLocationRes(ctxt, &uglr);
            Octets* buf = uglr.Encode();
            TCAP_Result *res = new TCAP_Result();
            //Note: Setting invokeId for the Tcap Response Built
            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
            res->SetOperation(map_common::OP_updateGprsLocation);
            res->SetParameter(buf->GetArray());
            out = res;
            if(buf != NULL)
            {
                delete buf;
                buf = NULL;
            }

            LogMAPAsnObj(uglr, false);
            UPDATE_SSG_STATS_UGL_RES_SENT;

            ret.action = IWF_RA_FORWARD;
            ret.appContext = map_common::gprsLocationUpdateContext_v3;
        }
        else if(opCode == map_common::OP_readyForSM)
        {
            ReadyForSM_Res rfrs;
            DLOG_DEBUG("Constructing MAP ReadyForSM_Res");

            Octets* buf = rfrs.Encode();
            TCAP_Result *res = new TCAP_Result();
            //Note: Setting invokeId for the Tcap Response Built
            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
            res->SetOperation(map_common::OP_readyForSM);
            if(buf != NULL)
            {
                res->SetParameter(buf->GetArray());
            }
            out = res;
            if(buf != NULL)
            {
                delete buf;
                buf = NULL;
            }

            LogMAPAsnObj(rfrs, false);
            UPDATE_SSG_STATS_READY_FOR_SM_RES_SENT;

            ret.action = IWF_RA_FORWARD;
            ret.appContext = map_common::mwdMngtContext_v3;
        }
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;

        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
    }

    return rc;
}

void MAPToS6aHandler::ConstructUpdateGprsLocationRes(IwfFsm *ctxt,
        UpdateGprsLocationRes *out)
{
    if (!ctxt || !out)
    {
        return;
    }
    uint8_t l_hlrnumber[10] = {0};
    std::string hlrNumber = m_config.HlrNumber();
    if(hlrNumber.length() > 20)
    {
        hlrNumber.erase(20, std::string::npos);
    }
    int len = IWFUtils::StringToTBCD(hlrNumber.substr(0, 2), l_hlrnumber, 2, 0, true);
    len += IWFUtils::StringToTBCD(hlrNumber.substr(2), (l_hlrnumber+1), 20);
    if (hlrNumber.length() % 2)
    {
        l_hlrnumber[(hlrNumber.length() / 2)] |= 0xF0;
    }

    map_v13::ISDN_AddressString isdn(IWFUtils::ByteArrayToVector(l_hlrnumber, len));
    out->SetHlr_Number(isdn);
}

int MAPToS6aHandler::BuildDiaErrorAnswer(IwfFsm *ctxt, int cmdCode, int error, DIA_BASE_CMD **out)
{
    int rc = ITS_SUCCESS;
    *out = NULL;

    switch(cmdCode)
    {
        case DIA_CMD_DS:
            {
                s6a::DeleteSubscriberDataAnswer* dsa = new s6a::DeleteSubscriberDataAnswer();
                ConstructErrorAnswer(error, dsa);
                SetDefaultAVPsInAns(ctxt, dsa);
                LogS6aDiaMsg(*dsa, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsa);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        case DIA_CMD_CL:
            {
                s6a::CancelLocationAnswer* cla = new s6a::CancelLocationAnswer();
                ConstructErrorAnswer(error, cla);
                SetDefaultAVPsInAns(ctxt, cla);
                LogS6aDiaMsg(*cla, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cla);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        case DIA_CMD_ID:
            {
                s6a::InsertSubscriberDataAnswer* ida = new s6a::InsertSubscriberDataAnswer();
                ConstructErrorAnswer(error, ida);
                SetDefaultAVPsInAns(ctxt, ida);
                LogS6aDiaMsg(*ida, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ida);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        default:
            {
                break;
            }
    }

    return rc;
}

int MAPToS6aHandler::BuildDiaErrorResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;
    const diameter::Command* bcmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();

    try
    {
        DiaCommandCode code = (DiaCommandCode)bcmd->getCommandCode();
        if (bcmd->isRequest())
        {
            if (code == DIA_CMD_DS)
            {
                DLOG_DEBUG("Constructing DSR out of diaCmd");
                s6a::DeleteSubscriberDataRequest dsdr(bcmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_ID)
            {
                DLOG_DEBUG("Constructing IDR out of diaCmd");
                s6a::InsertSubscriberDataRequest isdr(bcmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_CL)
            {
                DLOG_DEBUG("Constructing CLR out of diaCmd");
                s6a::CancelLocationRequest clr(bcmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            if(!ctxt->GetErrorCode())
            {
                ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
            }
        }
        else
        {
            ret.action = IWF_RA_DROP;
        }
    }

    catch (diameter::CodecExceptionToApp& e) {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_DEBUG("errorcode for commandCode %d is %d", bcmd->getCommandCode(), e.errcode());
        return e.errcode();
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("#### Exception: %s ####", e.what());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
    }
    catch(...)
    {
        DLOG_ERROR("#### Unknown Exception on BuildDiaResponse ####");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
    }


    return rc;
}

template <class T>
void MAPToS6aHandler::BuildErrorResponse(
        TCAP_Error *tcapError,
        T *out)
{
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
    if (!tcapError->HasError())
    {
        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        out->setResultCode(res);
        return;
    }

    ITS_OCTET errCode = 0;
    tcapError->GetError(errCode);
#if 0
    if (errCode != map_common::ERR_unknownSubscriber)
    {
        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        out->setResultCode(res);
        return;
    }
#endif
    ITS_ByteArray buffer;
    tcapError->GetParameter(buffer);
    Octets oct(buffer);

    diameter::base::ExperimentalResult res;
    unsigned resCode = 0;
    res.setVendorId(diameter::base::VendorId(DIAMETER_3GPP_VENDOR_ID));

    switch(errCode)
    {
        case map_common::ERR_unknownSubscriber:
            {
                if (oct.GetSize() > 0)
                {
                    UnknownSubscriberParam unkwnSubs;
                    unkwnSubs.Decode(oct);

                    LogMAPAsnObj(unkwnSubs);

                    resCode = DIAMETER_ERROR_USER_UNKNOWN;

                    if (unkwnSubs.OptionUnknownSubscriberDiagnostic())
                    {
                        unsigned long diag = unkwnSubs.GetUnknownSubscriberDiagnostic().GetValue();
                        if (diag == UnknownSubscriberDiagnostic::UNKNOWN_SUBSCRIBER_DIAGNOSTIC_GPRS_EPS_SUBSCRIPTION_UNKNOWN)
                        {
                            resCode = DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION;
                        }
                    }
                }
                else
                {
                    DLOG_WARNING("Unknown Subscriber IE - no optional parameter present");
                    diameter::base::ResultCode res(DIAMETER_ERROR_USER_UNKNOWN);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_roamingNotAllowed:
            {
                if (oct.GetSize() > 0)
                {
                    RoamingNotAllowedParam roamNot;
                    roamNot.Decode(oct);

                    DLOG_DEBUG("Roaming Not Allowed IE - decoding optional parameter");

                    LogMAPAsnObj(roamNot);

                    resCode = DIAMETER_ERROR_ROAMING_NOT_ALLOWED;
                    if (roamNot.OptionAdditionalRoamingNotAllowedCause())
                    {
                        unsigned long diag = roamNot.GetAdditionalRoamingNotAllowedCause().GetValue();
                        if (diag == 0)
                        {
                            resCode = DIAMETER_ERROR_RAT_NOT_ALLOWED;
                        }
                    }
                }
                else
                {
                    DLOG_WARNING("Roaming Not Allowed IE - no optional parameter present");
                    diameter::base::ResultCode res(DIAMETER_ERROR_ROAMING_NOT_ALLOWED);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_dataMissing:
            {
                if (oct.GetSize() > 0)
                {
                    DataMissingParam datamiss;
                    datamiss.Decode(oct);

                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    DLOG_DEBUG("Data Missing Param IE - decoding optional parameter");
                    LogMAPAsnObj(datamiss);
                    return;
                }
                else
                {
                    DLOG_WARNING("Data Missing Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_unexpectedDataValue:
            {
                if (oct.GetSize() > 0)
                {
                    UnexpectedDataParam udp;
                    udp.Decode(oct);

                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    DLOG_DEBUG("Unexpected data Param IE - decoding optional parameter");
                    LogMAPAsnObj(udp);
                    if(udp.OptionUnexpectedSubscriber())
                    {
                        /* TODO : Map it to appropriate diameter error */
                    }
                    return;
                }
                else
                {
                    DLOG_WARNING("Unexpected data Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_facilityNotSupported:
            {
                if (oct.GetSize() > 0)
                {
                    FacilityNotSupParam fns;
                    fns.Decode(oct);

                    DLOG_DEBUG("Facility not supported Param IE - decoding optional parameter");
                    LogMAPAsnObj(fns);
                    resCode = ITS_DIA_UNABLE_TO_COMPLY;
                    if(fns.OptionShapeOfLocationEstimateNotSupported())
                    {
                        /* TODO : Map it to appropriate diameter error */
                    }
                    if(fns.OptionNeededLcsCapabilityNotSupportedInServingNode())
                    {
                        /* TODO : Map it to appropriate diameter error */
                    }
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                else
                {
                    DLOG_WARNING("Facility not supported Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_systemFailure:
            {
                if (oct.GetSize() > 0)
                {
                    SystemFailureParam sfp;
                    sfp.Decode(oct);

                    DLOG_DEBUG("system failure Param IE - decoding optional parameter");
                    LogMAPAsnObj(sfp);
                    resCode = ITS_DIA_UNABLE_TO_COMPLY;

                    if(sfp.ChoiceNetworkResource())
                    {
                        /* unsigned long diag = sfp.GetChoiceNetworkResource().GetValue();
                         * TODO : Map it to appropriate diameter error */
                    }
                    if(sfp.ChoiceExtensibleSystemFailureParam())
                    {
                        ExtensibleSystemFailureParam esfp = sfp.GetChoiceExtensibleSystemFailureParam();

                        if(esfp.OptionNetworkResource())
                        {
                            /* unsigned long diag = esfp.GetNetworkResource().GetValue();
                             * TODO : Map it to appropriate diameter error */
                        }
                        if(esfp.OptionAdditionalNetworkResource())
                        {
                            /* unsigned long diag = esfp.GetAdditionalNetworkResource().GetValue();
                             * TODO : Map it to appropriate diameter error */
                        }
                        if(esfp.OptionFailureCauseParam())
                        {
                            /* unsigned long diag = esfp.GetFailureCauseParam().GetValue();
                             * TODO : Map it to appropriate diameter error */
                        }
                    }
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                else
                {
                    DLOG_WARNING("system failure Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_illegalSubscriber:
            {
                if (oct.GetSize() > 0)
                {
                    IllegalSubscriberParam isp;
                    isp.Decode(oct);

                    resCode = DIAMETER_ERROR_USER_UNKNOWN;
                    DLOG_DEBUG("Illegal Subscriber Param IE - decoding optional parameter");
                    LogMAPAsnObj(isp);
                }
                else
                {
                    DLOG_WARNING("Illegal Subscriber  Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_illegalEquipment:
            {
                if (oct.GetSize() > 0)
                {
                    IllegalEquipmentParam iep;
                    iep.Decode(oct);

                    DLOG_DEBUG("Illegal Eqipment Param IE - decoding optional parameter");
                    LogMAPAsnObj(iep);
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                else
                {
                    DLOG_WARNING("Illegal Equipment Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_absentSubscriber:
            {
                if (oct.GetSize() > 0)
                {
                    AbsentSubscriberParam asp;
                    asp.Decode(oct);

                    DLOG_DEBUG("Absent Subscriber Param IE - decoding optional parameter");
                    LogMAPAsnObj(asp);
                    resCode = DIAMETER_ERROR_USER_UNKNOWN;
                    if(asp.OptionAbsentSubscriberReason())
                    {
                        /* unsigned long diag = asp.GetAbsentSubscriberReason().GetValue();
                         * TODO : Map it to appropriate diameter error */
                    }
                }
                else
                {
                    DLOG_WARNING("Absent Subscriber Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }

        case map_common::ERR_unidentifiedSubscriber:
            {
                if (oct.GetSize() > 0)
                {
                    UnidentifiedSubParam usp;
                    usp.Decode(oct);

                    resCode = DIAMETER_ERROR_USER_UNKNOWN;

                    DLOG_DEBUG("Illegal Subscriber Param IE - decoding optional parameter");
                    LogMAPAsnObj(usp);
                }
                else
                {
                    DLOG_WARNING("Illegal Subscriber  Param IE - no optional parameter present");
                    diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                    out->setResultCode(res);
                    return;
                }
                break;
            }
        case map_common::ERR_tracingBufferFull:
            {
                DLOG_DEBUG("Operational or Maintainance Error");
                if(oct.GetSize() > 0)
                {
                    TracingBufferFullParam tbfp;
                    tbfp.Decode(oct);
                    LogMAPAsnObj(tbfp);
                }
                diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
                out->setResultCode(res);
                return;
                break;
            }

        default:
            /* should not reach this */
            break;
    }

    res.setExperimentalResultCode(diameter::base::ExperimentalResultCode(resCode));
    out->setExperimentalResult(res);
}

void MAPToS6aHandler::BuildGERANVector(const unsigned idx,
        const AuthenticationTriplet& in,
        s6a::GERANVector& out)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    out.setRAND(s6a::RAND(IWFUtils::VectorToString(rand)));

    const std::vector<byte>& sres = in.GetSres().GetArray();
    out.setSRES(s6a::SRES(IWFUtils::VectorToString(sres)));

    const std::vector<byte>& kc = in.GetKc().GetArray();
    out.setKc(s6a::Kc(IWFUtils::VectorToString(kc)));
}

void MAPToS6aHandler::BuildUTRANVector(const unsigned idx,
        const AuthenticationQuintuplet& in,
        s6a::UTRANVector& out)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    out.setRAND(s6a::RAND(IWFUtils::VectorToString(rand)));

    const std::vector<byte>& xres = in.GetXres().GetArray();
    out.setXRES(s6a::XRES(IWFUtils::VectorToString(xres)));

    const std::vector<byte>& ck = in.GetCk().GetArray();
    out.setCK(s6a::CK(IWFUtils::VectorToString(ck)));

    const std::vector<byte>& ik = in.GetIk().GetArray();
    out.setIK(s6a::IK(IWFUtils::VectorToString(ik)));

    const std::vector<byte>& autn = in.GetAutn().GetArray();
    out.setAUTN(s6a::AUTN(IWFUtils::VectorToString(autn)));
}

void MAPToS6aHandler::BuildEPSAuthSetList(const unsigned idx,
        const s6a::EUTRANVector& in,
        map_v13::EPC_AV& out)
{
    std::vector<byte> randValue = IWFUtils::StringToVector(in.getRAND().value());
    map_v13::RAND m_rand(randValue);
    out.SetRand(m_rand);

    std::vector<byte> xresValue = IWFUtils::StringToVector(in.getXRES().value());
    map_v13::XRES m_xres(xresValue);
    out.SetXres(m_xres);

    std::vector<byte> autnValue = IWFUtils::StringToVector(in.getAUTN().value());
    map_v13::AUTN m_autn(autnValue);
    out.SetAutn(m_autn);

    std::vector<byte> kasmeValue = IWFUtils::StringToVector(in.getKASME().value());
    map_v13::KASME m_kasme(kasmeValue);
    out.SetKasme(m_kasme);
}

void MAPToS6aHandler::BuildTripletList(const unsigned idx,
        const s6a::GERANVector& in,
        map_v13::TripletList& out)
{
    AuthenticationTriplet at;

    std::vector<byte> randValue = IWFUtils::StringToVector(in.getRAND().value());
    map_v13::RAND m_rand(randValue);
    at.SetRand(m_rand);

    std::vector<byte> sresValue = IWFUtils::StringToVector(in.getSRES().value());
    map_v13::SRES m_sres(sresValue);
    at.SetSres(m_sres);

    std::vector<byte> kcValue = IWFUtils::StringToVector(in.getKc().value());
    map_v13::Kc m_kc(kcValue);
    at.SetKc(m_kc);

    out.AddElement(at);
}

void MAPToS6aHandler::BuildQuintupletList(const unsigned idx,
        const s6a::UTRANVector& in,
        map_v13::QuintupletList& out)
{
    AuthenticationQuintuplet aqt;

    std::vector<byte> randValue = IWFUtils::StringToVector(in.getRAND().value());
    map_v13::RAND m_rand(randValue);
    aqt.SetRand(m_rand);

    std::vector<byte> xresValue = IWFUtils::StringToVector(in.getXRES().value());
    map_v13::XRES m_xres(xresValue);
    aqt.SetXres(m_xres);

    std::vector<byte> ckValue = IWFUtils::StringToVector(in.getCK().value());
    map_v13::CK m_ck(ckValue);
    aqt.SetCk(m_ck);

    std::vector<byte> ikValue = IWFUtils::StringToVector(in.getIK().value());
    map_v13::IK m_ik(ikValue);
    aqt.SetIk(m_ik);

    std::vector<byte> autnValue = IWFUtils::StringToVector(in.getAUTN().value());
    map_v13::AUTN m_autn(autnValue);
    aqt.SetAutn(m_autn);

    out.AddElement(aqt);
}

void MAPToS6aHandler::BuildEUTRANVector(const unsigned idx,
        const EPC_AV& in,
        s6a::EUTRANVector& out)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    out.setRAND(s6a::RAND(IWFUtils::VectorToString(rand)));

    const std::vector<byte>& xres = in.GetXres().GetArray();
    out.setXRES(s6a::XRES(IWFUtils::VectorToString(xres)));

    const std::vector<byte>& autn = in.GetAutn().GetArray();
    out.setAUTN(s6a::AUTN(IWFUtils::VectorToString(autn)));

    const std::vector<byte>& kasme = in.GetKasme().GetArray();
    out.setKASME(s6a::KASME(IWFUtils::VectorToString(kasme)));
}

    template <class T>
void MAPToS6aHandler::ConstructErrorAnswer(int error,T *out)
{
    diameter::base::BaseGenericCommand *diaBaseGenCmd = (diameter::base::BaseGenericCommand *) out;
    diameter::DiaHeader& hdr = const_cast<diameter::DiaHeader&>(diaBaseGenCmd->getHeader());

    /*Set the E BIT Explicitly*/
    hdr.flags.e = 1;
    DLOG_DEBUG("ConstructErrorAnswer: E-BIT is : %d", hdr.flags.e);

    if(error == DIAMETER_ERROR_USER_UNKNOWN)
    {
        //NOTE: As per map spec 29272, set error code in Experimental ResultCode
        diameter::base::ExperimentalResult experimentalresult;
        diameter::base::ExperimentalResultCode errcode(error);
        diameter::base::VendorId vendorid(DIAMETER_3GPP_VENDOR_ID);
        experimentalresult.setVendorId(vendorid);
        experimentalresult.setExperimentalResultCode(errcode);
        out->setExperimentalResult(experimentalresult);
    }
    else
    {
        diameter::base::ResultCode res(error);
        out->setResultCode(res);
    }

    /* Auth session state -> NO_STATE_MAINTAINED */
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}
void MAPToS6aHandler::ResetReq_To_ResetArg(IwfFsm *ctxt,
        s6a::ResetRequest *in,
        ResetArg* out)
{
    /* Reset is sent from the HLR (MAPv1 or MAPv2) */

    uint8_t l_hlrnumber[10] = {0};
    std::string hlrNumber = m_config.HlrNumber();
    if(hlrNumber.length() > 20)
    {
        hlrNumber.erase(20, std::string::npos);
    }
    int len = IWFUtils::StringToTBCD(hlrNumber.substr(0, 2), l_hlrnumber, 2, 0, true);
    len += IWFUtils::StringToTBCD(hlrNumber.substr(2), (l_hlrnumber+1), 20);
    if (hlrNumber.length() % 2)
    {
        l_hlrnumber[(hlrNumber.length() / 2)] |= 0xF0;
    }

    map_v13::ISDN_AddressString isdn(IWFUtils::ByteArrayToVector(l_hlrnumber, len));
    out->SetHlr_Number(isdn);

    /*    out->SetHlr_Number(new ISDN_AddressString(IWFUtils::StringToVector(
          IwfHssToSgsnCache::getInstance()->getHssNumber(in->getOriginHost().value()))));*/

    /* HLR-List from User-Id AVP  */
    if (in->countUserId() > 0)
    {
        HLR_List ocHlrList;
        for (int i = 0; i < in->countUserId(); i++)
        {
            uint8_t uhlrid[IWF_MAX_E164_SZ/2] = {'\0'};

            std::string shlrid = in->getUserId(i).value();
            IWFUtils::StringToTBCD(shlrid, uhlrid, IWF_MAX_E164_SZ, 0xF);

            ocHlrList.AddElement(new HLR_Id(IWF_FixedArrayToVector(uhlrid)));
        }

        out->SetHlr_List(ocHlrList);
    }

}
void MAPToS6aHandler::PurgeMSArg_To_PUR(IwfFsm *ctxt,
        const PurgeMS_Arg *in,
        s6a::PurgeUERequest *out)
{

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    std::string oImsi;
    const std::vector<byte>& vec = in->GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }
    ctxt->SetImsi(oImsi);
    out->setUserName(diameter::base::UserName(oImsi));

}

void MAPToS6aHandler::ProvideSubscriberInfoRes_To_IDA(IwfFsm *ctxt,
        const map_v13::ProvideSubscriberInfoRes *in,
        s6a::InsertSubscriberDataAnswer *out)
{
    TCAP_Component* cpt = ctxt->GetCurrRcvdTcapCpt();
    ITS_USHORT cptType = cpt->GetComponentType();

    if (cptType != TCPPT_TC_RESULT_L)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    SubscriberInfo si = in->GetSubscriberInfo();

    if(si.OptionImsVoiceOverPS_SessionsIndication())
    {
        const IMS_VoiceOverPS_SessionsInd &ims = si.GetImsVoiceOverPS_SessionsIndication().GetValue();
        if(ims.IsImsVoiceOverPS_SessionsNotSupported())
            out->setIMSVoiceOverPSSessionsSupported(s6a::IMSVoiceOverPSSessionsSupported(s6a::IMSVoiceOverPSSessionsSupported::NOT_SUPPORTED));
        else if(ims.IsImsVoiceOverPS_SessionsSupported())
            out->setIMSVoiceOverPSSessionsSupported(s6a::IMSVoiceOverPSSessionsSupported(s6a::IMSVoiceOverPSSessionsSupported::SUPPORTED));
    }
    if(si.OptionLastUE_ActivityTime())
    {
        const std::vector<byte>& vec = si.GetLastUE_ActivityTime().GetArray();
        uint32_t res = IWFUtils::ByteArray4ToUInt32(vec);
        out->setLastUEActivityTime(s6a::LastUEActivityTime(res));
    }
    if(si.OptionLastRAT_Type())
    {
        const Used_RAT_Type &urattype = si.GetLastRAT_Type().GetValue();
        if(urattype.IsUtran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::UTRAN));
        }
        else if(urattype.IsGeran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::GERAN));
        }
        else if(urattype.IsGan())
        {
            out->setRATType(s6a::RATType(s6a::RATType::GAN));
        }
        else if(urattype.IsI_hspa_evolution())
        {
            out->setRATType(s6a::RATType(s6a::RATType::HSPA_EVOLUTION));
        }
        else if(urattype.IsE_utran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::EUTRAN));
        }
    }
    if(si.OptionEps_SubscriberState())
    {
        s6a::EPSUserState epsuserstate;
        map_v13::PS_SubscriberState psstate = si.GetEps_SubscriberState();
        if(!psstate.ChoiceNotProvidedFromSGSNorMME())
        {
            s6a::SGSNUserState sgsnuserstate;
            if(psstate.ChoicePs_Detached())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::DETACHED));
            }
            if(psstate.ChoicePs_AttachedNotReachableForPaging())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::ATTACHED_NOT_REACHABLE_FOR_PAGING));
            }
            if(psstate.ChoicePs_AttachedReachableForPaging())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::ATTACHED_REACHABLE_FOR_PAGING));
            }
            if(psstate.ChoicePs_PDP_ActiveNotReachableForPaging())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::CONNECTED_NOT_REACHABLE_FOR_PAGING));
            }
            if(psstate.ChoicePs_PDP_ActiveReachableForPaging())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::CONNECTED_REACHABLE_FOR_PAGING));
            }
            if(psstate.ChoiceNetDetNotReachable())
            {
                sgsnuserstate.setUserState(s6a::UserState(s6a::UserState::NETWORK_DETERMINED_NOT_REACHABLE));
            }
            epsuserstate.setSGSNUserState(sgsnuserstate);
        }
        out->setEPSUserState(epsuserstate);
    }
    if(si.OptionLocationInformationEPS())
    {
        LocationInformationEPS lie = si.GetLocationInformationEPS();
        s6a::EPSLocationInformation epsli;
        s6a::MMELocationInformation mmeli;
        if(lie.OptionE_utranCellGlobalIdentity())
        {
            //mmeli.setEUTRANCellGlobalIdentity(s6a::EUTRANCellGlobalIdentity(IWFUtils::VectorToString(lie.GetE_utranCellGlobalIdentity().GetArray())));
            const std::vector<byte>& vecLieIEs = lie.GetE_utranCellGlobalIdentity().GetArray();
            std::string strEUTRANCGI="";
            IWFUtils::TBCDToString(&vecLieIEs[0], vecLieIEs.size(), strEUTRANCGI);
            mmeli.setEUTRANCellGlobalIdentity(s6a::EUTRANCellGlobalIdentity(strEUTRANCGI));
        }
        if(lie.OptionTrackingAreaIdentity())
        {
            //mmeli.setTrackingAreaIdentity(s6a::TrackingAreaIdentity(IWFUtils::VectorToString(lie.GetTrackingAreaIdentity().GetArray())));
            const std::vector<byte>& vecLieIEs = lie.GetTrackingAreaIdentity().GetArray();
            std::string strTAI="";
            IWFUtils::TBCDToString(&vecLieIEs[0], vecLieIEs.size(), strTAI);
            mmeli.setTrackingAreaIdentity(s6a::TrackingAreaIdentity(strTAI));
        }
        if(lie.OptionGeographicalInformation())
        {
            //mmeli.setGeographicalInformation(s6a::GeographicalInformation(IWFUtils::VectorToString(lie.GetGeographicalInformation().GetArray())));
            const std::vector<byte>& vecLieIEs = lie.GetGeographicalInformation().GetArray();
            std::string strGeographicalInformation="";
            IWFUtils::TBCDToString(&vecLieIEs[0], vecLieIEs.size(), strGeographicalInformation);
            mmeli.setGeographicalInformation(s6a::GeographicalInformation(strGeographicalInformation));
        }
        if(lie.OptionGeodeticInformation())
        {
            //mmeli.setGeodeticInformation(s6a::GeodeticInformation(IWFUtils::VectorToString(lie.GetGeodeticInformation().GetArray())));
            const std::vector<byte>& vecLieIEs = lie.GetGeodeticInformation().GetArray();
            std::string strGeodeticInformation="";
            IWFUtils::TBCDToString(&vecLieIEs[0], vecLieIEs.size(), strGeodeticInformation);
            mmeli.setGeodeticInformation(s6a::GeodeticInformation(strGeodeticInformation));
        }
        if(lie.OptionCurrentLocationRetrieved())
        {
            mmeli.setCurrentLocationRetrieved(s6a::CurrentLocationRetrieved(s6a::CurrentLocationRetrieved::ACTIVE_LOCATION_RETRIEVAL));
        }
        if(lie.OptionAgeOfLocationInformation())
        {
            mmeli.setAgeOfLocationInformation(s6a::AgeOfLocationInformation(lie.GetAgeOfLocationInformation().GetValue()));
        }
        epsli.setMMELocationInformation(mmeli);

        out->setEPSLocationInformation(epsli);
    }
}

void MAPToS6aHandler::IDR_To_ProvideSubscriberInfoArg(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataRequest *in,
        ProvideSubscriberInfoArg *out)
{
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));
    SetDestinationAddrinTcapDlg(ctxt, temp);


    if(in->containsIDRFlags())
    {
        RequestedInfo ri;
        const uint32_t idrflag = in->getIDRFlags().value();
        if(idrflag & IDR_FLAG_TADS_DATA_REQ)
        {
            map_v13::RequestedInfo::T_adsData tad;
            ri.SetT_adsData(tad);
        }
        if(idrflag & IDR_FLAG_EPS_USER_STATE_REQ)
        {
            map_v13::RequestedInfo::SubscriberState ss;
            ri.SetSubscriberState(ss);
        }
        if(idrflag & IDR_FLAG_EPS_LOC_INFO_REQ)
        {
            map_v13::RequestedInfo::LocationInformation li;
            ri.SetLocationInformation(li);
        }
        if(idrflag & IDR_FLAG_CUR_LOC_REQ)
        {
            map_v13::RequestedInfo::CurrentLocation cl;
            ri.SetCurrentLocation(cl);
        }
        out->SetRequestedInfo(ri);
    }

}

int MAPToS6aHandler::SendAuthenticationInfoArg_To_AIR(IwfFsm *ctxt,
        const SendAuthenticationInfoArg *in,
        s6a::AuthenticationInformationRequest *out)
{
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    std::string oImsi;
    const std::vector<byte>& vec = in->GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }
    out->setUserName(diameter::base::UserName(oImsi));

    string RuleName("");
    int32_t serviceKey = WILDCARD_SERVICE_KEY;
    int32_t ossn = SGSN_SSN;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,serviceKey,RuleName,ossn))
    {
       DLOG_ERROR("Could not find a RuleName configured.");
       return !ITS_SUCCESS;
    }

    if(in->OptionRequestingPLMN_Id())
    {
        const std::vector<byte>& vec = in->GetRequestingPLMN_Id().GetArray();

        if(IwfController::Instance().Config().LocalConfig().IsVplmnIdToBeValidated() &&
                IWFUtils::CompareVplmnId(&vec[0], oImsi,RuleName))
        {
            DLOG_ERROR("VplmnId does not match the configured value for SendAuthenticationInfoArg");
            ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
            return !ITS_SUCCESS;
        }

        out->setVisitedPLMNId(s6a::VisitedPLMNId(IWFUtils::VectorToString(in->GetRequestingPLMN_Id().GetArray())));
    }

    if(in->OptionRequestingNodeType())
    {
        if(in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME ||
                in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN)
        {
            s6a::RequestedEUTRANAuthenticationInfo reuai;

            if(in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME)
                reuai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedVectors().GetValue()));

            if((in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) && !(in->OptionAdditionalVectorsAreForEPS()))
                reuai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedVectors().GetValue()));

            if((in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) &&
                    (in->OptionAdditionalVectorsAreForEPS()) &&
                    (in->OptionNumberOfRequestedAdditional_Vectors()))
                reuai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedAdditional_Vectors().GetValue()));

            if((in->OptionImmediateResponsePreferred()) && (in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME))
                reuai.setImmediateResponsePreferred(s6a::ImmediateResponsePreferred(in->GetRequestingNodeType().GetValue()));

            if((in->OptionImmediateResponsePreferred()) &&
                    (in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) &&
                    !(in->OptionAdditionalVectorsAreForEPS()))
                reuai.setImmediateResponsePreferred(s6a::ImmediateResponsePreferred(in->GetRequestingNodeType().GetValue()));

            if(in->OptionRe_synchronisationInfo())
            {
                Re_synchronisationInfo resyn = in->GetRe_synchronisationInfo();
                std::string Resync = IWFUtils::VectorToString(resyn.GetRand().GetArray()) + IWFUtils::VectorToString(resyn.GetAuts().GetArray());
                s6a::ReSynchronizationInfo resyncinfo(Resync);
                reuai.setReSynchronizationInfo(resyncinfo);
            }

            out->setRequestedEUTRANAuthenticationInfo(reuai);
        }

        if(in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_SGSN ||
                in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN)
        {
            s6a::RequestedUTRANGERANAuthenticationInfo reugai;

            if(in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_SGSN)
                reugai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedVectors().GetValue()));

            if((in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) && (in->OptionAdditionalVectorsAreForEPS()))
                reugai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedVectors().GetValue()));

            if((in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) &&
                    !(in->OptionAdditionalVectorsAreForEPS()) &&
                    (in->OptionNumberOfRequestedAdditional_Vectors()))
                reugai.setNumberOfRequestedVectors(s6a::NumberOfRequestedVectors(in->GetNumberOfRequestedAdditional_Vectors().GetValue()));

            if((in->OptionImmediateResponsePreferred()) && (in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_SGSN))
                reugai.setImmediateResponsePreferred(s6a::ImmediateResponsePreferred(in->GetRequestingNodeType().GetValue()));

            if((in->OptionImmediateResponsePreferred()) &&
                    (in->GetRequestingNodeType().GetValue() == RequestingNodeType::REQUESTING_NODE_TYPE_MME_SGSN) &&
                    (in->OptionAdditionalVectorsAreForEPS()))
                reugai.setImmediateResponsePreferred(s6a::ImmediateResponsePreferred(in->GetRequestingNodeType().GetValue()));

            if(in->OptionRe_synchronisationInfo())
            {
                Re_synchronisationInfo resyn = in->GetRe_synchronisationInfo();
                std::string Resync = IWFUtils::VectorToString(resyn.GetRand().GetArray()) + IWFUtils::VectorToString(resyn.GetAuts().GetArray());
                s6a::ReSynchronizationInfo resyncinfo(Resync);
                reugai.setReSynchronizationInfo(resyncinfo);
            }
            out->setRequestedUTRANGERANAuthenticationInfo(reugai);
        }
    }

    return ITS_SUCCESS;
}

void MAPToS6aHandler::PUA_To_PurgeMSRes(IwfFsm *ctxt,
        const s6a::PurgeUEAnswer *in,
        PurgeMS_Res *out)
{

    if (!ctxt || !in || !out)
    {
        return;
    }
    if(in->containsPUAFlags())
    {
        if(in->getPUAFlags().value() & PUA_FLAG_FREEZ_M_TMSI)
        {
            map_v13::PurgeMS_Res::FreezeM_TMSI mtmsi;
            out->SetFreezeM_TMSI(mtmsi);
        }
        if(in->getPUAFlags().value() & PUA_FLAG_FREEZ_P_TMSI)
        {
            map_v13::PurgeMS_Res::FreezeP_TMSI ptmsi;
            out->SetFreezeP_TMSI(ptmsi);
        }
    }
}

void MAPToS6aHandler::AIA_To_SendAuthenticationInfoRes(IwfFsm *ctxt,
        const s6a::AuthenticationInformationAnswer *in,
        map_v13::SendAuthenticationInfoRes *out)
{

    if (!ctxt || !in || !out)
    {
        return;
    }
    if(in->containsAuthenticationInfo())
    {
        s6a::AuthenticationInfo ai = in->getAuthenticationInfo();
        map_v13::AuthenticationSetList authenticationSetList;
        //NOTE: At a time only one AVP will be present in AIA, either UTRAN or GERAN or E-UTRAN
        if(ai.countUTRANVector())
        {
            for (int i = 0; i < ai.countUTRANVector(); i++)
            {
                map_v13::QuintupletList qtl;
                BuildQuintupletList(i, ai.getUTRANVector(i), qtl);
                authenticationSetList.SetChoiceQuintupletList(qtl);
            }
            out->SetAuthenticationSetList(authenticationSetList);
        }

        if(ai.countGERANVector())
        {
            for (int i = 0; i < ai.countGERANVector(); i++)
            {
                map_v13::TripletList tl;
                BuildTripletList(i, ai.getGERANVector(i), tl);
                authenticationSetList.SetChoiceTripletList(tl);
            }
            out->SetAuthenticationSetList(authenticationSetList);
        }

        if(ai.countEUTRANVector())
        {
            map_v13::EPS_AuthenticationSetList epsAuth;

            for (int i = 0; i < ai.countEUTRANVector(); i++)
            {
                map_v13::EPS_AuthenticationSetList::EPC_AV epcAv;
                BuildEPSAuthSetList(i, ai.getEUTRANVector(i), epcAv);
                epsAuth.AddElement(epcAv);
            }
            out->SetEps_AuthenticationSetList(epsAuth);
        }
    }
}

void MAPToS6aHandler::ULA_To_UpdateGprsLocationRes(IwfFsm *ctxt,
        const s6a::UpdateLocationAnswer *in,
        UpdateGprsLocationRes *out)
{
    if (!ctxt || !in || !out)
    {
        return;
    }

    map_v13::UpdateGprsLocationRes::Add_Capability ac;
    out->SetAdd_Capability(ac);

    if (in->containsULAFlags())
    {
        if (in->getULAFlags().value() & ULA_FLAG_S6A_S6D_IND)
        {
            map_v13::UpdateGprsLocationRes::Sgsn_mmeSeparationSupported sgsnm;
            out->SetSgsn_mmeSeparationSupported(sgsnm);
        }
    }
    uint8_t l_hlrnumber[10] = {0};
    std::string hlrNumber = m_config.HlrNumber();
    if(hlrNumber.length() > 20)
    {
        hlrNumber.erase(20, std::string::npos);
    }
    int len = IWFUtils::StringToTBCD(hlrNumber.substr(0, 2), l_hlrnumber, 2, 0, true);
    len += IWFUtils::StringToTBCD(hlrNumber.substr(2), (l_hlrnumber+1), 20);
    if (hlrNumber.length() % 2)
    {
        l_hlrnumber[(hlrNumber.length() / 2)] |= 0xF0;
    }

    map_v13::ISDN_AddressString isdn(IWFUtils::ByteArrayToVector(l_hlrnumber, len));
    out->SetHlr_Number(isdn);
}

void MAPToS6aHandler::UpdateSessionCtxt(IwfFsm *ctxt, std::string imsi)
{
    TCAP_Dialogue* tcapDlg = ctxt->GetCurrRcvdTcapDlg();
    TCAP_Begin *begin = (TCAP_Begin*)tcapDlg;
    SCCP_CallingPartyAddr calligpartyaddr;
    ITS_UINT originPC = 0;
    begin->GetOrigAddr(calligpartyaddr);
    begin->GetOPC(originPC);

    SessionCtxt *sctxt = ctxt->GetTransactionManager()->GetSessionCtxt(imsi);
    if(sctxt && !sctxt->OldCallingPartyAddrpresent())
    {
        /*
        sctxt->SetOldCallingPartyAddress(sctxt->GetPbSccpParameters().sccpcallingpartyaddr());;
        sctxt->sccpParameter.cpa_itu = calligpartyaddr;
        sctxt->m_oldopc = sctxt->sccpParameter.m_opc;
        sctxt->sccpParameter.m_opc = originPC;
        sctxt->OldCallingPartyAddrpresent = true;
        */
        sctxt->UpdateSessionContext(calligpartyaddr, originPC);
    }
}

int MAPToS6aHandler::UpdateGprsLocationArg_To_ULR(IwfFsm *ctxt,
        const UpdateGprsLocationArg *in,
        s6a::UpdateLocationRequest *out)
{
    std::string oImsi;
    const std::vector<byte>& vec = in->GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }
    out->setUserName(diameter::base::UserName(oImsi));

    UpdateSessionCtxt(ctxt, oImsi);


    string RuleName("");
    int32_t serviceKey = WILDCARD_SERVICE_KEY;
    int32_t ossn = SGSN_SSN;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,serviceKey,RuleName,ossn))
    {
       DLOG_ERROR("Could not find a RuleName configured.");
       return !ITS_SUCCESS;
    }

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    std::string oSgsnNumber;
    std::string vSgsnNumber;
    std::string sgsnNumber;
    const std::vector<byte>& vec1 = in->GetSgsn_Number().GetArray();
    IWFUtils::TBCDToString(&vec1[0], 1, vSgsnNumber,false, true);
    IWFUtils::TBCDToString(&vec1[1], (vec1.size() - 1), oSgsnNumber);
    vSgsnNumber.append(oSgsnNumber);

    std::vector<byte> t1((vec1.size() - 1));
    for(unsigned int i = 0, j = 1; i < (vec1.size() - 1); i++, j++)
    {
        t1[i] = (vec1[j] >> 4);
        t1[i] |= (vec1[j] << 4);
    }

    sgsnNumber = IWFUtils::VectorToString(t1);
    fPos = sgsnNumber.find('F');
    if (fPos != std::string::npos)
    {
        sgsnNumber.erase(fPos, std::string::npos);
    }

    s6a::SGSNNumber sgsn(sgsnNumber);
    out->setSGSNNumber(sgsn);

    std::string mccmnc;
    std::string mcc;
    std::string mnc;
    if(m_config.VplmnIdFromSgsnNumber(vSgsnNumber,mccmnc))
    {
        IWFUtils::ExtractMncMcc(mccmnc, mcc, mnc);
        if(!mcc.empty() && !mnc.empty())
        {
            unsigned char plmn[4] = {0};
            IWFUtils::CreateVisitedPlmn(plmn, mcc, mnc);

            if(IwfController::Instance().Config().LocalConfig().IsVplmnIdToBeValidated() && 
                    IWFUtils::CompareVplmnId(&plmn[0], oImsi,RuleName))
            {
                DLOG_ERROR("VplmnId does not match the configured value for UpdateGPRSLocationArg");
                ctxt->SetErrorCode(MAP_ERR_ROAMING_NOT_ALLOWED);
                return !ITS_SUCCESS;
            }

            s6a::VisitedPLMNId  visPLMNid((const char*)plmn);
            out->setVisitedPLMNId(visPLMNid);
        }
        else
        {
            DLOG_WARNING("configured mcc/mnc is wrong, cannot set visted plmn-Id");
        }
    }
    else
    {
        DLOG_ERROR("VplmnId not configured for this SGSN Number %s.",vSgsnNumber.c_str());
        return !ITS_SUCCESS;
    }

    ITS_UINT ulrFlags = 0x00;
    if(in->OptionEps_info())
    {
        const EPS_Info &eps = in->GetEps_info();
        if(eps.ChoiceIsr_Information())
        {
            if(eps.GetChoiceIsr_Information().IsCancelSGSNSet())
            {
                ulrFlags |= ULR_FLAG_SINGLE_REIGSTRATION_IND;
            }
            else if(eps.GetChoiceIsr_Information().IsInitialAttachIndicatorDefined())
            {
                ulrFlags |= ULR_FLAGS_INITIAL_ATTACH_IND;
            }
        }
    }

    if(in->OptionServingNodeTypeIndicator())
    {
        ulrFlags |= ULR_FLAG_S6A_S6D_IND;
    }

    if(in->OptionSkipSubscriberDataUpdate())
    {
        ulrFlags |= ULR_FLAG_SKIP_SUBSCRIBER_DATA;
    }

    if(!(in->OptionGprsSubscriptionDataNotNeeded()))
    {
        ulrFlags |= ULR_FLAG_GPRS_SUBSCRIPTION_DATA_IND;
    }

    if(in->OptionNodeTypeIndicator())
    {
        ulrFlags |= ULR_FLAGS_NODE_TYPE_IND;
    }
    s6a::ULRFlags ulravp(ulrFlags);
    out->setULRFlags(ulravp);

    if(in->OptionUsedRAT_Type())
    {
        const Used_RAT_Type &urattype = in->GetUsedRAT_Type().GetValue();
        if(urattype.IsUtran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::UTRAN));
        }
        else if(urattype.IsGeran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::GERAN));
        }
        else if(urattype.IsGan())
        {
            out->setRATType(s6a::RATType(s6a::RATType::GAN));
        }
        else if(urattype.IsI_hspa_evolution())
        {
            out->setRATType(s6a::RATType(s6a::RATType::HSPA_EVOLUTION));
        }
        else if(urattype.IsE_utran())
        {
            out->setRATType(s6a::RATType(s6a::RATType::EUTRAN));
        }
    }
    else
    {
        out->setRATType(s6a::RATType(s6a::RATType::EUTRAN));
    }

    if(in->OptionUe_srvcc_Capability())
    {
        out->setUESRVCCCapability(s6a::UESRVCCCapability((s6a::UESRVCCCapability::Value)in->GetUe_srvcc_Capability().GetValue()));
    }

    if(in->OptionAdd_info())
    {
        const ADD_Info &addinfo = in->GetAdd_info();
        s6a::TerminalInformation ti;
        std::string Imeisv;
        std::string svn;
        const std::vector<byte>& vec = addinfo.GetImeisv().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), Imeisv);

        std::string imei = Imeisv.substr(0, 14);
        char strCheckdigit[2] = {0};
        sprintf(strCheckdigit, "%d", GetCheckDigitForIMEI(imei));
        imei.append(strCheckdigit);
        ti.setIMEI(s6a::IMEI(imei));

        svn = Imeisv.substr(14,2);
        int i = atoi(svn.c_str());
        if(i > 0)
        {
            ti.setSoftwareVersion(s6a::SoftwareVersion(Imeisv.substr(14,2)));
        }
        out->setTerminalInformation(ti);
    }

    if(in->OptionSgsn_Capability())
    {
        const SGSN_Capability &sgsncap = in->GetSgsn_Capability();

        if(sgsncap.OptionSupportedFeatures())
        {
            uint32_t sf = IWFUtils::BitVectorToUnsigned(sgsncap.GetSupportedFeatures().GetArray());
            s6a::SupportedFeatures suppFeatu;
            suppFeatu.setVendorId(diameter::base::VendorId(10415));
            suppFeatu.setFeatureListID(s6a::FeatureListID(1));
            suppFeatu.setFeatureList(s6a::FeatureList(sf));

            out->addSupportedFeatures(suppFeatu);
        }
    }
    return ITS_SUCCESS;
}

void MAPToS6aHandler::SetDestinationAddrinTcapDlg(IwfFsm *ctxt, std::string imsi, bool IsCancelLocation)
{
    SessionCtxt *sctxt = ctxt->GetTransactionManager()->GetSessionCtxt(imsi);

    TCAP_Begin *outbegin = ctxt->GetTcapBeginDlg();

    if(sctxt)
    {
        if (IsCancelLocation &&
                sctxt->OldCallingPartyAddrpresent())
        {
            outbegin->SetDPC(sctxt->GetOldOPC());
            SCCP_CallingPartyAddr cpa_itu;
            sctxt->GetOldCallingPartyAddress(&cpa_itu);
            outbegin->SetDestAddr(cpa_itu);

            //NOTE: Resetting the flag in sessioncontext
            sctxt->ClearOldCallingPartyAddr();
        }
        else
        {
            outbegin->SetDPC(sctxt->GetOPC());
            SCCP_CallingPartyAddr cpa_itu;
            sctxt->GetCallingPartyAddr(&cpa_itu);
            outbegin->SetDestAddr(cpa_itu);
        }
    }
}

void MAPToS6aHandler::DSR_To_DeleteSubscriberDataArg(
        IwfFsm *ctxt,
        const s6a::DeleteSubscriberDataRequest *in,
        DeleteSubscriberDataArg *out)
{
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));

    SetDestinationAddrinTcapDlg(ctxt, temp);

    const uint32_t dsrFlags = in->getDSRFlags().value();

    if( dsrFlags & DSR_FLAG_REGION_SUB_WITHDRAW )
    {
        uint8_t zca[] = {0x01,0x02};
        std::vector<byte> zc(zca, zca + sizeof(zca));
        map_v13::ZoneCode regZone(zc);
        out->SetRegionalSubscriptionIdentifier(regZone);
        /* set isRegionalSubWithdraw to be used when consrtucting DSA */
        isRegionalSubWithdraw = true;
    }

    //NOTE: At a time only one flag will be set either DSR_FLAG_PDP_CONTEXT_WITHDRAW or DSR_FLAG_COMPLETE_PDP_LIST_WITHDRAW in DSR-FLags
    map_v13::GPRSSubscriptionDataWithdraw gprssub;
    if((dsrFlags & DSR_FLAG_PDP_CONTEXT_WITHDRAW) &&
            in->countContextIdentifier())
    {
        map_v13::ContextIdList cid;
        for(int i = 0; i < in->countContextIdentifier(); i++)
        {
            map_v13::ContextId contextid(in->getContextIdentifier(i).value());
            cid.AddElement(contextid);
        }
        gprssub.SetChoiceContextIdList(cid);
        out->SetGprsSubscriptionDataWithdraw(gprssub);
    }
    else if((dsrFlags & DSR_FLAG_COMPLETE_PDP_LIST_WITHDRAW) &&
            in->countContextIdentifier())
    {
        map_v13::GPRSSubscriptionDataWithdraw::AllGPRSData allgprs;
        gprssub.SetChoiceAllGPRSData(allgprs);
        out->SetGprsSubscriptionDataWithdraw(gprssub);
    }

    if( dsrFlags & DSR_FLAG_ROAM_RESTRICT_UN_SUPPORTED )
    {
        map_v13::DeleteSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsuppportedFeature rrst;
        out->SetRoamingRestrictedInSgsnDueToUnsuppportedFeature(rrst);
    }
    if( dsrFlags & DSR_FLAG_SUB_CHARGE_CHAR )
    {
        map_v13::DeleteSubscriberDataArg::ChargingCharacteristicsWithdraw ccw;
        out->SetChargingCharacteristicsWithdraw(ccw);
    }
    if( dsrFlags & DSR_FLAG_STN_SR )
    {
        map_v13::DeleteSubscriberDataArg::Stn_srWithdraw stnw;
        out->SetStn_srWithdraw(stnw);
    }
    if( (dsrFlags & DSR_FLAG_COMPLETE_APN_CONFIG) ||
            ( dsrFlags & DSR_FLAG_PDN_SUBSCRIPTION_WITHDRAW) )
    {
        map_v13::EPS_SubscriptionDataWithdraw epsSubData;

        /* check for the sub-parameter allEPSData */
        if( dsrFlags & DSR_FLAG_COMPLETE_APN_CONFIG )
        {
            map_v13::EPS_SubscriptionDataWithdraw::AllEPS_Data aed;
            epsSubData.SetChoiceAllEPS_Data(aed);
        }
        if(dsrFlags & DSR_FLAG_PDN_SUBSCRIPTION_WITHDRAW)
        {
            if( in->countContextIdentifier() )
            {
                map_v13::ContextIdList ctxtidlist;
                for(int i = 0; i < in->countContextIdentifier() ; i++)
                {
                    map_v13::ContextId contextid((in->getContextIdentifier(i).value()));
                    ctxtidlist.AddElement(contextid);
                }
                epsSubData.SetChoiceContextIdList(ctxtidlist);
            }
        }
        out->SetEpsSubscriptionDataWithdraw(epsSubData);
    }
    if( dsrFlags & DSR_FLAG_GMLC_LIST_WITHDRAW )
    {
        map_v13::DeleteSubscriberDataArg::Gmlc_ListWithdraw gmlcw;
        out->SetGmlc_ListWithdraw(gmlcw);
    }
    if( dsrFlags & DSR_FLAG_LCS_WITHDRAW )
    {
        map_v13::SS_List sslist;
        for(int i =0 ; i < in->countSSCode() ; i++)
        {
            map_v13::SS_Code sscode(IWFUtils::StringToVector(in->getSSCode(i).value()));
            sslist.AddElement(sscode);
        }
        out->SetSs_List(sslist);
    }
    if( dsrFlags & DSR_FLAG_ASPN_OI_REPLACEMENT )
    {
        map_v13::DeleteSubscriberDataArg::Apn_oi_replacementWithdraw apnoirw;
        out->SetApn_oi_replacementWithdraw(apnoirw);
    }
    if( dsrFlags & DSR_FLAG_CSG_DELETED )
    {
        map_v13::DeleteSubscriberDataArg::Csg_SubscriptionDeleted csgsd;
        out->SetCsg_SubscriptionDeleted(csgsd);
    }
    if( dsrFlags & DSR_FLAG_SMS_WITHDRAW )
    {
        map_v13::SS_List sslist;
        for(int i =0 ; i < in->countSSCode() ; i++ )
        {
            map_v13::SS_Code sscode(IWFUtils::StringToVector(in->getSSCode(i).value()));
            sslist.AddElement(sscode);
        }
        out->SetSs_List(sslist);
    }

}

void MAPToS6aHandler::DeleteSubscriberDataRes_To_DSA(
        IwfFsm *ctxt,
        const DeleteSubscriberDataRes *in,
        s6a::DeleteSubscriberDataAnswer *out)
{
    if( !ctxt || !in || !out)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
    if( in->OptionRegionalSubscriptionResponse() )
    {
        ITS_UINT dsaFlags = 0x00;
        if( (in->GetRegionalSubscriptionResponse().IsNetworkNode_AreaRestricted()) )
        {
            dsaFlags |= DSA_FLAG_NET_NODE_AREA_RESTRICT;
            s6a::DSAFlags dsaAvp(dsaFlags);
            out->setDSAFlags(dsaAvp);
        }
        else
        {
            s6a::DSAFlags dsaAvp(dsaFlags);
            out->setDSAFlags(dsaAvp);
        }
        if( isRegionalSubWithdraw &&
                (!(in->GetRegionalSubscriptionResponse().
                   IsRegionalSubscNotSupported())) )
        {
            s6a::SupportedFeatures suppfeature;
            suppfeature.setVendorId(diameter::base::VendorId(10415));
            suppfeature.setFeatureListID(s6a::FeatureListID(1));
            suppfeature.setFeatureList(s6a::FeatureList(1<<9));
            out->addSupportedFeatures(suppfeature);
            /* clear isRegionalSubWithdraw */
            isRegionalSubWithdraw = false;
        }
    }
}

void MAPToS6aHandler::CancelLocationRes_To_CLA(IwfFsm *ctxt,
        const CancelLocationRes *in,
        s6a::CancelLocationAnswer *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);

    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

}

void MAPToS6aHandler::InsertSubscriberDataRes_To_IDA(IwfFsm *ctxt,
        const InsertSubscriberDataRes *in,
        s6a::InsertSubscriberDataAnswer *out)
{

    if( !ctxt || !in || !out)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    if(in->OptionRegionalSubscriptionResponse())
    {
        ITS_UINT idaflag = 0x00;
        if(in->GetRegionalSubscriptionResponse().IsRegionalSubscNotSupported())
        {
            idaflag |= IDA_FLAG_NET_NODE_AREA_RESTRICT;
            s6a::IDAFlags idaAvp(idaflag);
            out->setIDAFlags(idaAvp);
        }
        else
        {
            s6a::IDAFlags idaAvp(idaflag);
            out->setIDAFlags(idaAvp);
        }
    }

    if(in->OptionSupportedFeatures())
    {
        uint32_t sf = IWFUtils::BitVectorToUnsigned(in->GetSupportedFeatures().GetArray());
        s6a::SupportedFeatures suppFeatu;
        suppFeatu.setVendorId(diameter::base::VendorId(10415));
        suppFeatu.setFeatureListID(s6a::FeatureListID(1));
        suppFeatu.setFeatureList(s6a::FeatureList(sf));

        out->addSupportedFeatures(suppFeatu);
    }
}

void MAPToS6aHandler::CLR_To_CancelLocationArg(IwfFsm *ctxt,
        const s6a::CancelLocationRequest *in,
        CancelLocationArg *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    uint8_t imsi[IWF_MAX_E164_SZ/2];

    memset(imsi, 0, (IWF_MAX_E164_SZ/2));
    /* UserName To IMSI */
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    /* TODO: FIX is required on ARRAY Size. It can not have static array size IMSI could vary */
    Identity ocIdent;
    ocIdent.SetChoiceImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    out->SetIdentity(ocIdent);

    std::string temp(simsi.substr(0, simsi.find('@')));

    SetDestinationAddrinTcapDlg(ctxt, temp, true);
    ctxt->SetImsi(temp);

    if ((in->getCancellationType().value() ==
                s6a::CancellationType::MME_UPDATE_PROCEDURE) || (in->getCancellationType().value() ==
                    s6a::CancellationType::SGSN_UPDATE_PROCEDURE))
    {
        out->SetCancellationType(new CancellationType(CancellationType::CANCELLATION_TYPE_UPDATE_PROCEDURE));
    }
    else if (in->getCancellationType().value() == s6a::CancellationType::SUBSCRIPTION_WITHDRAWAL)
    {
        out->SetCancellationType(new CancellationType(CancellationType::CANCELLATION_TYPE_SUBSCRIPTION_WITHDRAW));
    }
    else if (in->getCancellationType().value() == (s6a::CancellationType::Value)4)
    {
        out->SetCancellationType(new CancellationType(CancellationType::CANCELLATION_TYPE_INITIAL_ATTACH_PROCEDURE));
    }

    if(in->containsCLRFlags())
    {
        if((in->getCLRFlags().value() == 0) && ((in->getCancellationType().value() == s6a::CancellationType::SGSN_UPDATE_PROCEDURE) ||
                    (in->getCancellationType().value() == s6a::CancellationType::INITIAL_ATTACH_PROCEDURE)))
        {
            out->SetTypeOfUpdate(new TypeOfUpdate(TypeOfUpdate::TYPE_OF_UPDATE_SGSN_CHANGE));
        }
        else if((in->getCLRFlags().value() != 0) && ((in->getCancellationType().value() == s6a::CancellationType::MME_UPDATE_PROCEDURE) ||
                    (in->getCancellationType().value() == s6a::CancellationType::INITIAL_ATTACH_PROCEDURE)))
        {
            out->SetTypeOfUpdate(new TypeOfUpdate(TypeOfUpdate::TYPE_OF_UPDATE_MME_CHANGE));
        }
    }

}

void MAPToS6aHandler::IDR_To_InsertSubscriberDataArg(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataRequest *in,
        InsertSubscriberDataArg *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    uint8_t imsi[IWF_MAX_E164_SZ/2];
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);

    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));

    SetDestinationAddrinTcapDlg(ctxt, temp);

    if (in->getSubscriptionData().containsMSISDN())
    {
        map_v13::ISDN_AddressString isdn(IWFUtils::StringToVector(in->getSubscriptionData().getMSISDN().value()));
        out->SetMsisdn(isdn);
    }

    if (in->getSubscriptionData().containsSubscriberStatus())
    {
        out->SetSubscriberStatus(
                new SubscriberStatus(in->getSubscriptionData().getSubscriberStatus().value()));
    }

    s6a::SubscriptionData oSubsData = in->getSubscriptionData();

    if ( oSubsData.containsOperatorDeterminedBarring() ||
            oSubsData.containsHPLMNODB() )
    {
        ODB_Data ocMapOdbData;
        BuildOperatorDeterminedBarring(oSubsData, ocMapOdbData);
        out->SetOdb_Data(ocMapOdbData);
    }

    int iCount = oSubsData.countRegionalSubscriptionZoneCode();
    ZoneCodeList ocZoneCodeList;
    std::vector<byte> vecZoneCodeList;
    for(int iIndex = 0;iIndex < iCount; iIndex++)
    {
        s6a::RegionalSubscriptionZoneCode ocCode = oSubsData.getRegionalSubscriptionZoneCode(iIndex);
        vecZoneCodeList = IWFUtils::StringToVector(ocCode.value());
        ZoneCode ocZoneCode(vecZoneCodeList);
        ocZoneCodeList.AddElement(ocZoneCode);
    }

    if(iCount > 0)
        out->SetRegionalSubscriptionData(ocZoneCodeList);

    if (oSubsData.containsGPRSSubscriptionData())
    {
        std::vector<byte> vecGprsSubscrData;
        GPRSDataList ocGprsDataList;
        GPRSSubscriptionData ocGprsSubsData;
        BuildGPRSSubscriptionData(oSubsData.getGPRSSubscriptionData(), ocGprsDataList);
        ocGprsSubsData.SetGprsDataList(ocGprsDataList);

        if(oSubsData.containsAPNOIReplacement())
        {
            ocGprsSubsData.SetApn_oi_Replacement(map_v13::GPRSSubscriptionData::APN_OI_Replacement(IWFUtils::StringToVector(oSubsData.getAPNOIReplacement().value())));
        }

        out->SetGprsSubscriptionData(ocGprsSubsData);
    }

    if (oSubsData.containsNetworkAccessMode())
    {
        out->SetNetworkAccessMode(oSubsData.getNetworkAccessMode().value());
    }

    if(oSubsData.containsRoamingRestrictedDueToUnsupportedFeature())
    {
        out->SetRoamingRestrictedInSgsnDueToUnsupportedFeature(new map_v13::InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature);
    }


    if (oSubsData.containsS6a3GPPChargingCharacteristics())
    {
        out->SetChargingCharacteristics((IWFUtils::StringToVector(oSubsData.getS6a3GPPChargingCharacteristics().value())));

    }

    if (oSubsData.containsAccessRestrictionData())
    {
        out->SetAccessRestrictionData(IWFUtils::UnsignedToBitVector(oSubsData.getAccessRestrictionData().value(), 8));
    }

    if (oSubsData.containsLCSInfo())
    {
        LCSInformation ocLcsInfo;
        GMLC_List ocGmlcList;
        ISDN_AddressString strAddrString;

        s6a::LCSInfo oLcsInfo = oSubsData.getLCSInfo();

        for (int iIndex=0;iIndex<oLcsInfo.countGMLCNumber();iIndex++)
        {
            map_v13::ISDN_AddressString isdnaddr(IWFUtils::StringToVector(oLcsInfo.getGMLCNumber(iIndex).value()));
            ocGmlcList.AddElement(isdnaddr);
        }

        ocLcsInfo.SetGmlc_List(ocGmlcList);

        if (oLcsInfo.countLCSPrivacyException() > 0)

        {
            LCS_PrivacyExceptionList ocList;
            BuildLCS_PrivacyExceptionList(oLcsInfo, ocList);
            ocLcsInfo.SetLcs_PrivacyExceptionList(ocList);
        }

        if(oLcsInfo.countMOLR())
        {
            MOLR_List ocMapMolrList;

            for (int iIndex=0;iIndex<oLcsInfo.countMOLR();iIndex++)
            {
                MOLR_Class ocMapMolr;
                s6a::MOLR oMolr = oLcsInfo.getMOLR(iIndex);
                ocMapMolr.SetSs_Code(IWFUtils::StringToVector(oMolr.getSSCode().value()));
                ocMapMolr.SetSs_Status(IWFUtils::StringToVector(oMolr.getSSStatus().value()));
                ocMapMolrList.AddElement(ocMapMolr);
            }

            ocLcsInfo.SetMolr_List(ocMapMolrList);
        }
        out->SetLcsInformation(ocLcsInfo);
    }


    if(oSubsData.containsTeleserviceList())
    {
        TeleserviceList tsl;
        s6a::TeleserviceList tl = oSubsData.getTeleserviceList();
        for (int iIndex=0;iIndex<tl.countTSCode();iIndex++)
        {
            tsl.AddElement(IWFUtils::StringToVector(tl.getTSCode(iIndex).value()));
        }
        out->SetTeleserviceList(tsl);
    }

    if(oSubsData.containsSTNSR() ||
            oSubsData.containsAPNOIReplacement() ||
            oSubsData.containsAMBR() ||
            oSubsData.containsAPNConfigurationProfile() ||
            oSubsData.containsRATFrequencySelectionPriorityID())
    {
        BuildEPSSubscriptionData(in, out);
    }

    BuildCSGSubscriptionData(in, out);

    if(in->containsIDRFlags())
    {
        unsigned int idrFlags = in->getIDRFlags().value();
        if (idrFlags & IDR_FLAG_UE_REACH_REQ)//bit '0' is enabled or not in IDR Flags
        {
            map_v13::InsertSubscriberDataArg::Ue_ReachabilityRequestIndicator uereach;
            out->SetUe_ReachabilityRequestIndicator(uereach);
        }
    }
}

void MAPToS6aHandler::BuildOperatorDeterminedBarring(
        const s6a::SubscriptionData& oSubsData,
        ODB_Data &iOdb)
{
    ODB_GeneralData *ocMapOdbGenData = new ODB_GeneralData(IWFUtils::UnsignedToBitVector(0,32));
    ODB_HPLMN_Data ocMapOdbHplmnData;

    if (oSubsData.containsOperatorDeterminedBarring())
    {
        uint32_t odbVal = oSubsData.getOperatorDeterminedBarring().value();
        if( odbVal & (1<<0) )
        {
            ocMapOdbGenData->SetAllPacketOrientedServicesBarred();
        }
        else if( odbVal & (1<<1) )
        {
            ocMapOdbGenData->SetRoamerAccessToHPLMN_AP_Barred();
        }
        else if( odbVal & (1<<2) )
        {
            ocMapOdbGenData->SetRoamerAccessToVPLMN_AP_Barred();
        }
        else if( odbVal & (1<<3) )
        {
            ocMapOdbGenData->SetAllOG_CallsBarred();
        }
        else if( odbVal & (1<<4) )
        {
            ocMapOdbGenData->SetInternationalOGCallsBarred();
        }
        else if( odbVal & (1<<5) )
        {
            ocMapOdbGenData->SetInternationalOGCallsNotToHPLMN_CountryBarred();
        }
        else if( odbVal & (1<<6) )
        {
            ocMapOdbGenData->SetInterzonalOGCallsBarred();
        }
        else if( odbVal & (1<<7) )
        {
            ocMapOdbGenData->SetInterzonalOGCallsNotToHPLMN_CountryBarred();
        }
        else if( odbVal & (1<<8) )
        {
            ocMapOdbGenData->SetInterzonalOGCallsAndInternationalOGCallsNotToHPLMN_CountryBarred();
        }
        iOdb.SetOdb_GeneralData(ocMapOdbGenData);
    }

    if (oSubsData.containsHPLMNODB())
    {
        uint32_t ohplmndbVal = oSubsData.getHPLMNODB().value();
        iOdb.SetOdb_HPLMN_Data(new ODB_HPLMN_Data(IWFUtils::UnsignedToBitVector(ohplmndbVal, 4)));
    }

}

void MAPToS6aHandler::BuildGPRSSubscriptionData(
        const s6a::GPRSSubscriptionData in,
        GPRSDataList& out)
{
    for (int i = 0; i < in.countPDPContext(); i++)
    {
        map_v13::PDP_Context element[in.countPDPContext()];
        BuildPDPContext(in.getPDPContext(i), element[i]);
        out.AddElement(element[i]);
    }
}

void MAPToS6aHandler::BuildPDPContext(s6a::PDPContext in , PDP_Context& out)
{
    out.SetPdp_ContextId(in.getContextIdentifier().value());

    out.SetPdp_Type(new PDP_Type(IWFUtils::StringToVector(in.getPDPType().value())));

    if (in.containsPDPAddress())
    {
        const diameter::Address& iAddr = in.getPDPAddress().value();
        out.SetPdp_Address(new PDP_Address(
                    IWFUtils::StringToVector(iAddr.value)));
    }

    if(in.getQoSSubscribed().value().length() >= 3)
    {
        out.SetQos_Subscribed(
                new QoS_Subscribed(IWFUtils::StringToVector(in.getQoSSubscribed().value().substr(0,3))));
    }

    /*uint8_t ucQoSSubscribed[4] = {0};
    if (in.getQoSSubscribed().value().length() >= 3)
    {
        memcpy(ucQoSSubscribed, in.getQoSSubscribed().value().c_str(), 3);
    }
    else if (in.getQoSSubscribed().value().length())
    {
        memcpy(ucQoSSubscribed, in.getQoSSubscribed().value().c_str(), in.getQoSSubscribed().value().length());
    }*/

    /*out.SetQos_Subscribed(
            new QoS_Subscribed(IWFUtils::StringToVector((const char*)ucQoSSubscribed)));*/

    out.SetApn(new APN(IWFUtils::StringToVector(in.getServiceSelection().value())));


    if (in.containsVPLMNDynamicAddressAllowed())
    {
        /* NOTALLOWED - 0   ALLOWED - 1 */
        out.SetVplmnAddressAllowed(new PDP_Context::VplmnAddressAllowed());
    }

    if (in.containsS6a3GPPChargingCharacteristics())
    {
        out.SetPdp_ChargingCharacteristics(IWFUtils::StringToVector(in.getS6a3GPPChargingCharacteristics().value()));

    }

    /* ext-pdp-Type --> Ext-PDP-Type (2 bytes to Oct string) */
    if (in.containsExtPDPAddress())
    {
        out.SetExt_pdp_Type((IWFUtils::StringToVector(in.getExtPDPType().value())));
        const diameter::Address& iAddr = in.getExtPDPAddress().value();
        out.SetExt_pdp_Address(new PDP_Address(
                    IWFUtils::StringToVector(iAddr.value)));
    }

    if (in.containsAMBR())
    {
        AMBR iAmbr;

        iAmbr.SetMax_RequestedBandwidth_UL(in.getAMBR().getMaxRequestedBandwidthUL().value());
        iAmbr.SetMax_RequestedBandwidth_DL(in.getAMBR().getMaxRequestedBandwidthDL().value());

        out.SetAmbr(iAmbr);
    }

    if (in.containsSIPTOPermission())
    {
        out.SetSipto_Permission(in.getSIPTOPermission().value());
    }

    if (in.containsLIPAPermission())
    {
        out.SetLipa_Permission(in.getLIPAPermission().value());
    }
}


void MAPToS6aHandler::BuildLCS_PrivacyExceptionList(s6a::LCSInfo in, LCS_PrivacyExceptionList& out)
{
    SS_Code osSSCode;
    Ext_SS_Status ocExtSSStatus;
    NotificationToMSUser ocNtfToMsUser;
    ExternalClientList ocExtCliList;
    PLMNClientList ocPlmnCliList;
    Ext_ExternalClientList ocExtExCliList;
    ServiceTypeList ocSvcTypeList;

    for (int iIndex=0;iIndex<in.countLCSPrivacyException();iIndex++)
    {
        s6a::LCSPrivacyException ocPrvExp = in.getLCSPrivacyException(iIndex);
        LCS_PrivacyClass ocLcsPrvClass;

        ocLcsPrvClass.SetSs_Code(IWFUtils::StringToVector(ocPrvExp.getSSCode().value()));
        ocLcsPrvClass.SetSs_Status(IWFUtils::StringToVector(ocPrvExp.getSSStatus().value()));

        if (ocPrvExp.containsNotificationToUEUser())
        {
            ocLcsPrvClass.SetNotificationToMSUser(ocPrvExp.getNotificationToUEUser().value());
        }

        if(ocPrvExp.countExternalClient())
        {
            ExternalClientList ocExtCliList;
            for (int iCliCount=0; iCliCount<ocPrvExp.countExternalClient(); iCliCount++)
            {
                s6a::ExternalClient ocDiaExtClient = ocPrvExp.getExternalClient(iCliCount);
                ExternalClient ocExtCli;
                LCSClientExternalID ocLcsCliExtId;
                ocLcsCliExtId.SetExternalAddress(new ISDN_AddressString(IWFUtils::StringToVector(ocDiaExtClient.getClientIdentity().value())));
                ocExtCli.SetClientIdentity(ocLcsCliExtId);
                ocExtCli.SetGmlc_Restriction(ocDiaExtClient.getGMLCRestriction().value());
                ocExtCli.SetNotificationToMSUser(ocDiaExtClient.getNotificationToUEUser().value());
                ocExtCliList.AddElement(ocExtCli);
            }
            ocLcsPrvClass.SetExternalClientList(ocExtCliList);
        }

        if(ocPrvExp.countPLMNClient())
        {
            PLMNClientList plmnclientList;
            for (int iCliCount=0; iCliCount<ocPrvExp.countPLMNClient(); iCliCount++)
            {
                map_v13::LCSClientInternalID lcsclientId(ocPrvExp.getPLMNClient(iCliCount).value());
                plmnclientList.AddElement(lcsclientId);
            }
            ocLcsPrvClass.SetPlmnClientList(plmnclientList);
        }

        if(ocPrvExp.countServiceType())
        {
            ServiceTypeList typelist;
            for (int iCliCount=0; iCliCount<ocPrvExp.countServiceType(); iCliCount++)
            {
                s6a::ServiceType srvctype = ocPrvExp.getServiceType(iCliCount);
                ServiceType servicetype;
                servicetype.SetServiceTypeIdentity(map_v13::LCSServiceTypeID(srvctype.getServiceTypeIdentity().value()));

                if(srvctype.containsGMLCRestriction())
                    servicetype.SetGmlc_Restriction(map_v13::GMLC_Restriction(srvctype.getGMLCRestriction().value()));

                if(srvctype.containsNotificationToUEUser())
                    servicetype.SetNotificationToMSUser(map_v13::NotificationToMSUser(srvctype.getNotificationToUEUser().value()));

                typelist.AddElement(servicetype);
            }
            ocLcsPrvClass.SetServiceTypeList(typelist);
        }
        out.AddElement(ocLcsPrvClass);
    }
}

void MAPToS6aHandler::BuildEPSSubscriptionData(const s6a::InsertSubscriberDataRequest *in,
        InsertSubscriberDataArg *out)
{

    s6a::SubscriptionData ocSubscrData = in->getSubscriptionData();
    EPS_SubscriptionData ocMapEpsSubscrData;

    if (ocSubscrData.containsSTNSR())
    {
        map_v13::ISDN_AddressString isdn(IWFUtils::StringToVector(ocSubscrData.getSTNSR().value()));
        ocMapEpsSubscrData.SetStn_sr(isdn);
    }

    if (ocSubscrData.containsAPNOIReplacement())
    {
        ocMapEpsSubscrData.SetApn_oi_Replacement(IWFUtils::StringToVector(ocSubscrData.getAPNOIReplacement().value()));
    }

    if (ocSubscrData.containsAMBR())
    {
        AMBR iAmbr;

        iAmbr.SetMax_RequestedBandwidth_UL(ocSubscrData.getAMBR().getMaxRequestedBandwidthUL().value());
        iAmbr.SetMax_RequestedBandwidth_DL(ocSubscrData.getAMBR().getMaxRequestedBandwidthDL().value());

        ocMapEpsSubscrData.SetAmbr(iAmbr);
    }

    if (ocSubscrData.containsAPNConfigurationProfile())
    {
        s6a::APNConfigurationProfile oAcp = ocSubscrData.getAPNConfigurationProfile();
        APN_ConfigurationProfile ocMapApnConfigurationProfile;
        BuildAPNConfigurationProfile(
                oAcp, ocMapApnConfigurationProfile);
        ocMapEpsSubscrData.SetApn_ConfigurationProfile(ocMapApnConfigurationProfile);
    }

    if (ocSubscrData.containsRATFrequencySelectionPriorityID())
    {
        ocMapEpsSubscrData.SetRfsp_id(ocSubscrData.getRATFrequencySelectionPriorityID().value());

    }
    out->SetEps_SubscriptionData(ocMapEpsSubscrData);
}

void MAPToS6aHandler::BuildEPSSubscriptionData(const s6a::UpdateLocationAnswer *in,
        InsertSubscriberDataArg *out)
{

    s6a::SubscriptionData ocSubscrData = in->getSubscriptionData();
    EPS_SubscriptionData ocMapEpsSubscrData;

    if (ocSubscrData.containsSTNSR())
    {
        ocMapEpsSubscrData.SetStn_sr(new ISDN_AddressString(IWFUtils::StringToVector(ocSubscrData.getSTNSR().value())));
    }

    if (ocSubscrData.containsAPNOIReplacement())
    {
        ocMapEpsSubscrData.SetApn_oi_Replacement(IWFUtils::StringToVector(ocSubscrData.getAPNOIReplacement().value()));
    }

    if (ocSubscrData.containsAMBR())
    {
        AMBR iAmbr;

        iAmbr.SetMax_RequestedBandwidth_UL(ocSubscrData.getAMBR().getMaxRequestedBandwidthUL().value());
        iAmbr.SetMax_RequestedBandwidth_DL(ocSubscrData.getAMBR().getMaxRequestedBandwidthDL().value());

        ocMapEpsSubscrData.SetAmbr(iAmbr);
    }

    if (ocSubscrData.containsAPNConfigurationProfile())
    {
        s6a::APNConfigurationProfile oAcp = ocSubscrData.getAPNConfigurationProfile();
        APN_ConfigurationProfile ocMapApnConfigurationProfile;
        BuildAPNConfigurationProfile(
                oAcp, ocMapApnConfigurationProfile);
        ocMapEpsSubscrData.SetApn_ConfigurationProfile(ocMapApnConfigurationProfile);
    }

    if (ocSubscrData.containsRATFrequencySelectionPriorityID())
    {
        ocMapEpsSubscrData.SetRfsp_id(ocSubscrData.getRATFrequencySelectionPriorityID().value());

    }
    out->SetEps_SubscriptionData(ocMapEpsSubscrData);
}

void MAPToS6aHandler::BuildAPNConfigurationProfile(s6a::APNConfigurationProfile in,
        APN_ConfigurationProfile& out)
{
    out.SetDefaultContext(in.getContextIdentifier().value());
    out.SetCompleteDataListIncluded(new map_v13::APN_ConfigurationProfile::CompleteDataListIncluded);

    if(in.countAPNConfiguration())
    {
        EPS_DataList ocMapEpsDataList;
        for(int iIndex = 0;iIndex<in.countAPNConfiguration();iIndex++)
        {
            APN_Configuration ocMapApnConfig;
            s6a::APNConfiguration ocApnConfig = in.getAPNConfiguration(iIndex);;
            BuildAPNConfiguration(ocApnConfig, ocMapApnConfig);
            ocMapEpsDataList.AddElement(ocMapApnConfig);
        }
        out.SetEpsDataList(ocMapEpsDataList);
    }

}

void MAPToS6aHandler::BuildAPNConfiguration( s6a::APNConfiguration in, APN_Configuration& out)
{
    out.SetContextId(in.getContextIdentifier().value());
    PDN_Type ocMapPdnType;
    unsigned char ucPdnType = (unsigned char)in.getPDNType().value();
    std::vector<byte> vecPdnType;
    vecPdnType.push_back(ucPdnType);
    out.SetPdn_Type(new PDN_Type(vecPdnType));

    if(in.countServedPartyIPAddress())
    {
        const diameter::Address& iAddr = in.getServedPartyIPAddress(0).value();
        out.SetServedPartyIP_IPv4_Address(new PDP_Address(
                    IWFUtils::StringToVector(iAddr.value)));
    }

    out.SetApn(new APN(IWFUtils::StringToVector(in.getServiceSelection().value())));

    if(in.containsEPSSubscribedQoSProfile())
    {
        s6a::EPSSubscribedQoSProfile ocEpsSubsQosProf = in.getEPSSubscribedQoSProfile();
        EPS_QoS_Subscribed ocMapEpsQosProf;
        ocMapEpsQosProf.SetQos_Class_Identifier(ocEpsSubsQosProf.getQoSClassIdentifier().value());

        Allocation_Retention_Priority ocAlocRetPri;
        ocAlocRetPri.SetPriority_level(ocEpsSubsQosProf.getAllocationRetentionPriority().getPriorityLevel().value());

        if (ocEpsSubsQosProf.getAllocationRetentionPriority().containsPreemptionCapability())
        {
            ocAlocRetPri.SetPre_emption_capability(ocEpsSubsQosProf.getAllocationRetentionPriority().getPreemptionCapability().value());
        }

        if (ocEpsSubsQosProf.getAllocationRetentionPriority().containsPreemptionVulnerability())
        {
            ocAlocRetPri.SetPre_emption_vulnerability(ocEpsSubsQosProf.getAllocationRetentionPriority().getPreemptionVulnerability().value());
        }

        ocMapEpsQosProf.SetAllocation_Retention_Priority(ocAlocRetPri);

        out.SetEps_qos_Subscribed(ocMapEpsQosProf);
    }

    if (in.containsVisitedNetworkIdentifier())
    {
        PDN_GW_Identity ocMapPdnGwIdent;
        //ocMapPdnGwIdent.SetPdn_gw_ipv4_Address();
        //ocMapPdnGwIdent.SetPdn_gw_ipv6_Address();
        ocMapPdnGwIdent.SetPdn_gw_name(new FQDN(IWFUtils::StringToVector(in.getVisitedNetworkIdentifier().value())));
        out.SetPdn_gw_Identity(ocMapPdnGwIdent);
    }


    if(in.containsPDNGWAllocationType())
    {
        out.SetPdn_gw_AllocationType(new PDN_GW_AllocationType(in.getPDNGWAllocationType().value()));
    }

    if(in.containsPDNGWAllocationType())
        out.SetVplmnAddressAllowed(new APN_Configuration::VplmnAddressAllowed);

    if (in.containsS6a3GPPChargingCharacteristics())
    {
        out.SetChargingCharacteristics((IWFUtils::StringToVector(in.getS6a3GPPChargingCharacteristics().value())));

    }

    if (in.containsAMBR())
    {
        AMBR iAmbr;

        iAmbr.SetMax_RequestedBandwidth_UL(in.getAMBR().getMaxRequestedBandwidthUL().value());
        iAmbr.SetMax_RequestedBandwidth_DL(in.getAMBR().getMaxRequestedBandwidthDL().value());

        out.SetAmbr(iAmbr);
    }


    if(in.countSpecificAPNInfo() > 0)
    {
        SpecificAPNInfoList iList;
        for (int iIndex=0;iIndex<in.countSpecificAPNInfo();iIndex++)
        {
            s6a::SpecificAPNInfo osApnInfo = in.getSpecificAPNInfo(iIndex);
            SpecificAPNInfo ocMapApnInfo;
            if (osApnInfo.containsVisitedNetworkIdentifier())
            {
                PDN_GW_Identity ocMapPdnGwIdent;
                //ocMapPdnGwIdent.SetPdn_gw_ipv4_Address();
                //ocMapPdnGwIdent.SetPdn_gw_ipv6_Address();
                ocMapPdnGwIdent.SetPdn_gw_name(new FQDN(IWFUtils::StringToVector(osApnInfo.getVisitedNetworkIdentifier().value())));
                ocMapApnInfo.SetPdn_gw_Identity(ocMapPdnGwIdent);
            }

            ocMapApnInfo.SetApn(new APN(IWFUtils::StringToVector(osApnInfo.getServiceSelection().value())));
            iList.AddElement(ocMapApnInfo);

        }
        out.SetSpecificAPNInfoList(iList);
    }

    if(in.containsAPNOIReplacement())
    {
        out.SetApn_oi_Replacement(map_v13::APN_Configuration::APN_OI_Replacement(IWFUtils::StringToVector(in.getAPNOIReplacement().value())));
    }

    if(in.containsSIPTOPermission())
    {
        int val = in.getSIPTOPermission().value();
        out.SetSipto_Permission(map_v13::APN_Configuration::SIPTO_Permission(val));
    }

    if(in.containsLIPAPermission())
    {
        int val = in.getLIPAPermission().value();
        out.SetLipa_Permission(map_v13::APN_Configuration::LIPA_Permission(val));
    }
}


void MAPToS6aHandler::BuildCSGSubscriptionData(const s6a::InsertSubscriberDataRequest *in,
        InsertSubscriberDataArg *out)
{
    s6a::SubscriptionData ocSubscrData = in->getSubscriptionData();
    CSG_SubscriptionDataList ocMapList;
    for (int iIndex=0; iIndex < ocSubscrData.countCSGSubscriptionData(); iIndex++)
    {
        CSG_SubscriptionData ocMapCsgSubData;
        LIPA_AllowedAPNList ocApnList;

        s6a::CSGSubscriptionData ocCsgSubData = ocSubscrData.getCSGSubscriptionData(iIndex);
        ocMapCsgSubData.SetCsg_Id(new CSG_Id(IWFUtils::UnsignedToBitVector(ocCsgSubData.getCSGId().value(), 27)));
        if(ocCsgSubData.containsExpirationDate())
        {
            //const void *value = static_cast<const void *>(&ocCsgSubData.getExpirationDate().value());
            //const byte *tarrp = static_cast<const byte *>(value);
            //std::vector<byte> tarr(tarrp, tarrp + sizeof(unsigned int));
            map_v13::Time mtime(IWFUtils::UnsignedToBytes((ocCsgSubData.getExpirationDate().value(), 4)));
            ocMapCsgSubData.SetExpirationDate(mtime);
        }

        for (int iSvcCount=0; iSvcCount< ocCsgSubData.countServiceSelection();iSvcCount++)
        {
            map_v13::APN apn(IWFUtils::StringToVector(ocCsgSubData.getServiceSelection(iSvcCount).value()));
            ocApnList.AddElement(apn);
        }

        if (ocCsgSubData.countServiceSelection() > 0)
            ocMapCsgSubData.SetLipa_AllowedAPNList(ocApnList);

        ocMapList.AddElement(ocMapCsgSubData);
    }

    if (ocSubscrData.countCSGSubscriptionData() > 0)
        out->SetCsg_SubscriptionDataList(ocMapList);

}

void MAPToS6aHandler::BuildCSGSubscriptionData(const s6a::UpdateLocationAnswer *in,
        InsertSubscriberDataArg *out)
{
    s6a::SubscriptionData ocSubscrData = in->getSubscriptionData();
    CSG_SubscriptionDataList ocMapList;
    for (int iIndex=0; iIndex < ocSubscrData.countCSGSubscriptionData(); iIndex++)
    {
        CSG_SubscriptionData ocMapCsgSubData;
        LIPA_AllowedAPNList ocApnList;

        s6a::CSGSubscriptionData ocCsgSubData = ocSubscrData.getCSGSubscriptionData(iIndex);
        ocMapCsgSubData.SetCsg_Id(new CSG_Id(IWFUtils::UnsignedToBitVector(ocCsgSubData.getCSGId().value(), 27)));
        if(ocCsgSubData.containsExpirationDate())
        {
            /*const void *value = static_cast<const void *>(&ocCsgSubData.getExpirationDate().value());
            const byte *tarrp = static_cast<const byte *>(value);
            std::vector<byte> tarr(tarrp, tarrp + sizeof(unsigned int));*/
            map_v13::Time mtime(IWFUtils::UnsignedToBytes((ocCsgSubData.getExpirationDate().value(), 4)));
            ocMapCsgSubData.SetExpirationDate(mtime);
        }

        for (int iSvcCount=0; iSvcCount< ocCsgSubData.countServiceSelection();iSvcCount++)
        {
            map_v13::APN apn(IWFUtils::StringToVector(ocCsgSubData.getServiceSelection(iSvcCount).value()));
            ocApnList.AddElement(apn);
        }

        if (ocCsgSubData.countServiceSelection() > 0)
            ocMapCsgSubData.SetLipa_AllowedAPNList(ocApnList);

        ocMapList.AddElement(ocMapCsgSubData);
    }

    if (ocSubscrData.countCSGSubscriptionData() > 0)
        out->SetCsg_SubscriptionDataList(ocMapList);

}

void MAPToS6aHandler::SubscriptionData_To_InsertSubscriberDataArg(IwfFsm *ctxt,
        const s6a::UpdateLocationAnswer *in,
        InsertSubscriberDataArg *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    if (in->getSubscriptionData().containsMSISDN())
    {
        std::string smsisdn = in->getSubscriptionData().getMSISDN().value();
        out->SetMsisdn(new ISDN_AddressString(IWFUtils::StringToVector(smsisdn)));
    }

    if (in->getSubscriptionData().containsSubscriberStatus())
    {
        out->SetSubscriberStatus(
                new SubscriberStatus(in->getSubscriptionData().getSubscriberStatus().value()));
    }

    s6a::SubscriptionData oSubsData = in->getSubscriptionData();

    if ( oSubsData.containsOperatorDeterminedBarring() ||
            oSubsData.containsHPLMNODB() )
    {
        ODB_Data ocMapOdbData;
        BuildOperatorDeterminedBarring(oSubsData, ocMapOdbData);
        out->SetOdb_Data(ocMapOdbData);
    }

    int iCount = oSubsData.countRegionalSubscriptionZoneCode();
    ZoneCodeList ocZoneCodeList;
    std::vector<byte> vecZoneCodeList;
    for(int iIndex = 0;iIndex < iCount; iIndex++)
    {
        s6a::RegionalSubscriptionZoneCode ocCode = oSubsData.getRegionalSubscriptionZoneCode(iIndex);
        vecZoneCodeList = IWFUtils::StringToVector(ocCode.value());
        ZoneCode ocZoneCode(vecZoneCodeList);
        ocZoneCodeList.AddElement(ocZoneCode);
    }

    if(iCount > 0)
        out->SetRegionalSubscriptionData(ocZoneCodeList);

    if (oSubsData.containsGPRSSubscriptionData())
    {
        std::vector<byte> vecGprsSubscrData;
        GPRSDataList ocGprsDataList;
        GPRSSubscriptionData ocGprsSubsData;
        BuildGPRSSubscriptionData(oSubsData.getGPRSSubscriptionData(), ocGprsDataList);
        ocGprsSubsData.SetGprsDataList(ocGprsDataList);

        if(oSubsData.containsAPNOIReplacement())
        {
            ocGprsSubsData.SetApn_oi_Replacement(map_v13::GPRSSubscriptionData::APN_OI_Replacement(IWFUtils::StringToVector(oSubsData.getAPNOIReplacement().value())));
        }

        out->SetGprsSubscriptionData(ocGprsSubsData);
    }

    if(oSubsData.containsRoamingRestrictedDueToUnsupportedFeature())
    {
        map_v13::InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature rrisgsn;
        out->SetRoamingRestrictedInSgsnDueToUnsupportedFeature(rrisgsn);
    }

    if (oSubsData.containsNetworkAccessMode())
    {
        out->SetNetworkAccessMode(oSubsData.getNetworkAccessMode().value());
    }


    if (oSubsData.containsS6a3GPPChargingCharacteristics())
    {
        out->SetChargingCharacteristics((IWFUtils::StringToVector(oSubsData.getS6a3GPPChargingCharacteristics().value())));

    }

    if (oSubsData.containsAccessRestrictionData())
    {
        out->SetAccessRestrictionData(IWFUtils::UnsignedToBitVector(oSubsData.getAccessRestrictionData().value(), 8));
    }

    if (oSubsData.containsLCSInfo())
    {
        LCSInformation ocLcsInfo;
        GMLC_List ocGmlcList;
        ISDN_AddressString strAddrString;

        s6a::LCSInfo oLcsInfo = oSubsData.getLCSInfo();;

        for (int iIndex=0;iIndex<oLcsInfo.countGMLCNumber();iIndex++)
        {
            map_v13::ISDN_AddressString isdnaddr(IWFUtils::StringToVector(oLcsInfo.getGMLCNumber(iIndex).value()));
            ocGmlcList.AddElement(isdnaddr);
        }

        ocLcsInfo.SetGmlc_List(ocGmlcList);

        if (oLcsInfo.countLCSPrivacyException() > 0)

        {
            LCS_PrivacyExceptionList ocList;
            BuildLCS_PrivacyExceptionList(oLcsInfo, ocList);
            ocLcsInfo.SetLcs_PrivacyExceptionList(ocList);
        }

        if(oLcsInfo.countMOLR())
        {
            MOLR_List ocMapMolrList;

            for (int iIndex=0;iIndex<oLcsInfo.countMOLR();iIndex++)
            {
                MOLR_Class ocMapMolr;
                s6a::MOLR oMolr = oLcsInfo.getMOLR(iIndex);
                ocMapMolr.SetSs_Code(IWFUtils::StringToVector(oMolr.getSSCode().value()));
                ocMapMolr.SetSs_Status(IWFUtils::StringToVector(oMolr.getSSStatus().value()));
                ocMapMolrList.AddElement(ocMapMolr);
            }

            ocLcsInfo.SetMolr_List(ocMapMolrList);
        }
        out->SetLcsInformation(ocLcsInfo);
    }

    if(oSubsData.containsTeleserviceList())
    {
        TeleserviceList tsl;
        s6a::TeleserviceList tl = oSubsData.getTeleserviceList();
        for (int iIndex=0;iIndex<tl.countTSCode();iIndex++)
        {
            Ext_TeleserviceCode extTsl(IWFUtils::StringToVector(tl.getTSCode(iIndex).value()));
            tsl.AddElement(extTsl);
        }
        out->SetTeleserviceList(tsl);
    }

    if(oSubsData.containsSTNSR() ||
            oSubsData.containsAPNOIReplacement() ||
            oSubsData.containsAMBR() ||
            oSubsData.containsAPNConfigurationProfile() ||
            oSubsData.containsRATFrequencySelectionPriorityID())
    {
        BuildEPSSubscriptionData(in, out);
    }

    BuildCSGSubscriptionData(in, out);
}

void MAPToS6aHandler::ReadyForSMArg_To_NOR(IwfFsm *ctxt,
        const ReadyForSM_Arg *in,
        s6a::NotifyRequest *out)
{
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    std::string oImsi;
    const std::vector<byte>& vec = in->GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }
    out->setUserName(diameter::base::UserName(oImsi));

    /* Alert-Reason AVP shall be present */
    uint32_t val = in->GetAlertReason().GetValue();
    if(val == 0)
        out->setAlertReason(s6a::AlertReason(s6a::AlertReason::UE_PRESENT));
    else if(val == 1)
        out->setAlertReason(s6a::AlertReason(s6a::AlertReason::UE_MEMORY_AVAILABLE));

    ITS_UINT norFlags = 0x00;
    norFlags |= NOR_FLAG_READY_FOR_SM_FROM_SGSN;
    s6a::NORFlags nor(norFlags);
    out->setNORFlags(nor);
}

void MAPToS6aHandler::UpdateGprsLocationArg_To_NOR(IwfFsm *ctxt,
        const UpdateGprsLocationArg *in,
        s6a::NotifyRequest *out)
{
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    std::string oImsi;
    const std::vector<byte>& vec = in->GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }
    out->setUserName(diameter::base::UserName(oImsi));

    UpdateSessionCtxt(ctxt, oImsi);

    if(in->OptionAdd_info())
    {
        const ADD_Info &addinfo = in->GetAdd_info();
        s6a::TerminalInformation ti;
        std::string Imeisv;
        std::string svn;
        const std::vector<byte>& vec = addinfo.GetImeisv().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), Imeisv);

        std::string imei = Imeisv.substr(0, 14);
        char strCheckdigit[2] = {0};
        sprintf(strCheckdigit, "%d", GetCheckDigitForIMEI(imei));
        imei.append(strCheckdigit);
        ti.setIMEI(s6a::IMEI(imei));

        svn = Imeisv.substr(14,2);
        int i = atoi(svn.c_str());
        if(i > 0)
        {
            ti.setSoftwareVersion(s6a::SoftwareVersion(Imeisv.substr(14,2)));
        }
        out->setTerminalInformation(ti);
    }

    if(in->OptionEps_info())
    {
        map_v13::EPS_Info epsinfo = in->GetEps_info();
        if(epsinfo.ChoicePdn_gw_update())
        {
            s6a::MIP6AgentInfo mipai;
            map_v13::PDN_GW_Update pdngwupdate = epsinfo.GetChoicePdn_gw_update();
            if(pdngwupdate.OptionPdn_gw_Identity())
            {
                map_v13::PDN_GW_Identity pdngwid = pdngwupdate.GetPdn_gw_Identity();
                if(pdngwid.OptionPdn_gw_ipv4_Address())
                {
                    std::string oStr;
                    const uint8_t *iPdpAddr = &(pdngwid.GetPdn_gw_ipv4_Address().GetArray()[0]);
                    int len = pdngwid.GetPdn_gw_ipv4_Address().GetArray().size();

                    mipai.addMIPHomeAgentAddress(s6a::MIPHomeAgentAddress(diameter::Address(diameter::Address::IPV4, (const char*)iPdpAddr, len)));
                }

                if(pdngwid.OptionPdn_gw_ipv6_Address())
                {
                    std::string oStr;
                    const uint8_t *iPdpAddr = &(pdngwid.GetPdn_gw_ipv6_Address().GetArray()[0]);
                    int len = pdngwid.GetPdn_gw_ipv6_Address().GetArray().size();

                    mipai.addMIPHomeAgentAddress(s6a::MIPHomeAgentAddress(diameter::Address(diameter::Address::IPV6, (const char*)iPdpAddr, len)));
                }
                if(pdngwid.OptionPdn_gw_name())
                {
                    s6a::MIPHomeAgentHost mipah;
                    mipah.setDestinationHost(diameter::base::DestinationHost(IWFUtils::VectorToString(pdngwid.GetPdn_gw_name().GetArray())));
                    mipah.setDestinationRealm(diameter::base::DestinationRealm(itsDiaConfig.getLocalRealmName()));
                    mipai.setMIPHomeAgentHost(mipah);
                }

                out->setMIP6AgentInfo(mipai);

                if(pdngwupdate.OptionApn())
                {
                    s6a::ServiceSelection ss(IWFUtils::VectorToString(pdngwupdate.GetApn().GetArray()));
                    out->setServiceSelection(ss);
                }

                if(pdngwupdate.OptionContextId())
                {
                    s6a::ContextIdentifier ci(pdngwupdate.GetContextId().GetValue());
                    out->setContextIdentifier(ci);
                }

            }
        }
    }

    if(in->OptionUe_srvcc_Capability())
    {
        if(in->GetUe_srvcc_Capability().IsUe_srvcc_not_supported())
            out->setUESRVCCCapability(s6a::UESRVCCCapability(s6a::UESRVCCCapability::UE_SRVCC_NOT_SUPPORTED));
        if(in->GetUe_srvcc_Capability().IsUe_srvcc_supported())
            out->setUESRVCCCapability(s6a::UESRVCCCapability(s6a::UESRVCCCapability::UE_SRVCC_SUPPORTED));
    }

    ITS_UINT norFlags = 0x00;
    if(in->OptionEps_info() && in->GetEps_info().ChoiceIsr_Information() && in->GetEps_info().GetChoiceIsr_Information().IsCancelSGSNSet())
    {
        norFlags |= NOR_FLAG_SINGLE_REGISTRATION_IND;
    }
    if(in->OptionAreaRestricted())
    {
        norFlags |= NOR_FLAG_SGSN_AREA_RESTRICTED;
    }
    if(in->OptionUe_reachableIndicator())
    {
        //norFlags |= UE_Reachable_From_MME;
        norFlags |= NOR_FLAG_UE_REACHABLE_FROM_SGSN;
    }
    s6a::NORFlags nor(norFlags);
    out->setNORFlags(nor);

}

void MAPToS6aHandler::IDR_To_ActivateTraceModeArg(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataRequest *in,
        ActivateTraceModeArg *out)
{
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to imsi
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));
    SetDestinationAddrinTcapDlg(ctxt, temp);

    s6a::SubscriptionData sd = in->getSubscriptionData();

    if(sd.containsTraceData())
    {
        s6a::TraceData td = sd.getTraceData();
        s6a::TraceReference tr = td.getTraceReference();

        std::string tref = (td.getTraceReference().value());
        if(tref.length() >= 6)
        {
            if(tref.length() > 3)
            {
                /* Extracting the 5 and 6 Octet of incoming diameter trace reference
                 * and populating in tracereference IE in MAP side */
                out->SetTraceReference(IWFUtils::StringToVector(tref.substr(4, 2)));
            }
            /* Extracting First 3 Octets of incoming diameter trace reference
             * and populating in tracereference IE in MAP side */
            out->SetTraceReference2(IWFUtils::StringToVector(tref.substr(0, 3)));
        }

        //TraceType shall be present with any value.
        out->SetTraceType(1000);

        //TraceNETypeList - > Trace-NE-Type-List AVP
        vector<byte> traceNETypeVector = IWFUtils::StringToVector((td.getTraceNETypeList().value()));
        unsigned int traceNEType = (((uint16_t)traceNETypeVector[1]) << 8 | traceNETypeVector[0]);
        map_v13::TraceNE_TypeList trnetl(IWFUtils::UnsignedToBitVector(traceNEType, 10));
        out->SetTraceNE_TypeList(trnetl);

        //TraceInterfaceList -> TraceInterfaceList AVP
        if(td.containsTraceInterfaceList())
        {
            map_v13::TraceInterfaceList tril;
            std::string trList = td.getTraceInterfaceList().value();
            BuildTraceInterfaceList(trList, &tril);
            out->SetTraceInterfaceList(tril);
        }

        s6a::TraceDepth tracedepth = td.getTraceDepth();
        BuildTraceDepthList(tracedepth, out);

        map_v13::TraceEventList trel;
        std::string trEvntList = td.getTraceEventList().value();
        BuildTraceEventList(trEvntList, &trel);
        out->SetTraceEventList(trel);

        if(td.containsOMCId())
        {
            std::string omcid = td.getOMCId().value();
            if(omcid.length() > 1)
            {
                out->SetOmc_Id(IWFUtils::StringToVector(omcid));
            }
        }

        const diameter::Address& iAddress = td.getTraceCollectionEntity().value();
        std::stringstream addr;
        int len = iAddress.value.length();
        if(len >0)
        {
            addr<<((int)(unsigned char)iAddress.value.at(0));
            for(int i=1; i<len; ++i)
            {
                addr<<".";
                addr<<((int)(unsigned char)iAddress.value.at(i));
            }
            std::string gsn = addr.str();
            cout<<"gsn = " <<gsn<<endl;
            its::ByteArray gsnAddress;
            IWFUtils::IpStringToGSNAddress(gsn,gsnAddress);
            out->SetTraceCollectionEntity(new GSN_Address(gsnAddress));
        }
    }
}

void MAPToS6aHandler::TraceData_To_ActivateTraceModeArg(IwfFsm *ctxt,
        const s6a::UpdateLocationAnswer *in,
        ActivateTraceModeArg *out)
{

#if 0
    // UserName to imsi
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));
    SetDestinationAddrinTcapDlg(ctxt, temp);
#endif

    s6a::SubscriptionData sd = in->getSubscriptionData();

    if(sd.containsTraceData())
    {
        s6a::TraceData td = sd.getTraceData();
        s6a::TraceReference tr = td.getTraceReference();

        std::string tref = (td.getTraceReference().value());
        if(tref.length() >= 6)
        {
            if(tref.length() > 3)
            {
                /* Extracting the 5 and 6 Octet of incoming diameter trace reference
                 * and populating in tracereference IE in MAP side */
                out->SetTraceReference(IWFUtils::StringToVector(tref.substr(4, 2)));
            }
            /* Extracting First 3 Octets of incoming diameter trace reference
             * and populating in tracereference IE in MAP side */
            out->SetTraceReference2(IWFUtils::StringToVector(tref.substr(0, 3)));
        }

        //TraceType shall be present with any value.
        out->SetTraceType(1000);

        //TraceNETypeList - > Trace-NE-Type-List AVP
        vector<byte> traceNETypeVector = IWFUtils::StringToVector((td.getTraceNETypeList().value()));
        unsigned int traceNEType = (((uint16_t)traceNETypeVector[1]) << 8 | traceNETypeVector[0]);
        map_v13::TraceNE_TypeList trnetl(IWFUtils::UnsignedToBitVector(traceNEType, 10));
        out->SetTraceNE_TypeList(trnetl);

        //TraceInterfaceList -> TraceInterfaceList AVP
        if(td.containsTraceInterfaceList())
        {
            map_v13::TraceInterfaceList tril;
            std::string trList = td.getTraceInterfaceList().value();
            BuildTraceInterfaceList(trList, &tril);
            out->SetTraceInterfaceList(tril);
        }

        s6a::TraceDepth tracedepth = td.getTraceDepth();
        BuildTraceDepthList(tracedepth, out);

        map_v13::TraceEventList trel;
        std::string trEvntList = td.getTraceEventList().value();
        BuildTraceEventList(trEvntList, &trel);
        out->SetTraceEventList(trel);

        if(td.containsOMCId())
        {
            std::string omcid = td.getOMCId().value();
            if(omcid.length() > 1)
            {
                out->SetOmc_Id(IWFUtils::StringToVector(omcid));
            }
        }

        const diameter::Address& iAddress = td.getTraceCollectionEntity().value();
        std::stringstream addr;
        int len = iAddress.value.length();
        if(len >0)
        {
            addr<<((int)(unsigned char)iAddress.value.at(0));
            for(int i=1; i<len; ++i)
            {
                addr<<".";
                addr<<((int)(unsigned char)iAddress.value.at(i));
            }
            std::string gsn = addr.str();
            cout<<"gsn = " <<gsn<<endl;
            its::ByteArray gsnAddress;
            IWFUtils::IpStringToGSNAddress(gsn,gsnAddress);
            out->SetTraceCollectionEntity(new GSN_Address(gsnAddress));
        }

        if(td.containsMDTConfiguration())
        {
            map_v13::MDT_Configuration mdtCfg;
            s6a::MDTConfiguration mdtConfig = td.getMDTConfiguration();
            BuildMDTConfiguration(mdtConfig, mdtCfg);
            out->SetMdt_Configuration(mdtCfg);
        }
    }
}

void MAPToS6aHandler::ActivateTraceModeRes_To_IDA(
        IwfFsm *ctxt,
        const ActivateTraceModeRes *in,
        s6a::InsertSubscriberDataAnswer *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);

    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}

void MAPToS6aHandler::DSR_To_DeactivateTraceModeArg(
        IwfFsm *ctxt,
        const s6a::DeleteSubscriberDataRequest *in,
        DeactivateTraceModeArg *out)
{
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    /*   set IMSI from User-Name AVP */
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    std::string temp(simsi.substr(0, simsi.find('@')));
    SetDestinationAddrinTcapDlg(ctxt, temp);

    if( in->containsTraceReference() )
    {
        std::string tref = (in->getTraceReference().value());
        if(tref.length() >= 6)
        {
            if(tref.length() > 3)
            {
                /* Extracting the 5 and 6 Octet of incoming diameter trace reference
                 * and populating in tracereference IE in MAP side */
                out->SetTraceReference(IWFUtils::StringToVector(tref.substr(4, 2)));
            }
            /* Extracting First 3 Octets of incoming diameter trace reference
             * and populating in tracereference IE in MAP side */
            out->SetTraceReference2(IWFUtils::StringToVector(tref.substr(0, 3)));
        }
    }
}

void MAPToS6aHandler::DeactivateTraceModeRes_To_DSA(
        IwfFsm *ctxt,
        const DeactivateTraceModeRes *in,
        s6a::DeleteSubscriberDataAnswer *out)
{
    if ((ctxt == NULL) || (in == NULL) || (out == NULL))
    {
        DLOG_DEBUG("Invalid Input Param");
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);

    out->setResultCode(res);

    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}


void MAPToS6aHandler:: BuildTraceInterfaceList(std::string& trInterfaceList, map_v13::TraceInterfaceList *tril)
{
    std::vector<byte> value = IWFUtils::StringToVector(trInterfaceList);

    /* extract first two bytes from the traceInterfaceList avp and populate
     * the MSC-S-List ie */
    if(value.size() >= 2)
    {
        std::stringstream str;
        str<<value[0];
        str<<value[1];
        vector<byte> mscVector = IWFUtils::StringToVector((str.str()));
        unsigned int msc = (((uint16_t)mscVector[1]) << 8 | mscVector[0]);
        map_v13::MSC_S_InterfaceList mscslist(IWFUtils::UnsignedToBitVector(msc,10));
        tril->SetMsc_s_List(mscslist);

    }
    if(value.size() >= 3)
    {
        unsigned int mgw = value[2];
        map_v13::MGW_InterfaceList mgwlist(IWFUtils::UnsignedToBitVector(mgw,3));
        tril->SetMgw_List(mgwlist);
    }
    if(value.size() >= 4)
    {
        std::stringstream tmpstr;
        tmpstr<<value[3];
        tmpstr<<value[4];
        vector<byte> sgsnVector = IWFUtils::StringToVector((tmpstr.str()));
        unsigned int sgsn = (((uint16_t)sgsnVector[1]) << 8 | sgsnVector[0]);
        map_v13::SGSN_InterfaceList sgsnlist(IWFUtils::UnsignedToBitVector(sgsn,10));
        tril->SetSgsn_List(sgsnlist);
    }
    if(value.size() >= 6)
    {
        unsigned int ggsn = value[5];
        map_v13::GGSN_InterfaceList ggsnlist(IWFUtils::UnsignedToBitVector(ggsn,3));
        tril->SetGgsn_List(ggsnlist);
    }
    if(value.size() >= 7)
    {
        unsigned int rnc = value[6];
        map_v13::RNC_InterfaceList rnclist(IWFUtils::UnsignedToBitVector(rnc,4));
        tril->SetRnc_List(rnclist);
    }
    if(value.size() >= 8)
    {
        unsigned int bmsc = value[7];
        map_v13::BMSC_InterfaceList bmsclist(IWFUtils::UnsignedToBitVector(bmsc,1));
        tril->SetBmsc_List(bmsclist);
    }
    if(value.size() >= 9)
    {
        unsigned int mme = value[8];
        map_v13::MME_InterfaceList mmelist(IWFUtils::UnsignedToBitVector(mme,5));
        tril->SetMme_List(mmelist);
    }
    if(value.size() >= 10)
    {
        unsigned int sgw = value[9];
        map_v13::SGW_InterfaceList sgwlist(IWFUtils::UnsignedToBitVector(sgw,5));
        tril->SetSgw_List(sgwlist);
    }
    if(value.size() >= 11)
    {
        unsigned int pdngw = value[10];
        map_v13::PGW_InterfaceList pdngwlist(IWFUtils::UnsignedToBitVector(pdngw,8));
        tril->SetPgw_List(pdngwlist);
    }
    if(value.size() >= 12)
    {
        unsigned int enb  = value[11];
        map_v13::ENB_InterfaceList enblist(IWFUtils::UnsignedToBitVector(enb,3));
        tril->SetENB_List(enblist);
    }
}

void MAPToS6aHandler::BuildTraceDepthList(s6a::TraceDepth tracedepth,map_v13::ActivateTraceModeArg *out)
{
    map_v13::TraceDepthList tdel;
    int depth_val = tracedepth.value();
    if(depth_val >=0 && depth_val<= 2)
    {
        tdel.SetMsc_s_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetMgw_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetSgsn_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetGgsn_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetRnc_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetBmsc_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetMme_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetSgw_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetPgw_TraceDepth(map_v13::TraceDepth(depth_val));
        tdel.SetENB_TraceDepth(map_v13::TraceDepth(depth_val));

        out->SetTraceDepthList(tdel);
    }
}

void MAPToS6aHandler:: BuildTraceEventList(std::string& trEvntList,map_v13::TraceEventList* trel)
{
    std::vector<byte> value = IWFUtils::StringToVector(trEvntList);

    /* extract first two bytes from the traceInterfaceList avp and populate
     * the MSC-S-List ie */
    if(value.size() >= 2)
    {
        std::stringstream tmpstr;
        tmpstr<<value[0];
        tmpstr<<value[1];
        vector<byte> mscVector = IWFUtils::StringToVector((tmpstr.str()));
        unsigned int msc = (((uint16_t)mscVector[1]) << 8 | mscVector[0]);
        map_v13::MSC_S_EventList mscslist(IWFUtils::UnsignedToBitVector(msc,5));
        trel->SetMsc_s_List(mscslist);
    }
    if(value.size() >= 3)
    {
        unsigned int mgw = value[2];
        map_v13::MGW_EventList mgwlist(IWFUtils::UnsignedToBitVector(mgw,1));
        trel->SetMgw_List(mgwlist);
    }
    if(value.size() >= 4)
    {
        std::stringstream tmpstr;
        tmpstr<<value[3];
        tmpstr<<value[4];
        vector<byte> sgsnVector = IWFUtils::StringToVector((tmpstr.str()));
        unsigned int sgsn = (((uint16_t)sgsnVector[1]) << 8 | sgsnVector[0]);
        map_v13::SGSN_EventList sgsnlist(IWFUtils::UnsignedToBitVector(sgsn,4));
        trel->SetSgsn_List(sgsnlist);
    }
    if(value.size() >= 6)
    {
        unsigned int ggsn = value[5];
        map_v13::GGSN_EventList ggsnlist(IWFUtils::UnsignedToBitVector(ggsn,2));
        trel->SetGgsn_List(ggsnlist);
    }
    if(value.size() >= 7)
    {
        unsigned int bmsc = value[6];
        map_v13::BMSC_EventList bmsclist(IWFUtils::UnsignedToBitVector(bmsc,1));
        trel->SetBmsc_List(bmsclist);
    }
    if(value.size() >= 8)
    {
        unsigned int mme = value[7];
        map_v13::MME_EventList mmelist(IWFUtils::UnsignedToBitVector(mme,6));
        trel->SetMme_List(mmelist);
    }
    if(value.size() >= 9)
    {
        unsigned int pgw = IWFUtils::High4(value[8]);
        unsigned int sgw = IWFUtils::Low4(value[8]);
        map_v13::PGW_EventList pgwlist(IWFUtils::UnsignedToBitVector(pgw,3));
        map_v13::SGW_EventList sgwlist(IWFUtils::UnsignedToBitVector(sgw,3));
        trel->SetPgw_List(pgwlist);
        trel->SetSgw_List(sgwlist);
    }
}


void MAPToS6aHandler::BuildMDTConfiguration(s6a::MDTConfiguration mdtConfig, map_v13::MDT_Configuration &out)
{
    int jobType = mdtConfig.getJobType().value();
    out.SetJobType(map_v13::JobType(jobType));

    if(mdtConfig.containsAreaScope())
    {
        s6a::AreaScope areaScope = mdtConfig.getAreaScope();
        map_v13::AreaScope areaScp;
        BuildAreaScope(areaScope, areaScp);
        out.SetAreaScope(areaScp);
    }

    if(mdtConfig.containsListOfMeasurements())
    {
        map_v13::ListOfMeasurements listOfMsrmnts(IWFUtils::UnsignedToBytes(mdtConfig.getListOfMeasurements().value(), 4));
        out.SetListOfMeasurements(listOfMsrmnts);
    }

    if(mdtConfig.containsReportingTrigger())
    {
        map_v13::ReportingTrigger reportingTrig(IWFUtils::UnsignedToBytes(mdtConfig.getReportingTrigger().value(), 1));
        out.SetReportingTrigger(reportingTrig);
    }

    if(mdtConfig.containsReportInterval())
    {
        int reportInterval = mdtConfig.getReportInterval().value();
        out.SetReportInterval(map_v13::ReportInterval(reportInterval));
    }

    if(mdtConfig.containsReportAmount())
    {
        int reportAmount = mdtConfig.getReportAmount().value();
        out.SetReportAmount(map_v13::ReportAmount(reportAmount));
    }

    if(mdtConfig.containsEventThresholdRSRP())
    {
        out.SetEventThresholdRSRP(map_v13::EventThresholdRSRP(mdtConfig.getEventThresholdRSRP().value()));
    }

    if(mdtConfig.containsEventThresholdRSRQ())
    {
        out.SetEventThresholdRSRQ(map_v13::EventThresholdRSRQ(mdtConfig.getEventThresholdRSRQ().value()));
    }

    if(mdtConfig.containsLoggingInterval())
    {
        int loggingInterval = mdtConfig.getLoggingInterval().value();
        out.SetLoggingInterval(map_v13::LoggingInterval(loggingInterval));
    }

    if(mdtConfig.containsLoggingDuration())
    {
        int loggingDuration = mdtConfig.getLoggingDuration().value();
        out.SetLoggingDuration(map_v13::LoggingDuration(loggingDuration));
    }
}

void MAPToS6aHandler::BuildAreaScope(s6a::AreaScope areaScope, map_v13::AreaScope &out)
{
    if(areaScope.countCellGlobalIdentity())
    {
        map_v13::CGI_List cgiList;
        for (int iIndex = 0; iIndex < areaScope.countCellGlobalIdentity(); iIndex++)
        {
            std::string cellId = areaScope.getCellGlobalIdentity(iIndex).value();
            if(cellId.length() >= 5 && cellId.length() <= 7)
            {
                map_v13::GlobalCellId globalCellId(IWFUtils::StringToVector(cellId));
                cgiList.AddElement(globalCellId);
            }
        }
        out.SetCgi_List(cgiList);
    }

    if(areaScope.countEUTRANCellGlobalIdentity())
    {
        map_v13::E_UTRAN_CGI_List eUtranCgiList;
        for (int iIndex = 0; iIndex < areaScope.countCellGlobalIdentity(); iIndex++)
        {
            std::string utrancgi = areaScope.getEUTRANCellGlobalIdentity(iIndex).value();
            if( utrancgi.length() >= 7)
            {
                map_v13::E_UTRAN_CGI eUtranCgi(IWFUtils::StringToVector(utrancgi.substr(0, 7)));
                eUtranCgiList.AddElement(eUtranCgi);
            }
        }
        out.SetE_utran_cgi_List(eUtranCgiList);
    }

    if(areaScope.countRoutingAreaIdentity())
    {
        map_v13::RoutingAreaId_List routingAreaIdList;
        for (int iIndex = 0; iIndex < areaScope.countCellGlobalIdentity(); iIndex++)
        {
            std::string rai = areaScope.getRoutingAreaIdentity(iIndex).value();
            if(rai.length() >= 6)
            {
                map_v13::RAIdentity raId(IWFUtils::StringToVector(rai.substr(0, 6)));
                routingAreaIdList.AddElement(raId);
            }
        }
        out.SetRoutingAreaId_List(routingAreaIdList);
    }

    if(areaScope.countLocationAreaIdentity())
    {
        map_v13::LocationAreaId_List locAreaIdList;
        for (int iIndex = 0; iIndex < areaScope.countCellGlobalIdentity(); iIndex++)
        {
            std::string lai = areaScope.getLocationAreaIdentity(iIndex).value();
            if(lai.length() >= 5)
            {
                map_v13::LAIFixedLength laiFixedLength(IWFUtils::StringToVector(lai.substr(0, 5)));
                locAreaIdList.AddElement(laiFixedLength);
            }
        }
        out.SetLocationAreaId_List(locAreaIdList);
    }

    if(areaScope.countTrackingAreaIdentity())
    {
        map_v13::TrackingAreaId_List trackAreaIdList;
        for (int iIndex = 0; iIndex < areaScope.countCellGlobalIdentity(); iIndex++)
        {
            std::string tai = areaScope.getTrackingAreaIdentity(iIndex).value();
            if(tai.length() >= 5)
            {
                map_v13::TA_Id taId(IWFUtils::StringToVector(tai.substr(0, 5)));
                trackAreaIdList.AddElement(taId);
            }
        }
        out.SetTrackingAreaId_List(trackAreaIdList);
    }
}

int MAPToS6aHandler::BuildDiaResponse(IwfFsm* ctxt, DIA_BASE_CMD* in, DIA_BASE_CMD*& out, IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    ret.appContext = map_common::UNKNOWN;
    out = NULL;

    try
    {
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();
        // the diameter message is s6a, assuming that the MAP function is called
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (cmd->isRequest())
        {
            if (code == DIA_CMD_RS)
            {
                // The only diameter response now is the Notify Answer
                s6a::ResetRequest rreq(cmd->getImpl());

                DLOG_DEBUG("Constructing ResetAnswer for ResetRequest");
                s6a::ResetAnswer *rsa = new s6a::ResetAnswer();

                ConstructRSA(ctxt, &rreq, rsa);
                SetDefaultAVPsInAns(ctxt, rsa);

                LogS6aDiaMsg(*rsa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)rsa);
                out->SetDictId(DIA_S6A_REL10_DICTID);
                ret.action = IWF_RA_RESPOND_ONLY;
            }
        }
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("#### Exception: %s ####", e.what());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
    }
    catch(...)
    {
        DLOG_ERROR("#### Unknown Exception on BuildDiaResponse ####");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
    }

    return rc;
}

void MAPToS6aHandler::ConstructRSA(IwfFsm *ctxt, const s6a::ResetRequest *in,
        s6a::ResetAnswer *out)
{
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    /* Auth session state -> NO_STATE_MAINTAINED */
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}

char MAPToS6aHandler::GetCheckDigitForIMEI(std::string imei)
{
    int checkDigit = 0;
    int i = strlen(imei.c_str());
    printf("length %d\n", i);
    char digitv = 0;

    while( i-- )
    {
        digitv = imei.c_str()[i] - '0';
        digitv <<= ( i % 2 );
        digitv -= 9 * ( digitv > 9 );
        checkDigit += digitv;
    }

    return ((10 - (checkDigit % 10)) % 10);
}

int MAPToS6aHandler::SetConfig(IwfTranslationDataConfig *translationDataConfig)
{
    DLOG_DEBUG("MAPToS6aHandler::SetConfig Entry");
    int retVal = ITS_SUCCESS;
    IwfMapToS6aConfig mapS6aCfg = translationDataConfig->maptos6ainfo();
    if(mapS6aCfg.has_hlrnumber())
    {
        m_config.SetHlrNumber(mapS6aCfg.hlrnumber());
    }

    int maps6avplmnIdcount = mapS6aCfg.maptos6avplmnidinfo_size();

    if(maps6avplmnIdcount > 0)
    {
        for(int i = 0; i < maps6avplmnIdcount; i++)
        {
            IwfMapToS6aVplmnIdConfig mapS6aVplmnIdCfg = mapS6aCfg.maptos6avplmnidinfo(i);
            if(mapS6aVplmnIdCfg.has_allowedvplmnid())
            {
                DLOG_DEBUG("MapS6a VplmnId [%d] : %s", i, mapS6aVplmnIdCfg.allowedvplmnid().c_str());
                std::string allowedVplmnId = mapS6aVplmnIdCfg.allowedvplmnid();
                int sgsnNumberCount = mapS6aVplmnIdCfg.sgsnnumberinfo_size();
                if(sgsnNumberCount > 0)
                {
                    for(int sgsnCnt = 0; sgsnCnt < sgsnNumberCount; sgsnCnt++)
                    {
                        SgsnNumbers sgsnNum = mapS6aVplmnIdCfg.sgsnnumberinfo(sgsnCnt);
                        if(sgsnNum.has_sgsnnumber())
                        {
                            DLOG_DEBUG("MapS6a SgsnNumber [%d] : %s", sgsnCnt, sgsnNum.sgsnnumber().c_str());
                            std::string sgsnNumber = sgsnNum.sgsnnumber();

                            // Truncate sgsnNumber from first occurance of wild-card (*) character
                            int pos= sgsnNumber.find_first_of('*',0);
                            if(pos != -1)
                            {
                                sgsnNumber.erase(pos);
                            }
                            if(!m_config.FindSgsnEntryInMap(sgsnNumber, allowedVplmnId))
                            {
                                m_config.SetVplmnIdFromSgsnNumber(sgsnNumber, allowedVplmnId);
                            }
                            else
                            {
                                DLOG_ERROR("MapS6a SgsnNumber %s already present in Map", sgsnNum.sgsnnumber().c_str());
                            }
                        }
                    }
                }
            }
        }
    }

    DLOG_DEBUG("MAPToS6aHandler::SetConfig Exit");
    return retVal;
}


int MAPToS6aHandler::DeleteVplmnIdEntryFromMap(IwfTranslationDataConfig *translationDataConfig)
{
    DLOG_DEBUG("MAPToS6aHandler::DeleteVplmnIdEntryFromMap Entry");
    int retVal = ITS_SUCCESS;
    IwfMapToS6aConfig mapS6aCfg = translationDataConfig->maptos6ainfo();
    int maps6avplmnIdcount = mapS6aCfg.maptos6avplmnidinfo_size();
    if(maps6avplmnIdcount > 0)
    {
        for(int i = 0; i < maps6avplmnIdcount; i++)
        {
            IwfMapToS6aVplmnIdConfig mapS6aVplmnIdCfg = mapS6aCfg.maptos6avplmnidinfo(i);
            if(mapS6aVplmnIdCfg.has_allowedvplmnid())
            {
                DLOG_DEBUG("MapS6a VplmnId [%d] : %s", i, mapS6aVplmnIdCfg.allowedvplmnid().c_str());
                std::string allowedVplmnId = mapS6aVplmnIdCfg.allowedvplmnid();
                if(m_config.DeleteVplmnIdFromMap(allowedVplmnId))
                {
                    DLOG_DEBUG("VplmnId Entry %s deleted successfully from map", allowedVplmnId.c_str());
                }
                else
                {
                    DLOG_ERROR("VplmnId %s not present in Map", allowedVplmnId.c_str());
                }
            }
        }
    }
    DLOG_DEBUG("MAPToS6aHandler::DeleteVplmnIdEntryFromMap Exit");
    return retVal;
}

int MAPToS6aHandler::DeleteSGSNNumberFromVplmnIdEntryInMap(IwfTranslationDataConfig *translationDataConfig)
{
    DLOG_DEBUG("MAPToS6aHandler::DeleteSGSNNumberFromVplmnIdEntryInMap Entry");
    int retVal = ITS_SUCCESS;
    IwfMapToS6aConfig mapS6aCfg = translationDataConfig->maptos6ainfo();

    int maps6avplmnIdcount = mapS6aCfg.maptos6avplmnidinfo_size();

    if(maps6avplmnIdcount > 0)
    {
        for(int i = 0; i < maps6avplmnIdcount; i++)
        {
            IwfMapToS6aVplmnIdConfig mapS6aVplmnIdCfg = mapS6aCfg.maptos6avplmnidinfo(i);
            if(mapS6aVplmnIdCfg.has_allowedvplmnid())
            {
                DLOG_DEBUG("MapS6a VplmnId [%d] : %s", i, mapS6aVplmnIdCfg.allowedvplmnid().c_str());
                std::string allowedVplmnId = mapS6aVplmnIdCfg.allowedvplmnid();
                int sgsnNumberCount = mapS6aVplmnIdCfg.sgsnnumberinfo_size();
                if(sgsnNumberCount > 0)
                {
                    std::string sgsnNumber = "";

                    for(int sgsnCnt = 0; sgsnCnt < sgsnNumberCount; sgsnCnt++)
                    {
                        SgsnNumbers sgsnNum = mapS6aVplmnIdCfg.sgsnnumberinfo(sgsnCnt);
                        if(sgsnNum.has_sgsnnumber())
                        {
                            DLOG_DEBUG("Delete MapS6a SgsnNumber [%d] : %s", sgsnCnt, sgsnNum.sgsnnumber().c_str());
                            std::string sgsnNumber = sgsnNum.sgsnnumber();

                            // Truncate sgsnNumber from first occurance of wild-card (*) character
                            int pos= sgsnNumber.find_first_of('*',0);
                            if(pos != -1)
                            {
                                sgsnNumber.erase(pos);
                            }
                            if(m_config.DeleteSgsnEntryFromMap(sgsnNumber, allowedVplmnId))
                            {
                                DLOG_DEBUG("Entry deleted successfully");
                            }
                            else
                            {
                                DLOG_ERROR("Sgsn Number : %s not present in VplmnId Map for VplmnId Entry : %s", sgsnNumber.c_str(), allowedVplmnId.c_str());
                            }
                        }
                    }
                }
            }
        }
    }
    DLOG_DEBUG("MAPToS6aHandler::DeleteSGSNNumberFromVplmnIdEntryInMap Exit");
    return retVal;
}

int MAPToS6aHandler::DeleteConfig(IwfTranslationDataConfig *translationDataConfig)
{
    int retVal = CMAPI_SUCCESS;
    switch (translationDataConfig->operreqid())
    {

        case DEL_MAPS6A_VPLMN_ID_DATA:
            {
                retVal = DeleteVplmnIdEntryFromMap(translationDataConfig);
                if (retVal != ITS_SUCCESS)
                {
                    DLOG_ERROR("Deletion if VplmnId entry Failed");
                }
            }
            break;
        case DEL_VPLMN_ID_SGSN_MAP_DATA:
            {
                retVal = DeleteSGSNNumberFromVplmnIdEntryInMap(translationDataConfig);
                if( retVal != ITS_SUCCESS )
                {
                    DLOG_ERROR("Deletion if Sgsn Number from VplmnId Map Failed");
                }
            }
            break;

    }
    return retVal;
}

void MAPToS6aHandler::EncodeMsg(AsnObject* p, Octets** octets)
{
    if (p == NULL)
    {
        return;
    }


    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        DLOG_ERROR("\n");
        DLOG_ERROR("--------------------------------------------------");
        DLOG_ERROR("Exception during encoding phase...");
        DLOG_ERROR("GetDescription",exc.GetDescription().c_str());
        DLOG_ERROR("Exit test...");
    }

    *octets = tmpOctets;
}


bool MAPToS6aHandler::IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt, bool &isReq)
{
    return false;
}

bool MAPToS6aHandler::IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq)
{
    return false;
}


int MAPToS6aHandler::BuildMultiTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

void MAPToS6aHandler::HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
        TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
        DIA_BASE_CMD*& outDiaCmd,
        TCAP_Component*& cpt,
        IwfReturnAction& outRetAction)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("MAPToS6aHandler::HandleTimeout Entry");

    DLOG_DEBUG("MAPToS6aHandler::HandleTimeout Exit");
}

void MAPToS6aHandler::StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType)
{
}
void MAPToS6aHandler::SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("MAPToS6aHandler::SetLocalTransId Entry");

    DLOG_DEBUG("MAPToS6aHandler::SetLocalTransId Exit");

}

int MAPToS6aHandler::SetTimerConfig(IwfTimersConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("MAPToS6aHandler::SetTimerConfig Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("MAPToS6aHandler::SetTimerConfig Exit");
    return retVal;
}

int MAPToS6aHandler::SetMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("MAPToS6aHandler::SetMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("MAPToS6aHandler::SetMsgSpecCfg Exit");
    return retVal;
}

int MAPToS6aHandler::DeleteMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("MAPToS6aHandler::DeleteMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("MAPToS6aHandler::DeleteMsgSpecCfg Exit");
    return retVal;
}

int MAPToS6aHandler::LogCDRData(IwfFsm* ctxt, ITS_UINT failureCause)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("MAPToS6aHandler::LogCDRData Entry");
    int retVal = ITS_SUCCESS;
    DLOG_DEBUG("MAPToS6aHandler::LogCDRData Exit");
    return retVal;
}

int MAPToS6aHandler::TerminateSession(IwfFsm *ctxt,
        TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd)
{
    ITS_UINT ret = ITS_SUCCESS;
    return ret;
}

int MAPToS6aHandler::OnUpstrmFinalReqSent(IwfFsm *ctxt)
{
    int retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT MAPToS6aHandler::SetFeaturesConfig(IwfFeatureConfig *req)
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT MAPToS6aHandler::GetCDRConfig()
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT MAPToS6aHandler::GetCDRFailureCause(IwfFsm* iwfFsm)
{
    return SUCCESS_CALL;
}
