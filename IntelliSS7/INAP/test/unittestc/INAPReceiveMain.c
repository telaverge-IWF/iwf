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

#include <signal.h>

#include <its.h>
#include <its_app.h>

#include <itu/tcap.h>
#include <itu/INAP-types.h>
#include <itu/inap.h>

#include "inaptest.h"


/* Global Variables */
ITS_HANDLE handle;
ITS_HDR header;         /* transaction header */
SCCP_ADDR dest_addr;    /* destination address */
SCCP_ADDR orig_addr;    /* originating address */


/*
 * Control C Handler: used to quit the application but doing the necessary
 * clean up before exiting
 */
void
break_handler(int sig)
{
    ITS_Terminate(handle);

    exit(0);
}


/****************************************************************************
 *                          Receive Program
 ****************************************************************************/
int
main(int arg, char** argv)
{
    int result = 0;
    int msgType = 0;

    ITS_HDR recvHeader;
    TCAP_CPT recvComponent;
    TCAP_CPT invokeCpt;
 
    signal(SIGINT, break_handler);

    /* Initializations */
    memset((char *)&invokeCpt, 0, sizeof(TCAP_CPT));

    /* Create an ITS_HANDLE */
    handle = initReceiveHandle();

    /* Ask user to provide Destination Address */
    printf("\n");
    printf("\n Enter Destination Address:");
    printf("\n --------------------------");

    /* Ask user for a destination address */
    result = getSCCPAddr(&dest_addr);

    /* Check to see Destination Address build failed */
    if (result != ITS_SUCCESS)
    {
        /* Failed to build SCCP Address, print error */
        printf("\n Failed to set SCCP Destination Address.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
        printf("\n Quiting...");

        /* Do neccessary clean up, then exit application */
        ITS_Terminate(handle);
        exit(0);
    }

    /* Ask user to provide Originating Address */
    printf("\n");
    printf("\n Enter Originating Address:");
    printf("\n --------------------------");

    /* Ask user for a originating address */
    result = getSCCPAddr(&orig_addr);

    /* Check to see Originating Address build failed */
    if (result != ITS_SUCCESS)
    {
        /* Failed to build SCCP Address, print error */
        printf("\n Failed to set SCCP Originating Address.");
        printf("\n Error is: %s.", ITS_GetErrorText(result));
        printf("\n");
        printf("\n Quiting...");

        /* Do neccessary clean up, then exit application */
        ITS_Terminate(handle);
        exit(0);
    }

    for (;;)
    {
        /* Ask user to select an action for the receive program */
        ReceiveProgramMainMenu();

        fflush(stdin);
        scanf("%d", &msgType);

        /* Check if user selected an invalid entry */
        if ( msgType != TEST_SCCP_UIS && msgType != TEST_SCCP_UOS &&
             msgType != TEST_WAIT_FOR_EVENT && msgType != TEST_INAP_RESPONSE &&
             msgType != TEST_TCAP_U_ERROR && msgType != TEST_TCAP_U_REJECT &&
             msgType != TEST_TCAP_U_ABORT && msgType != TEST_TCAP_END &&
             msgType != TEST_EXIT )
        {
            /* User selected an invalid selection */
            printf("\n You selected an invalid selection. ");

            /* Skip the rest of code below and begin with a new loop */
            continue;
        }

        /*
         * Determine which operation the user selected for the Receive
         * program
         */
        switch (msgType)
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
                printf("\n Error is: %s.", ITS_GetErrorText(result));
                printf("\n");
            }
            break;

        case TEST_SCCP_UOS:
            /*
             * Send an SCCP User Out of Service Message
             */
            printf("\n Sending SCCP User Out Of Service");
            result = sendUserOutOfService(handle, orig_addr);
            if (result == ITS_SUCCESS)
            {
                /* User Out of Service send success */
                printf("\n SCCP User Out Of Service successfully sent. ");
            }
            else
            {
                /* Failed to send User Out of Service */
                printf("\n Unable to send User Out Of Service.");
                printf("\n Error is: %s.", ITS_GetErrorText(result));
                printf("\n");
            }
            break;

        case TEST_INAP_RESPONSE:
            /* Send INAP Message response */
            respondToINAPMessage(handle, &recvHeader, &recvComponent, &orig_addr);
            break;

        case TEST_TCAP_U_ERROR:
            /* Send User Error Component response */
            result = sendTCAPErrorCpt(handle, &recvHeader,
                                      &(recvComponent.u.invoke.invoke_id));
            if (result == ITS_SUCCESS)
            {
                sendTCAPEndDlg(handle, &recvHeader, TCP_CPT_PRESENT,
                               TCPEND_BASIC);
            }
            break;

        case TEST_TCAP_U_REJECT:
            /* Will only send a user reject component for this application */
            result = sendTCAPRejectCpt(handle, &recvHeader,
                                       &(recvComponent.u.invoke.invoke_id));
            if (result == ITS_SUCCESS)
            {
                sendTCAPEndDlg(handle, &recvHeader, TCP_CPT_PRESENT, TCPEND_BASIC);
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

        case TEST_WAIT_FOR_EVENT:
            /*
             * Initializatize the header and component each time the user
             * wants to get the next ITS Event
             */
            memset((char *)&recvComponent, 0, sizeof(TCAP_CPT));
            memset((char *)&recvHeader, 0, sizeof(ITS_HDR));

            /* Wait for an SS7 Event */
            waitForEvent(handle, &recvHeader, &recvComponent);
            break;

        case TEST_EXIT:
            /* Exit program after IntelliSS7 cleanup */
            printf("\n Exiting program after cleanup...\n");

            ITS_Terminate(handle);                           
            exit(1);
            break;
        }
    } 
    return result;
}