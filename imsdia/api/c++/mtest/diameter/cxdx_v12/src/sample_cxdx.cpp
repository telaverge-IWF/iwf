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
 * LOG: $Log: sample_cxdx.cpp,v $
 * LOG: Revision 1.1.2.1  2015/05/18 05:15:10  kpnithin
 * LOG: cxdx v12 Test tool developed with new protocol file
 * LOG:
 * LOG: Revision 1.1.6.2  2015/01/07 07:28:52  ncshivakumar
 * LOG: Merged
 * LOG:
 * LOG: Revision 1.1.4.2  2014/11/12 04:51:30  ncshivakumar
 * LOG: merged from Aicent branch
 * LOG:
 * LOG: Revision 1.1.2.1  2014/11/03 09:30:42  venkat
 * LOG: Added cxdx_v10
 * LOG:
 * LOG: Revision 1.1.2.2  2013/04/18 16:31:31  cprem
 * LOG: Fixed crash of app
 * LOG:
 * LOG: Revision 1.1.2.1  2013/04/05 13:11:47  jvikram
 * LOG: Include cx/dx and sh interface test code
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:21:14  kamakshilk
 * LOG: Demo program for Cxdx Interface
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_cxdx.cpp,v 1.1.2.1 2015/05/18 05:15:10 kpnithin Exp $
 ****************************************************************************/
#include <dia_defines.h>

#include <diameter/cxdx_v12/LocationInfo.h>
#include <diameter/cxdx_v12/PushProfile.h>
#include <diameter/cxdx_v12/ServerAssignment.h>
#include <diameter/cxdx_v12/MultimediaAuth.h>
#include <diameter/cxdx_v12/RegistrationTermination.h>
#include <diameter/cxdx_v12/UserAuthorization.h>

#include <app.h>
#include <cxdx_defines.h>
#include <cxdx_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cxdx_v12;

