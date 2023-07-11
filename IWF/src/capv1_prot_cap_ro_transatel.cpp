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


#include "iwf.h"
#include "iwf_prot_cap_ro_transatel.h"
#include "iwf_prot_utils.h"
#include "iwf_prot_defines.h"
#include <ssg_statistics.h>




#include <sstream>
#include <bitset>

using namespace cap_v1;
using namespace TransCustomAvp;


SsgStackStatistics mapStats;


/*CCR Number which will be used for CCR-I/U/T */
//extern int ccrnum;

void CAPRoTSLConfig::GetMOCAPV2_EventList(std::vector<TCAPV2Event_ArmData>& evntLst, std::string& rrbRuleId) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    evntLst.clear();

    RRBRuleIdVsCallScenario::iterator itr = m_RRBRuleLst.find(rrbRuleId);
    if(itr != m_RRBRuleLst.end())
    {
        TCAPV2Event_ArmData v2Evt;
        for(unsigned int i = 0; i < itr->second.size(); i++)
        {
            CallScenario_t callscen = itr->second[i];
            for(unsigned j =0 ; j < callscen.MO_V2.size(); j++)
            {
                v2Evt.eventType = callscen.MO_V2[j].eventType;
                v2Evt.legIdMonMode = callscen.MO_V2[j].legIdMonMode;
                evntLst.push_back(v2Evt);
                //DLOG_DEBUG("CAPRoTSLConfig::GetMOCAPV2_EventList MO_V2 EventType : %ld added.",v2Evt.eventType.GetValue());
            }
        }
        
    }
    /*else
    {
        DLOG_INFO("CAPRoTSLConfig::GetMOCAPV2_EventList RRBRuleId : %s not found in RRBRuleIdVsCallScenarioMap.",rrbRuleId.c_str());

    }*/

}
void CAPRoTSLConfig::GetMTCAPV2_EventList(std::vector<TCAPV2Event_ArmData>& evntLst, std::string& rrbRuleId) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    evntLst.clear();
    
    RRBRuleIdVsCallScenario::iterator itr = m_RRBRuleLst.find(rrbRuleId);
    if(itr != m_RRBRuleLst.end())
    {
        TCAPV2Event_ArmData v2Evt;
        for(unsigned int i = 0; i < itr->second.size(); i++)
        {
            CallScenario_t callscen = itr->second[i];
            for(unsigned j =0 ; j < callscen.MT_V2.size(); j++)
            {
                v2Evt.eventType = callscen.MT_V2[j].eventType;
                v2Evt.legIdMonMode = callscen.MT_V2[j].legIdMonMode;
                evntLst.push_back(v2Evt);
                //DLOG_DEBUG("CAPRoTSLConfig::GetMTCAPV2_EventList MT_V2 EventType : %ld added.",v2Evt.eventType.GetValue());
            }
        }
        
    }
    /*else
    {
        DLOG_INFO("CAPRoTSLConfig::GetMTCAPV2_EventList RRBRuleId : %s not found in RRBRuleIdVsCallScenarioMap.",rrbRuleId.c_str());

    }*/
    
}
void CAPRoTSLConfig::GetMOCAPV1_EventList(std::vector<TCAPV1Event_ArmData>& evntLst, std::string& rrbRuleId) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    evntLst.clear();
//    evntLst.push_back(m_capv1MOAnsEvnt);
//    evntLst.push_back(m_capv1MODisconEvnt);

    RRBRuleIdVsCallScenario::iterator itr = m_RRBRuleLst.find(rrbRuleId);
    if(itr != m_RRBRuleLst.end())
    {
        TCAPV1Event_ArmData v1Evt;
        for(unsigned int i = 0; i < itr->second.size(); i++)
        {
            CallScenario_t callscen = itr->second[i];
            for(unsigned j =0 ; j < callscen.MO_V1.size(); j++)
            {
                //v1Evt = callscen.MO_V1[j];
                v1Evt.eventType = callscen.MO_V1[j].eventType;
                v1Evt.legIdMonMode = callscen.MO_V1[j].legIdMonMode;
                evntLst.push_back(v1Evt);
                //DLOG_DEBUG("CAPRoTSLConfig::GetMOCAPV1_EventList MO_V1 EventType : %ld added.",v1Evt.eventType.GetValue());
            }
        }
        
    }
    /*else
    {
        DLOG_INFO("CAPRoTSLConfig::GetMOCAPV1_EventList RRBRuleId : %s not found in RRBRuleIdVsCallScenarioMap.",rrbRuleId.c_str());
    
    }*/
        
}
void CAPRoTSLConfig::GetMTCAPV1_EventList(std::vector<TCAPV1Event_ArmData>& evntLst, std::string& rrbRuleId) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    evntLst.clear();
    
    RRBRuleIdVsCallScenario::iterator itr = m_RRBRuleLst.find(rrbRuleId);
    if(itr != m_RRBRuleLst.end())
    {
        TCAPV1Event_ArmData v1Evt;
        for(unsigned int i = 0; i < itr->second.size(); i++)
        {
            CallScenario_t callscen = itr->second[i];
            for(unsigned j =0 ; j < callscen.MT_V1.size(); j++)
            {
                v1Evt.eventType = callscen.MT_V1[j].eventType;
                v1Evt.legIdMonMode = callscen.MT_V1[j].legIdMonMode;
                evntLst.push_back(v1Evt);
                //DLOG_DEBUG("CAPRoTSLConfig::GetMTCAPV1_EventList MT_V1 EventType : %ld added.",v1Evt.eventType.GetValue());
            }
        }
        
    }
    /*else
    {
        DLOG_INFO("CAPRoTSLConfig::GetMTCAPV1_EventList RRBRuleId : %s not found in RRBRuleIdVsCallScenarioMap.",rrbRuleId.c_str());
    
    }*/
    
}

void CAPRoTSLConfig::GetMOSMSCAPV3_EventList(std::vector<TCAPV3SMSEvent_ArmData>& evntLst, std::string& rrbRuleId) 
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    evntLst.clear();

    RRBRuleIdVsCallScenario::iterator itr = m_RRBRuleLst.find(rrbRuleId);
    if(itr != m_RRBRuleLst.end())
    {
        TCAPV3SMSEvent_ArmData v3SMSEvt;
        for(unsigned int i = 0; i < itr->second.size(); i++)
        {
            CallScenario_t callscen = itr->second[i];
            for(unsigned j =0 ; j < callscen.SMS_V3.size(); j++)
            {
                v3SMSEvt.smsEvntType = callscen.SMS_V3[j].smsEvntType;
                v3SMSEvt.monitorMode = callscen.SMS_V3[j].monitorMode;
                    
                evntLst.push_back(v3SMSEvt);
                //DLOG_DEBUG("CAPRoTSLConfig::GetMOSMSCAPV3_EventList SMS_V3 EventType : %ld added.",v3SMSEvt.smsEvntType.GetValue());
            }
        }
        
    }
    /*else
    {
        DLOG_INFO("CAPRoTSLConfig::GetMOSMSCAPV3_EventList RRBRuleId : %s not found in RRBRuleIdVsCallScenarioMap.",rrbRuleId.c_str());
    
    }*/
        
}


