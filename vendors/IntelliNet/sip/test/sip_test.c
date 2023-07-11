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
 * CONTRACT: INTERNAL
 *                                                                          *
 ****************************************************************************
 *  ID:$Id  $
 *
 *  $Log: sip_test.c,v $
 *  Revision 9.1  2005/03/23 12:54:28  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.10  2005/03/21 13:53:28  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.9.2.3  2005/02/16 14:11:11  mkrishna
 *  added CANCEL, BYE, REGISTER msg's
 *
 *  Revision 1.9.2.2  2005/02/07 14:20:19  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.9.2.1  2004/12/28 14:04:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.9  2004/09/07 10:31:58  mkrishna
 *  Added function history blocks.
 *
 *  Revision 1.8  2004/06/30 14:07:13  sjaddu
 *  Testing goingon
 *
 *  Revision 1.7  2004/06/28 07:42:35  sjaddu
 *  Load test added and SIP_StackHandle also added.
 *
 ****************************************************************************/
#include <engine.h>
#include <sip.h>
#include <app_sendmsg.h>

/* These are required to make linker happy */
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;

#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

/* Debug console function */
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);

extern int TestSendInvite(char *callId, char *remHost, char *remPort,
                          char *lhost, char *lport);
extern int TestSendCancel(SIP_MSG *msg);
extern int TestSendBye(char *callId, char *remHost, char *remPort,
                       char *lhost, char *lport);
extern int TestSendRegister(char *callId, char *remHost, char *remPort,
                            char *lhost, char *lport);
extern int TestSend180Ringing(SIP_MSG *msg);
extern int TestSend200Ok(SIP_MSG *msg);
extern int TestSend3XX(SIP_MSG *msg);
extern int TestSendAck(SIP_MSG *msg);
extern int TestSendOptions(char *callId, char *remHost, char *remPort,
                           char *lhost, char *lport);
extern int TestSendPrack(SIP_MSG *msg);

extern void StatLoadSender(char * ipAddr, char *port, int calls);
extern void StatLoadReceiver();

extern int callsPerSec;
extern int _debug;

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function is the main of sip toolkit.
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
 *  See Also:
 ****************************************************************************/
int main(int argc, const char **argv)
{

    /* Set the application name */
    APPL_SetName("sip");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    DBC_SetDoCommand(ExecuteCommand);

    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This function has the implementation of Debug Console command. 
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
 *  See Also:
 ****************************************************************************/
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    int result= 0 , ret= 0;
    char buf[ITS_PATH_MAX];

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "invite", "SendInvite", "<callId> <remHost> <remPort> <lhost> <lport>",""))
    {
        char callId[ITS_PATH_MAX], remHost[ITS_PATH_MAX], remPort[ITS_PATH_MAX];
        char lhost[ITS_PATH_MAX], lport[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, callId, remHost,
                     remPort, lhost, lport);

        result = TestSendInvite(callId, remHost, remPort, lhost, lport);
        printf("\n(Application to SIP Stack) Send Invite return result = %d\n",
                result);
    }
    else if (DBC_Cmd(dbc, "cancel", "SendCancel", "<callId> <remHost> <remPort> <lhost> <lport>",""))
    {
        if (sip_last_msg)
        {
            result = TestSendCancel(sip_last_msg);
            printf("\n Send cancel return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        } 
    }
    else if (DBC_Cmd(dbc, "bye", "SendBye", "<callId> <remHost> <remPort> <lhost> <lport>",""))
    {
        char callId[ITS_PATH_MAX], remHost[ITS_PATH_MAX], remPort[ITS_PATH_MAX];
        char lhost[ITS_PATH_MAX], lport[ITS_PATH_MAX];
            
        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, callId, remHost,
                     remPort, lhost, lport);
        
        result = TestSendBye(callId, remHost, remPort, lhost, lport);
        printf("\n(Application to SIP Stack) Send bye return result = %d\n",
                result);
    } 
    else if (DBC_Cmd(dbc, "register", "SendRegister", "<callId> <remHost> <remPort> <lhost> <lport>",""))
    {
        char callId[ITS_PATH_MAX], remHost[ITS_PATH_MAX], remPort[ITS_PATH_MAX];
        char lhost[ITS_PATH_MAX], lport[ITS_PATH_MAX];
            
        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, callId, remHost,
                     remPort, lhost, lport);
        
        result = TestSendRegister(callId, remHost, remPort, lhost, lport);
        printf("\n(Application to SIP Stack)Send Register return result = %d\n",
                result);
    } 
    else if (DBC_Cmd(dbc, "180", "Send180", "","Only after receiving request"))
    {
        if (sip_last_msg)
        {
            result = TestSend180Ringing(sip_last_msg);
            printf("\nSIP APP Send Invite return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        }
    }
    else if (DBC_Cmd(dbc, "200", "Send200ok", "","Only after receiving request"))
    {
        if (sip_last_msg)
        {
            result = TestSend200Ok(sip_last_msg);
            printf("\nSIP APP Send Invite return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        }
    }
    else if (DBC_Cmd(dbc, "3xx", "Send3XX", "","Only after receiving request"))
    {
        if (sip_last_msg)
        {
            result = TestSend3XX(sip_last_msg);
            printf("\nSIP APP Send Invite return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        }
    }
    else if (DBC_Cmd(dbc, "ack", "SendACK", "","Only after receiving request"))
    {
        if (sip_last_msg)
        {
            result = TestSendAck(sip_last_msg);
            printf("\nSIP APP Send Invite return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        }
    }
    else if (DBC_Cmd(dbc, "loadS", "start load sender test", "<remHost> <remPort>",""))
    {
        char  remHost[ITS_PATH_MAX], remPort[ITS_PATH_MAX];
        int calls = 0;

        ret = sscanf(cmdLine, " %s %s %s %d", buf, remHost, remPort, &calls);

        StatLoadSender(remHost, remPort, calls);
    }
    else if (DBC_Cmd(dbc, "loadR", "start load receiver test", "<remHost> <remPort>",""))
    {
        StatLoadReceiver();
    }
    else if (DBC_Cmd(dbc, "debug", "increase load", "",""))
    {
        if ( _debug == 0) _debug++; else _debug--;
    }
    else if (DBC_Cmd(dbc, "incLoad", "increase load", "",""))
    {
        int calls = 0;
        ret = sscanf(cmdLine, " %s %d" , buf, &calls);
        callsPerSec += calls;
    }
    else if (DBC_Cmd(dbc, "decLoad", "decrease load", "",""))
    {
        int calls = 0;
        ret = sscanf(cmdLine, " %s %d" , buf, &calls);
        callsPerSec -= calls;
        if (callsPerSec == 0)
            callsPerSec = 1;
    }
    else if (DBC_Cmd(dbc, "options", "SendOptions", "<callId> <remHost> <remPort> <lhost> <lport>",""))
    {
        char callId[ITS_PATH_MAX], remHost[ITS_PATH_MAX], remPort[ITS_PATH_MAX];
        char lhost[ITS_PATH_MAX], lport[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, callId, remHost,
                     remPort, lhost, lport);

        result = TestSendOptions(callId, remHost, remPort, lhost, lport);
        printf("\n(Application to SIP Stack) Send Options return result = %d\n",
                result);
    }
    else if (DBC_Cmd(dbc, "prack", "SendPRACK", "","Only after receiving provisional response"))
    {
        if (sip_prov_msg)
        {
            result = TestSendPrack(sip_prov_msg);
            printf("\nSIP APP Send provisional resp return result = %d\n",
                result);
        }
        else
        {
            printf("Error :: No request received  \n");
        }
    }
}
