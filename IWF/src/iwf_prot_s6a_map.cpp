#include "iwf.h"
#include "iwf_prot_s6a_map.h"
#include "iwf_prot_utils.h"
#include "iwf_transaction_manager.h"

#include <dia_frame.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <ssg_trace.h>
#include <ssg_statistics.h>

// MAP Error codes
#include <map_c.h>

#include <sstream>

extern ITSDiaConfig itsDiaConfig;
static ITS_OCTET invkId = 0;

SsgStackStatistics mapStats;
    template <typename T> static
void SetDefaultAVPs(IwfFsm *ctxt, T *cmd, const char* imsiStr = NULL)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    std::string sessId = ctxt->GetDiaSessionId();
    if (sessId.empty())
    {
        // allocate new session id
        uint32_t sIdx = 0;
        int ret = DiaFrame::GetDiaFrame()->AllocateSessionIndex(
                0U, sIdx, sessId);
        if (ret != ITS_SUCCESS)
        {
            // log an error and thrown an exception
        }
        cmd->setSessionIndex(sIdx);
    }

    cmd->setSessionId(diameter::base::SessionId(sessId));

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    cmd->setOriginHost(lcer->getOriginHost());
    cmd->setOriginRealm(lcer->getOriginRealm());

}

void AddProxyInfoAVPs(IwfFsm* ctxt, void* cmd, uint32_t cmdCode)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG(" ProxyInfo count in Fsm = %d", ctxt->CountProxyInfo());
    switch(cmdCode)
    {
        case DIA_CMD_UL:
            {
                s6a::UpdateLocationAnswer* ula = (s6a::UpdateLocationAnswer*)cmd;
                for(int i = 0; i < ctxt->CountProxyInfo(); i++)
                {
                    ula->addProxyInfo(ctxt->GetProxyInfo(i));
                }
            }
            break;
        case DIA_CMD_AI:
            {
                s6a::AuthenticationInformationAnswer* aia = (s6a::AuthenticationInformationAnswer*)cmd;
                for(int i = 0; i < ctxt->CountProxyInfo(); i++)
                {
                    aia->addProxyInfo(ctxt->GetProxyInfo(i));
                }
            }
            break;
        case DIA_CMD_NO:
            {
                s6a::NotifyAnswer* noa = (s6a::NotifyAnswer*)cmd;
                for(int i = 0; i < ctxt->CountProxyInfo(); i++)
                {
                    noa->addProxyInfo(ctxt->GetProxyInfo(i));
                }
            }
            break;
        case DIA_CMD_PU:
            {
                s6a::PurgeUEAnswer* pua = (s6a::PurgeUEAnswer*)cmd;
                for(int i = 0; i < ctxt->CountProxyInfo(); i++)
                {
                    pua->addProxyInfo(ctxt->GetProxyInfo(i));
                }
            }
            break;
        default:
            break;
    }
}
    template <typename T> static
void SetDefaultAVPsInAns(IwfFsm *ctxt, T *cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    std::string sessId = ctxt->GetDiaSessionId();
    if (sessId.empty())
    {
        // allocate new session id
        uint32_t sIdx = 0;
        int ret = DiaFrame::GetDiaFrame()->AllocateSessionIndex(
                0U, sIdx, sessId);
        if (ret != ITS_SUCCESS)
        {
            // log an error an thrown an exception
        }
        cmd->setSessionIndex(sIdx);
    }

    cmd->setSessionId(diameter::base::SessionId(sessId));

    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    cmd->setOriginHost(lcer->getOriginHost());
    cmd->setOriginRealm(lcer->getOriginRealm());
    // Set the ProxyInfo AVPs if present
    switch(cmd->getCommandCode())
    {
        case DIA_CMD_UL:
        case DIA_CMD_AI:
        case DIA_CMD_NO:
        case DIA_CMD_PU:
            AddProxyInfoAVPs(ctxt, cmd, cmd->getCommandCode());
            break;
        default:
            break;
    }
}

    template<typename T> static
int SetDestinationHostAndRealm(IwfFsm *ctxt, std::string simsi, T *cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    // Now fetch SessionCtxt using IMSI for Destination Host&Realm
    SessionCtxt *sctxt= ctxt->GetTransactionManager()->GetSessionCtxt(simsi);
    if (!sctxt)
    {
        DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Not Found for: %s", simsi.c_str());
        return ITS_ENOTFOUND;
    }

    diameter::base::DestinationHost ds(sctxt->GetOriginHost());
    diameter::base::DestinationRealm dr(sctxt->GetOriginRealm());
    cmd->setDestinationHost(ds);
    cmd->setDestinationRealm(dr);

    return ITS_SUCCESS;
}

inline void LogDiaMsg(diameter::Command& cmd, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "RECEIVED S6a message\n";
    }
    else
    {
        str << "SENDING S6a message\n";
    }

    str << cmd << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

inline void LogAsnObj(AsnObject& asn, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "RECEIVED MAP message\n";
    }
    else
    {
        str << "SENDING MAP message\n";
    }

    str << asn << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

void S6aMAPConfig::Parse(Json::Value& val, IwfConfig& conf)
{
#if 0
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Json::Value entry = val["local-sgsn-number"];
    if (entry.empty())
    {
        throw IwfConfigException("'local-sgsn-number' not part "
                "of '/proto-translator/s6a-MAP/'");
    }

    std::string sgsnNum = entry.asString();
    uint8_t svar[20];
    int     len = 20;

    len = IWFUtils::StringToTBCD(sgsnNum, svar, len, 0x0f);
    m_sgsnNumber.assign(svar, svar + len);

    std::string oHost;
    its::ByteArray ipAddr;

    entry = val["sgsn-address-map"];

    for (unsigned i = 0; i < entry.size(); i++)
    {
        oHost = entry[i]["origin-host"].asString();
        IWFUtils::IpStringToGSNAddress(
                entry[i]["ip-address"].asString(), ipAddr);
        m_sgsnMap[oHost] = ipAddr;
    }
#endif
}

    S6aToMAPHandler::S6aToMAPHandler()
: IwfTranslator(S6A_TO_MAP_STR)
{
}

S6aToMAPHandler::~S6aToMAPHandler()
{
}

void S6aToMAPHandler::BuildTCAPErrorCpt(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::BuildTCAPErrorCpt Entry");
    try {

        ITS_OCTET  mapErr = MAP_ERR_UNEXPECTED_DATA_VALUE;
        Octets *enc2 = NULL;
        if (cmd != 0)
        {
            TCAP_Error *terr = new TCAP_Error();
            terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());


            diameter::base::BaseGenericCommand* bgc = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();
            int erc = bgc->countExperimentalResult();

            // get proper Error Code
            int eridx = 0;
            while (eridx < erc)
            {
                const diameter::base::ExperimentalResult *er = bgc->getExperimentalResult(eridx++);
                // Interested only in 3GPP vendor defined errors.
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
                                if(unkwnSubs != NULL)
                                {
                                    delete unkwnSubs;
                                    unkwnSubs = NULL;
                                }
                                if(enc2 != NULL)
                                {
                                    delete enc2;
                                    enc2 = NULL;
                                }
                                break;
                            }
                        case DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION:
                            {
                                map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                                map_v13::UnknownSubscriberDiagnostic unknsubdia(map_v13::
                                        UnknownSubscriberDiagnostic::
                                        UNKNOWN_SUBSCRIBER_DIAGNOSTIC_GPRS_EPS_SUBSCRIPTION_UNKNOWN);
                                unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                                EncodeMsg(unkwnSubs, &enc2);
                                terr->SetParameter(enc2->GetArray());
                                mapErr = MAP_ERR_UNKNOWN_SUBSCRIBER;
                                if(unkwnSubs != NULL)
                                {
                                    delete unkwnSubs;
                                    unkwnSubs = NULL;
                                }
                                if(enc2 != NULL)
                                {
                                    delete enc2;
                                    enc2 = NULL;
                                }
                                break;
                            }
                        case DIAMETER_ERROR_RAT_NOT_ALLOWED:
                            {
                                map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                                map_v13::RoamingNotAllowedCause rnac(map_v13::
                                        RoamingNotAllowedCause::ROAMING_NOT_ALLOWED_CAUSE_OPERATOR_DETERMINED_BARRING);
                                map_v13::AdditionalRoamingNotAllowedCause arnac(map_v13::
                                        AdditionalRoamingNotAllowedCause::
                                        ADDITIONAL_ROAMING_NOT_ALLOWED_CAUSE_SUPPORTED_RAT_TYPES_NOT_ALLOWED);
                                roamNot->SetAdditionalRoamingNotAllowedCause(arnac);
                                EncodeMsg(roamNot, &enc2);
                                terr->SetParameter(enc2->GetArray());
                                if(roamNot != NULL)
                                {
                                    delete roamNot;
                                    roamNot = NULL;
                                }
                                if(enc2 != NULL)
                                {
                                    delete enc2;
                                    enc2 = NULL;
                                }
                                mapErr = MAP_ERR_ROAMING_NOT_ALLOWED;
                                break;
                            }
                        case DIAMETER_ERROR_ROAMING_NOT_ALLOWED:
                            {
                                map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                                map_v13::RoamingNotAllowedCause rnac(map_v13::RoamingNotAllowedCause::
                                        ROAMING_NOT_ALLOWED_CAUSE_OPERATOR_DETERMINED_BARRING);
                                roamNot->SetRoamingNotAllowedCause(rnac);
                                EncodeMsg(roamNot, &enc2);
                                terr->SetParameter(enc2->GetArray());
                                if(roamNot != NULL)
                                {
                                    delete roamNot;
                                    roamNot = NULL;
                                }
                                if(enc2 != NULL)
                                {
                                    delete enc2;
                                    enc2 = NULL;
                                }
                                mapErr = MAP_ERR_ROAMING_NOT_ALLOWED;
                                break;
                            }
                        default:
                            break;
                    }
                    break;
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
    DLOG_DEBUG("S6aToMAPHandler::BuildTCAPErrorCpt Exit");
}

