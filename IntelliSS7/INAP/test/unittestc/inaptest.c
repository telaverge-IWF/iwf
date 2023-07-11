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
 *  NOTE:
 *      The function sendCallGapArg(...) is commented in detail. The other
 *      functions used to send other INAP Messages are very similar to
 *      sendCallGapArg(..). So, less comments were placed for the other INAP
 *      procedures in this test program.
 ****************************************************************************/

#include <stdlib.h>
#include <malloc.h>

#include <its.h>
#include <its_app.h>

#include <itu/tcap.h>
#include <itu/sccp.h>

#include <itu/INAP-types.h>
#include <itu/inap.h>

#include "inaptest.h"



/*
 * The values below are used to set the fields of the INAP Message
 * structures.
 */

int connectTime = 2000;

int duration = 1970;

int elementaryMessageID = 1950;

int facilityGroupMemberID = 1980;

int gapInterval = 1960;

int integerval = 33;

int interval = 44;

int monitorDuration = 1999;

int numberOfDigits = 11;

int numberOfRepetitions = 100;

int serviceKey = 44;

int trunkGroupID = 1900;

const char alertingPattern[4] = { 0x31, 0x32, 0x33, 0x00 };

const char bcsmEventCorrelationID[5] = { 0x30, 0x31, 0x32, 0x33 , 0x00 };

const char bearerCap[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };

const char callingAddressValue[7] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                      0x00 };

const char callingPartyBusinessGroupID[2] = { 0x31, 0x00 };

const char calledPartyNumber[6] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x00 };

const char callingPartyNumber[11] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                      0x37, 0x38, 0x39, 0x30, 0x00 };

const char callingPartysCategory[2] = { 0x32, 0x00 };

const char callingPartySubaddress[2] = { 0x33, 0x00 };

const char callStopTimeValue[7] = { 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                                    0x00 };

const char carrier[2] = { 0x31, 0x00 };

const char correlationID[11] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
                                    0x36, 0x37, 0x38, 0x39, 0x00 };

const char dialledDigits[11] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
                                 0x36, 0x37, 0x38, 0x39, 0x00 };

const char element_INAP_86[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };

const char element_INAP_88[7] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                  0x00 };

const char huntGroup[2] = { 0x31, 0x00 };

const char iPAvailable[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };

const char iPSSPCapabilities[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };

const char isdnAccessRelatedInfo[2] = { 0x31, 0x00 };

const char locationNumber[11] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                  0x37, 0x38, 0x39, 0x30, 0x00 };

const char originalCalledPartyID[11] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                         0x37, 0x38, 0x39, 0x30, 0x00 };

const char releaseCause[5] = { 0x30, 0x31, 0x32, 0x33, 0x00 };

const char scfID[11] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                         0x37, 0x38, 0x39, 0x30, 0x00 };

const char sendingSideID[2] = { 0x33, 0x00 };

const char serviceInteractionIndicators[6] = { 0x31, 0x32, 0x33, 0x34, 0x35,
                                               0x00 };

const char serviceProfileIdentifier[2] = { 0x31, 0x00 };

const char travellingClassMark[11] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
                                       0x37, 0x38, 0x39, 0x30, 0x00 };

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the Main Menu for the Sending Program.
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
 *      SCCP User In Service is not implemented in the alpha and beta release.
 *
 *  See Also:
 ****************************************************************************/
