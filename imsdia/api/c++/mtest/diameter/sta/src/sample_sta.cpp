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
 * LOG: $Log: sample_sta.cpp,v $
 * LOG: Revision 1.1  2011/04/27 12:01:40  vkumara
 * LOG: Draft version for STA sample app
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: sample_sta.cpp,v 1.1 2011/04/27 12:01:40 vkumara Exp $"

#include <dia_defines.h>
#include <diameter/Exceptions.h>
#include <diameter/sta/AA.h>
#include <diameter/sta/ReAuth.h>
#include <diameter/sta/SessionTermination.h>
#include <diameter/sta/AbortSession.h>
#include <diameter/sta/DiameterEAP.h>


#include <app.h>
#include <sta_defines.h>
#include <sta_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::sta;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxSTa)
{
    try
    {
        // Update the receive statistics
        STaStats::GetSTaStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case STA_AA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AARequest aaReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Request" << aaReq << endl;
                        SendSTaAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Answer" << aaAns << endl;
                    }
                    break;
                case STA_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ReAuthRequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Request" << raReq<< endl;
                        SendSTaReAuthAnswer(impl);
                    }
                    else
                    {
                        ReAuthAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Answer" << raAns<< endl;
                    }
                    break;

                case STA_ST_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        SessionTerminationRequest stReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Request" << stReq << endl;
                        SendSTaSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        SessionTerminationAnswer stAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Answer" << stAns << endl;
                    }
                    break;
                case STA_AS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AbortSessionRequest asReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Request"<<asReq << endl;
                        SendSTaAbortSessionAnswer(impl);
                    }
                    else
                    {
                        AbortSessionAnswer asAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Answer" <<asAns << endl;
                    }
                    break;
                case STA_DE_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DiameterEAPRequest DerReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Diameter-EAP-Request" << DerReq << endl;
                        SendSTaDiameterEAPAnswer(impl);
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
 *      This function displays the menu options for the STA interface
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
            cout << endl << "Select STA Command" <<endl << endl;
            cout << "1: AAR - AA-Request" << endl;
            cout << "2: RAR - Re-Auth-Request" << endl;
            cout << "3: STR - Session-Termination-Request" << endl;
            cout << "4: ASR - Abort-Session-Request" << endl;
            cout << "5: DER - Diameter-EAP-Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 5) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendSTaAARequest();
                    break;
                case 2:
                    SendSTaReAuthRequest();
                    break;
                case 3:
                    SendSTaSessionTerminationRequest();
                    break;
                case 4:
                    SendSTaAbortSessionRequest();
                    break;
                case 5:
                    SendSTaDiameterEAPRequest();
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
        if (STaStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < STaStats::burstSize; i++)
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
            ftime(&STaStats::current);
            TIMERS_USleep(STaStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((STaStats::current.time - STaStats::starter.time) >=
                 STaStats::duration)
            {
                if (STaStats::firstTime)
                {
                    ftime(&STaStats::sendComplete);
                    STaStats::sendTraffic = ITS_FALSE;
                    STaStats::firstTime = false;
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
    AppInitialize(STA_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

