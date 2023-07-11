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
 *     FILE: test.c                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test.c,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
 *
 * LOG: $Log: test.c,v $
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
 * LOG: Revision 5.1  2001/08/16 20:45:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:59  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:55  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/06/04 20:17:17  cmarchant
 * LOG:
 * LOG:
 * LOG: Build tests after updating ISUP code.
 * LOG:
 * LOG: Revision 1.4  1999/05/24 21:07:09  mmiers
 * LOG:
 * LOG:
 * LOG: Enable the transports to parse hex strings.
 * LOG:
 * LOG: Revision 1.3  1999/05/24 16:41:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize API.
 * LOG:
 * LOG: Revision 1.2  1999/05/24 15:49:14  mmiers
 * LOG:
 * LOG:
 * LOG: Update test code.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 15:39:42  mmiers
 * LOG: Reorganization of the source tree.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:28  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:48:44  rsonak
 * LOG: Baseline port.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>

#include <itu/tcap.h>
#include <itu/isup.h>
#include <itu/inap.h>
#include <itu/INAP-types.h>

#include <its_stubs.h>
#include <its_ss7_stubs.h>

/*
 * undefine if running ISUP only
 */
#define TEST_TCAP	1 
/*
 * define if using both spans on a dual span SS7 board
 */
#define DUAL_SPAN	0

/*
 * get the user-defined message formats
 */
#include "user.h"


extern void	inap_msg(ITS_HANDLE handle, ITS_EVENT *event);
extern void	isup_msg(ITS_HANDLE handle, ITS_EVENT *event);


/*
 * regular shortcut
 */
#define ever	(;;)

/*
 * our context
 */
ITS_HANDLE handle;
ITS_UINT opc, dpc;
ITS_USHORT call_ref;

extern ITS_HDR inc_hdr;

/*
 * handle user messages
 */
