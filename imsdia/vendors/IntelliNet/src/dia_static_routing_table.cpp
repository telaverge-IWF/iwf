/*********************************-*-CPP-*-**********************************
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
 ***************************************************************************/
#include <its++.h>
#include <dia_static_routing_table.h>
#include <algorithm>
#include<dia_ip_trans.h>
#if defined(ITS_STD_NAMESPACE)
using namespace its;
#endif

ITS_Mutex StaticRoutingTable::m_staticRoutingObjectGuard(0);

StaticRoutingTable* StaticRoutingTable::m_staticRoutingTable = NULL;


/*.implementation:static
 ****************************************************************************
 *  Purpose: Static method to create the object.StaticRoutingTable is a 
 *           singleton class
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None 
 *  Return Value:
 *        Returns the StaticRoutingTable object. 
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
StaticRoutingTable*
StaticRoutingTable::GetStaticRoutingTable()
{

    ITS_ASSERT(StaticRoutingTable::m_staticRoutingObjectGuard.Acquire() == ITS_SUCCESS);
    if (m_staticRoutingTable == NULL)
    {

        m_staticRoutingTable = new StaticRoutingTable;

    }
    StaticRoutingTable::m_staticRoutingObjectGuard.Release();
    return m_staticRoutingTable;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Destructor.free all elements in the list.
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
StaticRoutingTable::~StaticRoutingTable()
{  
    WriteLock();

    for (TypeStaticRoutingTable::iterator iter = m_staticEntriesTable.begin();
                                       iter != m_staticEntriesTable.end();
                                       iter++)
    {
        STATIC_ROUTE_ENTRY* entry = (*iter);

        if (entry != NULL)
        {
            delete entry;
            entry = NULL;
        }
    }
    m_staticEntriesTable.clear();
    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:Locks the Static routing table for read.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StaticRoutingTable::ReadLock()
{
    pthread_rwlock_rdlock(&m_routingTableLock);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:Locks the Static routing table for write.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StaticRoutingTable::WriteLock()
{
    pthread_rwlock_wrlock(&m_routingTableLock);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:Unlocks the static routing table after the read/write.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StaticRoutingTable::Unlock()
{
    pthread_rwlock_unlock(&m_routingTableLock);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:Searches for the peer throu which message to be routed.
 *          takes 3 parameters but 3rd parameter is optional.
 *  Input Parameters:
 *        DestinationHost,DestinationRealm and applicationId from the 
 *        incoming message. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *       Returns the peer name if found in the table otherwise NULL.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
bool
StaticRoutingTable::FindPeer(const char *destRealm,const char *destHost,
                            char *peerToReturn,ITS_USHORT &peerInstance,ITS_UINT appId)
{  

    STATIC_ROUTE_ENTRY *staticRouteEntry = NULL;
    int ret = !ITS_SUCCESS;
    ReadLock();
   
    if(m_staticEntriesTable.size() == 0)
    {
        DT_DBG(("Static routing table is empty"));
    }
    else
    {
        for (TypeStaticRoutingTable::iterator iter = m_staticEntriesTable.begin();
         iter != m_staticEntriesTable.end(); iter++)
        {
            staticRouteEntry = (*iter);
            if((strcasecmp(staticRouteEntry->realmName.c_str(),destRealm)==0) &&
               (strcasecmp(staticRouteEntry->destinationHostName.c_str(),destHost)==0) &&
               (appId == staticRouteEntry->appId || staticRouteEntry->appId == 0))
            {
                const char * peerName = staticRouteEntry->peerName.c_str();
                PEER_ENTRY *peer = NULL;
                bool found = PEER_TABLE->FindEntry(peerName, peer);
                if(!found || !peer)
                {
                    DT_DBG(("Peer %s found in static routing table but not in peer table.search next",peerName));
                }
                else
                {
                    ret = ITS_SUCCESS;
                    strcpy(peerToReturn,peerName);
                    ITS_USHORT inst = DIA_PE_INST(peer);
                    DiaSocketTransport *tr = trTable[inst];
                    if (tr && tr->GetPeer())
                    {
                        peerInstance = inst;
                        DT_DBG(("Peer %s selected from static routing table",peerToReturn));
                        break;
                    }
                }
            }
        }
    }   

    Unlock();

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Method to insert the intries to static routing table.
 *
 *  Input Parameters:pointer to static routing entry.
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StaticRoutingTable::InsertEntry(STATIC_ROUTE_ENTRY* entryParam)
{
    WriteLock();

    DT_DBG(("Entry to be added to static routing table"));
   
    DT_DBG(("realmName=%s,destName=%s,PeerName=%s,priority=%u,applicationId=%u",entryParam->realmName.c_str(),
             entryParam->destinationHostName.c_str(),entryParam->peerName.c_str(),entryParam->priority,entryParam->appId)); 
    m_staticEntriesTable.push_back(entryParam);
  
    //Sort peers based on priority
    m_staticEntriesTable.sort(ComparePeers);
   
    Unlock();
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Method to modify priority 
 *
 *  Input Parameters:destHost, peername and priority
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  sucess or failure
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

//Use only destHost and peer name as it going to be fully qualified domain name.
//realm name not required.
int
StaticRoutingTable::ModifyPriorityOfEntry(const char* destHost,const char*peer,
                                          int priority,ITS_UINT appId)
{
    int ret = !ITS_SUCCESS;

    DT_DBG(("Priority to be modified for destHost=%s,peer=%s,appId=%u to priority=%d",
             destHost,peer,appId,priority));

    WriteLock();

    TypeStaticRoutingTable::iterator it = m_staticEntriesTable.begin();
    for(;it!=m_staticEntriesTable.end();it++)
    {
        if(strcasecmp((*it)->peerName.c_str(),peer)==0 && (*it)->appId== appId &&
           strcasecmp((*it)->destinationHostName.c_str(),destHost)==0)
        {
            (*it)->priority=priority;
            DT_DBG(("Successfully modified"));
            ret = ITS_SUCCESS;
            break;
        }
    }
 
    if(ret == ITS_SUCCESS)
    { 
        //Sort peers based on priority
        m_staticEntriesTable.sort(ComparePeers);
    } 
    Unlock();
    return ret;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose: Method to static routing entry 
 *
 *  Input Parameters:desthost and peer name
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  success or failure
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

//Use only destHost and peer name as it going to be fully qualified domain name.
//realm name not required.
int
StaticRoutingTable::RemoveEntry(const char* destHost,const char*peer,ITS_UINT appId)
{
    int ret = !ITS_SUCCESS;

    DT_DBG(("Entry to be deleted for destHost=%s,peer=%s,appId = %u",destHost,peer,appId));

    WriteLock();

    TypeStaticRoutingTable::iterator it = m_staticEntriesTable.begin();
    for(;it!=m_staticEntriesTable.end();it++)
    {
        if(strcasecmp((*it)->peerName.c_str(),peer)==0 && (*it)->appId == appId &&
           strcasecmp((*it)->destinationHostName.c_str(),destHost)==0)
        {
            delete(*it);
            m_staticEntriesTable.erase(it);
            DT_DBG(("Successfully deleted"));
            ret = ITS_SUCCESS;
            break;
        }
    }
 
    if(ret == ITS_SUCCESS)
    { 
        //Sort peers based on priority
        m_staticEntriesTable.sort(ComparePeers);
    } 
    Unlock();
    return ret;
}
