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
 *  ID: $Id: dia_realm_table.cpp,v 3.15.12.1.22.1 2017/12/21 04:37:21 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_realm_table.cpp,v $
 *  LOG: Revision 3.15.12.1.22.1  2017/12/21 04:37:21  jkchaitanya
 *  LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 *  LOG:
 *  LOG: Revision 3.15.12.1  2013/01/03 07:47:40  rgovardhan
 *  LOG: Fix for bugs 797 and 815
 *  LOG:
 *  LOG: Revision 3.15  2009/08/26 11:57:16  rajeshak
 *  LOG: Fix for Issue:2328(IDS dumps core when trying to remove peer which
 *  LOG: is only destination in Realm)
 *  LOG: Fixed issue in RemoveAllDestination function.
 *  LOG:
 *  LOG: Revision 3.14  2009/08/24 04:37:41  rajeshak
 *  LOG: Fix for Issue 2320 (IDS allowing multiple destination in with
 *  LOG: same Peer name, realm Name, applicationId and vendorId in Realm)
 *  LOG: Added a check before inserting new destination.
 *  LOG:
 *  LOG: Revision 3.13  2009/08/13 11:43:59  rajeshak
 *  LOG: Inserting peers into realmEntry destination list based on priority
 *  LOG:
 *  LOG: Revision 3.12  2009/07/24 09:30:28  rajeshak
 *  LOG: Changes done for
 *  LOG:  1. new MML Command to print and remove default route
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 3.11  2009/07/15 10:09:20  sureshj
 *  LOG: print realmName also with Peer MML command printRealmtable.
 *  LOG: Issue ID:2189
 *  LOG:
 *  LOG: Revision 3.10  2009/04/13 13:36:57  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.9  2009/03/24 12:11:06  rajeshak
 *  LOG: Issue Id : 1786
 *  LOG: Description:(MML command: IDS dumps core after removing the realm entry).
 *  LOG: Removed Remove PeerEntry call in Realm FreeEntry.
 *  LOG:
 *  LOG: Revision 3.8  2009/02/11 11:04:35  chandrashekharbs
 *  LOG: Fix for issue #1480
 *  LOG:
 *  LOG: Revision 3.7  2009/02/03 10:21:11  ssaxena
 *  LOG: Modifications done for Redirect Agent functionality.
 *  LOG:
 *  LOG: Revision 3.6  2009/01/28 06:51:57  chandrashekharbs
 *  LOG: Added definition for FindFirstEntry API used for xml persistency
 *  LOG:
 *  LOG: Revision 3.5  2008/10/31 05:54:44  nvijikumar
 *  LOG: IssueID:none
 *  LOG: FeatureID:none
 *  LOG: Description:Code cleanup
 *  LOG:
 *  LOG: Revision 3.4  2008/10/28 12:06:28  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Porting Performance changes from 3.0 branch
 *  LOG:
 *  LOG: Revision 3.3  2008/04/24 13:58:39  nanaparthi
 *  LOG: Fix for Issue #885
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:36:24  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.7  2007/01/23 15:42:16  nanaparthi
 *  LOG: Fix for Bug id 5203
 *  LOG:
 *  LOG: Revision 2.6  2007/01/08 13:51:27  nanaparthi
 *  LOG: Some updates to RemoveEntry function.
 *  LOG:
 *  LOG: Revision 2.5  2006/12/17 03:34:44  tpanda
 *  LOG: Fix for bug# 5067 and default route handling
 *  LOG:
 *  LOG: Revision 2.4  2006/10/24 14:13:11  yranade
 *  LOG: Some updates to print function.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/09 11:29:57  yranade
 *  LOG: Add API to get default entry per realm.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/09 06:29:33  yranade
 *  LOG: Missing break. Updated print.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_realm_table.cpp,v 3.15.12.1.22.1 2017/12/21 04:37:21 jkchaitanya Exp $"

#include <iomanip>

#include <stdlib.h>
#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>

#include <dia_realm_table.h>
#include <dia_timer_handler.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

ITS_Mutex RealmTable::guard(0);
ITS_Mutex RealmTable::lock(0);

static RealmTable *rTable = NULL;

static void FreeEntry(REALM_ENTRY *entryParam);

static
unsigned int HashMakeKey(char* ph)
{
   unsigned int h = 0;
   unsigned int g;

   for(; *ph ; ph++)
   {
      h = (h << 4) + *ph;
      if( (g = h & 0xF0000000) != 0)
         h = (h ^ (g >> 24)) & ~0xF0000000;
   }

   return (h % 19997);
}


