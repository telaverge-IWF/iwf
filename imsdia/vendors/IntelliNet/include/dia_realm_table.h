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
 *  ID: $Id: dia_realm_table.h,v 3.9 2009/08/26 11:57:16 rajeshak Exp $
 *
 *  LOG: $Log: dia_realm_table.h,v $
 *  LOG: Revision 3.9  2009/08/26 11:57:16  rajeshak
 *  LOG: Fix for Issue:2328(IDS dumps core when trying to remove peer which
 *  LOG: is only destination in Realm)
 *  LOG: Fixed issue in RemoveAllDestination function.
 *  LOG:
 *  LOG: Revision 3.8  2009/08/13 11:43:59  rajeshak
 *  LOG: Inserting peers into realmEntry destination list based on priority
 *  LOG:
 *  LOG: Revision 3.7  2009/07/24 09:30:28  rajeshak
 *  LOG: Changes done for
 *  LOG:  1. new MML Command to print and remove default route
 *  LOG:  2. Stats changes (to include option to clear stats in get)
 *  LOG:
 *  LOG: Revision 3.6  2009/04/13 13:41:36  rajeshak
 *  LOG: Peer Discovery changes.
 *  LOG:
 *  LOG: Revision 3.5  2009/02/11 11:03:03  chandrashekharbs
 *  LOG: Fix for issue 1480
 *  LOG:
 *  LOG: Revision 3.4  2009/02/03 10:15:56  ssaxena
 *  LOG: Modifications done for Redirect Agent functionality.
 *  LOG:
 *  LOG: Revision 3.3  2009/01/28 06:47:59  chandrashekharbs
 *  LOG: Added FindFirstEntry API (used for xml persistency)
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 16:16:17  hbhatnagar
 *  LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.4  2006/12/17 03:35:58  tpanda
 *  LOG: Fix for bug# 5067 and default route handling
 *  LOG:
 *  LOG: Revision 2.3  2006/10/09 11:29:23  yranade
 *  LOG: Add API to get default entry per realm.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/09 06:25:50  yranade
 *  LOG: Increase no. of destinations per realm to 16.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 *  LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_realm_table.h,v 3.9 2009/08/26 11:57:16 rajeshak Exp $"

#if !defined DIA_REALM_TABLE_H_
#define DIA_REALM_TABLE_H_

#include <map>

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>

#include <its_dia_config.h>
#include <dia_peer_table.h>
#include <dia_peer_fsm.h>

typedef struct _dest_specs
{
    DIA_APPL_IDENTIFIER    appIdentifier;
    PEER_ENTRY             *peer;
    const char             *redirectHost;
    ITS_UINT               priority;
    bool                   isRedirectAgent;
}
REALM_DEST_SPECS;
    
typedef struct _realm_route_entry
{
    const char             *realmName;
    DIA_ROUTE_LOCAL_ACTION localAction;
    ITS_BOOLEAN            isDefault;
    ITS_BOOLEAN            isStatic;
    ITS_USHORT             destCnt;
    REALM_DEST_SPECS       destSpecs[MAX_LIST_SIZE];
    ITS_BOOLEAN            proxyInfoAvpEnabled;
    ITS_UINT               redirectUsage;
    ITS_UINT               redMaxCacheTime;
    ITS_BOOLEAN            isPeerDiscEnabled;
}
REALM_ENTRY;

#define DIA_RE_NAME(x) \
(((REALM_ENTRY *)(x))->realmName)

#define DIA_RE_L_ACTION(x) \
(((REALM_ENTRY *)(x))->localAction)

#define DIA_RE_IS_DEFAULT(x) \
(((REALM_ENTRY *)(x))->isDefault)

#define DIA_RE_IS_STATIC(x) \
(((REALM_ENTRY *)(x))->isStatic)

#define DIA_RE_DEST_CNT(x) \
(((REALM_ENTRY *)(x))->destCnt)

#define DIA_RE_DEST_APP_ID(x, i) \
(((REALM_ENTRY *)(x))->destSpecs[i].appIdentifier)

#define DIA_RE_DEST_PEER(x, i) \
(((REALM_ENTRY *)(x))->destSpecs[i].peer)

#define DIA_RE_DEST_PRIORITY(x, i) \
(((REALM_ENTRY *)(x))->destSpecs[i].priority)


#define DIA_RE_PXY_INFO_ENABLED(x) \
(((REALM_ENTRY *)(x))->proxyInfoAvpEnabled)

#define DIA_RE_REDIRECT_HOST(x, i) \
(((REALM_ENTRY *)(x))->destSpecs[i].redirectHost)
 
#define DIA_RE_REDIRECT_USAGE(x) \
(((REALM_ENTRY *)(x))->redirectUsage)
 
#define DIA_RE_REDIRECT_MAX_TIME(x) \
(((REALM_ENTRY *)(x))->redMaxCacheTime)

#define DIA_RE_DEST_IS_REDIRECT_AGENT(x) \
(((REALM_ENTRY *)(x))->destSpecs[0].isRedirectAgent)

#define DIA_RE_IS_PEER_DISC_ENABLE(x) \
(((REALM_ENTRY *)(x))->isPeerDiscEnabled)

class RealmTable
{
public:
    static RealmTable *GetRealmTable();

    bool FindDefaultEntry(const char *realmName, REALM_ENTRY *& entryParam);

    bool FindEntry(const char *realmName, REALM_ENTRY *& entryParam);
   
    REALM_ENTRY* FindFirstEntry();

    REALM_ENTRY* FindNextEntry(ITS_INT count);

    REALM_ENTRY* FindNextEntry(REALM_ENTRY *entryParam);

    REALM_ENTRY* FindDefaultEntry(REALM_ENTRY *& entryParam);
    int InsertEntry(REALM_ENTRY *entryParam);

    int FindRealmCount();

    int RemoveEntry(const char *realmName);

    int RemoveDefaultEntry();
   
    int RemoveAllDestination(PEER_ENTRY *pEntry);

    void Print(std::ostream& os) const;

    static int RemoveDestination(REALM_ENTRY *rEntry, 
                                  PEER_ENTRY *pEntry);
 
    static int InsertDestination(REALM_ENTRY *rEntry, 
                                 PEER_ENTRY *pEntry, 
                                 int appId, int vendId, 
                                 int prio);
private:
    typedef std::map<const char*, REALM_ENTRY*>TypeTableRealm;
        
    TypeTableRealm tableRealm;

    static its::ITS_Mutex lock;
    static its::ITS_Mutex guard;

    RealmTable() 
    {
        defaultRealmEntry = NULL;
    };

    ~RealmTable();

    RealmTable(RealmTable&) {};

    void Lock() const;

    void Unlock() const;
    REALM_ENTRY* defaultRealmEntry;
};

// PeerTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const RealmTable& table);

#define REALM_TABLE RealmTable::GetRealmTable()

#endif
