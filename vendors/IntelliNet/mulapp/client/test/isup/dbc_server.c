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
#include <mab_cmn.h>
#include <dbc_serv.h>
#include <dbc_server.h>

extern ITS_HANDLE CL_Handle;


SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;

#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

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

    printf("------------------------------------------------------\n");

    if (DBC_Cmd(dbc, "acm", "SendACM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("acm");
        result = TestSendACMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }   
    else if (DBC_Cmd(dbc, "anm", "SendANM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("anm");
        result = TestSendANMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send ANM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "bla", "SendBLA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("bla");
        result = TestSendBLARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send BLA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "blo", "SendBLO", "<cic>", ""))
    {
        VALIDATE_CMDLINE("blo");
        result = TestSendBLORequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send BLO return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ccr", "SendCCR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ccr");
        result = TestSendCCRRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CCR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cfn", "SendCFN", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cfn");
        result = TestSendCFNRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CFN return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgb", "SendCGB", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgb");
        result = TestSendCGBRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CGB return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgba", "SendCGBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgba");
        result = TestSendCGBARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CGBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgu", "SendCGU", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgu");
        result = TestSendCGURequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CGU return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgua", "SendCGUA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgua");
        result = TestSendCGUARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CGUA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cot", "SendCOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cot");
        result = TestSendCOTRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send COT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cpg", "SendCPG", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cpg");
        result = TestSendCPGRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CPG return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cqm", "SendCQM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cqm");
        result = TestSendCQMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CQM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fot", "SendFOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fot");
        result = TestSendFOTRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send FOT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "grs", "SendGRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("grs");
        result = TestSendGRSRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send GRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "gra", "SendGRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("gra");
        result = TestSendGRARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send GRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "iam", "SendIAM", "<cic>", ""))
    {
        memset(&hdr,0,sizeof(ITS_HDR));
        VALIDATE_CMDLINE("iam");
        result = TestSendIAMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inf", "SendINF", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inf");
        result = TestSendINFRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send INF return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inr", "SendINR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inr");
        result = TestSendINRRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send INR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "lpa", "SendLPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lpa");
        result = TestSendLPARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send LPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "pam", "SendPAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("pam");
        result = TestSendPAMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send PAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rel", "SendREL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rel");
        result = TestSendRELRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send REL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "res", "SendRES", "<cic>", ""))
    {
        VALIDATE_CMDLINE("res");
        result = TestSendRESRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send RES return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rlc", "SendRLC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rlc");
        result = TestSendRLCRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send RLC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rsc", "SendRSC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rsc");
        result = TestSendRSCRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send RSC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sus", "SendSUS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sus");
        result = TestSendSUSRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send SUS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "uba", "SendUBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("uba");
        result = TestSendUBARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send UBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ubl", "SendUBL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ubl");
        result = TestSendUBLRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send UBL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ucic", "SendUCIC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ucic");
        result = TestSendUCICRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send UCIC return result = %d\n", result);
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

        ret = MABCL_Register(CL_Handle, &msg);
    }
     
    else if (DBC_Cmd(dbc, "unreg", "UnRegister Message", "<clientID><msg_type>",
                      "<clientID#><msg_type#>"))
    {
        printf("DBC_Cmd : Inside UnRegister Command !!\n");

        // Need to send Register Event
        msg.msg_type = 1;
        ret = sscanf(cmdLine, "%s %d %d ", buf, &msg.clientID,
                                 &msg.u.deregInfo.routing_criteria);

        ret = MABCL_Deregister(CL_Handle, &msg);
    }
    else if (DBC_Cmd(dbc, "close", "Close Connection", "<connection type>",
                      "<connection type#"))
    {
        ITS_INT type;
        printf("DBC_Cmd : Inside Close Connection Command !!\n");
        ret = sscanf(cmdLine, "%s %d ", buf, &type);    
        ret = MABCL_CloseCon(CL_Handle,type);
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
    else if (DBC_Cmd(dbc, "reserveCic", "ReserveCIC", "<opc>,<dpc>,<sio>, <cicval>", "<opc#> <dpc#> <sio#> <cic#>"))
    {
        printf("DBC_Cmd : Inside ReserveCic Command !!\n");

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &opc, &dpc, &sio, &cicval);

#if defined (ANSI)
        ISUP_ReserveCIC_ANSI(NULL, sio, opc, dpc, cicval, cic_state, vcic); 
#endif

#if defined (CCITT)
        ISUP_ReserveCIC_CCITT(NULL, sio, opc, dpc, cicval, cic_state, vcic);
#endif
    }
    else if (DBC_Cmd(dbc, "unreserveCic", "UnReserveCIC", "<opc>,<dpc>,<sio>,<cicval>", "<opc#> <dpc#> <sio#> <cic#>"))
    {
        printf("DBC_Cmd : Inside UnReserveCic Command !!\n");

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &opc, &dpc, &sio, &cicval);

