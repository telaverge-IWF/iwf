/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: tx_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/12/19 08:54:50  kamakshilk
 * LOG: New architecture to work with static and distributed.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:08:56  kamakshilk
 * LOG: Merging with ITSDiameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:50:59  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: tx_defines.h,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: tx_defines.h,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $"

#ifndef _SAMPLE_TXAPP_DEFINE
#define _SAMPLE_TXAPP_DEFINE

#include <diameter/tx/AA.h>
#include <diameter/tx/AS.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::tx;

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define TX_INTERFACE_APP_ID    	 55557
#define VENDOR_ID    	 	 5535

/** 
 * The Application Worker Queue Id for Tx interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define TX_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For Tx Interface
 **/
#define TX_AA_MSG_CMD_CODE        265
#define TX_RA_MSG_CMD_CODE        258
#define TX_ST_MSG_CMD_CODE        275
#define TX_AS_MSG_CMD_CODE        274

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to display the menu options for the
 *      respective protocol interface.
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
 *      Returns the option selected.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int DisplayAppMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Tx Protocol messages to 
 *      the diameter stack. These will create the appropriate Tx protocol 
 *      Request Command objects, populate the AVPs and sends the 
 *      message to the stack.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendTxAARequest();
extern int SendTxRARequest();
extern int SendTxSTRequest();
extern int SendTxASRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Tx Protocol messages to 
 *      the diameter stack. These will create the appropriate Tx protocol 
 *      Answer Command objects, populate the AVPs and sends the 
 *      message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendTxAAAnswer(const diameter::CommandImpl *impl);
extern int SendTxRAAnswer(const diameter::CommandImpl *impl);
extern int SendTxSTAnswer(const diameter::CommandImpl *impl);
extern int SendTxASAnswer(const diameter::CommandImpl *impl);


/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to populate the Tx Protocol grouped AVPs. 
 *      These will populate the appropriate Tx protocol 
 *      grouped AVPs and returns the AVP objects. 
 *
 *  Input Parameters:
 *      : Reference to the grouped AVP object which needs to be populated.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern void PopulateMediaComponentDescription(MediaComponentDescription
                                                 &mediaCompDescrp);
extern void PopulateMediaSubComponent(MediaSubComponent &mediaSubComp);
extern void PopulateIPFilterRule(IPFilterRule &ipFltRule);
extern void PopulateFlows(Flows &flows);
extern void PopulateSubscriptionId(SubscriptionId &subscriptionId);
extern void PopulateAccessNetworkChargingIdentifier(
                AccessNetworkChargingIdentifier &accNwChargingId);


#endif

