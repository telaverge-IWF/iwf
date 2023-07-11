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

#include <iostream>
#include <iomanip>

#include <its++.h>
#include <its_app.h>
#include <tcap++.h>
#include <sccp++.h>

#include <itu/inap.h>
#include <itu/Digits.h>

#include "SendRecv.h"
#include "trace.h"
#include "initialize.h"


#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif


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
    cout << "[" << setw(2) << dec << (int)TestSCCPUIS
         << "] Send SCCP User In Service Message" << endl;
    cout << "[" << setw(2) << dec << (int)TestSCCPUOS
         << "] Send SCCP User Out of Service Message" << endl;
    cout << endl;
    cout << "Select Message to Send:" << endl;
    cout << "-----------------------" << endl;
    cout << "[" << setw(2) << (int)TestCallGap
         << "] CallGap" << endl;
    cout << "[" << setw(2) << (int)TestCallInformationRequest
         << "] CallInformationRequestArg" << endl;
    cout << "[" << setw(2) << (int)TestCancelStatusReportRequest
         << "] CancelStatusReportRequestArg" << endl;
    cout << "[" << setw(2) << (int)TestConnect
         << "] ConnectArg" << endl;
    cout << "[" << setw(2) << (int)TestInitialDP
         << "] InitialDPArg" << endl;

    // cout << "[ 6] RequestCurrentStatusReportArg" << endl;

    cout << "[" << setw(2) << (int)TestRequestEveryStatusChangeReport
         << "] RequestEveryStatusChangeReportArg" << endl;
    cout << "[" << setw(2) << (int)TestRequestFirstStatusMatchReport
         << "] RequestFirstStatusMatchReportArg" << endl;
    cout << "[" << setw(2) << (int)TestRequestReportBCSMEvent
         << "] RequestReportBCSMEventArg" << endl;
    cout << endl;
    cout << "[" << setw(2) << (int)TestCancelComponent
         << "] Cancel Component" << endl;
    cout << "[" << setw(2) << (int)TestEndPrearranged
         << "] End Dialog (Prearranged End)" << endl;
    cout << endl;
    cout << "[" << setw(2) << (int)TestWait
         << "] Wait For Event" << endl;
    cout << "[" << setw(2) << (int)TestQuit
         << "] Quit" << endl;
    cout << endl;
    cout << "-------------------------------------------------------" << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the response menu where the user can
 *      select a response for an INAP message.
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
    cout << "Send INAP Response:" << endl;
    cout << "-------------------" << endl;
    cout << "[" << setw(2) << dec << (int)TestCallInformationReport
         << "] CallInformationReport" << endl;
    cout << "[" << setw(2) << (int)TestEventReportBCSM
         << "] EventReportBCSM" << endl;
    
#if 0
    cout << "[" << setw(2) <<
         << "] RequestCurrentStatusReportResult" << endl;
