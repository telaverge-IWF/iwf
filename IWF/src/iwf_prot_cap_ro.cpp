#include "iwf.h"
#include "iwf_prot_cap_ro.h"
#include "iwf_prot_utils.h"
#include "iwf_transaction_manager.h"
#include "ThreadManager.h"
#include <dia_frame.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <ssg_trace.h>
#include <ssg_statistics.h>

#include <sstream>

#define CallingLegId "1"
#define CalledLegId "2"
#define NORMAL_CALL_CLEARING 0x90
#define USER_BUSY 0x91
#define NO_ANSWER_FROM_USER 0x93
#define CAUSE_LOCATION_USER 0x80
#define CAUSE_LOCATION_RLN 0x84
#define OPERATOR_DETERMINED_BARRING 0x08
#define MSCC_AVP_INDEX 0

#define SUB_STR_POS_0 0
#define SUB_STR_POS_2 2
#define SUB_STR_POS_4 4
#define SUB_STR_POS_5 5
#define SUB_STR_LEN_1 1
#define SUB_STR_LEN_2 2
#define SUB_STR_LEN_4 4
#define SUB_STR_LEN_5 5


extern ITSDiaConfig itsDiaConfig;

SsgStackStatistics mapStats;

using namespace cap_v3;
/*CCR Number which will be used for CCR-I/U/T */
static int ccrnum = 0;

    template <typename T>
void SetDefaultAVPs(IwfFsm *ctxt, T *cmd, const char* imsiStr = NULL)
{
    std::string sessId = ctxt->GetDiaSessionId();
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
   DLOG_DEBUG("Sessionid : %s dialogId = %d",sessId.c_str(),ctxt->GetTcapDlgId());
   ThreadManager::GetInstance()->SetSessionId(sessId,ctxt->GetTcapDlgId());

    cmd->setSessionId(diameter::base::SessionId(sessId));
    ctxt->SetDiaSessionId(sessId);
    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    cmd->setOriginHost(lcer->getOriginHost());
    cmd->setOriginRealm(lcer->getOriginRealm());
}

    template <typename T>
void SetDefaultAVPsInAns(IwfFsm *ctxt, T *cmd)
{
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
    cmd->setOriginHost(lcer->getOriginHost());
    cmd->setOriginRealm(lcer->getOriginRealm());
}

    template<typename T>
int SetDestinationHostAndRealm(IwfFsm *ctxt, std::string simsi, ITS_UINT serviceKey, T *cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if( ctxt )
    {
        /* Now fetch SessionCtxt using IMSI for Destination Host&Realm */
        SessionCtxt *sctxt= ctxt->GetTransactionManager()->GetSessionCtxt(simsi);
        if (!sctxt)
        {
            std::string mcc = "", mnc = "";
            std::string appId = DIAMETER_RO_APPLICATION_ID;

            IWFUtils::ExtractMncMcc(simsi, mcc, mnc);
            //std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey)->destRealm();
            std::string RuleName("");
            int32_t skVal = serviceKey;
            int32_t ossn = CAP;
            if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(simsi,skVal,RuleName,ossn))
            {
                DLOG_ERROR("Could not find a RuleName configured.");
                return !ITS_SUCCESS;
            }
            std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName)->destRealm();
            if(!destrealm.empty())
            {
                DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Not Found, Routing to Realm: %s Based on MCC: %s MNC: %s & AppId: %s Configured in Rules", 
                        destrealm.c_str(), mcc.c_str(), mnc.c_str() , appId.c_str());
                diameter::base::DestinationRealm dr(destrealm);
                cmd->setDestinationRealm(dr);
            }
            else
            {
                DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Not Found for:%s, hence doing Realm Based Routing ..", simsi.c_str());
                diameter::base::DestinationRealm dr(itsDiaConfig.getLocalRealmName());
                cmd->setDestinationRealm(dr);
            }
        }
        else
        {
            DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Found for: %s Routing to DestinationHost: %s and DestinationRealm: %s", 
                    simsi.c_str(),sctxt->GetOriginHost().c_str(),sctxt->GetOriginRealm().c_str());
            diameter::base::DestinationHost ds(sctxt->GetOriginHost());
            diameter::base::DestinationRealm dr(sctxt->GetOriginRealm());
            cmd->setDestinationHost(ds);
            cmd->setDestinationRealm(dr);
        }

        return ITS_SUCCESS;
    }
    else
    {
        DLOG_ERROR("IWFFsm in null");
        return !ITS_SUCCESS;
    }
}

inline void LogRoDiaMsg(diameter::Command& cmd, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "CAP-RoHandler RECEIVED Ro message\n";
    }
    else
    {
        str << "CAP-RoHandler SENDING Ro message\n";
    }

    str << cmd << std::endl;
    DLOG_DEBUG("%s\n", str.str().c_str());
}

inline void LogCAPAsnObj(AsnObject& asn, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "CAP-RoHandler RECEIVED CAP message\n";
    }
    else
    {
        str << "CAP-RoHandler SENDING CAP message\n";
    }

    str << asn << std::endl;
    DLOG_DEBUG("%s\n", str.str().c_str());
}

void CAPRoConfig::Parse(Json::Value& val, IwfConfig& conf)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /*Json::Value entry = val["InitialDPArg"];

      Json::Value sub_entry = entry["node-functionality"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'node-functionality' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_nodeFunctionality = sub_entry.asInt();

      sub_entry = entry["originating-ioi"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'originating-ioi' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_origIOI = sub_entry.asString();

      sub_entry = entry["terminating-ioi"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'terminating-ioi' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_termIOI = sub_entry.asString();

      sub_entry = entry["sip-method"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'sip-method' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_sipMethod = sub_entry.asString();

      sub_entry = entry["service-context-id"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'service-context-id' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_servCtxtId = sub_entry.asString();

      sub_entry = entry["cause-code"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'cause-code' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_causeCode = sub_entry.asString();

      sub_entry = entry["msc-service-specific-type"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'service-specific-type' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_idpMscServSpcfcType = sub_entry.asUInt();

      sub_entry = entry["gmsc-service-specific-type"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'service-specific-type' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_idpGmscServSpcfcType = sub_entry.asUInt();

      sub_entry = entry["cpc-service-specific-type"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'service-specific-type' not part "
      "of '/proto-translator/CAP-Ro/'");
}
m_idpCpcServSpcfcType = sub_entry.asUInt();

sub_entry = entry["multiple-services-indicator"];
if(sub_entry.empty())
{
    throw IwfConfigException("'multiple-services-indicator' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_mulServIndicator = sub_entry.asInt();

uint32_t extTeleService;

sub_entry = entry["ext-teleservice-to-service-id-map"];

for (unsigned i = 0; i < sub_entry.size(); i++)
{
    extTeleService = sub_entry[i]["ext-teleservice"].asInt();
    m_extTeleServiceMap[extTeleService] = sub_entry[i]["service-id"].asUInt();
}

uint32_t extBearerService;

sub_entry = entry["ext-bearerservice-to-service-id-map"];

for (unsigned i = 0; i < sub_entry.size(); i++)
{
    extBearerService = sub_entry[i]["ext-bearerservice"].asInt();
    m_extBearerServiceMap[extBearerService] = sub_entry[i]["service-id"].asUInt();
}

entry = val["InitialDPSMSArg"];

sub_entry = entry["sms-node"];
if(sub_entry.empty())
{
    throw IwfConfigException("'sms-node' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_smsNode = sub_entry.asInt();

sub_entry = entry["client-address"];
if(sub_entry.empty())
{
    throw IwfConfigException("'client-address' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_clientAddress = sub_entry.asString();

sub_entry = entry["originator-sccp-address"];
if(sub_entry.empty())
{
    throw IwfConfigException("'originator-sccp-address' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_originatorSCCPAddr = sub_entry.asString();

sub_entry = entry["reply-path-requested"];
if(sub_entry.empty())
{
    throw IwfConfigException("'reply-path-requested' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_rplyPathRqsted = sub_entry.asInt();

sub_entry = entry["msc-service-specific-type"];
if(sub_entry.empty())
{
    throw IwfConfigException("'service-specific-type' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_idpSmsMscServSpcfcType = sub_entry.asUInt();

sub_entry = entry["sgsn-service-specific-type"];
if(sub_entry.empty())
{
    throw IwfConfigException("'service-specific-type' not part "
            "of '/proto-translator/CAP-Ro/'");
}
m_idpSmsSgsnServSpcfcType = sub_entry.asUInt();*/
}

    CAPToRoHandler::CAPToRoHandler()
:IwfTranslator(CAP_TO_RO_STR)
{
}

CAPToRoHandler::~CAPToRoHandler()
{
}

void CAPToRoHandler::BuildTCAPErrorCpt(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::BuildTCAPErrorCpt Entry");
    TCAP_Error *terr = new TCAP_Error();
    terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
    ITS_OCTET invkId = 0;
    CAPRoTransactionContext* userData =
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if(ctxt->GetErrorCode() == ITS_ETIMEOUT)
    {
        DLOG_DEBUG("ERB in TC_END Set = %d", userData->IsOnlyERBinTCEndFlagSet());
        if(!userData->IsOnlyERBinTCEndFlagSet());
        {
            DLOG_DEBUG("Building Release");
            ctxt->SetErrorCode(0);
            BuildRelease(ctxt, NULL, cpt);
            if ( cpt != NULL )
            {
                UPDATE_SSG_STATS_REL_ARG_SENT;
                invkId = ctxt->GetInvkId();
                cpt->SetInvokeID(++invkId);
                ctxt->SetInvkId(invkId);
            }
        }

    }
    else if (ctxt->GetErrorCode())
    {
        UPDATE_SSG_STATS_NUM_OF_TCCOMP_ERR_SENT;
        terr->SetError((ITS_OCTET)ctxt->GetErrorCode());
        ctxt->SetErrorCode(0);
        cpt = terr;
    }
    else
    {
        UPDATE_SSG_STATS_NUM_OF_TCCOMP_ERR_SENT;
        terr->SetError(CAP_ERR_UNEXPECTED_DATA_VALUE);
        cpt = terr;
    }


    DLOG_DEBUG("CAPToRoHandler::BuildTCAPErrorCpt Exit");
}
 
int CAPToRoHandler::BuildTCAPMsg(IwfFsm *ctxt, 
        DIA_BASE_CMD *bcmd,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;

    ret.dir = IWF_RD_TCAP;
    try
    {
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        CAPRoTransactionContext* userData =
            reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
        if (!cmd->isRequest())
        {
            // Request message
            // TODO return respective Application Context for each request
            switch(code)
            {
                case DIA_CMD_CC:
                    {
                        Ro::CreditControlAnswer cca(cmd->getImpl());

                        if ( userData->GetLastSentCCRequestType() == cca.getCCRequestType().value() )
                        {
                            if ( cca.getCCRequestType().value() == Ro::CCRequestType::TERMINATION_REQUEST )
                            {
                                LogRoDiaMsg(cca);
                                ret.action = IWF_RA_CONSUME;
                                std::string rlsStr = cca.getSessionId().value();
                                ITS_UINT sIdx =  cca.getSessionIndex();
                                ReleaseSession(rlsStr, sIdx);

                                if(userData->IsCurrentReceivedTcapContinue())
                                {
                                    DLOG_DEBUG("[Ro::CreditControlAnswer-Terminate] -> [CAP::ReleaseCall]");
                                    BuildRelease(ctxt,&cca,cpt,NORMAL_CALL_CLEARING);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_REL_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        ret.action = IWF_RA_FORWARD;
                                        out->BuildTcapCptList(*cpt);
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                    } 
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                    }
                                }
                                else
                                {
                                    DLOG_DEBUG("Received ERB/ACR in Tcap_End dialogue not need to send Release");
                                    ret.action = IWF_RA_CONSUME;
                                    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                }

                            }
                            else if (cca.getCCRequestType().value() == Ro::CCRequestType::INITIAL_REQUEST )
                            {
                                if(userData->IsIDPSMSReceived())
                                {
                                    userData->SetIDPSMSReceived(false);
                                    DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ReleaseSMSArg]");
                                    BuildReleaseSMS(ctxt,&cca,cpt, OPERATOR_DETERMINED_BARRING);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        ret.action = IWF_RA_FORWARD;
                                        out->BuildTcapCptList(*cpt);
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release for CCA-U");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                    }
                                }
                                else
                                {
                                    if( userData->GetCurrentCCAIResultCode() != ITS_DIA_SUCCESS ||
                                            (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) ||
                                            (CheckMSCCGrantedServiceUnitCCTime(&cca) != ITS_SUCCESS))
                                    {
                                        DLOG_DEBUG("[Ro::CreditControlAnswer-Intial] -> [CAP::ReleaseCall]");
                                        userData->SetLastSentCCRequestType(Ro::CCRequestType::TERMINATION_REQUEST);
                                        BuildRelease(ctxt,&cca,cpt);
                                        if ( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_REL_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ret.action = IWF_RA_FORWARD;
                                            out->BuildTcapCptList(*cpt);
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                        } 
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP Release");
                                            ret.action = IWF_RA_ERROR;
                                            ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                        }
                                    }
                                }

                            }
                        }
                        else
                        {
                            DLOG_ERROR("Answer message CC-Request-Type doesn't match with request message CC-Request-Type. Dropping the message");
                            ret.action = IWF_RA_CONSUME;
                        }

                        break;
                    }
                default:
                    {
                        DLOG_ERROR("Ro::Unhandled diameter Answer message");
                        ret.action = IWF_RA_ERROR;
                    }
            }
        }
        else
        {
            DLOG_DEBUG("Received Request Message");
            rc = !ITS_SUCCESS;
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

    return rc;
}

