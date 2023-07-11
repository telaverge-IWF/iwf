/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: dia_peer_discovery.cpp,v 1.9.44.1.4.3.14.1 2017/12/21 04:37:21 jkchaitanya Exp $
 *
 * LOG: $Log: dia_peer_discovery.cpp,v $
 * LOG: Revision 1.9.44.1.4.3.14.1  2017/12/21 04:37:21  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 1.9.44.1.4.3  2014/01/06 09:43:20  ncshivakumar
 * LOG: Fix for bug Bug 2398
 * LOG:
 * LOG: Revision 1.9.44.1.4.2  2013/11/14 08:54:54  ncshivakumar
 * LOG: RFC6733 changes
 * LOG:
 * LOG: Revision 1.9.44.1.4.1  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 1.9.44.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.9  2011/10/14 10:40:45  rajeshak
 * LOG: Removing OSS finding for DNS parsing
 * LOG:
 * LOG: Revision 1.8  2010/09/20 05:13:32  nvijikumar
 * LOG: 1. trIndx -1 is invalid for unsigned short
 * LOG: 2. Introduced delay in dynamic peer start (dia_mgmt.cpp)
 * LOG:
 * LOG: Revision 1.7  2010/07/07 08:24:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 1.6  2010/04/29 06:49:08  nvijikumar
 * LOG: Fix for compilation issue on Sun CC - version 12
 * LOG:
 * LOG: Revision 1.5  2009/09/07 06:24:00  rajeshak
 * LOG: Klockworks reported Issue fix.
 * LOG:
 * LOG: Revision 1.4  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.3  2009/04/16 05:09:16  rajeshak
 * LOG: Core dump while removing Peer from discovery List when list is empty.
 * LOG:
 * LOG: Revision 1.2  2009/04/14 08:56:22  rajeshak
 * LOG: Remove PeerEntry changed for peers in Open state after TTL Timeout.
 * LOG:
 * LOG: Revision 1.1  2009/04/13 14:10:01  rajeshak
 * LOG: Introduced new files for peer discovery.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dia_peer_discovery.cpp,v 1.9.44.1.4.3.14.1 2017/12/21 04:37:21 jkchaitanya Exp $"

#include <string>
#include <ctype.h>
#include <dia_err.h>
#include <dia_peer_discovery.h>
#include <dia_trace.h>
#include <dia_ip_trans.h>
#include <dia_realm_table.h>
#include <dia_peer_table.h>
#include <dia_mgmt.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif


extern void FreeEntry(PEER_ENTRY *entryParam);

ITS_Mutex DiscoveryList::lock(0);

static DiscoveryList* pDiscoveryList = NULL;

void
DiscoveryList::Lock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Acquire();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

void
DiscoveryList::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

DiscoveryList*
DiscoveryList::GetDiscoveryList()
{
    if (pDiscoveryList == NULL)
    {
        pDiscoveryList = new DiscoveryList;
    }

    return pDiscoveryList;
}

bool
DiscoveryList::FindEntry(const char *realmName, 
                         const char *peerName,
                         DIA_PEER_DISC_INFO *& entryParam)
{
    LIST_Entry* lEntry = NULL;
    entryParam = NULL;

    Lock();

    for (lEntry = LIST_HEAD(peerDiscoveryList);
         lEntry != NULL;
         lEntry = lEntry->next)
    {
        DIA_PEER_DISC_INFO* peerInfo = (DIA_PEER_DISC_INFO*) lEntry->data;
        if (peerInfo != NULL)
        {
            if (peerName != NULL)
            {
                if ((strcasecmp(realmName, peerInfo->realmName) == 0) &&
                    (strcasecmp(peerName, peerInfo->hostName) == 0))
                {
                    entryParam =  peerInfo;
                    Unlock();
                    return true;
                }
            }
            else
            {
                if ((strcasecmp(realmName, peerInfo->realmName) == 0) &&
                    (peerInfo->hostName == NULL))
                {
                    entryParam =  peerInfo;
                    Unlock();
                    return true;
                }
            }
        }
    }
    Unlock();
    return false;
}

