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
 * LOG: $Log: sta_stats.cpp,v $
 * LOG: Revision 1.1  2011/04/27 12:01:40  vkumara
 * LOG: Draft version for STA sample app
 * LOG:
 * LOG:
 *
 * ID: $Id: sta_stats.cpp,v 1.1 2011/04/27 12:01:40 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sta_stats.cpp,v 1.1 2011/04/27 12:01:40 vkumara Exp $"

#include<dia_defines.h>
#include <app.h>

#include <sta_stats.h>
#include <sta_defines.h>

using namespace std;

its::ITS_Mutex STaStats::guard(0);
ITS_BOOLEAN STaStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN STaStats::firstTime = ITS_FALSE;
time_t STaStats::startTime;
time_t STaStats::stopTime;
struct timeb STaStats::sendComplete;
struct timeb STaStats::recvComplete;
struct timeb STaStats::starter;
struct timeb STaStats::current;
int STaStats::duration = 10;
int STaStats::burstSize = 0;
int STaStats::slpTime = 1000;

static STaStats *staStats = NULL;

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
STaStats::ResetAll()
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
STaStats*
STaStats::GetSTaStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(STaStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (staStats == NULL)
    {
        staStats = new STaStats;
    }

    /* Release the semaphore
    */
    STaStats::guard.Release();

    return staStats;
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
STaStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((STaStats::stopTime-STaStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(STaStats::stopTime-STaStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/STaStats::slpTime) * STaStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = STaStats::recvComplete.time - STaStats::sendComplete.time;
         int mt = STaStats::recvComplete.millitm - STaStats::sendComplete.millitm;

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
STaStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {

	case STA_AA_MSG_CMD_CODE:  /* AAR */
	    numAARSent++;
	    break;
	case STA_RA_MSG_CMD_CODE:  /* RAR */
	    numRARSent++;
            break;
        case STA_ST_MSG_CMD_CODE:  /* STR */
            numSTRSent++;
            break;
        case STA_AS_MSG_CMD_CODE:  /* ASR */
            numASRSent++;
            break;
        case STA_DE_MSG_CMD_CODE:  /* DER */
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
	case STA_AA_MSG_CMD_CODE:  /* AAA */
            numAAASent++;
            break;
        case STA_RA_MSG_CMD_CODE:  /*RAA */
            numRAASent++;
            break;
	case STA_ST_MSG_CMD_CODE:  /* STA */
            numSTASent++;
            break;
        case STA_AS_MSG_CMD_CODE:  /*ASAns */
            numASASent++;
            break;
        case STA_DE_MSG_CMD_CODE:  /*DEAns */
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
STaStats::UpdateRecvIndications(ITS_UINT indic)
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
STaStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
	case STA_AA_MSG_CMD_CODE:  /* AAR */
            numAARRecv++;
            break;
        case STA_RA_MSG_CMD_CODE:  /*RAR */
            numRARRecv++;
            break;
	case STA_ST_MSG_CMD_CODE:  /* STR */
            numSTRRecv++;
            break;
        case STA_AS_MSG_CMD_CODE:  /*ASReq */
            numASRRecv++;
            break;
        case STA_DE_MSG_CMD_CODE:  /*DEReq */
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
	case STA_AA_MSG_CMD_CODE:  /* AAA */
            numAAARecv++;
            break;
        case STA_RA_MSG_CMD_CODE:  /*RAA */
            numRAARecv++;
            break;
        case STA_ST_MSG_CMD_CODE:  /* STA */
            numSTARecv++;
            break;
        case STA_AS_MSG_CMD_CODE:  /*ASAns */
            numASARecv++;
            break;
        case STA_DE_MSG_CMD_CODE:  /* DEA */
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
            time(&STaStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!STaStats::sendTraffic &&
            (STaStats::numRqMsgsSent == STaStats::numRaMsgsRecv))
        {
            time(&STaStats::stopTime);
            ftime(&STaStats::recvComplete);
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
STaStats::PrintIndications(std::ostream& os) const
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
STaStats::Print(std::ostream& os) const
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
operator<<(ostream& os, const STaStats& staStats)
{
    staStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    STaStats::GetSTaStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    STaStats::duration = duration;
    STaStats::burstSize = burstSize;
    STaStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&STaStats::starter);
    time(&STaStats::startTime);

    STaStats::sendTraffic = ITS_TRUE;
    STaStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendSTaAARequest;

}

void StopTraffic()
{
    STaStats::sendTraffic = ITS_FALSE;
    ftime(&STaStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    STaStats::GetSTaStats()->Print(oss);
}

void ResetStats()
{
    STaStats::GetSTaStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    STaStats::GetSTaStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    STaStats::GetSTaStats()->CalcTPS(oss);
}

