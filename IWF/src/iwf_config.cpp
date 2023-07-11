#include <sstream>
#include <fstream>
#include <stdlib.h>

#include <ssg_trace.h>
#include "iwf_config.h"
#include "iwf.h"
#include "its_dia_config.h"
#include "dcca_conf.h"
#include "iwf_prot_utils.h"

#include <utility>
#include <algorithm>

IwfHssToSgsnCache* IwfHssToSgsnCache::m_self = NULL;

    IwfLocalConfig::IwfLocalConfig()
: m_opc(),m_apc(0), m_invokeId(), m_selfSccpAddr(), m_remoteSccpAddr(), m_useSccpCdPAFromInMsg(false), m_diaErrorCode(3002), m_useexperimentalResultCode(false), m_clearCallSessionContexts(false), m_sessionContextcleanUpTimer(0), m_sendASPActiveFromStandBy(false),
    m_maxPeerStatusUpdates(0), m_pendingQueueExpiryTime(0), m_isKasmeGenerationRequired(false), m_useLocalSgsnNumberForMapping(false), m_globalSgsnNumberCounter(S6A_MAP_START_SGSN_NUM), m_validateVplmnIdRcvdInReq(false)
{
    m_ssn.clear();
    m_timers.invokeTimeout = IWF_TIMER_IVK_DEFAULT;
}

IwfLocalConfig::~IwfLocalConfig()
{
}

void IwfLocalConfig::Parse(const Json::Value& val, IwfConfig& conf)
{
    Json::Value entry;

    /*entry = val["opc"];
      if (entry.empty())
      {
      throw IwfConfigException("'opc' missing in 'local' config");
      }
      m_opc = entry.asInt();


      entry = val["apc"];
      if (entry.empty())
      {
      throw IwfConfigException("'apc' missing in 'local' config");
      }
      m_apc = entry.asInt();*/

    entry = val.get("family", "ansi");
    std::string fStr = entry.asString();
    if (fStr.compare("ansi") == 0)
    {
        m_iwfFamily = FAMILY_ANSI;
    }
    else if (fStr.compare("itu") == 0)
    {
        m_iwfFamily = FAMILY_ITU;
    }
    else
    {
        throw IwfConfigException("unknown 'family' in /destinations/sccp/");
    }

    /*entry = val["timers"];
      if (!entry.empty())
      {
      m_timers.invokeTimeout = entry.get("invoke-timeout",
      IWF_TIMER_IVK_DEFAULT).asInt();
      }*/

    entry = val["invoke-id"];
    if (entry.empty())
    {
        throw IwfConfigException("'invoke-id' missing in 'local' config");
    }

    m_invokeId.Parse(entry, conf);

    entry = val["self-sccp-address"];
    if (entry.empty())
    {
        throw IwfConfigException("'self-sccp-address' missing in 'local' config");
    }

    m_selfSccpAddr.Parse(entry, conf);

    entry = val["remote-sccp-address"];
    if (entry.empty())
    {
        throw IwfConfigException("'remote-sccp-address' missing in 'local' config");
    }

    m_remoteSccpAddr.Parse(entry, conf);

    //m_useSccpCdPAFromInMsg = val.get("use-sccp-cdpa-from-in-msg", false).asBool();

    entry = val["diameter-config"];
    if (!entry.empty())
    {
        entry = val["diameter-config"]["experimental-result-code"];
        if(!entry.empty())
        {
            m_useexperimentalResultCode = entry.asBool();
        }

        entry = val["diameter-config"]["error-code"];
        if (!entry.empty())
        {
            m_diaErrorCode = entry.asInt();
        }
    }

    entry = val["clear-user-session-contexts"];
    if(!entry.empty())
    {
        m_clearCallSessionContexts = entry.asBool();
    }

    entry = val["timer-value-for-session-context-cleanup"];
    if(!entry.empty())
    {
        m_sessionContextcleanUpTimer = entry.asInt();
    }

    entry = val["send-aspActive-in-standby-node"];
    if(!entry.empty())
    {
        m_sendASPActiveFromStandBy = entry.asBool();
    }

    entry = val["max-peer-status-update-count"];
    if(!entry.empty())
    {
        m_maxPeerStatusUpdates = entry.asInt();
    }

    entry = val["pending-queue-expiry-time"];
    if(!entry.empty())
    {
        m_pendingQueueExpiryTime = entry.asInt();
    }

    entry = val["is-kasme-generation-required"];
    if(!entry.empty())
    {
        m_isKasmeGenerationRequired = entry.asBool();
    }

    entry = val["use-local-sgsn-number"];
    if(!entry.empty())
    {
        m_useLocalSgsnNumberForMapping = entry.asBool();
    }

    entry = val["validate-vplmnid"];
    if(!entry.empty())
    {
        m_validateVplmnIdRcvdInReq = entry.asBool();
    }
}
// END 'local'

// dest entry
    IwfDest::IwfDest()
: m_type(IWF_ADDR_PCSSN),  // default pc-ssn
    m_family(0), // default ANSI
    m_isNational(false), // default false
    m_pc(0),
    m_ssn(0),
    m_ssnPresent(false),
    m_gti(0),
    m_tt(0),
    m_np(0),
    m_ecsNationalSpecific(false)
{
}

IwfDest::~IwfDest()
{
}

void IwfDest::Parse(const Json::Value& val, IwfConfig& conf)
{
    /*Json::Value entry = val["dia_ident"];
      if (entry.empty())
      {
      throw IwfConfigException("'dia_ident' missing in /destinations/sccp/");
      }
      m_diaIdentity = entry.asString();

      entry = val["dest"];
      if (entry.empty())
      {
      throw IwfConfigException("'dest' missing in /destinations/sccp/");
      }
      m_destName = entry.asString();

      entry = val["type"];
      if (entry.empty())
      {
      throw IwfConfigException("'type' missing in /destinations/sccp/");
      }
      std::string typeStr = entry.asString();
      if (typeStr.compare("pc-ssn") == 0)
      {
      m_type = IWF_ADDR_PCSSN;
      }
      else if (typeStr.compare("gt") == 0)
      {
      m_type = IWF_ADDR_GT;
      }
      else
      {
      throw IwfConfigException("'type' should be 'pc-ssn' or 'gt'");
      }

      entry = val.get("family", "ansi");
      std::string fStr = entry.asString();
      if (fStr.compare("ansi") == 0)
      {
      m_family = ITS_FLAG_ANSI;
      }
      else if (fStr.compare("itu") == 0)
      {
      m_family = ITS_FLAG_CCITT;
      }
      else
      {
      throw IwfConfigException("unknown 'family' in /destinations/sccp/");
      }

      m_isNational = val.get("is-national", false).asBool();

      entry = val["pc"];
      if (entry.empty() && m_type == IWF_ADDR_PCSSN)
      {
      throw IwfConfigException("'pc' missing in /destinations/sccp/");
      }
      if (m_type == IWF_ADDR_PCSSN)
      {
      m_pc = entry.asInt();
      }

      m_ssnPresent = val.get("ssn-present", true).asBool();

      entry = val["ssn"];
      if (entry.empty() && m_ssnPresent)
      {
      throw IwfConfigException("'ssn' missing in /destinations/sccp/");
      }
      if (m_ssnPresent)
      {
      m_ssn = entry.asInt();
      }

    if (m_type == IWF_ADDR_GT)
    {
        entry = val["gti"];
        m_gti = entry.asInt();

        if ((m_family == ITS_FLAG_ANSI && m_gti > ANSI_SCCP_GTI_002) ||
                (m_family == ITS_FLAG_CCITT && m_gti > ITU_SCCP_GTI_004))
        {
            throw IwfConfigException("Unsupported Global Title Indicator 'gti'");
        }

        entry = val["tt"];
        if (entry.empty())
        {
            throw IwfConfigException("Translation Type should be present in GT");
        }
        m_tt  = entry.asInt();
        entry = val["np"];
        m_np  = entry.asInt();
        entry = val["encoding-scheme"];
        m_ecsNationalSpecific = false;
        if (!entry.empty())
        {
            std::string ecs = entry.asString();
            if (ecs.compare("national-specific") == 0)
            {
                m_ecsNationalSpecific = true;
            }
        }
        entry = val["gtdigits"];
        if (!entry.empty())
        {
            m_gtAddr = entry.asString();
        }
    }*/
}

void IwfDest::SetParameters(IwfSigtranDestinationConfig* destInfo)
{
    /* The dia-ident is not being used hence not populating this value*/
    //m_diaIdentity = entry.asString();
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfDest::SetParameter entry");
    if( destInfo->has_destinationname() )
    {
        m_destName = destInfo->destinationname();
        DLOG_DEBUG("m_destName : %s",m_destName.c_str());
    }

    if( destInfo->has_addresstype() )
    {
        std::string typeStr = destInfo->addresstype();
        m_ssnPresent = true;
        if ((typeStr.compare("pc-ssn") == 0) || (typeStr.compare("PC-SSN") == 0))
        {
            m_type = IWF_ADDR_PCSSN;
            DLOG_DEBUG("m_ssnPresent : %d",m_ssnPresent);

        }
        else if ((typeStr.compare("gt") == 0) || (typeStr.compare("GT") == 0))
        {
            m_type = IWF_ADDR_GT;
            DLOG_DEBUG("m_type : %d",m_type);
        }
        else
        {
            DLOG_ERROR("'Address Type' should be 'pc-ssn' or 'gt'");
        }
    }

    /*if( destInfo->has_protocolfamily() )
      {
      std::string fStr = destInfo->protocolfamily();
      if (fStr.compare("ansi") == 0)
      {
      m_family = ITS_FLAG_ANSI;
      }
      else if (fStr.compare("itu") == 0)
      {
      m_family = ITS_FLAG_CCITT;
      }
      else
      {
      DLOG_ERROR("unknown 'Procotol family' in /destinations/sccp/");
      }
      }*/

    if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ITU)
    {
        m_family = ITS_FLAG_CCITT;
        DLOG_DEBUG("m_family : %d",m_family);
    }
    else if(IwfController::Instance().Config().LocalConfig().Family() == FAMILY_ANSI)
    {
        m_family = ITS_FLAG_ANSI;
        DLOG_DEBUG("m_family : %d",m_family);
    }
    else
    {
        DLOG_ERROR("unknown 'Procotol family' in /destinations/sccp/");
    }

    if( destInfo->has_networkindicator() )
    {
        m_isNational = destInfo->networkindicator();
        DLOG_DEBUG("m_isNational : %d",m_isNational);
    }

    if( destInfo->has_pointcode() )
    {
        m_pc = destInfo->pointcode();
        DLOG_DEBUG("m_pc : %d",m_pc);
    }

    if( destInfo->has_ssn() )
    {
        if (m_ssnPresent)
        {
            m_ssn = destInfo->ssn();
            DLOG_DEBUG("m_ssn : %d",m_ssn);
        }
    }

    if (m_type == IWF_ADDR_GT)
    {
        if( destInfo->has_gti() )
        {
            m_gti = destInfo->gti();
            DLOG_DEBUG("m_gti : %d",m_gti);
        }

        if ((m_family == ITS_FLAG_ANSI && m_gti > ANSI_SCCP_GTI_002) ||
                (m_family == ITS_FLAG_CCITT && m_gti > ITU_SCCP_GTI_004))
        {
            DLOG_ERROR("IwfDest::SetParameter - Unsupported Global Title Indicator 'gti'");
        }

        if( destInfo->has_translationtype() )
        {
            m_tt = destInfo->translationtype();
            DLOG_DEBUG("m_tt : %d",m_tt);
        }

        if( destInfo->has_numberingplan() )
        {
            m_np  = destInfo->numberingplan();
            DLOG_DEBUG("m_np : %d",m_np);
        }

        m_ecsNationalSpecific = false;
        if( destInfo->has_encodingscheme() )
        {
            if (destInfo->encodingscheme() == 0)
            {
                m_ecsNationalSpecific = true;
            }
        }

        if( destInfo->has_gtaddrdigits() )
        {
            m_gtAddr = destInfo->gtaddrdigits();
            DLOG_DEBUG("m_gtAddr : %s",m_gtAddr.c_str());
        }
    }

}


