/*********************************-*HPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_timer_handler.h,v $
 * LOG: Revision 3.4.98.1.6.4  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.4.98.1.6.3  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.4.98.1.6.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.4.98.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.4  2009/04/13 13:41:36  rajeshak
 * LOG: Peer Discovery changes.
 * LOG:
 * LOG: Revision 3.3  2009/02/03 10:15:56  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.2  2008/12/12 07:55:18  sureshj
 * LOG: Cleanup (Viji)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.6  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.4.10.1  2007/09/03 14:58:10  hbhatnagar
 * LOG: Fix for Bridgewater Ticket 1752 transport shutdown due to DWTimeout.
 * LOG:
 * LOG: Revision 2.4  2006/10/12 10:35:38  yranade
 * LOG: Changing timer context sessionId as static variable
 * LOG: ( due to memory leak problem in load mode)
 * LOG:
 * LOG: Revision 2.3  2006/10/09 06:27:49  yranade
 * LOG: Timer related updates, still to be finished.
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 *
 * ID: $Id: dia_timer_handler.h,v 3.4.98.1.6.4 2020/02/14 11:36:11 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_timer_handler.h,v 3.4.98.1.6.4 2020/02/14 11:36:11 jkchaitanya Exp $"

#ifndef DIA_TIMER_MSG_HANDLER_H
#define DIA_TIMER_MSG_HANDLER_H

#include <dia_defines.h>
#include <dia_peer_table.h>
#include <dia_module.h>
#include <dia_cmn.h>
#include <its_dia_config.h>
#include <dia_realm_table.h>

class DiaSocketTransport;
typedef struct _diaTimerCtxt
{
    DIA_TIMER_TYPE  timerType;
    union
    {
        struct 
        {
            char sessionId[ITS_DIA_TIMER_CXT_SIZE];
        }
        sessionInfo;
        struct
        {
            //ITS_USHORT trInst;
            PEER_ENTRY *peer;
        }
        peerInfo;
        struct
        {
            REALM_ENTRY *realm;
        }
        realmInfo;
        struct
        {
            char key[ITS_DIA_TIMER_CXT_SIZE];
        }
        cacheInfo;
        struct
        {
            PEER_ENTRY *peer;
            unsigned int hopid;
        }
        retransInfo;
        struct
        {
            DiaSocketTransport *trHandle;
        }
        transportInfo;
    }
   data;
}
DIA_TIMER_CTXT;

/*.Interface: DiaTimerMsgHandler 
 *****************************************************************************
 *  Interface:
 *      DiaTimerMsgHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network 
 *****************************************************************************/
class DiaTimerMsgHandler:public MessageHandler
{
public:
    /*.implementation:public,inline,DiaTimerMsgHandler
    ************************************************************************
    *  Purpose:
    *       DiaTimerMsgHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaTimerMsgHandler ()
        :MessageHandler(ITS_TIMER_SRC){ }

    /*.implementation:public,inline,DiaTimerMsgHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaTimerMsgHandler
    *           
    ************************************************************************/
    ~DiaTimerMsgHandler(){}
    
    /*.implementation:public,DiaTimerMsgHandler
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing Network messages
    *           
    ************************************************************************/
    int HandleMessage(DIAThread *thr, its::Event &ev);
    int HandleRetryTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleExpiryTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleAuthSessionTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleLifeTimeTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleGracePeriodTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleRetryAbortTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleAcctSessionTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleInterimIntervalTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleRealTimeTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleCacheTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleTTLTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleRetransmissionTimeout(DIA_TIMER_CTXT *ctxt);
    int HandleFlushTimeout(DIA_TIMER_CTXT *ctxt);
private:
};

#endif
