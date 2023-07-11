/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2012 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
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
 ****************************************************************************/

#if !defined DIA_STATIC_ROUTING_TABLE_H_
#define DIA_STATIC_ROUTING_TABLE_H_

#include <list>
#include <pthread.h>    

#include <its_mutex.h>
#include <dia_peer_table.h>



typedef struct _static_route_entry
{
    std::string  realmName;
    std::string  destinationHostName;
    std::string  peerName;
    ITS_UINT     priority;
    ITS_UINT     appId;
}
STATIC_ROUTE_ENTRY;


class StaticRoutingTable
{
public:
    static StaticRoutingTable *GetStaticRoutingTable();

    bool FindPeer(const char *destRealm,const char *destHost, char* peerName,ITS_USHORT &peerInstance,ITS_UINT appId = 0);

    void InsertEntry(STATIC_ROUTE_ENTRY *routeEntry);

    int ModifyPriorityOfEntry(const char* destHost,const char*peer, int priority,ITS_UINT appId);

    int RemoveEntry(const char* destHost,const char*peer,ITS_UINT appId);

    static bool ComparePeers(const STATIC_ROUTE_ENTRY *firstObj,const STATIC_ROUTE_ENTRY *secObj)
           { return (firstObj->priority<secObj->priority);} 

private:
    typedef std::list<STATIC_ROUTE_ENTRY*>TypeStaticRoutingTable;
       
    TypeStaticRoutingTable m_staticEntriesTable;

    static its::ITS_Mutex m_staticRoutingObjectGuard;

    StaticRoutingTable() 
    {
        pthread_rwlock_init(&m_routingTableLock,NULL);
    };

    pthread_rwlock_t m_routingTableLock;
    
    ~StaticRoutingTable();

    StaticRoutingTable(StaticRoutingTable&) {};

    void ReadLock();
    
    void WriteLock();

    void Unlock();

    static StaticRoutingTable *m_staticRoutingTable;
};


#define STATIC_ROUTING_TABLE StaticRoutingTable::GetStaticRoutingTable()

#endif
