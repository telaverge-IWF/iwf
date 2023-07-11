/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: app_stats.h,v $
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:15  jkchaitanya
 * LOG: sub directories in capsim
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 19:44:56  brajappa
 * LOG: Changes for compilation errors
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_stats.h,v 1.1.2.1 2013/08/21 12:14:15 jkchaitanya Exp $"

#include <iostream>
#include <strstream>
#include <fstream>

#ifndef TCAP_STATS_H
#define TCAP_STATS_H

class TcapStats {
   public:
       TcapStats();

       ~TcapStats();
      
       void UpdateSendStats(unsigned short type, bool isPreArranged = false);

       void UpdateRecvStats(unsigned short type);

       void PrintTCAPStats(std::ostream& oss);

   private:    
       unsigned int sentBegins;
       unsigned int receivedBegins;
       unsigned int sentCont;
       unsigned int receivedCont;
       unsigned int sentEnds;
       unsigned int receivedEnds; 
       unsigned int sentAbort;
       unsigned int receivedAbort;
       unsigned int sentInvokes;
       unsigned int receivedInvokes;
       unsigned int receivedLCancels;
       unsigned int sentRResults;
       unsigned int receivedRResults;
       unsigned int sentPreArrangedEnds;
       int tps;
       std::ofstream output;
};

#endif

