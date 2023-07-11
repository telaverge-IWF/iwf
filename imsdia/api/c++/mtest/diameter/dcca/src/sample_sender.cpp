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
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/11/24 20:13:08  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:48:57  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/27 15:13:22  hbhatnagar
 * LOG: Modified for bcgi demo (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/27 09:41:48  hbhatnagar
 * LOG: Fix for Bug ID: 4383 and cleaning (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:18  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: sample_sender.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_sender.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>
#include <app.h>
#include <dcca_defines.h>
#include <dcca_test.h>


using namespace std;
using namespace its;
using namespace engine;


extern int DisplayDccaMenuTest(int *); 
extern int DisplayDccaMenuTestServer(int * );
extern int SendDccaMessageServer ( int , int ); 
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

void DccaSendThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret = 0;

    if (appMode == LOAD_TEST)
    {
        //  GenerateLoad();
        return;
    }
    
    while (1)
    {
        int index1 = 0;
        int index2 = 0;    
        // Display Based on the Choice made in the Menu
        switch (commandSet)
        {
        case 1:
            ret = DisplayDccaMenuTest(&index1);
            SendDccaMessage(ret, index1);
        break;

        case 2: 
            ret = DisplayDccaMenuTestServer(&index2);
            SendDccaMessageServer(ret,index2);
        break;
 
        case 9:
        exit(1);
        }
    }

}
