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
 *  ID: $Id: gy_stats.cpp,v 1.1 2011/03/10 09:27:34 vkumara Exp $
 *
 *  LOG: $Log: gy_stats.cpp,v $
 *  LOG: Revision 1.1  2011/03/10 09:27:34  vkumara
 *  LOG: Sample Demo for Gy Interface
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.1  2006/12/19 08:42:08  kamakshilk
 *  LOG: RfRo interface demo for static and distributed
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: gy_stats.cpp,v 1.1 2011/03/10 09:27:34 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <gy_stats.h>
#include <gy_defines.h>

#include <diameter/Command.h>
using namespace std;

its::ITS_Mutex GyStats::guard(0);
ITS_BOOLEAN GyStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN GyStats::firstTime = ITS_FALSE;
time_t GyStats::startTime;
time_t GyStats::stopTime;
struct timeb GyStats::sendComplete;
struct timeb GyStats::recvComplete;
struct timeb GyStats::starter;
struct timeb GyStats::current;
int GyStats::duration = 10;
int GyStats::burstSize = 0;
int GyStats::slpTime = 1000;

static GyStats *gyStats = NULL;

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
GyStats::ResetAll()
{
    Lock();

    numGqMsgsSent            = 0;
    numGaMsgsSent            = 0;
    numGqMsgsRecv            = 0;
    numGaMsgsRecv            = 0;

    numACRSent               = 0;
    numACRRecv               = 0;
    numACASent               = 0;
    numACARecv               = 0;

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
GyStats* 
GyStats::GetGyStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(GyStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (gyStats == NULL)
    {
        gyStats = new GyStats;
    }

    /* Release the semaphore
    */
    GyStats::guard.Release();

    return gyStats;
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
GyStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numGaMsgsRecv == numGqMsgsSent)
    {
         /* Calculate tps
         */
         if ((GyStats::stopTime-GyStats::startTime) > 0 )
         {
             tps = (numGaMsgsRecv)/(GyStats::stopTime-GyStats::startTime);
         }
         else
         {
             //tps = (numGaMsgsRecv);
             tps = (1000/GyStats::slpTime) * GyStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = GyStats::recvComplete.time - GyStats::sendComplete.time;
         int mt = GyStats::recvComplete.millitm - GyStats::sendComplete.millitm;

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
GyStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case GY_AC_MSG_CMD_CODE:  /*ACR */
            numACRSent++;
            break;
        case GY_CC_MSG_CMD_CODE:  /* CC */
            numCCRSent++;
            break;
        default:
            break;
        }
        numGqMsgsSent++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case GY_AC_MSG_CMD_CODE:  /* ACA */
            numACASent++;
            break;
        case GY_CC_MSG_CMD_CODE:  /* CCA */
            numCCASent++;
            break;
        default:
            break;
        }
        numGaMsgsSent++;
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
GyStats::UpdateRecvIndications(ITS_UINT indic)
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
GyStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case GY_AC_MSG_CMD_CODE:  /* ACR */
            numACRRecv++;
            break;
        case GY_RA_MSG_CMD_CODE:  /* RAR */
            numRARRecv++;
            break;
        case GY_CC_MSG_CMD_CODE:  /* CCR */
            numCCRRecv++;
            break;
        default:
            break;
        }
        numGqMsgsRecv++;
    }
    /* If message is answer
    */
    else
    {
        switch(commandCode)
        {
        case GY_AC_MSG_CMD_CODE:  /* ACA */
            numACARecv++;
            break;
        case GY_RA_MSG_CMD_CODE:  /* RAA */
            numRAARecv++;
            break;
        case GY_CC_MSG_CMD_CODE:  /* CCA */
            numCCARecv++;
            break;
        default:
            break;
        }
        numGaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numGaMsgsRecv == 1)
        {
            time(&GyStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!GyStats::sendTraffic && 
            (GyStats::numGqMsgsSent == GyStats::numGaMsgsRecv))
        {
            time(&GyStats::stopTime);
            ftime(&GyStats::recvComplete);
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
GyStats::PrintIndications(std::ostream& os) const
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
GyStats::Print(std::ostream& os) const
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
       <<  numGqMsgsSent << endl;

    os << "Total Num of Answer Msgs Sent       "
       <<  numGaMsgsSent << endl;

    os << "Total Num of Request Msgs Received  "
       <<  numGqMsgsRecv << endl;

    os << "Total Num of Answer Msgs Received   "
       <<  numGaMsgsRecv << endl;
    os << endl;

    os << "Num of CCR Sent                     "
       << numCCRSent << endl;

    os << "Num of CCA Sent                     "
       << numCCASent << endl;

    os << "Num of CCR Received                 "
       << numCCRRecv << endl;

    os << "Num of CCA Received                 "
       << numCCARecv << endl;

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
operator<<(ostream& os, const GyStats& gyStats)
{
    gyStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    GyStats::GetGyStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    GyStats::duration = duration;
    GyStats::burstSize = burstSize;
    GyStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&GyStats::starter);
    time(&GyStats::startTime);

    GyStats::sendTraffic = ITS_TRUE;
    GyStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendCreditControlRequestInitial;

}

void StopTraffic()
{
    GyStats::sendTraffic = ITS_FALSE;
    ftime(&GyStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    GyStats::GetGyStats()->Print(oss);
}

void ResetStats()
{
    GyStats::GetGyStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    GyStats::GetGyStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    GyStats::GetGyStats()->CalcTPS(oss);
}

