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
 *  ID: $Id: gx_stats.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 *
 *  LOG: $Log: gx_stats.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.2  2006/12/19 09:06:07  kamakshilk
 *  LOG: New architecture to work with static and distributed
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/07/24 14:38:10  nvijikumar
 *  LOG: Baseline demo application for Gx Interface.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: gx_stats.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $"

#include <dia_defines.h>
#include <app.h>

#include <gx_stats.h>
#include <gx_defines.h>

#include <diameter/Command.h>
using namespace std;

its::ITS_Mutex GxStats::guard(0);
ITS_BOOLEAN GxStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN GxStats::firstTime = ITS_FALSE;
time_t GxStats::startTime;
time_t GxStats::stopTime;
struct timeb GxStats::sendComplete;
struct timeb GxStats::recvComplete;
struct timeb GxStats::starter;
struct timeb GxStats::current;
int GxStats::duration = 10;
int GxStats::burstSize = 0;
int GxStats::slpTime = 1000;

static GxStats *gxStats = NULL;

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
GxStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

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
 *      Returns the GxStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
GxStats* 
GxStats::GetGxStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(GxStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (gxStats == NULL)
    {
        gxStats = new GxStats;
    }

    /* Release the semaphore
    */
    GxStats::guard.Release();

    return gxStats;
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
GxStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((GxStats::stopTime-GxStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(GxStats::stopTime-GxStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/GxStats::slpTime) * GxStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /* 
          * Log the time taken for the reception of messages after sending
          */
         int st = GxStats::recvComplete.time - GxStats::sendComplete.time;
         int mt = GxStats::recvComplete.millitm - GxStats::sendComplete.millitm;

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
GxStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case GX_RA_MSG_CMD_CODE:  /*ReAuth */
            numRARSent++;
            break;
        case GX_CC_MSG_CMD_CODE:  /* CC */
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
        case GX_RA_MSG_CMD_CODE:  /*ReAuth */
            numRAASent++;
            break;
        case GX_CC_MSG_CMD_CODE:  /* CCA */
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
GxStats::UpdateRecvIndications(ITS_UINT indic)
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
GxStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case GX_RA_MSG_CMD_CODE:  /*ReAuth */
            numRARRecv++;
            break;
        case GX_CC_MSG_CMD_CODE:  /* CCR */
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
        case GX_RA_MSG_CMD_CODE:  /*ReAuth */
            numRAARecv++;
            break;
        case GX_CC_MSG_CMD_CODE:  /* STA */
            numCCARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&GxStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!GxStats::sendTraffic && 
            (GxStats::numRqMsgsSent == GxStats::numRaMsgsRecv))
        {
            time(&GxStats::stopTime);
            ftime(&GxStats::recvComplete);
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
GxStats::PrintIndications(std::ostream& os) const
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
GxStats::Print(std::ostream& os) const
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

    os << "Num of RAR Sent                     "
       << numRARSent << endl;

    os << "Num of RAA Sent                     "
       << numRAASent << endl;

    os << "Num of RAR Received                 "
       << numRARRecv << endl;

    os << "Num of RAA Received                 "
       << numRAARecv << endl;
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
operator<<(ostream& os, const GxStats& gxStats)
{
    gxStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    GxStats::GetGxStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    GxStats::duration = duration;
    GxStats::burstSize = burstSize;
    GxStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&GxStats::starter);
    time(&GxStats::startTime);

    GxStats::sendTraffic = ITS_TRUE;
    GxStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendGxCCRequest;

}

void StopTraffic()
{
    GxStats::sendTraffic = ITS_FALSE;
    ftime(&GxStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    GxStats::GetGxStats()->Print(oss);
}

void ResetStats()
{
    GxStats::GetGxStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    GxStats::GetGxStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    GxStats::GetGxStats()->CalcTPS(oss);
}

