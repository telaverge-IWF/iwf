//////////////////////////////////////////////////////////////////////////
// Have Few global constants in encoding the messages.
//
byte gImsi[]    = { 0x04, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF1 };
byte gHlrAddr[] = { 0x99, 0x99, 0x88, 0x88, 0x88 };
byte gMsIsdn[]  = { 0x66, 0x66, 0x77, 0x77, 0x88 };
byte gExtTele[] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};

std::vector<byte> gImsiList[4];

void BuildImsiList()
{
    byte a1[] = { 0x04, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0xF1 };
    byte a2[] = { 0x04, 0x55, 0x03, 0x00, 0x00, 0x00, 0x00, 0xF1 };
    byte a3[] = { 0x04, 0x55, 0x06, 0x00, 0x00, 0x00, 0x00, 0xF1 };

    gImsiList[0].insert(gImsiList[0].begin(), a1, a1 + sizeof(a1));
    gImsiList[1].insert(gImsiList[1].begin(), a2, a2 + sizeof(a2));
    gImsiList[2].insert(gImsiList[2].begin(), a3, a3 + sizeof(a3));
}

int GetRecvImsiIndex()
{
    static int index = 0;

    if (gRecvImsi.length() >= 15)
    {
        // We have strip here becase the IWFArray is sending some extra junk.
        gRecvImsi.erase(15, std::string::npos);
        if (gRecvImsi.compare("404120000000001") == 0)
        {
            return 0;
        }
        else if (gRecvImsi.compare("405530000000001") == 0)
        {
            return 1;
        }
        else if (gRecvImsi.compare("405560000000001") == 0)
        {
            return 2;
        }
    }

    index = (index++ % 3);

    return index;
}

Json::Value parseMapConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;
    char cwd[1024] = {0};
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        snprintf(cwd + strlen(cwd), 1024,"/map_tools.json");
        APP_TRACE_DEBUG(("current working directory= %s ",cwd));
        char *jsonFile = cwd;
        if (jsonFile == NULL )
        {
            APP_TRACE_ERROR(("map_tools.json is not present"));
            exit(0);
        }
        APP_TRACE_DEBUG(("MAP_IWF_JSON=%s",jsonFile));

        std::ifstream doc(jsonFile);
        bool ret = m_jsonConfigFileReader.parse(doc,m_jsonroot);
        if(ret == false)
        {
            APP_TRACE_ERROR(("Parsing of JSON Config file failed."));
        }
    }
    else
    {
        APP_TRACE_ERROR(("getcwd error, current path is not found"));
        exit(0);
    }
    return m_jsonroot;
}


AsnObject* BuildMapMsg(MAP_OPCODE opCode)
{
    AsnObject *obj = 0;

    switch (opCode)
    {
        case MAP_V13_UPDATE_LOC:
            obj = BuildUpdateLocV13();
            break; 

        case MAP_V13_UPDATE_LOC_RES:
            obj = BuildMapResMsgV13();
            break;

        case MAP_V13_INSERT_SUB_DATA:
            obj = BuildInsertSubDataV13();
            break;

        case MAP_V13_INSERT_SUB_DATA_RES:
            obj = BuildInsertSubscriberDataResV13();
            break;

        case MAP_V13_UPDATE_GPRS_LOC:
            obj = BuildUpdateGPRSLocV13();
            break;

        case MAP_V13_UPDATE_GPRS_LOC_RES:
            obj = BuildUpdateGPRSLocResV13();
            break;

        case MAP_V13_PROVIDE_SUB_INFO:
            obj = BuildProvideSubscriberInfoArgV13();
            break;

        case MAP_V13_PROVIDE_SUB_INFO_RES:
            obj = BuildProvideSubscriberInfoResV13();
            break;


        case MAP_V13_DELETE_SUB_DATA:
            obj = BuildDeleteSubscriberDatArgV13(); 
            break;

        case MAP_V13_DELETE_SUB_DATA_RES:
            obj = BuildDeleteSubscriberDatResV13(); 
            break;
            
        case MAP_V13_SEND_AUTHENTICATION_INFO_RES:
            obj = BuildSendAuthenticationInfoResV13();
            break;

        case MAP_V13_READY_FOR_SM_ARG:
            obj = BuildReadyForSM_ArgV13();
            break;

        case MAP_V13_READY_FOR_SM_RES:
            obj = BuildReadyForSM_ResV13();
            break;

        case MAP_V13_CANCEL_LOCATION:
            obj = BuildCancelLocationArgV13();
            break;

        case MAP_V13_CANCEL_LOCATION_RES:
            obj = BuildCancelLocationResV13();
            break;

        case MAP_V13_PURGEMS_RES:
            obj = BuildPurgeMSResV13();
            break;

        case MAP_V13_TRACE_ACTIVATE_MODE_ARG:
            obj = BuildTraceActivateModeArgV13();
            break;

        case MAP_V13_TRACE_ACTIVATE_MODE_RES:
            obj = BuildTraceActivateModeResV13();
            break;

        case MAP_V13_TRACE_DEACTIVATE_MODE_ARG:
            obj = BuildTraceDeActivateModeArgV13();
            break;

        case MAP_V13_TRACE_DEACTIVATE_MODE_RES:
            obj = BuildTraceDeActivateModeResV13();
            break;

        case MAP_V13_RESET_ARG:
            obj = BuildResetArg();
            break;

        case MAP_V13_PURGE_MS_ARG:
            obj = BuildPurgeMSArg(); 
            break;
        
        case MAP_V13_SEND_AUTH_INFO_ARG:
            obj = BuildSendAuthenticationInfoArg(); 
            break;
        
        case MAP_V3_SEND_ROUTING_INFO_ARG:
            obj = BuildSendRoutingInfoArgv3();
            break;

        case MAP_V3_SEND_ROUTING_INFO_RES:
            obj = BuildSendRoutingInfoResv3();
            break;

        case  MAP_V9_ROUTING_INFO_FOR_SM_ARG:
            obj = BuildSendRoutingInfoForSMArgv1();
            break;

        case MAP_V9_ROUTING_INFO_FOR_SM_RES:
            obj = BuildSendRoutingInfoForSMRes();
            break;
       
        case MAP_V9_PROVIDE_ROAMING_NUMBER_ARG:
            obj = BuildProvideRoamingNumberArgv9();
            break;

        case MAP_V9_PROVIDE_ROAMING_NUMBER_RES:
            obj = BuildProvideRoamingNumberResv9(); 

        default:
            break;
    }

    return obj;
}

