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

#include <its++.h>

#include <iostream>
#include <iomanip>

#include <its_app.h>
#include <its_transports.h>

#include <its_object.h>
#include <its_thread.h>
#include <its_worker.h>
/*
#include <its_ss7_trans.h>
*/
#include <its_ss7_stubs.h>
#include <its_object.h>

extern "C" ITS_Class itsINTELLISS7_Class;

#include <itu/sccp.h>
#include <itu/tcap.h>
#include <tcap++.h>
#include <sccp++.h>

#include <cap_cpp.h>

#include "initialize.h"
#include "SendRecv.h"
#include "trace.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace cap;
using namespace cap_v3;
#endif


//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the main menu of the test program.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
displayMainMenu()
{
    cout << endl;
    cout << "------------------------MAIN MENU----------------------" << endl;
    cout << endl;
/*
    cout << "[" << setw(2) << dec << (int)TestSCCPUIS
         << "] Send SCCP User In Service Message" << endl;
    cout << "[" << setw(2) << dec << (int)TestSCCPUOS
         << "] Send SCCP User Out of Service Message" << endl;
    cout << endl;
*/
    cout << "Select Message to Send:" << endl;
    cout << "-----------------------" << endl;
	cout << "[" << setw(2) << (int)TestApplyCharging
         << "] ApplyChargingArg" << endl;
	cout << "[" << setw(2) << (int)TestApplyChargingReport
         << "] ApplyChargingReportArg" << endl;
	cout << "[" << setw(2) << (int)TestAssistRequestInstructions
         << "] AssistRequestInstructionsArg" << endl;
    cout << "[" << setw(2) << (int)TestCallGap
         << "] CallGapArg" << endl;
	cout << "[" << setw(2) << (int)TestCallInformationReport
         << "] CallInformationReportArg" << endl;
    cout << "[" << setw(2) << (int)TestCallInformationRequest
         << "] CallInformationRequestArg" << endl;
    cout << "[" << setw(2) << (int)TestCancel
         << "] CancelArg" << endl;
    cout << "[" << setw(2) << (int)TestConnect
         << "] ConnectArg" << endl;
	cout << "[" << setw(2) << (int)TestConnectToResource
         << "] ConnectToResourceArg" << endl;
    cout << "[" << setw(2) << (int)TestContinueWithArgument
         << "] ContinueWithArgumentArg" << endl;
	cout << "[" << setw(2) << (int)TestEstablishTemporaryConnection
         << "] EstablishTemporaryConnectionArg" << endl;
	cout << "[" << setw(2) << (int)TestEventReportBCSM
         << "] EventReportBCSMArg" << endl;
	cout << "[" << setw(2) << (int)TestFurnishChargingInformation
         << "] FurnishChargingInformationArg" << endl;
    cout << "[" << setw(2) << (int)TestInitialDP
         << "] InitialDPArg" << endl;
    cout << "[" << setw(2) << (int)TestReleaseCall
         << "] ReleaseCallArg" << endl;
    cout << "[" << setw(2) << (int)TestRequestReportBCSMEvent
         << "] RequestReportBCSMEventArg" << endl;
	cout << "[" << setw(2) << (int)TestResetTimer
         << "] ResetTimerArg" << endl;
	cout << "[" << setw(2) << (int)TestSendChargingInformation
         << "] SendChargingInformationArg" << endl;
	cout << "[" << setw(2) << (int)TestPromptAndCollectUserInformation
         << "] PromptAndCollectUserInformationArg" << endl;
	cout << "[" << setw(2) << (int)TestPlayAnnouncement
         << "] PlayAnnouncementArg" << endl;
	cout << "[" << setw(2) << (int)TestReceivedInformation
         << "] ReceivedInformationArg" << endl;
    cout << endl;
/*  
	cout << "[" << setw(2) << (int)TestCancelComponent
         << "] Cancel Component" << endl;
    cout << "[" << setw(2) << (int)TestEndPrearranged
         << "] End Dialog (Prearranged End)" << endl;
    cout << endl;
    cout << "[" << setw(2) << (int)TestWait
         << "] Wait For Event" << endl;
*/  
    cout << "[" << setw(2) << (int)TestQuit
         << "] Quit" << endl;
    cout << endl;
    
	cout << "-------------------------------------------------------" << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the response menu where the user can
 *      select a response for an CAP message.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
displayResponseMenu()
{
    cout << "----------------------RESPONSE MENU--------------------" << endl;
    cout << endl;
    cout << "Send CAP Response:" << endl;
    cout << "-------------------" << endl;
    cout << "[" << setw(2) << dec << (int)TestCallInformationReport
         << "] CallInformationReport" << endl;
    cout << "[" << setw(2) << (int)TestEventReportBCSM
         << "] EventReportBCSM" << endl;
/*  
#if 0
    cout << "[" << setw(2) <<
         << "] RequestCurrentStatusReportResult" << endl;
#endif


    cout << "[" << setw(2) << (int)TestStatusReport
         << "] StatusReport" << endl;
    cout << endl;

*/
    cout << "Send TCAP Response:" << endl;
    cout << "-------------------" << endl;
    cout << "[" << setw(2) << (int)TestUserErrorComponent
         << "] User Error Component" << endl;
    cout << "[" << setw(2) << (int)TestUserRejectComponent
         << "] User Reject Component" << endl;
    cout << "[" << setw(2) << (int)TestAbortDialog
         << "] Abort Dialog" << endl;
    cout << "[" << setw(2) << (int)TestEndDialog
         << "] End Dialog" << endl;
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will ask a user to enter an integer within a given
 *      range.
 *
 *  Input Parameters:
 *      startRange - lowerbound of expected value
 *      endRange - upperbound of expected value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Integer between startRange and endRange.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
getSelection (int startRange, int endRange)
{
	
    int selection = 0;
    
    fflush(stdin); 
	
    cout << "-> ";

    cin >> selection;
    printf("\n selection is %d", selection);
    printf("\n range is %d to %d" ,startRange, endRange );

    while ((selection < startRange) || (selection > endRange))
    {
		printf("\n within while loop");
        fflush(stdin);
        cout << "Incorrect Selection (range is: " << startRange << " to "
             << endRange << ")" << endl;
        cin >> selection;
    }
    
    return selection;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get a get a Yes or No from the user.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Return value is 1 if the user entered 'y' or a 'Y' and 0 otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
getYesOrNo()
{
    char ch;

    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        return 1;
    else
        return 0;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method will wait for an IntelliSS7 Event. This function is used
 *      to receive a dialog and a component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      origAddr - originating address of the application instance
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      did - the dialog Id of the received dialog is saved in this parameter
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
waitForEvent(ITS_HANDLE handle, ITS_USHORT &did,
             SCCP_CallingPartyAddr origAddr)
{
    int keepWaiting = 1;
    int noResponse = 0;
    int buflen = 0;
    ITS_LONG op;
    Octets *octets;
    ITS_EVENT eventstr;
    ITS_ByteArray eventData, buf;
    TCAP_Dialogue *recvDlg;
    TCAP_Component *recvCpt;

    cout << "--------------------- WAIT FOR EVENT ------------------" << endl;

    // process events
    while (keepWaiting)
    {
        if (ITS_GetNextEvent(handle, &eventstr) != ITS_SUCCESS)
        {
            // an error occurred
            continue;
        }

        // Create an Event class from Event structure
        // event = new ITS_Event(eventstruct);
        ITS_Event event(&eventstr);

        // Determine Event source        
        if (event.GetSource() == ITS_TCAP_SRC)
        {
            cout << "Received a TCAP Event." << endl;
    
            // Determine event type received
            switch (eventstr.data[0])
            {
            case ITS_TCAP_DLG:
                cout << "Receiving a Dialog." << endl;
                TCAP_Dialogue::Receive(handle, event, &recvDlg);

                // Copy the dialog id
                did = recvDlg->GetDialogueID();
                cout << "did = " <<did << endl;

                
                // Determine the dialog type and print out dialog type
                // specific information
                switch (recvDlg->GetDialogueType())
                {
                case TCPPT_TC_UNI:
                    // If dialog does not have a component stop waiting for an
                    // event
                    if (!recvDlg->IsComponentPresent())
                    {
                        keepWaiting = 0;
                    }
                    break;

                case TCPPT_TC_BEGIN:
                    // If dialog does not have a component stop waiting for an
                    // event
                    if (!recvDlg->IsComponentPresent())
                    {
                        keepWaiting = 0;
                    }
                    break;

                case TCPPT_TC_CONTINUE:
                    // If dialog does not have a component stop waiting for an
                    // event
                    if (!recvDlg->IsComponentPresent())
                    {
                        keepWaiting = 0;
                    }
                    break;

                case TCPPT_TC_END:
                    // No response is to be sent when an end dialog is
                    // received
                    noResponse = 1;

                    // If dialog does not have a component stop waiting for an
                    // event
                    if (!recvDlg->IsComponentPresent())
                    {
                        keepWaiting = 0;
                    }
                    break;

                case TCPPT_TC_U_ABORT:
                    // No response is to be sent when an abort dialog is
                    // received
                    noResponse = 1;

                    // Stop waiting for an event if a U-Abort dialog is
                    // received
                    keepWaiting = 0;
                    break;

                case TCPPT_TC_P_ABORT:
                    // No response is to be sent when an abort dialog is
                    // received
                    noResponse = 1;

                    // Stop waiting for an event if a P-Abort dialog is
                    // received
                    keepWaiting = 0;
                    break;

                case TCPPT_TC_NOTICE:
                    // Stop waiting for an event if a Notice dialog is
                    // received
                    keepWaiting = 0;
                    break;

                default:
                    cout << "Unknown Dialog, "
                         << (int)recvDlg->GetDialogueType() << endl;
                    break;
                }  
                break;

            case ITS_TCAP_CPT:
                cout << "Receiving a component." << endl;
                TCAP_Component::Receive(handle, event, recvDlg, &recvCpt);

                
                switch (recvCpt->GetComponentType())
                {
                case TCPPT_TC_INVOKE:
                    // Determine if the CAP message received does not require
                    // a response
                    ((TCAP_Invoke *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Invoke *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeCAPMsg(op, octets);

					/*********************************************

                    if (op == OP_callInformationReport ||
                        op == OP_eventReportBCSM)
                    {
                        // Indicate that the CAP message received does not
                        // require a response
                        noResponse = 1;
                    }

					**********************************************/

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_L:
                    // Determine if the CAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeCAPMsg(op, octets);

                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_NL:
                    // Determine if the CAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeCAPMsg(op, octets);

                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_U_ERROR:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_CANCEL:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_CANCEL:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_REJECT:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_R_REJECT:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_REJECT:
                    // Indicate that the CAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                default:
                    cout << "WARNING: Unknown component received" << endl;
                    cout << endl;
                }
                
                // Will stop waiting for an Event when a component is received
                // since this test program only sends one component for each
                // dialog sent
                keepWaiting = 0;

                cout << "Check noResponse = " << noResponse << endl;
                if (!noResponse)
                {
                    // Send an CAP response
                    sendResponse(handle, recvCpt, recvDlg);
                }
                break;

            default:
                // Received wrong TCAP event type
                cout << "Received wrong TCAP event type." << endl;
                cout << "TCAP event is: " << eventData[0] << endl;
                break;
            }
        }
        else
        {
            // Received non-TCAP event
            cout << "Received a non-TCAP Event." << endl;
            cout << "Source: " << event.GetSource() << endl;

            // Print out Event data
            cout << "Data Length: " << event.GetLength() << endl;
            cout << "       Data:" << endl;
            for (int i = 0; i < event.GetLength(); i++)
            {
                cout << eventstr.data[i] << " ";
                if (i % 10 == 0)
                {
                    cout << endl;
                }
            }
            cout << endl
                 << endl;

            // Exit for loop
            break;
        }
    }
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an CAP invoke.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvdid - dialog Id of the dialog received using waitForEvent()
 *      orig - originating address of the appication instance
 *      dest - destination address of remote application
 *      msgtag - tag for corresponding CAP message to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the CAP message was sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The message tags are defined in SendRecv.h.
 *
 *  See Also:
 ****************************************************************************/
int
sendQuery(ITS_HANDLE handle, ITS_USHORT recvdid, SCCP_Address &orig,
          SCCP_Address &dest, int msgtag)

{
    int result = 0;
    int dlgChoice = 1;
    //ITS_OCTET slsKey, priority; 
    ITS_OCTET appContext[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    ITS_OCTET userInfo[5] = { 0x01, 0x01, 0x02, 0x02, 0x03 };
    ITS_USHORT begdid; 
    TCAP_Begin beg;
    TCAP_Continue cont;
    int local_pc, local_ssn, remote_pc, remote_ssn;

    if (recvdid == SendInstance)
    {
	    local_pc = 2;
        local_ssn = 20;
        remote_pc = 3;
	    remote_ssn = 30;
    }
    else
    {
       	local_pc = 3;
        local_ssn = 30;
        remote_pc = 2;
	    remote_ssn = 20;
  
    }



    // Ask user select between a continue dialog and an end dialog to send
/*
    cout << endl;
    cout << "Select Dialog to Send:" << endl;
    cout << "----------------------" << endl;
    cout << "[1] Begin" << endl;
    cout << "[2] Continue" << endl;
    cout << endl;
    dlgChoice = getSelection(1, 2);
*/
    // Determine what kind of dialog the user wnats to send
    if (dlgChoice == 1)
    {
        /////////////////////////////////
        // Set Begin dialog information
		beg.SetOrigAddr(ADDR_IND, local_pc, local_ssn, NULL, 0);
        beg.SetDestAddr(ADDR_IND, remote_pc, remote_ssn, NULL, 0);

        // Set the Originating Point Code
        //beg.SetOPC(local_pc);

        // Set the Destination Point Code
        //beg.SetDPC(remote_pc);

        //cout << "Setting Begin dialog parameters:" << endl;
        //cout << "--------------------------------" << endl;

        // Allocate a unique Dialog ID for the Begin dialog and set  the
        TCAP_AllocateDialogueId(&begdid);
				/* dialog-id hardcoded till allocate-tcap-dialog works */ 

        beg.SetDialogueID(begdid);
		printf("\n dialog-id allocated is %d \n", begdid);

        // beg.SetQualityOfService(QOSI_RET_OPT, slsKey, priority);
        
        // Ask user to use Application Context Name or not
        cout << "Use Application Context Name? [y]es/[n]o -> ";
        if (getYesOrNo() == 1)
        {
            beg.SetApplicationContext(appContext, 5);
        }

        // Ask user to use User Information or not
        cout << "Use User Information? [y]es/[n]o -> ";
        if (getYesOrNo() == 1)
        {
            beg.SetUserInfo(userInfo, 5);
        }
    }
    else
    {
        ///////////////////////////////////
        // Set continue dialog information

        // Copy the dialog ID of the received Dialog
        cont.SetDialogueID(recvdid);

        // Temporarily commented  Set Originating Point Code
        cont.SetOPC(local_pc);

        // Set Originating address
        cont.SetOrigAddr(orig);

        // Ask user to use Application Context Name or not
        cout << "Use Application Context Name? [y]es/[n]o -> ";
        if (getYesOrNo() == 1)
        {
            cont.SetApplicationContext(appContext, 5);
        }

        // Ask user to use User Information or not
        cout << "Use User Information? [y]es/[n]o -> ";
        if (getYesOrNo() == 1)
        {
            cont.SetApplicationContext(userInfo, 5);
        }
    }

    // Determine what CAP message the user selected to send
    switch (msgtag)
    {

	case TestApplyCharging:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendApplyCharging(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendApplyCharging(handle, &cont);
        }
        break;

	case TestApplyChargingReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendApplyChargingReport(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendApplyChargingReport(handle, &cont);
        }
        break;
/*
	case TestAssistRequestInstruction:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendAssistRequestInstruction(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendAssistRequestInstruction(handle, &cont);
        }
        break;
*/
    case TestCallGap:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendCallGap(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendCallGap(handle, &cont);
        }
        break;


	case TestCallInformationReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendCallInformationReport(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendCallInformationReport(handle, &cont);
        }
        break;

    case TestCallInformationRequest:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendCallInformationRequest(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendCallInformationRequest(handle, &cont);
        }
        break;

    case TestCancel:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendCancel(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendCancel(handle, &cont);
        }
        break;

    case TestConnect:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendConnect(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendConnect(handle, &cont);
        }
        break;


	case TestConnectToResource:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendConnectToResource(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendConnectToResource(handle, &cont);
        }
        break;

	case TestContinueWithArgument:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendContinueWithArgument(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendContinueWithArgument(handle, &cont);
        }
        break;
/*
	case TestDisconnectForwardConnection:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendDisconnectForwardConnection(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendDisconnectForwardConnection(handle, &cont);
        }
        break;
*/
	case TestEstablishTemporaryConnection:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendEstablishTemporaryConnection(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendEstablishTemporaryConnection(handle, &cont);
        }
        break;

	case TestEventReportBCSM:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendEventReportBCSM(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendEventReportBCSM(handle, &cont);
        }
        break;

	case TestFurnishChargingInformation:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendFurnishChargingInformation(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendFurnishChargingInformation(handle, &cont);
        }
        break;

    case TestInitialDP:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendInitialDP(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendInitialDP(handle, &cont);
        }
        break;

	case TestPlayAnnouncement:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendPlayAnnouncement(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendPlayAnnouncement(handle, &cont);
        }
        break;

    case TestReleaseCall:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendReleaseCall(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendReleaseCall(handle, &cont);
        }
        break;

    case TestRequestReportBCSMEvent:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendRequestReportBCSMEvent(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendRequestReportBCSMEvent(handle, &cont);
        }
        break;

	 case TestResetTimer:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendResetTimer(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendResetTimer(handle, &cont);
        }
        break;

    case TestSendChargingInformation:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendChargingInformation(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendChargingInformation(handle, &cont);
        }
        break;

	case TestPromptAndCollectUserInformation:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendPromptAndCollectUserInformation(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendPromptAndCollectUserInformation(handle, &cont);
        }
        break;
/*
	case TestSendReceivedInformation:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendReceivedInformation(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendReceivedInformation(handle, &cont);
        }
        break;
*/
    }


    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // Check if the invoke component was sent successfully
            if (result == ITS_SUCCESS)
            {
                // Printout dialog information
                
                result = TCAP_Dialogue::Send(handle, &beg);
				printf("\n result of send is %d", result);
            }
        }
        else
        {
            // Check if the invoke component was sent successfully
            if (result == ITS_SUCCESS)
            {
                
                result = TCAP_Dialogue::Send(handle, &cont);
            }
        }
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to an CAP invoke.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvCpt - pointer to a component received in waitForEvent()
 *      recvDlg - pointer to a dialog received in waitForEvent()
 *      origAddr - originating address of the appication instance
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if a response was sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendResponse(ITS_HANDLE handle, TCAP_Component *recvCpt,
             TCAP_Dialogue *recvDlg)
{
    int result = ITS_SUCCESS;
    int responseChoice = 0;
    int dlgChoice = 0;
    ITS_OCTET appContext[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    ITS_OCTET userInfo[5] = { 0x01, 0x01, 0x02, 0x02, 0x03 };
    ITS_UINT opc;
    TCAP_Continue cont;
    TCAP_End end;

    ////////////////////////////
    // Display Send Query Menu
    displayResponseMenu();
    
    
    responseChoice = getSelection(1, 40);
    
    // User is not asked to choose between a Continue dialog and an End dialog
    // if the user wanted to send an Abort dialog or an End dialog with no
    // component
    if (responseChoice > 0 && responseChoice < 40)
    {
        
        // Ask user select between a continue dialog and an end dialog to send
        //cout << endl;
        //cout << "Select Dialog to Send:" << endl;
        //cout << "----------------------" << endl;
        //cout << "[1] Continue" << endl;
        //cout << "[2] End" << endl;
        //cout << endl;
        //dlgChoice = getSelection(1, 2);

/*
        // Check what kind of dialog the user wants to send
        if (dlgChoice == 1)
        {
            // User wants to send a continue dialog
            // Set Continue dialog parameters

            // Copy the dialog ID of the received Dialog
            cont.SetDialogueID(recvDlg->GetDialogueID());

            // Set Originating Point Code
            opc = ((SCCP_Address)origAddr).GetPointCode();
            cont.SetOPC(opc);

            // Set Originating address
            cont.SetOrigAddr(origAddr);

            // Ask user to use Application Context Name or not
            cout << "Use Application Context Name? [y]es/[n]o -> ";
            if (getYesOrNo() == 1)
            {
                cont.SetApplicationContext(appContext, 5);
            }

            // Ask user to use User Information or not
            cout << "Use User Information? [y]es/[n]o -> ";
            if (getYesOrNo() == 1)
            {
                cont.SetApplicationContext(userInfo, 5);
            }
        }
        else
*/
        
            // User wants to send an end dialog
            // Set End dialog parameters
            
            // Copy the dialog ID of the received Dialog
            end.SetDialogueID(recvDlg->GetDialogueID());

            // Set termination type to Basic End
            end.SetPreArrangedEnd(false);

            //end.SetApplicationContext(appContext, 5);

            //end.SetUserInfo(userInfo, 5);
            
        
    }
    
    // Determine what CAP message the user selected to send
    switch (responseChoice)
    {
/*
    case TestCallInformationReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a continue dialog
            result = sendCallInformationReport(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send a end dialog
            result = sendCallInformationReport(handle, &end, recvCpt);
        }
        break;
*/
        
    case TestEventReportBCSM:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a continue dialog
            result = sendEventReportBCSM(handle, &cont);
        }
        else
        {
            // User wanted to send a end dialog
            result = sendEventReportBCSM(handle, &end);
        }
        break;



    case TestUserErrorComponent:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // Send a U-Error component
            sendUErrorCpt(handle, &cont, recvCpt);
        }
        else
        {
            // Send a U-Error component
            sendUErrorCpt(handle, &end, recvCpt);
        }
        break;

    case TestUserRejectComponent:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // Send a U-Reject component
            sendURejectCpt(handle, &cont, recvCpt);

        }
        else
        {
            // Send a U-Reject component
            sendURejectCpt(handle, &end, recvCpt);
        }
        break;

    case TestAbortDialog:
        sendUAbortDlg(handle, recvDlg);
        break;

    case TestEndDialog:
        printf("\n  end dialog to be sent: fall through");
        //sendEndDlg(handle, &end /*recvDlg*/);
        break;
    }

    // Check if the user wanted to send a component as a response AND
    // Check if component was sent successfully
    if (responseChoice > 0 && responseChoice < 40 && result == ITS_SUCCESS)
    {
      // Check what kind of dialog the user wanted to send: Continue or End
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            // Check if the component was sent successfully
            if (result == ITS_SUCCESS)
            {
                
                result = TCAP_Dialogue::Send(handle, &cont);
            }
        }
        else
        {
            // User wanted to send an end dialog
            // Check if the component was sent successfully
            if (result == ITS_SUCCESS)
            {
                
                result = TCAP_Dialogue::Send(handle, &end);
                
            }
        }
    }    
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ApplyCharging invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/
int
sendApplyCharging(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0, timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ApplyChargingArg *applyChargingArg = new ApplyChargingArg();

    // Set Parameters
    cout << endl;
    cout << "Setting ApplyCharging Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // Ask user to include AChBillingChargingCharacteristics mandatory parameter
        cout << "Include aChBillingChargingCharacteristics mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            applyChargingArg->SetAChBillingChargingCharacteristics(InitializeAChBillingChargingCharacteristics());
        }

		 // Ask user to include partyToCharge mandatory parameter
        cout << "Include partyToCharge mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            applyChargingArg->SetPartyToCharge((SendingSideID*)InitializeSendingLegID);
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        applyChargingArg->SetAChBillingChargingCharacteristics(InitializeAChBillingChargingCharacteristics());
		applyChargingArg->SetPartyToCharge((SendingSideID*)InitializeSendingLegID());
	}

    // Extensions, not set

    // Encode message
    MsgEncode(applyChargingArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_applyCharging);

    // Set Operation Class to 2 indicating that a response is expected on
    // error of the procedure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an ApplyCharging invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ApplyCharging invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send ApplyCharging." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete applyChargingArg;
    applyChargingArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ApplyChargingReport invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendApplyChargingReport(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0, timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    CallResult *applyChargingReportArg =InitializeCallResult();

    // Set Parameters
    cout << endl;
    cout << "Setting ApplyChargingReport Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    
    // Extensions, not set

    // Encode message
    MsgEncode(applyChargingReportArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/

    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_applyChargingReport);

    // Set Operation Class to 2 indicating that a response is expected on
    // error of the procedure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an ApplyChargingReport invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ApplyChargingReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send ApplyChargingReport." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete applyChargingReportArg;
    applyChargingReportArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a AssistRequestInstruction invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

/*
int
sendAssistRequestInstruction(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0, timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    AssistRequestInstructionArg *assistRequestInstructionArg =new AssistRequestInstructionArg();

    // Set Parameters
    cout << endl;
    cout << "Setting AssistRequestInstruction Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         //

        // Ask user to include ResourceID mandatory parameter
        cout << "Include CorrelationID mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
           assistRequestInstructionArg->SetCorrelationID(InitializeCorrelationID());
        }

		 cout << "Include IPSSPCapabilities mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
           assistRequestInstructionArg->SetIPSSPCapabilities(InitializeIPSSPCapabilities());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         //
        assistRequestInstructionArg->SetCorrelationID(InitializeCorrelationID());
		assistRequestInstructionArg->SetIPSSPCapabilities(InitializeIPSSPCapabilities());
    }

    // Extensions, not set

    // Encode message
    MsgEncode(assistRequestInstructionArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_assistRequestInstruction);

    // Set Operation Class to 2 indicating that a response is expected on
    // error of the procedure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an AssistRequestInstruction invoke component
    traceComponent(&inv);
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "AssistRequestInstruction invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send AssistRequestInstruction." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete AssistRequestInstructionArg;
    assistRequestInstructionArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}
*/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a CallGap invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendCallGap(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    int gapCriteriaChoice = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    CallGapArg* callGapArg = new CallGapArg();

    // Set Parameters
    cout << endl;
    cout << "Setting CallGap Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

	
    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        
        // User wanted to send a badly encoded CAP message
         

        // Ask the user to include GapCriteria mandatory parameter
        cout << "Include GapCriteria mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            callGapArg->SetGapCriteria(InitializeGapCriteria());
        }

        // Ask the user to include GapIndicators mandatory parameter
        cout << "Include GapIndicators mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            callGapArg->SetGapIndicators(InitializeGapIndicators());    
        }

        // Ask the user to include
    }
    else
        
    {
        
         /* User wanted to send a valid CAP message */
         //
        callGapArg->SetGapCriteria(InitializeGapCriteria());
        callGapArg->SetGapIndicators(InitializeGapIndicators());
    }

    
        /* Ask user to include optional parameters */
     //

    // Ask user to include ControlType optional parameter
    cout << "Include ControlType optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        callGapArg->SetControlType(InitializeControlType());
    }

    // Ask user to include GapTreatment optional parameter
    cout << "Include GapTreatment optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        callGapArg->SetGapTreatment(InitializeGapTreatment());
    }

    // Encode message
    MsgEncode(callGapArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);
    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_callGap);

    // Set Operation Class to 4 indicating that no response is expected on
    // success or failure of sending the invoke as defined in ITU spec Q.1218
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallGap invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "CallGap invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: CallGap invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete callGapArg;
    callGapArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a CallInformationRequest invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendCallInformationRequest(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    int invokeID = 0;
    string str;
    Octets *encOctets;
    TCAP_Invoke inv;
    CallInformationRequestArg *callInformationRequestArg = new CallInformationRequestArg();

    // Set Parameters
    cout << endl;
    cout << "Setting CallInformationRequest Parameters:" << endl;
    cout << "------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message */
         //
        
        // Ask user to include RequestedInformationTypeList mandatory parameter
        cout << "Include RequestedInformationTypeList mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            callInformationRequestArg->SetRequestedInformationTypeList
                (InitializeRequestedInformationTypeList());
        }
    }
    else
    {
        /*
         * User wanted to send a valid message */
         //
        callInformationRequestArg->SetRequestedInformationTypeList
            (InitializeRequestedInformationTypeList());
    }

    /*
     * Ask user to include optional parameter, LegID */
     //
    cout << "Include LegID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        callInformationRequestArg->SetLegID((SendingSideID*)InitializeSendingLegID());;
    }

    // Encode message
    MsgEncode(callInformationRequestArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_callInformationRequest);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallInformationRequest invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "CallInformationRequest invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send CallInformationRequest." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete callInformationRequestArg;
    callInformationRequestArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a CallInformationReport invoke.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a dialog received in waitForEvent().
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendCallInformationReport(ITS_HANDLE handle, TCAP_Dialogue *dlg)
                          
