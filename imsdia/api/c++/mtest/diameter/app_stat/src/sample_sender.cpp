/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: sample_sender.cpp,v $
 * LOG: Revision 3.1.70.1.2.3.2.2.4.1.8.1  2015/05/18 05:15:09  kpnithin
 * LOG: cxdx v12 Test tool developed with new protocol file
 * LOG:
 * LOG: Revision 3.1.70.1.2.3.2.2.4.1  2014/02/12 07:07:16  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.1.70.1.2.3.2.2  2013/08/15 04:58:40  ncshivakumar
 * LOG: Updated for sy application
 * LOG:
 * LOG: Revision 3.1.70.1.2.3.2.1  2013/07/17 06:05:25  jkchaitanya
 * LOG: BugId:- 1874, Request-Id 1177 Changes for the crash gy simulator
 * LOG:
 * LOG: Revision 3.1.70.1.2.3  2013/07/01 07:32:36  nazad
 * LOG: changes for memory Leak, Review Request 1041
 * LOG:
 * LOG: Revision 3.1.70.1.2.2  2013/06/11 13:28:44  nazad
 * LOG: Revert back the leak fix
 * LOG:
 * LOG: Revision 3.1.70.1.2.1  2013/06/11 12:51:35  nazad
 * LOG: Memory leak fix... bcmd
 * LOG:
 * LOG: Revision 3.1.70.1  2013/04/07 03:58:51  cprem
 * LOG: Changes made to fix test-tool crash during switchover of DRE
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/02/01 12:05:14  kamakshilk
 * LOG: exit added after AppTerminate
 * LOG:
 * LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 * LOG: Common files required for static setup
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.8  2006/06/02 09:20:58  yranade
 * LOG: Minor update
 * LOG:
 * LOG: Revision 1.7  2006/06/02 04:48:58  kamakshilk
 * LOG: RfRo function calls
 * LOG:
 * LOG: Revision 1.6  2006/04/25 15:33:39  nvijikumar
 * LOG: Documentation
 * LOG:
 * LOG: Revision 1.5  2006/04/22 00:07:50  ahanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2006/04/17 16:25:11  yranade
 * LOG: Load Generator Support.
 * LOG:
 * LOG: Revision 1.3  2006/03/24 05:21:51  nvijikumar
 * LOG: Added exit case for Menu
 * LOG:
 * LOG: Revision 1.2  2006/03/08 08:48:17  nvijikumar
 * LOG: Baseline for GqGqprime sample applications
 * LOG:
 * LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 * LOG: First Version of Demo Application.
 * LOG:
 *
 * ID: $Id: sample_sender.cpp,v 3.1.70.1.2.3.2.2.4.1.8.1 2015/05/18 05:15:09 kpnithin Exp $
 ****************************************************************************/
#ident "$Id: sample_sender.cpp,v 3.1.70.1.2.3.2.2.4.1.8.1 2015/05/18 05:15:09 kpnithin Exp $"

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>
#include <app.h>

using namespace std;
using namespace its;
using namespace engine;

/* These functions need to be Definied in the specific Interfaces */
extern int DisplayAppMenu();
extern int HandleDiaAppMsg(const diameter::CommandImpl *impl, 
                                          unsigned int &sIdx);
extern int HandleDiaAppMsg(const DIA_BASE_CMD *bcmd, const diameter::CommandImpl *impl,unsigned int &sIdx);

extern void UpdateIndications(ITS_UINT indType);
#ifdef FOR_IWF
std::string sessionIdForCallFlow;
ITS_UINT opfromserv = 0;
#endif
extern "C"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Method to invoke the proper interface Display functions 
 *      To send the Request Messages to the stack
 *
 *  Input Parameters:
 *      thr - type ThreadPoolThread. arg - type void..
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

void SenderThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret;
    int choice;
    string inStr;

    if (appMode == LOAD_TEST)
    {
        GenerateLoad();
        return;
    }
    
    while (1)
    {
        cout << endl << "Enter youe choice"
            << endl << "1: Send "
            << endl << "9: To exit now"
            << endl;

        cin >>inStr;
        choice = atoi(inStr.c_str());
        // Display Based on the Choice made in the Menu

        switch (choice)
        {
        case 1:
            ret = DisplayAppMenu();
            break;

        case 9:
            AppTerminate();
            exit(1);

        default:
            cout << "Invalid Choice " << endl;
            break;
        }
    }

}