//
// home-based route
//
IwfRoute::IwfRoute()
    : m_mccHome(""),
    m_mncHome(""),
    m_appId(""),
    m_serviceKeyStart(""),
    m_serviceKeyEnd(""),
    m_callingGtAddrDigits(""),
    m_translatorId(IwfTranslator::InvalidId),
    m_ossn(),
    m_dssn(),
    m_dest(NULL),
    m_isServiceKeyInRange(false),
    m_serviceContextId("")
{
}

IwfRoute::~IwfRoute()
{
    // m_dest is owned by destinations, so not freed here
}

void IwfRoute::Parse(const Json::Value& val, IwfConfig& conf)
{
    /*Json::Value entry;

      entry = val["mcc"];
      if (entry.empty())
      {
      throw IwfConfigException("'mcc' missing in routing-rules/home-based");
      }
      m_mccHome = entry.asString();

      entry = val["mnc"];
      if (entry.empty())
      {
      throw IwfConfigException("'mnc' missing in routing-rules/home-based");
      }
      m_mncHome = entry.asString();

      entry = val["application-id"];
      if (entry.empty())
      {
      throw IwfConfigException("'applicaton-id' missing in routing-rules/home-based");
      }
      m_appId = entry.asString();

      entry = val["allowed-vplmn-id"];
      if(entry.empty())
      {
      throw IwfConfigException("'allowed-vplmn-id' missing in routing-rules/home-based");
      }

      m_allowedVplmnId = entry.asString();

      CreateAllowedVplmnIdVector(m_allowedVplmnId, ',');

      entry = val["translator"];
      if (entry.empty())
      {
      throw IwfConfigException("'translator' missing in routing-rules/home-based");
      }
      m_translatorId = IwfController::Instance().GetTranslatorId(entry.asString();
      if (m_translatorId == IwfTranslator::InvalidId)
      {
      std::stringstream str;
      str << "translator " << entry.asString() << " is not registered "
      << "[routing-rules/home-based]";
      throw IwfConfigException(str.str());
      }

      entry = val["ossn"];
      if (entry.empty())
      {
      throw IwfConfigException("'ossn' missing in routing-rules/home-based");
      }
      m_ossn = entry.asInt();

      entry = val["dest"];
      if (entry.empty())
      {
      throw IwfConfigException("'dest' missing in routing-rules/home-based");
      }
      m_dest = const_cast<IwfDest*>(&(conf.Destinations().Dest(entry.asString())));
      if (m_dest == NULL)
      {
      std::stringstream sstr;
      sstr << "Route dest '" << entry.asString() << "' not present in destinations";
      throw IwfConfigException(sstr.str());
      }
      entry = val["dest-realm"];
      if (!entry.empty())
      {
      m_destRealm = entry.asString();
      }*/
}

uint64_t IwfRoute::MakeKey(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey, std::string gtAddrDigits, SelectionCriteria selectionCriteria)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());


    switch (selectionCriteria)
    {
        case SELECT_MCC_MNC:
            {
                mcc.append(mnc);
                mcc.append(appId);
                return (atoll(mcc.c_str()));
            }
        case SELECT_SK:
            {
                return serviceKey;
            }
        case SELECT_SK_AND_MCC_MNC:
            {
                std::stringstream buf;
                buf << serviceKey << mcc << mnc;
                return (atoll(buf.str().c_str()));
            }
        default:
            {
                DLOG_ERROR("Invalid Selection Criteria Configured %d",
                        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());
            }
    }
    return -1;

}

std::string IwfRoute::MakeKey(std::string& rule_name, string& ossn, string& gtAddr, SelectionCriteria scVal)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    std::string keyVal("");
    switch (scVal)
    {
        case SELECT_MCC_MNC:
        case SELECT_SK:
        case SELECT_SK_AND_MCC_MNC:
        case SELECT_CLG_GTT_ADDR_DGTS_AND_SK:
        case SELECT_IMSI_PREFIX_AND_SK:
            {
                keyVal.append(rule_name);
                keyVal.append(ossn);
                return (keyVal);
            }
        case SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC:
        case SELECT_CLG_GTT_ADDR_DGTS:
            {
                keyVal.append(rule_name);
                keyVal.append(gtAddr);
                return keyVal;
            }
        default:
            {
                DLOG_ERROR("Invalid Selection Criteria Configured %d",
                        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());
            }
    }
    return keyVal;
}

void IwfRoute::SetParameter(IwfTranslatorRuleConfig* rule)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    IwfTranslatorConfig translator;
    IwfTranslatorType transType;
    IwfVplmnIdConfig vplmnIdConfig;
    std::string trans;

    if(rule->has_mcc())
    {
        m_mccHome = rule->mcc();
        DLOG_DEBUG("received mcc = %s",rule->mcc().c_str());
    }
    if(rule->has_mnc())
    {
        m_mncHome = rule->mnc();
        DLOG_DEBUG("received mnc = %s",rule->mnc().c_str());
    }
    if(rule->has_appid())
    {
        m_appId = rule->appid();
        DLOG_DEBUG("received AppId = %s",rule->appid().c_str());
    }
#if 0
    if(rule->has_servicekeystartvalue())
    {
        char buffer [16];
        snprintf(buffer, 16, "%d", rule->servicekeystartvalue());
        m_serviceKeyStart = buffer;
        //m_serviceKeyStart = rule->servicekeystartvalue();
        DLOG_DEBUG("received Servicekey Start Value = %d",rule->servicekeystartvalue());
    }
#endif
    if(rule->has_isservicekeyinrange())
    {
        m_isServiceKeyInRange = rule->isservicekeyinrange();
        DLOG_DEBUG("received Servicekey in Range = %d",rule->isservicekeyinrange());
    }

    if(rule->has_servicekey())
    {
        m_serviceKeyList.clear();
        DLOG_DEBUG("received Servicekey = %s",rule->servicekey().c_str());
        string srvKey = rule->servicekey();
        if(m_isServiceKeyInRange)
        {
            //If Range
            string startvalue = "";
            string endvalue = "";
            char *token = strtok( const_cast<char*> (srvKey.c_str()),"-");
            startvalue = token;
            while(token != NULL)
            {
                token = strtok(NULL, "-");
                if(token != NULL)
                    endvalue = token;
            }
            TServiceKeyStruct keyStruct;
            keyStruct.low = atoi(startvalue.c_str());
            keyStruct.high = atoi(endvalue.c_str());
            DLOG_DEBUG("Start Value : %d , End Value : %d",keyStruct.low, keyStruct.high);
            m_serviceKeyList.push_back(keyStruct);
        }
        else
        {
            if(!strcmp(srvKey.c_str(),"*")) //If WildCard
            {
                TServiceKeyStruct keyStruct;
                keyStruct.low = WILDCARD_SERVICE_KEY;
                keyStruct.high = -1;
                m_serviceKeyList.push_back(keyStruct);
            }
            else // If List
            {
                char *token = strtok( const_cast<char*> (srvKey.c_str()),",");
                while(token != NULL)
                {
                    TServiceKeyStruct keyStruct;
                    keyStruct.low = atoi(token);
                    keyStruct.high = -1;
                    m_serviceKeyList.push_back(keyStruct);
                    DLOG_DEBUG("Start Value : %d ",keyStruct.low);
                    token = strtok(NULL, ",");
                }
            }
        }
    }
#if 0
    if(rule->has_servicekeyendvalue())
    {
        char buffer [16];
        snprintf(buffer, 16, "%d", rule->servicekeyendvalue());
        m_serviceKeyEnd = buffer;
        //m_serviceKeyEnd = rule->servicekeyendvalue();
        DLOG_DEBUG("received Servicekey End Value = %d",rule->servicekeyendvalue());
    }