{
    int result = 0;
    int timeout = 0;
	ITS_USHORT InvokeID =1;
    string str;
    Octets *encOctets;
    TCAP_Invoke inv;
    CallInformationReportArg* callInformationReportArg = new CallInformationReportArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting CallInformationReport Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */
        
        // Ask user to include RequestedInformationList mandatory parameter
        cout << "Include RequestedInformationList mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            callInformationReportArg->SetRequestedInformationList
                (InitializeRequestedInformationList());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        callInformationReportArg->SetRequestedInformationList
            (InitializeRequestedInformationList());
    }

    /*
     * Ask user to include optional parameters
     */

    // Ask user to include CorrelationID optional parameter
    cout << "Include LegID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        callInformationReportArg->SetLegID((ReceivingSideID*)InitializeReceivingLegID());;
	}    
    // Encode message
    MsgEncode(callInformationReportArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Copy invoke ID of received component for use with for the
    // CallInformationReport invoke
    inv.SetInvokeID((ITS_USHORT)InvokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_callInformationReport);

    // Set Operation Class to 4 indicating that no response is expected on
    // success or failure of sending the invoke as defined in ITU spec Q.1218
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallInformationReport invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "CallInformationReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send CallInformationReport." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete callInformationReportArg;
    callInformationReportArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a Cancel invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendCancel(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
	int choice;
	long val;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    CancelArg* cancelArg = new CancelArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting Cancel Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
	
      
         /* User wanted to send a valid CAP message */
         
       
		cout << "Select one of the 2 choices:" << endl;
		cout << "[0] InvokeId" << endl;
		cout << "[1] All Requests" << endl;
		cout << endl;
		choice = getSelection(0, 1);

				// Determine what the user selected
		if (choice == 0)
		{
			// User selected number of digits

        // Ask user to enter number of digits
			cout << "Enter InvokeId: [1 .. 255] ";
			val = getSelection(1, 255);
			cancelArg->SetChoiceInvokeID(val);
			cout << endl;
		}
		else
		{
			cancelArg->SetChoiceAllRequests(NULL);
		}



	// EncodeMessages
    MsgEncode(cancelArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
	cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_cancel);

    // Set Operation Class to 1
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a Cancel invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "Cancel invoke send success." << endl;
    }
    else
    {
        cout << "WARNING:  Cancel invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete cancelArg;
    cancelArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a Connect invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendConnect(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ConnectArg* connectArg = new ConnectArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting Connect Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message */
         //

        // Ask user to include mandatory parameter
        cout << "Include DestinationRoutingAddress mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            connectArg->SetDestinationRoutingAddress
                (InitializeDestinationRoutingAddress());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message */
         //
        connectArg->SetDestinationRoutingAddress
                (InitializeDestinationRoutingAddress());
    }

    /*
     * Ask user to include optional parameters */
     //

    // AlertingPattern
    cout << "Include AlertingPattern optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        connectArg->SetAlertingPattern(InitializeAlertingPattern());
    }


    // CallingPartysCategory
    cout << "Include CallingPartysCategory optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        connectArg->SetCallingPartysCategory(InitializeCallingPartysCategory());    
    }

	 // OriginalCalledParty
    cout << "Include OriginalCalledPartyID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        connectArg->SetOriginalCalledPartyID(InitializeOriginalCalledPartyID());    
    }


    //
    // Optional Parameters listed below are not set in this test program
     //
    // GenericNumbers
    // OriginalCalledPartyID
    // Extensions
    // SuppressionOfAnnouncement
    // ServiceInteractionIndicators
    // RedirectingPartyID
    // RedirectionInformation

    // Encode message
    MsgEncode(connectArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_connect);

    // Set Operation Class to 1
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a Connect invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "Connect invoke send success." << endl;
    }
    else
    {
        cout << "WARNING:  Connect invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete connectArg;
    connectArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a Connect invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendConnectToResource(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ConnectToResourceArg* connectToResourceArg = new ConnectToResourceArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting ConnectToResource Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

	
    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        //
        // User wanted to send a badly encoded CAP message
         

        // Ask user to include mandatory parameter
        cout << "Include ResourceAddress mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            connectToResourceArg->SetResourceAddress
                (InitializeResourceAddress());
        }
    }
    else

    {
         /*
         * User wanted to send a valid CAP message
         */
        connectToResourceArg->SetResourceAddress
                (InitializeResourceAddress());
    }

    /*
     * Ask user to include optional parameters
     */