void S6aToMAPHandler::BuildTcapError(IwfFsm *ctxt, TCAP_Component *&cpt)
{
    DLOG_DEBUG("S6aToMAPHandler::BuildTcapError Entry ");
    Octets *enc2 = NULL;
    ITS_OCTET  Err = 0;
    TCAP_Error *terr = new TCAP_Error();
    if(ctxt->GetCurrRcvdTcapCpt() != NULL)
    {
        terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
    }
    try
    {
        switch(ctxt->GetErrorCode())
        {
            case MAP_ERR_UNKNOWN_SUBSCRIBER:
                {
                    DLOG_DEBUG("Building TcapError for Unknown Subscriber");
                    map_v13::UnknownSubscriberParam *unkwnSubs = new map_v13::UnknownSubscriberParam();
                    map_v13::UnknownSubscriberDiagnostic unknsubdia(map_v13::UnknownSubscriberDiagnostic
                            ::UNKNOWN_SUBSCRIBER_DIAGNOSTIC_IMSI_UNKNOWN);
                    unkwnSubs->SetUnknownSubscriberDiagnostic(unknsubdia);
                    EncodeMsg(unkwnSubs, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_UNKNOWN_SUBSCRIBER;
                    if(unkwnSubs != NULL)
                    {
                        delete unkwnSubs;
                        unkwnSubs = NULL;
                    }

                    ctxt->SetErrorCode(0);
                    break;
                }
            case MAP_ERR_ROAMING_NOT_ALLOWED:
                {
                    DLOG_DEBUG("Building TcapError for Roaming Not Allowed");
                    map_v13::RoamingNotAllowedParam *roamNot = new map_v13::RoamingNotAllowedParam();
                    map_v13::RoamingNotAllowedCause rnac(map_v13::RoamingNotAllowedCause::
                            ROAMING_NOT_ALLOWED_CAUSE_PLMN_ROAMING_NOT_ALLOWED);
                    roamNot->SetRoamingNotAllowedCause(rnac);
                    EncodeMsg(roamNot, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_ROAMING_NOT_ALLOWED;

                    if(roamNot != NULL)
                    {
                        delete roamNot;
                        roamNot = NULL;
                    }

                    break;
                }
            case IWF_EBASE_MAND_AVP_MISSING:
            case ITS_DIA_MISSING_AVP:
            case MAP_ERR_DATA_MISSING:
                {
                    DLOG_DEBUG("Building TcapError for Data Missing Error");
                    map_v13::DataMissingParam *dataMissing = new map_v13::DataMissingParam();
                    EncodeMsg(dataMissing, &enc2);
                    terr->SetParameter(enc2->GetArray());
                    Err = MAP_ERR_DATA_MISSING;

                    if(dataMissing != NULL)
                    {
                        delete dataMissing;
                        dataMissing = NULL;
                    }
                    break;
                }
            default:
                {
                    Err = MAP_ERR_UNEXPECTED_DATA_VALUE;
                    DLOG_DEBUG("No Specific Error Set, Returning Unexpected Data Value..!!");
                }
        }
        terr->SetError(Err);
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
    if(enc2 != NULL)
    {
        delete enc2;
        enc2 = 0;
    }
    DLOG_DEBUG("S6aToMAPHandler::BuildTcapError Exit");
}

int S6aToMAPHandler::BuildTCAPMsg(IwfFsm *ctxt, DIA_BASE_CMD *bcmd, TcapCptList *out,
        DIA_BASE_CMD *&outCmd, IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::BuildTCAPMsg Entry");
    int rc = ITS_SUCCESS;
    TCAP_Component *cpt  = NULL;

    ret.dir = IWF_RD_TCAP;

    try
    {

        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
        // the diameter message is s6a, assuming that the MAP function is called
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (cmd->isRequest())
        {
            // Request message
            // TODO return respective Application Context for each request
            switch(code)
            {
                case DIA_CMD_UL:
                    {
                        s6a::UpdateLocationRequest ulr(cmd->getImpl());
                        UpdateGprsLocationArg ugla;

                        LogDiaMsg(ulr);
                        DLOG_DEBUG("[S6a:UpdateLocationRequest] -> [MAP:UpdateGPRSLocationArg]");

                        int result = ULR_To_UpdateGPRSLocationArg(ctxt, &ulr, &ugla);
                        if(result != ITS_SUCCESS)
                        {
                            ret.action = IWF_RA_ERROR;
                            ret.dir = IWF_RD_DIA;
                            rc = !ITS_SUCCESS;
                            break;
                        }

                        Octets* buf = ugla.Encode();

                        TCAP_Invoke *ivk = new TCAP_Invoke();
                        ivk->SetClass(TCAP_OPERATION_CLASS);
                        ivk->SetOperation(map_common::OP_updateGprsLocation);
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
                        }
                        UPDATE_SSG_STATS_UGL_ARG_SENT;

                        LogAsnObj(ugla, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::gprsLocationUpdateContext_v3;

                        break;
                    }
                case DIA_CMD_AI:
                    {
                        s6a::AuthenticationInformationRequest air(cmd->getImpl());
                        SendAuthenticationInfoArg saia;

                        LogDiaMsg(air);
                        DLOG_DEBUG("[S6a:AuthenticationInformationRequest] -> [MAP:SendAuthenticationInfoArg]");
                        int result = AIR_To_SendAuthenticationInfoArgv3(ctxt, &air, &saia);
                        if(result != ITS_SUCCESS)
                        {
                            ret.action = IWF_RA_ERROR;
                            ret.dir = IWF_RD_DIA;
                            rc = !ITS_SUCCESS;
                            break;
                        }


                        Octets* buf = saia.Encode();

                        TCAP_Invoke *ivk = new TCAP_Invoke();
                        ivk->SetClass(TCAP_OPERATION_CLASS);
                        ivk->SetOperation(map_common::OP_sendAuthenticationInfo);
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
                        }
                        UPDATE_SSG_STATS_SAI_ARG_SENT;
                        LogAsnObj(saia, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::infoRetrievalContext_v3;
                        break;
                    }
                case DIA_CMD_NO:
                    {
                        // NOR is mapped to UpdateGprsLocationArg or ReadyForSM
                        s6a::NotifyRequest nor(cmd->getImpl());
                        LogDiaMsg(nor);
                        unsigned norFlags = 0;
                        if(nor.containsNORFlags())
                        {
                            norFlags = nor.getNORFlags().value();
                        }
                        if (norFlags & NOR_FLAG_READY_FOR_SM_FROM_SGSN||
                                norFlags & NOR_FLAG_READY_FOR_SM_FROM_MME)
                        {
                            // send ReadyForSM_Arg
                            ReadyForSM_Arg rfsa;
                            DLOG_DEBUG("[S6a:NotifyRequest] -> [MAP:ReadyForSM_Arg]");
                            NOR_To_ReadyForSM(ctxt, &nor, &rfsa);

                            Octets* buf = rfsa.Encode();

                            TCAP_Invoke *ivk = new TCAP_Invoke();
                            ivk->SetClass(TCAP_OPERATION_CLASS);
                            ivk->SetOperation(map_common::OP_readyForSM);
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
                            }
                            UPDATE_SSG_STATS_READY_FOR_SM_ARG_SENT;
                            LogAsnObj(rfsa, false);
                            ret.appContext = map_common::mwdMngtContext_v3;
                        }
                        else
                        {
                            // send UpdateGprsLocationArg
                            UpdateGprsLocationArg ugla;
                            DLOG_DEBUG("[S6a:NotifyRequest] -> [MAP:UpdateGprsLocationArg]");
                            NOR_To_UpdateGPRSLocationArg(ctxt, &nor, &ugla);

                            Octets* buf = ugla.Encode();

                            TCAP_Invoke *ivk = new TCAP_Invoke();
                            ivk->SetClass(TCAP_OPERATION_CLASS);
                            ivk->SetOperation(map_common::OP_updateGprsLocation);
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
                            }
                            UPDATE_SSG_STATS_UGL_ARG_SENT;
                            LogAsnObj(ugla, false);
                            ret.appContext = map_common::gprsLocationUpdateContext_v3;
                        }
                        ret.action = IWF_RA_RESPOND_AND_FORWARD;
                        break;
                    }
                case DIA_CMD_PU:
                    {
                        s6a::PurgeUERequest pur(cmd->getImpl());
                        PurgeMS_Arg puarg;

                        LogDiaMsg(pur);
                        DLOG_DEBUG("[S6a:PurgeUERequest] -> [MAP:PurgeMS-Arg]");

                        PUR_To_PurgeMSArgv3(ctxt, &pur, &puarg);

                        Octets* buf = puarg.Encode();

                        TCAP_Invoke *ivk = new TCAP_Invoke();
                        ivk->SetClass(TCAP_OPERATION_CLASS);
                        ivk->SetOperation(map_common::OP_purgeMS);
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
                        }
                        UPDATE_SSG_STATS_PURGE_ARG_SENT;
                        LogAsnObj(puarg, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::msPurgingContext_v3;
                        break;
                    }

                default:
                    {
                        // Log an error
                        DLOG_ERROR("S6aToMAPHandler::Unhandled diameter request %d", code);
                        ret.action = IWF_RA_ERROR;
                        ret.dir = IWF_RD_DIA;
                    }
            }
        }
        else
        {
            // Response or error
            switch(code)
            {
                case DIA_CMD_CL:
                    {
                        s6a::CancelLocationAnswer cla(cmd->getImpl());
                        LogDiaMsg(cla);

                        if (!cla.containsResultCode() ||
                                cla.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }

                        CancelLocationRes clRes;
                        DLOG_DEBUG("[s6a:CancelLocationAnswer] -> [MAP:CancelLocationRes]");
                        CLA_To_CancelLocationRes(ctxt, &cla, &clRes);
                        Octets* buf = clRes.Encode();

                        TCAP_Result *res = new TCAP_Result();
                        /*Note: Setting invokeId for the Tcap Response Built */
                        res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                        res->SetOperation(map_common::OP_cancelLocation);
                        res->SetParameter(buf->GetArray());
                        cpt = res;
                        out->BuildTcapCptList(*cpt);
                        if(buf != NULL)
                        {
                            delete buf;
                            buf = NULL;
                        }
                        if(res != NULL)
                        {
                            delete res;
                            res = NULL;
                        }
                        UPDATE_SSG_STATS_CLR_RES_SENT;
                        LogAsnObj(clRes, false);

                        ret.action = IWF_RA_FORWARD;
                        ret.appContext = map_common::locationCancellationContext_v3;
                        break;
                    }
                case DIA_CMD_ID:
                    {
                        // An IDA may map to IDA_To_InsertSubscriberDataRes
                        //                to ProvideSubscribeInfoRes
                        //                to ActivateTraceModeRes
                        // Decision should be made based on the ctxt
                        s6a::InsertSubscriberDataAnswer ida(cmd->getImpl());
                        LogDiaMsg(ida);

                        if (!ida.containsResultCode() ||
                                ida.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }

                        ITS_LONG opCode = GetLastMAPOperation(ctxt);
                        if (opCode == map_common::OP_insertSubscriberData)
                        {
                            InsertSubscriberDataRes isdr;
                            DLOG_DEBUG("[s6a:InsertSubscriberDataAnswer] -> [MAP:InsertSubscriberDataRes]");

                            IDA_To_InsertSubscriberDataRes(ctxt, &ida, &isdr);
                            Octets* buf = isdr.Encode();

                            TCAP_Result *res = new TCAP_Result();
                            /*Note: Setting invokeId for the Tcap Response Built */
                            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                            res->SetOperation(opCode);
                            res->SetParameter(buf->GetArray());
                            cpt = res;
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(res != NULL)
                            {
                                delete res;
                                res = NULL;
                            }
                            UPDATE_SSG_STATS_ISD_RES_SENT;
                            LogAsnObj(isdr, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::subscriberDataMngtContext_v3;
                        }
                        else if (opCode == map_common::OP_provideSubscriberInfo)
                        {
                            ProvideSubscriberInfoRes psir;
                            DLOG_DEBUG("[s6a:InsertSubscriberDataAnswer] -> [MAP:ProvideSubscriberInfoRes]");

                            IDA_To_ProvideSubscribeInfoRes(ctxt, &ida, &psir);
                            Octets* buf = psir.Encode();

                            TCAP_Result *res = new TCAP_Result();
                            /*Note: Setting invokeId for the Tcap Response Built */
                            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                            res->SetOperation(opCode);
                            res->SetParameter(buf->GetArray());
                            cpt = res;
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(res != NULL)
                            {
                                delete res;
                                res = NULL;
                            }
                            UPDATE_SSG_STATS_PSD_RES_SENT;
                            LogAsnObj(psir, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::subscriberInfoEnquiryContext_v3;
                        }
                        else if (opCode == map_common::OP_activateTraceMode)
                        {
                            ActivateTraceModeRes atmr;
                            DLOG_DEBUG("[s6a:InsertSubscriberDataAnswer] -> [MAP:ActivateTraceModeRes]");

                            IDA_To_ActivateTraceModeRes(ctxt, &ida, &atmr);
                            Octets* buf = atmr.Encode();

                            TCAP_Result *res = new TCAP_Result();
                            /*Note: Setting invokeId for the Tcap Response Built */
                            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                            res->SetOperation(opCode);
                            res->SetParameter(buf->GetArray());
                            cpt = res;
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(res != NULL)
                            {
                                delete res;
                                res = NULL;
                            }
                            UPDATE_SSG_STATS_ATM_RES_SENT;
                            LogAsnObj(atmr, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::tracingContext_v3;
                        }
                        else
                        {
                            DLOG_ERROR("S6aToMAPHandler::Unexpected Opcode for existing transaction");
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                        }

                        break;
                    }
                case DIA_CMD_DS:
                    {
                        // DSA maps to DeleteSubscriberDataAnswer
                        //          or DeactivateTraceModeRes
                        s6a::DeleteSubscriberDataAnswer dsa(cmd->getImpl());
                        LogDiaMsg(dsa);

                        if (!dsa.containsResultCode() ||
                                dsa.getResultCode().value() != ITS_DIA_SUCCESS)
                        {
                            BuildTCAPErrorCpt(ctxt, bcmd, cpt);
                            out->BuildTcapCptList(*cpt);
                            ret.action = IWF_RA_ERROR;
                            ret.appContext = map_common::UNKNOWN;
                            break;
                        }

                        ITS_LONG opCode = GetLastMAPOperation(ctxt);
                        if (opCode == map_common::OP_deleteSubscriberData)
                        {
                            DeleteSubscriberDataRes dsdr;
                            DLOG_DEBUG("[s6a:DeleteSubscriberDataAnswer] -> [MAP:DeleteSubscriberDataRes]");

                            DSA_To_DeleteSubscriberDataRes(ctxt, &dsa, &dsdr);
                            Octets* buf = dsdr.Encode();

                            TCAP_Result *res = new TCAP_Result();
                            /*Note: Setting invokeId for the Tcap Response Built */
                            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                            res->SetOperation(opCode);
                            res->SetParameter(buf->GetArray());
                            cpt = res;
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(res != NULL)
                            {
                                delete res;
                                res = NULL;
                            }
                            UPDATE_SSG_STATS_DSD_RES_SENT;
                            LogAsnObj(dsdr, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::subscriberDataMngtContext_v3;
                        }
                        else if (opCode == map_common::OP_deactivateTraceMode)
                        {
                            DeactivateTraceModeRes dtmr;
                            DLOG_DEBUG("[s6a:DeleteSubscriberDataAnswer] -> [MAP:DeactivateTraceModeRes]");

                            DSA_To_DeactivateTraceModeRes(ctxt, &dsa, &dtmr);
                            Octets* buf = dtmr.Encode();

                            TCAP_Result *res = new TCAP_Result();
                            /*Note: Setting invokeId for the Tcap Response Built */
                            res->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
                            res->SetOperation(opCode);
                            res->SetParameter(buf->GetArray());
                            cpt = res;
                            out->BuildTcapCptList(*cpt);
                            if(buf != NULL)
                            {
                                delete buf;
                                buf = NULL;
                            }
                            if(res != NULL)
                            {
                                delete res;
                                res = NULL;
                            }
                            UPDATE_SSG_STATS_DATM_RES_SENT;
                            LogAsnObj(dtmr, false);

                            ret.action = IWF_RA_FORWARD;
                            ret.appContext = map_common::tracingContext_v3;
                        }
                        break;
                    }
                case DIA_CMD_RS:
                    {
                        // nothing to do, set the cpt as NULL
                        DLOG_DEBUG("Received [S6a::ResetAnswer]. Nothing to do.");
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
    catch(...)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("Unknown exception thrown");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
    }

    DLOG_DEBUG("S6aToMAPHandler::BuildTCAPMsg Exit");
    return rc;
}
int S6aToMAPHandler::BuildDiaMsg(IwfFsm *ctxt, TCAP_Component *cpt, DIA_BASE_CMD *&cmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::BuildDiaMsg Entry");
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
                    // For request messages initiated by the server
                    switch (opCode)
                    {
                        case map_common::OP_provideSubscriberInfo:
                            {
                                s6a::InsertSubscriberDataRequest  *idr = new s6a::InsertSubscriberDataRequest();
                                map_v13::ProvideSubscriberInfoArg psiArg;
                                Octets                            octs(buf);

                                psiArg.Decode(octs);
                                LogAsnObj(psiArg);
                                DLOG_DEBUG("[MAP:ProvideSubscriberInfoArg] -> "
                                        "[s6a:InsertSubscriberDataRequest]");
                                UPDATE_SSG_STATS_PSD_ARG_RECVD;
                                if((rc = ProvideSubscriberInfoArg_To_IDR(ctxt, &psiArg, idr)) != ITS_SUCCESS)
                                {
                                    delete idr;
                                    idr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, idr, idr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)idr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*idr, false);
                                break;
                            }
                        case map_common::OP_insertSubscriberData:
                            {
                                s6a::InsertSubscriberDataRequest *idr =
                                    new s6a::InsertSubscriberDataRequest();
                                InsertSubscriberDataArg isda;
                                Octets octs(buf);
                                isda.Decode(octs);

                                LogAsnObj(isda);
                                DLOG_DEBUG("[MAP:InsertSubscriberDataArg] - [s6a:InsertSubscriberDataRequest]");
                                UPDATE_SSG_STATS_ISD_ARG_RECVD;
                                if((rc = InsertSubscriberDataArg_To_IDR(ctxt, &isda, idr)) != ITS_SUCCESS)
                                {
                                    delete idr;
                                    idr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, idr, idr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)idr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*idr, false);
                                break;
                            }
                        case map_common::OP_cancelLocation:
                            {
                                s6a::CancelLocationRequest  *clr = new s6a::CancelLocationRequest();
                                CancelLocationArg clArg;
                                Octets octs(buf);

                                clArg.Decode(octs);
                                LogAsnObj(clArg);
                                DLOG_DEBUG("[MAP:CancelLocationArg] -> "
                                        "[s6a:CancelLocationRequest]");
                                UPDATE_SSG_STATS_CLR_ARG_RECVD;
                                if((rc = CancelLocationArg_To_CLR(ctxt, &clArg, clr)) != ITS_SUCCESS)
                                {
                                    delete clr;
                                    clr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, clr, clr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)clr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);
                                LogDiaMsg(*clr, false);
                                break;
                            }
                        case map_common::OP_reset:
                            {
                                s6a::ResetRequest *rsr = new s6a::ResetRequest();
                                ResetArg ra;
                                Octets octs(buf);
                                ra.Decode(octs);

                                LogAsnObj(ra);
                                DLOG_DEBUG("[MAP:ResetArg] - [s6a:ResetRequest]");
                                ResetArg_To_RSR(ctxt, &ra, rsr);

                                // TODO the destination host for RSR cannot be determined
                                // from the User-Id, because there might be multiple
                                // user-ids in which case the Reset should be sent to all
                                // matching MME/SGSN's matching the IMSI
                                //
                                // TODO The other case is where there is not User-Id, in
                                // which case the RSR should be sent to all MME's connected
                                // to IWF.
                                SetDefaultAVPs(ctxt, rsr);
                                std::string destHost;
                                std::string destRealm;
                                ctxt->GetResetDestHost(destHost);
                                ctxt->GetResetDestRealm(destRealm);
                                CLOG_DEBUG("destHost = %s, destRealm = %s",destHost.c_str(), destRealm.c_str());
                                diameter::base::DestinationHost ds(destHost);
                                diameter::base::DestinationRealm dr(destRealm);

                                rsr->setDestinationHost(ds);
                                rsr->setDestinationRealm(dr);

                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)rsr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);
                                LogDiaMsg(*rsr, false);
                                break;
                            }
                        case map_common::OP_deleteSubscriberData:
                            {
                                s6a::DeleteSubscriberDataRequest *dsr =
                                    new s6a::DeleteSubscriberDataRequest();
                                DeleteSubscriberDataArg dsda;
                                Octets octs(buf);
                                dsda.Decode(octs);

                                LogAsnObj(dsda);
                                DLOG_DEBUG("[MAP:DeleteSubscriberDataArg] - [s6a:DeleteSubscriberDataRequest]");
                                UPDATE_SSG_STATS_DSD_ARG_RECVD;
                                if((rc = DeleteSubscriberDataArg_To_DSR(ctxt, &dsda, dsr)) != ITS_SUCCESS)
                                {
                                    delete dsr;
                                    dsr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, dsr, dsr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*dsr, false);
                                break;
                            }
                        case map_common::OP_activateTraceMode:
                            {
                                s6a::InsertSubscriberDataRequest *idr =
                                    new s6a::InsertSubscriberDataRequest();
                                ActivateTraceModeArg atma;
                                Octets octs(buf);
                                atma.Decode(octs);

                                LogAsnObj(atma);
                                DLOG_DEBUG("[MAP:ActivateTraceModeArg] - [s6a:InsertSubscriberDataRequest]");
                                UPDATE_SSG_STATS_ATM_ARG_RECVD;
                                if((rc = ActivateTraceModeArg_To_IDR(ctxt, &atma, idr)) != ITS_SUCCESS)
                                {
                                    delete idr;
                                    idr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, idr, idr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)idr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*idr, false);
                                break;
                            }
                        case map_common::OP_deactivateTraceMode:
                            {
                                s6a::DeleteSubscriberDataRequest *dsr =
                                    new s6a::DeleteSubscriberDataRequest();
                                DeactivateTraceModeArg dtma;
                                Octets octs(buf);
                                dtma.Decode(octs);

                                LogAsnObj(dtma);
                                DLOG_DEBUG("[MAP:DeactivateTraceModeArg] - [s6a:DeleteSubscriberDataRequest]");
                                UPDATE_SSG_STATS_DATM_ARG_RECVD;
                                if((rc = DeactivateTraceModeArg_To_DSR(ctxt, &dtma, dsr)) != ITS_SUCCESS)
                                {
                                    delete dsr;
                                    dsr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, dsr, dsr->getUserName().value().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsr);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*dsr, false);
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
                    // TODO what about RESULT_NL, will we get that?
                    TCAP_Result *tcapRes = static_cast<TCAP_Result*>(cpt);
                    tcapRes->GetOperation(opCode);
                    tcapRes->GetParameter(buf);
                    switch(opCode)
                    {
                        case map_common::OP_updateGprsLocation:
                            {
                                UpdateGprsLocationRes ugla;
                                Octets octs(buf);
                                ugla.Decode(octs);

                                LogAsnObj(ugla);
                                UPDATE_SSG_STATS_UGL_RES_RECVD;

                                DiaCommandCode diaCode = GetLastDiaOperation(ctxt);
                                if (diaCode == DIA_CMD_UL)
                                {
                                    DLOG_DEBUG("[MAP:UpdateGPRSLocationRes] -> "
                                            "[S6a:UpdateLocationAnswer]");

                                    s6a::UpdateLocationAnswer* ula = new s6a::UpdateLocationAnswer();
                                    UpdateGPRSLocationRes_To_ULA(ctxt, &ugla, ula);
                                    SetDefaultAVPsInAns(ctxt, ula);
                                    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ula);
                                    cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                    LogDiaMsg(*ula, false);
                                }
                                else if (diaCode == DIA_CMD_NO)
                                {
                                    DLOG_DEBUG("[MAP:UpdateGPRSLocationRes] -> "
                                            " Consume - NotifyAnswer sent already");
                                    ret.action = IWF_RA_CONSUME;
                                }

                                break;
                            }
                        case map_common::OP_readyForSM:
                            {
                                ReadyForSM_Res rfsr;
                                Octets octs(buf);
                                rfsr.Decode(octs);
                                LogAsnObj(rfsr);
                                DLOG_DEBUG("[MAP:ReadyForSM_Res] -> "
                                        " Consume - NotifyAnswer sent already");
                                ret.action = IWF_RA_CONSUME;
                                UPDATE_SSG_STATS_READY_FOR_SM_RECVD;

                                break;
                            }
                        case map_common::OP_sendAuthenticationInfo:
                            {
                                SendAuthenticationInfoRes sair;
                                Octets octs(buf);
                                sair.Decode(octs);

                                LogAsnObj(sair);

                                UPDATE_SSG_STATS_SAI_RES_RECVD;

                                DLOG_DEBUG("[MAP:SendAuthenticationInfoRes] -> "
                                        "[S6a:AuthenticationInformationAnswer]");

                                s6a::AuthenticationInformationAnswer* aia = new s6a::AuthenticationInformationAnswer();
                                SendAuthenticationInfoResv3_To_AIA(ctxt, &sair, aia);
                                SetDefaultAVPsInAns(ctxt, aia);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)aia);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*aia, false);

                                break;
                            }
                        case map_common::OP_purgeMS:
                            {
                                PurgeMS_Res puMsa;
                                Octets octs(buf);
                                puMsa.Decode(octs);

                                LogAsnObj(puMsa);

                                UPDATE_SSG_STATS_PURGE_RES_RECVD;

                                DLOG_DEBUG("[MAP:PurgeMS_Res] -> "
                                        "[S6a:PurgeUEAnswer]");

                                s6a::PurgeUEAnswer* pua = new s6a::PurgeUEAnswer();
                                PurgeMS_Resv3_To_PUA(ctxt, &puMsa, pua);
                                SetDefaultAVPsInAns(ctxt, pua);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)pua);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*pua, false);

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
                        case DIA_CMD_UL:
                            {
                                s6a::UpdateLocationAnswer* ula = new s6a::UpdateLocationAnswer(true);
                                UPDATE_SSG_STATS_UGL_ERROR_RECVD;
                                BuildErrorResponse(tcapError, ula);
                                SetDefaultAVPsInAns(ctxt, ula);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ula);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*ula, false);
                                break;
                            }
                        case DIA_CMD_AI:
                            {
                                s6a::AuthenticationInformationAnswer* aia = new s6a::AuthenticationInformationAnswer(true);
                                UPDATE_SSG_STATS_SAI_ERROR_RECVD;
                                BuildErrorResponse(tcapError, aia);
                                SetDefaultAVPsInAns(ctxt, aia);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)aia);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*aia, false);
                                break;
                            }
                        case DIA_CMD_PU:
                            {
                                s6a::PurgeUEAnswer* pua = new s6a::PurgeUEAnswer(true);
                                UPDATE_SSG_STATS_PURGE_ERROR_RECVD;
                                BuildErrorResponse(tcapError, pua);
                                SetDefaultAVPsInAns(ctxt, pua);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)pua);
                                cmd->SetDictId(DIA_S6A_REL10_DICTID);

                                LogDiaMsg(*pua, false);
                                break;
                            }
                        case DIA_CMD_NO:
                            {
                                ret.action = IWF_RA_CONSUME;
                                break;
                            }
                        default:
                            {
                                // TODO log an error
                                break;
                            }
                    }

                    break;
                }
            default:
                {
                    DLOG_ERROR("Unexpected cptType %d received", cptType);
                    rc = !ITS_SUCCESS;
                    ret.action = IWF_RA_ERROR;
                    ret.dir = IWF_RD_TCAP;
                }
        }

    }
    catch(AsnDecodeError &exc)
    {
        DLOG_ERROR("### ASN Decode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }

    DLOG_DEBUG("S6aToMAPHandler::BuildDiaMsg Exit");
    return rc;
}

int S6aToMAPHandler::BuildInterimTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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

    // TODO handle activateTrace
    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(in);
    tcapIvk->GetOperation(opCode);
    if (opCode != map_common::OP_insertSubscriberData)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }

    try
    {
        InsertSubscriberDataArg isda;
        tcapIvk->GetParameter(buf);

        Octets oct(buf);
        isda.Decode(oct);

        LogAsnObj(isda);
        DLOG_DEBUG("[MAP:InsertSubscriberData] -> [S6a:SubscriptionData AVP]");

        s6a::SubscriptionData *subsData = new s6a::SubscriptionData();
        InsertSubscriberDataArg_To_SubscriptionData(ctxt, &isda, subsData);

        S6aMAPTransactionContext* userData =
            reinterpret_cast<S6aMAPTransactionContext*>(ctxt->GetStoredUserData());
        if (userData == NULL)
        {
            userData = new S6aMAPTransactionContext();
            ctxt->SetStoredUserData(userData);
            userData->SetSubscriptionData(subsData);
        }
        else if (userData->GetSubscriptionData() == NULL)
        {
            userData->SetSubscriptionData(subsData);
        }
        else
        {
            userData->UpdateSubscriptionData(subsData);
        }

        InsertSubscriberDataRes isdr;
        ConstructInserSubsciberDataRes(ctxt, &isda, &isdr);

        Octets* buf = isdr.Encode();

        TCAP_Result* res = new TCAP_Result();
        res->SetOperation(map_common::OP_insertSubscriberData);
        res->SetInvokeID(tcapIvk->GetInvokeID());
        res->SetParameter(buf->GetArray());
        out = res;
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }

        LogAsnObj(isdr, false);

        ret.action = IWF_RA_RESPOND_ONLY;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("### Unknown exception on Decode ###");
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
    }

    return rc;
}

