/*********************************-*HPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_session_table.h,v $
 * LOG: Revision 3.12.14.1.4.2.4.2.12.2  2014/11/17 05:03:39  jkchaitanya
 * LOG: changes for HA Bug Fixes
 * LOG:
 * LOG: Revision 3.12.14.1.4.2.4.2.12.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.12.14.1.4.2.4.2  2014/01/06 09:22:32  cprem
 * LOG: Changes in diameter stack to support session replication. Review request 1611.
 * LOG:
 * LOG: Revision 3.12.14.1.4.2.4.1  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.12.14.1.4.2  2013/04/03 05:13:07  ncshivakumar
 * LOG: Added generation id required to check whether tracing is valid for current session
 * LOG:
 * LOG: Revision 3.12.14.1.4.1  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 3.12.14.1  2012/12/21 05:32:31  ncshivakumar
 * LOG: modified for Tracing
 * LOG:
 * LOG: Revision 3.12  2009/07/13 06:09:23  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.11  2009/06/29 14:49:07  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.10  2008/12/23 08:30:01  rajeshak
 * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
 * LOG: from dia_utils to dia_session_table
 * LOG:
 * LOG: Revision 3.9  2008/12/12 17:53:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.8  2008/11/13 11:51:11  ssaxena
 * LOG: Changed the define FTGroup from 0 to 1, for avoiding sessionDB
 * LOG: syncronization in case of redundancy.(Hemant)
 * LOG:
 * LOG: Revision 3.7  2008/10/31 05:38:31  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.6  2008/08/25 06:48:51  nvijikumar
 * LOG: Proper declaration of member funcs GetTableSize(), GetSessionTableSize()
 * LOG: PrintSessionTable()
 * LOG:
 * LOG: Revision 3.5  2008/08/21 06:07:08  yranade
 * LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
 * LOG:
 * LOG: Revision 3.4  2008/04/16 11:59:36  hbhatnagar
 * LOG: Made changes to include DestinationRealm in the Session Entry.
 * LOG: Also Added a new type in Message status enum.
 * LOG:
 * LOG: Revision 3.3  2008/04/07 17:25:44  hbhatnagar
 * LOG: Added a variable in session entry to determine the status of the message
 * LOG: in case of proxy. Also added the #defines for the same.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:14:26  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.12  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.10.4.1  2007/05/25 04:41:07  nvijikumar
 * LOG: Provided fun to restart the Auth timers only if timer AVP exists.
 * LOG:
 * LOG: Revision 2.10  2007/01/04 11:12:15  nvijikumar
 * LOG: added seperate fsmType and sState field in the context for Acct SM.
 * LOG:
 * LOG: Revision 2.9  2006/11/09 14:20:29  tpanda
 * LOG: clientId handling for IDS at the stack level
 * LOG:
 * LOG: Revision 2.8  2006/10/27 09:39:24  yranade
 * LOG: Added method to ReStart all AuthTimers.
 * LOG:
 * LOG: Revision 2.7  2006/10/16 06:30:21  yranade
 * LOG: Generate Client/Server Session Index. Will need update for redundancy.
 * LOG: Add API's to stop all timers.
 * LOG:
 * LOG: Revision 2.6  2006/10/09 11:30:23  yranade
 * LOG: Added LocalCache for SessionTable.
 * LOG:
 * LOG: Revision 2.5  2006/10/09 06:26:51  yranade
 * LOG: Timer related updates. Still to be finished.
 * LOG:
 * LOG: Revision 2.4  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/14 09:36:28  nvijikumar
 * LOG: Signature changes for Iterate function.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_session_table.h,v 3.12.14.1.4.2.4.2.12.2 2014/11/17 05:03:39 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_session_table.h,v 3.12.14.1.4.2.4.2.12.2 2014/11/17 05:03:39 jkchaitanya Exp $"

#ifndef DIA_SESSION_TABLE_H
#define DIA_SESSION_TABLE_H

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>                                                     

#include <dia_cmn.h> 
#include <its_dia_config.h>
#include <dia_timer_handler.h>

#define UNKNOWN_PEER_INST         0xFF
#define SESSION_TABLE_ID          0x52

// Changing session table FT Group for different redundancy scheme
#define SESSION_TABLE_FT_GROUP_ID 0x01

#define SESSION_DEST_REALM_MAX_SIZE    64

#define SESSION_STATE_TO_TEXT(x) \
    ((x==AUTH_SESSION_ST_IDLE)        ? "AUTH_SESSION_ST_IDLE"      : \
    ((x==AUTH_SESSION_ST_PENDING)     ? "AUTH_SESSION_ST_PENDING"   : \
    ((x==AUTH_SESSION_ST_OPEN)        ? "AUTH_SESSION_ST_OPEN"      : \
    ((x==AUTH_SESSION_ST_DISCON)      ? "AUTH_SESSION_ST_DISCON"    : \
    ((x==ACCT_SESSION_ST_IDLE)        ? "ACCT_SESSION_ST_IDLE"      : \
    ((x==ACCT_SESSION_ST_OPEN)        ? "ACCT_SESSION_ST_OPEN"      : \
    ((x==ACCT_SESSION_ST_PENDING_S)   ? "ACCT_SESSION_ST_PENDING_S" : \
    ((x==ACCT_SESSION_ST_PENDING_E)   ? "ACCT_SESSION_ST_PENDING_E" : \
    ((x==ACCT_SESSION_ST_PENDING_B)   ? "ACCT_SESSION_ST_PENDING_B" : \
    ((x==ACCT_SESSION_ST_PENDING_I)   ? "ACCT_SESSION_ST_PENDING_I" : \
    ((x==ACCT_SESSION_ST_PENDING_L)   ? "ACCT_SESSION_ST_PENDING_L" : \
    "INVALID")))))))))))


typedef enum
{
    AUTH_SESSION_ST_IDLE = 0,
    AUTH_SESSION_ST_PENDING,
    AUTH_SESSION_ST_OPEN,
    AUTH_SESSION_ST_DISCON,
    ACCT_SESSION_ST_IDLE,
    ACCT_SESSION_ST_OPEN,
    ACCT_SESSION_ST_PENDING_S,
    ACCT_SESSION_ST_PENDING_E,
    ACCT_SESSION_ST_PENDING_B,
    ACCT_SESSION_ST_PENDING_I,
    ACCT_SESSION_ST_PENDING_L,
    SESSION_ST_MAX
}SESSION_STATE;

typedef struct _authSessionTimers
{
    ITS_SERIAL   timeout;
    ITS_SERIAL   lifetime;
    ITS_SERIAL   gracePeriod;
    ITS_SERIAL   retryAbort;
    ITS_UINT     timeoutDuration;
    ITS_UINT     lifetimeDuration;
    ITS_UINT     gracePeriodDuration;
    ITS_UINT     retryAbortDuration;
}AUTH_SESS_TIMERS;

typedef struct _acctSessionTimers
{
    ITS_SERIAL  timeout;
    ITS_SERIAL  interim;
    ITS_SERIAL  realTime;
    ITS_UINT    timeoutDuration;
    ITS_UINT    interimDuration;
    ITS_UINT    realTimeDuration;
}ACCT_SESS_TIMERS;


/**
 * Only applies in the case of proxy.
 * enum to determine status of the message 
 */
