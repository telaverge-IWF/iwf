/****************************************************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: subagent.c,v 1.8 2010/12/02 12:03:11 chandrashekharbs Exp $
 *
 * LOG: $Log: subagent.c,v $
 * LOG: Revision 1.8  2010/12/02 12:03:11  chandrashekharbs
 * LOG: Changes to support native solaris send trap
 * LOG:
 * LOG: Revision 1.7  2010/11/04 09:32:25  nvijikumar
 * LOG: Integration with Solaris net-snmp
 * LOG:
 * LOG: Revision 1.6  2009/03/03 11:20:36  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 1.5  2008/12/31 11:37:35  chandrashekharbs
 * LOG: taskQueue created before alarm process thread creation to avoid possible dump
 * LOG:
 * LOG: Revision 1.4  2008/12/16 10:18:52  chandrabs
 * LOG: Changes to accomadate the mib change
 * LOG:
 * LOG: Revision 1.3  2008/12/12 16:34:13  chandrabs
 * LOG: NULL check added for event data recieved
 * LOG:
 * LOG: Revision 1.2  2008/12/11 13:37:54  chandrabs
 * LOG: Diameter Alarms Tokenising to send alarms to snmp manager
 * LOG:
 * LOG: Revision 1.1  2008/12/10 07:34:42  chandrabs
 * LOG: Initial draft for Alarm support
 * LOG:
****************************************************************************/
#ident "$Id: subagent.c,v 1.8 2010/12/02 12:03:11 chandrashekharbs Exp $"


/* generated from net-snmp-config */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include <net-snmp/net-snmp-config.h>
#ifdef HAVE_SIGNAL
#include <signal.h>
#endif /* HAVE_SIGNAL */
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include <pthread.h>
#include <signal.h>
#include <its.h>
#include <its_emlist.h>
#include <its_thread.h>
#include <its_sockets.h>
#include <subagent.h>


static char* sync_data = "ISS7SSI";
static ITS_INT   sd_len = 7;

const char *app_name = "sub";

#if defined(_SOL_SNMP_)
int netsnmp_running;
#else
extern int netsnmp_running;
#endif

ITS_INT agent_RecvInitialise(SAClientInfo *ClientInfo);
static ITS_INT DIASA_PutEventOnTaskQue(ITS_EVENT *evt);
static ITS_INT DIASA_GetEventFromTaskQue(ITS_EVENT *evt);

static ITS_INT ReadEvent(ITS_HANDLE h, ITS_EVENT *ev);
netsnmp_session session, *ss;
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

/* Global definitions */

#define BUFLEN 5000

ITS_SocketInfo *sockinfo;
struct sockaddr_in ntfyClientAddr, ntfyServerAddr;
static ITS_THREAD   recvClientThread;
static ITS_THREAD   processAlarmThread;
static ITS_THREAD   connectServerThread;
const ITS_INT ITS_OAM_NOTIFY_THREAD_STACK_SIZE = (2 * 1024 * 1024);

SAClientInfo CLI;
ITS_BOOLEAN connDown = ITS_TRUE;
int             inform = 0;

RETSIGTYPE
stop_server(UNUSED int a) {
    netsnmp_running = 0;
}

typedef struct _diasa_trans
{
    EMLIST_Manager       *taskQue;
    ITS_UINT             noCurrEnts;
}DIASA_TRANS_QUE;

DIASA_TRANS_QUE saTrans;

