#include "iwf_prot_default_translator.h"
#include "iwf_prot_utils.h"
#include "iwf_transaction_manager.h"
#include "iwf.h"
#include "iwf_prot_map_s6a.h"
#include <dia_frame.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <ssg_trace.h>
#include <ssg_statistics.h>
// MAP Error codes
#include <map_c.h>
// CAP Error codes
#include <cap_c.h>


#include <sstream>

SsgStackStatistics mapStats;
extern ITSDiaConfig itsDiaConfig;

    template <typename T>
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

    template <typename T>
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
}

inline void LogDefDiaMsg(diameter::Command& cmd, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "DefaultHandler RECEIVED S6a message\n";
    }
    else
    {
        str << "DefaultHandler SENDING S6a message\n";
    }

    str << cmd << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

inline void LogDefAsnObj(AsnObject& asn, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if (incoming)
    {
        str << "DefaultHandler RECEIVED MAP message\n";
    }
    else
    {
        str << "DefaultHandler SENDING MAP message\n";
    }

    str << asn << std::endl;
    DLOG_DEBUG("%s", str.str().c_str());
}

void DefaultConfig::Parse(Json::Value& val, IwfConfig& conf)
{
    /*TODO: json file configuration*/
}

    DefaultHandler::DefaultHandler()
: IwfTranslator(DEF_TRANSLATOR_STR)
{
}

DefaultHandler::~DefaultHandler()
{
}

void DefaultHandler::BuildTCAPErrorCpt(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TCAP_Component *&cpt)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::BuildTCAPErrorCpt Entry ");
    Octets *enc2 = 0;
    ITS_OCTET  Err = 0;
    TCAP_Error *terr = new TCAP_Error();
    terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());

    switch(ctxt->GetUpstrmReqProtocol())
    {
        case MAP_GR:
            {
                if(ctxt->GetErrorCode() == MAP_ERR_UNKNOWN_SUBSCRIBER)
                {
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
                }
                else if(ctxt->GetErrorCode() == ITS_ETIMEOUT)
                {
                    Err = MAP_ERR_UNKNOWN_SUBSCRIBER;
                }
                else
                {
                    Err = MAP_ERR_UNEXPECTED_DATA_VALUE;
                }
                break; 
            }
        case CAP_GE:
            {
                if(ctxt->GetErrorCode())
                {
                    Err = ctxt->GetErrorCode();
                    ctxt->SetErrorCode(0);
                }
                else
                {
                    Err = CAP_ERR_UNEXPECTED_DATA_VALUE;
                }
                break; 
            }
        default:
            {
                DLOG_ERROR("Unexpected MAP Protocol Received..!!");
            }
    }

    terr->SetError(Err);
    UPDATE_SSG_STATS_NUM_OF_TCCOMP_ERR_SENT;
    // TODO: More granualr error can be set but usually that is not much looked into.
    cpt = terr;
    DLOG_DEBUG("DefaultHandler::BuildTCAPErrorCpt Exit ");
}

