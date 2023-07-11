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
 *  ID: $Id: ual.c,v 9.16.4.5.4.4.36.2.2.1 2015/01/22 15:08:25 jkchaitanya Exp $
 *
 *  LOG: $Log: ual.c,v $
 *  LOG: Revision 9.16.4.5.4.4.36.2.2.1  2015/01/22 15:08:25  jkchaitanya
 *  LOG: changes for aspid issue faced in the HP site
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.4.36.2  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.4.36.1  2014/09/16 09:34:54  jsarvesh
 *  LOG: Changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.4.32.1  2014/09/15 07:20:42  jsarvesh
 *  LOG: Changes done for removing Warnings
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.4  2010/06/25 21:57:58  haltaf
 *  LOG: fixing xml persistancy issue #3131
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.3  2010/06/10 13:15:36  chandrashekharbs
 *  LOG: Fix for Issue id 2946
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.2  2010/05/31 14:19:02  ssingh
 *  LOG: removed unwanted code left in -r9.16.4.5.4.1
 *  LOG:
 *  LOG: Revision 9.16.4.5.4.1  2010/05/17 12:17:55  nvijikumar
 *  LOG: Fix for 2838 CheckAndStartOrStopAuditTimer func moved from 
 *  LOG: UAL to M3UA since UAL is not protocol dependent
 *  LOG:
 *  LOG: Revision 9.16.4.5  2009/04/09 08:17:14  ssodhi
 *  LOG: Adding redn trace
 *  LOG:
 *  LOG: Revision 9.16.4.4  2009/04/08 11:31:46  ssodhi
 *  LOG: Adding UAL_RedundancyCallback in REDUNDANCY_CALLBACK_MGR(redClass)
 *  LOG:
 *  LOG: Revision 9.16.4.3  2009/04/02 06:09:15  kramesh
 *  LOG: Fix for Whizible issue 1792. DAUD not started when second DUNA recieved.
 *  LOG:
 *  LOG: Revision 9.16.4.2  2009/03/24 04:11:40  ssodhi
 *  LOG: adding missing \n in trace
 *  LOG:
 *  LOG: Revision 9.16.4.1  2009/03/19 06:46:27  kramesh
 *  LOG: Changes for UAL section persistency.
 *  LOG:
 *  LOG: Revision 9.16  2008/06/30 14:04:18  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.15  2008/06/29 15:13:27  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.14  2008/05/25 17:11:25  kramesh
 *  LOG: Whizible Bug ID 932. Incorrect Routing Key printing.
 *  LOG:
 *  LOG: Revision 9.13  2008/05/01 16:18:31  kramesh
 *  LOG: Propagated Bridgeport issue 1541. Routing Key more than 255.
 *  LOG:
 *  LOG: Revision 9.12  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.11.2.15  2007/07/27 08:55:06  pspl
 *  LOG: Changed for loop counter to send ASP active message in function
 *  LOG: UAL_RedundancyCallback() to fix core dump.(Vipul)
 *  LOG:
 *  LOG: Revision 9.11.2.14  2007/07/06 06:58:35  pspl
 *  LOG: (PSPL, abhijeet) Support added for get/set audTimer from/to XML for SCON-DAUD feature
 *  LOG:
 *  LOG: Revision 9.11.2.13  2007/06/28 12:51:33  pspl
 *  LOG: (PSPL,abhijeet) few cosmetic changes for Point code val in trace logs
 *  LOG:
 *  LOG: Revision 9.11.2.12  2007/06/28 04:38:30  pspl
 *  LOG: (PSPL, abhijeet) minor change - changing UAL_ with UAL_ERRROR
 *  LOG:
 *  LOG: Revision 9.11.2.11  2007/06/26 10:36:41  pspl
 *  LOG: (PSPL, abhijeet) added check for ASP state to be ASP_ACTIVE before
 *  LOG:                  starting of audTimer.
 *  LOG:
 *  LOG: Revision 9.11.2.10  2007/06/22 11:50:36  pspl
 *  LOG: Auditing support for receipt of SSNM message (SCON/DUNA/DRST)
 *  LOG:
 *  LOG: Revision 9.11.2.9  2007/06/12 08:50:53  pspl
 *  LOG: (PSPL, abhijeet) misc changes, return value need not be stored
 *  LOG:
 *  LOG: Revision 9.11.2.8  2007/05/25 07:15:45  pspl
 *  LOG: (PSPL,Manish)
 *  LOG: - UAL_GetRoutingKeys() is changed to extract RK_Contexts instead of rKeys, and renamed
 *  LOG: - Hardcoading of UAL_OVERRIDE_MODE removed
 *  LOG: - Changed the Parameter type of SendASPActive()
 *  LOG:
 *  LOG: Revision 9.11.2.7  2007/05/18 05:54:08  pspl
 *  LOG: (PSPL, abhijeet) added a function to check for valid message type
 *  LOG: and raise 4026 alarm in case of problem
 *  LOG:
 *  LOG: Revision 9.11.2.6  2007/05/10 06:25:44  pspl
 *  LOG: (PSPL, abhijeet) BEAT and BEAT_ACK messages are allowed to pass through to Handler func
 *  LOG:
 *  LOG: Revision 9.11.2.5  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.11.2.4  2007/05/02 08:23:21  pspl
 *  LOG: Changes made in commit command to write UAL Manager node to the new
 *  LOG: configuration file. (Vipul)
 *  LOG:
 *  LOG: Revision 9.11.2.3  2007/04/30 11:13:07  pspl
 *  LOG: (PSPL, Abhijeet) misc changes
 *  LOG:
 *  LOG: Revision 9.11.2.2  2007/04/26 06:55:29  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - added msg.header len check
 *  LOG: - incorporated m3ua event handling for various instances of the APP(ASP/SGP/IPSP-SE..etc)
 *  LOG:   This was borrowed from the new loadline (hence have retained the function header)
 *  LOG:
 *  LOG: Revision 9.11.2.1  2007/04/05 14:48:23  pspl
 *  LOG: ackTimer[indexing] changed from trafficMode value to be msgType value being used
 *  LOG:
 *  LOG: Revision 9.11  2007/01/10 11:15:10  yranade
 *  LOG: Merge changes from 6.5.3 and Lucent branches
 *  LOG:
 *  LOG: Revision 9.10  2005/12/06 22:28:55  cbashyam
 *  LOG: Bug fixes for Bug ID : 2565
 *  LOG:
 *  LOG: Revision 9.9  2005/11/30 23:46:19  clin
 *  LOG: change ITS_TRACE to UAL trace.
 *  LOG:
 *  LOG: Revision 9.8  2005/11/30 15:09:30  clin
 *  LOG: make debug flag works to display ASP/IPSP client its own routing info.
 *  LOG:
 *  LOG: Revision 9.7  2005/11/23 20:19:54  clin
 *  LOG: fix bug #2531
 *  LOG:
 *  LOG: Revision 9.6  2005/11/18 23:23:28  cbashyam
 *  LOG: Bug fix for Bug ID : 2565
 *  LOG:
 *  LOG: Revision 9.5  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.4  2005/05/06 09:27:16  mmanikandan
 *  LOG: PR6.5.1 Validation Bug(1765, 1769, 1773, 1789) Fix.
 *  LOG:
 *  LOG: Revision 9.3  2005/05/05 05:58:43  adutta
 *  LOG: Fix for #1769
 *  LOG:
 *  LOG: Revision 9.2  2005/04/05 10:29:40  adutta
 *  LOG: Fix for Bug#1537
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:47  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:17  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.7  2005/01/11 12:30:07  craghavendra
 *  LOG: Syslog Enhancements.
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.6  2005/01/10 12:46:13  ssingh
 *  LOG: changes in redundancy callback function.
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.5  2005/01/10 06:13:48  ssingh
 *  LOG: commit related to last revision.
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.4  2005/01/07 15:03:05  ssingh
 *  LOG: Changed to enhance ACTIVE-BACKUP redundancy.
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.3  2004/12/25 10:54:23  ssingh
 *  LOG: Fix for Bug No #1331
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.2  2004/12/15 12:12:49  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2.4.1  2004/12/09 15:21:11  snagesh
 *  LOG: Modifications for Chinese variant
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.2  2004/10/06 08:32:50  mmanikandan
 *  LOG: Support for Windows build.
 *  LOG:
 *  LOG: Revision 7.2.2.9.2.1  2004/05/03 12:47:33  ssingh
 *  LOG: Bug#791; correction for UAL_BROADCAST_MODE_STRING mode.
 *  LOG:
 *  LOG: Revision 7.2.2.9  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.2.2.8  2003/10/15 20:50:57  lbana
 *  LOG: fixes for SG crash on reconnects with serveral ASPs
 *  LOG:
 *  LOG: Revision 7.2.2.7  2003/10/15 14:30:52  lbana
 *  LOG: use sctp manager instance for callback events
 *  LOG:
 *  LOG: Revision 7.2.2.6  2003/10/14 20:20:59  lbana
 *  LOG: fixes for TCS: removed begin and end tags for olivier fixes
 *  LOG:
 *  LOG: Revision 7.2.2.5  2003/09/11 00:45:08  lbana
 *  LOG: Code reorganized for Pause/Resumes and test config with 2 linksets.
 *  LOG:
 *  LOG: Revision 7.2.2.4  2003/09/08 19:32:47  lbana
 *  LOG: Added callback info for pause/resume when transport goes Up/Down
 *  LOG:
 *  LOG: Revision 7.2.2.3  2003/08/04 23:17:34  hcho
 *  LOG: fixes in DUNA/DAVA and propagate CANT_START indication to the user.
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/07/11 21:16:01  labuser
 *  LOG: DUNA/DAVA functionality is added.
 *  LOG:
 *  LOG: Revision 7.2.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.2  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.1.2.2  2002/12/26 23:52:04  lbana
 *  LOG: fix missing  open braces while patching
 *  LOG:
 *  LOG: Revision 7.1.2.1  2002/12/26 23:32:26  lbana
 *  LOG: buge fixes in ual in IPSP mode testing
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.18  2002/07/24 19:53:42  lbana
 *  LOG: fix bugs in reconnect logic, and get aspinfo element from parser
 *  LOG: extension.
 *  LOG:
 *  LOG: Revision 6.17  2002/07/22 18:42:06  lbana
 *  LOG: format.
 *  LOG:
 *  LOG: Revision 6.16  2002/07/18 18:25:28  lbana
 *  LOG: add family in AS Context to avoid sequency dependancy in xml file
 *  LOG:
 *  LOG: Revision 6.15  2002/07/16 13:41:09  labuser
 *  LOG: get network indicator from AS info configuration section.
 *  LOG:
 *  LOG: Revision 6.14  2002/07/10 21:36:16  lbana
 *  LOG: remove debug_stub func from ual
 *  LOG:
 *  LOG: Revision 6.13  2002/07/10 21:33:43  lbana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 6.12  2002/07/10 19:42:21  ngoel
 *  LOG: avoid duplicate RK register
 *  LOG:
 *  LOG: Revision 6.11  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 6.10  2002/07/09 22:17:04  ngoel
 *  LOG: add ual console function
 *  LOG:
 *  LOG: Revision 6.9  2002/07/09 21:18:37  lbana
 *  LOG: Start MML procedures for UALs
 *  LOG:
 *  LOG: Revision 6.8  2002/07/01 19:14:11  lbana
 *  LOG: Work in progress
 *  LOG:
 *  LOG: Revision 6.7  2002/05/21 22:16:59  lbana
 *  LOG: more debugging in current...
 *  LOG:
 *  LOG: Revision 6.6  2002/05/17 20:22:06  lbana
 *  LOG: More testing on current.
 *  LOG:
 *  LOG: Revision 6.5  2002/05/15 16:46:41  lbana
 *  LOG: added localPC in ual parser info
 *  LOG:
 *  LOG: Revision 6.4  2002/05/15 16:19:05  lbana
 *  LOG: Add localPC parsing of the resource manager. Compiled the routeHandler
 *  LOG: module.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 20:30:41  lbana
 *  LOG: uals in current starts from here...
 *  LOG:
 *  LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 *  LOG: Begin PR7.
 *  LOG:
 *  LOG: Revision 1.2  2002/01/09 22:31:48  lbana
 *  LOG: remove endofline character appended in dos
 *  LOG:
 *  LOG: Revision 1.1  2002/01/09 21:46:15  lbana
 *  LOG: Baseline for M3UA Draft Version 10 and SUA draft ver 9
 *  LOG:
 ****************************************************************************/