void TransatelCAPToRoHandler::RetrieveIDPToCCRIData(TransCustomAvp::CAPInformation& capInfo, IDPToCCRIData ccriAvpVal)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::RetrieveIDPToCCRIData Entry");

    TransCustomAvp::CAPServiceKey skval(ccriAvpVal.service_key());
    capInfo.setCAPServiceKey(skval);

    TransCustomAvp::CAPDialedDigits dialedDigits(ccriAvpVal.dialed_digits());
    if(ccriAvpVal.has_dialed_digits())
        capInfo.setCAPDialedDigits(dialedDigits);

    if(ccriAvpVal.called_ton() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCalledTON calledton(ccriAvpVal.called_ton());
        capInfo.setCAPCalledTON(calledton);
    }

    TransCustomAvp::CAPCLI capcli(ccriAvpVal.cli());
    if(ccriAvpVal.has_cli())   
        capInfo.setCAPCLI(capcli);

    if(ccriAvpVal.calling_category() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCallingCategory clgParyCategory(ccriAvpVal.calling_category());
        capInfo.setCAPCallingCategory(clgParyCategory);
    }

    TransCustomAvp::CAPLocationNumber caplocnumber(ccriAvpVal.location_number());
    if(ccriAvpVal.has_location_number())
        capInfo.setCAPLocationNumber(caplocnumber);

    TransCustomAvp::CAPRedirectingNumber redirectingNo(ccriAvpVal.redirecting_number());
    if(ccriAvpVal.has_redirecting_number())
        capInfo.setCAPRedirectingNumber(redirectingNo);


    if(ccriAvpVal.redirecting_indicator() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPRedirectingIndicator redirectInd(ccriAvpVal.redirecting_indicator());
        capInfo.setCAPRedirectingIndicator(redirectInd);
    }

    if(ccriAvpVal.original_redirecting_reason() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPOriginalRedirectingReason orgredirectReason(ccriAvpVal.original_redirecting_reason());
        capInfo.setCAPOriginalRedirectingReason(orgredirectReason);
    }

    if(ccriAvpVal.redirection_counter() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPRedirectionCounter redirectCnt(ccriAvpVal.redirection_counter());
        capInfo.setCAPRedirectionCounter(redirectCnt);
    }

    if(ccriAvpVal.redirecting_reason() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPRedirectingReason redirectreason(ccriAvpVal.redirecting_reason());
        capInfo.setCAPRedirectingReason(redirectreason);
    }

    TransCustomAvp::CAPIMSI imsi(ccriAvpVal.imsi());
    if(ccriAvpVal.has_imsi())
        capInfo.setCAPIMSI(imsi);

    TransCustomAvp::CAPVLRNumber vlrnumber(ccriAvpVal.vlr_number());
    if(ccriAvpVal.has_vlr_number())
        capInfo.setCAPVLRNumber(vlrnumber);

    TransCustomAvp::CAPCallReference callrefnumber(ccriAvpVal.call_reference());
    if(ccriAvpVal.has_call_reference())
        capInfo.setCAPCallReference(callrefnumber);

    TransCustomAvp::CAPMSCAddress mscaddr(ccriAvpVal.msc_address());    
    if(ccriAvpVal.has_msc_address())
        capInfo.setCAPMSCAddress(mscaddr);

    if(ccriAvpVal.called_npi() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCalledNPI callednpi(ccriAvpVal.called_npi());
        capInfo.setCAPCalledNPI(callednpi);
    }

    if(ccriAvpVal.calling_noa() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCLINOA callingnoa(ccriAvpVal.calling_noa());
        capInfo.setCAPCLINOA(callingnoa);        
    }

    if(ccriAvpVal.cli_npi() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCLINPI clinpi(ccriAvpVal.cli_npi());
        capInfo.setCAPCLINPI(clinpi);        
    }

    if(ccriAvpVal.clir() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCLIR clir(ccriAvpVal.clir());
        capInfo.setCAPCLIR(clir);        
    }

    TransCustomAvp::CAPExtBasicServiceCode extBasicSrvCode(ccriAvpVal.ext_basic_service_code());    
    if(ccriAvpVal.has_ext_basic_service_code())
        capInfo.setCAPExtBasicServiceCode(extBasicSrvCode);        

    if(ccriAvpVal.version() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPVersion capversion(ccriAvpVal.version());
        capInfo.setCAPVersion(capversion);
    }

    TransCustomAvp::CAPSCCPCallingGT sccpClgGT(ccriAvpVal.sccp_callinggt());    
    if(ccriAvpVal.has_sccp_callinggt())
        capInfo.setCAPSCCPCallingGT(sccpClgGT);        

    TransCustomAvp::CAPSCCPCalledGT sccpCldGT(ccriAvpVal.sccp_calledgt());    
    if(ccriAvpVal.has_sccp_calledgt())
        capInfo.setCAPSCCPCalledGT(sccpCldGT);        

    TransCustomAvp::CAPTCAPRemoteTransactionId tcapRemoteId(ccriAvpVal.tcap_remote_transaction_id());    
    if(ccriAvpVal.has_tcap_remote_transaction_id())
        capInfo.setCAPTCAPRemoteTransactionId(tcapRemoteId);        

    TransCustomAvp::CAPTCAPLocalTransactionId tcapLocalId(ccriAvpVal.tcap_local_transaction_id());    
    if(ccriAvpVal.has_tcap_local_transaction_id())
        capInfo.setCAPTCAPLocalTransactionId(tcapLocalId);        

    TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLAI(ccriAvpVal.cellid_areaid_lai());    
    if(ccriAvpVal.has_cellid_areaid_lai())
        capInfo.setCAPCellIDAreaIDLAI(cellIdAreaIdLAI);        

    if(ccriAvpVal.event_type_bcsm() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPEventTypeBCSM evntTypeBCSM(ccriAvpVal.event_type_bcsm());
        capInfo.setCAPEventTypeBCSM(evntTypeBCSM);    
    }

    TransCustomAvp::CAPBearerCapability capbearerCap(ccriAvpVal.bearer_capability());
    if(ccriAvpVal.has_bearer_capability())
        capInfo.setCAPBearerCapability(capbearerCap);

    TransCustomAvp::CAPGMSCAddress gmsc(ccriAvpVal.gmsc());
    if(ccriAvpVal.has_gmsc())
        capInfo.setCAPGMSCAddress(gmsc);

    if(ccriAvpVal.gsm_forwarding_pending() == CAP_GSM_FORWARDING_PENDING_PRESENT)
    {
        TransCustomAvp::CAPGSMForwardingPending capGSMForwardingInfo(CAP_GSM_FORWARDING_PENDING_PRESENT);
        capInfo.setCAPGSMForwardingPending(capGSMForwardingInfo);
    }

    /*Set TCAPErrorCause */
    if(TSLConstants::DEFAULT_TCAP_ERROR_CAUSE_VAL != ccriAvpVal.tcap_error_cause())
    {
        TransCustomAvp::CAPTCAPErrorCause errCause(ccriAvpVal.tcap_error_cause());
        capInfo.setCAPTCAPErrorCause(errCause);
    }

    if(ccriAvpVal.capisfollowingon())
    {
        TransCustomAvp::CAPIsFollowingOn capFollowOn((TransCustomAvp::CAPIsFollowingOn::Value)true);
        capInfo.setCAPIsFollowingOn(capFollowOn);
    }

    //DLOG_DEBUG("TransatelCAPToRoHandler::RetrieveIDPToCCRIData Exit");
}

/*Func Descrip : It extracts the CAP-Control-Mode value in the recevied CCA-I msg, for voice calls 
  and populates the out parameter with recv CAP-Control-Mode AVP value.
  By default CAP-Control-Mode is LOCAL_CONTROL.
  Also populates the same value in userData context.
  Retunr values : Failure, if invalid value is set in CAP-Control-Mode AVP else Success shall be returned. 

*/

