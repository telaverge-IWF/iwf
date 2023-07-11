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

#include <its++.h>
#include <its_app.h>
#include <tcap++.h>
#include <sccp++.h>

#include "SendRecv.h"
#include "trace.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif

ITS_HANDLE handle;

//
// termination handler
//
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    ITS_Terminate(handle);
    ITS_GlobalStop();

    exit(0);

#if defined(WIN32)
    return 1;
#endif
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This is the main function for the test program.
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
 *      When the application starts, the user is asked to select an
 *      instance number: 1 or 2. Two instances of this application is needed
 *      for the test.
 *
 *  See Also:
 ****************************************************************************/
int
main(int argc, char **argv)
{
    int result = 0;
    int hardCodeAddress = 0;    // 1 - use hardcoded address, 0 - user provided
    int keepGoing = 1;
    int choice = 0;
    int instance;
    int did;
    ITS_USHORT recvdid = 0;
    SCCP_CallingPartyAddr origAddr;
    SCCP_CalledPartyAddr destAddr;
    TCAP_End end;

// CTRL-C Handler to exit program mainly in receive mode
// This will however work for the receive mode too
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    cout << "*******************************************" << endl;
    cout << "*****                                 *****" << endl;
    cout << "*****  IntelliNet Technologies, Inc.  *****" << endl;
    cout << "*****  IntelliSS7 INAP C++ API Test   *****" << endl;
    cout << "*****                                 *****" << endl;
    cout << "*******************************************" << endl;
    cout << endl;
    cout << endl;

    // Ask the user to select an instance number for this application
    cout << "Select Instance for this Program:" << endl;
    cout << "---------------------------------" << endl;
    cout << "[1] Instance 1" << endl;
    cout << "[2] Instance 2" << endl;
    cout << endl;
    
    // Get user instance selection
    instance = getSelection(1, 2);

    // Determine which instance number this program is to use
    if (instance == 1)
    {
        // Setting the name of the application.
        // The name of the apllication is the name of the ITS .ini file
        // read by IntelliSS7
        ITS_Application::SetName("Send");

        if (hardCodeAddress)
        {
            // The first octet: 0x02 indicates the translation type
            // The rest of the 5 octets indicates the GTT number
            ITS_OCTET gttInfo[50] = { 0x02, 0x40, 0x77, 0x26, 0x06, 0x86 };

            ////////////////////////
            // Originating Address

            // Route using National standard
            origAddr.SetInternationalRouting(false);

            // Set the OPC field of the SCCP address
            origAddr.SetPointCode(1);

            // Set the SSN field of the SCCP address
            origAddr.SetSSN(3);

            // Route using PC and SSN?
            origAddr.SetRouteByPCSSN(true);

            ////////////////////////
            // Destination Address

            // Route using National standard
            destAddr.SetInternationalRouting(false);

            // Set the destination PC field of the SCCP address
            destAddr.SetPointCode(2);

            // Set the SSN field of the SCCP address
            destAddr.SetSSN(4);

            // Route using PC and SSN?
            // destAddr.SetRouteByPCSSN(true);

            // Global Title
            destAddr.SetGlobalTitle(SCCP_CPA_GTTI_TRANS, gttInfo, 6);
        }
    }
    else
    {
        // Setting the name of the application.
        // The name of the apllication is the name of the ITS .ini file
        // read by IntelliSS7
        ITS_Application::SetName("Recv");

        if (hardCodeAddress)
        {
            ITS_OCTET gttInfo[50] = { 0x02, 0x30, 0x16, 0x01, 0x60, 0x40 };

            ////////////////////////
            // Originating Address

            // Route using National standard
            origAddr.SetInternationalRouting(false);

            // Set originating point code
            origAddr.SetPointCode(2);

            // Set the SSN field of the SCCP address
            origAddr.SetSSN(4);

            // Route using PC and SSN?
            origAddr.SetRouteByPCSSN(true);

            ////////////////////////
            // Destination Address

            // Route using National standard
            destAddr.SetInternationalRouting(false);

            // Set the destination PC field of the SCCP address
            destAddr.SetPointCode(1);

            // Set the SSN field of the SCCP address
            destAddr.SetSSN(3);

            // Route using PC and SSN
            //destAddr.SetRouteByPCSSN(true);

            // Global Title
            destAddr.SetGlobalTitle(SCCP_CPA_GTTI_TRANS, gttInfo, 6);
        }
    }

    // Initializing IntelliSS7: using the SS7 Transport (for TCAP)
    // and only one app. is using the transport. Instance is used by the
    // vendor code to read the .ini file to configure the vendor's driver.
    handle = (ITS_HANDLE)ITS_Initialize(ITS_TCAP |
                                        ITS_TRANSPORT_SS7 |
                                        ITS_TRANSPORT_SINGLE_USER,
                                        instance);

    // Check if handle was created successfully
    if (handle != NULL)
    {
        cout << endl;
        cout << "Handle initialized successfully." << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "Failed to initialize handle!" << endl;
        cout << "Quiting..." << endl;

        // Do necessary IntelliSS7 clean up then exit
        ITS_Terminate(handle);
        exit(1);
    }

    if (!hardCodeAddress)
    {
        // Ask user to provide an originating address
        cout << endl;
        cout << "Setting Originating Address:" << endl;
        cout << "----------------------------" << endl;
        getSCCPAddress(&origAddr);
        traceSCCPAddress(origAddr);

        // Ask user to provide a destination address
        cout << endl;
        cout << "Setting Destination Address:" << endl;
        cout << "----------------------------" << endl;
        getSCCPAddress(&destAddr);
        traceSCCPAddress(destAddr);
    }

    // Keep looping until user decides to exit
    while (keepGoing)
    {
        // Display send Menu
        displayMainMenu();
        choice = getSelection(TestSCCPUIS, TestQuit);

        // Determine what operation the user selected
        switch (choice)
        {
        case TestSCCPUIS:
            // Send an SCCP User In Service message
            result = SCCP_SendUserInService(handle, origAddr.GetPointCode(),
                                            origAddr.GetSSN());

            // Check if SCCP message was sent successfully
            if (result == ITS_SUCCESS)
            {
                cout << "SCCP User In Service message send success." << endl;
            }
            else
            {
                cout << "WARNING: SCCP User In Service message send failed."
                     << endl;
                cout << "  Error: " << result << endl;
            }
            break;

        case TestSCCPUOS:
            // Send an SCCP User out of Service message
            result = SCCP_SendUserOutOfService(handle, origAddr.GetPointCode(),
                                               origAddr.GetSSN());
            
            // Check if SCCP message was sent successfully
            if (result == ITS_SUCCESS)
            {
                cout << "SCCP User Out of Service message send success."
                     << endl;
            }
            else
            {
                cout << "WARNING: SCCP User Out of Service message send failed"
                     << endl;
                cout << "  Error: " << result << endl;
            }
            break;

        case TestCallGap:
        case TestCallInformationRequest:
        case TestCancelStatusReportRequest:
        case TestConnect:
        case TestInitialDP:
        case TestRequestCurrentStatusReport:
        case TestRequestEveryStatusChangeReport:
        case TestRequestFirstStatusMatchReport:
        case TestRequestReportBCSMEvent:
            // Send an INAP Message
            sendQuery(handle, recvdid, origAddr, destAddr, choice);
            break;

        case TestCancelComponent:
            // Send cancel component with end dialog set to prearranged end
            sendCancelCpt(handle);
            break;

        case TestEndPrearranged:
            // User wants to send an End dialog with termination set to
            // Prearranged End

            // Ask user to enter the dialog id of the transaction to be ended
            cout << "Enter dialog Id of transaction to be terminated: ";
            cin >> did;

            // Set the dialog Id of the end dialog
            end.SetDialogueID((ITS_USHORT)did);

            // Set termination type to Basic End
            end.SetPreArrangedEnd(true);

            // Printout end dialog information
            traceDialogue(&end);

            // Send the end dialog
            result = TCAP_Dialogue::Send(handle, &end);

            // Check if end dialog was sent successfully
            if (result == ITS_SUCCESS)
            {
                // End dialog sent successfully
                cout << "End dialog send success." << endl;
            }
            else
            {
                // Failed to send end dialog
                cout << "WARNING: End dialog send failed." << endl;
                cout << "  Error: " << (int)result << endl;
                cout << endl;
            }
            break;

        case TestWait:
            // Wait for an Event
            waitForEvent(handle, recvdid, origAddr);
            break;

        case TestQuit:
            // Stop asking user to select an operation from the main menu
            keepGoing = 0;
            break;

        default:
            cout << endl;
            cout << "WARNING: Invalid choice" << endl;
            cout << endl;
        }
    }

    // Do necessary clean up before exiting
    ITS_Terminate(handle);
    return 0;
}