RealmTable*
RealmTable::GetRealmTable()
{

    if (rTable == NULL)
    {
        /* Moved inside if Due to Performance issue */
        ITS_ASSERT(RealmTable::guard.Acquire() == ITS_SUCCESS);

        rTable = new RealmTable;

        RealmTable::guard.Release();
    }


    return rTable;
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
 * Revision History:
 * ---------------------------------------------------------------------------
 *  Name          Date        Reference               Description
 * ---------------------------------------------------------------------------
 *  Naresh        23-04-2008   ST-IDIA-0300-02     Fix for Issue #885
 *                                                Added Priority
 *
 ****************************************************************************/
static void
PrintEntry(std::ostream& os, const REALM_ENTRY* entry)
{
 
    os << "Realm Name             = " << entry->realmName << endl;
    os << "Local Action           = " << entry->localAction << endl;
    os << "Proxy-Info AVP Enabled = " <<
          ((entry->proxyInfoAvpEnabled)? "yes" : "no") << endl;
    os << "Default Peer Status    = " << entry->isDefault << endl;
    for (int i = 0; i < DIA_RE_DEST_CNT(entry); i++)
    {
        if(DIA_RE_DEST_PEER(entry,i) ||
           DIA_RE_REDIRECT_HOST(entry,i))
        {
            if (DIA_RE_L_ACTION(entry) == ITS_DIA_REDIRECT)
            {
                os << " RedirectHost     = " << DIA_RE_REDIRECT_HOST(entry,i) << endl;
                os << "     AppId        = " << DIA_RE_DEST_APP_ID(entry, i).appId << endl;
            }
            else if (DIA_RE_DEST_PEER(entry,i)->hostIdentity)
            {
                os << " Peer         = " << DIA_RE_DEST_PEER(entry,i)->hostIdentity << endl;
                os << " Realm Name   = " << DIA_RE_DEST_PEER(entry,i)->realmName << endl;
                os << "     AppId    = " << DIA_RE_DEST_APP_ID(entry, i).appId << endl;
                os << "     VendorId = " << DIA_RE_DEST_APP_ID(entry, i).vendorId << endl;
                os << "     Priority = " << DIA_RE_DEST_PRIORITY(entry,i) << endl;
            }
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
RealmTable::~RealmTable()
{  
    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
                                       iter != tableRealm.end();
                                       iter++)
    {
        REALM_ENTRY* entry = (*iter).second;

        if (entry != NULL)
        {
            FreeEntry(entry);
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
void
RealmTable::Lock() const
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
RealmTable::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}

/*****************************************************************************
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
bool 
RealmTable::FindDefaultEntry(const char* rName, REALM_ENTRY *& entryParam)
{
    bool found = false;
    entryParam = NULL;
    if (defaultRealmEntry)
    {
       found = true;
       entryParam = defaultRealmEntry;
    }
    return found;
    
}

REALM_ENTRY*
RealmTable::FindDefaultEntry(REALM_ENTRY *& entryParam)
{

    entryParam = NULL;
    if (defaultRealmEntry)
    {
       entryParam = defaultRealmEntry;
    }

    return entryParam;
}

bool
RealmTable::FindEntry(const char *realmName, REALM_ENTRY *& entryParam)
{  
    bool found = false;

    REALM_ENTRY *retEntry = NULL;

    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
         iter != tableRealm.end(); iter++)
    {
        entryParam = (*iter).second;
        if (strcasecmp(realmName, entryParam->realmName) == 0)
        {
            found = true;
            break;
        }
        else
        {
            entryParam = NULL;
            found = false;
        }
    }   

    Unlock();

    return found;
}

REALM_ENTRY*
RealmTable::FindFirstEntry()
{
    REALM_ENTRY* ret = NULL;

    Lock();
    
    TypeTableRealm::iterator iter = tableRealm.begin();

    if (iter != tableRealm.end())
    {
        ret = (*iter).second;
    }

    Unlock();
    return ret;
}

ITS_INT
RealmTable::FindRealmCount()
{
    ITS_INT count = 0;

    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
         iter != tableRealm.end(); iter++)
    {
             count++;
    }

    Unlock();

    return count;

}

REALM_ENTRY*
RealmTable::FindNextEntry(REALM_ENTRY *entryParam)
{
    REALM_ENTRY* ret;

    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
         iter != tableRealm.end(); iter++)
    {
        ret = (*iter).second;

        if (strcasecmp(DIA_RE_NAME(ret), DIA_RE_NAME(entryParam)) == 0)
        {
            iter++;
            if (iter != tableRealm.end())
            {
                Unlock();
                return (*iter).second;
            }
            break;
        }
    }

    Unlock();

    return (NULL);
}


REALM_ENTRY*
RealmTable::FindNextEntry(ITS_INT count)
{
    REALM_ENTRY *retEntry = NULL;
    REALM_ENTRY *entryParam = NULL;
   
    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
         iter != tableRealm.end(); iter++)
    {
       
        if (count == 1)
        {
            entryParam = (*iter).second;
            Unlock();
            return entryParam;
        }
        else 
        {
            while (count > 1)
            {
                iter++;
                count--;
            }
            entryParam = (*iter).second;
            Unlock();
            return entryParam;
        }
        
    }

    Unlock();

    return (NULL);

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
int
RealmTable::InsertEntry(REALM_ENTRY* entryParam)
{
    Lock();

    ITS_REQUIRE(entryParam != NULL);

    if (entryParam->isDefault)
    {
        //add as default route, hence no further search,
        //only one default entry in realm table
        defaultRealmEntry = entryParam; 
        Unlock();
        return (ITS_SUCCESS);
    }

    const char *realmName = entryParam->realmName;

    REALM_ENTRY *entry = NULL;

    if (FindEntry(realmName, entry))
    {
        Unlock();
        return (ITS_EDUPLENTRY);
    }
    pair<TypeTableRealm::iterator, bool> insertRes =
        tableRealm.insert(TypeTableRealm::value_type(realmName,
                                                     entryParam));

    ITS_ENSURE(insertRes.second);

    Unlock();

    return (ITS_SUCCESS);
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
static void
FreeEntry(REALM_ENTRY *entryParam)
{
    if (entryParam->realmName)
    {
        free((void *)entryParam->realmName);
        entryParam->realmName = NULL;
    }

#if 0
    for (int i = 0; i<entryParam->destCnt; i++)
    {
        if (entryParam->destSpecs[i].peer)
        {
            PEER_ENTRY *peer  = entryParam->destSpecs[i].peer;
            PeerTable::GetPeerTable()->RemoveEntry(peer->hostIdentity);
        }
    }
#endif

    free((void *)entryParam);

    entryParam = NULL;
}

int
RealmTable::RemoveEntry(const char *realmName)
{
    int ret = ITS_SUCCESS;
    REALM_ENTRY *entryParam = NULL;

    Lock();

    for (TypeTableRealm::iterator iter = tableRealm.begin();
         iter != tableRealm.end(); iter++)
    {
        if (strcasecmp((*iter).first, realmName) == 0)
        {
            entryParam = (*iter).second;

            if (iter != tableRealm.end())
            {
                FreeEntry(entryParam);
                tableRealm.erase(iter);
                Unlock();
                return ITS_SUCCESS;

            }
            break;
        }
    }
    Unlock();

    return ITS_ENOTFOUND;

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
RealmTable::Print(std::ostream& os) const
{
    Lock();

    os << "------------------------------------------------------------" << endl;
    os << "-- Realm Table Begin --" << endl;
    os << "------------------------------------------------------------" << endl;
    os << endl;
    os << "Size: <" << tableRealm.size() << ">" << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;

    TypeTableRealm::const_iterator iter = tableRealm.begin();

    bool hasEntry = false;

    while(iter != tableRealm.end())
    {
        hasEntry = true;

        ITS_ASSERT((*iter).second != NULL);

        //os << *((*iter).second);
        REALM_ENTRY *entry = (*iter).second;
        PrintEntry(os, entry);

        os << "--------------------------------------------------" << endl;

        iter++;
    }

    if (!hasEntry)
    {
        os << "--------------------------------------------------" << endl;
    }

    os << "------------------------------------------------------------" << endl;
    os << "-- Realm Table End --" << endl;
    os << "------------------------------------------------------------" << endl;

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
int
RealmTable::InsertDestination(REALM_ENTRY *rEntry, PEER_ENTRY *pEntry,
                              int appId, int vendId, int prio)
{
    bool insertFlag = false;

    if ((rEntry == NULL) || (pEntry == NULL))
    {
        return !ITS_SUCCESS;
    }

    int reDstCnt = rEntry->destCnt;

    /*
     * Check if destination Entry already exist of this peer
     * If yes, discard Entry.
     */
	for(int i=0;i<reDstCnt;i++)
    {
        if((rEntry->destSpecs[i].peer == pEntry) &&
           (rEntry->destSpecs[i].appIdentifier.appId == appId) &&
           (rEntry->destSpecs[i].appIdentifier.vendorId == vendId))
        {
            return !ITS_SUCCESS;  
        }
    }
	
    for(int i=0;i<reDstCnt; i++)
    {
        if ((rEntry->destSpecs[i].appIdentifier.appId == appId ) && 
            (rEntry->destSpecs[i].appIdentifier.vendorId == vendId))
        {
            /* sorting by priority */
            int j = i;
            for ( ; j<reDstCnt; j++)
            {
                if (((rEntry->destSpecs[j].appIdentifier.appId != appId ) ||
                     (rEntry->destSpecs[j].appIdentifier.vendorId != vendId)) ||
                     ((rEntry->destSpecs[j].appIdentifier.appId == appId ) &&
                     (rEntry->destSpecs[j].appIdentifier.vendorId == vendId) &&
                     (rEntry->destSpecs[j].priority > prio)))
                {
                    break;
                }
            }

            for (int k=reDstCnt; k>j; k--)
            {
               rEntry->destSpecs[k].appIdentifier.appId =
                                rEntry->destSpecs[k-1].appIdentifier.appId;
               rEntry->destSpecs[k].appIdentifier.vendorId =
                                rEntry->destSpecs[k-1].appIdentifier.vendorId;
               rEntry->destSpecs[k].peer = 
                                rEntry->destSpecs[k-1].peer; 
               rEntry->destSpecs[k].priority = 
                                rEntry->destSpecs[k-1].priority;
            }

            rEntry->destSpecs[j].appIdentifier.appId = appId;
            rEntry->destSpecs[j].appIdentifier.vendorId = vendId;
            rEntry->destSpecs[j].peer = pEntry;
            rEntry->destSpecs[j].priority = prio;
            insertFlag = true;
            break;
        }
    }

    if (!insertFlag)
    {
        rEntry->destSpecs[reDstCnt].appIdentifier.appId = appId; 
        rEntry->destSpecs[reDstCnt].appIdentifier.vendorId = vendId;
        rEntry->destSpecs[reDstCnt].peer = pEntry;
        rEntry->destSpecs[reDstCnt].priority = prio;
    }
    
    rEntry->destCnt++;
    return ITS_SUCCESS;
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
int 
RealmTable::RemoveDestination(REALM_ENTRY *rEntry, PEER_ENTRY *pEntry)
{
    ITS_UINT found = 0;

    if ((rEntry == NULL) || (pEntry == NULL))
    {
        return !ITS_SUCCESS;
    }

    int reDstCnt = rEntry->destCnt;
    if (reDstCnt == 0)
    {
        return !ITS_SUCCESS;
    }

    for(int i=0;i< rEntry->destCnt; i++)
    {
        if (rEntry->destSpecs[i].peer == pEntry) 
        {
            found = 1;
            rEntry->destSpecs[i].peer = NULL;
        }

        if(found == 1 )
        {
            for (int j=i; j<rEntry->destCnt; j++)
            {
                if (j < (rEntry->destCnt-1))
                {
                    rEntry->destSpecs[j].peer = rEntry->destSpecs[j+1].peer;

                    rEntry->destSpecs[j].appIdentifier.appId =
                           rEntry->destSpecs[j+1].appIdentifier.appId;

                    rEntry->destSpecs[j].appIdentifier.vendorId =
                        rEntry->destSpecs[j+1].appIdentifier.vendorId;

                    rEntry->destSpecs[j].priority = rEntry->destSpecs[j+1].priority;
                }
            }

            if (reDstCnt > 0)
            {
                reDstCnt--; 
            }

            found = 0;
        }
    }
    rEntry->destCnt = reDstCnt;

    return ITS_SUCCESS;
}
/*.implementation:
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
int
RealmTable::RemoveAllDestination(PEER_ENTRY *pEntry)
{
    if (pEntry == NULL)
    {
        return !ITS_SUCCESS;
    }

    Lock();

    TypeTableRealm::const_iterator iter = tableRealm.begin();

    while(iter != tableRealm.end())
    {
        ITS_ASSERT((*iter).second != NULL);

        REALM_ENTRY *rEntry = (*iter).second;

        if (rEntry->destCnt == 0)
        {
            iter++;
            continue;
        }
     
        RealmTable::RemoveDestination(rEntry, pEntry);
  
        iter++;

        if (DIA_PE_IS_DISCOVERED(pEntry) && (rEntry->destCnt == 0))
        {
            /* No Destination. Remove realmEntry */
            tableRealm.erase(rEntry->realmName);
            FreeEntry(rEntry);
        }
    }

    Unlock();

    return ITS_SUCCESS;
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
int
RealmTable::RemoveDefaultEntry()
{
    Lock();

    defaultRealmEntry = NULL; 

    Unlock();

    return ITS_SUCCESS;
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
operator<< (ostream& os, const REALM_ENTRY& entry)
{
    PrintEntry(os, &entry); 
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
 ****************************************************************************/
ostream&
operator<< (ostream& os, const RealmTable& table)
{
    table.Print(os);
    return os;
}


