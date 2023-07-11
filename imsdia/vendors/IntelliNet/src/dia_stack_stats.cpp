/*******************************-*CPP-*-*************************************
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
 *  ID: $Id: dia_stack_stats.cpp,v 1.9.42.1 2013/02/19 11:05:57 jsarvesh Exp $
 *  
 *  LOG: $Log: dia_stack_stats.cpp,v $
 *  LOG: Revision 1.9.42.1  2013/02/19 11:05:57  jsarvesh
 *  LOG: dre global stats implementation
 *  LOG:
 *  LOG: Revision 1.9  2010/10/11 05:10:21  nvijikumar
 *  LOG: Motorola's changes incorporation for field compilation issue
 *  LOG:
 *  LOG: Revision 1.8  2009/07/27 09:12:51  rajeshak
 *  LOG: Locking before stats reset.
 *  LOG:
 *  LOG: Revision 1.7  2009/07/24 09:25:25  rajeshak
 *  LOG: Added Reset function for different statistics.
 *  LOG:
 *  LOG: Revision 1.6  2009/03/26 05:35:09  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 1.5  2009/03/02 04:43:52  nvijikumar
 *  LOG: Enhancements for MML API Support
 *  LOG:
 *  LOG: Revision 1.4  2009/01/07 13:10:32  nvijikumar
 *  LOG: Adding Mutex to make it thread safe
 *  LOG:
 *  LOG: Revision 1.3  2008/12/22 06:26:02  sureshj
 *  LOG: Reset Error message statistics.
 *  LOG:
 *  LOG: Revision 1.2  2008/12/12 12:30:01  nvijikumar
 *  LOG: More updates
 *  LOG:
 *  LOG: Revision 1.1  2008/12/12 07:51:38  nvijikumar
 *  LOG: Initial draft for Stack Statistics support (Suresh)
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: dia_stack_stats.cpp,v 1.9.42.1 2013/02/19 11:05:57 jsarvesh Exp $"

#include <dia_stack_stats.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <dia_peer_table.h>
#include <iomanip>
using namespace std;
using namespace its;

its::ITS_Mutex DiaStackStats::guardDS(0);
its::ITS_Mutex DiaStackStats::guardUS(0);
bool isStackStatsEnabled = true;

void
DiaStackStats::LockDS() const
{
    int res = const_cast<ITS_Mutex&>(guardDS).Acquire();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

void
DiaStackStats::UnlockDS() const
{
    int res = const_cast<ITS_Mutex&>(guardDS).Release();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}
void
DiaStackStats::LockUS() const
{
    int res = const_cast<ITS_Mutex&>(guardUS).Acquire();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}

void
DiaStackStats::UnlockUS() const
{
    int res = const_cast<ITS_Mutex&>(guardUS).Release();

    if (res != ITS_SUCCESS)
    {
        ITS_THROW_ERROR(res);
    }
}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function resets the statistics data.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DiaStackStats::ResetAll()
{
    LockUS();
    LockDS();

    memset(&as, 0, sizeof(DIA_CMD_STATS));
    memset(&ac, 0, sizeof(DIA_CMD_STATS));
    memset(&ce, 0, sizeof(DIA_CMD_STATS));
    memset(&dw, 0, sizeof(DIA_CMD_STATS));
    memset(&dp, 0, sizeof(DIA_CMD_STATS));
    memset(&st, 0, sizeof(DIA_CMD_STATS));
    memset(&ra, 0, sizeof(DIA_CMD_STATS));
    memset(&app, 0, sizeof(DIA_CMD_STATS));
    memset(&err, 0, sizeof(DIA_CMD_STATS));
    memset(&totalSessionBased, 0, sizeof(DIA_CMD_STATS));
    memset(&totalPeerBased, 0, sizeof(DIA_CMD_STATS));
    memset(&diaIndcStats, 0, sizeof(DIA_INDIC_STATS));
    memset(&diaMiscStats, 0, DIA_MAX_MISC_STATS*sizeof(ITS_UINT));
    totalMsgOut = 0;
    totalMsgIn = 0;

    UnlockDS();
    UnlockUS();
}

void 
DiaStackStats::UpdateReqInStats(ITS_UINT cmdCode)
{
    LockUS();
    switch(cmdCode)
    {
    case DIA_MSG_CE:
         ce.reqIn++;
         totalPeerBased.reqIn++;
         break;
    case DIA_MSG_DW:
         dw.reqIn++;
         totalPeerBased.reqIn++;
         break;
    case DIA_MSG_DP:
         dp.reqIn++;
         totalPeerBased.reqIn++;
         break;
    case DIA_MSG_AC:
         ac.reqIn++;
         totalSessionBased.reqIn++;
         break;
    case DIA_MSG_RA:
         ra.reqIn++;
         totalSessionBased.reqIn++;
         break;
    case DIA_MSG_ST:
         st.reqIn++;
         totalSessionBased.reqIn++;
         break;
    case DIA_MSG_AS:
         as.reqIn++;
         totalSessionBased.reqIn++;
         break;
    default:
         app.reqIn++;
         totalSessionBased.reqIn++;
         break;
    }
    totalMsgIn++;
   UnlockUS();
}

void
DiaStackStats::UpdateReqOutStats(ITS_UINT cmdCode)
{
    LockDS();
    switch(cmdCode)
    {
    case DIA_MSG_CE:
         ce.reqOut++;
         totalPeerBased.reqOut++;
         break;
    case DIA_MSG_DW:
         dw.reqOut++;
         totalPeerBased.reqOut++;
         break;
    case DIA_MSG_DP:
         dp.reqOut++;
         totalPeerBased.reqOut++;
         break;
    case DIA_MSG_AC:
         ac.reqOut++;
         totalSessionBased.reqOut++;
         break;
    case DIA_MSG_RA:
         ra.reqOut++;
         totalSessionBased.reqOut++;
         break;
    case DIA_MSG_ST:
         st.reqOut++;
         totalSessionBased.reqOut++;
         break;
    case DIA_MSG_AS:
         as.reqOut++;
         totalSessionBased.reqOut++;
         break;
    default:
         app.reqOut++;
         totalSessionBased.reqOut++;
         break;
    }
    totalMsgOut++;
    UnlockDS(); 
}

void               
DiaStackStats::UpdateAnsInStats(ITS_UINT cmdCode)
{
    LockUS();
    switch(cmdCode)
    {
    case DIA_MSG_CE:
         ce.ansIn++;
         totalPeerBased.ansIn++;
         break;
    case DIA_MSG_DW:
         dw.ansIn++;
         totalPeerBased.ansIn++;
         break;
    case DIA_MSG_DP:
         dp.ansIn++;
         totalPeerBased.ansIn++;
         break;
    case DIA_MSG_AC:
         ac.ansIn++;
         totalSessionBased.ansIn++;
         break;
    case DIA_MSG_RA:
         ra.ansIn++;
         totalSessionBased.ansIn++;
         break;
    case DIA_MSG_ST:
         st.ansIn++;
         totalSessionBased.ansIn++;
         break;
    case DIA_MSG_AS:
         as.ansIn++;
         totalSessionBased.ansIn++;
         break;
    default:
         app.ansIn++;
         totalSessionBased.ansIn++;
         break;
    }
    totalMsgIn++;
   UnlockUS(); 
}

void
DiaStackStats::UpdateAnsOutStats(ITS_UINT cmdCode)
{
    LockDS();
    switch(cmdCode)
    {
    case DIA_MSG_CE:
         ce.ansOut++;
         totalPeerBased.ansOut++;
         break;
    case DIA_MSG_DW:
         dw.ansOut++;
         totalPeerBased.ansOut++;
         break;
    case DIA_MSG_DP:
         dp.ansOut++;
         totalPeerBased.ansOut++;
         break;
    case DIA_MSG_AC:
         ac.ansOut++;
         totalSessionBased.ansOut++;
         break;
    case DIA_MSG_RA:
         ra.ansOut++;
         totalSessionBased.ansOut++;
         break;
    case DIA_MSG_ST:
         st.ansOut++;
         totalSessionBased.ansOut++;
         break;
    case DIA_MSG_AS:
         as.ansOut++;
         totalSessionBased.ansOut++;
         break;
   default:
         app.ansOut++;
         totalSessionBased.ansOut++;
         break;
    }
    totalMsgOut++;
   UnlockDS(); 
}
void
DiaStackStats::UpdateErrSessionAnsOutStats()
{
    LockDS();
    err.ansOut++;
    totalSessionBased.ansOut++;
    totalMsgOut++;
    UnlockDS();
}

void
DiaStackStats::UpdateErrSessionAnsInStats()
{
    LockUS();
    err.ansIn++;
    totalSessionBased.ansIn++;
    totalMsgIn++;
    UnlockUS();
}

void
DiaStackStats::UpdateDecodeFailureStats()
{
    LockUS();
    decodeFailure++;
    UnlockUS();
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function updates the indications received
 *      from the diameter stack.
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
 *      None
 *
 *  Notes:
 *      Not Thread Safe: To make it so, use it with Lock()/Unlock()
 *  See Also:
 ****************************************************************************/
