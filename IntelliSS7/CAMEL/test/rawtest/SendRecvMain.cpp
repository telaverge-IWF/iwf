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

#include <its_app.h>
#include <its_transports.h>

#include <its_object.h>

/*
#include <its_ss7_stubs.h>
#include <its_object.h>
*/

#include <its_thread.h>
#include <its_worker.h>

#include <its_ss7_trans.h>
/*
#include <its_ss7_stubs.h>
*/
//
// ASN CPP headers
//
#include <AsnObject.h>
#include <AsnException.h>
#include <Octets.h>


extern "C" ITS_Class itsINTELLISS7_Class;

#include <tcap++.h>
#include <sccp++.h>
#include <cap_cpp.h>

#include "initialize.h"
#include "SendRecv.h"
#include "trace.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace cap;
using namespace cap_v3;
#endif

ITS_HANDLE handle;

//
// TCAP containers
//
TCAP_Component* cpt = NULL;
TCAP_Dialogue* dlg = NULL;

//
// Communication
//
ITS_Worker*     trin;
ITS_Worker*     trout;

ITS_Thread* recvMTP3Thread = NULL;
ITS_Thread* recvTCAPThread = NULL;


/* extern "C" ITS_Class itsINTELLISS7_Class; */

////////////////////////////////////////////////////////////////////////////////
//
//  Temporary work around for missing symbols in IntelliNet Vendor Library.
//
//  => Must be removed when problem will be corrected.
//

extern "C" {

int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }

}

//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)

//
// termination handler
//

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#else // !defined(WIN32)
static void exitHandler(int sig)
{
    ITS_GlobalStop();

    exit(EXIT_SUCCESS);
}
#endif // defined(WIN32)

THREAD_RET_TYPE
RecvMTP3Func(void*)
{
    int i = 0, ret = ITS_SUCCESS;
    bool keepGoing = true;
    ITS_Event ev;

    
    cout << "Wait for MTP3 event." << endl;
    
    while ( keepGoing ) 
    {
        if (trout->GetNextEvent(ev) != ITS_SUCCESS)
        {
            cout << "Failed to get MTP3 event." << endl;
            continue;
        }
        else
        {
            cout << "Event source: ";
            switch ( ev.GetSource() )
            {
            case ITS_MTP3_SRC: 
                printf("\nMTP3");

            case ITS_SCCP_SRC:
                printf("\nSCCP");
                break;
            case ITS_TCAP_SRC:
                printf("\nTCAP");
                break;
            }
    
            cout << ", " << ev.GetSource() << endl;
            cout << "Length:  " << ev.GetLength() << endl;

            for ( i = 0; i < ev.GetLength(); i++)
            {
                printf("%02x ", ev.GetData()[i]);
                if (!((i+1) % 25))
                {
                    printf("\n");
                }
            }

            if ((i+1) % 25)
            {
                printf("\n");
            }

            cout << "\n Sending to SCCP... " << endl;
            ev.SetSource( ITS_MTP3_SRC ); 

            ret = ITS_Transport::PutEvent(ITS_SCCP_SRC, ev);
            if (ret != ITS_SUCCESS)
            {
               
                printf("Fail to put MTP3 event.\n");
                fflush(stdout);
            }
            else
            {
                printf("Put ok...\n");
                fflush(stdout);
            }
        
     
        }
    }
    
    return (0);
}

