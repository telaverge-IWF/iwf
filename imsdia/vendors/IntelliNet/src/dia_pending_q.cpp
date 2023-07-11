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
 *  ID: $Id: dia_pending_q.cpp,v 3.3.20.2.8.1.4.1.2.1.6.1 2014/12/18 04:32:42 jkchaitanya Exp $
 *
 *  LOG: $Log: dia_pending_q.cpp,v $
 *  LOG: Revision 3.3.20.2.8.1.4.1.2.1.6.1  2014/12/18 04:32:42  jkchaitanya
 *  LOG: changes for setting OriginHost as sgsn address and crash fix in stack for mandatory avp missing
 *  LOG:
 *  LOG: Revision 3.3.20.2.8.1.4.1.2.1  2014/07/02 06:37:11  millayaraja
 *  LOG: updated to handle answer message without mandatory field missing
 *  LOG:
 *  LOG: Revision 3.3.20.2.8.1.4.1  2014/05/12 05:48:52  millayaraja
 *  LOG: merged changes for Hop-By-Hop Id fix from B-DRE-0400-01-AICENT-POC branch
 *  LOG:
 *  LOG: Revision 3.3.20.2.8.1  2013/12/20 04:42:52  vsarath
 *  LOG: Fix for issue 2648
 *  LOG:
 *  LOG: Revision 3.3.20.2  2012/12/03 02:36:09  mallikarjun
 *  LOG: Bug-148-Alternate-Peer
 *  LOG:
 *  LOG: Revision 3.3.20.1  2012/09/06 11:30:46  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.3.22.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.3  2009/02/03 10:21:11  ssaxena
 *  LOG: Modifications done for Redirect Agent functionality.
 *  LOG:
 *  LOG: Revision 3.2  2008/12/12 18:30:47  rajeshak
 *  LOG: Lightweight Decode for base AVPS
 *  LOG: New Command class is introduced (BaseCommand)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.7  2008/03/27 12:14:08  hbhatnagar
 *  LOG: Converting 2.1 branch to CURRENT
 *  LOG:
 *  LOG: Revision 1.5.8.1  2007/05/25 12:25:46  nvijikumar
 *  LOG: Fix for PBN Bug ID: 5907, Map iterator increment issue on Solaris.
 *  LOG:
 *  LOG: Revision 1.5  2006/12/01 13:51:26  nvijikumar
 *  LOG: Fixes for Pending Queue issues.
 *  LOG: Set stopFailover flag, incase of Failback.
 *  LOG:
 *  LOG: Revision 1.4  2006/11/28 13:29:33  nvijikumar
 *  LOG: Failover and Multicasting clientId changes ( viji and kamakshi).
 *  LOG:
 *  LOG: Revision 1.3  2006/11/27 05:18:12  nvijikumar
 *  LOG: PopFirstEntry function ( just clear from the queue after retransmitt)
 *  LOG:
 *  LOG: Revision 1.2  2006/11/22 10:49:37  nvijikumar
 *  LOG: Baseline PendingQ ( Failover ) Changes.
 *  LOG:
 *  LOG: Revision 1.1  2006/10/06 09:26:34  yranade
 *  LOG: Baseline implementation for Pending Queue.
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_pending_q.cpp,v 3.3.20.2.8.1.4.1.2.1.6.1 2014/12/18 04:32:42 jkchaitanya Exp $"

#include <iomanip>

#include <stdlib.h>
#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>
#include <dia_pending_q.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
#endif


