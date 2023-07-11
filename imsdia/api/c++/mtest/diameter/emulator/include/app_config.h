/*********************************-*-H-*-************************************
*                                                                          *
*          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
*            Manufactured in the United States of America.                 *
*      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
*                                                                          *
*   This product and related documentation is protected by copyright and   *
*   distributed under licenses restricting its use, copying, distribution  *
*   and decompilation.  No part of this product or related documentation   *
*   may be reproduced in any form by any means without prior written       *
*   authorization of Diametriq and its licensors, if any.                  *
*                                                                          *
*   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
*   government is subject to restrictions as set forth in subparagraph     *
*   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
*   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
*                                                                          *
****************************************************************************/

#ifndef APP_CONFIG_H 
#define APP_CONFIG_H

#include <json/json.h>
#include <unordered_map>
#include <vector>

bool parseJsonConfigFile(char *file);
bool populateJsonAvpDataForMME(Json::Value *root);
bool populateJsonAvpDataForHSS(Json::Value *root);
unsigned int populateFeatures(const Json::Value &featureData);
unsigned int populateAccessRestriction(const Json::Value &arData);

enum Features 
{
    ODBallAPN                                   = (1<<0),
    ODB_HPLMN_APN                               = (1<<1),
    ODB_VPLMN_APN                               = (1<<2),
    ODBallOG                                    = (1<<3),
    ODBallInternationalOG                       = (1<<4),
    ODBallInternationalOGNotToHPLMNCountry      = (1<<5),
    ODBallInterzonalOG                          = (1<<6),
    ODBallInterzonalOGNotToHPLMNCountry         = (1<<7),
    ODBallInterzonalOGAndInternationalOGNotToHPLMNCountry = (1<<8),
    RegSub                                      = (1<<9),
    Trace                                       = (1<<10),
    LCSallPrivExcep                             = (1<<11),
    LCSUniversal                                = (1<<12),
    LCSCallSessionRelated                       = (1<<13),
    LCSCallSessionUnrelated                     = (1<<14),
    LCSPLMNOperator                             = (1<<15),
    LCSServiceType                              = (1<<16),
    LCSallMOLRSS                                = (1<<17),
    LCSBasicSelfLocation                        = (1<<18),
    LCSAutonomousSelfLocation                   = (1<<19),
    LCSTransferToThirdParty                     = (1<<20),
    SMMOPP                                      = (1<<21),
    BarringOutgoingCalls                        = (1<<22),
    BAOC                                        = (1<<23),
    BOIC                                        = (1<<24),
    BOICExHC                                    = (1<<25),
    UEReachabilityNotification                  = (1<<26),
    TADSDataRetrieval                           = (1<<27),  
    StateLocationInformationRetrieval           = (1<<28),
    PartialPurge                                = (1<<29)
};

enum AccessRestriction
{
    NO_UTRAN                    = (1<<0),
    NO_GERAN                    = (1<<1),
    NO_GAN                      = (1<<2),
    NO_I_HSPA_Evolution         = (1<<3),
    NO_E_UTRAN                  = (1<<4),
    NO_HO_To_Non_3GPP_Access    = (1<<5)
};

enum EquipmentStatus
{
    WHITELISTED   =  0,
    BLACKLISTED   =  1,
    GREYLISTED    =  2
};

struct QosProfile
{
    unsigned int class_value;
    unsigned int arp;
};

class LocalConfig
{
    private:
        unsigned int    mcc;
        unsigned int    mnc;
        unsigned int    features;
        std::string     nodeType;

    public:
        void setMcc(unsigned int value);
        unsigned int getMcc(void);

        void setMnc(unsigned int value);
        unsigned int getMnc(void);

        void setNodeType(std::string data);
        std::string getNodeType(void);

        void setFEATURES(unsigned int value);
        unsigned int getFEATURES(void);
};

class UeConfig
{
    private:
        std::string     imei;
        std::string     softwareVersion;
        std::string     radioAccessType;

    public:
        void setIMEI(std::string data);
        std::string getIMEI(void);

        void setSoftwareVersion(std::string data);
        std::string getSoftwareVersion(void);

        void setRadioAccessType(std::string data);
        std::string getRadioAccessType(void);
};

class ApnProfileConfig
{
    private:
        unsigned int    contextId;
        unsigned int    max_dl_bw;
        unsigned int    max_ul_bw;
        std::string     pdnType;
        std::string     apn;
        std::string     tgpp_charg_chara;
        std::string     apn_oi_repl;
        QosProfile      qosProfile;

