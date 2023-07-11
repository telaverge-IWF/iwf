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

#ifndef SENDRECV_H
#define SENDRECV_H

#include <tcap++.h>
#include <sccp++.h>
#include <Octets.h>

// Main menu operation tags
#define TestSCCPUIS                             1
#define TestSCCPUOS                             2

#define TestCallGap                             3
#define TestCallInformationRequest              4
#define TestCancelStatusReportRequest           5
#define TestConnect                             6
#define TestInitialDP                           7
#define TestRequestCurrentStatusReport          8
#define TestRequestEveryStatusChangeReport      9
#define TestRequestFirstStatusMatchReport       10
#define TestRequestReportBCSMEvent              11

#define TestCancelComponent                     12
#define TestEndPrearranged                      13

#define TestWait                                14
#define TestQuit                                15

// Response operation tags
#define TestCallInformationReport               1
#define TestEventReportBCSM                     2
#define TestRequestCurrentStatusReportResult    3
#define TestStatusReport                        4

#define TestUserErrorComponent                  5
#define TestUserRejectComponent                 6

#define TestAbortDialog                         7
#define TestEndDialog                           8

// Menus
void displayMainMenu();
void displayResponseMenu();

// User input function
int getYesOrNo();
int getSelection(int startRange, int endRange);


// Set SCCP Address
int getSCCPAddress(its::SCCP_Address *addr);
void setGTT(ITS_OCTET* addrIndicator, ITS_OCTET* gttInfo, int* len);

// Test program operations
int sendQuery(ITS_HANDLE handle, ITS_USHORT recvdid, its::SCCP_Address &orig,
              its::SCCP_Address &dest, int msgtag);
int sendResponse(ITS_HANDLE handle, its::TCAP_Component *recvCpt,
                 its::TCAP_Dialogue *recvDlg, 
                 its::SCCP_CallingPartyAddr origAddr);
void waitForEvent(ITS_HANDLE handle, ITS_USHORT& did,
                  its::SCCP_CallingPartyAddr origAddr);

// Decode INAP message
void decodeINAPMsg(ITS_LONG code, its::Octets *octet);

// Query operations
int sendCallGap(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCallInformationRequest(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCancelStatusReportRequest(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendConnect(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendInitialDP(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendRequestCurrentStatusReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendRequestEveryStatusChangeReport(ITS_HANDLE handle,
                                       its::TCAP_Dialogue *dlg);
int sendRequestFirstStatusMatchReport(ITS_HANDLE handle,
                                      its::TCAP_Dialogue *dlg);
int sendRequestReportBCSMEvent(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCancelCpt(ITS_HANDLE handle);

// Response operations
int sendCallInformationReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                              its::TCAP_Component *recvCpt);
int sendEventReportBCSM(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                        its::TCAP_Component *recvCpt);
int sendRequestCurrentStatusReportResult(ITS_HANDLE handle,
                                         its::TCAP_Dialogue *dlg,
                                         its::TCAP_Component *recvCpt);
int sendStatusReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                     its::TCAP_Component *recvCpt);
int sendUErrorCpt(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                  its::TCAP_Component *recvCpt);
int sendURejectCpt(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                   its::TCAP_Component *recvCpt);
int sendUAbortDlg(ITS_HANDLE handle, its::TCAP_Dialogue *recvDlg);
int sendEndDlg(ITS_HANDLE handle, its::TCAP_Dialogue *recvDlg);

#endif // SENDRECV_H