/*
 * UAL starts here !!!
 */
#include <its_ual.h>
#include <its_tq_trans.h>
#include <its_sctp_trans.h>
#include <engine.h>

//#include <m3ua.h>

#include "ual_intern.h"

static THREAD_RET_TYPE     UALThread(void *arg);

static ITS_THREAD   ualThread;

static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;

/* 
 * Globals
 */

UALDLLAPI TQUEUETRAN_Manager* __UAL_RcvQueue = NULL;
static void InitTraceSettings();

extern void (*Ual_CommitFp)(FILE *);

/* 
 * UAL Internal data structures
 */
UALDLLAPI ITS_MUTEX    __ualGuard;        /*to protect ual tables */ 
UALDLLAPI HASH_Table   __UAL_ASP_Table;   /*Keep track of all ASPs*/ 
UALDLLAPI AS_Manager   __UAL_AS_Manager;  /*Keep track of all AS's*/

UALDLLAPI HASH_Table   __UAL_Audit_Timer_Table; /*Keep track of Timers for Auditing*/ 

UALDLLAPI CALLBACK_Manager*   __UAL_MgntCallBack = NULL;
UALDLLAPI CALLBACK_Manager*   __UAL_MTP3MgntCallBack = NULL;
UALDLLAPI CALLBACK_Manager*   __UAL_SCTPMgntCallBack = NULL;

/*
 * Global Data
 */

UALDLLAPI UAL_GLOBALS __ualGlobals = {SCTP_PAYLOAD_M3UA,
                            1,
                            UAL_ITW_SG,
                            UAL_IPSP_TYPE_DOUBLE_EXCHG,
                            2,
                            10,
                            2,
                            5,
                            ITS_FALSE,
                            0, 
                            -1,
                            ITS_FALSE,
                            0,
                            ITS_FALSE,
                            UAL_GL_AUD_TIMER_DEFAULT_VAL 
                            };


UALDLLAPI char* itwStr[] =
{
    "SG",
    "ASP",
    "IPSP"
};

UALDLLAPI char* ITW_STRING;

/*
 * Forward declaration.
 */
UALDLLAPI int UAL_ForwardIndication(ITS_EVENT *UALEvent);
UALDLLAPI int UAL_Commit(FILE* fp);
UALDLLAPI void UAL_ExtensionCommit(FILE* fp);

