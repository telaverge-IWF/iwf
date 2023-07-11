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
 *  ID: $Id: app_common.cpp,v 3.1.30.1.26.1.4.1 2013/07/31 07:21:02 vsarath Exp $
 *
 *  LOG: $Log: app_common.cpp,v $
 *  LOG: Revision 3.1.30.1.26.1.4.1  2013/07/31 07:21:02  vsarath
 *  LOG: Fix for coverity warnings
 *  LOG:
 *  LOG: Revision 3.1.30.1.26.1  2013/02/27 08:49:06  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 3.1.30.1  2012/10/01 09:00:13  rsanjay
 *  LOG:  opendiameter code removal changes:bugzilla-id 300
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:06  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.4  2007/01/25 12:29:03  kamakshilk
 *  LOG: exit removed from AppTerminate
 *  LOG:
 *  LOG: Revision 2.3  2006/10/25 11:09:03  hbhatnagar
 *  LOG: DCCA Integartion with ITS_Diameter (badri)
 *  LOG:
 *  LOG: Revision 2.2  2006/10/16 13:17:07  tpanda
 *  LOG: Merging with ITSDIAMETER
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/08/04 18:00:48  nvijikumar
 *  LOG: Fix for Solaris CC compilation changes.
 *  LOG:
 *  LOG: Revision 1.1  2006/07/24 14:29:23  nvijikumar
 *  LOG: Baseline common application for all interfaces.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: app_common.cpp,v 3.1.30.1.26.1.4.1 2013/07/31 07:21:02 vsarath Exp $"
#include <iostream>
#include <its++.h>
#include <its_timers.h>
#include <engine++.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_defines.h>
#include <dia_config.h>
#include <dia_trace.h>
#include <dia_frame.h>
#include <app_trace.h>

#include <app.h>
#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/PROXYABLEERROR.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace base;
#endif

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
int
SendToStack(Command* impl)
{
    int ret;

    /* 
     * Access the diameter stack HANDLE  
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        /* 
         * Using the diameter stack HANDLE: aka DiaFrame
         * send the Command to the Diameter Stack. 
         */
        ret = diaFrame->Send(impl);

        if (ret != ITS_SUCCESS)
        {
           APP_TRACE_CRITICAL(("Send Failure %d\n", ret));

           return ret;
        }
    }
#if 0
    /* 
     * Update application statistics
     */
    ITS_BOOLEAN isReq = impl->isRequest() ? ITS_TRUE:ITS_FALSE;

    WxStats::GetWxStats()->UpdateSendStats(impl->getCommandCode(), isReq);
#endif
    return ITS_SUCCESS;

}

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
int
SendToStack(Command* impl, ITS_UINT index)
{
    int ret;

    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        /*
         * Using the diameter stack HANDLE: aka DiaFrame
         * send the Command to the Diameter Stack.
         */
        ret = diaFrame->Send(impl, index);

        if (ret != ITS_SUCCESS)
        {
           APP_TRACE_CRITICAL(("Send Failure %d\n", ret));

           return ret;
        }
    }
    return ITS_SUCCESS;

}

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
int AllocateSession(ITS_UINT appId, ITS_UINT &sessIdx, string &sessString)
{
    int ret = (!ITS_SUCCESS);

    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        /*
         * Using the diameter stack HANDLE: aka DiaFrame
         * send the Command to the Diameter Stack.
         */
        ret = diaFrame->AllocateSessionIndex(appId,sessIdx, sessString);
        if (ret != ITS_SUCCESS)
        {
           APP_TRACE_CRITICAL(("Session Allocate Failure %d\n", ret));
           return ret;
        }
        else 
        {
           APP_TRACE_DEBUG(("Succesful Session Allocation"));
           APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s",
                      sessIdx, sessString.c_str()));
        }
    }

    return ret;
}

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
int AppTerminate()
{

    /*
     * Terminate the diameter stack
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        diaFrame->Terminate();
    }

    return (ITS_SUCCESS);
}

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
int RegisterApplicationWithStack(ITS_UINT appId)
{
    /*
     * Access the diameter stack configuration details
     * via the DiaConfig Singelton Object Pointer
     */
    DiaConfig *cfg = DiaConfig::GetDiaConfig();

    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        if (cfg)
        {
            /*
             * Using the diameter stack HANDLE: aka DiaFrame
             * register all the applications with the diameter stack
             */
            diaFrame->RegisterApplication(appId);
        }
    }
    return ITS_SUCCESS;
}

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
int InitializeDiaStack()
{
    /*
     * Access the diameter stack configuration details
     * via the DiaConfig Singelton Object Pointer
     */
    DiaConfig *cfg = DiaConfig::GetDiaConfig();

    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        if (cfg)
        {
            /* Set the XML configuration file that contains the
             * Base Diameter Protocol Specific Configuration
             * NOTE: Since the Base Diameter Protocol is OpenDiameter
             * An Open Diameter style XML File should be provided.
             *
             * Refer to the AppOption:DiameterConfigFile in the
             * ../bin/demo.xml.server and ../bin/demo.xml.client
             * The Configuration object returns the name maintained
             * in this XML AppOption
             */
            diaFrame->SetConfigFile(cfg->GetConfigFile());

            /*
             * Now Initialize the Base diameter stack.
             */
            diaFrame->Initialize();
        }
    }
    return ITS_SUCCESS;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function converts the string into the Hex value.
 *
 *  Input Parameters:
 *      char *octet: String containing the Hexa value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the ITS_OCTET which contains the Hexa value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static
