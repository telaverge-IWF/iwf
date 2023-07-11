/*
 ****************************************************************************
 * DISCLAIMER:
 *
 * INTELLINET DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
 * INTELLINET BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *  
 ****************************************************************************/

#ifndef INAP_TEST_H
#define INAP_TEST_H

#include <itu/tcap.h>
#include <asn-c/AsnC.h>


/* The instance number set for Send application and the Receive Application */
#define TEST_SEND_INSTANCE      1
#define TEST_RECEIVE_INSTANCE   2


/* Tags for messages */
#define TEST_EXIT               -1
#define TEST_CONTINUE           0
#define TEST_SCCP_UIS           1
#define TEST_SCCP_UOS           2
#define TEST_WAIT_FOR_EVENT     3
#define TEST_NO_WAIT            4


/* Used for sending an INAP response when an invoke is received */
#define TEST_INAP_RESPONSE      10

/* Component response tags */
#define TEST_TCAP_RESULT_L      11
#define TEST_TCAP_RESULT_NL     12
#define TEST_TCAP_U_ERROR       13
#define TEST_TCAP_L_CANCEL      14
#define TEST_TCAP_U_CANCEL      15
#define TEST_TCAP_L_REJECT      16
#define TEST_TCAP_R_REJECT      17
#define TEST_TCAP_U_REJECT      18


/* Dialog response tags */
#define TEST_TCAP_BEGIN         20
#define TEST_TCAP_CONTINUE      21
#define TEST_TCAP_END           22
#define TEST_TCAP_NOTICE        23
#define TEST_TCAP_P_ABORT       24
#define TEST_TCAP_U_ABORT       25
#define TEST_TCAP_UNI           26


/* Menus */
void SendProgramMainMenu();
void SendINAPMessageMenu();
void ReceiveProgramMainMenu();
void ResponseMenu();


/* Get user input */
int getYesOrNo();
int getSelection (int startRange, int endRange);


/* Get SCCP address from user */
int getSCCPAddr(SCCP_ADDR *addr);


/* ITS Initialize functions */
ITS_HANDLE initSendHandle();
ITS_HANDLE initReceiveHandle();


/* Wait for ITS Event function */
int waitForEvent(ITS_HANDLE handle, ITS_HDR *waitHeader,
                 TCAP_CPT *recvComponent);


/* Send Dialog functions */
int sendTCAPBeginDlg(ITS_HANDLE handle, ITS_HDR *header, TCAP_DLG *dlg,
                     int cpt_present);

int sendTCAPContinueDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
                        SCCP_ADDR *orig_addr);

int sendTCAPEndDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
                   int termination);

int sendTCAPUAbortDlg(ITS_HANDLE handle, ITS_HDR *header);

int sendTCAPUniDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
                   SCCP_ADDR orig_addr, SCCP_ADDR dest_addr);


/* Send component functions */
int sendTCAPRejectCpt(ITS_HANDLE handle, ITS_HDR *header,
                      CPT_INV_ID *invoke_id);

int sendTCAPErrorCpt(ITS_HANDLE handle, ITS_HDR *header,
                     CPT_INV_ID *invoke_id);

int sendTCAPResultCpt(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt);

int sendTCAPUCancelCpt(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt);


/* Send INAP invoke */
int SelectINAPMessageToSend(ITS_HANDLE handle, ITS_HDR header, TCAP_CPT *cpt);


/* Send Response to an INAP Invoke */
void respondToINAPMessage(ITS_HANDLE handle, ITS_HDR *header,
                          TCAP_CPT *recvCpt, SCCP_ADDR *orig_addr);

int responseToCallGap(ITS_HANDLE handle, ITS_HDR *header);

int responseToCallInformationRequest(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *recvCpt);

int responseToCancelStatusReportRequest(ITS_HANDLE handle, ITS_HDR *header);

int responseToConnect(ITS_HANDLE handle, ITS_HDR *header);

int responseToInitialDP(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt,
                        SCCP_ADDR *orig_addr);

int responseToRequestCurrentStatusReport(ITS_HANDLE handle, ITS_HDR *header,
                                         TCAP_CPT *recvCpt,
                                         SCCP_ADDR *orig_addr);

int responseToRequestEveryStatusChangeReport(ITS_HANDLE handle,
                                             ITS_HDR *header,
                                             TCAP_CPT *recvCpt,
                                             SCCP_ADDR *orig_addr);

int responseToRequestFirstStatusMatchReport(ITS_HANDLE handle, ITS_HDR *header,
                                            TCAP_CPT *recvCpt,
                                            SCCP_ADDR *orig_addr);

int responseToRequestReportBCSMEvent(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *recvCpt);


/* Send SCCP Message functions */
int sendUserOutOfService(ITS_HANDLE handle, SCCP_ADDR orig);
int sendUserInService(ITS_HANDLE handle, SCCP_ADDR orig);


/* INAP Message send functions */
int sendCallGapArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendCallInformationReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                 TCAP_CPT *cpt);

int sendCallInformationRequestArg(ITS_HANDLE handle, ITS_HDR *header,
                                  TCAP_CPT *cpt);

int sendCancelStatusReportRequestArg(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *cpt);

int sendConnectArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendContinueArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendEventReportBCSMArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendInitialDPArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendReleaseCallArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);

int sendRequestCurrentStatusReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                      TCAP_CPT *cpt);

int sendRequestCurrentStatusReportResult(ITS_HANDLE handle, ITS_HDR *header,
                                         TCAP_CPT *cpt);

int sendRequestEveryStatusChangeReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                          TCAP_CPT *cpt);

int sendRequestFirstStatusMatchReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                         TCAP_CPT *cpt);

int sendRequestReportBCSMEventArg(ITS_HANDLE handle, ITS_HDR *header,
                                  TCAP_CPT *cpt);

int sendStatusReportArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt);


/* Decode function */
int decodeINAPMessage(ITS_HANDLE handle, TCAP_CPT *cpt);


/* Dialog trace functions */
void traceDialogue(ITS_HDR *header, TCAP_DLG *dlg);
void traceDialogueType(TCAP_DLG *dlg);

void traceAbortDlg(TCAP_DLG *dlg);
void traceBeginDlg(TCAP_DLG *dlg);
void traceContinueDlg(TCAP_DLG *dlg);
void traceEndDlg(TCAP_DLG *dlg);
void traceUniDlg(TCAP_DLG *dlg);

/* Component trace functions */
void traceComponent(ITS_HDR *header, TCAP_CPT *cpt);
void traceComponentType(TCAP_CPT *cpt);

void traceInvokeCpt(TCAP_CPT *cpt);
void traceCancelCpt(TCAP_CPT *cpt);
void traceErrorCpt(TCAP_CPT *cpt);
void traceRejectCpt(TCAP_CPT *cpt);
void traceResultCpt(TCAP_CPT *cpt);


/* Global Title Translation */
void setGTT(ITS_OCTET* addrIndicator, ITS_OCTET* gttInfo, int* len);


#endif /* INAP_TEST_H */
