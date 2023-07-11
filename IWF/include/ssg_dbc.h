/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  ID: $Id: ssg_dbc.h,v 1.1.1.1.2.1 2013/06/19 12:40:53 jsarvesh Exp $
 *
 *  LOG: $Log: ssg_dbc.h,v $
 *  LOG: Revision 1.1.1.1.2.1  2013/06/19 12:40:53  jsarvesh
 *  LOG: MML implementation for IWF Statistics
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:35  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#if !defined(_SSG_DBC_H_)
#define _SSG_DBC_H_

#include <its++.h>
#include <dbc_server.h>
#include <dia_mml.h>
#include <string>


class SsgDbcServer : public DiaMMLServer
{
public:
    SsgDbcServer(const std::string& nameParam)
        : DiaMMLServer(nameParam)
        //: its::DbcServer(nameParam), unknownArgument("")
    {};

    virtual ~SsgDbcServer()
    {};

    virtual void DoCommand(std::istream& commandLine);

    void DoCommandWithoutExceptionHandler(std::istream& commandLine);

    const std::string&
    GetUnknownArgument() const
    { return unknownArgument; }

protected:

    int ParseCmdLine(const std::vector<std::string>& arguments);

    int ReportInvalidCmdLine(int parseError);

    std::string unknownArgument;
};

#endif

