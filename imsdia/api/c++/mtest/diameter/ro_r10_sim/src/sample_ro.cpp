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
 * LOG: $Log: sample_ro.cpp,v $
 * LOG: Revision 1.1.4.2  2014/02/12 07:59:41  millayaraja
 * LOG: testapp for IWF performance
 * LOG:
 * LOG: Revision 1.1.2.2  2014/02/12 07:54:07  millayaraja
 * LOG: test app for IWF testing
 * LOG:
 * LOG: Revision 1.1.2.1  2013/08/21 11:36:41  jkchaitanya
 * LOG: sub directories in ro_r10_sim
 * LOG:
 * LOG: Revision 1.1.2.2  2013/07/09 11:08:35  jkchaitanya
 * LOG: changes for supporting json configuration for ro_r10 tool
 * LOG:
 * LOG: Revision 1.1.2.1  2013/07/03 06:32:43  jkchaitanya
 * LOG: changes for ro release 10 test tool changes and make file changes
 * LOG:
 * LOG: Revision 3.2  2010/06/24 08:35:58  nvijikumar
 * LOG: Rel 8.10.0 updates
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:42:08  kamakshilk
 * LOG: ro interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_ro.cpp,v 1.1.4.2 2014/02/12 07:59:41 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: sample_ro.cpp,v 1.1.4.2 2014/02/12 07:59:41 millayaraja Exp $"

#include <dia_defines.h>
#include <app.h>

#include <ro_stats.h>
#include <ro_defines.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::ro_r10;
//using namespace diameter::ro::ims;

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
int HandleDiaAppMsg(const DIA_BASE_CMD *bCmd, const diameter::CommandImpl *impl, unsigned int &sIdxro)
{
    try
    {
        RoStats::GetRoStats()->UpdateRecvStats(bCmd->getCommandCode(),
                                                   bCmd->isRequest());
        // Process the commands based on the command code.
        if(bCmd->isError())
        {
            HandleErrorResponse(bCmd);
        }
        else
        {
            switch (impl->getCommandCode())
            {
                case RO_CC_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        CreditControlRequest ccreq(*impl);
                        APP_TRACE_DEBUG((" Received CCR \n"));
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccreq" << ccreq << endl;
                        }
                        cout << "CallFlow to be executed = " << opfromserv << endl;
                        SendRoCreditControlAnswer(impl);
                        if(opfromserv == 8)
                        {
                            //NOTE: To simulate RAR call flow 
                            CreditControlRequest ccr(*impl);
                            const CCRequestType&  ccRequestType = ccr.getCCRequestType();
                            if(ccRequestType.value() == CCRequestType::INITIAL_REQUEST)
                            {
                                sleep(5);
                                sessionIdForCallFlow = ccr.getSessionId().value();
                                SendReAuthRequest();
                            }
                        }
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
                                   ReleaseSession(rlsStr, sIdxro);
                                }
                                break;
                            case CCRequestType::TERMINATION_REQUEST:
                                std::string rlsStr =
                                               ccans.getSessionId().value();
                                ReleaseSession(rlsStr, sIdxro);
                                break;
                        }
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxro);
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxro)
{
    try
    {
        RoStats::GetRoStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case RO_CC_MSG_CMD_CODE:
                    if(impl->isRequest())
                    {
                        CreditControlRequest ccreq(*impl);
                        APP_TRACE_DEBUG((" Received CCR \n"));
                        if (appMode == UNIT_TEST)
                        {
                            cout << "ccreq" << ccreq << endl;
                        }
                        cout << "CallFlow to be executed = " << opfromserv << endl;
                        SendRoCreditControlAnswer(impl);
                        if(opfromserv == 8)
                        {
                            //NOTE: To simulate RAR call flow 
                            CreditControlRequest ccr(*impl);
                            const CCRequestType&  ccRequestType = ccr.getCCRequestType();
                            if(ccRequestType.value() == CCRequestType::INITIAL_REQUEST)
                            {
                                sleep(5);
                                sessionIdForCallFlow = ccr.getSessionId().value();
                                SendReAuthRequest();
                            }
                        }
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
                                   ReleaseSession(rlsStr, sIdxro);
                                }
                                break;
                            case CCRequestType::TERMINATION_REQUEST:
                                std::string rlsStr =
                                               ccans.getSessionId().value();
                                ReleaseSession(rlsStr, sIdxro);
                                break;
                        }
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxro);
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
 *      Ro interface.
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
            cout << endl << "Select Ro Command"<<endl<<endl;
            cout <<"1: CCR - Credit Control Request with  Initial "<<endl;
            cout <<"2: CCR - Credit Control Request with  Update"<<endl;
            cout <<"3: CCR - Credit Control Request with  Terminate"<<endl;
            cout <<"4: CCR - Credit Control Request Event Based "<<endl;
            cout <<"5: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
    
            ret=atoi(input.c_str());

        } while((ret < 1 || ret > 5) && ret != 99 );

        try
        { 
            switch (ret)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    SendRoCreditControlRequest(ret); 
                    break;
                case 5:
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
        if (RoStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < RoStats::burstSize; i++)
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
            ftime(&RoStats::current);

            TIMERS_USleep(RoStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((RoStats::current.time - RoStats::starter.time) >=
                 RoStats::duration)
            {
                if (RoStats::firstTime)
                {
                    ftime(&RoStats::sendComplete);
                    RoStats::sendTraffic = ITS_FALSE;
                    RoStats::firstTime = false;
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

Json::Value parseS6aConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;

    char *jsonFile = getenv("ROSIM_IWF_CONFIG_FILE");
    if (jsonFile == NULL )
    {
        APP_TRACE_ERROR(("RO_IWF_JSON is not exported"));
        exit(0);
    }
    APP_TRACE_DEBUG(("RO_IWF_JSON=%s",jsonFile));

    std::ifstream doc(jsonFile);
    bool ret = m_jsonConfigFileReader.parse(doc,m_jsonroot);
    if(ret == false)
    {
        APP_TRACE_ERROR(("Parsing of JSON Config file failed."));
    }
    return m_jsonroot;
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
    AppInitialize(RO_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}



