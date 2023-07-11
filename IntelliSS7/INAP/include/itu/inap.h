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
 *   (c);(1);(ii); of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: Daewoo testbed                                                 *
 *                                                                          *
 *     FILE: inap.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: inap.h,v 9.1 2005/03/23 12:51:42 cvsadmin Exp $
 *
 * LOG: $Log: inap.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:33  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:26  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:48  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:43  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1999/07/13 23:32:19  cbascon
 * LOG: Added helper functions for RequestCurrentStatusReportResult
 * LOG:
 * LOG: Revision 1.5  1999/06/16 19:29:50  jpakrasi
 * LOG: Added comments about INAP interface, which are genrated into html docs.
 * LOG:
 * LOG: Revision 1.4  1999/05/24 16:41:56  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize API.
 * LOG:
 * LOG: Revision 1.3  1998/05/04 22:57:31  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.2  1998/05/04 21:14:26  mmiers
 * LOG: Work on IS634.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:24  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:43:40  rsonak
 * LOG: New files
 * LOG:
 * LOG:
 * LOG: New file
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITU_INAP_H
#define _ITU_INAP_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * operation code values
 */
#define INAP_OP_initialDP                           0
#define INAP_OP_originationAttemptAuthorized        1
#define INAP_OP_collectedInformation                2
#define INAP_OP_analysedInformation                 3
#define INAP_OP_routeSelectFailure                  4
#define INAP_OP_oCalledPartyBusy                    5
#define INAP_OP_oNoAnswer                           6
#define INAP_OP_oAnswer                             7
#define INAP_OP_oDisconnect                         8
#define INAP_OP_termAttemptAuthorized               9
#define INAP_OP_tBusy                               10
#define INAP_OP_tNoAnswer                           11
#define INAP_OP_tAnswer                             12
#define INAP_OP_tDisconnect                         13
#define INAP_OP_oMidCall                            14
#define INAP_OP_tMidCall                            15
#define INAP_OP_assistRequestInstructions           16
#define INAP_OP_establishTemporaryConnection        17
#define INAP_OP_disconnectForwardConnection         18
#define INAP_OP_connectToResource                   19
#define INAP_OP_connect                             20
#define INAP_OP_holdCallInNetwork                   21
#define INAP_OP_releaseCall                         22
#define INAP_OP_requestReportBCSMEvent              23
#define INAP_OP_eventReportBCSM                     24
#define INAP_OP_requestNotificationChargingEvent    25
#define INAP_OP_eventNotificationCharging           26
#define INAP_OP_collectInformation                  27
#define INAP_OP_analyseInformation                  28
#define INAP_OP_selectRoute                         29
#define INAP_OP_selectFacility                      30
#define INAP_OP_continue                            31
#define INAP_OP_initiateCallAttempt                 32
#define INAP_OP_resetTimer                          33
#define INAP_OP_furnishChargingInformation          34
#define INAP_OP_applyCharging                       35
#define INAP_OP_applyChargingReport                 36
#define INAP_OP_requestCurrentStatusReport          37
#define INAP_OP_requestEveryStatusChangeReport      38
#define INAP_OP_requestFirstStatusMatchReport       39
#define INAP_OP_statusReport                        40
#define INAP_OP_callGap                             41
#define INAP_OP_activateServiceFiltering            42
#define INAP_OP_serviceFilteringResponse            43
#define INAP_OP_callInformationReport               44
#define INAP_OP_callInformationRequest              45
#define INAP_OP_sendChargingInformation             46
#define INAP_OP_playAnnouncement                    47
#define INAP_OP_promptAndCollectUserInformation     48
#define INAP_OP_specializedResourceReport           49
#define INAP_OP_cancel                              53
#define INAP_OP_cancelStatusReportRequest           54
#define INAP_OP_activityTest                        55
#define INAP_OP_requestCurrentStatusReportResult    56

/*
 * error codes
 */
#define INAP_ERR_cancelled                      0
#define INAP_ERR_cancelFailed                   1
#define INAP_ERR_eTCFailed                      3
#define INAP_ERR_improperCallerResponse         4
#define INAP_ERR_missingCustomerRecord          6
#define INAP_ERR_missingParameter               7
#define INAP_ERR_parameterOutOfRange            8
#define INAP_ERR_requestedInfoError             10
#define INAP_ERR_systemFailure                  11
#define INAP_ERR_taskRefused                    12
#define INAP_ERR_unavailableResource            13
#define INAP_ERR_unexpectedComponentSequence    14
#define INAP_ERR_unexpectedDataValue            15
#define INAP_ERR_unexpectedParameter            16
#define INAP_ERR_unknownLegID                   17
#define INAP_ERR_unknownResource                18

