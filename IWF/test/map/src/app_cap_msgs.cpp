bool IsBusyornoAnswerSet = false;
bool sendERBandACRinTcContAgain = false;
bool simulateFollowOnCases = false;
extern ITS_UINT oPC;

Json::Value parseCapConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;
    char cwd[1024] = {0};
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        snprintf(cwd + strlen(cwd), 1024,"/cap_tools.json");
        APP_TRACE_DEBUG(("current working directory= %s ",cwd));
        char *jsonFile = cwd;
        if (jsonFile == NULL )
        {
            APP_TRACE_ERROR(("cap_tools.json is not present"));
            exit(0);
        }
        APP_TRACE_DEBUG(("DRE_JSON=%s",jsonFile));

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

void ParseTransactionInput(UserAutoData* userData)
{
    bool isNull;
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["user_auto"];

    Json::Value* cfgTrans = &(*m_jsonRoot1)["Transaction"];

    // Transaction related
    isNull = (*cfgTrans)["TransactionType"].isNull();
    if(!isNull)
    {
        userData->transactionType = (*cfgTrans)["TransactionType"].asInt();
    }
    isNull = (*cfgTrans)["OperationClass"].isNull();
    if(!isNull)
    {
        userData->operationClass = (*cfgTrans)["OperationClass"].asInt();
    }
    isNull = (*cfgTrans)["Operation"].isNull();
    if(!isNull)
    {
        userData->operation = (*cfgTrans)["Operation"].asInt();
    }
}

void ParseAndSetSCCPAddress(UserAutoData* userData)
{
    bool isNull;
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["user_auto"];

    Json::Value* cfgSccp = &(*m_jsonRoot1)["sccp"];
    Json::Value* cfgTrans = &(*m_jsonRoot1)["Transaction"];

    // SCCP related
    isNull = (*cfgSccp)["OPC"].isNull();
    if(!isNull)
    {
        userData->opc = (*cfgSccp)["OPC"].asInt();
    }
    isNull = (*cfgSccp)["DPC"].isNull();
    if(!isNull)
    {
        userData->dpc = (*cfgSccp)["DPC"].asInt();
    }
    isNull = (*cfgSccp)["PC"].isNull();
    if(!isNull)
    {
        userData->pc = (*cfgSccp)["PC"].asInt();
    }
    isNull = (*cfgSccp)["DestinationSSN"].isNull();
    if(!isNull)
    {
        userData->destinationSSN = (*cfgSccp)["DestinationSSN"].asInt();
    }
    isNull = (*cfgSccp)["SourceSSN"].isNull();
    if(!isNull)
    {
        userData->sourceSSN = (*cfgSccp)["SourceSSN"].asInt();
    }
    isNull = (*cfgSccp)["GTT"].isNull();
    if(!isNull)
    {
        userData->gtt = (*cfgSccp)["GTT"].asInt();
    }
    isNull = (*cfgSccp)["SetInternationalRouting"].isNull();
    if(!isNull)
    {
        userData->setInternationalRouting = (*cfgSccp)["SetInternationalRouting"].asInt();
    }
#if 0
    // Transaction related
    isNull = (*cfgTrans)["TransactionType"].isNull();
    if(!isNull)
    {
        userData->transactionType = (*cfgTrans)["TransactionType"].asInt();
    }
    isNull = (*cfgTrans)["OperationClass"].isNull();
    if(!isNull)
    {
        userData->operationClass = (*cfgTrans)["OperationClass"].asInt();
    }
    isNull = (*cfgTrans)["Operation"].isNull();
    if(!isNull)
    {
        userData->operation = (*cfgTrans)["Operation"].asInt();
    }
#endif
}

AsnObject* BuildCapEndMsg(int opcode)
{
    AsnObject *obj= NULL;

    switch(opcode)
    {
        case OP_eventReportBCSM:
            {
                if(IDPVersionBuilt == IDP_V1)	
                    obj = BuildEventReportBCSMArginTcEndV1();
                else if(IDPVersionBuilt == IDP_V2)	
                    obj = BuildEventReportBCSMArginTcEndV2();
                else if(IDPVersionBuilt == IDP_V3)	
                    obj = BuildEventReportBCSMArginTcEnd();
                break;
            }
        case OP_applyChargingReport:
            {   
                if(IDPVersionBuilt == IDP_V3)	
                    obj = BuildApplyChargingReportinTcEnd();
                else 	
                    obj = BuildApplyChargingReportinTcEndV2();
                break;
            }

        default:
            {   
                cout << "--------------------------------------------------" << endl;
                cout << "Worng choice" << endl;
            }
    }
}

AsnObject* BuildCapMsg(int opCode)
{
    AsnObject *obj= NULL;

    switch(opCode)
    {
        case OP_initialDP:
            {
                switch(IDPVersionBuilt)
                {
                    case IDP_V1:
                        obj = BuildInitialDPArgV1();
                        break;
                    case IDP_V2:
                        obj = BuildInitialDPArgV2();
                        break;
                    case IDP_V3:
                        obj = BuildInitialDPArg();
                        break;
                }
                break;
            }
        case OP_eventReportBCSM:
	    {
		    sendERBandACRinTcContAgain = true;
		    if(IDPVersionBuilt == IDP_V1)	
			    obj = BuildEventReportBCSMArginTcContV1();
		    else if(IDPVersionBuilt == IDP_V2)	
			    obj = BuildEventReportBCSMArginTcContV2();
		    else if(IDPVersionBuilt == IDP_V3)	
			    obj = BuildEventReportBCSMArginTcCont();
		    sendERBandACRinTcContAgain = false;
		break;
	    }
        case OP_applyChargingReport:
        {   
            sendERBandACRinTcContAgain = true;
            if(IDPVersionBuilt == IDP_V3)	
                obj = BuildApplyChargingReportinTcCont();
            else 	
                obj = BuildApplyChargingReportinTcContV2();
            sendERBandACRinTcContAgain = false;
            break;
        }
        case OP_initialDPSMS:
            {
                obj = BuildInitialDPSMSArg();
                break;
            }
        case OP_eventReportSMS:
            {
                obj = BuildEventReportSMSArg();
                break;
            }
        case OP_releaseCall:
            {   
                break;
            }   
        case OP_requestReportBCSMEvent:
            {   
                break;
            }   
        case OP_applyCharging:
            {   
                break;
            }   
        case OP_activityTest:
            {   
                break;
            }   
        default:
            {   
                cout << "--------------------------------------------------" << endl;
                cout << "Worng choice" << endl;
            }   
    }

    return obj;
}

AsnObject* BuildApplyChargingReport()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["ApplyChargingReportArg"];


    cap_v3::CAMEL_CallResult camelresult; 

    isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ReceivingSideID rid;
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
 
            rid.SetChoiceReceivingSideID(lt);
            tdcr.SetPartyToCharge(rid);
        }
        
        cap_v3::TimeInformation ti;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::TimeInformation::TimeIfNoTariffSwitch tint((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].asInt());
            ti.SetChoiceTimeIfNoTariffSwitch(tint);
            tdcr.SetTimeInformation(ti);
        }
        else
        {
           isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].isNull();
           isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].asBool();
           if(!isNull && isAVPEnabled)
           {
                cap_v3::TimeInformation::TimeIfTariffSwitch tits;

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].isNull();
                if(!isNull)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TimeSinceTariffSwitch tsts((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].asInt());
                    tits.SetTimeSinceTariffSwitch(tsts);
                }

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].isNull();
                isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TariffSwitchInterval tsi((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].asInt());
                    tits.SetTariffSwitchInterval(tsi);
                }
                ti.SetChoiceTimeIfTariffSwitch(tits);
                tdcr.SetTimeInformation(ti);
           }
        }
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].isNull();
        if(!isNull)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].asBool());
            tdcr.SetCallActive(ca);
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallReleasedAtTcpExpiry cr;
            tdcr.SetCallReleasedAtTcpExpiry(cr);
        }
        
        camelresult.SetChoiceTimeDurationChargingResult(tdcr);

    }
    cout << camelresult;
    Octets *camelresultBuf = camelresult.Encode();
    cout<<"octets camelresultBuf :"<<*camelresultBuf<<endl;
    cap_v3::ApplyChargingReportArg *acr = new cap_v3::ApplyChargingReportArg(camelresultBuf->GetArray());
    cout<<"ACR : "<<*(acr->Encode())<<endl;
    
    return acr;
}

AsnObject* BuildApplyChargingReportinTcCont()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont_Again"];
    else if(simulateFollowOnCases)
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont_Again_For_FollowOn"];
    else
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont"];


    cap_v3::CAMEL_CallResult camelresult; 

    isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ReceivingSideID rid;
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
 
            rid.SetChoiceReceivingSideID(lt);
            tdcr.SetPartyToCharge(rid);
        }
        
        cap_v3::TimeInformation ti;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::TimeInformation::TimeIfNoTariffSwitch tint((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].asInt());
            ti.SetChoiceTimeIfNoTariffSwitch(tint);
            tdcr.SetTimeInformation(ti);
        }
        else
        {
           isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].isNull();
           isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].asBool();
           if(!isNull && isAVPEnabled)
           {
                cap_v3::TimeInformation::TimeIfTariffSwitch tits;

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].isNull();
                if(!isNull)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TimeSinceTariffSwitch tsts((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].asInt());
                    tits.SetTimeSinceTariffSwitch(tsts);
                }

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].isNull();
                isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TariffSwitchInterval tsi((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].asInt());
                    tits.SetTariffSwitchInterval(tsi);
                }
                ti.SetChoiceTimeIfTariffSwitch(tits);
                tdcr.SetTimeInformation(ti);
           }
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].isNull();
        if(!isNull)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].asBool());
            tdcr.SetCallActive(ca);
        }
#if 0
        if(sendERBandACRinTcContAgain || sendERBandACRinTcEnd)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(false);
            tdcr.SetCallActive(ca);
        }
        else
        {
            if(gsentACRContinue)
            {
                cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(true);
                tdcr.SetCallActive(ca);
                gsentACRContinue = false;
            }
            else
            {
                cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(false);
                tdcr.SetCallActive(ca);
            }
        }
#endif
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallReleasedAtTcpExpiry cr;
            tdcr.SetCallReleasedAtTcpExpiry(cr);
        }
        
        camelresult.SetChoiceTimeDurationChargingResult(tdcr);

    }
    cout << camelresult;
    Octets *camelresultBuf = camelresult.Encode();
    cout<<"octets camelresultBuf :"<<*camelresultBuf<<endl;
    cap_v3::ApplyChargingReportArg *acr = new cap_v3::ApplyChargingReportArg(camelresultBuf->GetArray());
    cout<<"ACR : "<<*(acr->Encode())<<endl;
    
    return acr;
}

AsnObject* BuildApplyChargingReportinTcContV2()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont_Again"];
    else if(simulateFollowOnCases)
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont_Again_For_FollowOn"];
    else
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont"];


    cap_v2::CAMEL_CallResult camelresult; 

    isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::CAMEL_CallResult::TimeDurationChargingResult tdcr;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::ReceivingSideID rid;
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v2::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
 
            rid.SetChoiceReceivingSideID(lt);
            tdcr.SetPartyToCharge(rid);
        }
        
        cap_v2::TimeInformation ti;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::TimeInformation::TimeIfNoTariffSwitch tint((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].asInt());
            ti.SetChoiceTimeIfNoTariffSwitch(tint);
            tdcr.SetTimeInformation(ti);
        }
        else
        {
           isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].isNull();
           isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].asBool();
           if(!isNull && isAVPEnabled)
           {
                cap_v2::TimeInformation::TimeIfTariffSwitch tits;

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].isNull();
                if(!isNull)
                {
                    cap_v2::TimeInformation::TimeIfTariffSwitch::TimeSinceTariffSwitch tsts((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].asInt());
                    tits.SetTimeSinceTariffSwitch(tsts);
                }

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].isNull();
                isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v2::TimeInformation::TimeIfTariffSwitch::TariffSwitchInterval tsi((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].asInt());
                    tits.SetTariffSwitchInterval(tsi);
                }
                ti.SetChoiceTimeIfTariffSwitch(tits);
                tdcr.SetTimeInformation(ti);
           }
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].isNull();
        if(!isNull)
        {
            cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].asBool());
            tdcr.SetCallActive(ca);
        }
#if 0
        if(sendERBandACRinTcContAgain || sendERBandACRinTcEnd)
        {
            cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(false);
            tdcr.SetCallActive(ca);
        }
        else
        {
            if(gsentACRContinue)
            {
                cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(true);
                tdcr.SetCallActive(ca);
                gsentACRContinue = false;
            }
            else
            {
                cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca(false);
                tdcr.SetCallActive(ca);
            }
        }
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallReleasedAtTcpExpiry cr;
            tdcr.SetCallReleasedAtTcpExpiry(cr);
        }
#endif
        
        camelresult.SetChoiceTimeDurationChargingResult(tdcr);

    }
    cout << camelresult;
    Octets *camelresultBuf = camelresult.Encode();
    cout<<"octets camelresultBuf :"<<*camelresultBuf<<endl;
    cap_v2::ApplyChargingReportArg *acr = new cap_v2::ApplyChargingReportArg(camelresultBuf->GetArray());
    cout<<"ACR : "<<*(acr->Encode())<<endl;
    
    return acr;
}

AsnObject* BuildApplyChargingReportinTcEndV2()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcEnd"];


    cap_v2::CAMEL_CallResult camelresult; 

    isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::CAMEL_CallResult::TimeDurationChargingResult tdcr;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::ReceivingSideID rid;
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v2::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
 
            rid.SetChoiceReceivingSideID(lt);
            tdcr.SetPartyToCharge(rid);
        }
        
        cap_v2::TimeInformation ti;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::TimeInformation::TimeIfNoTariffSwitch tint((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].asInt());
            ti.SetChoiceTimeIfNoTariffSwitch(tint);
            tdcr.SetTimeInformation(ti);
        }
        else
        {
           isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].isNull();
           isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].asBool();
           if(!isNull && isAVPEnabled)
           {
                cap_v2::TimeInformation::TimeIfTariffSwitch tits;

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].isNull();
                if(!isNull)
                {
                    cap_v2::TimeInformation::TimeIfTariffSwitch::TimeSinceTariffSwitch tsts((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].asInt());
                    tits.SetTimeSinceTariffSwitch(tsts);
                }

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].isNull();
                isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v2::TimeInformation::TimeIfTariffSwitch::TariffSwitchInterval tsi((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].asInt());
                    tits.SetTariffSwitchInterval(tsi);
                }
                ti.SetChoiceTimeIfTariffSwitch(tits);
                tdcr.SetTimeInformation(ti);
           }
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].isNull();
        if(!isNull)
        {
            cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].asBool());
            tdcr.SetCallActive(ca);
        }
#if 0
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::CAMEL_CallResult::TimeDurationChargingResult::CallReleasedAtTcpExpiry cr;
            tdcr.SetCallReleasedAtTcpExpiry(cr);
        }
#endif   
        camelresult.SetChoiceTimeDurationChargingResult(tdcr);

    }
    cout << camelresult;
    Octets *camelresultBuf = camelresult.Encode();
    cout<<"octets camelresultBuf :"<<*camelresultBuf<<endl;
    cap_v2::ApplyChargingReportArg *acr = new cap_v2::ApplyChargingReportArg(camelresultBuf->GetArray());
    cout<<"ACR : "<<*(acr->Encode())<<endl;
    
    return acr;
}

AsnObject* BuildApplyChargingReportinTcEnd()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcEnd"];


    cap_v3::CAMEL_CallResult camelresult; 

    isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CAMEL_CallResult::TimeDurationChargingResult tdcr;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ReceivingSideID rid;
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["partyToCharge"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
 
            rid.SetChoiceReceivingSideID(lt);
            tdcr.SetPartyToCharge(rid);
        }
        
        cap_v3::TimeInformation ti;
        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::TimeInformation::TimeIfNoTariffSwitch tint((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfNoTariffSwitch"]["Value"].asInt());
            ti.SetChoiceTimeIfNoTariffSwitch(tint);
            tdcr.SetTimeInformation(ti);
        }
        else
        {
           isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].isNull();
           isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["Enabled"].asBool();
           if(!isNull && isAVPEnabled)
           {
                cap_v3::TimeInformation::TimeIfTariffSwitch tits;

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].isNull();
                if(!isNull)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TimeSinceTariffSwitch tsts((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["timeSinceTariffSwitch"]["Value"].asInt());
                    tits.SetTimeSinceTariffSwitch(tsts);
                }

                isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].isNull();
                isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::TimeInformation::TimeIfTariffSwitch::TariffSwitchInterval tsi((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["timeInformation"]["timeIfTariffSwitch"]["tariffSwitchInterval"]["Value"].asInt());
                    tits.SetTariffSwitchInterval(tsi);
                }
                ti.SetChoiceTimeIfTariffSwitch(tits);
                tdcr.SetTimeInformation(ti);
           }
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].isNull();
        if(!isNull)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallActive ca((*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callActive"]["Enabled"].asBool());
            tdcr.SetCallActive(ca);
        }

        isNull = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["CallResult"]["camel_callresult"]["timeDurationChargingResult"]["callReleasedAtTcpExpiry"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::CAMEL_CallResult::TimeDurationChargingResult::CallReleasedAtTcpExpiry cr;
            tdcr.SetCallReleasedAtTcpExpiry(cr);
        }
        
        camelresult.SetChoiceTimeDurationChargingResult(tdcr);

    }
    cout << camelresult;
    Octets *camelresultBuf = camelresult.Encode();
    cout<<"octets camelresultBuf :"<<*camelresultBuf<<endl;
    cap_v3::ApplyChargingReportArg *acr = new cap_v3::ApplyChargingReportArg(camelresultBuf->GetArray());
    cout<<"ACR : "<<*(acr->Encode())<<endl;
    
    return acr;
}