int DefaultHandler::BuildDiaErrorAnswer(IwfFsm *ctxt, int cmdCode, int error, DIA_BASE_CMD **out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::BuildDiaErrorResponse Entry ");
    int rc = ITS_SUCCESS;
    *out = NULL;

    try
    {
        switch(cmdCode)
        {
            case DIA_CMD_UL:
                {
                    s6a::UpdateLocationAnswer *ula = new s6a::UpdateLocationAnswer();
                    ConstructErrorAnswer(error, ula);
                    SetDefaultAVPsInAns(ctxt, ula);
                    LogDefDiaMsg(*ula, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ula);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_AI:
                {
                    s6a::AuthenticationInformationAnswer *aia = new s6a::AuthenticationInformationAnswer();
                    ConstructErrorAnswer(error, aia);
                    SetDefaultAVPsInAns(ctxt, aia);
                    LogDefDiaMsg(*aia, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)aia);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_PU:
                {
                    s6a::PurgeUEAnswer *pua = new s6a::PurgeUEAnswer();
                    ConstructErrorAnswer(error, pua);
                    SetDefaultAVPsInAns(ctxt, pua);
                    LogDefDiaMsg(*pua, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)pua);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_NO:
                {
                    s6a::NotifyAnswer *no = new s6a::NotifyAnswer();
                    ConstructErrorAnswer(error, no);
                    SetDefaultAVPsInAns(ctxt, no);
                    LogDefDiaMsg(*no, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)no);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_DS:
                {
                    s6a::DeleteSubscriberDataAnswer* dsa = new s6a::DeleteSubscriberDataAnswer();
                    ConstructErrorAnswer(error, dsa);
                    SetDefaultAVPsInAns(ctxt, dsa);
                    LogDefDiaMsg(*dsa, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)dsa);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_CL:
                {
                    s6a::CancelLocationAnswer* cla = new s6a::CancelLocationAnswer();
                    ConstructErrorAnswer(error, cla);
                    SetDefaultAVPsInAns(ctxt, cla);
                    LogDefDiaMsg(*cla, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cla);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_ID:
                {
                    s6a::InsertSubscriberDataAnswer* ida = new s6a::InsertSubscriberDataAnswer();
                    ConstructErrorAnswer(error, ida);
                    SetDefaultAVPsInAns(ctxt, ida);
                    LogDefDiaMsg(*ida, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ida);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_RS:
                {
                    s6a::ResetAnswer* ra = new s6a::ResetAnswer();
                    ConstructErrorAnswer(error, ra);
                    SetDefaultAVPsInAns(ctxt, ra);
                    LogDefDiaMsg(*ra, false);
                    *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ra);
                    (*out)->SetDictId(DIA_S6A_REL10_DICTID);
                    break;
                }
            case DIA_CMD_CC:
                {
                    DIA_BASE_CMD *cmd = ctxt->GetCurrRcvdDiaMsg();
                    rc = ConstructCreditControlAnswer(ctxt, cmd, out);
                    break;
                }
            default:
                {
                    break;
                }
        }

        if(!ctxt->GetErrorCode())
        {
            ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_DELIVER);
        }
    }
    catch (diameter::CodecExceptionToApp& e) {
        DLOG_WARNING("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_DEBUG("errorcode is %d for sessionId %s", e.errcode(), e.sessionId());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
        return e.errcode();
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("#### Exception: %s ####", e.what());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        DLOG_ERROR("#### Unknown Exception on BuildDiaResponse ####");
        rc = !ITS_SUCCESS;
    }

    return rc;
}

int DefaultHandler::BuildDiaErrorResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::BuildDiaErrorResponse Entry ");
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;
    const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();

    try
    {
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        if (in->isRequest())
        {
            if (code == DIA_CMD_UL)
            {
                DLOG_DEBUG("Constructing ULR out of diaCmd");
                s6a::UpdateLocationRequest ulr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code ==DIA_CMD_AI)
            {
                DLOG_DEBUG("Constructing ULR out of diaCmd");
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
            else if (code == DIA_CMD_DS)
            {
                DLOG_DEBUG("Constructing DSR out of diaCmd");
                s6a::DeleteSubscriberDataRequest dsdr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_ID)
            {
                DLOG_DEBUG("Constructing DSR out of diaCmd");
                s6a::InsertSubscriberDataRequest isdr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_CL)
            {
                DLOG_DEBUG("Constructing DSR out of diaCmd");
                s6a::CancelLocationRequest clr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_RS)
            {
                DLOG_DEBUG("Constructing RSR out of diaCmd");
                s6a::ResetRequest rr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }
            else if (code == DIA_CMD_CC)
            {
                DLOG_DEBUG("Contructing CCR out of diaCmd");
                Ro::CreditControlRequest ccr(cmd->getImpl());
                ret.action = IWF_RA_ERROR;
            }

        }
        else
        {
            ret.action = IWF_RA_DROP;
        }
    }

    catch (diameter::CodecExceptionToApp& e) {
        DLOG_WARNING("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_DEBUG("errorcode is %d for sessionId %s", e.errcode(), e.sessionId());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
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

int DefaultHandler::BuildTCAPMsg(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}


int DefaultHandler::BuildMultiTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

int DefaultHandler::BuildDiaMsg(IwfFsm *ctxt,
        TCAP_Component *cpt,
        DIA_BASE_CMD *&cmd,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

int DefaultHandler::BuildInterimTCAPMsg(IwfFsm *ctxt, 
        TCAP_Component *in,
        TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

int DefaultHandler::BuildTcapResponse(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

int DefaultHandler::BuildDiaResponse(IwfFsm *ctxt,
        DIA_BASE_CMD *in,
        DIA_BASE_CMD *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    return rc;
}

void DefaultHandler::EncodeMsg(AsnObject* p, Octets** octets)
{
    //cout << endl;
    //cout << "--------------------------------------------------" << endl;
    //cout << "Printing ASN value before encoding..." << endl;

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
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    *octets = tmpOctets;
}

    template <class T>
void DefaultHandler::ConstructErrorAnswer(int error,T *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::BaseGenericCommand *diaBaseGenCmd = (diameter::base::BaseGenericCommand *) out;
    diameter::DiaHeader& hdr = const_cast<diameter::DiaHeader&>(diaBaseGenCmd->getHeader());

    /*Set the E BIT Explicitly*/
    hdr.flags.e = 1; 
    DLOG_DEBUG("ConstructErrorAnswer: E-BIT is : %d", hdr.flags.e);

    if(IwfController::Instance().Config().LocalConfig().IsUseExperimentalResultCode())
    {
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
    // Auth session state -> NO_STATE_MAINTAINED
    out->setAuthSessionState(diameter::base::AuthSessionState(
                diameter::base::AuthSessionState::NO_STATE_MAINTAINED));
}

bool DefaultHandler::IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt, bool &isReq)
{
    return true;
}

bool DefaultHandler::IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq)
{
    return true;
}

int DefaultHandler::SetConfig(IwfTranslationDataConfig *translationDataConfig)
{
   int retVal = ITS_SUCCESS;
   return retVal;
}

int DefaultHandler::DeleteConfig(IwfTranslationDataConfig *translationDataConfig)
{
   int retVal = ITS_SUCCESS;
   return retVal;
}

void DefaultHandler::HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                               TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                               DIA_BASE_CMD*& outDiaCmd,
                               TCAP_Component*& cpt,
                               IwfReturnAction& outRetAction)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("DefaultHandler::HandleTimeout Entry");
    
    DLOG_DEBUG("DefaultHandler::HandleTimeout Exit");
}

void DefaultHandler::StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType)
{
}
void DefaultHandler::SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("DefaultHandler::SetLocalTransId Entry");
    
    DLOG_DEBUG("DefaultHandler::SetLocalTransId Exit");

}

int DefaultHandler::SetTimerConfig(IwfTimersConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::SetTimerConfig Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("DefaultHandler::SetTimerConfig Exit");
    return retVal;
}

int DefaultHandler::SetMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::SetMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("DefaultHandler::SetMsgSpecCfg Exit");
    return retVal;
}

int DefaultHandler::DeleteMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::DeleteMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("DefaultHandler::DeleteMsgSpecCfg Exit");
    return retVal;
}


int DefaultHandler::LogCDRData(IwfFsm* ctxt, ITS_UINT failureCause)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("DefaultHandler::LogCDRData Entry");
    int retVal = ITS_SUCCESS;
    DLOG_DEBUG("DefaultHandler::LogCDRData Exit");
    return retVal;
}