#if defined (ANSI)
        ISUP_UnReserveCIC_ANSI(CL_Handle, sio, opc, dpc, cicval); 
#endif

#if defined (CCITT)
        ISUP_UnReserveCIC_CCITT(CL_Handle, sio, opc, dpc, cicval); 
#endif
    }


#if defined (ANSI)
    else if (DBC_Cmd(dbc, "cra", "SendCRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cra");
        result = TestSendCRARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "crm", "SendCRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("crm");
        result = TestSendCRMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvr", "SendCVR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvr");
        result = TestSendCVRRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CVR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvt", "SendCVT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvt");
        result = TestSendCVTRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CVT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "exm", "SendEXM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("exm");
        result = TestSendACMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send EXM return result = %d\n", result);
    }
#if 0    /* Added By Santhosh */
    else if (DBC_Cmd(dbc, "reg", "Register Message", "<opc>,<dpc>,<sio>",
                      "<opc#> <dpc#> <sio#>"))
    {
        printf("DBC_Cmd : Inside Register Command !!\n");

        // Need to send Register Event

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &opc, &dpc, &sio);

        MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
        mtp3.sio = sio;

        printf("The OPC = %d \t DPC = %d \t SIO = %d\n", opc,dpc,sio);
        ret = MABCL_Register(NULL, &mtp3, 1);
    }
    else if (DBC_Cmd(dbc, "unreg", "UnRegister Message", "<opc>,<dpc>,<sio>",
                     "<opc#> <dpc#> <sio#>"))
    {
        printf("DBC_Cmd : Inside UnRegister Command !!\n");

        // Need to send Register Event

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &opc, &dpc, &sio);

        MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
        mtp3.sio = sio;

        printf("The OPC = %d \t DPC = %d \t SIO = %d\n", opc,dpc,sio);
        ret = MABCL_Deregister(NULL, &mtp3, 1);
    }

#endif
#endif /* ANSI */

#if defined (CCITT)
    else if (DBC_Cmd(dbc, "con", "SendCON", "<cic>", ""))
    {
        VALIDATE_CMDLINE("con");
        result = TestSendCONRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send CON return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "faa", "SendFAA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("faa");
        result = TestSendFAARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send FAA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( CL_Handle, &hdr );
        printf("\n(application to ISUP Stack) FAC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "far", "SendFAR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("far");
        result = TestSendFARRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send FAR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "frj", "SendFRJ", "<cic>", ""))
    {
        VALIDATE_CMDLINE("frj");
        result = TestSendFRJRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send FRJ return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "idr", "SendIDR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("idr");
        result = TestSendIDRRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send IDR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "irs", "SendIRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("irs");
        result = TestSendIRSRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send IRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "nrm", "SendNRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("nrm");
        result = TestSendNRMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send NRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "olm", "SendOLM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("olm");
        result = TestSendOLMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send OLM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sam", "SendSAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sam");
        result = TestSendSAMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send SAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sgm", "SendSGM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sgm");
        result = TestSendSGMRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send SGM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upa", "SendUPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upa");
        result = TestSendUPARequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send UPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upt", "SendUPT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upt");
        result = TestSendUPTRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send UPT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "usr", "SendUSR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("usr");
        result = TestSendUSRRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send USR return result = %d\n", result);
    }

#endif /* CCITT */

#if defined (CCITT) && defined (ITU_ISUP_97)
    else if (DBC_Cmd(dbc, "lop", "SendLOP", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lop");
        /*result = TestSendLOPRequest( CL_Handle, &hdr );*/
        printf("\n(Application to ISUP Stack) Send LOP return result = %d\n", result);
    }
#endif /* ITU_ISUP_97 */

#if defined (ANSI) && defined (ANSI_ISUP_95)
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( CL_Handle, &hdr );
        printf("\n(Application to ISUP Stack) Send FAC return result = %d\n", result);
    }
#endif /* ANSI_ISUP_95 */
    printf("------------------------------------------------------\n");

    return;
}

