/*********************************-*-HPP-*-**********************************
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
 *  ID: $Id: dia_peer_discovery.h,v 1.3.44.1.4.1 2013/10/26 07:42:21 ncshivakumar Exp $
 *
 *  LOG: $Log: dia_peer_discovery.h,v $
 *  LOG: Revision 1.3.44.1.4.1  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 1.3.44.1  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.3  2011/10/14 10:41:08  rajeshak
 *  LOG: Removing OSS finding for DNS parsing
 *  LOG:
 *  LOG: Revision 1.2  2009/04/14 08:59:02  rajeshak
 *  LOG: Remove PeerEntry changed for peers in Open state after TTL Timeout.
 *  LOG:
 *  LOG: Revision 1.1  2009/04/13 14:08:42  rajeshak
 *  LOG: Introduced new files for peer discovery.
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_peer_discovery.h,v 1.3.44.1.4.1 2013/10/26 07:42:21 ncshivakumar Exp $"

#ifndef DIA_PEER_DISCOVERY_H
#define DIA_PEER_DISCOVERY_H 

#include <its_emlist.h>
#include <dia_thread.h>
#include <dia_dns_query.h>

#define DIAMETER_SRV_Q_TCP_STRING         "_diameter._tcp."
#define DIAMETER_SRV_Q_SCTP_STRING        "_diameter._sctp."
#define DIAMETER_SRV_Q_TLS_TCP_STRING     "_diameters._tcp."
#define DIAMETER_SRV_Q_DTLS_SCTP_STRING   "_diameters._sctp."


typedef struct
{
    char* hostName;
    char* realmName;
    bool  peerDiscovered;
    bool  removePending;
}
DIA_PEER_DISC_INFO;

class DiscoveryList
{
public:
#if 0
    bool FindEntry(const char *realmName, DIA_PEER_DISC_INFO *& entryParam);
#endif

    static DiscoveryList *GetDiscoveryList();

    bool FindEntry(const char *realmName, const char *peerName, 
                              DIA_PEER_DISC_INFO *& entryParam);
    int InsertEntry(DIA_PEER_DISC_INFO *entryParam);
    int RemoveEntry(const char *realmName, const char* hostName);
    DIA_PEER_DISC_INFO* FindFirstEntry();
    DIA_PEER_DISC_INFO* FindNextEntry(DIA_PEER_DISC_INFO *pInfo);
    void Print(std::ostream& os) const;
   
private:
    LIST_Manager* peerDiscoveryList;
    
    ITS_UINT noCurrEnts;
    static its::ITS_Mutex lock;
    //static its::ITS_Mutex guard;
    ~DiscoveryList();
    DiscoveryList() { peerDiscoveryList = NULL;noCurrEnts=0;}
    DiscoveryList(DiscoveryList&) {}
    void Lock() const;
    void Unlock() const;
};


class DiaPeerDiscovery  : public DIAThread
{
public:
    DiaPeerDiscovery()
    : DIAThread(0, true, this, DETACHED)
    {
        _doExit = ITS_FALSE;
    }

    void Execute(void *arg);
    int FindDiameterPeer(const char* realmName, char*& hostName);
    HOST_DATA* ResolveHost(SrvRecord *srv, const char* domainKey);
    RDATA* GetDnsRecords(unsigned char* respBuf, int respLen);
    RDATA* GetDiaNaptrRecords(char* domain);
    //HOST_DATA* GetDiaSrvRecords(char* domainKey);
    RDATA* GetDiaSrvRecords(char* domainKey);
    RDATA* GetDiaARecords(char* domainKey);
    RDATA* SortNaptrRecords(RDATA* rRecord);
    RDATA* SortSrvRecords(RDATA* rRecord);
    int InsertIntoPeerTable(HOST_DATA* hdata, const char* realmName);
    int InsertIntoRealmTable(const char* realmName);
    SrvRecord* GetHostSrvRec(RDATA*, const char*);

private:
    ITS_BOOLEAN  _doExit;
};

#endif
