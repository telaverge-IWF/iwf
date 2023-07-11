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
 * LOG: $Log: sample_rr_delegatedmodel.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:36:51  vkumara
 * LOG: Baseline for rr_delegatedmodel interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_rr_delegatedmodel.cpp,v 1.1 2011/06/29 06:36:51 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_rr_delegatedmodel.cpp,v 1.1 2011/06/29 06:36:51 vkumara Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/rr_delegatedmodel/UserData.h>
#include <diameter/rr_delegatedmodel/PushNotification.h>
#include <diameter/rr_delegatedmodel/CC.h>
#include <diameter/rr_delegatedmodel/RA.h>


#include <app.h>
#include <rr_delegatedmodel_defines.h>
#include <rr_delegatedmodel_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rr_delegatedmodel;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRr_Delegatedmodel)
{
    try
    {
        // Update the receive statistics
        Rr_DelegatedmodelStats::GetRr_DelegatedmodelStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case Rr_Delegatedmodel_UD_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UserDataRequest saReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserDataRequest" << saReq << endl;
                        SendRr_DelegatedmodelUserDataAnswer(impl);
                    }
                    else
                    {
                        UserDataAnswer saAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserDataAnswer" << saAns << endl;
                    }
                    break;

                case Rr_Delegatedmodel_PN_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PushNotificationRequest rtReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"PushNotificationRequest"<<rtReq <<endl;
                        SendRr_DelegatedmodelPushNotificationAnswer(impl);
                    }
                    else
                    {
                        PushNotificationAnswer rtAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"PushNotificationAnswer" <<rtAns <<endl;
                    }
                    break;
                 
                 case Rr_Delegatedmodel_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RARequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"ReauthRequest"<<raReq <<endl;
                        SendRr_DelegatedmodelRAAnswer(impl);
                    }
                    else
                    {
                        RAAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"ReauthAnswer" <<raAns <<endl;
                    }
                    break;

		case Rr_Delegatedmodel_CC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CCRequest ccReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"CCRequest"<<ccReq <<endl;
                        SendRr_DelegatedmodelCCAnswer(impl);
                    }
                    else
                    {
                        CCAnswer ccAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"CCAnswer" <<ccAns <<endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxRr_Delegatedmodel);
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
 *      This function displays the menu options for the Rr_Delegatedmodel interface
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
            cout << endl << "Select Rr_Delegatedmodel Command" <<endl << endl;
            cout << "1: UDR - User Data Request" << endl;
            cout << "2: PNR - Push Notification Request" << endl;
            cout << "3: RAR - ReAuth  Request" << endl;
            cout << "4: CCR - Credit Control Request" << endl;
            cout << "5: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 5) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendRr_DelegatedmodelUserDataRequest();
                    break;
                case 2:
                    SendRr_DelegatedmodelPushNotificationRequest();
                    break;
		case 3:
                    SendRr_DelegatedmodelRARequest();
                    break;
                case 4:
                    SendRr_DelegatedmodelCCRequest();
                    break;
                case 5:
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
        if (Rr_DelegatedmodelStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < Rr_DelegatedmodelStats::burstSize; i++)
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
            ftime(&Rr_DelegatedmodelStats::current);
            TIMERS_USleep(Rr_DelegatedmodelStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((Rr_DelegatedmodelStats::current.time - Rr_DelegatedmodelStats::starter.time) >=
                 Rr_DelegatedmodelStats::duration)
            {
                if (Rr_DelegatedmodelStats::firstTime)
                {
                    ftime(&Rr_DelegatedmodelStats::sendComplete);
                    Rr_DelegatedmodelStats::sendTraffic = ITS_FALSE;
                    Rr_DelegatedmodelStats::firstTime = false;
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
    AppInitialize(Rr_Delegatedmodel_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

