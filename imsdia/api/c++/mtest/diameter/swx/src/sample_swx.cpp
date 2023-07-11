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
 * LOG: $Log: sample_swx.cpp,v $
 * LOG: Revision 1.1  2011/05/03 04:58:33  vkumara
 * LOG: SWx interface support.
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_swx.cpp,v 1.1 2011/05/03 04:58:33 vkumara Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/swx/MultimediaAuthentication.h>
#include <diameter/swx/PushProfile.h>
#include <diameter/swx/ServerAssignment.h>
#include <diameter/swx/RegistrationTermination.h>

#include <app.h>
#include <swx_defines.h>
#include <swx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::swx;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxSWx)
{
    try
    {
        // Update the receive statistics
        SWxStats::GetSWxStats()->UpdateRecvStats(impl->getCommandCode(), 
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
                case SWX_SA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ServerAssignmentRequest saReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ServerAssignmentRequest" << saReq << endl;
                        SendSWxServerAssignmentAnswer(impl);
                    }
                    else
                    {
                        ServerAssignmentAnswer saAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ServerAssignmentAnswer" << saAns << endl;
                    }
                    break;

                case SWX_MA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        MultimediaAuthenticationRequest maReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "MultimediaAuthenticationRequest" 
                             << maReq<< endl;
                        SendSWxMultimediaAuthenticationAnswer(impl);
                    }
                    else
                    {
                        MultimediaAuthenticationAnswer maAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "MultimediaAuthenticationAnswer" 
                             << maAns<< endl;
                    }
                    break;
   
                case SWX_PP_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PushProfileRequest ppReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "PushProfileRequest" << ppReq << endl;
                        SendSWxPushProfileAnswer(impl);
                    }
                    else
                    {
                        PushProfileAnswer ppAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "PushProfileAnswer" << ppAns << endl;
                    }
                    break;
                case SWX_RT_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RegistrationTerminationRequest rtReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout <<"RegistrationTerminationRequest"
                                 << rtReq << endl;
                        SendSWxRegistrationTerminationAnswer(impl);
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
                    HandleBaseMessages(impl,sIdxSWx);
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
 *      This function displays the menu options for the SWx interface
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
            cout << endl << "Select SWx Command" <<endl << endl;
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
                    SendSWxMultimediaAuthenticationRequest();
                    break;
                case 2:
                    SendSWxPushProfileRequest();
                    break;
                case 3:
                    SendSWxServerAssignmentRequest();
                    break;
                case 4:
                    SendSWxRegistrationTerminationRequest();
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
        if (SWxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < SWxStats::burstSize; i++)
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
            ftime(&SWxStats::current);
            TIMERS_USleep(SWxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((SWxStats::current.time - SWxStats::starter.time) >=
                 SWxStats::duration)
            {
                if (SWxStats::firstTime)
                {
                    ftime(&SWxStats::sendComplete);
                    SWxStats::sendTraffic = ITS_FALSE;
                    SWxStats::firstTime = false;
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
    AppInitialize(SWX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