int S6aToMAPHandler::BuildDiaResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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
            if (code == DIA_CMD_NO)
            {
                // The only diameter response now is the Notify Answer
                s6a::NotifyRequest nor(cmd->getImpl());

                DLOG_DEBUG("Constructing NotifyAnswer for NotifyRequest");
                s6a::NotifyAnswer *noa = new s6a::NotifyAnswer();

                ConstructNOA(ctxt, &nor, noa);
                SetDefaultAVPsInAns(ctxt, noa);

                LogDiaMsg(*noa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)noa);
                out->SetDictId(DIA_S6A_REL10_DICTID);
                ret.action = IWF_RA_RESPOND_ONLY;
            }
        }
        else
        {
            // Answer not expected
            ret.action = IWF_RA_DROP;
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

int S6aToMAPHandler::BuildDiaErrorAnswer(IwfFsm *ctxt, int cmdCode, int error, DIA_BASE_CMD **out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::BuildDiaErrorResponse Entry ");
    int rc = ITS_SUCCESS;
    *out = NULL;

    switch(cmdCode)
    {
        case DIA_CMD_UL:
            {
                s6a::UpdateLocationAnswer *ula = new s6a::UpdateLocationAnswer();
                ConstructErrorAnswer(error, ula);
                SetDefaultAVPsInAns(ctxt, ula);
                LogDiaMsg(*ula, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand* )ula);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        case DIA_CMD_AI:
            {
                s6a::AuthenticationInformationAnswer *aia = new s6a::AuthenticationInformationAnswer();
                ConstructErrorAnswer(error, aia);
                SetDefaultAVPsInAns(ctxt, aia);
                LogDiaMsg(*aia, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand* ) aia);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        case DIA_CMD_PU:
            {
                s6a::PurgeUEAnswer *pua = new s6a::PurgeUEAnswer();
                ConstructErrorAnswer(error, pua);
                SetDefaultAVPsInAns(ctxt, pua);
                LogDiaMsg(*pua, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand* ) pua);
                (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                break;
            }
        case DIA_CMD_NO:
            {
                s6a::NotifyAnswer *no = new s6a::NotifyAnswer();
                ConstructErrorAnswer(error, no);
                SetDefaultAVPsInAns(ctxt, no);
                LogDiaMsg(*no, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand* ) no);
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

int S6aToMAPHandler::BuildDiaErrorResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::BuildDiaErrorResponse Entry ");
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;
    const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();

    try
    {
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (cmd->isRequest())
        {
            if (code == DIA_CMD_UL)
            {
                DLOG_DEBUG("Constructing ULR out of diaCmd");
                s6a::UpdateLocationRequest ulr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code ==DIA_CMD_AI)
            {
                DLOG_DEBUG("Constructing AIR out of diaCmd");
                s6a::AuthenticationInformationRequest air(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_PU)
            {
                DLOG_DEBUG("Constructing PUR out of diaCmd");
                s6a::PurgeUERequest pur(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if(code == DIA_CMD_NO)
            {
                DLOG_DEBUG("Constructing NOR out of diaCmd");
                s6a::NotifyRequest nor(cmd->getImpl());
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
        DLOG_DEBUG("errorcode for commandCode %d is %d", cmd->getCommandCode(), e.errcode());
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
        DLOG_ERROR("#### Unknown Exception on BuildDiaErrorResponse ####");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
    }

    return rc;
}

int S6aToMAPHandler::ULR_To_UpdateGPRSLocationArg(
        IwfFsm *ctxt,
        const s6a::UpdateLocationRequest *in,
        UpdateGprsLocationArg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to IMSI
    std::string simsi = in->getUserName().value();
    std::string temp(simsi.substr(0, simsi.find('@')));
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    // TODO: FIX is required on ARRAY Size. It can not have static array size IMSI could vary
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    string RuleName("");
    int32_t serviceKey = WILDCARD_SERVICE_KEY;
    int32_t ossn = HLR;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(temp,serviceKey,RuleName,ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return !ITS_SUCCESS;
    }
    bool vplmnIdRcvd = false;
    uint8_t plmn[3] = {0};
    // Visited-PLMN-ID
    if (in->getVisitedPLMNId().value().size() < MAP_GR_REQUESTING_PLMN_ID_SZ)
    {
        DLOG_ERROR("Could not extract %d bytes of requestingPLMN-Id",
                in->getVisitedPLMNId().value().size());
    }
    else
    {
        for(unsigned int i = 0; i < in->getVisitedPLMNId().value().size(); i++)
        {
            plmn[i] = in->getVisitedPLMNId().value()[i];
        }
        vplmnIdRcvd = true;
        if(IwfController::Instance().Config().LocalConfig().IsVplmnIdToBeValidated() && 
                IWFUtils::CompareVplmnId(&plmn[0], temp,RuleName))
        {
            DLOG_ERROR("VplmnId does not match the configured value for ULR");
            ctxt->SetErrorCode(DIAMETER_ERROR_ROAMING_NOT_ALLOWED);
            return !ITS_SUCCESS;
        }
    }

    // Update the session context
    SessionCtxt *sctxt = ctxt->GetTransactionManager()->GetSessionCtxt(temp);
    if (sctxt &&
            in->getOriginHost().value().compare(sctxt->GetOriginHost()))
    {
        // Update the OriginHost to the new host
        sctxt->UpdateOldHostRealm();
        std::string& origHost = const_cast<std::string&>(in->getOriginHost().value());
        sctxt->SetOriginHost(origHost);
        std::string& origRealm = const_cast<std::string&>(in->getOriginRealm().value());
        sctxt->SetOriginRealm(origRealm);
        sctxt->UpdateEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, temp);
    }

    // SGSN-Number to sgsn-Number
    if (in->containsSGSNNumber())
    {
        std::string sgsnNum = in->getSGSNNumber().value();
        std::string routing_prefix = "";
        m_config.GetRoutingPrefix(routing_prefix);
        if(!routing_prefix.empty())
        {
            uint8_t svar[20] = {0};
            //NOTE: Add RoutingPrefix prior to SGSN Number
            std::string sgsn_prefix = SGSN_HEADER_DIGITS + routing_prefix;

            int len_of_routPref = IWFUtils::StringToTBCD(sgsn_prefix.substr(0, LENGTH_OF_ADDR_DIGITS),svar,LENGTH_OF_ADDR_DIGITS,0, true);
            len_of_routPref += IWFUtils::StringToTBCD(sgsn_prefix.substr(LENGTH_OF_ADDR_DIGITS),(svar+1),sizeof(sgsn_prefix),0xf0);

            std::vector<byte> rouPrefixVec = IWFUtils::ByteArrayToVector(svar,len_of_routPref);
            std::vector<byte> sgsnNumVec = IWFUtils::StringToVector(sgsnNum);
            rouPrefixVec.insert(rouPrefixVec.end(), sgsnNumVec.begin(), sgsnNumVec.end());

            out->SetSgsn_Number(new ISDN_AddressString((rouPrefixVec)));
        }
    }
    else
    {
        if(IwfController::Instance().Config().LocalConfig().IsLocalSgsnNumberUsedForMapping())
        {
            its::ByteArray outSgsnNum;
            m_config.GetSGSNNumber(outSgsnNum);
            out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
        }
        else
        {
            if(vplmnIdRcvd)
            {
                std::string sgsn_num = "";
                std::string vplmnId = "";
                IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmnId, 0, true);
                DLOG_DEBUG("VplmnId Rcvd in ULR = %s",vplmnId.c_str());
                if(!GetSgsnNumberFromConfig(in->getOriginHost().value(),vplmnId,sgsn_num))
                {
                    DLOG_ERROR("Failed to get SGSN number for OriginHost %s",in->getOriginHost().value().c_str());
                    ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
                    return !ITS_SUCCESS;
                }
                else
                {
                    its::ByteArray outSgsnNum;
                    uint8_t svar[20] = {0};
                    int len = IWFUtils::StringToTBCD(sgsn_num.substr(0,LENGTH_OF_ADDR_DIGITS), svar, 
                            LENGTH_OF_ADDR_DIGITS, 0, true);
                    len += IWFUtils::StringToTBCD(sgsn_num.substr(LENGTH_OF_ADDR_DIGITS), 
                            (svar+1), MAX_SGSN_NUM_LEN, 0x0f);

                    outSgsnNum.assign(svar, svar + len);
                    out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
                }
            }
        }
    }

    // SGSN-Address, obtained from the configuration mapping against OriginHost
    its::ByteArray gsnAddr;
    bool res = m_config.SGSNAddrFromOHost(in->getOriginHost().value(), gsnAddr);
    if (res)
    {
        // The value stored in config is already in GSNAddress format
        out->SetSgsn_Address(new GSN_Address(gsnAddr));
    }
    else
    {
        string ipaddr;
        Generateipv4(ipaddr);
        string orgHost = in->getOriginHost().value();
        m_config.SetSGSNAddrFromOHost(orgHost, ipaddr);
        IWFUtils::IpStringToGSNAddress(ipaddr, gsnAddr);
        out->SetSgsn_Address(new GSN_Address(gsnAddr));
    }

    // SGSN-Capability
    SGSN_Capability *sgsnCapability = new SGSN_Capability();
    BuildSGSNCapability(ctxt, in, sgsnCapability);
    out->SetSgsn_Capability(sgsnCapability);

    if (in->containsTerminalInformation())
    {
        // Terminal-Info to Additional Info
        ADD_Info *oAddInfo = new ADD_Info();
        BuildAddInfo(in->getTerminalInformation(), oAddInfo);
        out->SetAdd_info(oAddInfo);
    }

    {
        unsigned iUlrFlags = in->getULRFlags().value();

        // ULR-Flags to EPS-info
        EPS_Info *oEpsInfo = new EPS_Info();
        BuildEPSInfo(iUlrFlags, oEpsInfo);
        out->SetEps_info(oEpsInfo);

        if (iUlrFlags & ULR_FLAG_S6A_S6D_IND)
        {
            out->SetServingNodeTypeIndicator(
                    new UpdateGprsLocationArg::ServingNodeTypeIndicator());
        }
        if (iUlrFlags & ULR_FLAG_SKIP_SUBSCRIBER_DATA)
        {
            out->SetSkipSubscriberDataUpdate(
                    new UpdateGprsLocationArg::SkipSubscriberDataUpdate());
            // TODO set the transaction context skip subscriber data to true
        }
        if (!(iUlrFlags & ULR_FLAG_GPRS_SUBSCRIPTION_DATA_IND))
        {
            out->SetGprsSubscriptionDataNotNeeded(
                    new UpdateGprsLocationArg::GprsSubscriptionDataNotNeeded());
        }
        if (iUlrFlags & ULR_FLAGS_NODE_TYPE_IND)
        {
            out->SetNodeTypeIndicator(
                    new UpdateGprsLocationArg::NodeTypeIndicator());
        }
    }

    // Used RAT Type
    s6a::RATType::Value iRatType = (s6a::RATType::Value)in->getRATType().value();
    if (iRatType >= s6a::RATType::UTRAN && iRatType <= s6a::RATType::EUTRAN)
    {
        // For other RAT Types there is no mapping
        // s6a values are 1000 to 1004, whereas in MAP the values are 0-4
        Used_RAT_Type *oRatType = new Used_RAT_Type(iRatType - s6a::RATType::UTRAN);
        out->SetUsedRAT_Type(oRatType);
    }

    // UE SRVCC Capability direct mapping
    if (in->containsUESRVCCCapability())
    {
        unsigned ueSrvcc = in->getUESRVCCCapability().value();
        out->SetUe_srvcc_Capability(new UE_SRVCC_Capability(ueSrvcc));
    }
    return ITS_SUCCESS;
}

void S6aToMAPHandler::BuildSGSNCapability(
        IwfFsm *ctxt,
        const s6a::UpdateLocationRequest *in,
        SGSN_Capability *cap)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // By default set the GprsEnhancementsSupportIndicator
    cap->SetGprsEnhancementsSupportIndicator(new
            SGSN_Capability::GprsEnhancementsSupportIndicator());

    // RAT-Type to supportedRAT-TypesIndicator
    unsigned init = 0;
    SupportedRAT_Types* oRatType = new SupportedRAT_Types(
            IWFUtils::UnsignedToBitVector(init, 8));
    s6a::RATType::Value iRatType = (s6a::RATType::Value)in->getRATType().value();
    switch(iRatType)
    {
        case s6a::RATType::UTRAN:
            oRatType->SetUtran();
            break;
        case s6a::RATType::GERAN:
            oRatType->SetGeran();
            break;
        case s6a::RATType::GAN:
            oRatType->SetGan();
            break;
        case s6a::RATType::HSPA_EVOLUTION:
            oRatType->SetI_hspa_evolution();
            break;
        case s6a::RATType::EUTRAN:
            oRatType->SetE_utran();
            break;
        default:
            DLOG_WARNING("Rat-Type %d not supported", iRatType);
    }
    cap->SetSupportedRAT_TypesIndicator(oRatType);

    // SupportedFeatures.FeatureList to supportedFeatures
    unsigned long iFeatures = 0;
    for (int i = 0; i < in->countSupportedFeatures(); i++)
    {
        if (in->getSupportedFeatures(i).getFeatureListID().value() != 1)
        {
            DLOG_WARNING("FeatureList value is not 1 i.e. %d", in->getSupportedFeatures(i).getFeatureListID().value());
            break;
        }
        iFeatures = in->getSupportedFeatures(i).getFeatureList().value();
    }
    //NOTE:supportedFeatures shall be present if a SupportedFeature AVP was present
    //in the received ULR which indicated support of odbs and regsubs.
    //NOTE: If 10th bit position(regional subscription) is set and if any one of first 9 bits(odbs related bits) is set then populate SupportedFeatures
    if ((iFeatures & (1<<9)) && (iFeatures & FEATURE_LIST_ODB_BITS))
    {
        SupportedFeatures *oFeatures = new SupportedFeatures(
                IWFUtils::UnsignedToBitVector(iFeatures, 32));
        cap->SetSupportedFeatures(oFeatures);

        // Set the supported features, to be later used for sending ISDRes
        S6aMAPTransactionContext* userData =
            reinterpret_cast<S6aMAPTransactionContext*>(ctxt->GetStoredUserData());
        if (userData == NULL)
        {
            userData = new S6aMAPTransactionContext();
            ctxt->SetStoredUserData(userData);
        }
        if (userData->HasSupportedFeatures())
        {
            userData->ClearSupportedFeatures();
        }
        SupportedFeatures *clone = new SupportedFeatures(*oFeatures);
        userData->SetSupportedFeatures(clone);
    }
}

void S6aToMAPHandler::BuildAddInfo(
        const s6a::TerminalInformation &ti,
        ADD_Info *oAddInfo, bool skipSubsUpdate)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (ti.containsIMEI())
    {
        uint8_t imeisv[IWF_MAX_E164_SZ/2 + 1];
        std::string iImei, iSoftVer;
        iImei = ti.getIMEI().value();

        // Check if the IMEI is of length more than 14 digits and truncate
        if (iImei.size() > 14)
        {
            iImei.erase(14);
        }

        if (ti.containsSoftwareVersion())
        {
            iSoftVer = ti.getSoftwareVersion().value();
            if (iSoftVer.size() > 2)
            {
                iSoftVer.erase(2);
            }
            iImei += iSoftVer;
        }

        int len = IWFUtils::StringToTBCD(iImei, imeisv, IWF_MAX_E164_SZ, 0x0f);
        oAddInfo->SetImeisv(new IMEI(IWFUtils::ByteArrayToVector(imeisv, len)));
    }

    if (skipSubsUpdate)
    {
        oAddInfo->SetSkipSubscriberDataUpdate(
                new ADD_Info::SkipSubscriberDataUpdate());
    }
}


void S6aToMAPHandler::BuildEPSInfo(unsigned iFlags, EPS_Info *oEpsInfo)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    unsigned init = 0;
    ISR_Information *oIsrInfo = new ISR_Information(
            IWFUtils::UnsignedToBitVector(init, 8));

    if (iFlags & ULR_FLAG_S6A_S6D_IND)
    {
        oIsrInfo->SetUpdateMME();
    }
    if (iFlags & ULR_FLAG_SINGLE_REIGSTRATION_IND || iFlags & NOR_FLAG_SINGLE_REGISTRATION_IND)
    {
        oIsrInfo->SetCancelSGSN();
    }
    if (iFlags & ULR_FLAGS_INITIAL_ATTACH_IND)
    {
        oIsrInfo->SetInitialAttachIndicator();
    }
    oEpsInfo->SetChoiceIsr_Information(oIsrInfo);
}

void S6aToMAPHandler::UpdateGPRSLocationRes_To_ULA(
        IwfFsm *ctxt,
        const UpdateGprsLocationRes *in,
        s6a::UpdateLocationAnswer *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    TCAP_Component* cpt = ctxt->GetCurrRcvdTcapCpt();
    ITS_USHORT cptType = cpt->GetComponentType();

    if (cptType != TCPPT_TC_RESULT_L)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // ULA-Flags
    if (in->OptionSgsn_mmeSeparationSupported())
    {
        // Separation Indication -> bit 0
        out->setULAFlags(s6a::ULAFlags(1));
    }
    else
    {
        out->setULAFlags(s6a::ULAFlags(ITS_UINT(0)));
    }


    S6aMAPTransactionContext* userData =
        reinterpret_cast<S6aMAPTransactionContext*>(ctxt->GetStoredUserData());
    if (userData && userData->HasSubscriptionData())
    {
        out->setSubscriptionData(*userData->GetSubscriptionData());
        userData->ClearSubscriptionData();

        // the user data is no longer required, delete it
        delete userData;
        ctxt->SetStoredUserData(NULL);
    }
}

void S6aToMAPHandler::BuildErrorResponse(
        TCAP_Error *tcapError,
        s6a::UpdateLocationAnswer *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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
    if (errCode != map_common::ERR_unknownSubscriber &&
            errCode != map_common::ERR_roamingNotAllowed)
    {
        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        out->setResultCode(res);
        return;
    }

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
                resCode = DIAMETER_ERROR_USER_UNKNOWN;
                if (oct.GetSize() > 0)
                {
                    UnknownSubscriberParam unkwnSubs;
                    unkwnSubs.Decode(oct);

                    DLOG_DEBUG("Unknown Subscriber IE - decoding optional parameter");
                    LogAsnObj(unkwnSubs);

                    if (unkwnSubs.OptionUnknownSubscriberDiagnostic())
                    {
                        unsigned long diag = unkwnSubs.GetUnknownSubscriberDiagnostic().GetValue();
                        if (diag == UnknownSubscriberDiagnostic::
                                UNKNOWN_SUBSCRIBER_DIAGNOSTIC_GPRS_EPS_SUBSCRIPTION_UNKNOWN)
                        {
                            resCode = DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION;
                        }
                    }
                }
                else
                {
                    DLOG_DEBUG("Unknown Subscriber IE - no optional parameter present");
                }
                break;
            }
        case map_common::ERR_roamingNotAllowed:
            {
                resCode = DIAMETER_ERROR_ROAMING_NOT_ALLOWED;
                if (oct.GetSize() > 0)
                {
                    RoamingNotAllowedParam roamNot;
                    roamNot.Decode(oct);

                    DLOG_DEBUG("Roaming Not Allowed IE - decoding optional parameter");

                    LogAsnObj(roamNot);

                    if (roamNot.OptionAdditionalRoamingNotAllowedCause())
                    {
                        unsigned long diag = roamNot.GetAdditionalRoamingNotAllowedCause().GetValue();
                        if (diag == 0)
                        {
                            // SUPPORTED_RAT_TYPES_NOT_ALLOWED
                            resCode = DIAMETER_ERROR_RAT_NOT_ALLOWED;
                        }
                    }
                }
                else
                {
                    DLOG_DEBUG("Roaming Not Allowed IE - no optional parameter present");
                }
                break;
            }
        default:
            // should not reach this
            break;
    }
    res.setExperimentalResultCode(diameter::base::ExperimentalResultCode(resCode));
    out->setExperimentalResult(res);
}
template <class T>
void S6aToMAPHandler::BuildErrorResponse(
        TCAP_Error *tcapError,
        T *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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
    if (errCode != map_common::ERR_unknownSubscriber)
    {
        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        out->setResultCode(res);
        return;
    }

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
                resCode = DIAMETER_ERROR_USER_UNKNOWN;
                if (oct.GetSize() > 0)
                {
                    UnknownSubscriberParam unkwnSubs;
                    unkwnSubs.Decode(oct);

                    LogAsnObj(unkwnSubs);

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
                }
                break;
            }
        default:
            // should not reach this
            break;
    }

    res.setExperimentalResultCode(diameter::base::ExperimentalResultCode(resCode));
    out->setExperimentalResult(res);
}

void S6aToMAPHandler::InsertSubscriberDataArg_To_SubscriptionData(
        IwfFsm *ctxt,
        const InsertSubscriberDataArg *in,
        s6a::SubscriptionData *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (in->OptionSubscriberStatus())
    {
        out->setSubscriberStatus(s6a::SubscriberStatus(
                    (s6a::SubscriberStatus::Value)in->GetSubscriberStatus().GetValue()));
    }

    // MSISDN to MSISDN (tbcd string) - no conversion required
    if (in->OptionMsisdn())
    {
        const std::vector<byte>& msisdn = in->GetMsisdn().GetArray();
        out->setMSISDN(s6a::MSISDN(IWFUtils::VectorToString(msisdn)));
    }

    // EPS Subscription
    if (in->OptionEps_SubscriptionData())
    {
        const EPS_SubscriptionData& iEpsSubsData = in->GetEps_SubscriptionData();
        if (iEpsSubsData.OptionStn_sr())
        {
            // tbcd string to tbcd string
            const std::vector<byte>& stn_sr = iEpsSubsData.GetStn_sr().GetArray();
            out->setSTNSR(s6a::STNSR(IWFUtils::VectorToString(stn_sr)));
        }

        // apn-oi-Replacement to APN-OI-Replacement
        if (iEpsSubsData.OptionApn_oi_Replacement())
        {
            out->setAPNOIReplacement(s6a::APNOIReplacement(IWFUtils::VectorToString
                        (iEpsSubsData.GetApn_oi_Replacement().GetArray())));
        }

        // ambr to AMBR (sequence to grouped)
        if (iEpsSubsData.OptionAmbr())
        {
            uint32_t ul, dl;
            const AMBR& iAmbr = iEpsSubsData.GetAmbr();
            ul = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_UL().GetValue());
            dl = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_DL().GetValue());

            s6a::AMBR oAmbr;
            oAmbr.setMaxRequestedBandwidthUL(s6a::MaxRequestedBandwidthUL(ul));
            oAmbr.setMaxRequestedBandwidthDL(s6a::MaxRequestedBandwidthDL(dl));

            out->setAMBR(oAmbr);
        }

        // apn_ConfigurationProfile to APN
        if (iEpsSubsData.OptionApn_ConfigurationProfile())
        {
            s6a::APNConfigurationProfile oAcp;
            BuildAPNConfigurationProfile(
                    iEpsSubsData.GetApn_ConfigurationProfile(), oAcp);
            out->setAPNConfigurationProfile(oAcp);
        }

        // rfsp-id RAT-Frequency-Selection-Priority-ID
        if (iEpsSubsData.OptionRfsp_id())
        {
            out->setRATFrequencySelectionPriorityID(
                    s6a::RATFrequencySelectionPriorityID(
                        iEpsSubsData.GetRfsp_id().GetValue()));
        }

    }

    // Network Access Mode ENUM -> ENUM
    if (in->OptionNetworkAccessMode())
    {
        out->setNetworkAccessMode(s6a::NetworkAccessMode(
                    (s6a::NetworkAccessMode::Value)in->GetNetworkAccessMode().GetValue()));
    }

    if (in->OptionOdb_Data())
    {
        // Odb_data is mandatory and hence no checking
        const ODB_Data& odbData = in->GetOdb_Data();

        // ODB general data to Operator-Determined-Barring
        BuildOperatorDeterminedBarring(odbData.GetOdb_GeneralData(), out);

        // odb-Data.odb-HPLN-Data to Subscription-Data.HPLMN-ODB (bit string)
        if (odbData.OptionOdb_HPLMN_Data())
        {
            uint32_t hplnVal = IWFUtils::BitVectorToUnsigned(
                    odbData.GetOdb_HPLMN_Data().GetArray());
            out->setHPLMNODB(s6a::HPLMNODB(hplnVal));
        }
    }

    // Sequence of ZoneCode to *RegionalSubscriptionZoneCode
    if (in->OptionRegionalSubscriptionData())
    {
        const ZoneCodeList &zcList = in->GetRegionalSubscriptionData();
        for (unsigned i = 0; i < zcList.GetSize(); i++)
        {
            out->addRegionalSubscriptionZoneCode(
                    s6a::RegionalSubscriptionZoneCode(
                        IWFUtils::VectorToString(zcList.ElementAt(i).GetArray())));
        }
    }

    // accessRestrictionData to AccessRestrictionData (bit string)
    if (in->OptionAccessRestrictionData())
    {
        const std::vector<bool>& ardVec = in->GetAccessRestrictionData().GetArray();
        DLOG_DEBUG("Access Restriction Data present: %d => [ %d %d %d %d %d ]", ardVec.size(), ardVec[0], ardVec[1], ardVec[2], ardVec[3], ardVec[4]);
        out->setAccessRestrictionData(s6a::AccessRestrictionData(
                    IWFUtils::BitVectorToUnsigned(ardVec)));
        DLOG_DEBUG("Access Restriction Data value: %d",  IWFUtils::BitVectorToUnsigned(ardVec));
    }

    // Charging Characteristics HexByteArray to HexString
    if (in->OptionChargingCharacteristics())
    {
        std::string hexStr;
        const std::vector<byte>& arr = in->GetChargingCharacteristics().GetArray();
        IWFUtils::ByteArrayToHexString(arr, hexStr);
        out->setS6a3GPPChargingCharacteristics(
                s6a::S6a3GPPChargingCharacteristics(hexStr));
    }

    // gprsSubscriptionData to GPRS-Subscription-Data
    if (in->OptionGprsSubscriptionData())
    {
        s6a::GPRSSubscriptionData oGsd;
        BuildGPRSSubscriptionData(in->GetGprsSubscriptionData(), oGsd);
        out->setGPRSSubscriptionData(oGsd);
    }

    // lcsInformation to LCS-Info
    if (in->OptionLcsInformation())
    {
        s6a::LCSInfo oLcsInfo;
        BuildLCSInfo(in->GetLcsInformation(), oLcsInfo);
        out->setLCSInfo(oLcsInfo);
    }

    // csg-SubscriptionDataList to *CSG-Subscription-Data
    if (in->OptionCsg_SubscriptionDataList())
    {
        const CSG_SubscriptionDataList& iList = in->GetCsg_SubscriptionDataList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            s6a::CSGSubscriptionData oCSD;
            BuildCSGSubscriptionData(iList.ElementAt(i), oCSD);
            out->addCSGSubscriptionData(oCSD);
        }
    }

    // roamingRestrictedInSgsnDueToUnsupportedFeature (NULL) ->
    //  Roaming-Restricted-Due-To-Unsupported-Feature ENUM
    if (in->OptionRoamingRestrictedInSgsnDueToUnsupportedFeature())
    {
        // Roaming_Restricted_Due_To_Unsupported_Feature (0)
        out->setRoamingRestrictedDueToUnsupportedFeature(
                s6a::RoamingRestrictedDueToUnsupportedFeature(s6a::RoamingRestrictedDueToUnsupportedFeature::Roaming_Restricted_Due_To_Unsupported_Feature));
    }

    // TeleserviceList to TeleserviceList (Array to Grouped)
    if (in->OptionTeleserviceList())
    {
        s6a::TeleserviceList oTsl;
        const TeleserviceList& iList = in->GetTeleserviceList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            oTsl.addTSCode(s6a::TSCode(
                        IWFUtils::VectorToString(iList.ElementAt(i).GetArray())));
        }
        out->setTeleserviceList(oTsl);
    }

    // provisionedSS Ext-SS-InfoList  --> Call-Barring-Infor-List
    if (in->OptionProvisionedSS())
    {
        s6a::CallBarringInforList oList;
        const Ext_SS_InfoList& iList = in->GetProvisionedSS();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            const Ext_SS_Info& iSSInfo = iList.ElementAt(i);
            if (iSSInfo.ChoiceCallBarringInfo())
            {
                oList.addSSCode(s6a::SSCode(IWFUtils::VectorToString(
                                iSSInfo.GetChoiceCallBarringInfo().GetSs_Code().GetArray())));
            }
        }
        out->setCallBarringInforList(oList);
    }

    // mdtUserConsent (BOO) --> MDT-User-Consent (ENUM)
    if (in->OptionMdtUserConsent())
    {
        bool flag = in->GetMdtUserConsent().GetValue();
        unsigned val = flag ? s6a::MDTUserConsent::CONSENT_GIVEN :
            s6a::MDTUserConsent::CONSENT_NOT_GIVEN;
        out->setMDTUserConsent(s6a::MDTUserConsent(
                    (s6a::MDTUserConsent::Value)val));
    }
}