//   Comment out for the time being 

    // ServiceInteractionIndicatorsTwo
    cout << "Include ServiceInteractionIndicatorsTwo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        connectToResourceArg->SetServiceInteractionIndicatorsTwo(InitializeServiceInteractionIndicatorsTwo());
    }
/* Temporary commentation ends */

    // Encode message
    MsgEncode(connectToResourceArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_connectToResource);

    // Set Operation Class to 1
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a ConnectToResource invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ConnectToResource invoke send success." << endl;
    }
    else
    {
        cout << "WARNING:  ConnectToResource invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete connectToResourceArg;
    connectToResourceArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ContinueWithArgument invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a dialog received in waitForEvent().
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

int
sendContinueWithArgument(ITS_HANDLE handle, TCAP_Dialogue *dlg)
                    
{
    int result = 0;
    int timeout = 0;
    TCAP_Invoke inv;
	ITS_USHORT InvokeID =1;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ContinueWithArgumentArg *continueWithArgumentArg = new ContinueWithArgumentArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting ContinueWithArgument Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

	
    /*
     * Ask user to include optional parameters
     */
    
    // AlertingPattern
    cout << "Include AlertingPattern optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        continueWithArgumentArg->SetAlertingPattern
            (InitializeAlertingPattern());
    }
    
/* Comment out for the time being **

    // ServiceInteractionIndicatorsTwo
    cout << "Include ServiceInteractionIndicatorsTwo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        continueWithArgumentArg->SetServiceInteractionIndicatorsTwo(InitializeServiceInteractionIndicatorsTwo());
    }

/temporary commentation ends **/
  
    // Extensions, not set

	 // CallingPartysCategory
    cout << "Include CallingPartysCategory optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        continueWithArgumentArg->SetCallingPartysCategory(InitializeCallingPartysCategory());
    }
    
