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
 * LOG: $Log: app.h,v $
 * LOG: Revision 3.2  2011/03/23 03:44:55  mdinesh
 * LOG: 64 bit Compilation issue
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:05  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/10/25 10:58:07  hbhatnagar
 * LOG: DCCA Integration with ITS_Diameter (badri)
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:40  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/24 14:28:26  nvijikumar
 * LOG: Baseline common application for all interfaces.
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app.h,v 3.2 2011/03/23 03:44:55 mdinesh Exp $"

#ifndef _SAMPLE_APP
#define _SAMPLE_APP

#include <iostream>
#include<dia_frame.h>
#include <diameter/Command.h>
#include <its++.h>
#include <engine++.h>

using namespace std;
/* 
 * Application Specific Variables
 */

extern int commandSet;

enum ApplicationMode
{
    UNIT_TEST = 1,
    LOAD_TEST = 2
};

/* Used only for UnitTest */
enum RunMode
{
    INITIATOR = 1,
    RECEIVER  = 2
};

extern ApplicationMode appMode;
extern RunMode runMode;

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

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *       
 *         Utility function to handle error responses
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Error response 
 *      Command 
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
extern int HandleErrorResponse(const diameter::CommandImpl *impl);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function Registers the given application Id with stack.
 *
 *  Input Parameters:
 *      Application Id.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int RegisterApplicationWithStack(ITS_UINT appId);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function initialize the Diameter Stack.
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
 *      Returns the ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int InitializeDiaStack();

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function Receive the message from event received.
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
 *      Returns the ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int ReceiveMessageFromEvent(its::ITS_Event& ev, DiaMsg* &dMsg);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function conerts the  message from byte format to readable
 *      format.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      ITS_USHORT inst.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern void InjectDump(ITS_USHORT inst);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function allocates a new session and it gives the sessIdx
 *      and sessString.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      ITS_UINT appId, ITS_UINT &sessIdx, string &sessString
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern 
int AllocateSession(ITS_UINT appId, ITS_UINT &sessIdx, string &sessString);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function actually sends the Command to the base 
 *      diameter stack.
 *
 *  Input Parameters:
 *      impl - type CommandImpl.
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
 ****************************************************************************/
extern int SendToStack(diameter::Command *impl);
extern int SendToStack(diameter::Command *impl, ITS_UINT);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function disables all traces and terminates the DiaFrame
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
 *      Returns the ITS_SUCCESS
 *
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
extern int AppTerminate();

/* Load Generator Specific */
typedef int (*LoadGenFunc)();
extern
LoadGenFunc TrafficGeneratorFunc;
extern int GenerateLoad();



#endif
