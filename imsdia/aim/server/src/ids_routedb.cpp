/*********************************-*-CPP-*-**********************************
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
 *  ID: $Id: ids_routedb.cpp,v 3.9 2010/10/19 12:33:10 vkumara Exp $
 *
 *  LOG: $Log: ids_routedb.cpp,v $
 *  LOG: Revision 3.9  2010/10/19 12:33:10  vkumara
 *  LOG: printIdsRouteTbl endIp range changed
 *  LOG:
 *  LOG: Revision 3.8  2010/10/05 06:16:10  vkumara
 *  LOG: FindBestMatch check changed for validating IP Addr range
 *  LOG:
 *  LOG: Revision 3.7  2010/09/22 05:26:37  nvijikumar
 *  LOG: GlobalUniqueAddr based routing/distribution support
 *  LOG:
 *  LOG: Revision 3.6  2010/08/19 11:23:06  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.5.2.1  2010/04/26 06:28:26  rajeshak
 *  LOG: 1.Locking the complete operation in FindBestMatch to avoid List corruption.
 *  LOG: 2.Proper Handling of Timeout indication
 *  LOG:
 *  LOG: Revision 3.5  2009/09/07 05:31:10  rajeshak
 *  LOG: Klockworks reported Issue fix.
 *  LOG:
 *  LOG: Revision 3.4  2009/03/19 16:37:06  ssaxena
 *  LOG: Made changes in the debug traces for redirect application Id
 *  LOG:
 *  LOG: Revision 3.3  2009/03/03 11:10:47  rajeshak
 *  LOG: Klockwork reported issue fix
 *  LOG:
 *  LOG: Revision 3.2  2008/10/31 05:35:24  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.9  2008/03/27 11:21:05  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.6.6.3  2007/03/16 12:05:34  hbhatnagar
 *  LOG: added the missing bIter in RemoveEntry function
 *  LOG:
 *  LOG: Revision 2.6.6.2  2007/03/15 18:24:09  hbhatnagar
 *  LOG: added RemoveEntryWithAppId definition and call it appropriately
 *  LOG:
 *  LOG: Revision 2.6.6.1  2007/03/13 05:12:29  hbhatnagar
 *  LOG: Allow multiple registration from same client
 *  LOG:
 *  LOG: Revision 2.6  2006/12/12 14:14:45  kamakshilk
 *  LOG: To sent peer based messages to all clients
 *  LOG:
 *  LOG: Revision 2.5  2006/11/29 04:17:07  kamakshilk
 *  LOG: Routing to Backup clients
 *  LOG:
 *  LOG: Revision 2.4  2006/11/14 07:22:34  kamakshilk
 *  LOG: FindBestMatch overloaded for round robin routing
 *  LOG:
 *  LOG: Revision 2.3  2006/11/08 06:12:41  kamakshilk
 *  LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 *  LOG:
 *  LOG: Revision 2.2  2006/10/29 05:25:05  kamakshilk
 *  LOG: Added RemoveAllEntries() method
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 *  LOG: First cut
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ids_routedb.cpp,v 3.9 2010/10/19 12:33:10 vkumara Exp $"

#include <iostream>
#include <engine++.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include <dia_trace.h>

#include <ids_common.h>
#include <ids_routedb.h>

static void
CleanupGuaList(ClientRoutingInfo *clientInfo)
{
    if(!clientInfo || !clientInfo->guaEntryCount)
    {
        return;
    }
    for(int i=0; i<IDS_GUA_LIST_SIZE; i++)
    {
        if(clientInfo->guaList[i] != NULL)
        {
            IDS_GUA_ENTRY *ent = clientInfo->guaList[i];
            clientInfo->guaList[i] = NULL;
            free(ent);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
RouteTable::~RouteTable()
{   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
RouteTable::Lock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Acquire();
    
    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
RouteTable::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
RouteTable::InsertEntry(ClientRoutingInfo* entryParam)
{
    Lock();

    DIA_TRACE_DEBUG(("RouteTable::InsertEntry"));

    routInfo_.push_back(entryParam);

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Insert a Route Entry
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
 *      This should be called after acquiring mutex
 *  See Also:
 ****************************************************************************/
