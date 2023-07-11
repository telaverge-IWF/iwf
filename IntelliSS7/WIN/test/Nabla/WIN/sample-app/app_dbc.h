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
//

#if !defined(_TCAP_DBC_H_)
#define _APP_DBC_H_

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#include <its++.h>
#include <dbc_server.h>
#include <string>

class APPDbcServer : public its::DbcServer
{
public:
    APPDbcServer(const std::string& nameParam)
        : its::DbcServer(nameParam)
    {};

    virtual ~APPDbcServer()
    {};

    virtual void DoCommand(std::istream& commandLine);

    void DoCommandWithoutExceptionHandler(std::istream& commandLine);
    
protected:

};

#endif    // !defined(_APP_DBC_H_)
