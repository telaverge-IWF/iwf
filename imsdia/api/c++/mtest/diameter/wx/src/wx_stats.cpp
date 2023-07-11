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
 *  ID: $Id: wx_stats.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 *
 *  LOG: $Log: wx_stats.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.2  2006/12/19 09:02:14  kamakshilk
 *  LOG: New architecture to work with static and distributed
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/08/04 17:43:48  nvijikumar
 *  LOG: Changes to update the stats for all Wx Interface Messages.
 *  LOG:
 *  LOG: Revision 1.1  2006/07/24 15:40:06  nvijikumar
 *  LOG: Baseline commit for demo application ( Wx Interface).
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: wx_stats.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $"

#include<dia_defines.h>
#include <app.h>

#include <wx_stats.h>
#include <wx_defines.h>

using namespace std;

its::ITS_Mutex WxStats::guard(0);
ITS_BOOLEAN WxStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN WxStats::firstTime = ITS_FALSE;
time_t WxStats::startTime;
time_t WxStats::stopTime;
struct timeb WxStats::sendComplete;
struct timeb WxStats::recvComplete;
struct timeb WxStats::starter;
struct timeb WxStats::current;
int WxStats::duration = 10;
int WxStats::burstSize = 0;
int WxStats::slpTime = 1000;

static WxStats *wxStats = NULL;

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
WxStats::ResetAll()
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
 *      Returns the WxStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
WxStats* 
WxStats::GetWxStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(WxStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (wxStats == NULL)
    {
        wxStats = new WxStats;
    }

    /* Release the semaphore
    */
    WxStats::guard.Release();

    return wxStats;
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
WxStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((WxStats::stopTime-WxStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(WxStats::stopTime-WxStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/WxStats::slpTime) * WxStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = WxStats::recvComplete.time - WxStats::sendComplete.time;
         int mt = WxStats::recvComplete.millitm - WxStats::sendComplete.millitm;

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
WxStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case WX_SA_MSG_CMD_CODE:  /* SAR */
            numSARSent++;
            break;
        case WX_PP_MSG_CMD_CODE:  /* PPR */
            numPPRSent++;
            break;
        case WX_RT_MSG_CMD_CODE:  /* RTR */
            numRTRSent++;
            break;
        case WX_MA_MSG_CMD_CODE:  /*MAReq */
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
        case WX_RT_MSG_CMD_CODE:  /* RTA */
            numRTASent++;
            break;
        case WX_MA_MSG_CMD_CODE:  /*MAAns */
            numMAASent++;
            break;
        case WX_SA_MSG_CMD_CODE:  /*SAAns */
            numSAASent++;
        case WX_PP_MSG_CMD_CODE:  /*PPAns */
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
WxStats::UpdateRecvIndications(ITS_UINT indic)
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
WxStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case WX_RT_MSG_CMD_CODE:  /* RTR */
            numRTRRecv++;
            break;
        case WX_MA_MSG_CMD_CODE:  /*MAReq */
            numMARRecv++;
            break;
        case WX_PP_MSG_CMD_CODE:  /*PPReq */
            numPPRRecv++;
            break;
        case WX_SA_MSG_CMD_CODE:  /*SAReq */
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
        case WX_RT_MSG_CMD_CODE:  /* RTA */
            numRTARecv++;
            break;
        case WX_MA_MSG_CMD_CODE:  /*MAAns */
            numMAARecv++;
            break;
        case WX_PP_MSG_CMD_CODE:  /* PPA */
            numPPARecv++;
            break;
        case WX_SA_MSG_CMD_CODE:  /* SAA */
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
            time(&WxStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!WxStats::sendTraffic && 
            (WxStats::numRqMsgsSent == WxStats::numRaMsgsRecv))
        {
            time(&WxStats::stopTime);
            ftime(&WxStats::recvComplete);
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
WxStats::PrintIndications(std::ostream& os) const
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
WxStats::Print(std::ostream& os) const
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
operator<<(ostream& os, const WxStats& wxStats)
{
    wxStats.Print(os);
    return os;
}


void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    WxStats::GetWxStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    WxStats::duration = duration;
    WxStats::burstSize = burstSize;
    WxStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&WxStats::starter);
    time(&WxStats::startTime);

    WxStats::sendTraffic = ITS_TRUE;
    WxStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendWxMultimediaAuthenticationRequest;

}

void StopTraffic()
{
    WxStats::sendTraffic = ITS_FALSE;
    ftime(&WxStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    WxStats::GetWxStats()->Print(oss);
}

void ResetStats()
{
    WxStats::GetWxStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    WxStats::GetWxStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    WxStats::GetWxStats()->CalcTPS(oss);
}