#endif


    cout << "[" << setw(2) << (int)TestStatusReport
         << "] StatusReport" << endl;
    cout << endl;
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

    while ((selection < startRange) || (selection > endRange))
    {
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

                // Printout dialog information
                traceDialogue(recvDlg);

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

                // Printout component information
                traceComponent(recvCpt);

                switch (recvCpt->GetComponentType())
                {
                case TCPPT_TC_INVOKE:
                    // Determine if the INAP message received does not require
                    // a response
                    ((TCAP_Invoke *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Invoke *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeINAPMsg(op, octets);

                    if (op == INAP_OP_callInformationReport ||
                        op == INAP_OP_statusReport ||
                        op == INAP_OP_eventReportBCSM)
                    {
                        // Indicate that the INAP message received does not
                        // require a response
                        noResponse = 1;
                    }

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_L:
                    // Determine if the INAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeINAPMsg(op, octets);

                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_NL:
                    // Determine if the INAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeINAPMsg(op, octets);

                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_U_ERROR:
                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_CANCEL:
                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_CANCEL:
                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_REJECT:
                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_R_REJECT:
                    // Indicate that the INAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_REJECT:
                    // Indicate that the INAP message received does not
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
                    // Send an INAP response
                    sendResponse(handle, recvCpt, recvDlg, origAddr);
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
 *      This function will send an INAP invoke.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvdid - dialog Id of the dialog received using waitForEvent()
 *      orig - originating address of the appication instance
 *      dest - destination address of remote application
 *      msgtag - tag for corresponding INAP message to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the INAP message was sent successfully.
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
    int dlgChoice = 0;
    ITS_OCTET slsKey, priority;
    ITS_OCTET appContext[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    ITS_OCTET userInfo[5] = { 0x01, 0x01, 0x02, 0x02, 0x03 };
    ITS_USHORT begdid;
    TCAP_Begin beg;
    TCAP_Continue cont;
    
    // Ask user select between a continue dialog and an end dialog to send
    cout << endl;
    cout << "Select Dialog to Send:" << endl;
    cout << "----------------------" << endl;
    cout << "[1] Begin" << endl;
    cout << "[2] Continue" << endl;
    cout << endl;
    dlgChoice = getSelection(1, 2);

    // Determine what kind of dialog the user wnats to send
    if (dlgChoice == 1)
    {
        /////////////////////////////////
        // Set Begin dialog information

        cout << "Setting Begin dialog parameters:" << endl;
        cout << "--------------------------------" << endl;

        // Allocate a unique Dialog ID for the Begin dialog and set the
        TCAP_AllocateDialogueId(&begdid);
        beg.SetDialogueID(begdid);

        // Set Quality of Service for this transaction. QOS_RET_OPT indicates
        // that a response is expected.
        beg.SetQualityOfService(QOSI_RET_OPT, slsKey, priority);

        // Set the dialog Originating address
        beg.SetOrigAddr(orig);

        // Set the dialog Destination address
        beg.SetDestAddr(dest);

        // Set the Originating Point Code
        beg.SetOPC(orig.GetPointCode());

        // Set the Destination Point Code
        beg.SetDPC(dest.GetPointCode());

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
            beg.SetApplicationContext(userInfo, 5);
        }
    }
    else
    {
        ///////////////////////////////////
        // Set continue dialog information

        // Copy the dialog ID of the received Dialog
        cont.SetDialogueID(recvdid);

        // Set Originating Point Code
        cont.SetOPC(orig.GetPointCode());

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

    // Determine what INAP message the user selected to send
    switch (msgtag)
    {
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

    case TestCancelStatusReportRequest:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendCancelStatusReportRequest(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendCancelStatusReportRequest(handle, &cont);
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

// NOTE: This is excluded for now, Hubert needs to fix ASN compiler
#if 0
    case TestRequestCurrentStatusReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendRequestCurrentStatusReport(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendRequestCurrentStatusReport(handle, &cont);
        }
        break;
#endif

    case TestRequestEveryStatusChangeReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendRequestEveryStatusChangeReport(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendRequestEveryStatusChangeReport(handle, &cont);
        }
        break;

    case TestRequestFirstStatusMatchReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a begin dialog
            result = sendRequestFirstStatusMatchReport(handle, &beg);
        }
        else
        {
            // User wanted to send a continue dialog
            result = sendRequestFirstStatusMatchReport(handle, &cont);
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
                traceDialogue(&beg);
                result = TCAP_Dialogue::Send(handle, &beg);
            }
        }
        else
        {
            // Check if the invoke component was sent successfully
            if (result == ITS_SUCCESS)
            {
                // Printout dialog information
                traceDialogue(&cont);
                result = TCAP_Dialogue::Send(handle, &cont);
            }
        }
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to an INAP invoke.
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
             TCAP_Dialogue *recvDlg, SCCP_CallingPartyAddr origAddr)
{
    int result = 0;
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
    responseChoice = getSelection(1, 8);

    // User is not asked to choose between a Continue dialog and an End dialog
    // if the user wanted to send an Abort dialog or an End dialog with no
    // component
    if (responseChoice > 0 && responseChoice < 7)
    {
        // Ask user select between a continue dialog and an end dialog to send
        cout << endl;
        cout << "Select Dialog to Send:" << endl;
        cout << "----------------------" << endl;
        cout << "[1] Continue" << endl;
        cout << "[2] End" << endl;
        cout << endl;
        dlgChoice = getSelection(1, 2);

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
        {
            // User wants to send an end dialog
            // Set End dialog parameters

            // Copy the dialog ID of the received Dialog
            end.SetDialogueID(recvDlg->GetDialogueID());

            // Set termination type to Basic End
            end.SetPreArrangedEnd(false);
        }
    }

    // Determine what INAP message the user selected to send
    switch (responseChoice)
    {
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
    
    case TestEventReportBCSM:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a continue dialog
            result = sendEventReportBCSM(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send a end dialog
            result = sendEventReportBCSM(handle, &end, recvCpt);
        }
        break;

// NOTE: Not sent for now, the INAP Query this message is a response to is
//       not included yet
#if 0
    case TestRequestCurrentStatusReportResult:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a continue dialog
            result = sendRequestCurrentStatusReportResult(handle, &cont,
                                                          recvCpt);
        }
        else
        {
            // User wanted to send a end dialog
            result = sendRequestCurrentStatusReportResult(handle, &end,
                                                          recvCpt);
        }
        break;
#endif


    case TestStatusReport:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wamted to send a continue dialog
            result = sendStatusReport(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send a end dialog
            result = sendStatusReport(handle, &end, recvCpt);
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
        sendEndDlg(handle, recvDlg);
        break;
    }

    // Check if the user wanted to send a component as a response AND
    // Check if component was sent successfully
    if (responseChoice > 0 && responseChoice < 7 && result == ITS_SUCCESS)
    {
        // Check what kind of dialog the user wanted to send: Continue or End
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            // Check if the component was sent successfully
            if (result == ITS_SUCCESS)
            {
                // Printout dialog information
                traceDialogue(&cont);
                result = TCAP_Dialogue::Send(handle, &cont);
            }
        }
        else
        {
            // User wanted to send an end dialog
            // Check if the component was sent successfully
            if (result == ITS_SUCCESS)
            {
                // Printout dialog information
                traceDialogue(&end);
                result = TCAP_Dialogue::Send(handle, &end);
            }
        }
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a CancelStatusReportRequest invoke component.
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
sendCancelStatusReportRequest(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0, timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    CancelStatusReportRequestArg *csrrArg = new CancelStatusReportRequestArg();

    // Set Parameters
    cout << endl;
    cout << "Setting CancelStatusReportRequest Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // Ask user to include ResourceID mandatory parameter
        cout << "Include ResourceID mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            csrrArg->SetResourceID(InitializeResourceID());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        csrrArg->SetResourceID(InitializeResourceID());
    }

    // Extensions, not set

    // Encode message
    MsgEncode(csrrArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_cancelStatusReportRequest);

    // Set Operation Class to 2 indicating that a response is expected on
    // error of the procedure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CancelStatusReportRequest invoke component
    traceComponent(&inv);
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "CancelStatusReportRequest invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: Failed to send CancelStatusReportRequest." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete csrrArg;
    csrrArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

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
    CallGapArg* cgArg = new CallGapArg();

    // Set Parameters
    cout << endl;
    cout << "Setting CallGap Parameters:" << endl;
    cout << "---------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // Ask the user to include GapCriteria mandatory parameter
        cout << "Include GapCriteria mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            cgArg->SetGapCriteria(InitializeGapCriteria());
        }

        // Ask the user to include GapIndicators mandatory parameter
        cout << "Include GapIndicators mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            cgArg->SetGapIndicators(InitializeGapIndicators());    
        }

        // Ask the user to include
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        cgArg->SetGapCriteria(InitializeGapCriteria());
        cgArg->SetGapIndicators(InitializeGapIndicators());
    }

    /*
     * Ask user to include optional parameters
     */

    // Ask user to include ControlType optional parameter
    cout << "Include ControlType optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cgArg->SetControlType(InitializeControlType());
    }

    // Ask user to include GapTreatment optional parameter
    cout << "Include GapTreatment optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cgArg->SetGapTreatment(InitializeGapTreatment());
    }

    // Encode message
    MsgEncode(cgArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_callGap);

    // Set Operation Class to 4 indicating that no response is expected on
    // success or failure of sending the invoke as defined in ITU spec Q.1218
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallGap invoke component
    traceComponent(&inv);
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
    delete cgArg;
    cgArg = NULL;
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
    CallInformationRequestArg *cireqArg = new CallInformationRequestArg();

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
         * User wanted to send a badly encoded INAP message
         */
        
        // Ask user to include RequestedInformationTypeList mandatory parameter
        cout << "Include RequestedInformationTypeList mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            cireqArg->SetRequestedInformationTypeList
                (InitializeRequestedInformationTypeList());
        }
    }
    else
    {
        /*
         * User wanted to send a valid message
         */
        cireqArg->SetRequestedInformationTypeList
            (InitializeRequestedInformationTypeList());
    }

    /*
     * Ask user to include optional parameter, CorrelationID
     */
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cireqArg->SetCorrelationID(InitializeCorrelationID());
    }

    // Encode message
    MsgEncode(cireqArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_callInformationRequest);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallInformationRequest invoke component
    traceComponent(&inv);
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
    delete cireqArg;
    cireqArg = NULL;
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
sendCallInformationReport(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                          TCAP_Component *recvCpt)
{
    int result = 0;
    int timeout = 0;
    string str;
    Octets *encOctets;
    TCAP_Invoke inv;
    CallInformationReportArg* cirepArg = new CallInformationReportArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting CallInformationReport Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */
        
        // Ask user to include RequestedInformationList mandatory parameter
        cout << "Include RequestedInformationList mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            cirepArg->SetRequestedInformationList
                (InitializeRequestedInformationList());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        cirepArg->SetRequestedInformationList
            (InitializeRequestedInformationList());
    }

    /*
     * Ask user to include optional parameters
     */

    // Ask user to include CorrelationID optional parameter
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cirepArg->SetCorrelationID(InitializeCorrelationID());
    }
    
    // Encode message
    MsgEncode(cirepArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Copy invoke ID of received component for use with for the
    // CallInformationReport invoke
    inv.SetInvokeID(recvCpt->GetInvokeID());

    // Set Invoke operation code
    inv.SetOperation(INAP_OP_callInformationReport);

    // Set Operation Class to 4 indicating that no response is expected on
    // success or failure of sending the invoke as defined in ITU spec Q.1218
    inv.SetClass(4);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send an CallInformationReport invoke component
    traceComponent(&inv);
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
    delete cirepArg;
    cirepArg = NULL;
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
    ConnectArg* cArg = new ConnectArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting Connect Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // Ask user to include mandatory parameter
        cout << "Include DestinationRoutingAddress mandatory parameter?"
             << endl;
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            cArg->SetDestinationRoutingAddress
                (InitializeDestinationRoutingAddress());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        cArg->SetDestinationRoutingAddress
                (InitializeDestinationRoutingAddress());
    }

    /*
     * Ask user to include optional parameters
     */

    // AlertingPattern
    cout << "Include AlertingPattern optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetAlertingPattern(InitializeAlertingPattern());
    }

    // CorrelationID
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetCorrelationID(InitializeCorrelationID());
    }

    // CutAndPaste
    cout << "Include CutAndPaste optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetCutAndPaste(InitializeCutAndPaste());
    }
    
    // ForwardingCondition
    cout << "Include ForwardingCondition optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetForwardingCondition(InitializeForwardingCondition());
    }
    
    // RouteList
    cout << "Include RouteList optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetRouteList(InitializeRouteList());    
    }

    // ScfID
    cout << "Include ScfID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetScfID(InitializeScfID());    
    }

    // TravellingClassMark
    cout << "Include TravellingClassMark optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetTravellingClassMark(InitializeLocationNumber());    
    }

    // CallingPartyNumber
    cout << "Include CallingPartyNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetCallingPartyNumber(InitializeCallingPartyNumber());    
    }

    // CallingPartysCategory
    cout << "Include CallingPartysCategory optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        cArg->SetCallingPartysCategory(InitializeCallingPartysCategory());    
    }

    /*
     * Optional Parameters listed below are not set in this test program
     */
    // ISDNAccessRelatedInformation
    // OriginalCalledPartyID
    // Extensions
    // Carrier
    // ServiceInteractionIndicators
    // RedirectingPartyID
    // RedirectionInformation

    // Encode message
    MsgEncode(cArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_connect);

    // Set Operation Class to 1
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a Connect invoke component
    traceComponent(&inv);
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
    delete cArg;
    cArg = NULL;
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
sendEventReportBCSM(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                    TCAP_Component *recvCpt)
{
    int result = 0;
    int timeout = 0;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    EventReportBCSMArg *erbArg = new EventReportBCSMArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting EventReportBCSM Parameters:" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // EventTypeBCSM
        cout << "Include EventTypeBCSM mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            erbArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        }
        
        // MiscCallInfo
        cout << "Include MiscCallInfo mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            erbArg->SetMiscCallInfo(InitializeMiscCallInfo());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        erbArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
        erbArg->SetMiscCallInfo(InitializeMiscCallInfo());
    }

    /*
     * Ask user to include optional parameters
     */

    // BcsmEventCorrelationID
    cout << "Include BcsmEventCorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        erbArg->SetBcsmEventCorrelationID(InitializeDigits());
    }
    
    // EventSpecificInformationBCSM
    cout << "Include EventSpecificInformationBCSM optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        erbArg->SetEventSpecificInformationBCSM
            (InitializeEventSpecificInformationBCSM());
    }
    
    // LegID
    cout << "Include LegID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        erbArg->SetLegID(InitializeLegID());
    }
    
    // Extensions, not set

    // Encode message
    MsgEncode(erbArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Copy invoke ID of received component for use with for the
    // RequestEventReportBCSMEvent
    inv.SetInvokeID(recvCpt->GetInvokeID());

    // Set Invoke operation code
    inv.SetOperation(INAP_OP_eventReportBCSM);

    // Set Operation Class to 4 indicating that no response is expected on
    // error or success of the operation
    inv.SetClass(4);

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
        cout << "EventReportBCSM invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: EventReportBCSM invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete erbArg;
    erbArg = NULL;
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
    InitialDPArg* idpArg = new InitialDPArg();

    // Set Parameters for INAP message to send
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
        idpArg->SetServiceKey(InitializeServiceKey());
    }

    // DialledDigits
    cout << "Include DialledDigits optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetDialledDigits(InitializeCalledPartyNumber());
    }

    // CalledPartyNumber
    cout << "Include CalledPartyNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCalledPartyNumber(InitializeCalledPartyNumber());
    }

    // CallingPartyNumber
    cout << "Include CallingPartyNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCallingPartyNumber(InitializeCallingPartyNumber());
    }

    // CallingPartyBusinessGroupID
    cout << "Include CallingPartyBusinessGroupID optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCallingPartyBusinessGroupID
            (InitializeCallingPartyBusinessGroupID());
    }
    
    // CallingPartysCategory
    cout << "Include CallingPartysCategory optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCallingPartysCategory(InitializeCallingPartysCategory());
    }
    
    // CallingPartySubaddress
    cout << "Include CallingPartySubaddress optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCallingPartySubaddress(InitializeCallingPartySubaddress());
    }
    
    // CGEncountered
    cout << "Include CGEncountered optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetCGEncountered(InitializeCGEncountered());
    }

    // MiscCallInfo
    cout << "Include MiscCallInfo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetMiscCallInfo(InitializeMiscCallInfo());
    }

    // AdditionalCallingPartyNumber
    cout << "Include AdditionalCallingPartyNumber optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetAdditionalCallingPartyNumber
            (InitializeAdditionalCallingPartyNumber());
    }
    
    // BearerCapability
    cout << "Include BearerCapability optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetBearerCapability(InitializeBearerCapability());
    }
    
    // EventTypeBCSM
    cout << "Include EventTypeBCSM optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        idpArg->SetEventTypeBCSM(InitializeEventTypeBCSM());
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
    MsgEncode(idpArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_initialDP);

    // Set Operation Class to 2 indicating that a response is only expected on
    // error
    inv.SetClass(2);

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
        cout << "InitialDP invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: InitialDP invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete idpArg;
    idpArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RequestCurrentStatusReport invoke component.
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
sendRequestCurrentStatusReport(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    ResourceID *rcsrArg;

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestCurrentStatusReport Parameters:" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;

    rcsrArg = new ResourceID(InitializeResourceID());

    // Encode message
    MsgEncode(rcsrArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_requestCurrentStatusReport);

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
        cout << "RequestCurrentStatusReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: RequestCurrentStatusReport invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rcsrArg;
    rcsrArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RequestEveryStatusChangeReport result
 *      component.
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
 *      The dialog associated with the result component is either a continue
 *      or end dialog depending on what the user selected.
 *
 *  See Also:
 ****************************************************************************/
int
sendRequestCurrentStatusReportResult(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                                     TCAP_Component *recvCpt)
{
    int result = 0;
    int timeout = 0;
    Octets *encOctets;
    string str;
    TCAP_Result res;
    RequestCurrentStatusReportResultArg* rcsrrArg =
        new RequestCurrentStatusReportResultArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestCurrentStatusReportResult Parameters:" << endl;
    cout << "----------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // ResourceStatus
        cout << "Include ResourceStatus mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            rcsrrArg->SetResourceStatus(InitializeResourceStatus());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        rcsrrArg->SetResourceStatus(InitializeResourceStatus());
    }

    /*
     * Ask user to include optional parameters
     */
    
    // ResourceID
    cout << "Include ResourceID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rcsrrArg->SetResourceID(InitializeResourceID());
    }
    
    // Extensions, not set

    // Encode message
    MsgEncode(rcsrrArg, &encOctets, str);

    // Copy invoke ID of received component for use with for the
    // RequestCurrentStatusReportResult
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set Invoke operation code
    res.SetOperation(INAP_OP_requestCurrentStatusReport);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Send a InitialDP invoke component
    traceComponent(&res);
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "RequestCurrentStatusReportResult result send success."
             << endl;
    }
    else
    {
        cout << "WARNING: RequestCurrentStatusReportResult result send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rcsrrArg;
    rcsrrArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RequestEveryStatusChangeReport invoke
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
sendRequestEveryStatusChangeReport(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    RequestEveryStatusChangeReportArg* rescrArg =
        new RequestEveryStatusChangeReportArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestEveryStatusChangeReport Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // Ask user to include ResourceID mandatory parameter
        cout << "Include ResourceID mandatory parameter? [y]es/[n]o: " << endl;
        if (getYesOrNo() == 1)
        {
            rescrArg->SetResourceID(InitializeResourceID());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        rescrArg->SetResourceID(InitializeResourceID());
    }

    /*
     * Ask user to include optional parameters
     */

    // CorrelationID
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rescrArg->SetCorrelationID(InitializeCorrelationID());
    }

    // MonitorDuration
    cout << "Include MonitorDuration optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rescrArg->SetMonitorDuration(InitializeDuration());
    }
    
    // Extensions, not set

    // Encode message
    MsgEncode(rescrArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_requestEveryStatusChangeReport);

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
        cout << "RequestEveryStatusChangeReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: RequestEveryStatusChangeReport invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rescrArg;
    rescrArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RequestFirstStatusMatchReport invoke
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
sendRequestFirstStatusMatchReport(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout = 0;
    ITS_USHORT invokeID;
    TCAP_Invoke inv;
    TCAP_Continue cont;
    TCAP_End end;
    Octets *encOctets;
    string str;
    RequestFirstStatusMatchReportArg* rfsmrArg =
        new RequestFirstStatusMatchReportArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestFirstStatusMatchReport Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    /*
     * Ask user to include optional parameters
     */

    // Ask user to include ResourceID optional parameter
    cout << "Include ResourceID optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        rfsmrArg->SetResourceID(InitializeResourceID());
    }
    
    // Ask user to include ResourceStatus optional parameter
    cout << "Include ResourceStatus optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        rfsmrArg->SetResourceStatus(InitializeResourceStatus());
    }
    
    // Ask user to include CorrelationID optional parameter
    cout << "Include CorrelationID optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        rfsmrArg->SetCorrelationID(InitializeCorrelationID());
    }
    
    // Ask user to include MonitorDuration optional parameter
    cout << "Include MonitorDuration optional parameter? [y]es/[n]o: " << endl;
    if (getYesOrNo() == 1)
    {
        rfsmrArg->SetMonitorDuration(InitializeDuration());
    }

    // Ask user to include BearerCapability optional parameter
    cout << "Include BearerCapability optional parameter? [y]es/[n]o: "
         << endl;
    if (getYesOrNo() == 1)
    {
        rfsmrArg->SetBearerCapability(InitializeBearerCapability());
    }

    // Extensions, not set

    // Encode message
    MsgEncode(rfsmrArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_requestFirstStatusMatchReport);

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
        cout << "RequestFirstStatusMatchReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: RequestFirstStatusMatchReport invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rfsmrArg;
    rfsmrArg = NULL;
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
    RequestReportBCSMEventArg* rrbeArg = new RequestReportBCSMEventArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestEveryStatusChangeReport Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    // Ask the user to send a badly encoded message or a valid message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        /*
         * User wanted to send a badly encoded INAP message
         */

        // Ask user to include BcsmEvents mandatory parameter
        cout << "Include BcsmEvents mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            rrbeArg->SetBcsmEvents(InitializeRequestReportBCSMEventArg_BcsmEvents());
        }
    }
    else
    {
        /*
         * User wanted to send a valid INAP message
         */
        rrbeArg->SetBcsmEvents(InitializeRequestReportBCSMEventArg_BcsmEvents());
        
    }

    /*
     * Ask user to include optional parameters
     */

    // Ask user to include BcsmEventCorrelationID optinal parameter
    cout << "Include BcsmEventCorrelationID optinal parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rrbeArg->SetBcsmEventCorrelationID(InitializeDigits());
    }

    // Extensions, not set

    // Encode message
    MsgEncode(rrbeArg, &encOctets, str);

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
    inv.SetOperation(INAP_OP_requestReportBCSMEvent);

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
        cout << "RequestReportBCSMEvent invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: RequestReportBCSMEvent invoke send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rrbeArg;
    rrbeArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a StatusReport invoke component.
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
sendStatusReport(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                 TCAP_Component *recvCpt)
{
    int result = 0;
    int timeout = 0;
    TCAP_Invoke inv;
    Octets *encOctets;
    string str;
    StatusReportArg* srArg = new StatusReportArg();

    // Set Parameters for INAP message to send
    cout << endl;
    cout << "Setting RequestEveryStatusChangeReport Parameters:" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << endl;

    /*
     * Ask user to include optional parameters
     */

    // ResourceStatus
    cout << "Include ResourceStatus optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        srArg->SetResourceStatus(InitializeResourceStatus());
    }

    // CorrelationId
    cout << "Include CorrelationId optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        srArg->SetCorrelationID(InitializeCorrelationID());
    }

    // ResourceId
    cout << "Include ResourceId optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        srArg->SetResourceID(InitializeResourceID());
    }
    

    // ReportCondition
    cout << "Include ReportCondition optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        srArg->SetReportCondition(InitializeReportCondition());
    }
    
    // Extensions, not set

    // Encode message
    MsgEncode(srArg, &encOctets, str);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Copy invoke ID of received component for use with for the
    // RequestEventReportBCSMEvent
    inv.SetInvokeID(recvCpt->GetInvokeID());

    // Set Invoke operation code
    inv.SetOperation(INAP_OP_statusReport);

    // Set Operation Class to 4 indicating that no response is expected
    // on procedure success or failure
    inv.SetClass(4);

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
        cout << "StatusReport invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: StatusReport invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete srArg;
    srArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

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

    // Printout abort dialog information
    traceDialogue(&abort);

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

    // Printout component information
    traceComponent(&cancel);

    // Send cancel component
    result = TCAP_Component::Send(handle, &end, &cancel);

    // Check if cancel component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Cancel component sent successfully
        cout << "Cancel component send success." << endl;
        cout << endl;

        //Printout dialog information
        traceDialogue(&end);

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

    // Ask user to select an error code for this error component
    cout << "Select Error Code:" << endl;
    cout << "------------------" << endl;
    cout << '[' << setw(2) << INAP_ERR_cancelled
         << "] Cancelled" << endl;
    cout << '[' << setw(2) << INAP_ERR_cancelFailed
         << "] CancelFailed" << endl;
    // Missing one in inap.h
    cout << '[' << setw(2) << INAP_ERR_eTCFailed
         << "] ETCFailed" << endl;
    cout << '[' << setw(2) << INAP_ERR_improperCallerResponse
         << "] ImproperCallerResponse" << endl;
    cout << '[' << setw(2) << INAP_ERR_missingCustomerRecord
         << "] MissingCustomerRecord" << endl;
    cout << '[' << setw(2) << INAP_ERR_missingParameter
         << "] MissingParameter" << endl;
    cout << '[' << setw(2) << INAP_ERR_parameterOutOfRange
         << "] ParameterOutOfRange" << endl;
    cout << '[' << setw(2) << INAP_ERR_requestedInfoError
         << "] RequestedInfoError" << endl;
    cout << '[' << setw(2) << INAP_ERR_systemFailure
         << "] SystemFailure" << endl;
    cout << '[' << setw(2) << INAP_ERR_taskRefused
         << "] TaskRefused" << endl;
    cout << '[' << setw(2) << INAP_ERR_unavailableResource
         << "] UnavailableResource" << endl;
    cout << '[' << setw(2) << INAP_ERR_unexpectedComponentSequence
         << "] UnexpectedComponentSequence" << endl;
    cout << '[' << setw(2) << INAP_ERR_unexpectedDataValue
         << "] UnexpectedDataValue" << endl;
    cout << '[' << setw(2) << INAP_ERR_unexpectedParameter
         << "] UnexpectedParameter" << endl;
    cout << '[' << setw(2) << INAP_ERR_unknownLegID
         << "] UnknownLegID" << endl;
    cout << '[' << setw(2) << INAP_ERR_unknownResource
         << "] UnknownResource" << endl;
    cout << endl;

    // Get error code selected by user
    errorCode = (ITS_OCTET)getSelection(0, 18);
    
    // Set error code for the component
    error.SetError(errorCode);

    // Printout error component information
    traceComponent(&error);

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
    return result;
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

    // Ask user to select problem type    
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
    problemType = (ITS_OCTET)getSelection(0, 3);
    cout << endl;

    // Determine problem type seleceted by the user
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
        problemCode = (ITS_OCTET)getSelection(0, 4);
        break;
    }
    cout << endl;

    // Set reject component problem type and code
    reject.SetProblem(problemType, problemCode);

    // Printout reject component information
    traceComponent(&reject);

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
    int result = 0;
    //ITS_OCTET appContext[50], userInfo[50];
    //int appContext = 0;
    //int userInfo = 0;
    TCAP_End end;

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

    // Printout end dialog information
    traceDialogue(&end);

    // Send the end dialog
    result = TCAP_Dialogue::Send(handle, &end);

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
 *      This function will decode an encoded INAP message in the parameter
 *      field of the component.
 *
 *  Input Parameters:
 *      code - INAP operation code defined in inap.h
 *      octets - pointer to the encoded value of the INAP message
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
decodeINAPMsg(ITS_LONG code, Octets *octets)
{
    string str;
    CallGapArg *cgArg = new CallGapArg();
    CallInformationReportArg *cirepArg = new CallInformationReportArg();
    CallInformationRequestArg *cireqArg = new CallInformationRequestArg();
    CancelStatusReportRequestArg *csrrArg = new CancelStatusReportRequestArg();
    ConnectArg *cArg = new ConnectArg();
    EventReportBCSMArg *erbArg = new EventReportBCSMArg();
    InitialDPArg *idpArg = new InitialDPArg();
    ResourceID *rcsrArg = new ResourceID();
    RequestEveryStatusChangeReportArg *rescrArg =
        new RequestEveryStatusChangeReportArg();
    RequestFirstStatusMatchReportArg *rfsmrArg =
        new RequestFirstStatusMatchReportArg();
    RequestReportBCSMEventArg *rrbeArg = new RequestReportBCSMEventArg();
    StatusReportArg *srArg = new StatusReportArg();

    // Determine what INAP message the user selected to send
    switch (code)
    {
    case INAP_OP_callGap:
        // Decoding CallGap
        cout << "Decoding CallGap encoded value." << endl;
        MsgDecode(cgArg, octets, str);
        break;

    case INAP_OP_callInformationReport:
        // Decoding CallInformationReport
        cout << "Decoding CallInformationReport encoded value." << endl;
        MsgDecode(cirepArg, octets, str);
        break;

    case INAP_OP_callInformationRequest:
        // Decoding CallInformationRequest
        cout << "Decoding CallInformationRequest encoded value." << endl;
        MsgDecode(cireqArg, octets, str);
        break;

    case INAP_OP_cancelStatusReportRequest:
        // Decoding CancelStatusReportRequest
        cout << "Decoding CancelStatusReportRequest encoded value." << endl;
        MsgDecode(csrrArg, octets, str);
        break;

    case INAP_OP_connect:
        // Decoding Connect
        cout << "Decoding Connect encoded value." << endl;
        MsgDecode(cArg, octets, str);
        break;

    case INAP_OP_eventReportBCSM:
        // Decoding EventReportBCSM
        cout << "Decoding EventReportBCSM encoded value." << endl;
        MsgDecode(erbArg, octets, str);
        break;

    case INAP_OP_initialDP:
        // Decoding InitialDP
        cout << "Decoding InitialDP encoded value." << endl;
        MsgDecode(idpArg, octets, str);
        break;

    case INAP_OP_requestCurrentStatusReport:
        // Decoding RequestCurrentStatusReport
        cout << "Decoding RequestCurrentStatusReport encoded value." << endl;
        MsgDecode(rcsrArg, octets, str);
        break;

    case INAP_OP_requestEveryStatusChangeReport:
        // Decoding RequestEveryStatusChangeReport
        cout << "Decoding RequestEveryStatusChangeReport encoded value."
             << endl;
        MsgDecode(rescrArg, octets, str);
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        // Decoding RequestFirstStatusMatchReport
        cout << "Decoding RequestFirstStatusMatchReport encoded value."
             << endl;
        MsgDecode(rfsmrArg, octets, str);
        break;

    case INAP_OP_requestReportBCSMEvent:
        // Decoding RequestReportBCSMEvent
        cout << "Decoding RequestReportBCSMEvent encoded value." << endl;
        MsgDecode(rrbeArg, octets, str);
        break;
        
    case INAP_OP_statusReport:
        // Decoding StatusReport
        cout << "Decoding StatusReport encoded value." << endl;
        MsgDecode(srArg, octets, str);
        break;

    default:
        /*
         * If this is reached the operation is either not defined or not
         * included in this test program.
         */
        cout << "WARNING: Unrecognized INAP Operation code or not included"
             << endl;
        cout << "         for in this demo." << endl;
        cout << endl;
        break;
    }
}
