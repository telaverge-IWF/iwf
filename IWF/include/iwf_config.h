/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
#ifndef __IWF_CONFIG_H__
#define __IWF_CONFIG_H__

#include <json/json.h>
#include <exception>
#include <stdint.h>
#include <map>
#include <memory>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "iwf_prot_defines.h"
#include <Ref.h>
#include <list>

#include "IwfCAhoCorasickImpl.h"



#define IWF_TIMER_IVK_DEFAULT  30   // Invoke timer default val in secs

#define IWF_START_INVOKE_ID_DEFAULT 0   // TCAP start invoke id for each dialog

#define IWF_CONFIG_DEFAULT_FILE "iwf.json"
#define IWF_SIGTRAN_LOG_DEFAULT_FILE "iwf_sigtran.log"

#define IWF_NUM_SLS SLS_8BIT_ARRAY_SIZE  //Sequence control parameter is 1 byte in SCCP irrespective of ANSI and ITU so no change would require even at ITU support.

#define SS7_STRING "SS7"
#define DIAMETER_STRING "DIAMETER"
#define HTTP_STRING "HTTP"

int instanceId = 0;
enum IwfAddrType
{
    IWF_ADDR_PCSSN,
    IWF_ADDR_GT
};

class IwfConfigException: public std::exception
{
    public:
        IwfConfigException(const std::string& str)
            : m_str(str)
        {
        }
        virtual ~IwfConfigException() throw()
        {
        }

        virtual const char* what() const throw()
        {
            return m_str.c_str();
        }
    protected:
        std::string m_str;
};

class IwfConfig;

class IwfInvokeId
{
    public:
        IwfInvokeId();
        ~IwfInvokeId();

        int Parse(const Json::Value& val, IwfConfig& conf);

        const bool& IsUseFromConfig() const
        {
            return m_useFromConfig;
        }

        const unsigned& StartIdForEachDialog() const
        {
            return m_startIdForEachDialog;
        }

    private:
        bool m_useFromConfig;
        unsigned m_startIdForEachDialog;

};

class IwfSelfSccpAddress
{
    public:
        IwfSelfSccpAddress();
        ~IwfSelfSccpAddress();

        int Parse(const Json::Value& val, IwfConfig& conf);

        void SetUseFromConfig(bool useFromConfig)
        {
            m_useFromConfig = useFromConfig;
        }

        const bool& IsUseFromConfig() const
        {
            return m_useFromConfig;
        }

        void SetGtDigits(std::string gtdigits)
        {
            m_gtDigits = gtdigits;
        }

        const std::string& GtDigits() const
        {
            return m_gtDigits;
        }

        void SetGTI(ITS_OCTET gti)
        {
            m_gti = gti;
        }

        const ITS_OCTET& GTI() const
        {
            return m_gti;
        }

        void SetTranslationType(ITS_OCTET transtype)
        {
            m_translationType = transtype;
        }

        const ITS_OCTET& TranslationType() const
        {
            return m_translationType;
        }

        void SetNumberingPlan(ITS_OCTET numbplan)
        {
            m_numberingPlan = numbplan;
        }

        const ITS_OCTET& NumberingPlan() const
        {
            return m_numberingPlan;
        }

        void SetEncodingScheme(ITS_UINT encodingscheme)
        {
            m_encodingScheme = encodingscheme;
        }

        const ITS_UINT& EncodingScheme() const
        {
            return m_encodingScheme;
        }

        void SetAddressIndicator(ITS_OCTET addressind)
        {
            m_addressInd = addressind;
        }

        const ITS_OCTET& AddressIndicator() const
        {
            return m_addressInd;
        }

        void SetLocalPCIndicator(bool pcIndicator)
        {
            m_pcIndicator = pcIndicator;
        }

        const bool& IsLocalPCIndicatorSet() const
        {
            return m_pcIndicator;
        }

        void SetRouteByGT(bool isRouteByGT)
        {
            m_isAddressTypeGT = isRouteByGT;
        }

        const bool& IsRouteByGT() const
        {
            return m_isAddressTypeGT;
        }

