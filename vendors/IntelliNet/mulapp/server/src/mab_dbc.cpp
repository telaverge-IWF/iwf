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
 * ID: $Id: mab_dbc.cpp,v 1.1 2005/05/25 10:13:59 mmanikandan Exp $
 *
 * LOG: $Log: mab_dbc.cpp,v $
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <mab_dbc.h>

#define ALPHABET  "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
#define SPECIAL_CHAR  "#\\`~!@$%^&*()-_+=|^?{}[]:;'<>,.?/"

MAB_DbcServer* MAB_DbcServer::dbcServer_ = NULL;

MAB_DbcServer*
MAB_DbcServer::GetDBCServer (const std::string& nameParam)
{
    if (dbcServer_ == NULL)
    {
        dbcServer_ = new MAB_DbcServer(nameParam);
    }
    return dbcServer_;
}

MAB_DbcServer::MAB_DbcServer (const std::string& nameParam)
    : its::DbcServer(nameParam)
{
}

void 
MAB_DbcServer::DoCommand(std::istream& commandLine)
{
    if (Cmd("SendUIS", "Send User In Service message", "<>"))
    {
//        GW_SendUserInService();
        oss << "User In Service message send successfully\n";
    }
    else if (Cmd("SendUOS", "Send User Out Service message", "<>"))
    {
//        GW_SendUserOutOfService();
        oss << "User Out Service message send successfully\n";
    }
    else if (Cmd("gw_menu", "Menu", "<>"))
    {
        oss<< "\n   COMMAND                      DESCRIPTION                   "
           << "\n=============================================================="
           << "\nSendUIS                 Send User In Service message"
           << "\nSendUOS                 Send User Out Service message"  
          
           << "\n=============================================================";
    }
}