typedef enum _its_dia_msg_status
{
    REQ_RCV_FROM_PEER = 0,
    WAIT_REQ_FROM_APP,
    WAIT_ANS_FROM_PEER,
    WAIT_ANS_FROM_APP,
    ANS_SND_TO_PEER
}
MSG_STATUS;


/**
 * Session Entry 
 */
typedef struct _sessionEntry
{
    ITS_UINT      sessIndx;
    ITS_UINT      clientId;       /* used by IDS */
    ITS_UINT      sType:1;       /* Session Type: Authorization or Accounting */
    ITS_UINT      evtType:7;
    ITS_UINT      fsmType:4;      /* FSM Type */
    ITS_UINT      accFsmType:4;   /* Acct FSM Type */
    ITS_UINT      sState:4;       /* FSM State */
    ITS_UINT      accState:4;     /* Acct FSM State */
    ITS_USHORT    peerInst;
    ITS_USHORT    peerInst2;      /* Only incase of Agents */
    ITS_UINT      appId;
    DIA_FLAGS     rxFlags;
    ITS_UINT      rxhh;
    ITS_UINT      localhh;        /* Only incase of Agents */
    ITS_UINT      rxee;
    bool          isAgent; 
    ITS_UINT      agentType:2;       /* whether relay, proxy or redirect*/
    MSG_STATUS    msgStatus:3;       /* in case of proxy, status of message*/

    ITS_USHORT    traceRuleId;      /* Rule id used for tracing */
    ITS_USHORT    generation;      /* Used to dentify Rule, need use along with traceRuleId*/
    ITS_UINT      resultCode;
    bool          pendingMsgs;
    /* 
     * Storing Destination Ream in session entry. Required 
     * for sending STR and ACR properly.
     */ 
    ITS_CHAR      destRealm[SESSION_DEST_REALM_MAX_SIZE]; 
    union
    {
        AUTH_SESS_TIMERS authTimers;
        ACCT_SESS_TIMERS acctTimers;
    }timers;
    bool          newlyReplicatedSession;
}SESSION_ENTRY;

