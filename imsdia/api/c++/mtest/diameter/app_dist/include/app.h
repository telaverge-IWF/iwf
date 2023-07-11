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
 * LOG: $Log: app.h,v $
 * LOG: Revision 3.2  2011/03/23 03:46:01  mdinesh
 * LOG: Linux 64 bit compilation issue
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:09:04  kamakshilk
 * LOG: Common Files required for distributed set up
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:12:37  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: app.h,v 3.2 2011/03/23 03:46:01 mdinesh Exp $
 ****************************************************************************/
#ident "$Id: app.h,v 3.2 2011/03/23 03:46:01 mdinesh Exp $"

#ifndef _SAMPLE_IDC_APP
#define _SAMPLE_IDC_APP

#include <iostream>

#include <its++.h>
#include <its_timers.h>

#include <diameter/Command.h>
#include <diameter/base/BaseAVP.h>
using namespace diameter;
using namespace diameter::base;

#define BASE_INTERFACE_APP_ID    0
#define BASE_APP_THREAD_INST      1

/** 
 * Standard CommandCode's defined by IANA
 * For Base Interface
 **/
#define BASE_ACCT_MSG_CMD_CODE    271
#define BASE_CE_MSG_CMD_CODE      257
#define BASE_DW_MSG_CMD_CODE      280
#define BASE_DP_MSG_CMD_CODE      282
#define BASE_RA_MSG_CMD_CODE      258
#define BASE_ST_MSG_CMD_CODE      275
#define BASE_AS_MSG_CMD_CODE      274


/* Macro to log/display the error messages
*/
#define APP_TRACE_ERROR(x) \
              printf x

#define APP_TRACE_DEBUG(x) \
              printf x

#define APP_TRACE_WARNING(x) \
              printf x

#define APP_TRACE_CRITICAL(x) \
              printf x

enum ApplicationMode
{
    UNIT_TEST = 1,
    LOAD_TEST = 2
};
                                                                                
extern ApplicationMode appMode;

extern int mode;
extern int choice;

extern const char* orHost;
extern const char* orRealm;
extern const char* dhHost;
extern const char* drRealm;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to get the user configured values
 *     that are passed as commandLine options to the sample program
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
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginHost();
const char* GetOriginRealm();
const char* GetDestinationHost();
const char* GetDestinationRealm();

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to set the user configured values
 *     that are passed as commandLine options to the sample program
 *
 *  Input Parameters:
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
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
void SetOriginHost(const char* OriginHost);
void SetOriginRealm(const char* OriginRealm);
void SetDestinationHost(const char* DestinationHost);
void SetDestinationRealm(const char* DestinationRealm);


void AppInitialize(ITS_UINT appId);
int AppMain(int argc, const char** argv);
int HandleErrorResponse(const diameter::CommandImpl *impl);
int SendDiaAppMsg(diameter::Command& impl, ITS_UINT sesIdx=0);
int AllocateSession(ITS_UINT appId, ITS_UINT &sessIdx, std::string &sessString);
void ReleaseSession(std::string &sessString, ITS_UINT sessIdx=0);
bool IsDccaEnabled();

/* Load Generator Specific */
typedef int (*LoadGenFunc)();
extern LoadGenFunc TrafficGeneratorFunc;
extern int GenerateLoad();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Base Protocol messages to 
 *      the diameter stack. These will create the appropriate Base protocol 
 *      Request/Answer Command objects, populate the AVPs and sends the 
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
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *
 *  See Also:
 *      SendToStack()
 ****************************************************************************/
extern int SendReAuthRequest();
extern int SendSessionTerminationRequest
               (const diameter::base::SessionId *sesId=0);
extern int SendAbortSessionRequest();
extern int SendReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendAbortSessionAnswer(const diameter::CommandImpl *impl);
extern int HandleBaseMessages(const diameter::CommandImpl *impl,
                                   unsigned int &sIdxBase);
extern int DisplayBaseMenuToApp();

#endif
