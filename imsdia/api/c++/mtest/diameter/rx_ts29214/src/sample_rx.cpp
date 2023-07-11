/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: sample_rx.cpp,v $
 * LOG: Revision 1.2  2011/07/22 11:49:46  rajeshak
 * LOG: Proxy Changes for RX Interface
 * LOG:
 * LOG: Revision 1.1  2010/07/29 09:17:44  nvijikumar
 * LOG: RX sample app for TS29214 support
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_rx.cpp,v 1.2 2011/07/22 11:49:46 rajeshak Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/rx_ts29214/AA.h>
#include <diameter/rx_ts29214/RA.h>
#include <diameter/rx_ts29214/AS.h>
#include <diameter/rx_ts29214/ST.h>

#include <app.h>
#include <rx_defines.h>
#include <rx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rx_ts29214;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function processes the message received from the base
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRx)
{
    ITS_INT pinfo_avp_count = 0, count;
    ProxyInfo *pinf=NULL;
    try
    {
        // Update the receive statistics
        RxStats::GetRxStats()->UpdateRecvStats(impl->getCommandCode(), 
                                               impl->isRequest());
        // Process the commands based on the command code.
        if(impl->isError())
        {
           HandleErrorResponse(impl);
        }
        switch (impl->getCommandCode())
        {
            case RX_AA_MSG_CMD_CODE:
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
                        SendRxAAAnswer(impl);
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
                    pinfo_avp_count = aaAns.countProxyInfo();
                    if (!pinfo_avp_count)
                    {
                        if (appMode == UNIT_TEST)
                            cout << "AA Answer" << aaAns << endl;
                        return ITS_SUCCESS;
                    }

                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();

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
                }
                break;
            case RX_AS_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    ASRequest asReq(*impl);
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();

                    if(!strcmp(asReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {
                        if (appMode == UNIT_TEST)
                        cout << "Abort Session Request" << asReq<< endl;
                        SendRxASAnswer(impl);
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
                    ASAnswer asAns(*impl);
                    pinfo_avp_count = asAns.countProxyInfo();
                    if (!pinfo_avp_count)
                    {
                    if (appMode == UNIT_TEST)
                        cout << "Abort Session Answer" << asAns<< endl;
                        return ITS_SUCCESS;
                    }
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();

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
                }
                break;
            case RX_RA_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();

                    RARequest raReq(*impl);
                    if(!strcmp(raReq.getDestinationRealm().value().c_str(),
                           oriRealm))
                    {
                        if (appMode == UNIT_TEST)
                            cout << "RA Request" << raReq << endl;
                        SendRxRAAnswer(impl);
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
                                    cout << "RA Answer" << raAns << endl;
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
            case RX_ST_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                    STRequest stReq(*impl);
                    if(!strcmp(stReq.getDestinationRealm().value().c_str(),oriRealm))
                    {
                        if (appMode == UNIT_TEST)
                            cout << "ST Request" << stReq << endl;
                        SendRxSTAnswer(impl);
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
                                    cout << "ST Answer" << stAns << endl;
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

                break;
}
            default:
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

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: 
 *      This function displays the menu options for the Rx interface
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
            cout << endl << "Select Rx Command" <<endl << endl;
            cout << "1: AA - AA Request" << endl;
            cout << "2: RA - Re Auth Request" << endl;
            cout << "3: ST - Session Termination Request" << endl;
            cout << "4: AS - Abort Session Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);
    
        try
        {
            switch (ret)
            {
                case 1:
                    SendRxAARequest();
                    break;
                case 2:
                    SendRxRARequest();
                    break;
                case 3:
                    SendRxSTRequest();
                    break;
                case 4:
                    SendRxASRequest();
                    break;
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
        if (RxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < RxStats::burstSize; i++)
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
            ftime(&RxStats::current);
            TIMERS_USleep(RxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((RxStats::current.time - RxStats::starter.time) >=
                 RxStats::duration)
            {
                if (RxStats::firstTime)
                {
                    ftime(&RxStats::sendComplete);
                    RxStats::sendTraffic = ITS_FALSE;
                    RxStats::firstTime = false;
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
    AppInitialize(RX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