#endif
    if(rule->has_callinggtaddrdigits())
    {
        m_callingGtAddrDigits = rule->callinggtaddrdigits();
        DLOG_DEBUG("received AppId = %s",rule->callinggtaddrdigits().c_str());
    }
    if(rule->has_ossn())
    {
        m_ossn = rule->ossn();
        DLOG_DEBUG("received Ossn = %d",rule->ossn());
    }

    if(rule->has_dssn())
    {
        m_dssn = rule->dssn();
        DLOG_DEBUG("received Dssn = %d",rule->dssn());
    }
    if(rule->has_servicecontextid())
    {
        m_serviceContextId = rule->servicecontextid();
        DLOG_DEBUG("received ServiceContextId = %s",rule->servicecontextid().c_str());
    }
    if(rule->has_translatorinfo())
    {
        translator = rule->translatorinfo();
        m_translatorId = IwfController::Instance().GetTranslatorId(translator.translatorname());
        DLOG_DEBUG("received translator name : %s",translator.translatorname().c_str());
    }
    if(rule->has_translatortype())
    {
        transType = rule->translatortype();
        trans = transType.translatortypename();
        if( trans == SS7_STRING )
        {
            m_destRealm = rule->destinationname();
            DLOG_DEBUG("received translation Type SS7");
            DLOG_DEBUG("received destination name : %s",rule->destinationname().c_str());

            if(rule->has_destinationhost())
            {
                m_destHost = rule->destinationhost();
                DLOG_DEBUG("received destination host name : %s",rule->destinationhost().c_str());
            }
            if(rule->has_alternatehost())
            {
                m_altHost = rule->alternatehost();
                DLOG_DEBUG("received alternate destination host name : %s",rule->alternatehost().c_str());
            }
            if(rule->has_alternaterealm())
            {
                m_altRealm = rule->alternaterealm();
                DLOG_DEBUG("received alternate realm name : %s",rule->alternaterealm().c_str());
            }
        }
        else if( trans == DIAMETER_STRING )
        {
            m_dest = const_cast<IwfDest*>(&(IwfController::Instance().Config().Destinations().Dest(rule->destinationname())));
            if (m_dest == NULL)
            {
                std::stringstream sstr;
                sstr << "Route dest '" << rule->destinationname() << "' not present in destinations";
                throw IwfConfigException(sstr.str());
            }
            DLOG_DEBUG("received translation Type Diameter");
            DLOG_DEBUG("received destination name : %s",rule->destinationname().c_str());
            m_isAltDestSet = false;
            if(rule->has_alternaterealm())
            {
                m_altdest = const_cast<IwfDest*>(&(IwfController::Instance().Config().Destinations().Dest(rule->alternaterealm())));
                if (m_altdest == NULL)
                {
                    std::stringstream sstr;
                    sstr << "Route alt-dest '" << rule->alternaterealm() << "' not present in destinations";
                    throw IwfConfigException(sstr.str());
                }
                m_isAltDestSet = true;
                DLOG_DEBUG("received alt-destination name : %s",rule->alternaterealm().c_str());
            }
        }
        else
        {
            DLOG_DEBUG("received translation Type HTTP");
        }
    }

    if(rule->has_imsiprefix())
    {
        m_imsiPrefix = rule->imsiprefix();
        DLOG_DEBUG("received IMSI-Prefix = %s",rule->imsiprefix().c_str());
    }


    if(rule->has_proactionrulename())
    {
        m_protActionRuleName = rule->proactionrulename();
        DLOG_DEBUG("received ProActionRuleName = %s",rule->proactionrulename().c_str());
    }
    int numVplmnId = rule->vplmninfo_size();
    DLOG_DEBUG("VplmnId Count : %d", numVplmnId);
    if(numVplmnId > 0)
    {
        for(int i = 0; i < numVplmnId; i++)
        {
            vplmnIdConfig = rule->vplmninfo(i);
            if(vplmnIdConfig.has_allowedvplmnid())
            {
                DLOG_DEBUG("VplmnId [%d] : %s", i, vplmnIdConfig.allowedvplmnid().c_str());
                std::string mcc = "";
                std::string mnc = "";
                IWFUtils::ExtractMncMcc(vplmnIdConfig.allowedvplmnid(), mcc, mnc);
                if(!mcc.empty() && !mnc.empty())
                {
                    unsigned char plmn[4] = {0};
                    IWFUtils::CreateVisitedPlmn(plmn, mcc, mnc);
                    std::string vplmn = "";
                    IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmn, 0, true);
                    DLOG_DEBUG("VplmnId after transfroming [%d] : %s", i, vplmn.c_str());
                    m_vplmnVec.push_back(vplmn);
                }
                else
                {
                    DLOG_WARNING("configured mcc/mnc is wrong, cannot set visted plmn-Id");
                }
            }
        }
    }
}

void IwfRoute::SetParameter(IwfRoute* route)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    std::string trans;

    if(!route->MCC().empty())
    {
        m_mccHome = route->MCC();
        DLOG_DEBUG("received mcc = %s",route->MCC().c_str());
    }
    if(!route->MNC().empty())
    {
        m_mncHome = route->MNC();
        DLOG_DEBUG("received mnc = %s",route->MNC().c_str());
    }
    if(!route->AppId().empty())
    {
        m_appId = route->AppId();
        DLOG_DEBUG("received AppId = %s",route->AppId().c_str());
    }

    if(!route->ServiceKeyStart().empty())
    {
        m_serviceKeyStart = route->ServiceKeyStart();
        DLOG_DEBUG("received Servicekey Start Value = %s",route->ServiceKeyStart().c_str());
    }

    m_isServiceKeyInRange = route->IsServiceKeyInRange();
    DLOG_DEBUG("received Servicekey in Range = %d",route->IsServiceKeyInRange());

    if(!route->ServiceKeyEnd().empty())
    {
        m_serviceKeyEnd = route->ServiceKeyEnd();
        DLOG_DEBUG("received Servicekey End Value = %s",route->ServiceKeyEnd().c_str());
    }

    if(!route->CallingGtAddrDigits().empty())
    {
        m_callingGtAddrDigits = route->CallingGtAddrDigits();
        DLOG_DEBUG("received AppId = %s", route->CallingGtAddrDigits().c_str());
    }

    m_ossn = route->OriginSSN();
    DLOG_DEBUG("received Ossn = %d",route->OriginSSN());

    m_dssn = route->DestinationSSN();
    DLOG_DEBUG("received Dssn = %d",route->DestinationSSN());

    if(!route->ServiceContextId().empty())
    {
        m_serviceContextId = route->ServiceContextId();
        DLOG_DEBUG("received ServiceContextId = %s",route->ServiceContextId().c_str());
    }

    m_translatorId = route->TranslatorId();
    DLOG_DEBUG("received translatorId = %d",route->TranslatorId());

    if(!route->destRealm().empty())
    {
        m_destRealm = route->destRealm();
        DLOG_DEBUG("received destination name : %s",route->destRealm().c_str());
    }

    m_dest = const_cast<IwfDest*>(&(route->Dest()));
}



// 'routing-rules'

IwfRoutingRules::IwfRoutingRules()
{
}

IwfRoutingRules::~IwfRoutingRules()
{
    for(Routes::iterator it = m_routes.begin(); it != m_routes.end();)
    {
        //delete it->second;
        m_routes.erase(it++);
    }
}

void IwfRoutingRules::Parse(const Json::Value& val, IwfConfig& conf)
{
    Json::Value entry = val["e164-number-range"];
    if (entry.empty())
    {
        throw IwfConfigException("'e164-number-range' rules missing in 'routing-rules'");
    }

    m_ocE164NumRange.Parse(entry, conf);

    /*entry = val["home-based"];
      if (entry.empty())
      {
      throw IwfConfigException("'home-based' rules missing in 'routing-rules'");
      }

      int retVal = ITS_SUCCESS;
      uint64_t key;
      for (unsigned i = 0; i < entry.size(); i++)
      {
    // exception safety
    std::auto_ptr<IwfRoute> route(new IwfRoute());
    route->Parse(entry[i], conf);

    key = IwfRoute::MakeKey(route->MCC(), route->MNC(), route->AppId(), route->ServiceKeyStart(), route->CallingGtAddrDigits());
    m_routes[key] = route.get();

    // IwfRoute* is now managed by m_routes, don't free auto_ptr
    route.release();
    }*/
}

/*
bool IwfRoutingRules::IsRouteAvailable(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey, std::string gtAddrDigits)
{
    if (m_routes.find(IwfRoute::MakeKey(mcc, mnc,appId, serviceKey, gtAddrDigits,
                    IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())) != m_routes.end())
        return true;
    else
        return false;
}*/

bool IwfRoutingRules::IsRouteAvailable(string& rule_name, std::string& gtAddrDigits)
{
    std::vector<unsigned> ssnList = IwfController::Instance().Config().LocalConfig().LocalSSN();
    CLOG_DEBUG("Size Of Vector = %d",ssnList.size());
    for(int i = 0; i < ssnList.size(); i++)
    {
        stringstream ss;
        CLOG_DEBUG("Vector[%d] = %d", i, ssnList[i]);
        ss << ssnList[i];
        string strSSN = ss.str();
        if(m_routes.find(IwfRoute::MakeKey(rule_name,strSSN,gtAddrDigits,IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())) != m_routes.end())
            return true;
    }
    return false;
}
//IwfRoutingRules::IwfRouteRef IwfRoutingRules::Route(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey, std::string callingGtAddrDigits)
IwfRoutingRules::IwfRouteRef IwfRoutingRules::Route(std::string& ruleName,std::string callingGtAddrDigits)
{
    std::vector<unsigned> ssnList = IwfController::Instance().Config().LocalConfig().LocalSSN();
    for(int i = 0; i < ssnList.size(); i++)
    {
        stringstream ss;
        CLOG_DEBUG("Vector[%d] = %d", i, ssnList[i]);
        ss << ssnList[i];
        string strSSN = ss.str();
        if(m_routes.find(IwfRoute::MakeKey(ruleName,strSSN,callingGtAddrDigits,IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())) != m_routes.end())
            return m_routes[IwfRoute::MakeKey(ruleName, strSSN, callingGtAddrDigits, IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())];
    }
    return NULL;
}



