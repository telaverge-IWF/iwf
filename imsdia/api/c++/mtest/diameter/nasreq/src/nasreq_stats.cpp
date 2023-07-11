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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: nasreq_stats.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:31:42  nanaparthi
 * LOG: NASREQ Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: nasreq_stats.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: nasreq_stats.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $"

#include<dia_defines.h>
#include <app.h>

#include <nasreq_stats.h>
#include <nasreq_defines.h>

using namespace std;

its::ITS_Mutex NasreqStats::guard(0);
ITS_BOOLEAN NasreqStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN NasreqStats::firstTime = ITS_FALSE;
time_t NasreqStats::startTime;
time_t NasreqStats::stopTime;
struct timeb NasreqStats::sendComplete;
struct timeb NasreqStats::recvComplete;
struct timeb NasreqStats::starter;
struct timeb NasreqStats::current;
int NasreqStats::duration = 10;
int NasreqStats::burstSize = 0;
int NasreqStats::slpTime = 1000;

static NasreqStats *nasreqStats = NULL;

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
NasreqStats::ResetAll()
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

    numACRSent               = 0;
    numACRRecv               = 0;
    numACASent               = 0;
    numACARecv               = 0;


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
 *      Returns the NasreqStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
NasreqStats*
NasreqStats::GetNasreqStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(NasreqStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (nasreqStats == NULL)
    {
        nasreqStats = new NasreqStats;
    }

    /* Release the semaphore
    */
    NasreqStats::guard.Release();

    return nasreqStats;
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
NasreqStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((NasreqStats::stopTime-NasreqStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(NasreqStats::stopTime-NasreqStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/NasreqStats::slpTime) * NasreqStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = NasreqStats::recvComplete.time - NasreqStats::sendComplete.time;
         int mt = NasreqStats::recvComplete.millitm - NasreqStats::sendComplete.millitm;

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
NasreqStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {

	case NASREQ_AA_MSG_CMD_CODE:  /* AAR */
	    numAARSent++;
	    break;
	case NASREQ_RA_MSG_CMD_CODE:  /* RAR */
	    numRARSent++;
            break;
        case NASREQ_ST_MSG_CMD_CODE:  /* STR */
            numSTRSent++;
            break;
        case NASREQ_AS_MSG_CMD_CODE:  /* ASR */
            numASRSent++;
            break;
        case NASREQ_AC_MSG_CMD_CODE:  /* ACR */
            numACRSent++;
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
	case NASREQ_AA_MSG_CMD_CODE:  /* AAA */
            numAAASent++;
            break;
        case NASREQ_RA_MSG_CMD_CODE:  /*RAA */
            numRAASent++;
            break;
	case NASREQ_ST_MSG_CMD_CODE:  /* STA */
            numSTASent++;
            break;
        case NASREQ_AS_MSG_CMD_CODE:  /*ASAns */
            numASASent++;
            break;
        case NASREQ_AC_MSG_CMD_CODE:  /*ACAns */
            numACASent++;
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
NasreqStats::UpdateRecvIndications(ITS_UINT indic)
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
NasreqStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
	case NASREQ_AA_MSG_CMD_CODE:  /* AAR */
            numAARRecv++;
            break;
        case NASREQ_RA_MSG_CMD_CODE:  /*RAR */
            numRARRecv++;
            break;
	case NASREQ_ST_MSG_CMD_CODE:  /* STR */
            numSTRRecv++;
            break;
        case NASREQ_AS_MSG_CMD_CODE:  /*ASReq */
            numASRRecv++;
            break;
        case NASREQ_AC_MSG_CMD_CODE:  /*ACReq */
            numACRRecv++;
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
	case NASREQ_AA_MSG_CMD_CODE:  /* AAA */
            numAAARecv++;
            break;
        case NASREQ_RA_MSG_CMD_CODE:  /*RAA */
            numRAARecv++;
            break;
        case NASREQ_ST_MSG_CMD_CODE:  /* STA */
            numSTARecv++;
            break;
        case NASREQ_AS_MSG_CMD_CODE:  /*ASAns */
            numASARecv++;
            break;
        case NASREQ_AC_MSG_CMD_CODE:  /* ACA */
            numACARecv++;
            break;

        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&NasreqStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!NasreqStats::sendTraffic &&
            (NasreqStats::numRqMsgsSent == NasreqStats::numRaMsgsRecv))
        {
            time(&NasreqStats::stopTime);
            ftime(&NasreqStats::recvComplete);
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
NasreqStats::PrintIndications(std::ostream& os) const
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
NasreqStats::Print(std::ostream& os) const
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

    os << "Num of ACR Sent                     "
       << numACRSent << endl;

    os << "Num of ACA Sent                     "
       << numACASent << endl;

    os << "Num of ACR Received                 "
       << numACRRecv << endl;

    os << "Num of ACA Received                 "
       << numACARecv << endl;
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
operator<<(ostream& os, const NasreqStats& nasreqStats)
{
    nasreqStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    NasreqStats::GetNasreqStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    NasreqStats::duration = duration;
    NasreqStats::burstSize = burstSize;
    NasreqStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&NasreqStats::starter);
    time(&NasreqStats::startTime);

    NasreqStats::sendTraffic = ITS_TRUE;
    NasreqStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendNasreqAARequest;

}

void StopTraffic()
{
    NasreqStats::sendTraffic = ITS_FALSE;
    ftime(&NasreqStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    NasreqStats::GetNasreqStats()->Print(oss);
}

void ResetStats()
{
    NasreqStats::GetNasreqStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    NasreqStats::GetNasreqStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    NasreqStats::GetNasreqStats()->CalcTPS(oss);
}

