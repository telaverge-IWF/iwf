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
 * LOG: $Log: dia_downstream.h,v $
 * LOG: Revision 3.1.118.1  2014/10/27 08:28:39  millayaraja
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/10/30 15:57:41  yranade
 * LOG: ReleaseSession API is Asychronous.
 * LOG:
 * LOG: Revision 2.3  2006/10/13 16:34:55  yranade
 * LOG: A bit of cleanup.
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
 * ID: $Id: dia_downstream.h,v 3.1.118.1 2014/10/27 08:28:39 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: dia_downstream.h,v 3.1.118.1 2014/10/27 08:28:39 millayaraja Exp $"

#ifndef DIA_DOWN_MSG_HANDLERS_H
#define DIA_DOWN_MSG_HANDLERS_H

#include <dia_defines.h>
#include <dia_module.h>

/*.Interface: DiaDownStreamMsgHandler 
 *****************************************************************************
 *  Interface:
 *      DiaDownStreamMsgHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from Application 
 *****************************************************************************/
class DiaDownStreamMsgHandler:public MessageHandler
{
public:
    /*.implementation:public,inline,DiaDownStreamMsgHandler
    ************************************************************************
    *  Purpose:
    *       DiaDownStreamMsgHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaDownStreamMsgHandler ()
        :MessageHandler(DIA_APP_INST){ }

    DiaDownStreamMsgHandler(ITS_USHORT src)
        :MessageHandler(src){}

    /*.implementation:public,inline,DiaDownStreamMsgHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaDownStreamMsgHandler
    *           
    ************************************************************************/
    ~DiaDownStreamMsgHandler(){}
    
    /*.implementation:public,DiaStackApp
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing App messages
    *           
    ************************************************************************/
    int HandleMessage(DIAThread *thr, its::Event &ev);
    int HandleAcctReqMessage(its::Event &ev);
    int HandleAcctAnsMessage(its::Event &ev);
    int HandleAuthReqMessage(its::Event &ev);
    int HandleAuthAnsMessage(its::Event &ev);
    int ReleaseSession(const char* sessionId);
    int ReCreateSessionEntry(char* sessionId, ITS_OCTET* sessionData, ITS_UINT& sessionIdex, ITS_UINT& appId);


private:

};

#endif