/* To be coded later

	 // GenericNumbers
    cout << "Include GenericNumbers optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        continueWithArgumentArg->SetGenericNumbers(InitializeGenericNumbers());
    }

	 // SuppressionOfAnnouncement
    cout << "Include SuppressionOfAnnouncement optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        continueWithArgumentArg->SetSuppressionOfAnnouncement(InitializeSuppressionOfAnnouncement());
    }
    
*/    
    // Encode message
    MsgEncode(continueWithArgumentArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Copy invoke ID of received component for use with for the
    // RequestContinueWithArgumentEvent
    inv.SetInvokeID((ITS_USHORT)InvokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_continueWithArgument);

    // Set Operation Class to 4 indicating that no response is expected on
    // error or success of the operation
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ContinueWithArgument invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: ContinueWithArgument invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete continueWithArgumentArg;
    continueWithArgumentArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a disconnectForwardConnection invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

/*
int
sendDisconnectForwardConnection(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    DisconnectForwardConnectionArg* disconnectForwardConnectionArg = new DisconnectForwardConnectionArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting disconnectForwardConnection Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    //
     * Ask user to include optional parameters
     /

    // CorrelationID
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        disconnectforwardconnectionArg->SetCorrelationID(InitializeCorrelationID());
    }

    // scfID
    cout << "Include scfID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        disconnectforwardconnectionArg->SetScfID(InitializeScfID());
    }

    // ServiceInteractionIndicatorsTwo
    cout << "Include ServiceInteractionIndicatorsTwo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        disconnectforwardconnectionArg->SetServiceInteractionIndicatorsTwo(InitializeServiceInteractionIndicatorsTwo());
    }

    
    // Encode message
    MsgEncode(disconnectforwardconnectionArg, &encOctets, str);

    // Ask the user for a timeout value in seconds

    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_disconnectforwardconnection);

    // Set Operation Class to 2 indicating that a response is only expected on
    // error
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a disconnectforwardconnection invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "disconnectforwardconnection invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: disconnectforwardconnection invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete disconnectforwardconnectionArg;
    disconnectforwardconnectionArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}
*/


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a EstablishTemporaryConnection invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendEstablishTemporaryConnection(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    EstablishTemporaryConnectionArg* establishTemporaryConnectionArg = new EstablishTemporaryConnectionArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting EstablishTemporaryConnection Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

	// Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // EventTypeBCSM
        cout << "Include AssistingSSPIPRoutingAddress mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            establishTemporaryConnectionArg->SetAssistingSSPIPRoutingAddress(InitializeDigits());
        }
        
        
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
         establishTemporaryConnectionArg->SetAssistingSSPIPRoutingAddress(InitializeDigits());
    }

    /*
     * Ask user to include optional parameters
     */

    // CorrelationID
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        establishTemporaryConnectionArg->SetCorrelationID(InitializeCorrelationID());
    }

    // scfID
    cout << "Include scfID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        establishTemporaryConnectionArg->SetScfID(InitializeScfID());
    }

/* temporarily commented ***
    // ServiceInteractionIndicatorsTwo
    cout << "Include ServiceInteractionIndicatorsTwo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        establishTemporaryConnectionArg->SetServiceInteractionIndicatorsTwo(InitializeServiceInteractionIndicatorsTwo());
    }
/ temporary commentation ends **/
    
    // Encode message
    MsgEncode(establishTemporaryConnectionArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_establishTemporaryConnection);

    // Set Operation Class to 2 indicating that a response is only expected on
    // error
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a EstablishTemporaryConnection invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "EstablishTemporaryConnection invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: EstablishTemporaryConnection invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete establishTemporaryConnectionArg;
    establishTemporaryConnectionArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a EventReportBCSM invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a dialog received in waitForEvent().
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