THREAD_RET_TYPE
RecvTCAPFunc(void *arg)
{
	 int ret = ITS_SUCCESS;
    bool keepGoing = true;
    bool national = false;
    ITS_OCTET family = 0x00;
	ITS_LONG op;
    Octets* octets = NULL;
    ITS_Event ev;
    ITS_ByteArray buf;
    int noResponse =0;
    SCCP_CallingPartyAddr origAddr;


    while ( keepGoing ) 
    {
        // Get TCAP event
        
        cout << "Wait for TCAP event." << endl;
        noResponse =0;

        if (trin->GetNextEvent(ev) != ITS_SUCCESS)
        {
            cout << "TCAP GetNextEvent() failed." << endl;
            continue;
        }
        else
        {
			cout << "TCAP getnextevent succeeded" << endl;
            int i;
            for ( i = 0; i < ev.GetLength(); i++)
            {
                printf("%02x ", ev.GetData()[i]);
                if (!((i+1) % 25))
                {
                    printf("\n");
                }
            }

            if ((i+1) % 25)
            {
                printf("\n");
            }

            if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_CPT)
            {
                ret = TCAP_Component::Receive((ITS_HANDLE)trin->GetTransport(),
                                              ev, dlg, &cpt);

                printf("\n recvd. tcap component");

                if (ret == ITS_SUCCESS)
                {

                    // Determine what kind of component was received
                    switch (cpt->GetComponentType())
                    {
                    case TCPPT_TC_INVOKE:
                    
                        
                        printf("Received invoke component.\n");

						
                        ((TCAP_Invoke *)cpt)->GetOperation(op);
                        ((TCAP_Invoke *)cpt)->GetParameter(buf);

                        printf("Creating octets from parameter.\n");
                        octets = new Octets(buf);

                        
                        // Decode parameter of invoke component
                        printf("Decoding message.\n");
                        decodeCAPMsg(op, octets);

                        // Free allocated memory
                        if (octets)
                        {
                            delete octets;
                        }

                        break;

                    case TCPPT_TC_RESULT_L:
                    case TCPPT_TC_RESULT_NL:

                        printf("Received result component.\n");

						((TCAP_Result *)cpt)->GetOperation(op);

                        ((TCAP_Result *)cpt)->GetParameter(buf);

                        octets = new Octets(buf);
                        
						// Decode parameter of result component
                        decodeCAPMsg(op, octets);

                        // Free allocated memory
                        if (octets)
                        {
                            delete octets;
                        }

                        noResponse =1;
                        
                        break;

					
                    case TCPPT_TC_U_ERROR:
                        
                        printf("Received u-error component.\n");
                        
                        noResponse =1;
                        
                        break;

                    case TCPPT_TC_U_REJECT:
                        
                        printf("Received u-reject component.\n");
                        
                        noResponse =1;
                        
                        break;
                    
                    case TCPPT_TC_L_REJECT:
                        
                        printf("Received l-reject component.\n");
                        
                        noResponse =1;
                        
                        break;
                    
                    case TCPPT_TC_R_REJECT:
                        
                        printf("Received r-reject component.\n");
                        
                        noResponse =1;
                        
                        break;

                    case TCPPT_TC_L_CANCEL:
                        
                        printf("Received l-cancel component.\n");
                        
                        noResponse =1;
                        
                        break;
					
                    case TCPPT_TC_U_CANCEL:
                        
                        printf("Received u-cancel component.\n");
                        
                        noResponse =1;
                        
                        break;
					

                    default:
                       
                        cout << "Received unknown component. "
                             << dec << cpt->GetComponentType()
                             << endl;
                    }
                }
                else
                {
                    
                    printf("Fail to receive component.\n");
                }
            }
            else if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_DLG)
            {
                ret = TCAP_Dialogue::Receive((ITS_HANDLE)trin->GetTransport(),
                                             ev, &dlg);

                if (ret == ITS_SUCCESS)
                {
                   
                    printf("Received dialogue.\n");

                    switch (dlg->GetDialogueType())
                    {
                    case TCPPT_TC_UNI:
                        
                        printf("Received Unidirectional dialogue.\n");
                        break;

                    case TCPPT_TC_BEGIN:
                        
                        printf("Received Begin dialogue: wait for the invoke component to arrive\n");
                        
                        noResponse =1;
                        
                        break;

                    case TCPPT_TC_END:
                        
                        printf("Received End dialogue.\n");
                        
                        noResponse =1;
                        
                        break;

                    case TCPPT_TC_P_ABORT:
                        
                        
                        
                        noResponse =1;
                        
                        break;

                    case TCPPT_TC_U_ABORT:
                        
                        
                        
                        noResponse =1;
                        
                        break;

					case TCPPT_TC_CONTINUE:
                        
                        printf("Received Continue dialogue.\n");
                        break;


                    case TCPPT_TC_NOTICE:
                        
                        printf("Received Notice dialogue.\n");
                        break;

                    default:
                        
                        printf("Received unknown dialogue. 0x%02x",
                               dlg->GetDialogueType());
                        break;
                    }
                }
                else
                {
                    
                    printf("Fail to receive dialogue.\n");
                }

                printf("Got dialogue: DID is %d\n",
                       dlg->GetDialogueID());
            }
        }

        /*
        cout << "Check noResponse = " << noResponse << endl;
                
        if (!noResponse)
            {
                    // Send a response
                sendResponse((ITS_HANDLE)trin->GetTransport(), cpt, dlg);
            }
        */

    }

    return (0);
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
    int hardCodeAddress = 1;    // 1 - use hardcoded address, 0 - user provided
    int keepGoing = 1;
    int choice = 0;
    int instance;
    int did;
    ITS_USHORT recvdid = 0;
    SCCP_CallingPartyAddr origAddr;
    SCCP_CalledPartyAddr destAddr;
    TCAP_End end;
    int local_pc, local_ssn, remote_pc, remote_ssn;

