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
 * LOG: $Log: sample_eap.cpp,v $
 * LOG: Revision 3.4  2008/04/22 13:13:51  avinashks
 * LOG: Fix for Whizible Issue id: 886
 * LOG: Changes done to handle CE, DW and DP messages.
 * LOG:
 * LOG: Revision 3.3  2008/04/16 10:47:35  avinashks
 * LOG: Changes done as enhancement for EAP application against Bug id 843 logged by
 * LOG: lakshmys during validation.
 * LOG:
 * LOG: Revision 3.2  2008/04/07 09:44:18  avinashks
 * LOG: Changes made for Implementation of Proxy client.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:52:17  nanaparthi
 * LOG: EAP Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_eap.cpp,v 3.4 2008/04/22 13:13:51 avinashks Exp $
 ****************************************************************************/
#ident "$Id: sample_eap.cpp,v 3.4 2008/04/22 13:13:51 avinashks Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/eap/DiameterEAP.h>

#include <app.h>
#include <eap_defines.h>
#include <eap_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::eap;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sldxEap)
{
    ITS_INT pinfo_avp_count = 0, count;
    ProxyInfo *pinf=NULL;
    APP_TRACE_DEBUG(("Handling Dia App Message\n")); 
    try
    {
        // Update the receive statistics
        EapStats::GetEapStats()->UpdateRecvStats(impl->getCommandCode(),
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
            case EAP_DE_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    APP_TRACE_DEBUG(("Processing Request...\n")); 
                    DiameterEAPRequest eapReq(*impl);

                    const char *oriHost = GetOriginHost();
                    const char *oriRealm = GetOriginRealm();
                
                    if(!strcmp(eapReq.getDestinationRealm().value().c_str(),
                               oriRealm))
                    {
                        if (appMode == UNIT_TEST)
                            cout << "Diameter-EAP-Request" << eapReq << endl;
                        SendEapDiameterEAPAnswer(impl);
                    }
                    else
                    {
                        if(impl->isProxyable())
                        {
                            ProxyInfo pinfo;

                            ProxyHost phost(oriHost);
                            pinfo.setProxyHost(phost);

                            ProxyState pstate("state0");
                            pinfo.setProxyState(pstate);

                            eapReq.addProxyInfo(pinfo);

                            if (appMode == UNIT_TEST)
                                cout<<eapReq;

                            SendDiaAppMsg(eapReq, eapReq.getSessionIndex());
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
                    APP_TRACE_DEBUG(("Processing Answer...\n")); 

                    DiameterEAPAnswer eapAns(*impl);

                    const char *oriHost = GetOriginHost();
                    pinfo_avp_count = eapAns.countProxyInfo(); 

                    if (!pinfo_avp_count)
                    {
                        if (appMode == UNIT_TEST)
                            cout<<eapAns;
                        return ITS_SUCCESS; 
                    }

                    for(count=0; count < pinfo_avp_count; count++)
                    {
                        if(!strcmp(oriHost,
                            eapAns.getProxyInfo(count).getProxyHost(). \
                            value().c_str()))
                        {
                            APP_TRACE_DEBUG(("Message for Proxy Agent\n")); 
                            const ProxyInfo *pinfo1 = &(eapAns.getProxyInfo(count));
                            pinf = (ProxyInfo*) pinfo1;

                            if(impl->isProxyable())
                            {
                                cout<<"Message is Proxiable..."<<endl; 

                                if (pinf->removeAVP(pinf->getProxyHost()) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Host AVP removed successfully"<<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-Host AVP"<<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (pinf->removeAVP(pinf->getProxyState()) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-State AVP removed successfully"<<endl;
                                }
                                else
                                {
                                    cout<<"Unable to remove Proxy-State AVP"<<endl;
                                    return (!ITS_SUCCESS);
                                }
                                if (eapAns.removeAVP(*pinf) == ITS_SUCCESS)
                                {
                                    cout<<"Proxy-Info AVP removed successfully"<<endl;
                                }   
                                else
                                {
                                    cout<<"Unable to remove Proxy-Info AVP"<<endl;
                                    return (!ITS_SUCCESS);
                                }

                                if (appMode == UNIT_TEST)
                                    cout<<eapAns;

                                APP_TRACE_DEBUG(("Sending Answer Message...\n")); 
                                SendDiaAppMsg(eapAns, eapAns.getSessionIndex());
                                APP_TRACE_DEBUG(("Answer Message Sent...\n")); 
                                return ITS_SUCCESS;
                            }
                            else
                            {
                               return (!ITS_SUCCESS);
                            }
                        }
                    }
                    APP_TRACE_ERROR(("Proxy-Info Avp present in the message does not" \
                                     "matches for the Node."));
                    return (!ITS_SUCCESS);
                }
                break;

            // Handle Base Messages
            case BASE_RA_MSG_CMD_CODE:
            case BASE_ST_MSG_CMD_CODE:
            case BASE_AS_MSG_CMD_CODE:
            case BASE_CE_MSG_CMD_CODE:
            case BASE_DW_MSG_CMD_CODE:
            case BASE_DP_MSG_CMD_CODE:
                HandleBaseMessages(impl,sldxEap);
                break;

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
 *      This function displays the menu options for the Eap interface
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
            cout << endl << "Select EAP Command" <<endl << endl;
            cout << "1: DER - Diameter-EAP-Request" << endl;
            cout << "2: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 2) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendEapDiameterEAPRequest();
                    break;
                case 2:
                    DisplayBaseMenuToApp();
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
        if (EapStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < EapStats::burstSize; i++)
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
            ftime(&EapStats::current);
            TIMERS_USleep(EapStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((EapStats::current.time - EapStats::starter.time) >=
                 EapStats::duration)
            {
                if (EapStats::firstTime)
                {
                    ftime(&EapStats::sendComplete);
                    EapStats::sendTraffic = ITS_FALSE;
                    EapStats::firstTime = false;
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
    AppInitialize(EAP_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

