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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * ID: $Id: main.c,v 1.1 2005/07/05 11:33:46 mmanikandan Exp $
 *
 * LOG: $Log: main.c,v $
 * LOG: Revision 1.1  2005/07/05 11:33:46  mmanikandan
 * LOG: ISUP Distributed test code.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include <its_redundancy.h>

#include <engine.h>
#include <its_iniparse.h>
#include <dbc_serv.h>
#include <itu/mtp3.h>
#include <ss7_mgmt.h>

#include <isup_intern.h>
#include <isup_dis_client.h>

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#endif

#define NEWCODE 0
#define OLDCODE 1

#if defined (CCITT)
typedef struct _opcdpcinfo
{
    ITS_USHORT opc;
    ITS_USHORT dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#elif defined (ANSI)
typedef struct _opcdpcinfo
{
    ITS_UINT   opc;
    ITS_UINT   dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#else "Protocol Not Defined"
#endif

static OpcDpcInfo info;

static char dmpFile[256];

#if defined (CCITT)
static const char* section = "ITU-ISUP";
#elif defined (ANSI)
static const char* section = "ANSI-ISUP";
#else
#error "Protocol Not Defined"
#endif

#if NEWCODE
static TRANSPORT_Control* tc = NULL;
static ITS_SHORT instance = 0;
static ITS_HDR hdr;
#endif

void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);
int GetOpcDpcInfo(OpcDpcInfo*);
extern int ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic, ITS_USHORT* endcic);
extern int PrintCicRangeInfo(ITS_USHORT opc, ITS_USHORT dpc, ITS_USHORT sio,
                             ITS_USHORT startcic, ITS_USHORT endcic);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      The Application MAIN function 
 *
 *  Input Parameters:
 *      argc - Argument Count to the Main func.
 *      argv - Argument String Name/Value.
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
int main(int argc, const char** argv)
{
    const ushort MAXPATH = 256;
    char path[MAXPATH];

    memset( path, 0, MAXPATH );
    assert( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("ftest");
    APPL_SetConfigFileExtension("xml");

    /*ITS_AddFeature(itsREDUNDANCY_Class);*/

    DBC_SetDoCommand(ExecuteCommand);

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Gets OPC, DPC ans SIO values from the DMP file  
 *
 *  Input Parameters:
 *      info - Pointer to the OpcDpcInfo struct
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
int GetOpcDpcInfo(OpcDpcInfo* info)
{
    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    RESFILE_Manager* res = NULL;

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("GetOpcDpcInfo(): App Dmp Name = %s\n", dmpFile);

    ITS_C_ASSERT( info != NULL );

    res = RESFILE_CreateResourceManager(dmpFile);

    ITS_C_ASSERT( res != NULL );

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX)
                                                   == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX)
                                                   == ITS_SUCCESS)
    {
        if(strcmp(DEST_POINT_CODE_STRING, key) == 0)
        {
            info->dpc = RESFILE_ParseNum(val);
        }
        else if (strcmp(LOCAL_POINT_CODE_STRING, key) == 0)
        {
            info->opc = RESFILE_ParseNum(val);
        }
        else if (strcmp(SIO_STRING, key) == 0)
        {
            info->sio = RESFILE_ParseNum(val);
        }

    }
    RESFILE_Unlock(res);

    printf("DPC = %d\n", info->dpc);
    printf("OPC = %d\n", info->opc);
    printf("SIO = %d\n", info->sio);

    return ITS_SUCCESS;
}

#if OLDCODE
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
#endif

#if NEWCODE
#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        int len = 0; \
        char buf[ITS_PATH_MAX]; \
        printf("Command entered = %s\n", cmdLine); \
        tmp = strchr(cmdLine,' '); \
        if( !tmp) tmp = strchr(cmdLine, '\t'); \
        if(!tmp) \
        { \
           printf("Usage: %s <cic>\n",x); \
           sprintf(buf,"Usage: %s <cic>\n",x); \
           DBC_AppendText(dbc, buf); \
           DBC_SendCommandResult(dbc,instance); \
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
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads ISUP commands along with arguments and executes
 *      it to print the output on Console or send the Msg to ISUP 
 *
 *  Input Parameters:
 *      dbc - Pointer to the DBC_Server 
 *      cmdLine - String to be read from the Command Line 
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
ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_INT result = 0;
    ITS_INT ret = 0;
    ITS_HDR hdr;
    ITS_SHORT cic = 0;
    char buf[ITS_PATH_MAX];

    ITS_USHORT startcic = 0;
    ITS_USHORT endcic = 0;

    static ITS_BOOLEAN firstCall = ITS_TRUE;
    static OpcDpcInfo info;
    ITS_UINT i;

#if OLDCODE /* retianed */
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
        printf("%d;%d;%d\n", info.dpc, info.opc, info.sio);
    }
