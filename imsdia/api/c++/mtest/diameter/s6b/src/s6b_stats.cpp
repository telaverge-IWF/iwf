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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: s6b_stats.cpp,v $
 * LOG: Revision 1.1  2011/04/27 12:14:12  vkumara
 * LOG: Draft for S6b interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: s6b_stats.cpp,v 1.1 2011/04/27 12:14:12 vkumara Exp $
 ****************************************************************************/
#ident "$Id: s6b_stats.cpp,v 1.1 2011/04/27 12:14:12 vkumara Exp $"

#include<dia_defines.h>
#include <app.h>

#include <s6b_stats.h>
#include <s6b_defines.h>

using namespace std;

its::ITS_Mutex S6bStats::guard(0);
ITS_BOOLEAN S6bStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN S6bStats::firstTime = ITS_FALSE;
time_t S6bStats::startTime;
time_t S6bStats::stopTime;
struct timeb S6bStats::sendComplete;
struct timeb S6bStats::recvComplete;
struct timeb S6bStats::starter;
struct timeb S6bStats::current;
int S6bStats::duration = 10;
int S6bStats::burstSize = 0;
int S6bStats::slpTime = 1000;

static S6bStats *s6bStats = NULL;

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
S6bStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numAARSent               = 0;
    numAAASent               = 0;
    numAARRecv               = 0;
    numAAARecv               = 0;

    numRARSent               = 0;
    numRARRecv               = 0;
    numRAASent               = 0;
    numRAARecv               = 0;

    numSTRSent               = 0;
    numSTASent               = 0;
    numSTRRecv               = 0;
    numSTARecv               = 0;

    numASRSent               = 0;
    numASRRecv               = 0;
    numASASent               = 0;
    numASARecv               = 0;

    numDERSent               = 0;
    numDERRecv               = 0;
    numDEASent               = 0;
    numDEARecv               = 0;

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
 *      Returns the WdStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
S6bStats*
S6bStats::GetS6bStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(S6bStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (s6bStats == NULL)
    {
        s6bStats = new S6bStats;
    }

    /* Release the semaphore
    */
    S6bStats::guard.Release();

    return s6bStats;
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
S6bStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((S6bStats::stopTime-S6bStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(S6bStats::stopTime-S6bStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/S6bStats::slpTime) * S6bStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = S6bStats::recvComplete.time - S6bStats::sendComplete.time;
         int mt = S6bStats::recvComplete.millitm - S6bStats::sendComplete.millitm;

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
S6bStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {

	case S6B_AA_MSG_CMD_CODE:  /* AAR */
	    numAARSent++;
	    break;
	case S6B_RA_MSG_CMD_CODE:  /* RAR */
	    numRARSent++;
            break;
        case S6B_ST_MSG_CMD_CODE:  /* STR */
            numSTRSent++;
            break;
        case S6B_AS_MSG_CMD_CODE:  /* ASR */
            numASRSent++;
            break;
        case S6B_DE_MSG_CMD_CODE:  /* DER */
            numDERSent++;
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
	case S6B_AA_MSG_CMD_CODE:  /* AAA */
            numAAASent++;
            break;
        case S6B_RA_MSG_CMD_CODE:  /*RAA */
            numRAASent++;
            break;
	case S6B_ST_MSG_CMD_CODE:  /* STA */
            numSTASent++;
            break;
        case S6B_AS_MSG_CMD_CODE:  /*ASAns */
            numASASent++;
            break;
        case S6B_DE_MSG_CMD_CODE:  /*DEAns */
            numDEASent++;
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
S6bStats::UpdateRecvIndications(ITS_UINT indic)
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
S6bStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
	case S6B_AA_MSG_CMD_CODE:  /* AAR */
            numAARRecv++;
            break;
        case S6B_RA_MSG_CMD_CODE:  /*RAR */
            numRARRecv++;
            break;
	case S6B_ST_MSG_CMD_CODE:  /* STR */
            numSTRRecv++;
            break;
        case S6B_AS_MSG_CMD_CODE:  /*ASReq */
            numASRRecv++;
            break;
        case S6B_DE_MSG_CMD_CODE:  /*DEReq */
            numDERRecv++;
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
	case S6B_AA_MSG_CMD_CODE:  /* AAA */
            numAAARecv++;
            break;
        case S6B_RA_MSG_CMD_CODE:  /*RAA */
            numRAARecv++;
            break;
        case S6B_ST_MSG_CMD_CODE:  /* STA */
            numSTARecv++;
            break;
        case S6B_AS_MSG_CMD_CODE:  /*ASAns */
            numASARecv++;
            break;
        case S6B_DE_MSG_CMD_CODE:  /* DEA */
            numDEARecv++;
            break;

        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&S6bStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!S6bStats::sendTraffic &&
            (S6bStats::numRqMsgsSent == S6bStats::numRaMsgsRecv))
        {
            time(&S6bStats::stopTime);
            ftime(&S6bStats::recvComplete);
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
S6bStats::PrintIndications(std::ostream& os) const
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
S6bStats::Print(std::ostream& os) const
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

    os << "Num of STR Sent                     "
       << numSTRSent << endl;

    os << "Num of STA Sent                     "
       << numSTASent << endl;

    os << "Num of STR Received                 "
       << numSTRRecv << endl;

    os << "Num of STA Received                 "
       << numSTARecv << endl;
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

    os << "Num of DER Sent                     "
       << numDERSent << endl;

    os << "Num of DEA Sent                     "
       << numDEASent << endl;

    os << "Num of DER Received                 "
       << numDERRecv << endl;

    os << "Num of DEA Received                 "
       << numDEARecv << endl;
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
operator<<(ostream& os, const S6bStats& s6bStats)
{
    s6bStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    S6bStats::GetS6bStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    S6bStats::duration = duration;
    S6bStats::burstSize = burstSize;
    S6bStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&S6bStats::starter);
    time(&S6bStats::startTime);

    S6bStats::sendTraffic = ITS_TRUE;
    S6bStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendS6bAARequest;

}

void StopTraffic()
{
    S6bStats::sendTraffic = ITS_FALSE;
    ftime(&S6bStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    S6bStats::GetS6bStats()->Print(oss);
}

void ResetStats()
{
    S6bStats::GetS6bStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    S6bStats::GetS6bStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    S6bStats::GetS6bStats()->CalcTPS(oss);
}

