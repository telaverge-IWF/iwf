#include <stdio.h>
#include <assert.h>
#include <its.h>
#include <its_vmi.h>
/*#include <its_ss7_stubs.h>*/
/*#include <its_gdi_stubs.h>*/
#include <its_thread.h>
#include <its_transports.h>
#include <its_app.h>
#include<its_timers.h>
#include <ss7type.h>
#include <itu/mtp3.h>
/*#include <its_intern.h>*/
    
#define VMI_EVENT_RECEIVER_SRC 1
#define VMI_EVENT_ASYNRECEIVER_SRC 2
CALLBACK_Manager*   MTP3_CCITT_ManagementCallbacks;
CALLBACK_Manager*   SCCP_CCITT_ManagementCallbacks;
CALLBACK_Manager*   ISUP_CCITT_ManagementCallbacks;

void
VMI_ProcessCommandLine(int argc, const char **argv);
void
VMI_Usage(const char *invokedName);
 /* internal format for the ITS_SS7_HANDLE
 */

typedef struct
{
    ITS_UINT    mask;
    ITS_USHORT  instance;
    ITS_USHORT  pad;
    OS_HSYNC    mtp3Sync;
    OS_HSYNC    isupSync;
    OS_HSYNC    sccpSync;
    OS_HSYNC    tcapSync;
    OS_FD       sccpFD;
    S16         sapid;
    S16         servUserId;
    U8          boardNum;
    U8          srcEnt;
    U8          srcInst;
    U8          type;
    U32         opc;
    U32         dpc;
    U8          ssn[30];
    U8          maxSubs;
    U8          currentSub;
    U8          destSsn;
    U8          sio;
    U8          pad2;
}
ITS_SS7_CONTEXT;



static ITS_THREAD thr;
static ITS_BOOLEAN thrExitStatus = ITS_FALSE;
static int TEST_CreateReceiverThread();
static char * VMI_EventToText(ITS_OCTET vmiEventId);

THREAD_RET_TYPE
VMI_AsyncReceiver(void *arg)
{
	ITS_HANDLE handle;
	ITS_EVENT  event;
	int i;
	



	handle = ITS_Initialize(ITS_TRANSPORT_SINGLE_USER | ITS_TRANSPORT_TQUEUE, 
		                   VMI_EVENT_ASYNRECEIVER_SRC);

	
    assert(handle != NULL);

	VMI_RegisterInstance(VMI_EVENT_ASYNRECEIVER_SRC);

	memset(&event,0,sizeof(ITS_EVENT));

	for (;;)
	{

        ITS_GetNextEvent(handle, &event);

         printf("\n\n Asynchronous Event: %s: ",VMI_EventToText(event.data[0]) );

		 for(i = 0; i<event.len; i++)
		 {
             printf("0x%02x ",event.data[i]);
		 }
		 printf("\n");

	}

	THREAD_NORMAL_EXIT;
}


static int TEST_CreateReceiverThread()
{
	int ret;
    
	
	ret = THREAD_CreateThread(&thr, 0, VMI_AsyncReceiver, 
	   (void *) NULL, ITS_TRUE );
	
	if (ret != ITS_SUCCESS)
	{
        printf("ERROR Creating VMI_AsyncReceiver Thread\n\n");
		return ITS_ENOMEM;

	}

	return ITS_SUCCESS;

}

int main(int argc, const char **argv)
{
	int ret, choice = 0, finished=0;
	ITS_EVENT event;
	ITS_HANDLE handle;
	int i;
    ITS_SS7_HANDLE handl;
    ITS_SS7_CONTEXT *context;
    handl = (ITS_SS7_HANDLE) malloc(sizeof(ITS_SS7_CONTEXT));

    context = (ITS_SS7_CONTEXT *)handl;
    context->sio = 3;
    context->boardNum = 1;
    context->sapid = 0;
    context->servUserId = 0;
    context->srcEnt = 32;
    context->srcInst = 0;
	
    APPL_SetName("vmitest");

	ret = TEST_CreateReceiverThread();
	if (ret != ITS_SUCCESS)
	{
		printf("Unable to create the Receiver Thread\n");
		return 0;

	}
	TIMERS_Sleep(2);

    APPL_SetName("vmitest");
	handle = ITS_Initialize(ITS_TRANSPORT_SINGLE_USER | ITS_TRANSPORT_TQUEUE, 
		                   VMI_EVENT_RECEIVER_SRC);

    assert(handle != NULL);

	/*VMI_RegisterInstance(1);*/
     
    ret = VMI_Initialize(handl);
	if (ret != ITS_SUCCESS)
	{
		printf("\n\n VMI_Initialize has failed: %d\n", ret);
	}


            VMI_ProcessCommandLine(argc,argv);		


            ITS_GetNextEvent(handle, &event);

		    printf("\n\nEvent received: ");

		    for(i = 0; i<event.len; i++)
			{
                printf("0x%02x ",event.data[i]);
			}
   
    TIMERS_Sleep(10);


    return 0;
}


