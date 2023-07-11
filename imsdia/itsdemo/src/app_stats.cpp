/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: app_stats.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $
 *
 *  LOG: $Log: app_stats.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.2  2006/11/22 10:46:55  hbhatnagar
 *  LOG: made changes in statistics for CCR and CCA messages
 *  LOG:
 *  LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 *  LOG: Baseline ITS Demo.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.6  2006/07/02 12:14:35  yranade
 *  LOG: Minor Enhancements.
 *  LOG:
 *  LOG: Revision 1.5  2006/07/01 15:33:58  yranade
 *  LOG: Slight changes for tweaking performance.
 *  LOG:
 *  LOG: Revision 1.4  2006/06/07 15:00:20  tpanda
 *  LOG: Code added for load testing
 *  LOG:
 *  LOG: Revision 1.3  2006/05/26 14:10:59  yranade
 *  LOG: Support for CC Compiler.
 *  LOG:
 *  LOG: Revision 1.2  2006/04/25 15:27:36  nvijikumar
 *  LOG: Code Enhancements (Documentation)(yranade,adsouza)
 *  LOG:
 *  LOG: Revision 1.1  2006/04/17 16:06:46  yranade
 *  LOG: Interface to collect statistics.
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: app_stats.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $"

#include <dia_defines.h>
#include <app_stats.h>

using namespace std;

its::ITS_Mutex APPStats::guard(0);
ITS_BOOLEAN APPStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN APPStats::firstTime = ITS_FALSE;
time_t APPStats::startTime;
time_t APPStats::stopTime;
struct timeb APPStats::sendComplete;
struct timeb APPStats::recvComplete;
struct timeb APPStats::starter;
struct timeb APPStats::current;
int APPStats::duration = 10;
int APPStats::burstSize = 0;
int APPStats::slpTime = 1000;

static APPStats *appStats = NULL;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function resets the statistics data.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
APPStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numRARSent               = 0;
    numRARRecv               = 0;
    numRAASent               = 0;
    numRAARecv               = 0;

    numPURSent               = 0;
    numPURRecv               = 0;
    numPUASent               = 0;
    numPUARecv               = 0;

    numSTRSent               = 0;
    numSTRRecv               = 0;
    numSTASent               = 0;
    numSTARecv               = 0;
   
    numCCRSent               = 0;
    numCCRRecv               = 0;
    numCCASent               = 0;
    numCCARecv               = 0;

    numDisconnectIndic       = 0;
    numTimeoutIndic          = 0;
    numAuthLifeTimeoutIndic  = 0;
    numAuthGraceTimeoutIndic = 0;
    numAbortIndic            = 0;
    numCorruptMsgIndic       = 0;
    numUnknownIndic          = 0;

    Unlock();
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: Retrieve the SingleTon statistics object
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
 *      Returns the APPStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
APPStats* 
APPStats::GetAPPStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(APPStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (appStats == NULL)
    {
        appStats = new APPStats;
    }

    /* Release the semaphore
    */
    APPStats::guard.Release();

    return appStats;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: Calculate the total transactions per second.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
APPStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((APPStats::stopTime-APPStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(APPStats::stopTime-APPStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/APPStats::slpTime) * APPStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = APPStats::recvComplete.time - APPStats::sendComplete.time;
         int mt = APPStats::recvComplete.millitm - APPStats::sendComplete.millitm;

         if (st < 0) st = 0;
         if (mt < 0) mt = 0; 
         oss << "Time difference between sending & receiving = " << endl
             <<  st << " Secs " << endl
             <<  mt << " milli-secs " << endl;

         cout << "Time difference between sending & receiving = " << endl
              <<  st << " Secs " << endl
              <<  mt << " milli-secs " << endl;
    }
    else
    {
        cout <<"No of Request != No of Answers" << endl;
    }
}

/*  implementation: public
 *************************************************************************
 *  Purpose: Utility function to update the send statistics, based on the
 *      command code received.
 *      
 *  Input Parameters:
 *      ITS_UINT commandCode: Message Command Code
 *      ITS_BOOLEAN isReq: Whether message is a request or an answer
 *      
 *  Input/Output Parameters:
 *      None.
 *      
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes:
 *      For this particular demo application, since multiple threads
 *      do not operate on the same counters, this function is
 *      Not Thread Safe:
 *      To make it Thread Safe, use it with Lock()/Unlock()
 *
 *  See Also:
 *
 *************************************************************************/
void
APPStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case 258:  /*ReAuth */
            numRARSent++;
            break;
        case 275:  /* STR */
            numSTRSent++;
            break;
        case 307:  /*ProfileUpdateReq */
            numPURSent++;
            break;
        case 272:  /*CreditControlReq */
            numCCRSent++;
            break;
        default:
            break;
        }
        numRqMsgsSent++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case 258:  /*ReAuth */
            numRAASent++;
            break;
        case 275:  /* STA */
            numSTASent++;
            break;
        case 307:  /*ProfileUpdateReq */
            numPUASent++;
            break;
        case 272:  /*CreditControl */
            numCCASent++;
            break;
        default:
            break;
        }
        numRaMsgsSent++;
    }
 
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function updates the indications received
 *      from the diameter stack.
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
 *      None
 *
 *  Notes:
 *      Not Thread Safe: To make it so, use it with Lock()/Unlock()
 *  See Also:
 ****************************************************************************/
