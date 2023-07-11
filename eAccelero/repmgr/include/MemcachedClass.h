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

#ifndef  __MEMCACHEDCLASS_H__
#define  __MEMCACHEDCLASS_H__

#include <libmemcached/memcached.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "HashInterface.h"

enum FromSource { FROMTIMER = 1, FROMINIT };
const std::string TmpFilePrefix = "/tmp/TmpReplMemc-";
const std::string TmpFilePattern = "/tmp/TmpReplMemc-*";

// Class for handling Memcached server communication 
class MemcachedClient : public HashInterface
{
    // Attributes
    std::string MemcServers;      // to hold list of servernames
    memcached_st *mServer;        // Used to access our memcached server 
    memcached_server_st *mServers;  // List of Memcached servers

    public:
    //Constructor
    MemcachedClient(std::string servername);
    ~MemcachedClient();   // Destructor

    // Required Methods ==> MUST -- Start
    bool InitializeCache(void);
    int GetTotalRecordsNum(void);
    void StoreEntry(KeyValue kvl);
    KeyValue GetEntry(std::string Key);
    bool DeleteEntry(std::string Key);
    // Required Methods  ==> MUST -- End

    int OnTimerEvt(TimerEvent& event);
    private:
    time_t m_CacheTimeout;
    pid_t MemcPID;
    std::string TmpRepFileName;
    bool AddServer(std::string servername);
    bool MemcachedExists(FromSource frmSrc);
    bool StartMemcachedServer(void);
    //EventHandlerId memc_tid;
}; // Class MemcachedClient


#endif  //  __MEMCACHEDCLASS_H__