//Function Pointers for Replication.
typedef int (*createSessionCbk)(std::string , SESSION_ENTRY*);
typedef int (*updateSessionCbk)(std::string , SESSION_ENTRY*);
typedef int (*deleteSessionCbk)(std::string );
typedef int (*fetchSessionCbk)(string , SESSION_ENTRY*);

#define DIA_SE_CLIENTID(x) \
(((SESSION_ENTRY*)(x))->clientId)

#define DIA_SE_SINDX(x) \
(((SESSION_ENTRY*)(x))->sessIndx)

#define DIA_SE_STYPE(x) \
(((SESSION_ENTRY*)(x))->sType)

#define DIA_SE_FSM_TYPE(x) \
(((SESSION_ENTRY*)(x))->fsmType)

#define DIA_SE_ACC_FSM_TYPE(x) \
(((SESSION_ENTRY*)(x))->accFsmType)

#define DIA_SE_STATE(x) \
(((SESSION_ENTRY*)(x))->sState)

#define DIA_SE_EVT_TYPE(x) \
(((SESSION_ENTRY*)(x))->evtType)

#define DIA_SE_PEER_INST(x) \
(((SESSION_ENTRY*)(x))->peerInst)

#define DIA_SE_PEER_INST_AGENT(x) \
(((SESSION_ENTRY*)(x))->peerInst2)

#define DIA_SE_APP_ID(x) \
(((SESSION_ENTRY*)(x))->appId)

#define DIA_SE_RX_FLAGS(x) \
(((SESSION_ENTRY*)(x))->rxFlags)

#define DIA_SE_RX_HH(x) \
(((SESSION_ENTRY*)(x))->rxhh)

#define DIA_SE_LOCAL_HH(x) \
(((SESSION_ENTRY*)(x))->localhh)

#define DIA_SE_RX_EE(x) \
(((SESSION_ENTRY*)(x))->rxee)

#define DIA_SE_AUTH_TIMERS(x) \
(((SESSION_ENTRY*)(x))->timers.authTimers)

#define DIA_SE_ACCT_TIMERS(x) \
(((SESSION_ENTRY*)(x))->timers.acctTimers)

#define DIA_SE_ACC_STATE(x) \
(((SESSION_ENTRY*)(x))->accState)

#define DIA_SE_IS_AGENT(x) \
(((SESSION_ENTRY*)(x))->isAgent)

#define DIA_SE_AGENT_TYPE(x) \
(((SESSION_ENTRY*)(x))->agentType)

#define DIA_SE_RESULT_CODE(x) \
(((SESSION_ENTRY*)(x))->resultCode)

#define DIA_SE_MSG_STATUS(x) \
(((SESSION_ENTRY*)(x))->msgStatus)

