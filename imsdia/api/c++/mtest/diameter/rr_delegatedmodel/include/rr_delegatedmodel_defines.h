/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: rr_delegatedmodel_defines.h,v $
 * LOG: Revision 1.1  2011/06/29 06:36:51  vkumara
 * LOG: Baseline for rr_delegatedmodel interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: rr_delegatedmodel_defines.h,v 1.1 2011/06/29 06:36:51 vkumara Exp $
 ****************************************************************************/
 #ident "$Id: rr_delegatedmodel_defines.h,v 1.1 2011/06/29 06:36:51 vkumara Exp $"


#ifndef _SAMPLE_Rr_DelegatedmodelAPP_DEFINE
#define _SAMPLE_Rr_DelegatedmodelAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID                            0
#define Rr_Delegatedmodel_INTERFACE_APP_ID    	         16777279
#define VENDOR_ID    	 	         		 13019

/**
 * The Application Worker Queue Id for Rr_Delegatedmodel interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define Rr_Delegatedmodel_APP_TQ_INST             1

/**
 * Standard CommandCode's defined by IANA
 * For Rr_Delegatedmodel Interface
 **/
#define Rr_Delegatedmodel_UD_MSG_CMD_CODE        306
#define Rr_Delegatedmodel_PN_MSG_CMD_CODE        309
#define Rr_Delegatedmodel_RA_MSG_CMD_CODE        258
#define Rr_Delegatedmodel_CC_MSG_CMD_CODE        272


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
 *      Utility functions to send the Rr_Delegatedmodel Protocol messages to
 *      the diameter stack. These will create the appropriate Rr_Delegatedmodel protocol
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
extern int SendRr_DelegatedmodelUserDataRequest();
extern int SendRr_DelegatedmodelPushNotificationRequest();
extern int SendRr_DelegatedmodelRARequest();
extern int SendRr_DelegatedmodelCCRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Rr_Delegatedmodel Protocol messages to
 *      the diameter stack. These will create the appropriate Rr_Delegatedmodel protocol
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
extern int SendRr_DelegatedmodelUserDataAnswer(const diameter::CommandImpl *impl);
extern int SendRr_DelegatedmodelPushNotificationAnswer(const diameter::CommandImpl *impl);
extern int SendRr_DelegatedmodelRAAnswer(const diameter::CommandImpl *impl);
extern int SendRr_DelegatedmodelCCAnswer(const diameter::CommandImpl *impl);


#endif
















