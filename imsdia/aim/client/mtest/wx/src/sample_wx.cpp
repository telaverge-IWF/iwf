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
 * LOG: $Log: sample_wx.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:29:52  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: sample_wx.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_wx.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $"

#include <diameter/wx/PushProfile.h>
#include <diameter/wx/ServerAssignment.h>
#include <diameter/wx/MultimediaAuthentication.h>
#include <diameter/wx/RegistrationTermination.h>

#include <app.h>
#include <idc_api.h>
#include <wx_defines.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::wx;


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
int WxMessage(const diameter::CommandImpl *impl, unsigned int &sIdxwx)
{
    sIdxwx=sIdxwx;
    try
    {
        // Process the commands based on the command code.
        switch (impl->getCommandCode())
        {
        case WX_SA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                ServerAssignmentRequest
                sareq(*impl);
                cout << "ServerAssignmentRequest" << sareq << endl;
                SendWxServerAssignmentAnswer(impl);
            }
            else
            {
                ServerAssignmentAnswer
                saans(*impl);
                cout << "ServerAssignmentAnswer" << saans << endl;
            }
            break;

        case WX_MA_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                MultimediaAuthenticationRequest
                mareq(*impl);
                cout << "MultimediaAuthenticationRequest" << mareq << endl;
                SendWxMultimediaAuthenticationAnswer(impl);
            }
            else
            {
                MultimediaAuthenticationAnswer
                maans(*impl);
                cout << "MultimediaAuthenticationAnswer" << maans << endl;
            }
            break;
           
        case WX_RT_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                RegistrationTerminationRequest
                rtreq(*impl);
                cout << "RegistrationTerminationRequest" << rtreq <<endl;
                SendWxRegistrationTerminationAnswer(impl);
            }
            else
            {
                RegistrationTerminationAnswer
                rtans(*impl);
                cout << "RegistrationTerminationAnswer" << rtans 
                <<endl;
            }
            break;

        case WX_PP_MSG_CMD_CODE:
            if (impl->isRequest())
            {
                PushProfileRequest
                ppreq(*impl);
                cout << "PushProfileRequest" << ppreq << endl;
                SendWxPushProfileAnswer(impl);
            }
            else
            {
                PushProfileAnswer
                ppans(*impl);
                cout << "PushProfileAnswer" << ppans << endl;
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
int WxMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select Cx/Dx Command" <<endl << endl;
            cout << "1: MAR - Multimedia Auth Request" << endl;
            cout << "2: PPR - Push Profile Request" << endl;
            cout << "3: RTR - Registration Termination Request" << endl;
            cout << "4: SAR - Server Assignment Request" << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;
            ret=atoi(input.c_str());

        } while ((ret < 1 || ret > 4) && ret!=99);

        switch (ret)
        {
        case 1:
            SendWxMultimediaAuthenticationRequest();
            break;
        case 2:
            SendWxPushProfileRequest();
            break;
        case 3:
            SendWxRegistrationTerminationRequest();
            break;
        case 4:
            SendWxServerAssignmentRequest();
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
