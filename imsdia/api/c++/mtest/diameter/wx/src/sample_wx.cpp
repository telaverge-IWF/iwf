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
 * LOG: $Log: sample_wx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/12/19 09:02:14  kamakshilk
 * LOG: New architecture to work with static and distributed
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/08/04 17:45:26  nvijikumar
 * LOG: Fix for Solaris Compilation issue.
 * LOG:
 * LOG: Revision 1.2  2006/07/31 07:09:07  kamakshilk
 * LOG: Added new Message ( Registration Termination).
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_wx.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/wx/MultimediaAuthentication.h>
#include <diameter/wx/PushProfile.h>
#include <diameter/wx/ServerAssignment.h>
#include <diameter/wx/RegistrationTermination.h>

#include <app.h>
#include <wx_defines.h>
#include <wx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::wx;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxWx)
{
    try
    {
        // Update the receive statistics
        WxStats::GetWxStats()->UpdateRecvStats(impl->getCommandCode(), 
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
                case WX_SA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ServerAssignmentRequest saReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ServerAssignmentRequest" << saReq << endl;
                        SendWxServerAssignmentAnswer(impl);
                    }
                    else
                    {
                        ServerAssignmentAnswer saAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ServerAssignmentAnswer" << saAns << endl;
                    }
                    break;

                case WX_MA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        MultimediaAuthenticationRequest maReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "MultimediaAuthenticationRequest" 
                             << maReq<< endl;
                        SendWxMultimediaAuthenticationAnswer(impl);
                    }
                    else
                    {
                        MultimediaAuthenticationAnswer maAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "MultimediaAuthenticationAnswer" 
                             << maAns<< endl;
                    }
                    break;
   
                case WX_PP_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PushProfileRequest ppReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "PushProfileRequest" << ppReq << endl;
                        SendWxPushProfileAnswer(impl);
                    }
                    else
                    {
                        PushProfileAnswer ppAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "PushProfileAnswer" << ppAns << endl;
                    }
                    break;
                case WX_RT_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RegistrationTerminationRequest rtReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout <<"RegistrationTerminationRequest"
                                 << rtReq << endl;
                        SendWxRegistrationTerminationAnswer(impl);
                    }
                    else
                    {
                        RegistrationTerminationAnswer rtAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout <<"RegistrationTerminationAnswer" 
                                 << rtAns << endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxWx);
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
 *      This function displays the menu options for the Wx interface
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
            cout << endl << "Select Wx Command" <<endl << endl;
            cout << "1: MAR - Multimedia Authentication Request" << endl;
            cout << "2: PPR - Push Profile Request" << endl;
            cout << "3: SAR - Server Assignment Request" << endl;
            cout << "4: RTR - Registration Termination Request" << endl;
            cout << "5: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 5) && ret!=99);
    
        try
        {
            switch (ret)
            {
                case 1:
                    SendWxMultimediaAuthenticationRequest();
                    break;
                case 2:
                    SendWxPushProfileRequest();
                    break;
                case 3:
                    SendWxServerAssignmentRequest();
                    break;
                case 4:
                    SendWxRegistrationTerminationRequest();
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
        if (WxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < WxStats::burstSize; i++)
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
            ftime(&WxStats::current);
            TIMERS_USleep(WxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((WxStats::current.time - WxStats::starter.time) >=
                 WxStats::duration)
            {
                if (WxStats::firstTime)
                {
                    ftime(&WxStats::sendComplete);
                    WxStats::sendTraffic = ITS_FALSE;
                    WxStats::firstTime = false;
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
    AppInitialize(WX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

