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

#define SendInstance	1


// Main menu operation tags
#define TestSCCPUIS                             1
#define TestSCCPUOS                             2

#define	TestApplyCharging                       3
#define	TestApplyChargingReport                 4
#define TestAssistRequestInstructions		    5
#define TestCallGap                             6
#define TestCallInformationReport               7
#define TestCallInformationRequest              8
#define TestCancel								9
#define TestConnect                             10
#define TestConnectToResource					11
#define TestContinueWithArgument				12
#define TestEstablishTemporaryConnection		13
#define TestEventReportBCSM						14
#define	TestFurnishChargingInformation			15
#define TestInitialDP                           16
#define TestReleaseCall							17
#define TestRequestReportBCSMEvent				18
#define TestResetTimer							19
#define TestSendChargingInformation             20
#define TestPromptAndCollectUserInformation		21
#define TestPlayAnnouncement					22
#define TestReceivedInformation					23

#define TestCancelComponent                     24
#define TestEndPrearranged                      25

#define TestWait                                26
#define TestQuit                                27

#define TestAbortDialog                         28
#define TestEndDialog                           29

#define TestUserErrorComponent                  30
#define TestUserRejectComponent                 31

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
                 its::TCAP_Dialogue *recvDlg); 
                 
void waitForEvent(ITS_HANDLE handle, ITS_USHORT& did,
                  its::SCCP_CallingPartyAddr origAddr);

// Decode INAP message
void decodeCAPMsg(ITS_LONG code, its::Octets *octet);

// Query operations
int sendApplyCharging(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendApplyChargingReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCallGap(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCallInformationRequest(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCancel(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendChargingInformation(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendConnect(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendConnectToResource(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendContinueWithArgument(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendEstablishTemporaryConnection(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendFurnishChargingInformation(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendInitialDP(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendPlayAnnouncement(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendPromptAndCollectUserInformation(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendReleaseCall(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendRequestCurrentStatusReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendRequestEveryStatusChangeReport(ITS_HANDLE handle,
                                       its::TCAP_Dialogue *dlg);
int sendRequestFirstStatusMatchReport(ITS_HANDLE handle,
                                      its::TCAP_Dialogue *dlg);
int sendRequestReportBCSMEvent(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendResetTimer(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendCancelCpt(ITS_HANDLE handle);

// Response operations
int sendCallInformationReport(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
                            
int sendEventReportBCSM(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
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