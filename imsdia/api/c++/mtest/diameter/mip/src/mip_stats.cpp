/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: mip_stats.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/08 14:15:24  hbhatnagar
 * LOG: made changes for the Accounting and clean up
 * LOG:
 * LOG: Revision 1.1  2007/01/01 15:18:49  hbhatnagar
 * LOG: adding the baseline demo application for the MobileIP
 * LOG:
 *
 * ID: $Id: mip_stats.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/

#include <dia_defines.h>
#include <app.h>

#include <mip_stats.h>
#include <mip_defines.h>

using namespace std;

its::ITS_Mutex MipStats::guard(0);
ITS_BOOLEAN MipStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN MipStats::firstTime = ITS_FALSE;
time_t MipStats::startTime;
time_t MipStats::stopTime;
struct timeb MipStats::sendComplete;
struct timeb MipStats::recvComplete;
struct timeb MipStats::starter;
struct timeb MipStats::current;
int MipStats::duration = 10;
int MipStats::burstSize = 0;
int MipStats::slpTime = 1000;

static MipStats *mipStats = NULL;

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
MipStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numAMRSent               = 0;
    numAMRRecv               = 0;
    numAMASent               = 0;
    numAMARecv               = 0;

    numHARSent               = 0;
    numHARRecv               = 0;
    numHAASent               = 0;
    numHAARecv               = 0;

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
 *      Returns the MipStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
MipStats*
MipStats::GetMipStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(MipStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (mipStats == NULL)
    {
        mipStats = new MipStats;
    }

    /* Release the semaphore
    */
    MipStats::guard.Release();

    return mipStats;
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
MipStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((MipStats::stopTime-MipStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(MipStats::stopTime-MipStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/MipStats::slpTime) * MipStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = MipStats::recvComplete.time - MipStats::sendComplete.time;
         int mt = MipStats::recvComplete.millitm - MipStats::sendComplete.millitm;

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
MipStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case MIP_AM_MSG_CMD_CODE:  /* AMR */
            numAMRSent++;
            break;
        case MIP_HA_MSG_CMD_CODE:  /* HAR */
            numHARSent++;
            break;
        case MIP_AC_MSG_CMD_CODE:  /* ACR */
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
        case MIP_AM_MSG_CMD_CODE:  /* AMA */
            numAMASent++;
            break;
        case MIP_HA_MSG_CMD_CODE:  /*HAA */
            numHAASent++;
            break;
        case MIP_AC_MSG_CMD_CODE:  /*ACA */
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
MipStats::UpdateRecvIndications(ITS_UINT indic)
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
MipStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case MIP_AM_MSG_CMD_CODE:  /* AMR */
            numAMRRecv++;
            break;
        case MIP_HA_MSG_CMD_CODE:  /* HAR */
            numHARRecv++;
            break;
        case MIP_AC_MSG_CMD_CODE:  /* ACR */
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
        case MIP_AM_MSG_CMD_CODE:  /* AMA */
            numAMARecv++;
            break;
        case MIP_HA_MSG_CMD_CODE:  /*  HAA */
            numHAARecv++;
            break;
        case MIP_AC_MSG_CMD_CODE:  /*  ACA */
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
            time(&MipStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!MipStats::sendTraffic &&
            (MipStats::numRqMsgsSent == MipStats::numRaMsgsRecv))
        {
            time(&MipStats::stopTime);
            ftime(&MipStats::recvComplete);
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
MipStats::PrintIndications(std::ostream& os) const
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
MipStats::Print(std::ostream& os) const
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

    os << "Num of AMR Sent                     "
       << numAMRSent << endl;

    os << "Num of AMA Sent                     "
       << numAMASent << endl;

    os << "Num of AMR Received                 "
       << numAMRRecv << endl;

    os << "Num of AMA Received                 "
       << numAMARecv << endl;
    os << endl;

    os << "Num of HAR Sent                     "
       << numHARSent << endl;

    os << "Num of HAA Sent                     "
       << numHAASent << endl;

    os << "Num of HAR Received                 "
       << numHARRecv << endl;

    os << "Num of HAA Received                 "
       << numHAARecv << endl;
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
operator<<(ostream& os, const MipStats& shStats)
{
    shStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    MipStats::GetMipStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    MipStats::duration = duration;
    MipStats::burstSize = burstSize;
    MipStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&MipStats::starter);
    time(&MipStats::startTime);

    MipStats::sendTraffic = ITS_TRUE;
    MipStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendMipAAMobileNodeRequest;

}

void StopTraffic()
{
    MipStats::sendTraffic = ITS_FALSE;
    ftime(&MipStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    MipStats::GetMipStats()->Print(oss);
}

void ResetStats()
{
    MipStats::GetMipStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    MipStats::GetMipStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    MipStats::GetMipStats()->CalcTPS(oss);
}

