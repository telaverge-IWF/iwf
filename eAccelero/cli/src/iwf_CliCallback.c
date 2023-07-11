
/* ********************************-*-C-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/
#include "LibCli.h"
#include "cmd_utils.h"
#include "CliParser.h"
#include "CliRegister.h"
#include "CliCallback.h"
#include "InterfaceDefs.h"
#include <string.h>
#include "CliStrings.h"
#include "CommonStructure.h"
#include <stdbool.h>

extern void clisend(int port);
extern void send_receive_data(struct cli_def *cli,void* buf,int len,int cmdID,int interfaceID);
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);

void init_localconfig(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostKeyInfo.family[0] = INVALID_STR;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostKeyInfo.pointcode = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ni = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.routing_indicator[0] = INVALID_STR;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.translation_type = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.numbering_plan = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.encoding_scheme = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.nature_of_addr_indicator = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.global_title_addr_info[0] = INVALID_STR;
    for(i = 0; i < MAX_SSN_NUM; i++)
    {
        cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ssn[i][0] = INVALID_STR;
    }
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.tcap_invoke_timer = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.num_ssn_configured = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_local_gt_from_config = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_sccp_cdpa_from_in_msg = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_ssn = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_pc = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname1[0] = INVALID_STR;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname2[0] = INVALID_STR;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid1 = INVALID_NUM;
    cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid2 = INVALID_NUM;
    //NOTE: Initializing ssn count as 0
    cli->ssn_count = 0;

    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_local_config(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO,j = 0;

    cli->req.cmd_id = C_cli_localconfig_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        //NOTE: Reset cli structures to default Values
        init_localconfig(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "local")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"ni")){
            i++;
            if(!strcmp(argv[i],"NATIONAL"))
            {
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ni = NATIONAL;
            }
            else if(!strcmp(argv[i],"INTERNATIONAL"))
            {
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ni = INTERNATIONAL;
            }
            CLI_DEBUG_LOG("Network-Indicator = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"pointcode")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostKeyInfo.pointcode = atoi(argv[i]);
            CLI_DEBUG_LOG("PointCode = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"routing-indicator"))
        {
            i++;
            strncpy(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.routing_indicator, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Routing Indicator = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"local-GTI-1")){
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti = 1;
            CLI_DEBUG_LOG("GTI = 1");
        }
        else if(!strcmp(argv[i],"local-GTI-2")){
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti = 2;
            CLI_DEBUG_LOG("GTI = 2");
        }
        else if(!strcmp(argv[i],"local-GTI-3")){
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti = 3;
            CLI_DEBUG_LOG("GTI = 3");
        }
        else if(!strcmp(argv[i],"local-GTI-4")){
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.gti = 4;
            CLI_DEBUG_LOG("GTI = 4");
        }
        else if(!strcmp(argv[i],"trans-type")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.translation_type = atoll(argv[i]);
            CLI_DEBUG_LOG("Translator-Type = %lld",atoll(argv[i]));
        }
        else if(!strcmp(argv[i],"num-plan")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.numbering_plan = atoi(argv[i]);
            CLI_DEBUG_LOG("Numbering-Plan = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"encode-scheme")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.encoding_scheme = atoi(argv[i]);
            CLI_DEBUG_LOG("Encode-Scheme = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"nature-of-addr-indi")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.nature_of_addr_indicator = atol(argv[i]);
            CLI_DEBUG_LOG("NatureOfAddrIndicator = %ld",atol(argv[i]));
        }
        else if(!strcmp(argv[i],"tcap-invoke-timer")){
            i++;
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.tcap_invoke_timer = atoi(argv[i]);
            CLI_DEBUG_LOG("Tcap-Invoke-Timer = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"global-title-addr-info")){
            i++;
            strncpy(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.global_title_addr_info, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Global Title Addr Info = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"local-ssn")){
            i++;
            int found = 0;
            if(cli->ssn_count < MAX_SSN_NUM)
            {
                if(cli->ssn_count)
                {
                    for(j=0;j<=cli->ssn_count;j++)
                    {
                        //NOTE: Check for the repetetion of SSN entered
                        if(!strcmp(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ssn[j],argv[i]))
                        {
                            found++;
                        }
                    }
                }

                if(!found)
                {
                    strncpy(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.ssn[cli->ssn_count],argv[i],MAX_SSN_LENGTH - 1);
                    CLI_DEBUG_LOG("SSN = %s",argv[i]);
                    cli->ssn_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! SSN %s already entered.",argv[i]);
                    cli_print(cli,"\n\tERROR!! SSN %s already entered.",argv[i]);
                }

                if(cli->ssn_count == MAX_SSN_NUM)
                {
                    cli_print(cli,"\n\tNOTE: Max SSN count %d reached.",MAX_SSN_NUM);
                    CLI_WARNING_LOG("NOTE:Max SSN count %d reached.",MAX_SSN_NUM);
                }
            }
            else
            {
                cli_print(cli,"\n\tERROR!! Max %d SSN's are allowed to be configured. First %d SSN's are considered for the configuration.",MAX_SSN_NUM,MAX_SSN_NUM);
                CLI_ERROR_LOG("ERROR!! Max %d SSN's are allowed to be configured. First %d SSN's are considered for the configuration.",MAX_SSN_NUM,MAX_SSN_NUM);
            }
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.num_ssn_configured = cli->ssn_count;
        }
        else if(!strcmp(argv[i],"local-gt-use-from-config")){
            i++;
            CLI_DEBUG_LOG("local-gt-use-from-config = %s",argv[i]);
            if(!strcasecmp(argv[i],"yes"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_local_gt_from_config = ENABLE;
            else
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_local_gt_from_config = DISABLE;
        }
        else if(!strcmp(argv[i],"use-sccp-cdpa-from-incomming-msg")){
            i++;
            CLI_DEBUG_LOG("use-sccp-cdpa-from-incomming-msg = %s",argv[i]);
            if(!strcasecmp(argv[i],"yes"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_sccp_cdpa_from_in_msg = ENABLE;
            else
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.use_sccp_cdpa_from_in_msg = DISABLE;
        }
        else if(!strcmp(argv[i],"include-pc")){
            i++;
            CLI_DEBUG_LOG("include-pc = %s",argv[i]);
            if(!strcasecmp(argv[i],"yes"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_pc = ENABLE;
            else
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_pc = DISABLE;
        }
        else if(!strcmp(argv[i],"include-ssn")){
            i++;
            CLI_DEBUG_LOG("include-ssn = %s",argv[i]);
            if(!strcasecmp(argv[i],"yes"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_ssn = ENABLE;
            else
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.include_ssn = DISABLE;
        }
        else if(!strcmp(argv[i],"hostname1")){
            i++;
            CLI_DEBUG_LOG("HostName1 = %s",argv[i]);
            strncpy(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname1, argv[i], MAX_HOST_NAME - 1);
        }
        else if(!strcmp(argv[i],"hostname2")){
            i++;
            CLI_DEBUG_LOG("HostName2 = %s",argv[i]);
            strncpy(cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.hostname2, argv[i], MAX_HOST_NAME - 1);
        }
        else if(!strcmp(argv[i],"asp-id1")){
            i++;
            CLI_DEBUG_LOG("AspId1 = %d",atoi(argv[i]));
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid1 = atoi(argv[i]);
        }
        else if(!strcmp(argv[i],"asp-id2")){
            i++;
            CLI_DEBUG_LOG("AspId2 = %d",atoi(argv[i]));
            cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.aspid2 = atoi(argv[i]);
        }
        else if(!strcmp(argv[i],"selection-criteria")){
            i++;
            if(!strcasecmp(argv[i],"MCC-MNC"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = MCC_MNC;
            else if(!strcasecmp(argv[i],"APP-ID"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = APP_ID;
            else if(!strcasecmp(argv[i],"MCC-MNC-AND-APP-ID"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = MCC_MNC_AND_APP_ID;
            else if(!strcasecmp(argv[i],"SERVICE-KEY"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = SK;
            else if(!strcasecmp(argv[i],"SERVICE-KEY-AND-MCC-MNC"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = SK_AND_MCC_MNC;
            else if(!strcasecmp(argv[i],"GTT"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = GTT;
            else if(!strcasecmp(argv[i],"GTT-AND-SERVICE-KEY"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = GTT_AND_SK;
            else if(!strcasecmp(argv[i],"GTT-AND-MCC-MNC"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = GTT_AND_MCC_MNC;
            else if(!strcasecmp(argv[i],"IMSI-PREFIX-AND-SERVICE-KEY"))
                cli->req.IWFPayload.iwfLocalHostConfigPayload.iwfLocalHostConfigInfo.selection_criteria = IMSI_PREFIX_AND_SK;
            CLI_DEBUG_LOG("selection-criteria = %s",argv[i]);
        }
        i++;
    }

    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_sctp_endpoint_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.ipaddr[0] = INVALID_STR;
    cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.port = INVALID_NUM;
    cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.type[0] = INVALID_STR;
    for(i = 0; i< MAX_LOCALTRANSPORT_ATTRIBUTES; i++)
    {
        cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.secondaryIp[i][0] = INVALID_STR;
    }
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_sigtran_multihoming_config(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    cli->req.cmd_id = C_cli_delete_sctpendpoint_multihoming_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    init_sctp_endpoint_config(cli);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no") && !strcmp(argv[CMD_LINE_ARG_ONE],"multi-homing-ip")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"sctp-end-point")){
            i++;
            strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("SCTPEndPoint = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"ip"))
        {
            int k = 0;
            while(argv[i])
            {
                if(!strcmp(argv[i],"ip"))
                {
                    i++;
                    if(argv[i])
                    {
                        strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.secondaryIp[k], argv[i], MAX_IP_LEN - 1);
                        CLI_DEBUG_LOG("MultiHomingIpAddr = %s",argv[i]);
                        k++; i++;
                    }
                }
            }
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_sctp_endpoint_config(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        //NOTE: Reset cli structures to default Values
        init_sctp_endpoint_config(cli);
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        cli->req.cmd_id = C_cli_delete_sctp_endpoint_Id;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        cli->req.cmd_id = C_cli_modify_sctp_endpoint_Id;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "sctp-end-point")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        cli->req.cmd_id = C_cli_sctp_endpoint_Id;
    }

    while(argv[i]){
        if(!strcmp(argv[i],"sctp-end-point")){
            i++;
            strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("SCTPEndPoint = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"ip")){
            i++;
            strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.ipaddr, argv[i], MAX_IP_LEN - 1);
            CLI_DEBUG_LOG("Ip-addr = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"port")){
            i++;
            cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.port = atoi(argv[i]);
            CLI_DEBUG_LOG("Port = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"type")){
            i++;
            strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.type, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Type of EndPoint = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"multi-homing"))
        {
            int k = 0;
            i++;
            while(argv[i])
            {
                if(!strcmp(argv[i],"ip"))
                {
                    i++;
                    if(argv[i])
                    {
                        strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigInfo.secondaryIp[k], argv[i], MAX_IP_LEN - 1);
                        CLI_DEBUG_LOG("MultiHomingIpAddr = %s",argv[i]);
                        k++; i++;
                    }
                }
            }
        }
        i++;
    }

    if(cli->req.OP_CODE == MODIFY)
        cli->req.cmd_id = C_cli_modify_sctp_endpoint_Id;

    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
    {
        if(cli->req.OP_CODE == MODIFY)
            cli->req.cmd_id = C_cli_modify_sctp_endpoint_Id;

        cli->allow_exit=0;
    }
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_sctpprofile_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename[0] = INVALID_STR;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeat = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeattimeout = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.inittimeout = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxattempts = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.assocmaxattempts = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathfailureretrycount = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtoinit = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomin = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomax = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathmaxretransmit = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.reconnecttimeout = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sendbuffsize = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivebuffsize = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.cookielife = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sackdelay = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxinstreams = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.numofoutstreams = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.shutdowntimeout = INVALID_NUM;
    cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivetimeout = INVALID_NUM;

    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_sctp_profile_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_sctp_profile_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        //NOTE: Reset cli structures to default Values
        init_sctpprofile_config(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "sctp-profile")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"sctp-profile")){
            i++;
            strncpy(cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("SCTPProfile = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"heartbeat")){
            i++;
            if(!strcmp(argv[i],"enable"))
                cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeat = ENABLE;
            else if(!strcmp(argv[i],"disable"))
                cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeat = DISABLE;

            CLI_DEBUG_LOG("heartbeat = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"heart-beat-timeout"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.heartbeattimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("heartbeattimeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"init-time-out"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.inittimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("inittimeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"max-init-attempts"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxattempts = atoi(argv[i]);
            CLI_DEBUG_LOG("max-attempts = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"assoc-max-attempts"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.assocmaxattempts = atoi(argv[i]);
            CLI_DEBUG_LOG("assoc-max-attempts = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"pathfail-retrycount"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathfailureretrycount = atoi(argv[i]);
            CLI_DEBUG_LOG("pathfail-retrycount = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-Initial"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtoinit = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-initial = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-min"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomin = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-min = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-max"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.rtomax = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-max = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"path-max-retransmit"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.pathmaxretransmit = atoi(argv[i]);
            CLI_DEBUG_LOG("Path-max-retransmit = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"recv-time-out"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivetimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("receive timeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"shutdown-time-out"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.shutdowntimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("shutdown timeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"reconnect-time-out"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.reconnecttimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("re-connect timeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"send-buff-size"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sendbuffsize = atoi(argv[i]);
            CLI_DEBUG_LOG("send-buff-size = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"recv-buff-size"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.receivebuffsize = atoi(argv[i]);
            CLI_DEBUG_LOG("receive-buff-size = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"cookie-life"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.cookielife = atoi(argv[i]);
            CLI_DEBUG_LOG("cookie life = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"sack-delay"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.sackdelay = atoi(argv[i]);
            CLI_DEBUG_LOG("sack delay = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"max-instreams"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.maxinstreams = atoi(argv[i]);
            CLI_DEBUG_LOG("max instreams = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"num-of-outstreams"))
        {
            i++;
            cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigInfo.numofoutstreams = atoi(argv[i]);
            CLI_DEBUG_LOG("num of outstreams = %d",atoi(argv[i]));
        }
        i++;
    }

    if(cli->req.OP_CODE == MODIFY)
        cli->req.cmd_id = C_cli_modify_sctp_profile_Id;

    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_association_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.sctp_profile_name[0] = INVALID_STR;
    cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.association_set[0] = INVALID_STR;
    cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.local_sctp_end_point[0] = INVALID_STR;
    cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.remote_sctp_end_point[0] = INVALID_STR;
    cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.aspId = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_association_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    cli->req.cmd_id = C_cli_assocation_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no") && !strcmp(argv[CMD_LINE_ARG_ONE],"association")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        //NOTE: Reset cli structures to default Values
        init_association_config(cli);
        cli->req.cmd_id = C_cli_no_assocation_Id;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "association")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        init_association_config(cli);
    }

    if(cli->req.OP_CODE == MODIFY)
    {
        cli->req.cmd_id = C_cli_modify_assocation_Id;
    }

    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    while(argv[i]){
        if(!strcmp(argv[i],"association"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Association = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"association-set"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.association_set, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Association-Set = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"sctp-Profile"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.sctp_profile_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("SCTP-Profile = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"local-end-point"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.local_sctp_end_point, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Local-End-Point = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"remote-end-point"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.remote_sctp_end_point, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Remote-End-Point = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"asp-id"))
        {
            i++;
            cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.aspId = atoi(argv[i]);
            CLI_DEBUG_LOG("AspId = %d",atoi(argv[i]));
        }
        i++;
    }

    if(cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_ual_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    cli->req.IWFPayload.ualSetConfigPayload.ualSetConfigInfo.ack_timer = INVALID_NUM;
    cli->req.IWFPayload.ualSetConfigPayload.ualSetConfigInfo.sigtran_mode[0] = INVALID_STR;

    cli->req.cmd_id = C_cli_ual_set_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "ual-config")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"ack-timer"))
        {
            i++;
            cli->req.IWFPayload.ualSetConfigPayload.ualSetConfigInfo.ack_timer = atoi(argv[i]);
            CLI_DEBUG_LOG("Ack-Timer = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"sigtran-mode"))
        {
            i++;
            strncpy(cli->req.IWFPayload.ualSetConfigPayload.ualSetConfigInfo.sigtran_mode, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Sigtran-Mode = %s",argv[i]);
        }
        i++;
    }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_associationset_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.family[0] = INVALID_STR;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.ni = INVALID_NUM;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.pointcode = INVALID_NUM;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.routing_key = INVALID_NUM;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.traffic_mode[0] = INVALID_STR;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.asp_id = INVALID_NUM;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.isMember = INVALID_NUM;
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.homeIp[0] = INVALID_STR;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_associationset_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    char protocol_family[MAX_FAMILY_LENGTH] = "";


    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        //NOTE: Reset cli structures to default Values
        init_associationset_config(cli);
        cli->req.cmd_id = C_cli_assocation_set_Id;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        cli->req.cmd_id = C_cli_modify_assocation_set_Id;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "assoc-set")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        cli->req.cmd_id = C_cli_assocation_set_Id;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    }

    while(argv[i]){
        if(!strcmp(argv[i],"assoc-set"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Association-Set = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"family"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.family, argv[i], MAX_FAMILY_LENGTH - 1);
            strncpy(protocol_family, argv[i],MAX_FAMILY_LENGTH - 1);
            CLI_DEBUG_LOG("ProtocolFamily = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"adj-pointcode"))
        {
            i++;
            cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.pointcode = atoi(argv[i]);
            CLI_DEBUG_LOG("PointCode = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"ni"))
        {
            i++;
            if(!strcmp(argv[i],"NATIONAL"))
            {
                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.ni = NATIONAL;
            }
            else if(!strcmp(argv[i],"INTERNATIONAL"))
            {
                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.ni = INTERNATIONAL;
            }
            CLI_DEBUG_LOG("Network Indicator = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"routing-context"))
        {
            i++;
            cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.routing_key = atoi(argv[i]);
            CLI_DEBUG_LOG("RoutingContext = %d",atoi(argv[i]));
        }
        else if(!strcasecmp(argv[i],"traffic-mode"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.traffic_mode, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Traffic-Mode = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"asp-id"))
        {
            i++;
            cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.asp_id = atoi(argv[i]);
            CLI_DEBUG_LOG("ASP-Id = %d",atoi(argv[i]));
        }
        else if(!strcasecmp(argv[i],"IsMember"))
        {
            i++;
            if(!strcasecmp(argv[i],"Yes"))
                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.isMember = ENABLE;
            else
                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.isMember = DISABLE;
            CLI_DEBUG_LOG("IsMember = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"homeip"))
        {
            i++;
            CLI_DEBUG_LOG("HomeIp = %s",argv[i]);
            strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.homeIp, argv[i], MAX_FIELD_NAME - 1);
        }
        i++;
    }

    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_destination_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name[0] = INVALID_STR;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator[0] = INVALID_STR;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.family[0] = INVALID_STR;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ni = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ssn[0] = INVALID_STR;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.translation_type = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.numbering_plan = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.encoding_scheme = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.nature_of_addr_indicator = INVALID_NUM;
    cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.global_title_addr_info[0] = INVALID_STR;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_destination_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    char protocol_family[MAX_FAMILY_LENGTH] = "";

    cli->req.cmd_id = C_cli_destination_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        //NOTE: Reset cli structures to default Values
        init_destination_config(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "destination")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"destination"))
        {
            i++;
            strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Destination = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"family"))
        {
            i++;
            strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.family, argv[i], MAX_FIELD_NAME - 1);
            strncpy(protocol_family, argv[i],MAX_FAMILY_LENGTH - 1);
            CLI_DEBUG_LOG("ProtocolFamily = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"ni"))
        {
            i++;
            if(!strcmp(argv[i],"NATIONAL"))
            {
                cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ni = NATIONAL;
            }
            else if(!strcmp(argv[i],"INTERNATIONAL"))
            {
                cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ni = INTERNATIONAL;
            }
            CLI_DEBUG_LOG("Network Indicator = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"pointCode"))
        {
            i++;
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode = atoi(argv[i]);
            CLI_DEBUG_LOG("PointCode = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"routing-indicator"))
        {
            i++;
            strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Routing Indicator = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"dest-ssn"))
        {
            i++;
            strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ssn, argv[i], MAX_SSN_LENGTH - 1);
            CLI_DEBUG_LOG("Dest-SSN = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"dest-GTI-1")){
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti = 1;
            CLI_DEBUG_LOG("GTI = 1");
        }
        else if(!strcmp(argv[i],"dest-GTI-2")){
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti = 2;
            CLI_DEBUG_LOG("GTI = 2");
        }
        else if(!strcmp(argv[i],"dest-GTI-3")){
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti = 3;
            CLI_DEBUG_LOG("GTI = 3");
        }
        else if(!strcmp(argv[i],"dest-GTI-4")){
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti = 4;
            CLI_DEBUG_LOG("GTI = 4");
        }
        else if(!strcmp(argv[i],"trans-type"))
        {
            i++;
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.translation_type = atoll(argv[i]);
            CLI_DEBUG_LOG("Translation Type = %lld",atoll(argv[i]));
        }
        else if(!strcmp(argv[i],"nature-of-addr-indi"))
        {
            i++;
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.nature_of_addr_indicator = atol(argv[i]);
            CLI_DEBUG_LOG("Nature Of Addr Indicator = %ld",atol(argv[i]));
        }
        else if(!strcmp(argv[i],"num-plan"))
        {
            i++;
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.numbering_plan = atoi(argv[i]);
            CLI_DEBUG_LOG("Numbering plan = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"encode-scheme"))
        {
            i++;
            cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.encoding_scheme = atoi(argv[i]);
            CLI_DEBUG_LOG("Encode Scheme = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"global-title-addr-info"))
        {
            i++;
            strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.global_title_addr_info, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Global Title Addr Info = %s",argv[i]);
        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

void init_remoteroute_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.dest_name[0] = INVALID_STR;
    cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.assocsetname[0] = INVALID_STR;
    cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.priority = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_remoteroute_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_remoteroute_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        //NOTE: Reset cli structures to default Values
        init_remoteroute_config(cli);
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "remote-route")){
        cli->req.OP_CODE = ADD;
        //NOTE: Reset cli structures to default Values
        init_remoteroute_config(cli);
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"remote-route"))
        {
            i++;
            strncpy(cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("RemoteRoute = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"dest"))
        {
            i++;
            strncpy(cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.dest_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Destination = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"assoc-Set"))
        {
            i++;
            strncpy(cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.assocsetname, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Association-Set = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"priority"))
        {
            i++;
            cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigInfo.priority = atoi(argv[i]);
            CLI_DEBUG_LOG("Priority = %d",atoi(argv[i]));
        }
        i++;
    }

    if(cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

void init_translator_rule_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dest_host[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_host[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_realm[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mcc[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mnc[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dssn[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.app_id[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.http_url[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.web_service[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_start_value = INVALID_NUM;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.service_key_end_value = INVALID_NUM;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined = INVALID_NUM;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.calling_gt_address_digits[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceContextId[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.imsiPrefix[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.proActionRule[0] = INVALID_STR;
    cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id_count = INVALID_NUM;
    for(i = 0; i < MAX_VPLMN_ID_COUNT; i++)
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id[i][0] = INVALID_STR;
    cli->vplmnid_count = 0;

    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_translator_rule_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_translation_rule_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        //NOTE: Reset cli structures to default Values
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name[0] = INVALID_STR;
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translation_type[0] = INVALID_STR;
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator[0] = INVALID_STR;
        init_translator_rule_config(cli);
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        if(!strcasecmp(argv[i],"allowed-vplmn-id"))
        {
            i = CMD_LINE_ARG_TWO;
            cli->req.cmd_id = C_cli_translation_vplmn_Id;
        }
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "trans-rule")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        //Default value set as * (wildcard) for servicekey
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name[0] = INVALID_STR;
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translation_type[0] = INVALID_STR;
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator[0] = INVALID_STR;
        strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey, "*", MAX_SERVICE_KEY_DIGITS - 1);
        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined = DISABLE;
    }

    while(argv[i]){
        if(!strcmp(argv[i],"trans-rule"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Rule Name = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"trans-type"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translation_type, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Trans-Type = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"translator"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Translator = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"dest-name") || !strcasecmp(argv[i],"primary-dest-realm"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Primary Destination Realm= %s",argv[i]);
        }
        else if(!strcmp(argv[i],"primary-dest-host"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dest_host, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Primary Destination Host = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"secondary-dest-realm") || !strcasecmp(argv[i],"alt-dest"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_realm, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Secondary Destination/Realm = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"secondary-dest-host"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.alt_host, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Secondary Destination Host = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"mcc"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mcc, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("MCC = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"mnc"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.mnc, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("MNC = %s",argv[i]);
        }

        else if(!strcasecmp(argv[i],"ossn"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Ossn = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"dssn"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.dssn, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Dssn = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"app-id"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.app_id, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("App-Id = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"http-url"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.http_url, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("HTTP-Url = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"web-srvc"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.web_service, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("web-srvc = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"service-key"))
        {
            i++;
            if(!strcmp(argv[i],"list"))
            {
                i++;
                cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined = DISABLE;
                strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey, argv[i], MAX_SERVICE_KEY_DIGITS - 1);
                CLI_DEBUG_LOG("Service Key Value = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"range"))
            {
                cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined = ENABLE;
                i++;
                if(!strcmp(argv[i],"start-value"))
                {
                    i++;
                    CLI_DEBUG_LOG("Service Key Start Value = %d",atoi(argv[i]));
                    strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey, argv[i], MAX_SERVICE_KEY_DIGITS - 1);
                    i++;
                }
                if(!strcmp(argv[i],"end-value"))
                {
                    i++;
                    CLI_DEBUG_LOG("Service Key End Value = %d",atoi(argv[i]));
                    if(atoi(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey) >= atoi(argv[i]))
                    {
                        CLI_ERROR_LOG("Error: ServiceKey EndValue is Less than or Equal to StartValue");
                        cli_print(cli,"\n\tERROR!! ServiceKey EndValue is Less than or Equal to StartValue");
                        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey[0] = INVALID_STR;
                        cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.isRangeDefined = INVALID_NUM;
                    }
                    else
                    {
                        strncat(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey, " - ", MAX_SERVICE_KEY_DIGITS - 1);
                        strncat(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey, argv[i], MAX_SERVICE_KEY_DIGITS - 1);
                    }
                }
            }
        }
        else if(!strcmp(argv[i],"calling-gt-addr-digits"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.calling_gt_address_digits, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Calling-GT-Addr-Digits = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"service-context-id"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceContextId, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("ServiceContextId = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"allowed-vplmn-id") ||
                !strcasecmp(argv[i],"vplmn-id"))
        {
            i++;
            if(cli->vplmnid_count < MAX_VPLMN_ID_COUNT)
            {
                int j = 0;
                bool found = false;
                if(cli->vplmnid_count)
                {
                    for(j=0;j<=cli->vplmnid_count;j++)
                    {
                        // to check whether user entered same vplmn-id again
                        if(!strcmp(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id[j],argv[i]))
                            found = true;
                    }
                }
                if(!found)
                {
                    strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id[cli->vplmnid_count],argv[i],MAX_VPLMN_ID_LENGTH - 1);
                    CLI_DEBUG_LOG("allowed-vplmn-id = %s",argv[i]);
                    cli->vplmnid_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! Vplmn-Id %s already entered",argv[i]);
                    cli_print(cli,"\n\tERROR!! Vplmn-Id %s already entered.",argv[i]);
                }
                if(cli->vplmnid_count == MAX_VPLMN_ID_COUNT)
                {
                    cli_print(cli,"\n\tNOTE: Max Vplmn-Id count %d reached.",MAX_VPLMN_ID_COUNT);
                    CLI_WARNING_LOG("NOTE: Max Vplmn-Id count %d reached",MAX_VPLMN_ID_COUNT);
                }
            }
            else {
                cli_print(cli,"\n\tERROR!! Max %d Vplmn-Id's are allowed to be configured. First %d Vplmn-Id's are considered for the configuration.",MAX_VPLMN_ID_COUNT,MAX_VPLMN_ID_COUNT);
                CLI_ERROR_LOG("ERROR!! Max %d Vplmn-Id's are allowed to be configured. First %d Vplmn-Id's are considered for the configuration.",MAX_VPLMN_ID_COUNT,MAX_VPLMN_ID_COUNT);
            }
            cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.vplmn_id_count = cli->vplmnid_count;
        }
        else if(!strcasecmp(argv[i],"imsi-prefix"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.imsiPrefix, argv[i], MAX_IMSI_DIGITS - 1);
            CLI_DEBUG_LOG("IMSI-Prefix = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"pro-action-rule"))
        {
            i++;
            strncpy(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.proActionRule, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("ProActionRule = %s",argv[i]);
        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_s6a_map_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigKeyInfo.translator_name[0] = INVALID_STR;
    cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.local_sgsn_num[0] = INVALID_STR;
    cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.routing_prefix[0] = INVALID_STR;
    cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_addr_map_count = INVALID_NUM;
    cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix_map_count = INVALID_NUM;
    for (i = 0; i < MAX_SGSN_ADDR_MAP_NUM; i++)
    {
        cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.org_host[i][0] = INVALID_STR;
        cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.ip_addr[i][0] = INVALID_STR;
        cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.vplmnId[i][0] = INVALID_STR;
        cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix[i][0] = INVALID_STR;
    }
    cli->sgsn_addr_map_count = 0;
    cli->sgsn_prefix_map_count = 0;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_s6a_map_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_s6a_map_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    CLI_DEBUG_LOG("Translator = s6a-MAP");
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        //NOTE: Reset cli structures to default Values
        init_s6a_map_config(cli);
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "s6a-MAP")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"local-sgsn-num"))
        {
            i++;
            strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.local_sgsn_num, argv[i], MAX_SGSN_NUM_LENGTH -1);
            CLI_DEBUG_LOG("Local-SGSN-Num = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"routing-prefix"))
        {
            i++;
            strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.routing_prefix, argv[i], MAX_SGSN_NUM_LENGTH -1);
            CLI_DEBUG_LOG("Routing-Prefix = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"org-host"))
        {
            i++;
            int found = 0, j = 0;
            if(cli->sgsn_addr_map_count < MAX_SGSN_ADDR_MAP_NUM)
            {
                if(cli->sgsn_addr_map_count)
                {
                    for(j=0;j<=cli->sgsn_addr_map_count;j++)
                    {
                        if(!strcmp(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.org_host[j],argv[i]))
                            found++;
                    }
                }
                if(!found)
                {
                    strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.org_host[cli->sgsn_addr_map_count], argv[i], MAX_HOST_NAME -1);
                    CLI_DEBUG_LOG("Org-Host = %s",argv[i]);
                    if(argv[i+CMD_LINE_ARG_TWO])
                    {
                        strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.ip_addr[cli->sgsn_addr_map_count], argv[i+CMD_LINE_ARG_TWO], MAX_IP_LEN -1);
                        CLI_DEBUG_LOG("Ip-Addr = %s",argv[i+CMD_LINE_ARG_TWO]);
                    }
                    cli->sgsn_addr_map_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! SGSN-Addr-MAP with Org-Host name - %s already entered.",argv[i]);
                    cli_print(cli,"\n\tERROR!! SGSN-Addr-MAP with Org-Host name - %s already entered.",argv[i]);
                }

                if(cli->sgsn_addr_map_count == MAX_SGSN_ADDR_MAP_NUM)
                {
                    cli_print(cli,"\n\tNOTE: Max SGSN-Addr-MAP count %d is Reached",MAX_SGSN_ADDR_MAP_NUM);
                    CLI_ERROR_LOG("NOTE: Max SGSN-Addr-MAP count %d is Reached",MAX_SGSN_ADDR_MAP_NUM);
                }

            }
            else
            {
                CLI_ERROR_LOG("ERROR!! Max %d SGSN-Addr-MAP are allowed to be configured. First %d SGSN-Addr-MAP are considered for the configuration.",MAX_SGSN_ADDR_MAP_NUM,MAX_SGSN_ADDR_MAP_NUM);
                cli_print(cli,"\n\tERROR!! Max %d SGSN-Addr-MAP are allowed to be configured. First %d SGSN-Addr-MAP are considered for the configuration.",MAX_SGSN_ADDR_MAP_NUM,MAX_SGSN_ADDR_MAP_NUM);
            }
            cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_addr_map_count = cli->sgsn_addr_map_count;
        }
        else if(!strcasecmp(argv[i],"vplmnID"))
        {
            i++;
            int found = 0, j = 0;
            if(cli->sgsn_prefix_map_count < MAX_SGSN_ADDR_MAP_NUM)
            {
                if(cli->sgsn_prefix_map_count)
                {
                    for(j=0;j<=cli->sgsn_prefix_map_count;j++)
                    {
                        if(!strcmp(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.vplmnId[j],argv[i]))
                            found++;
                    }
                }
                if(!found)
                {
                    strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.vplmnId[cli->sgsn_prefix_map_count], argv[i], MAX_VPLMN_ID_LENGTH -1);
                    CLI_DEBUG_LOG("VplmnId = %s",argv[i]);
                    if(argv[i+CMD_LINE_ARG_TWO])
                    {
                        strncpy(cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix[cli->sgsn_addr_map_count], argv[i+CMD_LINE_ARG_TWO], MAX_SGSN_NUM_LENGTH -1);
                        CLI_DEBUG_LOG("Sgsn-Prefix = %s",argv[i+CMD_LINE_ARG_TWO]);
                    }
                    cli->sgsn_prefix_map_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! SGSN-Prefix-MAP with VplmnId - %s already entered.",argv[i]);
                    cli_print(cli,"\n\tERROR!! SGSN-Prefix-MAP with VplmnId - %s already entered.",argv[i]);
                }

                if(cli->sgsn_prefix_map_count == MAX_SGSN_ADDR_MAP_NUM)
                {
                    cli_print(cli,"\n\tNOTE: Max SGSN-Prefix-MAP count %d is Reached",MAX_SGSN_ADDR_MAP_NUM);
                    CLI_ERROR_LOG("NOTE: Max SGSN-Prefix-MAP count %d is Reached",MAX_SGSN_ADDR_MAP_NUM);
                }

            }
            else
            {
                CLI_ERROR_LOG("ERROR!! Max %d SGSN-Prefix-MAP are allowed to be configured. First %d SGSN-Prefix-MAP entries are considered for the configuration.",MAX_SGSN_ADDR_MAP_NUM,MAX_SGSN_ADDR_MAP_NUM);
                cli_print(cli,"\n\tERROR!! Max %d SGSN-Prefix-MAP are allowed to be configured. First %d SGSN-Prefix-MAP entries are considered for the configuration.",MAX_SGSN_ADDR_MAP_NUM,MAX_SGSN_ADDR_MAP_NUM);
            }
            cli->req.IWFPayload.s6aMAPConfigPayload.s6aMAPConfigInfo.sgsn_prefix_map_count = cli->sgsn_prefix_map_count;
        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);


    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

void init_map_s6a_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0, j = 0;
    cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigKeyInfo.translator_name[0] = INVALID_STR;
    cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.hlr_number[0] =  INVALID_STR;
    for(i = 0; i<MAX_VPLMN_ID_COUNT; i++)
    {
        cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[i][0] = INVALID_STR;
        for(j=0; j<MAX_SGSN_NUM_COUNT; j++)
        {
            cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.sgsn_number[i][j][0] = INVALID_STR;
        }
    }
    cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count = INVALID_NUM;
    cli->vplmnid_count = 0;
    CLI_DEBUG_LOG(" Exited ");
}

int validate_sgsn_number(struct cli_def *cli, const char *sgsn)
{
    if((cli->req.OP_CODE == ADD) ||
            (cli->req.OP_CODE == MODIFY))
    {
        int len = 0;
        char *found = strchr(sgsn, '*');
        if(found)
        {
            int index = (found - sgsn)/sizeof(char);
            len = strlen(sgsn);
            if(len < 2)
            {
                cli_print(cli,"\n\tERROR!! Atleast one digit should be present with wildcard.");
                CLI_ERROR_LOG("ERROR!! Atleast one digit should be present with wildcard.");
                return CLI_ERROR;
            }
            else if(index != (len - 1))
            {
                cli_print(cli,"\n\tERROR!! Wildcard character is allowed only at the end of sgsn-number.");
                CLI_ERROR_LOG("ERROR!! Wildcard character is allowed only at the end of sgsn-number.");
                return CLI_ERROR;
            }
        }
    }
    return CLI_OK;
}

int cli_delete_map_s6a_config_vplmn(struct cli_def *cli,char *command,char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    int k =0;
    cli->req.cmd_id = C_cli_map_s6a_vplmn_config_Id;
    CLI_DEBUG_LOG("Cmd id = %d", cli->req.cmd_id);
    init_map_s6a_config(cli);
    cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count = 0;
   
    if((!strcmp(argv[CMD_LINE_ARG_ZERO],"no")) && (!strcmp(argv[CMD_LINE_ARG_ONE],"map-s6a-vplmn-id")))
    {
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }

        while(argv[i])
        {
            if(!strcmp(argv[i],"vplmn-id"))
            {
                i++;
                strncpy(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[k],argv[i],MAX_VPLMN_ID_LENGTH -1);
                k++;
                CLI_DEBUG_LOG("VPLMNID = %s ",argv[i]);
                cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count++;
            }
            i++;
        }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG("Exited");
   return CLI_OK; 
}

int cli_int_map_s6a_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_map_s6a_config_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        if(!strcmp(argv[i],"sgsn-vplmn-id-map"))
        {
            cli->req.cmd_id = C_cli_map_s6a_vplmn_sgsn_config_Id;
        }
        else if(!strcmp(argv[i],"map-s6a-vplmn-id"))
        {
            cli->req.cmd_id = C_cli_map_s6a_vplmn_config_Id;
        }
        init_map_s6a_config(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "MAP-s6a")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }
    strncpy(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigKeyInfo.translator_name, "MAP-s6a", MAX_FIELD_NAME -1);
    CLI_DEBUG_LOG("Translator = MAP-s6a");

    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    while(argv[i])
    {
        if(!strcmp(argv[i],"hlr-num"))
        {
            i++;
            strncpy(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.hlr_number, argv[i], MAX_FIELD_NAME -1);
            CLI_DEBUG_LOG("HLR-Num = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"vplmn-id"))
        {
            i++;
            if(cli->vplmnid_count < MAX_VPLMN_ID_COUNT)
            {
                int j = 0;
                bool found = false;
                if(cli->vplmnid_count)
                {
                    for(j=0;j<=cli->vplmnid_count;j++)
                    {
                        // to check whether user entered same vplmn-id again
                        if(!strcmp(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[j],argv[i]))
                            found = true;
                    }
                }
                if(!found)
                {
                    strncpy(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id[cli->vplmnid_count],argv[i],MAX_VPLMN_ID_LENGTH - 1);
                    CLI_DEBUG_LOG("allowed-vplmn-id = %s",argv[i]);
                    i++;
                    int k = 0;
                    while(argv[i])
                    {
                        if(!strcmp(argv[i],"sgsn-number"))
                        {
                            i++;
                            CLI_DEBUG_LOG("sgsn-number = %s",argv[i]);
                            if((validate_sgsn_number(cli, argv[i])) == CLI_OK)
                            {
                                strncpy(cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.sgsn_number[cli->vplmnid_count][k],argv[i],MAX_SGSN_NUM_LENGTH - 1);
                                k++;
                            }
                        }
                        i++;
                    }
                    cli->vplmnid_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! Vplmn-Id %s already entered",argv[i]);
                    cli_print(cli,"\n\tERROR!! Vplmn-Id %s already entered.",argv[i]);
                }
                if(cli->vplmnid_count == MAX_VPLMN_ID_COUNT)
                {
                    cli_print(cli,"\n\tNOTE: Max Vplmn-Id count %d reached.",MAX_VPLMN_ID_COUNT);
                    CLI_WARNING_LOG("NOTE: Max Vplmn-Id count %d reached",MAX_VPLMN_ID_COUNT);
                }
            }
            else {
                cli_print(cli,"\n\tERROR!! Max %d Vplmn-Id's are allowed to be configured. First %d Vplmn-Id's are considered for the configuration.",MAX_VPLMN_ID_COUNT,MAX_VPLMN_ID_COUNT);
                CLI_ERROR_LOG("ERROR!! Max %d Vplmn-Id's are allowed to be configured. First %d Vplmn-Id's are considered for the configuration.",MAX_VPLMN_ID_COUNT,MAX_VPLMN_ID_COUNT);
            }
            cli->req.IWFPayload.mapS6aConfigPayload.mapS6aConfigInfo.vplmn_id_count = cli->vplmnid_count;

        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int check_for_invalid_idp_config(struct cli_def *cli)
{
    if(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.node_functionality == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.sip_method[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.originating_ioi[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.terminating_ioi[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.service_context_id[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cause_code[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.msc_service_specific_type == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.gmsc_service_specific_type == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cpc_service_specific_type == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator == INVALID_NUM ||
            (cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service_map_count == INVALID_NUM &&
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service_map_count == INVALID_NUM))
        return CLI_ERROR;

    return CLI_OK;
}

void init_cap_ro_idp_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigKeyInfo.translator_name[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.node_functionality = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.sip_method[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.originating_ioi[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.terminating_ioi[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.service_context_id[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cause_code[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.msc_service_specific_type = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.gmsc_service_specific_type = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cpc_service_specific_type = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service_map_count = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service_map_count = INVALID_NUM;
    for( i = 0; i<MAX_TELE_SERVICE_MAP; i++)
    {
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service[i] = INVALID_NUM;
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.tele_service_id[i] = INVALID_NUM;
    }
    for( i = 0; i<MAX_BEARER_SERVICE_MAP; i++)
    {
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service[i] = INVALID_NUM;
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.bearer_service_id[i] = INVALID_NUM;
    }
    cli->ext_tele_srvc_count = 0;
    cli->ext_bearer_srvc_count = 0;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_cap_ro_idp_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_cap_ro_idp_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    CLI_DEBUG_LOG("Translator = CAP-Ro");

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        init_cap_ro_idp_config(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "idp")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        //Default value for Multiple Service Indicator
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator = SUPPORTED;
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"node-func"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.node_functionality = atoi(argv[i]);
            CLI_DEBUG_LOG("Node-Functionality = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"sip-method"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.sip_method, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("SIP-Method = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"originating-ioi"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.originating_ioi, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Originating-IOI = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"terminating-ioi"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.terminating_ioi, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Terminating-IOI = %d",atoi(argv[i]));
        }
        else if(!strcasecmp(argv[i],"service-context-id"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.service_context_id, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Service Context Id = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"cause-code"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cause_code, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Cause Code = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"msc-srvc-specific-type"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.msc_service_specific_type = atoi(argv[i]);
            CLI_DEBUG_LOG("MSC Service Specific Type = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"gmsc-srvc-specific-type"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.gmsc_service_specific_type = atoi(argv[i]);
            CLI_DEBUG_LOG("GMSC Service Specific Type = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"cpc-srvc-specific-type"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.cpc_service_specific_type = atoi(argv[i]);
            CLI_DEBUG_LOG("CPC Service Specific Type = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"multi-srvc-indi"))
        {
            i++;
            if(!strcmp(argv[i],"SUPPORTED"))
                cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator = SUPPORTED;
            else
                cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator = NOT_SUPPORTED;
            CLI_DEBUG_LOG("Multi Service Indicator = %d",cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator);
        }
        else if(!strcmp(argv[i],"ext-tele-srvc"))
        {
            i++;
            int found = 0, j = 0;
            if(cli->ext_tele_srvc_count < MAX_TELE_SERVICE_MAP)
            {
                if(cli->ext_tele_srvc_count)
                {
                    for(j=0;j<=cli->ext_tele_srvc_count;j++)
                    {
                        if(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service[j] == atoi(argv[i]))
                            found++;
                    }
                }
                if(!found)
                {
                    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service[cli->ext_tele_srvc_count] = atoi(argv[i]);
                    CLI_DEBUG_LOG("Ext-Tele-Service = %d",atoi(argv[i]));
                    if(argv[i+CMD_LINE_ARG_TWO])
                    {
                        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.tele_service_id[cli->ext_tele_srvc_count] = atoi(argv[i+CMD_LINE_ARG_TWO]);
                        CLI_DEBUG_LOG("Tele-Service-id = %d",atoi(argv[i+CMD_LINE_ARG_TWO]));
                    }
                    cli->ext_tele_srvc_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! Ext-Tele-Service-Map with Ext-Tele-Service - %d already entered.",atoi(argv[i]));
                    cli_print(cli,"\n\tERROR!! Ext-Tele-Service-Map with Ext-Tele-Service - %d already entered.",atoi(argv[i]));
                }

                if(cli->ext_tele_srvc_count == MAX_TELE_SERVICE_MAP)
                {
                    cli_print(cli,"\n\tNOTE: Max Ext-Tele-Service-Map count %d is Reached",MAX_TELE_SERVICE_MAP);
                    CLI_ERROR_LOG("NOTE: Max Ext-Tele-Service-Map count %d is Reached",MAX_TELE_SERVICE_MAP);
                }

            }
            else
            {
                CLI_ERROR_LOG("ERROR!! Max %d Ext-Tele-Service-Map are allowed to be configured. First %d Ext-Tele-Service-Map are considered for the configuration.",MAX_TELE_SERVICE_MAP,MAX_TELE_SERVICE_MAP);
                cli_print(cli,"\n\tERROR!! Max %d Ext-Tele-Service-Map are allowed to be configured. First %d Ext-Tele-Service-Map are considered for the configuration.",MAX_TELE_SERVICE_MAP,MAX_TELE_SERVICE_MAP);
            }
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_tele_service_map_count = cli->ext_tele_srvc_count;

        }
        else if(!strcmp(argv[i],"ext-bearer-srvc"))
        {
            i++;
            int found = 0, j = 0;
            if(cli->ext_bearer_srvc_count < MAX_BEARER_SERVICE_MAP)
            {
                if(cli->ext_bearer_srvc_count)
                {
                    for(j=0;j<=cli->ext_bearer_srvc_count;j++)
                    {
                        if(cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service[j] == atoi(argv[i]))
                            found++;
                    }
                }
                if(!found)
                {
                    cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service[cli->ext_bearer_srvc_count] = atoi(argv[i]);
                    CLI_DEBUG_LOG("Ext-Bearer-Service = %d",atoi(argv[i]));
                    if(argv[i+CMD_LINE_ARG_TWO])
                    {
                        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.bearer_service_id[cli->ext_bearer_srvc_count] = atoi(argv[i+CMD_LINE_ARG_TWO]);
                        CLI_DEBUG_LOG("Bearer-Service-id = %d",atoi(argv[i+CMD_LINE_ARG_TWO]));
                    }
                    cli->ext_bearer_srvc_count++;
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! Ext-Bearer-Service-Map with Ext-Bearer-Service - %d already entered.",atoi(argv[i]));
                    cli_print(cli,"\n\tERROR!! Ext-Bearer-Service-Map with Ext-Bearer-Service - %d already entered.",atoi(argv[i]));
                }

                if(cli->ext_bearer_srvc_count == MAX_BEARER_SERVICE_MAP)
                {
                    cli_print(cli,"\n\tNOTE: Max Ext-Bearer-Service-Map count %d is Reached",MAX_BEARER_SERVICE_MAP);
                    CLI_ERROR_LOG("NOTE: Max Ext-Bearer-Service-Map count %d is Reached",MAX_BEARER_SERVICE_MAP);
                }

            }
            else
            {
                CLI_ERROR_LOG("ERROR!! Max %d Ext-Bearer-Service-Map are allowed to be configured. First %d Ext-Bearer-Service-Map are considered for the configuration.",MAX_BEARER_SERVICE_MAP,MAX_BEARER_SERVICE_MAP);
                cli_print(cli,"\n\tERROR!! Max %d Ext-Bearer-Service-Map are allowed to be configured. First %d Ext-Bearer-Service-Map are considered for the configuration.",MAX_BEARER_SERVICE_MAP,MAX_BEARER_SERVICE_MAP);
            }
            cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.ext_bearer_service_map_count = cli->ext_bearer_srvc_count;
        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int check_for_invalid_idp_sms_config(struct cli_def *cli)
{

    if(cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sms_node == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.client_addr[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.originator_sccp_addr[0] == INVALID_STR ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.reply_path_request == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.msc_service_specific_type == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sgsn_service_specific_type == INVALID_NUM ||
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.service_context_id[0] == INVALID_STR)
        return CLI_ERROR;

    return CLI_OK;

}

void init_cap_ro_idp_sms_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigKeyInfo.translator_name[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sms_node = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.client_addr[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.originator_sccp_addr[0] = INVALID_STR;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.reply_path_request = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.msc_service_specific_type = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sgsn_service_specific_type = INVALID_NUM;
    cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.service_context_id[0] = INVALID_STR;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_cap_ro_idp_sms_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_cap_ro_idp_sms_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    CLI_DEBUG_LOG("Translator = CAP-Ro");
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        init_cap_ro_idp_sms_config(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "idp-sms")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"sms-node"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sms_node = atoi(argv[i]);
            CLI_DEBUG_LOG("SMS-Node = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"client-addr"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.client_addr, argv[i], MAX_FIELD_NAME -1);
            CLI_DEBUG_LOG("Client-Addr = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"org-sccp-addr"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.originator_sccp_addr, argv[i], MAX_FIELD_NAME -1);
            CLI_DEBUG_LOG("Originator-Sccp-addr = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"reply-path-request"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.reply_path_request = atoi(argv[i]);
            CLI_DEBUG_LOG("Reply-Path-Request = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"service-Context-id"))
        {
            i++;
            strncpy(cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.service_context_id, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Service Context Id = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"msc-Srvc-specific-type"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.msc_service_specific_type = atoi(argv[i]);
            CLI_DEBUG_LOG("MSC-Service-Specific-Type = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"sgsn-srvc-specific-type"))
        {
            i++;
            cli->req.IWFPayload.capRoIDPSMSConfigPayload.capRoIDPSMSConfigInfo.sgsn_service_specific_type = atoi(argv[i]);
            CLI_DEBUG_LOG("SGSN-Service-Specific-Type = %d",atoi(argv[i]));
        }
        i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_activate_association(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_activate_association_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    cli->req.IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname[0] = INVALID_STR;

    while(argv[i])
    {
        if(!strcmp(argv[i],"assoc-state"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG(" Association = %s", argv[i]);
        }
        else if(!strcmp(argv[i],"enable"))
        {
            cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.status = ENABLE;
            CLI_DEBUG_LOG(" Status = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"disable"))
        {
            cli->req.IWFPayload.associationConfigPayload.associationConfigInfo.status = DISABLE;
            CLI_DEBUG_LOG(" Status = %s",argv[i]);
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_activate_associationSet(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_activate_associationSet_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname[0] = INVALID_STR;

    while(argv[i])
    {
        if(!strcmp(argv[i],"associationSet-state"))
        {
            i++;
            strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG(" AssociationSet = %s", argv[i]);
        }
        else if(!strcmp(argv[i],"enable"))
        {
            cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.status = ENABLE;
            CLI_DEBUG_LOG(" Status = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"disable"))
        {
            cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.status = DISABLE;
            CLI_DEBUG_LOG(" Status = %s",argv[i]);
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_ual_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_show_ual_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_sigtran_local_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_show_local_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_S6aMAP_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_show_s6amap_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
    req.cmd_id = C_cli_show_s6amap_sgsn_addr_config_Id;
    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
    req.cmd_id = C_cli_show_s6amap_sgsn_prefix_config_Id;
    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_MAPS6a_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_show_maps6a_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_CAPRo_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    if(!strcmp(argv[CMD_LINE_ARG_ONE],"cap-ro-idp-config"))
    {
        req.cmd_id = C_cli_show_capro_idp_config_Id;
        CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
        cli->has_capro_idp_config = YES;
        send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
        if(cli->has_capro_idp_config != NO)
        {
            req.cmd_id = C_cli_show_capro_idp_ext_tele_config_Id;
            CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
            send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
            req.cmd_id = C_cli_show_capro_idp_ext_bearer_config_Id;
            CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
            send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
        }
    }
    else
    {
        req.cmd_id = C_cli_show_capro_idpsms_config_Id;
        send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
    }

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_sctp_profile_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename[0] = INVALID_STR;

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_sctp_profile_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_sctp_profile_config_Id;
        strncpy(req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" Sctp-Profile = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_sctp_endpoint_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint[0] = INVALID_STR;
    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_sctp_endpoint_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_sctp_endpoint_config_Id;
        strncpy(req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" Sctp-EndPoint = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_association_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_association_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_association_config_Id;
        strncpy(req.IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" Association = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_associationset_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_associationset_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_associationset_config_Id;
        strncpy(req.IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" AssociationSet = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_destination_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_destination_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_destination_config_Id;
        strncpy(req.IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" Destination = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_remoteroute_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_remoteroute_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_remoteroute_config_Id;
        strncpy(req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" RemoteRoute = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_translatorrule_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        req.cmd_id = C_cli_show_all_translatorrule_config_Id;
    }
    else
    {
        req.cmd_id = C_cli_show_translatorrule_config_Id;
        strncpy(req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigKeyInfo.rule_name, argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" TranslatorRule = %s",argv[CMD_LINE_ARG_THREE]);
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_showIwfVersion(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));
    req.cmd_id = C_cli_show_iwf_version_Id;

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_cap_timers(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.no_activity_timer = INVALID_NUM;
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.retry_count = INVALID_NUM;
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.response_timeout = INVALID_NUM;
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.voice_no_answer_timer = INVALID_NUM;
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.network_delay_timer = INVALID_NUM;
    cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.sms_no_event_timer = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_cap_timers(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_cap_timers_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    init_cap_timers(cli);

    while(argv[i])
    {
        if(!strcmp(argv[i],"no-activity-timer"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.no_activity_timer = atoi(argv[i]);
            CLI_DEBUG_LOG(" No-Activity-Timer = %d", atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"retry-count"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.retry_count = atoi(argv[i]);
            CLI_DEBUG_LOG(" Retry-Count = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"response-timeout"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.response_timeout = atoi(argv[i]);
            CLI_DEBUG_LOG(" Response-TimeOut = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"voice-no-answer-timer"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.voice_no_answer_timer = atoi(argv[i]);
            CLI_DEBUG_LOG(" Voice-No-Answer-Timer = %d", atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"network-delay-timer"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.network_delay_timer = atoi(argv[i]);
            CLI_DEBUG_LOG(" Network-Delay-Timer = %d", atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"sms-no-event-timer"))
        {
            i++;
            cli->req.IWFPayload.capProtoTimersConfigPayload.capProtoTimersConfigInfo.sms_no_event_timer = atoi(argv[i]);
            CLI_DEBUG_LOG(" SMS-No-Event-Timer = %d", atoi(argv[i]));
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_cap_timers(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));
    req.cmd_id = C_cli_show_cap_timers_Id;

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_feature_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"followOn-TAns-trigger-config")){
        req.cmd_id = C_cli_show_tAns_trigger_config_Id;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ONE],"congestion-management-config")){
        req.cmd_id = C_cli_show_congestion_management_config_Id;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_log_cdr(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));
    req.cmd_id = C_cli_show_log_cdr_Id;

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_feature_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name[0] = INVALID_STR;
    cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = INVALID_NUM;
    cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.maxNumberOfCalls = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_feature_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    cli->req.cmd_id = C_cli_tAns_trigger_config_Id;
    init_feature_config(cli);

    while(argv[i])
    {
        if(!strcmp(argv[i],"follow-on-TAns-trigger"))
        {
            strncpy(cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name,
                    "FOLLOWON_TANS_TRIGGER", MAX_FIELD_NAME - 1);
            cli->req.cmd_id = C_cli_tAns_trigger_config_Id;
        }
        else if(!strcmp(argv[i],"congestion-management"))
        {
            strncpy(cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name,
                    "CONGESTION_MANAGEMENT", MAX_FIELD_NAME - 1);
            cli->req.cmd_id = C_cli_congestion_management_config_Id;
            if(!strcmp(argv[i],"enable"))
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = ENABLE;
            else
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = DISABLE;
        }
        else if(!strcmp(argv[i],"enable"))
        {
            cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = ENABLE;
            CLI_DEBUG_LOG("Status = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"disable"))
        {
            cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = DISABLE;
            CLI_DEBUG_LOG("Status = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"max-num-of-calls"))
        {
            i++;
            CLI_DEBUG_LOG("Max Number of sessions to hold = %lld",atoll(argv[i]));
            cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.maxNumberOfCalls = atoll(argv[i]);
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_log_cdr_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ONE;

    cli->req.cmd_id = C_cli_log_cdr_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    init_feature_config(cli);
    strncpy(cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigKeyInfo.feature_name, "LOG_CDR", MAX_FIELD_NAME - 1);

    while(argv[i])
    {
        if(!strcmp(argv[i],"enable"))
        {
            i++;
            if(!strcmp(argv[i],"failed-calls-only"))
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = ENABLE_ONLY_FAILED_CALLS;
            else
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = ENABLE_ALL_CALLS;
            CLI_DEBUG_LOG(" Enable - %s", argv[i]);
        }
        else if(!strcmp(argv[i],"disable"))
        {
            i++;
            if(!strcmp(argv[i],"success-calls-only"))
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = DISABLE_ONLY_SUCCESS_CALLS;
            else
                cli->req.IWFPayload.iwfFeatureConfigPayload.iwfFeatureConfigInfo.status = DISABLE_ALL_CALLS;
            CLI_DEBUG_LOG(" Disable - %s", argv[i]);
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_dcca_general_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    for(i = 0; i < MAX_FEATURE_COUNT; i++)
    {
        cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[i][0] = INVALID_STR;
        cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[i] = INVALID_NUM;
    }
    cli->dcca_feature_count = 0;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_dcca_general_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_dcca_general_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    init_dcca_general_config(cli);

    while(argv[i])
    {
        if(!strcmp(argv[i],"tx-timeout"))
        {
            strncpy(cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[0], "TX_TIMEOUT", MAX_FIELD_NAME - 1);
            i++;
            cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[0] = atoi(argv[i]);
            CLI_DEBUG_LOG(" Tx-TimeOut = %d", atoi(argv[i]));
        }
        i++;
    }

    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_failure_handling_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    int j = 0;
    cli->req.cmd_id = C_cli_dcca_failure_handling_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);

    j = cli->dcca_feature_count;
    while(argv[i])
    {
        if(!strcmp(argv[i],"initial-action"))
        {
            strncpy(cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[j], "INITIAL_ACTION", MAX_FIELD_NAME - 1);
            i++;
            if(!strcmp(argv[i],"retry-and-terminate"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = RETRY_AND_TERMINATE;
            else if(!strcmp(argv[i],"continue"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = CONTINUE;
            else if(!strcmp(argv[i],"terminate"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = TERMINATE;
            CLI_DEBUG_LOG(" InitialAction - %s", argv[i]);
            cli->dcca_feature_count++;
        }
        else if(!strcmp(argv[i],"update-action"))
        {
            strncpy(cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigKeyInfo.dcca_feature_name[j], "UPDATE_ACTION", MAX_FIELD_NAME - 1);
            i++;
            if(!strcmp(argv[i],"retry-and-terminate"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = RETRY_AND_TERMINATE;
            else if(!strcmp(argv[i],"continue"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = CONTINUE;
            else if(!strcmp(argv[i],"terminate"))
                cli->req.IWFPayload.iwfDccaGeneralConfigPayload.iwfDccaGeneralConfigInfo.dcca_feature_value[j] = TERMINATE;
            CLI_DEBUG_LOG(" UpdateAction - %s", argv[i]);
            cli->dcca_feature_count++;
        }
        i++;
    }

    cli->allow_exit=0;

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_dcca_dest_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    for(i = 0; i < MAX_DCCA_ENDPOINTS; i++)
    {
        cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.endPoint[i][0] = INVALID_STR;
        cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.priority[i] = INVALID_NUM;
    }
    cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.sendCCRT = INVALID_NUM;
    cli->dcca_endpoint_count = 0;
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_clearsession(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ONE;

    cli->req.cmd_id = C_cli_clear_session_config_Id;
    if(!strcmp(argv[i],"imsi"))
    {
        i++;
        int j = 0;
        for(j = 0; j < strlen(argv[i]) ; j++)
        {
            if(!isdigit(argv[i][j]))
            {
                cli_error(cli,"\n\tError: Invalid imsi entered : %s.",argv[i]);
                CLI_ERROR_LOG("Invalid imsi entered : %s.",argv[i]);
                return CLI_ERROR;
            }
        }

        strncpy(cli->req.IWFPayload.ImsiForSessionClearance, argv[i], MAX_IMSI_LENGTH -1);
        CLI_DEBUG_LOG("Imsi = %s",argv[i]);
    }
    else if(!strcmp(argv[i],"all"))
    {
        strncpy(cli->req.IWFPayload.ImsiForSessionClearance, argv[i], MAX_IMSI_LENGTH -1);
        CLI_DEBUG_LOG("Imsi = %s",argv[i]);
    }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_dcca_dest_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;

    cli->req.cmd_id = C_cli_dcca_dest_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        init_dcca_dest_config(cli);
        if(!strcmp(argv[i],"dest-realm"))
        {
            cli->req.cmd_id = C_cli_dcca_dest_realm_config_Id;
        }
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "endpoint")){
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    int j = cli->dcca_endpoint_count;
    while(argv[i])
    {
        if(!strcmp(argv[i],"send-ccrt"))
        {
            i++;
            CLI_DEBUG_LOG("sendCCRT = %s",argv[i]);
            if(!strcasecmp(argv[i],"Yes"))
                cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.sendCCRT = ENABLE;
            else
                cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.sendCCRT = DISABLE;
        }
        else if(!strcmp(argv[i],"dest-realm"))
        {
            i++;
            strncpy(cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm, argv[i], MAX_FIELD_NAME -1);
            CLI_DEBUG_LOG("Dest-Realm = %s",argv[i]);
        }
        else if(cli->dcca_endpoint_count != MAX_DCCA_ENDPOINTS)
        {
            if(!strcmp(argv[i],"endpoint"))
            {
                i++;
                strncpy(cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.endPoint[j], argv[i], MAX_FIELD_NAME -1);
                CLI_DEBUG_LOG("EndPoint = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"priority"))
            {
                i++;
                cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigInfo.priority[j] = atoi(argv[i]);
                CLI_DEBUG_LOG("Priority = %d",atoi(argv[i]));
                cli->dcca_endpoint_count++;
            }
        }
        else
        {
            CLI_ERROR_LOG("Max EndPoints %d already configured.",MAX_DCCA_ENDPOINTS);
            cli_print(cli,"\n\tError: Max EndPoints %d already configured.",MAX_DCCA_ENDPOINTS);
            CLI_DEBUG_LOG(" Exited ");
            return CLI_OK;
        }
       i++;
    }
    if(cli->req.OP_CODE == ADD || cli->req.OP_CODE == MODIFY)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_show_dcca_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    //GetConfigReq req;
    //memset(&req, 0, sizeof(req));

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"dcca-general-config"))
    {
        //req.cmd_id = C_cli_show_dcca_general_config_Id;
        cli->req.cmd_id = C_cli_show_dcca_general_config_Id;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ONE],"dcca-dest-config"))
    {
        //req.cmd_id = C_cli_show_dcca_dest_config_Id;
        cli->req.cmd_id = C_cli_show_dcca_dest_config_Id;
        cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm[0] = INVALID_STR;
        strncpy(cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm,
                argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME -1);
        CLI_DEBUG_LOG(" Destination = %s",argv[CMD_LINE_ARG_TWO]);
    }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    //send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_show_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    init_protocolactions_config(cli);

    cli->req.cmd_id = C_cli_show_protocolactions_config_Id;
    if(!strcmp(argv[CMD_LINE_ARG_ONE],"protocol-action-rule"))
    {
        if(!strcmp(argv[CMD_LINE_ARG_TWO],"rule"))
        {
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name,
                    argv[CMD_LINE_ARG_THREE], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG(" RuleName = %s",argv[CMD_LINE_ARG_THREE]);
        }
    }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

void init_protocolactions_config(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0, j = 0, k = 0;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol[0] = INVALID_STR;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name[0] = INVALID_STR;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId[0] = INVALID_STR;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_callscenarios = 0;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_eventtypes = 0;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_callscenario = INVALID_NUM;
    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_eventType = INVALID_NUM;
    for(i = 0; i < MAX_CALL_SCENARIOS; i++)
    {
        cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[i][0] = INVALID_STR;
        for(j = 0; j < MAX_EVENT_TYPES; j++)
        {
            cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[i][j][0] = INVALID_STR;
            for(k = 0; k < MAX_EVENT_TYPES_CONFIG; k++)
            {
                cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[i][j][k][0] = INVALID_STR;
                cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.legId[i][j][k][0] = INVALID_STR;
            }
        }
    }
    CLI_DEBUG_LOG(" Exited ");
}

int cli_int_delete_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        init_protocolactions_config(cli);
        if(!strcmp(argv[i],"rrb-rule"))
        {
            cli->req.cmd_id = C_cli_protocol_actions_Id;
        }
        else if(!strcmp(argv[i],"call-scenario"))
        {
            i = CMD_LINE_ARG_TWO;
            cli->req.cmd_id = C_cli_no_call_scenario_config_Id;
        }
        else if(!strcmp(argv[i],"event-type"))
        {
            i = CMD_LINE_ARG_TWO;
            cli->req.cmd_id = C_cli_no_eventtype_config_Id;
        }
        else if(!strcmp(argv[i],"event-config"))
        {
            i = CMD_LINE_ARG_TWO;
            cli->req.cmd_id = C_cli_no_eventspecific_config_Id;
        }
    }
    strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId, "RRB", MAX_FIELD_NAME - 1);
    while(argv[i])
    {
        if(!strcmp(argv[i],"rrb-rule"))
        {
            i++;
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol, "CAP", MAX_FIELD_NAME - 1);
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name, argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("RuleName = %s", argv[i]);
        }
        else if(!strcmp(argv[i],"call-scenario"))
        {
            i++;
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[0], argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("CallScenario = %s", argv[i]);
        }
        else if(!strcmp(argv[i],"event-type"))
        {
            i++;
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[0][0], argv[i], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("EventType = %s", argv[i]);
        }
        else if(!strcmp(argv[i],"monitorMode"))
        {
            i++;
            CLI_DEBUG_LOG("MonitorMode = %s", argv[i]);
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[0][0][0], argv[i], MAX_FIELD_NAME - 1);
        }
        else if(!strcmp(argv[i],"legId"))
        {
            i++;
            CLI_DEBUG_LOG("LegId = %s", argv[i]);
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.legId[0][0][0], argv[i], MAX_FIELD_NAME - 1);
        }
        i++;
    }
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ZERO;
    int j = 0;
    while(argv[i])
    {
        if(!strcmp(argv[i],"call-scenario"))
        {
            i++;
            int num_of_call_scenarios = cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_callscenarios;
            bool call_scenario_already_entered = false;
            CLI_DEBUG_LOG("CallScenario = %s", argv[i]);
            for(j = 0; j < num_of_call_scenarios ; j++)
            {
                if(!strcmp(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[j], argv[i]))
                {
                    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_callscenario = j;
                    call_scenario_already_entered = true;
                    break;
                }
            }
            if(!call_scenario_already_entered)
            {
                //If not entered add to the configuration
                strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.callscenario[num_of_call_scenarios],
                        argv[i], MAX_FIELD_NAME - 1);
                cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_callscenario = num_of_call_scenarios;
                ++cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_callscenarios;
            }
            cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_eventtypes = 0;
            cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_eventType = 0;
        }
        else if(!strcmp(argv[i],"event-type-mo-capv1") ||
                !strcmp(argv[i],"event-type-mo-capv2") ||
                !strcmp(argv[i],"event-type-mt-capv1") ||
                !strcmp(argv[i],"event-type-mt-capv2") ||
                !strcmp(argv[i],"event-type-sms-capv3"))
        {
            cli->req.cmd_id = C_cli_protocol_actions_Id;
            i++;
            int current_callscenario = cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_callscenario;
            int num_of_eventtypes = cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_eventtypes;
            bool event_type_already_entered = false;
            CLI_DEBUG_LOG("EventType = %s", argv[i]);
            for (j = 0; j < num_of_eventtypes; j++)
            {
                if(!strcmp(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[current_callscenario][j], argv[i]))
                {
                    event_type_already_entered = true;
                    cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_eventType = j;
                    break;
                }
            }
            if(!event_type_already_entered)
            {
                //If not entered add to the configuration
                strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[current_callscenario][num_of_eventtypes],
                        argv[i], MAX_FIELD_NAME - 1);
                CLI_DEBUG_LOG("eventType[%d][%d] = %s",current_callscenario,num_of_eventtypes,cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.eventType[current_callscenario][num_of_eventtypes]);
                cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_eventType = num_of_eventtypes;
                    ++cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.num_of_eventtypes;
            }
        }
        else if(!strcmp(argv[i],"monitorMode"))
        {
            i++;
            int current_callscenario = cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_callscenario;
            int current_eventType = cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.current_eventType;
            CLI_DEBUG_LOG("MonitorMode = %s", argv[i]);
            for(j = 0; j < MAX_EVENT_TYPES_CONFIG ; j++)
            {
                if(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[current_callscenario][current_eventType][j][0] == INVALID_STR)
                {
                    strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[current_callscenario][current_eventType][j], argv[i], MAX_FIELD_NAME - 1);
                CLI_DEBUG_LOG("monitormode[%d][%d][%d] = %s",current_callscenario,current_eventType,j,cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.monitorMode[current_callscenario][current_eventType][j]);
                    i++;
                    if(argv[i] && !strcmp(argv[i],"legId"))
                    {
                        i++;
                        CLI_DEBUG_LOG("LegId = %s",argv[i]);
                        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigInfo.legId[current_callscenario][current_eventType][j], argv[i], MAX_FIELD_NAME - 1);
                    }
                    break;
                }
            }
        }
        i++;
    }
    cli->allow_exit=0;
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_dump_system_info(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    cli->req.cmd_id = C_cli_dump_system_info_config_Id;
    send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