int
sendEventReportBCSM(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    TCAP_Invoke inv;
    TCAP_Result res;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
	ITS_USHORT invokeID =1;
    string str;
    EventReportBCSMArg *eventReportBCSMArg = new EventReportBCSMArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting EventReportBCSM Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // EventTypeBCSM
        cout << "Include EventTypeBCSM mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            eventReportBCSMArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        }
        
        // MiscCallInfo
        cout << "Include MiscCallInfo mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            eventReportBCSMArg->SetMiscCallInfo(InitializeMiscCallInfo());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        eventReportBCSMArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        eventReportBCSMArg->SetMiscCallInfo(InitializeMiscCallInfo());
    }

    /*
     * Ask user to include optional parameters
     */
    
    /* EventSpecificInformationBCSM
    cout << "Include EventSpecificInformationBCSM optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        eventReportBCSMArg->SetEventSpecificInformationBCSM
            (InitializeEventSpecificInformationBCSM());
    }
    

    // LegID
    cout << "Include LegID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        eventReportBCSMArg->SetLegID((ReceivingSideID*)InitializeReceivingLegID());
    }
    */

    // Extensions, not set

    // Encode message
    MsgEncode(eventReportBCSMArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*  
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
    inv.SetTimeOut(60000);
*/
    // Copy invoke ID of received component for use with for the
    // RequestEventReportBCSMEvent
    
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_eventReportBCSM);

    // Set Operation Class to 4 indicating that no response is expected on
    // error or success of the operation
    //res.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a EventReportBCSM invoke component
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "EventReportBCSM invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: EventReportBCSM invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete eventReportBCSMArg;
    eventReportBCSMArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a InitialDP invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendInitialDP(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    InitialDPArg* initialDPArg= new InitialDPArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting InitialDP Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    /*
     * Ask user to include optional parameters
     */

    // ServiceKey
    cout << "Include ServiceKey optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetServiceKey(InitializeServiceKey());
    }

    // CalledPartyNumber
    cout << "Include CalledPartyNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetCalledPartyNumber(InitializeCalledPartyNumber());
    }

    // CallingPartyNumber
    cout << "Include CallingPartyNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetCallingPartyNumber(InitializeCallingPartyNumber());
    }

    
    // CallingPartysCategory
    cout << "Include CallingPartysCategory optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetCallingPartysCategory(InitializeCallingPartysCategory());
    }
    
    
    // CGEncountered
    cout << "Include CGEncountered optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
       initialDPArg->SetCGEncountered(InitializeCGEncountered());
    }

    // AdditionalCallingPartyNumber
    cout << "Include AdditionalCallingPartyNumber optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetAdditionalCallingPartyNumber
            (InitializeAdditionalCallingPartyNumber());
    }
    
    // BearerCapability
    cout << "Include BearerCapability optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetBearerCapability(InitializeBearerCapability());
    }
    
    // EventTypeBCSM
    cout << "Include EventTypeBCSM optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        initialDPArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
    }
    
    /*
     * Optional parameters listed below not set
     */
    // IPSSPCapabilities
    // IPAvailable
    // LocationNumber
    // OriginalCalledPartyID
    // ServiceProfileIdentifier
    // TerminalType
    // Extensions
    // TriggerType
    // HighLayerCompatibility
    // ServiceInteractionIndicators
    // ForwardCallIndicators
    // RedirectingPartyID
    // RedirectionInformation

    // Encode message
    MsgEncode(initialDPArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_initialDP);

    // Set Operation Class to 2 indicating that a response is only expected on
    // error
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "InitialDP invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: InitialDP invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete initialDPArg;
    initialDPArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a FurnishChargingInformation invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendFurnishChargingInformation(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
	FurnishChargingInformationArg* furnishChargingInformationArg;

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting FurnishChargingInformation Parameters:" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;

	furnishChargingInformationArg = 
		InitializeFCIBillingChargingCharacteristics();

    // Encode message
    MsgEncode(furnishChargingInformationArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_furnishChargingInformation);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "FurnishChargingInformation invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: FurnishChargingInformation invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete furnishChargingInformationArg;
    furnishChargingInformationArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ReleaseCall invoke
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendReleaseCall(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    Cause* releaseCallArg = InitializeCause();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting ReleaseCall Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    
    // Encode message
    MsgEncode(releaseCallArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_releaseCall);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ReleaseCall invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: ReleaseCall invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete releaseCallArg;
    releaseCallArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RequestReportBCSMEvent invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendRequestReportBCSMEvent(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    RequestReportBCSMEventArg* requestReportBCSMEventArg = new RequestReportBCSMEventArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting RequestEveryStatusChangeReport Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // Ask user to include BcsmEvents mandatory parameter
        cout << "Include BcsmEvents mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            requestReportBCSMEventArg->SetBcsmEvents(InitializeRequestReportBCSMEventArg_BcsmEvents());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        requestReportBCSMEventArg->SetBcsmEvents(InitializeRequestReportBCSMEventArg_BcsmEvents());
        
    }

    /*
     * Ask user to include optional parameters
     */

    // Extensions, not set

    // Encode message
    MsgEncode(requestReportBCSMEventArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_requestReportBCSMEvent);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "RequestReportBCSMEvent invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: RequestReportBCSMEvent invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete requestReportBCSMEventArg;
    requestReportBCSMEventArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ResetTimer invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a dialog received in waitForEvent().
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

 
int
sendResetTimer(ITS_HANDLE handle, TCAP_Dialogue *dlg)
                
{
    int result = 0;
    int timeout = 0;
    TCAP_Invoke inv;
	ITS_USHORT InvokeID=1;
    Octets *encOctets;
    string str;
    ResetTimerArg* resetTimerArg = new ResetTimerArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting ResetTimer Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;


	    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        
         // User wanted to send a badly encoded CAP message
         

        // Ask user to include TimerID mandatory parameter
        cout << "Include TimerID mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            resetTimerArg->SetTimerID(InitializeTimerID());
        }

		// Ask user to include TimerValue mandatory parameter
        cout << "Include TimerValue mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            resetTimerArg->SetTimervalue(InitializeInteger4());
        }
    }
    else
	{
		resetTimerArg->SetTimerID(InitializeTimerID());
		resetTimerArg->SetTimervalue(InitializeInteger4());
	}


    // Extensions, not set

    // Encode message
    MsgEncode(resetTimerArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Copy invoke ID of received component for use with for the
    // RequestEventReportBCSMEvent
    inv.SetInvokeID(InvokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_resetTimer);

    // Set Operation Class to 4 indicating that no response is expected
    // on procedure success or failure
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ResetTimer invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: ResetTimer invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete resetTimerArg;
    resetTimerArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a SendChargingReport invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendChargingInformation(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    SendChargingInformationArg *sendChargingInformationArg;

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting SendChargingInformation Parameters:" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;

    sendChargingInformationArg = new SendChargingInformationArg();


       // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
         // User wanted to send a badly encoded CAP message
         

        // Ask user to include SCIBillingChargingCharacteristics mandatory parameter
        cout << "Include SCIBillingChargingCharacteristics mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            sendChargingInformationArg->SetSCIBillingChargingCharacteristics(InitializeSciBillingChargingCharacteristics());
		}
		// Ask user to include SetPartyToCharge mandatory parameter
        cout << "Include SetPartyToCharge mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            sendChargingInformationArg->SetPartyToCharge((SendingSideID*)InitializeSendingLegID());
        }
    }
    else

	{
		sendChargingInformationArg->SetSCIBillingChargingCharacteristics(InitializeSciBillingChargingCharacteristics());
		sendChargingInformationArg->SetPartyToCharge((SendingSideID*)InitializeSendingLegID());
	}


    // Encode message
    MsgEncode(sendChargingInformationArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_sendChargingInformation);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "SendChargingInformation invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: SendChargingInformation invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete sendChargingInformationArg;
    sendChargingInformationArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a PromptAndCollectUserInformation invoke
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendPromptAndCollectUserInformation(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    PromptAndCollectUserInformationArg* promptAndCollectUserInformationArg =
        new PromptAndCollectUserInformationArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting PromptAndCollectUserInformation Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // Ask user to include CollectedInfo mandatory parameter
        cout << "Include CollectedInfo mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            promptAndCollectUserInformationArg->SetCollectedInfo(InitializeCollectedInfo());
        }

		// Ask user to include DisconnectFromIPForbidden mandatory parameter
        cout << "Include disconnectFromIPForbidden mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            promptAndCollectUserInformationArg->SetDisconnectFromIPForbidden(InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        promptAndCollectUserInformationArg->SetCollectedInfo(InitializeCollectedInfo());
		promptAndCollectUserInformationArg->SetDisconnectFromIPForbidden(InitializePromptAndCollectUserInformation_DisconnectFromIPForbidden());
	}

    /*
     * Ask user to include optional parameters
     */

    // InformationToSend
    cout << "Include InformationToSend optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        promptAndCollectUserInformationArg->SetInformationToSend(InitializeInformationToSend());
    }

   
    // Extensions, not set

    // Encode message
    MsgEncode(promptAndCollectUserInformationArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*  
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_promptAndCollectUserInformation);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "PromptAndCollectUserInformation invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: PromptAndCollectUserInformation invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete promptAndCollectUserInformationArg;
    promptAndCollectUserInformationArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a PlayAnnouncement invoke
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/


