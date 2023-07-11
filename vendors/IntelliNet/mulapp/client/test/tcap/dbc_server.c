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

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <mab_client.h>
#include <dbc_serv.h>
#include <dbc_server.h>

extern ITS_HANDLE ISS7_Stack;


#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        int len = 0; \
        printf("Command entered = %s\n", cmdLine); \
        tmp = strchr(cmdLine,' '); \
        if( !tmp) tmp = strchr(cmdLine, '\t'); \
        if(!tmp) \
        { \
           printf("Usage: %s <cic>\n",x); \
           return; \
        } \
        else \
        { \
          *tmp = 0; tmp++; \
           while(*tmp == ' ' || *tmp == '\t') tmp++; \
           dup = tmp; \
           while( isdigit(*dup) ) dup++; \
           *dup = 0; \
           if( (len = strlen(tmp)) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }

void
ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_INT result = 0;
    ITS_INT ret = 0;
    ITS_HDR hdr;
    ITS_SHORT cic = 0;
    char buf[ITS_PATH_MAX];

    ITS_USHORT startcic = 0;
    ITS_USHORT endcic = 0;

    static OpcDpcInfo info;
    ITS_UINT i;
    ISUP_CIC_INFO *cic_rec = NULL;

    ITS_UINT opc,dpc,sio;
    ITS_OCTET* cic_state;
    ITS_CTXT* vcic;
    int cicval = 0;
    
    MABCL_MESSAGE msg;
 
    MTP3_HEADER mtp3;

    printf("ExecuteCommand: Inside Command \n");

    if (dbc == NULL)
    {
        printf("dbc == NULL DBC failed  ++++\n");
    }
    else if (DBC_Cmd(dbc, "reg", "Register Message","<clientID><routing_criteria><lpc><dpc><ssn><ltid><utid> <lcic><ucic>","<clientID#><routing_criteria#><lpc#><dpc#><ssn#><ltid#><utid#><lcic#><ucic#>"))
    {
        printf("DBC_Cmd : Inside Register Command !!\n");
        ITS_ULONG  clientID = 0; 
        ITS_UINT rc;
        ITS_UINT ssn = 0;
        ITS_INT ltid = 0; 
        ITS_INT utid = 0; 
        ITS_INT lcic = 0; 
        ITS_INT ucic = 0; 
        ITS_INT lpc = 0; 
        ITS_INT dpc = 0; 
        ret = sscanf(cmdLine,"%s %ld %d %d %d %d %d %d %d %d",buf, &clientID, &rc, &lpc, &dpc, &ssn, &ltid, &utid, &lcic, &ucic);
       
        msg.clientID  = clientID;
        msg.msg_type = 0;
        msg.u.regInfo.routing_criteria = rc;
       
        /* fill based on routing criteria */ 
        switch(rc)
        {
            case MABCL_TCAP_RT_TID_RANGE:
            {
               msg.u.regInfo.u.tcap.ltid  = ltid;
               msg.u.regInfo.u.tcap.utid  = utid;
               break;
            }
            case MABCL_TCAP_RT_LPC_DPC_LSSN:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.lpc,lpc);
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.dpc,dpc);
               msg.u.regInfo.u.tcap.ssn = ssn;
               break;
            }
            case MABCL_TCAP_RT_LPC_LSSN:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.lpc,lpc);
               msg.u.regInfo.u.tcap.ssn = ssn;
               break;
            } 
            case MABCL_TCAP_RT_LSSN:
            {
               msg.u.regInfo.u.tcap.ssn = ssn;
               break; 
            }  
            case MABCL_TCAP_RT_LPC:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.lpc,lpc);
               break; 
            }
            case MABCL_TCAP_RT_DPC:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.tcap.dpc,dpc);
               break; 
            }
            case MABCL_ISUP_RT_LPC_CIC_RANGE:
            {
               msg.u.regInfo.u.isup.lcic = lcic;
               msg.u.regInfo.u.isup.ucic = ucic;
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.isup.lpc,lpc); 
               break;
            }  
            case MABCL_ISUP_RT_DPC_CIC_RANGE:
            {
               msg.u.regInfo.u.isup.lcic = lcic;
               msg.u.regInfo.u.isup.ucic = ucic;
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.isup.dpc,dpc);
               break;
            }  
            case MABCL_ISUP_RT_DPC:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.isup.dpc,dpc);
               break;
            }
            case MABCL_ISUP_RT_LPC:
            {
               MTP3_PC_SET_VALUE(msg.u.regInfo.u.isup.lpc,lpc);
               break;
            }
        } 
        
        ret = MABCL_Register(ISS7_Stack, &msg);
    }
    else if (DBC_Cmd(dbc, "unreg", "UnRegister Message", "<clientID><msg_type>",
                      "<clientID#><msg_type#>"))
    {
        printf("DBC_Cmd : Inside UnRegister Command !!\n");

        // Need to send Register Event
        msg.msg_type = 1;
        ret = sscanf(cmdLine, "%s %d %d ", buf, &msg.clientID,
                                 &msg.u.deregInfo.routing_criteria);

        ret = MABCL_Deregister(ISS7_Stack, &msg);
    }
    else if (DBC_Cmd(dbc, "close", "Close Connection", "<connection type>",
                      "<connection type#"))
    {
        ITS_INT type;
        printf("DBC_Cmd : Inside Close Connection Command !!\n");
        ret = sscanf(cmdLine, "%s %d ", buf, &type);    
        ret = MABCL_CloseCon(ISS7_Stack,type);
    }
    else if (DBC_Cmd(dbc, "init", "Close Connection", "<ip><port><conn type>",
                      "<ip#><port#><conn type#>"))
    {
        const char *host;
        ITS_INT port;
        MABCL_CONNECTION_TYPE type;

        printf("DBC_Cmd : Inside Initi Command !!\n");
        host = (const char *) malloc(30);
        ret = sscanf(cmdLine, "%s %s %d %d", buf, host, &port, &type);
        
        ret = MABCL_Initialize(host, port, type);
    } 
    printf("------------------------------------------------------\n");

    return;
}

