#define CallingLegId "1"
#define CalledLegId "2"
#define TCAP_OPERATION_CLASS    1
#define NORMAL_CALL_CLEARING 0x90
#define USER_BUSY 0x91
#define USER_NOANS 0x93

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))


bool IsBusyornoAnswerSet = false;
bool sendERBandACRinTcContAgain = false;
extern ITS_UINT oPC;
extern int CapVersion;

template <typename T> inline std::vector<T> 
ArrayToVector(T array[],size_t size)
{ 
    return std::vector<T>(array, array + size); 
}


Json::Value parseCapConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;

    char *jsonFile = getenv("CAP_IWF_CONFIG_FILE");
    if (jsonFile == NULL )
    {
        APP_TRACE_ERROR(("CAP_IWF_JSON is not exported"));
        exit(0);
    }
    APP_TRACE_DEBUG(("DRE_JSON=%s",jsonFile));

    std::ifstream doc(jsonFile);
    bool ret = m_jsonConfigFileReader.parse(doc,m_jsonroot);
    if(ret == false)
    {
        APP_TRACE_ERROR(("Parsing of JSON Config file failed."));
    }
    return m_jsonroot;
}


AsnObject* BuildCapMsg(int opCode)
{
    AsnObject *obj= NULL;

    switch(opCode)
    {
        case OP_initialDP:
            {
                obj = BuildInitialDPArg();
                break;
            }
        case OP_eventReportBCSM:
            {
                obj = BuildEventReportBCSMArg();
                break;
            }
        case OP_applyChargingReport:
            {   
                obj = BuildApplyChargingReport();
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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
 
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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["ApplyChargingReportArg_in_TcCont_Again"];
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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
 
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
    
	if(NULL != camelresultBuf)
	{
		delete camelresultBuf;
		camelresultBuf = NULL;
	}
    return acr;
}

AsnObject* BuildApplyChargingReportinTcEnd()
{
    bool isNull;
    bool isAVPEnabled;

    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
 
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
    
	if(NULL != camelresultBuf)
	{
		delete camelresultBuf;
		camelresultBuf = NULL;
	}
    return acr;
}

AsnObject* BuildEventReportSMSArg()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportSMSArg"];
    cap_v3::EventReportSMSArg *erb = new EventReportSMSArg();
 

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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];
    cap_v3::EventReportBCSMArg *erb = new EventReportBCSMArg();
 

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
                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
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

AsnObject* BuildEventReportBCSMArginTcCont()
{
    bool isNull;
    bool isAVPEnabled;
 
    Json::Value l_jsonRoot = parseCapConfig();

    m_jsonRoot = &l_jsonRoot;
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];
    Json::Value* cfg = NULL;

    if(sendERBandACRinTcContAgain)
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont_Again"];
    else
        cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcCont"];

    cap_v3::EventReportBCSMArg *erb = new EventReportBCSMArg();
 

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
                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

    Json::Value* cfg = &(*m_jsonRoot1)["EventReportBCSMArg_in_TcEnd"];
    cap_v3::EventReportBCSMArg *erb = new EventReportBCSMArg();
 

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
                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                cap_v3::EventSpecificInformationBCSM::RouteSelectFailureSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                    cap_v3::EventSpecificInformationBCSM::OCalledPartyBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);

                            cap_v3::EventSpecificInformationBCSM::OAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                cap_v3::EventSpecificInformationBCSM::ODisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                                    int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);

                                    cap_v3::EventSpecificInformationBCSM::TBusySpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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

                                            int len = CAPUtils::StringToTBCD(dest.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_destinationaddress, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
                                            len += CAPUtils::StringToTBCD(dest.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_destinationaddress+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
                                            cap_v3::EventSpecificInformationBCSM::TAnswerSpecificInfo::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_destinationaddress, len));
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
                                                int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
                                                cap_v3::EventSpecificInformationBCSM::TDisconnectSpecificInfo::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
            int len = CAPUtils::StringToTBCD(rsi, l_rsi, MAX_LEG_ID_DIGITS, 0, true);
            cap_v3::ReceivingSideID::LegType lt(CAPUtils::ByteArrayToVector(l_rsi, len));
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

AsnObject* BuildInitialDPSMSArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    uint8_t l_imsi[CAP_MAX_E164_SZ/2];
    uint8_t l_timeandtimezone[CAP_MAX_E164_SZ/2];
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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

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
        int len = CAPUtils::StringToTBCD(destsubsnumber.substr(0, MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH), 
                l_destsubsnumber, MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(destsubsnumber.substr(MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH), 
                (l_destsubsnumber+1), MAX_DEST_SUBSCRIBER_NUMBER_DIGITS, 0, false);
        if (destsubsnumber.length() % 2)
        {
            l_destsubsnumber[(destsubsnumber.length() / 2)] |= 0xF0;
        }
 
        cap_v3::CalledPartyBCDNumber cpn(CAPUtils::ByteArrayToVector(l_destsubsnumber, len));
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
        int len = CAPUtils::StringToTBCD(cpnum.substr(0, MAX_ISDN_ADDRESS_HEADER_LENGTH), 
                l_callinpartynumber, MAX_ISDN_ADDRESS_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(cpnum.substr(MAX_ISDN_ADDRESS_HEADER_LENGTH), (l_callinpartynumber+1), MAX_ISDN_ADDRESS_DIGITS);
        if (cpnum.length() % 2)
        {
            l_callinpartynumber[(cpnum.length() / 2)] |= 0xF0;
        }
 
        cap_v3::ISDN_AddressString cpn(CAPUtils::ByteArrayToVector(l_callinpartynumber, len));
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

        int len = CAPUtils::StringToTBCD(Imsi, l_imsi, CAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        cap_v3::IMSI imsi(CAPUtils::ByteArrayToVector(l_imsi, len));
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
            cap_v3::LocationInformation::GeographicalInformation gi(CAPUtils::StringToVector((*cfg)["locationInformationMSC"]["geographicalInformation"]["Value"].asString()));
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
            int len = CAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH),
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_vlrnumber, len));
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

            int len = CAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH),
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH),
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);

            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::LocationNumber ln(CAPUtils::ByteArrayToVector(l_locationnumber, len));
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
                string cellId = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["CellId"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = CAPUtils::ToHex(mcc.c_str()[0]) | (CAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | (CAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = CAPUtils::ToHex(mnc.c_str()[0]) | (CAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    cout << locArea << "tbcd[3]" << tbcd[3] << endl;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    cout << locArea << "tbcd[4]" << tbcd[4] << endl;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    cout << cellId << "tbcd[5]" << tbcd[5] << endl;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                    cout << cellId << "tbcd[6]" << tbcd[6] << endl;
                }
                cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgil(CAPUtils::ByteArrayToVector(tbcd, 7));
                cgi.SetChoiceCellGlobalIdOrServiceAreaIdFixedLength(cgil);
            }
            else
            {
                isNull = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["Value"].isNull();
                isAVPEnabled = (*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["Enabled"].asBool();
                if(!isNull && isAVPEnabled)
                {
                    cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength lai(CAPUtils::StringToVector((*cfg)["locationInformationMSC"]["cellGlobalIdOrServiceAreaIdOrLAI"]["laiFixedLength"]["Value"].asString()));
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

            int len = CAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::LSAIdentity lsa(CAPUtils::ByteArrayToVector(l_lsaid, len));
 
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
            int len = CAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformationMSC"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationMSC"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeodeticInformation gi(CAPUtils::StringToVector((*cfg)["locationInformationMSC"]["geodeticInformation"]["Value"].asString()));
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
            string cellId = (*cfg)["locationInformationGPRS"]["cellGlobalIdOrServiceAreaIdOrLAI"]["CellId"].asString();
            if(atoi(cellId.c_str()) > 65535)
            {
                APP_TRACE_ERROR(("CellId Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                return NULL;
            }
            if(mcc.length() != 0  && mnc.length() != 0 )
            {
                tbcd[0] = CAPUtils::ToHex(mcc.c_str()[0]) | (CAPUtils::ToHex(mcc.c_str()[1]) << 4);
                cout << "mcc" << mcc << "tbcd[0]" << tbcd[0] << endl;
                if(mnc.length() == 3)
                {
                    tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | (CAPUtils::ToHex(mnc.c_str()[2]) << 4);
                }
                else
                {
                    tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                }
                cout << "mnc" << mnc << "tbcd[1]" << tbcd[1] << endl;
                tbcd[2] = CAPUtils::ToHex(mnc.c_str()[0]) | (CAPUtils::ToHex(mnc.c_str()[1]) << 4);
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

            cap_v3::LocationInformationGPRS::CellGlobalIdOrServiceAreaIdOrLAI cgs(CAPUtils::ByteArrayToVector(tbcd, 7));
            ligprs.SetCellGlobalIdOrServiceAreaIdOrLAI(cgs);
        }

        isNull = (*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::RAIdentity rai(CAPUtils::StringToVector((*cfg)["locationInformationGPRS"]["routeingAreaIdentity"]["Value"].asString()));
            ligprs.SetRouteingAreaIdentity(rai);
        }

        isNull = (*cfg)["locationInformationGPRS"]["geographicalInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformationGPRS"]["geographicalInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::GeographicalInformation gi(CAPUtils::StringToVector((*cfg)["locationInformationGPRS"]["geographicalInformation"]["Value"].asString()));
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
            int len = CAPUtils::StringToTBCD(sgsnnumber.substr(0, MAX_SGSN_NUMBER_HEADER_LENGTH), l_sgsnnumber, MAX_SGSN_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(sgsnnumber.substr(MAX_SGSN_NUMBER_HEADER_LENGTH), (l_sgsnnumber+1), MAX_SGSN_NUMBER_DIGITS);
            if (sgsnnumber.length() % 2)
            {
                l_sgsnnumber[(sgsnnumber.length() / 2)] |= 0xF0;
            }

            cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_sgsnnumber, len));
 
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
            int len = CAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }

            cap_v3::LSAIdentity lsa(CAPUtils::ByteArrayToVector(l_lsaid, len));
 
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
        int len = CAPUtils::StringToTBCD(smscaddress.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_smscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(smscaddress.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), 
                (l_smscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (smscaddress.length() % 2)
        {
            l_smscaddress[(smscaddress.length() / 2)] |= 0xF0;
        }
 
        cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_smscaddress, len));
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
        int len = CAPUtils::StringToTBCD(tatz, l_timeandtimezone, CAP_MAX_E164_SZ);
        cap_v3::TimeAndTimezone tat(CAPUtils::ByteArrayToVector(l_timeandtimezone, len));

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
        int len = CAPUtils::StringToTBCD(tpshortmsg, l_tpshortsms, MAX_TP_SHORT_MESSAGE_SUB_SPE_INFO_DIGITS, 0, true);
        if (tpshortmsg.length() % 2)
        {
            l_tpshortsms[(tpshortmsg.length() / 2)] |= 0xF0;
        }

        cap_v3::TPShortMessageSubmissionInfo tps(CAPUtils::ByteArrayToVector(l_tpshortsms, len));
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
        int len = CAPUtils::StringToTBCD(tppro, l_tpprotoiden, MAX_TP_PROTOCOL_IDENTIFIER_DIGITS, 0, true);
        cap_v3::TPProtocolIdentifier tpi(CAPUtils::ByteArrayToVector(l_tpprotoiden, len));
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
        int len = CAPUtils::StringToTBCD(tpdatacodingsch, l_tpdatacodsch, MAX_TP_DATA_CODING_SCHEME_DIGITS, 0, true);
        cap_v3::TPDataCodingScheme tdcs(CAPUtils::ByteArrayToVector(l_tpdatacodsch, len));
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
            len = CAPUtils::StringToTBCD(tpvalidityperiod, l_tpvalidityperiod, MAX_TP_VALIDITY_PERIOD_DIGITS_2, 0, true);
        }
        else if(tpvalidityperiod.length() == MAX_TP_VALIDITY_PERIOD_DIGITS_14)
        {
            len = CAPUtils::StringToTBCD(tpvalidityperiod, l_tpvalidityperiod, MAX_TP_VALIDITY_PERIOD_DIGITS_14, 0, true);
        }

        cap_v3::TPValidityPeriod tvp(CAPUtils::ByteArrayToVector(l_tpvalidityperiod, len));
 
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
        int len = CAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_SMS_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }

        cap_v3::CallReferenceNumber crn(CAPUtils::ByteArrayToVector(l_callreferencenumber, len));
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
        int len = CAPUtils::StringToTBCD(mscaddress.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(mscaddress.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscaddress.length() % 2)
        {
            l_mscaddress[(mscaddress.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_mscaddress, len));
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
        int len = CAPUtils::StringToTBCD(sgsnnumber.substr(0, MAX_SGSN_NUMBER_HEADER_LENGTH),
                l_sgsnnumber, MAX_SGSN_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(sgsnnumber.substr(MAX_SGSN_NUMBER_HEADER_LENGTH), (l_sgsnnumber+1), MAX_SGSN_NUMBER_DIGITS);
        if (sgsnnumber.length() % 2)
        {
            l_sgsnnumber[(sgsnnumber.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_sgsnnumber, len));
        idp->SetSgsn_Number(isdn);
    }

    return idp;
}

AsnObject* BuildInitialDPArg()
{
    bool isNull;
    bool isAVPEnabled;
    std::string Imsi = "";
    std::string tatz = "";
    std::string bc = "";
    uint8_t l_imsi[CAP_MAX_E164_SZ/2] = {0};
    uint8_t l_timeandtimezone[CAP_MAX_E164_SZ/2] = {0};
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
    m_jsonRoot1 = &(*m_jsonRoot)["cap_v3"];

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
        
        int len = CAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(cpan.substr(MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLED_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0xF0;
        }
        cap_v3::CalledPartyNumber cpn(CAPUtils::ByteArrayToVector(l_callingpartyNum, len));
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
        
        int len = CAPUtils::StringToTBCD(cpan.substr(0, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), l_callingpartyNum, MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(cpan.substr(MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_callingpartyNum+2), MAX_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (cpan.length() % 2)
        {
            l_callingpartyNum[(cpan.length() / 2)] |= 0xF0;
        }

        cap_v3::CallingPartyNumber cpn(CAPUtils::ByteArrayToVector(l_callingpartyNum, len));
        idp->SetCallingPartyNumber(cpn);
    }

    isNull = (*cfg)["callingPartysCategory"]["Value"].isNull();
    isAVPEnabled = (*cfg)["callingPartysCategory"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t tbcd[1] = {0};
        const char *cpcg = (*cfg)["callingPartysCategory"]["Value"].asString().c_str();

        tbcd[0] = atoi(cpcg);
        
        cap_v3::CallingPartysCategory cpc(CAPUtils::ByteArrayToVector(tbcd, 1));
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
        
        int len = CAPUtils::StringToTBCD(ipspcap, l_ipsspcap, MAX_IPSSP_CAPABILITY_DIGITS, 0, true);

        cap_v3::IPSSPCapabilities ips(CAPUtils::ByteArrayToVector(l_ipsspcap, len));
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

        int len = CAPUtils::StringToTBCD(locnum.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), l_locnum, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(locnum.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), (l_locnum+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
        if (locnum.length() % 2)
        {
            l_locnum[(locnum.length() / 2)] |= 0xF0;
        }

        cap_v3::LocationNumber ln(CAPUtils::ByteArrayToVector(l_locnum, len));
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
        
        int len = CAPUtils::StringToTBCD(origcalledPartyId.substr(0, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                l_origcalledPartyId, MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(origcalledPartyId.substr(MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH), 
                (l_origcalledPartyId+2), MAX_ORG_CALLED_PARTY_ID_DIGITS, 0, false);

        if (origcalledPartyId.length() % 2)
        {
            l_origcalledPartyId[(origcalledPartyId.length() / 2)] |= 0xF0;
        }
        cap_v3::OriginalCalledPartyID ocp(CAPUtils::ByteArrayToVector(l_origcalledPartyId, len));
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
        cap_v3::HighLayerCompatibility hlc(CAPUtils::StringToVector((*cfg)["highLayerCompatibility"]["Value"].asString()));
        idp->SetHighLayerCompatibility(hlc);
    }

    isNull = (*cfg)["additionalCallingPartyNumber"]["Value"].isNull();
    isAVPEnabled = (*cfg)["additionalCallingPartyNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        uint8_t l_addcallingpartynumber[10] = {0};
        std::string addcallingpartynumber = (*cfg)["additionalCallingPartyNumber"]["Value"].asString();;

        int len = CAPUtils::StringToTBCD(addcallingpartynumber.substr(0, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), 
                l_addcallingpartynumber, MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(addcallingpartynumber.substr(MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH), (l_addcallingpartynumber+3), MAX_ADDITIONAL_CALLING_PARTY_NUMBER_DIGITS, 0, false);
        if (addcallingpartynumber.length() % 2)
        {
            l_addcallingpartynumber[(addcallingpartynumber.length() / 2)] |= 0xF0;
        }
        cap_v3::AdditionalCallingPartyNumber acpn(CAPUtils::ByteArrayToVector(l_addcallingpartynumber, len));
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
            int len = CAPUtils::StringToTBCD(bc, l_bearercap, CAP_MAX_E164_SZ, 0, true);
            if (bc.length() % 2)
            {
                l_bearercap[(bc.length() / 2)] |= 0xF0;
            }
            cap_v3::BearerCapability::BearerCap bcap(CAPUtils::ByteArrayToVector(l_bearercap, len));

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
        
        int len = CAPUtils::StringToTBCD(redirectingpartyid.substr(0, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), l_redirectpartyid, MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(redirectingpartyid.substr(MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH), (l_redirectpartyid+2), MAX_REDIRECTING_PARTY_ID_DIGITS, 0, false);
 
        if (redirectingpartyid.length() % 2)
        {
            l_redirectpartyid[(redirectingpartyid.length() / 2)] |= 0xF0;
        }
        cap_v3::RedirectingPartyID rpi(CAPUtils::ByteArrayToVector(l_redirectpartyid, len));
 
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

        int len = CAPUtils::StringToTBCD(redirectioninfo, l_redirectinginfo, MAX_REDIRECTION_INFORMATION_DIGITS, 0, true);
        cap_v3::RedirectionInformation ri(CAPUtils::ByteArrayToVector(l_redirectinginfo, len));
 
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
        
        int len = CAPUtils::StringToTBCD(cse, l_cause, MAX_CAUSE_DIGITS, 0, true);
        if (cse.length() % 2)
        {
            l_cause[(cse.length() / 2)] |= 0xF0;
        }
        cap_v3::Cause cause(CAPUtils::ByteArrayToVector(l_cause, len));
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
                cap_v3::ForwardServiceInteractionInd::ConferenceTreatmentIndicator cti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                fsin.SetConferenceTreatmentIndicator(cti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallDiversionTreatmentIndicator cdt(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callDiversionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallDiversionTreatmentIndicator(cdt);
            }
            
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwardS    erviceInteractionInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
                fsin.SetCallCompletionTreatmentIndicator(ccti);
            }

            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["forwardServiceInteractionInd"]["callingPartyRestrictionIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::ForwardServiceInteractionInd::CallingPartyRestrictionIndicator cpri(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["forwar    dS    erviceInteractionInd"]["callingPartyRestrictionIndicator"]["Value"].asString()));
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
                cap_v3::BackwardServiceInteractionInd::ConferenceTreatmentIndicator cti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["conferenceTreatmentIndicator"]["Value"].asString()));
                bsii.SetConferenceTreatmentIndicator(cti);
            }
 
            isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].isNull();
            isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Enabled"].asBool();
            if(!isNull && isAVPEnabled)
            {
                cap_v3::BackwardServiceInteractionInd::CallCompletionTreatmentIndicator ccti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["backwardServiceInteractionsInd"]["callCompletionTreatmentIndicator"]["Value"].asString()));
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
            cap_v3::ServiceInteractionIndicatorsTwo::HoldTreatmentIndicator hti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["holdTreatmentIndicator"]["Value"].asString()));
            servIndic.SetHoldTreatmentIndicator(hti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::CwTreatmentIndicator cti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["cwTreatmentIndicator"]["Value"].asString()));
            servIndic.SetCwTreatmentIndicator(cti);
        }

        isNull = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].isNull();
        isAVPEnabled = (*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::ServiceInteractionIndicatorsTwo::EctTreatmentIndicator eti(CAPUtils::StringToVector((*cfg)["serviceInteractionIndicatorsTwo"]["ectTreatmentIndicator"]["Value"].asString()));
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

        int len = CAPUtils::StringToTBCD(Imsi, l_imsi, CAP_MAX_E164_SZ);
        if (Imsi.length() % 2)
        {
            l_imsi[(Imsi.length() / 2)] |= 0xF0;
        }
        cap_v3::IMSI imsi(CAPUtils::ByteArrayToVector(l_imsi, len));
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
            cap_v3::LocationInformation::GeographicalInformation gi(CAPUtils::StringToVector((*cfg)["locationInformation"]["geographicalInformation"]["Value"].asString()));
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
            int len = CAPUtils::StringToTBCD(vlrnum.substr(0, MAX_VLR_NUMBER_HEADER_LENGTH), 
                    l_vlrnumber, MAX_VLR_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(vlrnum.substr(MAX_VLR_NUMBER_HEADER_LENGTH), (l_vlrnumber+1), MAX_VLR_NUMBER_DIGITS);
            if (vlrnum.length() % 2)
            {
                l_vlrnumber[(vlrnum.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_vlrnumber, len));
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

            int len = CAPUtils::StringToTBCD(locinfo.substr(0, MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    l_locationnumber, MAX_LOCATION_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(locinfo.substr(MAX_LOCATION_NUMBER_HEADER_LENGTH), 
                    (l_locationnumber+2), MAX_LOCATION_NUMBER_DIGITS, 0, false);
            if (locinfo.length() % 2)
            {
                l_locationnumber[(locinfo.length() / 2)] |= 0xF0;
            }

            cap_v3::LocationInformation::LocationNumber ln(CAPUtils::ByteArrayToVector(l_locationnumber, len));
            li.SetLocationNumber(ln);
        }

        isNull = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI cgi;

            isAVPEnabled = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["Enabled"].asBool();
            if(isAVPEnabled)
            {
                uint8_t tbcd[7] = {0};
                string mcc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mcc"].asString();
                string mnc = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["mnc"].asString();
                string locArea = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["LocationArea"].asString();
                string cellId = (*cfg)["locationInformation"]["cellGlobalIdOrServiceAreaIdOrLAI"]["cellGlobalIdOrServiceAreaIdFixedLength"]["CellId"].asString();
                if(atoi(cellId.c_str()) > 65535)
                {
                    APP_TRACE_ERROR(("CellId Out Of Range(0-65535) Value Passed is %d", atoi(cellId.c_str())));
                    return NULL;
                }
                if(mcc.length() != 0  && mnc.length() != 0 )
                {
                    tbcd[0] = CAPUtils::ToHex(mcc.c_str()[0]) | (CAPUtils::ToHex(mcc.c_str()[1]) << 4);
                    if(mnc.length() == 3)
                    {
                        tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | (CAPUtils::ToHex(mnc.c_str()[2]) << 4);
                    }
                    else
                    {
                        tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                    }
                    tbcd[2] = CAPUtils::ToHex(mnc.c_str()[0]) | (CAPUtils::ToHex(mnc.c_str()[1]) << 4);
                    tbcd[3] = atoi(locArea.c_str()) >> 8;
                    tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    tbcd[5] = atoi(cellId.c_str()) >> 8;
                    tbcd[6] = atoi(cellId.c_str()) & 0xff;
                }
                cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::CellGlobalIdOrServiceAreaIdFixedLength cgil(CAPUtils::ByteArrayToVector(tbcd, 7));
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
                        tbcd[0] = CAPUtils::ToHex(mcc.c_str()[0]) | (CAPUtils::ToHex(mcc.c_str()[1]) << 4);
                        if(mnc.length() == 3)
                        {
                            tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | (CAPUtils::ToHex(mnc.c_str()[2]) << 4);
                        }
                        else
                        {
                            tbcd[1] = CAPUtils::ToHex(mcc.c_str()[2]) | 0xf0;
                        }
                        tbcd[2] = CAPUtils::ToHex(mnc.c_str()[0]) | (CAPUtils::ToHex(mnc.c_str()[1]) << 4);
                        tbcd[3] = atoi(locArea.c_str()) >> 8;
                        tbcd[4] = atoi(locArea.c_str()) & 0xff;
                    }

                    cap_v3::LocationInformation::CellGlobalIdOrServiceAreaIdOrLAI::LAIFixedLength lai(CAPUtils::ByteArrayToVector(tbcd, 5));
 
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

            int len = CAPUtils::StringToTBCD(lsaId, l_lsaid, MAX_LSA_ID_DIGITS, 0, true);
            if (lsaId.length() % 2)
            {
                l_lsaid[(lsaId.length() / 2)] |= 0xF0;
            }
            cap_v3::LocationInformation::LSAIdentity lsa(CAPUtils::ByteArrayToVector(l_lsaid, len));
 
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
            int len = CAPUtils::StringToTBCD(mscnum.substr(0, MAX_MSC_NUMBER_HEADER_LENGTH), 
                    l_mscnumber, MAX_MSC_NUMBER_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(mscnum.substr(MAX_MSC_NUMBER_HEADER_LENGTH), (l_mscnumber+1), MAX_MSC_NUMBER_DIGITS);
            if (mscnum.length() % 2)
            {
                l_mscnumber[(mscnum.length() / 2)] |= 0xF0;
            }
 
            cap_v3::LocationInformation::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_mscnumber, len));
            li.SetMsc_Number(isdn);
        }

        isNull = (*cfg)["locationInformation"]["geodeticInformation"]["Value"].isNull();
        isAVPEnabled = (*cfg)["locationInformation"]["geodeticInformation"]["Enabled"].asBool();
        if(!isNull && isAVPEnabled)
        {
            cap_v3::LocationInformation::GeodeticInformation gi(CAPUtils::StringToVector((*cfg)["locationInformation"]["geodeticInformation"]["Value"].asString()));
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
            int len = CAPUtils::StringToTBCD(bs, l_bs, MAX_BASIC_SERVICE_CODE_DIGITS, 0, true);
            cap_v3::Ext_BasicServiceCode::Ext_BearerServiceCode ebs(CAPUtils::ByteArrayToVector(l_bs, len)); 
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
                int len = CAPUtils::StringToTBCD(bs, l_bs, MAX_TELE_SERVICE_CODE_DIGITS, 0, true);
                cap_v3::Ext_BasicServiceCode::Ext_TeleserviceCode etc(CAPUtils::ByteArrayToVector(l_bs, len));
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
        int len = CAPUtils::StringToTBCD(callreferencenumber, l_callreferencenumber, MAX_CALL_REFERENCE_NUMBER_DIGITS, 0 , true);
        if (callreferencenumber.length() % 2)
        {
            l_callreferencenumber[(callreferencenumber.length() / 2)] |= 0xF0;
        }
        cap_v3::CallReferenceNumber crn(CAPUtils::ByteArrayToVector(l_callreferencenumber, len));
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
        int len = CAPUtils::StringToTBCD(mscadd.substr(0, MAX_MSC_ADDRESS_HEADER_LENGTH), 
                l_mscaddress, MAX_MSC_ADDRESS_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(mscadd.substr(MAX_MSC_ADDRESS_HEADER_LENGTH), (l_mscaddress+1), MAX_MSC_ADDRESS_DIGITS);
        if (mscadd.length() % 2)
        {
            l_mscaddress[(mscadd.length() / 2)] |= 0xF0;
        }
        cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_mscaddress, len));
        idp->SetMscAddress(isdn);
    }

    isNull = (*cfg)["calledPartyBCDNumber"]["Value"].isNull();
    isAVPEnabled  = (*cfg)["calledPartyBCDNumber"]["Enabled"].asBool();
    if(!isNull && isAVPEnabled)
    {
        std::string cldPrtyBCDNmbr = (*cfg)["calledPartyBCDNumber"]["Value"].asString();

        int len = CAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(0, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                l_calldpartybcdnum, MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(cldPrtyBCDNmbr.substr(MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH), 
                (l_calldpartybcdnum+1), MAX_CALLED_PARTY_BCD_NUMBER_DIGITS, 0, false);
        if (cldPrtyBCDNmbr.length() % 2)
        {
            l_calldpartybcdnum[(cldPrtyBCDNmbr.length() / 2)] |= 0xF0;
        }
        cap_v3::CalledPartyBCDNumber cp(CAPUtils::ByteArrayToVector(l_calldpartybcdnum, len));
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
        int len = CAPUtils::StringToTBCD(tatz, l_timeandtimezone, CAP_MAX_E164_SZ);
        cap_v3::TimeAndTimezone tat(CAPUtils::ByteArrayToVector(l_timeandtimezone, len));

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
        int len = CAPUtils::StringToTBCD(car.substr(0, MAX_CARRIER_DIGITS_LENGTH), l_carrier, MAX_CARRIER_DIGITS_LENGTH, 0, true);
        len += CAPUtils::StringToTBCD(car.substr(MAX_CARRIER_DIGITS_LENGTH), (l_carrier+2), MAX_CARRIER_DIGITS_LENGTH, 0, false);
        cap_v3::Carrier carrier(CAPUtils::ByteArrayToVector(l_carrier, len));
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
        int len = CAPUtils::StringToTBCD(cug_interlock, l_cuginterlock, MAX_CUG_INTERLOCK_DIGITS, 0, true);
 
        cap_v3::CUG_Interlock ci(CAPUtils::ByteArrayToVector(l_cuginterlock, len));
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
            int len = CAPUtils::StringToTBCD(gmscadd.substr(0, MAX_GMSC_ADDRESS_HEADER_LENGTH), 
                    l_gmscaddress, MAX_GMSC_ADDRESS_HEADER_LENGTH, 0, true);
            len += CAPUtils::StringToTBCD(gmscadd.substr(MAX_GMSC_ADDRESS_HEADER_LENGTH), (l_gmscaddress+1), MAX_GMSC_ADDRESS_DIGITS);
            if (gmscadd.length() % 2)
            {
                l_gmscaddress[(gmscadd.length() / 2)] |= 0xF0;
            }
            cap_v3::ISDN_AddressString isdn(CAPUtils::ByteArrayToVector(l_gmscaddress, len));
            idpext.SetGmscAddress(isdn);
        }
        

        idp->SetInitialDPArgExtension(idpext);
    }
    return idp;
}


int BuildBcsmEvent(EventTypeBCSM eventType,
        MonitorMode monitorMode,
        std::string legid,
        BCSMEvent *bcsmEvent)
{
    int rc = ITS_SUCCESS;
    bcsmEvent->SetEventTypeBCSM(new EventTypeBCSM(eventType));

    // Monitor-Mode ie should be mapped to notifyAndContinue or Interrupt
    bcsmEvent->SetMonitorMode(new MonitorMode(monitorMode));

    //LegID should be populated based on eventTypeBCSM
    std::vector<byte> vec = CAPUtils::StringToVector(legid);
    vec[0] = vec[0]&0xF;
    LegType* lt = new LegType(vec);
    LegID legId;
    legId.SetChoiceSendingSideID(lt);

    bcsmEvent->SetLegID(legId);
    return rc;
}


int BuildRRB(TCAP_Component *&cpt, bool isSMSIdp)
{
    APP_TRACE_DEBUG(("BuildRRB -- Entry"));                      
    int rc = ITS_SUCCESS;
	Octets* buf;
    try
    {
    	if(true == isSMSIdp)
		{
			RequestReportSMSEventArg rrbSMSArg;
			
			RequestReportSMSEventArg::SMSEvents smse;
			SMSEvent smsev;
			SMSEvent smsev1;
			smsev.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_FAILURE));
			smsev.SetMonitorMode(MonitorMode::MONITOR_MODE_INTERRUPTED);
			smsev1.SetEventTypeSMS(new EventTypeSMS(EventTypeSMS::EVENT_TYPE_SMS_O_SMS_SUBMITTED));
			smsev1.SetMonitorMode(MonitorMode::MONITOR_MODE_INTERRUPTED);
			smse.AddElement(smsev);
			smse.AddElement(smsev1);
			rrbSMSArg.SetSMSEvents(smse);
			cout<<rrbSMSArg;
			buf = rrbSMSArg.Encode();
		}
        else
		{
	        RequestReportBCSMEventArg rrbArg;                                       
			
			cap_v3::RequestReportBCSMEventArg::BcsmEvents reqReportingBcsmevent;
				BCSMEvent bcsmEvent;
				
				/* MO Call,populate all the DPs related to 'O' */
				if(cap::CAPV2_VERSION == CapVersion)
				{
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_OCALLED_PARTY_BUSY,
							MonitorMode::MONITOR_MODE_INTERRUPTED,
							CalledLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
			
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER,
							MonitorMode::MONITOR_MODE_INTERRUPTED,
							CalledLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
			
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER,
							MonitorMode::MONITOR_MODE_INTERRUPTED,
							CalledLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
			
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT,
							MonitorMode::MONITOR_MODE_INTERRUPTED,
							CallingLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
			
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_OABANDON,
							MonitorMode::MONITOR_MODE_NOTIFY_AND_CONTINUE,
							CallingLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
			
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE,
							MonitorMode::MONITOR_MODE_INTERRUPTED,
							CalledLegId,
							&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);
				}
				else if(cap::CAPV1_VERSION == CapVersion )
				{
					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER,
						MonitorMode::MONITOR_MODE_INTERRUPTED,
						CalledLegId,
						&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);

					BuildBcsmEvent(EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT,
						MonitorMode::MONITOR_MODE_INTERRUPTED,
						CallingLegId,
						&bcsmEvent);
					reqReportingBcsmevent.AddElement(bcsmEvent);					
				}
			rrbArg.SetBcsmEvents(reqReportingBcsmevent);
			if ( itstest::appMode == UNIT_TEST)
				cout<<rrbArg;
			buf = rrbArg.Encode();
    	}                                        

        TCAP_Invoke *ivk = new TCAP_Invoke();                                 
        ivk->SetClass(TCAP_OPERATION_CLASS);
		if(false == isSMSIdp)
			ivk->SetOperation(cap::OP_requestReportBCSMEvent);
		else
			ivk->SetOperation(cap::OP_requestReportSMSEvent);
		
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
        APP_TRACE_ERROR(("### ASN Encode Error ### <%s>", exc.GetDescription().c_str()));
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        APP_TRACE_ERROR(("BuildRRB Unknown Exception"));
    }
    APP_TRACE_DEBUG(("BuildRRB -- Exit"));                      
    return rc;
}


int BuildACH(TCAP_Component *&cpt)
{
    APP_TRACE_DEBUG(("BuildACH -- Entry"));                      
    int rc = ITS_SUCCESS;
    
    {
        ApplyChargingArg achArg;                                       

        cap_v3::CAMEL_AChBillingChargingCharacteristics achBilling;
    	cap_v3::CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging timeDurCharging;
		try
		{

			timeDurCharging.SetMaxCallPeriodDuration(50);
			timeDurCharging.SetTariffSwitchInterval(1);
			CAMEL_AChBillingChargingCharacteristics::TimeDurationCharging::ReleaseIfdurationExceeded releaseIfDurExceed(false);
			timeDurCharging.SetReleaseIfdurationExceeded(releaseIfDurExceed);


	
			achBilling.SetChoiceTimeDurationCharging((timeDurCharging));
			Octets* achBillingBuf = achBilling.Encode();
	
			AChBillingChargingCharacteristics *AChBilling = new AChBillingChargingCharacteristics((achBillingBuf->GetArray()));
	
			achArg.SetAChBillingChargingCharacteristics((AChBilling));
	
			/* SendingSideID values is set to leg1*/
			byte array[] = { 0x01 };
			LegType* lt = new LegType(ArrayToVector(array, ARRAY_SIZE(array)));
			SendingSideID *sid = new SendingSideID();
			sid->SetChoiceSendingSideID(lt);
			achArg.SetPartyToCharge((SendingSideID*)sid);
	
			if(achBillingBuf != NULL)
			{
				delete achBillingBuf;
				achBillingBuf = NULL;
			}
		if ( itstest::appMode == UNIT_TEST)
			cout<<achArg;

		
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
	}
		catch(AsnEncodeError &exc)
				{
					APP_TRACE_ERROR(("### ASN Encode Error ### <%s>", exc.GetDescription().c_str()));
				}
				catch(...)
				{
					APP_TRACE_ERROR(("Unknown exception thrown"));
				}

    }




    APP_TRACE_DEBUG(("BuildACH -- Exit"));                      

    return rc;
}

int BuildContinue(TCAP_Component *&cpt, bool isSMSIdp)
{
    int rc = ITS_SUCCESS;
    APP_TRACE_DEBUG(("BuildContinue -- Entry"));
    TCAP_Invoke *ivk = new TCAP_Invoke();                                 
    ivk->SetClass(TCAP_OPERATION_CLASS);
	if(true == isSMSIdp)
	{
		APP_TRACE_DEBUG(("BuildContinue:: BuildSMSCont"));
		ivk->SetOperation( cap::OP_continueSMS );
	}
	else
	{
		APP_TRACE_DEBUG(("BuildContinue:: BuildIdpCont"));
		ivk->SetOperation( cap::OP_continue );
	}
    cpt = ivk;   

	
	   //LogCAPAsnObj(achArg, false);
   
    APP_TRACE_DEBUG(("BuildContinue -- Exit"));
    return rc;
}

int BuildRelease(	TCAP_Component *&cpt, byte causecode)
{
    APP_TRACE_DEBUG(("BuildRelease -- Entry"));
    int rc = ITS_SUCCESS;
    byte causeLoc = CAUSE_LOCATION_RLN;
    try
    {

        if( causecode == NORMAL_CALL_CLEARING ) 
        {
            causeLoc = CAUSE_LOCATION_USER;
        }
        byte array[] = {causeLoc, causecode };
        cap_v3::ReleaseCallArg releaseCall(ArrayToVector(array, ARRAY_SIZE(array)));
		cout<<releaseCall;
        Octets* buf = releaseCall.Encode();                                        

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

    }
    catch(AsnEncodeError &exc)
    {

        APP_TRACE_ERROR(("### ASN Encode Error ### <%s>", exc.GetDescription().c_str()));
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        APP_TRACE_ERROR(("Unknown Exception"));
    }
    APP_TRACE_DEBUG(("BuildRelease -- Exit"));
    return rc;

}
int BuildReleaseSMS(TCAP_Component *&cpt, byte causeCode)
{
    APP_TRACE_DEBUG(("BuildReleaseSMS -- Entry"));
    int rc = ITS_SUCCESS;
    try
    {
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
    }
    catch(AsnEncodeError &exc)
    {
        APP_TRACE_DEBUG(("### ASN Encode Error ### <%s>", exc.GetDescription().c_str()));
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        APP_TRACE_DEBUG(("Unknown Exception"));
    }
    APP_TRACE_DEBUG(("BuildReleaseSMS -- Exit"));
    return rc;
}

int BuildConnect(TCAP_Component *&cpt, CalledPartyNumber& destinationAddr)
{
	APP_TRACE_DEBUG(("BuildConnect -- Entry"));
	int rc = ITS_SUCCESS;

	cap_v3::ConnectArg conArg;
	cap_v3::DestinationRoutingAddress destAddr;
	destAddr.AddElement(destinationAddr);
		
	conArg.SetDestinationRoutingAddress(destAddr);
	try
    {
    	Octets* buf = conArg.Encode();
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
        APP_TRACE_DEBUG(("BuildConnect:: ASN Encode Error :  <%s>", exc.GetDescription().c_str()));
        rc = !ITS_SUCCESS;
    }
    catch(...)
    {
        rc = !ITS_SUCCESS;
        APP_TRACE_DEBUG(("Unknown Exception"));
    }
    APP_TRACE_DEBUG(("BuildConnect -- Exit"));
	return rc;
}


