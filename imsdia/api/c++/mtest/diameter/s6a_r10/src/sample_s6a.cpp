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
 ****************************************************************************
 * LOG: $Log: sample_s6a.cpp,v $
 * LOG: Revision 1.1.6.2.2.1.4.4  2015/04/15 11:25:14  jkchaitanya
 * LOG: changes for handling reset request
 * LOG:
 * LOG: Revision 1.1.6.2.2.1.4.3  2015/03/12 11:13:50  jkchaitanya
 * LOG: changes for notify support
 * LOG:
 * LOG: Revision 1.1.6.2.2.1.4.2  2015/01/07 12:35:37  rsanjay
 * LOG: HSS can send Cancel location request if it receives ULR from 2 SGSN's with same IMSI
 * LOG:
 * LOG: Revision 1.1.6.2.2.1.4.1  2014/12/18 10:39:11  rsanjay
 * LOG: S6a test tool option to allow or disallow AIA responses
 * LOG:
 * LOG: Revision 1.1.6.2.2.1  2014/08/06 15:52:08  jsarvesh
 * LOG: Encoding VplmnId in AIR and ULR
 * LOG:
 * LOG: Revision 1.1.6.2  2014/02/12 08:06:13  millayaraja
 * LOG:  added testapp s6a_r10 for IWF
 * LOG:
 * LOG: Revision 1.1.2.5  2013/05/30 10:36:24  jsarvesh
 * LOG: added case for resetanswer handling
 * LOG:
 * LOG: Revision 1.1.2.4  2013/05/29 11:12:17  jvikas
 * LOG: added case for RSR
 * LOG:
 * LOG: Revision 1.1.2.3  2013/03/22 06:15:49  jsarvesh
 * LOG: changes done to configure resultcode from json file
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/14 09:49:17  brajappa
 * LOG: Notify code added to the app
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/19 22:17:18  brajappa
 * LOG: Added s6a and s13 Release 10 ABNF
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 08:53:44  pramana
 * LOG: New test code added for S6a, S13 for Release 10 support (Bug 48).
 * LOG:
 * LOG: Revision 1.3  2008/11/12 09:01:47  sureshj
 * LOG: case statement for Insert Subscriber Data added. 3.1.1 release.
 * LOG:
 * LOG: Revision 1.2  2008/11/12 05:53:50  sureshj
 * LOG: New commands added. part of 3.1.1 release.
 * LOG:
 * LOG: Revision 1.1  2008/08/19 06:58:33  sureshj
 * LOG: Baseline demo application for s6a interface.
 * LOG:
 * ID: $Id: sample_s6a.cpp,v 1.1.6.2.2.1.4.4 2015/04/15 11:25:14 jkchaitanya Exp $
 ****************************************************************************/

#include <dia_defines.h>
#include <diameter/Exceptions.h>
#include <diameter/s6a_r10/UpdateLocation.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>
#include <diameter/s6a_r10/CancelLocation.h>
#include <diameter/s6a_r10/PurgeUE.h>
#include <diameter/s6a_r10/DeleteSubscriberData.h>
#include <diameter/s6a_r10/InsertSubscriberData.h>
#include <diameter/s6a_r10/Reset.h>
#include <diameter/s6a_r10/Notify.h>

#include <app.h>
#include <vector>
#include <algorithm>
#include <s6a_defines.h>
#include <s6a_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

