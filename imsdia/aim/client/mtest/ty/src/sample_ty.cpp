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
 * LOG: $Log: sample_ty.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.4  2006/11/29 12:33:14  kamakshilk
 * LOG: Send App Id changed to TY app Id
 * LOG:
 * LOG: Revision 1.3  2006/11/17 07:36:13  kamakshilk
 * LOG: ReleaseSession added
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:27:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: sample_ty.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_ty.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $"

#include <diameter/ty/CC.h>
#include <diameter/ty/RA.h>

#include <app.h>
#include <idc_api.h>
#include <ty_defines.h>

using namespace std;
using namespace diameter;
using namespace diameter::ty;

unsigned int sIdxTy = 0;
IDSCLApi apiTy;

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
int TyMessage(const diameter::CommandImpl *impl, unsigned int &sIdxTy)
{
    sIdxTy=sIdxTy;
    try
    {
        // Process the commands based on the command code.
        switch (impl->getCommandCode())
        {
        case TY_CC_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                CCRequest
                ccReq(*impl);
                cout << "CreditControlRequest" << ccReq << endl;
                SendTyCCAnswer(impl);
            }
            else
            {
                CCAnswer
                ccAns(*impl);
                cout << "CreditControlAnswer" << ccAns << endl;
                /* Release session context */
                if (!apiTy.IsDccaEnabled())
                {
                    switch(ccAns.getCCRequestType().value())
                    {
                       case CCRequestType::EVENT_REQUEST:
                       case CCRequestType::TERMINATION_REQUEST:
                           std::string rlsStr =
                                       ccAns.getSessionId().value();
                           apiTy.ReleaseSession(rlsStr, 
                               ccAns.getSessionIndex());
                           break;
                    }
                }
            }
            break;

        case TY_RA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                RARequest
                raReq(*impl);
                cout << "Re-AuthRequest" << raReq << endl;
                SendTyRAAnswer(impl);
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
 *  See Also:
 ****************************************************************************/
int TyMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Ty Command" <<endl << endl;
            cout << "1: CCR - Credit Control Request" << endl;
            cout << "2: RAR - Re-Auth Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 2) && ret!=99);

        switch (ret)
        {
        case 1:
            SendTyCCRequest();
            break;
        case 2:
            SendTyRARequest();
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
