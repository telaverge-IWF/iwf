/********************************-*hpp*-*************************************
 *                                                                          *
 *             Copyright 2008 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: dia_stack_stats.h,v 1.7.44.1 2013/02/19 11:05:57 jsarvesh Exp $
 *  
 *  LOG: $Log: dia_stack_stats.h,v $
 *  LOG: Revision 1.7.44.1  2013/02/19 11:05:57  jsarvesh
 *  LOG: dre global stats implementation
 *  LOG:
 *  LOG: Revision 1.7  2011/02/15 05:43:53  nvijikumar
 *  LOG: Common stats structure are moved to imsdia/common
 *  LOG:
 *  LOG: Revision 1.6  2009/07/24 09:25:25  rajeshak
 *  LOG: Added Reset function for different statistics.
 *  LOG:
 *  LOG: Revision 1.5  2009/03/26 05:32:47  nvijikumar
 *  LOG: GetDiaMiscStats and ResetAllStats API Support
 *  LOG:
 *  LOG: Revision 1.4  2009/03/02 04:41:40  nvijikumar
 *  LOG: Enhancements for MML API Support
 *  LOG:
 *  LOG: Revision 1.3  2009/01/07 13:12:11  nvijikumar
 *  LOG: Adding Mutex to make it thread safe
 *  LOG:
 *  LOG: Revision 1.2  2008/12/12 12:33:03  sureshj
 *  LOG: Updates for Statistics support
 *  LOG:
 *  LOG: Revision 1.1  2008/12/12 07:52:40  nvijikumar
 *  LOG: Initial draft for Stack Statistics support (Suresh)
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: dia_stack_stats.h,v 1.7.44.1 2013/02/19 11:05:57 jsarvesh Exp $"

#ifndef DIA_STACK_STATS_H_
#define DIA_STACK_STATS_H_

#include <dia_stats.h>
#include <dia_cmn.h>

extern bool isStackStatsEnabled;

class DiaStackStats;

extern DiaStackStats diaStackStats;

/*
 * MACROS to update the stats
 */


#define UPDATE_DIA_STATS_REQIN(x)                                          \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateReqInStats(x);                                 \
    }

#define UPDATE_DIA_STATS_REQOUT(x)                                         \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateReqOutStats(x);                                \
    }

#define UPDATE_DIA_STATS_ANSIN(x)                                          \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateAnsInStats(x);                                 \
    }
    
#define UPDATE_DIA_STATS_ANSOUT(x)                                          \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateAnsOutStats(x);                                \
    }

#define UPDATE_DIA_STATS_MISC(x)                                           \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateMiscStats(x);                                  \
    }

#define UPDATE_DIA_STATS_INDC(x)                                           \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateIndicStats(x);                                 \
    }

#define UPDATE_DIA_ERR_ANSOUT()                                            \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateErrSessionAnsOutStats();                       \
    }

#define UPDATE_DIA_ERR_ANSIN()                                             \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateErrSessionAnsInStats();                        \
    }

#define UPDATE_DIA_STATS_DECODE_FAILED()                                   \
    if (isStackStatsEnabled)                                               \
    {                                                                      \
        diaStackStats.UpdateDecodeFailureStats();                          \
    }

class DiaStackStats: public DiaStats
{
public:
    ~DiaStackStats(){};

    DiaStackStats():
      DiaStats()
    {
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
        decodeFailure = 0;
    }

    int GetDiaIndStats(DIA_INDIC_STATS *indStats);
    int GetDiaSessStats(DIA_SESS_STATS *sessStats);
    int GetDiaPeerStats(DIA_PEER_STATS *peerStats);
    int GetDiaMiscStats(DIA_MISC_STATS_STR *mStats);
    int GetDiaTotalMessages()
    {
        return (totalMsgOut + totalMsgIn);
    }

    void UpdateReqInStats(ITS_UINT cmdCode);
    void UpdateReqOutStats(ITS_UINT cmdCode);
    void UpdateAnsInStats(ITS_UINT cmdCode);
    void UpdateAnsOutStats(ITS_UINT cmdCode);

    void UpdateErrSessionAnsInStats();
    void UpdateErrSessionAnsOutStats();
    void UpdateDecodeFailureStats();

    void UpdateMiscStats(DIA_MISC_STATS miscStats);
    void UpdateIndicStats(ITS_UINT indc);
   
    /*
     * Print functions 
     */
    void Print(std::ostream& os) const;
    void PrintPeerStats(std::ostream& os) const;
    void PrintSessionStats(std::ostream& os) const;
    void PrintMiscStats(std::ostream& os) const;
    void PrintIndicStats(std::ostream& os) const;

    void ResetPeerStats();
    void ResetSessionStats();
    void ResetSessionErrorStats();
    void ResetMiscStats();
    void ResetIndicStats();
    void ResetTotalMsgStats()
    {
        totalMsgOut = 0;
        totalMsgIn = 0;
    }

    void ResetAll();
    void LockDS() const;
    void UnlockDS() const;
    void LockUS() const;
    void UnlockUS() const;

private:
    //This mutex only to get class instance
    static its::ITS_Mutex guardDS;
    static its::ITS_Mutex guardUS;

    /*
     * Session based
     */
    DIA_CMD_STATS app;
    DIA_CMD_STATS as;
    DIA_CMD_STATS ac;
    DIA_CMD_STATS st;
    DIA_CMD_STATS ra;
    DIA_CMD_STATS err;
    DIA_CMD_STATS totalSessionBased;

    /*
     * Peer based
     */
    DIA_CMD_STATS ce;
    DIA_CMD_STATS dw;
    DIA_CMD_STATS dp;
    DIA_CMD_STATS totalPeerBased;
   
    ITS_UINT totalMsgOut;
    ITS_UINT totalMsgIn;
    ITS_UINT decodeFailure;

    /*
     * Misc Dia Stats
     */
    ITS_UINT diaMiscStats[DIA_MAX_MISC_STATS];

    /*
     * Dia Indication Stats
     */
    DIA_INDIC_STATS diaIndcStats;

    /*
     * Copy Constructor
     */
    DiaStackStats(const DiaStackStats&);
    DiaStackStats&
    operator=(const DiaStackStats&);

};

std::ostream& operator<< (std::ostream& os, const DiaStackStats& diaStackStats);
#endif