int IwfRoutingRules::SetRoutingRulesConfig(IwfTranslatorRulesConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numOfRules = 0;
    IwfTranslatorRuleConfig rule;
    SelectionCriteria selectionCriteria = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();

    DLOG_DEBUG("IwfRoutingRules::SetRoutingRulesConfig Entry");
    numOfRules = req->ruleinfo_size();
    try
    {
        if ( numOfRules > 0)
        {
            for(int ruleNum = 0 ; ruleNum < numOfRules ; ruleNum++)
            {
                rule = req->ruleinfo(ruleNum);
                if( ((rule.has_mcc() && rule.has_mnc()) || (rule.has_mcc() && rule.has_mnc() && rule.has_appid())
                            || (rule.has_servicekeystartvalue()) || (rule.has_imsiprefix() && rule.has_servicekey())) && ( rule.has_translatorinfo() && rule.has_translatortype()) )
                {

                    IwfTranslatorConfig translatoConfig = rule.translatorinfo();
                    std::string translatorName = translatoConfig.translatorname();
                    if(translatorName == "MAP-s6a" && rule.has_servicekeystartvalue())
                    {

                        DLOG_ERROR("ServiceKey Configured for MAP-S6a : Invalid Configuration");
                        return !ITS_SUCCESS;
                    }

                    //int64_t l_routingKey = IwfRoute::MakeKey(rule.mcc(), rule.mnc(), rule.appid(), rule.servicekeystartvalue(), rule.callinggtaddrdigits(),
                    //        selectionCriteria);
                    string ruleName = rule.translatorrulename();
                    stringstream ss;
                    ss <<  rule.ossn();
                    string ossn = ss.str();
                    string clgGtAddr = rule.callinggtaddrdigits();
                    string routingKey = IwfRoute::MakeKey(ruleName,ossn,clgGtAddr,
                            selectionCriteria);
                    Routes::iterator it = m_routes.find(routingKey);
                    if( it != m_routes.end() )
                    {
                        DLOG_ERROR("RoutingKey already present, Rule cannot be added");
                        return ADD_TRANSRULES_ERR_TRANS_RULE_ALREADY_PRESENT;
                    }
                    else
                    {
                        IwfRouteRef route = new IwfRoute();
                        route->SetParameter(&rule);

                        if(routingKey == "")
                        {
                            DLOG_ERROR("Invalid SelectionCriteria Configured");
                            retVal = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                        }
                        else
                        {
                            DLOG_DEBUG("Routing Key : %s Created for New RoutingRule ",routingKey.c_str());
                            m_routes[routingKey] = route;
                            IwfController::Instance().Config().InsertImsiPrefixVsRuleInMAP(rule.imsiprefix(),rule.translatorrulename());
                            //imsiPrefixAndRuleNameLst.insert(pair<string,string> (route->GetImsiPrefix(),rule.translatorrulename()));
                            IwfController::Instance().Config().InsertRuleVsSKListInMap(rule.translatorrulename(), route->GetServiceKeyList());
                        }

                        /*
                        if((selectionCriteria == SELECT_SK || selectionCriteria == SELECT_SK_AND_MCC_MNC) &&
                                route->IsServiceKeyInRange())
                        {
                            for(range = atoll(route->ServiceKeyStart().c_str()); range <= atoll(route->ServiceKeyEnd().c_str()); range++)
                            {
                                int64_t routingKey = IwfRoute::MakeKey(route->MCC(), route->MNC(), route->AppId(), range, route->CallingGtAddrDigits(),
                                        selectionCriteria);
                                if(routingKey == -1)
                                {
                                    DLOG_ERROR("Invalid SelectionCriteria Configured");
                                    retVal = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                                }
                                else
                                {
                                    // This log takes too much time if the SK range is too big, so commenting it
                                    //DLOG_DEBUG("Routing Key : %lld Created for New RoutingRule ",routingKey);
                                    m_routes[routingKey] = route;
                                }
                            }
                            DLOG_DEBUG("Routing keys : %lld to %lld created for"
                                       " new routing rules",
                                       atoll(route->ServiceKeyStart().c_str()),
                                       atoll(route->ServiceKeyEnd().c_str()));
                        }
                        else
                        {
                            int64_t routingKey = IwfRoute::MakeKey(route->MCC(), route->MNC(), route->AppId(), atoll(route->ServiceKeyStart().c_str()),
                                    route->CallingGtAddrDigits(), selectionCriteria);
                            if(routingKey == -1)
                            {
                                DLOG_ERROR("Invalid SelectionCriteria Configured");
                                retVal = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                            }
                            else
                            {
                                DLOG_DEBUG("Routing Key : %lld Created for New RoutingRule",routingKey);
                                m_routes[routingKey] = route;
                            }
                        }*/
                    }
                }
                else
                {
                    DLOG_ERROR("Missing mandator parameter for rule configurations(mcc/mnc/appId/serviceKey)");
                    retVal = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                }
            }
            IwfController::Instance().Config().GetPrefixRulesStore().PopulateRules(IwfController::Instance().Config().GetImsiPrefixVsRuleMap());
        }
        else
        {
            DLOG_ERROR("IwfRoutingRules::SetRoutingRulesConfig no Translator Rule data present");
            retVal = ADD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
        }
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Add IWF translator configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("IwfRoutingRules::SetRoutingRulesConfig no Translator Rule data present");
        retVal = ADD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfRoutingRules::SetRoutingRulesConfig Exit");
    return retVal;
}

int IwfRoutingRules::ModifyRoutingRulesConfig(IwfTranslatorRulesConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numOfRules = 0;
    IwfTranslatorRuleConfig rule;
    string oldRoutingKey, newRoutingKey;
    SelectionCriteria selectionCriteria = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();

    DLOG_DEBUG("IwfRoutingRules::ModifyRoutingRulesConfig Entry");
    numOfRules = req->ruleinfo_size();
    try
    {
        if ( numOfRules > 0)
        {
            for(int ruleNum = 0 ; ruleNum < numOfRules ; ruleNum++)
            {
                rule = req->ruleinfo(ruleNum);

                if( ((rule.has_mcc() && rule.has_mnc()) || (rule.has_mcc() && rule.has_mnc() && rule.has_appid())
                            || (rule.has_servicekeystartvalue()) || (rule.has_servicekey() && rule.has_imsiprefix())))
                {
                    string ruleName = rule.translatorrulename();
                    bool isRuleDeleted = false;
                    if(rule.has_oldossn())
                    {
                        stringstream ss;
                        ss <<  rule.oldossn();
                        string ossn = ss.str();
                        string clgGtAddr = rule.callinggtaddrdigits();
                        string routingKey = IwfRoute::MakeKey(ruleName,ossn,clgGtAddr,
                                selectionCriteria);
                        Routes::iterator it = m_routes.find(routingKey);
                        if( it != m_routes.end() )
                        {
                            isRuleDeleted = true;
                            m_routes.erase(it);
                            DLOG_DEBUG("Deleted Route with old Ossn");
                        }
                        else
                        {
                            DLOG_ERROR("routing rule not found");
                            return MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
                        }
                    }

                    stringstream ss;
                    ss <<  rule.ossn();
                    string ossn = ss.str();
                    string clgGtAddr = rule.callinggtaddrdigits();
                    string routingKey = IwfRoute::MakeKey(ruleName,ossn,clgGtAddr,
                            selectionCriteria);

                    if(!isRuleDeleted)
                    {
                        Routes::iterator it = m_routes.find(routingKey);
                        if( it != m_routes.end() )
                        {
                            m_routes.erase(it);
                        }
                        else
                        {
                            DLOG_ERROR("routing rule not found");
                            return MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
                        }
                    }

                    IwfRouteRef route = new IwfRoute();
                    route->SetParameter(&rule);
                    if(routingKey == "")
                    {
                        DLOG_ERROR("Invalid SelectionCriteria Configured");
                        retVal = ADD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
                    }
                    else
                    {
                        DLOG_DEBUG("Routing Key : %s Created for New RoutingRule ",routingKey.c_str());
                        m_routes[routingKey] = route;
                        IwfController::Instance().Config().DeleteImsiPrefixVsRuleInMap(rule.translatorrulename());
                        IwfController::Instance().Config().DeleteRuleVsSKListInMap(rule.translatorrulename());
                        IwfController::Instance().Config().InsertImsiPrefixVsRuleInMAP(rule.imsiprefix(),rule.translatorrulename());
                        //imsiPrefixAndRuleNameLst.insert(pair<string,string> (route->GetImsiPrefix(),rule.translatorrulename()));
                        IwfController::Instance().Config().InsertRuleVsSKListInMap(rule.translatorrulename(), route->GetServiceKeyList());
                    }
                }
                else
                {
                    //DLOG_ERROR("Translator rule with mcc = %s, mnc = %s, appId = %s not found",
                    //        rule.oldmcc().c_str(),rule.oldmnc().c_str()
                    //        ,rule.oldappid().c_str());

                    retVal = MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
                }
            }
            int val = IwfController::Instance().Config().GetPrefixRulesStore().FlushRules();
            val = IwfController::Instance().Config().GetPrefixRulesStore().PopulateRules(IwfController::Instance().Config().GetImsiPrefixVsRuleMap());
        }
        else
        {
            DLOG_ERROR("Missing mandator parameter for translator rule modification(mcc/mnc/appId)");
            retVal = MOD_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
        }
    }
    catch(std::exception& exp)
    {
        DLOG_DEBUG("Modify IWF translator configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("IwfRoutingRules::ModifyRoutingRulesConfig no Translator Rule data present");
        retVal = MOD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
    }

    DLOG_DEBUG("IwfRoutingRules::ModifyRoutingRulesConfig Exit");
    return retVal;
}

int IwfRoutingRules::DeleteRoutingRulesConfig(IwfTranslatorRulesConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numOfRules = 0;
    IwfTranslatorRuleConfig rule;
    SelectionCriteria selectionCriteria = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();

    DLOG_DEBUG("IwfRoutingRules::DeleteRoutingRulesConfig Entry");
    numOfRules = req->ruleinfo_size();
    if ( numOfRules > 0)
    {
        for(int ruleNum = 0 ; ruleNum < numOfRules ; ruleNum++)
        {
            rule = req->ruleinfo(ruleNum);
            if(rule.has_ossn())
            {
                string ruleName = rule.translatorrulename();
                stringstream ss;
                ss <<  rule.ossn();
                string ossn = ss.str();
                string clgGtAddr = rule.callinggtaddrdigits();
                string routingKey = IwfRoute::MakeKey(ruleName,ossn,clgGtAddr,
                        selectionCriteria);
                Routes::iterator it = m_routes.find(routingKey);
                if( it != m_routes.end() )
                {
                    m_routes.erase(it);
                    IwfController::Instance().Config().DeleteImsiPrefixVsRuleInMap(rule.translatorrulename());
                    IwfController::Instance().Config().DeleteRuleVsSKListInMap(rule.translatorrulename());
                    int val = IwfController::Instance().Config().GetPrefixRulesStore().FlushRules();
                    val = IwfController::Instance().Config().GetPrefixRulesStore().PopulateRules(IwfController::Instance().Config().GetImsiPrefixVsRuleMap());
                    DLOG_DEBUG("routing key deleted = %s",routingKey.c_str());
                }
                else
                {
                    DLOG_ERROR("routing rule not found");
                    retVal = DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;

                }
            }
#if 0
            if( (rule.has_mcc() && rule.has_mnc()) || (rule.has_mcc() && rule.has_mnc() && rule.has_appid())
                    || (rule.has_servicekeystartvalue()))
            {
                if(rule.has_isservicekeyinrange() && rule.isservicekeyinrange())
                {
                    for(range = rule.servicekeystartvalue(); range <= rule.servicekeyendvalue(); range++)
                    {
                        retVal = DeleteRuleFromMap(rule, range);
                        if(retVal != ITS_SUCCESS)
                        {
                            return retVal;
                        }
                    }
                }
                else
                {
                    range = rule.servicekeystartvalue();
                    retVal = DeleteRuleFromMap(rule, range);
                    if(retVal != ITS_SUCCESS)
                    {
                        return retVal;
                    }
                }
            }
            else
            {
                DLOG_ERROR("Missing mandator parameter for rule configurations(mcc/mnc/appId)");
                retVal = DEL_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
            }
#endif
        }
    }
    else
    {
        DLOG_ERROR("IwfRoutingRules::DeleteRoutingRulesConfig no Translator Rule data present");
        retVal = ADD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfRoutingRules::DeleteRoutingRulesConfig Exit");
    return retVal;
}

int IwfRoutingRules::DeleteRuleFromMap(IwfTranslatorRuleConfig rule, int32_t serviceKey)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::DeleteRuleFromMap Entry");
    //int64_t routingKey;
    string routingKey;
    int retVal = ITS_SUCCESS;
    //routingKey = IwfRoute::MakeKey(rule.mcc(), rule.mnc(), rule.appid(), serviceKey, rule.callinggtaddrdigits(),
    //        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());

    //routingKey = IwfRoute::MakeKey(rule.mcc(), rule.mnc(), rule.appid(), serviceKey, rule.callinggtaddrdigits(),
    //        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());
    //if(routingKey)
	if(!routingKey.empty())
    {
        Routes::iterator it = m_routes.find(routingKey);
        if( it != m_routes.end() )
        {
            m_routes.erase(it);
            DLOG_DEBUG("routing key deleted = %s",routingKey.c_str());
        }
        else
        {
            DLOG_ERROR("routing rule not found");
            retVal = DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
        }
    }
    else
    {
        DLOG_ERROR("Invalid SelectionCriteria Configured");
        retVal = DEL_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
    }
    DLOG_DEBUG("IwfRoutingRules::DeleteRuleFromMap Exit");
    return retVal;
}

int IwfRoutingRules::DeleteAllowedVplmnIdFromRoutingRulesConfig(IwfTranslatorRulesConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int numOfRules = 0;
    IwfTranslatorRuleConfig rule;

    DLOG_DEBUG("IwfRoutingRules::DeleteRoutingRulesConfig Entry");
    numOfRules = req->ruleinfo_size();
    if ( numOfRules > 0)
    {
        for(int ruleNum = 0 ; ruleNum < numOfRules ; ruleNum++)
        {
            rule = req->ruleinfo(ruleNum);
            //if( (rule.has_mcc() && rule.has_mnc()) || (rule.has_mcc() && rule.has_mnc() && rule.has_appid())
            //        || (rule.has_servicekeystartvalue()))
            {
                retVal = DeleteAllowedVplmnIdFromRule(rule);
                if(retVal != ITS_SUCCESS)
                {
                    return retVal;
                }
            }
            //else
            //{
            //    DLOG_ERROR("Missing mandator parameter for rule configurations(mcc/mnc/appId)");
            //    retVal = DEL_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
            //}
        }
    }
    else
    {
        DLOG_ERROR("IwfRoutingRules::DeleteRoutingRulesConfig no Translator Rule data present");
        retVal = ADD_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfRoutingRules::DeleteRoutingRulesConfig Exit");
    return retVal;
}

int IwfRoutingRules::DeleteAllowedVplmnIdFromRule(IwfTranslatorRuleConfig rule)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::DeleteRuleFromMap Entry");
    //int64_t routingKey;
    //string routingKey;
    SelectionCriteria selectionCriteria = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();
    string ruleName = rule.translatorrulename();
    stringstream ss;
    ss <<  rule.ossn();
    string ossn = ss.str();
    string clgGtAddr = rule.callinggtaddrdigits();
    string routingKey = IwfRoute::MakeKey(ruleName,ossn,clgGtAddr,
            selectionCriteria);

    int retVal = ITS_SUCCESS;
    IwfVplmnIdConfig vplmnIdConfig;

    //routingKey = IwfRoute::MakeKey(rule.mcc(), rule.mnc(), rule.appid(), rule.servicekeystartvalue(), rule.callinggtaddrdigits(),
    //        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());
    //routingKey = IwfRoute::MakeKey(rule.mcc(), rule.mnc(), rule.appid(), rule.servicekeystartvalue(), rule.callinggtaddrdigits(),
    //        IwfController::Instance().Config().LocalConfig().GetSelectionCriteria());
    //if(routingKey)
	if(!routingKey.empty())
    {
        Routes::iterator it = m_routes.find(routingKey);
        if( it != m_routes.end() )
        {
            IwfRouteRef iwfRoute = it->second;
            int numVplmnId = rule.vplmninfo_size();
            DLOG_DEBUG("VplmnId Count : %d", numVplmnId);
            if(numVplmnId > 0)
            {
                for(int i = 0; i < numVplmnId; i++)
                {
                    vplmnIdConfig = rule.vplmninfo(i);
                    if(vplmnIdConfig.has_allowedvplmnid())
                    {
                        DLOG_DEBUG("VplmnId [%d] : %s", i, vplmnIdConfig.allowedvplmnid().c_str());
                        std::string mcc = "";
                        std::string mnc = "";
                        IWFUtils::ExtractMncMcc(vplmnIdConfig.allowedvplmnid(), mcc, mnc);
                        if(!mcc.empty() && !mnc.empty())
                        {
                            unsigned char plmn[4] = {0};
                            IWFUtils::CreateVisitedPlmn(plmn, mcc, mnc);
                            std::string vplmn = "";
                            IWFUtils::TBCDToString(&plmn[0], MAP_GR_REQUESTING_PLMN_ID_SZ, vplmn, 0, true);
                            DLOG_DEBUG("VplmnId after transfroming [%d] : %s", i, vplmn.c_str());
                            std::vector<std::string> vecVplmn = iwfRoute->vplmnId();
                            std::vector<std::string>::iterator it = std::find(vecVplmn.begin(), vecVplmn.end(), vplmn);
                            if(it != vecVplmn.end())
                            {
                                DLOG_DEBUG("Allowed VplmnId deleted from Rule : %s", (*it).c_str());
                                vecVplmn.erase(it);
                            }
                            else
                            {
                                DLOG_ERROR("AllowedVplmnId : %s not found in Rule", vplmnIdConfig.allowedvplmnid().c_str());
                                retVal = !ITS_SUCCESS;
                            }
                        }
                        else
                        {
                            DLOG_WARNING("Received mcc/mnc is wrong, cannot delete visted plmn-Id");
                        }
                    }
                }
            }
        }
        else
        {
            DLOG_ERROR("routing rule not found");
            retVal = DEL_TRANSRULES_ERR_TRANS_RULE_NOT_PRESENT;
        }
    }
    else
    {
        DLOG_ERROR("Invalid SelectionCriteria Configured");
        retVal = DEL_TRANSRULES_ERR_MISSING_MANDATORY_PARAM;
    }
    DLOG_DEBUG("IwfRoutingRules::DeleteRuleFromMap Exit");
    return retVal;
}

int IwfRoutingRules::CleanRoutingRuleMap()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::CleanMap Entry");
    for(Routes::iterator it = m_routes.begin(); it != m_routes.end();)
    {
        it->second = NULL;
        m_routes.erase(it++);
    }
    DLOG_DEBUG("IwfRoutingRules::CleanMap Exit");
    return ITS_SUCCESS;
}

#if 0
int IwfRoutingRules::CheckFeasiblityOfRules(SelectionCriteria selectionCriteria)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::CheckFeasiblityOfRules Entry");
    int retVal = ITS_SUCCESS;
    bool isSelectionCriteriaFeasible = false;
    uint32_t range = 0;

    for (Routes::iterator routesIter = m_routes.begin(); routesIter != m_routes.end(); routesIter++)
    {
        IwfRoute* iwfRoute = routesIter->second;
        isSelectionCriteriaFeasible = IsSelectionCriteriaFeasibleForRule(iwfRoute, selectionCriteria);

        if(isSelectionCriteriaFeasible)
        {
            uint32_t l_routingKey = IwfRoute::MakeKey(iwfRoute->MCC(), iwfRoute->MNC(), iwfRoute->AppId(),
                    atoll(iwfRoute->ServiceKeyStart().c_str()), iwfRoute->CallingGtAddrDigits(), selectionCriteria);
            LocalRoutes::iterator it = l_routes.find(l_routingKey);
            if( it != l_routes.end() )
            {
                //CleanLocalMap(__LINE__);
                DLOG_ERROR("RoutingKey already present, Rule cannot be modified");
                return !ITS_SUCCESS;
            }
            else
            {
                std::auto_ptr<IwfRoute> route(new IwfRoute());
                route->SetParameter(iwfRoute);
                if((selectionCriteria == SELECT_SK || selectionCriteria == SELECT_SK_AND_MCC_MNC || selectionCriteria == SELECT_CLG_GTT_ADDR_DGTS_AND_SK) &&
                        route->IsServiceKeyInRange())
                {
                    for(range = atoll(route->ServiceKeyStart().c_str()); range <= atoll(route->ServiceKeyEnd().c_str()); range++)
                    {
                        uint64_t routingKey = IwfRoute::MakeKey(route->MCC(), route->MNC(), route->AppId(), range, route->CallingGtAddrDigits(),
                                selectionCriteria);
                        if(routingKey == -1)
                        {
                            CleanLocalMap(__LINE__);
                            DLOG_ERROR("Invalid SelectionCriteria Configured");
                            return !ITS_SUCCESS;
                        }
                        else
                        {
                            DLOG_DEBUG("Routing Key = %d",routingKey);
                            l_routes[routingKey] = route.get();
                        }
                    }
                }
                else
                {
                    uint64_t routingKey = IwfRoute::MakeKey(route->MCC(), route->MNC(), route->AppId(), atoll(route->ServiceKeyStart().c_str()),
                            route->CallingGtAddrDigits(), selectionCriteria);
                    if(routingKey == -1)
                    {
                        CleanLocalMap(__LINE__);
                        DLOG_ERROR("Invalid SelectionCriteria Configured");
                        return !ITS_SUCCESS;
                    }
                    else
                    {
                        DLOG_DEBUG("Routing Key = %d",routingKey);
                        l_routes[routingKey] = route.get();
                    }
                }

                // IwfRoute* is now managed by l_routes, don't free auto_ptr
                route.release();
            }
        }
        else
        {
            DLOG_ERROR("Selection Criteria feasibility failed for Rule ..");
            return !ITS_SUCCESS;
        }
    }
    DLOG_DEBUG("IwfRoutingRules::CheckFeasiblityOfRules Exit");
    return retVal;
}