void
DiaStackStats::UpdateIndicStats(ITS_UINT ind)
{
    LockUS();
    switch (ind)
    {
    case DISCONECT_IND_FROM_STACK:
        diaIndcStats.numDisconnInd++;
        break;
    case TIME_OUT_IND_FROM_STACK:
        diaIndcStats.numSessTimeoutInd++;
        break;
    case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
        diaIndcStats.numAuthLifeTimeoutInd++;
        break;
    case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
        diaIndcStats.numAuthGraceTimeoutInd++;
        break;
    case ABORT_IND_FROM_STACK:
        diaIndcStats.numAbortInd++;
        break;
    case CORRUPTED_MSG_IND_FROM_STACK:
        diaIndcStats.numCorruptMsgInd++;
        break;
    case FAILOVER_IND_FROM_STACK:
        diaIndcStats.numFailOverInd++;
        break;
    case FAILBACK_IND_FROM_STACK:
        diaIndcStats.numFailBackInd++;
        break;
    default:
        diaIndcStats.numUnknownInd++;
        break;
    }
    UnlockUS();
}

void 
DiaStackStats::UpdateMiscStats(DIA_MISC_STATS miscStats)
{
    diaMiscStats[miscStats]++;
}

int 
DiaStackStats::GetDiaIndStats(DIA_INDIC_STATS *indStats)
{
    if (indStats == NULL)
    {
        return !ITS_SUCCESS;
    }
    memcpy(indStats, &diaIndcStats, sizeof(DIA_INDIC_STATS));
    return ITS_SUCCESS;
}