/*.interface:INAP
 ****************************************************************************
 *  Interface:
 *      INAP_*
 *
 *  Purpose:
 *      This interface defines the user's C programming model for the
 *      Intelligent Network Application Part (INAP). 
 *      It defines the intelligent network application protocol for the 
 *      support of the capabilities required by the CS-1 target services over 
 *      the CS-1 interfaces (SSF-SCF, SCF-SDF and SCF-SRF) as defined in 
 *      Recommendation Q.1211. 
 *
 *      It corresponds to the specifications detailed below:
 *         Intelligent Network
 *         Interface Recommendation for Intelligent Network
 *         Capabilities Set 1 (CS-1)
 *           ITU-T Recommendation Q.1218 (Issue: 10/95)
 *
 *  Usage:
 *      
 ****************************************************************************/

/*** CALL INFORMATION REQUEST ***/
int INAP_SendCallInformationRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data);
int INAP_DecodeCallInformationRequest(ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data);

/*** CALL INFORMATION REPORT ***/
int INAP_SendCallInformationReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data);
int INAP_DecodeCallInformationReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data);

/*** EVENT REPORT BCSM ***/
int INAP_SendEventReportBCSM(ITS_HANDLE handle, ITS_HDR *hdr,
                             TCAP_CPT *cpt, void *data);
int INAP_DecodeEventReportBCSM(ITS_HANDLE handle, TCAP_CPT *cpt,
                               void **data);

/*** INITIAL DP ***/
int INAP_SendInitialDP(ITS_HANDLE handle, ITS_HDR *hdr,
                       TCAP_CPT *cpt, void *data);
int INAP_DecodeInitialDP(ITS_HANDLE handle, TCAP_CPT *cpt,
                         void **data);

/*** SERVICE FILTERING RESPONSE ***/
int INAP_SendServiceFilteringResponse(ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data);
int INAP_DecodeServiceFilteringResponse(ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data);

/*** APPLY CHARGING REQUEST ***/
int INAP_SendApplyChargingRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data);
int INAP_DecodeApplyChargingRequest(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data);

/*** APPLY CHARGING REQUEST ***/
int INAP_SendApplyChargingReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data);
int INAP_DecodeApplyChargingReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data);

/*** ACTIVATE SERVICE FILTERING ***/
int INAP_SendActivateServiceFiltering(ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt, void *data);
int INAP_DecodeActivateServiceFiltering(ITS_HANDLE handle, TCAP_CPT *cpt,
                                        void **data);

/*** ACTIVITY TEST ***/
int INAP_SendActivityTest(ITS_HANDLE handle, ITS_HDR *hdr,
                          TCAP_CPT *cpt, void *data);
int INAP_DecodeActivityTest(ITS_HANDLE handle, TCAP_CPT *cpt,
                            void **data);

/*** CALL GAP ***/
int INAP_SendCallGap(ITS_HANDLE handle, ITS_HDR *hdr,
                     TCAP_CPT *cpt, void *data);
int INAP_DecodeCallGap(ITS_HANDLE handle, TCAP_CPT *cpt,
                       void **data);

/*** CANCEL ***/
int INAP_SendCancel(ITS_HANDLE handle, ITS_HDR *hdr,
                    TCAP_CPT *cpt, void *data);
int INAP_DecodeCancel(ITS_HANDLE handle, TCAP_CPT *cpt,
                      void **data);

/*** CONNECT ***/
int INAP_SendConnect(ITS_HANDLE handle, ITS_HDR *hdr,
                     TCAP_CPT *cpt, void *data);
int INAP_DecodeConnect(ITS_HANDLE handle, TCAP_CPT *cpt,
                       void **data);

/*** CONTINUE ***/
int INAP_SendContinue(ITS_HANDLE handle, ITS_HDR *hdr,
                      TCAP_CPT *cpt, void *data);
int INAP_DecodeContinue(ITS_HANDLE handle, TCAP_CPT *cpt,
                        void **data);

/*** DISCONNECT FORWARD CONNECTION ***/
int INAP_SendDisconnectForwardConnection(ITS_HANDLE handle, ITS_HDR *hdr,
                                         TCAP_CPT *cpt, void *data);
int INAP_DecodeDisconnectForwardConnection(ITS_HANDLE handle, TCAP_CPT *cpt,
                                           void **data);

/*** ESTABLISH TEMPORARY CONNECTION ***/
int INAP_SendEstablishTemporaryConnection(ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data);
int INAP_DecodeEstablishTemporaryConnection(ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data);