/* Autogenerated */
static void
usage(const char *prog)
{
    fprintf(stderr,
            "USAGE: %s [OPTIONS]\n"
            "\n"
            "OPTIONS:\n", prog);

    fprintf(stderr,
            "  -d\t\t\tdump all traffic\n"
            "  -D TOKEN[,...]\tturn on debugging output for the specified "
            "TOKENs\n"
            "\t\t\t   (ALL gives extremely verbose debugging output)\n"
            "  -f\t\t\tDo not fork() from the calling shell.\n"
            "  -h\t\t\tdisplay this help message\n"
            "  -H\t\t\tdisplay a list of configuration file directives\n"
            "  -L LOGOPTS\t\tToggle various defaults controlling logging:\n");
#ifndef _SOL_SNMP_
    snmp_log_options_usage("\t\t\t  ", stderr);
#endif

#ifndef DISABLE_MIB_LOADING
    fprintf(stderr,
            "  -m MIB[:...]\t\tload given list of MIBs (ALL loads "
            "everything)\n"
            "  -M DIR[:...]\t\tlook in given list of directories for MIBs\n");
#endif /* DISABLE_MIB_LOADING */

#ifndef DISABLE_MIB_LOADING
    fprintf(stderr,
            "  -P MIBOPTS\t\tToggle various defaults controlling mib "
            "parsing:\n");
    snmp_mib_toggle_options_usage("\t\t\t  ", stderr);
#endif /* DISABLE_MIB_LOADING */

    fprintf(stderr,
            "  -v\t\t\tdisplay package version number\n"
            "  -x TRANSPORT\tconnect to master agent using TRANSPORT\n");
    exit(1);
}

/* Autogenerated */
static void
version(void)
{
    fprintf(stderr, "NET-SNMP version: %s\n", netsnmp_get_version());
    exit(0);
}


int
snmp_input(int operation,
           netsnmp_session * session,
           int reqid, netsnmp_pdu *pdu, void *magic)
{
    return 1;
}
static void
optProc(int argc, char *const *argv, int opt)
{
    switch (opt) {
    case 'C':
        while (*optarg) {
            switch (*optarg++) {
            case 'i':
                inform = 1;
                break;
            default:
                fprintf(stderr,
                        "Unknown flag passed to -C: %c\n", optarg[-1]);
                exit(1);
            }
        }
        break;
    }
}
/* 
 * This is automatically generated code from which IntelliNet initalise 
 * functions will be called 
 */
int
main (int argc, char **argv)
{
    int arg;
    char* cp = NULL;
    int dont_fork = 0, do_help = 0;
    ITS_INT rc;

/////////////////////////////////
#if defined(_SOL_SNMP_)
    netsnmp_pdu    *pdu, *response;
    in_addr_t      *pdu_in_addr_t;
    oid             name[MAX_OID_LEN];
    size_t          name_length;
    int             argG;
    int             status;
    char           *trap = NULL, *specific = NULL, *description =
        NULL, *agent = NULL;
    char           *prognam;
    int             exitval = 0;
    
#if 0
// Check this if other parameters needs to be parsed
    switch (argG = snmp_parse_args(argc, argv, &session, "C:", optProc)) {
    case -2:
        exit(0);
    case -1:
        //usage();
        exit(1);
    default:
        break;
    }
#endif
    snmp_sess_init( &session );
    session.version = SNMP_VERSION_2c;
    session.community = "public";
    session.community_len = strlen(session.community);
    session.peername = argv[3];
    init_snmp("snmpapp");
#endif

    SAClientInfo ClientInfo;

    memset(&ClientInfo, 0, sizeof(ClientInfo));

    if (argc < 3)
    {
        AGENT_DEBUG(("USAGE Error: subagent <serverIpAddr> <port>\n"));
        return 0;
    }

    while ((arg = getopt(argc, argv, "dD:fhHL:"
#ifndef DISABLE_MIB_LOADING
                       "m:M:"
#endif /* DISABLE_MIB_LOADING */
                       "n:"
#ifndef DISABLE_MIB_LOADING
                       "P:"
#endif /* DISABLE_MIB_LOADING */
                       "vx:")) != EOF) {
        switch (arg) {
            case 'd':
                netsnmp_ds_set_boolean(NETSNMP_DS_LIBRARY_ID,
                                     NETSNMP_DS_LIB_DUMP_PACKET, 1);
            break;

            case 'D':
                debug_register_tokens(optarg);
                snmp_set_do_debugging(1);
            break;

            case 'f':
                dont_fork = 1;
            break;

            case 'h':
                usage(argv[0]);
            break;

            case 'H':
                do_help = 1;
            break;

            case 'L':
#ifndef _SOL_SNMP_
                if (snmp_log_options(optarg, argc, argv) < 0) {
                    exit(1);
                    }
#else
                 init_snmp_logging();
                 snmp_enable_syslog();
                 snmp_enable_stderrlog();
                 snmp_enable_calllog();
#endif
            break;

#ifndef DISABLE_MIB_LOADING
            case 'm':
                if (optarg != NULL) {
                    setenv("MIBS", optarg, 1);
                    } else {
                    usage(argv[0]);
                    }
            break;

            case 'M':
                if (optarg != NULL) {
                    setenv("MIBDIRS", optarg, 1);
                    } else {
                    usage(argv[0]);
                    }
            break;
#endif /* DISABLE_MIB_LOADING */

            case 'n':
                if (optarg != NULL) {
                    app_name = optarg;
                    netsnmp_ds_set_string(NETSNMP_DS_LIBRARY_ID,
                                  NETSNMP_DS_LIB_APPTYPE, app_name);
                    } else {
                    usage(argv[0]);
                    }
            break;

#ifndef DISABLE_MIB_LOADING
            case 'P':
                cp = snmp_mib_toggle_options(optarg);
                if (cp != NULL) {
                    fprintf(stderr, "Unknown parser option to -P: %c.\n", *cp);
                    usage(argv[0]);
                    }
            break;
#endif /* DISABLE_MIB_LOADING */

            case 'v':
                version();
            break;

            case 'x':
                  if (optarg != NULL) {
                    netsnmp_ds_set_string(NETSNMP_DS_APPLICATION_ID,
                                          NETSNMP_DS_AGENT_X_SOCKET, optarg);
                      } else {
                        usage(argv[0]);
                      }
            break;

            default:
              fprintf(stderr, "invalid option: -%c\n", arg);
              usage(argv[0]);
              break;
        }
    }

#ifndef _SOL_SNMP_
    if (do_help) {
        netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID,
                               NETSNMP_DS_AGENT_NO_ROOT_ACCESS, 1);
        } else {
        /* we are a subagent */
        netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID,
                               NETSNMP_DS_AGENT_ROLE, 1);

     /* initialize tcpip, if necessary */
        SOCK_STARTUP;
    }

    /* initialize the agent library */
    init_agent(app_name);

    /* initialize your mib code here */

    /* subagent will be used to read subagent.conf files. */
    init_snmp("subagent");

    if (do_help) {
        fprintf(stderr, "Configuration directives understood:\n");
        read_config_print_usage("  ");
        exit(0);
    }