#endif

#if NEWCODE
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
        printf("%d;%d;%d\n", info.dpc, info.opc, info.sio);

        tc = TRANSPORT_FindTransportByName("Debug Console");
        ITS_C_ASSERT( tc != NULL );

        instance = TRANSPORT_INSTANCE(tc);
        printf("Instance of DBC = %d\n", instance);
    }
#endif

    ITS_C_ASSERT(dbc != NULL);

    printf("------------------------------------------------------\n");
    if (DBC_Cmd(dbc, "actiVe", "Make active","data = 0(act)", ""))
    {
        int ret;
        int data =0;
        result = ITS_SendStateChangeEventToStack(data);
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }   
    else if (DBC_Cmd(dbc, "standBy", "Make standBY","data = 1(back) ", ""))
    {
        int ret;
        int data =1;
        result = ITS_SendStateChangeEventToStack(data);
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }   
    else if (DBC_Cmd(dbc, "acm", "SendACM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("acm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }   
    else if (DBC_Cmd(dbc, "anm", "SendANM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("anm");
        result = TestSendANMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ANM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "bla", "SendBLA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("bla");
        result = TestSendBLARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "blo", "SendBLO", "<cic>", ""))
    {
        VALIDATE_CMDLINE("blo");
        result = TestSendBLORequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLO return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ccr", "SendCCR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ccr");
        result = TestSendCCRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CCR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cfn", "SendCFN", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cfn");
        result = TestSendCFNRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CFN return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgb", "SendCGB", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgb");
        result = TestSendCGBRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGB return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgba", "SendCGBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgba");
        result = TestSendCGBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgu", "SendCGU", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgu");
        result = TestSendCGURequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGU return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgua", "SendCGUA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgua");
        result = TestSendCGUARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGUA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cot", "SendCOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cot");
        result = TestSendCOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send COT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cpg", "SendCPG", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cpg");
        result = TestSendCPGRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CPG return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cqm", "SendCQM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cqm");
        result = TestSendCQMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CQM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fot", "SendFOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fot");
        result = TestSendFOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FOT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "grs", "SendGRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("grs");
        result = TestSendGRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "gra", "SendGRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("gra");
        result = TestSendGRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "iam", "SendIAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("iam");
        result = TestSendIAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inf", "SendINF", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inf");
        result = TestSendINFRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INF return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inr", "SendINR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inr");
        result = TestSendINRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "lpa", "SendLPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lpa");
        result = TestSendLPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "pam", "SendPAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("pam");
        result = TestSendPAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send PAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rel", "SendREL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rel");
        result = TestSendRELRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send REL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "res", "SendRES", "<cic>", ""))
    {
        VALIDATE_CMDLINE("res");
        result = TestSendRESRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RES return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rlc", "SendRLC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rlc");
        result = TestSendRLCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RLC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rsc", "SendRSC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rsc");
        result = TestSendRSCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RSC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sus", "SendSUS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sus");
        result = TestSendSUSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SUS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "uba", "SendUBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("uba");
        result = TestSendUBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ubl", "SendUBL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ubl");
        result = TestSendUBLRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ucic", "SendUCIC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ucic");
        result = TestSendUCICRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UCIC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cic", "PrintCicInfo", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cic");
        PrintCICRecInfo(info.opc, info.dpc, info.sio, hdr.context.cic);
        printf("\n");
    }
    else if (DBC_Cmd(dbc, "cicrange", "CicInfo for a range", "<startcic endcic>", ""))
    {
        /* printf("ExecuteCommand:cmdLine = *%s*\n",cmdLine); */
        if(ValidateCicRange(cmdLine, &startcic, &endcic) != ITS_SUCCESS)
        {
            return;
        }
        /* printf("startcic = %d\n",startcic); */
        /* printf("endcic = %d\n",endcic); */

        PrintCicRangeInfo(info.opc, info.dpc, info.sio, startcic, endcic);
        printf("\n");
    }

#if defined (ANSI)
    else if (DBC_Cmd(dbc, "cra", "SendCRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cra");
        result = TestSendCRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "crm", "SendCRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("crm");
        result = TestSendCRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvr", "SendCVR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvr");
        result = TestSendCVRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvt", "SendCVT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvt");
        result = TestSendCVTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "exm", "SendEXM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("exm");
        result = TestSendEXMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send EXM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "start", "Start ANSI MTP3", "", ""))
    {
        printf("*********** Starting ANSI MTP3 **************\n");

/*        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_RESTART,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);*/

        printf("*********** Returned from the MGMT Restart *************\n");
    }

