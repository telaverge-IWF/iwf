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
 * LOG: Revision 1.1.2.1  2013/03/04 04:44:05  pramana
 * LOG: Adding simulators for demos
 * LOG:
 * LOG: Revision 1.1.2.1  2013/01/28 15:54:23  pramana
 * LOG: Committing the simulator code
 * LOG:
 * LOG: Revision 3.1.42.1  2012/09/28 08:01:15  pramana
 * LOG: Checkins for the changes done for GenBand demo
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
 * ID: $Id: sample_sender.cpp,v 1.1.2.1 2013/03/04 04:44:05 pramana Exp $
 ****************************************************************************/
#ident "$Id: sample_sender.cpp,v 1.1.2.1 2013/03/04 04:44:05 pramana Exp $"

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>
#include <app.h>

using namespace std;
using namespace its;
using namespace engine;

/* These functions need to be Definied in the specific Interfaces */
extern int DisplayAppMenu();
extern int DisplayMainWindow();
extern int DisplayCursesWindow();
extern int HandleDiaAppMsg(const diameter::CommandImpl *impl, 
                                          unsigned int &sIdx);
extern int HandleDiaAppMsg(const DIA_BASE_CMD *bcmd,
        const diameter::CommandImpl *impl,unsigned int &sIdx);
extern void UpdateIndications(ITS_UINT indType);
extern RunMode GetMode();

extern char banner[256];
extern char* sim;
ApplicationStats appStats;

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

    //runMode = GetMode();

    if (appMode == LOAD_TEST)
    {
        GenerateLoad();
        return;
    }
    
    while (1)
    {
#if 0
        cout << endl << "Enter your choice"
            << endl << "1: Send "
            << endl << "9: Return to main menu"
            << endl;
#endif
        //cin >>inStr;
        inStr = "1";
        choice = atoi(inStr.c_str());
        sleep(5);
        // Display Based on the Choice made in the Menu

        switch (choice)
        {
        case 1:
            DisplayAppMenu();
            break;

        case 9:
            runMode = GetMode();
            break;

        default:
            cout << "Invalid Choice " << endl;
            break;
        }
    }

}

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

void ReceiverThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret;
    int choice;
    string inStr;

    displayMode = 100;
    return;

    //runMode = GetMode();

    while (1)
    {
        cin >>inStr;
        choice = atoi(inStr.c_str());
        // Display Based on the Choice made in the Menu

        switch (choice)
        {
            case 1:
                {
                    int k=1;
                    int ret;
                    std::string input;
                    while(k)
                    {
                        do
                        {
                            cin >> input;

                            ret=atoi(input.c_str());

                            if (*input.c_str() == 'q')
                            {
                                displayMode = 10;
                                break;
                            }
                            else
                            {
                                displayMode = 100;
                            }

                        } while ((ret < 1 || ret > 7) && ret!=99);
                        switch(ret)
                        {
                            case 'q':
                                k = 0;
                                break;
                        }
                    }

                }
                break;

            case 9:
                runMode = GetMode();
                break;

            default:
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
            {
                const DIA_BASE_CMD* cmd = dMsg->GetMsgFlow();
                //cout << "Received a message with command code of : " << (diameter::Command*)((const_cast<diameter::DiaMsgFlow*>(cmd))->GetBaseGenCommand())->getHeader().code << endl << endl << endl;
                if (cmd->getCommandCode() == 272 || //S9_CC_MSG_CMD_CODE ||
                                    cmd->getCommandCode() == 258 || //S9_RA_MSG_CMD_CODE ||
                                    cmd->getCommandCode() == 316 || //S6A_AI_MSG_CMD_CODE ||
                                    cmd->getCommandCode() == 318)   //S6A_UL_MSG_CMD_CODE)
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
                        if (dMsg)
                        delete dMsg;
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

#if 0
#ifdef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
        printf("|------------------------+---------------------------+-------------------------|\r\n")

#define DISPLAY_HEADER()\
   printf("|    Counter Name        |      Periodic value       |     Cumulative value    |\r\n")
#define DISPLAY_TXT_COL(T1, V1, V2)\
    printf("| %-22.22s | %-25.25s |", T1, V1); printf(" %-24.24s|\r\n", V2)
#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-22.22s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-22.22s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-22.22s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-22.22s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-22.22s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-22.22s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-22.22s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-22.22s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-22.22s | %-52.52s|\r\n", T1, V1)
#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-22s | %25s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//  printf("| %-22.22s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
   printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
   printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
   printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
   printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
   printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-22.22s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
    memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
    {\
       int i;\
           for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
                i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
            PT[i] = (unsigned long) 0;\
    }

#define RESET_PL_COUNTERS(PT)\
    {\
       int i;\
       for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
                i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
            PT[i] = (unsigned long) 0;\
    }
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
  struct tm *L_currentDate;

  // Get the current date and time
  L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

  // Format the time
  if (L_currentDate == NULL)
    {
      memset (P_time, 0, TIME_LENGTH);
    }
  else
    {
      sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
           L_currentDate->tm_year + 1900,
           L_currentDate->tm_mon + 1,
           L_currentDate->tm_mday,
           L_currentDate->tm_hour,
           L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

  static char L_time [TIME_LENGTH];
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (L_time, 0, TIME_LENGTH);
  } else {
    sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec);
  }
  return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;
    
    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;
    
    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
        mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
  long L_val_sec, L_val_usec;

  L_val_sec = P_final->tv_sec - P_init->tv_sec;
  L_val_usec = P_final->tv_usec - P_init->tv_usec;
  if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
  return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (P_time, 0, TIME_STRING_LENGTH);
  } else {
    sprintf(P_time, 
        "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec,
        (int)((P_tv->tv_usec)/1000));
  }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (P_time, 0, TIME_STRING_LENGTH);
  } else {
    sprintf(P_time, 
        "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec,
        (int)((P_tv->tv_usec)/1000));
  }
} 

