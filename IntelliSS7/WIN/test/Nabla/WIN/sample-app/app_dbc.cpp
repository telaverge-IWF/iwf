////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>
#include <app_dbc.h>

#undef ITS_TRACE_H
#undef USE_CPLUSPLUS

using namespace std;
using namespace its;


void
APPDbcServer::DoCommand(istream& commandLine)
{
    string dummy;

    if (Cmd("ap_info", "", ""))
    {
         oss << "ISOFTEL SCP version 1.0" << endl;
    }
    else if (Cmd("ap_test", "", ""))
    {
         oss << "Sample MML Console" << endl;
    }
}

