/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: sip_ifc.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_ifc.c,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.18  2005/03/21 13:53:25  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.17.2.4  2005/03/09 07:03:48  mkrishna
 *  Error types added for gethostbyname function
 *
 *  Revision 1.17.2.3  2005/01/17 10:00:33  mkrishna
 *  separate traces for SIP
 *
 *  Revision 1.17.2.2  2005/01/11 12:54:07  craghavendra
 *  Syslog Enhancements.
 *
 *  Revision 1.17.2.1  2004/12/28 14:00:33  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.17  2004/06/28 07:33:13  sjaddu
 *  Bug fixes during load, SIP_Stackhandle is also added.
 *
 *  Revision 1.16  2004/06/24 06:03:11  akumar
 *  Memleak fix.
 *
 *  Revision 1.15  2004/05/28 10:26:09  sjaddu
 *  Debug console support added & few bug fixes.
 *
 *  Revision 1.14  2004/04/27 11:15:39  sjaddu
 *  Transport layer revamping, no more dumps.
 *
 *  Revision 1.13  2004/04/23 13:19:44  sjaddu
 *  Testing going on.
 *
 *  Revision 1.12  2004/04/21 06:45:04  sjaddu
 *  Fixed some bugs.
 *
 *  Revision 1.11  2004/04/16 04:54:55  akumar
 *  SIP attributes are configurable thru XML.
 *
 *  Revision 1.10  2004/04/15 12:16:15  sjaddu
 *  Added indications & state machine revamping.
 *
 *  Revision 1.9  2004/04/08 13:38:56  akumar
 *  Modified as per changes in SIP_MSG struct.
 *
 *  Revision 1.8  2004/04/05 12:48:31  akumar
 *  Bug fix cycle.
 *
 *  Revision 1.7  2004/04/05 09:15:20  akumar
 *  Modification while testing basic call.
 *
 *  Revision 1.6  2004/04/05 07:47:25  sjaddu
 *  More testing, one complete call works fine.
 *
 *  Revision 1.5  2004/04/01 09:18:05  akumar
 *  FT going on.
 *
 *  Revision 1.4  2004/04/01 06:44:03  sjaddu
 *  Testing is in progress.
 *
 *  Revision 1.3  2004/03/30 15:28:49  sjaddu
 *  Commited after unit testing.
 *
 *  Revision 1.2  2004/03/25 06:49:41  akumar
 *  Interface to App functions added.
 *
 *  Revision 1.1  2004/03/19 06:02:11  sjaddu
 *  Added first revsion for sip, work in progress.
 *
 ****************************************************************************/

#include <stdio.h>
#include <sip_intern.h>
#include <its.h>
#include <its_object.h>
#include <its_types.h>
#include <sip_vframe.h>
#include <netdb.h>
#include <ctype.h>
#include <dbc_serv.h>

#define MAX_RESOLVE_ATTEMPTS 12

#include <sip_defines.h>

ITSSS7DLLAPI TRACE_Data* SIP_TraceData = NULL;

static void SIP_DbcConsole(DBC_Server *dbc, const char *cmdLine);

