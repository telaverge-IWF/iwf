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
 * LOG: $Log: Main.cpp,v $
 * LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
 * LOG: Create baseline imsdia project in CVS.
 * LOG:
 *
 * ID: $Id: Main.cpp,v 1.1.1.1 2006/02/16 12:16:44 yranade Exp $
 *
 ***************************************************************************/
#ident "$Id: Main.cpp,v 1.1.1.1 2006/02/16 12:16:44 yranade Exp $"
#include <iostream.h>
#include <CapabilitiesExchange.h>

extern int testCapabilitiesExchangeRequest();
extern int testAccountingRequest();
extern int testDeviceWatchdogRequest();
extern int testDisconnectPeerRequest();
extern int testReAuthRequest();
extern int testSessionTerminationRequest();
extern int testAbortSessionRequest();
int main()
{
cout <<  endl << "Enter choice no for the given following base messages"<<endl<<endl;
cout << endl <<"(1) . Accouting Command"<<endl;
cout << endl <<"(2) . Capability Exchange Command"<<endl;
cout << endl <<"(3) . Device Watchdog Command"<<endl;
cout << endl <<"(4) . Disconnect Peer Command"<<endl;
cout << endl <<"(5) . ReAuth Command"<<endl;
cout << endl <<"(6) . Session Termination Command"<<endl;
cout << endl <<"(7) . Abort Session Command"<<endl;
int input;
cin>>input;
switch(input)
{
case 1:
    return testAccountingRequest();
case 2:
    return testCapabilitiesExchangeRequest();
case 3:
    return testDeviceWatchdogRequest();
case 4:
    return testDisconnectPeerRequest();
case 5:
    return testReAuthRequest();
case 6:
    return testSessionTerminationRequest();
case 7:
    return testAbortSessionRequest();
default:
    cout<<endl<<"please enter the correct choice";
}
return 0;
}