int 
DiaStackStats::GetDiaSessStats(DIA_SESS_STATS *sessStats)
{
    if (sessStats  == NULL)
    {
        return !ITS_SUCCESS;
    }
    memcpy(&sessStats->app, &app, sizeof(DIA_CMD_STATS));
    memcpy(&sessStats->ac, &ac, sizeof(DIA_CMD_STATS));
    memcpy(&sessStats->as, &as, sizeof(DIA_CMD_STATS));
    memcpy(&sessStats->ra, &ra, sizeof(DIA_CMD_STATS));
    memcpy(&sessStats->st, &st, sizeof(DIA_CMD_STATS));
    memcpy(&sessStats->err, &err, sizeof(DIA_CMD_STATS));
    sessStats->decodeFailure = decodeFailure;
    return ITS_SUCCESS;
}
int 
DiaStackStats::GetDiaPeerStats(DIA_PEER_STATS *peerStats)
{
    if (peerStats  == NULL)
    {
        return !ITS_SUCCESS;
    }
    memcpy(&peerStats->total, &totalPeerBased, sizeof(DIA_CMD_STATS));
    memcpy(&peerStats->ce, &ce, sizeof(DIA_CMD_STATS));
    memcpy(&peerStats->dw, &dw, sizeof(DIA_CMD_STATS));
    memcpy(&peerStats->dp, &dp, sizeof(DIA_CMD_STATS));
    return ITS_SUCCESS;
}

void
DiaStackStats::ResetPeerStats()
{
    LockUS();
    LockDS();

    memset(&totalPeerBased, 0, sizeof(DIA_CMD_STATS));
    memset(&ce, 0, sizeof(DIA_CMD_STATS));
    memset(&dw, 0, sizeof(DIA_CMD_STATS));
    memset(&dp, 0, sizeof(DIA_CMD_STATS));

    UnlockDS();
    UnlockUS();
}
 
void
DiaStackStats::PrintPeerStats(std::ostream& os) const
{
    char tbuf[ITS_PATH_MAX];
    time_t local;
 
    time(&local);
#if defined (__SUNPRO_CC)
    ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
    ctime_r(&local, tbuf);
#endif
 
    os << "-----------------------------------------------------------"
       << endl;    os << "-- Dia Peer Stats -- at " << tbuf;
    os << "-----------------------------------------------------------"
       << endl;
    os<<"    Message           : ReqIn   | ReqOut | AnsIn  | AnsOut |"
       <<endl;
    os << "-----------------------------------------------------------"
       << endl;

    os << "Capabilities Exchange : "<< setw(8)<< ce.reqIn<<"|"
                                    << setw(8)<< ce.reqOut<<"|"
                                    << setw(8)<< ce.ansIn<< "|"
                                    << setw(8)<< ce.ansOut<<"|"<<endl;

    os << "Device WatchDog       : "<< setw(8)<< dw.reqIn<<"|"
                                    << setw(8)<< dw.reqOut<<"|"
                                    << setw(8)<< dw.ansIn<< "|"
                                    << setw(8)<< dw.ansOut<<"|"<<endl;

    os << "DisConnect Peer       : "<< setw(8)<< dp.reqIn<<"|"
                                    << setw(8)<< dp.reqOut<<"|"
                                    << setw(8)<< dp.ansIn<< "|"
                                    << setw(8)<< dp.ansOut<<"|"<<endl;
}

