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
 * LOG: Revision 1.1.2.2.2.2.2.1  2014/09/17 06:36:37  jkchaitanya
 * LOG: changes for bugs 4965 and 4978
 * LOG:
 * LOG: Revision 1.1.2.2.2.2  2014/07/31 12:14:08  jkchaitanya
 * LOG: changes for transparent followOn calls in load
 * LOG:
 * LOG: Revision 1.1.2.2.2.1  2014/07/30 10:37:08  jkchaitanya
 * LOG: changes for imsi based call flow selection at OCS for load
 * LOG:
 * LOG: Revision 1.1.2.2  2014/04/07 04:50:30  jkchaitanya
 * LOG: changes for ro-tsl-perf to support local/remote/sms calls for load
 * LOG:
 * LOG: Revision 1.1.2.1  2014/02/26 05:56:08  jkchaitanya
 * LOG: changes for new tool for perfomance for tsl
 * LOG:
 * LOG: Revision 1.1.4.2  2014/02/12 07:49:38  millayaraja
 * LOG: new testapp for IWF performance
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
 * ID: $Id: sample_ro.cpp,v 1.1.2.2.2.2.2.1 2014/09/17 06:36:37 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: sample_ro.cpp,v 1.1.2.2.2.2.2.1 2014/09/17 06:36:37 jkchaitanya Exp $"

#include <dia_defines.h>
#include <app.h>

