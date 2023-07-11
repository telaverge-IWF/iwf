/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: Daewoo testbed                                                 *
 *                                                                          *
 *     FILE: user.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: user.h,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
 *
 * LOG: $Log: user.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:45  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:57  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:34  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:58:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:57  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/02/06 14:26:14  mmiers
 * LOG: Make sure the latest version is here.
 * LOG:
 * LOG: Revision 1.2  1998/01/21 18:13:21  rsonak
 * LOG: General update/cleanup.
 * LOG:
 * Revision 1.1  1998/01/12  17:43:25  rsonak
 * *** empty log message ***
 *
 *
 ****************************************************************************/

#ifndef USER_H
#define USER_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * user message structure.
 */
typedef struct {
    unsigned char command;
    unsigned short call_ref;
} USER_MSG;

#define SEND_ACM		1
#define SEND_ANM		2
#define SEND_CPG		3
#define SEND_CON		4
#define SEND_IAM		5
#define SEND_REL		6
#define SEND_RLC		7
#define SEND_BLO		8
#define SEND_BLA		9
#define SEND_UBL		10
#define SEND_UBA		11
#define SEND_CGB		12
#define SEND_CGBA		13
#define SEND_CGU		14
#define SEND_CGUA		15
#define SEND_GRS		16
#define SEND_GRA		17
#define SEND_RSC		18
#define SEND_SUS		19
#define SEND_RES		20

#define SEND_INVOKE1_CPT	21
#define SEND_INVOKE4_CPT	22
#define SEND_RL_CPT		23
#define SEND_DLG_U_ABORT	24
#define SEND_DLG_BEGIN		25
#define SEND_DLG_CONT		26
#define SEND_DLG_END		27
#define SEND_DLG_UNI		28
#define REPLY_RL_CPT		29
#define REPLY_DLG_U_ABORT	30
#define REPLY_DLG_CONT		31
#define REPLY_DLG_END		32
#define REPLY_DLG_UNI		33

#define SEND_INFO_FWD_IL	34

#define SEND_CALL_INFO_RES	35
#define SEND_EVENT_REPORT_BCSM	36
#define SEND_INITIAL_DP		37
#define SEND_SERV_FILT_RES	38
#define SEND_APPLY_CHARGE_REQ	39
#define SEND_APPLY_CHARGE_RES	40
#define SEND_ACT_SERV_FILT	41
#define SEND_ACTIVITY_TEST	42
#define SEND_CALL_GAP		43
#define SEND_CANCEL		44
#define SEND_CONNECT		45
#define SEND_CONTINUE		46
#define SEND_DISC_FORW_CONN	47
#define SEND_ESTAB_TEMP_CONN	48
#define SEND_FURN_CHARG_INFO	49
#define SEND_RELEASE_CALL	50
#define SEND_REQ_RPT_BCSM_EVENT	51
#define SEND_RESET_TIMER	52

#define SEND_TGTD_DIAL_DTMF     53
#define SEND_TGTD_GET_DTMF      54
#define SEND_TGTD_GET_DTMFSTRING       55
#define SEND_TGTD_RECORD_FILE	56
#define SEND_TGTD_PLAY_FILE	57

#ifdef __cplusplus
}
#endif

#endif /* USER_H */
