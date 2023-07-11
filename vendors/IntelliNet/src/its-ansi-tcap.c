/*********************************-*-C-*-************************************
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
 *
 *  ID: $Id: its-ansi-tcap.c,v 9.2 2008/06/04 11:02:19 ssingh Exp $
 *
 * LOG: $Log: its-ansi-tcap.c,v $
 * LOG: Revision 9.2  2008/06/04 11:02:19  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.1.10.1  2007/02/02 14:13:39  raghavendrabk
 * LOG: Parallel Stack changes for Alarms and Statistics
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.11  2003/10/17 09:23:13  vjatti
 * LOG: set the trace levels to null if not set
 * LOG:
 * LOG: Revision 8.10  2003/10/15 10:41:00  vjatti
 * LOG: Removed duplicate peg for Error received
 * LOG:
 * LOG: Revision 8.9  2003/10/13 11:26:48  vjatti
 * LOG: removed unwanted pegs
 * LOG:
 * LOG: Revision 8.8  2003/10/06 05:02:18  vjatti
 * LOG: removed appending of an extra string on to the output buffer.
 * LOG: MML ta_get_gen_cfg.
 * LOG:
 * LOG: Revision 8.7  2003/07/16 11:55:48  vjatti
 * LOG: Wnaring removal with CC compiler.
 * LOG:
 * LOG: Revision 8.6  2003/07/16 08:28:10  vjatti
 * LOG: Changes for MML output format.
 * LOG:
 * LOG: Revision 8.5  2003/07/03 11:38:00  vjatti
 * LOG: MML: Alarms & Pegs changes for PR6.4.
 * LOG:
 * LOG: Revision 8.4  2003/06/16 13:40:57  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.3  2003/04/29 21:08:34  rsonak
 * LOG: Added GenerateLTID for Intellinet specific TID generation
 * LOG:
 * LOG: Revision 8.2  2003/02/25 22:26:37  mmiers
 * LOG: Finish the split, clean up some warnings.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 21:39:13  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <assert.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_thread_pool.h>
#include <its_mutex.h>
#include <its_assertion.h>

#include <dbc_serv.h>

#ident "$Id: its-ansi-tcap.c,v 9.2 2008/06/04 11:02:19 ssingh Exp $"

#include <ansi/tcap.h>

#include "tcap_intern.h"

TQUEUETRAN_Manager *__TCAP_ANSI_RcvQueue;

static ITS_CHAR *tcapPegStr[] =
{
    "TCAP_APP_MSG_SENT",
    "TCAP_APP_MSG_DISCARDED",
    "TCAP_APP_CMP_SENT",
    "TCAP_APP_CMP_DISCARDED",
    "TCAP_REMOTE_CMP_RCVD",
    "TCAP_REMOTE_CMP_DISCARDED",
    "TCAP_REMOTE_MSG_RCVD",
    "TCAP_REMOTE_UNKNOWN_MSG_RCVD",
    "TCAP_REMOTE_MSG_DISCARDED",
    "TCAP_ACTIVE_DIALOGUE",
    "TCAP_ACTIVATED_DIALOGUE",
    "TCAP_ACTIVE_TRANSACTIONS",
    "TCAP_ACTIVATED_TRANSACTIONS",
    "TCAP_PREARRANGED_END",
    "TCAP_REMOTE_UDT_RCVD",
    "TCAP_REMOTE_XUDT_RCVD",
    "TCAP_REMOTE_UDTS_RCVD",
    "TCAP_REMOTE_XUDTS_RCVD",
    "TCAP_REMOTE_LUDT_RCVD",
    "TCAP_REMOTE_LUDTS_RCVD",
    "TCAP_REMOTE_INVALID_SCCP_RCVD",
    "TCAP_REMOTE_SCCP_CLASS_0_RCVD",
    "TCAP_REMOTE_SCCP_CLASS_1_RCVD",
    "TCAP_REMOTE_UNI_RCVD",
    "TCAP_APP_UDT_SENT",
    "TCAP_APP_XUDT_SENT",
    "TCAP_APP_UDTS_SENT",
    "TCAP_APP_XUDTS_SENT",
    "TCAP_APP_LUDT_SENT",
    "TCAP_APP_LUDTS_SENT",
    "TCAP_APP_SCCP_CLASS_0_SENT",
    "TCAP_APP_SCCP_CLASS_1_SENT",
    "TCAP_APP_U_ABORT_TO_REMOTE_SENT",
    "TCAP_APP_UNI_SENT",
    "TCAP_P_ABORT_TO_REMOTE_SENT",
    "TCAP_P_ABORT_TO_APP_SENT",
    "TCAP_P_REJECT_TO_REMOTE_SENT",
    "TCAP_P_REJECT_TO_APP_SENT",
    "TCAP_REMOTE_U_ABORT_RCVD",
    "TCAP_REMOTE_P_ABORT_RCVD",
    "TCAP_LOCAL_CANCEL",
    "TCAP_DLG_SEND_TO_REMOTE_FAIL",
    "TCAP_DLG_SEND_TO_APP_FAIL",
    "TCAP_APP_U_REJECT_SENT",
    "TCAP_APP_INVOKE_L_SENT",
    "TCAP_APP_RESULT_L_SENT",
    "TCAP_APP_RESULT_NL_SENT",
    "TCAP_APP_ERROR_SENT",
    "TCAP_REMOTE_INVOKE_L_RCVD",
    "TCAP_REMOTE_RESULT_L_RCVD",
    "TCAP_REMOTE_RESULT_NL_RCVD",
    "TCAP_REMOTE_ERROR_RCVD",
    "TCAP_REMOTE_REJECT_RCVD",

/* ITU Specific ones */
    "TCAP_APP_INV_CLASS_1_SENT",
    "TCAP_APP_INV_CLASS_2_SENT",
    "TCAP_APP_INV_CLASS_3_SENT",
    "TCAP_APP_INV_CLASS_4_SENT",
    "TCAP_APP_SCCP_RET_ON_ERR_SENT",
    "TCAP_APP_BEGIN_SENT",
    "TCAP_REMOTE_BEGIN_RCVD",
    "TCAP_APP_CONT_SENT",
    "TCAP_APP_END_SENT",
    "TCAP_REMOTE_END_RCVD",
    "TCAP_REMOTE_R_REJECT_RCVD",
    "TCAP_REMOTE_U_REJECT_RCVD",
    "TCAP_REMOTE_CONT_RCVD",

