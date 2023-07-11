/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 * ID: $Id: test.c,v 1.4 2005/07/05 11:37:12 mmanikandan Exp $
 *
 * LOG: $Log: test.c,v $
 * LOG: Revision 1.4  2005/07/05 11:37:12  mmanikandan
 * LOG: Changes for national and international.
 * LOG:
 * LOG: Revision 1.3  2005/05/25 14:47:28  mmanikandan
 * LOG: Changes for CCITT.
 * LOG:
 * LOG: Revision 1.2  2005/05/25 12:33:32  mmanikandan
 * LOG: Changes for CCITT Compilation.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 * LOG:
 ****************************************************************************/
#include <mab_tcap_client.h>
#include "dbc_server.h"
#include <engine.h>
#include <pthread.h>
#include <signal.h>

/* gloabal variables */
ITS_HANDLE ISS7_Stack;

/* public variable */
static char* hostIpAddress;
static int serverPort;
char*  style;
//extern ITS_HANDLE CL_Handle;

//extern ITS_USHORT did;

//SS7TRAN_Manager*     ISS7_ANSI_Stack;
//#define ISS7_Stack   ISS7_ANSI_Stack

#define SEND_UNI           1
#define SEND_BEGIN         2
#define SEND_END           3
#define SEND_CONTINUE      4
#define SEND_ABORT         5
#define DUMP_RT            6
#define SEND_LOOP          7


#if defined(ANSI)
#define PROTOCOL_VERSION_TAG                  (0xDAU)
#define AC_NAME_TAG                           (0xDCU)
#define USER_INFO_TAG                         (0xFDU)
#define PABT_CAUSE_TAG                        (0xD7U)
#define TCPPN_SEQUENCE_TAG                    (0x30U)
#define TCPPN_SET_TAG                         (0xF2U)
#define U_ABORT_INFO_TAG                      (0xD8U)
//#define TCPPT_TC_INVOKE                       (0xE9U)
#endif

static void TCAP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);
void InputMenu();
void *PrintMenu();
void* PrintMenuFunc(void* args);

/* signal handling function */
static void
SignalHandler(int sig)
{
    printf("Terminating TCAP client application\n");
    //CL_CloseConnection(CL_Handle);
    MABCL_CloseCon(ISS7_Stack, 0);
    exit(0);
}
    
/* Forward declarations */
static void* Receive(void* args);

//static void HandleAppEvent(ITS_EVENT *evt);

static int InitClient();

int main(int argc, const char** argv)
{
    pthread_t thread, threadPrint,  thread1;
    int ret =0;

    signal(SIGINT, SignalHandler);


    printf("\n\t *******************************************\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****  IntelliSS7 TCAP Client Test     *****\n");
    printf("\t *******************************************\n\n\n");


    MABCL_PreInitialize(&ISS7_Stack);

    /* Dispatch a new thread to receive event from server */
    pthread_create(&thread, NULL, PrintMenuFunc, NULL);
    pthread_create(&thread1, NULL, Receive, NULL);

    /* Set the application name */
    APPL_SetName("Client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    /* Set the call back function for DBC */
    DBC_SetDoCommand(ExecuteCommand);


    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));

}

void *
PrintMenu()
{
    int  yes = 1;
    for (;;)
    {
        InputMenu();
        printf("\n Enter 1 to Display Menu or 99 to Exit : ");
        scanf("%d", &yes);
        if (yes == 99)
        exit(0);
    }
}