int CAPToRoHandler::BuildMultiTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ITS_ByteArray buf;
    ITS_USHORT cptType = in->GetComponentType();
    ITS_OCTET invkId = 0;
    if (cptType != TCPPT_TC_INVOKE)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }

    try
    {
        CAPRoTransactionContext* userData =
            reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

        DIA_BASE_CMD *bcmd = ctxt->GetCurrRcvdDiaMsg();
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();

        if((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_CC)
        {
            TCAP_Component *cpt  = NULL;

            Ro::CreditControlAnswer cca(cmd->getImpl());                            
            LogRoDiaMsg(cca); 

            unsigned int resultCode = cca.getResultCode().value();
            unsigned int ccaRequestType = cca.getCCRequestType().value();

            if( userData->GetLastSentCCRequestType() == ccaRequestType )
            {
                DLOG_DEBUG("received CC-Request-Type matches with sent CC-Request-Type process further.");
                switch(ccaRequestType)
                {
                    case Ro::CCRequestType::INITIAL_REQUEST:
                        {
                            bool buildFailed = false;
                            if(userData->IsIDPSMSReceived())
                            {
                                if(resultCode == ITS_DIA_SUCCESS)
                                {
                                    userData->SetIDPSMSReceived(false);
                                    DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportSMSEvent]");
                                    BuildRRBSMS(ctxt,&cca,cpt);
                                    if( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_RRSMS_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        out->BuildTcapCptList(*cpt);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Faild to build CAP RRB for CCA-I");
                                        buildFailed = true;
                                    }
                                    if( cpt != NULL )
                                    {
                                        delete cpt;
                                        cpt = NULL;
                                    }
                                    DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ContinueSMS]");
                                    BuildContinueSMS(ctxt,&cca,cpt);
                                    if( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_CONTINUE_SMS_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        out->BuildTcapCptList(*cpt);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Faild to build CAP Continue for CCA-I");
                                        buildFailed = true;
                                    }
                                    if( cpt != NULL )
                                    {
                                        delete cpt;
                                        cpt = NULL;
                                    }
                                    if( buildFailed )
                                    {
                                        /* incase if building of any one component failed,clean the out list and 
                                         * set Error ret.action */
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                        out->ClearTcapCptList();
                                        buildFailed = false;
                                    }
                                    else
                                    {
                                        ret.action = IWF_RA_FORWARD;
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                    }
                                }
                                else
                                {
                                    ret.isReleaseEnd = true;
                                    ret.action = IWF_RA_FORWARD;
                                }
                            }
                            else
                            {

                                /* set the received result Code for processing ACR*/
                                userData->SetCurrentCCAIResultCode(resultCode);
                                /* Set the flag in userdata if the CCA-I's MSCC-Granted-Service-CCTime is zero which is used in setting termination cause in CCR-T*/
                                if(CheckMSCCGrantedServiceUnitCCTime(&cca) != ITS_SUCCESS)
                                {
                                    userData->SetCurrentCCAMsccGrantedCCTimeZero(true);
                                }

                                if( (resultCode != ITS_DIA_SUCCESS) || 
                                        (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) )
                                {
                                    HandleCCAInitialErrorConditions(ctxt, &cca, cpt,outCmd, ret);
                                }
                                else
                                {
                                    if ( CheckMSCCGrantedServiceUnitCCTime(&cca) != ITS_SUCCESS )
                                    { 
                                        BuildCCRTerminate(ctxt, diameter::base::
                                                TerminationCause::DIAMETER_ADMINISTRATIVE, outCmd);
                                        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                    }
                                    else
                                    {

                                        DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportBCSMEvent]");
                                        BuildRRB(ctxt,&cca,cpt);
                                        if( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_RRBCSM_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            out->BuildTcapCptList(*cpt);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Faild to build CAP RRB for CCA-I");
                                            buildFailed = true;
                                        }
                                        if( cpt != NULL )
                                        {
                                            delete cpt;
                                            cpt = NULL;
                                        }
                                        DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ApplyChargingArg]");
                                        BuildACH(ctxt,&cca,cpt);
                                        if( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_AC_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);

                                            out->BuildTcapCptList(*cpt);
                                            DLOG_DEBUG("ACH Built Successfully appended to the list");
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP ACH for CCA-I");
                                            buildFailed = true;
                                        }
                                        if( cpt != NULL )
                                        {
                                            delete cpt;
                                            cpt = NULL;
                                        }
                                        DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Continue]");
                                        BuildContinue(ctxt,&cca,cpt);
                                        if( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);

                                            out->BuildTcapCptList(*cpt);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Faild to build CAP Continue for CCA-I");
                                            buildFailed = true;
                                        }
                                        if( cpt != NULL )
                                        {
                                            delete cpt;
                                            cpt = NULL;
                                        }
                                        if( buildFailed )
                                        {
                                            /* incase if building of any one component failed,clean the out list and 
                                             * set Error ret.action */
                                            ret.action = IWF_RA_ERROR;
                                            ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                            out->ClearTcapCptList();
                                            buildFailed = false;
                                        }
                                        else
                                        {
                                            ret.action = IWF_RA_FORWARD;
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                        }
                                    } 
                                }
                            }
                            break;
                        }
                    case Ro::CCRequestType::UPDATE_REQUEST:
                        {

                            /* set the received result Code for processing ACR*/
                            userData->SetCurrentCCAUResultCode(resultCode);

                            /* Store the CCA-U's MSCC result code */
                            userData->SetCurrentCCAUMsccResultCode(GetMSCCResultCode(&cca));

                            /* Set the flag in userdata if the CCA-U's MSCC-Granted-Service-CCTime is zero which is used in setting termination cause in CCR-T*/
                            if(CheckMSCCGrantedServiceUnitCCTime(&cca) != ITS_SUCCESS)
                            {
                                userData->SetCurrentCCAMsccGrantedCCTimeZero(true);
                            }

                            if( (resultCode != ITS_DIA_SUCCESS) || 
                                    (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) )
                            {
                                HandleCCAUpdateErrorConditions(ctxt, &cca, cpt,outCmd, ret);
                                if ( cpt != NULL )
                                {
                                    invkId = ctxt->GetInvkId();
                                    cpt->SetInvokeID(++invkId);
                                    ctxt->SetInvkId(invkId);

                                    out->BuildTcapCptList(*cpt);
                                    userData->SetReleaseCallSent(true);
                                }
                                else
                                {
                                    DLOG_ERROR("Unable to Build Release Component for CCA-U With error result code");
                                    ret.action = IWF_RA_ERROR;
                                    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                }
                                if( cpt != NULL)
                                {
                                    delete cpt;
                                    cpt = NULL;
                                }
                            }
                            else
                            {
                                if ( CheckMSCCGrantedServiceUnitCCTime(&cca) != ITS_SUCCESS )
                                {
                                    BuildRelease(ctxt,&cca,cpt);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_REL_ARG_SENT;
                                        //cpt->SetInvokeID(++invokeId);
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);

                                        out->BuildTcapCptList(*cpt);
                                        ret.action = IWF_RA_FORWARD;
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                        userData->SetReleaseCallSent(true);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release for CCA-U");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                    }
                                } 
                                else
                                {
                                    DLOG_DEBUG("[Ro:CreditControlAnswer-Update] -> [CAP:ApplyChargingArg]");
                                    BuildACH(ctxt,&cca,cpt);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_AC_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);

                                        out->BuildTcapCptList(*cpt);
                                        ret.action = IWF_RA_FORWARD;
                                        ret.isReleaseEnd = false;
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Unable to build ACH Component for CCA-Update");
                                        ret.action = IWF_RA_ERROR;
                                    }
                                    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                                }
                                if( cpt != NULL)
                                {
                                    delete cpt;
                                    cpt = NULL;
                                }
                            }
                            break;
                        }
                    default:
                        {
                            DLOG_DEBUG("Unhandled diameter answer");
                            break;
                        }
                }
            }
            else
            {
                DLOG_ERROR("Answer message CC-Request-Type doesn't match with request\
                        message CC-Request-Type. Dropping the message");
                ret.action = IWF_RA_CONSUME;
            }
            if( cpt != NULL)
            {
                delete cpt;
                cpt = NULL;
            }
        }
        else if ((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_RA)
        {
            diameter::base::ReAuthRequest rar(cmd->getImpl());
            LogRoDiaMsg(rar);
            DLOG_DEBUG("[Ro:ReAuthRequest]");
            ret.action = IWF_RA_RESPOND_ONLY;
        }
        else if ((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_AS)
        {
            diameter::base::AbortSessionRequest asr(cmd->getImpl());
            LogRoDiaMsg(asr); 
            TCAP_Component *cpt  = NULL;
            BuildRelease(ctxt,NULL,cpt);
            if ( cpt != NULL )
            {
                UPDATE_SSG_STATS_REL_ARG_SENT;
                //cpt->SetInvokeID(++invokeId);
                invkId = ctxt->GetInvkId();
                cpt->SetInvokeID(++invkId);
                ctxt->SetInvkId(invkId);

                out->BuildTcapCptList(*cpt);
                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                ret.isReleaseEnd = false;
                ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
                userData->SetReleaseCallSent(true);
            }
            else
            {
                DLOG_ERROR("Unable to Build Release Component");
                ret.action = IWF_RA_ERROR;
                ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
            }
            if( cpt != NULL)
            {
                delete cpt;
                cpt = NULL;
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

    return rc;
}

int CAPToRoHandler::BuildDiaMsg(IwfFsm *ctxt, TCAP_Component *cpt, DIA_BASE_CMD *&cmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ITS_LONG opCode = 0; 
    ITS_ByteArray buf; 
    cmd = NULL;

    ret.dir = IWF_RD_DIA;
    ret.action = IWF_RA_FORWARD;

    try
    {
        CAPRoTransactionContext* userData = NULL; 

        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if(inTcapDlg->GetDialogueType() == TCPPT_TC_P_ABORT 
                || inTcapDlg->GetDialogueType() == TCPPT_TC_U_ABORT)
        {
            ret.action = IWF_RA_CONSUME;
            ret.dir = IWF_RD_DIA;
            return rc;
        }

        ITS_USHORT cptType = cpt->GetComponentType();

        switch(cptType)
        {    
            case TCPPT_TC_INVOKE:
                {    
                    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(cpt);
                    tcapIvk->GetOperation(opCode);
                    tcapIvk->GetParameter(buf);

                    if (IwfController::Instance().Config().LocalConfig().InvokeId().IsUseFromConfig())
                    {
                        if ((opCode == cap::OP_initialDP) || (opCode == cap::OP_initialDPSMS))
                        {
                            ctxt->SetInvkId(IwfController::Instance().Config().LocalConfig().InvokeId().StartIdForEachDialog());
                        }
                    }
                    else
                    {
                        if ((opCode == cap::OP_initialDP) || (opCode == cap::OP_initialDPSMS))
                        {
                            ctxt->SetInvkId(tcapIvk->GetInvokeID());
                        }
                    }


                    /* For request messages initiated by the server */
                    switch (opCode)
                    {
                        case cap::OP_initialDP:
                            {
                                Ro::CreditControlRequest *ccr =
                                    new Ro::CreditControlRequest();
                                InitialDPArg idp;
                                Octets octs(buf);
                                idp.Decode(octs);

                                LogCAPAsnObj(idp);
                                UPDATE_SSG_STATS_IDP_ARG_RECVD;
                                DLOG_DEBUG("[CAP:InitialDPArg] - [Ro::CreditControlRequest]");
                                int result = InitialDPArg_To_CCR_Initial(ctxt, &idp, ccr);
                                if(result != ITS_SUCCESS)
                                {
                                    delete ccr;
                                    ccr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, ccr, ccr->getUserName().value().c_str());
                                SetDestinationHostAndRealm(ctxt, ccr->getUserName().value(), idp.GetServiceKey().GetValue(), ccr);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                userData = reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                /* Storing the last Sent CC-Request-Type to be used for 
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro::CCRequestType::INITIAL_REQUEST);
                                userData->SetServiceKey(idp.GetServiceKey().GetValue());
                                LogRoDiaMsg(*ccr, false);
                                break;
                            }

                        case cap::OP_initialDPSMS:
                            {
                                Ro::CreditControlRequest *ccr =
                                    new Ro::CreditControlRequest();
                                InitialDPSMSArg idps;
                                Octets octs(buf);
                                idps.Decode(octs);

                                LogCAPAsnObj(idps);
                                UPDATE_SSG_STATS_IDP_SMS_ARG_RECVD;
                                DLOG_DEBUG("[CAP:InitialDPSMSArg] - [Ro::CreditControlRequest (I)]");

                                int result = InitialDPSMSArg_To_CCR_Initial(ctxt, &idps, ccr);
                                if(result != ITS_SUCCESS)
                                {
                                    delete ccr;
                                    ccr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }

                                SetDefaultAVPs(ctxt, ccr, ccr->getUserName().value().c_str());
                                SetDestinationHostAndRealm(ctxt, ccr->getUserName().value(), idps.GetServiceKey().GetValue(), ccr);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                userData = reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                /* Storing the last Sent CC-Request-Type to be used for 
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro::CCRequestType::INITIAL_REQUEST); 
                                userData->SetServiceKey(idps.GetServiceKey().GetValue());

                                LogRoDiaMsg(*ccr, false);
                                break;
                            }

                        case cap::OP_eventReportBCSM:
                            {   
                                EventReportBCSMArg erb;
                                Octets octs(buf);
                                erb.Decode(octs);

                                LogCAPAsnObj(erb);
                                EventTypeBCSM eventBcsm = erb.GetEventTypeBCSM();
                                UPDATE_SSG_STATS_ERBCSM_ARG_RECVD;

                                TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                                ITS_USHORT tcapDlgType = inTcapDlg->GetDialogueType();
                                userData = reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                /* If dialogue is TC_End and component is erb and event is o-disconnect 
                                 * then build CCR-t and set return action as forward and set the flag*/
                                if((tcapDlgType == TCPPT_TC_END) && cpt->GetLast() &&
                                        (eventBcsm.IsODisconnect() || eventBcsm.IsTDisconnect()))
                                {
                                    userData->SetOnlyERBinTCEndFlag(true);
                                    DLOG_DEBUG("Recieved Only ERB in TC_End with ODisconnect/TDisconnect");
                                    Ro::CreditControlRequest *ccr = new Ro::CreditControlRequest();

                                    EventReportBCSM_to_CCR_Terminate(ctxt, &erb, ccr);
                                    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                    SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetServiceKey(), ccr);
                                    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                    /* Storing the last Sent CC-Request-Type to be used for 
                                     * validating incoming anser msg from ocs*/
                                    userData->SetLastSentCCRequestType(Ro::CCRequestType::TERMINATION_REQUEST);

                                    LogRoDiaMsg(*ccr, false);
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_FORWARD;
 
                                    ret.isReleaseEnd = false;
                                    break;
                                }

                                //NOTE: 1) Check if Release is sent in TcCont and 
                                // 2) ERB is not received with o_disconnect if MO call (or) t_disconnect if MT call.
                                // 3) If both the above conditions satisfy throw an error and consume the message.
                                if(userData->IsReleaseCallSent() && 
                                        ((userData->GetBcsmEventMO() && !eventBcsm.IsODisconnect()) ||
                                         (!userData->GetBcsmEventMO() && !eventBcsm.IsTDisconnect())))
                                {
                                    DLOG_DEBUG("Recieved ERB without ODisconnect/TDisconnect after sending ReleaseCall, So discarding the message.");
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_CONSUME;
                                    break;
                                }
                                //NOTE: Following are the two cases where CCR-T and ReleaseCall(if ERB comes in Tc_Cont) 
                                //are built for the first ERB received.
                                //1) If First ERB is received with o_abandon(MO call) or t_abandon(MT call)
                                //2) ERB with (o_busy or o_NoAnswer -- MO call) or (t_busy or t_NoAnswer -- MT call) 
                                else if((!userData->IsFirstERBrcvd() && 
                                            ((userData->GetBcsmEventMO() && eventBcsm.IsOAbandon()) ||
                                             (!userData->GetBcsmEventMO() && eventBcsm.IsTAbandon()))) ||
                                        ((userData->GetBcsmEventMO() && 
                                          (eventBcsm.IsOCalledPartyBusy() || eventBcsm.IsONoAnswer())) ||
                                         (!userData->GetBcsmEventMO() && 
                                          (eventBcsm.IsTBusy() || eventBcsm.IsTNoAnswer()))))
                                {
                                    //NOTE: Set the flag in UserData if First ERB is received.
                                    userData->SetFirstERBReceived(true);
                                    //NOTE: Set the release Cause in UserData based on the EventTypeBCSM received
                                    CheckEventTypeBCSMAndSetReleaseCause(ctxt, eventBcsm);
                                    /* Set the flag indicating to send Release on receiveing CCA-T
                                     * if the received Dialog type is Continue else set to false */
                                    if ( inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE )
                                    {
                                        if(userData) {
                                            userData->SetCurrentReceivedTcapContinue(true);
                                        }    
                                    } 
                                    else
                                    {
                                        if(userData) {
                                            userData->SetCurrentReceivedTcapContinue(false);
                                        }
                                    }
                                    Ro::CreditControlRequest *ccr = new Ro::CreditControlRequest();

                                    EventReportBCSM_to_CCR_Terminate(ctxt, &erb, ccr);
                                    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                    SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetServiceKey(), ccr);
                                    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                    /* Storing the last Sent CC-Request-Type to be used for 
                                     * validating incoming anser msg from ocs*/
                                    userData->SetLastSentCCRequestType(Ro::CCRequestType::TERMINATION_REQUEST);

                                    LogRoDiaMsg(*ccr, false);
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                    ret.isReleaseEnd = false;
                                }
                                else
                                {
                                    if(userData) {
                                        userData->SetCurrentReceivedTcapContinue(false);
                                    }
                                    DLOG_DEBUG("Recieved ERB without O_Busy/O_NoAnswer/T_Busy/T_NoAnswer Consume it");
                                    /*for O_ANSWER and set retAct to CONSUME*/
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_CONSUME;
                                }
                                break;
                            }

                        case cap::OP_applyChargingReport:
                            {
                                Ro::CreditControlRequest *ccr = new Ro::CreditControlRequest();
                                CallResult cr;
                                Octets octs(buf);
                                cr.Decode(octs);

                                LogCAPAsnObj(cr);
                                UPDATE_SSG_STATS_ACR_ARG_RECVD;

                                TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                                CAPRoTransactionContext* userData =
                                    reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

                                if(userData && inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                                {    
                                    if(userData->GetCurrentCCAUResultCode() == DIAMETER_ERROR_NODE_NOT_RESPONSIBLE || 
                                            userData->GetCurrentCCAUMsccResultCode() == DIAMETER_ERROR_NODE_NOT_RESPONSIBLE)
                                    {    
                                        DLOG_DEBUG(" CCA came with resultcode as DIAMETER_ERROR_NODE_NOT_RESPONSIBLE, so consuming ACR when comes in Tc_End " );
                                        ret.dir = IWF_RD_DIA;
                                        ret.action = IWF_RA_CONSUME;
                                        break;
                                    }    
                                }    

                                CAMEL_CallResult camelcr;
                                const std::vector<byte>& vec = cr.GetArray();
                                //std::vector<byte> destvec;
                                //destvec.assign(vec.begin()+2,vec.end());
                                Octets croctets(vec,vec.size());
                                camelcr.Decode(croctets);

                                LogCAPAsnObj(camelcr);


                                DLOG_DEBUG("[CAP:AppyChargingReportArg] - [ro:CreditControlRequest]");

                                TranslateAcrToCcr(ctxt, &camelcr, ccr, ret);
                                //NOTE: This check is for Error case, i.e Received ACR with CallActive true after ReleaseCall sent.
                                if(ret.action == IWF_RA_CONSUME)
                                {
                                    DLOG_ERROR("Received ACR with CallActive true after sending ReleaseCall, so discarding the message.");
                                    break;
                                }
                                SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetServiceKey(), ccr);

                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                LogRoDiaMsg(*ccr,false);
                                break;
                            }
                        case cap::OP_eventReportSMS:
                            {
                                Ro::CreditControlRequest *ccr = new Ro::CreditControlRequest();
                                EventReportSMSArg ersmsArg;
                                Octets octs(buf);
                                ersmsArg.Decode(octs);
                                userData = reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

                                LogCAPAsnObj(ersmsArg);
                                UPDATE_SSG_STATS_ERSMS_ARG_RECVD;

                                DLOG_DEBUG("[CAP:EventReportSMSArg] - [ro:CreditControlRequest(T)]");

                                EventReportSMSArg_To_CCRT(ctxt, &ersmsArg, ccr);
                                SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetServiceKey(), ccr);

                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);

                                /* Storing the last Sent CC-Request-Type to be used for 
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro::CCRequestType::TERMINATION_REQUEST);

                                LogRoDiaMsg(*ccr,false);
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
                    ret.action = IWF_RA_CONSUME;
                    ret.dir = IWF_RD_DIA;
                    DLOG_ERROR("Tcap Result Component Received .. Consuming it!!");
                    break;
                }   
            case TCPPT_TC_U_ERROR:
                {
                    ret.action = IWF_RA_CONSUME;
                    ret.dir = IWF_RD_DIA;
                    DLOG_ERROR("Tcap Error Component Received .. Consuming it!!");

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
    return rc;
}

int CAPToRoHandler::BuildInterimTCAPMsg(IwfFsm *ctxt, 
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ITS_ByteArray buf;

    return rc;
}

int CAPToRoHandler::BuildTcapResponse(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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
    ITS_OCTET invkId = 0;

    CAPRoTransactionContext* userData =
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    try
    {
        if (opCode == cap::OP_applyChargingReport)
        {
            if ( userData->IsCurrentReceivedTcapContinue() )
            {
                if ( userData->IsReleaseCallSent() )
                {
                    DLOG_ERROR("ReleaseCall already sent in TC_CONTINUE, Hence send TC_END w/o component to close the dialog.");
                    ret.action = IWF_RA_FORWARD_DUMMY_TCEND;
                }
                else
                {
                    DLOG_DEBUG("[ACR with Call-Active False] -> [CAP::ReleaseCall]");
                    BuildRelease(ctxt,NULL,out,NORMAL_CALL_CLEARING);
                    if ( out != NULL )
                    {
                        UPDATE_SSG_STATS_REL_ARG_SENT;
                        invkId = ctxt->GetInvkId();
                        out->SetInvokeID(++invkId);
                        ctxt->SetInvkId(invkId);

                        ret.action = IWF_RA_FORWARD;
                    }
                }
            } 
            else
            {
                DLOG_DEBUG("Received ACR in TC_END no need to send ReleaseCallArg consume");
                ret.action = IWF_RA_CONSUME;
            }
        }
        else if (opCode == cap::OP_eventReportBCSM)
        {
            if ( userData->IsCurrentReceivedTcapContinue() )
            {
                DLOG_DEBUG("[ERB] -> [CAP::ReleaseCall]");
                byte cause = userData->GetReleaseCause();
                BuildRelease(ctxt,NULL,out,cause);
                if ( out != NULL )
                {
                    UPDATE_SSG_STATS_REL_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    out->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);

                    ret.action = IWF_RA_FORWARD;
                } 
                else
                {
                    DLOG_DEBUG("Received ERB  in TC_END no need to send ReleaseCallArg consume");
                    ret.action = IWF_RA_CONSUME;
                }
            }
            else
            {
                DLOG_WARNING("Unhandled opcode");
                ret.action = IWF_RA_CONSUME;
            }
        }
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }

    return rc;
}

int CAPToRoHandler::BuildDiaErrorAnswer(IwfFsm *ctxt, int cmdCode, int error, DIA_BASE_CMD **out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    *out = NULL;

    switch(cmdCode)
    {
        case DIA_CMD_RA:
            {
                diameter::base::ReAuthAnswer* raa = new diameter::base::ReAuthAnswer();
                ConstructErrorAnswer(error, raa);
                SetDefaultAVPsInAns(ctxt, raa);
                LogRoDiaMsg(*raa, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)raa);
                break;
            }
        case DIA_CMD_AS:
            {
                break;
            }
        default:
            {
                break;
            }
    }

    return rc;
}

int CAPToRoHandler::BuildDiaErrorResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;
    const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();

    try
    {
        if( in != NULL )
        {
            DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
            if (cmd->isRequest())
            {
                ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
                if (code == DIA_CMD_RA)
                {
                    DLOG_DEBUG("Constructing RAR out of diaCmd");
                    diameter::base::ReAuthRequest rar(cmd->getImpl());
                    ret.action = IWF_RA_ERROR;
                }
                else
                {
                    ret.action = IWF_RA_DROP;
                }
            }
        }
        ret.action = IWF_RA_DROP;
        ctxt->SetErrorCode(0);
    }

    catch (diameter::CodecExceptionToApp& e) {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for commandCode %d is %d", cmd->getCommandCode(), e.errcode());
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
void CAPToRoHandler::BuildErrorResponse(
        TCAP_Error *tcapError,
        T *out)
{
    if (!tcapError->HasError())
    {
        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        out->setResultCode(res);
        return;
    }

    return;
}

    template <class T>
void CAPToRoHandler::ConstructErrorAnswer(int error,T *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::BaseGenericCommand *diaBaseGenCmd = (diameter::base::BaseGenericCommand *) out;
    diameter::DiaHeader& hdr = const_cast<diameter::DiaHeader&>(diaBaseGenCmd->getHeader());

    /*Set the E BIT Explicitly*/
    hdr.flags.e = 1; 
    DLOG_DEBUG("ConstructErrorAnswer: E-BIT is : %d", hdr.flags.e);
    diameter::base::ResultCode res(error);
    out->setResultCode(res);
}

int CAPToRoHandler::BuildDiaResponse(IwfFsm* ctxt, DIA_BASE_CMD* in, DIA_BASE_CMD*& out, IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;

    try
    {
        // the diameter message is Ro, assuming that the MAP function is called
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (cmd->isRequest())
        {
            if (code == DIA_CMD_RA)
            {
                diameter::base::ReAuthRequest rar(cmd->getImpl());

                DLOG_DEBUG("Constructing ReAuthAnswer for ReAuthRequest");
                diameter::base::ReAuthAnswer *raa = new diameter::base::ReAuthAnswer();

                ConstructRAA(ctxt, &rar, raa);
                SetDefaultAVPsInAns(ctxt, raa);

                LogRoDiaMsg(*raa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)raa);
            }
            if(code == DIA_CMD_AS)
            {
                diameter::base::AbortSessionRequest asr(cmd->getImpl());

                DLOG_DEBUG("Constructing AbortSessionAnswer for AbortSessionRequest");
                diameter::base::AbortSessionAnswer *asa = new diameter::base::AbortSessionAnswer();
                CAPRoTransactionContext* userData = 
                    reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
                if (userData)
                {
                    userData->SetASRReceived(true);
                }

                ConstructASA(ctxt, &asr, asa);
                SetDefaultAVPsInAns(ctxt, asa);

                LogRoDiaMsg(*asa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)asa);
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

void CAPToRoHandler::ConstructRAA(IwfFsm *ctxt, const diameter::base::ReAuthRequest *in,
        diameter::base::ReAuthAnswer *out)
{
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);
}

void CAPToRoHandler::ConstructASA(IwfFsm *ctxt, const diameter::base::AbortSessionRequest *in,
        diameter::base::AbortSessionAnswer *out)
{
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);
}

int CAPToRoHandler::InitialDPArg_To_CCR_Initial(IwfFsm *ctxt,
        const cap_v3::InitialDPArg *in,
        Ro::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;

    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData == NULL)
    {
        userData = new CAPRoTransactionContext();
        ctxt->SetStoredUserData(userData);
    }

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    std::string oImsi = "";
    std::string mcc = "", mnc = "";
    std::string callingGtAddrDigits = "";

    if(in->OptionIMSI())
    {
        const std::vector<byte>& vec = in->GetIMSI().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
        size_t fPos = oImsi.find('F'); 
        if (fPos != std::string::npos)
        {
            oImsi.erase(fPos, std::string::npos);
        }

        IWFUtils::ExtractMncMcc(oImsi, mcc, mnc);
        std::stringstream str1;
        //std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, DIAMETER_RO_APPLICATION_ID, 
        //        in->GetServiceKey().GetValue(), callingGtAddrDigits)->ServiceContextId();
        int32_t skVal = in->GetServiceKey().GetValue();
        std::string RuleName("");
        int32_t ossn = CAP;
        if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,skVal,RuleName,ossn))
        {
            DLOG_ERROR("Could not find a RuleName configured.");
            return !ITS_SUCCESS;
        }
        std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(RuleName,callingGtAddrDigits)->ServiceContextId();
        str1 << mnc << "." << mcc << "." << servCtxtId;

        if(userData->HasServiceContextId())
        {
            userData->ClearServiceContextId();
        }

        Ro::ServiceContextId* serviceContextId = new Ro::ServiceContextId(str1.str());
        out->setServiceContextId(*serviceContextId);
        userData->SetServiceContextId(serviceContextId);

        //std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, DIAMETER_RO_APPLICATION_ID, 
        //        in->GetServiceKey().GetValue())->destRealm();
        std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName,callingGtAddrDigits)->destRealm();
        std::stringstream username;
        if(!(destrealm.empty()))
        {    
            username << oImsi << "@" << destrealm;
        }    
        else 
        {    
            username << oImsi << "@" << itsDiaConfig.getLocalRealmName();
        }    
        out->setUserName(diameter::base::UserName(username.str()));
        userData->SetUserName(username.str());
    }

    Ro::CCRequestType ccRequestType(Ro::CCRequestType::INITIAL_REQUEST);
    out->setCCRequestType(ccRequestType);

    /* Fix: CC-Request-Number AVP for CCR Initial */
    ccrnum = userData->GetCCRequestNumber();
    Ro::CCRequestNumber ccRequestNumber(ccrnum++);
    out->setCCRequestNumber(ccRequestNumber);
    userData->SetCCRequestNumber(ccrnum);

    if(in->OptionTimeAndTimezone())
    {
        uint32_t seconds = 0;
        const std::vector<byte>& vec = in->GetTimeAndTimezone().GetArray();
        ret = TimeStamp(&vec[0], vec.size(), seconds, userData);
        if(ret != ITS_SUCCESS)
        {
            DLOG_ERROR("IWF Error: Validation Failed of Mandatory IE TimeAndTimeZone");
            ctxt->SetErrorCode(CAP_ERR_UNEXPECTED_DATA_VALUE);
            ret = !ITS_SUCCESS;
            return ret;
        }
        diameter::base::EventTimestamp eventTimestamp(seconds);
        out->setEventTimestamp(eventTimestamp);
    }
    else
    {
        DLOG_ERROR("IWF Error: Mandatory IE TimeAndTimeZone not present in IDP");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(userData->HasCUGInformation())
    {
        userData->ClearCUGInformation();
    }
    Ro::ServiceInformation si;
    if(in->OptionCug_Interlock())
    {
        Ro::MMTelInformation mmtelinfo;
        Ro::SupplementaryService ss;
        std::string cugInt;
        const std::vector<byte>& vec = in->GetCug_Interlock().GetArray();
        uint8_t cuginterlock[3] = {0};
        cuginterlock[0] = vec[2];
        cuginterlock[1] = vec[3];
        Ro::CUGInformation* cugInfo = new Ro::CUGInformation((const char*)cuginterlock);

        ss.setCUGInformation(*cugInfo);
        userData->SetCUGInformation(cugInfo);
        mmtelinfo.addSupplementaryService(ss);
        si.setMMTelInformation(mmtelinfo);
    }

    Ro::IMSInformation imsinfo;
    Ro::InterOperatorIdentifier interOperId;
    if(userData->HasSubscriptionId())
    {
        userData->ClearSubscriptionId();
    }
    if(!(in->OptionCallingPartyNumber() && in->OptionCalledPartyNumber())) 
    {
        if(in->OptionCallingPartyNumber())
        {
            std::string oCallingPartyNumber = "";
            const std::vector<byte>& vec = in->GetCallingPartyNumber().GetArray();
            //IWFUtils::TBCDToString(&vec[0], vec.size(), oCallingPartyNumber);
            IWFUtils::TBCDToString(&vec[2], vec.size() - 2, oCallingPartyNumber);

            IWFUtils::TrimAddrSignal(oCallingPartyNumber,this->IsOddIndicator(vec[0]));

            //std::string callingPartyNumber = oCallingPartyNumber.substr(SUB_STR_POS_4);

            imsinfo.addCallingPartyAddress(Ro::CallingPartyAddress(oCallingPartyNumber));

            Ro::SubscriptionId* subsId = new Ro::SubscriptionId();
            if(oCallingPartyNumber.find("sip") != std::string::npos)
            {
                subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_SIP_URI));
                subsId->setSubscriptionIdData(Ro::SubscriptionIdData(oCallingPartyNumber));
                out->addSubscriptionId(*subsId);
            }
            else
            {
                /* E164 and TelURI both are handled in this case as per section 8.1.14 of CAP-Ro Doc */
                subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_E164));
                subsId->setSubscriptionIdData(Ro::SubscriptionIdData(oCallingPartyNumber));
                out->addSubscriptionId(*subsId);
            }
            userData->SetSubscriptionId(subsId);

            if(userData->HasCallingPartyNumber())
            {
                userData->ClearCallingPartyNumber();
            }

            cap_v3::CallingPartyNumber *cpa = new CallingPartyNumber(in->GetCallingPartyNumber()); 
            userData->SetCallingPartyNumber(cpa);
            userData->SetBcsmEventMO(true);

            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::ORIGINATING_ROLE));

            /* To be populated from value configured at IWF end */
            if(!m_config.OriginatingIOI().empty())
            {
                Ro::OriginatingIOI originatingIOI(m_config.OriginatingIOI());
                interOperId.setOriginatingIOI(originatingIOI);
                imsinfo.addInterOperatorIdentifier(interOperId);
            }

        }
        else if(in->OptionCalledPartyNumber())
        {
            std::string oCalledPartyNumber = "";
            const std::vector<byte>& vec = in->GetCalledPartyNumber().GetArray();
            //IWFUtils::TBCDToString(&vec[0], vec.size(), oCalledPartyNumber);
            IWFUtils::TBCDToString(&vec[2], vec.size() - 2, oCalledPartyNumber);
            
            IWFUtils::TrimAddrSignal(oCalledPartyNumber, this->IsOddIndicator(vec[0]));

            //std::string calledPartyNumber = oCalledPartyNumber.substr(SUB_STR_POS_4);

            imsinfo.setCalledPartyAddress(Ro::CalledPartyAddress(oCalledPartyNumber));

            Ro::SubscriptionId *subsId = new Ro::SubscriptionId();
            if(oCalledPartyNumber.find("sip") != std::string::npos)
            {
                subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_SIP_URI));
                subsId->setSubscriptionIdData(Ro::SubscriptionIdData(oCalledPartyNumber));
                out->addSubscriptionId(*subsId);
            }
            else
            {
                subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_E164));
                subsId->setSubscriptionIdData(Ro::SubscriptionIdData(oCalledPartyNumber));
                out->addSubscriptionId(*subsId);
            }
            userData->SetSubscriptionId(subsId);

            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::TERMINATING_ROLE));

            /* To be populated from value configured at IWF end */
            if(!m_config.TerminatingIOI().empty())
            {
                Ro::TerminatingIOI terminatingIOI(m_config.TerminatingIOI()); 
                interOperId.setTerminatingIOI(terminatingIOI);
                imsinfo.addInterOperatorIdentifier(interOperId);
            }
        }
        else
        {
            DLOG_ERROR("IWF Error: Neither CallingPartyNumber nor CalledPartyNumber are present in IDP");
            ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
            ret = !ITS_SUCCESS;
            return ret;
        }
    }
    else
    {
        DLOG_ERROR("IWF Error: Invalid IDP received, both CallingPartyNumber & CalledPartyNumber are present in IDP");
        ctxt->SetErrorCode(CAP_ERR_UNEXPECTED_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(userData->HasIMSChargingIdentifier())
    {
        userData->ClearIMSChargingIdentifier();
    }

    std::string callRef = "";;
    if(in->OptionCallReferenceNumber())
    {
        const std::vector<byte>& vec = in->GetCallReferenceNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), callRef, false , true);
        size_t fPos = callRef.find('F'); 
        if (fPos != std::string::npos)
        {
            callRef.erase(fPos, std::string::npos);
        }
        Ro::IMSChargingIdentifier* imsci = new Ro::IMSChargingIdentifier(callRef);
        imsinfo.setIMSChargingIdentifier(*imsci);
        userData->SetIMSChargingIdentifier(imsci); 
    }
    else
    {
        DLOG_ERROR("IWF Error: Mandatory IE CallReferenceNumber not present in IDP");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(in->OptionCarrier())
    {
        std::string carrierIdentification = "";
        std::string carrierId = "";
        const std::vector<byte>& vec = in->GetCarrier().GetArray();
        IWFUtils::TBCDToString(&vec[1], 1, carrierIdentification, false , true);
        IWFUtils::TBCDToString(&vec[2], (vec.size()-2), carrierId);
        carrierIdentification.append(carrierId);
        if((vec[1] & 0x0f) == 2)
        {
            imsinfo.setCarrierSelectRoutingInformation(Ro::CarrierSelectRoutingInformation(carrierIdentification));
        }
        else if((vec[1] & 0x0f) == 1)
        {
            imsinfo.setCarrierSelectRoutingInformation(Ro::CarrierSelectRoutingInformation(carrierIdentification.substr(SUB_STR_POS_0, SUB_STR_LEN_5)));
        }
    }

    /* To be Populated in Userdata as be same for CCR I,U,T */
    Ro::UserSessionID *userSessId = new Ro::UserSessionID(callRef);
    imsinfo.setUserSessionID(*userSessId);

    if(userData->HasUserSessionId())
    {
        userData->ClearUserSessionID();
    }
    userData->SetUserSessionID(userSessId);
    /* To be populated from configuration */
    if(!m_config.SipMethod().empty())
    {
        Ro::EventType et;
        et.setSIPMethod(Ro::SIPMethod(m_config.SipMethod()));
        imsinfo.setEventType(et);
    }


    /* Node-Functionality AVP to be populate from Configuration file */
    if(m_config.IsNodeFunctionalityFlagSet())
    {
        Ro::NodeFunctionality nodeFunct((Ro::NodeFunctionality::Value)m_config.NodeFunctionality());
        imsinfo.setNodeFunctionality(nodeFunct);
    }

    if(in->OptionInitialDPArgExtension())
    {
        const InitialDPArgExtension &idpae = in->GetInitialDPArgExtension();

        if(idpae.OptionGmscAddress())
        {
            Ro::ServiceSpecificInfo ssi2;
            std::string gmscAddress = "";
            const std::vector<byte>& vec = idpae.GetGmscAddress().GetArray();
            IWFUtils::TBCDToString(&vec[1], (vec.size()-1), gmscAddress);
            size_t fPos = gmscAddress.find('F'); 
            if (fPos != std::string::npos)
            {
                gmscAddress.erase(fPos, std::string::npos);
            }

            ssi2.setServiceSpecificData(Ro::ServiceSpecificData(gmscAddress));
            /*To be populated from configuration file */
            if(m_config.IsIdpGmscServiceSpecifictypeFlagSet())
            {
                ssi2.setServiceSpecificType(Ro::ServiceSpecificType(m_config.IDPGmscServiceSpecificType()));
                imsinfo.addServiceSpecificInfo(ssi2);
            }
        }
    }

    if(in->OptionCallingPartysCategory())
    {
        Ro::ServiceSpecificInfo ssi;
        std::string cpc = "";
        const std::vector<byte>& vec = in->GetCallingPartysCategory().GetArray();
        uint32_t callingPartysCategory = 0;
        callingPartysCategory = uint32_t(vec[0]);
        char buf[6] = {0};
        sprintf(buf, "%u", callingPartysCategory);
        ssi.setServiceSpecificData(Ro::ServiceSpecificData(buf));
        /*To be populated from configuration file */
        if(m_config.IsIdpCpcServSpcfcTypeFlagSet())
        {
            ssi.setServiceSpecificType(Ro::ServiceSpecificType(m_config.IDPCPCServiceSpecificType()));
            imsinfo.addServiceSpecificInfo(ssi);
        }
    }

    if(in->OptionMscAddress())
    {
        Ro::ServiceSpecificInfo ssi1;
        std::string mscAddress = "";
        const std::vector<byte>& vec = in->GetMscAddress().GetArray();
        IWFUtils::TBCDToString(&vec[1], (vec.size()-1), mscAddress);
        size_t fPos = mscAddress.find('F'); 
        if (fPos != std::string::npos)
        {
            mscAddress.erase(fPos, std::string::npos);
        }

        ssi1.setServiceSpecificData(Ro::ServiceSpecificData(mscAddress));
        /*To be populated from configuration file */
        if(m_config.IsIdpMscServiceSpecifictypeFlagSet())
        {
            ssi1.setServiceSpecificType(Ro::ServiceSpecificType(m_config.IDPMscServiceSpecificType()));
            imsinfo.addServiceSpecificInfo(ssi1);
        }
    }
    else
    {
        DLOG_ERROR("IWF Error: Mandatory IE MSCAddress not present in IDP");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(in->OptionLocationInformation())
    {
        const LocationInformation &li = in->GetLocationInformation();
        if(li.OptionCellGlobalIdOrServiceAreaIdOrLAI())
        {
            const CellGlobalIdOrServiceAreaIdOrLAI &cgId = li.GetCellGlobalIdOrServiceAreaIdOrLAI();
            if(cgId.ChoiceCellGlobalIdOrServiceAreaIdFixedLength())
            {
                const std::vector<byte>& vec = cgId.GetChoiceCellGlobalIdOrServiceAreaIdFixedLength().GetArray();
                uint32_t cell ;
                uint8_t cellid[2] = {0};
                cellid[0] = vec[5];
                cellid[1] = vec[6];
                cell = (uint32_t)((((uint32_t)cellid[0])<<8) | cellid[1]);
                char buf[6] = {0};
                sprintf(buf, "%u", cell);
                imsinfo.setAccessNetworkInformation(Ro::AccessNetworkInformation(buf));
            }
            else
            {
                DLOG_ERROR("IWF Error: Mandatory IE CellGlobalIdOrServiceAreaIdFixedLength inside LocationInformation\
                        not present in IDP");
                ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
                ret = !ITS_SUCCESS;
                return ret;
            }
        }
        else
        {
            DLOG_ERROR("IWF Error: Mandatory IE CellGlobalIdOrServiceAreaIdOrLAI inside LocationInformation not present in IDP");
            ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
            ret = !ITS_SUCCESS;
            return ret;
        }
    }
    else
    {
        DLOG_ERROR("IWF Error: Mandatory IE LocationInformation not present in IDP");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(in->OptionOriginalCalledPartyID())
    {
        std::string oCalledPartyNumber = "";
        const std::vector<byte>& vec = in->GetOriginalCalledPartyID().GetArray();
        //IWFUtils::TBCDToString(&vec[0], vec.size(), oCalledPartyNumber);
        IWFUtils::TBCDToString(&vec[2], vec.size() - 2, oCalledPartyNumber);

        IWFUtils::TrimAddrSignal(oCalledPartyNumber, this->IsOddIndicator(vec[0]));

        //std::string calledPartyNumber = oCalledPartyNumber.substr(SUB_STR_POS_4);
        imsinfo.setRequestedPartyAddress(Ro::RequestedPartyAddress(oCalledPartyNumber));
        //imsinfo.addCalledAssertedIdentity(Ro::CalledAssertedIdentity(IWFUtils::VectorToString(in->GetOriginalCalledPartyID().GetArray())));
    }

    /* To be populated in UserData as be same for CCR I,U,T */
    if(in->OptionExt_basicServiceCode())
    {
        const Ext_BasicServiceCode &ebsc = in->GetExt_basicServiceCode();
        Ro::MultipleServicesCreditControl mscc;
        uint32_t si = 0;
        std::string ebs = "";
        userData->SetBasicServiceReceived(true);
        if(ebsc.ChoiceExt_BearerService())
        {
            const std::vector<byte>& vec = ebsc.GetChoiceExt_BearerService().GetArray();
            if(m_config.IsBearerSrvcMapFlagSet())
            {
                const uint32_t extCode = (uint32_t) vec[0] ;
                if( m_config.ServiceIdFromExtBearerService(extCode, si) )
                {
                    mscc.addServiceIdentifier(Ro::ServiceIdentifier(si));
                    userData->SetServiceIdentifier(si);
                    DLOG_DEBUG("mapped ServiceIdentifier from Ext_BearerService : %d to configured value %d",extCode,si);
                }
                else
                {
                    mscc.addServiceIdentifier(Ro::ServiceIdentifier(extCode));
                    userData->SetServiceIdentifier(extCode);
                    DLOG_WARNING("no mapping found setting ServiceIdentifier to recieved Ext_BearerSerice %d",extCode);
                }
                out->addMultipleServicesCreditControl(mscc);
            }
        }
        else
        {
            const std::vector<byte>& vec = ebsc.GetChoiceExt_Teleservice().GetArray();
            if(m_config.IsTeleSrvcMapFlagSet())
            {
                const uint32_t extCode = (uint32_t) vec[0] ;
                if( m_config.ServiceIdFromExtTeleService(extCode, si) )
                {
                    mscc.addServiceIdentifier(Ro::ServiceIdentifier(si));
                    userData->SetServiceIdentifier(si);
                    DLOG_DEBUG("mapped ServiceIdentifier from Ext_TeleService : %d to configured value %d",extCode,si);
                }
                else
                {
                    mscc.addServiceIdentifier(Ro::ServiceIdentifier(extCode));
                    userData->SetServiceIdentifier(extCode);
                    DLOG_WARNING("no mapping found setting ServiceIdentifier to recieved Ext_TeleSerice %d",extCode);
                }

                out->addMultipleServicesCreditControl(mscc);
            }
        }
    }

    if(in->OptionBearerCapability())
    {
        std::string mediadesc = "";
        const BearerCapability &bc = in->GetBearerCapability();
        if(bc.ChoiceBearerCap())
        {
            std::stringstream medianame;
            std::stringstream mediadesc;
            const std::vector<byte>& vec = bc.GetChoiceBearerCap().GetArray();

            FillSDPMediaDescription(&vec[0], vec.size(), medianame, mediadesc);
            Ro::SDPMediaComponent sdpMediaCompo;
            sdpMediaCompo.setSDPMediaName(Ro::SDPMediaName(medianame.str()));
            sdpMediaCompo.addSDPMediaDescription(Ro::SDPMediaDescription(mediadesc.str()));
            imsinfo.addSDPMediaComponent(sdpMediaCompo);
        }
    }

    si.setIMSInformation(imsinfo);
    out->setServiceInformation(si);

    /* To be filled from configuration file (mentioned in document) */
    if(m_config.IsMulServIndicatorFlagSet())
    {
        Ro::MultipleServicesIndicator  multipleServicesIndicator(
                (Ro::MultipleServicesIndicator::Value)m_config.MultipleServiceIndicator());
        out->setMultipleServicesIndicator(multipleServicesIndicator);
    }

    return ret;
}

int CAPToRoHandler::InitialDPSMSArg_To_CCR_Initial(IwfFsm *ctxt,
        const InitialDPSMSArg *in,
        Ro::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData == NULL)
    {
        userData = new CAPRoTransactionContext();
        ctxt->SetStoredUserData(userData);
    }
    userData->SetIDPSMSReceived(true);

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    std::string oImsi;
    std::string mcc = "", mnc = "";
    std::string callingGtAddrDigits = "";
    if(in->OptionIMSI())
    {
        const std::vector<byte>& vec = in->GetIMSI().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
        size_t fPos = oImsi.find('F'); 
        if (fPos != std::string::npos)
        {
            oImsi.erase(fPos, std::string::npos);
        }

        IWFUtils::ExtractMncMcc(oImsi, mcc, mnc);
        std::stringstream str1;
        //std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, DIAMETER_RO_APPLICATION_ID, 
        //        in->GetServiceKey().GetValue(), callingGtAddrDigits)->ServiceContextId();
        std::string RuleName("");
        int32_t skVal = (int32_t)in->GetServiceKey().GetValue();
        int32_t ossn = CAP;
        if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,skVal,RuleName,ossn))
        {
            DLOG_ERROR("Could not find a RuleName configured.");
            return !ITS_SUCCESS;
        }
        std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(RuleName,callingGtAddrDigits)->ServiceContextId();

        str1 << mnc << "." << mcc << "." << servCtxtId;

        if(userData->HasServiceContextId())
        {
            userData->ClearServiceContextId();
        }

        Ro::ServiceContextId* serviceContextId = new Ro::ServiceContextId(str1.str());
        out->setServiceContextId(*serviceContextId);
        userData->SetServiceContextId(serviceContextId);

        //std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, DIAMETER_RO_APPLICATION_ID, 
        //        in->GetServiceKey().GetValue())->destRealm();
        std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName)->destRealm();
        std::stringstream username;
        if(!(destrealm.empty()))
        {    
            username << oImsi << "@" << destrealm;
        }    
        else 
        {    
            username << oImsi << "@" << itsDiaConfig.getLocalRealmName();
        }    
        out->setUserName(diameter::base::UserName(username.str()));
        userData->SetUserName(username.str());
    }

    Ro::CCRequestType ccRequestType(Ro::CCRequestType::INITIAL_REQUEST);
    out->setCCRequestType(ccRequestType);

    ccrnum = userData->GetCCRequestNumber();
    Ro::CCRequestNumber ccRequestNumber(ccrnum++);
    out->setCCRequestNumber(ccRequestNumber);
    userData->SetCCRequestNumber(ccrnum);

    if(in->OptionTimeAndTimezone())
    {
        uint32_t seconds = 0;
        const std::vector<byte>& vec = in->GetTimeAndTimezone().GetArray();
        ret = TimeStamp(&vec[0], vec.size(), seconds, userData);
        if(ret != ITS_SUCCESS)
        {
            DLOG_ERROR("IWF Error: Validation Failed of Mandatory IE TimeAndTimeZone");
            ctxt->SetErrorCode(CAP_ERR_UNEXPECTED_DATA_VALUE);
            ret = !ITS_SUCCESS;
            return ret;
        }
        diameter::base::EventTimestamp eventTimestamp(seconds);
        out->setEventTimestamp(eventTimestamp);
    }
    else
    {
        DLOG_ERROR("IWF Error: Invalid IDPSMS received, TimeAndTimeZone is not present in IDPSMS");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    Ro::ServiceInformation si;

    Ro::IMSInformation imsinfo;
    Ro::SMSInformation smsinfo;

    if(userData->HasSubscriptionId())
    {
        userData->ClearSubscriptionId();
    }

    if(in->OptionCallingPartyNumber())
    {
        std::string callingPartyNumber;
        const std::vector<byte>& vec = in->GetCallingPartyNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), callingPartyNumber);//, false , true);
        size_t fPos = callingPartyNumber.find('F'); 
        if (fPos != std::string::npos)
        {
            callingPartyNumber.erase(fPos, std::string::npos);
        }

        //std::string callingPartyNumber = IWFUtils::VectorToString(in->GetCallingPartyNumber().GetArray());
        imsinfo.addCallingPartyAddress(Ro::CallingPartyAddress(callingPartyNumber.substr(SUB_STR_POS_2)));

        Ro::SubscriptionId* subsId = new Ro::SubscriptionId();
        if(callingPartyNumber.find("sip") != std::string::npos)
        {
            subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_SIP_URI));
            subsId->setSubscriptionIdData(Ro::SubscriptionIdData(callingPartyNumber.substr(SUB_STR_POS_2)));
            out->addSubscriptionId(*subsId);
        }
        else
        {
            subsId->setSubscriptionIdType(Ro::SubscriptionIdType(Ro::SubscriptionIdType::END_USER_E164));
            subsId->setSubscriptionIdData(Ro::SubscriptionIdData(callingPartyNumber.substr(SUB_STR_POS_2)));
            out->addSubscriptionId(*subsId);
        }
        userData->SetSubscriptionId(subsId);
    }
    else
    {
        DLOG_ERROR("IWF Error: Invalid IDPSMS received, CallingPartyNumber is not present in IDPSMS");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }

    if(userData->HasIMSChargingIdentifier())
    {
        userData->ClearIMSChargingIdentifier();
    }

    if(in->OptionSmsReferenceNumber())
    {
        std::string smsRef = "";;
        const std::vector<byte>& vec = in->GetSmsReferenceNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), smsRef, false , true);
        size_t fPos = smsRef.find('F'); 
        if (fPos != std::string::npos)
        {
            smsRef.erase(fPos, std::string::npos);
        }

        Ro::IMSChargingIdentifier* imsci = new Ro::IMSChargingIdentifier(smsRef);
        imsinfo.setIMSChargingIdentifier(*imsci);
        userData->SetIMSChargingIdentifier(imsci); 
    }

    if(ctxt->GetTransactionManager()->GetOrigSSN() == MSC_CAP)
    {
        if(in->OptionMscAddress())
        {
            Ro::ServiceSpecificInfo ssi1;
            std::string mscAddress;
            const std::vector<byte>& vec = in->GetMscAddress().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), mscAddress);//, false, true);
            size_t fPos = mscAddress.find('F'); 
            if (fPos != std::string::npos)
            {
                mscAddress.erase(fPos, std::string::npos);
            }

            ssi1.setServiceSpecificData(Ro::ServiceSpecificData(mscAddress.substr(SUB_STR_POS_2)));

            //ssi1.setServiceSpecificData(Ro::ServiceSpecificData(IWFUtils::VectorToString(in->GetMscAddress().GetArray())));
            /*To be populated from configuration file */
            if(m_config.IsIdpSmsMscServSpcfcTypeFlagSet())
            {
                ssi1.setServiceSpecificType(Ro::ServiceSpecificType(m_config.IDPSMSMscServiceSpecificType()));
            }
            imsinfo.addServiceSpecificInfo(ssi1);
        }

        if(in->OptionLocationInformationMSC())
        {
            const LocationInformation &li = in->GetLocationInformationMSC();
            if(li.OptionCellGlobalIdOrServiceAreaIdOrLAI())
            {
                const CellGlobalIdOrServiceAreaIdOrLAI &cgId = li.GetCellGlobalIdOrServiceAreaIdOrLAI();
                if(cgId.ChoiceCellGlobalIdOrServiceAreaIdFixedLength())
                {
                    const std::vector<byte>& vec = cgId.GetChoiceCellGlobalIdOrServiceAreaIdFixedLength().GetArray();
                    uint32_t cell ;
                    uint8_t cellid[2] = {0};
                    cellid[0] = vec[5];
                    cellid[1] = vec[6];
                    cell = (uint32_t)((((uint32_t)cellid[0])<<8) | cellid[1]);
                    char buf[6] = {0};
                    sprintf(buf, "%u", cell);
                    imsinfo.setAccessNetworkInformation(Ro::AccessNetworkInformation(buf));
                }
            }
        }
    }
    else if(ctxt->GetTransactionManager()->GetOrigSSN() == SGSN_SSN)
    {
        if(in->OptionSgsn_Number())
        {
            Ro::ServiceSpecificInfo ssi;
            std::string sgsnNumber;
            const std::vector<byte>& vec = in->GetSgsn_Number().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), sgsnNumber);//, false , true);
            size_t fPos = sgsnNumber.find('F'); 
            if (fPos != std::string::npos)
            {
                sgsnNumber.erase(fPos, std::string::npos);
            }

            ssi.setServiceSpecificData(Ro::ServiceSpecificData(sgsnNumber.substr(SUB_STR_POS_2)));
            /*To be populated from configuration file */
            if(m_config.IsIdpSmsSgsnServSpcfcTypeFlagSet())
            {
                ssi.setServiceSpecificType(Ro::ServiceSpecificType(m_config.IDPSMSsgsnServiceSpecificType()));
            }
            imsinfo.addServiceSpecificInfo(ssi);
        }

        if(in->OptionLocationInformationGPRS())
        {
            const LocationInformationGPRS &ligprs = in->GetLocationInformationGPRS();
            if(ligprs.OptionCellGlobalIdOrServiceAreaIdOrLAI())
            {
                const std::vector<byte>& vec = ligprs.GetCellGlobalIdOrServiceAreaIdOrLAI().GetArray();
                uint32_t cell ;
                uint8_t cellid[2] = {0};
                cellid[0] = vec[5];
                cellid[1] = vec[6];
                cell = (uint32_t)((((uint32_t)cellid[0])<<8) | cellid[1]);
                char buf[6] = {0};
                sprintf(buf, "%u", cell);
                imsinfo.setAccessNetworkInformation(Ro::AccessNetworkInformation(buf));
            }
        }
    }

    if(in->OptionTPDataCodingScheme())
    {
        std::string tpData;
        const std::vector<byte>& vec = in->GetTPDataCodingScheme().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), tpData, false , true);

        smsinfo.setDataCodingScheme(Ro::DataCodingScheme(atoi(tpData.c_str())));    
    }

    if(in->OptionTPProtocolIdentifier())
    {
        smsinfo.setSMProtocolID(Ro::SMProtocolID(IWFUtils::VectorToString(in->GetTPProtocolIdentifier().GetArray())));
    }

    if(in->OptionSMSCAddress())
    {    
        std::string smscAddress = "";
        const std::vector<byte>& vec = in->GetSMSCAddress().GetArray();
        std::vector<byte> t1((vec.size() - 1)); 
        for(unsigned int i = 0, j = 1; i < vec.size(); i++, j++) 
        {    
            t1[i] = (vec[j] >> 4);
            t1[i] |= (vec[j] << 4);
        }    

        smscAddress = IWFUtils::VectorToString(t1);

        diameter::Address addr1(diameter::Address::E164, smscAddress);
        Ro::SMSCAddress smscaddr(addr1);
        smsinfo.setSMSCAddress(smscaddr);
    }    
    else 
    {    
        DLOG_ERROR("IWF Error: Invalid IDPSMS received, SMSCAddress is not present in IDPSMS");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret; 
    }    
    if(m_config.IsSmsNodeFlagSet())
    {
        Ro::SMSNode smsnode((Ro::SMSNode::Value)m_config.SMSNode());
        smsinfo.setSMSNode(smsnode);
    }

    if(m_config.IsRplyPathRqstedFlagSet())
    {
        Ro::ReplyPathRequested rplypathrqstd((Ro::ReplyPathRequested::Value)m_config.ReplyPathRequested());
        smsinfo.setReplyPathRequested(rplypathrqstd);
    }

    bool isIPv4 = false;
    if(!m_config.ClientAddress().empty())
    {
        if(!(IWFUtils::ValidateIPString(m_config.ClientAddress(), isIPv4)))
        {
            if(isIPv4)
            {
                diameter::Address addr1(diameter::Address::IPV4, m_config.ClientAddress());
                Ro::ClientAddress ca(addr1);
                smsinfo.setClientAddress(ca);
                isIPv4 = false;
            }
            else
            {
                diameter::Address addr1(diameter::Address::IPV6, m_config.ClientAddress());
                Ro::ClientAddress ca(addr1);
                smsinfo.setClientAddress(ca);
            }
        }
    }
    if(!m_config.OriginatorSCCPAddr().empty())
    {
        if(!(IWFUtils::ValidateIPString(m_config.OriginatorSCCPAddr(), isIPv4)))
        {
            if(isIPv4)
            {
                diameter::Address addr1(diameter::Address::IPV4, m_config.OriginatorSCCPAddr());
                Ro::OriginatorSCCPAddress osccpaddr(addr1);
                smsinfo.setOriginatorSCCPAddress(osccpaddr);
                isIPv4 = false;
            }
            else
            {
                diameter::Address addr1(diameter::Address::IPV6, m_config.OriginatorSCCPAddr());
                Ro::OriginatorSCCPAddress osccpaddr(addr1);
                smsinfo.setOriginatorSCCPAddress(osccpaddr);
            }
        }
    }
    si.setSMSInformation(smsinfo);
    si.setIMSInformation(imsinfo);
    out->setServiceInformation(si);
    return ret;
}