int TransatelCAPToRoHandler::ExtractCtrlModeData(Ro_TSL::CreditControlAnswer* cca, 
        TransatelCAPRoTransactionContext* userData,
        TransCustomAvp::CAPControlMode::Value& ctrlModeVal)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("ExtractCtrlModeData:: Entry");
    int ret = ITS_SUCCESS;

    if(cca->containsServiceControl())
    {
        TransCustomAvp::ServiceControl servCtrl = cca->getServiceControl();
        if(servCtrl.containsCAPInformation())
        {
            TransCustomAvp::CAPInformation capInfo = servCtrl.getCAPInformation();
            if(capInfo.containsCAPControlMode())
            {
                int capcontrolmode = capInfo.getCAPControlMode().value();
                //DLOG_DEBUG("ExtractCtrlModeData: recieved CapControlMode %d",capcontrolmode);
                userData->SetCAPControlMode(capcontrolmode);
                switch(capcontrolmode)
                {
                    case TransCustomAvp::CAPControlMode::NO_CONTROL :
                        {
                            //DLOG_INFO("ExtractCtrlModeData: recieved CapControlMode as NO_CONTROL.");
                            ctrlModeVal = TransCustomAvp::CAPControlMode::NO_CONTROL;
                            userData->SetTerminationCause(DIA_TERM_CAUSE_NOT_CONTROLLED_CALL);
                            break;
                        }
                    case TransCustomAvp::CAPControlMode::LOCAL_CONTROL  :
                        {
                            //DLOG_DEBUG("ExtractCtrlModeData: recieved CapControlMode as LOCAL_CONTROL.");
                            ctrlModeVal = TransCustomAvp::CAPControlMode::LOCAL_CONTROL;
                            userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
                            break;
                        }
                    case TransCustomAvp::CAPControlMode::REMOTE_CONTROL :
                        {
                            //DLOG_DEBUG("ExtractCtrlModeData: recieved CapControlMode as REMOTE_CONTROL.");
                            ctrlModeVal = TransCustomAvp::CAPControlMode::REMOTE_CONTROL;                       
                            break;
                        }
                    default:
                        {
                            //DLOG_ERROR("ExtractCtrlModeData: Invalid value set in recieved CapControlMode: %d.",capcontrolmode);
                            userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_CONTROL_MODE);
                            userData->SetCAPControlMode(TSLConstants::INVALID_CONTROL_MODE);
                            ret = !ITS_SUCCESS;
                            break;
                        }
                }

            }
            else
            {
                //DLOG_INFO("CAP-Control-Mode is not set and by default set as LOCAL_CONTROL");
                userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
                ctrlModeVal = TransCustomAvp::CAPControlMode::LOCAL_CONTROL;
            }
        }
        else
        {
            //DLOG_INFO("CAP-Information is not set and by default CAP-Control-Mode set to LOCAL_CONTROL");
            userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
            ctrlModeVal = TransCustomAvp::CAPControlMode::LOCAL_CONTROL;
        }
    }
    else
    {
        //DLOG_INFO("Service-Control is not set and by default CAP-Control-Mode set to LOCAL_CONTROL");
        userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
        ctrlModeVal = TransCustomAvp::CAPControlMode::LOCAL_CONTROL;
    }

    //DLOG_INFO("ExtractCtrlModeData:: Exit");
    return ret;
}

/*Func Descrip : It extracts the SCPAction value in the recevied CCA msg, for voice calls 
  and populates the out parameter with the valid range of values for SCPAction
  and populates the same in userData context.
  Retunr values : Success if SCPAction AVP is present & populated valid value in out param scpActionVal                  
  Failure, if either SCPAction AVP is absent or do not contain valid value.

*/

int TransatelCAPToRoHandler::ExtractScpActionData(Ro_TSL::CreditControlAnswer* cca,
        TransatelCAPRoTransactionContext* userData,
        TransCustomAvp::SCPAction::Value& scpActionVal)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("ExtractScpActionData:: Entry");
    int ret = ITS_SUCCESS;

    if(cca->containsServiceControl())
    {
        TransCustomAvp::ServiceControl servCtrl = cca->getServiceControl();
        if(servCtrl.containsSCPAction())
        {
            int scpAction = servCtrl.getSCPAction().value();
            //DLOG_DEBUG("ExtractScpActionData:: Recv ScpAction : %d.",scpAction);
            userData->SetSCPAction(scpAction);
            if(!userData->IsFollowingOnSet())
            {
                userData->SetOriginalSCPAction(scpAction);
            }
            switch(scpAction)
            {
                case TransCustomAvp::SCPAction::CONTINUE :
                    scpActionVal = TransCustomAvp::SCPAction::CONTINUE;
                    break;
                case TransCustomAvp::SCPAction::REJECT   :
                    {
                        scpActionVal = TransCustomAvp::SCPAction::REJECT;
                        //DLOG_ERROR("ExtractScpActionData:: Reject ScpAction Received: %d.",scpAction);
                        userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_BAD_ANSWER);
                        ret = !ITS_SUCCESS;
                        break;
                    }
                case TransCustomAvp::SCPAction::CONNECT  :
                    scpActionVal = TransCustomAvp::SCPAction::CONNECT;
                    break;                
                case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON :
                    scpActionVal = TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON;
                    break;                
                case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT     :                
                    scpActionVal = TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT;
                    break;
                case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE    :                
                    scpActionVal = TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE;
                    break;
                default : 
                    {
                        //DLOG_ERROR("ExtractScpActionData:: Invalid ScpAction value: %d.",scpAction);
                        userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
                        userData->SetSCPAction(0);
                        //Note: Release Cause should be default value if SCP-Action is Unknown
                        userData->SetReleaseCause(m_config.ReleaseCallCauseCode());
                        ret = !ITS_SUCCESS;
                        break;
                    }
            }
        }
        else
        {
            //DLOG_ERROR("SCP-Action AVP not present in Service-Control");
            userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
            userData->SetSCPAction(0);
            //Note: Release Cause should be default value if SCP-Action is not there
            userData->SetReleaseCause(m_config.ReleaseCallCauseCode());
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        //DLOG_ERROR("Service-Control AVP not present in CreditControlAnswer");
        userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
        userData->SetSCPAction(0);
        //Note: Release Cause should be default value if service control avp is not received
        userData->SetReleaseCause(m_config.ReleaseCallCauseCode());

        ret = !ITS_SUCCESS;
    }

    //DLOG_INFO("ExtractScpActionData:: Exit");

    return ret;
}

int TransatelCAPToRoHandler::CheckAndGetGSUCCTime(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer& cca)
{


    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("CheckAndGetGSUCCTime:: Entry");
    int ret = ITS_SUCCESS;
    //DLOG_INFO("CheckAndGetGSUCCTime:: Exit");

    return ret;

}
/* Func Description : Based on recv SCPAction & Control-Mode decision which combination of CAMEL msgs have to be 
   constructed is derived & appropriately TcapCmptList is built.
   Return Failure : If building of cmptList failed.
   Return Success : If building of cmptList succeded.                    
   */