int 
DiscoveryList::InsertEntry(DIA_PEER_DISC_INFO *entryParam)
{
    int ret = ITS_SUCCESS;
    DIA_PEER_DISC_INFO* pEntry = NULL;

    if (entryParam == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    if (peerDiscoveryList == NULL)
    {
        peerDiscoveryList = LIST_Create();
    }

    entryParam->peerDiscovered = false;
    entryParam->removePending = false;

    if (!FindEntry( entryParam->realmName, entryParam->hostName, pEntry))
    {    
        Lock();
        LIST_AddTail(peerDiscoveryList, entryParam, sizeof(DIA_PEER_DISC_INFO));
        Unlock();
    }
    else
    {
        DT_WRN(("Entry Already Exist\n"));
        ret = !ITS_SUCCESS;
    }

    //Print(cout);
    return ret;
}

int 
DiscoveryList::RemoveEntry(const char *realmName, const char* hostName)
{
    LIST_Entry* lEntry = NULL;

    if (peerDiscoveryList == NULL)
    {
        return !ITS_SUCCESS;
    }

    Lock();

    for (lEntry = LIST_HEAD(peerDiscoveryList);
         lEntry != NULL;
         lEntry = lEntry->next)
    {
        DIA_PEER_DISC_INFO* peerInfo = (DIA_PEER_DISC_INFO*) lEntry->data;
        if (peerInfo != NULL)
        {
            bool found = false;

            if (hostName)
            {
                if ((strcasecmp(realmName, peerInfo->realmName) == 0) &&
                    (strcasecmp(hostName, peerInfo->hostName) == 0))
                {
                    found = true;
                }
            }
            else
            {
                if ((strcasecmp(realmName, peerInfo->realmName) == 0) &&
                    (peerInfo->hostName == NULL))
                {
                    found = true;
                }
            }

            if (peerInfo->peerDiscovered)
            {
                DT_WRN(("Peer Entry Present. Cannot delete\n"));
                Unlock();
                return !ITS_SUCCESS;
            }

            if (found)
            {
                LIST_Unlink(peerDiscoveryList, lEntry);

                if (peerInfo->realmName)
                {
                    free(peerInfo->realmName);
                }
                if (peerInfo->hostName)
                {
                    free(peerInfo->hostName);
                }
                ITS_Free(peerInfo);
                ITS_Free(lEntry);

                Unlock();
                return ITS_SUCCESS;
            }
        }
    }
    Unlock();
    return !ITS_SUCCESS;
}

DIA_PEER_DISC_INFO* 
DiscoveryList::FindFirstEntry()
{
    DIA_PEER_DISC_INFO* peerInfo = NULL;

    Lock();
    if (peerDiscoveryList)
    {
        LIST_Entry* lEntry =  LIST_HEAD(peerDiscoveryList);
        if (lEntry)
        {
            peerInfo = (DIA_PEER_DISC_INFO*) lEntry->data;
        }
    }
    Unlock();
    return peerInfo;
}

DIA_PEER_DISC_INFO* 
DiscoveryList::FindNextEntry(DIA_PEER_DISC_INFO *pInfo)
{
    LIST_Entry* lEntry = NULL;

    Lock();
    for (lEntry = LIST_HEAD(peerDiscoveryList);
         lEntry != NULL;
         lEntry = lEntry->next)
    {
        DIA_PEER_DISC_INFO* peerInfo = (DIA_PEER_DISC_INFO*) lEntry->data;
        if (peerInfo == pInfo)
        {
            if (lEntry->next)
            {
                Unlock();
                return (DIA_PEER_DISC_INFO*)lEntry->next->data;
            }
        }
    }
    Unlock();
    return NULL;
}

void 
DiscoveryList::Print(std::ostream& os) const
{
    os << "----------------------------------------------------\n";
    os << "---------------  Peer Discovery List  --------------\n";
    os << "----------------------------------------------------\n";

    Lock();
    int count = LIST_COUNT(peerDiscoveryList);
    os << "Count = " << count << endl;

    LIST_Entry* lEntry = NULL;

    for (lEntry = LIST_HEAD(peerDiscoveryList);
         lEntry != NULL;
         lEntry = lEntry->next)
    {
        DIA_PEER_DISC_INFO* peerInfo = (DIA_PEER_DISC_INFO*) lEntry->data;
        if (peerInfo != NULL)
        {
            if (peerInfo->realmName)
            {
                os << "Realm Name: " << peerInfo->realmName << endl;
            }

            if (peerInfo->hostName)
            {
                os << "Peer Name: " << peerInfo->hostName << endl;
            }
            os << "----------------------------------------------------\n";
        }
    }
    Unlock();

    os << "----------------------------------------------------\n";
}


void DiaPeerDiscovery::Execute(void *arg)
{
    int timerVal = 0;
    DiaMgmt *diaMgmt = DiaMgmt::GetDiaMgmt();

    while(!_doExit)
    {
        DIA_PEER_DISC_INFO* pEntry = DiscoveryList::GetDiscoveryList()->FindFirstEntry();

        while(pEntry != NULL)
        {
            if(!pEntry->peerDiscovered && itsDiaConfig.isPeerDiscoveryEnabled())
            {
                DT_DBG(("Find peer's in realm %s",pEntry->realmName));
                const char* realmName = pEntry->realmName;
                char* hostName = pEntry->hostName;

                if (FindDiameterPeer(realmName, hostName) == ITS_SUCCESS)
                {
                    pEntry->peerDiscovered = true;
                    if (pEntry->hostName == NULL)
                    {
                        pEntry->hostName = hostName;
                    }
                }
            }

            if(pEntry->removePending)
            {
               if (diaMgmt->RemovePeer(pEntry->hostName,
                                           pEntry->realmName) == ITS_SUCCESS)
               {
                   pEntry->peerDiscovered = false;
                   pEntry->removePending = false;
               }
            }
            pEntry = DiscoveryList::GetDiscoveryList()->FindNextEntry(pEntry);
        }

        timerVal = itsDiaConfig.getDiscoveryInterval();

        sleep(timerVal);
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will query the dns server and if any peer supporting 
 *      diameter service (AAA) is found, then that peer is inserted into Peertable.
 *  Input Parameters:
 *    RealName 
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - on success
 *      failure - in case of error
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int 
DiaPeerDiscovery::FindDiameterPeer(const char* realmName, char*& peerName)
{
    int ret = !ITS_SUCCESS;
    bool peerFound = false;
    struct ip_addr *ip;
    RDATA* head = NULL;
    RDATA* rd;

    PEER_ENTRY* pEntry = NULL;

    DT_DBG(("DiaPeerDiscovery: FindDiameterPeer\n"));

    /* res init */
    DnsQuery::ResInit();

    /* do NAPTR lookup */
    head = GetDiaNaptrRecords((char*)realmName);

    if (head) 
    {
        /* filter and sort the records */
        head = SortNaptrRecords(head);

        /* process the NAPTR records */
        for( rd=head ; rd ; rd=rd->next )
        {
            //NAPTR_RDATA* ptr = GET_NAPTR_REC(rd);
            NaptrRecord* ptr = GET_NAPTR_REC(rd);
            //DT_DBG(("NAPTR Rec = %s \n", ptr->repl));

            if(rd->rtype == A_QUERY && itsDiaConfig.isSnaptrSupportEnabled())
            {
                DT_DBG(("Query for A Records.Replacement string is %s",ptr->GetReplacement()));
                //RDATA* headPtrOfARec = GetDiaARecords(ptr->GetReplacement());
                //A_RDATA* aRec = GET_A_REC(headPtrOfARec);

                SrvRecord srvRec;
                srvRec.SetName(ptr->GetReplacement(),strlen(ptr->GetReplacement()) + 1);
                HOST_DATA* hdata = ResolveHost(&srvRec,"tls");
                if (hdata != NULL)
                {
                    ret = InsertIntoRealmTable(realmName);
                    ret = InsertIntoPeerTable(hdata, realmName);

                    peerName = strdup(hdata->name);

                    free(hdata);
                    hdata = NULL;

                    /* to discover all peers remove following 2 lines */
                    peerFound = true;
                    break;
                }
            }

            RDATA* headPtr = GetDiaSrvRecords(ptr->GetReplacement());
            if (headPtr)
            {
                if (peerName)
                {
                    string tmp;
                    tmp.append(peerName);
                    tmp.append(".");
                    tmp.append(realmName);

                    /* if Peer is given get SRV rec for that peer */
                    SrvRecord *srv = GetHostSrvRec(headPtr, tmp.c_str());
                    if (srv != NULL)
                    {
                        /* SRV record for the peer found */
                        HOST_DATA* hdata = ResolveHost(srv, ptr->GetReplacement());
                        if (hdata != NULL)
                        {
                            ret = InsertIntoRealmTable(realmName);
                            ret = InsertIntoPeerTable(hdata, realmName);

                            free(hdata);
                            hdata = NULL;
                            peerFound = true;
                        }
                    }
                }
                else
                {
                    headPtr = SortSrvRecords(headPtr);
                    RDATA *rec;
                    for (rec=headPtr; rec ; rec=rec->next ) 
                    {
                        SrvRecord *srv = (SrvRecord*) rec->rdata;
                        if (srv != NULL) 
                        {
                            HOST_DATA* hdata = ResolveHost(srv, ptr->GetReplacement());
                            if (hdata != NULL)
                            {
                                ret = InsertIntoRealmTable(realmName);
                                ret = InsertIntoPeerTable(hdata, realmName);
 
                                peerName = strdup(hdata->name);

                                free(hdata);
                                hdata = NULL;

                                /* to discover all peers remove following 2 lines */
                                peerFound = true;
                                break;
                            }
                        }
                    }
                }
                /* free SRV records */
                FreeDnsRecords(headPtr);
            }

            if (peerFound)
            {
                break;
            }
        }
        /* free NAPTR records */
        FreeDnsRecords(head);
        
        return ITS_SUCCESS;
    }

    /* NAPTR Record Look-up failed. Do SRV query for TCP */

    DT_DBG(("No valid NAPTR record found for %s\n", realmName));
    DT_DBG(("Trying direct SRV lookup\n"));
    
    std::string srvStr[4];
    int numberOfSrvStrings = 2;

    if(itsDiaConfig.isSnaptrSupportEnabled())
    {
        srvStr[0] = DIAMETER_SRV_Q_TCP_STRING;
        srvStr[1] = DIAMETER_SRV_Q_TLS_TCP_STRING;
        srvStr[2] = DIAMETER_SRV_Q_SCTP_STRING;
        srvStr[3] = DIAMETER_SRV_Q_DTLS_SCTP_STRING;
        numberOfSrvStrings = 4;

    }
    else
    {
        srvStr[0] = DIAMETER_SRV_Q_TCP_STRING;
        srvStr[1] = DIAMETER_SRV_Q_SCTP_STRING;
    }

    for(int i = 0; i < numberOfSrvStrings;i++)
    {

        srvStr[i].append(realmName);

        RDATA* headPtr = GetDiaSrvRecords((char*)srvStr[i].c_str());
        if (headPtr)
        {
            /* if Peer is given get SRV rec for that peer */
            if (peerName)
            {
                string tmp;
                tmp.append(peerName);
                tmp.append(".");
                tmp.append(realmName);

                SrvRecord *srv = GetHostSrvRec(headPtr, tmp.c_str());
                if (srv != NULL)
                {
                    HOST_DATA* hdata = ResolveHost(srv, srvStr[i].c_str());
                    if (hdata != NULL)
                    {
                        ret = InsertIntoRealmTable(realmName);
                        ret = InsertIntoPeerTable(hdata, realmName);

                        free(hdata);
                        hdata = NULL;
                        peerFound = true;
                    }
                }
            }
            else
            {
                RDATA *rec = NULL;
                for( rec=headPtr; rec ; rec=rec->next ) 
                {
                    SrvRecord *srv = (SrvRecord*) rec->rdata;
                    if (srv != NULL) 
                    {
                        HOST_DATA* hdata = ResolveHost(srv, srvStr[i].c_str());
                        /* dns query success. return will valid host entry */
                        if (hdata != NULL)
                        {
                            ret = InsertIntoRealmTable(realmName);
                            ret = InsertIntoPeerTable(hdata, realmName);

                            peerName = strdup(hdata->name);

                            free(hdata);
                            hdata = NULL;
                            peerFound = true;
                            break;
                        }
                    }
                }
            }
            /* free SRV records */
            FreeDnsRecords(headPtr);
            return ITS_SUCCESS;
        }
    }
    
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will parse the buffer returned from the dns server  
 *  Input Parameters:
 *     buffer, buffer length, Query Type
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to RDATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/ 
RDATA* 
DiaPeerDiscovery::GetDnsRecords(unsigned char* respBuf, int respLen)
{
    ns_msg msg;
    ns_rr rRec;
    int ret ;
    int aCount = 0;
    RDATA* rd;
    RDATA* head;
    RDATA** last;

    head = rd = NULL;
    last = &head;

    //DT_DBG(("DiaPeerDiscovery::GetDnsRecords\n"));

    ret = ns_initparse(respBuf, respLen , &msg);
    if (ret < 0)
    {
        /* handle error */
        DT_ERR(("Name Server init parse failed\n"));
        return NULL;
    }

    aCount = ns_msg_count(msg, ns_s_an);

    for (int i=0; i<aCount; i++)
    {
        int type, rclass, ttl, rLen;
        const unsigned char* ptrData = NULL;

        /* parse answer and get each record in rRec structure */
        ret = ns_parserr(&msg, ns_s_an, i, &rRec);
        if (ret < 0)
        {
            DT_ERR(("DNS Record Parse Error\n"));
            if (head)
            {
                FreeDnsRecords(head);
                head = NULL;
            }
            return NULL;
        }

        /* get the record information */
        type = ns_rr_type(rRec);
        rclass = ns_rr_class(rRec);
        ttl = ns_rr_ttl(rRec);
        rLen = ns_rr_rdlen(rRec);
        ptrData = ns_rr_rdata(rRec);

        /*allocate memory for the new record */
        rd = (RDATA*) calloc(1, sizeof(RDATA));
        if (rd == NULL)
        {
            DT_ERR(("Memory Allocation failed\n"));
            if (head)
            {
                FreeDnsRecords(head);
                head = NULL;
            }
            return NULL;
        }

        rd->rtype  = type;
        rd->rclass = rclass;
        rd->rttl   = ttl;
        rd->next  = NULL;
        rd->rdata = NULL;

        switch(type)
        {
            case NAPTR_QUERY:
                /* call the Naptr parser function here */
                rd->rdata = DnsQuery::ParseNaptrRecord(respBuf,
                                                       respBuf+respLen, 
                                                       (unsigned char*) ptrData);
                break;
            case SRV_QUERY:
                /* call the SRV parser function here */
                rd->rdata = DnsQuery::ParseSrvRecord(respBuf,
                                                     respBuf+respLen, 
                                                     (unsigned char*) ptrData);
                break;
            case A_QUERY:
                rd->rdata = DnsQuery::ParseIpv4AddrRecord(respBuf,
                                                          respBuf+respLen,
                                                          (unsigned char*) ptrData);
                break;
            case AAAA_QUERY:
                rd->rdata = NULL;
                break;
        }
        if (rd->rdata == NULL) 
        {
            free(rd);
            if (head)
            {
                FreeDnsRecords(head);
                head = NULL;
            }
            return NULL;
        }

        /*insert the new record in linked list */
        *last = rd;
        last = &(rd->next);
    }

    //DT_DBG(("Successfully retrieved DNS records\n"));

    /* return the records */
    return head;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will query the DNS Server  for NAPTR records  
 *  Input Parameters:
 *     DNS Lookup Key (domain name)
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to RDATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/ 
RDATA* 
DiaPeerDiscovery::GetDiaNaptrRecords(char* domain)
{
    int respLen = 0;
    unsigned char* respBuf = NULL;

    RDATA* data =  NULL;

    DT_DBG(("DiaPeerDiscovery::GetDiaNaptrRecords\n"));

    respLen = DnsQuery::NaptrQuery(domain, respBuf);

    if (respLen > 0)
    {
        data = GetDnsRecords(respBuf, respLen);
    }

    /* free the buffer. It is not required any more. */
    if (respBuf != NULL)
    {
        free(respBuf);
    }
    return data;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will query the DNS Server forSRV records 
 *  Input Parameters:
 *     DNS Lookup Key (domain name)
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to HOST_DATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/ 
RDATA* 
DiaPeerDiscovery::GetDiaSrvRecords(char* domainKey)
{
    int respLen = 0;
    unsigned char* respBuf = NULL;

    RDATA* data =  NULL;

    DT_DBG(("DiaPeerDiscovery::GetDiaSrvRecords\n"));

    respLen = DnsQuery::SrvQuery(domainKey, respBuf);
    
    if (respLen > 0)
    {
        data = GetDnsRecords(respBuf, respLen);
    }
    
    /* Get SRV Records Failed */
    if (respBuf != NULL)
    {
        free(respBuf);
        respBuf = NULL;
    }

    return data;
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will query the DNS Server for A records 
 *  Input Parameters:
 *     DNS Lookup Key (replacement string)
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to HOST_DATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/ 
RDATA* 
DiaPeerDiscovery::GetDiaARecords(char* domainKey)
{
    int respLen = 0;
    unsigned char* respBuf = NULL;

    RDATA* data =  NULL;

    DT_DBG(("DiaPeerDiscovery::GetDiaARecords\n"));

    respLen = DnsQuery::AQuery(domainKey, respBuf);
    
    if (respLen > 0)
    {
        data = GetDnsRecords(respBuf, respLen);
    }
    
    /* Get A Records Failed */
    if (respBuf != NULL)
    {
        free(respBuf);
        respBuf = NULL;
    }

    return data;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *     This Function will filter diameter relavant record and sort them 
 *     according to the oder and priority.
 *     This will also delete the dns records which are not relavant for diameter.
 *  Input Parameters:
 *     
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to RDATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/ 
RDATA *
DiaPeerDiscovery::SortNaptrRecords(RDATA* rRecord)
{
    char prot;
    char* str;
    unsigned int prio;
    RDATA* head = NULL;
    RDATA* tail = NULL;
    RDATA* tmpList = NULL;

    //DT_DBG(("DiaPeerDiscovery::SortNaptrRecords\n"));

    RDATA *rec, *nxtRec; 

    for (rec=rRecord; rec ; rec=nxtRec) 
    {
        nxtRec = rec->next;

        //NAPTR_RDATA *naptr = (NAPTR_RDATA*)rec->rdata;
        NaptrRecord *naptr = (NaptrRecord*)rec->rdata;

        if (naptr == NULL) 
        {
            goto skip;
        }

        /* first filter out by flag and service */
        //if (naptr->flags_len != 1 || (tolower(naptr->flags[0]) != 's'))
        if (naptr->GetFlagLength() != 1 || (tolower(naptr->GetFlags()[0]) != 's'))
        {
            if(itsDiaConfig.isSnaptrSupportEnabled())
            {
                if(tolower(naptr->GetFlags()[0]) != 'a')
                {
                    goto skip;
                }
            }
            else
            {
                goto skip;
            }
        }

        //if (naptr->repl_len==0 || naptr->regexp_len!=0 )
        if (naptr->GetReplacementLength() == 0 || naptr->GetRegExpLength() !=0 )
        {
            goto skip;
        }

        /* Check if AAA protocol is supported */
        str = strstr(naptr->GetServices(), "AAA");
        if (str == NULL)
        {
            str = strstr(naptr->GetServices(), "aaa");
        }
        if (str == NULL)
        {
            goto skip;
        }


        if(itsDiaConfig.isSnaptrSupportEnabled())
        {
            str = strstr(naptr->GetServices(), "diameter");
            if (str == NULL)
            {
                goto skip;
            }

            str = strstr(naptr->GetServices(), "tcp");
            if (str == NULL)
            {
                str = strstr(naptr->GetServices(), "sctp");
            }
            if (str == NULL)
            {
                str = strstr(naptr->GetServices(), "dtls");
            }

            if (str == NULL)
            {
                str = strstr(naptr->GetServices(), "tls");
            }

            if(str == NULL)
            {
                goto skip;
            }
        }
        else
        {
            /* Transort protocol supported */
            str = strstr(naptr->GetServices(), "D2");
            if (str == NULL)
            {
                goto skip;
            }

            /* get the transport protocol*/
            prot = str[2];

            /* TCP - SCTP Supported */ 
            if ((tolower(prot) != 't') && (tolower(prot) != 's'))
            {
                goto skip;
            }
        }
        /* this is a supported service -> add it according to order to the 
         * new head list */
        prio = NAPTR_PRIO(GET_NAPTR_REC(rec));
        if (head == NULL) 
        {
            head = tail = rec;
            rec->next = NULL;
        } 
        else if ( NAPTR_PRIO(GET_NAPTR_REC(head)) > prio ) 
        {
            /* priority is less than the priority of head record.
             * So insert at this record before head record
             */
            rec->next = head;
            head = rec;
        }
        else if ( prio >= NAPTR_PRIO(GET_NAPTR_REC(tail)) ) 
        {
            /* priority is greater than the priority of last record.
             * So insert at this record at the end. 
             */
            rec->next = NULL;
            tail->next = rec;
            tail = rec;
        } 
        else 
        {
            RDATA* tmp1,*tmp2;
            for( tmp1=head, tmp2=head->next; tmp1 && tmp1->next; 
                                  tmp1=tmp2, tmp2=tmp2->next)
            {
                if (prio <= NAPTR_PRIO(GET_NAPTR_REC(tmp2)))
                {
                    break;
                }
            }
            //tmp2->next = NULL;
            rec->next = tmp2;
            tmp1->next = rec;
        }

        continue;
skip:
        /* This is not a relavant record*/
        rec->next = tmpList;
        tmpList = rec;
    }

    if (tmpList)
    {
        FreeDnsRecords(tmpList);
        tmpList = NULL;
    }

    return head;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will sort the dns SRV records
 *  Input Parameters:
 *     
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to RDATA :- if success
 *      NULL - in case of error
 *  Notes:      
 *      
 *  See Also:
 *
 ****************************************************************************/
RDATA *
DiaPeerDiscovery::SortSrvRecords(RDATA* rRecord)
{
    RDATA* head = NULL;
    RDATA *rec = rRecord;
    RDATA *tail = NULL;
    RDATA *rd_next;
    RDATA *crt;
    RDATA *crt2;
    unsigned int weight_sum;
    unsigned int rand_no; 


    RDATA* nxtRec=NULL;

    while (rec)
    {
        rd_next = rec->next;

        /* only on element with same priority ? */
        if (rd_next==NULL ||
            GET_SRV_REC(rec)->GetPriority() != GET_SRV_REC(rd_next)->GetPriority()) 
        {
            if (tail) 
            {
                tail->next=rec;
                tail=rec;
            }
            else 
            {
                head = tail = rec;
            }
        }
        else 
        {
            /* multiple nodes with same priority */
            /* -> calculate running sums (and detect the end) */
            weight_sum = GET_SRV_REC(rec)->GetWeight();
            GET_SRV_REC(rec)->SetWeightSum(weight_sum);
            crt = rec;
            
            while (crt && crt->next && 
                  (GET_SRV_REC(rec)->GetPriority() == GET_SRV_REC(crt->next)->GetPriority()) ) 
            {
                crt = crt->next;
                weight_sum += GET_SRV_REC(crt)->GetWeight();
                GET_SRV_REC(crt)->SetWeightSum(weight_sum);
            }

            /* crt will point to last RR with same priority */
            rd_next = crt->next;
            crt->next = NULL;

            /* order the elements between rd and crt */
            while (rec->next) 
            {
                rand_no = (unsigned int)
                          (weight_sum*((float)rand()/RAND_MAX));

                for( crt=rec,crt2=NULL ; crt ; crt2=crt,crt=crt->next) 
                {
                    if (GET_SRV_REC(crt)->GetWeightSum()>=rand_no)
                        break;
                }

                if (crt == NULL) 
                {
                    crt = rec;
                    crt2 = NULL;
                }

                /* remove the element from the list ... */
                if (crt2==NULL) 
                {
                    rec = rec->next;
                }
                else 
                {
                    crt2->next = crt->next;
                }

                /* .... and update the running sums */
                ITS_USHORT temp;
                for ( crt2=crt->next ; crt2 ; crt2=crt2->next)
                {
                    temp = GET_SRV_REC(crt2)->GetWeightSum() -
                                GET_SRV_REC(crt2)->GetWeight();
                    GET_SRV_REC(crt2)->SetWeightSum(temp);
                }

                weight_sum -= GET_SRV_REC(crt)->GetWeight();
                /* link the crt in the new list */
                crt->next = 0;
                if (tail)
                {
                    tail->next=crt;
                    tail=crt;
                }
                else 
                {
                    head=tail=crt;
                }
            }
            /* just insert the last remaining element */
            tail->next = rec; 
            tail = rec ;
        }

        rec = rd_next;
    }

    return head;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will return the SRV record for host 
 *
 *  Input Parameters:
 *    SRV Records, HostName
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      SRV Record - on success
 *      NULL - in case of error
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SrvRecord*
DiaPeerDiscovery::GetHostSrvRec(RDATA* rRecord, const char* hostIdent)
{
    RDATA* nxtRec=NULL;
    for (RDATA* rec1=rRecord; rec1 ; rec1=nxtRec )
    {
        nxtRec = rec1->next;

        SrvRecord* pSrv = GET_SRV_REC(rec1);

        char* ptr = strstr(pSrv->GetName(), hostIdent);
        if (ptr != NULL)
        {
            /*srv record matching with host identity */
            return pSrv;
        }
    }

    return NULL;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will insert into peer table.
 *  Input Parameters:
 *
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if success
 *      
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaPeerDiscovery::InsertIntoPeerTable(HOST_DATA* hdata, const char* realmName)
{
    int ret = ITS_SUCCESS;
    char ipBuf[64];
    PEER_ENTRY* pEntry = NULL;

    memset(ipBuf, 0, sizeof(ipBuf));

    /* get trIndex for Peer */
    ITS_USHORT trIndx = trTable.GetNextTrIndex();

    if (trIndx == 0)
    {
        DT_ERR(("Max trans limit reached failed allocate trIndex For %s\n",
                                 hdata->name));

        DIA_Alarm(15250, __FILE__, __LINE__, "Peer=%s:Realm=%s",
                                  hdata->name, realmName);

        return ITS_DIA_EINVALID_PEER;
    }

    pEntry = (PEER_ENTRY *)malloc(sizeof(PEER_ENTRY));

    if (pEntry == NULL)
    {
        throw "Error: Malloc failed";
    }
    memset(pEntry, 0, sizeof(PEER_ENTRY));

    DIA_PE_STATIC(pEntry) = ITS_FALSE;
    DIA_PE_CONN_SPECS(pEntry).tInfo[0].type = hdata->trType;
    DT_DBG(("Transport type = %d",hdata->trType));
    DIA_PE_HOST(pEntry) = strdup(hdata->name);
    DIA_PE_REALM(pEntry) = strdup(realmName);

    if(hdata->port)
    {    
        DIA_PE_CONN_SPECS(pEntry).tInfo[0].portNo = hdata->port;
        DT_DBG(("port = %u",hdata->port));
    }

    if(hdata->securePort)
    {    
        DIA_PE_CONN_SPECS(pEntry).tInfo[0].securePort = hdata->securePort;
        DT_DBG((" secure port = %u",hdata->securePort));
    }


    DIA_PE_CONN_TRANS_COUNT(pEntry) = 1;
    DIA_PE_DW_TIME_VAL(pEntry) = 30;
    DIA_PE_RETRY_TIME_VAL(pEntry) = 30;
    DIA_PE_EXPIRY_TIME_VAL(pEntry) = 120;

    DIA_PE_STATE(pEntry) = PEER_ST_CLOSED;
    DIA_PE_FSM(pEntry)   = new PeerFsm();
    DIA_PE_INDEX(pEntry) = trIndx;
    DIA_PE_IS_DISCOVERED(pEntry) = true;
    DIA_PE_IS_FIRST_CAP_EXCH(pEntry) = true;
    DIA_PE_TLS_EN(pEntry) = hdata->isTLSEnabled;

    /* IPV4 Addr ipType -> 0 */
    if (hdata->ipType == IPV4)
    {
        //Correcting Calling risky function
        snprintf(ipBuf, 63, "%d.%d.%d.%d", hdata->u.ip[0],
                                      hdata->u.ip[1],
                                      hdata->u.ip[2],
                                      hdata->u.ip[3]);

        DIA_PE_CONN_SPECS(pEntry).tInfo[0].serverIpAddr =
                                                    strdup(ipBuf);
    }
    else
    {
        /* TODO - proper coding */
        //Correcting Calling risky function
        snprintf(ipBuf, 63, "%x%x:%x%x:%x%x:%x%x::%x%x:%x%x:%x%x:%x%x", 
                               hdata->u.ip6[0],  hdata->u.ip6[1],  hdata->u.ip6[2],
                               hdata->u.ip6[3],  hdata->u.ip6[4],  hdata->u.ip6[5],
                               hdata->u.ip6[6],  hdata->u.ip6[7],  hdata->u.ip6[8],
                               hdata->u.ip6[9],  hdata->u.ip6[10], hdata->u.ip6[11], 
                               hdata->u.ip6[12], hdata->u.ip6[13], hdata->u.ip6[14],
                               hdata->u.ip6[15]);

        DIA_PE_CONN_SPECS(pEntry).tInfo[0].serverIpAddr =
                                                    strdup((const char*)hdata->u.ip6);
    }

    if(DIA_PE_CONN_TINFO(pEntry).type == ITS_DIA_T_SCTP)
    {

        DIA_PE_CONN_TINFO(pEntry).multiHomeipaddrs[0] = 
                              (char *)DIA_PE_CONN_TINFO(pEntry).serverIpAddr;
        DIA_PE_CONN_TINFO(pEntry).noIPs = 1;
    }

    /* set connection initiate flag if set in config XML */
    if (itsDiaConfig.GetInitiateConnsOpt())
    {
        DIA_PE_INIT_CONN(pEntry) = true;
    }

    if (MUTEX_CreateMutex(&DIA_PE_MUX(pEntry), 0) != ITS_SUCCESS)
    {
        FreeEntry(pEntry);
        throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        return ITS_DIA_ALLOCFAIL;
    }

    ret = PEER_TABLE->InsertEntry(pEntry);
    if (ret == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Added Peer Entry For %s\n",
                                         pEntry->hostIdentity));
        PeerTable::StartTTLTimer(TTL_TIMER, hdata->ttl, pEntry);

        if((DIA_TRACE()->IsEnabled() && DIA_TRACE()->IsEnabled(DIA_DEBUG)))
        {
            cout<<"\n-----Peer table after peer discovery----\n"<<endl;
            cout<<*(PeerTable::GetPeerTable())<<endl;
        }
    }
    else
    {
        DT_WRN(("Failed to Add Peer Entry: Entry Exists For %s\n",
                                 pEntry->hostIdentity));

        FreeEntry(pEntry);
        return ITS_DIA_EINVALID_PEER;
    }

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will insert into realm table.
 *  Input Parameters:
 *
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if success
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaPeerDiscovery::InsertIntoRealmTable(const char* realmName)
{
    int ret = ITS_SUCCESS;

    REALM_ENTRY* rEntry = NULL;

    rEntry = (REALM_ENTRY*) malloc(sizeof(REALM_ENTRY));
    if (rEntry == NULL)
    {
        throw "Error: Malloc failed";
    }

    memset(rEntry, 0, sizeof(REALM_ENTRY));
    rEntry->isDefault = ITS_FALSE;
    rEntry->realmName = strdup(realmName);
    rEntry->isStatic = ITS_FALSE;
    rEntry->destCnt = 0;
    rEntry->localAction = ITS_DIA_LOCAL;
    rEntry->proxyInfoAvpEnabled = false;

    ret = RealmTable::GetRealmTable()->InsertEntry(rEntry);
    if (ret == ITS_SUCCESS)
    {
        DT_DBG(("Succesfully Added Realm Entry"));
    }
    else
    {
        free ((void *)rEntry->realmName);
        free ((void *)rEntry);
        DT_ERR(("Failed to Add Realm Entry "));
        ret = ITS_DIA_LOCAL_REALM_MISMATCH;
    }

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      This Function will Resolve the host Addr.
 *  Input Parameters:
 *      SRV Record, Domain Name
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Host Data Rec if success.
 *      NULL if error.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
HOST_DATA*
DiaPeerDiscovery::ResolveHost(SrvRecord *srv, const char* domainKey)
{
    unsigned char* addrBuf = NULL;

    /* Address translation (A Query/ AAAA Query) */
    int addrLen = DnsQuery::ResolveHostName(srv->GetName(), addrBuf);
    if (addrLen > 0)
    {
        /* this will get the IPv4 or IPv6 records from the buffer */
        RDATA* adrRec = GetDnsRecords(addrBuf, addrLen);
        if (adrRec != NULL)
        {
            /* success: we have a host with valid ip */
            HOST_DATA* hdata = (HOST_DATA*) malloc (sizeof(HOST_DATA));
            if (hdata == NULL)
            {
                /* memory allocation failed */
                if (addrBuf != NULL)
                {
                    free(addrBuf);
                    addrBuf = NULL;
                }

                FreeDnsRecords(adrRec);
                return NULL;
            }

            memset(hdata, 0, sizeof(HOST_DATA));
            char* nameEnd = strstr(srv->GetName(), ".");
            if (nameEnd == NULL)
            {
                /* error */
            }

            int nLen = nameEnd - srv->GetName();
            memcpy(hdata->name, srv->GetName(), nLen);
            hdata->name[nLen] = '\0';

            hdata->ttl  = adrRec->rttl;
            if (adrRec->rtype == A_QUERY)
            {
                hdata->ipType = IPV4; 
                memcpy(hdata->u.ip, adrRec->rdata, 4);
            }
            else
            {
                hdata->ipType = IPV6; 
                memcpy(hdata->u.ip6, adrRec->rdata, 16);
            }

            hdata->isTLSEnabled = true;

            if ((itsDiaConfig.isSnaptrSupportEnabled()) &&
                ((strstr(domainKey, "tls") != NULL) ||
                (strstr(domainKey, "TLS") != NULL)))
            {
                hdata->trType = ITS_DIA_T_TCP;
                hdata->securePort = ntohs(srv->GetPort());
            }
            else if ((strstr(domainKey, "tcp") != NULL) ||
                (strstr(domainKey, "TCP") != NULL))
            {
                hdata->trType = ITS_DIA_T_TCP;
                hdata->port = ntohs(srv->GetPort());
            }
            else
            {
                hdata->trType = ITS_DIA_T_SCTP;
                hdata->port = ntohs(srv->GetPort());
                hdata->isTLSEnabled = false;
            }


            if (addrBuf != NULL)
            {
                free(addrBuf);
                addrBuf = NULL;
            }
            FreeDnsRecords(adrRec);
            return hdata;
        }
    }
    return NULL;
}

