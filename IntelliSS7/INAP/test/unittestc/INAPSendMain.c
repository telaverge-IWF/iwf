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

#include <stdio.h>
#include <memory.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <itu/tcap.h>

#include <itu/INAP-types.h>
#include <itu/inap.h>

#include "inaptest.h"


/****************************************************************************
 *                           Send Program
 ****************************************************************************/
int
main(int argc, char** argv)
{
    int exit_counter, choice, result;

    ITS_USHORT dialogueID;
    ITS_HANDLE handle;
    ITS_HDR header, recvHeader;
    TCAP_CPT invokeCpt, recvComponent;
    TCAP_DLG dialog;
    SCCP_ADDR orig_addr;
    SCCP_ADDR dest_addr; 

    handle = NULL;

    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&recvHeader, 0, sizeof(ITS_HDR));
    memset((char *)&dialog, 0, sizeof(TCAP_DLG));
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));
    memset((char *)&orig_addr, 0, sizeof(SCCP_ADDR));
    memset((char *)&dest_addr, 0, sizeof(SCCP_ADDR));

    /* Initialize IntelliSS7 */
    handle = initSendHandle();

    /* Ask user to provide Destination Address */
    printf("\n");
    printf("\n Enter Destination Address:");
    printf("\n --------------------------");

    /* Get destination address from user */
    result = getSCCPAddr(&dest_addr);
    
    /* Check to see Destination Address build failed */
    if (result != ITS_SUCCESS)
    {
        /* Failed to build destination address, print error */
        printf("\n Failed to set SCCP Destination Address. Error is: %s .",
               ITS_GetErrorText(result));
        printf("\n Quiting...");

        /* Do necessary clean up then exit */
        ITS_Terminate(handle);
        exit(0);
    }

    /* Ask user to provide Originating Address */
    printf("\n");
    printf("\n Enter Originating Address:");
    printf("\n --------------------------");

    /* Get originating address from user */
    result = getSCCPAddr(&orig_addr);
 
    /* Check to see Originating Address build failed */
    if (result != ITS_SUCCESS)
    {
        /* Failed to build originating address, print error */
        printf("\n Failed to set SCCP Originating Address. Error is: %s .",
               ITS_GetErrorText(result));
        printf("\n Quiting...");

        /* Do necessary clean up, then exit */
        ITS_Terminate(handle);
        exit(0);
    }

    /*
     * Set the originating and destination address parameters of the dialog
     * using the addresses provided by the user
     */
    dialog.u.begin.orig_addr.len = orig_addr.len;
    dialog.u.begin.dest_addr.len = dest_addr.len;
    memcpy(dialog.u.begin.orig_addr.data, orig_addr.data, orig_addr.len);
    memcpy(dialog.u.begin.dest_addr.data, dest_addr.data, dest_addr.len);

    /*
     * Set Quality Of Service Indicator, in this case the dialog expects a
     * response.
     */
    dialog.u.begin.qos.indicator = QOSI_RET_OPT;
    
    /* 
     * Setting the Type of the header to TCAP
     * Setting the Dialogue ID to an arbitrary number.
     */
    header.type = ITS_TCAP;

    /* Indicate component as an Invoke */
    invokeCpt.ptype = TCPPT_TC_INVOKE;

    /*
     * Setting Invoke timeout, will cause the transaction to end when
     * 45 seconds is reached
     */
    invokeCpt.u.invoke.timeout = 45;

    /* Setting the Invoke ID */
    invokeCpt.u.invoke.invoke_id.len = 3; /* Total length of the array */
    invokeCpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* INVOKE ID tag */
    invokeCpt.u.invoke.invoke_id.data[1] = 1; /* INVOKE ID Length */ 
    invokeCpt.u.invoke.invoke_id.data[2] = 5; /* Invoke ID "value" */

    /* Indicate that this is the last component */
    invokeCpt.last_component = TCP_LAST_CPT;

    /*
     * Set Operation class = 1, meaning that a response is expected on succes
     * or failure
     */
    invokeCpt.u.invoke.opClass = 1;

    /* Setting link ID length */
    invokeCpt.u.invoke.linked_id.len = 0;

    for (exit_counter = 0; exit_counter < 100; exit_counter++)
    {
        /* Bring up send INAP message menu */
        SendProgramMainMenu();

        /* Get user selected operation */
        fflush(stdin);
        scanf("%d", &choice);

        switch ( choice )
        {
        case TEST_SCCP_UIS:
            /* Send SCCP User In Service message */
            result = sendUserInService(handle, orig_addr);

            /* Check if Send User In Service was sent successfully */
            if (result == ITS_SUCCESS)
            {
                /* User In Service Send success */
                printf("\n SCCP User In Service Message send success.");
            }
            else
            {
                /* Failed to send User In Service, print error */
                printf("\n Failed to send User In Service.");
                printf("\n Error is: %s", ITS_GetErrorText(result));
            }
            break;

        case TEST_SCCP_UOS:
            /* Send SCCP User In Service message */
            result = sendUserOutOfService(handle, orig_addr);

            /* Check if User Out of Service was sent successfully */
            if (result == ITS_SUCCESS)
            {
                /* Send success */
                printf("\n SCCP User Out Of Service Message send success.");
            }
            else
            {
                /* Failed to send, print error */
                printf("\n Failed to send User Out of Service.");
                printf("\n Error is: %s",
                       ITS_GetErrorText(result));
            }
            break;

        case TEST_TCAP_BEGIN:
            /* Send a Begin dialog */
            
            /* Allocating unique Dialogue ID to distinguish between dialogs. */
            TCAP_AllocateDialogueId(&dialogueID);
            header.context.dialogue_id = dialogueID;

            /*
             * Ask user if an invoke component should be sent with the Begin
             * dialog 
             */
            printf("\n Include an Invoke component [y]es/[n]o ? ");
            if(getYesOrNo() == 1)
            {
                /* Select INAP Messages to send */
                result = SelectINAPMessageToSend(handle, header, &invokeCpt);

                /* Check if INAP component was sent successfully */
                if (result == ITS_SUCCESS)
                {
                    /*
                     * INAP component sent successfully.
                     * Sending the Begin dialog.
                     */
                    sendTCAPBeginDlg(handle, &header, &dialog, TCP_CPT_PRESENT);
                }
                else
                {
                    /* Failed to send INAP message */
                    printf("\n WARNING: Failed to send INAP procedure.");
                    printf("\n          Not sending the Begin dialog.");
                    printf("\n");
                }
            }
            else
            {
                /* Sending a Begin dialog with no component */
                sendTCAPBeginDlg(handle, &header, &dialog, TCP_NO_CPT);
            }
            break;

        case TEST_TCAP_CONTINUE:
            /* Send a Continue dialog */

            /* Select INAP Messages to send */
            result = SelectINAPMessageToSend(handle, recvHeader, &invokeCpt);

            /* Check if INAP component was sent successfully */
            if (result == ITS_SUCCESS)
            {
                /*
                 * INAP component sent successfully.
                 * Sending the Continue dialog.
                 */
                sendTCAPContinueDlg(handle, &recvHeader, TCP_CPT_PRESENT, &orig_addr);
            }
            else
            {
                /* Failed to send INAP message */
                printf("\n WARNING: Failed to send INAP procedure.");
                printf("\n          Not sending the Continue dialog.");
                printf("\n");
            }
            break;

        case TEST_TCAP_U_ABORT:
            /* Send User Abort dialog response */
	    sendTCAPUAbortDlg(handle, &recvHeader);
            break;

        case TEST_TCAP_END:
            /*
             * Ask the user to select a termination type for the End dialog
             * to send
             */
            printf("\n Sending an End Dialog, select termination:");
            printf("\n ------------------------------------------");
            printf("\n [%2d] Basic End", 1);
            printf("\n [%2d] Prearranged End", 2);
            printf("\n");
            printf("\n -> ");
            
            /* Determine what termination type the user selected */
            if (getSelection (1, 2) == 1)
            {
                /* Send an end dialog with termination set to basic end */
                sendTCAPEndDlg(handle, &header, TCP_NO_CPT, TCPEND_BASIC);
            }
            else
            {
                /*
                 * Send an end dialog with termination set to
                 * prearranged end
                 */
                sendTCAPEndDlg(handle, &header, TCP_NO_CPT,
                               TCPEND_PREARRANGED);
            }
            break;

        case TEST_TCAP_UNI:
            /* Allocating unique Dialogue ID to distinguish between dialogs. */
            TCAP_AllocateDialogueId(&dialogueID);
            header.context.dialogue_id = dialogueID;

            /* Select INAP Messages to send */
            result = SelectINAPMessageToSend(handle, header, &invokeCpt);

            /* Check if INAP component was sent successfully */
            if (result == ITS_SUCCESS)
            {
                /*
                 * INAP component sent successfully.
                 * Sending the Unidirectional dialog.
                 */
                sendTCAPUniDlg(handle, &header, TCP_CPT_PRESENT, orig_addr,
                               dest_addr);
            }
            else
            {
                /* Failed to send INAP message */
                printf("\n WARNING: Failed to send INAP procedure.");
                printf("\n          Not sending the Unidirectional dialog.");
                printf("\n");
            }
            break;

        case TEST_TCAP_U_CANCEL:
            /* Send a User Cancel component */
            sendTCAPUCancelCpt(handle, &header, &invokeCpt);
            break;

        case TEST_WAIT_FOR_EVENT:
            /*
             * Initialize container for received TCAP component, each time the
             * user chooses to wait for an OTS Event
             */
            memset((char *)&recvComponent, 0, sizeof(TCAP_CPT));

            /* Get Next ITS Event */
            waitForEvent(handle, &recvHeader, &recvComponent);
            break;

        case -1:
            /* Used to exit Unit Tester */
            exit_counter = 200;
            break;

        default:
            break;
        }
    }
    return 0;
}