void
InteractiveSendUniDlg()
{
    ITS_HDR hdr;
    MTP3_HEADER hdr3;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    int  invokeCount;
    int j;
    int invokeId, i, ret;
    ITS_CTXT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_UINT opc = 0, dpc = 0;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
#if defined (ANSI)
    addrInd |= SCCP_CPA_ROUTE_NAT;
#elif defined (CCITT)
    addrInd |= SCCP_CPA_ROUTE_INT;
#endif

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    memset(dlg,0,sizeof(TCAP_DLG));
    memset(cpt,0,sizeof(TCAP_CPT));
    printf("\n Enter the opc\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);
    hdr3.sio = 0x83;

    pointCode = opc;
    ssn = 5;
    
    SCCP_EncodeAddr(&dlg->u.uni.orig_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    pointCode = dpc;
    SCCP_EncodeAddr(&dlg->u.uni.dest_addr, addrInd,
                    pointCode, ssn, NULL, 0);
    TCAP_AllocateDialogueId(ISS7_Stack,&localDid);
     printf("Allocated Local DID =  %d",localDid);
    /* Set did */

    /* Set did */
    hdr.context.dialogue_id = localDid;
    printf("\n did value = %d\n", hdr.context.dialogue_id);
    hdr.type = ITS_TCAP;

    /*Set ptype*/
#if defined(ANSI)
    dlg->ptype = TCAP_PT_TC_UNI_ANSI;
#elif defined(CCITT)
    dlg->ptype = TCAP_PT_TC_UNI_CCITT;
#endif
    /* Set opc dpc*/
    MTP3_PC_SET_VALUE(dlg->u.uni.opc, opc);
    MTP3_PC_SET_VALUE(dlg->u.uni.dpc, dpc);

    printf("\n======> How many invokes? <======\n");
    scanf("%d",&invokeCount);

    for (j = 1; j <= invokeCount; j++)
    {
        memset(cpt,0,sizeof(TCAP_CPT));
        printf("\n========> Enter Invoke Id: <======== \n");
        scanf("%d", &invokeId);
        cpt->ptype = TCPPT_TC_INVOKE;
        /* Set Invoke Id*/
        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = invokeId;
#if defined(CCITT) || defined(PRC)
        /* Set Op*/
        cpt->u.invoke.operation.len = 3;
        cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
        cpt->u.invoke.operation.data[1] = 1;
        cpt->u.invoke.operation.data[2] = 2;

        /* Set Param*/
        cpt->u.invoke.param.len = 3;
        cpt->u.invoke.param.data[0] = 0x30;
        cpt->u.invoke.param.data[1] = 1;
        cpt->u.invoke.param.data[2] = 1;

#else

        /* Set Op*/
        cpt->u.invoke.operation.len = 4;
        cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        cpt->u.invoke.operation.data[1] = 2;
        cpt->u.invoke.operation.data[2] = 1;
        cpt->u.invoke.operation.data[3] = 2;
        
        /* Set Param*/
        cpt->u.invoke.param.len = 3;
        cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;  
        cpt->u.invoke.param.data[1] = 1;
        cpt->u.invoke.param.data[2] = 1; 
#endif
        #if 0
        for (i = 2; i<6;i++)
        {
            cpt->u.invoke.param.data[i] = i;
        }
        #endif 
        ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt); 
        if (ret == ITS_SUCCESS)
        {
            printf("\n Component Sent successfully:Invoke Id = %d",
                    invokeId);
        }
        PrintComponent(cpt);
    }

    ret = TCAP_SendDialogue(ISS7_Stack, &hdr, dlg);
        
    if (ret == ITS_SUCCESS)
    {
        printf("\n UNI Dialogue Sent successfully\n");
        PrintDialoge(dlg);
    }
    else
    {
        printf("\n Failed to send the UNI Dialogue\n");
    }

    if (dlg)
    {
      free(dlg);
    }

    if (cpt)
    {
      free(cpt);
    }
}

void
InteractiveSendBeginDlg()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int  invokeCount, ret ;
    int invokeId, i, j, input;
    ITS_CTXT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_UINT opc = 0, dpc = 0;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));
    memset(dlg,0,sizeof(TCAP_DLG));
    memset(cpt,0,sizeof(TCAP_CPT));

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
#if defined (ANSI)
    addrInd |= SCCP_CPA_ROUTE_NAT;
#elif defined (CCITT)
    addrInd |= SCCP_CPA_ROUTE_INT;
