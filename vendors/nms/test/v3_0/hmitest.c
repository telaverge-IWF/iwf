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

         if(event.data[0] == VMI_EVN_HALTED)
		 {
			 TIMERS_Sleep(2);
			 printf("Loading Board\n");
			 VMI_SendPrimitive(VMI_LOAD_BOARD, VMI_EVENT_RECEIVER_SRC);

		 }

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

int main()
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



	finished = 0;
    while (!finished)
    {
		printf("\n\t\tVMI Test Program...\n\n");
		
        printf(" 1) Send VMI_BACKUP\n");
        printf(" 2) Send VMI_HALT_BOARD\n");
        printf(" 3) Send VMI_LOAD_BOARD\n");
        printf(" 4) Send VMI_PRIMARY\n");
        printf(" 5) Send VMI_RESET \n");
        printf(" 6) Send VMI_SHUTDOWN  \n");
        printf(" 7) Send VMI_STANDALONE \n");
        printf(" 8) Send VMI_STATUS_REQUEST\n");
		printf(" 9) Quit --> VMI Terminate\n\n");

		printf("Enter choice: ");

		scanf("%c",&choice);

		if (!isdigit(choice))
		{
			printf("Invalid choice\n");
			continue;
		}
		if (choice < '1' || choice > '9')
		{
			printf("Wrong choice\n\n");
			continue;
		}

		switch (choice)
		{
		case '1': 
            VMI_SendPrimitive(VMI_BACKUP,1);
			break;

		case '2': 
            VMI_SendPrimitive(VMI_HALT_BOARD,1);
			break;

		case '3': 
            VMI_SendPrimitive(VMI_LOAD_BOARD,1);
			break;


		case '4': 
            VMI_SendPrimitive(VMI_PRIMARY,1);
			break;

		case '5': 
            VMI_SendPrimitive(VMI_RESET,1);
			break;
		case '6': 
            VMI_SendPrimitive(VMI_SHUTDOWN,1);
			break;
		case '7': 
            VMI_SendPrimitive(VMI_STANDALONE,1);
			break;
		case '8': 
            VMI_SendPrimitive(VMI_STATUS_REQUEST,1);
			break;

        case '9':
			VMI_Terminate();
			/*THREAD_KillThread(&thr);*/
			exit(0);
			



		}
		


        /*for (i = 0; i< 2; i++)*/
		{
            ITS_GetNextEvent(handle, &event);

		    printf("\n\nEvent received: ");

		    for(i = 0; i<event.len; i++)
			{
                printf("0x%02x ",event.data[i]);
			}
		}


    }


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