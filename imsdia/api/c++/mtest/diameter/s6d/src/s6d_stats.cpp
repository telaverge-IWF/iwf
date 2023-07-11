/**************************-*-Dia-*-*****************************************
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
 * LOG: $Log: s6d_stats.cpp,v $
 * LOG: Revision 1.1  2011/05/04 10:46:01  vkumara
 * LOG: Baseline for S6d interface.
 * LOG:
 * LOG:
 * ID: $Id: s6d_stats.cpp,v 1.1 2011/05/04 10:46:01 vkumara Exp $
 ***************************************************************************/


#include<dia_defines.h>
#include <app.h>

#include <s6d_stats.h>
#include <s6d_defines.h>

using namespace std;

its::ITS_Mutex S6DStats::guard(0);
ITS_BOOLEAN S6DStats::sendTraffic = ITS_FALSE;
ITS_BOOLEAN S6DStats::firstTime = ITS_FALSE;
time_t S6DStats::startTime;
time_t S6DStats::stopTime;
struct timeb S6DStats::sendComplete;
struct timeb S6DStats::recvComplete;
struct timeb S6DStats::starter;
struct timeb S6DStats::current;
int S6DStats::duration = 10;
int S6DStats::burstSize = 0;
int S6DStats::slpTime = 1000;