#endif
    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);

    hdr3.sio = 0x83;
    
    //pointCode = MTP3_PC_GET_VALUE(hdr3.label.opc);

    //printf("\n OPC = %d\n", pointCode);
    ssn = 5;

    SCCP_EncodeAddr(&dlg->u.begin.orig_addr, addrInd,
                    opc, ssn, NULL, 0);

    //pointCode = MTP3_PC_GET_VALUE(hdr3.label.dpc);
    SCCP_EncodeAddr(&dlg->u.begin.dest_addr, addrInd,
                    dpc, ssn, NULL, 0);

    TCAP_AllocateDialogueId(ISS7_Stack,&localDid);
    printf("Allocated Local DID =  %d",localDid);

    /* Set did */
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;

    #if defined(CCITT) || defined(PRC)
      dlg->ptype = TCPPT_TC_BEGIN;
    #else
    /*Set ptype*/
    printf("\nEnter 1 for QWP and 2 for QWOP::\n");
    scanf ("%d",&input);

    if (input == 1)
    {
        dlg->ptype = TCAP_PT_TC_QUERY_W_PERM_ANSI;
    }
    else
    {
       dlg->ptype = TCAP_PT_TC_QUERY_WO_PERM_ANSI;
    }
    #endif

    /* Set opc dpc*/
    MTP3_PC_SET_VALUE(dlg->u.begin.opc, opc);
    MTP3_PC_SET_VALUE(dlg->u.begin.dpc, dpc);

    printf("\n======> How many invokes? <======\n");
    scanf("%d",&invokeCount);

    for (j = 1; j <= invokeCount; j++)
    {
        printf("\n========> Enter Invoke Id: <======== \n");
        scanf("%d", &invokeId);
        cpt->ptype = TCPPT_TC_INVOKE;
        /* Set Invoke Id*/
        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = invokeId;

        #if defined(CCITT) || defined(PRC)
        /* Set Op*/
        cpt->u.invoke.operation.len = 3;
        cpt->u.invoke.operation.data[0] = TCPPN_GLOBAL_OP_TAG;
        cpt->u.invoke.operation.data[1] = 1;
        cpt->u.invoke.operation.data[2] = 2;

        /* Set Param*/
        cpt->u.invoke.param.len = 3;
        cpt->u.invoke.param.data[0] = 0x30;
        cpt->u.invoke.param.data[1] = 1;
        cpt->u.invoke.param.data[2] = 1;

        #else
        /* Set Op*/
        cpt->u.invoke.operation.len = 4;
        cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        cpt->u.invoke.operation.data[1] = 2;
        cpt->u.invoke.operation.data[2] = 1;
        cpt->u.invoke.operation.data[3] = 2;

        /* Set Param*/
        cpt->u.invoke.param.len = 3;
        cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;
        cpt->u.invoke.param.data[1] = 1;
        cpt->u.invoke.param.data[2] = 1;
        #endif
#if 0
        for (i = 2; i<10;i++)
        {
            cpt->u.invoke.param.data[i] = i;
        }
#endif 
        ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);
        if (ret == ITS_SUCCESS)
        {
            printf("\n Component Sent successfully:Invoke Id = %d",
                    invokeId);
           PrintComponent(cpt);
        }
    }
    ret = TCAP_SendDialogue(ISS7_Stack, &hdr, dlg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n Dialogue Sent successfully");
        PrintDialoge(dlg);
    }
    else
    {
        printf("Failed to send the Dialogue\n");
    }
    return;
}

void
InteractiveSendEnd()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int numResult = 0, outcome = 0; 
    int invokeId, i, ret;
    int resNL, failure;
    //ITS_CTXT localDid;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT opc = 0, dpc = 0;
    ITS_UINT rejectType, errorcode;
    ITS_UINT rejectCode; 

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
#if defined (ANSI)
    addrInd |= SCCP_CPA_ROUTE_NAT;
#elif defined (CCITT)
    addrInd |= SCCP_CPA_ROUTE_INT;