    private:
        ITS_OCTET m_gti;
        ITS_OCTET m_translationType;
        ITS_OCTET m_numberingPlan;
        ITS_UINT m_encodingScheme;
        ITS_OCTET m_addressInd;
        bool m_useFromConfig;
        std::string m_gtDigits;
        bool m_pcIndicator;
        bool m_isAddressTypeGT;
};

class IwfRemoteSccpAddress
{
    public:
        IwfRemoteSccpAddress();
        ~IwfRemoteSccpAddress();

        int Parse(const Json::Value& val, IwfConfig& conf);

        const bool& IsUseFromConfig() const
        {
            return m_useFromConfig;
        }

        const std::string& GtDigits() const
        {
            return m_gtDigits;
        }

    private:
        bool m_useFromConfig;
        std::string m_gtDigits;

};

class IwfLocalConfig
{
    public:
        IwfLocalConfig();
        ~IwfLocalConfig();

        void Parse(const Json::Value& val, IwfConfig& conf);

        const unsigned& OriginPointCode() const
        {
            return m_opc;
        }
        void SetOriginPointCode(unsigned opc)
        {
            m_opc = opc;
        }

        const unsigned& AdjacentPointCode() const
        {
            return m_apc;
        }

        const SS7_Family& Family() const
        {
            return m_iwfFamily;
        }

        void SetAdjacentPointCode(unsigned apc)
        {
            m_apc = apc;
        }

        const unsigned& InvokeTimeout() const
        {
            return m_timers.invokeTimeout;
        }

        void SetInvokeTimeout(unsigned timeOut)
        {
            m_timers.invokeTimeout = timeOut;
        }

        void AddLocalSSN(unsigned ssn)
        {
            m_ssn.push_back(ssn);
        }

        const std::vector<unsigned> LocalSSN() const
        {
            return m_ssn;
        }

        const IwfInvokeId& InvokeId() const
        {
            return m_invokeId;
        }

        IwfSelfSccpAddress& SelfSccpAddress()
        {
            return m_selfSccpAddr;
        }

        const IwfRemoteSccpAddress& RemoteSccpAddress() const
        {
            return m_remoteSccpAddr;
        }

        void SetIsUseSccpCdPAFromInMsg(bool useSccpCdPAFromInMsg)
        {
            m_useSccpCdPAFromInMsg = useSccpCdPAFromInMsg;
        }

        const bool& IsUseSccpCdPAFromInMsg() const
        {
            return m_useSccpCdPAFromInMsg;
        }

        const unsigned DiaErroCode() const
        {
            return m_diaErrorCode;
        }

        const bool& IsUseExperimentalResultCode() const
        {
            return m_useexperimentalResultCode;
        }

        void SetLocalNetworkIndicator(unsigned networkInd)
        {
            m_networkInd = networkInd;
        }

        const bool& IsClearSessionContextSet() const
        {
            return m_clearCallSessionContexts;
        }

        const bool& IsSendASPActiveFromStandBySet() const
        {
            return m_sendASPActiveFromStandBy;
        }

        const unsigned GetSessionContextCleanUpTimerValue() const
        {
            return m_sessionContextcleanUpTimer;
        }

        const unsigned LocalNetworkIndicator() const
        {
            return m_networkInd;
        }

        void SetSelectionCriteria(SelectionCriteria selecCrit)
        {
            m_selectionCriteria = selecCrit;
        }

        const SelectionCriteria& GetSelectionCriteria() const
        {
            return m_selectionCriteria;
        }

        void SetASPId(uint32_t aspid)
        {
            m_aspId = aspid;
        }

        const uint32_t GetASPId() const
        {
            return m_aspId;
        }

        void SetCongestionManagementConfig(bool status)
        {
            m_CongestionManagement = status;
        }

        bool isCongestionManagementEnabled()
        {
            return m_CongestionManagement;
        }

        void SetMaxNumberOfSessionsToHold(uint64_t num)
        {
            m_maxNumberOfSessionsToHold = num;
        }

