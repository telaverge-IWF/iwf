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
#include "iwf_transaction_manager.h"

#include <dia_frame.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <ssg_trace.h>
#include <ssg_statistics.h>

#include <sstream>
#include <bitset>


#include "tcap_intern.h"
#include <itu/tcap.h>

#define CallingLegId "1"
#define CalledLegId "2"
#define NORMAL_CALL_CLEARING 0x90
#define USER_BUSY 0x91
#define NO_ANSWER_FROM_USER 0x93
#define CAUSE_LOCATION_USER 0x80
#define CAUSE_LOCATION_RLN 0x84
#define OPERATOR_DETERMINED_BARRING 0x08
#define MSCC_AVP_INDEX 0


extern ITSDiaConfig itsDiaConfig;

using namespace cap_v1;
using namespace cap_v2;
using namespace cap_v3;

SsgStackStatistics mapStats;

/*CCR Number which will be used for CCR-I/U/T */
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

    cmd->setSessionId(diameter::base::SessionId(sessId));
    ctxt->SetDiaSessionId(sessId);
    DIA_CER *lcer = itsDiaConfig.GetLocalCER();
    cmd->setOriginHost(lcer->getOriginHost());
    cmd->setOriginRealm(lcer->getOriginRealm());

    if ( lcer->containsOriginStateId() )
    {
        cmd->setOriginStateId(diameter::base::OriginStateId(lcer->getOriginStateId()));
    }
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
int SetDestinationHostAndRealm(IwfFsm *ctxt, std::string simsi,
        ITS_UINT serviceKey, T *cmd,bool isInitial = false)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if (ctxt == NULL)
    {
        DLOG_ERROR("IWFFsm in null");
        return !ITS_SUCCESS;
    }

    if (isInitial)
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
            /*DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Not Found, Routing to Realm: %s : Based on SelectionCriteria %d",
                    destrealm.c_str(), IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());*/
            diameter::base::DestinationRealm dr(destrealm);
            cmd->setDestinationRealm(dr);

            // Check with DCCA to set the destination endpoint
            std::string destHost;
            bool destFound = IwfDcca::SelectDestinationHost(destrealm, destHost);
            if (destFound)
            {
                //DLOG_DEBUG("Selected Destination Host <%s>", destHost.c_str());
                cmd->setDestinationHost(diameter::base::DestinationHost(destHost));
            }
            // The destination host and realm will be set to CapRo context when
            // the messge goes out
        }
        else
        {
            DLOG_CRITICAL("SetDestinationHostAndRealm: Destination Realm is not present in RoutingRule !!, Unable to Route Message");
            return !ITS_SUCCESS;
        }
    }
    else
    {
        // Get the destination Realm and host from DCCA
        TransatelCAPRoTransactionContext* capRoContext =
            static_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
        if (capRoContext)
        {
            IwfDccaSessionCtxt& dccaCtxt = capRoContext->GetDccaContext();
            if (!dccaCtxt.GetDestHost().empty())
            {
                cmd->setDestinationHost(
                        diameter::base::DestinationHost(dccaCtxt.GetDestHost()));
            }
            cmd->setDestinationRealm(
                    diameter::base::DestinationRealm(dccaCtxt.GetDestRealm()));
            /*DLOG_DEBUG("SetDestinationHostAndRealm: <%s> DestHost <%s> DestRealm <%s>",
                    cmd->getSessionId().value().c_str(),
                    dccaCtxt.GetDestHost().c_str(), dccaCtxt.GetDestRealm().c_str());*/
        }
#if 0
        if(isInitial)
        {
            DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Found for: %s Routing to DestinationRealm: %s",
                    simsi.c_str(),sctxt->originRealm.c_str());
            diameter::base::DestinationRealm dr(sctxt->originRealm);
            cmd->setDestinationRealm(dr);
        }
        else
        {
            DLOG_DEBUG("SetDestinationHostAndRealm: Session Context Found for: %s Routing to DestinationHost: %s and DestinationRealm: %s",
                    simsi.c_str(),sctxt->originHost.c_str(),sctxt->originRealm.c_str());
            diameter::base::DestinationHost ds(sctxt->originHost);
            diameter::base::DestinationRealm dr(sctxt->originRealm);
            cmd->setDestinationRealm(dr);
            cmd->setDestinationHost(ds);
        }
#endif

    }
    return ITS_SUCCESS;
}

inline void LogRoTslDiaMsg(diameter::Command& cmd, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if( IwfController::Instance().GetLogger().GetLevel() == Logger::Level::EACC_LOG_DEBUG )
    {
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
}

inline void LogCAPTslAsnObj(AsnObject& asn, bool incoming = true)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    stringstream str;
    if( IwfController::Instance().GetLogger().GetLevel() == Logger::Level::EACC_LOG_DEBUG )
    {
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
}

void CAPRoTSLConfig::Parse(Json::Value& val, IwfConfig& conf)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Json::Value entry = val["Voice"];
    bool isEventEnabled;
    Json::Value legId_entry;
    Json::Value oDiscEvent;
    Json::Value sub_entry;
    /* this is taken from DB now
       Json::Value sub_entry = entry["NoEventTimer"];
       if(sub_entry.empty())
       {
       throw IwfConfigException("'NoEventTimer' not part "
       "of '/proto-translator/CAP-Ro/'");
       }
       m_voiceNoEventTimer = sub_entry.asInt();
       */
#if 0
    TLegIDAndModeData legIdAndMonrMod;

    /* Parsing MO_CAPV2 LEGID and MONITORMODE */
    Json::Value sub_entry = entry["RRBCSM_ArmMode"];
    Json::Value mocapv2_entry = sub_entry["MO_CAPV2"];

    isEventEnabled = mocapv2_entry["oCldPtyBusyEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mocapv2_entry["oCldPtyBusyEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'oCldPtyBusyEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mocapv2_entry["oCldPtyBusyEvent"]["Mode"].asInt();
        m_capv2MOCldPtyBusyEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    isEventEnabled = mocapv2_entry["oNoAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {

        legId_entry = mocapv2_entry["oNoAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'oNoAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mocapv2_entry["oNoAnsEvent"]["Mode"].asInt();
        m_capv2MONoAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    isEventEnabled = mocapv2_entry["oAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {

        legId_entry = mocapv2_entry["oAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'oAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mocapv2_entry["oAnsEvent"]["Mode"].asInt();
        m_capv2MOAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    oDiscEvent = mocapv2_entry["oDisConEvent"];
    for(unsigned i = 0; i < oDiscEvent.size(); i++)
    {

        isEventEnabled = oDiscEvent[i]["Enabled"].asBool();
        if(true == isEventEnabled)
        {

            oDiscEvent = mocapv2_entry["oDisConEvent"];
            legId_entry = oDiscEvent[i]["Leg_ID"];

            if(legId_entry.empty())
            {
                throw IwfConfigException("'oDisConEvent/Leg_ID' not part "
                        "of '/proto-translator/CAP-Ro-TSL/'");
            }

            legIdAndMonrMod.legId = legId_entry.asString();
            legIdAndMonrMod.monitorMode = oDiscEvent[i]["Mode"].asInt();
            m_capv2MODisconEvnt.legIdMonMode.push_back(legIdAndMonrMod);
        }
    }

    isEventEnabled = mocapv2_entry["RouteSelectFailure"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {

        legId_entry = mocapv2_entry["RouteSelectFailure"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'RouteSelectFailure/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mocapv2_entry["RouteSelectFailure"]["Mode"].asInt();

        m_capv2MORouteSelFail.legIdMonMode.push_back(legIdAndMonrMod);
    }
    /* Parsing MT_CAPV2 LEGID and MONITORMODE */
    Json::Value mtcapv2_entry = sub_entry["MT_CAPV2"];

    isEventEnabled = mtcapv2_entry["tBusyEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mtcapv2_entry["tBusyEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'tBusyEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mtcapv2_entry["tBusyEvent"]["Mode"].asInt();
        m_capv2MTBusyEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    isEventEnabled = mtcapv2_entry["tNoAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mtcapv2_entry["tNoAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'tNoAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mtcapv2_entry["tNoAnsEvent"]["Mode"].asInt();
        m_capv2MTNoAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    isEventEnabled = mtcapv2_entry["tAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {

        legId_entry = mtcapv2_entry["tAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'tAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mtcapv2_entry["tAnsEvent"]["Mode"].asInt();
        m_capv2MTAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    Json::Value tDiscEvent = mtcapv2_entry["tDisConEvent"];
    for(unsigned i = 0; i < tDiscEvent.size(); i++)
    {
        isEventEnabled = tDiscEvent[i]["Enabled"].asBool();
        if(true == isEventEnabled)
        {
            tDiscEvent = mtcapv2_entry["tDisConEvent"];
            legId_entry = tDiscEvent[i]["Leg_ID"];

            if(legId_entry.empty())
            {
                throw IwfConfigException("'tDisConEvent/Leg_ID' not part "
                        "of '/proto-translator/CAP-Ro-TSL/'");
            }

            legIdAndMonrMod.legId = legId_entry.asString();
            legIdAndMonrMod.monitorMode = tDiscEvent[i]["Mode"].asInt();
            m_capv2MTDisconEvnt.legIdMonMode.push_back(legIdAndMonrMod);
        }
    }

    isEventEnabled = mtcapv2_entry["tAbandonEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mtcapv2_entry["tAbandonEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'tAbandonEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mtcapv2_entry["tAbandonEvent"]["Mode"].asInt();

        m_capv2MTAbandonEvt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    /* Parsing MO_CAPV1 LEGID and MONITORMODE */
    Json::Value mocapv1_entry = sub_entry["MO_CAPV1"];
    isEventEnabled = mocapv1_entry["oAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mocapv1_entry["oAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'oAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mocapv1_entry["oAnsEvent"]["Mode"].asInt();
        m_capv1MOAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    oDiscEvent = mocapv1_entry["oDisConEvent"];
    for(unsigned i = 0; i < oDiscEvent.size(); i++)
    {
        isEventEnabled = oDiscEvent[i]["Enabled"].asBool();
        if(true == isEventEnabled)
        {
            oDiscEvent = mocapv1_entry["oDisConEvent"];
            legId_entry = oDiscEvent[i]["Leg_ID"];

            if(legId_entry.empty())
            {
                throw IwfConfigException("'oDisConEvent/Leg_ID' not part "
                        "of '/proto-translator/CAP-Ro-TSL/'");
            }

            legIdAndMonrMod.legId = legId_entry.asString();
            legIdAndMonrMod.monitorMode = oDiscEvent[i]["Mode"].asInt();
            m_capv1MODisconEvnt.legIdMonMode.push_back(legIdAndMonrMod);
        }
    }

    /* Parsing MT_CAPV1 LEGID and MONITORMODE */
    Json::Value mtcapv1_entry = sub_entry["MT_CAPV1"];
    isEventEnabled = mtcapv1_entry["tAnsEvent"]["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        legId_entry = mtcapv1_entry["tAnsEvent"]["Leg_ID"];

        if(legId_entry.empty())
        {
            throw IwfConfigException("'tAnsEvent/Leg_ID' not part "
                    "of '/proto-translator/CAP-Ro-TSL/'");
        }

        legIdAndMonrMod.legId = legId_entry.asString();
        legIdAndMonrMod.monitorMode = mtcapv1_entry["oAnsEvent"]["Mode"].asInt();
        m_capv1MTAnsEvnt.legIdMonMode.push_back(legIdAndMonrMod);
    }

    tDiscEvent = mtcapv1_entry["tDisConEvent"];
    for(unsigned i = 0; i < tDiscEvent.size(); i++)
    {
        isEventEnabled = tDiscEvent[i]["Enabled"].asBool();
        if(true == isEventEnabled)
        {
            tDiscEvent = mtcapv1_entry["tDisConEvent"];

            legId_entry = tDiscEvent[i]["Leg_ID"];

            if(legId_entry.empty())
            {
                throw IwfConfigException("'tDisConEvent/Leg_ID' not part "
                        "of '/proto-translator/CAP-Ro-TSL/'");
            }

            legIdAndMonrMod.legId = legId_entry.asString();
            legIdAndMonrMod.monitorMode = tDiscEvent[i]["Mode"].asInt();
            m_capv1MTDisconEvnt.legIdMonMode.push_back(legIdAndMonrMod);
        }
    }
#endif

    sub_entry = entry["ReleaseParams"]["Cause_Location"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'Cause_Location' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ReleaseParams'");
    }
    m_voiceRelCauseLoc = sub_entry.asInt();

    sub_entry = entry["ReleaseParams"]["Coding_Standard"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'Coding_Standard' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ReleaseParams'");
    }
    m_voiceRelCauseStd = sub_entry.asInt();

    sub_entry = entry["ReleaseParams"]["Cause_Indicator"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'Cause_Indicator' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ReleaseParams'");
    }
    m_voiceReleaseCause = sub_entry.asInt();



    sub_entry = entry["ReleaseParams"]["Extension_Indicator1"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'Extension_Indicator' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ReleaseParams'");
    }
    m_voiceRelExtIndicator1 = sub_entry.asInt();

    sub_entry = entry["ReleaseParams"]["Extension_Indicator2"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'Extension_Indicator2' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ReleaseParams'");
    }
    m_voiceRelExtIndicator2 = sub_entry.asInt();
#if 0

    sub_entry = entry["ReleaseCause"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'ReleaseCause' not part "
                "of '/proto-translator/CAP-Ro-TSL/'");
    }
    m_voiceReleaseCause = sub_entry.asInt();
#endif

    sub_entry = entry["ConnectParams"]["ConnectMaxCallDuration"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'ConnectMaxCallDuration' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_ConnectCallMaxDuration = sub_entry.asInt();


    sub_entry = entry["ConnectParams"]["ConnectMaxCallDuration"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'ConnectMaxCallDuration' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_ConnectCallMaxDuration = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["AnnouncementNumber_INN"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'AnnoucementNumber_INN' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_AnnNumberINN = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["AnnouncementNumber_NOA"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'AnnoucementNumber_NOA' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_AnnNumberNOA = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["AnnouncementNumber_NPI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'AnnoucementNumber_NPI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_AnnNumberNPI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["DestinationNumber_INN"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'DestinationNumber_INN' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_DestNumberINN = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["DestinationNumber_NOA"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'DestinationNumber_NOA' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_DestNumberNOA = sub_entry.asInt();


    sub_entry = entry["ConnectParams"]["DestinationNumber_NPI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'DestinationNumber_NPI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_DestNumberNPI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_NQI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_NQI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberNQI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_NOA"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_NOA' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberNOA = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_NII"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_NII' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberNII = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_ARI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_ARI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberARI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_SCI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_SCI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberSCI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["GenericNumber_NPI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'GenericNumber_NPI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_GenNumberNPI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["RedirectingNumber_NOA"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'RedirectingNumber_NOA' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_RedirectNumberNOA = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["RedirectingNumber_NPI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'RedirectingNumber_NPI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_RedirectNumberNPI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["RedirectingNumber_ARI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'RedirectingNumber_ARI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_RedirectNumberARI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["OriginalCalledNumber_NOA"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'OriginalCalledNumber_NOA' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_OrgCldNumberNOA = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["OriginalCalledNumber_NPI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'OriginalCalledNumber_NPI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_OrgCldNumberNPI = sub_entry.asInt();

    sub_entry = entry["ConnectParams"]["OriginalCalledNumber_ARI"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'OriginalCalledNumber_ARI' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice/ConnectParams'");
    }
    m_OrgCldNumberARI = sub_entry.asInt();

    sub_entry = entry["IncludeTimeoutInCCTime"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'IncludeTimeoutInCCTime' not part "
                "of '/proto-translator/CAP-Ro-TSL/Voice'");
    }

    isEventEnabled = sub_entry["Enabled"].asBool();
    if(true == isEventEnabled)
    {
        m_includeTimeoutInCCTime = true;
    }
    else
    {
        m_includeTimeoutInCCTime = false;
    }

    entry = val["SMS"];

    /*sub_entry = entry["NoEventTimer"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'NoEventTimer' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_smsNoEventTimer = sub_entry.asInt();
      DLOG_DEBUG("NoEventTimer for Voice : %d", m_smsNoEventTimer);

      sub_entry = entry["service-context-id"];
      if(sub_entry.empty())
      {
      throw IwfConfigException("'service-context-id' not part "
      "of '/proto-translator/CAP-Ro/'");
      }
      m_smsServCtxtId = sub_entry.asString();
      */

    sub_entry = entry["ReleaseCause"];
    if(sub_entry.empty())
    {
        throw IwfConfigException("'ReleaseCause' not part "
                "of '/proto-translator/CAP-Ro/'");
    }
    m_smsReleaseCause = sub_entry.asInt();
}

TransatelCAPToRoHandler::TransatelCAPToRoHandler()
    : IwfTranslator(CAP_TO_RO_STR_TSL),
    m_cdrRecorder(new IwfFileCDRWriter(
                IWF_CAP_RO_CDR_PREFIX,
                new IwfCapRoDetailInterpreter()))
{
}

TransatelCAPToRoHandler::~TransatelCAPToRoHandler()
{
}

void TransatelCAPToRoHandler::BuildTCAPErrorCpt(IwfFsm *ctxt,
        DIA_BASE_CMD *cmd,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildTCAPErrorCpt Entry");
    TCAP_Error *terr = new TCAP_Error();
    terr->SetInvokeID(ctxt->GetCurrRcvdTcapCpt()->GetInvokeID());
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    ITS_OCTET invkId = 0;

    if(ctxt->GetErrorCode() == ITS_ETIMEOUT)
    {
        ctxt->SetErrorCode(0);
        if ( !userData->IsCapReleaseSent() )
        {
            if( userData->IsIDPSMSReceived() )
            {
                //DLOG_DEBUG("Building ReleaseSMS for timeout");
                BuildReleaseSMS(ctxt, NULL, cpt, userData->GetReleaseCause());
                UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                /*clearing the UserData to ensure releaseSMS is not sent again
                 * if in case IDP is received
                 */
                userData->SetCapReleaseSent(true);
                userData->SetIDPSMSReceived(false);
            }
            else
            {
                //DLOG_DEBUG("Building ReleaseCallArg for timeout");
                BuildRelease(ctxt, NULL, cpt, userData->GetReleaseCause());
                userData->SetCapReleaseSent(true);
                UPDATE_SSG_STATS_REL_ARG_SENT;
            }
            if ( cpt != NULL )
            {
                invkId = ctxt->GetInvkId();
                cpt->SetInvokeID(++invkId);
                ctxt->SetInvkId(invkId);
            }
        }
        else
        {
            DLOG_WARNING("Release already sent for the session");
        }
    }
    else if (ctxt->GetErrorCode())
    {
        DLOG_DEBUG("Building TcapError with Error %d",ctxt->GetErrorCode());
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

    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildTCAPErrorCpt Exit");
}

int TransatelCAPToRoHandler::BuildTCAPMsg(IwfFsm *ctxt,
        DIA_BASE_CMD *bcmd,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    TCAP_Component *cpt  = NULL;
    ITS_OCTET invkId = 0;
    TransatelCAPRoTransactionContext* userData = NULL;


    ret.dir = IWF_RD_TCAP;
    try
    {
        diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
        DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
        userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
        if (!cmd->isRequest())
        {
            // Request message
            // TODO return respective Application Context for each request
            switch(code)
            {
                case DIA_CMD_CC:
                    {
                        // Failure check is performed before decoding. Error
                        // messges maynot contain mandatory AVPs
                        IwfDccaSessionCtxt::DccaState dccaState = userData->GetDccaContext().GetState();
                        if (!ctxt->IsCCFHActionTaken() && (dccaState != IwfDccaSessionCtxt::DccaIdle) &&
                                !ctxt->IsFlowFailed() &&
                                (m_dccaHandler.IsFailureCondition(userData->GetDccaContext(), bcmd)))
                        {
                            UpdateCCAResultCodeForCDR(cmd,userData);
                            IwfDcca::FailureAction action;
                            ctxt->SetFlowFailure(true);
                            action = m_dccaHandler.HandleFailure(userData->GetDccaContext(), outCmd);
                            if (action == IwfDcca::FA_Retry)
                            {
                                DLOG_DEBUG("DCCA failure msg - Retry <%s> again",
                                        outCmd->getSessionId()->value().c_str());
                                ret.action = IWF_RA_CONSUME_AND_RETRY;
                                //Setting the Failedover reason to be logged in CDR
                                int resultCode = bcmd->getResultCode()->value();
                                if (resultCode == ITS_DIA_TOO_BUSY)
                                {
                                    userData->SetCcfhFailedoverReason(CDR_TOO_BUSY);
                                    DLOG_DEBUG("Setting Failedover Reason to CDR_TOO_BUSY");
                                }
                                if (resultCode == ITS_DIA_UNABLE_TO_DELIVER)
                                {
                                    userData->SetCcfhFailedoverReason(CDR_UNABLED_TO_DELIVER);
                                    DLOG_DEBUG("Setting Failedover Reason to CDR_UNABLE_TO_DELIVER");
                                }
                                return rc;
                            }
                            // Action may be Terminate and continue. Continue not handled
                            ret.action = IWF_RA_CONSUME;
                            TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(bcmd->getSessionId()->value(), ctxt);
                            DLOG_DEBUG("DCCA failure msg terminate for <%s>",
                                    bcmd->getSessionId()->value().c_str());
                            if( m_config.GetCdrConfig() != DISABLE_ALL_CALLS )
                            {
                                if(!userData->IsFailedCDRLogged())
                                {
                                    LogCDRData(ctxt, FAILED_3XXX_CCA_T);
                                    userData->SetFailedCDRLogged(true);
                                }
                            }
                            ctxt->SetMarkForRollback(false);
                        }

                        Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
                        unsigned int ccReqType = cca.getCCRequestType().value();
                        if ( userData->GetLastSentCCRequestType() == ccReqType || userData->IsCCRTBuiltForInvalidCCAI())
                        {
                            userData->SetCCRTBuiltForInvalidCCAI(false);
                            if ( cca.getCCRequestType().value() == Ro_TSL::CCRequestType::TERMINATION_REQUEST )
                            {
                                if(cca.getResultCode().value() != ITS_DIA_SUCCESS)
                                {
                                    userData->SetCurrentCCATResultCode(cca.getResultCode().value());
                                    /* update the dccaCtxt and clear transaction
                                     * only for CCA-T  for other casese it is update
                                     * in the BuildMultiTcapMsg */
                                    m_dccaHandler.HandleResponse(userData->GetDccaContext(),
                                            static_cast<diameter::base::BaseGenericCommand*>(cmd));

                                    if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                                            m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS)
                                    {
                                        CheckAndLogCDRForCCATerminate(ctxt, &cca);
                                    }

                                    LogRoTslDiaMsg(cca);
                                    ret.action = IWF_RA_CONSUME;
                                    if(userData->IsCurrentReceivedTcapContinue())
                                    {
                                        DLOG_DEBUG("[Ro_TSL::CreditControlAnswer-Terminate] -> [CAP::ReleaseCall]");
                                        HandleCCATerminateErrorConditions(ctxt, &cca, cpt,outCmd, ret);
                                        if ( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_REL_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ret.action = IWF_RA_FORWARD;
                                            out->BuildTcapCptList(*cpt);
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                            userData->SetCapReleaseSent(true);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP Release");
                                            ret.action = IWF_RA_ERROR;
                                        }
                                    }
                                    else
                                    {
                                        DLOG_DEBUG("Received ERB/ACR in Tcap_End dialogue not need to send Release");
                                        ret.action = IWF_RA_CONSUME;
                                    }
                                    std::string rlsStr = cca.getSessionId().value();
                                    ITS_UINT sIdx =  cca.getSessionIndex();
                                    TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
                                    ReleaseSession(rlsStr, sIdx);
                                    break;
                                }
                                if(!userData->GetBcsmEventMO() && (false == userData->GetTriggerFollowOnSession()))
                                {
                                    userData->SetCurrentCCATResultCode(cca.getResultCode().value());

                                    if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                                            m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS)
                                    {
                                        CheckAndLogCDRForCCATerminate(ctxt, &cca);
                                    }

                                    LogRoTslDiaMsg(cca);
                                    DLOG_DEBUG("[Ro_TSL::CreditControlAnswer-Terminate] -> [CAP::ReleaseCall]");
                                    userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                                    rc = BuildRelease(ctxt,&cca,cpt,userData->GetReleaseCause());
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_REL_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        ret.action = IWF_RA_FORWARD;
                                        out->BuildTcapCptList(*cpt);
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        userData->SetCapReleaseSent(true);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        out->ClearTcapCptList();
                                    }
                                    if( cpt != NULL)
                                    {
                                        delete cpt;
                                        cpt = NULL;
                                    }
                                    userData->SetTriggerFollowOnSession(true);
                                }
                                else
                                {
                                    userData->SetCurrentCCATResultCode(cca.getResultCode().value());
                                    /* update the dccaCtxt and clear transaction
                                     * only for CCA-T  for other casese it is update
                                     * in the BuildMultiTcapMsg */
                                    m_dccaHandler.HandleResponse(userData->GetDccaContext(),
                                            static_cast<diameter::base::BaseGenericCommand*>(cmd));

                                    if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                                            m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS)
                                    {
                                        CheckAndLogCDRForCCATerminate(ctxt, &cca);
                                    }

                                    LogRoTslDiaMsg(cca);
                                    ret.action = IWF_RA_CONSUME;
                                    if(userData->IsCurrentReceivedTcapContinue() && !userData->IsCapReleaseSent())
                                    {
                                        DLOG_DEBUG("[Ro_TSL::CreditControlAnswer-Terminate] -> [CAP::ReleaseCall]");
                                        BuildRelease(ctxt, &cca , cpt, userData->GetReleaseCause());
                                        if ( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_REL_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ret.action = IWF_RA_FORWARD;
                                            out->BuildTcapCptList(*cpt);
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                            userData->SetCapReleaseSent(true);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP Release");
                                            ret.action = IWF_RA_ERROR;
                                        }
                                    }
                                    else
                                    {
                                        DLOG_DEBUG("Release already sent or Received ERB/ACR in Tcap_End dialogue not need to send Release");
                                        ret.action = IWF_RA_CONSUME;
                                    }
                                }
                                std::string rlsStr = cca.getSessionId().value();
                                ITS_UINT sIdx =  cca.getSessionIndex();
                                TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
                                ReleaseSession(rlsStr, sIdx);
                            }
                            else if (cca.getCCRequestType().value() == Ro_TSL::CCRequestType::INITIAL_REQUEST )
                            {
                                if(userData->IsIDPSMSReceived())
                                {
                                    if(userData->GetCAPControlMode() == TransCustomAvp::CAPControlMode::NO_CONTROL)
                                    {
                                        rc = ConstructCptInTCEnd(ctxt,cca,out);
                                        if (ITS_SUCCESS == rc)
                                        {
                                            ret.action = IWF_RA_FORWARD;
                                            ret.isReleaseEnd = false;
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build TCAP Component");
                                            out->ClearTcapCptList();
                                            ret.action = IWF_RA_ERROR;
                                        }
                                    }
                                    else
                                    {
                                        DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ReleaseSMSArg]");
                                        rc = BuildReleaseSMS(ctxt,&cca,cpt, userData->GetReleaseCause());
                                        //Setting CCReq sent as CCR-T
                                        if ( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ret.action = IWF_RA_FORWARD;
                                            out->BuildTcapCptList(*cpt);
                                            ret.isReleaseEnd = false;
                                            userData->SetCapReleaseSent(true);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP Release for CCA-U");
                                            ret.action = IWF_RA_ERROR;
                                            out->ClearTcapCptList();
                                        }
                                        if( cpt != NULL)
                                        {
                                            delete cpt;
                                            cpt = NULL;
                                        }
                                    }
                                    ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                    userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                                }
                                else
                                {
                                    rc = HandleBuildReleaseConditions(ctxt, cca);
                                    if(rc != ITS_SUCCESS)
                                    {
                                        DLOG_DEBUG("[Ro_TSL::CreditControlAnswer-Intial] -> [CAP::ReleaseCall]");
                                        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                                        rc = BuildRelease(ctxt,&cca,cpt,userData->GetReleaseCause());
                                        if ( cpt != NULL )
                                        {
                                            UPDATE_SSG_STATS_REL_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ret.action = IWF_RA_FORWARD;
                                            out->BuildTcapCptList(*cpt);
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                            userData->SetCapReleaseSent(true);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build CAP Release");
                                            ret.action = IWF_RA_ERROR;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                            out->ClearTcapCptList();
                                        }
                                        if( cpt != NULL)
                                        {
                                            delete cpt;
                                            cpt = NULL;
                                        }
                                    }
                                    else if(userData->GetCAPControlMode() == TransCustomAvp::CAPControlMode::NO_CONTROL)
                                    {
                                        rc = ConstructCptInTCEnd(ctxt,cca,out);
                                        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                                        if (ITS_SUCCESS == rc)
                                        {
                                            ret.action = IWF_RA_FORWARD;
                                            ret.isReleaseEnd = false;
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Failed to build TCAP Component");
                                            out->ClearTcapCptList();
                                            ret.action = IWF_RA_ERROR;
                                        }
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                    }
                                }

                            }
                            else if (cca.getCCRequestType().value() == Ro_TSL::CCRequestType::UPDATE_REQUEST )
                            {
                                userData->ClearUpdateTriggerTimeStamp();
                                if( userData->GetCurrentCCAUResultCode() != ITS_DIA_SUCCESS ||
                                        (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) ||
                                        (CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS))
                                {
                                    DLOG_DEBUG("[Ro_TSL::CreditControlAnswer-Update] -> [CAP::ReleaseCall]");
                                    rc = BuildRelease(ctxt,&cca,cpt,userData->GetReleaseCause());
                                    userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_REL_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);
                                        ret.action = IWF_RA_FORWARD;
                                        out->BuildTcapCptList(*cpt);
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        userData->SetCapReleaseSent(true);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        out->ClearTcapCptList();
                                    }
                                    if( cpt != NULL)
                                    {
                                        delete cpt;
                                        cpt = NULL;
                                    }
                                }
                                else
                                {
                                    /* Incase if the CCA-U is success and still
                                     * clear the m_dccaCtxt and clear the
                                     * trasaction other wise its not required */
                                    m_dccaHandler.HandleResponse(userData->GetDccaContext(),
                                            static_cast<diameter::base::BaseGenericCommand*>(cmd));
                                    DLOG_DEBUG("recieved success CCA-U updating the DccaCtxt");
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
                        DLOG_ERROR("Ro_TSL::Unhandled diameter Answer message");
                        ret.action = IWF_RA_ERROR;
                        rc = !ITS_SUCCESS;
                    }
            }
        }
        else
        {
            /* Building Release in case of ASR received to IWF */
            if((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_AS)
            {
                if (!userData->IsCapReleaseSent())
                {
                    if (userData->IsIDPReceived())
                    {
                        /* Setting the TotalUsedTime in userData to send in CCR-Terminate*/
                        uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                        userData->SetUSUCCTime(totalUsedSeconds);
                        DLOG_DEBUG("Building Release in TC_End for ASR received");
                        rc = BuildRelease(ctxt,NULL, cpt, userData->GetReleaseCause());
                        if ( cpt != NULL )
                        {
                            UPDATE_SSG_STATS_REL_ARG_SENT;
                            invkId = ctxt->GetInvkId();
                            cpt->SetInvokeID(++invkId);
                            ctxt->SetInvkId(invkId);
                            ret.action = IWF_RA_FORWARD;
                            out->BuildTcapCptList(*cpt);
                            ret.isReleaseEnd = false;
                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                            userData->SetCapReleaseSent(true);
                        }
                        else
                        {
                            DLOG_ERROR("Failed to build CAP Release");
                            ret.action = IWF_RA_ERROR;
                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                            out->ClearTcapCptList();
                        }
                        if( cpt != NULL)
                        {
                            delete cpt;
                            cpt = NULL;
                        }
                    }
                    else if (userData->IsIDPSMSReceived())
                    {
                        DLOG_DEBUG("Building ReleaseSMS in TC_End for ASR received ");
                        rc = BuildReleaseSMS(ctxt,NULL,cpt, userData->GetReleaseCause());
                        if ( cpt != NULL )
                        {
                            UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                            invkId = ctxt->GetInvkId();
                            cpt->SetInvokeID(++invkId);
                            ctxt->SetInvkId(invkId);
                            ret.action = IWF_RA_FORWARD;
                            out->BuildTcapCptList(*cpt);
                            ret.isReleaseEnd = false;
                            userData->SetCapReleaseSent(true);
                        }
                        else
                        {
                            DLOG_ERROR("Failed to build CAP ReleaseSMS");
                            ret.action = IWF_RA_ERROR;
                            out->ClearTcapCptList();
                        }
                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                    }
                }
                else
                {
                    DLOG_WARNING("Release is already sent for this session. hence consume");
                    ret.action = IWF_RA_CONSUME;
                }
            }
            else
            {
                DLOG_DEBUG("Received Request Message");
                rc = !ITS_SUCCESS;
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
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for sessionId %s is %d", e.sessionId(), e.errcode());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
        if (userData->IsIDPReceived())
        {
            rc = BuildRelease(ctxt,NULL,cpt,userData->GetReleaseCause());
            if ( cpt != NULL )
            {
                UPDATE_SSG_STATS_REL_ARG_SENT;
                invkId = ctxt->GetInvkId();
                cpt->SetInvokeID(++invkId);
                ctxt->SetInvkId(invkId);
                ret.action = IWF_RA_FORWARD;
                out->BuildTcapCptList(*cpt);
                ret.isReleaseEnd = false;
                ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                userData->SetCapReleaseSent(true);
            }
            else
            {
                DLOG_ERROR("Failed to build CAP Release");
                ret.action = IWF_RA_ERROR;
                ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                out->ClearTcapCptList();
            }
        }
        else if (userData->IsIDPSMSReceived())
        {
            DLOG_DEBUG("Build CAP:ReleaseSMSArg");
            rc = BuildReleaseSMS(ctxt,NULL,cpt, userData->GetReleaseCause());
            if ( cpt != NULL )
            {
                UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                invkId = ctxt->GetInvkId();
                cpt->SetInvokeID(++invkId);
                ctxt->SetInvkId(invkId);
                ret.action = IWF_RA_FORWARD;
                out->BuildTcapCptList(*cpt);
                ret.isReleaseEnd = false;
                userData->SetCapReleaseSent(true);
            }
            else
            {
                DLOG_ERROR("Failed to build CAP ReleaseSMS");
                ret.action = IWF_RA_ERROR;
                out->ClearTcapCptList();
            }
            ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
        }
        if( cpt != NULL)
        {
            delete cpt;
            cpt = NULL;
        }
        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
    }
    catch(std::exception& e)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("### Exception on decode %s ###", e.what());
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

int TransatelCAPToRoHandler::BuildMultiTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,
        TcapCptList *out,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ITS_ByteArray buf;
    ITS_OCTET invkId = 0;

    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildMultiTCAPMsg -- Entry");

    DIA_BASE_CMD *bcmd = NULL;
    diameter::Command* cmd = NULL;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
        //Replicate the DCCA Context Details
        userData->ReplicateDccaCtxt();
    try
    {
        bcmd = ctxt->GetCurrRcvdDiaMsg();
        cmd =(const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();

        if((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_CC)
        {
            TCAP_Component *cpt  = NULL;

            // Error bit check is not done. It was observed that TSL test cases
            // was not setting Ebit but Result code with error was set. Not
            // performing Ebit check, to make their tests pass
            if (m_dccaHandler.IsFailureCondition(userData->GetDccaContext(), bcmd))
            {
                UpdateCCAResultCodeForCDR(cmd,userData);
                IwfDcca::FailureAction action;
                IwfDccaSessionCtxt::DccaState curState =  userData->GetDccaContext().GetState();
                ctxt->SetFlowFailure(true);
                action = m_dccaHandler.HandleFailure(userData->GetDccaContext(), outCmd);
                if (action == IwfDcca::FA_Retry)
                {
                    DLOG_DEBUG("DCCA Failure message - retry <%s>",
                            outCmd->getSessionId()->value().c_str());
                    ret.action = IWF_RA_CONSUME_AND_RETRY;
                    //Setting the Failedover reason to be logged in CDR
                    int resultCode = bcmd->getResultCode()->value();
                    if (resultCode == ITS_DIA_TOO_BUSY)
                    {
                        userData->SetCcfhFailedoverReason(CDR_TOO_BUSY);
                        //DLOG_DEBUG("Setting Failedover Reason to CDR_TOO_BUSY");
                    }
                    if (resultCode == ITS_DIA_UNABLE_TO_DELIVER)
                    {
                        userData->SetCcfhFailedoverReason(CDR_UNABLED_TO_DELIVER);
                        //DLOG_DEBUG("Setting Failedover Reason to CDR_UNABLE_TO_DELIVER");
                    }
                    return rc;
                }

                if( m_config.GetCdrConfig() != DISABLE_ALL_CALLS )
                {
                    CdrFailureCode failureCause;
                    if (userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::INITIAL_REQUEST)
                    {
                        failureCause = FAILED_3XXX_CCA_I;
                    }
                    else if (userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::UPDATE_REQUEST)
                    {
                        failureCause = FAILED_3XXX_CCA_U;
                    }
                    else
                    {
                        failureCause = FAILED_3XXX_CCA_T;
                    }
                    LogCDRData(ctxt, failureCause);
                    userData->SetFailedCDRLogged(true);
                }

                if (curState == IwfDccaSessionCtxt::DccaPendingI)
                {
                    // Action may be Terminate and continue. Continue not handled
                    ret.action = IWF_RA_FORWARD;
                    ret.isReleaseEnd = true;
                }
                else if (userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::TERMINATION_REQUEST)
                {
                    out->ClearTcapCptList();
                    if (userData->GetCAPControlMode() == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                    {
                        //if control mode is LOCAL, stop the Fake ACH timer, set the curr USU as elapsed time
                        ETimerType timerType = ETimerType::FAKE_ACH_TIMER;
                        STimerInfo fsmTimerData;
                        ctxt->GetTimerInfo(timerType, fsmTimerData);

                        IwfTimer timerObj;
                        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                        {
                            //DLOG_DEBUG("[CAP:EventReportArg] TimerType : FAKE_ACH_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
                            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                        }
                        else
                        {
                            DLOG_ERROR("[CAP:EventReportArg] Failed to stop TimerType : FAKE_ACH_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
                        }
                    }
                    Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
                    std::string rlsStr = cca.getSessionId().value();
                    ITS_UINT sIdx =  cca.getSessionIndex();
                    TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
                    ReleaseSession(rlsStr, sIdx);
                    string strSessId = ctxt->GetDiaSessionId();
                    strSessId.clear();
                    ctxt->SetDiaSessionId(strSessId);
                    ret.action = IWF_RA_FORWARD;
                    ret.isReleaseEnd = true;
                    //DLOG_DEBUG("First Session %s released",rlsStr.c_str());
                }
                else
                {
                    ret.isReleaseEnd = false;
                    BuildCCRTerminateForIDP(ctxt,
                            diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE,
                            outCmd, userData->GetUSUCCTime());
                    ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                    ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                    out->ClearTcapCptList();
                }

                DLOG_DEBUG("DCCA Failure message - terminate <%s>",
                        bcmd->getSessionId()->value().c_str());
                
                return rc;
            }

            Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
            LogRoTslDiaMsg(cca);

            unsigned int resultCode = cca.getResultCode().value();
            unsigned int ccaRequestType = cca.getCCRequestType().value();

            if( userData->GetLastSentCCRequestType() == ccaRequestType )
            {
                //DLOG_DEBUG("received CC-Request-Type matches with sent CC-Request-Type process further.");

                m_dccaHandler.HandleResponse(userData->GetDccaContext(),
                        static_cast<diameter::base::BaseGenericCommand*>(cmd));
                userData->ReplicateDccaCtxt();

                switch(ccaRequestType)
                {
                    case Ro_TSL::CCRequestType::INITIAL_REQUEST:
                        {
                            CheckIsCAPReleaseCausePresent(ctxt, &cca);

                            bool buildFailed = false;
                            /* set the received result Code for further processing */
                            userData->SetCurrentCCAIResultCode(resultCode);
                            if(userData->IsIDPSMSReceived())
                            {
                                if(resultCode == ITS_DIA_SUCCESS)
                                {
                                    if( (ITS_SUCCESS != CheckSCPAction(&cca, userData)) ||
                                            (ITS_SUCCESS != CheckControlMode(&cca, userData)) )
                                    {
                                        DLOG_ERROR("Validation failed for SCP-Action/Control-Mode avp's sending releaseSMS & CCR-T");
                                        ret.isReleaseEnd = true;
                                        userData->SetReleaseCause(m_config.ReleaseSmsCauseCode());

                                        BuildCCRTerminateForIDPSMS(ctxt,((diameter::base::TerminationCause::Value)userData->GetTerminationCause()), outCmd);
                                        userData->SetCCRTBuiltForInvalidCCAI(true);
                                        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                        out->ClearTcapCptList();
                                        CheckMSCCGSUServiceSpecificUnits(&cca, userData);
                                        break;
                                    }
                                    //Check the allocated GSU unit value.
                                    if(ITS_SUCCESS != CheckMSCCGSUServiceSpecificUnits(&cca, userData))
                                    {
                                        DLOG_ERROR("CAPToRoHandler::BuildMultiTCAPMsg validation falied for GSU ");
                                        ret.isReleaseEnd = true;
                                        userData->SetReleaseCause(m_config.ReleaseSmsCauseCode());
                                        BuildCCRTerminateForIDPSMS(ctxt, ((diameter::base::TerminationCause::Value)DIA_TERM_CAUSE_INVALID_GSU_UNIT), outCmd);
                                        userData->SetCCRTBuiltForInvalidCCAI(true);
                                        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                        ret.app_ctxt = cap::EncodeApplicationContext(cap::CAPV3_cap3_sms_AC);
                                        out->ClearTcapCptList();
                                        break;
                                    }

                                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:RequestReportSMSEvent]");
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

                                    //DLOG_DEBUG("[Ro:CreditControlAnswer-Initial] -> [CAP:ContinueSMS]");
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
                                        userData->SetTranslatorState(RRB_SENT);
                                    }
                                }
                                else
                                {
                                    DLOG_INFO("Recevied error answer in CCA-I Result-Code : %d",resultCode);
                                    //CheckAndUpdateReleaseCause(resultCode, userData);
                                    ret.isReleaseEnd = true;
                                    ret.action = IWF_RA_FORWARD;
                                }
                            }
                            else if(userData->IsIDPReceived())
                            {
                                /* Set the flag in userdata if the CCA-I's MSCC-Granted-Service-CCTime is zero which is used in setting termination cause in CCR-T*/
                                if(CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS)
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
                                    TransCustomAvp::SCPAction::Value scpActionVal;
                                    TransCustomAvp::CAPControlMode::Value ctrlModeVal;
                                    if(ITS_SUCCESS != ExtractScpActionData(&cca,userData,scpActionVal) ||
                                            ITS_SUCCESS != ExtractCtrlModeData(&cca,userData,ctrlModeVal))
                                    {
                                        DLOG_ERROR("Validation failed for SCP-Action/Control-Mode avp's sending RelCall & CCR-T");
                                        ret.isReleaseEnd = false;
                                        BuildCCRTerminateForIDP(ctxt,((diameter::base::TerminationCause::Value)userData->GetTerminationCause()), outCmd);
                                        userData->SetCCRTBuiltForInvalidCCAI(true);
                                        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        out->ClearTcapCptList();
                                        break;
                                    }

                                    if (CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS )
                                    {
                                        //Note: Release Cause should be default value if GSU is Invalid
                                        userData->SetReleaseCause(m_config.ReleaseCallCauseCode());

                                        BuildCCRTerminateForIDP(ctxt, ((diameter::base::TerminationCause::Value)DIA_TERM_CAUSE_INVALID_GSU_UNIT)
                                                , outCmd);
                                        userData->SetCCRTBuiltForInvalidCCAI(true);
                                        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        out->ClearTcapCptList();
                                        break;
                                    }
                                    else
                                    {

                                        if(ITS_SUCCESS == CheckMSCCFinalUnitAction(cca))
                                        {
                                            userData->SetIsFinalUnitsReceived(true);

                                        }
                                        int retVal = ExtractAndSetNoAnsTime(userData,cca);

                                        UpdateGSUValues(userData,cca);

                                        retVal = DeduceAndConstructCAMELMsg(ctxt,cca,out);

                                        if(ITS_SUCCESS == retVal)
                                        {
                                            if(ctxt->IsTCAPEnd())
                                            {
                                                BuildCCRTerminateForIDP(ctxt,
                                                        ((diameter::base::TerminationCause::Value)DIA_TERM_CAUSE_NOT_CONTROLLED_CALL), outCmd);
                                                userData->SetCCRTBuiltForInvalidCCAI(true);
                                                ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                                out->ClearTcapCptList();
                                                ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                            }
                                            else
                                            {
                                                ret.action = IWF_RA_FORWARD;
                                                if (userData->IsFollowingOnSet())
                                                {
                                                    userData->SetTranslatorState(IS_FOLLOW_ON);
                                                }
                                                else
                                                {

                                                    userData->SetTranslatorState(RRB_SENT);
                                                }
                                            }
                                            ret.isReleaseEnd = false;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        }
                                        else
                                        {
                                            /* incase if building of any one component failed,clean the out list and
                                             * Send out CCR-T toward OCS*/
                                            diameter::base::TerminationCause::Value cause = diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE;
                                            if(ctxt->GetErrorCode() == TSLConstants::INVALID_CONTROL_MODE_CAPV1)
                                            {
                                                //Note: Release Cause should be default value if Control Mode is Invalid
                                                userData->SetReleaseCause(m_config.ReleaseCallCauseCode());
                                                cause = (diameter::base::TerminationCause::Value )DIA_TERM_CAUSE_INVALID_CONTROL_MODE;
                                            }
                                            BuildCCRTerminateForIDP(ctxt, cause, outCmd);
                                            ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                            out->ClearTcapCptList();
                                            buildFailed = false;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    case Ro_TSL::CCRequestType::UPDATE_REQUEST:
                        {
                            userData->ClearUpdateTriggerTimeStamp();
                            /* set the received result Code for processing ACR*/
                            userData->SetCurrentCCAUResultCode(resultCode);

                            /* Store the CCA-U's MSCC result code */
                            userData->SetCurrentCCAUMsccResultCode(GetMSCCResultCode(&cca));
                            if(ITS_SUCCESS == CheckMSCCFinalUnitAction(cca))
                            {
                                userData->SetIsFinalUnitsReceived(true);

                            }
                            /* Set the flag in userdata if the CCA-U's MSCC-Granted-Service-CCTime is zero which is used in setting termination cause in CCR-T*/
                            if(CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS)
                            {
                                userData->SetCurrentCCAMsccGrantedCCTimeZero(true);
                            }

                            if( (resultCode != ITS_DIA_SUCCESS) ||
                                    (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) )
                            {
                                HandleCCAUpdateErrorConditions(ctxt, &cca, cpt,outCmd, ret);
                            }
                            else
                            {
                                if ( CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS )
                                {
                                    //Note: Release Cause should be default value if GSU is Invalid
                                    userData->SetReleaseCause(m_config.ReleaseCallCauseCode());

                                    BuildCCRTerminateForIDP(ctxt, ((diameter::base::TerminationCause::Value)DIA_TERM_CAUSE_INVALID_GSU_UNIT)
                                            , outCmd, userData->GetUSUCCTime());
                                    ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                                    ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                    out->ClearTcapCptList();
                                    break;
#if 0
                                    BuildRelease(ctxt,&cca,cpt);
                                    if ( cpt != NULL )
                                    {
                                        UPDATE_SSG_STATS_REL_ARG_SENT;
                                        invkId = ctxt->GetInvkId();
                                        cpt->SetInvokeID(++invkId);
                                        ctxt->SetInvkId(invkId);

                                        out->BuildTcapCptList(*cpt);
                                        ret.action = IWF_RA_FORWARD;
                                        ret.isReleaseEnd = false;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                        userData->SetCapReleaseSent(true);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Failed to build CAP Release for CCA-U");
                                        ret.action = IWF_RA_ERROR;
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                    }
#endif
                                }
                                else
                                {
                                    int iMode = userData->GetCAPControlMode();
                                    UpdateGSUValues(userData,cca);
                                    if (iMode == TransCustomAvp::CAPControlMode::REMOTE_CONTROL)
                                    {
                                        //DLOG_DEBUG("[Ro:CreditControlAnswer-Update] -> [CAP:ApplyChargingArg]");
                                        BuildACH(ctxt,&cca,cpt);
                                        if ( cpt != NULL )
                                        {
                                            //DLOG_DEBUG("Mode is REMOTE_CONTROL. Starting ACR Timer");
                                            //Start Fakce-ACH-Timer
                                            StartTimerHandling(ctxt, ETimerType::ACR_TIMER);
                                            UPDATE_SSG_STATS_AC_ARG_SENT;
                                            invkId = ctxt->GetInvkId();
                                            cpt->SetInvokeID(++invkId);
                                            ctxt->SetInvkId(invkId);
                                            ctxt->StoreOutgoingInvokeId(invkId);

                                            out->BuildTcapCptList(*cpt);
                                            ret.action = IWF_RA_FORWARD;
                                            ret.isReleaseEnd = false;
                                            userData->SetTranslatorState(ACH_SENT);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("Unable to build ACH Component for CCA-Update");
                                            ret.action = IWF_RA_ERROR;
                                        }
                                        ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                                    }
                                    else if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                                    {
                                        //DLOG_DEBUG("Mode is LOCAL_CONTROL. Starting Fake ACH Timer");

                                        //Start Fakce-ACH-Timer
                                        StartTimerHandling(ctxt, ETimerType::FAKE_ACH_TIMER);

                                        ret.action = IWF_RA_CONSUME;
                                        ret.isReleaseEnd = false;
                                        userData->SetTranslatorState(FAKE_ACH_SENT);
                                    }
                                }
                                if( cpt != NULL)
                                {
                                    delete cpt;
                                    cpt = NULL;
                                }
                            }
                            break;
                        }
                    case Ro_TSL::CCRequestType::TERMINATION_REQUEST:
                        {
                            /* set the received result Code for further processing */
                            userData->SetCurrentCCATResultCode(resultCode);

                            if ( userData->GetLastSentCCRequestType() == ccaRequestType )
                            {
                                if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                                        m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS)
                                {
                                    CheckAndLogCDRForCCATerminate(ctxt, &cca);
                                }
                                //If LOCAL-CONTROL Stop the Fake-ACH Timer
                                if (userData->GetCAPControlMode() == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                                {
                                    //if control mode is LOCAL, stop the Fake ACH timer, set the curr USU as elapsed time
                                    ETimerType timerType = ETimerType::FAKE_ACH_TIMER;
                                    STimerInfo fsmTimerData;
                                    ctxt->GetTimerInfo(timerType, fsmTimerData);

                                    IwfTimer timerObj;
                                    if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                                    {
                                        //DLOG_DEBUG("[CAP:EventReportArg] TimerType : FAKE_ACH_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
                                        ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                                    }
                                    else
                                    {
                                        DLOG_ERROR("[CAP:EventReportArg] Failed to stop TimerType : FAKE_ACH_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
                                    }
                                }
                                ret.isReleaseEnd = false;
                                std::string rlsStr = cca.getSessionId().value();
                                ITS_UINT sIdx =  cca.getSessionIndex();
                                std::string hostName = cca.getOriginHost().value();
                                std::string realmName = cca.getOriginRealm().value();
                                TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
                                ReleaseSession(rlsStr, sIdx);
                                string strSessId = ctxt->GetDiaSessionId();
                                strSessId.clear();
                                ctxt->SetDiaSessionId(strSessId);
                                //DLOG_DEBUG("First Session %s released",rlsStr.c_str());
                                if (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT ||
                                        userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE)
                                {
                                    //Reset all stored CCTime values, ERBData before establishing second call in Follow-On cases

                                    ResetInitialSessionContext(ctxt);

                                    //Reset DCCA Context to new call, set CLI value for failover
                                    m_dccaHandler.ResetDccaContext(userData->GetDccaContext());

                                    if((!userData->GetBcsmEventMO() && (false == userData->GetTriggerFollowOnSession())) || (ctxt->IsDontTriggerFollowOnForCCAUErrorSet()))
                                    {
                                        ctxt->SetDontTriggerFollowOnForCCAUError(false);
                                        //DLOG_DEBUG("Second session for FOLLOW_ON_CONNECT/FOLLOW_ON_CONTINUE not triggered for MT call or FirstSession CCAU Error case");
                                        if(ctxt->GetTransactionManager()->RemoveDiaSessionTxnEntry(rlsStr) != ITS_SUCCESS)
                                        {
                                            DLOG_ERROR("Deletion of old SessionId : %s failed",rlsStr.c_str());
                                        }
                                        /*else
                                        {
                                            DLOG_DEBUG("Successfully removed old SessionId : %s.",rlsStr.c_str());
                                        }*/

                                        ret.action = IWF_RA_FORWARD;
                                        ret.isReleaseEnd = true;
                                    }
                                    else
                                    {
                                        //DLOG_DEBUG("Creating Second session for FOLLOW_ON_CONNECT/FOLLOW_ON_CONTINUE");
                                        BuildSuccessiveCCRInitial(ctxt, outCmd, hostName, realmName);
                                        if(ctxt->GetTransactionManager()->RemoveDiaSessionTxnEntry(rlsStr) != ITS_SUCCESS)
                                        {
                                            DLOG_ERROR("Deletion of old SessionId : %s entry failed for new SessionId : %s",
                                                    rlsStr.c_str(),ctxt->GetDiaSessionId().c_str());
                                        }
                                        /*else
                                        {
                                            DLOG_DEBUG("Successfully removed old SessionId : %s and updated with new SessionId : %s",
                                                    rlsStr.c_str(),ctxt->GetDiaSessionId().c_str());
                                        }*/
                                        ret.action = IWF_RA_CONSUME_AND_RESPOND;
                                        ret.dir = IWF_RD_DIA;
                                        /* Reseting the ERB Data after populating it in CCR-I for second session*/
                                        userData->ClearERBData();
                                        userData->SetFirstERBReceived(false);
                                        userData->SetTranslatorState(FOLLOW_ON);
                                    }
                                }
                                else
                                {
                                    ret.action = IWF_RA_CONSUME;
                                }
                            }
                            else
                            {
                                DLOG_ERROR("Last Sent CCRequestType does not match with recieved msg, hence dropping the message");
                                DLOG_ERROR("Received CC-RequestType : %d, Stored CC-RequestType : %d",
                                        userData->GetLastSentCCRequestType(),
                                        ccaRequestType);
                                ret.action = IWF_RA_CONSUME;
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
                DLOG_ERROR("Answer message CC-Request-Type doesn't match with request" \
                        "message CC-Request-Type. Dropping the message");
                DLOG_ERROR("Received CC-RequestType : %d, Stored CC-RequestType : %d",
                        userData->GetLastSentCCRequestType(),
                        ccaRequestType);
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
            LogRoTslDiaMsg(rar);
            DLOG_DEBUG("[Ro:ReAuthRequest]");
            ret.action = IWF_RA_RESPOND_ONLY;
        }
        else if ((DiaCommandCode)cmd->getCommandCode() == DIA_CMD_AS)
        {
            diameter::base::AbortSessionRequest asr(cmd->getImpl());
            LogRoTslDiaMsg(asr);

                /* Setting the return action and isASRReceived flag
                 * to handle ASR flow in transaction manager */
                ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                ret.isASRReceived  = true;
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
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for sessionId %s is %d", e.sessionId(), e.errcode());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
        unsigned resultCode = 0;
        cmd->getAvpValue(RESULT_AVP_CODE, &resultCode, diameter::Unsigned32Type);
        if ( ((resultCode == ITS_DIA_SUCCESS) &&
                    (userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::INITIAL_REQUEST )) ||
                (userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::UPDATE_REQUEST) )
        {
            if(userData->IsIDPReceived())
            {
                uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                userData->SetUSUCCTime(totalUsedSeconds);
                BuildCCRTerminateForIDP(ctxt,diameter::base::TerminationCause::DIAMETER_BAD_ANSWER, outCmd,
                        userData->GetUSUCCTime());
            }
            else if(userData->IsIDPSMSReceived())
            {
                BuildCCRTerminateForIDPSMS(ctxt, diameter::base::TerminationCause::DIAMETER_BAD_ANSWER, outCmd);
            }
            ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
        }
        else
        {
            ret.action = IWF_RA_FORWARD;
            ret.isReleaseEnd = true;
        }
        return rc;
    }
    catch(...)
    {
        ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
        DLOG_ERROR("Unknown exception thrown");
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_DIA;
    }

    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildMultiTCAPMsg -- Exit");
    return rc;
}

int TransatelCAPToRoHandler::BuildDiaMsg(IwfFsm *ctxt, TCAP_Component *cpt, DIA_BASE_CMD *&cmd,
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
        TransatelCAPRoTransactionContext* userData = NULL;


        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if(inTcapDlg->GetDialogueType() == TCPPT_TC_P_ABORT
                || inTcapDlg->GetDialogueType() == TCPPT_TC_U_ABORT)
        {
            ETimerType timerType = ETimerType::ACR_TIMER;
            STimerInfo fsmTimerData;
            ctxt->GetTimerInfo(timerType, fsmTimerData);

            IwfTimer timerObj;
            if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
            {
                //DLOG_DEBUG("[CAP:EventReportSMSArg] TimerType : ACR_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
                ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
            }
            else
            {
                DLOG_ERROR("[CAP:EventReportSMSArg] Failed to stop TimerType : ACR_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
            }

            userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
            TCAP_Abort *abrtDlg = (TCAP_Abort*)inTcapDlg;
            if(NULL != userData)
            {
                ITS_OCTET abrtReasonVal = abrtDlg->GetAbortReason();
                if(userData->IsIDPReceived())
                {

                    IDPToCCRIData idpStoredData;
                    idpStoredData.CopyFrom(userData->GetIDPToCCRIData());
                    idpStoredData.set_tcap_error_cause((unsigned int) abrtReasonVal);

                    DLOG_DEBUG("BuildDiaMsg :: Extracted AbortReason value : %u, Value set in RoTransContext : %u.",
                            abrtReasonVal,
                            idpStoredData.tcap_error_cause());
                    userData->SetIDPToCCRIData(idpStoredData);

                    uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                    userData->SetUSUCCTime(totalUsedSeconds);
                    BuildCCRTerminateForIDP(ctxt,
                            (diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
                }
                else if(userData->IsIDPSMSReceived())
                {
                    StoredIDPSMSToCCRIData idpSMSStoredData;
                    idpSMSStoredData.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
                    idpSMSStoredData.set_cap_tcap_error_cause((unsigned int) abrtReasonVal);

                    DLOG_DEBUG("BuildDiaMsg :: Extracted AbortReason value : %u, Value set in RoTransContext : %u.",
                            abrtReasonVal,
                            idpSMSStoredData.cap_tcap_error_cause());
                    userData->SetStoredIDPSMSToCCRIData(idpSMSStoredData);
                    BuildCCRTerminateForIDPSMS(ctxt, diameter::base::TerminationCause::DIAMETER_LOGOUT, cmd);
                }
                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
            }
            else
            {
                rc = !ITS_SUCCESS;
            }
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
                    int result = 0 ;
                    switch (opCode)
                    {
                        case cap::OP_initialDP:
                            {
                                if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                                {
                                    DLOG_WARNING("InitialDP came in CONTINUE/END Dialog .. Consuming it !! ");
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_CONSUME;
                                    break;
                                }
                                ProcessInitialDP(ctxt);
                                userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
                                switch(userData->GetRecvAppCtxt())
                                {
                                    case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
                                        {
                                            cap_v1::InitialDPArg idp;
                                            Octets octs(buf);
                                            idp.Decode(octs);
                                            LogCAPTslAsnObj(idp);
                                            //DLOG_DEBUG("[CAP:InitialDPArgV1] - [Ro_TSL::CreditControlRequest]");
                                            result = InitialDPToCCRI(ctxt, idp,ccr);
                                            if(ITS_SUCCESS == result)
                                                SetDestinationHostAndRealm(ctxt,userData->GetIDPToCCRIData().imsi().c_str(),
                                                        idp.GetServiceKey().GetValue(), ccr, true);
                                        }
                                        break;
                                    case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
                                        {
                                            cap_v2::InitialDPArg idp;
                                            Octets octs(buf);
                                            idp.Decode(octs);
                                            LogCAPTslAsnObj(idp);
                                            //DLOG_DEBUG("[CAP:InitialDPArgV2] - [Ro_TSL::CreditControlRequest]");
                                            result = InitialDPToCCRI(ctxt, idp, ccr);
                                            if(ITS_SUCCESS == result)
                                            {
                                                PopulateV2SpecificIE(ctxt,idp, ccr);
                                                SetDestinationHostAndRealm(ctxt, userData->GetIDPToCCRIData().imsi().c_str(),
                                                        idp.GetServiceKey().GetValue(), ccr, true);
                                            }
                                        }
                                        break;
                                    case cap::CAPV3_cap3_sms_AC :
                                        {
                                            DLOG_ERROR("BuildDiaMsg: CAPV3_cap3_sms_AC set in userData : %d.",userData->GetRecvAppCtxt());
                                            result = !ITS_SUCCESS;
                                        }
                                        break;

                                    default :
                                        {
                                            DLOG_ERROR("BuildDiaMsg: Unknown CAP ApplContext set in userData : %d.",userData->GetRecvAppCtxt());
                                            result = !ITS_SUCCESS;
                                        }
                                        break;

                                }

                                UPDATE_SSG_STATS_IDP_ARG_RECVD;
                                if(result != ITS_SUCCESS)
                                {
                                    delete ccr;
                                    ccr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                SetDefaultAVPs(ctxt, ccr, userData->GetIDPToCCRIData().imsi().c_str());
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);

                                /* Storing the last Sent CC-Request-Type to be used for
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);

                                m_dccaHandler.HandleRequest(userData->GetDccaContext(),
                                        cmd, Ro_TSL::CCRequestType::INITIAL_REQUEST);

                                ReleaseInvokeId(ctxt, cpt->GetInvokeID());
                                LogRoTslDiaMsg(*ccr, false);
                                break;
                            }

                        case cap::OP_initialDPSMS:
                            {
                                if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                                {
                                    DLOG_WARNING("InitialDPSMS came in CONTINUE/END Dialog .. Consuming it !! ");
                                    ret.dir = IWF_RD_DIA;
                                    ret.action = IWF_RA_CONSUME;
                                    break;
                                }

                                Ro_TSL::CreditControlRequest *ccr =
                                    new Ro_TSL::CreditControlRequest();
                                InitialDPSMSArg idps;
                                Octets octs(buf);
                                idps.Decode(octs);

                                LogCAPTslAsnObj(idps);
                                UPDATE_SSG_STATS_IDP_SMS_ARG_RECVD;
                                //DLOG_DEBUG("[CAP:InitialDPSMSArg] - [Ro_TSL::CreditControlRequest (I)]");

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

                                userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                SetDefaultAVPs(ctxt, ccr, userData->GetStoredIDPSMSToCCRIData().cap_imsi().c_str());
                                result = SetDestinationHostAndRealm(ctxt, userData->GetStoredIDPSMSToCCRIData().cap_imsi(), idps.GetServiceKey().GetValue(), ccr, true);
                                if(result != ITS_SUCCESS)
                                {
                                    delete ccr;
                                    ccr = NULL;
                                    ret.action = IWF_RA_ERROR;
                                    ret.dir = IWF_RD_TCAP;
                                    rc = !ITS_SUCCESS;
                                    break;
                                }
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);
                                /* Storing the last Sent CC-Request-Type to be used for
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);

                                m_dccaHandler.HandleRequest(userData->GetDccaContext(),
                                        cmd, Ro_TSL::CCRequestType::INITIAL_REQUEST);

                                ReleaseInvokeId(ctxt, cpt->GetInvokeID());
                                LogRoTslDiaMsg(*ccr, false);
                                break;
                            }

                        case cap::OP_eventReportBCSM:
                            {

                                userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                /* Setting the transaltor State whenever ERB(Answer/Disconnnect)
                                 * is received and also clear any previously set Disconnect trigger
                                 * timeStamps */
                                userData->SetTranslatorState(ERB_RCVD);
                                userData->ClearDisconTriggerTimeStamp();
                                UPDATE_SSG_STATS_ERBCSM_ARG_RECVD;

                                switch(userData->GetRecvAppCtxt())
                                {
                                    case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
                                        {
                                            cap_v1::EventReportBCSMArg erbV1;
                                            Octets octs(buf);
                                            erbV1.Decode(octs);
                                            LogCAPTslAsnObj(erbV1);
                                            cap_v1::EventTypeBCSM eventBcsm = erbV1.GetEventTypeBCSM();
                                            /* Update the DisconTriggerTimeStamp only if it is not OAnswer/TAnswer*/
                                            CheckAndUpdateDisconTriggerTimeStamp(ctxt, eventBcsm);

                                            rc = ValidateRecvERBV1Event(erbV1,ctxt,cmd);
                                            if(IWF_RA_CONSUME == rc)
                                            {
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_CONSUME;
                                                rc = ITS_SUCCESS;
                                                break;
                                            }
                                            else if(IWF_RA_RESPOND_AND_FORWARD == rc)
                                            {
                                                rc = ITS_SUCCESS;
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                                ret.isReleaseEnd = false;
                                                break;
                                            }
                                            else if(IWF_RA_FORWARD == rc)
                                            {
                                                rc = ITS_SUCCESS;
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_FORWARD;
                                                ret.isReleaseEnd = false;
                                                break;

                                            }
                                            else if(TSLConstants::CONTINUE_CALL_RET == rc)
                                                rc = BuildCCRFromIncomingERBEvent(ctxt, erbV1, eventBcsm, cmd, ret);
                                            if(rc != ITS_SUCCESS)
                                            {
                                                ret.action = IWF_RA_ERROR;
                                                ret.dir = IWF_RD_TCAP;
                                                rc = !ITS_SUCCESS;
                                                break;
                                            }
                                        }
                                        break;
                                    case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
                                        {
                                            cap_v2::EventReportBCSMArg erbV2;
                                            Octets octs(buf);
                                            erbV2.Decode(octs);
                                            LogCAPTslAsnObj(erbV2);
                                            cap_v2::EventTypeBCSM eventBcsm = erbV2.GetEventTypeBCSM();
                                            /* Update the DisconTriggerTimeStamp only if it is not OAnswer/TAnswer*/
                                            CheckAndUpdateDisconTriggerTimeStamp(ctxt, eventBcsm);
                                            rc = ValidateRecvERBEvent(erbV2,ctxt,cmd);
                                            if(IWF_RA_CONSUME == rc)
                                            {
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_CONSUME;
                                                rc = ITS_SUCCESS;
                                                break;
                                            }
                                            else if(IWF_RA_RESPOND_AND_FORWARD == rc)
                                            {
                                                rc = ITS_SUCCESS;
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                                ret.isReleaseEnd = false;
                                                break;
                                            }
                                            else if(IWF_RA_FORWARD == rc)
                                            {
                                                rc = ITS_SUCCESS;
                                                ret.dir = IWF_RD_DIA;
                                                ret.action = IWF_RA_FORWARD;
                                                ret.isReleaseEnd = false;
                                                break;

                                            }
                                            else if(TSLConstants::CONTINUE_CALL_RET == rc)
                                                rc = BuildCCRFromIncomingERBEvent(ctxt, erbV2, eventBcsm, cmd, ret);
                                            if(rc != ITS_SUCCESS)
                                            {
                                                ret.action = IWF_RA_ERROR;
                                                ret.dir = IWF_RD_TCAP;
                                                rc = !ITS_SUCCESS;
                                                break;
                                            }
                                        }
                                        break;
                                    case cap::CAPV3_cap3_sms_AC :
                                        {
                                            DLOG_ERROR("BuildDiaMsg: CAPV3_cap3_sms_AC set in userData : %d.",userData->GetRecvAppCtxt());
                                            result = !ITS_SUCCESS;
                                        }
                                        break;

                                    default :
                                        {
                                            DLOG_ERROR("BuildDiaMsg: Unknown CAP ApplContext set in userData : %d.",userData->GetRecvAppCtxt());
                                            result = !ITS_SUCCESS;
                                        }
                                        break;

                                }
                                ReleaseInvokeId(ctxt, cpt->GetInvokeID());
                                ReleaseStoredInvokeIds(ctxt);
                                break;
                            }

                        case cap::OP_applyChargingReport:
                            {
                                Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
                                cap_v3::CallResult cr;
                                Octets octs(buf);
                                cr.Decode(octs);

                                LogCAPTslAsnObj(cr);
                                UPDATE_SSG_STATS_ACR_ARG_RECVD;

                                TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                                TransatelCAPRoTransactionContext* userData =
                                    reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

                                /* Setting the transaltor State whenever ACR is received
                                 * and also clear any previously set Disconnect trigger
                                 * timeStamps */
                                userData->SetTranslatorState(ACR_RCVD);
                                userData->ClearDisconTriggerTimeStamp();

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

                                cap_v2::CAMEL_CallResult camelcr;
                                const std::vector<byte>& vec = cr.GetArray();
                                Octets croctets(vec,vec.size());
                                camelcr.Decode(croctets);

                                LogCAPTslAsnObj(camelcr);


                                //DLOG_DEBUG("[CAP:AppyChargingReportArg] - [ro:CreditControlRequest]");

                                TranslateAcrToCcr(ctxt, &camelcr, ccr, ret);
                                //NOTE: This check is for Error case, i.e Received ACR with CallActive true after ReleaseCall sent.
                                if(ret.action == IWF_RA_CONSUME)
                                {
                                    if (ccr != NULL)
                                    {
                                        delete ccr;
                                        ccr = NULL;
                                    }
                                    break;
                                }
                                SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), IWF_DEFAULT_SERVICE_KEY, ccr);
                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);

                                m_dccaHandler.HandleRequest(userData->GetDccaContext(),
                                        cmd, ccr->getCCRequestType().value());

                                ReleaseInvokeId(ctxt, cpt->GetInvokeID());
                                ReleaseStoredInvokeIds(ctxt);

                                LogRoTslDiaMsg(*ccr,false);
                                break;
                            }
                        case cap::OP_eventReportSMS:
                            {
                                TransatelCAPRoTransactionContext* userData =
                                    reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                                userData->SetTranslatorState(ER_SMS_RCVD);
                                /*Stop the INTERNAL_NO_EVENT_TIMER*/
                                ETimerType timerType = ETimerType::NO_EVENT_TIMER;
                                STimerInfo fsmTimerData;
                                ctxt->GetTimerInfo(timerType, fsmTimerData);

                                IwfTimer timerObj;
                                if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                                {
                                    //DLOG_DEBUG("[CAP:EventReportSMSArg] TimerType : NO_EVENT_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
                                    ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                                }
                                else
                                {
                                    DLOG_ERROR("[CAP:EventReportSMSArg] Failed to stop TimerType : NO_EVENT_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
                                }

                                Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
                                cap_v3::EventReportSMSArg ersmsArg;
                                Octets octs(buf);
                                ersmsArg.Decode(octs);
                                userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

                                LogCAPTslAsnObj(ersmsArg);
                                UPDATE_SSG_STATS_ERSMS_ARG_RECVD;

                                //DLOG_DEBUG("[CAP:EventReportSMSArg] - [ro:CreditControlRequest(T)]");

                                EventReportSMSArg_To_CCRT(ctxt, &ersmsArg, ccr);
                                SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                                SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), IWF_DEFAULT_SERVICE_KEY, ccr);

                                cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                                cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);

                                /* Storing the last Sent CC-Request-Type to be used for
                                 * validating incoming anser msg from ocs*/
                                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);

                                m_dccaHandler.HandleRequest(userData->GetDccaContext(),
                                        cmd, Ro_TSL::CCRequestType::TERMINATION_REQUEST);

                                LogRoTslDiaMsg(*ccr,false);
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
                    TCAP_Result* tcapResult = static_cast<TCAP_Result*>(cpt);
                    userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                    if(userData)
                    {
                        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                        if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE)
                        {
                            if (!tcapResult->HasOperation())
                            {
                                /*DLOG_DEBUG("Received TCAP Result with InvokeId : %d and stored InvokeId : %d",
                                        cpt->GetInvokeID(),userData->GetActivityTimerData().invokeid());*/
                                if(cpt->GetInvokeID() == userData->GetActivityTimerData().invokeid())
                                {
                    		    UPDATE_SSG_STATS_ACT_RESP_RECVD;
                                    /* After receiving AT response update the AT
                                     * retry Count to configured value */
                                    //ActivityTimerData activityTimer = userData->GetActivityTimerData();
                                    pbActivityTimerData activityTimer;
                                    activityTimer.CopyFrom(userData->GetActivityTimerData());
                                    activityTimer.set_retrycount(m_config.ActivityTimer().retryCount);
                                    activityTimer.set_attimer(m_config.ActivityTimer().timerValue);
                                    /*DLOG_DEBUG("Recieved response for the last sent ActivityTest request,"
                                            "restoring the retryCount to %d and AT timer value : %d"
                                            ,activityTimer.retrycount(),activityTimer.attimer());*/
                                    userData->SetActivityTimerData(activityTimer);

                                    /* Start the next ACTIVITY_TIMER for actual
                                     * configured values */
                                    StartTimerHandling(ctxt, ETimerType::ACTIVITY_TIMER);


                                    /* AT response received in TC_Result stop the
                                     * Activity retry interval timer and remove it
                                     * from the IwfFsm */
                                    ETimerType timerType = ETimerType::ACTIVITY_RESPONSE_TIMER;
                                    STimerInfo fsmTimerData;
                                    if (ctxt->GetTimerInfo(timerType, fsmTimerData) == ITS_SUCCESS)
                                    {
                                        IwfTimer timerObj;
                                        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                                        {
                                            /*DLOG_DEBUG("AT response in TC_RESULT  received TimerType : ACTIVITY_RESPONSE_TIMER, TimerId : %u stopped."
                                                    ,fsmTimerData.m_uiTimerId);*/
                                            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                                        }
                                        else
                                        {
                                            DLOG_ERROR("AT response received Failed to stop TimerType : ACTIVITY_RESPONSE_TIMER, TimerId : %u"
                                                    ,fsmTimerData.m_uiTimerId);
                                        }
                                    }
                                    else
                                    {
                                        DLOG_ERROR("Unable to retreieve the ACTIVITY_RESPONSE_TIMER Timer info from FSM");
                                    }
                                    //DLOG_INFO("ActivityTest Response received in TC_Result");
                                    ret.action = IWF_RA_CONSUME;
                                    ret.dir = IWF_RD_DIA;
                                    break;
                                }
                                else
                                {
                                    DLOG_ERROR("Received component in Dailogue in TC_CONT does not match with sent InvokeId...droping the message");
                                    ret.action = IWF_RA_CONSUME;
                                    ret.dir = IWF_RD_DIA;
                                    break;
                                }
                            }
                            else
                            {
                                DLOG_ERROR("Received Component in dailogue TC_CONT with Opcode, Terminating the current Session");
                                if(userData->IsIDPReceived())
                                {
                                    uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                                    userData->SetUSUCCTime(totalUsedSeconds);
                                    BuildCCRTerminateForIDP(ctxt,
                                            (diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
                                }
                                else if(userData->IsIDPSMSReceived())
                                {
                                    BuildCCRTerminateForIDPSMS(ctxt, diameter::base::TerminationCause::DIAMETER_LOGOUT, cmd);
                                }
                                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                                ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                            }
                        }
                        else if(inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                        {
                            DLOG_ERROR("Received Component in dailogue TC_END with Opcode, Terminating the current Session");
                            if(userData->IsIDPReceived())
                            {
                                uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                                userData->SetUSUCCTime(totalUsedSeconds);
                                BuildCCRTerminateForIDP(ctxt,
                                        (diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
                            }
                            else if(userData->IsIDPSMSReceived())
                            {
                                BuildCCRTerminateForIDPSMS(ctxt, diameter::base::TerminationCause::DIAMETER_LOGOUT, cmd);
                            }
                            ret.action = IWF_RA_FORWARD;
                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                        }
                        else
                        {
                            DLOG_CRITICAL("Unexpected DialogueType Received %d", inTcapDlg->GetDialogueType());
                            ret.action = IWF_RA_CONSUME;
                            ret.dir = IWF_RD_DIA;
                        }
                    }
                }

                break;
            case TCPPT_TC_U_ERROR:
                {
                    userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                    if(userData)
                    {
                        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                        TCAP_Error *errCmpt = (TCAP_Error*)cpt;
                        ITS_OCTET errReasonVal;
                        errCmpt->GetError(errReasonVal);

                        if(userData->IsIDPReceived())
                        {
                            IDPToCCRIData idpStoredData;
                            idpStoredData.CopyFrom(userData->GetIDPToCCRIData());
                            idpStoredData.set_tcap_error_cause((unsigned int) errReasonVal);

                            DLOG_DEBUG("BuildDiaMsg :: Extracted ErrorReason value : %u, Value set in RoTransContext : %u.",
                                    errReasonVal,
                                    idpStoredData.tcap_error_cause());
                            userData->SetIDPToCCRIData(idpStoredData);
                            uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                            userData->SetUSUCCTime(totalUsedSeconds);
                            BuildCCRTerminateForIDP(ctxt,
                                    (diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
                        }
                        else if(userData->IsIDPSMSReceived())
                        {
                            StoredIDPSMSToCCRIData idpSMSStoredData;
                            idpSMSStoredData.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
                            idpSMSStoredData.set_cap_tcap_error_cause((unsigned int) errReasonVal);

                            DLOG_DEBUG("BuildDiaMsg :: Extracted ErrorReason value : %u, Value set in RoTransContext : %u.",
                                    errReasonVal,
                                    idpSMSStoredData.cap_tcap_error_cause());
                            userData->SetStoredIDPSMSToCCRIData(idpSMSStoredData);

                            BuildCCRTerminateForIDPSMS(ctxt, diameter::base::TerminationCause::DIAMETER_LOGOUT, cmd);
                        }
                        if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE)
                        {
                            //DLOG_DEBUG("Received Tcap_Error Component in dailogue TC_CONT, Terminating the current Session");
                            ret.action = IWF_RA_RESPOND_AND_FORWARD;
                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                        }
                        else if(inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                        {
                            //DLOG_DEBUG("Received Tcap_Error Component in dailogue TC_END, Terminating the current Session");
                            ret.action = IWF_RA_FORWARD;
                            ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                        }
                        else
                        {
                            DLOG_CRITICAL("Unexpected DialogueType Received %d", inTcapDlg->GetDialogueType());
                            ret.action = IWF_RA_CONSUME;
                            ret.dir = IWF_RD_DIA;
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
        rc = !ITS_SUCCESS;
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
    }
    catch (diameter::CodecExceptionToApp& e)
    {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for sessionId %s is %d", e.sessionId(), e.errcode());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
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

int TransatelCAPToRoHandler::BuildInterimTCAPMsg(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    int rc = ITS_SUCCESS;
    ITS_ByteArray buf;

    return rc;
}

int TransatelCAPToRoHandler::BuildTcapResponse(IwfFsm *ctxt,
        TCAP_Component *in,  TCAP_Component *&out,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = in->GetComponentType();
    out = NULL;
    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();

#if 0
    if (cptType != TCPPT_TC_INVOKE)
    {
        ret.action = IWF_RA_ERROR;
        ret.dir = IWF_RD_TCAP;
        ret.appContext = map_common::UNKNOWN;
        return !ITS_SUCCESS;
    }
#endif

    if(cptType == TCPPT_TC_INVOKE)
    {
        TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(in);
        tcapIvk->GetOperation(opCode);
    }
    ITS_OCTET  invkId = 0;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    try
    {
        if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE &&
                (in->GetComponentType() == TCPPT_TC_RESULT_L || in->GetComponentType() == TCPPT_TC_U_ERROR))
        {
            if(userData->IsIDPSMSReceived())
            {
                //DLOG_DEBUG("Release Build for either TCAP ResultLast/Error Component received");
                BuildReleaseSMS(ctxt,NULL,out,userData->GetReleaseCause());
                if ( out != NULL )
                {
                    UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    out->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    userData->SetCapReleaseSent(true);

                    ret.action = IWF_RA_FORWARD;
                }
            }
            else
            {
                //DLOG_DEBUG("Release Build for either TCAP ResultLast/Error Component received");
                BuildRelease(ctxt,NULL,out,userData->GetReleaseCause());
                if ( out != NULL )
                {
                    UPDATE_SSG_STATS_REL_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    out->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    userData->SetCapReleaseSent(true);

                    ret.action = IWF_RA_FORWARD;
                }
            }
        }
        else if (opCode == cap::OP_applyChargingReport)
        {
            if ( userData->IsCurrentReceivedTcapContinue() )
            {
                if ( userData->IsCapReleaseSent() )
                {
                    DLOG_ERROR("ReleaseCall already sent in TC_CONTINUE, Hence send TC_END w/o component to close the dialog.");
                    ret.action = IWF_RA_FORWARD_DUMMY_TCEND;
                }
                else
                {
                    //DLOG_DEBUG("[ACR with Call-Active False] -> [CAP::ReleaseCall]");
                    BuildRelease(ctxt,NULL,out,userData->GetReleaseCause());
                    if ( out != NULL )
                    {
                        UPDATE_SSG_STATS_REL_ARG_SENT;
                        invkId = ctxt->GetInvkId();
                        out->SetInvokeID(++invkId);
                        ctxt->SetInvkId(invkId);
                        userData->SetCapReleaseSent(true);

                        ret.action = IWF_RA_FORWARD;
                    }
                }
            }
            else
            {
                //DLOG_DEBUG("Received ACR in TC_END no need to send ReleaseCallArg consume");
                ret.action = IWF_RA_CONSUME;
            }
        }
        else if (opCode == cap::OP_eventReportBCSM)
        {
            if ( userData->IsCurrentReceivedTcapContinue() )
            {
                //DLOG_DEBUG("[ERB] -> [CAP::ReleaseCall]");
                byte cause = userData->GetReleaseCause();
                BuildRelease(ctxt,NULL,out,cause);
                if ( out != NULL )
                {
                    UPDATE_SSG_STATS_REL_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    out->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    userData->SetCapReleaseSent(true);

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

int TransatelCAPToRoHandler::BuildDiaErrorAnswer(IwfFsm *ctxt, int cmdCode, int error, DIA_BASE_CMD **out)
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
                LogRoTslDiaMsg(*raa, false);
                *out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)raa);
                (*out)->SetDictId(DIAMETER_RO_DICTIONARY_ID);
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

int TransatelCAPToRoHandler::BuildDiaErrorResponse(IwfFsm *ctxt,
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
void TransatelCAPToRoHandler::BuildErrorResponse(
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
void TransatelCAPToRoHandler::ConstructErrorAnswer(int error,T *out)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    diameter::base::BaseGenericCommand *diaBaseGenCmd = (diameter::base::BaseGenericCommand *) out;
    diameter::DiaHeader& hdr = const_cast<diameter::DiaHeader&>(diaBaseGenCmd->getHeader());

    /*Set the E BIT Explicitly*/
    hdr.flags.e = 1;
    //DLOG_DEBUG("ConstructErrorAnswer: E-BIT is : %d", hdr.flags.e);
    diameter::base::ResultCode res(error);
    out->setResultCode(res);
}

int TransatelCAPToRoHandler::BuildDiaResponse(IwfFsm* ctxt, DIA_BASE_CMD* in, DIA_BASE_CMD*& out, IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    ret.dir = IWF_RD_DIA;
    out = NULL;

    try
    {
        const diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(in))->GetBaseGenCommand();
        // the diameter message is Ro, assuming that the MAP function is called
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

                LogRoTslDiaMsg(*raa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)raa);
                out->SetDictId(DIAMETER_RO_DICTIONARY_ID);
            }
            if(code == DIA_CMD_AS)
            {
                diameter::base::AbortSessionRequest asr(cmd->getImpl());

                DLOG_DEBUG("Constructing AbortSessionAnswer for AbortSessionRequest");
                diameter::base::AbortSessionAnswer *asa = new diameter::base::AbortSessionAnswer();
                TransatelCAPRoTransactionContext* userData =
                    reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
                if (userData)
                {
                    userData->SetASRReceived(true);
                }

                ConstructASA(ctxt, &asr, asa);
                SetDefaultAVPsInAns(ctxt, asa);

                LogRoTslDiaMsg(*asa, false);
                out = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)asa);
                out->SetDictId(DIAMETER_RO_DICTIONARY_ID);
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

void TransatelCAPToRoHandler::ConstructRAA(IwfFsm *ctxt, const diameter::base::ReAuthRequest *in,
        diameter::base::ReAuthAnswer *out)
{
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);
}

void TransatelCAPToRoHandler::ConstructASA(IwfFsm *ctxt, const diameter::base::AbortSessionRequest *in,
        diameter::base::AbortSessionAnswer *out)
{
    diameter::base::ResultCode res(ITS_DIA_SUCCESS);
    out->setResultCode(res);
}

int TransatelCAPToRoHandler::ProcessInitialDP(IwfFsm *ctxt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("ProcessInitialDP -- Entry");

    its::TCAP_Dialogue* currDlg = NULL;
    if(NULL != ctxt)
    {
        currDlg = ctxt->GetCurrRcvdTcapDlg();
    }
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData == NULL)
    {
        userData = new TransatelCAPRoTransactionContext(ctxt->GetCapRoTslData());
        userData->SetReleaseCause(m_config.ReleaseCallCauseCode());
        ctxt->SetStoredUserData(userData);
    }

    cap::CAP_AC appCtxt;
    its::ITS_ByteArray app_ctxt, buf;
    currDlg->GetApplicationContext(buf);
    appCtxt = cap::DecodeApplicationContext(buf);

    switch(appCtxt)
    {

        case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
            {
                userData->SetRecvAppCtxt(cap::CAPV1_gsmSSF_to_gsmSCF_AC);
            }
            break;
        case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
            {
                userData->SetRecvAppCtxt(cap::CAPV2_gsmSSF_to_gsmSCF_AC);
            }
            break;
        case cap::CAPV3_cap3_sms_AC :
            {
                userData->SetRecvAppCtxt(cap::CAPV3_cap3_sms_AC);
            }
            break;

        default :
            {
                //DLOG_DEBUG("ProcessInitialDP: Unknown CAP ApplicationContext : %d received in dlg",appCtxt);
                app_ctxt = cap::EncodeApplicationContext(cap::UNKNOWN);
            }
            break;
    }

    //DLOG_DEBUG("ProcessInitialDP:: Received CAP AppContext : %d",appCtxt);
    //DLOG_DEBUG("ProcessInitialDP -- Exit");
    return ITS_SUCCESS;
}


int TransatelCAPToRoHandler::InitialDPArg_To_CCR_Initial(IwfFsm *ctxt,
        const cap_v3::InitialDPArg *in,
        Ro_TSL::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    return ret;
}

int TransatelCAPToRoHandler::InitialDPSMSArg_To_CCR_Initial(IwfFsm *ctxt,
        const cap_v3::InitialDPSMSArg *in,
        Ro_TSL::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    std::string appId = DIAMETER_RO_APPLICATION_ID;
    std::string callingGtAddrDigits = "";
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData == NULL)
    {
        userData = new TransatelCAPRoTransactionContext(ctxt->GetCapRoTslData());
        userData->SetReleaseCause(m_config.ReleaseSmsCauseCode());
        ctxt->SetStoredUserData(userData);
    }
    userData->SetIDPSMSReceived(true);
    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    StoredIDPSMSToCCRIData ccriData;

    std::string oImsi;
    std::string mcc = "", mnc = "";
    TransCustomAvp::CSInformation csinfo;
    TransCustomAvp::CAPInformation capInfoVal;
    if(in->OptionEventTypeSMS())
    {
        diameter::Unsigned32 smsEventVal = (diameter::Unsigned32)in->GetEventTypeSMS().GetValue();
        const TransCustomAvp::CAPEventTypeSMS capSMSEventVal(smsEventVal);
        capInfoVal.setCAPEventTypeSMS(capSMSEventVal);
        ccriData.set_cap_event_type_sms(smsEventVal);
    }
    else
    {
        DLOG_ERROR("IWF Error:  Mandatory Mapping of EventTypeSMS for IDPSMS-CCR-I for CAP-Ro not configured :");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }


    char strDlgId[sizeof(ITS_CTXT)];

    uint32_t remoteTransId;
    TCAP_TRANS_ENTRY *localTx = NULL;
    localTx = TCAP_FindLocalTx_CCITT(ctxt->GetTcapDlgId());
    if(NULL != localTx)
    {
        remoteTransId = localTx->rtid;
        //DLOG_DEBUG("Remote transaction Id %x",remoteTransId);
        sprintf(strDlgId,"%08x",remoteTransId);
        uint8_t remId[NYBBLE_SIZE] = {0};

        int len = IWFUtils::StringToTBCD(strDlgId, remId,strlen(strDlgId), 0, true);
        string hexString((const char*)remId,len);
        string strId(strDlgId);
        userData->SetRemoteTransIdForCDR(strId);

        TransCustomAvp::CAPTCAPRemoteTransactionId tcapRemoteId(hexString);
        capInfoVal.setCAPTCAPRemoteTransactionId(tcapRemoteId);
        ccriData.set_cap_tcap_remote_transaction_id(hexString);


    }
    Call_Type val;

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    TCAP_Begin *begin = (TCAP_Begin*)inTcapDlg;
    SCCP_CalledPartyAddr destAddr;
    begin->GetDestAddr(destAddr);

    int startIndex = 0;
    if (destAddr.HasGlobalTitle())
    {
        ITS_OCTET type = 0;
        ITS_USHORT gttLen = 0;
        ITS_OCTET gttInfo[64] = {0};

        // Get gloabal title from address
        destAddr.GetGlobalTitle(type, gttInfo, gttLen);
        startIndex = ReturnStartOctet(type);
        string gtdigits = "";
        IWFUtils::TBCDToString(&gttInfo[startIndex], (gttLen - startIndex), gtdigits);
        if(gttInfo[1] & 1)
        {
            capInfoVal.setCAPSCCPCalledGT(TransCustomAvp::CAPSCCPCalledGT(gtdigits.substr(0,gtdigits.length()-1)));
            ccriData.set_cap_sccp_calledgt(gtdigits.substr(0,gtdigits.length()-1));
        }
        else
        {
            capInfoVal.setCAPSCCPCalledGT(TransCustomAvp::CAPSCCPCalledGT(gtdigits));
            ccriData.set_cap_sccp_calledgt(gtdigits);
        }
    }

    SCCP_CallingPartyAddr orgAddr;
    begin->GetOrigAddr(orgAddr);

    if(orgAddr.HasGlobalTitle())
    {
        ITS_OCTET type = 0;
        ITS_USHORT gttLen = 0;
        ITS_OCTET gttInfo[64] = {0};
        // Get gloabal title from address
        orgAddr.GetGlobalTitle(type, gttInfo, gttLen);
        startIndex = ReturnStartOctet(type);
        string gtdigits = "";
        IWFUtils::TBCDToString(&gttInfo[startIndex], (gttLen - startIndex), gtdigits);
        if(gttInfo[1] & 1)
        {
            capInfoVal.setCAPSCCPCallingGT(TransCustomAvp::CAPSCCPCallingGT(gtdigits.substr(0,gtdigits.length()-1)));
            ccriData.set_cap_sccp_callinggt(gtdigits.substr(0,gtdigits.length()-1));
        }
        else
        {
            capInfoVal.setCAPSCCPCallingGT(TransCustomAvp::CAPSCCPCallingGT(gtdigits));
            ccriData.set_cap_sccp_callinggt(gtdigits);
        }
    }

    if(in->OptionEventTypeSMS())
    {
        switch(in->GetEventTypeSMS().GetValue())
        {
            case cap_v3::EventTypeSMS::EVENT_TYPE_SMS_SMS_COLLECTED_INFO :
                {
                    val = Call_Type::MO_SMS;
                    break;
                }
            case cap_v3::EventTypeSMS::EVENT_TYPE_SMS_SMS_DELIVERY_REQUESTED :
                {
                    val = Call_Type::MT_SMS;
                    break;
                }

            default:
                {
                    DLOG_ERROR("IWF Error:  Mandatory IE EventTypeBCSM contains : %d unknown value, no mapping done.");
                }
        }
    }
    userData->SetCallType(val);
    TransCustomAvp::CAPServiceKey capSrvKey((unsigned int)(in->GetServiceKey().GetValue()));
    capInfoVal.setCAPServiceKey(capSrvKey);
    ccriData.set_cap_service_key((unsigned int)(in->GetServiceKey().GetValue()));

    //NOTE: For SMS case CAP Version is 3
    capInfoVal.setCAPVersion(diameter::transatel_custom_avps::CAPVersion(3));
    ccriData.set_cap_version(3);

    if(in->OptionImei())
    {
        string strImei;
        const std::vector<byte>& vec = in->GetImei().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), strImei);
        TransCustomAvp::CAPIMEI capImei(strImei);
        capInfoVal.setCAPIMEI(capImei);
        ccriData.set_cap_sm_imei(strImei);
    }

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
        //std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId,
        //        in->GetServiceKey().GetValue(), callingGtAddrDigits)->ServiceContextId();
        std::string RuleName("");
        int32_t skVal = in->GetServiceKey().GetValue();
        int32_t ossn = CAP;
        if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,skVal,RuleName,ossn))
        {
            DLOG_ERROR("Could not find a RuleName configured.");
            return !ITS_SUCCESS;
        }

        std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(RuleName, callingGtAddrDigits)->ServiceContextId();

        Ro_TSL::ServiceContextId serviceContextId((servCtxtId));
        out->setServiceContextId(serviceContextId);
        userData->SetServiceContextId(servCtxtId);

        TransCustomAvp::CAPIMSI imsiVal(oImsi);
        capInfoVal.setCAPIMSI(imsiVal);
        ccriData.set_cap_imsi(oImsi);

        Ro_TSL::SubscriptionId subsId;
        subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_IMSI));
        subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(oImsi));
        out->addSubscriptionId(subsId);

        SubscriptionIdConfig* subsIdInfo = ccriData.mutable_subscriptionidinfo();
        subsIdInfo->set_subidtype(Ro_TSL::SubscriptionIdType::END_USER_IMSI);
        subsIdInfo->set_subiddata(oImsi);
    }

    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);
    out->setCCRequestType(ccRequestType);

    ccrnum = userData->GetCCRequestNumber();
    Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
    out->setCCRequestNumber(ccRequestNumber);
    userData->SetCCRequestNumber(ccrnum);



    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    out->setMultipleServicesIndicator(msi);

    Ro_TSL::MultipleServicesCreditControl mscc;
    Ro_TSL::UsedServiceUnit usu;
    usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));
    mscc.addUsedServiceUnit(usu);
    Ro_TSL::RequestedServiceUnit rsu;
    rsu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits(1));
    mscc.setRequestedServiceUnit(rsu);
    out->addMultipleServicesCreditControl(mscc);

    ITS_UINT seconds = this->GetCurrentTimeStamp();
    diameter::base::EventTimestamp eventTimestamp(seconds);
    out->setEventTimestamp(eventTimestamp);
    userData->SetSessionStartTime(seconds-TIME_FROM_1900_TO_EPOCH);

    Ro_TSL::ServiceInformation si;

    std::string DestSubNo = "";
    if(in->OptionDestinationSubscriberNumber())
    {
        const std::vector<byte>& vec = in->GetDestinationSubscriberNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), DestSubNo);//, false , true);
        size_t fPos = DestSubNo.find('F');
        if (fPos != std::string::npos)
        {
            DestSubNo.erase(fPos, std::string::npos);
        }

        TransCustomAvp::CAPDialedDigits capDialDigits(DestSubNo.substr(SUB_STR_POS_2));
        capInfoVal.setCAPDialedDigits(capDialDigits);
        ccriData.set_cap_dialed_digits(DestSubNo.substr(SUB_STR_POS_2));

        string sOctDigitVal,sOctDigitVal2;
        sOctDigitVal = DestSubNo.substr(SUB_STR_POS_0+1,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);

        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> byteVal(iOctDigit);
        bitset<NYBBLE_SIZE-1> tonBitVal;

        tonBitVal.reset();
        tonBitVal[BYTE_POS_0] = byteVal[BYTE_POS_0];
        tonBitVal[BYTE_POS_1] = byteVal[BYTE_POS_1];
        tonBitVal[BYTE_POS_2] = byteVal[BYTE_POS_2];

        capInfoVal.setCAPCalledTON(TransCustomAvp::CAPCalledTON(tonBitVal.to_ulong()));
        ccriData.set_cap_called_ton((unsigned int)capInfoVal.getCAPCalledTON().value());

        sOctDigitVal = DestSubNo.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> byteVal1(iOctDigit);
        capInfoVal.setCAPCalledNPI(TransCustomAvp::CAPCalledNPI(byteVal1.to_ulong()));
        ccriData.set_cap_called_npi((unsigned int)capInfoVal.getCAPCalledNPI().value());
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

        TransCustomAvp::CAPCLI capcli(callingPartyNumber.substr(SUB_STR_POS_2));

        capInfoVal.setCAPCLI(capcli);
        ccriData.set_cap_cli(callingPartyNumber.substr(SUB_STR_POS_2));

        //DLOG_DEBUG("CAPCLI AVP:  %s",capInfoVal.getCAPCLI().value().c_str());

        string sOctDigitVal, sOctDigitVal2;

        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal1(iOctDigit);

        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal2(iOctDigit);

        string octStrVal;
        octStrVal = octVal1.to_string();
        octStrVal += octVal2.to_string();
        bitset<BYTE_SIZE> finalOct(octStrVal);
        bitset<NYBBLE_SIZE> npiBitVal;

        for(int i = 0; i< NYBBLE_SIZE; i++)
        {
            npiBitVal[i] = finalOct[i];
        }
        bitset<NYBBLE_SIZE-1> noaBitVal;
        {
            noaBitVal[BYTE_POS_0] =  finalOct[BYTE_POS_4];
            noaBitVal[BYTE_POS_1] =  finalOct[BYTE_POS_5];
            noaBitVal[BYTE_POS_2] =  finalOct[BYTE_POS_6];
        }

        TransCustomAvp::CAPCLINOA capCgPtyNOA(noaBitVal.to_ulong());
        capInfoVal.setCAPCLINOA(capCgPtyNOA);
        //DLOG_DEBUG("CAPCallingNOA AVP:  %ul",capInfoVal.getCAPCLINOA().value());
        ccriData.set_cap_calling_noa((unsigned int)noaBitVal.to_ulong());

        TransCustomAvp::CAPCLINPI capCgPtyNPI(noaBitVal.to_ulong());
        capInfoVal.setCAPCLINPI(capCgPtyNPI);
        ccriData.set_cap_cli_npi((unsigned int) capInfoVal.getCAPCLINPI().value());

        //DLOG_DEBUG("CAPCLINPI AVP:  %ul",capInfoVal.getCAPCLINPI().value());

    }

    /*if(userData->HasIMSChargingIdentifier())
    {
        userData->ClearIMSChargingIdentifier();
    }*/

    if(in->OptionSmsReferenceNumber())
    {
        /*std::string smsRef = "";;
          const std::vector<byte>& vec = in->GetSmsReferenceNumber().GetArray();
          IWFUtils::TBCDToString(&vec[0], vec.size(), smsRef, false , true, true);*/

        TransCustomAvp::CAPCallReference callRefNoVal(IWFUtils::VectorToString(in->GetSmsReferenceNumber().GetArray()));
        capInfoVal.setCAPCallReference(callRefNoVal);
        ccriData.set_cap_call_reference(IWFUtils::VectorToString(in->GetSmsReferenceNumber().GetArray()));
    }

    /* For TSL flow irrespective of SGSN SSN present in SCPOrigAddr or not,
     * map Sgsn_Number IE recv in IDP to CAP-SGSN-Address AVP
     * map Msc_Address recv in IDP to CAP-SGSN-Address AVP */
    //if(ctxt->GetTransactionManager()->GetOrigSSN() == MSC_CAP)
    //{
    if(in->OptionMscAddress())
    {
        std::string mscAddress;
        const std::vector<byte>& vec = in->GetMscAddress().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), mscAddress);//, false, true);
        size_t fPos = mscAddress.find('F');
        if (fPos != std::string::npos)
        {
            mscAddress.erase(fPos, std::string::npos);
        }

        capInfoVal.setCAPMSCAddress(TransCustomAvp::CAPMSCAddress(mscAddress.substr(SUB_STR_POS_2)));
        ccriData.set_cap_msc_address(mscAddress.substr(SUB_STR_POS_2));
    }
    //}
    //else if(ctxt->GetTransactionManager()->GetOrigSSN() == SGSN_SSN)
    //{
    if(in->OptionSgsn_Number())
    {
        std::string sgsnNumber;
        const std::vector<byte>& vec = in->GetSgsn_Number().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), sgsnNumber);//, false , true);
        size_t fPos = sgsnNumber.find('F');
        if (fPos != std::string::npos)
        {
            sgsnNumber.erase(fPos, std::string::npos);
        }

        capInfoVal.setCAPSGSNAddress(TransCustomAvp::CAPSGSNAddress(sgsnNumber.substr(SUB_STR_POS_2)));
        ccriData.set_cap_sgsn_address(sgsnNumber.substr(SUB_STR_POS_2));
    }
    //}

    if(in->OptionTPDataCodingScheme())
    {
        std::string tpData;
        const std::vector<byte>& vec = in->GetTPDataCodingScheme().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), tpData, false , true, true);
        TransCustomAvp::CAPSMDCS smsDataCodingSch(tpData);
        capInfoVal.setCAPSMDCS(smsDataCodingSch);
        ccriData.set_cap_sm_dcs(tpData);

    }

    if(in->OptionTPProtocolIdentifier())
    {
        std::string protocolIdentifier;
        const std::vector<byte>& vec = in->GetTPProtocolIdentifier().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), protocolIdentifier, false, true, true);

        capInfoVal.setCAPSMProtocolID(TransCustomAvp::CAPSMProtocolID(protocolIdentifier));
        ccriData.set_cap_sm_protocolid(protocolIdentifier);

    }

    if(in->OptionTPValidityPeriod())
    {
        std::string validityperiod;
        const std::vector<byte>& vec = in->GetTPValidityPeriod().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), validityperiod, false, true, true);
        capInfoVal.setCAPSMValidityPeriod(TransCustomAvp::CAPSMValidityPeriod(validityperiod));
        ccriData.set_cap_sm_validityperiod(validityperiod);
    }


    if(in->OptionSMSCAddress())
    {
        std::string smscAddress = "";
        const std::vector<byte>& vec = in->GetSMSCAddress().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), smscAddress);//, false , true);
        size_t fPos = smscAddress.find('F');
        if (fPos != std::string::npos)
        {
            smscAddress.erase(fPos, std::string::npos);
        }

        capInfoVal.setCAPSMSCAddress(TransCustomAvp::CAPSMSCAddress(smscAddress.substr(SUB_STR_POS_2)));
        ccriData.set_cap_smsc_address(smscAddress.substr(SUB_STR_POS_2));
    }

    if(in->OptionTPShortMessageSubmissionSpecificInfo())
    {
#if 0
        string strTPSMSInf;
        const std::vector<byte>& vec = in->GetTPShortMessageSubmissionSpecificInfo().GetArray();

        strTPSMSInf += IWFUtils::ToChar(IWFUtils::High4(vec[0]));
        strTPSMSInf += IWFUtils::ToChar(IWFUtils::Low4(vec[0]));

        string sOctDigitVal,sOctDigitVal2;

        sOctDigitVal = strTPSMSInf.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal(iOctDigit);

        sOctDigitVal = strTPSMSInf.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);

        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal2(iOctDigit);

        string octStrVal;
        octStrVal = octVal.to_string();
        octStrVal += octVal2.to_string();
        bitset<BYTE_SIZE> finalOct(octStrVal);


        TransCustomAvp::CAPSMMessageTypeIndicator capSMSTypeInd((finalOct.to_string()).substr(SUB_STR_POS_5+1,SUB_STR_LEN_2));
        TransCustomAvp::CAPSMRejectDuplicate capSMSRD((finalOct.to_string()).substr(SUB_STR_POS_5,SUB_STR_LEN_1));
        TransCustomAvp::CAPSMVPFormat capVPF((finalOct.to_string()).substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_2));
        TransCustomAvp::CAPSMStatusReportRequest capSRR((finalOct.to_string()).substr(SUB_STR_POS_2,SUB_STR_LEN_1));
        TransCustomAvp::CAPSMUserDataHeaderIndicator capUDHI((finalOct.to_string()).substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1));
        TransCustomAvp::CAPSMReplyPath capRP((finalOct.to_string()).substr(SUB_STR_POS_0,SUB_STR_LEN_1));

        capInfoVal.setCAPSMMessageTypeIndicator(capSMSTypeInd);
        capInfoVal.setCAPSMRejectDuplicate(capSMSRD);
        capInfoVal.setCAPSMVPFormat(capVPF);
        capInfoVal.setCAPSMStatusReportRequest(capSRR);
        capInfoVal.setCAPSMUserDataHeaderIndicator(capUDHI);
        capInfoVal.setCAPSMReplyPath(capRP);

        ccriData.CAP_SM_MessageTypeIndicator = ((finalOct.to_string()).substr(SUB_STR_POS_5+1,SUB_STR_LEN_2));
        ccriData.CAP_SM_RejectDuplicate = ((finalOct.to_string()).substr(SUB_STR_POS_5,SUB_STR_LEN_1));
        ccriData.CAP_SM_VPFormat = ((finalOct.to_string()).substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_2));
        ccriData.CAP_SM_StatusReportRequest = ((finalOct.to_string()).substr(SUB_STR_POS_2,SUB_STR_LEN_1));
        ccriData.CAP_SM_UserDataHeaderIndicator = ((finalOct.to_string()).substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1));
        ccriData.CAP_SM_ReplyPath = ((finalOct.to_string()).substr(SUB_STR_POS_0,SUB_STR_LEN_1));
#endif
        capInfoVal.setCAPSMSpecificInfo((TransCustomAvp::CAPSMSpecificInfo)IWFUtils::VectorToString(in->GetTPShortMessageSubmissionSpecificInfo().GetArray()));
        std::string capSMSpecificInfo = IWFUtils::VectorToString(in->GetTPShortMessageSubmissionSpecificInfo().GetArray());
        ccriData.set_cap_smspecificinfo(capSMSpecificInfo);
    }

    if(in->OptionLocationInformationMSC())
    {
        if(in->GetLocationInformationMSC().OptionCellGlobalIdOrServiceAreaIdOrLAI())
        {
            cap_v3::CellGlobalIdOrServiceAreaIdOrLAI cellIdOrSAIOrLai = in->GetLocationInformationMSC().GetCellGlobalIdOrServiceAreaIdOrLAI();

            string hexString;
            if(cellIdOrSAIOrLai.ChoiceCellGlobalIdOrServiceAreaIdFixedLength())
            {
                const std::vector < byte > arr = cellIdOrSAIOrLai.GetChoiceCellGlobalIdOrServiceAreaIdFixedLength().GetArray();
                TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLaiVal(IWFUtils::VectorToString(arr));
                capInfoVal.setCAPCellIDAreaIDLAI(cellIdAreaIdLaiVal);
                ccriData.set_cap_cellid_areaid_lai(IWFUtils::VectorToString(arr));
            }
            else if(cellIdOrSAIOrLai.ChoiceLaiFixedLength())
            {
                const std::vector < byte > arr = cellIdOrSAIOrLai.GetChoiceLaiFixedLength().GetArray();
                TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLaiVal(IWFUtils::VectorToString(arr));
                capInfoVal.setCAPCellIDAreaIDLAI(cellIdAreaIdLaiVal);
                ccriData.set_cap_cellid_areaid_lai(IWFUtils::VectorToString(arr));
            }
        }
        if(in->GetLocationInformationMSC().OptionVlr_number())
        {
            string vlrnumber;
            const std::vector<byte>& vec = in->GetLocationInformationMSC().GetVlr_number().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), vlrnumber);
            size_t fPos = vlrnumber.find('F');
            if (fPos != std::string::npos)
            {
                vlrnumber.erase(fPos, std::string::npos);
            }

            TransCustomAvp::CAPVLRNumber vlrNo(vlrnumber.substr(SUB_STR_POS_2));
            capInfoVal.setCAPVLRNumber(vlrNo);
            //DLOG_DEBUG("LocationInfo-->Vlr_Number AVP:  %s",capInfoVal.getCAPVLRNumber().value().c_str());
            ccriData.set_cap_vlr_number(vlrnumber.substr(SUB_STR_POS_2));
        }

        if(in->GetLocationInformationMSC().OptionLocationNumber())
        {
            string locnumber;
            const std::vector<byte>& vec = in->GetLocationInformationMSC().GetLocationNumber().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), locnumber);//, false , true);

            string locNumber(locnumber.substr(SUB_STR_POS_4));
            IWFUtils::TrimAddrSignal(locNumber,IsDigitsOdd(vec[0]));
            TransCustomAvp::CAPLocationNumber locNo(locNumber);
            capInfoVal.setCAPLocationNumber(locNo);
            //DLOG_DEBUG("Location_Number AVP:  %s",capInfoVal.getCAPLocationNumber().value().c_str());
            ccriData.set_cap_location_number(locNumber);
        }


    }

    if(in->OptionImei())
    {
        string strImei;
        const std::vector<byte>& vec = in->GetImei().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), strImei);
        TransCustomAvp::CAPIMEI capImei(strImei);
        capInfoVal.setCAPIMEI(capImei);
        ccriData.set_cap_sm_imei(strImei);
    }

    csinfo.setCAPInformation(capInfoVal);
    userData->SetStoredIDPSMSToCCRIData(ccriData);
    si.setCSInformation(csinfo);
    out->setServiceInformation(si);
    return ret;
}

unsigned int TransatelCAPToRoHandler::GetMSCCResultCode(Ro_TSL::CreditControlAnswer *cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_DIA_SUCCESS;
    if( cca->countMultipleServicesCreditControl() )
    {
        Ro_TSL::MultipleServicesCreditControl mscc =
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



int TransatelCAPToRoHandler::CheckMSCCGrantedServiceUnitCCTime(Ro_TSL::CreditControlAnswer *cca,
        TransatelCAPRoTransactionContext* userData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;

    if( cca->countMultipleServicesCreditControl() )
    {
        Ro_TSL::MultipleServicesCreditControl mscc =
            cca->getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsGrantedServiceUnit() )
        {
            Ro_TSL::GrantedServiceUnit gsu = mscc.getGrantedServiceUnit();
            if( !gsu.containsCCTime() || gsu.getCCTime().value() == 0)
            {
                return !ITS_SUCCESS;
            }

            //DLOG_DEBUG("GSU-CCTime : %u recv in CCA.",gsu.getCCTime().value());
        }
        else
        {
            DLOG_ERROR("GSU AVP missing in CCA");
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
        ret = !ITS_SUCCESS;
    }
    return ret;
}

int TransatelCAPToRoHandler::CheckMSCCGSUServiceSpecificUnits(Ro_TSL::CreditControlAnswer *cca,
        TransatelCAPRoTransactionContext* userData)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    if( cca->countMultipleServicesCreditControl() )
    {
        Ro_TSL::MultipleServicesCreditControl mscc =
            cca->getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsGrantedServiceUnit() )
        {
            Ro_TSL::GrantedServiceUnit gsu = mscc.getGrantedServiceUnit();
            if (!gsu.containsCCServiceSpecificUnits() || gsu.getCCServiceSpecificUnits().value() == 0)
            {
                DLOG_ERROR("No CCServiceSpecificUnits/CCServiceSpecificUnits = 0");
                ret = !ITS_SUCCESS;
            }
            else
            {
                /* update the StoredIDPSMSToCCRIData to store the GSU from CCA-I
                 * to be used for CDR generation */
                if (userData)
                {
                    StoredIDPSMSToCCRIData idpSmsData;
                    idpSmsData.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
                    idpSmsData.set_m_totalgsuccservice(gsu.getCCServiceSpecificUnits().value());
                    userData->SetStoredIDPSMSToCCRIData(idpSmsData);
                }
            }
        }
        else
        {
            DLOG_ERROR("No GSU avp present in MSCC");
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        DLOG_ERROR("No MSCC Avp present in the CCA");
        ret = !ITS_SUCCESS;
    }
    return ret;
}

int TransatelCAPToRoHandler::CheckMSCCFinalUnitAction(Ro_TSL::CreditControlAnswer& cca)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = !ITS_SUCCESS;
    if( cca.countMultipleServicesCreditControl() )
    {
        Ro_TSL::MultipleServicesCreditControl mscc =
            cca.getMultipleServicesCreditControl(MSCC_AVP_INDEX);
        if ( mscc.containsFinalUnitIndication() )
        {
            switch(mscc.getFinalUnitIndication().getFinalUnitAction().value())
            {
                case Ro_TSL::FinalUnitAction::REDIRECT :
                case Ro_TSL::FinalUnitAction::RESTRICT_ACCESS :
                    {
                        /*DLOG_DEBUG("CheckMSCCFinalUnitAction:: Recv FUI-Action %d, Session Id : %s, CCA-Type : %d.",
                                mscc.getFinalUnitIndication().getFinalUnitAction().value(),
                                cca.getSessionId().value().c_str(),
                                cca.getCCRequestType().value());*/
                        ret = !ITS_SUCCESS;
                    }
                    break;
                case Ro_TSL::FinalUnitAction::TERMINATE :
                default :
                    {
                        /*DLOG_DEBUG("CheckMSCCFinalUnitAction:: Recv FUI-Action %d, Session Id : %s, CCA-Type : %d.",
                                mscc.getFinalUnitIndication().getFinalUnitAction().value(),
                                cca.getSessionId().value().c_str(),
                                cca.getCCRequestType().value());*/
                        ret = ITS_SUCCESS;
                    }
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

int TransatelCAPToRoHandler::BuildCCRTerminateForIDPSMS(IwfFsm *ctxt,
        diameter::base::TerminationCause::Value causeCode,
        DIA_BASE_CMD *&cmd)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;

    //DLOG_DEBUG("BuildCCRTerminateForIDPSMS-- Entry");

    /* Stop all timers  before sending CCR-T*/

    ctxt->StopAllTimers();

    Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
    Ro_TSL::ServiceInformation si;
    Ro_TSL::UsedServiceUnit usu;
    Ro_TSL::IMSInformation imsinfo;
    Ro_TSL::MultipleServicesCreditControl mscc;
    TransCustomAvp::CAPInformation capInfo;
    TransCustomAvp::CSInformation csInfo;

    ctxt->SetFinalUpstrmReqSent(true);

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    ccr->setAuthApplicationId(authApplicationId);

    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
    ccr->setCCRequestType(ccRequestType);

    diameter::base::TerminationCause terminationCause(causeCode);
    ccr->setTerminationCause(terminationCause);

    usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));

    if(userData)
    {
        StoredIDPSMSToCCRIData idpSms = userData->GetStoredIDPSMSToCCRIData();
        usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)idpSms.m_totalusuccservice()));

        userData->SetTerminationCause(causeCode);

        if (userData->IsRetransmissionEnabled())
        {
            //DLOG_DEBUG("Setting T-bit for retransmission and retaining same CCR-Request number ");
            ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(--ccrnum);
            ccr->setCCRequestNumber(ccRequestNumber);

        }
        else
        {
            ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
            ccr->setCCRequestNumber(ccRequestNumber);
            userData->SetCCRequestNumber(ccrnum);
        }

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro_TSL::ServiceIdentifier(serviden));
        }

        ITS_UINT seconds = this->GetCurrentTimeStamp();
        diameter::base::EventTimestamp eventTimestamp(seconds);
        ccr->setEventTimestamp(eventTimestamp);

        if(userData->HasServiceContextId())
        {
            Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
            ccr->setServiceContextId(serviceContextId);
        }

        if(userData->HasERBData())
        {
            TransCustomAvp::CAPERBSInformation capERInfo; 
            pbERBData ErbData = userData->GetERBData();
            if(ErbData.has_erbrecvevttype())
            {
                capERInfo.setCAPEventTypeSMS(TransCustomAvp::CAPEventTypeSMS(ErbData.erbrecvevttype()));
            }

            if(ErbData.has_msgtype())
            {
                capERInfo.setCAPERBSMessageType(TransCustomAvp::CAPERBSMessageType(ErbData.msgtype()));
            }

            if(ErbData.has_eventspecinfo())
            {
                std::string strcauseVal = ErbData.eventspecinfo();
                uint8_t remId[NYBBLE_SIZE-2] = {0};
                int len = IWFUtils::StringToTBCD(strcauseVal, remId,strlen(strcauseVal.c_str()), 0, false);
                string hexString((const char*)remId,len);

                TransCustomAvp::CAPERBSEventSpecificInformation capERBSpecInfo(hexString);
                capERInfo.setCAPERBSEventSpecificInformation(capERBSpecInfo);
                //DLOG_INFO("CAPERBEventSpecificInformation : %s",capERInfo.getCAPERBSEventSpecificInformation().value().c_str());
            }
            capInfo.setCAPERBSInformation(capERInfo);
        }
        /*if(userData->HasCUGInformation())
        {
            Ro_TSL::MMTelInformation mmtelinfo;
            Ro_TSL::SupplementaryService ss;
            Ro_TSL::CUGInformation* cuginfo = userData->GetCUGInformation();
            ss.setCUGInformation(*cuginfo);
            mmtelinfo.addSupplementaryService(ss);
            si.setMMTelInformation(mmtelinfo);
        }*/
        StoredIDPSMSToCCRIData ccriAvpVal;
        ccriAvpVal.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
        GetCCRIAvpVal(capInfo,ccriAvpVal);
        csInfo.setCAPInformation(capInfo);
        si.setCSInformation(csInfo);
        if(ccriAvpVal.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriAvpVal.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType
                        ((Ro_TSL::SubscriptionIdType::Value)ccriAvpVal.subscriptionidinfo().subidtype()));
            }
            if(ccriAvpVal.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriAvpVal.subscriptionidinfo().subiddata()));
            }
            ccr->addSubscriptionId(subsId);
        }
    }

    mscc.addUsedServiceUnit(usu);
    ccr->setServiceInformation(si);
    ccr->addMultipleServicesCreditControl(mscc);

    /*Setting MultipleServicesIndicator set to Supported */
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    ccr->setMultipleServicesIndicator(msi);

    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
    SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetStoredIDPSMSToCCRIData().cap_service_key(), ccr);
    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
    cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);
    if (userData->IsRetransmissionEnabled())
    {
        DIA_HDR &diaHdr = (DIA_HDR &)cmd->getHeader();
        diaHdr.flags.t = 1;
    }

    m_dccaHandler.HandleRequest(userData->GetDccaContext(),
            cmd, Ro_TSL::CCRequestType::TERMINATION_REQUEST);

    LogRoTslDiaMsg(*ccr, false);

    //DLOG_DEBUG("BuildCCRTerminateForIDPSMS -- Exit");

    return rc;
}

int TransatelCAPToRoHandler::BuildCCRTerminateForIDP(IwfFsm *ctxt,
        diameter::base::TerminationCause::Value causeCode,
        DIA_BASE_CMD *&cmd, uint32_t ccTime)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;

    //DLOG_DEBUG("BuildCCRTerminateForIDP-- Entry");

    /* Stop all timers  before sending CCR-T*/
    ctxt->StopAllTimers();

    /* Releaseing all invokeIds stoerd in the vector */
    ReleaseStoredInvokeIds(ctxt);

    Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
    Ro_TSL::ServiceInformation si;
    Ro_TSL::UsedServiceUnit usu;
    Ro_TSL::MultipleServicesCreditControl mscc;
    TransCustomAvp::CAPInformation capInfo;
    TransCustomAvp::CSInformation csInfo;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    ccr->setAuthApplicationId(authApplicationId);

    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
    ccr->setCCRequestType(ccRequestType);

    ctxt->SetFinalUpstrmReqSent(true);

    diameter::base::TerminationCause terminationCause(causeCode);
    ccr->setTerminationCause(terminationCause);

    //usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));
    usu.setCCTime(Ro_TSL::CCTime((diameter::Unsigned32)ccTime));
    mscc.addUsedServiceUnit(usu);

    if(userData)
    {
        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
        userData->SetTerminationCause(causeCode);

        if (userData->IsRetransmissionEnabled())
        {
            //DLOG_DEBUG("Setting T-bit for retransmission and retaining same CCR-Request number ");
            ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(--ccrnum);
            ccr->setCCRequestNumber(ccRequestNumber);

        }
        else
        {
            ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
            ccr->setCCRequestNumber(ccRequestNumber);
            userData->SetCCRequestNumber(ccrnum);
        }

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro_TSL::ServiceIdentifier(serviden));
        }

        ITS_UINT seconds = this->GetCurrentTimeStamp();
        diameter::base::EventTimestamp eventTimestamp(seconds);
        ccr->setEventTimestamp(eventTimestamp);

        if(userData->HasServiceContextId())
        {
            Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
            ccr->setServiceContextId(serviceContextId);
        }

        /* Only if  ERB msg is recv populate the CAP-ERBS-Information AVP*/
        if(true == userData->IsFirstERBrcvd())
        {
            pbERBData erbData;
            TransCustomAvp::CAPERBSInformation capErbInfo;
            erbData.CopyFrom(userData->GetERBData());
            RetrieveERBData(capErbInfo, erbData);
            if((userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_OANSWER != erbData.erbrecvevttype())) ||
                    (!userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_TANSWER != erbData.erbrecvevttype())))
            {
                capInfo.setCAPERBSInformation(capErbInfo);
            }
        }


        IDPToCCRIData ccriData;
        ccriData.CopyFrom(userData->GetIDPToCCRIData());
        RetrieveIDPToCCRIData(capInfo, ccriData);
        csInfo.setCAPInformation(capInfo);
        si.setCSInformation(csInfo);
        if(ccriData.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriData.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType((Ro_TSL::SubscriptionIdType::Value)ccriData.subscriptionidinfo().subidtype()));
            }
            if(ccriData.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriData.subscriptionidinfo().subiddata()));
            }
            ccr->addSubscriptionId(subsId);
        }
    }

    ccr->setServiceInformation(si);
    ccr->addMultipleServicesCreditControl(mscc);

    /*Setting MultipleServicesIndicator set to Supported */
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    ccr->setMultipleServicesIndicator(msi);

    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
    SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetIDPToCCRIData().service_key(), ccr);
    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
    cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);
    if (userData->IsRetransmissionEnabled())
    {
        DIA_HDR &diaHdr = (DIA_HDR &)cmd->getHeader();
        diaHdr.flags.t = 1;
    }

    m_dccaHandler.HandleRequest(userData->GetDccaContext(),
            cmd, Ro_TSL::CCRequestType::TERMINATION_REQUEST);

    LogRoTslDiaMsg(*ccr, false);

    //DLOG_DEBUG("BuildCCRTerminateForIDP-- Exit");

    return rc;
}


#if 0
void TransatelCAPToRoHandler:: EventReportBCSM_to_CCR_Terminate( IwfFsm *ctxt,
        const cap_v3::EventReportBCSMArg *in,
        Ro_TSL::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    DLOG_DEBUG("ERB to CCR-Terminate");

    Ro_TSL::MultipleServicesCreditControl mscc;
    Ro_TSL::UsedServiceUnit usu;
    Ro_TSL::ServiceInformation si;
    Ro_TSL::IMSInformation imsinfo;

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
    out->setCCRequestType(ccRequestType);

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    usu.setReportingReason(Ro_TSL::ReportingReason(Ro_TSL::ReportingReason::FINAL));
    mscc.addUsedServiceUnit(usu);

    //NOTE: setting CauseCode
    imsinfo.setCauseCode(Ro_TSL::CauseCode(NORMAL_END_OF_SESSION));

    if(userData)
    {

        ccrnum = userData->GetCCRequestNumber();
        Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro_TSL::ServiceIdentifier(serviden));
        }

        uint32_t sec = ConstructTimeStamp(userData);
        diameter::base::EventTimestamp eventTimestamp(sec);
        out->setEventTimestamp(eventTimestamp);

        //NOTE: setting Role Of Node
        if(userData->GetBcsmEventMO())
            imsinfo.setRoleOfNode(Ro_TSL::RoleOfNode(Ro_TSL::RoleOfNode::ORIGINATING_ROLE));
        else
            imsinfo.setRoleOfNode(Ro_TSL::RoleOfNode(Ro_TSL::RoleOfNode::TERMINATING_ROLE));

        if(userData->HasUserSessionId())
        {
            Ro_TSL::UserSessionID* sessionId = userData->GetUserSessionID();
            imsinfo.setUserSessionID(*sessionId);
        }

        if(userData->HasIMSChargingIdentifier())
        {
            Ro_TSL::IMSChargingIdentifier* imsci = userData->GetIMSChargingIdentifier();
            imsinfo.setIMSChargingIdentifier(*imsci);
        }

        if(userData->HasServiceContextId())
        {
            Ro_TSL::ServiceContextId* serviceContextId = userData->GetServiceContextId();
            out->setServiceContextId(*serviceContextId);
        }

        if(userData->HasSubscriptionId())
        {
            Ro_TSL::SubscriptionId* subsId = userData->GetSubscriptionId();
            out->addSubscriptionId(*subsId);
        }

        if(userData->HasCUGInformation())
        {
            Ro_TSL::MMTelInformation mmtelinfo;
            Ro_TSL::SupplementaryService ss;
            Ro_TSL::CUGInformation* cuginfo = userData->GetCUGInformation();
            ss.setCUGInformation(*cuginfo);
            mmtelinfo.addSupplementaryService(ss);
            si.setMMTelInformation(mmtelinfo);
        }
    }

    /* Node-Functionality AVP to be populate from Configuration file */
    /*if(m_config.IsNodeFunctionalityFlagSet())
      {
      Ro_TSL::NodeFunctionality nodeFunct((Ro_TSL::NodeFunctionality::Value)m_config.NodeFunctionality());
      imsinfo.setNodeFunctionality(nodeFunct);
      }*/

    if(userData && userData->IsASRReceived())
    {
        userData->SetASRReceived(false);
        out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE));
        userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE);
    }
    else
    {
        out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));
        if(userData)
        {
            userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT);
        }
    }
    si.setIMSInformation(imsinfo);
    out->setServiceInformation(si);
    out->addMultipleServicesCreditControl(mscc);

}
#endif

int TransatelCAPToRoHandler::BuildRRB(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildRRB -- Entry");
    int rc = ITS_SUCCESS;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    try
    {

        cap_v2::RequestReportBCSMEventArg v2rrbArg;
        cap_v1::RequestReportBCSMEventArg v1rrbArg;
        Octets* buf = NULL;
        switch(userData->GetRecvAppCtxt())
        {
            case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
                {
                    CCA_Initial_to_V2RequestReportBCSMEvent(userData->GetCallType(),v2rrbArg,userData->GetNoAnsTime(),ctxt->GetActionRuleName());
                    buf = v2rrbArg.Encode();
                    LogCAPTslAsnObj(v2rrbArg, false);
                }
                break;
            case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
                {
                    CCA_Initial_to_V1RequestReportBCSMEvent(userData->GetCallType(),v1rrbArg,ctxt->GetActionRuleName());
                    buf = v1rrbArg.Encode();
                    LogCAPTslAsnObj(v1rrbArg, false);
                }
                break;
            default :
                {
                    break;
                }

        }

        if (buf == NULL)
        {
            ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
            DLOG_ERROR("### ASN Encode Error ### NULL Encode");
            return !ITS_SUCCESS;
        }

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
    //DLOG_DEBUG("BuildRRB -- Exit");
    if(rc == ITS_SUCCESS)
    {
        /* Setting this timerFlag to check in transactionManager whether
         * to start NoEventTimer or not */
        ctxt->SetStartNoEventTimer(true);
    }
    return rc;
}

int TransatelCAPToRoHandler::BuildConnect(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildConnect-- Entry");
    int rc = ITS_SUCCESS;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    try
    {
        cap_v2::ConnectArg v2connectArg;
        cap_v1::ConnectArg v1connectArg;
        Octets* buf = NULL;
        StoreConnectArgDataInUserData(ctxt, cca);

        switch(userData->GetRecvAppCtxt())
        {
            case cap::CAPV2_gsmSSF_to_gsmSCF_AC :
                {
                    CCA_Initial_to_ConnectV2(ctxt, cca, v2connectArg);
                    buf = v2connectArg.Encode();
                    LogCAPTslAsnObj(v2connectArg, false);
                }
                break;
            case cap::CAPV1_gsmSSF_to_gsmSCF_AC :
                {
                    CCA_Initial_to_ConnectV1(ctxt, cca, v1connectArg);
                    buf = v1connectArg.Encode();
                    LogCAPTslAsnObj(v1connectArg, false);
                }
                break;
            default :
                {
                    break;
                }

        }
        UPDATE_SSG_STATS_CONNECT_ARG_SENT;
        TCAP_Invoke *ivk = new TCAP_Invoke();
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_connect);
        ivk->SetParameter(buf->GetArray());
        cpt = ivk;
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }
    }

    catch(AsnEncodeError &exc)
    {
        ctxt->SetErrorCode(ITS_EASNENCODE);
        DLOG_ERROR("### ASN Encode Error ### <%s>", exc.GetDescription().c_str());
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        ctxt->SetErrorCode(ITS_EASNENCODE);
        rc = !ITS_SUCCESS;
        DLOG_ERROR("BuildConnect Unknown Exception");
    }
    //DLOG_DEBUG("BuildConnect -- Exit");
    return rc;
}

void TransatelCAPToRoHandler::CCA_Initial_to_ConnectV2(IwfFsm *ctxt,
        const Ro_TSL::CreditControlAnswer *in,
        cap_v2::ConnectArg& out)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CCA_Initial_to_ConnectV2 -- Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());


    pbConnectArgData connArg;
    connArg.CopyFrom(userData->GetConnectArgData());

    if(connArg.hasservicecontrol())
    {
        if(connArg.hascapinfo())
        {
            if(connArg.hascapconnectinfo())
            {

                uint8_t destRoutAddr[12] = {0};
                switch(userData->GetSCPAction())
                {
                    case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON  :
                        {
                            std::string capConnAnnounceNo = "";
                            unsigned capConnAnnounceNoNature = m_config.GetAnnNoNOA();
                            unsigned capConnAnnNumberINN = m_config.GetAnnNoINN();
                            unsigned capConnAnnNumberNPI = m_config.GetAnnNoNPI();

                            if(connArg.has_capanncaccessno())
                            {
                                capConnAnnounceNo =  connArg.capanncaccessno();
                                /* Encoding Address Digits form the 3rd Octet in DestinationRoutingAddress */
                                //DLOG_DEBUG("CAP-Connect-Destination-Number : %s", capConnAnnounceNo.c_str());

                                if(capConnAnnounceNo.length() > 20)
                                {
                                    capConnAnnounceNo.erase(20, std::string::npos);
                                }

                                if((capConnAnnounceNo.length() % 2))
                                {
                                    /* If the Address digits are odd setting the last nibble of last Octet
                                     * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                                     * odd else 0*/
                                    destRoutAddr[(capConnAnnounceNo.length() / 2)] |= 0x00;
                                    destRoutAddr[0] = 0x80;
                                }

                                if(connArg.has_capconnanncnonatrue())
                                    capConnAnnounceNoNature = connArg.capconnanncnonatrue();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-nature : %d", capConnAnnounceNoNature);
                                /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of DestinationRoutingAddress */
                                destRoutAddr[0] |= (capConnAnnounceNoNature & 0x7f);

                                //DLOG_DEBUG("Ann CAP-Connect-Destination-Number-NPI : %d", capConnAnnNumberNPI);
                                /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= ((capConnAnnNumberNPI & 0x07) << 4);


                                //DLOG_DEBUG("Announcement No CAP-Connect-Destination-Number-INN : %d", capConnAnnNumberINN);
                                /* Encoding INN. into 8 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= (capConnAnnNumberINN << 7);

                                int len = IWFUtils::StringToTBCD(capConnAnnounceNo, (destRoutAddr+2), capConnAnnounceNo.length());
                                cap_v2::DestinationRoutingAddress destRoutAdd;
                                cap_v2::CalledPartyNumber calledPartyNum(IWFUtils::ByteArrayToVector(destRoutAddr, (len+2)));
                                destRoutAdd.AddElement(calledPartyNum);
                                out.SetDestinationRoutingAddress(destRoutAdd);
                            }
                            /*else
                            {
                                DLOG_ERROR("Mandatory avp missing for construction CAP-Connect-Arg" \
                                        "CAPAnnouncementAccessNumber");
                            }*/
                            break;
                        }
                    case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT     :
                    case TransCustomAvp::SCPAction::CONNECT :
                        {
                            std::string capConnDestNo = "";
                            unsigned capConnDestNoNature = m_config.GetDestNoNOA();
                            unsigned capConnDestNoNPI = m_config.GetDestNoNPI();
                            unsigned int capConnDestINN = m_config.GetDestNoINN();
                            if(connArg.has_capconndestno())
                            {
                                if(connArg.has_capconndestnonpi())
                                    capConnDestNoNPI = connArg.capconndestnonpi();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-NPI : %d", capConnDestNoNPI);
                                /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= ((capConnDestNoNPI & 0x07) << 4);

                                capConnDestNo =  connArg.capconndestno();
                                /* Encoding Address Digits form the 3rd Octet in DestinationRoutingAddress */
                                //DLOG_DEBUG("CAP-Connect-Destination-Number : %s", capConnDestNo.c_str());

                                if(capConnDestNo.length() > 20)
                                {
                                    capConnDestNo.erase(20, std::string::npos);
                                }

                                if((capConnDestNo.length() % 2))
                                {
                                    /* If the Address digits are odd setting the last nibble of last Octet
                                     * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                                     * odd else 0*/
                                    destRoutAddr[(capConnDestNo.length() / 2)] |= 0x00;
                                    destRoutAddr[0] = 0x80;
                                }
                                if(connArg.has_capconndestnonature())
                                    capConnDestNoNature = connArg.capconndestnonature();

                                //DLOG_DEBUG("CAP-Connect-Destination-Number-nature : %d", capConnDestNoNature);
                                /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of DestinationRoutingAddress */
                                destRoutAddr[0] |= (capConnDestNoNature & 0x7f);

                                if(connArg.has_capconndestinn())
                                    capConnDestINN = connArg.capconndestinn();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-INN : %d", capConnDestINN);
                                /* Encoding INN. into 8 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= (capConnDestINN << 7);

                                int len = IWFUtils::StringToTBCD(capConnDestNo, (destRoutAddr+2), capConnDestNo.length());
                                cap_v2::DestinationRoutingAddress destRoutAdd;
                                cap_v2::CalledPartyNumber calledPartyNum(IWFUtils::ByteArrayToVector(destRoutAddr, (len+2)));
                                destRoutAdd.AddElement(calledPartyNum);
                                out.SetDestinationRoutingAddress(destRoutAdd);
                            }
                            break;
                        }
                    default :
                        {
                        }
                }

                uint8_t genericNumber[11] = {0};
                std::string genericNum = "";
                unsigned genericNoNature = m_config.GetGenericNumNOA();
                unsigned genericNoNPI = m_config.GetGenericNumNPI();
                unsigned genericNoNII = m_config.GetGenericNumNII();
                unsigned genericNoARI = m_config.GetGenericNumARI();
                unsigned genericNoSCI = m_config.GetGenericNumSCI();
                unsigned genericNoNQI = m_config.GetGenericNumNQI();

                if(connArg.has_genericno())
                {
                    if(connArg.has_genericnonqi())
                    {
                        genericNoNQI = connArg.genericnonqi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NQI : %d", genericNoNQI);
                    /* Encoding Number Qualifier Indicator to the first Octet of GenericNumber */
                    genericNumber[0] = (genericNoNQI & 0xff);

                    if(connArg.has_genericnonii())
                    {
                        genericNoNII = connArg.genericnonii();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NII : %d", genericNoNII);
                    /* Encoding Number Incomplete Indicator into MSB of GenericNumber 2nd Octet */
                    genericNumber[2] = ((genericNoNII & 0x01) << 7);

                    if(connArg.has_genericnonpi())
                    {
                        genericNoNPI = connArg.genericnonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NPI : %d", genericNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 3rd Octet of GenericNumber*/
                    genericNumber[2] |= ((genericNoNPI & 0x07) << 4);

                    if(connArg.has_genericnoari())
                    {
                        genericNoARI = connArg.genericnoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-ARI : %d", genericNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 3 Octet of Generic Number*/
                    genericNumber[2] |= ((genericNoARI & 0x03) << 2);

                    if(connArg.has_genericnosci())
                    {
                        genericNoSCI = connArg.genericnosci();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-SCI : %d", genericNoSCI);
                    /*Encoding Screening Indicator into First 2 bits of 3rd Octet of
                     * Generic Number*/
                    genericNumber[2] |= (genericNoSCI & 0x03) ;

                    genericNum =  connArg.genericno();
                    //DLOG_DEBUG("CAP-Connect-Generic-Number : %s", genericNum.c_str());

                    if(genericNum.length() > 16)
                    {
                        genericNum.erase(16, std::string::npos);
                    }

                    if(genericNum.length() % 2)
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        genericNumber[(genericNum.length() / 2)] |= 0x00;
                        genericNumber[1] = 0x80;
                    }

                    if(connArg.has_genericnonature())
                    {
                        genericNoNature = connArg.genericnonature();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-nature : %d", genericNoNature);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 2nd octet of GenericNumber*/
                    genericNumber[1] |= (genericNoNature & 0x7f);

                    int len = IWFUtils::StringToTBCD(genericNum, (genericNumber+3), genericNum.length());
                    cap_v2::GenericNumbers genericNums;
                    cap_v2::GenericNumber genNum(IWFUtils::ByteArrayToVector(genericNumber, (len+3)));
                    genericNums.AddElement(genNum);
                    out.SetGenericNumbers(genericNums);
                }

                if(connArg.has_capconncallingcategory())
                {
                    unsigned callingPartysCat = connArg.capconncallingcategory();
                    //DLOG_DEBUG("CAP-Connect-Calling-Category : %d", callingPartysCat);
                    /* Encoding the CAllingPartysCategory with first octet of incoming CAPConnectCallingCategory */
                    byte array[] = {(byte)(callingPartysCat & 0xff)};
                    cap_v2::CallingPartysCategory callPartysCat(ArrayToVector(array, ARRAY_SIZE(array)));
                    out.SetCallingPartysCategory(callPartysCat);
                }

                uint8_t redirectingPrtyId[12] = {0};
                std::string redirectingNum = "";
                unsigned redirectNoNOA = m_config.GetRedirectNumNOA();
                unsigned redirectNoNPI = m_config.GetRedirectNumNPI();
                unsigned redirectNoARI = m_config.GetRedirectNumARI();
                if(connArg.has_redirectingnum())
                {
                    if(connArg.has_redirectnonpi())
                    {
                        redirectNoNPI = connArg.redirectnonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-NPI : %d", redirectNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of RedierctingPartyId*/
                    redirectingPrtyId[1] = ((redirectNoNPI & 0x07) << 4);

                    if(connArg.has_redirectnoari())
                    {
                        redirectNoARI = connArg.redirectnoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-ARI : %d", redirectNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 2 Octet of RedirectingPartyId*/
                    redirectingPrtyId[1] |= ((redirectNoARI & 0x03) << 2);

                    redirectingNum =  connArg.redirectingnum();
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Party-Id : %s", redirectingNum.c_str());

                    if(redirectingNum.length() > 20)
                    {
                        redirectingNum.erase(20, std::string::npos);
                    }

                    if((redirectingNum.length() % 2))
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        redirectingPrtyId[(redirectingNum.length() / 2)] |= 0x00;
                        redirectingPrtyId[0] = 0x80;
                    }

                    if(connArg.has_redirectnonoa())
                    {
                        redirectNoNOA = connArg.redirectnonoa();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-NOA : %d", redirectNoNOA);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of RedirectingPartyId*/
                    redirectingPrtyId[0] |= (redirectNoNOA & 0x7f);

                    int len = IWFUtils::StringToTBCD(redirectingNum, (redirectingPrtyId+2), redirectingNum.length());
                    cap_v2::RedirectingPartyID rpId(IWFUtils::ByteArrayToVector(redirectingPrtyId, (len+2)));
                    out.SetRedirectingPartyID(rpId);
                }

                uint8_t redirectionInfo[2] = {0};
                if(connArg.has_redirectind() &&
                        connArg.has_origredirectreason() &&
                        connArg.has_redirectioncount() &&
                        connArg.has_redirectreason())
                {
                    unsigned redirectInd = connArg.redirectind();
                    /* Extracting the first 3 bits of CAPConnectRedirectingIndicator and encoding
                     * it into 1st 3 bits of 1st Octet of redirectionInformation */
                    redirectionInfo[0] |= (redirectInd & 0x7);

                    unsigned origRedirectReason = connArg.origredirectreason();
                    /* Extracting the 1st 4 bits of CAPConnectOriginalRedirectionReason and encoding
                     * it into higher nibble of 1st octet of redirectionInformation  */
                    redirectionInfo[0] |= ((origRedirectReason & 0xf) << 4);

                    unsigned redirectionCount = connArg.redirectioncount();
                    /* Extracting the first 3 bits of CAPConnectRedirectionCounter and encoding
                     * it into 1st 3 bits of 2nd Octet of redirectionInformation */
                    redirectionInfo[1] |= (redirectionCount & 0x7);

                    unsigned redirectReason = connArg.redirectreason();
                    /* Extracting the 1st 4 bits of CAPConnectRedirectingReason and encoding
                     * it into higher nibble of 2nd octet of redirectionInformation  */
                    redirectionInfo[1] |= ((redirectReason & 0xf) << 4);
                    cap_v2::RedirectionInformation redirectInfo(IWFUtils::ByteArrayToVector(redirectionInfo, 2));
                    out.SetRedirectionInformation(redirectInfo);
                }

                uint8_t origCldPartyId[10] = {0};
                std::string origCalledPartyId = "";
                unsigned int originalCalledNoNPI = m_config.GetOrgCalledNumNPI();
                unsigned int originalCalledNoNOA = m_config.GetOrgCalledNumNOA();
                unsigned int originalCalledNoARI = m_config.GetOrgCalledNumARI();
                if(connArg.has_origcalledpartyid())
                {
                    if(connArg.has_originalcallednonpi())
                    {
                        originalCalledNoNPI = connArg.originalcallednonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-NPI : %d", originalCalledNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of OriginalCalledNumber*/
                    origCldPartyId[1] = ((originalCalledNoNPI & 0x07) << 4);

                    if(connArg.has_originalcallednoari())
                    {
                        originalCalledNoARI = connArg.originalcallednoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-ARI : %d", originalCalledNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 2 Octet of OriginalCalledNumber*/
                    origCldPartyId[1] |= ((originalCalledNoARI & 0x03) << 2);

                    origCalledPartyId =  connArg.origcalledpartyid();
                    //DLOG_DEBUG("CAPConnectOriginalCalledNumber: %s", origCalledPartyId.c_str());

                    if(origCalledPartyId.length() > 16)
                    {
                        origCalledPartyId.erase(16, std::string::npos);
                    }

                    if((origCalledPartyId.length() % 2))
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        origCldPartyId[(origCalledPartyId.length() / 2)] |= 0x00;
                        origCldPartyId[0] = 0x80;
                    }

                    if(connArg.has_originalcallednonoa())
                    {
                        originalCalledNoNOA = connArg.originalcallednonoa();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-NOA : %d", originalCalledNoNOA);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of OriginalCalledNumber*/
                    origCldPartyId[0] |= (originalCalledNoNOA & 0x7f);


                    int len = IWFUtils::StringToTBCD(origCalledPartyId, (origCldPartyId+2), origCalledPartyId.length());
                    cap_v2::OriginalCalledPartyID ocpId(IWFUtils::ByteArrayToVector(origCldPartyId, (len+2)));
                    out.SetOriginalCalledPartyID(ocpId);
                }

                if(connArg.has_capconnocsiapplicable())
                {
                    if(connArg.capconnocsiapplicable())
                    {
                        cap_v2::OCSIApplicable oCSIApplicable;
                        out.SetOCSIApplicable(oCSIApplicable);
                    }
                }

                if(connArg.has_capconnsuppressionofannc())
                {
                    if(connArg.capconnsuppressionofannc())
                    {
                        cap_v2::SuppressionOfAnnouncement suppressAnnounc;
                        out.SetSuppressionOfAnnouncement(suppressAnnounc);
                    }
                }
            }
        }
    }
    //DLOG_DEBUG("CCA_Initial_to_ConnectV2 -- Exit");
}

void TransatelCAPToRoHandler::CCA_Initial_to_ConnectV1(IwfFsm *ctxt,
        const Ro_TSL::CreditControlAnswer *in,
        cap_v1::ConnectArg& out)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CCA_Initial_to_ConnectV1 -- Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    pbConnectArgData connArg;
    connArg.CopyFrom(userData->GetConnectArgData());

    if(connArg.hasservicecontrol())
    {
        if(connArg.hascapinfo())
        {
            if(connArg.hascapconnectinfo())
            {

                uint8_t destRoutAddr[12] = {0};
                switch(userData->GetSCPAction())
                {
                    case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON  :
                        {
                            std::string capConnAnnounceNo = "";
                            unsigned capConnAnnounceNoNature = m_config.GetAnnNoNOA();
                            unsigned capConnAnnNumberINN = m_config.GetAnnNoINN();
                            unsigned capConnAnnNumberNPI = m_config.GetAnnNoNPI();

                            if(connArg.has_capanncaccessno())
                            {
                                capConnAnnounceNo =  connArg.capanncaccessno();
                                /* Encoding Address Digits form the 3rd Octet in DestinationRoutingAddress */
                                //DLOG_DEBUG("CAP-Connect-Destination-Number : %s", capConnAnnounceNo.c_str());

                                if(capConnAnnounceNo.length() > 20)
                                {
                                    capConnAnnounceNo.erase(20, std::string::npos);
                                }

                                if((capConnAnnounceNo.length() % 2))
                                {
                                    /* If the Address digits are odd setting the last nibble of last Octet
                                     * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                                     * odd else 0*/
                                    destRoutAddr[(capConnAnnounceNo.length() / 2)] |= 0x00;
                                    destRoutAddr[0] = 0x80;
                                }

                                if(connArg.has_capconnanncnonatrue())
                                    capConnAnnounceNoNature = connArg.capconnanncnonatrue();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-nature : %d", capConnAnnounceNoNature);
                                /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of DestinationRoutingAddress */
                                destRoutAddr[0] |= (capConnAnnounceNoNature & 0x7f);

                                //DLOG_DEBUG("Ann CAP-Connect-Destination-Number-NPI : %d", capConnAnnNumberNPI);
                                /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= ((capConnAnnNumberNPI & 0x07) << 4);


                                //DLOG_DEBUG("Announcement No CAP-Connect-Destination-Number-INN : %d", capConnAnnNumberINN);
                                /* Encoding INN. into 8 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= (capConnAnnNumberINN << 7);

                                int len = IWFUtils::StringToTBCD(capConnAnnounceNo, (destRoutAddr+2), capConnAnnounceNo.length());
                                cap_v1::DestinationRoutingAddress destRoutAdd;
                                cap_v1::CalledPartyNumber calledPartyNum(IWFUtils::ByteArrayToVector(destRoutAddr, (len+2)));
                                destRoutAdd.AddElement(calledPartyNum);
                                out.SetDestinationRoutingAddress(destRoutAdd);
                            }
                            /*else
                            {
                                DLOG_ERROR("Mandatory avp missing for construction CAP-Connect-Arg" \
                                        "CAPAnnouncementAccessNumber");
                            }*/
                            break;
                        }
                    case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT     :
                    case TransCustomAvp::SCPAction::CONNECT :
                        {
                            std::string capConnDestNo = "";
                            unsigned capConnDestNoNature = m_config.GetDestNoNOA();
                            unsigned capConnDestNoNPI = m_config.GetDestNoNPI();
                            unsigned int capConnDestINN = m_config.GetDestNoINN();
                            if(connArg.has_capconndestno())
                            {
                                if(connArg.has_capconndestnonpi())
                                    capConnDestNoNPI = connArg.capconndestnonpi();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-NPI : %d", capConnDestNoNPI);
                                /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= ((capConnDestNoNPI & 0x07) << 4);

                                capConnDestNo =  connArg.capconndestno();
                                /* Encoding Address Digits form the 3rd Octet in DestinationRoutingAddress */
                                //DLOG_DEBUG("CAP-Connect-Destination-Number : %s", capConnDestNo.c_str());

                                if(capConnDestNo.length() > 20)
                                {
                                    capConnDestNo.erase(20, std::string::npos);
                                }

                                if((capConnDestNo.length() % 2))
                                {
                                    /* If the Address digits are odd setting the last nibble of last Octet
                                     * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                                     * odd else 0*/
                                    destRoutAddr[(capConnDestNo.length() / 2)] |= 0x00;
                                    destRoutAddr[0] = 0x80;
                                }
                                if(connArg.has_capconndestnonature())
                                    capConnDestNoNature = connArg.capconndestnonature();

                                //DLOG_DEBUG("CAP-Connect-Destination-Number-nature : %d", capConnDestNoNature);
                                /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of DestinationRoutingAddress */
                                destRoutAddr[0] |= (capConnDestNoNature & 0x7f);

                                if(connArg.has_capconndestinn())
                                    capConnDestINN = connArg.capconndestinn();
                                //DLOG_DEBUG("CAP-Connect-Destination-Number-INN : %d", capConnDestINN);
                                /* Encoding INN. into 8 bits of 2nd Octet of DestinationRoutingAddress */
                                destRoutAddr[1] |= (capConnDestINN << 7);

                                int len = IWFUtils::StringToTBCD(capConnDestNo, (destRoutAddr+2), capConnDestNo.length());
                                cap_v1::DestinationRoutingAddress destRoutAdd;
                                cap_v1::CalledPartyNumber calledPartyNum(IWFUtils::ByteArrayToVector(destRoutAddr, (len+2)));
                                destRoutAdd.AddElement(calledPartyNum);
                                out.SetDestinationRoutingAddress(destRoutAdd);
                            }
                            break;
                        }
                    default :
                        {
                        }
                }

                uint8_t genericNumber[11] = {0};
                std::string genericNum = "";
                unsigned genericNoNature = m_config.GetGenericNumNOA();
                unsigned genericNoNPI = m_config.GetGenericNumNPI();
                unsigned genericNoNII = m_config.GetGenericNumNII();
                unsigned genericNoARI = m_config.GetGenericNumARI();
                unsigned genericNoSCI = m_config.GetGenericNumSCI();
                unsigned genericNoNQI = m_config.GetGenericNumNQI();

                if(connArg.has_genericno())
                {
                    if(connArg.has_genericnonqi())
                    {
                        genericNoNQI = connArg.genericnonqi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NQI : %d", genericNoNQI);
                    /* Encoding Number Qualifier Indicator to the first Octet of GenericNumber */
                    genericNumber[0] = (genericNoNQI & 0xff);

                    if(connArg.has_genericnonii())
                    {
                        genericNoNII = connArg.genericnonii();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NII : %d", genericNoNII);
                    /* Encoding Number Incomplete Indicator into MSB of GenericNumber 2nd Octet */
                    genericNumber[2] = ((genericNoNII & 0x01) << 7);

                    if(connArg.has_genericnonpi())
                    {
                        genericNoNPI = connArg.genericnonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-NPI : %d", genericNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 3rd Octet of GenericNumber*/
                    genericNumber[2] |= ((genericNoNPI & 0x07) << 4);

                    if(connArg.has_genericnoari())
                    {
                        genericNoARI = connArg.genericnoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-ARI : %d", genericNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 3 Octet of Generic Number*/
                    genericNumber[2] |= ((genericNoARI & 0x03) << 2);

                    if(connArg.has_genericnosci())
                    {
                        genericNoSCI = connArg.genericnosci();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-SCI : %d", genericNoSCI);
                    /*Encoding Screening Indicator into First 2 bits of 3rd Octet of
                     * Generic Number*/
                    genericNumber[2] |= (genericNoSCI & 0x03) ;

                    genericNum =  connArg.genericno();
                    //DLOG_DEBUG("CAP-Connect-Generic-Number : %s", genericNum.c_str());

                    if(genericNum.length() > 16)
                    {
                        genericNum.erase(16, std::string::npos);
                    }

                    if(genericNum.length() % 2)
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        genericNumber[(genericNum.length() / 2)] |= 0x00;
                        genericNumber[1] = 0x80;
                    }

                    if(connArg.has_genericnonature())
                    {
                        genericNoNature = connArg.genericnonature();
                    }
                    //DLOG_DEBUG("CAP-Connect-Generic-Number-nature : %d", genericNoNature);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 2nd octet of GenericNumber*/
                    genericNumber[1] |= (genericNoNature & 0x7f);

                    int len = IWFUtils::StringToTBCD(genericNum, (genericNumber+3), genericNum.length());
                    cap_v1::GenericNumbers genericNums;
                    cap_v1::GenericNumber genNum(IWFUtils::ByteArrayToVector(genericNumber, (len+3)));
                    genericNums.AddElement(genNum);
                    out.SetGenericNumbers(genericNums);
                }

                if(connArg.has_capconncallingcategory())
                {
                    unsigned callingPartysCat = connArg.capconncallingcategory();
                    //DLOG_DEBUG("CAP-Connect-Calling-Category : %d", callingPartysCat);
                    /* Encoding the CAllingPartysCategory with first octet of incoming CAPConnectCallingCategory */
                    byte array[] = {(byte)(callingPartysCat & 0xff)};
                    cap_v1::CallingPartysCategory callPartysCat(ArrayToVector(array, ARRAY_SIZE(array)));
                    out.SetCallingPartysCategory(callPartysCat);
                }

                uint8_t redirectingPrtyId[12] = {0};
                std::string redirectingNum = "";
                unsigned redirectNoNOA = m_config.GetRedirectNumNOA();
                unsigned redirectNoNPI = m_config.GetRedirectNumNPI();
                unsigned redirectNoARI = m_config.GetRedirectNumARI();
                if(connArg.has_redirectingnum())
                {
                    if(connArg.has_redirectnonpi())
                    {
                        redirectNoNPI = connArg.redirectnonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-NPI : %d", redirectNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of RedierctingPartyId*/
                    redirectingPrtyId[1] = ((redirectNoNPI & 0x07) << 4);

                    if(connArg.has_redirectnoari())
                    {
                        redirectNoARI = connArg.redirectnoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-ARI : %d", redirectNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 2 Octet of RedirectingPartyId*/
                    redirectingPrtyId[1] |= ((redirectNoARI & 0x03) << 2);

                    redirectingNum =  connArg.redirectingnum();
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Party-Id : %s", redirectingNum.c_str());

                    if(redirectingNum.length() > 20)
                    {
                        redirectingNum.erase(20, std::string::npos);
                    }

                    if((redirectingNum.length() % 2))
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        redirectingPrtyId[(redirectingNum.length() / 2)] |= 0x00;
                        redirectingPrtyId[0] = 0x80;
                    }

                    if(connArg.has_redirectnonoa())
                    {
                        redirectNoNOA = connArg.redirectnonoa();
                    }
                    //DLOG_DEBUG("CAP-Connect-Redirecting-Number-NOA : %d", redirectNoNOA);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of RedirectingPartyId*/
                    redirectingPrtyId[0] |= (redirectNoNOA & 0x7f);

                    int len = IWFUtils::StringToTBCD(redirectingNum, (redirectingPrtyId+2), redirectingNum.length());
                    cap_v1::RedirectingPartyID rpId(IWFUtils::ByteArrayToVector(redirectingPrtyId, (len+2)));
                    out.SetRedirectingPartyID(rpId);
                }

                uint8_t redirectionInfo[2] = {0};
                if(connArg.has_redirectind() &&
                        connArg.has_origredirectreason() &&
                        connArg.has_redirectioncount() &&
                        connArg.has_redirectreason())
                {
                    unsigned redirectInd = connArg.redirectind();
                    /* Extracting the first 3 bits of CAPConnectRedirectingIndicator and encoding
                     * it into 1st 3 bits of 1st Octet of redirectionInformation */
                    redirectionInfo[0] |= (redirectInd & 0x7);

                    unsigned origRedirectReason = connArg.origredirectreason();
                    /* Extracting the 1st 4 bits of CAPConnectOriginalRedirectionReason and encoding
                     * it into higher nibble of 1st octet of redirectionInformation  */
                    redirectionInfo[0] |= ((origRedirectReason & 0xf) << 4);

                    unsigned redirectionCount = connArg.redirectioncount();
                    /* Extracting the first 3 bits of CAPConnectRedirectionCounter and encoding
                     * it into 1st 3 bits of 2nd Octet of redirectionInformation */
                    redirectionInfo[1] |= (redirectionCount & 0x7);

                    unsigned redirectReason = connArg.redirectreason();
                    /* Extracting the 1st 4 bits of CAPConnectRedirectingReason and encoding
                     * it into higher nibble of 2nd octet of redirectionInformation  */
                    redirectionInfo[1] |= ((redirectReason & 0xf) << 4);
                    cap_v1::RedirectionInformation redirectInfo(IWFUtils::ByteArrayToVector(redirectionInfo, 2));
                    out.SetRedirectionInformation(redirectInfo);
                }

                uint8_t origCldPartyId[10] = {0};
                std::string origCalledPartyId = "";
                unsigned int originalCalledNoNPI = m_config.GetOrgCalledNumNPI();
                unsigned int originalCalledNoNOA = m_config.GetOrgCalledNumNOA();
                unsigned int originalCalledNoARI = m_config.GetOrgCalledNumARI();
                if(connArg.has_origcalledpartyid())
                {
                    if(connArg.has_originalcallednonpi())
                    {
                        originalCalledNoNPI = connArg.originalcallednonpi();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-NPI : %d", originalCalledNoNPI);
                    /* Encoding NumberingPlanInd. into 5-7 bits of 2nd Octet of OriginalCalledNumber*/
                    origCldPartyId[1] = ((originalCalledNoNPI & 0x07) << 4);

                    if(connArg.has_originalcallednoari())
                    {
                        originalCalledNoARI = connArg.originalcallednoari();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-ARI : %d", originalCalledNoARI);
                    /* Encoding Area Presentation Restricted Indicator into 3-4 bit of
                     * 2 Octet of OriginalCalledNumber*/
                    origCldPartyId[1] |= ((originalCalledNoARI & 0x03) << 2);

                    origCalledPartyId =  connArg.origcalledpartyid();
                    //DLOG_DEBUG("CAPConnectOriginalCalledNumber: %s", origCalledPartyId.c_str());

                    if(origCalledPartyId.length() > 16)
                    {
                        origCalledPartyId.erase(16, std::string::npos);
                    }

                    if((origCalledPartyId.length() % 2))
                    {
                        /* If the Address digits are odd setting the last nibble of last Octet
                         * to 0 and MSB of 1st Octet's MSB to 1 if number of Address Digits is
                         * odd else 0*/
                        origCldPartyId[(origCalledPartyId.length() / 2)] |= 0x00;
                        origCldPartyId[0] = 0x80;
                    }

                    if(connArg.has_originalcallednonoa())
                    {
                        originalCalledNoNOA = connArg.originalcallednonoa();
                    }
                    //DLOG_DEBUG("CAP-Connect-Original-Called-Number-NOA : %d", originalCalledNoNOA);
                    /* Encoding Nature of Address Ind. in the first 7 bits of 1st octet of OriginalCalledNumber*/
                    origCldPartyId[0] |= (originalCalledNoNOA & 0x7f);


                    int len = IWFUtils::StringToTBCD(origCalledPartyId, (origCldPartyId+2), origCalledPartyId.length());
                    cap_v1::OriginalCalledPartyID ocpId(IWFUtils::ByteArrayToVector(origCldPartyId, (len+2)));
                    out.SetOriginalCalledPartyID(ocpId);
                }

                if(connArg.has_capconnocsiapplicable())
                {
                    if(connArg.capconnocsiapplicable())
                    {
                        cap_v1::OCSIApplicable oCSIApplicable;
                        out.SetOCSIApplicable(oCSIApplicable);
                    }
                }

                if(connArg.has_capconnsuppressionofannc())
                {
                    if(connArg.capconnsuppressionofannc())
                    {
                        cap_v1::SuppressionOfAnnouncement suppressAnnounc;
                        out.SetSuppressionOfAnnouncement(suppressAnnounc);
                    }
                }
            }
        }
    }
    //DLOG_DEBUG("CCA_Initial_to_ConnectV1 -- Exit");
}

int TransatelCAPToRoHandler::BuildRRBSMS(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildRRBSMS -- Entry");
    int rc = ITS_SUCCESS;
    try
    {
        cap_v3::RequestReportSMSEventArg rrbsms;
        CCA_Initial_to_RequestReportSMSEvent(ctxt, cca, &rrbsms,ctxt->GetActionRuleName());
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

        LogCAPTslAsnObj(rrbsms, false);
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
    //DLOG_DEBUG("BuildRRBSMS -- Exit");

    if(rc == ITS_SUCCESS)
    {
        /* Setting this timerFlag to check in transactionManager whether
         * to start NoEventTimer or not */
        ctxt->SetStartNoEventTimer(true);
    }
    return rc;
}

int TransatelCAPToRoHandler::BuildACH(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildACH -- Entry");
    int rc = ITS_SUCCESS;
    try
    {
        cap_v2::ApplyChargingArg achArg;

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

        LogCAPTslAsnObj(achArg, false);
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

    //DLOG_DEBUG("BuildACH -- Exit");

    return rc;
}

int TransatelCAPToRoHandler::BuildContinue(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *in,
        TCAP_Component *&cpt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    //DLOG_DEBUG("BuildContinue -- Entry");
    TCAP_Invoke *ivk = new TCAP_Invoke();
    ivk->SetClass(TCAP_OPERATION_CLASS);
    ivk->SetOperation( cap:: OP_continue );
    cpt = ivk;
    //DLOG_DEBUG("BuildContinue -- Exit");
    return rc;
}

int TransatelCAPToRoHandler::BuildContinueSMS(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *in,
        TCAP_Component *&cpt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    //DLOG_DEBUG("BuildContinueSMS -- Entry");
    TCAP_Invoke *ivk = new TCAP_Invoke();
    ivk->SetClass(TCAP_OPERATION_CLASS);
    ivk->SetOperation( cap::OP_continueSMS);
    cpt = ivk;
    //DLOG_DEBUG("BuildContinueSMS -- Exit");
    return rc;
}

int TransatelCAPToRoHandler::BuildRelease(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *in,
        TCAP_Component *&cpt, byte causecode)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildRelease -- Entry");
    int rc = ITS_SUCCESS;
#if 0
    byte causeLoc = CAUSE_LOCATION_RLN;
#endif

    uint8_t causeOct[2] = {0};
    causeOct[0] |= (m_config.GetRelCauseLoc() & 0x4f);
    causeOct[0] |= ((m_config.GetRelCauseStd() & 0x07) << 5);
    causeOct[0] |= (m_config.GetRelCauseExtIndicator1()<<7);
    causeOct[1] |= ((unsigned int)causecode & 0x7f);
    causeOct[1] |= (m_config.GetRelCauseExtIndicator1() <<7);


    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    try
    {
#if 0

        /* IWF sends the ReleaseCall with Cause set to Normal Unspecified(31) by default */
        if( causecode == NORMAL_CALL_CLEARING )
        {
            causeLoc = CAUSE_LOCATION_USER;
        }
        byte array[] = {causeLoc, causecode };
        cap_v2::ReleaseCallArg releaseCall(ArrayToVector(array, ARRAY_SIZE(array)));
        Octets* buf = releaseCall.Encode();
#endif
        Octets* buf = NULL;

        if(cap::CAPV2_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
        {
            cap_v2::ReleaseCallArg releaseCall(IWFUtils::ByteArrayToVector(causeOct,2));
            buf = releaseCall.Encode();
            LogCAPTslAsnObj(releaseCall, false);
        }
        else if(cap::CAPV1_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
        {
            cap_v1::ReleaseCallArg releaseCall(IWFUtils::ByteArrayToVector(causeOct,2));
            buf = releaseCall.Encode();
            LogCAPTslAsnObj(releaseCall, false);
        }

        TCAP_Invoke *ivk = new TCAP_Invoke();
        ivk->SetClass(TCAP_OPERATION_CLASS);
        ivk->SetOperation(cap::OP_releaseCall);
        ivk->SetParameter(buf->GetArray());
        cpt = ivk;
        if(buf != NULL)
        {
            delete buf;
            buf = NULL;
        }
        //LogCAPTslAsnObj(releaseCall, false);
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
    //DLOG_DEBUG("BuildRelease -- Exit");
    return rc;
}

int TransatelCAPToRoHandler::BuildReleaseSMS(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *in,
        TCAP_Component *&cpt, byte causeCode)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("BuildReleaseSMS -- Entry");
    int rc = ITS_SUCCESS;
    try
    {
        /* IWF sends the ReleaseCall with Cause set to Normal Unspecified(31) */
        byte array[] = {causeCode};
        cap_v3::ReleaseSMSArg releaseSMS(ArrayToVector(array, ARRAY_SIZE(array)));
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
        LogCAPTslAsnObj(releaseSMS, false);
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
    //DLOG_DEBUG("BuildReleaseSMS -- Exit");
    return rc;
}



int TransatelCAPToRoHandler::BuildBcsmEvent(cap_v2::EventTypeBCSM eventType,
        cap_v2::MonitorMode monitorMode,
        std::string legid,
        cap_v2::BCSMEvent *bcsmEvent,
        unsigned int& uiNoAnsTimeout)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    cap_v2::EventTypeBCSM evtType(eventType);
    bcsmEvent->SetEventTypeBCSM(evtType);

    // Monitor-Mode ie should be mapped to notifyAndContinue or Interrupt
    cap_v2::MonitorMode mntMode(monitorMode);
    bcsmEvent->SetMonitorMode(mntMode);

    //LegID should be populated based on eventTypeBCSM
    std::vector<byte> vec = IWFUtils::StringToVector(legid);
    vec[0] = vec[0]&0xF;
    cap_v2::LegType lt(vec);
    cap_v2::LegID legId;
    legId.SetChoiceSendingSideID(lt);

    /*Only for O-TNoAnswer events arm the ApplicationTimer IE with CCA-I recv in CAP-RRBS-NoAnswerTimeout.
     * ApplicationTimer supported after  cap_v2 version.*/
    if(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER == eventType.GetValue() ||
            cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TNO_ANSWER == eventType.GetValue())
    {
        cap_v2::DPSpecificCriteria dpSpecInfo;
        cap_v2::ApplicationTimer camelNoAnsTimer(uiNoAnsTimeout);
        dpSpecInfo.SetChoiceApplicationTimer(camelNoAnsTimer);
        bcsmEvent->SetDPSpecificCriteria(dpSpecInfo);
    }

    bcsmEvent->SetLegID(legId);
    return rc;
}

int TransatelCAPToRoHandler::BuildBcsmEvent(cap_v1::EventTypeBCSM eventType,
        cap_v1::MonitorMode monitorMode,
        std::string legid,
        cap_v1::BCSMEvent *bcsmEvent)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    cap_v1::EventTypeBCSM evtType(eventType);
    bcsmEvent->SetEventTypeBCSM(evtType);

    // Monitor-Mode ie should be mapped to notifyAndContinue or Interrupt
    cap_v1::MonitorMode mtrMode(monitorMode);
    bcsmEvent->SetMonitorMode(mtrMode);

    //LegID should be populated based on eventTypeBCSM
    std::vector<byte> vec = IWFUtils::StringToVector(legid);
    vec[0] = vec[0]&0xF;
    cap_v1::LegType lt(vec);
    cap_v1::LegID legId;
    legId.SetChoiceSendingSideID(lt);

    bcsmEvent->SetLegID(legId);
    return rc;
}

void TransatelCAPToRoHandler::CCA_Initial_to_V2RequestReportBCSMEvent(Call_Type callTypeVal,
        cap_v2::RequestReportBCSMEventArg& rrbArg,
        unsigned int uiNoAnsTimeout,std::string rrbRuleId)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CCA_Initial_to_V2RequestReportBCSMEvent -- Entry");


    cap_v2::RequestReportBCSMEventArg::BcsmEvents reqReportingBcsmevent;


    /* MO Call,populate all the DPs related to 'O' */
    if (MO_VOICE == callTypeVal)
    {
        std::vector<TCAPV2Event_ArmData> eventLst;
        m_config.GetMOCAPV2_EventList(eventLst,rrbRuleId);

        for(unsigned j = 0 ; j < eventLst.size();j++)
        {
            TCAPV2Event_ArmData eventVal = eventLst[j];
            for(unsigned i = 0 ; i < eventVal.legIdMonMode.size();i++)
            {
                cap_v2::BCSMEvent bcsmEvent;
                BuildBcsmEvent(eventVal.eventType,
                        (cap_v2::MonitorMode)eventVal.legIdMonMode[i].monitorMode,
                        eventVal.legIdMonMode[i].legId,
                        &bcsmEvent,uiNoAnsTimeout);
                reqReportingBcsmevent.AddElement(bcsmEvent);

            }
        }
    }
    else if(MT_VOICE == callTypeVal)//if MT call populate all the DP's realted to 'T'
    {
        std::vector<TCAPV2Event_ArmData> eventLst;
        m_config.GetMTCAPV2_EventList(eventLst,rrbRuleId);

        for(unsigned j = 0 ; j < eventLst.size();j++)
        {
            TCAPV2Event_ArmData eventVal = eventLst[j];
            for(unsigned i = 0 ; i < eventVal.legIdMonMode.size();i++)
            {
                cap_v2::BCSMEvent bcsmEvent;
                BuildBcsmEvent(eventVal.eventType,
                        (cap_v2::MonitorMode)eventVal.legIdMonMode[i].monitorMode,
                        eventVal.legIdMonMode[i].legId,
                        &bcsmEvent,uiNoAnsTimeout);
                reqReportingBcsmevent.AddElement(bcsmEvent);

            }
        }
    }
    /*else
    {
        DLOG_ERROR("Unknown CallType : %d received", callTypeVal);
    }*/

    rrbArg.SetBcsmEvents(reqReportingBcsmevent);
    //DLOG_DEBUG("CCA_Initial_to_V2RequestReportBCSMEvent -- Exit");

}

void TransatelCAPToRoHandler::CCA_Initial_to_V1RequestReportBCSMEvent(Call_Type callTypeVal,
        cap_v1::RequestReportBCSMEventArg& rrbArg, std::string rrbRuleId)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CCA_Initial_to_V1RequestReportBCSMEvent -- Entry");


    cap_v1::RequestReportBCSMEventArg::BcsmEvents reqReportingBcsmevent;


    /* MO Call,populate all the DPs related to 'O' */
    if (MO_VOICE == callTypeVal)
    {
        std::vector<TCAPV1Event_ArmData> eventLst;
        m_config.GetMOCAPV1_EventList(eventLst,rrbRuleId);

        for(unsigned j = 0 ; j < eventLst.size();j++)
        {
            TCAPV1Event_ArmData eventVal = eventLst[j];
            for(unsigned i = 0 ; i < eventVal.legIdMonMode.size();i++)
            {
                cap_v1::BCSMEvent bcsmEvent;
                BuildBcsmEvent(eventVal.eventType,
                        (cap_v1::MonitorMode)eventVal.legIdMonMode[i].monitorMode,
                        eventVal.legIdMonMode[i].legId,
                        &bcsmEvent);
                reqReportingBcsmevent.AddElement(bcsmEvent);

            }
        }
    }
    else if(MT_VOICE == callTypeVal)//if MT call populate all the DP's realted to 'T'
    {
        std::vector<TCAPV1Event_ArmData> eventLst;
        m_config.GetMTCAPV1_EventList(eventLst,rrbRuleId);

        for(unsigned j = 0 ; j < eventLst.size();j++)
        {
            TCAPV1Event_ArmData eventVal = eventLst[j];
            for(unsigned i = 0 ; i < eventVal.legIdMonMode.size();i++)
            {
                cap_v1::BCSMEvent bcsmEvent;
                BuildBcsmEvent(eventVal.eventType,
                        (cap_v1::MonitorMode)eventVal.legIdMonMode[i].monitorMode,
                        eventVal.legIdMonMode[i].legId,
                        &bcsmEvent);
                reqReportingBcsmevent.AddElement(bcsmEvent);

            }
        }
    }
    /*else
    {
        DLOG_ERROR("Unknown CallType : %d received", callTypeVal);
    }*/

    rrbArg.SetBcsmEvents(reqReportingBcsmevent);
    //DLOG_DEBUG("CCA_Initial_to_V1RequestReportBCSMEvent -- Exit");

}

void  TransatelCAPToRoHandler::CCA_Initial_to_RequestReportSMSEvent(IwfFsm *ctxt,
        const Ro_TSL::CreditControlAnswer *in,
        cap_v3::RequestReportSMSEventArg *out,std::string rrbRuleId)
{
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    Call_Type callType;

    if(userData)
    {
        callType = userData->GetCallType();
    }

    RequestReportSMSEventArg::SMSEvents smse;
    SMSEvent smsev;
    SMSEvent smsev1;
    if(callType == MO_SMS)
    {
        std::vector<TCAPV3SMSEvent_ArmData> eventLst;
        m_config.GetMOSMSCAPV3_EventList(eventLst,rrbRuleId);

    for(unsigned j = 0 ; j < eventLst.size();j++)
    {
        TCAPV3SMSEvent_ArmData eventVal = eventLst[j];
        SMSEvent smsev;
        smsev.SetEventTypeSMS(new EventTypeSMS(eventVal.smsEvntType));
        for(unsigned i = 0 ; i < eventVal.monitorMode.size();i++)
        {
            if(2 == eventVal.monitorMode[i])
                smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
            if(1 == eventVal.monitorMode[i])
                smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_NOTIFY_AND_CONTINUE);
            if(0 == eventVal.monitorMode[i])
                smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED);
            smse.AddElement(smsev);

        }

        out->SetSMSEvents(smse);
        }
    }

#if 0
        smsev.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_FAILURE));
        smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
        smsev1.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_SUBMITTED));
        smsev1.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
        smse.AddElement(smsev);
        smse.AddElement(smsev1);
        out->SetSMSEvents(smse);
#endif

    else if(callType == MT_SMS)
    {
        SMSEvent smsev;
        smsev.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_T_SMS_FAILURE));
        smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
        smsev1.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_T_SMS_SUBMITTED));
        smsev1.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
        smse.AddElement(smsev);
        smse.AddElement(smsev1);
        out->SetSMSEvents(smse);

#if 0

        std::vector<TCAPV3SMSEvent_ArmData> eventLst;
        m_config.GetMOSMSCAPV3_EventList(eventLst,rrbRuleId);

        for(unsigned j = 0 ; j < eventLst.size();j++)
        {
            TCAPV3SMSEvent_ArmData eventVal = eventLst[j];
            SMSEvent smsev;
            smsev.SetEventTypeSMS(new EventTypeSMS(eventVal.eventType));
            for(unsigned i = 0 ; i < eventVal.monitorMode.size();i++)
            {
                if(2 == eventVal.monitorMode[i])
                    smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_TRANSPARENT);
                if(1 == eventVal.monitorMode[i])
                    smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_NOTIFY_AND_CONTINUE);
                if(0 == eventVal.monitorMode[i])
                    smsev.SetMonitorMode(cap_v3::MonitorMode::MONITOR_MODE_INTERRUPTED);
                smse.AddElement(smsev);

            }

            out->SetSMSEvents(smse);
         }
#endif
    }
}

void TransatelCAPToRoHandler:: CCA_to_ApplyChargingArg(IwfFsm *ctxt,
        const Ro_TSL::CreditControlAnswer *in,
        cap_v2::ApplyChargingArg *out)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    cap_v2::CAMEL_AChBillingChargingCharacteristics achBilling;
    cap_v2::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging timeDurCharging;

    try
    {
        //Set the maxCallPeriodDuration from Granted-Service-Unit's CC-Time

        cap_v2::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::MaxCallPeriodDuration maxCallPeriodDur(userData->GetGSUCCTime()*10);
        timeDurCharging.SetMaxCallPeriodDuration( maxCallPeriodDur);

        if(in != NULL)
        {
        if ( in->countMultipleServicesCreditControl() )
        {

            //NOTE: Assuming that only one MSCC will get from OCS for mapping all the IE's on cap side.
            Ro_TSL::MultipleServicesCreditControl serviceCreditControl =
                in->getMultipleServicesCreditControl(MSCC_AVP_INDEX);

            // already present in CheckMSCCGrantedServiceUnitCCTime(), GSU-CCTime value is stored in userData.
#if 0
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
#endif
            /*ReleaseIfDurationExceeded is populated if Final-Unit-Indication is  present
              and Final-Unit-Action=Terminate.
              tone is set if CAP-ACH-BeepTone AVP is set in CCA*/
            if(serviceCreditControl.containsFinalUnitIndication())
            {

                Ro_TSL::FinalUnitIndication finalUnitInd = serviceCreditControl.getFinalUnitIndication();
                cap_v2::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::ReleaseIfDurationExceeded releaseIfDurExceed;

                if( finalUnitInd.getFinalUnitAction().value() == Ro_TSL::FinalUnitAction::TERMINATE)
                {
                    unsigned int beepToneVal;
                    if(ITS_SUCCESS == GetBeepToneFromCCA(*(const_cast<Ro_TSL::CreditControlAnswer*>(in)),beepToneVal) &&
                            0 != beepToneVal)
                    {
                        cap_v2::ReleaseIfDurationExceeded::Tone tone(true);
                        releaseIfDurExceed.SetTone(tone);

                    }
                    else
                    {
                        cap_v2::ReleaseIfDurationExceeded::Tone tone(false);
                        releaseIfDurExceed.SetTone(tone);
                    }
                    timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);
                }
                }
            }
        }
        else
        {
            pbACHData achData;
            achData.CopyFrom(userData->GetACHData());

            cap_v2::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::ReleaseIfDurationExceeded releaseIfDurExceed;
            if(achData.has_finalunitindication())
            {
                if( achData.finalunitindication() == Ro_TSL::FinalUnitAction::TERMINATE)
                {
                    if(achData.has_beeptone() && achData.beeptone() != 0)
                    {
                        cap_v2::ReleaseIfDurationExceeded::Tone tone(true);
                        releaseIfDurExceed.SetTone(tone);
                    }
                    else
                    {
                        cap_v2::ReleaseIfDurationExceeded::Tone tone(false);
                        releaseIfDurExceed.SetTone(tone);
                    }
                    timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);
                }
            }
        }
        //Not Applicable for TSL. LowBalanceIndication.
#if 0
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

        else
        {
            CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::
                Tone tone(false);
            timeDurCharging.SetTone(tone);
        }
#endif

        achBilling.SetChoiceTimeDurationCharging((timeDurCharging));
        LogCAPTslAsnObj(achBilling);
        Octets* achBillingBuf = achBilling.Encode();

        cap_v2::AChBillingChargingCharacteristics *AChBilling = new cap_v2::AChBillingChargingCharacteristics((achBillingBuf->GetArray()));

        out->SetAChBillingChargingCharacteristics((AChBilling));


        /* SendingSideID values is set based on Call_Type value recv in IDP*/
        Call_Type val = userData->GetCallType();
        byte array[] = { 0x01 };
        if(MO_VOICE == val)
        {
            //byte arr = { 0x01 };
            array[0] = { 0x01 };
        }
        else if (MT_VOICE == val)
        {
            array[0] = { 0x02 };
        }
        cap_v2::LegType* lt = new cap_v2::LegType(ArrayToVector(array, ARRAY_SIZE(array)));
        cap_v2::SendingSideID *sid = new cap_v2::SendingSideID();
        sid->SetChoiceSendingSideID(lt);
        out->SetPartyToCharge((cap_v2::SendingSideID*)sid);

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

void TransatelCAPToRoHandler::HandleCCAInitialErrorConditions(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("HandleCCAInitialErrorConditions -- Entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if ((m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS) && !userData->IsFailedCDRLogged())
    {
        /* Log CDR only if the Error-Code is 3xx */
        ITS_UINT resultCode = cca->getResultCode().value();

        if ( resultCode >= ITS_DIA_PROT_ERR_MIN_RANGE &&
                resultCode <= ITS_DIA_PROT_ERR_MAX_RANGE )
        {
            //DLOG_DEBUG("Logging CDR for Failed 3xxx CCA-I");
            LogCDRData(ctxt, FAILED_3XXX_CCA_I);
            userData->SetFailedCDRLogged(true);
        }
        else if( resultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE &&
                resultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE)
        {
            //DLOG_DEBUG("Logging CDR for Failed 5xxx CCA-I");
            LogCDRData(ctxt, FAILED_5XXX_CCA_I);
            userData->SetFailedCDRLogged(true);
        }
        else if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS)
        {
            if(!userData->IsFailedCDRLogged())
            {
                if( resultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE &&
                        resultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE)
                {
                    //DLOG_DEBUG("Logging CDR for Failed 4xxx CCA-I");
                    LogCDRData(ctxt, FAILED_4XXX_CCA_I);
                }
                else
                {
                    //DLOG_DEBUG("Logging CDR for Successful Calls");
                    LogCDRData(ctxt);
                }
            }
        }
    }
    ret.action = IWF_RA_FORWARD;
    ret.isReleaseEnd = true;

    //DLOG_DEBUG("HandleCCAInitialErrorConditions -- Exit");
}

void TransatelCAPToRoHandler::HandleCCAUpdateErrorConditions(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("HandleCCAUpdateErrorConditions -- Entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    /* Log CDR only if the Error-Code is 3xx */
    ITS_UINT resultCode = cca->getResultCode().value();
    if ( resultCode >= ITS_DIA_PROT_ERR_MIN_RANGE &&
            resultCode <= ITS_DIA_PROT_ERR_MAX_RANGE )
    {
        //DLOG_DEBUG("Logging CDR for Error-Code : %d",resultCode);
        if( m_config.GetCdrConfig() != DISABLE_ALL_CALLS )
        {
            LogCDRData(ctxt, FAILED_3XXX_CCA_U);
            userData->SetFailedCDRLogged(true);
        }
    }

    std::string RuleName("");
    int32_t skVal = userData->GetIDPToCCRIData().service_key();
    string imsi = userData->GetIDPToCCRIData().imsi().c_str();
    int32_t ossn = CAP;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(imsi,skVal,RuleName,ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return;
    }
    std::string destrealm = IwfController::Instance().Config().RoutingRules().Route(RuleName)->destRealm();

    if(destrealm.empty())
    {
        DLOG_ERROR("HandleCCAUpdateErrorConditions: Destination Realm is not present in RoutingRule, Unable to Route Message");
        return;
    }

    IwfDCCAEndpointsConf* endpoints = IwfController::Instance().Config().
                                            DCCAConfig().GetDestinations().LookupEndpointsConf(destrealm);

    if (endpoints == NULL)
    {
        DLOG_DEBUG("No DCCA endpoints founds for realm %s", destrealm.c_str());
        return;
    }
    if (endpoints->Size() == 0)
    {
        DLOG_DEBUG("No endpoints are configured under realm %s", destrealm.c_str());
        return;
    }

    if(true == endpoints->GetCCRTFlag())
    {
        BuildCCRTerminateForIDP(ctxt,
                (diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE),
                outCmd, userData->GetUSUCCTime());
        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
        ret.isReleaseEnd = false;
        ctxt->SetDontTriggerFollowOnForCCAUError(true);
    }
    else
    {
        DLOG_DEBUG("HandleCCAUpdateErrorConditions, sendCCRTFlag set to false, consuming for CCA-U error resultCode.");
        ret.action = IWF_RA_FORWARD;
        ret.isReleaseEnd = true;
        //NOTE: Clear the session
        std::string rlsStr = cca->getSessionId().value();
        ITS_UINT sIdx =  cca->getSessionIndex();
        if ((m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
                    m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS) && !userData->IsFailedCDRLogged())
        {
            /* Log CDR only if the Error-Code is 3xx */
            ITS_UINT resultCode = cca->getResultCode().value();

            if ( resultCode >= ITS_DIA_PROT_ERR_MIN_RANGE &&
                    resultCode <= ITS_DIA_PROT_ERR_MAX_RANGE )
            {
                //DLOG_DEBUG("Logging CDR for Failed 3xxx CCA-U");
                LogCDRData(ctxt, FAILED_3XXX_CCA_U);
                userData->SetFailedCDRLogged(true);
            }
            else if( resultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE &&
                    resultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE)
            {
                //DLOG_DEBUG("Logging CDR for Failed 5xxx CCA-U");
                LogCDRData(ctxt, FAILED_5XXX_CCA_U);
                userData->SetFailedCDRLogged(true);
            }
            else if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS)
            {
                if(!userData->IsFailedCDRLogged())
                {
                    if( resultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE &&
                            resultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE)
                    {
                        //DLOG_DEBUG("Logging CDR for Failed 4xxx CCA-U");
                        LogCDRData(ctxt, FAILED_4XXX_CCA_U);
                    }
                    else
                    {
                        //DLOG_DEBUG("Logging CDR for Successful Calls");
                        LogCDRData(ctxt);
                    }
                }
            }
        }
        TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
        ReleaseSession(rlsStr, sIdx);
    }
    //DLOG_DEBUG("HandleCCAUpdateErrorConditions -- Exit");
}

void TransatelCAPToRoHandler::HandleCCATerminateErrorConditions(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca,
        TCAP_Component *&cpt,
        DIA_BASE_CMD *&outCmd,
        IwfReturnAction& ret)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("HandleCCATerminateErrorConditions -- Entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    BuildRelease(ctxt, cca , cpt, userData->GetReleaseCause());
    UPDATE_SSG_STATS_REL_ARG_SENT;
    ret.action = IWF_RA_FORWARD;
    ret.isReleaseEnd = true;
    ret.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
    userData->SetCapReleaseSent(true);

    //DLOG_DEBUG("HandleCCATerminateErrorConditions -- Exit");
}

void TransatelCAPToRoHandler::CheckAndLogCDRForCCATerminate(IwfFsm *ctxt,
        Ro_TSL::CreditControlAnswer *cca)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CheckAndLogCDRForCCATerminate-- Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if ((m_config.GetCdrConfig() == ENABLE_ALL_CALLS ||
            m_config.GetCdrConfig() == ENABLE_ONLY_FAILED_CALLS) && !userData->IsFailedCDRLogged())
    {
        ITS_UINT resultCode = cca->getResultCode().value();
        if(userData)
        {
            ITS_UINT ccaUpdateResultCode = userData->GetCurrentCCAUResultCode();
            if(ccaUpdateResultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE &&
                    ccaUpdateResultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE)
            {
                //DLOG_DEBUG("Logging CDR for Failed 5xxx CCA-U");
                LogCDRData(ctxt, FAILED_5XXX_CCA_U);
            }
            else if ( resultCode >= ITS_DIA_PROT_ERR_MIN_RANGE &&
                    resultCode <= ITS_DIA_PROT_ERR_MAX_RANGE )
            {
                //DLOG_DEBUG("Logging CDR for Failed 3xxx CCA-T");
                LogCDRData(ctxt, FAILED_3XXX_CCA_T);
                userData->SetFailedCDRLogged(true);
            }
            else if( resultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE &&
                    resultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE)
            {
                //DLOG_DEBUG("Logging CDR for Failed 5xxx CCA-T");
                LogCDRData(ctxt, FAILED_5XXX_CCA_T);
                userData->SetFailedCDRLogged(true);
            }
            else if (m_config.GetCdrConfig() == ENABLE_ALL_CALLS)
            {
                if(!userData->IsFailedCDRLogged())
                {
                    //Check for CCA-U result code, and log Failure reason for 4xxx
                    if(ccaUpdateResultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE &&
                            ccaUpdateResultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE)
                    {
                        //DLOG_DEBUG("Logging CDR for Failed 4xxx CCA-U");
                        LogCDRData(ctxt, FAILED_4XXX_CCA_U);
                    }
                    else if( resultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE &&
                            resultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE)
                    {
                        //DLOG_DEBUG("Logging CDR for Failed 4xxx CCA-T");
                        LogCDRData(ctxt, FAILED_4XXX_CCA_T);
                    }
                    else
                    {
                        //DLOG_DEBUG("Logging CDR for Successful Calls");
                        LogCDRData(ctxt);
                    }
                }
            }
        }
    }
    //DLOG_DEBUG("CheckAndLogCDRForCCATerminate-- Exit");
}

void TransatelCAPToRoHandler::TranslateAcrToCcr(IwfFsm* ctxt,
        const cap_v2::CAMEL_CallResult *in,
        Ro_TSL::CreditControlRequest *out,
        IwfReturnAction& ret)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Ro_TSL::MultipleServicesCreditControl mscc;
    Ro_TSL::UsedServiceUnit usu;
    Ro_TSL::ServiceInformation si;
    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    TransCustomAvp::CAPERBSInformation capErbInfo;
    IDPToCCRIData ccriData;
    pbERBData erbData;

    TCAP_Component *currRcvdTcapCpt = ctxt->GetCurrRcvdTcapCpt();

    //if control mode is REMOTE, stop the ACR timer, set the curr USU as elapsed time
    ETimerType timerType = ETimerType::ACR_TIMER;
    STimerInfo fsmTimerData;
    ctxt->GetTimerInfo(timerType, fsmTimerData);

    IwfTimer timerObj;
    if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
    {
        //DLOG_DEBUG("[CAP:ApplyChargingArg] TimerType : ACR_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
        ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
    }
    else
    {
        DLOG_ERROR("[CAP:ApplyChargingArg] Failed to stop TimerType : ACR_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
    }


    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    //Set Multiple-Service-Indicator, Multiple_Servcie_Credit_Control - USU --CCTime
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    out->setMultipleServicesIndicator(msi);

    if(userData)
    {
        ccriData.CopyFrom(userData->GetIDPToCCRIData());
        RetrieveIDPToCCRIData(capInfo, ccriData);
        if(ccriData.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriData.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType((Ro_TSL::SubscriptionIdType::Value)ccriData.subscriptionidinfo().subidtype()));
            }
            if(ccriData.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriData.subscriptionidinfo().subiddata()));
            }
            out->addSubscriptionId(subsId);
        }
        erbData.CopyFrom(userData->GetERBData());
        //RetrieveERBData(capErbInfo, erbData);
        //capInfo.setCAPERBSInformation(capErbInfo);

        if(in != NULL && in->ChoiceTimeDurationChargingResult())
        {
            //NOTE: This check is for Error case, i.e Received ACR with CallActive true after ReleaseCall sent.
            if (userData->IsCapReleaseSent())
            {
                //DLOG_WARNING("ReleaseCallArg sent so just cosuming the ACR message");
                ret.action = IWF_RA_CONSUME;
                ret.dir = IWF_RD_DIA;
                return;
            }

            if(userData->IsFirstERBrcvd() == false)
            {
                int rc = HandleACR_Recv_Before_CallAnswered(ctxt,in,out,ret);
                //DLOG_DEBUG("HandleACR_Recv_Before_CallAnswered returned : %d.",rc);
                return;
            }

            cap_v2::CAMEL_CallResult::TimeDurationChargingResult tdcr = in->GetChoiceTimeDurationChargingResult();

            if(tdcr.GetCallActive().GetValue())
            {
                //NOTE: setting CCTYPE as UPDATE_REQUEST if CallActive is true
                out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::UPDATE_REQUEST));
                //DLOG_DEBUG("setting CCTYPE as UPDATE_REQUEST");

                //setting returnAction to IWF_RA_FORWARD in case of CCR-U so release is not sent
                ret.action = IWF_RA_FORWARD;

                /* Storing the last Sent CC-Request-Type to be used for validating incoming anser msg from ocs*/
                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::UPDATE_REQUEST);

                RetrieveERBData(capErbInfo, erbData);
                capInfo.setCAPERBSInformation(capErbInfo);

                //Setting the Transaltor State as ACR_CALLACT_TRUE so that replication will be performed.
                userData->SetTranslatorState(ACR_CALLACT_TRUE);
                struct timeval tv = GetCurrentMonotonic();
                userData->SetUpdateTriggerTimeStamp(tv.tv_sec);

            }
            else
            {
                userData->ClearUpdateTriggerTimeStamp();

                //Setting the Transaltor State as ACR_CALLACT_FALSE so that replication will be performed.
                userData->SetTranslatorState(ACR_CALLACT_FALSE);

                struct timeval tv = GetCurrentMonotonic();
                userData->SetDisconTriggerTimeStamp(tv.tv_sec);

                /*Stop AT Timer on recv ACR(CallActive=False) */

                ETimerType timerType = ETimerType::ACTIVITY_TIMER;
                STimerInfo fsmTimerData;
                ctxt->GetTimerInfo(timerType, fsmTimerData);

                IwfTimer timerObj;
                if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                {
                    /*DLOG_DEBUG("[CAP:ApplyChargingArg] TimerType : %s, TimerId : %u stopped.",
                            (GetStrTimerType(fsmTimerData.m_eTimerType)).c_str(),
                            fsmTimerData.m_uiTimerId);*/
                    ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                }
                else
                {
                    DLOG_ERROR("[CAP:ApplyChargingArg] Failed to stop TimerType : %s, TimerId : %ul.",
                            (GetStrTimerType(fsmTimerData.m_eTimerType)).c_str(),
                            fsmTimerData.m_uiTimerId);
                }

                RetrieveERBData(capErbInfo, erbData);
                if((userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_OANSWER != erbData.erbrecvevttype())) ||
                        (!userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_TANSWER != erbData.erbrecvevttype())))
                {
                    capInfo.setCAPERBSInformation(capErbInfo);
                }

                //NOTE: setting CCTYPE as TERMINATION_REQUEST if CallActive is false
                out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST));
                //DLOG_DEBUG("setting CCTYPE as TERMINATION_REQUEST");

                if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE)
                {
                    bool isResAndFwd = false;
                    /* If the SCPAction is not follow-On, means Normal Remote scenario trigger CCR-T and Release */
                    if ( (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ||
                                userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT))
                    {
                        /* Case To consume subsequent ACR(ca=falseDiscon) in separate TC_Cont or same TC_Cont message after CCR-T is triggered for earlier ERB(Discon)*/
                        /* Check if CC-Request-Type is not terminate and IsFollowingOn is not set trigger CCR-T
                         * and Release else consume ACR */
                        if (userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST &&
                                userData->IsFollowingOnSet() != true)
                        {
                            /* Check if FUI is set do a respond and forward else if its not lastComponent consume else default action is forward*/
                            if(userData->GetIsFinalUnitsReceived())
                            {
                                isResAndFwd = true;
                                //DLOG_DEBUG("Recv ACR(False) in TC_Cont, with FUI set, sending CCR-T & Release");
                            }
                            else if(!currRcvdTcapCpt->GetLast())
                            {
                                ret.action = IWF_RA_CONSUME;
                                ret.dir = IWF_RD_DIA;
                                //DLOG_DEBUG("Recv ACR(False) in TC_Cont & is not lastComp, consuming...");
                                return;
                            }
                            else //Recv as last component then send CCR-T and ReleaseCall
                            {
                                isResAndFwd = true;
                                //DLOG_DEBUG("Recv ACR(False) in TC_Cont & is  lastComp, sending CCR-T & Release...");
                            }
                        }
                        else
                        {
                            ret.action = IWF_RA_CONSUME;
                            ret.dir = IWF_RD_DIA;
                            //DLOG_DEBUG("Recv ACR(False) in TC_Cont & CCR-T already sent, hence consuming...");
                            return;
                        }
                    }
                    else
                    {
                        if(!currRcvdTcapCpt->GetLast())
                        {
                            ret.action = IWF_RA_CONSUME;
                            ret.dir = IWF_RD_DIA;
                            //DLOG_DEBUG("Recv ACR(False) in TC_Cont & is not lastComp, consuming...");
                            return;
                        }
                        isResAndFwd = true;
                    }

                    if(isResAndFwd)
                    {
                        /* setting returnAction to IWF_RA_RESPOND_AND_FORWARD in case of triggering CCR-T and release */
                        ret.action = IWF_RA_RESPOND_AND_FORWARD;
                        isResAndFwd = false;
                    }
                }
                else if(inTcapDlg->GetDialogueType() == TCPPT_TC_END)
                {
                    /* Checking this condition if for Follow-On case ACR comes in TC_End
                     * 1. If it is only single Component trigger CCR-T
                     * 2. If ERB is First and ACR is second Consume it.
                     * 3. If ACR is First and ERB is second then also consume */

                    //if ( (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ||
                    //            userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT))
                    {
                        if(!currRcvdTcapCpt->GetLast())
                        {
                            /* Checking the Component if it is not Last Component Consume it */
                            //DLOG_INFO("Received ACR in TC_End for Follow-On case, But is not Last Component so CONSUME it..!!!");
                            ret.action = IWF_RA_CONSUME;
                            ret.dir = IWF_RD_DIA;
                            return;
                        }

                    }
                    if(userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::TERMINATION_REQUEST)
                    {
                        /* Checking the CC-RequestType if already a CCR-T is triggered just
                         * consume otherwise by default the return-action is IWF_RA_FORWARD */
                        //DLOG_INFO("Received ACR in TC_End for Follow-On case, But already CCR-T is sent so CONSUME it..!!!");
                        ret.action = IWF_RA_CONSUME;
                        ret.dir = IWF_RD_DIA;
                        return;
                    }

                }



                /* Storing the last Sent CC-Request-Type to be used for
                 * validating incoming anser msg from ocs*/
                userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);

                //NOTE: setting Termination cause
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

            cap_v2::TimeInformation ti;
            if (in!= NULL)
                ti = tdcr.GetTimeInformation();

            if(in!=NULL && ti.ChoiceTimeIfNoTariffSwitch())
            {
                //unsigned int timeIfNoTariffSwitch = (ti.GetChoiceTimeIfNoTariffSwitch().GetValue())/10;
                unsigned int timeIfNoTariffSwitch = ROUNDOFF_USU_VALUE(ti.GetChoiceTimeIfNoTariffSwitch().GetValue());
                //DLOG_DEBUG("USU populated in CCR Message : %d", timeIfNoTariffSwitch);
                if(timeIfNoTariffSwitch > userData->GetCumulativeGSUCCTime())
                {
                    Ro_TSL::CCTime cctime(userData->GetCumulativeGSUCCTime());
                    usu.setCCTime(cctime);
                    userData->SetUSUCCTime(userData->GetCumulativeGSUCCTime());
                }
                else
                {
                    Ro_TSL::CCTime cctime(timeIfNoTariffSwitch);
                    usu.setCCTime(cctime);
                    userData->SetUSUCCTime(timeIfNoTariffSwitch);
                }
                mscc.addUsedServiceUnit(usu);
            }
        }

        ITS_UINT seconds = this->GetCurrentTimeStamp();
        diameter::base::EventTimestamp eventTimestamp(seconds);
        out->setEventTimestamp(eventTimestamp);

        ccrnum = userData->GetCCRequestNumber();
        Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        //DLOG_DEBUG("ServiceContextId fetched from Couchbase %s",userData->GetServiceContextId().c_str());
        Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
        out->setServiceContextId(serviceContextId);

        csInfo.setCAPInformation(capInfo);
        si.setCSInformation(csInfo);
        out->setServiceInformation(si);
        out->addMultipleServicesCreditControl(mscc);
    }
}

void TransatelCAPToRoHandler::EventReportSMSArg_To_CCRT(IwfFsm* ctxt,
        const cap_v3::EventReportSMSArg *in,
        Ro_TSL::CreditControlRequest *out)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Ro_TSL::ServiceInformation si;
    Ro_TSL::SMSInformation smsinfo;
    pbERBData erbData;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(userData != NULL)
    {
        StoreCallAnswerTimeStamp(userData);
    }

    STimerInfo fsmTimerData;
    IwfTimer timerObj;
    if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
    {
        //DLOG_DEBUG("EventReportSMSArg_To_CCRT:: TimerType : NO_EVENT_TIMER, TimerId : %u stopped.",fsmTimerData.m_uiTimerId);
        ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
    }
    else
    {
        DLOG_ERROR("EventReportSMSArg_To_CCRT:: Failed to stop TimerType : NO_EVENT_TIMER, TimerId : %u.",fsmTimerData.m_uiTimerId);
    }

    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    out->setAuthApplicationId(authApplicationId);

    out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST));
    out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));

    if(userData)
    {
        userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT);
        ccrnum = userData->GetCCRequestNumber();
        Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
        out->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        ITS_UINT seconds = this->GetCurrentTimeStamp();
        diameter::base::EventTimestamp eventTimestamp(seconds);
        out->setEventTimestamp(eventTimestamp);

        if(userData->HasServiceContextId())
        {
            Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
            out->setServiceContextId(serviceContextId);
        }
        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
    }

    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    out->setMultipleServicesIndicator(msi);

    Ro_TSL::MultipleServicesCreditControl mscc;
    //NOTE: Need to confirm if required
    //Ro_TSL::RequestedServiceUnit rsu;
    //rsu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));
    //mscc.setRequestedServiceUnit(rsu);
    Ro_TSL::UsedServiceUnit usu;

    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    TransCustomAvp::CAPERBSInformation capERInfo;
    if(in->GetEventTypeSMS().IsO_smsSubmitted())
    {
        usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits(1));
        capERInfo.setCAPEventTypeSMS(TransCustomAvp::CAPEventTypeSMS(3));
    }
    else if(in->GetEventTypeSMS().IsO_smsFailure())
    {
        usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));
        capERInfo.setCAPEventTypeSMS(TransCustomAvp::CAPEventTypeSMS(2));
        if(in->OptionEventSpecificInformationSMS())
        {
            if(in->GetEventSpecificInformationSMS().ChoiceO_smsFailureSpecificInfo())
            {
                long int causeVal = in->GetEventSpecificInformationSMS().GetChoiceO_smsFailureSpecificInfo().GetFailureCause().GetValue();
                std::string strcauseVal("");
                std::stringstream streamval;
                streamval<<causeVal;
                streamval>>strcauseVal;

                erbData.set_eventspecinfo(strcauseVal);

                uint8_t remId[NYBBLE_SIZE-2] = {0};
                int len = IWFUtils::StringToTBCD(strcauseVal, remId,strlen(strcauseVal.c_str()), 0, false);
                string hexString((const char*)remId,len);

                TransCustomAvp::CAPERBSEventSpecificInformation capERBSpecInfo(hexString);
                capERInfo.setCAPERBSEventSpecificInformation(capERBSpecInfo);
                //DLOG_INFO("CAPERBEventSpecificInformation : %s",capERInfo.getCAPERBSEventSpecificInformation().value().c_str());
            }
        }
    }
    else if(in->GetEventTypeSMS().IsT_smsSubmitted())
    {
        usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits(1));
        capERInfo.setCAPEventTypeSMS(TransCustomAvp::CAPEventTypeSMS(13));
    }
    else if(in->GetEventTypeSMS().IsT_smsFailure())
    {
        usu.setCCServiceSpecificUnits(Ro_TSL::CCServiceSpecificUnits((diameter::Unsigned64)0));
        capERInfo.setCAPEventTypeSMS(TransCustomAvp::CAPEventTypeSMS(12));
    }
    erbData.set_erbrecvevttype((unsigned int)in->GetEventTypeSMS().GetValue());

    mscc.addUsedServiceUnit(usu);
    out->addMultipleServicesCreditControl(mscc);

    cap_v3::MiscCallInfo misscallinfo = in->GetMiscCallInfo();
    int messagetype = misscallinfo.GetMessageType().GetValue();
    capERInfo.setCAPERBSMessageType(TransCustomAvp::CAPERBSMessageType(messagetype));

    erbData.set_msgtype(messagetype);
    userData->SetERBData(erbData);

    StoredIDPSMSToCCRIData ccriAvpVal;
    ccriAvpVal.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
    GetCCRIAvpVal(capInfo,ccriAvpVal);
    if(ccriAvpVal.has_subscriptionidinfo())
    {
        Ro_TSL::SubscriptionId subsId;

        if(ccriAvpVal.subscriptionidinfo().has_subidtype())
        {
            subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType
                    ((Ro_TSL::SubscriptionIdType::Value)ccriAvpVal.subscriptionidinfo().subidtype()));
        }
        if(ccriAvpVal.subscriptionidinfo().has_subiddata())
        {
            subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriAvpVal.subscriptionidinfo().subiddata()));
        }
        out->addSubscriptionId(subsId);
    }

    /*update the StoredIDPSMSToCCRIData to store TotalUSUCCServiceSpecificUnits
     * used for CDR generation */
    ccriAvpVal.set_m_totalusuccservice(usu.getCCServiceSpecificUnits().value());
    userData->SetStoredIDPSMSToCCRIData(ccriAvpVal);

    capInfo.setCAPERBSInformation(capERInfo);
    csInfo.setCAPInformation(capInfo);
    /* Call-Type AVP removed from CCR msg as per latest SoW */
#if 0
    if(userData)
    {
        Call_Type callType = userData->GetCallType();
        if(callType == MO_SMS)
            csInfo.setCallType((TransCustomAvp::CallType)TransCustomAvp::CallType::MO_SMS);
        else if (callType == MT_SMS)
            csInfo.setCallType((TransCustomAvp::CallType)TransCustomAvp::CallType::MT_SMS);
    }
#endif
    si.setCSInformation(csInfo);

    out->setServiceInformation(si);
}

bool TransatelCAPToRoHandler::IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt, bool &isReq)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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

bool TransatelCAPToRoHandler::IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /* if CCR-RequestType is not Terminate send true else false
     * here it is reponse message*/
    diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();
    DiaCommandCode code = (DiaCommandCode)cmd->getCommandCode();
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    try
    {
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
            //Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
            unsigned ccRequestType = 0;
            if (cmd->getAvpValue(CC_REQUEST_TYPE_AVP_CODE, &ccRequestType,
                        diameter::EnumeratedType) != 0)
            {
                /*DLOG_DEBUG("Received CC-Request-Type avp form answer message : %d",ccRequestType);
            }
            else
            {*/
                ccRequestType = userData->GetLastSentCCRequestType();
                //DLOG_DEBUG("CC-Request-Type avp missing, retrieved from the Cap-Ro-Ctxt : %d",ccRequestType);
            }
            if(ccRequestType != Ro_TSL::CCRequestType::TERMINATION_REQUEST)
            {

                bool isSuccess = true;
                if(ccRequestType == Ro_TSL::CCRequestType::INITIAL_REQUEST)
                {
                     //if (!cmd->isError()) // This is not a proper check since our stack sets E bit for all error cases
                    if (true)
                    {
                        Ro_TSL::CreditControlAnswer cca(cmd->getImpl());

                        /** Check for the 4xxx/5xxx errors */
                        int resultCode = cca.getResultCode().value();
                        /*
                          if(((cca.getResultCode().value() % 5000) < 1000 ) ||
                             ((cca.getResultCode().value() % 4000) < 1000 ))
                         */
                        if((resultCode == DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED) ||
                                (resultCode == DIAMETER_ERROR_CREDIT_LIMIT_REACHED) ||
                                (resultCode == DIAMETER_ERROR_OTHER_ERROR) ||
                                (resultCode == DIAMETER_ERROR_RATING_FAILED) ||
                                (resultCode == ITS_DIA_AUTHORIZATION_REJECT) ||
                                (resultCode == ITS_DIA_INVALID_AVP_VALUE) ||
                                (resultCode == ITS_DIA_UNABLE_TO_COMPLY) ||
                                (resultCode == ITS_DIA_MISSING_AVP))

                        {
                            CheckIsCAPReleaseCausePresent(ctxt, &cca);
                            isSuccess = false;
                        }

                        if(cca.containsServiceControl())
                        {
                            TransCustomAvp::ServiceControl servCtrl = cca.getServiceControl();
                            if((resultCode == DIAMETER_ERROR_NODE_NOT_RESPONSIBLE) &&
                                    servCtrl.containsSCPAction() &&
                                    servCtrl.getSCPAction().value() == TransCustomAvp::SCPAction::REJECT)
                            {
                                CheckIsCAPReleaseCausePresent(ctxt, &cca);
                                isSuccess = false;
                            }
                        }
                    }

                }
                return isSuccess;
            }
            else
            {
                if( (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ||
                            userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT)
                        && userData->IsCurrentReceivedTcapContinue() == true
                        && !userData->IsCapReleaseSent())
                {
                    Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
                    int resultCode = cca.getResultCode().value();
                    if((resultCode >= ITS_DIA_4XXX_ERR_MIN_RANGE && resultCode <= ITS_DIA_4XXX_ERR_MAX_RANGE) || 
                            (resultCode >= ITS_DIA_5XXX_ERR_MIN_RANGE && resultCode <= ITS_DIA_5XXX_ERR_MAX_RANGE))
                    {
                        DLOG_DEBUG("Error Received in CCA-T message for followOn case, terminate the call");
                        return false;
                    }
                    if(!userData->GetBcsmEventMO() && (false == userData->GetTriggerFollowOnSession()))
                    {
                        //DLOG_DEBUG("FollowOn session not to be triggered for MO call");
                        return false;
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    catch (diameter::CodecExceptionToApp& e)
    {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for commandCode %d is %d", cmd->getCommandCode(), e.errcode());
        DLOG_ERROR("SessionId %s", e.sessionId());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
        //return e.errcode();
        return true;
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
    }
    return true;
}

int TransatelCAPToRoHandler::TimeStamp(const uint8_t *tbcd, int len, uint32_t &seconds,TransatelCAPRoTransactionContext* userData)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
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
        /*DLOG_DEBUG("Year = %d, Month = %d, Day = %d, Hours = %d, Min = %d,Sec = %d",m_time.year, m_time.month, m_time.day,
                m_time.hours, m_time.minutes, m_time.seconds);*/

        tmstruct_2.tm_hour = m_time.hours; tmstruct_2.tm_min = m_time.minutes; tmstruct_2.tm_sec = m_time.seconds;
        tmstruct_2.tm_mon = (m_time.month - 1);  tmstruct_2.tm_mday = m_time.day; tmstruct_2.tm_year = (m_time.year - 1900);

        strftime (buf,100," %Y/%m/%d %H:%M:%S\n",&tmstruct_2);
        //DLOG_DEBUG("Time from Peer is %s", buf);

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
        //DLOG_DEBUG("%u seconds \n", seconds);
    }
    else
    {
        //DLOG_ERROR("DateAndTime not in Expected range");
        ret = !ITS_SUCCESS;
    }
    return ret;
}

uint32_t TransatelCAPToRoHandler::ConstructTimeStamp(TransatelCAPRoTransactionContext* userData)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    time_t timestruct_2;

    struct tm tmstruct_2;
    uint32_t seconds;
    char buf [100];

    time(&timestruct_2);  /* get current time; same as: now = time(NULL)  */

    tmstruct_2 = *localtime(&timestruct_2);

    strftime (buf,100," %Y/%m/%d %H:%M:%S\n",&tmstruct_2);
    //DLOG_DEBUG("Current Time is %s", buf);

    seconds = ((mktime(&tmstruct_2)) + TIME_FROM_1900_TO_EPOCH);
    if(userData->IsTimeZoneBitSet())
    {
        seconds -= (userData->GetTimeZoneSeconds());
    }
    else
    {
        seconds += (userData->GetTimeZoneSeconds());
    }
    //DLOG_DEBUG("%u seconds \n", seconds);

    return seconds;
}

unsigned int TransatelCAPToRoHandler::GetTerminationCauseCode(TransatelCAPRoTransactionContext* userData)
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
            userData->IsASRReceived())
    {
        causeCode = diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE;
    }

    return causeCode;
}

int TransatelCAPToRoHandler::SetConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    return retVal;
}

int TransatelCAPToRoHandler::DeleteConfig(IwfTranslationDataConfig *translationDataConfig)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    return retVal;
}

void TransatelCAPToRoHandler::EncodeMsg(AsnObject* p, Octets** octets)
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

void TransatelCAPToRoHandler::ReleaseSession(string &sessString, ITS_UINT sessIdx)
{
    DiaFrame::GetDiaFrame()->ReleaseSession(sessString.c_str());
}

void TransatelCAPToRoHandler::CheckEventTypeBCSMAndSetReleaseCause(IwfFsm *ctxt, cap_v3::EventTypeBCSM eventType)
{
    byte cause = NORMAL_CALL_CLEARING;
    TransatelCAPRoTransactionContext* userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

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

int TransatelCAPToRoHandler::CheckControlMode(Ro_TSL::CreditControlAnswer* cca,
        TransatelCAPRoTransactionContext* userData)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    int ret = ITS_SUCCESS;

    //Verify the SCPAction value & CAP-Control-Mode
    if(cca->containsServiceControl())
    {
        TransCustomAvp::ServiceControl servCtrl = cca->getServiceControl();
        if(servCtrl.containsCAPInformation())
        {
            TransCustomAvp::CAPInformation capInfo = servCtrl.getCAPInformation();
            if(capInfo.containsCAPControlMode())
            {
                int capcontrolmode = capInfo.getCAPControlMode().value();
                //DLOG_DEBUG("CheckControlMode: recieved CapControlMode %d",capcontrolmode);
                userData->SetCAPControlMode(capcontrolmode);
                switch(capcontrolmode)
                {
                    case TransCustomAvp::CAPControlMode::NO_CONTROL :
                        {
                            //DLOG_ERROR("CheckControlMode: recieved CapControlMode as NO_CONTROL");
                            userData->SetTerminationCause(DIA_TERM_CAUSE_NOT_CONTROLLED_CALL);
                            ret = !ITS_SUCCESS;
                            break;
                        }
                    case TransCustomAvp::CAPControlMode::LOCAL_CONTROL  :
                        {
                            //DLOG_DEBUG("CheckControlMode: recieved CapControlMode as LOCAL_CONTROL");
                            userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
                            break;
                        }
                    case TransCustomAvp::CAPControlMode::REMOTE_CONTROL :
                        {
                            userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_CONTROL_MODE);
                            ret = !ITS_SUCCESS;
                            break;
                        }
                    default:
                        {
                            userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_CONTROL_MODE);
                            ret = !ITS_SUCCESS;
                            break;
                        }
                }

            }
            else
            {
                //DLOG_DEBUG("CAP-Control-Mode is not set and by default considered as LOCAL_CONTROL");
                userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
            }
        }
        else
        {
            //DLOG_DEBUG("CAP-Information is not set and by default CAP-Control-Mode is considered as LOCAL_CONTROL");
            userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
        }
    }
    else
    {
        //DLOG_DEBUG("Service-Control is not set and by default CAP-Control-Mode is considered as LOCAL_CONTROL");
        userData->SetCAPControlMode(TransCustomAvp::CAPControlMode::LOCAL_CONTROL);
    }


    return ret;
}

int TransatelCAPToRoHandler::CheckSCPAction(Ro_TSL::CreditControlAnswer* cca,
        TransatelCAPRoTransactionContext* userData)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    int ret = ITS_SUCCESS;

    if(cca->containsServiceControl())
    {
        //Verify the SCPAction value & CAP-Control-Mode
        TransCustomAvp::ServiceControl servCtrl = cca->getServiceControl();
        if ( servCtrl.containsSCPAction() )
        {
            int scpAction = servCtrl.getSCPAction().value();
            //DLOG_DEBUG("CheckSCPAction:: Recv ScpAction : %d.",scpAction);
            userData->SetSCPAction(scpAction);
            switch(scpAction)
            {
                case TransCustomAvp::SCPAction::CONTINUE :
                    break;
                case TransCustomAvp::SCPAction::REJECT   :
                case TransCustomAvp::SCPAction::CONNECT  :
                case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON :
                case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT     :
                case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE    :
                default :
                    {
                        //DLOG_ERROR("CheckSCPAction:: Recv ScpAction : %d.",scpAction);
                        userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
                        ret = !ITS_SUCCESS;
                        break;
                    }
            }
        }
        else
        {
            //DLOG_ERROR("No SCP-Action avp present in Service-Control");
            userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
            ret = !ITS_SUCCESS;
        }
    }
    else
    {
        //DLOG_ERROR("No Service-Control avp present in CreditControlAnswer");
        userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
        ret = !ITS_SUCCESS;
    }

    return ret;
}

void TransatelCAPToRoHandler::CheckIsCAPReleaseCausePresent(IwfFsm *ctxt, Ro_TSL::CreditControlAnswer *cca)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("CheckIsCAPReleaseCausePresent Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(cca->containsServiceControl())
    {
        TransCustomAvp::ServiceControl servCtrl = cca->getServiceControl();

        if(servCtrl.containsCAPInformation())
        {
            TransCustomAvp::CAPInformation capInfo = servCtrl.getCAPInformation();
            if(capInfo.containsCAPReleaseCause())
            {
                userData->SetReleaseCause(capInfo.getCAPReleaseCause().value());
                //DLOG_DEBUG("Recieved CAPReleaseCause : %d",capInfo.getCAPReleaseCause().value());
            }
        }
    }
    //DLOG_DEBUG("CheckIsCAPReleaseCausePresent Exit");
}

void TransatelCAPToRoHandler::CheckHexDigit(string& in_sOctDigitVal, string& out_sOctDigitVal)
{

    char val = in_sOctDigitVal[0];

    switch(val)
    {

        case 'A':
        case 'a':
            out_sOctDigitVal = "10";
            break;
        case 'B':
        case 'b':
            out_sOctDigitVal = "11";
            break;
        case 'C':
        case 'c':
            out_sOctDigitVal = "12";
        case 'D':
        case 'd':
            out_sOctDigitVal = "13";
            break;
        case 'E':
        case 'e':
            out_sOctDigitVal = "14";
            break;
        case 'F':
        case 'f':
            out_sOctDigitVal = "15";
            break;
        default:
            out_sOctDigitVal = in_sOctDigitVal;
    }

}

void TransatelCAPToRoHandler::HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
        TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
        DIA_BASE_CMD*& outDiaCmd,
        TCAP_Component*& outCpt,
        IwfReturnAction& outRetAction)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::HandleTimeout Entry");

    outRetAction.action = IWF_RA_CONSUME;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(inFsmCtxt->GetStoredUserData());

    switch(inTimerType)
    {
        case ETimerType::FAKE_ACH_TIMER:
            {
                //DLOG_DEBUG("TransatelCAPToRoHandler::FAKE ACH TIMER");
		if(userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST) {
			//Initiate CCR-U/CCR-T
			Ro_TSL::CreditControlRequest *ccr = NULL;
			IwfReturnAction ret;
			cap_v1::EventReportBCSMArg evtBcsmArg;

			//Set Cumulattive USU
			if (!userData->GetIsFinalUnitsReceived())
			{
				ccr = new Ro_TSL::CreditControlRequest;
				ERB_To_CCR_Update(inFsmCtxt, evtBcsmArg, ccr, true);
				//else
				//ERB_To_CCR_Terminate(inFsmCtxt, evtBcsmArg, ccr, true);

				SetDefaultAVPs(inFsmCtxt, ccr, inFsmCtxt->GetImsi().c_str());
				SetDestinationHostAndRealm(inFsmCtxt, inFsmCtxt->GetImsi().c_str(), IWF_DEFAULT_SERVICE_KEY, ccr);
				outDiaCmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
				outDiaCmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);

				m_dccaHandler.HandleRequest(userData->GetDccaContext(),
						outDiaCmd, Ro_TSL::CCRequestType::UPDATE_REQUEST);

				LogRoTslDiaMsg(*ccr, false);
				outRetAction.dir = IWF_RD_DIA;
				outRetAction.action = IWF_RA_FORWARD;
				outRetAction.isReleaseEnd = false;
			}
			else
			{
				userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT);
				STimerInfo osInfo;
				inFsmCtxt->GetTimerInfo(inTimerType, osInfo);
				userData->SetUSUCCTime(userData->GetUSUCCTime() + osInfo.m_uiDuration);
				outRetAction.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
				outRetAction.isReleaseEnd = true;
			}
		} else {
			// No action is taken on this event as CCRT is sent for ERB disconnect
			outRetAction.dir = IWF_RD_DIA;
			outRetAction.action = IWF_RA_CONSUME;
			//DLOG_DEBUG("Dropping the FAKE ACH TIMER event as CCRT is already sent for this session");
		}
                break;
            }
        case ETimerType::ACTIVITY_TIMER :
            {
                //DLOG_DEBUG("TransatelCAPToRoHandler::ACTIVITY TIMER");
                //DLOG_DEBUG("Send AT Message and start ACTIVITY_RESPONSE_INTERVAL timers");

                pbActivityTimerData activityTest;
                activityTest.CopyFrom(userData->GetActivityTimerData());
                BuildActivityTest(inFsmCtxt, outCpt);
                if ( outCpt != NULL )
                {
                    ITS_OCTET invkId = inFsmCtxt->GetInvkId();
                    outCpt->SetInvokeID(++invkId);
                    inFsmCtxt->SetInvkId(invkId);
                    activityTest.set_invokeid(invkId);
                    outRetAction.action = IWF_RA_FORWARD;
                    outRetAction.isReleaseEnd = false;
                    outRetAction.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                }

                userData->SetActivityTimerData(activityTest);

                /* Start the AT response timer to wait for the
                 * AT response after sending out AT Message */
                StartTimerHandling(inFsmCtxt, ETimerType::ACTIVITY_RESPONSE_TIMER);

                break;
            }
        case ETimerType::ACH_DELTA_TIMER :
        case ETimerType::NO_EVENT_TIMER :
        case ETimerType::ACR_TIMER :
        case ETimerType::CONNECT_MAX_CALL_DURATION :
            {
                userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_SESSION_TIMEOUT);
                if(ETimerType::NO_EVENT_TIMER == inTimerType)
                {
                    DLOG_DEBUG("TransatelCAPToRoHandler::NO_EVENT_TIMER expired");
                }
                else if(ETimerType::ACR_TIMER == inTimerType)
                {
                    uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(inFsmCtxt);
                    if(m_config.GetIncludeTimeoutInCCTimeConfig())
                    {
                        userData->SetUSUCCTime(totalUsedSeconds);
                    }
                    else
                    {
                        userData->SetUSUCCTime((totalUsedSeconds - m_config.NoACRTimer()));
                    }
                    //DLOG_INFO("IncludeTimeoutInCCTime : %s, USUCCTime set to : %u, ",m_config.GetIncludeTimeoutInCCTimeConfig()?"true":"false", userData->GetUSUCCTime());

                    //DLOG_DEBUG("TransatelCAPToRoHandler::ACR_TIMER expired");
                }
                else if(ETimerType::CONNECT_MAX_CALL_DURATION == inTimerType)
                {
                    DLOG_DEBUG("TransatelCAPToRoHandler::CONNECT_MAX_CALL_DURATION expired");
                }
                outRetAction.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                outRetAction.dir = IWF_RD_TCAP;
                outRetAction.appContext = map_common::UNKNOWN;
                outRetAction.isReleaseEnd = true;

                break;
            }
        case ETimerType::ACTIVITY_RESPONSE_TIMER:
            {
                //DLOG_DEBUG("TransatelCAPToRoHandler::ACTIVITY_RESPONSE_TIMER");
                pbActivityTimerData activityTest;
                activityTest.CopyFrom(userData->GetActivityTimerData());
                /* AT response timer expired decrement the retryCount and set it
                 * on UserData, if the retryCount is equal to 0, Terminate the
                 * Session by sending ReleaseCallArg and CCR-T. Start Ther
                 * ACTIVITY_TIMER for the ACTIVITY_RESPONSE_TIMER value
                 * */

                int32_t atRetryCount = activityTest.retrycount();
                //DLOG_DEBUG("Activity retry count retrieved : %d",atRetryCount);
                if ( DECREMENT_AT_RETRY_COUNT(atRetryCount) <= 0 )
                {
                    DLOG_CRITICAL("IWF did not receive responses for consecutive ActivityTest for maximum retry count, terminating session");
                    outRetAction.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                    outRetAction.dir = IWF_RD_TCAP;
                    outRetAction.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                    outRetAction.isReleaseEnd = true;
                    activityTest.set_retrycount(DECREMENT_AT_RETRY_COUNT(atRetryCount));
                    userData->SetActivityTimerData(activityTest);
                }
                else
                {
                    DLOG_ERROR("IWF did not receive response for last sent ActivityTest, decrementing the retry count to %d",
                            DECREMENT_AT_RETRY_COUNT(atRetryCount));
                    activityTest.set_retrycount(DECREMENT_AT_RETRY_COUNT(atRetryCount));

                    BuildActivityTest(inFsmCtxt, outCpt);
                    if ( outCpt != NULL )
                    {
                        ITS_OCTET invkId = inFsmCtxt->GetInvkId();
                        outCpt->SetInvokeID(++invkId);
                        inFsmCtxt->SetInvkId(invkId);
                        activityTest.set_invokeid(invkId);
                        outRetAction.action = IWF_RA_FORWARD;
                        outRetAction.isReleaseEnd = false;
                        outRetAction.app_ctxt = cap::EncodeApplicationContext(userData->GetRecvAppCtxt());
                    }

                    userData->SetActivityTimerData(activityTest);

                    /* Start the AT response timer to wait for the
                     * AT response after sending out AT Message */
                    StartTimerHandling(inFsmCtxt, ETimerType::ACTIVITY_RESPONSE_TIMER);
                }
                break;
            }
        case ETimerType::IWF_DCCA_TX_TIMER:
            {
                //DLOG_DEBUG("IWF_DCCA_TX_TIMER expired, releasing the session");
                userData->EnabledRetransmission(true); //Enable Retransmission bit
                outRetAction.dir = IWF_RD_TCAP;
                outRetAction.appContext = map_common::UNKNOWN;
                inFsmCtxt->SetErrorCode(IWF_APP_TX_TIMEOUT);
                if (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ||
                        userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT)
                {
                    //DLOG_DEBUG("Scp Action is FollowOn not sending ReleaseCall only CCR-T will be sent");
                    BuildCCRTerminateForIDP(inFsmCtxt, ((diameter::base::TerminationCause::Value)
                                userData->GetTerminationCause()), outDiaCmd, userData->GetUSUCCTime());
                    outRetAction.action = IWF_RA_FORWARD;
                    outRetAction.dir = IWF_RD_DIA;
                    outRetAction.isReleaseEnd = false;
                }
                else
                {
                    //DLOG_DEBUG("Scp Action is not FollowOn Terminating the Session");
                    outRetAction.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
                    outRetAction.isReleaseEnd = true;
                }
                break;
            }
        default : {
                      DLOG_ERROR("TransatelCAPToRoHandler::HandleTimeout Invalid TimerType : %d.",inTimerType);
                  }
    }

    STimerInfo fsmTimerData;
    inFsmCtxt->GetTimerInfo(inTimerType, fsmTimerData);
    inFsmCtxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);

    //DLOG_DEBUG("TransatelCAPToRoHandler::HandleTimeout Exit");

}

void TransatelCAPToRoHandler::StartTimerHandling(IwfFsm* ctxt, ETimerType timerType)
{

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    if(NULL == ctxt ||
            NULL == ctxt->GetCurrRcvdTcapDlg() ||
            NULL == ctxt->GetStoredUserData())
    {
        DLOG_ERROR("TransatelCAPToRoHandler::StartTimerHandling, IwfFsm/CurrRcvdTcapDlg/UserData is NULL.");
        return;
    }
    //2 Start InternalNoEventTimer
    STimerContext sTimerCtxt;
    sTimerCtxt.m_eKeyType = EKeyType::DIALOG_ID;
    sTimerCtxt.m_uiDlgId = ctxt->GetCurrRcvdTcapDlg()->GetDialogueID();
    sTimerCtxt.m_eTimerType = timerType;

    IwfTimer timerObj;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    unsigned int uiTimeout = 0;
    if (sTimerCtxt.m_eTimerType == ETimerType::NO_EVENT_TIMER)
    {
        if( userData->IsIDPSMSReceived())
        {
            uiTimeout = m_config.SmsNoEventTimer();
        }
        else if( userData->IsIDPReceived())
        {
            uiTimeout = userData->GetNoAnsTime() + m_config.NoACRTimer();
        }
    }
    else if (sTimerCtxt.m_eTimerType == ETimerType::FAKE_ACH_TIMER)
    {
        uiTimeout = userData->GetGSUCCTime();
    }
    else if (sTimerCtxt.m_eTimerType == ETimerType::ACR_TIMER)
    {
        uiTimeout = (userData->GetGSUCCTime() + m_config.NoACRTimer());
    }
    else if (sTimerCtxt.m_eTimerType == ETimerType::ACTIVITY_TIMER)
    {
        uiTimeout = userData->GetActivityTimerData().attimer();
    }
    else if (sTimerCtxt.m_eTimerType == ETimerType::CONNECT_MAX_CALL_DURATION)
    {
        uiTimeout = userData->GetConnectMaxDuration();
    }
    else if (sTimerCtxt.m_eTimerType == ETimerType::ACTIVITY_RESPONSE_TIMER)
    {
        uiTimeout = userData->GetActivityTimerData().responsetimeout();
    }

    //unsigned int uiTimeout = m_config.SmsNoEventTimer();
    unsigned int timerId;
    timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType,sTimerCtxt,uiTimeout);

    STimerInfo timerInfo;
    timerInfo.m_eTimerType = sTimerCtxt.m_eTimerType;
    timerInfo.m_uiDuration = uiTimeout;
    timerInfo.m_uiTimerId = timerId;

    struct timeval tv = GetCurrentMonotonic();
    timerInfo.m_tStartTime = tv.tv_sec;
    ctxt->SetTimerInfo(timerInfo);
    /*DLOG_DEBUG("Started TimerType : %s, TimerId %d for dialogId %ud ; SessionId : %s for time %d ,StatTime %d",
            GetStrTimerType(sTimerCtxt.m_eTimerType).c_str(),
            timerInfo.m_uiTimerId,
            sTimerCtxt.m_uiDlgId,
            ctxt->GetDiaSessionId().c_str(),
            uiTimeout,
            timerInfo.m_tStartTime);*/
}

void TransatelCAPToRoHandler::GetCCRIAvpVal(TransCustomAvp::CAPInformation& capInfo, StoredIDPSMSToCCRIData ccriAvpVal)
{
    TransCustomAvp::CAPServiceKey skval(ccriAvpVal.cap_service_key());
    capInfo.setCAPServiceKey(skval);

    TransCustomAvp::CAPDialedDigits dialedDigits(ccriAvpVal.cap_dialed_digits());
    if(ccriAvpVal.has_cap_dialed_digits())
        capInfo.setCAPDialedDigits(dialedDigits);

    if(ccriAvpVal.cap_called_ton() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCalledTON calledton(ccriAvpVal.cap_called_ton());
        capInfo.setCAPCalledTON(calledton);
    }

    TransCustomAvp::CAPCLI capcli(ccriAvpVal.cap_cli());
    if(ccriAvpVal.has_cap_cli())
        capInfo.setCAPCLI(capcli);

    TransCustomAvp::CAPLocationNumber caplocnumber(ccriAvpVal.cap_location_number());
    if(ccriAvpVal.has_cap_location_number())
        capInfo.setCAPLocationNumber(caplocnumber);

    TransCustomAvp::CAPIMSI imsi(ccriAvpVal.cap_imsi());
    if(ccriAvpVal.has_cap_imsi())
        capInfo.setCAPIMSI(imsi);

    TransCustomAvp::CAPVLRNumber vlrnumber(ccriAvpVal.cap_vlr_number());
    if(ccriAvpVal.has_cap_vlr_number())
        capInfo.setCAPVLRNumber(vlrnumber);

    TransCustomAvp::CAPCallReference callrefnumber(ccriAvpVal.cap_call_reference());
    if(ccriAvpVal.has_cap_call_reference())
        capInfo.setCAPCallReference(callrefnumber);

    TransCustomAvp::CAPMSCAddress mscaddr(ccriAvpVal.cap_msc_address());
    if(ccriAvpVal.has_cap_msc_address())
        capInfo.setCAPMSCAddress(mscaddr);

    if(ccriAvpVal.cap_called_npi() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCalledNPI callednpi(ccriAvpVal.cap_called_npi());
        capInfo.setCAPCalledNPI(callednpi);
    }

    if(ccriAvpVal.cap_calling_noa() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCLINOA callingnoa(ccriAvpVal.cap_calling_noa());
        capInfo.setCAPCLINOA(callingnoa);
    }

    if(ccriAvpVal.cap_cli_npi() != TSLConstants::DEFAULT_INVALID_VAL)
    {
        TransCustomAvp::CAPCLINPI clinpi(ccriAvpVal.cap_cli_npi());
        capInfo.setCAPCLINPI(clinpi);
    }

    TransCustomAvp::CAPVersion capversion(ccriAvpVal.cap_version());
    capInfo.setCAPVersion(capversion);

    TransCustomAvp::CAPSMSCAddress smscaddr(ccriAvpVal.cap_smsc_address());
    if(ccriAvpVal.has_cap_smsc_address())
        capInfo.setCAPSMSCAddress(smscaddr);

    TransCustomAvp::CAPSGSNAddress sgsnaddr(ccriAvpVal.cap_sgsn_address());
    if(ccriAvpVal.has_cap_sgsn_address())
        capInfo.setCAPSGSNAddress(sgsnaddr);

    TransCustomAvp::CAPIMEI smimei(ccriAvpVal.cap_sm_imei());
    if(ccriAvpVal.has_cap_sm_imei())
        capInfo.setCAPIMEI(smimei);

    /*TransCustomAvp::CAPSMStatusReportRequest smSRR(ccriAvpVal.CAP_SM_StatusReportRequest);
      if(!ccriAvpVal.CAP_SM_StatusReportRequest.empty())
      capInfo.setCAPSMStatusReportRequest(smSRR);

      TransCustomAvp::CAPSMUserDataHeaderIndicator smUDH(ccriAvpVal.CAP_SM_UserDataHeaderIndicator);
      if(!ccriAvpVal.CAP_SM_UserDataHeaderIndicator.empty())
      capInfo.setCAPSMUserDataHeaderIndicator(smUDH);

      TransCustomAvp::CAPSMReplyPath smRP(ccriAvpVal.CAP_SM_ReplyPath);
      if(!ccriAvpVal.CAP_SM_ReplyPath.empty())
      capInfo.setCAPSMReplyPath(smRP);

      TransCustomAvp::CAPSMVPFormat smVPF(ccriAvpVal.CAP_SM_VPFormat);
      if(!ccriAvpVal.CAP_SM_VPFormat.empty())
      capInfo.setCAPSMVPFormat(smVPF);

      TransCustomAvp::CAPSMMessageTypeIndicator smMTI(ccriAvpVal.CAP_SM_MessageTypeIndicator);
      if(!ccriAvpVal.CAP_SM_MessageTypeIndicator.empty())
      capInfo.setCAPSMMessageTypeIndicator(smMTI);        */

    TransCustomAvp::CAPSMSpecificInfo smSpecificInfo(ccriAvpVal.cap_smspecificinfo());
    if(ccriAvpVal.has_cap_smspecificinfo())
        capInfo.setCAPSMSpecificInfo(smSpecificInfo);

    if (ccriAvpVal.has_cap_sm_protocolid())
    {
        TransCustomAvp::CAPSMProtocolID smProtId(ccriAvpVal.cap_sm_protocolid());
        capInfo.setCAPSMProtocolID(smProtId);
    }

    TransCustomAvp::CAPSMDCS smDCS(ccriAvpVal.cap_sm_dcs());
    if(ccriAvpVal.has_cap_sm_dcs())
        capInfo.setCAPSMDCS(smDCS);

    TransCustomAvp::CAPSMValidityPeriod smValidityPeriod(ccriAvpVal.cap_sm_validityperiod());
    if(ccriAvpVal.has_cap_sm_validityperiod())
        capInfo.setCAPSMValidityPeriod(smValidityPeriod);

    /*TransCustomAvp::CAPSMRejectDuplicate smRD(ccriAvpVal.CAP_SM_RejectDuplicate);
      if(!ccriAvpVal.CAP_SM_RejectDuplicate.empty())
      capInfo.setCAPSMRejectDuplicate(smRD);        */

    TransCustomAvp::CAPSCCPCallingGT sccpClgGT(ccriAvpVal.cap_sccp_callinggt());
    if(ccriAvpVal.has_cap_sccp_callinggt())
        capInfo.setCAPSCCPCallingGT(sccpClgGT);

    TransCustomAvp::CAPSCCPCalledGT sccpCldGT(ccriAvpVal.cap_sccp_calledgt());
    if(ccriAvpVal.has_cap_sccp_calledgt())
        capInfo.setCAPSCCPCalledGT(sccpCldGT);

    TransCustomAvp::CAPTCAPRemoteTransactionId tcapRemoteId(ccriAvpVal.cap_tcap_remote_transaction_id());
    if(ccriAvpVal.has_cap_tcap_remote_transaction_id())
        capInfo.setCAPTCAPRemoteTransactionId(tcapRemoteId);

    TransCustomAvp::CAPTCAPLocalTransactionId tcapLocalId(ccriAvpVal.cap_tcap_local_transaction_id());
    if(ccriAvpVal.has_cap_tcap_local_transaction_id())
        capInfo.setCAPTCAPLocalTransactionId(tcapLocalId);

    TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLAI(ccriAvpVal.cap_cellid_areaid_lai());
    if(ccriAvpVal.has_cap_cellid_areaid_lai())
        capInfo.setCAPCellIDAreaIDLAI(cellIdAreaIdLAI);

    TransCustomAvp::CAPEventTypeSMS evntTypeSMS(ccriAvpVal.cap_event_type_sms());
    capInfo.setCAPEventTypeSMS(evntTypeSMS);

    /*Set TCAPErrorCause */
    if(TSLConstants::DEFAULT_TCAP_ERROR_CAUSE_VAL != ccriAvpVal.cap_tcap_error_cause())
    {
        TransCustomAvp::CAPTCAPErrorCause errCause(ccriAvpVal.cap_tcap_error_cause());
        capInfo.setCAPTCAPErrorCause(errCause);
    }
}

int TransatelCAPToRoHandler::ReturnStartOctet(ITS_OCTET type)
{
    int startIndex = 0;

    if ((type & SCCP_CPA_GTTI_ALL) == SCCP_CPA_GTTI_ALL)
    {
        startIndex = 3;
    }
    else if ((type & SCCP_CPA_GTTI_TNE) == SCCP_CPA_GTTI_TNE)
    {
        startIndex = 2;
    }
    else if ((type & SCCP_CPA_GTTI_TRANS) == SCCP_CPA_GTTI_TRANS)
    {
        startIndex = 1;
    }
    else if ((type & SCCP_CPA_GTTI_NATURE) == SCCP_CPA_GTTI_NATURE)
    {
        startIndex = 1;
    }
    else
    {
        DLOG_ERROR("Received GTT address indicator is INVALID!!!");
    }
    return startIndex;
}

void TransatelCAPToRoHandler::CheckAndUpdateReleaseCause(
        unsigned int& resultCode, TransatelCAPRoTransactionContext*& userData)
{

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    //DLOG_DEBUG("CheckAndUpdateReleaseCause");
    switch(resultCode)
    {
        case DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED:
        case DIAMETER_ERROR_CREDIT_LIMIT_REACHED :
        case ITS_DIA_AUTHORIZATION_REJECT:
        case DIAMETER_ERROR_RATING_FAILED:
            {
                //DLOG_DEBUG("Setting releaseCasue Code to OPERATOR_DETERMINED_BARRING");
                userData->SetReleaseCause(OPERATOR_DETERMINED_BARRING);
                break;
            }
        case DIAMETER_ERROR_CUSTOMER_NOT_FOUND:
            {
                //DLOG_DEBUG("Setting releaseCasue Code to UNIDENTIFIED_SUBSCRIBER");
                userData->SetReleaseCause(UNIDENTIFIED_SUBSCRIBER);
                break;
            }
        case DIAMETER_USER_UNKNOWN:
            {
                //DLOG_DEBUG("Setting releaseCasue Code to UNKNOWN_SUBSCRIBER");
                userData->SetReleaseCause(UNKNOWN_SUBSCRIBER);
                break;
            }
        default :
            {
                //DLOG_DEBUG("Default Setting releaseCasue Code to PROTOCOL_ERROR_UNSPECIFIED");
                userData->SetReleaseCause(PROTOCOL_ERROR_UNSPECIFIED);
                break;
            }
    }
}



void TransatelCAPToRoHandler::SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetLocalTransId Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    StoredIDPSMSToCCRIData ccriData;
    IDPToCCRIData idpData;
    if (userData != NULL)
    {
        if(userData->IsIDPSMSReceived())
            ccriData.CopyFrom(userData->GetStoredIDPSMSToCCRIData());
        else
            idpData.CopyFrom(userData->GetIDPToCCRIData());
    }
    char strDlgId[sizeof(ITS_CTXT)];

    uint32_t localTransid;
    TCAP_TRANS_ENTRY *localTx = NULL;
    localTx = TCAP_FindLocalTx_CCITT(dlgId);
    if(NULL != localTx)
    {
        localTransid = localTx->ltid;
        //DLOG_DEBUG("Local transaction Id %x",localTransid);

        sprintf(strDlgId,"%08x",localTransid);
        uint8_t remId[NYBBLE_SIZE] = {0};
        int len = IWFUtils::StringToTBCD(strDlgId, remId,strlen(strDlgId), 0, true);
        string hexString((const char*)remId,len);
        string strId(strDlgId);
        userData->SetLocalTransIdForCDR(strId);

        if(userData->IsIDPSMSReceived())
        {
            ccriData.set_cap_tcap_local_transaction_id(hexString);
            userData->SetStoredIDPSMSToCCRIData(ccriData);
        }
        else
        {
            idpData.set_tcap_local_transaction_id(hexString);
            userData->SetIDPToCCRIData(idpData);
        }

        /* Populate the TCAP Transaction Entry to be used for replication */
        ctxt->SetTcapLocalTid(localTx->ltid);
        ctxt->SetTcapRemoteTid(localTx->rtid);
        ctxt->SetTcapOrgAddr(localTx->oaddr);
        ctxt->SetTcapDestAddr(localTx->daddr);
        ctxt->SetTcapMtp3Label(localTx->label);

        /*DLOG_DEBUG("LocalTx->ltid : %u",localTx->ltid);
        DLOG_DEBUG("LocalTx->rtid : %u",localTx->rtid);
        DLOG_DEBUG("LocalTx->oaddr.len : %d",localTx->oaddr.len);
        DLOG_DEBUG("LocalTx->oaddr.data : %x",localTx->oaddr.data);
        DLOG_DEBUG("LocalTx->daddr.len : %d",localTx->daddr.len);
        DLOG_DEBUG("LocalTx->daddr.data : %x",localTx->daddr.data);
        DLOG_DEBUG("LocalTx->label.sio : %d",localTx->label.sio);
        DLOG_DEBUG("LocalTx->label.label.data : %x",localTx->label.label.data);*/
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetLocalTransId Exit");
}
/*
   Func description : This func exxtractes below list of IE from camel IDP and map them to TSL specific CCRI AVPs
   in Param1           : capv1 or capv2 IDP arg contianing IEs.
   in_out Param2           : CCR request message which if set with TSL specific AVP like CAP-Information along with other basic AVP.
   Service Key             --> CAP-Service-Key

*/

    template <class T>
int TransatelCAPToRoHandler::InitialDPToCCRI(IwfFsm *ctxt,
        T& in,
        Ro_TSL::CreditControlRequest *out)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    //DLOG_DEBUG("TransatelCAPToRoHandler::InitialDPToCCRI Entry");

    TransatelCAPRoTransactionContext* userData = NULL;
    userData = reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    userData->SetIDPReceived(true);

    //Set Auth-Application-Id
    std::string appId = DIAMETER_RO_APPLICATION_ID;

    TransCustomAvp::CSInformation csinfo;
    TransCustomAvp::CAPInformation capInfoVal;
    IDPToCCRIData ccriData;
    diameter::base::AuthApplicationId authApplicationId(atoi(appId.c_str()));
    out->setAuthApplicationId(authApplicationId);

    //Set Service-Context-Id, CAP_IMSI

    std::string oImsi = "";
    std::string mcc = "", mnc = "";

    std::string callingGtAddrDigits = "";
    if(in.OptionIMSI())
    {
	    const std::vector<byte>& vec = in.GetIMSI().GetArray();
	    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
	    size_t fPos = oImsi.find('F');
	    if (fPos != std::string::npos)
	    {
		    oImsi.erase(fPos, std::string::npos);
	    }
    } else {
	    //As per Transatel flows IMSI can be optional in IDP, setting dummy value to pass the translation rules
	    oImsi = "000000000000";
    }
    IWFUtils::ExtractMncMcc(oImsi, mcc, mnc);
    std::stringstream str1;
    //std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId,
    //        in.GetServiceKey().GetValue(), callingGtAddrDigits)->ServiceContextId();
    std::string RuleName("");
    int32_t skVal = in.GetServiceKey().GetValue();
    int32_t ossn = CAP;
    if(ITS_SUCCESS != ctxt->GetTransactionManager()->Evaluate(oImsi,skVal,RuleName,ossn))
    {
	    DLOG_ERROR("Could not find a RuleName configured.");
	    return !ITS_SUCCESS;
    }
    std::string servCtxtId = IwfController::Instance().Config().RoutingRules().Route(RuleName, callingGtAddrDigits)->ServiceContextId();

    Ro_TSL::ServiceContextId serviceContextId((servCtxtId));
    out->setServiceContextId(serviceContextId);
    userData->SetServiceContextId(servCtxtId);

    // set imsi in transaction data
    ccriData.set_imsi(oImsi);

    Call_Type val;
    if(in.OptionEventTypeBCSM())
    {
        diameter::Unsigned32 BCSMEventVal = (diameter::Unsigned32)in.GetEventTypeBCSM().GetValue();
        const TransCustomAvp::CAPEventTypeBCSM capBCSMEventVal(BCSMEventVal);
        capInfoVal.setCAPEventTypeBCSM(capBCSMEventVal);
        ccriData.set_event_type_bcsm((unsigned int) BCSMEventVal);

        if(TSLConstants::MO_DP_EVENT == in.GetEventTypeBCSM().GetValue())
        {
            val = Call_Type::MO_VOICE;
            userData->SetBcsmEventMO(true);
        }
        else if(TSLConstants::MT_DP_EVENT == in.GetEventTypeBCSM().GetValue())
        {
            val = Call_Type::MT_VOICE;

        }
        else
        {
            DLOG_ERROR("IWF Error: EventTypeBCSM having unexpectedDataValue");
            ctxt->SetErrorCode(CAP_ERR_UNEXPECTED_DATA_VALUE);
            ret = !ITS_SUCCESS;
            return ret;
        }
        ccriData.set_calltypeval(val);
        userData->SetCallType(val);
    }
    else
    {
        DLOG_ERROR("IWF Error: EventTypeBCSM not present in IDP");
        ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
        ret = !ITS_SUCCESS;
        return ret;
    }


    //Set Event-Timestamp

    ITS_UINT seconds = this->GetCurrentTimeStamp();
    diameter::base::EventTimestamp eventTimestamp(seconds);
    out->setEventTimestamp(eventTimestamp);
    userData->SetSessionStartTime(seconds-TIME_FROM_1900_TO_EPOCH);

    //Set CC-Request-Number
    //CC-Request-Type

    ccrnum = userData->GetCCRequestNumber();
    Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
    out->setCCRequestNumber(ccRequestNumber);
    userData->SetCCRequestNumber(ccrnum);

    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);
    out->setCCRequestType(ccRequestType);

    //Set Service-Key, CAP_Version based on RecvAppContextName
    TransCustomAvp::CAPServiceKey capSrvKey((unsigned int)(in.GetServiceKey().GetValue()));
    capInfoVal.setCAPServiceKey(capSrvKey);
    ccriData.set_service_key((unsigned int)in.GetServiceKey().GetValue());

    if(cap::CAPV1_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
    {
        capInfoVal.setCAPVersion(diameter::transatel_custom_avps::CAPVersion(TSLConstants::CAPV1_VERSION));
        ccriData.set_version(TSLConstants::CAPV1_VERSION);
    }
    else if(cap::CAPV2_gsmSSF_to_gsmSCF_AC == userData->GetRecvAppCtxt())
    {
        capInfoVal.setCAPVersion(diameter::transatel_custom_avps::CAPVersion(TSLConstants::CAPV2_VERSION));
        ccriData.set_version(TSLConstants::CAPV2_VERSION);
    }

    //Set Multiple-Service-Indicator, Multiple_Servcie_Credit_Control - USU --CCTime
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    out->setMultipleServicesIndicator(msi);

    Ro_TSL::MultipleServicesCreditControl mscc;
    Ro_TSL::UsedServiceUnit usu;
    int defaultCCTimeVal = 0;
    usu.setCCTime(Ro_TSL::CCTime((diameter::Unsigned64)defaultCCTimeVal));
    mscc.addUsedServiceUnit(usu);
    out->addMultipleServicesCreditControl(mscc);


    Ro_TSL::ServiceInformation si;

#if 0
    //Based on the presence of below IE in IDP, MO or MT call is deduced
    //Both CallingPartyNumber & CalledPartyBCDNumber, then its a MO_Call
    //Both CallingPartyNumber & CallingPartyNumber, then its MT_Call
    //If any one of the above 3 IE absence shall be a CAP_ERR_MISSING_PARMETER case
#endif
    bool buildClgPartyDet = false;
    bool buildCldPtyDet = false;
    std::string callingPartyNumber("");
    std::string cldPartyNo("");
    if(MO_VOICE == val)
    {
        //if((in.OptionCallingPartyNumber()) && (in.OptionCalledPartyBCDNumber()))
        if(in.OptionCalledPartyNumber())
        {
            buildCldPtyDet = true;
        }

        if(in.OptionCallingPartyNumber())
        {
            buildClgPartyDet = true;

        }
        else
        {
            if(!(in.OptionCallingPartyNumber()))
            {
                DLOG_DEBUG("IWF Error: CallingPartyNumber not present in IDP");
            }
            else if(!(in.OptionCalledPartyBCDNumber()))
            {
                DLOG_DEBUG("IWF Info: CalledPartyBCDNumber not present in IDP");
            }
            else if(!(in.OptionCalledPartyNumber()))
            {
                DLOG_DEBUG("IWF Info: CalledPartyNumber not present in IDP");
            }
#ifdef NO_MISSING_PARAM_CHECK_IN_IDP
            ctxt->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
            ret = !ITS_SUCCESS;
            return ret;
#endif
        }
    }

    if(MT_VOICE == val)
    {
        if(in.OptionCalledPartyNumber())
        {
            //MT_Call
            buildCldPtyDet = true;
        }

        if(in.OptionCallingPartyNumber())
        {
            buildClgPartyDet = true;
        }
    }

    if(in.OptionCalledPartyBCDNumber() && (false == buildCldPtyDet))
    {
        //Set CAP-Dialed-Digits, CAP-Called-TON, CAP-Called-NPI

        const std::vector<byte>& vec = in.GetCalledPartyBCDNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), cldPartyNo);//, false , true);
        size_t fPos = cldPartyNo.find('F');
        if (fPos != std::string::npos)
        {
            cldPartyNo.erase(fPos, std::string::npos);
        }

        TransCustomAvp::CAPDialedDigits capDialDigits(cldPartyNo.substr(SUB_STR_POS_2));
        capInfoVal.setCAPDialedDigits(capDialDigits);
        ccriData.set_dialed_digits(cldPartyNo.substr(SUB_STR_POS_2));

        string sOctDigitVal,sOctDigitVal2;
        sOctDigitVal = cldPartyNo.substr(SUB_STR_POS_0+1,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);

        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> byteVal(iOctDigit);
        bitset<NYBBLE_SIZE-1> tonBitVal;

        tonBitVal.reset();
        tonBitVal[BYTE_POS_0] = byteVal[BYTE_POS_0];
        tonBitVal[BYTE_POS_1] = byteVal[BYTE_POS_1];
        tonBitVal[BYTE_POS_2] = byteVal[BYTE_POS_2];

        capInfoVal.setCAPCalledTON(TransCustomAvp::CAPCalledTON(tonBitVal.to_ulong()));
        ccriData.set_called_ton((unsigned int)capInfoVal.getCAPCalledTON().value());

        sOctDigitVal = cldPartyNo.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        sOctDigitVal2 = "";
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> byteVal1(iOctDigit);
        capInfoVal.setCAPCalledNPI(TransCustomAvp::CAPCalledNPI(byteVal1.to_ulong()));
        ccriData.set_called_npi((unsigned int)capInfoVal.getCAPCalledNPI().value());

        cldPartyNo = cldPartyNo.substr(SUB_STR_POS_2);
        //buildClgPartyDet = true;
    }

    //Set CAP_CLI,CAP-Calling-NOA,CAP-CLI-NPI,CAP-CLIR
    if(true == buildClgPartyDet)
    {
        string callingPartyNumberHDR("");
        const std::vector<byte>& vec = in.GetCallingPartyNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], BYTE_POS_2, callingPartyNumberHDR,false, true);
        IWFUtils::TBCDToString(&vec[2], vec.size() - 2, callingPartyNumber);

        IWFUtils::TrimAddrSignal(callingPartyNumber,this->IsDigitsOdd(vec[0]));

        callingPartyNumber = callingPartyNumberHDR + callingPartyNumber;

        TransCustomAvp::CAPCLI capcli(callingPartyNumber.substr(SUB_STR_POS_4));
        capInfoVal.setCAPCLI(capcli);
        //DLOG_DEBUG("CAPCLI AVP:  %s",capInfoVal.getCAPCLI().value().c_str());
        ccriData.set_cli(callingPartyNumber.substr(SUB_STR_POS_4));
        //DLOG_DEBUG("Stored CAPCLI AVP:  %s",ccriData.cli().c_str());


        string sOctDigitVal, sOctDigitVal2;

        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal(iOctDigit);

        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
        CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal2(iOctDigit);

        string octStrVal;
        octStrVal = octVal.to_string();
        octStrVal += octVal2.to_string();
        bitset<BYTE_SIZE> finalOct(octStrVal);
        bitset<BYTE_SIZE - 1> fOct;
        for(int i = 0 ; i< BYTE_SIZE - 1; i++)
        {
            fOct[i] = finalOct[i];
        }

        int capcallNOA = vec[0] & 0x7f;
        //TransCustomAvp::CAPCallingNOA capCgPtyNOA(fOct.to_ulong());
        TransCustomAvp::CAPCLINOA capCgPtyNOA(capcallNOA);
        capInfoVal.setCAPCLINOA(capCgPtyNOA);
        //DLOG_DEBUG("CAP_CallingNOA AVP:  %ul",capInfoVal.getCAPCLINOA().value());
        ccriData.set_calling_noa(fOct.to_ulong());
        //DLOG_DEBUG("Stored CAP_CallingNOA AVP:  %u",ccriData.calling_noa());


        octVal.reset();
        octVal2.reset();
        finalOct.reset();
        octStrVal = "";
        sOctDigitVal2 = "";

        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_2,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        octVal = iOctDigit;
        bitset<NYBBLE_SIZE-1> npiVal;
        for(int i = 0; i < NYBBLE_SIZE-2; i++)
        {
            npiVal[i] = octVal[i];
        }

        TransCustomAvp::CAPCLINPI capCgPtyNPI(npiVal.to_ulong());
        capInfoVal.setCAPCLINPI(capCgPtyNPI);
        //DLOG_DEBUG("CAP_CLI_NPI AVP:  %ul",capInfoVal.getCAPCLINPI().value());
        ccriData.set_cli_npi(npiVal.to_ulong());
        //DLOG_DEBUG("Stored CAP_CLI_NPI AVP:  %u",ccriData.cli_npi());

        octVal.reset();
        sOctDigitVal = callingPartyNumber.substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        octVal = iOctDigit;
        bitset<NYBBLE_SIZE-2> bitLen2;
        //for(int i = NYBBLE_SIZE-2 ; i< NYBBLE_SIZE-1; i++)
        //{
        //    bitLen2[i] = octVal[i];
        //}

        bitLen2[BYTE_POS_0] = octVal[BYTE_POS_2];
        bitLen2[BYTE_POS_1] = octVal[BYTE_POS_3];

        TransCustomAvp::CAPCLIR capCgPtyAddrPresentInd(bitLen2.to_ulong());
        capInfoVal.setCAPCLIR(capCgPtyAddrPresentInd);
        ccriData.set_clir(bitLen2.to_ulong());
        //DLOG_DEBUG("CAP_CLIR AVP:  %ul",capInfoVal.getCAPCLIR().value());
        //DLOG_DEBUG("Stored CAP_CLIR AVP:  %u",ccriData.clir());

        callingPartyNumber = callingPartyNumber.substr(SUB_STR_POS_4);

        buildClgPartyDet = false;
    }

    if(true == buildCldPtyDet)
    {
        //Set CAP-Dialed-Digits, CAP-Called-TON with NOA , CAP-Called-NPI
        //Set CAP_Call_Type
        std::string calledPartyNumber("");
        string calledPartyNumberHDR("");
        const std::vector<byte>& vec = in.GetCalledPartyNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], BYTE_POS_2, calledPartyNumberHDR, false, true);
        IWFUtils::TBCDToString(&vec[2], vec.size() - 2, cldPartyNo);

        IWFUtils::TrimAddrSignal(cldPartyNo,this->IsDigitsOdd(vec[0]));

        TransCustomAvp::CAPDialedDigits capdialdigits(cldPartyNo);
        capInfoVal.setCAPDialedDigits(capdialdigits);
        //DLOG_DEBUG("CAPCAPDialedDigits AVP:  %s",capInfoVal.getCAPDialedDigits().value().c_str());
        ccriData.set_dialed_digits(cldPartyNo);

        /*            string sOctDigitVal, sOctDigitVal2;

                      sOctDigitVal = cldPartyNo.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
                      TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
                      int iOctDigit = atoi(sOctDigitVal2.c_str());
                      bitset<NYBBLE_SIZE> octVal(iOctDigit);

                      sOctDigitVal = cldPartyNo.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
                      TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
                      iOctDigit = atoi(sOctDigitVal2.c_str());
                      bitset<NYBBLE_SIZE> octVal2(iOctDigit);

                      string octStrVal;
                      octStrVal = octVal.to_string();
                      octStrVal += octVal2.to_string();
                      bitset<BYTE_SIZE> finalOct(octStrVal);
                      bitset<BYTE_SIZE - 1> fOct;
                      for(int i = 0 ; i< BYTE_SIZE - 1; i++)
                      {
                      fOct[i] = finalOct[i];
                      }
                      */

        /* Decoding first 7 bits of first Octet of CalledPartyNumber to
         * fill CAP-CALL-TON*/
        unsigned int capcallNPI = vec[0] & 0x7f;
        TransCustomAvp::CAPCalledTON capCldPtyNOA(capcallNPI);
        capInfoVal.setCAPCalledTON(capCldPtyNOA);
        //DLOG_DEBUG("CAP_CalledTON AVP:  %ul",capInfoVal.getCAPCalledTON().value());
        ccriData.set_called_ton(capcallNPI);

        /*
           octVal.reset();
           octVal2.reset();
           finalOct.reset();
           octStrVal = "";
           sOctDigitVal2 = "";

           sOctDigitVal = cldPartyNo.substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_1);
           TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
           iOctDigit = atoi(sOctDigitVal2.c_str());
           octVal = iOctDigit;
           bitset<NYBBLE_SIZE-1> npiVal;
           for(int i = 0; i < NYBBLE_SIZE-2; i++)
           {
           npiVal[i] = octVal[i];
           }*/

        /* Shifting upper nibble by 4 Decoding 0-2 bits of Second Octet
         * of CalledPartyNumber to fill CAP-Called-NPI*/
        unsigned int npiVal = ((vec[1] >> 4) & 0x07);
        TransCustomAvp::CAPCalledNPI capCldPtyNPI(npiVal);
        capInfoVal.setCAPCalledNPI(capCldPtyNPI);
        //DLOG_DEBUG("CAP_Called_NPI AVP:  %ul",capInfoVal.getCAPCalledNPI().value());
        ccriData.set_called_npi(npiVal);


        buildCldPtyDet = false;
    }

    if(in.OptionIMSI())
    {
	    //Set Subscription-Id
	    Ro_TSL::SubscriptionId subsId;
	    subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_IMSI));
	    subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(oImsi));

	    SubscriptionIdConfig* subsIdInfo = ccriData.mutable_subscriptionidinfo();
	    subsIdInfo->set_subidtype(Ro_TSL::SubscriptionIdType::END_USER_IMSI);
	    subsIdInfo->set_subiddata(oImsi);

	    out->addSubscriptionId(subsId);

	    // Set imsi in CCR_I only if received in the IDP
	    TransCustomAvp::CAPIMSI imsiVal(oImsi);
	    capInfoVal.setCAPIMSI(imsiVal);
    }
#if 0
    if(MO_VOICE == ccriData.GetCallType())
    {
        if(callingPartyNumber.find("sip") != std::string::npos)
        {
            subsId->setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_SIP_URI));
            subsId->setSubscriptionIdData(Ro_TSL::SubscriptionIdData(callingPartyNumber));
            out->addSubscriptionId(*subsId);
        }
        else
        {
            subsId->setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_E164));
            subsId->setSubscriptionIdData(Ro_TSL::SubscriptionIdData(callingPartyNumber));
            out->addSubscriptionId(*subsId);
        }
    }
    else if(MT_VOICE == ccriData.GetCallType())
    {
        if(cldPartyNo.find("sip") != std::string::npos)
        {
            subsId->setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_SIP_URI));
            subsId->setSubscriptionIdData(Ro_TSL::SubscriptionIdData(cldPartyNo));
            out->addSubscriptionId(*subsId);
        }
        else
        {
            subsId->setSubscriptionIdType(Ro_TSL::SubscriptionIdType(Ro_TSL::SubscriptionIdType::END_USER_E164));
            subsId->setSubscriptionIdData(Ro_TSL::SubscriptionIdData(cldPartyNo));
            out->addSubscriptionId(*subsId);
        }

    }
#endif

    //Set CAP_MSC_Address

    //if(ctxt->GetTransactionManager()->GetOrigSSN() == MSC_CAP)
    //{
    if(in.OptionMscAddress())
    {
        std::string mscAddress;
        const std::vector<byte>& vec = in.GetMscAddress().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), mscAddress);//, false, true);
        size_t fPos = mscAddress.find('F');
        if (fPos != std::string::npos)
        {
            mscAddress.erase(fPos, std::string::npos);
        }

        capInfoVal.setCAPMSCAddress(TransCustomAvp::CAPMSCAddress(mscAddress.substr(SUB_STR_POS_2)));
        ccriData.set_msc_address( mscAddress.substr(SUB_STR_POS_2));
    }

    //Set Location_Number, LocationInformation -> VLR Number,
    //CAP-CellID-AreaID-LAI,
    if(in.OptionLocationNumber())
    {
        string locnumber;
        const std::vector<byte>& vec = in.GetLocationNumber().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), locnumber);//, false , true);

        string locNumber(locnumber.substr(SUB_STR_POS_4));
        IWFUtils::TrimAddrSignal(locNumber,this->IsDigitsOdd(vec[0]));

        TransCustomAvp::CAPLocationNumber locNo(locNumber);
        capInfoVal.setCAPLocationNumber(locNo);
        //DLOG_DEBUG("Location_Number AVP:  %s",capInfoVal.getCAPLocationNumber().value().c_str());
        ccriData.set_location_number(locNumber);
    }

    if(in.OptionLocationInformation())
    {
        if(in.GetLocationInformation().OptionCellIdOrLAI())
        {
            //CellIdOrLAI cellIdOrLai = in.GetLocationInformation().GetCellIdOrLAI();

            string hexString;
            if(in.GetLocationInformation().GetCellIdOrLAI().ChoiceCellIdFixedLength())
            {
                const std::vector < byte > arr = in.GetLocationInformation().GetCellIdOrLAI().GetChoiceCellIdFixedLength().GetArray();
                TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLaiVal(IWFUtils::VectorToString(arr));
                capInfoVal.setCAPCellIDAreaIDLAI(cellIdAreaIdLaiVal);
                ccriData.set_cellid_areaid_lai(IWFUtils::VectorToString(arr));
            }
            else if(in.GetLocationInformation().GetCellIdOrLAI().ChoiceLaiFixedLength())
            {
                const std::vector < byte > arr = in.GetLocationInformation().GetCellIdOrLAI().GetChoiceLaiFixedLength().GetArray();
                TransCustomAvp::CAPCellIDAreaIDLAI cellIdAreaIdLaiVal(IWFUtils::VectorToString(arr));
                capInfoVal.setCAPCellIDAreaIDLAI(cellIdAreaIdLaiVal);
                ccriData.set_cellid_areaid_lai(IWFUtils::VectorToString(arr));
            }
        }
        if(in.GetLocationInformation().OptionVlr_number())
        {
            string vlrnumber;
            const std::vector<byte>& vec = in.GetLocationInformation().GetVlr_number().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), vlrnumber);
            size_t fPos = vlrnumber.find('F');
            if (fPos != std::string::npos)
            {
                vlrnumber.erase(fPos, std::string::npos);
            }

            TransCustomAvp::CAPVLRNumber vlrNo(vlrnumber.substr(SUB_STR_POS_2));
            capInfoVal.setCAPVLRNumber(vlrNo);
            //DLOG_DEBUG("LocationInfo-->Vlr_Number AVP:  %s",capInfoVal.getCAPVLRNumber().value().c_str());
            ccriData.set_vlr_number(vlrnumber.substr(SUB_STR_POS_2));
        }
    }

    if(in.OptionCallReferenceNumber())
    {
        /*std::string callRef = "";;
          const std::vector<byte>& vec = in.GetCallReferenceNumber().GetArray();
          IWFUtils::TBCDToString(&vec[0], vec.size(), callRef, false , true, true);*/

        TransCustomAvp::CAPCallReference callRefNoVal(IWFUtils::VectorToString(in.GetCallReferenceNumber().GetArray()));
        capInfoVal.setCAPCallReference(callRefNoVal);
        ccriData.set_call_reference(IWFUtils::VectorToString(in.GetCallReferenceNumber().GetArray()));
    }

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    TCAP_Begin *begin = (TCAP_Begin*)inTcapDlg;
    SCCP_CalledPartyAddr destAddr;
    begin->GetDestAddr(destAddr);

    int startIndex = 0;
    if (destAddr.HasGlobalTitle())
    {
        ITS_OCTET type = 0;
        ITS_USHORT gttLen = 0;
        ITS_OCTET gttInfo[64] = {0};

        destAddr.GetGlobalTitle(type, gttInfo, gttLen);
        startIndex = TransatelCAPToRoHandler::ReturnStartOctet(type);
        string gtdigits = "";
        IWFUtils::TBCDToString(&gttInfo[startIndex], (gttLen - startIndex), gtdigits);
        if(gttInfo[1] & 1)
        {
            capInfoVal.setCAPSCCPCalledGT(TransCustomAvp::CAPSCCPCalledGT(gtdigits.substr(0,gtdigits.length()-1)));
            ccriData.set_sccp_calledgt(gtdigits.substr(0,gtdigits.length()-1));
        }
        else
        {
            capInfoVal.setCAPSCCPCalledGT(TransCustomAvp::CAPSCCPCalledGT(gtdigits));
            ccriData.set_sccp_calledgt(gtdigits);
        }
    }

    SCCP_CallingPartyAddr orgAddr;
    begin->GetOrigAddr(orgAddr);

    if(orgAddr.HasGlobalTitle())
    {
        ITS_OCTET type = 0;
        ITS_USHORT gttLen = 0;
        ITS_OCTET gttInfo[64] = {0};
        // Get gloabal title from address
        orgAddr.GetGlobalTitle(type, gttInfo, gttLen);
        startIndex = TransatelCAPToRoHandler::ReturnStartOctet(type);
        string gtdigits = "";
        IWFUtils::TBCDToString(&gttInfo[startIndex], (gttLen - startIndex), gtdigits);
        if(gttInfo[1] & 1)
        {
            capInfoVal.setCAPSCCPCallingGT(TransCustomAvp::CAPSCCPCallingGT(gtdigits.substr(0,gtdigits.length()-1)));
            ccriData.set_sccp_callinggt(gtdigits.substr(0,gtdigits.length()-1));
        }
        else
        {
            capInfoVal.setCAPSCCPCallingGT(TransCustomAvp::CAPSCCPCallingGT(gtdigits));
            ccriData.set_sccp_callinggt(gtdigits);
        }
    }

    if(in.OptionCallingPartysCategory())
    {
        std::string strClgPtyCategory = "";;
        const std::vector<byte>& vec = in.GetCallingPartysCategory().GetArray();
        //NOTE: Mapping the vector[0] value to AVP(typecasting to unsigned int)
        unsigned int capcallcat = (unsigned int) vec[0];
        TransCustomAvp::CAPCallingCategory clgPtyCat(capcallcat);
        capInfoVal.setCAPCallingCategory(clgPtyCat);
        ccriData.set_calling_category(capcallcat);
        //DLOG_DEBUG("CAPCallingCategory AVP:  %d",capcallcat);
    }

    if(in.OptionRedirectingPartyID())
    {
        std::string redirectingPtyId = "";;
        const std::vector<byte>& vec = in.GetRedirectingPartyID().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), redirectingPtyId);
        string redirectingPtyNumber(redirectingPtyId.substr(SUB_STR_POS_4));
        IWFUtils::TrimAddrSignal(redirectingPtyNumber,IsDigitsOdd(vec[0]));

        TransCustomAvp::CAPRedirectingNumber redirectNo(redirectingPtyNumber);
        capInfoVal.setCAPRedirectingNumber(redirectNo);
        ccriData.set_redirecting_number(redirectingPtyNumber);

    }

    if(in.OptionRedirectionInformation())
    {
        std::string redirectInfo = "";;
        const std::vector<byte>& vec = in.GetRedirectionInformation().GetArray();
        IWFUtils::TBCDToString(&vec[0], vec.size(), redirectInfo, false , true);
        size_t fPos = redirectInfo.find('F');
        if (fPos != std::string::npos)
        {
            redirectInfo.erase(fPos, std::string::npos);
        }


        string sOctDigitVal, sOctDigitVal2;

        sOctDigitVal = redirectInfo.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        int iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal1(iOctDigit);
        bitset<NYBBLE_SIZE - 1 > redIndiBitVal;

        for(int i = 0; i< NYBBLE_SIZE - 1; i++)
        {
            redIndiBitVal[i] = octVal1[i];
        }

        TransCustomAvp::CAPRedirectingIndicator redirectIndi(redIndiBitVal.to_ulong());
        capInfoVal.setCAPRedirectingIndicator(redirectIndi);
        ccriData.set_redirecting_indicator((unsigned int)redIndiBitVal.to_ulong());
        //DLOG_DEBUG("CAPRedirectingIndicator AVP:  %ul",capInfoVal.getCAPRedirectingIndicator().value());

        sOctDigitVal = redirectInfo.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal2(iOctDigit);

        TransCustomAvp::CAPOriginalRedirectingReason orgrdirectReasn(octVal2.to_ulong());
        capInfoVal.setCAPOriginalRedirectingReason(orgrdirectReasn);
        ccriData.set_original_redirecting_reason((unsigned int)octVal2.to_ulong());
        //DLOG_DEBUG("CAPOriginalRedirectingReason AVP:  %ul",capInfoVal.getCAPOriginalRedirectingReason().value());

        octVal1.reset();
        octVal2.reset();
        sOctDigitVal2 = "";

        sOctDigitVal = redirectInfo.substr(SUB_STR_POS_2,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal3(iOctDigit);

        TransCustomAvp::CAPRedirectingReason rdirectReasn(octVal3.to_ulong());
        capInfoVal.setCAPRedirectingReason(rdirectReasn);
        ccriData.set_redirecting_reason((unsigned int)octVal3.to_ulong());
        //DLOG_DEBUG("CAPRedirectingReason AVP:  %ul",capInfoVal.getCAPRedirectingReason().value());

        sOctDigitVal = redirectInfo.substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_1);
        TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
        iOctDigit = atoi(sOctDigitVal2.c_str());
        bitset<NYBBLE_SIZE> octVal4(iOctDigit);
        bitset<NYBBLE_SIZE - 1> redCntBitVal;

        for(int i = 0; i< NYBBLE_SIZE - 1; i++)
        {
            redCntBitVal[i] = octVal4[i];
        }

        TransCustomAvp::CAPRedirectionCounter redirectCntr(redCntBitVal.to_ulong());
        capInfoVal.setCAPRedirectionCounter(redirectCntr);
        ccriData.set_redirection_counter((unsigned int)redCntBitVal.to_ulong());
        //DLOG_DEBUG("CAPRedirectionCounter AVP:  %ul",capInfoVal.getCAPRedirectionCounter().value());


    }

    if(in.OptionBearerCapability())
    {
        std::string bearerCap = "";;
        if(in.GetBearerCapability().ChoiceBearerCap())
        {
            const std::vector<byte>& vec  = in.GetBearerCapability().GetChoiceBearerCap().GetArray();
            IWFUtils::TBCDToString(&vec[0], vec.size(), bearerCap,false,true);
            size_t fPos = bearerCap.find('F');
            if (fPos != std::string::npos)
            {
                bearerCap.erase(fPos, std::string::npos);
            }
            ccriData.set_bearer_capability_cdr(bearerCap);

            TransCustomAvp::CAPBearerCapability bearerCapability(IWFUtils::VectorToString(in.GetBearerCapability().GetChoiceBearerCap().GetArray()));
            capInfoVal.setCAPBearerCapability(bearerCapability);
            ccriData.set_bearer_capability(IWFUtils::VectorToString(in.GetBearerCapability().GetChoiceBearerCap().GetArray()));

#if 0
            string sOctDigitVal, sOctDigitVal2;

            sOctDigitVal = bearerCap.substr(SUB_STR_POS_0,SUB_STR_LEN_1);
            TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
            int iOctDigit = atoi(sOctDigitVal2.c_str());
            bitset<NYBBLE_SIZE> octVal(iOctDigit);

            sOctDigitVal = bearerCap.substr(SUB_STR_POS_0 + 1,SUB_STR_LEN_1);
            CheckHexDigit(sOctDigitVal,sOctDigitVal2);
            iOctDigit = atoi(sOctDigitVal2.c_str());
            bitset<NYBBLE_SIZE> octVal2(iOctDigit);

            string octStrVal;
            octStrVal = octVal.to_string();
            octStrVal += octVal2.to_string();
            bitset<BYTE_SIZE> finalOct(octStrVal);
            bitset<NYBBLE_SIZE + 1> fOct;
            for(int i = 0 ; i< BYTE_SIZE - 4; i++)
            {
                fOct[i] = finalOct[i];
            }

            TransCustomAvp::CAPBearerCapabilityTransfer bearerTransferCap(fOct.to_string());
            capInfoVal.setCAPBearerCapabilityTransfer(bearerTransferCap);
            DLOG_DEBUG("CAP_BearerCapabilityTransfer  AVP:  %s",capInfoVal.getCAPBearerCapabilityTransfer().value().c_str());
            ccriData.SetBearer_Capability_Transfer(fOct.to_string());

            octStrVal = "";
            sOctDigitVal2 = "";
            sOctDigitVal = bearerCap.substr(SUB_STR_POS_2,SUB_STR_LEN_1);
            TransatelCAPToRoHandler::CheckHexDigit(sOctDigitVal,sOctDigitVal2);
            iOctDigit = atoi(sOctDigitVal2.c_str());
            bitset<NYBBLE_SIZE> octVal3(iOctDigit);

            sOctDigitVal = bearerCap.substr(SUB_STR_POS_2 + 1,SUB_STR_LEN_1);
            CheckHexDigit(sOctDigitVal,sOctDigitVal2);
            iOctDigit = atoi(sOctDigitVal2.c_str());
            bitset<NYBBLE_SIZE> octVal4(iOctDigit);

            octStrVal = octVal3.to_string();
            octStrVal += octVal4.to_string();
            bitset<BYTE_SIZE> finalOct1(octStrVal);
            bitset<NYBBLE_SIZE + 1> fOct2;
            for(int i = 0 ; i< BYTE_SIZE - 4; i++)
            {
                fOct2[i] = finalOct1[i];
            }

            TransCustomAvp::CAPBearerCapabilityTransferRate bearerTransferRate(fOct2.to_string());
            capInfoVal.setCAPBearerCapabilityTransferRate(bearerTransferRate);
            DLOG_DEBUG("CAP_BearerCapabilityTransferRate  AVP:  %s",capInfoVal.getCAPBearerCapabilityTransferRate().value().c_str());
            ccriData.SetBearer_Capability_Transfer_Rate(fOct2.to_string());

            bitset<NYBBLE_SIZE-2> modeOct;
            modeOct[0] = finalOct1[BYTE_POS_5];
            modeOct[1] = finalOct1[BYTE_POS_6];

            TransCustomAvp::CAPBearerCapabilityTransferMode bearerTransferMode(modeOct.to_string());
            capInfoVal.setCAPBearerCapabilityTransferMode(bearerTransferMode);
            DLOG_DEBUG("CAP_BearerCapabilityTransferMode  AVP:  %s",capInfoVal.getCAPBearerCapabilityTransferMode().value().c_str());
            ccriData.SetBearer_Capability_Transfer_Mode(modeOct.to_string());
#endif

        }
        /*else
        {
            DLOG_INFO("InitialDPToCCRI:: BearerCapability choice not set.");
        }*/
    }

    if(in.OptionExt_basicServiceCode())
    {

        string hexString;
        if(in.GetExt_basicServiceCode().ChoiceExt_BearerService())
        {
            const std::vector < byte > arr = in.GetExt_basicServiceCode().GetChoiceExt_BearerService().GetArray();
            string strbearerSrvCode;
            IWFUtils::TBCDToString(&arr[0], arr.size(), strbearerSrvCode,false,true);
            size_t fPos = strbearerSrvCode.find('F');
            if (fPos != std::string::npos)
            {
                strbearerSrvCode.erase(fPos, std::string::npos);
            }

            TransCustomAvp::CAPExtBasicServiceCode extSrvCode(strbearerSrvCode);
            capInfoVal.setCAPExtBasicServiceCode(extSrvCode);
            ccriData.set_ext_basic_service_code(strbearerSrvCode);
        }
        else if(in.GetExt_basicServiceCode().ChoiceExt_Teleservice())
        {
            const std::vector < byte > arr = in.GetExt_basicServiceCode().GetChoiceExt_Teleservice().GetArray();
            string strtelSrvCode;
            IWFUtils::TBCDToString(&arr[0], arr.size(), strtelSrvCode,false,true);
            size_t fPos = strtelSrvCode.find('F');
            if (fPos != std::string::npos)
            {
                strtelSrvCode.erase(fPos, std::string::npos);
            }
            TransCustomAvp::CAPExtBasicServiceCode extSrvCode(strtelSrvCode);
            capInfoVal.setCAPExtBasicServiceCode(extSrvCode);
            ccriData.set_ext_basic_service_code(strtelSrvCode);
        }

    }

    ITS_CTXT dlgId = ctxt->GetCurrRcvdTcapDlg()->GetDialogueID();
    char strDlgId[sizeof(ITS_CTXT)];
    uint32_t remoteTransId;
    TCAP_TRANS_ENTRY *localTx = NULL;
    localTx = TCAP_FindLocalTx_CCITT(dlgId);
    if(NULL != localTx)
    {
        remoteTransId = localTx->rtid;
        //DLOG_DEBUG("Remote transaction Id %x",remoteTransId);
        sprintf(strDlgId,"%08x",remoteTransId);
        uint8_t remId[NYBBLE_SIZE] = {0};

        int len = IWFUtils::StringToTBCD(strDlgId, remId,strlen(strDlgId), 0, true);
        string hexString((const char*)remId,len);

        TransCustomAvp::CAPTCAPRemoteTransactionId tcapRemoteId(hexString);
        capInfoVal.setCAPTCAPRemoteTransactionId(tcapRemoteId);
        ccriData.set_tcap_remote_transaction_id(hexString);

        string strId(strDlgId);
        userData->SetRemoteTransIdForCDR(strId);

    }

    csinfo.setCAPInformation(capInfoVal);
    userData->SetIDPToCCRIData(ccriData);
    si.setCSInformation(csinfo);
    out->setServiceInformation(si);


    //DLOG_DEBUG("TransatelCAPToRoHandler::InitialDPToCCRI Exit");

    return ret;
}

int TransatelCAPToRoHandler::SetTimerConfig(IwfTimersConfig *req)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetTimerConfig Entry");
    int retVal = CMAPI_SUCCESS;

    for( int curTimer = 0 ; curTimer < req->iwftimersinfo_size() ; curTimer++ )
    {
        IwfTimerConfig timerInfo = req->iwftimersinfo(curTimer);
        if( timerInfo.has_timername() && timerInfo.has_timervalue() )
        {
            if( timerInfo.timername() == VOICE_NO_EVNT )
            {
                m_config.SetVoiceNoEventTimer(timerInfo.timervalue());
                //DLOG_DEBUG("Received Voice No Event Timer : %d",timerInfo.timervalue());
            }
            else if ( timerInfo.timername() == NO_ACR )
            {
                m_config.SetNoACRTimer(timerInfo.timervalue());
                //DLOG_DEBUG("Received Voice No ApplyChargingReport Timer : %d",timerInfo.timervalue());
            }
            else if ( timerInfo.timername() == SMS_NO_EVNT )
            {
                m_config.SetSmsNoEventTimer(timerInfo.timervalue());
                //DLOG_DEBUG("Received SMS No Event Timer : %d",timerInfo.timervalue());
            }
            else if ( timerInfo.timername() == NO_ACTIVITY )
            {
                m_config.SetActivityTimer(timerInfo.timervalue());
                //DLOG_DEBUG("Received Activity Timer : %d",timerInfo.timervalue());
            }
            else if ( timerInfo.timername() == AT_RETRY_COUNT )
            {
                m_config.SetActivityRetryCount(timerInfo.timervalue());
                //DLOG_DEBUG("Received Activity retry count : %d",timerInfo.timervalue());
            }
            else if ( timerInfo.timername() == AT_RESPONSE_TIMEOUT)
            {
                m_config.SetActivityResponseTimer(timerInfo.timervalue());
                //DLOG_DEBUG("Received Activity retry interval : %d",timerInfo.timervalue());
            }
            /*else
            {
                DLOG_WARNING("Unknown timer configuration %s",timerInfo.timername().c_str());
            }*/
        }
        /*else
        {
            DLOG_ERROR("Missing mandatory timer paramter");
        }*/
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetTimerConfig Exit");
    return retVal;
}

int TransatelCAPToRoHandler::DeleteMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::DeleteMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;

    RRBRuleIdVsCallScenario ruleIdCallScenarioLst = m_config.GetRRBRuleLst();
    std::string actionRuleName = req->actionrulename();

    try {
            m_config.DeleteEntryFromActionRuleVsCallScenMap(actionRuleName);
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Delete IWF translator configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("TransatelCAPToRoHandler::DeleteMsgSpecCfg no Translator Rule data present");
        retVal = ADD_PROTOCOL_ACTION_ERR_MSGDET_NOT_PRESENT;
    }

    //DLOG_DEBUG("TransatelCAPToRoHandler::DeleteMsgSpecCfg Exit");
    return retVal;
}

int TransatelCAPToRoHandler::SetMsgSpecCfg(IwfProtocolActionConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg Entry");
    int retVal = CMAPI_SUCCESS;

    int msgDetNum = req->msgdetval_size();
    MsgDet msgDetInst;
    CallScenario callScenarioInst;
    EventType evntTypeInst;
    ArmData armDataInst;
    unsigned int RRBActionId = 1;
    CallScenarioLst callCaseLst;
    RRBRuleIdVsCallScenario ruleIdCallScenarioLst = m_config.GetRRBRuleLst();
    std::string actionRuleName = req->actionrulename();

    try
    {
        if(msgDetNum > 0)
        {
            if(RRBActionId == req->actionid())
            {
                for(int idx = 0 ; idx < msgDetNum ; idx++)
                {
                    msgDetInst = req->msgdetval(idx);
                    callCaseLst.clear();
                    int callScenarioNum = msgDetInst.callscenarioval_size();

                    for(int idx2 = 0; idx2 < callScenarioNum; idx2++)
                    {
                        callScenarioInst = msgDetInst.callscenarioval(idx2);
                        CallScenario_t callScenType;
                        if(callScenarioInst.has_call_typename())
                        {
                            if("MO_CAPV1" == callScenarioInst.call_typename())
                            {
                                int eventTypeNum = callScenarioInst.eventtypeval_size();
                                if(eventTypeNum)
                                {
                                    V1EventLst evntLst;
                                    for(int idx3 = 0; idx3 < eventTypeNum; idx3++)
                                    {
                                        evntTypeInst = callScenarioInst.eventtypeval(idx3);

                                        if(evntTypeInst.has_eventtypename())
                                        {
                                            if("oAnswer" == evntTypeInst.eventtypename())
                                            {
                                                int armDataNum = evntTypeInst.armdatval_size();
                                                if(armDataNum)
                                                {
                                                    TCAPV1Event_ArmData evtData(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER);
                                                    for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                    {
                                                        armDataInst = evntTypeInst.armdatval(idx4);
                                                        if(armDataInst.has_monitormode() && armDataInst.has_legid())
                                                        {
                                                            TLegIDAndModeData legIdMode;
                                                            legIdMode.legId = armDataInst.legid();
                                                            if("interrupted" == armDataInst.monitormode())
                                                            {
                                                                legIdMode.monitorMode = 0;
                                                            }
                                                            if("transparent" == armDataInst.monitormode())
                                                            {
                                                                legIdMode.monitorMode = 2;
                                                            }
                                                            if("notifyAndContinue" == armDataInst.monitormode())
                                                            {
                                                                legIdMode.monitorMode = 1;
                                                            }
                                                            evtData.legIdMonMode.push_back(legIdMode);
                                                            //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oAnswer' : MonitorMode: %d, LegId : %s inserted into V1EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());

                                                        }
                                                        else
                                                        {
                                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig MonitorMode/LegId data absent");
                                                            retVal = ADD_PROTOCOL_ACTION_ERR_ARM_DATA_MANDATORY_PARAM_MISSING;
                                                        }

                                                    }
                                                    //callScenType.MO = evtData;
                                                    evntLst.push_back(evtData);
                                                }
                                            }

                                            if("oDisconnect" == evntTypeInst.eventtypename())
                                            {

                                                int armDataNum = evntTypeInst.armdatval_size();
                                                if(armDataNum)
                                                {
                                                    TCAPV1Event_ArmData evtData(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT);
                                                    for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                    {
                                                        armDataInst = evntTypeInst.armdatval(idx4);
                                                        TLegIDAndModeData legIdMode;
                                                        int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                        if(CMAPI_SUCCESS != ret)
                                                            return ret;
                                                        evtData.legIdMonMode.push_back(legIdMode);

                                                        //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oDisconnect' : MonitorMode: %d, LegId : %s inserted into V1EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                    }
                                                    //callScenType.MO = evtData;
                                                    evntLst.push_back(evtData);
                                                }
                                            }

                                        }
                                        else
                                        {
                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig EventTypeName/ArmData data absent");
                                            retVal = ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING;
                                        }

                                    }
                                    callScenType.MO_V1 = evntLst;
                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'MO_V1' set in CallScenario.");
                                }
                                //callCaseLst.push_back(callScenType);
                            }
                            if("MO_CAPV2" == callScenarioInst.call_typename())
                            {
                                int eventTypeNum = callScenarioInst.eventtypeval_size();
                                if(eventTypeNum)
                                {
                                    V2EventLst evntLst;
                                    for(int idx3 = 0; idx3 < eventTypeNum; idx3++)
                                    {
                                        evntTypeInst = callScenarioInst.eventtypeval(idx3);

                                        if(!(evntTypeInst.has_eventtypename()))
                                        {
                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig EventTypeName/ArmData data absent");
                                            retVal = ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING;
                                        }

                                        if("oAnswer" == evntTypeInst.eventtypename())
                                        {
                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oAnswer' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }

                                        if("oNoAnswer" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oNoAnswer' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }
                                        if("oDisconnect" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oDisconnect' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }
                                        if("oAbandon" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OABANDON);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oAbandon' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }
                                        if("oCalledPartyBusy" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OCALLED_PARTY_BUSY);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'oCalledPartyBusy' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }
                                        if("routeSelectFailure" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'routeSelectFailure' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }
                                    }
                                    callScenType.MO_V2 = evntLst;
                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'MO_V2' set in CallScenario.");
                                }
                                //callCaseLst.push_back(callScenType);
                            }
                            if("MT_CAPV1" == callScenarioInst.call_typename())
                            {
                                int eventTypeNum = callScenarioInst.eventtypeval_size();
                                if(eventTypeNum)
                                {
                                    V1EventLst evntLst;
                                    for(int idx3 = 0; idx3 < eventTypeNum; idx3++)
                                    {
                                        evntTypeInst = callScenarioInst.eventtypeval(idx3);
                                        if(!(evntTypeInst.has_eventtypename()))
                                        {
                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig EventTypeName/ArmData data absent");
                                            retVal = ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING;
                                        }

                                        if("tAnswer" == evntTypeInst.eventtypename())
                                        {
                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV1Event_ArmData evtData(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tAnswer' : MonitorMode: %d, LegId : %s inserted into V1EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                        }

                                        if("tDisconnect" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV1Event_ArmData evtData(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tDisconnect' : MonitorMode: %d, LegId : %s inserted into V1EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v1EventData = evtData;
                                        }
                                    }
                                    callScenType.MT_V1 = evntLst;
                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'MT_V1' set in CallScenario.");
                                }
                                //callCaseLst.push_back(callScenType);
                            }
                            if("MT_CAPV2" == callScenarioInst.call_typename())
                            {
                                int eventTypeNum = callScenarioInst.eventtypeval_size();
                                if(eventTypeNum)
                                {
                                    V2EventLst evntLst;
                                    for(int idx3 = 0; idx3 < eventTypeNum; idx3++)
                                    {
                                        evntTypeInst = callScenarioInst.eventtypeval(idx3);
                                        if(!(evntTypeInst.has_eventtypename()))
                                        {
                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig EventTypeName/ArmData data absent");
                                            retVal = ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING;
                                        }

                                        if("tAnswer" == evntTypeInst.eventtypename())
                                        {
                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tAnswer' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;
                                        }

                                        if("tNoAnswer" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TNO_ANSWER);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tNoAnswer' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;

                                        }
                                        if("tDisconnect" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tDisconnect' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;
                                        }
                                        if("tAbandon" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TABANDON);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tAbandon' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;
                                        }
                                        if("tBusy" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TBUSY);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'tBusy' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;
                                        }
                                        if("routeSelectFailure" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV2Event_ArmData evtData(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    TLegIDAndModeData legIdMode;
                                                    int ret = GetArmDataDetails(armDataInst,legIdMode);
                                                    if(CMAPI_SUCCESS != ret)
                                                        return ret;
                                                    evtData.legIdMonMode.push_back(legIdMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'routeSelectFailure' : MonitorMode: %d, LegId : %s inserted into V2EvntLst.",legIdMode.monitorMode,legIdMode.legId.c_str());
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.MT.v2EventData = evtData;
                                        }
                                    }
                                    callScenType.MT_V2 = evntLst;
                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'MT_V2' set in CallScenario.");
                                }
                                //callCaseLst.push_back(callScenType);
                            }
                            if("SMS_CAPV3" == callScenarioInst.call_typename())
                            {
                                int eventTypeNum = callScenarioInst.eventtypeval_size();
                                if(eventTypeNum)
                                {
                                    V3SMSEventLst evntLst;
                                    for(int idx3 = 0; idx3 < eventTypeNum; idx3++)
                                    {
                                        evntTypeInst = callScenarioInst.eventtypeval(idx3);
                                        if(!(evntTypeInst.has_eventtypename()))
                                        {
                                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig EventTypeName/ArmData data absent");
                                            retVal = ADD_PROTOCOL_ACTION_ERR_EVENT_TYPE_MANDATORY_PARAM_MISSING;
                                        }

                                        if("o-smsSubmitted" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV3SMSEvent_ArmData evtData(cap_v3::EventTypeSMS::EVENT_TYPE_SMS_O_SMS_SUBMITTED);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    int monMode;
                                                    if("interrupted" == armDataInst.monitormode())
                                                    {
                                                        monMode = 0;
                                                    }
                                                    if("transparent" == armDataInst.monitormode())
                                                    {
                                                        monMode = 2;
                                                    }
                                                    if("notifyAndContinue" == armDataInst.monitormode())
                                                    {
                                                        monMode= 1;
                                                    }
                                                    evtData.monitorMode.push_back(monMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'o-smsSubmitted' : MonitorMode: %d inserted into V3SMSEventLst.",monMode);
                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.SMS.v2EventData = evtData;
                                        }
                                        if("o-smsFailure" == evntTypeInst.eventtypename())
                                        {

                                            int armDataNum = evntTypeInst.armdatval_size();
                                            if(armDataNum)
                                            {
                                                TCAPV3SMSEvent_ArmData evtData(cap_v3::EventTypeSMS::EVENT_TYPE_SMS_O_SMS_FAILURE);
                                                for(int idx4 = 0; idx4 < armDataNum; idx4++)
                                                {
                                                    armDataInst = evntTypeInst.armdatval(idx4);
                                                    int monMode;
                                                    if("interrupted" == armDataInst.monitormode())
                                                    {
                                                        monMode = 0;
                                                    }
                                                    if("transparent" == armDataInst.monitormode())
                                                    {
                                                        monMode = 2;
                                                    }
                                                    if("notifyAndContinue" == armDataInst.monitormode())
                                                    {
                                                        monMode= 1;
                                                    }
                                                    evtData.monitorMode.push_back(monMode);
                                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'o-smsFailure' : MonitorMode: %d inserted into V3SMSEventLst.",monMode);

                                                }
                                                evntLst.push_back(evtData);
                                            }
                                            //callScenType.SMS.v2EventData = evtData;
                                        }
                                    }
                                    callScenType.SMS_V3 = evntLst;
                                    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg, 'SMS_V3' set in CallScenario.");
                                }
                            }
                        }
                        else
                        {
                            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig Call_TypeName/EventTypeVal data absent");
                            retVal = ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_MANDATORY_PARAM_MISSING;
                        }
                        callCaseLst.push_back(callScenType);
                    }

                }

#if 0
                else
                {
                    DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig no Call_Scenario data absent");
                    retVal = ADD_PROTOCOL_ACTION_ERR_CALL_SCENARIO_NOT_PRESENT;
                }
#endif
                m_config.InsertActionRuleVsCallScenMap(actionRuleName,callCaseLst);
            }
        }
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Add IWF translator configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("TransatelCAPToRoHandler::SetMsgSpecCfg no Translator Rule data present");
        retVal = ADD_PROTOCOL_ACTION_ERR_MSGDET_NOT_PRESENT;
    }


    //DLOG_DEBUG("TransatelCAPToRoHandler::SetMsgSpecCfg Exit");
    return retVal;

}
    template<class T1, class T2>
int TransatelCAPToRoHandler::BuildCCRFromIncomingERBEvent(IwfFsm *ctxt, T1& erb, T2& eventBcsm, DIA_BASE_CMD *&cmd, IwfReturnAction& ret)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("BuildCCRFromIncomingERBEvent:: Entry");

    int retVal = ITS_SUCCESS;
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    int iMode = userData->GetCAPControlMode();


    ETimerType timerType = ETimerType::NO_EVENT_TIMER;
    STimerInfo fsmTimerData;
    int resultCode = ctxt->GetTimerInfo(timerType, fsmTimerData);

    if((userData->GetBcsmEventMO() && eventBcsm.IsOAnswer()) ||
            ((!userData->GetBcsmEventMO()) && eventBcsm.IsTAnswer()))
    {
        IwfTimer timerObj;
        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
        {
            //DLOG_DEBUG("BuildCCRFromIncomingERBEvent:: TimerType : NO_EVENT_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
        }
        else
        {
            DLOG_ERROR("BuildCCRFromIncomingERBEvent:: Failed to stop TimerType : NO_EVENT_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
        }
        /* Store the ERB Answer TimeStamp to  be used for CDR generation */
        ITS_UINT seconds = this->GetCurrentTimeStamp();
        userData->SetErbAnswerTimeStamp(seconds-TIME_FROM_1900_TO_EPOCH);
    }
    /* setting default ret.action to IWF_RA_CONSUME to avoid undesirable
     * behavior, TODO: ErrorHandling */
    ret.dir = IWF_RD_DIA;
    ret.action = IWF_RA_CONSUME;

    switch(userData->GetSCPAction())
    {
        case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON :
            {
                TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
                if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE &&
                        ((userData->GetBcsmEventMO() && eventBcsm.IsOAnswer()) ||
                         ((!userData->GetBcsmEventMO()) && eventBcsm.IsTAnswer())))
                {
                    //DLOG_DEBUG("ERB O/T Answer Received for TRANSPARENT_FOLLOW_ON case Consume it.");
                    ret.dir = IWF_RD_DIA;
                    ret.action = IWF_RA_CONSUME;

                    //DLOG_DEBUG("SCP-Action is Transparent Follow-On. Starting ConnectMaxCallDuration Timer");
                    //Start Fakce-ACH-Timer
                    StartTimerHandling(ctxt, ETimerType::CONNECT_MAX_CALL_DURATION);
                }
                else if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE &&
                        ((userData->GetBcsmEventMO() && eventBcsm.IsODisconnect()) ||
                         ((!userData->GetBcsmEventMO()) && eventBcsm.IsTDisconnect())||
                         (true == userData->IsContinueCallSet())))
                {
                    //if ERB with o/t Disconnect comes stop the ConnectMaxDuration time
                    ETimerType timerType = ETimerType::CONNECT_MAX_CALL_DURATION;
                    STimerInfo fsmTimerData;
                    resultCode = ctxt->GetTimerInfo(timerType, fsmTimerData);

                    IwfTimer timerObj;
                    if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                    {
                        /*DLOG_DEBUG("BuildCCRFromIncomingERBEvent:: TimerType : CONNECT_MAX_CALL_DURATION, TimerId : %u stopped.",
                                fsmTimerData.m_uiTimerId);*/
                        ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                    }
                    else
                    {
                        DLOG_ERROR("BuildCCRFromIncomingERBEvent:: Failed to stop TimerType : CONNECT_MAX_CALL_DURATION, TimerId : %u.",
                                fsmTimerData.m_uiTimerId);
                    }

                    //Extract DisconnectSpecInfo & update in RoTransCtxt
                    pbERBData erbData;
                    erbData.CopyFrom(userData->GetERBData());
                    string sDisconSpecInfo("");
                    FetchDisconEvtSpecInfo(erb,sDisconSpecInfo,ctxt);
                    if(!sDisconSpecInfo.empty())
                    {
                        erbData.set_eventspecinfo(sDisconSpecInfo);
                    }
                    userData->SetERBData(erbData);

                    if(ExtractLegIdFromErb(erb) == TSLConstants::CalledLegID)
                    {
                        TcapCptList *cmptList = ctxt->GetTcapCptList();
                        DIA_BASE_CMD *bcmd = ctxt->GetCurrRcvdDiaMsg();
                        diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
                        Ro_TSL::CreditControlAnswer *cca = NULL;
                        TransCustomAvp::ServiceControl servControl;
                        if (cmd->getAvpValue(IWF_SERVICE_CONTROL_AVP_CODE, &servControl,
                                    diameter::GroupedType) == 0)
                        {
                            cca = new Ro_TSL::CreditControlAnswer(cmd->getImpl());
                        }
                        else
                        {
                            DLOG_DEBUG("Curr Received Dia Msg is not set, not building CCA");
                        }

                        /* Reseting the ERBData and AnswerTimeStamp of First session before second session
                         * is started for Transparent-FollowOn */

                        ResetInitialSessionContext(ctxt);

                        userData->SetSCPAction(TransCustomAvp::SCPAction::CONNECT);
                        //DLOG_DEBUG("Modified SCP-Action %d", userData->GetSCPAction());

                        if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                        {
                            //DLOG_DEBUG("ERB O/T Disconnect Received for TRANSPARENT_FOLLOW_ON case Constructing RRB CONNECT");
                            ConstructRRB_CON(ctxt, cca, cmptList);
                            userData->SetFirstERBReceived(false);
                        }
                        else if(iMode == TransCustomAvp::CAPControlMode::REMOTE_CONTROL)
                        {
                            //DLOG_DEBUG("ERB O/T Disconnect Received for TRANSPARENT_FOLLOW_ON case Constructing RRB ACH CONNECT");
                            ConstructRRB_CON_ACh(ctxt, cca, cmptList);
                            userData->SetFirstERBReceived(false);
                        }
                        ret.dir = IWF_RD_TCAP;
                        ret.action = IWF_RA_RESPOND_ONLY;
                        userData->SetTranslatorState(RRB_SENT);
                    }
                    else
                    {
                        DLOG_ERROR("Unknown LegId Received : %d", ExtractLegIdFromErb(erb));
                        bool triggerCCRT = CheckBCSMEventAndDialogueType(ctxt, erb, eventBcsm, ret);
                        if(true == triggerCCRT)
                        {
                            DLOG_DEBUG("Sending CCR-T & ReleaseCall.");
                            BuildCCRTerminateForIDP(ctxt,(diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd);
                        }
                    }
                    userData->SetContinueCall(false);
                }
                break;
            }
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT :
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE :
        case TransCustomAvp::SCPAction::CONTINUE :
        case TransCustomAvp::SCPAction::CONNECT  :
            {
                if(userData)
                {
                    //DLOG_DEBUG("Current SCP-Action %d", userData->GetSCPAction());
                    Ro_TSL::UsedServiceUnit usu;
                    if((userData->GetBcsmEventMO() && eventBcsm.IsOAnswer()) || ((!userData->GetBcsmEventMO()) && eventBcsm.IsTAnswer()))
                    {
                        if((!userData->GetBcsmEventMO()) &&
                            (userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT || userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE))
                        {
                            if(true == m_config.GetFollowOnTAnsTrigger())
                            {
                                userData->SetTriggerFollowOnSession(false);
                                //DLOG_DEBUG("CallType MT, Trigger FollowOnSession set to %s", userData->GetTriggerFollowOnSession()?"true":"false");
                            }
                        }
                        StoreCallAnswerTimeStamp(userData);
                        /* As soon as ERB  with OAnswer/TAnswer
                         * is recieved start the ActivityTest Timer
                         * and upon timeout sent the ActivityTest
                         * Message towards MSC, update the timer configuration in
                         * the UserData ActivityTest structure*/

                        //DLOG_DEBUG("Starting ActivityTest Timer");
                        //ActivityTimerData activityTest = userData->GetActivityTimerData();
                        pbActivityTimerData activityTest;
                        ActivityTimerConfig activityConfig = m_config.ActivityTimer();
                        activityTest.set_retrycount(activityConfig.retryCount);
                        activityTest.set_attimer(activityConfig.timerValue);
                        activityTest.set_responsetimeout(activityConfig.responseTimeout);
                        userData->SetActivityTimerData(activityTest);

                        StartTimerHandling(ctxt, ETimerType::ACTIVITY_TIMER);
                        if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                        {
                            //DLOG_DEBUG("Mode is LOCAL_CONTROL. Starting Fake ACH Timer");
                            //Start Fakce-ACH-Timer
                            StartTimerHandling(ctxt, ETimerType::FAKE_ACH_TIMER);
                        }
                        else if(iMode == TransCustomAvp::CAPControlMode::REMOTE_CONTROL)
                        {
                            //DLOG_DEBUG("Mode is REMOTE_CONTROL. Starting ACR Timer");
                            //Start Fakce-ACH-Timer
                            StartTimerHandling(ctxt, ETimerType::ACR_TIMER);
                        }
                        ERB_To_CCR_Update(ctxt, erb, NULL);
                        ret.dir = IWF_RD_DIA;
                        ret.action = IWF_RA_CONSUME;
                    }


                    else if((userData->GetBcsmEventMO() && eventBcsm.IsODisconnect()) || (!userData->GetBcsmEventMO() && eventBcsm.IsTDisconnect())||
                            (true == userData->IsContinueCallSet()))
                    {
                        /*Stop AT Timer on recv ERB(O-TDisconnect) */
                        ETimerType timerType = ETimerType::ACTIVITY_TIMER;
                        STimerInfo fsmTimerData;
                        ctxt->GetTimerInfo(timerType, fsmTimerData);

                        IwfTimer timerObj;
                        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                        {
                            /*DLOG_DEBUG("BuildCCRFromIncomingERBEvent:: TimerType : %s, TimerId : %u stopped.",
                                    (GetStrTimerType(fsmTimerData.m_eTimerType)).c_str(),
                                    fsmTimerData.m_uiTimerId);*/
                            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                        }
                        else
                        {
                            DLOG_ERROR("BuildCCRFromIncomingERBEvent:: Failed to stop TimerType : %s, TimerId : %u.",
                                    (GetStrTimerType(fsmTimerData.m_eTimerType)).c_str(),
                                    fsmTimerData.m_uiTimerId);
                        }


                        bool m_triggerCCRTerminate = CheckBCSMEventAndDialogueType(ctxt, erb, eventBcsm, ret);

                        if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
                        {
                            //if control mode is LOCAL, stop the Fake ACH timer, set the curr USU as elapsed time
                            ETimerType timerType = ETimerType::FAKE_ACH_TIMER;
                            STimerInfo fsmTimerData;
                            resultCode = ctxt->GetTimerInfo(timerType, fsmTimerData);

                            IwfTimer timerObj;
                            if(ITS_SUCCESS != timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                            /*{
                                DLOG_DEBUG("BuildCCRFromIncomingERBEvent:: TimerType : FAKE_ACH_TIMER, TimerId : %u stopped.",fsmTimerData.m_uiTimerId);
                            }
                            else*/
                            {
                                DLOG_ERROR("BuildCCRFromIncomingERBEvent:: Failed to stop TimerType : FAKE_ACH_TIMER, TimerId : %u.",fsmTimerData.m_uiTimerId);
                            }

                            unsigned int uiElapsedTime = 0;
                            uiElapsedTime = RetrieveTotalCallTimeDuration(ctxt);
                            //timerObj.GetElapsedTime(fsmTimerData, uiElapsedTime);

                            //DLOG_DEBUG("UI ElapsedTime : %d", uiElapsedTime);
                            userData->SetUSUCCTime(uiElapsedTime);
                            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                            ret.dir = IWF_RD_DIA;
                            //ret.action = IWF_RA_FORWARD;
                            m_triggerCCRTerminate = true;
                        }
                        else if(iMode == TransCustomAvp::CAPControlMode::REMOTE_CONTROL)
                        {
                            //if control mode is LOCAL, stop the Fake ACH timer, set the curr USU as elapsed time
                            ETimerType timerType = ETimerType::ACR_TIMER;
                            STimerInfo fsmTimerData;
                            resultCode = ctxt->GetTimerInfo(timerType, fsmTimerData);

                            IwfTimer timerObj;
                            if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
                            {
                                //DLOG_DEBUG("BuildCCRFromIncomingERBEvent:: TimerType : ACR_TIMER, TimerId : %u stopped.",fsmTimerData.m_uiTimerId);
                                ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
                            }
                            else
                            {
                                DLOG_ERROR("BuildCCRFromIncomingERBEvent:: Failed to stop TimerType : ACR_TIMER, TimerId : %u.",fsmTimerData.m_uiTimerId);
                            }
                            ret.dir = IWF_RD_DIA;
                            //ret.action = IWF_RA_CONSUME;
                        }

                        if(m_triggerCCRTerminate)
                        {
                            Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest;
                            ERB_To_CCR_Terminate(ctxt, erb, ccr);
                            SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
                            SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), IWF_DEFAULT_SERVICE_KEY, ccr);
                            cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
                            cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);
                            LogRoTslDiaMsg(*ccr, false);

                            m_dccaHandler.HandleRequest(userData->GetDccaContext(),
                                    cmd, Ro_TSL::CCRequestType::TERMINATION_REQUEST);

                            userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
                        }
                        else
                        {
                            ERB_To_CCR_Terminate(ctxt, erb, NULL);
                        }
                    }
                    userData->SetContinueCall(false);
                }
            }
            break;
        case TransCustomAvp::SCPAction::REJECT   :
            break;
            //case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT     :
            //break;
            //case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE    :
            //break;
        default :
            {
                DLOG_ERROR("ExtractScpActionData:: Invalid ScpAction value: %d.",userData->GetSCPAction());
                userData->SetTerminationCause(DIA_TERM_CAUSE_INVALID_SCP_ACTION);
                retVal = !ITS_SUCCESS;
                break;
            }
    }
    return retVal;
}

    template<class T1, class T2>
bool TransatelCAPToRoHandler::CheckBCSMEventAndDialogueType(IwfFsm* ctxt, T1& erb, T2& eventBcsm, IwfReturnAction& ret)
{
    bool triggerCCRT = false;
    //DLOG_DEBUG("TransatelCAPToRoHandler::CheckBCSMEventAndDialogueType Entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    TCAP_Component *currRcvdTcapCpt = ctxt->GetCurrRcvdTcapCpt();

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    if(inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE)
    {
        userData->SetCurrentReceivedTcapContinue(true);
        if((userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT ||
                    userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE) && ExtractLegIdFromErb(erb) == TSLConstants::CalledLegID)
        {
            if((!userData->GetBcsmEventMO())&& (false== userData->GetTriggerFollowOnSession()))
            {
                //DLOG_INFO("tAnswerTriggerFollowOnSession set to %s, Trigger CCR-T and close call.",m_config.GetFollowOnTAnsTrigger()?"true":"false");
                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                triggerCCRT = true;
            }
            /* To consume subsequent ERB(Discon) in separate TC_Cont or same TC_Cont message after CCR-T is triggered for ACR(ca=false)*/
            if (userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST &&
                    userData->IsFollowingOnSet() != true)
            {
                //DLOG_DEBUG("ERB Received in TC_Continue for FOLLOW_ON case");
                ret.action = IWF_RA_FORWARD;
                triggerCCRT = true;
            }
            else
            {
                //DLOG_DEBUG("ERB Received in TC_Continue .");
                ret.action = IWF_RA_CONSUME;
            }

        }
        else
        {
            if(currRcvdTcapCpt->GetLast())
            {
                //DLOG_DEBUG("ERB Received in TC_Continue for NORMAL case");
                ret.action = IWF_RA_RESPOND_AND_FORWARD;
                triggerCCRT = true;
            }
            else
            {
                //DLOG_DEBUG("ERB Received in TC_Continue for NORMAL case and is not last Component");
                ret.action = IWF_RA_CONSUME;
            }
        }
    }
    else if(inTcapDlg->GetDialogueType() == TCPPT_TC_END)
    {
        userData->SetCurrentReceivedTcapContinue(false);
        if(currRcvdTcapCpt->GetLast())
        {
            if(userData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::TERMINATION_REQUEST)
            {
                /* Checking the CC-RequestType if already a CCR-T is triggered just
                 * consume otherwise FORWARD*/
                //DLOG_INFO("Received ERB in TC_End, But already CCR-T is sent so CONSUME it..!!!");
                ret.action = IWF_RA_CONSUME;
                ret.dir = IWF_RD_DIA;
            }
            else
            {
                //DLOG_DEBUG("ERB Received in TC_End as LastComponent, trigger CCR-T");
                ret.action = IWF_RA_FORWARD;
                triggerCCRT = true;
            }
        }
        else
        {
            if((userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT ||
                        userData->GetSCPAction() == TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE))
            {
                //DLOG_DEBUG("ERB Received in TC_End for follow-On case so trigger CCR-Terminate");
                ret.action = IWF_RA_FORWARD;
                triggerCCRT = true;
            }
            else
            {
                //DLOG_DEBUG("ERB Received in TC_End but not Last Component");
                ret.action = IWF_RA_CONSUME;
            }
        }
    }

    //DLOG_DEBUG("TransatelCAPToRoHandler::CheckBCSMEventAndDialogueType Exit");
    return triggerCCRT;

}

    template<class T1>
int TransatelCAPToRoHandler::ExtractLegIdFromErb(T1& erb)
{
    //DLOG_DEBUG("TransatelCAPToRoHandler::ExtractLegIdFromErb Entry");
    uint32_t lt = 0;
    if (erb.OptionLegID())
    {
        if ( erb.GetLegID().ChoiceReceivingSideID() )
        {
            const std::vector<byte>& vec = erb.GetLegID().GetChoiceReceivingSideID().GetArray();
            lt = uint32_t (vec[0]);
        }
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::ExtractLegIdFromErb Exit");
    return lt;
}

    template<class T>
void TransatelCAPToRoHandler::ERB_To_CCR_Update(IwfFsm *ctxt,
        const T& in,
        Ro_TSL::CreditControlRequest *out, bool bIsTimeout)
{

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::ERB_To_CCR_Update Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    pbERBData erbData;
    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    Ro_TSL::ServiceInformation si;
    Ro_TSL::MultipleServicesCreditControl mscc;

    if(out != NULL)
    {
        diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
        out->setAuthApplicationId(authApplicationId);

        //Set Multiple-Service-Indicator, Multiple_Servcie_Credit_Control - USU --CCTime
        Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
        out->setMultipleServicesIndicator(msi);

        if (userData)
        {
            struct timeval tv = GetCurrentMonotonic();
            userData->SetUpdateTriggerTimeStamp(tv.tv_sec);

            /* Setting CCRequest number from UserData */
            unsigned int ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
            out->setCCRequestNumber(ccRequestNumber);
            userData->SetCCRequestNumber(ccrnum);

            /* Storing the last Sent CC-Request-Type to be used for validating incoming anser msg from ocs*/
            userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::UPDATE_REQUEST);

            ITS_UINT seconds = this->GetCurrentTimeStamp();
            diameter::base::EventTimestamp eventTimestamp(seconds);
            out->setEventTimestamp(eventTimestamp);

            //DLOG_DEBUG("ServiceContextId fetched from Couchbase %s",userData->GetServiceContextId().c_str());
            Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
            out->setServiceContextId(serviceContextId);

            int iMode = userData->GetCAPControlMode();
            Ro_TSL::UsedServiceUnit usu;
            if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
            {
                //Set the Timeout Value
                ETimerType timerType = ETimerType::FAKE_ACH_TIMER;
                STimerInfo osInfo;
                ctxt->GetTimerInfo(timerType, osInfo);
                userData->SetUSUCCTime(userData->GetUSUCCTime() + osInfo.m_uiDuration);
                Ro_TSL::CCTime cctime(userData->GetUSUCCTime());
                usu.setCCTime(cctime);
            }
            else
            {
                //NEED TO DECIDE WHAT TIME WE HAVE TO SET
                /*TODO:Get the stored Granted-Service-Unit.CCTime from CCA-I and populate it Used-Service-Unit.CCTime */
                //usu.setCCTime(userData->GetLastGSUCCTIME());
            }

            mscc.addUsedServiceUnit(usu);

            //setting CCTYPE as UPDATE_REQUEST
            out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::UPDATE_REQUEST));
            //DLOG_DEBUG("setting CCTYPE as UPDATE_REQUEST");
        }
    }

    TransCustomAvp::CAPERBSInformation capErbInfo;
    if (!bIsTimeout)
    {
        /*EventTypeBCSM is mapped to CAP-Event-Type-BSCM under CAP-ERB-Information avp */
        const TransCustomAvp::CAPEventTypeBCSM capEventTypeBcsm((unsigned int)in.GetEventTypeBCSM().GetValue());
        capErbInfo.setCAPEventTypeBCSM(capEventTypeBcsm);
        erbData.set_erbrecvevttype((unsigned int)in.GetEventTypeBCSM().GetValue());

        /* LegID->ReceivingSideID is mapped to CAP-ERB-LegID */
        if (in.OptionLegID())
        {
            if ( in.GetLegID().ChoiceReceivingSideID() )
            {
                const std::vector<byte>& vec = in.GetLegID().GetChoiceReceivingSideID().GetArray();
                uint32_t lt = uint32_t (vec[0]);
                const TransCustomAvp::CAPERBSLegId capErbLegId(lt);
                capErbInfo.setCAPERBSLegId(capErbLegId);
                erbData.set_recvlegid(lt);
            }
        }

        /*miscCallInfo->MessageType is mapped to CAP-ERB-MessageType */
        const TransCustomAvp::CAPERBSMessageType capErbMsgType((unsigned int) in.GetMiscCallInfo().GetMessageType().GetValue());
        capErbInfo.setCAPERBSMessageType(capErbMsgType);
        erbData.set_msgtype((unsigned int) in.GetMiscCallInfo().GetMessageType().GetValue());
        userData->SetERBData(erbData);
    }
    else
    {
        pbERBData erbData;
        erbData.CopyFrom(userData->GetERBData());
        RetrieveERBData(capErbInfo, erbData);
        capInfo.setCAPERBSInformation(capErbInfo);
    }

    IDPToCCRIData ccriData;
    ccriData.CopyFrom(userData->GetIDPToCCRIData());
    RetrieveIDPToCCRIData(capInfo, ccriData);
    csInfo.setCAPInformation(capInfo);
    si.setCSInformation(csInfo);
    if(out != NULL)
    {
        out->setServiceInformation(si);
        out->addMultipleServicesCreditControl(mscc);
        if(ccriData.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriData.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType((Ro_TSL::SubscriptionIdType::Value)ccriData.subscriptionidinfo().subidtype()));
            }
            if(ccriData.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriData.subscriptionidinfo().subiddata()));
            }
            out->addSubscriptionId(subsId);
        }
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::ERB_To_CCR_Update Exit");
}

    template<class T>
void TransatelCAPToRoHandler::ERB_To_CCR_Terminate(IwfFsm *ctxt,
        const T& in,
        Ro_TSL::CreditControlRequest *out, bool bIsTimeout)
{

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::ERB_To_CCR_Terminate Entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    pbERBData erbData;
    Ro_TSL::MultipleServicesCreditControl mscc;
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    Ro_TSL::ServiceInformation si;

    TransCustomAvp::CAPERBSInformation capErbInfo;
    if(out != NULL)
    {
        diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
        out->setAuthApplicationId(authApplicationId);

        out->setMultipleServicesIndicator(msi);
        if (userData)
        {
            userData->ClearUpdateTriggerTimeStamp();
            /* Setting CCRequest number from UserData */
            unsigned int ccrnum = userData->GetCCRequestNumber();
            Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
            out->setCCRequestNumber(ccRequestNumber);
            userData->SetCCRequestNumber(ccrnum);

            ITS_UINT seconds = this->GetCurrentTimeStamp();
            diameter::base::EventTimestamp eventTimestamp(seconds);
            out->setEventTimestamp(eventTimestamp);

            if(userData->HasServiceContextId())
            {
                Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
                out->setServiceContextId(serviceContextId);
            }

            if(userData)
            {
                out->setTerminationCause(diameter::base::TerminationCause
                        ((diameter::base::TerminationCause::Value)GetTerminationCauseCode(userData)));
                userData->SetTerminationCause(GetTerminationCauseCode(userData));
                userData->SetASRReceived(false);
            }
            else
            {
                out->setTerminationCause(diameter::base::TerminationCause(diameter::base::TerminationCause::DIAMETER_LOGOUT));
            }

            /* Storing the last Sent CC-Request-Type to be used for validating incoming anser msg from ocs*/
            userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);

            int iMode = userData->GetCAPControlMode();
            Ro_TSL::UsedServiceUnit usu;
            if (iMode == TransCustomAvp::CAPControlMode::LOCAL_CONTROL)
            {
                //Set the Timeout Value
                //ETimerType timerType = ETimerType::FAKE_ACH_TIMER;
                //STimerInfo osInfo = ctxt->GetTimerInfo(timerType);
                //DLOG_DEBUG("USU TIme : %d", userData->GetUSUCCTime());
                Ro_TSL::CCTime cctime(userData->GetUSUCCTime());
                usu.setCCTime(cctime);
            }
            else if(iMode == TransCustomAvp::CAPControlMode::REMOTE_CONTROL)
            {
                uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                userData->SetUSUCCTime(totalUsedSeconds);
                Ro_TSL::CCTime cctime(totalUsedSeconds);
                usu.setCCTime(cctime);
            }
            mscc.addUsedServiceUnit(usu);
        }
        //setting CCTYPE as TERMINATE_REQUEST
        out->setCCRequestType(Ro_TSL::CCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST));
        //DLOG_DEBUG("setting CCTYPE as TERMINATE_REQUEST");
    }


    if (!bIsTimeout)
    {
        /*EventTypeBCSM is mapped to CAP-Event-Type-BSCM under CAP-ERB-Information avp */
        const TransCustomAvp::CAPEventTypeBCSM capEventTypeBcsm((unsigned int)in.GetEventTypeBCSM().GetValue());
        capErbInfo.setCAPEventTypeBCSM(capEventTypeBcsm);
        erbData.set_erbrecvevttype((unsigned int)in.GetEventTypeBCSM().GetValue());
        //DLOG_DEBUG("Terminate Stored ERB-CAPEventTypeBCSM AVP:  %u",erbData.erbrecvevttype());


        /* LegID->ReceivingSideID is mapped to CAP-ERB-LegID */
        if (in.OptionLegID())
        {
            if ( in.GetLegID().ChoiceReceivingSideID() )
            {
                const std::vector<byte>& vec = in.GetLegID().GetChoiceReceivingSideID().GetArray();
                uint32_t lt = uint32_t (vec[0]);
                const TransCustomAvp::CAPERBSLegId capErbLegId(lt);
                capErbInfo.setCAPERBSLegId(capErbLegId);
                erbData.set_recvlegid(lt);
                //DLOG_DEBUG("Terminate Stored ERB-CAPERBLegId AVP:  %u",erbData.recvlegid());

            }

            /*miscCallInfo->MessageType is mapped to CAP-ERB-MessageType */
            const TransCustomAvp::CAPERBSMessageType capErbMsgType((unsigned int) in.GetMiscCallInfo().GetMessageType().GetValue());
            capErbInfo.setCAPERBSMessageType(capErbMsgType);
            erbData.set_msgtype((unsigned int) in.GetMiscCallInfo().GetMessageType().GetValue());
            //DLOG_DEBUG("Terminate Stored ERB-CAPERBMessageType AVP:  %u",erbData.msgtype());

            /* TODO : Remove this extraction of ERBData since taken care in validate function */
            if(TSLConstants::EVENT_TYPE_BCSM_ODISCONNECT == in.GetEventTypeBCSM().GetValue()||
                    TSLConstants::EVENT_TYPE_BCSM_TDISCONNECT == in.GetEventTypeBCSM().GetValue())
            {
                //Extract EventSpecInfo in case of O-TDisconnect Event & update in RoTransCtxt
                if(in.OptionEventSpecificInformationBCSM())
                {
                    if(in.GetEventSpecificInformationBCSM().ChoiceODisconnectSpecificInfo())
                    {
                        if(in.GetEventSpecificInformationBCSM().GetChoiceODisconnectSpecificInfo().OptionReleaseCause())
                        {
                            const std::vector<byte>& vec = in.GetEventSpecificInformationBCSM().GetChoiceODisconnectSpecificInfo().GetReleaseCause().GetArray();
                            string evtSpecInfo;
                            IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);
                            uint8_t remId[NYBBLE_SIZE-2] = {0};
                            int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                            string hexString((const char*)remId,len);
                            erbData.set_eventspecinfo(hexString);
                            userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                            //DLOG_INFO("CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                        }
                    }
                    if(in.GetEventSpecificInformationBCSM().ChoiceTDisconnectSpecificInfo())
                    {
                        if(in.GetEventSpecificInformationBCSM().GetChoiceTDisconnectSpecificInfo().OptionReleaseCause())
                        {
                            const std::vector<byte>& vec = in.GetEventSpecificInformationBCSM().GetChoiceTDisconnectSpecificInfo().GetReleaseCause().GetArray();
                            string evtSpecInfo;
                            IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);
                            uint8_t remId[NYBBLE_SIZE-2] = {0};
                            int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                            string hexString((const char*)remId,len);
                            erbData.set_eventspecinfo(hexString);
                            userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                            //DLOG_INFO("CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                        }
                    }

                }
            }
            pbERBData storedERBData = userData->GetERBData();
            if(!storedERBData.has_eventspecinfo())
            {
                userData->SetERBData(erbData);
            }
        }
    }
    {
        pbERBData erbData;
        erbData.CopyFrom(userData->GetERBData());
        RetrieveERBData(capErbInfo, erbData);
        if((userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_OANSWER != erbData.erbrecvevttype())) ||
                (!userData->GetBcsmEventMO() && (TSLConstants::EVENT_TYPE_BCSM_TANSWER != erbData.erbrecvevttype())))
        {
            capInfo.setCAPERBSInformation(capErbInfo);
        }
    }

    IDPToCCRIData ccriData;
    ccriData.CopyFrom(userData->GetIDPToCCRIData());
    RetrieveIDPToCCRIData(capInfo, ccriData);
    csInfo.setCAPInformation(capInfo);
    si.setCSInformation(csInfo);
    if(out != NULL)
    {
        out->setServiceInformation(si);
        out->addMultipleServicesCreditControl(mscc);

        if(ccriData.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriData.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType((Ro_TSL::SubscriptionIdType::Value)ccriData.subscriptionidinfo().subidtype()));
            }
            if(ccriData.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriData.subscriptionidinfo().subiddata()));
            }
            out->addSubscriptionId(subsId);
        }
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::ERB_To_CCR_Terminate Exit");

}

int TransatelCAPToRoHandler::BuildActivityTest(IwfFsm *ctxt, TCAP_Component *&cpt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildActivityTest Entry");
    TCAP_Invoke *ivk = new TCAP_Invoke();
    ivk->SetClass(TCAP_OPERATION_CLASS);
    ivk->SetOperation( cap::OP_activityTest );
    cpt = ivk;
    UPDATE_SSG_STATS_ACT_TEST_SENT;
    //DLOG_DEBUG("TransatelCAPToRoHandler::BuildActivityTest Exit");
    return rc;
}

int TransatelCAPToRoHandler::BuildSuccessiveCCRInitial(IwfFsm *ctxt, DIA_BASE_CMD *&cmd, std::string& hostName, std::string& realmName)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = ITS_SUCCESS;

    //DLOG_DEBUG("BuildSuccessSiveCCRInitial -- Entry");

    Ro_TSL::CreditControlRequest *ccr = new Ro_TSL::CreditControlRequest();
    Ro_TSL::ServiceInformation si;
    TransCustomAvp::CSInformation csInfo;
    TransCustomAvp::CAPInformation capInfo;
    IDPToCCRIData ccriData;
    Ro_TSL::MultipleServicesCreditControl mscc;


    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    //Set Auth-Application-Id
    std::string appId = DIAMETER_RO_APPLICATION_ID;
    diameter::base::AuthApplicationId authApplicationId(atoi(DIAMETER_RO_APPLICATION_ID));
    ccr->setAuthApplicationId(authApplicationId);


    Ro_TSL::CCRequestType ccRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);
    ccr->setCCRequestType(ccRequestType);

    //Set Event-Timestamp
    ITS_UINT seconds = this->GetCurrentTimeStamp();
    diameter::base::EventTimestamp eventTimestamp(seconds);
    ccr->setEventTimestamp(eventTimestamp);

    if(userData)
    {
        userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::INITIAL_REQUEST);

        /*setting CCRequestNumber to 0 for CCR-I */
        int ccrnum = 0;
        Ro_TSL::CCRequestNumber ccRequestNumber(ccrnum++);
        ccr->setCCRequestNumber(ccRequestNumber);
        userData->SetCCRequestNumber(ccrnum);

        if(userData->IsBasicServiceReceived())
        {
            //NOTE: setting Service Identifier from User Context
            int serviden = userData->GetServiceIdentifier();
            mscc.addServiceIdentifier(Ro_TSL::ServiceIdentifier(serviden));
        }

        if(userData->HasServiceContextId())
        {
            Ro_TSL::ServiceContextId serviceContextId(Ro_TSL::ServiceContextId(userData->GetServiceContextId()));
            ccr->setServiceContextId(serviceContextId);
        }

        ccriData.CopyFrom(userData->GetIDPToCCRIData());
        RetrieveIDPToCCRIData(capInfo, ccriData);

        if(ccriData.has_subscriptionidinfo())
        {
            Ro_TSL::SubscriptionId subsId;

            if(ccriData.subscriptionidinfo().has_subidtype())
            {
                subsId.setSubscriptionIdType(Ro_TSL::SubscriptionIdType((Ro_TSL::SubscriptionIdType::Value)ccriData.subscriptionidinfo().subidtype()));
            }
            if(ccriData.subscriptionidinfo().has_subiddata())
            {
                subsId.setSubscriptionIdData(Ro_TSL::SubscriptionIdData(ccriData.subscriptionidinfo().subiddata()));
            }
            ccr->addSubscriptionId(subsId);
        }

        /*set the CAP-Is-Following-On explicitly to indicate its FOLLOW_ON */
        TransCustomAvp::CAPIsFollowingOn capFollowOn((TransCustomAvp::CAPIsFollowingOn::Value)true);
        capInfo.setCAPIsFollowingOn(capFollowOn);
        userData->SetIsFollowingOn(true);
        ccriData.set_capisfollowingon(true);
        userData->SetIDPToCCRIData(ccriData);

        pbERBData erbData;
        TransCustomAvp::CAPERBSInformation capErbInfo;
        erbData.CopyFrom(userData->GetERBData());
        RetrieveERBData(capErbInfo, erbData);
        capInfo.setCAPERBSInformation(capErbInfo);

        csInfo.setCAPInformation(capInfo);
        si.setCSInformation(csInfo);

    }

    //Set Multiple-Service-Indicator, Multiple_Servcie_Credit_Control - USU --CCTime
    Ro_TSL::MultipleServicesIndicator msi(Ro_TSL::MultipleServicesIndicator::Value::MULTIPLE_SERVICES_SUPPORTED);
    ccr->setMultipleServicesIndicator(msi);

    ccr->setServiceInformation(si);
    Ro_TSL::UsedServiceUnit usu;
    int defaultCCTimeVal = 0;
    usu.setCCTime(Ro_TSL::CCTime((diameter::Unsigned64)defaultCCTimeVal));
    mscc.addUsedServiceUnit(usu);
    ccr->addMultipleServicesCreditControl(mscc);

    SetDefaultAVPs(ctxt, ccr, ctxt->GetImsi().c_str());
    //SetDestinationHostAndRealm(ctxt, ctxt->GetImsi().c_str(), userData->GetIDPToCCRIData().service_key(), ccr, true);
    //DLOG_DEBUG("Set DestHost - %s and DestRealm - %s in successive CCR-I", hostName.c_str(), realmName.c_str());
    ccr->setDestinationHost(diameter::base::DestinationHost(hostName));
    ccr->setDestinationRealm(diameter::base::DestinationRealm(realmName));
    cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
    cmd->SetDictId(DIAMETER_RO_DICTIONARY_ID);

    m_dccaHandler.HandleRequest(userData->GetDccaContext(),
            cmd, Ro_TSL::CCRequestType::INITIAL_REQUEST);

    LogRoTslDiaMsg(*ccr, false);

    //DLOG_DEBUG("BuildSuccessiveCCRInitial -- exit");
    return retVal;

}

int TransatelCAPToRoHandler::LogCDRData(IwfFsm* ctxt, ITS_UINT failureCause)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    //DLOG_DEBUG("TransatelCAPToRoHandler::LogCDRRecord entry");

    //DLOG_DEBUG("LogCDRData : Logging CDR for [ %s ]", ctxt->GetDiaSessionId().c_str());

    this->GetCDRRecorder().Record(ctxt, failureCause);

    //DLOG_DEBUG("TransatelCAPToRoHandler::LogCDRRecord exit");

    return ITS_SUCCESS;
}

ITS_UINT TransatelCAPToRoHandler::GetCurrentTimeStamp()
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("GetCurrentTimeStamp:: Entry");
    ITS_UINT seconds;
    struct timeval tv = GetCurrentMonotonic();

    seconds = (tv.tv_sec + TIME_FROM_1900_TO_EPOCH );
    //DLOG_DEBUG("Current TimeStamp %u", seconds);
    //DLOG_INFO("GetCurrentTimeStamp :: Exit");
    return seconds;
}

int TransatelCAPToRoHandler::TerminateSession(IwfFsm *ctxt,
        TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    ITS_UINT ret = ITS_SUCCESS;
    ITS_OCTET invkId = 0;
    bool isTerminateAlreadySent = false;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    //DLOG_DEBUG("TransatelCAPToRoHandler::TerminateSession entry");
    if( userData->IsIDPReceived() )
    {
        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if( inTcapDlg != NULL )
        {
            //Added TC_L_Reject check, to avoid IWF initiate a ReleaseCall, since TC_R_Reject would already be sent.
            if((inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_BEGIN)
                    &&  !userData->IsCapReleaseSent()
                    && !(TCPPT_TC_L_REJECT == ctxt->GetCurrRcvdTcapCpt()->GetComponentType()))
            {

                BuildRelease(ctxt, NULL, outCpt, userData->GetReleaseCause());
                if ( outCpt != NULL )
                {
                    UPDATE_SSG_STATS_REL_ARG_SENT;
                    invkId = ctxt->GetInvkId();
                    outCpt->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    userData->SetCapReleaseSent(true);
                }
            }
            /*else
            {

                DLOG_DEBUG("Release already sent or Received TCAP Dialogue is not Continue");
            }*/
        }

        if (!userData->GetDccaContext().IsDone())
        {
            //DLOG_DEBUG("Build CCR-Terminate for Timeout/PeerDown/ASR case");
            if ( userData->GetTerminationCause() == 0 )
            {
                if(ctxt->GetErrorCode() == IWF_EBASE_MAND_AVP_MISSING)
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_BAD_ANSWER");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_BAD_ANSWER);
                }
                else if(userData->IsASRReceived())
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_ADMINISTRATIVE");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE);
                }
                else if(ctxt->GetErrorCode() == IWF_APP_TX_TIMEOUT)
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_SESSION_TIMEOUT");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_SESSION_TIMEOUT);
                }
                else
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_ADMINISTRATIVE");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE);
                }
            }
            /* only in AT timeout case,
             * if USUCCTime should set to time elapsed after ERB(Answer) is received.*/
            pbActivityTimerData activityTest = userData->GetActivityTimerData();

            if(0 == activityTest.retrycount())
            {
                uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
                if(m_config.GetIncludeTimeoutInCCTimeConfig() || totalUsedSeconds == 0)
                {
                    userData->SetUSUCCTime(totalUsedSeconds);
                }
                else
                {
                    userData->SetUSUCCTime((totalUsedSeconds -
                                ((m_config.ActivityTimer()).responseTimeout * (m_config.ActivityTimer()).retryCount)));
                }
            }
            //DLOG_DEBUG("SendATTimeoutInCCTime : %s, USUCCTime set to : %u, ",m_config.GetIncludeTimeoutInCCTimeConfig()?"true":"false", userData->GetUSUCCTime());
            if((userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST) ||
                    (ctxt->IsSessionAcrossSwitchover() && ctxt->GetErrorCode() == IWF_APP_TX_TIMEOUT))
            {
                if(userData->IsASRReceived())
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_ADMINISTRATIVE");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE);
                }
                BuildCCRTerminateForIDP(ctxt, ((diameter::base::TerminationCause::Value)
                            userData->GetTerminationCause()), outDiaCmd, userData->GetUSUCCTime());
            }
            else
            {
                isTerminateAlreadySent = true;
                //DLOG_DEBUG("CCR-T already sent. Consume it");
            }
        }
        else
        {
            isTerminateAlreadySent = true;
            //DLOG_DEBUG("CCR-T already sent. Terminating");
        }
    }
    else if ( userData->IsIDPSMSReceived() )
    {
        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if( inTcapDlg != NULL )
        {
            if((inTcapDlg->GetDialogueType() == TCPPT_TC_CONTINUE || inTcapDlg->GetDialogueType() == TCPPT_TC_BEGIN)
                    &&  !userData->IsCapReleaseSent()
                    && !(TCPPT_TC_L_REJECT == ctxt->GetCurrRcvdTcapCpt()->GetComponentType()))
            {
                //DLOG_DEBUG("Building ReleaseSMS for timeout");
                BuildReleaseSMS(ctxt, NULL, outCpt, userData->GetReleaseCause());
                if ( outCpt != NULL )
                {
                    invkId = ctxt->GetInvkId();
                    outCpt->SetInvokeID(++invkId);
                    ctxt->SetInvkId(invkId);
                    UPDATE_SSG_STATS_RELSMS_ARG_SENT;
                    userData->SetCapReleaseSent(true);
                }
            }
            /*else
            {
                DLOG_DEBUG("Release already sent or Received TCAP Dialogue is not Continue");
            }*/

        }

        if (!userData->GetDccaContext().IsDone())
        {
            //DLOG_DEBUG("Build CCR-Terminate for Timeout/Peer Down/ASR case");
            if ( userData->GetTerminationCause() == 0 )
            {
                if(userData->IsASRReceived())
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_ADMINISTRATIVE");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE);
                }
                else
                {
                    //DLOG_DEBUG("set TerminationCause as DIAMETER_SESSION_TIMEOUT");
                    userData->SetTerminationCause(diameter::base::TerminationCause::DIAMETER_SESSION_TIMEOUT);
                }
            }
            if((userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST) ||
                    (ctxt->IsSessionAcrossSwitchover() && ctxt->GetErrorCode() == IWF_APP_TX_TIMEOUT))
            {
                if (userData->GetTerminationCause() == diameter::base::TerminationCause::DIAMETER_ADMINISTRATIVE)
                {
                    BuildCCRTerminateForIDPSMS(ctxt,(diameter::base::TerminationCause::
                                DIAMETER_ADMINISTRATIVE), outDiaCmd);
                }
                else if(userData->GetTerminationCause() == diameter::base::TerminationCause::DIAMETER_LOGOUT)
                {
                    BuildCCRTerminateForIDPSMS(ctxt,(diameter::base::TerminationCause::DIAMETER_LOGOUT),outDiaCmd);
                }
                else
                {
                    BuildCCRTerminateForIDPSMS(ctxt,(diameter::base::TerminationCause::
                                DIAMETER_SESSION_TIMEOUT), outDiaCmd);
                }
            }
            else
            {
                isTerminateAlreadySent = true;
                //DLOG_DEBUG("CCR-T already sent. Consume it");
            }
        }
        else
        {
            isTerminateAlreadySent = true;
            //DLOG_DEBUG("CCR-Terminate sent already. Terminating");
        }
    }
    else
    {
        //DLOG_DEBUG("No Handling for this case");
        ret = !ITS_SUCCESS;
    }

    if(isTerminateAlreadySent)
    {
        if(ctxt->GetCurrRcvdDiaMsg() != NULL)
        {
            DIA_BASE_CMD *bcmd = ctxt->GetCurrRcvdDiaMsg();
            diameter::Command* cmd = (const_cast<DIA_BASE_CMD*>(bcmd))->GetBaseGenCommand();
            Ro_TSL::CreditControlAnswer cca(cmd->getImpl());
            unsigned int ccReqType = cca.getCCRequestType().value();
            if ( userData->GetLastSentCCRequestType() == ccReqType )
            {
                if ( cca.getCCRequestType().value() == Ro_TSL::CCRequestType::TERMINATION_REQUEST )
                {
                    userData->SetCurrentCCATResultCode(cca.getResultCode().value());
                    if( m_config.GetCdrConfig() != DISABLE_ALL_CALLS )
                    {
                        if(!userData->IsFailedCDRLogged())
                        {
                            LogCDRData(ctxt);
                            userData->SetFailedCDRLogged(true);
                        }
                    }
                }
            }
        }
        std::string& rlsStr = ctxt->GetDiaSessionId();
        TransactionManager::Instance()->DeleteFirstSessionEntryFromReplica(rlsStr, ctxt);
        DiaFrame::GetDiaFrame()->ReleaseSession(rlsStr.c_str());
        ctxt->SetCurrentState(CLOSED);
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::TerminateSession exit ");
    return ret;
}

int TransatelCAPToRoHandler::HandleBuildReleaseConditions(IwfFsm* ctxt,Ro_TSL::CreditControlAnswer& cca)
{
    //DLOG_INFO("HandleBuildReleaseConditions:: Entry");
    int rc = ITS_SUCCESS;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if( userData->GetCurrentCCAIResultCode() != ITS_DIA_SUCCESS ||
            (GetMSCCResultCode(&cca) != ITS_DIA_SUCCESS) ||
            (CheckMSCCGrantedServiceUnitCCTime(&cca,userData) != ITS_SUCCESS) ||
            userData->GetSCPAction() == TransCustomAvp::SCPAction::REJECT ||
            ITS_ETIMEOUT == ctxt->GetErrorCode() ||
            TSLConstants::INVALID_CONTROL_MODE_CAPV1 == ctxt->GetErrorCode() ||
            ITS_EASNENCODE == ctxt->GetErrorCode() || userData->GetSCPAction() == 0 ||
            TSLConstants::INVALID_CONTROL_MODE == userData->GetCAPControlMode())
    {
        rc = !ITS_SUCCESS;
    }

    //DLOG_INFO("HandleBuildReleaseConditions:: Exit");
    return rc;
}
/*Func description : It validates the BCSM_Event recv in ERB msg.
  Verifys for Events armed in RRB msg for MO or MT call corresspondingly other than O-TAnswer.
  Return value         : CONTINUE_CALL_RET if first ERB recv is O-TAnswer or O-TDisconnect is recv
  AppropriateRetActionValue if any of the armed events in RRB msg is recv
  In MO_Voice case if
  -oCalledPartyBusy/oNoAnswer/routeSelectFailure recv on 02 legId
  -first ERB oDiscon is recv on legId 01 in callFlow.
  In MT_Voice case if
  -tBusy/tNoAnswer recv on legId 02 and tAbandon is recv on 01 legId
  - first ERB tDiscon is recv on legId 01 in callFlow.

*/
int TransatelCAPToRoHandler::ValidateRecvERBEvent(cap_v2::EventReportBCSMArg& erbV2,
        IwfFsm* ctxt,
        DIA_BASE_CMD *&cmd)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("ValidateRecvERBEvent:: Entry");
    int ret = TSLConstants::CONTINUE_CALL_RET;
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    cap_v2::EventTypeBCSM eventBcsm = erbV2.GetEventTypeBCSM();
    pbERBData erbData;
    int RecvLegId = ExtractLegIdFromErb(erbV2);
    uint32_t totalTimeInSec = 0;

    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    ITS_USHORT tcapDlgType = inTcapDlg->GetDialogueType();

    /*DLOG_INFO("ValidateRecvERBEvent:: Recv ERB with EventTypeBCSM : %s, LegId : %d, SCPAction :%d.",
            GetStrBCSMEventType(eventBcsm).c_str(),RecvLegId,userData->GetSCPAction());*/

    /*Stop the NO_EVENT_TIMER  on recv of first ERB msg*/
    if(!userData->IsFirstERBrcvd())
    {
        ETimerType timerType = ETimerType::NO_EVENT_TIMER;
        STimerInfo fsmTimerData;
        ctxt->GetTimerInfo(timerType, fsmTimerData);
        IwfTimer timerObj;
        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
        {
            //DLOG_DEBUG("ValidateRecvERBEvent:: TimerType : NO_EVENT_TIMER, TimerId : %ul stopped.",fsmTimerData.m_uiTimerId);
            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
        }
        /*else
        {
            DLOG_ERROR("ValidateRecvERBEvent:: Failed to stop TimerType : NO_EVENT_TIMER, TimerId : %ul.",fsmTimerData.m_uiTimerId);
        }*/
    }
    /*Case : First ERB recv is O-TDiscon in TC_END, should send only CCR-T */

    /* if(!userData->IsFirstERBrcvd() &&
       (eventBcsm.IsODisconnect() || eventBcsm.IsTDisconnect()))
       {

       if(TCPPT_TC_END == tcapDlgType)
       {
       DLOG_DEBUG("ValidateRecvERBEvent:: Recieved first ERB(%s) in TC_End.",
       GetStrBCSMEventType(eventBcsm).c_str());
       ret = IWF_RA_FORWARD;
       if(userData)
       {
       userData->SetCurrentReceivedTcapContinue(false);
       }

       }
       else if(TCPPT_TC_CONTINUE == tcapDlgType)
       {
       DLOG_DEBUG("ValidateRecvERBEvent:: Recieved first ERB(%s) in TC_Continue.",
       GetStrBCSMEventType(eventBcsm).c_str());
       ret = IWF_RA_RESPOND_AND_FORWARD;
       if(userData)
       {
       userData->SetCurrentReceivedTcapContinue(true);
       }

       }
       userData->SetFirstERBReceived(true);


       }*/

    /* Case when ACR time-out or last quota timeout had occurred & after cleanup has been done
     * ERB(O-TDiscon) is recv*/
    if(userData->IsCapReleaseSent())
    {
        /*DLOG_DEBUG("ValidateRecvERBEvent:: Recv ERB(%s) after sending ReleaseCall, consume the message.",
                GetStrBCSMEventType(eventBcsm).c_str());*/
        return(IWF_RA_CONSUME);
    }


    if((MO_VOICE == userData->GetCallType() ||
                MT_VOICE == userData->GetCallType())
            &&
            (!userData->IsFirstERBrcvd()))
    {
        userData->SetFirstERBReceived(true);

        if(true == eventBcsm.IsOCalledPartyBusy() ||
                true == eventBcsm.IsTBusy())
        {
            //Extract EventSpecInfo & update in RoTransCtxt
            if(erbV2.OptionEventSpecificInformationBCSM())
            {
                if(erbV2.GetEventSpecificInformationBCSM().ChoiceOCalledPartyBusySpecificInfo())
                {
                    if(erbV2.GetEventSpecificInformationBCSM().GetChoiceOCalledPartyBusySpecificInfo().OptionBusyCause())
                    {
                        const std::vector<byte>& vec = erbV2.GetEventSpecificInformationBCSM().GetChoiceOCalledPartyBusySpecificInfo().GetBusyCause().GetArray();
                        string evtSpecInfo;
                        IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);

                        uint8_t remId[NYBBLE_SIZE-2] = {0};
                        int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                        string hexString((const char*)remId,len);

                        erbData.set_eventspecinfo(hexString);
                        userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                        //DLOG_INFO("CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                    }
                }
                if(erbV2.GetEventSpecificInformationBCSM().ChoiceTBusySpecificInfo())
                {
                    if(erbV2.GetEventSpecificInformationBCSM().GetChoiceTBusySpecificInfo().OptionBusyCause())
                    {
                        const std::vector<byte>& vec = erbV2.GetEventSpecificInformationBCSM().GetChoiceTBusySpecificInfo().GetBusyCause().GetArray();
                        string evtSpecInfo;
                        IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);


                        uint8_t remId[NYBBLE_SIZE-2] = {0};
                        int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                        string hexString((const char*)remId,len);
                        erbData.set_eventspecinfo(hexString);
                        userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                        //DLOG_INFO("CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                    }
                }

            }
        }
        if(true == eventBcsm.IsONoAnswer()||
                true == eventBcsm.IsTNoAnswer())
        {
            //EventSpecInfo is Not set in this case.
            //erbData.set_eventspecinfo("");
            std::string erbEvntSpecificInfo("");
            userData->SetErbSpecificInfoForCDR(erbEvntSpecificInfo);
        }
        if(true == eventBcsm.IsRouteSelectFailure())
        {
            //Extract EventSpecInfo & update in RoTransCtxt
            if(erbV2.OptionEventSpecificInformationBCSM())
            {
                if(erbV2.GetEventSpecificInformationBCSM().ChoiceRouteSelectFailureSpecificInfo())
                {
                    if(erbV2.GetEventSpecificInformationBCSM().GetChoiceRouteSelectFailureSpecificInfo().OptionFailureCause())
                    {
                        const std::vector<byte>& vec = erbV2.GetEventSpecificInformationBCSM().GetChoiceRouteSelectFailureSpecificInfo().GetFailureCause().GetArray();
                        string evtSpecInfo;
                        IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);
                        uint8_t remId[NYBBLE_SIZE-2] = {0};
                        int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                        string hexString((const char*)remId,len);
                        erbData.set_eventspecinfo(hexString);
                        userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                        //DLOG_INFO("CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                    }
                }
            }
        }
        if(true == eventBcsm.IsTAbandon())
        {
            //EventSpecInfo is not applicable in case of TAbandon
            //erbData.set_eventspecinfo("");
            std::string erbEvntSpecificInfo("");
            userData->SetErbSpecificInfoForCDR(erbEvntSpecificInfo);
        }

        //Extract EventSpecInfo & update in RoTransCtxt
        string sDisconSpecInfo("");
        FetchDisconEvtSpecInfo(erbV2,sDisconSpecInfo,ctxt);
        if(!sDisconSpecInfo.empty())
        {
            erbData.set_eventspecinfo(sDisconSpecInfo);
        }
        if (TCPPT_TC_CONTINUE == tcapDlgType)
        {
            if(userData)
            {
                userData->SetCurrentReceivedTcapContinue(true);
            }
            /*DLOG_DEBUG("ValidateRecvERBEvent:: Recieved first ERB(%s) in TC_Continue.",
                    GetStrBCSMEventType(eventBcsm).c_str());*/
            ret = IWF_RA_RESPOND_AND_FORWARD;
        }
        else if(TCPPT_TC_END == tcapDlgType)
        {
            if(userData)
            {
                userData->SetCurrentReceivedTcapContinue(false);
            }
            /*DLOG_DEBUG("ValidateRecvERBEvent:: Recieved first ERB(%s) in TC_End.",
                    GetStrBCSMEventType(eventBcsm).c_str());*/
            ret = IWF_RA_FORWARD;
        }

        /* In case of O-TAnswer event continue with further call processing*/
        if(true == eventBcsm.IsOAnswer() ||
                true == eventBcsm.IsTAnswer())
        {
            ret = TSLConstants::CONTINUE_CALL_RET;
        }

        /*Case : ERB(Busy/NoAnswer/Abandon/Discon) recv in Follow-On or Transparent-Follow-on cases in TC_CONTINUE
         * set flag to true and continue to establish second call*/

        if((IWF_RA_RESPOND_AND_FORWARD == ret) &&
                (TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON ==  userData->GetSCPAction() ||
                 TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ==  userData->GetSCPAction() ||
                 TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT ==  userData->GetSCPAction()))
        {
            if(TSLConstants::CalledLegID == ExtractLegIdFromErb(erbV2))
            {
                userData->SetContinueCall(true);
                ret = TSLConstants::CONTINUE_CALL_RET;
            }
        }
    }
    else if(userData->IsFirstERBrcvd())
    {

        if(true == erbV2.GetEventTypeBCSM().IsODisconnect()||
                true == erbV2.GetEventTypeBCSM().IsTDisconnect())
        {
            totalTimeInSec = RetrieveTotalCallTimeDuration(ctxt);
            if(TSLConstants::CallingLegID == ExtractLegIdFromErb(erbV2))
            {
                string sDisconSpecInfo("");
                FetchDisconEvtSpecInfo(erbV2,sDisconSpecInfo,ctxt);
                if(!sDisconSpecInfo.empty())
                {
                    erbData.set_eventspecinfo(sDisconSpecInfo);
                }
                if (TCPPT_TC_CONTINUE == tcapDlgType)
                {
                    if(userData)
                    {
                        userData->SetCurrentReceivedTcapContinue(true);
                    }
                    /*DLOG_DEBUG("ValidateRecvERBVEvent:: Recieved second ERB(%ld) in TC_Continue.",
                            eventBcsm.GetValue());*/
                    ret = IWF_RA_RESPOND_AND_FORWARD;
                }
                else if(TCPPT_TC_END == tcapDlgType)
                {
                    if(userData)
                    {
                        userData->SetCurrentReceivedTcapContinue(false);
                    }
                    /*DLOG_DEBUG("ValidateRecvERBVEvent:: Recieved second ERB(%ld) in TC_End.",
                            eventBcsm.GetValue());*/
                    ret = IWF_RA_FORWARD;
                }
            }
            else if(TSLConstants::CalledLegID == ExtractLegIdFromErb(erbV2) &&
                    TCPPT_TC_END == tcapDlgType)
            {
                string sDisconSpecInfo("");
                FetchDisconEvtSpecInfo(erbV2,sDisconSpecInfo,ctxt);
                if(!sDisconSpecInfo.empty())
                    erbData.set_eventspecinfo(sDisconSpecInfo);
                /*DLOG_DEBUG("ValidateRecvERBVEvent:: Received second ERB(%ld) in TC_End.",
                        eventBcsm.GetValue());*/
                /* Continue the call as in CheckBCSMEventAndDialogueType we validate call conditions */
            }

        }
    }

    /*Extract ERB_Data & populate in RoTransContext */
    erbData.set_erbrecvevttype((unsigned int)erbV2.GetEventTypeBCSM().GetValue());

    /* LegID->ReceivingSideID is mapped to CAP-ERB-LegID */
    if (erbV2.OptionLegID())
    {
        if ( erbV2.GetLegID().ChoiceReceivingSideID() )
        {
            const std::vector<byte>& vec = erbV2.GetLegID().GetChoiceReceivingSideID().GetArray();
            uint32_t lt = uint32_t (vec[0]);
            erbData.set_recvlegid(lt);
        }
    }

    /*miscCallInfo->MessageType is mapped to CAP-ERB-MessageType */
    erbData.set_msgtype((unsigned int) erbV2.GetMiscCallInfo().GetMessageType().GetValue());
    userData->SetERBData(erbData);


    if(IWF_RA_RESPOND_AND_FORWARD == ret ||
            IWF_RA_FORWARD == ret
      )
    {
        if(userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST)
        {
            userData->SetUSUCCTime(totalTimeInSec);
            BuildCCRTerminateForIDP(ctxt,(diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
        }
        else
        {
            //DLOG_DEBUG("CCR-T already sent, so consume current recv ERB.");
            ret = IWF_RA_CONSUME;
        }
    }
    //DLOG_INFO("ValidateRecvERBEvent:: Exit");
    return ret;
}

int TransatelCAPToRoHandler::OnUpstrmFinalReqSent(IwfFsm *ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("OnUpstrmFinalReqSent :: Entry");
    int retVal = ITS_SUCCESS;

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(userData)
    {
        if(ctxt->IsFinalUpstrmReqSent())
        {
            //DLOG_DEBUG("IsFinalUpstrmReqSent is TRUE");
            userData->SetLastSentCCRequestType(Ro_TSL::CCRequestType::TERMINATION_REQUEST);
            ctxt->SetFinalUpstrmReqSent(false);
        }
    }
    //DLOG_INFO("OnUpstrmFinalReqSent :: Exit");
    return retVal;
}

ITS_UINT TransatelCAPToRoHandler::SetFeaturesConfig(IwfFeatureConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransatelCAPToRoHandler::SetFeaturesConfig Entry");
    ITS_UINT retVal = CMAPI_SUCCESS;

    if( req->has_featurename() && req->has_statusvalue() )
    {
        if( req->featurename() == CDR )
        {
            m_config.SetCdrConfig(req->statusvalue());
            DLOG_DEBUG("Setting the CDR configuration to %d",req->statusvalue());
        }
        else if( req->featurename() == TANS_TRIGGER )
        {
            if(req->statusvalue())
                m_config.SetFollowOnTAnsTrigger(true);
            else
                m_config.SetFollowOnTAnsTrigger(false);
            DLOG_DEBUG("Setting the FollowOnTAnsTrigger to %d",req->statusvalue());
        }
    }
    else
    {
        DLOG_ERROR("Invalid Feature configuration");
        retVal = !ITS_SUCCESS;
    }
    return retVal;
}

ITS_UINT TransatelCAPToRoHandler::GetCDRConfig()
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("Retrieved CDR config : %d",m_config.GetCdrConfig());
    return m_config.GetCdrConfig();
}

ITS_UINT TransatelCAPToRoHandler::GetCDRFailureCause(IwfFsm *iwfFsm)
{
    ITS_UINT failureCause;
    bool isDccaEnabled = false;
    TransatelCAPRoTransactionContext* capRoTsluserData =
        static_cast<TransatelCAPRoTransactionContext*>(iwfFsm->GetStoredUserData());
    if ( itsDiaConfig.GetDccaFeature() != NULL )
        isDccaEnabled = true;

    if (capRoTsluserData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::INITIAL_REQUEST)
    {
        if(isDccaEnabled)
            failureCause = TX_TIMEOUT_CCR_I;
        else
            failureCause = AUTH_TIMEOUT_CCR_I;
    }
    else if(capRoTsluserData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::UPDATE_REQUEST)
    {
        if(isDccaEnabled)
            failureCause = TX_TIMEOUT_CCR_U;
        else
            failureCause = AUTH_TIMEOUT_CCR_U;
    }
    else if(capRoTsluserData->GetLastSentCCRequestType() == Ro_TSL::CCRequestType::TERMINATION_REQUEST)
    {
        if(isDccaEnabled)
            failureCause = TX_TIMEOUT_CCR_T;
        else
            failureCause = AUTH_TIMEOUT_CCR_T;
    }
    return failureCause;
}
/*Func description : It validates the BCSM_Event recv in V1 ERB msg.
  Verifys for Events armed in RRB msg for MO or MT call corresspondingly other than O-TAnswer.
  Return value         : CONTINUE_CALL_RET if first ERB recv is O-TAnswer or O-TDisconnect is recv in TC_Cont on LegId=2
  AppropriateRetActionValue if any of the armed events in RRB msg is recv
  In MO_Voice case if
  -first ERB oDiscon is recv on legId 01 in callFlow.
  In MT_Voice case if
  - first ERB tDiscon is recv on legId 01 in callFlow.

*/
int TransatelCAPToRoHandler::ValidateRecvERBV1Event(cap_v1::EventReportBCSMArg& erbV1,
        IwfFsm* ctxt,
        DIA_BASE_CMD *&cmd)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("ValidateRecvERBV1Event:: Entry");
    int ret = TSLConstants::CONTINUE_CALL_RET;
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    cap_v1::EventTypeBCSM eventBcsm = erbV1.GetEventTypeBCSM();
    pbERBData erbData;
    int RecvLegId = ExtractLegIdFromErb(erbV1);

    uint32_t totalTimeInSec = 0;
    TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
    ITS_USHORT tcapDlgType = inTcapDlg->GetDialogueType();

    /*DLOG_INFO("ValidateRecvERBV1Event:: Recv ERB with EventTypeBCSM : %ld, LegId : %d, SCPAction :%d.",
            eventBcsm.GetValue(),RecvLegId,userData->GetSCPAction());*/

    /*Stop the NO_EVENT_TIMER  on recv of first ERB msg*/
    if(!userData->IsFirstERBrcvd())
    {
        ETimerType timerType = ETimerType::NO_EVENT_TIMER;
        STimerInfo fsmTimerData;
        ctxt->GetTimerInfo(timerType, fsmTimerData);
        IwfTimer timerObj;
        if(ITS_SUCCESS == timerObj.StopTimer(fsmTimerData.m_uiTimerId))
        {
            //DLOG_DEBUG("ValidateRecvERBV1Event:: TimerType : NO_EVENT_TIMER, TimerId : %u stopped.",fsmTimerData.m_uiTimerId);
            ctxt->RemoveTimerInfo(fsmTimerData.m_uiTimerId);
        }
        else
        {
            DLOG_ERROR("ValidateRecvERBV1Event:: Failed to stop TimerType : NO_EVENT_TIMER, TimerId : %u.",fsmTimerData.m_uiTimerId);
        }
    }

    /* Case when ACR time-out or last quota timeout had occurred & after cleanup has been done
     * ERB(O-TDiscon) is recv*/
    if(userData->IsCapReleaseSent())
    {
        /*DLOG_DEBUG("ValidateRecvERBV1Event:: Recv ERB(%ld) after sending ReleaseCall, consume the message.",
                eventBcsm.GetValue());*/
        return(IWF_RA_CONSUME);
    }


    if((MO_VOICE == userData->GetCallType() ||
                MT_VOICE == userData->GetCallType())
            &&
            (!userData->IsFirstERBrcvd()))
    {
        userData->SetFirstERBReceived(true);

        //Extract EventSpecInfo & update in RoTransCtxt

        string sDisconSpecInfo("");
        FetchDisconEvtSpecInfo(erbV1,sDisconSpecInfo,ctxt);
        if(!sDisconSpecInfo.empty())
        {
            erbData.set_eventspecinfo(sDisconSpecInfo);
        }

        if (TCPPT_TC_CONTINUE == tcapDlgType)
        {
            if(userData)
            {
                userData->SetCurrentReceivedTcapContinue(true);
            }
            /*DLOG_DEBUG("ValidateRecvERBV1Event:: Recieved first ERB(%ld) in TC_Continue.",
                    eventBcsm.GetValue());*/
            ret = IWF_RA_RESPOND_AND_FORWARD;
        }
        else if(TCPPT_TC_END == tcapDlgType)
        {
            if(userData)
            {
                userData->SetCurrentReceivedTcapContinue(false);
            }
            /*DLOG_DEBUG("ValidateRecvERBV1Event:: Recieved first ERB(%ld) in TC_End.",
                    eventBcsm.GetValue());*/
            ret = IWF_RA_FORWARD;
        }

        /* In case of O-TAnswer event continue with further call processing*/
        if(true == eventBcsm.IsOAnswer() ||
                true == eventBcsm.IsTAnswer())
        {
            ret = TSLConstants::CONTINUE_CALL_RET;
        }

        /*Case : ERB(Discon) recv in Follow-On or Transparent-Follow-on cases in TC_CONTINUE
         * set flag to true and continue to establish second call*/

        if((IWF_RA_RESPOND_AND_FORWARD == ret) &&
                (TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON ==  userData->GetSCPAction() ||
                 TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE ==  userData->GetSCPAction() ||
                 TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT ==  userData->GetSCPAction()))
        {
            if(TSLConstants::CalledLegID == ExtractLegIdFromErb(erbV1))
            {
                userData->SetContinueCall(true);
                ret = TSLConstants::CONTINUE_CALL_RET;
            }
        }
    }
    else if(userData->IsFirstERBrcvd())
    {

        if(true == erbV1.GetEventTypeBCSM().IsODisconnect()||
                true == erbV1.GetEventTypeBCSM().IsTDisconnect())
        {
            totalTimeInSec = RetrieveTotalCallTimeDuration(ctxt);
            if(TSLConstants::CallingLegID == ExtractLegIdFromErb(erbV1))
            {
                string sDisconSpecInfo("");
                FetchDisconEvtSpecInfo(erbV1,sDisconSpecInfo,ctxt);
                if(!sDisconSpecInfo.empty())
                {
                    erbData.set_eventspecinfo(sDisconSpecInfo);
                }
                if (TCPPT_TC_CONTINUE == tcapDlgType)
                {
                    if(userData)
                    {
                        userData->SetCurrentReceivedTcapContinue(true);
                    }
                    /*DLOG_DEBUG("ValidateRecvERBV1Event:: Recieved second ERB(%ld) in TC_Continue.",
                            eventBcsm.GetValue());*/
                    ret = IWF_RA_RESPOND_AND_FORWARD;
                }
                else if(TCPPT_TC_END == tcapDlgType)
                {
                    if(userData)
                    {
                        userData->SetCurrentReceivedTcapContinue(false);
                    }
                    /*DLOG_DEBUG("ValidateRecvERBV1Event:: Recieved second ERB(%ld) in TC_End.",
                            eventBcsm.GetValue());*/
                    ret = IWF_RA_FORWARD;
                }
            }
            else if(TSLConstants::CalledLegID == ExtractLegIdFromErb(erbV1) &&
                    TCPPT_TC_END == tcapDlgType)
            {
                string sDisconSpecInfo("");
                FetchDisconEvtSpecInfo(erbV1,sDisconSpecInfo,ctxt);
                if(!sDisconSpecInfo.empty())
                    erbData.set_eventspecinfo(sDisconSpecInfo);
                /*DLOG_DEBUG("ValidateRecvERBV1Event:: Received second ERB(%ld) in TC_End.",
                        eventBcsm.GetValue());*/
                /* Continue the call as in CheckBCSMEventAndDialogueType we validate call conditions */
            }
        }
    }

    /*Extract ERB_Data & populate in RoTransContext */
    erbData.set_erbrecvevttype((unsigned int)erbV1.GetEventTypeBCSM().GetValue());

    /* LegID->ReceivingSideID is mapped to CAP-ERB-LegID */
    if (erbV1.OptionLegID())
    {
        if ( erbV1.GetLegID().ChoiceReceivingSideID() )
        {
            const std::vector<byte>& vec = erbV1.GetLegID().GetChoiceReceivingSideID().GetArray();
            uint32_t lt = uint32_t (vec[0]);
            erbData.set_recvlegid(lt);
        }
    }

    /*miscCallInfo->MessageType is mapped to CAP-ERB-MessageType */
    erbData.set_msgtype((unsigned int) erbV1.GetMiscCallInfo().GetMessageType().GetValue());
    userData->SetERBData(erbData);


    if(IWF_RA_RESPOND_AND_FORWARD == ret ||
            IWF_RA_FORWARD == ret)
    {
        if(userData->GetLastSentCCRequestType() != Ro_TSL::CCRequestType::TERMINATION_REQUEST)
        {
            userData->SetUSUCCTime(totalTimeInSec);
            BuildCCRTerminateForIDP(ctxt,(diameter::base::TerminationCause::DIAMETER_LOGOUT), cmd, userData->GetUSUCCTime());
        }
        else
        {
            //DLOG_DEBUG("CCR-T already sent, so consume current recv ERB.");
            ret = IWF_RA_CONSUME;
        }
    }
    //DLOG_INFO("ValidateRecvERBV1Event:: Exit");
    return ret;
}

ITS_INT TransatelCAPToRoHandler::HandleError(IwfFsm* ctxt,
        DIA_BASE_CMD*& outCmd,
        TCAP_Component*& outCpt,
        IwfReturnAction& ret)
{
    // Handle only the error's Timeout and Unable-to-deliver Indication from
    // stack
    ITS_INT rc = ITS_SUCCESS;
    TransatelCAPRoTransactionContext* userData =
        static_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if(userData)
    {
        IwfDccaSessionCtxt::DccaState state = userData->GetDccaContext().GetState();

        int errCode = ctxt->GetErrorCode();
        /*CCFH action is not required in case of Auth_timeout,
         * Terminate the Session */
        if (errCode == IWF_EAUTH_SESSION_TIMEOUT ||
                errCode == IWF_EBASE_MAND_AVP_MISSING)
        {
            ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
            if (state == IwfDccaSessionCtxt::DccaPendingT)
            {
                // Set to not retry the CCR-T again during AuthSession timeout &
                // Base Mandatory avp missing
                userData->GetDccaContext().SetIsDone(true);
            }
            uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
            userData->SetUSUCCTime(totalUsedSeconds);
            return rc;
        }
        if (errCode != ITS_ETIMEOUT && errCode != ITS_DIA_UNABLE_TO_DELIVER)
        {
            //DLOG_DEBUG("Fsm errCode : %d, for dlg Id : %u, setting RetAction : IWF_RA_RESPOND_ONLY.",errCode,ctxt->GetTcapDlgId());
            uint32_t totalUsedSeconds = RetrieveTotalCallTimeDuration(ctxt);
            userData->SetUSUCCTime(totalUsedSeconds);
            ret.action = IWF_RA_RESPOND_ONLY;
            return rc;
        }
        std::string& sessId = ctxt->GetDiaSessionId();

        /*DLOG_DEBUG("Translator Error handler - %s <%s>",
                (errCode == ITS_ETIMEOUT ? "Tx Timeout" : "Peer Down"),
                sessId.c_str());*/

        IwfDcca::FailureAction action;
        ctxt->SetFlowFailure(true);
        action = m_dccaHandler.HandleFailure(userData->GetDccaContext(), outCmd);
        if (action == IwfDcca::FA_Retry)
        {
            /*DLOG_DEBUG("FailureHandling: Retry <%s>",
                    outCmd->getSessionId()->value().c_str());*/
            ret.action = IWF_RA_CONSUME_AND_RETRY;
            //Setting the Failedover reason to be logged in CDR
            if (errCode == ITS_ETIMEOUT)
            {
                userData->SetCcfhFailedoverReason(CDR_TX_TIMEOUT);
                //DLOG_DEBUG("Setting Failedover Reason to CDR_TX_TIMEOUT");
            }
            if (errCode == ITS_DIA_UNABLE_TO_DELIVER)
            {
                userData->SetCcfhFailedoverReason(CDR_PEER_DOWN);
                //DLOG_DEBUG("Setting Failedover Reason to CDR_PEER_DOWN");
            }

            return rc;
        }

        // Action may be Terminate and continue. Continue not handled
        ret.action = IWF_RA_RESPOND_AND_FORWARD_WITH_TERM;
        if( m_config.GetCdrConfig() != DISABLE_ALL_CALLS )
        {
            CdrFailureCode failureCause = CDR_CODE_PEER_DOWN;
            if (errCode == ITS_ETIMEOUT)
            {
                failureCause = (CdrFailureCode)GetCDRFailureCause(ctxt);
            }
            if(!userData->IsFailedCDRLogged())
            {
                LogCDRData(ctxt, failureCause);
                userData->SetFailedCDRLogged(true);
            }
        }

        if (state == IwfDccaSessionCtxt::DccaPendingT)
        {
            // Set to not retry the CCR-T again during Tx timeout
            userData->GetDccaContext().SetIsDone(true);
            ret.action = IWF_RA_CONSUME;
            //DLOG_DEBUG("No need to retry CCRT, consume the message");
        }

        //DLOG_DEBUG("FailureHandling: Terminate %s", sessId.c_str());
    }
    return rc;
}

    template<class T1>
void TransatelCAPToRoHandler::FetchDisconEvtSpecInfo(T1& erb, string& strEventSpecInfo, IwfFsm* ctxt)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_INFO("FetchDisconEvtSpecInfo:: Entry");

    TransatelCAPRoTransactionContext* userData =
        static_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    if(true == erb.GetEventTypeBCSM().IsODisconnect()||
            true == erb.GetEventTypeBCSM().IsTDisconnect())
    {
        //Extract EventSpecInfo & populate out parameter
        if(erb.OptionEventSpecificInformationBCSM())
        {
            if(erb.GetEventSpecificInformationBCSM().ChoiceODisconnectSpecificInfo())
            {
                if(erb.GetEventSpecificInformationBCSM().GetChoiceODisconnectSpecificInfo().OptionReleaseCause())
                {
                    const std::vector<byte>& vec = erb.GetEventSpecificInformationBCSM().GetChoiceODisconnectSpecificInfo().GetReleaseCause().GetArray();
                    string evtSpecInfo;
                    IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);
                    uint8_t remId[NYBBLE_SIZE-2] = {0};
                    int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                    string hexString((const char*)remId,len);
                    strEventSpecInfo = hexString;
                    userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                    //DLOG_INFO("FetchDisconEvtSpecInfo::CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                }
            }
            if(erb.GetEventSpecificInformationBCSM().ChoiceTDisconnectSpecificInfo())
            {
                if(erb.GetEventSpecificInformationBCSM().GetChoiceTDisconnectSpecificInfo().OptionReleaseCause())
                {
                    const std::vector<byte>& vec = erb.GetEventSpecificInformationBCSM().GetChoiceTDisconnectSpecificInfo().GetReleaseCause().GetArray();
                    string evtSpecInfo;
                    IWFUtils::TBCDToString(&vec[0], vec.size(), evtSpecInfo,false, true);
                    uint8_t remId[NYBBLE_SIZE-2] = {0};
                    int len = IWFUtils::StringToTBCD(evtSpecInfo, remId,strlen(evtSpecInfo.c_str()), 0, true);
                    string hexString((const char*)remId,len);
                    strEventSpecInfo = hexString;
                    userData->SetErbSpecificInfoForCDR(evtSpecInfo);
                    //DLOG_INFO("FetchDisconEvtSpecInfo::CAPERBEventSpecificInformation : %s",evtSpecInfo.c_str());

                }
            }

        }
    }
    //DLOG_INFO("FetchDisconEvtSpecInfo:: Exit");

}

void TransatelCAPToRoHandler::ReleaseInvokeId(IwfFsm* ctxt, const ITS_OCTET invokeId, bool isOutGoing)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::ReleaseInvokeId Entry");

    if(ctxt != NULL)
    {
        TCAP_Dialogue *inTcapDlg = ctxt->GetCurrRcvdTcapDlg();
        if(inTcapDlg && (inTcapDlg->GetDialogueType() != TCPPT_TC_END) && 
                    (inTcapDlg->GetDialogueType() != TCPPT_TC_P_ABORT) &&
                    (inTcapDlg->GetDialogueType() != TCPPT_TC_U_ABORT))
        {
            TCAP_INVOKE_ENTRY *cptCtxt = NULL;
            CPT_INV_ID  invoke_id;
            invoke_id.len = INVOKEID_LEN;
            invoke_id.data[0] = TCPPN_INVOKE_TAG;
            invoke_id.data[1] = 1;
            invoke_id.data[2] = invokeId;

            /* Finding the InvokeContext */
            if(isOutGoing)
            {
                cptCtxt = TCAP_FindInvokeContext_CCITT(ctxt->GetTcapDlgId(), &invoke_id, INV_OUTGOING);
            }
            else
            {
                cptCtxt = TCAP_FindInvokeContext_CCITT(ctxt->GetTcapDlgId(), &invoke_id, INV_INCOMING);
            }

            if(cptCtxt != NULL)
            {
                //DLOG_DEBUG("Freeing the Invoke Context for did : %d and invokeId : %d", ctxt->GetTcapDlgId(), invokeId);
                /* FreeInvokeContext */
                TCAP_FreeInvokeContext_CCITT(cptCtxt);
            }
            /*else
            {
                //InvokeContext not Found
                DLOG_WARNING("Invoke Context Not Found for did : %d and invokeId : %d", ctxt->GetTcapDlgId(), invokeId);
            }*/
        }
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::ReleaseInvokeId Exit");
}

void TransatelCAPToRoHandler::ReleaseStoredInvokeIds(IwfFsm* ctxt)
{
    /*ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransatelCAPToRoHandler::ReleaseStoredInvokeIds Entry");*/

    vector<ITS_OCTET> ivkIds = ctxt->GetStoredOutGoingInvokeIdList();

    /* loop through the invokeIds and remove it */
    for(unsigned int i = 0; i < ivkIds.size(); i++)
    {
        ReleaseInvokeId(ctxt, ivkIds[i], true);
    }

    ctxt->ResetInvokeIdVector();

    //DLOG_DEBUG("TransatelCAPToRoHandler::ReleaseStoredInvokeIds Exit");
}

void TransatelCAPToRoHandler::ResetInitialSessionContext(IwfFsm* ctxt)
{
    /*ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransatelCAPToRoHandler::ResetInitialSessionContext Entry");*/

    TransatelCAPRoTransactionContext* userData =
        static_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    const unsigned int reset_value = 0;
    userData->SetCallAnsTimeStamp(reset_value);
    std::string erbEvntSpecificInfo("");
    userData->SetErbSpecificInfoForCDR(erbEvntSpecificInfo);
    userData->SetErbAnswerTimeStamp(reset_value);
    userData->SetFailedCDRLogged(false);
    userData->ClearDisconTriggerTimeStamp();
    userData->SetCurrentCCAUResultCode(0);
    userData->SetCurrentCCATResultCode(0);
    userData->SetTerminationCause(0);
    userData->SetLastSentCCRequestType(0);
    userData->SetCumulativeGSUCCTime(0);
    userData->SetUSUCCTime(0);
    ctxt->MarkFsmForDeletion(false);
    /*DLOG_DEBUG("Reset CallAnsTimeStamp : %u, ERB_AnswerTimeStamp : %u",
            userData->GetCallAnsTimeStamp(),
            userData->ErbAnswerTimeStamp());*/

    
    pbERBData erbData = userData->GetERBData();

    /*DLOG_DEBUG("Reset ReceivedEvtType : %u, eventSpecificInfo : %s, ReceivedLegId : %u, msgType : %u",
            erbData.erbrecvevttype(),
            erbData.eventspecinfo().c_str(),
            erbData.recvlegid(),
            erbData.msgtype());*/

    switch(userData->GetSCPAction())
    {
        case TransCustomAvp::SCPAction::TRANSPARENT_FOLLOW_ON :
            {
                /* Reseting the ERB Data */
                userData->ClearERBData();
                userData->SetFirstERBReceived(false);
                /*DLOG_DEBUG("Reset ReceivedEvtType : %u, eventSpecificInfo : %s, ReceivedLegId : %u, msgType : %u",
                        erbData.erbrecvevttype(),
                        erbData.eventspecinfo().c_str(),
                        erbData.recvlegid(),
                        erbData.msgtype());*/
                break;
            }
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONNECT :
        case TransCustomAvp::SCPAction::FOLLOW_ON_CONTINUE :
            {
                userData->SetUSUCCTime(reset_value);
                userData->SetGSUCCTime(reset_value);
                userData->ResetCumulativeGSUCCTime();
                userData->SetCcfhFailedoverReason(SUCCESS_CALL);
                ctxt->SetSessionAcrossSwitchover(false);
                /*DLOG_DEBUG("Reset USU_CCTime : %u, GSU_CCTime : %u, Cumulative GSU_CCTime : %u",
                        userData->GetUSUCCTime(),
                        userData->GetGSUCCTime(),
                        userData->GetCumulativeGSUCCTime());*/
                break;
            }
        default :
            {
                DLOG_WARNING("Unknown SCP-Action received : %d", userData->GetSCPAction());
            }
    }


    //DLOG_DEBUG("TransatelCAPToRoHandler::ResetInitialSessionContext Exit");
}

void TransatelCAPToRoHandler::CheckAndLogCDR(IwfFsm *ctxt)
{
    if( GetCDRConfig() != DISABLE_ALL_CALLS )
    {
        ITS_UINT failureCause = GetCDRFailureCause(ctxt);
        LogCDRData(ctxt, failureCause);
    }
}

int TransatelCAPToRoHandler::GetArmDataDetails(ArmData& armDataInst, TLegIDAndModeData& legIdMode)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    int ret = CMAPI_SUCCESS;
    if(!(armDataInst.has_monitormode()))
    {
        //DLOG_ERROR("TransatelCAPToRoHandler::GetArmDataDetails MonitorMode/LegId data absent");
        return (ADD_PROTOCOL_ACTION_ERR_ARM_DATA_MANDATORY_PARAM_MISSING);
    }

    if(armDataInst.has_legid())
        legIdMode.legId = armDataInst.legid();
    if("interrupted" == armDataInst.monitormode())
    {
      legIdMode.monitorMode = 0;
    }
    if("transparent" == armDataInst.monitormode())
    {
      legIdMode.monitorMode = 2;
    }
    if("notifyAndContinue" == armDataInst.monitormode())
    {
      legIdMode.monitorMode = 1;
    }

    return ret;
}

void TransatelCAPToRoHandler::CreateUserDataContext(IwfFsm* ctxt, pbStoredUserData storedUserData)
{
    //CLOG_DEBUG("TransatelCAPToRoHandler::CreateUserDataContext entry");
    pbCapRoTsl capRoTsl = storedUserData.caprotsl();

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    //CLOG_DEBUG("UserData is NULL creating UserData Context");
    userData = new TransatelCAPRoTransactionContext(ctxt->GetCapRoTslData());
    userData->SetReleaseCause(m_config.ReleaseCallCauseCode());

    userData->GetCapRoTslData()->CopyFrom(capRoTsl);
    userData->GetDccaContext().GetDccaReplicableData().CopyFrom(capRoTsl.dccactxt());
    ctxt->SetStoredUserData(userData);
    //CLOG_DEBUG("TransatelCAPToRoHandler::CreateUserDataContext exit");
}

void TransatelCAPToRoHandler::StartTimerHandling(IwfFsm* ctxt, const pbIwfTimerData timerData)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::StartTimerHandling entry");

    if(NULL == ctxt)
    {
        DLOG_ERROR("TransatelCAPToRoHandler::StartTimerHandling, IwfFsm is NULL.");
        return;
    }
    //2 Start InternalNoEventTimer
    STimerContext sTimerCtxt;
    sTimerCtxt.m_eKeyType = EKeyType::DIALOG_ID;
    sTimerCtxt.m_uiDlgId = ctxt->GetTcapDlgId();
    sTimerCtxt.m_eTimerType = (ETimerType)timerData.m_etimertype();

    IwfTimer timerObj;
    int uiTimeout = 0;
    int elapsedTime = 0;
    struct timeval currTv = GetCurrentMonotonic();
    //DLOG_DEBUG("Current time : %u Started Time : %u", currTv.tv_sec, timerData.m_tstarttime());
    elapsedTime = currTv.tv_sec - timerData.m_tstarttime();
    //DLOG_DEBUG("Elapsed Time : %d, TimerDuration : %d",elapsedTime,timerData.m_uiduration());
    uiTimeout = ((timerData.m_uiduration()) - elapsedTime);

    //DLOG_DEBUG("Normalized timer duration : %d",uiTimeout);

    if (uiTimeout <= 0)
    {
        DLOG_ERROR("Timer Duration is less than 0, Starting [ %d ] Timer for  %d sec", (ETimerType)timerData.m_etimertype(), SWITCHOVER_DELTA_TIME);
        uiTimeout = SWITCHOVER_DELTA_TIME;
    }
    unsigned int timerId;
    timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType,sTimerCtxt,uiTimeout);

    STimerInfo timerInfo;
    timerInfo.m_eTimerType = sTimerCtxt.m_eTimerType;
    timerInfo.m_uiDuration = timerData.m_uiduration();
    timerInfo.m_uiTimerId = timerId;

    struct timeval tv = GetCurrentMonotonic();
    timerInfo.m_tStartTime = tv.tv_sec;
    ctxt->SetTimerInfo(timerInfo);
    /*DLOG_DEBUG("Started TimerType : %s, TimerId %d for dialogId %u ; SessionId : %s for time %d",
            GetStrTimerType(sTimerCtxt.m_eTimerType).c_str(),
            timerInfo.m_uiTimerId,
            sTimerCtxt.m_uiDlgId,
            ctxt->GetDiaSessionId().c_str(),
            uiTimeout);*/

    //DLOG_DEBUG("TransatelCAPToRoHandler::StartTimerHandling exit");
}

void TransatelCAPToRoHandler::SetTranslatorState(IwfFsm *ctxt, TransState state)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetTranslatorState entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData != NULL)
    {
        userData->GetCapRoTslData()->set_currstate(state);
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::SetTranslatorState exit ");
}

TransState TransatelCAPToRoHandler::GetTranslatorState(IwfFsm *ctxt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetTranslatorState entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    if (userData != NULL)
    {
        //DLOG_DEBUG("Stored Translator State : %d",userData->GetCapRoTslData()->currstate());
        return userData->GetCapRoTslData()->currstate();
    }

    //DLOG_DEBUG("UserData not set returning default state : %d",TransState::INVALID_STATE);
    //DLOG_DEBUG("TransatelCAPToRoHandler::GetTranslatorState exit ");
    return TransState::INVALID_STATE;
}

void TransatelCAPToRoHandler::StoreConnectArgDataInUserData(IwfFsm *ctxt, const Ro_TSL::CreditControlAnswer *in)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::StoreConnectArgDatainUserData entry");

    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    pbConnectArgData connectArg;

    if(in != NULL)
    {
        //DLOG_DEBUG("TransatelCAPToRoHandler::StoreConnectArgDatainUserData CCA is not NULL Copying the Connect Parameters");
        if(in->containsServiceControl())
        {
            connectArg.set_hasservicecontrol(true);
            TransCustomAvp::ServiceControl servCtrl = in->getServiceControl();
            if(servCtrl.containsCAPInformation())
            {
                connectArg.set_hascapinfo(true);
                TransCustomAvp::CAPInformation capInfo = servCtrl.getCAPInformation();
                if(capInfo.containsCAPConnectInformation())
                {
                    connectArg.set_hascapconnectinfo(true);
                    TransCustomAvp::CAPConnectInformation capConnectInfo = capInfo.getCAPConnectInformation();
                    if(capConnectInfo.containsCAPAnnouncementAccessNumber())
                    {
                        connectArg.set_capanncaccessno(capConnectInfo.getCAPAnnouncementAccessNumber().value());

                        if(capConnectInfo.containsCAPAnnouncementAccessNumberNOA())
                        {
                            connectArg.set_capconnanncnonatrue(capConnectInfo.getCAPAnnouncementAccessNumberNOA().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectDestinationNumber())
                    {
                        connectArg.set_capconndestno(capConnectInfo.getCAPConnectDestinationNumber().value());
                        if(capConnectInfo.containsCAPConnectDestinationNumberNPI())
                        {
                            connectArg.set_capconndestnonpi(capConnectInfo.getCAPConnectDestinationNumberNPI().value());
                        }

                        if(capConnectInfo.containsCAPConnectDestinationNumberNature())
                        {
                            connectArg.set_capconndestnonature(capConnectInfo.getCAPConnectDestinationNumberNature().value());
                        }

                        if(capConnectInfo.containsCAPConnectDestinationNumberINN())
                        {
                            connectArg.set_capconndestinn(capConnectInfo.getCAPConnectDestinationNumberINN().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectGenericNumber())
                    {
                        connectArg.set_genericno(capConnectInfo.getCAPConnectGenericNumber().value());
                        if(capConnectInfo.containsCAPConnectGenericNumberNQI())
                        {
                            connectArg.set_genericnonqi(capConnectInfo.getCAPConnectGenericNumberNQI().value());
                        }

                        if(capConnectInfo.containsCAPConnectGenericNumberNII())
                        {
                            connectArg.set_genericnonii(capConnectInfo.getCAPConnectGenericNumberNII().value());
                        }

                        if(capConnectInfo.containsCAPConnectGenericNumberNPI())
                        {
                            connectArg.set_genericnonpi(capConnectInfo.getCAPConnectGenericNumberNPI().value());
                        }

                        if(capConnectInfo.containsCAPConnectGenericNumberARI())
                        {
                            connectArg.set_genericnoari(capConnectInfo.getCAPConnectGenericNumberARI().value());
                        }

                        if(capConnectInfo.containsCAPConnectGenericNumberSCI())
                        {
                            connectArg.set_genericnosci(capConnectInfo.getCAPConnectGenericNumberSCI().value());
                        }

                        if(capConnectInfo.containsCAPConnectGenericNumberNOA())
                        {
                            connectArg.set_genericnonature(capConnectInfo.getCAPConnectGenericNumberNOA().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectCallingCategory())
                    {
                        connectArg.set_capconncallingcategory(capConnectInfo.getCAPConnectCallingCategory().value());
                    }

                    if(capConnectInfo.containsCAPConnectRedirectingNumber())
                    {
                        connectArg.set_redirectingnum(capConnectInfo.getCAPConnectRedirectingNumber().value());
                        if(capConnectInfo.containsCAPConnectRedirectingNumberNPI())
                        {
                            connectArg.set_redirectnonpi(capConnectInfo.getCAPConnectRedirectingNumberNPI().value());
                        }

                        if(capConnectInfo.containsCAPConnectRedirectingNumberARI())
                        {
                            connectArg.set_redirectnoari(capConnectInfo.getCAPConnectRedirectingNumberARI().value());
                        }

                        if(capConnectInfo.containsCAPConnectRedirectingNumberNOA())
                        {
                            connectArg.set_redirectnonoa(capConnectInfo.getCAPConnectRedirectingNumberNOA().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectRedirectingIndicator() &&
                            capConnectInfo.containsCAPConnectOriginalRedirectingReason() &&
                            capConnectInfo.containsCAPConnectRedirectingCounter() &&
                            capConnectInfo.containsCAPConnectRedirectingReason())
                    {
                        connectArg.set_redirectind(capConnectInfo.getCAPConnectRedirectingIndicator().value());
                        connectArg.set_origredirectreason(capConnectInfo.getCAPConnectOriginalRedirectingReason().value());
                        connectArg.set_redirectioncount(capConnectInfo.getCAPConnectRedirectingCounter().value());
                        connectArg.set_redirectreason(capConnectInfo.getCAPConnectRedirectingReason().value());
                    }

                    if(capConnectInfo.containsCAPConnectOriginalCalledNumber())
                    {
                        connectArg.set_origcalledpartyid(capConnectInfo.getCAPConnectOriginalCalledNumber().value());
                        if(capConnectInfo.containsCAPConnectOriginalCalledNumberNPI())
                        {
                            connectArg.set_originalcallednonpi(capConnectInfo.getCAPConnectOriginalCalledNumberNPI().value());
                        }

                        if(capConnectInfo.containsCAPConnectOriginalCalledNumberARI())
                        {
                            connectArg.set_originalcallednoari(capConnectInfo.getCAPConnectOriginalCalledNumberARI().value());
                        }

                        if(capConnectInfo.containsCAPConnectOriginalCalledNumberNOA())
                        {
                            connectArg.set_originalcallednonoa(capConnectInfo.getCAPConnectOriginalCalledNumberNOA().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectoCSIApplicable())
                    {
                        if(capConnectInfo.getCAPConnectoCSIApplicable().value())
                        {
                            connectArg.set_capconnsuppressionofannc(capConnectInfo.getCAPConnectoCSIApplicable().value());
                        }
                    }

                    if(capConnectInfo.containsCAPConnectSuppressionOfAnnouncement())
                    {
                        if(capConnectInfo.getCAPConnectSuppressionOfAnnouncement().value())
                        {
                            connectArg.set_capconnsuppressionofannc(capConnectInfo.getCAPConnectSuppressionOfAnnouncement().value());
                        }
                    }
                }
            }
        }
        userData->SetConnectArgData(connectArg);
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::StoreConnectArgDatainUserData exit");
}

void TransatelCAPToRoHandler::StoreApplyChargignDataInUserData(IwfFsm *ctxt, const Ro_TSL::CreditControlAnswer *in)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransatelCAPToRoHandler::StoreApplyChargignDataInUserData entry");
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());

    pbACHData achData;

    if ( in->countMultipleServicesCreditControl() )
    {
        //NOTE: Assuming that only one MSCC will get from OCS for mapping all the IE's on cap side.
        Ro_TSL::MultipleServicesCreditControl serviceCreditControl =
            in->getMultipleServicesCreditControl(MSCC_AVP_INDEX);

        /*ReleaseIfDurationExceeded is populated if Final-Unit-Indication is  present
          and Final-Unit-Action=Terminate.
          tone is set if CAP-ACH-BeepTone AVP is set in CCA*/
        if(serviceCreditControl.containsFinalUnitIndication())
        {

            //DLOG_DEBUG("TransatelCAPToRoHandler::StoreApplyChargignDataInUserData Final Unit Indication Present");
            Ro_TSL::FinalUnitIndication finalUnitInd = serviceCreditControl.getFinalUnitIndication();

            achData.set_finalunitindication(finalUnitInd.getFinalUnitAction().value());

            unsigned int beepToneVal;
            if(ITS_SUCCESS == GetBeepToneFromCCA(*(const_cast<Ro_TSL::CreditControlAnswer*>(in)),beepToneVal))
            {
                //DLOG_DEBUG("TransatelCAPToRoHandler::StoreApplyChargignDataInUserData Beep Tone Present");
                achData.set_beeptone(beepToneVal);
            }
            userData->SetACHData(achData);
        }
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::StoreApplyChargignDataInUserData exit");
}

template <class T>
void TransatelCAPToRoHandler::CheckAndUpdateDisconTriggerTimeStamp(IwfFsm *ctxt, T& evntBcsm)
{
    /*ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransatelCAPToRoHandler::CheckAndUpdateDisconTriggerTimeStamp entry");*/
    TransatelCAPRoTransactionContext* userData =
        reinterpret_cast<TransatelCAPRoTransactionContext*>(ctxt->GetStoredUserData());
    Call_Type callType = userData->GetCallType();
    if (callType == MO_VOICE)
    {
        if(evntBcsm.IsOAnswer() != true)
        {
            //DLOG_DEBUG("Recieved Disconnect triggers for MO call, setting the DisconnnectTriggerTimeStamp");
            struct timeval tv = GetCurrentMonotonic();
            userData->SetDisconTriggerTimeStamp(tv.tv_sec);
        }
        /*else
        {
            DLOG_DEBUG("Recieved Answer trigger for MO call, not setting DisconnnectTriggerTimeStamp");
        }*/
    }
    else if (callType == MT_VOICE)
    {
        if(evntBcsm.IsTAnswer() != true)
        {
            //DLOG_DEBUG("Recieved Disconnect triggers for MT call, setting the DisconnnectTriggerTimeStamp");
            struct timeval tv = GetCurrentMonotonic();
            userData->SetDisconTriggerTimeStamp(tv.tv_sec);
        }
        /*else
        {
            DLOG_DEBUG("Recieved Answer trigger for MT call, not setting DisconnnectTriggerTimeStamp");
        }*/
    }
    //DLOG_DEBUG("TransatelCAPToRoHandler::CheckAndUpdateDisconTriggerTimeStamp exit");
}
