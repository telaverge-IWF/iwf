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
 * LOG: $Log: sample_mip.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/08 14:15:24  hbhatnagar
 * LOG: made changes for the Accounting and clean up
 * LOG:
 * LOG: Revision 1.1  2007/01/01 15:18:50  hbhatnagar
 * LOG: adding the baseline demo application for the MobileIP
 * LOG:
 *
 * ID: $Id: sample_mip.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/mip/AAMobileNode.h>
#include <diameter/mip/HomeAgentMIP.h>
#include <diameter/mip/Accounting.h>

#include <app.h>
#include <mip_defines.h>
#include <mip_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::mip;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxMip)
{
    try
    {
        // Update the receive statistics
        MipStats::GetMipStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case MIP_AM_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AAMobileNodeRequest  amReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AAMobileNodeRequest" << amReq << endl;
                        SendMipAAMobileNodeAnswer(impl);
                    }
                    else
                    {
                        AAMobileNodeAnswer amAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AAMobileNodeAnswer" << amAns << endl;
                    }
                    break;

                case MIP_HA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        HomeAgentMIPRequest haReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "HomeAgentMIPRequest" << haReq<< endl;
                        SendMipHomeAgentMIPAnswer(impl);
                    }
                    else
                    {
                        HomeAgentMIPAnswer haAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "HomeAgentMIPAnswer" << haAns<< endl;
                    }
                    break;

                case MIP_AC_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AccountingRequest acReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AccountingRequest" << acReq<< endl;
                        SendMipAccountingAnswer(impl);
                    }
                    else
                    {
                        AccountingAnswer acAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AccountingAnswer" << acAns<< endl;
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxMip);
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
 *      This function displays the menu options for the Mip interface
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
            cout << endl << "Select Mip Command" <<endl << endl;
            cout << "1: AMR - AA Mobile Node Request" << endl;
            cout << "2: HAR - Home Agent MIP Request" << endl;
            cout << "3: ACR - MIP Accounting Request" << endl;
            cout << "4: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendMipAAMobileNodeRequest();
                    break;
                case 2:
                    SendMipHomeAgentMIPRequest();
                    break;
                case 3:
                    SendMipAccountingRequest();
                    break;
                case 4:
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
        if (MipStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < MipStats::burstSize; i++)
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
            ftime(&MipStats::current);
            TIMERS_USleep(MipStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((MipStats::current.time - MipStats::starter.time) >=
                 MipStats::duration)
            {
                if (MipStats::firstTime)
                {
                    ftime(&MipStats::sendComplete);
                    MipStats::sendTraffic = ITS_FALSE;
                    MipStats::firstTime = false;
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
    AppInitialize(MIP_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