    public:
        void setContextId(unsigned int value);
        unsigned int getContextId(void);

        void setPdnType(std::string data);
        std::string getPdnType(void);

        void setMaxDlBw(unsigned int value);
        unsigned int getMaxDlBw(void);

        void setMaxUlBw(unsigned int value);
        unsigned int getMaxUlBw(void);

        void setApn(std::string data);
        std::string getApn(void);

        void setTgppChargData(std::string data);
        std::string getTgppChargData(void);

        void setApnOiRepl(std::string data);
        std::string getApnOiRepl(void);
        
        void setQosProfile(unsigned int, unsigned int);
        void getQosProfile(unsigned int&, unsigned int&);
};

class SubTemplate
{
    private:
        unsigned int    access_restriction;
        unsigned int    max_dl_bandwidth;
        unsigned int    max_ul_bandwidth;
        unsigned int    dac;
        std::string     template_name;
        std::string     aor;
        std::string     tgppChargChara;
        std::vector<std::string> apnProfiles;     

    public:
        void setAccessRestriction(unsigned int value);
        unsigned int getAccessRestriction(void);
        
        void setMaxDlBw(unsigned int value);
        unsigned int getMaxDlBw(void);

        void setMaxUlBw(unsigned int value);
        unsigned int getMaxUlBw(void);

        void setDac(unsigned int value);
        unsigned int getDac(void);

        void setTemplateName(std::string data);
        std::string getTemplateName(void);

        void setAor(std::string data);
        std::string getAor(void);

        void setTgppChargChara(std::string data);
        std::string getTgppChargChara(void);

        void setApnProfiles(std::string data);
        std::vector<std::string>& getApnProfiles(void);

};

class SubRegistry
{
    private:
        std::string     imsi;
        std::string     msisdn;
        std::string     XRES;
        std::string     AUTN;
        std::string     KASME;
        std::string     template_name;

    public:
        void setImsi(std::string data);
        std::string getImsi(void);

        void setMsisdn(std::string data);
        std::string getMsisdn(void);

        void setXRES(std::string data);
        std::string getXRES(void);

        void setAUTN(std::string data);
        std::string getAUTN(void);

        void setKASME(std::string data);
        std::string getKASME(void);

        void setTemplateName(std::string data);
        std::string getTemplateName(void);      
};

class EIR
{
    private:
        std::string imei;
        EquipmentStatus status;

    public:
        void setImei(std::string data);
        std::string getImei(void);

        void setStatus(EquipmentStatus data);
        EquipmentStatus getStatus(void);
};

// =====================================
// Class LocalConfig Set and Get methods
// =====================================

inline void LocalConfig::setMcc(unsigned int value)
{
    mcc = value;
}

inline unsigned int LocalConfig::getMcc(void)
{
    return mcc;
}

inline void LocalConfig::setMnc(unsigned int value)
{
    mnc = value;
}

inline unsigned int LocalConfig::getMnc(void)
{
    return mnc;
}
  
inline void LocalConfig::setNodeType(std::string data)
{
    nodeType = data;
}

inline std::string LocalConfig::getNodeType(void)
{
    return nodeType;
}

inline void LocalConfig::setFEATURES(unsigned int value)
{
    features = value;
}

inline unsigned int LocalConfig::getFEATURES(void)
{
    return features;
}

// =====================================
// Class UeConfig Set and Get methods
// =====================================

inline void UeConfig::setIMEI(std::string data)
{
    imei = data;
}

inline std::string UeConfig::getIMEI(void)
{
    return imei;
}

inline void UeConfig::setSoftwareVersion(std::string data)
{
    softwareVersion = data;
}

inline std::string UeConfig::getSoftwareVersion(void)
{
    return softwareVersion;
}

inline void UeConfig::setRadioAccessType(std::string data)
{
    radioAccessType = data;
}

inline std::string UeConfig::getRadioAccessType(void)
{
    return radioAccessType;
}

// ===========================================
// Class ApnProfileConfig Set and Get methods
// ===========================================

inline void ApnProfileConfig::setContextId(unsigned int value)
{
   contextId = value; 
}

inline unsigned int ApnProfileConfig::getContextId(void)
{
    return contextId;
}

inline void ApnProfileConfig::setPdnType(std::string data)
{
    pdnType = data;    
}

inline std::string ApnProfileConfig::getPdnType(void)
{
    return pdnType;
}

inline void ApnProfileConfig::setMaxDlBw(unsigned int value)
{
    max_dl_bw = value;
}

inline unsigned int ApnProfileConfig::getMaxDlBw(void)
{
    return max_dl_bw;
}

