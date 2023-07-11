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
 * LOG: Revision 1.1.2.4  2013/03/19 12:24:10  jvikas
 * LOG: Boundary Issues.
 * LOG:
 * LOG: Revision 1.1.2.3  2013/03/19 10:04:53  jvikas
 * LOG: Fixes to Display Diameter Message Details.
 * LOG:
 * LOG: Revision 1.1.2.2  2013/03/18 12:13:44  jvikas
 * LOG: diaSim changes for CLR.
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/08 10:52:30  jvikas
 * LOG: Diameter Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/06 14:45:46  jvikas
 * LOG: S6a Simulator Code from 300 Branch.
 * LOG:
 * LOG: Revision 1.1.2.1  2013/01/28 11:31:39  pramana
 * LOG: Initial check-in for simulator code
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
 * ID: $Id: sample_s6a.cpp,v 1.1.2.4 2013/03/19 12:24:10 jvikas Exp $
 ****************************************************************************/
#include <sys/time.h>
#include <dia_defines.h>

#include <diameter/Exceptions.h>
#include <diameter/s6a_r10/UpdateLocation.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>
#include <diameter/s6a_r10/CancelLocation.h>
#include <diameter/s6a_r10/PurgeUE.h>
#include <diameter/s6a_r10/DeleteSubscriberData.h>
#include <diameter/s6a_r10/InsertSubscriberData.h>

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

extern ApplicationStats appStats;
char* sim;

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
int HandleDiaAppMsg(const DIA_BASE_CMD *bCmd,const diameter::CommandImpl *impl,
        unsigned int &sIdxS6A)
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
            appStats.m_failedCalls++;
        }
        else
        {
            switch (impl->getCommandCode())
            {
                case S6A_UL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UpdateLocationRequest udReq(*impl);
#if 0
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationRequest" << udReq << endl;
#endif
                        appStats.u.s6a.ulr.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received ULR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        SendS6AUpdateLocationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent ULA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.ula.m_in++;
                    }
                    else
                    {
                        appStats.u.s6a.ula.m_in++;
                        UpdateLocationAnswer udAns(*impl);
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received ULA ";
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        //appStats.last_processed_msgs[appStats.recent_msg_idx] += udAns.getUserName().value();
                        appStats.u.s6a.ulr.m_in++;
#if 0
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationAnswer" << udAns << endl;
#endif
                    }
                    break;

                case S6A_AI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AuthenticationInformationRequest aiReq(*impl);
                        appStats.u.s6a.air.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received AIR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += aiReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 

#if 0
                        if (appMode == UNIT_TEST)
                            cout <<endl<< "AuthenticationInformationRequest" << aiReq << endl;
#endif
                        SendS6AAuthenticationInformationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent AIA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += aiReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.aia.m_in++;
                    }
                    else
                    {
                        appStats.u.s6a.aia.m_in++;
                        AuthenticationInformationAnswer aiAns(*impl);
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received AIA ";
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        //appStats.last_processed_msgs[appStats.recent_msg_idx] += aiAns.getUserName().value();
                        appStats.u.s6a.air.m_in++;

#if 0
                        if (appMode == UNIT_TEST)
                            cout << "AuthenticationInformationAnswer" << aiAns << endl;
#endif
                    }
                    break;

                case S6A_CL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CancelLocationRequest clReq(*impl);
                        appStats.u.s6a.clr.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received CLR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += clReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 

                        /*if (appMode == UNIT_TEST)
                            cout << "CancelLocationRequest" << clReq << endl;*/
                        SendS6ACancelLocationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent CLA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += clReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.cla.m_in++;
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