void S6aToMAPHandler::BuildOperatorDeterminedBarring(
        const ODB_GeneralData &iOdb,
        s6a::SubscriptionData *oSubsData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint32_t odbVal = 0;

    // 0    All Packet Oriented Services Barred
    //  maps to allPacketOrientedServicesBarred(15)
    if (iOdb.IsAllPacketOrientedServicesBarredSet())
    {
        odbVal |= (1<<0);
    }

    // 1    Roamer Access HPLMN-AP Barred
    //  maps to roamerAccessToHPLMN-AP-Barred(16)
    if (iOdb.IsRoamerAccessToHPLMN_AP_BarredSet())
    {
        odbVal |= (1<<1);
    }

    // 2    Roamer Access to VPLMN-AP Barred
    //  maps to roamerAccessToVPLMN-AP-Barred(17)
    if (iOdb.IsRoamerAccessToVPLMN_AP_BarredSet())
    {
        odbVal |= (1<<2);
    }

    // 3    Barring of all outgoing calls
    //  maps to allOG-CallsBarred (0)
    if (iOdb.IsAllOG_CallsBarredSet())
    {
        odbVal |= (1<<3);
    }

    // 4    Barring of all outgoing international calls
    //  maps to internationalOGCallsBarred(1)
    if (iOdb.IsInternationalOGCallsBarredSet())
    {
        odbVal |= (1<<4);
    }

    // 5    Barring of all outgoing international calls except those directed
    //          to the home PLMN country
    //  maps to internationalOGCallsNotToHPLMN-CountryBarred (2)
    if (iOdb.IsInternationalOGCallsNotToHPLMN_CountryBarredSet())
    {
        odbVal |= (1<<5);
    }

    // 6    Barring of all outgoing inter-zonal calls
    //  maps to interzonalOGCallsBarred (6)
    if (iOdb.IsInterzonalOGCallsBarredSet())
    {
        odbVal |= (1<<6);
    }

    // 7    Barring of all outgoing inter-zonal calls except those directed
    //          to the home PLMN country
    //  maps to interzonalOGCallsNotToHPLMN-CountryBarred(7)
    if (iOdb.IsInterzonalOGCallsNotToHPLMN_CountryBarredSet())
    {
        odbVal |= (1<<7);
    }

    // 8    Barring of all outgoing international calls except those directed to
    //      the home PLMN country and Barring of all outgoing inter-zonal calls
    //  maps to interzonalOGCallsAndInternationalOGCallsNotToHPLMN-CountryBarred (8)
    if (iOdb.IsInterzonalOGCallsAndInternationalOGCallsNotToHPLMN_CountryBarredSet())
    {
        odbVal |= (1<<8);
    }

    oSubsData->setOperatorDeterminedBarring(s6a::OperatorDeterminedBarring(odbVal));
}


void S6aToMAPHandler::BuildAPNConfigurationProfile(
        const APN_ConfigurationProfile& in,
        s6a::APNConfigurationProfile& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // defaultContext   ContextId,  -> Context-Identifier
    out.setContextIdentifier(s6a::ContextIdentifier(
                in.GetDefaultContext().GetValue()));

    // completeDataListIncluded NULL, -> All-APN-Configurations-Included-Indicator
    if (in.OptionCompleteDataListIncluded())
    {
        // set it to All_APN_CONFIGURATIONS_INCLUDED
        out.setAllAPNConfigurationsIncludedIndicator(
                s6a::AllAPNConfigurationsIncludedIndicator(s6a::AllAPNConfigurationsIncludedIndicator::Value(0)));
    }
    else
    {
        // set it to MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED
        out.setAllAPNConfigurationsIncludedIndicator(
                s6a::AllAPNConfigurationsIncludedIndicator(s6a::AllAPNConfigurationsIncludedIndicator::Value(1)));
    }

    // epsDataList  [1] EPS-DataList, -> *APN-Configuration
    const EPS_DataList& dlist = in.GetEpsDataList();
    for (unsigned i = 0; i < dlist.GetSize(); i++)
    {
        s6a::APNConfiguration oAc;
        BuildAPNConfiguration(dlist.ElementAt(i), oAc);
        out.addAPNConfiguration(oAc);
    }

}


void S6aToMAPHandler::BuildAPNConfiguration(
        const APN_Configuration& in, s6a::APNConfiguration &out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //  contextId       [0] ContextId, --> Context-Identifier
    out.setContextIdentifier(s6a::ContextIdentifier(in.GetContextId().GetValue()));

    //  pdn-Type        [1] PDN-Type, --> PDN-Type (2 bytes to ENUM)
    //   Octet0: 7-4 bits -> F, 3-0 -> Type (0 ETSI, 1 IETF)
    //   Octet1: 0x21 - IPv4, 0x57 - IPv6, and 0x8D - IPv4IPv6
    std::vector<byte> iPdnType = in.GetPdn_Type().GetArray();
    uint32_t oPdnType = 0;

    if (iPdnType[1] == 0x21) oPdnType = s6a::PDNType::IPv4;
    else if (iPdnType[1] == 0x57) oPdnType = s6a::PDNType::IPv6;
    else if (iPdnType[1] == 0x8D) oPdnType = s6a::PDNType::IPv4v6;

    out.setPDNType(s6a::PDNType((s6a::PDNType::Value)oPdnType));

    //  servedPartyIP-IPv4-Address  [2] PDP-Address, --> Served-Party-IP-Address
    //  servedPartyIP-IPv6-Address  [12] PDP-Address, --> Served-Party-IP-Address
    if (in.OptionServedPartyIP_IPv4_Address())
    {
        std::string oStr;
        const uint8_t *iPdpAddr = &(in.GetServedPartyIP_IPv4_Address().GetArray()[0]);
        int len = in.GetServedPartyIP_IPv4_Address().GetArray().size();

        // IWFUtils::IPAddrToString(AF_INET, iPdpAddr, oStr);
        out.addServedPartyIPAddress(s6a::ServedPartyIPAddress(
                    diameter::Address(diameter::Address::IPV4, (const char*)iPdpAddr, len)));
    }
    if (in.OptionServedPartyIP_IPv6_Address())
    {
        std::string oStr;
        const uint8_t *iPdpAddr = &(in.GetServedPartyIP_IPv6_Address().GetArray()[0]);
        int len = in.GetServedPartyIP_IPv6_Address().GetArray().size();

        // IWFUtils::IPAddrToString(AF_INET6, iPdpAddr, oStr);
        out.addServedPartyIPAddress(s6a::ServedPartyIPAddress(
                    diameter::Address(diameter::Address::IPV6, (const char*)iPdpAddr, len)));
    }

    //  apn         [3] APN, --> Service-Selection UT8String with '.'
    std::string oApn;
    IWFUtils::LabelsToString(in.GetApn().GetArray(), oApn);
    out.setServiceSelection(s6a::ServiceSelection(oApn));

    //  eps-qos-Subscribed  [4] EPS-QoS-Subscribed, --> EPS-Subscribed-QoS-Profile
    //  (grouped)
    //      qos-Class-Identifier    -> QOS-Class-Identifier (int to enum)
    //      allocation-Retention-Priority -> Allocation-Retention-Priority (grouped)
    //          priority-level ->    {Priority-Level} (integer)
    //          pre-emption-capability -> [Pre-emption-Capability] (bool to enum)
    //          pre-emption-vulnerability -> [Pre-emption-Vulnerability] (bool to enum)
    {
        s6a::EPSSubscribedQoSProfile oQos;
        const EPS_QoS_Subscribed& iQos = in.GetEps_qos_Subscribed();

        oQos.setQoSClassIdentifier(s6a::QoSClassIdentifier(
                    (s6a::QoSClassIdentifier::Value)
                    iQos.GetQos_Class_Identifier().GetValue()));
        {
            s6a::AllocationRetentionPriority oArp;
            const Allocation_Retention_Priority& iArp =
                iQos.GetAllocation_Retention_Priority();

            oArp.setPriorityLevel(s6a::PriorityLevel(
                        iArp.GetPriority_level().GetValue()));

            if (iArp.OptionPre_emption_capability())
            {
                oArp.setPreemptionCapability(s6a::PreemptionCapability(
                            s6a::PreemptionCapability::PRE_EMPTION_CAPABILITY_ENABLED));
            }
            else
            {
                oArp.setPreemptionCapability(s6a::PreemptionCapability(
                            s6a::PreemptionCapability::PRE_EMPTION_CAPABILITY_DISABLED));
            }

            if (iArp.OptionPre_emption_vulnerability())
            {
                oArp.setPreemptionVulnerability(s6a::PreemptionVulnerability(
                            s6a::PreemptionVulnerability::PRE_EMPTION_VULNERABILITY_ENABLED));
            }
            else
            {
                oArp.setPreemptionVulnerability(s6a::PreemptionVulnerability(
                            s6a::PreemptionVulnerability::PRE_EMPTION_VULNERABILITY_DISABLED));
            }
            oQos.setAllocationRetentionPriority(oArp);
        }

        out.setEPSSubscribedQoSProfile(oQos);
    }


    //  pdn-gw-Identity --> Visited-Network-Identifier
    if (in.OptionPdn_gw_Identity())
    {
        const PDN_GW_Identity& pgwId = in.GetPdn_gw_Identity();
        if (pgwId.OptionPdn_gw_name())
        {
            out.setVisitedNetworkIdentifier(s6a::VisitedNetworkIdentifier(
                        IWFUtils::VectorToString(pgwId.GetPdn_gw_name().GetArray())));
        }
    }

    //  pdn-gw-AllocationType   --> PDN-GW-Allocation-Type (enum - enum)
    if (in.OptionPdn_gw_AllocationType())
    {
        out.setPDNGWAllocationType(s6a::PDNGWAllocationType(
                    (s6a::PDNGWAllocationType::Value)
                    in.GetPdn_gw_AllocationType().GetValue()));
    }

    //  vplmnAddressAllowed -> VPLMN-Dynamic-Address-Allowed (NULL to enum)
    if (in.OptionVplmnAddressAllowed())
    {
        // NOTALLOWED - 0   ALLOWED - 1
        out.setVPLMNDynamicAddressAllowed(s6a::VPLMNDynamicAddressAllowed(
                    s6a::VPLMNDynamicAddressAllowed::ALLOWED));
    }

    //  chargingCharacteristics --> S6a-3GPP-Charging-Characteristics
    // Charging Characteristics HexByteArray to HexString
    if (in.OptionChargingCharacteristics())
    {
        std::string hexStr;
        const std::vector<byte>& arr = in.GetChargingCharacteristics().GetArray();
        IWFUtils::ByteArrayToHexString(arr, hexStr);
        out.setS6a3GPPChargingCharacteristics(
                s6a::S6a3GPPChargingCharacteristics(hexStr));
    }

    //  ambr  --> AMBR
    // ambr to AMBR (sequence to grouped)
    if (in.OptionAmbr())
    {
        uint32_t ul, dl;
        const AMBR& iAmbr = in.GetAmbr();
        ul = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_UL().GetValue());
        dl = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_DL().GetValue());

        s6a::AMBR oAmbr;
        oAmbr.setMaxRequestedBandwidthUL(s6a::MaxRequestedBandwidthUL(ul));
        oAmbr.setMaxRequestedBandwidthDL(s6a::MaxRequestedBandwidthDL(dl));

        out.setAMBR(oAmbr);
    }

    //  specificAPNInfoList --> *Specific-APN-Info
    if (in.OptionSpecificAPNInfoList())
    {
        const SpecificAPNInfoList& iList = in.GetSpecificAPNInfoList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            // In each SpecifiAPNList
            //  apn --> Service-Selection
            //  pdn-gw-identity --> Visited-Network-Identifier
            std::string oApnStr;
            s6a::SpecificAPNInfo osApnInfo;
            s6a::MIP6AgentInfo mipai;
            const SpecificAPNInfo& isApn = iList.ElementAt(i);

            IWFUtils::LabelsToString(isApn.GetApn().GetArray(), oApnStr);
            osApnInfo.setServiceSelection(s6a::ServiceSelection(oApnStr));

            osApnInfo.setMIP6AgentInfo(mipai);

            const PDN_GW_Identity& pgwId = isApn.GetPdn_gw_Identity();
            if (pgwId.OptionPdn_gw_name())
            {
                osApnInfo.setVisitedNetworkIdentifier(
                        s6a::VisitedNetworkIdentifier(
                            IWFUtils::VectorToString(pgwId.GetPdn_gw_name().GetArray())));
            }

            out.addSpecificAPNInfo(osApnInfo);
        }
    }


    //  apn-oi-Replacement  --> APN-OI-Replacement
    if (in.OptionApn_oi_Replacement())
    {
        out.setAPNOIReplacement(s6a::APNOIReplacement(IWFUtils::VectorToString
                    (in.GetApn_oi_Replacement().GetArray())));
    }

    //  sipto-Permission   -->  SIPTO-Permission
    if (in.OptionSipto_Permission())
    {
        out.setSIPTOPermission(s6a::SIPTOPermission(
                    (s6a::SIPTOPermission::Value)in.GetSipto_Permission().GetValue()));
    }

    //  lipa-Permission    -->  LIPA-Permission
    if (in.OptionLipa_Permission())
    {
        out.setLIPAPermission(s6a::LIPAPermission(
                    (s6a::LIPAPermission::Value)in.GetLipa_Permission().GetValue()));
    }

}

void S6aToMAPHandler::BuildGPRSSubscriptionData(
        const GPRSSubscriptionData& in,
        s6a::GPRSSubscriptionData& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // completeDataListIncluded NULL -->
    //      Complete-Data-List-Included-Indicator(0/1)
    if (in.OptionCompleteDataListIncluded())
    {
        // set it to All_APN_CONFIGURATIONS_INCLUDED
        out.setCompleteDataListIncludedIndicator(
                s6a::CompleteDataListIncludedIndicator(0));
    }
    else
    {
        // set it to MODIFIED_ADDED_APN_CONFIGURATIONS_INCLUDED
        out.setCompleteDataListIncludedIndicator(
                s6a::CompleteDataListIncludedIndicator(s6a::CompleteDataListIncludedIndicator::MODIFIED_ADDED_PDP_CONTEXTS_INCLUDED));
    }

    // gprsDataList -> *PDP-Context
    const GPRSDataList& dlist = in.GetGprsDataList();
    for (unsigned i = 0; i < dlist.GetSize(); i++)
    {
        s6a::PDPContext oPdp;
        BuildPDPContext(dlist.ElementAt(i), oPdp);
        out.addPDPContext(oPdp);
    }

}

void S6aToMAPHandler::BuildPDPContext(const PDP_Context& in, s6a::PDPContext& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //  pdp-contextId --> Context-Identifier
    out.setContextIdentifier(s6a::ContextIdentifier(
                in.GetPdp_ContextId().GetValue()));

    //  pdp-Type --> PDP-Type (2 bytes to Oct string)
    const std::vector<byte>& iPdpType = in.GetPdp_Type().GetArray();
    out.setPDPType(s6a::PDPType(IWFUtils::VectorToString(iPdpType)));

    // pdp-Address  --> PDP-Address, address type based on family
    if (in.OptionPdp_Address())
    {
        const std::vector<byte>& iAddr = in.GetPdp_Address().GetArray();
        diameter::Address::Family family = (iPdpType[1] == 0x21) ?
            diameter::Address::IPV4 :
            (iPdpType[1] == 0x57) ? diameter::Address::IPV6:
            diameter::Address::RESERVED;
        out.setPDPAddress(s6a::PDPAddress(
                    diameter::Address(family, (const char*)&iAddr[0], iAddr.size())));
    }

    // Concatenation
    // QoS-Subscribed, Ext-QoS-Subscribed, Ext2-QoS-Subscribed,
    // Ext3-QoS-Subscribed and Ext4-QoS-Subscribed --> QosSubscribed
    std::vector<byte> qos = in.GetQos_Subscribed().GetArray();
    if (in.OptionExt_QoS_Subscribed())
    {
        IWFUtils::VectorAppend(qos, in.GetExt_QoS_Subscribed().GetArray());
        if (in.OptionExt2_QoS_Subscribed())
        {
            IWFUtils::VectorAppend(qos, in.GetExt2_QoS_Subscribed().GetArray());
            if (in.OptionExt3_QoS_Subscribed())
            {
                IWFUtils::VectorAppend(
                        qos, in.GetExt3_QoS_Subscribed().GetArray());
                if (in.OptionExt4_QoS_Subscribed())
                {
                    IWFUtils::VectorAppend(
                            qos, in.GetExt4_QoS_Subscribed().GetArray());
                }
            }
        }
    }
    out.setQoSSubscribed(s6a::QoSSubscribed(IWFUtils::VectorToString(qos)));

    //  apn         [3] APN, --> Service-Selection UT8String with '.'
    std::string oApn;
    IWFUtils::LabelsToString(in.GetApn().GetArray(), oApn);
    out.setServiceSelection(s6a::ServiceSelection(oApn));

    //  vplmnAddressAllowed -> VPLMN-Dynamic-Address-Allowed (NULL to enum)
    if (in.OptionVplmnAddressAllowed())
    {
        // NOTALLOWED - 0   ALLOWED - 1
        out.setVPLMNDynamicAddressAllowed(s6a::VPLMNDynamicAddressAllowed(
                    s6a::VPLMNDynamicAddressAllowed::ALLOWED));
    }

    //  chargingCharacteristics --> S6a-3GPP-Charging-Characteristics
    // Charging Characteristics HexByteArray to HexString
    if (in.OptionPdp_ChargingCharacteristics())
    {
        std::string hexStr;
        const std::vector<byte>& arr = in.GetPdp_ChargingCharacteristics().GetArray();
        IWFUtils::ByteArrayToHexString(arr, hexStr);
        out.setS6a3GPPChargingCharacteristics(
                s6a::S6a3GPPChargingCharacteristics(hexStr));
    }

    //  ext-pdp-Type --> Ext-PDP-Type (2 bytes to Oct string)
    if (in.OptionExt_pdp_Type())
    {
        const std::vector<byte>& iExtPdpType = in.GetExt_pdp_Type().GetArray();
        out.setExtPDPType(s6a::ExtPDPType(IWFUtils::VectorToString(iExtPdpType)));

        // ext-pdp-Address  --> Ext-PDP-Address, address type based on family
        if (in.OptionExt_pdp_Address())
        {
            const std::vector<byte>& iAddr = in.GetExt_pdp_Address().GetArray();
            out.setExtPDPAddress(s6a::ExtPDPAddress(
                        diameter::Address(diameter::Address::IPV6,
                            (const char*)&iAddr[0], iAddr.size())));
        }
    }

    //  ambr  --> AMBR
    // ambr to AMBR (sequence to grouped)
    if (in.OptionAmbr())
    {
        uint32_t ul, dl;
        const AMBR& iAmbr = in.GetAmbr();
        ul = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_UL().GetValue());
        dl = (uint32_t)(iAmbr.GetMax_RequestedBandwidth_DL().GetValue());

        s6a::AMBR oAmbr;
        oAmbr.setMaxRequestedBandwidthUL(s6a::MaxRequestedBandwidthUL(ul));
        oAmbr.setMaxRequestedBandwidthDL(s6a::MaxRequestedBandwidthDL(dl));

        out.setAMBR(oAmbr);
    }

    //  sipto-Permission   -->  SIPTO-Permission
    if (in.OptionSipto_Permission())
    {
        out.setSIPTOPermission(s6a::SIPTOPermission(
                    (s6a::SIPTOPermission::Value)in.GetSipto_Permission().GetValue()));
    }

    //  lipa-Permission    -->  LIPA-Permission
    if (in.OptionLipa_Permission())
    {
        out.setLIPAPermission(s6a::LIPAPermission(
                    (s6a::LIPAPermission::Value)in.GetLipa_Permission().GetValue()));
    }
}


void S6aToMAPHandler::BuildLCSInfo(const LCSInformation& in, s6a::LCSInfo& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // gmlc-List GMLC-List --> *[ GMLC-Number ]
    if (in.OptionGmlc_List())
    {
        // GMLC_List is a list of ISDN_AddressString
        const GMLC_List& iList = in.GetGmlc_List();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            out.addGMLCNumber(s6a::GMLCNumber(
                        IWFUtils::VectorToString(iList.ElementAt(i).GetArray())));
        }
    }

    // lcs-PrivacyExceptionList --> *LCS-PrivacyException
    if (in.OptionLcs_PrivacyExceptionList())
    {
        const LCS_PrivacyExceptionList& iList = in.GetLcs_PrivacyExceptionList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            const LCS_PrivacyClass& iLcsPrv = iList.ElementAt(i);
            s6a::LCSPrivacyException oLcsPrv;
            BuildLCSPrivacyException(iLcsPrv, oLcsPrv);
            out.addLCSPrivacyException(oLcsPrv);
        }
    }
    // add-lcs-PrivacyExceptionList LCS-PrivacyExceptionList
    if (in.OptionAdd_lcs_PrivacyExceptionList())
    {
        const LCS_PrivacyExceptionList& iList = in.GetAdd_lcs_PrivacyExceptionList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            const LCS_PrivacyClass& iLcsPrv = iList.ElementAt(i);
            s6a::LCSPrivacyException oLcsPrv;
            BuildLCSPrivacyException(iLcsPrv, oLcsPrv);
            out.addLCSPrivacyException(oLcsPrv);
        }
    }

    // molr-List to *MOLR
    if (in.OptionMolr_List())
    {
        const MOLR_List& iList = in.GetMolr_List();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            const MOLR_Class& iMC = iList.ElementAt(i);
            s6a::MOLR oMC;

            // ss-Code to SSCode (octetstring of size 1)
            oMC.setSSCode(s6a::SSCode(IWFUtils::VectorToString(
                            iMC.GetSs_Code().GetArray())));
            // ss-Status to SS-Status (octetstring of size 1..5)
            oMC.setSSStatus(s6a::SSStatus(IWFUtils::VectorToString(
                            iMC.GetSs_Status().GetArray())));

            out.addMOLR(oMC);
        }
    }
}

