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
 *     FILE: inap.c                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: inap.c,v 9.1 2005/03/23 12:51:45 cvsadmin Exp $
 *
 * LOG: $Log: inap.c,v $
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
 * LOG: Revision 3.1  2000/08/15 23:57:58  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:53  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/06/04 20:17:17  cmarchant
 * LOG:
 * LOG:
 * LOG: Build tests after updating ISUP code.
 * LOG:
 * LOG: Revision 1.3  1999/05/24 16:41:56  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize API.
 * LOG:
 * LOG: Revision 1.2  1999/05/24 15:49:09  mmiers
 * LOG:
 * LOG:
 * LOG: Update test code.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 15:39:37  mmiers
 * LOG: Reorganization of the source tree.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:27  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:48:36  rsonak
 * LOG: Baseline port.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include "..\include\itu\tcap.h"
#include "..\include\itu\inap.h"
#include "..\include\itu\INAP-types.h"

ITS_HDR inc_hdr;

/*
 * handle inap messages
 */
void
inap_msg(ITS_HANDLE handle, ITS_EVENT *event)
{
    TCAP_CPT cpt;
    TCAP_DLG dlg;
    void *data;

    switch (TCAP_MSG_TYPE(event)) {
    case ITS_TCAP_DLG:
	TCAP_ReceiveDialogue(handle, event, &inc_hdr, &dlg);
	break;

    case ITS_TCAP_CPT:
	TCAP_ReceiveComponent(handle, event, &inc_hdr, &cpt);

	if (cpt.ptype == TCPPT_TC_INVOKE) {
	    /* the op code */
	    switch (cpt.u.invoke.operation.data[2]) {
	    case INAP_OP_callInformationRequest:
		{
		struct type_INAP_CallInformationRequestArg *arg;

		/*
		 * GUYS>  This is what I was trying to tell you on the
		 * phone.  The pointer returned from the decode function
		 * will *actually* be the same type used to construct the
		 * data to encode.
		 */
		INAP_DecodeCallInformationRequest(handle, &cpt, (void *)&arg);

		/* SO: once you get it, you can play around with it */
		if (arg->requestedInformationTypeList->element_INAP_66
		     == int_INAP_element_INAP_66_releaseCause)
		{
		    printf("\nvalue=%d\n", int_INAP_element_INAP_66_releaseCause);
		}
		/* you get the idea.
		* So do with the data what you will */
		free_INAP_CallInformationRequestArg(arg);
		}
		break;

	    case INAP_OP_callInformationReport:
		INAP_DecodeCallInformationReport(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_CallInformationReportArg(data);
		break;

	    case INAP_OP_eventReportBCSM:
		INAP_DecodeEventReportBCSM(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_EventReportBCSMArg(data);
		break;

	    case INAP_OP_initialDP:
		INAP_DecodeInitialDP(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_InitialDPArg(data);
		break;

	    case INAP_OP_serviceFilteringResponse:
		INAP_DecodeServiceFilteringResponse(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ServiceFilteringResponseArg(data);
		break;

	    case INAP_OP_applyCharging:
		INAP_DecodeApplyChargingRequest(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ApplyChargingArg(data);
		break;

	    case INAP_OP_applyChargingReport:
		INAP_DecodeApplyChargingReport(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ApplyChargingReportArg(data);
		break;

	    case INAP_OP_activateServiceFiltering:
		INAP_DecodeActivateServiceFiltering(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ActivateServiceFilteringArg(data);
		break;

	    case INAP_OP_activityTest:
		/* this is a noop, and is included only for completeness */
		INAP_DecodeActivityTest(handle, &cpt, &data);
		/* do with it what you will */
		/* there is no free, as there is no data */
		break;

	    case INAP_OP_callGap:
		INAP_DecodeCallGap(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_CallGapArg(data);
		break;

	    case INAP_OP_cancel:
		INAP_DecodeCancel(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_CancelArg(data);
		break;

	    case INAP_OP_connect:
		INAP_DecodeConnect(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ConnectArg(data);
		break;

	    case INAP_OP_continue:
		/* this is a noop, and is included only for completeness */
		INAP_DecodeContinue(handle, &cpt, &data);
		/* do with it what you will */
		/* there is no free as there is no arg */
		break;

	    case INAP_OP_disconnectForwardConnection:
		/* this is a noop, and is included only for completeness */
		INAP_DecodeDisconnectForwardConnection(handle, &cpt, &data);
		/* do with it what you will */
		/* there is no free as there is no arg */
		break;

	    case INAP_OP_establishTemporaryConnection:
		INAP_DecodeEstablishTemporaryConnection(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_EstablishTemporaryConnectionArg(data);
		break;

	    case INAP_OP_furnishChargingInformation:
		INAP_DecodeFurnishChargingInformation(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_FurnishChargingInformationArg(data);
		break;

	    case INAP_OP_releaseCall:
		INAP_DecodeReleaseCall(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ReleaseCallArg(data);
		break;

	    case INAP_OP_requestReportBCSMEvent:
		INAP_DecodeRequestReportBCSMEvent(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_RequestReportBCSMEventArg(data);
		break;

	    case INAP_OP_resetTimer:
		INAP_DecodeResetTimer(handle, &cpt, &data);
		/* do with it what you will */
		free_INAP_ResetTimerArg(data);
		break;

	    default:
		printf("Got INVOKE: opcode: %d\n",
			cpt.u.invoke.operation.data[2]);
	    }
	}
	break;

    default:
	fprintf(stderr, "Invalid INAP message.\n");
    }
}