static TRACE_OutputInitializer fileCritTrace =
{
    UAL_FILE_STRING,
    ITS_TRUE,
    UAL_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    UAL_FILE_STRING,
    ITS_TRUE,
    UAL_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    UAL_FILE_STRING,
    ITS_TRUE,
    UAL_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    UAL_FILE_STRING,
    ITS_TRUE,
    UAL_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    UAL_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    UAL_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer UAL_TraceMap[] =
{
    {UAL_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {UAL_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {UAL_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {UAL_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } }
};

TRACE_Data* UAL_TraceData = NULL;

struct UALConfigVar 
{
    ITS_INT    configCmd;   /* Configuration Command */

    union
    {
        struct              /* For ASP_UP   asp = ASP Transport ID */
        {                   /* For Active   asp = Routing key */
            ITS_UINT asp;   /* For Inactive asp = Routing Key */  
        }                   /* For ASP_Down asp = ASP Transport ID */
        asp_info;

        struct
        {
            ITS_UINT  rStyle;    /* Set Route style */
            ITS_UINT  rkey;      /* Set Routing Key value */
            ITS_UINT  dpc;       /* Set routing key DPC */
            ITS_UINT  opc;       /* Set routing key OPC */
            ITS_UINT  ssn;       /* Set SSN */
            ITS_UINT  sio;       /* Set SIO */
            ITS_UINT  cic;       /* Set CIC */
            ITS_UINT  start;     /* Need to work on this */
            ITS_UINT  end;
            ITS_UINT  family;
            ITS_UINT  tMode;     /* AS Traffic Mode */ 
        }
        rk_info;
    }
    config;
};

typedef struct UALConfigVar *UAL_ConfigPriv;
#define UAL_CONFIG_PRIV_ASP_INFO(x) (((UAL_ConfigPriv)x)->config.asp_info)
extern ITS_BOOLEAN SendASP_INACTIVE(UAL_ConfigPriv info);

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is called to initialize the UAL manager. All the resouces
 *    used in the UAL manager are allocated. Trace, Transport, UAL thread,
 *    Association Manager, AS manager, Routing key manager.
 *   
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 * Mani        05-05-2005  BugId:1765
 *
 ******************************************************************************/
static int
UAL_Initialize(ITS_Class objClass)
{
    int ret1 = ITS_SUCCESS;
    int ret = ITS_SUCCESS;
    void *status;
    ITS_Class redClass;

    if (initialized)
    {
        return (ITS_SUCCESS);
    }

    initialized = ITS_TRUE;

    if ((UAL_TraceData = TRACE_Constructor("UAL",
                                             UAL_TraceMap, 4)) == NULL)
    {
        /* UAL failed to Intialize -  No Memory. */
 
        return (ITS_ENOMEM);
    }

    if( (ret = MUTEX_CreateMutex(&__ualGuard, 0)) != ITS_SUCCESS)
    {
        UAL_CRITICAL(("UAL_Initialize: couldn't create Mutex\n"));

        initialized = ITS_FALSE;

        return ret; 
    }

    if ((__UAL_MTP3MgntCallBack = CALLBACK_InitManager()) == NULL)
    {
        UAL_WARNING(("UAL_Initialize: Could not create MTP3 Mgnt Callback.\n"));
    }
    else
    {
        /* UAL_RegisterMTP3MgntCallbacks(); */
    } 

    if ((__UAL_SCTPMgntCallBack = CALLBACK_InitManager()) == NULL)
    {
        UAL_WARNING(("UAL_Initialize: Could not create SCTP Mgnt Callback.\n"));
    }

    UAL_ASP_ManagementCallbacks = CALLBACK_InitManager();

    if (UAL_ASP_ManagementCallbacks == NULL)
    {
        return (ITS_ENOMEM);
    }

    ret = UAL_InitializeInternalTables();
    
    if ((__UAL_RcvQueue = TQUEUETRAN_CreateTransport("UAL_Manager",
                                                      UAL_MANAGER_INSTANCE,
                                                      ITS_SS7_MASK)) == NULL) 
    {
        UAL_CRITICAL(("UALL_Initialize: couldn't create transport\n"));

        initialized = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    InitTraceSettings();

    if (THREAD_CreateThread(&ualThread, 0, UALThread, NULL, ITS_TRUE)
        != ITS_SUCCESS)
    {
        UAL_CRITICAL(("UAL_Initialize: couldn't create thread\n"));

        TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

        initialized = ITS_FALSE;

        return (ITS_EBADTHREAD);
    }

    if (ret != ITS_SUCCESS)
    {
        UAL_CRITICAL(("UAL_Initialize: could not init tables \n"));

        TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

        THREAD_WaitForThread(&ualThread, &status);

        THREAD_DeleteThread(&ualThread);

        return ret;
    }

    /* register for SCTP Transport callbacks, to receive messages */
    ret = CALLBACK_AddCallback(SCTPTRAN_ManagementCallbacks, 
                               UAL_SCTPTransCallback, NULL);
    if (ret != ITS_SUCCESS)
    {
        UAL_CRITICAL(("UAL_Initialize: could not register for SCTP "
                            "Callback.\n"));

        TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

        THREAD_WaitForThread(&ualThread, &status);

        THREAD_DeleteThread(&ualThread);

        return ret;
    }

    if ( (redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME)) != NULL)
    {
        if ((ret = ITS_InitializeClass(itsREDUNDANCY_Class)) != ITS_SUCCESS)
        {
            UAL_ERROR(("ClassInitialize: Redundancy class init failed\n"));
            return ret;
        }

		ret1 = CALLBACK_AddCallback(REDUNDANCY_CALLBACK_MGR(redClass),
							 UAL_RedundancyCallback, NULL);

        /* register for Redundancy Callback, to receive messages */
        ret = CALLBACK_AddCallback(ITS_RedundancyMgmtCallbacks,
                                   UAL_RedundancyCallback, NULL);
        if ((ret1 != ITS_SUCCESS) || (ret != ITS_SUCCESS))
        {
            UAL_CRITICAL(("UAL_Initialize: could not register for Redundancy "
                                "Callback.\n"));

            TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

            THREAD_WaitForThread(&ualThread, &status);

            THREAD_DeleteThread(&ualThread);

            return ret;
        }
     }

    if ((__UAL_MgntCallBack = CALLBACK_InitManager()) == NULL)
    {
        UAL_ERROR(("UAL_Initialize: Could not create Mgnt CallBack Manager.\n"));

        TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

        THREAD_WaitForThread(&ualThread, &status);

        THREAD_DeleteThread(&ualThread);

        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    DBC_AddDoCommand(UAL_Console);
 
    AddCommitCallback("UAL",UAL_Commit);

    //Initilize Ual_CommitFp.
    Ual_CommitFp = &UAL_ExtensionCommit;
    return (ITS_SUCCESS);
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is called in order to terminate the UAL Manager instance.
 *    All resources used by the UAL manager should be released.
 *     
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *
 *    None.      
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    None.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
static void
UAL_Terminate(ITS_Class objClass)
{
    ITS_EVENT ev;
    void *status;
    ITS_Class dbClass;

    if (!initialized || terminated)
    {
        return;
    }

    terminated = ITS_TRUE;
  
    ev.src = UAL_MANAGER_INSTANCE;
    ev.len = 0;

    /*
     * Just wondering if we should send ASP down to all 
     * association an wait for acks before we take the whole
     * thing down TODO
     */

    TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &ev);

    THREAD_WaitForThread(&ualThread, &status);

    THREAD_DeleteThread(&ualThread);

    ITS_C_ASSERT(__UAL_RcvQueue != NULL);

    TQUEUETRAN_DeleteTransport(__UAL_RcvQueue);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(UAL_Console);
    }

}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *     None.
 *
 *  Output Parameters:
 *
 *     None.
 *
 *  Return Value:
 *
 *
 *  Notes:
 *
 *     None.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * gdevanand 05-03-2005  BugId:1769   change in return value in case of failure 
 *                                    change in traces.
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT UAL_AddASInfoToASManager(RESFILE_Manager *appRes, 
                                 ITS_BOOLEAN fromUser)
{
    ITS_INT ret; 
    RK_Context *asEntry = NULL;
    UAL_ASP_INFO aspInfoArray[64];
    ITS_INT numASP = 0;
    ITS_BOOLEAN inAS, hasTM, hasRK, hasRInfo;
    char var[ITS_PATH_MAX];
    char val[ITS_PATH_MAX];

    ret  = !ITS_SUCCESS;
    inAS = hasTM = hasRK = hasRInfo = ITS_FALSE;

    memset(var, 0, sizeof(char) * ITS_PATH_MAX);
    memset(val, 0, sizeof(char) * ITS_PATH_MAX);

    while (RESFILE_GetKeyName(appRes, UAL_MGNT_CLASS_NAME,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        if (strcmp(var, UAL_AS_INFO_STRING) == 0)
        {
            if (strstr(val, "begin") != NULL)
            {
                hasTM = hasRK = hasRInfo = ITS_FALSE;

                asEntry = (RK_Context*)calloc(1, sizeof(RK_Context));

                if (asEntry != NULL)
                {
                    memset(aspInfoArray, 0, (64 * sizeof(UAL_ASP_INFO)));

                    numASP = 0;

                    asEntry->isMember = ITS_FALSE;

                    inAS = ITS_TRUE;
                }
                else
                {
                    UAL_CRITICAL(("UALThread: Failed to allocate memory\n"));

                    inAS = ITS_FALSE;

                    break;
                }
            }
            else if (strstr(val, "end") != NULL)
            {
                if (inAS && hasTM && hasRK && hasRInfo)
                {
                    int i = 0;

                    /* add an entry to AS table */

                    if(RKManager_FindEntry(asEntry->rCtxt))
                    {
                        if (!UAL_IS_IPSP_SINGLE_EXCHG(UAL_GL_IPSP_TYPE))
                        {
                            UAL_WARNING(("Routing Context %u is already present\n",
                                         asEntry->rCtxt));
                            free(asEntry);

                            asEntry = NULL;
                            continue;
                        }
                    }
                    else
                    {
                        ret = RKManager_AddEntry(asEntry->rCtxt, asEntry);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("Error adding AS entry, "
                                         "RK = %u\n", asEntry->rCtxt));
                            continue;
                        }
                        else 
                        {
                            UAL_DEBUG(("Adding AS entry, "
                                         "RK = %u\n", asEntry->rCtxt));
                        }
                    }

                    /* populate the list of ASP if ASPID provided */
                    for (i = 0; i < numASP; i++)
                    {
                        ASPListNode aspEntry; 

                        memset(&aspEntry, 0, sizeof(ASPListNode));

                        if (asEntry->aspList == NULL)
                        {
                            asEntry->aspList = UAL_CreateList();
                        }

                        aspEntry.aspInfo = aspInfoArray[i];

                        ret = ASPList_AddEntry(asEntry->aspList, &aspEntry);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("Error adding to ASP List\n"));
                        }
                    }

                    /*
                     * need to add linkSet and Destiantion for the new AS 
                     * only for SG or IPSP
                     */
                     if (UAL_GL_ITW_MODE != UAL_ITW_ASP)
                     {
                          ret = UAL_AddLinkSetAndDestination(asEntry);
                          if (ret != ITS_SUCCESS)
                          {
                             UAL_ERROR(("Error Adding LinkSet and Destination "
                                             "for RK %u\n", asEntry->rCtxt));
                          }
                      }

                      inAS = ITS_FALSE;

                      asEntry = NULL;
                 }
            }
            else 
            {
                free(asEntry);
                asEntry = NULL;
            }

            continue;
        }
        else if (strcmp(var, UAL_IS_MEMBER_STRING) == 0)
        {
            if (strstr(val, "yes") != NULL)
            {
                if (asEntry != NULL)
                {
                    asEntry->isMember = ITS_TRUE;
                }
            }
                
            continue; 
        } 
        else if (strcmp(var, ROUTING_KEY_STRING) == 0)
        {
            if (asEntry != NULL)
            {
                ROUTE_Info **rinfo;

                hasRK = ITS_TRUE;

                asEntry->rCtxt = RESFILE_ParseNum(val);

                ret = ROUTE_FindRoutingKeyInfo(asEntry->rCtxt, &rinfo);
                if (ret != ITS_SUCCESS)
                {
                     UAL_ERROR(("UALThread: could not obtain rInfo "
                                      "from Routing Ctxt: %u\n", 
                                      asEntry->rCtxt));
                     continue;
                }

                asEntry->asInfo = (*rinfo)->basic;

                asEntry->asInfo.type = REMOTE_ROUTE;

                hasRInfo = ITS_TRUE;
            }

            continue;
        }
        else if (strcmp(var, UAL_ASP_ID_STRING) == 0)
        {
            if (asEntry != NULL)
            {
                if (strcmp(val, "-1") != 0)
                {
                    aspInfoArray[numASP].aspid = RESFILE_ParseNum(val);
                }
                else
                {
                    aspInfoArray[numASP].aspid = -1;
                }
                numASP++;
            }

            continue;
        }
        else if(strcmp(var, FAMILY_STRING) == 0)
        {
            if(asEntry != NULL)
            {
                asEntry->family = strdup(val);
            }
        }
        else if (strcmp(var, UAL_HOME_STRING) == 0)
        {
            if (asEntry != NULL)
            {
                SOCK_IPv4Addr ipAddrs;
                ITS_UINT numHome = aspInfoArray[numASP - 1].numHome;

                ret = SOCK_IPv4NameToAddr(val, &ipAddrs);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error reading IP address\n"));
 
                    continue;
                }

                aspInfoArray[numASP - 1].home[numHome] = ipAddrs;

                aspInfoArray[numASP - 1].numHome++;
            }

            continue;
        }
        else if (strcmp(var, UAL_N_REDUNDANCY_STRING) == 0)
        {
             if (asEntry != NULL)
             {
                 asEntry->nActives = RESFILE_ParseNum(val);
             }

            continue;
        }
        else if (strcmp(var, UAL_K_REDUNDANCY_STRING) == 0)
        {
            if (asEntry != NULL)
            {
                asEntry->kStandby = RESFILE_ParseNum(val);
            }

            continue;
        }
        else if(strcmp(var, UAL_NI_STRING) == 0)
        {
            if(asEntry != NULL)
            {
                asEntry->na.na = RESFILE_ParseNum(val);
            }

            continue;
        }
        else if (strcmp(var, UAL_ASP_CAPABILITIES_STRING ) == 0)
        {
            if (asEntry != NULL)
            {
                if (strstr(val, UAL_CAPAB_CLASS0_STRING) != NULL)
                {
                    asEntry->aspCapab.protClass = SUA_PROT_CLASS0_FLAG;
                }
                else if (strstr(val, UAL_CAPAB_CLASS1_STRING) != NULL)
                {
                    asEntry->aspCapab.protClass = SUA_PROT_CLASS1_FLAG;
                }
                else if (strstr(val, UAL_CAPAB_CLASS2_STRING) != NULL)
                {
                    asEntry->aspCapab.protClass = SUA_PROT_CLASS2_FLAG;
                }
                else if (strstr(val, UAL_CAPAB_CLASS3_STRING) != NULL)
                {
                    asEntry->aspCapab.protClass = SUA_PROT_CLASS3_FLAG;
                }
                else
                {
                    asEntry->aspCapab.protClass = 0;

                    continue;
                }

            }

            continue;
        }
        else if (strcmp(var, UAL_AS_TRAFFIC_MODE_STRING) == 0)
        {
            if (asEntry != NULL)
            {
                if (strstr(val, UAL_OVERIDE_MODE_STRING) != NULL)
                {
                    asEntry->trafficMode = UAL_OVERRIDE;
                }
                else if (strstr(val, UAL_LOAD_SHARE_MODE_STRING) != NULL)
                {
                    asEntry->trafficMode = UAL_LOADSHARE;
                }
                else if (strstr(val, UAL_BROADCAST_MODE_STRING) != NULL)
                {
                    asEntry->trafficMode = UAL_BROADCAST;
                }
                else
                {
                    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || 
                             (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))) 
                    {
                        hasTM = ITS_TRUE;
                    }
                    else
                    {
                        UAL_ERROR(("Traffice mode is not supported.\n"));
                        hasTM = ITS_FALSE;
                        continue;
                    }
                }
                hasTM = ITS_TRUE;
           }
           continue;
        }
    }

    if (fromUser == ITS_TRUE)
    {	
        return ret;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *    This function is the main function for the UAL manager thread. first
 *    configuration parameters are read from the ressource manager, then the
 *    function enters a forever loop performing GetNextEvent on the UAL
 *    TQUEUE transport.
 *     
 *  Input Parameters:
 *    arg - argument list.
 *
 *  Input/Output Parameters:
 *    None.
 *
 *  Output Parameters:
 *    None.
 *
 *  Return Value:
 *    THREAD_RET_TYPE      
 *
 *  Notes:
 *    None.
 *
 *  See Also:
 *    None.
 *
 ******************************************************************************/
static THREAD_RET_TYPE
UALThread(void *arg)
{
    ITS_EVENT UALEvent;
    ITS_BOOLEAN cont = ITS_TRUE;
    int ret = ITS_SUCCESS;

    TRANSPORT_Control* base = NULL; 

    ITS_EVENT_INIT(&UALEvent, 0, 0);

    base = (TRANSPORT_Control*)__UAL_RcvQueue;

    /*
     * Get info from INI files
     */
    if (TRANSPORT_RES(__UAL_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__UAL_RcvQueue);
        char *name = TRANSPORT_NAME(__UAL_RcvQueue);

        /* Get the interworking from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_INTERWORK_MODE_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (strstr(value, UAL_SG_MODE_STRING) != NULL)
            {
                UAL_GL_ITW_MODE = UAL_ITW_SG;
            }
            else if (strstr(value, UAL_IPSP_MODE) != NULL)
            {
                UAL_GL_ITW_MODE = UAL_ITW_IPSP;
            }
            else
            {
                UAL_GL_ITW_MODE = UAL_ITW_ASP;
            }

	    ITW_STRING = itwStr[UAL_GL_ITW_MODE];
        }

        /* Set the IPSP exchange type */
        if (RESFILE_GetKeyValueOf(res, name, UAL_IPSP_TYPE_STRING, 
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_IPSP_TYPE = RESFILE_ParseNum(value);
        }
        else if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
        {
            UAL_ERROR(("Required IPSP Single/Double exchange mode.\n"));
            UAL_GL_IPSP_TYPE = UAL_IPSP_TYPE_NONE;
            THREAD_NORMAL_EXIT;
        }

        /* Get the HeartBeat info */
        if (RESFILE_GetKeyValueOf(res, name, UAL_HEARTBEAT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (strstr(value, "on") != NULL)
            {
                UAL_GL_HB_FLAG = ITS_TRUE;

                if (RESFILE_GetKeyValueOf(res, name, UAL_HB_INTERVAL_STRING,
                                          value, ITS_PATH_MAX) == ITS_SUCCESS)
                {
                    UAL_GL_HB_INTER = RESFILE_ParseNum(value);
                }
            }
        }

        /* Get the ack timer from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_ACK_TIMER_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_ACK_TIMER = RESFILE_ParseNum(value);
        }

	/* Get the aud timer from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_AUD_TIMER_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_AUD_TIMER = RESFILE_ParseNum(value);
        }

        /* Get the retry count from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_RETRY_COUNTER_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_NUM_RETRY = RESFILE_ParseNum(value);
        }

        /* Get the pending timer from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_PENDING_TIMER_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_PEND_TIMER = RESFILE_ParseNum(value);
        }

        /* Get the UAL version from config */
        if (RESFILE_GetKeyValueOf(res, name, UAL_VERSION_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_VERSION = (ITS_OCTET)(RESFILE_ParseNum(value) & 0xFF);
        }
        
        if (RESFILE_GetKeyValueOf(res, name, UAL_ASP_ID_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (UAL_GL_ITW_MODE != UAL_ITW_SG)
            {
                /* we need to support id 0, use "-1" to distinguish
                   the value is being configured or not */
                if (strcmp(value, "-1") != 0)
                {
                    UAL_GL_ASP_ID = RESFILE_ParseNum(value);
                }
            }
        }

        if (RESFILE_GetKeyValueOf(res, name, UAL_LOCAL_PC_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            UAL_GL_LOCAL_PC = RESFILE_ParseNum(value);
        }
        else
        {
            UAL_CRITICAL(("Config Missing Local PC parameter Exiting !!! \n"));

            THREAD_NORMAL_EXIT;
        }

        if (RESFILE_GetKeyValueOf(res, name, UAL_DEBUG_FLAG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (RESFILE_ParseNum(value))
            {
                UAL_GL_DEBUG_FLAG = ITS_TRUE;
            }
            else
            {
                UAL_GL_DEBUG_FLAG = ITS_FALSE;
            }
        }

        if (RESFILE_GetKeyValueOf(res, name,
                                  UAL_PROPAG_MGNT_MSG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (strstr(value, "yes") != NULL)
            {
                UAL_PROPAGATE_MGNT = ITS_TRUE;
            }
        }
        
        /* 
         * Take care of RK static configurarion
         */
        
        ret = RESFILE_Rewind(TRANSPORT_RES(base), TRANSPORT_NAME(base));
        if (ret != ITS_SUCCESS)
        {
            UAL_CRITICAL(("Could not rewind section !!!\n"));

            THREAD_NORMAL_EXIT;
        }

        /* Acquire mutex before manipulating the tables */
        if( (ret = MUTEX_AcquireMutex(&__ualGuard)) != ITS_SUCCESS)
        {
            UAL_ERROR(("Failed to acquire mutex, Exiting UAL_Thread.\n"));

            THREAD_NORMAL_EXIT;
        }

        ret = UAL_AddASInfoToASManager(TRANSPORT_RES(base), ITS_FALSE);

        if( (ret = MUTEX_ReleaseMutex(&__ualGuard)) != ITS_SUCCESS)
        {
            UAL_ERROR(("Failed to release mutex. Exiting UAL_Thread.\n"));

            THREAD_NORMAL_EXIT;
        }
    }
    else
    {
        UAL_CRITICAL(("UALThread: UAL Transport Instance is NULL, "
                            "exiting thread\n"));

        THREAD_NORMAL_EXIT;
    }

    UAL_DEBUG(("UALThread: Entering event loop.\n"));

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__UAL_RcvQueue))
                                                        (__UAL_RcvQueue,
                                                         &UALEvent)
           == ITS_SUCCESS)
    {
        PRINT_EVENT(&UALEvent);

        /* Acquire mutex before manipulating the tables */
        if( (ret = MUTEX_AcquireMutex(&__ualGuard)) != ITS_SUCCESS)
        {
            UAL_ERROR(("Failed to acquire mutex, Exiting UAL_Thread.\n"));

            THREAD_NORMAL_EXIT;
        }

        switch (UALEvent.src)
        {
        case ITS_TIMER_SRC:
        {   
            ITS_TimerData td;
            
            UAL_DEBUG(("UALThread: handle TIMER msg.\n"));

            ITS_C_ASSERT(UALEvent.len <= sizeof(ITS_TimerData));

            memcpy(&td, UALEvent.data, UALEvent.len);
          
            UAL_HandleTimerEvent(&td);
 
            break;
        }
        case UAL_MANAGER_INSTANCE: /* Termination event */

            UAL_DEBUG(("UALThread: handle termination event.\n"));

            cont = ITS_FALSE;

            break;

        case ITS_MTP3_ANSI_SRC:
        case ITS_MTP3_CCITT_SRC:
        case ITS_MTP3_PRC_SRC:
        case ITS_MTP3_TTC_SRC:
            
            ret = UAL_ForwardIndication(&UALEvent);
            if (ret != ITS_SUCCESS)
            {
               UAL_ERROR(("UAL_ForwardIndication: Failed to forward "
                                "MTP3 Msg to ASP.\n"));
            }

            break;

        case SCTP_MANAGER_INSTANCE:
            {
                UAL_DEBUG(("UALThread: handle SCTP EVENT. %d\n ", UALEvent.data[2]));
                UAL_HandleSCTPIndication(&UALEvent);
            }
	    break;

        default:
            base = TRANSPORT_FindTransport(UALEvent.src);
            TRANSPORT_UnfindTransport(base);

            if(ITS_IsInstanceOf((ITS_Class)itsSCTPTRAN_LocalEndPointClass, 
                                (ITS_Object)base) ||
               ITS_IsInstanceOf((ITS_Class)itsSCTPTRAN_RemoteEndPointClass, 
                                (ITS_Object)base))
            { 
                UAL_DEBUG(("UALThread: handle SCTP msg.\n"));

                UAL_HandleSCTPDataMsg(&UALEvent);
            }
            else   /* message from the user or Layer Management */
            {
                ret = UAL_HandleLayerMgntMsg(&UALEvent);

                if (ret != ITS_SUCCESS)
                {
                   UAL_ERROR(("UAL_HandleLayerMgntMsg: Error Handling "
                                    "Usr Msg.\n"));
                }
             }

            break;
        }

        if( (ret = MUTEX_ReleaseMutex(&__ualGuard)) != ITS_SUCCESS)
        {
            UAL_ERROR(("Failed to release mutex. Exiting UAL_Thread.\n"));

            THREAD_NORMAL_EXIT;
        }

		//ITS_EVENT_TERM(&UALEvent);
    }

    UAL_DEBUG(("UALThread: exiting UAL thread. \n"));

    THREAD_NORMAL_EXIT;

}

/*
 * This functions checks if the message has valid message type field.
 * If not then it raises an alarm and sends back and ERR message.
 */
ITS_INT ValidateMessageType(ITS_INT msgClass, ITS_INT msgType, ITS_INT trId)
{
    ITS_INT retVal = ITS_SUCCESS;
    switch(msgClass)
    {
        case UAL_CLASS_MGMT:
            switch(msgType)
            {
                case UAL_MSG_NOTIFY:
                case UAL_MSG_ERR:
                    break;
                default:
                    UAL_DEBUG(("ValidateMessageType: Received Unexpected message Type (%d)\n", msgType));
                    UAL_Alarm(4026, __FILE__, __LINE__, "msgClass (%d) , msgType(%d) on TransportId %x", msgClass, msgType, trId);
                    UAL_SendERR(trId, UAL_ERR_UNSUP_MSG_TYPE, NULL, 0);
                    retVal = !ITS_SUCCESS;
                    break;
            }
            break;
        case UAL_CLASS_ASPSM:
            switch(msgType)
            {
                case UAL_MSG_ASPUP:
                case UAL_MSG_ASPUP_ACK:
                case UAL_MSG_ASPDN:
                case UAL_MSG_ASPDN_ACK:
                case UAL_MSG_BEAT:
                case UAL_MSG_BEAT_ACK:
                    break;
                default:
                    UAL_DEBUG(("ValidateMessageType: Received Unexpected message Type (%d)\n", msgType));
                    UAL_Alarm(4026, __FILE__, __LINE__, "msgClass (%d) , msgType(%d) on TransportId %x", msgClass, msgType, trId);
                    UAL_SendERR(trId, UAL_ERR_UNSUP_MSG_TYPE, NULL, 0);
                    retVal = !ITS_SUCCESS;
                    break;
            }
            break;
        case UAL_CLASS_ASPTM:
            switch(msgType)
            {
                case UAL_MSG_ASPAC:
                case UAL_MSG_ASPAC_ACK:
                case UAL_MSG_ASPIA:
                case UAL_MSG_ASPIA_ACK:
                    break;
                default:
                    UAL_DEBUG(("ValidateMessageType: Received Unexpected message Type (%d)\n", msgType));
                    UAL_Alarm(4026, __FILE__, __LINE__, "msgClass (%d) , msgType(%d) on TransportId %x", msgClass, msgType, trId);
                    UAL_SendERR(trId, UAL_ERR_UNSUP_MSG_TYPE, NULL, 0);
                    retVal = !ITS_SUCCESS;
                    break;
            }
            break;
        case UAL_CLASS_RKM:
            switch(msgType)
            {
                case UAL_MSG_REG_REQ:
                case UAL_MSG_REG_RSP:
                case UAL_MSG_DEREG_REQ:
                case UAL_MSG_DEREG_RSP:
                    break;
                default:
                    UAL_DEBUG(("ValidateMessageType: Received Unexpected message Type (%d)\n", msgType));
                    UAL_Alarm(4026, __FILE__, __LINE__, "msgClass (%d) , msgType(%d) on TransportId %x", msgClass, msgType, trId);
                    UAL_SendERR(trId, UAL_ERR_UNSUP_MSG_TYPE, NULL, 0);
                    retVal = !ITS_SUCCESS;
                    break;   
            }
            break;
        default:
            /** this case will be handled by the caller **/
            break;
    }

    return retVal;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   This function is used to handle SCTP data messages. That is it sends
 *   the message to the correct handler according to the message class.
 *
 *  Input Parameters:
 *
 *   UALEvent - a pointer to the ITS_EVENT received from SCTP.
 *
 *  Input/Output Parameters:
 *
 *   None.
 *
 *  Output Parameters:
 *
 *   None.
 *
 *  Return Value:
 *
 *   ITS_SUCCESS - in case no error occured, any other return value indicates
 *   an error condition.
 *
 *  Notes:
 *
 *   None.
 *
 *  See Also:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 *  Name         Date        Reference     Description
 * -----------------------------------------------------------------------------
 *  skatta      01-22-2007                Avoid sending back error message for
 *                                        received error message with invalid
 *                                        version. (RFC3332bis06)
 *
 *  clin        02-04-2007                Correct trace
 *
 *  clin        02-05-2007                Implement event handler, only process
 *                                        the valid message in valid state.
 *
 * skatta       02-06-2007                Check for length of unsupported msg
 *                                        while sending diagnostic Information.
 *
 *  clin        02-06-2007                correct typo in debug trace
 *
 *  clin        02-07-2007                update event handler for
 *                                        IPSP-SE-client and IPSP-DE-client
 *
 *  skatta      02-19-2007                support for both RFC3332 and bis06
 *
 *  skatta      02-21-2007                Fixes for IPSP SE and DE clients
 ******************************************************************************/
UALDLLAPI int
UAL_HandleSCTPDataMsg(ITS_EVENT *ualEvent)
{
    ITS_INT     ret = ITS_SUCCESS;
    UAL_MSG_HDR msgHdr;
    ASP_Entry*  aspRec = NULL;
    ITS_UAL_IE diagnInfo;
    ITS_BOOLEAN unknownMsgClass = ITS_FALSE;

    /* 1) first get the common message header */
    memcpy(&msgHdr, ualEvent->data, sizeof(UAL_MSG_HDR));
    UAL_NComHdrToH(&msgHdr);

    UAL_DEBUG(("UAL_HandleSCTPDataMsg:\n"));

    /* 2) Get ASP_Entry from the Event src TODO */
    ret = ASPTable_FindEntry(ualEvent->src, &aspRec);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_HandleSCTPDataMsg:\n"));
    }

    if (aspRec == NULL)
    {
        UAL_ERROR(("UAL_HandleSCTPDataMsg: could not find Assoc Entry: "
                   "%d.\n", ualEvent->src));
        return ret;
    }

    if(msgHdr.version != UAL_GL_VERSION)
    {
        UAL_ERROR(("UAL_HandleSCTPDataMsg:Invalid Header Version\n"));
        if(msgHdr.msgClass != UAL_CLASS_MGMT &&
           msgHdr.msgType != UAL_MSG_ERR)
        {
            ret = UAL_SendERR(aspRec->trId, UAL_ERR_INV_VESION, NULL, 0);
        }
        return !ITS_SUCCESS;
    }

    /*Checking Header Length*/ 
    if(msgHdr.msgLen < sizeof(UAL_MSG_HDR))
    {
        UAL_ERROR(("UAL_HandleSCTPDataMsg:Invalid Header Legnth\n"));
        ret = UAL_SendERR(aspRec->trId, UAL_ERR_PROT_ERROR, NULL, 0);
        return !ITS_SUCCESS;
    }

    /* Check the Message type to be valid */
    if(ValidateMessageType(msgHdr.msgClass, msgHdr.msgType, aspRec->trId) != ITS_SUCCESS)
    {
        return !ITS_SUCCESS;
    }
    /*
     *  SG (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_RESP]          |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [DEREG_RESP]        |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     */

    if (UAL_IS_APP_SGP(UAL_GL_ITW_MODE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP ||
                           msgHdr.msgType == UAL_MSG_ASPDN ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                        msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                        UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                        break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP ||
                           msgHdr.msgType == UAL_MSG_ASPDN ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent, msgHdr.msgType,
                                              aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ASPAC ||
                            msgHdr.msgType == UAL_MSG_ASPIA)
                        {
                            ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_REG_REQ ||
                            msgHdr.msgType == UAL_MSG_DEREG_REQ)
                        {
                            ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                   aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling RKM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                        break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP ||
                           msgHdr.msgType == UAL_MSG_ASPDN ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                          msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                         if (msgHdr.msgType == UAL_MSG_ASPAC ||
                             msgHdr.msgType == UAL_MSG_ASPIA)
                         {
                             ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                             if (ret != ITS_SUCCESS)
                             {
                                 UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                            "handling ASPTM message\n"));
                             }
                         }
                         else
                         {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                         }

                         break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                         if (msgHdr.msgType == UAL_MSG_REG_REQ ||
                             msgHdr.msgType == UAL_MSG_DEREG_REQ)
                         {
                             ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                             if (ret != ITS_SUCCESS)
                             {
                                 UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                            "handling RKM message\n"));
                             }
                         }
                         else
                         {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                         }

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            default:

                break;
        }
    }


    /*
     *  ASP (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [REG_RESP]          |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [DEREG_RESP]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     */

    else if (UAL_IS_APP_ASP(UAL_GL_ITW_MODE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP_ACK ||
                           msgHdr.msgType == UAL_MSG_ASPDN_ACK ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                        msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                        UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                        break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP_ACK ||
                           msgHdr.msgType == UAL_MSG_ASPDN_ACK ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent, msgHdr.msgType,
                                              aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ASPAC_ACK ||
                            msgHdr.msgType == UAL_MSG_ASPIA_ACK)
                        {
                            ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_REG_RSP ||
                            msgHdr.msgType == UAL_MSG_DEREG_RSP)
                        {
                            ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                   aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling RKM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                        break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType == UAL_MSG_ASPUP_ACK ||
                           msgHdr.msgType == UAL_MSG_ASPDN_ACK ||
			   msgHdr.msgType == UAL_MSG_BEAT ||
			   msgHdr.msgType == UAL_MSG_BEAT_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                          msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                         if (msgHdr.msgType == UAL_MSG_ASPAC_ACK ||
                             msgHdr.msgType == UAL_MSG_ASPIA_ACK)
                         {
                             ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                             if (ret != ITS_SUCCESS)
                             {
                                 UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                            "handling ASPTM message\n"));
                             }
                         }
                         else
                         {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                         }

                         break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                         if (msgHdr.msgType == UAL_MSG_REG_RSP ||
                             msgHdr.msgType == UAL_MSG_DEREG_RSP)
                         {
                             ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                             if (ret != ITS_SUCCESS)
                             {
                                 UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                            "handling RKM message\n"));
                             }
                         }
                         else
                         {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                         }

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            default:

                break;
        }
    }


    /*
     *  IPSP-SE-client (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |    ERR       |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |               |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |     ?         |     ?
     * --------------------+--------------+---------------+--------------
     * [REG_RESP]          |    DISCARD   |     ?         |     ?
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |     ?         |     ?
     * --------------------+--------------+---------------+--------------
     * [DEREG_RESP]        |    DISCARD   |     ?         |     ?
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     *
     * Note: For our implementation, IPSP-SE-server will not trigger
     *       ASP_UP due to isClient flag. If the other vendor peer node
     *       trigger the ASP_UP, we should not process it
     */

    else if (UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType != UAL_MSG_ASPUP)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                        msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                        UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                        break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType != UAL_MSG_ASPUP)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                                 msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

