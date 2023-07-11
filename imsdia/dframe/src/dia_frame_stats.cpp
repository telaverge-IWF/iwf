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
 *  ID: $Id: dia_frame_stats.cpp,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $
 *
 *  LOG: $Log: dia_frame_stats.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.3  2006/05/26 14:13:05  yranade
 *  LOG: Support for CC Compiler.
 *  LOG:
 *  LOG: Revision 1.2  2006/04/25 15:39:12  yranade
 *  LOG: Added flowerboxes.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:08:15  tpanda
 *  LOG: Building IMS Diameter Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_frame_stats.cpp,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $"

#include <dia_frame_stats.h>

using namespace std;

its::ITS_Mutex DiaFrameStats::guard(0);

static DiaFrameStats *odstats = NULL;
/*.implementation:public
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
DiaFrameStats* 
DiaFrameStats::GetDiaFrameStats()
{
    ITS_ASSERT(DiaFrameStats::guard.Acquire() == ITS_SUCCESS);

    if (odstats == NULL)
    {
        odstats = new DiaFrameStats;
    }

    DiaFrameStats::guard.Release();

    return odstats;
}

/*.implementation:public
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
void
DiaFrameStats::Print(std::ostream& os) const
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

    os << "-----------------------------------------------------------" << endl;
    os << "-- DiaFrame Stats -- at " << tbuf;
    os << "-----------------------------------------------------------" << endl;
    os << endl;

    os << "Num of Msgs From Stack "
       <<  numMsgsFromStack << endl;
    os << endl;

    os << "Num of Msgs From Application "
       <<  numMsgsFromApp << endl;
    os << endl;

    Unlock();
}
/*.implementation:public
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ostream&
operator<<(ostream& os, const DiaFrameStats& odStats)
{
    odStats.Print(os);
    return os;
}