static char * 
VMI_EventToText(ITS_OCTET vmiEventId)
{
    switch (vmiEventId)
    {
        case  VMI_EVN_ISOLATED:
            return "VMI_EVN_ISOLATED"; 
 
        case VMI_EVN_CONNECTED:
            return "VMI_EVN_CONNECTED"; 

        case VMI_EVN_NOWPRIMARY:
            return "VMI_EVN_NOWPRIMARY"; 

        case VMI_EVN_BRDDEAD:
            return "VMI_EVN_BRDDEAD"; 
    
        case  VMI_EVN_TASKDEAD:
            return "VMI_EVN_TASKDEAD"; 

        case  VMI_EVN_HALTED:
            return "VMI_EVN_HALTED"; 

        case  VMI_EVN_LOADING:
            return "VMI_EVN_LOADING"; 

        case  VMI_EVN_NOWBACKUP:
            return "VMI_EVN_NOWBACKUP"; 

        case  VMI_EVN_NOWSTANDALONE:
            return "VMI_EVN_NOWSTANDALONE"; 

        case VMI_EVN_STARTING:
            return "VMI_EVN_STARTING"; 

        case  VMI_EVN_CONFLICT:
            return "VMI_EVN_CONFLICT"; 

        case  VMI_EVN_SERVICE_DOWN:
            return "VMI_EVN_SERVICE_DOWN"; 

        default:
            return "UNKNOWN EVENT";



    }

} 


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function processes the command line for the PSNIF server
 *
 *  Input Parameters:
 *     argc           = The number of parameters
 *     *argv          = The list of parameters
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
VMI_ProcessCommandLine(int argc, const char **argv)
{
    int exitCode = -1;
    int i = 0;

	if (argc==1)
	{
        VMI_Usage(argv[0]);
         exit(exitCode);
	}


    for (i = 1; i < argc; i++)
    {

        if (*argv[i] == '-')
        {
            if ( (strcmp("help", argv[i] + 1) == 0) ||
                 (strcmp("h", argv[i] + 1) == 0) )
            {
                VMI_Usage(argv[0]);
                exit(0);
            }
            else if ( (strcmp("LOAD", argv[i] + 1)  == 0) || 
				     (strcmp("L",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_LOAD_BOARD,VMI_EVENT_RECEIVER_SRC);
				i++;
            }

            else if ( (strcmp("HALT", argv[i] + 1)  == 0) || 
				      (strcmp("H",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_HALT_BOARD,VMI_EVENT_RECEIVER_SRC);
				i++;
            }

            else if ( (strcmp("PRIMARY", argv[i] + 1)  == 0) || 
				      (strcmp("P",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_PRIMARY,VMI_EVENT_RECEIVER_SRC);
				i++;
            }


            else if ( (strcmp("BACKUP", argv[i] + 1)  == 0) || 
				      (strcmp("B",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_BACKUP,VMI_EVENT_RECEIVER_SRC);
				i++;
            }

            else if ( (strcmp("RESET", argv[i] + 1)  == 0) || 
				      (strcmp("R",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_RESET,VMI_EVENT_RECEIVER_SRC);
				i++;
            }


            else if ( (strcmp("SHUTDOWN", argv[i] + 1)  == 0) || 
				      (strcmp("SD",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_SHUTDOWN,VMI_EVENT_RECEIVER_SRC);
				i++;
            }


            else if ( (strcmp("STANDALONE", argv[i] + 1)  == 0) || 
				      (strcmp("SA",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_STANDALONE,VMI_EVENT_RECEIVER_SRC);
				i++;
            }


            else if ( (strcmp("STATUS", argv[i] + 1)  == 0) || 
				      (strcmp("ST",argv[i] + 1) == 0 )  )
            {
                VMI_SendPrimitive(VMI_STATUS_REQUEST,VMI_EVENT_RECEIVER_SRC);
				i++;
            }


            else if (strcmp("console", argv[i] + 1) == 0)
            {
              
                    /*traceOn = 1;
                    PSNIF_TRACE(("... running at Console \n")); */
                    continue;
               
            }
            else
            {
                VMI_Usage(argv[0]);
                exit(exitCode);
            }

        }
        else
        {
            VMI_Usage(argv[0]);
            exit(exitCode);

        }

    }

}


void
VMI_Usage(const char *invokedName)
{
    printf("\n");
    printf("Usage:  %s   <args> \n", invokedName);
    printf("\n");
    printf("Where args are one or more of:\n");
    printf("  -console           to run as a console application.\n");
    printf("  -LOAD/L            to Load the board\n");
    printf("  -HALT/H            to Halt the board.\n");
    printf("  -RESET/R           to Reset the board. \n");
    printf("  -PRIMARY/P         to set the board as Primary.\n");
    printf("  -BACKUP/B          to set the board as backup.\n");
    printf("  -SHUTDOWN/SD       to shutdown the board.\n");
    printf("  -STANDALONE/SA     to convert to standalone configuration.\n");
    printf("  -STATUS/ST         to get the board status.\n");
    printf("  -help              to display this message.\n");
    printf("\n");
}