/*ANSI specific */
    "TCAP_APP_QWOP_SENT",
    "TCAP_REMOTE_QWOP_RCVD",
    "TCAP_APP_QWIP_SENT",
    "TCAP_REMOTE_QWIP_RCVD",
    "TCAP_APP_RESP_SENT",
    "TCAP_REMOTE_RESP_RCVD",
    "TCAP_APP_CWOP_SENT",
    "TCAP_REMOTE_CWOP_RCVD",
    "TCAP_APP_CWIP_SENT",
    "TCAP_REMOTE_CWIP_RCVD",
    "TCAP_APP_INVOKE_NL_SENT",
    "TCAP_REMOTE_INVOKE_NL_RCVD",
    NULL
};

THREAD_RET_TYPE ANSI_TCAPThread(void *arg);
static void TCAP_Console_ANSI(DBC_Server *dbc, const char *cmdLine);

static ITS_THREAD   *tcapThread;

static int numThreads = 1;

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes the TCAP subsystem for use.
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
 *      If the subsystem is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_TCAP_Initialize_ANSI(ITS_SS7_HANDLE handle)
{
    int i, j, ret;
    ITS_Class dbClass;
    RESFILE_Manager *res;
    char *name;
    char value[ITS_PATH_MAX];

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    if ((__TCAP_ANSI_RcvQueue = TQUEUETRAN_CreateTransport("ANSI-TCAP",
                                                           ITS_TCAP_ANSI_SRC,
                                                           ITS_TCAP_ANSI |
                                                           ITS_SCCP_ANSI |
                                                           ITS_SCCP_CCITT)) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Initialize: couldn't create transport.\n"));
        
        /* TCAP failed to Intialize -  couldn't create transport. */
        TCAP_Alarm_ANSI(1013, __FILE__, __LINE__,"family=%s", "ANSI");

        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__TCAP_ANSI_RcvQueue);
    name = TRANSPORT_NAME(__TCAP_ANSI_RcvQueue);

    ret = TCAP_Init_ANSI(res, name, 
                         TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo);
    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);

        return (ret);
    }

    if (res != NULL)
    {
        /* get the number of threads */
        if (RESFILE_GetKeyValueOf(res, name, NUM_THREADS_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            numThreads = atoi(value);
            if (numThreads < 1)
            {
                numThreads = 1;
            }
        }
    }

    if ((tcapThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        TCAP_CRITICAL(("TCAP_Init: Couldn't create thread array.\n"));
        
        /* TCAP failed to Intialize -  couldn't create thread array. */
        TCAP_Alarm_ANSI(1013, __FILE__, __LINE__, "family=%s", "ANSI");

        TCAP_Term_ANSI(TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo);

        TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);

        started = ITS_FALSE;

        return (ITS_EBADTHREAD);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&tcapThread[i], 0, ANSI_TCAPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            TCAP_CRITICAL(("TCAP_Init: Couldn't create TCAP thread.\n"));
        
        
            /* TCAP failed to Intialize -  couldn't create thread. */
            TCAP_Alarm_ANSI(1013, __FILE__, __LINE__, "family=%s", "ANSI");

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&tcapThread[j]);

                THREAD_DeleteThread(&tcapThread[j]);
            }

            free(tcapThread);

            TCAP_Term_ANSI(TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo);

            TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);

            started = ITS_FALSE;

            return (ITS_ENOMEM);
        }
    }

    /* TCAP Intialized Successfully. */
    TCAP_Alarm_ANSI(1014, __FILE__, __LINE__, "family=%s", "ANSI");

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(TCAP_Console_ANSI);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the TCAP subsystem.  Well behaved
 *      applications should call this function before exiting.
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
 *      If the subsystem is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
