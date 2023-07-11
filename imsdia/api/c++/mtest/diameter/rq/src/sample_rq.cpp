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
 * LOG: $Log: sample_rq.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/12 13:40:50  hbhatnagar
 * LOG: placed the missing else in HandleDiaAppMsg
 * LOG:
 * LOG: Revision 1.1  2007/01/08 07:41:35  hbhatnagar
 * LOG: baseline demo application for rq interface for static and distributed mode.
 * LOG:
 *
 * ID: $Id: sample_rq.cpp,v 3.1 2008/03/31 10:33:11 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/rq/AA.h>
#include <diameter/rq/RA.h>
#include <diameter/rq/AS.h>
#include <diameter/rq/ST.h>

#include <app.h>
#include <rq_defines.h>
#include <rq_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rq;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function processes the message received from the base
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRq)
{
    try
    {
        // Update the receive statistics
        RqStats::GetRqStats()->UpdateRecvStats(impl->getCommandCode(), 
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
            case RQ_AA_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    AARequest aaReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "AA Request" << aaReq << endl;
                    SendRqAAAnswer(impl);
                }
                else
                {
                    AAAnswer aaAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "AA Answer" << aaAns << endl;
                }
                break;
            case RQ_AS_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    ASRequest asReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Abort Session Request" << asReq<< endl;
                    SendRqASAnswer(impl);
                }
                else
                {
                    ASAnswer asAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Abort Session Answer" << asAns<< endl;
                }
                break;
            case RQ_RA_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    RARequest raReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "RA Request" << raReq << endl;
                    SendRqRAAnswer(impl);
                }
                else
                {
                    RAAnswer raAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "RA Answer" << raAns << endl;
                }
                break;
            case RQ_ST_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    STRequest stReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "ST Request" << stReq << endl;
                    SendRqSTAnswer(impl);
                }
                else
                {
                    STAnswer stAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "ST Answer" << stAns << endl;
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
 *      This function displays the menu options for the Rq interface
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
            cout << endl << "Select Rq Command" <<endl << endl;
            cout << "1: AA - AA Request" << endl;
            cout << "2: RA - Re Auth Request" << endl;
            cout << "3: ST - Session Termination Request" << endl;
            cout << "4: AS - Abort Session Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);
    
        try
        {
            switch (ret)
            {
                case 1:
                    SendRqAARequest();
                    break;
                case 2:
                    SendRqRARequest();
                    break;
                case 3:
                    SendRqSTRequest();
                    break;
                case 4:
                    SendRqASRequest();
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
        if (RqStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < RqStats::burstSize; i++)
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
            ftime(&RqStats::current);
            TIMERS_USleep(RqStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((RqStats::current.time - RqStats::starter.time) >=
                 RqStats::duration)
            {
                if (RqStats::firstTime)
                {
                    ftime(&RqStats::sendComplete);
                    RqStats::sendTraffic = ITS_FALSE;
                    RqStats::firstTime = false;
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
    AppInitialize(RQ_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