void IwfRoutingRules::CleanLocalMap(int lineno)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::CleanLocalMap Entry called from %d",lineno);
    for(LocalRoutes::iterator it = l_routes.begin(); it != l_routes.end();)
    {
        DLOG_DEBUG("Address of it->second %p", it->second);
        delete it->second;
        l_routes.erase(it++);
    }
    DLOG_DEBUG("IwfRoutingRules::CleanLocalMap Exit");
}

void IwfRoutingRules::UpdateRoutingRuleMap()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::UpdateRoutingRuleMap Entry");
    for(Routes::iterator it = m_routes.begin(); it != m_routes.end();)
    {
        delete it->second;
        m_routes.erase(it++);
    }

    m_routes.insert(l_routes.begin(), l_routes.end());
    DLOG_DEBUG("IwfRoutingRules::UpdateRoutingRuleMap Exit");
}

bool IwfRoutingRules::IsSelectionCriteriaFeasibleForRule(IwfRoute *iwfRoute, SelectionCriteria selectionCriteria)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::IsSelectionCriteriaFeasibleForRule Entry");
    bool isSelectionCriteriaFeasible = false;

    switch(selectionCriteria)
    {
        case SELECT_MCC_MNC:
            {
                if(!iwfRoute->MCC().empty() && !iwfRoute->MNC().empty() && !iwfRoute->AppId().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS:
            {
                if(!iwfRoute->CallingGtAddrDigits().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC:
            {
                if(!iwfRoute->MCC().empty() && !iwfRoute->MNC().empty() && !iwfRoute->CallingGtAddrDigits().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        case SELECT_SK:
            {
                if(!iwfRoute->ServiceKeyStart().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        case SELECT_SK_AND_MCC_MNC:
            {
                if(!iwfRoute->MCC().empty() && !iwfRoute->MNC().empty() && !iwfRoute->ServiceKeyStart().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS_AND_SK:
            {
                if(!iwfRoute->ServiceKeyStart().empty() && !iwfRoute->CallingGtAddrDigits().empty())
                {
                    isSelectionCriteriaFeasible = true;
                }
                break;
            }
        default:
            {
                DLOG_ERROR("Invalid SelectionCriteria Configured");
            }
    }
    DLOG_DEBUG("IwfRoutingRules::IsSelectionCriteriaFeasibleForRule Exit");
    return isSelectionCriteriaFeasible;
}

#endif
// Destinations
IwfDestinations::IwfDestinations()
{
}

IwfDestinations::~IwfDestinations()
{
    for (DestMap::iterator it = m_destinations.begin();
            it != m_destinations.end();)
    {
        delete it->second;
        m_destinations.erase(it++);
    }
}

void IwfDestinations::Parse(const Json::Value& val, IwfConfig& conf)
{
    /*Json::Value entry = val["sccp"];
      if (entry.empty())
      {
      throw IwfConfigException("'sccp' entry missing in destinations");
      }
      for (unsigned i = 0; i < entry.size(); i++)
      {
      std::auto_ptr<IwfDest> dest(new IwfDest();
      dest->Parse(entry[i], conf);

      m_destinations[dest->Name()] = dest.get();
      std::stringstream str;
      str << dest->PointCode();
      m_PointCodeToNameMap[str.str()] = dest.get();
      dest.release();
      }*/
}

int IwfDestinations::SetIwfDestinationConfig(IwfSigtranDestinationConfig* dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("IwfDestinations::SetIwfDestionConfig Entry");
    if( dest->IsInitialized() )
    {
        std::auto_ptr<IwfDest> destInfo(new IwfDest());
        destInfo->SetParameters(dest);

        DLOG_DEBUG("Destination Name : %s",destInfo->Name().c_str());
        m_destinations[destInfo->Name()] = destInfo.get();
        std::stringstream str;
        str << destInfo->PointCode();
        DLOG_DEBUG("Destination PointCode : %s",str.str().c_str());
        m_PointCodeToNameMap[str.str()] = destInfo.get();
        destInfo.release();
        DLOG_DEBUG("m_destinations.size() : %d",m_destinations.size());
    }
    else
    {
        DLOG_ERROR("Error destination info not initialized");
        retVal = CMAPI_INVALIDPARAMS;
    }
    DLOG_DEBUG("IwfDestinations::SetIwfDestionConfig Exit");
    return retVal;
}

int IwfDestinations::ModifyIwfDestinationConfig(IwfSigtranDestinationConfig* dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("IwfDestinations::ModifyIwfDestionConfig Entry");
    if( dest->IsInitialized() )
    {
        if( dest->has_pointcode() && dest->has_destinationname() )
        {
            DLOG_DEBUG("received destination name : %s and pointcode : %d",
                    dest->destinationname().c_str(),dest->pointcode());
            DestMap::iterator it = m_destinations.find(dest->destinationname());
            if( it != m_destinations.end() )
            {
                IwfDest *destInfo = it->second;

                destInfo->SetParameters(dest);
                m_destinations[destInfo->Name()] = destInfo;

                std::stringstream str;
                str << dest->pointcode();
                PCMap::iterator pcIt = m_PointCodeToNameMap.find(str.str());
                if( pcIt != m_PointCodeToNameMap.end() )
                {
                    m_PointCodeToNameMap[str.str()] = destInfo;
                }
            }
            else
            {
                DLOG_DEBUG("Cannot find the Destination Info for dest : %s \
                        and pointCode : %d",dest->destinationname().c_str(),
                        dest->pointcode());
                DLOG_DEBUG("Hence adding the new Destination for RemoteRoute");
                retVal = SetIwfDestinationConfig(dest);
            }
        }
        else
        {
            DLOG_ERROR("Missing mandatory parameter pointcode/destination name");
            retVal = MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT;
        }
    }
    else
    {
        DLOG_ERROR("Error Destination Info not initialized");
        retVal = CMAPI_INVALIDPARAMS;
    }
    DLOG_DEBUG("IwfDestinations::ModifyIwfDestionConfig Exit");
    return retVal;
}

int IwfDestinations::DeleteIwfDestinationConfig(IwfSigtranDestinationConfig* dest)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    DLOG_DEBUG("IwfDestinations::DeleteIwfDestionConfig Entry");
    if( dest->IsInitialized() )
    {
        if( dest->has_pointcode() && dest->has_destinationname() )
        {
            DLOG_DEBUG("received destination name : %s and pointcode : %d",
                    dest->destinationname().c_str(),dest->pointcode());
            DestMap::iterator it = m_destinations.find(dest->destinationname());
            if( it != m_destinations.end() )
            {
                m_destinations.erase(it);

                std::stringstream str;
                str << dest->pointcode();
                PCMap::iterator pcIt = m_PointCodeToNameMap.find(str.str());
                if( pcIt != m_PointCodeToNameMap.end() )
                {
                    m_PointCodeToNameMap.erase(pcIt);
                }
            }
            else
            {
                DLOG_ERROR("Cannot find the Destination Info for dest : %s \
                        and pointCode : %d",dest->destinationname().c_str(),
                        dest->pointcode());
                retVal = MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT;
            }
        }
        else
        {
            DLOG_ERROR("Missing mandatory parameter pointcode/destination name");
            retVal = MOD_ROUTE_ERR_DESTINATION_NOT_PRESENT;
        }
    }
    else
    {
        DLOG_ERROR("Error Destination Info not initialized");
        retVal = CMAPI_INVALIDPARAMS;
    }
    DLOG_DEBUG("IwfDestinations::DeleteIwfDestionConfig Exit");

    return retVal;
}


int IwfE164NumberRange::Parse(const Json::Value& val, IwfConfig& conf)
{
    Json::Value entry = val["startNumber"];
    if(entry.empty())
    {
        throw IwfConfigException("'startNumber' entry missing in destinations");
    }

    m_iE164Start = entry.asUInt64();

    entry = val["endNumber"];
    if(entry.empty())
    {
        throw IwfConfigException("'endNumber' entry missing in destinations");
    }

    m_iE164End = entry.asInt();

    return 0;
}

int IwfInvokeId::Parse(const Json::Value& val, IwfConfig& conf)
{

    m_useFromConfig = val.get("use-from-config", false).asBool();

    m_startIdForEachDialog = val.get("start-id-for-each-dialog", IWF_START_INVOKE_ID_DEFAULT).asUInt();

    return 0;
}

int IwfSelfSccpAddress::Parse(const Json::Value& val, IwfConfig& conf)
{

    /*m_useFromConfig = val.get("use-from-config", false).asBool();

      Json::Value entry = val["gtdigits"];
      if (!entry.empty())
      {
      m_gtDigits = entry.asString();
      }*/

    return 0;
}

int IwfRemoteSccpAddress::Parse(const Json::Value& val, IwfConfig& conf)
{

    m_useFromConfig = val.get("use-from-config", false).asBool();

    Json::Value entry = val["gtdigits"];
    if (!entry.empty())
    {
        m_gtDigits = entry.asString();
    }

    return 0;
}

//
// root config
//
    IwfConfig::IwfConfig(const char* configFile, IwfCTrieImpl* pTrieIntf)
: m_configFileName(configFile),
  m_transRules(pTrieIntf)
{
}

IwfConfig::~IwfConfig()
{
}

int IwfConfig::ParseConfig()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    Json::Reader reader;
    Json::Value root, entry;
    int ret = ITS_SUCCESS;

    try
    {
        if (m_configFileName.empty())
        {
            throw IwfConfigException("Config File not specified");
        }

        std::ifstream doc(m_configFileName.c_str());
        bool res = reader.parse(doc, root);
        if (!res)
        {
            std::stringstream sstr;
            sstr << "Json parsing failed <" <<
                reader.getFormattedErrorMessages() << ">";
            throw IwfConfigException(sstr.str());
        }

        entry = root["local"];
        if (entry.empty())
        {
            throw IwfConfigException("'local' config missing");
        }
        m_localConfig.Parse(entry, *this);

        // parse destinations before routing-rules, because routing-rules refer
        // to destination entries
        entry = root["destinations"];
        if (entry.empty())
        {
            throw IwfConfigException("No 'destinations' in config");
        }
        m_destinations.Parse(entry, *this);

        entry = root["routing-rules"];
        if (entry.empty())
        {
            throw IwfConfigException("No 'routing-rules' in config");
        }
        m_routingRules.Parse(entry, *this);

        m_protoConvertor = root["proto-translator"];
        if (m_protoConvertor.empty())
        {
            throw IwfConfigException("No 'proto-translator' in config");
        }
#if 0
        // for each registered translator, invoke the ParseConfig function
        IwfTranslator* transl;
        IwfController& ctrl = IwfController::Instance();
        for (IwfController::TranslStrMap::iterator it = ctrl.m_translStrMap.begin();
                it != ctrl.m_translStrMap.end(); it++)
        {
            entry = m_protoConvertor[it->first];
            transl = ctrl.GetTranslator(it->second);
            if (transl)
            {
                transl->ParseConfig(entry, *this);
            }
        }
#endif
        entry = root["cdr-config"];
        if (!entry.empty())
        {
            unsigned maxRecs = entry.get("max-records-per-file",
                                IwfCDRConfig::MAX_REC_PER_FILE).asInt();
            m_cdrConfig.SetMaxRecsPerFile(maxRecs);

            Json::Value frmt = entry["format"];
            std::string format = frmt.asString();
            if(format.compare("csv") == 0)
            {
                m_cdrConfig.SetCdrInCsvFormat();
                Json::Value fs = entry["field-separator"];
                std::string fSep = fs.asString();
                if(fSep.size() == 1)
                {
                    m_cdrConfig.SetFieldSeparator(fSep.c_str());
                }
                else
                {
                    throw IwfConfigException("Invalid 'field-separator' in config");
                }
            }
            else if(format.compare("json") == 0)
            {
                m_cdrConfig.SetCdrInJsonFormat();
            }
            else
            {
                throw IwfConfigException("No/Invalid 'cdr-format' in config");
            }
        }

        entry = root["dcca"];
        if (!entry.empty())
        {
            DLOG_DEBUG("configuring DCCA");
            IwfDCCAConfig& dccaConfig = this->DCCAConfig();
            dccaConfig.Configure(entry);
        }
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Parse IWF configuration failed. Reason: %s", exp.what());
        ret = -1;
    }
    catch(...)
    {
        DLOG_ERROR("Parse IWF configuration failed. Unknown reason!");
        ret = -1;
    }

    return ret;
}

int IwfConfig::ParseTranslatorConfig()
{
    Json::Reader reader;
    Json::Value root, entry;
    int ret = ITS_SUCCESS;

    try
    {
        if (m_configFileName.empty())
        {
            throw IwfConfigException("Config File not specified");
        }

        std::ifstream doc(m_configFileName.c_str());
        bool res = reader.parse(doc, root);
        if (!res)
        {
            std::stringstream sstr;
            sstr << "Json parsing failed <" <<
                reader.getFormattedErrorMessages() << ">";
            throw IwfConfigException(sstr.str());
        }

        ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
        int ret = ITS_SUCCESS;
        // for each registered translator, invoke the ParseConfig function
        IwfTranslator* transl;
        IwfController& ctrl = IwfController::Instance();
        for (IwfController::TranslStrMap::iterator it = ctrl.m_translStrMap.begin();
                it != ctrl.m_translStrMap.end(); it++)
        {
            entry = m_protoConvertor[it->first];
            transl = ctrl.GetTranslator(it->second);
            if (transl)
            {
                transl->ParseConfig(entry, *this);
            }
        }
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Parse IWF Translator configuration failed. Reason: %s", exp.what());
        ret = -1;
    }
    catch(...)
    {
        DLOG_ERROR("Parse IWF Translator configuration failed. Unknown reason!");
        ret = -1;
    }
    return ret;
}

int IwfConfig::SearchServiceKey(string& RuleId, int32_t& serviceKeyVal)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = !ITS_SUCCESS;
    RuleNameVsSKList::iterator itr = m_mapRuleNameVsSKList.find(RuleId);

    if(itr != m_mapRuleNameVsSKList.end())
    {
        DLOG_DEBUG("Found RuleId : %s, searching ServiceKey : %d", RuleId.c_str(), serviceKeyVal);
        TSKList sklist;
        sklist = itr->second;
        for(unsigned int i = 0; i < sklist.size(); i++)
        {
            if(sklist[i].low == -42)
            {
               DLOG_DEBUG("Servicekey %d, matched in skList[%u].*.",serviceKeyVal,i);
               ret = ITS_SUCCESS;
               break;
            }
            if(sklist[i].high == -1)    //servicekey is as single value
            {
                if(sklist[i].low == serviceKeyVal)
                {
                    DLOG_DEBUG("Servicekey %d, matched in skList[%u].%d.",serviceKeyVal,i,sklist[i].low);
                    ret = ITS_SUCCESS;
                    break;
                }
                else
                    DLOG_DEBUG("Servicekey %d, not matched in skList[%u].%d.",serviceKeyVal,i, sklist[i].low);
            }
            else                        //servicekey values is range
            {
               if(serviceKeyVal <= sklist[i].high && serviceKeyVal >= sklist[i].low)
               {
                  DLOG_DEBUG("Servicekey : %d, found in range skList[%u].%d - skList[%u].%d.",serviceKeyVal,i, sklist[i].low,i, sklist[i].high);
                  ret = ITS_SUCCESS;
                  break;
               }
               else
                  DLOG_DEBUG("Servicekey : %d, not found in range skList[%u].%d - skList[%u].%d.",serviceKeyVal,i, sklist[i].low,i, sklist[i].high);
            }
        }

    }
    else
    {
        DLOG_DEBUG("Not Found RuleId : %s.", RuleId.c_str());
    }
    return ret;
}
void IwfConfig::InsertImsiPrefixVsRuleInMAP(std::string ImsiPrefix, std::string RuleName)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    std::pair<string,string> ruleimsiPrefixPair(ImsiPrefix, RuleName);
    std::pair<std::map<string,string>::iterator, bool> ret;
    string ruleName;
    ret = m_mapImsiPrefixVsRule.insert(ruleimsiPrefixPair);
    if(false == ret.second)
    {
        ruleName = ret.first->second;
        ruleName.append(",");
        ruleName.append(RuleName);
        std::map<string,string>::iterator itr;
        itr = m_mapImsiPrefixVsRule.find(ImsiPrefix);
        if(itr != m_mapImsiPrefixVsRule.end())
        {
            m_mapImsiPrefixVsRule.erase(itr);
        }
        ret = m_mapImsiPrefixVsRule.insert(std::pair<string,string> (ImsiPrefix, ruleName));
        if(true == ret.second)
        {
            DLOG_DEBUG("Inserted ImsiPrefix : %s, RuleName : %s",ImsiPrefix.c_str(),ruleName.c_str());
        }
        else
        {
            DLOG_DEBUG("failed to re-Insert ImsiPrefix : %s, RuleName : %s",ImsiPrefix.c_str(),ruleName.c_str());
        }
    }

}

IwfHssToSgsnCache::IwfHssToSgsnCache()
{
    m_iFreeIndex = 0;
}

IwfHssToSgsnCache::~IwfHssToSgsnCache()
{
}

IwfE164NumberRange::IwfE164NumberRange()
{
    m_iE164Start = 0;
    m_iE164End = 0;
}

IwfE164NumberRange::~IwfE164NumberRange()
{
}

IwfInvokeId::IwfInvokeId()
{
}

IwfInvokeId::~IwfInvokeId()
{
}

IwfSelfSccpAddress::IwfSelfSccpAddress():m_useFromConfig(true),m_pcIndicator(false)
{
}

IwfSelfSccpAddress::~IwfSelfSccpAddress()
{
}

IwfRemoteSccpAddress::IwfRemoteSccpAddress()
{
}

IwfRemoteSccpAddress::~IwfRemoteSccpAddress()
{
}

int IwfHssToSgsnCache::addElement(std::string strOrigHost, SHssWatcherInfo osWatcherInfo)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    if ((itrMap == m_mapHssToWatcherInfo.end()) && (strOrigHost.size() > 0))
    {
        m_mapHssToWatcherInfo[strOrigHost] = osWatcherInfo;
        return 0;
    }

    return -1;
}

int IwfHssToSgsnCache::isSgsnPresent(std::string strOrigHost, ITS_UINT pointCode)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    bool sgsnPresent = false;
    if (itrMap == m_mapHssToWatcherInfo.end() || (strOrigHost.size() == 0))
    {
        return true;
    }

    SHssWatcherInfo osWatcherInfo = itrMap->second;
    if(!osWatcherInfo.m_vecSgsn.empty())
    {
        for(unsigned int iIndex = 0;iIndex < osWatcherInfo.m_vecSgsn.size(); iIndex++)
        {
            if(osWatcherInfo.m_vecSgsn[iIndex].m_opc == pointCode)
            {
                sgsnPresent = true;
                break;
            }
        }
    }
    return sgsnPresent;
}

int IwfHssToSgsnCache::addSgsn(std::string strOrigHost, SCCPParameters sccpParam)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    bool sgsnPresent = false;
    if (itrMap == m_mapHssToWatcherInfo.end() || (strOrigHost.size() == 0))
    {
        return -1;
    }

    SHssWatcherInfo osWatcherInfo = itrMap->second;
    if(!osWatcherInfo.m_vecSgsn.empty())
    {
        for(unsigned int iIndex = 0;iIndex < osWatcherInfo.m_vecSgsn.size(); iIndex++)
        {
            if(osWatcherInfo.m_vecSgsn[iIndex].m_opc == sccpParam.m_opc)
            {
                sgsnPresent = true;
                break;
            }
        }
    }
    /* if sgsn already present dont add again entry into map */
    if(!sgsnPresent)
    {
        osWatcherInfo.m_vecSgsn.push_back(sccpParam);
        m_mapHssToWatcherInfo[strOrigHost] = osWatcherInfo;
    }
    return 0;
}

int IwfHssToSgsnCache::delElement(std::string strOrigHost)
{
    return 0;
}

std::vector<SCCPParameters> IwfHssToSgsnCache::getSgsnListForHss(std::string strOrigHost)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    SHssWatcherInfo osWatcherInfo;
    if ((itrMap != m_mapHssToWatcherInfo.end()) && (strOrigHost.size() > 0))
    {
        osWatcherInfo = itrMap->second;
    }
    return osWatcherInfo.m_vecSgsn;
}

void IwfHssToSgsnCache::getSgsnListForHss(std::string strOrigHost,std::vector<SCCPParameters>& sgsn)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    if ((itrMap != m_mapHssToWatcherInfo.end()) && (strOrigHost.size() > 0))
    {
        SHssWatcherInfo osWatcherInfo = itrMap->second;
        sgsn = osWatcherInfo.m_vecSgsn;
    }
}