INTELLINET_TCAP_Terminate_ANSI(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    int i;
    ITS_Class dbClass;

    if (!started || stopped)
    {
        return;
    }

    stopped = ITS_TRUE;

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(TCAP_Console_ANSI);
    }

    ITS_EVENT_INIT(&ev, ITS_TCAP_ANSI_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_TCAP_ANSI_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&tcapThread[i], &status);

        THREAD_DeleteThread(&tcapThread[i]);
    }

    free(tcapThread);

    assert(__TCAP_ANSI_RcvQueue != NULL);

    TCAP_Term_ANSI(TRANSPORT_SS7_INFO(__TCAP_ANSI_RcvQueue).linkInfo);

    TQUEUETRAN_DeleteTransport(__TCAP_ANSI_RcvQueue);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the ANSI TCAP thread.
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
 *      This method should be considered an undocumented internal
 *      TCAP function.
 *
 *  See Also:
 ****************************************************************************/
THREAD_RET_TYPE
ANSI_TCAPThread(void *arg)
{
    ITS_EVENT tcapEvent;
    ITS_BOOLEAN cont;

    if (/*sizeof(TCAP_TRANS_ENTRY) > ITS_MAX_TIMER_CONTEXT ||*//* TBD */
        sizeof(TCAP_INVOKE_ENTRY) > ITS_MAX_TIMER_CONTEXT)
    {
        TCAP_CRITICAL(("Structure overflow\n"));
                
        /* TCAP Aborting  - Structure overflow. */
        TCAP_Alarm_ANSI(1016, __FILE__, __LINE__, "family=%s", "ANSI");

        abort();
    }

    memset(&tcapEvent, 0, sizeof(ITS_EVENT));

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__TCAP_ANSI_RcvQueue))
                                                        (__TCAP_ANSI_RcvQueue,
                                                         &tcapEvent)
           == ITS_SUCCESS)
    {
        switch (tcapEvent.src)
        {
        case ITS_SCCP_SRC:
            TCAP_DEBUG(("TCAP_Main: process SCCP event.\n"));

            TRPHandleSCCPMsg_ANSI(&tcapEvent);
            break;

        case ITS_TCAP_ANSI_SRC:
            TCAP_CRITICAL(("TCAP_Main: termination event.\n"));

            TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            TCAP_DEBUG(("TCAP_Main: process TIMER event.\n"));

            CMPHandleTimeout_ANSI(&tcapEvent);
            break;

        default:

            TCAP_DEBUG(("TCAP_Main: process APP event.\n"));

            /* we accept the message regardless.  This is dangerous, as
             * the user may not have registered their application for sending.
             */
            if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_DLG)
            {
                TPCPIHandleAPPMsg_ANSI(&tcapEvent);
            }
            else if (TCAP_MSG_TYPE(&tcapEvent) == ITS_TCAP_CPT)
            {            
                CMPHandleAPPMsg_ANSI(&tcapEvent);
            }
            else
            {
                /* user sending funky stuff */
                TCAP_CRITICAL(("TCAP_Main: unrecognized event type.\n"));
    
                /* Received Unrecognized or Invalid Event. */
                TCAP_Alarm_ANSI(1017, __FILE__, __LINE__, "family=%s", "ANSI");
            }
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__TCAP_ANSI_RcvQueue) = ITS_FALSE;

    THREAD_NORMAL_EXIT;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
