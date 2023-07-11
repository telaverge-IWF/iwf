/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
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

#include <time.h>
#include "iwf_cdr.h"
#include "iwf_prot_cap_ro_transatel.h"
#include "iwf.h"
#include "its_dia_config.h"
#include "iwf_prot_defines.h"

static const unsigned IWF_MAX_PATH = 256;

static std::string FormattedTime(time_t tsecs)
{
    struct tm tmNow;
    char timeStr[IWF_MAX_PATH];
    strftime(timeStr, IWF_MAX_PATH, "%Y-%m-%d %H:%M:%S %Z", localtime_r(&tsecs, &tmNow));

    return std::string(timeStr);
}

static std::string FormattedTimeUtc(time_t tsecs)
{
    struct tm *tmNow = gmtime(&tsecs);
    char timeStr[IWF_MAX_PATH];
    strftime(timeStr, IWF_MAX_PATH, "%Y-%m-%d %H:%M:%S %Z", tmNow);

    return std::string(timeStr);
}

IwfFileCDRWriter::IwfFileCDRWriter(const std::string& filePrefix,
                    IwfCallDetailInterpreter* interpreter)
    : m_filePrefix(filePrefix),
      m_recordsCount(0),
      m_outFile(NULL),
      m_interpreter(interpreter)
{
    int cdrFormat = IwfController::Instance().Config().CDRConfig().GetCdrFormat();
    if(cdrFormat == IwfCDRConfig::CDR_FORMAT_CSV)
    {
        char fs = IwfController::Instance().Config().CDRConfig().GetFieldSeparator();
        m_formatter = new IwfCsvFormatter(fs);
    }
    else if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
    {
        m_formatter = new IwfJsonFormatter();
    }
}

IwfFileCDRWriter::~IwfFileCDRWriter()
{
    if (m_outFile)
    {
        delete m_outFile;
    }
    if (m_formatter)
    {
        delete m_formatter;
    }
    if (m_interpreter)
    {
        delete m_interpreter;
    }
}

void IwfFileCDRWriter::CreateFile()
{
    char timeStr[IWF_MAX_PATH];
    char fileName[IWF_MAX_PATH];
    struct tm tmNow;
    time_t now = time(NULL);

    strftime(timeStr, IWF_MAX_PATH, "%Y%m%d%H%M%S", localtime_r(&now, &tmNow));
    snprintf(fileName, IWF_MAX_PATH, "%s%s_%s", IWF_CDR_PATH,
            m_filePrefix.c_str(), timeStr);

    m_outFile = new std::ofstream(fileName);
    m_fileName.assign(fileName);

    // Create the initial array
    int cdrFormat = IwfController::Instance().Config().CDRConfig().GetCdrFormat();
    if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
    {
        (*m_outFile) << "[" << std::endl << std::endl << "]";
    }
    m_recordsCount = 0;
}

int IwfFileCDRWriter::Record(IwfFsm* ctxt, int failureCause)
{
    eAccelero::Mutex::ScopedMutex guard(m_fileGuard);

    if (m_outFile == NULL)
    {
        this->CreateFile();
    }
    if (m_recordsCount >=
        IwfController::Instance().Config().CDRConfig().GetMaxRecsPerFile())
    {
        delete m_outFile;
        this->CreateFile();
    }
    struct stat buf;
    if (stat(m_fileName.c_str(), &buf) != 0)
    {
        delete m_outFile;
        this->CreateFile();
    }

    int cdrFormat = IwfController::Instance().Config().CDRConfig().GetCdrFormat();
    if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
    {
        // Seek two bytes from the end to swallow the "]" at the end
        m_outFile->seekp((long)m_outFile->tellp() - 2);
    }
    if (m_recordsCount != 0)
    {
        if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
        {
                *m_outFile << ",\n";
        }
        else if(cdrFormat == IwfCDRConfig::CDR_FORMAT_CSV)
        {
                *m_outFile << "\n";
        }
    }

    m_formatter->StartRecord(*m_outFile);
    m_interpreter->Record(*m_formatter, ctxt, failureCause);
    m_formatter->StopRecord();

    if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
    {
        *m_outFile << std::endl << "]";
    }

    m_recordsCount++;

    return 0;
}

// Member functions of IwfJsonFormatter class
IwfFormatter& IwfJsonFormatter::StartRecord(std::ostream& os)
{
    m_fieldCount = 0;
    m_indentLevel = 1;
    m_ostream = &os;
    (*m_ostream) << std::setfill(' ') <<
        std::setw(m_indentLevel * 2) << "{" << std::endl;
    m_indentLevel++;
    return *this;
}