        uint64_t GetMaxNumberOfSessionsToHold()
        {
            return m_maxNumberOfSessionsToHold;
        }

        void InsertEntryinRoutkingKeyMap(string ip, ITS_UINT port, ITS_UINT routkingKey, string homeIp)
        {
            char IpPortKey[22] = {0};
            sprintf(IpPortKey, "%s:%d",ip.c_str(),port);

            struct RoutingKeyInfo rkInfo;
            rkInfo.routingKey = routkingKey;
            strcpy(rkInfo.homeIp, homeIp.c_str());
            RoutingKeyMap.insert(std::pair<string, RoutingKeyInfo>(IpPortKey, rkInfo));
        }

        bool GetRoutingKeyInfofromMap(char *ip, ITS_UINT port, ITS_UINT &routkingKey, char* homeIp)
        {
            char IpPortKey[22] = {0};
            sprintf(IpPortKey, "%s:%d",ip,port);

            std::map<string,RoutingKeyInfo>::iterator itr = RoutingKeyMap.find(IpPortKey);
            if(itr != RoutingKeyMap.end())
            {
                routkingKey = itr->second.routingKey;
                strcpy(homeIp,itr->second.homeIp);
                return true;
            }
            return false;
        }

        uint32_t GetMaxPeerStatusUpdates()
        {
            return m_maxPeerStatusUpdates;
        }

        uint32_t GetPendingQueueExpiryTime()
        {
            return m_pendingQueueExpiryTime;
        }

        bool IsKASMEGenerationRequired()
        {
            return m_isKasmeGenerationRequired;
        }

        bool IsLocalSgsnNumberUsedForMapping()
        {
            return m_useLocalSgsnNumberForMapping;
        }

        uint64_t GetIncrementedSgsnNumber()
        {
            return ++m_globalSgsnNumberCounter;
        }

        bool IsVplmnIdToBeValidated()
        {
            return m_validateVplmnIdRcvdInReq;
        }
    protected:
        unsigned m_opc;
        unsigned m_apc;
        SS7_Family m_iwfFamily;
        std::vector<unsigned> m_ssn;

        struct Timers {
            unsigned invokeTimeout;
        }m_timers;

        IwfInvokeId m_invokeId;

        IwfSelfSccpAddress m_selfSccpAddr;
        IwfRemoteSccpAddress m_remoteSccpAddr;

        bool m_useSccpCdPAFromInMsg;
        unsigned m_diaErrorCode;
        bool m_useexperimentalResultCode;
        unsigned m_networkInd;
        SelectionCriteria m_selectionCriteria;
        bool m_clearCallSessionContexts;
        unsigned m_sessionContextcleanUpTimer;
        uint32_t m_aspId;
        bool m_CongestionManagement;
        uint64_t m_maxNumberOfSessionsToHold;
        std::map <string, RoutingKeyInfo> RoutingKeyMap;
        uint32_t m_maxPeerStatusUpdates;
        bool m_sendASPActiveFromStandBy;
        uint32_t m_pendingQueueExpiryTime;
        bool m_isKasmeGenerationRequired;
        bool m_useLocalSgsnNumberForMapping;
        uint64_t m_globalSgsnNumberCounter;
        bool m_validateVplmnIdRcvdInReq;
};

class IwfDest
{
    public:
        IwfDest();
        ~IwfDest();

        void Parse(const Json::Value& val, IwfConfig& conf);

        const std::string& Name() const
        {
            return m_destName;
        }
        const IwfAddrType& Type() const
        {
            return m_type;
        }
        const unsigned& Family() const
        {
            return m_family;
        }
        const bool& IsNational() const
        {
            return m_isNational;
        }
        const unsigned& PointCode() const
        {
            return m_pc;
        }
        const bool& IsSSNPresent() const
        {
            return m_ssnPresent;
        }
        const std::string& DiaIdentity() const
        {
            return m_diaIdentity;
        }
        const unsigned& SSN() const
        {
            return m_ssn;
        }
        const unsigned& GTI() const
        {
            return m_gti;
        }
        const unsigned& TransType() const
        {
            return m_tt;
        }
        const unsigned& NumberingPlan() const
        {
            return m_np;
        }
        const bool& IsNationalSpecificECS() const
        {
            return m_ecsNationalSpecific;
        }
        const std::string& GtAddr() const
        {
            return m_gtAddr;
        }