TCAP_Console_ANSI(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;
    ITS_UINT i;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "ta_get_gen_cfg", "TCAP Get General Config", "", ""))
    {
        TCAPGeneralCfg *cfg;
        cfg =  TCAP_GetGeneralCfg_ANSI();

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "\n    Alarm Level  CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "\n    Alarm Level  MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "\n    Alarm Level  MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "\n    Alarm Level  INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "\n    Alarm Level  OFF\n");
            break;

            default :
                sprintf(buf, "\n    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);
        strcpy(buf, "\n    TCAP Trace -\n");
        DBC_AppendText(dbc, buf);

       if ( cfg->traceOn)
       {
           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_DEBUG,
                                      1)))
               {
                   strcpy(buf, "        Debug     =  null");
               }
           }
           else
           {
               strcpy(buf, "        Debug     =  null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_CRITICAL,
                                      1)))
               {
                   strcpy(buf, "        Critical  =  null");
               }
           }
           else
           {
               strcpy(buf, "        Critical  =  null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_WARNING,
                                      1)))
               {
                   strcpy(buf, "        Warning   =  null");
               }
           }
           else
           {
               strcpy(buf, "        Warning   =  null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(TCAP_ANSI_TraceData,
                                    TCAP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (!(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      0)) &&
                   !(TRACE_IsOutputOn(TCAP_ANSI_TraceData,
                                      TCAP_TRACE_ERROR,
                                      1)))
               {
                   strcpy(buf, "        Error     =  null");
               }
           }
           else
           {
               strcpy(buf, "        Error     =  null");
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
           strcpy(buf, "        Error     = null\n");
           DBC_AppendText(dbc, buf);
       }
    }
    else if (DBC_Cmd(dbc, "ta_set_gen_cfg", "TCAP Set General Config", 
                      "<al> <tl>",
                     "<alarm level> <On / Off>"))

    {
        TCAPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);
        
        if (ret != 5)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ta_set_gen_cfg [CRITICAL/MAJOR/MINOR/INFO/OFF]\n");
            DBC_AppendText(dbc, buf);
                           
            sprintf(buf, "\n          [CRITICAL/ERROR/WARNING/DEBUG] [stdout/file] [ON/OFF]\n");
            DBC_AppendText(dbc, buf); 
            sprintf(buf, "\n Note : The arguements are case insensitive.\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL || 
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") || 
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || 
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || 
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "\n   Invalid Alarm Level\n");
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
            sprintf(buf, "\n   Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, TCAP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, TCAP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, TCAP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, TCAP_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "\n   Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, TCAP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, TCAP_FILE_STRING);
        }
        else
        {
            sprintf(buf, "\n   Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  TCAP_SetGeneralCfg_ANSI(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

        sprintf(buf, "\n *********** TCAP General Config Set*************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ta_get_behavior", "TCAP Get Behaviors", 

                     "", ""))

    {
        if (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI))
        {
            sprintf(buf, "\n    TCAP_B_use_reserved_NI    <yes> \n");
        }
        else
        {
            sprintf(buf, "\n    TCAP_B_use_reserved_NI    <no> \n");
        }
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ta_set_behavior", "TCAP Set Behaviors", 
                     "<rni>", ""))

    {
        int rni;

        ret = sscanf(cmdLine, "%s %d", buf, &rni);

        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage : ta_set_behavior <rni> - rni = 0/1. \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (rni)
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI, 
                                  ITS_TRUE);
        }
        else
        {
            BEHAVIORS_SetBehavior(&ANSI_TCAP_Behaviors, TCAP_B_use_reserved_NI, 
                                   ITS_FALSE);
        }

        sprintf(buf, "\n *******TCAP Behaviors Set*******\n");
        DBC_AppendText(dbc, buf);


    }
    else if (DBC_Cmd(dbc, "ta_get_peg", "Get Pegs", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_UINT pg = PEG_TCAP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
            sprintf(buf, "\n   Invalid Command Arguments \n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ta_get_peg <peg>  Pls see cmd $help ta_get_peg for PEGS list\n");
            DBC_AppendText(dbc, buf); 
             return;
        }

        for (i = 0; i < PEG_TCAP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, tcapPegStr[i]))
            {
                pg = i;
                break;
            }
        }

        if (pg == PEG_TCAP_NUM_PEGS)
        {
            sprintf(buf, "\n   **** Invalid Peg Type *******\n");
            DBC_AppendText(dbc, buf);
             return;
        }

        sprintf(buf, "\n   %s \n", pgName);
        DBC_AppendText(dbc, buf);

        value = PEG_GetPeg(ANSI_TCAP_Pegs, pg);

        sprintf(buf, "\n   value is %d\n", value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ta_clr_peg", "Clear Peg", "<pg> ", "<Peg#> <>"))
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_TCAP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
             DBC_AppendText(dbc, buf);
             sprintf(buf, "\n   Usage: ta_clr_peg <ALL/all/peg-type> Pls see cmd $help ta_get_peg for PEGs list\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        if ( strstr(pgName, "ALL") || strstr(pgName, "all"))
        {
            PEG_ClearBlock(ANSI_TCAP_Pegs);

            sprintf(buf, "\n   Clearing All ANSI TCAP Pegs \n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            for (i = 0; i < PEG_TCAP_NUM_PEGS; i++)
            {
                if ( strstr(pgName, tcapPegStr[i]))
                {
                    pg = i;
                }
            }

            if (pg == PEG_TCAP_NUM_PEGS)
            {
                sprintf(buf, "\n   **** Invalid Peg Type *******\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "\n   Clearing the Pegs for %s \n", pgName);
            DBC_AppendText(dbc, buf);

            PEG_ClearPeg(ANSI_TCAP_Pegs, pg);
        }

    }
    else if (DBC_Cmd(dbc, "ta_set_local_ss", "TCAP Set Local Subsystem Entry", 
                     "<ssn>",
                     "<ssn>"))

    {
        TCAPSubSystemInfo info;
        ITS_UINT linkset = 0;
        SS7_LinkSetPtr lptr = NULL;
        int ssn;

        ret = sscanf(cmdLine, "%s %d", buf, &ssn);

        if (ret != 2)
        {
            sprintf(buf, "\n   **** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n   Usage: ta_set_local_ss <ssn>");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n          where ssn -> Local Subsystem Number to add value range 0-255 \n");
            DBC_AppendText(dbc, buf);        
            return;
        }

        lptr = LINKSET_FindLinkSet((ITS_OCTET)linkset);
        if (lptr == NULL)
        {
            sprintf(buf, "\n ********* Local Linkset 0 Not Configured********\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        
        info.pointcode = lptr->lpc;
        info.ni = lptr->ni;
        info.ssn = (ITS_OCTET)ssn;

        ret = TCAP_SetLocalSSEntry_ANSI(&info);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\n Failed To Set TCAP Local Subsystem Entryt********\n");
            DBC_AppendText(dbc, buf);
            return;
        }

         sprintf(buf, "\n ********* TCAP Local Subsystem Entry Set********\n");
         DBC_AppendText(dbc, buf);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Generate LTID.
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
 ****************************************************************************/
ITS_UINT
GenerateNewLTID_ANSI(ITS_UINT* nextLTid)
{
        (*nextLTid)--;

        return (*nextLTid);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for ansi tcap.
 *
 *  Input Parameters:
 *      Pointer to a file.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the stack informations written successfully on the given file
 *      it returns ITS_SUCCESS else if file pointer is null it will return
 *      ITS_ENULLPTR.
 ****************************************************************************/

int
INTELLINET_TCAP_Commit_ANSI(FILE* fp)
{
    int count = 0;
    TRACE_Data* td = TCAP_ANSI_TraceData;

    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    fprintf(fp,"\t\t\t\t<StackTrace>\n");

    for (count =0; count < TRACE_DATA_NUM_LEVELS(td); count++)
    {
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[0]->trace.name : "");
        fprintf(fp,"\t\t\t\t\t<%s output=\"%s\"/>\n",
                TRACE_DATA_LEVEL_MAP(td)[count]->level.levelName,
                (TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.isEnabled)?
                TRACE_DATA_LEVEL_MAP(td)[count]->
                    level.outputs[1]->trace.name : "");
    }

    fprintf(fp,"\t\t\t\t</StackTrace>\n");
    fprintf(fp,"\t\t\t\t<BehaviorControl\n");
    fprintf(fp,"\t\t\t\t\tuse_reserved_NI = \"%s\"\n",
            (BEHAVIORS_GetBehavior(&ANSI_TCAP_Behaviors,
                                   TCAP_B_use_reserved_NI) == ITS_TRUE)? 
            "yes" : "no");
    fprintf(fp,"\t\t\t\t/>\n");

    return ITS_SUCCESS;
}
