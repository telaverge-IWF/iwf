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
 *  ID: $Id: app_common.cpp,v 1.1.2.1 2013/01/28 15:54:23 pramana Exp $
 *
 *  LOG: $Log: app_common.cpp,v $
 *  LOG: Revision 1.1.2.1  2013/01/28 15:54:23  pramana
 *  LOG: Committing the simulator code
 *  LOG:
 *  LOG: Revision 3.3  2008/04/22 11:47:43  avinashks
 *  LOG: Fix for Whizible Issue id: 890
 *  LOG: Changes done to print Error Response properly on IDC.
 *  LOG:
 *  LOG: Revision 3.2  2008/04/16 11:17:25  avinashks
 *  LOG: Changes done for Application to support agents.
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.2  2007/01/25 12:22:37  kamakshilk
 *  LOG: exit removed from AppTerminate
 *  LOG:
 *  LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 *  LOG: Common files required for static setup
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
#ident "$Id: app_common.cpp,v 1.1.2.1 2013/01/28 15:54:23 pramana Exp $"
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
#include <diameter/base/BaseGenericCommand.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace base;
#endif

const char* orHost;
const char* orRealm;
const char* dhHost;
const char* drRealm;

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
    return ITS_SUCCESS;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This is a wrapper provieded for the interfaces. 
 *           This functions called the dframe Send API.
 *
 *  Input Parameters:
 *      impl - type Command.
 *      sessionIndex - type unsigned int.
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
SendDiaAppMsg(diameter::Command& appCmd, ITS_UINT sesIdx)
{
    return SendToStack(&appCmd);
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
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This is a wrapper function to release a diameter session.
 *           It calls the dframe ReleaseSession API.
 *
 *  Input Parameters:
 *      ITS_UINT sessIdx, string &sessString
 *
 *  Input/Output Parameters:
 *      None.
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
void ReleaseSession(string &sessString, ITS_UINT sessIdx)
{
    DiaFrame::GetDiaFrame()->ReleaseSession(sessString.c_str());
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This is a wrapper function to check if DCCA is enabled at stack.
 *           It calls the dframe IsDccaEnabled API.
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
 *      true or false.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
bool IsDccaEnabled()
{
    return DiaFrame::GetDiaFrame()->IsDccaEnabled();
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

int HandleErrorResponse(const DIA_BASE_CMD *bCmd)
{
    ITS_INT pinfo_avp_count=0, avpCount;
    ProxyInfo *pinf=NULL;
    ITS_INT ret = (!ITS_SUCCESS);

    const char *oriHost = GetOriginHost();

    printf(("Error Answers Received"));

    if(bCmd->isProxyable())
    {
        /*PROXYABLEERROR err(*impl);
        Command *cmd = (Command *) &err;
        diameter::base::BaseGenericCommand *gCmd =
                                (diameter::base::BaseGenericCommand *) cmd;*/
#if 0
        const diameter::base::BaseGenericCommand *gCmd =
                               const_cast<DIA_BASE_CMD*>(bCmd)->GetBaseGenCommand();
#endif
        pinfo_avp_count = const_cast<DIA_BASE_CMD*>(bCmd)->countProxyInfo();

        for(avpCount=0; avpCount < pinfo_avp_count; avpCount++)
        {
            if(!strcmp(oriHost,
                       (const_cast<DIA_BASE_CMD*>(bCmd)->getProxyInfo(avpCount)->getProxyHost())->
                       value().c_str()))
            {
                const ProxyInfo *pinfo1 = ((diameter::base::BaseGenericCommand *)bCmd)->getProxyInfo(avpCount);
                pinf = (ProxyInfo*) pinfo1;

                if ((pinf->removeAVP(pinf->getProxyHost())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Host AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Host AVP"));
                }
                if ((pinf->removeAVP(pinf->getProxyState())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-State AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-State AVP"));
                }
                if (((Command*)bCmd)->removeAVP(*pinf) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Info AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Info AVP"));
                }

                if ((ret = SendDiaAppMsg(*(Command*)bCmd, const_cast<DIA_BASE_CMD*>(bCmd)->getSessionIndex())) != ITS_SUCCESS)
                {
                    APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                }
                return ret;
            }
        }
        if(pinfo_avp_count == 0)
        {
            //cout<<endl<<err<<endl;
            return ITS_SUCCESS;
        }
        else if(avpCount > pinfo_avp_count)
        {
            //cout<<endl<<"Error in Message"<<endl;
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        //NONPROXYABLEERROR err(*impl);
        //cout<<endl<<err<<endl;
    }

    return (ITS_SUCCESS);
}
/////////////////////////////////////////////// -> Older
int HandleErrorResponse(const diameter::CommandImpl *impl)
{
    ITS_INT pinfo_avp_count=0, avpCount;
    ProxyInfo *pinf=NULL;
    ITS_INT ret = (!ITS_SUCCESS);

    const char *oriHost = GetOriginHost();

    printf(("Error Answers Received"));

    if(impl->isProxyable())
    {
        PROXYABLEERROR err(*impl);
        Command *cmd = (Command *) &err;
        diameter::base::BaseGenericCommand *gCmd =
                                (diameter::base::BaseGenericCommand *) cmd;
        pinfo_avp_count = gCmd->countProxyInfo();

        for(avpCount=0; avpCount < pinfo_avp_count; avpCount++)
        {
            if(!strcmp(oriHost,
                       gCmd->getProxyInfo(avpCount)->getProxyHost(). \
                       value().c_str()))
            {
                const ProxyInfo *pinfo1 = gCmd->getProxyInfo(avpCount);
                pinf = (ProxyInfo*) pinfo1;

                if ((pinf->removeAVP(pinf->getProxyHost())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Host AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Host AVP"));
                }
                if ((pinf->removeAVP(pinf->getProxyState())) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-State AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-State AVP"));
                }
                if (((Command*)gCmd)->removeAVP(*pinf) == ITS_SUCCESS)
                {
                    APP_TRACE_DEBUG(("Proxy-Info AVP removed successfully"));
                }
                else
                {
                    APP_TRACE_ERROR(("Unable to remove Proxy-Info AVP"));
                }

                if ((ret = SendDiaAppMsg(*gCmd, gCmd->getSessionIndex())) != ITS_SUCCESS)
                {
                    APP_TRACE_ERROR(("SendDiaAppMsg Failure"));
                }
                return ret;
            }
        }
        if(pinfo_avp_count == 0)
        {
            cout<<endl<<err<<endl;
            return ITS_SUCCESS;
        }
        else if(avpCount > pinfo_avp_count)
        {
            cout<<endl<<"Error in Message"<<endl;
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        NONPROXYABLEERROR err(*impl);
        cout<<endl<<err<<endl;
    }

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get OriginHost  
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
 *     orHost - type char 
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginHost() 
{
    return orHost;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get OriginRealm 
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
 *     orRealm - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginRealm() 
{
    return orRealm;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get DestinationHost 
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
 *     dhHost - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetDestinationHost() 
{
    return dhHost;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Method to get DestinationRealm 
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
 *     dhRealm - type char
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetDestinationRealm() 
{
    return drRealm;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set OriginHost 
 *
 *  Input Parameters:
 *      OriginHost - type char.
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
void SetOriginHost(const char* OriginHost) 
{
    orHost = strdup(OriginHost);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set OriginRealm 
 *
 *  Input Parameters:
 *      OriginRealm - type char.
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
void SetOriginRealm(const char* OriginRealm) 
{
    orRealm = strdup(OriginRealm);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set DestinationHost
 *
 *  Input Parameters:
 *      DestinationHost - type char.
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
void SetDestinationHost(const char* DestinationHost) 
{
    dhHost = strdup(DestinationHost);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Method to set DestinationRealm 
 *  
 *  Input Parameters:
 *      DestinationRealm - type char.
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
void SetDestinationRealm(const char* DestinationRealm) 
{
    drRealm = strdup(DestinationRealm);
}

