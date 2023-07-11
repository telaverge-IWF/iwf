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
 ****************************************************************************/

#include <mab_isup_client.h>
#include "dbc_server.h"
#include <pthread.h>
#include <signal.h>

/* gloabal variables */
ITS_HANDLE CL_Handle;

/* public variable */
static char* primeIpAddress;
static int primeServerPort;
static char* backupIpAddress;
static int backupServerPort;

/* signal handling function */
static void
SignalHandler(int sig)
{
    printf("Terminating ISUP client application\n");
    MABCL_CloseCon(CL_Handle,0);
    exit(0);
}
    
/* Forward declarations */
static void* Receive(void* args);

static void HandleAppEvent(ITS_EVENT *evt);

static int InitClient(const char* primeipAddress, ITS_INT primePort,
               const char* backupipAddress, ITS_INT backupPort);

int main(int argc, const char **argv)
{
    pthread_t thread;
    int ret =0;

    signal(SIGINT, SignalHandler);

    MABCL_PreInitialize(&CL_Handle);
    

    printf("\n\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****  IntelliSS7 ISUP Client Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n\n\n");
      
    /* Dispatch a new thread to receive event from server */
    pthread_create(&thread, NULL, Receive, NULL);

    /* Set the application name */
    APPL_SetName("Client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    /* Set the call back function for DBC */
    DBC_SetDoCommand(ExecuteCommand);
 
    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
}


/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */
#if 0
int InitClient(const char* primeipAddress, ITS_INT primePort,
               const char* backupipAddress, ITS_INT backupPort)
{
    MTP3_HEADER hdr;
    int flag = ITS_SUCCESS;
    int ret =0;

     //MABCL_PreInitialize();
   //do 
    //{
        /* Method binds client app with server on specified 
         *  ipaddress and port 
         */
        MABCL_Initialize(primeipAddress, primePort, 
                         MABCL_PRIMARY_CONNECTION, &CL_Handle); 
        if (CL_Handle == NULL)
        {
            printf("Client Connect to Primary Server failed\n");
            sleep(5);
            flag = (!ITS_SUCCESS);
        }
        else
        {
            flag = ITS_SUCCESS;
            fflush(stdout);
        }


        MABCL_Initialize(backupipAddress, backupPort, 
                         MABCL_BACKUP_CONNECTION, &CL_Handle); 
        if (CL_Handle == NULL)
        {
            printf("Client Connect to Primary Server failed\n");
            sleep(5);
            flag = (!ITS_SUCCESS);
        }
        else
        {
            flag = ITS_SUCCESS;
            fflush(stdout);
        }
    //} while(flag != ITS_SUCCESS);

    /* Compose MTP3 headers for list of OPC,DPC,SIO */

    MABCL_MESSAGE msg;
    int tmpPc=0;   
    printf(" Enter the client : \n");
    scanf("%d",&msg.clientID);

    printf(" Enter the msg_type : \n");
    scanf("%d",&msg.msg_type);

    printf(" Enter the routing criteria");
    scanf("%d",&msg.u.regInfo.routing_criteria);

    switch(msg.u.regInfo.routing_criteria)
    {
         case MABCL_TCAP_RT_LPC_DPC_LSSN:
              printf("Enter the lpc \n");
              scanf("%X",&tmpPc);
              fflush(stdout);
              MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.lpc,tmpPc);
              printf("Enter the dpc \n");
              scanf("%X",&tmpPc); 
              MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.dpc,tmpPc);
              printf("Enter the ssn \n");
              scanf("%d",&msg.u.regInfo.u.tcap.ssn);
              break;
    
    }         
    /* Register with the server */
    ret = MABCL_Register(CL_Handle, &msg);
    if (ret  == ITS_SUCCESS)
    {
        printf("CL_Register: Successfully Regitered the client \n");
    }

    return ret;
}
#endif
/* 
 * This Function runs as a separate thread to 
 * receive event from the Server and waits for 
 * establishing connection with server
 */
void* Receive(void* args)
{
    ITS_EVENT evt;
    ITS_INT ret=0,i=0;
    signal(SIGINT, SignalHandler);
    CL_Handle = MABCL_GetHandle(); 

    while(1)
    {
        /* Receive event from the server */
        ret = MABCL_GetNextEvent(CL_Handle, &evt);
        printf("Event from task Q : event len:%d\n",evt.len);
        for(i=0;i<evt.len;i++)
        {
            if ((i + 1) % 16 == 0) printf("\n");
            printf("%02x ",evt.data[i]);
        }
        printf("\n");


         
        HandleAppEvent(&evt);

        /* Free the Event we no longer require it */
        ITS_EVENT_TERM(&evt);
        fflush(stdout);
    }
}

/* 
 * This function will Handle the application events
 * It decodes the events and prints the contents
 */
void HandleAppEvent(ITS_EVENT *evt)
{
    MABCL_ISUP_RSV_CIC_ENTRY reserveCic;
    MABCL_ISUP_UNRSV_CIC_ENTRY unreserveCic;
    MABCL_REGISTER_ACK regInfo;
    MABCL_DEREGISTER_ACK regInfo1;
    int ret =0;

    switch (evt->data[sizeof(ITS_ULONG)])
    {
    case ISUP_RSV_CIC_ACK_MSG:
        ret = ISUP_ReceiveReserveCICIndication(CL_Handle, evt, &reserveCic);

        printf("HandleAppEvent: Received ReserveCIC responsen\n");
        printf("VCIC = %d : CIC = %d cic_state = %d : ret = %d\n",
               reserveCic.vcic, reserveCic.cic,
               reserveCic.cic_state,reserveCic.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(reserveCic.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(reserveCic.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(reserveCic.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));


        break;

    case ISUP_URSV_CIC_ACK_MSG:
        ret = ISUP_ReceiveUnReserveCICIndication(CL_Handle, evt, &unreserveCic);

        printf("HandleAppEvent: Received Un ReserveCIC response: \n");
        printf("CIC = %d : ret = %d\n",
                unreserveCic.cic, unreserveCic.ret);
        #if 0
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        #endif
        break;

    case REGISTER_ACK_MSG:
        printf("HandleAppEvent: Received Register Response\n");

        ret = MABCL_ReceiveRegisterIndication(CL_Handle, evt, &regInfo);
        #if 0
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        #endif
        break;

    case DERGISTER_ACK_MSG:
        printf("HandleAppEvent: Received DeRegister Response\n");
        

        ret = MABCL_ReceiveDeRegisterIndication(CL_Handle, evt, &regInfo1);
        #if 0
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        #endif
        break;

    default:
           
        /* This will handle all other message including
         * ISUP msgs,
         * Information indications,
         * time out indiactions,
         * error indications .
         * See the defintion in printISUPMsg.c
         */
        printf("\n\n--- Received ISUP Event From Server --");
        ISUP_ReceiveMsg(CL_Handle, evt);
        break;
    }
}