/* For IPSP SE client, to Handle ASP_ACTIVE Message in ASP_INACTIVE state,
   The following portions are commented */

#if 0
                        if (msgHdr.msgType != UAL_MSG_ASPAC)
                        {
#endif
                            ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                            }
#if 0
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }
#endif
                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling RKM message\n"));
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                        break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType != UAL_MSG_ASPUP)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                          msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

/* For IPSP SE client, to Handle ASP_ACTIVE Message in ASP_ACTIVE state,
   The following portions are commented */
#if 0
                         if (msgHdr.msgType != UAL_MSG_ASPAC)
                         {
#endif
                             ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                             if (ret != ITS_SUCCESS)
                             {
                                 UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                            "handling ASPTM message\n"));
                             }
#if 0
                         }
                         else
                         {
                             ret = UAL_SendERR(aspRec->trId,
                                               UAL_ERR_UNEPECTED_MSG, NULL, 0);
                         }
#endif
                         break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                         ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                        "handling RKM message\n"));
                         }

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            default:

                break;
        }
    }


    /*
     *  IPSP-DE-client (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |              |               |    ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     *
     * Note: For our implementation, IPSP-DE-server will not trigger
     *       ASP_UP due to isClient flag. If the other vendor peer node
     *       trigger the ASP_UP, we should not process it
     */

    else if (UAL_IS_IPSP_DE_CLIENT(UAL_GL_IPSP_TYPE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

/* For IPSP DE client, to Handle ASPUP Message in ASP_DOWN state,
   The following portions are commented */

#if 0
                        if(msgHdr.msgType != UAL_MSG_ASPUP)
                        {
#endif
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
#if 0
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }
#endif
                        break;

                     case UAL_CLASS_ASPTM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                         UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                         break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

/* For IPSP DE client, to Handle ASPUP Message in ASP_INACTIVE state,
   The following portions are commented */

#if 0
                        if(msgHdr.msgType != UAL_MSG_ASPUP)
                        {
#endif
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                         msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
#if 0
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }
#endif
                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                         ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                        "handling ASPTM message\n"));
                         }

                         break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                         ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                        "handling RKM message\n"));
                         }

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                               msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                     case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                         ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                        "handling ASPTM message\n"));
                         }

                         break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                         ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                         if (ret != ITS_SUCCESS)
                         {
                             UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                        "handling RKM message\n"));
                         }

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            default:

                break;
        }
    }


    /*
     *  IPSP-SE-server (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |              |               |  (ACK + ERR)
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |     ERR      |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |     ERR       |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |      ?        |      ?
     * --------------------+--------------+---------------+--------------
     * [REG_RESP]          |    DISCARD   |      ?        |      ?
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |      ?        |      ?
     * --------------------+--------------+---------------+--------------
     * [DEREG_RESP]        |    DISCARD   |      ?        |      ?
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     */

    else if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if(msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                        msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                        UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                        break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent, msgHdr.msgType,
                                              aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPAC_ACK)
                        {
                            ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                               UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling RKM message\n"));
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                          msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPAC_ACK)
                        {
                            ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling RKM message\n"));
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                        break;
                }

                break;

            default:

                break;
        }
    }


    /*
     *  IPSP-DE-server (message receive from remote)
     *
     *
     *                     |  [ASP-DOWN]  | [ASP-INACTIVE]| [ASP-ACTIVE]
     * --------------------+--------------+---------------+--------------
     * [ASP_UP]            |              |               |  (ACK + ERR)
     * --------------------+--------------+---------------+--------------
     * [ASP_UP_ACK]        |     ERR      |      ERR      |     ERR
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_DOWN_ACK]      |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT]              |              |               |
     * --------------------+--------------+---------------+--------------
     * [BEAT_ACK]          |              |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_ACTIVE_ACK]    |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE]      |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [ASP_INACTIVE_ACK]  |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_REQ]           |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [REG_RESP]          |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [DEREG_REQ]         |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [DEREG_RESP]        |    DISCARD   |               |
     * --------------------+--------------+---------------+--------------
     * [NOTIFY]            |    DISCARD   |               |
     *---------------------+--------------+---------------+--------------
     * [ERROR]             |              |               |
     *---------------------+--------------+---------------+--------------
     */

    else if (UAL_IS_IPSP_DE_SERVER(UAL_GL_IPSP_TYPE))
    {
        switch(aspRec->state)
        {
            case UAL_ASP_DOWN:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType == UAL_MSG_ERR)
                        {
                            ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);
                        }
                        else
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                        "message is discarded.\n"));
                        }

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                            msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                   "Traffic Maintenace Msg type class %02x "
                                   " in ASP state %d.\n", msgHdr.msgClass,
                                   aspRec->state));

                        UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                    "message is discarded.\n"));

                        break;

                     case UAL_CLASS_RKM:
                         UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                    " Msg type class %02x in ASP state %d.\n",
                                    msgHdr.msgClass, aspRec->state));

                          UAL_ERROR(("UAL_HandleSCTPDataMsg: Illegal message, "
                                     "message is discarded.\n"));

                         break;

                     default:
                         unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_INACTIVE:
                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent, msgHdr.msgType,
                                              aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }

                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling ASPTM message\n"));
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling RKM message\n"));
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                         break;
                }

                break;

            case UAL_ASP_ACTIVE:

                switch(msgHdr.msgClass)
                {
                    case UAL_CLASS_MGMT:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL Mgmt "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleManagementClassMsg(ualEvent,
                                              msgHdr.msgType, aspRec);

                        break;

                    case UAL_CLASS_ASPSM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL ASPSM "
                                   "Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        if (msgHdr.msgType != UAL_MSG_ASPUP_ACK)
                        {
                            ret = UAL_HandleStateMaintMsg(ualEvent,
                                          msgHdr.msgType, aspRec);
                            if (ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPSM message\n"));
                            }
                        }
                        else
                        {
                            ret = UAL_SendERR(aspRec->trId,
                                              UAL_ERR_UNEPECTED_MSG, NULL, 0);
                        }
                        break;

                    case UAL_CLASS_ASPTM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL "
                                    "Traffic Maintenace Msg type class %02x "
                                    " in ASP state %d.\n", msgHdr.msgClass,
                                    aspRec->state));

                        ret = UAL_HandleTrafficMaintMsg(ualEvent,
                                             msgHdr.msgType, aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                           "handling ASPTM message\n"));
                        }

                        break;

                    case UAL_CLASS_RKM:
                        UAL_DEBUG(("UAL_HandleSCTPDataMsg: Recieved UAL RKM "
                                   " Msg type class %02x in ASP state %d.\n",
                                   msgHdr.msgClass, aspRec->state));

                        ret = UAL_HandleRKMMsg(ualEvent, msgHdr.msgType,
                                                    aspRec);
                        if (ret != ITS_SUCCESS)
                        {
                            UAL_ERROR(("UAL_HandleSCTPDataMsg: Error "
                                       "handling RKM message\n"));
                        }

                        break;

                    default:
                        unknownMsgClass = ITS_TRUE;

                        break;
                }

                break;

            default:

                break;
        }
    }

    if (unknownMsgClass)
    {
        UAL_ERROR(("UAL_HandleSCTPDataMsg: Recieved unknown message:"
                   " Msg type class %02x.\n", msgHdr.msgClass));

        /*Build and send Diagnostic Info param*/
        diagnInfo.param_id = UAL_PRM_DIAGNOSTIC;
        if(ualEvent->len < UAL_MAX_DIAG_INFO_LEN)
        {
           diagnInfo.param_length = ualEvent->len;
           memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                  ualEvent->data, ualEvent->len);
        }
        else
        {
           diagnInfo.param_length = UAL_MAX_DIAG_INFO_LEN;
           memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                  ualEvent->data, UAL_MAX_DIAG_INFO_LEN);
        }
        ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNSUP_MSG_CLASS,
                 &diagnInfo, 1);
    }

    return ret;
}


