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

int CMAPICMgr::CMgrAMSetConfiguration(AvaMgrConfig *req,AvaMgrConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_AvaMgrConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_AvaMgr_Set_Config_Reqs(req,resp);

    if(iReturn != DRE_DB_SUCCESS)
    {
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
        resp->set_responseid(CMAPI_SUCCESS);

    DLOG_DEBUG("AvaMgrConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("AvaMgrConfig req = %s",req->DebugString().c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::CMgrRMSetConfiguration(RepMgrConfig *req,RepMgrConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_RepMgrConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_RepMgr_Set_Config_Reqs(req,resp);

    if(iReturn != DRE_DB_SUCCESS)
    {
        m_dbInterface->m_dbHandle.mysql_exec_rollback(m_dbInterface->m_dbHandle.mysql_get_current_connection());
        resp->set_responseid(CMAPI_ERROR);
    }
    else
        resp->set_responseid(CMAPI_SUCCESS);

    DLOG_DEBUG("RepMgrConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("RepMgrConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::CMgrDreSetConfiguration(DreHAConfig *req,DreHAConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_DreHAConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_Dre_Set_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_FAIL)
        resp->set_responseid(CMAPI_ERROR);
    else
        resp->set_responseid(CMAPI_SUCCESS);

    DLOG_DEBUG("DreHAConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("DreHAConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;

}

int CMAPICMgr::FetchAvaMgrConfiguration(AvaMgrConfig *req,AvaMgrConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_AvaMgrConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_AvaMgr_Get_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_responseid(CMAPI_SUCCESS);
    else if (iReturn == GET_AVAMGR_ERR_NO_DATA_PRESENT)
        resp->set_responseid(CMAPI_SUCCESS);
    else
        resp->set_responseid(CMAPI_ERROR);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("AvaMgrConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("AvaMgrConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::FetchRepMgrConfiguration(RepMgrConfig *req,RepMgrConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_RepMgrConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_RepMgr_Get_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_FAIL)
        resp->set_responseid(CMAPI_ERROR);
    else
        resp->set_responseid(CMAPI_SUCCESS);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("RepMgrConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("RepMgrConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

int CMAPICMgr::FetchDreHAConfiguration(DreHAConfig *req,DreHAConfigResp *resp)
{
    DbStatus_e iReturn = DRE_DB_FAIL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    if (DRE_DB_FAIL == m_dbInterface->m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");
        resp->set_responseid(CMAPI_ERROR);
        m_dbInterface->mysql_set_error_for_DreHAConfigResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }
    iReturn =  m_dbInterface->mysql_Dre_Get_Config_Reqs(req,resp);

    if(iReturn == DRE_DB_FAIL)
        resp->set_responseid(CMAPI_ERROR);
    else
        resp->set_responseid(CMAPI_SUCCESS);

    // release the current connection object back to free pool
    m_dbInterface->m_dbHandle.mysql_release_current_connection();

    DLOG_DEBUG("DreHAConfigResp resp = %s",resp->DebugString().c_str());
    DLOG_DEBUG("DreHAConfig req = %s",req->DebugString().c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
    return 0;


}