#endif

    /* In case we received a request to stop (kill -TERM or kill -INT) */
    netsnmp_running = 1;
#ifdef SIGTERM
    signal(SIGTERM, stop_server);
#endif

#ifdef SIGINT
    signal(SIGINT, stop_server);
#endif

#if defined(_SOL_SNMP_)
    SOCK_STARTUP;
    session.callback = snmp_input;
    session.callback_magic = NULL;
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_DEFAULT_PORT, 
                        SNMP_TRAP_PORT);
    ss = snmp_open(&session);
    if (ss == NULL) {
        /*
         * diagnose snmp_open errors with the input netsnmp_session pointer 
         */
        snmp_sess_perror("iiisnmptrap", &session);
        SOCK_CLEANUP;
        exit(1);
    }
#endif

    /* printf("Sendig Data \n"); Used to test alarms */
    AGENT_DEBUG(("argc = %d, argv[1] = %s argv[2] = %s\n",argc,  argv[1], argv[2]));
    strcpy(ClientInfo.ipAddr,  argv[1]);
    AGENT_DEBUG(("Server Ip = %s \n", ClientInfo.ipAddr));
    ClientInfo.port = atoi(argv[2]);
    AGENT_DEBUG(("Port Number = %d\n", ClientInfo.port));

    /* This is IntelliNet API */
    rc = agent_RecvInitialise(&ClientInfo);
    if (rc < 0)
    {
        AGENT_DEBUG(("sub agent initiale failed \n"));
    }

    /* main loop here... */
    while(netsnmp_running) {
        agent_check_and_process(1);
    }

    /* at shutdown time */
    snmp_shutdown(app_name);
    SOCK_CLEANUP;
    exit(0);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This thread is used to recieve notification from Diameter Application
 *
 *  Input Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name               Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Chandrashekhar BS   10/10/2008                         subagent Recieve 
 *                                                         initialise
 ****************************************************************************/