UALDLLAPI int
UAL_ForwardIndication(ITS_EVENT *UALEvent)
{
    int ret = ITS_SUCCESS, size = UAL_MAX_NUM_ASSOC, avail = 0;
    ITS_USHORT tridArray[UAL_MAX_NUM_ASSOC];
    int i = 0;
    ITS_EVENT event;
    
    ret = ASPTable_GetAllTransportIds(tridArray, size, &avail);
    if (ret |= ITS_SUCCESS)
    {
        UAL_ERROR(("Error Traversing ASP_Table.\n"));

        return ret;
    }

    for (i = 0; i < avail; i++)
    {
        ITS_EVENT_INIT(&event, ITS_DEFAULT_USER_SRC, UALEvent->len);

        memcpy(event.data, UALEvent->data, UALEvent->len);

        ret = TRANSPORT_PutEvent(tridArray[i], &event);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("TRANSPORT_PutEvent Failed \n"));
        }

	if(UALEvent->data[0] == MTP3_MSG_PAUSE)
	{
	    UAL_DEBUG(("========== got MTP3_MSG_PAUSE\n"));
	    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_PAUSE_IND_ID);
	}
	else if (UALEvent->data[0] == MTP3_MSG_RESUME)
	{
	    UAL_DEBUG(("========== got MTP3_MSG_RESUME\n"));
	    UAL_IncrementMIBStats(tridArray[i], UAL_PEG_RESUME_IND_ID);
	}
    }

    ITS_EVENT_TERM(UALEvent);

    return ret;
}