        void SetParameters(IwfSigtranDestinationConfig* destInfo);

    protected:
        std::string m_destName;
        std::string m_diaIdentity;
        IwfAddrType m_type;  // pc-ssn or gt
        unsigned    m_family; // ansi or itu
        bool        m_isNational; // national or international
        unsigned    m_pc;
        unsigned    m_ssn;
        bool        m_ssnPresent;
        unsigned    m_gti;
        unsigned    m_tt;
        unsigned    m_np;
        bool        m_ecsNationalSpecific;
        std::string m_gtAddr;
};

class IwfE164NumberRange
{
    public:
        IwfE164NumberRange();
        ~IwfE164NumberRange();

        int Parse(const Json::Value& val, IwfConfig& conf);
        uint64_t startNumber() const
        {
            return m_iE164Start;
        }
        uint64_t endNumber() const
        {
            return m_iE164End;
        }

    private:
        uint32_t m_iE164Start;
        uint32_t m_iE164End;

};

class IwfRoute
{
    public:
        IwfRoute();
        ~IwfRoute();

        void Parse(const Json::Value& val, IwfConfig& conf);

        const std::string& MNC() const
        {
            return m_mncHome;
        }
        const std::string& MCC() const
        {
            return m_mccHome;
        }

        const std::string& AppId() const
        {
            return m_appId;
        }

        const std::string& ServiceKeyStart() const
        {
            return m_serviceKeyStart;
        }

        const std::string& ServiceKeyEnd() const
        {
            return m_serviceKeyEnd;
        }

        const bool& IsServiceKeyInRange() const
        {
            return m_isServiceKeyInRange;
        }

        const std::string& CallingGtAddrDigits() const
        {
            return m_callingGtAddrDigits;
        }

        const int& TranslatorId() const
        {
            return m_translatorId;
        }

        const unsigned& OriginSSN() const
        {
            return m_ossn;
        }
        const unsigned& DestinationSSN() const
        {
            return m_dssn;
        }
        const IwfDest& Dest() const
        {
            return *m_dest;
        }
        bool IsAltDestinationSet() const
        {
            return m_isAltDestSet;
        }
        const IwfDest& AltDest() const
        {
            return *m_altdest;
        }
        const std::string& ServiceContextId() const
        {
            return m_serviceContextId;
        }

        const std::string& GetImsiPrefix() const
        {
            return m_imsiPrefix;
        }

        const TSKList& GetServiceKeyList() const
        {
            return m_serviceKeyList;
        }
        static uint64_t MakeKey(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey, std::string callingGtAddrDigits,
                SelectionCriteria selectionCriteria = UNKNOWN_SELECTIONCRITERIA);

        static uint64_t MakeKey(std::string mcc, std::string mnc, std::string appId)
        {
            mcc.append(mnc);
            mcc.append(appId);
            return (atoi(mcc.c_str()));
        }

        static std::string MakeKey(std::string& rule_name, string& ossn, string& gtAddr, SelectionCriteria scVal = UNKNOWN_SELECTIONCRITERIA);

        const std::string& destRealm() const
        {
            return m_destRealm;
        }

        const std::string& destHost() const
        {
            return m_destHost;
        }

        const std::string& altHost() const
        {
            return m_altHost;
        }

        const std::string& altRealm() const
        {
            return m_altRealm;
        }

        void SetParameter(IwfTranslatorRuleConfig* rule);
        void SetParameter(IwfRoute* route);

        std::string& GetProtActionRuleName()
        {
            return m_protActionRuleName;
        }

#if 0
        const void  CreateAllowedVplmnIdVector(const std::string& vplmnId, char delim)
        {
            std::stringstream ss(vplmnId);
            std::string item;
            while (std::getline(ss, item, delim))
            {
                m_vplmnVec.push_back(item);
            }
        }
#endif
        const std::vector<std::string>& vplmnId() const
        {
            return m_vplmnVec;
        }

