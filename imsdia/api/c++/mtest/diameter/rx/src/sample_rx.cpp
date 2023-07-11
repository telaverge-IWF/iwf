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
 * LOG: $Log: sample_rx.cpp,v $
 * LOG: Revision 3.2  2010/08/04 10:30:12  nvijikumar
 * LOG: Load capability for RX interface
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:12  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/12/19 09:10:07  kamakshilk
 * LOG: New architecture for static and distributed
 * LOG:
 * LOG: Revision 2.2  2006/10/18 04:54:47  tpanda
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/08/04 17:55:37  nvijikumar
 * LOG: Changes for update the stats for all messages and
 * LOG: fix for solaris CC compilation issue.
 * LOG:
 * LOG: Revision 1.1  2006/07/24 15:28:20  nvijikumar
 * LOG: Baseline demo application for Rx Interface.
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_rx.cpp,v 3.2 2010/08/04 10:30:12 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/rx/AA.h>
#include <diameter/rx/RA.h>
#include <diameter/rx/AS.h>
#include <diameter/rx/ST.h>

#include <app.h>
#include <rx_defines.h>
#include <rx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rx;

time_t t1,temp, tx;
static time_t preTime;
struct tm tbuf, *temp1;;
char buff[80];

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRx)
{
    try
    {
        // Update the receive statistics
        RxStats::GetRxStats()->UpdateRecvStats(impl->getCommandCode(), 
                                               impl->isRequest());
        // Process the commands based on the command code.
        if(impl->isError())
        {
           HandleErrorResponse(impl);
        }
        else
        {
//////////// TPS //////////////
            static int msgCount;
            msgCount++;
            int mps =0;

            if (msgCount == 1)
            {
                time(&preTime);
            }
            if((msgCount % 20000) == 0)
            {
                time(&t1);
                if (t1 != preTime)
                {
                    mps = (20000*2)/(t1-preTime);
                    time(&tx);
                    temp1 =  localtime_r(&tx, &tbuf);
                    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
                    std::cout <<"Previus Msg received at ----->" << buff << std::endl;
                    printf("MPS(Msg per sec): %d Total Msg =%d\n", mps, msgCount);
                    preTime = t1;
                    fflush(stdout);
                }
            }
//////////// TPS //////////////

        }
        switch (impl->getCommandCode())
        {
            case RX_AA_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    AARequest aaReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "AA Request" << aaReq << endl;
                    SendRxAAAnswer(impl);
                }
                else
                {
                    AAAnswer aaAns(*impl);
                    if (appMode == UNIT_TEST)
                    {
                        cout << "AA Answer" << aaAns << endl;
                    }
                    else
                    {
                        const SessionId &sesId=aaAns.getSessionId();
                        SendRxSTRequest(&sesId);
                    }

                }
                break;
            case RX_AS_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    ASRequest asReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Abort Session Request" << asReq<< endl;
                    SendRxASAnswer(impl);
                }
                else
                {
                    ASAnswer asAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Abort Session Answer" << asAns<< endl;
                }
                break;
            case RX_RA_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    RARequest raReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "RA Request" << raReq << endl;
                    SendRxRAAnswer(impl);
                }
                else
                {
                    RAAnswer raAns(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "RA Answer" << raAns << endl;
                }
                break;
            case RX_ST_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    STRequest stReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "ST Request" << stReq << endl;
                    SendRxSTAnswer(impl);
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
 *      This function displays the menu options for the Rx interface
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
            cout << endl << "Select Rx Command" <<endl << endl;
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
                    SendRxAARequest();
                    break;
                case 2:
                    SendRxRARequest();
                    break;
                case 3:
                    SendRxSTRequest();
                    break;
                case 4:
                    SendRxASRequest();
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
        if (RxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < RxStats::burstSize; i++)
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
            ftime(&RxStats::current);
            TIMERS_USleep(RxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((RxStats::current.time - RxStats::starter.time) >=
                 RxStats::duration)
            {
                if (RxStats::firstTime)
                {
                    ftime(&RxStats::sendComplete);
                    RxStats::sendTraffic = ITS_FALSE;
                    RxStats::firstTime = false;
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
    AppInitialize(RX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

