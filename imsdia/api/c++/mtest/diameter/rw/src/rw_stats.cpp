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
 *  ID: $Id: rw_stats.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 *  LOG:
 *
 * ID: $Id: rw_stats.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 ****************************************************************************/
#ident "$Id: rw_stats.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <rw_stats.h>
#include <rw_defines.h>

#include <diameter/Command.h>
using namespace std;

its::ITS_Mutex RwStats::guard(0);
ITS_BOOLEAN RwStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN RwStats::firstTime = ITS_FALSE;
time_t RwStats::startTime;
time_t RwStats::stopTime;
struct timeb RwStats::sendComplete;
struct timeb RwStats::recvComplete;
struct timeb RwStats::starter;
struct timeb RwStats::current;
int RwStats::duration = 10;
int RwStats::burstSize = 0;
int RwStats::slpTime = 1000;

static RwStats *rwStats = NULL;

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
RwStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;


    numPIRSent               = 0;
    numPIRRecv               = 0;
    numPIASent               = 0;
    numPIARecv               = 0;

    numASRSent               = 0;
    numASRRecv               = 0;
    numASASent               = 0;
    numASARecv               = 0;

    numRARSent               = 0;
    numRARRecv               = 0;
    numRAASent               = 0;
    numRAARecv               = 0;

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
 *      Returns the RfRoStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
RwStats* 
RwStats::GetRwStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(RwStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (rwStats == NULL)
    {
        rwStats = new RwStats;
    }

    /* Release the semaphore
    */
    RwStats::guard.Release();

    return rwStats;
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
RwStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRqMsgsRecv == numRaMsgsSent)
    {
         /* Calculate tps
         */
         if ((RwStats::stopTime-RwStats::startTime) > 0 )
         {
             tps = (numRqMsgsRecv)/(RwStats::stopTime-RwStats::startTime);
         }
         else
         {
             //tps = (numRqMsgsRecv);
             tps = (1000/RwStats::slpTime) * RwStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = RwStats::recvComplete.time - RwStats::sendComplete.time;
         int mt = RwStats::recvComplete.millitm - RwStats::sendComplete.millitm;

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
RwStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case RW_PI_MSG_CMD_CODE:  /*PIR */
            numPIRSent++;
            break;
        case RW_RA_MSG_CMD_CODE:  /*RAR */
            numRARSent++;
            break;
        case RW_AS_MSG_CMD_CODE:  /*ACR */
            numASRSent++;
            break;
        case RW_CC_MSG_CMD_CODE:  /*CCR */
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
       case RW_PI_MSG_CMD_CODE:  /* PIA */
            numPIASent++;
            break;
       case RW_RA_MSG_CMD_CODE:  /* RAA */
            numRAASent++;
            break;
        case RW_AS_MSG_CMD_CODE:  /* ASA */
            numASASent++;
            break;
        case RW_CC_MSG_CMD_CODE:  /* CCA */
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
RwStats::UpdateRecvIndications(ITS_UINT indic)
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
RwStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case RW_AS_MSG_CMD_CODE:  /* ASR */
            numASRRecv++;
            break;
        case RW_PI_MSG_CMD_CODE:  /* PIR */
            numPIRRecv++;
            break;
        case RW_RA_MSG_CMD_CODE:  /* RAR */
            numRARRecv++;
            break;
        case RW_CC_MSG_CMD_CODE:  /* CCR */
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
        case RW_AS_MSG_CMD_CODE:  /* ASA */
            numASARecv++;
            break;
        case RW_PI_MSG_CMD_CODE:  /* PIA */
            numPIARecv++;
            break;
        case RW_RA_MSG_CMD_CODE:  /* RAA */
            numRAARecv++;
            break;
        case RW_CC_MSG_CMD_CODE:  /* CCA */
            numCCARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRqMsgsRecv == 1)
        {
            time(&RwStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!RwStats::sendTraffic && 
            (RwStats::numRqMsgsSent == RwStats::numRaMsgsRecv))
        {
            time(&RwStats::stopTime);
            ftime(&RwStats::recvComplete);
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
RwStats::PrintIndications(std::ostream& os) const
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
RwStats::Print(std::ostream& os) const
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
       <<  numRqMsgsSent << endl;

    os << "Total Num of Request Msgs Received  "
       <<  numRaMsgsRecv << endl;

    os << "Total Num of Answer Msgs Received   "
       <<  numRaMsgsRecv << endl;
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

    os << "Num of PIR Sent                     "
       << numPIRSent << endl;

    os << "Num of PIA Sent                     "
       << numPIASent << endl;

    os << "Num of PIR Received                 "
       << numPIRRecv << endl;

    os << "Num of PIA Received                 "
       << numPIARecv << endl;
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
operator<<(ostream& os, const RwStats& rwStats)
{
    rwStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    RwStats::GetRwStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    RwStats::duration = duration;
    RwStats::burstSize = burstSize;
    RwStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&RwStats::starter);
    time(&RwStats::startTime);

    RwStats::sendTraffic = ITS_TRUE;
    RwStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendRwPIRequest;

}

void StopTraffic()
{
    RwStats::sendTraffic = ITS_FALSE;
    ftime(&RwStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    RwStats::GetRwStats()->Print(oss);
}

void ResetStats()
{
    RwStats::GetRwStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    RwStats::GetRwStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    RwStats::GetRwStats()->CalcTPS(oss);
}

