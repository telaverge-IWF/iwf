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
 * LOG: Revision 1.1.2.1  2013/03/04 04:44:05  pramana
 * LOG: Adding simulators for demos
 * LOG:
 * LOG: Revision 1.1.2.1  2013/01/28 15:54:23  pramana
 * LOG: Committing the simulator code
 * LOG:
 * LOG: Revision 3.2.16.1  2012/09/28 08:01:15  pramana
 * LOG: Checkins for the changes done for GenBand demo
 * LOG:
 * LOG: Revision 3.2  2010/10/11 05:17:32  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 * LOG: Common files required for static setup
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
#ident "$Id: app.h,v 1.1.2.1 2013/03/04 04:44:05 pramana Exp $"

#ifndef _SAMPLE_APP
#define _SAMPLE_APP

#include <dia_frame.h>
#include <diameter/Command.h>
#include <diameter/base/BaseAVP.h>
#include <its++.h>
#include <engine++.h>

#include <app_trace.h>
using namespace std;
using namespace diameter;
using namespace diameter::base;
/* 
 * Application Specific Variables
 */
#define APP_TQ_INST            1
#define BASE_INTERFACE_APP_ID  0

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

extern int commandSet;

enum ApplicationMode
{
    UNIT_TEST = 1,
    LOAD_TEST = 2
};

/* Used only for UnitTest */
enum RunMode
{
    UNKNOWN   = 0,
    INITIATOR = 1,
    RECEIVER  = 2
};

#define MAX_MSGS_TO_DISPLAY 12

union diameter_message_stats
{
    long m_in;
    long m_out;
};
typedef struct
{
    long m_outMsgs;
    long m_inMsgs;
    long m_lastOutMsgs;
    long m_lastInMsgs;
    long m_successfulCalls;
    long m_failedCalls;
    long m_lastSuccessfulCalls;
    long m_lastFailedCalls;
    union
    {
        struct 
        {
            diameter_message_stats air;
            diameter_message_stats aia;
            diameter_message_stats ulr;
            diameter_message_stats ula;
        } s6a;
        struct 
        {
            diameter_message_stats ccr;
            diameter_message_stats cca;
            diameter_message_stats rar;
            diameter_message_stats raa;
        } s9;
        struct
        {
            diameter_message_stats ccr;
            diameter_message_stats cca;
        } gy;
        struct
        {
            diameter_message_stats ccr;
            diameter_message_stats cca;
        } gx;
    }u;
    string last_processed_sessionId[MAX_MSGS_TO_DISPLAY];
    string last_processed_msgs[MAX_MSGS_TO_DISPLAY];
    int recent_msg_idx;
}ApplicationStats;

extern ApplicationMode appMode;
extern RunMode runMode;
extern int     displayMode;

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
extern int HandleErrorResponse(const DIA_BASE_CMD *bCmd);

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
extern int SendDiaAppMsg(diameter::Command& appCmd, ITS_UINT sesIdx=0);

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
extern LoadGenFunc TrafficGeneratorFunc;
extern int GenerateLoad();

extern void ReleaseSession(string &sessString, ITS_UINT sessIdx = 0);
extern bool IsDccaEnabled();
extern void AppInitialize(ITS_UINT appId);
extern "C" 
{
ITS_USHORT ApplicationRoutingFunction(ITS_HDR* h, ITS_EVENT* ev);
void SenderThreadFunc(its::ThreadPoolThread* thr, void* arg);
void ReceiverThreadFunc(its::ThreadPoolThread* thr, void* arg);
void DisplayThreadFunc(its::ThreadPoolThread* thr, void* arg);
void DisplayThreadFunc2(its::ThreadPoolThread* thr, void* arg);
void DisplayCursesThreadFunc(its::ThreadPoolThread* thr, void* arg);
void AppThreadFunc(its::ThreadPoolThread* thr, void* arg);
}
extern int AppMain(int argc, const char** argv);

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