void S6aToMAPHandler::BuildLCSPrivacyException(
        const LCS_PrivacyClass &in,
        s6a::LCSPrivacyException &out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // ss-Code to SSCode (octetstring of size 1)
    out.setSSCode(s6a::SSCode(IWFUtils::VectorToString(in.GetSs_Code().GetArray())));

    // ss-Status to SS-Status (octetstring of size 1..5)
    out.setSSStatus(s6a::SSStatus(IWFUtils::VectorToString(in.GetSs_Status().GetArray())));

    // notificationToMSUser to Notification-To-UE-User (ENUM)
    if (in.OptionNotificationToMSUser())
    {
        out.setNotificationToUEUser(s6a::NotificationToUEUser(
                    (s6a::NotificationToUEUser::Value)
                    in.GetNotificationToMSUser().GetValue()));
    }

    // externalClientList to *ExternalClient
    if (in.OptionExternalClientList())
    {
        const ExternalClientList& iList = in.GetExternalClientList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            s6a::ExternalClient oEc;
            BuildExternalClient(iList.ElementAt(i), oEc);
            out.addExternalClient(oEc);
        }
    }
    if (in.OptionExt_externalClientList())
    {
        const Ext_ExternalClientList& iList = in.GetExt_externalClientList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            s6a::ExternalClient oEc;
            BuildExternalClient(iList.ElementAt(i), oEc);
            out.addExternalClient(oEc);
        }
    }

    // plmnClientList to *PLMN-Client
    if (in.OptionPlmnClientList())
    {
        const PLMNClientList& iList = in.GetPlmnClientList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            // LCSClientInternalID to PLMN-Client ENUM
            out.addPLMNClient(s6a::PLMNClient(
                        (s6a::PLMNClient::Value)iList.ElementAt(i).GetValue()));
        }
    }

    // serviceTypeList to *Service-Type
    if (in.OptionServiceTypeList())
    {
        const ServiceTypeList& iList = in.GetServiceTypeList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            const ServiceType& iST = iList.ElementAt(i);
            s6a::ServiceType oST;

            // serviceTypeIdentity to ServiceTypeIdentity (integer)
            oST.setServiceTypeIdentity(s6a::ServiceTypeIdentity(
                        iST.GetServiceTypeIdentity().GetValue()));

            // gmlc-Restriction to GMLC-Restriction (ENUM)
            if (iST.OptionGmlc_Restriction())
            {
                oST.setGMLCRestriction(s6a::GMLCRestriction(
                            (s6a::GMLCRestriction::Value)
                            iST.GetGmlc_Restriction().GetValue()));
            }

            // notificationToMSUser to Notification-To-UE-User (ENUM)
            if (iST.OptionNotificationToMSUser())
            {
                oST.setNotificationToUEUser(s6a::NotificationToUEUser(
                            (s6a::NotificationToUEUser::Value)
                            iST.GetNotificationToMSUser().GetValue()));
            }

            out.addServiceType(oST);
        }
    }
}

void S6aToMAPHandler::BuildExternalClient(
        const ExternalClient& in,
        s6a::ExternalClient& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // clientIdentity to Client-Identity (sequence to octet string)
    const std::vector<byte>& iVec = in.GetClientIdentity().GetExternalAddress().GetArray();
    out.setClientIdentity(s6a::ClientIdentity(IWFUtils::VectorToString(iVec)));

    // gmlc-Restriction to GMLC-Restriction (ENUM)
    if (in.OptionGmlc_Restriction())
    {
        out.setGMLCRestriction(s6a::GMLCRestriction(
                    (s6a::GMLCRestriction::Value)in.GetGmlc_Restriction().GetValue()));
    }

    // notificationToMSUser to Notification-To-UE-User (ENUM)
    if (in.OptionNotificationToMSUser())
    {
        out.setNotificationToUEUser(s6a::NotificationToUEUser(
                    (s6a::NotificationToUEUser::Value)in.GetNotificationToMSUser().GetValue()));
    }
}

void S6aToMAPHandler::BuildCSGSubscriptionData(
        const CSG_SubscriptionData& in,
        s6a::CSGSubscriptionData& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // csg-Id (bit string) to CSG-Id (integer)
    out.setCSGId(s6a::CSGId(
                IWFUtils::BitVectorToUnsigned(in.GetCsg_Id().GetArray())));

    // expirationDate to Expiration-Date (Octets[4] to Unsigned)
    if (in.OptionExpirationDate())
    {
        out.setExpirationDate(s6a::ExpirationDate(
                    IWFUtils::ByteArray4ToUInt32(in.GetExpirationDate().GetArray())));
    }

    // lipa-AllowedAPNList to *Service-Selection
    if (in.OptionLipa_AllowedAPNList())
    {
        const LIPA_AllowedAPNList& iList = in.GetLipa_AllowedAPNList();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            std::string oApn;
            IWFUtils::LabelsToString(iList.ElementAt(i).GetArray(), oApn);
            out.addServiceSelection(s6a::ServiceSelection(oApn));
        }
    }
}

void S6aToMAPHandler::ConstructInserSubsciberDataRes(
        IwfFsm* ctxt,
        const InsertSubscriberDataArg* arg,
        InsertSubscriberDataRes* res)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // teleserviceList from arg
    if (arg->OptionTeleserviceList())
    {
        res->SetTeleserviceList(arg->GetTeleserviceList());
    }

    // bearerServiceList from arg
    if (arg->OptionBearerServiceList())
    {
        res->SetBearerServiceList(arg->GetBearerServiceList());
    }

    // TODO ss-List from arg


    // TODO regionalSubscriptionResponse in InsertSubscriberDataRes
    //  -shall be set to regionalSubscNotSupported if regional subscription was
    //   requested within the received InsertSubscriberDataArg but is not
    //   supported by the serving node as indicated within the Supported-Feature
    //   AVP within IDA.
    //  -shall be set to networkNode-AreaRestricted if regional subscription was
    //   requested within the received InsertSubscriberDataArg but a
    //   Network-Node-Area-Restricted indication  has been received within the
    //   IDA-Flags AVP within IDA.
    //  - otherwise shall be absent.

    // supportedCamelPhases in InsertSubscriberDataRes shall be absent or shall
    // indicate that no CAMEL phase is supported.

    // offeredCamel4CSIs in InsertSubscriberDataRes shall be absent.


    S6aMAPTransactionContext* userData =
        reinterpret_cast<S6aMAPTransactionContext*>(ctxt->GetStoredUserData());
    if (userData && userData->HasSupportedFeatures())
    {
        SupportedFeatures *sf = userData->GetSupportedFeatures();
        if (arg->OptionOdb_Data())
        {
            ODB_GeneralData *oOdb = new ODB_GeneralData(
                    IWFUtils::UnsignedToBitVector(0, 32));
            const ODB_GeneralData& iOdb = arg->GetOdb_Data().GetOdb_GeneralData();

            BuildOdbGeneralData(sf, iOdb, oOdb);
            res->SetOdb_GeneralData(oOdb);
        }

        // supportedFeatures in InsertSubscriberDataRes shall be populated with the
        // information received within the Supported-Features AVP within IDA.
        res->SetSupportedFeatures(*sf);
        userData->ClearSupportedFeatures();
    }

}

// Build ODB general data from the Supported Features and ODB_GeneralData in
// the InsertSubscriberArg -> for sending ISDRes
void S6aToMAPHandler::BuildOdbGeneralData(
        const SupportedFeatures* sf,
        const ODB_GeneralData& iOdb,
        ODB_GeneralData *oOdb)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // odb-GeneralData from in InsertSubscriberDataRes shall include all odb
    // categoties that have been requested within the received
    // InsertSubscriberDataArg but are not supported by the serving node as
    // indicated within the Supported-Feature AVP within IDA
    if (sf->IsOdb_all_apnSet() &&
            iOdb.IsAllPacketOrientedServicesBarredSet())
    {
        oOdb->SetAllPacketOrientedServicesBarred();
    }
    if (sf->IsOdb_HPLMN_APNSet() &&
            iOdb.IsRoamerAccessToHPLMN_AP_BarredSet())
    {
        oOdb->SetRoamerAccessToHPLMN_AP_Barred();
    }
    if (sf->IsOdb_VPLMN_APNSet() &&
            iOdb.IsRoamerAccessToVPLMN_AP_BarredSet())
    {
        oOdb->SetRoamerAccessToVPLMN_AP_Barred();
    }
    if (sf->IsOdb_all_ogSet() &&
            iOdb.IsAllOG_CallsBarredSet())
    {
        oOdb->SetAllOG_CallsBarred();
    }
    if (sf->IsOdb_all_international_ogSet() &&
            iOdb.IsInternationalOGCallsBarredSet())
    {
        oOdb->SetInternationalOGCallsBarred();
    }
    if (sf->IsOdb_all_int_og_not_to_HPLMN_countrySet() &&
            iOdb.IsInternationalOGCallsNotToHPLMN_CountryBarredSet())
    {
        oOdb->SetInternationalOGCallsNotToHPLMN_CountryBarred();
    }
    if (sf->IsOdb_all_interzonal_ogSet() &&
            iOdb.IsInterzonalOGCallsBarredSet())
    {
        oOdb->SetInterzonalOGCallsBarred();
    }
    if (sf->IsOdb_all_interzonal_og_not_to_HPLMN_countrySet() &&
            iOdb.IsInterzonalOGCallsNotToHPLMN_CountryBarredSet())
    {
        oOdb->SetInterzonalOGCallsNotToHPLMN_CountryBarred();
    }
    if (sf->IsOdb_all_interzonal_og_and_internat_og_not_to_HPLMN_countrySet() &&
            iOdb.IsInterzonalOGCallsAndInternationalOGCallsNotToHPLMN_CountryBarredSet())
    {
        oOdb->SetInterzonalOGCallsAndInternationalOGCallsNotToHPLMN_CountryBarred();
    }
}

void S6aToMAPHandler::BuildGERANVector(const unsigned idx,
        const AuthenticationTriplet& in,
        s6a::GERANVector& out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    string rand_str = IWFUtils::VectorToString(rand);
    out.setRAND(s6a::RAND(rand_str));

    const std::vector<byte>& sres = in.GetSres().GetArray();
    string sres_str = IWFUtils::VectorToString(sres);
    out.setSRES(s6a::SRES(sres_str));

    const std::vector<byte>& kc = in.GetKc().GetArray();
    string kc_str = IWFUtils::VectorToString(kc);
    out.setKc(s6a::Kc(kc_str));
}

void S6aToMAPHandler::BuildUTRANVector(const unsigned idx,
        const AuthenticationQuintuplet& in,
        s6a::UTRANVector& out)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    string rand_str = IWFUtils::VectorToString(rand);
    out.setRAND(s6a::RAND(rand_str));

    const std::vector<byte>& xres = in.GetXres().GetArray();
    string xres_str = IWFUtils::VectorToString(xres);
    out.setXRES(s6a::XRES(xres_str));

    const std::vector<byte>& ck = in.GetCk().GetArray();
    string ck_str = IWFUtils::VectorToString(ck);
    out.setCK(s6a::CK(ck_str));

    const std::vector<byte>& ik = in.GetIk().GetArray();
    string ik_str = IWFUtils::VectorToString(ik);
    out.setIK(s6a::IK(ik_str));

    const std::vector<byte>& autn = in.GetAutn().GetArray();
    string autn_str = IWFUtils::VectorToString(autn);
    out.setAUTN(s6a::AUTN(autn_str));
}

void S6aToMAPHandler::BuildEUTRANVector(const unsigned idx,
        const AuthenticationQuintuplet& in,
        s6a::EUTRANVector& out, uint8_t *vplmnId)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    string Rand_str = IWFUtils::VectorToString(rand);
    out.setRAND(s6a::RAND(Rand_str));

    const std::vector<byte>& xres = in.GetXres().GetArray();
    std::string xres_str = IWFUtils::VectorToString(xres);
    out.setXRES(s6a::XRES(xres_str));

    const std::vector<byte>& autn = in.GetAutn().GetArray();
    string autn_str = IWFUtils::VectorToString(autn);
    out.setAUTN(s6a::AUTN(autn_str));

    const std::vector<byte>& ck = in.GetCk().GetArray();
    string ck_str = IWFUtils::VectorToString(ck);
    const std::vector<byte>& ik = in.GetIk().GetArray();
    string ik_str = IWFUtils::VectorToString(ik);
    char strKasme[32 + 1] = {0};
    unsigned char *autn_val = (unsigned char *)(autn_str.c_str());
    unsigned char *ck_val = (unsigned char *)(ck_str.c_str());
    unsigned char *ik_val = (unsigned char *)(ik_str.c_str());
    unsigned char Kasme[32] = {0};

    IWFUtils::GenerateKASMEKey(vplmnId, autn_val, ck_val, ik_val, Kasme);
    for (int tok_idx = 0; tok_idx < 32; tok_idx++)
        strKasme[tok_idx] = Kasme[tok_idx];
    std::string kasmeStr(strKasme, 32);
    //s6a::KASME kasme((const char*)strKasme);
    s6a::KASME kasme(kasmeStr);
    out.setKASME(kasme);
}

void S6aToMAPHandler::BuildEUTRANVector(const unsigned idx,
        const EPC_AV& in,
        s6a::EUTRANVector& out)
{
    out.setItemNumber(s6a::ItemNumber(idx));

    const std::vector<byte>& rand = in.GetRand().GetArray();
    string Rand_str = IWFUtils::VectorToString(rand);
    out.setRAND(s6a::RAND(Rand_str));

    const std::vector<byte>& xres = in.GetXres().GetArray();
    std::string xres_str = IWFUtils::VectorToString(xres);
    out.setXRES(s6a::XRES(xres_str));

    const std::vector<byte>& autn = in.GetAutn().GetArray();
    string autn_str = IWFUtils::VectorToString(autn);
    out.setAUTN(s6a::AUTN(autn_str));

    const std::vector<byte>& kasme = in.GetKasme().GetArray();
    string kasme_str = IWFUtils::VectorToString(kasme);
    out.setKASME(s6a::KASME(kasme_str));
}

int S6aToMAPHandler::InsertSubscriberDataArg_To_IDR(IwfFsm *ctxt,
        const InsertSubscriberDataArg *in,
        s6a::InsertSubscriberDataRequest *out)
{
    int ret = ITS_SUCCESS;
    // Auth-Session-State AVP shall be set to the value NO_STATE_MAINTAINED (1)
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    if(in->OptionImsi())
    {
        // User-Name AVP shall be populated with the value received within the imsi
        // parameter of InsertSubscriberDataArg.
        std::string oImsi;
        const std::vector<byte>& vec = in->GetImsi().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
        size_t fPos = oImsi.find('F'); // TODO: Check for 'f'
        if (fPos != std::string::npos)
        {
            oImsi.erase(fPos, std::string::npos);
        }
        out->setUserName(diameter::base::UserName(oImsi));

        if (SetDestinationHostAndRealm(ctxt, oImsi, out) != ITS_SUCCESS)
        {
            DLOG_ERROR("InserSubscriberDataArg_To_IDR: Destination Info is not found for IMSI: %s", oImsi.c_str());
            ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
            return ITS_ENOTFOUND;
        }
    }
    else
    {
        DLOG_WARNING("IMSI not present in InserSubscriberDataArg.");
        ctxt->SetErrorCode(MAP_ERR_DATA_MISSING);
        ret = !ITS_SUCCESS;
        return ret;
    }
    // Supported-Features AVP shall be absent.

    // Subscription-Data AVP: See chapter 8.2.2.
    s6a::SubscriptionData oSubsData;
    InsertSubscriberDataArg_To_SubscriptionData(ctxt, in, &oSubsData);
    out->setSubscriptionData(oSubsData);

    // IDR-Flags AVP: Flags shall be set as follows:
    // UE Reachability Request shall be set to 1 if the
    // ue-reachabilityRequestIndicator was present within InsertSubscriberDataArg;
    // othewise shall be set to 0 or the AVP shall be absent.
    if (in->OptionUe_ReachabilityRequestIndicator())
    {
        out->setIDRFlags(s6a::IDRFlags(IDR_FLAG_UE_REACH_REQ));
    }
    else
    {
        out->setIDRFlags(s6a::IDRFlags((unsigned)0));
    }
    return ret;
}

void S6aToMAPHandler::IDA_To_InsertSubscriberDataRes(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataAnswer *in,
        InsertSubscriberDataRes* out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // TODO teleserviceList from arg
#if 0
    if (arg->OptionTeleserviceList())
    {
        res->SetTeleserviceList(arg->GetTeleserviceList());
    }
#endif

    // TODO bearerServiceList from arg
#if 0
    if (arg->OptionBearerServiceList())
    {
        res->SetBearerServiceList(arg->GetBearerServiceList());
    }
#endif

    // TODO ss-List from arg

    // TODO regionalSubscriptionResponse

    // Supported Features to supported Features
    // TODO the mapping is not straight forward for the last few items
    unsigned long iFeatures = 0;
    for (int i = 0; i < in->countSupportedFeatures(); i++)
    {
        if (in->getSupportedFeatures(i).getFeatureListID().value() != 1)
        {
            DLOG_WARNING("FeatureList value is not 1 i.e. %d", in->getSupportedFeatures(i).getFeatureListID().value());
            break;
        }
        iFeatures = in->getSupportedFeatures(i).getFeatureList().value();
    }

    if (iFeatures)
    {
        SupportedFeatures *oFeatures = new SupportedFeatures(
                IWFUtils::UnsignedToBitVector(iFeatures, 32));
        out->SetSupportedFeatures(oFeatures);
    }
}

// too big of a namespce polution :)
using namespace diameter::base;

    void
S6aToMAPHandler::IDA_To_ProvideSubscribeInfoRes(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataAnswer *in,
        ProvideSubscriberInfoRes *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (!ctxt || !in || !out) {
        return;
    }
    if (in->getResultCode().value() != ITS_DIA_SUCCESS)
    {
        // TODO: Set MAP Error and ProvideSubscriberInfoRes
        return;
    }

    SubscriberInfo subInfo;
    if (in->containsIMSVoiceOverPSSessionsSupported())
    {
        const s6a::IMSVoiceOverPSSessionsSupported &diaVInd =
            in->getIMSVoiceOverPSSessionsSupported();
        IMS_VoiceOverPS_SessionsInd imsVoiceInd(diaVInd.value());
        subInfo.SetImsVoiceOverPS_SessionsIndication(imsVoiceInd);
    }

    if (in->containsLastUEActivityTime())
    {
        const s6a::LastUEActivityTime &diaAct = in->getLastUEActivityTime();
        const void *value = static_cast<const void *>(&diaAct.value());
        const byte *tarrp = static_cast<const byte *>(value);
        std::vector<byte> tarr(tarrp, tarrp + sizeof(unsigned int));
        map_v13::Time mtime(tarr);
        subInfo.SetLastUE_ActivityTime(mtime);
    }

    if (in->containsRATType())
    {
        Used_RAT_Type urt;
        switch (in->getRATType().value())
        {
            case s6a::RATType::UTRAN:
                urt.SetUtran();
                break;

            case s6a::RATType::GERAN:
                urt.SetGeran();
                break;

            case s6a::RATType::GAN:
                urt.SetGan();
                break;

            case s6a::RATType::HSPA_EVOLUTION:
                urt.SetI_hspa_evolution();
                break;

            case s6a::RATType::EUTRAN:
                urt.SetE_utran();
                break;

            default:
                DLOG_WARNING("RAT-Type %d not supported", in->getRATType().value());
                break; // Find other matching enums in MAP
        }
        subInfo.SetLastRAT_Type(urt);
    }

    if (in->containsEPSUserState())
    {
        PS_SubscriberState mapEPS;
        int                us  = 0;
        bool               set = true;

        if (in->getEPSUserState().containsMMEUserState() &&
                in->getEPSUserState().getMMEUserState().containsUserState())
        {
            us = in->getEPSUserState().getMMEUserState().getUserState().value();
        }
        else if (in->getEPSUserState().containsSGSNUserState() &&
                in->getEPSUserState().getSGSNUserState().containsUserState())
        {
            us = in->getEPSUserState().getSGSNUserState().getUserState().value();
        }
        else
        {
            set = false;
        }

        if (set)
        {
            switch (us)
            {
                case s6a::UserState::DETACHED:
                    {
                        PS_SubscriberState::Ps_Detached det;
                        mapEPS.SetChoicePs_Detached(det);
                        break;
                    }

                case s6a::UserState::ATTACHED_NOT_REACHABLE_FOR_PAGING:
                    {
                        PS_SubscriberState::Ps_AttachedNotReachableForPaging nrp;
                        mapEPS.SetChoicePs_AttachedNotReachableForPaging(nrp);
                        break;
                    }

                case s6a::UserState::ATTACHED_REACHABLE_FOR_PAGING:
                    {
                        PS_SubscriberState::Ps_AttachedReachableForPaging apr;
                        mapEPS.SetChoicePs_AttachedReachableForPaging(apr);
                        break;
                    }

                case s6a::UserState::CONNECTED_NOT_REACHABLE_FOR_PAGING:
                case s6a::UserState::CONNECTED_REACHABLE_FOR_PAGING:
                case s6a::UserState::NETWORK_DETERMINED_NOT_REACHABLE:
                    // TODO: Not found a better mapping in map
                    break;
                default:
                    break;
            }
            subInfo.SetEps_SubscriberState(mapEPS);
        }
    }
    if (in->containsEPSLocationInformation())
    {
        map_v13::LocationInformationEPS mapLI;
        if (in->getEPSLocationInformation().containsMMELocationInformation())
        {
            const s6a::MMELocationInformation &mmeli =
                in->getEPSLocationInformation().getMMELocationInformation();

            if (mmeli.containsEUTRANCellGlobalIdentity())
            {
                std::vector<byte> idv = IWFUtils::StringToVector(
                        mmeli.getEUTRANCellGlobalIdentity().value());
                E_UTRAN_CGI       cgid(idv);
                mapLI.SetE_utranCellGlobalIdentity(cgid);
            }

            if (mmeli.containsTrackingAreaIdentity())
            {
                std::vector<byte> tav = IWFUtils::StringToVector(
                        mmeli.getTrackingAreaIdentity().value());
                TA_Id             taid(tav);
                mapLI.SetTrackingAreaIdentity(taid);
            }

            if (mmeli.containsGeographicalInformation())
            {
                std::vector<byte> giv = IWFUtils::StringToVector(
                        mmeli.getGeographicalInformation().value());
                map_v13::GeographicalInformation gi(giv);
                mapLI.SetGeographicalInformation(gi);
            }

            if (mmeli.containsGeodeticInformation())
            {
                std::vector<byte> gdifv = IWFUtils::StringToVector(
                        mmeli.getGeodeticInformation().value());
                map_v13::GeodeticInformation gdi(gdifv);
                mapLI.SetGeodeticInformation(gdi);
            }

            if (mmeli.containsCurrentLocationRetrieved())
            {
                // Only one is defined.
                LocationInformationEPS::CurrentLocationRetrieved clr;
                mapLI.SetCurrentLocationRetrieved(clr);
            }

            if (mmeli.containsAgeOfLocationInformation())
            {
                map_v13::AgeOfLocationInformation ali(
                        mmeli.getAgeOfLocationInformation().value());
                mapLI.SetAgeOfLocationInformation(ali);
            }

            subInfo.SetLocationInformationEPS(mapLI);
        }
        else if (in->getEPSLocationInformation().containsSGSNLocationInformation())
        {
            const s6a::SGSNLocationInformation &sgsnli =
                in->getEPSLocationInformation().getSGSNLocationInformation();

            if (sgsnli.containsCellGlobalIdentity())
            {
                std::vector<byte> idv = IWFUtils::StringToVector(
                        sgsnli.getCellGlobalIdentity().value());
                E_UTRAN_CGI       cgid;
                mapLI.SetE_utranCellGlobalIdentity(cgid);
            }

            if (sgsnli.containsGeographicalInformation())
            {
                std::vector<byte> giv = IWFUtils::StringToVector(
                        sgsnli.getGeographicalInformation().value());
                map_v13::GeographicalInformation gi(giv);
                mapLI.SetGeographicalInformation(gi);
            }

            if (sgsnli.containsGeodeticInformation())
            {
                std::vector<byte> gdifv = IWFUtils::StringToVector(
                        sgsnli.getGeodeticInformation().value());
                map_v13::GeodeticInformation gdi(gdifv);
                mapLI.SetGeodeticInformation(gdi);
            }

            if (sgsnli.containsCurrentLocationRetrieved())
            {
                // Only one is defined.
                LocationInformationEPS::CurrentLocationRetrieved clr;
                mapLI.SetCurrentLocationRetrieved(clr);
            }

            if (sgsnli.containsAgeOfLocationInformation())
            {
                map_v13::AgeOfLocationInformation ali(
                        sgsnli.getAgeOfLocationInformation().value());
                mapLI.SetAgeOfLocationInformation(ali);
            }

            subInfo.SetLocationInformationEPS(mapLI);
        }
    }
    out->SetSubscriberInfo(subInfo);

    // TODO: Time Zone population from IDA
    //       Daylight-Saving-Time population from IDA
}

    int
