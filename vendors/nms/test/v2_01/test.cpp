/*********************************-*-C++-*-**********************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test.cpp,v 9.1 2005/03/23 12:56:17 cvsadmin Exp $
 *
 * LOG: $Log: test.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:56:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:10  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:06  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/09/05 22:01:57  mmiers
 * LOG: Add two tests.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:37  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.7  2000/12/05 17:36:51  hxing
 * LOG: Add mtp3 messages
 * LOG:
 * LOG: Revision 3.6  2000/12/01 00:51:50  hxing
 * LOG: isup integration
 * LOG:
 * LOG: Revision 3.5  2000/11/30 23:15:46  mmiers
 * LOG: Change ini file names
 * LOG:
 * LOG: Revision 3.4  2000/11/30 18:33:30  hxing
 * LOG: integration of isup
 * LOG:
 * LOG: Revision 3.3  2000/10/03 23:53:46  labuser
 * LOG:
 * LOG: Debugging under Solaris
 * LOG:
 * LOG: Revision 3.2  2000/10/02 22:40:59  hxing
 * LOG: Work in solaris
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:15  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.13  2000/08/15 23:08:46  hxing
 * LOG: Get the affected point code for MTP3Pause/Resume.
 * LOG:
 * LOG: Revision 1.12  2000/08/04 23:35:57  hxing
 * LOG: Add the ITS feature "itsNMS_Class", start ANSI
 * LOG:
 * LOG: Revision 1.11  2000/08/03 21:54:02  hxing
 * LOG: Handle some MTP3 messages
 * LOG:
 * LOG: Revision 1.10  2000/07/31 21:39:17  hxing
 * LOG: Testing more ies and more messages
 * LOG:
 * LOG: Revision 1.9  2000/07/27 23:00:20  hxing
 * LOG: Testing with more optional IEs
 * LOG:
 * LOG: Revision 1.8  2000/07/25 21:15:22  hxing
 * LOG: Now ITS_Terminate() doesn't crush.
 * LOG:
 * LOG: Revision 1.7  2000/07/20 23:07:48  hxing
 * LOG: IAM is sent out correctly.
 * LOG:
 * LOG: Revision 1.6  2000/07/19 16:04:57  ite
 * LOG: Add more prints
 * LOG:
 * LOG: Revision 1.5  2000/07/18 23:08:02  ite
 * LOG: Fix bug in isup vendor lib.
 * LOG:
 * LOG: Revision 1.4  2000/07/17 21:59:28  ite
 * LOG: Modify .ini files
 * LOG:
 * LOG: Revision 1.3  2000/07/17 20:17:23  hxing
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.2  2000/07/14 22:50:41  hxing
 * LOG: Add more print
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:37  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <exception>
#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif

#include <its.h>
#include <its_app.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_transports.h>
#include <its_ss7_trans.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif

#include <UnitTest.h>

#include "sendISUPMsg.h"
#include "printISUPMsg.h"

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

#if !defined(HPUX)
using namespace std;
#endif

// temp add for missing external symbol
CALLBACK_Manager*   ISUP_CCITT_ManagementCallbacks = NULL;
CALLBACK_Manager*   ISUP_ANSI_ManagementCallbacks = NULL;
CALLBACK_Manager*   SCCP_CCITT_ManagementCallbacks = NULL;
CALLBACK_Manager*   SCCP_ANSI_ManagementCallbacks = NULL;
CALLBACK_Manager*   MTP3_CCITT_ManagementCallbacks = NULL;
CALLBACK_Manager*   MTP3_ANSI_ManagementCallbacks = NULL;

static ITS_HANDLE   isup_handle;
static ITS_HDR      hdr;
static ITS_THREAD   borderTransportThread;

////////////////////////////////////////////
//   temp add for mtp3

int TestSendMTP3Msg( ITS_HANDLE handle);

/*------------------------------------------------------------------------------
 *
 *  termination handler
 */
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    if (isup_handle)
    {
        THREAD_KillThread(&borderTransportThread);

        ITS_Terminate(isup_handle);
    }

    ITS_GlobalStop();

    exit(0);

#if defined(WIN32)
    return 1;
#endif
}

