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
 * LOG: Revision 1.1.4.2.4.3  2014/08/13 12:50:38  jkchaitanya
 * LOG: changes for enhancement bug 4685
 * LOG:
 * LOG: Revision 1.1.4.2.4.2  2014/07/31 12:13:24  jkchaitanya
 * LOG: chanegs for transparent followOn calls in load
 * LOG:
 * LOG: Revision 1.1.4.2.4.1  2014/07/29 06:04:44  jkchaitanya
 * LOG: changes for imsi increment for load
 * LOG:
 * LOG: Revision 1.1.4.2  2013/12/06 09:46:09  jkchaitanya
 * LOG: PerfSim is taken from B-IWF-0100-01 branch
 * LOG:
 * LOG: Revision 1.1.2.1  2013/11/15 11:03:56  jsarvesh
 * LOG: IWF Performance for CAP-Ro
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
#ident "$Id: appMain.cpp,v 1.1.4.2.4.3 2014/08/13 12:50:38 jkchaitanya Exp $"

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

int InteractiveModeMenu();
int  parseArguments(int, const char**);

void Usage(const char**);

ITS_USHORT SelectApplication(ITS_HDR*, ITS_EVENT*);

void printHeader()
{
   printf("   ===================================== \n");      
   printf("   ASP Simulator Program: \n\n");
   printf("   ===================================== \n");      
   printf("   Interactive Mode: \n\n");
   printf("   ===================================== \n");      

}

inline int printMenu()
{
   int q;
   printf("\n	1) Configure The ASP Simulator \n");
   printf("	2) Exit Test \n");
   printf("   ===================================== \n");
   printf("   Enter Selection: ");

   scanf("%d", &q);

   return q;
}

int InteractiveModeMenu()
{
        int choice;
        /* Menu Implemented */
        ITS_BOOLEAN exit = ITS_FALSE;
        printHeader();
  
        while(exit != ITS_TRUE)
        {
           choice = printMenu();

           switch(choice)
           {
            case 1:
  
               int dpc,opc,apc,mode;
               char strng[30];

               printf("\n ASP Simulator Configuration \n");
#if 0
               printf("\n Enter the OPC (Local Point Code): ");
               scanf("%d",&opc);
               itstest::setOPC(opc);
#endif
               printf("Set OPC = %d\n", itstest::opc);

               printf("\n Enter the DPC (Destination Point Code): ");
               scanf("%d",&dpc);
               itstest::setDPC(dpc);

               printf("\n Enter the APC (Adjacent Point Code): ");
               scanf("%d",&apc);
               itstest::setAPC(apc);

               printf("\n Route by GTT [y/n]? {PC/SSN by default}:");
               scanf("%s",strng);

               if(strcmp(strng, "y") == 0)
               {
                  itstest::setRouteByGTT();
                  printf("\n Enter the Origination E164 number: ");
                  scanf("%s",strng);
                  itstest::setOE164(strng);
                  printf("\n Enter the Destination E164 number: ");
                  scanf("%s",strng);
                  itstest::setDE164(strng);
               }

               printf("\n Do you want to run the test app as a sender [y/n]?");
               scanf("%s",strng);
               if(strcmp(strng, "y") == 0)
               {
                   itstest::setSender();
               }

               printf("\n Run the test app as [1 - UnitTester, 2-LoadTester ]?");
               scanf("%d",&mode);
               if ( mode == 1 )
               {
                   itstest::appMode = UNIT_TEST;
               }
               else if (mode == 2)
               {
                   itstest::appMode = LOAD_TEST;
               }
               printf("\n ASP Simulator Configuration Complete \n");
               exit = ITS_TRUE;
               break;

           case 2:
               exit = ITS_TRUE;
               break;

          default:
               printf("\n Incorrect Selection\n");
               printf(" Select Menu 1-2\n\n");

          } /* End Case */
    }

    return choice;
   
}

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
   
   if(argc == 1)
   {
       //Usage(args);
       ret = InteractiveModeMenu();
       if ( ret == 2)
       {
          exit(0);
       }
       else
       {
          return 0;
       }
   }

   for(; i < argc && flag; i++)
   {
       if(strcmp(args[i], "opc") == 0)
       {
          itstest::setOPC(atoi(args[++i]));
          printf("OPC = %d (MAP Tool)\n", atoi(args[i]));
       }
       else if(strcmp(args[i], "dpc") == 0)
       {
          itstest::setDPC(atoi(args[++i]));
          printf("DPC = %d (IWF)\n", atoi(args[i]));
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