S6aToMAPHandler::ProvideSubscriberInfoArg_To_IDR(IwfFsm *ctxt,
        const ProvideSubscriberInfoArg *in,
        s6a::InsertSubscriberDataRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (!ctxt || !in || !out)
    {
        DLOG_CRITICAL("ProvideSubscriberInfoArg_To_IDR: Invalid Arguments:");
        return ITS_ENOTFOUND;
    }

    AuthSessionState authSesState(AuthSessionState::NO_STATE_MAINTAINED);
    out->setAuthSessionState(authSesState);

    const std::vector<byte> &imsi = in->GetImsi().GetArray();
    std::string simsi;

    const uint8_t *imsiarr = reinterpret_cast<const uint8_t *>(&imsi[0]);
    IWFUtils::TBCDToString(imsiarr,
            imsi.size(),
            simsi,
            imsi.size() % 2 ? true: false);

    size_t fPos = simsi.find('F');
    if (fPos != std::string::npos)
    {
        simsi.erase(fPos, std::string::npos);
    }

    UserName un(simsi);
    out->setUserName(un);

    if (SetDestinationHostAndRealm(ctxt, simsi, out) != ITS_SUCCESS)
    {
        DLOG_WARNING("ProvideSubscriberInfoArg_To_IDR: Destination Info is not found for IMSI: %s", simsi.c_str());
        ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
        return ITS_ENOTFOUND;
    }

    // Supported-Features shall be empty
    // Subscription-Data shall be empty
    s6a::SubscriptionData sd;
    out->setSubscriptionData(sd);

    ITS_UINT idrFlags = 0x00; // Init with UE reachability set to 0
    const RequestedInfo &reqInfo = in->GetRequestedInfo();
    // Enable IDR Flags bits
    if (reqInfo.OptionT_adsData())
    {
        idrFlags |= IDR_FLAG_TADS_DATA_REQ;
    }
    if (reqInfo.OptionSubscriberState())
    {
        idrFlags |= IDR_FLAG_EPS_USER_STATE_REQ;
    }
    if (reqInfo.OptionLocationInformation())
    {
        idrFlags |= IDR_FLAG_EPS_LOC_INFO_REQ;
    }
    if (reqInfo.OptionCurrentLocation())
    {
        idrFlags |= IDR_FLAG_CUR_LOC_REQ;
    }
    // TODO: MAP V13 API is missing LocalTimeZone params.
    s6a::IDRFlags flags(idrFlags);
    out->setIDRFlags(flags);

    return ITS_SUCCESS;
}


    int
S6aToMAPHandler::DeleteSubscriberDataArg_To_DSR(IwfFsm *ctxt,
        const DeleteSubscriberDataArg *in,
        s6a::DeleteSubscriberDataRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (!ctxt || !in || !out)
    {
        DLOG_CRITICAL("DeleteSubscriberDataArg_To_DSR: Invalid Arguments:");
        return ITS_ENOTFOUND;
    }

    AuthSessionState authSesState(AuthSessionState::NO_STATE_MAINTAINED);
    out->setAuthSessionState(authSesState);

    const std::vector<byte> &imsi = in->GetImsi().GetArray();
    std::string simsi;

    const uint8_t *imsiarr = reinterpret_cast<const uint8_t *>(&imsi[0]);
    IWFUtils::TBCDToString(imsiarr,
            imsi.size(),
            simsi,
            imsi.size() % 2 ? true: false);

    size_t fPos = simsi.find('F');
    if (fPos != std::string::npos)
    {
        simsi.erase(fPos, std::string::npos);
    }

    UserName un(simsi);
    out->setUserName(un);

    if (SetDestinationHostAndRealm(ctxt, simsi, out) != ITS_SUCCESS)
    {
        DLOG_WARNING("DeleteSubscriberDataArg_To_DSR: Destination Info is not found for IMSI: %s", simsi.c_str());
        ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
        return ITS_ENOTFOUND;
    }

    // Supported Feature shall be Absent
    // DSR Flags
    ITS_UINT dsrFlags = 0x00;
    if (in->OptionRegionalSubscriptionIdentifier())
    {
        dsrFlags |= DSR_FLAG_REGION_SUB_WITHDRAW;
    }
    if (in->OptionEpsSubscriptionDataWithdraw())
    {
        const EPS_SubscriptionDataWithdraw &eps = in->GetEpsSubscriptionDataWithdraw();
        if (eps.ChoiceAllEPS_Data())
        {
            dsrFlags |= DSR_FLAG_COMPLETE_APN_CONFIG;
        }
        if (eps.ChoiceContextIdList())
        {
            dsrFlags |= DSR_FLAG_PDN_SUBSCRIPTION_WITHDRAW;

            const ContextIdList &cl = eps.GetChoiceContextIdList();
            int s = cl.GetSize();
            while (s > 0 && s--)
            {
                s6a::ContextIdentifier ci(cl.ElementAt(s).GetValue());
                out->addContextIdentifier(ci);
            }
        }


    }
    if (in->OptionChargingCharacteristicsWithdraw())
    {
        dsrFlags |= DSR_FLAG_SUB_CHARGE_CHAR;
    }
    if (in->OptionStn_srWithdraw())
    {
        dsrFlags |= DSR_FLAG_STN_SR;
    }
    if (in->OptionGmlc_ListWithdraw())
    {
        dsrFlags |= DSR_FLAG_GMLC_LIST_WITHDRAW;
    }
    if (in->OptionSs_List())
    {
        dsrFlags |= DSR_FLAG_LCS_WITHDRAW;
        // NOTE: Conditions to set SMS Withdrawal Flag
        const SS_List& sslist = in->GetSs_List();
        for(unsigned int i = 0; i<sslist.GetSize(); i++)
        {
            const std::vector<byte>& sscode = sslist.ElementAt(i).GetArray();
            if(sscode[0] == SSCODE_BARRING_OF_ALL_OUTGOING_CALLS ||
                    sscode[0] == SSCODE_BARRING_OF_OUTGOING_INTERNATIONAL_CALLS ||
                    sscode[0] == SSCODE_BARRING_OF_OUTGOING_INTERN_CALLS_EXCEPT_THOSE_DIRECTED_TO_HOME_PLMN_COUNTRY ||
                    sscode[0] == SSCODE_BARRING_OF_ALL_INCOMING_CALLS ||
                    sscode[0] == SSCODE_BARRING_OF_INCOMING_CALLS_WHEN_ROAMING_OUTSIDE_THE_HOME_PLMN_COUNTRY)
            {
                dsrFlags |= DSR_FLAG_SMS_WITHDRAW;
                break;
            }
        }
    }
    if (in->OptionGprsSubscriptionDataWithdraw())
    {
        const GPRSSubscriptionDataWithdraw &gprs = in->GetGprsSubscriptionDataWithdraw();
        if (gprs.ChoiceAllGPRSData())
        {
            dsrFlags |= DSR_FLAG_COMPLETE_PDP_LIST_WITHDRAW;
        }
        if (gprs.ChoiceContextIdList())
        {
            const ContextIdList &cl = gprs.GetChoiceContextIdList();
            int s = cl.GetSize();

            dsrFlags |= DSR_FLAG_PDP_CONTEXT_WITHDRAW;
            while (s > 0 && s--)
            {
                s6a::ContextIdentifier ci(cl.ElementAt(s).GetValue());
                out->addContextIdentifier(ci);
            }
        }
    }
    if (in->OptionRoamingRestrictedInSgsnDueToUnsuppportedFeature())
    {
        dsrFlags |= DSR_FLAG_ROAM_RESTRICT_UN_SUPPORTED;
    }
    if (in->OptionCsg_SubscriptionDeleted())
    {
        dsrFlags |= DSR_FLAG_CSG_DELETED;
    }
    if (in->OptionApn_oi_replacementWithdraw())
    {
        dsrFlags |= DSR_FLAG_ASPN_OI_REPLACEMENT;
    }
    // TODO: VSRVV is not in MAP v13
    s6a::DSRFlags dsrAvp(dsrFlags);
    out->setDSRFlags(dsrAvp);

    return ITS_SUCCESS;
}


    void
S6aToMAPHandler::DSA_To_DeleteSubscriberDataRes(IwfFsm *ctxt,
        const s6a::DeleteSubscriberDataAnswer *in,
        DeleteSubscriberDataRes *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (!ctxt || !in || !out)
    {
        DLOG_CRITICAL("DSA_To_DeleteSubscriberDataRes: Invalid Arguments:");
        return;
    }

    RegionalSubscriptionResponse rsr;

    bool setRegionalSubscResponse = false;
    if(in->countSupportedFeatures())
    {
        for(int i = 0; i < in->countSupportedFeatures(); i++)
        {
            const s6a::SupportedFeatures& iFl = in->getSupportedFeatures(i);
            if((iFl.getFeatureListID().value() == 1) &&
                    (iFl.getFeatureList().value() & (1<<9)))
            {
                rsr.SetRegionalSubscNotSupported();
                setRegionalSubscResponse = true;
            }
        }
        if(setRegionalSubscResponse)
        {
            out->SetRegionalSubscriptionResponse(rsr);
        }
    }
    if (!setRegionalSubscResponse && in->containsDSAFlags())
    {
        if (in->getDSAFlags().value() & DSA_FLAG_NET_NODE_AREA_RESTRICT)
        {
            rsr.SetNetworkNode_AreaRestricted();
            out->SetRegionalSubscriptionResponse(rsr);
        }
    }
}

void S6aToMAPHandler::ResetArg_To_RSR(IwfFsm *ctxt,
        const ResetArg* in,
        s6a::ResetRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // Reset is sent from the HLR (MAPv1 or MAPv2, no MAPv3? TODO)
    // Reset doesn't have any corresponding Response

    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // User-Id taken from hlr-list
    if (in->OptionHlr_List())
    {
        const HLR_List& iList = in->GetHlr_List();
        for (unsigned i = 0; i < iList.GetSize(); i++)
        {
            std::string imsi;
            const std::vector<byte>& vec = iList.ElementAt(i).GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), imsi);
            size_t fPos = imsi.find('F');
            if (fPos != std::string::npos)
            {
                imsi.erase(fPos, std::string::npos);
            }

            out->addUserId(s6a::UserId(imsi));
        }
    }

    // Supported features shall be absent

}

void S6aToMAPHandler::NOR_To_UpdateGPRSLocationArg(IwfFsm *ctxt,
        const s6a::NotifyRequest *in,
        UpdateGprsLocationArg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // When NOR is received after constructing UpdateGprsLocationArg or
    // ReadyForSM, the NOA is sent immediately without waiting for response TODO
    // return a flag or something for this
    // Also in case of UpdateGprsLocationArg, some HLR's might send
    // InsertSubscriberDataArg even though skipSubscriberData is set. In such
    // cases the Arg should be acked, but no diameter response TODO SM change

    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to IMSI
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));

    // sgsn-Number, locally assigned IWF number consistence with SS7 routing
    if(IwfController::Instance().Config().LocalConfig().IsLocalSgsnNumberUsedForMapping())
    {
        its::ByteArray outSgsnNum;
        m_config.GetSGSNNumber(outSgsnNum);
        out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
    }
    else
    {
        std::string sgsn_num = ""; 
        if(m_config.GetSGSNNumberFromOriginHost(in->getOriginHost().value(), sgsn_num))
        {
            DLOG_DEBUG("SGSN Number %s found in SGSN Num Map for OriginHost %s",
                    sgsn_num.c_str(), in->getOriginHost().value().c_str());
            its::ByteArray outSgsnNum;
            uint8_t svar[20] = {0};
            int len = IWFUtils::StringToTBCD(sgsn_num.substr(0,LENGTH_OF_ADDR_DIGITS), svar, 
                    LENGTH_OF_ADDR_DIGITS, 0, true);
            len += IWFUtils::StringToTBCD(sgsn_num.substr(LENGTH_OF_ADDR_DIGITS), 
                    (svar+1), MAX_SGSN_NUM_LEN, 0x0f);
            outSgsnNum.assign(svar, svar + len);
            out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
        }
        else
        {
            DLOG_DEBUG("SGSN Number not found in SGSN Num Map for OriginHost %s",in->getOriginHost().value().c_str());
        }
    }

    // sgsn-Address, shall be the IP address of the source node
    // SGSN-Address, obtained from the configuration mapping against OriginHost
    its::ByteArray gsnAddr;
    bool res = m_config.SGSNAddrFromOHost(in->getOriginHost().value(), gsnAddr);
    if (res)
    {
        // The value stored in config is already in GSNAddress format
        out->SetSgsn_Address(new GSN_Address(gsnAddr));
    }
    else
    {
        string ipaddr;
        Generateipv4(ipaddr);
        string orgHost = in->getOriginHost().value();
        m_config.SetSGSNAddrFromOHost(orgHost, ipaddr);
        IWFUtils::IpStringToGSNAddress(ipaddr, gsnAddr);
        out->SetSgsn_Address(new GSN_Address(gsnAddr));
    }

    // sgsn-Capability in UpdateGprsLocationArg shall be absent.
    // informPreviousNetworkEntity in UpdateGprsLocationArg shall be absent;
    // ps-LCS-NotSupportedByUE in UpdateGprsLocationArg shall be absent
    // v-gmlc-Address in UpdateGprsLocationArg shall be absent.

    // Terminal-Information to add-info with skipSubscriberDataUpdate
    if (in->containsTerminalInformation())
    {
        // Terminal-Info to Additional Info
        ADD_Info *oAddInfo = new ADD_Info();
        BuildAddInfo(in->getTerminalInformation(), oAddInfo, true);
        out->SetAdd_info(oAddInfo);
    }

    // eps-info in UpdateGprsLocationArg shall be present and contain a
    // pdn-gw-update parameter if the received NOR contained a MIP6-Agent-Info
    // eps-info and contain a isr-Information parameter if the received NOR contained
    // a Single-Registration-Indication indication within the NOR-Flags AVP
    if (in->containsMIP6AgentInfo() || in->containsServiceSelection())
    {
        EPS_Info *oEpsInfo = new EPS_Info();
        PDN_GW_Update *oPgu = new PDN_GW_Update();
        if(in->containsMIP6AgentInfo())
        {
            PDN_GW_Identity *oPid = new PDN_GW_Identity();
            BuildPDNGWIdentity(in->getMIP6AgentInfo() , *oPid);
            oPgu->SetPdn_gw_Identity(oPid);
        }
        if(in->containsServiceSelection())
        {
            oPgu->SetApn(new APN(IWFUtils::StringToVector(in->getServiceSelection().value())));
        }
        oEpsInfo->SetChoicePdn_gw_update(oPgu);
        out->SetEps_info(oEpsInfo);
    }
    else if (in->containsNORFlags() &&
            in->getNORFlags().value() & NOR_FLAG_SINGLE_REGISTRATION_IND)
    {
        // set isr information
        EPS_Info *oEpsInfo = new EPS_Info();

        BuildEPSInfo(NOR_FLAG_SINGLE_REGISTRATION_IND,
                oEpsInfo);
        out->SetEps_info(oEpsInfo);
    }

    // servingNodeTypeIndicator in UpdateGprsLocationArg shall be present.
    out->SetServingNodeTypeIndicator(
            new UpdateGprsLocationArg::ServingNodeTypeIndicator());

    // skipSubscriberData Update in UpdateGprsLocationArg shall be present.
    out->SetSkipSubscriberDataUpdate(
            new UpdateGprsLocationArg::SkipSubscriberDataUpdate());

    // usedRAT-Type in UpdateGprsLocationArg shall be absent.
    // gprsSubscriptionDataNotNeeded in UpdateGprsLocationArg shall be absent.
    // nodeTypeIndicator in UpdateGprsLocationArg shall be absent.

    // areaRestricted in UpdateGprsLocationArg shall be present if the
    // corresponding information was received within the NOR-Flags
    if (in->containsNORFlags())
    {
        unsigned norFlags = in->getNORFlags().value();
        if (norFlags & NOR_FLAG_SGSN_AREA_RESTRICTED)
        {
            out->SetAreaRestricted(new UpdateGprsLocationArg::AreaRestricted());
        }

        if (norFlags & NOR_FLAG_UE_REACHABLE_FROM_MME ||
                norFlags & NOR_FLAG_UE_REACHABLE_FROM_SGSN)
        {
            out->SetUe_reachableIndicator(
                    new UpdateGprsLocationArg::Ue_reachableIndicator());
        }
    }

    // UE-SRVCC-Capability to UE-SRVCC-Capability enum
    if (in->containsUESRVCCCapability())
    {
        unsigned ueSrvcc = in->getUESRVCCCapability().value();
        out->SetUe_srvcc_Capability(new UE_SRVCC_Capability(ueSrvcc));
    }
}

void S6aToMAPHandler::NOR_To_ReadyForSM(IwfFsm *ctxt,
        const s6a::NotifyRequest *in,
        ReadyForSM_Arg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to IMSI
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));

    // alertReason in ReadyForSMArg shall be populated with the value of the Alert-Reason AVP received within NOR.
    if (in->containsAlertReason())
    {
        out->SetAlertReason(new AlertReason(in->getAlertReason().value()));
    }
    else
    {
        // throw an exception? AlreadReason is mandatory in ReadyForSM
    }

    // alertReasonIndicator in ReadyForSMArg shall be present.
    out->SetAlertReasonIndicator(
            new ReadyForSM_Arg::AlertReasonIndicator());

    // additionalAlertReasonIndicator in ReadyForSMArg shall be absent.
}


void S6aToMAPHandler::BuildPDNGWIdentity(const s6a::MIP6AgentInfo& in,
        PDN_GW_Identity &out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // MIP-Home-Agent-Address to pdn-gw-ipv4-Address or pdn-gw-ipv6-Address
    for (int i = 0; i < in.countMIPHomeAgentAddress(); i++)
    {
        const diameter::Address& iAddr = in.getMIPHomeAgentAddress(i).value();
        if (iAddr.family == diameter::Address::IPV4)
        {
            out.SetPdn_gw_ipv4_Address(new PDP_Address(
                        IWFUtils::StringToVector(iAddr.value)));
        }
        else if (iAddr.family == diameter::Address::IPV6)
        {
            out.SetPdn_gw_ipv6_Address(new PDP_Address(
                        IWFUtils::StringToVector(iAddr.value)));
        }
    }

    // MIP-Home-Agent-Host to pdn-gw-name
    if (in.containsMIPHomeAgentHost())
    {
        out.SetPdn_gw_name(new FQDN(IWFUtils::StringToVector(
                        in.getMIPHomeAgentHost().getDestinationHost().value())));
    }
}

void S6aToMAPHandler::ConstructNOA(IwfFsm *ctxt, const s6a::NotifyRequest *in,
        s6a::NotifyAnswer *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}

    template <class T>
void S6aToMAPHandler::ConstructErrorAnswer(int error,T *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::BaseGenericCommand *diaBaseGenCmd = (diameter::base::BaseGenericCommand *) out;
    diameter::DiaHeader& hdr = const_cast<diameter::DiaHeader&>(diaBaseGenCmd->getHeader());
    diameter::base::ExperimentalResult res;
    unsigned resCode = 0;

    switch(error)
    {
        case DIAMETER_ERROR_USER_UNKNOWN:
            {
                res.setVendorId(diameter::base::VendorId(DIAMETER_3GPP_VENDOR_ID));
                resCode = DIAMETER_ERROR_USER_UNKNOWN;
                res.setExperimentalResultCode(diameter::base::ExperimentalResultCode(resCode));
                out->setExperimentalResult(res);
                break;
            }

        case DIAMETER_ERROR_ROAMING_NOT_ALLOWED:
            {
                res.setVendorId(diameter::base::VendorId(DIAMETER_3GPP_VENDOR_ID));
                resCode = DIAMETER_ERROR_ROAMING_NOT_ALLOWED;
                res.setExperimentalResultCode(diameter::base::ExperimentalResultCode(resCode));
                out->setExperimentalResult(res);
                break;
            }
        default:
            {
                /*Set the E BIT Explicitly*/
                hdr.flags.e = 1;
                DLOG_DEBUG("ConstructErrorAnswer: E-BIT is : %d", hdr.flags.e);
                diameter::base::ResultCode res(error);
                out->setResultCode(res);
            }
    }
    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}

