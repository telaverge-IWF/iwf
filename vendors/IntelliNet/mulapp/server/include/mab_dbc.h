/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: mab_dbc.h,v 1.1 2005/05/25 10:13:59 mmanikandan Exp $
 *
 * LOG: $Log: mab_dbc.h,v $
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef _MAB_DBC_H
#define _MAB_DBC_H

#include <its++.h>
#include <dbc_server.h>
#include <dbc_serv.h>

class MAB_DbcServer : public its::DbcServer
{
public:
    static MAB_DbcServer* GetDBCServer (const std::string& nameParam);
    virtual ~MAB_DbcServer() {};
    virtual void DoCommand(std::istream& commandLine);
private:
    MAB_DbcServer (const std::string& nameParam);
    static MAB_DbcServer* dbcServer_;
};

#endif
