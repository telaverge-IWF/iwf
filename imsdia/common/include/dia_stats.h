/**************************-*-Dia-*-*************************************
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
 *  ID: $Id: dia_stats.h,v 3.2 2011/02/15 05:42:42 nvijikumar Exp $
 *
 *  LOG: $Log: dia_stats.h,v $
 *  LOG: Revision 3.2  2011/02/15 05:42:42  nvijikumar
 *  LOG: Common stats structure are moved from dia_stack_stats.h
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.3  2006/04/07 11:35:46  yranade
 *  LOG: DoxyGen Compatible Code Comments.
 *  LOG:
 *  LOG: Revision 1.2  2006/03/13 16:26:48  yranade
 *  LOG: Remove decrement, what was I thinking.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 *  LOG: Building IMS Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_stats.h,v 3.2 2011/02/15 05:42:42 nvijikumar Exp $"

#if !defined(_DIA_STATS_H_)
#define _DIA_STATS_H_

#include <its++.h>
#include <iostream>
#include <its_mutex.h>

typedef struct _diaCmdStats
{
     ITS_UINT reqIn;
     ITS_UINT reqOut;
     ITS_UINT ansIn;
     ITS_UINT ansOut;
}DIA_CMD_STATS;

typedef struct _diaPeerStats
{
     DIA_CMD_STATS total;
     DIA_CMD_STATS ce;
     DIA_CMD_STATS dw;
     DIA_CMD_STATS dp;
}DIA_PEER_STATS;

typedef struct _diaSessStats
{
     DIA_CMD_STATS app;
     DIA_CMD_STATS ac;
     DIA_CMD_STATS as;
     DIA_CMD_STATS ra;
     DIA_CMD_STATS st;
     DIA_CMD_STATS err;
     ITS_UINT     decodeFailure;
}DIA_SESS_STATS;

/* 
 * Indications Received
 */
typedef struct _diaIndStats
{
    ITS_UINT numDisconnInd;
    ITS_UINT numSessTimeoutInd;
    ITS_UINT numAuthLifeTimeoutInd;
    ITS_UINT numAuthGraceTimeoutInd;
    ITS_UINT numAbortInd;
    ITS_UINT numCorruptMsgInd;
    ITS_UINT numUnknownInd;
    ITS_UINT numFailOverInd;
    ITS_UINT numFailBackInd;
}DIA_INDIC_STATS;

/* 
 * Misc Stats Received
 */
typedef struct _diaStrMiscStats
{
    ITS_UINT redirectEvents;
    ITS_UINT totalRetrans;
    ITS_UINT hhDropMsgs;
    ITS_UINT unknownTypes;
    ITS_UINT protocolErrs;
    ITS_UINT transientErrs;
    ITS_UINT permanentErrs;
}DIA_MISC_STATS_STR;

typedef enum
{
     DIA_REDIRECTEVTS =0,
     DIA_ACCDUPREQ,
     DIA_MALFORMDREQ,
     DIA_ACCRETRANS,
     DIA_TOTRETRANS,
     DIA_ACCREQDROPD,
     DIA_HBYHDROPMSGS,
     DIA_UNKNOWNTYPES,
     DIA_PROTOCOLERRORS,
     DIA_TRANSIENTFAILS,
     DIA_PERMANENTFAILS,
     DIA_TRANSPDOWN,
     DIA_MAX_MISC_STATS
}
DIA_MISC_STATS;


/** Interface:
 *      Abstract DiaStats Class
 *      
 *  Purpose:
 *      DiaStats class forms the Base Class to encapsulate all Diameter stack 
 *      pegs and statistics. Individual Modules inherit from this base class
 *      and implement their layer specific pegs and statistics.
 **/
class DiaStats
{
public:
    DiaStats()
        :lock(0){}

    virtual ~DiaStats(){}

    virtual void Print(std::ostream& os) const = 0;

    virtual void Increment(ITS_UINT& peg)
    {
        Lock();
        peg++;
        Unlock();
    }

    virtual void Reset(ITS_UINT& peg)
    {
        Lock();
        peg = 0;
        Unlock();
    }

    virtual void ResetAll() = 0;

    void Lock() const
    {
        const_cast<its::ITS_Mutex&>(lock).Acquire();
    }

    void Unlock() const
    {
        const_cast<its::ITS_Mutex&>(lock).Release();
    }

protected:
    its::ITS_Mutex lock;

private:

};

#endif

