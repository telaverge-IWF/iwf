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
 *  ID: $Id: swx_stats.cpp,v 1.1 2011/05/03 04:58:33 vkumara Exp $
 *
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: swx_stats.cpp,v 1.1 2011/05/03 04:58:33 vkumara Exp $"

#include<dia_defines.h>
#include <app.h>

#include <swx_stats.h>
#include <swx_defines.h>

using namespace std;

its::ITS_Mutex SWxStats::guard(0);
ITS_BOOLEAN SWxStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN SWxStats::firstTime = ITS_FALSE;
time_t SWxStats::startTime;
time_t SWxStats::stopTime;
struct timeb SWxStats::sendComplete;
struct timeb SWxStats::recvComplete;
struct timeb SWxStats::starter;
struct timeb SWxStats::current;
int SWxStats::duration = 10;
int SWxStats::burstSize = 0;
int SWxStats::slpTime = 1000;

static SWxStats *swxStats = NULL;

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
SWxStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numMARSent               = 0;
    numMARRecv               = 0;
    numMAASent               = 0;
    numMAARecv               = 0;

    numRTRSent               = 0;
    numRTRRecv               = 0;
    numRTASent               = 0;
    numRTARecv               = 0;

    numSARSent               = 0;
    numSARRecv               = 0;
    numSAASent               = 0;
    numSAARecv               = 0;

    numPPRSent               = 0;
    numPPRRecv               = 0;
    numPPASent               = 0;
    numPPARecv               = 0;

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
 *      Returns the SWxStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SWxStats* 
SWxStats::GetSWxStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(SWxStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (swxStats == NULL)
    {
        swxStats = new SWxStats;
    }

    /* Release the semaphore
    */
    SWxStats::guard.Release();

    return swxStats;
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
SWxStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((SWxStats::stopTime-SWxStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(SWxStats::stopTime-SWxStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/SWxStats::slpTime) * SWxStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = SWxStats::recvComplete.time - SWxStats::sendComplete.time;
         int mt = SWxStats::recvComplete.millitm - SWxStats::sendComplete.millitm;

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
SWxStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case SWX_SA_MSG_CMD_CODE:  /* SAR */
            numSARSent++;
            break;
        case SWX_PP_MSG_CMD_CODE:  /* PPR */
            numPPRSent++;
            break;
        case SWX_RT_MSG_CMD_CODE:  /* RTR */
            numRTRSent++;
            break;
        case SWX_MA_MSG_CMD_CODE:  /*MAReq */
            numMARSent++;
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
        case SWX_RT_MSG_CMD_CODE:  /* RTA */
            numRTASent++;
            break;
        case SWX_MA_MSG_CMD_CODE:  /*MAAns */
            numMAASent++;
            break;
        case SWX_SA_MSG_CMD_CODE:  /*SAAns */
            numSAASent++;
        case SWX_PP_MSG_CMD_CODE:  /*PPAns */
            numPPASent++;
            break;
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
SWxStats::UpdateRecvIndications(ITS_UINT indic)
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
SWxStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case SWX_RT_MSG_CMD_CODE:  /* RTR */
            numRTRRecv++;
            break;
        case SWX_MA_MSG_CMD_CODE:  /*MAReq */
            numMARRecv++;
            break;
        case SWX_PP_MSG_CMD_CODE:  /*PPReq */
            numPPRRecv++;
            break;
        case SWX_SA_MSG_CMD_CODE:  /*SAReq */
            numSARRecv++;
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
        case SWX_RT_MSG_CMD_CODE:  /* RTA */
            numRTARecv++;
            break;
        case SWX_MA_MSG_CMD_CODE:  /*MAAns */
            numMAARecv++;
            break;
        case SWX_PP_MSG_CMD_CODE:  /* PPA */
            numPPARecv++;
            break;
        case SWX_SA_MSG_CMD_CODE:  /* SAA */
            numSAARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&SWxStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!SWxStats::sendTraffic && 
            (SWxStats::numRqMsgsSent == SWxStats::numRaMsgsRecv))
        {
            time(&SWxStats::stopTime);
            ftime(&SWxStats::recvComplete);
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
SWxStats::PrintIndications(std::ostream& os) const
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
SWxStats::Print(std::ostream& os) const
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

    os << "Num of MAR Sent                     "
       << numMARSent << endl;

    os << "Num of MAA Sent                     "
       << numMAASent << endl;

    os << "Num of MAR Received                 "
       << numMARRecv << endl;

    os << "Num of MAA Received                 "
       << numMAARecv << endl;
    os << endl;

    os << "Num of RTR Sent                     "
       << numRTRSent << endl;

    os << "Num of RTA Sent                     "
       << numRTASent << endl;

    os << "Num of RTR Received                 "
       << numRTRRecv << endl;

    os << "Num of RTA Received                 "
       << numRTARecv << endl;
    os << endl;

    os << "Num of PPR Sent                     "
       << numPPRSent << endl;

    os << "Num of PPA Sent                     "
       << numPPASent << endl;

    os << "Num of PPR Received                 "
       << numPPRRecv << endl;

    os << "Num of PPA Received                 "
       << numPPARecv << endl;
    os << endl;

    os << "Num of SAR Sent                     "
       << numSARSent << endl;

    os << "Num of SAA Sent                     "
       << numSAASent << endl;

    os << "Num of SAR Received                 "
       << numSARRecv << endl;

    os << "Num of SAA Received                 "
       << numSAARecv << endl;

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
operator<<(ostream& os, const SWxStats& swxStats)
{
    swxStats.Print(os);
    return os;
}


void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    SWxStats::GetSWxStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    SWxStats::duration = duration;
    SWxStats::burstSize = burstSize;
    SWxStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&SWxStats::starter);
    time(&SWxStats::startTime);

    SWxStats::sendTraffic = ITS_TRUE;
    SWxStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendSWxMultimediaAuthenticationRequest;

}

void StopTraffic()
{
    SWxStats::sendTraffic = ITS_FALSE;
    ftime(&SWxStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    SWxStats::GetSWxStats()->Print(oss);
}

void ResetStats()
{
    SWxStats::GetSWxStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    SWxStats::GetSWxStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    SWxStats::GetSWxStats()->CalcTPS(oss);
}


