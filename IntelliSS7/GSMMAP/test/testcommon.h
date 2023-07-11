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
 * CONTRACT: IntelliSS7                                                     *
 *                                                                          *
 *     FILE: testcommon.h                                                   *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: testcommon.h,v 9.1 2005/03/23 12:51:31 cvsadmin Exp $
 *
 * LOG: $Log: testcommon.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:50  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:20  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:21  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:09  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:10  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1998/09/14 15:30:59  ite
 * LOG: Tested successfully on NMS hardware. This version sent to Nokia for trials.
 * LOG:
 *
 ****************************************************************************/

#ifndef TEST_COMMON_H_
#define TEST_COMMON_H_

#define TEST_MIN_MSG        0
#define TEST_UPDLOC         TEST_MIN_MSG + 1 /* updateLocation */
#define TEST_CANCLOC        TEST_MIN_MSG + 2 /* cancelLocation */
#define TEST_PURGEMS        TEST_MIN_MSG + 3 /* purgeMS */
#define TEST_SENDID         TEST_MIN_MSG + 4 /* sendIdentification */
#define TEST_PERFORMHO      TEST_MIN_MSG + 5 /* performHandover */
#define TEST_PREPAREHO      TEST_MIN_MSG + 6 /* prepareHandover */
#define TEST_SENDENDSIG     TEST_MIN_MSG + 7 /* sendEndSignal */
#define TEST_PROCACCSIG     TEST_MIN_MSG + 8 /* processAccessSignalling */
#define TEST_FORWACCSIG     TEST_MIN_MSG + 9 /* forwardAccessSignalling */
#define TEST_PERFORMSHO     TEST_MIN_MSG + 10 /* performSubsequentHandover */
#define TEST_PREPARESHO     TEST_MIN_MSG + 11 /* prepareSubsequentHandover */
#define TEST_SENDAUTHINFO   TEST_MIN_MSG + 12 /* sendAuthenticationInfo */
#define TEST_CHECKIMEI      TEST_MIN_MSG + 13 /* checkIMEI */
#define TEST_SENDPARAMS     TEST_MIN_MSG + 14 /* sendParameters */
#define TEST_INSSUBSDATA    TEST_MIN_MSG + 15 /* insertSubscriberData */
#define TEST_DELSUBADATA    TEST_MIN_MSG + 16 /* deleteSubscriberData */
#define TEST_RESET          TEST_MIN_MSG + 17 /* reset */
#define TEST_FORWSSIND      TEST_MIN_MSG + 18 /* forwardCheckSS_Indication */
#define TEST_RESTDATA       TEST_MIN_MSG + 19 /* restoreData */
#define TEST_ACTTRMODE      TEST_MIN_MSG + 20 /* activateTraceMode */
#define TEST_DEACTTRMODE    TEST_MIN_MSG + 21 /* deactivateTraceMode */
#define TEST_TRACSUBSACTV   TEST_MIN_MSG + 22 /* traceSubscriberActivity */
#define TEST_NOTEINTHO      TEST_MIN_MSG + 23 /* noteInternalHandover */
#define TEST_SENDIMSI       TEST_MIN_MSG + 24 /* sendIMSI */
#define TEST_SENDRTINFO     TEST_MIN_MSG + 25 /* sendRoutingInfo */
#define TEST_PROVIDERN      TEST_MIN_MSG + 26 /* provideRoamingNumber */
#define TEST_REGSS          TEST_MIN_MSG + 27 /* registerSS */
#define TEST_ERASESS        TEST_MIN_MSG + 28 /* eraseSS */
#define TEST_ACTSS          TEST_MIN_MSG + 29 /* activateSS */
#define TEST_DEACTSS        TEST_MIN_MSG + 30 /* deactivateSS */
#define TEST_INTRRSS        TEST_MIN_MSG + 31 /* interrogateSS */
#define TEST_PROCUSSDATA    TEST_MIN_MSG + 32 /* processUnstructuredSS_Data */
#define TEST_PROCUSSREQ     TEST_MIN_MSG + 33 /* processUnstructuredSS_Request */
#define TEST_USSREQ         TEST_MIN_MSG + 34 /* unstructuredSS_Request */
#define TEST_USSNOT         TEST_MIN_MSG + 35 /* unstructuredSS_Notify */
#define TEST_REGPSSWD       TEST_MIN_MSG + 36 /* registerPassword */
#define TEST_GETPSSWD       TEST_MIN_MSG + 37 /* getPassword */
#define TEST_BEGSUBSACTV    TEST_MIN_MSG + 38 /* beginSubscriberActivity */
#define TEST_SENDRTINFOSM   TEST_MIN_MSG + 39 /* sendRoutingInfoForSM */
#define TEST_FORWSM         TEST_MIN_MSG + 40 /* forwardSM */
#define TEST_RPTSMSTATUS    TEST_MIN_MSG + 41 /* reportSM_DeliveryStatus */
#define TEST_NOTESUBSPRES   TEST_MIN_MSG + 42 /* noteSubscriberPresent */
#define TEST_ALRTSCWR       TEST_MIN_MSG + 43 /* alertServiceCentreWithoutResult */
#define TEST_INFRMSC        TEST_MIN_MSG + 44 /* informServiceCentre  */
#define TEST_ALRTSC         TEST_MIN_MSG + 45 /* alertServiceCentre */
#define TEST_RDYFORSM       TEST_MIN_MSG + 46 /* readyForSM */

#define TEST_EXIT           TEST_MIN_MSG + 47 /* Exit the test program */
#define TEST_MAX_MSG        TEST_EXIT + 1

/*
 * Some return/error codes within this test module.
 */
#define TEST_NOT_IMPL       100
#define TEST_BAD_MSG        101

/* Defined in test1SendInvoke.c */
int TEST_SendGSMMAPInvoke(int cmdInput, int *replyExpected, ITS_HANDLE handle);

/* Defined in test1SendResult.c */
int TEST_SendGSMMAPResult(ITS_HDR *hdr, TCAP_CPT *cpt, ITS_HANDLE handle);

/* Defined in test1DecodeResult.c */
int TEST_DecodeGSMMAPResult( TCAP_CPT *cpt, ITS_HANDLE handle );

/* Defined in file test1DecodeInvoke.c. */
int TEST_DecodeInvoke( TCAP_CPT *cpt, ITS_HANDLE handle );

#endif
