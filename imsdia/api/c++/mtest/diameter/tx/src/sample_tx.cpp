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
 * LOG: $Log: sample_tx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/12/19 08:54:50  kamakshilk
 * LOG: New architecture to work with static and distributed.
 * LOG:
 * LOG: Revision 2.3  2006/11/02 11:59:40  kamakshilk
 * LOG: Uncommented Send STA and ASA
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:08:01  kamakshilk
 * LOG: Merging with ITSDiameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/08/04 17:52:51  nvijikumar
 * LOG: 1. Changes to update the stats for all messgaes.
 * LOG: 2. Fix for solaris compilation issue.
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG: 
 *
 * ID: $Id: sample_tx.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/tx/AA.h>
#include <diameter/tx/AS.h>
#include <diameter/tx/RA.h>
#include <diameter/tx/ST.h>

#include <app.h>
#include <tx_defines.h>
#include <tx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::tx;

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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxTx)
{
    try
    {
        // Update the receive statistics
        TxStats::GetTxStats()->UpdateRecvStats(impl->getCommandCode(), 
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
                case TX_AA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AARequest aaReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "AARequest" << aaReq << endl;
                        SendTxAAAnswer(impl);
                    }
                    else
                    {
                        AAAnswer aaAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "AAAnswer" << aaAns << endl;
                    }
                    break;
   
                case TX_RA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        RARequest raReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "RARequest" << raReq << endl;
                        SendTxRAAnswer(impl);
                    }
                    else
                    {
                        RAAnswer raAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "RAAnswer" << raAns << endl;
                    }
                    break;
   
                case TX_ST_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        STRequest stReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "STRequest" << stReq << endl;
                        SendTxSTAnswer(impl);
                    }
                    else
                    {
                        STAnswer stAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "STAnswer" << stAns << endl;
                    }
                    break;

                case TX_AS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ASRequest asReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ASRequest" << asReq<< endl;
                        SendTxASAnswer(impl);
                    }
                    else
                    {
                        ASAnswer asAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "ASAnswer" << asAns<< endl;
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
 *      This function displays the menu options for the Tx interface
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
            cout << endl << "Select Tx Command" <<endl << endl;
            cout << "1: AAR - AA Request" << endl;
            cout << "2: RAR - Re-Auth Request" << endl;
            cout << "3: STR - Session Termination Request" << endl;
            cout << "4: ASR - Abort Session Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);
    
        try
        {
            switch (ret)
            {
                case 1:
                    SendTxAARequest();
                    break;
                case 2:
                    SendTxRARequest();
                    break;
                case 3:
                    SendTxSTRequest();
                    break;
                case 4:
                    SendTxASRequest();
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
        if (TxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < TxStats::burstSize; i++)
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
            ftime(&TxStats::current);
            TIMERS_USleep(TxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((TxStats::current.time - TxStats::starter.time) >=
                 TxStats::duration)
            {
                if (TxStats::firstTime)
                {
                    ftime(&TxStats::sendComplete);
                    TxStats::sendTraffic = ITS_FALSE;
                    TxStats::firstTime = false;
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
    AppInitialize(TX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