static void
user_msg(ITS_HANDLE handle, ITS_EVENT *event)
{
    USER_MSG *umsg = (USER_MSG *)event->data;
    ITS_ISUP_IE ies[16];
    ITS_HDR hdr;
    ITS_USHORT dialogue_id = 4;
    TCAP_CPT cpt;
    TCAP_DLG dlg;
    ITS_OCTET digits[4] = { 0x27, 0x06, 0x86, 0x60 };

    printf("RECEIVED USER COMMAND: %d\n", umsg->command);
    switch (umsg->command) {
    case SEND_ACM:
	hdr.context.call_ref = call_ref;
	ies[0].param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
	ies[0].param_length = sizeof(ISUP_BKWD_CALL_INDICATORS);
	SET_BKWD_CI_BA_BITS(&ies[0].param_data.backwardCallIndicators, CHARGE);
	SET_BKWD_CI_DC_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);
	SET_BKWD_CI_FE_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);
	SET_BKWD_CI_HG_BITS(&ies[0].param_data.backwardCallIndicators, NO_ETE_METHOD);
	SET_BKWD_CI_I_BIT(&ies[0].param_data.backwardCallIndicators, NO_INTWK_ENCOUNTERED);
	SET_BKWD_CI_J_BIT(&ies[0].param_data.backwardCallIndicators, NO_ETE_INFO);
	SET_BKWD_CI_K_BIT(&ies[0].param_data.backwardCallIndicators, NO_ETE_INFO);
	SET_BKWD_CI_L_BIT(&ies[0].param_data.backwardCallIndicators, HOLDING_NOT_REQ);
	SET_BKWD_CI_M_BIT(&ies[0].param_data.backwardCallIndicators, TERM_ISDN);
	SET_BKWD_CI_N_BIT(&ies[0].param_data.backwardCallIndicators, DEVICE_NOT_INCL);
	SET_BKWD_CI_PO_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);

	printf("SEND ACM\n");
	ISUP_SendACMRequest(handle, &hdr, ies, 1);
	break;

    case SEND_ANM:
	hdr.context.call_ref = call_ref;
	printf("SEND ANM\n");
	ISUP_SendANMRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_CON:
	hdr.context.call_ref = call_ref;
	ies[0].param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
	ies[0].param_length = sizeof(ISUP_BKWD_CALL_INDICATORS);
	SET_BKWD_CI_BA_BITS(&ies[0].param_data.backwardCallIndicators, CHARGE);
	SET_BKWD_CI_DC_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);
	SET_BKWD_CI_FE_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);
	SET_BKWD_CI_HG_BITS(&ies[0].param_data.backwardCallIndicators, NO_ETE_METHOD);
	SET_BKWD_CI_I_BIT(&ies[0].param_data.backwardCallIndicators, NO_INTWK_ENCOUNTERED);
	SET_BKWD_CI_J_BIT(&ies[0].param_data.backwardCallIndicators, NO_ETE_INFO);
	SET_BKWD_CI_K_BIT(&ies[0].param_data.backwardCallIndicators, NO_ETE_INFO);
	SET_BKWD_CI_L_BIT(&ies[0].param_data.backwardCallIndicators, HOLDING_NOT_REQ);
	SET_BKWD_CI_M_BIT(&ies[0].param_data.backwardCallIndicators, TERM_ISDN);
	SET_BKWD_CI_N_BIT(&ies[0].param_data.backwardCallIndicators, DEVICE_NOT_INCL);
	SET_BKWD_CI_PO_BITS(&ies[0].param_data.backwardCallIndicators, NO_INDICATION);
	printf("SEND CON\n");
	ISUP_SendCONRequest(handle, &hdr, ies, 1);
	break;

    case SEND_CPG:
	hdr.context.call_ref = call_ref;
	ies[0].param_id = ISUP_PRM_EVENT_INFO;
	ies[0].param_length = sizeof(ISUP_EVENT_INFO);
	SET_EI_PRES_IND(&ies[0].param_data.eventInfo, EI_NO_INDICATION);
	SET_EI_INFO(&ies[0].param_data.eventInfo, EI_ALERTING);
	printf("SEND CPG: %d\n", sizeof(ISUP_EVENT_INFO));
	ISUP_SendCPGRequest(handle, &hdr, ies, 1);
	break;

    case SEND_IAM:
	hdr.context.call_ref = call_ref;

	ies[0].param_id = ISUP_PRM_NATURE_CONN_INDICATORS;
	ies[0].param_length = sizeof(ISUP_CONNECTION_INDICATORS);
	SET_CONN_IND_BA_BITS(&ies[0].param_data.connectionIndicator, NO_SATELLITE_CKT);
	SET_CONN_IND_DC_BITS(&ies[0].param_data.connectionIndicator, CHECK_NOT_REQUIRED);
	SET_CONN_IND_E_BIT(&ies[0].param_data.connectionIndicator, DEVICE_NOT_INCL);

	ies[1].param_id = ISUP_PRM_FWD_CALL_INDICATORS;
	ies[1].param_length = sizeof(ISUP_FORWARD_CALL_INDICATORS);
	SET_FWD_CI_A_BIT(&ies[1].param_data.forwardCallIndicators, NATNL_CALL);
	SET_FWD_CI_CB_BITS(&ies[1].param_data.forwardCallIndicators, NO_ETE_METHOD);
	SET_FWD_CI_D_BIT(&ies[1].param_data.forwardCallIndicators, NO_INTWK_ENCOUNTERED);
	SET_FWD_CI_E_BIT(&ies[1].param_data.forwardCallIndicators, NO_ETE_INFO);
	SET_FWD_CI_F_BIT(&ies[1].param_data.forwardCallIndicators, ISUP_ALL_WAY);
	SET_FWD_CI_HG_BITS(&ies[1].param_data.forwardCallIndicators, ISUP_PREFERRED);
	SET_FWD_CI_I_BIT(&ies[1].param_data.forwardCallIndicators, ORIG_ISDN);

	ies[2].param_id = ISUP_PRM_CALLING_PARTY_CATEGORY;
	ies[2].param_length = sizeof(ISUP_CALLING_PARTY_CATEGORY);
	ies[2].param_data.callingPartyCategory.cat = CPNG_ENGLISH;

	ies[3].param_id = ISUP_PRM_TX_MEDIUM_REQMNT;
	ies[3].param_length = sizeof(ISUP_TX_MEDIUM_REQUIREMENT);
	ies[3].param_data.txMediumRequirement.tmr = TMR_SPEECH;

	ies[4].param_id = ISUP_PRM_CALLED_PARTY_NUM;
	ies[4].param_length = sizeof(ISUP_CALLED_PARTY_NUM)+5;
	SET_CPN_ODD_EVEN_BIT(&ies[4].param_data.calledPartyNum, ODD_DIGITS);
	SET_CPN_ADDR_IND(&ies[4].param_data.calledPartyNum, CPN_SUBSCRIBER_NUM);
	SET_CPN_INN_BIT(&ies[4].param_data.calledPartyNum, ROUTING_INN_ALLOWED);
	SET_CPN_NUM_PLAN(&ies[4].param_data.calledPartyNum, ISDN_PLAN);
	memcpy(&ies[4].param_data.calledPartyNum.dgts, digits, sizeof(digits));
	       
	printf("SEND IAM\n");
	ISUP_SendIAMRequest(handle, &hdr, ies, 5);

	break;

    case SEND_REL:
	hdr.context.call_ref = call_ref;

	ies[0].param_id = ISUP_PRM_CAUSE_INDICATORS;
	ies[0].param_length = sizeof(ISUP_CAUSE_INDICATOR) - 1; /* Adjust for missing diag */
	SET_CI_EXT_IND(&ies[0].param_data.causeIndicator, CI_EXTEND);
	SET_CI_CODING_STANDARD(&ies[0].param_data.causeIndicator, CI_CS_CCITT);
	SET_CI_LOCATION(&ies[0].param_data.causeIndicator, CI_LOC_USER);
	SET_CI_CAUSE_EXT_IND(&ies[0].param_data.causeIndicator, CI_NO_EXTEND);
	SET_CI_CAUSE(&ies[0].param_data.causeIndicator, CI_CAUSE_NORMAL);
	printf("SEND REL\n");

	ISUP_SendRELRequest(handle, &hdr, ies, 1);
	break;

    case SEND_RLC:
	hdr.context.call_ref = call_ref;
	printf("SEND RLC\n");
	ISUP_SendRLCRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_BLO:
	hdr.context.call_ref = call_ref;
	printf("SEND BLO\n");
	ISUP_SendBLORequest(handle, &hdr, NULL, 0);
	break;

    case SEND_BLA:
	hdr.context.call_ref = call_ref;
	printf("SEND BLA\n");
	ISUP_SendBLARequest(handle, &hdr, NULL, 0);
	break;

    case SEND_UBL:
	hdr.context.call_ref = call_ref;
	printf("SEND UBL\n");
	ISUP_SendUBLRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_UBA:
	hdr.context.call_ref = call_ref;
	printf("SEND UBA\n");
	ISUP_SendUBARequest(handle, &hdr, NULL, 0);
	break;

    case SEND_CGB:
	hdr.context.call_ref = call_ref;
	printf("SEND CGB\n");
	ISUP_SendCGBRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_CGBA:
	hdr.context.call_ref = call_ref;
	printf("SEND CGBA\n");
	ISUP_SendCGBARequest(handle, &hdr, NULL, 0);
	break;

    case SEND_CGU:
	hdr.context.call_ref = call_ref;
	printf("SEND CGU\n");
	ISUP_SendCGURequest(handle, &hdr, NULL, 0);
	break;

    case SEND_CGUA:
	hdr.context.call_ref = call_ref;
	printf("SEND CGUA\n");
	ISUP_SendCGUARequest(handle, &hdr, NULL, 0);
	break;

    case SEND_GRS:
	hdr.context.call_ref = call_ref;
	printf("SEND GRS\n");
	ISUP_SendGRSRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_GRA:
	hdr.context.call_ref = call_ref;
	printf("SEND GRA\n");
	ISUP_SendGRARequest(handle, &hdr, NULL, 0);
	break;

    case SEND_RSC:
	hdr.context.call_ref = call_ref;
	printf("SEND RSC\n");
	ISUP_SendRSCRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_SUS:
	hdr.context.call_ref = call_ref;
	printf("SEND SUS\n");
	ISUP_SendSUSRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_RES:
	hdr.context.call_ref = call_ref;
	printf("SEND RES\n");
	ISUP_SendRESRequest(handle, &hdr, NULL, 0);
	break;

    case SEND_INVOKE1_CPT:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 1;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
	cpt.u.invoke.invoke_id.data[1] = 1;
	cpt.u.invoke.invoke_id.data[2] = 1;
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
	cpt.u.invoke.operation.data[1] = 1;
	cpt.u.invoke.operation.data[2] = 99;   /* integer op_code = 99 */
	cpt.u.invoke.operation.len = 3;

	cpt.u.invoke.param.len = 0;           /* no parameters */

	printf("SEND INVOKE_CPT\n");
	TCAP_SendComponent(handle, &hdr, &cpt);
	break;

    case SEND_INVOKE4_CPT:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;              /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;           /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
	cpt.u.invoke.invoke_id.data[1] = 1;
	cpt.u.invoke.invoke_id.data[2] = 1;
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
	cpt.u.invoke.operation.data[1] = 1;
	cpt.u.invoke.operation.data[2] = 100;   /* integer op_code = 100 */
	cpt.u.invoke.operation.len = 3;

	cpt.u.invoke.param.len = 0;           /* no parameters */

	printf("SEND INVOKE_CPT\n");
	TCAP_SendComponent(handle, &hdr, &cpt);
	break;

    case SEND_RL_CPT:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_RESULT_L;

	cpt.u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
	cpt.u.result.invoke_id.data[1] = 1;
	cpt.u.result.invoke_id.data[0] = 1;
	cpt.u.result.invoke_id.len = 3;

	cpt.u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
	cpt.u.result.operation.data[1] = 1;
	cpt.u.result.operation.data[2] = 99;     /* integer op_code = 99 */
	cpt.u.result.operation.len = 3;

	cpt.u.result.param.len = 6;             /* parameters length */
	cpt.u.result.param.data[0] = 0x04;      /* OCTET_STRING_TAG or tag = any ASN tag */
	cpt.u.result.param.data[1] = 4;
	cpt.u.result.param.data[2] = 'R';
	cpt.u.result.param.data[3] = 'R';
	cpt.u.result.param.data[4] = '-';
	cpt.u.result.param.data[5] = 'L';

	printf("SEND RL_CPT\n");
	TCAP_SendComponent(handle, &hdr, &cpt);
	break;

    case SEND_DLG_U_ABORT:
	memset(&dlg, 0, sizeof(dlg));

	TCAP_AllocateDialogueId(&dialogue_id);
        hdr.context.dialogue_id = dialogue_id;

	dlg.ptype = TCPPT_TC_U_ABORT;

	dlg.u.abort.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;

	dlg.u.abort.ac_name.len = 0;     /* no ac_name */
	dlg.u.abort.user_info.len = 0;   /* no user_info */

	printf("SEND U_ABORT\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case SEND_DLG_BEGIN:
	memset(&dlg, 0, sizeof(dlg));

	TCAP_AllocateDialogueId(&dialogue_id);
        hdr.context.dialogue_id = dialogue_id;

        dlg.ptype = TCPPT_TC_BEGIN;

	dlg.u.begin.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;

	dlg.u.begin.orig_addr.len = 4;
	dlg.u.begin.orig_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.begin.orig_addr.data[1] = opc & 0xFFU;  /* OPC */
	dlg.u.begin.orig_addr.data[2] = (opc >> 8) & 0x3FU;  /* OPC */
	dlg.u.begin.orig_addr.data[3] = 0x66; /* LSSN */

	dlg.u.begin.dest_addr.len = 4;
	dlg.u.begin.dest_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.begin.dest_addr.data[1] = dpc & 0xFFU;  /* DPC */
	dlg.u.begin.dest_addr.data[2] = (dpc >> 8) & 0x3FU;  /* DPC */
	dlg.u.begin.dest_addr.data[3] = 0x66; /* RSSN */

	dlg.u.begin.ac_name.len = 0;     /* no ac_name */
	dlg.u.begin.user_info.len = 0;   /* no user_info */
	dlg.u.begin.cpt_present = 1;

	printf("SEND BEGIN_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case SEND_DLG_CONT:
	memset(&dlg, 0, sizeof(dlg));

	/* dialogue id received */
	hdr.context.dialogue_id = dialogue_id;

	dlg.ptype = TCPPT_TC_CONTINUE;
	dlg.u.cont.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.cont.orig_addr.len = 0;                 /* no orig_addr */
	dlg.u.cont.ac_name.len = 0;                   /* no ac_name */
	dlg.u.cont.user_info.len = 0;                 /* no user_info */
	dlg.u.cont.cpt_present = 0;

	printf("SEND CONT_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case SEND_DLG_END:
	memset(&dlg, 0, sizeof(dlg));
	hdr.context.dialogue_id = dialogue_id;
	dlg.ptype = TCPPT_TC_END;
	dlg.u.end.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.end.termination = TCPEND_BASIC;         /* basic end */
	dlg.u.end.ac_name.len = 0;                    /* no ac_name */
	dlg.u.end.user_info.len = 0;                  /* no user_info */

	printf("SEND END_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case SEND_DLG_UNI:

	memset(&dlg, 0, sizeof(dlg));

	hdr.context.dialogue_id = dialogue_id;
	dlg.ptype = TCPPT_TC_UNI;

	dlg.u.uni.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.uni.ac_name.len = 0;         /* no ac_name */

	dlg.u.uni.orig_addr.len = 4;
	dlg.u.uni.orig_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.uni.orig_addr.data[1] = opc & 0xFFU;  /* OPC */
	dlg.u.uni.orig_addr.data[2] = (opc >> 8) & 0x3FU;  /* OPC */
	dlg.u.uni.orig_addr.data[3] = 0x66; /* LSSN */

	dlg.u.uni.dest_addr.len = 4;
	dlg.u.uni.dest_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.uni.dest_addr.data[1] = dpc & 0xFFU;  /* DPC */
	dlg.u.uni.dest_addr.data[2] = (dpc >> 8) & 0x3FU;  /* DPC */
	dlg.u.uni.dest_addr.data[3] = 0x66; /* RSSN */

	dlg.u.uni.user_info.len = 0;       /* no user_info */

	dlg.u.uni.cpt_present = 1;

	printf("SEND UNI_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case REPLY_RL_CPT:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_RESULT_L;

	cpt.u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
	cpt.u.result.invoke_id.data[1] = 1;
	cpt.u.result.invoke_id.data[0] = 1;
	cpt.u.result.invoke_id.len = 3;

	cpt.u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
	cpt.u.result.operation.data[1] = 1;
	cpt.u.result.operation.data[2] = 1;     /* integer op_code = 45 */
	cpt.u.result.operation.len = 3;

	cpt.u.result.param.len = 6;             /* parameters length */
	cpt.u.result.param.data[0] = 0x04;      /* OCTET_STRING_TAG or tag = any ASN tag */
	cpt.u.result.param.data[1] = 4;
	cpt.u.result.param.data[2] = 'R';
	cpt.u.result.param.data[3] = 'R';
	cpt.u.result.param.data[4] = '-';
	cpt.u.result.param.data[5] = 'L';

	printf("SEND RL_CPT\n");
	TCAP_SendComponent(handle, &hdr, &cpt);
	break;

    case REPLY_DLG_U_ABORT:
	memset(&dlg, 0, sizeof(dlg));

	hdr.context.dialogue_id = inc_hdr.context.dialogue_id;

	dlg.ptype = TCPPT_TC_U_ABORT;

	dlg.u.abort.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;

	dlg.u.abort.ac_name.len = 0;     /* no ac_name */
	dlg.u.abort.user_info.len = 0;   /* no user_info */

	printf("SEND U_ABORT\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case REPLY_DLG_CONT:
	memset(&dlg, 0, sizeof(dlg));

	/* dialogue id received */
	hdr.context.dialogue_id = inc_hdr.context.dialogue_id;

	dlg.ptype = TCPPT_TC_CONTINUE;
	dlg.u.cont.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.cont.orig_addr.len = 0;                 /* no orig_addr */
	dlg.u.cont.ac_name.len = 0;                   /* no ac_name */
	dlg.u.cont.user_info.len = 0;                 /* no user_info */
	dlg.u.cont.cpt_present = 0;

	printf("SEND CONT_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case REPLY_DLG_END:
	memset(&dlg, 0, sizeof(dlg));
	hdr.context.dialogue_id = inc_hdr.context.dialogue_id;
	dlg.ptype = TCPPT_TC_END;
	dlg.u.end.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.end.termination = TCPEND_BASIC;         /* basic end */
	dlg.u.end.ac_name.len = 0;                    /* no ac_name */
	dlg.u.end.user_info.len = 0;                  /* no user_info */

	printf("SEND END_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

    case REPLY_DLG_UNI:

	memset(&dlg, 0, sizeof(dlg));

	hdr.context.dialogue_id = inc_hdr.context.dialogue_id;
	dlg.ptype = TCPPT_TC_UNI;

	dlg.u.uni.qos.indicator = QOSI_RET_OPT | QOSI_SEQ_CTRL;
	dlg.u.uni.ac_name.len = 0;         /* no ac_name */

	dlg.u.uni.orig_addr.len = 4;
	dlg.u.uni.orig_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.uni.orig_addr.data[1] = opc & 0xFFU;  /* OPC */
	dlg.u.uni.orig_addr.data[2] = (opc >> 8) & 0x3FU;  /* OPC */
	dlg.u.uni.orig_addr.data[3] = 0x66; /* LSSN */

	dlg.u.uni.dest_addr.len = 4;
	dlg.u.uni.dest_addr.data[0] = 0x43; /* Address Ind */
	dlg.u.uni.dest_addr.data[1] = dpc & 0xFFU;  /* DPC */
	dlg.u.uni.dest_addr.data[2] = (dpc >> 8) & 0x3FU;  /* DPC */
	dlg.u.uni.dest_addr.data[3] = 0x66; /* RSSN */

	dlg.u.uni.user_info.len = 0;       /* no user_info */

	dlg.u.uni.cpt_present = 1;

	printf("SEND UNI_DLG\n");
	TCAP_SendDialogue(handle, &hdr, &dlg);
	break;

#if 0
    case SEND_CALL_INFO_REQ:
	{
	struct type_INAP_CallInformationRequestArg *arg;

	printf("SEND_CALL_INFO_REQ\n");
	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	/* strucures MUST be dynamically allocated.  The API will free
	 * the structures passed in.  DO NOT USE MALLOC() UNLESS YOU
	 * INITIALIZE EVERY FIELD!!!
	 */
	arg = calloc(1, sizeof(struct type_INAP_CallInformationRequestArg));

	arg->requestedInformationTypeList =
	    calloc(1, sizeof(struct element_INAP_65));
	arg->requestedInformationTypeList->next = NULL;

	arg->requestedInformationTypeList->element_INAP_66 =
	    int_INAP_element_INAP_66_releaseCause;

	/* operation and data are filled in in the API */
	INAP_SendCallInformationRequest(handle, &hdr, &cpt, (void *)arg);
	}
	break;
#endif

    case SEND_CALL_INFO_RES:
	{
	struct type_INAP_CallInformationReportArg *arg;

	printf("SEND_CALL_INFO_RES\n");
	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	/* just follow the structures down to what you need */
	arg = calloc(1, sizeof(struct type_INAP_CallInformationReportArg));

	arg->requestedInformationList =
	    calloc(1, sizeof(struct element_INAP_59));

	arg->requestedInformationList->element_INAP_60 =
	    calloc(1, sizeof(struct element_INAP_61));
	arg->requestedInformationList->next = NULL;

	arg->requestedInformationList->element_INAP_60->
	    requestedInformationValue =
	        calloc(1, sizeof(struct choice_INAP_17));

	arg->requestedInformationList->element_INAP_60->
	    requestedInformationType =
	        int_INAP_requestedInformationType_callAttemptElapsedTime;

	arg->requestedInformationList->element_INAP_60->
	    requestedInformationValue->offset =
	        choice_INAP_17_callAttemptElapsedTimeValue;
	arg->requestedInformationList->element_INAP_60->
	    requestedInformationValue->un.callAttemptElapsedTimeValue = 30;

	/* operation and data are filled in in the API */
	INAP_SendCallInformationReport(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_EVENT_REPORT_BCSM:
	{
	struct type_INAP_EventReportBCSMArg *arg;

	printf("SEND_EVENT_REPORT_BCSM\n");
	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_EventReportBCSMArg));

	arg->eventTypeBCSM = int_INAP_eventTypeBCSM_collectedInfo;

	/* operation and data are filled in in the API */
	INAP_SendEventReportBCSM(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_INITIAL_DP:
	{
	struct type_INAP_InitialDPArg *arg;
	ISUP_CALLED_PARTY_NUM dd;

	printf("SEND_INITIAL_DP\n");
	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 1;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_InitialDPArg));

	/* this is a qbuf.  The definition of DialedDigits comes from ISUP */
	arg->calledPartyNumber =
	    calloc(1, sizeof(struct qbuf));
	arg->calledPartyNumber->qb_len =
		sizeof(ISUP_CALLED_PARTY_NUM) + sizeof(digits) - 1;
	arg->calledPartyNumber->qb_data =
	    calloc(1, arg->calledPartyNumber->qb_len);

	SET_CPN_ODD_EVEN_BIT(&dd, ODD_DIGITS);
	SET_CPN_ADDR_IND(&dd, CPN_SUBSCRIBER_NUM);
	SET_CPN_INN_BIT(&dd, ROUTING_INN_ALLOWED);
	SET_CPN_NUM_PLAN(&dd, ISDN_PLAN);
	memcpy(arg->calledPartyNumber->qb_data, &dd, sizeof(ISUP_CALLED_PARTY_NUM)-1);
	memcpy(&arg->calledPartyNumber->qb_data[sizeof(ISUP_CALLED_PARTY_NUM)-1],
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->calledPartyNumber->qb_forw = arg->calledPartyNumber;
	arg->calledPartyNumber->qb_back = arg->calledPartyNumber;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendInitialDP(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_SERV_FILT_RES:
	{
	struct type_INAP_ServiceFilteringResponseArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ServiceFilteringResponseArg));

	arg->countersValue =
	    calloc(1, sizeof(struct element_INAP_257));
	arg->countersValue->element_INAP_258 =
	    calloc(1, sizeof(struct element_INAP_259));
	arg->countersValue->next = NULL;

	arg->countersValue->element_INAP_258->counterID = 17;

	arg->countersValue->element_INAP_258->counterValue = 66;

	arg->filteringCriteria =
	    calloc(1, sizeof(struct choice_INAP_63));
	arg->filteringCriteria->offset =
	    choice_INAP_63_callingLineID;

	/* this is a qbuf. */
	arg->filteringCriteria->un.callingLineID =
	    calloc(1, sizeof(struct qbuf));
	arg->filteringCriteria->un.callingLineID->qb_len = sizeof(digits);
	arg->filteringCriteria->un.callingLineID->qb_data =
	    calloc(1, arg->filteringCriteria->un.callingLineID->qb_len);

	memcpy(arg->filteringCriteria->un.callingLineID->qb_data,
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->filteringCriteria->un.callingLineID->qb_forw =
	    arg->filteringCriteria->un.callingLineID;
	arg->filteringCriteria->un.callingLineID->qb_back =
	    arg->filteringCriteria->un.callingLineID;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendServiceFilteringResponse(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_APPLY_CHARGE_REQ:
	{
	struct type_INAP_ApplyChargingArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ApplyChargingArg));

#define BILL	"Pay up!"
	arg->aChBillingChargingCharacteristics =
	    calloc(1, sizeof(struct qbuf));
	arg->aChBillingChargingCharacteristics->qb_len = strlen(BILL) + 1;
	arg->aChBillingChargingCharacteristics->qb_data =
	    calloc(1, arg->aChBillingChargingCharacteristics->qb_len);

	memcpy(arg->aChBillingChargingCharacteristics->qb_data,
	       BILL, strlen(BILL));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->aChBillingChargingCharacteristics->qb_forw =
	    arg->aChBillingChargingCharacteristics;
	arg->aChBillingChargingCharacteristics->qb_back =
	    arg->aChBillingChargingCharacteristics;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendApplyChargingRequest(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_APPLY_CHARGE_RES:
	{
	struct type_INAP_ApplyChargingReportArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ApplyChargingReportArg));

#define PAYED "He paid"

	arg->qb_len = strlen(PAYED) + 1;
	arg->qb_data = calloc(1, arg->qb_len);

	memcpy(arg->qb_data, PAYED, strlen(PAYED));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->qb_forw = arg;
	arg->qb_back = arg;

	/* operation and data are filled in in the API */
	INAP_SendApplyChargingReport(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_ACT_SERV_FILT:
	{
	struct type_INAP_ActivateServiceFilteringArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 1 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ActivateServiceFilteringArg));

	arg->filteredCallTreatment =
	    calloc(1, sizeof(struct element_INAP_0));

	arg->filteredCallTreatment->sFBillingChargingCharacteristics =
	    calloc(1, sizeof(struct qbuf));
#define SBILL "Want money"

	arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_len =
	    strlen(SBILL) + 1;
	arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_data =
	    calloc(1, arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_len);

	memcpy(arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_data,
	       SBILL, strlen(SBILL));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_forw =
	    arg->filteredCallTreatment->sFBillingChargingCharacteristics;
	arg->filteredCallTreatment->sFBillingChargingCharacteristics->qb_back =
	    arg->filteredCallTreatment->sFBillingChargingCharacteristics;

	arg->filteredCallTreatment->informationToSend =
	    calloc(1, sizeof(struct choice_INAP_0));
	arg->filteredCallTreatment->informationToSend->offset =
	    choice_INAP_0_tone;
	arg->filteredCallTreatment->informationToSend->un.tone =
	     calloc(1, sizeof(struct element_INAP_8));

	/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE
	 * this is an example of how to send an optional parameter */
	arg->filteredCallTreatment->informationToSend->un.tone->optionals =
	    opt_INAP_element_INAP_8_duration;
	arg->filteredCallTreatment->informationToSend->un.tone->toneID = 345;
	arg->filteredCallTreatment->informationToSend->un.tone->duration =
	     678;

	arg->filteringCharacteristics =
	     calloc(1, sizeof(struct choice_INAP_3));
	arg->filteringCharacteristics->offset =
	     choice_INAP_3_interval;
	arg->filteringCharacteristics->un.interval = 45;

	arg->filteringTimeOut =
	     calloc(1, sizeof(struct choice_INAP_4));
	arg->filteringTimeOut->offset =
	     choice_INAP_4_duration;
	arg->filteringTimeOut->un.duration = 15000;

	arg->filteringCriteria =
	    calloc(1, sizeof(struct choice_INAP_5));
	arg->filteringCriteria->offset =
	    choice_INAP_5_callingLineID;

	/* this is a qbuf. */
	arg->filteringCriteria->un.callingLineID =
	    calloc(1, sizeof(struct qbuf));
	arg->filteringCriteria->un.callingLineID->qb_len = sizeof(digits);
	arg->filteringCriteria->un.callingLineID->qb_data =
	    calloc(1, arg->filteringCriteria->un.callingLineID->qb_len);

	memcpy(arg->filteringCriteria->un.callingLineID->qb_data,
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->filteringCriteria->un.callingLineID->qb_forw =
	    arg->filteringCriteria->un.callingLineID;
	arg->filteringCriteria->un.callingLineID->qb_back =
	    arg->filteringCriteria->un.callingLineID;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendActivateServiceFiltering(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_ACTIVITY_TEST:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;               /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */
	/* operation and data are filled in in the API */
	INAP_SendActivityTest(handle, &hdr, &cpt, NULL);
	break;

    case SEND_CALL_GAP:
	{
	struct type_INAP_CallGapArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;               /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_CallGapArg));

	arg->gapCriteria =
	    calloc(1, sizeof(struct choice_INAP_9));
	arg->gapCriteria->offset =
	    choice_INAP_9_calledAddressValue;

	/* this is a qbuf. */
	arg->gapCriteria->un.calledAddressValue =
	    calloc(1, sizeof(struct qbuf));
	arg->gapCriteria->un.calledAddressValue->qb_len = sizeof(digits);
	arg->gapCriteria->un.calledAddressValue->qb_data =
	    calloc(1, arg->gapCriteria->un.calledAddressValue->qb_len);

	memcpy(arg->gapCriteria->un.calledAddressValue->qb_data,
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->gapCriteria->un.calledAddressValue->qb_forw =
	    arg->gapCriteria->un.calledAddressValue;
	arg->gapCriteria->un.calledAddressValue->qb_back =
	    arg->gapCriteria->un.calledAddressValue;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	arg->gapIndicators =
	    calloc(1, sizeof(struct element_INAP_38));
	arg->gapIndicators->duration = 5000;
	arg->gapIndicators->gapInterval = 6000;

	/* operation and data are filled in in the API */
	INAP_SendCallGap(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_CANCEL:
	{
	struct type_INAP_CancelArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_CancelArg));

	arg->offset = type_INAP_CancelArg_allRequests;

	/* operation and data are filled in in the API */
	INAP_SendCancel(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_CONNECT:
	{
	struct type_INAP_ConnectArg *arg;
	ISUP_CALLED_PARTY_NUM dd;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ConnectArg));

	arg->destinationRoutingAddress =
	    calloc(1, sizeof(struct element_INAP_85));
	arg->destinationRoutingAddress->next = NULL;

	/* this is a qbuf.  The definition of DialedDigits comes from ISUP */
	arg->destinationRoutingAddress->element_INAP_86 =
	    calloc(1, sizeof(struct qbuf));
	arg->destinationRoutingAddress->element_INAP_86->qb_len =
		sizeof(ISUP_CALLED_PARTY_NUM) + sizeof(digits) - 1;
	arg->destinationRoutingAddress->element_INAP_86->qb_data =
	    calloc(1, arg->destinationRoutingAddress->element_INAP_86->qb_len);

	SET_CPN_ODD_EVEN_BIT(&dd, ODD_DIGITS);
	SET_CPN_ADDR_IND(&dd, CPN_SUBSCRIBER_NUM);
	SET_CPN_INN_BIT(&dd, ROUTING_INN_ALLOWED);
	SET_CPN_NUM_PLAN(&dd, ISDN_PLAN);
	memcpy(arg->destinationRoutingAddress->element_INAP_86->qb_data, &dd, sizeof(ISUP_CALLED_PARTY_NUM)-1);
	memcpy(&arg->destinationRoutingAddress->element_INAP_86->qb_data[sizeof(ISUP_CALLED_PARTY_NUM)-1],
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->destinationRoutingAddress->element_INAP_86->qb_forw =
	    arg->destinationRoutingAddress->element_INAP_86;
	arg->destinationRoutingAddress->element_INAP_86->qb_back =
	    arg->destinationRoutingAddress->element_INAP_86;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendConnect(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_CONTINUE:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;               /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	/* operation and data are filled in in the API */
	INAP_SendContinue(handle, &hdr, &cpt, NULL);
	break;

    case SEND_DISC_FORW_CONN:
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	/* operation and data are filled in in the API */
	INAP_SendDisconnectForwardConnection(handle, &hdr, &cpt, NULL);
	break;

    case SEND_ESTAB_TEMP_CONN:
	{
	struct type_INAP_EstablishTemporaryConnectionArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_EstablishTemporaryConnectionArg));

	/* this is a qbuf. */
	arg->assistingSSPIPRoutingAddress =
	    calloc(1, sizeof(struct qbuf));
	arg->assistingSSPIPRoutingAddress->qb_len = sizeof(digits);
	arg->assistingSSPIPRoutingAddress->qb_data =
	    calloc(1, arg->assistingSSPIPRoutingAddress->qb_len);

	memcpy(arg->assistingSSPIPRoutingAddress->qb_data,
	       digits, sizeof(digits));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->assistingSSPIPRoutingAddress->qb_forw =
	    arg->assistingSSPIPRoutingAddress;
	arg->assistingSSPIPRoutingAddress->qb_back =
	    arg->assistingSSPIPRoutingAddress;
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

	/* operation and data are filled in in the API */
	INAP_SendEstablishTemporaryConnection(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_FURN_CHARG_INFO:
	{
	struct type_INAP_FurnishChargingInformationArg *arg;

printf("SEND FURN\n");
	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_FurnishChargingInformationArg));

#define SEND_BILL "Send bill"

	arg->qb_len = strlen(SEND_BILL) + 1;
	arg->qb_data = calloc(1, arg->qb_len);

	memcpy(arg->qb_data, SEND_BILL, arg->qb_len);

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->qb_forw = arg;
	arg->qb_back = arg;

	/* operation and data are filled in in the API */
	INAP_SendFurnishChargingInformation(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_RELEASE_CALL:
	{
	struct type_INAP_ReleaseCallArg *arg;
	ISUP_CAUSE_INDICATOR ci;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 4;               /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ReleaseCallArg));

	/* The Cause field comes from ISUP */
	arg->qb_len = sizeof(ISUP_CAUSE_INDICATOR) - 1; /* Adjust for missing diag */
	arg->qb_data = calloc(1, sizeof(ISUP_CAUSE_INDICATOR));

	SET_CI_EXT_IND(&ci, CI_EXTEND);
	SET_CI_CODING_STANDARD(&ci, CI_CS_CCITT);
	SET_CI_LOCATION(&ci, CI_LOC_USER);
	SET_CI_CAUSE_EXT_IND(&ci, CI_NO_EXTEND);
	SET_CI_CAUSE(&ci, CI_CAUSE_NORMAL);
	memcpy(arg->qb_data, &ci, arg->qb_len);

	arg->qb_forw = arg;
	arg->qb_back = arg;

	/* operation and data are filled in in the API */
	INAP_SendReleaseCall(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_REQ_RPT_BCSM_EVENT:
	{
	struct type_INAP_RequestReportBCSMEventArg *arg;
	struct element_INAP_224 *next_evt;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_RequestReportBCSMEventArg));

	arg->bcsmEvents =
	    calloc(1, sizeof(struct element_INAP_224));
	/* HERE'S THE CODE FOR A SEQUENCE.  Note that we are just chaining
	 * events into a singly linked list. */
	next_evt = calloc(1, sizeof(struct element_INAP_224));

	arg->bcsmEvents->element_INAP_225 =
	    calloc(1, sizeof(struct element_INAP_226));
	next_evt->element_INAP_225 =
	    calloc(1, sizeof(struct element_INAP_226));
	arg->bcsmEvents->next = next_evt; /* next event in the sequence */
	next_evt->next = NULL;

	arg->bcsmEvents->element_INAP_225->eventTypeBCSM =
	    int_INAP_eventTypeBCSM_collectedInfo;
	arg->bcsmEvents->element_INAP_225->monitorMode =
	    int_INAP_monitorMode_transparent;

	next_evt->element_INAP_225->eventTypeBCSM =
	    int_INAP_eventTypeBCSM_analysedInformation;
	next_evt->element_INAP_225->monitorMode =
	    int_INAP_monitorMode_transparent;

	/* operation and data are filled in in the API */
	INAP_SendRequestReportBCSMEvent(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    case SEND_RESET_TIMER:
	{
	struct type_INAP_ResetTimerArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.opClass = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ResetTimerArg));

	arg->timerID = int_INAP_timerID_tssf;

	arg->timervalue = 99;

	/* operation and data are filled in in the API */
	INAP_SendResetTimer(handle, &hdr, &cpt, (void *)arg);
	}
	break;

    default:
	printf("Invalid USER event\n");
	break;
    }
}

void
test_segv(int signal)
{
    printf("dintest task caught SIGSEGV\n");
    exit(0);
}

/*
 * test program entry point
 */
void
main(int argc, char **argv)
{
    ITS_EVENT event;
    ITS_EVENT uevent;
    USER_MSG *umsg = (USER_MSG *)uevent.data;
    char key_press;
    
    uevent.len = sizeof(USER_MSG);
    uevent.src = ITS_FIRST_USER_SRC;
    umsg->command = (unsigned char)SEND_RESET_TIMER;
    uevent.len = 2;
    
    /* initialize the context */
#if TEST_TCAP
    if ((handle = ITS_Initialize(ITS_ISUP|ITS_TCAP, 1)) == NULL) {
#else
    if ((handle = ITS_Initialize(ITS_ISUP, 1)) == NULL) {
#endif
        printf("Error initializing\n");
        exit(0);
    }
    
    
    /* go into the event loop */
    printf("\nEntering event loop\n\n");
    
    for ever
    {
        printf("LOOP\n");

        if (ITS_GetNextEvent(handle, &event) != ITS_SUCCESS)
        {
            printf("Error getting event\n");
            perror("because: ");
        }
        else
        {
            printf("Received event from: %d\n", event.src);
            switch (event.src) {
            case ITS_ISUP:
                isup_msg(handle, &event);
                break;
                
            case ITS_TCAP:
                inap_msg(handle, &event);
                break;
                
            case ITS_FIRST_USER_SRC:
                user_msg(handle, &event);
                break;
                
            default:
                fprintf(stderr, "Invalid event source: %d!\n", event.src);
                break;
            }
        } /* else */
        
        key_press = getchar();
        if (key_press == 'q')
        {
            ITS_Terminate(handle);
            
            exit(0);
        }
        
        user_msg(handle, &uevent);
        
        key_press = getchar();
        if (key_press == 'q')
        {
            ITS_Terminate(handle);
            
            exit(0);
        }
        
        
    } /* forever */
    
    /* NOTREACHED */
    exit(0);
}

