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
 * LOG: $Log: s6d_stats.h,v $
 * LOG: Revision 1.1  2011/05/04 10:46:01  vkumara
 * LOG: Baseline for S6d interface.
 * LOG:
 * LOG:
 * ID: $Id: s6d_stats.h,v 1.1 2011/05/04 10:46:01 vkumara Exp $
 ****************************************************************************/

#if !defined(_S6DAPP_STATS_H_)
#define _S6DAPP_STATS_H_

#include <strstream>
#include <sys/timeb.h>
#include <dia_stats.h>

class S6DStats: public DiaStats
{
public:
    /*  implementation: public
     *************************************************************************
     *  Purpose: Static Function to Get the Singleton Class Pointer.
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
     *      Returns the S6DStats object pointer.
     *      NULL in case of Failure.
     *
     *  Notes:
     *
     *  See Also:
     *************************************************************************/
     static S6DStats* GetS6DStats();

    /*  implementation: public
     *************************************************************************
     *  Purpose: Destructor
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
     ************************************************************************/
     ~S6DStats(){};

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
     **************************************************************************/
     void Print(std::ostream& os) const;

    /*  implementation: public
     ***************************************************************************
     *  Purpose: This function prints the various indications received from the
     *      Base Diameter stack to the output stream.
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
     void PrintIndications(std::ostream& os) const;

    /*  implementation: public
     ***************************************************************************
     *  Purpose: Utility function to reset the statistics data.
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
     void ResetAll();

    /*  implementation: public
     *************************************************************************
     *  Purpose:
     *      Utility function that calculates the TPS (Transactions Per Second)
     *      Transaction : 1 Request -- 1 Answer
     *      TPS: Is calculated based on No. of Answer's received/second
     *      This accounts for network latency.
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
     *************************************************************************/
     void CalcTPS(std::ostrstream& oss);

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
     void UpdateSendStats(ITS_UINT commandCode, ITS_BOOLEAN isReq);

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
     void UpdateRecvStats(ITS_UINT commandCode, ITS_BOOLEAN isReq);

    /*  implementation: public
     *************************************************************************
     *  Purpose: Utility function to update the indications received
     *      from the diameter stack.
     *
     *  Input Parameters:
     *      ITS_UINT indic: Indication Received from the Stack.
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
     ************************************************************************/
     void UpdateRecvIndications(ITS_UINT indic);

     /* Performance Related */
     static ITS_BOOLEAN sendTraffic;
     static ITS_BOOLEAN firstTime;
     static time_t startTime;
     static time_t stopTime;
     static struct timeb sendComplete;
     static struct timeb recvComplete;
     static struct timeb starter;
     static struct timeb current;
     static int duration;
     static int burstSize;
     static int slpTime;
     /* End Performance Related */

private:
     static its::ITS_Mutex guard;

     /* Message Specific Counters
     */

     ITS_UINT numULRSent;        /*Number of UA Request sent*/
     ITS_UINT numULASent;        /*Number of UA Answer sent*/
     ITS_UINT numULRRecv;        /*Number of UA Request received*/
     ITS_UINT numULARecv;        /*Number of UA Answer received*/

     ITS_UINT numAIRSent;        /*Number of AI Request sent*/
     ITS_UINT numAIASent;        /*Number of AI Answer sent*/
     ITS_UINT numAIRRecv;        /*Number of AI Request received*/
     ITS_UINT numAIARecv;        /*Number of AI Answer received*/


     ITS_UINT numCLRSent;        /*Number of CL Request sent*/
     ITS_UINT numCLASent;        /*Number of CL Answer sent*/
     ITS_UINT numCLRRecv;        /*Number of CL Request received*/
     ITS_UINT numCLARecv;        /*Number of CL Answer received*/

     ITS_UINT numIDRSent;        /*Number of ID Request sent*/
     ITS_UINT numIDASent;        /*Number of ID Answer sent*/
     ITS_UINT numIDRRecv;        /*Number of ID Request received*/
     ITS_UINT numIDARecv;        /*Number of ID Answer received*/
  
     ITS_UINT numPURSent;        /*Number of PU Request sent*/
     ITS_UINT numPUASent;        /*Number of PU Answer sent*/
     ITS_UINT numPURRecv;        /*Number of PU Request received*/
     ITS_UINT numPUARecv;        /*Number of PU Answer received*/