unsigned int CAPToRoHandler::GetMSCCResultCode(Ro::CreditControlAnswer *cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_DIA_SUCCESS;
    if( cca->countMultipleServicesCreditControl() )
    {
        Ro::MultipleServicesCreditControl mscc =
            cca->getMultipleServicesCreditControl(MSCC_AVP_INDEX);

        if( mscc.containsResultCode() )
        {
            ret =  mscc.getResultCode().value();
        }
    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
    }

    return ret;
}


int CAPToRoHandler::CheckMSCCGrantedServiceUnitCCTime(Ro::CreditControlAnswer *cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    if( cca->countMultipleServicesCreditControl() )
    {
        Ro::MultipleServicesCreditControl mscc =
            cca->getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsGrantedServiceUnit() )
        {
            Ro::GrantedServiceUnit gsu = mscc.getGrantedServiceUnit();
            if ( !gsu.containsCCTime() ||
                    gsu.getCCTime().value() == 0 )
            {
                ret = !ITS_SUCCESS;
            }
        }
    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
        ret = !ITS_SUCCESS;
    }

    return ret;
}

int CAPToRoHandler::CheckMSCCFinalUnitAction(Ro::CreditControlAnswer *cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    if( cca->countMultipleServicesCreditControl() )
    {
        Ro::MultipleServicesCreditControl mscc =
            cca->getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsFinalUnitIndication() )
        {
            if( (mscc.getFinalUnitIndication().
                        getFinalUnitAction().value()) != Ro::FinalUnitAction::TERMINATE)
            {
                ret = !ITS_SUCCESS;
            }
        }
    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
        ret = !ITS_SUCCESS;
    }

    return ret;
}

