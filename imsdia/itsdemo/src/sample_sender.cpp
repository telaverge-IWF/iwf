/*********************************-*CPP*-************************************
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
 * LOG: $Log: sample_sender.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.8  2006/06/02 09:20:58  yranade
 * LOG: Minor update
 * LOG:
 * LOG: Revision 1.7  2006/06/02 04:48:58  kamakshilk
 * LOG: RfRo function calls
 * LOG:
 * LOG: Revision 1.6  2006/04/25 15:33:39  nvijikumar
 * LOG: Documentation
 * LOG:
 * LOG: Revision 1.5  2006/04/22 00:07:50  ahanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2006/04/17 16:25:11  yranade
 * LOG: Load Generator Support.
 * LOG:
 * LOG: Revision 1.3  2006/03/24 05:21:51  nvijikumar
 * LOG: Added exit case for Menu
 * LOG:
 * LOG: Revision 1.2  2006/03/08 08:48:17  nvijikumar
 * LOG: Baseline for GqGqprime sample applications
 * LOG:
 * LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 * LOG: First Version of Demo Application.
 * LOG:
 *
 * ID: $Id: sample_sender.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_sender.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $"

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>
#include <app.h>

using namespace std;
using namespace its;
using namespace engine;


extern "C"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Method to invoke the proper interface Display functions 
 *      To send the Request Messages to the stack
 *
 *  Input Parameters:
 *      thr - type ThreadPoolThread. arg - type void..
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

void SenderThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret;

    if (appMode == LOAD_TEST)
    {
        GenerateLoad();
        return;
    }
    
    while (1)
    {
        // Display Based on the Choice made in the Menu

        switch (commandSet)
        {
        case 1:
            ret = DisplayBaseMenu();
            SendBaseMessage(ret);
            break;

        case 2:
            ret = DisplayShMenu();
            SendShMessage(ret);
            break;
         
        case 3:
            ret = DisplayCxdxMenu();
            SendCxdxMessage(ret);
            break;
        case 4:
            ret = DisplayGqMenu();
            SendGqMessage(ret);
            break;
        case 5:
            ret = DisplayRfRoMenu();
            SendRfRoMessage(ret);
            break;
        case 99:
	    exit(1);
        default:
            cout << "Invalid Choice " << endl;
            break;
    }
}

}
