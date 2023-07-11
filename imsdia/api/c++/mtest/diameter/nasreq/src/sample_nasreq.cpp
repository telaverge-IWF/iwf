/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: sample_nasreq.cpp,v $
 * LOG: Revision 3.2  2010/05/07 03:47:34  nvijikumar
 * LOG: Proxy Agent Support with customization for customer evaluation
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/11 11:29:41  kamakshilk
 * LOG: AppId 1 added to commands
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:31:42  nanaparthi
 * LOG: NASREQ Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_nasreq.cpp,v 3.2 2010/05/07 03:47:34 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_nasreq.cpp,v 3.2 2010/05/07 03:47:34 nvijikumar Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/nasreq/AA.h>
#include <diameter/nasreq/RA.h>
#include <diameter/nasreq/ST.h>
#include <diameter/nasreq/AS.h>
#include <diameter/nasreq/AC.h>


#include <app.h>
#include <nasreq_defines.h>
#include <nasreq_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function processes the message received from the
 *      diameter stack. It identifies the commands and processes that command.
 *
 *  Input Parameters:
 *     ITS_Event& ev: Event Received from the Queue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxNasreq)
{
    ITS_INT pinfo_avp_count = 0, count;
    ProxyInfo *pinf=NULL;
    APP_TRACE_DEBUG(("Handling Dia App Message\n"));
    try
    {
        // Update the receive statistics
        NasreqStats::GetNasreqStats()->UpdateRecvStats(impl->getCommandCode(),
                                               impl->isRequest());

        // Process the commands based on the command code.
        if(impl->isError())
        {
           HandleErrorResponse(impl);
        }
        else
        {
            switch (impl->getCommandCode())
            {
            case NASREQ_AA_MSG_CMD_CODE:
            {
                if (impl->isRequest())
                {
                    AARequest aaReq(*impl);

                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();

                    if(!strcmp(aaReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {
                        if (appMode == UNIT_TEST)
                        cout << "AA-Request" << aaReq << endl;
                        SendNasreqAAAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG(("Processing Proxy Request...\n"));
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            aaReq.addProxyInfo(pinfo);

                            /* Change Calling Station Id */
                            if(aaReq.containsCallingStationId())
                            {
                                const CallingStationId *csId =
                                           &(aaReq.getCallingStationId());
                                CallingStationId *csIdPtr = NULL;
                                csIdPtr = (CallingStationId*)csId;
                                if (aaReq.removeAVP(*csIdPtr) == ITS_SUCCESS)
                                {
                                    cout<<"CallingStationId AVP removed "
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove CallingStationId"
                                        <<endl;
                                }
                            }
                            CallingStationId csID("station-IN");
                            aaReq.setCallingStationId(csID);
                            
                            /* User Name */
                            if(aaReq.containsUserName())
                            {
                                std::string uNameStr;
                                const UserName &uname =
                                           aaReq.getUserName();
                                uNameStr = aaReq.getUserName().value();

                                UserName *uName = NULL;
                                uName = (UserName*)&uname;
                                if (aaReq.removeAVP(*uName)== ITS_SUCCESS)
                                {
                                    cout<<"UserName AVP removed " <<endl;
                                }
                                else
                                {
                                   cout<<"Unable to remove UserName" <<endl;
                                }
                                char *token = strtok((char *)uNameStr.c_str(),"@");
                                string newUerName;
                                newUerName = token;
                                newUerName += "@atni.net";
                                aaReq.setUserName(UserName(newUerName));
                            }
                            else
                            {
                               cout<<"UserName is not exists in the pxy req"
                                   <<endl;
                            }


                            if (appMode == UNIT_TEST)
                                cout<<aaReq;

                            SendDiaAppMsg(aaReq, aaReq.getSessionIndex());
                            return ITS_SUCCESS;
                        }
                        else
                        {
                            return (!ITS_SUCCESS);
                        }
                    }
                }
                else
                {
                    AAAnswer aaAns(*impl);
                    const char *oriHost = GetOriginHost();
                    pinfo_avp_count = aaAns.countProxyInfo();

                    if (!pinfo_avp_count)
                    {
                        if (appMode == UNIT_TEST)
                        cout << "AA-Answer" << aaAns << endl;
                        return ITS_SUCCESS;
                    }
                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            aaAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n"));
                            const ProxyInfo *pinfo1 = 
                                            &(aaAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl;

                                if (pinf->removeAVP(pinf->getProxyHost()) == 
                                                                   ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == 
                                                                    ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (aaAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
#if 0
                                /* Calling Station Id */
                                if(aaAns.containsCallingStationId())
                                {
                                    const CallingStationId &csId =
                                               aaAns.getCallingStationId();
                                    CallingStationId *csIdPtr = NULL;
                                    csIdPtr = (CallingStationId*)&csId;
                                    if (aaAns.removeAVP(*csIdPtr)== ITS_SUCCESS)
                                    {
                                        cout<<"CallingStationId AVP removed "
                                            <<endl;
                                    }
                                    else
                                    {
                                       cout<<"Unable to remove CallingStationId"
                                            <<endl;
                                    }
                                }
                                CallingStationId csID("station-IN");
                                aaAns.setCallingStationId(csID);
#endif
                              
                                /* Delete UserName */
                                if(aaAns.containsUserName())
                                {
                                    const UserName &uname =
                                               aaAns.getUserName();
                                    UserName *uName = NULL;
                                    uName = (UserName*)&uname;
                                    if (aaAns.removeAVP(*uName)== ITS_SUCCESS)
                                    {
                                        cout<<"UserName AVP removed " <<endl;
                                    }
                                    else
                                    {
                                       cout<<"Unable to remove UserName" <<endl;
                                    }
                                }
 

                                if (appMode == UNIT_TEST)
                                    cout<<aaAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n"));
                                SendDiaAppMsg(aaAns, aaAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n"));
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);

                }
                break;
            }
            case NASREQ_RA_MSG_CMD_CODE:
            {
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                    RARequest raReq(*impl);

                    if(!strcmp(raReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Request" << raReq<< endl;
                        SendNasreqReAuthAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG(("Processing Proxy Request...\n"));
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            raReq.addProxyInfo(pinfo);

                            if (appMode == UNIT_TEST)
                                cout<<raReq;

                            SendDiaAppMsg(raReq, raReq.getSessionIndex());
                            return ITS_SUCCESS;
                        }
                        else
                        {
                            return (!ITS_SUCCESS);
                        }
                    }

                }
                else
                {
                    const char *oriHost = GetOriginHost();
                    RAAnswer raAns(*impl);
                    pinfo_avp_count = raAns.countProxyInfo();

                    if (!pinfo_avp_count)
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Answer" << raAns<< endl;
                        return ITS_SUCCESS;
                    }
                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            raAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n"));
                            const ProxyInfo *pinfo1 = 
                                            &(raAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl;

                                if (pinf->removeAVP(pinf->getProxyHost()) == 
                                                                   ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == 
                                                                    ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (raAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }

                                if (appMode == UNIT_TEST)
                                    cout<<raAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n"));
                                SendDiaAppMsg(raAns, raAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n"));
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);

                }
                break;
            }
            case NASREQ_ST_MSG_CMD_CODE:
            {
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                    STRequest stReq(*impl);

                    if(!strcmp(stReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Request" << stReq << endl;
                        SendNasreqSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG(("Processing Proxy Request...\n"));
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            stReq.addProxyInfo(pinfo);

                            if (appMode == UNIT_TEST)
                                cout<<stReq;

                            SendDiaAppMsg(stReq, stReq.getSessionIndex());
                            return ITS_SUCCESS;
                        }
                        else
                        {
                            return (!ITS_SUCCESS);
                        }
                    }

                }
                else
                {
                    const char *oriHost = GetOriginHost();
                    STAnswer stAns(*impl);

                    pinfo_avp_count = stAns.countProxyInfo();

                    if (!pinfo_avp_count)
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Answer" << stAns << endl;
                        return ITS_SUCCESS;
                    }
                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            stAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n"));
                            const ProxyInfo *pinfo1 = 
                                            &(stAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl;

                                if (pinf->removeAVP(pinf->getProxyHost()) == 
                                                                   ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == 
                                                                    ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (stAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }

                                if (appMode == UNIT_TEST)
                                    cout<<stAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n"));
                                SendDiaAppMsg(stAns, stAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n"));
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);

                }
                break;
            }
            case NASREQ_AS_MSG_CMD_CODE:
            {
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                    ASRequest asReq(*impl);

                    if(!strcmp(asReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {

                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Request"<<asReq << endl;
                        SendNasreqAbortSessionAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG(("Processing Proxy Request...\n"));
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            asReq.addProxyInfo(pinfo);

                            if (appMode == UNIT_TEST)
                                cout<<asReq;

                            SendDiaAppMsg(asReq, asReq.getSessionIndex());
                            return ITS_SUCCESS;
                        }
                        else
                        {
                            return (!ITS_SUCCESS);
                        }
                    }

                }
                else
                {
                    const char *oriHost = GetOriginHost();
                    ASAnswer asAns(*impl);
                    pinfo_avp_count = asAns.countProxyInfo();

                    if (!pinfo_avp_count)
                    {

                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Answer" <<asAns << endl;
                        return ITS_SUCCESS;
                    }
                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            asAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n"));
                            const ProxyInfo *pinfo1 = 
                                            &(asAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl;

                                if (pinf->removeAVP(pinf->getProxyHost()) == 
                                                                   ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == 
                                                                    ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (asAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }

                                if (appMode == UNIT_TEST)
                                    cout<<asAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n"));
                                SendDiaAppMsg(asAns, asAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n"));
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);

                }
                break;
            }
            case NASREQ_AC_MSG_CMD_CODE:
            {
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                    ACRequest acReq(*impl);

                    if(!strcmp(acReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Accounting-Request" << acReq << endl;
                        SendNasreqAccountingAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG(("Processing Proxy Request...\n"));
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            acReq.addProxyInfo(pinfo);

                            if (appMode == UNIT_TEST)
                                cout<<acReq;

                            SendDiaAppMsg(acReq, acReq.getSessionIndex());
                            return ITS_SUCCESS;
                        }
                        else
                        {
                            return (!ITS_SUCCESS);
                        }
                    }

                }
                else
                {
                    const char *oriHost = GetOriginHost();
                    ACAnswer acAns(*impl);
                    pinfo_avp_count = acAns.countProxyInfo();

                    if (!pinfo_avp_count)
                    {

                        if (appMode == UNIT_TEST)
                        cout << "Accounting-Answer" << acAns << endl;
                        return ITS_SUCCESS;
                    }
                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            acAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n"));
                            const ProxyInfo *pinfo1 = 
                                            &(acAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl;

                                if (pinf->removeAVP(pinf->getProxyHost()) == 
                                                                   ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == 
                                                                    ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (acAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"
                                        <<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"
                                        <<endl;
                                    return (!ITS_SUCCESS);
                                }

                                if (appMode == UNIT_TEST)
                                    cout<<acAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n"));
                                SendDiaAppMsg(acAns, acAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n"));
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);

                }
                break;
            }
            default:
               break;
            }
        }
    }
    catch (NoSuchAttributeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (WrongCommandTypeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (UnknownTypeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (CodecException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (...)
    {
        APP_TRACE_ERROR(("Unknown Exception Caught"));
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function displays the menu options for the NASREQ interface
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
 *      input - User choice of type integer.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int DisplayAppMenu()
{
    string input;
    int ret = 0;

    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select NASREQ Command" <<endl << endl;
            cout << "1: AAR - AA-Request" << endl;
            cout << "2: RAR - Re-Auth-Request" << endl;
            cout << "3: STR - Session-Termination-Request" << endl;
            cout << "4: ASR - Abort-Session-Request" << endl;
            cout << "5: ACR - Accounting-Request" << endl;
        //    cout << "6: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 5) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendNasreqAARequest();
                    break;
                case 2:
                    SendNasreqReAuthRequest();
                    break;
                case 3:
                    SendNasreqSessionTerminationRequest();
                    break;
                case 4:
                    SendNasreqAbortSessionRequest();
                    break;
                case 5:
                    SendNasreqAccountingRequest();
                    break;
             /*   case 6:
                    DisplayBaseMenuToApp();
                    break;*/
                case 99:
                    k=0;
                    break;
                default:
                    cout << endl << "please enter the correct choice";
                    break;
            }
        }
        catch (NoSuchAttributeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (WrongCommandTypeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (UnknownTypeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (CodecException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (...)
        {
            APP_TRACE_ERROR(("Unknown Exception Caught"));
        }
    }
    return ret;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function generates the load for the diameter
 *      stack during the load testing. If the appMode is set to
 *      LOAD_TEST, this function is called.
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
 ****************************************************************************/
int GenerateLoad()
{
    static int count = 0;
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];


    while (true)
    {
        if (NasreqStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < NasreqStats::burstSize; i++)
            {
                if (TrafficGeneratorFunc == NULL)
                {
                    APP_TRACE_ERROR(("Traffic Generator Func Not Set"));

                    return (!ITS_SUCCESS);
                }

                (*TrafficGeneratorFunc)();
            }

            /*
             * Sleep for the duration as specified in slpTime
             * Duration Provided should be in milliseconds
             */
            ftime(&NasreqStats::current);
            TIMERS_USleep(NasreqStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((NasreqStats::current.time - NasreqStats::starter.time) >=
                 NasreqStats::duration)
            {
                if (NasreqStats::firstTime)
                {
                    ftime(&NasreqStats::sendComplete);
                    NasreqStats::sendTraffic = ITS_FALSE;
                    NasreqStats::firstTime = false;
                    time(&tx);
                    temp = localtime_r(&tx, &tbuf);
                    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
                    cout << "Test stopped sending traffic at ----->"
                         << buff << endl;
               }
           }
       }
       else
           TIMERS_Sleep(1);
   }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This is the main function.
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
int main(int argc, const char** argv)
{
    AppInitialize(NASREQ_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