/*     ITS_OCTET slsKey, priority; */
    ITS_OCTET appContext[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
    ITS_OCTET userInfo[5] = { 0x01, 0x01, 0x02, 0x02, 0x03 };
    ITS_USHORT begdid=1; /* hardcoded for the time being,
                            till allocate-tcap-dialog works */
    TCAP_Begin beg;

    int res = ITS_AddFeature(itsINTELLISS7_Class);
              

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
        }

    cout << "*******************************************" << endl;
    cout << "*****                                 *****" << endl;
    cout << "*****  IntelliNet Technologies, Inc.  *****" << endl;
    cout << "*****  IntelliSS7 CAMEL C++ API Test   *****" << endl;
    cout << "*****                                 *****" << endl;
    cout << "*******************************************" << endl;
    cout << endl;
    cout << endl;

    // Ask the user to select an instance number for this application
    cout << "Select Instance for this Program:" << endl;
    cout << "---------------------------------" << endl;
    cout << "[1] Send Instance " << endl;
    cout << "[2] Receive Instance " << endl;
    cout << endl;
    

    // Get user instance selection
    instance = getSelection(1, 2);
    recvdid = instance; // temporary getaround

	if (instance == 1)
    {
        ITS_Application::SetName( "Send" );
    }
    else
    {
        ITS_Application::SetName( "Recv" );
    }

	//ITS_GlobalStart(ITS_TCAP | ITS_SCCP);

	trin = new ITS_Worker(0, "User", ITS_DEFAULT_USER_SRC,
                              ITS_TRANSPORT_TQUEUE);

        if (trin == NULL)
        {
            
            printf("Fail to create Tqueue transport\n");
        }

    // Determine which instance number this program is to use
    if (instance == SendInstance)
    {
       trout = new ITS_Worker(0, "Sender", ITS_DEFAULT_USER_SRC + instance,
                                   ITS_SCCP | ITS_TCAP |
                                   ITS_TRANSPORT_CSOCKET);

		/*
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
		*/

			local_pc = 2;
            local_ssn = 20;
            remote_pc = 3;
            remote_ssn = 30;
		
    }
    else
    {
      
		trout = new ITS_Worker(0, "Receiver", ITS_DEFAULT_USER_SRC + instance,
                                   ITS_SCCP | ITS_TCAP |
                                   ITS_TRANSPORT_SSOCKET);


		/*
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
		*/
		local_pc = 3;
        local_ssn = 30;
        remote_pc = 2;
        remote_ssn = 20;

	
    }
/*
	ITS_HDR hdr;
    hdr.type = 0;
    hdr.context.dialogue_id = 1;
    ITS_ASSERT(ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, &hdr) ==
               ITS_SUCCESS);


	if (trin != NULL)
	{
		handle = (ITS_HANDLE)trin->GetTransport();
	}
*/
    //
    // Creating MTP3 border transport thread
    //
    recvMTP3Thread = new ITS_Thread(0, RecvMTP3Func);

    if (recvMTP3Thread->Enter((void *)recvMTP3Thread) != ITS_SUCCESS)
    {
        
        printf("Fail to start MTP3 receive thread\n");
    }

    //
    // Creating TCAP receive thread
    //
    recvTCAPThread = new ITS_Thread(0, RecvTCAPFunc);
    
    if (recvTCAPThread->Enter((void *)recvTCAPThread) != ITS_SUCCESS)
    {
        
        printf("Fail to start TCAP receive thread\n");
    }
    

    if (!hardCodeAddress)
    {
        // Ask user to provide an originating address
        cout << endl;
        cout << "Setting Originating Address:" << endl;
        cout << "----------------------------" << endl;
        getSCCPAddress(&origAddr);
        
        // Ask user to provide a destination address
        cout << endl;
        cout << "Setting Destination Address:" << endl;
        cout << "----------------------------" << endl;
        getSCCPAddress(&destAddr);
       
    }

    // Keep looping until user decides to exit
    while (keepGoing)
    {
        // Display send Menu
        displayMainMenu();
        choice = getSelection(TestSCCPUIS, TestQuit);
	
		if (trin != NULL)
		{
			handle = (ITS_HANDLE)trin->GetTransport();
		}

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

        case TestApplyCharging:
		case TestApplyChargingReport:
		case TestAssistRequestInstructions:
        case TestCallGap:
		case TestCallInformationReport:
        case TestCallInformationRequest:
        case TestCancel:
		case TestConnect:
		case TestConnectToResource:
		case TestContinueWithArgument:
		case TestEstablishTemporaryConnection:
		case TestEventReportBCSM:
		case TestFurnishChargingInformation:
        case TestInitialDP:
        case TestReleaseCall:
		case TestRequestReportBCSMEvent:
        case TestResetTimer:
        case TestSendChargingInformation:
        case TestPromptAndCollectUserInformation:
		case TestPlayAnnouncement:
		case TestReceivedInformation:

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