int TransatelCAPToRoHandler::DeduceAndConstructCAMELMsg(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer& cca,
        TcapCptList *&cmptList)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("DeduceAndConstructCAMELMsg:: Entry");
    int ret = ITS_SUCCESS;


    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    switch(userData->GetSCPAction())
    {
        case SCPAction::FOLLOW_ON_CONTINUE:
        case SCPAction::CONTINUE:
            {
                switch(userData->GetCAPControlMode())
                {
                    case CAPControlMode::LOCAL_CONTROL:
                        {
                            ret = ConstructRRB_CONT(ctxt, cca, cmptList);
                            userData->SetFirstERBReceived(false);
                        }
                        break;
                    case CAPControlMode::REMOTE_CONTROL:
                        {
                            if(cap::CAPV2_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
                                ret = ConstructRRB_CONT_ACh(ctxt,cca,cmptList);
                            else if(cap::CAPV1_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
                            {
                                DLOG_ERROR("DeduceAndConstructCAMELMsg:: Recv IDP in AC : CAPV1_gsmSSF_to_gsmSCF_AC, SCP-Action : %s, CAPControMode : %s",
                                        (GetStrSCPAction(userData->GetSCPAction())).c_str(),
                                        (GetStrCAPControlMode(userData->GetCAPControlMode())).c_str());
                                DLOG_INFO("DeduceAndConstructCAMELMsg:: Send ReleaseCall and CCR-T.");
                                ctxt->SetErrorCode(TSLConstants::INVALID_CONTROL_MODE_CAPV1);
                                ret = !ITS_SUCCESS;
                            }               
                            userData->SetFirstERBReceived(false);                                            
                        }
                        break;
                    case CAPControlMode::NO_CONTROL:
                        {
                            //ret = ConstructCONT_TCEnd(ctxt,cca,cmptList);
                            ctxt->SetIsTCAPEnd(true);
                        }
                        break;
                    default:
                        {
                            DLOG_ERROR("DeduceAndConstructCAMELMsg:: CapControlMode Invalid value: %d.",userData->GetCAPControlMode());
                            ret = !ITS_SUCCESS;
                        }

                }

            }
            break;

        case SCPAction::FOLLOW_ON_CONNECT:
        case SCPAction::CONNECT:
            {
                switch(userData->GetCAPControlMode())
                {
                    case CAPControlMode::LOCAL_CONTROL:
                        {
                            ret = ConstructRRB_CON(ctxt, &cca, cmptList);
                            userData->SetFirstERBReceived(false);                                            
                        }
                        break;
                    case CAPControlMode::REMOTE_CONTROL:
                        {
                            if(cap::CAPV2_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
                                ret = ConstructRRB_CON_ACh(ctxt, &cca, cmptList);
                            else if(cap::CAPV1_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
                            {
                                DLOG_ERROR("DeduceAndConstructCAMELMsg:: Recv IDP capverion : V1, SCP-Action : %s, CAPControMode : %s",
                                        (GetStrSCPAction(userData->GetSCPAction())).c_str(),
                                        (GetStrCAPControlMode(userData->GetCAPControlMode())).c_str());
                                DLOG_INFO("DeduceAndConstructCAMELMsg:: Send ReleaseCall and CCR-T.");
                                ctxt->SetErrorCode(TSLConstants::INVALID_CONTROL_MODE_CAPV1);
                                ret = !ITS_SUCCESS;
                            }               
                            userData->SetFirstERBReceived(false);                                            
                        }
                        break;
                    case CAPControlMode::NO_CONTROL:
                        {
                            //ConstructCON_TCEnd();           
                            ctxt->SetIsTCAPEnd(true);
                        }
                        break;
                    default:
                        {
                            DLOG_ERROR("DeduceAndConstructCAMELMsg:: CapControlMode Invalid value: %d.",userData->GetCAPControlMode());
                            ret = !ITS_SUCCESS;
                        }

                }

            }
            break;
        case SCPAction::REJECT:
            {
                switch(userData->GetCAPControlMode())
                {
                    case CAPControlMode::LOCAL_CONTROL:
                    case CAPControlMode::REMOTE_CONTROL:
                    case CAPControlMode::NO_CONTROL:
                    default:
                        {
                            DLOG_INFO("DeduceAndConstructCAMELMsg:: SCPAction : %d , CapControlMode : %d. Send CCR-T and RELEASE",
                                    userData->GetSCPAction(),
                                    userData->GetCAPControlMode());
                            ret = !ITS_SUCCESS;
                        }

                }
            }
            break;
        case SCPAction::TRANSPARENT_FOLLOW_ON:
            {
                switch(userData->GetCAPControlMode())
                {
                    case CAPControlMode::LOCAL_CONTROL:
                    case CAPControlMode::REMOTE_CONTROL:
                        {
                            ExtractAndSetConnectMaxDuration(ctxt, cca);
                            ret = ConstructRRB_CON(ctxt, &cca, cmptList);
                        }
                        break;
                    case CAPControlMode::NO_CONTROL:
                        {
                            //ConstructCON_TCEnd();           
                            ctxt->SetIsTCAPEnd(true);
                        }
                        break;
                    default:
                        {
                            DLOG_ERROR("DeduceAndConstructCAMELMsg:: CapControlMode Invalid value: %d.",userData->GetCAPControlMode());
                            ret = !ITS_SUCCESS;
                        }
                }
            }
            break;
        default:
            {
                DLOG_ERROR("DeduceAndConstructCAMELMsg:: Invalid ScpAction value: %d.",userData->GetSCPAction());
            }

    }

    //DLOG_INFO("DeduceAndConstructCAMELMsg:: Exit");
    return ret;

}

int TransatelCAPToRoHandler::ConstructRRB_CONT(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer& cca,
        TcapCptList *&cmptList)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ConstructRRB_CONT -- Entry"); 
    int rc = ITS_SUCCESS;


    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    bool buildFailed = false;

    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportBCSMEvent]");
    BuildRRB(ctxt,&cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_RRBCSM_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);
        cmptList->BuildTcapCptList(*cpt);
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

    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Continue]");
    BuildContinue(ctxt,&cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
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
        ctxt->SetErrorCode(ITS_EASNENCODE);
        rc = !ITS_SUCCESS;
    }
    //DLOG_INFO("ConstructRRB_CONT:: Exit");
    return rc;
}

int TransatelCAPToRoHandler::ConstructRRB_CONT_ACh(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer& cca,
        TcapCptList *&cmptList)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ConstructRRB_CONT_ACh -- Entry"); 
    int rc = ITS_SUCCESS;


    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    bool buildFailed = false;

    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportBCSMEvent]");
    BuildRRB(ctxt,&cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_RRBCSM_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);
        cmptList->BuildTcapCptList(*cpt);
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
    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ApplyChargingArg]");
    BuildACH(ctxt,&cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_AC_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
        //DLOG_DEBUG("ACH Built Successfully appended to the list");
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
    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Continue]");
    BuildContinue(ctxt,&cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
    }
    else
    {
        //DLOG_ERROR("Faild to build CAP Continue for CCA-I");
        buildFailed = true;
    }
    if( cpt != NULL )
    {
        delete cpt;
        cpt = NULL;
    }
    if( buildFailed )
    {
        ctxt->SetErrorCode(ITS_EASNENCODE);
        rc = !ITS_SUCCESS;
    }

    //DLOG_DEBUG("ConstructRRB_CONT_ACh -- Entry"); 
    return rc;
}

int TransatelCAPToRoHandler::ConstructRRB_CON(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer* cca,
        TcapCptList *&cmptList)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ConstructRRB_CON -- Entry"); 
    int rc = ITS_SUCCESS;


    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    bool buildFailed = false;

    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportBCSMEvent]");
    BuildRRB(ctxt, cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_RRBCSM_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);
        cmptList->BuildTcapCptList(*cpt);
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
    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Connect]");
    BuildConnect(ctxt,cca,cpt);
    if( cpt != NULL )
    {
        //UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
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
        ctxt->SetErrorCode(ITS_EASNENCODE);
        rc = !ITS_SUCCESS;
    }

    //DLOG_DEBUG("ConstructRRB_CON -- Entry");
    return rc;
}

int TransatelCAPToRoHandler::ConstructRRB_CON_ACh(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer* cca,
        TcapCptList *&cmptList)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ConstructRRB_CON_ACh -- Entry"); 
    int rc = ITS_SUCCESS;


    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    bool buildFailed = false;

    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportBCSMEvent]");
    BuildRRB(ctxt,cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_RRBCSM_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);
        cmptList->BuildTcapCptList(*cpt);
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
    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ApplyChargingArg]");
    BuildACH(ctxt,cca,cpt);
    if( cpt != NULL )
    {
        UPDATE_SSG_STATS_AC_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
        //DLOG_DEBUG("ACH Built Successfully appended to the list");
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
    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Connect]");
    BuildConnect(ctxt, cca,cpt);
    if( cpt != NULL )
    {
        //UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
        invkId = ctxt->GetInvkId();
        cpt->SetInvokeID(++invkId);
        ctxt->SetInvkId(invkId);
        ctxt->StoreOutgoingInvokeId(invkId);

        cmptList->BuildTcapCptList(*cpt);
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
        ctxt->SetErrorCode(ITS_EASNENCODE);
        rc = !ITS_SUCCESS;
    }

    //DLOG_DEBUG("ConstructRRB_CON_ACh -- Entry"); 
    return rc;
}

int TransatelCAPToRoHandler::ConstructCptInTCEnd(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer& cca,
        TcapCptList *&cmptList)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ConstructCptInTCEnd -- Entry"); 
    int rc = ITS_SUCCESS;
    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    bool buildFailed = false;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    switch(userData->GetSCPAction())
    {
        case SCPAction::CONTINUE:
            {
                if(userData->IsIDPSMSReceived())
                {
                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ContinueSMS]");
                    BuildContinueSMS(ctxt,&cca,cpt);
                }
                else
                {
                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Continue]");
                    BuildContinue(ctxt,&cca,cpt);
                }

                if( cpt != NULL )
                {
                    if(userData->IsIDPSMSReceived())
                    {
                        UPDATE_SSG_STATS_CONTINUE_SMS_ARG_SENT;
                    }
                    else
                    {
                        UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
                    }
                    invkId = ctxt->GetInvkId();
                    cpt->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    ctxt->StoreOutgoingInvokeId(invkId);

                    cmptList->BuildTcapCptList(*cpt);
                }
                else
                {
                    DLOG_ERROR("Failed to build CAP Continue for CCA-I");
                    buildFailed = true;
                }
                if( cpt != NULL )
                {
                    delete cpt;
                    cpt = NULL;
                }
                if( buildFailed )
                {
                    ctxt->SetErrorCode(ITS_EASNENCODE);
                    rc = !ITS_SUCCESS;
                }
                break;
            }
        case SCPAction::CONNECT:
            {
                if(userData->IsFollowingOnSet())
                {
                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Connect] & [CAP:RRB]");
                    rc = ConstructRRB_CON(ctxt, &cca, cmptList);
                }
                else
                {
                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:Connect]");
                    BuildConnect(ctxt,&cca,cpt);
                    if( cpt != NULL )
                    {
                        //UPDATE_SSG_STATS_CONTINUE_ARG_SENT;
                        invkId = ctxt->GetInvkId();
                        cpt->SetInvokeID(++invkId);
                        ctxt->SetInvkId(invkId);
                        ctxt->StoreOutgoingInvokeId(invkId);

                        cmptList->BuildTcapCptList(*cpt);
                    }
                    else
                    {
                        DLOG_ERROR("Failed to build CAP Continue for CCA-I");
                        buildFailed = true;
                    }
                    if( cpt != NULL )
                    {
                        delete cpt;
                        cpt = NULL;
                    }
                    if( buildFailed )
                    {
                        ctxt->SetErrorCode(ITS_EASNENCODE);
                        rc = !ITS_SUCCESS;
                    }
                }
                break;
            }
        default:
            {
                DLOG_ERROR("Unexpected SCP Action Received : %d", userData->GetSCPAction());
                rc = !ITS_SUCCESS;
            }
    }
    //DLOG_DEBUG("ConstructCptInTCEnd-- Entry"); 
    return rc;
}



