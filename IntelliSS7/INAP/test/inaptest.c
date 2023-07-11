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
 *     FILE: test.c                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: inaptest.c,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
 *
 * LOG: $Log: inaptest.c,v $
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
 * LOG: Revision 2.0  1999/12/03 23:19:54  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/06/04 20:17:17  cmarchant
 * LOG:
 * LOG:
 * LOG: Build tests after updating ISUP code.
 * LOG:
 * LOG: Revision 1.2  1999/05/24 15:49:12  mmiers
 * LOG:
 * LOG:
 * LOG: Update test code.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 15:39:39  mmiers
 * LOG: Reorganization of the source tree.
 * LOG:
 * LOG: Revision 1.2  1998/01/24 22:36:56  mmiers
 * LOG: Tree cleanup.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:27  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:48:39  rsonak
 * LOG: Baseline port.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>

#include "..\include\itu\tcap.h"
#include "..\include\itu\inap.h"
#include "..\include\itu\INAP-types.h"
#include "..\include\itu\isup.h"

static void
testit()
{
	TCAP_CPT cpt;
	int dialogue_id = 4;
	ITS_HANDLE handle = (void *)1;
	ITS_HDR hdr;

#if 0

	struct type_INAP_CallInformationRequestArg *arg;

	printf("SEND CallInformationRequest\n");
	fflush(stdout);

	memset(&cpt, 0, sizeof(cpt));
	cpt.dialogue_id = dialogue_id;
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.class = 1;               /* ie. Class 1 operation */
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

	arg->requestedInformationTypeList->element_INAP_66 =
	    int_INAP_element_INAP_66_callAttemptElapsedTime;
	arg->requestedInformationTypeList->next = NULL;

	/* operation and data are filled in in the API */
	INAP_SendCallInformationRequest(handle, &hdr, &cpt, (void *)arg);

	struct type_INAP_FurnishChargingInformationArg *arg;

	memset(&cpt, 0, sizeof(cpt));
	cpt.dialogue_id = dialogue_id;
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.class = 3;               /* ie. Class 3 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_FurnishChargingInformationArg));

printf("SIZE: %d\n",
	sizeof(struct type_INAP_FurnishChargingInformationArg));
#define SEND_BILL "Send bill"

	arg->qb_len = strlen(SEND_BILL) + 1;
	arg->qb_data = calloc(1, arg->qb_len);

	memcpy(arg->qb_data, SEND_BILL, strlen(SEND_BILL));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 * qbufs (when sequences) are kept in a doubly-linked *CIRCULAR* list.
	 * FAILURE TO PERFORM THE FOLLOWING INITIALIZATION WILL RESULT IN
	 * A SIGSEGV.  THE LIBRARY REQUIRES THIS CODE.
	 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	arg->qb_forw = arg;
	arg->qb_back = arg;


	/* operation and data are filled in in the API */
	INAP_SendFurnishChargingInformation(handle, &hdr, &cpt, (void *)arg);

	struct type_INAP_ActivateServiceFilteringArg *arg;
	unsigned char digits[4] = { 0x27, 0x06, 0x86, 0x06 }; /* "726-0686" (odd) */

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
	arg->filteredCallTreatment->informationToSend->un.tone->toneID = 345;

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
	
	struct type_INAP_ReleaseCallArg *arg;
	CauseInd ci;

	memset(&cpt, 0, sizeof(cpt));
	cpt.dialogue_id = dialogue_id;
	cpt.ptype = TCPPT_TC_INVOKE;
	cpt.u.invoke.class = 4;               /* ie. Class 4 operation */
	cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

	cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
	cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
	cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
	cpt.u.invoke.invoke_id.len = 3;

	cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

	arg = calloc(1, sizeof(struct type_INAP_ReleaseCallArg));

	/* The Cause field comes from ISUP */
	arg->qb_len = sizeof(CauseInd) - 1; /* Adjust for missing diag */
	arg->qb_data = calloc(1, sizeof(CauseInd));

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
#else
	struct type_INAP_InitialDPArg *arg;
	ISUP_CALLED_PARTY_NUM dd;
	char digits[4] = { 0x27, 0x06, (char)0x86, 0x06 }; /* "726-0686" (odd) */

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
	arg->calledPartyNumber->qb_forw = arg->calledPartyNumber;
	arg->calledPartyNumber->qb_back = arg->calledPartyNumber;

	/* operation and data are filled in in the API */
	INAP_SendInitialDP(handle, &hdr, &cpt, (void *)arg);

#endif
}


int
TCAP_SendComponent(ITS_HANDLE handle, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    void *data;
    int i;

#if 0
    printf("DECODE CallInformationRequest\n");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
	printf("%02x\n", cpt->u.invoke.param.data[i]);
    INAP_DecodeCallInformationRequest(handle, cpt, &data);

    printf("DECODE ActivateServiceFiltering\n");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
	printf("%02x\n", cpt->u.invoke.param.data[i]);
    INAP_DecodeActivateServiceFiltering(handle, cpt, &data);

    printf("DECODE ReleaseCall\n");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
	printf("%02x\n", cpt->u.invoke.param.data[i]);
    INAP_DecodeReleaseCall(handle, cpt, &data);

    printf("DECODE FurnishChargingInformation\n");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
	printf("%02x\n", cpt->u.invoke.param.data[i]);
    INAP_DecodeFurnishChargingInformation(handle, cpt, &data);
#else

    printf("DECODE InitialDP\n");
    for (i = 0; i < cpt->u.invoke.param.len; i++)
	printf("%02x\n", cpt->u.invoke.param.data[i]);
    INAP_DecodeInitialDP(handle, cpt, &data);

#endif

    return 0;
}


int
main(int argc, char **argv)
{
	testit();
#if 1
	printf("inhale\n");
	testit();
	printf("exhale\n");
	testit();
	printf("inhale\n");
	testit();
	printf("exhale\n");
	testit();
	printf("inhale\n");
	testit();
	printf("exhale\n");
	testit();
#endif
	getchar();
	return EXIT_SUCCESS;
}


