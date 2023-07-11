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

void TransformationsTPBQuery::sql_TransformationConfig_Create_Check_Modifcation_Query(TransformPlugin *TransformPluginReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from TransformationT");
}

void TransformationsTPBQuery::sql_TransformationConfig_Create_Add_Query(TransformPlugin *TransformPluginReq,char *pStatement)
{


    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    DLOG_NONE(" > %s ",__FUNCTION__);

    LoggingConfig *pLocalLoggingConfig = NULL;

    if(TransformPluginReq->has_logging())
    {
        pLocalLoggingConfig = TransformPluginReq->mutable_logging();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into TransformationT ");
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"("); 
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(TransformPluginReq->has_peerpingperiodicity())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->peerpingperiodicity());
    }

    if(TransformPluginReq->has_arbitratorpingperiodicity())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->arbitratorpingperiodicity());
    }

    if(TransformPluginReq->has_peernumconsecpingackrcvfailures())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->peernumconsecpingackrcvfailures());

    }

    if(TransformPluginReq->has_arbitratornumconsecpingackrcvfailures())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->arbitratornumconsecpingackrcvfailures());

    }

    if(TransformPluginReq->has_processrestartmaxallowedinterval())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->processrestartmaxallowedinterval());

    }

    if(TransformPluginReq->has_processrestartmaxallowedcount())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->processrestartmaxallowedcount());

    }

    if(TransformPluginReq->has_arbitratoripaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ArbitratorIpAddress,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TransformPluginReq->arbitratoripaddress().c_str());

    }

    if(TransformPluginReq->has_virtualipaddressescidrformat())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TransformPluginReq->virtualipaddressescidrformat().c_str());

    }

    if(TransformPluginReq->has_ethernetinterfaces())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"EthernetInterfaces,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TransformPluginReq->ethernetinterfaces().c_str());

    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"_loglevel_,"); 
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->loglevel());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"LogChannel,"); 
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->logchannel());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"_logfilesize_,"); 
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->logfilesize());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"LogFileLocation,"); 
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pLocalLoggingConfig->logfilename().c_str());

        }
    }

    if(TransformPluginReq->has_processes())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"Processes,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TransformPluginReq->processes().c_str());

    }

    if(TransformPluginReq->has_processpriorities())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessPriorities,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",TransformPluginReq->processpriorities().c_str());

    }

    if(TransformPluginReq->has_timetolaunchprocesses())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses,"); 
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",TransformPluginReq->timetolaunchprocesses());

    }


    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")"); 
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")"); 

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE(" < %s ",__FUNCTION__);
}


void TransformationsTPBQuery::sql_TransformationConfig_Create_Mod_Query(TransformPlugin *TransformPluginReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    LoggingConfig *pLocalLoggingConfig = NULL;

    if(TransformPluginReq->has_logging())
    {
        pLocalLoggingConfig = TransformPluginReq->mutable_logging();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update TransformationT set ");

    if(TransformPluginReq->has_peerpingperiodicity())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer=%d,",TransformPluginReq->peerpingperiodicity());
    }

    if(TransformPluginReq->has_arbitratorpingperiodicity())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator=%d,",TransformPluginReq->arbitratorpingperiodicity());
    }

    if(TransformPluginReq->has_peernumconsecpingackrcvfailures())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer=%d,",TransformPluginReq->peernumconsecpingackrcvfailures());
    }

    if(TransformPluginReq->has_arbitratornumconsecpingackrcvfailures())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%d,",TransformPluginReq->peernumconsecpingackrcvfailures());
    }

    if(TransformPluginReq->has_processrestartmaxallowedinterval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval=%d,",TransformPluginReq->processrestartmaxallowedinterval());
    }

    if(TransformPluginReq->has_processrestartmaxallowedcount())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount=%d,",TransformPluginReq->processrestartmaxallowedcount());
    }

    if(TransformPluginReq->has_arbitratoripaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ArbitratorIpAddress='%s',",TransformPluginReq->arbitratoripaddress().c_str());
    }

    if(TransformPluginReq->has_virtualipaddressescidrformat())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat='%s',",TransformPluginReq->virtualipaddressescidrformat().c_str());
    }


    if(TransformPluginReq->has_ethernetinterfaces())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"EthernetInterfaces='%s',",TransformPluginReq->ethernetinterfaces().c_str());

    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"_loglevel_=%d,",pLocalLoggingConfig->loglevel());
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LogChannel=%d,",pLocalLoggingConfig->logchannel());
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"_logfilesize_=%d,",pLocalLoggingConfig->logfilesize());
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LogFileLocation='%s',",pLocalLoggingConfig->logfilename().c_str());
        }
    }

    if(TransformPluginReq->has_processes())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Processes='%s',",TransformPluginReq->processes().c_str());

    }

    if(TransformPluginReq->has_processpriorities())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessPriorities='%s',",TransformPluginReq->processpriorities().c_str());

    }

    if(TransformPluginReq->has_timetolaunchprocesses())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses=%d,",TransformPluginReq->timetolaunchprocesses());

    }

    pStatement[strlen(pStatement) -1] = ' ';

    //  snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where Id=%d",TransformPluginReq->avaMgrConfigKey.Id);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void TransformationsTPBQuery::sql_TransformationConfig_Create_Delete_Query(TransformPlugin *TransformPluginReq,char *pStatement)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    int iFlag                                       = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]        = {0};