    protected:
        std::string m_mccHome;
        std::string m_mncHome;
        std::string m_appId;
        std::string m_serviceKeyStart;
        std::string m_serviceKeyEnd;
        std::string m_callingGtAddrDigits;
        std::vector<std::string> m_vplmnVec;
        int      m_translatorId;
        unsigned m_ossn;
        unsigned m_dssn;
        IwfDest* m_dest;
        IwfDest* m_altdest;
        bool m_isAltDestSet;
        std::string m_destRealm;
        std::string m_destHost;
        std::string m_altRealm;
        std::string m_altHost;
        bool m_isServiceKeyInRange;
        std::string m_serviceContextId;
        std::string m_imsiPrefix;
        std::string m_protActionRuleName;
        TSKList m_serviceKeyList;
};

class IwfRoutingRules
{
    protected:
        // The key will be mcc + mnc + application-id
        typedef eAccelero::SmartPtr<IwfRoute> IwfRouteRef;
        //typedef std::map<int64_t, IwfRouteRef> Routes;
        typedef std::map<std::string, IwfRouteRef> Routes;
        Routes m_routes;
        IwfE164NumberRange m_ocE164NumRange;

    public:
        IwfRoutingRules();
        ~IwfRoutingRules();

        void Parse(const Json::Value& val, IwfConfig& conf);

        //bool IsRouteAvailable(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey, std::string gtAddrDigits);

        bool IsRouteAvailable(string& rule_name, std::string& gtAddrDigits);

        //IwfRouteRef Route(std::string mcc, std::string mnc, std::string appId, int32_t serviceKey = -1, std::string callingGtAddrDigits = "");

        IwfRouteRef Route(std::string& ruleName,std::string callingGtAddrDigits = "");

        uint64_t getE164StartNumber(){return m_ocE164NumRange.startNumber();};
        uint64_t getE164EndNumber(){return m_ocE164NumRange.endNumber();};

        int SetRoutingRulesConfig(IwfTranslatorRulesConfig *req);

        int ModifyRoutingRulesConfig(IwfTranslatorRulesConfig *req);

        int DeleteRoutingRulesConfig(IwfTranslatorRulesConfig *req);

        int DeleteRuleFromMap(IwfTranslatorRuleConfig rule, int32_t serviceKey);

        int DeleteAllowedVplmnIdFromRoutingRulesConfig(IwfTranslatorRulesConfig *req);

        int DeleteAllowedVplmnIdFromRule(IwfTranslatorRuleConfig rule);

        int CleanRoutingRuleMap();

};

struct SHssWatcherInfo
{
    std::string m_strHssNumber;
    std::vector<SCCPParameters> m_vecSgsn;
};

class IwfHssToSgsnCache
{
    public:

        static IwfHssToSgsnCache* getInstance()
        {
            if (m_self == NULL)
                m_self = new IwfHssToSgsnCache;

            return m_self;
        }

        IwfHssToSgsnCache();
        ~IwfHssToSgsnCache();

        int initialize(uint64_t uiStart, uint64_t uiEnd)
        {
            m_iFreeIndex = 0;
            for (uint64_t iIndex = 0; iIndex < (uiEnd - uiStart); iIndex++)
            {
                m_vecE164NumPool.push_back(uiStart + iIndex);
            }
            return 0;
        };

        int addElement(std::string strOrigHost, SHssWatcherInfo osWatcherInfo);
        int addSgsn(std::string strOrigHost, SCCPParameters sccpParam);
        int isSgsnPresent(std::string strOrigHost, ITS_UINT opc);
        int delElement(std::string strOrigHost);
        std::vector<SCCPParameters> getSgsnListForHss(std::string strOrigHost);
        void getSgsnListForHss(std::string strOrigHost,std::vector<SCCPParameters>& sgsn);
        bool isEntryPresentFor(std::string strOrigHost);
        std::string allocE164Num();
        void freeE164NumFor(std::string strE164Num){};
        std::string getHssNumber(std::string strOrigHost);
        SHssWatcherInfo getHssWatcherInfo(std::string strOrigHost);
    private:
        std::vector<uint64_t> m_vecE164NumPool;
        static IwfHssToSgsnCache* m_self;
        std::map<std::string, SHssWatcherInfo> m_mapHssToWatcherInfo;
        int m_iFreeIndex;
};

