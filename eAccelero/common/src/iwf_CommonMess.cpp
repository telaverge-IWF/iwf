void ShowIwfCapProtoConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfTimersConfig timersconfig;

    if(m_iwfcmapi->GetIwfCapProtoTimers(timersconfig, err) == CMAPI_SUCCESS)
    {
        IwfTimersConfig *TimersConf = &timersconfig;
        unsigned int cap_timers_info = TimersConf->iwftimersinfo_size();
        CLOG_DEBUG(" Cap Timers Size = %d",cap_timers_info);
        if(cap_timers_info)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "IWF-Cap-Proto-Timers Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                    FIELD_DELIMITER,"Name",
                    FIELD_DELIMITER,"Value",ROW_DELIMITER);

            for(unsigned int i = 0; i < cap_timers_info; i++)
            {
                IwfTimerConfig *TimerConf = TimersConf->mutable_iwftimersinfo(i);

        	if(TimerConf->has_timername())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",TimerConf->timername().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

        	if(TimerConf->has_timervalue())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",TimerConf->timervalue(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching IWFCapProtoTimers Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching IWFCapProtoTimers Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);

}

void SetIwfCapProtoConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfTimersConfig TimersConfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }


    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.no_activity_timer != INVALID_NUM)
    {
    	IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int activity_timer = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.no_activity_timer;
        CLOG_DEBUG(" No Activity Timer = %d",activity_timer);
        timerconfig->set_timername(NO_ACTIVITY_TIMER);
        timerconfig->set_timervalue(activity_timer);
    }

    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.retry_count != INVALID_NUM)
    {
    	IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int retry_count = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.retry_count;
        CLOG_DEBUG(" Retry Count = %d",retry_count);
        timerconfig->set_timername(RETRY_COUNT);
        timerconfig->set_timervalue(retry_count);
    }

    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.response_timeout != INVALID_NUM)
    {
    	IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int response_timeout = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.response_timeout;
        CLOG_DEBUG(" Response TimeOut = %d",response_timeout);
        timerconfig->set_timername(RESPONSE_TIMEOUT);
        timerconfig->set_timervalue(response_timeout);
    }

    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.voice_no_answer_timer != INVALID_NUM)
    {
        IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int voice_no_answer_timer = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.voice_no_answer_timer;
        CLOG_DEBUG(" Voice No Answer Timer = %d",voice_no_answer_timer);
        timerconfig->set_timername(VOICE_NO_ANSWER_TIMER);
        timerconfig->set_timervalue(voice_no_answer_timer);
    }

    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.network_delay_timer != INVALID_NUM)
    {
        IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int network_delay_timer = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.network_delay_timer;
        CLOG_DEBUG(" Network Delay Timer = %d",network_delay_timer);
        timerconfig->set_timername(NETWORK_DELAY_TIMER);
        timerconfig->set_timervalue(network_delay_timer);
    }

    if(cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.sms_no_event_timer != INVALID_NUM)
    {
        IwfTimerConfig* timerconfig = TimersConfig.add_iwftimersinfo();
        int sms_no_event_timer = cliReq->IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.sms_no_event_timer;
        CLOG_DEBUG(" SMS NoEvent Timer = %d",sms_no_event_timer);
        timerconfig->set_timername(SMS_NO_EVENT_TIMER);
        timerconfig->set_timervalue(sms_no_event_timer);
    }

    if(m_iwfcmapi->ModifyIwfCapProtoTimers(TimersConfig, &cfgResp) == CMAPI_SUCCESS)
    {
	    CLOG_DEBUG(" Succesfully Modified the Timers Configuration");
	    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
	    CLOG_ERROR("Error in Modifying the Timers Configuration");
	    rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);

}

void SetIWFDccaDestConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfDccaDestsConfig DccaDestsConfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm[0] != INVALID_STR)
    {
        IwfDccaDestConfig *DccaDestConfig = DccaDestsConfig.add_iwfdccadestinfo();
        string dest_realm = cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm;
        CLOG_DEBUG("Dest-Realm = %s",dest_realm.c_str());
        DccaDestConfig->set_destname(dest_realm);
        
        if(cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.sendCCRT != INVALID_NUM)
        {
            int send_ccrt = cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.sendCCRT;
            CLOG_DEBUG("Send CCRT Indicator = %d",send_ccrt);
            DccaDestConfig->set_sendccrtindicator(send_ccrt);
        }
        
        for(int i = 0; i < MAX_DCCA_ENDPOINTS; i++)
        {
            if(cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.endPoint[i][0] != INVALID_STR)
            {
                IwfDccaEndPointConfig *endpointconfig = DccaDestConfig->add_iwfdccaendpoints();
                string endpoint_name  = cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.endPoint[i];
                CLOG_DEBUG(" EndPoint = %s",endpoint_name.c_str());
                endpointconfig->set_endpointname(endpoint_name);

                if(cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.priority[i] != INVALID_NUM)
                {
                    int priority = cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.priority[i];
                    CLOG_DEBUG(" Priority = %d",priority);
                    endpointconfig->set_priority(priority);
                }
            }
        }
    }

    if(cliReq->OP_CODE == MODIFY)
    {
        if(m_iwfcmapi->ModifyIwfDccaDestConfig(DccaDestsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the IWF Dcca Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the IWF Dcca Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == DELETE)
    {
        if(cmdID == C_cli_dcca_dest_realm_config_Id)
        {
            if(m_iwfcmapi->DeleteIwfDccaDestConfig(DccaDestsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the IWF Dcca Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Deleting the IWF Dcca Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->DeleteIwfDccaEndpointConfig(DccaDestsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the IWF Dcca EndPoint Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Deleting the IWF Dcca EndPoint Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }
    else
    {
        if(m_iwfcmapi->AddIwfDccaDestConfig(DccaDestsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the IWF Dcca Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Adding the IWF Dcca Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);

}

void ShowIWFDccaDestConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    SetConfigReq *cliReq = (SetConfigReq *)req;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfDccaDestsConfig DccaDestsConfig;

    if(cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm[0] != INVALID_STR)
    {
        IwfDccaDestConfig *DccaDestConfig = DccaDestsConfig.add_iwfdccadestinfo();
        string dest_realm = cliReq->IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm;
        CLOG_DEBUG("Dest-Realm = %s",dest_realm.c_str());
        DccaDestConfig->set_destname(dest_realm);
    }

    if(m_iwfcmapi->GetIwfDccaDestConfig(DccaDestsConfig, err) == CMAPI_SUCCESS)
    {
        IwfDccaDestsConfig *dccaDestsConf = &DccaDestsConfig;
        int dcca_dest_size = DccaDestsConfig.iwfdccadestinfo_size();
        if(dcca_dest_size)
        {
            for(int j = 0; j < dcca_dest_size; j++)
            {
                IwfDccaDestConfig *DccaConf = dccaDestsConf->mutable_iwfdccadestinfo(j);
                unsigned int endpoint_info = DccaConf->iwfdccaendpoints_size();
                CLOG_DEBUG(" Dcca EndPoint Size = %d",endpoint_info);
                if(endpoint_info)
                {
                    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "IWF-DCCA-Destination Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"EndPoint",
                            FIELD_DELIMITER,"Priority",
                            FIELD_DELIMITER,"SendCCRTIndicator",ROW_DELIMITER);

                    for(unsigned int i = 0; i < endpoint_info; i++)
                    {
                        IwfDccaEndPointConfig *endPointConf = DccaConf->mutable_iwfdccaendpoints(i);

                        if(endPointConf->has_endpointname())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",endPointConf->endpointname().c_str(),FIELD_DELIMITER);
                            if(endPointConf->has_priority())
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",endPointConf->priority(),FIELD_DELIMITER);
                            }
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(DccaConf->has_sendccrtindicator())
                            {
                                if(DccaConf->sendccrtindicator())
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",ROW_DELIMITER);
                                else
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",ROW_DELIMITER);
                            }
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%cNULL%cNULL%c",
                                    FIELD_DELIMITER,FIELD_DELIMITER,ROW_DELIMITER);
                    }
                }
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Dcca Destination Config Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Dcca Destination Config Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void SetIWFDccaGeneralConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    int i=0;

    IWFCfgResp cfgResp;
    IwfDccaGenConfig FeaturesConfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    while(cliReq->IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[i][0] != INVALID_STR)
    {
        IwfDccaFeatureConfig *featureConf = FeaturesConfig.add_iwfdccafeatures();
        string feature_name = cliReq->IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[i];
        CLOG_DEBUG(" Feature Name = %s",feature_name.c_str());
        featureConf->set_dccafeaturename(feature_name);

        if(cliReq->IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[i] != INVALID_NUM)
        {
            int dcca_feature_value = cliReq->IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[i];
            CLOG_DEBUG(" Feature Value = %d",dcca_feature_value);
            featureConf->set_dccavalue(dcca_feature_value);
        }
        i++;
    }

    if(m_iwfcmapi->ModifyIwfDccaGenConfig(FeaturesConfig, &cfgResp) == CMAPI_SUCCESS)
    {
	    CLOG_DEBUG(" Succesfully Modified the IWF Dcca Genereal Configuration");
	    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
	    CLOG_ERROR("Error in Modifying the IWF Dcca General Configuration");
	    rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);

}

void ShowIWFDccaGeneralConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfDccaGenConfig dccaGenConfig;

    if(m_iwfcmapi->GetIwfDccaGenConfig(dccaGenConfig, err) == CMAPI_SUCCESS)
    {
        IwfDccaGenConfig *DccaConf = &dccaGenConfig;
        unsigned int dcca_info = DccaConf->iwfdccafeatures_size();
        CLOG_DEBUG(" Dcca Feature info Size = %d",dcca_info);
        if(dcca_info)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "IWF-DCCA-General Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                    FIELD_DELIMITER,"Tx-TimeOut",
                    FIELD_DELIMITER,"CCFH-Initial-Action",ROW_DELIMITER);

            bool IsValueSet = false;
            //Set Tx-TimeOut
            for(unsigned int i = 0; i < dcca_info; i++)
            {
                IwfDccaFeatureConfig *FeatureConf = DccaConf->mutable_iwfdccafeatures(i);
                if(FeatureConf->has_dccafeaturename() && (FeatureConf->dccafeaturename() == "TX_TIMEOUT") && FeatureConf->has_dccavalue())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",FeatureConf->dccavalue(),FIELD_DELIMITER);
                    IsValueSet = true;
                    break;
                }
            }
            if(!IsValueSet)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
            IsValueSet = false; // Reset the flag

            //Set CCFH-Initial-Action
            for(unsigned int i = 0; i < dcca_info; i++)
            {
                IwfDccaFeatureConfig *FeatureConf = DccaConf->mutable_iwfdccafeatures(i);

                if(FeatureConf->has_dccafeaturename() && (FeatureConf->dccafeaturename() == "INITIAL_ACTION") && FeatureConf->has_dccavalue())
                {
                    int status = FeatureConf->dccavalue();
                    if(status == TERMINATE)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"TERMINATE%c",ROW_DELIMITER);
                    else if(status == CONTINUE)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CONTINUE%c",ROW_DELIMITER);
                    else if(status == RETRY_AND_TERMINATE)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"RETRY_AND_TERMINATE%c",ROW_DELIMITER);
                    IsValueSet = true;
                    break;
                }
            }
            if(!IsValueSet)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }

            IsValueSet = false; //Reset the flag
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Dcca General Config Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Dcca general Config Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void SetIWFFeatureConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfFeaturesConfig FeaturesConfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name[0] != INVALID_STR)
    {
        IwfFeatureConfig *featureConf = FeaturesConfig.add_iwffeatureinfo();
        string feature_name = cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name;
        CLOG_DEBUG(" Feature Name = %s",feature_name.c_str());
        featureConf->set_featurename(feature_name);

        if(cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status != INVALID_NUM)
        {
            int status = cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status;
            CLOG_DEBUG(" Feature Status = %d",status);
            featureConf->set_statusvalue(status);
        }

        if(cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.maxNumberOfCalls != INVALID_NUM)
        {
            IwfFeatureConfig *featureConfig = FeaturesConfig.add_iwffeatureinfo();
            featureConfig->set_featurename("MAX_NUMBER_OF_SESSIONS");
            int64_t numOfcalls = cliReq->IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.maxNumberOfCalls;
            CLOG_DEBUG(" Max Number Of Calls = %lld",numOfcalls);
            featureConfig->set_statusvalue(numOfcalls);
        }
    }

    if(m_iwfcmapi->ModifyIwfFeatures(FeaturesConfig, &cfgResp) == CMAPI_SUCCESS)
    {
	    CLOG_DEBUG(" Succesfully Modified the IWF Features Configuration");
	    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
	    CLOG_ERROR("Error in Modifying the IWF Features Configuration");
	    rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);

}

void ShowIwfFeatureConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    ErrorDetails err;
    IwfFeaturesConfig featuresconfig;

    if(cmdID == C_cli_show_tAns_trigger_config_Id)
    {
        IwfFeatureConfig *featureConf = featuresconfig.add_iwffeatureinfo();
        CLOG_DEBUG(" Feature Name = FOLLOWON_TANS_TRIGGER");
        featureConf->set_featurename("FOLLOWON_TANS_TRIGGER");
    }
    else if(cmdID == C_cli_show_congestion_management_config_Id)
    {
        IwfFeatureConfig *featureConf = featuresconfig.add_iwffeatureinfo();
        CLOG_DEBUG(" Feature Name = CONGESTION_MANAGEMENT");
        featureConf->set_featurename("CONGESTION_MANAGEMENT");
        IwfFeatureConfig *featureConfig = featuresconfig.add_iwffeatureinfo();
        featureConfig->set_featurename("MAX_NUMBER_OF_SESSIONS");
    }

    if(m_iwfcmapi->GetIwfFeatures(featuresconfig, err) == CMAPI_SUCCESS)
    {
        IwfFeaturesConfig *FeaturesConf = &featuresconfig;
        unsigned int feature_info = FeaturesConf->iwffeatureinfo_size();
        CLOG_DEBUG(" Feature info Size = %d",feature_info);
        if(feature_info)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            if(cmdID == C_cli_show_tAns_trigger_config_Id)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "  IWF-Feature-Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",
                        FIELD_DELIMITER,"FollowOn_TAns_Trigger",ROW_DELIMITER);

                for(unsigned int i = 0; i < feature_info; i++)
                {
                    IwfFeatureConfig *FeatureConf = FeaturesConf->mutable_iwffeatureinfo(i);

                    if(FeatureConf->has_statusvalue())
                    {
                        int status = FeatureConf->statusvalue();
                        if(status == ENABLE)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"ENABLE%c",ROW_DELIMITER);
                        else if(status == DISABLE)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"DISABLE%c",ROW_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
            }
            else if(cmdID == C_cli_show_congestion_management_config_Id)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "  IWF-Feature-Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                        FIELD_DELIMITER,"CongestionManagement",
                        FIELD_DELIMITER,"MaxNumOfActiveSessToHold",ROW_DELIMITER);

                for(unsigned int i = 0; i < feature_info; i++)
                {
                    IwfFeatureConfig *FeatureConf = FeaturesConf->mutable_iwffeatureinfo(i);

                    if(FeatureConf->has_featurename() && !(strcasecmp(FeatureConf->featurename().c_str(),"CONGESTION_MANAGEMENT")))
                    {
                        if(FeatureConf->has_statusvalue())
                        {
                            int status = FeatureConf->statusvalue();
                            if(status == ENABLE)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"ENABLE%c",FIELD_DELIMITER);
                            else if(status == DISABLE)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"DISABLE%c",FIELD_DELIMITER);
                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                    }
                    else if(FeatureConf->has_featurename() && !(strcasecmp(FeatureConf->featurename().c_str(),"MAX_NUMBER_OF_SESSIONS")))
                    {
                        if(FeatureConf->has_statusvalue())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%ld%c",FeatureConf->statusvalue(),ROW_DELIMITER);
                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                    }
                }
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Iwf Fetures Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Ief Features Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowLogCdrConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfFeaturesConfig featuresconfig;
    IwfFeatureConfig *featureConf = featuresconfig.add_iwffeatureinfo();
    CLOG_DEBUG(" Feature Name = LOG_CDR");
    featureConf->set_featurename("LOG_CDR");

    if(m_iwfcmapi->GetIwfFeatures(featuresconfig, err) == CMAPI_SUCCESS)
    {
        IwfFeaturesConfig *FeaturesConf = &featuresconfig;
        unsigned int cdr_info = FeaturesConf->iwffeatureinfo_size();
        CLOG_DEBUG(" CDR info Size = %d",cdr_info);
        if(cdr_info)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "  IWF-LOG-CDR Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",
                    FIELD_DELIMITER,"Status",ROW_DELIMITER);

            for(unsigned int i = 0; i < cdr_info; i++)
            {
                IwfFeatureConfig *FeatureConf = FeaturesConf->mutable_iwffeatureinfo(i);

                if(FeatureConf->has_statusvalue())
                {
                    int status = FeatureConf->statusvalue();
                    if(status == DISABLE_ALL_CALLS)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"DISABLE_ALL_CALLS%c",ROW_DELIMITER);
                    else if(status == DISABLE_ONLY_SUCCESS_CALLS)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"DISABLE_ONLY_SUCCESS_CALLS%c",ROW_DELIMITER);
                    else if(status == ENABLE_ONLY_FAILED_CALLS)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"ENABLE_ONLY_FAILED_CALLS%c",ROW_DELIMITER);
                    else if(status == ENABLE_ALL_CALLS)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"ENABLE_ALL_CALLS%c",ROW_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching IWFLogCDR Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching IWFLogCDR Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void SetUALConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranUalManagerConfig ualconfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.ualSetConfigPayload.ualSetConfigInfo.ack_timer != INVALID_NUM)
    {
        int ack_timer = cliReq->IWFPayload.ualSetConfigPayload.ualSetConfigInfo.ack_timer;
        CLOG_DEBUG(" Ack Timer = %d",ack_timer);
        ualconfig.set_acktimer(ack_timer);
    }

    if(cliReq->IWFPayload.ualSetConfigPayload.ualSetConfigInfo.sigtran_mode[0] != INVALID_STR)
    {
        string sigtran_mode = cliReq->IWFPayload.ualSetConfigPayload.ualSetConfigInfo.sigtran_mode;
        CLOG_DEBUG(" SigtranMode = %s",sigtran_mode.c_str());
        ualconfig.set_sigtranmode(sigtran_mode);
    }

    if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetUalConfig(ualconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the UAL Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the UAL Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == MODIFY)
    {
        if(m_iwfcmapi->ModifyUalConfig(ualconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the UAL Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the UAL Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetSCTPEndPointConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IwfSigtranSctpEndPointsConfig sctpEndPointsConfig;
    IwfSigtranSctpEndPointConfig *sctpEndPointConfig = sctpEndPointsConfig.add_sctpendpointinfo();
    IWFCfgResp cfgResp;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    string endpoint = "";
    int port = 0;
    string ipaddr = "";
    string type = "";

    if(cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint[0] != INVALID_STR)
    {
        endpoint  = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint;
        CLOG_DEBUG(" EndPoint = %s", endpoint.c_str());
        sctpEndPointConfig->set_endpointname(endpoint);
    }

    if(cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.port != INVALID_NUM)
    {
        port = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.port;
        CLOG_DEBUG(" Port = %d", port);
        sctpEndPointConfig->set_port(port);
    }

    if(cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.ipaddr[0] != INVALID_STR)
    {
        ipaddr = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.ipaddr;
        CLOG_DEBUG(" IpAddr = %s",ipaddr.c_str());
        sctpEndPointConfig->set_ipaddress(ipaddr);
    }

    if(cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.type[0] != INVALID_STR)
    {
        type = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.type;
        CLOG_DEBUG(" Type = %s", type.c_str());
        sctpEndPointConfig->set_endpointtype(type);
    }

    for(int i = 0; i< MAX_LOCALTRANSPORT_ATTRIBUTES; i++)
    {
        if(cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.secondaryIp[i][0] != INVALID_STR)
        {
            IwfSigtranMultihomingConfig *MultiHoming = sctpEndPointConfig->add_multihominginfo();
            string secondary_Ip = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.secondaryIp[i];
            CLOG_DEBUG("SecondaryIp[%d] = %s",i,secondary_Ip.c_str());
            MultiHoming->set_otheripaddress(secondary_Ip);
        }
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(cmdID == C_cli_delete_sctpendpoint_multihoming_Id)
        {
            if(m_iwfcmapi->DeleteSigtranMultihoming(sctpEndPointsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the SCTP-End-Point's MultiHoming Ip's Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Deleting the SCTP-End-Point's MultiHoming Ip's Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->DeleteIwfSctpEndPoint(sctpEndPointsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the SCTP-End-Point Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Deleting the SCTP-End-Point Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }
    else if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetIwfSctpEndPoint(sctpEndPointsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the SCTP-End-Point Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the SCTP-End-Point Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyIwfSctpEndPoint(sctpEndPointsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the SCTP-End-Point Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the SCTP-End-Point Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetAssociationConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranAssociationsConfig AssociationsConfig;
    IwfSigtranAssociationConfig *AssociationConfig = AssociationsConfig.add_associationinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname[0] != INVALID_STR)
    {
        string association = cliReq->IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname;
        CLOG_DEBUG(" Association = %s",association.c_str());
        AssociationConfig->set_associationname(association);
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.sctp_profile_name[0] != INVALID_STR)
    {
        string sctp_profile = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.sctp_profile_name;
        CLOG_DEBUG(" SCTP-Profile = %s",sctp_profile.c_str());
        IwfSigtranSctpProfileConfig *sctpprofile = AssociationConfig->mutable_sctpprofile();
        sctpprofile->set_sctpprofilename(sctp_profile);
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.association_set[0] != INVALID_STR)
    {
        string assoc_set = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.association_set;
        CLOG_DEBUG(" Association-Set = %s",assoc_set.c_str());
        AssociationConfig->set_associationsetname(assoc_set);
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.local_sctp_end_point[0] != INVALID_STR)
    {
        string local_end_point = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.local_sctp_end_point;
        CLOG_DEBUG(" Local-Sctp-EndPoint = %s",local_end_point.c_str());
        IwfSigtranSctpEndPointConfig *LocalSCTPEndPoint = AssociationConfig->mutable_localendpoint();
        LocalSCTPEndPoint->set_endpointname(local_end_point);
        LocalSCTPEndPoint->set_endpointtype("LOCAL");
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.remote_sctp_end_point[0] != INVALID_STR)
    {
        string remote_end_point = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.remote_sctp_end_point;
        CLOG_DEBUG(" Remote-Sctp-EndPoint = %s",remote_end_point.c_str());
        IwfSigtranSctpEndPointConfig *RemoteSCTPEndPoint = AssociationConfig->mutable_remoteendpoint();
        RemoteSCTPEndPoint->set_endpointname(remote_end_point);
        RemoteSCTPEndPoint->set_endpointtype("REMOTE");
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.aspId != INVALID_NUM)
    {
        int aspId = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.aspId;
        AssociationConfig->set_aspid(aspId);
        CLOG_DEBUG(" AspId = %d",aspId);
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteAssociation(AssociationsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetAssociation(AssociationsConfig, &cfgResp) == CMAPI_SUCCESS)
        {

            CLOG_DEBUG(" Succesfully Added the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyAssociation(AssociationsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the Association Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}
void SetAssociationSetConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranAssociationSetsConfig AssociationSetsConfig;
    IwfSigtranAssociationSetConfig *AssociationSetConfig = AssociationSetsConfig.add_associationsetinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname[0] != INVALID_STR)
    {
        string assocset = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname;
        CLOG_DEBUG(" AssociationSet = %s", assocset.c_str());
        AssociationSetConfig->set_associationsetname(assocset);
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteAssociationSet(AssociationSetsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the Association Set Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the Association Set Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.family[0] != INVALID_STR)
        {
            //NOT THERE IN PROTOCOL BUFFER
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.ni != INVALID_NUM)
        {
            int Ni = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.ni;
            CLOG_DEBUG(" Network Indicator = %d",Ni);
            AssociationSetConfig->set_networkindicator(Ni);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.pointcode != INVALID_NUM)
        {
            int pointcode = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.pointcode;
            CLOG_DEBUG(" Adj-PointCode = %d",pointcode);
            AssociationSetConfig->set_adjacenpointcode(pointcode);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.routing_key != INVALID_NUM)
        {
            int routing_key = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.routing_key;
            CLOG_DEBUG(" Routing Context = %d",routing_key);
            AssociationSetConfig->set_routingcontext(routing_key);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.traffic_mode[0] != INVALID_STR)
        {
            string traffic_mode = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.traffic_mode;
            CLOG_DEBUG(" TrafficMode = %s",traffic_mode.c_str());
            AssociationSetConfig->set_trafficmode(traffic_mode);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.asp_id != INVALID_NUM)
        {
            int asp_id = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.asp_id;
            CLOG_DEBUG(" ASP Id = %d",asp_id);
            AssociationSetConfig->set_aspid(asp_id);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.isMember != INVALID_NUM)
        {
            int isMember = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.isMember;
            CLOG_DEBUG(" IsMember = %d",isMember);
            AssociationSetConfig->set_ismember(isMember);
        }

        if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.homeIp[0] != INVALID_STR)
        {
            string homeIp = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.homeIp;
            CLOG_DEBUG(" HomeIp = %d",homeIp.c_str());
            AssociationSetConfig->set_homeip(homeIp);
        }

        if(cliReq->OP_CODE == ADD)
        {
            if(m_iwfcmapi->SetAssociationSet(AssociationSetsConfig, &cfgResp) == CMAPI_SUCCESS)
            {

                CLOG_DEBUG(" Succesfully Added the Association Set Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Setting the Association Set Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->ModifyAssociationSet(AssociationSetsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Modified the Association Set Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Modifying the Association Set Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetSCTPProfileConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranSctpProfilesConfig SctpProfilesConfig;
    IwfSigtranSctpProfileConfig *sctpprofileconfig = SctpProfilesConfig.add_sctpprofileinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }


    if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename[0] != INVALID_STR)
    {
        string sctpprofile = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename;
        CLOG_DEBUG(" SCTP-Profile = %s",sctpprofile.c_str());
        sctpprofileconfig->set_sctpprofilename(sctpprofile);
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteSctpProfile(SctpProfilesConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the SCTP Profile Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the SCTP Profile Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeat != INVALID_NUM)
        {
            int heartbeat = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeat;
            CLOG_DEBUG(" HeartBeat = %d",heartbeat);
            sctpprofileconfig->set_heartbeatenable(heartbeat);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeattimeout != INVALID_NUM)
        {
            int heartbeattimeout = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeattimeout;
            CLOG_DEBUG(" HeartBeat-TimeOut = %d",heartbeattimeout);
            sctpprofileconfig->set_heartbeattimeout(heartbeattimeout);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.inittimeout != INVALID_NUM)
        {
            int inittimeout = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.inittimeout;
            CLOG_DEBUG(" Init-Timeout = %d",inittimeout);
            sctpprofileconfig->set_inittimeout(inittimeout);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxattempts != INVALID_NUM)
        {
            int maxattempts = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxattempts;
            CLOG_DEBUG(" Max Attempts = %d",maxattempts);
            sctpprofileconfig->set_maxattempt(maxattempts);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.assocmaxattempts != INVALID_NUM)
        {
            int assocmaxattempts = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.assocmaxattempts;
            CLOG_DEBUG(" Max Assoc Attempts = %d",assocmaxattempts);
            sctpprofileconfig->set_assocmaxattempt(assocmaxattempts);
        }
#if 0
        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathfailureretrycount != INVALID_NUM)
        {
            int pathfailureretrycount = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathfailureretrycount;
            CLOG_DEBUG(" Path Failure Retry Count = %d",pathfailureretrycount);
            sctpprofileconfig->set_pathfailureretrycount(pathfailureretrycount);
        }
#endif
        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtoinit != INVALID_NUM)
        {
            int rtoinit = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtoinit;
            CLOG_DEBUG(" Rto Initial = %d",rtoinit);
            sctpprofileconfig->set_rtoinitial(rtoinit);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomin != INVALID_NUM)
        {
            int rtomin = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomin;
            CLOG_DEBUG(" Rto Minimum = %d",rtomin);
            sctpprofileconfig->set_rtomin(rtomin);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomax != INVALID_NUM)
        {
            int rtomax = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomax;
            CLOG_DEBUG(" Rto Maximum = %d",rtomax);
            sctpprofileconfig->set_rtomax(rtomax);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathmaxretransmit != INVALID_NUM)
        {
            int pathmaxretransmit = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathmaxretransmit;
            CLOG_DEBUG(" Path Max Retransmit = %d",pathmaxretransmit);
            sctpprofileconfig->set_pathfailureretrycount(pathmaxretransmit);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivetimeout != INVALID_NUM)
        {
            int receivetimeout = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivetimeout;
            CLOG_DEBUG(" ReceiveTimeOut = %d",receivetimeout);
            sctpprofileconfig->set_receivetimeout(receivetimeout);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.shutdowntimeout != INVALID_NUM)
        {
            int shutdowntimeout = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.shutdowntimeout;
            CLOG_DEBUG(" ShutDownTimeOut = %d",shutdowntimeout);
            sctpprofileconfig->set_shutdowntimeout(shutdowntimeout);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.reconnecttimeout != INVALID_NUM)
        {
            int reconnecttimeout = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.reconnecttimeout;
            CLOG_DEBUG(" ReconnectTimeOut = %d",reconnecttimeout);
            sctpprofileconfig->set_reconnecttimeout(reconnecttimeout);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivebuffsize != INVALID_NUM)
        {
            int recvbuffsize = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivebuffsize;
            CLOG_DEBUG(" RecvBuffSize = %d",recvbuffsize);
            sctpprofileconfig->set_recvbufsize(recvbuffsize);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sendbuffsize != INVALID_NUM)
        {
            int sendbuffsize = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sendbuffsize;
            CLOG_DEBUG(" SendBuffSize = %d",sendbuffsize);
            sctpprofileconfig->set_sendbufsize(sendbuffsize);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.cookielife != INVALID_NUM)
        {
            int cookielife = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.cookielife;
            CLOG_DEBUG(" Cookielife = %d",cookielife);
            sctpprofileconfig->set_cookielife(cookielife);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sackdelay != INVALID_NUM)
        {
            int sackdelay = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sackdelay;
            CLOG_DEBUG(" SackDelay = %d",sackdelay);
            sctpprofileconfig->set_sackdelay(sackdelay);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxinstreams != INVALID_NUM)
        {
            int maxinstreams = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxinstreams;
            CLOG_DEBUG(" MaxInstreams = %d",maxinstreams);
            sctpprofileconfig->set_maxinstreams(maxinstreams);
        }

        if(cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.numofoutstreams != INVALID_NUM)
        {
            int numoutstreams = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.numofoutstreams;
            CLOG_DEBUG(" NumofOutstreams = %d",numoutstreams);
            sctpprofileconfig->set_numoutstreams(numoutstreams);
        }

        if(cliReq->OP_CODE == ADD)
        {
            if(m_iwfcmapi->SetSctpProfile(SctpProfilesConfig, &cfgResp) == CMAPI_SUCCESS)
            {

                CLOG_DEBUG(" Succesfully Added the SCTP Profile Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Setting the SCTP Profile Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->ModifySctpProfile(SctpProfilesConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Modified the SCTP Profile Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Modifying the SCTP Profile Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }
    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetRemoteRouteConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranRemoteRoutesConfig RemoteRoutesConfig;
    IwfSigtranRemoteRouteConfig *remoterouteconfig = RemoteRoutesConfig.add_remoterouteinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }
    string remoteroute = "";
    string association_set = "";
    string destination = "";
    int priority = 0;

    if(cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name[0] != INVALID_STR)
    {
        remoteroute = cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name;
        CLOG_DEBUG("  RemoteRoute = %s",remoteroute.c_str());
        remoterouteconfig->set_remoteroutename(remoteroute);
    }

    if(cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.assocsetname[0] != INVALID_STR)
    {
        association_set = cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.assocsetname;
        CLOG_DEBUG("  AssociationSet = %s",association_set.c_str());
        remoterouteconfig->set_associationsetname(association_set);
    }

    if(cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.dest_name[0] != INVALID_STR)
    {
        destination = cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.dest_name;
        CLOG_DEBUG("  Destination = %s", destination.c_str());
        IwfSigtranDestinationConfig *destinationconfig = remoterouteconfig->mutable_destinationinfo();
        destinationconfig->set_destinationname(destination);
    }

    if(cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.priority != INVALID_NUM)
    {
        priority = cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.priority;
        CLOG_DEBUG("  Priority = %d",priority);
        remoterouteconfig->set_priority(priority);
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteRemoteRoute(RemoteRoutesConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetRemoteRoute(RemoteRoutesConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyRemoteRoute(RemoteRoutesConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the Remote Route Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetCAPRoIDPSMSConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfCapToRoConfig captoroconfig;
    CapRoIdpSmsConfig *idpsmsconfig = captoroconfig.mutable_caproidpsmsinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }
    string translator = "";
    int smsNode = 0;
    string clientAddr ="";
    int replyPathReq = 0;
    string sccpAddr = "";
    int msc_srvc_type = 0;
    int sgsn_srvc_type = 0;
    string service_ctxt_id = "";

    IwfTranslatorConfig *translatorconfig = captoroconfig.mutable_translatorinfo();
    translatorconfig->set_translatorname("CAP-Ro");
    CLOG_DEBUG(" Translator = CAP-Ro");

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sms_node != INVALID_NUM)
    {
        smsNode = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sms_node;
        CLOG_DEBUG(" SMS-Node = %d", smsNode);
        idpsmsconfig->set_smsnode(smsNode);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.client_addr[0] != INVALID_STR)
    {
        clientAddr = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.client_addr;
        CLOG_DEBUG(" ClientAddr = %s",clientAddr.c_str());
        idpsmsconfig->set_clientaddress(clientAddr);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.service_context_id[0] != INVALID_STR)
    {
        service_ctxt_id = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.service_context_id;
        CLOG_DEBUG(" Service Context Id = %s",service_ctxt_id.c_str());
        idpsmsconfig->set_servicecontextid(service_ctxt_id);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.originator_sccp_addr[0] != INVALID_STR)
    {
        sccpAddr = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.originator_sccp_addr;
        CLOG_DEBUG(" Orginator-SCCP-Addr = %s",sccpAddr.c_str());
        idpsmsconfig->set_originatorsccpaddress(sccpAddr);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.reply_path_request != INVALID_NUM)
    {
        replyPathReq = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.reply_path_request;
        CLOG_DEBUG(" Reply Path Request = %d",replyPathReq);
        idpsmsconfig->set_replypathrequested(replyPathReq);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.msc_service_specific_type != INVALID_NUM)
    {
        msc_srvc_type = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.msc_service_specific_type;
        CLOG_DEBUG(" MSC Service Spec Type = %d",msc_srvc_type);
        idpsmsconfig->set_mscservicespecifictype(msc_srvc_type);
    }

    if(cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sgsn_service_specific_type != INVALID_NUM)
    {
        sgsn_srvc_type = cliReq->IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sgsn_service_specific_type;
        CLOG_DEBUG(" SGSN Service Spec Type = %d",sgsn_srvc_type);
        idpsmsconfig->set_sgsnservicespecifictype(sgsn_srvc_type);
    }

    if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetCapRoTranslationData(captoroconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the CAP_Ro-IDPSMS Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the CAP_Ro-IDPSMS Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyCapRoTranslationData(captoroconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the CAP_Ro-IDPSMS Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the CAP_Ro-IDPSMS Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}


void SetCAPRoIDPConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfCapToRoConfig captoroconfig;
    CapRoIdpConfig *idpconfig = captoroconfig.mutable_caproidpinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    string translator = "";
    string sip_method = "";
    int node_functionality = 0;
    string org_ioi = "";
    string term_ioi = "";
    string service_ctxt_id = "";
    string cause_code = "";
    int msc_srvc_type = 0;
    int gmsc_srvc_type = 0;
    int cpc_srvc_type = 0;
    int ext_tele_srvc_count = 0;
    int ext_tele_srvc = 0;
    int tele_srvc_id = 0;
    int ext_bearer_srvc_count = 0;
    int ext_bearer_srvc = 0;
    int bearer_srvc_id = 0;
    int multi_service_indicator = 0;

    IwfTranslatorConfig *translatorconfig = captoroconfig.mutable_translatorinfo();
    translatorconfig->set_translatorname("CAP-Ro");
    CLOG_DEBUG(" Translator = CAP-Ro");

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.node_functionality != INVALID_NUM)
    {
        node_functionality = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.node_functionality;
        CLOG_DEBUG(" Node Functionality = %d",node_functionality);
        idpconfig->set_nodefunctionality(node_functionality);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.sip_method[0] != INVALID_STR)
    {
        sip_method = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.sip_method;
        CLOG_DEBUG(" Sip Method = %s",sip_method.c_str());
        idpconfig->set_sipmethod(sip_method);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.originating_ioi[0] != INVALID_STR)
    {
        org_ioi = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.originating_ioi;
        CLOG_DEBUG(" Originating IOI = %s",org_ioi.c_str());
        idpconfig->set_orignatingtoi(org_ioi);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.terminating_ioi[0] != INVALID_STR)
    {
        term_ioi = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.terminating_ioi;
        CLOG_DEBUG(" Terminating IOI = %s",term_ioi.c_str());
        idpconfig->set_terminatingtoi(term_ioi);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.service_context_id[0] != INVALID_STR)
    {
        service_ctxt_id = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.service_context_id;
        CLOG_DEBUG(" Service Context Id = %s",service_ctxt_id.c_str());
        idpconfig->set_servicecontextid(service_ctxt_id);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cause_code[0] != INVALID_STR)
    {
        cause_code = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cause_code;
        CLOG_DEBUG(" Cause Code = %s",cause_code.c_str());
        idpconfig->set_causecode(cause_code);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.msc_service_specific_type != INVALID_NUM)
    {
        msc_srvc_type = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.msc_service_specific_type;
        CLOG_DEBUG(" MSC Service Specific Type = %d",msc_srvc_type);
        idpconfig->set_mscservicespecfictype(msc_srvc_type);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.gmsc_service_specific_type != INVALID_NUM)
    {
        gmsc_srvc_type = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.gmsc_service_specific_type;
        CLOG_DEBUG(" GMSC Service Specific Type = %d",gmsc_srvc_type);
        idpconfig->set_gmscservicespecifictype(gmsc_srvc_type);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cpc_service_specific_type != INVALID_NUM)
    {
        cpc_srvc_type = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cpc_service_specific_type;
        CLOG_DEBUG(" CPC Service Specific Type = %d",cpc_srvc_type);
        idpconfig->set_cpcservicespecifictype(cpc_srvc_type);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator != INVALID_NUM)
    {
        multi_service_indicator = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator;
        CLOG_DEBUG(" Multi Service Indicator = %d",multi_service_indicator);
        idpconfig->set_multipleserviceindicator(multi_service_indicator);
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service_map_count != INVALID_NUM)
    {
        ext_tele_srvc_count = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service_map_count;
        CLOG_DEBUG(" Ext_Tele_Service_Count = %d", ext_tele_srvc_count);

        for (int i = 0; i < ext_tele_srvc_count; i++)
        {
            ExtTeleServiceConfig *exttelesrvcconfig = idpconfig->add_extteleinfo();

            if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service[i] != INVALID_NUM)
            {
                ext_tele_srvc = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service[i];
                CLOG_DEBUG(" Ext_Tele_Srvc[%d] = %d",i,ext_tele_srvc);
                exttelesrvcconfig->set_extteleservicecode(ext_tele_srvc);
            }
            if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.tele_service_id[i] != INVALID_NUM)
            {
                tele_srvc_id = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.tele_service_id[i];
                CLOG_DEBUG(" Tele_Srvc_Id[%d] = %d",i,tele_srvc_id);
                exttelesrvcconfig->set_serviceid(tele_srvc_id);
            }
        }
    }

    if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service_map_count != INVALID_NUM)
    {
        ext_bearer_srvc_count = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service_map_count;
        CLOG_DEBUG(" Ext_Tele_Service_Count = %d", ext_bearer_srvc_count);

        for (int i = 0; i < ext_bearer_srvc_count; i++)
        {
            ExtBearerServiceConfig *extbearersrvcconfig = idpconfig->add_extbearerinfo();

            if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service[i] != INVALID_NUM)
            {
                ext_bearer_srvc = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service[i];
                CLOG_DEBUG(" Ext_Bearer_Srvc[%d] = %d",i,ext_bearer_srvc);
                extbearersrvcconfig->set_extbearerservicecode(ext_bearer_srvc);
            }
            if(cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.bearer_service_id[i] != INVALID_NUM)
            {
                bearer_srvc_id = cliReq->IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.bearer_service_id[i];
                CLOG_DEBUG(" Bearer_Srvc_Id[%d] = %d",i,bearer_srvc_id);
                extbearersrvcconfig->set_serviceid(bearer_srvc_id);
            }
        }
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteCapRoTranslationData(captoroconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetCapRoTranslationData(captoroconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyCapRoTranslationData(captoroconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the CAP_Ro-IDP Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void ClearSessionContext(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;

    if(cliReq->IWFPayload.ImsiForSessionClearance[0] != INVALID_STR)
    {
        string imsi = cliReq->IWFPayload.ImsiForSessionClearance;
        CLOG_DEBUG("Imsi for Session Clearance = %s",imsi.c_str());
        if(m_iwfcmapi->ClearSessionContext(imsi, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Cleared SessionContext");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Clearing the SessionContext");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetMAPS6aConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfMapToS6aConfig maptos6aconfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    IwfTranslatorConfig *translatorconfig = maptos6aconfig.mutable_translatorinfo();
    translatorconfig->set_translatorname("MAP-s6a");
    CLOG_DEBUG("Translator = MAP-s6a");

    if(cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.hlr_number[0] != INVALID_STR)
    {
        string hlr_num = cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.hlr_number;
        maptos6aconfig.set_hlrnumber(hlr_num);
        CLOG_DEBUG("Hlr-Num = %s",hlr_num.c_str());
    }

    if(cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count != INVALID_NUM)
    {
        int vplmn_id_count = cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count;
        for(int i = 0; i<vplmn_id_count; i++)
        {
            IwfMapToS6aVplmnIdConfig *VplmnIdConfig = maptos6aconfig.add_maptos6avplmnidinfo();
            if(cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[i][0] != INVALID_STR)
            {
                string vplmn_id = cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[i];
                VplmnIdConfig->set_allowedvplmnid(vplmn_id);
                CLOG_DEBUG("Allowed-VplmnId = %s", vplmn_id.c_str());
                int j = 0;
                while(cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.sgsn_number[i][j][0] != INVALID_STR)
                {
                    SgsnNumbers *SgsnInfo = VplmnIdConfig->add_sgsnnumberinfo();
                    string sgsn_num = cliReq->IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.sgsn_number[i][j];
                    SgsnInfo->set_sgsnnumber(sgsn_num);
                    CLOG_DEBUG("Sgsn-Num = %s",sgsn_num.c_str());
                    j++;
                }
            }
        }
    }

    if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetMapS6aTranslationData(maptos6aconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the MAP-S6a Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the MAP-S6a Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == DELETE)
    {
	    if(cmdID == C_cli_map_s6a_vplmn_config_Id)
	    {
		    if(m_iwfcmapi->DeleteMapS6aVplmnIdData(maptos6aconfig, &cfgResp) == CMAPI_SUCCESS)
		    {
			    CLOG_DEBUG(" Succesfully Deleted the MAP-S6a Allowed-Vplmn Data Configuration");
			    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
		    }
		    else
		    {
			    CLOG_ERROR("Error in Deleting the MAP-S6a Allowed-Vplmn Data Configuration");
			    rsp->ResponseCode = IWF_CONFIG_ERROR;
		    }
	    }
	    else if(cmdID == C_cli_map_s6a_vplmn_sgsn_config_Id)
	    {
		    if(m_iwfcmapi->DeleteMapS6aVplmnIdSgsnMapData(maptos6aconfig, &cfgResp) == CMAPI_SUCCESS)
		    {
			    CLOG_DEBUG(" Succesfully Deleted the MAP-S6a VplmnId-Sgsn Map Configuration");
			    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
		    }
		    else
		    {
			    CLOG_ERROR("Error in Deleting the MAP-S6a VplmnId-Sgsn Map Configuration");
			    rsp->ResponseCode = IWF_CONFIG_ERROR;
		    }

	    }
	    else
	    {
		    if(m_iwfcmapi->DeleteMaps6aTranslationData(maptos6aconfig, &cfgResp) == CMAPI_SUCCESS)
		    {
			    CLOG_DEBUG(" Succesfully Deleted the MAP-S6a Configuration");
			    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
		    }
		    else
		    {
			    CLOG_ERROR("Error in Deleting the MAP-S6a Configuration");
			    rsp->ResponseCode = IWF_CONFIG_ERROR;
		    }
	    }
    }
    else
    {
        if(m_iwfcmapi->ModifyMapS6aTranslationData(maptos6aconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the MAP-S6a Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the MAP-S6a Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}


void SetS6aMAPConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfS6aToMapConfig s6atomapconfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    IwfTranslatorConfig *translatorconfig = s6atomapconfig.mutable_translatorinfo();
    translatorconfig->set_translatorname("s6a-MAP");
    CLOG_DEBUG("Translator = s6a-MAP");

    if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.local_sgsn_num[0] != INVALID_STR)
    {
        string sgsn_num = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.local_sgsn_num;
        CLOG_DEBUG(" Local-SGSN-NUM = %s",sgsn_num.c_str());
        s6atomapconfig.set_sgsnnumber(sgsn_num);
    }

    if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.routing_prefix[0] != INVALID_STR)
    {
        string routing_prefix = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.routing_prefix;
        CLOG_DEBUG(" RoutingPrefix = %s",routing_prefix.c_str());
        s6atomapconfig.set_routingprefix(routing_prefix);
    }

    if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_addr_map_count != INVALID_NUM)
    {
        int sgsn_addr_map_count = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_addr_map_count;
        CLOG_DEBUG(" sgsn_addr_map_count = %d",sgsn_addr_map_count);
        for(int i = 0; i < sgsn_addr_map_count; i++)
        {
            SgsnAddresses *sgsnaddr = s6atomapconfig.add_sgsnaddress();
            string org_host = "";
            string ip_addr = "";

            if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.org_host[i][0] != INVALID_STR)
            {
                org_host = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.org_host[i];
                sgsnaddr->set_orginhost(org_host);
                CLOG_DEBUG(" Org-Host[%d] = %s",i,org_host.c_str());
            }

            if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.ip_addr[i][0] != INVALID_STR)
            {
                ip_addr = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.ip_addr[i];
                sgsnaddr->set_ipaddress(ip_addr);
                CLOG_DEBUG(" Ip-Addr[%d] = %s",i,ip_addr.c_str());
            }
        }
    }

    if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix_map_count != INVALID_NUM)
    {
        int sgsn_prefix_map_count = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix_map_count;
        CLOG_DEBUG(" sgsn_prefix_map_count = %d",sgsn_prefix_map_count);
        for(int i = 0; i < sgsn_prefix_map_count; i++)
        {
            SgsnPrefixesConfig *sgsnprefix = s6atomapconfig.add_sgsnprefixconf();
            string vplmnid = "";
            string sgsn_prefix = "";

            if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.vplmnId[i][0] != INVALID_STR)
            {
                vplmnid = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.vplmnId[i];
                sgsnprefix->set_vplmnid(vplmnid);
                CLOG_DEBUG(" VplmnId[%d] = %s",i,vplmnid.c_str());
            }

            if(cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix[i][0] != INVALID_STR)
            {
                sgsn_prefix = cliReq->IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix[i];
                sgsnprefix->set_sgsnprefix(sgsn_prefix);
                CLOG_DEBUG(" SgsnPrefix[%d] = %s",i,sgsn_prefix.c_str());
            }
        }
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteS6aMapTranslationData(s6atomapconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Deleted the SGSN-Addr-Map Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Deleting the SGSN-Addr-Map Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else if(cliReq->OP_CODE == ADD)
    {
        if(m_iwfcmapi->SetS6aMapTranslationData(s6atomapconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the S6a-MAP Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Setting the S6a-MAP Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(m_iwfcmapi->ModifyS6aMapTranslationData(s6atomapconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the S6a-MAP Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in Modifying the S6a-MAP Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}


void SetTranslatorRule(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    IWFCfgResp cfgResp;
    IwfTranslatorRulesConfig transrulesconfig;
    IwfTranslatorRuleConfig *transrule = transrulesconfig.add_ruleinfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }
    string rulename = "";
    string trans_type = "";
    string translator = "";
    string ossn = "";
    string dssn = "";
    string app_id = "";
    string destination = "";
    string mcc = "";
    string mnc = "";
    string web_service = "";
    string http_url = "";
    string dest_host = "";
    string alt_host = "";
    string alt_realm = "";

    if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name[0] != INVALID_STR)
    {
        rulename = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name;
        CLOG_DEBUG("Translator Rule = %s",rulename.c_str());
        transrule->set_translatorrulename(rulename);
    }
    CLOG_DEBUG("Trans Rules Size = %d",transrulesconfig.ruleinfo_size());
    if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id_count != INVALID_NUM)
    {
        int count = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id_count;
        for(int i = 0; i < count; i++)
        {
            if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id[i][0] != INVALID_STR)
            {
                IwfVplmnIdConfig* vplmninfo = transrule->add_vplmninfo();
                string vplmn_id = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id[i];
                CLOG_DEBUG("Allowed-Vplmn-Id = %s",vplmn_id.c_str());
                vplmninfo->set_allowedvplmnid(vplmn_id);
            }
        }
    }


    if(cliReq->OP_CODE == DELETE)
    {
	    if(cmdID == C_cli_translation_vplmn_Id)
	    {
		    if(m_iwfcmapi->DeleteTranslatorVplmnIds(transrulesconfig, &cfgResp) == CMAPI_SUCCESS)
		    {
			    CLOG_DEBUG(" Succesfully deleted Vplmn-Id from translator rule Configuration");
			    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
		    }
		    else
		    {
			    CLOG_ERROR("Error in deleting Vplmn-Id from translator rule Configuration");
			    rsp->ResponseCode = IWF_CONFIG_ERROR;
		    }
	    }
	    else
	    {

		    if(m_iwfcmapi->DeleteTranslatorRules(transrulesconfig, &cfgResp) == CMAPI_SUCCESS)
		    {
			    CLOG_DEBUG(" Succesfully deleted translator rule Configuration");
			    rsp->ResponseCode = IWF_CONFIG_SUCCESS;
		    }
		    else
		    {
			    CLOG_ERROR("Error in deleting translator rule Configuration");
			    rsp->ResponseCode = IWF_CONFIG_ERROR;
		    }
	    }
    }
    else
    {
        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translation_type[0] != INVALID_STR)
        {
            trans_type = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translation_type;
            CLOG_DEBUG("Translator Type = %s",trans_type.c_str());
            IwfTranslatorType *translatortype = transrule->mutable_translatortype();
            translatortype->set_translatortypename(trans_type);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator[0] != INVALID_STR)
        {
            translator = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator;
            CLOG_DEBUG("Translator = %s",translator.c_str());
            IwfTranslatorConfig *translatorconfig = transrule->mutable_translatorinfo();
            translatorconfig->set_translatorname(translator);
            string app_id = "";
            if(!strcmp(translator.c_str(),"s6a-MAP") || !strcmp(translator.c_str(),"MAP-s6a"))
            {
                app_id = S6A_APPID;
                transrule->set_appid(app_id);
            }
            else if(!strcmp(translator.c_str(),"CAP-Ro") || !strcmp(translator.c_str(),"CAP-Ro-TSL"))
            {
                app_id = RO_APPID;
                transrule->set_appid(app_id);
            }
            CLOG_DEBUG("App-Id = %s", app_id.c_str());
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination[0] != INVALID_STR)
        {
            destination = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination;
            CLOG_DEBUG("Destination = %s",destination.c_str());
            transrule->set_destinationname(destination);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dest_host[0] != INVALID_STR)
        {
            dest_host = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dest_host;
            CLOG_DEBUG("Destination Host = %s",dest_host.c_str());
            transrule->set_destinationhost(dest_host);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_realm[0] != INVALID_STR)
        {
            alt_realm = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_realm;
            CLOG_DEBUG("Alternate Realm/Destination = %s",alt_realm.c_str());
            transrule->set_alternaterealm(alt_realm);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_host[0] != INVALID_STR)
        {
            alt_host = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_host;
            CLOG_DEBUG("Alternate Destination Host = %s",alt_host.c_str());
            transrule->set_alternatehost(alt_host);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mcc[0] != INVALID_STR)
        {
            mcc = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mcc;
            CLOG_DEBUG("MCC = %s",mcc.c_str());
            transrule->set_mcc(mcc);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mnc[0] != INVALID_STR)
        {
            mnc = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mnc;
            CLOG_DEBUG("MNC = %s",mnc.c_str());
            transrule->set_mnc(mnc);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.app_id[0] != INVALID_STR)
        {
            app_id = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.app_id;
            string appid = "";
            if(!strcmp(app_id.c_str(),"S6a"))
            {
                appid = S6A_APPID;
                transrule->set_appid(appid);
            }
            else if(!strcmp(app_id.c_str(),"Ro"))
            {
                appid = RO_APPID;
                transrule->set_appid(appid);
            }
            CLOG_DEBUG("App-Id = %s - %s",app_id.c_str(),appid.c_str());
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn[0] != INVALID_STR)
        {
            ossn = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn;
            CLOG_DEBUG("Ossn = %s",ossn.c_str());
            if(!strcmp(ossn.c_str(),"HLR"))
                transrule->set_ossn(HLR);
            else if(!strcmp(ossn.c_str(),"SGSN"))
                transrule->set_ossn(SGSN);
            else if(!strcmp(ossn.c_str(),"CAP"))
                transrule->set_ossn(CAP);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dssn[0] != INVALID_STR)
        {
            dssn = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dssn;
            CLOG_DEBUG("Dssn = %s",dssn.c_str());
            if(!strcmp(dssn.c_str(),"HLR"))
                transrule->set_dssn(HLR);
            else if(!strcmp(dssn.c_str(),"SGSN"))
                transrule->set_dssn(SGSN);
            else if(!strcmp(dssn.c_str(),"CAP"))
                transrule->set_dssn(CAP);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.http_url[0] != INVALID_STR)
        {
            http_url = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.http_url;
            transrule->set_httpurl(http_url);
            CLOG_DEBUG("Http-Url = %s",http_url.c_str());
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.web_service[0] != INVALID_STR)
        {
            web_service = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.web_service;
            CLOG_DEBUG("web_service = %s",web_service.c_str());
            transrule->set_webservice(web_service);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined != INVALID_NUM)
        {
            int range = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined;
            CLOG_DEBUG("Range Defined = %d",range);
            transrule->set_isservicekeyinrange(range);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_start_value != INVALID_NUM)
        {
            unsigned int service_key_start_value = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_start_value;
            CLOG_DEBUG("service_key_start_value = %d",service_key_start_value);
            transrule->set_servicekeystartvalue(service_key_start_value);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_end_value != INVALID_NUM)
        {
            unsigned int service_key_end_value = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_end_value;
            CLOG_DEBUG("service_key_end_value = %d",service_key_end_value);
            transrule->set_servicekeyendvalue(service_key_end_value);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.calling_gt_address_digits[0] != INVALID_STR)
        {
            string addr_digits = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.calling_gt_address_digits;
            CLOG_DEBUG("Calling GT Addr Digits = %s",addr_digits.c_str());
            transrule->set_callinggtaddrdigits(addr_digits);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceContextId[0] != INVALID_STR)
        {
            string servicecontextid = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceContextId;
            CLOG_DEBUG("ServiceContextId = %s",servicecontextid.c_str());
            transrule->set_servicecontextid(servicecontextid);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.imsiPrefix[0] != INVALID_STR)
        {
            string imsiPrefix = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.imsiPrefix;
            CLOG_DEBUG("IMSI Prefix = %s",imsiPrefix.c_str());
            transrule->set_imsiprefix(imsiPrefix);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey[0] != INVALID_STR)
        {
            string serviceKey = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey;
            CLOG_DEBUG("serviceKey = %s",serviceKey.c_str());
            transrule->set_servicekey(serviceKey);
        }

        if(cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.proActionRule[0] != INVALID_STR)
        {
            string proActionRule = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.proActionRule;
            CLOG_DEBUG("ProActionRule = %s",proActionRule.c_str());
            transrule->set_proactionrulename(proActionRule);
        }

        if(cliReq->OP_CODE == ADD)
        {
            if(m_iwfcmapi->SetTranslatorRules(transrulesconfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Added the Translator Rule Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Setting the Translator Rule Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->ModifyTranslatorRules(transrulesconfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Modified the TranslatorRule Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Modifying the TranslatorRule Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}
void SetDestinationConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    IWFCfgResp cfgResp;
    IwfSigtranDestinationsConfig DestinationsConfig;
    IwfSigtranDestinationConfig *DestinationConfig = DestinationsConfig.add_destioninfo();

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name[0] != INVALID_STR)
    {
        string dest = cliReq->IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name;
        CLOG_DEBUG(" Destination = %s",dest.c_str());
        DestinationConfig->set_destinationname(dest);
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteDestination(DestinationsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully deleted Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in deleting Destination Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {
        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator[0] != INVALID_STR)
        {
            string routing_indi = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator;
            CLOG_DEBUG(" Routing Indicator = %s",routing_indi.c_str());
            DestinationConfig->set_addresstype(routing_indi);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.family[0] != INVALID_STR)
        {
            string family = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.family;
            CLOG_DEBUG(" Family = %s",family.c_str());
            DestinationConfig->set_protocolfamily(family);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode != INVALID_NUM)
        {
            int pointcode = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode;
            CLOG_DEBUG(" PointCode = %d",pointcode);
            DestinationConfig->set_pointcode(pointcode);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.ni != INVALID_NUM)
        {
            int ni = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.ni;
            CLOG_DEBUG(" Network Indicator = %d",ni);
            DestinationConfig->set_networkindicator(ni);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.ssn[0] != INVALID_STR)
        {
            string ssn = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.ssn;

            if(!strcmp(ssn.c_str(),"HLR"))
            {
                DestinationConfig->set_ssn(HLR);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),HLR);
            }
            else if(!strcmp(ssn.c_str(),"CAP"))
            {
                DestinationConfig->set_ssn(CAP);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),CAP);
            }
            else if(!strcmp(ssn.c_str(),"SGSN"))
            {
                DestinationConfig->set_ssn(SGSN);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),SGSN);
            }
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.gti != INVALID_NUM)
        {
            int gti = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.gti;
            CLOG_DEBUG(" GTI = %d",gti);
            DestinationConfig->set_gti(gti);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.translation_type != INVALID_NUM)
        {
            long long trans_type = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.translation_type;
            CLOG_DEBUG(" Translation Type = %lld",trans_type);
            DestinationConfig->set_translationtype(trans_type);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.numbering_plan != INVALID_NUM)
        {
            int num_plan = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.numbering_plan;
            CLOG_DEBUG(" Numbering Plan = %d",num_plan);
            DestinationConfig->set_numberingplan(num_plan);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.encoding_scheme != INVALID_NUM)
        {
            int encode_scheme = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.encoding_scheme;
            CLOG_DEBUG(" Encode Scheme = %d",encode_scheme);
            DestinationConfig->set_encodingscheme(encode_scheme);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.nature_of_addr_indicator != INVALID_NUM)
        {
            long nature_of_addr_ind = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.nature_of_addr_indicator;
            CLOG_DEBUG(" Nature Of Addr Indi = %ld",nature_of_addr_ind);
            DestinationConfig->set_natureofaddrind(nature_of_addr_ind);
        }

        if(cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.global_title_addr_info[0] != INVALID_STR)
        {
            string global_title_addr_info = cliReq->IWFPayload.destinationConfigPayload.destinationConfigInfo.global_title_addr_info;
            CLOG_DEBUG(" Global Title Addr Info = %s",global_title_addr_info.c_str());
            DestinationConfig->set_gtaddrdigits(global_title_addr_info);
        }

        if(cliReq->OP_CODE == ADD)
        {
            if(m_iwfcmapi->SetDestination(DestinationsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Added the Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Setting the Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            rsp->cmd_id = C_cli_modify_destination_config_Id;
            if(m_iwfcmapi->ModifyDestination(DestinationsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Modified the Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Modifying the Destination Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);

}

void SetAssociationSetStatus(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranAssociationSetsConfig AssociationSetsConfig;
    IwfSigtranAssociationSetConfig *AssociationSetConfig = AssociationSetsConfig.add_associationsetinfo();

    if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname[0] != INVALID_STR)
    {
        string association_set = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname;
        CLOG_DEBUG(" AssociationSet = %s",association_set.c_str());
        AssociationSetConfig->set_associationsetname(association_set);
    }

    if(cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.status != INVALID_NUM)
    {
        bool status = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigInfo.status;
        CLOG_DEBUG(" status = %d",status);
        AssociationSetConfig->set_status(status);
    }

    if(m_iwfcmapi->ActivateAssociationSet(AssociationSetsConfig, &cfgResp) == CMAPI_SUCCESS)
    {
        CLOG_DEBUG(" Succesfully Modified the Association Set Status Configuration");
        rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
        CLOG_ERROR("Error in Modifying the Association Set Status Configuration");
        rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetAssociationStatus(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfSigtranAssociationsConfig AssociationsConfig;
    IwfSigtranAssociationConfig *AssociationConfig = AssociationsConfig.add_associationinfo();

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname[0] != INVALID_STR)
    {
        string association = cliReq->IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname;
        CLOG_DEBUG(" Association = %s",association.c_str());
        AssociationConfig->set_associationname(association);
    }

    if(cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.status != INVALID_NUM)
    {
        bool status = cliReq->IWFPayload.associationConfigPayload.associationConfigInfo.status;
        CLOG_DEBUG(" status = %d",status);
        AssociationConfig->set_status(status);
    }

    if(m_iwfcmapi->ActivateAssociation(AssociationsConfig, &cfgResp) == CMAPI_SUCCESS)
    {
        CLOG_DEBUG(" Succesfully Modified the Association Status Configuration");
        rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
        CLOG_ERROR("Error in Modifying the Association Status Configuration");
        rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void SetLocalConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    IwfLocalHostConfig localhostconfig;
    IWFCfgResp cfgResp;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.num_ssn_configured != INVALID_NUM)
    {
        int num_of_ssn = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.num_ssn_configured;
        CLOG_DEBUG(" Num of SSN's = %d",num_of_ssn);
        for(int i = 0; i < num_of_ssn; i++)
        {
            IwfLocalSSNConfig *ssnconfig = localhostconfig.add_ssn_config();
            string ssn = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ssn[i];

            if(!strcmp(ssn.c_str(),"HLR"))
            {
                ssnconfig->set_ssn(HLR);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),HLR);
            }
            else if(!strcmp(ssn.c_str(),"CAP"))
            {
                ssnconfig->set_ssn(CAP);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),CAP);
            }
            else if(!strcmp(ssn.c_str(),"SGSN"))
            {
                ssnconfig->set_ssn(SGSN);
                CLOG_DEBUG(" SSN = %s - %d",ssn.c_str(),SGSN);
            }
        }
    }

    if(cliReq->OP_CODE == DELETE)
    {
        if(m_iwfcmapi->DeleteLocalHostSSN(localhostconfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully removed ssn assocaition from LocalHost Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR("Error in removing association ssn from LocalHost Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else
    {

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostKeyInfo.pointcode != INVALID_NUM)
        {
            int pointcode = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostKeyInfo.pointcode;
            localhostconfig.set_pointcode(pointcode);
            CLOG_DEBUG(" PointCode = %d",pointcode);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ni != INVALID_NUM)
        {
            int networkIndicator = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ni;
            localhostconfig.set_networkindicator(networkIndicator);
            CLOG_DEBUG(" Newtwork Indicator = %d",networkIndicator);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.routing_indicator[0] != INVALID_STR)
        {
            string routing_indi = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.routing_indicator;
            localhostconfig.set_addresstype(routing_indi);
            CLOG_DEBUG(" Routing Indicator = %s",routing_indi.c_str());
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.tcap_invoke_timer != INVALID_NUM)
        {
            int tcap_timer = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.tcap_invoke_timer;
            localhostconfig.set_tcapinvoketimer(tcap_timer);
            CLOG_DEBUG(" Tcap Invoke Timer = %d",tcap_timer);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti != INVALID_NUM)
        {
            int gti = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti;
            localhostconfig.set_gti(gti);
            CLOG_DEBUG(" GTI = %d",gti);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.translation_type != INVALID_NUM)
        {
            long long trans_type = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.translation_type;
            localhostconfig.set_translationtype(trans_type);
            CLOG_DEBUG(" Translation Type = %lld",trans_type);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.numbering_plan != INVALID_NUM)
        {
            int num_plan = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.numbering_plan;
            localhostconfig.set_numberingplan(num_plan);
            CLOG_DEBUG(" Numbering Plan = %d",num_plan);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.encoding_scheme != INVALID_NUM)
        {
            int encode_scheme = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.encoding_scheme;
            localhostconfig.set_encodingscheme(encode_scheme);
            CLOG_DEBUG(" Encode Scheme = %d",encode_scheme);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.nature_of_addr_indicator != INVALID_NUM)
        {
            long nature_of_addr_ind = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.nature_of_addr_indicator;
            localhostconfig.set_natureofaddrind(nature_of_addr_ind);
            CLOG_DEBUG(" Nature Of Addr Indi = %ld",nature_of_addr_ind);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.global_title_addr_info[0] != INVALID_STR)
        {
            string addr_info = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.global_title_addr_info;
            localhostconfig.set_gtaddrdigits(addr_info);
            CLOG_DEBUG(" Global Title Addr Info = %s",addr_info.c_str());
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria != INVALID_NUM)
        {
            int criteria = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria;
            localhostconfig.set_selectcriteria(criteria);
            CLOG_DEBUG(" SelectionCriteria = %d",criteria);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_local_gt_from_config != INVALID_NUM)
        {
            int use_local_gt_from_config = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_local_gt_from_config;
            localhostconfig.set_localgtusefromconfig(use_local_gt_from_config);
            CLOG_DEBUG(" Use Local GT from Config = %d",use_local_gt_from_config);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_sccp_cdpa_from_in_msg != INVALID_NUM)
        {
            int use_sccp_cdpa_from_in_msg = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_sccp_cdpa_from_in_msg;
            localhostconfig.set_usesccpcdpafromincommingmsg(use_sccp_cdpa_from_in_msg);
            CLOG_DEBUG(" Use SCCP CalledPartyAddress from Incomming Msg = %d",use_sccp_cdpa_from_in_msg);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_ssn != INVALID_NUM)
        {
            int include_ssn = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_ssn;
            localhostconfig.set_includessn(include_ssn);
            CLOG_DEBUG(" Include SSN = %d",include_ssn);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_pc != INVALID_NUM)
        {
            int include_pc = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_pc;
            localhostconfig.set_includepc(include_pc);
            CLOG_DEBUG(" Include PC = %d",include_pc);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname1[0] != INVALID_STR)
        {
            string hostname = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname1;
            localhostconfig.set_hostname1(hostname);
            CLOG_DEBUG(" HostName1 = %s",hostname.c_str());
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid1 != INVALID_NUM)
        {
            int aspid = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid1;
            localhostconfig.set_aspid1(aspid);
            CLOG_DEBUG(" ASPId1 = %d",aspid);
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname2[0] != INVALID_STR)
        {
            string hostname = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname2;
            localhostconfig.set_hostname2(hostname);
            CLOG_DEBUG(" HostName2 = %s",hostname.c_str());
        }

        if(cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid2 != INVALID_NUM)
        {
            int aspid = cliReq->IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid2;
            localhostconfig.set_aspid2(aspid);
            CLOG_DEBUG(" ASPId2 = %d",aspid);
        }

        if(cliReq->OP_CODE == ADD)
        {
            if(m_iwfcmapi->SetLocalHostConfig(localhostconfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Added the LocalHost Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Setting the LocalHost Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else
        {
            if(m_iwfcmapi->ModifyLocalHostConfig(localhostconfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Modified the LocalHost Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR("Error in Modifying the LocalHost Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void ShowSigtranLocalConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    ErrorDetails err;
    IwfLocalHostConfig localhostconfig;

    if(m_iwfcmapi->GetLocalHostConfig(localhostconfig, err) == CMAPI_SUCCESS)
    {
        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
        IwfLocalHostConfig *LC = &localhostconfig;
        if(LC->has_pointcode())
        {
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, " IWF Local Config Table");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"PointCode",
                            FIELD_DELIMITER,"NetworkIndicator",
                            FIELD_DELIMITER,"RoutingIndicator",
                            FIELD_DELIMITER,"SSN",
                            FIELD_DELIMITER,"GTI",
                            FIELD_DELIMITER,"TranslationType",
                            FIELD_DELIMITER,"NumberingPlan",
                            FIELD_DELIMITER,"EncodingScheme",
                            FIELD_DELIMITER,"NatureOfAddrIndi",
                            FIELD_DELIMITER,"GlobalTitleAddrInfo",
                            FIELD_DELIMITER,"SelectionCriteria",
                            FIELD_DELIMITER,"TcapInvokeTimer",
                            FIELD_DELIMITER,"UseLocalGtFromConfig",
                            //FIELD_DELIMITER,"UseSCCPCdpaFromIncommingMsg",
                            //FIELD_DELIMITER,"IncludeSSN",
                            FIELD_DELIMITER,"IncludePC",
                            FIELD_DELIMITER,"HostName1",
                            FIELD_DELIMITER,"AspId1",
                            FIELD_DELIMITER,"HostName2",
                            FIELD_DELIMITER,"AspId2",ROW_DELIMITER);



            if(LC->has_pointcode())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->pointcode(),FIELD_DELIMITER);
            }

            if(LC->has_networkindicator())
            {
                int ni = LC->networkindicator();
                if(ni)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c","NATIONAL",FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c","INTERNATIONAL",FIELD_DELIMITER);
            }
            else
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

            if(LC->has_addresstype())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->addresstype().c_str(),FIELD_DELIMITER);
            }
            else
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

            int ssn_size = LC->ssn_config_size();
            if(!ssn_size)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
            else
            {
                for(int i = 0; i < ssn_size; i++)
                {
                    IwfLocalSSNConfig *SSNConfig = LC->mutable_ssn_config(i);
                    if(SSNConfig->has_ssn())
                    {
                        int ssn = SSNConfig->ssn();
                        if(ssn == HLR)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"HLR");
                        else if(ssn == SGSN)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN");
                        else if(ssn == CAP)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CAP");

                        if(i < ssn_size - 1)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                    }
                }
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",FIELD_DELIMITER);
            }

            if(LC->has_gti())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->gti(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_translationtype())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->translationtype(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_numberingplan())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->numberingplan(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_encodingscheme())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->encodingscheme(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_natureofaddrind())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->natureofaddrind(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_gtaddrdigits())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->gtaddrdigits().c_str(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_selectcriteria())
            {
                int criteria = LC->selectcriteria();
                if(criteria == MCC_MNC)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"MCC-MNC%c",FIELD_DELIMITER);
                else if(criteria == APP_ID)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"APP-ID%c",FIELD_DELIMITER);
                else if(criteria == MCC_MNC_AND_APP_ID)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"MCC-MNC-AND-APP-ID%c",FIELD_DELIMITER);
                else if(criteria == SK)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SERVICE-KEY%c",FIELD_DELIMITER);
                else if(criteria == SK_AND_MCC_MNC)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SERVICE-KEY-AND-MCC-MNC%c",FIELD_DELIMITER);
                else if(criteria == GTT)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"GTT%c",FIELD_DELIMITER);
                else if(criteria == GTT_AND_SK)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"GTT-AND-SERVICE-KEY%c",FIELD_DELIMITER);
                else if(criteria == GTT_AND_MCC_MNC)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"GTT-AND-MCC-MNC%c",FIELD_DELIMITER);
                else if(criteria == IMSI_PREFIX_AND_SK)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"IMSI-PREFIX-AND-SERVICE-KEY%c",FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_tcapinvoketimer())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->tcapinvoketimer(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_localgtusefromconfig())
            {
                if(LC->localgtusefromconfig())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
#if 0
            if(LC->has_usesccpcdpafromincommingmsg())
            {
                if(LC->usesccpcdpafromincommingmsg())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            //NEED TO IMPLEMENT IN IWF TO SUPPORT IN CLI
            if(LC->has_includessn())
            {
                if(LC->includessn())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
#endif

            if(LC->has_includepc())
            {
                if(LC->includepc())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_hostname1())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->hostname1().c_str(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
            
            if(LC->has_aspid1())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->aspid1(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }
            
            if(LC->has_hostname2())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LC->hostname2().c_str(),FIELD_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
            }

            if(LC->has_aspid2())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",LC->aspid2(),ROW_DELIMITER);
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Sigtran Local Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Sigtran Local Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowSctpProfileConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;
    ErrorDetails err;
    IwfSigtranSctpProfilesConfig SctpProfilesconfig;

    if(cmdID == C_cli_show_sctp_profile_config_Id)
    {
        IwfSigtranSctpProfileConfig *SctpProfileConfig = SctpProfilesconfig.add_sctpprofileinfo();
        string sctpprofile = cliReq->IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename;
        CLOG_DEBUG(" SCTP-Profile = %s",sctpprofile.c_str());
        SctpProfileConfig->set_sctpprofilename(sctpprofile);
    }

    if(m_iwfcmapi->GetSctpProfile(SctpProfilesconfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranSctpProfilesConfig *SctpProfiles = &SctpProfilesconfig;
        unsigned int sctpprofiles_size = SctpProfiles->sctpprofileinfo_size();
        CLOG_INFO("Num of SCTP Profiles = %d",sctpprofiles_size);

        if(sctpprofiles_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   SCTP-Profile Config");
#if 0
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"SCTPProfile",
                    FIELD_DELIMITER,"HeartBeatEnable",
                    FIELD_DELIMITER,"HearBeatTimeOut",
                    FIELD_DELIMITER,"InitialTimeOut",
                    FIELD_DELIMITER,"MaximumInitAttempts",
                    FIELD_DELIMITER,"MaximumAssocAttempts",
                    FIELD_DELIMITER,"RTOMaximum",
                    FIELD_DELIMITER,"RTOMinimum",
                    FIELD_DELIMITER,"RTOInitial",
                    FIELD_DELIMITER,"PathFailRetryCount",
                    FIELD_DELIMITER,"MaxInstreams",
                    FIELD_DELIMITER,"NumofOutStreams",
                    FIELD_DELIMITER,"SendTimeOut",
                    FIELD_DELIMITER,"ReceiveTimeOut",
                    FIELD_DELIMITER,"ShutDownTimeOut",
                    FIELD_DELIMITER,"PathMaxRetransmit",
                    FIELD_DELIMITER,"CookieLife",
                    FIELD_DELIMITER,"SackDelay",
                    FIELD_DELIMITER,"SendBufferSize",
                    FIELD_DELIMITER,"ReceiveBufferSize",
                    FIELD_DELIMITER,"ReconnectTimeOut",
                    ROW_DELIMITER);
#endif
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"SCTPProfile",
                    FIELD_DELIMITER,"HeartBeatEnable",
                    FIELD_DELIMITER,"HearBeatTimeOut",
                    FIELD_DELIMITER,"InitialTimeOut",
                    FIELD_DELIMITER,"MaximumInitAttempts",
                    FIELD_DELIMITER,"MaximumAssocAttempts",
                    FIELD_DELIMITER,"RTOMaximum",
                    FIELD_DELIMITER,"RTOMinimum",
                    FIELD_DELIMITER,"RTOInitial",
                    FIELD_DELIMITER,"MaxInstreams",
                    FIELD_DELIMITER,"NumofOutStreams",
                    FIELD_DELIMITER,"PathMaxRetransmit",
                    FIELD_DELIMITER,"CookieLife",
                    FIELD_DELIMITER,"SackDelay",
                    FIELD_DELIMITER,"ReconnectTimeOut",
                    ROW_DELIMITER);

            for(unsigned int i = 0; i < sctpprofiles_size; i++)
            {
                IwfSigtranSctpProfileConfig *sctpconfig = SctpProfiles->mutable_sctpprofileinfo(i);

                if(sctpconfig->has_sctpprofilename())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",sctpconfig->sctpprofilename().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_heartbeatenable())
                {
                    if(sctpconfig->heartbeatenable()==0)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"disable%c",FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"enable%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_heartbeattimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->heartbeattimeout(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_inittimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->inittimeout(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_maxattempt())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->maxattempt(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_assocmaxattempt())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->assocmaxattempt(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_rtomax())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->rtomax(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_rtomin())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->rtomin(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_rtoinitial())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->rtoinitial(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_maxinstreams())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->maxinstreams(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_numoutstreams())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->numoutstreams(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if 0
                if(sctpconfig->has_sendtimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->sendtimeout(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_receivetimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->receivetimeout(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_shutdowntimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->shutdowntimeout(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif

                if(sctpconfig->has_pathfailureretrycount())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->pathfailureretrycount(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_cookielife())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->cookielife(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_sackdelay())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->sackdelay(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if 0
                if(sctpconfig->has_sendbufsize())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->sendbufsize(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(sctpconfig->has_recvbufsize())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->recvbufsize(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                if(sctpconfig->has_reconnecttimeout())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",sctpconfig->reconnecttimeout(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Peer Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching SCTPProfile Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowSctpEndPointConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranSctpEndPointsConfig SctpEndPointsconfig;

    if(cmdID == C_cli_show_sctp_endpoint_config_Id)
    {
        IwfSigtranSctpEndPointConfig *sctpEndPointConfig = SctpEndPointsconfig.add_sctpendpointinfo();
        string endpoint  = cliReq->IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint;
        CLOG_DEBUG(" EndPoint = %s", endpoint.c_str());
        sctpEndPointConfig->set_endpointname(endpoint);
    }

    if(m_iwfcmapi->GetIwfSctpEndPoint(SctpEndPointsconfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranSctpEndPointsConfig *SctpEndPoints = &SctpEndPointsconfig;
        unsigned int sctp_end_pints_size = SctpEndPoints->sctpendpointinfo_size();
        CLOG_DEBUG(" Sctp EndPoints Size = %d",sctp_end_pints_size);
        if(sctp_end_pints_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   SCTP-EndPoint Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"SCTPEndPoint",
                    FIELD_DELIMITER,"Ip-Addr",
                    FIELD_DELIMITER,"Port",
                    FIELD_DELIMITER,"MultiHomingIp's",ROW_DELIMITER);

            for(unsigned int i = 0; i < sctp_end_pints_size; i++)
            {
                IwfSigtranSctpEndPointConfig *SctpEndPoint = SctpEndPoints->mutable_sctpendpointinfo(i);

                if(SctpEndPoint->has_endpointname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",SctpEndPoint->endpointname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(SctpEndPoint->has_ipaddress())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",SctpEndPoint->ipaddress().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(SctpEndPoint->has_port())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",SctpEndPoint->port(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                unsigned int multihoming_size = SctpEndPoint->multihominginfo_size();
                if(multihoming_size)
                {
                    for(unsigned int i = 0; i < multihoming_size; i++)
                    {
                        IwfSigtranMultihomingConfig *MultiHoming = SctpEndPoint->mutable_multihominginfo(i);
                        if(MultiHoming->has_otheripaddress())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",MultiHoming->otheripaddress().c_str());
                            if(i < multihoming_size - 1)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                        }
                    }
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching SCTPEndPoint Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching SCTPEndPoint Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowAssociationConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranAssociationsConfig AssociationsConfig;

    if(cmdID == C_cli_show_association_config_Id)
    {
        IwfSigtranAssociationConfig *AssociationConfig = AssociationsConfig.add_associationinfo();
        string association = cliReq->IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname;
        CLOG_DEBUG(" Association = %s",association.c_str());
        AssociationConfig->set_associationname(association);
    }

    if(m_iwfcmapi->GetAssociation(AssociationsConfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranAssociationsConfig *AssocsConfig = &AssociationsConfig;
        unsigned int associations_size = AssocsConfig->associationinfo_size();
        CLOG_DEBUG(" Association Size = %d",associations_size);
        if(associations_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Association Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"Association",
                    FIELD_DELIMITER,"AssociationSet",
                    FIELD_DELIMITER,"LocalEndPoint",
                    FIELD_DELIMITER,"RemoteEndPoint",
                    FIELD_DELIMITER,"SctpProfile",
                    FIELD_DELIMITER,"AspId",ROW_DELIMITER);

            for(unsigned int i = 0; i<associations_size; i++)
            {
                IwfSigtranAssociationConfig *AssocConfig = AssocsConfig->mutable_associationinfo(i);

                if(AssocConfig->has_associationname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",AssocConfig->associationname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocConfig->has_associationsetname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",AssocConfig->associationsetname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocConfig->has_localendpoint())
                {
                    IwfSigtranSctpEndPointConfig LocalEndPoint = AssocConfig->localendpoint();

                    if(LocalEndPoint.has_endpointname())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",LocalEndPoint.endpointname().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocConfig->has_remoteendpoint())
                {
                    IwfSigtranSctpEndPointConfig RemoteEndPoint = AssocConfig->remoteendpoint();

                    if(RemoteEndPoint.has_endpointname())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RemoteEndPoint.endpointname().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocConfig->has_sctpprofile())
                {
                    IwfSigtranSctpProfileConfig SctpProfile = AssocConfig->sctpprofile();

                    if(SctpProfile.has_sctpprofilename())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",SctpProfile.sctpprofilename().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocConfig->has_aspid())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",AssocConfig->aspid(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Association Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Association Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowUALConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranUalManagerConfig ualconfig;

    if(m_iwfcmapi->GetUalConfig(ualconfig, err) == CMAPI_SUCCESS)
    {
        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
        IwfSigtranUalManagerConfig* UALconfig = &ualconfig;
        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "    UAL-Manager Config");
        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                FIELD_DELIMITER,"Ack-Timer",
                FIELD_DELIMITER,"Sigtran-Mode",ROW_DELIMITER);

        if(UALconfig->has_acktimer())
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",UALconfig->acktimer(),FIELD_DELIMITER);
        else
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

        if(UALconfig->has_sigtranmode())
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",UALconfig->sigtranmode().c_str(),ROW_DELIMITER);
        else
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching UAL Manager Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowAssociationSetConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranAssociationSetsConfig AssociationSetsConfig;

    if(cmdID == C_cli_show_associationset_config_Id)
    {
        IwfSigtranAssociationSetConfig *AssocSetConfig = AssociationSetsConfig.add_associationsetinfo();
        string assocset = cliReq->IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname;
        CLOG_DEBUG(" AssociationSet = %s", assocset.c_str());
        AssocSetConfig->set_associationsetname(assocset);
    }

    if(m_iwfcmapi->GetAssociationSet(AssociationSetsConfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranAssociationSetsConfig *AssocSetsConfig = &AssociationSetsConfig;
        unsigned int assoc_set_size = AssocSetsConfig->associationsetinfo_size();
        CLOG_DEBUG(" AssociationSet Size = %d",assoc_set_size);
        if(assoc_set_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   AssociationSet Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"AssociationSet",
                    FIELD_DELIMITER,"AdjPointCode",
                    FIELD_DELIMITER,"NetworkIndicator",
                    FIELD_DELIMITER,"RoutingContext",
                    FIELD_DELIMITER,"TrafficMode",
                    FIELD_DELIMITER,"IsMember",
                    FIELD_DELIMITER,"HomeIp",ROW_DELIMITER);

            for(unsigned int i = 0; i<assoc_set_size; i++)
            {
                IwfSigtranAssociationSetConfig *AssocSetConfig = AssocSetsConfig->mutable_associationsetinfo(i);

                if(AssocSetConfig->has_associationsetname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",AssocSetConfig->associationsetname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_adjacenpointcode())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",AssocSetConfig->adjacenpointcode(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_networkindicator())
                {
                    int ni = AssocSetConfig->networkindicator();
                    if(ni)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NATIONAL%c",FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"INTERNATIONAL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_routingcontext())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",AssocSetConfig->routingcontext(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_trafficmode())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",AssocSetConfig->trafficmode().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_ismember())
                {
                    if(AssocSetConfig->ismember())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(AssocSetConfig->has_homeip())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",AssocSetConfig->homeip().c_str(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

#if 0
                if(AssocSetConfig->has_aspid())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",AssocSetConfig->aspid(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching AssociationSet Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching AssociationSet Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowDestinationConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranDestinationsConfig DestsConfig;

    if(cmdID == C_cli_show_destination_config_Id)
    {
        IwfSigtranDestinationConfig *DestinationConfig = DestsConfig.add_destioninfo();
        string dest = cliReq->IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name;
        CLOG_DEBUG(" Destination = %s",dest.c_str());
        DestinationConfig->set_destinationname(dest);
    }

    if(m_iwfcmapi->GetDestination(DestsConfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranDestinationsConfig *DestinationsConfig = &DestsConfig;
        unsigned int destination_size = DestinationsConfig->destioninfo_size();
        CLOG_DEBUG(" Destinations Size = %d",destination_size);

        if(destination_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Destinations Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"Destination",
                    FIELD_DELIMITER,"PointCode",
                    FIELD_DELIMITER,"NetworkIndicator",
                    FIELD_DELIMITER,"RoutingIndicator",
                    FIELD_DELIMITER,"SSN",
                    FIELD_DELIMITER,"GTI",
                    FIELD_DELIMITER,"TranslationType",
                    FIELD_DELIMITER,"NumberingPlan",
                    FIELD_DELIMITER,"EncodingScheme",
                    FIELD_DELIMITER,"NatureOfAddrIndi",
                    FIELD_DELIMITER,"GlobalTitleAddrInfo",ROW_DELIMITER);

            for(unsigned int i = 0; i<destination_size; i++)
            {
                IwfSigtranDestinationConfig *DestConfig = DestinationsConfig->mutable_destioninfo(i);

                if(DestConfig->has_destinationname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DestConfig->destinationname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(DestConfig->has_pointcode())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->pointcode(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(DestConfig->has_networkindicator())
                {
                    int ni = DestConfig->networkindicator();
                    if(ni)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NATIONAL%c",FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"INTERNATIONAL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(DestConfig->has_addresstype())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DestConfig->addresstype().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(DestConfig->has_ssn())
                {
                    int ssn = DestConfig->ssn();
                    if(ssn == HLR)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"HLR%c",FIELD_DELIMITER);
                    else if(ssn == SGSN)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN%c",FIELD_DELIMITER);
                    else if(ssn == CAP)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CAP%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(DestConfig->has_gti())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->gti(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }

                if(DestConfig->has_translationtype())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->translationtype(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }

                if(DestConfig->has_numberingplan())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->numberingplan(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }

                if(DestConfig->has_encodingscheme())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->encodingscheme(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }

                if(DestConfig->has_natureofaddrind())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",DestConfig->natureofaddrind(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }

                if(DestConfig->has_gtaddrdigits())
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DestConfig->gtaddrdigits().c_str(),ROW_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }

            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Destination Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Destination Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowRemoteRouteConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfSigtranRemoteRoutesConfig RemoteRoutesConfig;

    if(cmdID == C_cli_show_remoteroute_config_Id)
    {
        IwfSigtranRemoteRouteConfig *remoterouteconfig = RemoteRoutesConfig.add_remoterouteinfo();
        string remoteroute = cliReq->IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name;
        CLOG_DEBUG("  RemoteRoute = %s",remoteroute.c_str());
        remoterouteconfig->set_remoteroutename(remoteroute);
    }

    if(m_iwfcmapi->GetRemoteRoute(RemoteRoutesConfig, err) == CMAPI_SUCCESS)
    {
        IwfSigtranRemoteRoutesConfig *RoutesConfig = &RemoteRoutesConfig;
        unsigned int remote_route_size = RoutesConfig->remoterouteinfo_size();

        if(remote_route_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   Remote-Route Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"RemoteRoute",
                    FIELD_DELIMITER,"AssociationSet",
                    FIELD_DELIMITER,"Destination",
                    FIELD_DELIMITER,"Priority",ROW_DELIMITER);

            for(unsigned int i =0; i<remote_route_size; i++)
            {
                IwfSigtranRemoteRouteConfig *RouteConfig = RoutesConfig->mutable_remoterouteinfo(i);

                if(RouteConfig->has_remoteroutename())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RouteConfig->remoteroutename().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RouteConfig->has_associationsetname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RouteConfig->associationsetname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RouteConfig->has_destinationinfo())
                {
                    IwfSigtranDestinationConfig DestConfig = RouteConfig->destinationinfo();
                    if(DestConfig.has_destinationname())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",DestConfig.destinationname().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RouteConfig->has_priority())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RouteConfig->priority(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching RemoteRoute Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching RemoteRoute Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowTranslatorRuleConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfTranslatorRulesConfig TranslatorRulesConfig;

    if(cmdID == C_cli_show_translatorrule_config_Id)
    {
        IwfTranslatorRuleConfig *transrule = TranslatorRulesConfig.add_ruleinfo();
        string rulename = cliReq->IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name;
        CLOG_DEBUG("Translator Rule = %s",rulename.c_str());
        transrule->set_translatorrulename(rulename);
    }

    if(m_iwfcmapi->GetTranslatorRules(TranslatorRulesConfig, err) == CMAPI_SUCCESS)
    {
        IwfTranslatorRulesConfig *TransRulesConfig = &TranslatorRulesConfig;
        unsigned int trans_rule_size = TransRulesConfig->ruleinfo_size();
        CLOG_DEBUG(" Translator Rules Size = %d",trans_rule_size);

        if(trans_rule_size)
        {
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   TranslatorRule Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                    FIELD_DELIMITER,"TranslatorRule",
                    FIELD_DELIMITER,"TranslatorType",
                    FIELD_DELIMITER,"Translator",
                    FIELD_DELIMITER,"Primary-Host",
                    FIELD_DELIMITER,"Primary-Realm/Destination",
                    FIELD_DELIMITER,"Secondary-Host",
                    FIELD_DELIMITER,"Secondary-Realm/Destination",
                    //FIELD_DELIMITER,"Mcc",
                    //FIELD_DELIMITER,"Mnc",
                    FIELD_DELIMITER,"Ossn",
                    FIELD_DELIMITER,"Dssn",
                    FIELD_DELIMITER,"App-Id",
                    FIELD_DELIMITER,"Http-Url",
                    FIELD_DELIMITER,"Web-Srvc-Id",
                    //FIELD_DELIMITER,"IsRangeDefined",
                    FIELD_DELIMITER,"ServiceKey",
                    FIELD_DELIMITER,"IMSIPrefix",
                    FIELD_DELIMITER,"ProActionRule",
                    //FIELD_DELIMITER,"CallingGTAddrDigits",
                    FIELD_DELIMITER,"ServiceContextId",
                    FIELD_DELIMITER,"Allowed-vplmn-Id",ROW_DELIMITER);

            for(unsigned int i = 0; i<trans_rule_size; i++)
            {
                IwfTranslatorRuleConfig *RuleConfig = TransRulesConfig->mutable_ruleinfo(i);

                if(RuleConfig->has_translatorrulename())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->translatorrulename().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_translatortype())
                {
                    IwfTranslatorType TransType = RuleConfig->translatortype();
                    if(TransType.has_translatortypename())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",TransType.translatortypename().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_translatorinfo())
                {
                    IwfTranslatorConfig Translator = RuleConfig->translatorinfo();
                    if(Translator.has_translatorname())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",Translator.translatorname().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_destinationhost())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->destinationhost().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_destinationname())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->destinationname().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_alternatehost())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->alternatehost().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_alternaterealm())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->alternaterealm().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#if 0
                if(RuleConfig->has_mcc())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->mcc().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_mnc())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->mnc().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                if(RuleConfig->has_ossn())
                {
                    if(RuleConfig->ossn() == HLR)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"HLR%c",FIELD_DELIMITER);
                    else if(RuleConfig->ossn() == SGSN)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN%c",FIELD_DELIMITER);
                    else if(RuleConfig->ossn() == CAP)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CAP%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_dssn())
                {
                    if(RuleConfig->dssn() == HLR)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"HLR%c",FIELD_DELIMITER);
                    else if(RuleConfig->dssn() == SGSN)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN%c",FIELD_DELIMITER);
                    else if(RuleConfig->dssn() == CAP)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"CAP%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_appid())
                {
                    if(!strcmp(RuleConfig->appid().c_str(),S6A_APPID))
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"S6a%c",FIELD_DELIMITER);
                    else if(!strcmp(RuleConfig->appid().c_str(),RO_APPID))
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Ro%c",FIELD_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_httpurl())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->httpurl().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_webservice())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->webservice().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

#if 0
                if(RuleConfig->has_isservicekeyinrange())
                {
                    if(RuleConfig->isservicekeyinrange())
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Yes%c",FIELD_DELIMITER);

                        if(RuleConfig->has_servicekeystartvalue())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d ",RuleConfig->servicekeystartvalue());

                            if(RuleConfig->has_servicekeyendvalue())
                            {
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"- %d%c",RuleConfig->servicekeyendvalue(),FIELD_DELIMITER);
                            }
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",FIELD_DELIMITER);
                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    }
                    else
                    {
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No%c",FIELD_DELIMITER);

                        if(RuleConfig->has_servicekeystartvalue())
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",RuleConfig->servicekeystartvalue(),FIELD_DELIMITER);
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                    }
                }
#endif
                if(RuleConfig->has_servicekey() && RuleConfig->has_isservicekeyinrange())
                {
                    if(RuleConfig->isservicekeyinrange())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"Range : %s%c",RuleConfig->servicekey().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"List  : %s%c",RuleConfig->servicekey().c_str(),FIELD_DELIMITER);
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
                }
                #if 0
                if(RuleConfig->has_callinggtaddrdigits())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->callinggtaddrdigits().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);
#endif
                if(RuleConfig->has_imsiprefix())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->imsiprefix().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_proactionrulename())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->proactionrulename().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(RuleConfig->has_servicecontextid())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",RuleConfig->servicecontextid().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

		        if(RuleConfig->vplmninfo_size())
                {
                    int vplmn_size = RuleConfig->vplmninfo_size();
                    for(int i = 0; i < vplmn_size; i++)
                    {
                        IwfVplmnIdConfig *vplmnInfo = RuleConfig->mutable_vplmninfo(i);
                        if(vplmnInfo->has_allowedvplmnid())
                        {
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",vplmnInfo->allowedvplmnid().c_str());
                            if(i < vplmn_size - 1)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,", ");
                        }
                    }
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching Translator Rule Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Translator Rule Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }

    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowS6aMAPConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfS6aToMapConfig S6aMapConfig;

    if(m_iwfcmapi->GetS6aMapTranslationData(S6aMapConfig, err) == CMAPI_SUCCESS)
    {
        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
        IwfS6aToMapConfig *S6aMapConf = &S6aMapConfig;

        if(cmdID == C_cli_show_s6amap_config_Id)
        {
            if(S6aMapConf->has_sgsnnumber())
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   S6a-MAP Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                        FIELD_DELIMITER,"LocalSGSNNumber",
                        FIELD_DELIMITER,"RoutingPrefix",ROW_DELIMITER);

                if(S6aMapConf->has_sgsnnumber())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",S6aMapConf->sgsnnumber().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(S6aMapConf->has_routingprefix())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",S6aMapConf->routingprefix().c_str(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error Fetching S6aMAP Information ");
            }
        }
        else if(cmdID == C_cli_show_s6amap_sgsn_addr_config_Id)
        {
            unsigned int sgsn_size = S6aMapConf->sgsnaddress_size();
            if(sgsn_size)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "SGSN-Addr Mapping Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                        FIELD_DELIMITER,"Org-Host",
                        FIELD_DELIMITER,"Ip-Addr",ROW_DELIMITER);

                for(unsigned int i = 0; i < sgsn_size; i++)
                {
                    SgsnAddresses *sgsnAddr = S6aMapConf->mutable_sgsnaddress(i);
                    if(sgsnAddr->has_orginhost())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",sgsnAddr->orginhost().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sgsnAddr->has_ipaddress())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",sgsnAddr->ipaddress().c_str(),ROW_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("SGSN Address mapping is not configired.");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN Address Mapping is not configured.");
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);
                return;
            }
        }
        else
        {
            unsigned int sgsn_size = S6aMapConf->sgsnprefixconf_size();
            if(sgsn_size)
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "SGSN-Prefix Mapping Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                        FIELD_DELIMITER,"VplmnId",
                        FIELD_DELIMITER,"Sgsn-Prefix",ROW_DELIMITER);

                for(unsigned int i = 0; i < sgsn_size; i++)
                {
                    SgsnPrefixesConfig *sgsnAddr = S6aMapConf->mutable_sgsnprefixconf(i);
                    if(sgsnAddr->has_vplmnid())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",sgsnAddr->vplmnid().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(sgsnAddr->has_sgsnprefix())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",sgsnAddr->sgsnprefix().c_str(),ROW_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_DEBUG("SGSN Prefix mapping is not configired.");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SGSN Prefix Mapping is not configured.");
                CLOG_DEBUG(" < %s ",__FUNCTION__);
                SendResponseToMgmt2((void*)rsp, portnum);
                return;
            }
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching S6aMAP Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowMAPS6aConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfMapToS6aConfig MapS6aConfig;

    if(m_iwfcmapi->GetMapS6aTranslationData(MapS6aConfig, err) == CMAPI_SUCCESS)
    {
        IwfMapToS6aConfig *MapS6aConf = &MapS6aConfig;
        rsp->ResponseCode = CMGR_FETCH_SUCCESS;
        if(MapS6aConf->has_hlrnumber())
        {
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   MAP-S6a Config");
            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",FIELD_DELIMITER,"HLRNumber");
            int vplmnid_size = MapS6aConf->maptos6avplmnidinfo_size();
            if(vplmnid_size)
            {
                for(int i=0; i<vplmnid_size; i++)
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",FIELD_DELIMITER,"Allowed-VplmnId");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);

                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",MapS6aConf->hlrnumber().c_str(),FIELD_DELIMITER);
                for(int i=0; i<vplmnid_size; i++)
                {
                    IwfMapToS6aVplmnIdConfig *VplmnIdConf = MapS6aConf->mutable_maptos6avplmnidinfo(i);
                    if(VplmnIdConf->has_allowedvplmnid())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",VplmnIdConf->allowedvplmnid().c_str());
                    if(VplmnIdConf->sgsnnumberinfo_size())
                    {
                        int sgsn_size = VplmnIdConf->sgsnnumberinfo_size();
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN," - Mapped Sgsn-Num's: ");
                        for(int j = 0; j < sgsn_size; j++)
                        {
                            SgsnNumbers *sgsnConf = VplmnIdConf->mutable_sgsnnumberinfo(j);
                            if(sgsnConf->has_sgsnnumber())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s",sgsnConf->sgsnnumber().c_str());
                            if(j != sgsn_size -1)
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,",");
                        }
                    }

                    if(i == vplmnid_size - 1)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",FIELD_DELIMITER);
                }
            }
            else
            {
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,"Allowed-VplmnId",ROW_DELIMITER);
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c%s%c",MapS6aConf->hlrnumber().c_str(),FIELD_DELIMITER,"NULL",ROW_DELIMITER);
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching MAP-S6a Information ");
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching MAP-S6a Information ");
    }

    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowCAPRoConfig(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfCapToRoConfig CapRoConfig;

    if(cmdID == C_cli_show_capro_idpsms_config_Id)
    {
        if(m_iwfcmapi->GetCapRoIDPSMSTranslationData(CapRoConfig, err) == CMAPI_SUCCESS)
        {
            IwfCapToRoConfig *CapRoConf = &CapRoConfig;
            if(CapRoConf->has_caproidpsmsinfo())
            {
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                CapRoIdpSmsConfig IdpSMSConfig = CapRoConf->caproidpsmsinfo();

                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   CAPRo-IDPSMS Config");
                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c",
                        FIELD_DELIMITER,"SMSNode",
                        FIELD_DELIMITER,"ClientAddr",
                        FIELD_DELIMITER,"OrgSccpAddr",
                        FIELD_DELIMITER,"ReplyPathRequest",
                        FIELD_DELIMITER,"Msc-Srvc-Specific-Type",
                        FIELD_DELIMITER,"Sgsn-Srvc-Specific-Type",ROW_DELIMITER);


                if(IdpSMSConfig.has_smsnode())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpSMSConfig.smsnode(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(IdpSMSConfig.has_clientaddress())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpSMSConfig.clientaddress().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(IdpSMSConfig.has_originatorsccpaddress())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpSMSConfig.originatorsccpaddress().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(IdpSMSConfig.has_replypathrequested())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpSMSConfig.replypathrequested(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(IdpSMSConfig.has_mscservicespecifictype())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpSMSConfig.mscservicespecifictype(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(IdpSMSConfig.sgsnservicespecifictype())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpSMSConfig.sgsnservicespecifictype(),ROW_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error Fetching CAPRO-IDPSMS Information ");
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching CAPRO-IDPSMS Information ");
        }
    }
    else
    {
        if(m_iwfcmapi->GetCapRoIDPTranslationData(CapRoConfig, err) == CMAPI_SUCCESS)
        {
            IwfCapToRoConfig *CapRoConf = &CapRoConfig;
            if(CapRoConf->has_caproidpinfo())
            {
                CapRoIdpConfig IdpConfig = CapRoConf->caproidpinfo();
                rsp->ResponseCode = CMGR_FETCH_SUCCESS;
                if(cmdID == C_cli_show_capro_idp_config_Id)
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "   CAPRo-IDP Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"NodeFunctionality",
                            FIELD_DELIMITER,"SipMethod",
                            FIELD_DELIMITER,"Originating-IOI",
                            FIELD_DELIMITER,"Terminating-IOI",
                            FIELD_DELIMITER,"CauseCode",
                            FIELD_DELIMITER,"Msc-Srvc-Specific-Type",
                            FIELD_DELIMITER,"Gmsc-Srvc-Specific-Type",
                            FIELD_DELIMITER,"Cpc-Srvc-Specific-Type",
                            FIELD_DELIMITER,"MultipleServiceIndi",ROW_DELIMITER);

                    if(IdpConfig.has_nodefunctionality())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpConfig.nodefunctionality(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_sipmethod())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpConfig.sipmethod().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_orignatingtoi())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpConfig.orignatingtoi().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_terminatingtoi())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpConfig.terminatingtoi().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_causecode())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",IdpConfig.causecode().c_str(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_mscservicespecfictype())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpConfig.mscservicespecfictype(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_gmscservicespecifictype())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpConfig.gmscservicespecifictype(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_cpcservicespecifictype())
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",IdpConfig.cpcservicespecifictype(),FIELD_DELIMITER);
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                    if(IdpConfig.has_multipleserviceindicator())
                    {
                        int multiple_srvs_indi = IdpConfig.multipleserviceindicator();
                        if(multiple_srvs_indi == SUPPORTED)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"SUPPORTED%c",ROW_DELIMITER);
                        else if(multiple_srvs_indi == NOT_SUPPORTED)
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NOT-SUPPORTED%c",ROW_DELIMITER);
                    }
                    else
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                }
                else if(cmdID == C_cli_show_capro_idp_ext_tele_config_Id)
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Ext-Tele-Service-Map Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"Ext-Tele-Service",
                            FIELD_DELIMITER,"Service-Id",ROW_DELIMITER);


                    if(IdpConfig.extteleinfo_size() > 0)
                    {
                        unsigned int ext_tele_service_count = IdpConfig.extteleinfo_size();
                        for(unsigned int i = 0; i < ext_tele_service_count; i++)
                        {
                            ExtTeleServiceConfig *TeleServiceConfig = IdpConfig.mutable_extteleinfo(i);
                            if(TeleServiceConfig->has_extteleservicecode())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",TeleServiceConfig->extteleservicecode(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(TeleServiceConfig->has_serviceid())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",TeleServiceConfig->serviceid(),ROW_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        CLOG_ERROR("No CAPRO-IDP Ext-Tele Information ");
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%cNULL%c",FIELD_DELIMITER,ROW_DELIMITER);
                    }
                }
                else
                {
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "Ext-Bearer-Service-Map Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c",
                            FIELD_DELIMITER,"Ext-Bearer-Service",
                            FIELD_DELIMITER,"Service-Id",ROW_DELIMITER);

                    if(IdpConfig.extbearerinfo_size() > 0)
                    {
                        unsigned int ext_bearer_service_count = IdpConfig.extbearerinfo_size();
                        for(unsigned int i = 0; i < ext_bearer_service_count; i++)
                        {
                            ExtBearerServiceConfig *BearerServiceConfig = IdpConfig.mutable_extbearerinfo(i);
                            if(BearerServiceConfig->has_extbearerservicecode())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",BearerServiceConfig->extbearerservicecode(),FIELD_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                            if(BearerServiceConfig->has_serviceid())
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%d%c",BearerServiceConfig->serviceid(),ROW_DELIMITER);
                            else
                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
                        }
                    }
                    else
                    {
                        CLOG_ERROR("No CAPRO-IDP Ext-Bearer Information ");
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%cNULL%c",FIELD_DELIMITER,ROW_DELIMITER);
                    }
                }
            }
            else
            {
                rsp->ResponseCode = CMGR_FETCH_ERROR;
                CLOG_ERROR("Error Fetching CAPRO-IDP Information ");
            }
        }
        else
        {
            rsp->ResponseCode = CMGR_FETCH_ERROR;
            CLOG_ERROR("Error Fetching CAPRO Information ");
        }
    }
    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowIwfVersion(int portnum, void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    const char iwfVersion[] = IWF_VER;

    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "     IWF Version");
    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,"Diametriq IWF Version ",ROW_DELIMITER);
    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c",FIELD_DELIMITER,iwfVersion, ROW_DELIMITER);
    CLOG_DEBUG("Diametriq IWF Version : %s",iwfVersion);

    rsp->cmd_id = cmdID;
    rsp->ResponseCode = CMGR_FETCH_SUCCESS;
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void ShowIWFProtocolActionsConfig(int portnum, void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG(" > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    ErrorDetails err;
    IwfProtocolActionsConfig ProtocolActionsConfig;

    if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name[0] != INVALID_STR)
    {
        IwfProtocolActionConfig *ProtocolConfig = ProtocolActionsConfig.add_iwfprotactioncfgval();
        string rule = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name;
        ProtocolConfig->set_actionrulename(rule);
        CLOG_DEBUG("RuleName = %s",rule.c_str());
    }

    if(m_iwfcmapi->GetIwfProtocolActionsConfig(ProtocolActionsConfig, err) == CMAPI_SUCCESS)
    {
        IwfProtocolActionsConfig *ProtocolActions = &ProtocolActionsConfig;

        if(ProtocolActions->iwfprotactioncfgval_size())
        {
            int protcol_size = ProtocolActions->iwfprotactioncfgval_size();
            rsp->ResponseCode = CMGR_FETCH_SUCCESS;

            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s",TABLE_DELIMITER, "ProtocolAction Rules Config");
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c%s%c%s%c%s%c%s%c",
                            FIELD_DELIMITER,"Protocol",
                            FIELD_DELIMITER,"RuleName",
                            FIELD_DELIMITER,"ActionId",
                            FIELD_DELIMITER,"CallScenarioDetails",ROW_DELIMITER);


            for(int i = 0; i < protcol_size; i++)
            {
                IwfProtocolActionConfig *ActionConfig = ProtocolActions->mutable_iwfprotactioncfgval(i);

                if(ActionConfig->has_protocol())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",ActionConfig->protocol().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(ActionConfig->has_actionrulename())
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s%c",ActionConfig->actionrulename().c_str(),FIELD_DELIMITER);
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(ActionConfig->has_actionid())
                {
                    int actionId = ActionConfig->actionid();
                    if(actionId == RRB_ACTION)
                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"RRB%c",FIELD_DELIMITER);

                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",FIELD_DELIMITER);

                if(ActionConfig->msgdetval_size())
                {
                    int message_size = ActionConfig->msgdetval_size();
                    for(int j = 0; j < message_size; j++)
                    {
                        MsgDet *msgDet = ActionConfig->mutable_msgdetval(j);

                        if(msgDet->callscenarioval_size())
                        {
                            int callscenario_size = msgDet->callscenarioval_size();
                            for(int k = 0; k < callscenario_size; k++)
                            {
                                CallScenario *callScenario = msgDet->mutable_callscenarioval(k);

                                if(callScenario->has_call_typename())
                                {
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%s - ",callScenario->call_typename().c_str());
                                    if(callScenario->eventtypeval_size())
                                    {
                                        int eventtype_size = callScenario->eventtypeval_size();
                                        for(int l = 0; l < eventtype_size ; l++)
                                        {
                                            EventType *eventType = callScenario->mutable_eventtypeval(l);
                                            if(eventType->has_eventtypename())
                                            {
                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"EventType : %s - ", eventType->eventtypename().c_str());
                                                if(eventType->armdatval_size())
                                                {
                                                    int armData_size = eventType->armdatval_size();
                                                    if(armData_size)
                                                    {
                                                        if(!strcasecmp(callScenario->call_typename().c_str(),"SMS_CAPV3"))
                                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"MonitorMode :");
                                                        else
                                                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"MonitorMode-LegId : ");
                                                        for (int m = 0; m < armData_size; m++)
                                                        {
                                                            ArmData* armData = eventType->mutable_armdatval(m);
                                                            if(armData->has_monitormode())
                                                            {
                                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"[%s",armData->monitormode().c_str());
                                                            }

                                                            if(armData->has_legid())
                                                            {
                                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN," - %s]",armData->legid().c_str());
                                                                if(m < armData_size - 1)
                                                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,",");
                                                            }
                                                            else
                                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"]");
                                                        }
                                                    }
                                                }
                                                else
                                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No EventType Details configured for this Event ");

                                                snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,")");
                                            }
                                        }
                                    }
                                    else
                                        snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"No EventTypes configured for this CallScenario");
                                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"}");
                                }
                            }
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"%c",ROW_DELIMITER);
                        }
                        else
                            snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);

                    }
                }
                else
                    snprintf(rsp->payload + strlen(rsp->payload), MAX_PAYLOAD_LEN,"NULL%c",ROW_DELIMITER);
            }
        }
    }
    else
    {
        rsp->ResponseCode = CMGR_FETCH_ERROR;
        CLOG_ERROR("Error Fetching Protocol Action Rules Information ");
    }
    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(err.IsInitialized())
        {
            formErrorMessage(err,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    CLOG_DEBUG(" < %s ",__FUNCTION__);
    SendResponseToMgmt2((void*)rsp, portnum);
}

void SetIWFProtocolActionsConfig(int portnum, void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    SetConfigReq *cliReq = (SetConfigReq *)req;
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;
    IwfProtocolActionsConfig ProtocolActionsConfig;

    if(cliReq->OP_CODE == DELETE){
        CLOG_DEBUG("  DEL OP_CODE recieved.");
    }
    else if (cliReq->OP_CODE == MODIFY){
        CLOG_DEBUG("  MOD OP_CODE recieved.");
    }
    else {
        CLOG_DEBUG("  add OP_CODE recieved.");
    }

    IwfProtocolActionConfig *ProtocolConfig = ProtocolActionsConfig.add_iwfprotactioncfgval();
    if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol[0] != INVALID_STR)
    {
        string protocol = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol;
        ProtocolConfig->set_protocol(protocol);
        CLOG_DEBUG("Protocol = %s",protocol.c_str());
    }

    if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name[0] != INVALID_STR)
    {
        string rule = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name;
        ProtocolConfig->set_actionrulename(rule);
        CLOG_DEBUG("RuleName = %s",rule.c_str());
    }

    if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId[0] != INVALID_STR)
    {
        string actionId = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId;
        if(!strcmp(actionId.c_str(),"RRB"))
        {
            ProtocolConfig->set_actionid(RRB_ACTION);
            CLOG_DEBUG("ActionId = %s",actionId.c_str());
        }
    }

    MsgDet *msgDet = ProtocolConfig->add_msgdetval();
    for(int i = 0; i < MAX_CALL_SCENARIOS ; i++)
    {
        if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[i][0] != INVALID_STR)
        {
            CallScenario *callScenario = msgDet->add_callscenarioval();
            string call_type = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[i];
            callScenario->set_call_typename(call_type);
            CLOG_DEBUG("CallScenario = %s",call_type.c_str());

            for(int j = 0; j < MAX_EVENT_TYPES; j++)
            {
                if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[i][j][0] != INVALID_STR)
                {
                    EventType *evtType = callScenario->add_eventtypeval();
                    string eventType = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[i][j];
                    CLOG_DEBUG("EventType = %s",eventType.c_str());
                    evtType->set_eventtypename(eventType);

                    for(int k = 0; k < MAX_EVENT_TYPES_CONFIG; k++)
                    {
                        if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[i][j][k][0] != INVALID_STR)
                        {
                            ArmData *armData = evtType->add_armdatval();
                            string monitorMode = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[i][j][k];
                            string legId = "";
                            armData->set_monitormode(monitorMode);
                            CLOG_DEBUG("MonitorMode: %s", monitorMode.c_str());
                            if(cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.legId[i][j][k][0] != INVALID_STR)
                            {
                                legId = cliReq->IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.legId[i][j][k];
                                CLOG_DEBUG("LegId: %s", legId.c_str());
                                armData->set_legid(legId);
                            }
                        }
                    }
                }
            }
        }
    }

    if(cliReq->OP_CODE == DELETE){

        if(cmdID == C_cli_protocol_actions_Id)
        {
            if(m_iwfcmapi->DeleteIwfProtocolActionsConfig(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the ProtocolAction Rule Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR(" Error in Deleting the ProtocolAction Rule Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else if(cmdID == C_cli_no_call_scenario_config_Id)
        {
            if(m_iwfcmapi->DeleteIwfCallScenarioConfig(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the ProtocolActionRule-CallScenario Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR(" Error in Deleting the ProtocolActionRule-CallScenario Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else if(cmdID == C_cli_no_eventtype_config_Id)
        {
            if(m_iwfcmapi->DeleteIwfProtocolEventType(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the ProtocolActionRule-CallScenario-EventType Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR(" Error in Deleting the ProtocolActionRule-CallScenario-EventType Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
        else if(cmdID == C_cli_no_eventspecific_config_Id)
        {
            if(m_iwfcmapi->DeleteIwfEventTypeConfig(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
            {
                CLOG_DEBUG(" Succesfully Deleted the ProtocolActionRule-CallScenario-EventSpecific Configuration");
                rsp->ResponseCode = IWF_CONFIG_SUCCESS;
            }
            else
            {
                CLOG_ERROR(" Error in Deleting the ProtocolActionRule-CallScenario-EventSpecific Configuration");
                rsp->ResponseCode = IWF_CONFIG_ERROR;
            }
        }
    }
    else if (cliReq->OP_CODE == MODIFY){
        if(m_iwfcmapi->ModifyIwfProtocolActionsConfig(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Modified the ProtocolActionRule Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR(" Error in Modifying the ProtocolActionRule Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }
    else {
        if(m_iwfcmapi->AddIwfProtocolActionsConfig(ProtocolActionsConfig, &cfgResp) == CMAPI_SUCCESS)
        {
            CLOG_DEBUG(" Succesfully Added the ProtocolActionRule Configuration");
            rsp->ResponseCode = IWF_CONFIG_SUCCESS;
        }
        else
        {
            CLOG_ERROR(" Error in Adding the ProtocolActionRule Configuration");
            rsp->ResponseCode = IWF_CONFIG_ERROR;
        }
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}

void DumpSystemInfo(int portnum,void* req,int len,int cmdID,int interfaceID)
{
    CLOG_DEBUG("  > %s ",__FUNCTION__);
    AllResponses cliRsp, *rsp;
    memset(&cliRsp,0,sizeof(cliRsp));
    rsp = &cliRsp;
    rsp->cmd_id = cmdID;

    IWFCfgResp cfgResp;

    if(m_iwfcmapi->DumpSystemInfo(&cfgResp) == CMAPI_SUCCESS)
    {
        CLOG_DEBUG(" Succesfully Dumped System Info");
        rsp->ResponseCode = IWF_CONFIG_SUCCESS;
    }
    else
    {
        CLOG_ERROR("Error in Dumping System Info");
        rsp->ResponseCode = IWF_CONFIG_ERROR;
    }

    if(rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        //Form Error Response Message
        if(cfgResp.errordetails_size() == 1)
        {
            ErrorDetails det = cfgResp.errordetails(0);
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
        else
        {
            ErrorDetails det;
            det.set_errormsgkey("config.common.err.generic.error");
            formErrorMessage(det,rsp);
            CLOG_ERROR("Error Message received is %s",rsp->payload);
        }
    }
    SendResponseToMgmt2((void*)rsp, portnum);
    CLOG_DEBUG("  < %s ",__FUNCTION__);
}
