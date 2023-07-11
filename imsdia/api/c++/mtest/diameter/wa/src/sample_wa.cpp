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
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: sample_wa.cpp,v 1.1 2011/04/18 09:44:11 vkumara Exp $"

#include <dia_defines.h>
#include <diameter/Exceptions.h>
#include <diameter/wa/AA.h>
#include <diameter/wa/AC.h>
#include <diameter/wa/ReAuth.h>
#include <diameter/wa/SessionTermination.h>
#include <diameter/wa/AbortSession.h>
#include <diameter/wa/DiameterEAP.h>


#include <app.h>
#include <wa_defines.h>
#include <wa_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::wa;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxWa)
{
    try
    {
        // Update the receive statistics
        WaStats::GetWaStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case WA_AA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AARequest aaReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Request" << aaReq << endl;
                        SendWaAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Answer" << aaAns << endl;
                    }
                    break;
                case WA_AC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ACRequest acReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AC-Request" << acReq << endl;
                        SendWaACAnswer(impl);
                    }
                    else
                    {
                        ACAnswer acAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AC-Answer" << acAns << endl;
                    }
                    break;
                case WA_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ReAuthRequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Request" << raReq<< endl;
                        SendWaReAuthAnswer(impl);
                    }
                    else
                    {
                        ReAuthAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Answer" << raAns<< endl;
                    }
                    break;

                case WA_ST_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        SessionTerminationRequest stReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Request" << stReq << endl;
                        SendWaSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        SessionTerminationAnswer stAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Answer" << stAns << endl;
                    }
                    break;
                case WA_AS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AbortSessionRequest asReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Request"<<asReq << endl;
                        SendWaAbortSessionAnswer(impl);
                    }
                    else
                    {
                        AbortSessionAnswer asAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Answer" <<asAns << endl;
                    }
                    break;
                case WA_DE_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DiameterEAPRequest DerReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Diameter-EAP-Request" << DerReq << endl;
                        SendWaDiameterEAPAnswer(impl);
                    }
                    else
                    {
                        DiameterEAPAnswer DerAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Diameter-EAP-Answer" << DerAns << endl;
                    }
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
 *      This function displays the menu options for the WA interface
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

int
AccountingRequestMenu()
{
    string input;
    int ret = 0;
    do
    {
        cout << "Enter your choice to send the following Accounting Messages"
             << endl << endl;
        cout << endl << " (1) . Accounting START Request"   << endl;
        cout << endl << " (2) . Accounting INTERIM Request" << endl;
        cout << endl << " (3) . Accounting STOP Request"    << endl;
        cout << endl << " (4) . Accounting EVENT Request"   << endl;
        cout << endl << " (5) . Accounting START Request on Auth session"<<endl;
        cout << endl << " (6) . Accounting EVENT Request on Auth session"<<endl;
        cout << endl << "(99) . Exit" << endl;

        cin >> input;
        ret = atoi(input.c_str());

    } while ((ret < 1 || ret > 6) && ret!=99);

    switch(ret)
    {
    case 1:
        return SendWaACRequest(START);
    case 2:
        return SendWaACRequest(INTERIM);
    case 3:
        return SendWaACRequest(STOP);
    case 4:
        return SendWaACRequest(EVENT);
    case 5:
        return SendWaACRequest(START_AUTHSESS);
    case 6:
        return SendWaACRequest(EVENT_AUTHSESS);
    default:
        cout << endl << "Invalid choice";
        break;
    }
    return 0;
}


int DisplayAppMenu()
{
    string input;
    int ret = 0;

    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select WA Command" <<endl << endl;
            cout << "1: AAR - AA-Request" << endl;
            cout << "2: ACR - AC-Request" << endl;
            cout << "3: RAR - Re-Auth-Request" << endl;
            cout << "4: STR - Session-Termination-Request" << endl;
            cout << "5: ASR - Abort-Session-Request" << endl;
            cout << "6: DER - Diameter-EAP-Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 6) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendWaAARequest();
                    break;
                case 2:
                    AccountingRequestMenu();
                    break;
                case 3:
                    SendWaReAuthRequest();
                    break;
                case 4:
                    SendWaSessionTerminationRequest();
                    break;
                case 5:
                    SendWaAbortSessionRequest();
                    break;
                case 6:
                    SendWaDiameterEAPRequest();
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
        if (WaStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < WaStats::burstSize; i++)
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
            ftime(&WaStats::current);
            TIMERS_USleep(WaStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((WaStats::current.time - WaStats::starter.time) >=
                 WaStats::duration)
            {
                if (WaStats::firstTime)
                {
                    ftime(&WaStats::sendComplete);
                    WaStats::sendTraffic = ITS_FALSE;
                    WaStats::firstTime = false;
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
    AppInitialize(WA_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