#endif

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));
    memset(dlg,0,sizeof(TCAP_DLG));
    memset(cpt,0,sizeof(TCAP_CPT));

    #if defined(CCITT) || defined(PRC)
    /* set the ptype */
    dlg->ptype = TCPPT_TC_END;
    #else
    dlg->ptype = TCPPT_TC_RESP;
    #endif

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);
    hdr3.sio = 0x83;
  
    /* Set did */
    printf("\n Enter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;
    printf("Sending END on DID == %d", localDid);
    printf("\n OutCome of transaction (1-success, 0-failure) ? \n");
    scanf ("%d",&outcome);
    if (outcome == 1)
    {
        printf("\nHow Many return Results ?\n");
        scanf ("%d" , &numResult);
        for ( i = 0;i < numResult; i ++)
        {
            printf("\n Enter \"0\" for RET_RES_NOT_LAST,"
                   " \"1\" for RET_RES_LAST:");
            scanf("%d" ,&resNL);
            if (resNL == 0)
            {
                cpt->ptype = TCPPT_TC_RESULT_NL;
            }
            else if (resNL == 1)
            {
                cpt->ptype = TCPPT_TC_RESULT_L;
            }
            printf("\n Enter Invoke ID\n");
            scanf("%d" , &invokeId);
            cpt->u.result.invoke_id.len = 3;
            cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.result.invoke_id.data[1] = 1;
            cpt->u.result.invoke_id.data[2] = invokeId;
#if defined(CCITT)
            /* Set Op*/
            cpt->u.result.operation.len = 4;
            cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.result.operation.data[1] = 2;
            cpt->u.result.operation.data[2] = 1;

            /* Set Param*/
            cpt->u.result.param.len = 4;
            cpt->u.result.param.data[0] = 0x30;
            cpt->u.result.param.data[1] = 2;
            cpt->u.result.param.data[2] = 1;
            cpt->u.result.param.data[3] = 2;
#endif

#if defined(ANSI)
            /* Set Param*/
            cpt->u.result.param.len = 4;
            cpt->u.result.param.data[0] = TCPPN_SET_TAG;
            cpt->u.result.param.data[1] = 2;
            cpt->u.result.param.data[2] = 1;
            cpt->u.result.param.data[3] = 2;
#endif

            ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);
             if(ret == ITS_SUCCESS)
             {
                  printf("\n TCAP_Comp RESULT send successful");
             }
             else
             {
                 printf("\n TCAP_Comp RESULT send failed\n");
             }
        }
    }
    else
    {
        printf("\nChoose 0 for ReturnError or 1 for Reject\n");
        scanf("%d", &failure);
        if (failure == 1)
        {
            #if defined(CCITT) 
            cpt->ptype = TCPPT_TC_R_REJECT;
            #else
            cpt->ptype = TCPPT_TC_REJECT;
            #endif 
            printf("\n Enter Invoke ID \n");
            scanf("%d" , &invokeId);
            cpt->u.reject.invoke_id.len = 3;
            cpt->u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.reject.invoke_id.data[1] = 1;
            cpt->u.reject.invoke_id.data[2] = invokeId;
            printf("\n Enter reject Type [128 - 131]:\n"); 
            scanf("%d", &rejectType);
            printf("\n Enter Reject Code \n");
            scanf("%d" , &rejectCode); 
#if defined(CCITT) || defined(PRC)
            cpt->u.reject.problem.len = 3;
            cpt->u.reject.problem.data[0] = rejectType;
            cpt->u.reject.problem.data[1] = 1;
            cpt->u.reject.problem.data[2] = rejectCode;
#else
           
            /* Set the Problem Type and Code */
            cpt->u.reject.problem.len = 4;
            cpt->u.reject.problem.data[0] = TCPPROB_IDENT;
            cpt->u.reject.problem.data[1] = 2;
            cpt->u.reject.problem.data[2] = 1;
            cpt->u.reject.problem.data[3] = rejectCode;
            //hasProblem = true;
#endif
        }
        else 
        {
            #if defined(CCITT) || defined(PRC)
               cpt->ptype = TCPPT_TC_U_ERROR;
            #elif defined(ANSI)
               cpt->ptype = TCPPT_TC_ERROR;
            #endif
            printf("\n Enter Invoke ID \n");
            scanf("%d" , &invokeId);
            cpt->u.error.invoke_id.len = 3;
            cpt->u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.error.invoke_id.data[1] = 1;
            cpt->u.error.invoke_id.data[2] = invokeId;
            printf("\n Enter Error Code \n");
            scanf("%d" , &errorcode); 

#if defined(CCITT) || defined(PRC)
            cpt->u.error.error.len =3;
            cpt->u.error.error.data[0] = TCPPN_LOCAL_ERR_TAG;
            cpt->u.error.error.data[1] = 1;
            cpt->u.error.error.data[2] = errorcode; 
#else
            /* Set The Error code */
            cpt->u.error.error.len = 3;
            cpt->u.error.error.data[0] = 1;
            cpt->u.error.error.data[1] = 1;
            cpt->u.error.error.data[2] = errorcode;
            //hasError = true;
#endif
        }    
        ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);
        if (ret ==ITS_SUCCESS)
        {
           printf("\nTCAP_Comp RESULT sent successfully\n");
           PrintComponent(cpt);
        }
        else
        {
            printf("TCAP_Comp RESULT failed to send.:\n");
        }
    } /* End of Else */

    ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg);
    if ( ret != ITS_SUCCESS) 
    {
        printf("\nFailed to send the END Dialogue \n");
        PrintDialoge(dlg);
    }  
    else
    {
        printf("\nEND Dialogue sent successfully\n");
    }
} 

void
InteractiveSendContinue()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int numResult = 0, invokeCount;
    int ErrorCode;
    int invokeId, i, j;
    int input,ret,resNL;
    //ITS_CTXT localDid;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode = 0, opc = 0, dpc = 0;
    ITS_OCTET ssn;

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
#if defined (ANSI)
    addrInd |= SCCP_CPA_ROUTE_NAT;
#elif defined (CCITT)
    addrInd |= SCCP_CPA_ROUTE_INT;
