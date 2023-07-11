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
 ****************************************************************************
 *
 *  ID: $Id: SendOrReceive.h,v 9.1 2005/03/23 12:51:33 cvsadmin Exp $
 *
 * LOG: $Log: SendOrReceive.h,v $
 * LOG: Revision 9.1  2005/03/23 12:51:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:30  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:50  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:21  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:22  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:26  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/11/01 17:26:35  cbascon
 * LOG:
 * LOG:
 * LOG: Should have log entries on files now.
 * LOG:
 ****************************************************************************/

#ifndef GSMMAP_SEND_OR_RECEIVE
#define GSMMAP_SEND_OR_RECEIVE

#include <its++.h>
#include <tcap++.h>
#include <sccp++.h>

#include <AsnException.h>
#include <AsnObject.h>


/*
 ****************************************************************************
 *
 * NOTE: The Point Codes and Subsystem Numbers below need to be changed as
 *       needed for this test program to function properly
 *  
 ****************************************************************************/

// Sending Program Originating Point Code and SubSystem Number
#define TEST_SENDPC         1
#define TEST_SENDSSN        3

// Receiving Program Originating Point Code and SubSystem Number
#define TEST_RECVPC         2
#define TEST_RECVSSN        4

// Main Menu Operations
#define TestSCCPUIS                             1   // SCCP messages
#define TestSCCPUOS                             2
#define TestActivateTraceModeArg                3   // GSMMAP invokes
#define TestDeactivateTraceModeArg              4
#define TestForwardGroupCallSignallingArg       5
#define TestMTForwardSMArg                      6
#define TestPrepareGroupCallArg                 7
#define TestProvideRoamingNumberArg             8
#define TestReportSMDeliveryStatusArg           9
#define TestRoutingInfoForSMArg                 10
#define TestCancelComponent                     11  // TCAP messages
#define TestEndPrearranged                      12
#define TestWait                                13  // Get next event
#define TestQuit                                14  // Quit program

// Response menu
#define TestMTForwardSMRes                      1   // GSMMAP results
#define TestProvideRoamingNumberRes             2
#define TestReportSMDeliveryStatusRes           3
#define TestRoutingInfoForSMRes                 4
#define TestUserErrorComponent                  5   // TCAP components
#define TestUserRejectComponent                 6
#define TestAbortDialog                         7   // TCAP dialogs
#define TestEndDialog                           8


// User input functions
int getYesOrNo();
int getSelection(int startRange, int endRange);

// Build SCCP_Address from user input
int setSCCPAddress(its::SCCP_Address *addr);    

// Send a GSMMAP i
int sendQuery(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);

// Main menu operations
int sendActivateTraceModeArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendDeactivateTraceModeArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendForwardGroupCallSignallingArg(ITS_HANDLE handle,
                                      its::TCAP_Dialogue *dlg);
int sendMTForwardSMArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendPrepareGroupCallArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendProvideRoamingNumberArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendReportSMDeliveryStatusArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendRoutingInfoForSMArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendSendRoutingInfoArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);
int sendUpdateLocationArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg);

// Response menu operations
int sendMTForwardSMRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                       its::TCAP_Component *recvCpt);
int sendProvideRoamingNumberRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                                its::TCAP_Component *recvCpt);
int sendReportSMDeliveryStatusRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                                  its::TCAP_Component *recvCpt);
int sendRoutingInfoForSMRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                            its::TCAP_Component *recvCpt);
int sendSendRoutingInfoRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                           its::TCAP_Component *recvCpt);
int sendUpdateLocationRes(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                          its::TCAP_Component *recvCpt);

// Wait for ITS Event
void waitForEvent(ITS_HANDLE handle, ITS_USHORT& did,
                  its::SCCP_CallingPartyAddr origAddr);

// Encode/Decode functions
void encodeGSMMAPMsg(its::AsnObject *p, its::Octets **octets);
void decodeGSMMAPInvoke(ITS_LONG code, its::Octets *octets);
void decodeGSMMAPResult(ITS_LONG code, its::Octets *octets);

void MsgDecode(AsnObject *p, Octets *octets);

// Menus
void displayMainMenu();
void displayResponseMenu();

// User input function
int getYesOrNo();
int getSelection(int startRange, int endRange);


// Set SCCP Address
int getSCCPAddress(its::SCCP_Address *addr);
void setGTT(ITS_OCTET *addrIndicator, ITS_OCTET* gttInfo, int *len);

// Test program operations
int sendQuery(ITS_HANDLE handle, ITS_USHORT recvdid, its::SCCP_Address &orig,
              its::SCCP_Address &dest, int msgtag);
int sendResponse(ITS_HANDLE handle, its::TCAP_Component *recvCpt,
                 its::TCAP_Dialogue *recvDlg, 
                 its::SCCP_CallingPartyAddr origAddr);
void waitForEvent(ITS_HANDLE handle, ITS_USHORT& did,
                  its::SCCP_CallingPartyAddr origAddr);

// Decode GSMAP message
void decodeGSMMAPMsg(ITS_LONG code, its::Octets *octet);

// Query operations
int sendCancelCpt(ITS_HANDLE handle);

// Response operations
int sendUErrorCpt(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                  its::TCAP_Component *recvCpt);
int sendURejectCpt(ITS_HANDLE handle, its::TCAP_Dialogue *dlg,
                   its::TCAP_Component *recvCpt);
int sendUAbortDlg(ITS_HANDLE handle, its::TCAP_Dialogue *recvDlg);
int sendEndDlg(ITS_HANDLE handle, its::TCAP_Dialogue *recvDlg);


#endif
