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
 * LOG: $Log: e4_stats.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/04 16:05:47  hbhatnagar
 * LOG: Baseline demo application for e4 interface for static and distributed.
 * LOG:
 * LOG:
 * ID: $Id: e4_stats.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: e4_stats.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <dia_defines.h>
#include <app.h>

#include <e4_stats.h>
#include <e4_defines.h>

using namespace std;

its::ITS_Mutex E4Stats::guard(0);
ITS_BOOLEAN E4Stats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN E4Stats::firstTime = ITS_FALSE;
time_t E4Stats::startTime;
time_t E4Stats::stopTime;
struct timeb E4Stats::sendComplete;
struct timeb E4Stats::recvComplete;
struct timeb E4Stats::starter;
struct timeb E4Stats::current;
int E4Stats::duration = 10;
int E4Stats::burstSize = 0;
int E4Stats::slpTime = 1000;

static E4Stats *e4Stats = NULL;

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
E4Stats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numUDRSent               = 0;
    numUDRRecv               = 0;
    numUDASent               = 0;
    numUDARecv               = 0;

    numPNRSent               = 0;
    numPNRRecv               = 0;
    numPNASent               = 0;
    numPNARecv               = 0;

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
 *      Returns the E4Stats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
E4Stats*
E4Stats::GetE4Stats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(E4Stats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (e4Stats == NULL)
    {
        e4Stats = new E4Stats;
    }

    /* Release the semaphore
    */
    E4Stats::guard.Release();

    return e4Stats;
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
E4Stats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((E4Stats::stopTime-E4Stats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(E4Stats::stopTime-E4Stats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/E4Stats::slpTime) * E4Stats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = E4Stats::recvComplete.time - E4Stats::sendComplete.time;
         int mt = E4Stats::recvComplete.millitm - E4Stats::sendComplete.millitm;

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
E4Stats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case E4_UD_MSG_CMD_CODE:  /* UDR */
            numUDRSent++;
            break;
        case E4_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRSent++;
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
        case E4_UD_MSG_CMD_CODE:  /* UDA */
            numUDASent++;
            break;
        case E4_PN_MSG_CMD_CODE:  /*PNAns */
            numPNASent++;
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
E4Stats::UpdateRecvIndications(ITS_UINT indic)
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
E4Stats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case E4_UD_MSG_CMD_CODE:  /* UDR */
            numUDRRecv++;
            break;
        case E4_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRRecv++;
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
        case E4_UD_MSG_CMD_CODE:  /* UDA */
            numUDARecv++;
            break;
        case E4_PN_MSG_CMD_CODE:  /* PNA */
            numPNARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&E4Stats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!E4Stats::sendTraffic &&
            (E4Stats::numRqMsgsSent == E4Stats::numRaMsgsRecv))
        {
            time(&E4Stats::stopTime);
            ftime(&E4Stats::recvComplete);
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
E4Stats::PrintIndications(std::ostream& os) const
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
E4Stats::Print(std::ostream& os) const
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

    os << "Num of UDR Sent                     "
       << numUDRSent << endl;

    os << "Num of UDA Sent                     "
       << numUDASent << endl;

    os << "Num of UDR Received                 "
       << numUDRRecv << endl;

    os << "Num of UDA Received                 "
       << numUDARecv << endl;
    os << endl;

    os << "Num of PNR Sent                     "
       << numPNRSent << endl;

    os << "Num of PNA Sent                     "
       << numPNASent << endl;

    os << "Num of PNR Received                 "
       << numPNRRecv << endl;

    os << "Num of PNA Received                 "
       << numPNARecv << endl;

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
operator<<(ostream& os, const E4Stats& e4Stats)
{
    e4Stats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    E4Stats::GetE4Stats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    E4Stats::duration = duration;
    E4Stats::burstSize = burstSize;
    E4Stats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&E4Stats::starter);
    time(&E4Stats::startTime);

    E4Stats::sendTraffic = ITS_TRUE;
    E4Stats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendE4PushNotificationRequest;

}

void StopTraffic()
{
    E4Stats::sendTraffic = ITS_FALSE;
    ftime(&E4Stats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    E4Stats::GetE4Stats()->Print(oss);
}

void ResetStats()
{
    E4Stats::GetE4Stats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    E4Stats::GetE4Stats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    E4Stats::GetE4Stats()->CalcTPS(oss);
}