int CAPToRoHandler::BuildCCRTerminate(IwfFsm *ctxt,
        diameter::base::TerminationCause::Value causeCode,
        DIA_BASE_CMD *&cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;

    DLOG_DEBUG("BuildCCRTerminate -- Entry");

    Ro::CreditControlRequest *ccr = new Ro::CreditControlRequest();
    Ro::ServiceInformation si;
    Ro::UsedServiceUnit usu;
    Ro::IMSInformation imsinfo;
    Ro::MultipleServicesCreditControl mscc;

    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    ccr->setAuthApplicationId(authApplicationId);

    Ro::CCRequestType ccRequestType(Ro::CCRequestType::TERMINATION_REQUEST);
    ccr->setCCRequestType(ccRequestType);

    diameter::base::TerminationCause terminationCause(causeCode);
    ccr->setTerminationCause(terminationCause);
    if(m_config.IsMulServIndicatorFlagSet())
    {
        Ro::MultipleServicesIndicator  multipleServicesIndicator(
                (Ro::MultipleServicesIndicator::Value)m_config.MultipleServiceIndicator());
        ccr->setMultipleServicesIndicator(multipleServicesIndicator);
    }

    usu.setReportingReason(Ro::ReportingReason(Ro::ReportingReason::FINAL));
    mscc.addUsedServiceUnit(usu);

    if(userData)
    {
        std::string userName = userData->GetUserName();
        if(!userName.empty())
        {
            ccr->setUserName(diameter::base::UserName(userName));
        }
        ccrnum = userData->GetCCRequestNumber();
        Ro::CCRequestNumber ccRequestNumber(ccrnum++);
        ccr->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro::ServiceIdentifier(serviden));
        }

        uint32_t sec = ConstructTimeStamp(userData);
        diameter::base::EventTimestamp eventTimestamp(sec);
        ccr->setEventTimestamp(eventTimestamp);

        //NOTE: setting Role Of Node
        if(userData->GetBcsmEventMO())
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::ORIGINATING_ROLE));
        else 
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::TERMINATING_ROLE));

        if(userData->HasUserSessionId())
        {
            Ro::UserSessionID* sessionId = userData->GetUserSessionID();
            imsinfo.setUserSessionID(*sessionId);
        }
        if(userData->HasIMSChargingIdentifier())
        {
            Ro::IMSChargingIdentifier* imsci = userData->GetIMSChargingIdentifier();
            imsinfo.setIMSChargingIdentifier(*imsci);
        }
        if(userData->HasServiceContextId())
        {
            Ro::ServiceContextId* serviceContextId = userData->GetServiceContextId();
            ccr->setServiceContextId(*serviceContextId);
        }

        if(userData->HasSubscriptionId())
        {
            Ro::SubscriptionId* subsId = userData->GetSubscriptionId();
            ccr->addSubscriptionId(*subsId);
        }
        if(userData->HasCUGInformation())
        {
            Ro::MMTelInformation mmtelinfo;
            Ro::SupplementaryService ss;
            Ro::CUGInformation* cuginfo = userData->GetCUGInformation();
            ss.setCUGInformation(*cuginfo);
            mmtelinfo.addSupplementaryService(ss);
            si.setMMTelInformation(mmtelinfo);
        }
    }

    /* Node-Functionality AVP to be populate from Configuration file */
    if(m_config.IsNodeFunctionalityFlagSet())
    {
        Ro::NodeFunctionality nodeFunct((Ro::NodeFunctionality::Value)m_config.NodeFunctionality());
        imsinfo.setNodeFunctionality(nodeFunct);
    }

    /* Cause Code AVP set to NORMAL_END_OF_SESSION */
    imsinfo.setCauseCode(Ro::CauseCode(NORMAL_END_OF_SESSION));

    si.setIMSInformation(imsinfo);
    ccr->setServiceInformation(si);
    ccr->addMultipleServicesCreditControl(mscc);

    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
    SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetServiceKey(), ccr);
    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
    LogRoDiaMsg(*ccr, false);

    DLOG_DEBUG("BuildCCRTerminate -- Exit");

    return rc;
}