int TransatelCAPToRoHandler::ExtractAndSetNoAnsTime(TransatelCAPRoTransactionContext* userData,
        Ro_TSL::CreditControlAnswer& cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("ExtractAndSetNoAnsTime:: Entry");
    int ret = ITS_SUCCESS;



    if(cca.containsServiceControl())
    {
        if(cca.getServiceControl().containsCAPInformation())
        {
            if(cca.getServiceControl().getCAPInformation().containsCAPRRBSInformation())
            {
                if(cca.getServiceControl().getCAPInformation().getCAPRRBSInformation().containsCAPRRBSNoAnswerTimeout())
                {
                    TransCustomAvp::CAPRRBSNoAnswerTimeout noAnsTime = cca.getServiceControl().getCAPInformation().getCAPRRBSInformation().getCAPRRBSNoAnswerTimeout();
                    //DLOG_DEBUG("CAP-RRB-NoAnswerTimeout : %u recv in CCA.",noAnsTime.value());
                    userData->SetNoAnsTime(noAnsTime.value());
                }
                else
                {
                    DLOG_ERROR("CAP-RRB-NoAnswerTimeout Avp not present in the CCA");                    
                    ret = !ITS_SUCCESS;
                }
            }
            else
            {
                DLOG_ERROR("CAP-RRB-Information Avp not present in the CCA");
                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            DLOG_ERROR("CAP-Information Avp not present in the CCA");
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        DLOG_ERROR("Service-Control Avp not present in the CCA");
        ret = !ITS_SUCCESS;
    }
    if(ret == !ITS_SUCCESS)
    {
        //DLOG_DEBUG("CAP-RRB-NoAnswerTimeout Avp not present in the CCA, Populating with Default Value %u .", m_config.VoiceNoEventTimer());
        userData->SetNoAnsTime(m_config.VoiceNoEventTimer());
    }
    //DLOG_INFO("ExtractAndSetNoAnsTime:: Exit");
    return ret;

}

int TransatelCAPToRoHandler::UpdateGSUValues(TransatelCAPRoTransactionContext* userData,
        Ro_TSL::CreditControlAnswer& cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("UpdateGSUValues :: Entry");
    int ret = ITS_SUCCESS;

    if( cca.countMultipleServicesCreditControl() )
    {
        Ro_TSL::MultipleServicesCreditControl mscc =
            cca.getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsGrantedServiceUnit() )
        {
            Ro_TSL::GrantedServiceUnit gsu = mscc.getGrantedServiceUnit();
            if( !gsu.containsCCTime() || gsu.getCCTime().value() == 0)
            {
                return !ITS_SUCCESS;
            }

            //DLOG_DEBUG("GSU-CCTime : %u recv in CCA.",gsu.getCCTime().value());
            userData->SetCumulativeGSUCCTime(gsu.getCCTime().value());
            userData->SetGSUCCTime(gsu.getCCTime().value());
        }
        else
        {
            DLOG_ERROR("GSU AVP missing in CCA");
            return !ITS_SUCCESS;
        }

    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
        ret = !ITS_SUCCESS;
    }
    //DLOG_INFO("UpdateGSUValues :: Exit");
    return ret;
}

void TransatelCAPToRoHandler::StoreCallAnswerTimeStamp(TransatelCAPRoTransactionContext* userData)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("StoreCallAnswerTimeStamp :: Entry");
    struct timeval tv = GetCurrentMonotonic();

    //DLOG_DEBUG("CallAnswer TimeStamp Stored %u", tv.tv_sec);
    userData->SetCallAnsTimeStamp(tv.tv_sec);
    //DLOG_INFO("StoreCallAnswerTimeStamp :: Exit");
}

uint32_t TransatelCAPToRoHandler::RetrieveTotalCallTimeDuration(IwfFsm* ctxt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("RetrieveTotalCallTimeDuration :: Entry");
    struct timeval tv = GetCurrentMonotonic();

    uint32_t diffTime = 0;
    //DLOG_DEBUG("Current TimeStamp %u", tv.tv_sec);
    TransatelCAPRoTransactionContext* userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(userData != NULL && userData->GetCallAnsTimeStamp() != 0)
    {
        diffTime = (tv.tv_sec - userData->GetCallAnsTimeStamp());
        //DLOG_DEBUG("Call Duration %u", diffTime);
    }
    //DLOG_INFO("RetrieveTotalCallTimeDuration :: Exit");
    return diffTime;

}

struct timeval TransatelCAPToRoHandler::GetCurrentMonotonic()
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("GetCurrentMonotonic :: Entry");

#ifdef USING_MONOTONIC_CLOCK 
    /* Implementation will be taken up when we have a 
     * mechanism to synch it between ACT/STBY.*/
    struct timespec ts;
    struct timeval tv; 
#if defined (CLOCK_MONOTONIC_COARSE)
    //faster version of CLOCK_MONOTONIC but less accurate
    // we won't be needing accuracy of few nanosecs
    clock_gettime(CLOCK_MONOTONIC_COARSE, &ts);
    tv.tv_sec = ts.tv_sec;
    //DLOG_DEBUG("Current Monotonic Coarse Time%u", tv.tv_sec);
#elif defined (CLOCK_MONOTONIC)
    // slower version more accurate
    clock_gettime(CLOCK_MONOTONIC, &ts);
    tv.tv_sec = ts.tv_sec;
    //DLOG_DEBUG("Current Monotonic Time%u", tv.tv_sec);
#else
    // Monotonic clock not awailable, do a gettimeofday
    // since it is more portable
    gettimeofday(&tv, NULL);
    //DLOG_DEBUG("Current Time%u", tv.tv_sec);
#endif
#endif
    struct timeval tv;
    gettimeofday(&tv, NULL);
    //DLOG_DEBUG("Current Time%u", tv.tv_sec);
    //DLOG_INFO("GetCurrentMonotonic :: Exit");
    return tv;
}

int TransatelCAPToRoHandler::GetBeepToneFromCCA(Ro_TSL::CreditControlAnswer& cca,
        unsigned int& BeepToneVal)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("GetBeepToneFromCCA:: Entry");
    int ret = ITS_SUCCESS;
    BeepToneVal = 0;
    if(!cca.containsServiceControl())
    {
        DLOG_ERROR("GetBeepToneFromCCA::Service-Control Avp not present in the CCA");
        return !ITS_SUCCESS;
    }
    if(!cca.getServiceControl().containsCAPInformation())
    {
        DLOG_ERROR("GetBeepToneFromCCA::CAP-Information Avp not present in the CCA");
        return !ITS_SUCCESS;
    }
    if(!cca.getServiceControl().getCAPInformation().containsCAPACHInformation())
    {
        DLOG_ERROR("GetBeepToneFromCCA::CAP-ACH-Information Avp not present in the CCA");
        return !ITS_SUCCESS;
    }

    if(!cca.getServiceControl().getCAPInformation().getCAPACHInformation().containsCAPACHBeepTone())
    {
        DLOG_ERROR("GetBeepToneFromCCA::CAP-ACH-Information Avp not present in the CCA");
        return !ITS_SUCCESS;
    }

    BeepToneVal = cca.getServiceControl().getCAPInformation().getCAPACHInformation().getCAPACHBeepTone().value();

    //DLOG_INFO("GetBeepToneFromCCA:: Exit");
    return ret;

}