int
sendPlayAnnouncement(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    PlayAnnouncementArg* playAnnouncementArg =
        new PlayAnnouncementArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting playAnnouncement Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded CAP message
         */

        // Ask user to include SendInformationToSend mandatory parameter
        cout << "Include SendInformationToSend mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            playAnnouncementArg->SetInformationToSend(InitializeInformationToSend());
        }

		// Ask user to include DisconnectFromIPForbidden mandatory parameter
        cout << "Include disconnectFromIPForbidden mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            playAnnouncementArg->SetDisconnectFromIPForbidden(InitializeDisconnectFromIPForbidden());
        }

		// Ask user to include requestAnnouncementComplete mandatory parameter
        cout << "Include requestAnnouncementComplete mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            playAnnouncementArg->SetRequestAnnouncementComplete(InitializeRequestAnnouncementComplete());
        }
    }
    else
    {
        /*
         * User wanted to send a valid CAP message
         */
        playAnnouncementArg->SetInformationToSend(InitializeInformationToSend());
		playAnnouncementArg->SetDisconnectFromIPForbidden(InitializeDisconnectFromIPForbidden());
		playAnnouncementArg->SetRequestAnnouncementComplete(InitializeRequestAnnouncementComplete());
	}

    /*
     * Ask user to include optional parameters
     */

   
    // Extensions, not set

    // Encode message
    MsgEncode(playAnnouncementArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
/*
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);
*/
    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_playAnnouncement);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "playannouncement invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: playannouncement invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete playAnnouncementArg;
    playAnnouncementArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ReceivedInformation invoke
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The dialog associated with the invoke component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/

