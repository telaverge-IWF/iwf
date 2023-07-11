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
 * LOG: $Log: sh_stats.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:48:46  kamakshilk
 * LOG: Sh 3GPP2 interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sh_stats.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sh_stats.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $"

#include <dia_defines.h>
#include <app.h>

#include <sh_stats.h>
#include <sh_defines.h>

using namespace std;

its::ITS_Mutex ShStats::guard(0);
ITS_BOOLEAN ShStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN ShStats::firstTime = ITS_FALSE;
time_t ShStats::startTime;
time_t ShStats::stopTime;
struct timeb ShStats::sendComplete;
struct timeb ShStats::recvComplete;
struct timeb ShStats::starter;
struct timeb ShStats::current;
int ShStats::duration = 10;
int ShStats::burstSize = 0;
int ShStats::slpTime = 1000;

static ShStats *shStats = NULL;

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
ShStats::ResetAll()
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

    numPURSent               = 0;
    numPURRecv               = 0;
    numPUASent               = 0;
    numPUARecv               = 0;

    numSNRSent               = 0;
    numSNRRecv               = 0;
    numSNASent               = 0;
    numSNARecv               = 0;

    numPNRSent               = 0;
    numPNRRecv               = 0;
    numPNASent               = 0;
    numPNARecv               = 0;

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
 *      Returns the ShStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ShStats*
ShStats::GetShStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(ShStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (shStats == NULL)
    {
        shStats = new ShStats;
    }

    /* Release the semaphore
    */
    ShStats::guard.Release();

    return shStats;
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
ShStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((ShStats::stopTime-ShStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(ShStats::stopTime-ShStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/ShStats::slpTime) * ShStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = ShStats::recvComplete.time - ShStats::sendComplete.time;
         int mt = ShStats::recvComplete.millitm - ShStats::sendComplete.millitm;

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
ShStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {
        case SH_UD_MSG_CMD_CODE:  /* UDR */
            numUDRSent++;
            break;
        case SH_PU_MSG_CMD_CODE:  /* PUR */
            numPURSent++;
            break;
        case SH_SN_MSG_CMD_CODE:  /* SNR */
            numSNRSent++;
            break;
        case SH_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRSent++;
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
        case SH_UD_MSG_CMD_CODE:  /* UDA */
            numUDASent++;
            break;
        case SH_PU_MSG_CMD_CODE:  /*PUAns */
            numPUASent++;
            break;
        case SH_SN_MSG_CMD_CODE:  /*SNAns */
            numSNASent++;
            break;
        case SH_PN_MSG_CMD_CODE:  /*PNAns */
            numPNASent++;
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
ShStats::UpdateRecvIndications(ITS_UINT indic)
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
ShStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
        case SH_UD_MSG_CMD_CODE:  /* UDR */
            numUDRRecv++;
            break;
        case SH_PU_MSG_CMD_CODE:  /*PUReq */
            numPURRecv++;
            break;
        case SH_SN_MSG_CMD_CODE:  /*SNReq */
            numSNRRecv++;
            break;
        case SH_PN_MSG_CMD_CODE:  /*PNReq */
            numPNRRecv++;
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
        case SH_UD_MSG_CMD_CODE:  /* UDA */
            numUDARecv++;
            break;
        case SH_PU_MSG_CMD_CODE:  /*PUAns */
            numPUARecv++;
            break;
        case SH_SN_MSG_CMD_CODE:  /* SNA */
            numSNARecv++;
            break;
        case SH_PN_MSG_CMD_CODE:  /* PNA */
            numPNARecv++;
            break;
        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&ShStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!ShStats::sendTraffic &&
            (ShStats::numRqMsgsSent == ShStats::numRaMsgsRecv))
        {
            time(&ShStats::stopTime);
            ftime(&ShStats::recvComplete);
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
ShStats::PrintIndications(std::ostream& os) const
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
ShStats::Print(std::ostream& os) const
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

    os << "Num of PUR Sent                     "
       << numPURSent << endl;

    os << "Num of PUA Sent                     "
       << numPUASent << endl;

    os << "Num of PUR Received                 "
       << numPURRecv << endl;

    os << "Num of PUA Received                 "
       << numPUARecv << endl;
    os << endl;

    os << "Num of SNR Sent                     "
       << numSNRSent << endl;

    os << "Num of SNA Sent                     "
       << numSNASent << endl;

    os << "Num of SNR Received                 "
       << numSNRRecv << endl;

    os << "Num of SNA Received                 "
       << numSNARecv << endl;
    os << endl;

    os << "Num of PNR Sent                     "
       << numPNRSent << endl;

    os << "Num of PNA Sent                     "
       << numPNASent << endl;

    os << "Num of PNR Received                 "
       << numPNRRecv << endl;

    os << "Num of PNA Received                 "
       << numPNARecv << endl;

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
operator<<(ostream& os, const ShStats& shStats)
{
    shStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    ShStats::GetShStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    ShStats::duration = duration;
    ShStats::burstSize = burstSize;
    ShStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&ShStats::starter);
    time(&ShStats::startTime);

    ShStats::sendTraffic = ITS_TRUE;
    ShStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendShProfileUpdateRequest;

}

void StopTraffic()
{
    ShStats::sendTraffic = ITS_FALSE;
    ftime(&ShStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    ShStats::GetShStats()->Print(oss);
}

void ResetStats()
{
    ShStats::GetShStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    ShStats::GetShStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    ShStats::GetShStats()->CalcTPS(oss);
}