bool IwfHssToSgsnCache::isEntryPresentFor(std::string strOrigHost)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    if ((itrMap == m_mapHssToWatcherInfo.end()) && (strOrigHost.size() > 0))
    {
        return false;
    }

    return true;
}

std::string IwfHssToSgsnCache::allocE164Num()
{
    std::ostringstream strStream;
    uint64_t uiNum = m_vecE164NumPool[m_iFreeIndex++];
    strStream << uiNum;
    return std::string(strStream.str());
}

std::string IwfHssToSgsnCache::getHssNumber(std::string strOrigHost)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    if ((itrMap == m_mapHssToWatcherInfo.end()) || (strOrigHost.size() == 0))
    {
        return std::string();
    }

    SHssWatcherInfo osWatcherInfo = itrMap->second;
    return osWatcherInfo.m_strHssNumber;
}

SHssWatcherInfo IwfHssToSgsnCache::getHssWatcherInfo(std::string strOrigHost)
{
    std::map<std::string, SHssWatcherInfo>::iterator itrMap =  m_mapHssToWatcherInfo.find(strOrigHost);
    SHssWatcherInfo osWatcherInfo;
    if ((itrMap != m_mapHssToWatcherInfo.end()) && (strOrigHost.size() > 0))
    {
        osWatcherInfo = itrMap->second;
    }
    return osWatcherInfo;
}