     ITS_UINT numDSRSent;        /*Number of DS Request sent*/
     ITS_UINT numDSASent;        /*Number of DS Answer sent*/
     ITS_UINT numDSRRecv;        /*Number of DS Request received*/
     ITS_UINT numDSARecv;        /*Number of DS Answer received*/

     ITS_UINT numRSRSent;        /*Number of RS Request sent*/
     ITS_UINT numRSASent;        /*Number of RS Answer sent*/
     ITS_UINT numRSRRecv;        /*Number of RS Request received*/
     ITS_UINT numRSARecv;        /*Number of RS Answer received*/

     ITS_UINT numNORSent;        /*Number of NO Request sent*/
     ITS_UINT numNOASent;        /*Number of NO Answer sent*/
     ITS_UINT numNORRecv;        /*Number of NO Request received*/
     ITS_UINT numNOARecv;        /*Number of NO Answer received*/

     ITS_UINT numECRSent;        /*Number of EC Request sent*/
     ITS_UINT numECASent;        /*Number of EC Answer sent*/
     ITS_UINT numECRRecv;        /*Number of EC Request received*/
     ITS_UINT numECARecv;        /*Number of EC Answer received*/

     /* 
      * Total Number of Messages Sent/Received
      */
     ITS_UINT numRqMsgsSent;     /*Total number of request message sent*/
     ITS_UINT numRaMsgsSent;     /*Total number of answer message sent*/
     ITS_UINT numRqMsgsRecv;     /*Total number of request message received*/
     ITS_UINT numRaMsgsRecv;     /*Total number of answer message received*/

     ITS_UINT tps;               /*Total packets per second*/

     /* Indications Received from Stack
     */
     ITS_UINT numDisconnectIndic;      /*Number of Disconnect Indication*/
     ITS_UINT numTimeoutIndic;         /*Number of Timeout Indication*/
     ITS_UINT numAuthLifeTimeoutIndic; /*Number of Lifetime Timeout Indication*/
     ITS_UINT numAuthGraceTimeoutIndic;/*Number of Grace Timeout Indication*/
     ITS_UINT numAbortIndic;           /*Number of Abort Indication*/
     ITS_UINT numCorruptMsgIndic;      /*Number of Corrupt message Indication*/
     ITS_UINT numUnknownIndic;         /*Number of Unknown Indication*/

    /*  implementation: private
     *************************************************************************
     *  Purpose: Constructor
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
     ************************************************************************/
     S6DStats()
         : DiaStats(),
           numRqMsgsSent(0),
           numRaMsgsSent(0),
           numRqMsgsRecv(0),
           numRaMsgsRecv(0),
           numULRSent(0),
	   numULASent(0),
	   numULRRecv(0),
           numULARecv(0),
           numAIRSent(0),
           numAIASent(0),
           numAIRRecv(0),
           numAIARecv(0),
           numCLRSent(0),
           numCLASent(0),
           numCLRRecv(0),
           numCLARecv(0),
           numPURSent(0),
           numPUASent(0),
           numPURRecv(0),
           numPUARecv(0),
           numDSRSent(0),
           numDSASent(0),
           numDSRRecv(0),
           numDSARecv(0),
           numIDRSent(0),
           numIDASent(0),
           numIDRRecv(0),
           numIDARecv(0), 
           numRSRSent(0),
           numRSASent(0),
           numRSRRecv(0),
           numRSARecv(0),
           numNORSent(0),
           numNOASent(0),
           numNORRecv(0),
           numNOARecv(0),
           numECRSent(0),
           numECASent(0),
           numECRRecv(0),
           numECARecv(0),
          
           numDisconnectIndic(0),
           numTimeoutIndic(0),
           numAuthLifeTimeoutIndic(0),
           numAuthGraceTimeoutIndic(0),
           numAbortIndic(0),
           numCorruptMsgIndic(0),
           numUnknownIndic(0)
     {};

    /*  implementation: private
     *************************************************************************
     *  Purpose: Copy constructor
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
     ************************************************************************/
     S6DStats(const S6DStats&);

    /*  implementation: private
     *************************************************************************
     *  Purpose: Overloaded assignment operator
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
     ************************************************************************/
     S6DStats&
     operator=(const S6DStats&);
};

/*  implementation: public
 *************************************************************************
 *  Purpose: Overloaded << operator
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
 ************************************************************************/
std::ostream& operator<< (std::ostream& os, const S6DStats& s6dStats);

#endif