void
DiaStackStats::ResetSessionStats()
{
    LockUS();
    LockDS();

    memset(&app, 0, sizeof(DIA_CMD_STATS));
    memset(&ac, 0, sizeof(DIA_CMD_STATS));
    memset(&as, 0, sizeof(DIA_CMD_STATS));
    memset(&ra, 0, sizeof(DIA_CMD_STATS));
    memset(&st, 0, sizeof(DIA_CMD_STATS));

    UnlockDS();
    UnlockUS();
}

void
DiaStackStats::ResetSessionErrorStats()
{
    LockUS();
    LockDS();

    memset(&err, 0, sizeof(DIA_CMD_STATS));
    decodeFailure = 0;

    UnlockDS();
    UnlockUS();
}


void
DiaStackStats::PrintSessionStats(std::ostream& os) const
{
    char tbuf[ITS_PATH_MAX];
    time_t local;

    time(&local);
#if defined (__SUNPRO_CC)
    ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
    ctime_r(&local, tbuf);
#endif

    os << "-----------------------------------------------------------"
       << endl;    os << "-- Dia Session Stats -- at " << tbuf;
    os << "-----------------------------------------------------------"
       << endl;
    os<<"    Message           : ReqIn   | ReqOut | AnsIn  | AnsOut |"
       <<endl;
    os << "-----------------------------------------------------------"
       << endl;

    os << "Application Based     : "<<setw(8)<<app.reqIn<<"|"
                                    <<setw(8)<<app.reqOut<<"|"
                                    <<setw(8)<<app.ansIn<< "|"
                                    <<setw(8)<<app.ansOut<<"|"<<endl;
    
    os << "Accounting            : "<<setw(8)<< ac.reqIn<<"|"
                                    <<setw(8)<< ac.reqOut<<"|"
                                    <<setw(8)<< ac.ansIn<< "|"
                                    <<setw(8)<< ac.ansOut<<"|"<<endl;
    os << "Abort Session         : "<<setw(8)<< as.reqIn<<"|"
                                    <<setw(8)<< as.reqOut<<"|"
                                    <<setw(8)<< as.ansIn<< "|"
                                    <<setw(8)<< as.ansOut<<"|"<<endl;
    os << "Re-Auth               : "<<setw(8)<< ra.reqIn<<"|"
                                    <<setw(8)<< ra.reqOut<<"|"
                                    <<setw(8)<< ra.ansIn<< "|"
                                    <<setw(8)<< ra.ansOut<<"|"<<endl;
    os << "Session Terminate     : "<<setw(8)<< st.reqIn<<"|"
                                    <<setw(8)<< st.reqOut<<"|"
                                    <<setw(8)<< st.ansIn<< "|"
                                    <<setw(8)<< st.ansOut<<"|"<<endl;
    os << "Msg with 'E' bit set  : "<<setw(8)<< err.reqIn<<"|"
                                    <<setw(8)<< err.reqOut<<"|"
                                    <<setw(8)<< err.ansIn<< "|"
                                    <<setw(8)<< err.ansOut<<"|"<<endl;
    os << "-----------------------------------------------------------"
       << endl;
    os << "Decode Failures       : "<<setw(16)<< decodeFailure<<endl;
    os << "-----------------------------------------------------------"
       << endl;
}

void
DiaStackStats::ResetMiscStats()
{
    LockUS();
    LockDS();

    memset(&diaMiscStats, 0, DIA_MAX_MISC_STATS*sizeof(ITS_UINT));

    UnlockDS();
    UnlockUS();
}

