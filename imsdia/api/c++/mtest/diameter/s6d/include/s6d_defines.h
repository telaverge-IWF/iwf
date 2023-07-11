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
 ****************************************************************************
 * LOG: $Log: s6d_defines.h,v $
 * LOG: Revision 1.1  2011/05/04 10:46:01  vkumara
 * LOG: Baseline for S6d interface.
 * LOG:
 * LOG:
 * ID: $Id: s6d_defines.h,v 1.1 2011/05/04 10:46:01 vkumara Exp $
 ****************************************************************************/

#ifndef _SAMPLE_S6DAPP_DEFINE
#define _SAMPLE_S6DAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define S6D_INTERFACE_APP_ID   	         16777251
#define S6D_ECR_ECA_INTERFACE_APP_ID   	 16777252
#define VENDOR_ID    	 	         10415

/**
 * The Application Worker Queue Id for S6D interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define S6D_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For S6D Interface
 **/
#define S6D_UL_MSG_CMD_CODE        316 
#define S6D_CL_MSG_CMD_CODE        317
#define S6D_PU_MSG_CMD_CODE        321
#define S6D_ID_MSG_CMD_CODE        319
#define S6D_DS_MSG_CMD_CODE        320
#define S6D_AI_MSG_CMD_CODE        318
#define S6D_RS_MSG_CMD_CODE        322
#define S6D_NO_MSG_CMD_CODE        323
#define S6D_EC_MSG_CMD_CODE        324


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
 *      Utility functions to send the S6D Protocol messages to
 *      the diameter stack. These will create the appropriate S6D protocol
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
extern int SendS6DUpdateLocationRequest();

extern int SendS6DAuthenticationInformationRequest();

extern int SendS6DCancelLocationRequest();

extern int SendS6DPurgeUERequest();

extern int SendS6DDeleteSubDataRequest();

extern int SendS6DInsertSubDataRequest();

extern int SendS6DResetRequest();

extern int SendS6DNotifyRequest();

extern int SendS6DMEIdCheckRequest();
 


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the S6D Protocol messages to
 *      the diameter stack. These will create the appropriate S6D protocol
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

extern int SendS6DUpdateLocationAnswer(const diameter::CommandImpl *impl);

extern int SendS6DAuthenticationInformationAnswer(const diameter::CommandImpl *impl);

extern int SendS6DCancelLocationAnswer(const diameter::CommandImpl *impl);

extern int SendS6DPurgeUEAnswer(const diameter::CommandImpl *impl);

extern int SendS6DDeleteSubDataAnswer(const diameter::CommandImpl *impl);

extern int SendS6DInsertSubDataAnswer(const diameter::CommandImpl *impl);

extern int SendS6DResetAnswer(const CommandImpl * impl);

extern int SendS6DNotifyAnswer(const CommandImpl * impl);

extern int SendS6DMEIdCheckAnswer(const CommandImpl * impl);


#endif