/*
 * this is the feature record.
 */
UALDLLAPI ITS_ClassRec itsUAL_ClassRec =
{
    /* core part */
    {
        NULL, /*&itsCORE_ClassRec,    */          /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        UAL_CLASS_NAME,                 /* class name */
        UAL_Initialize,                 /* class init */
        UAL_Terminate,                  /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

UALDLLAPI ITS_Class itsUAL_Class = &itsUAL_ClassRec;

ITS_BOOLEAN inAS       = ITS_FALSE;
ITS_BOOLEAN inASP      = ITS_FALSE;
ITS_BOOLEAN inAppMode  = ITS_FALSE;
ITS_BOOLEAN inIpspType = ITS_FALSE;
UAL_KeyInfo *prevKey   = NULL;  /* store present key when inAS is true */


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      When UAL works with the engine, it needs to parse its resources out
 *      of the INI file.
 *
 *  Input Parameters:
 *      ext - the parse extension object
 *      el - element name
 *      attr - attribute list for the element
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
 *      None.
 *
 *  See Also:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1789
 *
 ******************************************************************************/
UALDLLAPI void
UAL_ParseStartFunc(ENGINE_ParserExtension ext,
                    const char* el, const char** attr)
{
    UAL_ParseInfo* tmp;
    UAL_KeyInfo**  list, *key;
    ITS_UINT       count, i;

    count = i = 0;

    if(strcmp(el, UAL_MGNT_CLASS_NAME) == 0)
    {
        tmp = calloc(1, sizeof(UAL_ParseInfo));
        ITS_C_ASSERT(tmp != NULL);
        tmp->aspId = -1;

        ENGINE_PE_USER_DATA(ext) = tmp;

        while(*attr)
        {
            if(strcmp(*attr, UAL_HEARTBEAT_STRING) == 0)
            {
                attr++;

                tmp->hb = strstr(*attr, "on") != NULL ||
                          strstr(*attr, "ON") != NULL;

                attr++;
            }
            else if(strcmp(*attr, UAL_HB_INTERVAL_STRING) == 0)
            {
                attr++;

                tmp->hbInterval = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_ACK_TIMER_STRING) == 0)
            {
                attr++;

                tmp->ackTimer = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_AUD_TIMER_STRING) == 0)
            {
                attr++;

                tmp->audTimer = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_PENDING_TIMER_STRING) == 0)
            {
                attr++;

                tmp->pendingTimer = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_INTERWORK_MODE_STRING) == 0)
            {
                attr++;

                tmp->interworkingMode = strdup(*attr);
                ITS_C_ASSERT(tmp->interworkingMode != NULL);

                attr++;
            }
            else if(strcmp(*attr, UAL_VERSION_STRING) == 0)
            {
                attr++;

                tmp->version = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_LOCAL_PC_STRING) == 0)
            {
                attr++;

                tmp->localPC = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_ASP_ID_STRING) == 0)
            {
                attr++;

                if (strncmp(*attr, "-", 1) != 0)
                {
                    tmp->aspId = RESFILE_ParseNum(*attr);
                }
                else
                {
                    tmp->aspId = -1;
                }

                attr++;
            }
            else if(strcmp(*attr, UAL_DEBUG_FLAG_STRING) == 0)
            {
                attr++;

                tmp->debug = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        /* If value is not specified in config file (or is specified to be ZERO), 
	 * assign the default value */
	tmp->audTimer = (tmp->audTimer == 0) 
	                          ? UAL_GL_AUD_TIMER_DEFAULT_VAL : tmp->audTimer;
    }
    else if(strcmp(el, UAL_APPL_SERVER_STRING) == 0)
    {
        ITS_C_ASSERT(ENGINE_PE_USER_DATA(ext) != NULL);

        tmp = (UAL_ParseInfo *)ENGINE_PE_USER_DATA(ext);
        key = (UAL_KeyInfo *)calloc(1, sizeof(UAL_KeyInfo));
        ITS_C_ASSERT(key != NULL);

        inAS = ITS_TRUE;
        prevKey = key;

        /* append record to list */
        for(list = &tmp->keyList; *list; list = &((*list)->next))
        {
        }
        *list = key;

        while(*attr)
        {
            if(strcmp(*attr, ROUTING_KEY_STRING) == 0)
            {
                attr++;

                key->rkey = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_AS_TRAFFIC_MODE_STRING) == 0)
            {
                attr++;

                key->asTrafficMode = strdup(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_NI_STRING) == 0)
            {
                attr++;

                key->ni = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, FAMILY_STRING) == 0)
            {
                attr++;

                key->family = strdup(*attr);

                attr++;
            }
            else if (strcmp(*attr, UAL_ASP_CAPABILITIES_STRING) == 0)
            {
                if (strstr(*attr, UAL_CAPAB_CLASS0_STRING) != NULL)
                {
                    key->aspCapab.protClass = SUA_PROT_CLASS0_FLAG;
                }
                else if (strstr(*attr, UAL_CAPAB_CLASS1_STRING) != NULL)
                {
                    key->aspCapab.protClass = SUA_PROT_CLASS1_FLAG;
                }
                else if (strstr(*attr, UAL_CAPAB_CLASS2_STRING) != NULL)
                {
                    key->aspCapab.protClass = SUA_PROT_CLASS2_FLAG;
                }
                else if (strstr(*attr, UAL_CAPAB_CLASS3_STRING) != NULL)
                {
                    key->aspCapab.protClass = SUA_PROT_CLASS3_FLAG;
                }
                else
                {
                    key->aspCapab.protClass = 0;
                }

                attr++;

            }
            else if(strcmp(*attr, UAL_IS_MEMBER_STRING) == 0)
            {
                attr++;

                key->isMember = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

                attr++;
            }
            else if(strcmp(*attr, UAL_N_REDUNDANCY_STRING) == 0)
            {
                attr++;

                key->nActives = RESFILE_ParseNum(*attr);

                attr++;
            }
            else if(strcmp(*attr, UAL_K_REDUNDANCY_STRING) == 0)
            {
                attr++;

                key->kStandby = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if((strcmp(el, UAL_ASP_INFO_STRING) == 0) && inAS)
    {
        count = prevKey->aspCount;

        inASP = ITS_TRUE;

        while(*attr)
        {
            if(strcmp(*attr, UAL_ASP_ID_STRING) == 0)
            {
                attr++;

                if (strncmp(*attr, "-", 1) != 0)
                {
                    prevKey->asp_info[count].aspId = RESFILE_ParseNum(*attr);
                }
                else
                {
                    prevKey->asp_info[count].aspId = -1;
                }

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if((strcmp(el, UAL_HOME_STRING) == 0) && inASP)
    {
        count = prevKey->aspCount;

        if(strcmp(*attr, UAL_VALUE_STRING) == 0)
        {
            attr++;

            i = prevKey->asp_info[count].ipAddrCount;

            prevKey->asp_info[count].home[i] = strdup(*attr);

            prevKey->asp_info[count].ipAddrCount++;

            ITS_C_ASSERT(prevKey->aspCount < UAL_MAX_ASP_IN_AS);

            i++;

            attr++;
         }
         else
         {
             attr += 2;
         }
    }
    else if (strcmp(el, UAL_APP_OP_TYPE) == 0)
    {
        tmp = (UAL_ParseInfo *)ENGINE_PE_USER_DATA(ext);

        inAppMode = ITS_TRUE;

        while (*attr)
        {
            if (strcmp(*attr, UAL_INTERWORK_MODE_STRING) == 0)
            {
                attr++;

                tmp->interworkingMode = strdup(*attr);
                ITS_C_ASSERT(tmp->interworkingMode != NULL);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if ((strcmp(el, UAL_IPSP_APP_TYPE) == 0) && inAppMode)
    {
        tmp = (UAL_ParseInfo *)ENGINE_PE_USER_DATA(ext);

        inIpspType = ITS_TRUE;

        tmp->ipspType = 0;
    }
    else if ((strcmp(el, UAL_IPSP_EXCHANGE) == 0) && inIpspType)
    {
        tmp = (UAL_ParseInfo *)ENGINE_PE_USER_DATA(ext);

        while (*attr)
        {
            if (strcmp(*attr, UAL_VALUE_STRING) == 0)
            {
                attr++;

                if (strcmp(*attr, UAL_IPSP_SINGLE_EXCHANGE) == 0)
                {
                    tmp->ipspType |= UAL_IPSP_TYPE_SINGLE_EXCHG;
                }
                else if (strcmp(*attr, UAL_IPSP_DOUBLE_EXCHANGE) == 0)
                {
                    tmp->ipspType |= UAL_IPSP_TYPE_DOUBLE_EXCHG;
                }

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if ((strcmp(el, UAL_IPSP_SE_CLIENT) == 0) && inIpspType)
    {
        tmp = (UAL_ParseInfo *)ENGINE_PE_USER_DATA(ext);

        while (*attr)
        {
            if (strcmp(*attr, UAL_VALUE_STRING) == 0)
            {
                attr++;

                if ((strcmp(*attr, "no") == 0) ||
                    (strcmp(*attr, "NO") == 0))
                {
                    tmp->ipspType |= UAL_IPSP_MASK_SERVER;
                }
                else
                {
                    tmp->ipspType |= UAL_IPSP_MASK_CLIENT;
                }
                attr++;
            }
            else if (strcmp(*attr, UAL_IPSP_SE_SERVER) == 0)
            {
                attr++;

                if ((strcmp(*attr, "no") == 0) ||
                    (strcmp(*attr, "NO") == 0))
                {
                    tmp->ipspType |= UAL_IPSP_MASK_CLIENT;
                }
                else
                {
                    tmp->ipspType |= UAL_IPSP_MASK_SERVER;
                }
            }
            else
            {
                attr += 2;
            }
        }
    }

    return;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      When UAL works with the engine, it needs to parse its resources out
 *      of the INI file.
 *
 *  Input Parameters:
 *      ext - the parse extension object
 *      el - element name
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
 *      None.
 *
 *  See Also:
 *      None.
 *
 ******************************************************************************/
UALDLLAPI void
UAL_ParseStop(ENGINE_ParserExtension ext,
              const char* el)
{
    if(strcmp(el, UAL_APPL_SERVER_STRING) == 0)
    {
        prevKey = NULL;
        inAS = ITS_FALSE;
    }
    else if(strcmp(el, UAL_ASP_INFO_STRING) == 0)
    {
        inASP = ITS_FALSE;
        prevKey->aspCount++;
    }
    else if (strcmp(el, UAL_IPSP_APP_TYPE) == 0)
    {
        inAppMode = ITS_FALSE;
    }
}

#if 0
static void
freeParseInfo(UAL_ParseInfo *tmp)
{
    ITS_INT     i = 0, j = 0;
    UAL_KeyInfo *rkey = NULL;


    if (tmp->interworkingMode)
    {
        free(tmp->interworkingMode);
    }

    for (rkey = tmp->keyList; rkey; rkey = tmp->keyList)
    {
        if (rkey->asTrafficMode)
        {
            free(rkey->asTrafficMode);
        }

        if (rkey->family)
        {
            free(rkey->family);
        }

        for (i = 0; i < rkey->aspCount; i++)
        {
            for (j = 0; j < rkey->asp_info[i].ipAddrCount; j++)
            {
                free(rkey->asp_info[i].home[j]);
            }
        }

        tmp->keyList = rkey->next;
        free(rkey);
    }

    free(tmp);
}
#endif

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      When the engine gets around to it, the UAL needs to set
 *      some expected resources.
 *
 *  Input Parameters:
 *      ext - the parse extension object
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
 *      None.
 *
 *  See Also:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1789
 *  Vipul       02-05-2007   Bug ID:41                   The UAL_ParseInfo pointer  
 *                                                       is been used in 
 *                                                       UAL_ExtensionCommit     
 *                                                       function. Hence memory is
 *                                                       not released here.   
 *
  ******************************************************************************/
UALDLLAPI void
UAL_ResourceXlate(RESFILE_Manager* appRes, ENGINE_ParserExtension ext)
{
    UAL_ParseInfo *tmp = NULL;

    tmp = ENGINE_PE_USER_DATA(ext);
    ITS_C_ASSERT(tmp != NULL);

    UAL_BuildResourceConfig(appRes, tmp);

   /* freeParseInfo(tmp);*/

   /* ENGINE_PE_USER_DATA(ext) = NULL; */
}

UALDLLAPI void
UAL_BuildResourceConfig(RESFILE_Manager* appRes, UAL_ParseInfo* tmp)
{
    UAL_KeyInfo* key, *tkey;
    char buf[32];
    int  ret;

    ret = RESFILE_AddSection(appRes, UAL_MGNT_CLASS_NAME);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* heartbeat */
    if (tmp->hb)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_HEARTBEAT_STRING, "on");
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_HEARTBEAT_STRING, "off");
    }
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* hb interval */
    sprintf(buf, "%d", tmp->hbInterval);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_HB_INTERVAL_STRING, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* ack timer */
    sprintf(buf, "%d", tmp->ackTimer);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_ACK_TIMER_STRING, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* aud timer */
    sprintf(buf, "%d", tmp->audTimer);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_AUD_TIMER_STRING, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* pending timer */
    sprintf(buf, "%d", tmp->pendingTimer);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_PENDING_TIMER_STRING, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* interworkingMode */
    if (tmp->interworkingMode)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_INTERWORK_MODE_STRING,
                                  tmp->interworkingMode);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (tmp->interworkingMode &&
        strcmp(tmp->interworkingMode, UAL_IPSP_MODE) == 0 &&
               tmp->ipspType == 0)
    {
       /* for backward compatible. */
       tmp->ipspType = UAL_IPSP_TYPE_DOUBLE_EXCHG;
    }

    sprintf(buf, "%d", tmp->ipspType);

    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_IPSP_TYPE_STRING,
                              buf);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (tmp->aspId != -1)
    {
	sprintf(buf, "%d", tmp->aspId);

	ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
		                  UAL_ASP_ID_STRING, buf);
    }

    /* version */
    sprintf(buf, "%d", tmp->version);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_VERSION_STRING, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* get localPC from xml parser */
    sprintf(buf, "%d", tmp->localPC);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_LOCAL_PC_STRING, buf);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* debug flag to display ASP's own config */
    sprintf(buf, "%d", tmp->debug);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_DEBUG_FLAG_STRING, buf);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* keys */
    for (key = tmp->keyList; key != NULL; key = tkey)
    {
        int count = 0;

        tkey = key->next;

        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_AS_INFO_STRING, "begin");

        ITS_C_ASSERT(ret == ITS_SUCCESS);
 
        /* routing key */
        sprintf(buf, "%d", key->rkey);
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  ROUTING_KEY_STRING, buf);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        if(key->asTrafficMode)
        {
            ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_AS_TRAFFIC_MODE_STRING, 
                                      key->asTrafficMode);

            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if(key->family)
        {
            ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      FAMILY_STRING, key->family);

            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        sprintf(buf, "%d", key->ni);
        ret =  RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                   UAL_NI_STRING, buf);

        ITS_C_ASSERT(ret == ITS_SUCCESS);

        while(count < key->aspCount)
        {
            ITS_UINT num = 0;

            sprintf(buf, "%d", key->asp_info[count].aspId);

            ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_ASP_ID_STRING, buf);

            ITS_C_ASSERT(ret == ITS_SUCCESS);

            while(num < key->asp_info[count].ipAddrCount)
            {
                sprintf(buf, "%s", key->asp_info[count].home[num]);

                ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                          UAL_HOME_STRING, buf);

                ITS_C_ASSERT(ret == ITS_SUCCESS);

                num++;
            }

            count++;
        }

        if(key->aspCapab.protClass)
        {
            if (key->aspCapab.protClass == SUA_PROT_CLASS0_FLAG)
            {
                ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                          UAL_ASP_CAPABILITIES_STRING, 
                                          UAL_CAPAB_CLASS0_STRING);
            }
            else if (key->aspCapab.protClass == SUA_PROT_CLASS1_FLAG)
            {
                ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                          UAL_ASP_CAPABILITIES_STRING, 
                                          UAL_CAPAB_CLASS1_STRING);
            }
            else if (key->aspCapab.protClass == SUA_PROT_CLASS2_FLAG)
            {
                ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                          UAL_ASP_CAPABILITIES_STRING, 
                                          UAL_CAPAB_CLASS2_STRING);
            }
            else if (key->aspCapab.protClass == SUA_PROT_CLASS3_FLAG)
            {
                ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                          UAL_ASP_CAPABILITIES_STRING, 
                                          UAL_CAPAB_CLASS3_STRING);
            }

            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
        sprintf(buf, "%d", key->nActives);

        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_N_REDUNDANCY_STRING, buf);

        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(buf, "%d", key->kStandby);

        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_K_REDUNDANCY_STRING, buf);

        ITS_C_ASSERT(ret == ITS_SUCCESS);

        if(key->isMember)
        {
            ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_IS_MEMBER_STRING, "yes");
        }
        else
        {
            ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_IS_MEMBER_STRING, "no");
        }

        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_AS_INFO_STRING, "end");

        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      When UAL works with the engine, it needs to parse its resources out
 *      of the INI file.
 *
 *  Input Parameters:
 *      ext1 - the new parse extension object
 *      ext2 - the old parse extension object
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
 *      None.
 *
 *  See Also:
 *      None.
 *
 ******************************************************************************/