static void FreeEntry(DIA_BASE_CMD *cmdParam);

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
PrintEntry(std::ostream& os, DIA_BASE_CMD* cmd)
{
    os << "Hop-By-Hop = " << cmd->getHeader().hh << " End-to-End = " << cmd->getHeader().ee << " sessionID = " << cmd->getSessionId()->value() << endl;
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
PendingQ::PendingQ()
{
    lock = new its::Mutex(0);
    stopFailover = false;
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
PendingQ::~PendingQ()
{  
    Lock();

    for (TypeQPending::iterator iter = qPending.begin();
                                       iter != qPending.end();
                                       iter++)
    {
        DIA_BASE_CMD* cmd = (*iter).second.cmd;

        if (cmd != NULL)
        {
            FreeEntry(cmd);
        }
    }

    delete lock;
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
PendingQ::Lock() const
{
    int res = lock->Acquire();
    
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
PendingQ::Unlock() const
{
    int res = lock->Release();

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
PendingQ::FindEntry(unsigned int hopId)
{  
    bool found = false;

    Lock();
    TypeQPending::iterator iter = qPending.find(hopId);
    if(iter !=qPending.end())
    {
        found = true;
    }

    Unlock();

    return found;
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
DIA_BASE_CMD *
PendingQ::PopFirstEntry()
{
    Lock();
    DIA_BASE_CMD *cmd = NULL;
    TypeQPending::iterator iter = qPending.begin();
    if(iter !=qPending.end())
    {
        cmd = (*iter).second.cmd;
        qPending.erase(iter);
    }
    Unlock();
    return cmd;
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
DIA_BASE_CMD *
PendingQ::FindNextEntry(unsigned int &it)
{
    DIA_BASE_CMD *cmd = NULL;

    Lock();

    TypeQPending::iterator &iter = (TypeQPending::iterator &)it;

    if (iter !=qPending.end())
    {
        iter++;
        if (iter !=qPending.end())
        {
                cmd = (*iter).second.cmd;
        }
        else
        {
            qPending.clear();
        }
    }

    Unlock();

    return cmd;
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
DIA_BASE_CMD *
PendingQ::GetEntry(unsigned int hopId, bool eraseEntry)
{
    DIA_BASE_CMD *cmd = NULL;
 
    Lock();
    TypeQPending::iterator iter = qPending.find(hopId);
    if(iter !=qPending.end())
    {
        cmd = (*iter).second.cmd;
        DT_DBG(("Request found for hopByHopId recieved is: %d", hopId));
        if (eraseEntry)
        {
            qPending.erase(iter);
        }
    }
    Unlock();
 
    return cmd;
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
PendingQ::InsertEntry(DIA_GEN_CMD* cmdParam,ITS_SERIAL retransmissionTimer)
{
    Lock();

    ITS_REQUIRE(cmdParam != NULL);
   
    unsigned int hopId=cmdParam->getHeader().hh;
 
    if (FindEntry(hopId))
    {
        Unlock();
        return (ITS_EDUPLENTRY);
    }

    DIA_BASE_CMD* gCmd = new DIA_BASE_CMD(cmdParam);
    
    struct PendingQMsg pendingQMsg;
    pendingQMsg.retransmissionTimer = retransmissionTimer;
    pendingQMsg.cmd = gCmd;

    pair<TypeQPending::iterator, bool> insertRes =
        qPending.insert(TypeQPending::value_type(hopId, pendingQMsg));

    ITS_ENSURE(insertRes.second);

    Unlock();

    return (ITS_SUCCESS);
}

int
PendingQ::InsertEntry(DIA_BASE_CMD* cmdParam,ITS_SERIAL retransmissionTimer)
{
    Lock();

    ITS_REQUIRE(cmdParam != NULL);

    unsigned int hopId=cmdParam->getHeader().hh;

    if (FindEntry(hopId))
    {
        Unlock();
        return (ITS_EDUPLENTRY);
    }
    ITS_UINT  dictId = cmdParam->GetDictId();
    DIA_BASE_CMD* gCmd =  new DIA_BASE_CMD(cmdParam->GetBaseGenCommand(),true);
    gCmd->SetDictId(dictId);


    struct PendingQMsg pendingQMsg;
    pendingQMsg.retransmissionTimer = retransmissionTimer;
    pendingQMsg.cmd = gCmd;

    pair<TypeQPending::iterator, bool> insertRes =
        qPending.insert(TypeQPending::value_type(hopId, pendingQMsg));

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
FreeEntry(DIA_BASE_CMD *cmdParam)
{
    if (cmdParam)
    {
        delete(cmdParam);
        cmdParam = NULL;
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
int
PendingQ::RemoveEntry(unsigned int hopId)
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD *cmdParam = NULL;
    Lock();
    TypeQPending::iterator iter = qPending.find(hopId);

    if (iter != qPending.end())
    {
        cmdParam = (*iter).second.cmd;

        if (cmdParam != NULL)
        {
            FreeEntry(cmdParam);
        }
 
        qPending.erase(iter);

        Unlock();

        return ITS_SUCCESS;
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
int
PendingQ::CancelRetransmitTimerAndRemoveEntry(unsigned int hopId)
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD *cmdParam = NULL;
    Lock();
    TypeQPending::iterator iter = qPending.find(hopId);

    if (iter != qPending.end())
    {
        TIMERS_CancelTimer((*iter).second.retransmissionTimer);
        cmdParam = (*iter).second.cmd;

        if (cmdParam != NULL)
        {
            FreeEntry(cmdParam);
        }
 
        qPending.erase(iter);

        Unlock();

        return ITS_SUCCESS;
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
int
PendingQ::RemoveEntry(char *sessId)
{
    int ret = !ITS_SUCCESS;
    DIA_BASE_CMD *cmdParam = NULL;
    Lock();

   for (TypeQPending::iterator iter = qPending.begin();
                                       iter !=qPending.end();
                                       iter++)
    {
        cmdParam = (*iter).second.cmd;

        if (cmdParam)
        {
            if (strcmp(sessId, cmdParam->getSessionId()->value().c_str()) == 0)
            {
                FreeEntry(cmdParam);
                qPending.erase(iter);
                ret = ITS_SUCCESS;
                break;
            }
        }

    }

    Unlock();
    return ret;

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
PendingQ::RemoveAllEntry()
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD *cmdParam = NULL;
    Lock();

    for (TypeQPending::iterator iter = qPending.begin();
                                       iter !=qPending.end();)
    {
        cmdParam = (*iter).second.cmd;

        if (cmdParam && (cmdParam != NULL))
        {
            FreeEntry(cmdParam);
        }

        qPending.erase(iter);
        iter = qPending.begin();
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
PendingQ::CancelAllRetransmitTimerAndRemoveAllEntry()
{
    int ret = ITS_SUCCESS;
    DIA_BASE_CMD *cmdParam = NULL;
    Lock();

    for (TypeQPending::iterator iter = qPending.begin();
                                       iter !=qPending.end();)
    {
        cmdParam = (*iter).second.cmd;
        
        TIMERS_CancelTimer((*iter).second.retransmissionTimer);

        if (cmdParam && (cmdParam != NULL))
        {
            FreeEntry(cmdParam);
        }

        qPending.erase(iter);
        iter = qPending.begin();
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
void
PendingQ::Print(std::ostream& os) const
{
    Lock();

    os << "------------------------------------------------------------" << endl;
    os << "-- Pending Queue Begin --" << endl;
    os << "------------------------------------------------------------" << endl;
    os << endl;
    os << "Size: <" << qPending.size() << ">" << endl;
    os << endl;
    os << "Entries:" << endl;
    os << "--------------------------------------------------" << endl;

    TypeQPending::const_iterator iter = qPending.begin();

    bool hasEntry = false;

    while(iter != qPending.end())
    {
        hasEntry = true;

        ITS_ASSERT((*iter).second.cmd != NULL);

        DIA_BASE_CMD *cmd = (*iter).second.cmd;
        PrintEntry(os, cmd);

        os << "--------------------------------------------------" << endl;

        iter++;
    }

    if (!hasEntry)
    {
        os << "--------------------------------------------------" << endl;
    }

    os << "------------------------------------------------------------" << endl;
    os << "-- Pending Queue End --" << endl;
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
ostream&
operator<< (ostream& os, const PendingQ& table)
{
    table.Print(os);
    return os;
}
