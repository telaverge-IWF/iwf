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
 * LOG: $Log: rr_delegatedmodel_stats.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:36:51  vkumara
 * LOG: Baseline for rr_delegatedmodel interface.
 * LOG:
 * LOG:
 * ID: $Id: rr_delegatedmodel_stats.cpp,v 1.1 2011/06/29 06:36:51 vkumara Exp $
 ****************************************************************************/
#ident "$Id: rr_delegatedmodel_stats.cpp,v 1.1 2011/06/29 06:36:51 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <rr_delegatedmodel_stats.h>
#include <rr_delegatedmodel_defines.h>

using namespace std;

its::ITS_Mutex Rr_DelegatedmodelStats::guard(0);
ITS_BOOLEAN Rr_DelegatedmodelStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN Rr_DelegatedmodelStats::firstTime = ITS_FALSE;
time_t Rr_DelegatedmodelStats::startTime;
time_t Rr_DelegatedmodelStats::stopTime;
struct timeb Rr_DelegatedmodelStats::sendComplete;
struct timeb Rr_DelegatedmodelStats::recvComplete;
struct timeb Rr_DelegatedmodelStats::starter;
struct timeb Rr_DelegatedmodelStats::current;
int Rr_DelegatedmodelStats::duration = 10;
int Rr_DelegatedmodelStats::burstSize = 0;
int Rr_DelegatedmodelStats::slpTime = 1000;

static Rr_DelegatedmodelStats *rr_delegatedmodelStats = NULL;

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
Rr_DelegatedmodelStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numUDRSent               = 0;
    numUDRRecv               = 0;
    numUDASent               = 0;
    numUDARecv               = 0;

    numPNRSent               = 0;
    numPNRRecv               = 0;
    numPNASent               = 0;
    numPNARecv               = 0;

    numCCRSent               = 0;
    numCCRRecv               = 0;
    numCCASent               = 0;
    numCCARecv               = 0;

    numRARSent               = 0;
    numRARRecv               = 0;
    numRAASent               = 0;
    numRAARecv               = 0;

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
 *      Returns the Rr_DelegatedmodelStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
Rr_DelegatedmodelStats*
Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(Rr_DelegatedmodelStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (rr_delegatedmodelStats == NULL)
    {
        rr_delegatedmodelStats = new Rr_DelegatedmodelStats;
    }

    /* Release the semaphore
    */
    Rr_DelegatedmodelStats::guard.Release();

    return rr_delegatedmodelStats;
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
Rr_DelegatedmodelStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((Rr_DelegatedmodelStats::stopTime-Rr_DelegatedmodelStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(Rr_DelegatedmodelStats::stopTime-Rr_DelegatedmodelStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/Rr_DelegatedmodelStats::slpTime) * Rr_DelegatedmodelStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = Rr_DelegatedmodelStats::recvComplete.time - Rr_DelegatedmodelStats::sendComplete.time;
         int mt = Rr_DelegatedmodelStats::recvComplete.millitm - Rr_DelegatedmodelStats::sendComplete.millitm;

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
Rr_DelegatedmodelStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case Rr_Delegatedmodel_UD_MSG_CMD_CODE:  /* UDR */
            numUDRSent++;
            break;
        case Rr_Delegatedmodel_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRSent++;
            break;
        case Rr_Delegatedmodel_CC_MSG_CMD_CODE:  /*CCReq */
            numCCRSent++;
            break;
        case Rr_Delegatedmodel_RA_MSG_CMD_CODE:  /*RAReq */
            numRARSent++;
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
        case Rr_Delegatedmodel_UD_MSG_CMD_CODE:  /* UDA */
            numUDASent++;
            break;
        case Rr_Delegatedmodel_PN_MSG_CMD_CODE:  /*PNAns */
            numPNASent++;
            break;
        case Rr_Delegatedmodel_CC_MSG_CMD_CODE:  /*CCAns */
            numCCASent++;
            break;
        case Rr_Delegatedmodel_RA_MSG_CMD_CODE:  /*RAAns */
            numRAASent++;
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
Rr_DelegatedmodelStats::UpdateRecvIndications(ITS_UINT indic)
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
Rr_DelegatedmodelStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case Rr_Delegatedmodel_UD_MSG_CMD_CODE:  /* UDR */
            numUDRRecv++;
            break;
        case Rr_Delegatedmodel_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRRecv++;
            break;
        case Rr_Delegatedmodel_CC_MSG_CMD_CODE:  /*CCReq */
            numCCRRecv++;
            break;
        case Rr_Delegatedmodel_RA_MSG_CMD_CODE:  /*RAReq */
            numRARRecv++;
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
        case Rr_Delegatedmodel_UD_MSG_CMD_CODE:  /* UDA */
            numUDARecv++;
            break;
        case Rr_Delegatedmodel_PN_MSG_CMD_CODE:  /* PNA */
            numPNARecv++;
            break;
        case Rr_Delegatedmodel_CC_MSG_CMD_CODE:  /* CCA */
            numCCARecv++;
            break;
        case Rr_Delegatedmodel_RA_MSG_CMD_CODE:  /* RAA */
            numRAARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&Rr_DelegatedmodelStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!Rr_DelegatedmodelStats::sendTraffic &&
            (Rr_DelegatedmodelStats::numRqMsgsSent == Rr_DelegatedmodelStats::numRaMsgsRecv))
        {
            time(&Rr_DelegatedmodelStats::stopTime);
            ftime(&Rr_DelegatedmodelStats::recvComplete);
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
Rr_DelegatedmodelStats::PrintIndications(std::ostream& os) const
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
Rr_DelegatedmodelStats::Print(std::ostream& os) const
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

    os << "Num of UDR Sent                     "
       << numUDRSent << endl;

    os << "Num of UDA Sent                     "
       << numUDASent << endl;

    os << "Num of UDR Received                 "
       << numUDRRecv << endl;

    os << "Num of UDA Received                 "
       << numUDARecv << endl;
    os << endl;

    os << "Num of PNR Sent                     "
       << numPNRSent << endl;

    os << "Num of PNA Sent                     "
       << numPNASent << endl;

    os << "Num of PNR Received                 "
       << numPNRRecv << endl;

    os << "Num of PNA Received                 "
       << numPNARecv << endl;
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
operator<<(ostream& os, const Rr_DelegatedmodelStats& rr_delegatedmodelStats)
{
    rr_delegatedmodelStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    Rr_DelegatedmodelStats::duration = duration;
    Rr_DelegatedmodelStats::burstSize = burstSize;
    Rr_DelegatedmodelStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&Rr_DelegatedmodelStats::starter);
    time(&Rr_DelegatedmodelStats::startTime);

    Rr_DelegatedmodelStats::sendTraffic = ITS_TRUE;
    Rr_DelegatedmodelStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendRr_DelegatedmodelPushNotificationRequest;

}

void StopTraffic()
{
    Rr_DelegatedmodelStats::sendTraffic = ITS_FALSE;
    ftime(&Rr_DelegatedmodelStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->Print(oss);
}

void ResetStats()
{
    Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->CalcTPS(oss);
}

