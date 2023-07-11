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
 *  ID: $Id: SendOrReceive.cpp,v 9.1 2005/03/23 12:51:33 cvsadmin Exp $
 *
 * LOG: $Log: SendOrReceive.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:51:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:30  cvsadmin
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
 * LOG: Revision 3.1  2000/08/15 23:57:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:24  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.30  1999/11/01 17:26:36  cbascon
 * LOG:
 * LOG:
 * LOG: Should have log entries on files now.
 * LOG:
 ****************************************************************************/

#include <iostream>
#include <iomanip>
#include <mbstring.h>

#include <its++.h>
#include <its_app.h>
#include <tcap++.h>
#include <sccp++.h>

#include <GSMMAPP2P.H>
#include <tools.h>
#include "SendOrReceive.h"
#include "trace.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace GSMMAP;
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will encode a GSMMAP message.
 *
 *  Input Parameters:
 *      p - pointer to the GSMMAP message to be encoded
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      octets - used to store the encoded value of the GSMMAP message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
encodeGSMMAPMsg(AsnObject* p, Octets** octets)
{
    // Print ASN.1 value before encoding.
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 value before encoding..." << endl;
    cout << endl << *p << endl;

    // Encode using ASN.1 BER.
    Octets* tmpOctets;

    try
    {
        tmpOctets = p->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during encoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 encoded value..." << endl;
    cout << endl << *tmpOctets << endl;

    *octets = tmpOctets;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will decode an encoded GSMMAP message.
 *
 *  Input Parameters:
 *      octets - the encoded value of a GSMMAP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      p - storage for decoded GSMMAP message
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
MsgDecode(AsnObject* p, Octets* octets)
{
    // Decoding using ASN.1 BER.
    try
    {
        p->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Exception during decoding phase..." << endl;
        cout << exc.GetDescription() << endl;
        cout << "Exit test..." << endl;
    }

    // Print ASN.1 value after decoding.
    cout << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Printing ASN.1 value after decoding..." << endl;
    cout << endl << *p << endl;
}

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
    cout << "------------------------MAIN MENU----------------------" << endl;
    cout << endl;
    cout << "[" << setw(2) << dec << (int)TestSCCPUIS
         << "] Send SCCP User In Service Message" << endl;
    cout << "[" << setw(2) << dec << (int)TestSCCPUOS
         << "] Send SCCP User Out of Service Message" << endl;
    cout << endl;
    cout << "Select Message to Send:" << endl;
    cout << "-----------------------" << endl;
    cout << "[" << setw(2) << (int)TestActivateTraceModeArg
         << "] ActivateTraceModeArg" << endl;
    cout << "[" << setw(2) << (int)TestDeactivateTraceModeArg
         << "] DeactivateTraceModeArg" << endl;
    cout << "[" << setw(2) << (int)TestForwardGroupCallSignallingArg
         << "] ForwardGroupCallSignallingArg" << endl;
    cout << "[" << setw(2) << (int)TestMTForwardSMArg
         << "] MTForwardSMArg" << endl;
    cout << "[" << setw(2) << (int)TestPrepareGroupCallArg
         << "] PrepareGroupCallArg" << endl;
    cout << "[" << setw(2) << (int)TestProvideRoamingNumberArg
         << "] ProvideRoamingNumberArg" << endl;
    cout << "[" << setw(2) << (int)TestReportSMDeliveryStatusArg
         << "] ReportSMDeliveryStatusArg" << endl;
    cout << "[" << setw(2) << (int)TestRoutingInfoForSMArg
         << "] RoutingInfoForSMArg" << endl;
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
 *      select a response for an GSMMAP message.
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
    cout << "Send GSMMAP Response:" << endl;
    cout << "-------------------" << endl;
    cout << "[" << setw(2) << (int)TestMTForwardSMRes
         << "] MTForwardSMRes" << endl;
    cout << "[" << setw(2) << (int)TestProvideRoamingNumberRes
         << "] ProvideRoamingNumberRes" << endl;
    cout << "[" << setw(2) << (int)TestReportSMDeliveryStatusRes
         << "] ReportSMDeliveryStatusRes" << endl;
    cout << "[" << setw(2) << (int)TestRoutingInfoForSMRes
         << "] RoutingInfoForSMRes" << endl;
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
getSelection(int startRange, int endRange)
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
    TCAP_Dialogue *recvDlg = NULL;
    TCAP_Component *recvCpt = NULL;

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

                // Determine what kind of component was received
                switch (recvCpt->GetComponentType())
                {
                case TCPPT_TC_INVOKE:
                    // Get operation code of GSMMAP procedure
                    ((TCAP_Invoke *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Invoke *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeGSMMAPInvoke(op, octets);

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_L:
                    // Determine if the GSMMAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeGSMMAPResult(op, octets);

                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_RESULT_NL:
                    // Determine if the GSMMAP message received does not require
                    // a response
                    ((TCAP_Result *)recvCpt)->GetOperation(op);

                    // Get the parameter of the invoke component
                    ((TCAP_Result *)recvCpt)->GetParameter(buf);

                    // Create an Octets object for storing the encoded message
                    // The decode function needs the encoded message in Octets
                    // form to decode
                    octets = new Octets(buf);

                    // Decode the parameter field of the invoke component
                    decodeGSMMAPResult(op, octets);

                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;

                    // Free allocated memory
                    delete octets;
                    break;

                case TCPPT_TC_U_ERROR:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_CANCEL:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_CANCEL:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_L_REJECT:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_R_REJECT:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                case TCPPT_TC_U_REJECT:
                    // Indicate that the GSMMAP message received does not
                    // require a response
                    noResponse = 1;
                    break;

                default:
                    cout << "WARNING: Unknown component received" << endl;
                    cout << "         ComponentType: "
                         << dec << (int)recvCpt->GetComponentType() << endl;
                    cout << endl;
                }
                
                // Will stop waiting for an Event when a component is received
                // since this test program only sends one component for each
                // dialog sent
                keepWaiting = 0;

                // Check if a response needs to be sent to the remote application
                if (!noResponse)
                {
                    // Send an GSMMAP response
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
 *      This function will send a GSMMAP invoke component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      recvdid - dialog Id of the dialog received using waitForEvent()
 *      orig - originating address of the appication instance
 *      dest - destination address of remote application
 *      msgtag - tag for corresponding GSMMAP message to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the invoke component was sent successfully.
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

        // Allocate a unique Dialog ID for the Begin dialog and set the
        TCAP_AllocateDialogueId(&begdid);
        beg.SetDialogueID(begdid);

        // Set Quality of Service for this transaction. QOS_RET_OPT indicates
        // that a response is expected.
        beg.SetQualityOfService(QOSI_RET_OPT);

        // Set the dialog Originating address
        beg.SetOrigAddr(orig);

        // Set the dialog Destination address
        beg.SetDestAddr(dest);

        // Set the Originating Point Code
        beg.SetOPC(orig.GetPointCode());

        // Set the Destination Point Code
        beg.SetDPC(dest.GetPointCode());
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

        // Set Quality of Service for this transaction. QOS_RET_OPT indicates
        // that a response is expected.
        cont.SetQualityOfService(QOSI_RET_OPT);
    }

    // Determine what GSMMAP message the user selected to send
    switch (msgtag)
    {
    case TestActivateTraceModeArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendActivateTraceModeArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendActivateTraceModeArg(handle, &cont);
        }
        break;

    case TestDeactivateTraceModeArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendDeactivateTraceModeArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendDeactivateTraceModeArg(handle, &cont);
        }
        break;

    case TestForwardGroupCallSignallingArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendForwardGroupCallSignallingArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendForwardGroupCallSignallingArg(handle, &cont);
        }
        break;

    case TestMTForwardSMArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendMTForwardSMArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendMTForwardSMArg(handle, &cont);
        }
        break;

    case TestPrepareGroupCallArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendPrepareGroupCallArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendPrepareGroupCallArg(handle, &cont);
        }
        break;

    case TestProvideRoamingNumberArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendProvideRoamingNumberArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendProvideRoamingNumberArg(handle, &cont);
        }
        break;

    case TestReportSMDeliveryStatusArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendReportSMDeliveryStatusArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendReportSMDeliveryStatusArg(handle, &cont);
        }
        break;

    case TestRoutingInfoForSMArg:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a begin dialog
            result = sendRoutingInfoForSMArg(handle, &beg);
        }
        else
        {
            // User wanted to send a begin dialog
            result = sendRoutingInfoForSMArg(handle, &cont);
        }
        break;

    default:
        // This should not be reached
        break;
    }

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // Printout dialog information
            traceDialogue(&beg);
            result = TCAP_Dialogue::Send(handle, &beg);
        }
        else
        {
            // Printout dialog information
            traceDialogue(&cont);
            result = TCAP_Dialogue::Send(handle, &cont);
        }
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to an GSMMAP invoke component.
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
    ITS_UINT opc;
    TCAP_Continue cont;
    TCAP_End end;

    ////////////////////////////
    // Display Send Query Menu
    displayResponseMenu();
    responseChoice = getSelection(1, 10);

    // User is not asked to choose between a Continue dialog and an End dialog
    // if the user wanted to send an Abort dialog or an End dialog with no
    // component
    if (responseChoice >= 1 && responseChoice <= 6)
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

            // Set Originating Point Code
            opc = ((SCCP_Address)origAddr).GetPointCode();
            cont.SetOPC(opc);

            // Set Originating address
            cont.SetOrigAddr(origAddr);

            // Copy the dialog ID of the received Dialog
            cont.SetDialogueID(recvDlg->GetDialogueID());

            // Set Quality of service
            cont.SetQualityOfService(QOSI_RET_OPT);
        }
        else
        {
            // User wants to send an end dialog
            // Set End dialog parameters

            // Copy the dialog ID of the received Dialog
            end.SetDialogueID(recvDlg->GetDialogueID());

            // Set termination type to Basic End
            end.SetPreArrangedEnd(false);

            // Set Quality of service
            //end.SetQualityOfService(flags, slsKey, priority);
        }
    }

    // Determine what GSMMAP message the user selected to send
    switch (responseChoice)
    {
    case TestMTForwardSMRes:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            result = sendMTForwardSMRes(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send an end dialog
            result = sendMTForwardSMRes(handle, &end, recvCpt);
        }
        break;

    case TestProvideRoamingNumberRes:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            result = sendProvideRoamingNumberRes(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send an end dialog
            result = sendProvideRoamingNumberRes(handle, &end, recvCpt);
        }
        break;

    case TestReportSMDeliveryStatusRes:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            result = sendReportSMDeliveryStatusRes(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send an end dialog
            result = sendReportSMDeliveryStatusRes(handle, &end, recvCpt);
        }
        break;

    case TestRoutingInfoForSMRes:
        // Check what kind of dialog the user wanted to send
        if (dlgChoice == 1)
        {
            // User wanted to send a continue dialog
            result = sendRoutingInfoForSMRes(handle, &cont, recvCpt);
        }
        else
        {
            // User wanted to send an end dialog
            result = sendRoutingInfoForSMRes(handle, &end, recvCpt);
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
    if (responseChoice >= 1 && responseChoice <= 6 && result == ITS_SUCCESS)
    {
        // Check what kind of dialog the user wanted to send: Continue or End
        if (dlgChoice == 1)
        {
            // Printout dialog information
            traceDialogue(&cont);
            result = TCAP_Dialogue::Send(handle, &cont);

            // Check if continue dialog was sent successfully
            if (result == ITS_SUCCESS)
            {
                cout << "Continue dialog send success." << endl;
            }
            else
            {
                cout << "WARNING: Continue dialog send failed." << endl;
                cout << "  Error: " << result << endl;
            }
        }
        else
        {
            // Printout dialog information
            traceDialogue(&end);
            result = TCAP_Dialogue::Send(handle, &end);

            // Check if end dialog was sent successfully
            if (result == ITS_SUCCESS)
            {
                cout << "End dialog send success." << endl;
            }
            else
            {
                cout << "WARNING: End dialog send failed." << endl;
                cout << "  Error: " << result << endl;
            }
        }
    }
    return result;
}

/*
 ************************************************************************
 *  Purpose:
 *      This function will decode an encoded GSMMAP message in the parameter
 *      field of an invoke component.
 *
 *  Input Parameters:
 *      code - GSMMAP operation code defined in GSMMAPP2P.h
 *      octets - pointer to the encoded value of the GSMMAP message
 *
 * Input/Output Parameters:
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
 ************************************************************************/
void
decodeGSMMAPInvoke(ITS_LONG code, Octets *octets)
{
    ActivateTraceModeArg *atmArg = new ActivateTraceModeArg();
    DeactivateTraceModeArg *dtmArg = new DeactivateTraceModeArg();
    ForwardGroupCallSignallingArg *fgcsArg =
        new ForwardGroupCallSignallingArg();
    InsertSubscriberDataArg *isdArg = new InsertSubscriberDataArg();
    MT_ForwardSM_Arg* mfsArg = new MT_ForwardSM_Arg();
    PrepareGroupCallArg *pgcArg = new PrepareGroupCallArg();
    ProvideRoamingNumberArg *prnArg = new ProvideRoamingNumberArg();
    RoutingInfoForSM_Arg *rifsArg = new RoutingInfoForSM_Arg();
    SendRoutingInfoArg *sriArg = new SendRoutingInfoArg();
    ReportSM_DeliveryStatusArg* rsdsArg = new ReportSM_DeliveryStatusArg();

    // Determine what GSMMAP message the user selected to send
    switch (code)
    {
    case OP_activateTraceMode:
        // Decoding ActivateTraceModeArg
        cout << "Decoding ActivateTraceModeArg." << endl;
        MsgDecode(atmArg, octets);
        break;

    case OP_deactivateTraceMode:
        // Decoding DeactivateTraceModeArg
        cout << "Decoding DeactivateTraceModeArg." << endl;
        MsgDecode(dtmArg, octets);
        break;

    case OP_forwardGroupCallSignalling:
        // Decoding ForwardGroupCallSignallingArg
        cout << "Decoding ForwardGroupCallSignallingArg." << endl;
        MsgDecode(fgcsArg, octets);
        break;

    case OP_mt_forwardSM:
        // Decoding MT_ForwardSM_Arg
        cout << "Decoding MT_ForwardSM_Arg." << endl;
        MsgDecode(mfsArg, octets);
        break;

    case OP_prepareGroupCall:
        // Decoding PrepareGroupCallArg
        cout << "Decoding PrepareGroupCallArg." << endl;
        MsgDecode(pgcArg, octets);
        break;

    case OP_provideRoamingNumber:
        // Decoding ProvideRoamingNumberArg
        cout << "Decoding ProvideRoamingNumberArg." << endl;
        MsgDecode(prnArg, octets);
        break;

    case OP_reportSM_DeliveryStatus:
        // Decoding ReportSM_DeliveryStatusArg
        cout << "Decoding ReportSM_DeliveryStatusArg." << endl;
        MsgDecode(rsdsArg, octets);
        break;

    case OP_sendRoutingInfoForSM:
        // Decoding RoutingInfoForSMArg
        cout << "Decoding RoutingInfoForSMArg." << endl;
        MsgDecode(rifsArg, octets);
        break;

    case OP_sendRoutingInfo:
        // Decoding SendRoutingInfoArg
        cout << "Decoding SendRoutingInfoArg." << endl;
        MsgDecode(sriArg, octets);
        break;

    default:
        /*
         * If this is reached the operation is either not defined or not
         * included in this test program.
         */
        cout << "WARNING: Unrecognized GSMMAP Operation code or not included"
             << endl;
        cout << "         for in this demo." << endl;
        cout << "         Operation Code = " << dec << (int)code << endl;
        cout << endl;
        break;
    }
}

/*
 ************************************************************************
 *  Purpose:
 *      This function will decode an encoded GSMMAP message in the parameter
 *      field of a result component.
 *
 *  Input Parameters:
 *      code - GSMMAP operation code defined in GSMMAPP2P.h
 *      octets - pointer to the encoded value of the GSMMAP message
 *
 * Input/Output Parameters:
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
 ************************************************************************/
void
decodeGSMMAPResult(ITS_LONG code, Octets *octets)
{
    InsertSubscriberDataRes *isdRes = new InsertSubscriberDataRes();
    MT_ForwardSM_Res* mfsRes = new MT_ForwardSM_Res();
    ProvideRoamingNumberRes *prnRes = new ProvideRoamingNumberRes();
    ReportSM_DeliveryStatusRes* rsdsRes = new ReportSM_DeliveryStatusRes();
    RoutingInfoForSM_Res *rifsRes = new RoutingInfoForSM_Res();
    SendRoutingInfoRes *sriRes = new SendRoutingInfoRes();

    // Determine what GSMMAP message the user selected to send
    switch (code)
    {
    case OP_mt_forwardSM:
        // Decoding 
        cout << "Decoding MT_ForwardSM_Res." << endl;
        MsgDecode(mfsRes, octets);
        break;

    case OP_provideRoamingNumber:
        // Decoding ProvideRoamingNumberRes
        cout << "Decoding ProvideRoamingNumberRes." << endl;
        MsgDecode(prnRes, octets);
        break;

    case OP_reportSM_DeliveryStatus:
        // Decoding reportSM_DeliveryStatusRes
        cout << "Decoding ReportSM_DeliveryStatusRes." << endl;
        MsgDecode(rsdsRes, octets);
        break;

    case OP_sendRoutingInfoForSM:
        // Decoding RoutingInfoForSM_Res
        cout << "Decoding RoutingInfoForSM_Res." << endl;
        MsgDecode(rifsRes, octets);
        break;
    
    case OP_sendRoutingInfo:
        // Decoding SendRoutingInfoRes
        cout << "Decoding SendRoutingInfoRes." << endl;
        MsgDecode(sriRes, octets);
        break;

    default:
        /*
         * If this is reached the operation is either not defined or not
         * included in this test program.
         */
        cout << "WARNING: Unrecognized GSMMAP Operation code or not included"
             << endl;
        cout << "         for in this demo." << endl;
        cout << "         Operation Code = " << dec << (int)code << endl;
        cout << endl;
        break;
    }
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

    // Generic error codes.
    cout << "[" << setw(2) << dec << (int)ERR_systemFailure
         << "] SystemFailure" << endl;
    cout << "[" << setw(2) << (int)ERR_dataMissing
         << "] DataMissing" << endl;
    cout << "[" << setw(2) << (int)ERR_unexpectedDataValue
         << "] UnexpectedDataValue" << endl;
    cout << "[" << setw(2) << (int)ERR_facilityNotSupported
         << "] FacilityNtSupported" << endl;
    cout << "[" << setw(2) << (int)ERR_incompatibleTerminal
         << "] IncompatibleTerminal" << endl;
    cout << "[" << setw(2) << (int)ERR_resourceLimitation
         << "] ResourceLimitation" << endl;
    cout << endl;

    // Identification and numbering error codes.
    cout << "[" << setw(2) << (int)ERR_unknownSubscriber
         << "] UnknownSubscriber" << endl;
    cout << "[" << setw(2) << (int)ERR_numberChanged
         << "] NumberChanged" << endl;
    cout << "[" << setw(2) << (int)ERR_unknownMSC
         << "] UnknownMSC" << endl;
    cout << "[" << setw(2) << (int)ERR_unidentifiedSubscriber
         << "] UnidentifiedSubscriber" << endl;
    cout << "[" << setw(2) << (int)ERR_unknownEquipment
         << "] UnknownEquipment" << endl;

    // Subscription error codes.
    cout << "[" << setw(2) << (int)ERR_roamingNotAllowed
         << "] RoamingNotAllowed" << endl;
    cout << "[" << setw(2) << (int)ERR_illegalSubscriber
         << "] IllegalSubscriber" << endl;
    cout << "[" << setw(2) << (int)ERR_illegalEquipment
         << "] IllegalEquipment" << endl;
    cout << "[" << setw(2) << (int)ERR_bearerServiceNotProvisioned
         << "] BearerServiceNotProvisioned" << endl;
    cout << "[" << setw(2) << (int)ERR_teleserviceNotProvisioned
         << "] TeleserviceNotProvisioned" << endl;

    // Handover error codes.
    cout << "[" << setw(2) << (int)ERR_noHandoverNumberAvailable
         << "] NoHandoverNumberAvailable" << endl;
    cout << "[" << setw(2) << (int)ERR_subsequentHandoverFailure
         << "] SubsequentHandoverFailure" << endl;

    // Operation and maintenance error codes.
    cout << "[" << setw(2) << (int)ERR_tracingBufferFull
         << "] TracingBufferFull" << endl;

    // Call handling error codes.
    cout << "[" << setw(2) << (int)ERR_noRoamingNumberAvailable
         << "] NoRoamingNumberAvailable" << endl;
    cout << "[" << setw(2) << (int)ERR_absentSubscriber
         << "] AbsentSubscriber" << endl;
    cout << "[" << setw(2) << (int)ERR_busySubscriber
         << "] BusySubscriber" << endl;
    cout << "[" << setw(2) << (int)ERR_noSubscriberReply
         << "] NoSubscriberReply" << endl;
    cout << "[" << setw(2) << (int)ERR_callBarred
         << "] CallBarred" << endl;
    cout << "[" << setw(2) << (int)ERR_forwardingFailed
         << "] ForwardingFailed" << endl;
    cout << "[" << setw(2) << (int)ERR_or_NotAllowed
         << "] Or_NotAllowed" << endl;
    cout << "[" << setw(2) << (int)ERR_forwardingViolation
         << "] ForwardingViolation" << endl;
    cout << "[" << setw(2) << (int)ERR_cug_Reject
         << "] Cug_Reject" << endl;

    // Any time interrogation error codes.
    cout << "[" << setw(2) << (int)ERR_ati_NotAllowed
         << "] Ati_NotAllowed" << endl;

    // Group Call error codes
    cout << "[" << setw(2) << (int)ERR_noGroupCallNumberAvailable
         << "] NoGroupCallNumberAvailable" << endl;

    // Supplementary service error codes.
    cout << "[" << setw(2) << (int)ERR_illegalSS_Operation
         << "] IllegalSS_Operation" << endl;
    cout << "[" << setw(2) << (int)ERR_ss_ErrorStatus
         << "] Ss_ErrorStatus" << endl;
    cout << "[" << setw(2) << (int)ERR_ss_NotAvailable
         << "] Ss_NotAvailable" << endl;
    cout << "[" << setw(2) << (int)ERR_ss_SubscriptionViolation
         << "] Ss_SubscriptionViolation" << endl;
    cout << "[" << setw(2) << (int)ERR_ss_Incompatibility
         << "] Ss_Incompatibility" << endl;
    cout << "[" << setw(2) << (int)ERR_unknownAlphabet
         << "] UnknownAlphabet" << endl;
    cout << "[" << setw(2) << (int)ERR_ussd_Busy
         << "] Ussd_Busy" << endl;
    cout << "[" << setw(2) << (int)ERR_pw_RegistrationFailure
         << "] Pw_RegistrationFailure" << endl;
    cout << "[" << setw(2) << (int)ERR_negativePW_Check
         << "] NegativePW_Check" << endl;
    cout << "[" << setw(2) << (int)ERR_numberOfPW_AttemptsViolation
         << "] NumberOfPW_AttemptsViolation" << endl;
    cout << "[" << setw(2) << (int)ERR_shortTermDenial
         << "] ShortTermDenial" << endl;
    cout << "[" << setw(2) << (int)ERR_longTermDenial
         << "] LongTermDenial" << endl;

    // Short message service error codes.
    cout << "[" << setw(2) << (int)ERR_subscriberBusyForMT_SMS
         << "] SubscriberBusyForMT_SMS" << endl;
    cout << "[" << setw(2) << (int)ERR_sm_DeliveryFailure
         << "] Sm_DeliveryFailure" << endl;
    cout << "[" << setw(2) << (int)ERR_messageWaitingListFull
         << "] MessageWaitingListFull" << endl;
    cout << "[" << setw(2) << (int)ERR_absentsubscriberSM
         << "] AbsentsubscriberSM" << endl;
    cout << endl;

    // Get error code selected by user
    errorCode = (ITS_OCTET)getSelection(1, 72);
    
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
    cout << "Does SCCP Address hold an SSN? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        // Ask user for an SSN
        cout << "Please Enter SSN (decimal value): ";
        cin >> ssn;

        // Set the SSN field of the SCCP address
        addr->SetSSN(ssn);
    }

    // Ask user if the address has an Point Code
    cout << "Does SCCP Address hold an Point Code? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        // Ask user for point code
        cout << "Please Enter Point Code (decimal value) -> ";
        cin >> pc;

        // Set the point code field of the SCCP address
        addr->SetPointCode(pc);
    }

    // Ask user if the address has a global title
    cout << "Does SCCP Address hold a Global Title? [y]es/[n]o: ";
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
 *       addrIndicator - modified address indicator based on the GT indicator.
 *       ggtInfo - gtt information provided by user.
 *       len - length of the gtt Information.
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
    cout << "Address Information (ex: 1800456): " << endl;
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
