/********************************-*-CPP-*-***********************************
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
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: sample_a4.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:39:46  vkumara
 * LOG: Baseline for a4 interface.
 * LOG:
 * LOG:
 * ID: $Id: sample_a4.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_a4.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/a4/UserData.h>
#include <diameter/a4/PushNotification.h>

#include <app.h>
#include <a4_defines.h>
#include <a4_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::a4;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxA4)
{
    try
    {
        // Update the receive statistics
        A4Stats::GetA4Stats()->UpdateRecvStats(impl->getCommandCode(),
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
                case A4_UD_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UserDataRequest saReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserDataRequest" << saReq << endl;
                        SendA4UserDataAnswer(impl);
                    }
                    else
                    {
                        UserDataAnswer saAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserDataAnswer" << saAns << endl;
                    }
                    break;

                case A4_PN_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PushNotificationRequest rtReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"PushNotificationRequest"<<rtReq <<endl;
                        SendA4PushNotificationAnswer(impl);
                    }
                    else
                    {
                        PushNotificationAnswer rtAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"PushNotificationAnswer" <<rtAns <<endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxA4);
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
 *      This function displays the menu options for the A4 interface
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
            cout << endl << "Select A4 Command" <<endl << endl;
            cout << "1: UDR - User Data Request" << endl;
            cout << "2: PNR - Push Notification Request" << endl;
            cout << "3: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 3) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendA4UserDataRequest();
                    break;
                case 2:
                    SendA4PushNotificationRequest();
                    break;
                case 3:
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
        if (A4Stats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < A4Stats::burstSize; i++)
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
            ftime(&A4Stats::current);
            TIMERS_USleep(A4Stats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((A4Stats::current.time - A4Stats::starter.time) >=
                 A4Stats::duration)
            {
                if (A4Stats::firstTime)
                {
                    ftime(&A4Stats::sendComplete);
                    A4Stats::sendTraffic = ITS_FALSE;
                    A4Stats::firstTime = false;
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
    AppInitialize(A4_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

