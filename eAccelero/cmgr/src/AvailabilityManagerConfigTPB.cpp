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

void AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Create_Check_Modifcation_Query(AvaMgrConfig *AvaMgrConfigReq,char *pStatement)
{

    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from AvailabilityManagerConfigT");
}

void AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Create_Add_Query(AvaMgrConfig *AvaMgrConfigReq,char *pStatement)
{


    char sFieldName[MAX_STATEMENT_SIZE]     = {0};
    char sFieldValue[MAX_STATEMENT_SIZE]    = {0};  

    LoggingConfig *pLocalLoggingConfig = NULL;

    DLOG_NONE("> %s",__FUNCTION__);
    if(AvaMgrConfigReq->has_logging())
    {
        pLocalLoggingConfig = AvaMgrConfigReq->mutable_logging();
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"insert into AvailabilityManagerConfigT ");
    snprintf(sFieldName,MAX_STATEMENT_SIZE,"(");
    snprintf(sFieldValue,MAX_STATEMENT_SIZE,"(");


    if(AvaMgrConfigReq->has_peerpingperiodicity())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->peerpingperiodicity());
    }

    if(AvaMgrConfigReq->has_arbitratorpingperiodicity())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->arbitratorpingperiodicity());
    }

    if(AvaMgrConfigReq->has_peernumconsecpingackrcvfailures())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->peernumconsecpingackrcvfailures());

    }

    if(AvaMgrConfigReq->has_arbitratornumconsecpingackrcvfailures())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->arbitratornumconsecpingackrcvfailures());

    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedinterval())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->processrestartmaxallowedinterval());

    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedcount())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->processrestartmaxallowedcount());

    }

    if(AvaMgrConfigReq->has_arbitratoripaddress())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ArbitratorIpAddress,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",AvaMgrConfigReq->arbitratoripaddress().c_str());

    }

    if(AvaMgrConfigReq->has_virtualipaddressescidrformat())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",AvaMgrConfigReq->virtualipaddressescidrformat().c_str());

    }

    if(AvaMgrConfigReq->has_ethernetinterfaces())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"EthernetInterfaces,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",AvaMgrConfigReq->ethernetinterfaces().c_str());

    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"_loglevel_,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->loglevel());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"LogChannel,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->logchannel());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"_logfilesize_,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",pLocalLoggingConfig->logfilesize());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"LogFileLocation,");
            snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",pLocalLoggingConfig->logfilename().c_str());

        }
    }

    if(AvaMgrConfigReq->has_processes())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"Processes,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",AvaMgrConfigReq->processes().c_str());

    }

    if(AvaMgrConfigReq->has_processpriorities())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"ProcessPriorities,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"'%s',",AvaMgrConfigReq->processpriorities().c_str());

    }

    if(AvaMgrConfigReq->has_timetolaunchprocesses())
    {
        snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses,");
        snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,"%d,",AvaMgrConfigReq->timetolaunchprocesses());

    }


    sFieldName[strlen(sFieldName) -1] = ' ';
    sFieldValue[strlen(sFieldValue) -1] = ' ';
    snprintf(sFieldName + strlen(sFieldName),MAX_STATEMENT_SIZE,")");
    snprintf(sFieldValue + strlen(sFieldValue),MAX_STATEMENT_SIZE,")");

    snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"%s value %s",sFieldName,sFieldValue);


    DLOG_NONE("< %s",__FUNCTION__);
}


void AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Create_Mod_Query(AvaMgrConfig *AvaMgrConfigReq,char *pStatement)
{

    DLOG_NONE("> %s",__FUNCTION__);

    LoggingConfig *pLocalLoggingConfig = NULL;

    if(AvaMgrConfigReq->has_logging())
    {
        pLocalLoggingConfig = AvaMgrConfigReq->mutable_logging();
    }

    snprintf(pStatement,MAX_STATEMENT_SIZE,"update AvailabilityManagerConfigT set ");

    if(AvaMgrConfigReq->has_peerpingperiodicity())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer=%d,",AvaMgrConfigReq->peerpingperiodicity());
    }

    if(AvaMgrConfigReq->has_arbitratorpingperiodicity())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator=%d,",AvaMgrConfigReq->arbitratorpingperiodicity());
    }

    if(AvaMgrConfigReq->has_peernumconsecpingackrcvfailures())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer=%d,",AvaMgrConfigReq->peernumconsecpingackrcvfailures());
    }

    if(AvaMgrConfigReq->has_arbitratornumconsecpingackrcvfailures())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%d,",AvaMgrConfigReq->peernumconsecpingackrcvfailures());
    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedinterval())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval=%d,",AvaMgrConfigReq->processrestartmaxallowedinterval());
    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedcount())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount=%d,",AvaMgrConfigReq->processrestartmaxallowedcount());
    }

    if(AvaMgrConfigReq->has_arbitratoripaddress())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ArbitratorIpAddress='%s',",AvaMgrConfigReq->arbitratoripaddress().c_str());
    }

    if(AvaMgrConfigReq->has_virtualipaddressescidrformat())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat='%s',",AvaMgrConfigReq->virtualipaddressescidrformat().c_str());
    }


    if(AvaMgrConfigReq->has_ethernetinterfaces())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"EthernetInterfaces='%s',",AvaMgrConfigReq->ethernetinterfaces().c_str());

    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"_loglevel_=%d,",pLocalLoggingConfig->loglevel());
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LogChannel=%d,",pLocalLoggingConfig->logchannel());
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"_logfilesize_=%d,",pLocalLoggingConfig->logfilesize());
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"LogFileLocation='%s',",pLocalLoggingConfig->logfilename().c_str());
        }
    }

    if(AvaMgrConfigReq->has_processes())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"Processes='%s',",AvaMgrConfigReq->processes().c_str());

    }

    if(AvaMgrConfigReq->has_processpriorities())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"ProcessPriorities='%s',",AvaMgrConfigReq->processpriorities().c_str());

    }

    if(AvaMgrConfigReq->has_timetolaunchprocesses())
    {
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses=%d,",AvaMgrConfigReq->timetolaunchprocesses());

    }

    pStatement[strlen(pStatement) -1] = ' ';

    //  snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE,"where Id=%d",AvaMgrConfigReq->avaMgrConfigKey.Id);

    DLOG_NONE("< %s",__FUNCTION__);
}

void AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Create_Delete_Query(AvaMgrConfig *AvaMgrConfigReq,char *pStatement)
{

    DLOG_NONE("> %s",__FUNCTION__);

    snprintf(pStatement,MAX_STATEMENT_SIZE,"delete from  AvailabilityManagerConfigT");


    DLOG_NONE("< %s",__FUNCTION__);

}

