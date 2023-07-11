/*********************************-*-C-*-************************************
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

#include <iostream>
#include <fstream>
#include <cstring>
#include <app_config.h>

using namespace std;

// =========================================================================
// Purpose  : For parsing the json file.
// Input    : JSON file name
// Output   : Status of the parsing
// =========================================================================
bool parseJsonConfigFile(char *file)
{
    Json::Reader reader;
    Json::Value jsonRoot;
    ifstream doc(file);

    bool status = reader.parse(doc,jsonRoot);
    if (status == false)
    {
        return status;
    }
    
    if(strcmp(file,"mme_emu.json") == 0)
    {
        populateJsonAvpDataForMME(&jsonRoot);
    }
    else if(strcmp(file,"hss_emu.json") == 0)
    {
        populateJsonAvpDataForHSS(&jsonRoot);
    }
    else 
    {
        cout<<"Unknown Configuration file!"<<endl;
        return false;
    }
    return true;
}

bool populateJsonAvpDataForMME(Json::Value *root)
{
    LocalConfig *localConfig = new LocalConfig; // Didn't delete

    string nodeType = (*root)["local"]["node-type"].asString();
    localConfig->setNodeType(nodeType);

    unsigned int mcc = (*root)["local"]["mcc"].asUInt();
    localConfig->setMcc(mcc);

    unsigned int mnc  = (*root)["local"]["mnc"].asUInt();
    localConfig->setMnc(mnc);

    const Json::Value featureData = (*root)["local"]["features"];
    unsigned int featureValue = populateFeatures(featureData);

    localConfig->setFEATURES(featureValue);
    cout<<"featureValue:"<<localConfig->getFEATURES()<<endl;

    UECONFIGMAP UeConfigMap;
    const Json::Value UeConfigData = (*root)["ue-config"];
    for (int ueIndex = 0; ueIndex < UeConfigData.size(); ueIndex++)
    {
        string imsi = UeConfigData[ueIndex]["imsi"].asString();
        
        const Json::Value attrData = UeConfigData[ueIndex]["data"];
        for (int attrInex = 0; attrInex < attrData.size(); attrInex++ )
        {
            UeConfig *ueConfig = new UeConfig; // Don't delete this's pushing to map

            string imei = attrData[attrInex]["imei"].asString();
            ueConfig->setIMEI(imei);

            string softVersion =
                attrData[attrInex]["software-version"].asString();
            ueConfig->setSoftwareVersion(softVersion);

            string ratType = attrData[attrInex]["radio-access-type"].asString();
            ueConfig->setRadioAccessType(ratType);

            UeConfigMap[imsi] = ueConfig;
        }
            
    }

    UECONFIGMAP::const_iterator it;
    for(it = UeConfigMap.begin(); it != UeConfigMap.end(); it++)
    {
        cout<<it->first<<'\t'<<it->second->getIMEI()<<endl;
    }
}

bool populateJsonAvpDataForHSS(Json::Value *root)
{
    LocalConfig *localConfig = new LocalConfig; // Didn't delete

    string nodeType = (*root)["local"]["node-type"].asString();
    localConfig->setNodeType(nodeType);

    unsigned int mcc = (*root)["local"]["mcc"].asUInt();
    localConfig->setMcc(mcc);

    unsigned int mnc  = (*root)["local"]["mnc"].asUInt();
    localConfig->setMnc(mnc);

    const Json::Value featureData = (*root)["local"]["features"];
    unsigned int featureValue = populateFeatures(featureData);

    localConfig->setFEATURES(featureValue);
    cout<<"featureValue:"<<localConfig->getFEATURES()<<endl;

    const Json::Value apnProfile = (*root)["apn-profiles"];
    for(int apnIndex = 0; apnIndex < apnProfile.size(); apnIndex++)
    {
        ApnProfileConfig *apnProfileConfig = new ApnProfileConfig;

        string apn = apnProfile[apnIndex]["apn"].asString();
        apnProfileConfig->setApn(apn);

        unsigned int ctxId = apnProfile[apnIndex]["context-id"].asUInt();
        apnProfileConfig->setContextId(ctxId);

        string pdntype = apnProfile[apnIndex]["pdn-type"].asString();
        apnProfileConfig->setPdnType(pdntype);

        unsigned int class_value =
            apnProfile[apnIndex]["qos-profile"]["class"].asUInt();

        unsigned int air =
            apnProfile[apnIndex]["qos-profile"]["allocation-retention-priority"].asUInt();
        apnProfileConfig->setQosProfile(class_value, air);

        string tgppChargChara =
            apnProfile[apnIndex]["3gpp-charging-characteristics"].asString();
        apnProfileConfig->setTgppChargData(tgppChargChara);

        unsigned int maxDlBw =
            apnProfile[apnIndex]["max-dl-bandwidth"].asUInt();
        apnProfileConfig->setMaxDlBw(maxDlBw);

        unsigned int maxUlBw =
            apnProfile[apnIndex]["max-ul-bandwidth"].asUInt();
        apnProfileConfig->setMaxUlBw(maxUlBw);

        string apnOR = apnProfile[apnIndex]["apn-oi-replacement"].asString();
        apnProfileConfig->setApnOiRepl(apnOR);

        /*cout<<(apnProfileConfig->getContextId())<<endl;
        cout<<(apnProfileConfig->getPdnType())<<endl;
        cout<<(apnProfileConfig->getMaxDlBw())<<endl;
        cout<<(apnProfileConfig->getMaxUlBw())<<endl;
        cout<<(apnProfileConfig->getApn())<<endl;
        cout<<(apnProfileConfig->getTgppChargData())<<endl;
        cout<<(apnProfileConfig->getApnOiRepl())<<endl;
        unsigned int x,y;
        apnProfileConfig->getQosProfile(x,y);
        cout<<x<<":"<<y<<endl;*/
    }

    const Json::Value subscTmplts = (*root)["subscriber-templates"];
    for(int subIndex = 0; subIndex < subscTmplts.size(); subIndex++)
    {
        SubTemplate *subTemplate = new SubTemplate;

        string template_name = subscTmplts[subIndex]["template"].asString();
        subTemplate->setTemplateName(template_name);

        const Json::Value arData = subscTmplts[subIndex]["access-restriction"];
        unsigned int accessRestriction = populateAccessRestriction(arData);
        subTemplate->setAccessRestriction(accessRestriction);

        string aOR = subscTmplts[subIndex]["apn-oi-replacement"].asString();
        subTemplate->setAor(aOR);

        string tgppChargChara =
            subscTmplts[subIndex]["3gpp-charging-characteristics"].asString();
        subTemplate->setTgppChargChara(tgppChargChara);

        unsigned int maxDlBw =
            subscTmplts[subIndex]["max-dl-bandwidth"].asUInt();
        subTemplate->setMaxDlBw(maxDlBw);

        unsigned int maxUlBw =
            subscTmplts[subIndex]["max-ul-bandwidth"].asUInt();
        subTemplate->setMaxUlBw(maxUlBw);

        unsigned int dAC =
            subscTmplts[subIndex]["default-apn-context"].asUInt();
        subTemplate->setDac(dAC);
        
        const Json::Value data = subscTmplts[subIndex]["apn-profiles"];
        for(int i = 0; i < data.size(); i++)
        {
            subTemplate->setApnProfiles(data[i].asString());
        }

        /*vector<string> test = subTemplate->getApnProfiles();
        vector<string>::const_iterator it;
        for(it = test.begin();it != test.end(); it++)
        {
            cout<<(*it)<<endl;
        }*/
    }

    const Json::Value subscRes = (*root)["subscriber-registry"];
    for(int subRegIndex = 0; subRegIndex < subscRes.size(); subRegIndex++)
    {
        SubRegistry *subRegistry = new SubRegistry;

        string imsi = subscRes[subRegIndex]["imsi"].asString();
        subRegistry->setImsi(imsi);

        string msisdn = subscRes[subRegIndex]["msisdn"].asString();
        subRegistry->setMsisdn(msisdn);

        string xres = subscRes[subRegIndex]["XRES"].asString();
        subRegistry->setXRES(xres);

        string autn = subscRes[subRegIndex]["AUTN"].asString();
        subRegistry->setAUTN(autn);

        string kasme = subscRes[subRegIndex]["KASME"].asString();
        subRegistry->setKASME(kasme);

        string template_name = subscRes[subRegIndex]["template"].asString();
        subRegistry->setTemplateName(template_name);

        // cout<<subRegistry->getTemplateName()<<endl;
    }

    const Json::Value eirData = (*root)["equipment-identity-registry"];
    for(int eirIndex = 0; eirIndex < eirData.size(); eirIndex++)
    {
        EIR *eir = new EIR;

        string imei = eirData[eirIndex]["imei"].asString();
        eir->setImei(imei);

        string status = eirData[eirIndex]["status"].asString();
        {
            if(eirData[eirIndex]["status"].asString() == "whitelisted")
            {
                eir->setStatus(WHITELISTED);
            }
            else if(eirData[eirIndex]["status"].asString() == "blacklisted")
            {
                eir->setStatus(BLACKLISTED);
            }
            else if(eirData[eirIndex]["status"].asString() == "greylisted")
            {
                eir->setStatus(GREYLISTED);
            }
        }
        // cout<<eir->getStatus()<<endl;
    }
}

