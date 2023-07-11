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
 *  ID: $Id: sendGSMMAPMsg.cpp,v 9.1 2005/03/23 12:51:34 cvsadmin Exp $
 *
 * LOG: $Log: sendGSMMAPMsg.cpp,v $
 * LOG: Revision 9.1  2005/03/23 12:51:34  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:30  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:51  mmiers
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
 * LOG: Revision 3.1  2000/08/15 23:57:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/11/01 17:26:35  cbascon
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
 *      This function will send a MT_ForwardSM_Arg invoke component.
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
sendMTForwardSMArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result =0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    MT_ForwardSM_Arg *mfsArg = new MT_ForwardSM_Arg();

    cout << "Setting MT_ForwardSM_Arg Parameteres:" << endl;
    cout << "-------------------------------------" << endl;
    
    // Ask user to send a badly encoded message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        // Ask user to include Sm_RP_DA mandatory parameter
        cout << "Include Sm_RP_DA mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            mfsArg->SetSm_RP_DA(InitializeSm_RP_DA());
        }

        // Ask user to include Sm_RP_OA mandatory parameter
        cout << "Include Sm_RP_OA mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            mfsArg->SetSm_RP_OA(InitializeSm_RP_OA());
        }

        // Ask user to include Sm_RP_UI mandatory parameter
        cout << "Include Sm_RP_UI mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            mfsArg->SetSm_RP_UI(InitializeSm_RP_UI());
        }
    }
    else
    {
        // Setting mandatory parameters
        mfsArg->SetSm_RP_DA(InitializeSm_RP_DA());
        mfsArg->SetSm_RP_OA(InitializeSm_RP_OA());
        mfsArg->SetSm_RP_UI(InitializeSm_RP_UI());
    }

    // Setting optional parameters

    // Ask user to include MoreMessagesToSend optional parameter
    cout << "Include MoreMessagesToSend optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        mfsArg->SetMoreMessagesToSend(InitializeMoreMessagesToSend());
    }

    // Ask user to include ExtensionContainer optional parameter
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        mfsArg->SetExtensionContainer(InitializeExtensionContainer());
    }

    // Encode GSMMAP message
    encodeGSMMAPMsg(mfsArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_mt_forwardSM);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout invoke information
    traceComponent(&inv);

    // Send an MTForwardSMArg invoke component
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "MTForwardSMArg invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: MTForwardSMArg invoke send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete mfsArg;
    mfsArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a MT_ForwardSM_Res result component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a component received in the waitForEvent()
 *                function of this test program
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
sendMTForwardSMRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                   TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Result res;
    MT_ForwardSM_Res *mfsRes = new MT_ForwardSM_Res();

    // Set Parameters for GSMMAP message to send
    cout << "Setting MT_ForwardSM_Res Parameters:" << endl;
    cout << "------------------------------------" << endl;

    // Ask user to include Sm_RP_UI optional parameter
    cout << "Include Sm_RP_UI optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        mfsRes->SetSm_RP_UI(InitializeSm_RP_UI());
    }

    // Ask user to include ExtensionContainer optional parameter
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        mfsRes->SetExtensionContainer(InitializeExtensionContainer());
    }

    // Encode GSMMAP message
    encodeGSMMAPMsg(mfsRes, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_mt_forwardSM);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout result information
    traceComponent(&res);

    // Send an ReportSMDeliveryStatus result component
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "MTForwardSM result send success." << endl;
    }
    else
    {
        cout << "WARNING: MTForwardSM result send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete mfsRes;
    mfsRes = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ReportSMDeliveryStatus invoke component.
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
sendReportSMDeliveryStatusArg(ITS_HANDLE handle, its::TCAP_Dialogue *dlg)
{
    int result = 0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    ReportSM_DeliveryStatusArg* rsdsArg = new ReportSM_DeliveryStatusArg();

    cout << "Setting ReportSM_DeliveryStatusArg Parameteres:" << endl;
    cout << "-------------------------------------" << endl;
    
    // Ask user to send a badly encoded message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        // Ask user to include mandatory parameters

        // Ask user to include Msisdn
        cout << "Include Msisdn mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            rsdsArg->SetMsisdn(InitializeMsisdn());
        }

        // Ask user to include ServiceCentreAddress
        cout << "Include ServiceCentreAddress mandatory parameter? ";
        cout << "[y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            rsdsArg->SetServiceCentreAddress(InitializeServiceCentreAddress());
        }

        // Ask user to include Sm_DeliveryOutcome
        cout << "Include Sm_DeliveryOutcome mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            rsdsArg->SetSm_DeliveryOutcome(InitializeSM_DeliveryOutcome());
        }
    }
    else
    {
        // Set mandatory parameters
        rsdsArg->SetMsisdn(InitializeMsisdn());
        rsdsArg->SetServiceCentreAddress(InitializeServiceCentreAddress());
        rsdsArg->SetSm_DeliveryOutcome(InitializeSM_DeliveryOutcome());
    }

    // Setting optional parameters

    // Ask user to include AbsentSubscriberDiagnosticSM optional parameter
    cout << "Include AbsentSubscriberDiagnosticSM optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rsdsArg->SetAbsentSubscriberDiagnosticSM
            (InitializeAbsentSubscriberDiagnosticSM());
    }

    // Ask user to include AdditionalAbsentSubscriberDiagnosticSM optional
    // parameter
    cout << "Include AdditionalAbsentSubscriberDiagnosticSM optional "
         << endl;
    cout << "parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rsdsArg->SetAdditionalAbsentSubscriberDiagnosticSM
            (InitializeAbsentSubscriberDiagnosticSM());
    }

    // Ask user to include AdditionalSM_DeliveryOutcome optional
    // parameter
    cout << "Include AdditionalSM_DeliveryOutcome optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rsdsArg->SetAdditionalSM_DeliveryOutcome(InitializeSM_DeliveryOutcome());
    }

    // Ask user to include DeliveryOutcomeIndicator
    cout << "Include DeliveryOutcomeIndicator optional parameter? ";
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rsdsArg->SetDeliveryOutcomeIndicator
            (InitializeDeliveryOutcomeIndicator());
    }

    // Ask user to include ExtensionContainer
    cout << "Include ExtensionContainer optional parameter? [y]es/[n]: ";
    if (getYesOrNo() == 1)
    {
        rsdsArg->SetExtensionContainer(InitializeExtensionContainer());
    }

    // Encode GSMMAP message
    encodeGSMMAPMsg(rsdsArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_reportSM_DeliveryStatus);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout invoke information
    traceComponent(&inv);

    // Send an ReportSMDeliveryStatus invoke component
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ReportSMDeliveryStatus invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: ReportSMDeliveryStatus invoke send failed." << endl;
    }

    // Free allocated memory
    delete rsdsArg;
    rsdsArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ReportSMDeliveryStatus result component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a component received in the waitForEvent()
 *                function of this test program
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
sendReportSMDeliveryStatusRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                              TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Result res;
    ReportSM_DeliveryStatusRes *rsdsRes = new ReportSM_DeliveryStatusRes();

    // Set Parameters for GSMMAP message to send
    cout << "Setting ReportSM_DeliveryStatusRes parameters:" << endl;
    cout << "----------------------------------------------" << endl;

    // Ask user to include StoredMSISDN optional parameter
    cout << "Include StoredMSISDN optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        rsdsRes->SetStoredMSISDN(InitializeISDN_AddressString());
    }

    // Encode GSMMAP message
    encodeGSMMAPMsg(rsdsRes, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_reportSM_DeliveryStatus);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout result information
    traceComponent(&res);

    // Send an ReportSMDeliveryStatus result component
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ReportSMDeliveryStatus result send success." << endl;
    }
    else
    {
        cout << "WARNING: ReportSMDeliveryStatus result send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete rsdsRes;
    rsdsRes = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a SendRoutingInfo invoke component.
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
sendSendRoutingInfoArg(ITS_HANDLE handle, TCAP_Dialogue* dlg)
{
    int result =0;
    int invokeId, timeout;
    Octets* encOctets;
    TCAP_Invoke inv;
    SendRoutingInfoArg* sriArg = new SendRoutingInfoArg();

    // Set Parameters for GSMMAP message to send
    cout << "Setting SendRoutingInfoArg parameters:" << endl;
    cout << "--------------------------------------" << endl;

    // Ask user to send a badly encoded message
    cout << "Send a badly encoded message? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        // Ask user to include mandatory parameters

        // Ask user to include Msisdn
        cout << "Include Msisdn mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            sriArg->SetMsisdn(InitializeISDN_AddressString());
        }

        // Ask user to include InterrogationType
        cout << "Include InterrogationType mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            sriArg->SetInterrogationType(InitializeInterrogationType());
        }

        // Ask user to include Gmsc_Address
        cout << "Include Gmsc_Address mandatory parameter? [y]es/[n]o: ";
        if (getYesOrNo() == 1)
        {
            sriArg->SetGmsc_Address(InitializeISDN_AddressString());
        }
    }
    else
    {
        // Setting mandatory parameters
        sriArg->SetMsisdn(InitializeISDN_AddressString());
        sriArg->SetInterrogationType(InitializeInterrogationType());
        sriArg->SetGmsc_Address(InitializeISDN_AddressString());
    }

    // Setting optional parameters

    // Ask user to include Cug_CheckInfo
    cout << "Include Cug_CheckInfo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetCug_CheckInfo(InitializeCUG_CheckInfo());
    }
    
    // Ask user to include NumberOfForwarding
    cout << "Include NumberOfForwarding optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetNumberOfForwarding(InitializeNumberOfForwarding());
    }
   
    // Ask user to include Or_Interrogation
    cout << "Include Or_Interrogation optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetOr_Interrogation(InitializeOr_Interrogation());
    }

    // Ask user to include Or_Capability
    cout << "Include Or_Capability optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetOr_Capability(InitializeOrCapability());
    }

    // Ask user to include CallReferenceNumber
    cout << "Include CallReferenceNumber optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetCallReferenceNumber(InitializeCallReferenceNumber());
    }
    
    // Ask user to include ForwardingReason
    cout << "Include ForwardingReason optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetForwardingReason(InitializeForwardingReason());
    }
    
    // Ask user to include BasicServiceGroup
    cout << "Include BasicServiceGroup optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetBasicServiceGroup(InitializeBasicServiceGroup());
    }
    
    // Ask user to include NetworkSignalInfo
    cout << "Include NetworkSignalInfo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetNetworkSignalInfo(InitializeNetworkSignalInfo2());
    }
    
    // Ask user to include CamelInfo
    cout << "Include CamelInfo optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetCamelInfo(InitializeCamelInfo());
    }
    
    // Ask user to include SuppressionOfAnnouncement
    cout << "Include SuppressionOfAnnouncement optional parameter?" << endl;
    cout << "[y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetSuppressionOfAnnouncement
            (InitializeSuppressionOfAnnouncement());
    }

    // Ask user to include AlertingPattern
    cout << "Include AlertingPattern optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetAlertingPattern(InitializeAlertingPattern());
    }

    // Ask user to include Ccbs_Call
    cout << "Include Ccbs_Call optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetCcbs_Call(InitializeCcbs_Call());
    }

    // Ask user to include SupportedCCBS_Phase
    cout << "Include SupportedCCBS_Phase optional parameter? [y]es/[n]o: ";
    if (getYesOrNo() == 1)
    {
        sriArg->SetSupportedCCBS_Phase(InitializeSupportedCCBS_Phase());
    }

    // Encode GSMMAP message
    encodeGSMMAPMsg(sriArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_sendRoutingInfo);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout invoke information
    traceComponent(&inv);

    // Send an SendRoutingInfoArg invoke component
    cout << "Sending SendRoutingInfoArg." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "SendRoutingInfoArg invoke send success." << endl;
    }
    else
    {
        cout << "WARNING: SendRoutingInfoArg invoke send failed." << endl;
    }

    // Free allocated memory
    delete sriArg;
    sriArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a SendRoutingInfoRes result component
 *      sent in response to a SendRoutingInfoArg invoke. The parameters
 *      for the GSMMAP message is set then the message is encoded. The encoded
 *      value is used to set the parameter field of the result component. The
 *      result component is then sent.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog the invoke component is associated with
 *      recvCpt - component received using the waitForEvent() method of the
 *                LoopBack class
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the result component is sent successfully. Any other
 *      value indicates an error.
 *
 *  Notes:
 *      The memory allocated for the GSMMAP message and the encoded value of
 *      the message needs to be freed to prevent memory leaks.
 *
 *  See Also:
 ****************************************************************************/