////////////////////////// -> Older
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdxS6A)
{
    APP_TRACE_ERROR(("Vikas: Rcved DMT Cmd with CmdCode: %d",impl->getCommandCode()));
    try
    {
        // Update the receive statistics
        S6AStats::GetS6AStats()->UpdateRecvStats(impl->getCommandCode(),
                impl->isRequest());

        // Process the commands based on the command code.
        if(impl->isError())
        {
            HandleErrorResponse(impl);
            appStats.m_failedCalls++;
        }
        else
        {
            switch (impl->getCommandCode())
            {
                case S6A_UL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        UpdateLocationRequest udReq(*impl);
#if 0
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationRequest" << udReq << endl;
#endif
                        appStats.u.s6a.ulr.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received ULR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        SendS6AUpdateLocationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent ULA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.ula.m_in++;
                    }
                    else
                    {
                        appStats.u.s6a.ula.m_in++;
                        UpdateLocationAnswer udAns(*impl);
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received ULA ";
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        //appStats.last_processed_msgs[appStats.recent_msg_idx] += udAns.getUserName().value();
                        appStats.u.s6a.ulr.m_in++;
#if 0
                        if (appMode == UNIT_TEST)
                            cout << "UpdateLocationAnswer" << udAns << endl;
#endif
                    }
                    break;

                case S6A_AI_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        AuthenticationInformationRequest aiReq(*impl);
                        appStats.u.s6a.air.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received AIR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += aiReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 

#if 0
                        if (appMode == UNIT_TEST)
                            cout <<endl<< "AuthenticationInformationRequest" << aiReq << endl;
#endif
                        SendS6AAuthenticationInformationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent AIA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += aiReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.aia.m_in++;
                    }
                    else
                    {
                        appStats.u.s6a.aia.m_in++;
                        AuthenticationInformationAnswer aiAns(*impl);
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received AIA ";
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        //appStats.last_processed_msgs[appStats.recent_msg_idx] += aiAns.getUserName().value();
                        appStats.u.s6a.air.m_in++;

#if 0
                        if (appMode == UNIT_TEST)
                            cout << "AuthenticationInformationAnswer" << aiAns << endl;
#endif
                    }
                    break;

                case S6A_CL_MSG_CMD_CODE:
                    if (impl->isRequest())
                    {
                        CancelLocationRequest clReq(*impl);
                        appStats.u.s6a.clr.m_in++;
                        int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Received CLR with IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += clReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        /*if (appMode == UNIT_TEST)
                            cout << "CancelLocationRequest" << clReq << endl;*/
                        SendS6ACancelLocationAnswer(impl);
                        recent_msg_idx = appStats.recent_msg_idx++ % 10;
                        appStats.last_processed_msgs[recent_msg_idx] = "Sent CLA for IMSI: ";
                        appStats.last_processed_msgs[recent_msg_idx] += clReq.getUserName().value();
                        appStats.recent_msg_idx = recent_msg_idx+1; 
                        appStats.u.s6a.cla.m_in++;
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
        cin >> input;

        ret=atoi(input.c_str());

        if (*input.c_str() == 'q')
        {
            displayMode = 10;
            break;
        }
        else
        {
            displayMode = 100;
        }

        try
        {
            switch (ret)
            {
                case 1:
                case 11:
                case 111:
                case 1111:
                case 11111:
                case 111111:
                    SendS6AUpdateLocationRequest();
                    break;
                case 2:
                case 22:
                case 222:
                case 2222:
                case 22222:
                case 222222:
                    for (int numMsg = 0; numMsg < 10; numMsg++)
                        SendS6AUpdateLocationRequest();
                    break;
                case 3:
                case 33:
                case 333:
                case 3333:
                case 33333:
                case 333333:
                    SendS6AAuthenticationInformationRequest();
                    break;
                case 4:
                case 44:
                case 444:
                case 4444:
                case 44444:
                case 444444:
                    for (int numMsg = 0; numMsg < 10; numMsg++)
                        SendS6AAuthenticationInformationRequest();
                    break;
                case 'q':
                    k=0;
                    break;
                default:
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

#ifdef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
    printf("|------------------------+---------------------------+-------------------------|\r\n")

#define DISPLAY_HEADER()\
    printf("|    Counter Name        |      Periodic value       |     Cumulative value    |\r\n")
#define DISPLAY_TXT_COL(T1, V1, V2)\
    printf("| %-22.22s | %-25.25s |", T1, V1); printf(" %-24.24s|\r\n", V2)
#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-22.22s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-22.22s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-22.22s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-22.22s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-22.22s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-22.22s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-22.22s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-22.22s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-22.22s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-22.22s | %-52.52s|\r\n", T1, V1)
#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-22s | %25s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//	printf("| %-22.22s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
    printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
    printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-22.22s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-22.22s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
    printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
    printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
    printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-22.22s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}

#define RESET_PL_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
    struct tm *L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL)
    {
        memset (P_time, 0, TIME_LENGTH);
    }
    else
    {
        sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

    static char L_time [TIME_LENGTH];
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (L_time, 0, TIME_LENGTH);
    } else {
        sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec);
    }
    return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;

    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;

    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
    mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
    long L_val_sec, L_val_usec;

    L_val_sec = P_final->tv_sec - P_init->tv_sec;
    L_val_usec = P_final->tv_usec - P_init->tv_usec;
    if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
    return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

#endif // _STAT_MACROS_H
#endif // SEAGUL_STYLE_OUTPUT

#ifndef  SEAGUL_STYLE_OUTPUT
#ifndef _STAT_MACROS_H
#define _STAT_MACROS_H

#define TIME_LENGTH 32
#define TIME_STRING_LENGTH 32

#define DISPLAY_EMPTY_LINE()\
    printf("|                                                                              |\r\n")
#define DISPLAY_OPEN_TEXT(T1)\
    printf("| %s", T1);fflush(stdout)

#define DISPLAY_EMPTY_TEXT(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_LINE()\
    printf("|------------------------------------------------------------------------------|\r\n")
#define DISPLAY_DLINE()\
    printf("================================================================================\r\n")
#define DISPLAY_CROSS_LINE()\
    printf("|-----------------------------+----------------------+-------------------------|\r\n")

#define DISPLAY_BANNER()\
    printf("|                            Diametriq S6a Simulator                           |\r\n", sim)

#define DISPLAY_BANNER2()\
    printf("|                       Diametriq S6a Simulator Messages                       |\r\n", sim)

#define DISPLAY_HEADER()\
    printf("|        Main Menu            |                     Statistics                 |\r\n")

#define DISPLAY_CROSS_LINE2()\
    printf("|-----------------------------|------------------------------------------------|\r\n")

#define DISPLAY_TXT_COL(T1, T2, V1)\
    printf("| %-27.27s | %-35.35s :", T1, T2); printf(" %-9d|\r\n", V1)

#define DISPLAY_VAL_RATEF_COL(T1, V1, V2)\
    printf("| %-27.27s | %8.3f cps              | %8.3f cps            |\r\n", T1, V1, V2)
#define DISPLAY_2VAL(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8ld                |\r\n", T1, V1, V2)
#define DISPLAY_CUMUL(T1, V1)\
    printf("| %-27.27s |                           | %8ld                |\r\n", T1, V1)
#define DISPLAY_PERIO(T1, V1)\
    printf("| %-27.27s | %8ld                  |                         |\r\n", T1, V1)
#define DISPLAY_VALF(T1, V1)\
    printf("| %-27.27s | %8.3f ms                                         |\r\n", T1, V1)
#define DISPLAY_VAL_RATEF(T1, V1)\
    printf("| %-27.27s | %8.3f cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL_RATE(T1, V1)\
    printf("| %-27.27s | %8d cps                                        |\r\n", T1, V1)
#define DISPLAY_VAL(T1, V1)\
    printf("| %-27.27s : %8d                                            |\r\n", T1, V1)
#define DISPLAY_2VALF(T1, V1, T2, V2)\
    printf("| %-27.27s : %8.2f  | %-7.7s : %8.2f                      |\r\n", T1, V1, T2, V2)
#define DISPLAY_3VAL(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8d  | %-7.7s : %8d  | %-12.12s : %5d|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_3VALF(T1, V1, T2, V2, T3, V3)\
    printf("| %-27.27s : %8.3f  | %-7.7s : %8.3f  | %-12.12s : %5.1f|\r\n", T1, V1, T2, V2, T3, V3)
#define DISPLAY_TXT(T1, V1)\
    printf("| %-27.27s | %-52.52s|\r\n", T1, V1)

#define DISPLAY_3TXT(T1, T2, T3)\
    printf("| %-27s | %20s | %23s |\r\n", (T1), (T2), (T3))

//#define DISPLAY_3TXT(T1, T2, T3)
//	printf("| %-27.27s | %-25.25s | %-25.25s |\r\n", (T1), (T2), (T3))


#define DISPLAY_4TXT(T1, T2, T3, T4)\
    printf("| %-10.10s | %-19.19s | %-19.19s | %-19.19s |\r\n", (T1), (T2), (T3), (T4))
#define DISPLAY_INFO(T1)\
    printf("| %-77.77s|\r\n", T1)

#define DISPLAY_REPART(T1, T2, V1)\
    printf("|   %8d ms <= n <  %8d ms : %10ld  %-29.29s|\r\n", T1, T2, V1, "")


#define DISPLAY_LAST_REPART(T1, V1)\
    printf("|   %14.14s n >= %8d ms : %10ld  %-29.29s|\r\n", "", T1, V1, "")

#define DISPLAY_VAL_RATEF_TPS(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)

#define DISPLAY_2VAL_RATEF(T1, V1, V2)\
    printf("| %-27.27s | %8.3f                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_2VAL_CURRENTF(T1, V1, V2)\
    printf("| %-27.27s | %8ld                  | %8.3f                |\r\n", T1, V1, V2)


#define DISPLAY_REPART_F(T1, T2, V1, V2)\
    printf("|   %8d ms <= n <  %8d ms : %10ld     : %8.3f %-15.15s|\r\n", T1, T2, V1, V2, "")


#define DISPLAY_LAST_REPART_F(T1, V1, V2)\
    printf("|   %14.14s n >= %8d ms : %10ld     : %8.3f %-15.15s|\r\n", "", T1, V1, V2,"")



#define ZERO_COUNTER_VALUE      (unsigned long) 0


#define DISPLAY_HEADER_NIL()\
    printf("|                        |                           |                         |\r\n")


#define DISPLAY_SCEN_INFO(T1,T2)\
    printf("| %-27.27s : %02d                                                  |\r\n", T1, T2)

/*
#define RESET_COUNTERS(PT)\
memset (PT, 0, C_GeneratorStats::E_NB_COUNTER * sizeof(unsigned long))

#define RESET_PD_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PD_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PD_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}

#define RESET_PL_COUNTERS(PT)\
{\
int i;\
for (i=C_GeneratorStats::CPT_PL_IncomingCallCreated; \
i<=C_GeneratorStats::CPT_PL_FailedCallRegexpHdrNotFound; i++)\
PT[i] = (unsigned long) 0;\
}
*/

void formatTime (char *P_time, struct timeval* P_tv)
{
    struct tm *L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *) &P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL)
    {
        memset (P_time, 0, TIME_LENGTH);
    }
    else
    {
        sprintf (P_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min, L_currentDate->tm_sec);

    }
}/* end of formatTime */

char* formatTime (struct timeval* P_tv) {

    static char L_time [TIME_LENGTH];
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (L_time, 0, TIME_LENGTH);
    } else {
        sprintf(L_time, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec);
    }
    return (L_time);
} /* end of formatTime */


char* msToHHMMSS (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long hh, mm, ss;

    P_ms = P_ms / 1000;
    hh = P_ms / 3600;
    mm = (P_ms - hh * 3600) / 60;
    ss = P_ms - (hh * 3600) - (mm * 60);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld", hh, mm, ss);
    return (L_time);
} /* end of msToHHMMSS */

char* msToHHMMSSmmm (unsigned long P_ms)
{
    static char L_time [TIME_LENGTH];
    unsigned long sec, hh, mm, ss, mmm;

    sec  = P_ms / 1000;
    hh   = sec / 3600;
    mm   = (sec - hh * 3600) / 60;
    ss   = sec - (hh * 3600) - (mm * 60);
    mmm  = P_ms - (hh * 3600000) - (mm * 60000) - (ss*1000);
    sprintf (L_time, "%2.2ld:%2.2ld:%2.2ld:%3.3ld", hh, mm, ss, mmm);
    return (L_time);
} /* end of msToHHMMSS */

long ms_difftime (struct timeval* P_final, struct timeval* P_init)
{
    long L_val_sec, L_val_usec;

    L_val_sec = P_final->tv_sec - P_init->tv_sec;
    L_val_usec = P_final->tv_usec - P_init->tv_usec;
    if (L_val_usec < 0) L_val_usec += 1000000, L_val_sec--;
    return (L_val_sec*1000 + L_val_usec/1000);

}

void time_tochar (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d:%2.2d:%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

void time_tochar_minus (char *P_time, struct timeval* P_tv)
{
    struct tm * L_currentDate;

    // Get the current date and time
    L_currentDate = localtime ((const time_t *)&P_tv->tv_sec);

    // Format the time
    if (L_currentDate == NULL) {
        memset (P_time, 0, TIME_STRING_LENGTH);
    } else {
        sprintf(P_time, 
                "%4.4d-%2.2d-%2.2d.%2.2d-%2.2d-%2.2d.%3.3d", 
                L_currentDate->tm_year + 1900,
                L_currentDate->tm_mon + 1,
                L_currentDate->tm_mday,
                L_currentDate->tm_hour,
                L_currentDate->tm_min,
                L_currentDate->tm_sec,
                (int)((P_tv->tv_usec)/1000));
    }
} 

#endif // _STAT_MACROS_H
#endif // not SEAGUL_STYLE_OUTPUT


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function displays the main windows of the application
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
void DisplayMainWindow()
{
    int ret;
    struct timeval startTime;
    gettimeofday (&startTime, NULL);
    struct timeval periodicStartTime;
    gettimeofday (&periodicStartTime, NULL);
    struct timeval currentTime;
    long globalElapsedTime;
    long localElapsedTime;

    // Display the data
    printf("\n");
    //DISPLAY_CROSS_LINE ();
    if (displayMode !=20)
    {
        DISPLAY_DLINE ();
        DISPLAY_BANNER();
        DISPLAY_DLINE ();
        //DISPLAY_CROSS_LINE();

        {
            char L_start_time[TIME_LENGTH];
            char L_current_time[TIME_LENGTH];
            gettimeofday (&currentTime, NULL);
            formatTime(L_start_time, &startTime);
            formatTime(L_current_time, &currentTime);
            DISPLAY_3TXT ("Start/Current Time", 
                    L_start_time, 
                    L_current_time);
            globalElapsedTime   = ms_difftime (&currentTime, &startTime);
            localElapsedTime    = ms_difftime (&currentTime, &periodicStartTime);

        }

        // printing the header in the middle
        DISPLAY_DLINE ();
        DISPLAY_HEADER();
        DISPLAY_DLINE ();
    }

    //DISPLAY_CROSS_LINE2();

    if (displayMode == 0)
    {
        DISPLAY_TXT_COL ("1. Send Mode", "1. Total AIR messages received",   appStats.u.s6a.air.m_out);
        DISPLAY_TXT_COL ("2. Receive Mode", runMode == INITIATOR?"2. Total AIA messages received":"2. Total AIA messages sent",   appStats.u.s6a.aia.m_in);
        DISPLAY_TXT_COL ("3. Reset Statistics", runMode == INITIATOR?"3. Total ULR messages sent":"3. Total ULR messages received",   appStats.u.s6a.ulr.m_out);
        DISPLAY_TXT_COL ("4. Quit", runMode == INITIATOR?"4. Total ULA messages received":"4. Total ULA messages sent",   appStats.u.s6a.ula.m_in);
        DISPLAY_TXT_COL (" ", "5. Total CLR messages received",   appStats.u.s6a.clr.m_in);
        DISPLAY_TXT_COL (" ", "6. Total CLA messages sent",   appStats.u.s6a.cla.m_out);
        DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
        DISPLAY_DLINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        //DISPLAY_LINE();
        /*DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();*/
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        DISPLAY_OPEN_TEXT ("Enter your choice _");
        printf("\n");
        printf("\n");

    }
    else if(displayMode == 10)
    {
        DISPLAY_TXT_COL ("1. Send Mode", runMode == INITIATOR?"1. Total AIR messages sent":"1. Total AIR messages received",   appStats.u.s6a.air.m_out);
        DISPLAY_TXT_COL ("2. Display messages ", runMode == INITIATOR?"2. Total AIA messages received":"2. Total AIA messages sent",   appStats.u.s6a.aia.m_in);
        DISPLAY_TXT_COL ("9. Return to main menu ", runMode == INITIATOR?"3. Total ULR messages sent":"3. Total ULR messages received",   appStats.u.s6a.ulr.m_out);
        DISPLAY_TXT_COL (" ", runMode == INITIATOR?"4. Total ULA messages received":"4. Total ULA messages sent",   appStats.u.s6a.ula.m_in);
        DISPLAY_TXT_COL (" ", "5. Total CLR messages received",   appStats.u.s6a.clr.m_in);
        DISPLAY_TXT_COL (" ", "6. Total CLA messages sent",   appStats.u.s6a.cla.m_out);
        DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        DISPLAY_EMPTY_TEXT (" Running in Sender Mode ");
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        /*DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();*/
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        DISPLAY_OPEN_TEXT ("Enter your choice _");
        printf("\n");
        printf("\n");

    }
    else if(displayMode == 20)
    {
        /*DISPLAY_TXT_COL ("1. Display messages", runMode == INITIATOR?"1. Total AIR messages sent":"1. Total AIR messages received",   appStats.u.s6a.air.m_out);
        DISPLAY_TXT_COL ("9. Return to main menu ", runMode == INITIATOR?"2. Total AIA messages received":"2. Total AIA messages sent",   appStats.u.s6a.aia.m_in);
        DISPLAY_TXT_COL (" ", runMode == INITIATOR?"3. Total ULR messages sent":"3. Total ULR messages received",   appStats.u.s6a.ulr.m_out);
        DISPLAY_TXT_COL (" ", runMode == INITIATOR?"4. Total ULA messages received":"4. Total ULA messages sent",   appStats.u.s6a.ula.m_in);
        DISPLAY_TXT_COL (" ", "5. Total CLR messages received",   appStats.u.s6a.clr.m_in);
        DISPLAY_TXT_COL (" ", "6. Total CLA messages sent",   appStats.u.s6a.cla.m_out);
        DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
        DISPLAY_DLINE ();
        //DISPLAY_LINE();*/
        DISPLAY_DLINE ();
        DISPLAY_BANNER2();
        DISPLAY_DLINE ();
        //DISPLAY_EMPTY_TEXT (" Diameter Simulator Messages ::");
        //DISPLAY_EMPTY_TEXT (" Running in Receiver Mode");
        //DISPLAY_DLINE ();
        //DISPLAY_LINE();
        //DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[appStats.recent_msg_idx%10].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+1)%10].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+2)%10].c_str());
        //DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+3)%10].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+4)%10].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+5)%10].c_str());
        //DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+6)%10].c_str());
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+7)%10].c_str());
        //DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+8)%10].c_str());
        //DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_TEXT (appStats.last_processed_msgs[(appStats.recent_msg_idx+9)%10].c_str());
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_DLINE ();
        DISPLAY_OPEN_TEXT ("Enter your choice _");
        printf("\n");
        printf("\n");

    }
    else if (displayMode == 100)
    {
        DISPLAY_TXT_COL ("1:  Send One ULR Message", runMode == INITIATOR?"1. Total AIR messages sent":"1. Total AIR messages received",   appStats.u.s6a.air.m_out);
        DISPLAY_TXT_COL ("2:  Send Ten ULR Messages", runMode == INITIATOR?"2. Total AIA messages received":"2. Total AIA messages sent",   appStats.u.s6a.aia.m_in);
        DISPLAY_TXT_COL ("3:  Send One AIR Message", runMode == INITIATOR?"3. Total ULR messages sent":"3. Total ULR messages received",   appStats.u.s6a.ulr.m_out);
        DISPLAY_TXT_COL ("4:  Send Ten AIR Messages", runMode == INITIATOR?"4. Total ULA messages received":"4. Total ULA messages sent",   appStats.u.s6a.ula.m_in);
        DISPLAY_TXT_COL (" ", "5. Total CLR messages received",   appStats.u.s6a.clr.m_in);
        DISPLAY_TXT_COL (" ", "6. Total CLA messages sent",   appStats.u.s6a.cla.m_out);
        DISPLAY_TXT_COL (" ", "7. Total rejected messages ",   appStats.m_failedCalls);
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        DISPLAY_EMPTY_TEXT (runMode == INITIATOR? " Running in Sender Mode" : " Running in Receiver Mode");
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        /*DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();
        DISPLAY_EMPTY_LINE ();*/
        DISPLAY_DLINE ();
        //DISPLAY_LINE();
        DISPLAY_OPEN_TEXT ("Enter your choice ('q' to return to previous menu) _ ");
        printf("\n");
        printf("\n");

    }

    int numberOfCall        = appStats.m_outMsgs + appStats.m_inMsgs;
    float averageCallRate     = (globalElapsedTime > 0 ? 1000*(float)numberOfCall/(float)globalElapsedTime : 0.0);
    numberOfCall        = (appStats.m_outMsgs - appStats.m_lastOutMsgs) + (appStats.m_inMsgs - appStats.m_lastInMsgs);
    float realInstantCallRate = (localElapsedTime  > 0 ? 
            1000*(float)numberOfCall / (float)localElapsedTime :
            0.0);

    //       DISPLAY_VAL_RATEF_TPS ("Call rate (/s)",  realInstantCallRate, averageCallRate);
    /*
       DISPLAY_CROSS_LINE ();
       DISPLAY_2VAL  ("Incoming calls", 
       (appStats.m_inMsgs - appStats.m_lastInMsgs),
       appStats.m_inMsgs);

       DISPLAY_2VAL  ("Outgoing calls", 
       (appStats.m_outMsgs - appStats.m_lastOutMsgs),
       appStats.m_outMsgs);
       */
    /*
       DISPLAY_2VAL_RATEF ( "Msg Recv/s" ,
       L_traffic_data->MsgRecvPerS,
       L_traffic_data->AverageMsgRecvPerS);

       DISPLAY_2VAL_RATEF ( "Msg Sent/s" ,
       L_traffic_data->MsgSendPerS,
       L_traffic_data->AverageMsgSendPerS);

       DISPLAY_2VAL  ("Unexpected msg",      
       m_displayCounters[CPT_PD_FailedCallUnexpectedMessage], 
       m_displayCounters[CPT_C_FailedCallUnexpectedMessage]);

       DISPLAY_2VAL_CURRENTF ("Current calls",       
       m_displayCounters[CPT_C_CurrentCall],
       L_traffic_data->AverageCurrentCallPerS);
       DISPLAY_CROSS_LINE2 ();

*/

    //    DISPLAY_2VAL  ("Successful calls", 
    //           m_displayCounters[CPT_PD_SuccessfulCall], 
    //           m_displayCounters[CPT_C_SuccessfulCall]);

    //    char L_values_periodic[100], L_values_cumulated[100];

    //    sprintf(L_values_periodic, "%ld/%ld/%ld/%ld", 
    //        m_displayCounters[CPT_PD_InitSuccessfulCall],
    //        m_displayCounters[CPT_PD_TrafficSuccessfulCall],
    //        m_displayCounters[CPT_PD_DefaultSuccessfulCall],
    //        m_displayCounters[CPT_PD_AbortSuccessfulCall]);
    //    sprintf(L_values_cumulated, "%ld/%ld/%ld/%ld", 
    //        m_displayCounters[CPT_C_InitSuccessfulCall],
    //        m_displayCounters[CPT_C_TrafficSuccessfulCall],
    //        m_displayCounters[CPT_C_DefaultSuccessfulCall],
    //        m_displayCounters[CPT_C_AbortSuccessfulCall]);

    //    DISPLAY_3TXT  ("Success calls(i/t/d/a)", 
    //           L_values_periodic,
    //           L_values_cumulated);

    /*
       DISPLAY_2VAL  ("Successful calls", 
       (appStats.m_successfulCalls - appStats.m_lastSuccessfulCalls),
       appStats.m_successfulCalls);


       DISPLAY_2VAL  ("Failed calls",      
       (appStats.m_failedCalls - appStats.m_lastFailedCalls), 
       appStats.m_failedCalls);
       */
    /*
       DISPLAY_2VAL  ("Refused calls",      
       m_displayCounters[CPT_PD_RefusedCall], 
       m_displayCounters[CPT_C_RefusedCall]);

       DISPLAY_2VAL  ("Aborted calls",      
       m_displayCounters[CPT_PD_FailedCallAborted], 
       m_displayCounters[CPT_C_FailedCallAborted]);

       DISPLAY_2VAL  ("Timeout calls",      
       m_displayCounters[CPT_PD_FailedCallTimeout], 
       m_displayCounters[CPT_C_FailedCallTimeout]);
       DISPLAY_CROSS_LINE ();
       DISPLAY_TXT("Last Info", m_info_msg);
       DISPLAY_TXT("Last Error", m_err_msg);
       DISPLAY_CROSS_LINE2 ();

*/
    gettimeofday (&periodicStartTime, NULL);
    appStats.m_lastSuccessfulCalls = appStats.m_successfulCalls;
    appStats.m_lastFailedCalls = appStats.m_failedCalls;
    appStats.m_lastOutMsgs = appStats.m_outMsgs;
    appStats.m_lastInMsgs = appStats.m_inMsgs;

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
        else if(strcmp(argv[i], "-name") == 0)
        {
            sim = strdup(argv[i+1]);
        }
    }

    AppInitialize(S6A_INTERFACE_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

