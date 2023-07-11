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
 ****************************************************************************
 * LOG: $Log: sample_s6d.cpp,v $
 * LOG: Revision 1.1  2011/05/04 10:46:01  vkumara
 * LOG: Baseline for S6d interface.
 * LOG:
 * LOG:
 * ID: $Id: sample_s6d.cpp,v 1.1 2011/05/04 10:46:01 vkumara Exp $
 ****************************************************************************/

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/s6d/UpdateLocation.h>
#include <diameter/s6d/AuthenticationInformation.h>
#include <diameter/s6d/CancelLocation.h>
#include <diameter/s6d/PurgeUE.h>
#include <diameter/s6d/DeleteSubscriberData.h>
#include <diameter/s6d/InsertSubscriberData.h>
#include <diameter/s6d/Reset.h>
#include <diameter/s6d/Notify.h>
#include <diameter/s6d/MEIdentityCheck.h>

#include <app.h>
#include <s6d_defines.h>
#include <s6d_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6d;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxS6D)
{
    try
    {
        // Update the receive statistics
        S6DStats::GetS6DStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case S6D_UL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UpdateLocationRequest udReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UpdateLocationRequest" << udReq << endl;
                        SendS6DUpdateLocationAnswer(impl);
                    }
                    else
                    {
                        UpdateLocationAnswer udAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UpdateLocationAnswer" << udAns << endl;
                    }
                    break;

		case S6D_AI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AuthenticationInformationRequest aiReq(*impl);
                      
                        if (appMode == UNIT_TEST)
                        cout <<endl<< "AuthenticationInformationRequest" << aiReq << endl;
                        SendS6DAuthenticationInformationAnswer(impl);
                    }
                    else
                    {
                        AuthenticationInformationAnswer aiAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AuthenticationInformationAnswer" << aiAns << endl;
                    }
                    break;
			
		case S6D_CL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CancelLocationRequest clReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "CancelLocationRequest" << clReq << endl;
                        SendS6DCancelLocationAnswer(impl);
                    }
                    else
                    {
                        CancelLocationAnswer clAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "CancelLocationAnswer" << clAns << endl;
                    }
                    break;

                 case S6D_PU_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PurgeUERequest puReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Purge UE Request" << puReq << endl;
                        SendS6DPurgeUEAnswer(impl);
                    }
                    else
                    {
                        PurgeUEAnswer puAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "PurgeUE Answer" << puAns << endl;
                    }
                    break;

                 case S6D_DS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DeleteSubscriberDataRequest dsReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Delete Subscriber Data  Request" << dsReq << endl;
                        SendS6DDeleteSubDataAnswer(impl);
                    }   
                    else
                    {   
                        DeleteSubscriberDataAnswer dsAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Delete Subscriber Data Answer" << dsAns << endl;
                    }   
                    break;
                case S6D_ID_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        InsertSubscriberDataRequest idReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Insert Subscriber Data  Request" << idReq << endl;
                        SendS6DInsertSubDataAnswer(impl);
                    }
                    else
                    {
                        InsertSubscriberDataAnswer idAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Insert Subscriber Data Answer" << idAns << endl;
                    }
                    break;    
                case S6D_RS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ResetRequest rReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Reset  Request" << rReq << endl;
                        SendS6DResetAnswer(impl);
                    }
                    else
                    {
                        ResetAnswer rAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Reset  Answer" << rAns << endl;
                    }
                    break;
                case S6D_NO_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        NotifyRequest nReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Notify  Request" << nReq << endl;
                        SendS6DNotifyAnswer(impl);
                    }
                    else
                    {
                        NotifyAnswer nAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Notify Answer" << nAns << endl;
                    }
                    break;
                case S6D_EC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        MEIdentityCheckRequest meReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "MEIdentityCheck  Request" << meReq << endl;
                        SendS6DMEIdCheckAnswer(impl);
                    }
                    else
                    {
                        MEIdentityCheckAnswer meAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "MEIdentityCheck Answer" << meAns << endl;
                    }
                    break;
                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxS6D);
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
 *      This function displays the menu options for the S6D interface
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
            cout << endl << "Select S6D Command" <<endl << endl;
            cout << "1:  ULR - User Location Request    " << endl;
            cout << "2:  AIR - Authentication Information Request   " << endl;
            cout << "3:  CLR - Cancel Location Request   " << endl;
            cout << "4:  PUR - Purge UE  Request   " << endl;
            cout << "5:  DSR - Delete Subscriber Data Request    " << endl;
            cout << "6:  IDR - Insert Subscriber Data Request    " << endl;
            cout << "7:  RSR - Reset  Request    " << endl;
            cout << "8:  NOR - Notify Request    " << endl;
            cout << "9:  ECR - MEIdentityCheck Request    " << endl;
            cout << "10:  To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 11) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendS6DUpdateLocationRequest();
                    break;
		case 2:
                    SendS6DAuthenticationInformationRequest();
                    break;
	
		case 3:
                    SendS6DCancelLocationRequest();
                    break;

                case 4:
                    SendS6DPurgeUERequest();
                    break;
                
                case 5:
                    SendS6DDeleteSubDataRequest();
                    break;
                
                case 6:
                    SendS6DInsertSubDataRequest();
                    break;
                case 7:
                    SendS6DResetRequest();
                    break;

                case 8:
                    SendS6DNotifyRequest();
                    break;

                case 9:
                    SendS6DMEIdCheckRequest();
                    break;

                case 10:
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
        if (S6DStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < S6DStats::burstSize; i++)
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
            ftime(&S6DStats::current);
            TIMERS_USleep(S6DStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((S6DStats::current.time - S6DStats::starter.time) >=
                 S6DStats::duration)
            {
                if (S6DStats::firstTime)
                {
                    ftime(&S6DStats::sendComplete);
                    S6DStats::sendTraffic = ITS_FALSE;
                    S6DStats::firstTime = false;
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
    AppInitialize(S6D_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