// Added for session tracing
#define DIA_SE_TRACE_RULE(x) \
(((SESSION_ENTRY*)(x))->traceRuleId)

#define DIA_SE_MESSAGES_PENDING(x) \
(((SESSION_ENTRY*)(x))->pendingMsgs)

/**
 * define added for destination realm
 */
#define DIA_SE_DEST_REALM(x) \
(((SESSION_ENTRY*)(x))->destRealm)

// Added for session tracing
#define DIA_SE_GENERATION(x) \
(((SESSION_ENTRY*)(x))->generation)

// For replication use in IWF
#define DIA_SE_NEWLY_REP_SESSION(x) \
(((SESSION_ENTRY*)(x))->newlyReplicatedSession)

/* Key To Index the Table is HostIdentity 
 */

class SessionTable
{
public:

    static SessionTable *GetSessionTable();

    static unsigned int GenerateSessionIndex(const char* ph);

    static int AllocateClientSessionIndex(unsigned int& sessId);

    static int AllocateServerSessionIndex(unsigned int& sessId);

    int InsertEntry(SESSION_ENTRY &sessionInfo, ITS_OCTET *key, ITS_UINT keyLen, bool replicateInsertion = true);

    int FindEntry(SESSION_ENTRY *&sessionInfo, ITS_OCTET *key, ITS_UINT keyLen);

    int RemoveEntry(SESSION_ENTRY *sessionInfo, ITS_OCTET *key, ITS_UINT keyLen);

    int ModifyEntry(SESSION_ENTRY *sessionInfo, ITS_OCTET *key, ITS_UINT keyLen);

    int StartTimer(const char *sessionId, DIA_TIMER_TYPE type, 
                   int duration, SESSION_ENTRY *entry);

    int StopTimer(DIA_TIMER_TYPE type, SESSION_ENTRY *entry);

    int StopAllAuthTimers(SESSION_ENTRY *entry);

    int StopAllAcctTimers(SESSION_ENTRY *entry);

    int ReStartAllAuthTimers(SESSION_ENTRY *entry, DIA_GEN_CMD *msg);

    int ReStartAllAuthTimers(SESSION_ENTRY *entry, DIA_BASE_CMD *msg);

    /*
     * Restart Auth timers only is timer AVPs exists.
     */
    int ReStartAuthTimers(SESSION_ENTRY *entry, DIA_GEN_CMD *msg);
    int ReStartAuthTimers(SESSION_ENTRY *entry, DIA_BASE_CMD *msg);

    void IterateTable(void *in, void *out, DSM_IterateEntryProc iterateFunc, int index);
    void IterateTable(void *in, void *out, DSM_IterateEntryProc iterateFunc);
    
    int InsertAcctSession(DIA_BASE_CMD *&cmd, const char* sessionId, 
                                SESSION_ENTRY*& ent, its::Event &ev, 
                                bool isStateless);

    int InsertAuthSession(DIA_BASE_CMD *&cmd, const char* sessionId, 
                                SESSION_ENTRY*& ent, its::Event &ev, 
                                bool isStateless);

    void Print(std::ostream& os);

    void PrintCache(std::ostream& os);

    int GetTableSize();
    int GetTableSize(int index);
    void Lock() const;

    void Unlock() const;

    /*
     * Replication callback pointers.
     */
    static createSessionCbk sessCreateCbk;
    static deleteSessionCbk sessDeleteCbk;
    static updateSessionCbk sessUpdateCbk;
    static fetchSessionCbk sessFetchCbk; 
    static bool replicateSessions;

private:
    SessionTable();
    ~SessionTable();
    SessionTable(const SessionTable&);            /* Prevent Copy Constructor */
    SessionTable& operator=(const SessionTable&); /* Prevent assignment */

    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;



    typedef std::map<ITS_UINT, SESSION_ENTRY*>SessionTableCache;
    SessionTableCache stCache;
};

// SessionTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, SessionTable& table);

#define SESSION_TABLE   SessionTable::GetSessionTable()


#endif