void S6aToMAPHandler::ActivateTraceModeArg_To_TraceData(IwfFsm *ctxt,
        const ActivateTraceModeArg *in,
        s6a::TraceData *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // traceReference and traceReference2 to TraceReference
    // There is no direct mapping, where to get the MCC and MNC?
    std::string traceId;
    if (in->OptionTraceReference2())
    {
        // If reference2 is present, get it from that
        traceId = IWFUtils::VectorToString(in->GetTraceReference2().GetArray());
    }
    else
    {
        traceId = IWFUtils::VectorToString(in->GetTraceReference().GetArray());
        traceId += '\0'; // make it 3 octets long
    }

    if(in->OptionImsi())
    {
        // Get the MNC and MCC from IMSI?
        unsigned mnc, mcc;
        IWFUtils::ExtractMncMcc(in->GetImsi().GetArray(), mcc, mnc);

        // Construct in the PLMN format
        std::string traceRef;
        IWFUtils::ConstructPLMN(traceRef, mcc, mnc);

        // now set prefix the traceId
        traceRef += traceId;
        out->setTraceReference(s6a::TraceReference(traceRef));
    }

    // traceDepthList to Trace-Depth grouped to enum
    if (in->OptionTraceDepthList())
    {
        unsigned val = 0;
        const TraceDepthList& iList = in->GetTraceDepthList();
        if (iList.OptionMme_TraceDepth())
        {
            val = iList.GetMme_TraceDepth().GetValue();
        }
        else if (iList.OptionSgsn_TraceDepth())
        {
            val = iList.GetSgsn_TraceDepth().GetValue();
        }
        out->setTraceDepth(s6a::TraceDepth((s6a::TraceDepth::Value)val));
    }
    else
    {
        out->setTraceDepth(s6a::TraceDepth(s6a::TraceDepth::Minimum));
    }

    // traceNE-TypeList to Trace-NE-Type-List (bit-string to octet string)
    if (in->OptionTraceNE_TypeList())
    {
        uint16_t bits = htons((uint16_t)IWFUtils::BitVectorToUnsigned(
                    in->GetTraceNE_TypeList().GetArray()));
        out->setTraceNETypeList(s6a::TraceNETypeList(
                    std::string((char*)(&bits), 2)));
    }
    else
    {
        uint16_t bits = htons((uint16_t)0x0044);
        out->setTraceNETypeList(s6a::TraceNETypeList(
                    std::string((char*)(&bits), 2)));
    }

    // traceEventList to Trace-Event-List (Grouped bit string to octet string)
    if (in->OptionTraceEventList())
    {
        const TraceEventList& iList = in->GetTraceEventList();
        if (iList.OptionMme_List())
        {
            uint8_t bits = (uint8_t)IWFUtils::BitVectorToUnsigned(
                    iList.GetMme_List().GetArray());
            out->setTraceEventList(s6a::TraceEventList(
                        std::string((char*)&bits, 1)));
        }
        else if (iList.OptionSgsn_List())
        {
            uint16_t bits = htons((uint16_t)IWFUtils::BitVectorToUnsigned(
                        iList.GetSgsn_List().GetArray()));
            out->setTraceEventList(s6a::TraceEventList(
                        std::string((char*)&bits, 2)));
        }
    }

    // traceCollectionEntity to Trace-Collection-Entity GSN-Address to Address
    if (in->OptionTraceCollectionEntity())
    {
        try
        {
            diameter::Address diaAddr = IWFUtils::GSNAddressToDiaAddress(
                    in->GetTraceCollectionEntity().GetArray());
            out->setTraceCollectionEntity(s6a::TraceCollectionEntity(diaAddr));
        }
        catch(...)
        {
            DLOG_ERROR("Exception Caught .. !! While Conversion of Trace-Collection-Entity");
        }
    }

    // traceInterfaceList to TraceInterfacelist (Grouped bit string to octet string)
    if (in->OptionTraceInterfaceList())
    {
        const TraceInterfaceList& iList = in->GetTraceInterfaceList();
        if (iList.OptionMme_List())
        {
            uint8_t bits = (uint8_t)IWFUtils::BitVectorToUnsigned(
                    iList.GetMme_List().GetArray());
            out->setTraceInterfaceList(s6a::TraceInterfaceList(
                        std::string((char*)&bits, 1)));
        }
        else if (iList.OptionSgsn_List())
        {
            uint16_t bits = htons((uint16_t)IWFUtils::BitVectorToUnsigned(
                        iList.GetSgsn_List().GetArray()));
            out->setTraceInterfaceList(s6a::TraceInterfaceList(
                        std::string((char*)&bits, 2)));
        }
    }

    // omc-Id to OMC-ID (TBCD String)
    if (in->OptionOmc_Id())
    {
        out->setOMCId(s6a::OMCId(
                    IWFUtils::VectorToString(in->GetOmc_Id().GetArray())));
    }

    // mdt-Configuration to MDT-Configuration (Grouped)
    if (in->OptionMdt_Configuration())
    {
        const MDT_Configuration& iMdt = in->GetMdt_Configuration();
        s6a::MDTConfiguration oMdt;

        // jobType to Job-Type
        oMdt.setJobType(s6a::JobType((s6a::JobType::Value)
                    iMdt.GetJobType().GetValue()));

        // areaScope to Area-Scope
        if (iMdt.OptionAreaScope())
        {
            const AreaScope& iAs = iMdt.GetAreaScope();
            s6a::AreaScope oAs;

            // cgi-List to *Cell-Global-Identity
            if (iAs.OptionCgi_List())
            {
                const CGI_List& iList = iAs.GetCgi_List();
                for (unsigned i = 0; i < iList.GetSize(); i++)
                {
                    oAs.addCellGlobalIdentity(s6a::CellGlobalIdentity(
                                IWFUtils::VectorToString(
                                    iList.ElementAt(i).GetArray())));
                }
            }

            // e-utran-cgi-list to *E-UTRAN-Cell-Global-Identity
            if (iAs.OptionE_utran_cgi_List())
            {
                const E_UTRAN_CGI_List& iList = iAs.GetE_utran_cgi_List();
                for (unsigned i = 0; i < iList.GetSize(); i++)
                {
                    oAs.addEUTRANCellGlobalIdentity(
                            s6a::EUTRANCellGlobalIdentity(IWFUtils::VectorToString(
                                    iList.ElementAt(i).GetArray())));
                }
            }

            // routingAreaId-List to *Routing-Area-Identity
            if (iAs.OptionRoutingAreaId_List())
            {
                const RoutingAreaId_List& iList = iAs.GetRoutingAreaId_List();
                for (unsigned i = 0; i < iList.GetSize(); i++)
                {
                    oAs.addRoutingAreaIdentity(s6a::RoutingAreaIdentity(
                                s6a::RoutingAreaIdentity(IWFUtils::VectorToString(
                                        iList.ElementAt(i).GetArray()))));
                }
            }

            // locationAreaId-List to *Location-Area-Identity
            if (iAs.OptionLocationAreaId_List())
            {
                const LocationAreaId_List& iList = iAs.GetLocationAreaId_List();
                for (unsigned i = 0; i < iList.GetSize(); i++)
                {
                    oAs.addLocationAreaIdentity(s6a::LocationAreaIdentity(
                                s6a::LocationAreaIdentity(IWFUtils::VectorToString(
                                        iList.ElementAt(i).GetArray()))));
                }
            }

            // trackingAreaId-List to *Tracking-Area-Identity
            if (iAs.OptionLocationAreaId_List())
            {
                const TrackingAreaId_List& iList = iAs.GetTrackingAreaId_List();
                for (unsigned i = 0; i < iList.GetSize(); i++)
                {
                    oAs.addTrackingAreaIdentity(s6a::TrackingAreaIdentity(
                                s6a::TrackingAreaIdentity(IWFUtils::VectorToString(
                                        iList.ElementAt(i).GetArray()))));
                }
            }

            oMdt.setAreaScope(oAs);
        }

        // listOfMeasurements to List-Of-Measurements
        if (iMdt.OptionListOfMeasurements())
        {
            // the msbit is the 8th bit of octet 1
            unsigned val = (unsigned)iMdt.GetListOfMeasurements().GetArray()[0];
            oMdt.setListOfMeasurements(s6a::ListOfMeasurements(val));
        }

        // reportingTrigger to Reporting-Trigger
        if (iMdt.OptionReportingTrigger())
        {
            // the msbit is the 8th bit of octet 1
            unsigned val = (unsigned)iMdt.GetReportingTrigger().GetArray()[0];
            oMdt.setReportingTrigger(s6a::ReportingTrigger(val));
        }

        // reportInterval to Report-Interval (enum)
        if (iMdt.OptionReportInterval())
        {
            oMdt.setReportInterval(s6a::ReportInterval(
                        (s6a::ReportInterval::Value)iMdt.GetReportInterval().GetValue()));
        }

        // reportAmount to Report-Amount (enum)
        if (iMdt.OptionReportAmount())
        {
            oMdt.setReportAmount(s6a::ReportAmount(
                        (s6a::ReportAmount::Value)iMdt.GetReportAmount().GetValue()));
        }

        // eventThresholdRSRP tp Event-Threshold-RSRP (integer)
        if (iMdt.OptionEventThresholdRSRP())
        {
            oMdt.setEventThresholdRSRP(s6a::EventThresholdRSRP(
                        iMdt.GetEventThresholdRSRP().GetValue()));
        }

        // eventThresholdRSRP to Event-Threshold-RSRQ (integer)
        if (iMdt.OptionEventThresholdRSRQ())
        {
            oMdt.setEventThresholdRSRQ(s6a::EventThresholdRSRQ(
                        iMdt.GetEventThresholdRSRQ().GetValue()));
        }

        // loggingInterval to Logging-Interval (enum)
        if (iMdt.OptionLoggingInterval())
        {
            oMdt.setLoggingInterval(s6a::LoggingInterval(
                        (s6a::LoggingInterval::Value)iMdt.GetLoggingInterval().GetValue()));
        }

        // loggingDuration to Logging-Duration
        if (iMdt.OptionLoggingDuration())
        {
            oMdt.setLoggingDuration(s6a::LoggingDuration(
                        (s6a::LoggingDuration::Value)iMdt.GetLoggingDuration().GetValue()));
        }

        out->setMDTConfiguration(oMdt);
    }

}

int S6aToMAPHandler::ActivateTraceModeArg_To_IDR(IwfFsm *ctxt,
        const ActivateTraceModeArg *in,
        s6a::InsertSubscriberDataRequest *out)
{
    int ret = ITS_SUCCESS;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    if(in->OptionImsi())
    {
        // IMSI to UserName
        std::string oImsi;
        const std::vector<byte>& vec = in->GetImsi().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
        size_t fPos = oImsi.find('F');
        if (fPos != std::string::npos)
        {
            oImsi.erase(fPos, std::string::npos);
        }
        out->setUserName(diameter::base::UserName(oImsi));
        if (SetDestinationHostAndRealm(ctxt, oImsi, out) != ITS_SUCCESS)
        {
            DLOG_ERROR("ActivateTraceModeArg_To_DSR: Destination Info is not found for IMSI: %s", oImsi.c_str());
            ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
            return ITS_ENOTFOUND;
        }
    }
    else
    {
        DLOG_WARNING("IMSI not present in ActivateTraceModeArg.");
        ctxt->SetErrorCode(MAP_ERR_DATA_MISSING);
        ret = !ITS_SUCCESS;
        return ret;
    }

    // Session binding
    // Build trace data and set it to subscription data
    s6a::TraceData oTdata;
    ActivateTraceModeArg_To_TraceData(ctxt, in, &oTdata);

    s6a::SubscriptionData oSd;
    oSd.setTraceData(oTdata);

    out->setSubscriptionData(oSd);
    return ret;
}

void S6aToMAPHandler::IDA_To_ActivateTraceModeRes(IwfFsm *ctxt,
        const s6a::InsertSubscriberDataAnswer *in,
        ActivateTraceModeRes *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // traceSupportIndicator from Supported-Features flag
    for(int i = 0; i < in->countSupportedFeatures(); i++)
    {
        const s6a::SupportedFeatures& iFl = in->getSupportedFeatures(i);
        if (iFl.getFeatureListID().value() == 1 &&
                iFl.getFeatureList().value() & (1<<10))
        {
            // 10 bit of FeatureList when FeatureListID is 1 is for tracing
            out->SetTraceSupportIndicator(
                    new ActivateTraceModeRes::TraceSupportIndicator());
        }
    }
}

int S6aToMAPHandler::DeactivateTraceModeArg_To_DSR(IwfFsm *ctxt,
        const DeactivateTraceModeArg *in,
        s6a::DeleteSubscriberDataRequest *out)
{
    int ret = ITS_SUCCESS;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    if(in->OptionImsi())
    {
        // IMSI to UserName
        std::string oImsi;
        const std::vector<byte>& vec = in->GetImsi().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
        size_t fPos = oImsi.find('F');
        if (fPos != std::string::npos)
        {
            oImsi.erase(fPos, std::string::npos);
        }
        out->setUserName(diameter::base::UserName(oImsi));

        if (SetDestinationHostAndRealm(ctxt, oImsi, out) != ITS_SUCCESS)
        {
            DLOG_ERROR("DeactivateTraceModeArg_To_DSR: Destination Info is not found for IMSI: %s", oImsi.c_str());
            ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
            return ITS_ENOTFOUND;
        }
    }
    else
    {
        DLOG_WARNING("IMSI not present in ActivateTraceModeArg.");
        ctxt->SetErrorCode(MAP_ERR_DATA_MISSING);
        ret = !ITS_SUCCESS;
        return ret;
    }
    // traceReference and traceReference2 to TraceReference
    std::string traceId = "";

    traceId = IWFUtils::VectorToString(in->GetTraceReference().GetArray());
    if (in->OptionTraceReference2())
    {
        // If reference2 is present, get it from that
        traceId += IWFUtils::VectorToString(in->GetTraceReference2().GetArray());
    }

    out->setTraceReference(s6a::TraceReference(traceId));

    // DSR-Flags AVP: Trace Data Withdrawal shall be set to 1.
    // 8th bit (starting from 0) is Trace withdrawal flag.
    out->setDSRFlags(s6a::DSRFlags(DSR_FLAG_TRACE_DATA_WITHDRAW));
    return ret;
}

void S6aToMAPHandler::DSA_To_DeactivateTraceModeRes(IwfFsm *ctxt,
        const s6a::DeleteSubscriberDataAnswer *in,
        DeactivateTraceModeRes *out)
{
    // nothing to be populated
}

// S13 interface message, application context will be different
void ECR_To_CheckIMEIArg(IwfFsm *ctxt, const s13::MEIdentityCheckRequest* in,
        CheckIMEI_Arg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // TerminalInformation.IMEI to imei
    uint8_t imei[IWF_MAX_E164_SZ];
    int len = IWFUtils::StringToTBCD(
            in->getTerminalInformation().getIMEI().value(),
            imei, IWF_MAX_E164_SZ, 0x0f);
    out->SetImei(new IMEI(IWFUtils::ByteArrayToVector(imei, len)));

    // RequestedEquipmentInfo set to equipmentStatus (bitstring)
    unsigned eqStatus = 1; // corresponds to equipmentStatus
    out->SetRequestedEquipmentInfo(new RequestedEquipmentInfo(
                IWFUtils::UnsignedToBitVector(eqStatus, 8)));
}

void CheckIMEIRes_To_ECA(IwfFsm *ctxt, CheckIMEI_Res *in,
        s13::MEIdentityCheckAnswer* out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // Equipment-Status to equipmentStatus (enum)
    if (in->OptionEquipmentStatus())
    {
        out->setEquipmentStatus(s13::EquipmentStatus(
                    (s13::EquipmentStatus::Value)in->GetEquipmentStatus().GetValue()));
    }
}



int S6aToMAPHandler::AIR_To_SendAuthenticationInfoArgv3(
        IwfFsm *ctxt,
        const s6a::AuthenticationInformationRequest *in,
        SendAuthenticationInfoArg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to imsi
    std::string simsi = in->getUserName().value();
    std::string temp(simsi.substr(0, simsi.find('@')));
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));
    string RuleName("");
    int32_t serviceKey = WILDCARD_SERVICE_KEY;
    int32_t ossn = HLR;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(temp,serviceKey,RuleName,ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return !ITS_SUCCESS;
    }

    // Visited-PLMN-ID to requestedPLMN-Id
    if (in->getVisitedPLMNId().value().size() < MAP_GR_REQUESTING_PLMN_ID_SZ)
    {
        DLOG_ERROR("Could not extract %d bytes of requestingPLMN-Id",
                in->getVisitedPLMNId().value().size());
    }
    else
    {

        uint8_t plmn[3] = {0};
        for(unsigned int i = 0; i < in->getVisitedPLMNId().value().size(); i++)
        {
            plmn[i] = in->getVisitedPLMNId().value()[i];
        }
        ctxt->SetVplmnId(plmn);

        if(IwfController::Instance().Config().LocalConfig().IsVplmnIdToBeValidated() &&
                IWFUtils::CompareVplmnId(&plmn[0], temp,RuleName))
        {
            DLOG_ERROR("VplmnId does not match the configured value for AIR");
            ctxt->SetErrorCode(DIAMETER_ERROR_USER_UNKNOWN);
            return !ITS_SUCCESS;
        }

        out->SetRequestingPLMN_Id(new PLMN_Id(
                    IWFUtils::StringToVector(in->getVisitedPLMNId().value().substr(0, MAP_GR_REQUESTING_PLMN_ID_SZ))));
    }


    // Number-Of-Requested-Vectors to numberOfRequestedVectors
    if (in->containsRequestedEUTRANAuthenticationInfo() && !in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        out->SetNumberOfRequestedVectors(
                new NumberOfRequestedVectors(
                    (long) in->getRequestedEUTRANAuthenticationInfo().getNumberOfRequestedVectors().value()));

    } else if (in->containsRequestedUTRANGERANAuthenticationInfo() && !in->containsRequestedEUTRANAuthenticationInfo())
    {
        out->SetNumberOfRequestedVectors(
                new NumberOfRequestedVectors(
                    (long) in->getRequestedUTRANGERANAuthenticationInfo().getNumberOfRequestedVectors().value()));

    } else if (in->containsRequestedEUTRANAuthenticationInfo() && in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (in->getRequestedEUTRANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetNumberOfRequestedVectors(
                    new NumberOfRequestedVectors(
                        (long) in->getRequestedEUTRANAuthenticationInfo().getNumberOfRequestedVectors().value()));

        }
        else
        {
            out->SetNumberOfRequestedVectors(
                    new NumberOfRequestedVectors(
                        (long) in->getRequestedUTRANGERANAuthenticationInfo().getNumberOfRequestedVectors().value()));
        }
    }

    // segmentationProhibited shall be absent in SendAuthenticationInfoArg

    // Immediate-Response-Preferred to immediateResponsePreferred
    if (in->containsRequestedEUTRANAuthenticationInfo() && !in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (in->getRequestedEUTRANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetImmediateResponsePreferred(new SendAuthenticationInfoArg::ImmediateResponsePreferred());
        }
    } else if (in->containsRequestedUTRANGERANAuthenticationInfo() && !in->containsRequestedEUTRANAuthenticationInfo())
    {
        if (in->getRequestedUTRANGERANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetImmediateResponsePreferred(new SendAuthenticationInfoArg::ImmediateResponsePreferred());
        }
    } else if (in->containsRequestedEUTRANAuthenticationInfo() && in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (in->getRequestedEUTRANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetImmediateResponsePreferred(new SendAuthenticationInfoArg::ImmediateResponsePreferred());
        }
        else if (in->getRequestedUTRANGERANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetImmediateResponsePreferred(new SendAuthenticationInfoArg::ImmediateResponsePreferred());
        }
    }

    // extensionContainer in SendAuthenticationInfoArg shall be absent

    // Re-Synchronization-Info to re-synchronization
    bool isRe_synchronisationInfoSet = false;
    if (in->containsRequestedEUTRANAuthenticationInfo())
    {
        if (in->getRequestedEUTRANAuthenticationInfo().containsReSynchronizationInfo())
        {
            Re_synchronisationInfo *re_synchronisationInfo = new Re_synchronisationInfo();

            re_synchronisationInfo->SetRand(
                    new RAND(IWFUtils::StringToVector(
                            in->getRequestedEUTRANAuthenticationInfo().getReSynchronizationInfo().value().substr(0, MAP_GR_RAND_SZ))));

            re_synchronisationInfo->SetAuts(
                    new AUTS(IWFUtils::StringToVector(
                            in->getRequestedEUTRANAuthenticationInfo().getReSynchronizationInfo().value().substr(16, MAP_GR_AUTS_SZ))));

            if (in->getRequestedEUTRANAuthenticationInfo().getReSynchronizationInfo().value().length() <
                    (MAP_GR_RAND_SZ + MAP_GR_AUTS_SZ))
                DLOG_ERROR("Could not extract %d bytes of re-synchronisationInfo");

            out->SetRe_synchronisationInfo(re_synchronisationInfo);
            isRe_synchronisationInfoSet = true;
        }
        ctxt->SetEUTRANRcvdInReq(true);
    }
    if (in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (in->getRequestedUTRANGERANAuthenticationInfo().containsReSynchronizationInfo() &&
                !isRe_synchronisationInfoSet)
        {
            Re_synchronisationInfo *re_synchronisationInfo = new Re_synchronisationInfo();

            re_synchronisationInfo->SetRand(
                    new RAND(IWFUtils::StringToVector(
                            in->getRequestedUTRANGERANAuthenticationInfo().getReSynchronizationInfo().value().substr(0, MAP_GR_RAND_SZ))));

            re_synchronisationInfo->SetAuts(
                    new AUTS(IWFUtils::StringToVector(
                            in->getRequestedUTRANGERANAuthenticationInfo().getReSynchronizationInfo().value().substr(16, MAP_GR_AUTS_SZ))));

            if (in->getRequestedUTRANGERANAuthenticationInfo().getReSynchronizationInfo().value().length() <
                    (MAP_GR_RAND_SZ + MAP_GR_AUTS_SZ))
                DLOG_ERROR("Could not extract %d bytes of re-synchronisationInfo");

            out->SetRe_synchronisationInfo(re_synchronisationInfo);
        }
        ctxt->SetUTRANRcvdInReq(true);
    }

    if(IwfController::Instance().Config().LocalConfig().IsKASMEGenerationRequired())
    {
        DLOG_DEBUG("Setting RequestingNodeType as SGSN as KASME conversion flag is enabled");
        RequestingNodeType *requestingNodeType = new RequestingNodeType();
        requestingNodeType->SetSgsn();

        out->SetRequestingNodeType(requestingNodeType);
    }
    else
    {
        // Populate requestingNodeType
        if (in->containsRequestedEUTRANAuthenticationInfo() && !in->containsRequestedUTRANGERANAuthenticationInfo())
        {
            RequestingNodeType *requestingNodeType = new RequestingNodeType();
            requestingNodeType->SetMme();

            out->SetRequestingNodeType(requestingNodeType);

        } else if (in->containsRequestedUTRANGERANAuthenticationInfo() && !in->containsRequestedEUTRANAuthenticationInfo())
        {
            RequestingNodeType *requestingNodeType = new RequestingNodeType();
            requestingNodeType->SetSgsn();

            out->SetRequestingNodeType(requestingNodeType);

        } else if (in->containsRequestedEUTRANAuthenticationInfo() && in->containsRequestedUTRANGERANAuthenticationInfo())
        {
            RequestingNodeType *requestingNodeType = new RequestingNodeType();
            requestingNodeType->SetMme_sgsn();

            out->SetRequestingNodeType(requestingNodeType);
        }
    }

    // Number-Of-Requested-Vectors to numberOfRequestedAdditional-Vectors
    if (in->containsRequestedEUTRANAuthenticationInfo() && in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (!in->getRequestedEUTRANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetNumberOfRequestedAdditional_Vectors(
                    new NumberOfRequestedVectors(
                        (long) in->getRequestedEUTRANAuthenticationInfo().getNumberOfRequestedVectors().value()));
        }
        else
        {
            out->SetNumberOfRequestedAdditional_Vectors(
                    new NumberOfRequestedVectors(
                        (long) in->getRequestedUTRANGERANAuthenticationInfo().getNumberOfRequestedVectors().value()));
        }
    }

    // additionalVectorsAreForEPS
    if (in->containsRequestedEUTRANAuthenticationInfo() && in->containsRequestedUTRANGERANAuthenticationInfo())
    {
        if (!in->getRequestedEUTRANAuthenticationInfo().containsImmediateResponsePreferred())
        {
            out->SetAdditionalVectorsAreForEPS(new SendAuthenticationInfoArg::AdditionalVectorsAreForEPS());
        }
    }
    return ITS_SUCCESS;
}