#include <ro_stats.h>
#include <ro_defines.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::ro_r10_transatel;
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
                            //cout << "ccreq" << ccreq << endl;
                        } 
                        SendRoCreditControlAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG((" Received CCA \n"));
                        CreditControlAnswer ccans(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            //cout << "ccrsp" << ccans << endl;
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
                            //cout << "ccreq" << ccreq << endl;
                        } 
                        SendRoCreditControlAnswer(impl);
                    }
                    else
                    {
                        APP_TRACE_DEBUG((" Received CCA \n"));
                        CreditControlAnswer ccans(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            //cout << "ccrsp" << ccans << endl;
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
    char cwd[1024] = {0};
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        snprintf(cwd + strlen(cwd), 1024,"/ro_r10_tools.json");
        char *jsonFile = cwd;
        if (jsonFile == NULL )
        {
            APP_TRACE_ERROR(("ro_r10_tools.json is not present"));
            exit(0);
        }
        APP_TRACE_DEBUG(("RO_TRANSATEL_IWF_CONFIG_FILE=%s",jsonFile));

        std::ifstream doc(jsonFile);
        bool ret = m_jsonConfigFileReader.parse(doc,m_jsonroot);
        if(ret == false)
        {
            APP_TRACE_ERROR(("Parsing of JSON Config file failed."));
        }
    }
    else {
        APP_TRACE_ERROR(("getcwd error, current path is not found"));
        exit(0);
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
string ImsiForLocalConnectCall="";
string ImsiForLocalContinueCall="";
string ImsiForRemoteConnectCall="";
string ImsiForRemoteContinueCall="";
string ImsiForSMSCall="";
string ImsiForTransparentLocalCall="";
string ImsiForTransparentRemoteCall="";
string ImsiForFollowOnContinueLocalAndLocalConnect="";
string ImsiForFollowOnContinueLocalAndRemoteConnect="";
string ImsiForFollowOnConnectRemoteAndLocalContinue="";
string ImsiForFollowOnConnectRemoteAndRemoteContinue="";
int CCTimeForRemoteConnectCall=0;
int CCTimeForRemoteContinueCall=0;
int CCTimeForLocalConnectCall=0;
int CCTimeForLocalContinueCall=0;
int CCTimeForTransparentLocalCall=0;
int CCTimeForTransparentRemoteCall=0;
int CCTimeForFollowOnContinueLocalAndLocalConnect=0;
int CCTimeForFollowOnContinueLocalAndRemoteConnect=0;
int CCTimeForFollowOnConnectRemoteAndLocalContinue=0;
int CCTimeForFollowOnConnectRemoteAndRemoteContinue=0;

int main(int argc, const char** argv)
{
#if 0
    for(int i=1;i<argc;i++)
    {   
        
        if(strcmp(argv[i],"-callFlow")==0)
            callFlowSelected = atoi(argv[i+1]);
        if(strcmp(argv[i],"-ccTime")==0)
            configuredCCTime = atoi(argv[i+1]);
    }   
#endif
    AppInitialize(RO_INTERFACE_APP_ID);
    parseImsiRange();
    AppMain(argc,argv);
    return ITS_SUCCESS;
}

void parseImsiRange()
{
    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseS6aConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["ro_r10"];

    isNull = (*m_jsonRoot1)["Imsi_for_LocalConnectCall"].isNull();
    if(!isNull)
    {
        ImsiForLocalConnectCall = (*m_jsonRoot1)["Imsi_for_LocalConnectCall"].asString();
        cout << "Imsi_for_LocalConnectCall :" << ImsiForLocalConnectCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_LocalConnectCall"].isNull();
    if(!isNull)
    {
        CCTimeForLocalConnectCall = (*m_jsonRoot1)["CCTime_for_LocalConnectCall"].asInt();
        cout << "CCTime_for_LocalConnectCall :" << CCTimeForLocalConnectCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_LocalContinueCall"].isNull();
    if(!isNull)
    {
        ImsiForLocalContinueCall = (*m_jsonRoot1)["Imsi_for_LocalContinueCall"].asString();
        cout << "Imsi_for_LocalContinueCall :" << ImsiForLocalContinueCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_LocalContinueCall"].isNull();
    if(!isNull)
    {
        CCTimeForLocalContinueCall = (*m_jsonRoot1)["CCTime_for_LocalContinueCall"].asInt();
        cout << "CCTime_for_LocalContinueCall :" << CCTimeForLocalContinueCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_RemoteConnectCall"].isNull();
    if(!isNull)
    {
        ImsiForRemoteConnectCall = (*m_jsonRoot1)["Imsi_for_RemoteConnectCall"].asString();
        cout << "Imsi_for_RemoteConnectCall :" << ImsiForRemoteConnectCall <<endl;
    }

    isNull = (*m_jsonRoot1)["CCTime_for_RemoteConnectCall"].isNull();
    if(!isNull)
    {
        CCTimeForRemoteConnectCall = (*m_jsonRoot1)["CCTime_for_RemoteConnectCall"].asInt();
        cout << "CCTime_for_RemoteConnectCall :" << CCTimeForRemoteConnectCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_RemoteContinueCall"].isNull();
    if(!isNull)
    {
        ImsiForRemoteContinueCall = (*m_jsonRoot1)["Imsi_for_RemoteContinueCall"].asString();
        cout << "Imsi_for_RemoteContinueCall :" << ImsiForRemoteContinueCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_RemoteContinueCall"].isNull();
    if(!isNull)
    {
        CCTimeForRemoteContinueCall = (*m_jsonRoot1)["CCTime_for_RemoteContinueCall"].asInt();
        cout << "CCTime_for_RemoteContinueCall :" << CCTimeForRemoteContinueCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_TransparentLocalCall"].isNull();
    if(!isNull)
    {
        ImsiForTransparentLocalCall = (*m_jsonRoot1)["Imsi_for_TransparentLocalCall"].asString();
        cout << "Imsi_for_TransparentLocalCall :" << ImsiForTransparentLocalCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_TransparentLocalCall"].isNull();
    if(!isNull)
    {
        CCTimeForTransparentLocalCall = (*m_jsonRoot1)["CCTime_for_TransparentLocalCall"].asInt();
        cout << "CCTime_for_TransparentLocalCall :" << CCTimeForTransparentLocalCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_TransparentRemoteCall"].isNull();
    if(!isNull)
    {
        ImsiForTransparentRemoteCall = (*m_jsonRoot1)["Imsi_for_TransparentRemoteCall"].asString();
        cout << "Imsi_for_TransparentRemoteCall :" << ImsiForTransparentRemoteCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_TransparentRemoteCall"].isNull();
    if(!isNull)
    {
        CCTimeForTransparentRemoteCall = (*m_jsonRoot1)["CCTime_for_TransparentRemoteCall"].asInt();
        cout << "CCTime_for_TransparentRemoteCall :" << CCTimeForTransparentRemoteCall <<endl;
    }
    
    isNull = (*m_jsonRoot1)["Imsi_for_SMSCall"].isNull();
    if(!isNull)
    {
        ImsiForSMSCall = (*m_jsonRoot1)["Imsi_for_SMSCall"].asString();
        cout << "Imsi_for_SMSCall :" << ImsiForSMSCall <<endl;
    }

    isNull = (*m_jsonRoot1)["Imsi_for_FollowOnContinueLocalAndLocalConnect"].isNull();
    if(!isNull)
    {
        ImsiForFollowOnContinueLocalAndLocalConnect = (*m_jsonRoot1)["Imsi_for_FollowOnContinueLocalAndLocalConnect"].asString();
        cout << "Imsi_for_FollowOnContinueLocalAndLocalConnect :" << ImsiForFollowOnContinueLocalAndLocalConnect <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_FollowOnContinueLocalAndLocalConnect"].isNull();
    if(!isNull)
    {
        CCTimeForFollowOnContinueLocalAndLocalConnect = (*m_jsonRoot1)["CCTime_for_FollowOnContinueLocalAndLocalConnect"].asInt();
        cout << "CCTime_for_FollowOnContinueLocalAndLocalConnect :" << CCTimeForFollowOnContinueLocalAndLocalConnect <<endl;
    }

    isNull = (*m_jsonRoot1)["Imsi_for_FollowOnContinueLocalAndRemoteConnect"].isNull();
    if(!isNull)
    {
        ImsiForFollowOnContinueLocalAndRemoteConnect = (*m_jsonRoot1)["Imsi_for_FollowOnContinueLocalAndRemoteConnect"].asString();
        cout << "Imsi_for_FollowOnContinueLocalAndRemoteConnect :" << ImsiForFollowOnContinueLocalAndRemoteConnect <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_FollowOnContinueLocalAndRemoteConnect"].isNull();
    if(!isNull)
    {
        CCTimeForFollowOnContinueLocalAndRemoteConnect = (*m_jsonRoot1)["CCTime_for_FollowOnContinueLocalAndRemoteConnect"].asInt();
        cout << "CCTime_for_FollowOnContinueLocalAndRemoteConnect :" << CCTimeForFollowOnContinueLocalAndRemoteConnect <<endl;
    }

    isNull = (*m_jsonRoot1)["Imsi_for_FollowOnConnectRemoteAndLocalContinue"].isNull();
    if(!isNull)
    {
        ImsiForFollowOnConnectRemoteAndLocalContinue = (*m_jsonRoot1)["Imsi_for_FollowOnConnectRemoteAndLocalContinue"].asString();
        cout << "Imsi_for_FollowOnConnectRemoteAndLocalContinue :" << ImsiForFollowOnConnectRemoteAndLocalContinue <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_FollowOnConnectRemoteAndLocalContinue"].isNull();
    if(!isNull)
    {
        CCTimeForFollowOnConnectRemoteAndLocalContinue = (*m_jsonRoot1)["CCTime_for_FollowOnConnectRemoteAndLocalContinue"].asInt();
        cout << "CCTime_for_FollowOnConnectRemoteAndLocalContinue :" << CCTimeForFollowOnConnectRemoteAndLocalContinue <<endl;
    }

    isNull = (*m_jsonRoot1)["Imsi_for_FollowOnConnectRemoteAndRemoteContinue"].isNull();
    if(!isNull)
    {
        ImsiForFollowOnConnectRemoteAndRemoteContinue = (*m_jsonRoot1)["Imsi_for_FollowOnConnectRemoteAndRemoteContinue"].asString();
        cout << "Imsi_for_FollowOnConnectRemoteAndRemoteContinue :" << ImsiForFollowOnConnectRemoteAndRemoteContinue <<endl;
    }
    
    isNull = (*m_jsonRoot1)["CCTime_for_FollowOnConnectRemoteAndRemoteContinue"].isNull();
    if(!isNull)
    {
        CCTimeForFollowOnConnectRemoteAndRemoteContinue = (*m_jsonRoot1)["CCTime_for_FollowOnConnectRemoteAndRemoteContinue"].asInt();
        cout << "CCTime_for_FollowOnConnectRemoteAndRemoteContinue :" << CCTimeForFollowOnConnectRemoteAndRemoteContinue <<endl;
    }
}