/*------------------------------------------------------------------------------
 *
 *  Synchronization object (semaphore) used to synchronize primary thread and
 *  border transport thread.
 */

static ITS_SEMAPHORE borderTransportSemaphore;

/*------------------------------------------------------------------------------
 *
 *  Boolean to be set to true to stop border transport thread.
 */

static ITS_BOOLEAN borderTransportStopRequested = ITS_FALSE;


/*------------------------------------------------------------------------------
 *
 *  Dump ITS_EVENT
 */
void DumpITSEvent(ITS_EVENT* ev)
{
    int i;

    cout << "\nEvent came from: " << ev->src << endl;
    cout << "The length was:  " << ev->len << endl;

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }
}

/*------------------------------------------------------------------------------
 *
 *  Border transport thread function.
 */

THREAD_RET_TYPE
BorderTransportThreadDispatchFunction(void* arg)
{
    ITS_HANDLE borderTransportHandle = NULL; 
    ITS_EVENT event;

    memset(&event, 0, sizeof(ITS_EVENT));

    borderTransportHandle = isup_handle;

    if (borderTransportHandle == NULL)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ITS_ENOTRANSPORT));

        THREAD_NORMAL_EXIT;
    }

    SEMA_PostSemaphore(&borderTransportSemaphore);

    while (!borderTransportStopRequested)
    {
        int res = ITS_GetNextEvent(borderTransportHandle, &event);
        
        if (res != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));
        }
        else
        {
            DumpITSEvent(&event);

            if ( event.src == ITS_ISUP_SRC )
            {
                if (ReceiveISUPMsg(borderTransportHandle, 
                                   &event) == ITS_SUCCESS)
                {
                    printf("ISUP msg receive success\n");
                }
            }
            ////////////////////////////////////////////////
            if ( event.src == ITS_MTP3_SRC )
            {
                printf("MTP3 msg received\n");
            }
            ////////////////////////////////////////////////
        }
    }

    SEMA_PostSemaphore(&borderTransportSemaphore);

    THREAD_NORMAL_EXIT;
}

/*-----------------------------------------------------------------------------
 *
 *  unit tester derived class
 */