UALDLLAPI void
UAL_ExtensionDiff(ENGINE_ParserExtension ext1,
                   ENGINE_ParserExtension ext2)
{
    /* nothing to do here. */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the parser extension configuration in the XML file.
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

UALDLLAPI void
UAL_ExtensionCommit(FILE* fp)
{
    UAL_ParseInfo* tmp = NULL;
    UAL_KeyInfo* key, *tkey;

    ENGINE_ParserExtension ext=
        (ENGINE_ParserExtension) ENGINE_APP_PARSER_EXTENSIONS(application);

    if (fp == NULL) return;

    while (ext)
    {
        if (strcmp(ENGINE_PE_ELEMENT_NAME(ext),"UAL_Manager") == 0)
        {
            break;
        }

        ext = (ENGINE_ParserExtensionRec*)ENGINE_PE_NEXT(ext);
    }

    tmp = ENGINE_PE_USER_DATA(ext);

    if (tmp == NULL) return;

    fprintf(fp, "\t<%s\n",UAL_MGNT_CLASS_NAME);

    fprintf(fp, "\t\tuseSCMGCallBack   = \"no\"\n");

    if (tmp->hb)
    {
        fprintf(fp, "\t\t%s = \"on\"\n",UAL_HEARTBEAT_STRING);
    }
    else
    {
        fprintf(fp, "\t\t%s = \"off\"\n",UAL_HEARTBEAT_STRING);
    }

    fprintf(fp, "\t\t%s = \"%d\"\n",UAL_HB_INTERVAL_STRING, tmp->hbInterval);
    fprintf(fp, "\t\t%s = \"%d\"\n",UAL_ACK_TIMER_STRING, tmp->ackTimer);
    fprintf(fp, "\t\t%s = \"%d\"\n",UAL_AUD_TIMER_STRING, tmp->audTimer);
    fprintf(fp, "\t\t%s = \"%d\"\n",UAL_PENDING_TIMER_STRING, tmp->pendingTimer);

    if (tmp->interworkingMode)
    {
        fprintf(fp, "\t\t%s = \"%s\"\n",UAL_INTERWORK_MODE_STRING, tmp->interworkingMode);
    }

    fprintf(fp, "\t\t%s = \"%d\"\n",UAL_LOCAL_PC_STRING, tmp->localPC);
    fprintf(fp, "\t\t%s = \"%d\">\n",UAL_VERSION_STRING, tmp->version);

    for (key = tmp->keyList; key != NULL; key = tkey)
    {
        int count = 0;

        tkey = key->next;

        fprintf(fp, "\t\t<%s\n",UAL_APPL_SERVER_STRING);
        fprintf(fp, "\t\t\t%s = \"%d\"\n",ROUTING_KEY_STRING, key->rkey);

        if(key->asTrafficMode)
        {
            fprintf(fp, "\t\t\t%s = \"%s\"\n",UAL_AS_TRAFFIC_MODE_STRING, key->asTrafficMode);
        }

        if(key->family)
        {
            fprintf(fp, "\t\t\t%s = \"%s\"\n",FAMILY_STRING, key->family);
        }

        fprintf(fp, "\t\t\t%s = \"%d\"\n",UAL_NI_STRING, key->ni);

        if(key->isMember)
        {
            fprintf(fp, "\t\t\t%s = \"yes\">\n",UAL_IS_MEMBER_STRING);
        }
        else
        {
            fprintf(fp, "\t\t\t%s = \"no\">\n",UAL_IS_MEMBER_STRING);
        }

        while(count < key->aspCount)
        {
            ITS_UINT num = 0;

            fprintf(fp, "\t\t\t<%s\n",UAL_ASP_INFO_STRING);
            fprintf(fp, "\t\t\t\t%s = \"%d\"\n",UAL_ASP_ID_STRING,key->asp_info[count].aspId);

            while(num < key->asp_info[count].ipAddrCount)
            {
                fprintf(fp, "\t\t\t\t%s = \"%s\"\n",UAL_HOME_STRING,
                       key->asp_info[count].home[num]);
                num++;
            }

            fprintf(fp, "\t\t\t/>\n");

            count++;
        }

        fprintf(fp, "\t\t</%s>\n",UAL_APPL_SERVER_STRING);
    }

    fprintf(fp, "\t</%s>\n",UAL_MGNT_CLASS_NAME);
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Initialise UAL trace settings.
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
 *      None.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * adutta    04-05-2005  BugId:1537    UAL_CRITICAL_STRING
 *                                     replaced by UAL_DEBUG_STRING.
 *
 *  See Also:
 *      None.
 *
 ******************************************************************************/
static void
InitTraceSettings()
{
     /*
     * determine tracing from INI files
     */

    if (TRANSPORT_RES(__UAL_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__UAL_RcvQueue);
        /*char *name = TRANSPORT_NAME(__UAL_RcvQueue); */

        char *name = "UAL";

        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, UAL_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, UAL_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_STDOUT_STRING, ITS_FALSE);

            }
            if (strstr(value, UAL_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_FILE_STRING, ITS_FALSE);

            }
            if (strstr(value, UAL_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_CRITICAL_STRING,
                                           UAL_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_CRITICAL_STRING, ITS_FALSE);
            }
        }
        
        /* error */
        if (RESFILE_GetKeyValueOf(res, name, UAL_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, UAL_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_ERROR_STRING,
                                           UAL_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys) 
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_ERROR_STRING, ITS_FALSE);
            }
        }
        
        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, UAL_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE ;

            if (strstr(value, UAL_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_WARNING_STRING,
                                           UAL_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_WARNING_STRING, ITS_FALSE);
            }
        }
  
        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, UAL_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, UAL_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, UAL_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(UAL_TraceData,
                                           UAL_DEBUG_STRING,
                                           UAL_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)    
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(UAL_TraceData,
                                          UAL_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Routing Key value more than 255 related function.
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
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-01-2008   BugId: 1541     Propagated Bridgeport Isse.
 *                                          Support of Routing Key value 
 *                                          more than 255.                                          
 *
 *  See Also:
 ****************************************************************************/

int
SendASPActive_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
   RK_Context *rCtxt = (RK_Context *)data;
   if(SendASPActive(rCtxt) != ITS_SUCCESS)
   {
      UAL_ERROR(("Failed to Send ASP Active"));
   } 
   return ITS_SUCCESS;
}