void TransatelCAPToRoHandler::RetrieveERBData(TransCustomAvp::CAPERBSInformation& capERBInfo, 
        pbERBData& erbAvpVal)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::RetrieveERBData Entry");

    TransCustomAvp::CAPERBSLegId legIdVal(erbAvpVal.recvlegid());
    capERBInfo.setCAPERBSLegId(legIdVal);

    TransCustomAvp::CAPERBSEventSpecificInformation evtSpecInfo(erbAvpVal.eventspecinfo());
    if(erbAvpVal.has_eventspecinfo())
        capERBInfo.setCAPERBSEventSpecificInformation(evtSpecInfo);

    TransCustomAvp::CAPERBSMessageType erbmsgType(erbAvpVal.msgtype());
    capERBInfo.setCAPERBSMessageType(erbmsgType);


    TransCustomAvp::CAPEventTypeBCSM erbEvtType(erbAvpVal.erbrecvevttype());
    capERBInfo.setCAPEventTypeBCSM(erbEvtType);

    //DLOG_DEBUG("TransatelCAPToRoHandler::RetrieveERBData Exit");

}

std::string TransatelCAPToRoHandler::GetStrBCSMEventType(cap_v2::EventTypeBCSM& eventType)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrBCSMEventType Entry");
    std::string strEventTypeBCSM("");
    switch(eventType.GetValue())
    {
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_COLLECTED_INFO : 
            strEventTypeBCSM = "COLLECTED_INFO";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE : 
            strEventTypeBCSM = "ROUTE_SELECT_FAILURE";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OCALLED_PARTY_BUSY : 
            strEventTypeBCSM = "OCALLED_PARTY_BUSY";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER : 
            strEventTypeBCSM = "ONO_ANSWER";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER : 
            strEventTypeBCSM = "OANSWER";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT : 
            strEventTypeBCSM = "ODISCONNECT";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OABANDON : 
            strEventTypeBCSM = "OABANDON";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TERM_ATTEMPT_AUTHORIZED : 
            strEventTypeBCSM = "TERM_ATTEMPT_AUTHORIZED";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TBUSY : 
            strEventTypeBCSM = "TBUSY";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TNO_ANSWER : 
            strEventTypeBCSM = "TNO_ANSWER";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER : 
            strEventTypeBCSM = "TANSWER";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT : 
            strEventTypeBCSM = "TDISCONNECT";
            break;
        case cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TABANDON : 
            strEventTypeBCSM = "TABANDON";
            break;
        default :
            strEventTypeBCSM = "";
            break;
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrBCSMEventType Exit");
    return strEventTypeBCSM;
}

std::string TransatelCAPToRoHandler::GetStrTimerType(ETimerType& timerType)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrTimerType Entry");
    std::string strTimerType("");
    switch(timerType)
    {
        case NO_EVENT_TIMER : 
            strTimerType = "NO_EVENT_TIMER";
            break;
        case FAKE_ACH_TIMER : 
            strTimerType = "FAKE_ACH_TIMER";
            break;
        case ACTIVITY_TIMER : 
            strTimerType = "ACTIVITY_TIMER";
            break;
        case ACH_DELTA_TIMER : 
            strTimerType = "ACH_DELTA_TIMER";
            break;
        case ACR_TIMER : 
            strTimerType = "ACR_TIMER";
            break;
        case INVALID_TIMER : 
            strTimerType = "INVALID_TIMER";
            break;
        default :
            strTimerType = "";
            break;
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrTimerType Exit");
    return strTimerType;
}

std::string& TransatelCAPToRoHandler::GetStrSCPAction(int scpAction)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrSCPAction Entry");
    std::string strScpAction("");
    switch(scpAction)
    {
        case TransCustomAvp::SCPAction::REJECT : 
            strScpAction = "REJECT";
            break;
        case TransCustomAvp::SCPAction::CONTINUE : 
            strScpAction = "CONTINUE";
            break;
        case TransCustomAvp::SCPAction::CONNECT : 
            strScpAction = "CONNECT";
            break;
        case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON : 
            strScpAction = "TRANSPARENT_FOLLOW_ON";
            break;
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE : 
            strScpAction = "FOLLOW_ON_CONTINUE";
            break;
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT : 
            strScpAction = "FOLLOW_ON_CONNECT";
            break;
        default :
            strScpAction = "";
            break;
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrSCPAction Exit");
    return strScpAction;
}
std::string& TransatelCAPToRoHandler::GetStrCAPControlMode(signed int controlMode)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrCAPControlMode Entry");
    std::string strControlMode("");
    switch(controlMode)
    {
        case TransCustomAvp::CAPControlMode::NO_CONTROL : 
            strControlMode = "NO_CONTROL";
            break;
        case TransCustomAvp::CAPControlMode::LOCAL_CONTROL : 
            strControlMode = "LOCAL_CONTROL";
            break;
        case TransCustomAvp::CAPControlMode::REMOTE_CONTROL : 
            strControlMode = "REMOTE_CONTROL";
            break;
        default :
            strControlMode = "";
            break;
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetStrCAPControlMode Exit");
    return strControlMode;
}

int TransatelCAPToRoHandler::ExtractAndSetConnectMaxDuration(IwfFsm* ctxt,Ro_TSL::CreditControlAnswer& cca)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::ExtractAndSetConnectMaxDuration Entry");
    int retVal = ITS_SUCCESS;
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(cca.containsServiceControl())
    {
        TransCustomAvp::ServiceControl servCtrl = cca.getServiceControl();
        if(servCtrl.containsCAPInformation())
        {
            TransCustomAvp::CAPInformation capInfo = servCtrl.getCAPInformation();
            if(capInfo.containsCAPConnectInformation())
            {
                TransCustomAvp::CAPConnectInformation capConnectInfo = capInfo.getCAPConnectInformation();

                if(capConnectInfo.containsCAPConnectMaxDuration())
                {
                    TransCustomAvp::CAPConnectMaxDuration connectMaxDuration = capConnectInfo.getCAPConnectMaxDuration();
                    //DLOG_DEBUG("CAP-Connect-MaxDuration : %u recv in CCA.", connectMaxDuration.value());
                    userData->SetConnectMaxDuration(connectMaxDuration.value());
                }
                else
                {
                    //DLOG_INFO("Cap-Connect-Max-Duration not present in incoming CCA-I");
                    retVal = !ITS_SUCCESS;
                }
            }
            else
            {
                //DLOG_INFO("Cap-Connect-Information not present in incoming CCA-I");
                retVal = !ITS_SUCCESS;
            }
        }
        else
        {
            //DLOG_INFO("Cap-Information not present in incoming CCA-I");
            retVal = !ITS_SUCCESS;
        }
    }
    else
    {
        //DLOG_INFO("Service-Control not present in incoming CCA-I");
        retVal = !ITS_SUCCESS;
    }

    if(retVal == !ITS_SUCCESS)
    {
        /*DLOG_DEBUG("CAP-Conenct-MaxDuration Avp not present in the CCA, Populating with Default Value %u .", 
                m_config.GetConnectMaxCallDuration());*/
        userData->SetConnectMaxDuration(m_config.GetConnectMaxCallDuration());
    }

    //DLOG_DEBUG("TransatelCAPToRoHandler::ExtractAndSetConnectMaxDuration Exit");
    return retVal;
}