void AppThreadFunc(its::ThreadPoolThread* thr, void* arg)
{
    int ret;
    engine::Worker* work = (engine::Worker *)thr;

    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    Event evt;

    while (!work->GetExit())
    {
        /* 
         * Wait For Event from the event queue.
         * GetNextEvent is a BlockingCall that returns
         * when an Event is posted onto the associated worker 
         * taskqueue
         */
        if (work->GetNextEvent(evt) == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("Received an event on Instance %d", inst));

            // If the event source is from the diameter stack,
            // handle that event.
            switch (evt.GetSource())
            {
                case ITS_DIA_SRC:
                    {
                        APP_TRACE_DEBUG(("Received Event from ITSDiameter Stack"));

                        // Create an instance DiaMsg to handle Received Message
                        DiaMsg * dMsg = NULL;
                        const DIA_BASE_CMD *bcmd =NULL;

                        // Receive the message from the event received
                        if(ReceiveMessageFromEvent(evt,dMsg)==ITS_SUCCESS)
                        {
                            // If the message is the indication from the stack,
                            // Handle Indication. In this case, we simply update
                            // the indication statistics.

                            if(dMsg->IsIndication())
                            {
                                APP_TRACE_DEBUG(("Received Indication<%d> from Stack\n"
                                            , dMsg->GetIndication()));

                                UpdateIndications(dMsg->GetIndication());
                            }
                            // If not an indication, then it is a Command Message
                            else
                                /*{
                                  const diameter::CommandImpl* impl = 
                                  dMsg->GetCommandImpl();
                                  unsigned int sesIdx = dMsg->GetSessionIndex();
                                  HandleDiaAppMsg(impl, sesIdx);
                                  }*/
                            {
                                const DIA_BASE_CMD* cmd = dMsg->GetMsgFlow();
                                //cout << "Received a message with command code of : " << (diameter::Command*)((const_cast<diameter::DiaMsgFlow*>(cmd))->GetBaseGenCommand())->getHeader().code << endl << endl << endl;
                                if (cmd->getCommandCode() == 272 || //S9_CC_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 271 || //S9_RA_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 264 || //S9_RA_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 274 || //S9_RA_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 275 || //S9_RA_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 258 || //S9_RA_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 316 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 317 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 319 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 320 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 321 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 322 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 323 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 324 || //S6A_AI_MSG_CMD_CODE ||
                                        cmd->getCommandCode() == 318 || //S6A_UL_MSG_CMD_CODE)||
                                        cmd->getCommandCode() == 300 || //CXDX_UAR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 301 || //CXDX_SAR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 302 || //CXDX_LIR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 303 || //CXDX_MAR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 304 || //CXDX_RTR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 305 || //CXDX_PPR_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 8388635||  //SY_SL_MSG_CMD_CODE)
                                        cmd->getCommandCode() == 8388636 )//SY_SN_MSG_CMD_CODE)
                                        {
                                            bcmd = dMsg->GetMsgFlow();

                                            const diameter::CommandImpl* impl = dMsg->GetCommandImpl();
                                            unsigned int sesIdx = dMsg->GetSessionIndex();
                                            //HandleDiaAppMsg(impl, sesIdx);
                                            HandleDiaAppMsg(bcmd,impl,sesIdx);

                                        }

                                else
                                {
                                    int recent_msg_idx;
                                    //int recent_msg_idx = appStats.recent_msg_idx++ % MAX_MSGS_TO_DISPLAY;
                                    //appStats.last_processed_msgs[recent_msg_idx] = "Received Capabilities Exchange Message ";                      
                                    //appStats.recent_msg_idx = recent_msg_idx+1;
                                }
                            }

                            if (bcmd && dMsg && dMsg->GetMessageType() != ITS_DIA_MSG_TYPE_IND_WITH_DATA)
                            {
                                delete bcmd;
                                bcmd = NULL;
                            }

                            if (dMsg)
                            {
                                delete dMsg;
                                dMsg = NULL;
                            }
                        }
                    }
                    break;

                default:
                    APP_TRACE_ERROR(("Unknown Event Received"));
                    break;
            }
        }
    }
}

#ifdef FOR_IWF
void diep(char *s)
{
    perror(s);
    exit(1);
}
#define PORT 3355
#define BUFLEN 10
void ScenarioRecvThreadFunc(its::ThreadPoolThread* thr, void* arg)
{
    int ret,newsockfd;
    struct sockaddr_in si_me, si_other;
    int s;
    socklen_t slen = sizeof(si_other);
    char buf[BUFLEN] = {'\0'};

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
    {   
        diep("socket");
    }   

    memset((char *) &si_me, 0, sizeof(si_me));
    memset((char *) &si_other, 0, sizeof(si_other));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&si_me, sizeof(struct sockaddr))==-1)
    {   
        diep("bind");
    }   
    engine::Worker* work = (engine::Worker *)thr;

    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    Event evt;
    socklen_t clilen = sizeof(si_other);
    while (!work->GetExit())
    {
        /* 
         * Wait For Event from the event queue.
         * GetNextEvent is a BlockingCall that returns
         * when an Event is posted onto the associated worker 
         * taskqueue
         */
        printf("\nWaiting for call flow number to receive");

        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_other, &slen)==-1)
        {   
            diep("recvfrom()");
        }
        printf("\nReceived packet from %s:%d\nData: %s\n\n",
                inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port), buf);

        int receivedValue = atoi(buf);
        if((receivedValue > 0) && (receivedValue < 20))
        {
            printf("\ncallflow number received = %d",receivedValue);
            opfromserv = receivedValue;
        }
    }
    close(s);
}
#endif