AsnObject* BuildEventReportSMSArg()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportSMSArg"];
    cap_v3::EventReportSMSArg *erb = new cap_v3::EventReportSMSArg();
 

    isNull = (*cfg)["eventTypeSMS"]["Value"].isNull();
    if(!isNull)
    {
        cap_v3::EventTypeSMS etb((*cfg)["eventTypeSMS"]["Value"].asInt());
        erb->SetEventTypeSMS(etb);
    }
    
    isNull = (*cfg)["eventSpecificInformationSMS"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationSMS"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        EventSpecificInformationSMS esisms;
        isNull = (*cfg)["eventSpecificInformationSMS"]["o_smsFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationSMS"]["o_smsFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            EventSpecificInformationSMS::O_smsFailureSpecificInfo osms;
            isNull = (*cfg)["eventSpecificInformationSMS"]["o_smsFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationSMS"]["o_smsFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::SMSCause sms((*cfg)["eventSpecificInformationSMS"]["o_smsFailureSpecificInfo"]["failureCause"]["Value"].asInt());
                osms.SetFailureCause(sms);
                esisms.SetChoiceO_smsFailureSpecificInfo(osms);
                erb->SetEventSpecificInformationSMS(esisms);
            }
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationSMS"]["o_smsSubmittedSpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationSMS"]["o_smsSubmittedSpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::EventSpecificInformationSMS::O_smsSubmittedSpecificInfo osmssub;
                esisms.SetChoiceO_smsSubmittedSpecificInfo(osmssub);
                erb->SetEventSpecificInformationSMS(esisms);
            }
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }

    return erb;
}

AsnObject* BuildEventReportBCSMArg()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];
    cap_v3::EventReportBCSMArg *erb = new cap_v3::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        cap_v3::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        erb->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::EventSpecificInformationBCSM esib;

        isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo rsf;

            isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                uint8_t l_cause[2] = {0};
                string cse = ((*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].asString()); 
                if(cse.length() > MAX_CAUSE_DIGITS)
                {    
                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                }    
                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                rsf.SetFailureCause(cause);
            }
            esib.SetChoiceRouteSelectFailureSpecificInfo(rsf);
            erb->SetEventSpecificInformationBCSM(esib);
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo ocpb;
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    uint8_t l_cause[2] = {0};
                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].asString());
                    if(cse.length() > MAX_CAUSE_DIGITS)
                    {    
                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                    }    
                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                    ocpb.SetBusyCause(cause);
                }
                esib.SetChoiceOCalledPartyBusySpecificInfo(ocpb);
                erb->SetEventSpecificInformationBCSM(esib);
            }
            else
            {
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::EventSpecificInformationBCSM::ONoAnswerSpecificInfo onoa;
                    esib.SetChoiceONoAnswerSpecificInfo(onoa);
                    erb->SetEventSpecificInformationBCSM(esib);
                }
                else
                {
                    isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo oasi;

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            uint8_t l_destinationaddress[18] = {0};
                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                            {
                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                            }

                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                            oasi.SetDestinationAddress(cpn);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::Or_Call oc;
                            oasi.SetOr_Call(oc);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::ForwardedCall fc;
                            oasi.SetForwardedCall(fc);
                        }
                        esib.SetChoiceOAnswerSpecificInfo(oasi);
                        erb->SetEventSpecificInformationBCSM(esib);
                    }
                    else
                    {
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

                            isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                uint8_t l_cause[2] = {0};
                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                if(cse.length() > MAX_CAUSE_DIGITS)
                                {    
                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                }    
                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                odis.SetReleaseCause(cause);
                            }
                            esib.SetChoiceODisconnectSpecificInfo(odis);
                            erb->SetEventSpecificInformationBCSM(esib);
                        }
                        else
                        {
                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo tbsi;

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    uint8_t l_cause[2] = {0};
                                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].asString()); 
                                    if(cse.length() > MAX_CAUSE_DIGITS)
                                    {    
                                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                    }    
                                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                    tbsi.SetBusyCause(cause);
                                }

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::CallForwarded cf;
                                    tbsi.SetCallForwarded(cf);
                                }

                                esib.SetChoiceTBusySpecificInfo(tbsi);
                                erb->SetEventSpecificInformationBCSM(esib);
                            }
                            else
                            {
                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo tasi;

                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo::CallForwarded cf;
                                        tasi.SetCallForwarded(cf);
                                    }
                                    esib.SetChoiceTNoAnswerSpecificInfo(tasi);
                                    erb->SetEventSpecificInformationBCSM(esib);
                                }
                                else
                                {
                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo oasi;

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            uint8_t l_destinationaddress[18] = {0};
                                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                                            {
                                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                                            }

                                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                                            oasi.SetDestinationAddress(cpn);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::Or_Call oc;
                                            oasi.SetOr_Call(oc);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::ForwardedCall fc;
                                            oasi.SetForwardedCall(fc);
                                        }
                                        esib.SetChoiceTAnswerSpecificInfo(oasi);
                                        erb->SetEventSpecificInformationBCSM(esib);
                                    }
                                    else
                                    {
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

                                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                                            if(!isNull && isAVPEnabled)
                                            {
                                                uint8_t l_cause[2] = {0};
                                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                                if(cse.length() > MAX_CAUSE_DIGITS)
                                                {    
                                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                                }    
                                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                                odis.SetReleaseCause(cause);
                                            }
                                            esib.SetChoiceTDisconnectSpecificInfo(odis);
                                            erb->SetEventSpecificInformationBCSM(esib);
                                        }                
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        { 
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            rsid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(rsid);
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;

}

AsnObject* BuildEventReportBCSMArginTcContV2()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again"];
    else if(simulateFollowOnCases)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again_For_FollowOn"];
    else
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];


    cap_v2::EventReportBCSMArg *erb = new cap_v2::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        cap_v2::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        erb->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::EventSpecificInformationBCSM esib;

        isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo rsf;

            isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                uint8_t l_cause[2] = {0};
                string cse = ((*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].asString()); 
                if(cse.length() > MAX_CAUSE_DIGITS)
                {    
                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                }    
                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v2::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                rsf.SetFailureCause(cause);
            }
            esib.SetChoiceRouteSelectFailureSpecificInfo(rsf);
            erb->SetEventSpecificInformationBCSM(esib);
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v2::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo ocpb;
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    uint8_t l_cause[2] = {0};
                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].asString());
                    if(cse.length() > MAX_CAUSE_DIGITS)
                    {    
                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                    }    
                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v2::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                    ocpb.SetBusyCause(cause);
                }
                esib.SetChoiceOCalledPartyBusySpecificInfo(ocpb);
                erb->SetEventSpecificInformationBCSM(esib);
            }
            else
            {
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v2::EventSpecificInformationBCSM::ONoAnswerSpecificInfo onoa;
                    esib.SetChoiceONoAnswerSpecificInfo(onoa);
                    erb->SetEventSpecificInformationBCSM(esib);
                }
                else
                {
                    isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo oasi;
#if 0
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            uint8_t l_destinationaddress[18] = {0};
                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                            {
                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                            }

                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                            oasi.SetDestinationAddress(cpn);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::Or_Call oc;
                            oasi.SetOr_Call(oc);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::ForwardedCall fc;
                            oasi.SetForwardedCall(fc);
                        }
#endif
                        esib.SetChoiceOAnswerSpecificInfo(oasi);
                        erb->SetEventSpecificInformationBCSM(esib);
                    }
                    else
                    {
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

                            isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                uint8_t l_cause[2] = {0};
                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                if(cse.length() > MAX_CAUSE_DIGITS)
                                {    
                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                }    
                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v2::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                odis.SetReleaseCause(cause);
                            }
                            esib.SetChoiceODisconnectSpecificInfo(odis);
                            erb->SetEventSpecificInformationBCSM(esib);
                        }
                        else
                        {
                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo tbsi;

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    uint8_t l_cause[2] = {0};
                                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].asString()); 
                                    if(cse.length() > MAX_CAUSE_DIGITS)
                                    {    
                                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                    }    
                                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                    tbsi.SetBusyCause(cause);
                                }

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo::CallForwarded cf;
                                    tbsi.SetCallForwarded(cf);
                                }

                                esib.SetChoiceTBusySpecificInfo(tbsi);
                                erb->SetEventSpecificInformationBCSM(esib);
                            }
                            else
                            {
                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v2::EventSpecificInformationBCSM::TNoAnswerSpecificInfo tasi;

                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v2::EventSpecificInformationBCSM::TNoAnswerSpecificInfo::CallForwarded cf;
                                        tasi.SetCallForwarded(cf);
                                    }
                                    esib.SetChoiceTNoAnswerSpecificInfo(tasi);
                                    erb->SetEventSpecificInformationBCSM(esib);
                                }
                                else
                                {
                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo oasi;
#if 0
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            uint8_t l_destinationaddress[18] = {0};
                                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                                            {
                                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                                            }

                                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                                            oasi.SetDestinationAddress(cpn);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::Or_Call oc;
                                            oasi.SetOr_Call(oc);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::ForwardedCall fc;
                                            oasi.SetForwardedCall(fc);
                                        }
#endif
                                        esib.SetChoiceTAnswerSpecificInfo(oasi);
                                        erb->SetEventSpecificInformationBCSM(esib);
                                    }
                                    else
                                    {
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

                                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                                            if(!isNull && isAVPEnabled)
                                            {
                                                uint8_t l_cause[2] = {0};
                                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                                if(cse.length() > MAX_CAUSE_DIGITS)
                                                {    
                                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                                }    
                                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                                cap_v2::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                                odis.SetReleaseCause(cause);
                                            }
                                            esib.SetChoiceTDisconnectSpecificInfo(odis);
                                            erb->SetEventSpecificInformationBCSM(esib);
                                        }                
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        { 
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v2::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            rsid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(rsid);
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v2::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;

}

AsnObject* BuildEventReportBCSMArginTcEndV1()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];
    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcEnd"];

    cap_v1::EventReportBCSMArg *erb = new cap_v1::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        int val = (*cfg)["eventTypeBCSM"]["Value"].asInt();
        cap_v1::EventTypeBCSM etb(val);
        erb->SetEventTypeBCSM(etb);
        if(val == 5 || val == 6 || val == 13 || val == 14)
		IsBusyornoAnswerSet = true;
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
	    cap_v1::EventSpecificInformationBCSM esib;
	    isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
	    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
	    if(!isNull && isAVPEnabled)
	    {
		    cap_v1::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

		    isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
		    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
		    if(!isNull && isAVPEnabled)
		    {
			    uint8_t l_cause[2] = {0};
			    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
			    if(cse.length() > MAX_CAUSE_DIGITS)
			    {    
				    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
			    }    
			    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

			    cap_v1::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
			    odis.SetReleaseCause(cause);
		    }
		    esib.SetChoiceODisconnectSpecificInfo(odis);
		    erb->SetEventSpecificInformationBCSM(esib);
	    }
	    else
	    {
		    isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
		    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
		    if(!isNull && isAVPEnabled)
		    {
			    cap_v1::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

			    isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
			    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
			    if(!isNull && isAVPEnabled)
			    {
				    uint8_t l_cause[2] = {0};
				    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
				    if(cse.length() > MAX_CAUSE_DIGITS)
				    {    
					    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
				    }    
				    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
				    cap_v1::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
				    odis.SetReleaseCause(cause);
			    }
			    esib.SetChoiceTDisconnectSpecificInfo(odis);
			    erb->SetEventSpecificInformationBCSM(esib);
		    }
	    }

    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
	cap_v1::LegID legid;
        //cap_v1::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        { 
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v1::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            legid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(legid);
        }
	else
	{
		isNull = (*cfg)["legID"]["sendingSideID"]["Value"].isNull();
		isAVPEnabled = (*cfg)["legID"]["sendingSideID"]["Enabled"].asBool();
		if(!isNull && isAVPEnabled)
		{ 
			uint8_t l_rsi[1] = {0};
			string rsi = (*cfg)["legID"]["sendingSideID"]["Value"].asString();
			if(rsi.length() > MAX_LEG_ID_DIGITS)
			{
				rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
			}
			int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
			cap_v1::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
			legid.SetChoiceReceivingSideID(lt);
			//Setting out object inside because of only one choice
			erb->SetLegID(legid);
		}
	}
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v1::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;
}

AsnObject* BuildEventReportBCSMArginTcContV1()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again"];
    else if(simulateFollowOnCases)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again_For_FollowOn"];
    else
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];

    cap_v1::EventReportBCSMArg *erb = new cap_v1::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        int val = (*cfg)["eventTypeBCSM"]["Value"].asInt();
        cap_v1::EventTypeBCSM etb(val);
        erb->SetEventTypeBCSM(etb);
        if(val == 5 || val == 6 || val == 13 || val == 14)
		IsBusyornoAnswerSet = true;
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
	    cap_v1::EventSpecificInformationBCSM esib;
	    isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
	    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
	    if(!isNull && isAVPEnabled)
	    {
		    cap_v1::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

		    isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
		    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
		    if(!isNull && isAVPEnabled)
		    {
			    uint8_t l_cause[2] = {0};
			    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
			    if(cse.length() > MAX_CAUSE_DIGITS)
			    {    
				    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
			    }    
			    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

			    cap_v1::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
			    odis.SetReleaseCause(cause);
		    }
		    esib.SetChoiceODisconnectSpecificInfo(odis);
		    erb->SetEventSpecificInformationBCSM(esib);
	    }
	    else
	    {
		    isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
		    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
		    if(!isNull && isAVPEnabled)
		    {
			    cap_v1::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

			    isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
			    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
			    if(!isNull && isAVPEnabled)
			    {
				    uint8_t l_cause[2] = {0};
				    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
				    if(cse.length() > MAX_CAUSE_DIGITS)
				    {    
					    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
				    }    
				    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
				    cap_v1::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
				    odis.SetReleaseCause(cause);
			    }
			    esib.SetChoiceTDisconnectSpecificInfo(odis);
			    erb->SetEventSpecificInformationBCSM(esib);
		    }
	    }

    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
	cap_v1::LegID legid;
        //cap_v1::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        { 
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v1::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            legid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(legid);
        }
	else
	{
		isNull = (*cfg)["legID"]["sendingSideID"]["Value"].isNull();
		isAVPEnabled = (*cfg)["legID"]["sendingSideID"]["Enabled"].asBool();
		if(!isNull && isAVPEnabled)
		{ 
			uint8_t l_rsi[1] = {0};
			string rsi = (*cfg)["legID"]["sendingSideID"]["Value"].asString();
			if(rsi.length() > MAX_LEG_ID_DIGITS)
			{
				rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
			}
			int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
			cap_v1::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
			legid.SetChoiceReceivingSideID(lt);
			//Setting out object inside because of only one choice
			erb->SetLegID(legid);
		}
	}
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v1::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;
}