class NMS_ISUP_UnitTest : public UnitTest
{
public:
    NMS_ISUP_UnitTest() : UnitTest("NMS_ISUP_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};



void
NMS_ISUP_UnitTest::DoCommand(istream& cmdLine)
{       
    int result = 0;
    ITS_USHORT cic;

    printf("\nEnter circuit : ");
    cin >> cic;
    hdr.context.CIC = cic;

    if (Cmd("ACM", "SendACM", ""))
    {
        result = TestSendACMRequest( isup_handle, &hdr );
        printf("\nSend ACM return result = %d\n", result);
    }   
    else if (Cmd("ANM", "SendANM", ""))
    {
        result = TestSendANMRequest( isup_handle, &hdr );
        printf("\nSend ANM return result = %d\n", result);
    }
    else if (Cmd("BLA", "SendBLA", ""))
    {
        result = TestSendBLARequest( isup_handle, &hdr );
        printf("\nSend BLA return result = %d\n", result);
    }
    else if (Cmd("BLO", "SendBLO", ""))
    {
        result = TestSendBLORequest( isup_handle, &hdr );
        printf("\nSend BLO return result = %d\n", result);
    }
    else if (Cmd("CCR", "SendCCR", ""))
    {
        result = TestSendCCRRequest( isup_handle, &hdr );
        printf("\nSend CCR return result = %d\n", result);
    }
    else if (Cmd("CFN", "SendCFN", ""))
    {
        result = TestSendCFNRequest( isup_handle, &hdr );
        printf("\nSend CFN return result = %d\n", result);
    }
    else if (Cmd("CGB", "SendCGB", ""))
    {
        result = TestSendCGBRequest( isup_handle, &hdr );
        printf("\nSend CGB return result = %d\n", result);
    }
    else if (Cmd("CGBA", "SendCGBA", ""))
    {
        result = TestSendCGBARequest( isup_handle, &hdr );
        printf("\nSend CGBA return result = %d\n", result);
    }
    else if (Cmd("CGU", "SendCGU", ""))
    {
        result = TestSendCGURequest( isup_handle, &hdr );
        printf("\nSend CGU return result = %d\n", result);
    }
    else if (Cmd("CGUA", "SendCGUA", ""))
    {
        result = TestSendCGUARequest( isup_handle, &hdr );
        printf("\nSend CGUA return result = %d\n", result);
    }
    else if (Cmd("COT", "SendCOT", ""))
    {
        result = TestSendCOTRequest( isup_handle, &hdr );
        printf("\nSend COT return result = %d\n", result);
    }
    else if (Cmd("CPG", "SendCPG", ""))
    {
        result = TestSendCPGRequest( isup_handle, &hdr );
        printf("\nSend CPG return result = %d\n", result);
    }
    else if (Cmd("CQM", "SendCQM", ""))
    {
        result = TestSendCQMRequest( isup_handle, &hdr );
        printf("\nSend CQM return result = %d\n", result);
    }
    else if (Cmd("FOT", "SendFOT", ""))
    {
        result = TestSendFOTRequest( isup_handle, &hdr );
        printf("\nSend FOT return result = %d\n", result);
    }
    else if (Cmd("GRS", "SendGRS", ""))
    {
        result = TestSendGRSRequest( isup_handle, &hdr );
        printf("\nSend GRS return result = %d\n", result);
    }
    else if (Cmd("IAM", "SendIAM", ""))
    {
        result = TestSendIAMRequest( isup_handle, &hdr );
        printf("\nSend IAM return result = %d\n", result);
    }
    else if (Cmd("INF", "SendINF", ""))
    {
        result = TestSendINFRequest( isup_handle, &hdr );
        printf("\nSend INF return result = %d\n", result);
    }
    else if (Cmd("INR", "SendINR", ""))
    {
        result = TestSendINRRequest( isup_handle, &hdr );
        printf("\nSend INR return result = %d\n", result);
    }
    else if (Cmd("LPA", "SendLPA", ""))
    {
        result = TestSendLPARequest( isup_handle, &hdr );
        printf("\nSend LPA return result = %d\n", result);
    }
    else if (Cmd("PAM", "SendPAM", ""))
    {
        result = TestSendPAMRequest( isup_handle, &hdr );
        printf("\nSend PAM return result = %d\n", result);
    }
    else if (Cmd("REL", "SendREL", ""))
    {
        result = TestSendRELRequest( isup_handle, &hdr );
        printf("\nSend REL return result = %d\n", result);
    }
    else if (Cmd("RES", "SendRES", ""))
    {
        result = TestSendRESRequest( isup_handle, &hdr );
        printf("\nSend RES return result = %d\n", result);
    }
    else if (Cmd("RLC", "SendRLC", ""))
    {
        result = TestSendRLCRequest( isup_handle, &hdr );
        printf("\nSend RLC return result = %d\n", result);
    }
    else if (Cmd("RSC", "SendRSC", ""))
    {
        result = TestSendRSCRequest( isup_handle, &hdr );
        printf("\nSend RSC return result = %d\n", result);
    }
    else if (Cmd("SUS", "SendSUS", ""))
    {
        result = TestSendSUSRequest( isup_handle, &hdr );
        printf("\nSend SUS return result = %d\n", result);
    }
    else if (Cmd("UBA", "SendUBA", ""))
    {
        result = TestSendUBARequest( isup_handle, &hdr );
        printf("\nSend UBA return result = %d\n", result);
    }
    else if (Cmd("UBL", "SendUBL", ""))
    {
        result = TestSendUBLRequest( isup_handle, &hdr );
        printf("\nSend UBL return result = %d\n", result);
    }

    /////////////////////////////////////////////////////
    else if (Cmd("MTP3", "SendMTP3", ""))
    {
        result = TestSendMTP3Msg( isup_handle );
        printf("\nSend MTP3 msg return result = %d\n", result);
    }
    /////////////////////////////////////////////////////

#if defined (ANSI)
    else if (Cmd("CRA", "SendCRA", ""))
    {
        result = TestSendCRARequest( isup_handle, &hdr );
        printf("\nSend CRA return result = %d\n", result);
    }
    else if (Cmd("CRM", "SendCRM", ""))
    {
        result = TestSendCRMRequest( isup_handle, &hdr );
        printf("\nSend CRM return result = %d\n", result);
    }
    else if (Cmd("CVR", "SendCVR", ""))
    {
        result = TestSendCVRRequest( isup_handle, &hdr );
        printf("\nSend CVR return result = %d\n", result);
    }
    else if (Cmd("CVT", "SendCVT", ""))
    {
        result = TestSendCVTRequest( isup_handle, &hdr );
        printf("\nSend CVT return result = %d\n", result);
    }
    else if (Cmd("EXM", "SendEXM", ""))
    {
        result = TestSendACMRequest( isup_handle, &hdr );
        printf("\nSend EXM return result = %d\n", result);
    }
#endif /*  ANSI */

#if defined (CCITT)
    else if (Cmd("CON", "SendCON", ""))
    {
        result = TestSendCONRequest( isup_handle, &hdr );
        printf("\nSend CON return result = %d\n", result);
    }
    else if (Cmd("FAA", "SendFAA", ""))
    {
        result = TestSendFAARequest( isup_handle, &hdr );
        printf("\nSend FAA return result = %d\n", result);
    }
    else if (Cmd("FAC", "SendFAC", ""))
    {
        result = TestSendFACRequest( isup_handle, &hdr );
        printf("\nSend FAC return result = %d\n", result);
    }
    else if (Cmd("FAR", "SendFAR", ""))
    {
        result = TestSendFARRequest( isup_handle, &hdr );
        printf("\nSend FAR return result = %d\n", result);
    }
    else if (Cmd("FRJ", "SendFRJ", ""))
    {
        result = TestSendFRJRequest( isup_handle, &hdr );
        printf("\nSend FRJ return result = %d\n", result);
    }
    else if (Cmd("IDR", "SendIDR", ""))
    {
        result = TestSendIDRRequest( isup_handle, &hdr );
        printf("\nSend IDR return result = %d\n", result);
    }
    else if (Cmd("IRS", "SendIRS", ""))
    {
        result = TestSendIRSRequest( isup_handle, &hdr );
        printf("\nSend IRS return result = %d\n", result);
    }
    else if (Cmd("NRM", "SendNRM", ""))
    {
        result = TestSendNRMRequest( isup_handle, &hdr );
        printf("\nSend NRM return result = %d\n", result);
    }
    else if (Cmd("OLM", "SendOLM", ""))
    {
        result = TestSendOLMRequest( isup_handle, &hdr );
        printf("\nSend OLM return result = %d\n", result);
    }
    else if (Cmd("SAM", "SendSAM", ""))
    {
        result = TestSendSAMRequest( isup_handle, &hdr );
        printf("\nSend SAM return result = %d\n", result);
    }
    else if (Cmd("SGM", "SendSGM", ""))
    {
        result = TestSendSGMRequest( isup_handle, &hdr );
        printf("\nSend SGM return result = %d\n", result);
    }
    else if (Cmd("UPA", "SendUPA", ""))
    {
        result = TestSendUPARequest( isup_handle, &hdr );
        printf("\nSend UPA return result = %d\n", result);
    }
    else if (Cmd("UPT", "SendUPT", ""))
    {
        result = TestSendUPTRequest( isup_handle, &hdr );
        printf("\nSend UPT return result = %d\n", result);
    }
    else if (Cmd("USR", "SendUSR", ""))
    {
        result = TestSendUSRRequest( isup_handle, &hdr );
        printf("\nSend USR return result = %d\n", result);
    }
#endif /* CCITT */  
}


/*-----------------------------------------------------------------------------
 *  main program
 */
int
main(int argc, char **argv)
{
    int res = 0;
    int boardNum;
    void *status = NULL;

    /* TODO: tmp */
    hdr.context.CIC = 0;

    memset(&borderTransportThread, 0, sizeof(ITS_THREAD)); 

    printf("\nBegin NMS ISUP send test...\n");

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif    
   
    if (argc == 2)
    {
        boardNum = atoi(argv[1]);
    }
    else
    {
        printf("\nEnter boardNumber(instance number) (1 or 2): ");
        scanf("%d", &boardNum);
    }

    /*-------------------------------------------------------------------
     * Setting the name of the application. The application name is the
     * name of the ini file read by IntelliSS7.
     */
    if (boardNum == 1)
    {
        //APPL_SetName("board1");
        APPL_SetName("NMS_Inst1");
    }
    else
    {
        //APPL_SetName("board2");
        APPL_SetName("NMS_Inst2");
    }

    ITS_AddFeature(itsNMS_Class);

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 subsystems initialization (including licensing).
     */

    res = ITS_GlobalStart(ITS_MTP3 | ITS_ISUP);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));
        