#endif

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  TransformationT");

#if 0
    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE(" > %s ",__FUNCTION__);
    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
#endif

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e TransformationsTPBQuery::sql_TransformationConfig_Payload_Validation(TransformPlugin *TransformPluginReq)
{

    return DRE_DB_SUCCESS;
}


void TransformationsTPBQuery::sql_TransformationConfig_Create_Select_Query(TransformPlugin *TransformPluginReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    LoggingConfig *pLocalLoggingConfig = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(TransformPluginReq->has_logging())
    {
        pLocalLoggingConfig = TransformPluginReq->mutable_logging();
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  TransformationT"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    if(TransformPluginReq->has_peerpingperiodicity())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer=%d and ",TransformPluginReq->peerpingperiodicity());
    }

    if(TransformPluginReq->has_arbitratorpingperiodicity())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator=%d and ",TransformPluginReq->arbitratorpingperiodicity());

    }

    if(TransformPluginReq->has_peernumconsecpingackrcvfailures())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer=%d and ",TransformPluginReq->peernumconsecpingackrcvfailures());

    }

    if(TransformPluginReq->has_arbitratornumconsecpingackrcvfailures())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%d and ",TransformPluginReq->arbitratornumconsecpingackrcvfailures());

    }

    if(TransformPluginReq->has_processrestartmaxallowedinterval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval=%d and ",TransformPluginReq->processrestartmaxallowedinterval());

    }

    if(TransformPluginReq->has_processrestartmaxallowedcount())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount=%d and ",TransformPluginReq->processrestartmaxallowedcount());

    }

    if(TransformPluginReq->has_arbitratoripaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ArbitratorIpAddress='%s' and ",TransformPluginReq->arbitratoripaddress().c_str());

    }

    if(TransformPluginReq->has_virtualipaddressescidrformat())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat='%s' and ",TransformPluginReq->virtualipaddressescidrformat().c_str());

    }

    if(TransformPluginReq->has_ethernetinterfaces())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"EthernetInterfaces='%s' and ",TransformPluginReq->ethernetinterfaces().c_str());

    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"_loglevel=%d and ",pLocalLoggingConfig->loglevel());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LogChannel=%d and ",pLocalLoggingConfig->logchannel());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"_logfilesize_=%d and ",pLocalLoggingConfig->logfilesize());

        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LogFileLocation='%s' and ",pLocalLoggingConfig->logfilename().c_str());

        }
    }

    if(TransformPluginReq->has_processes())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Processes='%s' and ",TransformPluginReq->processes().c_str());

    }

    if(TransformPluginReq->has_processpriorities())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessPriorities='%s' and ",TransformPluginReq->processpriorities().c_str());

    }

    if(TransformPluginReq->has_timetolaunchprocesses())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses=%d and ",TransformPluginReq->timetolaunchprocesses());

    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
}



DbStatus_e TransformationsTPBQuery::sql_TransformationConfig_Check_All_Invalid(TransformPlugin *TransformPluginReq)
{
    LoggingConfig *pLocalLoggingConfig = NULL;

    if(TransformPluginReq->has_logging())
    {
        pLocalLoggingConfig = TransformPluginReq->mutable_logging();
    }



    if(TransformPluginReq->has_peerpingperiodicity())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_arbitratorpingperiodicity())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_peernumconsecpingackrcvfailures())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_arbitratornumconsecpingackrcvfailures())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_processrestartmaxallowedinterval())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_processrestartmaxallowedcount())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_arbitratoripaddress())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_virtualipaddressescidrformat())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_ethernetinterfaces())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            return DRE_DB_FAIL;
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            return DRE_DB_FAIL;
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            return DRE_DB_FAIL;
        }
    }

    if(TransformPluginReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            return DRE_DB_FAIL;
        }
    }

    if(TransformPluginReq->has_processes())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_processpriorities())
    {
        return DRE_DB_FAIL;
    }

    if(TransformPluginReq->has_timetolaunchprocesses())
    {
        return DRE_DB_FAIL;
    }

    DLOG_INFO("In the Request, No Fields are Set for Operation");
    return DRE_DB_SUCCESS;
}