#endif

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));
    memset(dlg,0,sizeof(TCAP_DLG));
    memset(cpt,0,sizeof(TCAP_CPT));

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    #if 0
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    #endif
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);

    hdr3.sio = 0x83;

    //pointCode = MTP3_PC_GET_VALUE(hdr3.label.opc);
    //printf("\n OPC = %d\n", pointCode);

    ssn = 5;

    SCCP_EncodeAddr(&dlg->u.cont.orig_addr, addrInd,
                    opc, ssn, NULL, 0);

    MTP3_PC_SET_VALUE(dlg->u.cont.opc, opc);

    #if 0
    SCCP_EncodeAddr(&dlg->u.begin.orig_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    pointCode = MTP3_PC_GET_VALUE(hdr3.label.dpc);
    SCCP_EncodeAddr(&dlg->u.begin.dest_addr, addrInd,
                    pointCode, ssn, NULL, 0);
    #endif

    #if defined(CCITT) || defined(PRC)
    
    /* set the ptype */
        dlg->ptype = TCPPT_TC_CONTINUE;
    #else

    printf("\n Enter \"1\" for CONV_WO_PERM \"2\" for CONV_W_PERM \n");
    scanf("%d",&input);
    if (input == 1)
    {
        /*Set ptype*/
        dlg->ptype = TCPPT_TC_CONV_WO_PERM;
    }
    else
    {
        dlg->ptype = TCPPT_TC_CONV_W_PERM;
    }
    #endif
    /* Set did */
    printf("\n Enter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;

    printf("\n Enter - \"1\" for Return Result & Invoke Component \n "
             " Enter - \"0\" for Error Component\n");
    scanf("%d",&input);
    if (input == 1)
    {
        printf("\n How many Return Results? \n");
        scanf("%d",&numResult);
        for (i = 0; i < numResult; i++)
        {
            printf("\n Enter \"1\" for RET_RES_NOT_LAST \n"
                     " Enter \"0\" for RET_RES_LAST: \n");
            scanf("%d",&resNL);
            if (resNL == 1)
            {
                cpt->ptype = TCPPT_TC_RESULT_NL;
            }
            else
            {
                cpt->ptype = TCPPT_TC_RESULT_L;
            }

            printf("\n========> Enter Invoke Id: <======== \n");
            scanf("%d", &invokeId);
            //cpt->ptype = TCAP_PT_TC_RESULT_L_ANSI;
            /* Set Invoke Id*/
            cpt->u.result.invoke_id.len = 3;
            cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.result.invoke_id.data[1] = 1;
            cpt->u.result.invoke_id.data[2] = invokeId;
#if defined(CCITT)
            /* Set Op*/
            cpt->u.result.operation.len = 4;
            cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.result.operation.data[1] = 2;
            cpt->u.result.operation.data[2] = 1;

            /* Set Param*/
            cpt->u.result.param.len = 4;
            cpt->u.result.param.data[0] = 0x30;
            cpt->u.result.param.data[1] = 2;
            cpt->u.result.param.data[2] = 1;
            cpt->u.result.param.data[3] = 2;
#endif

#if defined(ANSI)
            /* Set Param*/
            cpt->u.result.param.len = 4;
            cpt->u.result.param.data[0] = TCPPN_SET_TAG;
            cpt->u.result.param.data[1] = 2;
            cpt->u.result.param.data[2] = 1;
            cpt->u.result.param.data[3] = 2;
#endif
    
            ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);
            if (ret ==ITS_SUCCESS)
            {
                printf("TCAP_Comp RESULT send success:\n");
            }
            else
            {
                printf("TCAP_Comp RESULT failed to send.:\n");
            }
        }

        printf("\nHow many Invokes? \n");
        scanf("%d", &invokeCount);
        for (j = 1; j <= invokeCount; j++)
        {
            printf("\n========> Enter Invoke Id: <======== \n");
            scanf("%d", &invokeId);
            cpt->ptype = TCPPT_TC_INVOKE;
            /* Set Invoke Id*/
            cpt->u.invoke.invoke_id.len = 3;
            cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.invoke.invoke_id.data[1] = 1;
            cpt->u.invoke.invoke_id.data[2] = invokeId;
#if defined(CCITT) || defined(PRC)
            cpt->u.invoke.operation.len = 3;
            cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.invoke.operation.data[1] = 1;
            cpt->u.invoke.operation.data[2] = 2;
 
            /* Set Param*/
            cpt->u.invoke.param.len = 3;
            cpt->u.invoke.param.data[0] = 0x30;
            cpt->u.invoke.param.data[1] = 1;
            cpt->u.invoke.param.data[2] = 1;


#else
            /* Set Op*/
            cpt->u.invoke.operation.len = 4;
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] = 1;
            cpt->u.invoke.operation.data[3] = 2;

            /* Set Param*/
            cpt->u.invoke.param.len = 5;
            cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;
            cpt->u.invoke.param.data[1] = 3;
            cpt->u.invoke.param.data[2] = 10;
            cpt->u.invoke.param.data[3] = 10;
            cpt->u.invoke.param.data[4] = 10;
#endif
            #if 0

            for (i = 2; i<10;i++)
            {
                cpt->u.invoke.param.data[i] = i;
            }

            #endif

            ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);

            if (ret ==ITS_SUCCESS)
            {
                printf("TCAP_Comp INVOKE send success:\n");
                PrintComponent(cpt);
            }
            else
            {
                printf("TCAP_Comp INVOKE send failed:\n");
            }
        }
   } /* End of case 1 */

   /*case for ERROR Component */
   else if (input == 0)
   {
       #if defined(CCITT) || defined(PRC)
        cpt->ptype = TCPPT_TC_U_ERROR;
    #elif defined(ANSI)
       cpt->ptype = TCPPT_TC_ERROR;
    #endif

       printf( "\nEnter Invoke Id: \n");
       scanf("%d",&invokeId);
       cpt->u.error.invoke_id.len = 3;
       cpt->u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
       cpt->u.error.invoke_id.data[1] = 1;
       cpt->u.error.invoke_id.data[2] = invokeId;

       printf("\n Enter Error Code: \n");
       scanf("%d",&ErrorCode);

#ifdef ANSI
       cpt->u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
       cpt->u.error.error.data[1] = 1;
       cpt->u.error.error.data[2] = ErrorCode;
#elif defined CCITT
       cpt->u.error.error.data[0] = ErrorCode;
#endif

       ret = TCAP_SendComponent(ISS7_Stack, &hdr,cpt);
       if (ret ==ITS_SUCCESS)
       {
           printf("TCAP_Comp ERROR send success:\n");
       }
       else
       {
           printf("TCAP_Comp ERROR failed to send.:\n");
       }
   }     /* End of ERROR Component */

   ret = TCAP_SendDialogue(ISS7_Stack, &hdr, dlg);
   if (ret == ITS_SUCCESS)
   {
       printf("\n Continue Dialogue Sent successfully\n");
       PrintDialoge(dlg);
   } 
   else
   {
      printf("\n Failed to send the Continue Dialogue\n");
   }
}