IwfFormatter& IwfJsonFormatter::AddField(const std::string& name,
                        const std::string& value)
{
    AddCommaIndent();
    (*m_ostream) << "\"" << name << "\" : " << "\"" << value << "\"";
    return *this;
}

IwfFormatter& IwfJsonFormatter::AddField(const std::string& name, unsigned value){
    AddCommaIndent();
    (*m_ostream) << "\"" << name << "\" : " << value;
    return *this;
}

IwfFormatter& IwfJsonFormatter::AddField(const std::string& name, bool value)
{
    AddCommaIndent();
    (*m_ostream) << "\"" << name << "\" : " << value;
    return *this;
}

IwfFormatter& IwfJsonFormatter::StopRecord()
{
    m_indentLevel--;
    (*m_ostream) << std::endl << std::setfill(' ') << std::setw(m_indentLevel * 2) << "}";
    m_ostream->flush();
    m_ostream = NULL;
    m_fieldCount = 0;
    return *this;
}
// ---------------  End   --------------------

// Member functions of IwfCsvFormatter class
IwfFormatter& IwfCsvFormatter::StartRecord(std::ostream& os)
{
    m_fieldCount = 0;
    m_ostream = &os;
    return *this;
}

IwfFormatter& IwfCsvFormatter::AddField(const std::string& value)
{
    AddFieldSeparator();
    (*m_ostream) << value;
    return *this;
}

IwfFormatter& IwfCsvFormatter::AddField(unsigned value){
    AddFieldSeparator();
    (*m_ostream) << value;
    return *this;
}

IwfFormatter& IwfCsvFormatter::AddField(bool value)
{
    AddFieldSeparator();
    (*m_ostream) << value;
    return *this;
}

IwfFormatter& IwfCsvFormatter::AddFieldAsNull()
{
    AddFieldSeparator();
    return *this;
}

IwfFormatter& IwfCsvFormatter::StopRecord()
{
    m_ostream->flush();
    m_ostream = NULL;
    m_fieldCount = 0;
    return *this;
}
// ---------------  End   --------------------

IwfCallDetailRecorder::IwfCallDetailRecorder(IwfCDRWriter* writer)
    : m_cdrWriter(writer)
{
}

IwfCallDetailRecorder::~IwfCallDetailRecorder()
{
    if (m_cdrWriter)
    {
        delete m_cdrWriter;
    }
}

static const std::string IWF_CDR_LOG_TSTAMP_STR("LogTimeStamp");
static const std::string IWF_CDR_DIA_SESS_ID_STR("SessionId");
static const std::string IWF_CDR_IMSI_STR("IMSI");
static const std::string IWF_CDR_SK_STR("ServiceKey");
static const std::string IWF_CDR_DIA_SVC_CTXT_ID_STR("ServiceContextId");
static const std::string IWF_CDR_CALL_ANS_TSTAMP_STR("CallAnswerTimeStamp");
static const std::string IWF_CDR_TOTAL_GSU_STR("TotalGrantedServiceUnits");
static const std::string IWF_CDR_TOTAL_USU_STR("TotalUsedServiceUnits");
static const std::string IWF_CDR_CCR_TYPE_STR("CCRequestType");
static const std::string IWF_CDR_CCR_NUMBER_STR("CCRequestNumber");
static const std::string IWF_CDR_SCP_ACTION_STR("CAPScpAction");
static const std::string IWF_CDR_CONTROL_MODE_STR("CAPControlMode");
static const std::string IWF_CDR_CLD_PARTY_NUMBER_STR("CalledPartyNumber");
static const std::string IWF_CDR_CLD_PARTY_NATURE_OF_ADDRESS_STR("CalledPartyNumberNature");
static const std::string IWF_CDR_CLNG_PARTY_NUMBER_STR("CallingPartyNumber");
static const std::string IWF_CDR_CLNG_PARTY_NATURE_OF_ADDRESS_STR("CallingPartyNumberNature");
static const std::string IWF_CDR_VLR_NUMBER_STR("VlrNumber");
static const std::string IWF_CDR_MSC_ADDRESS_STR("MscAddress");
static const std::string IWF_CDR_SMSC_ADDRESS_STR("SmscAddress");
static const std::string IWF_CDR_GMSC_ADDRESS_STR("GmscAddress");
static const std::string IWF_CDR_TCAP_LOCAL_TRANSACTION_ID_STR("TcapLocalTransactionID");
static const std::string IWF_CDR_TCAP_REMOTE_TRANSACTION_ID_STR("TcapRemoteTransactionID");
static const std::string IWF_CDR_REDIRECTING_NUMBER_STR("RedirectingNumber");
static const std::string IWF_CDR_REDIRECTION_COUNTER_STR("RedirectionCounter");
static const std::string IWF_CDR_ADDR_PRESENTATION_RESTRICTED_STR("AddressPresentationRestricted");
static const std::string IWF_CDR_BEARER_CAPABALITY_STR("BearerCapabality");
static const std::string IWF_CDR_GSM_FORWARDING_PENDING_STR("GsmForwardingPending");
static const std::string IWF_CDR_CCA_I_RESULT_CODE_STR("CCAInitialResultCode");
static const std::string IWF_CDR_CCA_U_RESULT_CODE_STR("CCAUpdateResultCode");
static const std::string IWF_CDR_CCA_T_RESULT_CODE_STR("CCATerminateResultCode");
static const std::string IWF_CDR_FAILURE_REASON_STR("FailureReason");
static const std::string IWF_CDR_SESSION_START_TIME_STR("SessionStartTime");
static const std::string IWF_CDR_IDPSMS_EVENT_TYPE_STR("IDPSMSEventType");
static const std::string IWF_CDR_IDP_EVENT_TYPE_STR("IDPEventType");
static const std::string IWF_CDR_EVENT_TYPE_SMS_STR("ERBSMSEventType");
static const std::string IWF_CDR_EVENT_TYPE_BCSM_STR("ERBEventType");
static const std::string IWF_CDR_ERB_SPECIFIC_INFO_STR("ErbSpecificInfo");
static const std::string IWF_CDR_ERB_LEG_ID_STR("ErbLegId");
static const std::string IWF_CDR_ERB_ANSWER_TIMESTAMP_STR("ErbAnswerTimeStamp");
static const std::string IWF_CDR_CCR_T_TERMINATION_CAUSE_STR("CCRTerminationCause");
static const std::string IWF_CDR_IS_FOLLOW_ON_STR("IsFollowOnCall");
static const std::string IWF_CDR_IS_SESSION_ACROSS_SWITCHOVER("IsSessionAcrossSwitchover");
static const std::string IWF_CDR_FAILEDOVER_REASON("FailedoverReason");