unsigned int populateFeatures(const Json::Value &featureData)
{
    unsigned int featureValue = 0x00000000;

    for(int featureIndex = 0; featureIndex < featureData.size(); featureIndex++)
    {

        if(featureData[featureIndex].asString() == "ODB-all-APN")
        {
            featureValue |= ODBallAPN;
        }
        else if(featureData[featureIndex].asString() == "ODB-HPLMN-APN")
        {
            featureValue |= ODB_HPLMN_APN;
        }
        else if(featureData[featureIndex].asString() == "ODB-VPLMN-APN")
        {
            featureValue |= ODB_VPLMN_APN;
        }
        else if(featureData[featureIndex].asString() == "ODB-all-OG")
        {
            featureValue |= ODBallOG;
        }
        else if(featureData[featureIndex].asString() == "ODB-all-InternationalOG")
        {
            featureValue |= ODBallInternationalOG;
        }
        else if(featureData[featureIndex].asString() ==
                "ODB-all-InternationalOGNotToHPLMN-Country")
        {
            featureValue |= ODBallInternationalOGNotToHPLMNCountry;
        }
        else if(featureData[featureIndex].asString() == "ODB-all-InterzonalOG")
        {
            featureValue |= ODBallInterzonalOG;
        }
        else if(featureData[featureIndex].asString() ==
                "ODB-all-InterzonalOGNotToHPLMN-Country")
        {
            featureValue |= ODBallInterzonalOGNotToHPLMNCountry;
        }
        else if(featureData[featureIndex].asString() ==
                "ODB-all-InterzonalOGAndInternationalOGNotToHPLMN-Country")
        {
            featureValue |=
                ODBallInterzonalOGAndInternationalOGNotToHPLMNCountry;
        }
        else if(featureData[featureIndex].asString() == "RegSub")
        {
            featureValue |= RegSub;
        }
        else if(featureData[featureIndex].asString() == "Trace")
        {
            featureValue |= Trace;
        }
        else if(featureData[featureIndex].asString() == "LCS-all-PrivExcep")
        {
            featureValue |= LCSallPrivExcep;
        }
        else if(featureData[featureIndex].asString() == "LCS-Universal")
        {
            featureValue |= LCSUniversal;
        }
        else if(featureData[featureIndex].asString() == "LCS-CallSessionRelated")
        {
            featureValue |= LCSCallSessionRelated;
        }
        else if(featureData[featureIndex].asString() ==
                "LCS-CallSessionUnrelated")
        {
            featureValue |= LCSCallSessionUnrelated;
        }
        else if(featureData[featureIndex].asString() == "LCS-PLMNOperator")
        {
            featureValue |= LCSPLMNOperator;
        }
        else if(featureData[featureIndex].asString() == "LCS-ServiceType")
        {
            featureValue |= LCSServiceType;
        }
        else if(featureData[featureIndex].asString() == "LCS-all-MOLR-SS")
        {
            featureValue |= LCSallMOLRSS ;
        }
        else if(featureData[featureIndex].asString() == "LCS-BasicSelfLocation")
        {
            featureValue |= LCSBasicSelfLocation ;
        }
        else if(featureData[featureIndex].asString() ==
                "LCS-AutonomousSelfLocation")
        {
            featureValue |= LCSAutonomousSelfLocation ;
        }
        else if(featureData[featureIndex].asString() == 
                "LCS-TransferToThirdParty")
        {
            featureValue |= LCSTransferToThirdParty;
        }
        else if(featureData[featureIndex].asString() == "SM-MO-PP")
        {
            featureValue |= SMMOPP;
        }
        else if(featureData[featureIndex].asString() == "Barring-OutgoingCalls")
        {
            featureValue |= BarringOutgoingCalls;
        }
        else if(featureData[featureIndex].asString() == "BAOC")
        {
            featureValue |= BAOC;
        }
        else if(featureData[featureIndex].asString() == "BOIC")
        {
            featureValue |= BOIC;
        }
        else if(featureData[featureIndex].asString() == "BOICExHC")
        {
            featureValue |= BOICExHC;
        }
        else if(featureData[featureIndex].asString() ==
                "UE-Reachability-Notification") 
        {
            featureValue |= UEReachabilityNotification;
        }
        else if(featureData[featureIndex].asString() == "T-ADSDataRetrieval")
        {
            featureValue |= TADSDataRetrieval;
        }
        else if(featureData[featureIndex].asString() ==
                "State/Location-Information-Retrieval")
        {
            featureValue |= StateLocationInformationRetrieval;
        }
        else if(featureData[featureIndex].asString() == "PartialPurge")
        {
            featureValue |= PartialPurge;
        }

    }        

    return featureValue;
}

unsigned int populateAccessRestriction(const Json::Value &arData)
{

    unsigned int accessRestriction = 0x00000000;

    for(int accessIndex = 0; accessIndex < arData.size(); accessIndex++)
    {
        if(arData[accessIndex].asString() == "NO-UTRAN")
        {
            accessRestriction |= NO_UTRAN;
        }
        else if(arData[accessIndex].asString() == "NO-GERAN")
        {
            accessRestriction |= NO_GERAN;
        }
        else if(arData[accessIndex].asString() == "NO-GAN")
        {
            accessRestriction |= NO_GAN;
        }
        else if(arData[accessIndex].asString() == "NO-I-HSPA-Evolution")
        {
            accessRestriction |= NO_I_HSPA_Evolution;
        }
        else if(arData[accessIndex].asString() == "NO-E-UTRAN")
        {
            accessRestriction |= NO_E_UTRAN;
        }
        else if(arData[accessIndex].asString() == "NO-HO-To-Non-3GPP-Access")
        {
            accessRestriction |= NO_HO_To_Non_3GPP_Access;
        }
    }

    return accessRestriction;
}