void
InteractiveSendAbort()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg;
    TCAP_CPT* cpt;
    //ITS_CTXT localDid;
    ITS_UINT abortReason; 
    int ret, input = 0;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
#if defined (ANSI)
    addrInd |= SCCP_CPA_ROUTE_NAT;
#elif defined (CCITT)
    addrInd |= SCCP_CPA_ROUTE_INT;
#endif

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    memset(dlg,0,sizeof(TCAP_DLG));
    memset(cpt,0,sizeof(TCAP_CPT));

    #if defined(CCITT) || defined(PRC)
    printf("\nEnter 1 for P ABORT and 2 for U ABORT::\n");
    scanf ("%d",&input);

    if (input == 1)
    {
        dlg->ptype = TCPPT_TC_P_ABORT;
    }
    else
    {
       dlg->ptype = TCPPT_TC_P_ABORT;
    }
    #else
    
    dlg->ptype = TCPPT_TC_ABORT;
    #endif

    printf("\nEnter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;

    printf("\n Enter the abort Reason \n");
    scanf("%d" ,&abortReason);
    dlg->u.abort.abort_reason = abortReason;
    /* Set the Abort Info */ 
   
    dlg->u.abort.abort_info.len = 3;
    dlg->u.abort.abort_info.data[0] = 0xd8;
    dlg->u.abort.abort_info.data[1] = 0x01;
    dlg->u.abort.abort_info.data[1] = 0x01; 

    /* Send the Dialogue */
    ret = TCAP_SendDialogue(ISS7_Stack, &hdr, dlg); 
    if (ret != ITS_SUCCESS)
    {
        printf("\nFailed to send the ABORT Dialogue\n");
        PrintComponent(cpt); 
    }    
    else
    {
        printf("Successfully sent the ABORT Dialogue \n");
    }
}