int
SendASPInactive_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
    UAL_DEBUG(("Sending ASP Inactive \n"));
    ITS_BOOLEAN ret = ITS_FALSE;
    RK_Context *rCtxt = (RK_Context *)data;
    UAL_DEBUG(("rCtxt->rCtxt = %x", rCtxt->rCtxt));

    UAL_ConfigPriv config;
    config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));
    if(config == NULL)
    {
            UAL_ERROR(("\n Memory Allocation failed...\n"));
            return !ITS_SUCCESS;
    }

    UAL_CONFIG_PRIV_ASP_INFO(config).asp = rCtxt->rCtxt;

    ret = SendASP_INACTIVE(config);
    if(ret == ITS_FALSE)
    {
        UAL_ERROR(("\nSending ASP Inactive failed"));
        free(config);
        return !ITS_SUCCESS;
    }
    free(config);
    return ITS_SUCCESS;
}

UALDLLAPI void
UAL_RedundancyCallback(ITS_POINTER object, ITS_POINTER userData,
                       ITS_POINTER callData)
{
   ITS_EVENT *event = (ITS_EVENT *) callData;
   //RK_Context *rCtxtArray[UAL_MAX_NUM_AS];
 
   UAL_DEBUG(("UAL_RedundancyCallback called Redn event: (%02x), %s. \n", 
			   event->data[0],
			   DSM_MEMBERSHIP_CHANGE_EVENT_TYPE_STRING(event->data[0])));

   /* Bypass the processing if running as SG */
   if (UAL_GL_ITW_MODE == UAL_ITW_SG)
   {
      //ITS_EVENT_TERM(event);
      return;
   }

   switch (event->data[0])
   {
   case ITS_STATE_CHANGE_EVENT:
   case DSM_FT_GROUP_MEMBER_LEAVE:
      if (event->data[1] == ITS_STATE_BACKUP)
      {
          UAL_DEBUG(("Node becomes Inactive/Backup\n"));
          HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                                      NULL, SendASPInactive_hash_iterative_proc);
      }
      else if (event->data[1] == ITS_STATE_PRIMARY)
      {
          UAL_DEBUG(("Node becomes Active/Primary\n"));
 
          HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                                      NULL, SendASPActive_hash_iterative_proc);
      }
      break;
 
   case DSM_FT_GROUP_MEMBER_JOIN:
   default:
      UAL_DEBUG(("Discarded.....\n"));
      break;
   }

   //ITS_EVENT_TERM(event);
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
 * Mani        05-05-2005  BugId:1765
 *
 *  See Also:
 ****************************************************************************/

UALDLLAPI int 
UAL_Commit(FILE* fp)
{
    fprintf(fp, "\t\t<UAL>\n");
    
    if (UAL_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<SigtranTrace>\n");
        if (TRACE_IsLevelOn(UAL_TraceData,
            UAL_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(UAL_TraceData,
            UAL_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(UAL_TraceData,
            UAL_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(UAL_TraceData,
            UAL_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(UAL_TraceData,
                UAL_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</SigtranTrace>\n");
    }
    
    fprintf(fp, "\t\t</UAL>\n\n");
    return ITS_SUCCESS;
}
