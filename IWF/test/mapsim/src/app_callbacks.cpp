/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: app_callbacks.cpp,v $
 * LOG: Revision 1.1.2.3  2013/03/18 13:00:12  jvikas
 * LOG: Changes taken from map/src for CCITT/ANSI.
 * LOG:
 * LOG: Revision 1.1.2.2  2013/03/18 09:45:00  jvikas
 * LOG: mapsim changes.
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/12 14:09:19  jvikas
 * LOG: Map Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 02:44:43  lakshman
 * LOG: update tcap tests - add gprs and randomize responses.
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
 * LOG: checkin first version of MAP test along with CAP.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_callbacks.cpp,v 1.1.2.3 2013/03/18 13:00:12 jvikas Exp $"

#include <iostream>
#include <sys/time.h>

#include <its++.h>
#include <engine++.h>
#include <its_service.h>
#include <its_iniparse.h>

#include <its_sctp_trans.h>

#include <its_gen_disp.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>

// Generated TCAP components are here.
#include <app_const.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

extern TCAPMsgs *tcapMsgs[4];
//extern ITS_INT Notify_PreFunc();

extern "C" void SERVICE_SetStopped();


extern "C" 
void SenderThreadFunc(its::ThreadPoolThread* thr, void* arg);

ApplicationStats appStats;
extern int DisplayMainWindow();
extern void GetMode();
extern int DisplayMessageDetails();
extern void printMainMenu();
extern void printHLRMenu();
extern char* sim;

/*
 * This object isto keep track of number of inboud/outbound messsages
 * sent and received.
 */
TcapStats stats;

/*
 * This is to keep track of number of IMAL up transports.
 */
TransportState transStateInfo;

/*
 * This semaphore isto signal the collector function in main
 * after intializating the engine pools
 */
Semaphore* appSem = NULL;

/*
 * TCAP messages encode/decode functions are here.
 */
TCAPMsgs*  appMsgs = NULL;


ITS_BOOLEAN trans_state_flag = ITS_FALSE;
ITS_INT transportInstance;
int decision_Making;

void SignalHandler(int signo)
{
   /*even this can also be called from EnginePostFunc*/
   //stats.PrintTCAPStats();

   SERVICE_SetStopped();

   exit(0);
}

/***********************************************************************
 *
 *  Implementation for worker pool call backs.
 *  These call backs generate TCAP messages in multi user mode.
 *
 **********************************************************************/