void* 
NotificationHandlerThread(void* param)
{
    AGENT_DEBUG(("NotificationHandlerThread:: Entering \n"));
    ITS_UINT  recvdDataLen = 0;
    ITS_OCTET recvd_buff[BUFLEN]; 
    ITS_UINT addr_len = sizeof(struct sockaddr);
    ITS_EVENT ev;
    ITS_INT ret;
    ITS_CHAR    bytes[255];
    static int cnt =0;

    while(1)
    {
        AGENT_DEBUG(("sockinfo->socket = %d \n", sockinfo->socket));
        memset(&ev, 0, sizeof(ITS_EVENT));
        ret = ReadEvent(sockinfo, &ev);
        
        if (ret == ITS_ERCVFAIL)
        {
            /* 
             * If Server connection is down wait for some time
             * before try to re-connect 
             */
#ifdef WIN32
            Sleep(5);
#else
            sleep(5);
#endif
            ret = DIASA_Connect(&CLI);
            
            if (ret == ITS_SUCCESS)
            {
                AGENT_DEBUG(("Connect to Server success\n"));
            }
        }
        else if (ret != ITS_SUCCESS)
        {
            AGENT_DEBUG(("Read Failure \n"));
            continue;
        }

        if (ev.data == NULL)
        {
            AGENT_DEBUG(("NULL EVent Recieved \n"));
            continue;
        }
       
        AGENT_DEBUG(("Put event to taskQueue ev.data = %s\n", ev.data));
        DIASA_PutEventOnTaskQue(&ev);
    }

    THREAD_NORMAL_EXIT;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This thread is used to Process the alarm and send notification to master  agent
 *
 *  Input Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name               Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Chandrashekhar BS   08/10/2008                         subagent Recieve 
 *                                                          initialise
 ****************************************************************************/
void*
ProcessAlarmThread(void* param)
{    
    AGENT_DEBUG(("ProcessAlarmThread:: Entering \n"));
    ITS_EVENT event;
    ITS_INT ret;
    ITS_INT alarmId = 0;

    /* for Tokenising */
    ITS_CHAR *token = NULL;
    ITS_CHAR *ptr = NULL;
    ITS_INT Index = 0;
    ITS_INT i = 0;
    ITS_INT ch='=';
    ITS_CHAR bytes[255];
    ITS_CHAR alarmString[100];


    while(1)
    {
        Index = 0;
        ret = DIASA_GetEventFromTaskQue(&event);

        AGENT_DEBUG(("In Process Alarm Thread event.src= %d, ev.len=%d ev.data = %s\n", 
                            event.src,event.len, event.data));
        /* Process the Recieved AlarmText here */

        for (i = 0; i < event.len; i++)
        {
            bytes[i] = event.data[i];
        }
        bytes[i] = '\0';
        AGENT_DEBUG(("PRINTING bytes = %s\n", bytes));


        /*
         * Alarm Format will be as follows 
         * alarmid|SUBSYS|SEV|CLASS|descripFileNam |Fun|lin|Actual dat
         */


        token = strtok(bytes, "|");
        printf("token = %s\n", token);
        
        while ( token != NULL )
        {
            switch ( Index )
            {
                case 0:
                {
                    /* AlarmId */
                    alarmId = (ITS_UINT)atoi(token);
                    Index++;
                    token = strtok(NULL, "|");
                    break;
                }
                case 1:
                {
                    /* Subsystem string - Not needed*/ 
                    Index++;
                    token = strtok(NULL, "|");
                    break;
                }
                case 2:
                {
                    /* Alarm Severity Needed. However since Clear Alarm has 
                     * different alarmId we dont need this information this 
                     * is locally present for us
                     */

                    Index++;
                    token = strtok(NULL, "|");                    
                    break;
                }
                case 3:
                {
                    /* Alarm object.If classname is different; based on which
                     * alarms will be raised needed 
                     */

                    Index++;
                    //strcpy(className,token);
                    token = strtok(NULL, "|");
                    break;
                }
                case 4:
                {
                    /* description */
                    Index++;
                    token = strtok(NULL, "|");
                    break;
                }
                case 5:
                {
                    /* file name */
                    Index++;
                    token = strtok(NULL, "|");
                    break;
                }
                case 6:
                {
                    /* function name */
                    Index++;
                    token = strtok(NULL, "|");
                    break;
                }
                case 7:
                {
                    /* line Number */
                    Index++;
                    //token = strtok(NULL, "|");
                    strcpy(alarmString,token);
                    AGENT_DEBUG(("alarmString = %s\n", alarmString));
                    break;
                }
                
                default:
                {
                    token = NULL;
                    break;
                }
            }
        }
        Index = 0;

        if ((ALARM_SEVERITY(alarmId)) == major)
        {
            ret = send_diaMajorNotification_trap(alarmId, &alarmString);
        }
        else if ((ALARM_SEVERITY(alarmId)) == minor)
        {
            ret = send_diaMinorNotification_trap(alarmId, &alarmString);
        }
        else if ((ALARM_SEVERITY(alarmId)) == cleared)
        {
            ret = send_diaClearedNotification_trap(alarmId, &alarmString);
        }
        else if ((ALARM_SEVERITY(alarmId)) == critical) 
        {
            ret = send_diaCriticalNotification_trap(alarmId, &alarmString);
        }
        else 
        {
            ret = send_diaInfoNotification_trap(alarmId, &alarmString);
        }
    }

    THREAD_NORMAL_EXIT;
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method is used to initalise subagent 
 *
 *  Input Parameters:
 *      
 *
 *  Output Parameters:
 *      
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name               Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Chandrashekhar BS   10/10/2008                         subagent Recieve 
 *                                                          initialise
 ****************************************************************************/
ITS_INT 
agent_RecvInitialise(SAClientInfo *ClientInfo)
{
    AGENT_DEBUG(("agent_RecvInitialise:: ClientInfo Address=%s port = %d\n", 
                        ClientInfo->ipAddr, ClientInfo->port));
    ITS_INT ret;

    strcpy(CLI.ipAddr, ClientInfo->ipAddr);
    CLI.port = ClientInfo->port;

    AGENT_DEBUG(("CLI Addr = %s CLI port = %d \n",CLI.ipAddr,CLI.port));

#if defined(DEBUG)
{
    agentTraceEnable = ITS_TRUE;
}
#else
{
    agentTraceEnable = ITS_FALSE;
}
#endif

    ret = DIASA_Connect(&CLI);

    if (ret == ITS_SUCCESS)
    {
        AGENT_DEBUG(("Connect to Server success\n"));
    }
    else
    {
        AGENT_DEBUG(("Connect to Server failed\n"));
    }

    /* Create queue for recieving event in Process alarm thread */
    saTrans.taskQue = EMLIST_Create();

    /* Thread for recieving alarms */

    if(ITS_SUCCESS !=  THREAD_CreateThread(&recvClientThread,
           ITS_OAM_NOTIFY_THREAD_STACK_SIZE,
           NotificationHandlerThread,NULL,1))
    {
        AGENT_DEBUG(("Thread Creation For Receiving Notification from \
                      Notification Server Failed \n"));
        return -1;
    }

    /* Thread for Processing alarms */
    if(ITS_SUCCESS !=  THREAD_CreateThread(&processAlarmThread,
         ITS_OAM_NOTIFY_THREAD_STACK_SIZE,
         ProcessAlarmThread, NULL, 1))
    {
        AGENT_DEBUG(("Thread Creation For Processing Alarms Failed \n"));
        return -1;
    }


    return ITS_SUCCESS;
}


/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method retrieves the event from the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type DIASA_TRANS_QUE
 *
 *  Output Parameters:
 *      evt   -   of type ITS_EVENT
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_INT
DIASA_GetEventFromTaskQue(ITS_EVENT *evt)
{
    AGENT_DEBUG(("DIASA_GetEventFromTaskQue:: Entering\n"));
    ITS_INT len = 0, ret;
    void *data = 0;
    ITS_INT interval = 5;

repeat:
    if ((ret = EMLIST_GetNextEventWithTimeOut(saTrans.taskQue,
                       &data, &len, interval)) != ITS_SUCCESS)
    {
        if (ret == ITS_ETIMEOUT)
        {
            goto repeat;
        }

        if (data != NULL)
        {
            ITS_Free(data);
        }
        return (ret);
    }
    memcpy(evt, data, len);

    if (EMLIST_Lock(saTrans.taskQue) != ITS_SUCCESS)
    {
        ITS_Free(data);
        return (ITS_EBADMUTEX);
    }

    --saTrans.noCurrEnts;

    EMLIST_Unlock(saTrans.taskQue);

    ITS_Free(data);

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method puts the event on to the task que.
 *
 *  Input Parameters:
 *      taskTran  -   of type DIASA_TRANS_QUE
 *      evt   -   of type ITS_EVENT
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
static ITS_INT
DIASA_PutEventOnTaskQue(ITS_EVENT *evt)
{
    AGENT_DEBUG(("DIASA_PutEventOnTaskQue:: Entering\n"));
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT index = 0;

    if (EMLIST_Lock(saTrans.taskQue) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ret = EMLIST_PutEvent(saTrans.taskQue,(ITS_CHAR*)evt,sizeof(ITS_EVENT));

    ++saTrans.noCurrEnts;

    EMLIST_Unlock(saTrans.taskQue);

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method connects to the server.
 *      socket
 *
 *  Input Parameters:
 *      info  -   of type IDS_CONNECTION_INFO
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *      This function doesn't return until it connects to the server.
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
DIASA_Connect(SAClientInfo *ClientInfo)
{
    AGENT_DEBUG(("DIASA_Connect:: \n"));
    ITS_INT ret =0;
    ITS_INT repeat_count = 1;
    ITS_INT    dummy = 1;                /* for socket option */
    ITS_SocketInfo *sInfo;
    struct linger      linger;           /* for set linger */
    ITS_BOOLEAN isUp = ITS_FALSE;
    ITS_CHAR ipAddr[20];
    ITS_INT port;

    while(1)
    {
        strcpy(&ipAddr, ClientInfo->ipAddr);
        port = ClientInfo->port;

        AGENT_DEBUG(("DIASA_Connect:: ipaddr = %s port = %d \n", 
                                                     ipAddr, port));

        ret = SOCK_ClientOpen(&sockinfo,
                              INET_DOMAIN,
                              ipAddr,
                              port);
        if (ret != ITS_SUCCESS)
        {
            AGENT_DEBUG(("IDSCL_Connect: Create client failed ret = %d\n", 
                                                                      ret));
            return (ret);
        }

        AGENT_DEBUG(("sockinfo->socket = %d \n", sockinfo->socket));

        ret = SOCK_ClientConnect(sockinfo);
        if (ret != ITS_SUCCESS)
        {
            AGENT_DEBUG(("Connect to server failed. Trying Again \n"));
            SOCK_Close(sockinfo);
            sockinfo = NULL;

#ifdef WIN32
            Sleep(5);
#else
            sleep(5);
#endif
            repeat_count++;
        }
        else
        {
            isUp = ITS_TRUE;
            AGENT_DEBUG(("IDSCL_Connect:: Connected to server\n"));
            break;
        }
    }

    return (ret);
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method used to ReadEvent
 *      socket
 *
 *  Input Parameters:
 *      sd  -   Socket descriptor
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returs ITS_SUCCESS
 *
 *  Notes:
 *      
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
ReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    unsigned i, dosCount;
    ITS_USHORT tmp;
    char b;
    ITS_SocketInfo* sockInfo  = (ITS_SocketInfo *)h;

    ITS_BOOLEAN firstTime = ITS_TRUE;

    if (h == NULL || ev == NULL)
    {
        return !ITS_SUCCESS;
    }

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = sockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);

            if (ret < ITS_SUCCESS)
            {
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }
            firstTime = ITS_FALSE;
        }
        ret = SOCK_Read(sockInfo, &b, sizeof(char));
        if (ret != sizeof(char))
        {
            return (ITS_ERCVFAIL);
        }

        if (b != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* read the source */
    ret = SOCK_Read(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }
    ev->src = SOCK_NToHS(tmp);

    /* read the length */
    ret = SOCK_Read(sockInfo, (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ERCVFAIL);
    }

    ev->len = SOCK_NToHS(tmp);

    ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }
    /* read the data */
    if (ev->len)
    {
        ret = SOCK_Read(sockInfo, (char *)ev->data, ev->len);
        if (ret != ev->len)
        {
            ITS_Free(ev->data);
            ev->data = NULL;
            return (ITS_ERCVFAIL);
        }
    }

    return (ITS_SUCCESS);
}