void
RouteTable::InsertRoutingEntry(ClientRoutingInfo* entryParam)
{
    DIA_TRACE_DEBUG(("RouteTable::InsertRoutingEntry"));

    routInfo_.push_back(entryParam);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *      Not thread safe. To be used in conjunction with Lock() and Unlock().
 *
 *  See Also:
 ****************************************************************************/
ClientRoutingInfo*
RouteTable::RetrieveEntry(const ITS_UINT entryKey)
{
    ITS_BOOLEAN found = ITS_FALSE;

    DIA_TRACE_DEBUG(("RouteTable: RetrieveEntry"));

    Lock();

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();

    while (biter != eiter)
    {
        if ((*biter)->clientID == entryKey)
        {
            DIA_TRACE_DEBUG(("RetrieveEntry: list key <%d>", entryKey));
            found = ITS_TRUE;

            break;
        }

        biter++;
    }

    if (found)
    {
        Unlock();

        return ((*biter));
    }

    Unlock();

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      One client can register with multiple AppIds. This method Retrieves
 *      the entry for Client registered with a particular AppId.
 *
 *  Input Parameters:
 *      entryKey - clientId.
 *      appId - application Id with which the client has registered.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ClientRoutingInfo* - client info or NULL
 *
 *  Notes:
 *      Not thread safe. To be used in conjunction with Lock() and Unlock().
 *
 *  See Also:
 ****************************************************************************/
ClientRoutingInfo*
RouteTable::RetrieveWithAppId(const ITS_UINT entryKey, ITS_UINT appId)
{
    ITS_BOOLEAN found = ITS_FALSE;

    DIA_TRACE_DEBUG(("RouteTable: RetrieveWithAppId"));

    Lock();

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();

    while (biter != eiter)
    {
        if (((*biter)->clientID == entryKey) && 
              ((*biter)->regInfo.appIdentifier == appId))
        {
            DIA_TRACE_DEBUG(("RetrieveEntry: list key <%d>", entryKey));
            found = ITS_TRUE;

            break;
        }

        biter++;
    }

    if (found)
    {
        Unlock();

        return ((*biter));
    }

    Unlock();

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Remove the client entry. If client has registered for multiple appIds
 *      this removes all the entries for the client.
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
 *  
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    14-11-06    Enhancement   increment iter to loop thorugh list.
 *   Kamakshi    12-03-07    Enhancement   Loop continued to remove multiple
 *                                         Apps registered by same client.
 *   Kamakshi    15-03-07    Enhancement   Get next iter.
 *
 ****************************************************************************/

void
RouteTable::RemoveEntry(const ITS_UINT entryKey)
{
    Lock();

    DIA_TRACE_DEBUG(("RouteTable::RemoveEntry"));

    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eIter = routInfo_.end();
    while(bIter != eIter)
    {
        if ((*bIter)->clientID == entryKey)
        {
            DIA_TRACE_DEBUG(("RemoveEntry: list key <%d>", entryKey));
            CleanupGuaList((ClientRoutingInfo*)(*bIter));
            free((*bIter));
            bIter = routInfo_.erase(bIter);

            /* Loop through, to check if there are multiple applications
               registered by the same client */
        }
        else
            bIter++;
    }

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Removes the client registered with a particular appId
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
 *      This function is not mutex protected. Mutex should be 
 *      acquire before calling this function.
 *
 *  See Also:
 *
 *  Revision History:
 *
 ****************************************************************************/
void
RouteTable::RemoveEntryWithAppId(const ITS_UINT entryKey, ITS_UINT appId)
{
    //Lock();

    DIA_TRACE_DEBUG(("RouteTable::RemoveEntryWithAppId"));

    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eIter = routInfo_.end();

    while(bIter != eIter)
    {
        if (((*bIter)->clientID == entryKey) &&
              ((*bIter)->regInfo.appIdentifier == appId))
        {
            DIA_TRACE_DEBUG(("RemoveEntryWithAppId: list key <%d>", entryKey));
            CleanupGuaList((ClientRoutingInfo*)(*bIter));

            free((*bIter));
            bIter = routInfo_.erase(bIter);

            //Unlock();
            return;
        }
        bIter++;
    }

    //Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Removes all the existing entries from the list
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
 *  Return Value: None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
RouteTable::RemoveAllEntries()
{
    Lock();

    DIA_TRACE_DEBUG(("RouteTable::RemoveAllEntries"));

    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator nIter;

    while(bIter != routInfo_.end())
    {
        if (*bIter )
        {
            DIA_TRACE_DEBUG(("RemoveAllEntries: Removing entry <%u>",
                              (*bIter)->clientID));

            CleanupGuaList((ClientRoutingInfo*)(*bIter));
            free((*bIter));
            routInfo_.erase(bIter);
        
            bIter = routInfo_.begin();        
        }
    }

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Return all the client ID in the route table
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      Count(number of client Ids).
 *
 *  Output Parameters:
 *      Array of client Ids.
 *
 *  Return Value: None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT*
RouteTable::GetAllEntries(ITS_UINT &count)
{
    ITS_UINT* clist = NULL;
    ITS_UINT index = 0;

    Lock();

    DIA_TRACE_DEBUG(("RouteTable::GetAllEntries"));

    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator nIter;

    count = routInfo_.size();

    if (count)
    {
        clist = (ITS_UINT*)calloc(count, sizeof(ITS_UINT));
        if (clist == NULL)
        {
            //throw exception();
            throw "Error: memory allocation failed";
        } 

        while(bIter != routInfo_.end())
        {
            if (*bIter)
            {
                clist[index++] = ((*bIter)->clientID);
            }
            bIter++;
        }
    }

    Unlock();

    return clist;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Return all the client ID in the route table with matching AppId
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      Count(number of client Ids).
 *
 *  Output Parameters:
 *      Array of client Ids.
 *
 *  Return Value: None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT*
RouteTable::GetAllEntries(ITS_UINT appId, ITS_UINT &count)
{
    ITS_UINT* clist = NULL;
    ITS_UINT index = 0;
    ITS_UINT entryCount = 0;

    Lock();

    DIA_TRACE_DEBUG(("RouteTable::GetAllEntries"));

    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator nIter;

    count = routInfo_.size();

    if (count)
    {
        clist = (ITS_UINT*)calloc(count, sizeof(ITS_UINT));
        if (clist == NULL)
        {
            //throw exception();
            throw "Error: memory allocation failed";
        }

        while(bIter != routInfo_.end())
        {
            if ((*bIter) && ((*bIter)->regInfo.appIdentifier == appId))
            {
                clist[index++] = ((*bIter)->clientID);
                entryCount++;
            }
            bIter++;
        }
    }
    count = entryCount;

    Unlock();

    return clist;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
RouteTable::Print(std::ostream& os) const
{
    DIA_TRACE_DEBUG(("RouteTable::Print"));

    Lock();

    os << "-----------------------------------------------------------" << endl;
    os << "-- IDS Route Table Begin --" << endl;
    os << "-----------------------------------------------------------" << endl;
    os << endl;
    os << "Size: <" << routInfo_.size() << ">" << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;

    std::list<ClientRoutingInfo*>::const_iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::const_iterator eiter = routInfo_.end();

    bool hasEntry = false;

    while(biter != eiter)
    {
        hasEntry = true;

        os << "<" << ((*biter)->clientID) << "> <" << 
            ((*biter)->regInfo.appIdentifier) << "> <" << 
            ((*biter)->regInfo.routing_criteria) << "> <" << 
            ((*biter)->regInfo.connectionType) << ">" << endl ;

        if((*biter)->guaEntryCount)
        {
           int guaEntryCount = (*biter)->guaEntryCount;
           os << "Global Unique Addr :"<<endl;

           for(int i=0; i<IDS_GUA_LIST_SIZE; i++)
           {
               if((*biter)->guaList[i] != NULL)
               {
                   IDS_GUA_ENTRY *ent = (*biter)->guaList[i];
                   os << "---------------"<<endl;
                   os << "GUA List index :"<<i<<endl;
                   os << "startIp :0x" <<hex<<ent->startIp<< endl;
                   os << "endIp   :0x" <<hex<<(ent->endIp) - 1<< endl;
                   os << "---------------"<<endl;
               }
           }
           os << "Global Unique Addr :"<<dec<<guaEntryCount<<endl;
        }

        os << "--------------------------------------------------" << endl;

        biter++;
    }

    if (!hasEntry)
    {
        os << "--------------------------------------------------" << endl;
    }

    os << "-----------------------------------------------------------" << endl;
    os << "-- IDS Route Table End --" << endl;
    os << "-----------------------------------------------------------" << endl;

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
ostream&
operator<< (ostream& os, const RouteTable& table)
{
    table.Print(os);
    return os;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    28-11-06    Enhancement    Routing to Backup Client.
 *
 ****************************************************************************/
ITS_UINT
RouteTable::FindBestMatch(ITS_UINT appId, ITS_UINT* clientID)
{
    ITS_INT index = 0;
    ITS_INT bkupIndex = 0;
    ITS_UINT bkupClientID[50];
    ITS_BOOLEAN actvFound = ITS_FALSE;
    int idx = 0;

    Lock();

    DIA_TRACE_DEBUG(("RouteTable::FindBestMatch"));

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator tmpIter = routInfo_.end();

    while (biter != eiter)
    {
        switch((*biter)->regInfo.routing_criteria)
        {
            case IDS_APP_IDENTIFIER:
                if ((appId == (*biter)->regInfo.appIdentifier)
                   && ((*biter)->regInfo.connectionType
                                            == IDS_PRIMARY_CONNECTION))
                {
                    actvFound = ITS_TRUE;
                    bkupIndex = 0;
                    DIA_TRACE_DEBUG(("FindBestMatch: clientID <%d> appId <%d>", 
                                        (*biter)->clientID, appId));
                    clientID[index++] = (*biter)->clientID;
                }
                else if (!actvFound &&
                            (appId == (*biter)->regInfo.appIdentifier) &&
                            ((*biter)->regInfo.connectionType
                               == IDS_BACKUP_CONNECTION))
                {
                    DIA_TRACE_DEBUG(("FindBestMatch: bkclntID <%d> appId <%d>", 
                                        (*biter)->clientID, appId));
                    bkupClientID[bkupIndex++] = (*biter)->clientID;
                }
                
            break;
        }

        biter++;
    }

    Unlock();

    if (bkupIndex)
    {
        for (idx =0; idx < bkupIndex ; idx++)
        {
            clientID[index++] = bkupClientID[idx];
        }
    }

    return (index);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Does a Round Robin search and finds the first best client.
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
 *  
 *  Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    28-11-06    Enhancement    Routing to Backup Client.
 *
 ****************************************************************************/
ITS_UINT
RouteTable::FindBestMatch(ITS_UINT appId)
{
    ITS_UINT bestClient = 0;
    ITS_UINT bkupClient = 0;
    ITS_BOOLEAN bkupFound = ITS_FALSE;

    Lock();

    DIA_TRACE_DEBUG(("RouteTable::FindBestMatch"));

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator bkupiter = biter; 

    while (biter != eiter)
    {
        switch((*biter)->regInfo.routing_criteria)
        {
            case IDS_APP_IDENTIFIER:
                if ((appId == (*biter)->regInfo.appIdentifier)
                   && ((*biter)->regInfo.connectionType
                                            == IDS_PRIMARY_CONNECTION))
                {
                    DIA_TRACE_DEBUG(("FindBestMatch: clientID <%d> appId <%u>", 
                                       (*biter)->clientID, appId));

                    bestClient = (*biter)->clientID;
                    /* Release lock after complete operation */
                    //Unlock();

                    /* The client already selected is removed from the list
                       and reinserted at the back of the list to allow,
                       round robin scheduling  */
                    if (routInfo_.size() > 1)
                    {
                        ClientRoutingInfo* newEntry = 
                            (ClientRoutingInfo*) calloc(1, 
                                sizeof(ClientRoutingInfo));
                        if (newEntry == NULL)
                        {
                            //throw exception();
                            throw "Error: memory allocation failed";
                        }
                        newEntry->clientID = (*biter)->clientID;
                        newEntry->regInfo = (*biter)->regInfo;
                        newEntry->guaEntryCount = (*biter)->guaEntryCount;
                        memcpy(newEntry->guaList, (*biter)->guaList,
                               sizeof(IDS_GUA_ENTRY*)*IDS_GUA_LIST_SIZE);

                        RemoveEntryWithAppId((*biter)->clientID, appId);
                        InsertRoutingEntry(newEntry);
                    }
                    /* release lock before return */
                    Unlock();
                    return bestClient;
                }
                /* Find the client registered as backup for the same appId */
                else if (!bkupFound && 
                            (appId == (*biter)->regInfo.appIdentifier) &&
                            ((*biter)->regInfo.connectionType
                                 == IDS_BACKUP_CONNECTION))
                {
                    DIA_TRACE_DEBUG(("FindBestMatch: No Active Clients"));
                    bkupFound = ITS_TRUE;
                    DIA_TRACE_DEBUG(("FindBestMatch: Backup ClientID <%d>", 
                                       (*biter)->clientID));
                    bkupClient = (*biter)->clientID;
                    bkupiter = biter;
                }
            break;
        }

        biter++;
    }

    //Unlock();

    /* If no active clients found and a backup client found,
      then return the backup client ID */
    if (bkupClient)
    {
        if (routInfo_.size() > 1)
        {
            ClientRoutingInfo* newEntry = 
                (ClientRoutingInfo*) calloc(1, 
                    sizeof(ClientRoutingInfo));

            if (newEntry == NULL)
            {
                throw "Error: memory allocation failed";
            }

            newEntry->clientID = bkupClient;
            newEntry->regInfo = (*bkupiter)->regInfo;
            newEntry->guaEntryCount = (*biter)->guaEntryCount;
            memcpy(newEntry->guaList, (*biter)->guaList,
                               sizeof(IDS_GUA_ENTRY*)*IDS_GUA_LIST_SIZE);

            RemoveEntryWithAppId((*bkupiter)->clientID, appId);
            InsertRoutingEntry(newEntry);
        }
        /* release lock before return */
        Unlock();
        return bkupClient;
    }
    /* release lock before return */
    Unlock();
    return bestClient;
}

ITS_UINT
RouteTable::FindBestMatch(unsigned char *guIpAddr, ITS_UINT appId)
{
    ITS_UINT bestClient = 0;
    ITS_UINT bkupClient = 0;
    ITS_BOOLEAN bkupFound = ITS_FALSE;
    ClientRoutingInfo* clientInfo = NULL;

    DIA_TRACE_DEBUG(("RouteTable::FindBestMatch for GlobalUniqIp=%s",guIpAddr));

    Lock();

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator bkupiter = biter; 

    while (biter != eiter)
    {
        clientInfo = (*biter);
        if ((appId == (*biter)->regInfo.appIdentifier)
           && ((*biter)->regInfo.connectionType == IDS_PRIMARY_CONNECTION))
        {
            ITS_INT binIpAdrr =  htonl(inet_addr((const char*)guIpAddr)); 
            for(int i=0; i<IDS_GUA_LIST_SIZE && (*biter)->guaEntryCount; i++)
            {
                IDS_GUA_ENTRY *ent = clientInfo->guaList[i];

                if (ent && (binIpAdrr >= ent->startIp) && (binIpAdrr < ent->endIp))
                {
                    DIA_TRACE_DEBUG(("FindBestMatch: clientID <%d> appId <%u>", 
                                       (*biter)->clientID, appId));
                    bestClient = (*biter)->clientID;
                    /* release lock before return */
                    Unlock();
                    return bestClient;
                }
            }
        }
        /* Find the client registered as backup for the same appId */
        else if (!bkupFound && (appId == (*biter)->regInfo.appIdentifier) &&
                 ((*biter)->regInfo.connectionType == IDS_BACKUP_CONNECTION))
        {
            ITS_INT binIpAdrr =  htonl(inet_addr((const char*)guIpAddr)); 

            for(int i=0; i<IDS_GUA_LIST_SIZE && (*biter)->guaEntryCount; i++)
            {
                IDS_GUA_ENTRY *ent = clientInfo->guaList[i];

                if (ent && (binIpAdrr >= ent->startIp) && (binIpAdrr < ent->endIp))
                {
                    DIA_TRACE_DEBUG(("FindBestMatch: BkpclientID<%d>appId<%u>", 
                                       (*biter)->clientID, appId));
                    bkupClient = (*biter)->clientID;
                    bkupFound = ITS_TRUE;
                }
            }
        }
        biter++;
    }
    if (bkupFound)
    {
        DIA_TRACE_DEBUG(("backup Client matches Client Id = %d", bkupClient));
        bestClient = bkupClient;
    }

    /* release lock before return */
    Unlock();
    return bestClient;
}
