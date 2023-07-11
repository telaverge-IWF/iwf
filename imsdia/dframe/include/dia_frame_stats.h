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
 *  ID: $Id: dia_frame_stats.h,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $
 *
 *  LOG: $Log: dia_frame_stats.h,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.2  2006/04/07 11:37:24  yranade
 *  LOG: DoxyGen Compatible Code Comments.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:08:15  tpanda
 *  LOG: Building IMS Diameter Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_frame_stats.h,v 3.1 2008/03/31 10:33:25 nvijikumar Exp $"

#if !defined(_DIAFRAME_STATS_H_)
#define _DIAFRAME_STATS_H_

#include <dia_stats.h>

/** Interface:
 *      DiaFrameStats
 *      
 *  Purpose:
 *      DiaFrameStats class is used to encapsulate all Diameter stack 
 *      pegs and statistics.
 **/
class DiaFrameStats: public DiaStats
{
public:
    /********************************************************************/
    /** Purpose:
    *      Static Function to get the DiaFrameStats instance. 
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
    *      Pointer to the singleton DiaFrameStats object.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
     static DiaFrameStats* GetDiaFrameStats();

     ~DiaFrameStats(){};
     
    /********************************************************************/
    /** Purpose:
    *      Print Function to print the DiaFrameStats. 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      std::ostream& os: A std:: Ostream object
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
     void Print(std::ostream& os) const;
     
    /********************************************************************/
    /** Purpose:
    *      Function to Get the Count of Messages from base Diameter Stack. 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      Count of Messages from the stack.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
     ITS_UINT& GetNumMsgsFromStack()
     {
         return numMsgsFromStack;
     }

    /********************************************************************/
    /** Purpose:
    *      Function to Get the Count of Messages from Application to Stack. 
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      Count of Messages from the Application to Stack.
    *
    *  Return Value:
    *      None.
    *
    *  Notes:
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
     ITS_UINT& GetNumMsgsFromApp()
     {
         return numMsgsFromApp;
     }

    /********************************************************************/
    /** Purpose:
    *      Function to Reset Complete Statistics. 
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
    *      None.
    *
    *  See Also:
    *      None.
    *
    **/
    /* Revision History:
    *
    *********************************************************************/
     void ResetAll()
     {
         Lock();
         numMsgsFromStack = 0;
         numMsgsFromApp = 0;
         Unlock();
     }

private:
     static its::ITS_Mutex guard;

     ITS_UINT numMsgsFromStack;
     ITS_UINT numMsgsFromApp;

     DiaFrameStats()
     : DiaStats(),
       numMsgsFromStack(0),
       numMsgsFromApp(0)
      {};


     DiaFrameStats(const DiaFrameStats&);

     DiaFrameStats&
     operator=(const DiaFrameStats&);
     //{ return *this;}
};

// DiaFrameStats ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const DiaFrameStats& odStats);

#endif

