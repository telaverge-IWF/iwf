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
 *  ID: $Id: dia_peer_table.cpp,v 3.18.2.1.2.2.26.4.4.2.12.1.2.3 2020/02/14 11:36:11 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_peer_table.cpp,v $
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.2.12.1.2.3  2020/02/14 11:36:11  jkchaitanya
 *  LOG: TCP Timeout fix ported from DRE
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.2.12.1.2.2  2017/12/21 04:37:21  jkchaitanya
 *  LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.2.12.1.2.1  2015/02/17 06:22:44  jkchaitanya
 *  LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.2.12.1  2014/09/16 09:52:26  jsarvesh
 *  LOG: Chnages done for Peer wise Statistics enhancement
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.2  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4.4.1  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.4  2013/03/06 08:31:00  jvikram
 *  LOG: BUGID=1016, 1027, 803. Fixed the specified bugs.
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.3  2013/02/25 13:16:09  mallikarjun
 *  LOG: Bug 623 changes
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.2  2013/02/21 10:20:45  jkchaitanya
 *  LOG: Mar31 CMAPI Features
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2.26.1  2013/02/01 11:34:16  pramana
 *  LOG: Merged from branch 0212 to 0300.
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.3  2013/01/18 04:48:00  jsarvesh
 *  LOG: cppcheck changes
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.2  2012/10/03 15:08:43  cprem
 *  LOG: Merged from ERLBF branch B-DRE-0212-02
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.1.2.1  2012/09/20 07:54:03  cprem
 *  LOG: Support for multiple dictionary id configuration per peer.
 *  LOG:
 *  LOG: Revision 3.18.2.1.2.1  2012/09/06 11:30:46  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.18.2.1.4.1  2012/08/22 13:29:08  cashok
 *  LOG: Added Dictionary Id to xml configuration
 *  LOG:
 *  LOG: Revision 3.18.2.1  2012/07/10 08:34:11  ncshivakumar
 *  LOG: Updated code to send error code 3003 and 3010 in case of unknown realm and unknown peer respectively
 *  LOG:
 *  LOG: Revision 3.18  2011/07/14 14:04:51  vkumara
 *  LOG: ForceDisconnect Requirement - Not to initiate connection.
 *  LOG:
 *  LOG: Revision 3.17  2010/08/27 12:28:12  nvijikumar
 *  LOG: DSCP value support (IP header) - Vasanth
 *  LOG:
 *  LOG: Revision 3.16  2010/08/19 11:21:27  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.15  2009/10/14 10:40:20  sureshj
 *  LOG: ForceDisconectPeer new expiry timer support in msecs.
 *  LOG: Motorola heldesk ticket 2219.
 *  LOG:
 *  LOG: Revision 3.14  2009/04/13 13:37:57  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.13  2009/03/26 09:35:29  rajeshak
 *  LOG: GetPeerStatus MML API Support
 *  LOG:
 *  LOG: Revision 3.12  2009/03/19 12:38:15  nvijikumar
 *  LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 *  LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 *  LOG:
 *  LOG: Revision 3.11  2009/02/04 05:59:35  nvijikumar
 *  LOG: DiaSocketTransportContainer::slotsList maintains list PEER_ENTRY ptrs
 *  LOG:
 *  LOG: Revision 3.10  2009/01/06 14:00:03  nvijikumar
 *  LOG: Updates for FreeEntry API
 *  LOG:
 *  LOG: Revision 3.9  2009/01/03 06:57:48  nvijikumar
 *  LOG: Proper usage of Peer's trIndex
 *  LOG:
 *  LOG: Revision 3.8  2008/11/19 10:58:18  sureshj
 *  LOG: TLSEnabled prints Yes/No. Fix for whizible bug id 1282.
 *  LOG:
 *  LOG: Revision 3.7  2008/11/12 12:19:04  sureshj
 *  LOG: conn est time added when peer in R-OPEN state. Fix for the issue id 1230.
 *  LOG:
 *  LOG: Revision 3.6  2008/11/05 14:00:40  sureshj
 *  LOG: Release 3.1.1 feature
 *  LOG: Peer Connection Status Information
 *  LOG:
 *  LOG: Revision 3.5  2008/10/31 05:53:56  nvijikumar
 *  LOG: IssueID:none
 *  LOG: FeatureID:none
 *  LOG: Description:Code cleanup
 *  LOG:
 *  LOG: Revision 3.4  2008/10/28 12:06:28  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Porting Performance changes from 3.0 branch
 *  LOG:
 *  LOG: Revision 3.3  2008/08/25 05:49:39  ssaxena
 *  LOG: Updates to PeerTable print function
 *  LOG:
 *  LOG: Revision 3.2  2008/04/21 12:09:11  nanaparthi
 *  LOG:  Fix for Issue #854 , Added isFailoverEnabled & ifRedundantMate
 *  LOG:  to PrintEntry() API
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.13  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.12.2.2  2007/11/14 17:23:19  hbhatnagar
 *  LOG: Made changes in StartTimer() to print traces properly.
 *  LOG:
 *  LOG: Revision 2.12.2.1  2007/09/25 09:54:34  hbhatnagar
 *  LOG: Added StopTimer for DeviceWatchdog timer before starting.( DWTimeout issue)
 *  LOG:
 *  LOG: Revision 2.12  2007/02/19 15:07:32  nvijikumar
 *  LOG: Insert unique entry w.r.t hostname and realmname.
 *  LOG:
 *  LOG: Revision 2.11  2007/01/29 14:10:00  nanaparthi
 *  LOG: Enhancements made for PrintEntry() function to print
 *  LOG: IP address, Port, Transport type .
 *  LOG:
 *  LOG: Revision 2.10  2007/01/23 15:41:44  nanaparthi
 *  LOG: Fix for Bug id 5203
 *  LOG:
 *  LOG: Revision 2.9  2007/01/09 10:30:32  nvijikumar
 *  LOG: Fix Peer Removal issue.
 *  LOG:
 *  LOG: Revision 2.8  2006/12/20 14:57:42  tpanda
 *  LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 *  LOG:
 *  LOG: Revision 2.7  2006/12/11 13:51:25  tpanda
 *  LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 *  LOG:
 *  LOG: Revision 2.6  2006/12/10 13:42:42  tpanda
 *  LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 *  LOG:
 *  LOG: Revision 2.5  2006/11/28 13:29:33  nvijikumar
 *  LOG: Failover and Multicasting clientId changes ( viji and kamakshi).
 *  LOG:
 *  LOG: Revision 2.4  2006/10/12 14:13:41  yranade
 *  LOG: Finish up Device Watchdog handling. Bug Fix: 4464
 *  LOG:
 *  LOG: Revision 2.3  2006/10/11 15:00:01  yranade
 *  LOG: CERCache change to CECache.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/05 13:21:54  yranade
 *  LOG: Getting there.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_peer_table.cpp,v 3.18.2.1.2.2.26.4.4.2.12.1.2.3 2020/02/14 11:36:11 jkchaitanya Exp $"