void CAPToRoHandler:: EventReportBCSM_to_CCR_Terminate( IwfFsm *ctxt,
        const cap_v3::EventReportBCSMArg *in,
        Ro::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("ERB to CCR-Terminate");

    Ro::MultipleServicesCreditControl mscc;
    Ro::UsedServiceUnit usu;
    Ro::ServiceInformation si;
    Ro::IMSInformation imsinfo;

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    Ro::CCRequestType ccRequestType(Ro::CCRequestType::TERMINATION_REQUEST);
    out->setCCRequestType(ccRequestType);

    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if(m_config.IsMulServIndicatorFlagSet())
    {
        Ro::MultipleServicesIndicator  multipleServicesIndicator(
                (Ro::MultipleServicesIndicator::Value)m_config.MultipleServiceIndicator());
        out->setMultipleServicesIndicator(multipleServicesIndicator);
    }

    usu.setReportingReason(Ro::ReportingReason(Ro::ReportingReason::FINAL));
    /* Setting CCtime to 0 as either it is ERB with oAbodan case or oDisconnect */
    Ro::CCTime cctime((ITS_UINT)0);
    usu.setCCTime(cctime);
    mscc.addUsedServiceUnit(usu);

    //NOTE: setting CauseCode
    imsinfo.setCauseCode(Ro::CauseCode(NORMAL_END_OF_SESSION));

    if(userData)
    {
        std::string userName = userData->GetUserName();
        if(!userName.empty())
        {
            out->setUserName(diameter::base::UserName(userName));
        }
        ccrnum = userData->GetCCRequestNumber();
        Ro::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro::ServiceIdentifier(serviden));
        }

        uint32_t sec = ConstructTimeStamp(userData);
        diameter::base::EventTimestamp eventTimestamp(sec);
        out->setEventTimestamp(eventTimestamp);

        //NOTE: setting Role Of Node
        if(userData->GetBcsmEventMO())
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::ORIGINATING_ROLE));
        else 
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::TERMINATING_ROLE));

        if(userData->HasUserSessionId())
        {
            Ro::UserSessionID* sessionId = userData->GetUserSessionID();
            imsinfo.setUserSessionID(*sessionId);
        }

        if(userData->HasIMSChargingIdentifier())
        {
            Ro::IMSChargingIdentifier* imsci = userData->GetIMSChargingIdentifier();
            imsinfo.setIMSChargingIdentifier(*imsci);
        }

        if(userData->HasServiceContextId())
        {
            Ro::ServiceContextId* serviceContextId = userData->GetServiceContextId();
            out->setServiceContextId(*serviceContextId);
        }

        if(userData->HasSubscriptionId())
        {
            Ro::SubscriptionId* subsId = userData->GetSubscriptionId();
            out->addSubscriptionId(*subsId);
        }

        if(userData->HasCUGInformation())
        {
            Ro::MMTelInformation mmtelinfo;
            Ro::SupplementaryService ss;
            Ro::CUGInformation* cuginfo = userData->GetCUGInformation();
            ss.setCUGInformation(*cuginfo);
            mmtelinfo.addSupplementaryService(ss);
            si.setMMTelInformation(mmtelinfo);
        } 
    }

    /* Node-Functionality AVP to be populate from Configuration file */
    if(m_config.IsNodeFunctionalityFlagSet())
    {
        Ro::NodeFunctionality nodeFunct((Ro::NodeFunctionality::Value)m_config.NodeFunctionality());
        imsinfo.setNodeFunctionality(nodeFunct);
    }

    if((userData && userData->IsASRReceived()) || (userData &&
            userData->IsCurrentCCAMsccGrantedCCTimeZero()))
    {
        userData->SetASRReceived(false);
        out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE));
    }
    else
    {
        out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));
    }

    si.setIMSInformation(imsinfo);
    out->setServiceInformation(si);
    out->addMultipleServicesCreditControl(mscc);

}

