/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 * CONTRACT: INTERNAL
 *
 *  LOG: $Log: m3ua_config_mgnt.c,v $
 *  LOG: Revision 1.5  2008/06/04 06:34:54  ssingh
 *  LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 *  LOG:
 *  LOG: Revision 1.4  2008/04/15 05:03:14  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 1.3.2.1  2007/04/26 06:53:32  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - MML output change
 *  LOG:
 *  LOG: Revision 1.2.8.4  2008/03/14 15:09:17  ssodhi
 *  LOG: Trace level also should be off.
 *  LOG:
 *  LOG: Revision 1.2.8.3  2007/04/19 05:44:41  mshanmugam
 *  LOG: typo is correction
 *  LOG:
 *  LOG: Revision 1.2.8.2  2007/04/10 15:23:10  raghavendrabk
 *  LOG: Check Validation for M3UA_TraceData
 *  LOG:
 *  LOG: Revision 1.2.8.1  2006/12/13 18:16:03  clin
 *  LOG: merge fixes from current(no tag)
 *  LOG:
 *  LOG: Revision 1.3  2005/12/09 03:53:08  clin
 *  LOG: Add SSNM pegs for M3UA.
 *  LOG:
 *  LOG: Revision 1.2  2005/05/06 09:36:38  mmanikandan
 *  LOG: PR6.5.1 Validation Bug(1773) Fix.
 *  LOG:
 *  LOG: Revision 1.1  2005/04/06 06:02:40  adutta
 *  LOG: MML feature add as part of Bug#1557
 *  LOG:
 *  LOG:
 *
 ***************************************************************************/
#include <its.h>
#include <its_types.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <dbc_serv.h>
#include <m3ua.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Helper function to set M3UA configuration.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI ITS_INT
M3UA_SetGeneralCfg(M3UAGeneralCfg* data)
{
    if(M3UA_TraceData == NULL)
    {
        return !ITS_SUCCESS;
    }

    M3UA_AlarmLevel = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      data->traceType, ITS_FALSE);

        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Helper function to get M3UA configuration details.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI M3UAGeneralCfg*