/*
int
sendReceivedInformation(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ReceivedInformationArg* receivedInformationArg =
        new ReceivedInformationArg();

    // Set Parameters for CAP message to send
    cout << endl;
    cout << "Setting ReceivedInformation Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    /*
     * Ask user to include optional parameters
    //

    // Ask user to include ResourceID optional parameter
    cout << "Include ResourceID optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        receivedInformationArg->SetResourceID(InitializeResourceID());
    }
    
    // Ask user to include ResourceStatus optional parameter
    cout << "Include ResourceStatus optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        receivedInformationArg->SetResourceStatus(InitializeResourceStatus());
    }
    
    // Ask user to include CorrelationID optional parameter
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        receivedInformationArg->SetCorrelationID(InitializeCorrelationID());
    }
    
    // Ask user to include MonitorDuration optional parameter
    cout << "Include MonitorDuration optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        receivedInformationArg->SetMonitorDuration(InitializeDuration());
    }

    // Ask user to include BearerCapability optional parameter
    cout << "Include BearerCapability optional parameter? [y]es/[n]o: "
         << endl;
    if (getYesOrNo() == 1)
    {
        receivedInformationArg->SetBearerCapability(InitializeBearerCapability());
    }

    // Extensions, not set

    // Encode message
    MsgEncode(receivedInformationArg, &encOctets, str);

    // Ask the user for a timeout value in seconds

    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    inv.SetTimeOut(60000);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeID;
    inv.SetInvokeID((ITS_USHORT)invokeID);

    // Set Invoke operation code
    inv.SetOperation(OP_receivedInformation);

    // Set Operation Class to 1 indicating that a response is expected on the
    // procedure success or failure
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    traceComponent(&inv);
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ReceivedInformation invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: ReceivedInformation invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete receivedInformationArg;
    receivedInformationArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}
*/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a User Abort dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvDlg - pointer to a dialog received in waitForEvent().
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the user abort dialog is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendUAbortDlg(ITS_HANDLE handle, TCAP_Dialogue *recvDlg)
{
    int result = 0;
    int abortChoice = 0;
    TCAP_Abort abort(true);

    // Copy the dialog ID of the received Dialog
    abort.SetDialogueID(recvDlg->GetDialogueID());

    // Set abort reason
    abort.SetAbortReason(TCAP_UABT_USER_DEFINED_CCITT);

    

    // Send the end dialog
    result = TCAP_Dialogue::Send(handle, &abort);

    // Check if abort dialog was sent successfully
    if (result == ITS_SUCCESS)
    {
        // User abort dialog sent successfully
        cout << "U-Abort dialog send success." << endl;
    }
    else
    {
        // Failed to send U-Abort dialog
        cout << "WARNING: U-Abort dialog send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a Cancel component with an end dialog with
 *      termination set to prearranged end.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the cancel component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendCancelCpt(ITS_HANDLE handle)
{
    int result = 0;
    int invokeId = 0;
    ITS_USHORT did = 0;
    TCAP_Cancel cancel;
    TCAP_End end;

    // Set end dialog parameters

    // Ask user to enter the dialog id of the transaction to be ended
    cout << "Enter dialog Id of transaction to be terminated: ";
    cin >> did;

    // Set the dialog Id of the end dialog
    end.SetDialogueID(did);

    // Set termination type to Prearranged End to locally end a transaction
    end.SetPreArrangedEnd(true);

    // Ask user to provide the invoke Id of the component to be cancelled
    cout << "Enter Invoke ID of component to be cancelled: ";
    cin >> invokeId;

    // Set invoke Id of cancel component
    cancel.SetInvokeID((ITS_OCTET)invokeId);

    
    // Send cancel component
    result = TCAP_Component::Send(handle, &end, &cancel);

    // Check if cancel component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Cancel component sent successfully
        cout << "Cancel component send success." << endl;
        cout << endl;

        
        // Send end dialog
        result = TCAP_Dialogue::Send(handle, &end);

        // Check if end dialog was sent succesfully
        if (result == ITS_SUCCESS)
        {
            // End dialog sent successfully
            cout << "End dialog send success." << endl;
        }
        else
        {
            // Failed to send end dialog
            cout << "WARNING: End dialog send failed." << endl;
            cout << "  Error: " << result << endl;
        }
    }
    else
    {
        // Failed to send cancel component
        cout << "WARNING: Cancel component send failed." << endl;
        cout << "         Not sending end dialog." << endl;
        cout << "  Error: " << result << endl;
    }
    cout << endl;
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a User Error component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associcated with the error component
 *      recvCpt - pointer to a component received in waitForEvent()
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the user error component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendUErrorCpt(ITS_HANDLE handle, TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{

    int result = 0;
    ITS_OCTET errorCode;
    TCAP_Error error;

    // Copy invoke of received component into error component's
    // invoke ID field
    error.SetInvokeID(recvCpt->GetInvokeID());
/*
    // Ask user to select an error code for this error component
    cout << "Select Error Code:" << endl;
    cout << "------------------" << endl;
    cout << '[' << setw(2) << CAP_ERR_cancelled
         << "] Cancelled" << endl;
    cout << '[' << setw(2) << CAP_ERR_cancelFailed
         << "] CancelFailed" << endl;
    // Missing one in CAP.h
    cout << '[' << setw(2) << CAP_ERR_eTCFailed
         << "] ETCFailed" << endl;
    cout << '[' << setw(2) << CAP_ERR_improperCallerResponse
         << "] ImproperCallerResponse" << endl;
    cout << '[' << setw(2) << CAP_ERR_missingCustomerRecord
         << "] MissingCustomerRecord" << endl;
    cout << '[' << setw(2) << CAP_ERR_missingParameter
         << "] MissingParameter" << endl;
    cout << '[' << setw(2) << CAP_ERR_parameterOutOfRange
         << "] ParameterOutOfRange" << endl;
    cout << '[' << setw(2) << CAP_ERR_requestedInfoError
         << "] RequestedInfoError" << endl;
    cout << '[' << setw(2) << CAP_ERR_systemFailure
         << "] SystemFailure" << endl;
    cout << '[' << setw(2) << CAP_ERR_taskRefused
         << "] TaskRefused" << endl;
    cout << '[' << setw(2) << CAP_ERR_unavailableResource
         << "] UnavailableResource" << endl;
    cout << '[' << setw(2) << CAP_ERR_unexpectedComponentSequence
         << "] UnexpectedComponentSequence" << endl;
    cout << '[' << setw(2) << CAP_ERR_unexpectedDataValue
         << "] UnexpectedDataValue" << endl;
    cout << '[' << setw(2) << CAP_ERR_unexpectedParameter
         << "] UnexpectedParameter" << endl;
    cout << '[' << setw(2) << CAP_ERR_unknownLegID
         << "] UnknownLegID" << endl;
    cout << '[' << setw(2) << CAP_ERR_unknownResource
         << "] UnknownResource" << endl;
    cout << endl;
*/
    // Get error code selected by user
    errorCode = (ITS_OCTET)20;
    
    // Set error code for the component
    error.SetError(errorCode);

    // Printout error component information
    
    // Send the error component
    result = TCAP_Component::Send(handle, dlg, &error);

    // Check if error component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Error component was sent successfully
        cout << "Error component send success." << endl;
    }
    else
    {
        // Error component send failed
        cout << "WARNING: Error component send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    cout << endl;

    return ITS_SUCCESS;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a User Reject component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associcated with the error component
 *      recvCpt - pointer to a component received in waitForEvent()
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the user reject component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendURejectCpt(ITS_HANDLE handle, TCAP_Dialogue *dlg, TCAP_Component *recvCpt)
{
    int result = 0;
    ITS_OCTET problemType, problemCode;
    TCAP_Reject reject(true, true);

    // Copy invoke of received component into error component's
    // invoke ID field
    reject.SetInvokeID(recvCpt->GetInvokeID());

    /* Ask user to select problem type    
    cout << "Select Problem Type:" << endl;
    cout << "--------------------" << endl;
    cout << '[' << setw(2) << (int)TCAP_PROB_GENERAL_CCITT
         << "] General" << endl;
    cout << '[' << setw(2) << (int)TCAP_PROB_INVOKE_CCITT
         << "] Invoke" << endl;
    cout << '[' << setw(2) << (int)TCAP_PROB_RETURN_RES_CCITT
         << "] Return Result" << endl;
    cout << '[' << setw(2) << (int)TCAP_PROB_RETURN_ERR_CCITT
         << "] Return Error" << endl;
    cout << endl;
    */

    problemType = (ITS_OCTET)2;
    

    /* Determine problem type seleceted by the user
    switch (problemType)
    {
    case TCAP_PROB_GENERAL_CCITT:
        cout << "Select General Problem Code:" << endl;
        cout << "----------------------------" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT
             << "] Unrecognized Component" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT
             << "] Mistyped Component" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT
             << "] Badly Structured Component" << endl;
        cout << endl;
        problemCode = (ITS_OCTET)getSelection(0, 2);
        break;

    case TCAP_PROB_INVOKE_CCITT:
        cout << "Select Invoke Problem Code:" << endl;
        cout << "----------------------------" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT
             << "] Duplicate Invoke ID" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT
             << "] Unrecognized Operation Code" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT
             << "] Mistyped Parameter" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT
             << "] Resource Limit" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT
             << "] Initiate Release" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT
             << "] Unrecognized Link ID" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT
             << "] Unexpected Link Response" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT
             << "] Unexpected Link Operation" << endl;
        cout << endl;
        problemCode = (ITS_OCTET)getSelection(0, 7);
        break;

    case TCAP_PROB_RETURN_RES_CCITT:
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT
             << "] Unrecognized Invoke ID" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT
             << "] Unexpected Return Result" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT
             << "] Mistyped Parameter" << endl;
        cout << endl;
        problemCode = (ITS_OCTET)getSelection(0, 2);
        break;

    case TCAP_PROB_RETURN_ERR_CCITT:
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT
             << "] Unrecognized Invoke ID" << endl;
        cout << '[' << setw(2)
             << (int)TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT
             << "] Unexpected Return Error" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT
             << "] Unrecognized Error" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT
             << "] Unexpected Error" << endl;
        cout << '[' << setw(2) << (int)TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT
             << "] Mistyped Parameter" << endl;
        cout << endl;
    */
        problemCode = (ITS_OCTET)2;
    /*
        break;
    }
    cout << endl;
    */
    // Set reject component problem type and code
    reject.SetProblem(problemType, problemCode);

    
    // Send the reject component
    result = TCAP_Component::Send(handle, dlg, &reject);

    // Check if error component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Reject component was sent successfully
        cout << "Reject component send success." << endl;
    }
    else
    {
        // Reject component send failed
        cout << "WARNING: Reject component send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an End dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvDlg - pointer to a dialog received in waitForEvent()
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the end dialog is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *      The user will be asked to select the termination type: Basic End or
 *      Prearranged End. To end a transaction locally select Prearranged End.
 *
 *  See Also:
 ****************************************************************************/
int
sendEndDlg(ITS_HANDLE handle, TCAP_Dialogue *recvDlg)
{
    printf("\n entered end dialog fn");
    int result = 0;
    //ITS_OCTET appContext[50], userInfo[50];
    //int appContext = 0;
    //int userInfo = 0;
    TCAP_End end;

    result = TCAP_Dialogue::Send(handle, recvDlg);
/*
    // Copy the dialog ID of the received Dialog
    end.SetDialogueID(recvDlg->GetDialogueID());
    
    // Not set in this test program
    // Application Context
    // User Info

    cout << "Select Termination Type:" << endl;
    cout << "------------------------" << endl;
    cout << "[1] Basic End" << endl;
    cout << "[2] PreArranged End" << endl;
    cout << endl;

    if (getSelection(1, 2) == 1)
    {
        // Set termination type to Basic End
        end.SetPreArrangedEnd(false);
    }
    else
    {
        // Set termination type to Prearranged End
        end.SetPreArrangedEnd(true);
    }

    printf("\n print1");
    // Send the end dialog
    result = TCAP_Dialogue::Send(handle, &end);
*/
    // Check if dialog was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Send success
        cout << "End dialog send success." << endl;
    }
    else
    {
        // Send failed
        cout << "WARNING: End dialog send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get an SCCP address from the user.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - SCCP address built according to user provided information
 *
 *  Return Value:
 *      ITS_SUCCESS if the result component is sent successfully.
 *      Any other value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
getSCCPAddress(SCCP_Address *addr)
{
    int result = 0;
    ITS_OCTET addrIndicator = (0x00U);
    int ssn;
    ITS_UINT  pc;
    int gttLen = 0;
    ITS_OCTET gttInfo[50];

    // Ask user to select a standard for the address
    cout << "Select Standard:" << endl;
    cout << "----------------" << endl;
    cout << "[1] National" << endl;
    cout << "[2] International" << endl;
    cout << endl;

    // Check if user selected National standard
    if (getSelection(1, 2) == 1)
    {
        // Address uses national standard
        addr->SetInternationalRouting(false);
    }
    else
    {
        // Address uses international standard
        addr->SetInternationalRouting(true);
    }
    cout << endl;

    // Ask user to select how the message will be routed
    cout << "Select Routing:" << endl;
    cout << "---------------" << endl;
    cout << "[1] Point Code and Subsystem Number" << endl;
    cout << "[2] Global Translation Title" << endl;
    cout << endl;

    // Check if user selected route by ssn
    if (getSelection(1, 2) == 1)
    {
        // Route using point code and subsystem number
        addr->SetRouteByPCSSN(true);
    }
    cout << endl;

    // User indicates if the address holds an SSN
    cout << "Does SCCP Address hold an SSN? [y]es/[n]o -> ";
    if (getYesOrNo() == 1)
    {
        // Ask user for an SSN
        cout << "Please Enter SSN (decimal value) -> ";
        cin >> ssn;

        // Set the SSN field of the SCCP address
        addr->SetSSN(ssn);
    }

    // Ask user if the address has an Point Code
    cout << "Does SCCP Address hold an Point Code? [y]es/[n]o -> ";
    if (getYesOrNo() == 1)
    {
        // Ask user for point code
        cout << "Please Enter Point Code (decimal value) -> ";
        cin >> pc;

        // Set the point code field of the SCCP address
        addr->SetPointCode(pc);
    }

    // Ask user if the address has a global title
    cout << "Does SCCP Address hold a Global Title? [y]es/[n]o -> ";
    if (getYesOrNo() == 1)
    {
        // Set GTT information
        setGTT(&addrIndicator, gttInfo, &gttLen);

        // Set global title information
        result = addr->SetGlobalTitle(addrIndicator, gttInfo, gttLen);
    }

    return result;
}

/*
 ************************************************************************
 *  Purpose:
 *       This method constructs a GTT entry in the destination address
 *
 *  Input Parameters:
 *       None.
 *
 * Input/Output Parameters:
 *       None.
 *
 *  Output Parameters:
 *       addrIndicator: modified address indicator based on the GT indicator.
 *       ggtInfo: gtt information provided by user.
 *       len: length of the gtt Information.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
void
setGTT(ITS_OCTET* addrIndicator, ITS_OCTET* gttInfo, int* len)
{
    // temporary information used to set gtt information
    ITS_OCTET tmpAddressIndicator = *addrIndicator;
    int gttEncoding = 0;
    ITS_OCTET translationType = 0;
    ITS_OCTET natureAddress = 0;
    ITS_OCTET encoding = 0;
    ITS_OCTET numbering = 0;
    int tmpLen = 0;

#ifdef ANSI
    // Max Number of digits in GTT for ANSI is 20. +4 just in case
    char gttDigits[24] ;
#else
    // Max Number of digits in GTT for ITU is 48. +4 just in case
    char gttDigits[52] ;
#endif

    // index to browse back and forth in gttInfo array
    int gttInfoIndex = 0;

    // number of digits
    int nbDigits = 0;
    int i;

    /*
     * Setting GGT Encoding.
     * There is more option for ITU than there are for ANSI.
     */
    cout << endl;
    cout << "Select GTT Encoding:" << endl;
    cout << "--------------------------------------------------------------"
         << endl;
#ifdef CCITT
    cout << "[1] Nature of Address only." << endl;
#endif
    cout << "[2] Translation only." << endl;
    cout << "[3] Translation with Encoding Scheme and Numbering Plan." << endl;
#ifdef CCITT
    cout << "[4] Translation with both Nature of Address and Scheme + Plan."
         << endl;
#endif

#ifdef ANSI
    gttEncoding = getSelection(2, 3);
    if (gttEncoding == 2)
    {
        // GTT Translation Only
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
    }
    else
    {
        // GTT Translation with Encoding Scheme and Numbering Plan
        tmpAddressIndicator |= SCCP_CPA_GTTI_TNE;
    }
#endif

#ifdef CCITT
    gttEncoding = getSelection(1, 4);
    if (gttEncoding == 1)
    {
        // GTT Translation with Nature of Address
        tmpAddressIndicator |= SCCP_CPA_GTTI_NATURE;
    }
    else if (gttEncoding == 2)
    {
        // GTT Translation Only
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
    }
    else if (gttEncoding == 3)
    {
        // GTT Translation with Encoding Scheme and Numbering Plan
        tmpAddressIndicator |= SCCP_CPA_GTTI_TNE;
    }
    else
    {
        // GTT Translation with both Nat of Addr and Scheme + Plan
        tmpAddressIndicator |= SCCP_CPA_GTTI_ALL;
    }
#endif
    
    /*
     * Setting Translation Type.
     * Translation Type is not valid for ITU with Nature of Addr.
     */    
#ifdef CCITT
    if (gttEncoding != 1)
    {
#endif
    cout << "Enter GTT Translation Type (0-255)" << endl;
    translationType = (ITS_OCTET)getSelection(0, 255);
    gttInfo[gttInfoIndex++] = (ITS_OCTET)translationType;
    tmpLen++;

#ifdef CCITT
    }
#endif

    /*
     * Based on GTT Encoding:
     * ask user for Nature of Address Indicator,
     * and/or Encoding Scheme + Numbering Plan
     */
    switch (tmpAddressIndicator & SCCP_CPA_GTTI_MASK)
    {
#ifdef CCITT
    case SCCP_CPA_GTTI_NATURE:
        // Need to provide Nature of Address
        cout << "Enter GTT Nature of Address Indicator (0-127)" << endl;
        natureAddress = (ITS_OCTET)getSelection(0, 127);
        /*  Need to know number of digits to set or clear MSB
         * for nature of Address Indicator.
         * Will be added to gttInfo array when requesting digits.
         */ 
        break;
#endif

    case SCCP_CPA_GTTI_TRANS:
        // Nothing to set for that one
        break;

    case SCCP_CPA_GTTI_TNE:
        // Need to provide Encoding Scheme and Numbering Plan
        cout << "Enter GTT Encoding Scheme (0-15)" << endl;
        encoding = (ITS_OCTET)getSelection(0, 15);
        cout << "Enter GTT Numbering Plan (0-15)" << endl;
        numbering = (ITS_OCTET)getSelection(0, 15);
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;
        break;

#ifdef CCITT
    case SCCP_CPA_GTTI_ALL:
        /* Need to provide  Scheme + Plan then Nat of Addr*/
        cout << "Enter GTT Encoding Scheme (0-15)" << endl;
        encoding = (ITS_OCTET)getSelection(0, 15);
        cout << "Enter GTT Numbering Plan (0-15)" << endl;
        numbering = (ITS_OCTET)getSelection(0, 15);
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;

        cout << "Enter GTT Nature of Address Indicator (0-127)" << endl;
        natureAddress = (ITS_OCTET)getSelection(0, 127);
        gttInfo[gttInfoIndex++] = natureAddress;
        tmpLen++;
        break;
#endif // CCITT

    default:
        break;
    }

    // Ask User for GTT digits.
    cout << "Address Information (ex: 1800456) -> " << endl;
    cin >> gttDigits;

    nbDigits = strlen(gttDigits);
    cout << "nbDigits: " << nbDigits << endl;
    
#ifdef CCITT
    /*
     * For GTT Encoding Nature of Address Indicator,
     * if Odd number of digits, will set last bit.
     */
    if ((tmpAddressIndicator & SCCP_CPA_GTTI_MASK) == SCCP_CPA_GTTI_NATURE) 
    {
        if ((nbDigits % 2) != 0)
        {
            // Odd Number of digits: setting MSB
            gttInfo[gttInfoIndex++] = (natureAddress | 0x80);
            tmpLen++;
        }
        else
        {
            // Even Number of digits, clearing MSB
            gttInfo[gttInfoIndex++] = (natureAddress & 0x7F);
            tmpLen++;
        }
    }
#endif

    // Putting digits into GTT Info array
    for (i = 0; i < nbDigits; i++)
    {
         if (i & 1)
         {
             // MSB digit
             gttInfo[gttInfoIndex++] |= ((gttDigits[i] - 0x30) << 4);
         }
         else
         {
             // LSB digit
             gttInfo[gttInfoIndex] = (gttDigits[i] - 0x30);
         }
    }

    // adding the len of digits, if odd number, must add + 1
    tmpLen += (nbDigits / 2);
    if (nbDigits & 1)
    {
        tmpLen++;
    }
    
    // Updating address Indicator to reflect GTT Encoding
    *addrIndicator = tmpAddressIndicator;

    // Updating length of GTT Info
    *len = tmpLen;
}

/*
 ************************************************************************
 *  Purpose:
 *      This function will decode an encoded CAP message in the parameter
 *      field of the component.
 *
 *  Input Parameters:
 *      code - CAP operation code defined in CAP.h
 *      octets - pointer to the encoded value of the CAP message
 *
 * Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
void
decodeCAPMsg(ITS_LONG code, Octets *octets)
{

    string str;

    ApplyChargingArg *applyChargingArg = new ApplyChargingArg();
	ApplyChargingReportArg *applyChargingReportArg = new ApplyChargingReportArg();
    AssistRequestInstructionsArg* assistRequestInstructionsArg = new AssistRequestInstructionsArg();
	ContinueWithArgumentArg *continueWithArgumentArg = new ContinueWithArgumentArg();
	CallGapArg callGapArg ;
    CallInformationReportArg *callInformationReportArg = new CallInformationReportArg();
    CallInformationRequestArg *callInformationRequestArg = new CallInformationRequestArg();
    CancelArg *cancelArg = new CancelArg();
	ConnectArg *connectArg = new ConnectArg();
	ConnectToResourceArg *connectToResourceArg = new ConnectToResourceArg();
	EstablishTemporaryConnectionArg *establishTemporaryConnectionArg = new EstablishTemporaryConnectionArg();
    EventReportBCSMArg *eventReportBCSMArg = new EventReportBCSMArg();
	FurnishChargingInformationArg *furnishChargingInformationArg = new FurnishChargingInformationArg();
    InitialDPArg *initialDPArg = new InitialDPArg();
    ReleaseCallArg *releaseCallArg = new ReleaseCallArg();
    RequestReportBCSMEventArg *requestReportBCSMEventArg = new RequestReportBCSMEventArg();
    ResetTimerArg *resetTimerArg = new ResetTimerArg();
	SendChargingInformationArg *sendChargingInformationArg = new SendChargingInformationArg();
	PromptAndCollectUserInformationArg *promptAndCollectUserInformationArg = new PromptAndCollectUserInformationArg();
    PlayAnnouncementArg *playAnnouncementArg = new PlayAnnouncementArg();
	ReceivedInformationArg *receivedInformationArg = new ReceivedInformationArg();

    // Determine what CAP message the user selected to send
    switch (code)
    {
    case OP_callGap:
        // Decoding CallGap
        cout << "Decoding CallGap encoded value." << endl;
        MsgDecode(&callGapArg, octets, str);
        break;

    case OP_callInformationReport:
        // Decoding CallInformationReport
        cout << "Decoding CallInformationReport encoded value." << endl;
        MsgDecode(callInformationReportArg, octets, str);
        break;

    case OP_callInformationRequest:
        // Decoding CallInformationRequest
        cout << "Decoding CallInformationRequest encoded value." << endl;
        MsgDecode(callInformationRequestArg, octets, str);
        break;

    case OP_applyCharging:
        // Decoding ApplyCharging
        cout << "Decoding ApplyCharging encoded value." << endl;
        MsgDecode(applyChargingArg, octets, str);
        break;

	case OP_applyChargingReport:
        // Decoding ApplyChargingReport
        cout << "Decoding ApplyChargingReport encoded value." << endl;
        MsgDecode(applyChargingReportArg, octets, str);
        break;

	case OP_assistRequestInstructions:
        // Decoding AssistRequestInstruction
        cout << "Decoding AssistRequestInstruction encoded value." << endl;
        MsgDecode(assistRequestInstructionsArg, octets, str);
        break;
 
	case OP_cancel:
        // Decoding Cancel
        cout << "Decoding Cancel encoded value." << endl;
        MsgDecode(cancelArg, octets, str);
        break;

	case OP_connect:
        // Decoding Connect
        cout << "Decoding Connect encoded value." << endl;
        MsgDecode(connectArg, octets, str);
        break;

	case OP_connectToResource:
        // Decoding ConnectToResource
        cout << "Decoding ConnectToResource encoded value." << endl;
        MsgDecode(connectToResourceArg, octets, str);
        break;

    case OP_establishTemporaryConnection:
        // Decoding EstablishTemporaryConnection
        cout << "Decoding EstablishTemporaryConnection encoded value." << endl;
        MsgDecode(establishTemporaryConnectionArg, octets, str);
        break;

    case OP_continueWithArgument:
        // Decoding ContinueWithArgument
        cout << "Decoding ContinueWithArgument encoded value." << endl;
        MsgDecode(continueWithArgumentArg, octets, str);
        break;

    case OP_eventReportBCSM:
        // Decoding EventReportBCSM
        cout << "Decoding EventReportBCSM encoded value." << endl;
        MsgDecode(eventReportBCSMArg, octets, str);
        break;

    case OP_initialDP:
        // Decoding InitialDP
        cout << "Decoding InitialDP encoded value." << endl;
        MsgDecode(initialDPArg, octets, str);
        break;

	case OP_releaseCall:
        // Decoding ReleaseCall
        cout << "Decoding ReleaseCall encoded value." << endl;
        MsgDecode(releaseCallArg, octets, str);
        break;

	case OP_furnishChargingInformation:
        // Decoding FurnishChargingInformation
        cout << "Decoding FurnishChargingInformation encoded value." << endl;
        MsgDecode(furnishChargingInformationArg, octets, str);
        break;


    case OP_sendChargingInformation:
        // Decoding SendChargingInformation
        cout << "Decoding SendChargingInformation encoded value." << endl;
        MsgDecode(sendChargingInformationArg, octets, str);
        break;

    case OP_promptAndCollectUserInformation:
        // Decoding PromptAndCollectUserInformation
        cout << "Decoding PromptAndCollectUserInformation encoded value." << endl;
        MsgDecode(promptAndCollectUserInformationArg, octets, str);
        break;

    case OP_playAnnouncement:
        // Decoding PlayAnnouncement
        cout << "Decoding PlayAnnouncement encoded value." << endl;
        MsgDecode(playAnnouncementArg, octets, str);
        break;

    case OP_requestReportBCSMEvent:
        // Decoding RequestReportBCSMEvent
        cout << "Decoding RequestReportBCSMEvent encoded value." << endl;
        MsgDecode(requestReportBCSMEventArg, octets, str);
        break;
        
    case OP_resetTimer:
        // Decoding ResetTimer
        cout << "Decoding ResetTimer encoded value." << endl;
        MsgDecode(resetTimerArg, octets, str);
        break;

    default:
        /*
         * If this is reached the operation is either not defined or not
         * included in this test program.
         */
        cout << "WARNING: Unrecognized CAP Operation code or not included"
             << endl;
        cout << "         for in this demo." << endl;
        cout << endl;
        break;
    }
}
