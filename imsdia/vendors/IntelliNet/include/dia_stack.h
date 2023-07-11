/********************************-*HPP*-*************************************
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
 *  
 *  LOG: $Log: dia_stack.h,v $
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2.2.3.8.1.2.1  2014/10/27 08:28:39  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2.2.3.8.1  2014/08/26 10:24:47  pramana
 *  LOG: Logging related refinements
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2.2.3  2014/01/06 09:22:32  cprem
 *  LOG: Changes in diameter stack to support session replication. Review request 1611.
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2.2.2  2013/12/13 09:34:58  vsarath
 *  LOG: Merged the session-splict changes
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2.2.1  2013/07/15 06:33:08  jvikram
 *  LOG: Fixed crash during service restart
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.2  2013/07/04 10:47:29  ncshivakumar
 *  LOG: Updated for TPS based licensing
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4.2.1  2013/06/10 09:37:13  cprem
 *  LOG: Review request 1016.
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.4  2013/04/10 05:41:19  mallikarjun
 *  LOG: TLS initilisation Chages bug 1363
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.3  2013/04/07 09:44:47  cprem
 *  LOG: Commented unused code
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.2  2013/04/07 03:54:21  cprem
 *  LOG: Changes made to fix HA bugs. Review Request 784
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6.6.1  2013/03/22 06:33:33  pramana
 *  LOG: Changes for HA feature
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.6  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.2.12.2  2012/11/20 10:28:35  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.2  2012/10/03 15:08:43  cprem
 *  LOG: Merged from ERLBF branch B-DRE-0212-02
 *  LOG:
 *  LOG: Revision 3.5.12.1.2.1.2.1  2012/09/20 07:44:14  cprem
 *  LOG: New method to validatePeer Dictionaries is added.
 *  LOG:
 *  w
 *  LOG: Revision 3.5.12.1.2.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.5.12.1.4.2  2012/08/24 07:40:43  jvikas
 *  LOG: Fixed Compilation Issue for Rule Engine.
 *  LOG:
 *  LOG: Revision 3.5.12.1.4.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.5.12.1  2012/03/07 13:23:08  brajappa
 *  LOG: Changes made for the DRE demo
 *  LOG:
 *  LOG: Revision 3.5  2009/07/13 06:09:23  rajeshak
 *  LOG: Reverting back session table changes.
 *  LOG:
 *  LOG: Revision 3.4  2009/06/29 14:49:07  rajeshak
 *  LOG: Changes done for performance enhancement (splitting the session table).
 *  LOG:
 *  LOG: Revision 3.3  2008/10/31 05:38:31  nvijikumar
 *  LOG: IssueID:1189
 *  LOG: FeatureID: none
 *  LOG: Description: 1. Introducing additional TQs and Threads for better
 *  LOG:                 Performance on PP50 and initial stack tunning
 *  LOG:              2. Unwanted code cleanup
 *  LOG:
 *  LOG: Revision 3.2  2008/08/21 06:07:08  yranade
 *  LOG: Added APIs to print QSize, SessionTable size and SessionTable details.
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.11  2006/12/15 12:37:20  tpanda
 *  LOG: Redundancy Config-Callback added,state change events to App via this function
 *  LOG:
 *  LOG: Revision 2.10  2006/12/11 11:50:09  tpanda
 *  LOG: Minor changes to the Node state change callback function
 *  LOG:
 *  LOG: Revision 2.9  2006/12/11 11:41:04  tpanda
 *  LOG: Fix for standby node not handling transaction when peer gcs down(bug#4960)
 *  LOG:
 *  LOG: Revision 2.8  2006/11/25 04:00:12  tpanda
 *  LOG: Changes for Msg based redundancy
 *  LOG:
 *  LOG: Revision 2.7  2006/10/31 07:48:01  hbhatnagar
 *  LOG: ReleaseSession API made static
 *  LOG:
 *  LOG: Revision 2.6  2006/10/28 12:26:23  yranade
 *  LOG: Added ReleaseSession API to provide a hook for an application to
 *  LOG: clear session from sessionDb. May need revisit (to make it asynchronous)
 *  LOG:
 *  LOG: Revision 2.5  2006/10/24 14:24:41  yranade
 *  LOG: 1. RegisterWithAppId now takes AppId type.
 *  LOG: 2. Start(): No configFile argument needed.
 *  LOG: 3. Reorganize Initialization a bit, while sending message check if appId
 *  LOG: is registered.
 *  LOG:
 *  LOG: Revision 2.4  2006/10/13 16:38:54  yranade
 *  LOG: API updates.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/07 12:24:55  yranade
 *  LOG: Today's round of updates.
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

#ifndef DIA_STACK_H_
#define DIA_STACK_H_

#include <dia_defines.h>
#include <its.h>

#include <diameter/Command.h>

//Added for DTF
#include <Sync.h>
#include <PluginObj.h>
#include <DiameterTransformer.h>
#include <DiameterDictionary.h>
#include <DictionaryTable.h>
#include <dtf.h>
////End of DTF addition
#include <dia_acceptor.h>
#include <dia_connector.h>
#include <dia_rate_filter.h>
#include <dia_session_table.h>                

#define MASTER_CA "MasterCA.pem"

#define DIA_STACK_MAX_ACCEPTORS 32

class DiaStackClass
{
public:
    DiaStackClass();

    ~DiaStackClass();

    unsigned int RegisterWithAppId(unsigned int id, unsigned int type = 0);

    //int Start();

    int Start(bool activateStack=true);
    //int Start(bool initLocalTransports, bool initPeerTransports);

    inline bool isStarted(){return started;}

    int SendMsgToPeer(const diameter::Command* mesg, unsigned int sessionIndex,
                      ITS_USHORT toPeer = 0xFF, ITS_UINT flags = 0);

    int SendMsgToPeer(const diameter::Command* mesg);

    int SendMsgToPeer(const DIA_BASE_CMD* mesg, unsigned int sessionInd,
                             ITS_USHORT toPeer, ITS_UINT flags);
    int SendAuthRequestToPeer(diameter::Command& mesg);

    int SendAuthSuccToPeer(diameter::Command& mesg);

    //returns session index, error value 0xFFFFFFFF
    int AllocateSession(unsigned int appId, unsigned int& sessIdx,
                        std::string& sessIdString);

    void ReleaseClientSession(unsigned int sessId);

    static int ReleaseSession(const char* sessionId);

    static int GetDiaStackQCount();

    static int GetDiaStackQCount(int index);

    static int GetMsgRouterThreadCount();

    static int GetDiaStackSenderQCount();

    static diameter::DTF& GetDtf();

    static diameter::DictionaryTable& GetDictionaryTable();

    int InitLocalTransports(bool activateStack = true);

    int InitPeerTransports(bool activateStack = true);

    int TermTransports(bool cleanUpSockets = false);

    //int TermLocalTransports();

    int GoActive();

    int GoStandby();

    void Terminate();
   
    int InitTLS();

    int enableReplication();

    int disableReplication();

    int registerCreateSessionReplicationCbk(createSessionCbk );

    int registerUpdateSessionReplicationCbk(updateSessionCbk );

    int registerDeleteSessionReplicationCbk(deleteSessionCbk );
    
    int registerFetchSessionReplicaCbk(fetchSessionCbk );

    static inline void EnableInterfaceStats(bool enableStats = false)
    {
        m_interfaceStatsEnabled = enableStats;
    }

    static inline bool InterfaceStatsEnabled() {return m_interfaceStatsEnabled;}

    int ReCreateSessionEntry(string& sessionId, ITS_EVENT& event);

protected:
    bool started;
    static its::ITS_Mutex guard;
    static diameter::DTF mDtf;
    static diameter::DictionaryTable mDictTable;
    int InitDictionaryTable();
    int InitTransformationTable();
	int ValidatePeerDictionaries();

    int ActivateTransportThreads();

    int DeActivateTransportThreads();

    int StopAcceptors();
    int StopConnectors();
    int StopWatchdog();

    int numAcceptor;
    DiaConnector *connector;
    DiaConnectorReader *connReader;
    DiaAcceptor *acceptor[DIA_STACK_MAX_ACCEPTORS];
    DiaAcceptorReader *accReader[DIA_STACK_MAX_ACCEPTORS];
private:
    TokenUpdateThread *m_tokenUpdateThread;
    eAccelero::Thread *m_startTokenThread; 
    static bool m_interfaceStatsEnabled;

};

#if defined(__cplusplus)
extern "C"
{
#endif

ITSSS7DLLAPI void NodeStateChangeCallback(ITS_POINTER object,ITS_POINTER userData,ITS_POINTER callData);

ITSSS7DLLAPI void RedundancyConfigCallback(ITS_POINTER ptr, ITS_POINTER ptr1, ITS_POINTER evt);

#if defined(__cplusplus)
}
#endif

#endif
