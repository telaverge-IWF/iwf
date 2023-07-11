////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: Corsair                                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//ID: $Id: win_trace.cpp,v 9.1 2005/03/23 12:52:45 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

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
#include "win_trace.h"


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
        {
            cout << endl;
        }
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
    cout << "Dialog Information: " << endl;
    cout << "------------------- " << endl;

    // Dialog ID
    cout << "Dialogue ID: " << dec << (int)dlg->GetDialogueID()
         << endl;

    // Component present?
    cout << "Component Present: ";
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

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        traceBeginDlg((TCAP_Begin *)dlg);
        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        traceContinueDlg((TCAP_Continue *)dlg);
        break;

    case TCPPT_TC_ABORT:
        traceAbortDlg((TCAP_Abort *)dlg);
        break;

    case TCPPT_TC_RESP:
        // TO DO
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
    cout << "Dialogue Type: Abort, "
         << dec << (int)dlg->GetDialogueType() << endl;

    // Abort reason
    cout << "Abort Reason: ";
    
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
    cout << "Dialogue Type: " << "Begin, "
         << (int)dlg->GetDialogueType() << endl;

    // Quality of service
    dlg->GetQualityOfService(flags, slsKey, priority);
    cout << endl;
    cout << "Quality Of Service: " << endl;
    cout << "------------------- " << endl;
    cout << "Flags: " << "0x" << hex << (int)flags << endl;
    cout << "slsKey: " << "0x" << hex << (int)slsKey << endl;
    cout << "Priority: " << "0x" << hex << (int)slsKey << endl;

    // Application context
    dlg->GetApplicationContext(appContext, appContextLen);
    cout << "Application Context: ";
    hexDump(appContext, appContextLen);

    // User info
    dlg->GetUserInfo(userInfo, userInfoLen);
    cout << "User Info: ";
    hexDump(userInfo, userInfoLen);

    // Originating address
    cout << "Originating Address " << endl;
    dlg->GetOrigAddr(origAddr);
    // traceSCCPAddress(origAddr);

    // Destination address
    cout << "Destination Address " << endl;
    dlg->GetDestAddr(destAddr);
    // traceSCCPAddress(destAddr);
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
    SCCP_CallingPartyAddr origAddr;

    // Dialog type
    cout << "Dialogue Type: " << "Continue, "
         << dec << (int)dlg->GetDialogueType() << endl;

    // Originating address
    cout << "Originating Address: " << endl;
    cout << "-------------------- " << endl;
    dlg->GetOrigAddr(origAddr);
    traceSCCPAddress(origAddr);

    // Originating point code
    cout << "Originating Point Code: ";
    if (dlg->HaveOPC())
    {
        dlg->GetOPC(opc);
        cout << opc;
    }
    else
    {
        cout << "None";
    }
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
    cout << "Dialogue Type: " << "End, "
         << dec << (int)dlg->GetDialogueType() << endl;

// NOTE: Excluded for now because aplication context and user info
//       is not used for this test program
#if 0
    // Application context
    dlg->GetApplicationContext(appContext, appContextLen);
    cout << "Application Context: ";
    hexDump(appContext, appContextLen);
    cout << endl;

    // User info
    dlg->GetUserInfo(userInfo, userInfoLen);
    cout << endl;
    cout << "User Info: ";
    hexDump(userInfo, userInfoLen);
    cout << endl;
#endif

    // Termination
    cout << "Termination: ";
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
    cout << "Component Information: " << endl;
    cout << "---------------------- " << endl;

    // invoke ID
    cout << "Invoke ID: " << dec << (int)cpt->GetInvokeID()
         << endl;

    // Last component
    cout << "Last Component: ";
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

    case TCPPT_TC_ERROR:
        traceErrorCpt(cpt);
        break;

    case TCPPT_TC_CANCEL:
        traceCancelCpt(cpt);
        break;

    case TCPPT_TC_REJECT:
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
    cout << "Component Type: Cancel, "
         << dec << (int)cpt->GetComponentType() << endl;

    // Dialog ID
    cout << "Dialog ID: "
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
    int paramLen = 300;
    bool national = false;
    ITS_OCTET family = 0x00, code = 0x00;

    // Component type
    cout << "Component Type: Invoke, " << dec
         << (int)cpt->GetComponentType() << endl;

    // Timeout
    printf("Timeout: %d\n", (int)(((TCAP_Invoke *)cpt)->GetTimeOut()) );

    // Operation
    ((TCAP_Invoke *)cpt)->GetOperation(national, family, code);

    printf("Operation:\n");
    printf("national: ");
    if (national)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }

    printf("family: 0x%02x\n", family);
    printf("code: 0x%02x\n", code);

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
    ITS_OCTET family = 0x00, code = 0x00;

    // Component type
    printf("Component Type: Reject, 0x%02x\n" , cpt->GetComponentType());

    // Problem: family and code
    ((TCAP_Reject *)cpt)->GetProblem(family, code);

    cout << "After GetProblem()." << endl;
    cout << "Problem Type: " << (int)family << endl;
    cout << "Problem Code: " << (int)code << endl;
    cout << endl;

    // Parameter
    //((TCAP_Reject *)cpt)->GetParameter(param, paramLen);
    //cout << "Parameter: " << endl;
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
    int paramLen = 0;

    // Component type
    cout << "Component Type: ";
    if (cpt->GetComponentType() == TCPPT_TC_RESULT_L)
    {
        cout << "ResultLast";
    }
    else if (cpt->GetComponentType() == TCPPT_TC_RESULT_NL)
    {
        cout << "ResultNotLast";
    }
    printf(", 0x%02x\n", cpt->GetComponentType());

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
    bool national = false;
    ITS_OCTET code = 0x00;
    int paramLen = 100;
    ITS_OCTET param[100];

    // Component type
    printf("Component Type: Error, 0x%02x\n", cpt->GetComponentType());

    // Error
    ((TCAP_Error *) cpt)->GetError(national, code);

    printf("Error: ");
    if (national)
    {
        printf("national");
    }
    else
    {
        printf("international");
    }
    printf(", code 0x%02x\n", code);

    // Parameter
    ((TCAP_Error *) cpt)->GetParameter( param, paramLen );

    cout << "Parameter: " << endl;
    hexDump( param, paramLen );

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

    cout << "SCCP Address Information: " << endl;
    cout << "------------------------- " << endl;

    // Does the address adhere to International/National Standard?
    cout << "Routing: ";
    if(addr.IsInternationalRouting())
    {
        cout << "International" << endl;
    }
    else
    {
        cout << "National" << endl;
    }

    // Does the address have a point code?
    cout << "Point Code: ";
    if(addr.HasPointCode())
    {
        cout << addr.GetPointCode() << endl;
    }
    else
    {
        cout << "None" << endl;
    }

    // Does the address have a SubSystem Number?
    cout << "SubSystem Number: ";
    if(addr.HasSSN())
    {
        cout << dec << (int)addr.GetSSN() << endl;
    }
    else
    {
        cout << "None" << endl;
    }

    // Is routed by Point Code and SubSystem Number?
    cout << "Routing: ";
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
        cout << "GTT Type: " << (int)type << endl;
        cout << "GTT Length: " << (int)gttLen << endl;
        cout << "GTT Info: ";
        hexDump(gttInfo, gttLen);
    }
    cout << endl;
}
