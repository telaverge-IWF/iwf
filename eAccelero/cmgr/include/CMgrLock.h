/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2014 Diametriq, LLC All Rights Reserved.              *
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


#ifndef _CMGR_LOCK_H_
#define _CMGR_LOCK_H_

#include <map>
#include <string>
#include "CMgrDbInterface.h"
#include "CMgrIwfDbInterface.h"
#include "MysqlInterfacePB.h"

class MysqlInterfacePB;
class CMgrDbInterface;
class CMgrIwfDbInterface;

typedef std::map<int, std::string> ReqIdToTableMap;
typedef std::pair<int, std::string> ReqIdToTablePair;

class CnfLockMgr
{
    private:
        MysqlInterfacePB *m_dbHandle;
        ReqIdToTableMap m_RTMap;
        std::string  CMgr_GetTable(int RequestID);
        int CMgr_GetMysqlLock(std::string tablename);
        int CMgr_ReleaseMysqlLock(std::string tablename,void *connFromCookie=NULL);
    public:
        int CMgr_GetLock(int RequestID);
        int CMgr_ReleaseLock(int RequestID,void *connFromCookie=NULL);
        CnfLockMgr(CMgrDbInterface *pCMgrDbInterface);
        CnfLockMgr(CMgrIwfDbInterface *pCMgrIwfDbInterface);
};

#endif
