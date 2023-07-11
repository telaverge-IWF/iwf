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
 * LOG: $Log: sample_sh.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:12  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:28:31  kamakshilk
 * LOG: Sh Interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_sh.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_sh.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $"

#include <dia_defines.h>

#include <diameter/sh/PushNotification.h>
#include <diameter/sh/SubscribeNotifications.h>
#include <diameter/sh/ProfileUpdate.h>
#include <diameter/sh/UserData.h>

#include <app.h>
#include <sh_defines.h>
#include <sh_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::sh;
using namespace diameter::cxdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handles the message received from  the base
 *      diameter stack. This identifies the commands
 *      in the message and processes that command.
 *
 *  Input Parameters:
 *      ITS_Event& ev: ITS_Event
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxSh)
{
    try
    {
        // Update the receive statistics
        ShStats::GetShStats()->UpdateRecvStats(impl->getCommandCode(),
                                               impl->isRequest());

        if(impl->isError())
        {
            HandleErrorResponse(impl);
        }
        else
        {
            switch (impl->getCommandCode())
            {
                case SH_UD_MSG_CMD_CODE: 
                    if(impl->isRequest())
                    {
                        UserDataRequest udreq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "udreq" << udreq << endl;

                        SendShUserDataAnswer(impl);
                    }
                    else
                    {
                        UserDataAnswer udans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "udans" << udans << endl;
                    }
                    break;

                case SH_PU_MSG_CMD_CODE:
                    if(impl->isRequest())
                    { 
                        ProfileUpdateRequest pureq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "pureq" << pureq << endl;

                        SendShProfileUpdateAnswer(impl);

                    }
                    else
                    {
                        ProfileUpdateAnswer puans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "puans" << puans << endl;
                        if (appMode == LOAD_TEST)
                        {
                            const SessionId &sesId=puans.getSessionId();
//                            SendSessionTerminationRequest(&sesId);
                        }

                    }
                    break;

                case SH_SN_MSG_CMD_CODE: 
                    if(impl->isRequest())
                    {
                        SubscribeNotificationsRequest snreq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "snreq" << snreq << endl;

                        SendShSubscribeNotificationsAnswer(impl);
                    }
                    else
                    {
                        SubscribeNotificationsAnswer snans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "snans" << snans << endl;
                    }
                    break;

                case SH_PN_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        PushNotificationRequest pnreq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "pnreq" << pnreq << endl;
                        SendShPushNotificationAnswer(impl);
                    }
                    else
                    {
                        PushNotificationAnswer pnans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "pnans" << pnans << endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxSh);
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

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      Sh interface.
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
int DisplayAppMenu()
{
    string input;
    int ret = 0;

    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Sh Command"<<endl<<endl;
            cout <<"1: PUR - Profile Update Request"<<endl;
            cout <<"2: PNR - Push Notification Request"<<endl;
            cout <<"3: SNR - Subscriber Notification Request"<<endl;
            cout <<"4: UDR - User Data Request"<<endl;
            cout <<"5: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret = atoi(input.c_str());
        } while ((ret < 1 || ret > 5) && ret!=99);

        try
        {
            switch(ret)
            {
                case 1:
                    SendShProfileUpdateRequest(); 
                    break;
                case 2:
                    SendShPushNotificationRequest(); 
                    break;
                case 3:
                    SendShSubscribeNotificationsRequest(); 
                    break;
                case 4:
                    SendShUserDataRequest(); 
                    break;
                case 5:
                    DisplayBaseMenuToApp(); 
                    break;
                case 99:
                    k =0;
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
        if (ShStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < ShStats::burstSize; i++)
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
            ftime(&ShStats::current);
            TIMERS_USleep(ShStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((ShStats::current.time - ShStats::starter.time) >=
                 ShStats::duration)
            {
                if (ShStats::firstTime)
                {
                    ftime(&ShStats::sendComplete);
                    ShStats::sendTraffic = ITS_FALSE;
                    ShStats::firstTime = false;
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
    AppInitialize(SH_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