/*** FURNISH CHARGING INFORMATION ***/
int INAP_SendFurnishChargingInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data);
int INAP_DecodeFurnishChargingInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data);

/*** RELEASE CALL ***/
int INAP_SendReleaseCall(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data);
int INAP_DecodeReleaseCall(ITS_HANDLE handle, TCAP_CPT *cpt,
                           void **data);

/*** REQUEST REPORT ***/
int INAP_SendRequestReportBCSMEvent(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestReportBCSMEvent(ITS_HANDLE handle, TCAP_CPT *cpt,
                                      void **data);

/*** RESET TIMER ***/
int INAP_SendResetTimer(ITS_HANDLE handle, ITS_HDR *hdr,
                        TCAP_CPT *cpt, void *data);
int INAP_DecodeResetTimer(ITS_HANDLE handle, TCAP_CPT *cpt,
                          void **data);

/*** CONNECT TO RESOURCE ***/
int INAP_SendConnectToResource(ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data);
int INAP_DecodeConnectToResource(ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data);

/*** PROMPT AND COLLECT USER INFORMATION ***/
int INAP_SendPromptAndCollectUserInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                             TCAP_CPT *cpt, void *data);
int INAP_DecodePromptAndCollectUserInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                               void **data);

/*** RECEIVED INFORMATION ***/
int INAP_SendReceivedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data);
int INAP_DecodeReceivedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data);

/*** PLAY ANNOUNCEMENT ***/
int INAP_SendPlayAnnouncement(ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data);
int INAP_DecodePlayAnnouncement(ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data);

/*** ASSIST REQUEST INSTRUCTION ***/
int INAP_SendAssistRequestInstructions(ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data);
int INAP_DecodeAssistRequestInstructions(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data);

/*** SPECIALIZED RESOURCE REPORT ***/
int INAP_SendSpecializedResourceReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data);
int INAP_DecodeSpecializedResourceReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data);

/*** INITIATE CALL ATTEMPT ***/
int INAP_SendInitiateCallAttempt(ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data);
int INAP_DecodeInitiateCallAttempt(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data);

/*** SEND CHARGING INFORMATION ***/
int INAP_SendSendChargingInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt, void *data);
int INAP_DecodeSendChargingInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                       void **data);

/*** COLLECT INFORMATION ***/
int INAP_SendCollectInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data);
int INAP_DecodeCollectInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data);

/*** ANALYSE INFORMATION ***/
int INAP_SendAnalyseInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data);
int INAP_DecodeAnalyseInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data);

/*** EVENT NOTIFICATION CHARGING ***/
int INAP_SendEventNotificationCharging(ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data);
int INAP_DecodeEventNotificationCharging(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data);

/*** REQUEST CURRENT STATUS REPORT ***/
int INAP_SendRequestCurrentStatusReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                        TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestCurrentStatusReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                          void **data);

/*** REQUEST CURRENT STATUS REPORT RESULT ***/
int INAP_SendRequestCurrentStatusReportResult(ITS_HANDLE handle, ITS_HDR *hdr,
                                              TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestCurrentStatusReportResult(ITS_HANDLE handle,
                                                TCAP_CPT *cpt, void **data);

/*** REQUEST EVERY STATUS CHANGE REPORT ***/
int INAP_SendRequestEveryStatusChangeReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                            TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestEveryStatusChangeReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                              void **data);

/*** REQUEST FIRST STATUS MATCH REPORT ***/
int INAP_SendRequestFirstStatusMatchReport(ITS_HANDLE handle, ITS_HDR *hdr,
                                           TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestFirstStatusMatchReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                                             void **data);

/*** REQUEST NOTIFICATION CHARGING EVENT ***/
int INAP_SendRequestNotificationChargingEvent(ITS_HANDLE handle, ITS_HDR *hdr,
                                              TCAP_CPT *cpt, void *data);
int INAP_DecodeRequestNotificationChargingEvent(ITS_HANDLE handle, TCAP_CPT *cpt,
                                                void **data);

/*** SELECT FACILITY ***/
int INAP_SendSelectFacility(ITS_HANDLE handle, ITS_HDR *hdr,
                            TCAP_CPT *cpt, void *data);
int INAP_DecodeSelectFacility(ITS_HANDLE handle, TCAP_CPT *cpt,
                              void **data);

/*** STATUS REPORT ***/
int INAP_SendStatusReport(ITS_HANDLE handle, ITS_HDR *hdr,
                          TCAP_CPT *cpt, void *data);
int INAP_DecodeStatusReport(ITS_HANDLE handle, TCAP_CPT *cpt,
                            void **data);