static TRACE_OutputInitializer fileTrace =
{
    SIP_FILE_STRING,
    ITS_TRUE,
    SIP_TRACE_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    SIP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    SIP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer SIP_TraceMap[] =
{
    {SIP_CRITICAL_STRING, ITS_FALSE,  3, { &stdoutTrace, &fileTrace, 
                                                         &syslogTrace } },
    {SIP_ERROR_STRING,    ITS_FALSE,  3, { &stdoutTrace, &fileTrace, 
                                                         &syslogTrace } },
    {SIP_WARNING_STRING,  ITS_FALSE,  3, { &stdoutTrace, &fileTrace, 
                                                         &syslogTrace } },
    {SIP_DEBUG_STRING,    ITS_FALSE,  3, { &stdoutTrace, &fileTrace, 
                                                         &syslogTrace } }
};

/*globals*/
SIP_CONFIG_INFO    SIP_configInfo;
extern TQUEUETRAN_Manager *__SIP_RcvQueue;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function Initializes config from file
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  InitSettings(RESFILE_Manager *res, const char *section)
{
    char val[ITS_PATH_MAX << 2];

    SIP_DEBUG(("InitSettings :: Enter ---\n"));
    /* These are defaults override below */
    SIP_configInfo.type = SIP_UAC;
    SIP_configInfo.T4 = 5 * 1000;  /* 5 secs */
    SIP_configInfo.T1 = 500;       /* 500 ms */
    SIP_configInfo.T2 = 4 * 1000;  /* 4 secs */
    SIP_configInfo.trnTimer = 64 * 500; /* 32 secs */

    /* Populate the transport */
    SIP_configInfo.transInfo = ITS_Malloc(sizeof(SIP_TRANSPORT_INFO));
    SIP_configInfo.transInfo->udpPortNo = 5060; 
    SIP_configInfo.transInfo->tcpPortNo = 5061;
    SIP_configInfo.transInfo->maxConn =   100;

    if (RESFILE_GetKeyValueOf(res, section, SIP_UDP_PORTNO_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        SIP_configInfo.transInfo->udpPortNo = RESFILE_ParseNum(val);
    }
    if (RESFILE_GetKeyValueOf(res, section, SIP_TCP_PORTNO_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        SIP_configInfo.transInfo->tcpPortNo = RESFILE_ParseNum(val);
    }
    if (RESFILE_GetKeyValueOf(res, section, SIP_IP_ADDR_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        SOCK_IPv4NameToAddr(val, &SIP_configInfo.transInfo->ipAddr);
    }
    /* Populate timer val */
    if (RESFILE_GetKeyValueOf(res, section, SIP_TIMER_T1_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        SIP_configInfo.T1 = RESFILE_ParseNum(val);
    }
    if (RESFILE_GetKeyValueOf(res, section, SIP_TIMER_T2_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        SIP_configInfo.T2 = RESFILE_ParseNum(val);
    }
    /* Timer for transaction */
    SIP_configInfo.trnTimer = (SIP_configInfo.T1 * 64);

    /* Critical  Traces*/
    if (RESFILE_GetKeyValueOf(res, section, SIP_TRACE_CRITICAL_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, SIP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_CRITICAL_STRING,
                                       SIP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_CRITICAL_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_CRITICAL_STRING, ITS_FALSE);
        }
    }

    /* Error Traces */
    if (RESFILE_GetKeyValueOf(res, section, SIP_TRACE_ERROR_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, SIP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_ERROR_STRING,
                                       SIP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_ERROR_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_ERROR_STRING, ITS_FALSE);
        }
    }

    /* Warning Traces */
    if (RESFILE_GetKeyValueOf(res, section, SIP_TRACE_WARNING_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, SIP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_WARNING_STRING,
                                       SIP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_WARNING_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_WARNING_STRING, ITS_FALSE);
        }
    }

    /* Debug Traces */
    if (RESFILE_GetKeyValueOf(res, section, SIP_TRACE_DEBUG_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, SIP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, SIP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(SIP_TraceData,
                                       SIP_DEBUG_STRING,
                                       SIP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(SIP_TraceData,
                                      SIP_DEBUG_STRING, ITS_FALSE);
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function Initializes the SIP stack.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int 
ISIP_Initialize()
{
    RESFILE_Manager *res;
    const char *section;
    int ret = 0;

    /* Initialize the tracing subsystem also*/
    if ((SIP_TraceData = TRACE_Constructor("ITS-SIP",
                                                 SIP_TraceMap, 4)) == NULL)
    {
        printf("Trace Initialization is failed\n");
        return (ITS_ENOMEM);
    }

    /*Initialize parser */
    SIP_ParserInit();

    /* Intialize transaction layer */
    ret = SIP_TransactionLayerInit();
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("Failed to create transaction layer  \n"));
        abort();
    }

    res = TRANSPORT_RES(__SIP_RcvQueue);
    section = TRANSPORT_NAME(__SIP_RcvQueue);

    ret = InitSettings(res, section);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("Failed to init config data from file \n"));
        abort();
    }

    /* Initiliaze transport layer */
    ret = SIP_TransportInit(SIP_configInfo.transInfo);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("Failed to create transport layer  \n"));
        abort();
    } 

    if (ITS_FindFeature(DBC_CLASS_NAME) != NULL)
    {
        SIP_DEBUG(("Added DBC console feature \n"));
        DBC_AddDoCommand(SIP_DbcConsole);
    }

    SIP_DEBUG(("------ Initialization Successfull ------\n"));
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the SIP stack.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  
ISIP_Terminate()
{
    SIP_CRITICAL(("ISIP_Terminate:: SIP stack terminating \n"));

    /* Trasnport terminate */

    /*Transaction layer terminate */
    {
        ITS_EVENT evt;
        evt.src = ITS_SIP_SRC;
        TRANSPORT_PutEvent(ITS_SIP_SRC, &evt);
    }

    /*Terminate transport layer */
    {
        SIP_configInfo.transInfo->isUp = ITS_FALSE;

        /* interrupt the select */
        write(SIP_configInfo.transInfo->cntlFd[1],
              (void *)SIP_configInfo.transInfo, 1);

        /* just wait for sec */
        TIMERS_USleep(1000);
    
        ITS_Free(SIP_configInfo.transInfo);
    }

    /*Parser terminate */

    if (ITS_FindFeature(DBC_CLASS_NAME) != NULL)
    {
        DBC_RemDoCommand(SIP_DbcConsole);
    }
    return ITS_SUCCESS;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function sends event to intellinet SIP stack
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  
ISIP_SendEvent(ITS_HANDLE handle, SIP_MSG *msg)
{
    int ret;
    ITS_CHAR  *data;
    SIP_EVENT *sipEvent;
    ITS_EVENT ev;
    ITS_USHORT portNo;

    ret = SIP_Encode(msg, &data);
    if (ret != ITS_SUCCESS)
    {
        SIP_ERROR(("ISIP_SendEvent:: Failed to Encode ret  = %d", ret));
        return ret;
    }

    sipEvent = (SIP_EVENT *) ITS_Malloc( sizeof(SIP_EVENT));
    sipEvent->msg  = (void*)msg;
    sipEvent->buf  = data;

    if (msg->statusCode == 0)
    {
        ITS_CHAR addr[16];
        portNo = atoi(msg->reqUri.hostInfo.port);
        sipEvent->dest.portNo = htons ((short) portNo);

        if (msg->reqUri.hostInfo.type == SIP_HOST_TYPE_IPV4ADDR)
        { 
            SOCK_IPv4NameToAddr(msg->reqUri.hostInfo.address,
                                &sipEvent->dest.ipAddr);
        }
        else if (msg->reqUri.hostInfo.type == SIP_HOST_TYPE_HOSTNAME)
        {
            ITS_BOOLEAN done = ITS_FALSE;
            struct hostent *hostinfo = NULL;
            ITS_INT attempt = 0;
            ITS_UINT ipAddr;

            while(done == ITS_FALSE)
            {
                hostinfo  = gethostbyname(msg->reqUri.hostInfo.address);
                if (hostinfo == NULL)
                {
                    /*
                     * If the error is TRY_AGAIN do so unless we have tried to
                     * often already, in which case just timeout
                     */
                    switch (h_errno)
                    {
                    case TRY_AGAIN:
                        if (++attempt > MAX_RESOLVE_ATTEMPTS)
                        {
                            return (ITS_EBADHOST);
                        }
                        else
                        {
                            TIMERS_Sleep(5);
                        }
                        break;
                    case HOST_NOT_FOUND:
                        SIP_ERROR((" Host Not Found \n"));
                        return (ITS_ENOTFOUND);
                    case NO_ADDRESS:
                        SIP_ERROR((" No Address \n"));
                        return (ITS_ENOADDRESS);
                    case NO_RECOVERY:  
                        SIP_ERROR((" No Recovery \n"));
                        return (ITS_EBADHOST);
                    }
                }
                done = ITS_TRUE; 
            }
            memcpy(&ipAddr, hostinfo->h_addr,
                   hostinfo->h_length);
            sipEvent->dest.ipAddr = ipAddr;
        }

        addr[0] = 0;
        SOCK_IPv4AddrToName(addr, ntohl(sipEvent->dest.ipAddr));
        SIP_DEBUG(("Rem IP Address ==  %s \n", addr));
    }
    else
    {
        /* Let Trnsaction layer do this */
        sipEvent->dest.ipAddr = 0;
        sipEvent->dest.portNo = 0;
    }

    ev.src = TRANSPORT_INSTANCE(handle);
    ev.len = 0;
    ev.data = (char *) sipEvent;

    ret = TRANSPORT_PutEvent(ITS_SIP_SRC, &ev);
    if (ret != ITS_SUCCESS)
    {
        SIP_DEBUG(("Fail to send evt to Transaction layer ret = %d\n", ret));
        SIP_MsgFree((SIP_MSG *)SIP_GET_MSG_INFO(sipEvent));
        SIP_EVENT_TERM(sipEvent);
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function receives event from intellinet sip stack
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int  
ISIP_RecvEvent(ITS_HANDLE handle, ITS_EVENT *event, SIP_MSG **msg)
{
    SIP_EVENT *sipEvent;
    
    sipEvent = (SIP_EVENT *)event->data;
    *msg = (SIP_MSG *)sipEvent->msg;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function dbc control functions
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void 
SIP_DbcConsole(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret =0;

    if (dbc == NULL)
    {
        SIP_ERROR(("SIP_DbcConsole:: dbc == NULL"));
        return;
    }

    if (DBC_Cmd(dbc, "sip_set_gen_cfg", "SIP Set General Config",
                      "<traceType> <traceOutput> <On/Off>", ""))
    {
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char *type = NULL;
        char traceOutput[ITS_PATH_MAX];
        char *outPut = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, traceType,
                     traceOutput, traceOn);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: sip_set_gen_cfg <tracetype>"
                         " <trOutput> <On/Off>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            outPut = SIP_STDOUT_STRING;
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            outPut = SIP_FILE_STRING;
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            outPut = SIP_SYSLOG_STRING;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            type =  SIP_CRITICAL_STRING;
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            type = SIP_DEBUG_STRING;
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            type = SIP_WARNING_STRING;
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            type = SIP_ERROR_STRING;
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            type = "all";
        }

        if (type == "all")
        {
            if (strstr(traceOn, "on") != NULL ||
                strstr(traceOn, "ON") != NULL)
            {
                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_CRITICAL_STRING,
                                           outPut, ITS_TRUE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_CRITICAL_STRING, ITS_TRUE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_ERROR_STRING,
                                           outPut, ITS_TRUE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_ERROR_STRING, ITS_TRUE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_WARNING_STRING,
                                           outPut, ITS_TRUE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_WARNING_STRING, ITS_TRUE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_DEBUG_STRING,
                                           outPut, ITS_TRUE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_CRITICAL_STRING,
                                           outPut, ITS_FALSE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_CRITICAL_STRING, ITS_FALSE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_ERROR_STRING,
                                           outPut, ITS_FALSE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_ERROR_STRING, ITS_FALSE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_WARNING_STRING,
                                           outPut, ITS_FALSE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_WARNING_STRING, ITS_FALSE);

                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           SIP_DEBUG_STRING,
                                           outPut, ITS_FALSE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          SIP_DEBUG_STRING, ITS_FALSE);
            }
        }
        else
        {
            if (strstr(traceOn, "on") != NULL ||
                strstr(traceOn, "ON") != NULL)
            {
                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           type,
                                           outPut, ITS_TRUE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          type, ITS_TRUE);
            }
            else
            {
                TRACE_SetOutputOnOffByName(SIP_TraceData,
                                           type,
                                           outPut, ITS_FALSE);
                TRACE_SetLevelOnOffByName(SIP_TraceData,
                                          type, ITS_FALSE);
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function Initializes the SIP Class.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    /* Init the SIP stack from we directly call the sip_init function*/
    printf(" ---- Initializing the SIP stack ----\n");

    if (SIP_VENDOR_INIT_PROC(objClass) != NULL)
    {
        SIP_VENDOR_INIT_PROC(objClass)();
    }

    SIP_StackHandle = (ITS_HANDLE)objClass;

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the SIP  Class.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassDest(ITS_Class objClass)
{   
    /* Do clean up here */
    SIP_CRITICAL(("Sip stack is terminating \n"));
}


ITSDLLAPI SipVENDOR_ClassRec itsINTELLISIP_ClassRec =
{
    /* core part */
    {
        NULL,                           /* no superclass in a DLL */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        "INtellNet SIP",                /* class name */
        ClassInit,                      /* class init */
        ClassDest,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },

    /*sip vendor  part*/
    {
        ISIP_Initialize,
        ISIP_Terminate,
        ISIP_SendEvent,
        ISIP_RecvEvent
    }
};

ITSDLLAPI ITS_Class itsINTELLISIP_Class = (ITS_Class)&itsINTELLISIP_ClassRec;

