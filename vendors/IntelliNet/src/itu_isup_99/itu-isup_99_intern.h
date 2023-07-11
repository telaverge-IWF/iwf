/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: itu-isup_99_intern.h,v 1.2.46.1 2013/10/04 13:39:16 millayaraja Exp $
 *
 *  LOG: $Log: itu-isup_99_intern.h,v $
 *  LOG: Revision 1.2.46.1  2013/10/04 13:39:16  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags
 *  LOG:
 *  LOG: Revision 1.2  2006/01/09 06:44:52  omayor
 *  LOG: Added support for ITU ISUP 99.(skatta)
 *  LOG:
 *      
 ****************************************************************************/

#ifndef ITU_ISUP_99_INTERN_H
#define ITU_ISUP_99_INTERN_H

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Functions returning Message handlers
 * depending on message type and call state
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgHandler_ITU_99(ITS_OCTET msgType,
                                                  ITS_ISUP_STATE state);
/*
 * Message handling functions for all the call states
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_Idle_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAcm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAnm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_RcvdIncomingAnm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRlc_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRes_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAcm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAnm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_SentOutgoingAnm_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRlc_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRes_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRel_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRsc_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingGra_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCot_ITU_99(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReport_ITU_99(ITS_OCTET msgType);


/*
 * Generic message and timer handlers, valid for all states
 */
void __ISUP_Received_APM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
static void __ISUP_Received_PRI(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

#ifdef __cplusplus
}
#endif

#endif /* ITU_ISUP_99_INTERN_H */

