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
 * LOG: $Log: appMain.cpp,v $
 * LOG: Revision 1.1.2.1  2014/07/29 09:49:58  jkchaitanya
 * LOG: added a new directory cap_sample useful for load testing
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/05/29 07:43:37  jsarvesh
 * LOG: Added Logs For SSN Number And Hardcoding GTT Route To 1 As Not Supported Now
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/02/14 09:55:16  brajappa
 * LOG: ISD sending withing UGLA is handled through command line, handling readyForSM
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
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
#ident "$Id: appMain.cpp,v 1.1.2.1 2014/07/29 09:49:58 jkchaitanya Exp $"

#include <iostream>
#include <stdlib.h>

#include <signal.h>
#include <sched.h>

#include <its++.h>
#include <engine++.h>

#include <its_route.h>

#include <app_const.h>
#include <app_msgs.h>
#include <app_trace.h>
#include <app_stats.h>
#include <app_dbc.h>

#if defined(DMALLOC)
#include <dmalloc.h>
#endif

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#define ITS_ENOLICENSE  ITS_SUCCESS

int numReceiverThreads = 1;
int numSenderThreads = 1;
const int BUF_SIZE = 1024;
TCAPMsgs *tcapMsgs[4];

extern "C" void PostFunc();

extern Mutex* appMtx;

extern TcapStats stats;

extern TCAPMsgs* appMsgs;

int  parseArguments(int, const char**);

void Usage(const char**);

ITS_USHORT SelectApplication(ITS_HDR*, ITS_EVENT*);

#include <its_gen_disp.h> /* if needed */

int main(int argc, const char** args)
{
   int ret;
 
 
#if defined (REALTIME_CLASS)
   struct sched_param sparm;

   sparm.sched_priority = 40; /* you might try 40 as well */
   ret = sched_setscheduler(getpid(), SCHED_RR, &sparm);
   if (ret < 0)
   {
       abort();
   }
#endif

   //appSem = new Semaphore(0);
   ret = parseArguments(argc, args);

    for(int i=0;i<4;i++)
    {
        tcapMsgs[i] = NULL;
    }
#if defined(DEF_CCITT)
    ITUTcapMsgs *ituInst = ITUTcapMsgs::GetItuInstance();
    if (ituInst != NULL)
    {
        ituInst->SetSCCPAddress();
        tcapMsgs[APP_CCITT]=ituInst;
    }
#endif

   ITS_Application::SetName("TCAP TEST APP"); 

   TCAPDbcServer dbgConsole("TCAP_TEST Debug Console");

   ENGINE_Initialize((argc-ret), &args[ret], NULL, 0);

   ret = ENGINE_Run(argc, args);

   return ret;
}

int parseArguments(int argc, const char** args)
{
   int i = 1;
   int flag = 1;
   int ret = 0;
   itstest::noISD = false;
   

   for(; i < argc && flag; i++)
   {
       if(strcmp(args[i], "opc") == 0)
       {
          itstest::setOPC(atoi(args[++i]));
          printf("OPC = %d (CAP SampleApp)\n", atoi(args[i]));
       }
       else if(strcmp(args[i], "dpc") == 0)
       {
          itstest::setDPC(atoi(args[++i]));
          printf("DPC = %d (In-House MSC Simulator)\n", atoi(args[i]));
       }
       else if(strcmp(args[i], "apc") == 0)
       {
          itstest::setAPC(atoi(args[++i]));
          printf("APC = %d\n", atoi(args[i]));
       }
       else if(strcmp(args[i], "send") == 0)
       {
          itstest::setSender();
       }
       else if(strcmp(args[i], "oe164") == 0)
       {
          itstest::setRouteByGTT();
          itstest::setOE164(strdup(args[++i]));
       }
       else if(strcmp(args[i], "de164") == 0)
       {
          itstest::setDE164(strdup(args[++i]));
       }
       else if(strcmp(args[i], "num") == 0)
       {
          itstest::numThreads = atoi(args[++i]);
       }
       else if(strcmp(args[i], "noISD") == 0)
       {
           // no ISD when UpdateGPRSLocationArg is received
          itstest::noISD = true;
       }
       else if(strcmp(args[i], "-configFile") == 0)
       {
          flag = 0;
       }
       else if(strcmp(args[i], "load") == 0)
       {
          itstest::interactive = ITS_FALSE; 
          itstest::appMode = LOAD_TEST;
       }
       else if(strcmp(args[i], "-rt") == 0)
       {
           numReceiverThreads = atoi(args[++i]);
           if (numReceiverThreads <= 0)
               numReceiverThreads = 1;

           if (numReceiverThreads > 20)
               numReceiverThreads = 20;

           printf("Num Receiver Threads: %d\n", numReceiverThreads);

       }
       else if(strcmp(args[i], "-st") == 0)
       {
           numSenderThreads = atoi(args[++i]);
           if (numSenderThreads <= 0)
               numSenderThreads = 1;

           if (numSenderThreads > 20)
               numSenderThreads = 20;

           printf("Num Sender Threads: %d\n", numSenderThreads);
       }
       else
       {
          Usage(args);
       }
    }
  
    /* from here onwrds engine arguments. */ 
    return i - 2;
}

void Usage(const char** args)
{
    printf("Usage: %s ", args[0]);
    printf("interactive\n");
    printf("Usage: %s ", args[0]);
    printf("opc <value> | ");
    printf("dpc <value> | ");
    printf("apc <value> | ");
    printf(" <send> | ");
    printf("oe164 <value> | ");
    printf("de164 <value>");
    printf("num <value for num threads>");
    printf("\n");
    exit(0);
}