#include <iomanip>

#include <stdlib.h>
#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>

#include <dia_timer_handler.h>
#include <dia_ip_trans.h>
#include <dia_peer_table.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif


ITS_Mutex PeerTable::guard(0);
ITS_Mutex PeerTable::lock(0);

static PeerTable *pTable = NULL;

void FreeEntry(PEER_ENTRY *entryParam);

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


PeerTable*
PeerTable::GetPeerTable()
{

    if (pTable == NULL)
    {
        /* Moved inside if Due to Performance issue */
        ITS_ASSERT(PeerTable::guard.Acquire() == ITS_SUCCESS);

        pTable = new PeerTable;

        PeerTable::guard.Release();
    }


    return pTable;
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
PrintEntry(std::ostream& os, const PEER_ENTRY* entry)
{
    char tempBuf[MAXSIZE];
    struct tm tbuf;
    localtime_r(&(DIA_PE_CONEST_TIME(entry)), &tbuf);
    strftime(tempBuf,MAXSIZE, "[ %b %d %Y %H:%M:%S ]" ,&tbuf);
  
    os << "HostIdentity          = " << entry->hostIdentity << endl;
    os << "RealmName             = " << entry->realmName << endl;
    os << "isStatic              = " << ((entry->isStatic == 0)?"No":"Yes") << endl;
    os << "TLS Enabled           = " << ((entry->tlsEnabled == 0)?"No":"Yes") << endl;
    //When DTLS is supported then need to change the condition i.e == MAX_TRANS_PER_LIST
    if(DIA_PE_CONN_TRANS_COUNT(entry) == (MAX_TRANS_PER_LIST-1))
    {
        os << "Transport Type        = " "ITS_DIA_T_TCP,ITS_DIA_T_SCTP"<<endl;
    }
    else
    {
    os << "Transport Type        = " << DIA_TRANS_TYPE_TO_TEXT
                                         (DIA_PE_CONN_TINFO(entry).type) << endl;
    }
    os << "Peer conn instance    = " << entry->trInst <<endl;
    os << "Peer TrIndex          = " << DIA_PE_INDEX(entry) <<endl;
    os << "Status                = " << PEER_STATE_TO_TEXT(entry->statusT) <<endl;
    os << "Dscp Enabled          = " << ((entry->dscpEnabled == 0)?"No":"Yes") << endl;
    os << "Dscp Value            = " << entry->dscpVal <<endl;

    for(int i=0; i < MAX_DICT_IDS_PER_PEER; i++)
        os << "Dictionary Id__"   << i << "      = " << entry->dictId[i]<<endl; 
    if( entry->statusT == PEER_ST_R_OPEN || entry->statusT == PEER_ST_I_OPEN)
    os << "Connection Est Time   = " << tempBuf <<endl;
    
    if (DIA_PE_CONN_TINFO(entry).type == ITS_DIA_T_TCP)
    {
        os << "Ip address            = " << DIA_PE_CONN_TINFO(entry).
                                            serverIpAddr << endl;
    }
    else if (DIA_PE_CONN_TINFO(entry).type == ITS_DIA_T_SCTP)
    {
        os << "List of IPs           : " << endl;
        for(int i=0; i < DIA_PE_CONN_TINFO(entry).noIPs; i++)
        {
            os << "                        " << DIA_PE_CONN_TINFO(entry).
                 multiHomeipaddrs[i]<< endl; 
        }
    }
    for(int i = 0;i < DIA_PE_CONN_TRANS_COUNT(entry);i++)
    {
        if(i == 2)
        break;//Since only 2 ports can be configured 

        if(DIA_PE_CONN_TINFO_INDEX(entry,i).portNo != 0)
        {
            os << "Port No               = " << DIA_PE_CONN_TINFO_INDEX(entry,i).portNo << endl;
        }
        else
        {
            os << "Secure Port No        = " << DIA_PE_CONN_TINFO_INDEX(entry,i).securePort << endl;
        }
    }
    os << "IsFailover Enabled    = " <<((entry->isFailoverEnabled == 0)?"No":"Yes")<<endl; 
    os << "IsFailback Enabled    = " <<((entry->isFailbackEnabled == 0)?"No":"Yes")<<endl;
    os << "IsRedundantMate       = " <<((entry->ifRedundantMate == 0)?"No":"Yes")<< endl;
    if (entry->altHost) 
    {
        os << "Alternate Peer        = " << entry->altHost << endl;
        os << "Alternate Realm       = " << entry->altRealmName << endl;
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
PeerTable::~PeerTable()
{  
    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
                                       iter != peerList.end();
                                       iter++)
    {
        PEER_ENTRY* entry = (*iter);

        if (entry != NULL)
        {
            FreeEntry(entry);
        }
    }

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
void
PeerTable::Lock() const
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
PeerTable::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {   
        ITS_THROW_ERROR(res);
    }
}


PEER_ENTRY*
PeerTable::FindFirstEntry()
{
    PEER_ENTRY* ret;

    Lock();

    if (peerList.empty())
    {
        ret = NULL;
    }
    else
    {
        ret = peerList.front();
    }
    Unlock();

    return ret;
}


PEER_ENTRY*
PeerTable::FindNextEntry(PEER_ENTRY* entryParam)
{
    PEER_ENTRY* ret;

    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {
        ret = (*iter);

        if ((strcasecmp(ret->hostIdentity, entryParam->hostIdentity) == 0) &&
            (strcasecmp(ret->realmName, entryParam->realmName) == 0))
        {
            iter++;
            if (iter != peerList.end())
            {
                Unlock();
                return (*iter);
            }
            break;
        }
    }

    Unlock();

    return (NULL);
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
PeerTable::FindEntry(const char *hostIdentity, PEER_ENTRY *& entryParam)
{  
    bool found = false;

    Lock();
    
    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {
        entryParam = (*iter);

        if (strcasecmp(hostIdentity, entryParam->hostIdentity) == 0)
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

bool
PeerTable::FindEntry(const char *hostIdentity, 
                     const char *realmName,
                     PEER_ENTRY *& entryParam)
{
    bool found = false;

    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {

        entryParam = (*iter);

        if ((strcasecmp(hostIdentity, entryParam->hostIdentity) == 0) &&
            (strcasecmp(realmName, entryParam->realmName) == 0))
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


int
PeerTable::GetCERFailureResultCode(const char *hostIdentity,
                     const char *realmName)
{
    int resultcode = ITS_DIA_UNKNOWN_PEER;
    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {
        //Check if hostname present in peer table.If found then
        //realm mentioned in CER is wrong.chances are there realm can exists
        //but host does not come under that realm
        if ((strcasecmp(hostIdentity, (*iter)->hostIdentity) == 0))
        {
            resultcode = ITS_DIA_REALM_NOT_SERVED;
            break;
        }
    }

    Unlock();
    if(resultcode == ITS_DIA_UNKNOWN_PEER)
    {
        DT_DBG(("Host <%s> not found in the peer table", hostIdentity));
    }
    else
    {
        DT_DBG(("Host <%s> found in the peer table but realm <%s> not served",
                hostIdentity,realmName));
    }
    return resultcode;
}



bool
PeerTable::FindEntry(const char *hostIdentity, 
                     const char *realmName,
                     PEER_ENTRY *& entryParam, ITS_USHORT& Instance)
{
    bool found = false;
    Instance   = 1;
    Lock();
    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {

        entryParam = (*iter);

        if ((strcasecmp(hostIdentity, entryParam->hostIdentity) == 0) &&
            (strcasecmp(realmName, entryParam->realmName) == 0))
        {
            Instance = DIA_PE_INDEX(entryParam);
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
PeerTable::InsertEntry(PEER_ENTRY* entryParam)
{
    int trIndx = 0;
    Lock();

    PEER_ENTRY *entry = NULL;
    if (FindEntry(entryParam->hostIdentity, entryParam->realmName, entry))
    {
        Unlock();
        return (ITS_EDUPLENTRY);
    }
    ITS_REQUIRE(entryParam != NULL);
      
    trIndx = DIA_PE_INDEX(entryParam); 
    /* Reserve the Slot in Transport */
    if ((trIndx == 0) || !(trTable.SetTrSlot(trIndx, entryParam)))
    {
        DT_ERR(("Invalid trIndx || Failed to reserve trSlot Peer = %s\n", 
                 DIA_PE_HOST(entryParam)));
        Unlock();
        return (!ITS_SUCCESS);
    }

    peerList.push_back(entryParam);

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
void
FreeEntry(PEER_ENTRY *entryParam)
{
    if (entryParam->hostIdentity)
    {
        free((void *)entryParam->hostIdentity);
        entryParam->hostIdentity = NULL;
    }

    if (entryParam->realmName)
    {
        free((void *)entryParam->realmName);
        entryParam->realmName = NULL;
    }

    if (entryParam->accSpecs.tInfo.serverIpAddr)
    {
        free ((void *)entryParam->accSpecs.tInfo.serverIpAddr);
        entryParam->accSpecs.tInfo.serverIpAddr = NULL;
    }
    
    for(int i =0;i < DIA_PE_CONN_TRANS_COUNT(entryParam);i++)
    {
        if (entryParam->connSpecs.tInfo[i].serverIpAddr)
        {
            free ((void *)entryParam->connSpecs.tInfo[i].serverIpAddr);
            entryParam->connSpecs.tInfo[i].serverIpAddr = NULL;
        }
    }

    if (entryParam->fsm)
    {
        delete entryParam->fsm;
    }

    if (entryParam->ceCache)
    {
        delete entryParam->ceCache;
    }

    if (entryParam->pendingQ)
    {
        delete entryParam->pendingQ;
    }
    if (entryParam->altHost)
    {
        free((void *)entryParam->altHost);
        entryParam->altHost = NULL;
    }

    if (entryParam->altRealmName)
    {
        free((void *)entryParam->altRealmName);
        entryParam->altRealmName = NULL;
    }

    free((void *)entryParam);

    entryParam = NULL;
}

int
PeerTable::RemoveEntry(const char *hostIdentity)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *entryParam = NULL;
    int trIndx = 0;
    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
                                       iter != peerList.end();
                                       iter++)
    {
        PEER_ENTRY* entry = (*iter);

        if (entry != NULL)
        {
            if (strcasecmp(hostIdentity, entry->hostIdentity) == 0)
            {
                trIndx = DIA_PE_INDEX(entry);
                /* Reserve the Slot in Transport */
                if (trTable.UnSetTrSlot(trIndx) == false)
                {
                    DT_WRN(("Failed to clear the trSlot"));
                }

                FreeEntry(entry);
                peerList.erase(iter);
            }

            Unlock();

            return ITS_SUCCESS;
        }
    }

    Unlock();

    return ITS_ENOTFOUND;

}

int
PeerTable::RemoveEntry(const char *hostIdentity,
                       const char *realmName)
{
    int ret = ITS_SUCCESS;
    PEER_ENTRY *entryParam = NULL;
    int trIndx = 0;
    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
                                       iter != peerList.end();
                                       iter++)
    {
        PEER_ENTRY* entry = (*iter);

        if (entry != NULL)
        {
            if ((strcasecmp(hostIdentity, entry->hostIdentity) == 0) &&
                (strcasecmp(realmName,    entry->realmName) == 0))
            {
                trIndx = DIA_PE_INDEX(entry);
                /* Reserve the Slot in Transport */
                if (trTable.UnSetTrSlot(trIndx) == false)
                {
                    DT_WRN(("Failed to clear the trSlot"));
                }

                FreeEntry(entry);
                peerList.erase(iter);

                Unlock();
                return ITS_SUCCESS;
            }

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
PeerTable::Print(std::ostream& os) const
{
    Lock();

    os << "------------------------------------------------------------" << endl;
    os << "-- Peer Table Begin --" << endl;
    os << "------------------------------------------------------------" << endl;
    os << endl;
    os << "Size: <" << peerList.size() << ">" << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;

    TypePeerList::const_iterator iter = peerList.begin();

    bool hasEntry = false;

    while(iter != peerList.end())
    {
        hasEntry = true;

        PEER_ENTRY *entry = (*iter);
        PrintEntry(os, entry);

        os << "--------------------------------------------------" << endl;

        iter++;
    }

    if (!hasEntry)
    {
        os << "--------------------------------------------------" << endl;
    }

    os << "------------------------------------------------------------" << endl;
    os << "-- Peer Table End --" << endl;
    os << "------------------------------------------------------------" << endl;

    Unlock();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      PeerEntry, PeerName
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
void PeerTable::Print(std::ostream& oss, PEER_ENTRY *peer, std::string peerName)
{
    eAccelero::MsgStatsCounter collatedCounter;
    collatedCounter = collateMsgStatsCounter(peer->statsCounter.m_peerGeneralStats.TotalMsgs);

    oss << "-----------------------------------------------------------"
        << endl;
    oss <<"    Peer              : ReqIn   | ReqOut | AnsIn  | AnsOut | Retnsmt |"
        <<endl;
    oss << "-----------------------------------------------------------"
        << endl;


    oss <<setw(4)<< " "<< peerName <<setw(19 - peerName.length())<<":"<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
        <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"
        <<setw(8)<<collateStats(peer->statsCounter.m_peerGeneralStats.retrasmitMsgs)<<"|"<<endl;

    oss << "-----------------------------------------------------------"
        << endl;
    oss <<"    ProtMsg           : ReqIn   | ReqOut | AnsIn  | AnsOut |"
        <<endl;
    oss << "-----------------------------------------------------------"
        << endl;

    collatedCounter = collateMsgStatsCounter(peer->statsCounter.m_peerGeneralStats.CEMsgs);

    oss << "    CER/CEA           : "<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
        <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"<<endl;

    collatedCounter = collateMsgStatsCounter(peer->statsCounter.m_peerGeneralStats.DWMsgs);

    oss << "    DWR/DWA           : "<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
        <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"<<endl;

    collatedCounter = collateMsgStatsCounter(peer->statsCounter.m_peerGeneralStats.DPMsgs);

    oss << "    DPR/DPA           : "<<setw(8)<<collatedCounter.GetRxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetTxReqCount()<<"|"
        <<setw(8)<<collatedCounter.GetRxRspCount()<< "|"
        <<setw(8)<<collatedCounter.GetTxRspCount()<<"|"<<endl;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To Print the Peerwise Stats
 *  Input Parameters:
 *      PeerName, RealmName
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
void PeerTable::PrintPeerStats(std::ostream& oss, std::string peerName, std::string realmName)
{
    Lock();
    try
    {
        char tbuf[ITS_PATH_MAX];
        time_t local;

        time(&local);
#if defined (__SUNPRO_CC)
        ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
        ctime_r(&local, tbuf);
#endif

        PEER_ENTRY *peer = NULL;

        if((!peerName.empty()) && (!realmName.empty()))
        {
            bool found = FindEntry(peerName.c_str(),realmName.c_str(), peer);
            if(!found || !peer)
            {   
                oss << "Peer not found in peer table : " << peerName.c_str() << endl;
                Unlock();
                return;
            }   

            oss << "-----------------------------------------------------------"
                << endl;    oss << "-- Dia Peer Stats -- at " << tbuf;
            oss << "-----------------------------------------------------------"
                << endl;
            Print(oss, peer, peerName);

        }
        else
        {
            PEER_ENTRY *firstPeer = PEER_TABLE->FindFirstEntry();
            if(firstPeer)
            {
                oss << "-----------------------------------------------------------"
                    << endl;    oss << "-- Dia All peer Stats -- at " << tbuf;
                oss << "-----------------------------------------------------------"
                    << endl;

                std::string peerName = DIA_PE_HOST(firstPeer);
                Print(oss, firstPeer, peerName);

                PEER_ENTRY *peer = firstPeer;
                PEER_ENTRY *nextPeer = NULL;
                while((nextPeer = PEER_TABLE->FindNextEntry(peer)))
                {
                    peer = nextPeer;
                    std::string peerName = DIA_PE_HOST(peer);
                    Print(oss, peer, peerName);
                }
            }
            else
            {
                DLOG_ERROR("peer table is empty");
                Unlock();
                return;
            }
        }
        Unlock();
    }
    catch(...)
    {
        DLOG_ERROR("Unkown Exception Caught");
        Unlock();
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
ostream&
operator<< (ostream& os, const PEER_ENTRY& entry)
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
operator<< (ostream& os, const PeerTable& table)
{
    table.Print(os);
    return os;
}

/****************************************************************************
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
PeerTable::DropAllPeers()
{
    DT_DBG(("Inside PeerTable::DropAllPeers()"));

    Lock();
    //Description: Corrected the iterator increment issue
    //Iterator was getting incremented after being erased.
    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); )
    {
        PEER_ENTRY *entry = (*iter);
        DT_DBG(("Removing Peer With HostIdentity: %s", entry->hostIdentity));
        FreeEntry(entry);
        peerList.erase(iter++);
    }

    Unlock();

    DT_DBG(("Exiting PeerTable::DropAllPeers()"));
}

int
PeerTable::StopTimer(DIA_TIMER_TYPE type, PEER_ENTRY *entry)
{
    if (entry == NULL)
    {
        return (!ITS_SUCCESS);
    }

    DT_DBG(("StopTimer Type = %d", type));

    switch (type)
    {
    case RETRY:
        TIMERS_CancelTimer(DIA_PE_RETRY_TIMER(entry));
        DIA_PE_RETRY_TIMER(entry) = TIMER_BAD_SERIAL;
        break;
    case EXPIRY:
        TIMERS_CancelTimer(DIA_PE_EXPIRY_TIMER(entry));
        DIA_PE_EXPIRY_TIMER(entry) = TIMER_BAD_SERIAL;
        break;
    case DEVICE_WATCHDOG:
        TIMERS_CancelTimer(DIA_PE_DW_TIMER(entry));
        DIA_PE_DW_TIMER(entry) = TIMER_BAD_SERIAL;
        break;
    case SOCK_FLUSH_TIMER:
	TIMERS_CancelTimer(DIA_PE_SOCK_FLUSH_TIMER(entry));
	DIA_PE_SOCK_FLUSH_TIMER(entry) = TIMER_BAD_SERIAL;
	break;
    default:
        DT_ERR(("Invalid Timer"));
        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

int
PeerTable::StartTimer(DIA_TIMER_TYPE type, PEER_ENTRY *entry,int timerVal)
{
    int duration;
    DIA_TIMER_CTXT timerCtxt;
    if (entry == NULL)
    {
        return (!ITS_SUCCESS);
    }

    if ((DIA_PE_IS_FORCE_DISCONNECTED(entry)) &&
        (type == RETRY))
    {
        DT_WRN(("Timer not started for Force Disconnected peer\n"));
        return (ITS_SUCCESS);
    }

    DT_DBG(("StartTimer Type = %s", TIMER_TO_TEXT(type)));

    timerCtxt.timerType = type;
    timerCtxt.data.peerInfo.peer = entry;

    switch (type)
    {
        case RETRY:
            {
                if(timerVal == 0)
                {
                    duration = DIA_PE_RETRY_TIME_VAL(entry);
                }else
                {
                    //This value in case of DPR rcvd with cause as BUSY or
                    //DO_NOT_WANT_TO_TALK_TO_YOU applicable for RFC6733
                    duration = timerVal;
                }

                DT_DBG(("StartTimer value = %d",duration));
                DIA_PE_RETRY_TIMER(entry) = TIMERS_StartTimer(DIASTACK_TQ_INST,
                        duration,
                        &timerCtxt,
                        sizeof(DIA_TIMER_CTXT));
                break;
            }
        case EXPIRY:
            {
                duration = DIA_PE_EXPIRY_TIME_VAL(entry);
                DIA_PE_EXPIRY_TIMER(entry) = TIMERS_StartTimer(DIASTACK_TQ_INST,
                        duration,
                        &timerCtxt,
                        sizeof(DIA_TIMER_CTXT));
                break;
            }
        case DEVICE_WATCHDOG:
            {
                duration = DIA_PE_DW_TIME_VAL(entry);

                /* Stop the DW timer if it is running */
                if (DIA_PE_DW_TIMER(entry) != TIMER_BAD_SERIAL)
                {
                    PeerTable::StopTimer(DEVICE_WATCHDOG, entry);
                    DT_DBG(("Re-Starting Timer = %s ", TIMER_TO_TEXT(type)));
                }
                DIA_PE_DW_TIMER(entry) = TIMERS_StartTimer(DIASTACK_TQ_INST,
                        duration,
                        &timerCtxt,
                        sizeof(DIA_TIMER_CTXT));
                break;
            }
	case SOCK_FLUSH_TIMER:
	    if (DIA_PE_SOCK_FLUSH_TIMER_VAL(entry))
	    {
		    duration = DIA_PE_SOCK_FLUSH_TIMER_VAL(entry);
	    }
	    else
	    {
		    duration = DEF_SOCK_FLUSH_TIMEOUT;
	    }
	    DT_DBG(("StartTimer value = %d",duration));
	    DIA_PE_SOCK_FLUSH_TIMER(entry) = TIMERS_StartTimer(DIASTACK_TQ_INST,
			    duration,
			    &timerCtxt,
			    sizeof(DIA_TIMER_CTXT));
	    break;
        default:
            {
                DT_ERR(("Invalid Timer"));
                return (!ITS_SUCCESS);
            }
    }

    return (ITS_SUCCESS);
}

void
PeerTable::UpdateAltPeerInfo()
{
    PEER_ENTRY* peer;
    Lock();
    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {
        peer = (*iter);
        const char* hostId    = DIA_PE_ALT_HOST(peer);
        const char* realmName = DIA_PE_ALT_REALM(peer);
        if (hostId &&
           realmName)
        {
            for (TypePeerList::iterator aiter = peerList.begin();
                aiter != peerList.end(); aiter++)
            {
               if ((strcasecmp(hostId, (*aiter)->hostIdentity) == 0) &&
                  (strcasecmp(realmName, (*aiter)->realmName) == 0))
               {
                  peer->altTrInst = &((*aiter)->trInst);
                  break;
               }
            }
        }
    }
    Unlock();
}


ITS_USHORT 
PeerTable::GetAltTrInst(ITS_USHORT trInst)
{
   //for trInst 1-4, index should be 0
   //for trInst 5-8, index should be 1
   trInst = (trInst-1) /  4;
   if (trInst < peerList.size() && peerList[trInst]->altTrInst)
   {
      PEER_ENTRY* entry = peerList[trInst];
      if (DIA_PE_PENDING_Q(entry) &&
         DIA_PEER_CHK_IF_REDUNDANT_MATE(entry) == ITS_FALSE)
      {
         return 0;
      }
      return *(entry->altTrInst);
   }
   return 0;
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
PeerTable::StartTTLTimer(DIA_TIMER_TYPE type, ITS_UINT duration, PEER_ENTRY* &pEntry)
{
    DIA_TIMER_CTXT timerCtxt;

    if (pEntry == NULL)
    {
        return (!ITS_SUCCESS);
    }

    DT_DBG(("StartTimer Type = %s", TIMER_TO_TEXT(type)));

    timerCtxt.timerType = type;
    timerCtxt.data.peerInfo.peer = pEntry;

    DIA_PE_TIME_TO_LIVE(pEntry) = TIMERS_StartTimer( DIASTACK_TQ_INST, 
                                                     duration,
                                                     &timerCtxt,
                                                     sizeof(DIA_TIMER_CTXT));
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
int
PeerTable::StopTTLTimer(DIA_TIMER_TYPE type, PEER_ENTRY *pEntry)
{   
    DT_DBG(("StopTimer Type = %s Id = %d",
              TIMER_TO_TEXT(type),  DIA_PE_TIME_TO_LIVE(pEntry) ));
    
    if ( DIA_PE_TIME_TO_LIVE(pEntry) != TIMER_BAD_SERIAL )
    {   
        TIMERS_CancelTimer(DIA_PE_TIME_TO_LIVE(pEntry));
        DIA_PE_TIME_TO_LIVE(pEntry) = TIMER_BAD_SERIAL;
    }
    return (ITS_SUCCESS);
}

void
PeerTable::ResetIsFailoveredFlag(PEER_ENTRY *entry)
{
    DT_DBG(("PeerTable::ResetIsFailoveredFlag"));

    PEER_ENTRY* peer = NULL;
    const char* peerName  = entry->hostIdentity;
    const char* peerRealm = entry->realmName;

    Lock();

    for (TypePeerList::iterator iter = peerList.begin();
         iter != peerList.end(); iter++)
    {
        peer = (*iter);

        const char* hostId    = DIA_PE_ALT_HOST(peer);
        const char* realmName = DIA_PE_ALT_REALM(peer);

        if (DIA_PEER_CHK_IS_FAILOVER_ENABLED(peer) && hostId && realmName)
        {
            if ((strcasecmp(peerName, hostId) == 0) &&
                (strcasecmp(peerRealm, realmName) == 0))
            {
                if (DIA_PEER_CHK_IS_FAILOVERED(peer))
                {
                    DT_DBG(("Peer Failovered flag set to false"));
                    DIA_PEER_CHK_IS_FAILOVERED(peer) = false;
                }
            }
        }
    }
    Unlock();
}

/*
 * GetPeerTableSize() 
 *          Returns Number of Peers in the Peer Table.
 *          0 if No Peers exists.
 *          -1 if any Error
 *
 */

unsigned int 
PeerTable::GetPeerTableSize(void)
{
   unsigned int NumPeers = 0;
   NumPeers = peerList.size();

   return NumPeers;
}

