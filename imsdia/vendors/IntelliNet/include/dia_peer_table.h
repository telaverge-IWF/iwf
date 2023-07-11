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
 *  ID: $Id: dia_peer_table.h,v 3.16.2.1.2.3.6.2.4.2.8.1.4.1.2.1 2020/02/14 11:36:11 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_peer_table.h,v $
 *  LOG: Revision 3.16.2.1.2.3.6.2.4.2.8.1.4.1.2.1  2020/02/14 11:36:11  jkchaitanya
 *  LOG: TCP Timeout fix ported from DRE
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.2.4.2.8.1.4.1  2014/09/16 09:52:26  jsarvesh
 *  LOG: Chnages done for Peer wise Statistics enhancement
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.2.4.2.8.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.2.4.2  2013/10/26 07:42:21  ncshivakumar
 *  LOG: RFC 6733 changes
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.2.4.1  2013/09/10 08:36:39  ncshivakumar
 *  LOG: RFC6733 Changes
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.2  2013/02/25 13:16:37  mallikarjun
 *  LOG: Bug 623 changes
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3.6.1  2013/02/21 10:20:34  jkchaitanya
 *  LOG: Mar31 CMAPI Features
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.3  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.2.12.2  2012/11/17 04:31:35  millayaraja
 *  LOG: modified for peer stack stats
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.2.12.1  2012/11/14 08:28:18  millayaraja
 *  LOG: modified to accomdate Peer stack stats
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.2  2012/10/03 15:08:43  cprem
 *  LOG: Merged from ERLBF branch B-DRE-0212-02
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.1.2.1  2012/09/20 07:43:44  cprem
 *  LOG: Support for multiple dictionary id configuration per peer.
 *  LOG:
 *  LOG: Revision 3.16.2.1.2.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.16.2.1.4.3  2012/08/23 11:32:29  jvikas
 *  LOG: 1. Reading dictId from Peer Table Configuration
 *  LOG: 2. Calling BaseGenericCmd Destructor in DiaMsgFlow Destructor
 *  LOG: 3. Changed DictId ITS_UINT
 *  LOG: 4. Added HandleTransConfig
 *  LOG:
 *  LOG: Revision 3.16.2.1.4.2  2012/08/22 13:29:08  cashok
 *  LOG: Added Dictionary Id to xml configuration
 *  LOG:
 *  LOG: Revision 3.16.2.1.4.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.16.2.1  2012/07/10 08:34:40  ncshivakumar
 *  LOG: Updated code to send error code 3003 and 3010 in case of unknown realm and unknown peer respectively
 *  LOG:
 *  LOG: Revision 3.16  2011/07/14 14:08:47  vkumara
 *  LOG: ForceDisconnect Requirement - Not to initiate connection.
 *  LOG:
 *  LOG: Revision 3.15  2010/08/27 12:29:23  nvijikumar
 *  LOG: DSCP value support IP Header (Vasanth)
 *  LOG:
 *  LOG: Revision 3.14  2010/08/19 11:21:26  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 3.13  2009/10/14 10:32:14  sureshj
 *  LOG: forceDisconectPeer, support for new expiry timer value added
 *  LOG: to peer table( Motorola helpdesk ticket 2219).
 *  LOG:
 *  LOG: Revision 3.12  2009/07/01 11:22:23  nvijikumar
 *  LOG: Fix for RETRY timer issue (CER is not initiated properly)
 *  LOG:
 *  LOG: Revision 3.11  2009/04/13 13:41:36  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.10  2009/02/04 05:46:53  nvijikumar
 *  LOG: Changes to make Initiate Peer connections as configurable
 *  LOG:
 *  LOG: Revision 3.9  2009/01/03 06:52:42  nvijikumar
 *  LOG: TransportIndex related changes moved to dia_ip_trans.h
 *  LOG:
 *  LOG: Revision 3.8  2008/12/24 03:50:49  nvijikumar
 *  LOG: Initialize TrIndex with value "1"
 *  LOG:
 *  LOG: Revision 3.7  2008/12/23 14:41:33  ssaxena
 *  LOG: Provided API to GET/SET next trTable index
 *  LOG: Fix for Issue 1375
 *  LOG:
 *  LOG: Revision 3.6  2008/11/05 14:01:50  sureshj
 *  LOG: Release 3.1.1 feature
 *  LOG: Peer Connection Status Information
 *  LOG:
 *  LOG: Revision 3.5  2008/08/25 05:52:12  ssaxena
 *  LOG: 1. Failover / Failback indications to application
 *  LOG: 2. Failback is XML configurable option
 *  LOG:
 *  LOG: Revision 3.4  2008/06/13 11:18:47  hbhatnagar
 *  LOG: Made changes for the TLS implementation and also related xml parsing.
 *  LOG:
 *  LOG: Revision 3.3  2008/04/21 12:01:33  nanaparthi
 *  LOG: Fix for Issue #854 : Added isFailoverEnabled entry
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:16:17  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.11  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 2.10.4.2  2007/12/27 15:15:22  avinashks
 *  LOG: Changes made to fix issue no.2 (testcase No.1)
 *  LOG: raised during the validation of bcgi ticket 1807.
 *  LOG:
 *  LOG: Revision 2.10.4.1  2007/12/17 07:24:45  hbhatnagar
 *  LOG: removing the earlier boolean flag for DW and changing it with
 *  LOG: new integer dwa in PeerEntry structure. ( changes for the DW Transport
 *  LOG: Thread).
 *  LOG:
 *  LOG: Revision 2.10  2007/01/22 07:28:22  nanaparthi
 *  LOG: New entry isActive added to peertable
 *  LOG:
 *  LOG: Revision 2.9  2006/12/20 14:59:46  tpanda
 *  LOG: Other bug fixes related to redundancy(Issue#5075,5073,5069,5057 etc)
 *  LOG:
 *  LOG: Revision 2.8  2006/12/15 15:37:13  tpanda
 *  LOG: Disconnect peer problem in redundancy bug# 5068
 *  LOG:
 *  LOG: Revision 2.7  2006/12/10 13:43:48  tpanda
 *  LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 *  LOG:
 *  LOG: Revision 2.6  2006/11/24 03:50:33  nvijikumar
 *  LOG: Alternate peer lookup from hostname and realm (Failover).
 *  LOG:
 *  LOG: Revision 2.5  2006/11/22 10:51:46  nvijikumar
 *  LOG: Baseline PendingQ (Failover) changes.
 *  LOG:
 *  LOG: Revision 2.4  2006/10/12 14:01:41  yranade
 *  LOG: Add flag for dwPending.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/11 14:42:25  yranade
 *  LOG: CERCache is now of type BaseGenericCommand.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/05 13:00:22  yranade
 *  LOG: Getting there.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_peer_table.h,v 3.16.2.1.2.3.6.2.4.2.8.1.4.1.2.1 2020/02/14 11:36:11 jkchaitanya Exp $"

#if !defined DIA_PEER_TABLE_H_
#define DIA_PEER_TABLE_H_

#include <map>

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>

#include <dia_cmn.h>
#include <its_dia_config.h>
#include <dia_peer_fsm.h>
#include <dia_pending_q.h>
#include <dia_stack_statistics.h>
#define MAXSIZE 50
#define DEF_SOCK_FLUSH_TIMEOUT 2

typedef struct _trans_specs
{
    ITS_USHORT      trInst;
    ITS_HANDLE      trHandle;
    DIA_TRANS_INFO  tInfo;
}
PEER_TRANS_SPECS;

typedef struct connector_trans_specs
{
    ITS_USHORT      trInst;
    ITS_USHORT      trsnsCount;
    ITS_HANDLE      trHandle;
    ITS_USHORT      currentTinfoIndex;
    DIA_TRANS_INFO  tInfo[MAX_TRANS_PER_LIST];//Store max 4 transports
}
PEER_CONNECTOR_TRANS_SPECS;

typedef struct _peer_entry
{
    ITS_USHORT         trInst;
    ITS_USHORT         trIndex;
    ITS_HANDLE         trHandle;
    const char         *hostIdentity;
    const char         *realmName;
    ITS_BOOLEAN        isActive;
    ITS_BOOLEAN        isStatic;
    ITS_BOOLEAN        tlsEnabled;
    PEER_STATE         statusT;
    PEER_TRANS_SPECS   accSpecs;
    PEER_CONNECTOR_TRANS_SPECS   connSpecs;
    PeerFsm            *fsm;
    DIA_GEN_CMD        *ceCache;
    ITS_SERIAL         retry;
    ITS_UINT           retryTimeVal;
    ITS_SERIAL         expiry;
    ITS_UINT           expiryTimeVal;
    ITS_SERIAL         dw;
    ITS_UINT           dwTimeVal;
    ITS_MUTEX          wMutex;
    ITS_INT            dwaPending;
    PendingQ           *pendingQ;
    const char         *altHost;
    const char         *altRealmName;
    ITS_USHORT*        altTrInst;
    ITS_INT            disconectCause;
    bool               ifRedundantMate;
    bool               isFailoverEnabled;
    bool               isFailovered;
    bool               isFailbackEnabled;
    bool               isRelay;
    ITS_BOOLEAN        InbandSecIdMatch;
    time_t             connEstTime; 
    bool               initConnection;
    ITS_INT            initCoount;
    bool               isDiscovered;
    bool               isFirstCapabExchage;
    bool               isForceDisconnected;
    ITS_SERIAL         discoveryTimeout;
    ITS_BOOLEAN        dscpEnabled;
    ITS_INT            dscpVal;
    ITS_UINT           dictId[MAX_DICT_IDS_PER_PEER];
    ITS_INT            dictCount;
    DiaStackPeerStats  statsCounter;
    ITS_UINT busyReconnectTimerVal ;//Retry timer value need to be used in the case of disconnect cause is BUSY
    ITS_UINT doNotWantToTalkYouReconnectTimerVal; //retry timer value need to be used in the case of disconnect cause is  DO_NOT_WANT_TO_TALK_TO_YOU
    ITS_BOOLEAN isSupportDisconnectCause;//Supporting disconnect cause as mentioned in RFC6733 is enabled
    bool isRetransmissionEnabled;
    ITS_SERIAL         sockFlushTimer;  /* Timer in seconds */
    ITS_SERIAL         sockFlushTimerVal;  /* Timer in seconds */
    ITS_INT            sockFlushRetryCnt; /* -1 indicates infinite retry, 0 indicates don't retry, 'n' indicates retry cnt */
    ITS_INT            sockFlushCnt;      /* How many times retry is attempted */
    ITS_BOOLEAN        isCongIndGiven;
}
PEER_ENTRY;

#define DIA_PE_STATS(x) \
(((PEER_ENTRY *)(x))->statsCounter)

#define DIA_PE_TIME_TO_LIVE(x) \
(((PEER_ENTRY *)(x))->discoveryTimeout)

#define DIA_PEER_CHK_IF_REDUNDANT_MATE(x) \
(((PEER_ENTRY *)(x))->ifRedundantMate)

#define DIA_PEER_GET_DIS_CAUSE(x) \
(((PEER_ENTRY *)(x))->disconectCause)

#define DIA_PE_INST(x) \
(((PEER_ENTRY *)(x))->trInst)

#define DIA_PE_INDEX(x) \
(((PEER_ENTRY *)(x))->trIndex)

#define DIA_PE_HANDLE(x) \
(((PEER_ENTRY *)(x))->trHandle)

#define DIA_PE_HOST(x) \
(((PEER_ENTRY *)(x))->hostIdentity)

#define DIA_PE_REALM(x) \
(((PEER_ENTRY *)(x))->realmName)

#define DIA_PE_ACTIVE(x) \
(((PEER_ENTRY *)(x))->isActive)

#define DIA_PE_STATIC(x) \
(((PEER_ENTRY *)(x))->isStatic)

#define DIA_PE_TLS_EN(x) \
(((PEER_ENTRY *)(x))->tlsEnabled)

#define DIA_PE_STATE(x) \
(((PEER_ENTRY *)(x))->statusT)

#define DIA_PE_ACC_SPECS(x) \
(((PEER_ENTRY *)(x))->accSpecs)

#define DIA_PE_CONN_SPECS(x) \
(((PEER_ENTRY *)(x))->connSpecs)

#define DIA_PE_FSM(x) \
(((PEER_ENTRY *)(x))->fsm)

#define DIA_PE_CE_CACHE(x) \
(((PEER_ENTRY *)(x))->ceCache)

#define DIA_PE_RETRY_TIMER(x) \
(((PEER_ENTRY *)(x))->retry)

#define DIA_PE_RETRY_TIME_VAL(x) \
(((PEER_ENTRY *)(x))->retryTimeVal)

#define DIA_PE_EXPIRY_TIMER(x) \
(((PEER_ENTRY *)(x))->expiry)

#define DIA_PE_EXPIRY_TIME_VAL(x) \
(((PEER_ENTRY *)(x))->expiryTimeVal)

#define DIA_PE_DW_TIMER(x) \
(((PEER_ENTRY *)(x))->dw)

#define DIA_PE_DW_TIME_VAL(x) \
(((PEER_ENTRY *)(x))->dwTimeVal)

#define DIA_PE_MUX(x) \
(((PEER_ENTRY *)(x))->wMutex)

#define DIA_PE_CONN_TINFO(x) \
(((PEER_ENTRY *)(x))->connSpecs.tInfo[((PEER_ENTRY *)(x))->connSpecs.currentTinfoIndex])

#define DIA_PE_ACC_TINFO(x) \
(((PEER_ENTRY *)(x))->accSpecs.tInfo)

#define DIA_PE_DWA_PENDING(x) \
(((PEER_ENTRY *)(x))->dwaPending)

#define DIA_PE_PENDING_Q(x) \
(((PEER_ENTRY *)(x))->pendingQ)

#define DIA_PE_ALT_HOST(x) \
(((PEER_ENTRY *)(x))->altHost)

#define DIA_PE_ALT_REALM(x) \
(((PEER_ENTRY *)(x))->altRealmName)

#define DIA_PE_IS_RELAY(x) \
(((PEER_ENTRY *)(x))->isRelay)

#define DIA_PEER_CHK_IS_FAILOVER_ENABLED(x) \
(((PEER_ENTRY *)(x))->isFailoverEnabled)

#define DIA_PEER_CHK_IS_FAILOVERED(x) \
(((PEER_ENTRY *)(x))->isFailovered)
 
#define DIA_PEER_CHK_IS_FAILBACK_ENABLED(x) \
(((PEER_ENTRY *)(x))->isFailbackEnabled)

#define DIA_PE_IS_INBAND_SEC_MATCH(x) \
(((PEER_ENTRY *)(x))->InbandSecIdMatch)

#define DIA_PE_CONEST_TIME(x) \
(((PEER_ENTRY *)(x))->connEstTime)

#define DIA_PE_INIT_CONN(x) \
(((PEER_ENTRY *)(x))->initConnection)

#define DIA_PE_INIT_COUNT(x) \
(((PEER_ENTRY *)(x))->initCoount)

#define DIA_PE_IS_DISCOVERED(x) \
(((PEER_ENTRY *)(x))->isDiscovered)


#define DIA_PE_IS_FIRST_CAP_EXCH(x) \
(((PEER_ENTRY *)(x))->isFirstCapabExchage)

#define DIA_PE_DSCP_EN(x) \
(((PEER_ENTRY *)(x))->dscpEnabled)

#define DIA_PE_DSCP_VAL(x) \
(((PEER_ENTRY *)(x))->dscpVal)

#define DIA_PE_IS_FORCE_DISCONNECTED(x) \
(((PEER_ENTRY *)(x))->isForceDisconnected)

#define DIA_PE_DICTIONARY_ID(x, index) \
(((PEER_ENTRY *)(x))->dictId[index])

#define DIA_PE_BUSY_RECONNECT_TIMER(x) \
(((PEER_ENTRY *)(x))->busyReconnectTimerVal)

#define DIA_PE_DO_NOT_WANT_TO_TALK_TO_YOU_RECONNECT_TIMER(x) \
(((PEER_ENTRY *)(x))->doNotWantToTalkYouReconnectTimerVal)

#define DIA_PE_DISCONNECT_CAUSE_SUPPORT(x) \
(((PEER_ENTRY *)(x))->isSupportDisconnectCause)

#define DIA_PE_CONN_TRANS_COUNT(x) \
(((PEER_ENTRY *)(x))->connSpecs.trsnsCount)

#define DIA_PE_CONN_TINFO_INDEX(x,i) \
(((PEER_ENTRY *)(x))->connSpecs.tInfo[i])

#define DIA_PE_RETRANSMISSION_ENABLED(x) \
(((PEER_ENTRY *)(x))->isRetransmissionEnabled)

typedef struct _peer_state_ctxt
{
    ITS_UINT          evtType;
    PEER_ENTRY        *pEntry;
    diameter::Command *currCmd;
}
PEER_STATE_CTXT;


#define DIA_PEER_ST_ENTRY(x) \
(((PEER_STATE_CTXT *)(x))->pEntry)

#define DIA_PEER_ST_TRANS(x) \
((DiaSocketTransport *)(((PEER_STATE_CTXT *)(x))->pEntry->trHandle))

#define DIA_PEER_ST_EVT_TYPE(x) \
(((PEER_STATE_CTXT *)(x))->evtType)

#define DIA_PEER_ST_CURR_CMD(x) \
(((PEER_STATE_CTXT *)(x))->currCmd)

#define DIA_PEER_ST_FSM(x) \
(((PEER_STATE_CTXT *)(x))->pEntry->fsm)

#define DIA_PE_SOCK_FLUSH_TIMER(x) \
(((PEER_ENTRY *)(x))->sockFlushTimer)

#define DIA_PE_SOCK_FLUSH_TIMER_VAL(x) \
(((PEER_ENTRY *)(x))->sockFlushTimerVal)

#define DIA_PE_SOCK_FLUSH_RETRY_CNT(x) \
(((PEER_ENTRY *)(x))->sockFlushRetryCnt)

#define DIA_PE_SOCK_FLUSH_CNT(x) \
(((PEER_ENTRY *)(x))->sockFlushCnt)

#define DIA_PE_PEER_CONG_IND(x) \
(((PEER_ENTRY *)(x))->isCongIndGiven)

class PeerTable
{
public:
    static PeerTable *GetPeerTable();

    bool FindEntry(const char *hostIdentity, PEER_ENTRY *& entryParam);

    bool FindEntry(const char *hostIdentity,
                   const char *realmName,
                   PEER_ENTRY *& entryParam);
    //Tushar
    bool FindEntry(const char *hostIdentity,
                   const char *realmName,
                   PEER_ENTRY *& entryParam, ITS_USHORT& Instance);

    int InsertEntry(PEER_ENTRY *entryParam);

    int RemoveEntry(const char *hostIdentity);

    int RemoveEntry(const char *hostIdentity,
                    const char *realmName);

    static int StartTTLTimer(DIA_TIMER_TYPE type,
                      ITS_UINT duration,
                      PEER_ENTRY* &pEntry);

    static int StopTTLTimer(DIA_TIMER_TYPE type,
                      PEER_ENTRY *pEntry);

    PEER_ENTRY* FindFirstEntry();

    PEER_ENTRY* FindNextEntry(PEER_ENTRY *entryParam);

    static int StartTimer(DIA_TIMER_TYPE type, PEER_ENTRY *entry,int timerVal = 0);
    static int StopTimer(DIA_TIMER_TYPE type, PEER_ENTRY *entry);

    void DropAllPeers();

    void Print(std::ostream& os) const;
   
    
    void UpdateAltPeerInfo();
    //for redudancy, get alttrasport instance for backup peer
    ITS_USHORT GetAltTrInst(ITS_USHORT trInst);
    void ResetIsFailoveredFlag(PEER_ENTRY *entry);
    int GetCERFailureResultCode(const char *hostIdentity,const char *realmName);
    unsigned int GetPeerTableSize(void);

    void PrintPeerStats(std::ostream& os, std::string peer, std::string realm);
    void Print(std::ostream& oss, PEER_ENTRY *peer, std::string peerName);
private:
    typedef std::vector<PEER_ENTRY*>TypePeerList;
        
    TypePeerList peerList;

    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;
    ~PeerTable();

    PeerTable() {}

    PeerTable(PeerTable&) {}

    void Lock() const;

    void Unlock() const;
};

// PeerTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const PeerTable& table);

#define PEER_TABLE   PeerTable::GetPeerTable()

#endif