bool IwfDCCAEndpointsConf::AddEndpoint(
            const std::string& endpointName, 
            uint32_t priority,
            bool sendCCRTFlag)
{
    EndpointsList::iterator it = std::find(m_endpoints.begin(), m_endpoints.end(),
                                    IwfDCCAEndpointConf(endpointName, 0));
    if (it != m_endpoints.end())
    {
        // Duplicate entry
        DLOG_ERROR("Duplicate entry while adding endpoint %s to %s",
                   endpointName.c_str(), m_destination.c_str());
        return false;
    }

    // Add it to the end and sort
    m_endpoints.push_back(IwfDCCAEndpointConf(endpointName, priority));
    m_endpoints.sort();
    SetCCRTFlag(sendCCRTFlag);

    DLOG_DEBUG("Successfully added endpoint %s to %s",
                   endpointName.c_str(), m_destination.c_str());

    return true;
}

bool IwfDCCAEndpointsConf::RemoveEndpoint(const std::string& endpointName, uint32_t priority)
{
    EndpointsList::iterator it = std::find(m_endpoints.begin(), m_endpoints.end(),
                                    IwfDCCAEndpointConf(endpointName, priority));
    if(it == m_endpoints.end())
    {
        DLOG_ERROR("Failed to find entry in the list for endPoint : %s, priority : %d",
                endpointName.c_str(), priority);
        return false;
    }
    m_endpoints.remove(IwfDCCAEndpointConf(endpointName, priority));
    DLOG_DEBUG("Successfully removed endpoint %s to %s",
            endpointName.c_str(), m_destination.c_str());
    return true;
}