DbStatus_e AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Payload_Validation(AvaMgrConfig *AvaMgrConfigReq)
{

    DLOG_NONE("> %s",__FUNCTION__);
    DLOG_NONE("< %s",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


void AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Create_Select_Query(AvaMgrConfig *AvaMgrConfigReq,char *pStatement)
{
    int iFlag                   = 0;
    char sWhereStatement[MAX_STATEMENT_SIZE]    = {0};

    DLOG_NONE("> %s",__FUNCTION__);
    LoggingConfig *pLocalLoggingConfig = NULL;

    if(AvaMgrConfigReq->has_logging())
    {
        pLocalLoggingConfig = AvaMgrConfigReq->mutable_logging();
    }


    snprintf(pStatement,MAX_STATEMENT_SIZE,"select * from  AvailabilityManagerConfigT"); 

    snprintf(sWhereStatement,MAX_STATEMENT_SIZE,"where ");

    DLOG_NONE("< %s",__FUNCTION__);
    if(AvaMgrConfigReq->has_peerpingperiodicity())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"PingPeriodicityForPeer=%d and ",AvaMgrConfigReq->peerpingperiodicity());
    }

    if(AvaMgrConfigReq->has_arbitratorpingperiodicity())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"MinimumPingPeriodicityForArbitrator=%d and ",AvaMgrConfigReq->arbitratorpingperiodicity());

    }

    if(AvaMgrConfigReq->has_peernumconsecpingackrcvfailures())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromPeer=%d and ",AvaMgrConfigReq->peernumconsecpingackrcvfailures());

    }

    if(AvaMgrConfigReq->has_arbitratornumconsecpingackrcvfailures())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"NumberOfConsecutivePingAckRcvFailuresFromArbitrator=%d and ",AvaMgrConfigReq->arbitratornumconsecpingackrcvfailures());

    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedinterval())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedInterval=%d and ",AvaMgrConfigReq->processrestartmaxallowedinterval());

    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedcount())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessRestartMaxAllowedCount=%d and ",AvaMgrConfigReq->processrestartmaxallowedcount());

    }

    if(AvaMgrConfigReq->has_arbitratoripaddress())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ArbitratorIpAddress='%s' and ",AvaMgrConfigReq->arbitratoripaddress().c_str());

    }

    if(AvaMgrConfigReq->has_virtualipaddressescidrformat())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"VirtualIpAddressesCidrFormat='%s' and ",AvaMgrConfigReq->virtualipaddressescidrformat().c_str());

    }

    if(AvaMgrConfigReq->has_ethernetinterfaces())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"EthernetInterfaces='%s' and ",AvaMgrConfigReq->ethernetinterfaces().c_str());

    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"_loglevel=%d and ",pLocalLoggingConfig->loglevel());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LogChannel=%d and ",pLocalLoggingConfig->logchannel());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"_logfilesize_=%d and ",pLocalLoggingConfig->logfilesize());

        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            iFlag = 1;
            snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"LogFileLocation='%s' and ",pLocalLoggingConfig->logfilename().c_str());

        }
    }

    if(AvaMgrConfigReq->has_processes())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"Processes='%s' and ",AvaMgrConfigReq->processes().c_str());

    }

    if(AvaMgrConfigReq->has_processpriorities())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"ProcessPriorities='%s' and ",AvaMgrConfigReq->processpriorities().c_str());

    }

    if(AvaMgrConfigReq->has_timetolaunchprocesses())
    {
        iFlag = 1;
        snprintf(sWhereStatement + strlen(sWhereStatement),MAX_STATEMENT_SIZE,"TimeToLaunchProcesses=%d and ",AvaMgrConfigReq->timetolaunchprocesses());

    }


    if(iFlag)
    {
        sWhereStatement[strlen(sWhereStatement) - REMOVE_FOUR_CHARATERS] = '\0';
        snprintf(pStatement + strlen(pStatement),MAX_STATEMENT_SIZE," %s ",sWhereStatement);
    }
    DLOG_NONE("< %s",__FUNCTION__);

}



DbStatus_e AvailabilityManagerConfigTPBQuery::sql_AvaMgrConfig_Check_All_Invalid(AvaMgrConfig *AvaMgrConfigReq)
{
    LoggingConfig *pLocalLoggingConfig = NULL;

    DLOG_NONE("> %s",__FUNCTION__);
    if(AvaMgrConfigReq->has_logging())
    {
        pLocalLoggingConfig = AvaMgrConfigReq->mutable_logging();
    }



    if(AvaMgrConfigReq->has_peerpingperiodicity())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_arbitratorpingperiodicity())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_peernumconsecpingackrcvfailures())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_arbitratornumconsecpingackrcvfailures())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedinterval())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_processrestartmaxallowedcount())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_arbitratoripaddress())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_virtualipaddressescidrformat())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_ethernetinterfaces())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_loglevel())
        {
            return DRE_DB_FAIL;
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logchannel())
        {
            return DRE_DB_FAIL;
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilesize())
        {
            return DRE_DB_FAIL;
        }
    }

    if(AvaMgrConfigReq->has_logging())
    {
        if(pLocalLoggingConfig->has_logfilename())
        {
            return DRE_DB_FAIL;
        }
    }

    if(AvaMgrConfigReq->has_processes())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_processpriorities())
    {
        return DRE_DB_FAIL;
    }

    if(AvaMgrConfigReq->has_timetolaunchprocesses())
    {
        return DRE_DB_FAIL;
    }

    DLOG_ERROR("No variables are set in the request AvaMgrConfig  %s",__FUNCTION__);
    DLOG_NONE("< %s",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