AsnObject* BuildEventReportBCSMArginTcCont()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again"];
    else if(simulateFollowOnCases)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again_For_FollowOn"];
    else
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];

    cap_v3::EventReportBCSMArg *erb = new cap_v3::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        int val = (*cfg)["eventTypeBCSM"]["Value"].asInt();
        cap_v3::EventTypeBCSM etb(val);
        erb->SetEventTypeBCSM(etb);
        if(val == 5 || val == 6 || val == 13 || val == 14)
            IsBusyornoAnswerSet = true;
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::EventSpecificInformationBCSM esib;

        isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo rsf;

            isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                uint8_t l_cause[2] = {0};
                string cse = ((*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].asString()); 
                if(cse.length() > MAX_CAUSE_DIGITS)
                {    
                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                }    
                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                rsf.SetFailureCause(cause);
            }
            esib.SetChoiceRouteSelectFailureSpecificInfo(rsf);
            erb->SetEventSpecificInformationBCSM(esib);
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo ocpb;
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    uint8_t l_cause[2] = {0};
                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].asString());
                    if(cse.length() > MAX_CAUSE_DIGITS)
                    {    
                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                    }    
                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                    ocpb.SetBusyCause(cause);
                }
                esib.SetChoiceOCalledPartyBusySpecificInfo(ocpb);
                erb->SetEventSpecificInformationBCSM(esib);
            }
            else
            {
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::EventSpecificInformationBCSM::ONoAnswerSpecificInfo onoa;
                    esib.SetChoiceONoAnswerSpecificInfo(onoa);
                    erb->SetEventSpecificInformationBCSM(esib);
                }
                else
                {
                    isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo oasi;

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            uint8_t l_destinationaddress[18] = {0};
                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                            {
                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                            }

                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                            oasi.SetDestinationAddress(cpn);

                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::Or_Call oc;
                            oasi.SetOr_Call(oc);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::ForwardedCall fc;
                            oasi.SetForwardedCall(fc);
                        }
                        esib.SetChoiceOAnswerSpecificInfo(oasi);
                        erb->SetEventSpecificInformationBCSM(esib);
                    }
                    else
                    {
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

                            isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                uint8_t l_cause[2] = {0};
                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                if(cse.length() > MAX_CAUSE_DIGITS)
                                {    
                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                }    
                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                odis.SetReleaseCause(cause);
                            }
                            esib.SetChoiceODisconnectSpecificInfo(odis);
                            erb->SetEventSpecificInformationBCSM(esib);
                        }
                        else
                        {
                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo tbsi;

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    uint8_t l_cause[2] = {0};
                                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].asString()); 
                                    if(cse.length() > MAX_CAUSE_DIGITS)
                                    {    
                                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                    }    
                                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                    tbsi.SetBusyCause(cause);
                                }

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::CallForwarded cf;
                                    tbsi.SetCallForwarded(cf);
                                }

                                esib.SetChoiceTBusySpecificInfo(tbsi);
                                erb->SetEventSpecificInformationBCSM(esib);
                            }
                            else
                            {
                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo tasi;

                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo::CallForwarded cf;
                                        tasi.SetCallForwarded(cf);
                                    }
                                    esib.SetChoiceTNoAnswerSpecificInfo(tasi);
                                    erb->SetEventSpecificInformationBCSM(esib);
                                }
                                else
                                {
                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo oasi;

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            uint8_t l_destinationaddress[18] = {0};
                                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                                            {
                                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                                            }

                                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                                            oasi.SetDestinationAddress(cpn);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::Or_Call oc;
                                            oasi.SetOr_Call(oc);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::ForwardedCall fc;
                                            oasi.SetForwardedCall(fc);
                                        }
                                        esib.SetChoiceTAnswerSpecificInfo(oasi);
                                        erb->SetEventSpecificInformationBCSM(esib);
                                    }
                                    else
                                    {
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

                                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                                            if(!isNull && isAVPEnabled)
                                            {
                                                uint8_t l_cause[2] = {0};
                                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                                if(cse.length() > MAX_CAUSE_DIGITS)
                                                {    
                                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                                }    
                                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                                odis.SetReleaseCause(cause);
                                            }
                                            esib.SetChoiceTDisconnectSpecificInfo(odis);
                                            erb->SetEventSpecificInformationBCSM(esib);
                                        }                
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        { 
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            rsid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(rsid);
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;
}

AsnObject* BuildEventReportBCSMArginTcEnd()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcEnd"];
    cap_v3::EventReportBCSMArg *erb = new cap_v3::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        cap_v3::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        erb->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::EventSpecificInformationBCSM esib;

        isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo rsf;

            isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                uint8_t l_cause[2] = {0};
                string cse = ((*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].asString()); 
                if(cse.length() > MAX_CAUSE_DIGITS)
                {    
                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                }    
                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                rsf.SetFailureCause(cause);
            }
            esib.SetChoiceRouteSelectFailureSpecificInfo(rsf);
            erb->SetEventSpecificInformationBCSM(esib);
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo ocpb;
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    uint8_t l_cause[2] = {0};
                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].asString());
                    if(cse.length() > MAX_CAUSE_DIGITS)
                    {    
                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                    }    
                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                    ocpb.SetBusyCause(cause);
                }
                esib.SetChoiceOCalledPartyBusySpecificInfo(ocpb);
                erb->SetEventSpecificInformationBCSM(esib);
            }
            else
            {
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::EventSpecificInformationBCSM::ONoAnswerSpecificInfo onoa;
                    esib.SetChoiceONoAnswerSpecificInfo(onoa);
                    erb->SetEventSpecificInformationBCSM(esib);
                }
                else
                {
                    isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo oasi;

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            uint8_t l_destinationaddress[18] = {0};
                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                            {
                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                            }

                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                            oasi.SetDestinationAddress(cpn);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::Or_Call oc;
                            oasi.SetOr_Call(oc);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::ForwardedCall fc;
                            oasi.SetForwardedCall(fc);
                        }
                        esib.SetChoiceOAnswerSpecificInfo(oasi);
                        erb->SetEventSpecificInformationBCSM(esib);
                    }
                    else
                    {
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

                            isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                uint8_t l_cause[2] = {0};
                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                if(cse.length() > MAX_CAUSE_DIGITS)
                                {    
                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                }    
                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                odis.SetReleaseCause(cause);
                            }
                            esib.SetChoiceODisconnectSpecificInfo(odis);
                            erb->SetEventSpecificInformationBCSM(esib);
                        }
                        else
                        {
                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo tbsi;

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    uint8_t l_cause[2] = {0};
                                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].asString()); 
                                    if(cse.length() > MAX_CAUSE_DIGITS)
                                    {    
                                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                    }    
                                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                    tbsi.SetBusyCause(cause);
                                }

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::CallForwarded cf;
                                    tbsi.SetCallForwarded(cf);
                                }

                                esib.SetChoiceTBusySpecificInfo(tbsi);
                                erb->SetEventSpecificInformationBCSM(esib);
                            }
                            else
                            {
                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo tasi;

                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TNoAnswerSpecificInfo::CallForwarded cf;
                                        tasi.SetCallForwarded(cf);
                                    }
                                    esib.SetChoiceTNoAnswerSpecificInfo(tasi);
                                    erb->SetEventSpecificInformationBCSM(esib);
                                }
                                else
                                {
                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo oasi;

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            uint8_t l_destinationaddress[18] = {0};
                                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                                            {
                                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                                            }

                                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                                            oasi.SetDestinationAddress(cpn);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::Or_Call oc;
                                            oasi.SetOr_Call(oc);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::ForwardedCall fc;
                                            oasi.SetForwardedCall(fc);
                                        }
                                        esib.SetChoiceTAnswerSpecificInfo(oasi);
                                        erb->SetEventSpecificInformationBCSM(esib);
                                    }
                                    else
                                    {
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

                                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                                            if(!isNull && isAVPEnabled)
                                            {
                                                uint8_t l_cause[2] = {0};
                                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                                if(cse.length() > MAX_CAUSE_DIGITS)
                                                {    
                                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                                }    
                                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                                odis.SetReleaseCause(cause);
                                            }
                                            esib.SetChoiceTDisconnectSpecificInfo(odis);
                                            erb->SetEventSpecificInformationBCSM(esib);
                                        }                
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            rsid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(rsid);
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;
}

AsnObject* BuildEventReportBCSMArginTcEndV2()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcEnd"];
    cap_v2::EventReportBCSMArg *erb = new cap_v2::EventReportBCSMArg();
 

    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    if(!isNull)
    {
        cap_v2::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        erb->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::EventSpecificInformationBCSM esib;

        isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo rsf;

            isNull = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                uint8_t l_cause[2] = {0};
                string cse = ((*cfg)["eventSpecificInformationBCSM"]["routeSelectFailureSpecificInfo"]["failureCause"]["Value"].asString()); 
                if(cse.length() > MAX_CAUSE_DIGITS)
                {    
                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                }    
                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v2::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                rsf.SetFailureCause(cause);
            }
            esib.SetChoiceRouteSelectFailureSpecificInfo(rsf);
            erb->SetEventSpecificInformationBCSM(esib);
        }
        else
        {
            isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v2::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo ocpb;
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    uint8_t l_cause[2] = {0};
                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["oCalledPartyBusySpecificInfo"]["busyCause"]["Value"].asString());
                    if(cse.length() > MAX_CAUSE_DIGITS)
                    {    
                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                    }    
                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v2::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                    ocpb.SetBusyCause(cause);
                }
                esib.SetChoiceOCalledPartyBusySpecificInfo(ocpb);
                erb->SetEventSpecificInformationBCSM(esib);
            }
            else
            {
                isNull = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].isNull();
                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oNoAnswerSpecificInfo"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v2::EventSpecificInformationBCSM::ONoAnswerSpecificInfo onoa;
                    esib.SetChoiceONoAnswerSpecificInfo(onoa);
                    erb->SetEventSpecificInformationBCSM(esib);
                }
                else
                {
                    isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo oasi;
#if 0
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            uint8_t l_destinationaddress[18] = {0};
                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                            {
                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                            }

                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                            oasi.SetDestinationAddress(cpn);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::Or_Call oc;
                            oasi.SetOr_Call(oc);
                        }

                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::OAnswerSpecificInfo::ForwardedCall fc;
                            oasi.SetForwardedCall(fc);
                        }
#endif
                        esib.SetChoiceOAnswerSpecificInfo(oasi);
                        erb->SetEventSpecificInformationBCSM(esib);
                    }
                    else
                    {
                        isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["Enabled"].asBool();
                        if(!isNull && isAVPEnabled)
                        {
                            cap_v2::EventSpecificInformationBCSM::ODisconnectSpecificInfo odis;

                            isNull = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                uint8_t l_cause[2] = {0};
                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["oDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                if(cse.length() > MAX_CAUSE_DIGITS)
                                {    
                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                }    
                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v2::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                odis.SetReleaseCause(cause);
                            }
                            esib.SetChoiceODisconnectSpecificInfo(odis);
                            erb->SetEventSpecificInformationBCSM(esib);
                        }
                        else
                        {
                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].isNull();
                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["Enabled"].asBool();
                            if(!isNull && isAVPEnabled)
                            {
                                cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo tbsi;

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    uint8_t l_cause[2] = {0};
                                    string cse = ((*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["busyCause"]["Value"].asString()); 
                                    if(cse.length() > MAX_CAUSE_DIGITS)
                                    {    
                                        cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                    }    
                                    int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                    tbsi.SetBusyCause(cause);
                                }

                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tBusySpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v2::EventSpecificInformationBCSM::TBusySpecificInfo::CallForwarded cf;
                                    tbsi.SetCallForwarded(cf);
                                }

                                esib.SetChoiceTBusySpecificInfo(tbsi);
                                erb->SetEventSpecificInformationBCSM(esib);
                            }
                            else
                            {
                                isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].isNull();
                                isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["Enabled"].asBool();
                                if(!isNull && isAVPEnabled)
                                {
                                    cap_v2::EventSpecificInformationBCSM::TNoAnswerSpecificInfo tasi;

                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tNoAnswerSpecificInfo"]["callForwarded"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v2::EventSpecificInformationBCSM::TNoAnswerSpecificInfo::CallForwarded cf;
                                        tasi.SetCallForwarded(cf);
                                    }
                                    esib.SetChoiceTNoAnswerSpecificInfo(tasi);
                                    erb->SetEventSpecificInformationBCSM(esib);
                                }
                                else
                                {
                                    isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].isNull();
                                    isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["Enabled"].asBool();
                                    if(!isNull && isAVPEnabled)
                                    {
                                        cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo oasi;
#if 0
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            uint8_t l_destinationaddress[18] = {0};
                                            std::string dest = ((*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["destinationAddress"]["Value"].asString());
                                            if(dest.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
                                            {
                                                dest.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
                                            }

                                            int len = MAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += MAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_destinationaddress, len));
                                            oasi.SetDestinationAddress(cpn);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["or_Call"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::Or_Call oc;
                                            oasi.SetOr_Call(oc);
                                        }

                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tAnswerSpecificInfo"]["forwardedCall"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TAnswerSpecificInfo::ForwardedCall fc;
                                            oasi.SetForwardedCall(fc);
                                        }