void
DiaStackStats::PrintMiscStats(std::ostream& os) const
{
    os << "-----------------------------------------------------------"
       << endl;    os << "-- Dia Misc Stats --  " << endl;
    os << "-----------------------------------------------------------"
       << endl;
    os << "Num of RedirectEvents               "
       << diaMiscStats[DIA_REDIRECTEVTS] << endl;     
    os << "Num of AccDupRequests               "
       << diaMiscStats[DIA_ACCDUPREQ] << endl;     
    os << "Num of Malformed Requests           "
       << diaMiscStats[DIA_MALFORMDREQ] << endl;     
    os << " Num of Acc Retransmissions         "
       << diaMiscStats[DIA_ACCRETRANS] << endl;     
    os << "Num of Total Retrans                "
       << diaMiscStats[DIA_TOTRETRANS] << endl;     
    os << "Num of AccReqstsDropped             "
       << diaMiscStats[DIA_ACCREQDROPD] << endl;     
    os << "Num of Hop-By-Hop Drop Messages     "
       << diaMiscStats[DIA_HBYHDROPMSGS] << endl;     
    os << "Num of Unknown Types                "
       << diaMiscStats[DIA_UNKNOWNTYPES] << endl;     
    os << " Num of Protocol  Errors            "
       << diaMiscStats[DIA_PROTOCOLERRORS] << endl;     
    os << "Num of Transient Failure            "
       << diaMiscStats[DIA_TRANSIENTFAILS] << endl;     
    os << "Num of Permanent Failures           "
       << diaMiscStats[DIA_PERMANENTFAILS] << endl;     
    os << "Num of Transport Down               "
       << diaMiscStats[DIA_TRANSPDOWN] << endl;     
}

int
DiaStackStats::GetDiaMiscStats(DIA_MISC_STATS_STR *mStats)
{
    if (mStats == NULL)
    {
        return !ITS_SUCCESS;
    }

    mStats->redirectEvents = diaMiscStats[DIA_REDIRECTEVTS];
    mStats->totalRetrans   = diaMiscStats[DIA_TOTRETRANS];
    mStats->hhDropMsgs     = diaMiscStats[DIA_HBYHDROPMSGS];
    mStats->unknownTypes   = diaMiscStats[DIA_UNKNOWNTYPES];
    mStats->protocolErrs   = diaMiscStats[DIA_PROTOCOLERRORS];
    mStats->transientErrs  = diaMiscStats[DIA_TRANSIENTFAILS]; 
    mStats->permanentErrs  = diaMiscStats[DIA_PERMANENTFAILS];

    return ITS_SUCCESS;
}
/*  implementation: public
 ****************************************************************************
 *  Purpose: This function prints the indications from the base diameter
 *      stack to the output stream.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DiaStackStats::PrintIndicStats(std::ostream& os) const
{
    os << "-----------------------------------------------------------"
       << endl;    os << "-- Dia Indication Stats --  " << endl;
    os << "-----------------------------------------------------------"
       << endl;
    os << "Num of Disconnect Indications       "
       << diaIndcStats.numDisconnInd << endl;

    os << "Num of Timeout Indications          "
       << diaIndcStats.numSessTimeoutInd << endl;

    os << "Num of AuthLifeTimeout Indications  "
       << diaIndcStats.numAuthLifeTimeoutInd << endl;

    os << "Num of AuthGraceTimeout Indications "
       << diaIndcStats.numAuthGraceTimeoutInd << endl;

    os << "Num of Abort Indications            "
       << diaIndcStats.numAbortInd << endl;

    os << "Num of Corrupt Indications          "
       << diaIndcStats.numCorruptMsgInd << endl;

    os << "Num of Unknown Indications          "
       << diaIndcStats.numUnknownInd << endl;
    
    os << "Num of FailOver Indications         "
       << diaIndcStats.numFailOverInd << endl;
    
    os << "Num of FailBack Indications         "
       << diaIndcStats.numFailBackInd << endl;
}

void
DiaStackStats::ResetIndicStats()
{
    LockUS();
    LockDS();

    memset(&diaIndcStats, 0, sizeof(DIA_INDIC_STATS));

    UnlockDS();
    UnlockUS();
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function prints the statistical data to the
 *      output stream.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DiaStackStats::Print(std::ostream& os) const
{
    char tbuf[ITS_PATH_MAX];
    time_t local;

    time(&local);
#if defined (__SUNPRO_CC)
    ctime_r(&local, tbuf, ITS_PATH_MAX);
#else
    ctime_r(&local, tbuf);
#endif

    Lock();

    os << "-----------------------------------------------------------" 
       << endl;    os << "-- DiaStack Stats -- at " << tbuf;
    os << "-----------------------------------------------------------" 
       << endl;    

    os << "Total Num of Msgs Sent                         "
       <<  totalMsgOut << endl;
    os << "Total Num of Msgs Received                     "
       <<  totalMsgIn << endl;
         
    PrintPeerStats(os);    
    PrintSessionStats(os);    
    //PrintMiscStats(os);    
    PrintIndicStats(os);    
 
    Unlock();
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: Overloading of the << operator.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ostream&
operator<<(ostream& os, const DiaStackStats& diaStackStats)
{
    diaStackStats.Print(os);
    return os;
}

