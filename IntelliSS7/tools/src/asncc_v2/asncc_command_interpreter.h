///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: asncc_command_interpreter.h,v $
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:59  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_ASNCC_COMMAND_INTERPRETER_H_)
#define _ASNCC_COMMAND_INTERPRETER_H_

#ident "$Id: asncc_command_interpreter.h,v 9.1 2005/03/23 12:54:13 cvsadmin Exp $"

#include <asncc.h>
#include <asncc_assertion.h>
#include <asncc_command_file.h>
#include <asncc_ast.h>


////////////////////////////////////////////////////////////////////////////////
//
//  CommandInterpreter.
//

class CommandInterpreter
{
public:

    explicit CommandInterpreter(const std::string& commandFilePathParam)
    :   commandFile(commandFilePathParam),
        initialized(false)
    {};

    void Initialize();

    void Terminate();

    bool 
    IsInitialized() const
    { return initialized; }

    const CommandFile& 
    GetCommandFile() const
    { return commandFile; }

    void ProcessModule(Module& module);

protected:

    CommandFile commandFile;

    bool initialized;
};



#endif  // !defined(_ASNCC_COMMAND_INTERPRETER_H_)

