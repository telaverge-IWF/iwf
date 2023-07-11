/*********************************-*-C-*-************************************
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
 * LOG: $Log: sample_rx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:02  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:22:30  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: sample_rx.cpp,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_rx.cpp,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $"

#include <diameter/rx/AA.h>
#include <diameter/rx/AS.h>
#include <diameter/rx/RA.h>
#include <diameter/rx/ST.h>

#include <app.h>
#include <idc_api.h>
#include <rx_defines.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::rx;


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
int RxMessage(const diameter::CommandImpl *impl, unsigned int &sIdxRx)
{
    sIdxRx=sIdxRx;
    try
    {
        // Process the commands based on the command code.
        switch (impl->getCommandCode())
        {
        case RX_AA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                AARequest
                aaReq(*impl);
                cout << "Authentication Request" << aaReq << endl;
                SendRxAAAnswer(impl);
            }
            else
            {
                AAAnswer
                aaAns(*impl);
                cout << "Authentication Answer" << aaAns << endl;
            }
            break;

        case RX_RA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                RARequest
                raReq(*impl);
                cout << "Re-Auth-Request" << raReq << endl;
                SendRxRAAnswer(impl);
            }
            else
            {
                RAAnswer
                raAns(*impl);
                cout << "Re-Auth-Answer" << raAns << endl;
            }
            break;
           
        case RX_ST_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                STRequest
                stReq(*impl);
                cout << "SessionTerminationRequest" << stReq <<endl;
                SendRxSTAnswer(impl);
            }
            else
            {
                STAnswer
                stAns(*impl);
                cout << "SessionTerminationAnswer" << stAns 
                <<endl;
            }
            break;

        case RX_AS_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                ASRequest
                asReq(*impl);
                cout << "AbortSessionRequest" << asReq << endl;
                SendRxASAnswer(impl);
            }
            else
            {
                ASAnswer
                asAns(*impl);
                cout << "AbortSessionAnswer" << asAns << endl;
            }
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

    return (ITS_SUCCESS);
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
 *  Revision History:
 *  See Also:
 ****************************************************************************/
int RxMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Rx Command" <<endl << endl;
            cout << "1: AA - Multimedia Auth Request" << endl;
            cout << "2: RA - Re-Auth Request" << endl;
            cout << "3: ST - Session Termination Request" << endl;
            cout << "4: AS - Abort Session Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        switch (ret)
        {
        case 1:
            SendRxAARequest();
            break;
        case 2:
            SendRxRARequest();
            break;
        case 3:
            SendRxSTRequest();
            break;
        case 4:
            SendRxASRequest();
            break;
        case 99:
            k=0;
            break;
        default:
            cout << endl << "please enter the correct choice";
            break;
        }
    }
    return 0;
}
