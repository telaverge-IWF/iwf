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
 * LOG: $Log: dia_upstream.h,v $
 * LOG: Revision 3.3  2008/12/12 17:57:02  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:14:26  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2006/11/25 04:00:12  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.4  2006/11/22 10:51:46  nvijikumar
 * LOG: Baseline PendingQ (Failover) changes.
 * LOG:
 * LOG: Revision 2.3  2006/10/25 15:17:08  yranade
 * LOG: Error Handling related updates.
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
 * ID: $Id: dia_upstream.h,v 3.3 2008/12/12 17:57:02 rajeshak Exp $
 ****************************************************************************/
#ident "$Id: dia_upstream.h,v 3.3 2008/12/12 17:57:02 rajeshak Exp $"

#ifndef DIA_UP_MSG_HANDLER_H
#define DIA_UP_MSG_HANDLER_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_cmn.h>

/*.Interface: DiaUpStreamMsgHandler 
 *****************************************************************************
 *  Interface:
 *      DiaUpStreamMsgHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network 
 *****************************************************************************/
class DiaUpStreamMsgHandler:public MessageHandler
{
public:
    /*.implementation:public,inline,DiaUpStreamMsgHandler
    ************************************************************************
    *  Purpose:
    *       DiaUpStreamMsgHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaUpStreamMsgHandler ()
        :MessageHandler(DIA_NET_INST), AppId(0){ }

    DiaUpStreamMsgHandler (ITS_USHORT src)
        :MessageHandler(src), AppId(0){ }

    /*.implementation:public,inline,DiaUpStreamMsgHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaUpStreamMsgHandler
    *           
    ************************************************************************/
    ~DiaUpStreamMsgHandler(){}
    
    /*.implementation:public,DiaUpStreamMsgHandler
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing Network messages
    *           
    ************************************************************************/
    int HandleMessage(DIAThread *thr, its::Event &ev);
    int HandleReqMessage(its::Event &ev);
    int HandleAnsMessage(its::Event &ev);
    int HandleLocalAuthReqMessage(DIA_BASE_CMD *&cmd, its::Event &ev, 
                                  bool isProxy = false);
    int HandleLocalAuthAnsMessage(DIA_BASE_CMD *&cmd, its::Event &ev);
    int HandleLocalAcctReqMessage(DIA_BASE_CMD *&cmd, its::Event &ev,
                                  bool isProxy = false);
    int HandleLocalAcctAnsMessage(DIA_BASE_CMD *&cmd, its::Event &ev);

     

private:
    int AppId;
};

#endif