class IwfDestinations
{
    public:
        IwfDestinations();
        ~IwfDestinations();
        void Parse(const Json::Value& val, IwfConfig& conf);

        IwfDest& Dest(const std::string& str)
        {
            return *m_destinations[str];
        }

        IwfDest& GetDestForPC(const std::string& str)
        {
            return *m_PointCodeToNameMap[str];
        }

        int SetIwfDestinationConfig(IwfSigtranDestinationConfig* dest);

        int ModifyIwfDestinationConfig(IwfSigtranDestinationConfig* dest);

        int DeleteIwfDestinationConfig(IwfSigtranDestinationConfig* dest);

    protected:
        typedef std::map<std::string, IwfDest*> DestMap;
        typedef std::map<std::string, IwfDest*> PCMap;
        DestMap m_destinations;
        PCMap  m_PointCodeToNameMap;
};

class IwfCDRConfig
{
 public:
    enum
    {
        MAX_REC_PER_FILE = 1000
    };
    enum
    {
        CDR_FORMAT_CSV,
        CDR_FORMAT_JSON
    };

    IwfCDRConfig()
        : m_maxRecsPerFile(MAX_REC_PER_FILE),
        m_cdrFormat(CDR_FORMAT_CSV),
        m_fieldSeparator(',')
    {
    }

    unsigned GetMaxRecsPerFile() const
    {
        return m_maxRecsPerFile;
    }

    void SetMaxRecsPerFile(unsigned maxRecs)
    {
        m_maxRecsPerFile = maxRecs;
    }

    void SetCdrInJsonFormat()
    {
        m_cdrFormat = CDR_FORMAT_JSON;
    }

    void SetCdrInCsvFormat()
    {
        m_cdrFormat = CDR_FORMAT_CSV;
    }

    void SetFieldSeparator(const char* fs)
    {
        m_fieldSeparator = fs[0];
    }

    char GetFieldSeparator()
    {
        return m_fieldSeparator;
    }

    int GetCdrFormat()
    {
        return m_cdrFormat;
    }

 protected:
    unsigned m_maxRecsPerFile;
    int m_cdrFormat;
    char m_fieldSeparator;
};

class IwfDCCAEndpointConf
{
 public:
    IwfDCCAEndpointConf(const std::string& name, uint32_t priority)
        : m_endpointName(name),
          m_priority(priority)
    {
    }
    IwfDCCAEndpointConf(const IwfDCCAEndpointConf& rhs)
    {
        this->Assign(rhs);
    }
    IwfDCCAEndpointConf& operator=(const IwfDCCAEndpointConf& rhs)
    {
        if (this != &rhs)
        {
            this->Assign(rhs);
        }
        return *this;
    }

    const std::string& GetEndpoint() const
    {
        return m_endpointName;
    }
    uint32_t GetPriority() const
    {
        return m_priority;
    }

    // For stl sorting
    bool operator < (const IwfDCCAEndpointConf& rhs) const
    {
        return (m_priority < rhs.m_priority);
    }
    int operator - (const IwfDCCAEndpointConf& rhs) const
    {
        return (m_priority - rhs.m_priority);
    }
    // for stl find
    bool operator == (const IwfDCCAEndpointConf& rhs) const
    {
        return (m_endpointName == rhs.m_endpointName);
    }

 protected:

    void Assign(const IwfDCCAEndpointConf& rhs)
    {
        m_endpointName = rhs.m_endpointName;
        m_priority = rhs.m_priority;
    }

    std::string m_endpointName;
    uint32_t    m_priority;
};