int IwfCapRoDetailInterpreter::Record(IwfFormatter& formatter,
        IwfFsm* ctxt, int failureCause)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("IwfCapRoDetailInterpreter::Record Enter");
    TransatelCAPRoTransactionContext* caproCtxt =
        static_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    int cdrFormat = IwfController::Instance().Config().CDRConfig().GetCdrFormat();

    if(caproCtxt != NULL)
    {
        // Generate CDR in Json Formate
        if(cdrFormat == IwfCDRConfig::CDR_FORMAT_JSON)
        {
            //DLOG_DEBUG("IwfCapRoDetailInterpreter::Record CDR-Formate : JSON");

            formatter.AddField(IWF_CDR_DIA_SESS_ID_STR, ctxt->GetDiaSessionId());
            formatter.AddField(IWF_CDR_LOG_TSTAMP_STR, FormattedTimeUtc(time(NULL)));
            formatter.AddField(IWF_CDR_IMSI_STR, ctxt->GetImsi());

            if(caproCtxt->IsFollowingOnSet())
            {
                string followOn = "yes";
                formatter.AddField(IWF_CDR_IS_FOLLOW_ON_STR,
                        followOn);
            }

            uint32_t sessionStartTime = caproCtxt->SessionStartTime();
            if (sessionStartTime != 0)
            {
                formatter.AddField(IWF_CDR_SESSION_START_TIME_STR,
                        FormattedTimeUtc(sessionStartTime));
            }

            pbERBData erbData = caproCtxt->GetERBData();

            if (caproCtxt->IsIDPSMSReceived())
            {
                StoredIDPSMSToCCRIData idpSms = caproCtxt->GetStoredIDPSMSToCCRIData();

                formatter.AddField(IWF_CDR_SK_STR,
                        idpSms.cap_service_key());

                std::string cldPartyNumber = idpSms.cap_dialed_digits();
                if ( !cldPartyNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_CLD_PARTY_NUMBER_STR,
                            cldPartyNumber);
                }

                unsigned int cldPartyNumberNature= idpSms.cap_called_ton();
                if (cldPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_CLD_PARTY_NATURE_OF_ADDRESS_STR,
                            cldPartyNumberNature);
                }

                std::string clngPartyNumber = idpSms.cap_cli();
                if ( !clngPartyNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_CLNG_PARTY_NUMBER_STR,
                            clngPartyNumber);
                }

                unsigned int clngPartyNumberNature= idpSms.cap_calling_noa();
                if (clngPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_CLNG_PARTY_NATURE_OF_ADDRESS_STR,
                            clngPartyNumberNature);
                }

                std::string vlrNumber = idpSms.cap_vlr_number();
                if ( !vlrNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_VLR_NUMBER_STR,
                            vlrNumber);
                }

                std::string mscAddr = idpSms.cap_msc_address();
                if ( !mscAddr.empty() )
                {
                    formatter.AddField(IWF_CDR_MSC_ADDRESS_STR,
                            mscAddr);
                }

                std::string smscAddr = idpSms.cap_smsc_address();
                if ( !smscAddr.empty() )
                {
                    formatter.AddField(IWF_CDR_SMSC_ADDRESS_STR,
                            smscAddr);
                }

                unsigned int idpsmsEventType = idpSms.cap_event_type_sms();
                if(idpsmsEventType != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_IDPSMS_EVENT_TYPE_STR,idpsmsEventType);
                }

                unsigned int eventTypeSms = erbData.erbrecvevttype();
                if (eventTypeSms != 0)
                {
                    formatter.AddField(IWF_CDR_EVENT_TYPE_SMS_STR,eventTypeSms);
                }

                std::string erbSpecificInfo = erbData.eventspecinfo();
                if ( !erbSpecificInfo.empty() )
                {
                    formatter.AddField(IWF_CDR_ERB_SPECIFIC_INFO_STR,
                            erbSpecificInfo);
                }

                formatter.AddField(IWF_CDR_TOTAL_GSU_STR,
                        idpSms.m_totalgsuccservice());

                formatter.AddField(IWF_CDR_TOTAL_USU_STR,
                        idpSms.m_totalusuccservice());
            }
            else if (caproCtxt->IsIDPReceived())
            {
                IDPToCCRIData idpData = caproCtxt->GetIDPToCCRIData();

                formatter.AddField(IWF_CDR_SK_STR,
                        idpData.service_key());

                std::string cldPartyNumber = idpData.dialed_digits();
                if ( !cldPartyNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_CLD_PARTY_NUMBER_STR,
                            cldPartyNumber);
                }

                unsigned int cldPartyNumberNature= idpData.called_ton();
                if (cldPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_CLD_PARTY_NATURE_OF_ADDRESS_STR,
                            cldPartyNumberNature);
                }

                std::string clngPartyNumber = idpData.cli();
                if ( !clngPartyNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_CLNG_PARTY_NUMBER_STR,
                            clngPartyNumber);
                }

                unsigned int clngPartyNumberNature= idpData.calling_noa();
                if (clngPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_CLNG_PARTY_NATURE_OF_ADDRESS_STR,
                            clngPartyNumberNature);
                }

                std::string vlrNumber = idpData.vlr_number();
                if ( !vlrNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_VLR_NUMBER_STR,
                            vlrNumber);
                }

                if ( idpData.clir() != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_ADDR_PRESENTATION_RESTRICTED_STR,
                            idpData.clir());
                }

                std::string mscAddr = idpData.msc_address();
                if ( !mscAddr.empty() )
                {
                    formatter.AddField(IWF_CDR_MSC_ADDRESS_STR,
                            mscAddr);
                }

                std::string gmscAddr = idpData.gmsc();
                if ( !gmscAddr.empty() )
                {
                    formatter.AddField(IWF_CDR_GMSC_ADDRESS_STR,
                            gmscAddr);
                }

                std::string redirectNumber= idpData.redirecting_number();
                if ( !redirectNumber.empty() )
                {
                    formatter.AddField(IWF_CDR_REDIRECTING_NUMBER_STR,
                            redirectNumber);
                }

                unsigned int redirectCounter= idpData.redirection_counter();
                if (redirectCounter != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_REDIRECTION_COUNTER_STR,
                            redirectCounter);
                }

                std::string bearerCapability = idpData.bearer_capability_cdr();
                if ( !bearerCapability.empty() )
                {
                    formatter.AddField(IWF_CDR_BEARER_CAPABALITY_STR,
                            bearerCapability);
                }

                unsigned int gsmForwardingPending = idpData.gsm_forwarding_pending();
                if (idpData.version() == TSLConstants::CAPV2_VERSION
                        && gsmForwardingPending != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_GSM_FORWARDING_PENDING_STR,
                            gsmForwardingPending);
                }

                unsigned int idpEventType = idpData.event_type_bcsm();
                if(idpEventType != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(IWF_CDR_IDP_EVENT_TYPE_STR,idpEventType);
                }

                unsigned int eventTypeBcsm = erbData.erbrecvevttype();
                if ( eventTypeBcsm != 0 )
                {
                    formatter.AddField(IWF_CDR_EVENT_TYPE_BCSM_STR,eventTypeBcsm);
                }

                std::string erbSpecificInfo = caproCtxt->GetErbSpecificInfoForCDR();
                //std::string erbSpecificInfo = erbData.GetEvtSpecInfoCdr();
                if ( !erbSpecificInfo.empty() )
                {
                    formatter.AddField(IWF_CDR_ERB_SPECIFIC_INFO_STR,
                            erbSpecificInfo);
                }

                unsigned int erbLegId= erbData.recvlegid();
                if ( erbLegId != 0 )
                {
                    formatter.AddField(IWF_CDR_ERB_LEG_ID_STR,erbLegId);
                }

                ITS_UINT seconds = caproCtxt->ErbAnswerTimeStamp();
                if ( seconds != 0 )
                {
                    formatter.AddField(IWF_CDR_ERB_ANSWER_TIMESTAMP_STR,
                            FormattedTimeUtc(seconds));
                }

                formatter.AddField(IWF_CDR_TOTAL_GSU_STR,
                        caproCtxt->GetCumulativeGSUCCTime());

                formatter.AddField(IWF_CDR_TOTAL_USU_STR,
                        caproCtxt->GetUSUCCTime());
            }

            if (caproCtxt->HasServiceContextId())
            {
                formatter.AddField(IWF_CDR_DIA_SVC_CTXT_ID_STR,
                        caproCtxt->GetServiceContextId());
            }

