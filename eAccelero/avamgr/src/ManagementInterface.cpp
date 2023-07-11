#include "ManagementInterface.h"
#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvailabilityManager.h"
#include "CMAPICommon.h"

ManagementInterface::ManagementInterface(AvailabilityManager *avaMgr) {
    m_objAvaMgr = avaMgr;
}

ManagementInterface::~ManagementInterface() {   
}

int ManagementInterface::AvaMgrSetConfiguration(AvaMgrConfig *req, AvaMgrConfigResp *resp) {
    return(m_objAvaMgr->AvaMgrSetConfiguration(req, resp));
}

int ManagementInterface::AvaMgrGetConfiguration(ComponentActionReq *req, AvaMgrConfigResp *resp) {
    return (m_objAvaMgr->AvaMgrGetConfiguration(req, resp));
}

int ManagementInterface::FetchClusterInfo(ClusterInfoReq *req, ClusterInfoResp *resp) {
    return (m_objAvaMgr->FetchClusterInfo(req,resp));
}

int ManagementInterface::FetchProcessState(ProcessStateReq *req, ProcessStateResp *resp) {
    return (m_objAvaMgr->FetchProcessState(req,resp));
}

int ManagementInterface::AvaMgrSwitchOverRequest(ComponentActionReq *req, AvaMgrConfigResp *resp) {
    return (m_objAvaMgr->AvaMgrSwitchOverRequest(req, resp));
}

int ManagementInterface::SetComponentLoggingConf(LoggerConfReq *req, LoggerConfResp *resp) {
    int retVal = CMAPI_SUCCESS;
    CLOG_DEBUG("AvailabilityManagerLoggingConf::SetComponentLoggingConf");

    if(!req->IsInitialized() || !req->has_requestid() || req->loggerconfig_size() <= 0)
    {    
        CLOG_ERROR("Error invalid request message for logger");
        retVal = CMAPI_ERROR;
    }    
    else 
    {    
        if(req->requestid() == MOD_LOGGERCONFIG)
        {    
            LoggerConf loggerConfig = req->loggerconfig(0);
            CLOG_DEBUG("SetComponentLoggingConf::In MOD_LOGGERCONFIG");
            if(loggerConfig.has_channel() && loggerConfig.LogChannel_IsValid(loggerConfig.channel())
                    && loggerConfig.has_componentname())
            {    
                CLOG_DEBUG("Setting log Channel of %s to %d",loggerConfig.componentname().c_str(),loggerConfig.channel());
                Logger::Channel logChannel = (Logger::Channel)loggerConfig.channel();
                m_objAvaMgr->SetLogChannel(logChannel);
                resp->set_responseid(CMAPI_SUCCESS);
            }    
            else if(loggerConfig.has_level() && loggerConfig.LogLevel_IsValid(loggerConfig.level())
                    && loggerConfig.has_componentname())
            {    
                CLOG_DEBUG("Setting log level of %s to %d ",loggerConfig.componentname().c_str(),loggerConfig.level());
                Logger::Level logLevel = (Logger::Level)loggerConfig.level();
                m_objAvaMgr->SetLogLevel(logLevel);
                resp->set_responseid(CMAPI_SUCCESS);
            }    
        }    
        else 
        {    
            CLOG_ERROR("Unsupported Logger Request received");
            resp->set_responseid(CMAPI_ERROR);
            retVal = CMAPI_ERROR;
        }    
    }    
    return retVal;
}