extern "C"
{

int SendResponses(TCAP_Dialogue*, TCAP_Component**, engine::Worker*);

void WP_Dispatch(ThreadPoolThread* thr, void* arg);
void DisplayThreadFunc2(ThreadPoolThread* thr, void* arg);

ITS_USHORT
ROUTE_SendToAPP(ITS_HDR* h, ITS_EVENT* ev)
{
    return (transportInstance);
}

ITS_USHORT
SendToAPP1(ITS_HDR* h, ITS_EVENT* ev)
{
    if (h->type == ITS_TCAP)
    {
        if (h->context.dialogue_id % 2 != 0)
           return (transportInstance);
    }
    return ITS_NO_SRC;
}

ITS_USHORT
SendToAPP2(ITS_HDR* h, ITS_EVENT* ev)
{
    if (h->type == ITS_TCAP)

    {
        if (h->context.dialogue_id % 2 == 0)
           return (transportInstance);
    }
    return ITS_NO_SRC;
}


void ENGINE_PreFunc(void)
{
   int ret = 0;

   EnableAppTracing();


   //Get the resource manager

    ResourceManager *rf = new ResourceManager(APPL_GetConfigFileName());

    // sequential parsing
    char key[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];

    rf->Lock();
    rf->Rewind(NULL);

    while (rf->GetKeyName(NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&

        rf->GetKeyValue(NULL, value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strcmp(key, "TRANSPORT_TYPE") == 0)
        {
            if (strcmp(value, "SCTP") == 0)
            {
                CALLBACK_AddCallback(SCTPTRAN_ManagementCallbacks,
                         TCAPUtils::RegisterSCTPTransCallback, NULL);

           }
        }
        if (strcmp(key,"APP_TRACE") == 0)
        {
            itstest::enableTrace = atoi(value);
        }
    }

   rf->Unlock();

   delete rf;

   /* Register GTT callback */
#if 0
   CALLBACK_AddCallback(SCCP_GlobalTitleTranslator,
                        TCAPUtils::RegisterGTTCallback, NULL);

   APP_TRACE_DEBUG(("Added GTT Callback to the IntelliSS7."));
#endif


   ITS_ThreadPoolEntry ent;

   /*
    *  Dispatch Receive thread here
   */
   if(workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
   {
       engine::Worker* work = (engine::Worker *)ent.GetThread();

       if (work == NULL)
       {
            workerPool->ReturnToAvailThreads(ent);
       }

       if(work != NULL)
       {
           ret = workerPool->DispatchOnThread(ent, WP_Dispatch, NULL);

           if (ret != ITS_SUCCESS)
           {
                 workerPool->ReturnToAvailThreads(ent);

                 ITS_THROW_ERROR(ret);
           }
       }
   }

   /*
    *  Dispatch Sender thread here
   */
   if(workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
   {
       engine::Worker* work = (engine::Worker *)ent.GetThread();

       if (work == NULL)
       {
            workerPool->ReturnToAvailThreads(ent);
       }

       if(work != NULL)
       {
           ret = workerPool->DispatchOnThread(ent, SenderThreadFunc, NULL);

           if (ret != ITS_SUCCESS)
           {
                 workerPool->ReturnToAvailThreads(ent);

                 ITS_THROW_ERROR(ret);
           }
       }
   }

   //GetMode();
   /*
    *  Dispatch Display thread here
   */
   if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
   {
       engine::Worker* work = (engine::Worker *)ent.GetThread();
       if (work)
       {
           ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)DisplayThreadFunc2, NULL);
           /* If the dispatch fails, return the thread to the thread pool
              and throw the error. */
           if (ret != ITS_SUCCESS)
           {
               workerPool->ReturnToAvailThreads(ent);
               ITS_THROW_ERROR(ret);
           }
        }
        else
        {
            workerPool->ReturnToAvailThreads(ent);
        }
   }

   //GetMode();

   signal(SIGINT, SignalHandler);

   printf("Added GTT callbacks:\n");
   fflush(stdout);

   return;
}

/**********************************************************************
 *
 * Here I will call ITS_Initialize and block the thread forever by
 * calling GetNextEvent. I will be depending on 
 * PreInitialize function only for getting a thread from WorkerPool
 *
 *********************************************************************/ 
void WP_Dispatch(ThreadPoolThread* thr, void* arg)
{
   engine::Worker* work = (engine::Worker *)thr;
   ITS_HANDLE handle = NULL;

   ITS_USHORT inst = work->GetInstance();
   Event evt;

   APP_TRACE_DEBUG(("WP_Dispatch"));

   handle = ITS_Initialize(work->GetMask(), inst);

   transportInstance = work->GetInstance();

   if (tcapMsgs[APP_CCITT] != NULL)
   {
       tcapMsgs[APP_CCITT]->InitExternals();
   }

   while(!work->GetExit())
   {
       if(work->GetNextEvent(evt) == ITS_SUCCESS)
       {
            APP_TRACE_DEBUG(("Recieved an event on Instance %d", 
                     TRANSPORT_INSTANCE(handle)));

           if(evt.GetSource() == APP_TCAP_ANSI_SRC)
           {
               APP_TRACE_DEBUG(("Received from TCAP_ANSI_SRC"));
               if (tcapMsgs[APP_ANSI] != NULL)
               {
                   tcapMsgs[APP_ANSI]->HandleMessage(work, evt);
               }
               else
               {
                   APP_TRACE_ERROR(("Failed to handle ANSI TCAP message"));
               }
           }
           else if(evt.GetSource() == APP_TCAP_CCITT_SRC)
           {
               APP_TRACE_DEBUG(("Received from TCAP_CCITT_SRC"));
               if (tcapMsgs[APP_CCITT] != NULL)
               {
                   tcapMsgs[APP_CCITT]->HandleMessage(work, evt);
               }
               else
               {
                   APP_TRACE_ERROR(("Failed to handle CCITT TCAP message"));
               }

           }
           else
           {
               APP_TRACE_ERROR(("Not a TCAP Source."));
           }
       }
   }
}

int
WP_GetNextEventFail(ThreadPoolThread* thr, int err)
{
   int ret = ITS_SUCCESS;

   APP_TRACE_ERROR(("WP_GetNextEventFail"));

   if(ret)
   {
      /*Tell engine to terminate the loop */
      return ITS_ENOLIST;
   }

   return ITS_SUCCESS;
}

void ResetStats()
{
    memset(&appStats.u, 0, sizeof(appStats.u));
}

void SenderThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int choice = 0;
    int ch = 0;
    engine::Worker* work = (engine::Worker *)thr;
    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    APP_TRACE_DEBUG(("SenderThreadFunc"));
    handle = ITS_Initialize(work->GetMask(), inst);
    string inStr;

    if(!TRANSPORT_INSTANCE(handle))
    {
        APP_TRACE_ERROR(("TRANSPORT FAILURE"));
    }

    if (itstest::appMode == LOAD_TEST)
    {
        return;
    }

    while (1)
    {
        std::cin >>inStr;
        ch = atoi(inStr.c_str());
        /* Take Action based on the Choice as per Main Menu */
        switch (ch)
        {
        case 1:
            /* Sending HLR Initiated Messages*/
            displayMode = 40;
            //choice = 2;
            break;

        case 2:
            /* Dispalying Message Details*/
            displayMode = 30;
            DisplayMainWindow();
            break;

        case 3:
            /* Reset All Statistics*/
            ResetStats();
            break;

        case 9:
            /* Returning to Main Menu */
            displayMode = 20;
            break;

        case 100:
            /* Sending Cancel Location Request */
            choice = 2;
            break;

        case 55:
        case 85:
        case 75:
            /* Sending Cancel Location Request */
            cout << "Currently Not Supported. Going back to Main Menu . . . ." << endl;
            sleep(2000);
            /* Returning to Main Menu */
            displayMode = 20;
            break;

        default:
            cout << "Invalid Choice: Enter Again " << endl;
            break;
        }

        if(choice==2)
        {
            switch (TCAPUtils::GetVariantType())
            {
                case APP_ANSI:
                    if (tcapMsgs[APP_ANSI] != NULL)
                    {
                        APP_TRACE_DEBUG(("ANSI Message Selected"));
                        (tcapMsgs[APP_ANSI])->SendMsgs(handle, choice);
                    }
                    else
                    {
                        APP_TRACE_CRITICAL(("Failed to send ANSI Message"));
                    }
                    break;

                case APP_CCITT:
                    if (tcapMsgs[APP_CCITT] != NULL)
                    {
                        APP_TRACE_DEBUG(("CCITT Message Selected"));
                        (tcapMsgs[APP_CCITT])->SendMsgs(handle, choice);
                    }
                    else
                    {
                        APP_TRACE_CRITICAL(("Failed to send CCITT Message"));
                    }
                    break;

                default:
                    cout << "Invalid Choice " << endl;
                    break;
            }
        }
        choice = 0;
    }
    sleep(1);
}

void DisplayThreadFunc2(its::ThreadPoolThread* thr, void* arg)
{
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);

    while (1)
    {
        //displayMode = 20;
        // Display the data
        DisplayMainWindow();
        sleep(1);
    }
}

} //End of extern C