void
InputMenu()
{
    ITS_INT val = 0;

    while(val < 1 || val > 5 )
    {
        printf("\n===> 1 - Initiate Transaction - TC_Uni.    <===");
        printf("\n===> 2 - Initiate Transaction - TC_Begin.  <===");
        printf("\n===> 3 - Close Transaction - TC_End.       <===");
        printf("\n===> 4 - Continue Transaction - TC_Continue.<===");
        printf("\n===> 5 - Abort Transaction - TC_Abort.      <===");
        printf("\n===> 99 - Exit                              <===\n");
        
        scanf("%d", &val);

        if ( val == 99)
        {
            exit(0);
        }
    } 

    switch (val)
    {
    case SEND_UNI:
        InteractiveSendUniDlg();
        break;

    case SEND_BEGIN:
        InteractiveSendBeginDlg();
        return;
        break;

    case SEND_END:
        InteractiveSendEnd();
        break;

    case SEND_CONTINUE:
        InteractiveSendContinue();
        break;

    case SEND_ABORT:
        InteractiveSendAbort();
        break;

    default:
        break;
    }
}


/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */
int InitClient()
{
    int flag = ITS_SUCCESS;
    int ret =0;
    //CL_REG_INFO rInfo;
    ITS_UINT opcIn, dpcIn, ssnIn;
    //ITS_OCTET ssnIn;

    #if 0

    do 
    {
        /* Method binds client app with server on specified 
         *  ipaddress and port 
         */
        CL_Handle = CL_Initialize(hostIpAddress, serverPort); 
        if (CL_Handle == NULL)
        {
            printf("Client Connect to Server failed\n");
            sleep(5);
            flag = (!ITS_SUCCESS);
        }
        else
        {
            flag = ITS_SUCCESS;
            fflush(stdout);
        }

    } while(flag != ITS_SUCCESS);

    /* Compose routing info for list of routing keys*/
    memset(&rInfo, 0, sizeof(CL_REG_INFO));

    rInfo.route_style = GetRouteStyle(style);
    printf("ROUTE_STYLE is %s \n",style);

    MTP3_HDR_SET_SIO(rInfo,0x83);
    switch (rInfo.route_style)
    {
    case DPC:
        //fflush(stdout);
        printf("Enter the DPC\n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf( "DPC = %d\n", dpcIn);
        break;

    case SSN:
        //fflush(stdout);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf( "SSN = %d\n", ssnIn);
        break;

    case OPC_DPC:
       // fflush(stdout);
        printf("Enter OPC \n");
        scanf("%d",&opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("Enter DPC \n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d DPC = %d\n ", opcIn,dpcIn);
        break;

    case DPC_SIO:
        //fflush(stdout);
        printf("Enter DPC \n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d SIO = %d \n", opcIn,rInfo.sio);
        break;

    case DPC_SSN:
        //fflush(stdout);
        printf("Enter DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d SSN = %d\n ", opcIn,ssnIn);
        break;

    case OPC_DPC_SIO:
        //fflush(stdout);
        printf("\n Enter the OPC \n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("\n Enter the DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d DPC = %d SIO = %d\n",opcIn ,dpcIn,rInfo.sio);
        break;

    case OPC_DPC_SSN:
        //fflush(stdout);
        printf("\n Enter the OPC \n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("\n Enter the DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d DPC= %d SIO= %d SSN = %d",
               opcIn, dpcIn,rInfo.sio,ssnIn);
       break;

    case OPC_DPC_SIO_SSN:
        //flush(stdout);
        printf("Enter the OPC\n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("Enter the DPC\n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d DPC = %d SIO = %d SSN = %d \n",
                opcIn,dpcIn,rInfo.sio,rInfo.ssn);
        break;

    default:
        printf("\n Invalid Option\n");
        break;
    }

    /* Register with the server */
    ret = CL_Register(CL_Handle, &rInfo, 1);
  
    #endif
        MABCL_Initialize(hostIpAddress, serverPort,0); 

    if (ret  == ITS_SUCCESS)
    {
        printf("\nCL_Register: Successfully Regitered the client \n");
    }

    return ret;
}

/* 
 * This Function runs as a separate thread to 
 * receive event from the Server and waits for 
 * establishing connection with server
 */
void* Receive(void* args)
{
    ITS_EVENT evt;
    ITS_INT ret=0, i;
    TCAP_DLG dlg;
    TCAP_CPT cpt;
    ITS_HDR hdr;
    signal(SIGINT, SignalHandler);
    while(1)
    {
        printf("Reading Event\n");
        /* Receive event from the server */
        ret = MABCL_GetNextEvent(ISS7_Stack, &evt);
        #if 0
        printf("event len:%d\n",evt.len);
        for(i=0;i<evt.len;i++)
        {
            if ((i + 1) % 16 == 0) printf("\n");
            printf("%02x ",evt.data[i]);
        }
        printf("\n");
        #endif

        switch(evt.src)
        {
            case ITS_TCAP_SRC: 
            {
               if (evt.data[0] == ITS_TCAP_CPT) 
               {
                  TCAP_ReceiveComponent(ISS7_Stack,
                                             &evt,
                                             &hdr,  
                                             &cpt); 
                  /* print the dlgid */
                  printf("Dlg Id:%d\n",hdr.context.dialogue_id);

                  /* print the comp */
                  PrintComponent(&cpt);
               }
               else
               {
                  TCAP_ReceiveDialogue(ISS7_Stack,
                                             &evt,
                                             &hdr,  
                                             &dlg); 
                  /* print the dlgid */
                  printf("Dlg Id:%d\n",hdr.context.dialogue_id);

                  /* print the dlg*/
                  PrintDialoge(&dlg);
               }
               break;
            }
            default:
            {
                for(i=0;i<evt.len;i++)
                {
                  if ((i + 1) % 16 == 0) printf("\n");
                    printf("%02x ",evt.data[i]);
                }
                printf("\n");
            }
        }


        //HandleAppEvent(&evt);

        /* Free the Event we no longer require it */
       /* Terminate the event */ 
       ITS_EVENT_TERM(&evt);
       fflush(stdout);
    }
}
void* PrintMenuFunc(void* args)
{
    PrintMenu();
}

/* 
 * This function will Handle the application events
 * It decodes the events and prints the contents
 */

#if 0
void HandleAppEvent(ITS_EVENT *evt)
{
    CL_TCAP_REG_ENTRY  regInfo;

    int ret =0;

    switch (evt->data[0])
    {
    case CL_TCAP_ALLOC_DID_RESP:
        did = 0;
        did |= evt->data[1];
        did |= evt->data[2] & (did << 8);
        printf("\n Got ALLOC DID %d\n", did);
        break;

    case CL_TCAP_REGISTER_RESP:
        printf("HandleAppEvent: Received Register Response\n");

        ret = TCAP_ReceiveRegisterIndication(CL_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d SSN = %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.reg_info),
                MTP3_RL_GET_DPC_VALUE(regInfo.reg_info),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.reg_info) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),regInfo.reg_info.ssn);
        break;
    case CL_TCAP_DEREGISTER_RESP:
        printf("HandleAppEvent: Received DeRegister Response\n");

        ret = TCAP_ReceiveDeRegisterIndication(CL_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC = %d SIO = %d SSN = %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.reg_info),
                MTP3_RL_GET_DPC_VALUE(regInfo.reg_info),
                (ITS_OCTET)
                (MTP3_HDR_GET_SIO(regInfo.reg_info) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),
                regInfo.reg_info.ssn);
        break;

    default:
        printf("\n\nHandleAppEvent :: Received TCAP Event From Server\n");
        TCAP_ReceiveMsg(CL_Handle, evt);
        break;
    }
}

