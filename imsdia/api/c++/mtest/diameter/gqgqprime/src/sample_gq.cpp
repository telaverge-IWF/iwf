/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: sample_gq.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_gq.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_gq.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <dia_defines.h>

#include <diameter/gqgqprime/AA.h>
#include <diameter/gqgqprime/AS.h>
#include <diameter/gqgqprime/RA.h>
#include <diameter/gqgqprime/ST.h>

#include <app.h>
#include <gq_defines.h>
#include <gq_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::gqgqprime;

/*  implementation: public
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxGq)
{
    try
    {
        // Update the receive statistics
        GqgqStats::GetGqgqStats()->UpdateRecvStats(impl->getCommandCode(), 
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
                case GQGQ_AA_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        AARequest aareq(*impl);
                        cout << "AARequest " << aareq << endl;
                        SendGqAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaans(*impl);
                        cout << "AAAnswer " << aaans << endl;
                    }
                    break;

                case GQGQ_RA_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        RARequest rareq(*impl);
                        cout << "RARequest" << rareq << endl;
                        SendGqRAAnswer(impl);
                    }
                    else
                    {
                        RAAnswer raans(*impl);
                        cout << "RAAnswer" << raans << endl;
                    }
                    break;

                case GQGQ_ST_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        STRequest streq(*impl);
                        cout << "STRequest" << streq << endl;

                        SendGqSTAnswer(impl);
                    }
                    else
                    {
                        STAnswer stans(*impl);
                        cout << "STAnswer" << stans << endl;
                    }
                    break;

                case GQGQ_AS_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        ASRequest asreq(*impl);
                        cout << "ASRequest" << asreq << endl;

                        SendGqASAnswer(impl);
                    }
                    else
                    {
                        ASAnswer asans(*impl);
                        cout << "ASAnswer" << asans << endl;
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

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      Gqgq prime protocol interface.
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
 *      Returns the option selected.
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
            cout << endl << "Select GqGq' Command" <<endl << endl;
            cout << "1: AAR - AA Request" << endl;
            cout << "2: RAR - Re-Auth Request" << endl;
            cout << "3: STR - Session Termination Request" << endl;
            cout << "4: ASR - Abort Session Request" << endl;
            cout << "99: To Previous Menu" << endl;
  
            cin >> input;

            ret = atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        try
        {
            switch(ret)
            {
                case 1:
                    SendGqAARequest();
                    break;
                case 2:
                    SendGqRARequest();
                    break;
                case 3:
                    SendGqSTRequest();
                    break;
                case 4:
                    SendGqASRequest();
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
        if (GqgqStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < GqgqStats::burstSize; i++)
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
            ftime(&GqgqStats::current);
            TIMERS_USleep(GqgqStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((GqgqStats::current.time - GqgqStats::starter.time) >=
                 GqgqStats::duration)
            {
                if (GqgqStats::firstTime)
                {
                    ftime(&GqgqStats::sendComplete);
                    GqgqStats::sendTraffic = ITS_FALSE;
                    GqgqStats::firstTime = false;
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
    AppInitialize(GQGQ_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