ITS_OCTET GetHexValue(char *octet)
{
    int i;
    ITS_OCTET val = 0;
    int len = strlen(octet);
    int incr = 1;

    for (i=len-1; i >= 0; i--, incr=incr*16)
    {
        if(isdigit(octet[i]))
        {
            val = val + (octet[i] - 48)*incr;
        }
        else if (tolower(octet[i]) == 'a')
        {
            val = val + 10*incr;
        }
        else if (tolower(octet[i]) == 'b')
        {
            val = val + 11*incr;
        }
        else if (tolower(octet[i]) == 'c')
        {
            val = val + 12*incr;
        }
        else if (tolower(octet[i]) == 'd')
        {
            val = val + 13*incr;
        }
        else if (tolower(octet[i]) == 'e')
        {
            val = val + 14*incr;
        }
        else if (tolower(octet[i]) == 'f')
        {
            val = val + 15*incr;
        }
    }

    return val;
}

/*
 * Holds the message in the dump;
 */
ITS_OCTET msg[1024];

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function reads the dump from dump.txt and creates the
 *      Message.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the size of the dump
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int ReadDump()
{
    FILE *fp;
    int size = 0;
    char escape;
    char word[256];

    memset(msg, sizeof(msg), 0);

    fp = fopen("MsgDump.txt", "r");

    if (NULL == fp)
    {
        APP_TRACE_ERROR(("Unable to open file : MsgDump.txt"));
        return -1;
    }
    else
    {
        while(fscanf(fp, "%s", word) != EOF)
        {
            if(word[0] == '#')
            {
                do
                {
                    escape = fgetc(fp);
                }
                while (escape != '\n');
                continue;
            }
            msg[size++] = GetHexValue(word);
        }
    }

    fclose(fp);
    return size;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the message to the stack as a dump.
 *      Dump should be in the file dump.txt in the current folder.
 *
 *  Input Parameters:
 *      ITS_USHORT inst: Application Thread Instance
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
void InjectDump(ITS_USHORT inst)
{
    Event ev;
    int len;
    int i;

    ev.SetSource(ITS_DIA_SRC);

    if ((len = ReadDump()) <= 0)
    {
        APP_TRACE_ERROR(("Invalid Buffer in File"));
        return;
    }

    ev.SetData(msg, len);

    its::Transport::PutEvent(inst, ev);

}

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
int ReceiveMessageFromEvent(its::ITS_Event& ev, DiaMsg* &dMsg)
{
    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame * diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        // Receive the message from the event received
        if (diaFrame->Receive(ev, &dMsg) != ITS_SUCCESS)
        {
            APP_TRACE_ERROR(("Failed to Receive Diameter Message"));
            return -1;
        }
    }
    return ITS_SUCCESS;
}

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

int HandleErrorResponse(const diameter::CommandImpl *impl)
{
    APP_TRACE_DEBUG(("Error Answers Received"));
    if(impl->isProxyable())
    {
       PROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }
    else
    {
       NONPROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }

    return (ITS_SUCCESS);
}