int DefaultHandler::TerminateSession(IwfFsm *ctxt,
        TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd)
{
    ITS_UINT ret = ITS_SUCCESS;
    return ret;
} 

int DefaultHandler::OnUpstrmFinalReqSent(IwfFsm *ctxt)
{
    int retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT DefaultHandler::SetFeaturesConfig(IwfFeatureConfig *req)
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT DefaultHandler::GetCDRConfig()
{
    ITS_UINT retVal = ITS_SUCCESS;
    return retVal;
}

ITS_UINT DefaultHandler::GetCDRFailureCause(IwfFsm *iwfFsm)
{
    return SUCCESS_CALL;
}

ITS_UINT DefaultHandler::ConstructCreditControlAnswer(IwfFsm *ctxt, DIA_BASE_CMD *in, DIA_BASE_CMD **&out)
{
    int ret = ITS_SUCCESS;
    if (in != NULL)
    {
        diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();
        Ro::CreditControlRequest ccr(cmd->getImpl());
        Ro::CreditControlAnswer* cca = new Ro::CreditControlAnswer(true,false);

        string destRealm(ccr.getOriginRealm().value());
        string destHost(ccr.getOriginHost().value());

        cca->setAuthApplicationId(ccr.getAuthApplicationId());

        cca->setCCRequestType(ccr.getCCRequestType());

        cca->setCCRequestNumber(ccr.getCCRequestNumber());

        diameter::base::ResultCode res(ITS_DIA_UNABLE_TO_COMPLY);
        cca->setResultCode(res);
        SetDefaultAVPsInAns(ctxt, cca);
        LogDefDiaMsg(*cca, false);
        *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cca);
    }
    else
    {
        ret = !ITS_SUCCESS;
    }

    return ret;
}
