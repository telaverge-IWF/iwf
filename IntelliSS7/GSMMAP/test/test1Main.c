/****************************************************************************
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
 * CONTRACT: GSMMAP testbed                                                 *
 *                                                                          *
 *     FILE: test1Main.c                                                    *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test1Main.c,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: test1Main.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:48  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:20  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:20  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:07  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:08  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/09/14 15:30:16  ite
 * LOG: Tested successfully on NMS hardware. This version also sent to Nokia
 * LOG: for trial.
 * LOG:
 * LOG: Revision 1.1  1998/09/03 22:10:01  jpakrasi
 * LOG: First draft. Setting up test prgm on NMS hardware.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <conio.h>

#include <its.h>
#include <its_fifo_trans.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_route.h>

#include <tcap.h>
#include <GSMMAP.h>
#include <its_GSMMAP.h>
#include <GSMMAP-types.h>
#include <assert.h>

#include <testcommon.h>

static int TEST_PrintCommand();
int TEST_WaitForResponse(ITS_HANDLE handle);

ITS_HANDLE handle = NULL;

/*
 * termination handler
 */
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    ITS_Terminate(handle);
}

int
main(int argc, char **argv)
{
    int ret = 0, cmdInput = 0;
    int replyExpected = 0;
  		
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

	handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP | ITS_SCCP | 
                                        ITS_TRANSPORT_SS7 | 
                                        ITS_TRANSPORT_SINGLE_USER, 1);
    if (handle == NULL)
    {
        printf("Null handle \n");
        exit(0);
    }


    for (;;)
    {
        TEST_PrintCommand();
        scanf("%d", &cmdInput);
        printf("You input %d.\n", cmdInput);
        if (cmdInput < TEST_MIN_MSG || cmdInput > TEST_MAX_MSG)
        {
            printf("Please choose your input number between %d and %d.\n",
                    TEST_MIN_MSG, TEST_MAX_MSG);
            continue;
        }
        else if (cmdInput == TEST_EXIT)
        {
            printf("Exiting program after cleanup...\n");
            ITS_Terminate(handle);
            exit(1);
        }
        
        ret = TEST_SendGSMMAPInvoke(cmdInput, &replyExpected, handle);
        if (ret == ITS_SUCCESS && replyExpected)
        {
            TEST_WaitForResponse(handle);
        }
    }

	return EXIT_SUCCESS;
}

int 
TEST_WaitForResponse(ITS_HANDLE handle)
{
    int ret = 0;
    TCAP_CPT cpt;
    ITS_HDR hdr;
    TCAP_DLG dlg;
    ITS_EVENT event;    

    memset((char *)&cpt, 0, sizeof(TCAP_CPT));
    memset((char *)&hdr, 0, sizeof(ITS_HDR));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    for(;;)
    {
        printf("Waiting for event..\n\n");
        ret = ITS_GetNextEvent(handle, &event);
        if (ret == ITS_SUCCESS)
        {
            printf("\nEvent received\n");

            if(event.data[0] == ITS_TCAP_DLG)
            {
                printf("Received Dialogue\n");
                TCAP_ReceiveDialogue(handle, &event, &hdr, &dlg);
                printf("ptype = 0x%x, dialogue_id = 0x%x\n",
                        dlg.ptype,hdr.context.dialogue_id);
            }
            if(event.data[0] == ITS_TCAP_CPT)
            {
                printf("Received Component\n");
                TCAP_ReceiveComponent(handle, &event, &hdr, &cpt);
                printf("ptype = 0x%x\n", cpt.ptype);            
                if (cpt.ptype == TCPPT_TC_RESULT_L)
                {
                    /* Decode the parameter set in the component. */
                    printf("Received Return Result component.\n");
                    TEST_DecodeGSMMAPResult( &cpt, handle );
                }
                return ret;
            }
        }
    } /* for(;;) */
}

static int 
TEST_PrintCommand()
{
    printf("\n\n\t**** IntelliNet Technologies, Inc. ****\n");
    printf("\t\tBasic GSMMAP Test program\n\n");

    printf("To send a message from the following list, \n");
    printf("\ttype in the corresponding number:-\n\n");

    printf("    %d) SendIdentification.        %d) RestoreData.\n",
            TEST_SENDID, TEST_RESTDATA);
    printf("    %d) InsertSubscriberData       %d) ActivateTraceMode.\n",
            TEST_INSSUBSDATA, TEST_ACTTRMODE);
    printf("    %d) DeactivateTraceMode\n", TEST_DEACTTRMODE);
#if 0
    printf("    %d) Disconnect           %d) ForwardCall.\n",
            TEST_DISCONN, TEST_FORWDCALL);
    printf("    %d) InfoAnalyzed.\n",
            TEST_INFOANLZ);
    printf("    %d) InfoCollected.      %d) MonitorForChange.\n", 
            TEST_INFOCOLL, TEST_MONCHANGE);
    printf("    %d) MonitorSuccess      %d) NetworkBusy.\n",
            TEST_MONSUCC, TEST_NTWKBUSY);
    printf("    %d) OriginationAttempt  %d) ResourceClear.\n",
            TEST_ORIGATTMP, TEST_RESRCCLR);
    printf("    %d) ReportError         %d) SendNotification.\n",
            TEST_RPTERR, TEST_SENDNOTIF);
    printf("    %d) SendToResource      %d) StatusReported.\n",
            TEST_SENDTORSRC, TEST_STATRPTED);
    printf("    %d) TerminationAttempt  %d) TerminationNotification.\n",
            TEST_TERMATTMP, TEST_TERMNOTIF);
    printf("    %d) UpdateData          %d) UpdateRequest.\n",
            TEST_UPDDATA, TEST_UPDREQ);
#endif
    printf("\n    %d) Quit program.\n", TEST_EXIT);

    printf("\n  -> ");

    return 1;
}