/*** CANCEL STATUS REPORT REQUEST ***/
int INAP_SendCancelStatusReportRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                                       TCAP_CPT *cpt, void *data);
int INAP_DecodeCancelStatusReportRequest(ITS_HANDLE handle, TCAP_CPT *cpt,
                                         void **data);

/*** ROUTE SELECT FAILURE ***/
int INAP_SendRouteSelectFailure(ITS_HANDLE handle, ITS_HDR *hdr,
                                TCAP_CPT *cpt, void *data);
int INAP_DecodeRouteSelectFailure(ITS_HANDLE handle, TCAP_CPT *cpt,
                                  void **data);

/*** OCALLED PARTY BUSY ***/
int INAP_SendOCalledPartyBusy(ITS_HANDLE handle, ITS_HDR *hdr,
                              TCAP_CPT *cpt, void *data);
int INAP_DecodeOCalledPartyBusy(ITS_HANDLE handle, TCAP_CPT *cpt,
                                void **data);

/*** O NO ANSWER ***/
int INAP_SendONoAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                       TCAP_CPT *cpt, void *data);
int INAP_DecodeONoAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                         void **data);

/*** O ANSWER ***/
int INAP_SendOAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                     TCAP_CPT *cpt, void *data);
int INAP_DecodeOAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                       void **data);

/*** O DISCONNECT ***/
int INAP_SendODisconnect(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data);
int INAP_DecodeODisconnect(ITS_HANDLE handle, TCAP_CPT *cpt,
                           void **data);

/*** O TERM ATTEMPT AUTHORIZED ***/
int INAP_SendOTermAttempAuthorized(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_CPT *cpt, void *data);
int INAP_DecodeOTermAttempAuthorized(ITS_HANDLE handle, TCAP_CPT *cpt,
                                     void **data);

/*** T BUSY ***/
int INAP_SendTBusy(ITS_HANDLE handle, ITS_HDR *hdr,
                   TCAP_CPT *cpt, void *data);
int INAP_DecodeTBusy(ITS_HANDLE handle, TCAP_CPT *cpt,
                     void **data);

/*** T NO ANSWER ***/
int INAP_SendTNoAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                       TCAP_CPT *cpt, void *data);
int INAP_DecodeTNoAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                         void **data);

/*** T ANSWER ***/
int INAP_SendTAnswer(ITS_HANDLE handle, ITS_HDR *hdr,
                     TCAP_CPT *cpt, void *data);
int INAP_DecodeTAnswer(ITS_HANDLE handle, TCAP_CPT *cpt,
                       void **data);

/*** T DISCONNECT ***/
int INAP_SendTDisconnect(ITS_HANDLE handle, ITS_HDR *hdr,
                         TCAP_CPT *cpt, void *data);
int INAP_DecodeTDisconnect(ITS_HANDLE handle, TCAP_CPT *cpt,
                           void **data);

/*** O MID CALL ***/
int INAP_SendOMidCall(ITS_HANDLE handle, ITS_HDR *hdr,
                      TCAP_CPT *cpt, void *data);
int INAP_DecodeOMidCall(ITS_HANDLE handle, TCAP_CPT *cpt,
                        void **data);

/*** T MID CALL ***/
int INAP_SendTMidCall(ITS_HANDLE handle, ITS_HDR *hdr,
                      TCAP_CPT *cpt, void *data);
int INAP_DecodeTMidCall(ITS_HANDLE handle, TCAP_CPT *cpt,
                        void **data);

/*** HOLD CALL IN NETWORK ***/
int INAP_SendHoldCallInNetwork(ITS_HANDLE handle, ITS_HDR *hdr,
                               TCAP_CPT *cpt, void *data);
int INAP_DecodeHoldCallInNetwork(ITS_HANDLE handle, TCAP_CPT *cpt,
                                 void **data);

/*** ORIGINATION ATTEMPT AUTHORIZED ***/
int INAP_SendOriginationAttemptAuthorized(ITS_HANDLE handle, ITS_HDR *hdr,
                                          TCAP_CPT *cpt, void *data);
int INAP_DecodeOriginationAttemptAuthorized(ITS_HANDLE handle, TCAP_CPT *cpt,
                                            void **data);

/*** COLLECTED INFORMATION ***/
int INAP_SendCollectedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                  TCAP_CPT *cpt, void *data);
int INAP_DecodeCollectedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                    void **data);

/*** ANALYSED INFORMATION ***/
int INAP_SendAnalysedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                 TCAP_CPT *cpt, void *data);
int INAP_DecodeAnalysedInformation(ITS_HANDLE handle, TCAP_CPT *cpt,
                                   void **data);

#ifdef __cplusplus
}
#endif

#endif /* _ITU_INAP_H */