AsnObject* BuildUpdateGPRSLocV13() {

    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string Imei = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationArg"];

    map_v13::UpdateGprsLocationArg *gprsa = new map_v13::UpdateGprsLocationArg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        gprsa->SetImsi(imsi);
    }

    isNull = (*cfg)["Sgsn_Number"]["Value"].isNull();
    if(!isNull)
    {
        uint8_t l_sgsnnumber[9] = {0};
        string sgsnnum = (*cfg)["Sgsn_Number"]["Value"].asString();

        if(sgsnnum.length() > MAX_ISDN_ADDRESS_DIGITS)
        {
            sgsnnum.erase(MAX_ISDN_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(sgsnnum.substr(0, MAX_ISDN_ADDRESS_HEADER_LENGTH), 
                l_sgsnnumber, MAX_ISDN_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(sgsnnum.substr(MAX_ISDN_ADDRESS_HEADER_LENGTH), (l_sgsnnumber+1), MAX_ISDN_ADDRESS_DIGITS);
        if (sgsnnum.length() % 2)
        {
            l_sgsnnumber[(sgsnnum.length() / 2)] |= 0xF0;
        }
 
        map_v13::ISDN_AddressString sgsnnu(MAPUtils::ByteArrayToVector(l_sgsnnumber, len));
        gprsa->SetSgsn_Number(sgsnnu);
    }

    isNull = (*cfg)["Sgsn_Address"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::GSN_Address gsnadr(MAPUtils::StringToVector((*cfg)["Sgsn_Address"]["Value"].asString()));
        gprsa->SetSgsn_Address(gsnadr);
    }

    isNull = (*cfg)["EPS_Info"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["EPS_Info"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::EPS_Info epsinfo;
        isAVPEnabled = (*cfg)["EPS_Info"]["ISR_Information"]["Enabled"].asBool();
        isNull = (*cfg)["EPS_Info"]["ISR_Information"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ISR_Information isr(MAPUtils::UnsignedToBitVector(((*cfg)["EPS_Info"]["ISR_Information"]["Value"].asInt()),8));
            epsinfo.SetChoiceIsr_Information(isr);
        }
        else
        {
            isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["Enabled"].asBool();
            isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PDN_GW_Update  pdngwupdate;
                isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["APN"]["Enabled"].asBool();
                isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["APN"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::APN apn(MAPUtils::StringToVector((*cfg)["EPS_Info"]["PDN_GW_Update"]["APN"]["Value"].asString()));
                    pdngwupdate.SetApn(apn);
                }

                isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["Enabled"].asBool();
                isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::PDN_GW_Identity pdniden;

                    isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Enabled"].asBool();
                    isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        uint8_t ipv4[sizeof(struct in_addr)] = {0};
                        its::ByteArray pdpAddr;
                        string ipV4Add = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].asString();
                        int ret = inet_pton(AF_INET, ipV4Add.c_str(), ipv4);
                        if(ret == 1)
                        {
                            pdpAddr.assign(ipv4, ipv4 + (sizeof(struct in_addr)));
                        }
                        map_v13::PDP_Address pdnaddr(pdpAddr);
                        pdniden.SetPdn_gw_ipv4_Address(pdnaddr);
                    }

                    isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Enabled"].asBool();
                    isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        uint8_t ipv6[sizeof(struct in6_addr)] = {0};
                        its::ByteArray pdpAddr;
                        string ipV6Add = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].asString();
                        int ret = inet_pton(AF_INET6, ipV6Add.c_str(), ipv6);
                        if(ret == 1)
                        {
                            pdpAddr.assign(ipv6, ipv6 + (sizeof(struct in6_addr)));
                        }
 
                        map_v13::PDP_Address pdnaddr(pdpAddr);
                        pdniden.SetPdn_gw_ipv6_Address(pdnaddr);
                    }

                    isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_name"]["Enabled"].asBool();
                    isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::FQDN pdngwname(MAPUtils::StringToVector((*cfg)["EPS_Info"]["PDN_GW_Update"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].asString()));
                        pdniden.SetPdn_gw_name(pdngwname);
                    }

                    pdngwupdate.SetPdn_gw_Identity(pdniden);
                }

                isAVPEnabled = (*cfg)["EPS_Info"]["PDN_GW_Update"]["ContextId"]["Enabled"].asBool();
                isNull = (*cfg)["EPS_Info"]["PDN_GW_Update"]["ContextId"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::ContextId cid((*cfg)["EPS_Info"]["PDN_GW_Update"]["ContextId"]["Value"].asInt());
                    pdngwupdate.SetContextId(cid);
                }
                epsinfo.SetChoicePdn_gw_update(pdngwupdate);
            }
        }
        gprsa->SetEps_info(epsinfo);
    }

    isNull = (*cfg)["ServingNodeTypeIndicator"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["ServingNodeTypeIndicator"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::ServingNodeTypeIndicator snti;
        gprsa->SetServingNodeTypeIndicator(snti);
    }

    isNull = (*cfg)["SkipSubscriberDataUpdate"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["SkipSubscriberDataUpdate"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::SkipSubscriberDataUpdate ssdu;
        gprsa->SetSkipSubscriberDataUpdate(ssdu);
    }

    isNull = (*cfg)["GprsSubscriptionDataNotNeeded"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["GprsSubscriptionDataNotNeeded"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::GprsSubscriptionDataNotNeeded gsdnn;
        gprsa->SetGprsSubscriptionDataNotNeeded(gsdnn);
    }

    isNull = (*cfg)["NodeTypeIndicator"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["NodeTypeIndicator"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::NodeTypeIndicator nti;
        gprsa->SetNodeTypeIndicator(nti);
    }

    isNull = (*cfg)["Used_RAT_Type"]["Value"].isNull();
    isAVPEnabled = (*cfg)["Used_RAT_Type"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::Used_RAT_Type urat((*cfg)["Used_RAT_Type"]["Value"].asInt());
        gprsa->SetUsedRAT_Type(urat);
    }

    isNull = (*cfg)["sgsn_Capability"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["sgsn_Capability"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::SGSN_Capability sgsn;
        isNull = (*cfg)["sgsn_Capability"]["solsaSupportIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["solsaSupportIndicator"]["Value"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::SGSN_Capability::SolsaSupportIndicator ssi;
            sgsn.SetSolsaSupportIndicator(ssi);
        }
        isNull = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SuperChargerInfo scf;
            isNull = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["sendSubscriberData"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["sendSubscriberData"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::UpdateGprsLocationArg::SGSN_Capability::SuperChargerInfo::SendSubscriberData ssd;
                scf.SetChoiceSendSubscriberData(ssd);
            }
            bool isoptionalNull = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["subscriberDataStored"]["Value"].isNull();
            bool isoptionalAVPEnabled = (*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["subscriberDataStored"]["Value"].asBool();
            if(!isoptionalNull && isoptionalAVPEnabled && !isAVPEnabled)
            {
                map_v13::AgeIndicator ai(MAPUtils::StringToVector((*cfg)["sgsn_Capability"]["superChargerSupportedInServingNetworkEntity"]["subscriberDataStored"]["Value"].asString()));
                scf.SetChoiceSubscriberDataStored(ai);
            }
            sgsn.SetSuperChargerSupportedInServingNetworkEntity(scf);
        }
        isNull = (*cfg)["sgsn_Capability"]["gprsEnhancementsSupportIndicator"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["gprsEnhancementsSupportIndicator"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::SGSN_Capability::GprsEnhancementsSupportIndicator gesi;
            sgsn.SetGprsEnhancementsSupportIndicator(gesi);
        }
        isNull = (*cfg)["sgsn_Capability"]["supportedCamelPhases"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["supportedCamelPhases"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SupportedCamelPhases scp(MAPUtils::UnsignedToBitVector(((*cfg)["sgsn_Capability"]["supportedCamelPhases"]["Value"].asInt()),16));
            sgsn.SetSupportedCamelPhases(scp);
        }
        isNull = (*cfg)["sgsn_Capability"]["supportedLCS_CapabilitySets"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["supportedLCS_CapabilitySets"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SupportedLCS_CapabilitySets slc(MAPUtils::UnsignedToBitVector(((*cfg)["sgsn_Capability"]["supportedLCS_CapabilitySets"]["Value"].asInt()),16));
            sgsn.SetSupportedLCS_CapabilitySets(slc);
        }
        isNull = (*cfg)["sgsn_Capability"]["offeredCamel4CSIs"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["offeredCamel4CSIs"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::OfferedCamel4CSIs occsi(MAPUtils::UnsignedToBitVector(((*cfg)["sgsn_Capability"]["offeredCamel4CSIs"]["Value"].asInt()),16));
            sgsn.SetOfferedCamel4CSIs(occsi);
        }
        isNull = (*cfg)["sgsn_Capability"]["smsCallBarringSupportIndicator"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["smsCallBarringSupportIndicator"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::SGSN_Capability::SmsCallBarringSupportIndicator scb;
            sgsn.SetSmsCallBarringSupportIndicator(scb);
        }
        isNull = (*cfg)["sgsn_Capability"]["supportedRAT_TypesIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["supportedRAT_TypesIndicator"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SupportedRAT_Types srt(MAPUtils::UnsignedToBitVector(((*cfg)["sgsn_Capability"]["supportedRAT_TypesIndicator"]["Value"].asInt()),8));
            sgsn.SetSupportedRAT_TypesIndicator(srt);
        }
        isNull = (*cfg)["sgsn_Capability"]["supportedFeatures"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["supportedFeatures"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SupportedFeatures sf(MAPUtils::UnsignedToBitVector(((*cfg)["sgsn_Capability"]["supportedFeatures"]["Value"].asInt()),40));
            sgsn.SetSupportedFeatures(sf);
        }
        isNull = (*cfg)["sgsn_Capability"]["t_adsDataRetrieval"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["t_adsDataRetrieval"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::SGSN_Capability::T_adsDataRetrieval tad;
            sgsn.SetT_adsDataRetrieval(tad);
        }
        isNull = (*cfg)["sgsn_Capability"]["homogeneousSupportOfIMSVoiceOverPSSessions"]["Value"].isNull();
        isAVPEnabled = (*cfg)["sgsn_Capability"]["homogeneousSupportOfIMSVoiceOverPSSessions"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::SGSN_Capability::HomogeneousSupportOfIMSVoiceOverPSSessions hsoiv((*cfg)["sgsn_Capability"]["homogeneousSupportOfIMSVoiceOverPSSessions"]["Enabled"].asBool());
            sgsn.SetHomogeneousSupportOfIMSVoiceOverPSSessions(hsoiv);
        }
        gprsa->SetSgsn_Capability(sgsn);
    }
    isNull = (*cfg)["informPreviousNetworkEntity"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["informPreviousNetworkEntity"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::InformPreviousNetworkEntity ipne;
        gprsa->SetInformPreviousNetworkEntity(ipne);
    }
    isNull = (*cfg)["ps_LCS_NotSupportedByUE"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["ps_LCS_NotSupportedByUE"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::Ps_LCS_NotSupportedByUE pln;
        gprsa->SetPs_LCS_NotSupportedByUE(pln);
    }
    isNull = (*cfg)["v_gmlc_Address"]["Value"].isNull();
    isAVPEnabled = (*cfg)["v_gmlc_Address"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GSN_Address ga(MAPUtils::StringToVector((*cfg)["v_gmlc_Address"]["Value"].asString()));
        gprsa->SetV_gmlc_Address(ga);
    }
    isNull = (*cfg)["add_info"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["add_info"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ADD_Info addinfo;
        isNull = (*cfg)["add_info"]["imeisv"]["Value"].isNull();
        if(!isNull)
        {
            
        Imei = (*cfg)["add_info"]["imeisv"]["Value"].asString();
        if (Imei.length() >= 16)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imei.erase(16, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(Imei, l_imsi, MAP_MAX_E164_SZ);
        if (Imei.length() % 2)
        {
            l_imsi[(Imei.length() / 2)] |= 0xF0;
        }
        map_v13::IMEI imei(MAPUtils::ByteArrayToVector(l_imsi, len));
        addinfo.SetImeisv(imei);
        }
        isNull = (*cfg)["add_info"]["skipSubscriberDataUpdate"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["add_info"]["skipSubscriberDataUpdate"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UpdateGprsLocationArg::ADD_Info::SkipSubscriberDataUpdate ssd;
            addinfo.SetSkipSubscriberDataUpdate(ssd);
        }
        gprsa->SetAdd_info(addinfo);
    }
    isNull = (*cfg)["areaRestricted"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["areaRestricted"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::AreaRestricted ar;
        gprsa->SetAreaRestricted(ar);
    }
    isNull = (*cfg)["ue_reachableIndicator"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["ue_reachableIndicator"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::Ue_reachableIndicator ur;
        gprsa->SetUe_reachableIndicator(ur);
    }
    isNull = (*cfg)["epsSubscriptionDataNotNeeded"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["epsSubscriptionDataNotNeeded"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UpdateGprsLocationArg::EpsSubscriptionDataNotNeeded esdnn;
        gprsa->SetEpsSubscriptionDataNotNeeded(esdnn);
    }
    isNull = (*cfg)["ue_srvcc_Capability"]["Value"].isNull();
    isAVPEnabled = (*cfg)["ue_srvcc_Capability"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UE_SRVCC_Capability usr((*cfg)["ue_srvcc_Capability"]["Value"].asInt());
        gprsa->SetUe_srvcc_Capability(usr);
    }   
    
    return gprsa;
}

AsnObject* BuildUpdateGPRSLocResV13() {

    bool isNull;
    bool isAVPEnabled;

    Json::Value* cfg = &(*m_jsonRoot1)["UpdateGprsLocationRes"];

    map_v13::UpdateGprsLocationRes       *gprsl = new map_v13::UpdateGprsLocationRes();

    isNull = (*cfg)["hlr_number"]["Value"].isNull();
    if(!isNull)
    {
        std::vector<byte> iaddr = MAPUtils::StringToVector((*cfg)["hlr_number"]["Value"].asString());
        map_v13::ISDN_AddressString isdnAddr(iaddr);
        gprsl->SetHlr_Number(isdnAddr);
    }   

    isNull = (*cfg)["Sgsn_mmeSeparationSupported"]["Enabled"].isNull();
    if(!isNull)
    {  
        isAVPEnabled = (*cfg)["Sgsn_mmeSeparationSupported"]["Enabled"].asBool();
        if(isAVPEnabled)
        {   
            map_v13::UpdateGprsLocationRes::Sgsn_mmeSeparationSupported smmeSupp;
            gprsl->SetSgsn_mmeSeparationSupported(smmeSupp);
        }   
    }   

    isNull = (*cfg)["Add_Capability"]["Enabled"].isNull();
    if(!isNull)
    {   
        isAVPEnabled = (*cfg)["Add_Capability"]["Enabled"].asBool();
        if(isAVPEnabled)
        {   
            map_v13::UpdateGprsLocationRes::Add_Capability addCap;
            gprsl->SetAdd_Capability(addCap);
        }   
    }   


   /*map_v13::UpdateGprsLocationRes::Sgsn_mmeSeparationSupported smmeSupp;
    map_v13::UpdateGprsLocationRes::Add_Capability              addCap;

    std::vector<byte> iaddr(gHlrAddr, gHlrAddr + sizeof(gHlrAddr));

    map_v13::ISDN_AddressString isdnAddr(iaddr);
    gprsl->SetHlr_Number(isdnAddr);

    gprsl->SetSgsn_mmeSeparationSupported(smmeSupp);
    gprsl->SetAdd_Capability(addCap);*/
   
    return gprsl;
}

AsnObject* BuildUpdateLocV13()
{
    int idx = GetRecvImsiIndex();
    map_v13::UpdateLocationArg *upArg = new map_v13::UpdateLocationArg();
    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);

    map_v13::IMSI               imsi(gImsiList[idx]);
    map_v13::ISDN_AddressString isdnAddr(iaddr);

    upArg->SetImsi(imsi);
    upArg->SetMsc_Number(isdnAddr);
    upArg->SetVlr_Number(isdnAddr);

    return upArg;
}

AsnObject* BuildSendRoutingInfoArgv3(){
    
    bool isNull;
    bool isAVPEnabled;
    
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["SendRoutingInfoArg"];

    map_v9::SendRoutingInfoArg *sriarg = new map_v9::SendRoutingInfoArg();
    
    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);
    map_v9::ISDN_AddressString isdnAddr(iaddr);
    sriarg->SetMsisdn(iaddr);
    
    isAVPEnabled = (*cfg)["InterrogationType"]["Enabled"].asBool();
    isNull = (*cfg)["InterrogationType"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        sriarg->SetInterrogationType(new map_v9::InterrogationType((*cfg)["InterrogationType"]["Value"].asInt()));
    }

    map_v9::ISDN_AddressString gmscAddress(MAPUtils::StringToVector("456788"));
    sriarg->SetGmsc_OrGsmSCF_Address(gmscAddress);

    isAVPEnabled = (*cfg)["NumberOfForwarding"]["Enabled"].asBool();
    isNull = (*cfg)["NumberOfForwarding"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::NumberOfForwarding numberOfForwarding((*cfg)["NumberOfForwarding"]["Value"].asInt());
        sriarg->SetNumberOfForwarding(numberOfForwarding);
    }
 
    isAVPEnabled = (*cfg)["Or-Interrogation"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::Or_Interrogation orinull;
        sriarg->SetOr_Interrogation(orinull);
    }
 
    isAVPEnabled = (*cfg)["Or-Capability"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::OR_Phase orcap((*cfg)["OR-Capability"]["Value"].asInt());
        sriarg->SetOr_Capability(orcap);
    }
    
    isAVPEnabled = (*cfg)["CallReferenceNumber"]["Enabled"].asBool();
    isNull = (*cfg)["CallReferenceNumber"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::CallReferenceNumber callrefno(MAPUtils::StringToVector((*cfg)["CallReferenceNumber"]["Value"].asString()));
        sriarg->SetCallReferenceNumber(callrefno);
    }

    isAVPEnabled = (*cfg)["ForwardingReason"]["Enabled"].asBool();
    isNull = (*cfg)["ForwardingReason"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        sriarg->SetForwardingReason(new map_v9::ForwardingReason((*cfg)["ForwardingReason"]["Value"].asInt()));
    }
    
    isAVPEnabled = (*cfg)["NetworkSignalInfo"]["Enabled"].asBool();
    isNull = (*cfg)["NetworkSignalInfo"]["Value"].isNull();
    /*if(!isNull && isAVPEnabled)
    {
       sriarg->SetNetworkSignalInfo(new  map_v9::ExternalSignalInfo((*cfg)["NetworkSignalInfo"]["Value"].asInt()));
    }

    isAVPEnabled = (*cfg)["CamelInfo"]["Enabled"].asBool();
    isNull = (*cfg)["CamelInfo"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::CamelInfo camelInfo((*cfg)["CamelInfo"]["Value"].asString());
        sriarg->SetCamelInfo(camelInfo);
    }
*/ 
    isAVPEnabled = (*cfg)["suppressionOfAnnouncement"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::SuppressionOfAnnouncement  supnull;
        sriarg->SetSuppressionOfAnnouncement(supnull);
    }

    isAVPEnabled = (*cfg)["AlertingPattern"]["Enabled"].asBool();
    isNull = (*cfg)["AlertingPattern"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::AlertingPattern alertPattern(MAPUtils::StringToVector((*cfg)["AlertingPattern"]["Value"].asString()));
        sriarg->SetAlertingPattern(alertPattern);
    }

    isAVPEnabled = (*cfg)["Ccbs-Call"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::Ccbs_Call ccbsnull;
        sriarg->SetCcbs_Call(ccbsnull);
    }

    isAVPEnabled = (*cfg)["Pre-pagingSupported"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::Pre_pagingSupported ccbsnull;
        sriarg->SetPre_pagingSupported(ccbsnull);
    }

    isAVPEnabled = (*cfg)["LongFTN-Supported"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::LongFTN_Supported longftnnull;
        sriarg->SetLongFTN_Supported(longftnnull);
    }

    isAVPEnabled = (*cfg)["Suppress-VT-CSI"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::Suppress_VT_CSI suppressnull;
        sriarg->SetSuppress_VT_CSI(suppressnull);
    }

    isAVPEnabled = (*cfg)["SuppressIncomingCallBarring"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::SuppressIncomingCallBarring suppressIncomingnull;
        sriarg->SetSuppressIncomingCallBarring(suppressIncomingnull);
    }

    isAVPEnabled = (*cfg)["GsmSCF-InitiatedCall"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::SendRoutingInfoArg::GsmSCF_InitiatedCall   gsmnull;
        sriarg->SetGsmSCF_InitiatedCall(gsmnull);
    }
/* 
    isAVPEnabled = (*cfg)["NetworkSignalInfo2"]["Enabled"].asBool();
    isNull = (*cfg)["NetworkSignalInfo2"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        sriarg->SetNetworkSignalInfo2(new map_v9::ExternalSignalInfo((*cfg)["NetworkSignalInfo2"]["Value"].asInt()));
    }


    isAVPEnabled = (*cfg)["BasicServiceGroup2"]["Enabled"].asBool();
    isNull = (*cfg)["BasicServiceGroup2"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::Ext_BasicServiceCode basicservergroup2(MAPUtils::StringToVector((*cfg)["BasicServiceGroup2"]["Value"].asString()));
        sriarg->SetBasicServiceGroup2(basicservergroup2);
    }
*/
    isAVPEnabled = (*cfg)["SupportedCCBS-Phase"]["Enabled"].asBool();
    isNull = (*cfg)["SupportedCCBS-Phase"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        sriarg->SetSupportedCCBS_Phase(new map_v9::SupportedCCBS_Phase((*cfg)["SupportedCCBS-Phase"]["Value"].asInt()));
    }

    isAVPEnabled = (*cfg)["IstSupportIndicator"]["Enabled"].asBool();
    isNull = (*cfg)["IstSupportIndicator"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        sriarg->SetIstSupportIndicator(new map_v9::IST_SupportIndicator((*cfg)["IstSupportIndicator"]["Value"].asInt()));
    }

    isAVPEnabled = (*cfg)[""]["Enabled"].asBool();
    isNull = (*cfg)[""]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v9::CallDiversionTreatmentIndicator calldiv(MAPUtils::StringToVector((*cfg)[""]["Value"].asString()));
        sriarg->SetCallDiversionTreatmentIndicator(calldiv);
    }




    return sriarg;
}

AsnObject* BuildSendRoutingInfoForSMArgv1(){
    map_v9::RoutingInfoForSM_Arg  *srifsma = new map_v9::RoutingInfoForSM_Arg();
    
    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);
    map_v9::ISDN_AddressString isdnAddr(iaddr);
    srifsma->SetMsisdn(iaddr);
    
    map_v9::AddressString Addr(iaddr); 
    srifsma->SetServiceCentreAddress(Addr);

    map_v9::RoutingInfoForSM_Arg::Sm_RP_PRI smrppri(true);
    srifsma->SetSm_RP_PRI(smrppri);

    return srifsma;
}

AsnObject* BuildSendRoutingInfoForSMRes(){

    map_v9::RoutingInfoForSM_Res *srifsmr = new map_v9::RoutingInfoForSM_Res();
    std::vector<byte>          l_imsi(gImsi, gImsi +8);
    map_v9::IMSI   imsi(l_imsi);
    srifsmr->SetImsi(imsi);

    return srifsmr;
}


AsnObject* BuildSendRoutingInfoResv3(){

    map_v9::SendRoutingInfoRes *srires = new map_v9::SendRoutingInfoRes();
   
    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);
	std::vector<byte>          l_imsi(gImsi, gImsi +8);
	map_v9::IMSI               imsi(l_imsi);
   
    srires->SetImsi(imsi);

    map_v9::ExtendedRoutingInfo extrinfo;
    srires->SetExtendedRoutingInfo(extrinfo);

    map_v9::ISDN_AddressString vmsc_addr;
    srires->SetVmsc_Address(vmsc_addr);

    return srires;
}

AsnObject* BuildMapResMsgV13()
{
    map_v13::UpdateLocationRes *upRes = new map_v13::UpdateLocationRes();
    std::vector<byte> addrStr(gHlrAddr, gHlrAddr + 5);

    map_v13::ISDN_AddressString hlrNum(addrStr);

    upRes->SetHlr_Number(hlrNum);
    return upRes;
}

AsnObject* BuildInsertSubDataV13()
{

    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["InsertSubscriberDataArg"];

    map_v13::InsertSubscriberDataArg *isdArg =
                            new map_v13::InsertSubscriberDataArg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    isAVPEnabled = (*cfg)["IMSI"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        isdArg->SetImsi(imsi);
    }

    isNull = (*cfg)["SubscriberData"].isNull();
    if(!isNull)
    {
        isNull = (*cfg)["SubscriberData"]["SubscriberStatus"]["Value"].isNull();
        isAVPEnabled = (*cfg)["SubscriberData"]["SubscriberStatus"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SubscriberStatus subStatus((*cfg)["SubscriberData"]["SubscriberStatus"]["Value"].asInt());
            isdArg->SetSubscriberStatus(subStatus);
        }
        
        isNull = (*cfg)["SubscriberData"]["msisdn"]["Value"].isNull();
        isAVPEnabled = (*cfg)["SubscriberData"]["msisdn"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ISDN_AddressString  msisdn(MAPUtils::StringToVector((*cfg)["SubscriberData"]["msisdn"]["Value"].asString()));
            isdArg->SetMsisdn(msisdn);
        }

        isNull = (*cfg)["SubscriberData"]["ODB_Data"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["SubscriberData"]["ODB_Data"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ODB_Data odb_data;
            isNull = (*cfg)["SubscriberData"]["ODB_Data"]["ODB_GeneralData"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::ODB_GeneralData odb_gendata(MAPUtils::UnsignedToBitVector(((*cfg)["SubscriberData"]["ODB_Data"]["ODB_GeneralData"]["Value"].asInt()),32));
                odb_data.SetOdb_GeneralData(odb_gendata);
            }

            isAVPEnabled = (*cfg)["SubscriberData"]["ODB_Data"]["ODB_HPLMN_Data"]["Enabled"].asBool();
            isNull = (*cfg)["SubscriberData"]["ODB_Data"]["ODB_HPLMN_Data"]["Value"].isNull();
            if((!isNull) && isAVPEnabled)
            {

                map_v13::ODB_HPLMN_Data hplmn_data(MAPUtils::UnsignedToBitVector(((*cfg)["SubscriberData"]["ODB_Data"]["ODB_HPLMN_Data"]["Value"].asInt()),32));
                odb_data.SetOdb_HPLMN_Data(hplmn_data);
            }
            isdArg->SetOdb_Data(odb_data);
        }

        isNull = (*cfg)["SubscriberData"]["regionalSubscriptionData"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["SubscriberData"]["regionalSubscriptionData"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ZoneCodeList zcl;
            isNull = (*cfg)["SubscriberData"]["regionalSubscriptionData"]["ZoneCode"].isNull();
            if(!isNull)
            {
                map_v13::ZoneCode zc(MAPUtils::StringToVector((*cfg)["SubscriberData"]["regionalSubscriptionData"]["ZoneCode"]["Value"].asString()));
                zcl.AddElement(zc);
                isdArg->SetRegionalSubscriptionData(zcl);
            }
        }

        isNull = (*cfg)["SubscriberData"]["TeleserviceList"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["SubscriberData"]["TeleserviceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TeleserviceList telServ;
            int num = (*cfg)["SubscriberData"]["TeleserviceList"]["number_of_times"].asInt();
            for(int i = 0; i < num; i++)
            {
                isNull = (*cfg)["SubscriberData"]["TeleserviceList"]["Ext_TeleserviceCode"].isNull();
                if(!isNull)
                {
                    map_v13::Ext_TeleserviceCode extService(MAPUtils::StringToVector((*cfg)["SubscriberData"]["TeleserviceList"]["Ext_TeleserviceCode"]["Value"].asString()));
                    telServ.AddElement(extService);
                }
            }
            if(num)
                isdArg->SetTeleserviceList(telServ);
        }
    }

    isNull = (*cfg)["EPS_SubscriptionData"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::EPS_SubscriptionData epsdata;
        isNull = (*cfg)["EPS_SubscriptionData"]["stn_sr"]["Value"].isNull();
        isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["stn_sr"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            std::vector<byte> iaddr = MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["stn_sr"]["Value"].asString());
            map_v13::ISDN_AddressString isdnAddr(iaddr);
            epsdata.SetStn_sr(isdnAddr);
        }

        isNull = (*cfg)["EPS_SubscriptionData"]["APN_OI_Replacement"]["Value"].isNull();
        isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_OI_Replacement"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            std::vector<byte> apnoi = MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_OI_Replacement"]["Value"].asString());
            map_v13::APN_OI_Replacement apnoirep(apnoi);
            epsdata.SetApn_oi_Replacement(apnoirep);
        }

        isNull = (*cfg)["EPS_SubscriptionData"]["AMBR"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["AMBR"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::AMBR ambr;
            isNull = (*cfg)["EPS_SubscriptionData"]["AMBR"]["max_RequestedBandwidth_UL"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::Bandwidth bwul((*cfg)["EPS_SubscriptionData"]["AMBR"]["max_RequestedBandwidth_UL"]["Value"].asInt());
                ambr.SetMax_RequestedBandwidth_UL(bwul);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["AMBR"]["max_RequestedBandwidth_DL"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::Bandwidth bwdl((*cfg)["EPS_SubscriptionData"]["AMBR"]["max_RequestedBandwidth_DL"]["Value"].asInt());
                ambr.SetMax_RequestedBandwidth_DL(bwdl);
            }

            epsdata.SetAmbr(ambr);
        }

        isNull = (*cfg)["EPS_SubscriptionData"]["RFSP_ID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["RFSP_ID"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RFSP_ID rfspid((*cfg)["EPS_SubscriptionData"]["RFSP_ID"]["Value"].asInt());
            epsdata.SetRfsp_id(rfspid);
        }

        isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::APN_ConfigurationProfile apncp;
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["ContextId"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::ContextId cId((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["ContextId"]["Value"].asInt());
                apncp.SetDefaultContext(cId);
            }
            
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["CompleteDataListIncluded"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["CompleteDataListIncluded"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::APN_ConfigurationProfile::CompleteDataListIncluded cdi;
                apncp.SetCompleteDataListIncluded(cdi);
            }
            
            map_v13::EPS_DataList epsdl;
            map_v13::APN_Configuration apnconf;

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ContextId"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::ContextId cId((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ContextId"]["Value"].asInt());
                apnconf.SetContextId(cId);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_Type"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::PDN_Type pdnt(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_Type"]["Value"].asString()));
                apnconf.SetPdn_Type(pdnt);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ServedPartyIP_IPv4_Address"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ServedPartyIP_IPv4_Address"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                uint8_t ipv4[sizeof(struct in_addr)] = {0};
                its::ByteArray pdpAddr;
                string ipV4Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ServedPartyIP_IPv4_Address"]["Value"].asString();
                int ret = inet_pton(AF_INET, ipV4Add.c_str(), ipv4);
                if(ret == 1)
                {
                    pdpAddr.assign(ipv4, ipv4 + (sizeof(struct in_addr)));
                }
                map_v13::PDP_Address pdnaddr(pdpAddr);
                apnconf.SetServedPartyIP_IPv4_Address(pdnaddr);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["APN"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::APN apn(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["APN"]["Value"].asString()));
                apnconf.SetApn(apn);
            }
            
            map_v13::EPS_QoS_Subscribed epsqos;
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["QoS_Class_Identifier"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::QoS_Class_Identifier qoscid((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["QoS_Class_Identifier"]["Value"].asInt());
                epsqos.SetQos_Class_Identifier(qoscid);
            }
            map_v13::Allocation_Retention_Priority arp;
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["priority-level"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::Allocation_Retention_Priority::Priority_level pl((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["priority-level"]["Value"].asInt());
                arp.SetPriority_level(pl);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_capability"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_capability"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::Allocation_Retention_Priority::Pre_emption_capability pec((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_capability"]["Value"].asBool());
                arp.SetPre_emption_capability(pec);
            }
            
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_vulnerability"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_vulnerability"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::Allocation_Retention_Priority::Pre_emption_vulnerability pev((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["EPS_QoS_Subscribed"]["Allocation_Retention_Priority"]["pre_emption_vulnerability"]["Value"].asBool());
                arp.SetPre_emption_vulnerability(pev);
            }

            epsqos.SetAllocation_Retention_Priority(arp);
            apnconf.SetEps_qos_Subscribed(epsqos);

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PDN_GW_Identity pdngwid;

                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].isNull();
                isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    uint8_t ipv4[sizeof(struct in_addr)] = {0};
                    its::ByteArray pdpAddr;
                    string ipV4Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].asString();
                    int ret = inet_pton(AF_INET, ipV4Add.c_str(), ipv4);
                    if(ret == 1)
                    {
                        pdpAddr.assign(ipv4, ipv4 + (sizeof(struct in_addr)));
                    }
                    map_v13::PDP_Address pdnaddr(pdpAddr);
                    pdngwid.SetPdn_gw_ipv4_Address(pdnaddr);
                }

                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].isNull();
                isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    uint8_t ipv6[sizeof(struct in6_addr)] = {0};
                    its::ByteArray pdpAddr;
                    string ipV6Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].asString();
                    int ret = inet_pton(AF_INET6, ipV6Add.c_str(), ipv6);
                    if(ret == 1)
                    {
                        pdpAddr.assign(ipv6, ipv6 + (sizeof(struct in6_addr)));
                    }

                    map_v13::PDP_Address pdnaddr(pdpAddr);
                    pdngwid.SetPdn_gw_ipv6_Address(pdnaddr);
                }

                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].isNull();
                isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_name"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::FQDN fqdn(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].asString()));
                    pdngwid.SetPdn_gw_name(fqdn);
                }
                apnconf.SetPdn_gw_Identity(pdngwid);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_AllocationType"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_AllocationType"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PDN_GW_AllocationType pdngwat((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["PDN_GW_AllocationType"]["Value"].asInt());
                apnconf.SetPdn_gw_AllocationType(pdngwat);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["VPLMNAddressAllowed"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["VPLMNAddressAllowed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::APN_Configuration::VplmnAddressAllowed vplmn;
                apnconf.SetVplmnAddressAllowed(vplmn);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ChargingCharacteristics"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ChargingCharacteristics"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["ChargingCharacteristics"]["Value"].asString()));
                apnconf.SetChargingCharacteristics(cc);
            }        

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::AMBR ambr;
                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["max_RequestedBandwidth_UL"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::Bandwidth bwul((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["max_RequestedBandwidth_UL"]["Value"].asInt());
                    ambr.SetMax_RequestedBandwidth_UL(bwul);
                }

                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["max_RequestedBandwidth_DL"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::Bandwidth bwdl((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["AMBR"]["max_RequestedBandwidth_DL"]["Value"].asInt());
                    ambr.SetMax_RequestedBandwidth_DL(bwdl);
                }

                apnconf.SetAmbr(ambr);
            }
            
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["Enabled"].asBool();
            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::SpecificAPNInfoList sapnil;
                map_v13::SpecificAPNInfo sapni;
                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["APN"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::APN apn(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["APN"]["Value"].asString()));
                    sapni.SetApn(apn);
                }

                isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::PDN_GW_Identity pdngwid;

                    isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].isNull();
                    isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Enabled"].asBool();
                    if((!isNull) && isAVPEnabled)
                    {
                        uint8_t ipv4[sizeof(struct in_addr)] = {0};
                        its::ByteArray pdpAddr;
                        string ipV4Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv4_Address"]["Value"].asString();
                        int ret = inet_pton(AF_INET, ipV4Add.c_str(), ipv4);
                        if(ret == 1)
                        {
                            pdpAddr.assign(ipv4, ipv4 + (sizeof(struct in_addr)));
                        }
                        map_v13::PDP_Address pdnaddr(pdpAddr);
                        pdngwid.SetPdn_gw_ipv4_Address(pdnaddr);
                    }

                    isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].isNull();
                    isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Enabled"].asBool();
                    if((!isNull) && isAVPEnabled)
                    {
                        uint8_t ipv6[sizeof(struct in6_addr)] = {0};
                        its::ByteArray pdpAddr;
                        string ipV6Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_ipv6_Address"]["Value"].asString();
                        int ret = inet_pton(AF_INET6, ipV6Add.c_str(), ipv6);
                        if(ret == 1)
                        {
                            pdpAddr.assign(ipv6, ipv6 + (sizeof(struct in6_addr)));
                        }

                        map_v13::PDP_Address pdnaddr(pdpAddr);
                        pdngwid.SetPdn_gw_ipv6_Address(pdnaddr);
                    }

                    isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].isNull();
                    isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_name"]["Enabled"].asBool();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::FQDN fqdn(MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["SpecificAPNInfoList"]["SpecificAPNInfo"]["PDN_GW_Identity"]["pdn_gw_name"]["Value"].asString()));
                        pdngwid.SetPdn_gw_name(fqdn);
                    }
                    sapni.SetPdn_gw_Identity(pdngwid);
                }

                sapnil.AddElement(sapni);
                apnconf.SetSpecificAPNInfoList(sapnil);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["servedPartyIP_IPv6_Address"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["servedPartyIP_IPv6_Address"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                uint8_t ipv6[sizeof(struct in6_addr)] = {0};
                its::ByteArray pdpAddr;
                string ipV6Add = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["servedPartyIP_IPv6_Address"]["Value"].asString();
                int ret = inet_pton(AF_INET6, ipV6Add.c_str(), ipv6);
                if(ret == 1)
                {
                    pdpAddr.assign(ipv6, ipv6 + (sizeof(struct in6_addr)));
                }

                map_v13::PDP_Address pdnaddr(pdpAddr);
                apnconf.SetServedPartyIP_IPv6_Address(pdnaddr); 
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["APN_OI_Replacement"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["APN_OI_Replacement"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> apnoi = MAPUtils::StringToVector((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["APN_OI_Replacement"]["Value"].asString());
                map_v13::APN_OI_Replacement apnoirep(apnoi);
                apnconf.SetApn_oi_Replacement(apnoirep);
            }

            isNull = (*cfg)["SIPTO_Permission"]["Value"].isNull();
            isAVPEnabled = (*cfg)["SIPTO_Permission"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::SIPTO_Permission sipto((*cfg)["SIPTO_Permission"]["Value"].asInt());
                apnconf.SetSipto_Permission(sipto);
            }

            isNull = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["LIPA_Permission"]["Value"].isNull();
            isAVPEnabled = (*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["LIPA_Permission"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::LIPA_Permission lipap((*cfg)["EPS_SubscriptionData"]["APN_ConfigurationProfile"]["EPS_DataList"]["APN_Configuration"]["LIPA_Permission"]["Value"].asInt());
                apnconf.SetLipa_Permission(lipap);
            }

            epsdl.AddElement(apnconf);
            apncp.SetEpsDataList(epsdl);
            epsdata.SetApn_ConfigurationProfile(apncp);
        }

        isdArg->SetEps_SubscriptionData(epsdata);
    }

    isNull = (*cfg)["NetworkAccessMode"]["Value"].isNull();
    isAVPEnabled = (*cfg)["NetworkAccessMode"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::NetworkAccessMode nam((*cfg)["NetworkAccessMode"]["Value"].asInt());
        isdArg->SetNetworkAccessMode(nam);
    }

    isNull = (*cfg)["ChargingCharacteristics"]["Value"].isNull();
    isAVPEnabled = (*cfg)["ChargingCharacteristics"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["ChargingCharacteristics"]["Value"].asString()));
        isdArg->SetChargingCharacteristics(cc);
    }

    isNull = (*cfg)["ue_ReachabilityRequestIndicator"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["ue_ReachabilityRequestIndicator"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::InsertSubscriberDataArg::Ue_ReachabilityRequestIndicator ur;
        isdArg->SetUe_ReachabilityRequestIndicator(ur);
    }

    isNull = (*cfg)["GPRSSubscriptionData"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GPRSSubscriptionData gprsSD;
        map_v13::GPRSDataList datalist;
        isNull = (*cfg)["GPRSSubscriptionData"]["CompleteDataListIncluded"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["CompleteDataListIncluded"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::GPRSSubscriptionData::CompleteDataListIncluded cdnull;
            gprsSD.SetCompleteDataListIncluded(cdnull);
        }

        isNull = (*cfg)["GPRSSubscriptionData"]["APN_OI_Replacement"]["Value"].isNull();
        isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["APN_OI_Replacement"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            std::vector<byte> apnoi = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["APN_OI_Replacement"]["Value"].asString());
            map_v13::APN_OI_Replacement apnoirep(apnoi);
            gprsSD.SetApn_oi_Replacement(apnoirep);
        }

        isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"].isNull();
        if(!isNull)
        {
            map_v13::PDP_Context  pdp;
           
            int num = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["number_of_times"].asInt();
            for(int i = 0; i < num; i++)
            {
                isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["ContextId"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::ContextId ctxtid((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["ContextId"]["Value"].asInt());
                    pdp.SetPdp_ContextId(ctxtid);

                }
            }


            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_Type"]["Value"].isNull();
            if(!isNull)
            {
                std::vector<byte> type = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_Type"]["Value"].asString());
                map_v13::PDP_Type  pdpty(type);
                pdp.SetPdp_Type(pdpty);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_Address"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_Address"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> pdpadd = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_Address"]["Value"].asString());
                map_v13::PDP_Address pdpAdd(pdpadd);
                pdp.SetPdp_Address(pdpAdd);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["QoS_Subscribed"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["QoS_Subscribed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> qos = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["QoS_Subscribed"]["Value"].asString());
                map_v13::QoS_Subscribed qoss(qos);
                pdp.SetQos_Subscribed(qoss);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["VPLMNAddressAllowed"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["VPLMNAddressAllowed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PDP_Context::VplmnAddressAllowed vplmn;
                pdp.SetVplmnAddressAllowed(vplmn);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["APN"]["Value"].isNull();
            if(!isNull)
            {
                std::vector<byte> apn = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["APN"]["Value"].asString());
                map_v13::APN  apno(apn);
                pdp.SetApn(apno);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_QoS_Subscribed"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_QoS_Subscribed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> eqoss = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_QoS_Subscribed"]["Value"].asString());
                map_v13::Ext_QoS_Subscribed eQoSs(eqoss);
                pdp.SetExt_QoS_Subscribed(eQoSs);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_ChargingCharacteristics"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_ChargingCharacteristics"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["PDP_ChargingCharacteristics"]["Value"].asString()));
                pdp.SetPdp_ChargingCharacteristics(cc);
            }        

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext2_QoS_Subscribed"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext2_QoS_Subscribed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> eqoss2 = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext2_QoS_Subscribed"]["Value"].asString());
                map_v13::Ext2_QoS_Subscribed eQoSs2(eqoss2);
                pdp.SetExt2_QoS_Subscribed(eQoSs2);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext3_QoS_Subscribed"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext3_QoS_Subscribed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> eqoss3 = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext3_QoS_Subscribed"]["Value"].asString());
                map_v13::Ext3_QoS_Subscribed eQoSs3(eqoss3);
                pdp.SetExt3_QoS_Subscribed(eQoSs3);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext4_QoS_Subscribed"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext4_QoS_Subscribed"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> eqoss4 = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext4_QoS_Subscribed"]["Value"].asString());
                map_v13::Ext4_QoS_Subscribed eQoSs4(eqoss4);
                pdp.SetExt4_QoS_Subscribed(eQoSs4);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["APN_OI_Replacement"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["APN_OI_Replacement"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> apnoi = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["APN_OI_Replacement"]["Value"].asString());
                map_v13::APN_OI_Replacement apnoirep(apnoi);
                pdp.SetApn_oi_Replacement(apnoirep);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Type"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Type"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> epdpt = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Type"]["Value"].asString());
                map_v13::Ext_PDP_Type ePdpt(epdpt);
                pdp.SetExt_pdp_Type(ePdpt);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Address"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Address"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                std::vector<byte> epdpa = MAPUtils::StringToVector((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["Ext_PDP_Address"]["Value"].asString());
                map_v13::PDP_Address ePdpa(epdpa);
                pdp.SetExt_pdp_Address(ePdpa);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["SIPTO_Permission"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["SIPTO_Permission"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::SIPTO_Permission sipto((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["SIPTO_Permission"]["Value"].asInt());
                pdp.SetSipto_Permission(sipto);
            }

            isNull = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["LIPA_Permission"]["Value"].isNull();
            isAVPEnabled = (*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["LIPA_Permission"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::LIPA_Permission lipap((*cfg)["GPRSSubscriptionData"]["GPRSDataList"]["PDP_Context"]["LIPA_Permission"]["Value"].asInt());
                pdp.SetLipa_Permission(lipap);
            }

            datalist.AddElement(pdp); 
        }

        gprsSD.SetGprsDataList(datalist);
        isdArg->SetGprsSubscriptionData(gprsSD);
    }

    isNull = (*cfg)["LCSInformation"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["LCSInformation"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LCSInformation lcsinfo;
        isNull = (*cfg)["LCSInformation"]["GMLC_List"]["ISDN-AddressString"]["Value"].isNull();
        isAVPEnabled = (*cfg)["LCSInformation"]["GMLC_List"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::GMLC_List gmlclist;
            map_v13::ISDN_AddressString isdn(MAPUtils::StringToVector((*cfg)["LCSInformation"]["GMLC_List"]["ISDN-AddressString"]["Value"].asString()));
            gmlclist.AddElement(isdn);
            lcsinfo.SetGmlc_List(gmlclist);
        }

        isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LCS_PrivacyExceptionList lcspel;
            map_v13::LCS_PrivacyClass lcspc;
            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["SS_Code"]["Value"].isNull();
            if(!isNull)
            {
                uint8_t l_ssc[1] = {0};
                std::string ssc = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["SS_Code"]["Value"].asString();
                if(ssc.length() > MAX_SS_CODE_DIGITS)
                {
                    ssc.erase(MAX_SS_CODE_DIGITS, std::string::npos);
                }

                int len = MAPUtils::StringToTBCD(ssc, l_ssc, MAX_SS_CODE_DIGITS, 0, true);

                map_v13::SS_Code sscode(MAPUtils::ByteArrayToVector(l_ssc, len));

                lcspc.SetSs_Code(sscode);
            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_SS_Status"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::Ext_SS_Status extsss(MAPUtils::StringToVector((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_SS_Status"]["Value"].asString()));
                lcspc.SetSs_Status(extsss);
            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["NotificationToMSUser"]["Value"].isNull();
            isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["NotificationToMSUser"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::NotificationToMSUser ntmtuser((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["NotificationToMSUser"]["Value"].asInt());
                lcspc.SetNotificationToMSUser(ntmtuser);
            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::ExternalClientList ecl;
                map_v13::ExternalClient ec;
                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                ["LCSClientExternalID"]["externalAddress"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                ["LCSClientExternalID"]["externalAddress"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::LCSClientExternalID lcseid;
                    map_v13::ISDN_AddressString extadd(MAPUtils::StringToVector((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]
                                                                                                ["ExternalClient"]["LCSClientExternalID"]["externalAddress"]["Value"].asString()));
                    lcseid.SetExternalAddress(extadd);
                    ec.SetClientIdentity(lcseid);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                ["GMLC_Restriction"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                ["GMLC_Restriction"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::GMLC_Restriction gmlcr((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                                                ["GMLC_Restriction"]["Value"].asInt());
                    ec.SetGmlc_Restriction(gmlcr);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                                    ["NotificationToMSUser"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                                    ["NotificationToMSUser"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::NotificationToMSUser ntmtuser((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ExternalClientList"]["ExternalClient"]
                                                                                    ["NotificationToMSUser"]["Value"].asInt());
                    ec.SetNotificationToMSUser(ntmtuser);
                }
                ecl.AddElement(ec);
                lcspc.SetExternalClientList(ecl);    

            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["PLMNClientList"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["PLMNClientList"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PLMNClientList plmncl;
                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["PLMNClientList"]["LCSClientInternalID"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["PLMNClientList"]["LCSClientInternalID"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::LCSClientInternalID lcsid((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["PLMNClientList"]["LCSClientInternalID"]["Value"].asInt());
                    plmncl.AddElement(lcsid);
                }
                lcspc.SetPlmnClientList(plmncl);
            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::Ext_ExternalClientList eecl;
                map_v13::ExternalClient ec1;
                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                ["LCSClientExternalID"]["externalAddress"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                ["LCSClientExternalID"]["externalAddress"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::LCSClientExternalID elcseid;
                    map_v13::ISDN_AddressString extadd(MAPUtils::StringToVector((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]
                                                                                                ["ExternalClient"]["LCSClientExternalID"]["externalAddress"]["Value"].asString()));
                    elcseid.SetExternalAddress(extadd);
                    ec1.SetClientIdentity(elcseid);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                ["GMLC_Restriction"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                ["GMLC_Restriction"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::GMLC_Restriction egmlcr((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                                                ["GMLC_Restriction"]["Value"].asInt());
                    ec1.SetGmlc_Restriction(egmlcr);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                                    ["NotificationToMSUser"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                                    ["NotificationToMSUser"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::NotificationToMSUser entmtuser((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["Ext_ExternalClientList"]["ExternalClient"]
                                                                                    ["NotificationToMSUser"]["Value"].asInt());
                    ec1.SetNotificationToMSUser(entmtuser);
                }
                eecl.AddElement(ec1);
                lcspc.SetExt_externalClientList(eecl);    

            }

            isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"].isNull();
            if(!isNull)
            {
                map_v13::ServiceTypeList stl;
                map_v13::ServiceType st;
                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]["LCSServiceTypeID"]["Value"].isNull();
                if(!isNull)
                {
                    map_v13::LCSServiceTypeID lcsid((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]
                                                                                                ["LCSServiceTypeID"]["Value"].asInt());
                    st.SetServiceTypeIdentity(lcsid);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]["GMLC_Restriction"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]["GMLC_Restriction"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::GMLC_Restriction gmlcr((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]
                                                                                            ["ServiceType"]["GMLC_Restriction"]["Value"].asInt());
                    st.SetGmlc_Restriction(gmlcr);
                }

                isNull = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]["NotificationToMSUser"]["Value"].isNull();
                isAVPEnabled = (*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]["ServiceTypeList"]["ServiceType"]["NotificationToMSUser"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::NotificationToMSUser ntmtuser((*cfg)["LCSInformation"]["LCS_PrivacyExceptionList"]["LCS_PrivacyClass"]
                                                                ["ServiceTypeList"]["ServiceType"]["NotificationToMSUser"]["Value"].asInt());
                    st.SetNotificationToMSUser(ntmtuser);
                }
                stl.AddElement(st);
                lcspc.SetServiceTypeList(stl);
            }
            
            lcspel.AddElement(lcspc);
            lcsinfo.SetLcs_PrivacyExceptionList(lcspel);
        }
    
        isNull = (*cfg)["LCSInformation"]["MOLR_List"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["LCSInformation"]["MOLR_List"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MOLR_List molrl;
            map_v13::MOLR_Class molrc;
            isNull = (*cfg)["LCSInformation"]["MOLR_List"]["MOLR_Class"]["SS_Code"]["Value"].isNull();
            if(!isNull)
            {
                uint8_t l_ssc[1] = {0};
                std::string ssc = (*cfg)["LCSInformation"]["MOLR_List"]["MOLR_Class"]["SS_Code"]["Value"].asString();
                if(ssc.length() > MAX_SS_CODE_DIGITS)
                {
                    ssc.erase(MAX_SS_CODE_DIGITS, std::string::npos);
                }

                int len = MAPUtils::StringToTBCD(ssc, l_ssc, MAX_SS_CODE_DIGITS, 0, true);

                map_v13::SS_Code sscode(MAPUtils::ByteArrayToVector(l_ssc, len));

                molrc.SetSs_Code(sscode);
            }

            isNull = (*cfg)["LCSInformation"]["MOLR_List"]["MOLR_Class"]["Ext_SS_Status"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::Ext_SS_Status extsss(MAPUtils::StringToVector((*cfg)["LCSInformation"]["MOLR_List"]["MOLR_Class"]["Ext_SS_Status"]["Value"].asString()));
                molrc.SetSs_Status(extsss);
            }
            molrl.AddElement(molrc);
            lcsinfo.SetMolr_List(molrl);
        }
        isdArg->SetLcsInformation(lcsinfo);
    }

    isNull = (*cfg)["CSG_SubscriptionDataList"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CSG_SubscriptionDataList"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::CSG_SubscriptionDataList csgsdl;
        isNull = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"].isNull();
        if(!isNull)
        {
            map_v13::CSG_SubscriptionData csgsd;
            isNull = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["CSG_Id"]["Value"].isNull();
            if(!isNull)
            {   
                map_v13::CSG_Id csgid(MAPUtils::UnsignedToBitVector(((*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["CSG_Id"]["Value"].asInt()),27));
                csgsd.SetCsg_Id(csgid);
            }

            isNull = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["expirationDate"]["Value"].isNull();
            isAVPEnabled = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["expirationDate"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::Time time(MAPUtils::StringToVector((*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["expirationDate"]["Value"].asString()));
                csgsd.SetExpirationDate(time);
            }

            isNull = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["LIPA_AllowedAPNList"]["APN"]["Value"].isNull();
            isAVPEnabled = (*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["LIPA_AllowedAPNList"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::LIPA_AllowedAPNList lipaapnl;
                map_v13::APN apn(MAPUtils::StringToVector((*cfg)["CSG_SubscriptionDataList"]["CSG_SubscriptionData"]["LIPA_AllowedAPNList"]["APN"]["Value"].asString()));
                lipaapnl.AddElement(apn);
                csgsd.SetLipa_AllowedAPNList(lipaapnl);
            }
            csgsdl.AddElement(csgsd);
        }
        isdArg->SetCsg_SubscriptionDataList(csgsdl);
    }

    isNull = (*cfg)["AccessRestrictionData"]["Value"].isNull();
    isAVPEnabled = (*cfg)["AccessRestrictionData"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::AccessRestrictionData ard(MAPUtils::UnsignedToBitVector(((*cfg)["AccessRestrictionData"]["Value"].asInt()),8));
        isdArg->SetAccessRestrictionData(ard);
    }
    
    isNull = (*cfg)["RoamingRestrictedInSgsnDueToUnsupportedFeature"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["RoamingRestrictedInSgsnDueToUnsupportedFeature"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::InsertSubscriberDataArg::InsertSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsupportedFeature rrisgsn;
        isdArg->SetRoamingRestrictedInSgsnDueToUnsupportedFeature(rrisgsn);
    }

    isNull = (*cfg)["MDTUserConsent"]["Value"].isNull();
    isAVPEnabled = (*cfg)["MDTUserConsent"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::InsertSubscriberDataArg::MdtUserConsent mdt((*cfg)["MDTUserConsent"]["Value"].asBool());
        isdArg->SetMdtUserConsent(mdt);
    }



    
    /*int idx = GetRecvImsiIndex();
    map_v13::InsertSubscriberDataArg *isdArg =
                            new map_v13::InsertSubscriberDataArg();
    std::vector<byte>           imsidata(gImsi, gImsi + sizeof(gImsi));
    std::vector<byte>           msdata(gMsIsdn, gMsIsdn + 5);
    std::vector<byte>           extdata(gExtTele, gExtTele + 9);

    map_v13::IMSI                imsi(gImsiList[0]);
    map_v13::ISDN_AddressString  msisdn(msdata);
    map_v13::SubscriberStatus    subStatus(
                                 map_v13::SubscriberStatus::SUBSCRIBER_STATUS_SERVICE_GRANTED);
    map_v13::TeleserviceList     telServ;
    map_v13::Ext_TeleserviceCode extService(extdata);
    map_v13::InsertSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature rrest;

    telServ.AddElement(extService);

    isdArg->SetImsi(imsi);
    isdArg->SetMsisdn(msisdn);
    isdArg->SetRoamingRestrictionDueToUnsupportedFeature(rrest);

    map_v13::GPRSSubscriptionData gprsSD;
    map_v13::GPRSSubscriptionData::CompleteDataListIncluded cdnull;
    map_v13::GPRSDataList datalist;

    gprsSD.SetCompleteDataListIncluded(cdnull);
    byte arr[2] = { 0x011, 0x22};
    byte arqos[3] = { 0x01, 0x02, 0x03 };
    byte arapn[10] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };
    std::vector<byte> type(arr, arr + 2);
    std::vector<byte> qos(arqos, arqos + 3);
    std::vector<byte> apn(arapn, arapn + 10);

    map_v13::ContextId ctxtid(0xBEEF);
    map_v13::PDP_Type  pdpty(type);
    map_v13::QoS_Subscribed qoss(qos);
    map_v13::APN            apno(apn);
    map_v13::PDP_Context    pdp;

    pdp.SetPdp_ContextId(ctxtid);
    pdp.SetPdp_Type(pdpty);
    pdp.SetQos_Subscribed(qoss);
    pdp.SetApn(apno);

    datalist.AddElement(pdp); 
    gprsSD.SetGprsDataList(datalist);

    isdArg->SetGprsSubscriptionData(gprsSD);*/
 
    return isdArg;
}

AsnObject* BuildProvideSubscriberInfoArgV13()
{

    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];


    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoArg"];

    map_v13::ProvideSubscriberInfoArg *psiArg = new map_v13::ProvideSubscriberInfoArg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2) 
        {    
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        psiArg->SetImsi(imsi);
    }

    isNull = (*cfg)["RequestedInfo"].isNull();
    if(!isNull)
    {
        map_v13::RequestedInfo  reqInfo;
        isNull = (*cfg)["RequestedInfo"]["LocationInformation"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["RequestedInfo"]["LocationInformation"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RequestedInfo::LocationInformation linfo;
            reqInfo.SetLocationInformation(linfo);
        }

        isNull = (*cfg)["RequestedInfo"]["SubscriberState"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["RequestedInfo"]["SubscriberState"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RequestedInfo::SubscriberState subs;
            reqInfo.SetSubscriberState(subs);
        }

        isNull = (*cfg)["RequestedInfo"]["CurrentLocation"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["RequestedInfo"]["CurrentLocation"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RequestedInfo::CurrentLocation curloc;
            reqInfo.SetCurrentLocation(curloc);
        }

        isNull = (*cfg)["RequestedInfo"]["T_adsData"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["RequestedInfo"]["T_adsData"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RequestedInfo::T_adsData tads;
            reqInfo.SetT_adsData(tads);
        }

        psiArg->SetRequestedInfo(reqInfo);
    }
    /*int idx = GetRecvImsiIndex();
    map_v13::ProvideSubscriberInfoArg *psiArg = new map_v13::ProvideSubscriberInfoArg();

    map_v13::IMSI     imsi(gImsiList[idx]);

    psiArg->SetImsi(imsi);

    map_v13::RequestedInfo                      reqInfo;
    map_v13::RequestedInfo::T_adsData           tads;
    map_v13::RequestedInfo::SubscriberState     subs;
    map_v13::RequestedInfo::LocationInformation linfo;
    map_v13::RequestedInfo::CurrentLocation     curloc;

    reqInfo.SetLocationInformation(linfo);
    reqInfo.SetSubscriberState(subs);
    reqInfo.SetCurrentLocation(curloc);
    reqInfo.SetT_adsData(tads);

    psiArg->SetRequestedInfo(reqInfo);*/

    return psiArg;
}

AsnObject* BuildDeleteSubscriberDatArgV13()
{

    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];


    Json::Value* cfg = &(*m_jsonRoot1)["DeleteSubscriberDataArg"];

    map_v13::DeleteSubscriberDataArg *dsdArg = new map_v13::DeleteSubscriberDataArg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2) 
        {    
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        dsdArg->SetImsi(imsi);
    }

    isNull = (*cfg)["regionalSubscriptionIdentifier"]["Value"].isNull();
    isAVPEnabled = (*cfg)["regionalSubscriptionIdentifier"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ZoneCode regZone(MAPUtils::StringToVector((*cfg)["regionalSubscriptionIdentifier"]["Value"].asString()));
        dsdArg->SetRegionalSubscriptionIdentifier(regZone);
    }

    isAVPEnabled = (*cfg)["EPS_SubscriptionDataWithdraw"]["Enabled"].asBool();
    isNull = (*cfg)["EPS_SubscriptionDataWithdraw"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {  
        map_v13::EPS_SubscriptionDataWithdraw epsSubData;
        bool isAllEPS_DataEnabled = (*cfg)["EPS_SubscriptionDataWithdraw"]["AllEPS_Data"]["Enabled"].asBool();
        isNull = (*cfg)["EPS_SubscriptionDataWithdraw"]["AllEPS_Data"]["Enabled"].isNull();
        if ((!isNull) && isAllEPS_DataEnabled)
        {
            map_v13::EPS_SubscriptionDataWithdraw::AllEPS_Data aed;
            epsSubData.SetChoiceAllEPS_Data(aed);
            dsdArg->SetEpsSubscriptionDataWithdraw(epsSubData);
        }

        bool isContextIdListEnabled = (*cfg)["EPS_SubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Enabled"].asBool();
        isNull = (*cfg)["EPS_SubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Value"].isNull();
        if((!isNull) && isContextIdListEnabled && (!isAllEPS_DataEnabled))
        {
            map_v13::ContextIdList ctxtidlst;
            map_v13::ContextId contextid((*cfg)["EPS_SubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Value"].asInt());
            ctxtidlst.AddElement(contextid);
            epsSubData.SetChoiceContextIdList(ctxtidlst);
            dsdArg->SetEpsSubscriptionDataWithdraw(epsSubData);
        }
    }

    isNull = (*cfg)["ChargingCharacteristicsWithdraw"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["ChargingCharacteristicsWithdraw"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::ChargingCharacteristicsWithdraw ccw;
        dsdArg->SetChargingCharacteristicsWithdraw(ccw);
    }

    isNull = (*cfg)["STN_SRWithdraw"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["STN_SRWithdraw"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::Stn_srWithdraw stnw;
        dsdArg->SetStn_srWithdraw(stnw);
    }

    isNull = (*cfg)["GMLC_ListWithdraw"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["GMLC_ListWithdraw"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::Gmlc_ListWithdraw gmlcw;
        dsdArg->SetGmlc_ListWithdraw(gmlcw);
    }

    isNull = (*cfg)["SS_List"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["SS_List"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::SS_List sslist;
        isNull = (*cfg)["SS_List"]["SS_Code"]["Value"].isNull();
        isAVPEnabled = (*cfg)["SS_List"]["SS_Code"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            uint8_t l_ssc[1] = {0};
            std::string ssc = (*cfg)["SS_List"]["SS_Code"]["Value"].asString();
            if(ssc.length() > MAX_SS_CODE_DIGITS)
            {
                ssc.erase(MAX_SS_CODE_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(ssc, l_ssc, MAX_SS_CODE_DIGITS, 0, true);
            
            map_v13::SS_Code sscode(MAPUtils::ByteArrayToVector(l_ssc, len));
            sslist.AddElement(sscode);
            dsdArg->SetSs_List(sslist);
        }
    }

    isAVPEnabled = (*cfg)["GPRSSubscriptionDataWithdraw"]["Enabled"].asBool();
    isNull = (*cfg)["GPRSSubscriptionDataWithdraw"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {  
        map_v13::GPRSSubscriptionDataWithdraw gprs;
        bool isAllGPRS_DataEnabled = (*cfg)["GPRSSubscriptionDataWithdraw"]["AllGPRSData"]["Enabled"].asBool();
        isNull = (*cfg)["GPRSSubscriptionDataWithdraw"]["AllGPRSData"]["Enabled"].isNull();
        if ((!isNull) && isAllGPRS_DataEnabled)
        {
            map_v13::GPRSSubscriptionDataWithdraw::AllGPRSData agprs;
            gprs.SetChoiceAllGPRSData(agprs);
            dsdArg->SetGprsSubscriptionDataWithdraw(gprs);
        }

        bool isContextIdListEnabled = (*cfg)["GPRSSubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Enabled"].asBool();
        isNull = (*cfg)["GPRSSubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Value"].isNull();
        if((!isNull) && isContextIdListEnabled && (!isAllGPRS_DataEnabled))
        {
            map_v13::ContextIdList ctxtidlst;
            map_v13::ContextId contextid((*cfg)["GPRSSubscriptionDataWithdraw"]["ContextIdList"]["ContextId"]["Value"].asInt());
            ctxtidlst.AddElement(contextid);
            gprs.SetChoiceContextIdList(ctxtidlst);
            dsdArg->SetGprsSubscriptionDataWithdraw(gprs);
        }
    }
    
    isNull = (*cfg)["RoamingRestrictedInSgsnDueToUnsuppportedFeature"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["RoamingRestrictedInSgsnDueToUnsuppportedFeature"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::RoamingRestrictedInSgsnDueToUnsuppportedFeature rrisgsndtuf;
        dsdArg->SetRoamingRestrictedInSgsnDueToUnsuppportedFeature(rrisgsndtuf);
    }

    isNull = (*cfg)["RoamingRestrictionDueToUnsupportedFeature"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["RoamingRestrictionDueToUnsupportedFeature"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature rrdtuf;
        dsdArg->SetRoamingRestrictionDueToUnsupportedFeature(rrdtuf);
    }

    isNull = (*cfg)["CSG_SubscriptionDeleted"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CSG_SubscriptionDeleted"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::Csg_SubscriptionDeleted csgsd;
        dsdArg->SetCsg_SubscriptionDeleted(csgsd);
    }

    isNull = (*cfg)["APN_oi_replacementWithdraw"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["APN_oi_replacementWithdraw"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::DeleteSubscriberDataArg::Apn_oi_replacementWithdraw apnoirw;
        dsdArg->SetApn_oi_replacementWithdraw(apnoirw);
    }


/*
    int idx = GetRecvImsiIndex();
    map_v13::DeleteSubscriberDataArg *dsdArg = new map_v13::DeleteSubscriberDataArg();

    map_v13::IMSI     imsi(gImsiList[idx]);

    dsdArg->SetImsi(imsi);

    map_v13::DeleteSubscriberDataArg::RoamingRestrictionDueToUnsupportedFeature rrst;
    dsdArg->SetRoamingRestrictionDueToUnsupportedFeature(rrst);

    uint8_t zca[] = { 0x01, 0x02 };
    std::vector<byte> zc(zca, zca + sizeof(zca));
    map_v13::ZoneCode regZone(zc);

    dsdArg->SetRegionalSubscriptionIdentifier(regZone);

    // TODO: Select Context ID choice.
    map_v13::EPS_SubscriptionDataWithdraw epsSubData;
    map_v13::EPS_SubscriptionDataWithdraw::AllEPS_Data aed;
    epsSubData.SetChoiceAllEPS_Data(aed);
    dsdArg->SetEpsSubscriptionDataWithdraw(epsSubData);

    map_v13::GPRSSubscriptionDataWithdraw gprs;
    map_v13::GPRSSubscriptionDataWithdraw::AllGPRSData agprs;
    gprs.SetChoiceAllGPRSData(agprs);
    dsdArg->SetGprsSubscriptionDataWithdraw(gprs);
*/

    return dsdArg;
}

AsnObject* BuildDeleteSubscriberDatResV13() {

    bool isNull;
    bool isAVPEnabled;

    Json::Value* cfg = &(*m_jsonRoot1)["DeleteSubscriberDataRes"];
    map_v13::DeleteSubscriberDataRes *dsdr = new map_v13::DeleteSubscriberDataRes();

    isAVPEnabled = (*cfg)["RegionalSubscriptionResponse"]["Enabled"].asBool();
    isNull = (*cfg)["RegionalSubscriptionResponse"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::RegionalSubscriptionResponse rsr((*cfg)["RegionalSubscriptionResponse"]["Value"].asInt());
        dsdr->SetRegionalSubscriptionResponse(rsr);
    }

    return dsdr;
}


AsnObject* BuildSendAuthenticationInfoResV13() 
{

    bool isNull;
    bool isAVPEnabled;
    uint8_t l_rand[MAP_MAX_E164_SZ/2];
    uint8_t l_xres[MAP_MAX_E164_SZ/2];
    uint8_t l_autn[MAP_MAX_E164_SZ/2];
    uint8_t l_kasme[MAP_MAX_E164_SZ/2];
    uint8_t l_sres[MAP_MAX_E164_SZ/2];
    uint8_t l_kc[MAP_MAX_E164_SZ/2];
    uint8_t l_ck[MAP_MAX_E164_SZ/2];
    uint8_t l_ik[MAP_MAX_E164_SZ/2];

    Json::Value* cfg = &(*m_jsonRoot1)["SendAuthenticationInfoRes"];
    map_v13::SendAuthenticationInfoRes *sair = new map_v13::SendAuthenticationInfoRes();

    isNull = (*cfg)["EPS_AuthenticationSetList"]["Enabled"].isNull();
    if(!isNull)
    {
        isAVPEnabled = (*cfg)["EPS_AuthenticationSetList"]["Enabled"].asBool();
        if(isAVPEnabled)
        {
            map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList eps_AuthenticationSetList;
            map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList::EPC_AV epc_AV;


            isNull = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["RAND"]["Value"].isNull();
            if(!isNull)
            {
                string rand_bv = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["RAND"]["Value"].asString();
                if(rand_bv.length() > MAX_RAND_DIGITS)
                    rand_bv.erase(MAX_RAND_DIGITS, std::string::npos);

                int len = MAPUtils::StringToTBCD(rand_bv, l_rand, MAP_MAX_E164_SZ);

                map_v13::RAND rand_os(MAPUtils::ByteArrayToVector(l_rand, len));
                epc_AV.SetRand(rand_os);
            }
            isNull = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["XRES"]["Value"].isNull();
            if(!isNull)
            {
                string xres_str = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["XRES"]["Value"].asString();
                if(xres_str.length() > MAX_XRES_DIGITS)
                    xres_str.erase(MAX_XRES_DIGITS, std::string::npos);

                int len = MAPUtils::StringToTBCD(xres_str, l_xres, MAP_MAX_E164_SZ);

                if (xres_str.length() % 2)
                    l_xres[(xres_str.length() / 2)] |= 0xF0;

                map_v13::XRES xres_os(MAPUtils::ByteArrayToVector(l_xres, len));
                epc_AV.SetXres(xres_os);
            }
            isNull = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["AUTN"]["Value"].isNull();
            if(!isNull)
            {
                string autn_str = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["AUTN"]["Value"].asString();
                if(autn_str.length() > MAX_AUTN_DIGITS)
                    autn_str.erase(MAX_AUTN_DIGITS, std::string::npos);
                int len = MAPUtils::StringToTBCD(autn_str, l_autn, MAP_MAX_E164_SZ);
                map_v13::AUTN autn_os(MAPUtils::ByteArrayToVector(l_autn, len));
                epc_AV.SetAutn(autn_os);
            }
            isNull = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["KASME"]["Value"].isNull();
            if(!isNull)
            {
                string kasme_str = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["KASME"]["Value"].asString();
                if(kasme_str.length() > MAX_KASME_DIGITS)
                    kasme_str.erase(MAX_KASME_DIGITS, std::string::npos);
                int len = MAPUtils::StringToTBCD(kasme_str, l_kasme, MAP_MAX_E164_SZ);

                map_v13::KASME kasme_os(MAPUtils::ByteArrayToVector(l_kasme, len));
                epc_AV.SetKasme(kasme_os);
            }
            int num = (*cfg)["EPS_AuthenticationSetList"]["EPC_AV"]["Number_of_times_to_populate"].asInt();
            while(num)
            {
                eps_AuthenticationSetList.AddElement(epc_AV);
                num--;
            }
            sair->SetEps_AuthenticationSetList(eps_AuthenticationSetList);
        }
    }

    isNull = (*cfg)["AuthenticationSetList"]["Enabled"].isNull();
    if(!isNull)
    {
        isAVPEnabled = (*cfg)["AuthenticationSetList"]["Enabled"].asBool();
        if(isAVPEnabled)
        {
            map_v13::AuthenticationSetList authenticationSetList;
            isNull = (*cfg)["AuthenticationSetList"]["TripletList"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["AuthenticationSetList"]["TripletList"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::TripletList tl;
                map_v13::AuthenticationTriplet at;

                isNull = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["RAND"]["Value"].isNull();
                if(!isNull)
                {
                    string rand_bv = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["RAND"]["Value"].asString();
                    if(rand_bv.length() > MAX_RAND_DIGITS)
                        rand_bv.erase(MAX_RAND_DIGITS, std::string::npos);

                    int len = MAPUtils::StringToTBCD(rand_bv, l_rand, MAP_MAX_E164_SZ);
                    map_v13::RAND rand_os(MAPUtils::ByteArrayToVector(l_rand, len));
                    at.SetRand(rand_os);
                }
                isNull = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["SRES"]["Value"].isNull();
                if(!isNull)
                {
                    string sres_bv = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["SRES"]["Value"].asString();
                    if(sres_bv.length() > MAX_SRES_DIGITS)
                        sres_bv.erase(MAX_SRES_DIGITS, std::string::npos);

                    int len = MAPUtils::StringToTBCD(sres_bv, l_sres, MAP_MAX_E164_SZ);
                    map_v13::SRES sres_os(MAPUtils::ByteArrayToVector(l_sres, len));

                    at.SetSres(sres_os);
                }
                isNull = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["Kc"]["Value"].isNull();
                if(!isNull)
                {
                    string kc_bv = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["Kc"]["Value"].asString();
                    if(kc_bv.length() > MAX_KC_DIGITS)
                        kc_bv.erase(MAX_KC_DIGITS, std::string::npos);

                    int len = MAPUtils::StringToTBCD(kc_bv, l_kc, MAP_MAX_E164_SZ);
                    map_v13::Kc kc_os(MAPUtils::ByteArrayToVector(l_kc, len));
                    at.SetKc(kc_os);
                }
                int num = (*cfg)["AuthenticationSetList"]["TripletList"]["AuthenticationTriplet"]["Number_of_times_to_populate"].asInt();
                while(num)
                {
                    tl.AddElement(at);
                    num--;
                }
                authenticationSetList.SetChoiceTripletList(tl);
                sair->SetAuthenticationSetList(authenticationSetList);
            }
            else
            {
                isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["AuthenticationSetList"]["QuintupletList"]["Enabled"].asBool();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::QuintupletList ql;
                    map_v13::AuthenticationQuintuplet aql;

                    isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["RAND"]["Value"].isNull();
                    if(!isNull)
                    {
                        string rand_bv = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["RAND"]["Value"].asString();
                        if(rand_bv.length() > MAX_RAND_DIGITS)
                            rand_bv.erase(MAX_RAND_DIGITS, std::string::npos);

                        int len = MAPUtils::StringToTBCD(rand_bv, l_rand, MAP_MAX_E164_SZ);
                        map_v13::RAND rand_os(MAPUtils::ByteArrayToVector(l_rand, len));

                        aql.SetRand(rand_os);
                    }
                    isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["XRES"]["Value"].isNull();
                    if(!isNull)
                    {
                        string xres_str = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["XRES"]["Value"].asString();
                        if(xres_str.length() > MAX_XRES_DIGITS)
                            xres_str.erase(MAX_XRES_DIGITS, std::string::npos);

                        int len = MAPUtils::StringToTBCD(xres_str, l_xres, MAP_MAX_E164_SZ);

                        if (xres_str.length() % 2)
                            l_xres[(xres_str.length() / 2)] |= 0xF0;

                        map_v13::XRES xres_os(MAPUtils::ByteArrayToVector(l_xres, len));
                        aql.SetXres(xres_os);
                    }
                    isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["CK"]["Value"].isNull();
                    if(!isNull)
                    {
                        string ck_bv = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["CK"]["Value"].asString();
                        if(ck_bv.length() > MAX_CK_DIGITS)
                            ck_bv.erase(MAX_CK_DIGITS, std::string::npos);

                        int len = MAPUtils::StringToTBCD(ck_bv, l_ck, MAP_MAX_E164_SZ);
                        map_v13::CK ck_os(MAPUtils::ByteArrayToVector(l_ck, len));
                        aql.SetCk(ck_os);
                    }
                    isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["IK"]["Value"].isNull();
                    if(!isNull)
                    {
                        string ik_bv = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["IK"]["Value"].asString();
                        if(ik_bv.length() > MAX_IK_DIGITS)
                            ik_bv.erase(MAX_IK_DIGITS, std::string::npos);

                        int len = MAPUtils::StringToTBCD(ik_bv, l_ik, MAP_MAX_E164_SZ);
                        map_v13::IK ik_os(MAPUtils::ByteArrayToVector(l_ik, len));
                        aql.SetIk(ik_os);
                    }
                    isNull = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["AUTN"]["Value"].isNull();
                    if(!isNull)
                    {
                        string autn_str = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["AUTN"]["Value"].asString();
                        if(autn_str.length() > MAX_AUTN_DIGITS)
                            autn_str.erase(MAX_AUTN_DIGITS, std::string::npos);
                        int len = MAPUtils::StringToTBCD(autn_str, l_autn, MAP_MAX_E164_SZ);
                        map_v13::AUTN autn_os(MAPUtils::ByteArrayToVector(l_autn, len));
                        aql.SetAutn(autn_os);
                    }
                    int num = (*cfg)["AuthenticationSetList"]["QuintupletList"]["AuthenticationQuintuplet"]["Number_of_times_to_populate"].asInt();
                    while(num)
                    {
                        ql.AddElement(aql);
                        num--;
                    }
                    authenticationSetList.SetChoiceQuintupletList(ql);
                    sair->SetAuthenticationSetList(authenticationSetList);
                }
            }
        }
    }

    /*map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList eps_AuthenticationSetList;
    map_v13::SendAuthenticationInfoRes::EPS_AuthenticationSetList::EPC_AV epc_AV;

    byte rand_a[] = {
        0x3f, 0x18, 0xeb, 0xdd,
        0xdb, 0x84, 0x29, 0x3d,
        0x64, 0x79, 0xca, 0xd7,
        0x81, 0x1e, 0x26, 0x58
    };    
    std::vector<byte> rand_bv(rand_a, rand_a + sizeof(rand_a));
    map_v13::RAND rand_os(rand_bv);
    epc_AV.SetRand(rand_os);
    
    byte xres_a[] = {
        0x19, 0xe6, 0xcf, 0xf9,
        0x43, 0x79, 0x68, 0x61
    };
    std::vector<byte> xres_bv(xres_a, xres_a + sizeof(xres_a));
    map_v13::XRES xres_os(xres_bv);
    epc_AV.SetXres(xres_os);
    
    byte autn_a[] = {
        0x61, 0x70, 0x23, 0xab,
        0xb2, 0x5a, 0x00, 0x00,
        0x93, 0xf3, 0x3b, 0xb4,
        0x9a, 0x2e, 0x11, 0xc6
    };
    std::vector<byte> autn_bv(autn_a, autn_a + sizeof(autn_a));
    map_v13::AUTN autn_os(autn_bv);
    epc_AV.SetAutn(autn_os); 
    
    byte kasme_a[] = {
        0xdc, 0x86, 0x08, 0x5f,
        0xa0, 0xba, 0xcf, 0x31,
        0x67, 0xc0, 0xc9, 0xb4,
        0x20, 0xbf, 0x3f, 0xdc,
        0xdc, 0x86, 0x08, 0x5f,
        0xa0, 0xba, 0xcf, 0x31,
        0x67, 0xc0, 0xc9, 0xb4,
        0x20, 0xbf, 0x3f, 0xdc        
    };
    std::vector<byte> kasme_bv(kasme_a, kasme_a + sizeof(kasme_a));
    map_v13::KASME kasme_os(kasme_bv);
    epc_AV.SetKasme(kasme_os);
    
    eps_AuthenticationSetList.AddElement(epc_AV);
    
    sair->SetEps_AuthenticationSetList(eps_AuthenticationSetList);*/
    
    return sair;
}

AsnObject* BuildReadyForSM_ResV13()
{
    map_v13::ReadyForSM_Res *rfsr = new map_v13::ReadyForSM_Res();
    // nothing to be built!!
    
    return rfsr;
}

AsnObject* BuildCancelLocationResV13()
{
    map_v13::CancelLocationRes *clargRes = new map_v13::CancelLocationRes();
    //Nothing to fill in this 
    return clargRes;
}

/*AsnObject* SleepCancelLoc()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = " ";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["CancelLocationArg"];
    
    isNull = (*cfg)["SleepCancelLoc"]["Value"].isNull();
    sleep_value = (*cfg)["SleepCancelLoc"]["Value"].asInt();
    isAVPEnabled = (*cfg)["SleepCancelLoc"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        sleep(sleep_value);
    }

}*/

AsnObject*  BuildProvideRoamingNumberArgv9() {
 
    bool isNull;
    bool isAVPEnabled;
    
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideRoamingNumber"];

    map_v9::ProvideRoamingNumberArg *prrn = new map_v9::ProvideRoamingNumberArg();

    std::vector<byte>          iaddr(gMsIsdn, gMsIsdn + 5);
    std::vector<byte>          l_imsi(gImsi, gImsi +8);
    map_v9::IMSI               imsi(l_imsi);
    map_v9::ISDN_AddressString mscNumber(MAPUtils::StringToVector("236590"));

    prrn->SetImsi(imsi);
    prrn->SetMsc_Number(mscNumber);
   /* 
    isAVPEnabled = (*cfg)["Gsm-BearerCapability"]["ProtocolId"]["Enabled"].asBool();
    isNull = (*cfg)["Gsm-BearerCapability"]["ProtocolId"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        prrn->SetGsm_BearerCapability(new map_v3::ExternalSignalInfo ((*cfg)["Gsm-BearerCapability"]["ProtocolId"]["Value"].asInt()));
    }*/
 
    isAVPEnabled = (*cfg)["OrNotSupportedInGMSC"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v9::ProvideRoamingNumberArg::OrNotSupportedInGMSC ornull;
        prrn->SetOrNotSupportedInGMSC(ornull);
    }

    return prrn;
}

AsnObject*  BuildProvideRoamingNumberResv9() {

    map_v9::ProvideRoamingNumberRes *prrnres = new map_v9::ProvideRoamingNumberRes();

    map_v9::ISDN_AddressString roamingNumber(MAPUtils::StringToVector("400"));
    prrnres->SetRoamingNumber(roamingNumber);
    
    return prrnres;
}


AsnObject* BuildCancelLocationArgV13()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];


    Json::Value* cfg = &(*m_jsonRoot1)["CancelLocationArg"];

    map_v13::CancelLocationArg *clArg = new map_v13::CancelLocationArg();

    isNull = (*cfg)["Identity"].isNull();
    if(!isNull)
    {
        map_v13::Identity id;
        isNull = (*cfg)["Identity"]["IMSI"]["Value"].isNull();
        if(!isNull)
        {
            Imsi = (*cfg)["Identity"]["IMSI"]["Value"].asString();
            if (Imsi.length() >= 15)
            {
                // We have strip here becase the IWFArray is sending some extra junk.
                Imsi.erase(15, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
            if (Imsi.length() % 2) 
            {    
                l_imsi[(Imsi.length() / 2)] |= 0xF0;
            }
            map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
            id.SetChoiceImsi(imsi);
            clArg->SetIdentity(id);
        }
    }

    isNull = (*cfg)["CancellationType"]["Value"].isNull();
    isAVPEnabled = (*cfg)["CancellationType"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        clArg->SetCancellationType(new map_v13::CancellationType((*cfg)["CancellationType"]["Value"].asInt()));
    }

    isNull = (*cfg)["TypeOfUpdate"]["Value"].isNull();
    isAVPEnabled = (*cfg)["TypeOfUpdate"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        clArg->SetTypeOfUpdate(new map_v13::TypeOfUpdate((*cfg)["TypeOfUpdate"]["Value"].asInt()));
    }

    // Set IMSI
    /*std::vector<byte> imsidata(gImsi, gImsi + sizeof(gImsi));
    map_v13::IMSI     imsi(imsidata);
    map_v13::Identity id;
    id.SetChoiceImsi(imsi);

    clArg->SetIdentity(id);

    // Set the Cancellation Type
    clArg->SetCancellationType(new map_v13::CancellationType(
    map_v13::CancellationType::CANCELLATION_TYPE_UPDATE_PROCEDURE));

    // Set TypeOfUpdate to MME
    clArg->SetTypeOfUpdate(new map_v13::TypeOfUpdate(
    map_v13::TypeOfUpdate::TYPE_OF_UPDATE_MME_CHANGE));*/

    return clArg;
}

AsnObject* BuildPurgeMSResV13()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value* cfg = &(*m_jsonRoot1)["PurgeMS_Res"];

    map_v13::PurgeMS_Res *puaRes = new map_v13::PurgeMS_Res();

    isNull = (*cfg)["FreezeM_TMSI"]["Enabled"].isNull();
    if(!isNull)
    {
        isAVPEnabled = (*cfg)["FreezeM_TMSI"]["Enabled"].asBool();
        if(isAVPEnabled)
        {
            map_v13::PurgeMS_Res::FreezeM_TMSI mtmsi;
            puaRes->SetFreezeM_TMSI(mtmsi);
        }
    }

    isNull = (*cfg)["FreezeP_TMSI"]["Enabled"].isNull();
    if(!isNull)
    {
        isAVPEnabled = (*cfg)["FreezeP_TMSI"]["Enabled"].asBool();
        if(isAVPEnabled)
        {
            map_v13::PurgeMS_Res::FreezeP_TMSI ptmsi;
            puaRes->SetFreezeP_TMSI(ptmsi);
        }
    }

    /*map_v13::PurgeMS_Res::FreezeM_TMSI mtmsi;
    map_v13::PurgeMS_Res::FreezeP_TMSI ptmsi;

    //Set freeze MTMSI and freeze PTMSI
    puaRes->SetFreezeP_TMSI(ptmsi);
    puaRes->SetFreezeM_TMSI(mtmsi);*/
    
    return puaRes;
}

AsnObject* BuildTraceActivateModeArgV13()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ActivateTraceModeArg"];

    map_v13::ActivateTraceModeArg *trArg = new map_v13::ActivateTraceModeArg(); 

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    isAVPEnabled = (*cfg)["IMSI"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        trArg->SetImsi(imsi);
    }

    isNull = (*cfg)["TraceReference"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::TraceReference tref(MAPUtils::StringToVector((*cfg)["TraceReference"]["Value"].asString()));
        trArg->SetTraceReference(tref);
    }

    isNull = (*cfg)["TraceReference2"]["Value"].isNull();
    isAVPEnabled = (*cfg)["TraceReference2"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceReference2 tref2(MAPUtils::StringToVector((*cfg)["TraceReference2"]["Value"].asString()));
        trArg->SetTraceReference2(tref2);
    }

    isNull = (*cfg)["TraceType"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::TraceType tt((*cfg)["TraceType"]["Value"].asInt());
        trArg->SetTraceType(tt);
    }

    isNull = (*cfg)["TraceDepthList"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["TraceDepthList"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceDepthList tdl;
        isNull = (*cfg)["TraceDepthList"]["msc_s_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["msc_s_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td((*cfg)["TraceDepthList"]["msc_s_TraceDepth"]["Value"].asInt());
            tdl.SetMsc_s_TraceDepth(td);
        }
        isNull = (*cfg)["TraceDepthList"]["mgw_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["mgw_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td1((*cfg)["TraceDepthList"]["mgw_TraceDepth"]["Value"].asInt());
            tdl.SetMgw_TraceDepth(td1);
        }
        isNull = (*cfg)["TraceDepthList"]["sgsn_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["sgsn_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td2((*cfg)["TraceDepthList"]["sgsn_TraceDepth"]["Value"].asInt());
            tdl.SetSgsn_TraceDepth(td2);
        }
        isNull = (*cfg)["TraceDepthList"]["ggsn_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["ggsn_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td3((*cfg)["TraceDepthList"]["ggsn_TraceDepth"]["Value"].asInt());
            tdl.SetGgsn_TraceDepth(td3);
        }    
        isNull = (*cfg)["TraceDepthList"]["rnc_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["rnc_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td4((*cfg)["TraceDepthList"]["rnc_TraceDepth"]["Value"].asInt());
            tdl.SetRnc_TraceDepth(td4);
        }    
        isNull = (*cfg)["TraceDepthList"]["bmsc_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["bmsc_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td5((*cfg)["TraceDepthList"]["bmsc_TraceDepth"]["Value"].asInt());
            tdl.SetBmsc_TraceDepth(td5);
        }    
        isNull = (*cfg)["TraceDepthList"]["mme_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["mme_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td6((*cfg)["TraceDepthList"]["mme_TraceDepth"]["Value"].asInt());
            tdl.SetMme_TraceDepth(td6);
        }    
        isNull = (*cfg)["TraceDepthList"]["sgw_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["sgw_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td7((*cfg)["TraceDepthList"]["sgw_TraceDepth"]["Value"].asInt());
            tdl.SetSgw_TraceDepth(td7);
        }    
        isNull = (*cfg)["TraceDepthList"]["pgw_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["pgw_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td8((*cfg)["TraceDepthList"]["pgw_TraceDepth"]["Value"].asInt());
            tdl.SetPgw_TraceDepth(td8);
        }    
        isNull = (*cfg)["TraceDepthList"]["eNB_TraceDepth"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceDepthList"]["eNB_TraceDepth"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::TraceDepth td9((*cfg)["TraceDepthList"]["eNB_TraceDepth"]["Value"].asInt());
            tdl.SetENB_TraceDepth(td9);
        }    
         
        trArg->SetTraceDepthList(tdl);
    }

    isNull = (*cfg)["TraceNE_TypeList"]["Value"].isNull();
    isAVPEnabled = (*cfg)["TraceNE_TypeList"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceNE_TypeList trnetl(MAPUtils::UnsignedToBitVector(((*cfg)["TraceNE_TypeList"]["Value"].asInt()),16));
        trArg->SetTraceNE_TypeList(trnetl);
    }

    isNull = (*cfg)["TraceInterfaceList"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["TraceInterfaceList"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceInterfaceList til;
        isNull = (*cfg)["TraceInterfaceList"]["MSC_S_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["MSC_S_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MSC_S_InterfaceList msc(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["MSC_S_InterfaceList"]["Value"].asInt()),16));
            til.SetMsc_s_List(msc);
        }
        isNull = (*cfg)["TraceInterfaceList"]["MGW_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["MGW_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MGW_InterfaceList mgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["MGW_InterfaceList"]["Value"].asInt()),8));
            til.SetMgw_List(mgw);
            
        }
        isNull = (*cfg)["TraceInterfaceList"]["SGSN_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["SGSN_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SGSN_InterfaceList sgsn(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["SGSN_InterfaceList"]["Value"].asInt()),16));
            til.SetSgsn_List(sgsn);
        }
        isNull = (*cfg)["TraceInterfaceList"]["GGSN_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["GGSN_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::GGSN_InterfaceList ggsn(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["GGSN_InterfaceList"]["Value"].asInt()),8));
            til.SetGgsn_List(ggsn);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["RNC_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["RNC_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::RNC_InterfaceList rnc(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["RNC_InterfaceList"]["Value"].asInt()),8));
            til.SetRnc_List(rnc);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["BMSC_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["BMSC_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::BMSC_InterfaceList bmsc(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["BMSC_InterfaceList"]["Value"].asInt()),8));
            til.SetBmsc_List(bmsc);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["MME_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["MME_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MME_InterfaceList mme(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["MME_InterfaceList"]["Value"].asInt()),8));
            til.SetMme_List(mme);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["SGW_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["SGW_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SGW_InterfaceList sgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["SGW_InterfaceList"]["Value"].asInt()),8));
            til.SetSgw_List(sgw);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["PGW_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["PGW_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::PGW_InterfaceList pgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["PGW_InterfaceList"]["Value"].asInt()),16));
            til.SetPgw_List(pgw);
        }    
        isNull = (*cfg)["TraceInterfaceList"]["ENB_InterfaceList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceInterfaceList"]["ENB_InterfaceList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ENB_InterfaceList enb(MAPUtils::UnsignedToBitVector(((*cfg)["TraceInterfaceList"]["ENB_InterfaceList"]["Value"].asInt()),8));
            til.SetENB_List(enb);
        }    
         
        trArg->SetTraceInterfaceList(til);
    }

    isNull = (*cfg)["TraceEventList"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["TraceEventList"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceEventList tel;
        isNull = (*cfg)["TraceEventList"]["MSC_S_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["MSC_S_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MSC_S_EventList msc(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["MSC_S_EventList"]["Value"].asInt()),16));
            tel.SetMsc_s_List(msc);
        }
        isNull = (*cfg)["TraceEventList"]["MGW_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["MGW_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MGW_EventList mgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["MGW_EventList"]["Value"].asInt()),8));
            tel.SetMgw_List(mgw);
            
        }
        isNull = (*cfg)["TraceEventList"]["SGSN_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["SGSN_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SGSN_EventList sgsn(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["SGSN_EventList"]["Value"].asInt()),16));
            tel.SetSgsn_List(sgsn);
        }
        isNull = (*cfg)["TraceEventList"]["GGSN_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["GGSN_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::GGSN_EventList ggsn(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["GGSN_EventList"]["Value"].asInt()),8));
            tel.SetGgsn_List(ggsn);
        }    
        isNull = (*cfg)["TraceEventList"]["BMSC_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["BMSC_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::BMSC_EventList bmsc(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["BMSC_EventList"]["Value"].asInt()),8));
            tel.SetBmsc_List(bmsc);
        }    
        isNull = (*cfg)["TraceEventList"]["MME_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["MME_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MME_EventList mme(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["MME_EventList"]["Value"].asInt()),8));
            tel.SetMme_List(mme);
        }    
        isNull = (*cfg)["TraceEventList"]["SGW_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["SGW_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SGW_EventList sgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["SGW_EventList"]["Value"].asInt()),8));
            tel.SetSgw_List(sgw);
        }    
        isNull = (*cfg)["TraceEventList"]["PGW_EventList"]["Value"].isNull();
        isAVPEnabled = (*cfg)["TraceEventList"]["PGW_EventList"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::PGW_EventList pgw(MAPUtils::UnsignedToBitVector(((*cfg)["TraceEventList"]["PGW_EventList"]["Value"].asInt()),8));
            tel.SetPgw_List(pgw);
        }    
        trArg->SetTraceEventList(tel);
    }

    isNull = (*cfg)["omc_id"]["Value"].isNull();
    isAVPEnabled = (*cfg)["omc_id"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::AddressString adstr(MAPUtils::StringToVector((*cfg)["omc_id"]["Value"].asString()));
        trArg->SetOmc_Id(adstr);
    }

    isNull = (*cfg)["traceCollectionEntity"]["Value"].isNull();
    isAVPEnabled = (*cfg)["traceCollectionEntity"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GSN_Address gsnadr(MAPUtils::StringToVector((*cfg)["traceCollectionEntity"]["Value"].asString()));
        trArg->SetTraceCollectionEntity(gsnadr);
    }

    isNull = (*cfg)["MDT_Configuration"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["MDT_Configuration"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::MDT_Configuration mdtc;
        isNull = (*cfg)["MDT_Configuration"]["JobType"]["Value"].isNull();
        if(!isNull)
        {
            map_v13::JobType jt((*cfg)["MDT_Configuration"]["JobType"]["Value"].asInt());
            mdtc.SetJobType(jt);
        }

        isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::AreaScope as;
            isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["CGI_List"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["CGI_List"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::CGI_List cgil;
                map_v13::GlobalCellId gcId(MAPUtils::StringToVector((*cfg)["MDT_Configuration"]["AreaScope"]["CGI_List"]["GlobalCellId"]["Value"].asString()));
                cgil.AddElement(gcId);
                as.SetCgi_List(cgil);
            }
            isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["E_UTRAN_CGI_List"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["E_UTRAN_CGI_List"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::E_UTRAN_CGI_List eucl;
                map_v13::E_UTRAN_CGI eucgi(MAPUtils::StringToVector((*cfg)["MDT_Configuration"]["AreaScope"]["E_UTRAN_CGI_List"]["E_UTRAN_CGI"]["Value"].asString()));
                eucl.AddElement(eucgi);
                as.SetE_utran_cgi_List(eucl);
            }
            isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["RoutingAreaId_List"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["RoutingAreaId_List"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::RoutingAreaId_List raId;
                map_v13::RAIdentity rId(MAPUtils::StringToVector((*cfg)["MDT_Configuration"]["AreaScope"]["RoutingAreaId_List"]["RAIdentity"]["Value"].asString()));
                raId.AddElement(rId);
                as.SetRoutingAreaId_List(raId);
            }
            isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["LocationAreaId_List"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["LocationAreaId_List"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::LocationAreaId_List laId;
                map_v13::LAIFixedLength lafl(MAPUtils::StringToVector((*cfg)["MDT_Configuration"]["AreaScope"]["LocationAreaId_List"]["LAIFixedLength"]["Value"].asString()));
                laId.AddElement(lafl);
                as.SetLocationAreaId_List(laId);
            }
            isNull = (*cfg)["MDT_Configuration"]["AreaScope"]["TrackingAreaId_List"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["MDT_Configuration"]["AreaScope"]["TrackingAreaId_List"]["Enabled"].asBool();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::TrackingAreaId_List taId;
                map_v13::TA_Id tId(MAPUtils::StringToVector((*cfg)["MDT_Configuration"]["AreaScope"]["TrackingAreaId_List"]["TA_Id"]["Value"].asString()));
                taId.AddElement(tId);
                as.SetTrackingAreaId_List(taId);
            }
            mdtc.SetAreaScope(as);
        }

        isNull = (*cfg)["ListOfMeasurements"]["Value"].isNull();
        isAVPEnabled = (*cfg)["ListOfMeasurements"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ListOfMeasurements lom(MAPUtils::StringToVector((*cfg)["ListOfMeasurements"]["Value"].asString()));
            mdtc.SetListOfMeasurements(lom);
        }

        isNull = (*cfg)["ReportingTrigger"]["Value"].isNull();
        isAVPEnabled = (*cfg)["ReportingTrigger"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ReportingTrigger rt(MAPUtils::StringToVector((*cfg)["ReportingTrigger"]["Value"].asString()));
            mdtc.SetReportingTrigger(rt);
        }

        isNull = (*cfg)["ReportInterval"]["Value"].isNull();
        isAVPEnabled = (*cfg)["ReportInterval"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ReportInterval ri((*cfg)["ReportInterval"]["Value"].asInt());
            mdtc.SetReportInterval(ri);
        }

        isNull = (*cfg)["ReportAmount"]["Value"].isNull();
        isAVPEnabled = (*cfg)["ReportAmount"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::ReportAmount ra((*cfg)["ReportAmount"]["Value"].asInt());
            mdtc.SetReportAmount(ra);
        }

        isNull = (*cfg)["EventThresholdRSRP"]["Value"].isNull();
        isAVPEnabled = (*cfg)["EventThresholdRSRP"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::EventThresholdRSRP rsrp((*cfg)["EventThresholdRSRP"]["Value"].asInt());
            mdtc.SetEventThresholdRSRP(rsrp);
        }

        isNull = (*cfg)["EventThresholdRSRQ"]["Value"].isNull();
        isAVPEnabled = (*cfg)["EventThresholdRSRQ"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::EventThresholdRSRQ rsrq((*cfg)["EventThresholdRSRQ"]["Value"].asInt());
            mdtc.SetEventThresholdRSRQ(rsrq);
        }

        isNull = (*cfg)["LoggingInterval"]["Value"].isNull();
        isAVPEnabled = (*cfg)["LoggingInterval"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LoggingInterval li((*cfg)["LoggingInterval"]["Value"].asInt());
            mdtc.SetLoggingInterval(li);
        }

        isNull = (*cfg)["LoggingDuration"]["Value"].isNull();
        isAVPEnabled = (*cfg)["LoggingDuration"]["Enabled"].asBool();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LoggingDuration ld((*cfg)["LoggingDuration"]["Value"].asInt());
            mdtc.SetLoggingDuration(ld);
        }
        trArg->SetMdt_Configuration(mdtc);
    }

    return trArg;
}

AsnObject* BuildTraceDeActivateModeArgV13()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["DeactivateTraceModeArg"];

    map_v13::DeactivateTraceModeArg *dtrArg = new map_v13::DeactivateTraceModeArg(); 

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    isAVPEnabled = (*cfg)["IMSI"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        dtrArg->SetImsi(imsi);
    }

    isNull = (*cfg)["TraceReference"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::TraceReference tref(MAPUtils::StringToVector((*cfg)["TraceReference"]["Value"].asString()));
        dtrArg->SetTraceReference(tref);
    }

    isNull = (*cfg)["TraceReference2"]["Value"].isNull();
    isAVPEnabled = (*cfg)["TraceReference2"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::TraceReference2 tref2(MAPUtils::StringToVector((*cfg)["TraceReference2"]["Value"].asString()));
        dtrArg->SetTraceReference2(tref2);
    }
    
    return dtrArg;
}

AsnObject* BuildTraceDeActivateModeResV13()
{
    map_v13::DeactivateTraceModeRes *dtrRes = new map_v13::DeactivateTraceModeRes();

    return dtrRes;
}

AsnObject* BuildTraceActivateModeResV13()
{
    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ActivateTraceModeRes"];
 
    map_v13::ActivateTraceModeRes *atrRes = new map_v13::ActivateTraceModeRes();

    isNull = (*cfg)["traceSupportIndicator"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["traceSupportIndicator"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        map_v13::ActivateTraceModeRes::TraceSupportIndicator tsi;
        atrRes->SetTraceSupportIndicator(tsi);
    }
    return atrRes;
}

AsnObject* BuildSendAuthenticationInfoArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["SendAuthenticationInfoArg"];
    map_v13::SendAuthenticationInfoArg *saia = new map_v13::SendAuthenticationInfoArg();
    
    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        saia->SetImsi(imsi);
    }

    isNull = (*cfg)["numberOfRequestedVectors"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::NumberOfRequestedVectors norv((*cfg)["numberOfRequestedVectors"]["Value"].asInt());
        saia->SetNumberOfRequestedVectors(norv);
    }
    isAVPEnabled = (*cfg)["segmentationProhibited"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::SendAuthenticationInfoArg::SegmentationProhibited spnull;
        saia->SetSegmentationProhibited(spnull);
    }
    isAVPEnabled = (*cfg)["immediateResponsePreferred"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::SendAuthenticationInfoArg::ImmediateResponsePreferred irpnull;
        saia->SetImmediateResponsePreferred(irpnull);
    }
    isAVPEnabled = (*cfg)["re_synchronisationInfo"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::Re_synchronisationInfo resync;
        isNull = (*cfg)["re_synchronisationInfo"]["RAND"]["Value"].isNull();
        if(!isNull)
        {
            uint8_t ra[8] = {0};
            string cpnum = (*cfg)["re_synchronisationInfo"]["RAND"]["Value"].asString();
            if(cpnum.length() > 32)
            {
                cpnum.erase(32, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(cpnum, ra, 32, 0, true);
            map_v13::RAND rand(MAPUtils::ByteArrayToVector(ra, len));
            resync.SetRand(rand);
        }
        isNull = (*cfg)["re_synchronisationInfo"]["AUTS"]["Value"].isNull();
        if(!isNull)
        {
            uint8_t au[8] = {0};
            string cpnum = (*cfg)["re_synchronisationInfo"]["AUTS"]["Value"].asString();
            if(cpnum.length() > 28)
            {
                cpnum.erase(28, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(cpnum, au, 28, 0, true);
            map_v13::AUTS auts(MAPUtils::ByteArrayToVector(au, len));
            resync.SetAuts(auts);
        }
        saia->SetRe_synchronisationInfo(resync);
    }
    isAVPEnabled = (*cfg)["requestingNodeType"]["Enabled"].asBool();
    isNull = (*cfg)["requestingNodeType"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::RequestingNodeType rnt((*cfg)["requestingNodeType"]["Value"].asInt());
        saia->SetRequestingNodeType(rnt);
    }    
    isAVPEnabled = (*cfg)["requestingPLMN-Id"]["Enabled"].asBool();
    isNull = (*cfg)["requestingPLMN-Id"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_plmnId[3] = {0};
        string plmn = (*cfg)["requestingPLMN-Id"]["Value"].asString();

        if(plmn.length() > 6)
        {
            plmn.erase(6, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(plmn.substr(0, 6), l_plmnId, 6, 0, true);
 
        map_v13::PLMN_Id pid(MAPUtils::ByteArrayToVector(l_plmnId, len));
        saia->SetRequestingPLMN_Id(pid);
    }    
    isAVPEnabled = (*cfg)["numberOfRequestedAdditional_Vectors"]["Enabled"].asBool();
    isNull = (*cfg)["numberOfRequestedAdditional_Vectors"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::NumberOfRequestedVectors norv((*cfg)["numberOfRequestedAdditional_Vectors"]["Value"].asInt());
        saia->SetNumberOfRequestedAdditional_Vectors(norv);
    }    
    isAVPEnabled = (*cfg)["additionalVectorsAreForEPS"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::SendAuthenticationInfoArg::AdditionalVectorsAreForEPS avafenull;
        saia->SetAdditionalVectorsAreForEPS(avafenull);
    }
    return saia;
}

AsnObject* BuildPurgeMSArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["PurgeMSArg"];
    
    map_v13::PurgeMS_Arg *pma = new map_v13::PurgeMS_Arg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        pma->SetImsi(imsi);
    }

    isNull = (*cfg)["vlr_Number"]["Value"].isNull();
    isAVPEnabled = (*cfg)["vlr_Number"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        map_v13::ISDN_AddressString vn(MAPUtils::StringToVector((*cfg)["vlr_Number"]["Value"].asString()));
        pma->SetVlr_Number(vn);
    }

    isNull = (*cfg)["sgsn_Number"]["Value"].isNull();
    isAVPEnabled = (*cfg)["sgsn_Number"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        map_v13::ISDN_AddressString sn(MAPUtils::StringToVector((*cfg)["sgsn_Number"]["Value"].asString()));
        pma->SetSgsn_Number(sn);
    }
    
    return pma;
}

AsnObject* BuildResetArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ResetArg"];

    map_v13::ResetArg *ra = new map_v13::ResetArg();

    isNull = (*cfg)["ISDN_AddressString"]["Value"].isNull();
    if(!isNull)
    {
        map_v13::AddressString adstr(MAPUtils::StringToVector((*cfg)["ISDN_AddressString"]["Value"].asString()));
        ra->SetHlr_Number(adstr);
    }

    isNull = (*cfg)["HLR_List"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["HLR_List"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::HLR_List hlrlist;
        isNull = (*cfg)["HLR_List"]["HLR_Id"]["Value"].isNull();
        if(!isNull)
        {
            Imsi = (*cfg)["HLR_List"]["HLR_Id"]["Value"].asString();
            if (Imsi.length() >= 15)
            {
                // We have strip here becase the IWFArray is sending some extra junk.
                Imsi.erase(15, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
            if (Imsi.length() % 2)
            {
                l_imsi[(Imsi.length() / 2)] |= 0xF0;
            }
            map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
            hlrlist.AddElement(imsi);
        }
        ra->SetHlr_List(hlrlist);
    }

    return ra;
}

AsnObject* BuildInsertSubscriberDataResV13() {

    bool isNull;
    bool isAVPEnabled;

    Json::Value* cfg = &(*m_jsonRoot1)["InsertSubscriberDataRes"];
    map_v13::InsertSubscriberDataRes *isdr = new map_v13::InsertSubscriberDataRes();

    isAVPEnabled = (*cfg)["TeleserviceList"]["Enabled"].asBool();
    isNull = (*cfg)["TeleserviceList"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        isNull = (*cfg)["Ext_TeleserviceCode"]["Value"].isNull();
        if(!isNull)
        {    
            std::vector<byte> ext = MAPUtils::StringToVector((*cfg)["Ext_TeleserviceCode"]["Value"].asString());
            map_v13::TeleserviceList tl;
            tl.AddElement(ext);
            isdr->SetTeleserviceList(tl);
        }    
    }    

    isAVPEnabled = (*cfg)["BearerServiceList"]["Enabled"].asBool();
    isNull = (*cfg)["BearerServiceList"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {    
        isNull = (*cfg)["Ext_BearerServiceCode"]["Value"].isNull();
        if(!isNull)
        {
            std::vector<byte> extbe = MAPUtils::StringToVector((*cfg)["Ext_BearerServiceCode"]["Value"].asString());
            map_v13::BearerServiceList bsl;
            bsl.AddElement(extbe);
            isdr->SetBearerServiceList(bsl);
        }
    }

    isAVPEnabled = (*cfg)["SS_List"]["Enabled"].asBool();
    isNull = (*cfg)["SS_List"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::SS_List sslist;
        isNull = (*cfg)["SS_Code"]["Value"].isNull();
        if(!isNull)
        {
            uint8_t l_ssc[1] = {0};
            std::string ssc = (*cfg)["SS_Code"]["Value"].asString();
            if(ssc.length() > MAX_SS_CODE_DIGITS)
            {
                ssc.erase(MAX_SS_CODE_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(ssc, l_ssc, MAX_SS_CODE_DIGITS, 0, true);

            map_v13::SS_Code sscode(MAPUtils::ByteArrayToVector(l_ssc, len));

            sslist.AddElement(sscode);
            isdr->SetSs_List(sslist);
        }
    }

    isAVPEnabled = (*cfg)["ODB_GeneralData"]["Enabled"].asBool();
    isNull = (*cfg)["ODB_GeneralData"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::ODB_GeneralData odb_gendata(MAPUtils::UnsignedToBitVector(((*cfg)["ODB_GeneralData"]["Value"].asInt()),32));
        isdr->SetOdb_GeneralData(odb_gendata);
    }

    isAVPEnabled = (*cfg)["RegionalSubscriptionResponse"]["Enabled"].asBool();
    isNull = (*cfg)["RegionalSubscriptionResponse"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::RegionalSubscriptionResponse rsr((*cfg)["RegionalSubscriptionResponse"]["Value"].asInt());
        isdr->SetRegionalSubscriptionResponse(rsr);
    }

    isAVPEnabled = (*cfg)["SupportedCamelPhases"]["Enabled"].asBool();
    isNull = (*cfg)["SupportedCamelPhases"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::SupportedCamelPhases scp(MAPUtils::UnsignedToBitVector(((*cfg)["SupportedCamelPhases"]["Value"].asInt()),16));
        isdr->SetSupportedCamelPhases(scp);
    }

    isAVPEnabled = (*cfg)["OfferedCamel4CSIs"]["Enabled"].asBool();
    isNull = (*cfg)["OfferedCamel4CSIs"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::OfferedCamel4CSIs occ(MAPUtils::UnsignedToBitVector(((*cfg)["OfferedCamel4CSIs"]["Value"].asInt()),16));
        isdr->SetOfferedCamel4CSIs(occ);
    }

    isAVPEnabled = (*cfg)["SupportedFeatures"]["Enabled"].asBool();
    isNull = (*cfg)["SupportedFeatures"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        map_v13::SupportedFeatures sf(MAPUtils::UnsignedToBitVector(((*cfg)["SupportedFeatures"]["Value"].asInt()),40));
        isdr->SetSupportedFeatures(sf);
    }

    return isdr;

}
void BuildLocationInformation(map_v13::LocationInformation *li)
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoRes"];


    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["AgeOfLocationInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["AgeOfLocationInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::AgeOfLocationInformation aoli((*cfg)["SubscriberInfo"]["LocationInformation"]["AgeOfLocationInformation"]["Value"].asInt());
        li->SetAgeOfLocationInformation(aoli);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["GeographicalInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["GeographicalInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["GeographicalInformation"]["Value"].asString()));
        li->SetGeographicalInformation(gi);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["vlr_number"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["vlr_number"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ISDN_AddressString isdn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["vlr_number"]["Value"].asString()));
        li->SetVlr_number(isdn);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationNumber"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationNumber"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationNumber ln(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["LocationNumber"]["Value"].asString()));
        li->SetLocationNumber(ln);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::CellGlobalIdOrServiceAreaIdOrLAI cgosa;
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["Value"].isNull();
        if(!isNull)
        {
            map_v13::CellGlobalIdOrServiceAreaIdFixedLength cglen(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["Value"].asString()));
            cgosa.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cglen); 
        }
        else
        {
            isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["LAIFixedLength"]["Value"].isNull();
            if(!isNull)
            {
                map_v13::LAIFixedLength lailen(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["CellGlobalIdOrServiceAreaIdOrLAI"]["LAIFixedLength"]["Value"].asString()));
                cgosa.SetChoiceLaiFixedLength(lailen); 
            }
        }
        li->SetCellGlobalIdOrServiceAreaIdOrLAI(cgosa);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LSAIdentity"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LSAIdentity"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LSAIdentity lsai(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["LSAIdentity"]["Value"].asString()));
        li->SetSelectedLSA_Id(lsai);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["msc_Number"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["msc_Number"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ISDN_AddressString isdn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["msc_Number"]["Value"].asString()));
        li->SetMsc_Number(isdn);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["GeodeticInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["GeodeticInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["GeodeticInformation"]["Value"].asString()));
        li->SetGeodeticInformation(gi);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["currentLocationRetrieved"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["currentLocationRetrieved"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformation::CurrentLocationRetrieved clr;
        li->SetCurrentLocationRetrieved(clr);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["sai_Present"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["sai_Present"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformation::Sai_Present sai;
        li->SetSai_Present(sai);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationEPS lieps; 

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            uint8_t uEUTRANCGI[13] = {0};
            string strEUTRANCGI = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Value"].asString();
            if (strEUTRANCGI.length() > MAX_EUTRAN_CGI_DIGITS)
            {
                strEUTRANCGI.erase(MAX_EUTRAN_CGI_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(strEUTRANCGI, uEUTRANCGI, MAX_EUTRAN_CGI_DIGITS, 0, true);
            map_v13::LocationInformationEPS::E_UTRAN_CGI eucgi(MAPUtils::ByteArrayToVector(uEUTRANCGI, len));
            lieps.SetE_utranCellGlobalIdentity(eucgi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["TA_Id"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["TA_Id"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            uint8_t uTAI[10] = {0};
            string strTAI = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["TA_Id"]["Value"].asString();
            if (strTAI.length() > MAX_TAI_DIGITS)
            {
                strTAI.erase(MAX_TAI_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(strTAI, uTAI, MAX_TAI_DIGITS, 0, true);
            map_v13::LocationInformationEPS::TA_Id taid(MAPUtils::ByteArrayToVector(uTAI, len));
            lieps.SetTrackingAreaIdentity(taid);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeographicalInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeographicalInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            uint8_t uGeographicalInformation[8] = {0};
            string strGeographicalInformation = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeographicalInformation"]["Value"].asString();
            if (strGeographicalInformation.length() > MAX_GEOGRAPHIC_LOCATION_DIGITS)
            {
                strGeographicalInformation.erase(MAX_GEOGRAPHIC_LOCATION_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(strGeographicalInformation, uGeographicalInformation, MAX_GEOGRAPHIC_LOCATION_DIGITS, 0, true);
            map_v13::LocationInformationEPS::GeographicalInformation gi(MAPUtils::ByteArrayToVector(uGeographicalInformation, len));
            lieps.SetGeographicalInformation(gi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeodeticInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeodeticInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            uint8_t uGeodeticInformation[10] = {0};
            string strGeodeticInformation = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["GeodeticInformation"]["Value"].asString();
            if (strGeodeticInformation.length() > MAX_GEODETIC_LOCATION_DIGITS)
            {
                strGeodeticInformation.erase(MAX_GEODETIC_LOCATION_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(strGeodeticInformation, uGeodeticInformation, MAX_GEODETIC_LOCATION_DIGITS, 0, true);
            map_v13::LocationInformationEPS::GeodeticInformation gi(MAPUtils::ByteArrayToVector(uGeodeticInformation, len));
            lieps.SetGeodeticInformation(gi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["currentLocationRetrieved"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["currentLocationRetrieved"]["Enabled"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::CurrentLocationRetrieved clr;
            lieps.SetCurrentLocationRetrieved(clr);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::AgeOfLocationInformation aoli((*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Value"].asInt());
            lieps.SetAgeOfLocationInformation(aoli);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["mme_name"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["mme_name"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::DiameterIdentity di(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["LocationInformationEPS"]["mme_name"]["Value"].asString()));
            lieps.SetMme_Name(di);
        }
        li->SetLocationInformationEPS(lieps);    
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UserCSGInformation uci;

        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["CSG_Id"]["Value"].isNull();
        if(!isNull)
        {
            map_v13::UserCSGInformation::CSG_Id csgidi(MAPUtils::UnsignedToBitVector((*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["CSG_Id"]["Value"].asInt(),27));
            uci.SetCsg_Id(csgidi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["accessMode"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["accessMode"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UserCSGInformation::AccessMode am(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["accessMode"]["Value"].asString()));
            uci.SetAccessMode(am);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["cmi"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["cmi"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UserCSGInformation::Cmi cmi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformation"]["UserCSGInformation"]["cmi"]["Value"].asString()));
            uci.SetCmi(cmi);
        }

        li->SetUserCSGInformation(uci);
    }
}

void BuildLocationInformationGPRS(map_v13::LocationInformationGPRS *ligprs)
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoRes"];

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].isNull();
    map_v13::LocationInformationGPRS::CellGlobalIdOrServiceAreaIdOrLAI cgosa;

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["CellGlobalIdOrServiceAreaIdFixedLength"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["CellGlobalIdOrServiceAreaIdFixedLength"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationGPRS::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["CellGlobalIdOrServiceAreaIdFixedLength"]["Value"].asString()));
        cgosa.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cgi);
    }
    else
    {
        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["LAIFixedLength"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["LAIFixedLength"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationGPRS::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength laifl(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["CellGlobalIdOrServiceAreaIdOrLAI"]["LAIFixedLength"]["Value"].asString()));
            cgosa.SetChoiceLaiFixedLength(laifl);
        }
    }
    ligprs->SetCellGlobalIdOrServiceAreaIdOrLAI(cgosa);

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["RAIdentity"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["RAIdentity"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::RAIdentity rai(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["RAIdentity"]["Value"].asString()));
        ligprs->SetRouteingAreaIdentity(rai);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeographicalInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeographicalInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeographicalInformation"]["Value"].asString()));
        ligprs->SetGeographicalInformation(gi);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["sgsn_Number"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["sgsn_Number"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::ISDN_AddressString isdn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["sgsn_Number"]["Value"].asString()));
        ligprs->SetSgsn_Number(isdn);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["LSAIdentity"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["LSAIdentity"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LSAIdentity lsa(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["LSAIdentity"]["Value"].asString()));
        ligprs->SetSelectedLSAIdentity(lsa);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["sai_Present"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["sai_Present"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationGPRS::Sai_Present sai;
        ligprs->SetSai_Present(sai);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeodeticInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeodeticInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["GeodeticInformation"]["Value"].asString()));
        ligprs->SetGeodeticInformation(gi);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["currentLocationRetrieved"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["currentLocationRetrieved"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationGPRS::CurrentLocationRetrieved clr;
        ligprs->SetCurrentLocationRetrieved(clr);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["AgeOfLocationInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["AgeOfLocationInformation"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::AgeOfLocationInformation aoli((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["AgeOfLocationInformation"]["Value"].asInt());
        ligprs->SetAgeOfLocationInformation(aoli);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::UserCSGInformation uci;

        isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["CSG_Id"]["Value"].isNull();
        if(!isNull)
        {
            map_v13::UserCSGInformation::CSG_Id csgidi(MAPUtils::UnsignedToBitVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["CSG_Id"]["Value"].asInt(),27));
            uci.SetCsg_Id(csgidi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["accessMode"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["accessMode"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UserCSGInformation::AccessMode am(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["accessMode"]["Value"].asString()));
            uci.SetAccessMode(am);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["cmi"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["cmi"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::UserCSGInformation::Cmi cmi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["UserCSGInformation"]["cmi"]["Value"].asString()));
            uci.SetCmi(cmi);
        }

        ligprs->SetUserCSGInformation(uci);
    }

}

void BuildEPS_SubscriberState(map_v13::PS_SubscriberState *psstate)
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoRes"];
    isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["notProvidedFromSGSNorMME"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["notProvidedFromSGSNorMME"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::PS_SubscriberState::NotProvidedFromSGSNorMME np;
        psstate->SetChoiceNotProvidedFromSGSNorMME(np);
    }
    else
    {
        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_Detached"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_Detached"]["Enabled"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::PS_SubscriberState::Ps_Detached ps;
            psstate->SetChoicePs_Detached(ps);
        }
        else
        {
            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_AttachedNotReachableForPaging"]["Enabled"].asBool();
            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_AttachedNotReachableForPaging"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PS_SubscriberState::Ps_AttachedNotReachableForPaging psA;
                psstate->SetChoicePs_AttachedNotReachableForPaging(psA);
            }
            else
            {
                isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_AttachedReachableForPaging"]["Enabled"].asBool();
                isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_AttachedReachableForPaging"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::PS_SubscriberState::Ps_AttachedReachableForPaging ps;
                    psstate->SetChoicePs_AttachedReachableForPaging(ps);
                }
                else
                {
                    isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["Enabled"].asBool();
                    isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["Enabled"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::PS_SubscriberState::PDP_ContextInfoList pdp;
                        map_v13::PDP_ContextInfo pdpinfo;
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].isNull();
                        if(!isNull)
                        {
                            map_v13::PDP_ContextInfo::ContextId cid((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].asInt());
                            pdpinfo.SetPdp_ContextIdentifier(cid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Pdp_ContextActive pdpact;
                            pdpinfo.SetPdp_ContextActive(pdpact);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Type pdptype(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].asString()));
                            pdpinfo.SetPdp_Type(pdptype);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].asString()));
                            pdpinfo.SetPdp_Address(pdpadd);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].asString()));
                            pdpinfo.SetApn_Subscribed(apn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].asString()));
                            pdpinfo.SetApn_InUse(apn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::NSAPI nsapi((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].asInt());
                            pdpinfo.SetNsapi(nsapi);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TransactionId tid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].asString()));
                            pdpinfo.SetTransactionId(tid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].asString()));
                            pdpinfo.SetTeid_ForGnAndGp(teid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].asString()));
                            pdpinfo.SetTeid_ForIu(teid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].asString()));
                            pdpinfo.SetGgsn_Address(gsn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos_Subscribed(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].asString()));
                            pdpinfo.SetQos_Requested(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos_Negotiated(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GPRSChargingID gprs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].asString()));
                            pdpinfo.SetChargingId(gprs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].asString()));
                            pdpinfo.SetChargingCharacteristics(cc);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].asString()));
                            pdpinfo.SetRnc_Address(gsn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos2_Subscribed(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].asString()));
                            pdpinfo.SetQos2_Requested(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos2_Negotiated(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos3_Subscribed(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].asString()));
                            pdpinfo.SetQos3_Requested(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos3_Negotiated(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos4_Subscribed(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].asString()));
                            pdpinfo.SetQos4_Requested(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos4_Negotiated(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_PDP_Type extpdp(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].asString()));
                            pdpinfo.SetExt_pdp_Type(extpdp);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].asString()));
                            pdpinfo.SetExt_pdp_Address(pdpadd);
                        }

                        pdp.AddElement(pdpinfo);
                        psstate->SetChoicePs_PDP_ActiveNotReachableForPaging(pdp);
                    }
                    else
                    {
                        isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["Enabled"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PS_SubscriberState::PDP_ContextInfoList pdp;
                            map_v13::PDP_ContextInfo pdpinfo;
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].isNull();
                            if(!isNull)
                            {
                                map_v13::PDP_ContextInfo::ContextId cid((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].asInt());
                                pdpinfo.SetPdp_ContextIdentifier(cid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Pdp_ContextActive pdpact;
                                pdpinfo.SetPdp_ContextActive(pdpact);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Type pdptype(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].asString()));
                                pdpinfo.SetPdp_Type(pdptype);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].asString()));
                                pdpinfo.SetPdp_Address(pdpadd);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].asString()));
                                pdpinfo.SetApn_Subscribed(apn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].asString()));
                                pdpinfo.SetApn_InUse(apn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::NSAPI nsapi((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].asInt());
                                pdpinfo.SetNsapi(nsapi);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TransactionId tid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].asString()));
                                pdpinfo.SetTransactionId(tid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].asString()));
                                pdpinfo.SetTeid_ForGnAndGp(teid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].asString()));
                                pdpinfo.SetTeid_ForIu(teid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].asString()));
                                pdpinfo.SetGgsn_Address(gsn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos_Subscribed(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].asString()));
                                pdpinfo.SetQos_Requested(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos_Negotiated(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GPRSChargingID gprs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].asString()));
                                pdpinfo.SetChargingId(gprs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].asString()));
                                pdpinfo.SetChargingCharacteristics(cc);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].asString()));
                                pdpinfo.SetRnc_Address(gsn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos2_Subscribed(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].asString()));
                                pdpinfo.SetQos2_Requested(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos2_Negotiated(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos3_Subscribed(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].asString()));
                                pdpinfo.SetQos3_Requested(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos3_Negotiated(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos4_Subscribed(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].asString()));
                                pdpinfo.SetQos4_Requested(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos4_Negotiated(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_PDP_Type extpdp(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].asString()));
                                pdpinfo.SetExt_pdp_Type(extpdp);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].asString()));
                                pdpinfo.SetExt_pdp_Address(pdpadd);
                            }

                            pdp.AddElement(pdpinfo);
                            psstate->SetChoicePs_PDP_ActiveReachableForPaging(pdp);
                        }
                        else
                        {
                            isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["netDetNotReachable"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::NotReachableReason nrr((*cfg)["SubscriberInfo"]["eps_SubscriberState"]["netDetNotReachable"]["Value"].asInt());
                                psstate->SetChoiceNetDetNotReachable(nrr);
                            }
                        }
                    }
                }
            }
        }
    }
}
void BuildPS_SubscriberState(map_v13::PS_SubscriberState *psstate)
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoRes"];
    isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["notProvidedFromSGSNorMME"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["notProvidedFromSGSNorMME"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::PS_SubscriberState::NotProvidedFromSGSNorMME np;
        psstate->SetChoiceNotProvidedFromSGSNorMME(np);
    }
    else
    {
        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_Detached"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_Detached"]["Enabled"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::PS_SubscriberState::Ps_Detached ps;
            psstate->SetChoicePs_Detached(ps);
        }
        else
        {
            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_AttachedNotReachableForPaging"]["Enabled"].asBool();
            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_AttachedNotReachableForPaging"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::PS_SubscriberState::Ps_AttachedNotReachableForPaging psA;
                psstate->SetChoicePs_AttachedNotReachableForPaging(psA);
            }
            else
            {
                isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_AttachedReachableForPaging"]["Enabled"].asBool();
                isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_AttachedReachableForPaging"]["Enabled"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::PS_SubscriberState::Ps_AttachedReachableForPaging ps;
                    psstate->SetChoicePs_AttachedReachableForPaging(ps);
                }
                else
                {
                    isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["Enabled"].asBool();
                    isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["Enabled"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::PS_SubscriberState::PDP_ContextInfoList pdp;
                        map_v13::PDP_ContextInfo pdpinfo;
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].isNull();
                        if(!isNull)
                        {
                            map_v13::PDP_ContextInfo::ContextId cid((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].asInt());
                            pdpinfo.SetPdp_ContextIdentifier(cid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Pdp_ContextActive pdpact;
                            pdpinfo.SetPdp_ContextActive(pdpact);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Type pdptype(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].asString()));
                            pdpinfo.SetPdp_Type(pdptype);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].asString()));
                            pdpinfo.SetPdp_Address(pdpadd);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].asString()));
                            pdpinfo.SetApn_Subscribed(apn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].asString()));
                            pdpinfo.SetApn_InUse(apn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::NSAPI nsapi((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].asInt());
                            pdpinfo.SetNsapi(nsapi);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TransactionId tid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].asString()));
                            pdpinfo.SetTransactionId(tid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].asString()));
                            pdpinfo.SetTeid_ForGnAndGp(teid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].asString()));
                            pdpinfo.SetTeid_ForIu(teid);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].asString()));
                            pdpinfo.SetGgsn_Address(gsn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos_Subscribed(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].asString()));
                            pdpinfo.SetQos_Requested(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos_Negotiated(eqs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GPRSChargingID gprs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].asString()));
                            pdpinfo.SetChargingId(gprs);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].asString()));
                            pdpinfo.SetChargingCharacteristics(cc);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].asString()));
                            pdpinfo.SetRnc_Address(gsn);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos2_Subscribed(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].asString()));
                            pdpinfo.SetQos2_Requested(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos2_Negotiated(ext2);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos3_Subscribed(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].asString()));
                            pdpinfo.SetQos3_Requested(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos3_Negotiated(ext3);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].asString()));
                            pdpinfo.SetQos4_Subscribed(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].asString()));
                            pdpinfo.SetQos4_Requested(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].asString()));
                            pdpinfo.SetQos4_Negotiated(ext4);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::Ext_PDP_Type extpdp(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].asString()));
                            pdpinfo.SetExt_pdp_Type(extpdp);
                        }

                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveNotReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].asString()));
                            pdpinfo.SetExt_pdp_Address(pdpadd);
                        }

                        pdp.AddElement(pdpinfo);
                        psstate->SetChoicePs_PDP_ActiveNotReachableForPaging(pdp);
                    }
                    else
                    {
                        isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["Enabled"].asBool();
                        isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["Enabled"].isNull();
                        if((!isNull) && isAVPEnabled)
                        {
                            map_v13::PS_SubscriberState::PDP_ContextInfoList pdp;
                            map_v13::PDP_ContextInfo pdpinfo;
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].isNull();
                            if(!isNull)
                            {
                                map_v13::PDP_ContextInfo::ContextId cid((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextIdentifier"]["Value"].asInt());
                                pdpinfo.SetPdp_ContextIdentifier(cid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["pdp_ContextActive"]["Enabled"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Pdp_ContextActive pdpact;
                                pdpinfo.SetPdp_ContextActive(pdpact);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Type pdptype(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Type"]["Value"].asString()));
                                pdpinfo.SetPdp_Type(pdptype);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["PDP_Address"]["Value"].asString()));
                                pdpinfo.SetPdp_Address(pdpadd);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_Subscribed"]["Value"].asString()));
                                pdpinfo.SetApn_Subscribed(apn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::APN apn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["apn_InUse"]["Value"].asString()));
                                pdpinfo.SetApn_InUse(apn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::NSAPI nsapi((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["nsapi"]["Value"].asInt());
                                pdpinfo.SetNsapi(nsapi);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TransactionId tid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["TransactionId"]["Value"].asString()));
                                pdpinfo.SetTransactionId(tid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForGnAndGp"]["Value"].asString()));
                                pdpinfo.SetTeid_ForGnAndGp(teid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::TEID teid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["teid_ForIu"]["Value"].asString()));
                                pdpinfo.SetTeid_ForIu(teid);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ggsn_Address"]["Value"].asString()));
                                pdpinfo.SetGgsn_Address(gsn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos_Subscribed(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Requested"]["Value"].asString()));
                                pdpinfo.SetQos_Requested(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_QoS_Subscribed eqs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos_Negotiated(eqs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GPRSChargingID gprs(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["GPRSChargingID"]["Value"].asString()));
                                pdpinfo.SetChargingId(gprs);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::ChargingCharacteristics cc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ChargingCharacteristics"]["Value"].asString()));
                                pdpinfo.SetChargingCharacteristics(cc);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::GSN_Address gsn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["rnc_Address"]["Value"].asString()));
                                pdpinfo.SetRnc_Address(gsn);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos2_Subscribed(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Requested"]["Value"].asString()));
                                pdpinfo.SetQos2_Requested(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext2_QoS_Subscribed ext2(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos2_Negotiated(ext2);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos3_Subscribed(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Requested"]["Value"].asString()));
                                pdpinfo.SetQos3_Requested(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos3_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext3_QoS_Subscribed ext3(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos2_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos3_Negotiated(ext3);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Subscribed"]["Value"].asString()));
                                pdpinfo.SetQos4_Subscribed(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Requested"]["Value"].asString()));
                                pdpinfo.SetQos4_Requested(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext4_QoS_Subscribed ext4(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["qos4_Negotiated"]["Value"].asString()));
                                pdpinfo.SetQos4_Negotiated(ext4);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::Ext_PDP_Type extpdp(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Type"]["Value"].asString()));
                                pdpinfo.SetExt_pdp_Type(extpdp);
                            }

                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::PDP_ContextInfo::PDP_Address pdpadd(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["ps_PDP_ActiveReachableForPaging"]["PDP_ContextInfo"]["ext_pdp_Address"]["Value"].asString()));
                                pdpinfo.SetExt_pdp_Address(pdpadd);
                            }

                            pdp.AddElement(pdpinfo);
                            psstate->SetChoicePs_PDP_ActiveReachableForPaging(pdp);
                        }
                        else
                        {
                            isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                            isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["netDetNotReachable"]["Value"].isNull();
                            if((!isNull) && isAVPEnabled)
                            {
                                map_v13::NotReachableReason nrr((*cfg)["SubscriberInfo"]["PS_SubscriberState"]["netDetNotReachable"]["Value"].asInt());
                                psstate->SetChoiceNetDetNotReachable(nrr);
                            }
                        }
                    }
                }
            }
        }
    }
}

AsnObject* BuildProvideSubscriberInfoResV13()
{

    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string Imei = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];
    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];

    Json::Value* cfg = &(*m_jsonRoot1)["ProvideSubscriberInfoRes"];

    map_v13::ProvideSubscriberInfoRes *psir = new map_v13::ProvideSubscriberInfoRes();
    map_v13::SubscriberInfo subinfo;
    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformation"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformation"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformation li;
        BuildLocationInformation(&li);
        subinfo.SetLocationInformation(li);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["SubscriberState"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["SubscriberState"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::SubscriberState ss;

        isAVPEnabled = (*cfg)["SubscriberInfo"]["SubscriberState"]["assumedIdle"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["SubscriberState"]["assumedIdle"]["Enabled"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::SubscriberState::AssumedIdle ai;
            ss.SetChoiceAssumedIdle(ai);
        }
        else
        {
            isAVPEnabled = (*cfg)["SubscriberInfo"]["SubscriberState"]["camelBusy"]["Enabled"].asBool();
            isNull = (*cfg)["SubscriberInfo"]["SubscriberState"]["camelBusy"]["Enabled"].isNull();
            if((!isNull) && isAVPEnabled)
            {
                map_v13::SubscriberState::CamelBusy cb;
                ss.SetChoiceCamelBusy(cb);
            }
            else
            {
                isAVPEnabled = (*cfg)["SubscriberInfo"]["SubscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                isNull = (*cfg)["SubscriberInfo"]["SubscriberState"]["netDetNotReachable"]["Value"].isNull();
                if((!isNull) && isAVPEnabled)
                {
                    map_v13::SubscriberState::NotReachableReason nrr((*cfg)["SubscriberInfo"]["SubscriberState"]["netDetNotReachable"]["Value"].asInt());
                    ss.SetChoiceNetDetNotReachable(nrr);
                }
                else
                {   
                    isAVPEnabled = (*cfg)["SubscriberInfo"]["SubscriberState"]["notProvidedFromVLR"]["Enabled"].asBool();
                    isNull = (*cfg)["SubscriberInfo"]["SubscriberState"]["notProvidedFromVLR"]["Value"].isNull();
                    if((!isNull) && isAVPEnabled)
                    {
                        map_v13::SubscriberState::NotProvidedFromVLR npfr;
                        ss.SetChoiceNotProvidedFromVLR(npfr);
                    }   
                }
            }
        }
        subinfo.SetSubscriberState(ss);    
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationGPRS"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationGPRS ligprs;
        BuildLocationInformationGPRS(&ligprs);
        subinfo.SetLocationInformationGPRS(ligprs);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["PS_SubscriberState"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::PS_SubscriberState psstate;
        BuildPS_SubscriberState(&psstate);
        subinfo.SetPs_SubscriberState(psstate);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["GPRSMSClass"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["GPRSMSClass"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::GPRSMSClass gprsm;
        isNull = (*cfg)["SubscriberInfo"]["GPRSMSClass"]["MSNetworkCapability"]["Value"].isNull();
        if(!isNull)
        {
            map_v13::GPRSMSClass::MSNetworkCapability msnc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["GPRSMSClass"]["MSNetworkCapability"]["Value"].asString()));
            gprsm.SetMSNetworkCapability(msnc);
        }
        isAVPEnabled = (*cfg)["SubscriberInfo"]["GPRSMSClass"]["MSRadioAccessCapability"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["GPRSMSClass"]["MSRadioAccessCapability"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::GPRSMSClass::MSRadioAccessCapability msrc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["GPRSMSClass"]["MSRadioAccessCapability"]["Value"].asString()));
            gprsm.SetMSRadioAccessCapability(msrc);
        }
        subinfo.SetGprs_MS_Class(gprsm);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["IMEI"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["IMEI"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        Imei = (*cfg)["SubscriberInfo"]["IMEI"]["Value"].asString();
        if (Imei.length() >= 16)
        {    
            // We have strip here becase the IWFArray is sending some extra junk.
            Imei.erase(16, std::string::npos);
        }    

        int len = MAPUtils::StringToTBCD(Imei, l_imsi, MAP_MAX_E164_SZ);
        if (Imei.length() % 2) 
        {    
            l_imsi[(Imei.length() / 2)] |= 0xF0;
        }    
        map_v13::IMEI imei(MAPUtils::ByteArrayToVector(l_imsi, len));
        subinfo.SetImei(imei);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["Enabled"].asBool();
    isAVPEnabled = (*cfg)["SubscriberInfo"]["MS_Classmark2"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["MS_Classmark2"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::MS_Classmark2 msc(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["MS_Classmark2"]["Value"].asString()));
        subinfo.SetMs_Classmark2(msc);
    }
    
    isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::MNPInfoRes mnpinfo;
        isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["RouteingNumber"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["RouteingNumber"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MNPInfoRes::RouteingNumber rn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["MNPInfoRes"]["RouteingNumber"]["Value"].asString()));
            mnpinfo.SetRouteingNumber(rn);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["IMSI"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["IMSI"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            Imsi = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["IMSI"]["Value"].asString();
            if (Imsi.length() >= 15)
            {
                // We have strip here becase the IWFArray is sending some extra junk.
                Imsi.erase(15, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
            if (Imsi.length() % 2)
            {
                l_imsi[(Imsi.length() / 2)] |= 0xF0;
            }
            map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
            mnpinfo.SetImsi(imsi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["msisdn"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["msisdn"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MNPInfoRes::ISDN_AddressString isdn(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["MNPInfoRes"]["msisdn"]["Value"].asString()));
            mnpinfo.SetMsisdn(isdn);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["NumberPortabilityStatus"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["MNPInfoRes"]["NumberPortabilityStatus"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::MNPInfoRes::NumberPortabilityStatus nps((*cfg)["SubscriberInfo"]["MNPInfoRes"]["NumberPortabilityStatus"]["Value"].asInt());
            mnpinfo.SetNumberPortabilityStatus(nps);
        }
        subinfo.SetMnpInfoRes(mnpinfo);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["IMS_VoiceOverPS_SessionsInd"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["IMS_VoiceOverPS_SessionsInd"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::IMS_VoiceOverPS_SessionsInd imsv((*cfg)["SubscriberInfo"]["IMS_VoiceOverPS_SessionsInd"]["Value"].asInt());
        subinfo.SetImsVoiceOverPS_SessionsIndication(imsv);
    }
   
    isAVPEnabled = (*cfg)["SubscriberInfo"]["lastUE_ActivityTime"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["lastUE_ActivityTime"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        uint8_t uLastUEActivityTime[4] = {0};
        string strLastUEActivityTime = (*cfg)["SubscriberInfo"]["lastUE_ActivityTime"]["Value"].asString();
        if (strLastUEActivityTime.length() > MAX_EUTRAN_CGI_DIGITS)
        {
            strLastUEActivityTime.erase(MAX_EUTRAN_CGI_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(strLastUEActivityTime, uLastUEActivityTime, MAX_EUTRAN_CGI_DIGITS, 0, true);
        map_v13::Time time(MAPUtils::ByteArrayToVector(uLastUEActivityTime, len));
        subinfo.SetLastUE_ActivityTime(time);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["lastRAT_Type"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["lastRAT_Type"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::Used_RAT_Type urt((*cfg)["SubscriberInfo"]["lastRAT_Type"]["Value"].asInt());
        subinfo.SetLastRAT_Type(urt);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["Enabled"].asBool();
    isAVPEnabled = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["eps_SubscriberState"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::PS_SubscriberState psstate;
        BuildEPS_SubscriberState(&psstate);
        subinfo.SetEps_SubscriberState(psstate);
    }

    isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["Enabled"].asBool();
    isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["Enabled"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        map_v13::LocationInformationEPS lieps;

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::E_UTRAN_CGI eucgi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["E_UTRAN_CGI"]["Value"].asString()));
            lieps.SetE_utranCellGlobalIdentity(eucgi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["TA_Id"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["TA_Id"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::TA_Id taid(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["TA_Id"]["Value"].asString()));
            lieps.SetTrackingAreaIdentity(taid);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeographicalInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeographicalInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeographicalInformation"]["Value"].asString()));
            lieps.SetGeographicalInformation(gi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeodeticInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeodeticInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::GeodeticInformation geoi(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["GeodeticInformation"]["Value"].asString()));
            lieps.SetGeodeticInformation(geoi);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["currentLocationRetrieved"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["currentLocationRetrieved"]["Enabled"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::CurrentLocationRetrieved clr;
            lieps.SetCurrentLocationRetrieved(clr);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::AgeOfLocationInformation aoli((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["AgeOfLocationInformation"]["Value"].asInt());
            lieps.SetAgeOfLocationInformation(aoli);
        }

        isAVPEnabled = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["mme_name"]["Enabled"].asBool();
        isNull = (*cfg)["SubscriberInfo"]["LocationInformationEPS"]["mme_name"]["Value"].isNull();
        if((!isNull) && isAVPEnabled)
        {
            map_v13::LocationInformationEPS::DiameterIdentity di(MAPUtils::StringToVector((*cfg)["SubscriberInfo"]["LocationInformationEPS"]["mme_name"]["Value"].asString()));
            lieps.SetMme_Name(di);
        }
        subinfo.SetLocationInformationEPS(lieps);    
    }
    psir->SetSubscriberInfo(subinfo);

    return psir;
}

AsnObject* BuildReadyForSM_ArgV13()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];

    Json::Value l_jsonRoot = parseMapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["map_v13"];


    Json::Value* cfg = &(*m_jsonRoot1)["ReadyForSM_Arg"];

    map_v13::ReadyForSM_Arg *rfsArg = new map_v13::ReadyForSM_Arg();

    isNull = (*cfg)["IMSI"]["Value"].isNull();
    if(!isNull)
    {
        Imsi = (*cfg)["IMSI"]["Value"].asString();
        if (Imsi.length() >= 15)
        {
            // We have strip here becase the IWFArray is sending some extra junk.
            Imsi.erase(15, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(Imsi, l_imsi, MAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        map_v13::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        rfsArg->SetImsi(imsi);
    }
    
    isNull = (*cfg)["AlertReason"]["Value"].isNull();
    if(!isNull)
    {
        rfsArg->SetAlertReason(new map_v13::AlertReason((*cfg)["AlertReason"]["Value"].asInt()));
    }

    isAVPEnabled = (*cfg)["alertReasonIndicator"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::ReadyForSM_Arg::AlertReasonIndicator ari;
        rfsArg->SetAlertReasonIndicator(ari);
    }

    isAVPEnabled = (*cfg)["additionalAlertReasonIndicator"]["Enabled"].asBool();
    if(isAVPEnabled)
    {
        map_v13::ReadyForSM_Arg::AdditionalAlertReasonIndicator aari;
        rfsArg->SetAdditionalAlertReasonIndicator(aari);
    }
    return rfsArg;

}








