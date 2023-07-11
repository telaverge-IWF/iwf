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
 *  ID: $Id: tx_stats.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 *
 *  LOG: $Log: tx_stats.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.2  2006/12/19 08:54:50  kamakshilk
 *  LOG: New architecture to work with static and distributed.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/08/04 17:52:51  nvijikumar
 *  LOG: 1. Changes to update the stats for all messgaes.
 *  LOG: 2. Fix for solaris compilation issue.
 *  LOG:
 *  LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 *  LOG: Baseline demo application for Tx Interface.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: tx_stats.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $"

#include <dia_defines.h>
#include <app.h>

#include <tx_stats.h>
#include <tx_defines.h>

using namespace std;

its::ITS_Mutex TxStats::guard(0);
ITS_BOOLEAN TxStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN TxStats::firstTime = ITS_FALSE;
time_t TxStats::startTime;
time_t TxStats::stopTime;
struct timeb TxStats::sendComplete;
struct timeb TxStats::recvComplete;
struct timeb TxStats::starter;
struct timeb TxStats::current;
int TxStats::duration = 10;
int TxStats::burstSize = 0;
int TxStats::slpTime = 1000;

static TxStats *txStats = NULL;

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
TxStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numAARSent               = 0;
    numAARRecv               = 0;
    numAAASent               = 0;
    numAAARecv               = 0;

    numRARSent               = 0;
    numRARRecv               = 0;
    numRAASent               = 0;
    numRAARecv               = 0;

    numASRSent               = 0;
    numASRRecv               = 0;
    numASASent               = 0;
    numASARecv               = 0;

    numSTRSent               = 0;
    numSTRRecv               = 0;
    numSTASent               = 0;
    numSTARecv               = 0;

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
 *      Returns the TxStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
TxStats* 
TxStats::GetTxStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(TxStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (txStats == NULL)
    {
        txStats = new TxStats;
    }

    /* Release the semaphore
    */
    TxStats::guard.Release();

    return txStats;
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
TxStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((TxStats::stopTime-TxStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(TxStats::stopTime-TxStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/TxStats::slpTime) * TxStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = TxStats::recvComplete.time - TxStats::sendComplete.time;
         int mt = TxStats::recvComplete.millitm - TxStats::sendComplete.millitm;

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
TxStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case 265:  /*AAR */
            numAARSent++;
            break;
        case 258:  /*ReAuth */
            numRARSent++;
            break;
        case 275:  /* STR */
            numSTRSent++;
            break;
        case 274:  /*ASR */
            numASRSent++;
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
        case 265:  /*AAA */
            numAAASent++;
            break;
        case 258:  /*ReAuth */
            numRAASent++;
            break;
        case 275:  /* STA */
            numSTASent++;
            break;
        case 274:  /* ASA */
            numASASent++;
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
TxStats::UpdateRecvIndications(ITS_UINT indic)
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
TxStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case 265:  /* AAR */
            numAARRecv++;
            break;
        case 258:  /*ReAuth */
            numRARRecv++;
            break;
        case 275:  /* STR */
            numSTRRecv++;
            break;
        case 274:  /* ASR */
            numASRRecv++;
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
        case 265:  /* AAA */
            numAAARecv++;
            break;
        case 258:  /*ReAuth */
            numRAARecv++;
            break;
        case 275:  /* STA */
            numSTARecv++;
            break;
        case 274:  /* ASA */
            numASARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&TxStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!TxStats::sendTraffic && 
            (TxStats::numRqMsgsSent == TxStats::numRaMsgsRecv))
        {
            time(&TxStats::stopTime);
            ftime(&TxStats::recvComplete);
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
TxStats::PrintIndications(std::ostream& os) const
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
TxStats::Print(std::ostream& os) const
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

    os << "Num of AAR Sent                     "
       << numAARSent << endl;

    os << "Num of AAA Sent                     "
       << numAAASent << endl;

    os << "Num of AAR Received                 "
       << numAARRecv << endl;

    os << "Num of AAA Received                 "
       << numAAARecv << endl;
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

    os << "Num of ASR Sent                     "
       << numASRSent << endl;

    os << "Num of ASA Sent                     "
       << numASASent << endl;

    os << "Num of ASR Received                 "
       << numASRRecv << endl;

    os << "Num of ASA Received                 "
       << numASARecv << endl;
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
operator<<(ostream& os, const TxStats& txStats)
{
    txStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    TxStats::GetTxStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    TxStats::duration = duration;
    TxStats::burstSize = burstSize;
    TxStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&TxStats::starter);
    time(&TxStats::startTime);

    TxStats::sendTraffic = ITS_TRUE;
    TxStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendTxAARequest;

}

void StopTraffic()
{
    TxStats::sendTraffic = ITS_FALSE;
    ftime(&TxStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    TxStats::GetTxStats()->Print(oss);
}

void ResetStats()
{
    TxStats::GetTxStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    TxStats::GetTxStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    TxStats::GetTxStats()->CalcTPS(oss);
}