int CAPToRoHandler::BuildRRB(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("BuildRRB -- Entry"); 
    int rc = ITS_SUCCESS;
    try
    {
        RequestReportBCSMEventArg rrbArg;                                       
        CCA_Initial_to_RequestReportBCSMEvent( ctxt, cca, &rrbArg);     

        Octets* buf = rrbArg.Encode();                                        

        TCAP_Invoke *ivk = new TCAP_Invoke();                                 
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_requestReportBCSMEvent);
        ivk->SetParameter(buf->GetArray());                                   
        cpt = ivk;                                                            
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }

        LogCAPAsnObj(rrbArg, false);
    }

    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("BuildRRB Unknown Exception");
    }
    DLOG_DEBUG("BuildRRB -- Exit");                      
    return rc;
}

int CAPToRoHandler::BuildRRBSMS(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("BuildRRBSMS -- Entry");                      
    int rc = ITS_SUCCESS;
    try
    {
        cap_v3::RequestReportSMSEventArg rrbsms;
        CCA_Initial_to_RequestReportSMSEvent(ctxt, cca, &rrbsms);
        Octets* buf = rrbsms.Encode();

        TCAP_Invoke *ivk = new TCAP_Invoke();
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_requestReportSMSEvent);
        ivk->SetParameter(buf->GetArray());
        cpt = ivk;
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }

        LogCAPAsnObj(rrbsms, false);
    }

    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("BuildRRBSMS Unknown Exception");
    }
    DLOG_DEBUG("BuildRRBSMS -- Exit");                      
    return rc;
}

int CAPToRoHandler::BuildACH(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("BuildACH -- Entry");                      
    int rc = ITS_SUCCESS;
    try
    {
        ApplyChargingArg achArg;                                       

        CCA_to_ApplyChargingArg( ctxt, cca, &achArg);     
        Octets* buf = achArg.Encode();                                        

        TCAP_Invoke *ivk = new TCAP_Invoke();                                 
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_applyCharging);
        ivk->SetParameter(buf->GetArray());                                   
        cpt = ivk;                                                            
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }

        LogCAPAsnObj(achArg, false);
    }

    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("BuildACH Unkown Error");
    }

    DLOG_DEBUG("BuildACH -- Exit");                      

    return rc;
}

int CAPToRoHandler::BuildContinue(IwfFsm *ctxt,
        Ro::CreditControlAnswer *in,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    DLOG_DEBUG("BuildContinue -- Entry");
    TCAP_Invoke *ivk = new TCAP_Invoke();                                 
    ivk->SetClass(TCAP_OPERATION_CLASS);
    ivk->SetOperation( cap:: OP_continue );
    cpt = ivk;   
    DLOG_DEBUG("BuildContinue -- Exit");
    return rc;
}

int CAPToRoHandler::BuildContinueSMS(IwfFsm *ctxt,
        Ro::CreditControlAnswer *in,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    DLOG_DEBUG("BuildContinueSMS -- Entry");
    TCAP_Invoke *ivk = new TCAP_Invoke();                                 
    ivk->SetClass(TCAP_OPERATION_CLASS);
    ivk->SetOperation( cap::OP_continueSMS);
    cpt = ivk;   
    DLOG_DEBUG("BuildContinueSMS -- Exit");
    return rc;
}

int CAPToRoHandler::BuildRelease(IwfFsm *ctxt,
        Ro::CreditControlAnswer *in,
        TCAP_Component *&cpt, byte causecode)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("BuildRelease -- Entry");
    int rc = ITS_SUCCESS;
    byte causeLoc = CAUSE_LOCATION_RLN;
    try
    {
        /* IWF sends the ReleaseCall with Cause set to Normal Unspecified(31) by default */
        if( causecode == NORMAL_CALL_CLEARING ) 
        {
            causeLoc = CAUSE_LOCATION_USER;
        }
        byte array[] = {causeLoc, causecode };
        ReleaseCallArg releaseCall(ArrayToVector(array, ARRAY_SIZE(array)));
        Octets* buf = releaseCall.Encode();                                        

        TCAP_Invoke *ivk = new TCAP_Invoke();                                 
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap:: OP_releaseCall);
        ivk->SetParameter(buf->GetArray());                                   
        cpt = ivk;                                                            
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }
        LogCAPAsnObj(releaseCall, false);
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("Unknown Exception");
    }
    DLOG_DEBUG("BuildRelease -- Exit");
    return rc;
}

int CAPToRoHandler::BuildReleaseSMS(IwfFsm *ctxt,
        Ro::CreditControlAnswer *in,
        TCAP_Component *&cpt, byte causeCode)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("BuildReleaseSMS -- Entry");
    int rc = ITS_SUCCESS;
    try
    {
        /* IWF sends the ReleaseCall with Cause set to Normal Unspecified(31) */
        byte array[] = {causeCode};
        ReleaseSMSArg releaseSMS(ArrayToVector(array, ARRAY_SIZE(array)));
        Octets* buf = releaseSMS.Encode();                                        

        TCAP_Invoke *ivk = new TCAP_Invoke();                                 
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_releaseSMS);
        ivk->SetParameter(buf->GetArray());                                   
        cpt = ivk;                                                            
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }
        LogCAPAsnObj(releaseSMS, false);
    }
    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        DLOG_ERROR("Unknown Exception");
    }
    DLOG_DEBUG("BuildReleaseSMS -- Exit");
    return rc;
}

int CAPToRoHandler::BuildBcsmEvent(cap_v3::EventTypeBCSM eventType,
        cap_v3::MonitorMode monitorMode,
        std::string legid,
        cap_v3::BCSMEvent *bcsmEvent)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    bcsmEvent->SetEventTypeBCSM(new cap_v3::EventTypeBCSM(eventType));

    // Monitor-Mode ie should be mapped to notifyAndContinue or Interrupt
    bcsmEvent->SetMonitorMode(new MonitorMode(monitorMode));

    //LegID should be populated based on eventTypeBCSM
    std::vector<byte> vec = IWFUtils::StringToVector(legid);
    vec[0] = vec[0]&0xF;
    LegType* lt = new LegType(vec);
    LegID legId;
    legId.SetChoiceSendingSideID(lt);

    bcsmEvent->SetLegID(legId);
    return rc;
}

void  CAPToRoHandler::CCA_Initial_to_RequestReportBCSMEvent(IwfFsm *ctxt,
        const Ro::CreditControlAnswer *in,
        cap_v3::RequestReportBCSMEventArg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    cap_v3::RequestReportBCSMEventArg::BcsmEvents reqReportingBcsmevent;
    BCSMEvent bcsmEvent;

    CAPRoTransactionContext* userData =
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    /* MO Call,populate all the DPs related to 'O' */
    if (userData && userData->GetBcsmEventMO() )    
    {
        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_OCALLED_PARTY_BUSY,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CallingLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_OABANDON,
                cap_v3::MonitorMode::MONITOR_MODE_NOTIFY_AND_CONTINUE,
                CallingLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);
    }
    else //if MT call populate all the DP's realted to 'T'
    {
        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TBUSY,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TNO_ANSWER ,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER ,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT ,
                cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED,
                CalledLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);

        BuildBcsmEvent(cap_v3::EventTypeBCSM::EVENT_TYPE_BCSM_TABANDON ,
                cap_v3::MonitorMode::MONITOR_MODE_NOTIFY_AND_CONTINUE,
                CallingLegId,
                &bcsmEvent);
        reqReportingBcsmevent.AddElement(bcsmEvent);
    }

    out->SetBcsmEvents(reqReportingBcsmevent);
}

void  CAPToRoHandler::CCA_Initial_to_RequestReportSMSEvent(IwfFsm *ctxt,
        const Ro::CreditControlAnswer *in,
        cap_v3::RequestReportSMSEventArg *out)
{
    RequestReportSMSEventArg::SMSEvents smse;
    SMSEvent smsev;
    SMSEvent smsev1;
    smsev.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_FAILURE));
    smsev.SetMonitorMode(MonitorMode::MONITOR_MODE_INTERRUPTED);
    smsev1.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_SUBMITTED));
    smsev1.SetMonitorMode(MonitorMode::MONITOR_MODE_INTERRUPTED);
    smse.AddElement(smsev);
    smse.AddElement(smsev1);
    out->SetSMSEvents(smse);
}

void CAPToRoHandler:: CCA_to_ApplyChargingArg(IwfFsm *ctxt,
        const Ro::CreditControlAnswer *in,
        cap_v3::ApplyChargingArg *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    cap_v3::CAMEL_AChBillingChargingCharacteristics achBilling;
    cap_v3::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging timeDurCharging;

    try
    {
        //Set the maxCallPeriodDuration from Granted-Service-Unit's CC-Time  
        if ( in->countMultipleServicesCreditControl() )
        {
            //NOTE: Assuming that only one MSCC will get from OCS for mapping all the IE's on cap side.
            Ro::MultipleServicesCreditControl serviceCreditControl = 
                in->getMultipleServicesCreditControl(MSCC_AVP_INDEX);

            if ( serviceCreditControl.containsGrantedServiceUnit() )
            {
                if(serviceCreditControl.getGrantedServiceUnit().containsCCTime())
                {
                    CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                        MaxCallPeriodDuration maxCallPeriodDur(serviceCreditControl.
                                getGrantedServiceUnit().getCCTime().value());

                    timeDurCharging.SetMaxCallPeriodDuration( maxCallPeriodDur);
                }
                if(serviceCreditControl.getGrantedServiceUnit().containsTariffTimeChange())
                {
                    CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging
                        ::TariffSwitchInterval tsi(serviceCreditControl.
                                getGrantedServiceUnit().getTariffTimeChange().value());

                    timeDurCharging.SetTariffSwitchInterval(tsi);
                }
            }

            /*ReleaseIfDurationExceeded is populated if Final-Unit-Indication is 
             *     not present in Multiple-Service-Credit-Conrol */
            if(serviceCreditControl.containsFinalUnitIndication())
            {
                Ro::FinalUnitIndication finalUnitInd = serviceCreditControl.getFinalUnitIndication();
                if( finalUnitInd.getFinalUnitAction().value() == Ro::FinalUnitAction::TERMINATE)
                {
                    CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                        ReleaseIfdurationExceeded releaseIfDurExceed(true);

                    timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);
                }
                else 
                {
                    CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                        ReleaseIfdurationExceeded releaseIfDurExceed(false);

                    timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);
                }
            }
            else if(!serviceCreditControl.containsFinalUnitIndication())
            {
                CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                    ReleaseIfdurationExceeded releaseIfDurExceed(false);

                timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);
            }
        }
        //Check for the Low Balance indication avp if present set the Tone parameter
        if ( in->containsLowBalanceIndication() )
        {
            if (in->getLowBalanceIndication().value())
            {
                CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                    Tone tone(true);
                timeDurCharging.SetTone(tone);
            }
        }
#if 0
        else
        {
            CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                Tone tone(false);
            timeDurCharging.SetTone(tone);
        }
#endif

        achBilling.SetChoiceTimeDurationCharging((timeDurCharging));
        LogCAPAsnObj(achBilling);
        Octets* achBillingBuf = achBilling.Encode();

        AChBillingChargingCharacteristics *AChBilling = new AChBillingChargingCharacteristics((achBillingBuf->GetArray()));

        out->SetAChBillingChargingCharacteristics((AChBilling));

        /* SendingSideID values is set to leg1*/
        byte array[] = { 0x01 };
        LegType* lt = new LegType(ArrayToVector(array, ARRAY_SIZE(array)));
        SendingSideID *sid = new SendingSideID();
        sid->SetChoiceSendingSideID(lt);
        out->SetPartyToCharge((SendingSideID*)sid);

        if(achBillingBuf != NULL)
        {
            delete achBillingBuf;
            achBillingBuf = NULL;
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
}

void CAPToRoHandler::HandleCCAInitialErrorConditions(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("HandleCCAInitialErrorConditions -- Entry");

    ret.action = IWF_RA_FORWARD;
    ret.isReleaseEnd = true;

    DLOG_DEBUG("HandleCCAInitialErrorConditions -- Exit");
}

void CAPToRoHandler::HandleCCAUpdateErrorConditions(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("HandleCCAUpdateErrorConditions -- Entry");

    BuildRelease(ctxt, cca , cpt);
    UPDATE_SSG_STATS_REL_ARG_SENT;
    ret.action = IWF_RA_FORWARD;
    ret.isReleaseEnd = false;
    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);

    DLOG_DEBUG("HandleCCAUpdateErrorConditions -- Exit");
}

void CAPToRoHandler::HandleCCATerminateErrorConditions(IwfFsm *ctxt,
        Ro::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("HandleCCATerminateErrorConditions -- Entry");

    BuildRelease(ctxt, cca , cpt);
    UPDATE_SSG_STATS_REL_ARG_SENT;
    ret.action = IWF_RA_FORWARD;
    ret.isReleaseEnd = true;
    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV2_gsmSSF_to_gsmSCF_AC);

    DLOG_DEBUG("HandleCCATerminateErrorConditions -- Exit");
}