        exit(EXIT_FAILURE);
    }

    /*--------------------------------------------------------------------------
     *
     *  Create transport.
     */
    ITS_UINT initMask = (ITS_MTP3 | ITS_ISUP | ITS_TRANSPORT_SS7 | 
                         ITS_TRANSPORT_SINGLE_USER);
    
    //isup_handle = (ITS_HANDLE)ITS_Initialize(initMask, 2);
    isup_handle = (ITS_HANDLE)ITS_Initialize(initMask, boardNum);

    if (isup_handle == NULL)
    {
        printf("\nIntelliSS7 Error <%s>.\n", 
               ITS_GetErrorText(ITS_ENOTRANSPORT));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }    

    /*--------------------------------------------------------------------------
     *        
     *  o   Create border transport semaphore.
     *
     *  o   Create border transport thread object.
     *  
     *  o   Start border transport thread.
     *
     *  o   Wait for border transport thread (synchronization point).
     */
    res = SEMA_CreateSemaphore(&borderTransportSemaphore, 0);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    res = THREAD_CreateThread(
            &borderTransportThread,
            0,
            BorderTransportThreadDispatchFunction,
            NULL,
            ITS_TRUE);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    res = SEMA_WaitSemaphore(&borderTransportSemaphore);

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        ITS_GlobalStop();

        exit(EXIT_FAILURE);
    }

    NMS_ISUP_UnitTest test;

    test.ExecuteCommandsFromStream();


    /*--------------------------------------------------------------------------
     *
     *  o   Stop border transport thread.
     *
     *  o   Delete border transport thread (can be done even if still running).
     *
     *  o   Delete border transport semaphore.
     */
    borderTransportStopRequested = ITS_TRUE;

    SEMA_WaitSemaphore(&borderTransportSemaphore);

    SEMA_DeleteSemaphore(&borderTransportSemaphore);

    THREAD_WaitForThread(&borderTransportThread, &status);

    THREAD_DeleteThread(&borderTransportThread);

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 termination.
     */

    ITS_Terminate(isup_handle);

    ITS_GlobalStop();

    ITS_RemFeature(itsNMS_Class);

    return ITS_SUCCESS;
}


