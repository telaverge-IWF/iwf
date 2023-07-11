/* ********************************-*-H-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#ifndef __REPMGRCOMMON_H_
#define __REPMGRCOMMON_H_

using namespace eAccelero;

#include "ComponentDefines.h"

const unsigned RepMgrID = COMP_REPLICATION_MANAGER;
const unsigned I_REPMGR_ID = 101; // Replication Manager Interface ID
const unsigned I_DREAPP_ID = 201; // DRE Application Interface ID


// Wanna add more methods, add it immediately before
// REPMGR_INVALIDMETHOD 
  
enum RepMgrMethods { M_REPMGR_CACHE_DREBINDINFO = 1,
    M_REPMGR_UPDATE_DREBINDINFO,
    M_REPMGR_DELETE_DREBINDINFO,
    M_REPMGR_CACHE_DRERXBINDINFO,
    M_REPMGR_DELETE_DRERXBINDINFO,
    M_REPMGR_LOGLEVEL,
    M_REPMGR_INVALIDMETHOD
};

enum {
    M_DREAPP_SAVE_SESSION_ID = 1,
    M_DREAPP_UPDATE_SESSION_ID,
    M_DREAPP_DELETE_SESSION_ID,
    M_DREAPP_SAVE_RXSESSION_ID,
    M_DREAPP_DELETE_RXSESSION_ID
};

enum RM_ReturnCodes {
    RM_SUCCESS = 0, RM_CACHE_ERROR, RM_UPDATE_ERROR,
    RM_DELETEERROR, RM_INTERNAL_ERROR, RM_REPL_ERROR
};

struct DREBindResp
{
    // 0 ==> Success // Non-Zero ==> Error
    RM_ReturnCodes responseID;
};

struct DRERxBindInfo
{
    std::string    sessionId;       // KEY
    bool           isIPv4Address;   // Value1
    std::string    dreBindInfoKey;  // VALUE2 and is KEY to DREBindInfo
};

struct DREBindInfo
{
    std::string    dreBindInfoKey;     // KEY
    std::string    serverName;         // PCRF Name
    bool           isIPV6;             // Rest from here are Values
    unsigned int   counter;            // Tracking Interface Counter 
    unsigned int   sessionTerminateTimerId;  //ITS_SERIAL is Unsigned int
    unsigned int  gxSessionFlag:1;
    unsigned int  gxxSessionFlag:1;
    unsigned int  rxSessionFlag:1;
};

#endif  // __REPMGRCOMMON_H_

