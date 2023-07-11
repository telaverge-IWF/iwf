/**********************************-CPP-*************************************
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
 * LOG: $Log: sample_rw.cpp,v $
 * LOG: Revision 1.1  2011/07/14 11:51:38  vkumara
 * LOG: Baseline for Rw interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_rw.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_rw.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <rw_stats.h>
#include <rw_defines.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::rw;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handles the message received from the base
 *      diameter stack. This identifies the commands
 *      in the message and processes that command.
 *
 *  Input Parameters:
 *      ITS_Event& ev: ITS_Event
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxRfro)
{
    try
    {
        RwStats::GetRwStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case RW_CC_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        CCRequest ccreq(*impl);
                        APP_TRACE_DEBUG((" Received CCR \n"));
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccreq" << ccreq << endl;
                        } 
                        SendRwCCAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG((" Received CCA \n"));
                        CCAnswer ccans(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccrsp" << ccans << endl;
                        } 
                    }
                    break;
                case RW_PI_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                       PIRequest pireq(*impl);
                       if (appMode == UNIT_TEST)
                       cout << endl << "PI Request Received"
                            << pireq << endl;
                       SendRwPIAnswer(impl);
                    }
                    else
                    {
                        PIAnswer pians(*impl);
                        if (appMode == UNIT_TEST)
                        cout << endl << "PI  Answer Received"
                        << pians << endl;
                    }
                    break;
                case RW_RA_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                       RARequest rareq(*impl);
                       if (appMode == UNIT_TEST)
                       cout << endl << "Re Auth Request Received"
                            << rareq << endl;
                       SendRwRAAnswer(impl);
                    }
                    else
                    {
                        RAAnswer raans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << endl << "Re Auth  Answer Received"
                        << raans << endl;
                    }
                    break;

 		 case RW_AS_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                       ASRequest asreq(*impl);
                       if (appMode == UNIT_TEST)
                       cout << endl << "AS  Request Received"
                            << asreq << endl;
                       SendRwAbortSessionAnswer(impl);
                    }
                    else
                    {
                        ASAnswer asans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << endl << "AS  Answer Received"
                        << asans << endl;
                    }
                    break;
                    // Handle Base Messages
                    case BASE_ST_MSG_CMD_CODE:
                          HandleBaseMessages(impl,sIdxRfro);
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
 *      Rw interface.
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
            cout << endl << "Select Rw Command"<<endl<<endl;
            cout <<"1: CCR - Credit Control Request with  Initial "<<endl;
            cout <<"2: CCR - Credit Control Request with  Update"<<endl;
            cout <<"3: CCR - Credit Control Request with  Terminate"<<endl;
            cout <<"4: CCR - Credit Control Request Event Based "<<endl;
            cout <<"5: PIR - PI Request " << endl;
            cout <<"6: RAR - Re Auth Request" << endl;
            cout <<"7: ASR - AS  Request" << endl;
            cout <<"99: To Previous Menu" << endl;

            cin >> input;
    
            ret=atoi(input.c_str());

        } while((ret < 1 || ret > 7) && ret != 99 );

        try
        { 
            switch (ret)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    SendRwCCRequest(ret); 
                    break;
                case 5:
                   SendRwPIRequest(); 
                    break;
                case 6:
                    SendRwRARequest();  
                    break;
                case 7:
                    SendRwAbortSessionRequest();
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
        if (RwStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < RwStats::burstSize; i++)
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
            ftime(&RwStats::current);

            TIMERS_USleep(RwStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((RwStats::current.time - RwStats::starter.time) >=
                 RwStats::duration)
            {
                if (RwStats::firstTime)
                {
                    ftime(&RwStats::sendComplete);
                    RwStats::sendTraffic = ITS_FALSE;
                    RwStats::firstTime = false;
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
    AppInitialize(RW_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}