vector<string> vec_imsi;
vector<string> vec_oh;
//std::vector<std::pair<string,string>> vec;
std::vector<string>::iterator it;
int HandleDiaAppMsg(const DIA_BASE_CMD *bCmd,const diameter::CommandImpl *impl, unsigned int &sIdxS6A)
{
    try
    {
        // Update the receive statistics
        S6AStats::GetS6AStats()->UpdateRecvStats(bCmd->getCommandCode(),
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
                case S6A_UL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UpdateLocationRequest udReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationRequest" << udReq << endl;
                        std::string UserName;
                        std::string DestinationHost;
                        SendS6AUpdateLocationAnswer(impl);
                        UserName = udReq.getUserName().value();
                        DestinationHost = udReq.getOriginHost().value();
                        it = find(vec_imsi.begin(), vec_imsi.end(),UserName);
                        if (it != vec_imsi.end()) 
                        {
                            cout<<"Duplicate Entry Found !!! " <<*it<<endl;
                            SendS6ACancelLocationRequest(DestinationHost,UserName);
                        }
                        else
                        {
                            vec_imsi.push_back(UserName);
                            //vec_oh.push_back(DestinationHost);
                        }
                    }
                    else
                    {
                        UpdateLocationAnswer udAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationAnswer" << udAns << endl;
                    }
                    break;

                case S6A_AI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AuthenticationInformationRequest aiReq(*impl);

                        if (appMode == UNIT_TEST)
                            cout <<endl<< "AuthenticationInformationRequest" << aiReq << endl;

                        bool isNull;
                        bool isAVPEnabled;
                        Json::Value l_jsonRoot = parseS6aConfig();

                        Json::Value* m_jsonRoot = &l_jsonRoot;
                        Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["s6a_r10"];

                        Json::Value* cfg = &(*m_jsonRoot1)["Do_not_send_AIA"];
                        isNull = (*cfg)["Enabled"].isNull();
                        isAVPEnabled = (*cfg)["Enabled"].asBool();
                        if(!isAVPEnabled)
                        {

                            APP_TRACE_DEBUG(("Sending AIA message"));
                            SendS6AAuthenticationInformationAnswer(impl);
                        }
                    }
                    else
                    {
                        AuthenticationInformationAnswer aiAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "AuthenticationInformationAnswer" << aiAns << endl;
                    }
                    break;

                case S6A_CL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CancelLocationRequest clReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "CancelLocationRequest" << clReq << endl;
                        SendS6ACancelLocationAnswer(impl);
                    }
                    else
                    {
                        CancelLocationAnswer clAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "CancelLocationAnswer" << clAns << endl;
                    }
                    break;

                case S6A_PU_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PurgeUERequest puReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Purge UE Request" << puReq << endl;
                        SendS6APurgeUEAnswer(impl);
                    }
                    else
                    {
                        PurgeUEAnswer puAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "PurgeUE Answer" << puAns << endl;
                    }
                    break;

                case S6A_DS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DeleteSubscriberDataRequest dsReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Delete Subscriber Data  Request" << dsReq << endl;
                        SendS6ADeleteSubDataAnswer(impl);
                    }   
                    else
                    {   
                        DeleteSubscriberDataAnswer dsAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Delete Subscriber Data Answer" << dsAns << endl;
                    }   
                    break;
                    case S6A_NO_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        NotifyRequest noReq(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Notify Request " << noReq << endl; 
                        }
                        SendS6ANotifyAnswer(impl);
                    }
                    else
                    {
                        NotifyAnswer noAns(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Notify Answer" << noAns << endl;
                        }
                    }
                    break;
                case S6A_ID_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        InsertSubscriberDataRequest idReq(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Insert Subscriber Data  Request" << idReq << endl;
                        SendS6AInsertSubDataAnswer(impl);
                    }
                    else
                    {
                        InsertSubscriberDataAnswer idAns(*impl);
                        if (appMode == UNIT_TEST)
                            cout << "Insert Subscriber Data Answer" << idAns << endl;
                    }
                    break;
                case S6A_RS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ResetRequest rsReq(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Reset Request " << rsReq << endl; 
                        }
                        SendS6AResetAnswer(impl);
                    }
                    else
                    {
                        ResetAnswer rsAns(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Reset Answer" << rsAns << endl;
                        }
                    }

                    break;    
                    // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxS6A);
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
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxS6A)
{
    try
    {
        // Update the receive statistics
        S6AStats::GetS6AStats()->UpdateRecvStats(impl->getCommandCode(),
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
                case S6A_UL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UpdateLocationRequest udReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UpdateLocationRequest" << udReq << endl;
                        SendS6AUpdateLocationAnswer(impl);
                    }
                    else
                    {
                        UpdateLocationAnswer udAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "UpdateLocationAnswer" << udAns << endl;
                    }
                    break;

		case S6A_AI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AuthenticationInformationRequest aiReq(*impl);
                      
                        if (appMode == UNIT_TEST)
                        cout <<endl<< "AuthenticationInformationRequest" << aiReq << endl;
                        SendS6AAuthenticationInformationAnswer(impl);
                    }
                    else
                    {
                        AuthenticationInformationAnswer aiAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "AuthenticationInformationAnswer" << aiAns << endl;
                    }
                    break;
			
		case S6A_CL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CancelLocationRequest clReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "CancelLocationRequest" << clReq << endl;
                        SendS6ACancelLocationAnswer(impl);
                    }
                    else
                    {
                        CancelLocationAnswer clAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "CancelLocationAnswer" << clAns << endl;
                    }
                    break;

                 case S6A_PU_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        PurgeUERequest puReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Purge UE Request" << puReq << endl;
                        SendS6APurgeUEAnswer(impl);
                    }
                    else
                    {
                        PurgeUEAnswer puAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "PurgeUE Answer" << puAns << endl;
                    }
                    break;

                 case S6A_DS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        DeleteSubscriberDataRequest dsReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Delete Subscriber Data  Request" << dsReq << endl;
                        SendS6ADeleteSubDataAnswer(impl);
                    }   
                    else
                    {   
                        DeleteSubscriberDataAnswer dsAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Delete Subscriber Data Answer" << dsAns << endl;
                    }   
                    break;
 
                case S6A_ID_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        InsertSubscriberDataRequest idReq(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Insert Subscriber Data  Request" << idReq << endl;
                        SendS6AInsertSubDataAnswer(impl);
                    }
                    else
                    {
                        InsertSubscriberDataAnswer idAns(*impl);
                        if (appMode == UNIT_TEST)
                        cout << "Insert Subscriber Data Answer" << idAns << endl;
                    }
                    break;    
                case S6A_NO_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        NotifyRequest noReq(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Notify Request " << noReq << endl; 
                        }
                        SendS6ANotifyAnswer(impl);
                    }
                    else
                    {
                        NotifyAnswer noAns(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Notify Answer" << noAns << endl;
                        }
                    }
                    break;
                case S6A_RS_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        ResetRequest rsReq(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Reset Request " << rsReq << endl; 
                        }
                        SendS6AResetAnswer(impl);
                    }
                    else
                    {
                        ResetAnswer rsAns(*impl);
                        if (appMode == UNIT_TEST)
                        {
                            cout << "Reset Answer" << rsAns << endl;
                        }
                    }
                    break;

                // Handle Base Messages
                case BASE_RA_MSG_CMD_CODE:
                case BASE_ST_MSG_CMD_CODE:
                case BASE_AS_MSG_CMD_CODE:
                    HandleBaseMessages(impl,sIdxS6A);
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
 *      This function displays the menu options for the S6A interface
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
            cout << endl << "Select S6A Command" <<endl << endl;
            cout << "1:  ULR - User Location Request    " << endl;
            cout << "2:  AIR - Authentication Information Request   " << endl;
            cout << "3:  CLR - Cancel Location Request   " << endl;
            cout << "4:  PUR - Purge UE  Request   " << endl;
            cout << "5:  DSR - Delete Subscriber Data Request    " << endl;
            cout << "6:  IDR - Insert Subscriber Data Request    " << endl;
            cout << "7:  NOR - Notify Request without Ready_For_SM" << endl;
            cout << "8:  NOR - Notify Request with Ready_For_SM" << endl;
            cout << "9:  RSR - Reset Request " << endl;
            cout << "11:  To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 11) && ret!=99);

        try
        {
            switch (ret)
            {
                case 1:
                    SendS6AUpdateLocationRequest();
                    break;
		case 2:
                    SendS6AAuthenticationInformationRequest();
                    break;
	
		case 3:
                    SendS6ACancelLocationRequest();
                    break;

                case 4:
                    SendS6APurgeUERequest();
                    break;
                
                case 5:
                    SendS6ADeleteSubDataRequest();
                    break;
                
                case 6:
                    SendS6AInsertSubDataRequest();
                    break;

                case 7:
                    SendS6ANotifyRequest(false);
                    break;
                case 8:
                    SendS6ANotifyRequest(true);
                    break;
                case 9:
                    SendS6AResetRequest();
                    break;
                case 11:
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
        if (S6AStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < S6AStats::burstSize; i++)
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
            ftime(&S6AStats::current);
            TIMERS_USleep(S6AStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((S6AStats::current.time - S6AStats::starter.time) >=
                 S6AStats::duration)
            {
                if (S6AStats::firstTime)
                {
                    ftime(&S6AStats::sendComplete);
                    S6AStats::sendTraffic = ITS_FALSE;
                    S6AStats::firstTime = false;
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

typedef std::unordered_map<unsigned, unsigned> MccWith3DigitMnc;
// gcc flag -std=c++0x need for this type of initialization
static const MccWith3DigitMnc sMccWith3DigitMnc = {
// { 262, 2},       // Mixture of 2 and 3-digit MNCs
{ 302, 1},
{ 310, 1},
{ 311, 1},
{ 316, 1},
{ 334, 1},
{ 338, 1},
{ 342, 1},
{ 344, 1},
{ 346, 1},
{ 348, 1},
{ 352, 1},
{ 354, 1},
{ 356, 1},
{ 358, 1},
{ 360, 1},
{ 365, 1},
{ 366, 1},
// { 374, 1},       // Mixture of 2 and 3-digit MNCs
{ 376, 1},
{ 405, 1},
// { 502, 1},       // Mixture of 2 and 3-digit MNCs
// { 710, 1},       // Mixture of 2 and 3-digit MNCs
{ 722, 1},
{ 732, 1},
};

void CreatePlmn(unsigned char* plmn, std::string& mcc, std::string& mnc)
{
    const char* mcc_arr = mcc.c_str();
    const char* mnc_arr = mnc.c_str();
    plmn[0] = ((mcc_arr[1] - '0') << 4)| (mcc_arr[0] - '0');
    if (mnc.length() == 3)
    {
        plmn[1] = ((mnc_arr[2] - '0') << 4)| (mcc_arr[2] - '0');
    }
    else
    {
        plmn[1] = 0xf0 | (mcc_arr[2] - '0');
    }
    plmn[2] = ((mnc_arr[1] - '0') << 4)|(mnc_arr[0] - '0');
}

void ExtractMncMcc(const std::string& imsi, std::string& strMcc, std::string& strMnc)
{
    unsigned mncDigits = 2; 
    unsigned mcc = 0, mnc = 0; 
    unsigned *val = &mcc;
    strMcc = "";
    strMnc = "";
    for (int i = 0; i < 6 ; i++) 
    {    
        if (i < 3) 
        {    
            mcc *= 10;
            mcc += imsi[i] - '0'; 
            strMcc += imsi[i];
        }    
        else if (i == 3)
        {    
            if (sMccWith3DigitMnc.find(mcc) != sMccWith3DigitMnc.end())
            {    
                mncDigits = 3; 
            }    
            strMnc += imsi[i];
        }    
        else if (i == 5 && mncDigits == 2)
        {    
            break;
        }    
        else 
        {    
            strMnc += imsi[i];
        }    
    }    
}

Json::Value parseS6aConfig()
{
    Json::Reader m_jsonConfigFileReader;
    Json::Value m_jsonroot;

    char *jsonFile = getenv("S6A_IWF_CONFIG_FILE");
    if (jsonFile == NULL )
    {    
        APP_TRACE_ERROR(("S6A_IWF_JSON is not exported"));
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
int singlton::a;
long long singlton::arg[2];

int main(int argc, const char** argv)
{
	int i;
                singlton::a= argc;
                char *end;
        for(i=1;i<argc;i++)
        {
                if(strcmp(argv[i],"-imsistart")==0)
                singlton::arg[0]=strtoll(argv[i+1],&end,10);

                else if(strcmp(argv[i],"-imsiend")==0)
                singlton::arg[1]=strtoll(argv[i+1],&end,10);
        }

    AppInitialize(S6A_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

