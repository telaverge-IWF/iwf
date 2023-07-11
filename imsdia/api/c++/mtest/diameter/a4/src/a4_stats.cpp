/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
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
 * LOG: $Log: a4_stats.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:39:46  vkumara
 * LOG: Baseline for a4 interface.
 * LOG:
 * LOG:
 * ID: $Id: a4_stats.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $
 ****************************************************************************/
#ident "$Id: a4_stats.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <a4_stats.h>
#include <a4_defines.h>

using namespace std;

its::ITS_Mutex A4Stats::guard(0);
ITS_BOOLEAN A4Stats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN A4Stats::firstTime = ITS_FALSE;
time_t A4Stats::startTime;
time_t A4Stats::stopTime;
struct timeb A4Stats::sendComplete;
struct timeb A4Stats::recvComplete;
struct timeb A4Stats::starter;
struct timeb A4Stats::current;
int A4Stats::duration = 10;
int A4Stats::burstSize = 0;
int A4Stats::slpTime = 1000;

static A4Stats *a4Stats = NULL;

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
A4Stats::ResetAll()
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
 *      Returns the A4Stats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
A4Stats*
A4Stats::GetA4Stats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(A4Stats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (a4Stats == NULL)
    {
        a4Stats = new A4Stats;
    }

    /* Release the semaphore
    */
    A4Stats::guard.Release();

    return a4Stats;
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
A4Stats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((A4Stats::stopTime-A4Stats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(A4Stats::stopTime-A4Stats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/A4Stats::slpTime) * A4Stats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = A4Stats::recvComplete.time - A4Stats::sendComplete.time;
         int mt = A4Stats::recvComplete.millitm - A4Stats::sendComplete.millitm;

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
A4Stats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case A4_UD_MSG_CMD_CODE:  /* UDR */
            numUDRSent++;
            break;
        case A4_PN_MSG_CMD_CODE:  /*PNReq */
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
        case A4_UD_MSG_CMD_CODE:  /* UDA */
            numUDASent++;
            break;
        case A4_PN_MSG_CMD_CODE:  /*PNAns */
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
A4Stats::UpdateRecvIndications(ITS_UINT indic)
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
A4Stats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case A4_UD_MSG_CMD_CODE:  /* UDR */
            numUDRRecv++;
            break;
        case A4_PN_MSG_CMD_CODE:  /*PNReq */
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
        case A4_UD_MSG_CMD_CODE:  /* UDA */
            numUDARecv++;
            break;
        case A4_PN_MSG_CMD_CODE:  /* PNA */
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
            time(&A4Stats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!A4Stats::sendTraffic &&
            (A4Stats::numRqMsgsSent == A4Stats::numRaMsgsRecv))
        {
            time(&A4Stats::stopTime);
            ftime(&A4Stats::recvComplete);
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
A4Stats::PrintIndications(std::ostream& os) const
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
A4Stats::Print(std::ostream& os) const
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
operator<<(ostream& os, const A4Stats& a4Stats)
{
    a4Stats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    A4Stats::GetA4Stats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    A4Stats::duration = duration;
    A4Stats::burstSize = burstSize;
    A4Stats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&A4Stats::starter);
    time(&A4Stats::startTime);

    A4Stats::sendTraffic = ITS_TRUE;
    A4Stats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendA4PushNotificationRequest;

}

void StopTraffic()
{
    A4Stats::sendTraffic = ITS_FALSE;
    ftime(&A4Stats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    A4Stats::GetA4Stats()->Print(oss);
}

void ResetStats()
{
    A4Stats::GetA4Stats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    A4Stats::GetA4Stats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    A4Stats::GetA4Stats()->CalcTPS(oss);
}

