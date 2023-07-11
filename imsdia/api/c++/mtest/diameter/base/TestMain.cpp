/****************************************************************************
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
 * LOG: $Log: TestMain.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
 * LOG: Create baseline imsdia project in CVS.
 * LOG:
 *
 * ID: $Id: TestMain.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: TestMain.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"
#include <iostream.h>
#include <CapabilitiesExchange.h>

extern int EncodeCapabilitiesExchangeReq();
extern int EncodeAccountingReq();
extern int EncodeDeviceWatchdogReq();
extern int EncodeDisconnectPeerReq();
extern int EncodeReAuthReq();
extern int EncodeSessionTerminationReq();
extern int EncodeAbortSessionReq();

int main()
{
    cout <<  endl << "Enter choice no for the given following base messages"<<endl<<endl;
    cout << endl <<"(1) . Accouting Req Command"<<endl;
    cout << endl <<"(2) . Capability Exchange Req Command"<<endl;
    cout << endl <<"(3) . Device Watchdog Req Command"<<endl;
    cout << endl <<"(4) . Disconnect Peer Req Command"<<endl;
    cout << endl <<"(5) . ReAuth Req Command"<<endl;
    cout << endl <<"(6) . Session Termination Req Command"<<endl;
    cout << endl <<"(7) . Abort Session Req Command"<<endl;
    int input;
    cin>>input;
    switch(input)
    {
    case 1:
        return EncodeAccountingReq();
    case 2:
        return EncodeCapabilitiesExchangeReq();
    case 3:
        return EncodeDeviceWatchdogReq();
    case 4:
        return EncodeDisconnectPeerReq();
    case 5:
        return EncodeReAuthReq();
    case 6:
        return EncodeSessionTerminationReq();
    case 7:
        return EncodeAbortSessionReq();
    default:
        cout<<endl<<"please enter the correct choice";
    }
    return 0;
}
