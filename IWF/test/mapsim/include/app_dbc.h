/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: app_dbc.h,v $
 * LOG: Revision 1.1.2.1  2013/02/12 14:11:30  jvikas
 * LOG: Map Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_dbc.h,v 1.1.2.1 2013/02/12 14:11:30 jvikas Exp $"

#if !defined(_TCAP_DBC_H_)
#define _TCAP_DBC_H_

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#include <its++.h>
#include <dbc_server.h>
#include <string>

class TCAPDbcServer : public its::DbcServer
{
public:
    TCAPDbcServer(const std::string& nameParam)
        : its::DbcServer(nameParam), unknownArgument("")
    {};

    virtual ~TCAPDbcServer()
    {};

    virtual void DoCommand(std::istream& commandLine);

    void DoCommandWithoutExceptionHandler(std::istream& commandLine);
    
    const std::string& 
    GetUnknownArgument() const
    { return unknownArgument; }   

protected:

    void DoMTP3Management(std::istream& commonLine);

    void DoSCCPManagement(std::istream& commonLine);
 
    int ParseCmdLine(const std::vector<std::string>& arguments);

    int ReportInvalidCmdLine(int parseError);

    std::string unknownArgument;
};

#endif    // !defined(_TCAP_DBC_H_)
