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


#include <CMgrDbInterface.h>

using namespace std;
extern std::map<int,std::string> errorMap;

void CMgrDbInterface::mysql_set_error_for_AvaMgr_Config_Reqs(AvaMgrConfig *pAvaMgrConfig, AvaMgrConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    CLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_AvaMgr_Get_Config_Reqs(AvaMgrConfig *pAvaMgrConfig,AvaMgrConfigResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    sql_AvaMgrConfig_Create_Select_Query(pAvaMgrConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_AVAMGR_ERR_DB_ERROR;

        mysql_set_error_for_AvaMgr_Config_Reqs(pAvaMgrConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);       
        return iReturn;
    }

    if((iReturn = mysql_AvaMgrConfig_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_AvaMgr_Config_Reqs(pAvaMgrConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_RepMgr_Get_Config_Reqs(RepMgrConfig *pRepMgrConfig,RepMgrConfigResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_Dre_Get_Config_Reqs(DreHAConfig *pDreHAConfig,DreHAConfigResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_AvaMgrConfig_resultset_to_protoBuff(sql::ResultSet *pRes,AvaMgrConfigResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" %s: AvaMgr Result Set Count = %d ",__FUNCTION__,pRes->rowsCount()); 
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_AVAMGR_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            ::AvaMgrConfig* pAvaMgrConfig = resp->mutable_avamgrdata();

            pAvaMgrConfig->set_peerpingperiodicity(pRes->getInt("PingPeriodicityForPeer"));
            pAvaMgrConfig->set_arbitratorpingperiodicity(pRes->getInt("MinimumPingPeriodicityForArbitrator"));
            pAvaMgrConfig->set_peernumconsecpingackrcvfailures(pRes->getInt("NumberOfConsecutivePingAckRcvFailuresFromPeer"));
            pAvaMgrConfig->set_arbitratornumconsecpingackrcvfailures(pRes->getInt("NumberOfConsecutivePingAckRcvFailuresFromArbitrator"));
            pAvaMgrConfig->set_processrestartmaxallowedinterval(pRes->getInt("ProcessRestartMaxAllowedInterval"));
            pAvaMgrConfig->set_processrestartmaxallowedcount(pRes->getInt("ProcessRestartMaxAllowedCount"));
            pAvaMgrConfig->set_arbitratoripaddress(pRes->getString("ArbitratorIpAddress"));
            pAvaMgrConfig->set_virtualipaddressescidrformat(pRes->getString("VirtualIpAddressesCidrFormat"));
            pAvaMgrConfig->set_ethernetinterfaces(pRes->getString("EthernetInterfaces"));
            pAvaMgrConfig->set_processes(pRes->getString("Processes"));
            pAvaMgrConfig->set_processpriorities(pRes->getString("ProcessPriorities"));
            pAvaMgrConfig->set_timetolaunchprocesses(pRes->getInt("TimeToLaunchProcesses"));

            ::LoggingConfig* pLoggingConfig = pAvaMgrConfig->mutable_logging();

            //pLoggingConfig->set_loglevel(pRes->getInt(""));
            pLoggingConfig->set_logchannel(pRes->getInt("LogChannel"));
            //pLoggingConfig->set_logfilesize(pRes->getInt(""));
            pLoggingConfig->set_logfilename(pRes->getString("LogFileLocation"));

        }       
    }

    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}


DbStatus_e CMgrDbInterface::mysql_AvaMgr_Set_Config_Reqs(AvaMgrConfig *pAvaMgrConfig,AvaMgrConfigResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    AvaMgrConfig LocalAvaMgrConfig;
    DLOG_NONE(" > %s ",__FUNCTION__);

    pRes = NULL;

    sql_AvaMgrConfig_Create_Check_Modifcation_Query(pAvaMgrConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_AVAMGR_ERR_DB_ERROR;

        mysql_set_error_for_AvaMgr_Config_Reqs(pAvaMgrConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;

    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_AvaMgrConfig_Create_Add_Query(pAvaMgrConfig,sStatement);
    }
    else // MOD
    {
        Copy_ResultSet_To_AvaMgrConfig(pRes,pAvaMgrConfig,&LocalAvaMgrConfig);          
        sql_AvaMgrConfig_Create_Mod_Query(&LocalAvaMgrConfig,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_AVAMGR_ERR_DB_ERROR;

        mysql_set_error_for_AvaMgr_Config_Reqs(pAvaMgrConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_RepMgr_Set_Config_Reqs(RepMgrConfig *pRepMgrConfig,RepMgrConfigResp *resp)
{

    return DRE_DB_SUCCESS;

}

void CMgrDbInterface::copy_AvaMgrConfig(AvaMgrConfigResp *resp,AvaMgrConfig *pFromAvaMgrConfig)
{
    AvaMgrConfig *pToAvaMgrConfig = resp->mutable_avamgrdata();

    pToAvaMgrConfig->CopyFrom(*pFromAvaMgrConfig);
}

DbStatus_e CMgrDbInterface::mysql_Dre_Set_Config_Reqs(DreHAConfig *pDreHAConfig,DreHAConfigResp *resp)
{

    return DRE_DB_SUCCESS;

}

void CMgrDbInterface::Copy_ResultSet_To_AvaMgrConfig(sql::ResultSet *pRes,AvaMgrConfig *pFromAvaMgrConfig,AvaMgrConfig *pToAvaMgrConfig)
{
    pToAvaMgrConfig->CopyFrom(*pFromAvaMgrConfig);

    try
    {
        pRes->next();

        if(!pFromAvaMgrConfig->has_peerpingperiodicity())
        {
            if(!pRes->isNull("PingPeriodicityForPeer"))
                pToAvaMgrConfig->set_peerpingperiodicity(pRes->getInt("PingPeriodicityForPeer"));
        }

        if(!pFromAvaMgrConfig->has_arbitratorpingperiodicity())
        {
            if(!pRes->isNull("MinimumPingPeriodicityForArbitrator"))
                pToAvaMgrConfig->set_arbitratorpingperiodicity(pRes->getInt("MinimumPingPeriodicityForArbitrator"));
        }

        if(!pFromAvaMgrConfig->has_peernumconsecpingackrcvfailures())
        {
            if(!pRes->isNull("NumberOfConsecutivePingAckRcvFailuresFromPeer"))
                pToAvaMgrConfig->set_peernumconsecpingackrcvfailures(pRes->getInt("NumberOfConsecutivePingAckRcvFailuresFromPeer"));
        }

        if(!pFromAvaMgrConfig->has_arbitratornumconsecpingackrcvfailures())
        {
            if(!pRes->isNull("NumberOfConsecutivePingAckRcvFailuresFromArbitrator"))
                pToAvaMgrConfig->set_arbitratornumconsecpingackrcvfailures(pRes->getInt("NumberOfConsecutivePingAckRcvFailuresFromArbitrator"));
        }

        if(!pFromAvaMgrConfig->has_processrestartmaxallowedinterval())
        {
            if(!pRes->isNull("ProcessRestartMaxAllowedInterval"))
                pToAvaMgrConfig->set_processrestartmaxallowedinterval(pRes->getInt("ProcessRestartMaxAllowedInterval"));
        }

        if(!pFromAvaMgrConfig->has_processrestartmaxallowedcount())
        {
            if(!pRes->isNull("ProcessRestartMaxAllowedCount"))
                pToAvaMgrConfig->set_processrestartmaxallowedcount(pRes->getInt("ProcessRestartMaxAllowedCount"));
        }

        if(!pFromAvaMgrConfig->has_arbitratoripaddress())
        {
            if(!pRes->isNull("ArbitratorIpAddress"))
                pToAvaMgrConfig->set_arbitratoripaddress(pRes->getString("ArbitratorIpAddress"));
        }

        if(!pFromAvaMgrConfig->has_virtualipaddressescidrformat())
        {
            if(!pRes->isNull("VirtualIpAddressesCidrFormat"))
                pToAvaMgrConfig->set_virtualipaddressescidrformat(pRes->getString("VirtualIpAddressesCidrFormat"));
        }

        if(!pFromAvaMgrConfig->has_ethernetinterfaces())
        {
            if(!pRes->isNull("EthernetInterfaces"))
                pToAvaMgrConfig->set_ethernetinterfaces(pRes->getString("EthernetInterfaces"));
        }

        if(!pFromAvaMgrConfig->has_processes())
        {
            if(!pRes->isNull("Processes"))
                pToAvaMgrConfig->set_processes(pRes->getString("Processes"));
        }

        if(!pFromAvaMgrConfig->has_processpriorities())
        {
            if(!pRes->isNull("ProcessPriorities"))
                pToAvaMgrConfig->set_processpriorities(pRes->getString("ProcessPriorities"));
        }

        if(!pFromAvaMgrConfig->has_timetolaunchprocesses())
        {
            if(!pRes->isNull("TimeToLaunchProcesses"))
                pToAvaMgrConfig->set_timetolaunchprocesses(pRes->getInt("TimeToLaunchProcesses"));
        }

        ::LoggingConfig* pToLoggingConfig = pToAvaMgrConfig->mutable_logging();
        ::LoggingConfig* pFromLoggingConfig = pFromAvaMgrConfig->mutable_logging();

        if(!pFromLoggingConfig->has_loglevel())
        {
            //if(!pRes->isNull("PingPeriodicityForPeer"))
            //pToLoggingConfig->set_loglevel(pRes->getInt(""));
        }


        DLOG_NONE("%s:%d pFromLoggingConfig->has_loglevel() = %d \n",__FUNCTION__,__LINE__,pFromLoggingConfig->has_loglevel());

        if(!pFromLoggingConfig->has_logchannel())
        {
            if(!pRes->isNull("LogChannel"))
                pToLoggingConfig->set_logchannel(pRes->getInt("LogChannel"));
        }

        if(!pFromLoggingConfig->has_logfilesize())
        {
            //if(!pRes->isNull(""))
            //pToLoggingConfig->set_logfilesize(pRes->getInt(""));
        }

        DLOG_NONE("%s:%d pFromLoggingConfig->has_logfilename() = %d \n",__FUNCTION__,__LINE__,pFromLoggingConfig->has_logfilename());
        if(!pFromLoggingConfig->has_logfilename())
        {
            DLOG_NONE("%s:%d pRes->isNull(\"LogFileLocation\") = %d \n",__FUNCTION__,__LINE__,pRes->isNull("LogFileLocation"));
            if(!pRes->isNull("LogFileLocation"))
                pToLoggingConfig->set_logfilename(pRes->getString("LogFileLocation"));
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
    }

    DLOG_NONE(" < %s ",__FUNCTION__);

}

