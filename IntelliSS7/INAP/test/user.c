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
 *     FILE: user2.c                                                        *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: user.c,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
 *
 * LOG: $Log: user.c,v $
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
 * LOG: Revision 3.1  2000/08/15 23:58:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:57  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/05/24 15:49:16  mmiers
 * LOG:
 * LOG:
 * LOG: Update test code.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 15:39:43  mmiers
 * LOG: Reorganization of the source tree.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:28  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:48:45  rsonak
 * LOG: Baseline port.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <din_api.h>

/*
 * get the user-defined message formats
 */
#include "user.h"

/*
 * regular shortcut
 */
#define ever	(;;)

/*
 * catch SIGSEGV
 */
void
user_segv(int signal)
{
    printf("User task received SIGSEGV\n");
    exit(0);
}


#if 0
/*
 * remember that this is a process even if it looks like a function
 */
void
main(int argc, char **argv)
{
    DIN_EVENT uevent;
    USER_MSG *umsg = (USER_MSG *)uevent.data;
    int command, cic;
    DIN_IE ies[5];
    mqd_t q;
    char buf[128];

    signal(SIGSEGV, user_segv);

    uevent.len = sizeof(USER_MSG);
    uevent.src = DIN_USER;

    sprintf(buf, QUEUE_NAME, 0);

    q = mq_open(buf, O_WRONLY);
    if (q == -1) {
	fprintf(stderr, "User test can't open message queue!\n");
	exit(0);
    }

    for ever {

	printf("Select an option:\n");
	printf("   %d) Send ACM   %d) Send ANM   %d) Send CPG   %d) Send CON\n",
		SEND_ACM, SEND_ANM, SEND_CPG, SEND_CON);
	printf("   %d) Send IAM   %d) Send REL   %d) Send RLC   %d) Send BLO\n",
		SEND_IAM, SEND_REL, SEND_RLC, SEND_BLO);
	printf("   %d) Send BLA   %d)  Send UBL  %d)  Send UBA  %d) Send CGB\n",
		SEND_BLA, SEND_UBL, SEND_UBA, SEND_CGB);
	printf("   %d) Send CGBA  %d)  Send CGU  %d)  Send CGUA %d) Send RSC\n",
		SEND_CGBA, SEND_CGU, SEND_CGUA, SEND_RSC);
	printf("   %d) Send SUS  %d)  Send RES   %d)  Send GRS  %d) Send GRA\n",
		SEND_SUS, SEND_RES, SEND_GRS, SEND_GRA);
	printf("    %d)  Send class 1 INVOKE_CPT (for TC-BEGIN)\n", SEND_INVOKE1_CPT);
	printf("    %d)  Send class 4 INVOKE_CPT (for TC-UNI)\n", SEND_INVOKE4_CPT);
	printf("    %d)  Send RL_CPT\n", SEND_RL_CPT);
	printf("    %d)  Send DLG_U_ABORT  %d)  Send DLG_BEGIN\n", SEND_DLG_U_ABORT, SEND_DLG_BEGIN);
	printf("    %d)  Send DLG_CONT     %d)  Send DLG_END\n", SEND_DLG_CONT, SEND_DLG_END);
	printf("    %d)  Send DLG_UNI\n", SEND_DLG_UNI);
	printf("    %d)  Reply RL_CPT\n", REPLY_RL_CPT);
	printf("    %d)  Reply DLG_U_ABORT %d)  Reply DLG_CONT\n", REPLY_DLG_U_ABORT, REPLY_DLG_CONT);
	printf("    %d)  Reply DLG_UNI\n", REPLY_DLG_UNI);
	printf("    %d)  Send CALL_INFO_REQ %d) Send CALL_INFO_RES\n", SEND_CALL_INFO_REQ, SEND_CALL_INFO_RES);
	printf("    %d)  Send EVT_RPT_BCSM  %d) Send INITIAL_DP\n", SEND_EVENT_REPORT_BCSM, SEND_INITIAL_DP);
	printf("    %d)  Send APPL_CHG_REQ  %d) Send APPL_CHG_RES\n", SEND_APPLY_CHARGE_REQ, SEND_APPLY_CHARGE_RES);
	printf("    %d)  Send ACT_SERV_FILT %d) Send SERV_FILT_RES\n", SEND_ACT_SERV_FILT, SEND_SERV_FILT_RES);
	printf("    %d)  Send CALL_GAP      %d) Send CANCEL\n", SEND_CALL_GAP, SEND_CANCEL);
	printf("    %d)  Send CONNECT       %d) Send CONTINUE\n", SEND_CONNECT, SEND_CONTINUE);
	printf("    %d)  Send DISC_FORW_CON %d) Send ESTAB_TEMP_CONN\n", SEND_DISC_FORW_CONN, SEND_ESTAB_TEMP_CONN);
	printf("    %d)  Send FURN_CHAR_INF %d) Send RELEASE_CALL\n", SEND_FURN_CHARG_INFO, SEND_RELEASE_CALL);
	printf("    %d)  Send REQ_RPT_BCSM  %d) Send RESET_TIMER\n", SEND_REQ_RPT_BCSM_EVENT, SEND_RESET_TIMER);
	printf("    %d)  Send DTMF digits   %d) Get single digit\n", SEND_TGTD_DIAL_DTMF, SEND_TGTD_GET_DTMF);
	printf("    %d)  Get digit string   %d) Record file\n", SEND_TGTD_GET_DTMFSTRING, SEND_TGTD_RECORD_FILE);
	printf("    %d)  Play file\n", SEND_TGTD_PLAY_FILE);
	printf("\n> ");
	scanf("%d %d", &command, &cic);

        printf("sent command %d to q %d\n", command, q);

	umsg->command = (unsigned char)command;

	if ((command == SEND_TGTD_DIAL_DTMF) ||
	    (command == SEND_TGTD_GET_DTMF) ||
	    (command == SEND_TGTD_GET_DTMFSTRING) ||
	    (command == SEND_TGTD_RECORD_FILE) ||
	    (command == SEND_TGTD_PLAY_FILE)) {
	    umsg->call_ref = (unsigned short)cic;
            printf("sent command %d for CIC %d to q %d\n", 
		    command, cic, q);
	}

	/* A switch isn't really needed here, but you could customize the
	 * user messages this way. */
	switch (command) {
	case SEND_ACM: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_ANM: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CPG: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CON: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_IAM: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_REL: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RLC: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_BLO: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_BLA: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_UBL: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_UBA: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CGB: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CGBA: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CGU: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CGUA: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_GRS: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_GRA: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RSC: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_SUS: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RES: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_INVOKE1_CPT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_INVOKE4_CPT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RL_CPT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DLG_U_ABORT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DLG_BEGIN: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DLG_CONT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DLG_END: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DLG_UNI: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case REPLY_RL_CPT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case REPLY_DLG_U_ABORT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case REPLY_DLG_CONT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case REPLY_DLG_END: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case REPLY_DLG_UNI: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CALL_INFO_REQ: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CALL_INFO_RES: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_EVENT_REPORT_BCSM: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_INITIAL_DP: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_APPLY_CHARGE_REQ: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_APPLY_CHARGE_RES: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_ACT_SERV_FILT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_SERV_FILT_RES: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_ACTIVITY_TEST: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CALL_GAP: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CANCEL: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CONNECT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_CONTINUE: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_DISC_FORW_CONN: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_ESTAB_TEMP_CONN: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_FURN_CHARG_INFO: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RELEASE_CALL: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_REQ_RPT_BCSM_EVENT: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_RESET_TIMER: 
	    uevent.len = 2;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_TGTD_DIAL_DTMF:
	    uevent.len = 4;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_TGTD_GET_DTMF:
	    uevent.len = 4;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_TGTD_GET_DTMFSTRING:
	    uevent.len = 4;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_TGTD_RECORD_FILE:
	    uevent.len = 4;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	case SEND_TGTD_PLAY_FILE:
	    uevent.len = 4;
	    mq_send(q, (char *)&uevent.src, uevent.len, 0);
	    break;

	default:
	    printf("Invalid option.\n");
	    break;
	}
    }
}
#endif
