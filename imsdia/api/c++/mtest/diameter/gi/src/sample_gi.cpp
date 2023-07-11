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
 * LOG: $Log: sample_gi.cpp,v $
 * LOG: Revision 1.1  2011/05/26 08:57:24  vkumara
 * LOG: Baseline for Gi interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_gi.cpp,v 1.1 2011/05/26 08:57:24 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_gi.cpp,v 1.1 2011/05/26 08:57:24 vkumara Exp $"


#include <dia_defines.h>
#include <diameter/Exceptions.h>
#include <diameter/gi/AA.h>
#include <diameter/gi/AC.h>
#include <diameter/gi/ST.h>
#include <diameter/gi/ASR.h>
#include <diameter/gi/ASA.h>


#include <app.h>
#include <gi_defines.h>
#include <gi_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::gi;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxGi)
{
    try
    {
        // Update the receive statistics
        GiStats::GetGiStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case GI_AA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AARequest aaReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Request" << aaReq << endl;
                        SendGiAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AA-Answer" << aaAns << endl;
                    }
                    break;
                case GI_AC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ACRequest acReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AC-Request" << acReq << endl;
                        SendGiACAnswer(impl);
                    }
                    else
                    {
                        ACAnswer acAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AC-Answer" << acAns << endl;
                    }
                    break;
                case GI_ST_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        STRequest stReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Request" << stReq << endl;
                        SendGiSessionTerminationAnswer(impl);
                    }
                    else
                    {
                        STAnswer stAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Session-Termination-Answer" << stAns << endl;
                    }
                    break;
                case GI_AS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ASR asReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Request"<<asReq << endl;
                        SendGiAbortSessionAnswer(impl);
                    }
                    else
                    {
                        ASA asAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout <<"Abort-Session-Answer" <<asAns << endl;
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
 *      This function displays the menu options for the GI interface
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
        return SendGiACRequest(START);
    case 2:
        return SendGiACRequest(INTERIM);
    case 3:
        return SendGiACRequest(STOP);
    case 4:
        return SendGiACRequest(EVENT);
    case 5:
        return SendGiACRequest(START_AUTHSESS);
    case 6:
        return SendGiACRequest(EVENT_AUTHSESS);
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
            cout << endl << "Select GI Command" <<endl << endl;
            cout << "1: AAR - AA-Request" << endl;
            cout << "2: ACR - AC-Request" << endl;
            cout << "3: STR - Session-Termination-Request" << endl;
            cout << "4: ASR - Abort-Session-Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendGiAARequest();
                    break;
                case 2:
                    AccountingRequestMenu();
                    break;
                case 3:
                    SendGiSessionTerminationRequest();
                    break;
                case 4:
                    SendGiAbortSessionRequest();
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
        if (GiStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < GiStats::burstSize; i++)
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
            ftime(&GiStats::current);
            TIMERS_USleep(GiStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((GiStats::current.time - GiStats::starter.time) >=
                 GiStats::duration)
            {
                if (GiStats::firstTime)
                {
                    ftime(&GiStats::sendComplete);
                    GiStats::sendTraffic = ITS_FALSE;
                    GiStats::firstTime = false;
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
    AppInitialize(GI_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

