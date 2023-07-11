/**************************-*-Dia-*-*****************************************
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
 * LOG: $Log: s6a_stats.cpp,v $
 * LOG: Revision 1.2  2008/11/12 05:52:01  sureshj
 * LOG: stats for new commands added. part of 3.1.1 release.
 * LOG:
 * LOG: Revision 1.1  2008/08/19 06:58:33  sureshj
 * LOG: Baseline demo application for s6a interface.
 * LOG:
 * ID: $Id: s6a_stats.cpp,v 1.2 2008/11/12 05:52:01 sureshj Exp $
 ***************************************************************************/


#include<dia_defines.h>
#include <app.h>

#include <s6a_stats.h>
#include <s6a_defines.h>

using namespace std;

its::ITS_Mutex S6AStats::guard(0);
ITS_BOOLEAN S6AStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN S6AStats::firstTime = ITS_FALSE;
time_t S6AStats::startTime;
time_t S6AStats::stopTime;
struct timeb S6AStats::sendComplete;
struct timeb S6AStats::recvComplete;
struct timeb S6AStats::starter;
struct timeb S6AStats::current;
int S6AStats::duration = 10;
int S6AStats::burstSize = 0;
int S6AStats::slpTime = 1000;

static S6AStats *s6aStats = NULL;

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
S6AStats::ResetAll()
{
    Lock();

    numRqMsgsSent            = 0;
    numRaMsgsSent            = 0;
    numRqMsgsRecv            = 0;
    numRaMsgsRecv            = 0;

    numULRSent               = 0;
    numULASent               = 0;
    numULRRecv               = 0;
    numULARecv               = 0;

    numAIRSent               = 0;
    numAIASent               = 0;
    numAIRRecv               = 0;
    numAIARecv               = 0;

    numCLRSent               = 0;
    numCLASent               = 0;
    numCLRRecv               = 0;
    numCLARecv               = 0;
    
    numIDRSent               = 0;
    numIDASent               = 0;
    numIDRRecv               = 0;
    numIDARecv               = 0;  
  
    numPURSent               = 0;
    numPUASent               = 0;
    numPURRecv               = 0;
    numPUARecv               = 0;

    numDSRSent               = 0;
    numDSASent               = 0;
    numDSRRecv               = 0;
    numDSARecv               = 0;
 
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
 *      Returns the S6AStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
S6AStats*
S6AStats::GetS6AStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(S6AStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (s6aStats == NULL)
    {
        s6aStats = new S6AStats;
    }

    /* Release the semaphore
    */
    S6AStats::guard.Release();

    return s6aStats;
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
S6AStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((S6AStats::stopTime-S6AStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(S6AStats::stopTime-S6AStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/S6AStats::slpTime) * S6AStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = S6AStats::recvComplete.time - S6AStats::sendComplete.time;
         int mt = S6AStats::recvComplete.millitm - S6AStats::sendComplete.millitm;

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
S6AStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {

	case S6A_UL_MSG_CMD_CODE:  /* ULR */
	    numULRSent++;
	    break;
    
        case S6A_AI_MSG_CMD_CODE:  /* AIR */
            numAIRSent++;
            break;
        case S6A_CL_MSG_CMD_CODE:  /* CLR */
            numCLRSent++;
            break;
 
        case S6A_PU_MSG_CMD_CODE:  /* PUR */
            numPURSent++;
            break;
     
       case S6A_DS_MSG_CMD_CODE:  /* DSR */
            numDSRSent++;
            break;
 
       case S6A_ID_MSG_CMD_CODE:  /* IDR */
            numIDRSent++;
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
	case S6A_UL_MSG_CMD_CODE:  /* ULA */
            numULASent++;
            break;
  
 	case S6A_AI_MSG_CMD_CODE:  /* AIA */
            numAIASent++;
            break;

        case S6A_CL_MSG_CMD_CODE:  /* CLA */
            numCLASent++;
            break;
        
        case S6A_PU_MSG_CMD_CODE:  /* PUA */
            numPUASent++;
            break;
 
        case S6A_DS_MSG_CMD_CODE:  /* DSA */
            numDSASent++;
            break; 
       
        case S6A_ID_MSG_CMD_CODE:  /* IDA */
            numIDASent++;
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
S6AStats::UpdateRecvIndications(ITS_UINT indic)
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
S6AStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
	case S6A_UL_MSG_CMD_CODE:  /* ULR */
            numULRRecv++;
            break;
       
       case S6A_AI_MSG_CMD_CODE:  /* AIR */
            numAIRRecv++;
            break;

       case S6A_CL_MSG_CMD_CODE:  /* CLR */
            numCLRRecv++;
            break;
        
       case S6A_PU_MSG_CMD_CODE:  /* PUR */
            numPURRecv++;
            break;
 
       case S6A_DS_MSG_CMD_CODE:  /* DSR */
            numDSRRecv++;
            break; 

       case S6A_ID_MSG_CMD_CODE:  /* IDR */
            numIDRRecv++;
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
	case S6A_UL_MSG_CMD_CODE:  /* ULA */
            numULARecv++;
            break;
	case S6A_AI_MSG_CMD_CODE:  /* AIA*/
            numAIARecv++;
            break;
        case S6A_CL_MSG_CMD_CODE:  /* CLA*/
            numCLARecv++;
            break;
 
        case S6A_PU_MSG_CMD_CODE:  /* PUA */
            numPUARecv++;
            break;
 
        case S6A_DS_MSG_CMD_CODE:  /* DSA */
            numDSARecv++;
            break;
       
        case S6A_ID_MSG_CMD_CODE:  /* IDA */
            numIDARecv++;
            break;  

        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&S6AStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!S6AStats::sendTraffic &&
            (S6AStats::numRqMsgsSent == S6AStats::numRaMsgsRecv))
        {
            time(&S6AStats::stopTime);
            ftime(&S6AStats::recvComplete);
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
S6AStats::PrintIndications(std::ostream& os) const
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
S6AStats::Print(std::ostream& os) const
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

    os << "Num of ULR Sent                     "
	   << numULRSent << endl;

    os << "Num of ULA Sent                     "
	   << numULASent << endl;

    os << "Num of ULR Received                 "
	   << numULRRecv << endl;

    os << "Num of ULA Received                 "
	   << numULARecv << endl;
    os << endl;

    os << "Num of AIR Sent                     "
           << numAIRSent << endl;

    os << "Num of AIA Sent                     "
           << numAIASent << endl;

    os << "Num of AIR Received                 "
           << numAIRRecv << endl;

    os << "Num of AIA Received                 "
           << numAIARecv << endl;
    os << endl;

    os << "Num of CLR Sent                     "
           << numCLRSent << endl;

    os << "Num of CLA Sent                     "
           << numCLASent << endl;

    os << "Num of CLR Received                 "
           << numCLRRecv << endl;

    os << "Num of CLA Received                 "
           << numCLARecv << endl;
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
    
    os << "Num of DSR Sent                     "
           << numDSRSent << endl;
 
    os << "Num of DSA Sent                     "
           << numDSASent << endl;
 
    os << "Num of DSR Received                 "
           << numDSRRecv << endl;
 
    os << "Num of DSA Received                 "
           << numDSARecv << endl;
    os << endl;
  
    os << "Num of IDR Sent                     "
           << numIDRSent << endl;
    
    os << "Num of IDA Sent                     "
           << numIDASent << endl;
 
    os << "Num of DSR Received                 "
           << numIDRRecv << endl;
 
    os << "Num of DSA Received                 "
           << numIDARecv << endl;
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
operator<<(ostream& os, const S6AStats& s6aStats)
{
    s6aStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    S6AStats::GetS6AStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    S6AStats::duration = duration;
    S6AStats::burstSize = burstSize;
    S6AStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&S6AStats::starter);
    time(&S6AStats::startTime);

    S6AStats::sendTraffic = ITS_TRUE;
    S6AStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendS6AUpdateLocationRequest;

}

void StopTraffic()
{
    S6AStats::sendTraffic = ITS_FALSE;
    ftime(&S6AStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    S6AStats::GetS6AStats()->Print(oss);
}

void ResetStats()
{
    S6AStats::GetS6AStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    S6AStats::GetS6AStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    S6AStats::GetS6AStats()->CalcTPS(oss);
}

