/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_proxy.h,v $
 * LOG: Revision 1.2.62.1  2013/03/22 05:56:57  jvikram
 * LOG: Corrected the issues related to message handling related to same session id
 * LOG: by queuing the messages. Also included debug logs.
 * LOG:
 * LOG: Revision 1.2  2008/12/12 17:53:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 1.1  2008/12/07 09:54:05  rajeshak
 * LOG: Created new file to separate the functionality of proxy
 * LOG:
 *
 * ID: $Id: dia_proxy.h,v 1.2.62.1 2013/03/22 05:56:57 jvikram Exp $
 ****************************************************************************/
#ident "$Id: dia_proxy.h,v 1.2.62.1 2013/03/22 05:56:57 jvikram Exp $"

#ifndef DIA_PROXY_H
#define DIA_PROXY_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_cmn.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>

/*.Interface: DiaProxyHandler 
 *****************************************************************************
 *  Interface:
 *      DiaProxyHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network 
 *****************************************************************************/
class DiaProxyHandler
{
public:
    /*.implementation:public,inline,DiaProxyHandler
    ************************************************************************
    *  Purpose:
    *       DiaProxyHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaProxyHandler () {}

    /*.implementation:public,inline,DiaProxyHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaProxyHandler
    *           
    ************************************************************************/
    ~DiaProxyHandler(){}
    
    /*.implementation:public,DiaProxyHandler
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing Network messages
    *           
    ************************************************************************/

    static int HandleReqMessage(DIA_BASE_CMD *cmd, its::Event &ev );

    static int HandleProxyAuthReqMsg(DIA_BASE_CMD *&cmd, 
                                        its::Event &ev);

    static int HandleProxyAcctReqMsg(DIA_BASE_CMD *&cmd, 
                                        its::Event &ev);

    static int HandleProxyAuthAnsMsg(DIA_BASE_CMD *&cmd, 
                                    SESSION_ENTRY *ent, its::Event &ev);

    static int HandleProxyAcctAnsMsg(DIA_BASE_CMD *&cmd, 
                                    SESSION_ENTRY *ent, its::Event &ev);
    
    static int HandleAcctReqMsgFromApp(DIA_BASE_CMD *cmd, 
                                    ITS_OCTET * sessionId, 
                                    SESSION_ENTRY *e, its::Event &ev);

    static int HandleAuthReqMsgFromApp(DIA_BASE_CMD *cmd, 
                                    ITS_OCTET * sessionId, 
                                    SESSION_ENTRY *e, its::Event &ev);

    static int HandleAcctAnsMsgFromApp(DIA_BASE_CMD *cmd, 
                                    ITS_OCTET * sessionId, 
                                    SESSION_ENTRY *ent, its::Event &ev);

    static int HandleAuthAnsMsgFromApp(DIA_BASE_CMD *cmd, 
                                    ITS_OCTET * sessionId, 
                                    SESSION_ENTRY *ent, its::Event &ev);

   static int CheckIfMsgTobeQueued(DIA_BASE_CMD *msg,
				     SESSION_ENTRY *ent,ITS_EVENT &ev);

   static ITS_INT RepostPendingMessageOfSession(SESSION_ENTRY* aSessEntry,
				     ITS_OCTET * sessionId);
     
};

#endif
