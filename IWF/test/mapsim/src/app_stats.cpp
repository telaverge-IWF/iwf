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
 * LOG: $Log: app_stats.cpp,v $
 * LOG: Revision 1.1.2.1  2013/02/12 14:09:19  jvikas
 * LOG: Map Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/03 19:44:56  brajappa
 * LOG: Changes for compilation errors
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/28 13:45:14  lakshman
 * LOG: checkin first version of MAP test along with CAP.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_stats.cpp,v 1.1.2.1 2013/02/12 14:09:19 jvikas Exp $"

#include <iostream>
#include <app_stats.h>

#include <time.h>
#include <tcap++.h>
#include <app_const.h>
#include <sys/timeb.h>

using namespace std;
using namespace its;

extern struct timeb sendComplete, recvComplete;

TcapStats::TcapStats() 
{
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];

    sentBegins   = receivedBegins = sentEnds        = 0;
    receivedEnds = sentInvokes    = receivedInvokes = 0;

    receivedLCancels    = sentRResults = receivedRResults = 0;
    sentPreArrangedEnds = sentCont     = receivedCont = 0;

    output.open("tcapStats.out");

    time(&tx);
    temp =  localtime_r(&tx, &tbuf);
    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
    output << buff << endl; 
}

TcapStats::~TcapStats()
{
    /*Close the file descriptor*/
}

void TcapStats::UpdateSendStats(unsigned short type, bool isPreArranged)
{
     return;
}

void TcapStats::UpdateRecvStats(unsigned short type)
{
     return;
}

/*void TcapStats::UpdateStats(TCAP_Component* its_cpt)
{
    switch ((*cpt)->GetComponentType())
       {
           case TCPPT_TC_INVOKE:
           {
               TCAP_Invoke *ivk = dynamic_cast<TCAP_Invoke *>(*cpt);
               ivk->GetOperation(op);
               
               if (op == map_common::OP_updateGprsLocation)
               {
                   appStats.u.hlrmap.ulr.m_in++;
                   //int recent_msg_idx = appStats.recent_msg_idx++ % 10;
                   //appStats.last_processed_msgs[recent_msg_idx] = "Received UpdateGPRS Location Request with IMSI: ";
                   //appStats.last_processed_msgs[recent_msg_idx] += udReq.getUserName().value();
                   //appStats.recent_msg_idx = recent_msg_idx+1; 
                   //appStats.u.hlrmap.ula.m_out++;
               }
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   appStats.u.hlrmap.air.m_in++;
               }
               else if (op == map_common::OP_insertSubscriberData)
               {
                   appStats.u.hlrmap.idr.m_in++;
               }
           }
           break;

           case TCPPT_TC_RESULT_L:
           case TCPPT_TC_RESULT_NL:
           {
               TCAP_Result *resl = dynamic_cast<TCAP_Result *>(*cpt);
               resl->GetOperation(op); 

               (*cpt)->Print(cout);
               if (op == map_common::OP_updateGprsLocation)
               {
                   appStats.u.hlrmap.ula.m_in++;
               }
               else if (op == map_common::OP_insertSubscriberData)
               {
                   appStats.u.hlrmap.ida.m_in++;
               }
               else if (op == map_common::OP_sendAuthenticationInfo)
               {
                   appStats.u.hlrmap.aia.m_in++;
               }
           }
           break;

           default:
           break;
       }

    return;
}*/

void TcapStats::PrintTCAPStats(std::ostream& oss)
{
      time_t tx;
      struct tm tbuf, *temp;
      char buff[80];

      oss << "Num of Begins  Sent         = " << sentBegins << endl;
      oss << "Num of BeginsReceived       = " << receivedBegins << endl;
      oss << "Num of Continues Sent       = " << sentCont << endl;
      oss << "Num of Continues Received   = " << receivedCont << endl; 
      oss << "Num of Ends sent            = " << sentEnds << endl;
      oss << "Num of Ends Received        = " << receivedEnds << endl;
      oss << "Num of Aborts Sent          = " << sentAbort << endl;
      oss << "Num of Aborts Received      = " << receivedAbort << endl;
      oss << "Num of Invokes Sent         = " << sentInvokes << endl;
      oss << "Num of Invokes Received     = " << receivedInvokes << endl;
      oss << "Num of LocalCancels recv    = " << receivedLCancels << endl;
      oss << "Num of ReturnResults Sent   = " << sentRResults << endl;
      oss << "Num of ReturnResults Recv   = " << receivedRResults << endl;
      oss << "Num of PreArrangedEnds Sent = " << sentPreArrangedEnds << endl;

     time(&tx);
     temp =  localtime_r(&tx, &tbuf);
     strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
     oss << buff << endl; 

     return;
}