void CAPToRoHandler::TranslateAcrToCcr(IwfFsm* ctxt, 
        const CAMEL_CallResult *in, 
        Ro::CreditControlRequest *out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Ro::MultipleServicesCreditControl mscc;
    Ro::UsedServiceUnit usu;
    Ro::ServiceInformation si;
    Ro::IMSInformation imsinfo;

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(m_config.IsMulServIndicatorFlagSet())
    {
        Ro::MultipleServicesIndicator  multipleServicesIndicator(
                (Ro::MultipleServicesIndicator::Value)m_config.MultipleServiceIndicator());
        out->setMultipleServicesIndicator(multipleServicesIndicator);
    }

    if(userData)
    {
        std::string userName = userData->GetUserName();
        if(!userName.empty())
        {
            out->setUserName(diameter::base::UserName(userName));
        }
        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro::ServiceIdentifier(serviden));
        }


        uint32_t sec = ConstructTimeStamp(userData);
        diameter::base::EventTimestamp eventTimestamp(sec);
        out->setEventTimestamp(eventTimestamp);

        //NOTE: setting Role Of Node
        if(userData->GetBcsmEventMO())
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::ORIGINATING_ROLE));
        else 
            imsinfo.setRoleOfNode(Ro::RoleOfNode(Ro::RoleOfNode::TERMINATING_ROLE));

        if(userData->HasUserSessionId())
        {
            Ro::UserSessionID* sessionId = userData->GetUserSessionID();
            imsinfo.setUserSessionID(*sessionId);
        }

        if(userData->HasIMSChargingIdentifier())
        {
            Ro::IMSChargingIdentifier* imsci = userData->GetIMSChargingIdentifier();
            imsinfo.setIMSChargingIdentifier(*imsci);
        }

        if(userData->HasServiceContextId())
        {
            Ro::ServiceContextId* serviceContextId = userData->GetServiceContextId();
            out->setServiceContextId(*serviceContextId);
        }

        if(userData->HasSubscriptionId())
        {
            Ro::SubscriptionId* subsId = userData->GetSubscriptionId();
            out->addSubscriptionId(*subsId);
        }

        if(userData->HasCUGInformation())
        {
            Ro::MMTelInformation mmtelinfo;
            Ro::SupplementaryService ss;
            Ro::CUGInformation* cuginfo = userData->GetCUGInformation();
            ss.setCUGInformation(*cuginfo);
            mmtelinfo.addSupplementaryService(ss);
            si.setMMTelInformation(mmtelinfo);
        }

        /* Node-Functionality AVP to be populate from Configuration file */
        if(m_config.IsNodeFunctionalityFlagSet())
        {
            Ro::NodeFunctionality nodeFunct((Ro::NodeFunctionality::Value)m_config.NodeFunctionality());
            imsinfo.setNodeFunctionality(nodeFunct);
        }

        if(in->ChoiceTimeDurationChargingResult())
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr = in->GetChoiceTimeDurationChargingResult();

            if(tdcr.GetCallActive().GetValue())
            {
                //NOTE: This check is for Error case, i.e Received ACR with CallActive true after ReleaseCall sent.
                if (userData->IsReleaseCallSent())
                {
                    ret.action = IWF_RA_CONSUME;
                    ret.dir = IWF_RD_DIA;
                    return;
                }

                //NOTE: setting CCTYPE as UPDATE_REQUEST if CallActive is true
                out->setCCRequestType(Ro::CCRequestType(Ro::CCRequestType::UPDATE_REQUEST));
                DLOG_DEBUG("setting CCTYPE as UPDATE_REQUEST");

                usu.setReportingReason(Ro::ReportingReason(Ro::ReportingReason::THRESHOLD));
                //setting returnAction to IWF_RA_FORWARD in case of CCR-U so release is not sent
                ret.action = IWF_RA_FORWARD;

                /* Storing the last Sent CC-Request-Type to be used for validating incoming anser msg from ocs*/
                userData->SetLastSentCCRequestType(Ro::CCRequestType::UPDATE_REQUEST);
            }
            else
            {
                //NOTE: setting CauseCode
                if(userData && userData->IsASRReceived())
                {
                    imsinfo.setCauseCode(Ro::CauseCode(UNSPECIFIED_ERROR));
                }
                else
                {
                    imsinfo.setCauseCode(Ro::CauseCode(NORMAL_END_OF_SESSION));
                }

                //NOTE: setting CCTYPE as TERMINATION_REQUEST if CallActive is false
                out->setCCRequestType(Ro::CCRequestType(Ro::CCRequestType::TERMINATION_REQUEST));
                DLOG_DEBUG("setting CCTYPE as TERMINATION_REQUEST");
                //setting returnAction to IWF_RA_RESPOND_AND_FORWARD in case of CCR-T so release is sent
                ret.action = IWF_RA_RESPOND_AND_FORWARD;

                /* Storing the last Sent CC-Request-Type to be used for 
                 * validating incoming anser msg from ocs*/
                userData->SetLastSentCCRequestType(Ro::CCRequestType::TERMINATION_REQUEST);

                usu.setReportingReason(Ro::ReportingReason(Ro::ReportingReason::FINAL));
                //NOTE: setting Termination cause
                if(userData)
                {
                    out->setTerminationCause(diameter::base::TerminationCause
                            ((diameter::base::TerminationCause::Value)GetTerminationCauseCode(userData)));
                    userData->SetASRReceived(false);
                }
                else
                {
                    out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));
                }
                /* Set the flag in received Dialog type is continue so that
                 * ReleaseCall will be sent upon receiving CCA-T else consume */
                if ( inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE )
                {
                    if(userData) {
                        userData->SetCurrentReceivedTcapContinue(true);
                    }
                }
                else
                {
                    if(userData) {
                        userData->SetCurrentReceivedTcapContinue(false);
                    }
                }
            }

            TimeInformation ti = tdcr.GetTimeInformation();

            if(ti.ChoiceTimeIfNoTariffSwitch())
            {
                Ro::CCTime cctime(ti.GetChoiceTimeIfNoTariffSwitch().GetValue());
                usu.setCCTime(cctime);
            }
            else if(ti.ChoiceTimeIfTariffSwitch())
            {
                TimeIfTariffSwitch tits = ti.GetChoiceTimeIfTariffSwitch();
                Ro::CCTime cctime(tits.GetTimeSinceTariffSwitch().GetValue());
                usu.setCCTime(cctime);
            }
            mscc.addUsedServiceUnit(usu);
        }

        ccrnum = userData->GetCCRequestNumber();
        Ro::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);
    }

    si.setIMSInformation(imsinfo);
    out->setServiceInformation(si);
    out->addMultipleServicesCreditControl(mscc);
}

void CAPToRoHandler::EventReportSMSArg_To_CCRT(IwfFsm* ctxt,
        const EventReportSMSArg *in,
        Ro::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Ro::ServiceInformation si;
    Ro::SMSInformation smsinfo;
    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    out->setCCRequestType(Ro::CCRequestType(Ro::CCRequestType::TERMINATION_REQUEST));
    out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));

    CAPRoTransactionContext* userData = 
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(userData)
    {
        std::string userName = userData->GetUserName();
        if(!userName.empty())
        {
            out->setUserName(diameter::base::UserName(userName));
        }
        ccrnum = userData->GetCCRequestNumber();
        Ro::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        uint32_t sec = ConstructTimeStamp(userData);
        diameter::base::EventTimestamp eventTimestamp(sec);
        out->setEventTimestamp(eventTimestamp);

        if(userData->HasServiceContextId())
        {
            Ro::ServiceContextId* serviceContextId = userData->GetServiceContextId();
            out->setServiceContextId(*serviceContextId);
        }
    }
#if 0
    if(in->GetEventTypeSMS().IsO_smsSubmitted() && in->OptionEventSpecificInformationSMS())
    {
        EventSpecificInformationSMS esisms = in->GetEventSpecificInformationSMS();
        if(esisms.ChoiceO_smsSubmittedSpecificInfo())
        {
            smsinfo.setSMMessageType(Ro::SMMessageType(Ro::SMMessageType::SUBMISSION));
        }
    }

    if(in->GetEventTypeSMS().IsO_smsFailure() && in->OptionEventSpecificInformationSMS())
    {
        EventSpecificInformationSMS esisms = in->GetEventSpecificInformationSMS();
        if(esisms.ChoiceO_smsFailureSpecificInfo())
        {
            EventSpecificInformationSMS::O_smsFailureSpecificInfo osmsinfo = esisms.GetChoiceO_smsFailureSpecificInfo();
            if(osmsinfo.OptionFailureCause())
            {
                //Ro::SMStatus status = IWFUtils::StringToVector("FAILURE");
                smsinfo.setSMStatus(Ro::SMStatus("FAILURE"));      
            }
        }
    }
#endif
    if(in->GetEventTypeSMS().IsO_smsSubmitted())
    {
        smsinfo.setSMMessageType(Ro::SMMessageType(Ro::SMMessageType::SUBMISSION));
    }

    if(in->GetEventTypeSMS().IsO_smsFailure())
    {
        smsinfo.setSMStatus(Ro::SMStatus("FAILURE"));      
    }
    if(m_config.IsSmsNodeFlagSet())
    {
        Ro::SMSNode smsnode((Ro::SMSNode::Value)m_config.SMSNode());
        smsinfo.setSMSNode(smsnode);
    }

    if(m_config.IsRplyPathRqstedFlagSet())
    {
        Ro::ReplyPathRequested rplypathrqstd((Ro::ReplyPathRequested::Value)m_config.ReplyPathRequested());
        smsinfo.setReplyPathRequested(rplypathrqstd);
    }

    bool isIPv4 = false;
    if(!m_config.ClientAddress().empty())
    {
        if(!(IWFUtils::ValidateIPString(m_config.ClientAddress(), isIPv4)))
        {
            if(isIPv4)
            {
                diameter::Address addr1(diameter::Address::IPV4, m_config.ClientAddress());
                Ro::ClientAddress ca(addr1);
                smsinfo.setClientAddress(ca);
                isIPv4 = false;
            }
            else
            {
                diameter::Address addr1(diameter::Address::IPV6, m_config.ClientAddress());
                Ro::ClientAddress ca(addr1);
                smsinfo.setClientAddress(ca);
            }
        }
    }

    if(!m_config.OriginatorSCCPAddr().empty())
    {
        if(!(IWFUtils::ValidateIPString(m_config.OriginatorSCCPAddr(), isIPv4)))
        {
            if(isIPv4)
            {
                diameter::Address addr1(diameter::Address::IPV4, m_config.OriginatorSCCPAddr());
                Ro::OriginatorSCCPAddress osccpaddr(addr1);
                smsinfo.setOriginatorSCCPAddress(osccpaddr);
                isIPv4 = false;
            }
            else
            {
                diameter::Address addr1(diameter::Address::IPV6, m_config.OriginatorSCCPAddr());
                Ro::OriginatorSCCPAddress osccpaddr(addr1);
                smsinfo.setOriginatorSCCPAddress(osccpaddr);
            }
        }
    }

    si.setSMSInformation(smsinfo);
    out->setServiceInformation(si);
}

bool CAPToRoHandler::IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt, bool &isReq)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /* if the Dialog tpe is invoke/continue return true 
     * if it is end return false*/

    if(tcapDlg->GetDialogueType() == TCPPT_TC_BEGIN || tcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE)
    {
        return true;
    }
    else if(tcapDlg->GetDialogueType() == TCPPT_TC_END && 
            (tcapCpt->GetComponentType() == TCPPT_TC_RESULT_L || tcapCpt->GetComponentType() == TCPPT_TC_U_ERROR))
    {
        return true; 
    }
    else
    {
        return false;
    }
}

bool CAPToRoHandler::IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /* if CCR-RequestType is not Terminate send true else false
     * here it is reponse message*/
    const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();
    DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
    if(cmd->isRequest())
    {    
        if(code == DIA_CMD_RA || code == DIA_CMD_AS)
        {    
            return true;
        }    
        else 
        {    
            return false;
        }    
    }    
    else 
    {
        Ro::CreditControlAnswer cca(cmd->getImpl());
        if(cca.getCCRequestType().value() != Ro::CCRequestType::TERMINATION_REQUEST)
        {    
            return true;
        }    
        else 
        {    
            return false;
        }
    }
}

int CAPToRoHandler::FillSDPMediaDescription(const uint8_t *tbcd, int len, std::stringstream &mediaName,
        std::stringstream &mediaDesc)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::FillSDPMediaDescription Entry");
    if ((tbcd == NULL) || (len == 0) || (len < 3))   
        return !ITS_SUCCESS;

    //std::string iLine = "i=A Seminar on the session description protocol";
    //std::string cLine = ",c=IN IP4 ";
    //std::string bLine = ",b=X-YZ:";
    //std::string a1Line = ",a=sendrecv";
    std::string a2Line = "";
    //std::string bandWidth = "";
    bool isMulRate = false;

    int infoTrnsfrCap = (tbcd[0] & 0x1F);
    switch(infoTrnsfrCap)
    {
        case SPEECH:
        case AUDIO_3_1KHZ:
            {
                mediaName << "m=audio 49172 RTP/AVP 0"; 
                break;
            }
        case VIDEO: 
            {
                mediaName << "m=video 51372 RTP/AVP 99"; 
                break;
            }
        default:
            {
                DLOG_ERROR("Unexpected Information transfer capability came");
                return !ITS_SUCCESS;
            }
    }

    int inforate = (tbcd[1] & 0x1F);

    if(inforate == RATE_MULRATEKBPS)
    {
        isMulRate = true;
    }
    /*switch(inforate)
      {
      case RATE_64KBPS:
      {
      bandWidth = "64";
      break;
      }
      case RATE_2X64KBPS:
      {
      bandWidth = "128";
      break;
      }
      case RATE_384KBPS:
      {
      bandWidth = "384";
      break;
      }
      case RATE_1536KBPS:
      {
      bandWidth = "1536";
      break;
      }
      case RATE_1920KBPS:
      {
      bandWidth = "1920";
      break;
      }
      case RATE_MULRATEKBPS:
      {
      bandWidth = "MultiRate";
      isMulRate = true;
      break;
      }
      default:
      {
      DLOG_ERROR("Unexpected Information rate came");
      return !ITS_SUCCESS;
      }
      }*/

    int codec = 0;
    if(isMulRate)
    {
        codec = (tbcd[3] & 0x1F);
    }
    else
    {
        codec = (tbcd[2] & 0x1F);
    }

    switch(codec)
    {
        case G711ULAW:
            {
                a2Line =  "a=rtpmap:0 PCMU/8000";
                break;
            }
        case G711ALAW:
            {
                a2Line = "a=rtpmap:8 PCMA/8000";
                break;
            }
        case G721:
            {
                a2Line = "a=rtpmap:0 G721/8000";
                break;
            }
        case H221H242:
            {
                a2Line = "a=rtpmap:99 H221/90000";
                break;
            }
        case H223H245:
            {
                a2Line = "a=rtpmap:99 H223/90000";
                break;
            }
        default:
            {
                DLOG_ERROR("Unexpected codec came");
                return !ITS_SUCCESS;
            }
    }

    /*mediaDesc << iLine << cLine << itsDiaConfig.GetLocalIpAddr() << "/3868" 
      << bLine << bandWidth << a1Line << a2Line;*/
    mediaDesc << a2Line;
    DLOG_DEBUG("CAPToRoHandler::FillSDPMediaDescription Exit");
    return ITS_SUCCESS;
}

int CAPToRoHandler::TimeStamp(const uint8_t *tbcd, int len, uint32_t &seconds,CAPRoTransactionContext* userData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if ((tbcd == NULL) || (len == 0))   
        return !ITS_SUCCESS;

    int ret = ITS_SUCCESS;

    std::stringstream str1;
    bool IsTimeOk;
    struct TimeAndDate m_time;

    /* time_t and tm structures for incoming time from peer */
    time_t timestruct_2;
    struct tm tmstruct_2;
    char buf [IWF_MAX_TIME_BUF]; /* Buffer to print the time in string format */

    time(&timestruct_2);  /* get current time; same as: now = time(NULL)  */

    tmstruct_2 = *localtime(&timestruct_2); /* filling tm structure with value return by localtime API */

    for(int i = 0; i < len; i++) 
    {
        /* extracting the lower nibble from each octet in loop and storing in stream*/
        int j = IWFUtils::Low4(tbcd[i]);
        str1 << j;
        /* extracting the higher nibble from each octet in loop and storing in stream*/
        int k = IWFUtils::High4(tbcd[i]);
        str1 << k;

        /* filling the tm structure with the incoming timeandtimezone value in format
         * Indicates the time and timezone, relative to GMT. This parameter BCD encoded. 
         * The year digit indicating millenium occupies bits 0-3 of the first octet, and the year 
         * digit indicating century occupies bits 4-7 of the first octet. 
         * The year digit indicating decade occupies bits 0-3 of the second octet, whilst the digit 
         * indicating the year within the decade occupies bits 4-7 of the second octet. 
         * The most significant month digit occupies bits 0-3 of the third octet, and the least 
         * significant month digit occupies bits 4-7 of the third octet. 
         * The most significant day digit occupies bits 0-3 of the fourth octet, and the least 
         * significant day digit occupies bits 4-7 of the fourth octet. 
         * The most significant hours digit occupies bits 0-3 of the fifth octet, and the least 
         * significant hours digit occupies bits 4-7 of the fifth octet. 
         * The most significant minutes digit occupies bits 0-3 of the sixth octet, and the least 
         * significant minutes digit occupies bits 4-7 of the sixth octet. 
         * The most significant seconds digit occupies bits 0-3 of the seventh octet, and the least 
         * significant seconds digit occupies bits 4-7 of the seventh octet.
         * 
         *The timezone information occupies the eigth octet. For the encoding of Timezone refer to */

        /* First Octet is not handled as first two octet forms a year so after 2 Octet we are 
         * filling the tm structure */
        switch(i)
        {
            case OCTET_YR:
                {
                    m_time.year = (atoi(str1.str().c_str()));
                    str1.str( std::string() ); /* clearing the stream after value has been assgined to tm struct */
                    str1.clear();
                    break;
                }
            case OCTET_MT:
                {
                    m_time.month = (atoi(str1.str().c_str()));
                    str1.str( std::string() );
                    str1.clear();
                    break;
                }
            case OCTET_DY:
                {
                    m_time.day = (atoi(str1.str().c_str()));
                    str1.str( std::string() );
                    str1.clear();
                    break;
                }
            case OCTET_HR:
                {
                    m_time.hours = (atoi(str1.str().c_str()));
                    str1.str( std::string() );
                    str1.clear();
                    break;
                }
            case OCTET_MN:
                {
                    m_time.minutes = (atoi(str1.str().c_str()));
                    str1.str( std::string() );
                    str1.clear();
                    break;
                }
            case OCTET_SC:
                {
                    m_time.seconds = (atoi(str1.str().c_str()));
                    str1.str( std::string() );
                    str1.clear();
                    break;
                }
            case OCTET_TZ:
                {
                    m_time.tz[0] = str1.str().c_str()[0];
                    m_time.tz[1] = str1.str().c_str()[1];
                    str1.clear();
                    break;
                }
        }
    }

    IsTimeOk = IWFUtils::CheckDateAndTime(m_time);

    if(IsTimeOk)
    {
        DLOG_DEBUG("Year = %d, Month = %d, Day = %d, Hours = %d, Min = %d,Sec = %d",m_time.year, m_time.month, m_time.day, 
                m_time.hours, m_time.minutes, m_time.seconds);

        tmstruct_2.tm_hour = m_time.hours; tmstruct_2.tm_min = m_time.minutes; tmstruct_2.tm_sec = m_time.seconds;
        tmstruct_2.tm_mon = (m_time.month - 1);  tmstruct_2.tm_mday = m_time.day; tmstruct_2.tm_year = (m_time.year - 1900);

        strftime (buf,100," %Y/%m/%d %H:%M:%S\n",&tmstruct_2);
        DLOG_DEBUG("Time from Peer is %s", buf);

        seconds = ((mktime(&tmstruct_2)) + TIME_FROM_1900_TO_EPOCH);

        /* The Time Zone indicates the difference, expressed in quarters of an hour, 
         * between the local time and GMT. In the first of the two semi octets, the 
         * first bit (bit 3 of the seventh octet of the TP Service Centre Time Stamp 
         * field) represents the algebraic sign of this difference 
         * (0: positive, 1: negative). */

        int quarters = ((((m_time.tz[0]) & 0x07) * 10) + (m_time.tz[1] & 0x0f));

        if(userData != NULL)
        {    
            if((m_time.tz[0] & 0x08) == 0x08)
            {
                userData->SetTimeZoneBit(true);
                seconds -= (quarters * 15 * 60);    
            }
            else
            {
                seconds += (quarters * 15 * 60);    
            }
            userData->SetTimeZoneSeconds((quarters * 15 * 60));
        }
        DLOG_DEBUG("%u seconds \n", seconds);
    }
    else
    {
        DLOG_ERROR("DateAndTime not in Expected range");
        ret = !ITS_SUCCESS;
    }
    return ret;
}

