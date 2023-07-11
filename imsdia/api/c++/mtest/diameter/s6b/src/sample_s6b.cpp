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
 * LOG: $Log: sample_s6b.cpp,v $
 * LOG: Revision 1.1  2011/04/27 12:14:12  vkumara
 * LOG: Draft for S6b interface.
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: sample_s6b.cpp,v 1.1 2011/04/27 12:14:12 vkumara Exp $"

#include <dia_defines.h>
#include <diameter/Exceptions.h>
#include <diameter/s6b/AA.h>
#include <diameter/s6b/ReAuth.h>
#include <diameter/s6b/SessionTermination.h>
#include <diameter/s6b/AbortSession.h>
#include <diameter/s6b/DiameterEAP.h>


#include <app.h>
#include <s6b_defines.h>
#include <s6b_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6b;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxS6b)
{
    try
    {
        // Update the receive statistics
        S6bStats::GetS6bStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case S6B_AA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AARequest aaReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Request" << aaReq << endl;
                        SendS6bAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Answer" << aaAns << endl;
                    }
                    break;
                case S6B_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ReAuthRequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Request" << raReq<< endl;
                        SendS6bReAuthAnswer(impl);
                    }
                    else
                    {
                        ReAuthAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Re-Auth-Answer" << raAns<< endl;
                    }
                    break;

                case S6B_ST_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        SessionTerminationRequest stReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Request" << stReq << endl;
                        SendS6bSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        SessionTerminationAnswer stAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Answer" << stAns << endl;
                    }
                    break;
                case S6B_AS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AbortSessionRequest asReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Request"<<asReq << endl;
                        SendS6bAbortSessionAnswer(impl);
                    }
                    else
                    {
                        AbortSessionAnswer asAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Answer" <<asAns << endl;
                    }
                    break;
                case S6B_DE_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DiameterEAPRequest DerReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Diameter-EAP-Request" << DerReq << endl;
                        SendS6bDiameterEAPAnswer(impl);
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
 *      This function displays the menu options for the S6B interface
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
            cout << endl << "Select S6B Command" <<endl << endl;
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
                    SendS6bAARequest();
                    break;
                case 2:
                    SendS6bReAuthRequest();
                    break;
                case 3:
                    SendS6bSessionTerminationRequest();
                    break;
                case 4:
                    SendS6bAbortSessionRequest();
                    break;
                case 5:
                    SendS6bDiameterEAPRequest();
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
        if (S6bStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < S6bStats::burstSize; i++)
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
            ftime(&S6bStats::current);
            TIMERS_USleep(S6bStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((S6bStats::current.time - S6bStats::starter.time) >=
                 S6bStats::duration)
            {
                if (S6bStats::firstTime)
                {
                    ftime(&S6bStats::sendComplete);
                    S6bStats::sendTraffic = ITS_FALSE;
                    S6bStats::firstTime = false;
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
    AppInitialize(S6B_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

