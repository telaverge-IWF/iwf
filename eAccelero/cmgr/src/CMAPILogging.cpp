/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/


#include <CMAPICMgr.h>
#include <CMAPICommon.h>
#include <CMgrDbInterface.h>

extern std::map<int,std::string> errorMap;

int CMAPICMgr::GetComponentLoggingConf(LoggerConfReq* req, LoggerConfResp* resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }



    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    switch(iOperID)
    {
        case GET_LOGGERCONFIG:
            iReturn =  m_dbInterface->mysql_Logging_Get_Config_Reqs(req,resp);
            break;
        default:
            resp->set_responseid(CMAPI_ERROR);
            DLOG_ERROR("Unknown Operation ID");
            break;

    }

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_LOGCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Logging resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Logging req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::SetComponentLoggingConf(LoggerConfReq* req, LoggerConfResp* resp)
{
    int iOperID;
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(req->has_requestid())
        iOperID =  req->requestid();
    else
    {
        resp->set_responseid(CMAPI_ERROR);
        DLOG_ERROR("Operation ID is not Set");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return 0;
    }


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }

    //Aquire Table lock before doing any operation in Mysql
	if ((iReturn = m_LockManager->CMgr_GetLock(iOperID)) != DRE_DB_SUCCESS)
	{
		if(iReturn == GET_LOCK_ERR_TABLE_MAP_NOT_CREATED)
		{
            DLOG_WARNING("Req-To-Table Map is not created for this Request");
			m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,GET_LOCK_ERR_TABLE_MAP_NOT_CREATED);
		}
		else
		{
            if(iReturn == GET_LOCK_ERR_DB_ERROR)
            {
			    DLOG_ERROR("Database Error!");
			    m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,GET_LOCK_ERR_DB_ERROR);
            }
            else if(iReturn == GET_LOCK_ERR_RESOURSE_BUSY)
            {
			    DLOG_ERROR("Failed to Acquire the Table Lock, Resource busy!");
			    m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,GET_LOCK_ERR_RESOURSE_BUSY);
            }
        	m_dbInterface->m_dbHandle.mysql_release_current_connection();
			resp->set_responseid(CMAPI_ERROR);
	        DLOG_NONE(" < %s ",__FUNCTION__);
			return 0;
		}
	}

    switch(iOperID)
    {
        case SET_LOGGERCONFIG:
            iReturn =  m_dbInterface->mysql_Logging_Add_Config_Reqs(req,resp);
            break;
        case MOD_LOGGERCONFIG:
            iReturn =  m_dbInterface->mysql_Logging_Mod_Config_Reqs(req,resp);
            break;
        default:
            DLOG_ERROR("Unknown Operation ID");
            resp->set_responseid(CMAPI_ERROR);
            break;

    }


    if(iReturn != DRE_DB_SUCCESS)
    {
		m_LockManager->CMgr_ReleaseLock(iOperID);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
    {

        if(Set_Log_Configuration(req,resp) == DRE_DB_FAIL)
        {
            resp->set_responseid(CMAPI_SUCCESS);
            if(CheckforWebAgentAndCli(req,resp) == DRE_SUCCESS)
            {
                int comp = MeSSComponent::Instance().MeSSObj().Handle().m_src.compId;
                m_compResultsHandler[comp]->SendLogConfigResult(*resp);
                m_LockManager->CMgr_ReleaseLock(iOperID);
                m_dbInterface->m_dbHandle.mysql_exec_commit(m_dbInterface->m_dbHandle.mysql_get_current_connection());
            }
            else if(CheckforAvaMgr(req,resp) == DRE_SUCCESS)
            {
                LoggerConfReq *lReq = new LoggerConfReq();
                lReq->CopyFrom(*req);

                CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                        m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);

                m_loggingAvlCallerObj->SetComponentLoggingConf(*lReq, (void*)cookie);
            }
            else
            {
                LoggerConfReq *lReq = new LoggerConfReq();
                lReq->CopyFrom(*req);

                CMgrCookie *cookie = new CMgrCookie(MeSSComponent::Instance().MeSSObj().Handle().m_src.compId, iOperID, CMAPI_SUCCESS,
                        m_dbInterface->m_dbHandle.mysql_get_current_connection(),(void*)lReq);

#if DRE
                m_loggingCallerObj->SetComponentLoggingConf(*req, (void*)cookie);
#else
                m_iwfloggingCallerObj->SetComponentLoggingConf(*req, (void*)cookie);
#endif
            }

        }
        else
        {
            int comp = MeSSComponent::Instance().MeSSObj().Handle().m_src.compId;
            m_compResultsHandler[comp]->SendLogConfigResult(*resp);
            m_LockManager->CMgr_ReleaseLock(iOperID);
            m_dbInterface->m_dbHandle.mysql_exec_commit(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        }

    }

    DLOG_DEBUG("Logging resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Logging req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::FetchLoggerConfiguration(LoggerConfReq *req, LoggerConfResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = DRE_DB_FAIL;


    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_LoggerConfResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }


    iReturn =  m_dbInterface->mysql_Logging_Get_Config_Reqs(req,resp);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();
    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if(iReturn == GET_LOGCONFIG_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    DLOG_DEBUG("Logging resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("Logging req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

// ***********************************************************************
// Component Logging Configuration Response Handlers Implementation
// ***********************************************************************

int CMAPICMgr::SetComponentLoggingConfRespCbk(LoggerConfResp *resp)
{
    int retVal = 0;
    std::string StrVal;
    LoggerConfResp ErrorResponse;
    DLOG_NONE(">SetComponentLoggingConfRespCbk : ");

    if (MeSS::Handle().m_src.instance >= MESS_MIN_STANDBY_INSTANCE)
    {
        DLOG_NONE("Response From Instance %d", MeSS::Handle().m_src.instance);
        return 0;
    }

    CMgrCookie *cookie = (CMgrCookie*)MeSS::Handle().m_cookie;
    void* conn = cookie->con;
    int iOperID = cookie->iReqID;
    LoggerConfReq *req = (LoggerConfReq*) cookie->req;

    if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
    {
        if(resp == NULL)
        {
            resp = &ErrorResponse;
        }
        DLOG_WARNING("MESS Responded with state : MESS_STATUS_NOT_READY ");

        retVal = CMAPI_SRVERROR;
        resp->set_responseid(CMAPI_SRVERROR);
        ErrorDetails* err = resp->add_errordetails();
        err->set_errorcode(CONFIG_COMMON_MESS_NOT_READY);
        err->set_errormsgkey(errorMap[CONFIG_COMMON_MESS_NOT_READY]);
    	m_LockManager->CMgr_ReleaseLock(iOperID,conn);
        m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);

    }
    else
    {

        if (MeSS::Handle().m_state == MESS_STATUS_SUCCESS)
        {
            if (resp->responseid() == CMAPI_SUCCESS)
            {

                DLOG_DEBUG(">SetComponentLoggingConfRespCbk : DRE operation - Successful. Committing the database ");
    		m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                //commit database
                m_dbInterface->m_dbHandle.mysql_exec_commit(conn);
                if(CheckforAvaMgr(req,resp) == DRE_SUCCESS)
                {
                    m_loggingStandbyAvlCallerObj->SetComponentLoggingConf(*req, (void*)NULL);
                }
                else
                {
#if DRE
                    m_standbyloggingCallerObj->SetComponentLoggingConf(*req, (void*)NULL);
#else
                    m_standbyiwfloggingCallerObj->SetComponentLoggingConf(*req, (void*)NULL);
#endif
                }
            }
            else {
                //resp->SerializeToString(&StrVal);
                //m_CMAPIResponse->Set(StrVal);
                //rollback database, since the DRE configuration failed
                m_LockManager->CMgr_ReleaseLock(iOperID,conn);
                m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            }
        } else {
            if (resp == NULL || MeSS::Handle().m_state == MESS_STATUS_TIMEOUT)
            {
                retVal = CMAPI_SRVERROR;
                ErrorResponse.set_responseid(retVal);
                //ErrorResponse.SerializeToString(&StrVal);
                resp = &ErrorResponse;
            } else {
                //resp->SerializeToString(&StrVal);
            }
    	    m_LockManager->CMgr_ReleaseLock(iOperID,conn);
            m_dbInterface->m_dbHandle.mysql_exec_rollback(conn);
            //m_CMAPIResponse->Set(StrVal);
        }
    }
    m_compResultsHandler[cookie->comp]->SendLogConfigResult(*resp);

    deleteCookie(cookie,SET_LOGGERCONFIG);
    return retVal;
}

DbStatus_e CMAPICMgr::CheckforWebAgentAndCli(LoggerConfReq *req,LoggerConfResp *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	::LoggerConf LoggingConfig;

	int iCount = req->loggerconfig_size();
	DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        LoggingConfig = req->loggerconfig(i);

        if((LoggingConfig.componentname() == "WEBAGENT") ||
            (LoggingConfig.componentname() == "webagent") ||
            (LoggingConfig.componentname() == "cli") ||
            (LoggingConfig.componentname() == "CLI"))
        {
	        DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_SUCCESS;
        }
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_FAIL;
}

DbStatus_e CMAPICMgr::CheckforAvaMgr(LoggerConfReq *req,LoggerConfResp *resp)
{
	DLOG_NONE(" > %s ",__FUNCTION__);

	::LoggerConf LoggingConfig;

	int iCount = req->loggerconfig_size();
	DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        LoggingConfig = req->loggerconfig(i);

        if((LoggingConfig.componentname() == "AVAMGR") || (LoggingConfig.componentname() == "avamgr"))
        {
	        DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_SUCCESS;
        }
    }


	DLOG_NONE(" < %s ",__FUNCTION__);
	return DRE_FAIL;
}

DbStatus_e CMAPICMgr::Set_Log_Configuration(LoggerConfReq *req,LoggerConfResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iFlag = 0;
    ::LoggerConf *pLoggingConfig;

    int iCount = req->loggerconfig_size();
    DLOG_DEBUG(" %s: loggerconfig_size = %d ",__FUNCTION__,iCount);

    for(int i=0;i<iCount;i++)
    {
        pLoggingConfig = req->mutable_loggerconfig(i);

        if(pLoggingConfig->componentname() == "CMGR")
        {
            iFlag = 1;
            if(pLoggingConfig->has_level())
            {
                DLOG_DEBUG(" Log Level is changed to %d in CMGR %s ",pLoggingConfig->level(),__FUNCTION__);
                m_ConfigManager->SetLogLevel(pLoggingConfig->level());
            }

            if(pLoggingConfig->has_channel())
            {
                DLOG_DEBUG(" Log Channel is changed to %d in CMGR %s ",pLoggingConfig->level(),__FUNCTION__);
                m_ConfigManager->SetLogChannel(pLoggingConfig->channel());
            }

            resp->set_responseid(CMAPI_SUCCESS);
        }
    }

    if(iFlag == 1)
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_FAIL;
}