int TestSendMTP3Msg( ITS_HANDLE handle)
{ 
    ITS_EVENT mtp3Event;
    MTP3_HEADER mtp3Hdr;
    int instance = 0;

    while (instance != 1 && instance != 2 )
    {
        cout << "input the boardnum bound to (1 or 2):";
        cin >> instance;
    }

    mtp3Hdr.sio = 3;

    if (instance == 1 )    /* opc = 0.1.1 (0x101) dpc = 0.1.2 (0x102) */
    {
        mtp3Hdr.label.data[0] = 0x02;
        mtp3Hdr.label.data[1] = 0x01;
        mtp3Hdr.label.data[2] = 0x01;
        mtp3Hdr.label.data[3] = 0x01;
    }
    else
    {
        mtp3Hdr.label.data[0] = 0x01;
        mtp3Hdr.label.data[1] = 0x01;
        mtp3Hdr.label.data[2] = 0x02;
        mtp3Hdr.label.data[3] = 0x01;
    }

    ITS_OCTET data[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };

    if ( MTP3_Encode(&mtp3Event, MTP3_MSG_USER_DATA, &mtp3Hdr, data, 5) 
         != ITS_SUCCESS )
    {
        cout << "MTP3_Encode error!!" << endl;

        return !ITS_SUCCESS;
    }

    mtp3Event.src = ITS_SCCP_SRC;

    cout << "Dump the mtp3 message before sending" << endl;
    
    DumpITSEvent(&mtp3Event);

    TRANSPORT_PutEvent(instance, &mtp3Event);

    return 0;
}