#endif

/*************************************************************************
* Purpose : This function  handles messages received from Server.
*
* Inputs :   Handle and received event
*
* Return Value :
*
**************************************************************************/
static void
TCAP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)
{
    switch ( event->data[0] )
    {
    case ITS_TCAP_DLG:
        printf("\n TCAP_ReceiveMsg:: Dialogue\n");
        break;

    case ITS_TCAP_CPT:
        printf("\n TCAP_ReceiveMsg:: Component\n");
        break;

    default:
        printf("\n TCAP_ReceiveMsg:: Neither Dialogue nor Cpt\n");
        break;
    }
    return;
}

/*************************************************************************
* Purpose : This function returns the routing style 
* used for the registration and for routing messages.
*
* Input : style as string 
* [This is a command line argument for the time being]
*
* Return Value :route_style
*
**************************************************************************/

#if 0
int
GetRouteStyle(char* style)
{
    CL_REG_INFO rInfo;
    if(strcmp(style,ROUTE_DPC_STRING) == 0)
    rInfo.route_style = DPC;
    else if(strcmp(style,ROUTE_SSN_STRING) == 0)
    rInfo.route_style = SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_STRING) == 0)
    rInfo.route_style = OPC_DPC;
    else if(strcmp(style,ROUTE_DPC_SIO_STRING) == 0)
    rInfo.route_style = DPC_SIO;
    else if(strcmp(style,ROUTE_DPC_SSN_STRING) == 0)
    rInfo.route_style = DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_STRING) == 0)
    rInfo.route_style = OPC_DPC_SIO;
    else if(strcmp(style,ROUTE_OPC_DPC_SSN_STRING) == 0)
    rInfo.route_style = OPC_DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_SSN_STRING) == 0)
    rInfo.route_style = OPC_DPC_SIO_SSN;
    return rInfo.route_style;
}
#endif
