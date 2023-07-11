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
 * LOG: $Log: sample_gx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/12/19 09:06:07  kamakshilk
 * LOG: New architecture to work with static and distributed
 * LOG:
 * LOG: Revision 2.2  2006/10/16 13:19:32  tpanda
 * LOG: Merging with ITSDIAMETER
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/08/04 17:59:25  nvijikumar
 * LOG: Fix for solaris CC compilation issue and stats updation changes.
 * LOG:
 * LOG: Revision 1.1  2006/07/24 14:38:10  nvijikumar
 * LOG: Baseline demo application for Gx Interface.
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_gx.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/gx/CC.h>
#include <diameter/gx/RA.h>

#include <app.h>
#include <gx_defines.h>
#include <gx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::gx;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxGx)
{
    try
    {
        GxStats::GetGxStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case GX_CC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CCRequest ccReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Credit Control " << ccReq << endl;
                        SendGxCCAnswer(impl);
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
                                   ReleaseSession(rlsStr, sIdxGx);
                                }
                                break;
                            case CCRequestType::TERMINATION_REQUEST:
                                std::string rlsStr =
                                               ccAns.getSessionId().value();
                                ReleaseSession(rlsStr, sIdxGx);
                                break;
                        }
                    }
                    break;

                case GX_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RARequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Re Auth Request" << raReq<< endl;
                        SendGxRAAnswer(impl);
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
 *      This function displays the menu options for the Gx interface
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
            cout << endl << "Select Gx Command" <<endl << endl;
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
                SendGxCCRequest();
                break;
            case 2:
                SendGxRARequest();
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
        if (GxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < GxStats::burstSize; i++)
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
            ftime(&GxStats::current);

            TIMERS_USleep(GxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((GxStats::current.time - GxStats::starter.time) >=
                 GxStats::duration)
            {
                if (GxStats::firstTime)
                {
                    ftime(&GxStats::sendComplete);
                    GxStats::sendTraffic = ITS_FALSE;
                    GxStats::firstTime = false;
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
    AppInitialize(GX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