#endif
                                        esib.SetChoiceTAnswerSpecificInfo(oasi);
                                        erb->SetEventSpecificInformationBCSM(esib);
                                    }
                                    else
                                    {
                                        isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].isNull();
                                        isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["Enabled"].asBool();
                                        if(!isNull && isAVPEnabled)
                                        {
                                            cap_v2::EventSpecificInformationBCSM::TDisconnectSpecificInfo odis;

                                            isNull = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].isNull();
                                            isAVPEnabled = (*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Enabled"].asBool();
                                            if(!isNull && isAVPEnabled)
                                            {
                                                uint8_t l_cause[2] = {0};
                                                string cse = ((*cfg)["eventSpecificInformationBCSM"]["tDisconnectSpecificInfo"]["releaseCause"]["Value"].asString()); 
                                                if(cse.length() > MAX_CAUSE_DIGITS)
                                                {    
                                                    cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
                                                }    
                                                int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                                                cap_v2::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
                                                odis.SetReleaseCause(cause);
                                            }
                                            esib.SetChoiceTDisconnectSpecificInfo(odis);
                                            erb->SetEventSpecificInformationBCSM(esib);
                                        }                
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    isNull = (*cfg)["legID"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["legID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::ReceivingSideID rsid;
        isNull = (*cfg)["legID"]["receivingSideID"]["Value"].isNull();
        isAVPEnabled = (*cfg)["legID"]["receivingSideID"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_rsi[1] = {0};
            string rsi = (*cfg)["legID"]["receivingSideID"]["Value"].asString();
            if(rsi.length() > MAX_LEG_ID_DIGITS)
            {
                rsi.erase(MAX_LEG_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v2::ReceivingSideID::LegType lt(MAPUtils::ByteArrayToVector(l_rsi, len));
            rsid.SetChoiceReceivingSideID(lt);
            //Setting out object inside because of only one choice
            erb->SetLegID(rsid);
        }
    }

    isNull = (*cfg)["miscCallInfo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["miscCallInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::MiscCallInfo msi;
        isNull = (*cfg)["miscCallInfo"]["messageType"]["Value"].isNull();
        if(!isNull)
        {
            cap_v2::MiscCallInfo::MessageType mt((*cfg)["miscCallInfo"]["messageType"]["Value"].asInt());
            msi.SetMessageType(mt);
        }
        
        isNull = (*cfg)["miscCallInfo"]["dpAssignment"]["Value"].isNull();
        isAVPEnabled = (*cfg)["miscCallInfo"]["dpAssignment"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::MiscCallInfo::DpAssignment da((*cfg)["miscCallInfo"]["dpAssignment"]["Value"].asInt());
            msi.SetDpAssignment(da);
        }
        erb->SetMiscCallInfo(msi);
    }
    return erb;
}

AsnObject* BuildInitialDPSMSArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2];
    uint8_t l_timeandtimezone[MAP_MAX_E164_SZ/2];
    uint8_t l_tpvalidityperiod[8] = {0};
    uint8_t l_callinpartynumber[9] = {0};
    uint8_t l_smscaddress[9] = {0};
    uint8_t l_mscaddress[9] = {0};
    uint8_t l_sgsnnumber[9] = {0};
    uint8_t l_callreferencenumber[8] = {0};
    uint8_t l_tpprotoiden[1] = {0};
    uint8_t l_tpdatacodsch[1] = {0};
    uint8_t l_tpshortsms[1] = {0};
    uint8_t l_vlrnumber[9] = {0};
    uint8_t l_mscnumber[9] = {0};
    uint8_t l_locationnumber[10] = {0};
    uint8_t l_destsubsnumber[10] = {0};

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["InitialDPSMSArg"];

    cap_v3::InitialDPSMSArg *idp = new cap_v3::InitialDPSMSArg();

    isNull = (*cfg)["serviceKey"]["Value"].isNull();
    if(!isNull)
    {
        cap_v3::ServiceKey sk((*cfg)["serviceKey"]["Value"].asInt());
        idp->SetServiceKey(sk); 
    }

    isNull = (*cfg)["destinationSubscriberNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["destinationSubscriberNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        std::string destsubsnumber = (*cfg)["destinationSubscriberNumber"]["Value"].asString();
        int len = MAPUtils::StringToTBCD(destsubsnumber.substr(0, MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH), 
                l_destsubsnumber, MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(destsubsnumber.substr(MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH), 
                (l_destsubsnumber+1), MAX_DEST_SUBSCRIBER_NUMBER_DIGITS, 0, false);
        if (destsubsnumber.length() % 2)
        {
            l_destsubsnumber[(destsubsnumber.length() / 2)] |= 0xF0;
        }
 
        cap_v3::CalledPartyBCDNumber cpn(MAPUtils::ByteArrayToVector(l_destsubsnumber, len));
        idp->SetDestinationSubscriberNumber(cpn);
    }

    isNull = (*cfg)["callingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpnum = (*cfg)["callingPartyNumber"]["Value"].asString();
        if(cpnum.length() > MAX_ISDN_ADDRESS_DIGITS)
        {
            cpnum.erase(MAX_ISDN_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(cpnum.substr(0, MAX_ISDN_ADDRESS_HEADER_LENGTH), 
                l_callinpartynumber, MAX_ISDN_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpnum.substr(MAX_ISDN_ADDRESS_HEADER_LENGTH), (l_callinpartynumber+1), MAX_ISDN_ADDRESS_DIGITS);
        if (cpnum.length() % 2)
        {
            l_callinpartynumber[(cpnum.length() / 2)] |= 0xF0;
        }
 
        cap_v3::ISDN_AddressString cpn(MAPUtils::ByteArrayToVector(l_callinpartynumber, len));
        idp->SetCallingPartyNumber(cpn);
    }

    isNull = (*cfg)["eventTypeSMS"]["Value"].isNull();
    isAVPEnabled = (*cfg)["eventTypeSMS"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::EventTypeSMS ets((*cfg)["eventTypeSMS"]["Value"].asInt());
        idp->SetEventTypeSMS(ets);
    }
 
    isNull = (*cfg)["imsi"]["Value"].isNull();
    isAVPEnabled = (*cfg)["imsi"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        Imsi = (*cfg)["imsi"]["Value"].asString();
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
        cap_v3::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        idp->SetIMSI(imsi);
    }
 
    isNull = (*cfg)["locationInformationMSC"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["locationInformationMSC"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::LocationInformation li;
        
        isNull = (*cfg)["locationInformationMSC"]["ageOfLocationInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["ageOfLocationInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::AgeOfLocationInformation aoli((*cfg)["locationInformationMSC"]["ageOfLocationInformation"]["Value"].asInt());
            li.SetAgeOfLocationInformation(aoli);
        }

        isNull = (*cfg)["locationInformationMSC"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["locationInformationMSC"]["geographicalInformation"]["Value"].asString()));
            li.SetGeographicalInformation(gi);
        }

        isNull = (*cfg)["locationInformationMSC"]["vlr_number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["vlr_number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string vlrnum = (*cfg)["locationInformationMSC"]["vlr_number"]["Value"].asString();
            if(vlrnum.length() > MAX_VLR_NUMBER_DIGITS)
            {
                vlrnum.erase(MAX_VLR_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH),
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_vlrnumber, len));
            li.SetVlr_number(isdn);
        }
        
        isNull = (*cfg)["locationInformationMSC"]["locationNumber"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["locationNumber"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string locinfo = (*cfg)["locationInformationMSC"]["locationNumber"]["Value"].asString();
            if(locinfo.length() > MAX_LOCATION_NUMBER_DIGITS)
            {
                locinfo.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH),
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH),
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);

            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0x00;
            }
            cap_v3::LocationInformation::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locationnumber, len));
            li.SetLocationNumber(ln);
        }

        isNull = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI cgi;

            isAVPEnabled = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["Enabled"].asBool();
            if(isAVPEnabled)
            {
                uint8_t tbcd[7] = {0};
                string mcc = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mcc"].asString();
                string mnc = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mnc"].asString();
                string locArea = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["LocationArea"].asString();
                string cellId = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["CellId_Or_SAC"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId/SAC Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    cout << locArea << "tbcd[3]" << tbcd[3] << endl;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    cout << locArea << "tbcd[4]" << tbcd[4] << endl;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    cout << cellId << "tbcd[5]" << tbcd[5] << endl;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                    cout << cellId << "tbcd[6]" << tbcd[6] << endl;
                }
                cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgil(MAPUtils::ByteArrayToVector(tbcd, 7));
                cgi.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cgil);
            }
            else
            {
                isAVPEnabled = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["Enabled"].asBool();
                if(isAVPEnabled)
                {
                    uint8_t tbcd[5] = {0};
                    string mcc = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["mcc"].asString();
                    string mnc = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["mnc"].asString();
                    string locArea = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["LocationArea"].asString();
                    if(mcc.length() != 0  && mnc.length() != 0 )
                    {
                        tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                        if(mnc.length() == 3)
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                        }
                        else
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                        }
                        tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                        tbcd[3] = atoi(locArea.c_str()) >> 8;
                        cout << locArea << "tbcd[3]" << tbcd[3] << endl;
                        tbcd[4] = atoi(locArea.c_str()) & 0xff;
                        cout << locArea << "tbcd[4]" << tbcd[4] << endl;
                    }

                    cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength lai(MAPUtils::ByteArrayToVector(tbcd, 5)); 
                    cgi.SetChoiceLaiFixedLength(lai);
                }
            }
            li.SetCellGlobalIdOrServiceAreaIdOrLAI(cgi);
        }

        isNull = (*cfg)["locationInformationMSC"]["selectedLSA_Id"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["selectedLSA_Id"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_lsaid[3] = {0};
            string lsaId = (*cfg)["locationInformationMSC"]["selectedLSA_Id"]["Value"].asString();
             if(lsaId.length() > MAX_LSA_ID_DIGITS)
            {
                lsaId.erase(MAX_LSA_ID_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::LSAIdentity lsa(MAPUtils::ByteArrayToVector(l_lsaid, len));
 
            li.SetSelectedLSA_Id(lsa);
        }

        isNull = (*cfg)["locationInformationMSC"]["msc_Number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["msc_Number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string mscnum = (*cfg)["locationInformationMSC"]["msc_Number"]["Value"].asString();
            if(mscnum.length() > MAX_MSC_NUMBER_DIGITS)
            {
                mscnum.erase(MAX_MSC_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformationMSC"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["locationInformationMSC"]["geodeticInformation"]["Value"].asString()));
            li.SetGeodeticInformation(gi);
        }

        isNull = (*cfg)["locationInformationMSC"]["currentLocationRetrieved"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["currentLocationRetrieved"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::CurrentLocationRetrieved clr;
            li.SetCurrentLocationRetrieved(clr);
        }
        idp->SetLocationInformationMSC(li);
    }   

    isNull = (*cfg)["locationInformationGPRS"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["locationInformationGPRS"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        LocationInformationGPRS ligprs;
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
        
        if(isAVPEnabled)
        {
            uint8_t tbcd[7] = {0};
            string mcc = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["mcc"].asString();
            string mnc = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["mnc"].asString();
            string locArea = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["LocationArea"].asString();
            string cellId = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["CellId_Or_SAC"].asString();
            if(atoi(cellId.c_str()) > 65535)
            {
                APP_TRACE_ERROR(("CellId/SAC Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                return NULL;
            }
            if(mcc.length() != 0  && mnc.length() != 0 )
            {
                tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                cout << "mcc" << mcc << "tbcd[0]" << tbcd[0] << endl;
                if(mnc.length() == 3)
                {
                    tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                }
                else
                {
                    tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                }
                cout << "mnc" << mnc << "tbcd[1]" << tbcd[1] << endl;
                tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                cout << "tbcd[2]" << tbcd[2] << endl;
                tbcd[3] = atoi(locArea.c_str()) >> 8;
                cout << locArea << "tbcd[3]" << tbcd[3] << endl;
                tbcd[4] = atoi(locArea.c_str()) & 0xff;
                cout << locArea << "tbcd[4]" << tbcd[4] << endl;
                tbcd[5] = atoi(cellId.c_str()) >> 8;
                cout << cellId << "tbcd[5]" << tbcd[5] << endl;
                tbcd[6] = atoi(cellId.c_str()) & 0xff;
                cout << cellId << "tbcd[6]" << tbcd[6] << endl;
            }

            cap_v3::LocationInformationGPRS::CellGlobalIdOrServiceAreaIdOrLAI cgs(MAPUtils::ByteArrayToVector(tbcd, 7));
            ligprs.SetCellGlobalIdOrServiceAreaIdOrLAI(cgs);
        }

        isNull = (*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::RAIdentity rai(MAPUtils::StringToVector((*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Value"].asString()));
            ligprs.SetRouteingAreaIdentity(rai);
        }

        isNull = (*cfg)["locationInformationGPRS"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["locationInformationGPRS"]["geographicalInformation"]["Value"].asString()));
            ligprs.SetGeographicalInformation(gi);
        }

        isNull = (*cfg)["locationInformationGPRS"]["sgsn_Number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["sgsn_Number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string sgsnnumber = (*cfg)["locationInformationGPRS"]["sgsn_Number"]["Value"].asString();
            if(sgsnnumber.length() > MAX_SGSN_NUMBER_DIGITS)
            {
                sgsnnumber.erase(MAX_SGSN_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(sgsnnumber.substr(0, MAX_SGSN_NUMBER_HEADER_LENGTH), l_sgsnnumber, MAX_SGSN_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(sgsnnumber.substr(MAX_SGSN_NUMBER_HEADER_LENGTH), (l_sgsnnumber+1), MAX_SGSN_NUMBER_DIGITS);
            if (sgsnnumber.length() % 2)
            {
                l_sgsnnumber[(sgsnnumber.length() / 2)] |= 0xF0;
            }

            cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_sgsnnumber, len));
 
            ligprs.SetSgsn_Number(isdn);
        }

        isNull = (*cfg)["locationInformationGPRS"]["selectedLSAIdentity"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["selectedLSAIdentity"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_lsaid[3] = {0};
            string lsaId = (*cfg)["locationInformationGPRS"]["selectedLSAIdentity"]["Value"].asString();
            if(lsaId.length() > MAX_LSA_ID_DIGITS)
            {
                lsaId.erase(MAX_LSA_ID_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }

            cap_v3::LSAIdentity lsa(MAPUtils::ByteArrayToVector(l_lsaid, len));
 
            ligprs.SetSelectedLSAIdentity(lsa);
        }

        isNull = (*cfg)["locationInformationGPRS"]["sai_Present"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["sai_Present"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformationGPRS::Sai_Present sai;
            ligprs.SetSai_Present(sai);
        }
        idp->SetLocationInformationGPRS(ligprs);  
    }

    isNull = (*cfg)["sMSCAddress"]["Value"].isNull();
    isAVPEnabled = (*cfg)["sMSCAddress"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string smscaddress = (*cfg)["sMSCAddress"]["Value"].asString();
        if(smscaddress.length() > MAX_MSC_ADDRESS_DIGITS)
        {
            smscaddress.erase(MAX_MSC_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(smscaddress.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_smscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(smscaddress.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), 
                (l_smscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (smscaddress.length() % 2)
        {
            l_smscaddress[(smscaddress.length() / 2)] |= 0xF0;
        }
 
        cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_smscaddress, len));
        idp->SetSMSCAddress(isdn);
    }

    isNull = (*cfg)["timeAndTimezone"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["timeAndTimezone"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        tatz = (*cfg)["timeAndTimezone"]["Value"].asString();
        if(tatz.length() >= MAX_TIME_AND_TIME_ZONE_DIGITS)
        {
            tatz.erase(MAX_TIME_AND_TIME_ZONE_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tatz, l_timeandtimezone, MAP_MAX_E164_SZ);
        cap_v3::TimeAndTimezone tat(MAPUtils::ByteArrayToVector(l_timeandtimezone, len));

        idp->SetTimeAndTimezone(tat);
    }

    isNull = (*cfg)["tPShortMessageSubmissionSpecificInfo"]["Value"].isNull();
    isAVPEnabled = (*cfg)["tPShortMessageSubmissionSpecificInfo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string tpshortmsg = (*cfg)["tPShortMessageSubmissionSpecificInfo"]["Value"].asString();
        if(tpshortmsg.length() >= MAX_TP_SHORT_MESSAGE_SUB_SPE_INFO_DIGITS)
        {
            tpshortmsg.erase(MAX_TP_SHORT_MESSAGE_SUB_SPE_INFO_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tpshortmsg, l_tpshortsms, MAX_TP_SHORT_MESSAGE_SUB_SPE_INFO_DIGITS, 0, true);
        if (tpshortmsg.length() % 2)
        {
            l_tpshortsms[(tpshortmsg.length() / 2)] |= 0xF0;
        }

        cap_v3::TPShortMessageSubmissionInfo tps(MAPUtils::ByteArrayToVector(l_tpshortsms, len));
        idp->SetTPShortMessageSubmissionSpecificInfo(tps);
    }

    isNull = (*cfg)["tPProtocolIdentifier"]["Value"].isNull();
    isAVPEnabled = (*cfg)["tPProtocolIdentifier"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string tppro = (*cfg)["tPProtocolIdentifier"]["Value"].asString();
        if(tppro.length() >= MAX_TP_PROTOCOL_IDENTIFIER_DIGITS)
        {
            tppro.erase(MAX_TP_PROTOCOL_IDENTIFIER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tppro, l_tpprotoiden, MAX_TP_PROTOCOL_IDENTIFIER_DIGITS, 0, true);
        cap_v3::TPProtocolIdentifier tpi(MAPUtils::ByteArrayToVector(l_tpprotoiden, len));
        idp->SetTPProtocolIdentifier(tpi);
    }

    isNull = (*cfg)["tPDataCodingScheme"]["Value"].isNull();
    isAVPEnabled = (*cfg)["tPDataCodingScheme"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string tpdatacodingsch = (*cfg)["tPDataCodingScheme"]["Value"].asString();
        if(tpdatacodingsch.length() >= MAX_TP_DATA_CODING_SCHEME_DIGITS)
        {
            tpdatacodingsch.erase(MAX_TP_DATA_CODING_SCHEME_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tpdatacodingsch, l_tpdatacodsch, MAX_TP_DATA_CODING_SCHEME_DIGITS, 0, true);
        cap_v3::TPDataCodingScheme tdcs(MAPUtils::ByteArrayToVector(l_tpdatacodsch, len));
        idp->SetTPDataCodingScheme(tdcs);
    }

    isNull = (*cfg)["tPValidityPeriod"]["Value"].isNull();
    isAVPEnabled = (*cfg)["tPValidityPeriod"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string tpvalidityperiod = (*cfg)["tPValidityPeriod"]["Value"].asString();
        int len = 0;
        if(tpvalidityperiod.length() == MAX_TP_VALIDITY_PERIOD_DIGITS_2)
        {
            len = MAPUtils::StringToTBCD(tpvalidityperiod, l_tpvalidityperiod, MAX_TP_VALIDITY_PERIOD_DIGITS_2, 0, true);
        }
        else if(tpvalidityperiod.length() == MAX_TP_VALIDITY_PERIOD_DIGITS_14)
        {
            len = MAPUtils::StringToTBCD(tpvalidityperiod, l_tpvalidityperiod, MAX_TP_VALIDITY_PERIOD_DIGITS_14, 0, true);
        }

        cap_v3::TPValidityPeriod tvp(MAPUtils::ByteArrayToVector(l_tpvalidityperiod, len));
 
        idp->SetTPValidityPeriod(tvp);
    }
    
    isNull = (*cfg)["smsReferenceNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["smsReferenceNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string callreferencenumber = (*cfg)["smsReferenceNumber"]["Value"].asString();
        if(callreferencenumber.length() > MAX_SMS_REFERENCE_NUMBER_DIGITS)
        {
            callreferencenumber.erase(MAX_SMS_REFERENCE_NUMBER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_SMS_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }

        cap_v3::CallReferenceNumber crn(MAPUtils::ByteArrayToVector(l_callreferencenumber, len));
        idp->SetSmsReferenceNumber(crn);
    }

    isNull = (*cfg)["mscAddress"]["Value"].isNull();
    isAVPEnabled = (*cfg)["mscAddress"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string mscaddress = (*cfg)["mscAddress"]["Value"].asString();
        if(mscaddress.length() > MAX_MSC_ADDRESS_DIGITS)
        {
            mscaddress.erase(MAX_MSC_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(mscaddress.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(mscaddress.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscaddress.length() % 2)
        {
            l_mscaddress[(mscaddress.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscaddress, len));
        idp->SetMscAddress(isdn);
    }

    isNull = (*cfg)["sgsn_Number"]["Value"].isNull();
    isAVPEnabled = (*cfg)["sgsn_Number"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string sgsnnumber = (*cfg)["sgsn_Number"]["Value"].asString();
        if(sgsnnumber.length() > MAX_SGSN_NUMBER_DIGITS)
        {
            sgsnnumber.erase(MAX_SGSN_NUMBER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(sgsnnumber.substr(0, MAX_SGSN_NUMBER_HEADER_LENGTH),
                l_sgsnnumber, MAX_SGSN_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(sgsnnumber.substr(MAX_SGSN_NUMBER_HEADER_LENGTH), (l_sgsnnumber+1), MAX_SGSN_NUMBER_DIGITS);
        if (sgsnnumber.length() % 2)
        {
            l_sgsnnumber[(sgsnnumber.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_sgsnnumber, len));
        idp->SetSgsn_Number(isdn);
    }
    
    isAVPEnabled = (*cfg)["IMEI"]["Enabled"].asBool();
    isNull = (*cfg)["IMEI"]["Value"].isNull();
    if((!isNull) && isAVPEnabled)
    {
        std::string Imei = (*cfg)["IMEI"]["Value"].asString();
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
        cap_v3::IMEI imei(MAPUtils::ByteArrayToVector(l_imsi, len));
        idp->SetImei(imei);
    }
    return idp;
}

AsnObject* BuildInitialDPArgV1()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    std::string bc = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_timeandtimezone[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_callingpartyNum[10] = {0};
    uint8_t l_bearercap[11] = {0};
    uint8_t l_carrier[4] = {0};
    uint8_t l_cuginterlock[4] = {0};
    uint8_t l_mscaddress[9] = {0};
    uint8_t l_gmscaddress[9] = {0};
    uint8_t l_callreferencenumber[8] = {0};
    uint8_t l_cause[2] = {0};
    uint8_t l_ipsspcap[4] = {0};
    uint8_t l_vlrnumber[9] = {0};
    uint8_t l_mscnumber[9] = {0};
    uint8_t l_locationnumber[10] = {0};
    uint8_t l_calldpartybcdnum[10] = {0};

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["InitialDPArg"];

    cap_v1::InitialDPArg *idp = new cap_v1::InitialDPArg();

    isNull = (*cfg)["serviceKey"]["Value"].isNull();
    if(!isNull)
    {
        cap_v1::ServiceKey sk((*cfg)["serviceKey"]["Value"].asInt());
        idp->SetServiceKey(sk); 
    }

    isNull = (*cfg)["calledPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["calledPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["calledPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }
        cap_v1::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCalledPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["callingPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLING_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLING_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }

        cap_v1::CallingPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCallingPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartysCategory"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartysCategory"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string category = (*cfg)["callingPartysCategory"]["Value"].asString();
        if(category.length() > MAX_CALLING_PARTYS_CATEGORY_DIGITS)
        {
            category.erase(2, std::string::npos);
        }
        uint8_t tbcd[2] = {0};
        int len = MAPUtils::StringToTBCD(category.substr(0, MAX_CALLING_PARTYS_CATEGORY_DIGITS), tbcd, MAX_CALLING_PARTYS_CATEGORY_DIGITS, 0, true);
        cap_v1::CallingPartysCategory cpc(MAPUtils::ByteArrayToVector(tbcd, 1));
        idp->SetCallingPartysCategory(cpc);
    }
#if 0
    isNull = (*cfg)["cGEncountered"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cGEncountered"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::CGEncountered cge((*cfg)["cGEncountered"]["Value"].asInt());
        idp->SetCGEncountered(cge);
    }
    isNull = (*cfg)["iPSSPCapabilities"]["Value"].isNull();
    isAVPEnabled = (*cfg)["iPSSPCapabilities"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string ipspcap = (*cfg)["iPSSPCapabilities"]["Value"].asString();
        if(ipspcap.length() > MAX_IPSSP_CAPABILITY_DIGITS)
        {
            ipspcap.erase(MAX_IPSSP_CAPABILITY_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(ipspcap, l_ipsspcap, MAX_IPSSP_CAPABILITY_DIGITS, 0, true);

        cap_v1::IPSSPCapabilities ips(MAPUtils::ByteArrayToVector(l_ipsspcap, len));
        idp->SetIPSSPCapabilities(ips);
    }
#endif

    isNull = (*cfg)["locationNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["locationNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string locnum = (*cfg)["locationNumber"]["Value"].asString();
        uint8_t l_locnum[10] = {0};
        if(locnum.length() > MAX_LOCATION_NUMBER_DIGITS)
        {
            locnum.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(locnum.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), l_locnum, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(locnum.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), (l_locnum+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
        if (locnum.length() % 2)
        {
            l_locnum[(locnum.length() / 2)] |= 0x00;
        }

        cap_v1::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locnum, len));
        idp->SetLocationNumber(ln);
    }

    isNull = (*cfg)["originalCalledPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["originalCalledPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_origcalledPartyId[10] = {0};
        string origcalledPartyId = (*cfg)["originalCalledPartyID"]["Value"].asString();
        if(origcalledPartyId.length() > MAX_ORG_CALLED_PARTY_ID_DIGITS)
        {
            origcalledPartyId.erase(MAX_ORG_CALLED_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(origcalledPartyId.substr(0, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                l_origcalledPartyId, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(origcalledPartyId.substr(MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                (l_origcalledPartyId+2), MAX_ORG_CALLED_PARTY_ID_DIGITS, 0, false);

        if (origcalledPartyId.length() % 2)
        {
            l_origcalledPartyId[(origcalledPartyId.length() / 2)] |= 0x00;
        }
        cap_v1::OriginalCalledPartyID ocp(MAPUtils::ByteArrayToVector(l_origcalledPartyId, len));
        idp->SetOriginalCalledPartyID(ocp);
    }
#if 0
    isNull = (*cfg)["extensions"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["extensions"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        //TODO: check with the format
        cap_v1::ExtensionField exts;

        isNull = (*cfg)["extensions"]["type"]["Value"].isNull();
        if(!isNull)
        {
            cap_v1::ExtensionField::Type type((*cfg)["extensions"]["type"]["Value"].asInt());
            exts.SetType(type);
        }

        isNull = (*cfg)["extensions"]["criticality"]["Value"].isNull();
        if(!isNull)
        {
            cap_v1::ExtensionField::CriticalityType ctype((*cfg)["extensions"]["criticality"]["Value"].asInt());
            exts.SetCriticality(ctype);
        }

        isNull = (*cfg)["extensions"]["value"]["Value"].isNull();
        if(!isNull)
        {
            //TODO: check with the format
            //cap_v1::ExtensionField::Value val((*cfg)["extensions"]["value"]["Value"]);
            //exts.SetValue(val);
        }

        //TODO: check with the format
        //idp->SetExtensions(exts);
    }
#endif
    isNull = (*cfg)["highLayerCompatibility"]["Value"].isNull();
    isAVPEnabled = (*cfg)["highLayerCompatibility"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::HighLayerCompatibility hlc(MAPUtils::StringToVector((*cfg)["highLayerCompatibility"]["Value"].asString()));
        idp->SetHighLayerCompatibility(hlc);
    }

    isNull = (*cfg)["additionalCallingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["additionalCallingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_addcallingpartynumber[10] = {0};
        std::string addcallingpartynumber = (*cfg)["additionalCallingPartyNumber"]["Value"].asString();;

        int len = MAPUtils::StringToTBCD(addcallingpartynumber.substr(0, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), 
                l_addcallingpartynumber, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(addcallingpartynumber.substr(MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_addcallingpartynumber+3), MAX_ADDITIONAL_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (addcallingpartynumber.length() % 2)
        {
            l_addcallingpartynumber[(addcallingpartynumber.length() / 2)] |= 0xF0;
        }
        cap_v1::AdditionalCallingPartyNumber acpn(MAPUtils::ByteArrayToVector(l_addcallingpartynumber, len));
        idp->SetAdditionalCallingPartyNumber(acpn);
    }

    isNull = (*cfg)["bearerCapability"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["bearerCapability"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::BearerCapability beca;
        isNull = (*cfg)["bearerCapability"]["bearerCap"]["Value"].isNull();
        isAVPEnabled = (*cfg)["bearerCapability"]["bearerCap"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            bc = (*cfg)["bearerCapability"]["bearerCap"]["Value"].asString();
            int len = MAPUtils::StringToTBCD(bc, l_bearercap, MAP_MAX_E164_SZ, 0, true);
            if (bc.length() % 2)
            {
                l_bearercap[(bc.length() / 2)] |= 0xF0;
            }
            cap_v1::BearerCapability::BearerCap bcap(MAPUtils::ByteArrayToVector(l_bearercap, len));

            beca.SetChoiceBearerCap(bcap);
        }
        idp->SetBearerCapability(beca);
    }
    
    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    isAVPEnabled = (*cfg)["eventTypeBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        idp->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["redirectingPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectingPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectpartyid[10] = {0};
        string redirectingpartyid = (*cfg)["redirectingPartyID"]["Value"].asString();
        if(redirectingpartyid.length() > MAX_REDIRECTING_PARTY_ID_DIGITS)
        {
            redirectingpartyid.erase(MAX_REDIRECTING_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(redirectingpartyid.substr(0, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), l_redirectpartyid, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(redirectingpartyid.substr(MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), (l_redirectpartyid+2), MAX_REDIRECTING_PARTY_ID_DIGITS, 0, false);
 
        if (redirectingpartyid.length() % 2)
        {
            l_redirectpartyid[(redirectingpartyid.length() / 2)] |= 0x00;
        }
        cap_v1::RedirectingPartyID rpi(MAPUtils::ByteArrayToVector(l_redirectpartyid, len));
 
        idp->SetRedirectingPartyID(rpi);
    }

    isNull = (*cfg)["redirectionInformation"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectionInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectinginfo[2] = {0};
        string redirectioninfo = (*cfg)["redirectionInformation"]["Value"].asString();
        if(redirectioninfo.length() > MAX_REDIRECTION_INFORMATION_DIGITS)
        {
            redirectioninfo.erase(MAX_REDIRECTION_INFORMATION_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(redirectioninfo, l_redirectinginfo, MAX_REDIRECTION_INFORMATION_DIGITS, 0, true);
        cap_v1::RedirectionInformation ri(MAPUtils::ByteArrayToVector(l_redirectinginfo, len));
 
        idp->SetRedirectionInformation(ri);
    }
#if 0
    isNull = (*cfg)["cause"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cause"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cse = (*cfg)["cause"]["Value"].asString();
        if(cse.length() > MAX_CAUSE_DIGITS)
        {
            cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
        if (cse.length() % 2)
        {
            l_cause[(cse.length() / 2)] |= 0xF0;
        }
        cap_v1::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
        idp->SetCause(cause);
    }

    isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::ServiceInteractionIndicatorsTwo servIndic;

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::ForwardServiceInteractionInd fsin;

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::ForwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                fsin.SetConferenceTreatmentIndicator(cti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::ForwardServiceInteractionInd::CallDiversionTreatmentIndicator cdt(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallDiversionTreatmentIndicator(cdt);
            }
            
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::ForwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardS    erviceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallCompletionTreatmentIndicator(ccti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::ForwardServiceInteractionInd::CallingPartyRestrictionIndicator cpri(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwar    dS    erviceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].asString()));
                fsin.SetCallingPartyRestrictionIndicator(cpri);
            }

            servIndic.SetForwardServiceInteractionInd(fsin);
        }
        
        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::BackwardServiceInteractionInd bsii;
           
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::BackwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                bsii.SetConferenceTreatmentIndicator(cti);
            }
 
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::BackwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                bsii.SetCallCompletionTreatmentIndicator(ccti);
            }
            servIndic.SetBackwardServiceInteractionsInd(bsii);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::BothwayThroughConnectionInd btci((*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].asInt());
            servIndic.SetBothwayThroughConnectionInd(btci);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::ConnectedNumberTreatmentInd cnti((*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].asInt());
            servIndic.SetConnectedNumberTreatmentInd(cnti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator hti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].asString()));
            servIndic.SetHoldTreatmentIndicator(hti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::ServiceInteractionIndicatorsTwo::CwTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].asString()));
            servIndic.SetCwTreatmentIndicator(cti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::ServiceInteractionIndicatorsTwo::EctTreatmentIndicator eti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].asString()));
            servIndic.SetEctTreatmentIndicator(eti);
        }
        idp->SetServiceInteractionIndicatorsTwo(servIndic);
    }
    
#endif
    isNull = (*cfg)["imsi"]["Value"].isNull();
    isAVPEnabled = (*cfg)["imsi"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        Imsi = (*cfg)["imsi"]["Value"].asString();
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
        cap_v1::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        idp->SetIMSI(imsi);
    }
    
    isNull = (*cfg)["subscriberState"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["subscriberState"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::SubscriberState ss;

        isNull = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::SubscriberState::AssumedIdle ai;
            ss.SetChoiceAssumedIdle(ai);
        }
        else
        {
            isNull = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v1::SubscriberState::CamelBusy cb;
                ss.SetChoiceCamelBusy(cb);
            }
            else
            {
                isNull = (*cfg)["subscriberState"]["netDetNotReachable"]["Value"].isNull();
                isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v1::SubscriberState::NotReachableReason nrr((*cfg)["subscriberState"]["netDetNotReachable"]["Value"].asInt());
                    ss.SetChoiceNetDetNotReachable(nrr);
                }
                else
                {
                    isNull = (*cfg)["subscriberState"]["notProvidedFromVLR"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v1::SubscriberState::NotProvidedFromVLR npfv;
                        ss.SetChoiceNotProvidedFromVLR(npfv);
                    }
                }
            }
        }
        idp->SetSubscriberState(ss);
    }

    isNull = (*cfg)["locationInformation"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["locationInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::LocationInformation li;
        
        isNull = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::LocationInformation::AgeOfLocationInformation aoli((*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].asInt());
            li.SetAgeOfLocationInformation(aoli);
        }

        isNull = (*cfg)["locationInformation"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::LocationInformation::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geographicalInformation"]["Value"].asString()));
            li.SetGeographicalInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["vlr_number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["vlr_number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string vlrnum = (*cfg)["locationInformation"]["vlr_number"]["Value"].asString();
            if(vlrnum.length() > MAX_VLR_NUMBER_DIGITS)
            {
                vlrnum.erase(MAX_VLR_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH), 
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
 
            cap_v1::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_vlrnumber, len));
            li.SetVlr_number(isdn);
        }
        
        isNull = (*cfg)["locationInformation"]["locationNumber"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["locationNumber"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string locinfo = (*cfg)["locationInformation"]["locationNumber"]["Value"].asString();
            if(locinfo.length() > MAX_LOCATION_NUMBER_DIGITS)
            {
                locinfo.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0x00;
            }

            cap_v1::LocationInformation::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locationnumber, len));
            li.SetLocationNumber(ln);
        }
#if 0
        isNull = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI cgi;

            isAVPEnabled = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["Enabled"].asBool();
            if(isAVPEnabled)
            {
                uint8_t tbcd[7] = {0};
                string mcc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mcc"].asString();
                string mnc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mnc"].asString();
                string locArea = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["LocationArea"].asString();
                string cellId = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["CellId_Or_SAC"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId/SAC Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                }
                cap_v1::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgil(MAPUtils::ByteArrayToVector(tbcd, 7));
                cgi.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cgil);
            }
            else
            {
                isAVPEnabled = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["Enabled"].asBool();
                if(isAVPEnabled)
                {
                    uint8_t tbcd[7] = {0};
                    string mcc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mcc"].asString();
                    string mnc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mnc"].asString();
                    string locArea = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["LocationArea"].asString();
                    if(mcc.length() != 0  && mnc.length() != 0 )
                    {
                        tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                        if(mnc.length() == 3)
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                        }
                        else
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                        }
                        tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                        tbcd[3] = atoi(locArea.c_str()) >> 8;
                        tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    }

                    cap_v1::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength lai(MAPUtils::ByteArrayToVector(tbcd, 5));
 
                    cgi.SetChoiceLaiFixedLength(lai);
                }
            }
            li.SetCellGlobalIdOrServiceAreaIdOrLAI(cgi);
        }
        isNull = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["selectedLSA_Id"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_lsaid[3] = {0};
            string lsaId = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].asString();
             if(lsaId.length() > MAX_LSA_ID_DIGITS)
            {
                lsaId.erase(MAX_LSA_ID_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
            cap_v1::LocationInformation::LSAIdentity lsa(MAPUtils::ByteArrayToVector(l_lsaid, len));
 
            li.SetSelectedLSA_Id(lsa);
        }

        isNull = (*cfg)["locationInformation"]["msc_Number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["msc_Number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string mscnum = (*cfg)["locationInformation"]["msc_Number"]["Value"].asString();
            if(mscnum.length() > MAX_MSC_NUMBER_DIGITS)
            {
                mscnum.erase(MAX_MSC_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
 
            cap_v1::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformation"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::LocationInformation::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geodeticInformation"]["Value"].asString()));
            li.SetGeodeticInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v1::LocationInformation::CurrentLocationRetrieved clr;
            li.SetCurrentLocationRetrieved(clr);
        }
#endif
        idp->SetLocationInformation(li);
    }
    
    isNull = (*cfg)["ext_basicServiceCode"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::Ext_BasicServiceCode txtb;

        isNull = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Enabled"].asBool();
        uint8_t l_bs[5] = {0};
        if(!isNull && isAVPEnabled)
        {
            string bs = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].asString();
            if(bs.length() > MAX_BASIC_SERVICE_CODE_DIGITS)
            {
                bs.erase(MAX_BASIC_SERVICE_CODE_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_BASIC_SERVICE_CODE_DIGITS, 0, true);
            cap_v1::Ext_BasicServiceCode::Ext_BearerServiceCode ebs(MAPUtils::ByteArrayToVector(l_bs, len)); 
            txtb.SetChoiceExt_BearerService(ebs);
        }
        else
        {
            isNull = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                string bs = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].asString();
                if(bs.length() > MAX_TELE_SERVICE_CODE_DIGITS)
                {
                    bs.erase(MAX_TELE_SERVICE_CODE_DIGITS, std::string::npos);
                }
                int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_TELE_SERVICE_CODE_DIGITS, 0, true);
                cap_v1::Ext_BasicServiceCode::Ext_TeleserviceCode etc(MAPUtils::ByteArrayToVector(l_bs, len));
                txtb.SetChoiceExt_Teleservice(etc);
            }
        }
        idp->SetExt_basicServiceCode(txtb);
    }

    isNull = (*cfg)["callReferenceNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["callReferenceNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string callreferencenumber = (*cfg)["callReferenceNumber"]["Value"].asString();
        if(callreferencenumber.length() > MAX_CALL_REFERENCE_NUMBER_DIGITS)
        {
            callreferencenumber.erase(MAX_CALL_REFERENCE_NUMBER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_CALL_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }
        cap_v1::CallReferenceNumber crn(MAPUtils::ByteArrayToVector(l_callreferencenumber, len));
        idp->SetCallReferenceNumber(crn);
    }

    isNull = (*cfg)["mscAddress"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["mscAddress"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string mscadd = (*cfg)["mscAddress"]["Value"].asString();
        if(mscadd.length() > MAX_MSC_ADDRESS_DIGITS)
        {
            mscadd.erase(MAX_MSC_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(mscadd.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(mscadd.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscadd.length() % 2)
        {
            l_mscaddress[(mscadd.length() / 2)] |= 0xF0;
        }
        cap_v1::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscaddress, len));
        idp->SetMscAddress(isdn);
    }

    isNull = (*cfg)["calledPartyBCDNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["calledPartyBCDNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        std::string cldPrtyBCDNmbr = (*cfg)["calledPartyBCDNumber"]["Value"].asString();

        int len = MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(0, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                l_calldpartybcdnum, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                (l_calldpartybcdnum+1), MAX_CALLED_PARTY_BCD_NUMBER_DIGITS, 0, false);
        if (cldPrtyBCDNmbr.length() % 2)
        {
            l_calldpartybcdnum[(cldPrtyBCDNmbr.length() / 2)] |= 0xF0;
        }
        cap_v1::CalledPartyBCDNumber cp(MAPUtils::ByteArrayToVector(l_calldpartybcdnum, len));
        idp->SetCalledPartyBCDNumber(cp);
    }
#if 0 
    isNull = (*cfg)["timeAndTimezone"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["timeAndTimezone"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        tatz = (*cfg)["timeAndTimezone"]["Value"].asString();
        if(tatz.length() >= MAX_TIME_AND_TIME_ZONE_DIGITS)
        {
            tatz.erase(MAX_TIME_AND_TIME_ZONE_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tatz, l_timeandtimezone, MAP_MAX_E164_SZ);
        cap_v1::TimeAndTimezone tat(MAPUtils::ByteArrayToVector(l_timeandtimezone, len));

        idp->SetTimeAndTimezone(tat);
    }
    isNull = (*cfg)["gsm_ForwardingPending"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["gsm_ForwardingPending"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::InitialDPArg::Gsm_ForwardingPending gsm;
        idp->SetGsm_ForwardingPending(gsm);
    }

    isNull = (*cfg)["carrier"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["carrier"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string car = (*cfg)["carrier"]["Value"].asString();
        if(car.length() >= MAX_CARRIER_DIGITS)
        {
            car.erase(MAX_CARRIER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(car.substr(0, MAX_CARRIER_DIGITS_LENGTH), l_carrier, MAX_CARRIER_DIGITS_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(car.substr(MAX_CARRIER_DIGITS_LENGTH), (l_carrier+2), MAX_CARRIER_DIGITS_LENGTH, 0, false);
        cap_v1::Carrier carrier(MAPUtils::ByteArrayToVector(l_carrier, len));
        idp->SetCarrier(carrier);
    }

    isNull = (*cfg)["cug_Index"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Index"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::CUG_Index ci((*cfg)["cug_Index"]["Value"].asInt());
        idp->SetCug_Index(ci);
    }

    isNull = (*cfg)["cug_Interlock"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Interlock"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cug_interlock = (*cfg)["cug_Interlock"]["Value"].asString();
        if(cug_interlock.length() >= MAX_CUG_INTERLOCK_DIGITS)
        {
            cug_interlock.erase(MAX_CUG_INTERLOCK_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(cug_interlock, l_cuginterlock, MAX_CUG_INTERLOCK_DIGITS, 0, true);
 
        cap_v1::CUG_Interlock ci(MAPUtils::ByteArrayToVector(l_cuginterlock, len));
        idp->SetCug_Interlock(ci);
    }
    
    isNull = (*cfg)["cug_OutgoingAccess"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["cug_OutgoingAccess"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::InitialDPArg::Cug_OutgoingAccess coa;
        idp->SetCug_OutgoingAccess(coa);
    }

    isNull = (*cfg)["initialDPArgExtension"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["initialDPArgExtension"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v1::InitialDPArgExtension idpext;


        isNull = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string gmscadd = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].asString();
            if(gmscadd.length() > MAX_GMSC_ADDRESS_DIGITS)
            {
                gmscadd.erase(MAX_GMSC_ADDRESS_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(gmscadd.substr(0, MAX_GMSC_ADDRESS_HEADER_LENGTH), 
                    l_gmscaddress, MAX_GMSC_ADDRESS_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(gmscadd.substr(MAX_GMSC_ADDRESS_HEADER_LENGTH), (l_gmscaddress+1), MAX_GMSC_ADDRESS_DIGITS);
            if (gmscadd.length() % 2)
            {
                l_gmscaddress[(gmscadd.length() / 2)] |= 0xF0;
            }
            cap_v1::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_gmscaddress, len));
            idpext.SetGmscAddress(isdn);
        }
        

        idp->SetInitialDPArgExtension(idpext);
    }
#endif
    return idp;
}

AsnObject* BuildInitialDPArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    std::string bc = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_timeandtimezone[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_callingpartyNum[10] = {0};
    uint8_t l_bearercap[11] = {0};
    uint8_t l_carrier[4] = {0};
    uint8_t l_cuginterlock[4] = {0};
    uint8_t l_mscaddress[9] = {0};
    uint8_t l_gmscaddress[9] = {0};
    uint8_t l_callreferencenumber[8] = {0};
    uint8_t l_cause[2] = {0};
    uint8_t l_ipsspcap[4] = {0};
    uint8_t l_vlrnumber[9] = {0};
    uint8_t l_mscnumber[9] = {0};
    uint8_t l_locationnumber[10] = {0};
    uint8_t l_calldpartybcdnum[10] = {0};

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["InitialDPArg"];

    cap_v3::InitialDPArg *idp = new cap_v3::InitialDPArg();

    isNull = (*cfg)["serviceKey"]["Value"].isNull();
    if(!isNull)
    {
        cap_v3::ServiceKey sk((*cfg)["serviceKey"]["Value"].asInt());
        idp->SetServiceKey(sk); 
    }

    isNull = (*cfg)["calledPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["calledPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["calledPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }
        cap_v3::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCalledPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["callingPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLING_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLING_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }

        cap_v3::CallingPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCallingPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartysCategory"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartysCategory"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string category = (*cfg)["callingPartysCategory"]["Value"].asString();
        if(category.length() > MAX_CALLING_PARTYS_CATEGORY_DIGITS)
        {
            category.erase(MAX_CALLING_PARTYS_CATEGORY_DIGITS, std::string::npos);
        }
        uint8_t tbcd[2] = {0};
        int len = MAPUtils::StringToTBCD(category.substr(0, MAX_CALLING_PARTYS_CATEGORY_DIGITS), tbcd, MAX_CALLING_PARTYS_CATEGORY_DIGITS, 0, true);
        cap_v3::CallingPartysCategory cpc(MAPUtils::ByteArrayToVector(tbcd, 1));
        idp->SetCallingPartysCategory(cpc);
    }

    isNull = (*cfg)["cGEncountered"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cGEncountered"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CGEncountered cge((*cfg)["cGEncountered"]["Value"].asInt());
        idp->SetCGEncountered(cge);
    }

    isNull = (*cfg)["iPSSPCapabilities"]["Value"].isNull();
    isAVPEnabled = (*cfg)["iPSSPCapabilities"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string ipspcap = (*cfg)["iPSSPCapabilities"]["Value"].asString();
        if(ipspcap.length() > MAX_IPSSP_CAPABILITY_DIGITS)
        {
            ipspcap.erase(MAX_IPSSP_CAPABILITY_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(ipspcap, l_ipsspcap, MAX_IPSSP_CAPABILITY_DIGITS, 0, true);

        cap_v3::IPSSPCapabilities ips(MAPUtils::ByteArrayToVector(l_ipsspcap, len));
        idp->SetIPSSPCapabilities(ips);
    }

    isNull = (*cfg)["locationNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["locationNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string locnum = (*cfg)["locationNumber"]["Value"].asString();
        uint8_t l_locnum[10] = {0};
        if(locnum.length() > MAX_LOCATION_NUMBER_DIGITS)
        {
            locnum.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(locnum.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), l_locnum, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(locnum.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), (l_locnum+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
        if (locnum.length() % 2)
        {
            l_locnum[(locnum.length() / 2)] |= 0xF0;
        }

        cap_v3::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locnum, len));
        idp->SetLocationNumber(ln);
    }

    isNull = (*cfg)["originalCalledPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["originalCalledPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_origcalledPartyId[10] = {0};
        string origcalledPartyId = (*cfg)["originalCalledPartyID"]["Value"].asString();
        if(origcalledPartyId.length() > MAX_ORG_CALLED_PARTY_ID_DIGITS)
        {
            origcalledPartyId.erase(MAX_ORG_CALLED_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(origcalledPartyId.substr(0, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                l_origcalledPartyId, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(origcalledPartyId.substr(MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                (l_origcalledPartyId+2), MAX_ORG_CALLED_PARTY_ID_DIGITS, 0, false);

        if (origcalledPartyId.length() % 2)
        {
            l_origcalledPartyId[(origcalledPartyId.length() / 2)] |= 0x00;
        }
        cap_v3::OriginalCalledPartyID ocp(MAPUtils::ByteArrayToVector(l_origcalledPartyId, len));
        idp->SetOriginalCalledPartyID(ocp);
    }
#if 0
    isNull = (*cfg)["extensions"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["extensions"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        //TODO: check with the format
        cap_v3::ExtensionField exts;

        isNull = (*cfg)["extensions"]["type"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::ExtensionField::Type type((*cfg)["extensions"]["type"]["Value"].asInt());
            exts.SetType(type);
        }

        isNull = (*cfg)["extensions"]["criticality"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::ExtensionField::CriticalityType ctype((*cfg)["extensions"]["criticality"]["Value"].asInt());
            exts.SetCriticality(ctype);
        }

        isNull = (*cfg)["extensions"]["value"]["Value"].isNull();
        if(!isNull)
        {
            //TODO: check with the format
            //cap_v3::ExtensionField::Value val((*cfg)["extensions"]["value"]["Value"]);
            //exts.SetValue(val);
        }

        //TODO: check with the format
        //idp->SetExtensions(exts);
    }
#endif
    isNull = (*cfg)["highLayerCompatibility"]["Value"].isNull();
    isAVPEnabled = (*cfg)["highLayerCompatibility"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::HighLayerCompatibility hlc(MAPUtils::StringToVector((*cfg)["highLayerCompatibility"]["Value"].asString()));
        idp->SetHighLayerCompatibility(hlc);
    }

    isNull = (*cfg)["additionalCallingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["additionalCallingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_addcallingpartynumber[10] = {0};
        std::string addcallingpartynumber = (*cfg)["additionalCallingPartyNumber"]["Value"].asString();;

        int len = MAPUtils::StringToTBCD(addcallingpartynumber.substr(0, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), 
                l_addcallingpartynumber, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(addcallingpartynumber.substr(MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_addcallingpartynumber+3), MAX_ADDITIONAL_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (addcallingpartynumber.length() % 2)
        {
            l_addcallingpartynumber[(addcallingpartynumber.length() / 2)] |= 0xF0;
        }
        cap_v3::AdditionalCallingPartyNumber acpn(MAPUtils::ByteArrayToVector(l_addcallingpartynumber, len));
        idp->SetAdditionalCallingPartyNumber(acpn);
    }

    isNull = (*cfg)["bearerCapability"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["bearerCapability"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::BearerCapability beca;
        isNull = (*cfg)["bearerCapability"]["bearerCap"]["Value"].isNull();
        isAVPEnabled = (*cfg)["bearerCapability"]["bearerCap"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            bc = (*cfg)["bearerCapability"]["bearerCap"]["Value"].asString();
            int len = MAPUtils::StringToTBCD(bc, l_bearercap, MAP_MAX_E164_SZ, 0, true);
            if (bc.length() % 2)
            {
                l_bearercap[(bc.length() / 2)] |= 0xF0;
            }
            cap_v3::BearerCapability::BearerCap bcap(MAPUtils::ByteArrayToVector(l_bearercap, len));

            beca.SetChoiceBearerCap(bcap);
        }
        idp->SetBearerCapability(beca);
    }
    
    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    isAVPEnabled = (*cfg)["eventTypeBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        idp->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["redirectingPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectingPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectpartyid[10] = {0};
        string redirectingpartyid = (*cfg)["redirectingPartyID"]["Value"].asString();
        if(redirectingpartyid.length() > MAX_REDIRECTING_PARTY_ID_DIGITS)
        {
            redirectingpartyid.erase(MAX_REDIRECTING_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(redirectingpartyid.substr(0, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), l_redirectpartyid, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(redirectingpartyid.substr(MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), (l_redirectpartyid+2), MAX_REDIRECTING_PARTY_ID_DIGITS, 0, false);
 
        if (redirectingpartyid.length() % 2)
        {
            l_redirectpartyid[(redirectingpartyid.length() / 2)] |= 0x00;
        }
        cap_v3::RedirectingPartyID rpi(MAPUtils::ByteArrayToVector(l_redirectpartyid, len));
 
        idp->SetRedirectingPartyID(rpi);
    }

    isNull = (*cfg)["redirectionInformation"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectionInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectinginfo[2] = {0};
        string redirectioninfo = (*cfg)["redirectionInformation"]["Value"].asString();
        if(redirectioninfo.length() > MAX_REDIRECTION_INFORMATION_DIGITS)
        {
            redirectioninfo.erase(MAX_REDIRECTION_INFORMATION_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(redirectioninfo, l_redirectinginfo, MAX_REDIRECTION_INFORMATION_DIGITS, 0, true);
        cap_v3::RedirectionInformation ri(MAPUtils::ByteArrayToVector(l_redirectinginfo, len));
 
        idp->SetRedirectionInformation(ri);
    }

    isNull = (*cfg)["cause"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cause"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cse = (*cfg)["cause"]["Value"].asString();
        if(cse.length() > MAX_CAUSE_DIGITS)
        {
            cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
        if (cse.length() % 2)
        {
            l_cause[(cse.length() / 2)] |= 0xF0;
        }
        cap_v3::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
        idp->SetCause(cause);
    }

    isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::ServiceInteractionIndicatorsTwo servIndic;

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ForwardServiceInteractionInd fsin;

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                fsin.SetConferenceTreatmentIndicator(cti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallDiversionTreatmentIndicator cdt(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallDiversionTreatmentIndicator(cdt);
            }
            
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardS    erviceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallCompletionTreatmentIndicator(ccti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallingPartyRestrictionIndicator cpri(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwar    dS    erviceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].asString()));
                fsin.SetCallingPartyRestrictionIndicator(cpri);
            }

            servIndic.SetForwardServiceInteractionInd(fsin);
        }
        
        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::BackwardServiceInteractionInd bsii;
           
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::BackwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                bsii.SetConferenceTreatmentIndicator(cti);
            }
 
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::BackwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                bsii.SetCallCompletionTreatmentIndicator(ccti);
            }
            servIndic.SetBackwardServiceInteractionsInd(bsii);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::BothwayThroughConnectionInd btci((*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].asInt());
            servIndic.SetBothwayThroughConnectionInd(btci);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ConnectedNumberTreatmentInd cnti((*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].asInt());
            servIndic.SetConnectedNumberTreatmentInd(cnti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator hti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].asString()));
            servIndic.SetHoldTreatmentIndicator(hti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::CwTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].asString()));
            servIndic.SetCwTreatmentIndicator(cti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::EctTreatmentIndicator eti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].asString()));
            servIndic.SetEctTreatmentIndicator(eti);
        }
        idp->SetServiceInteractionIndicatorsTwo(servIndic);
    }
    
    isNull = (*cfg)["imsi"]["Value"].isNull();
    isAVPEnabled = (*cfg)["imsi"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        Imsi = (*cfg)["imsi"]["Value"].asString();
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
        cap_v3::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        idp->SetIMSI(imsi);
    }
    
    isNull = (*cfg)["subscriberState"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["subscriberState"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::SubscriberState ss;

        isNull = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::SubscriberState::AssumedIdle ai;
            ss.SetChoiceAssumedIdle(ai);
        }
        else
        {
            isNull = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::SubscriberState::CamelBusy cb;
                ss.SetChoiceCamelBusy(cb);
            }
            else
            {
                isNull = (*cfg)["subscriberState"]["netDetNotReachable"]["Value"].isNull();
                isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::SubscriberState::NotReachableReason nrr((*cfg)["subscriberState"]["netDetNotReachable"]["Value"].asInt());
                    ss.SetChoiceNetDetNotReachable(nrr);
                }
                else
                {
                    isNull = (*cfg)["subscriberState"]["notProvidedFromVLR"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v3::SubscriberState::NotProvidedFromVLR npfv;
                        ss.SetChoiceNotProvidedFromVLR(npfv);
                    }
                }
            }
        }
        idp->SetSubscriberState(ss);
    }

    isNull = (*cfg)["locationInformation"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["locationInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::LocationInformation li;
        
        isNull = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::AgeOfLocationInformation aoli((*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].asInt());
            li.SetAgeOfLocationInformation(aoli);
        }

        isNull = (*cfg)["locationInformation"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geographicalInformation"]["Value"].asString()));
            li.SetGeographicalInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["vlr_number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["vlr_number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string vlrnum = (*cfg)["locationInformation"]["vlr_number"]["Value"].asString();
            if(vlrnum.length() > MAX_VLR_NUMBER_DIGITS)
            {
                vlrnum.erase(MAX_VLR_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH), 
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_vlrnumber, len));
            li.SetVlr_number(isdn);
        }
        
        isNull = (*cfg)["locationInformation"]["locationNumber"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["locationNumber"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string locinfo = (*cfg)["locationInformation"]["locationNumber"]["Value"].asString();
            if(locinfo.length() > MAX_LOCATION_NUMBER_DIGITS)
            {
                locinfo.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0xF0;
            }

            cap_v3::LocationInformation::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locationnumber, len));
            li.SetLocationNumber(ln);
        }
        

        isNull = (*cfg)["locationInformation"]["cellIdOrLAI"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI cgi;

            isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["Enabled"].asBool();
            if(isAVPEnabled)
            {
                uint8_t tbcd[7] = {0};
                string mcc = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["mcc"].asString();
                string mnc = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["mnc"].asString();
                string locArea = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["LocationArea"].asString();
                string cellId = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["CellId"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId/SAC Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                }
                cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgil(MAPUtils::ByteArrayToVector(tbcd, 7));
                cgi.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cgil);
            }
            else
            {
                isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["Enabled"].asBool();
                if(isAVPEnabled)
                {
                    uint8_t tbcd[7] = {0};
                    string mcc = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["mcc"].asString();
                    string mnc = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["mnc"].asString();
                    string locArea = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["LocationArea"].asString();
                    if(mcc.length() != 0  && mnc.length() != 0 )
                    {
                        tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                        if(mnc.length() == 3)
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                        }
                        else
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                        }
                        tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                        tbcd[3] = atoi(locArea.c_str()) >> 8;
                        tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    }

                    cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength lai(MAPUtils::ByteArrayToVector(tbcd, 5));
 
                    cgi.SetChoiceLaiFixedLength(lai);
                }
            }
            li.SetCellGlobalIdOrServiceAreaIdOrLAI(cgi);
        }

        isNull = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["selectedLSA_Id"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_lsaid[3] = {0};
            string lsaId = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].asString();
             if(lsaId.length() > MAX_LSA_ID_DIGITS)
            {
                lsaId.erase(MAX_LSA_ID_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::LSAIdentity lsa(MAPUtils::ByteArrayToVector(l_lsaid, len));
 
            li.SetSelectedLSA_Id(lsa);
        }

        isNull = (*cfg)["locationInformation"]["msc_Number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["msc_Number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string mscnum = (*cfg)["locationInformation"]["msc_Number"]["Value"].asString();
            if(mscnum.length() > MAX_MSC_NUMBER_DIGITS)
            {
                mscnum.erase(MAX_MSC_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformation"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geodeticInformation"]["Value"].asString()));
            li.SetGeodeticInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::CurrentLocationRetrieved clr;
            li.SetCurrentLocationRetrieved(clr);
        }
        idp->SetLocationInformation(li);
    }
    
    isNull = (*cfg)["ext_basicServiceCode"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::Ext_BasicServiceCode txtb;

        isNull = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Enabled"].asBool();
        uint8_t l_bs[5] = {0};
        if(!isNull && isAVPEnabled)
        {
            string bs = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].asString();
            if(bs.length() > MAX_BASIC_SERVICE_CODE_DIGITS)
            {
                bs.erase(MAX_BASIC_SERVICE_CODE_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_BASIC_SERVICE_CODE_DIGITS, 0, true);
            cap_v3::Ext_BasicServiceCode::Ext_BearerServiceCode ebs(MAPUtils::ByteArrayToVector(l_bs, len)); 
            txtb.SetChoiceExt_BearerService(ebs);
        }
        else
        {
            isNull = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                string bs = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].asString();
                if(bs.length() > MAX_TELE_SERVICE_CODE_DIGITS)
                {
                    bs.erase(MAX_TELE_SERVICE_CODE_DIGITS, std::string::npos);
                }
                int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_TELE_SERVICE_CODE_DIGITS, 0, true);
                cap_v3::Ext_BasicServiceCode::Ext_TeleserviceCode etc(MAPUtils::ByteArrayToVector(l_bs, len));
                txtb.SetChoiceExt_Teleservice(etc);
            }
        }
        idp->SetExt_basicServiceCode(txtb);
    }

    isNull = (*cfg)["callReferenceNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["callReferenceNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string callreferencenumber = (*cfg)["callReferenceNumber"]["Value"].asString();
        if(callreferencenumber.length() > MAX_CALL_REFERENCE_NUMBER_DIGITS)
        {
            callreferencenumber.erase(MAX_CALL_REFERENCE_NUMBER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_CALL_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }
        cap_v3::CallReferenceNumber crn(MAPUtils::ByteArrayToVector(l_callreferencenumber, len));
        idp->SetCallReferenceNumber(crn);
    }

    isNull = (*cfg)["mscAddress"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["mscAddress"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string mscadd = (*cfg)["mscAddress"]["Value"].asString();
        if(mscadd.length() > MAX_MSC_ADDRESS_DIGITS)
        {
            mscadd.erase(MAX_MSC_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(mscadd.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(mscadd.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscadd.length() % 2)
        {
            l_mscaddress[(mscadd.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscaddress, len));
        idp->SetMscAddress(isdn);
    }

    isNull = (*cfg)["calledPartyBCDNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["calledPartyBCDNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        std::string cldPrtyBCDNmbr = (*cfg)["calledPartyBCDNumber"]["Value"].asString();

        int len = MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(0, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                l_calldpartybcdnum, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                (l_calldpartybcdnum+1), MAX_CALLED_PARTY_BCD_NUMBER_DIGITS, 0, false);
        if (cldPrtyBCDNmbr.length() % 2)
        {
            l_calldpartybcdnum[(cldPrtyBCDNmbr.length() / 2)] |= 0xF0;
        }
        cap_v3::CalledPartyBCDNumber cp(MAPUtils::ByteArrayToVector(l_calldpartybcdnum, len));
        idp->SetCalledPartyBCDNumber(cp);
    }
    
    isNull = (*cfg)["timeAndTimezone"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["timeAndTimezone"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        tatz = (*cfg)["timeAndTimezone"]["Value"].asString();
        if(tatz.length() >= MAX_TIME_AND_TIME_ZONE_DIGITS)
        {
            tatz.erase(MAX_TIME_AND_TIME_ZONE_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tatz, l_timeandtimezone, MAP_MAX_E164_SZ);
        cap_v3::TimeAndTimezone tat(MAPUtils::ByteArrayToVector(l_timeandtimezone, len));

        idp->SetTimeAndTimezone(tat);
    }

    isNull = (*cfg)["gsm_ForwardingPending"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["gsm_ForwardingPending"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::InitialDPArg::Gsm_ForwardingPending gsm;
        idp->SetGsm_ForwardingPending(gsm);
    }

    isNull = (*cfg)["carrier"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["carrier"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string car = (*cfg)["carrier"]["Value"].asString();
        if(car.length() >= MAX_CARRIER_DIGITS)
        {
            car.erase(MAX_CARRIER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(car.substr(0, MAX_CARRIER_DIGITS_LENGTH), l_carrier, MAX_CARRIER_DIGITS_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(car.substr(MAX_CARRIER_DIGITS_LENGTH), (l_carrier+2), MAX_CARRIER_DIGITS_LENGTH, 0, false);
        cap_v3::Carrier carrier(MAPUtils::ByteArrayToVector(l_carrier, len));
        idp->SetCarrier(carrier);
    }

    isNull = (*cfg)["cug_Index"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Index"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CUG_Index ci((*cfg)["cug_Index"]["Value"].asInt());
        idp->SetCug_Index(ci);
    }

    isNull = (*cfg)["cug_Interlock"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Interlock"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cug_interlock = (*cfg)["cug_Interlock"]["Value"].asString();
        if(cug_interlock.length() >= MAX_CUG_INTERLOCK_DIGITS)
        {
            cug_interlock.erase(MAX_CUG_INTERLOCK_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(cug_interlock, l_cuginterlock, MAX_CUG_INTERLOCK_DIGITS, 0, true);
 
        cap_v3::CUG_Interlock ci(MAPUtils::ByteArrayToVector(l_cuginterlock, len));
        idp->SetCug_Interlock(ci);
    }
    
    isNull = (*cfg)["cug_OutgoingAccess"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["cug_OutgoingAccess"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::InitialDPArg::Cug_OutgoingAccess coa;
        idp->SetCug_OutgoingAccess(coa);
    }

    isNull = (*cfg)["initialDPArgExtension"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["initialDPArgExtension"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::InitialDPArgExtension idpext;


        isNull = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string gmscadd = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].asString();
            if(gmscadd.length() > MAX_GMSC_ADDRESS_DIGITS)
            {
                gmscadd.erase(MAX_GMSC_ADDRESS_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(gmscadd.substr(0, MAX_GMSC_ADDRESS_HEADER_LENGTH), 
                    l_gmscaddress, MAX_GMSC_ADDRESS_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(gmscadd.substr(MAX_GMSC_ADDRESS_HEADER_LENGTH), (l_gmscaddress+1), MAX_GMSC_ADDRESS_DIGITS);
            if (gmscadd.length() % 2)
            {
                l_gmscaddress[(gmscadd.length() / 2)] |= 0xF0;
            }
            cap_v3::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_gmscaddress, len));
            idpext.SetGmscAddress(isdn);
            idp->SetInitialDPArgExtension(idpext);
        }

    }
    return idp;
}

AsnObject* BuildInitialDPArgV2()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    std::string bc = "";
    uint8_t l_imsi[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_timeandtimezone[MAP_MAX_E164_SZ/2] = {0};
    uint8_t l_callingpartyNum[10] = {0};
    uint8_t l_bearercap[11] = {0};
    uint8_t l_carrier[4] = {0};
    uint8_t l_cuginterlock[4] = {0};
    uint8_t l_mscaddress[9] = {0};
    uint8_t l_gmscaddress[9] = {0};
    uint8_t l_callreferencenumber[8] = {0};
    uint8_t l_cause[2] = {0};
    uint8_t l_ipsspcap[4] = {0};
    uint8_t l_vlrnumber[9] = {0};
    uint8_t l_mscnumber[9] = {0};
    uint8_t l_locationnumber[10] = {0};
    uint8_t l_calldpartybcdnum[10] = {0};

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap"];

    Json::Value* cfg = &(*m_jsonRoot1)["InitialDPArg"];

    cap_v2::InitialDPArg *idp = new cap_v2::InitialDPArg();

    isNull = (*cfg)["serviceKey"]["Value"].isNull();
    if(!isNull)
    {
        cap_v2::ServiceKey sk((*cfg)["serviceKey"]["Value"].asInt());
        idp->SetServiceKey(sk); 
    }

    isNull = (*cfg)["calledPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["calledPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["calledPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLED_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLED_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }
        cap_v2::CalledPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCalledPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cpan = (*cfg)["callingPartyNumber"]["Value"].asString();
        if(cpan.length() > MAX_CALLING_PARTY_NUMBER_DIGITS)
        {
            cpan.erase(MAX_CALLING_PARTY_NUMBER_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cpan.substr(MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0x00;
        }

        cap_v2::CallingPartyNumber cpn(MAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCallingPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartysCategory"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartysCategory"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string category = (*cfg)["callingPartysCategory"]["Value"].asString();
        if(category.length() > MAX_CALLING_PARTYS_CATEGORY_DIGITS)
        {
            category.erase(MAX_CALLING_PARTYS_CATEGORY_DIGITS, std::string::npos);
        }
        uint8_t tbcd[2] = {0};
        int len = MAPUtils::StringToTBCD(category.substr(0, MAX_CALLING_PARTYS_CATEGORY_DIGITS), tbcd, MAX_CALLING_PARTYS_CATEGORY_DIGITS, 0, true);
        cap_v2::CallingPartysCategory cpc(MAPUtils::ByteArrayToVector(tbcd, 1));
        idp->SetCallingPartysCategory(cpc);
    }

    #if 0
    isNull = (*cfg)["cGEncountered"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cGEncountered"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CGEncountered cge((*cfg)["cGEncountered"]["Value"].asInt());
        idp->SetCGEncountered(cge);
    }
    #endif 
    
    isNull = (*cfg)["iPSSPCapabilities"]["Value"].isNull();
    isAVPEnabled = (*cfg)["iPSSPCapabilities"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string ipspcap = (*cfg)["iPSSPCapabilities"]["Value"].asString();
        if(ipspcap.length() > MAX_IPSSP_CAPABILITY_DIGITS)
        {
            ipspcap.erase(MAX_IPSSP_CAPABILITY_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(ipspcap, l_ipsspcap, MAX_IPSSP_CAPABILITY_DIGITS, 0, true);

        cap_v2::IPSSPCapabilities ips(MAPUtils::ByteArrayToVector(l_ipsspcap, len));
        idp->SetIPSSPCapabilities(ips);
    }

    isNull = (*cfg)["locationNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["locationNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string locnum = (*cfg)["locationNumber"]["Value"].asString();
        uint8_t l_locnum[10] = {0};
        if(locnum.length() > MAX_LOCATION_NUMBER_DIGITS)
        {
            locnum.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(locnum.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), l_locnum, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(locnum.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), (l_locnum+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
        if (locnum.length() % 2)
        {
            l_locnum[(locnum.length() / 2)] |= 0x00;
        }

        cap_v2::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locnum, len));
        idp->SetLocationNumber(ln);
    }

    isNull = (*cfg)["originalCalledPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["originalCalledPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_origcalledPartyId[10] = {0};
        string origcalledPartyId = (*cfg)["originalCalledPartyID"]["Value"].asString();
        if(origcalledPartyId.length() > MAX_ORG_CALLED_PARTY_ID_DIGITS)
        {
            origcalledPartyId.erase(MAX_ORG_CALLED_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(origcalledPartyId.substr(0, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                l_origcalledPartyId, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(origcalledPartyId.substr(MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                (l_origcalledPartyId+2), MAX_ORG_CALLED_PARTY_ID_DIGITS, 0, false);

        if (origcalledPartyId.length() % 2)
        {
            l_origcalledPartyId[(origcalledPartyId.length() / 2)] |= 0x00;
        }
        cap_v2::OriginalCalledPartyID ocp(MAPUtils::ByteArrayToVector(l_origcalledPartyId, len));
        idp->SetOriginalCalledPartyID(ocp);
    }
#if 0
    isNull = (*cfg)["extensions"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["extensions"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        //TODO: check with the format
        cap_v3::ExtensionField exts;

        isNull = (*cfg)["extensions"]["type"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::ExtensionField::Type type((*cfg)["extensions"]["type"]["Value"].asInt());
            exts.SetType(type);
        }

        isNull = (*cfg)["extensions"]["criticality"]["Value"].isNull();
        if(!isNull)
        {
            cap_v3::ExtensionField::CriticalityType ctype((*cfg)["extensions"]["criticality"]["Value"].asInt());
            exts.SetCriticality(ctype);
        }

        isNull = (*cfg)["extensions"]["value"]["Value"].isNull();
        if(!isNull)
        {
            //TODO: check with the format
            //cap_v3::ExtensionField::Value val((*cfg)["extensions"]["value"]["Value"]);
            //exts.SetValue(val);
        }

        //TODO: check with the format
        //idp->SetExtensions(exts);
    }
#endif
#if 0
    isNull = (*cfg)["highLayerCompatibility"]["Value"].isNull();
    isAVPEnabled = (*cfg)["highLayerCompatibility"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::HighLayerCompatibility hlc(MAPUtils::StringToVector((*cfg)["highLayerCompatibility"]["Value"].asString()));
        idp->SetHighLayerCompatibility(hlc);
    }
#endif

    isNull = (*cfg)["additionalCallingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["additionalCallingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_addcallingpartynumber[10] = {0};
        std::string addcallingpartynumber = (*cfg)["additionalCallingPartyNumber"]["Value"].asString();;

        int len = MAPUtils::StringToTBCD(addcallingpartynumber.substr(0, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), 
                l_addcallingpartynumber, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(addcallingpartynumber.substr(MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_addcallingpartynumber+3), MAX_ADDITIONAL_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (addcallingpartynumber.length() % 2)
        {
            l_addcallingpartynumber[(addcallingpartynumber.length() / 2)] |= 0xF0;
        }
        cap_v2::AdditionalCallingPartyNumber acpn(MAPUtils::ByteArrayToVector(l_addcallingpartynumber, len));
        idp->SetAdditionalCallingPartyNumber(acpn);
    }

    isNull = (*cfg)["bearerCapability"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["bearerCapability"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::BearerCapability beca;
        isNull = (*cfg)["bearerCapability"]["bearerCap"]["Value"].isNull();
        isAVPEnabled = (*cfg)["bearerCapability"]["bearerCap"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            bc = (*cfg)["bearerCapability"]["bearerCap"]["Value"].asString();
            int len = MAPUtils::StringToTBCD(bc, l_bearercap, MAP_MAX_E164_SZ, 0, true);
            if (bc.length() % 2)
            {
                l_bearercap[(bc.length() / 2)] |= 0xF0;
            }
            cap_v2::BearerCapability::BearerCap bcap(MAPUtils::ByteArrayToVector(l_bearercap, len));

            beca.SetChoiceBearerCap(bcap);
        }
        idp->SetBearerCapability(beca);
    }
    
    isNull = (*cfg)["eventTypeBCSM"]["Value"].isNull();
    isAVPEnabled = (*cfg)["eventTypeBCSM"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::EventTypeBCSM etb((*cfg)["eventTypeBCSM"]["Value"].asInt());
        idp->SetEventTypeBCSM(etb);
    }

    isNull = (*cfg)["redirectingPartyID"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectingPartyID"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectpartyid[10] = {0};
        string redirectingpartyid = (*cfg)["redirectingPartyID"]["Value"].asString();
        if(redirectingpartyid.length() > MAX_REDIRECTING_PARTY_ID_DIGITS)
        {
            redirectingpartyid.erase(MAX_REDIRECTING_PARTY_ID_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(redirectingpartyid.substr(0, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), l_redirectpartyid, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(redirectingpartyid.substr(MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), (l_redirectpartyid+2), MAX_REDIRECTING_PARTY_ID_DIGITS, 0, false);
 
        if (redirectingpartyid.length() % 2)
        {
            l_redirectpartyid[(redirectingpartyid.length() / 2)] |= 0x00;
        }
        cap_v2::RedirectingPartyID rpi(MAPUtils::ByteArrayToVector(l_redirectpartyid, len));
 
        idp->SetRedirectingPartyID(rpi);
    }

    isNull = (*cfg)["redirectionInformation"]["Value"].isNull();
    isAVPEnabled = (*cfg)["redirectionInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_redirectinginfo[2] = {0};
        string redirectioninfo = (*cfg)["redirectionInformation"]["Value"].asString();
        if(redirectioninfo.length() > MAX_REDIRECTION_INFORMATION_DIGITS)
        {
            redirectioninfo.erase(MAX_REDIRECTION_INFORMATION_DIGITS, std::string::npos);
        }

        int len = MAPUtils::StringToTBCD(redirectioninfo, l_redirectinginfo, MAX_REDIRECTION_INFORMATION_DIGITS, 0, true);
        cap_v2::RedirectionInformation ri(MAPUtils::ByteArrayToVector(l_redirectinginfo, len));
 
        idp->SetRedirectionInformation(ri);
    }

#if 0
    isNull = (*cfg)["cause"]["Value"].isNull();
    isAVPEnabled = (*cfg)["cause"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cse = (*cfg)["cause"]["Value"].asString();
        if(cse.length() > MAX_CAUSE_DIGITS)
        {
            cse.erase(MAX_CAUSE_DIGITS, std::string::npos);
        }
        
        int len = MAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
        if (cse.length() % 2)
        {
            l_cause[(cse.length() / 2)] |= 0xF0;
        }
        cap_v3::Cause cause(MAPUtils::ByteArrayToVector(l_cause, len));
        idp->SetCause(cause);
    }

    isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::ServiceInteractionIndicatorsTwo servIndic;

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ForwardServiceInteractionInd fsin;

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                fsin.SetConferenceTreatmentIndicator(cti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallDiversionTreatmentIndicator cdt(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallDiversionTreatmentIndicator(cdt);
            }
            
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardS    erviceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallCompletionTreatmentIndicator(ccti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallingPartyRestrictionIndicator cpri(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwar    dS    erviceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].asString()));
                fsin.SetCallingPartyRestrictionIndicator(cpri);
            }

            servIndic.SetForwardServiceInteractionInd(fsin);
        }
        
        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::BackwardServiceInteractionInd bsii;
           
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::BackwardServiceInteractionInd::ConferenceTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                bsii.SetConferenceTreatmentIndicator(cti);
            }
 
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::BackwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                bsii.SetCallCompletionTreatmentIndicator(ccti);
            }
            servIndic.SetBackwardServiceInteractionsInd(bsii);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::BothwayThroughConnectionInd btci((*cfg)["serviceInteractionIndicatorsTwo"]["bothwayThroughConnectionInd"]["Value"].asInt());
            servIndic.SetBothwayThroughConnectionInd(btci);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ConnectedNumberTreatmentInd cnti((*cfg)["serviceInteractionIndicatorsTwo"]["connectedNumberTreatmentInd"]["Value"].asInt());
            servIndic.SetConnectedNumberTreatmentInd(cnti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator hti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].asString()));
            servIndic.SetHoldTreatmentIndicator(hti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::CwTreatmentIndicator cti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].asString()));
            servIndic.SetCwTreatmentIndicator(cti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::EctTreatmentIndicator eti(MAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].asString()));
            servIndic.SetEctTreatmentIndicator(eti);
        }
        idp->SetServiceInteractionIndicatorsTwo(servIndic);
    }
#endif


    isNull = (*cfg)["imsi"]["Value"].isNull();
    isAVPEnabled = (*cfg)["imsi"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        Imsi = (*cfg)["imsi"]["Value"].asString();
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
        cap_v2::IMSI imsi(MAPUtils::ByteArrayToVector(l_imsi, len));
        idp->SetIMSI(imsi);
    }
    
    isNull = (*cfg)["subscriberState"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["subscriberState"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::SubscriberState ss;

        isNull = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["subscriberState"]["assumedIdle"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::SubscriberState::AssumedIdle ai;
            ss.SetChoiceAssumedIdle(ai);
        }
        else
        {
            isNull = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].isNull();
            isAVPEnabled = (*cfg)["subscriberState"]["camelBusy"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v2::SubscriberState::CamelBusy cb;
                ss.SetChoiceCamelBusy(cb);
            }
            else
            {
                isNull = (*cfg)["subscriberState"]["netDetNotReachable"]["Value"].isNull();
                isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v2::SubscriberState::NotReachableReason nrr((*cfg)["subscriberState"]["netDetNotReachable"]["Value"].asInt());
                    ss.SetChoiceNetDetNotReachable(nrr);
                }
                else
                {
                    isNull = (*cfg)["subscriberState"]["notProvidedFromVLR"]["Enabled"].isNull();
                    isAVPEnabled = (*cfg)["subscriberState"]["netDetNotReachable"]["Enabled"].asBool();
                    if(!isNull && isAVPEnabled)
                    {
                        cap_v2::SubscriberState::NotProvidedFromVLR npfv;
                        ss.SetChoiceNotProvidedFromVLR(npfv);
                    }
                }
            }
        }
        idp->SetSubscriberState(ss);
    }

    isNull = (*cfg)["locationInformation"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["locationInformation"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::LocationInformation li;
        
        isNull = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["ageOfLocationInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::LocationInformation::AgeOfLocationInformation aoli((*cfg)["locationInformation"]["ageOfLocationInformation"]["Value"].asInt());
            li.SetAgeOfLocationInformation(aoli);
        }

        isNull = (*cfg)["locationInformation"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::LocationInformation::GeographicalInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geographicalInformation"]["Value"].asString()));
            li.SetGeographicalInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["vlr_number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["vlr_number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string vlrnum = (*cfg)["locationInformation"]["vlr_number"]["Value"].asString();
            if(vlrnum.length() > MAX_VLR_NUMBER_DIGITS)
            {
                vlrnum.erase(MAX_VLR_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH), 
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
 
            cap_v2::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_vlrnumber, len));
            li.SetVlr_number(isdn);
        }
        
        isNull = (*cfg)["locationInformation"]["locationNumber"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["locationNumber"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string locinfo = (*cfg)["locationInformation"]["locationNumber"]["Value"].asString();
            if(locinfo.length() > MAX_LOCATION_NUMBER_DIGITS)
            {
                locinfo.erase(MAX_LOCATION_NUMBER_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0xF0;
            }

            cap_v2::LocationInformation::LocationNumber ln(MAPUtils::ByteArrayToVector(l_locationnumber, len));
            li.SetLocationNumber(ln);
        }

        isNull = (*cfg)["locationInformation"]["cellIdOrLAI"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::LocationInformation::CellIdOrLAI cgi;

            isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["Enabled"].asBool();
            if(isAVPEnabled)
            {
                uint8_t tbcd[7] = {0};
                string mcc = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["mcc"].asString();
                string mnc = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["mnc"].asString();
                string locArea = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["LocationArea"].asString();
                string cellId = (*cfg)["locationInformation"]["cellIdOrLAI"]["cellIdFixedLength"]["CellId"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                }
                cap_v2::LocationInformation::CellIdOrLAI::CellIdFixedLength cgil(MAPUtils::ByteArrayToVector(tbcd, 7));
                cgi.SetChoiceCellIdFixedLength(cgil);
            }
            else
            {
                isAVPEnabled = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["Enabled"].asBool();
                if(isAVPEnabled)
                {
                    uint8_t tbcd[7] = {0};
                    string mcc = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["mcc"].asString();
                    string mnc = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["mnc"].asString();
                    string locArea = (*cfg)["locationInformation"]["cellIdOrLAI"]["laiFixedLength"]["LocationArea"].asString();
                    if(mcc.length() != 0  && mnc.length() != 0 )
                    {
                        tbcd[0] = MAPUtils::ToHex(mcc.c_str()[0]) | (MAPUtils::ToHex(mcc.c_str()[1]) << 4);
                        if(mnc.length() == 3)
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | (MAPUtils::ToHex(mnc.c_str()[2]) << 4);
                        }
                        else
                        {
                            tbcd[1] = MAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                        }
                        tbcd[2] = MAPUtils::ToHex(mnc.c_str()[0]) | (MAPUtils::ToHex(mnc.c_str()[1]) << 4);
                        tbcd[3] = atoi(locArea.c_str()) >> 8;
                        tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    }

                    cap_v2::LocationInformation::CellIdOrLAI::LAIFixedLength lai(MAPUtils::ByteArrayToVector(tbcd, 5));
 
                    cgi.SetChoiceLaiFixedLength(lai);
                }
            }
            li.SetCellIdOrLAI(cgi);
        }

#if 0
        isNull = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["selectedLSA_Id"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            uint8_t l_lsaid[3] = {0};
            string lsaId = (*cfg)["locationInformation"]["selectedLSA_Id"]["Value"].asString();
             if(lsaId.length() > MAX_LSA_ID_DIGITS)
            {
                lsaId.erase(MAX_LSA_ID_DIGITS, std::string::npos);
            }

            int len = MAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::LSAIdentity lsa(MAPUtils::ByteArrayToVector(l_lsaid, len));
 
            li.SetSelectedLSA_Id(lsa);
        }

        isNull = (*cfg)["locationInformation"]["msc_Number"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["msc_Number"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string mscnum = (*cfg)["locationInformation"]["msc_Number"]["Value"].asString();
            if(mscnum.length() > MAX_MSC_NUMBER_DIGITS)
            {
                mscnum.erase(MAX_MSC_NUMBER_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformation"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeodeticInformation gi(MAPUtils::StringToVector((*cfg)["locationInformation"]["geodeticInformation"]["Value"].asString()));
            li.SetGeodeticInformation(gi);
        }

        isNull = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["currentLocationRetrieved"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v2::LocationInformation::CurrentLocationRetrieved clr;
            li.SetCurrentLocationRetrieved(clr);
        }
#endif        
        idp->SetLocationInformation(li);
    }
    
    isNull = (*cfg)["ext_basicServiceCode"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::Ext_BasicServiceCode txtb;

        isNull = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Enabled"].asBool();
        uint8_t l_bs[5] = {0};
        if(!isNull && isAVPEnabled)
        {
            string bs = (*cfg)["ext_basicServiceCode"]["ext_BearerService"]["Value"].asString();
            if(bs.length() > MAX_BASIC_SERVICE_CODE_DIGITS)
            {
                bs.erase(MAX_BASIC_SERVICE_CODE_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_BASIC_SERVICE_CODE_DIGITS, 0, true);
            cap_v2::Ext_BasicServiceCode::Ext_BearerServiceCode ebs(MAPUtils::ByteArrayToVector(l_bs, len)); 
            txtb.SetChoiceExt_BearerService(ebs);
        }
        else
        {
            isNull = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].isNull();
            isAVPEnabled  = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                string bs = (*cfg)["ext_basicServiceCode"]["ext_Teleservice"]["Value"].asString();
                if(bs.length() > MAX_TELE_SERVICE_CODE_DIGITS)
                {
                    bs.erase(MAX_TELE_SERVICE_CODE_DIGITS, std::string::npos);
                }
                int len = MAPUtils::StringToTBCD(bs, l_bs, MAX_TELE_SERVICE_CODE_DIGITS, 0, true);
                cap_v2::Ext_BasicServiceCode::Ext_TeleserviceCode etc(MAPUtils::ByteArrayToVector(l_bs, len));
                txtb.SetChoiceExt_Teleservice(etc);
            }
        }
        idp->SetExt_basicServiceCode(txtb);
    }

    isNull = (*cfg)["callReferenceNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["callReferenceNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string callreferencenumber = (*cfg)["callReferenceNumber"]["Value"].asString();
        if(callreferencenumber.length() > MAX_CALL_REFERENCE_NUMBER_DIGITS)
        {
            callreferencenumber.erase(MAX_CALL_REFERENCE_NUMBER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_CALL_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }
        cap_v2::CallReferenceNumber crn(MAPUtils::ByteArrayToVector(l_callreferencenumber, len));
        idp->SetCallReferenceNumber(crn);
    }

    isNull = (*cfg)["mscAddress"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["mscAddress"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string mscadd = (*cfg)["mscAddress"]["Value"].asString();
        if(mscadd.length() > MAX_MSC_ADDRESS_DIGITS)
        {
            mscadd.erase(MAX_MSC_ADDRESS_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(mscadd.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(mscadd.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscadd.length() % 2)
        {
            l_mscaddress[(mscadd.length() / 2)] |= 0xF0;
        }
        cap_v2::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_mscaddress, len));
        idp->SetMscAddress(isdn);
    }

    isNull = (*cfg)["calledPartyBCDNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["calledPartyBCDNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        std::string cldPrtyBCDNmbr = (*cfg)["calledPartyBCDNumber"]["Value"].asString();

        int len = MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(0, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                l_calldpartybcdnum, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                (l_calldpartybcdnum+1), MAX_CALLED_PARTY_BCD_NUMBER_DIGITS, 0, false);
        if (cldPrtyBCDNmbr.length() % 2)
        {
            l_calldpartybcdnum[(cldPrtyBCDNmbr.length() / 2)] |= 0xF0;
        }
        cap_v2::CalledPartyBCDNumber cp(MAPUtils::ByteArrayToVector(l_calldpartybcdnum, len));
        idp->SetCalledPartyBCDNumber(cp);
    }
    
    isNull = (*cfg)["timeAndTimezone"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["timeAndTimezone"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        tatz = (*cfg)["timeAndTimezone"]["Value"].asString();
        if(tatz.length() >= MAX_TIME_AND_TIME_ZONE_DIGITS)
        {
            tatz.erase(MAX_TIME_AND_TIME_ZONE_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(tatz, l_timeandtimezone, MAP_MAX_E164_SZ);
        cap_v2::TimeAndTimezone tat(MAPUtils::ByteArrayToVector(l_timeandtimezone, len));

        idp->SetTimeAndTimezone(tat);
    }

    isNull = (*cfg)["gsm_ForwardingPending"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["gsm_ForwardingPending"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::InitialDPArg::Gsm_ForwardingPending gsm;
        idp->SetGsm_ForwardingPending(gsm);
    }

#if 0
    isNull = (*cfg)["carrier"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["carrier"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string car = (*cfg)["carrier"]["Value"].asString();
        if(car.length() >= MAX_CARRIER_DIGITS)
        {
            car.erase(MAX_CARRIER_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(car.substr(0, MAX_CARRIER_DIGITS_LENGTH), l_carrier, MAX_CARRIER_DIGITS_LENGTH, 0, true);
        len += MAPUtils::StringToTBCD(car.substr(MAX_CARRIER_DIGITS_LENGTH), (l_carrier+2), MAX_CARRIER_DIGITS_LENGTH, 0, false);
        cap_v3::Carrier carrier(MAPUtils::ByteArrayToVector(l_carrier, len));
        idp->SetCarrier(carrier);
    }

    isNull = (*cfg)["cug_Index"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Index"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::CUG_Index ci((*cfg)["cug_Index"]["Value"].asInt());
        idp->SetCug_Index(ci);
    }

    isNull = (*cfg)["cug_Interlock"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["cug_Interlock"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        string cug_interlock = (*cfg)["cug_Interlock"]["Value"].asString();
        if(cug_interlock.length() >= MAX_CUG_INTERLOCK_DIGITS)
        {
            cug_interlock.erase(MAX_CUG_INTERLOCK_DIGITS, std::string::npos);
        }
        int len = MAPUtils::StringToTBCD(cug_interlock, l_cuginterlock, MAX_CUG_INTERLOCK_DIGITS, 0, true);
 
        cap_v3::CUG_Interlock ci(MAPUtils::ByteArrayToVector(l_cuginterlock, len));
        idp->SetCug_Interlock(ci);
    }
    
    isNull = (*cfg)["cug_OutgoingAccess"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["cug_OutgoingAccess"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v3::InitialDPArg::Cug_OutgoingAccess coa;
        idp->SetCug_OutgoingAccess(coa);
    }
#endif

    isNull = (*cfg)["initialDPArgExtension"]["Enabled"].isNull();
    isAVPEnabled  = (*cfg)["initialDPArgExtension"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        cap_v2::InitialDPArgExtension idpext;


        isNull = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].isNull();
        isAVPEnabled  = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            string gmscadd = (*cfg)["initialDPArgExtension"]["gmscAddress"]["Value"].asString();
            if(gmscadd.length() > MAX_GMSC_ADDRESS_DIGITS)
            {
                gmscadd.erase(MAX_GMSC_ADDRESS_DIGITS, std::string::npos);
            }
            int len = MAPUtils::StringToTBCD(gmscadd.substr(0, MAX_GMSC_ADDRESS_HEADER_LENGTH), 
                    l_gmscaddress, MAX_GMSC_ADDRESS_HEADER_LENGTH, 0, true);
            len += MAPUtils::StringToTBCD(gmscadd.substr(MAX_GMSC_ADDRESS_HEADER_LENGTH), (l_gmscaddress+1), MAX_GMSC_ADDRESS_DIGITS);
            if (gmscadd.length() % 2)
            {
                l_gmscaddress[(gmscadd.length() / 2)] |= 0xF0;
            }
            cap_v2::ISDN_AddressString isdn(MAPUtils::ByteArrayToVector(l_gmscaddress, len));
            idpext.SetGmscAddress(isdn);
            idp->SetInitialDPArgExtension(idpext);
        }
        

    }
    return idp;
}
