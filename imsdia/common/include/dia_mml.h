/*********************************-*-CDIA-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: dia_mml.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $
 *
 *  LOG: $Log: dia_mml.h,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/04/07 11:35:46  yranade
 *  LOG: DoxyGen Compatible Code Comments.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 *  LOG: Building IMS Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_mml.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $"

#if !defined(_DIA_MML_H_)
#define _DIA_MML_H_

#include <its++.h>
#include <dbc_server.h>
#include <string>

/* Interface:
 *      DiaMMLServer
 *      
 *  Purpose:
 *      DiaMMLServer class is used to encapsulate all Diameter stack 
 *      abstraction related MML Commands.
 */
class DiaMMLServer : public its::DbcServer
{
public:
    DiaMMLServer(const std::string& nameParam)
        : its::DbcServer(nameParam), unknownArgument("")
    {};

    virtual ~DiaMMLServer()
    {};

    virtual void DoCommand(std::istream& commandLine);

    const std::string& GetUnknownArgument() const
    { return unknownArgument; }

protected: 

    std::string unknownArgument;

};


#endif

