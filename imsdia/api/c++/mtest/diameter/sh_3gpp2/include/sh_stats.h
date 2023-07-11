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
 *
 * LOG: $Log: sh_stats.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:48:46  kamakshilk
 * LOG: Sh 3GPP2 interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sh_stats.h,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
 #ident "$Id: sh_stats.h,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $"


#if !defined(_SH_3GPP2APP_STATS_H_)
#define _SH_3GPP2APP_STATS_H_

#include <strstream>
#include <sys/timeb.h>
#include <dia_stats.h>

class ShStats: public DiaStats
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
     *      Returns the ShStats object pointer.
     *      NULL in case of Failure.
     *
     *  Notes:
     *
     *  See Also:
     *************************************************************************/
     static ShStats* GetShStats();

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
     ~ShStats(){};

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
     ITS_UINT numUDRSent;        /*Number of UD Request sent*/
     ITS_UINT numUDASent;        /*Number of UD Answer sent*/
     ITS_UINT numUDRRecv;        /*Number of UD Request received*/
     ITS_UINT numUDARecv;        /*Number of UD Answer received*/

     ITS_UINT numPURSent;        /*Number of PU Request sent*/
     ITS_UINT numPUASent;        /*Number of PU Answer sent*/
     ITS_UINT numPURRecv;        /*Number of PU Request received*/
     ITS_UINT numPUARecv;        /*Number of PU Answer received*/

     ITS_UINT numSNRSent;        /*Number of SN Request sent*/
     ITS_UINT numSNASent;        /*Number of SN Answer sent*/
     ITS_UINT numSNRRecv;        /*Number of SN Request received*/
     ITS_UINT numSNARecv;        /*Number of SN Answer received*/

     ITS_UINT numPNRSent;        /*Number of PN Request sent*/
     ITS_UINT numPNASent;        /*Number of PN Answer sent*/
     ITS_UINT numPNRRecv;        /*Number of PN Request received*/
     ITS_UINT numPNARecv;        /*Number of PN Answer received*/

     /* Total Number of Messages Sent/Received
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
     ShStats()
         : DiaStats(),
           numRqMsgsSent(0),
           numRaMsgsSent(0),
           numRqMsgsRecv(0),
           numRaMsgsRecv(0),
           numUDRSent(0),
           numUDRRecv(0),
           numUDASent(0),
           numUDARecv(0),
           numPURSent(0),
           numPURRecv(0),
           numPUASent(0),
           numPUARecv(0),
           numSNRSent(0),
           numSNRRecv(0),
           numSNASent(0),
           numSNARecv(0),
           numPNRSent(0),
           numPNRRecv(0),
           numPNASent(0),
           numPNARecv(0),
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
     ShStats(const ShStats&);

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
     ShStats&
     operator=(const ShStats&);
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
std::ostream& operator<< (std::ostream& os, const ShStats& shStats);

#endif

