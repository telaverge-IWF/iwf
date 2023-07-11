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
 * LOG: $Log: sample_cx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:47:03  kamakshilk
 * LOG: Cx 3GPP2 interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_cx.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_cx.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/cx_3gpp2/MultimediaAuth.h>
#include <diameter/cx_3gpp2/PushProfile.h>
#include <diameter/cx_3gpp2/ServerAssignment.h>
#include <diameter/cx_3gpp2/RegistrationTermination.h>
#include <diameter/cx_3gpp2/UserAuthorization.h>
#include <diameter/cx_3gpp2/LocationInfo.h>

#include <app.h>
#include <cx_defines.h>
#include <cx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cx_3gpp2;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxCx)
{
    try
    {
        // Update the receive statistics
        CxStats::GetCxStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case CX_SA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ServerAssignmentRequest saReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "ServerAssignmentRequest" << saReq << endl;
                        SendCxServerAssignmentAnswer(impl);
                    }
                    else
                    {
                        ServerAssignmentAnswer saAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "ServerAssignmentAnswer" << saAns << endl;
                    }
                    break;
                case CX_MA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        MultimediaAuthRequest maReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "MultimediaAuthRequest" << maReq<< endl;
                        SendCxMultimediaAuthAnswer(impl);
                    }
                    else
                    {
                        MultimediaAuthAnswer maAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "MultimediaAuthAnswer" << maAns<< endl;
                    }
                    break;

                case CX_PP_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PushProfileRequest ppReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "PushProfileRequest" << ppReq << endl;
                        SendCxPushProfileAnswer(impl);
                    }
                    else
                    {
                        PushProfileAnswer ppAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "PushProfileAnswer" << ppAns << endl;
                    }
                    break;
                case CX_RT_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RegistrationTerminationRequest rtReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"RegistrationTerminationRequest"<<rtReq << endl;
                        SendCxRegistrationTerminationAnswer(impl);
                    }
                    else
                    {
                        RegistrationTerminationAnswer rtAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"RegistrationTerminationAnswer" <<rtAns << endl;
                    }
                    break;
                case CX_UA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UserAuthorizationRequest uaReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserAuthorizationRequest" << uaReq << endl;
                        SendCxUserAuthorizationAnswer(impl);
                    }
                    else
                    {
                        UserAuthorizationAnswer uaAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UserAuthorizationAnswer" << uaAns << endl;
                    }
                    break;
                case CX_LI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        LocationInfoRequest liReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"LocationInfoRequest"<< liReq << endl;
                        SendCxLocationInfoAnswer(impl);
                    }
                    else
                    {
                        LocationInfoAnswer liAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"LocationInfoAnswer" << liAns << endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxCx);
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
 *      This function displays the menu options for the Cx interface
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
            cout << endl << "Select Cx.3GPP2 Command" <<endl << endl;
            cout << "1: UAR - User-Authorization-Request" << endl;
            cout << "2: SAR - Server Assignment Request" << endl;
            cout << "3: LIR - Location-Info-Request" << endl;
            cout << "4: MAR - Multimedia-Auth-Request" << endl;
            cout << "5: RTR - Registration Termination Request" << endl;
            cout << "6: PPR - Push-Profile-Request" << endl;
            cout << "7: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 7) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendCxUserAuthorizationRequest();
                    break;
                case 2:
                    SendCxServerAssignmentRequest();
                    break;
                case 3:
                    SendCxLocationInfoRequest();
                    break;
                case 4:
                    SendCxMultimediaAuthRequest();
                    break;
                case 5:
                    SendCxRegistrationTerminationRequest();
                    break;
                case 6:
                    SendCxPushProfileRequest();
                    break;
                case 7:
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
        if (CxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < CxStats::burstSize; i++)
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
            ftime(&CxStats::current);
            TIMERS_USleep(CxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((CxStats::current.time - CxStats::starter.time) >=
                 CxStats::duration)
            {
                if (CxStats::firstTime)
                {
                    ftime(&CxStats::sendComplete);
                    CxStats::sendTraffic = ITS_FALSE;
                    CxStats::firstTime = false;
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
    AppInitialize(CX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