// Endpoints group, identified by its realm
class IwfDCCAEndpointsConf
{
 public:
    typedef std::list<IwfDCCAEndpointConf> EndpointsList;

    IwfDCCAEndpointsConf(const std::string& realmName)
        : m_destination(realmName)
    {
    }
    // Copy and assignment not required. Default is good enough

    bool AddEndpoint(const std::string& endpointName, uint32_t priority, bool sendCCRTFlag);

    bool RemoveEndpoint(const std::string& endpointName, uint32_t prioirty);

    const std::string& GetPrimary() const
    {
        return m_endpoints.front().GetEndpoint();
    }

    size_t Size() const
    {
        return m_endpoints.size();
    }

    EndpointsList::iterator Begin()
    {
        return m_endpoints.begin();
    }
    EndpointsList::iterator End()
    {
        return m_endpoints.end();
    }

    void SetCCRTFlag(bool val)
    {
        sendCCRTFlag = val;
    }
    bool GetCCRTFlag()
    {
        return sendCCRTFlag;
    }
 protected:
    std::string   m_destination; // currently this is a realm
    EndpointsList m_endpoints;
    bool sendCCRTFlag;
};

class IwfDCCADestinations
{
 public:
    IwfDCCADestinations()
    {
    }

    // Implicit new map entry creation
    bool AddEndpoint(const std::string& destName,
                        const std::string& endpointName,
                        uint32_t prioirty,
                        bool sendCCRTFlg);

    bool RemoveEndpoint(const std::string& destName, const std::string& endpointName, uint32_t prioirty);

    bool RemoveDestination(const std::string& destName);

    IwfDCCAEndpointsConf* LookupEndpointsConf(const std::string& destName);

 protected:
    // key is the realm name and contents are the endpoints
    typedef std::map<std::string, IwfDCCAEndpointsConf> DestMap;
    DestMap m_destinations;
};

enum IwfCCFHAction
{
    IWF_CCFH_ACTION_TERMINATE = 0,
    IWF_CCFH_ACTION_CONTINUE = 1,
    IWF_CCFH_ACTION_RETRY_TERMINATE = 2
};

class IwfDCCAConfig
{
 public:
    enum
    {
        IWF_DEFAULT_TX_TIMEOUT = 10,  // in secs
    };

    IwfDCCAConfig()
        : m_txTimeout(IWF_DEFAULT_TX_TIMEOUT),
          m_ccfhInitialAction(IWF_CCFH_ACTION_TERMINATE),
          m_ccfhUpdateAction(IWF_CCFH_ACTION_TERMINATE),
          m_setTbitOnRetry(false)
    {
    }

    uint32_t GetTxTimeout() const
    {
        return m_txTimeout;
    }
    void SetTxTimeout(uint32_t timeoutSecs);

    IwfCCFHAction GetInitialCCFHAction() const
    {
        return m_ccfhInitialAction;
    }
    void SetInitialCCFHAction(IwfCCFHAction action);

    IwfCCFHAction GetUpdateCCFHAction() const
    {
        return m_ccfhUpdateAction;
    }
    void SetUpdateCCFHAction(IwfCCFHAction action);

    // Not a const function, can be used for modifying the IwfDCCADestinations
    IwfDCCADestinations& GetDestinations()
    {
        return m_destinations;
    }
    bool IsTbitRequired()
    {
        return m_setTbitOnRetry;
    }

    void Configure(Json::Value& dcca);

 protected:
    IwfCCFHAction GetCCFHAction(const std::string& actionStr);

    uint32_t m_txTimeout;
    IwfCCFHAction m_ccfhInitialAction;
    IwfCCFHAction m_ccfhUpdateAction;
    IwfDCCADestinations m_destinations;
    bool m_setTbitOnRetry;
};

class IwfProtActionCfg
{

public :
    IwfProtActionCfg(){};
    ~IwfProtActionCfg(){};

