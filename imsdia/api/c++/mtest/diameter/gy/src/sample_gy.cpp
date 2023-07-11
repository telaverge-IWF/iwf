/**********************************-CPP-*************************************
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
 * LOG: $Log: sample_gy.cpp,v $
 * LOG: Revision 1.1  2011/03/10 09:27:34  vkumara
 * LOG: Sample Demo for Gy Interface
 * LOG:
 * LOG: Revision 3.2  2010/06/24 08:35:58  nvijikumar
 * LOG: Rel 8.10.0 updates
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:42:08  kamakshilk
 * LOG: Gy interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_gy.cpp,v 1.1 2011/03/10 09:27:34 vkumara Exp $
 ****************************************************************************/
#ident "$Id: sample_gy.cpp,v 1.1 2011/03/10 09:27:34 vkumara Exp $"

#include <dia_defines.h>
#include <app.h>

#include <gy_stats.h>
#include <gy_defines.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::gy;

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
        GyStats::GetGyStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case GY_CC_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        CreditControlRequest ccreq(*impl);
                        APP_TRACE_DEBUG((" Received CCR \n"));
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccreq" << ccreq << endl;
                        } 
                        SendGyCreditControlAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG((" Received CCA \n"));
                        CreditControlAnswer ccans(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccrsp" << ccans << endl;
                        } 

                        /* Release session context */
                        switch(ccans.getCCRequestType().value())
                        {
                            case CCRequestType::EVENT_REQUEST:
                                if (!IsDccaEnabled())
                                {
                                   std::string rlsStr =
                                               ccans.getSessionId().value();
                                   ReleaseSession(rlsStr, sIdxRfro);
                                }
                                break;
                            case CCRequestType::TERMINATION_REQUEST:
                                std::string rlsStr =
                                               ccans.getSessionId().value();
                                ReleaseSession(rlsStr, sIdxRfro);
                                break;
                        }
                    }
                    break;
                case BASE_ACCT_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                       ACRequest areq(*impl);
                       if (appMode == UNIT_TEST)
                       cout << endl << "Accounting Request Received"
                            << areq << endl;
                       SendGyACAnswer(impl);
                    }
                    else
                    {
                        ACAnswer aans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << endl << "Accounting Answer Received"
                        << aans << endl;
                    }
                    break;
                case BASE_RA_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                       ReAuthRequest rareq(*impl);
                       if (appMode == UNIT_TEST)
                       cout << endl << "Re Auth Request Received"
                            << rareq << endl;
                       SendGyRAAnswer(impl);
                    }
                    else
                    {
                        ReAuthAnswer raans(*impl);
                        if (appMode == UNIT_TEST)
                        cout << endl << "Re Auth  Answer Received"
                        << raans << endl;
                    }
                    break;
                    // Handle Base Messages
                //case BASE_ST_MSG_CMD_CODE:
                //case BASE_AS_MSG_CMD_CODE:
                   // HandleBaseMessages(impl,sIdxRfro);
                    //break;

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
 *      Gy interface.
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
        return SendGyACRequest(START);
    case 2:
        return SendGyACRequest(INTERIM);
    case 3:
        return SendGyACRequest(STOP);
    case 4:
        return SendGyACRequest(EVENT);
    case 5:
        return SendGyACRequest(START_AUTHSESS);
    case 6:
        return SendGyACRequest(EVENT_AUTHSESS);
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
            cout << endl << "Select Gy Command"<<endl<<endl;
            cout <<"1: CCR - Credit Control Request with  Initial "<<endl;
            cout <<"2: CCR - Credit Control Request with  Update"<<endl;
            cout <<"3: CCR - Credit Control Request with  Terminate"<<endl;
            cout <<"4: CCR - Credit Control Request Event Based "<<endl;
            cout <<"5: ACR - Accounting  Request Menu" << endl;
            cout <<"6: RAR - Re Auth Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
    
            ret=atoi(input.c_str());

        } while((ret < 1 || ret > 6) && ret != 99 );

        try
        { 
            switch (ret)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    SendGyCreditControlRequest(ret); 
                    break;
                case 5:
                    AccountingRequestMenu(); 
                    break;
                case 6:
                    SendGyRARequest();     
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
        if (GyStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < GyStats::burstSize; i++)
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
            ftime(&GyStats::current);

            TIMERS_USleep(GyStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((GyStats::current.time - GyStats::starter.time) >=
                 GyStats::duration)
            {
                if (GyStats::firstTime)
                {
                    ftime(&GyStats::sendComplete);
                    GyStats::sendTraffic = ITS_FALSE;
                    GyStats::firstTime = false;
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
    AppInitialize(GY_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}



