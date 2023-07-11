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


/*
 ****************************************************************************
 * NOTE: The functions below are used to printout TCAP dialog and component
 *       information. There is also a function for printing out an SCCP
 *       address.
 *
 ****************************************************************************/

#include <iostream>
#include <iomanip>

#include <tcap++.h>
#include <sccp++.h>
#include <itu/inap.h>
#include "trace.h"

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will do a hex dump for an ITS_OCTET array.
 *
 *  Input Parameters:
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
hexDump(ITS_OCTET *array, int len)
{
    for (int b = 0; b < len; b++)
    {
        cout << "0x" << setw(2) << hex << (int)array[b] << ' ';
        if (b % 10 == 0)
            cout << endl;
    }
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout dialog information.
 *
 *  Input Parameters:
 *      dlg - pointer to a dialog
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
traceDialogue(TCAP_Dialogue *dlg)
{
    // Display dialogue information
    cout << endl;
    cout << setw(25) << "Dialog Information: " << endl;
    cout << setw(25) << "------------------- " << endl;

    // Dialog ID
    cout << setw(25) << "Dialogue ID: " << dec << (int)dlg->GetDialogueID()
         << endl;

    // Component present?
    cout << setw(25) << "Component Present: ";
    if (dlg->IsComponentPresent() == true)
    {
        cout << "True, " << endl;
    }
    else
    {
        cout << "False, " << endl;
    }

    // Determine the dialog type and print out dialog type specific information
    switch (dlg->GetDialogueType())
    {
    case TCPPT_TC_UNI:
        // TO DO
        break;

    case TCPPT_TC_BEGIN:
        traceBeginDlg((TCAP_Begin *)dlg);
        break;

    case TCPPT_TC_CONTINUE:
        traceContinueDlg((TCAP_Continue *)dlg);
        break;

    case TCPPT_TC_END:
        traceEndDlg((TCAP_End *)dlg);
        break;

    case TCPPT_TC_U_ABORT:
        traceAbortDlg((TCAP_Abort *)dlg);
        break;

    case TCPPT_TC_P_ABORT:
        traceAbortDlg((TCAP_Abort *)dlg);
        break;

    case TCPPT_TC_NOTICE:
        // TO DO
        break;

    default:
        cout << "Unknown Dialog";
        break;
    }  
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Abort dialog information.
 *
 *  Input Parameters:
 *      dlg - pointer to a begin dialog
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
traceAbortDlg(TCAP_Abort *dlg)
{
    // Dialog type
    cout << setw(25) << "Dialogue Type: ";
    
    // Determine type of abort dialog
    if (dlg->GetDialogueType() == TCPPT_TC_U_ABORT)
    {
        cout << "U-Abort, ";
    }
    else
    {
        cout << "P-Abort, ";
    }
    cout << dec << (int)dlg->GetDialogueType() << endl;

    // Abort reason
    cout << setw(25) << "Abort Reason: ";
    
    if (dlg->GetAbortReason() == TCAP_UABT_AC_NOT_SUP_CCITT)
    {
        cout << "Application Context Not Supported";
    }
    else
    {
        cout << "User Defined";   
    }
    cout << endl << endl;
}   

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Begin dialog information.
 *
 *  Input Parameters:
 *      dlg - pointer to a begin dialog
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
traceBeginDlg(its::TCAP_Begin *dlg)
{
    ITS_OCTET flags, slsKey, priority;
    ITS_OCTET appContext[50];
    int appContextLen = 50;
    ITS_OCTET userInfo[50];
    int userInfoLen = 50;
    SCCP_CallingPartyAddr origAddr;
    SCCP_CalledPartyAddr destAddr;

    // Dialog type
    cout << setw(25) << "Dialogue Type: " << "Begin, "
         << (int)dlg->GetDialogueType() << endl;

    // Quality of service
    dlg->GetQualityOfService(flags, slsKey, priority);
    cout << endl;
    cout << setw(25) << "Quality Of Service: " << endl;
    cout << setw(25) << "------------------- " << endl;
    cout << setw(25) << "Flags: " << "0x" << hex << (int)flags << endl;
    cout << setw(25) << "slsKey: " << "0x" << hex << (int)slsKey << endl;
    cout << setw(25) << "Priority: " << "0x" << hex << (int)slsKey << endl;

    // Application context
    dlg->GetApplicationContext(appContext, appContextLen);
    cout << setw(25) << "Application Context: ";
    hexDump(appContext, appContextLen);

    // User info
    dlg->GetUserInfo(userInfo, userInfoLen);
    cout << setw(25) << "User Info: ";
    hexDump(userInfo, userInfoLen);

    // Originating address
    cout << setw(25) << "Originating Address " << endl;
    dlg->GetOrigAddr(origAddr);
    traceSCCPAddress(origAddr);

    // Destination address
    cout << setw(25) << "Destination Address " << endl;
    dlg->GetDestAddr(destAddr);
    traceSCCPAddress(destAddr);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Continue dialog information.
 *
 *  Input Parameters:
 *      dlg - pointer to a continue dialog
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
traceContinueDlg(its::TCAP_Continue *dlg)
{
    ITS_UINT opc;
    ITS_OCTET appContext[50];
    int appContextLen = 50;
    ITS_OCTET userInfo[50];
    int userInfoLen = 50;
    SCCP_CallingPartyAddr origAddr;

    // Dialog type
    cout << setw(25) << "Dialogue Type: " << "Continue, "
         << dec << (int)dlg->GetDialogueType() << endl;

    // Originating address
    cout << setw(25) << "Originating Address: " << endl;
    cout << setw(25) << "-------------------- " << endl;
    dlg->GetOrigAddr(origAddr);
    traceSCCPAddress(origAddr);

    // Originating point code
    cout << setw(25) << "Originating Point Code: ";
    if (dlg->HaveOPC())
    {
        dlg->GetOPC(opc);
        cout << opc;
    }
    else
    {
        cout << "None";
    }

    // Application context
    dlg->GetApplicationContext(appContext, appContextLen);
    cout << setw(25) << "Application Context: ";
    hexDump(appContext, appContextLen);

    // User info
    dlg->GetUserInfo(userInfo, userInfoLen);
    cout << setw(25) << "User Info: ";
    hexDump(userInfo, userInfoLen);

    cout << endl;
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout End dialog information.
 *
 *  Input Parameters:
 *      dlg - pointer to an end dialog
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
traceEndDlg(its::TCAP_End *dlg)
{
    //ITS_OCTET appContext[50];
    //int appContextLen = 50;
    //ITS_OCTET userInfo[50];
    //int userInfoLen = 50;

    // Dialog type
    cout << setw(25) << "Dialogue Type: " << "End, "
         << dec << (int)dlg->GetDialogueType() << endl;

// NOTE: Excluded for now because aaplication context and user info
//       is not used for this test program
#if 0
    // Application context
    dlg->GetApplicationContext(appContext, appContextLen);
    cout << setw(25) << "Application Context: ";
    hexDump(appContext, appContextLen);
    cout << endl;

    // User info
    dlg->GetUserInfo(userInfo, userInfoLen);
    cout << endl;
    cout << setw(25) << "User Info: ";
    hexDump(userInfo, userInfoLen);
    cout << endl;
#endif

    // Termination
    cout << setw(25) << "Termination: ";
    if (dlg->IsPreArrangedEnd())
    {
        cout << "PreArranged End";
    }
    else
    {
        cout << "Basic End";
    }
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout component information.
 *
 *  Input Parameters:
 *      cpt - pointer to a component
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
traceComponent(TCAP_Component *cpt)
{
    cout << endl;
    cout << setw(25) << "Component Information: " << endl;
    cout << setw(25) << "---------------------- " << endl;

    // invoke ID
    cout << setw(25) << "Invoke ID: " << dec << (int)cpt->GetInvokeID()
         << endl;

    // Last component
    cout << setw(25) << "Last Component: ";
    if (cpt->GetLast())
        cout << "True";
    else
        cout << "False";
    cout << endl;

    // Determine component type and print component type specific information
    switch (cpt->GetComponentType())
    {
    case TCPPT_TC_INVOKE:
        traceInvokeCpt(cpt);
        break;

    case TCPPT_TC_RESULT_L:
        traceResultCpt(cpt);
        break;

    case TCPPT_TC_RESULT_NL:
        traceResultCpt(cpt);
        break;

    case TCPPT_TC_U_ERROR:
        traceErrorCpt(cpt);
        break;

    case TCPPT_TC_L_CANCEL:
        traceCancelCpt(cpt);
        break;

    case TCPPT_TC_U_CANCEL:
        traceCancelCpt(cpt);
        break;

    case TCPPT_TC_L_REJECT:
        traceRejectCpt(cpt);
        break;

    case TCPPT_TC_R_REJECT:
        traceRejectCpt(cpt);
        break;

    case TCPPT_TC_U_REJECT:
        traceRejectCpt(cpt);
        break;

    default:
        cout << "Unknown Component" << endl;
        cout << endl;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout a Cancel component.
 *
 *  Input Parameters:
 *      cpt - pointer to a Cancel component
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
traceCancelCpt(TCAP_Component *cpt)
{
    // Cancel Component type
    cout << setw(25) << "Component Type: ";
    if (cpt->GetComponentType() == TCPPT_TC_L_CANCEL)
    {
        cout << "Local Cancel";
    }
    else
    {
        cout << "User Cancel";
    }
    cout << ", " << dec << (int)cpt->GetComponentType() << endl;

    // Dialog ID
    cout << setw(25) << "Dialog ID: "
         << (int)((TCAP_Cancel*)cpt)->GetDialogueID() << endl;
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout invoke component information.
 *
 *  Input Parameters:
 *      cpt - pointer to an Invoke component
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
traceInvokeCpt(TCAP_Component *cpt)
{
    int paramLen = 100;
    ITS_OCTET param[100];
    ITS_LONG code;

    // Component type
    cout << setw(25) << "Component Type: Invoke, " << dec
         << (int)cpt->GetComponentType() << endl;

    // Class
    cout << setw(25) << "Class: " << (int)(((TCAP_Invoke *)cpt)->GetClass())
         << endl;

#if 0
    // Link ID
    cout << setw(25) << "Link ID: "
         << (int)(((TCAP_Invoke *)cpt)->GetLinkedID()) << endl;
#endif

    // Timeout
    cout << setw(25) << "Timeout: "
         << (int)(((TCAP_Invoke *)cpt)->GetTimeOut()) << endl;

    // Operation
    ((TCAP_Invoke *)cpt)->GetOperation(code);
    cout << setw(25) << "Operation: " << (int)code << ", ";

    // Determine INAP operation
    switch (code)
    {
    case INAP_OP_callGap:
        cout << "CallGap";
        break;

    case INAP_OP_callInformationReport:
        cout << "CallInformationReport";
        break;

    case INAP_OP_callInformationRequest:
        cout << "CallInformationRequest";
        break;

    case INAP_OP_cancelStatusReportRequest:
        cout << "CancelStatusReportRequest";
        break;

    case INAP_OP_connect:
        cout << "Connect";
        break;

    case INAP_OP_eventReportBCSM:
        cout << "EventReportBCSM";
        break;

    case INAP_OP_initialDP:
        cout << "InitialDP";
        break;

    case INAP_OP_requestCurrentStatusReport:
        cout << "RequestCurrentStatusReport";
        break;

    case INAP_OP_requestEveryStatusChangeReport:
        cout << "RequestEveryStatusChangeReport";
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        cout << "RequestFirstStatusMatchReport";
        break;

    case INAP_OP_requestReportBCSMEvent:
        cout << "RequestReportBCSMEvent";
        break;

    case INAP_OP_statusReport:
        cout << "StatusReport";
        break;

    default:
        cout << "Unrecognized operation";
    }
    cout << endl;

    // Parameter
    ((TCAP_Invoke *)cpt)->GetParameter(param, paramLen);
    cout << setw(25) << "Parameter: " << endl;
    hexDump(param, paramLen);
    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Reject component information.
 *
 *  Input Parameters:
 *      cpt - pointer to a Reject component
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
traceRejectCpt(TCAP_Component *cpt)
{
    //int paramLen = 100;
    //ITS_OCTET param[100];
    ITS_OCTET family, code;

    // Component type
    cout << setw(25) << "Component Type: ";
    switch (cpt->GetComponentType())
    {
    case TCPPT_TC_L_REJECT:
        cout << "Local Reject";
        break;

    case TCPPT_TC_R_REJECT:
        cout << "Remote Reject";
        break;
    
    case TCPPT_TC_U_REJECT:
        cout << "User Reject";
        break;
    }
    cout << ", " << dec << (int)cpt->GetComponentType() << endl;

    // Problem: family and code
    cout << "Before GetProblem()." << endl;
    cout << setw(25) << "Problem Type: " << (int)family << endl;
    cout << setw(25) << "Problem Code: " << (int)code << endl;
    cout << endl;

    ((TCAP_Reject *)cpt)->GetProblem(family, code);
    cout << "After GetProblem()." << endl;
    cout << setw(25) << "Problem Type: " << (int)family << endl;
    cout << setw(25) << "Problem Code: " << (int)code << endl;
    cout << endl;

    // Parameter
    //((TCAP_Reject *)cpt)->GetParameter(param, paramLen);
    //cout << setw(25) << "Parameter: " << endl;
    //hexDump(param, paramLen);

    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Result component information.
 *
 *  Input Parameters:
 *      cpt - pointer to a result component
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
traceResultCpt(TCAP_Component *cpt)
{
    ITS_LONG code;
    int paramLen = 100;
    ITS_OCTET param[100];

    // Component type
    cout << setw(25) << "Component Type: ";
    if (cpt->GetComponentType() == TCPPT_TC_RESULT_L)
    {
        cout << "Result Last";
    }
    else
    {
        cout << "Result Not Last";
    }
    cout << ", " << dec << (int)cpt->GetComponentType() << endl;

    // Operation
    ((TCAP_Result *) cpt)->GetOperation(code);
    cout << setw(25) << "Operation: " << (int)code << endl;


// TO DO:
#if 0 
    // Determine INAP operation
    switch (code)
    {
    default:
        cout << "Unrecognized operation";
    }
#endif


    // Parameter
    ((TCAP_Result *)cpt)->GetParameter(param, paramLen);
    cout << setw(25) << "Parameter: " << endl;
    hexDump(param, paramLen);

    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will printout Error component information.
 *
 *  Input Parameters:
 *      cpt - pointer to an error component
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
traceErrorCpt(TCAP_Component *cpt)
{
    ITS_OCTET code;
    int paramLen = 100;
    ITS_OCTET param[100];

    // Component type
    cout << setw(25) << "Component Type: " << "User Error, "
         << dec << (int)cpt->GetComponentType() << endl;

    // Error
    ((TCAP_Error *) cpt)->GetError(code);
    cout << setw(25) << "Error: " << (int)code << endl;

    // Parameter
    ((TCAP_Error *) cpt)->GetParameter(param, paramLen);
    cout << setw(25) << "Parameter: " << endl;
    hexDump(param, paramLen);

    cout << endl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out SCCP Address information.
 *
 *  Input Parameters:
 *      addr - a SCCP address object
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
traceSCCPAddress(SCCP_Address &addr)
{
    ITS_USHORT gttLen;
    ITS_OCTET type, gttInfo[50];

    cout << setw(25) << "SCCP Address Information: " << endl;
    cout << setw(25) << "------------------------- " << endl;

    // Does the address adhere to International/National Standard?
    cout << setw(25) << "Routing: ";
    if(addr.IsInternationalRouting())
    {
        cout << "International" << endl;
    }
    else
    {
        cout << "National" << endl;
    }

    // Does the address have a point code?
    cout << setw(25) << "Point Code: ";
    if(addr.HasPointCode())
    {
        cout << addr.GetPointCode() << endl;
    }
    else
    {
        cout << "None" << endl;
    }

    // Does the address have a SubSystem Number?
    cout << setw(25) << "SubSystem Number: ";
    if(addr.HasSSN())
    {
        cout << dec << (int)addr.GetSSN() << endl;
    }
    else
    {
        cout << "None" << endl;
    }

    // Is routed by Point Code and SubSystem Number?
    cout << setw(25) << "Routing: ";
    if(addr.IsRoutedByPCSSN())
    {
        cout << "By PC and SSN" << endl;
    }
    else
    {
        cout << "By GTT" << endl;
    }

    // GTT information
    if (addr.HasGlobalTitle())
    {
        // Get gloabal title from address
        addr.GetGlobalTitle(type, gttInfo, gttLen);

        // Print global title information
        cout << setw(25) << "GTT Type: " << (int)type << endl;
        cout << setw(25) << "GTT Length: " << (int)gttLen << endl;
        cout << setw(25) << "GTT Info: ";
        hexDump(gttInfo, gttLen);
    }
    cout << endl;
}