inline void ApnProfileConfig::setMaxUlBw(unsigned int value)
{
    max_ul_bw = value;
}

inline unsigned int ApnProfileConfig::getMaxUlBw(void)
{
    return max_ul_bw;
}

inline void ApnProfileConfig::setApn(std::string data)
{
    apn = data;    
}

inline std::string ApnProfileConfig::getApn(void)
{
    return apn;
}

inline void ApnProfileConfig::setTgppChargData(std::string data)
{
    tgpp_charg_chara = data;
}

inline std::string ApnProfileConfig::getTgppChargData(void)
{
    return tgpp_charg_chara;
}

inline void ApnProfileConfig::setApnOiRepl(std::string data)
{
   apn_oi_repl = data; 
}

inline std::string ApnProfileConfig::getApnOiRepl(void)
{
    return apn_oi_repl;
}

inline void ApnProfileConfig::setQosProfile(unsigned int class_value, unsigned int arp)
{
    qosProfile.class_value  =   class_value;
    qosProfile.arp          =   arp;
}

inline void ApnProfileConfig::getQosProfile(unsigned int&class_value, unsigned int&arp)
{
    class_value     =   qosProfile.class_value;
    arp             =   qosProfile.arp;
}

// ===============================================
// Class SubTemplate Get and Set methods
// ===============================================
inline void SubTemplate::setAccessRestriction(unsigned int value)
{
    access_restriction = value;    
}

inline unsigned int SubTemplate::getAccessRestriction(void)
{
    return access_restriction;    
}

inline void SubTemplate::setMaxDlBw(unsigned int value)
{
    max_dl_bandwidth = value;
}

inline unsigned int SubTemplate::getMaxDlBw(void)
{
    return max_dl_bandwidth;
}

inline void SubTemplate::setMaxUlBw(unsigned int value)
{
    max_ul_bandwidth = value;
}

inline unsigned int SubTemplate::getMaxUlBw(void)
{
    return max_ul_bandwidth;
}

inline void SubTemplate::setDac(unsigned int value)
{
    dac = value;
}

inline unsigned int SubTemplate::getDac(void)
{
    return dac;
}

inline void SubTemplate::setTemplateName(std::string data)
{
    template_name = data;
}

inline std::string SubTemplate::getTemplateName(void)
{
    return template_name;
}

inline void SubTemplate::setAor(std::string data)
{
    aor = data;
}

inline std::string SubTemplate::getAor(void)
{
    return aor;
}

inline void SubTemplate::setTgppChargChara(std::string data)
{
    tgppChargChara = data;
}

inline std::string SubTemplate::getTgppChargChara(void)
{
    return tgppChargChara;
}

inline void SubTemplate::setApnProfiles(std::string data)
{
    apnProfiles.push_back(data);
}

inline std::vector<std::string>& SubTemplate::getApnProfiles(void)
{
    return apnProfiles;
}

// =====================================================
// Class SubRegistry Get and Set methods
// =====================================================

inline void SubRegistry::setImsi(std::string data)
{
    imsi = data;    
}

inline std::string SubRegistry::getImsi(void)
{
    return imsi;
}

inline void SubRegistry::setMsisdn(std::string data)
{
    msisdn = data;    
}

inline std::string SubRegistry::getMsisdn(void)
{
    return msisdn;
}

inline void SubRegistry::setXRES(std::string data)
{
    XRES = data;
}

inline std::string SubRegistry::getXRES(void)
{
    return XRES;    
}

inline void SubRegistry::setAUTN(std::string data)
{
    AUTN = data;
}

inline std::string SubRegistry::getAUTN(void)
{
    return AUTN;
}

inline void SubRegistry::setKASME(std::string data)
{
    KASME = data;
}

inline std::string SubRegistry::getKASME(void)
{
    return KASME;
}

inline void SubRegistry::setTemplateName(std::string data)
{
    template_name = data;
}

inline std::string SubRegistry::getTemplateName(void)
{
    return template_name;
}
    
// =================================================
// Class EIR Get and Set methods
// =================================================

inline void EIR::setImei(std::string data)
{
    imei = data;
}

inline std::string EIR::getImei(void)
{
    return imei;
}

inline void EIR::setStatus(EquipmentStatus data)
{
    status = data;
}

inline EquipmentStatus EIR::getStatus(void)
{
    return status;
}

typedef std::unordered_map<std::string, UeConfig*> UECONFIGMAP;
extern UECONFIGMAP UeConfigMap;

#endif // #ifndef APP_CONFIG_H
