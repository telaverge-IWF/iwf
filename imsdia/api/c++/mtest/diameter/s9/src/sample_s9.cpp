/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: sample_s9.cpp,v $
 * LOG: Revision 1.1  2010/04/22 11:12:53  nvijikumar
 * LOG: sample Application for S9 interface
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_s9.cpp,v 1.1 2010/04/22 11:12:53 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/s9/CC.h>
#include <diameter/s9/RA.h>

#include <app.h>
#include <s9_defines.h>
#include <s9_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::s9;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxS9)
{
    try
    {
        S9Stats::GetS9Stats()->UpdateRecvStats(impl->getCommandCode(),
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
                case S9_CC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CCRequest ccReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Credit Control " << ccReq << endl;
                        SendS9CCAnswer(impl);
                    }
                    else
                    {
                        CCAnswer ccAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Credit Control Answer" << ccAns << endl;

                        /* Release session context */
                        switch(ccAns.getCCRequestType().value())
                        {
                            case CCRequestType::EVENT_REQUEST:
                                if (!IsDccaEnabled())
                                {
                                   std::string rlsStr =
                                               ccAns.getSessionId().value();
                                   ReleaseSession(rlsStr, sIdxS9);
                                }
                                break;
                            case CCRequestType::TERMINATION_REQUEST:
                                std::string rlsStr =
                                               ccAns.getSessionId().value();
                                ReleaseSession(rlsStr, sIdxS9);
                                break;
                        }
                    }
                    break;

                case S9_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RARequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Re Auth Request" << raReq<< endl;
                        SendS9RAAnswer(impl);
                    }
                    else
                    {
                        RAAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Re Auth Answer" << raAns<< endl;
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
 *      This function displays the menu options for the S9 interface
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
            cout << endl << "Select S9 Command" <<endl << endl;
            cout << "1: CCR - Credit Control Request" << endl;
            cout << "2: RAR - Re Auth Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
    
            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 2) && ret!=99);

        try
        { 
            switch (ret)
            {
            case 1:
                SendS9CCRequest();
                break;
            case 2:
                SendS9RARequest();
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
        if (S9Stats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < S9Stats::burstSize; i++)
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
            ftime(&S9Stats::current);

            TIMERS_USleep(S9Stats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((S9Stats::current.time - S9Stats::starter.time) >=
                 S9Stats::duration)
            {
                if (S9Stats::firstTime)
                {
                    ftime(&S9Stats::sendComplete);
                    S9Stats::sendTraffic = ITS_FALSE;
                    S9Stats::firstTime = false;
                    time(&tx);
                    temp = localtime_r(&tx, &tbuf);
                    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
                    cout << "Test stopped sending traffic at ----->"
                         << buff << endl;
               }
           }
       }
       else
       {
           TIMERS_Sleep(1);
       }
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
    AppInitialize(S9_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