void
SendProgramMainMenu()
{
    printf("\n\n");
    printf("\n ***************************************************");
    printf("\n *            INAP C SEND PROGRAM MENU             *");
    printf("\n ***************************************************");
    printf("\n\n");
    printf("\n NOTE:");
    printf("\n A Begin dialog must be sent before sending any");
    printf("\n Continue dialog.");
    printf("\n");
    printf("\n Select Send Program Operation:");
    printf("\n -------------------------------------------------");
    printf("\n [%2d] SCCP User In Service", TEST_SCCP_UIS);
    printf("\n [%2d] SCCP User Out of Service", TEST_SCCP_UOS);
    printf("\n");
    printf("\n [%2d] Begin Dialog", TEST_TCAP_BEGIN);
    printf("\n [%2d] Continue Dialog", TEST_TCAP_CONTINUE);
    printf("\n [%2d] End Dialog", TEST_TCAP_END);
    printf("\n [%2d] Unidirectional Dialog", TEST_TCAP_UNI);
    printf("\n [%2d] User Abort Dialog", TEST_TCAP_U_ABORT);
    printf("\n");
    printf("\n [%2d] User Cancel Component", TEST_TCAP_U_CANCEL);
    printf("\n");
    printf("\n [%2d] Get Next IntelliSS7 Event", TEST_WAIT_FOR_EVENT);
    printf("\n");
    printf("\n [%2d] To Quit", TEST_EXIT);
    printf("\n -------------------------------------------------");
    printf("\n -> ");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display a menu where the user can select the INAP
 *      message to send.
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
SendINAPMessageMenu()
{
    printf("\n Send Begin Dialog with Invoke Component");
    printf("\n -------------------------------------------------");
    printf("\n [%2d] CallGapArg", INAP_OP_callGap);
    printf("\n [%2d] CallInformationRequestArg",
           INAP_OP_callInformationRequest);
    printf("\n [%2d] CancelStatusReportRequestArg",
           INAP_OP_cancelStatusReportRequest);
    printf("\n [%2d] ConnectArg",
           INAP_OP_connect);
    printf("\n [%2d] InitialDPArg",
           INAP_OP_initialDP);
    printf("\n [%2d] RequestCurrentStatusReportArg",
           INAP_OP_requestCurrentStatusReport);
    printf("\n [%2d] RequestEveryStatusChangeReportArg",
           INAP_OP_requestEveryStatusChangeReport);
    printf("\n [%2d] RequestFirstStatusMatchReportArg",
           INAP_OP_requestFirstStatusMatchReport);
    printf("\n [%2d] RequestReportBCSMEventArg",
           INAP_OP_requestReportBCSMEvent);
    printf("\n -------------------------------------------------");
    printf("\n -> ");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the Main menu of the Receive program.
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
 *      SCCP User In Service is not implemented in the alpha and beta release.
 *
 *  See Also:
 ****************************************************************************/
void
ReceiveProgramMainMenu()
{
    printf("\n\n");
    printf("\n ***************************************************");
    printf("\n *           INAP C RECEIVE PROGRAM MENU           *");
    printf("\n ***************************************************");
    printf("\n\n");
    printf("\n Select Receive Program Operation:");
    printf("\n -------------------------------------------------");
    printf("\n [%2d] Send SCCP User In Service", TEST_SCCP_UIS);
    printf("\n [%2d] SCCP User Out Of Service", TEST_SCCP_UOS);
    printf("\n");
    printf("\n [%2d] INAP Response", TEST_INAP_RESPONSE);
    printf("\n");
    printf("\n [%2d] User Error Component", TEST_TCAP_U_ERROR);
    printf("\n [%2d] User Reject Component", TEST_TCAP_U_REJECT);
    printf("\n");
    printf("\n [%2d] User Abort Dialog", TEST_TCAP_U_ABORT);
    printf("\n [%2d] End Dialog(no component)", TEST_TCAP_END);
    printf("\n");
    printf("\n [%2d] Get Next IntelliSS7 Event", TEST_WAIT_FOR_EVENT);
    printf("\n");
    printf("\n [%2d] Exit program", TEST_EXIT);
    printf("\n -------------------------------------------------");
    printf("\n -> ");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the Response menu.
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
 *      The menu provides a list of responses that can be sent for a received
 *      INAP invoke. The user can send a User Error component, a User Reject
 *      component, an Abort dialog, an End dialog and an INAP response. 
 *      Sending a Continue dialog is not implemented for the alpha release.
 *      Sending a Continue dialog is implemented in beta release.
 *
 *  See Also:
 ****************************************************************************/
void
ResponseMenu()
{
    printf("\n Response Menu:");
    printf("\n -------------------------------------------------");
    printf("\n [%2d] User Error component", TEST_TCAP_U_ERROR);
    printf("\n [%2d] User Reject component", TEST_TCAP_U_REJECT);
    printf("\n");
    printf("\n [%2d] Abort dialog", TEST_TCAP_U_ABORT);
    printf("\n [%2d] End dialog(Basic end)", TEST_TCAP_END);
    printf("\n");
    printf("\n [%2d] INAP Response", TEST_INAP_RESPONSE);
    printf("\n -------------------------------------------------");
    printf("\n -> ");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a Begin dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      dlg - a pointer to the dialogue to send
 *      cpt_present - component present flag(TCP_NO_CPT or TCP_CPT_PRESENT)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the Begin dialog is sent successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPBeginDlg(ITS_HANDLE handle, ITS_HDR *header, TCAP_DLG *dlg,
                 int cpt_present)
{
    int result = 0;
    const char ac_name[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };
    const char user_info[6] = { 0x31, 0x31, 0x32, 0x32, 0x33, 0x00 };

    /* Set the type of dialog as a Begin dialog */
    dlg->ptype = TCPPT_TC_BEGIN;

    /* Set component present flag */
    dlg->u.begin.cpt_present = cpt_present;

    /* Ask user to include application context name */
    printf("\n Include aplication context name [y]es/[n]o ? ");
    if (getYesOrNo() == 1)
    {
        /* Set the application context name field of the Begin dialog */
        dlg->u.begin.ac_name.len = strlen(ac_name);
        memcpy(dlg->u.begin.ac_name.data, ac_name, strlen(ac_name));

    }
    /* Ask user to include user info */
    printf("\n Include user info [y]es/[n]o ? ");
    if (getYesOrNo() == 1)
    {
        /* Set the application user info field of the Begin dialog */
        dlg->u.begin.user_info.len = strlen(ac_name);
        memcpy(dlg->u.begin.user_info.data, ac_name, strlen(user_info));
    }

    /* Printout dialog information before sending */
    printf("\n Dialogue before sending.");
    traceDialogue(header, dlg);

    /* Sending dialog */
    result = TCAP_SendDialogue(handle, header, dlg);
    printf("\n result = %d", result);

    /* Check if dialog was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Dialog was sent successfully */
        printf("\n Begin dialog send success.");
    }
    else
    {
        /* Failed to send dialog */
        printf("\n WARNING: Failed send Begin dialog.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a TCAP Continue Dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt_present - component present flag
 *      orig_addr - a pointer to the originating address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the Continue dialog is sent successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPContinueDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
                    SCCP_ADDR *orig_addr)
{
    const char ac_name[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };
    const char user_info[6] = { 0x31, 0x31, 0x32, 0x32, 0x33, 0x00 };
    int result = 0;
    TCAP_DLG continueDlg;

    /* Initialize dialog structure */
    memset((char *)&continueDlg, 0, sizeof(TCAP_DLG));

    /* Indicate that this is a Continue dialog */
    continueDlg.ptype = TCPPT_TC_CONTINUE;

    /*
     * Set component present field, this can be two values
     * TCP_NO_CPT or TCP_CPT_PRESENT
     */
    continueDlg.u.cont.cpt_present = cpt_present;

    /* Set Continue dialog Quality of Service */
    continueDlg.u.cont.qos.indicator = QOSI_RET_OPT; 

    /* Ask user to include application context name */
    printf("\n Include aplication context name [y]es/[n]o ? ");
    if (getYesOrNo() == 1)
    {
        /* Set the application context name field of the Begin dialog */
        continueDlg.u.cont.ac_name.len = strlen(ac_name);
        memcpy(continueDlg.u.cont.ac_name.data, ac_name, strlen(ac_name));

        /* Ask user to include user info */
        printf("\n Include user info [y]es/[n]o ? ");
        if (getYesOrNo() == 1)
        {
            /* Set the application user info field of the Begin dialog */
            continueDlg.u.cont.user_info.len = strlen(ac_name);
            memcpy(continueDlg.u.cont.user_info.data, ac_name, strlen(user_info));
        }
    }

    /* Originating Point Code, opc */
#if 0
    continueDlg.u.cont.orig_addr.len = 0x04;
    continueDlg.u.cont.orig_addr.data[0] = 0x43;
    continueDlg.u.cont.orig_addr.data[1] = 0x02;
    continueDlg.u.cont.orig_addr.data[2] = 0x00;
    continueDlg.u.cont.orig_addr.data[3] = 0x06;
#endif

    /* Printout dialog information before sending */
    printf("\n Continue dialog before sending.");
    traceDialogue(header, &continueDlg);

    /* Sending dialog */
    result = TCAP_SendDialogue(handle, header, &continueDlg);
    printf("\n result = %d", result);

    /* Check if dialog was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Dialog sent successfully */
        printf("\n Continue dialog send success.");
    }
    else
    {
        /* Failed to send abort dialog */
        printf("\n WARNING: Failed to send Continue dialog.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a TCAP End Dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt_present - tag used to indicate if a dialog has a component
 *      termination - tag for the way to end the transaction
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the End dialog is sent successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The End dialog termination is set to basic end which ends the
 *      transaction with cpt_present having a value of TCP_NO_CPT or
 *      TCP_CPT_PRESENT. Valid termination values are TCPEND_BASIC_END and
 *      TCPEND_PREARRANGED.
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPEndDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
               int termination)
{
    const char ac_name[6] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x00 };
    const char user_info[6] = { 0x31, 0x31, 0x32, 0x32, 0x33, 0x00 };
    int choice = 0;
    int result = 0;
    TCAP_DLG endDlg;

    /* Initialize dialog structure */
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    /* Indicate that the dialog is an End dialog */
    endDlg.ptype = TCPPT_TC_END;

    /*
     * Set component present field, this can be two values
     * TCP_NO_CPT or TCP_CPT_PRESENT
     */
    endDlg.u.end.cpt_present = cpt_present;

    /* Set End dialog termination to basic end */
    endDlg.u.end.termination = termination;

    /* Ask user to include application context name */
    printf("\n Include aplication context name [y]es/[n]o ? ");
    if (getYesOrNo() == 1)
    {
        /* Set the application context name field of the Begin dialog */
        endDlg.u.end.ac_name.len = strlen(ac_name);
        memcpy(endDlg.u.end.ac_name.data, ac_name, strlen(ac_name));

        /* Ask user to include user info */
        printf("\n Include user info [y]es/[n]o ? ");
        if (getYesOrNo() == 1)
        {
            /* Set the application user info field of the Begin dialog */
            endDlg.u.end.user_info.len = strlen(ac_name);
            memcpy(endDlg.u.end.user_info.data, ac_name, strlen(user_info));
        }
    }

    /* Display end dialog information before sending it */
    printf("\n End Dialog before send.");
    traceDialogue(header, &endDlg);
    
    /* Send this End dialog */
    result = TCAP_SendDialogue(handle, header, &endDlg);
    printf("\n result = %d", result);

    /* Check if dialog was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* End dialog sent successfully */
        printf("\n End Dialog send success.");
    }
    else
    {
        /* Failed to send End dialog */
        printf("\n WARNING: Failed to send TCAP End Dialog.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an User Abort dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the User Abort dialog is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The abort reason is set to User defined.
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPUAbortDlg(ITS_HANDLE handle, ITS_HDR *header)
{
    int result = 0;
    int choice = 0;
    TCAP_DLG abortDlg;

    /* Initialize dialog structure */
    memset((char *)&abortDlg, 0, sizeof(TCAP_DLG));

    /* Indicate that this dialog will be a User Abort dialog */
    abortDlg.ptype = TCPPT_TC_U_ABORT;

    /* Selected user defined abort reason */
    abortDlg.u.abort.abort_reason = TCPUABT_USER_DEFINED;

    /* Printout dialog information before sending */
    printf("\n Abort dialog before sending.");
    traceDialogue(header, &abortDlg);

    /* Sending dialog */
    result = TCAP_SendDialogue(handle, header, &abortDlg);
    printf("\n result = %d", result);

    /* Check if dialog was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Dialog sent successfully */
        printf("\n Abort dialog send success.");
    }
    else
    {
        /* Failed to send abort dialog */
        printf("\n WARNING: Failed to send User Abort dialog.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an Unidirectional dialog.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the Unidirectional dialog is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPUniDlg(ITS_HANDLE handle, ITS_HDR *header, int cpt_present,
               SCCP_ADDR orig_addr, SCCP_ADDR dest_addr)
{
    int result = 0;
    int choice = 0;
    TCAP_DLG uniDlg;

    /* Initialize dialog structure */
    memset((char *)&uniDlg, 0, sizeof(TCAP_DLG));

    /* Indicate that this dialog will be a User Abort dialog */
    uniDlg.ptype = TCPPT_TC_UNI;

    /* Set component present flag */
    uniDlg.u.uni.cpt_present = cpt_present;

    /* Set originating address of the dialog */
    uniDlg.u.uni.orig_addr.len = orig_addr.len;
    memcpy(uniDlg.u.uni.orig_addr.data, orig_addr.data, orig_addr.len);

    /* Set destination address of the dialog */
    uniDlg.u.uni.dest_addr.len = dest_addr.len;
    memcpy(uniDlg.u.uni.dest_addr.data, dest_addr.data, dest_addr.len);

    /* qos */
    /* ac_name */
    /* user_info */
    /* opc */
    /* dpc */

    /* Printout dialog information before sending */
    printf("\n Unidirectional dialog before sending.");
    traceDialogue(header, &uniDlg);

    /* Sending dialog */
    result = TCAP_SendDialogue(handle, header, &uniDlg);
    printf("\n result = %d", result);

    /* Check if dialog was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Dialog sent successfully */
        printf("\n Unidirectional dialog send success.");
    }
    else
    {
        /* Failed to send abort dialog */
        printf("\n WARNING: Failed to send Unidirectional dialog.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CALL GAP ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the CallGap INAP procedure and
 *      calls INAP_SendCallGap(...) to encode the INAP procedure, set the
 *      parameter field of the component using the encoded value and then send
 *      the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If CallGap is sent successfully, ITS_SUCCESS is returned. Any other
 *      return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
int
sendCallGapArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;

    /* Structure used to send a Call Gap Arg */
    struct type_INAP_CallGapArg* cg_arg;

    /* Allocate and initialize the memory for the INAP structure */
    cg_arg = (struct type_INAP_CallGapArg*)
        calloc(1, sizeof(struct type_INAP_CallGapArg));

    /* Set CallGapArg fields before sending */
    printf("\n Setting CallGapArg parameters:");
    printf("\n ------------------------------");
    printf("\n");

        /* 
         * optionals, indicate that optional parameters are present or not.
         * If more than one optional field needs to be set the tags for the
         * fields, store the bitwise ORed value for the specific tags
         * ex. cg_arg->optionals = tag1 | tag2 | tag3;
         */
        cg_arg->optionals = opt_INAP_CallGapArg_controlType;

        /*
         * gapCriteria: criteria for a call to be subject to call gapping
         * Four criteria: calledAddressValue, gapOnService,
         * calledAddressAndService and callingAddressAndService
         */
        cg_arg->gapCriteria = (struct choice_INAP_9*)
                calloc(1, sizeof(struct choice_INAP_9));
        {
            /*
             * offset: used to select callingAddressAndService instead of the
             * other criteria
             */
            cg_arg->gapCriteria->offset = choice_INAP_9_callingAddressAndService;

            /* Allocate memory for callingAddressAndService field */
            cg_arg->gapCriteria->un.callingAddressAndService =
                (struct element_INAP_37*)calloc(1, sizeof(struct element_INAP_37));
            {
                /*
                 * Allocate memory for callingAddressValue using the size of a
                 * qbuf structure plus the string length of callingAddressValue
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->
                    callingAddressValue = 
                        (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                             strlen(callingAddressValue));

                /*
                 * qb_data needs to point to qbase so that the allocated memory
                 * for the structure can be freed properly later, to prevent
                 * memory leaks
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->
                callingAddressValue->qb_data =
                    cg_arg->gapCriteria->un.callingAddressAndService->
                callingAddressValue->qb_base;

                /*
                 * Set the length field of the qbuf structure match the string
                 * length of callingAddressValue
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->
                    callingAddressValue->qb_len = strlen(callingAddressValue);

                /*
                 * Copy the contents of callingAddressValue to the qb_data field
                 * of the qbuf structure
                 */
                memcpy(cg_arg->gapCriteria->un.callingAddressAndService->
                       callingAddressValue->qb_data, callingAddressValue,
                       strlen(callingAddressValue));

                /*
                 * Since the qbuf structure is a doubly linked list
                 * the head must point to the tail
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->
                    callingAddressValue->qb_forw =
                        cg_arg->gapCriteria->un.callingAddressAndService->
                            callingAddressValue;

                cg_arg->gapCriteria->un.callingAddressAndService->
                    callingAddressValue->qb_back =
                        cg_arg->gapCriteria->un.callingAddressAndService->
                            callingAddressValue;

                /* Set the serviceKey parameter */ 
                cg_arg->gapCriteria->un.callingAddressAndService->serviceKey =
                    serviceKey;

                /* Allocate memory for locationNumber parameter */
                cg_arg->gapCriteria->un.callingAddressAndService->locationNumber =
                    (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                         strlen(locationNumber));

                /*
                 * Need to have qb_data = qb_base so the allocated memory can be
                 * freed properly later
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->locationNumber->
                    qb_data = 
                    cg_arg->gapCriteria->un.callingAddressAndService->locationNumber->
                    qb_base;

                /*
                 * Set the length field of the qbuf structure to match the length
                 * of the string value to be used to set the field
                 */
                cg_arg->gapCriteria->un.callingAddressAndService->locationNumber->
                qb_len = strlen(locationNumber);

                /* Copy the string into the structure */
                memcpy(cg_arg->gapCriteria->un.callingAddressAndService->
                       locationNumber->qb_data, locationNumber,
                       strlen(locationNumber));

                /* Need to have the head point to the tail */
                cg_arg->gapCriteria->un.callingAddressAndService->locationNumber->
                    qb_forw = cg_arg->gapCriteria->un.callingAddressAndService->
                    locationNumber;

                cg_arg->gapCriteria->un.callingAddressAndService->locationNumber->
                    qb_back = cg_arg->gapCriteria->un.callingAddressAndService->
                    locationNumber;
            }
        }

        /* Allocate memory for gapIndicators field */
        cg_arg->gapIndicators = (struct element_INAP_38*)
            calloc(1, sizeof(struct element_INAP_38));
        {
            /* Set duration field value */
            cg_arg->gapIndicators->duration = duration;

            /* Set gapInterval field value */
            cg_arg->gapIndicators->gapInterval = gapInterval;
        }

        /* Set controlType field value */
        cg_arg->controlType = int_INAP_controlType_destinationOverload;

        /* Allocate memory for gapTreatment field */
        cg_arg->gapTreatment = (struct choice_INAP_10*)
            calloc(1, sizeof(struct choice_INAP_10));
        {
            /* Set offset field, the Both gap treatment is selected */
            cg_arg->gapTreatment->offset = choice_INAP_10_both;

            /* Allocate memory for Both field */
            cg_arg->gapTreatment->un.both = (struct element_INAP_47*)
                calloc(1, sizeof(struct element_INAP_47));
            {
                /* Allocate memory for informationToSend */
                cg_arg->gapTreatment->un.both->informationToSend =
                    (struct choice_INAP_14*)
                    calloc(1, sizeof(struct choice_INAP_14));
                {
                    /*
                     * Set offset: selected inbandInfo as the Information to send
                     */
                    cg_arg->gapTreatment->un.both->informationToSend->offset =
                        choice_INAP_11_inbandInfo;

                    /* Allocate memory for inbandInfo field */
                    cg_arg->gapTreatment->un.both->informationToSend->un.inbandInfo =
                        (struct element_INAP_48*)
                        calloc(1, sizeof(struct element_INAP_48));
                    {
                        /* 
                         * Set optional parameters to be present, in this case
                         * numberOfRepetitions, duration, and interval are present
                         */
                        cg_arg->gapTreatment->un.both->informationToSend->
                            un.inbandInfo->optionals =
                            opt_INAP_element_INAP_48_numberOfRepetitions |
                            opt_INAP_element_INAP_48_duration |
                            opt_INAP_element_INAP_48_interval;

                        /* Allocate memory for messageID field */
                        cg_arg->gapTreatment->un.both->informationToSend->
                            un.inbandInfo->messageID = (struct choice_INAP_15*)
                            calloc(1, sizeof(struct choice_INAP_15));
                        {
                            /* Set offset field*/
                            cg_arg->gapTreatment->un.both->informationToSend->
                                un.inbandInfo->messageID->offset =
                                choice_INAP_15_variableMessage;

                            /* allocate memory for variableMessage field */
                            cg_arg->gapTreatment->un.both->informationToSend->
                                un.inbandInfo->messageID->un.variableMessage =
                                (struct element_INAP_52*)
                                calloc(1, sizeof(struct element_INAP_52));
                            {
                                /* Set elementaryMessageID field */
                                cg_arg->gapTreatment->un.both->informationToSend->
                                    un.inbandInfo->messageID->un.variableMessage->
                                    elementaryMessageID = elementaryMessageID;

                                /* Allocate memory for variableParts field */
                                cg_arg->gapTreatment->un.both->informationToSend->
                                    un.inbandInfo->messageID->un.variableMessage->
                                    variableParts = (struct element_INAP_53*)
                                    calloc(1, sizeof(struct element_INAP_53));
                                {
                                    /* Allocate memory for element_INAP_54 */
                                    cg_arg->gapTreatment->un.both->
                                        informationToSend->un.inbandInfo->
                                        messageID->un.variableMessage->
                                        variableParts->element_INAP_54 =
                                            (struct choice_INAP_16*)
                                            calloc(1,
                                                   sizeof(struct choice_INAP_16));
                                    {
                                        /* Set offset field */
                                        cg_arg->gapTreatment->un.both->
                                            informationToSend->un.inbandInfo->
                                            messageID->un.variableMessage->
                                            variableParts->element_INAP_54->
                                            offset = choice_INAP_16_integer;

                                        /* Set integer field */
                                        cg_arg->gapTreatment->un.both->
                                            informationToSend->un.inbandInfo->
                                            messageID->un.variableMessage->
                                            variableParts->element_INAP_54->
                                            un.integer = integerval;
                                    }
                                }
                            }
                        }

                        /* Set numberOfRepetitions field */
                        cg_arg->gapTreatment->un.both->informationToSend->
                            un.inbandInfo->numberOfRepetitions = numberOfRepetitions;

                        /* Set duration field */
                        cg_arg->gapTreatment->un.both->informationToSend->
                            un.inbandInfo->duration = duration;

                        /* Set interval field */
                        cg_arg->gapTreatment->un.both->informationToSend->
                            un.inbandInfo->interval = interval;
                    }
                }

                /* Allocate memory for releaseCause field */
                cg_arg->gapTreatment->un.both->releaseCause = 
                    (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                         strlen(releaseCause));

                /*
                 * qb_data must be set equal to qb_base so the allocated memory
                 * can be freed properly later: prevent memory leaks
                 */
                cg_arg->gapTreatment->un.both->releaseCause->qb_data =
                    cg_arg->gapTreatment->un.both->releaseCause->qb_base;

                /*
                 * Set qb_len equal to the length of the string to be stored in
                 * the qbuf structure
                 */
                cg_arg->gapTreatment->un.both->releaseCause->qb_len =
                    strlen(releaseCause);
            
                /*
                 * Copy the the string releaseCause into the qbuf structure
                 */
                memcpy(cg_arg->gapTreatment->un.both->releaseCause->qb_data,
                       releaseCause, strlen(releaseCause));
            
                /* Head must point to tail */
                cg_arg->gapTreatment->un.both->releaseCause->qb_forw =
                    cg_arg->gapTreatment->un.both->releaseCause;
                cg_arg->gapTreatment->un.both->releaseCause->qb_back =
                    cg_arg->gapTreatment->un.both->releaseCause;
            }
        }

        /* optional extensions field is not supplied this time */

        /* Sending CallGapArg */
        printf("\n Going to send CallGap.");

        /* Send CallGap invoke */
        result = INAP_SendCallGap(handle, header, cpt, cg_arg);
        printf("\n result = %d", result);

    /* Check if CallGap invoke was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n Call Gap send success.");

        /* Printout component information before sending the dialog */
        traceComponent(header, cpt);
    }
    else
    {
        /* Failed to send CallGap invoke, print error */
        printf("\n Failed to send Call Gap.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CALL INFORMATION REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the CallInformationReport INAP
 *      procedure and calls INAP_SendCallInformationReport(...) to encode the
 *      INAP procedure, set the parameter field of the component using the
 *      encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If CallInformationReport is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendCallInformationReportArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;

    /* Structure used to send a Call Information Report Arg */
    struct type_INAP_CallInformationReportArg*  cirep_arg;

    cirep_arg = (struct type_INAP_CallInformationReportArg*)
        calloc(1, sizeof(struct type_INAP_CallInformationReportArg));
    
    /* Set CallInformationReportArg parameters */

    /* requestedInformationList */
    cirep_arg->requestedInformationList = (struct element_INAP_59*)
        calloc(1, sizeof(struct element_INAP_59));
    {
        /* element_INAP_60 */
        cirep_arg->requestedInformationList->element_INAP_60 =
            (struct element_INAP_61*)calloc(1, sizeof(struct element_INAP_61));
        {
            /* requestedInformationType */
            cirep_arg->requestedInformationList->element_INAP_60->
            requestedInformationType =
                int_INAP_requestedInformationType_callStopTime;
            
            /* requestedInformationValue */
            cirep_arg->requestedInformationList->element_INAP_60->
            requestedInformationValue = (struct choice_INAP_17*)
                calloc(1, sizeof(struct choice_INAP_17));
            {
                /* offset */
                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->offset =
                    choice_INAP_17_callStopTimeValue;

                /* callStopTimeValue */
                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->un.callStopTimeValue =
                    (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                         strlen(callStopTimeValue));

                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->un.callStopTimeValue->qb_data =
                    cirep_arg->requestedInformationList->element_INAP_60->
                    requestedInformationValue->un.callStopTimeValue->qb_base;

                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->un.callStopTimeValue->qb_len =
                    strlen(callStopTimeValue);
                                
                memcpy(cirep_arg->requestedInformationList->element_INAP_60->
                       requestedInformationValue->un.callStopTimeValue->qb_data,
                       callStopTimeValue, strlen(callStopTimeValue));

                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->un.callStopTimeValue->qb_forw =
                    cirep_arg->requestedInformationList->element_INAP_60->
                    requestedInformationValue->un.callStopTimeValue;
                
                cirep_arg->requestedInformationList->element_INAP_60->
                requestedInformationValue->un.callStopTimeValue->qb_back =
                    cirep_arg->requestedInformationList->element_INAP_60->
                    requestedInformationValue->un.callStopTimeValue;
            }
        }
    }

    /* correlationID */
    cirep_arg->correlationID = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                             strlen(correlationID));

    cirep_arg->correlationID->qb_data = cirep_arg->correlationID->qb_base;

    cirep_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(cirep_arg->correlationID->qb_data, correlationID,
           strlen(correlationID));

    cirep_arg->correlationID->qb_forw = cirep_arg->correlationID;
    cirep_arg->correlationID->qb_back = cirep_arg->correlationID;

    /* extensions */

    printf("\n Finished setting CallInformationReportArg parameters.");

    /* Sending CallInformationReportArg */
    printf("\n Going to send CallInformationReportArg.");

    result = INAP_SendCallInformationReport(handle, header, cpt, cirep_arg);
    printf("\n result = %d", result);

    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n CallInformationReportArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        /*
         * An error occured when trying to send CallGap invoke.
         * Print the error.
         */
        printf("\n WARNING: Failed to send Call Gap.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CALL INFORMATION REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the CallInformationRequest INAP
 *      procedure and calls INAP_SendCallInformationRequest(...) to encode the
 *      INAP procedure, set the parameter field of the component using the
 *      encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If CallInformationRequest is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendCallInformationRequestArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;

    /* Structure used to send a Call Information Request Arg */
    struct type_INAP_CallInformationRequestArg* cireq_arg;

    cireq_arg = (struct type_INAP_CallInformationRequestArg*)
        calloc(1, sizeof(struct type_INAP_CallInformationRequestArg));

    /* Set CallInformationRequestArg parameters */

    printf("\n Setting CallInformationRequestArg parameters.");

    /* requestedInformationTypeList */ 
    cireq_arg->requestedInformationTypeList = (struct element_INAP_65*)
        calloc(1, sizeof(struct element_INAP_65));
    {
        /* element_INAP_66 */
        cireq_arg->requestedInformationTypeList->element_INAP_66 =
            int_INAP_element_INAP_66_releaseCause;

        /*
         * next: next element for this list, this time only one element is
         * included
         */
    }

    /* correlationID */
    cireq_arg->correlationID = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                             strlen(correlationID));

    cireq_arg->correlationID->qb_data = 
        cireq_arg->correlationID->qb_base;

    cireq_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(cireq_arg->correlationID->qb_data, correlationID,
           strlen(correlationID));

    cireq_arg->correlationID->qb_forw = cireq_arg->correlationID;
    cireq_arg->correlationID->qb_back = cireq_arg->correlationID;

    /* extensions */
    
    printf("\n Finished setting CallInformationRequestArg parameters.");

    /* Sending CallInformationRequestArg */
    result = INAP_SendCallInformationRequest(handle, header, cpt, cireq_arg);
    printf("\n result = %d", result);

    /* Check if CallInformationRequestArg message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n CallInformationRequestArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        /*
         * An error occured while trying to send CallInformationRequestArg.
         * Print the error.
         */
        printf("\n Failed to send CallInformationRequestArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CANCEL STATUS REPORT REQUEST ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the CancelStatusReportRequest INAP
 *      procedure and calls INAP_SendCancelStatusReportRequest(...) to encode
 *      the INAP procedure, set the parameter field of the component using the
 *      encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If CancelStatusReportRequest is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendCancelStatusReportRequestArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_CancelStatusReportRequestArg* csrr_arg;

    csrr_arg = (struct type_INAP_CancelStatusReportRequestArg*)
        calloc(1, sizeof(struct type_INAP_CancelStatusReportRequestArg));
    
    /* Set parameters */

    printf("\n Setting CancelStatusReportRequestArg parameters.");

    /* resourceID */
    csrr_arg->resourceID = (struct choice_INAP_18*)
        calloc(1, sizeof(struct choice_INAP_18));
    {
        /* offset */
        csrr_arg->resourceID->offset = choice_INAP_18_facilityGroupID;

        /* facilityGroupID */
        csrr_arg->resourceID->un.facilityGroupID = (struct choice_INAP_19*)
            calloc(1, sizeof(struct choice_INAP_19));
        {
            /* offset */
            csrr_arg->resourceID->un.facilityGroupID->offset =
                choice_INAP_19_huntGroup;

            /* huntGroup */
            csrr_arg->resourceID->un.facilityGroupID->un.huntGroup = 
                (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                     strlen(huntGroup));

            csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_data =
                csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_base;

            csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_len =
                strlen(huntGroup);
            
            memcpy(csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->
                   qb_data, huntGroup, strlen(huntGroup));

            csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_forw =
                csrr_arg->resourceID->un.facilityGroupID->un.huntGroup;
            csrr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_back =
                csrr_arg->resourceID->un.facilityGroupID->un.huntGroup;
        } /* End facilityGroupID */

    } /* End resourceID */

    /* extensions */

    /* Sending CancelStatusReportRequestArg */
    printf("\n Going to send CancelStatusReportRequestArg.");
    result = INAP_SendCancelStatusReportRequest(handle, header, cpt, csrr_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n CancelStatusReportRequestArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send CancelStatusReportRequestArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CONNECT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the Connect INAP procedure and calls
 *      INAP_SendConnect(...) to encode the INAP procedure, set the parameter
 *      field of the component using the encoded value and then send the
 *      component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If Connect is sent successfully, ITS_SUCCESS is returned. Any other
 *      return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendConnectArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;
    struct type_INAP_ConnectArg* c_arg;

    /* Allocate memory for message structure */
    c_arg = (struct type_INAP_ConnectArg*)
        calloc(1, sizeof(struct type_INAP_ConnectArg));
    
    /* Set Parameters */

    /* optionals */
    c_arg->optionals = opt_INAP_ConnectArg_cutAndPaste |
                            opt_INAP_ConnectArg_forwardingCondition;

    /* destinationRoutingAddress */
    c_arg->destinationRoutingAddress = (struct element_INAP_85*)
        calloc( 1, sizeof(struct element_INAP_85));
    {
        /* element_INAP_86 */
        c_arg->destinationRoutingAddress->element_INAP_86 =
            (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                 strlen(element_INAP_86));

        c_arg->destinationRoutingAddress->element_INAP_86->qb_data =
            c_arg->destinationRoutingAddress->element_INAP_86->qb_base;

        c_arg->destinationRoutingAddress->element_INAP_86->qb_len =
            strlen(element_INAP_86);
        
        memcpy(c_arg->destinationRoutingAddress->element_INAP_86->qb_data,
               element_INAP_86, strlen(element_INAP_86));

        c_arg->destinationRoutingAddress->element_INAP_86->qb_forw =
            c_arg->destinationRoutingAddress->element_INAP_86;
        c_arg->destinationRoutingAddress->element_INAP_86->qb_back =
            c_arg->destinationRoutingAddress->element_INAP_86;
        /* next */
    }

    /* alertingPattern */
    c_arg->alertingPattern = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(alertingPattern));

    c_arg->alertingPattern->qb_data = 
        c_arg->alertingPattern->qb_base;

    c_arg->alertingPattern->qb_len = strlen(alertingPattern);

    memcpy(c_arg->alertingPattern->qb_data, alertingPattern,
           strlen(alertingPattern));

    c_arg->alertingPattern->qb_forw = c_arg->alertingPattern;
    c_arg->alertingPattern->qb_back = c_arg->alertingPattern;

    /* correlationID */
    c_arg->correlationID = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(correlationID));

    c_arg->correlationID->qb_data = 
        c_arg->correlationID->qb_base;

    c_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(c_arg->correlationID->qb_data, correlationID,
           strlen(correlationID));

    c_arg->correlationID->qb_forw = c_arg->correlationID;
    c_arg->correlationID->qb_back = c_arg->correlationID;

    /* cutAndPaste */
    c_arg->cutAndPaste = 11;
    
    /* forwardingCondition */
    c_arg->forwardingCondition = int_INAP_forwardingCondition_any;

    /* iSDNAccessRelatedInformation */
    c_arg->iSDNAccessRelatedInformation = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(isdnAccessRelatedInfo));

    c_arg->iSDNAccessRelatedInformation->qb_data =
        c_arg->iSDNAccessRelatedInformation->qb_base;

    c_arg->iSDNAccessRelatedInformation->qb_len =
        strlen(isdnAccessRelatedInfo);
    
    memcpy(c_arg->iSDNAccessRelatedInformation->qb_data,
           isdnAccessRelatedInfo, strlen(isdnAccessRelatedInfo));

    c_arg->iSDNAccessRelatedInformation->qb_forw =
        c_arg->iSDNAccessRelatedInformation;
    c_arg->iSDNAccessRelatedInformation->qb_back =
        c_arg->iSDNAccessRelatedInformation;

    /* originalCalledPartyID */
    c_arg->originalCalledPartyID =
        (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                             strlen(originalCalledPartyID));

    c_arg->originalCalledPartyID->qb_data =
        c_arg->originalCalledPartyID->qb_base;

    c_arg->originalCalledPartyID->qb_len = strlen(originalCalledPartyID);
    
    memcpy(c_arg->originalCalledPartyID->qb_data, originalCalledPartyID,
           strlen(originalCalledPartyID));

    c_arg->originalCalledPartyID->qb_forw =
        c_arg->originalCalledPartyID;
    c_arg->originalCalledPartyID->qb_back =
        c_arg->originalCalledPartyID;

    /* routeList */
    c_arg->routeList = (struct element_INAP_87*)
        calloc(1, sizeof(struct element_INAP_87));
    {
        /* element_INAP_88 */
        c_arg->routeList->element_INAP_88 = 
            (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                 strlen(element_INAP_88));

        c_arg->routeList->element_INAP_88->qb_data =
            c_arg->routeList->element_INAP_88->qb_base;

        c_arg->routeList->element_INAP_88->qb_len =
            strlen(element_INAP_88);
        
        memcpy(c_arg->routeList->element_INAP_88->qb_data,
               element_INAP_88, strlen(element_INAP_88));

        c_arg->routeList->element_INAP_88->qb_forw =
            c_arg->routeList->element_INAP_88;
        c_arg->routeList->element_INAP_88->qb_back =
            c_arg->routeList->element_INAP_88;

        /* next */
    }
    
    /* scfID */
    c_arg->scfID = (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                             strlen(scfID));

    c_arg->scfID->qb_data = c_arg->scfID->qb_base;

    c_arg->scfID->qb_len = strlen(scfID);
    
    memcpy(c_arg->scfID->qb_data, scfID, strlen(scfID));

    c_arg->scfID->qb_forw = c_arg->scfID;
    c_arg->scfID->qb_back = c_arg->scfID;

    /* travellingClassMark */
    c_arg->travellingClassMark =
        (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                             strlen(travellingClassMark));

    c_arg->travellingClassMark->qb_data =
        c_arg->travellingClassMark->qb_base;

    c_arg->travellingClassMark->qb_len = strlen(travellingClassMark);
    
    memcpy(c_arg->travellingClassMark->qb_data, travellingClassMark,
           strlen(travellingClassMark));

    c_arg->travellingClassMark->qb_forw = c_arg->travellingClassMark;
    c_arg->travellingClassMark->qb_back = c_arg->travellingClassMark;

    /* extensions: not used yet, client defined types */

    /* carrier */
    c_arg->carrier = (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                               strlen(carrier));

    c_arg->carrier->qb_data = c_arg->carrier->qb_base;

    c_arg->carrier->qb_len = strlen(carrier);
    
    memcpy(c_arg->carrier->qb_data, carrier, strlen(carrier));

    c_arg->carrier->qb_forw = c_arg->carrier;
    c_arg->carrier->qb_back = c_arg->carrier;

    /* serviceInteractionIndicators */
    c_arg->serviceInteractionIndicators = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(serviceInteractionIndicators));

    c_arg->serviceInteractionIndicators->qb_data =
        c_arg->serviceInteractionIndicators->qb_base;

    c_arg->serviceInteractionIndicators->qb_len =
        strlen(serviceInteractionIndicators);
    
    memcpy(c_arg->serviceInteractionIndicators->qb_data,
           serviceInteractionIndicators,
           strlen(serviceInteractionIndicators));

    c_arg->serviceInteractionIndicators->qb_forw =
        c_arg->serviceInteractionIndicators;
    c_arg->serviceInteractionIndicators->qb_back =
        c_arg->serviceInteractionIndicators;

    /* callingPartyNumber */
    c_arg->callingPartyNumber = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(callingPartyNumber));

    c_arg->callingPartyNumber->qb_data =
        c_arg->callingPartyNumber->qb_base;

    c_arg->callingPartyNumber->qb_len = strlen(callingPartyNumber);
    
    memcpy(c_arg->callingPartyNumber->qb_data, callingPartyNumber,
            strlen(callingPartyNumber));

    c_arg->callingPartyNumber->qb_forw = c_arg->callingPartyNumber;
    c_arg->callingPartyNumber->qb_back = c_arg->callingPartyNumber;

    /* callingPartysCategory */
    c_arg->callingPartysCategory = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(callingPartysCategory));

    c_arg->callingPartysCategory->qb_data =
        c_arg->callingPartysCategory->qb_base;

    c_arg->callingPartysCategory->qb_len = strlen(callingPartysCategory);
    
    memcpy(c_arg->callingPartysCategory->qb_data, callingPartysCategory,
            strlen(callingPartysCategory));

    c_arg->callingPartysCategory->qb_forw =
        c_arg->callingPartysCategory;
    c_arg->callingPartysCategory->qb_back =
        c_arg->callingPartysCategory;

    /* redirectingPartyID */
    /* redirectionInformation */

    /* Sending ConnectArg */
    printf("\n Going to send ConnectArg.");
    result = INAP_SendConnect(handle, header, cpt, c_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n ConnectArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send ConnectArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** CONTINUE ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the Continue INAP procedure
 *      and calls INAP_SendContinue(...) to encode the INAP procedure,
 *      set the parameter field of the component using the encoded value and
 *      then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If Conitnue is sent successfully, ITS_SUCCESS is returned. Any other
 *      return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendContinueArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;
    void* data = NULL;

    /* Sending ContinueArg */
    printf("\n Going to send ContinueArg.");
    result = INAP_SendContinue(handle, header, cpt, data);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n ContinueArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send ContinueArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** EVENT REPORT BCSM ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the EventReportBCSM INAP procedure
 *      and calls INAP_SendEventReportBCSM(...) to encode the INAP procedure,
 *      set the parameter field of the component using the encoded value and
 *      then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If EventReportBCSM is sent successfully, ITS_SUCCESS is returned. Any other
 *      return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendEventReportBCSMArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;
    struct type_INAP_EventReportBCSMArg *erb_arg;

    /* allocate memory for message structures */
    erb_arg = (struct type_INAP_EventReportBCSMArg *)
        calloc(1, sizeof(struct type_INAP_EventReportBCSMArg));

    /* Set parameters */

    printf("\n Setting EventReportBCSMArg");

    /* eventTypeBCSM */
    erb_arg->eventTypeBCSM = int_INAP_eventTypeBCSM_tDisconnect;

    /* bcsmEventCorrelationID */
    erb_arg->bcsmEventCorrelationID = 
        (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                             strlen(bcsmEventCorrelationID));

    erb_arg->bcsmEventCorrelationID->qb_data =
        erb_arg->bcsmEventCorrelationID->qb_base;

    erb_arg->bcsmEventCorrelationID->qb_len =
        strlen(bcsmEventCorrelationID);

    memcpy(erb_arg->bcsmEventCorrelationID->qb_data,
           bcsmEventCorrelationID, strlen(bcsmEventCorrelationID));

    erb_arg->bcsmEventCorrelationID->qb_forw =
        erb_arg->bcsmEventCorrelationID;
    erb_arg->bcsmEventCorrelationID->qb_back =
        erb_arg->bcsmEventCorrelationID;

    /* eventSpecificInformationBCSM */
    erb_arg->eventSpecificInformationBCSM = (struct choice_INAP_27*)
        calloc(1, sizeof(struct choice_INAP_27));
    {
        /* offset */
        erb_arg->eventSpecificInformationBCSM->offset =
            choice_INAP_27_tDisconnectSpecificInfo;

        /* tDisconnectSpecificInfo */
        erb_arg->eventSpecificInformationBCSM->un.tDisconnectSpecificInfo =
            (struct element_INAP_114*)calloc(1,
                                             sizeof(struct element_INAP_114));
        {
            /* optionals */
            erb_arg->eventSpecificInformationBCSM->
            un.tDisconnectSpecificInfo->optionals =
                opt_INAP_element_INAP_114_connectTime;

            /* releaseCause */
            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->releaseCause =
                    (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                         strlen(releaseCause));

            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->releaseCause->qb_data =
                    erb_arg->eventSpecificInformationBCSM->
                        un.tDisconnectSpecificInfo->releaseCause->qb_base;

            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->releaseCause->qb_len =
                    strlen(releaseCause);

            memcpy(erb_arg->eventSpecificInformationBCSM->
                   un.tDisconnectSpecificInfo->releaseCause->qb_data,
                   releaseCause, strlen(releaseCause));   

            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->releaseCause->qb_forw =
                    erb_arg->eventSpecificInformationBCSM->
                        un.tDisconnectSpecificInfo->releaseCause;
            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->releaseCause->qb_back =
                    erb_arg->eventSpecificInformationBCSM->
                        un.tDisconnectSpecificInfo->releaseCause;

            /* connectTime */
            erb_arg->eventSpecificInformationBCSM->
                un.tDisconnectSpecificInfo->connectTime = connectTime;
        }
    }

    /* legID */
    erb_arg->legID = (struct choice_INAP_28*)
        calloc(1, sizeof(struct choice_INAP_28));
    {
        /* offset */
        erb_arg->legID->offset = choice_INAP_28_sendingSideID;

        /* sendingSideID */
        erb_arg->legID->un.sendingSideID = 
            (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                 strlen(sendingSideID));

        erb_arg->legID->un.sendingSideID->qb_data =
            erb_arg->legID->un.sendingSideID->qb_base;

        erb_arg->legID->un.sendingSideID->qb_len =
            strlen(sendingSideID);

        memcpy(erb_arg->legID->un.sendingSideID->qb_data,
               sendingSideID, strlen(sendingSideID));

        erb_arg->legID->un.sendingSideID->qb_forw =
            erb_arg->legID->un.sendingSideID;
        erb_arg->legID->un.sendingSideID->qb_back =
            erb_arg->legID->un.sendingSideID;
    }

    /* miscCallInfo */
    erb_arg->miscCallInfo = (struct element_INAP_115 *)
        calloc(1, sizeof(struct element_INAP_115));
    {
        /* optionals */
        erb_arg->miscCallInfo->optionals =
            opt_INAP_element_INAP_115_dpAssignment;

        /* messageType */
        erb_arg->miscCallInfo->messageType = int_INAP_messageType_request;

        /* dpAssignment */
        erb_arg->miscCallInfo->dpAssignment =
            int_INAP_dpAssignment_groupBased;
    }

    /* extensions */

    /* Sending EventReportBCSMArg */
    printf("\n Going to send EventReportBCSMArg.");
    result = INAP_SendEventReportBCSM(handle, header, cpt, erb_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n EventReportBCSMArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send EventReportBCSMArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** INITIAL DP ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the InitialDP INAP procedure and
 *      calls INAP_SendInitialDP(...) to encode the INAP procedure, set the
 *      parameter field of the component using the encoded value and then send
 *      the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If InitialDP is sent successfully, ITS_SUCCESS is returned. Any other
 *      return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendInitialDPArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_InitialDPArg *idp_arg;

    /* Setting InitialDPArg parameters */ 
    printf("\n Setting InitialDPArg parameters.");

    /* Allocate memory for InitialDPArg */
    idp_arg = (struct type_INAP_InitialDPArg *)
        calloc(1, sizeof(struct type_INAP_InitialDPArg));

    /* Set Parameters */
    printf("\n Setting InitialDP Parameters.");
    /* optionals */
    idp_arg->optionals = opt_INAP_InitialDPArg_serviceKey |
                         opt_INAP_InitialDPArg_cGEncountered |
                         opt_INAP_InitialDPArg_terminalType |
                         opt_INAP_InitialDPArg_triggerType |
                         opt_INAP_InitialDPArg_eventTypeBCSM;

    /* serviceKey */
    idp_arg->serviceKey = serviceKey;

    /* dialledDigits */
    idp_arg->dialledDigits = (struct qbuf *)
        calloc(1, sizeof(struct qbuf) + strlen(dialledDigits));

    idp_arg->dialledDigits->qb_data =
        idp_arg->dialledDigits->qb_base;

    idp_arg->dialledDigits->qb_len = strlen(dialledDigits);

    memcpy(idp_arg->dialledDigits->qb_data, dialledDigits,
           strlen(dialledDigits));

    idp_arg->dialledDigits->qb_forw = idp_arg->dialledDigits;
    idp_arg->dialledDigits->qb_back = idp_arg->dialledDigits;

    /* calledPartyNumber */
    idp_arg->calledPartyNumber =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                              strlen(calledPartyNumber));

    idp_arg->calledPartyNumber->qb_data =
        idp_arg->calledPartyNumber->qb_base;

    idp_arg->calledPartyNumber->qb_len = strlen(calledPartyNumber);

    memcpy(idp_arg->calledPartyNumber->qb_data, calledPartyNumber,
           strlen(calledPartyNumber));

    idp_arg->calledPartyNumber->qb_forw = idp_arg->calledPartyNumber;
    idp_arg->calledPartyNumber->qb_back = idp_arg->calledPartyNumber;

    /* callingPartyNumber */
    idp_arg->callingPartyNumber =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(callingPartyNumber));

    idp_arg->callingPartyNumber->qb_data =
        idp_arg->callingPartyNumber->qb_base;

    idp_arg->callingPartyNumber->qb_len = strlen(callingPartyNumber);

    memcpy(idp_arg->callingPartyNumber->qb_data, callingPartyNumber,
           strlen(callingPartyNumber));

    idp_arg->callingPartyNumber->qb_forw =
        idp_arg->callingPartyNumber;
    idp_arg->callingPartyNumber->qb_back =
        idp_arg->callingPartyNumber;

    /* callingPartyBusinessGroupID */
    idp_arg->callingPartyBusinessGroupID =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                              strlen(callingPartyBusinessGroupID));

    idp_arg->callingPartyBusinessGroupID->qb_data =
        idp_arg->callingPartyBusinessGroupID->qb_base;

    idp_arg->callingPartyBusinessGroupID->qb_len =
        strlen(callingPartyBusinessGroupID);

    memcpy(idp_arg->callingPartyBusinessGroupID->qb_data,
           callingPartyBusinessGroupID, strlen(callingPartyBusinessGroupID));

    idp_arg->callingPartyBusinessGroupID->qb_forw =
        idp_arg->callingPartyBusinessGroupID;
    idp_arg->callingPartyBusinessGroupID->qb_back =
        idp_arg->callingPartyBusinessGroupID;

    /* callingPartysCategory */
    idp_arg->callingPartysCategory = (struct qbuf *)
        calloc(1, sizeof(struct qbuf) + strlen(callingPartysCategory));

    idp_arg->callingPartysCategory->qb_data =
        idp_arg->callingPartysCategory->qb_base;

    idp_arg->callingPartysCategory->qb_len =
        strlen(callingPartysCategory);

    memcpy(idp_arg->callingPartysCategory->qb_data,
           callingPartysCategory, strlen(callingPartysCategory));

    idp_arg->callingPartysCategory->qb_forw =
        idp_arg->callingPartysCategory;
    idp_arg->callingPartysCategory->qb_back =
        idp_arg->callingPartysCategory;

    /* callingPartySubaddress */
    idp_arg->callingPartySubaddress =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                              strlen(callingPartySubaddress));

    idp_arg->callingPartySubaddress->qb_data =
        idp_arg->callingPartySubaddress->qb_base;

    idp_arg->callingPartySubaddress->qb_len =
        strlen(callingPartySubaddress);

    memcpy(idp_arg->callingPartySubaddress->qb_data,
           callingPartysCategory, strlen(callingPartysCategory));
    
    idp_arg->callingPartySubaddress->qb_forw =
        idp_arg->callingPartySubaddress;
    idp_arg->callingPartySubaddress->qb_back =
        idp_arg->callingPartySubaddress;

    /* cGEncountered */
    idp_arg->cGEncountered = int_INAP_cGEncountered_scpOverload;

    /* iPSSPCapabilities */
    idp_arg->iPSSPCapabilities =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                              strlen(iPSSPCapabilities));

    idp_arg->iPSSPCapabilities->qb_len = strlen(iPSSPCapabilities);

    idp_arg->iPSSPCapabilities->qb_data = 
        idp_arg->iPSSPCapabilities->qb_base;
        
    memcpy(idp_arg->iPSSPCapabilities->qb_data,
           iPSSPCapabilities, strlen(iPSSPCapabilities));

    idp_arg->iPSSPCapabilities->qb_forw =
        idp_arg->iPSSPCapabilities;
    idp_arg->iPSSPCapabilities->qb_back =
        idp_arg->iPSSPCapabilities;
 
    /* iPAvailable */
    idp_arg->iPAvailable =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(iPAvailable));

    idp_arg->iPAvailable->qb_data = 
        idp_arg->iPAvailable->qb_base;

    idp_arg->iPAvailable->qb_len = strlen(iPAvailable);
    
    memcpy(idp_arg->iPAvailable->qb_data,
           iPAvailable, strlen(iPAvailable));

    idp_arg->iPAvailable->qb_forw = idp_arg->iPAvailable;
    idp_arg->iPAvailable->qb_back = idp_arg->iPAvailable;
    
    /* locationNumber */
    idp_arg->locationNumber = (struct qbuf *)
        calloc(1, sizeof(struct qbuf) + strlen(locationNumber));

    idp_arg->locationNumber->qb_data = 
        idp_arg->locationNumber->qb_base;

    idp_arg->locationNumber->qb_len = strlen(locationNumber);
    
    memcpy(idp_arg->locationNumber->qb_data, locationNumber,
           strlen(locationNumber));

    idp_arg->locationNumber->qb_forw = idp_arg->locationNumber;
    idp_arg->locationNumber->qb_back = idp_arg->locationNumber;

    /* miscCallInfo */
    idp_arg->miscCallInfo = (struct element_INAP_119 *)
        calloc(1, sizeof(struct element_INAP_119));
    {
        idp_arg->miscCallInfo->optionals =
            opt_INAP_element_INAP_119_dpAssignment;

        /* messageType */
        idp_arg->miscCallInfo->messageType =
            int_INAP_messageType_notification;

        /* dpAssignment */
        idp_arg->miscCallInfo->dpAssignment =
            int_INAP_dpAssignment_officeBased;
    }

    /* originalCalledPartyID */
    idp_arg->originalCalledPartyID = 
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(originalCalledPartyID));

    idp_arg->originalCalledPartyID->qb_data =
        idp_arg->originalCalledPartyID->qb_base;

    idp_arg->originalCalledPartyID->qb_len =
        strlen(originalCalledPartyID);

    memcpy(idp_arg->originalCalledPartyID->qb_data,
           originalCalledPartyID, strlen(originalCalledPartyID));

    idp_arg->originalCalledPartyID->qb_forw =
        idp_arg->originalCalledPartyID;
    idp_arg->originalCalledPartyID->qb_back =
        idp_arg->originalCalledPartyID;

    /* serviceProfileIdentifier */
    idp_arg->serviceProfileIdentifier =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(serviceProfileIdentifier));

    idp_arg->serviceProfileIdentifier->qb_data =
        idp_arg->serviceProfileIdentifier->qb_base;

    idp_arg->serviceProfileIdentifier->qb_len =
        strlen(serviceProfileIdentifier);
    
    memcpy(idp_arg->serviceProfileIdentifier->qb_data,
           serviceProfileIdentifier, strlen(serviceProfileIdentifier));

    idp_arg->serviceProfileIdentifier->qb_forw =
        idp_arg->serviceProfileIdentifier;
    idp_arg->serviceProfileIdentifier->qb_back =
        idp_arg->serviceProfileIdentifier;

    /* terminalType */
    idp_arg->terminalType = int_INAP_terminalType_spare;

    /* extensions, optional parameter not included */
    
    /* triggerType */
    idp_arg->triggerType = int_INAP_triggerType_tDisconnect;

    /* highLayerCompatibility */
    /* serviceInteractionIndicators */ 
    /* additionalCallingPartyNumber */
    /* forwardCallIndicators */

    /* bearerCapability */
    idp_arg->bearerCapability = (struct choice_INAP_29*)
        calloc(1, sizeof(struct choice_INAP_29));
    {
        idp_arg->bearerCapability->un.bearerCap = 
            (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                 strlen(bearerCap));

        idp_arg->bearerCapability->offset = choice_INAP_29_bearerCap;

        idp_arg->bearerCapability->un.bearerCap->qb_len =
            strlen(bearerCap);
        idp_arg->bearerCapability->un.bearerCap->qb_data =
            idp_arg->bearerCapability->un.bearerCap->qb_base;

        memcpy(idp_arg->bearerCapability->un.bearerCap->qb_data,
               bearerCap, strlen(bearerCap));

        idp_arg->bearerCapability->un.bearerCap->qb_forw =
            idp_arg->bearerCapability->un.bearerCap;
        idp_arg->bearerCapability->un.bearerCap->qb_back =
            idp_arg->bearerCapability->un.bearerCap;
    }

    /* eventTypeBCSM */
    idp_arg->eventTypeBCSM = int_INAP_eventTypeBCSM_tAbandon;

    /* redirectingPartyID */
    /* redirectionInformation */
    
    printf("\n Finished setting InitialDP parameters.");    

    /* Send InitialDPArg Invoke Component */
    printf("\n Going to send InitialDP.");
    result = INAP_SendInitialDP(handle, header, cpt, idp_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n InitialDP send success.");

        /* Printout component information */
        traceComponent(header, cpt);   
    }
    else
    {
        printf("\n Failed to send InitialDP.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** RELEASE CALL ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the ReleaseCallArg
 *      INAP procedure and calls INAP_SendReleaseCall(...)
 *      to encode the INAP procedure, set the parameter field of the component
 *      using the encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If ReleaseCall is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendReleaseCallArg(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *cpt)
{
    int result = 0;
    struct type_INAP_ReleaseCallArg* rcArg;
    const char data[6] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x00 };

    /* Initialize memory for INAP structure */
    rcArg = (struct type_INAP_ReleaseCallArg*)
        calloc(1, sizeof(struct type_INAP_ReleaseCallArg));

    /* Needed to free allocated memory properly */
    rcArg->qb_data = rcArg->qb_base;

    /* Set length field of qbuf structure */
    rcArg->qb_len = strlen(data);

    /* Copy octets into qbuf */
    memcpy(rcArg->qb_data, data, strlen(data));

    /* qbuf is a doubly linked list, head must point to tail */
    rcArg->qb_forw = rcArg;
    rcArg->qb_back = rcArg;

    printf("\n Finished setting ReleaseCallArg parameters.");

    /* Send ReleaseCallArg Invoke Component */
    printf("\n Going to send ReleaseCallArg.");
    result = INAP_SendReleaseCall(handle, header, cpt, rcArg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n ReleaseCall send success.");

        /* Printout component information */
        traceComponent(header, cpt);   
    }
    else
    {
        printf("\n Failed to send ReleaseCall.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** REQUEST EVERY STATUS CHANGE REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the RequestEveryStatusChangeReport
 *      INAP procedure and calls INAP_SendRequestEveryStatusChangeReport(...)
 *      to encode the INAP procedure, set the parameter field of the component
 *      using the encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If RequestEveryStatusChangeReport is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendRequestEveryStatusChangeReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                      TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_RequestEveryStatusChangeReportArg *rescr_arg;

    /* allocate memory for message structures */
    rescr_arg = (struct type_INAP_RequestEveryStatusChangeReportArg*)
        calloc(1, sizeof(struct type_INAP_RequestEveryStatusChangeReportArg));
    
    /* Set parameters */

    /* optionals */
    rescr_arg->optionals =
        opt_INAP_RequestEveryStatusChangeReportArg_monitorDuration;

    /* resourceID */
    rescr_arg->resourceID = (struct choice_INAP_51*)
        calloc(1, sizeof(struct choice_INAP_51));
    {
        /* offset */
        rescr_arg->resourceID->offset = choice_INAP_51_facilityGroupID;

        /* facilityGroupID */
        rescr_arg->resourceID->un.facilityGroupID = (struct choice_INAP_52*)
            calloc(1, sizeof(struct choice_INAP_52));
        {
            /* offset */
            rescr_arg->resourceID->un.facilityGroupID->offset =
                choice_INAP_52_huntGroup;

            /* huntGroup */
            rescr_arg->resourceID->un.facilityGroupID->un.huntGroup =
                (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                     strlen(huntGroup));

            rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_data =
                rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_base;

            rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_len =
                strlen(huntGroup);
            
            memcpy(rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->
                   qb_data, huntGroup, strlen(huntGroup));

            rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_forw =
                rescr_arg->resourceID->un.facilityGroupID->un.huntGroup;
            rescr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_back =
                rescr_arg->resourceID->un.facilityGroupID->un.huntGroup;
        } /* End facilityGroupID */

    } /* End resourceID */

    /* correlationID */
    rescr_arg->correlationID = 
        (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                              strlen(correlationID));

    rescr_arg->correlationID->qb_data =
        rescr_arg->correlationID->qb_base;

    rescr_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(rescr_arg->correlationID->qb_data, correlationID,
           strlen(correlationID));

    rescr_arg->correlationID->qb_forw = rescr_arg->correlationID;
    rescr_arg->correlationID->qb_back = rescr_arg->correlationID;

    /* monitorDuration */
    rescr_arg->monitorDuration = monitorDuration;

    /* extensions */

    /* Sending RequestEveryStatusChangeReportArg */
    printf("\n Going to send RequestEveryStatusChangeReportArg.");
    result = INAP_SendRequestEveryStatusChangeReport(handle, header, cpt,
                                                     rescr_arg);
    printf("\n result = %d", result);

    /* Check if INAP Message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n RequestEveryStatusChangeReportArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send RequestEveryStatusChangeReportArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** REQUEST FIRST STATUS MATCH REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the RequestFirstStatusMatchReport
 *      INAP procedure and calls INAP_SendRequestFirstStatusMatchReport(...)
 *      to encode the INAP procedure, set the parameter field of the component
 *      using the encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If RequestFirstStatusMatchReport is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendRequestFirstStatusMatchReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_RequestFirstStatusMatchReportArg* rfsmr_arg;

    rfsmr_arg = (struct type_INAP_RequestFirstStatusMatchReportArg*)
        calloc(1, sizeof(struct type_INAP_RequestFirstStatusMatchReportArg));
    
    /*
     * Set parameters
     */

    /* optionals */
    rfsmr_arg->optionals =
        opt_INAP_RequestFirstStatusMatchReportArg_resourceStatus |
        opt_INAP_RequestFirstStatusMatchReportArg_monitorDuration;


    /* resourceID */
    rfsmr_arg->resourceID = (struct choice_INAP_53*)
        calloc(1, sizeof(struct choice_INAP_53));
    {
        /* offset */
        rfsmr_arg->resourceID->offset = choice_INAP_53_facilityGroupID;

        /* facilityGroupID */
        rfsmr_arg->resourceID->un.facilityGroupID = (struct choice_INAP_54*)
            calloc(1, sizeof(struct choice_INAP_54));
        {
            /* offset */
            rfsmr_arg->resourceID->un.facilityGroupID->offset =
                choice_INAP_54_huntGroup;

            /* huntGroup */
            rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup = 
                (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                     strlen(huntGroup));

            rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_data =
                rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_base;

            rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_len =
                strlen(huntGroup);
            
            memcpy(rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->
                   qb_data, huntGroup, strlen(huntGroup));

            rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_forw =
                rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup;
            rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_back =
                rfsmr_arg->resourceID->un.facilityGroupID->un.huntGroup;
        } /* End facilityGroupID */

    } /* End resourceID */

    /* resourceStatus */
    rfsmr_arg->resourceStatus = int_INAP_resourceStatus_idle;

    /* correlationID */
    rfsmr_arg->correlationID = 
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(correlationID));

    rfsmr_arg->correlationID->qb_data = rfsmr_arg->correlationID->qb_base;

    rfsmr_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(rfsmr_arg->correlationID->qb_data,
           correlationID, strlen(correlationID));

    rfsmr_arg->correlationID->qb_forw = rfsmr_arg->correlationID;
    rfsmr_arg->correlationID->qb_back = rfsmr_arg->correlationID;

    /* monitorDuration */
    rfsmr_arg->monitorDuration = monitorDuration;

    /* extensions */

    /* bearerCapability */
    rfsmr_arg->bearerCapability = (struct choice_INAP_55*)
        calloc(1, sizeof(struct choice_INAP_55));
    {
        /* offset */
        rfsmr_arg->bearerCapability->offset = choice_INAP_55_bearerCap;

        /* bearerCap */
        rfsmr_arg->bearerCapability->un.bearerCap = 
            (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                 strlen(bearerCap));

        rfsmr_arg->bearerCapability->un.bearerCap->qb_data =
            rfsmr_arg->bearerCapability->un.bearerCap->qb_base;

        rfsmr_arg->bearerCapability->un.bearerCap->qb_len =
            strlen(bearerCap);
        
        memcpy(rfsmr_arg->bearerCapability->un.bearerCap->qb_data,
               bearerCap, strlen(bearerCap));

        rfsmr_arg->bearerCapability->un.bearerCap->qb_forw =
            rfsmr_arg->bearerCapability->un.bearerCap;
        rfsmr_arg->bearerCapability->un.bearerCap->qb_back =
            rfsmr_arg->bearerCapability->un.bearerCap;
    } /* End bearerCapability */

    /*
     * Sending RequestFirstStatusMatchReportArg
     */
    printf("\n Going to send RequestFirstStatusMatchReportArg.");
    result = INAP_SendRequestFirstStatusMatchReport(handle, header, cpt,
                                                    rfsmr_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n RequestFirstStatusMatchReportArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send RequestFirstStatusMatchReportArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** REQUEST CURRENT STATUS REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the RequestCurrentStatusReport
 *      INAP procedure and calls INAP_SendRequestCurrentStatusReport(...)
 *      to encode the INAP procedure, set the parameter field of the component
 *      using the encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If RequestCurrentStatusReport is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendRequestCurrentStatusReportArg(ITS_HANDLE handle, ITS_HDR *header,
                                  TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_RequestCurrentStatusReportArg *rcsr_arg;

    rcsr_arg = (struct type_INAP_RequestCurrentStatusReportArg*)
        calloc(1, sizeof(struct type_INAP_RequestCurrentStatusReportArg));
    
    /* Set parameters */

    /* offset */
    rcsr_arg->offset = type_INAP_RequestCurrentStatusReportArg_facilityGroupID;

    /* facilityGroupID */
    rcsr_arg->un.facilityGroupID = (struct choice_INAP_48*)
        calloc(1, sizeof(struct choice_INAP_48));
    {
        /* offset */
        rcsr_arg->un.facilityGroupID->offset = choice_INAP_48_huntGroup;

        /* huntGroup */
        rcsr_arg->un.facilityGroupID->un.huntGroup = 
            (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                 strlen(huntGroup));

        rcsr_arg->un.facilityGroupID->un.huntGroup->qb_data = 
            rcsr_arg->un.facilityGroupID->un.huntGroup->qb_base;

        rcsr_arg->un.facilityGroupID->un.huntGroup->qb_len = strlen(huntGroup);
        
        memcpy(rcsr_arg->un.facilityGroupID->un.huntGroup->qb_data, huntGroup,
               strlen(huntGroup));

        rcsr_arg->un.facilityGroupID->un.huntGroup->qb_forw =
            rcsr_arg->un.facilityGroupID->un.huntGroup;
        rcsr_arg->un.facilityGroupID->un.huntGroup->qb_back =
            rcsr_arg->un.facilityGroupID->un.huntGroup;
    } /* End facilityGroupID */

    /* Sending RequestCurrentStatusReportArg */
    printf("\n Going to send RequestCurrentStatusReportArg.");
    result = INAP_SendRequestCurrentStatusReport(handle, header, cpt,
                                                 rcsr_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n RequestCurrentStatusReportArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send RequestCurrentStatusReportArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** REQUEST CURRENT STATUS REPORT RESULT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the RequestCurrentStatusReportResult
 *      INAP procedure and calls INAP_SendRequestCurrentStatusReportResult(..)
 *      to encode the INAP procedure, set the parameter field of the component
 *      using the encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If RequestCurrentStatusReportResult is sent successfully, ITS_SUCCESS
 *      is returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendRequestCurrentStatusReportResult(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_RequestCurrentStatusReportResult *rcsr_res;

    rcsr_res = (struct type_INAP_RequestCurrentStatusReportResult*)
        calloc(1, sizeof(struct type_INAP_RequestCurrentStatusReportResult));

    /* Set RequestCurrentStatusReportResult parameters */

    /* Set mandatory parameter resourceStatus */
    rcsr_res->resourceStatus = int_INAP_resourceStatus_busy;

    /* Sending RequestCurrentStatusReportResult */
    printf("\n Going to send RequestCurrentStatusReportResult.");
    result = INAP_SendRequestCurrentStatusReportResult(handle, header, cpt,
                                                       rcsr_res);
    printf("\n result = %d", result);

    /* Check if RequestCurrentStatusReportResult was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n RequestCurrentStatusReportResult send success.");
    }
    else
    {
        /* Failed to send INAP message */
        printf("\n Failed to send RequestCurrentStatusReportResult.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }

    return result;
}

/*** REQUEST CURRENT STATUS REPORT RESULT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the RequestReportBCSMEvent INAP
 *      procedure and calls INAP_SendRequestReportBCSMEvent(..) to encode the
 *      INAP procedure, set the parameter field of the component using the
 *      encoded value and then send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If RequestReportBCSMEvent is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendRequestReportBCSMEventArg(ITS_HANDLE handle, ITS_HDR *header,
                              TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_RequestReportBCSMEventArg* rrbe_arg;

    /* allocate memory for message struct */
    rrbe_arg = (struct type_INAP_RequestReportBCSMEventArg*)
        calloc(1, sizeof(struct type_INAP_RequestReportBCSMEventArg));
    
    /* Set parameters */

    /* bcsmEvents */
    rrbe_arg->bcsmEvents = (struct element_INAP_224*)
        calloc(1, sizeof(struct element_INAP_224));
    {
        rrbe_arg->bcsmEvents->element_INAP_225 = (struct element_INAP_226*)
            calloc(1, sizeof(struct element_INAP_226));

        /* eventTypeBCSM */
        rrbe_arg->bcsmEvents->element_INAP_225->eventTypeBCSM =
            int_INAP_eventTypeBCSM_origAttemptAuthorized;

        /* monitorMode */
        rrbe_arg->bcsmEvents->element_INAP_225->monitorMode =
            int_INAP_monitorMode_interrupted;

        /* legID */
        rrbe_arg->bcsmEvents->element_INAP_225->legID =
            (struct choice_INAP_57*)calloc(1, sizeof(struct choice_INAP_57));
        {
            /* offset */
            rrbe_arg->bcsmEvents->element_INAP_225->legID->offset =
                choice_INAP_57_sendingSideID;

            /* sendingSideID */
            rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID =
                (struct qbuf*)calloc(1, sizeof(struct qbuf) + 
                                     strlen(sendingSideID));

            rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID->
            qb_data = 
                rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID->
                qb_base;

            rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID->
                qb_len = strlen(sendingSideID);
            
            memcpy(rrbe_arg->bcsmEvents->element_INAP_225->legID->
                   un.sendingSideID->qb_data, sendingSideID,
                   strlen(sendingSideID));

            rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID->
                qb_forw = rrbe_arg->bcsmEvents->element_INAP_225->legID->
                un.sendingSideID;
            rrbe_arg->bcsmEvents->element_INAP_225->legID->un.sendingSideID->
                qb_back = rrbe_arg->bcsmEvents->element_INAP_225->legID->
                un.sendingSideID;

        } /* end legID */

        /* dpSpecificCriteria */
        rrbe_arg->bcsmEvents->element_INAP_225->dpSpecificCriteria =
            (struct choice_INAP_58*)calloc(1, sizeof(struct choice_INAP_58));
        {
            /* offset */
            rrbe_arg->bcsmEvents->element_INAP_225->dpSpecificCriteria->
                offset = choice_INAP_58_numberOfDigits;

            /* numberOfDigits */

            rrbe_arg->bcsmEvents->element_INAP_225->dpSpecificCriteria->
                un.numberOfDigits = numberOfDigits;
        } /* end dpSpecificCriteria */

    } /* end bcsmEvents structure */

    /* bcsmEventCorrelationID */
    rrbe_arg->bcsmEventCorrelationID =
        (struct qbuf *)calloc(1, sizeof(struct qbuf) + 
                              strlen(bcsmEventCorrelationID));

    rrbe_arg->bcsmEventCorrelationID->qb_data =
        rrbe_arg->bcsmEventCorrelationID->qb_base;

    rrbe_arg->bcsmEventCorrelationID->qb_len = strlen(bcsmEventCorrelationID);
    
    memcpy(rrbe_arg->bcsmEventCorrelationID->qb_data,
           bcsmEventCorrelationID, strlen(bcsmEventCorrelationID));

    rrbe_arg->bcsmEventCorrelationID->qb_forw =
        rrbe_arg->bcsmEventCorrelationID;
    rrbe_arg->bcsmEventCorrelationID->qb_back =
        rrbe_arg->bcsmEventCorrelationID;    
   
    /* extensions */

    /* Sending RequestReportBCSMEventArg */
    printf("\n Going to send RequestReportBCSMEventArg.");
    result = INAP_SendRequestReportBCSMEvent(handle, header, cpt,
                                             rrbe_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n RequestReportBCSMEventArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send RequestReportBCSMEventArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*** STATUS REPORT ***/
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets the fields for the StatusReport INAP procedure
 *      and calls INAP_SendStatusReport(..) to encode the INAP procedure, set
 *      the parameter field of the component using the encoded value and then
 *      send the component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If StatusReport is sent successfully, ITS_SUCCESS is returned. Any
 *      other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Memory needs to be allocated for the INAP Message structure. Also,
 *      memory needs to be allocated for the paramaters of the INAP procedure
 *      which are also structures.
 *
 *      Each INAP procedure has its own INAP_SendXXXX() function.
 *
 *  See Also:
 *      sendCallGapArg()
 ****************************************************************************/
int
sendStatusReportArg(ITS_HANDLE handle, ITS_HDR *header, 
                    TCAP_CPT *cpt)
{
    int result = 0;

    struct type_INAP_StatusReportArg *sr_arg;

    sr_arg = (struct type_INAP_StatusReportArg*)
        calloc(1, sizeof(struct type_INAP_StatusReportArg));
    
    /* Set parameters */

    /* optionals */
    sr_arg->optionals = opt_INAP_StatusReportArg_resourceStatus |
                        opt_INAP_StatusReportArg_reportCondition;

    /* resourceStatus */
    sr_arg->resourceStatus = int_INAP_resourceStatus_idle;

    /* correlationID */
    sr_arg->correlationID = (struct qbuf *)calloc(1, sizeof(struct qbuf) +
                                                 strlen(correlationID));

    sr_arg->correlationID->qb_data = sr_arg->correlationID->qb_base;

    sr_arg->correlationID->qb_len = strlen(correlationID);
    
    memcpy(sr_arg->correlationID->qb_data, correlationID,
           strlen(correlationID));

    sr_arg->correlationID->qb_forw = sr_arg->correlationID;
    sr_arg->correlationID->qb_back = sr_arg->correlationID;

    /* resourceID */
    sr_arg->resourceID = (struct choice_INAP_64*)
        calloc(1, sizeof(struct choice_INAP_64));
    {
        /* offset */
        sr_arg->resourceID->offset = choice_INAP_64_facilityGroupID;

        /* facilityGroupID */
        sr_arg->resourceID->un.facilityGroupID = (struct choice_INAP_65*)
            calloc(1, sizeof(struct choice_INAP_65));
        {
            /* offset */
            sr_arg->resourceID->un.facilityGroupID->offset =
                choice_INAP_65_huntGroup;

            /* huntGroup */
            sr_arg->resourceID->un.facilityGroupID->un.huntGroup =
                (struct qbuf*)calloc(1, sizeof(struct qbuf) +
                                     strlen(huntGroup));

            sr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_data =
                sr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_base;

            sr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_len =
                strlen(huntGroup);
            
            memcpy(sr_arg->resourceID->un.facilityGroupID->un.huntGroup->
                   qb_data, huntGroup, strlen(huntGroup));

            sr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_forw =
                sr_arg->resourceID->un.facilityGroupID->un.huntGroup;
            sr_arg->resourceID->un.facilityGroupID->un.huntGroup->qb_back =
                sr_arg->resourceID->un.facilityGroupID->un.huntGroup;
        } /* End facilityGroupID */

    } /* End resourceID */

    /* extensions */

    /* reportCondition */
    sr_arg->reportCondition = int_INAP_reportCondition_timerExpired;

    /* Sending StatusReportArg */
    printf("\n Going to send StatusReportArg.");
    result = INAP_SendStatusReport(handle, header, cpt, sr_arg);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameters of the Invoke Component
         */
        printf("\n StatusReportArg send success.");

        /* Printout component information before sending */
        traceComponent(header, cpt);
    }
    else
    {
        printf("\n Failed to send StatusReportArg.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will ask the user for an SCCP Address.
 *      
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - pointer to an allocated SCCP_ADDR structure
 *
 *  Return Value:
 *      If the SCCP address is encoded successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Global title is not included for the alpha release of the Send and
 *      Receive test programs. Global Title translation is included in the
 *      beta release of the Send and Receive test programs.
 *
 *  See Also:
 ****************************************************************************/
int
getSCCPAddr(SCCP_ADDR *addr)
{
    ITS_OCTET addressIndicator = (0x00U);
    int ssn;
    ITS_UINT  pc;
    int gttLen = 0;
    ITS_OCTET gttInfo[50];

    /* User selects between National and International Standard */
    printf("\n Does SCCP Address use National Standard ?");
    printf("\n press [y] for yes, [n] for no (International) -> ");
    if (getYesOrNo() == 1)
    {
        /* Set the addressIndicator bit flag for National standard */
        addressIndicator = addressIndicator | SCCP_CPA_ROUTE_NAT;
    }

    /* User selects to route messages using SSN or GT Translation */
    printf("\n Route Message using SSN ?");
    printf("\n press [y] for yes, [n] for no (Perform GT Translation) -> ");
    if (getYesOrNo() == 1)
    {
        /* Set the bit flag for Route using SSN */
        addressIndicator = addressIndicator | SCCP_CPA_ROUTE_SSN;
    }

    /* User indicates if the address holds an SSN */
    printf("\n Does SCCP Address hold an SSN ?");
    printf("\n press [y] for yes, [n] for no -> ");
    if (getYesOrNo() == 1)
    {
        /* Set the bit flag for SCCP Address having an SSN */
        addressIndicator = addressIndicator | SCCP_CPA_HAS_SSN;

        /* Ask user for an SSN */
        printf("\n Please Enter SSN (decimal value) -> ");
        scanf("%d", &ssn);
    }

    /* Ask user if the address has an Point Code */
    printf("\n Does SCCP Address hold an Point Code ?");
    printf("\n press [y] for yes, [n] for no -> ");
    if (getYesOrNo() == 1)
    {
        /* Set the Point code bit flag */
        addressIndicator = addressIndicator | SCCP_CPA_HAS_PC;

        /* Ask user for point code */
        printf("\n Please Enter Point Code (decimal value) -> ");
        scanf("%u", &pc);
    }

    /* Ask user if the address has a global title */
    printf("\n Does SCCP Address hold a Global Title?");
    printf("\n press [y] for yes, [n] for no -> ");
    if (getYesOrNo() == 1)
    {
        setGTT(&addressIndicator, gttInfo, &gttLen);
    }

    /* Encode the SCCP Address, builds the address so it can be used */
    return SCCP_EncodeAddr(addr, addressIndicator, pc, (ITS_OCTET)ssn, 
                           gttInfo, gttLen);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a SCCP User Out Of Service message,
 *      essentially informing the SCCP layer that services that the sender
 *      no longer need servicing.
 *
 *  Input Parameters:
 *      handle - the transport associated with application
 *      orig - the SCCP address of the sender
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the SCCP address is decoded successfully and the SCCP message is
 *      sent successfully ITS_SUCCESS is returned. Any other return code
 *      indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The function will decode the SCCP address to get the originating
 *      point code and the subsytem number of the sender. The opc and
 *      the ssn are necessary for sending the SCCP message.
 *
 *  See Also:
 ****************************************************************************/
int
sendUserOutOfService(ITS_HANDLE handle, SCCP_ADDR orig)
{
    int result = 0;

    ITS_OCTET ssn;
    ITS_OCTET addrInd;
    ITS_UINT opc;
    ITS_OCTET gttInfo[50];
    ITS_USHORT gttLen;

    printf("\n In sendUserOutOfService()");

    /*
     * Decode the sccp address and store the corresponding values for the SCCP
     * fields into the formal arguments: 2, 3, 4, 5, and 6
     */
    result = SCCP_DecodeAddr(&orig, &addrInd, &opc, &ssn, gttInfo, &gttLen);
    printf("\n result = %d", result);

    /* Check if SCCP address was decoded successfully */
    if (result == ITS_SUCCESS)
    {
        /* SCCP Address decoded successfully */
        printf("\n SCCP_Address successfully decoded");
        printf("\n");

        /* Print out the SSCP Address values */
        printf("\n Address Indicator: %x", addrInd);
        printf("\n               opc: %x", opc);
        printf("\n               ssn: %x", ssn);
    }
    else
    {
        /* Failed to decode the address, print the error */
        printf("\n Failed to decode SCCP_Address.");
        printf("\n Error: ");
        printf("%s", ITS_GetErrorText(result));
        printf("\n");
        return result;
    }

    /* Send an SCCP User Out of service message */
    return SCCP_SendUserOutOfService(handle, opc, ssn);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a SCCP User In Service message, essentially
 *      informing the SCCP layer that the sender needs services.
 *
 *  Input Parameters:
 *      handle - the transport associated with application
 *      orig - the SCCP address of the sender
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the SCCP address is decoded successfully and the SCCP message is
 *      sent successfully ITS_SUCCESS is returned. Any other return code
 *      indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The function will decode the SCCP address to get the originating
 *      point code and the subsytem number of the sender. The opc and
 *      the ssn are necessary for sending the SCCP message.
 *
 *  See Also:
 ****************************************************************************/
int
sendUserInService(ITS_HANDLE handle, SCCP_ADDR orig)
{
    ITS_OCTET gttInfo[50];
    ITS_USHORT gttLen;
    ITS_OCTET ssn, addrInd = 0;
    ITS_UINT opc = 0;
    int result = 0;

    printf("\n In sendUserInService()");

    /* We are not interested in getting the Global Title */
    result = SCCP_DecodeAddr(&orig, &addrInd, &opc, &ssn, gttInfo, &gttLen);
    printf("\n result = %d", result);

    if (result == ITS_SUCCESS)
    {
        /* SCCP Address decoded successfully */
        printf("\n       SCCP_Address successfully decoded");
        printf("\n");

        /* Print out the SSCP Address values */
        printf("\n       Address Indicator: %x", addrInd);
        printf("\n                     opc: %x", opc);
        printf("\n                     ssn: %x", ssn);
    }
    else
    {
        /* Failed to decode the address, print the error */
        printf("\n Failed to decode SCCP_Address.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
        return result;
    }

    /* Send an SCCP User Out of service message */
    return SCCP_SendUserInService(handle, opc, ssn);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will ask the user for a [y]es or [n]o.
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
 *      1 - if the user selected 'y'
 *      0 - if the user selected 'n'
 *
 *  Notes:
 *      This function will go into an infinite loop until the user selects
 *      a 'y' or an 'n'.
 *
 *  See Also:
 ****************************************************************************/
int
getYesOrNo()
{
    char response;

    fflush(stdin);
    response = getchar();

    while(response != 'y' && response != 'n')
    {
        printf("\nEnter either a 'y' or a 'n' -> ");
        response = getchar();
    }

    if (response == 'y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will ask a user to enter a number within a given range.
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
 *      SCCP User In Service is not implemented in the alpha release.
 *
 *  See Also:
 ****************************************************************************/
int
getSelection (int startRange, int endRange)
{
    int selection = 0;
    
    fflush(stdin);
    printf("\n Enter your selection -> ");
    scanf("%d", &selection);
       
    while ((selection < startRange) || (selection > endRange))
    {
        fflush(stdin);
        printf("\n Incorrect Selection (range is: %d to %d) -> ", startRange,
               endRange);
        scanf("%d", &selection);
    }
    return selection;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display dialogue information for any dialog type.
 *      
 *  Input Parameters:
 *      header - a pointer to the context for this dialogue
 *      dlg - pointer to a dialog of any type
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
traceDialogue(ITS_HDR *header, TCAP_DLG *dlg)
{
    /* Dialogue type */
    printf("\n");
    printf("\n Dialogue Printout");
    printf("\n ---------------------------------");
    printf("\n       Dialogue Type: ");
    traceDialogueType(dlg);

    /* Dialog ID */
    printf("\n           Dialog ID: 0x%x", header->context.dialogue_id);

    /* Determine dialog type and print dialog type specific information */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        traceUniDlg(dlg);
        break;

    case TCPPT_TC_BEGIN:
        traceBeginDlg(dlg);
        break;

    case TCPPT_TC_CONTINUE:
        traceContinueDlg(dlg);
        break;

    case TCPPT_TC_END:
        traceEndDlg(dlg);
        break;

    case TCPPT_TC_U_ABORT:
        traceAbortDlg(dlg);
        break;

    case TCPPT_TC_P_ABORT:
        traceAbortDlg(dlg);
        break;

    case TCPPT_TC_NOTICE:
        /* Not in this release */
        break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will  return a string representation of the dialog type.
 *      
 *  Input Parameters:
 *      dlg - pointer a dialog of any type
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
traceDialogueType(TCAP_DLG *dlg)
{
    /* Determine dialog type */
    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        printf("Unidirectional");
        break;

    case TCPPT_TC_BEGIN:
        printf("Begin");
        break;

    case TCPPT_TC_CONTINUE:
        printf("Continue");
        break;

    case TCPPT_TC_END:
        printf("End");
        break;

    case TCPPT_TC_U_ABORT:
        printf("User Abort");
        break;

    case TCPPT_TC_P_ABORT:
        printf("Provider Abort");
        break;

    case TCPPT_TC_NOTICE:
        printf("Notice");
        break;

    default:
        printf("Not Recognized!");
        break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out Begin dialog specific information.
 *      
 *  Input Parameters:
 *      dlg - pointer to a Begin dialog
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
 *      dlg must be a pointer to a Begin dialog, other wise the function will
 *      print out garbage.
 *
 *  See Also:
 ****************************************************************************/
void
traceBeginDlg(TCAP_DLG *dlg)
{
    int i;

    /* Component present */
    printf("\n   Component Present: 0x%x", dlg->u.begin.cpt_present);

    /* Quality of Service indicator */
    printf("\n       QOS Indicator: 0x%x", dlg->u.begin.qos.indicator);

    /* Originating Point Code */
    printf("\n                 OPC: 0x%x", dlg->u.begin.opc);

    /* Destination Point Code */
    printf("\n                 DPC: 0x%x", dlg->u.begin.dpc);
    printf("\n");

    /* Application Context Name */
    printf("\n             AC Name: ");
    for (i = 0; i < dlg->u.begin.ac_name.len; i++)
    {
        printf("0x%x ", dlg->u.begin.ac_name.data[i]);
    }

    /* User Info */
    printf("\n           User Info: ");
    for (i = 0; i < dlg->u.begin.user_info.len; i++)
    {
        printf("0x%x ", dlg->u.begin.user_info.data[i]);
    }
    printf("\n");

    /* Originating address */
    printf("\n Originating Address");
    printf("\n -------------------");
    printf("\n      Address Length: 0x%x", dlg->u.begin.orig_addr.len);
    printf("\n             Address: ");
    for (i = 0; i < dlg->u.begin.orig_addr.len; i++)
    {
        printf("0x%2x ", dlg->u.begin.orig_addr.data[i]);
    }
    printf("\n");

    /* Destination address */
    printf("\n Destination Address");
    printf("\n -------------------");
    printf("\n      Address Length: 0x%x", dlg->u.begin.dest_addr.len);
    printf("\n             Address: ");
    for (i = 0; i < dlg->u.begin.dest_addr.len; i++)
    {
        printf("0x%2x ", dlg->u.begin.dest_addr.data[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out Abort dialog specific information.
 *      
 *  Input Parameters:
 *      dlg - pointer to an Abort dialog
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
 *      dlg must be a pointer to a Abort dialog, other wise the function will
 *      print out garbage.
 *
 *  See Also:
 ****************************************************************************/
void
traceAbortDlg(TCAP_DLG *dlg)
{
    /* Abort reason */
    printf("\n        Abort Reason: 0x%x, ", dlg->u.abort.abort_reason);
    
    /* Print text representation of abort reason */
    switch (dlg->u.abort.abort_reason)
    {
    case TCPUABT_AC_NOT_SUP:
        printf("Application context not supported");
        break;

    case TCPUABT_USER_DEFINED:
        printf("User defined reason");
        break;

    default:
        printf("Reason does not match any predefined reasons.");
        break;
    }

    /* QOS indicator */
    printf("\n       QOS Indicator: 0x%x", dlg->u.abort.qos.indicator);

    /* ac_name */
    /* user_info */

    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print Continue dialog specific information.
 *      
 *  Input Parameters:
 *      dlg - pointer to a Continue dialog
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
 *      dlg must be a pointer to a Continue dialog, other wise the function will
 *      print out garbage.
 *
 *  See Also:
 ****************************************************************************/
void traceContinueDlg(TCAP_DLG *dlg)
{
    int i;

    /* Component present */
    printf("\n   Component Present: 0x%x", dlg->u.cont.cpt_present);

    /* QOS indicator */
    printf("\n       QOS Indicator: %d", dlg->u.cont.qos.indicator);
    printf("\n");

    /* Application Context Name */
    printf("\n             AC Name: ");
    for (i = 0; i < dlg->u.cont.ac_name.len; i++)
    {
        printf("0x%x ", dlg->u.cont.ac_name.data[i]);
    }

    /* User Info */
    printf("\n           User Info: ");
    for (i = 0; i < dlg->u.cont.user_info.len; i++)
    {
        printf("0x%x ", dlg->u.cont.user_info.data[i]);
    }
    printf("\n");

    /* orig_addr */
#if 0
    /* Display Originating address */
    printf("\n Originating Address");
    printf("\n -------------------");
    printf("\n      Address Length: 0x%x", dlg->u.cont.orig_addr.len);
    printf("\n             Address: ");
    for (i = 0; i < dlg->u.cont.orig_addr.len; i++)
    {
        printf("0x%2x ", dlg->u.cont.orig_addr.data[i]);
    }
    printf("\n");
#endif
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print End dialog specific information.
 *      
 *  Input Parameters:
 *      dlg - pointer to an End dialog
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
 *      dlg must be a pointer to a End dialog, other wise the function will
 *      print out garbage.
 *
 *  See Also:
 ****************************************************************************/
void
traceEndDlg(TCAP_DLG *dlg)
{
    int i;

    /* Component present */
    printf("\n   Component Present: 0x%x", dlg->u.end.cpt_present);

    /* Quality Of Service indicator */
    printf("\n       QOS Indicator: %d", dlg->u.end.qos.indicator);

    /* Application Context Name */
    printf("\n             AC Name: ");
    for (i = 0; i < dlg->u.end.ac_name.len; i++)
    {
        printf("0x%x ", dlg->u.end.ac_name.data[i]);
    }

    /* User Info */
    printf("\n           User Info: ");
    for (i = 0; i < dlg->u.end.user_info.len; i++)
    {
        printf("0x%x ", dlg->u.end.user_info.data[i]);
    }

    /* Termination */
    printf("\n         Termination: 0x%x, ", dlg->u.end.termination);

    /* Print text representation of termination parameter */
    switch (dlg->u.end.termination)
    {
    case TCPEND_PREARRANGED:
        printf("Prearranged End");
        break;

    case TCPEND_BASIC:
        printf("Basic End");
        break;

    default:
        printf("Unrecognized termination value");
        break;
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print End dialog specific information.
 *      
 *  Input Parameters:
 *      dlg - pointer to an End dialog
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
 *      dlg must be a pointer to a End dialog, other wise the function will
 *      print out garbage.
 *
 *  See Also:
 ****************************************************************************/
void
traceUniDlg(TCAP_DLG *dlg)
{
    int i;

    /* Component present */
    printf("\n   Component Present: 0x%x, ", dlg->u.uni.cpt_present);
    switch (dlg->u.uni.cpt_present)
    {
    case TCP_CPT_PRESENT:
        printf("TCP_CPT_PRESENT");
        break;
    
    case TCP_NO_CPT:
        printf("TCP_NO_CPT");
        break;
   
    default:
        printf("Unrecogniged tag");
        break;    
    }

    /* Quality of Service indicator */
    printf("\n       QOS Indicator: 0x%x", dlg->u.uni.qos.indicator);

    /* Originating Point Code */
    printf("\n                 OPC: 0x%x", dlg->u.uni.opc);

    /* Destination Point Code */
    printf("\n                 DPC: 0x%x", dlg->u.uni.dpc);
    printf("\n");

    /* Application Context Name */
    printf("\n             AC Name: ");
    for (i = 0; i < dlg->u.uni.ac_name.len; i++)
    {
        printf("0x%x ", dlg->u.uni.ac_name.data[i]);
    }

    /* User Info */
    printf("\n           User Info: ");
    for (i = 0; i < dlg->u.uni.user_info.len; i++)
    {
        printf("0x%x ", dlg->u.uni.user_info.data[i]);
    }
    
    /* Originating address */
    printf("\n Originating Address");
    printf("\n -------------------");
    printf("\n      Address Length: 0x%x", dlg->u.uni.orig_addr.len);
    printf("\n             Address: ");
    for (i = 0; i < dlg->u.uni.orig_addr.len; i++)
    {
        printf("0x%2x ", dlg->u.uni.orig_addr.data[i]);
    }
    printf("\n");

    /* Destination address */
    printf("\n Destination Address");
    printf("\n -------------------");
    printf("\n      Address Length: 0x%x", dlg->u.uni.dest_addr.len);
    printf("\n             Address: ");
    for (i = 0; i < dlg->u.uni.dest_addr.len; i++)
    {
        printf("0x%2x ", dlg->u.uni.dest_addr.data[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print a string representation of the component
 *      type.
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
traceComponentType(TCAP_CPT *cpt)
{
    switch (cpt->ptype)
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
        printf("\n Component Type: 0x%x, L_CANCEL", cpt->ptype);
        break; 

    case TCPPT_TC_U_CANCEL:
        printf("\n Component Type: 0x%x, U_CANCEL", cpt->ptype);
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
        printf("\n Component Type: 0x%x, Unrecognized component",
               cpt->ptype);
        break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for any component type.
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
traceComponent(ITS_HDR *header, TCAP_CPT *cpt)
{
    printf("\n TCAP_Component Information");
    printf("\n --------------------------");

    /* Determine component type */
    switch (cpt->ptype)
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
        printf("\n Unrecognized Component Type!");
    }

    /* Print if this component is the last component or not */
    printf("\n Last Component: 0x%x, ", cpt->last_component);
    switch (cpt->last_component)
    {
    case TCP_MORE_CPTS:
        printf("More components");
        break;

    case TCP_LAST_CPT:
        printf("Last component");
        break;

    default:
        printf("Invalid value for cpt->last_component");
        break;
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for a Cancel component.
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
 *      cpt must be a pointer to a Cancel component to print relevant
 *      information.
 *
 *  See Also:
 ****************************************************************************/
void
traceCancelCpt(TCAP_CPT *cpt)
{
    int i;

    printf("\n Component Type: 0x%x, ", cpt->ptype);

    /* Determine type of Cancel component */
    switch (cpt->ptype)
    {
    case TCPPT_TC_L_CANCEL:
        printf("L_CANCEL");
        break;

    case TCPPT_TC_U_CANCEL:
        printf("U_CANCEL");
        break;
    }

    /* Invoke ID */
    printf("\n      Invoke ID: ");
    for (i=0; i < cpt->u.cancel.invoke_id.len; i++)
    {
        printf("0x%x ", cpt->u.cancel.invoke_id.data[i]);
    } 
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for a Invoke component.
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
 *      cpt must be a pointer to a Invoke component to print relevant
 *      information.
 *
 *  See Also:
 ****************************************************************************/
void
traceInvokeCpt(TCAP_CPT *cpt)
{
    int i = 0, a = 0;
    int err = 0;
    int len = 0;
    int result = 0;

    /* Component type */
    printf("\n   Component Type: 0x%x, TC_INVOKE", cpt->ptype);

    /* Last component */
    printf("\n   Last Component: 0x%x", cpt->last_component);

    /* Invoke ID */
    printf("\n    Invoke ID Len: 0x%x", cpt->u.invoke.invoke_id.len);
    printf("\n        Invoke ID: ");
    for (i = 0; i < cpt->u.invoke.invoke_id.len; ++i)
    {
        printf("0x%x ", cpt->u.invoke.invoke_id.data[i]);
    }

    /* Operation */
    printf("\n Operation Length: 0x%x", cpt->u.invoke.operation.len);
    printf("\n        Operation: ");
    for (i = 0; i < cpt->u.invoke.operation.len; i ++)
    {
        printf("0x%x ", cpt->u.invoke.operation.data[i]);
    }
    /* Determine which INAP Message was received */
    printf("\n   INAP Procedure: ");
    switch(cpt->u.invoke.operation.data[2])
    {
    case INAP_OP_callGap:
        printf("CallGap");
        break;
    case INAP_OP_continue:
        printf("Continue");
        break;
    case INAP_OP_callInformationReport:
        printf("CallInformationReport");
        break;
    case INAP_OP_callInformationRequest:
        printf("CallInformationRequest");
        break;
    case INAP_OP_cancelStatusReportRequest:
        printf("CancelStatusReportRequest");
        break;
    case INAP_OP_connect:
        printf("Connect");
        break;
    case INAP_OP_eventReportBCSM:
        printf("EventReportBCSM");
        break;
    case INAP_OP_initialDP:
        printf("InitialDP");
        break;
    case INAP_OP_releaseCall:
        printf("ReleaseCall");
        break;
    case INAP_OP_requestCurrentStatusReport:
        printf("RequestCurrentStatusReport");
        break;
    case INAP_OP_requestCurrentStatusReportResult:
        printf("RequestCurrentStatusReportResult");
        break;
    case INAP_OP_requestEveryStatusChangeReport:
        printf("RequestEveryStatusChangeReport");
        break;
    case INAP_OP_requestFirstStatusMatchReport:
        printf("RequestFirstStatusMatchReport");
        break;
    case INAP_OP_requestReportBCSMEvent:
        printf("RequestReportBCSMEvent");
        break;
    case INAP_OP_statusReport:
        printf("StatusReport");
        break;
    default:
        printf("Unrecognized procedure or not included in this demo.");
        break;
    }

    /* Operation class */
    printf("\n         Op Class: 0x%x", cpt->u.invoke.opClass);

    /* Timeout */
    printf("\n          Timeout: 0x%x", cpt->u.invoke.timeout);

    /* Link ID */
    printf("\n        Linked ID: 0x%x", cpt->u.invoke.linked_id.data[2]);

    /*
     * Display parameter(encoded value of the INAP message structure) for this
     * component
     */
    printf("\n    Parameter Len: 0x%x", cpt->u.result.param.len);
    printf("\n        Parameter: ");
    printf("\n");
    for (i = 0; i < cpt->u.result.param.len; i++)
    {
        printf("0x%2x ", cpt->u.result.param.data[i]);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for a Reject component.
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
 *      cpt must be a pointer to a Reject component to print relevant
 *      information.
 *
 *  See Also:
 ****************************************************************************/
void
traceRejectCpt(TCAP_CPT *cpt)
{
    /* Display hex & text representation of Component type */
    printf("\n     Component Type: 0x%x, ", cpt->ptype);
    switch (cpt->ptype)
    {
    case TCPPT_TC_L_REJECT:
        printf("TC_L_REJECT");
        break;

    case TCPPT_TC_R_REJECT:
        printf("TC_R_REJECT");
        break;
    
    case TCPPT_TC_U_REJECT:
        printf("TC_U_REJECT");
        break;
    }

    /* Last component */
    printf("\n     Last Component: 0x%x", cpt->last_component);

    /* Problem length */
    printf("\n     Problem Length: 0x%x", cpt->u.reject.problem.len);

    /* Problem type */
    printf("\n       Problem Type: 0x%x", cpt->u.reject.problem.data[0]);

    /* Problem identifier flag */
    printf("\n Problem Ident Flag: 0x%x", cpt->u.reject.problem.data[1]);

    /* Problem identifier */
    printf("\n Problem Identifier: 0x%x", cpt->u.reject.problem.data[2]);
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for a Result component.
 *      
 *  Input Parameters:
 *      cpt - pointer to a Result component
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
 *      cpt must be a pointer to a Result component to print relevant
 *      information.
 *
 *  See Also:
 ****************************************************************************/
void
traceResultCpt(TCAP_CPT *cpt)
{
    int i;

    /* Display text representation of Component type */
    printf("\n Component Type: 0x%x, ", cpt->ptype);
    if (cpt->ptype == TCPPT_TC_RESULT_L)
    {
        printf("TC_RESULT_L");
    }
    else
    {
        printf("TC_RESULT_NL");
    }

    /* Last component */
    printf("\n   Last Component: 0x%x", cpt->last_component);

    /* Invoke ID */
    printf("\n    Invoke ID Len: 0x%x", cpt->u.result.invoke_id.len);
    printf("\n        Invoke ID: ");
    for(i = 0; i < cpt->u.result.invoke_id.len; i++)
    {
        printf("0x%x ",cpt->u.result.invoke_id.data[i]);
    }

    /* Operation */
    printf("\n        Operation: 0x%x, ", cpt->u.result.operation.data[2]);

    /* Determine which INAP Message was received */
    switch(cpt->u.invoke.operation.data[2])
    {
    case INAP_OP_callGap:
        printf("CallGap");
        break;

    case INAP_OP_callInformationReport:
        printf("CallInformationReport");
        break;

    case INAP_OP_callInformationRequest:
        printf("CallInformationRequest");
        break;

    case INAP_OP_cancelStatusReportRequest:
        printf("CancelStatusReportRequest");
        break;

    case INAP_OP_connect:
        printf("Connect");
        break;

    case INAP_OP_eventReportBCSM:
        printf("EventReportBCSM");
        break;

    case INAP_OP_initialDP:
        printf("InitialDP");
        break;

    case INAP_OP_requestCurrentStatusReport:
        printf("RequestCurrentStatusReport");
        break;
    
    case INAP_OP_requestCurrentStatusReportResult:
        printf("RequestCurrentStatusReportResult");
        break;

    case INAP_OP_requestEveryStatusChangeReport:
        printf("RequestEveryStatusChangeReport");
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        printf("RequestFirstStatusMatchReport");
        break;

    case INAP_OP_requestReportBCSMEvent:
        printf("RequestReportBCSMEvent");
        break;

    case INAP_OP_statusReport:
        printf("StatusReport");
        break;

    default:
        printf("Unrecognized procedure or not included in this demo.");
        break;
    }

    /* Parameter */
    printf("\n  Parameter Len: 0x%x", cpt->u.result.param.len);
    printf("\n      Parameter: ");
    for (i = 0; i < cpt->u.result.param.len; i++)
    {
        printf("0x%x ", cpt->u.result.param.data[i]);
    }
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print out information for a Error component.
 *      
 *  Input Parameters:
 *      cpt - pointer to an Error component
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
 *      cpt must be a pointer to a Error component to print relevant
 *      information.
 *
 *  See Also:
 ****************************************************************************/
void
traceErrorCpt(TCAP_CPT *cpt)
{
    int i;

    /* Text representation of Component type */
    printf("\n    Component Type: 0x%x, TC_U_ERROR", cpt->ptype);

    /* Error total length */
    printf("\n      Total Length: 0x%x", cpt->u.error.error.len);

    /* Error tag */
    printf("\n         Error Tag: 0x%x", cpt->u.error.error.data[0]);

    /* Error length */
    printf("\n Error code length: 0x%x", cpt->u.error.error.data[1]);

    /* Error Code */
    printf("\n        Error Code: 0x%x", cpt->u.error.error.data[2]);
  
    /* Parameter Length */
    printf("\n  Parameter Length: %d", cpt->u.error.param.len);
    printf("\n         Parameter: "); 
    for (i = 0; i < cpt->u.error.param.len; i++)
    {
        printf("0x%x ", cpt->u.error.param.data[i]);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }  
    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will print an menu for sending INAP invokes.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      cpt - pointer to an invoke component
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the INAP invoke and the dialog are sent successfully ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SelectINAPMessageToSend(ITS_HANDLE handle, ITS_HDR header, TCAP_CPT *cpt)
{
    int result = 0;
    int choice = 0;

    /* Display INAP Message menu */
    SendINAPMessageMenu();

    scanf("%d", &choice);

    /* Determine which INAP Message the user selected to send */
    switch (choice)
    {
    case INAP_OP_callGap:
        /* Send CallGapArg */
        printf("\n");
        printf("\n CallGapArg");
        printf("\n ----------------------------------");
        result = sendCallGapArg(handle, &header, cpt);
        break;

    case INAP_OP_callInformationRequest:
        /* Send CallInformationRequestArg */
        printf("\n");
        printf("\n CallInformationRequestArg");
        printf("\n ----------------------------------");
        result = sendCallInformationRequestArg(handle, &header, cpt);
        break;

    case INAP_OP_cancelStatusReportRequest:
        /* Send CancelStatusReportRequestArg */
        printf("\n");
        printf("\n CancelStatusReportRequestArg");
        printf("\n ----------------------------------");
        result = sendCancelStatusReportRequestArg(handle, &header, cpt);
        break;

    case INAP_OP_connect:
        /* Send ConnectArg */
        printf("\n");
        printf("\n ConnectArg");
        printf("\n ----------------------------------");
        result = sendConnectArg(handle, &header, cpt);
        break;

    case INAP_OP_initialDP:
        /* Send InitialDPArg */
        printf("\n");
        printf("\n InitialDPArg");
        printf("\n ----------------------------------");
        result = sendInitialDPArg(handle, &header, cpt);
        break;

    case INAP_OP_requestCurrentStatusReport:
        /* Send RequestCurrentStatusReportArg */
        printf("\n");
        printf("\n RequestCurrentStatusReportArg");
        printf("\n ----------------------------------");
        result = sendRequestCurrentStatusReportArg(handle, &header, cpt);
        break;


    case INAP_OP_requestEveryStatusChangeReport:
        /* Send RequestEveryStatusChangeReportArg */
        printf("\n");
        printf("\n RequestEveryStatusChangeReportArg");
        printf("\n ----------------------------------");
        result = sendRequestEveryStatusChangeReportArg(handle, &header, cpt);
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        /* Send RequestFirstStatusMatchReportArg */
        printf("\n");
        printf("\n RequestFirstStatusMatchReportArg");
        printf("\n ----------------------------------");
        result = sendRequestFirstStatusMatchReportArg(handle, &header, cpt);
        break;

    case INAP_OP_requestReportBCSMEvent:
        /* Send RequestReportBCSMEventArg */
        printf("\n");
        printf("\n RequestReportBCSMEventArg");
        printf("\n ----------------------------------");
        result = sendRequestReportBCSMEventArg(handle, &header, cpt);
        break;

    default:
        /* bad selection default to InitialDPArg */
        printf("\n User selected an invalid choice.");
        printf("\n");
        break;
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will wait for an ITS Event. TCAP dialogs and components
 *      are received using this function.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      recvHeader - pointer to a copy of the header from the received dialog
 *      recvComponent - pointer to the received component
 *
 *  Return Value:
 *      If the no problems were encountered in getting the dialog or
 *      the component, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
waitForEvent(ITS_HANDLE handle, ITS_HDR *recvHeader, TCAP_CPT *recvComponent)
{
    int result = 0;
    int keepGoing = 1;
    int invRespType = 0;
    int begRespType = 0;
    int noResponse = 0;
    ITS_USHORT did_Dialog = 0;
    ITS_USHORT did_Component = 0;
    ITS_HDR header;
    TCAP_DLG dlg;
    ITS_EVENT event;

    /* Initializations */
    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&dlg, 0, sizeof(TCAP_DLG));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    /* Keep getting an Event */
    while (keepGoing)
    {
        /* Wait for an Event */
        printf("\n");
        printf("\n Waiting For an ITS Event");
        printf("\n ------------------------");
        printf("\n");

        /*
         * Get the next event if there is an event otherwise block until an
         * event is received
         */
        result = ITS_GetNextEvent(handle, &event);
        if (result == ITS_SUCCESS)
        {
            /* Check if we received a TCAP Event */
            if (event.src == ITS_TCAP_SRC)
            {
                /* Check if a TCAP dialogue was received */
                printf("\n Recevied a TCAP event");
                if (event.data[0] == ITS_TCAP_DLG)
                {
                    /* Received a dialogue */
                    printf("\n Received a TCAP Dialogue, going to get it");
                    result = TCAP_ReceiveDialogue(handle, &event, &header,
                                                  &dlg);
                    printf("\n result = %d", result);

                    /* Copy the dialog ID of transaction */
                    recvHeader->context.dialogue_id =
                        header.context.dialogue_id;

                    /* Check if the dialog was received successfully */
                    if (result == ITS_SUCCESS)
                    {
                        /* storing the Dialogue Id */
                        did_Dialog = header.context.dialogue_id;

                        /* Print the received Dialogue information */
                        traceDialogue(&header, &dlg);

                        /* Determine which type of dialog was received */
                        switch (dlg.ptype)
                        {
                        case TCPPT_TC_BEGIN:
                            /* Received a Begin dialog */
                            printf("\n TCAP Begin dialog received.");

                            /* Check if component is present */
                            if (dlg.u.begin.cpt_present == TCP_NO_CPT)
                            {
                                /*
                                 * Stop waiting for Event if no 
                                 * component is present
                                 */    
                                keepGoing = 0;
                            } 
                            break;

                        case TCPPT_TC_CONTINUE:
                            /* Received an Continue dialog */
                            printf("\n TCAP Continue dialog received.");
                            break;

                        case TCPPT_TC_END:
                            /* Received an End dialog */
                            printf("\n TCAP End dialog received.");

                            /*
                             * Check if the dialog has no component, if true
                             * then this while loop will end
                             */
                            if (dlg.u.end.cpt_present == TCP_NO_CPT)
                            {
                               keepGoing = 0;
                            }
                            break;

                        case TCPPT_TC_NOTICE:
                            /* Received a Notice dialog */
                            printf("\n TCAP Notice dialog received.");
                            break;

                        case TCPPT_TC_P_ABORT:
                            /* Received a Provider Abort dialog */
                            printf("\n TCAP Provider Abort dialog received.");

                            /* Stop waiting for an event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_U_ABORT:
                            /* Received a User Abort dialog */
                            printf("\n TCAP User Abort dialog received.");

                            /* Stop waiting for an event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_UNI:
                            /* Received a Unidirectional dialog */
                            printf("\n TCAP Unidirectional dialog received.");

                            /* Stop waiting for an event */
                            keepGoing = 0;
                            break;

                        default:
                            /* Received an unrecognized dialog */
                            printf("\n Unrecognized dialogue with type: 0x%x",
                                   dlg.ptype);
                        }
                    }
                    else
                    {
                        /* Failed to get TCAP dialogue. Print the error */
                        printf("\n Failed to get the TCAP dialog.");
                        printf("\n Error: %s.", ITS_GetErrorText(result));
                        printf("\n");
                    }
                }
                else if (event.data[0] == ITS_TCAP_CPT)
                {
                    /* Receive a TCAP Component */
                    printf("\n Received a TCAP component, going to get it");
                    result = TCAP_ReceiveComponent(handle, &event, &header,
                                                   recvComponent);
                    printf("\n result = %d", result);

                    /* Check if component was received successfully */
                    if (result == ITS_SUCCESS)
                    {
                        /* Display component information */
                        traceComponent(&header, recvComponent);

                        /*
                         * Check if component received is the last one.
                         * If so, exit the while loop
                         */
                        if (recvComponent->last_component == TCP_LAST_CPT)
                        {
                            printf("\n Received last component.");
                            keepGoing = 0;
                        }

                        /* Determine which component type was received */
                        switch (recvComponent->ptype)
                        {
                        case TCPPT_TC_INVOKE:
                            /* storing the Dialogue Id */
                            did_Component = header.context.dialogue_id;

                            /* Decode the parameter field of the invoke */
                            decodeINAPMessage(handle, recvComponent);

                            /*
                             * Check if the dialogID and the invokeID
                             * do not match.
                             */
                            if (did_Dialog != did_Component)
                            {
                                /*
                                 * The dialog ID of the dialog do not match
                                 * the dialogID stored in the component
                                 */
                                printf("\n DialogueIDs do not match... "); 
                            }
                            break;

                        case TCPPT_TC_RESULT_L:
                            /* Received a TCAP Result Last component */
                            printf("\n Received a Result Last component.");

                            /* Decode the parameter field of the result */
                            decodeINAPMessage(handle, recvComponent);

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_RESULT_NL:
                            /* Received a Result Not Last component */
                            printf("\n Received a Result Not Last component.");
                            break;

                        case TCPPT_TC_U_ERROR:
                            /* Received a User Error component */
                            printf("\n Received a User Error component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_L_CANCEL:
                            /* Received a Local Cancel Component */
                            printf("\n Received a Local Cancel component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_U_CANCEL:
                            /* Received a User cancel component */
                            printf("\n Received a User Cancel component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_L_REJECT:
                            /* Received a Local Reject component */
                            printf("\n Received a Local Reject component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;

                        case TCPPT_TC_R_REJECT:
                            /* Received a Remote Reject component */
                            printf("\n Received a Remote Reject component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;
                        
                        case TCPPT_TC_U_REJECT:
                            /* Received a User reject component */
                            printf("\n Received a User Reject component.");

                            /* Stop waiting for an ITS Event */
                            keepGoing = 0;
                            break;
                        
                        default:
                            /* Received an unrecognized component */
                            printf("\n Received an Unrecognized component."); 
                        }
                    }
                    else
                    {
                        /* Failed to get TCAP component */
                        printf("\n Failed to get the TCAP Component");
                        printf("\n Error: %s.", ITS_GetErrorText(result));
                        printf("\n");

                        /* Stop waiting for an ITS Event */
                        keepGoing = 0;
                        break;
                    }
                }
                else
                {
                    /* Wrong type of TCAP event was received */
                    printf("\n Received a TCAP event but wrong type");
                    printf("\n TCAP event is: 0x%x",
                           event.data[0]);

                    /* Stop waiting for an ITS Event */
                    keepGoing = 0;
                    break;
                }
            }
            else
            {
                /* Received a non TCAP event */
                printf("\n Received an event, but it is not from TCAP");
                printf("\n The source of the event is: 0x%x", event.src);

                /* Stop waiting for an ITS Event */
                keepGoing = 0;
                break;
            }
        }
        else
        {
            /* Failed to get next event */
            printf("\n GetNextEvent failed.");
            printf("\n Error: %s.", ITS_GetErrorText(result));
            printf("\n");

            /* Stop waiting for an ITS Event */
            keepGoing = 0;
            break;
        }
    }

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will create an IntelliSS7 handle for the Receive
 *      program.
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
 *      An ITS_HANDLE if a handle was created successfully. NULL if an error
 *      occured in creating the handle.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_HANDLE
initReceiveHandle() 
{
    int result = 0;
    ITS_HANDLE hdl;

    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****    IntelliSS7 INAP API Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n");

    printf("\n INAP C API  Receive Test Program.\n\n");

    /*
     * Setting the name of the application.
     * The name of the apllication is the name of the ITS .ini file
     * read by IntelliSS7
     */
    APPL_SetName("INAP_Test_Receive");

    /*
     * Initializing IntelliSS7: using the SS7 Transport (for TCAP)
     * and only one app. is using the transport. Instance = 2,
     * instance is used by the vendor code to read the .ini
     * file to configure the vendor's driver.
     */
    hdl = (ITS_HANDLE)ITS_Initialize(ITS_TCAP  |
                                     ITS_TRANSPORT_SS7 |
                                     ITS_TRANSPORT_SINGLE_USER,
                                     TEST_RECEIVE_INSTANCE);
    if (hdl == NULL)
    {
        printf("\n Not able to create an ITS_HANDLE, quiting...\n");
        exit(0);
    }
    
    printf("\n IntelliSS7 initialized with success");
    return hdl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will create an IntelliSS7 handle for the Send
 *      program.
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
 *      An ITS_HANDLE if a handle was created successfully. NULL if an error
 *      occured in creating the handle.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_HANDLE
initSendHandle() 
{
    int result = 0;
    ITS_HANDLE hdl;

    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****    IntelliSS7 INAP API Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n");

    printf("\n INAP C API  Send Test Program.\n\n");

    /*
     * Setting the name of the application.
     * The name of the apllication is the name of the ITS .ini file
     * read by IntelliSS7
     */
    APPL_SetName("INAP_Test_Send");

    /*
     * Initializing IntelliSS7: using the SS7 Transport (for TCAP)
     * and only one app. is using the transport. Instance = 1,
     * instance is used by the vendor code to read the .ini
     * file to configure the vendor's driver.
     */
    hdl = (ITS_HANDLE)ITS_Initialize(ITS_TCAP |
                                     ITS_TRANSPORT_SS7 |
                                     ITS_TRANSPORT_SINGLE_USER,
                                     TEST_SEND_INSTANCE);
    if (hdl == NULL)
    {
        printf("\n Not able to create an ITS_HANDLE, quiting...\n");
        exit(0);
    }
    
    printf("\n IntelliSS7 initialized with success");
    return hdl;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a TCAP Error component. The user is asked to
 *      provide an error code for the component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      invoke_id - a pointer to the invoke id of the component this Error
 *                  component is a response to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the Error component is sent successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPErrorCpt(ITS_HANDLE handle, ITS_HDR *header, CPT_INV_ID *invoke_id)
{
    int result = 0;
    int errorId = 0;
    int errorCode = 0;
    const char errorparam[4] = { 0x30, 0x31, 0x32, 0x00 };

    TCAP_CPT errorCpt;
    
    /* Initializations */
    memset((char *)&errorCpt, 0, sizeof(TCAP_CPT));

    /* setting and sending Return Error Component */
    errorCpt.ptype = TCPPT_TC_U_ERROR;
    errorCpt.last_component = TCP_LAST_CPT;

    /* grabbing the invoke ID from the incoming invoke */
    errorCpt.u.error.invoke_id.len = invoke_id->len;
    memcpy(errorCpt.u.error.invoke_id.data, invoke_id->data,
           invoke_id->len);

    /* Total Length = 3 */
    errorCpt.u.error.error.len = 3;

    /* Local Error Tag */
    errorCpt.u.error.error.data[0] = TCPPN_LOCAL_ERR_TAG;

    /* Error Code Length = 1 */ 
    errorCpt.u.error.error.data[1] = 1;

    /* ERROR TEST */
    errorCpt.u.error.param.len = strlen(errorparam); 
    memcpy(errorCpt.u.error.param.data, errorparam, strlen(errorparam));

    /* asking user to provide Error identifier and code */
    printf("\n Going to send a TCAP Return Error Component.");
    printf("\n");
    printf("\n Select Error Code:");
    printf("\n --------------------------------------------");
    printf("\n [%2d] Cancelled", INAP_ERR_cancelled);
    printf("\n [%2d] Cancel Failed", INAP_ERR_cancelFailed);
    printf("\n [%2d] eTCFailed", INAP_ERR_eTCFailed);
    printf("\n [%2d] Improper Caller Response",
           INAP_ERR_improperCallerResponse);
    printf("\n [%2d] Missing Customer Record",
           INAP_ERR_missingCustomerRecord);
    printf("\n [%2d] Missing Parameter", INAP_ERR_missingParameter);
    printf("\n [%2d] Parameter Out of Range", 
           INAP_ERR_parameterOutOfRange);
    printf("\n [%2d] Requested Info Error", INAP_ERR_requestedInfoError);
    printf("\n [%2d] System Failure", INAP_ERR_systemFailure);
    printf("\n [%2d] Task Refused", INAP_ERR_taskRefused);
    printf("\n [%2d] Unavailable Resource", INAP_ERR_unavailableResource);
    printf("\n [%2d] Unexpected Component Sequence",
           INAP_ERR_unexpectedComponentSequence);
    printf("\n [%2d] Unexpected Data Value", INAP_ERR_unexpectedDataValue);
    printf("\n [%2d] Unexpected Parameter", INAP_ERR_unexpectedParameter);
    printf("\n [%2d] Unknown Leg", INAP_ERR_unknownLegID);
    printf("\n [%2d] Unknown Resource", INAP_ERR_unknownResource);
    printf("\n");
    printf("\n -> ");
    scanf("%d", &errorCode);

    /* Set error code from user selection */
    errorCpt.u.error.error.data[2] = errorCode;

    /* Send the component */
    printf("\n Error Component Before send.");
    traceComponent(header, &errorCpt);

    result = TCAP_SendComponent(handle, header, &errorCpt);
    printf("\n result = %d", result);

    /* Check if component was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Component sent successfully */
        printf("\n Error Component send success.");
    }
    else
    {
        /* Failed to send User Error component */
        printf("\n WARNING: Cannot send Error component.");
        printf("\n result = %d", result);
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

 /*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a TCAP User Reject component. The user is asked
 *      to provide a problem type and a problem identifier for the User Reject
 *      component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      invoke_id - a pointer to the invoke id of the component this Reject
 *                  component is a response to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the User Reject component is sent successfully, ITS_SUCCESS is
 *      returned. Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPRejectCpt(ITS_HANDLE handle, ITS_HDR *header, CPT_INV_ID *invoke_id)
{
    int result = 0;
    int problemType = 0;
    int problemCode = 0;
    TCAP_CPT rejectCpt;

    /* Initialization */
    memset((char *)&rejectCpt, 0, sizeof(TCAP_CPT));

    /* Setting and sending Remote Reject Component */
    rejectCpt.ptype = TCPPT_TC_U_REJECT;
    rejectCpt.last_component = TCP_LAST_CPT;

    /* grabbing the invoke ID from the incoming invoke */
    rejectCpt.u.reject.invoke_id.len = invoke_id->len;
    memcpy(rejectCpt.u.reject.invoke_id.data, invoke_id->data,
           invoke_id->len);

    /* Set Reject problem parameters */
    rejectCpt.u.reject.problem.len = 3;
    rejectCpt.u.reject.problem.data[1] = 1;

    /* Asking user to provide  problem type */
    printf("\n Going to send a TCAP Reject Component, select problem type:");
    printf("\n -----------------------------------------------------------");
    printf("\n [%2d] General", TCPPROB_GENERAL);
    printf("\n [%2d] Invoke", TCPPROB_INVOKE);
    printf("\n [%2d] Return Result", TCPPROB_RETURN_RES);
    printf("\n [%2d] Return Error", TCPPROB_RETURN_ERR);
    printf("\n");
    printf("\n -> ");
    scanf("%d", &problemType);
    
    /* Setting problem type as selected by the user */
    rejectCpt.u.reject.problem.data[0] = problemType;
    
    /* Asking user for problem identifier */
    printf("\n");
    printf("\n Select problem identifier:");
    printf("\n --------------------------");
    switch (problemType)
    {
    case TCPPROB_GENERAL:
        printf("\n [%2d] Unrecognized Component",
               TCPPROB_SPEC_GEN_UNREC_COMP);
        printf("\n [%2d] Incorrect Component Portion",
               TCPPROB_SPEC_GEN_MISTYPED_COMP);
        printf("\n [%2d] Badly Structured Component",
               TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        break;

    case TCPPROB_INVOKE:
        printf("\n [%2d] Duplicate Invoke ID",
               TCPPROB_SPEC_INV_DUPLICATE_INV_ID);
        printf("\n [%2d] Unrecognized Operation",
               TCPPROB_SPEC_INV_UNREC_OP_CODE);
        printf("\n [%2d] Incorrect Parameter",
               TCPPROB_SPEC_INV_MISTYPED_PARAM);
        printf("\n [%2d] Resource Limit",
               TCPPROB_SPEC_INV_RESOURCE_LIMIT);
        printf("\n [%2d] Related Dialog About to be Released",
               TCPPROB_SPEC_INV_INITIATE_RELEASE);
        printf("\n [%2d] Unrecognized Link ID",
               TCPPROB_SPEC_INV_UNREC_LINKED_ID);
        printf("\n [%2d] Unexpected Link Response",
               TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP);
        printf("\n [%2d] Unexpected Link Operation",
               TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP);
        break;

    case TCPPROB_RETURN_RES:
        printf("\n [%2d] Unrecognized Invoke ID",
               TCPPROB_SPEC_RES_UNREC_INVOKE_ID);
        printf("\n [%2d] Enexpected Return Result",
               TCPPROB_SPEC_RES_UNEXPECTED_RET_RES);
        printf("\n [%2d] Mistyped Parameter",
               TCPPROB_SPEC_RES_MISTYPED_PARAM);
        break;

    case TCPPROB_RETURN_ERR:
        printf("\n [%2d] Unrecognized Link ID",
               TCPPROB_SPEC_ERR_UNREC_INVOKE_ID);
        printf("\n [%2d] Unexpected Return Error",
               TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR);
        printf("\n [%2d] Unrecognized Error",
               TCPPROB_SPEC_ERR_UNREC_ERROR);
        printf("\n [%2d] Unexpected Error",
               TCPPROB_SPEC_ERR_UNEXPECTED_ERROR);
        printf("\n [%2d] Mistyped Parameter",
               TCPPROB_SPEC_ERR_MISTYPED_PARAM);
        break;
    }
    printf("\n -> ");
    scanf("%d", &problemCode);

    /* Setting pronblem identifier from user selection */
    rejectCpt.u.reject.problem.data[2] = problemCode;

    /* Print component informationn before sending */
    printf("\n Reject Component before send.");
    traceComponent(header, &rejectCpt);

    /* Send the component */
    result = TCAP_SendComponent(handle, header, &rejectCpt);
    printf("\n result = %d", result);

    /* Check if the component was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Component sent successfully */
        printf("\n Reject Component send success.");
    }
    else
    {
        /* Failed to send component, printing error */
        printf("\n WARNING: Cannot send Reject component.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a TCAP Result component.
 *
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component this Result component is
 *                a response to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the Result component is sent successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
sendTCAPResultCpt(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt)
{
    int result = 0;
    int code = 0;
    const char resultParam[6] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x00 };
    TCAP_CPT resultCpt;

    /* initialize component structure */
    memset((char *)&resultCpt, 0, sizeof(TCAP_CPT));

    printf("\n Sending a Result Component.");

    /* grabbing the invoke ID from the incoming invoke */
    resultCpt.u.result.invoke_id.len = recvCpt->u.invoke.invoke_id.len;
    memcpy(resultCpt.u.result.invoke_id.data, recvCpt->u.invoke.invoke_id.data,
           recvCpt->u.invoke.invoke_id.len);

    /* Set Result component parameters */

    /* Setting component type to Result Last */
    resultCpt.ptype = TCPPT_TC_RESULT_L;
    resultCpt.last_component = TCP_LAST_CPT;

    /* Operation total length */
    /* resultCpt.u.result.operation.len = 3; */
    resultCpt.u.result.operation.len = 0;

    /* Local result tag */
    resultCpt.u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;

    /* Result code length */
    resultCpt.u.result.operation.data[1] = 1;
    resultCpt.u.result.operation.data[2] = INAP_OP_requestCurrentStatusReportResult;

    /* Parameter */
    resultCpt.u.result.param.len = strlen(resultParam);
    memcpy(resultCpt.u.result.param.data, resultParam, strlen(resultParam));

    /* Print component information before sending */
    printf("\n Result Component before send.");
    traceComponent(header, &resultCpt);

    /* Send the component */
    result = TCAP_SendComponent(handle, header, &resultCpt);
    printf("\n result = %d", result);

    /* Check if component was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Component sent successfully */
        printf("\n Result Last Component send success.");
    }
    else
    {
        /* Failed to send component, printing error */
        printf("\n WARNING: Cannot send Result component.");
        /* printf("\n Error: %s.", ITS_GetErrorText(result));*/
        printf("\n result = %d", result);
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a User Cancel component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component this User Cancel
 *                component will cancel
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
int sendTCAPUCancelCpt(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt)
{
    int result = 0;
    TCAP_CPT ucancelCpt;

    /* initialize component structure */
    memset((char *)&ucancelCpt, 0, sizeof(TCAP_CPT));

    /* Set user cancel component parameters */
    ucancelCpt.ptype = TCPPT_TC_U_CANCEL;

    /* Indicate that this is the last component */
    ucancelCpt.last_component = TCP_LAST_CPT;

    /* grabbing the invoke ID from the incoming invoke */
    ucancelCpt.u.cancel.invoke_id.len = recvCpt->u.invoke.invoke_id.len;
    memcpy(ucancelCpt.u.cancel.invoke_id.data, recvCpt->u.invoke.invoke_id.data,
           recvCpt->u.invoke.invoke_id.len);

    /* Print component information before sending */
    printf("\n Result Component before send.");
    traceComponent(header, &ucancelCpt);

    /* Send the component */
    result = TCAP_SendComponent(handle, header, &ucancelCpt);
    printf("\n result = %d", result);

    /* Check if component was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* Component sent successfully */
        printf("\n User Cancel component send success.");
    }
    else
    {
        /* Failed to send component, printing error */
        printf("\n WARNING: Failed to send User Cancel component.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to any of the 9 INAP Procedures in
 *      this program.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *      orig_addr - originating address
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
respondToINAPMessage(ITS_HANDLE handle, ITS_HDR *header,
                     TCAP_CPT *recvCpt, SCCP_ADDR *orig_addr)
{
    int result = 0;
    int code = 0;

    /* Determine which INAP Message was received */
    switch (recvCpt->u.invoke.operation.data[2])
    {
    case INAP_OP_callGap:
        /* Received a CallGap message, sending a response for CallGap */
        printf("\n Sending a response for CallGap.");
        responseToCallGap(handle, header);
        break;

    case INAP_OP_callInformationRequest:
        /* Received an CallInformationRequest message, sending a response */
        responseToCallInformationRequest(handle, header, recvCpt);
        break;

    case INAP_OP_cancelStatusReportRequest:
        responseToCancelStatusReportRequest(handle, header);
        break;

    case INAP_OP_connect:
        /* Received a Connect procedure, sending a response */
        responseToConnect(handle, header);
        break;

    case INAP_OP_initialDP:
        /* Received an InitialDP message, sending a response */
        responseToInitialDP(handle, header, recvCpt, orig_addr);
        break;

    case INAP_OP_requestCurrentStatusReport:
        /*
         * Received a RequestCurrentStatusReport message, sending a
         * response
         */
        responseToRequestCurrentStatusReport(handle, header, recvCpt,
                                             orig_addr);
        break;

    case INAP_OP_requestEveryStatusChangeReport:
        /*
         * Received an RequestEveryStatusChangeReport message, sending a
         * response
         */
        responseToRequestEveryStatusChangeReport(handle, header, recvCpt,
                                                 orig_addr);
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        /*
         * Received an RequestFirstStatusMatchReport message, sending a
         * response
         */
        result = responseToRequestFirstStatusMatchReport(handle, header,
                                                         recvCpt, orig_addr);
        break;

    case INAP_OP_requestReportBCSMEvent:
        /* Received an RequestReportBCSMEvent message, sending a response */
        result = responseToRequestReportBCSMEvent(handle, header, recvCpt);
        break;

    default:
        /*
         * The INAP Operation code is not recognized. Only the 12 messages
         * above is supported in this test program.
         */
        printf("\n INAP Operation code is not recognized.");
        printf("\n Operation Code: 0x%x", recvCpt->u.invoke.operation.data[2]);
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");
        printf("\n");

        /* Send end dialog transaction */
        sendTCAPEndDlg(handle, header, TCP_NO_CPT, TCPEND_PREARRANGED);
        printf("\n result = %d", result);
        break;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send an End dialog for when a CallGap invoke
 *      component is received.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the End dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToCallGap(ITS_HANDLE handle, ITS_HDR *header)
{
    TCAP_DLG endDlg;
    
    /* Initialize component structure */
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    /* Transaction needs to be ended */
    printf("\n Sending an End dialog with no component.");
    printf("\n Termination set to Pre-arranged End.");
    printf("\n");

    /* Send end dialog transaction */
    return sendTCAPEndDlg(handle, header, TCP_NO_CPT, TCPEND_PREARRANGED);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a CallInformationRequest invoke
 *      component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToCallInformationRequest(ITS_HANDLE handle, ITS_HDR *header,
                                 TCAP_CPT *recvCpt)
{
    int result = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT invokeCpt;
    
    /* Initialize component structure */
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    printf("\n Sending an Invoke Component.");

    /* setting component type, invoke ID */
    invokeCpt.ptype = TCPPT_TC_INVOKE;

    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    invokeCpt.u.invoke.invoke_id.len = invoke_id->len;
    memcpy(invokeCpt.u.invoke.invoke_id.data, invoke_id->data, 
           invoke_id->len);

    /* Setting the Invoke ID */

    /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.len = 3;

    /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;

    /* INVOKE ID Length */
    invokeCpt.u.invoke.invoke_id.data[1] = 1;

    /* Invoke ID "value" */
    invokeCpt.u.invoke.invoke_id.data[2] = 5;

    /*
     * Setting operation class = 1, meaning response expected for operation
     * success or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    /* Setting Invoke timeout */
    invokeCpt.u.invoke.timeout = 45;

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * The operation and the parameters of the invoke will be set
     * by the INAP library.
     */

    /* Send INAP Response for CallInformationRequest procedure */
    result = sendCallInformationReportArg(handle, header, &invokeCpt);
    printf("\n result = %d", result);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* CallInformationRequest send success */
        printf("\n Invoke Component before sending dialog.");
        traceComponent(header, &invokeCpt);

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT,
                                TCPEND_BASIC);
    }
    else
    {
        /* Failed to send CallInformationRequest, print error */
        printf("\n Failed to send CallInformationReportArg.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");
        printf("\n");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a CancelStatusReportRequest
 *      invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the End dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The transaction is just ended by sending an end dialog.
 *
 *  See Also:
 ****************************************************************************/
int
responseToCancelStatusReportRequest(ITS_HANDLE handle, ITS_HDR *header)
{
    TCAP_DLG endDlg;
    
    /* Initialize component structure */
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    /* Transaction needs to be ended */
    printf("\n Sending an End dialog with no component.");
    printf("\n Termination set to Pre-arranged End.");
    printf("\n");

    /* Send end dialog transaction */
    return sendTCAPEndDlg(handle, header, TCP_NO_CPT, TCPEND_PREARRANGED);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a Connect invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the End dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The transaction is just ended by sending an end dialog.
 *
 *  See Also:
 ****************************************************************************/
int
responseToConnect(ITS_HANDLE handle, ITS_HDR *header)
{
    TCAP_DLG endDlg;

    /* Initialize component structure */
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    /* Transaction needs to be ended */
    printf("\n Sending an End dialog with no component.");
    printf("\n Termination set to Pre-arranged End.");
    printf("\n");

    /* Send end dialog transaction */
   return sendTCAPEndDlg(handle, header, TCP_NO_CPT, TCPEND_PREARRANGED);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a InitialDP invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the End dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      InitialDP is ended once the operation is done, so sending a TCAP End
 *      dialog is all that needs to be done.
 *
 *  See Also:
 ****************************************************************************/
int
responseToInitialDP(ITS_HANDLE handle, ITS_HDR *header, TCAP_CPT *recvCpt,
                    SCCP_ADDR *orig_addr)
{
    int result = 0, choice = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT invokeCpt;
    
    /* Initialize structures */
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));

    /* setting component type, invoke ID */
    invokeCpt.ptype = TCPPT_TC_INVOKE;

    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    invokeCpt.u.invoke.invoke_id.len = invoke_id->len;
    memcpy(invokeCpt.u.invoke.invoke_id.data, invoke_id->data, 
           invoke_id->len);

    /* Setting the Invoke ID */

    /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.len = 3;

    /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;

    /* INVOKE ID Length */
    invokeCpt.u.invoke.invoke_id.data[1] = 1;

    /* Invoke ID "value" */
    invokeCpt.u.invoke.invoke_id.data[2] = 5;

    /*
     * Setting operation class = 1, meaning response expected for operation
     * success or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    /* Setting Invoke timeout */
    invokeCpt.u.invoke.timeout = 45;

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * The operation and the parameters of the invoke will be set
     * by the INAP library.
     */

    /* Ask user to select response for InitialDPArg */
    printf("\n Select response to IntialDP:");
    printf("\n ----------------------------");
    printf("\n 1 ContinueArg");
    printf("\n 2 ReleaseCallArg");
    printf("\n");
    choice = getSelection(1, 2);

    /* Determine response selected by user */
    if (choice == 1)
    {
        printf("\n Sending ContinueArg as response.");
        result = sendContinueArg(handle, header, &invokeCpt);
    }
    else
    {
        printf("\n Sending ReleaseCallArg as response.");
        result = sendReleaseCallArg(handle, header, &invokeCpt);
    }

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /* CallInformationRequest send success */
        printf("\n Invoke Component before sending dialog.");
        traceComponent(header, &invokeCpt);

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT,
                                TCPEND_BASIC);
    }
    else
    {
        /* Failed to send CallInformationRequest, print error */
        printf("\n Failed to send CallInformationReportArg.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with invoke.");
        printf("\n Termination set to Basic End.");
        printf("\n");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a RequestCurrentStatusReport
 *      invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *      orig_addr - originating address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToRequestCurrentStatusReport(ITS_HANDLE handle, ITS_HDR *header,
                                     TCAP_CPT *recvCpt, SCCP_ADDR *orig_addr)
{
    int result = 0;
    int resourceStatus = 0;
    int selection = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT resultCpt;

    /* Initialize component structure */
    memset((char *)&resultCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    printf("\n Sending a response to RequestCurrentStatusReport.");

    /* Component to send is a Result Last component */
    resultCpt.ptype = TCPPT_TC_RESULT_L;

    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    resultCpt.u.result.invoke_id.len = invoke_id->len;
    memcpy(resultCpt.u.result.invoke_id.data, invoke_id->data, 
           invoke_id->len);

    /* Indicate that this is the last component */
    resultCpt.last_component = TCP_LAST_CPT;

    /* Result component operation field is set in the send function below */
    result = sendRequestCurrentStatusReportResult(handle, header, &resultCpt);

    /* Check if INAP message was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameter of the Result Component
         */
        printf("\n RequestCurrentStatusReportResult send success.");

        /* Printout component information */
        traceComponent(header, &resultCpt);

        /* Ask user to select between a TCAP End or Continue to send */
        printf("\n Select Dialog To Send:");
        printf("\n ----------------------");
        printf("\n [%2d] Continue", 1);
        printf("\n [%2d] End", 2);
        printf("\n");
        printf("\n -> ");
        selection = getSelection(1,2);

        /* Determine what dialog the user selected to send */
        if (selection == 1)
        {
            /* Send a continue dialog */
            result = sendTCAPContinueDlg(handle, header, TCP_CPT_PRESENT, orig_addr);
        }
        else
        {
            /* Send a TCAP End dialog */
            result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT, TCPEND_BASIC);
        }
    }
    else
    {
        /* Failed to send RequestCurrentStatusReportResult */
        printf("\n Failed to send RequestCurrentStatusReportResult.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a RequestEveryStatusChangeReport
 *      invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *      orig_addr - originating address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToRequestEveryStatusChangeReport(ITS_HANDLE handle, ITS_HDR *header,
                                         TCAP_CPT *recvCpt,
                                         SCCP_ADDR *orig_addr)
{
    int result = 0;
    int selection = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT invokeCpt;
    
    /* Initialize component structure */
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    printf("\n Sending an Invoke Component.");

    /* setting component type, invoke ID */
    invokeCpt.ptype = TCPPT_TC_INVOKE;

    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    invokeCpt.u.invoke.invoke_id.len = invoke_id->len;
    memcpy(invokeCpt.u.invoke.invoke_id.data, invoke_id->data, 
           invoke_id->len);

    /* Setting the Invoke ID */
    invokeCpt.u.invoke.invoke_id.len = 3; /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[1] = 1; /* INVOKE ID Length */
    invokeCpt.u.invoke.invoke_id.data[2] = 5; /* Invoke ID "value" */

    /*
     * Setting operation class = 1, meaning response expected for operation
     * success or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    /* Setting Invoke timeout */
    invokeCpt.u.invoke.timeout = 45;

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * The operation and the parameters of the invoke will be set
     * by the INAP library.
     */
    result = sendStatusReportArg(handle, header, &invokeCpt);

    /* Check if StatusReport was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameter of the Result Component
         */
        printf("\n StatusReport send success.");

        /* Printout component information */
        traceComponent(header, &invokeCpt);

        /* Ask user to select between a TCAP End or Continue to send */
        printf("\n Select Dialog To Send:");
        printf("\n ----------------------");
        printf("\n [%2d] Continue", 1);
        printf("\n [%2d] End", 2);
        printf("\n");
        printf("\n -> ");
        selection = getSelection(1,2);

        /* Determine what dialog the user selected to send */
        if (selection == 1)
        {
            /* Send a continue dialog */
            result = sendTCAPContinueDlg(handle, header, TCP_CPT_PRESENT,
                                         orig_addr);
        }
        else
        {
            /* Send a TCAP End dialog */
            result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT,
                                    TCPEND_BASIC);
        }
    }
    else
    {
        /* Failed to send StatusReport */
        printf("\n Failed to send StatusReport.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a RequestFirstStatusMatchReport
 *      invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *      orig_addr - originating address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToRequestFirstStatusMatchReport(ITS_HANDLE handle, ITS_HDR *header,
                                        TCAP_CPT *recvCpt, SCCP_ADDR *orig_addr)
{
    int result = 0;
    int selection = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT invokeCpt;
    
    /* Initialize component structure */
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    printf("\n Sending an Invoke Component.");

    /* setting component type, invoke ID */
    invokeCpt.ptype = TCPPT_TC_INVOKE;
 
    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    invokeCpt.u.invoke.invoke_id.len = invoke_id->len;
    memcpy(invokeCpt.u.invoke.invoke_id.data, invoke_id->data, 
           invoke_id->len);

    /* Setting the Invoke ID */
    invokeCpt.u.invoke.invoke_id.len = 3; /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[1] = 1; /* INVOKE ID Length */
    invokeCpt.u.invoke.invoke_id.data[2] = 5; /* Invoke ID "value" */

    /*
     * Setting operation class = 1, meaning response expected for operation
     * success or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    /* Setting Invoke timeout */
    invokeCpt.u.invoke.timeout = 45;

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * The operation and the parameters of the invoke will be set
     * by the INAP library.
     */
    result = sendStatusReportArg(handle, header, &invokeCpt);
    
    /* Check if StatusReport was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameter of the Result Component
         */
        printf("\n StatusReport send success.");

        /* Printout component information */
        traceComponent(header, &invokeCpt);

        /* Ask user to select between a TCAP End or Continue to send */
        printf("\n Select Dialog To Send:");
        printf("\n ----------------------");
        printf("\n [%2d] Continue", 1);
        printf("\n [%2d] End", 2);
        printf("\n");
        printf("\n -> ");
        selection = getSelection(1,2);

        /* Determine what dialog the user selected to send */
        if (selection == 1)
        {
            /* Send a continue dialog */
            result = sendTCAPContinueDlg(handle, header, TCP_CPT_PRESENT, orig_addr);
        }
        else
        {
            /* Send a TCAP End dialog */
            result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT, TCPEND_BASIC);
        }
    }
    else
    {
        /* Failed to send StatusReport */
        printf("\n Failed to send StatusReport.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");
        
        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
    }
    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send a response to a RequestReportBCSMEvent
 *      invoke component.
 *      
 *  Input Parameters:
 *      handle - the transport associated with the transaction
 *      header - a pointer to the context for this dialogue
 *      recvCpt - a pointer to the received component to respond to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
responseToRequestReportBCSMEvent(ITS_HANDLE handle, ITS_HDR *header,
                                 TCAP_CPT *recvCpt)
{
    int result = 0;
    CPT_INV_ID *invoke_id;
    TCAP_DLG endDlg;
    TCAP_CPT invokeCpt;
    
    /* Initialize component structure */
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&endDlg, 0, sizeof(TCAP_DLG));

    printf("\n Sending an Invoke Component.");

    /* setting component type, invoke ID */
    invokeCpt.ptype = TCPPT_TC_INVOKE;

    /* Get the invokeID from the received component */
    invoke_id = &(recvCpt->u.invoke.invoke_id);
    invokeCpt.u.invoke.invoke_id.len = invoke_id->len;
    memcpy(invokeCpt.u.invoke.invoke_id.data, invoke_id->data, 
           invoke_id->len);
    
    /* Setting the Invoke ID */
    invokeCpt.u.invoke.invoke_id.len = 3; /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[1] = 1; /* INVOKE ID Length */
    invokeCpt.u.invoke.invoke_id.data[2] = 5; /* Invoke ID "value" */

    /*
     * Setting operation class = 1, meaning response expected for operation
     * success or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    /* Setting Invoke timeout */
    invokeCpt.u.invoke.timeout = 45;

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * The operation and the parameters of the invoke will be set
     * by the INAP library.
     */
    result = sendEventReportBCSMArg(handle, header, &invokeCpt);

    /* Check if EventReportBCSM was sent successfully */
    if (result == ITS_SUCCESS)
    {
        /*
         * The INAP message was successfully encoded.
         * The Operation code of the Invoke Component was updated.
         * In addition encoded INAP message was copied into the
         * parameter of the Result Component
         */
        printf("\n EventReportBCSM send success.");

        /* Printout component information */
        traceComponent(header, &invokeCpt);

        /* Send a TCAP End dialog */
        result = sendTCAPEndDlg(handle, header, TCP_CPT_PRESENT, TCPEND_BASIC);
    }
    else
    {
        /* Failed to send EventReportBCSM */
        printf("\n Failed to send EventReportBCSM.");
        printf("\n Error: %s.", ITS_GetErrorText(result));
        printf("\n");

        /* Transaction needs to be ended */
        printf("\n Sending an End dialog with no component.");
        printf("\n Termination set to Pre-arranged End.");

        /* Send end dialog transaction */
        result = sendTCAPEndDlg(handle, header, TCP_NO_CPT,
                                TCPEND_PREARRANGED);
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
    /* temporary information used to set gtt information */
    ITS_OCTET tmpAddressIndicator = *addrIndicator;
    int gttEncoding = 0;
    ITS_OCTET translationType = 0;
    ITS_OCTET natureAddress = 0;
    ITS_OCTET encoding = 0;
    ITS_OCTET numbering = 0;
    int tmpLen = 0;

#ifdef ANSI
    /* Max Number of digits in GTT for ANSI is 20. +4 just in case */
    char gttDigits[24] ;
#else
    /* Max Number of digits in GTT for ITU is 48. +4 just in case */
    char gttDigits[52] ;
#endif

    /* index to browse back and forth in gttInfo array */
    int gttInfoIndex = 0;

    /* number of digits */
    int nbDigits = 0;
    int i;

    /*
     * Setting GGT Encoding.
     * There is more option for ITU than there are for ANSI.
     */
    printf("\n Enter GTT Encoding:");
#ifdef CCITT
    printf("\n [1] Perform GTT with Nature of Address only.");
#endif
    printf("\n [2] Perform GTT Translation only.");
    printf("\n [3] Perform GTT Translation with Encoding Scheme and Numbering Plan.");
#ifdef CCITT
    printf("\n [4] Perform GTT Translation with both Nat of Addr and Scheme + Plan.");
#endif

#ifdef ANSI
    gttEncoding = getSelection(2, 3);
    if (gttEncoding == 2)
    {
        /* GTT Translation Only */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
    }
    else
    {
        /* GTT Translation with Encoding Scheme and Numbering Plan */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TNE;
    }
#endif

#ifdef CCITT
    gttEncoding = getSelection(1, 4);
    if (gttEncoding == 1)
    {
        /* GTT Translation with Nature of Address */
        tmpAddressIndicator |= SCCP_CPA_GTTI_NATURE;
    }
    else if (gttEncoding == 2)
    {
        /* GTT Translation Only */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
    }
    else if (gttEncoding == 3)
    {
        /* GTT Translation with Encoding Scheme and Numbering Plan */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TNE;
    }
    else
    {
        /* GTT Translation with both Nat of Addr and Scheme + Plan */
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
    printf("\n Enter GTT Translation Type (0-255)");
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
        /* Need to provide Nature of Address */
        printf("\n Enter GTT Nature of Address Indicator (0-127)");
        natureAddress = (ITS_OCTET)getSelection(0, 127);
        /*  Need to know number of digits to set or clear MSB
         * for nature of Address Indicator.
         * Will be added to gttInfo array when requesting digits.
         */
        break;
#endif

    case SCCP_CPA_GTTI_TRANS:
        /* Nothing to set for that one */
        break;

    case SCCP_CPA_GTTI_TNE:
        /* Need to provide Encoding Scheme and Numbering Plan */
        printf("\n Enter GTT Encoding Scheme (0-15)");
        encoding = (ITS_OCTET)getSelection(0, 15);
        printf(" Enter GTT Numbering Plan (0-15)");
        numbering = (ITS_OCTET)getSelection(0, 15);
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;
        break;

#ifdef CCITT
    case SCCP_CPA_GTTI_ALL:
        /* Need to provide  Scheme + Plan then Nat of Addr*/
        printf("\n Enter GTT Encoding Scheme (0-15)");
        encoding = (ITS_OCTET)getSelection(0, 15);
        printf(" Enter GTT Numbering Plan (0-15)");
        numbering = (ITS_OCTET)getSelection(0, 15);
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;

        printf(" Enter GTT Nature of Address Indicator (0-127)");
        natureAddress = (ITS_OCTET)getSelection(0, 127);
        gttInfo[gttInfoIndex++] = natureAddress;
        tmpLen++;
        break;
#endif /* CCITT */

    default:
        break;
    }

    /* Ask User for GTT digits. */
    printf(" Address Information (ex: 1800456) -> ");
    scanf("%s", gttDigits);

    nbDigits = strlen(gttDigits);
    
#ifdef CCITT
    /*
     * For GTT Encoding Nature of Address Indicator,
     * if Odd number of digits, will set last bit.
     */
    if ((tmpAddressIndicator & SCCP_CPA_GTTI_MASK) == SCCP_CPA_GTTI_NATURE) 
    {
        if ((nbDigits % 2) != 0)
        {
            /* Odd Number of digits: setting MSB */
            gttInfo[gttInfoIndex++] = (natureAddress | 0x80);
            tmpLen++;
        }
        else
        {
            /* Even Number of digits, clearing MSB */
            gttInfo[gttInfoIndex++] = (natureAddress & 0x7F);
            tmpLen++;
        }
    }
#endif

    /* Putting digits into GTT Info array */
    for (i = 0; i < nbDigits; i++)
    {
         if (i & 1)
         {
             /* MSB digit */
             gttInfo[gttInfoIndex++] |= ((gttDigits[i] - 0x30) << 4);
         }
         else
         {
             /* LSB digit */
             gttInfo[gttInfoIndex] = (gttDigits[i] - 0x30);
         }
    }

    /* adding the len of digits, if odd number, must add + 1 */
    tmpLen += (nbDigits / 2);
    if (nbDigits & 1)
    {
        tmpLen++;
    }
    
    /* Updating address Indicator to reflect GTT Encoding */
    *addrIndicator = tmpAddressIndicator;

    /* Updating length of GTT Info */
    *len = tmpLen;
}

/*
 ************************************************************************
 *  Purpose:
 *       This function will decode the parameter field of a component.
 *
 *  Input Parameters:
 *       cpt - a pointer to a component
 *
 *  Input/Output Parameters:
 *       None.
 *
 *  Output Parameters:
 *       None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the component and the dialog was sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      
 *
 *  See Also:
 ************************************************************************/
int
decodeINAPMessage(ITS_HANDLE handle, TCAP_CPT *cpt)
{
    int result = 0;
    struct type_INAP_CallGapArg *cgArg;
    struct type_INAP_CallInformationRequestArg *cireqArg;
    struct type_INAP_CancelStatusReportRequestArg *csrrArg;
    struct type_INAP_ConnectArg *cArg;
    struct type_INAP_ContinueArg *contArg;
    struct type_INAP_InitialDPArg *idpArg;
    struct type_INAP_ReleaseCallArg *rcArg;
    struct type_INAP_RequestCurrentStatusReport *rcsrArg;
    struct type_INAP_RequestEveryStatusChangeReport *rescrArg;
    struct type_INAP_RequestFirstStatusMatchReport *rfsmrArg;
    struct type_INAP_RequestReportBCSMEventArg *rrbcsmeArg;
    struct type_INAP_CallInformationReport *cirepArg;
    struct type_INAP_EventReportBCSM *erbcsmArg;
    struct type_INAP_RequestCurrentStatusReportResult *rcsrRes;
    struct type_INAP_StatusReport *srArg;

    /*
     * Determine which INAP message is stored in the parameter field of the
     * component
     */
    switch (cpt->u.invoke.operation.data[2])
    {
    case INAP_OP_callGap:
        /* Decode INAP message */
        printf("\n Decoding CallGap.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeCallGap(handle, cpt, (void**)&cgArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_CallGapArg(cgArg);
        break;

    case INAP_OP_callInformationReport:
        /* Decode INAP message */
        printf("\n Decoding CallInformationReport.\n");
        
        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeCallInformationReport(handle, cpt, 
                                                  (void**)&cirepArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_CallInformationReportArg(cirepArg);
        break;

    case INAP_OP_callInformationRequest:
        /* Decode INAP message */
        printf("\n Decoding CallInformationRequest.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeCallInformationRequest(handle, cpt, 
                                                   (void**)&cireqArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_CallInformationRequestArg(cireqArg);
        break;

    case INAP_OP_cancelStatusReportRequest:
        /* Decode INAP message */
        printf("\n Decoding CancelStatusReportRequest.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeCancelStatusReportRequest(handle, cpt, 
                                                      (void**)&csrrArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_CancelStatusReportRequestArg(csrrArg);
        break;

    case INAP_OP_connect:
        /* Decode INAP message */
        printf("\n Decoding Connect.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeConnect(handle, cpt, (void**)&cArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_ConnectArg(cArg);
        break;
    case INAP_OP_continue:
        /* Decode INAP message */
        printf("\n Decoding Continue.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeContinue(handle, cpt, (void**)&contArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }
        /* Coninue has no parameters so no memory needs to be freed */
        break;
    case INAP_OP_eventReportBCSM:
        /* Decode INAP message */
        printf("\n Decoding EventReportBCSM.\n");
        
        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeEventReportBCSM(handle, cpt, (void**)&erbcsmArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_EventReportBCSMArg(erbcsmArg);
        break;

    case INAP_OP_initialDP:
        /* Decode INAP message */
        printf("\n Decoding InitialDP.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeInitialDP(handle, cpt, (void**)&idpArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_InitialDPArg(idpArg);
        break;
    case INAP_OP_releaseCall:
        /* Decode INAP message */
        printf("\n Decoding ReleaseCall.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeReleaseCall(handle, cpt, (void**)&rcArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_ReleaseCallArg(rcArg);
        break;
    case INAP_OP_requestCurrentStatusReport:
        /* Decode INAP message */
        printf("\n Decoding RequestCurrentStatusReport.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeRequestCurrentStatusReport(handle, cpt,
                                                       (void**)&rcsrArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_RequestCurrentStatusReportArg(rcsrArg);
        break;

    case INAP_OP_requestCurrentStatusReportResult:
        /* Decode INAP message */
        printf("\n Decoding RequestCurrentStatusReportResult.\n");
        
        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeRequestCurrentStatusReportResult(handle, cpt,
                                                             (void**)&rcsrRes);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_RequestCurrentStatusReportResult(rcsrRes);
        break;

    case INAP_OP_requestEveryStatusChangeReport:
        /* Decode INAP message */
        printf("\n Decoding RequestEveryStatusChangeReport.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeRequestEveryStatusChangeReport(handle, cpt,
                                                           (void**)&rescrArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_RequestEveryStatusChangeReportArg(rescrArg);
        break;

    case INAP_OP_requestFirstStatusMatchReport:
        /* Decode INAP message */
        printf("\n Decoding RequestFirstStatusMatchReport.\n");
        
        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeRequestFirstStatusMatchReport(handle, cpt,
                                                          (void**)&rfsmrArg);
        printf("\n result = %d", result);

        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_RequestFirstStatusMatchReportArg(rfsmrArg);
        break;

    case INAP_OP_requestReportBCSMEvent:
        /* Decode INAP message */
        printf("\n Decoding RequestReportBCSMEvent.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeRequestReportBCSMEvent(handle, cpt, 
                                                   (void**)&rrbcsmeArg);
        printf("\n result = %d", result);
        
        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_RequestReportBCSMEventArg(rrbcsmeArg);
        break;

    case INAP_OP_statusReport:
        /* Decode INAP message */
        printf("\n Decoding StatusReport.\n");

        /*
         * Memory is allocated for the pointer to the INAP structure
         * during the decode
         */
        result = INAP_DecodeStatusReport(handle, cpt, (void**)&srArg);
        printf("\n result = %d", result);
        
        /* Check if decode was successful */
        if (result == ITS_SUCCESS)
        {
            /* INAP message decoded successfully */
            printf("\n Decode success.");
        }
        else
        {
            /* Failed to decode INAP message */
            printf("\n Failed to decode.");
            printf("\n Error is: %s.", ITS_GetErrorText(result));
            printf("\n");
        }

        /* Free allocated memory */
        free_INAP_StatusReportArg(srArg);
        break;

    default:
        /*
         * The INAP Operation code is not recognized. Only the 12 messages
         * above is supported in this test program.
         */
        printf("\n INAP Operation code is not recognized.");
        printf("\n Either the operation doesnt exist or it is not included in");
        printf("\n this demo.");
        printf("\n");
        break;
    }

    return result;
}