void S6aToMAPHandler::SendAuthenticationInfoResv3_To_AIA(IwfFsm *ctxt,
        const SendAuthenticationInfoRes *in,
        s6a::AuthenticationInformationAnswer *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    TCAP_Component* cpt = ctxt->GetCurrRcvdTcapCpt();
    ITS_USHORT cptType = cpt->GetComponentType();

    if (cptType != TCPPT_TC_RESULT_L)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    // Auth-Session-State -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // Supported-Features shall be absent

    // authenticationSetList or eps-AuthenticationSetList to Authentication-Info
    s6a::AuthenticationInfo authenticationInfo;
    bool setAuthInfo = false;
    if (in->OptionAuthenticationSetList())
    {
        AuthenticationSetList authenticationSetList = in->GetAuthenticationSetList();

        if (authenticationSetList.ChoiceTripletList())
        {
            for (unsigned i = 0; i < authenticationSetList.GetChoiceTripletList().GetSize(); i++)
            {
                s6a::GERANVector geranVector;
                BuildGERANVector(i, authenticationSetList.GetChoiceTripletList().ElementAt(i), geranVector);
                authenticationInfo.addGERANVector(geranVector);
                setAuthInfo = true;
            }
        }
        else if (authenticationSetList.ChoiceQuintupletList())
        {
            DLOG_DEBUG("Size of QuintupletList Rcvd = %d", authenticationSetList.GetChoiceQuintupletList().GetSize());
            DLOG_DEBUG("Is KASME conversion required = %d", IwfController::Instance().Config().LocalConfig().IsKASMEGenerationRequired());
            DLOG_DEBUG("IsEUTRAN vector present in Req = %d", ctxt->IsEUTRANRcvdInReq());
            DLOG_DEBUG("Is Eps_AuthenticationSetList present in Response = %d", in->OptionEps_AuthenticationSetList());
            for (unsigned i = 0; i < authenticationSetList.GetChoiceQuintupletList().GetSize(); i++)
            {
                if(IwfController::Instance().Config().LocalConfig().IsKASMEGenerationRequired())
                {
                    if(ctxt->IsEUTRANRcvdInReq() && !in->OptionEps_AuthenticationSetList())
                    {
                        s6a::EUTRANVector eutranVector;
                        uint8_t vplmn[3] = {0};
                        ctxt->GetVplmnId(vplmn);
                        BuildEUTRANVector(i, authenticationSetList.GetChoiceQuintupletList().ElementAt(i), eutranVector, vplmn);
                        authenticationInfo.addEUTRANVector(eutranVector);
                        setAuthInfo = true;
                    }

                    if(ctxt->IsUTRANRcvdInReq())
                    {
                        s6a::UTRANVector utranVector;
                        BuildUTRANVector(i, authenticationSetList.GetChoiceQuintupletList().ElementAt(i), utranVector);
                        authenticationInfo.addUTRANVector(utranVector);
                        setAuthInfo = true;
                    }
                }
                else
                {
                    s6a::UTRANVector utranVector;
                    BuildUTRANVector(i, authenticationSetList.GetChoiceQuintupletList().ElementAt(i), utranVector);
                    authenticationInfo.addUTRANVector(utranVector);
                    setAuthInfo = true;
                }
            }
        }
    }

    if (in->OptionEps_AuthenticationSetList())
    {
        EPS_AuthenticationSetList eps_AuthenticationSetList = in->GetEps_AuthenticationSetList();

        for (unsigned i = 0; i < eps_AuthenticationSetList.GetSize(); i++)
        {
            s6a::EUTRANVector eutranVector;
            BuildEUTRANVector(i, eps_AuthenticationSetList.ElementAt(i), eutranVector);
            authenticationInfo.addEUTRANVector(eutranVector);
            setAuthInfo = true;
        }
    }
    if(setAuthInfo)
    {
        out->setAuthenticationInfo(authenticationInfo);
    }
}
void S6aToMAPHandler::PUR_To_PurgeMSArgv3(
        IwfFsm *ctxt,
        const s6a::PurgeUERequest *in,
        PurgeMS_Arg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t imsi[IWF_MAX_E164_SZ/2];

    // UserName to IMSI
    std::string simsi = in->getUserName().value();
    IWFUtils::ExtractIMSIFromUserName(simsi, imsi);
    // TODO: FIX is required on ARRAY Size. It can not have static array size IMSI could vary
    out->SetImsi(new IMSI(IWF_FixedArrayToVector(imsi)));

    // SGSN-Number to sgsn-Number
    if(IwfController::Instance().Config().LocalConfig().IsLocalSgsnNumberUsedForMapping())
    {
        its::ByteArray outSgsnNum;
        m_config.GetSGSNNumber(outSgsnNum);
        out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
    }
    else
    {
        std::string sgsn_num = ""; 
        if(m_config.GetSGSNNumberFromOriginHost(in->getOriginHost().value(), sgsn_num))
        {
            DLOG_DEBUG("SGSN Number %s found in SGSN Num Map for OriginHost %s",
                    sgsn_num.c_str(), in->getOriginHost().value().c_str());
            its::ByteArray outSgsnNum;
            uint8_t svar[20] = {0};
            int len = IWFUtils::StringToTBCD(sgsn_num.substr(0,LENGTH_OF_ADDR_DIGITS), svar, 
                    LENGTH_OF_ADDR_DIGITS, 0, true);
            len += IWFUtils::StringToTBCD(sgsn_num.substr(LENGTH_OF_ADDR_DIGITS), 
                    (svar+1), MAX_SGSN_NUM_LEN, 0x0f);
            outSgsnNum.assign(svar, svar + len);
            out->SetSgsn_Number(new ISDN_AddressString(outSgsnNum));
        }
        else
        {
            DLOG_DEBUG("SGSN Number not found in SGSN Num Map for OriginHost %s",in->getOriginHost().value().c_str());
        }
    }
}

void S6aToMAPHandler::PurgeMS_Resv3_To_PUA(IwfFsm *ctxt,
        const PurgeMS_Res *in,
        s6a::PurgeUEAnswer *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    TCAP_Component* cpt = ctxt->GetCurrRcvdTcapCpt();
    ITS_USHORT cptType = cpt->GetComponentType();

    if (cptType != TCPPT_TC_RESULT_L)
    {
        return;
    }

    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);

    // Auth-Session-State -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // PUA Flags: -
    // Freeze M-TMSI shall be set to 1
    // if the freezeM-TMSI parameter was present within PurgeMS-Res; otherwise shall be set to 0.

    //PUA-Flags
    unsigned puaFlags = 0;
    if (in->OptionFreezeM_TMSI())
    {
        puaFlags |= 1;
    }

    // Freeze P-TMSI shall be set to 1
    // if the freezeP-TMSI parameter was present within PurgeMS-Res; otherwise shall be set to 0.
    if (in->OptionFreezeP_TMSI())
    {
        puaFlags  |= 1 << 1;
    }
    out->setPUAFlags(s6a::PUAFlags(puaFlags));
}

int S6aToMAPHandler::CancelLocationArg_To_CLR(IwfFsm *ctxt,
        const CancelLocationArg *in,
        s6a::CancelLocationRequest *out)
{
    int ret = ITS_SUCCESS;
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    // Auth-Session-State -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));

    // IMSI to UserName
    std::string oImsi;
    std::vector<byte> vec;
    if (in->GetIdentity().ChoiceImsi())
    {
        vec = in->GetIdentity().GetChoiceImsi().GetArray();
    }
    else
    {
        vec = in->GetIdentity().GetChoiceImsi_WithLMSI().GetImsi().GetArray();
    }
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    size_t fPos = oImsi.find('F');
    if (fPos != std::string::npos)
    {
        oImsi.erase(fPos, std::string::npos);
    }

    out->setUserName(diameter::base::UserName(oImsi));

    if (SetDestinationHostAndRealm(ctxt, oImsi, out) != ITS_SUCCESS)
    {
        DLOG_ERROR("CancelLocationArg_To_CLR: Destination Info is not found for IMSI: %s", oImsi.c_str());
        ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
        ret = ITS_ENOTFOUND;
        return ret;
    }

    // Set the destination host and realm
    SessionCtxt *sctxt = ctxt->GetTransactionManager()->GetSessionCtxt(oImsi);
    if (sctxt == NULL)
    {
        ret = !ITS_SUCCESS;
        return ret;
    }
    if (!sctxt->HasOldHost())
    {
        out->setDestinationHost(diameter::base::DestinationHost(sctxt->GetOriginHost()));
        out->setDestinationRealm(diameter::base::DestinationRealm(sctxt->GetOriginRealm()));
    }
    else
    {
        out->setDestinationHost(diameter::base::DestinationHost(sctxt->GetOldHost()));
        out->setDestinationRealm(diameter::base::DestinationRealm(sctxt->GetOldRealm()));
    }

    // Supported-Features AVP shall be absent

    // Cancellation-Type
    s6a::CancellationType::Value cancelType = s6a::CancellationType::MME_UPDATE_PROCEDURE;

    if (in->OptionCancellationType())
    {
        if (in->GetCancellationType().GetValue() ==
                CancellationType::CANCELLATION_TYPE_UPDATE_PROCEDURE)
        {
            if (!in->OptionTypeOfUpdate())
            {
                // no type of update
                cancelType = s6a::CancellationType::UPDATE_PROCEDURE_IWF;
            }
            else if (in->GetTypeOfUpdate().GetValue() == TypeOfUpdate::TYPE_OF_UPDATE_MME_CHANGE)
            {
                cancelType = s6a::CancellationType::MME_UPDATE_PROCEDURE;
            }
            else if (in->GetTypeOfUpdate().GetValue() == TypeOfUpdate::TYPE_OF_UPDATE_SGSN_CHANGE)
            {
                cancelType = s6a::CancellationType::SGSN_UPDATE_PROCEDURE;
            }
        }
        else if (in->GetCancellationType().GetValue() ==
                CancellationType::CANCELLATION_TYPE_SUBSCRIPTION_WITHDRAW)
        {
            cancelType = s6a::CancellationType::SUBSCRIPTION_WITHDRAWAL;

            // since the cancel type is subscription withdrawal, the 
            // CLR message should go to the current MME, not old MME
            out->setDestinationHost(diameter::base::DestinationHost(sctxt->GetOriginHost()));
            out->setDestinationRealm(diameter::base::DestinationRealm(sctxt->GetOriginRealm()));
        }
        else if (in->GetCancellationType().GetValue() ==
                CancellationType::CANCELLATION_TYPE_INITIAL_ATTACH_PROCEDURE)
        {
            //cancelType = s6a::CancellationType::INITIAL_ATTACH_PROCEDURE;
            cancelType = (s6a::CancellationType::Value)4;
        }
    }

    out->setCancellationType(s6a::CancellationType(cancelType));

    // CLR-Flags s6a/s6d indicator1 if the TypeOfUpdate parameter was present
    // and indicates "mme-change" else 0
    unsigned s6a_s6dIndicator = 0;
    if (in->OptionTypeOfUpdate() &&
            in->GetTypeOfUpdate().GetValue() == TypeOfUpdate::TYPE_OF_UPDATE_MME_CHANGE)
    {
        s6a_s6dIndicator = 1;
    }
    out->setCLRFlags(s6a::CLRFlags(s6a_s6dIndicator));
    return ret;
}

void S6aToMAPHandler::CLA_To_CancelLocationRes(IwfFsm *ctxt,
        const s6a::CancelLocationAnswer *in,
        CancelLocationRes *out)
{
    // Nothing to do. there is no mapping, it is just an empty message
}

int S6aToMAPHandler::BuildTcapResponse(IwfFsm*, its::TCAP_Component_CCITT*, its::TCAP_Component_CCITT*&, IwfReturnAction&)
{
    //Nothing todo
    int rc = ITS_SUCCESS;
    return rc;
}

int S6aToMAPHandler::SetConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMapHandler::SetConfig Entry");
    int retVal = ITS_SUCCESS;
    IwfS6aToMapConfig s6aMapCfg = translationDataConfig->s6atomapinfo();
    if(s6aMapCfg.has_sgsnnumber())
    {
        DLOG_DEBUG("SgsnNumber = %s",s6aMapCfg.sgsnnumber().c_str());
        m_config.SetSGSNNumber(s6aMapCfg.sgsnnumber());
    }
    if(s6aMapCfg.has_routingprefix())
    {
        DLOG_DEBUG("RoutingPrefix = %s",s6aMapCfg.routingprefix().c_str());
        m_config.SetRoutingPrefix(s6aMapCfg.routingprefix());
    }
    int TotalsgsnAddrNum = s6aMapCfg.sgsnaddress_size();
    if(TotalsgsnAddrNum > 0)
    {
        for(int sgsnnum = 0; sgsnnum < TotalsgsnAddrNum; sgsnnum++)
        {
            SgsnAddresses sgsnAddr = s6aMapCfg.sgsnaddress(sgsnnum);
            if(sgsnAddr.has_orginhost())
            {
                std::string originHost = sgsnAddr.orginhost();
                if(sgsnAddr.has_ipaddress())
                {
                    std::string ipAddress = sgsnAddr.ipaddress();
                    m_config.SetSGSNAddrFromOHost(originHost, ipAddress);
                    DLOG_DEBUG("Added entry in map for SGSNAddr %s for Host %s",ipAddress.c_str(),originHost.c_str());
                }
            }
        }
    }

    int TotalsgsnPrefixNum = s6aMapCfg.sgsnprefixconf_size();
    if(TotalsgsnPrefixNum > 0)
    {
        for(int sgsnnum = 0; sgsnnum < TotalsgsnPrefixNum; sgsnnum++)
        {
            SgsnPrefixesConfig sgsnAddr = s6aMapCfg.sgsnprefixconf(sgsnnum);
            if(sgsnAddr.has_vplmnid())
            {
                std::string vplmnid = sgsnAddr.vplmnid();
                DLOG_DEBUG("VplmnId Rcvd : %s",vplmnid.c_str());
                if(sgsnAddr.has_sgsnprefix())
                {
#if 0
                    std::string mcc = "";
                    std::string mnc = "";
                    std::string vplmn = "";
                    IWFUtils::ExtractMncMcc(vplmnid.c_str(), mcc, mnc);
                    if(!mcc.empty() && !mnc.empty())
                    {
                        unsigned char plmn[4] = {0};
                        IWFUtils::CreateVisitedPlmn(plmn, mcc, mnc);
                        IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmn, 0, true);
                        DLOG_DEBUG("VplmnId after transforming : %s", vplmn.c_str());
                    }
#endif
                    std::string sgsnprefix = sgsnAddr.sgsnprefix();
                    m_config.SetSGSNPrefixFromVplmnId(vplmnid, sgsnprefix);
                    DLOG_DEBUG("Added entry in map for SGSNPrefix %s for VplmnId %s",sgsnprefix.c_str(),vplmnid.c_str());
                }
            }
        }
    }
    DLOG_DEBUG("S6aToMapHandler::SetConfig Exit");
    return retVal;
}

int S6aToMAPHandler::DeleteConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    IwfS6aToMapConfig s6aMapCfg;
    DLOG_DEBUG("S6aToMapHandler::DeleteConfig Entry");
    if( translationDataConfig->has_s6atomapinfo() )
    {
        s6aMapCfg = translationDataConfig->s6atomapinfo();
        int numOfSgsnAddr = s6aMapCfg.sgsnaddress_size();
        if( numOfSgsnAddr > 0)
        {
            for(int sgsnnum = 0; sgsnnum < numOfSgsnAddr; sgsnnum++)
            {
                SgsnAddresses sgsnAddr = s6aMapCfg.sgsnaddress(sgsnnum);
                if(sgsnAddr.has_orginhost())
                {
                    std::string originHost = sgsnAddr.orginhost();
                    if(!(m_config.RemoveSGSNAddrFromOHost(originHost)))
                    {
                        DLOG_ERROR("Failed to delete SGSN config for host %s",originHost.c_str());
                    }
                    else
                    {
                        DLOG_DEBUG("Successfully deleted SGSN config entry for host %s",originHost.c_str());
                    }
                }
            }
        }
        int numOfSgsnPrefix = s6aMapCfg.sgsnprefixconf_size();
        if( numOfSgsnPrefix > 0)
        {
            for(int sgsnnum = 0; sgsnnum < numOfSgsnPrefix; sgsnnum++)
            {
                SgsnPrefixesConfig sgsnAddr = s6aMapCfg.sgsnprefixconf(sgsnnum);
                if(sgsnAddr.has_vplmnid())
                {
                    std::string vplmnid = sgsnAddr.vplmnid();
                    DLOG_DEBUG("VplmnId Rcvd : %s",vplmnid.c_str());
#if 0
                    std::string mcc = "";
                    std::string mnc = "";
                    std::string vplmn = "";
                    IWFUtils::ExtractMncMcc(vplmnid.c_str(), mcc, mnc);
                    if(!mcc.empty() && !mnc.empty())
                    {
                        unsigned char plmn[4] = {0};
                        IWFUtils::CreateVisitedPlmn(plmn, mcc, mnc);
                        IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmn, 0, true);
                        DLOG_DEBUG("VplmnId after transforming : %s", vplmn.c_str());
                    }
#endif
                    if(!(m_config.RemoveSGSNPrefixFromVplmnId(vplmnid)))
                    {
                        DLOG_ERROR("Failed to delete SGSN Prefix config for VplmnId %s",vplmnid.c_str());
                    }
                    else
                    {
                        DLOG_DEBUG("Successfully deleted SGSN Prefix config entry for VplmnId %s",vplmnid.c_str());
                    }
                }
            }
        }
    }
    else
    {
        DLOG_ERROR("S6aToMAPHandler::DeleteConfig no S6aMap configuration to Delete");
        retVal = CMAPI_SRVERROR;
    }
    return retVal;
}

void S6aToMAPHandler::EncodeMsg(AsnObject* p, Octets** octets)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (p == NULL)
    {
        return;
    }

    cout << endl << *p << endl;

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

bool S6aToMAPHandler::IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt, bool &isReq)
{
    return false;
}

bool S6aToMAPHandler::IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq)
{
    return false;
}

int S6aToMAPHandler::BuildMultiTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

void S6aToMAPHandler::HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
        TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
        DIA_BASE_CMD*& outDiaCmd,
        TCAP_Component*& cpt,
        IwfReturnAction& outRetAction)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("S6aToMAPHandler::HandleTimeout Entry");

    DLOG_DEBUG("S6aToMAPHandler::HandleTimeout Exit");
}
void S6aToMAPHandler::StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType)
{
}
void S6aToMAPHandler::SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("S6aToMAPHandler::SetLocalTransId Entry");

    DLOG_DEBUG("S6aToMAPHandler::SetLocalTransId Exit");

}

int S6aToMAPHandler::SetTimerConfig(IwfTimersConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::SetTimerConfig Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("S6aToMAPHandler::SetTimerConfig Exit");
    return retVal;
}

int S6aToMAPHandler::SetMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::SetMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("S6aToMAPHandler::SetMsgSpecCfg Exit");
    return retVal;
}

int S6aToMAPHandler::DeleteMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::DeleteMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("S6aToMAPHandler::DeleteMsgSpecCfg Exit");
    return retVal;
}

int S6aToMAPHandler::LogCDRData(IwfFsm* ctxt, ITS_UINT failureCause)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::LogCDRData Entry");
    int retVal = ITS_SUCCESS;
    DLOG_DEBUG("S6aToMAPHandler::LogCDRData Exit");
    return retVal;
}

int S6aToMAPHandler::TerminateSession(IwfFsm *ctxt,
        TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd)
{
    ITS_UINT ret = ITS_SUCCESS;
    return ret;
}

int S6aToMAPHandler::OnUpstrmFinalReqSent(IwfFsm *ctxt)
{
    int retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT S6aToMAPHandler::SetFeaturesConfig(IwfFeatureConfig *req)
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT S6aToMAPHandler::GetCDRConfig()
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT S6aToMAPHandler::GetCDRFailureCause(IwfFsm* iwfFsm)
{
    return SUCCESS_CALL;
}

bool S6aToMAPHandler::GetSgsnNumberFromConfig(std::string originHost, std::string vplmnId, std::string& sgsnNumber)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("S6aToMAPHandler::GetSgsnNumberFromConfig Entry");

    if(!m_config.GetSGSNNumberFromOriginHost(originHost, sgsnNumber))
    {
        DLOG_DEBUG("SGSN Number Not found for OriginHost %s in SgsnNum Map",originHost.c_str());
        //Generate SGSN Number for this VplmnId and store it
        std::string sgsnPrefix = "";
        if(!m_config.GetSGSNPrefixFromVplmnId(vplmnId, sgsnPrefix))
        {
            DLOG_ERROR("SGSN Prefix is not configured for vplmnId %s",vplmnId.c_str());
            return false;
        }
        else
        {
            std::string routing_prefix = "";
            m_config.GetRoutingPrefix(routing_prefix);
            if(!routing_prefix.empty())
            {
                //NOTE: Add RoutingPrefix, SgsnPrefix prior to SGSN Number
                //sgsnNumber = SGSN_HEADER_DIGITS + routing_prefix + sgsnPrefix + std::to_string ((long long)IwfController::Instance().Config().LocalConfig().GetIncrementedSgsnNumber());
                char hashBuf[9] = {0};
                std::snprintf(hashBuf, 8, "%0lld", (long long)IWFUtils::MurmurHash32(originHost));
                sgsnNumber = SGSN_HEADER_DIGITS + routing_prefix + sgsnPrefix + hashBuf;
                DLOG_DEBUG("SGSN Number %s is generated for OriginHost %s",sgsnNumber.c_str(), originHost.c_str());
                m_config.SetSGSNNumberFromOriginHost(originHost, sgsnNumber);
            }
            else
            {
                DLOG_ERROR("Routing Prefix not configured");
                return false;
            }
        }
    }
    else
    {
        DLOG_DEBUG("SGSN Number %s found for OriginHost %s in Sgsn Map", sgsnNumber.c_str(), originHost.c_str());
    }
    DLOG_DEBUG("S6aToMAPHandler::GetSgsnNumberFromConfig Exit");
    return true;
}

void S6aToMAPHandler::Generateipv4(string& createdAddress)
{
    stringstream createAddress;

    for(int i = 0; i < 4; i++)
    {
        createAddress << ((rand() % 255 +1));
        if(i != 3)
        {
            createAddress << ".";
        }
    }
    createdAddress = createAddress.str();
}