bool IwfDCCADestinations::AddEndpoint(const std::string& destName,
                        const std::string& endpointName,
                        uint32_t priority,
                        bool sendCCRTFlg)
{
    DestMap::iterator it = m_destinations.find(destName);
    if (it == m_destinations.end())
    {
        // Entry not found. Create a new Endpoint group
        std::pair<DestMap::iterator, bool> ret;
        ret = m_destinations.insert(std::make_pair(destName,
                                    IwfDCCAEndpointsConf(destName)));
        if (ret.second == false)
        {
            // Not added
            DLOG_ERROR("Add Destination insertion failed <%s : %s>",
                destName.c_str(), endpointName.c_str());
            return false;
        }
        it = ret.first;
    }

    bool res = it->second.AddEndpoint(endpointName, priority,sendCCRTFlg);

    return res;
}

bool IwfDCCADestinations::RemoveEndpoint(const std::string& destName,
                            const std::string& endpointName,
                            uint32_t priority)
{
    DestMap::iterator it = m_destinations.find(destName);
    if (it == m_destinations.end())
    {
        DLOG_ERROR("Destination %s not found. Remove endpoint %s failed",
                   destName.c_str(), endpointName.c_str());
        return false;
    }

    bool ret = it->second.RemoveEndpoint(endpointName,priority);

    return ret;
}

bool IwfDCCADestinations::RemoveDestination(const std::string& destName)
{
    int ret = m_destinations.erase(destName);
    if (ret == 0)
    {
        DLOG_WARNING("Destination %s not found. RemoveDestination failed",destName.c_str());
        return false;
    }
    DLOG_DEBUG("Destination %s removed from DCCA Config",destName.c_str());
    return true;
}

IwfDCCAEndpointsConf* IwfDCCADestinations::LookupEndpointsConf(
                            const std::string& destName)
{
    DestMap::iterator it = m_destinations.find(destName);
    if (it == m_destinations.end())
    {
        return NULL;
    }
    return &(it->second);
}

void IwfDCCAConfig::SetTxTimeout(uint32_t timeoutSecs)
{
    m_txTimeout = timeoutSecs;
    if (itsDiaConfig.GetDccaFeature() != NULL)
    {
        DCCAConf::GetDCCAConf()->SetConf(DCCA_CONF_TX_TIMER, m_txTimeout);
    }
}

void IwfDCCAConfig::SetInitialCCFHAction(IwfCCFHAction action)
{
    m_ccfhInitialAction = action;
    if (itsDiaConfig.GetDccaFeature() != NULL)
    {
        DCCAConf::GetDCCAConf()->SetConf(DCCA_CONF_CCFH, m_txTimeout);
    }
}

void IwfDCCAConfig::SetUpdateCCFHAction(IwfCCFHAction action)
{
    m_ccfhUpdateAction = action;
    // There is no equivalent for this in DCCA. TODO add the same to DCCA
}

IwfCCFHAction IwfDCCAConfig::GetCCFHAction(const std::string& actionStr)
{
    IwfCCFHAction ret = IWF_CCFH_ACTION_TERMINATE;
    if (actionStr.compare("retry-and-terminate") == 0)
    {
        ret = IWF_CCFH_ACTION_RETRY_TERMINATE;
    }
    else if (actionStr.compare("terminate") == 0)
    {
        ret = IWF_CCFH_ACTION_TERMINATE;
    }
    // continue is not handled currently. It is treated like terminate.

    return ret;
}

void IwfDCCAConfig::Configure(Json::Value& dcca)
{
    uint32_t txTimeout = dcca.get("tx-timeout", IWF_DEFAULT_TX_TIMEOUT).asInt();
    this->SetTxTimeout(txTimeout);

    Json::Value entry = dcca["failure-handling"];
    if (!entry.empty())
    {
        std::string actionStr = entry.get("initial-action", "retry-and-terminate").asString();
        this->SetInitialCCFHAction(this->GetCCFHAction(actionStr));

        actionStr = entry.get("update-action", "retry-and-terminate").asString();
        this->SetUpdateCCFHAction(this->GetCCFHAction(actionStr));
    }

    entry = dcca["destinations"];
    if (!entry.empty())
    {
        for (Json::Value::iterator it = entry.begin();
             it != entry.end(); it++)
        {
            std::string realm = (*it)["realm"].asString();
            Json::Value endpoints = (*it)["endpoints"];
            for (Json::Value::iterator ep = endpoints.begin();
                 ep != endpoints.end(); ep++)
            {
                this->GetDestinations().AddEndpoint(realm,
                        (*ep)["endpoint"].asString(),
                        (*ep).get("priority", 1).asInt(),
                        true);
            }
        }
    }
    entry = dcca["set-tbit-on-retry"];
    if (!entry.empty())
    {
        DLOG_DEBUG("DCCA set T-Bit on retry : %d",entry.asBool());
        m_setTbitOnRetry = entry.asBool();
    }
}

int IwfProtActionCfg::SetProtActionConfig(IwfProtocolActionsConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int protActionCfgNum = 0;
    IwfProtocolActionConfig protActionCfgInst;

    protActionCfgNum = req->iwfprotactioncfgval_size();

    try
    {
        if(protActionCfgNum > 0)
        {
            for(int idx = 0 ; idx < protActionCfgNum ; idx++)
            {
                protActionCfgInst = req->iwfprotactioncfgval(idx);
                if(protActionCfgInst.has_protocol() && protActionCfgInst.has_actionid() && protActionCfgInst.has_actionrulename()) //&& protActionCfgInst.has_msgdetval())
                {
                    string protName = protActionCfgInst.protocol();
                    if("CAP" == protName)
                    {
                        IwfTranslator* CapToRoTsl = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);

                        if((retVal == CapToRoTsl->SetMsgSpecCfg(&protActionCfgInst)) == CMAPI_SUCCESS)
                        {
                            DLOG_DEBUG("Successfully configured ProtActionCfg for TransatelCAPToRo transalator");
                        }
                    }

                }
                else
                {
                    DLOG_ERROR("Missing mandatory parameter for ProtActionConfig configurations(Protocol/ActionRuleName/ActionId)");
                    retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_MANDATORY_PARAM_MISSING;
                }

            }
        }
        else
        {
            DLOG_ERROR("IwfProtActionCfg::SetProtActionConfig no ProtActionConfig data present");
            retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
        }


    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Add IWF translator configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("IwfRoutingRules::SetRoutingRulesConfig no Translator Rule data present");
        retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfRoutingRules::SetProtActionConfig Exit");
    return retVal;

}

int IwfProtActionCfg::ModifyProtActionConfig(IwfProtocolActionsConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("IwfRoutingRules::ModifyProtActionConfig Exit");
    int retVal = CMAPI_SUCCESS;
    int protActionCfgNum = 0;
    IwfProtocolActionConfig protActionCfgInst;

    protActionCfgNum = req->iwfprotactioncfgval_size();

    try
    {
        if(protActionCfgNum > 0)
        {
            for(int idx = 0 ; idx < protActionCfgNum ; idx++)
            {
                protActionCfgInst = req->iwfprotactioncfgval(idx);
                if(protActionCfgInst.has_protocol() && protActionCfgInst.has_actionid() && protActionCfgInst.has_actionrulename()) //&& protActionCfgInst.has_msgdetval())
                {
                    string protName = protActionCfgInst.protocol();
                    if("CAP" == protName)
                    {
                        IwfTranslator* CapToRoTsl = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                        //Delete the Rule from Map and Add a new Rule
                        if((retVal == CapToRoTsl->DeleteMsgSpecCfg(&protActionCfgInst)) == CMAPI_SUCCESS)
                        {
                            DLOG_DEBUG("Successfully deleted ProtActionCfg for TransatelCAPToRo transalator");
                        }
                        if((retVal == CapToRoTsl->SetMsgSpecCfg(&protActionCfgInst)) == CMAPI_SUCCESS)
                        {
                            DLOG_DEBUG("Successfully configured ProtActionCfg for TransatelCAPToRo transalator");
                        }
                    }
                }
                else
                {
                    DLOG_ERROR("Missing mandatory parameter for ProtActionConfig configurations(Protocol/ActionRuleName/ActionId)");
                    retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_MANDATORY_PARAM_MISSING;
                }

            }
        }
        else
        {
            DLOG_ERROR("IwfProtActionCfg::ModifyProtActionConfig no ProtActionConfig data present");
            retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
        }


    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Add IWF protocolActions configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("IwfRoutingRules::ModifyRoutingRulesConfig no Translator Rule data present");
        retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfRoutingRules::ModifyProtActionConfig Exit");
    return retVal;

}

int IwfProtActionCfg::DeleteProtActionConfig(IwfProtocolActionsConfig *req)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int retVal = CMAPI_SUCCESS;
    int protActionCfgNum = 0;
    IwfProtocolActionConfig protActionCfgInst;

    protActionCfgNum = req->iwfprotactioncfgval_size();

    try
    {
        if(protActionCfgNum > 0)
        {
            for(int idx = 0 ; idx < protActionCfgNum ; idx++)
            {
                protActionCfgInst = req->iwfprotactioncfgval(idx);
                if(protActionCfgInst.has_protocol() && protActionCfgInst.has_actionid() && protActionCfgInst.has_actionrulename()) //&& protActionCfgInst.has_msgdetval())
                {
                    string protName = protActionCfgInst.protocol();
                    if("CAP" == protName)
                    {
                        IwfTranslator* CapToRoTsl = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                        //Delete the Rule from Map and Add a new Rule
                        if((retVal == CapToRoTsl->DeleteMsgSpecCfg(&protActionCfgInst)) == CMAPI_SUCCESS)
                        {
                            DLOG_DEBUG("Successfully deleted ProtActionCfg for TransatelCAPToRo transalator");
                        }
                        if(req->operreqid() != DEL_IWF_PROT_ACTIONS)
                        {
                            if((retVal == CapToRoTsl->SetMsgSpecCfg(&protActionCfgInst)) == CMAPI_SUCCESS)
                            {
                                DLOG_DEBUG("Successfully configured ProtActionCfg for TransatelCAPToRo transalator");
                            }
                        }
                    }

                }
                else
                {
                    DLOG_ERROR("Missing mandatory parameter for ProtActionConfig configurations(Protocol/ActionRuleName/ActionId)");
                    retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_MANDATORY_PARAM_MISSING;
                }

            }
        }
        else
        {
            DLOG_ERROR("IwfProtActionCfg::DeleteProtActionConfig no ProtActionConfig data present");
            retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
        }
    }
    catch(std::exception& exp)
    {
        DLOG_ERROR("Delete IwfProtocolActions configuration failed. Reason: %s", exp.what());
        retVal = CMAPI_SRVERROR;
    }
    catch(...)
    {
        DLOG_ERROR("IwfProtActionCfg::DeleteProtActionConfig no Translator Rule data present");
        retVal = ADD_PROTOCOL_ACTION_ERR_PROTACTCFG_NOT_PRESENT;
    }
    DLOG_DEBUG("IwfProtActionCfg::DeleteProtActionConfig Exit");
    return retVal;

}