#if 0
//Accessor methods for IDP-CCRI mapped AVP values.
Call_Type IDPToCCRIData::GetCallType()
{
    return callTypeVal;
}
void IDPToCCRIData::SetCallType(Call_Type val)
{
    callTypeVal = val;
}
unsigned int IDPToCCRIData::GetService_Key()
{
    return Service_Key;
}
void IDPToCCRIData::SetService_Key(unsigned int val)
{
    Service_Key = val;          
}
unsigned int IDPToCCRIData::GetCalled_TON()
{
    return Called_TON;
}
void IDPToCCRIData::SetCalled_TON(unsigned int val)
{
    Called_TON = val;
}
unsigned int IDPToCCRIData::GetCalled_NPI()
{
    return Called_NPI;
}
void IDPToCCRIData::SetCalled_NPI(unsigned int val)
{
    Called_NPI = val;
}
unsigned int IDPToCCRIData::GetCalling_NOA()
{
    return Calling_NOA; 
}
void IDPToCCRIData::SetCalling_NOA(unsigned int val)
{
    Calling_NOA = val;
}
unsigned int IDPToCCRIData::GetCLI_NPI()
{
    return CLI_NPI;
}
void IDPToCCRIData::SetCLI_NPI(unsigned int val)
{
    CLI_NPI = val;
}
unsigned int IDPToCCRIData::GetVersion()
{
    return Version;
}
void IDPToCCRIData::SetVersion(unsigned int val)
{
    Version = val;
}
unsigned int IDPToCCRIData::GetEvent_Type_BCSM()
{
    return Event_Type_BCSM;
}
void IDPToCCRIData::SetEvent_Type_BCSM(unsigned int val)
{
    Event_Type_BCSM = val;
}
unsigned int IDPToCCRIData::GetTCAP_Error_Cause()
{
    return TCAP_Error_Cause;
}
void IDPToCCRIData::SetTCAP_Error_Cause(unsigned int val)
{
    TCAP_Error_Cause = val;
}
unsigned int IDPToCCRIData::GetSCCP_Error_Cause()
{
    return SCCP_Error_Cause;
}
void IDPToCCRIData::SetSCCP_Error_Cause(unsigned int val)
{
    SCCP_Error_Cause = val;
}
unsigned int IDPToCCRIData::GetCalling_Category()
{
    return Calling_Category;
}
void IDPToCCRIData::SetCalling_Category(unsigned int val)
{
    Calling_Category = val;
}
unsigned int IDPToCCRIData::GetRedirecting_Indicator()
{
    return Redirecting_Indicator;
}
void IDPToCCRIData::SetRedirecting_Indicator(unsigned int val)
{
    Redirecting_Indicator = val;
}
unsigned int IDPToCCRIData::GetOriginal_Redirecting_Reason()
{
    return Original_Redirecting_Reason;
}
void IDPToCCRIData::SetOriginal_Redirecting_Reason(unsigned int val)
{
    Original_Redirecting_Reason = val;
}
unsigned int IDPToCCRIData::GetRedirection_Counter()
{
    return Redirection_Counter;
}
void IDPToCCRIData::SetRedirection_Counter(unsigned int val)
{
    Redirection_Counter = val;
}
unsigned int IDPToCCRIData::GetRedirecting_Reason()
{
    return Redirecting_Reason;
}
void IDPToCCRIData::SetRedirecting_Reason(unsigned int val)
{
    Redirecting_Reason = val;
}
unsigned int IDPToCCRIData::GetCLIR()
{
    return CLIR;
}
void IDPToCCRIData::SetCLIR(unsigned int val)
{
    CLIR = val;
}
unsigned int IDPToCCRIData::GetGSM_Forwarding_Pending()
{
    return GSM_Forwarding_Pending;
}
void IDPToCCRIData::SetGSM_Forwarding_Pending(unsigned int val)
{
    GSM_Forwarding_Pending = val;
}

std::string IDPToCCRIData::GetRedirecting_Number()
{
    return Redirecting_Number;
}
void IDPToCCRIData::SetRedirecting_Number(std::string val)
{
    Redirecting_Number = val;
}
std::string IDPToCCRIData::GetGMSC()
{
    return GMSC;
}
void IDPToCCRIData::SetGMSC(std::string val)
{
    GMSC = val;
}
std::string IDPToCCRIData::GetExt_Basic_Service_Code()
{
    return Ext_Basic_Service_Code;
}
void IDPToCCRIData::SetExt_Basic_Service_Code(std::string val)
{
    Ext_Basic_Service_Code = val;
}
std::string IDPToCCRIData::GetBearer_Capability()
{
    return Bearer_Capability;
}
void IDPToCCRIData::SetBearer_Capability(std::string val)
{
    Bearer_Capability = val;
}
std::string IDPToCCRIData::GetBearer_Capability_Transfer()
{
    return Bearer_Capability_Transfer;
}
void IDPToCCRIData::SetBearer_Capability_Transfer(std::string val)
{
    Bearer_Capability_Transfer = val;
}
std::string IDPToCCRIData::GetBearer_Capability_Transfer_Rate()
{
    return Bearer_Capability_Transfer_Rate;
}
void IDPToCCRIData::SetBearer_Capability_Transfer_Rate(std::string val)
{
    Bearer_Capability_Transfer_Rate = val;
}

std::string IDPToCCRIData::GetBearer_Capability_Transfer_Mode()
{
    return Bearer_Capability_Transfer_Mode;
}
void IDPToCCRIData::SetBearer_Capability_Transfer_Mode(std::string val)
{
    Bearer_Capability_Transfer_Mode = val;
}
std::string IDPToCCRIData::GetDialed_Digits()
{
    return Dialed_Digits;
}
void IDPToCCRIData::SetDialed_Digits(std::string val)
{
    Dialed_Digits = val;
}

std::string IDPToCCRIData::GetCLI()
{
    return CLI;
}
void IDPToCCRIData::SetCLI(std::string val)
{
    CLI = val;
}
std::string IDPToCCRIData::GetLocation_Number()
{
    return Location_Number;
}
void IDPToCCRIData::SetLocation_Number(std::string val)
{
    Location_Number = val;
}
std::string IDPToCCRIData::GetIMSI()
{
    return IMSI;
}
void IDPToCCRIData::SetIMSI(std::string val)
{
    IMSI = val;
}
std::string IDPToCCRIData::GetVLR_Number()
{
    return VLR_Number;
}
void IDPToCCRIData::SetVLR_Number(std::string val)
{
    VLR_Number = val;
}
std::string IDPToCCRIData::GetCall_Reference()
{
    return Call_Reference;
}
void IDPToCCRIData::SetCall_Reference(std::string val)
{
    Call_Reference = val;
}
std::string IDPToCCRIData::GetMSC_Address()
{
    return MSC_Address;
}
void IDPToCCRIData::SetMSC_Address(std::string val)
{
    MSC_Address = val;
}
std::string IDPToCCRIData::GetSCCP_CallingGT()
{ 
    return SCCP_CallingGT;
}
void IDPToCCRIData::SetSCCP_CallingGT(std::string val)
{
    SCCP_CallingGT = val;
}
std::string IDPToCCRIData::GetSCCP_CalledGT()
{
    return SCCP_CalledGT;
}
void IDPToCCRIData::SetSCCP_CalledGT(std::string val)
{
    SCCP_CalledGT = val;
}
std::string IDPToCCRIData::GetTCAP_Remote_Transaction_Id()
{
    return TCAP_Remote_Transaction_Id;
}
void IDPToCCRIData::SetTCAP_Remote_Transaction_Id(std::string val)
{
    TCAP_Remote_Transaction_Id = val;
}
std::string IDPToCCRIData::GetTCAP_Local_Transaction_Id()
{
    return TCAP_Local_Transaction_Id;
}
void IDPToCCRIData::SetTCAP_Local_Transaction_Id(std::string val)
{
    TCAP_Local_Transaction_Id = val;
}
std::string IDPToCCRIData::GetCellID_AreaID_LAI()
{
    return CellID_AreaID_LAI;
}
void IDPToCCRIData::SetCellID_AreaID_LAI(std::string val)
{
    CellID_AreaID_LAI = val;
}

std::string ERBData::GetEvtSpecInfo()
{
    return eventSpecInfo;
}
void ERBData::SetEvtSpecInfo(std::string val)
{
    eventSpecInfo = val;
}

unsigned int ERBData::GetRecvEvntType()
{
    return erbRecvEvtType;
}
void ERBData::SetRecvEvntType(unsigned int val)
{
    erbRecvEvtType = val;
}
unsigned int ERBData::GetRecvLegId()
{
    return recvlegId;
}
void ERBData::SetRecvLegId(unsigned int val)
{
    recvlegId = val;
}
unsigned int ERBData::GetMsgType()
{
    return msgType;
}
void ERBData::SetMsgType(unsigned int val)
{
    msgType = val;
}

void ERBData::ResetERBData()
{
    erbRecvEvtType = 0; 
    eventSpecInfo = "";
    recvlegId = 0; 
    msgType = 0; 
}

