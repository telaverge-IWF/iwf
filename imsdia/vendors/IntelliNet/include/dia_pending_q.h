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
 *  ID: $Id: dia_pending_q.h,v 3.3.20.1.42.1.6.1 2014/12/18 04:32:42 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_pending_q.h,v $
 *  LOG: Revision 3.3.20.1.42.1.6.1  2014/12/18 04:32:42  jkchaitanya
 *  LOG: changes for setting OriginHost as sgsn address and crash fix in stack for mandatory avp missing
 *  LOG:
 *  LOG: Revision 3.3.20.1.42.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.3.20.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.3.22.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.3  2009/02/03 10:15:56  ssaxena
 *  LOG: Modifications done for Redirect Agent functionality.
 *  LOG:
 *  LOG: Revision 3.2  2008/12/12 17:53:08  rajeshak
 *  LOG: Lightweight Decode for base AVPS
 *  LOG: New Command class is introduced (BaseCommand)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.5  2006/12/01 13:53:59  nvijikumar
 *  LOG: Fixes for Pending Queue issues.
 *  LOG: Set stopFailover flag, incase of Failback.
 *  LOG:
 *  LOG: Revision 1.4  2006/11/27 05:19:35  nvijikumar
 *  LOG: PopFirstEntry function ( just clear from the queue after retransmitt).
 *  LOG:
 *  LOG: Revision 1.3  2006/11/22 10:51:46  nvijikumar
 *  LOG: Baseline PendingQ (Failover) changes.
 *  LOG:
 *  LOG: Revision 1.2  2006/10/07 12:55:00  yranade
 *  LOG: Singleton class.
 *  LOG:
 *  LOG: Revision 1.1  2006/10/06 09:25:21  yranade
 *  LOG: Baseline implementation for pending Queue.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_pending_q.h,v 3.3.20.1.42.1.6.1 2014/12/18 04:32:42 jkchaitanya Exp $"

#if !defined DIA_PENDING_Q_H_
#define DIA_PENDING_Q_H_

#include <map>

#include <its_types.h>
#include <its_mutex.h>
#include <its_timers.h>

#include <dia_cmn.h>
#include "dia_msg_flow.h"

//Struct contains dia base cmd and serial number 
//to stop the timer
struct PendingQMsg
{
    ITS_SERIAL retransmissionTimer;
    DIA_BASE_CMD* cmd;
};


class PendingQ
{
public:
    bool FindEntry(unsigned int hopId);

    DIA_BASE_CMD*  PopFirstEntry();

    DIA_BASE_CMD*  FindNextEntry(unsigned int &it);

    DIA_BASE_CMD*  GetEntry(unsigned int hopId, bool eraseEntry = true);
    
    int InsertEntry(DIA_BASE_CMD *cmdParam,ITS_SERIAL retransmissionTimer);

    int InsertEntry(DIA_GEN_CMD *cmdParam,ITS_SERIAL retransmissionTimer);

    int RemoveEntry(unsigned int hopId);

    int RemoveEntry(char *sessId);

    int RemoveAllEntry();

    void Print(std::ostream& os) const;

    int CancelRetransmitTimerAndRemoveEntry(unsigned int hopId);
    
    int CancelAllRetransmitTimerAndRemoveAllEntry();

    PendingQ();

    ~PendingQ();
   
    bool IsStopFailover() { return stopFailover; }

    void SetStopFailover(bool sFailover) { stopFailover = sFailover; }

private:

    //typedef std::map<unsigned int, DIA_BASE_CMD*>TypeQPending;
    typedef std::map<unsigned int, struct PendingQMsg>TypeQPending;
        
    TypeQPending qPending;

    its::ITS_Mutex *lock;

    bool stopFailover;

    void Lock() const;

    void Unlock() const;
};

// PeerTable ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const PendingQ& pQueue);

#endif
