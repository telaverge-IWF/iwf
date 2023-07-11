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
 * LOG: $Log: sample_gx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:01  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2008/03/27 11:18:29  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.4  2006/11/29 12:31:08  kamakshilk
 * LOG: Send App Id changed to GX_APP_ID
 * LOG:
 * LOG: Revision 1.3  2006/11/17 07:07:26  kamakshilk
 * LOG: ReleaseSesion Added
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:12:37  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: sample_gx.cpp,v 3.1 2008/03/31 10:33:01 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_gx.cpp,v 3.1 2008/03/31 10:33:01 nvijikumar Exp $"

#include <diameter/gx/CC.h>
#include <diameter/gx/RA.h>

#include <app.h>
#include <idc_api.h>
#include <gx_defines.h>

using namespace std;
using namespace diameter;
using namespace diameter::gx;

unsigned int sIdxGx = 0;
IDSCLApi apiGx;

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
int GxMessage(const diameter::CommandImpl *impl, unsigned int &sIdxGx)
{
    sIdxGx=sIdxGx;
    try
    {
        // Process the commands based on the command code.
        switch (impl->getCommandCode())
        {
        case GX_CC_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                CCRequest
                ccReq(*impl);
                cout << "CreditControlRequest" << ccReq << endl;
                SendGxCCAnswer(impl);
            }
            else
            {
                CCAnswer
                ccAns(*impl);
                cout << "CreditControlAnswer" << ccAns << endl;
                /* Release session context */
                if (!apiGx.IsDccaEnabled())
                {
                    switch(ccAns.getCCRequestType().value())
                    {
                       case CCRequestType::EVENT_REQUEST:
                       case CCRequestType::TERMINATION_REQUEST:
                           std::string rlsStr =
                                       ccAns.getSessionId().value();
                           apiGx.ReleaseSession(rlsStr, 
                               ccAns.getSessionIndex());
                           break;
                    }
                }

            }
            break;

        case GX_RA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                RARequest
                raReq(*impl);
                cout << "Re-AuthRequest" << raReq << endl;
                SendGxRAAnswer(impl);
            }
            else
            {
                RAAnswer
                raAns(*impl);
                cout << "Re-AuthAnswer" << raAns << endl;
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int GxMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Gx Command" <<endl << endl;
            cout << "1: CCR - Credit Control Request" << endl;
            cout << "2: RAR - Re-Auth Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 2) && ret!=99);

        switch (ret)
        {
        case 1:
            SendGxCCRequest();
            break;
        case 2:
            SendGxRARequest();
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
