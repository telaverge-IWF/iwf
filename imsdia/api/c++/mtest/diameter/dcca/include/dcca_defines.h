/*********************************-*-C-*-************************************
/*                                                                          *
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
 * LOG: $Log: dcca_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/11/24 20:15:00  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:50:27  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/27 09:34:12  hbhatnagar
 * LOG: Fix for Bug ID: 4383 and cleaning (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:50:59  kamakshilk
 * LOG: Baseline demo application for Dcca Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: dcca_defines.h,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $
 ****************************************************************************/
#ifndef _SAMPLE_DCCAAPP_DEFINE
#define _SAMPLE_DCCAAPP_DEFINE


#define ERROR  -1

#define  MAX_SESS_MAP 64

typedef struct _SESSION_MAP
{
	ITS_UINT valid;
	ITS_UINT index;
	string sessionid;
	ITS_UINT snum;	
	DiaMsg *dMsg1;
} SESSION_MAP;


/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define DCCA_INTERFACE_APP_ID    4
#define VENDOR_ID    	 	 5535

/** 
 * The Application Worker Queue Id for Dcca interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define DCCA_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For Dcca Interface
 **/
#define DCCA_CC_MSG_CMD_CODE	272
#define BASE_ST_MSG_CMD_CODE	275
#define BASE_AS_MSG_CMD_CODE    274



/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Application Interface Specific Thread Functions
 *      This demo simulates below Application specific workers
 *      1. Worker that processes Dcca Protocol Messages
 *      The following are the individual thread functions.
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
extern "C"
void DccaThreadFunc(its::ThreadPoolThread* thr, void* arg);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sender Thread Function
 *
 *  Input Parameters:
 *      thr - type ThreadPoolThread. arg - type void..
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

extern "C"
void DccaSendThreadFunc(its::ThreadPoolThread* thr, void* arg);

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
extern int DisplayDccaMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the command to the diameter
 *      stack based on the option selected in the menu.
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
 *      SendToStack()
 ****************************************************************************/
extern int SendDccaMessage(int input, int);

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Dcca Protocol messages to 
 *      the diameter stack. These will create the appropriate Dcca protocol 
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
extern int SendSessionTerminationRequest( string sesId, int);
extern int SendAbortSessionRequest(string sesId, ITS_UINT index );



/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Dcca Protocol messages to 
 *      the diameter stack. These will create the appropriate Dcca protocol 
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
extern int HandleDccaDiaMessage(its::ITS_Event&);
extern int SendSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