#if 0
            uint32_t callAnsTs = caproCtxt->GetCallAnsTimeStamp();
            if (callAnsTs != 0)
            {
                formatter.AddField(IWF_CDR_CALL_ANS_TSTAMP_STR, FormattedTimeUtc(callAnsTs));
            }
#endif

            /* decrementing by 1 since in the CapRoCtxt it will store
             * the incremented value to be used for next request */
            formatter.AddField(IWF_CDR_CCR_TYPE_STR,
                    (caproCtxt->GetLastSentCCRequestType()));

            formatter.AddField(IWF_CDR_CCR_NUMBER_STR,
                    (caproCtxt->GetCCRequestNumber()-1));

            unsigned orgScpAction = caproCtxt->GetOriginalSCPAction();
            if (orgScpAction == TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON)
            {
                formatter.AddField(IWF_CDR_SCP_ACTION_STR,
                        orgScpAction);
            }
            else
            {
                unsigned scpAction = caproCtxt->GetSCPAction();
                if ( scpAction != 0 )
                {
                    formatter.AddField(IWF_CDR_SCP_ACTION_STR,
                            scpAction);
                }
            }

            int controlMode = caproCtxt->GetCAPControlMode();
            if ( controlMode != -1 )
            {
                formatter.AddField(IWF_CDR_CONTROL_MODE_STR,
                        static_cast<unsigned int>(controlMode));
            }

            std::string localTransactionId = caproCtxt->GetLocalTransIdForCDR();
            if ( !localTransactionId.empty() )
            {
                formatter.AddField(IWF_CDR_TCAP_LOCAL_TRANSACTION_ID_STR,
                        localTransactionId);
            }

            std::string remoteTransactionId = caproCtxt->GetRemoteTransIdForCDR();
            if ( !remoteTransactionId.empty() )
            {
                formatter.AddField(IWF_CDR_TCAP_REMOTE_TRANSACTION_ID_STR,
                        remoteTransactionId);
            }

            ITS_UINT ccaInitialResultCode = caproCtxt->GetCurrentCCAIResultCode();
            if ( ccaInitialResultCode != 0 )
            {
                formatter.AddField(IWF_CDR_CCA_I_RESULT_CODE_STR,
                        ccaInitialResultCode);
            }

            ITS_UINT ccaUpdateResultCode = caproCtxt->GetCurrentCCAUResultCode();
            if ( ccaUpdateResultCode != 0 )
            {
                formatter.AddField(IWF_CDR_CCA_U_RESULT_CODE_STR,
                        ccaUpdateResultCode);
            }

            ITS_UINT ccaTerminateResultCode = caproCtxt->GetCurrentCCATResultCode();
            if ( ccaTerminateResultCode != 0 )
            {
                formatter.AddField(IWF_CDR_CCA_T_RESULT_CODE_STR,
                        ccaTerminateResultCode);
            }

            ITS_UINT ccrTerminationCause = caproCtxt->GetTerminationCause();
            if( ccrTerminationCause != 0)
            {
                formatter.AddField(IWF_CDR_CCR_T_TERMINATION_CAUSE_STR,
                        ccrTerminationCause);
            }

            if ( failureCause != SUCCESS_CALL )
            {
                std::string reasonStr;
                if (failureCause == TX_TIMEOUT_CCR_I)
                {
                    reasonStr.assign("Tx Timeout for CCR-Initial Request");
                }
                else if (failureCause == TX_TIMEOUT_CCR_U)
                {
                    reasonStr.assign("Tx Timeout for CCR-Update Request");
                }
                else if (failureCause == TX_TIMEOUT_CCR_T)
                {
                    reasonStr.assign("Tx Timeout for CCR-Terminate Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_I)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Initial Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_U)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Update Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_T)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Terminate Request");
                }
                else if (failureCause == FAILED_3XXX_CCA_I)
                {
                    reasonStr.assign("3xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == FAILED_3XXX_CCA_U)
                {
                    reasonStr.assign("3xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_U)
                {
                    reasonStr.assign("4xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_U)
                {
                    reasonStr.assign("5xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_3XXX_CCA_T)
                {
                    reasonStr.assign("3xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_T)
                {
                    reasonStr.assign("4xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_T)
                {
                    reasonStr.assign("5xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_I)
                {
                    reasonStr.assign("4xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_I)
                {
                    reasonStr.assign("5xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == CDR_CODE_PEER_DOWN)
                {
                    reasonStr.assign("Peer Down");
                }

                formatter.AddField(IWF_CDR_FAILURE_REASON_STR, reasonStr);
            }

            if (ctxt->IsSessionAcrossSwitchover())
            {
                std::string value="true";
                formatter.AddField(IWF_CDR_IS_SESSION_ACROSS_SWITCHOVER, value);
            }
            else
            {
                std::string value="false";
                formatter.AddField(IWF_CDR_IS_SESSION_ACROSS_SWITCHOVER, value);
            }

            std::string ccfhreason;
            if (caproCtxt->GetCcfhFailedoverReason() == CDR_TX_TIMEOUT)
            {
                ccfhreason.assign("Tx timer expired");
                formatter.AddField(IWF_CDR_FAILEDOVER_REASON, ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_PEER_DOWN)
            {
                ccfhreason.assign("Unable to deliver message");
                formatter.AddField(IWF_CDR_FAILEDOVER_REASON, ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_UNABLED_TO_DELIVER)
            {
                ccfhreason.assign("3002 error response received");
                formatter.AddField(IWF_CDR_FAILEDOVER_REASON, ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_TOO_BUSY)
            {
                ccfhreason.assign("3004 error response received");
                formatter.AddField(IWF_CDR_FAILEDOVER_REASON,ccfhreason);
            }
        }
        // Generate CDR in CSV formate
        else if(cdrFormat == IwfCDRConfig::CDR_FORMAT_CSV)
        {
            //DLOG_DEBUG("IwfCapRoDetailInterpreter::Record CDR-Formate : CSV");
            if(caproCtxt->IsIDPSMSReceived())
            {
                string msg = "SMS";
                formatter.AddField(msg);
                //DLOG_DEBUG("IwfCapRoDetailInterpreter::Record SMS");
            }
            else
            {
                string msg = "Voice";
                formatter.AddField(msg);
                //DLOG_DEBUG("IwfCapRoDetailInterpreter::Record Voice");
            }
            formatter.AddField(ctxt->GetDiaSessionId());
            formatter.AddField(FormattedTimeUtc(time(NULL)));
            formatter.AddField(ctxt->GetImsi());

            if(caproCtxt->IsFollowingOnSet())
            {
                string followOn = "yes";
                formatter.AddField(followOn);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            uint32_t sessionStartTime = caproCtxt->SessionStartTime();
            if (sessionStartTime != 0)
            {
                formatter.AddField(FormattedTimeUtc(sessionStartTime));
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            pbERBData erbData = caproCtxt->GetERBData();

            if (caproCtxt->IsIDPSMSReceived())
            {
                StoredIDPSMSToCCRIData idpSms = caproCtxt->GetStoredIDPSMSToCCRIData();

                formatter.AddField(idpSms.cap_service_key());

                std::string cldPartyNumber = idpSms.cap_dialed_digits();
                if ( !cldPartyNumber.empty() )
                {
                    formatter.AddField(cldPartyNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int cldPartyNumberNature= idpSms.cap_called_ton();
                if (cldPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(cldPartyNumberNature);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string clngPartyNumber = idpSms.cap_cli();
                if ( !clngPartyNumber.empty() )
                {
                    formatter.AddField(clngPartyNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int clngPartyNumberNature= idpSms.cap_calling_noa();
                if (clngPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(clngPartyNumberNature);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string vlrNumber = idpSms.cap_vlr_number();
                if ( !vlrNumber.empty() )
                {
                    formatter.AddField(vlrNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string mscAddr = idpSms.cap_msc_address();
                if ( !mscAddr.empty() )
                {
                    formatter.AddField(mscAddr);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string smscAddr = idpSms.cap_smsc_address();
                if ( !smscAddr.empty() )
                {
                    formatter.AddField(smscAddr);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int idpsmsEventType = idpSms.cap_event_type_sms();
                if(idpsmsEventType != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(idpsmsEventType);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int eventTypeSms = erbData.erbrecvevttype();
                if (eventTypeSms != 0)
                {
                    formatter.AddField(eventTypeSms);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string erbSpecificInfo = erbData.eventspecinfo();
                if ( !erbSpecificInfo.empty() )
                {
                    formatter.AddField(erbSpecificInfo);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }
                formatter.AddField(idpSms.m_totalgsuccservice());

                formatter.AddField(idpSms.m_totalusuccservice());
            }
            else if (caproCtxt->IsIDPReceived())
            {
                IDPToCCRIData idpData = caproCtxt->GetIDPToCCRIData();

                formatter.AddField(idpData.service_key());

                std::string cldPartyNumber = idpData.dialed_digits();
                if ( !cldPartyNumber.empty() )
                {
                    formatter.AddField(cldPartyNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int cldPartyNumberNature= idpData.called_ton();
                if (cldPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(cldPartyNumberNature);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string clngPartyNumber = idpData.cli();
                if ( !clngPartyNumber.empty() )
                {
                    formatter.AddField(clngPartyNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int clngPartyNumberNature= idpData.calling_noa();
                if (clngPartyNumberNature != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(clngPartyNumberNature);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string vlrNumber = idpData.vlr_number();
                if ( !vlrNumber.empty() )
                {
                    formatter.AddField(vlrNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                if ( idpData.clir() != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(idpData.clir());
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string mscAddr = idpData.msc_address();
                if ( !mscAddr.empty() )
                {
                    formatter.AddField(mscAddr);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string gmscAddr = idpData.gmsc();
                if ( !gmscAddr.empty() )
                {
                    formatter.AddField(gmscAddr);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string redirectNumber= idpData.redirecting_number();
                if ( !redirectNumber.empty() )
                {
                    formatter.AddField(redirectNumber);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int redirectCounter= idpData.redirection_counter();
                if (redirectCounter != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(redirectCounter);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string bearerCapability = idpData.bearer_capability_cdr();
                if ( !bearerCapability.empty() )
                {
                    formatter.AddField(bearerCapability);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int gsmForwardingPending = idpData.gsm_forwarding_pending();
                if (idpData.version() == TSLConstants::CAPV2_VERSION
                        && gsmForwardingPending != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(gsmForwardingPending);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int idpEventType = idpData.event_type_bcsm();
                if(idpEventType != TSLConstants::DEFAULT_INVALID_VAL)
                {
                    formatter.AddField(idpEventType);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int eventTypeBcsm = erbData.erbrecvevttype();
                if ( eventTypeBcsm != 0 )
                {
                    formatter.AddField(eventTypeBcsm);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                std::string erbSpecificInfo = caproCtxt->GetErbSpecificInfoForCDR();
                //std::string erbSpecificInfo = erbData.GetEvtSpecInfoCdr();
                if ( !erbSpecificInfo.empty() )
                {
                    formatter.AddField(erbSpecificInfo);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                unsigned int erbLegId= erbData.recvlegid();
                if ( erbLegId != 0 )
                {
                    formatter.AddField(erbLegId);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                ITS_UINT seconds = caproCtxt->ErbAnswerTimeStamp();
                if ( seconds != 0 )
                {
                    formatter.AddField(FormattedTimeUtc(seconds));
                }
                else
                {
                    formatter.AddFieldAsNull();
                }

                formatter.AddField(caproCtxt->GetCumulativeGSUCCTime());

                formatter.AddField(caproCtxt->GetUSUCCTime());
            }

            if (caproCtxt->HasServiceContextId())
            {
                formatter.AddField(caproCtxt->GetServiceContextId());
            }
            else
            {
                formatter.AddFieldAsNull();
            }
#if 0
            uint32_t callAnsTs = caproCtxt->GetCallAnsTimeStamp();
            if (callAnsTs != 0)
            {
                formatter.AddField(IWF_CDR_CALL_ANS_TSTAMP_STR, FormattedTimeUtc(callAnsTs));
            }
#endif

            /* decrementing by 1 since in the CapRoCtxt it will store
             * the incremented value to be used for next request */
            formatter.AddField(caproCtxt->GetLastSentCCRequestType());

            formatter.AddField(caproCtxt->GetCCRequestNumber()-1);

            unsigned orgScpAction = caproCtxt->GetOriginalSCPAction();
            if (orgScpAction == TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON)
            {
                formatter.AddField(orgScpAction);
            }
            else
            {
                unsigned scpAction = caproCtxt->GetSCPAction();
                if ( scpAction != 0 )
                {
                    formatter.AddField(scpAction);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }
            }

            int controlMode = caproCtxt->GetCAPControlMode();
            if ( controlMode != -1 )
            {
                formatter.AddField(static_cast<unsigned int>(controlMode));
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            std::string localTransactionId = caproCtxt->GetLocalTransIdForCDR();
            if ( !localTransactionId.empty() )
            {
                formatter.AddField(localTransactionId);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            std::string remoteTransactionId = caproCtxt->GetRemoteTransIdForCDR();
            if ( !remoteTransactionId.empty() )
            {
                formatter.AddField(remoteTransactionId);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            ITS_UINT ccaInitialResultCode = caproCtxt->GetCurrentCCAIResultCode();
            if ( ccaInitialResultCode != 0 )
            {
                formatter.AddField(ccaInitialResultCode);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            ITS_UINT ccaUpdateResultCode = caproCtxt->GetCurrentCCAUResultCode();
            if ( ccaUpdateResultCode != 0 )
            {
                formatter.AddField(ccaUpdateResultCode);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            ITS_UINT ccaTerminateResultCode = caproCtxt->GetCurrentCCATResultCode();
            if ( ccaTerminateResultCode != 0 )
            {
                formatter.AddField(ccaTerminateResultCode);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            ITS_UINT ccrTerminationCause = caproCtxt->GetTerminationCause();
            if( ccrTerminationCause != 0)
            {
                formatter.AddField(ccrTerminationCause);
            }
            else
            {
                formatter.AddFieldAsNull();
            }

            if ( failureCause != SUCCESS_CALL )
            {
                std::string reasonStr;
                if (failureCause == TX_TIMEOUT_CCR_I)
                {
                    reasonStr.assign("Tx Timeout for CCR-Initial Request");
                }
                else if (failureCause == TX_TIMEOUT_CCR_U)
                {
                    reasonStr.assign("Tx Timeout for CCR-Update Request");
                }
                else if (failureCause == TX_TIMEOUT_CCR_T)
                {
                    reasonStr.assign("Tx Timeout for CCR-Terminate Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_I)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Initial Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_U)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Update Request");
                }
                else if (failureCause == AUTH_TIMEOUT_CCR_T)
                {
                    reasonStr.assign("AuthSession Timeout for CCR-Terminate Request");
                }
                else if (failureCause == FAILED_3XXX_CCA_I)
                {
                    reasonStr.assign("3xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == FAILED_3XXX_CCA_U)
                {
                    reasonStr.assign("3xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_U)
                {
                    reasonStr.assign("4xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_U)
                {
                    reasonStr.assign("5xx Error response received in CCA-Update Answer");
                }
                else if (failureCause == FAILED_3XXX_CCA_T)
                {
                    reasonStr.assign("3xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_T)
                {
                    reasonStr.assign("4xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_T)
                {
                    reasonStr.assign("5xx Error response received in CCA-Terminate Answer");
                }
                else if (failureCause == FAILED_4XXX_CCA_I)
                {
                    reasonStr.assign("4xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == FAILED_5XXX_CCA_I)
                {
                    reasonStr.assign("5xx Error response received in CCA-Initial Answer");
                }
                else if (failureCause == CDR_CODE_PEER_DOWN)
                {
                    reasonStr.assign("Peer Down");
                }

                if(!reasonStr.empty())
                {
                    formatter.AddField(reasonStr);
                }
                else
                {
                    formatter.AddFieldAsNull();
                }
            }
            else
            {
                formatter.AddFieldAsNull();
            }
            if (ctxt->IsSessionAcrossSwitchover())
            {
                std::string value="true";
                formatter.AddField(value);
            }
            else
            {
                std::string value="false";
                formatter.AddField(value);
            }

            std::string ccfhreason;
            if (caproCtxt->GetCcfhFailedoverReason() == CDR_TX_TIMEOUT)
            {
                ccfhreason.assign("Tx timer expired");
                formatter.AddField(ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_PEER_DOWN)
            {
                ccfhreason.assign("Unable to deliver message");
                formatter.AddField(ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_UNABLED_TO_DELIVER)
            {
                ccfhreason.assign("3002 error response received");
                formatter.AddField(ccfhreason);
            }
            else if (caproCtxt->GetCcfhFailedoverReason() == CDR_TOO_BUSY)
            {
                ccfhreason.assign("3004 error response received");
                formatter.AddField(ccfhreason);
            }
            else
            {
                formatter.AddFieldAsNull();
            }
        }
    }

    return ITS_SUCCESS;
}