    int SetProtActionConfig(IwfProtocolActionsConfig *req);
    int ModifyProtActionConfig(IwfProtocolActionsConfig *req);
    int DeleteProtActionConfig(IwfProtocolActionsConfig *req);
};
class IwfConfig
{
    public:
        IwfConfig(const char* configFile = NULL);
        IwfConfig(const char* configFile, IwfCTrieImpl *pTrieIntf);
        ~IwfConfig();

        void SetConfigFile(const char* configFile)
        {
            m_configFileName = configFile;
        }

        int ParseConfig();

        int ParseTranslatorConfig();

        IwfLocalConfig& LocalConfig()
        {
            return m_localConfig;
        }

        IwfRoutingRules& RoutingRules()
        {
            return m_routingRules;
        }

        IwfDestinations& Destinations()
        {
            return m_destinations;
        }

        IwfCDRConfig& CDRConfig()
        {
            return m_cdrConfig;
        }

        IwfDCCAConfig& DCCAConfig()
        {
            return m_dccaConfig;
        }

        IwfPrefixRules& GetPrefixRulesStore()
        {
            return m_transRules;
        }

        RuleNameVsSKList& GetRuleNameVsSKList()
        {
            return m_mapRuleNameVsSKList;
        }

        void InsertRuleVsSKListInMap(std::string RuleName, TSKList serviceKeyList)
        {
            std::pair<string,TSKList> ruleSkListPair(RuleName, serviceKeyList);
            m_mapRuleNameVsSKList.insert(ruleSkListPair);
        }

        void DeleteRuleVsSKListInMap(std::string RuleName)
        {
            std::map<string, TSKList>::iterator itr = m_mapRuleNameVsSKList.find(RuleName);
            if(itr != m_mapRuleNameVsSKList.end())
            {
                m_mapRuleNameVsSKList.erase(itr);
            }
        }

        void ModifyRuleVsSKListInMAP(std::string RuleName, TSKList serviceKeyList)
        {
            std::map<string,TSKList>::iterator itr = m_mapRuleNameVsSKList.find(RuleName);
            if(itr != m_mapRuleNameVsSKList.end())
            {
                itr->second = serviceKeyList;
            }
        }

        void InsertImsiPrefixVsRuleInMAP(std::string ImsiPrefix, std::string RuleName);
        void DeleteImsiPrefixVsRuleInMap(std::string RuleName)
        {
            for(std::map<string, string>::iterator it = m_mapImsiPrefixVsRule.begin() ; it != m_mapImsiPrefixVsRule.end() ; ++it)
            {
                if(!strcmp(it->second.c_str(),RuleName.c_str()))
                {
                    m_mapImsiPrefixVsRule.erase(it);
                    break;
                }
                std::size_t pos = it->second.find(RuleName);
                if(pos != std::string::npos)
                {
                    if((pos == 0) && (it->second[pos+RuleName.length()] == ',' ||
                                it->second[pos+RuleName.length()] == '\0'))
                    {
                        it->second.erase(pos, RuleName.length()+1);
                        break;
                    }
                    else if((it->second[pos-1] == ',') && (it->second[pos+RuleName.length()] == ',' ||
                                it->second[pos+RuleName.length()] == '\0'))
                    {
                        it->second.erase(pos-1, RuleName.length()+1);
                        break;
                    }
                }
            }
        }

        map<string,string>& GetImsiPrefixVsRuleMap()
        {
            return m_mapImsiPrefixVsRule;
        }
        int SearchServiceKey(string& RuleId, int32_t& serviceKeyVal);

        IwfProtActionCfg& GetIwfProtActionCfg()
        {
            return m_protActionConfig;
        }

    protected:
        std::string m_configFileName;

        IwfLocalConfig m_localConfig;
        IwfRoutingRules m_routingRules;
        IwfDestinations m_destinations;
        IwfCDRConfig    m_cdrConfig;
        IwfDCCAConfig   m_dccaConfig;
        IwfProtActionCfg m_protActionConfig;
        Json::Value m_protoConvertor;

        IwfPrefixRules m_transRules;
        RuleNameVsSKList m_mapRuleNameVsSKList;
        map<string,string> m_mapImsiPrefixVsRule;
};


#endif // __IWF_CONFIG_H__