#endif /* ANSI */

#if defined (CCITT)
    else if (DBC_Cmd(dbc, "con", "SendCON", "<cic>", ""))
    {
        VALIDATE_CMDLINE("con");
        result = TestSendCONRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CON return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "faa", "SendFAA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("faa");
        result = TestSendFAARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "far", "SendFAR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("far");
        result = TestSendFARRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "frj", "SendFRJ", "<cic>", ""))
    {
        VALIDATE_CMDLINE("frj");
        result = TestSendFRJRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FRJ return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "idr", "SendIDR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("idr");
        result = TestSendIDRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IDR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "irs", "SendIRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("irs");
        result = TestSendIRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "nrm", "SendNRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("nrm");
        result = TestSendNRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send NRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "olm", "SendOLM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("olm");
        result = TestSendOLMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send OLM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sam", "SendSAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sam");
        result = TestSendSAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sgm", "SendSGM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sgm");
        result = TestSendSGMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SGM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upa", "SendUPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upa");
        result = TestSendUPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upt", "SendUPT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upt");
        result = TestSendUPTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "usr", "SendUSR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("usr");
        result = TestSendUSRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send USR return result = %d\n", result);
    }

#endif /* CCITT */

#if defined (CCITT) && defined (ITU_ISUP_97)
    else if (DBC_Cmd(dbc, "lop", "SendLOP", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lop");
        result = TestSendLOPRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LOP return result = %d\n", result);
    }
#endif /* ITU_ISUP_97 */

#if defined (ANSI) && defined (ANSI_ISUP_95)
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAC return result = %d\n", result);
    }
#endif
    else if (DBC_Cmd(dbc,"register","Register the ISUP stack with the distributed MTP3", "<ClientID> <RoutingCriteria> <LPC> <DPC> <LowerCIC> <UpperCIC> [<LPC> <DPC> <LowerCIC> <UpperCIC>]",""))
    {
        ISUPDIS_MESSAGE msg;
        char dummy[25];
        ITS_ULONG  clientID = 0;
        ITS_UINT rc = 0;
        ITS_INT lpc = 0;
        ITS_INT dpc = 0;
        ITS_INT lcic = 0;
        ITS_INT ucic = 0;
        ITS_INT lpc1 = 0;
        ITS_INT dpc1 = 0;
        ITS_INT lcic1 = 0;
        ITS_INT ucic1 = 0;

        printf("%s\n",cmdLine);
        sscanf(cmdLine,"%s %d %d %d %d %d %d %d %d %d %d",dummy, &clientID, &rc,
               &lpc,&dpc,&lcic,&ucic,&lpc1,&dpc1,&lcic1,&ucic1);

        printf("Register Info 1 : %d %d %d %d %d %d %d %d %d %d",clientID, rc,
               lpc,dpc,lcic,ucic,lpc1,dpc1,lcic1,ucic1);

        memset(&msg, 0, sizeof(ISUPDIS_MESSAGE));

        msg.clientID = clientID;
        msg.u.regInfo.routing_criteria = rc;

        MTP3_PC_SET_VALUE(msg.u.regInfo.isup[0].lpc,lpc);
        MTP3_PC_SET_VALUE(msg.u.regInfo.isup[0].dpc,dpc);
        msg.u.regInfo.isup[0].lcic = lcic;
        msg.u.regInfo.isup[0].ucic = ucic;

        MTP3_PC_SET_VALUE(msg.u.regInfo.isup[1].lpc,lpc1);
        MTP3_PC_SET_VALUE(msg.u.regInfo.isup[1].dpc,dpc1);
        msg.u.regInfo.isup[1].lcic = lcic1;
        msg.u.regInfo.isup[1].ucic = ucic1;
       
        printf("Register Info : %d %d %d %d %d %d",msg.clientID,
              msg.u.regInfo.routing_criteria,
              msg.u.regInfo.isup[0].lcic,
              msg.u.regInfo.isup[0].ucic, 
              msg.u.regInfo.isup[1].lcic,
              msg.u.regInfo.isup[1].ucic);

        msg.u.regInfo.isup[0].regType = 1;
        msg.u.regInfo.isup[1].regType = 0;

        if ((msg.u.regInfo.isup[1].lcic != 0) && 
            (msg.u.regInfo.isup[1].ucic != 0))
        {
            msg.u.regInfo.numOfRecords = 2;
        }
        else
        {
            msg.u.regInfo.numOfRecords = 1;
        }

        msg.msg_type = REGISTER_MSG;

#ifdef ANSI
        ISUPDIS_Register_ANSI(&msg);
#elif defined (CCITT)
        ISUPDIS_Register_CCITT(&msg);
#endif
    }
}