void
APPStats::UpdateRecvIndications(ITS_UINT indic)
{
    switch (indic)
    {
    case DISCONECT_IND_FROM_STACK:
        numDisconnectIndic++;
        break;
    case TIME_OUT_IND_FROM_STACK:
        numTimeoutIndic++;
        break;
    case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
        numAuthLifeTimeoutIndic++;
        break;
    case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
        numAuthGraceTimeoutIndic++;
        break;
    case ABORT_IND_FROM_STACK:
        numAbortIndic++;
        break;
    case CORRUPTED_MSG_IND_FROM_STACK:
        numCorruptMsgIndic++;
        break;
    default:
        numUnknownIndic++;
        break;
    }
}
/*  implementation: public
 ****************************************************************************
 *  Purpose: Utility function to update the receive statistics, based on the
 *      command code received.
 *
 *  Input Parameters:
 *      ITS_UINT commandCode: Message Command Code
 *      ITS_BOOLEAN isReq: Whether message is a request or an answer
 *  
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes: 
 *      For this particular demo application, since multiple threads
 *      do not operate on the same counters, this function is
 *      Not Thread Safe:
 *      To make it Thread Safe, use it with Lock()/Unlock()
 *      
 *  See Also:
 *      
 ****************************************************************************/
void
APPStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    time_t tx;
    struct tm tbuf, *temp;
    char buff[80];

    /* If message request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case 258:  /*ReAuth */
            numRARRecv++;
            break;
        case 275:  /* STR */
            numSTRRecv++;
            break;
        case 307:  /*ProfileUpdateReq */
            numPURRecv++;
            break;
        case 272:  /*CreditControlReq */
            numCCRRecv++;
            break;
        default:
            break;
        }
        numRqMsgsRecv++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case 258:  /*ReAuth */
            numRAARecv++;
            break;
        case 275:  /* STA */
            numSTARecv++;
            break;
        case 307:  /*ProfileUpdateReq */
            numPUARecv++;
            break;
        case 272:  /*CreditControlAns */
            numCCARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&APPStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!APPStats::sendTraffic && 
            (APPStats::numRqMsgsSent == APPStats::numRaMsgsRecv))
        {
            time(&APPStats::stopTime);
            ftime(&APPStats::recvComplete);
            time(&tx);
            temp =  localtime_r(&tx, &tbuf);
            strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
            cout <<"Test Finished Receiving at ----->" << buff << endl;
        }
    }
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function prints the indications from the base diameter
 *      stack to the output stream.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
APPStats::PrintIndications(std::ostream& os) const
{
    os << "Num of Disconnect Indications       "
       << numDisconnectIndic << endl;

    os << "Num of Timeout Indications          "
       << numTimeoutIndic << endl;

    os << "Num of AuthLifeTimeout Indications  "
       << numAuthLifeTimeoutIndic << endl;

    os << "Num of AuthGraceTimeout Indications "
       << numAuthGraceTimeoutIndic << endl;

    os << "Num of Abort Indications            "
       << numAbortIndic << endl;

    os << "Num of Corrupt Indications          "
       << numCorruptMsgIndic << endl;

    os << "Num of Unknown Indications          "
       << numUnknownIndic << endl;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function prints the statistical data to the
 *      output stream.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
APPStats::Print(std::ostream& os) const
{
    char tbuf[ITS_PATH_MAX];
    time_t local;

    time(&local);
#if defined (__SUNPRO_CC)
    ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
    ctime_r(&local, tbuf);
#endif

    Lock();

    os << "-----------------------------------------------------------" << endl;
    os << "-- APP Stats -- at " << tbuf;
    os << "-----------------------------------------------------------" << endl;
    os << endl;

    os << "Total Num of Request Msgs Sent      "
       <<  numRqMsgsSent << endl;

    os << "Total Num of Answer Msgs Sent       "
       <<  numRaMsgsSent << endl;

    os << "Total Num of Request Msgs Received  "
       <<  numRqMsgsRecv << endl;

    os << "Total Num of Answer Msgs Received   "
       <<  numRaMsgsRecv << endl;
    os << endl;

    os << "Num of RAR Sent                     "
       << numRARSent << endl;

    os << "Num of RAA Sent                     "
       << numRAASent << endl;

    os << "Num of RAR Received                 "
       << numRARRecv << endl;

    os << "Num of RAA Received                 "
       << numRAARecv << endl;
    os << endl;

    os << "Num of PUR Sent                     "
       << numPURSent << endl;

    os << "Num of PUA Sent                     "
       << numPUASent << endl;

    os << "Num of PUR Received                 "
       << numPURRecv << endl;

    os << "Num of PUA Received                 "
       << numPUARecv << endl;
    os << endl;

    os << "Num of CCR Sent                     "
       << numCCRSent << endl;

    os << "Num of CCA Sent                     "
       << numCCASent << endl;

    os << "Num of CCR Received                 "
       << numCCRRecv << endl;

    os << "Num of CCA Received                 "
       << numCCARecv << endl;
    os << endl;

    os << "Num of STR Sent                     "
       << numSTRSent << endl;

    os << "Num of STA Sent                     "
       << numSTASent << endl;

    os << "Num of STR Received                 "
       << numSTRRecv << endl;

    os << "Num of STA Received                 "
       << numSTARecv << endl;

    PrintIndications(os);

    Unlock();
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: Overloading of the << operator.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ostream&
operator<<(ostream& os, const APPStats& appStats)
{
    appStats.Print(os);
    return os;
}