void IDPToCCRIData::SetBearerCapabilityForCdr(std::string val)
{
    Bearer_Capability_Cdr.assign(val);
}

std::string IDPToCCRIData::GetBearerCapabilityForCdr()
{
    return Bearer_Capability_Cdr;
}

void IDPToCCRIData::SetCAPIsFollowingOnSet(bool isFollowingOnSet)
{
    CAPIsFollowingOn = isFollowingOnSet;
}

bool IDPToCCRIData::GetCAPIsFollowingOnSet()
{
    return CAPIsFollowingOn;
}
#endif

int TransatelCAPToRoHandler::HandleACR_Recv_Before_CallAnswered(IwfFsm* ctxt,
        const cap_v2::CAMEL_CallResult *in,
        Ro_TSL::CreditControlRequest *out,
        IwfReturnAction& ret)
{
    //DLOG_DEBUG("TransatelCAPToRoHandler::HandleACR_Recv_Before_CallAnswered Entry");

    int retVal = ITS_SUCCESS;

    ret.action = IWF_RA_CONSUME;
    TransatelCAPRoTransactionContext* userData = 
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(NULL == userData)
    {
        return !ITS_SUCCESS;
    }

    TCAP_Dialogue *currRecvTcapDlg = ctxt->GetCurrRcvdTcapDlg();    
    TCAP_Component *currRecvTcapCpt = ctxt->GetCurrRcvdTcapCpt();


    cap_v2::CAMEL_CallResult::TimeDurationChargingResult tdcr = in->GetChoiceTimeDurationChargingResult();

    cap_v2::TimeInformation ti;
    if (NULL != in)
        ti = tdcr.GetTimeInformation();
    if(NULL != in && 
            ti.ChoiceTimeIfNoTariffSwitch())
    {
        unsigned int timeIfNoTariffSwitch = ROUNDOFF_USU_VALUE(ti.GetChoiceTimeIfNoTariffSwitch().GetValue());
        DLOG_DEBUG("TransatelCAPToRoHandler::HandleACR_Recv_Before_CallAnswered, Received ACR callDuration : %d, DlgId : %u", 
                timeIfNoTariffSwitch,
                currRecvTcapDlg->GetDialogueID());
        if(timeIfNoTariffSwitch > userData->GetCumulativeGSUCCTime())
        {
            userData->SetUSUCCTime(userData->GetCumulativeGSUCCTime());
        }
        else
        {
            userData->SetUSUCCTime(timeIfNoTariffSwitch);
        }
    }

    if(!tdcr.GetCallActive().GetValue())
    {
        DLOG_DEBUG("TransatelCAPToRoHandler::HandleACR_Recv_Before_CallAnswered, CallActive = %s", 
                tdcr.GetCallActive().GetValue()?"true":"false");
        if(currRecvTcapDlg ->GetDialogueType() == TCPPT_TC_CONTINUE &&
                currRecvTcapCpt->GetLast())
        {
            if(TransCustomAvp::CAPControlMode::REMOTE_CONTROL == userData->GetCAPControlMode())
            {
                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                ret.dir = IWF_RD_DIA;
                ConstructCCRTMessage(ctxt,out);
                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);                
            }

            userData->SetCurrentReceivedTcapContinue(true);
        }
        else if(currRecvTcapDlg ->GetDialogueType() == TCPPT_TC_END &&
                currRecvTcapCpt->GetLast())
        {
            if(TransCustomAvp::CAPControlMode::REMOTE_CONTROL == userData->GetCAPControlMode())
            {
                ret.action = IWF_RA_FORWARD;
                ret.dir = IWF_RD_DIA;                
                ConstructCCRTMessage(ctxt,out);
                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);                
            }

            userData->SetCurrentReceivedTcapContinue(false);
        }

    }



    //DLOG_DEBUG("TransatelCAPToRoHandler::HandleACR_Recv_Before_CallAnswered Entry");
    return retVal;
}


void TransatelCAPToRoHandler::ConstructCCRTMessage(IwfFsm* ctxt,
        Ro_TSL::CreditControlRequest *out)
{
    //DLOG_DEBUG("TransatelCAPToRoHandler::ConstructCCRTMessage Entry");


    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    TransCustomAvp::CAPERBSInformation capErbInfo;
    Ro_TSL::MultipleServicesCreditControl mscc;

    Ro_TSL::ServiceInformation si;

    IDPToCCRIData ccriData;
    pbERBData erbData;

    TransatelCAPRoTransactionContext* userData = 
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    out->setMultipleServicesIndicator(msi);
    ccriData = userData->GetIDPToCCRIData();
    RetrieveIDPToCCRIData(capInfo, ccriData);

    if(userData->IsFirstERBrcvd() == true)
    {
        RetrieveERBData(capErbInfo, erbData);
        if((userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_OANSWER != erbData.erbrecvevttype())) ||
                (!userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_TANSWER != erbData.erbrecvevttype())))
        {
            capInfo.setCAPERBSInformation(capErbInfo);
        }
    }

    out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST));
    if(userData)
    {
        //DLOG_DEBUG("UserData is Present setting termination cause from userData");
        out->setTerminationCause(diameter::base::TerminationCause
                ((diameter::base::TerminationCause::Value)GetTerminationCauseCode(userData)));
        userData->SetTerminationCause(GetTerminationCauseCode(userData));
        userData->SetASRReceived(false);
    }
    else
    {
        //DLOG_DEBUG("UserData is not Present setting termination cause as Diameter LOGOUT");
        out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));
    }
    ITS_UINT seconds = this->GetCurrentTimeStamp(); 
    diameter::base::EventTimestamp eventTimestamp(seconds);
    out->setEventTimestamp(eventTimestamp);
    ccrnum = userData->GetCCRequestNumber();
    Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
    out->setCCRequestNumber(ccRequestNumber);
    userData->SetCCRequestNumber(ccrnum);
    if(userData->HasServiceContextId())
    {
        Ro_TSL::ServiceContextId* serviceContextId = new Ro_TSL::ServiceContextId(userData->GetServiceContextId());
        out->setServiceContextId(*serviceContextId);
    }
#if 0
    if(userData->HasSubscriptionId())
    {
        Ro_TSL::SubscriptionId* subsId = userData->GetSubscriptionId();
        out->addSubscriptionId(*subsId);
    }
#endif
    Ro_TSL::UsedServiceUnit usu;
    Ro_TSL::CCTime cctime(userData->GetUSUCCTime());
    usu.setCCTime(cctime);    
    //DLOG_DEBUG("TransatelCAPToRoHandler::ConstructCCRTMessage, UsedCCTime set  : %d", 
    //        usu.getCCTime().value());

    mscc.addUsedServiceUnit(usu);

    csInfo.setCAPInformation(capInfo);
    si.setCSInformation(csInfo);
    out->setServiceInformation(si);
    out->addMultipleServicesCreditControl(mscc);


    //DLOG_DEBUG("TransatelCAPToRoHandler::ConstructCCRTMessage Exit");

}

/*
* Description : Extracts the Result Code AVP value and sets it in TSLCapToRoContext based on CCA-RequestType
*                    These values shall be retrieved durign CDR logging only.
* Params      : Both cmd & userData are in parameters, cmd contains the received CCA message & 
*                     userData shall be updated with ResultCode values                   
*/
void TransatelCAPToRoHandler::UpdateCCAResultCodeForCDR(diameter::Command* cmd, 
                                                                  TransatelCAPRoTransactionContext* userData)
{
    if(NULL == cmd || 
       NULL == userData)
    {
        return;
    }
        
    Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
    if(cca.getCCRequestType().value() == userData->GetLastSentCCRequestType())
    {
        if(Ro_TSL::CCRequestType::TERMINATION_REQUEST == cca.getCCRequestType().value())
        {
            userData->SetCurrentCCATResultCode(cca.getResultCode().value());
        }
        else if(Ro_TSL::CCRequestType::UPDATE_REQUEST == cca.getCCRequestType().value())
        {
            userData->SetCurrentCCAUResultCode(cca.getResultCode().value());        
        }
        else if(Ro_TSL::CCRequestType::INITIAL_REQUEST == cca.getCCRequestType().value())
        {
            userData->SetCurrentCCAIResultCode(cca.getResultCode().value());
        }
    }
}