static S6DStats *s6dStats = NULL;

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
S6DStats::ResetAll()
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

    numRSRSent               = 0;
    numRSASent               = 0;
    numRSRRecv               = 0;
    numRSARecv               = 0;

    numNORSent               = 0;
    numNOASent               = 0;
    numNORRecv               = 0;
    numNOARecv               = 0;
 
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
 *      Returns the S6DStats object
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
S6DStats*
S6DStats::GetS6DStats()
{
    /* Acquire the semaphore before creating the object
    */
    ITS_ASSERT(S6DStats::guard.Acquire() == ITS_SUCCESS);

    /* If object does not exist, cteate one
    */
    if (s6dStats == NULL)
    {
        s6dStats = new S6DStats;
    }

    /* Release the semaphore
    */
    S6DStats::guard.Release();

    return s6dStats;
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
S6DStats::CalcTPS(std::ostrstream& oss)
{
    Print(oss);

    if (numRaMsgsRecv == numRqMsgsSent)
    {
         /* Calculate tps
         */
         if ((S6DStats::stopTime-S6DStats::startTime) > 0 )
         {
             tps = (numRaMsgsRecv)/(S6DStats::stopTime-S6DStats::startTime);
         }
         else
         {
             //tps = (numRaMsgsRecv);
             tps = (1000/S6DStats::slpTime) * S6DStats::burstSize;
         }

         /* Log the tps value
         */
         oss <<  "TPS                          " << tps << endl;
         cout << "TPS                          " << tps << endl;

         /*
          * Log the time taken for the reception of messages after sending
          */
         int st = S6DStats::recvComplete.time - S6DStats::sendComplete.time;
         int mt = S6DStats::recvComplete.millitm - S6DStats::sendComplete.millitm;

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
S6DStats::UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
{
    /* If message is request
    */
    if (isReq)
    {
        switch(commandCode)
        {

	case S6D_UL_MSG_CMD_CODE:  /* ULR */
	    numULRSent++;
	    break;
    
        case S6D_AI_MSG_CMD_CODE:  /* AIR */
            numAIRSent++;
            break;
        case S6D_CL_MSG_CMD_CODE:  /* CLR */
            numCLRSent++;
            break;
 
        case S6D_PU_MSG_CMD_CODE:  /* PUR */
            numPURSent++;
            break;
     
       case S6D_DS_MSG_CMD_CODE:  /* DSR */
            numDSRSent++;
            break;
 
       case S6D_ID_MSG_CMD_CODE:  /* IDR */
            numIDRSent++;
            break;       

       case S6D_RS_MSG_CMD_CODE:  /* RSR */
            numRSRSent++;
            break;

       case S6D_NO_MSG_CMD_CODE:  /* NOR */
            numNORSent++;
            break;

       case S6D_EC_MSG_CMD_CODE:  /* ECR */
            numECRSent++;
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
	case S6D_UL_MSG_CMD_CODE:  /* ULA */
            numULASent++;
            break;
  
 	case S6D_AI_MSG_CMD_CODE:  /* AIA */
            numAIASent++;
            break;

        case S6D_CL_MSG_CMD_CODE:  /* CLA */
            numCLASent++;
            break;
        
        case S6D_PU_MSG_CMD_CODE:  /* PUA */
            numPUASent++;
            break;
 
        case S6D_DS_MSG_CMD_CODE:  /* DSA */
            numDSASent++;
            break; 
       
        case S6D_ID_MSG_CMD_CODE:  /* IDA */
            numIDASent++;
            break;  

        case S6D_RS_MSG_CMD_CODE:  /* RSA */
            numRSASent++;
            break;

        case S6D_NO_MSG_CMD_CODE:  /* NOA */
            numNOASent++;
            break;

        case S6D_EC_MSG_CMD_CODE:  /* ECA */
            numECASent++;
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
S6DStats::UpdateRecvIndications(ITS_UINT indic)
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
S6DStats::UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq)
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
	case S6D_UL_MSG_CMD_CODE:  /* ULR */
            numULRRecv++;
            break;
       
       case S6D_AI_MSG_CMD_CODE:  /* AIR */
            numAIRRecv++;
            break;

       case S6D_CL_MSG_CMD_CODE:  /* CLR */
            numCLRRecv++;
            break;
        
       case S6D_PU_MSG_CMD_CODE:  /* PUR */
            numPURRecv++;
            break;
 
       case S6D_DS_MSG_CMD_CODE:  /* DSR */
            numDSRRecv++;
            break; 

       case S6D_ID_MSG_CMD_CODE:  /* IDR */
            numIDRRecv++;
            break;

       case S6D_RS_MSG_CMD_CODE:  /* RSR */
            numRSRRecv++;
            break;

       case S6D_NO_MSG_CMD_CODE:  /* NOR */
            numNORRecv++;
            break;

       case S6D_EC_MSG_CMD_CODE:  /* ECR */
            numECRRecv++;
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
	case S6D_UL_MSG_CMD_CODE:  /* ULA */
            numULARecv++;
            break;
	case S6D_AI_MSG_CMD_CODE:  /* AIA*/
            numAIARecv++;
            break;
        case S6D_CL_MSG_CMD_CODE:  /* CLA*/
            numCLARecv++;
            break;
 
        case S6D_PU_MSG_CMD_CODE:  /* PUA */
            numPUARecv++;
            break;
 
        case S6D_DS_MSG_CMD_CODE:  /* DSA */
            numDSARecv++;
            break;
       
        case S6D_ID_MSG_CMD_CODE:  /* IDA */
            numIDARecv++;
            break;  

        case S6D_RS_MSG_CMD_CODE:  /* RSA */
            numRSARecv++;
            break;

        case S6D_NO_MSG_CMD_CODE:  /* NOA */
            numNOARecv++;
            break;

        case S6D_EC_MSG_CMD_CODE:  /* ECA */
            numECARecv++;
            break;

        default:
            break;
        }
        numRaMsgsRecv++;

        /*Update the start time details in stats
        */
        if (numRaMsgsRecv == 1)
        {
            time(&S6DStats::startTime);
        }

        /*Update the stop time details in stats
        */
        if (!S6DStats::sendTraffic &&
            (S6DStats::numRqMsgsSent == S6DStats::numRaMsgsRecv))
        {
            time(&S6DStats::stopTime);
            ftime(&S6DStats::recvComplete);
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
S6DStats::PrintIndications(std::ostream& os) const
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
S6DStats::Print(std::ostream& os) const
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


    os << "Num of RSR Sent                     "
           << numRSRSent << endl;

    os << "Num of RSA Sent                     "
           << numRSASent << endl;

    os << "Num of RSR Received                 "
           << numRSRRecv << endl;

    os << "Num of RSA Received                 "
           << numRSARecv << endl;
    os << endl;

    os << "Num of NOR Sent                     "
           << numNORSent << endl;

    os << "Num of NOA Sent                     "
           << numNOASent << endl;

    os << "Num of NOR Received                 "
           << numNORRecv << endl;

    os << "Num of NOA Received                 "
           << numNOARecv << endl;
    os << endl;

    os << "Num of ECR Sent                     "
           << numECRSent << endl;

    os << "Num of ECA Sent                     "
           << numECASent << endl;

    os << "Num of ECR Received                 "
           << numECRRecv << endl;

    os << "Num of ECA Received                 "
           << numECARecv << endl;
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
operator<<(ostream& os, const S6DStats& s6dStats)
{
    s6dStats.Print(os);
    return os;
}

void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime)
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    S6DStats::GetS6DStats()->ResetAll();

    /*
     * Set the duration, burst size and the sleep time
     */
    S6DStats::duration = duration;
    S6DStats::burstSize = burstSize;
    S6DStats::slpTime = slpTime;

    /*
     * Store the start time
     */
    ftime(&S6DStats::starter);
    time(&S6DStats::startTime);

    S6DStats::sendTraffic = ITS_TRUE;
    S6DStats::firstTime = ITS_TRUE;
    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    oss <<"Test Started at ----->" << buff << endl;

    /*
     * Set the traffic generator function
     */
    TrafficGeneratorFunc = SendS6DUpdateLocationRequest;

}

void StopTraffic()
{
    S6DStats::sendTraffic = ITS_FALSE;
    ftime(&S6DStats::sendComplete);
}

void PrintStats(std::ostream& oss)
{
    S6DStats::GetS6DStats()->Print(oss);
}

void ResetStats()
{
    S6DStats::GetS6DStats()->ResetAll();
}

void UpdateIndications(ITS_UINT indType)
{
    S6DStats::GetS6DStats()->UpdateRecvIndications(indType);
}

void CalculateTPS(std::ostrstream& oss)
{
    S6DStats::GetS6DStats()->CalcTPS(oss);
}