#endif // _STAT_MACROS_H
#endif // SEAGUL_STYLE_OUTPUT

#ifndef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_EMPTY_LINE()\
    printf("|                                                                              |\r\n")
#define DISPLAY_OPEN_TEXT(T1)\
    printf("| %s", T1);fflush(stdout)

#define DISPLAY_EMPTY_TEXT(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
        printf("|-----------------------------+----------------------+-------------------------|\r\n")

#define DISPLAY_BANNER()\
        printf("|                            Diametriq %4s Simulator                          |\r\n", sim)

#define DISPLAY_HEADER()\
        printf("|        Main Menu            |                     Statistics                 |\r\n")

#define DISPLAY_CROSS_LINE2()\
        printf("|-----------------------------|------------------------------------------------|\r\n")

#define DISPLAY_TXT_COL(T1, T2, V1)\
    printf("| %-27.27s | %-35.35s :", T1, T2); printf(" %-9d|\r\n", V1)

#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-27.27s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-27.27s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-27.27s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-27.27s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-27.27s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-27.27s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-27.27s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-27.27s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-27.27s | %-52.52s|\r\n", T1, V1)

#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-27s | %20s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//  printf("| %-27.27s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
   printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
   printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
   printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
   printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
   printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-27.27s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
    memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
    {\
       int i;\
           for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
                i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
            PT[i] = (unsigned long) 0;\
    }

#define RESET_PL_COUNTERS(PT)\
    {\
       int i;\
       for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
                i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
            PT[i] = (unsigned long) 0;\
    }
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
  struct tm *L_currentDate;

  // Get the current date and time
  L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

  // Format the time
  if (L_currentDate == NULL)
    {
      memset (P_time, 0, TIME_LENGTH);
    }
  else
    {
      sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
           L_currentDate->tm_year + 1900,
           L_currentDate->tm_mon + 1,
           L_currentDate->tm_mday,
           L_currentDate->tm_hour,
           L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

  static char L_time [TIME_LENGTH];
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (L_time, 0, TIME_LENGTH);
  } else {
    sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec);
  }
  return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;
    
    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;
    
    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
        mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
  long L_val_sec, L_val_usec;

  L_val_sec = P_final->tv_sec - P_init->tv_sec;
  L_val_usec = P_final->tv_usec - P_init->tv_usec;
  if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
  return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (P_time, 0, TIME_STRING_LENGTH);
  } else {
    sprintf(P_time, 
        "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec,
        (int)((P_tv->tv_usec)/1000));
  }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
  struct tm * L_currentDate;
  
  // Get the current date and time
  L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);
  
  // Format the time
  if (L_currentDate == NULL) {
    memset (P_time, 0, TIME_STRING_LENGTH);
  } else {
    sprintf(P_time, 
        "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
        L_currentDate->tm_year + 1900,
        L_currentDate->tm_mon + 1,
        L_currentDate->tm_mday,
        L_currentDate->tm_hour,
        L_currentDate->tm_min,
        L_currentDate->tm_sec,
        (int)((P_tv->tv_usec)/1000));
  }
} 

#endif // _STAT_MACROS_H
#endif // not SEAGUL_STYLE_OUTPUT
#endif

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

void DisplayThreadFunc2(its::ThreadPoolThread* thr, void* arg)
{
    int ret;
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);
    struct timeval currentTime;
    long globalElapsedTime;
    long localElapsedTime;

    while (1)
    {
        // Display the data
        DisplayMainWindow();
        sleep(1);
    }
}

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

void DisplayThreadFunc(its::ThreadPoolThread* thr, void* arg)
{
    int ret;
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);
    struct timeval currentTime;
    long globalElapsedTime;
    long localElapsedTime;

    while (1)
    {
        // Display the data
        DisplayMainWindow();
        sleep(2);
    }
}

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

void DisplayCursesThreadFunc(its::ThreadPoolThread* thr, void* arg)
{

    while (1)
    {
        // Display the data
        //DisplayCursesWindow();
        sleep(2);
    }
}