M3UA_GetGeneralCfg()
{
    M3UAGeneralCfg *ret;

    ret = calloc(1, sizeof(M3UAGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_WARNING) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_ERROR) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_CRITICAL) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      2)));
    ret->alarmLevel = M3UA_AlarmLevel;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      It gives the M3UA configuration details
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI
void GetCfg(DBC_Server *dbc, ITS_CHAR *buf)
{
    M3UAGeneralCfg *cfg;
    ITS_UINT i;

    cfg =  M3UA_GetGeneralCfg();

    i = cfg->alarmLevel;

    /* Alarm Info */
    switch(i)
    {
        case ALARM_LVL_CRIT :
            sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

        case ALARM_LVL_MAJOR :
            sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

        case ALARM_LVL_MINOR :
            sprintf(buf, "    Alarm Level = MINOR\n");
            break;

        case ALARM_LVL_INFO :
            sprintf(buf, "    Alarm Level = INFO\n");
            break;

        case ALARM_LVL_OFF :
            sprintf(buf, "    Alarm Level = OFF\n");
            break;

        default :
            sprintf(buf, "    Alarm Level Not Set\n");
            break;
    }

    DBC_AppendText(dbc, buf);

    strcpy(buf, "    M3UA Trace -\n");
    DBC_AppendText(dbc, buf);

    /* Trace Info */
    if ( cfg->traceOn)
    {
        /* Debug */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                               M3UA_TRACE_DEBUG))
        {
            strcpy(buf, "        Debug     = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
                                2))
            {
                strcat(buf, " syslog");
            }
        }
        else
        {
            strcpy(buf, "        Debug     = null");
        }

        strcat(buf, "\n");
        DBC_AppendText(dbc, buf);

        /* Critical */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL))
        {
            strcpy(buf, "        Critical  = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
                                2))
            {
                strcat(buf, " syslog");
            }
        }
        else
        {
            strcpy(buf, "        Critical  = null");
        }

        strcat(buf, "\n");
        DBC_AppendText(dbc, buf);

        /* Warning */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING))
        {
            strcpy(buf, "        Warning   = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
                                2))
            {
                strcat(buf, " syslog");
            }
        }
        else
        {
            strcpy(buf, "        Warning   = null");
        }

        strcat(buf, "\n");
        DBC_AppendText(dbc, buf);

        /* Error */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR))
        {
            strcpy(buf, "        Error     = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
                                2))
            {
                strcat(buf, " syslog");
            }
        }
        else
        {
            strcpy(buf, "        Error     = null");
        }

        strcat(buf, "\n");
        DBC_AppendText(dbc, buf);

    }
    else
    {
        strcpy(buf, "        Debug     = null\n");
        DBC_AppendText(dbc, buf);
        strcpy(buf, "        Critical  = null\n");
        DBC_AppendText(dbc, buf);
        strcpy(buf, "        Warning   = null\n");
        DBC_AppendText(dbc, buf);
        strcpy(buf, "        Error    = null\n");
        DBC_AppendText(dbc, buf);
    }

    sprintf(buf, "*********** End of M3UA General Config *************\n");
    DBC_AppendText(dbc, buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      MML handler
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     This function handles mml commands .
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI void
M3UA_Console(DBC_Server *dbc, const char *cmdLine)
{
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_INT ret;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "m3_get_gen_cfg", "M3UA Get General Config", "", ""))
    {
        GetCfg(dbc,buf);
    }
    else if (DBC_Cmd(dbc, "m3_set_gen_cfg", "M3UA Set General Config", "<al>",
                     "<alarm level>"))
    {
        M3UAGeneralCfg cfg;
        ITS_CHAR alarmLevel[ITS_PATH_MAX];
        ITS_CHAR traceOn[ITS_PATH_MAX];
        ITS_CHAR traceType[ITS_PATH_MAX];
        ITS_CHAR traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }


        if (strstr(alarmLevel, "CRITICAL") != NULL ||
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") || strstr(alarmLevel, "major"))
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") || strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "Invalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, M3UA_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, M3UA_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, M3UA_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, M3UA_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, M3UA_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, M3UA_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, M3UA_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  M3UA_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

        sprintf(buf, "*********** M3UA General Config Set*************\n");
        DBC_AppendText(dbc, buf);

        M3UA_DEBUG(("M3UA DEBUG IS ACTIVE \n")); 
        M3UA_CRITICAL(("M3UA CRITICAL IS ACTIVE \n")); 
        M3UA_WARNING(("M3UA WARNING IS ACTIVE \n")); 
        M3UA_ERROR(("M3UA ERROR IS ACTIVE \n")); 
    }
    else if (DBC_Cmd(dbc, "m3_get_gen_peg", "M3UA Get Peg Count",
                     "<transportID> <PegID> ", " "))
    {       
        ITS_UINT trid;
        ITS_INT pegid;        
        char pgName[ITS_PATH_MAX];
        ITS_INT value;

        ret = sscanf(cmdLine, "%s %x %s", buf,&trid,pgName); 
                                                          
        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);                     
            sprintf(buf, "\n Usage: m3_get_gen_peg <trid> <pegid>\n");
            DBC_AppendText(dbc, buf);
            return;
        }                                                 
            
        if((strncmp(pgName, "All", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0))
        {   
            UAL_MIB_STATS*  data;
            data = (UAL_MIB_STATS*)malloc(sizeof(UAL_MIB_STATS));
            memset(data, 0, sizeof(UAL_MIB_STATS));       
            
            ret = UAL_GetAllPegInfo(trid, data);
            if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf, "\n**** Transport id invalid *******\n");
                DBC_AppendText(dbc, buf);
                sprintf(buf, "To get valid transport id run command u_asptbl\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "\n**************** M3UA Pegs ****************\n"); 
            DBC_AppendText(dbc, buf);

            sprintf(buf, "\nPEG_M3UA_MSG_PAUSE_IND         : %d\n",
                                                          data->pause);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_RESUME_IND        : %d\n",
                                                          data->resume);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DATA_SENT         : %d\n",
                                                          data->dataSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DATA_RECV         : %d\n",
                                                          data->dataRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DAUD_SENT         : %d\n",
                                                          data->daudSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DAUD_RECV         : %d\n",
                                                          data->daudRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DUNA_SENT         : %d\n",
                                                          data->dunaSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DUNA_RECV         : %d\n",
                                                          data->dunaRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DAVA_SENT         : %d\n",
                                                          data->davaSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DAVA_RECV         : %d\n",
                                                          data->davaRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_SCON_SENT         : %d\n",
                                                          data->sconSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_SCON_RECV         : %d\n",
                                                          data->sconRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DRST_SENT         : %d\n",
                                                          data->drstSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DRST_RECV              : %d\n",
                                                          data->drstRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DUPU_SENT         : %d\n",
                                                          data->dupuSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "PEG_M3UA_MSG_DUPU_RECV         : %d\n",
                                                          data->dupuRecv);
            DBC_AppendText(dbc, buf);

            free(data);
            return;
        }

        pegid = atoi(pgName);

        ret = UAL_GetPegInfo(trid, pegid, &value, SCTP_PAYLOAD_M3UA);
        if (ret == ITS_EENDOFLIST)
        {
            sprintf(buf, "\n**** Transport id invalid *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else if (ret == ITS_ENOTFOUND)
        {
            sprintf(buf, "\n**** Peg id invalid *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get vaild peg id do help m3_get_gen_peg\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\nvalue of peg id %d is %d\n", pegid, value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "m3_clr_gen_peg", "M3UA Clear Peg Count",
                     "<transportID> <PegID> ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ITS_INT pegid;
        ITS_UINT trid;

        ret = sscanf(cmdLine, "%s %x %s", buf, &trid, pgName);

        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid number of parameters *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n Usage: m3_clr_gen_peg <trid> <pegid>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(pgName, "All", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0))
        {
            ret = UAL_ClearAllPegInfo(trid, SCTP_PAYLOAD_M3UA);
            if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf, "\n**** Transport id invalid *******\n");
                DBC_AppendText(dbc, buf);
                sprintf(buf, "To get valid transport id run command u_asptbl\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "value of all peg ids set to 0 \n");
            DBC_AppendText(dbc, buf);
        }

        pegid = atoi(pgName);

        ret = UAL_ClearPegInfo(trid, pegid);

        if (ret == ITS_EENDOFLIST)
        {
            sprintf(buf, "\n**** invalid Transport id *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else if (ret == ITS_ENOTFOUND)
        {
            sprintf(buf, "\n**** invalid peg id *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get vaild peg id do help m3_clr_gen_peg\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\nvalue of peg id %d set to 0 \n", pegid);
        DBC_AppendText(dbc, buf);
    }

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the configuration in the XML file.
 *
 *  Input Parameters:
 *      FILE* fp - File Pointer to commit.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 * Mani        05-05-2005  BugId:1773
 *
 *  See Also:
 ****************************************************************************/

int
M3UA_Commit(FILE* fp)
{
    fprintf(fp, "\t\t<M3UA>\n");

    if (M3UA_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<SigtranTrace>\n");
        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</SigtranTrace>\n");
    }

    fprintf(fp, "\t\t</M3UA>\n\n");

    return ITS_SUCCESS;
}