int HandleDiaAppMsg(const DIA_BASE_CMD *bCmd,const diameter::CommandImpl *impl, unsigned int &sIdxCx)
{
    try
    {
        // Update the receive statistics
        CxdxStats::GetCxdxStats()->UpdateRecvStats(bCmd->getCommandCode(),
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
                case CXDX_UA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UserAuthorizationRequest uareq(*impl);
                        cout <<"UserAuthorizationRequest "<< uareq << endl;
                        SendCxdxUserAuthorizationAnswer(impl);
                    }
                    else
                    {
                        UserAuthorizationAnswer uaans(*impl);
                        cout << "UserAuthorizationAnswer " << uaans << endl;
                    }
                    break;
                case CXDX_SA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ServerAssignmentRequest sareq(*impl);
                        cout << "ServerAssignmentRequest" << sareq << endl;
                        SendCxdxServerAssignmentAnswer(impl);
                    }
                    else
                    {
                        ServerAssignmentAnswer saans(*impl);
                        cout << "ServerAssignmentAnswer" << saans << endl;
                    }
                    break;

                case CXDX_LI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        LocationInfoRequest lireq(*impl);
                        cout << "LocationInfoRequest" << lireq << endl;
                        SendCxdxLocationInfoAnswer(impl);
                    }
                    else
                    {
                         LocationInfoAnswer lians(*impl);
                         cout << "LocationInfoAnswer" << lians << endl;
                    }
                    break;

                case CXDX_MA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         MultimediaAuthRequest  mareq(*impl);
                         cout << "MultimediaAuthRequest" << mareq << endl;
                         SendCxdxMultimediaAuthAnswer(impl);
                    }
                    else
                    {
                         MultimediaAuthAnswer  maans(*impl);
                         cout << "MultimediaAuthAnswer" << maans << endl;
                    }
                    break;
           
                case CXDX_RT_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         RegistrationTerminationRequest rtreq(*impl);
                         cout << "RegistrationTerminationRequest"<<rtreq<<endl;
                         SendCxdxRegistrationTerminationAnswer(impl);
                    }
                    else
                    {
                         RegistrationTerminationAnswer rtans(*impl);
                         cout << "RegistrationTerminationAnswer"<<rtans<<endl;
                    }
                    break;

                case CXDX_PP_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         PushProfileRequest  ppreq(*impl);
                         cout << "PushProfileRequest" << ppreq << endl;
                         SendCxdxPushProfileAnswer(impl);
                    }
                    else
                    {
                         PushProfileAnswer  ppans(*impl);
                         cout << "PushProfileAnswer" << ppans << endl;
                    }
                    break;
                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxCx);
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxCx)
{
    try
    {
        // Update the receive statistics
        CxdxStats::GetCxdxStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case CXDX_UA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UserAuthorizationRequest uareq(*impl);
                        cout <<"UserAuthorizationRequest "<< uareq << endl;
                        SendCxdxUserAuthorizationAnswer(impl);
                    }
                    else
                    {
                        UserAuthorizationAnswer uaans(*impl);
                        cout << "UserAuthorizationAnswer " << uaans << endl;
                    }
                    break;
                case CXDX_SA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ServerAssignmentRequest sareq(*impl);
                        cout << "ServerAssignmentRequest" << sareq << endl;
                        SendCxdxServerAssignmentAnswer(impl);
                    }
                    else
                    {
                        ServerAssignmentAnswer saans(*impl);
                        cout << "ServerAssignmentAnswer" << saans << endl;
                    }
                    break;

                case CXDX_LI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        LocationInfoRequest lireq(*impl);
                        cout << "LocationInfoRequest" << lireq << endl;
                        SendCxdxLocationInfoAnswer(impl);
                    }
                    else
                    {
                         LocationInfoAnswer lians(*impl);
                         cout << "LocationInfoAnswer" << lians << endl;
                    }
                    break;

                case CXDX_MA_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         MultimediaAuthRequest  mareq(*impl);
                         cout << "MultimediaAuthRequest" << mareq << endl;
                         SendCxdxMultimediaAuthAnswer(impl);
                    }
                    else
                    {
                         MultimediaAuthAnswer  maans(*impl);
                         cout << "MultimediaAuthAnswer" << maans << endl;
                    }
                    break;
           
                case CXDX_RT_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         RegistrationTerminationRequest rtreq(*impl);
                         cout << "RegistrationTerminationRequest"<<rtreq<<endl;
                         SendCxdxRegistrationTerminationAnswer(impl);
                    }
                    else
                    {
                         RegistrationTerminationAnswer rtans(*impl);
                         cout << "RegistrationTerminationAnswer"<<rtans<<endl;
                    }
                    break;

                case CXDX_PP_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                         PushProfileRequest  ppreq(*impl);
                         cout << "PushProfileRequest" << ppreq << endl;
                         SendCxdxPushProfileAnswer(impl);
                    }
                    else
                    {
                         PushProfileAnswer  ppans(*impl);
                         cout << "PushProfileAnswer" << ppans << endl;
                    }
                    break;
                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxCx);
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
 *      This function displays the menu options for the Cxdx interface
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
            cout << endl << "Select Cx/Dx Command" <<endl << endl;
            cout << "1: LIR - Location Info Request" << endl;
            cout << "2: MAR - Multimedia Auth Request" << endl;
            cout << "3: PPR - Push Profile Request" << endl;
            cout << "4: RTR - Registration Termination Request" << endl;
            cout << "5: SAR - Server Assignment Request" << endl;
            cout << "6: UAR - User Authorization Request" << endl;
            cout << "7: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 7) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendCxdxLocationInfoRequest();
                    break;
                case 2:
                    SendCxdxMultimediaAuthRequest();
                    break;
                case 3:
                    SendCxdxPushProfileRequest();
                    break;
                case 4:
                    SendCxdxRegistrationTerminationRequest();
                    break;
                case 5:
                    SendCxdxServerAssignmentRequest();
                    break;
                case 6:
                    SendCxdxUserAuthorizationRequest();
                    break;
                case 7:
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
        if (CxdxStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < CxdxStats::burstSize; i++)
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
            ftime(&CxdxStats::current);
            TIMERS_USleep(CxdxStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((CxdxStats::current.time - CxdxStats::starter.time) >=
                 CxdxStats::duration)
            {
                if (CxdxStats::firstTime)
                {
                    ftime(&CxdxStats::sendComplete);
                    CxdxStats::sendTraffic = ITS_FALSE;
                    CxdxStats::firstTime = false;
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

Json::Value parseCxdxConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;

    char *jsonFile = getenv("CXDX_IWF_CONFIG_FILE");
    if (jsonFile == NULL )
    {    
        APP_TRACE_ERROR(("CXDX_IWF_JSON is not exported"));
        exit(0);
    }    
    APP_TRACE_DEBUG(("DRE_JSON=%s",jsonFile));

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
#if 0
    string errlog = "./dre_console_err.log";
    string dbglog = "./dre_console_out.log";

    // Redirect standard files (input) to /dev/null
    freopen("/dev/null", "r", stdin);
    // Redirect standard files (output and error) to respective log files
    freopen(dbglog.c_str(), "w", stdout);
    freopen(errlog.c_str(), "w", stderr);
#endif

    AppInitialize(CXDX_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

