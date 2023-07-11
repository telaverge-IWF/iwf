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
 * LOG: $Log: sample_re.cpp,v $
 * LOG: Revision 1.1  2011/05/20 04:15:48  vkumara
 * LOG: Basline for Re interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_re.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_re.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $"

#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/re/PriceRequest.h>
#include <diameter/re/PriceResponse.h>
#include <diameter/re/TariffRequest.h>
#include <diameter/re/TariffResponse.h>
#include <diameter/re/ServiceUsageRequest.h>
#include <diameter/re/ServiceUsageResponse.h>

#include <app.h>
#include <re_defines.h>
#include <re_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::re;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRe)
{
    try
    {
        // Update the receive statistics
        ReStats::GetReStats()->UpdateRecvStats(impl->getCommandCode(), 
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
            case RE_PRICE_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    PriceRequest priceReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Price Request" << priceReq << endl;
                    SendRePriceResponse(impl);
                }
                else
                {
                    PriceResponse priceResp(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Price Response" << priceResp << endl;
                }
                break;
            case RE_TARIFF_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    TariffRequest trReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Tariff Request" << trReq<< endl;
                    SendReTariffResponse(impl);
                }
                else
                {
                    TariffResponse trResp(*impl);
                    if (appMode == UNIT_TEST)
                        cout << " Tariff Response" << trResp << endl;
                }
                break;
            case RE_SERVICEUSAGE_MSG_CMD_CODE:
                if (impl->isRequest())
                {
                    ServiceUsageRequest suReq(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Service Usage Request" << suReq << endl;
                    SendReServiceUsageResponse(impl);
                }
                else
                {
                    ServiceUsageResponse suResp(*impl);
                    if (appMode == UNIT_TEST)
                        cout << "Service Usage Response " << suResp << endl;
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
 *      This function displays the menu options for the Re interface
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
            cout << endl << "Select Re Command" <<endl << endl;
            cout << "1: PRQ - Price  Request" << endl;
            cout << "2: TRQ - Tariff Request" << endl;
            cout << "3: SUQ - Service Usage  Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 3) && ret!=99);
    
        try
        {
            switch (ret)
            {
                case 1:
                    SendRePriceRequest();
                    break;
                case 2:
                    SendReTariffRequest();
                    break;
                case 3:
                    SendReServiceUsageRequest();
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
        if (ReStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < ReStats::burstSize; i++)
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
            ftime(&ReStats::current);
            TIMERS_USleep(ReStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((ReStats::current.time - ReStats::starter.time) >=
                 ReStats::duration)
            {
                if (ReStats::firstTime)
                {
                    ftime(&ReStats::sendComplete);
                    ReStats::sendTraffic = ITS_FALSE;
                    ReStats::firstTime = false;
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
    AppInitialize(RE_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

