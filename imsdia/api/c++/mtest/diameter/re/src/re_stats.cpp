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
 *  ID: $Id: re_stats.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $
 *  LOG:
 *
 * ID: $Id: re_stats.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $
 ****************************************************************************/
#ident "$Id: re_stats.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <re_stats.h>
#include <re_defines.h>

using namespace std;

its::ITS_Mutex ReStats::guard(0);
ITS_BOOLEAN ReStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN ReStats::firstTime = ITS_FALSE;
time_t ReStats::startTime;
time_t ReStats::stopTime;
struct timeb ReStats::sendComplete;
struct timeb ReStats::recvComplete;
struct timeb ReStats::starter;
struct timeb ReStats::current;
int ReStats::duration = 10;
int ReStats::burstSize = 0;
int ReStats::slpTime = 1000;

static ReStats *reStats = NULL;

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
ReStats::ResetAll()
{
    Lock();

    numReMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numReMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numPRQSent               = 0;
    numPRQRecv               = 0;
    numPRSSent               = 0;
    numPRSRecv               = 0;

    numTRQSent               = 0;
    numTRQRecv               = 0;
    numTRSSent               = 0;
    numTRSRecv               = 0;

    numSUQSent               = 0;
    numSUQRecv               = 0;
    numSUSSent               = 0;
    numSUSRecv               = 0;

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
 *      Returns the ReStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ReStats* 
ReStats::GetReStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(ReStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (reStats == NULL)
    {
        reStats = new ReStats;
    }

    /* Release the semaphore
    */
    ReStats::guard.Release();

    return reStats;
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
ReStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numReMsgsSent)
    {
         /* Calculate tps
         */
         if ((ReStats::stopTime-ReStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(ReStats::stopTime-ReStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/ReStats::slpTime) * ReStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = ReStats::recvComplete.time - ReStats::sendComplete.time;
         int mt = ReStats::recvComplete.millitm - ReStats::sendComplete.millitm;

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
ReStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case RE_PRICE_MSG_CMD_CODE:  /*PriceRequest */
            numPRQSent++;
            break;
        case RE_TARIFF_MSG_CMD_CODE :  /* TariffRequest */
            numTRQSent++;
            break;
        case RE_SERVICEUSAGE_MSG_CMD_CODE:  /*ServiceUsage Request */
            numSUQSent++;
            break;
        default:
            break;
        }
        numReMsgsSent++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case RE_PRICE_MSG_CMD_CODE:  /*PriceResponse */
            numPRSSent++;
            break;
        case RE_TARIFF_MSG_CMD_CODE :  /* TariffResponse */
            numTRSSent++;
            break;
        case RE_SERVICEUSAGE_MSG_CMD_CODE:  /*ServiceUsage Response */
            numSUSSent++;
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
ReStats::UpdateRecvIndications(ITS_UINT indic)
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
ReStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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

        case RE_PRICE_MSG_CMD_CODE:  /*PriceRequest */
            numPRQRecv++;
            break;
        case  RE_TARIFF_MSG_CMD_CODE :  /* TariffRequest */
            numTRQRecv++;
            break;
        case RE_SERVICEUSAGE_MSG_CMD_CODE:  /*ServiceUsage Request */
            numSUQRecv++;
            break;
        default:
            break;
        }
        numReMsgsRecv++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case RE_PRICE_MSG_CMD_CODE:  /*PriceResponse */ 
            numPRSRecv++;
            break;
        case RE_TARIFF_MSG_CMD_CODE :  /* TariffResponse */
            numTRSRecv++;
            break;
        case RE_SERVICEUSAGE_MSG_CMD_CODE:  /*ServiceUsage Response */
            numSUSRecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&ReStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!ReStats::sendTraffic && 
            (ReStats::numReMsgsSent == ReStats::numRaMsgsRecv))
        {
            time(&ReStats::stopTime);
            ftime(&ReStats::recvComplete);
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
ReStats::PrintIndications(std::ostream& os) const
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
ReStats::Print(std::ostream& os) const
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
       <<  numReMsgsSent << endl;

    os << "Total Num of Answer Msgs Sent       "
       <<  numRaMsgsSent << endl;

    os << "Total Num of Request Msgs Received  "
       <<  numReMsgsRecv << endl;

    os << "Total Num of Answer Msgs Received   "
       <<  numRaMsgsRecv << endl;
    os << endl;

    os << "Num of PriceRequest  Sent          "
       << numPRQSent << endl;

    os << "Num of PRiceResponse  Sent                     "
       << numPRSSent << endl;

    os << "Num of PriceRequest Received                 "
       << numPRQRecv << endl;

    os << "Num of PriceResponse Received                 "
       << numPRSRecv << endl;
    os << endl;

    os << "Num of TariffRequest Sent                     "
       << numTRQSent << endl;

    os << "Num of TariffResponse Sent                     "
       << numTRSSent << endl;

    os << "Num of TariffRequest Received                 "
       << numTRQRecv << endl;

    os << "Num of TariffResponse Received                 "
       << numTRSRecv << endl;
    os << endl;

    os << "Num of ServiceUsage Request Sent                     "
       << numSUQSent << endl;

    os << "Num of ServiceUsage Response Sent                     "
       << numSUSSent << endl;

    os << "Num of ServiceUsage Request Received                 "
       << numSUQRecv << endl;

    os << "Num of ServiceUsage Response Received                 "
       << numSUSRecv << endl;
    os << endl;

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
operator<<(ostream& os, const ReStats& reStats)
{
    reStats.Print(os);
    return os;
}


void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    ReStats::GetReStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    ReStats::duration = duration;
    ReStats::burstSize = burstSize;
    ReStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&ReStats::starter);
    time(&ReStats::startTime);

    ReStats::sendTraffic = ITS_TRUE;
    ReStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendRePriceRequest;

}

void StopTraffic()
{
    ReStats::sendTraffic = ITS_FALSE;
    ftime(&ReStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    ReStats::GetReStats()->Print(oss);
}

void ResetStats()
{
    ReStats::GetReStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    ReStats::GetReStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    ReStats::GetReStats()->CalcTPS(oss);
}

