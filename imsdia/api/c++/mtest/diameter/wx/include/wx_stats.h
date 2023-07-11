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
 *  ID: $Id: wx_stats.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 *
 *  LOG: $Log: wx_stats.h,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/08/04 17:46:39  nvijikumar
 *  LOG: Changes to update the stats for all messages.
 *  LOG:
 *  LOG: Revision 1.1  2006/07/24 15:41:47  nvijikumar
 *  LOG: Baseline commit for Wx Interface demo application.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: wx_stats.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $"

#if !defined(_WXAPP_STATS_H_)
#define _WXAPP_STATS_H_

#include <strstream>
#include <sys/timeb.h>
#include <dia_stats.h>

class WxStats: public DiaStats
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
     *      Returns the WxStats object pointer.
     *      NULL in case of Failure.
     *
     *  Notes:
     *
     *  See Also:
     *************************************************************************/
     static WxStats* GetWxStats();

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
     ~WxStats(){};

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
     ITS_UINT numMARSent;        /*Number of MA Request sent*/
     ITS_UINT numMAASent;        /*Number of MA Answer sent*/
     ITS_UINT numMARRecv;        /*Number of MA Request received*/
     ITS_UINT numMAARecv;        /*Number of MA Answer received*/

     ITS_UINT numRTRSent;        /*Number of RT Request sent*/
     ITS_UINT numRTASent;        /*Number of RT Answer sent*/
     ITS_UINT numRTRRecv;        /*Number of RT Request received*/
     ITS_UINT numRTARecv;        /*Number of RT Answer received*/

     ITS_UINT numPPRSent;        /*Number of PP Request sent*/
     ITS_UINT numPPASent;        /*Number of PP Answer sent*/
     ITS_UINT numPPRRecv;        /*Number of PP Request received*/
     ITS_UINT numPPARecv;        /*Number of PP Answer received*/

     ITS_UINT numSARSent;        /*Number of SA Request sent*/
     ITS_UINT numSAASent;        /*Number of SA Answer sent*/
     ITS_UINT numSARRecv;        /*Number of SA Request received*/
     ITS_UINT numSAARecv;        /*Number of SA Answer received*/

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
     WxStats()
         : DiaStats(),
           numRqMsgsSent(0),
           numRaMsgsSent(0),
           numRqMsgsRecv(0),
           numRaMsgsRecv(0),
           numMARSent(0),
           numMARRecv(0),
           numMAASent(0),
           numMAARecv(0),
           numPPRSent(0),
           numPPRRecv(0),
           numPPASent(0),
           numPPARecv(0),
           numRTRSent(0),
           numRTRRecv(0),
           numRTASent(0),
           numRTARecv(0),
           numSARSent(0),
           numSARRecv(0),
           numSAASent(0),
           numSAARecv(0),
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
     WxStats(const WxStats&);

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
     WxStats&
     operator=(const WxStats&);
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
std::ostream& operator<< (std::ostream& os, const WxStats& wxStats);

#endif