uint32_t CAPToRoHandler::ConstructTimeStamp(CAPRoTransactionContext* userData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    time_t timestruct_2;

    struct tm tmstruct_2;
    uint32_t seconds;
    char buf [100];

    time(&timestruct_2);  /* get current time; same as: now = time(NULL)  */

    tmstruct_2 = *localtime(&timestruct_2);

    strftime (buf,100," %Y/%m/%d %H:%M:%S\n",&tmstruct_2);
    DLOG_DEBUG("Current Time is %s", buf);

    seconds = ((mktime(&tmstruct_2)) + TIME_FROM_1900_TO_EPOCH);
    if(userData->IsTimeZoneBitSet())
    {
        seconds -= (userData->GetTimeZoneSeconds());
    }
    else
    {
        seconds += (userData->GetTimeZoneSeconds());
    }

    DLOG_DEBUG("%u seconds \n", seconds);

    return seconds;
}

unsigned int CAPToRoHandler::GetTerminationCauseCode(CAPRoTransactionContext* userData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    unsigned int causeCode = diameter::base::TerminationCause::DIAMETER_LOGOUT;
    unsigned int resultCode = userData->GetCurrentCCAUResultCode();
    unsigned int msccResultCode = userData->GetCurrentCCAUMsccResultCode(); 

    if((resultCode == DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED) ||
            (resultCode == DIAMETER_ERROR_CREDIT_LIMIT_REACHED) || 
            (resultCode == DIAMETER_ERROR_OTHER_ERROR) || 
            (resultCode == DIAMETER_ERROR_RATING_FAILED) || 
            (resultCode == ITS_DIA_INVALID_AVP_VALUE) || 
            (resultCode == ITS_DIA_MISSING_AVP) || 
            (msccResultCode == DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED) || 
            (msccResultCode == DIAMETER_ERROR_CREDIT_LIMIT_REACHED) || 
            (msccResultCode == DIAMETER_ERROR_OTHER_ERROR) || 
            (msccResultCode == DIAMETER_ERROR_RATING_FAILED) || 
            (msccResultCode == ITS_DIA_INVALID_AVP_VALUE) || 
            (msccResultCode == ITS_DIA_MISSING_AVP) || 
            (userData->IsCurrentCCAMsccGrantedCCTimeZero()) ||
            userData->IsASRReceived() ||
            (resultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE && resultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE) ||
            (resultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE && resultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE))
    {
        causeCode = diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE;
    }

    return causeCode;
}

int CAPToRoHandler::SetConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    IwfCapToRoConfig capRoCfg;
    DLOG_DEBUG("CAPToRoHandler::SetConfig Entry");
    if(translationDataConfig->has_captoroinfo())
    {
        capRoCfg = translationDataConfig->captoroinfo();

        if(capRoCfg.has_caproidpinfo())
        {
            DLOG_DEBUG("Received CAPToRo IDP configurations");

            CapRoIdpConfig capRoIDPCfg = capRoCfg.caproidpinfo();
            if(capRoIDPCfg.has_nodefunctionality())
            {
                m_config.SetNodeFunctionalityFlag(true);
                m_config.SetNodeFunctionality(capRoIDPCfg.nodefunctionality());
            }
            if(capRoIDPCfg.has_orignatingtoi())
            {
                m_config.SetOriginatingIOI(capRoIDPCfg.orignatingtoi());
            }
            if(capRoIDPCfg.has_terminatingtoi())
            {
                m_config.SetTerminatingIOI(capRoIDPCfg.terminatingtoi());
            }
            if(capRoIDPCfg.has_sipmethod())
            {
                m_config.SetSipMethod(capRoIDPCfg.sipmethod());
            }
            if(capRoIDPCfg.has_servicecontextid())
            {
                m_config.SetIDPServiceContextId(capRoIDPCfg.servicecontextid());
            }
            if(capRoIDPCfg.has_causecode())
            {
                m_config.SetCauseCode(capRoIDPCfg.causecode());
            }
            if(capRoIDPCfg.has_mscservicespecfictype())
            {
                m_config.SetIdpMscServiceSpecifictypeFlag(true);
                m_config.SetIDPMscServiceSpecificType(capRoIDPCfg.mscservicespecfictype());
            }
            if(capRoIDPCfg.has_gmscservicespecifictype())
            {
                m_config.SetIdpGmscServiceSpecifictypeFlag(true);
                m_config.SetIDPGmscServiceSpecificType(capRoIDPCfg.gmscservicespecifictype());
            }
            if(capRoIDPCfg.has_cpcservicespecifictype())
            {
                m_config.SetIdpCpcServSpcfcTypeFlag(true);
                m_config.SetIDPCPCServiceSpecificType(capRoIDPCfg.cpcservicespecifictype());
            }
            if(capRoIDPCfg.has_multipleserviceindicator())
            {
                m_config.SetMulServIndicatorFlag(true);
                m_config.SetMultipleServiceIndicator(capRoIDPCfg.multipleserviceindicator());
            }
            int TotalTeleServCfgNum = capRoIDPCfg.extteleinfo_size();
            if(TotalTeleServCfgNum > 0)
            {
                for(int teleNum = 0; teleNum < TotalTeleServCfgNum; teleNum++)
                {
                    ExtTeleServiceConfig extTeleCfg = capRoIDPCfg.extteleinfo(teleNum);
                    if(extTeleCfg.has_extteleservicecode() && extTeleCfg.has_serviceid())
                    {
                        uint32_t teleServCode = extTeleCfg.extteleservicecode();
                        uint32_t servId = extTeleCfg.serviceid();
                        m_config.SetTeleSrvcMapFlag(true);
                        m_config.SetServiceIdFromExtTeleService(teleServCode, servId);
                    }
                }
            }

            int TotalBearServCfgNum = capRoIDPCfg.extbearerinfo_size();
            if(TotalBearServCfgNum > 0)
            {
                for(int bearNum = 0; bearNum < TotalBearServCfgNum; bearNum++)
                {
                    ExtBearerServiceConfig extBearCfg = capRoIDPCfg.extbearerinfo(bearNum);
                    if(extBearCfg.has_extbearerservicecode() && extBearCfg.has_serviceid())
                    {
                        uint32_t bearServCode = extBearCfg.extbearerservicecode();
                        uint32_t servId = extBearCfg.serviceid();
                        m_config.SetBearerSrvcMapFlag(true);
                        m_config.SetServiceIdFromExtBearerService(bearServCode, servId);
                    }
                }
            }
        }
        if(capRoCfg.has_caproidpsmsinfo())
        {
            DLOG_DEBUG("Received CAPToRo IDPSMS configurations");

            CapRoIdpSmsConfig capRoIDPSMSCfg = capRoCfg.caproidpsmsinfo();
            if(capRoIDPSMSCfg.has_smsnode())
            {
                m_config.SetSmsNodeFlag(true);
                m_config.SetSMSNode(capRoIDPSMSCfg.smsnode());
            }
            if(capRoIDPSMSCfg.has_clientaddress())
            {
                m_config.SetClientAddress(capRoIDPSMSCfg.clientaddress());
            }
            if(capRoIDPSMSCfg.has_originatorsccpaddress())
            {
                m_config.SetOriginatorSCCPAddr(capRoIDPSMSCfg.originatorsccpaddress());
            }
            if(capRoIDPSMSCfg.has_replypathrequested())
            {
                m_config.SetRplyPathRqstedFlag(true);
                m_config.SetReplyPathRequested(capRoIDPSMSCfg.replypathrequested());
            }
            if(capRoIDPSMSCfg.has_mscservicespecifictype())
            {
                m_config.SetIdpSmsMscServSpcfcTypeflag(true);
                m_config.SetIDPSMSMscServiceSpecificType(capRoIDPSMSCfg.mscservicespecifictype());
            }
            if(capRoIDPSMSCfg.has_sgsnservicespecifictype())
            {
                m_config.SetIdpSmsSgsnServSpcfcTypeFlag(true);
                m_config.SetIDPSMSsgsnServiceSpecificType(capRoIDPSMSCfg.sgsnservicespecifictype());
            }
            if(capRoIDPSMSCfg.has_servicecontextid())
            {
                m_config.SetIDPSMSServiceContextId(capRoIDPSMSCfg.servicecontextid());
            }
        }
    }
    else
    {
        DLOG_ERROR("CAPToRoHandler::SetConfig: Request does not have CAPToRo configurations");
        retVal = CMAPI_INVALIDPARAMS;
    }

    DLOG_DEBUG("CAPToRoHandler::SetConfig Exit");
    return retVal;
}

int CAPToRoHandler::DeleteConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    IwfCapToRoConfig capRoCfg;
    int numOfBearerService = 0; 
    int numOfTeleService = 0;
    DLOG_DEBUG("CAPToRoHandler::DeleteConfig Entry");
    if(translationDataConfig->has_captoroinfo())
    {
        capRoCfg = translationDataConfig->captoroinfo();

        if(capRoCfg.has_caproidpinfo())
        {
            CapRoIdpConfig capRoIDPCfg = capRoCfg.caproidpinfo();
            DLOG_DEBUG("Received CAPToRo IDP configurations for deletion");
            numOfTeleService = capRoIDPCfg.extteleinfo_size();
            if(numOfTeleService > 0)
            {
                for(int teleNum = 0; teleNum < numOfTeleService; teleNum++)
                {
                    ExtTeleServiceConfig teleCfg = capRoIDPCfg.extteleinfo(teleNum);
                    if(teleCfg.has_extteleservicecode())
                    {
                        uint32_t teleServCode = teleCfg.extteleservicecode();
                        if(!(m_config.RemoveServiceIdFromExtTeleService(teleServCode)))
                        {
                            //Populate Error Details
                        }
                    }
                }
            }

            numOfBearerService = capRoIDPCfg.extbearerinfo_size();
            if(numOfBearerService > 0)
            {
                for(int bearerNum = 0; bearerNum < numOfBearerService; bearerNum++)
                {
                    ExtBearerServiceConfig BearerCfg = capRoIDPCfg.extbearerinfo(bearerNum);
                    if(BearerCfg.has_extbearerservicecode())
                    {
                        uint32_t bearerServCode = BearerCfg.extbearerservicecode();
                        if(!(m_config.RemoveServiceIdFromExtBearerService(bearerServCode)))
                        {
                            //Populate Error Details
                        }
                    }
                }
            }
        }
        else
        {
            DLOG_ERROR("No CAP IDP configurations to be removed");
            retVal = CMAPI_INVALIDPARAMS;
        }
    }
    else
    {
        DLOG_ERROR("CAPToRoHandler::DeleteConfig no CapRo configuration to Delete");
        retVal = CMAPI_SRVERROR;
    }
    DLOG_DEBUG("CAPToRoHandler::DeleteConfig Exit");
    return retVal;
}

void CAPToRoHandler::EncodeMsg(AsnObject* p, Octets** octets)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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

void CAPToRoHandler::ReleaseSession(string &sessString, ITS_UINT sessIdx)
{
    DiaFrame::GetDiaFrame()->ReleaseSession(sessString.c_str());
}

void CAPToRoHandler::CheckEventTypeBCSMAndSetReleaseCause(IwfFsm *ctxt, EventTypeBCSM eventType)
{
    byte cause = NORMAL_CALL_CLEARING;
    CAPRoTransactionContext* userData = reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(eventType.IsOCalledPartyBusy() || eventType.IsTBusy())
    {
        cause = USER_BUSY;
    }
    else if(eventType.IsOAbandon() || eventType.IsTAbandon())
    {
        cause = NORMAL_UNSPECIFIED;
    }
    else if(eventType.IsONoAnswer() || eventType.IsTNoAnswer())
    {
        cause = NO_ANSWER_FROM_USER;
    }
    userData->SetReleaseCause(cause);
}

void CAPToRoHandler::HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                               TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                               DIA_BASE_CMD*& outDiaCmd,
                               TCAP_Component*& cpt,
                               IwfReturnAction& outRetAction)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("CAPToRoHandler::HandleTimeout Entry");
    
    DLOG_DEBUG("CAPToRoHandler::HandleTimeout Exit");
}

void CAPToRoHandler::StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType)
{
}
void CAPToRoHandler::SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("CAPToRoHandler::SetLocalTransId Entry");
    
    DLOG_DEBUG("CAPToRoHandler::SetLocalTransId Exit");

}

int CAPToRoHandler::SetTimerConfig(IwfTimersConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::SetTimerConfig Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("CAPToRoHandler::SetTimerConfig Exit");
    return retVal;
}

int CAPToRoHandler::SetMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::SetMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("CAPToRoHandler::SetMsgSpecCfg Exit");
    return retVal;
}

int CAPToRoHandler::DeleteMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::DeleteMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("CAPToRoHandler::DeleteMsgSpecCfg Exit");
    return retVal;
}

int CAPToRoHandler::LogCDRData(IwfFsm* ctxt,ITS_UINT failureCause)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("CAPToRoHandler::LogCDRData Entry");
    int retVal = ITS_SUCCESS;
    DLOG_DEBUG("CAPToRoHandler::LogCDRData Exit");
    return retVal;
}


int CAPToRoHandler::TerminateSession(IwfFsm *ctxt,
        TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    ITS_UINT ret = ITS_SUCCESS;
    ITS_OCTET invkId = 0;

    DLOG_DEBUG("TransatelCAPToRoHandler::TerminateSession entry");

    CAPRoTransactionContext* userData =
        reinterpret_cast<CAPRoTransactionContext*>(ctxt->GetStoredUserData());


    if ( userData->IsIDPSMSReceived() )
    {
        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if( inTcapDlg != NULL )
        {
            if((inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_BEGIN) 
                    &&  !userData->IsReleaseCallSent() )
            {
                DLOG_DEBUG("Building ReleaseSMS for timeout");
                BuildReleaseSMS(ctxt, NULL, outCpt, userData->GetReleaseCause());
                if ( outCpt != NULL )
                {
                    invkId = ctxt->GetInvkId();
                    outCpt->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                    userData->SetReleaseCallSent(true);
                }
            }
            else
            {
                DLOG_DEBUG("Release already sent or Received TCAP Dialogue is not Continue");
            }
        }
    }
    else
    {
        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if( inTcapDlg != NULL )
        {
            if((inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_BEGIN) 
                    &&  !userData->IsReleaseCallSent() )
            {
                BuildRelease(ctxt, NULL, outCpt, userData->GetReleaseCause());
                if ( outCpt != NULL )
                {
                    UPDATE_SSG_STATS_REL_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    outCpt->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    userData->SetReleaseCallSent(true);
                }
            }
            else
            {

                DLOG_DEBUG("Release already sent or Received TCAP Dialogue is not Continue");
            }
        }
    }
    DLOG_DEBUG("TransatelCAPToRoHandler::TerminateSession exit ");
    return ret;
} 

int CAPToRoHandler::OnUpstrmFinalReqSent(IwfFsm *ctxt)
{
    int retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT CAPToRoHandler::SetFeaturesConfig(IwfFeatureConfig *req)
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT CAPToRoHandler::GetCDRConfig()
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT CAPToRoHandler::GetCDRFailureCause(IwfFsm *iwfFsm)
{
    return SUCCESS_CALL;
}