int
sendSendRoutingInfoRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                       TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Result res;
    SendRoutingInfoRes *sriRes = new SendRoutingInfoRes();

    // Set Parameters for GSMMAP message to send
    sriRes->SetImsi(InitializeIMSI());
    sriRes->SetExtendedRoutingInfo(InitializeExtendedRoutingInfo());
    sriRes->SetCug_CheckInfo(InitializeCUG_CheckInfo());
    sriRes->SetCugSubscriptionFlag(InitializeCugSubscriptionFlag());
    sriRes->SetSubscriberInfo(InitializeSubscriberInfo());
    //sriRes->SetSs_List(InitializeSS_List());
    //sriRes->SetBasicService(InitializeExt_BasicServiceCode());
    sriRes->SetForwardingInterrogationRequired
        (InitializeForwardingInterrogationRequired());
    //sriRes->SetVmsc_Address(InitializeVmsc_Address());
    //sriRes->SetNaea_PreferredCI(InitializeNaea_PreferredCI());
    //sriRes->SetCcbs_Indicators(InitializeCCBS_Indicators());

    // Encode GSMMAP message
    encodeGSMMAPMsg(sriRes, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_sendRoutingInfo);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printout result information
    traceComponent(&res);

    // Send an SendRoutingInfoRes result component
    cout << "Sending SendRoutingInfoRes." << endl;
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "SendRoutingInfoRes send success." << endl;
    }
    else
    {
        cout << "WARNING: SendRoutingInfoRes send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete sriRes;
    sriRes = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a GSMMAP ProvideRoamingNumber invoke.
 *      First, ProvideRoamingNumberArg's member variables are set.
 *      Second, the GSMMAP message is encoded into a byte stream which is used
 *      to set the parameter field of the invoke component to be sent.
 *      Third, the invoke component's member variables are set. Then the
 *      invoke component is sent.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog the invoke component is associated with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the invoke component is sent successfully. Any other
 *      value indicates an error.
 *
 *  Notes:
 *      The memory allocated for the GSMMAP message and the encoded value of
 *      the message needs to be freed to prevent memory leaks.
 *
 *  See Also:
 ****************************************************************************/
int
sendProvideRoamingNumberArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    Octets *encOctets;
    ITS_USHORT invokeId, timeout;
    TCAP_Invoke inv;
    ProvideRoamingNumberArg *prnArg = new ProvideRoamingNumberArg();

    // Set Parameters for GSMMAP message to send
    prnArg->SetImsi(InitializeIMSI());
    prnArg->SetMsc_Number(InitializeMsc_Number());
    prnArg->SetMsisdn(InitializeMsisdn());
    prnArg->SetLmsi(InitializeLMSI());
    prnArg->SetGsm_BearerCapability(InitializeGsm_BearerCapability());
    prnArg->SetNetworkSignalInfo(InitializeNetworkSignalInfo());
    prnArg->SetSuppressionOfAnnouncement
        (InitializeSuppressionOfAnnouncement());
    prnArg->SetGmsc_Address(InitializeISDN_AddressString());
    prnArg->SetCallReferenceNumber(InitializeCallReferenceNumber());
    prnArg->SetOr_Interrogation(InitializePRNAOr_Interrogation());
    prnArg->SetAlertingPattern(InitializeAlertingPattern());
    prnArg->SetCcbs_Call(InitializePRNACcbs_Call());

    // Encode GSMMAP message
    encodeGSMMAPMsg(prnArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_provideRoamingNumber);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an ProvideRoamingNumberArg invoke component
    cout << "Sending ProvideRoamingNumberArg." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ProvideRoamingNumberArg send success." << endl;
    }
    else
    {
        cout << "WARNING: ProvideRoamingNumberArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete prnArg;
    prnArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ProvideRoamingNumber result component
 *      sent in response to a ProvideRoamingNumberArg invoke. The parameters
 *      for the GSMMAP message is set then the message is encoded. The encoded
 *      value is used to set the parameter field of the result component. The
 *      result component is then sent.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog the invoke component is associated with
 *      recvCpt - component received using the waitForEvent() method of the
 *                LoopBack class
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the result component is sent successfully. Any other
 *      value indicates an error.
 *
 *  Notes:
 *      The memory allocated for the GSMMAP message and the encoded value of
 *      the message needs to be freed to prevent memory leaks.
 *
 *  See Also:
 ****************************************************************************/
int
sendProvideRoamingNumberRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                            TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    ProvideRoamingNumberRes *prnRes = new ProvideRoamingNumberRes();
    TCAP_Result res;

    // Set Parameters for GSMMAP message to send
    prnRes->SetRoamingNumber(InitializeRoamingNumber());

    // Encode GSMMAP message
    encodeGSMMAPMsg(prnRes, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_provideRoamingNumber);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing result component information
    traceComponent(&res);

    // Send an ProvideRoamingNumberRes invoke component
    cout << "Sending ProvideRoamingNumberRes." << endl;
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ProvideRoamingNumberRes send success." << endl;
    }
    else
    {
        cout << "WARNING: ProvideRoamingNumberRes send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete prnRes;
    prnRes = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a GSMMAP UpdateLocation invoke.
 *      First, UpdateLocationArg's member variables are set.
 *      Second, the GSMMAP message is encoded into a byte stream which is used
 *      to set the parameter field of the invoke component to be sent.
 *      Third, the invoke component's member variables are set. Then the
 *      invoke component is sent.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog the invoke component is associated with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the invoke component is sent successfully. Any other
 *      value indicates an error.
 *
 *  Notes:
 *      The memory allocated for the GSMMAP message and the encoded value of
 *      the message needs to be freed to prevent memory leaks.
 *
 *  See Also:
 ****************************************************************************/
int
sendUpdateLocationArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Invoke inv;
    UpdateLocationArg *ulArg = new UpdateLocationArg();
    int invokeId, timeout;

    // Set Parameters for GSMMAP message to send
    ulArg->SetExtensionContainer(InitializeExtensionContainer());
    ulArg->SetImsi(InitializeIMSI());
    ulArg->SetLmsi(InitializeLMSI());
    ulArg->SetVlr_Capability(InitializeVLR_Capability());
    ulArg->SetMsc_Number(InitializeMsc_Number());
    ulArg->SetVlr_Number(InitializeVlr_Number());

    // Encode GSMMAP message
    encodeGSMMAPMsg(ulArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_updateLocation);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an UpdateLocationArg invoke component
    cout << "Sending UpdateLocationArg." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "UpdateLocationArg send success." << endl;
    }
    else
    {
        cout << "WARNING: UpdateLocationArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }
    
    // Free allocated memory
    delete ulArg;
    ulArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a UpdateLocationRes result component sent in
 *      response to a UpdateLocationRes invoke. The parameters for the GSMMAP
 *      message is set then the message is encoded. The encoded value is used
 *      to set the parameter field of the result component. The result
 *      component is then sent.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog the invoke component is associated with
 *      recvCpt - component received using the waitForEvent() method of the
 *                LoopBack class
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the result component is sent successfully. Any other
 *      value indicates an error.
 *
 *  Notes:
 *      The memory allocated for the GSMMAP message and the encoded value of
 *      the message needs to be freed to prevent memory leaks.
 *
 *  See Also:
 ****************************************************************************/
int
sendUpdateLocationRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                      TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Result res;
    UpdateLocationRes *ulRes = new UpdateLocationRes();

    // Set Parameters for GSMMAP message to send
    ulRes->SetExtensionContainer(InitializeExtensionContainer());
    ulRes->SetHlr_Number(InitializeHlr_Number());

    // Encode GSMMAP message
    encodeGSMMAPMsg(ulRes, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_updateLocation);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing result component information
    traceComponent(&res);

    // Send an UpdateLocationRes result component
    cout << "Sending UpdateLocationRes." << endl;
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "UpdateLocationRes send success." << endl;
    }
    else
    {
        cout << "WARNING: UpdateLocationRes send failed." << endl;
        cout << "  Error: " << result << endl;
    }   

    // Free allocated memory
    delete ulRes;
    ulRes = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a PrepareGroupCall invoke component.
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
sendPrepareGroupCallArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    PrepareGroupCallArg *pgcArg = new PrepareGroupCallArg();

    // Set Parameters for GSMMAP message to send
    pgcArg->SetTeleservice(InitializeExt_TeleserviceCode());
    pgcArg->SetAsciCallReference(InitializeAsciCallReference());
    pgcArg->SetCodec_Info(InitializeCODEC_Info());
    pgcArg->SetCipheringAlgorithm(InitializeCipheringAlgorithm());
    pgcArg->SetGroupKeyNumber(InitializeGroupKeyNumber());
    pgcArg->SetGroupKey(InitializeKc());
    pgcArg->SetPriority(InitializeEmlpp_Priority());
    pgcArg->SetUplinkFree(InitializeUplinkFree());

    // Encode GSMMAP message
    encodeGSMMAPMsg(pgcArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_prepareGroupCall);

    // Set Operation Class to 2 indicating that a response is expected on
    // operation failure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an PrepareGroupCallArg invoke component
    cout << "Sending PrepareGroupCallArg." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "PrepareGroupCallArg send success." << endl;
    }
    else
    {
        cout << "WARNING: PrepareGroupCallArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete pgcArg;
    pgcArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a ForwardGroupCallSignalling invoke component.
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
sendForwardGroupCallSignallingArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    ForwardGroupCallSignallingArg* fgcsArg =
        new ForwardGroupCallSignallingArg();

    // Set Parameters for GSMMAP message to send
    fgcsArg->SetImsi(InitializeIMSI());
    fgcsArg->SetUplinkRequestAck(InitializeFGCSAUplinkRequestAck());
    fgcsArg->SetUplinkReleaseIndication
        (InitializeFGCSAUplinkReleaseIndication());
    fgcsArg->SetUplinkRejectCommand(InitializeFGCSAUplinkRejectCommand());
    fgcsArg->SetUplinkSeizedCommand(InitializeFGCSAUplinkSeizedCommand());
    fgcsArg->SetUplinkReleaseCommand(InitializeFGCSAUplinkReleaseCommand());

    // Encode GSMMAP message
    encodeGSMMAPMsg(fgcsArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_forwardGroupCallSignalling);

    // Set Operation Class to 2 indicating that a response is expected on
    // operation failure
    inv.SetClass(2);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an ForwardGroupCallSignallingArg invoke component
    cout << "Sending ForwardGroupCallSignallingArg." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ForwardGroupCallSignallingArg send success." << endl;
    }
    else
    {
        cout << "WARNING: ForwardGroupCallSignallingArg send failed."
             << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete fgcsArg;
    fgcsArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an ActivateTraceMode invoke component.
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
sendActivateTraceModeArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int timeout, invokeId;
    Octets *encOctets;
    TCAP_Invoke inv;
    ActivateTraceModeArg *atmArg = new ActivateTraceModeArg();

    // Set Parameters for GSMMAP message to send
    atmArg->SetImsi(InitializeIMSI()); 
    atmArg->SetTraceReference(InitializeTraceReference());
    atmArg->SetTraceType(InitializeTraceType());
    atmArg->SetOmc_Id(InitializeOmc_Id());

    // Encode GSMMAP message
    encodeGSMMAPMsg(atmArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_activateTraceMode);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                      encOctets->GetLength());

    // Printing invoke component information
    traceComponent(&inv);

    // Send an ActivateTraceModeArg invoke component
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "ActivateTraceModeArg send success." << endl;
    }
    else
    {
        cout << "WARNING: ActivateTraceModeArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete atmArg;
    atmArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a DeactivateTraceMode invoke component.
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
sendDeactivateTraceModeArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    DeactivateTraceModeArg* dtmArg = new DeactivateTraceModeArg();

    // Set Parameters for GSMMAP message to send
    dtmArg->SetImsi(InitializeIMSI()); 
    dtmArg->SetTraceReference(InitializeTraceReference());

    // Encode GSMMAP message
    encodeGSMMAPMsg(dtmArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_deactivateTraceMode);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an DeactivateTraceMode invoke component
    cout << "Sending DeactivateTraceMode." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "DeactivateTraceModeArg send success." << endl;
    }
    else
    {
        cout << "WARNING: DeactivateTraceModeArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete dtmArg;
    dtmArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a RoutingInfoForSM invoke component.
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
sendRoutingInfoForSMArg(ITS_HANDLE handle, TCAP_Dialogue *dlg)
{
    int result = 0;
    int invokeId, timeout;
    Octets *encOctets;
    TCAP_Invoke inv;
    RoutingInfoForSM_Arg *rifsArg = new RoutingInfoForSM_Arg();

    // Set Parameters for GSMMAP message to send
    rifsArg->SetGprsSupportIndicator(InitializeGprsSupportIndicator());
    rifsArg->SetMsisdn(InitializeMsisdn());
    rifsArg->SetServiceCentreAddress(InitializeServiceCentreAddress());
    rifsArg->SetSm_RP_MTI(InitializeSm_RP_MTI());
    rifsArg->SetSm_RP_PRI(InitializeSm_RP_PRI());
    rifsArg->SetSm_RP_SMEA(InitializeSm_RP_SMEA());

    // Encode GSMMAP message
    encodeGSMMAPMsg(rifsArg, &encOctets);

    // Ask the user for a timeout value in seconds
    cout << "Enter timeout value: ";
    cin >> timeout;
    inv.SetTimeOut((ITS_USHORT)timeout);

    // Ask user to provide invoke id
    // This is necessary because in CCITT the same invoke ID cannot be used
    // a certain amount of time before it can be used again
    cout << "Enter InvokeID: ";
    cin >> invokeId;
    inv.SetInvokeID((ITS_USHORT)invokeId);

    // Set Invoke operation code
    inv.SetOperation(OP_sendRoutingInfoForSM);

    // Set Operation Class to 1 indicating that a response is expected on
    // success or failure of sending the invoke
    inv.SetClass(1);

    // Set invoke parameter using encoded message
    // Set the parameter of the invoke component using the encoded message
    inv.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing invoke information
    traceComponent(&inv);

    // Send an SendRoutingInfoForSM invoke component
    cout << "Sending SendRoutingInfoForSM." << endl;
    result = TCAP_Component::Send(handle, dlg, &inv);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "SendRoutingInfoForSMArg send success." << endl;
    }
    else
    {
        cout << "WARNING: SendRoutingInfoForSMArg send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rifsArg;
    rifsArg = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a MT_ForwardSM_Res result component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      dlg - pointer to the dialog associated with the component to be sent
 *      recvCpt - pointer to a component received in the waitForEvent()
 *                function of this test program
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
sendRoutingInfoForSMRes(ITS_HANDLE handle, TCAP_Dialogue *dlg,
                         TCAP_Component *recvCpt)
{
    int result = 0;
    Octets *encOctets;
    TCAP_Result res;
    RoutingInfoForSM_Res* rifs_res = new RoutingInfoForSM_Res();

    // Set Parameters for GSMMAP message to send
    rifs_res->SetImsi(InitializeIMSI());
    rifs_res->SetLocationInfoWithLMSI(InitializeLocationInfoWithLMSI());
    
    // Encode GSMMAP message
    encodeGSMMAPMsg(rifs_res, &encOctets);

    // Set invoke ID
    res.SetInvokeID(recvCpt->GetInvokeID());

    // Set result component operation code
    res.SetOperation(OP_sendRoutingInfoForSM);

    // Set result component parameter using encoded message
    // The GSMMAP message whose parameters are set above is stored in
    // TCAP Invoke component
    res.SetParameter(const_cast<ITS_OCTET *>(encOctets->GetArray().begin()),
                     encOctets->GetLength());

    // Printing result component information
    traceComponent(&res);

    // Send an RoutingInfoForSMRes invoke component
    cout << "Sending RoutingInfoForSMRes." << endl;
    result = TCAP_Component::Send(handle, dlg, &res);

    // Check if component was sent successfully
    if (result == ITS_SUCCESS)
    {
        cout << "RoutingInfoForSMRes send success." << endl;
    }
    else
    {
        cout << "WARNING: RoutingInfoForSMRes result send failed." << endl;
        cout << "  Error: " << result << endl;
    }

    // Free allocated memory
    delete rifs_res;
    rifs_res = NULL;
    delete encOctets;
    encOctets = NULL;

    return result;
}
