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

/*
 * *******************************************************************************
 * *      
 * *      
 * *******************************************************************************
 * *     
 * *      PROJECT         : DRE
 * *      FILE            : CliCallback.c
 * *      MODULE          : cli
 * *      ENGINEER        : Ananth, Prabhakar
 * *      DESCRIPTION     : The file includes call back function for all the cli
 * commands. User input after parsing is passed on to these callback functions.
 * Here command specific structures are  poplulated based on the user input and
 * configuration request is sent
 * *      HISTORY         : <Initial Implementation>
 * *      
 * *******************************************************************************
 * */
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

#undef CLI_DEBUG
#define SEND_ALL_REQ
#define ERLBF_ENABLE 0

extern void clisend(int port);
extern void send_receive_data(struct cli_def *cli,void* buf,int len,int cmdID,int interfaceID);

extern int dre_add_user();
extern int dre_delete_user();
extern int encryptPassword(unsigned char *pass,unsigned char *encryptedPassword);
extern int dre_verify_UserPasswd(unsigned char *user_password,unsigned char *encryptedPassword);
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_help(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    cli_error(cli, "\nCommands available:");
    cli_show_help(cli, cli->commands);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_quit(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    cli_set_privilege(cli, PRIVILEGE_UNPRIVILEGED);
    cli_set_configmode(cli, MODE_EXEC, NULL);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_QUIT;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_exit(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int prevmode;
    CLI_DEBUG_LOG("cli->mode = %d",cli->mode);

    if (cli->mode == MODE_EXEC)
    {
        if(cli->delusr == 1 || cli->req.cmd_id == C_cli_switchover_Id)
        {
            CLI_DEBUG_LOG(" cli->allow_exit = %c ",cli->allow_exit);
            if(cli->allow_exit == 'y') 
            {
                if(cli->req.cmd_id == C_cli_switchover_Id)
                {
                    //sending request for switchover
                    send_receive_data(cli, &cli->req, sizeof(cli->req), cli->req.cmd_id, 0);
                    memset(&cli->req, 0, sizeof(SetConfigReq));
                }
                else
                {
                    /*Allow to exit*/ 
                    cli->state = STATE_DELETE_USER_PASSWORD;
                }
            }
            else if(cli->allow_exit == 'n')
            {
                cli_set_configmode(cli, MODE_EXEC, NULL);
                CLI_DEBUG_LOG(" Exited ");
                cli->allow_exit = 0;
                return CLI_OK;
            }
            else if(cli->allow_exit != 'y' || cli->allow_exit != 'n')
            {
                cli_print(cli,"\n\t*** WRONG OPTION *** " );
                if(cli->req.cmd_id == C_cli_switchover_Id)
                    cli->state = STATE_ACTIVATE_SWITCHOVER;
                else
                    cli->state = STATE_EXIT_WITHOUT_SENT;
            }
            else {
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
        }
        else
        {
            CLI_DEBUG_LOG(" Exited ");
            return cli_int_quit(cli, command, argv, argc);
        }
    }

    if (cli->mode > MODE_CONFIG)
    {
        if((cli->mode  ==  MODE_CONFIG_PEER)||
                (cli->mode == MODE_CONFIG_LOCALHOST)||
                (cli->mode == MODE_MODIFY_LOCALHOST)||
                (cli->mode == MODE_CONFIG_LOCAL &&
                 (cli->req.OP_CODE == ADD || (cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_localconfig_Id)))||
                //check if nothing is set for modifying in SCTP Profile submode if commit is given
                (cli->mode == MODE_CONFIG_SCTP_PROFILE && 
                 ((cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_modify_sctp_profile_Id) || (cli->req.OP_CODE == ADD))) ||
                (cli->mode == MODE_CONFIG_ADD_SCTP_ENDPOINT) || 
                (cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT && cli->req.cmd_id == C_cli_modify_sctp_endpoint_Id) || 
                (cli->mode == MODE_CONFIG_ADD_ASSOCIATION) || 
                (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION && cli->req.cmd_id == C_cli_modify_assocation_Id) || 
                (cli->mode == MODE_CONFIG_ADD_ASSOCIATION_SET) ||
                (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET && cli->req.cmd_id == C_cli_assocation_set_Id) || 
                (cli->mode == MODE_CONFIG_DESTINATION &&
                 (cli->req.OP_CODE == ADD || (cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_destination_config_Id)))||
                (cli->mode == MODE_CONFIG_REMOTEROUTE &&
                 (cli->req.OP_CODE == ADD || (cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_remoteroute_config_Id))) ||
                (cli->mode == MODE_CONFIG_ADD_S6A_MAP) ||
                (cli->mode == MODE_CONFIG_ADD_MAP_S6A) ||
                (cli->mode == MODE_CONFIG_FAILURE_HANDLING && cli->req.cmd_id == C_cli_dcca_failure_handling_Id) ||
                (cli->mode == MODE_CONFIG_DCCA_DESTINATION && cli->req.cmd_id == C_cli_dcca_dest_config_Id) ||
                (cli->mode == MODE_TRANS_RULE_SS7) ||
                (cli->mode == MODE_TRANS_RULE_DIAMETER) ||
                (cli->mode == MODE_TRANS_RULE_HTTP) ||
                //check if nothing is set for modifying in s6a-MAP submode if exit is given
                (cli->mode == MODE_CONFIG_MODIFY_S6A_MAP && cli->req.cmd_id == C_cli_s6a_map_config_Id) ||
                (cli->mode == MODE_CONFIG_MODIFY_MAP_S6A && cli->req.cmd_id == C_cli_map_s6a_config_Id) ||
                //check if nothing is set for modifying in IDP submode if exit is given
                (cli->mode == MODE_CONFIG_CAP_RO_IDP && 
                 (cli->req.OP_CODE == ADD || (cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_cap_ro_idp_config_Id))) ||
                //check if nothing is set for adding or modifying in IDP_SMS submode if exit is given
                (cli->mode == MODE_CONFIG_CAP_RO_IDP_SMS && cli->req.cmd_id == C_cli_cap_ro_idp_sms_config_Id) ||
                (cli->mode == MODE_TRANS_RULE_SS7) ||
                (cli->mode == MODE_TRANS_RULE_DIAMETER) ||
                (cli->mode == MODE_TRANS_RULE_HTTP) ||
                (cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO && cli->req.cmd_id == C_cli_protocol_actions_Id) ||
                ((cli->mode == MODE_CONFIG_ERLBF) && (cli->req.cmd_id == C_cli_set_erlbf_peer_group_Id)) ||
                ((cli->mode == MODE_PEER_DICTIONARY) && (cli->req.cmd_id == C_cli_peer_dictionary_Id)) ||
                ((cli->mode == MODE_CONFIG_ADD_ERLBF_PEER) && ((cli->req.cmd_id == C_cli_set_erlbf_peer_group_Id) || (cli->req.cmd_id == C_cli_set_erlbf_peer_config_Id ))) ||
                ((cli->mode  ==  MODE_CONFIG_REALM) && ((cli->req.cmd_id == C_cli_RealmDestination_Id) || (cli->req.cmd_id == C_cli_configRealm_Id)))) 
        {
            CLI_DEBUG_LOG(" cli->allow_exit = %c ",cli->allow_exit);
            if(!cli->allow_exit)
            {
                cli->state = STATE_EXIT_WITHOUT_SENT;
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
            else if(cli->allow_exit == 'y') 
            {
                /*Allow to delete Peer-group*/
                if(cli->mode == MODE_CONFIG_ERLBF)
                {
                    send_receive_data(cli, &cli->req, sizeof(cli->req), cli->req.cmd_id, 0);
                    memset(&cli->req, 0, sizeof(SetConfigReq));
                }
                else
                {
                    /*Allow to exit*/
                    memset(&cli->req, 0, sizeof(SetConfigReq)); 
                    prevmode = cli_track_configmode(cli, 0, 0, false);
                    cli_set_configmode(cli, prevmode, NULL);
                }
            }
            else if(cli->allow_exit == 'n')
            {
                if(cli->mode == MODE_CONFIG_ERLBF)
                    memset(&cli->req, 0, sizeof(SetConfigReq));
                cli_set_configmode(cli, cli->mode, NULL);
                cli->allow_exit = 0;
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
            else if(cli->allow_exit != 'y' || cli->allow_exit != 'n')
            {
                cli_print(cli,"\n\t*** WRONG OPTION *** " );
                cli->state = STATE_EXIT_WITHOUT_SENT;
            }
            else {
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
        }
        else if((cli->mode == MODE_CONFIG_LOCAL_PCSSN)||
                (cli->mode == MODE_CONFIG_LOCAL_GT)||
                (cli->mode == MODE_CONFIG_DESTINATION_GT)||
                (cli->mode == MODE_CONFIG_DESTINATION_PCSSN) ||
                (cli->mode == MODE_CONFIG_MO_CAP_V1) ||
                (cli->mode == MODE_CONFIG_MO_CAP_V2) ||
                (cli->mode == MODE_CONFIG_MT_CAP_V1) ||
                (cli->mode == MODE_CONFIG_MT_CAP_V2) ||
                (cli->mode == MODE_CONFIG_SMS_CAP_V3))
        {
            prevmode = cli_track_configmode(cli, 0, 0, false);
            cli_set_configmode(cli, prevmode, NULL);
        }
        else {
            memset(&cli->req, 0, sizeof(SetConfigReq));
            prevmode = cli_track_configmode(cli, 0, 0, false);
            cli_set_configmode(cli, prevmode, NULL);
        }
    }
    else
        cli_set_configmode(cli, MODE_EXEC, NULL);
    cli->service = NULL;
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_history(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    int i;

    cli_error(cli, "\nCommand history:");
    for (i = 0; i < MAX_HISTORY; i++)
    {
        if (cli->history[i])
            cli_error(cli, "%3d. %s", i, cli->history[i]);
    }
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_enable(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    if (cli->privilege == PRIVILEGE_SEC_ADMIN)
    {
        CLI_DEBUG_LOG(" Exited ");
        return CLI_OK;
    }

    if (!cli->enable_password && !cli->enable_callback)
    {
        /* no password required, set privilege immediately */
        cli_set_privilege(cli, PRIVILEGE_PRIVILEGED);
        cli_set_configmode(cli, MODE_EXEC, NULL);
    }
    else
    {
        /* require password entry */
        cli->state = STATE_ENABLE_PASSWORD;
    }
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_disable(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    cli_set_privilege(cli, cli->privilege);
    CLI_DEBUG_LOG("cli->privilege = %d",cli->privilege);
    CLI_DEBUG_LOG("mode = %d",MODE_EXEC);
    cli_set_configmode(cli, MODE_EXEC, NULL);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_peerControl(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i=0;
    int interfaceID = 0;
    SetConfigReq req;
    memset(&req,0,sizeof(SetConfigReq));

    req.cmd_id = C_cli_peerControl_Id;
    CLI_DEBUG_LOG("cmdID = %d",C_cli_peerControl_Id);
    while(argv[i]){

        if(!strcmp(argv[i],"host")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("HostName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"enable")){
            req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.Enable_Status = ENABLE;
            CLI_DEBUG_LOG("Enable_Status = %s",argv[i]);
        }else if(!strcmp(argv[i],"disable")){
            req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.Enable_Status = DISABLE;
            CLI_DEBUG_LOG("Enable_Status = %s",argv[i]);
        }else if(!strcmp(argv[i],"restart")){
            req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.Enable_Status = PEER_RESTART;
            CLI_DEBUG_LOG("Enable_Status = %s",argv[i]);
        }
        i++;

    }
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,interfaceID);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_showpeer(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i;
    GetConfigReq req; 
    memset(&req,0,sizeof(GetConfigReq));
    req.cmd_id = 0;
    //check if the string is not peer-config and peer-status
    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }
    req.shReqPayload.dreKeyInfo.peerKeyInfo.HostName[0] = INVALID_STR;
    req.shReqPayload.dreKeyInfo.peerKeyInfo.RealmName[0] = INVALID_STR;
    if (!strcmp("peer-config",argv[CMD_LINE_ARG_ONE]))
    {
        if(!strcmp("all",argv[CMD_LINE_ARG_TWO]))
        {
            CLI_DEBUG_LOG("cmdId = %d",C_cli_showallpeer_Id);
            send_receive_data(cli,&req,sizeof(req),C_cli_showallpeer_Id,0);
            CLI_DEBUG_LOG(" Exited ");
            return CLI_OK;
        }
        else
            req.cmd_id = C_cli_showpeerconfig_Id;

    }
    else if(!strcmp("peer-status",argv[CMD_LINE_ARG_ONE]))
    {
        if(!strcmp("all",argv[CMD_LINE_ARG_TWO]))
        {
            CLI_DEBUG_LOG("cmdId = %d",C_cli_showpeerstatus_Id);
            send_receive_data(cli,&req,sizeof(req),C_cli_showpeerstatus_Id,0);
            CLI_DEBUG_LOG(" Exited ");
            return CLI_OK;
        }
        else
        {
            req.cmd_id = C_cli_showpeer_Id;
        }
    }
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    i = CMD_LINE_ARG_TWO;
    while(argv[i] && argv[i + 1]){

        if(!strcmp(argv[i],"host")){
            i++;
            strncpy(req.shReqPayload.dreKeyInfo.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(req.shReqPayload.dreKeyInfo.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        i++;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);



#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/


int cli_int_showuser(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;

    memset(&req,0,sizeof(GetConfigReq));

    req.cmd_id = C_cli_showuser_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }
    req.shReqPayload.showID = SH_USERNAME;

    req.shReqPayload.dreKeyInfo.UserKeyInfo.UserName[0] = INVALID_STR;


    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);


#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/

int cli_int_showrealm(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;

    memset(&req, 0, sizeof(req));

    if(argv[CMD_LINE_ARG_TWO] == NULL)
        return CLI_ERROR;

    if(!strcmp("realm-config",argv[CMD_LINE_ARG_ONE]))
    {
        if(!strcmp("all",argv[CMD_LINE_ARG_TWO]))
            req.cmd_id = C_cli_showconfigallrealm_Id;
        else if(!strcmp("realm",argv[CMD_LINE_ARG_TWO]))
        {
            req.cmd_id = C_cli_showconfigrealm_Id;
            CLI_DEBUG_LOG("RealmName = %s",argv[CMD_LINE_ARG_THREE]);
            strncpy(req.shReqPayload.dreKeyInfo.realmKeyInfo.RealmName,argv[CMD_LINE_ARG_THREE],MAX_PARAM_SIZE - 1);
        }
    }
    else if(!strcmp("realm-route",argv[CMD_LINE_ARG_ONE]))
    {
        req.cmd_id = C_cli_showroute_Id;
        CLI_DEBUG_LOG("RealmName = %s",argv[CMD_LINE_ARG_TWO]);
        strncpy(req.shReqPayload.dreKeyInfo.realmKeyInfo.RealmName,argv[CMD_LINE_ARG_TWO],MAX_PARAM_SIZE - 1);
    }

    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id, CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    {
        int i;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }
#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}


int cli_int_showDiscoverPeer(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;

    memset(&req, 0, sizeof(req));
    req.cmd_id = C_cli_showDiscoverPeer_Id ;
    req.shReqPayload.showID = SH_DISCOVERED_PEERS;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);


#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_showNodeState(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_GetNodeState_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_showconfigavamgr(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));
    CLI_DEBUG_LOG("cmdId = %d",C_cli_showconfigavamgr_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_showconfigavamgr_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_switchover(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    CLI_DEBUG_LOG("cmdId = %d",C_cli_switchover_Id);
    cli->req.cmd_id = C_cli_switchover_Id;
    // changing cli state to activate switchover to confirm with user
    cli->state = STATE_ACTIVATE_SWITCHOVER;
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_showDiameterBaseConfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_showlocalhost_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    req.cmd_id = C_cli_showallpeer_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    req.cmd_id = C_cli_showrealm_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_showconfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));

    CLI_DEBUG_LOG("cmdId = %d",C_cli_showlocalhost_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_showlocalhost_Id,0);

#ifdef CLI_DEBUG       
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int verify_user_password(struct cli_def *cli,unsigned char *user, unsigned char *passwd)
{
    CLI_DEBUG_LOG(" Entered ");
    int result;
    GetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_verify_passwd_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
#if 0
    /*hardcoding user,passwd for testing purpose*/
    if(!strcmp((char*)user,(char*)"root")){
        if(!strcmp((char*)passwd,(char*)"intelliss7")){
            return 0;
        }else{
            return CLI_ERROR;
        }
    }
#endif
    cli->user_found = 0;
    strncpy((char*)req.shReqPayload.dreKeyInfo.UserKeyInfo.UserName,(char*)user,MAX_NAME_LEN - 1);
    CLI_DEBUG_LOG("User Name = %s",user);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    if(cli->user_found != AUTH_USER_NOT_FOUND) {
        result = dre_verify_UserPasswd(passwd,cli->user.encryptedPassword);
        if(!result){
            CLI_DEBUG_LOG(" Password Matched ");
        }else{
            CLI_ERROR_LOG(" Password Not Matched ");
        } 
    }else {
        CLI_DEBUG_LOG(" Exited ");
        return AUTH_USER_NOT_FOUND;
    }
    CLI_DEBUG_LOG(" Exited ");
    return result;

}

int adduser(struct cli_def *cli,unsigned char *user,unsigned char *passwd)
{
    CLI_DEBUG_LOG(" Entered ");
    unsigned char password[MAX_NAME_LEN];
    SetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_adduser_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    req.OP_CODE = ADD;
    CLI_DEBUG_LOG("OP_CODE - ADD");

    strncpy(req.Payload.dreUserConfigPayload.UserKeyInfo.UserName,cli->user.username,MAX_NAME_LEN - 1);
    CLI_DEBUG_LOG("User Name = %s",cli->user.username);
    req.Payload.dreUserConfigPayload.UserConfigInfo.privilege = cli->user.privilege;
    CLI_DEBUG_LOG("privilege = %d",cli->user.privilege);
    encryptPassword((unsigned char* )cli->user.password,(unsigned char*)password);
    CLI_DEBUG_LOG("Encrypted Password = %s",password);
    memcpy(req.Payload.dreUserConfigPayload.UserConfigInfo.password,password,16);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

    CLI_DEBUG_LOG(" Exited ");
    return 0;

}
/*********************************************************************************************



 *********************************************************************************************/

int deleteuser(struct cli_def *cli,unsigned char *user, unsigned char *psswd)
{
    CLI_DEBUG_LOG(" Entered ");
    char delusername[MAX_NAME_LEN];
    SetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_deleteuser_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    req.OP_CODE = DELETE;
    CLI_DEBUG_LOG("OP_CODE - DELETE");

    strncpy(delusername,cli->user.username,MAX_NAME_LEN - 1);
    CLI_DEBUG_LOG("User Name = %s",cli->user.username);

    if(!verify_user_password(cli,(unsigned char*)cli->loginuser,cli->user.password))
    {
        strncpy(req.Payload.dreUserConfigPayload.UserKeyInfo.UserName,delusername,MAX_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),C_cli_deleteuser_Id,0);
    }
    else
    {
        cli_print(cli, "\n\tInCorrect Password");
        CLI_ERROR_LOG(" InCorrect Password "); 
    }

    CLI_DEBUG_LOG(" Exited ");
    return 0;
}

/*********************************************************************************************



 *********************************************************************************************/

int modifyuser(struct cli_def *cli,unsigned char *user, unsigned char *psswd)
{
    CLI_DEBUG_LOG(" Entered ");
    unsigned char password[MAX_NAME_LEN];
    SetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_moduser_Id;
    CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
    req.OP_CODE = MODIFY;
    CLI_DEBUG_LOG("OP_CODE - MODIFY");

    if(cli->user.allowNewPassword == 'n')
    {  
        if(!verify_user_password(cli,(unsigned char*)cli->user.username,cli->user.password))
        {
            cli->user.allowNewPassword = 'y';
            cli->max_attempts = 0;
        }
        else {
            // if user doesn't exists
            if(cli->user_found == AUTH_USER_NOT_FOUND)
            {
                cli->state = STATE_NORMAL;
                CLI_DEBUG_LOG(" Exited ");
                return 0;
            }
            //if user exists and old password is wrong
            cli->max_attempts++;
            CLI_DEBUG_LOG("cli->max_attempts = %d",cli->max_attempts);
            cli->user.allowNewPassword = 'n';
            if(cli->max_attempts ==  MAX_LOGIN_ATTEMPTS)
            {
                cli_print(cli, "\n\n\tERROR! Maximum attempts reached. Try again with correct password.");
                CLI_ERROR_LOG("ERROR! Maximum attempts reached. Try again with correct password.");
                cli->state = STATE_NORMAL;
                cli->max_attempts = 0;
                CLI_DEBUG_LOG(" Exited ");
                return 0;
            }
            cli_print(cli, "\n\n\tOld Password did not match.");
            CLI_ERROR_LOG("Old Password did not match.");
        }
    }

    if(cli->user.setNewPassword == 'y') {
        req.cmd_id = C_cli_moduser_Id;
        CLI_DEBUG_LOG("cmdId = %d",req.cmd_id);
        req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");

        strncpy(req.Payload.dreUserConfigPayload.UserKeyInfo.UserName,cli->user.username,MAX_NAME_LEN - 1);
        encryptPassword((unsigned char* )cli->user.newPassword,(unsigned char*)password);
        memcpy(req.Payload.dreUserConfigPayload.UserConfigInfo.password,password,16);
        cli->user.setNewPassword = 'n';
        cli->user.verifyNewPassword = 'n';
        cli->user.allowNewPassword = 'n';   
        cli->privilege = PRIVILEGE_ADMIN;
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
        cli->state = STATE_NORMAL;
    }
    CLI_DEBUG_LOG(" Exited ");
    return 0;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_adduser(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    int OP_CODE = 0;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"modify")){
        i = CMD_LINE_ARG_TWO;
        OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }else {
        OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }


    while(argv[i]){
        if(!strcmp(argv[i],"username")){
            i++;
            if(argv[i])
            {
                strncpy(cli->user.username,argv[i],MAX_NAME_LEN - 1);
                CLI_DEBUG_LOG("username = %s",argv[i]);
            }
        }
        else if(!strcmp(argv[i],"group"))
        {
            i++;
            if(!strcmp(argv[i],"admin")){
                cli->user.privilege = PRIVILEGE_ADMIN;
                CLI_DEBUG_LOG("privilege = %s",argv[i]);
            }else if(!strcmp(argv[i],"operator")){
                cli->user.privilege = PRIVILEGE_OPERATOR;
                CLI_DEBUG_LOG("privilege = %s",argv[i]);
            }else
            {
                cli->user.privilege = PRIVILEGE_MIN;
                CLI_DEBUG_LOG("privilege",PRIVILEGE_MIN);
            }
        }
        else if(!strcmp(argv[i], "password"))
        {
            if(OP_CODE == MODIFY) {
                cli->max_attempts = 0;
                cli->user.allowNewPassword = 'n';
                cli->user.verifyNewPassword = 'n';
                cli->state = STATE_MOD_USER_PASSWORD;
            }
        }
        else {
            cli->max_attempts = 0;
            // default privelge while adding a user
            cli->user.privilege = PRIVILEGE_ADMIN;
            CLI_DEBUG_LOG("privilege set for user = %d",PRIVILEGE_ADMIN);
            cli->user.verifyNewPassword = 'n';
            cli->state = STATE_ADD_USER_PASSWORD;
        }
        i++;
    }

    CLI_DEBUG_LOG(" Exited ");
    return 0;

}

/*********************************************************************************************



 *********************************************************************************************/

int cli_int_deleteuser(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;

    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_deleteuser_Id;
    req.OP_CODE = DELETE;
    CLI_DEBUG_LOG("OP_CODE - DELETE");
    CLI_DEBUG_LOG("CmdID = %d",C_cli_deleteuser_Id);

    while(argv[i])
    {
        if(!strcmp(argv[i],"user"))
        {
            i++;
            if(argv[i]){
                if(strcmp(cli->loginuser,argv[i]))
                {
                    strncpy(cli->user.username,argv[i],MAX_NAME_LEN - 1);
                    CLI_DEBUG_LOG("username = %s",argv[i]);
                    cli->state = STATE_DELETE_USER_PASSWORD;
                    CLI_DEBUG_LOG("cli->state = %d",STATE_DELETE_USER_PASSWORD);
                }
                else if(strcmp("root",argv[i]))
                {
                    CLI_DEBUG_LOG("username = %s",argv[i]);
                    cli_print(cli,"\n\tERROR!! User is not allowed to delete root account.");
                    CLI_ERROR_LOG("ERROR!! User is not allowed to delete root account.");
                    return 0;
                }
                else
                {
                    cli_print(cli,"\n\tERROR!! User is not allowed to delete himself.");
                    CLI_ERROR_LOG("ERROR!! User is not allowed to delete himself.");
                    return 0;
#if 0
                    // code to ask user for confirmation when he is trying to delete himself               
                    cli_print(cli,"User you are deleting is logged in.User will be logged out if it is deleted...!!!");
                    cli_print(cli,"Do you still want to delete..? (y/n)");
                    strcpy(cli->user.username,argv[i]);
                    cli->state = STATE_USER_EXIT;
                    cli->allow_exit='y';
                    cli->state = STATE_DELETE_USER_PASSWORD;
#endif
                }
            }
        }
        i++;
    }
    CLI_DEBUG_LOG(" Exited ");
    return 0;

}

/*********************************************************************************************



 *********************************************************************************************/

int cli_int_configTerminal(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc))
{
    CLI_DEBUG_LOG(" Entered ");
    int oldmode;

    oldmode = cli_set_configmode(cli, MODE_CONFIG, "(config)");
    CLI_DEBUG_LOG("cli->mode = %d",MODE_CONFIG);
    cli_track_configmode(cli, oldmode, MODE_CONFIG,true);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_configPrompt(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int mode = MODE_EXEC, oldmode;
    char component[MAX_PARAM_SIZE] = {0};
    char *cptr;
    if((cptr = strstr(command, "dre")) != NULL)
    {
        strncpy(component, "dre",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_DRE;
    }
    else if((cptr = strstr(command, "avlmgr")) != NULL)
    {
        strncpy(component, "avlmgr",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_AVLMGR;
    }
    else if((cptr = strstr(command, "repl-mgr")) != NULL)
    {
        strncpy(component, "repl-mgr",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_REPMGR;
    }
    else if((cptr = strstr(command, "diameter-base")) != NULL)
    {
        strncpy(component, "diameter-base",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_DIABASE;
    }
    else if((cptr = strstr(command, "asf-mode")) != NULL)
    {
        strncpy(component, "asf",MAX_PARAM_SIZE - 1);
        mode = MODE_ASF_GROUP_TABLE;
    }
    else if((cptr = strstr(command, "general-config")) != NULL)
    {
        strncpy(component, "general-config",MAX_PARAM_SIZE - 1);
        mode = MODE_GENERAL_CONFIG;
    }
    else if((cptr = strstr(command, "sctp-config")) != NULL)
    {
        strncpy(component, "sctp-config",MAX_PARAM_SIZE - 1);
        mode = MODE_SCTP_CONFIG;
    }
    else if((cptr = strstr(command, "tls-config")) != NULL)
    {
        strncpy(component, "tls-config",MAX_PARAM_SIZE - 1);
        mode = MODE_TLS_CONFIG;
        cli_print(cli,"\n\tNOTE: Below are the Cipher-suites supported.");
        CLI_DEBUG_LOG("CmdID = %d",C_cli_show_ciphersuites_Id);
        // request to fetch the available cipher-suites to show to user 
        send_receive_data(cli,&cli->req,sizeof(cli->req),C_cli_show_ciphersuites_Id,0);
    }
    else if((cptr = strstr(command, "erlbf")) != NULL)
    {
        strncpy(component, "erlbf",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_ERLBF;
    }
    else if((cptr = strstr(command, "static-routing")) != NULL)
    {
        strncpy(component, "routing",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_STATIC_ROUTING;
    }
    else if((cptr = strstr(command, "transforms")) != NULL)
    {
        strncpy(component, "transforms",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_TRANSFORM;
    }
    else if((cptr = strstr(command, "peer-config")) != NULL)
    {
        strncpy(component, cli->req.Payload.peerGroupsPayload.peer_group.groupname,MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_MOD_ERLBF_PEER;
        //cli_int_getPeerIds(cli, command, argv, argc);
    }
    else if((cptr = strstr(command, "peer-group")) != NULL)
    {
        /*if the peer-group command add peer-group command, then only set to peer-config mode*/
        if((strcmp("no",argv[CMD_LINE_ARG_ZERO])==0) || (strcmp("modify",argv[CMD_LINE_ARG_ZERO])==0)) {
            strncpy(component, "erlbf",MAX_PARAM_SIZE - 1);
            mode = MODE_CONFIG_ERLBF;           
        }
        else {
            strncpy(component, cli->req.Payload.peerGroupsPayload.peer_group.groupname,MAX_PARAM_SIZE - 1);
            mode = MODE_CONFIG_ADD_ERLBF_PEER;
            cli_print(cli,"\n\tNOTE: Use lb-algo command and type commit for creating a peer-group\(if it has not been created yet).\
                \n\t      Use peer-name command and type commit to associate a peer to the existing peer-group.");
            //cli_int_getPeerIds(cli, command, argv, argc);
        }
    }
    else if ((strcmp("peer",argv[CMD_LINE_ARG_ZERO])==0) && (strcmp("host",argv[CMD_LINE_ARG_ONE])==0))
    {
        /* set to peer-config mode*/
        {
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "peer-");          
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
            mode = MODE_CONFIG_PEER;
            cli->req.OP_CODE = ADD;
            cli->req.cmd_id = C_cli_peer_Id; 
            init_peer(cli);
            //default values for timers
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue = 120;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue =30;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue =30;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.busyReconnectTimerVal = 1000;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.doNotWantToTalkToYouReconnectTimer = 1000;
#if DRE
            cli_print(cli," \n\tNOTE: ip (or) fqdn, port (or) secureport and atleast one dictionary are mandatory for adding the peer.");
#else
            cli_print(cli," \n\tNOTE: ip (or) fqdn, port and atleast one dictionary are mandatory for adding the peer.");
#endif
            send_receive_data(cli,&cli->req,sizeof(cli->req),C_cli_show_peerdictionary_Id,0);
            cli_print(cli,"\tNOTE: Upto %d dictionaries are allowed to be configured for a peer. Enter them one by one and type commit after you are done with the configuration.",MAX_DICTIONARY_NUM);
            dre_addPeer(cli, command, argv, argc);
        }
    }
    else if ((strcmp("modify",argv[CMD_LINE_ARG_ZERO])==0) && (strcmp("peer",argv[CMD_LINE_ARG_ONE])==0))
    {
        /* set to peer-config mode*/
        {
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-");           
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_THREE]);
            mode = MODE_CONFIG_PEER;
            cli->req.OP_CODE = MODIFY;
            cli->req.cmd_id = C_cli_modifypeer_Id; 
            init_peer(cli);
            send_receive_data(cli,&cli->req,sizeof(cli->req),C_cli_show_peerdictionary_Id,0);
            cli_print(cli,"\tNOTE: User can only add dictionaries\(up to %d),add secondary-ips and modify other values for a peer using modify peer command.\
                \n\t      Type commit after you are done with the configuration.",MAX_DICTIONARY_NUM);
            dre_addPeer(cli, command, argv, argc);
        }
    }
    else if ((strcmp("local-host",argv[CMD_LINE_ARG_ZERO])==0) && (strcmp("host",argv[CMD_LINE_ARG_ONE])==0))
    {
        /* set to localhost-config mode*/
        {
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "localhost-");         
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
            mode = MODE_CONFIG_LOCALHOST;
            init_localhost(cli);
            cli_print(cli,"\n\tNOTE: Upto 4 Local-Transports are allowed to be configured for a local-host\(one Local-Transport is mandatory).\
                \n\t      Upto 4 secondary-ips\(optional) are allowed for each Local-Transport if transport-type is SCTP.\
                \n\t      Enter them one by one and type commit after you are done with the configuration.");
            cli_int_localhost(cli, command, argv, argc);
        }
    }
    else if ((strcmp("modify",argv[CMD_LINE_ARG_ZERO])==0) && (strcmp("local-host",argv[CMD_LINE_ARG_ONE])==0))
    {
        /* set to localhost-modify-config mode*/
        {
            cli->localhost_mode = NO;
            init_localhost(cli);
            send_receive_data(cli,&cli->req,sizeof(cli->req),C_cli_get_localhostconfig_Id,0);
            if(cli->localhost_mode == YES)
                return CLI_ERROR;
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-");           
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_THREE]);         
            mode = MODE_MODIFY_LOCALHOST;
            cli_print(cli,"\n\tNOTE: Upto 4 Local-Transports are allowed to be configured for a local-host.\
                    \n\t      Upto 4 secondary-ips\(optional) are allowed for each Local-Transport if transport-type is SCTP.\
                \n\t      User can add or modify existing Local-Transports and can only add secondary-ips using transport-id's along with other configurations.");
            cli_int_modifylocalhost(cli, command, argv, argc);
        }
    }
    else if (strcmp("realm",argv[CMD_LINE_ARG_ZERO])==0)
    {   
        init_realm(cli);
        mode = MODE_CONFIG_REALM;
        cli_print(cli,"\n\tNOTE: Realm should have been added before associating a peer to the Realm.\
                \n\t      Use local-action command and type commit for creating a Realm\(if it has not been created yet).\
            \n\t      Use route command and type commit to associate a peer to the existing realm.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "realm-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_configRealm(cli, command, argv, argc);  
    }
    else if (strcmp("dest-host",argv[CMD_LINE_ARG_ZERO])==0)
    {
        init_staticrouting(cli);
        mode = MODE_STATIC_PEER_CONFIG;
        cli_print(cli,"\n\tNOTE: Use static-peer command and type commit to associate a peer for static routing.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "dest-host-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_staticrouting(cli, command, argv, argc); 
    }
    else if (strcmp("dictionary",argv[CMD_LINE_ARG_ZERO])==0)
    {
        mode = MODE_PEER_DICTIONARY;
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "dict-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        init_peerdictionary(cli);
        send_receive_data(cli,&cli->req,sizeof(cli->req),C_cli_show_peerdictionary_Id,0);
        cli_print(cli,"\tNOTE: Upto 8 dictionaries are allowed to be configured for a peer. Enter them one by one and type commit after you are done with the configuration");
        cli_int_configDictionary(cli, command, argv, argc);     
    }
    else if((cptr = strstr(command, "sigtran")) != NULL)
    {
        strncpy(component, "sigtran",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_SIGTRAN;
    }
    else if((cptr = strstr(command, "SCTP")) != NULL)
    {
        strncpy(component, "SCTP",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_SIGTRAN_SCTP;
    }
    else if((cptr = strstr(command, "M3UA")) != NULL)
    {
        strncpy(component, "M3UA",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_SIGTRAN_M3UA;
    }
    else if((cptr = strstr(command, "iwf")) != NULL)
    {
        strncpy(component, "iwf",MAX_PARAM_SIZE - 1);
        mode = MODE_CONFIG_IWF;
    }
    else if (!strcmp("local",argv[CMD_LINE_ARG_ZERO]))
    {
        init_localconfig(cli);
        mode = MODE_CONFIG_LOCAL;
        cli->req.OP_CODE = ADD;
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "local"); 
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("local",argv[CMD_LINE_ARG_ONE]))
    {
        init_localconfig(cli);
        cli->req.OP_CODE = MODIFY;
        mode = MODE_CONFIG_LOCAL;
        cli_print(cli,"\n\tNOTE: User can modify required parameters for a local-host under this mode.\
                \n\t      Type commit after you are done with the configuration.");
        
        cli_print(cli,"\n\tNOTE: If Selection Criteria is modified, then all existing TranslatorRules will be deleted by IWF.\
                \n\t      User needs to configure new rules as per Modified Selection Criteria Manually.");

        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-local");
    }
    else if (!strcmp("local-SCCP",argv[CMD_LINE_ARG_ZERO]) && !strcmp("PC-SSN",argv[CMD_LINE_ARG_TWO]))
    {
        mode = MODE_CONFIG_LOCAL_PCSSN;
        cli_print(cli,"\n\tNOTE: User can configure at max %d SSN's.\
                \n\t      Enter Exit Command once done with the configuration.",MAX_SSN_NUM);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "SCCP-PC_SSN");
        cli_int_local_config(cli, command, argv, argc);
    }
    else if (!strcmp("local-SCCP",argv[CMD_LINE_ARG_ZERO]) && !strcmp("GT",argv[CMD_LINE_ARG_TWO]))
    {
        mode = MODE_CONFIG_LOCAL_GT;
        cli_print(cli,"\n\tNOTE: User has to configure GT configuration mandatorily.\
                \n\t      Enter Exit Command once done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "SCCP-GT");
        cli_int_local_config(cli, command, argv, argc);
    }
    else if (!strcmp("sctp-profile",argv[CMD_LINE_ARG_ZERO]))
    {
        init_sctpprofile_config(cli);
        mode = MODE_CONFIG_SCTP_PROFILE;
        cli_print(cli,"\n\tNOTE: User has to configure required parameters under SCTP Profile Configuration.\
                \n\t      Default Values will be configured for parameters which are not configured.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "sctp-profile-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_sctp_profile_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("sctp-profile",argv[CMD_LINE_ARG_ONE]))
    {
        init_sctpprofile_config(cli);
        mode = MODE_CONFIG_SCTP_PROFILE;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under SCTP Profile Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-sctp-profile-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        strncpy(cli->req.IWFPayload.sctpProfileConfigPayload.sctpProfileConfigKeyInfo.profilename, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" SCTP-Profile = %s",argv[CMD_LINE_ARG_TWO]);
    }
    else if (!strcmp("sctp-end-point",argv[CMD_LINE_ARG_ZERO]))
    {
        init_sctpprofile_config(cli);
        mode = MODE_CONFIG_ADD_SCTP_ENDPOINT;
        cli_print(cli,"\n\tNOTE: User has to configure required parameters under SCTP EndPoint Configuration.\
                \n\t      User can configure upto %d Multi-Homing Ip's at max.\
                \n\t      Type commit after you are done with the configuration.",MAX_LOCALTRANSPORT_ATTRIBUTES);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "sctp-endpoint-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_sctp_endpoint_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("sctp-end-point",argv[CMD_LINE_ARG_ONE]))
    {
        init_sctp_endpoint_config(cli);
        mode = MODE_CONFIG_MODIFY_SCTP_ENDPOINT;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under SCTP EndPoint Configuration.\
                \n\t      User can only add Multi-Homing Ip's under this mode.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-sctp-endpoint-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        strncpy(cli->req.IWFPayload.sctpEndPointConfigPayload.sctpEndPointConfigKeyInfo.endpoint, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" SCTP-Profile = %s",argv[CMD_LINE_ARG_TWO]);
    }
#if 0
    else if (!strcmp("association",argv[CMD_LINE_ARG_ZERO]))
    {
        init_association_config(cli);
        mode = MODE_CONFIG_ADD_ASSOCIATION;
        cli_print(cli,"\n\tNOTE: User has to configure specific SCTP-Profile otherwise default SCTP-Profile will be taken.\
                \n\t      User can configure upto %d Multi-Homing Ip's at max.\
                \n\t      Type commit after you are done with the configuration.",MAX_LOCALTRANSPORT_ATTRIBUTES);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "assoc-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_association_config(cli, command, argv, argc);
    }
#endif
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("association",argv[CMD_LINE_ARG_ONE]))
    {
        init_association_config(cli);
        mode = MODE_CONFIG_MODIFY_ASSOCIATION;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under Association Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-assoc-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        strncpy(cli->req.IWFPayload.associationConfigPayload.associationConfigKeyInfo.associationname, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG(" Association = %s",argv[CMD_LINE_ARG_TWO]);
    }
    else if (!strcmp("assoc-set",argv[CMD_LINE_ARG_ZERO]))
    {
        init_associationset_config(cli);
        mode = MODE_CONFIG_ADD_ASSOCIATION_SET;
        cli_print(cli,"\n\tNOTE: User has to configure all parameters mandatorily under AssociationSet Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "assoc-set-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_associationset_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("assoc-set",argv[CMD_LINE_ARG_ONE]))
    {
        init_associationset_config(cli);
        mode = MODE_CONFIG_MODIFY_ASSOCIATION_SET;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under AssociationSet Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-assoc-set-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG(" Association-Set = %s",argv[CMD_LINE_ARG_TWO]);
        cli->req.cmd_id = C_cli_modify_assocation_set_Id; 
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
        strncpy(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigKeyInfo.assocsetname, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
    }
    else if (!strcmp("destination",argv[CMD_LINE_ARG_ZERO]))
    {
        init_destination_config(cli);
        mode = MODE_CONFIG_DESTINATION;
        cli_print(cli,"\n\tNOTE: User has to configure Routing Indicator and Pointcode related parameters mandatorily under Destination Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "dest-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_destination_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("destination",argv[CMD_LINE_ARG_ONE]))
    {
        init_destination_config(cli);
        mode = MODE_CONFIG_DESTINATION;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under Destination Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-dest-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        strncpy(cli->req.IWFPayload.destinationConfigPayload.destinationConfigKeyInfo.dest_name, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
        CLI_DEBUG_LOG("Destination = %s",argv[CMD_LINE_ARG_TWO]);
    }
    else if (!strcmp("dest-SCCP",argv[CMD_LINE_ARG_ZERO]) && !strcmp("PC-SSN",argv[CMD_LINE_ARG_TWO]))
    {
        mode = MODE_CONFIG_DESTINATION_PCSSN;
        cli_print(cli,"\n\tNOTE: User has to configure SSN mandatorily.\
                \n\t      Enter Exit Command once done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "SCCP-PC_SSN");
        cli_int_destination_config(cli, command, argv, argc);
    }
    else if (!strcmp("dest-SCCP",argv[CMD_LINE_ARG_ZERO]) && !strcmp("GT",argv[CMD_LINE_ARG_TWO]))
    {
        mode = MODE_CONFIG_DESTINATION_GT;
        cli_print(cli,"\n\tNOTE: User has to configure GT configuration mandatorily.\
                \n\t      Enter Exit Command once done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "SCCP-GT");
        cli_int_destination_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("remote-route",argv[CMD_LINE_ARG_ONE]))
    {
        init_remoteroute_config(cli);
        mode = MODE_CONFIG_REMOTEROUTE;
        cli_print(cli,"\n\tNOTE: User has to modify required parameters under Remote-Route Configuration.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-route-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        strncpy(cli->req.IWFPayload.remoteRouteConfigPayload.remoteRouteConfigKeyInfo.route_name, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1); 
        CLI_DEBUG_LOG("RemoteRoute = %s",argv[CMD_LINE_ARG_TWO]);
    }
    else if (!strcmp("trans-rule",argv[CMD_LINE_ARG_ZERO]))
    {
        init_translator_rule_config(cli);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "trans-rule-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);

        if(!strcmp("trans-type",argv[CMD_LINE_ARG_TWO]) && !strcmp("SS7",argv[CMD_LINE_ARG_THREE]))
        {
            mode = MODE_TRANS_RULE_SS7;
            cli_print(cli,"\n\tNOTE: User has to configure required parameters as mandatory under Translator Rule Mode.\
                    \n\t      service-key & service-context-id is applicable only for CAP-Ro or CAP-Ro-TSL Translators.\
                    \n\t      User can add at max %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
        }
        else if(!strcmp("trans-type",argv[CMD_LINE_ARG_TWO]) && !strcmp("DIAMETER",argv[CMD_LINE_ARG_THREE]))
        {
            mode = MODE_TRANS_RULE_DIAMETER;
            cli_print(cli,"\n\tNOTE: User has to configure all parameters as mandatory under Translator Rule Mode.\
                    \n\t      User can add at max %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
        }
        else if(!strcmp("trans-type",argv[CMD_LINE_ARG_TWO]) && !strcmp("HTTP",argv[CMD_LINE_ARG_THREE]))
        {
            mode = MODE_TRANS_RULE_HTTP;
            cli_print(cli,"\n\tNOTE: User has to configure all parameters as mandatory under Translator Rule Mode.\
                    \n\t      User can add at max %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
        }
        cli_int_translator_rule_config(cli, command, argv, argc);
    }
    else if (!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("trans-rule",argv[CMD_LINE_ARG_ONE]))
    {
        init_translator_rule_config(cli);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-trans-rule-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);

        if(!strcmp("trans-type",argv[CMD_LINE_ARG_THREE]) && !strcmp("SS7",argv[CMD_LINE_ARG_FOUR]))
        {
            mode = MODE_TRANS_RULE_SS7;
            cli_print(cli,"\n\tNOTE: User can modify required parameters under modify Translator Rule Mode.\
                    \n\t      User can only add %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
            cli_print(cli,"\n\tNOTE: Restart of IWF is required if Primary-Destination is modified for CAP-Ro translator.");
        }
        else if(!strcmp("trans-type",argv[CMD_LINE_ARG_THREE]) && !strcmp("DIAMETER",argv[CMD_LINE_ARG_FOUR]))
        {
            mode = MODE_TRANS_RULE_DIAMETER;
            cli_print(cli,"\n\tNOTE: User can modify required parameters under modify Translator Rule Mode.\
                    \n\t      User can only add %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
        }
        else if(!strcmp("trans-type",argv[CMD_LINE_ARG_THREE]) && !strcmp("HTTP",argv[CMD_LINE_ARG_FOUR]))
        {
            mode = MODE_TRANS_RULE_HTTP;
            cli_print(cli,"\n\tNOTE: User can modify required parameters under modify Translator Rule Mode.\
                    \n\t      User can only add %d Vplmn-Id's in this mode.\
                    \n\t      Type commit after you are done with the configuration.",MAX_VPLMN_ID_COUNT);
        }
        cli_int_translator_rule_config(cli, command, argv, argc);
    }
    else if(!strcmp("s6a-MAP",argv[CMD_LINE_ARG_ZERO]))
    {
        init_s6a_map_config(cli);
        mode = MODE_CONFIG_ADD_S6A_MAP;
        cli_print(cli,"\n\tNOTE: User has to configure required number of sgsn-address-map params.\
                \n\t      User can configure required number of sgsg-prefix-map params.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "add-s6a-MAP");
        cli_int_s6a_map_config(cli, command, argv, argc);
    }
    else if(!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("s6a-MAP",argv[CMD_LINE_ARG_ONE]))
    {
        init_s6a_map_config(cli);
        mode = MODE_CONFIG_MODIFY_S6A_MAP;
        cli_print(cli,"\n\tNOTE: User can only modify Local-Sgsn-Number and Routing-Prefix.\
                \n\t      User can add multiple sgsn-address-map or sgsg-prefix-map params in this mode.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-s6a-MAP");
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG("Translator = s6a-MAP");
    }
    else if(!strcmp("MAP-s6a",argv[CMD_LINE_ARG_ZERO]))
    {
        init_map_s6a_config(cli);
        mode = MODE_CONFIG_ADD_MAP_S6A;
        cli_print(cli,"\n\tNOTE: User can configure required number of vplmn_id-sgsn_number mapping params.\
                \n\t      Wildcard entry is supported for sgsn-number. ex- 9778*\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "add-MAP-s6a");
        cli_int_map_s6a_config(cli, command, argv, argc);
    }
    else if(!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("MAP-s6a",argv[CMD_LINE_ARG_ONE]))
    {
        init_map_s6a_config(cli);
        mode = MODE_CONFIG_MODIFY_MAP_S6A;
        cli_print(cli,"\n\tNOTE: User can modify required fields and add multiple vplmnid-sgsn-map params in this mode.\
                \n\t      Wildcard entry is supported for sgsn-number. ex- 9778*\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-MAP-s6a");
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG("Translator = MAP-s6a");
        cli_int_map_s6a_config(cli, command, argv, argc);
    }
    else if(!strcmp("CAP-Ro",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_CAP_RO;
        strncpy(component, "CAP-Ro",MAX_PARAM_SIZE - 1);
    }
    else if(!strcmp("idp",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_CAP_RO_IDP;
        init_cap_ro_idp_config(cli);
        cli_print(cli,"\n\tNOTE: User has to configure required parameters under IDP mode.\
                \n\t      User can configure Multiple Ext-Tele-Service-Id-MAP and Ext-Bearer-Service-Id-MAP.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "add-IDP");
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        CLI_DEBUG_LOG("Translator = CAP-Ro");
        cli->req.cmd_id = C_cli_cap_ro_idp_config_Id;
        //Default value for Multiple Service Indicator
        cli->req.IWFPayload.capRoIDPConfigPayload.capRoIDPConfigInfo.multi_service_indicator = 1;
        CLI_DEBUG_LOG("Default Multi-Service-Indicator = 1");
    }
    else if(!strcmp("idp-sms",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_CAP_RO_IDP_SMS;
        init_cap_ro_idp_sms_config(cli);
        cli_print(cli,"\n\tNOTE: User has to configure required parameters under IDP-SMS mode.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "add-IDP-SMS");
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        CLI_DEBUG_LOG("Translator = CAP-Ro");
    }
    else if(!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("idp",argv[CMD_LINE_ARG_ONE]))
    {
        mode = MODE_CONFIG_CAP_RO_IDP;
        init_cap_ro_idp_config(cli);
        cli_print(cli,"\n\tNOTE: User can modify Required parameters under IDP mode.\
                \n\t      User can configure Multiple Ext-Tele-Service-Id-MAP and Ext-Bearer-Service-Id-MAP.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-IDP");
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG("Translator = CAP-Ro");
    }
    else if(!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("idp-sms",argv[CMD_LINE_ARG_ONE]))
    {
        mode = MODE_CONFIG_CAP_RO_IDP_SMS;
        init_cap_ro_idp_sms_config(cli);
        cli_print(cli,"\n\tNOTE: User can modify Required parameters under IDP-SMS mode.\
                \n\t      Type commit after you are done with the configuration.");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "mod-IDP-SMS");
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG("Translator = CAP-Ro");
    }
    else if(!strcmp("CAP-Proto",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_CAP_PROTO;
        strncpy(component, "CAP-Proto",MAX_PARAM_SIZE - 1);
    }
    else if(!strcmp("cap-timers",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_CAP_TIMERS;
        strncpy(component, "Timers",MAX_PARAM_SIZE - 1);
    }
    else if(!strcmp("dcca",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_DCCA;
        strncpy(component, "dcca",MAX_PARAM_SIZE - 1);
    }
    else if(!strcmp("failure-handling",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_FAILURE_HANDLING;
        strncpy(component, "failure-handling",MAX_PARAM_SIZE - 1);
        init_dcca_general_config(cli);
    }
    else if (strcmp("dest-realm",argv[CMD_LINE_ARG_ZERO])==0)
    {
        init_dcca_dest_config(cli);
        mode = MODE_CONFIG_DCCA_DESTINATION;
        cli_print(cli,"\n\tNOTE: At max user can configure %d EndPoints for a Realm.\
                \n\t      User can modify the existing EndPoints priority.\
                \n\t      Type commit after you are done with the configuration.",MAX_DCCA_ENDPOINTS);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "dest-realm-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_staticrouting(cli, command, argv, argc);
        strncpy(cli->req.IWFPayload.iwfDccaDestinationConfigPayload.iwfDccaDestinationConfigKeyInfo.dest_realm, 
                argv[CMD_LINE_ARG_ONE], MAX_FIELD_NAME - 1);
    }
    else if(!strcmp("protocol-action",argv[CMD_LINE_ARG_ZERO]))
    {
        init_protocolactions_config(cli);
        if(!strcmp("RRB",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_CAP_RRB;
            snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "Prot-Act-RRB");
            strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId, argv[CMD_LINE_ARG_ONE], MAX_FIELD_NAME - 1);
            CLI_DEBUG_LOG("Action = %s", argv[CMD_LINE_ARG_ONE]);
        }
    }
    else if(!strcmp("rrb-rule",argv[CMD_LINE_ARG_ZERO]))
    {
        init_protocolactions_config(cli);
        mode = MODE_CONFIG_RRB_CALL_SCENARIO;
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol, "CAP", MAX_FIELD_NAME - 1);
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId, "RRB", MAX_FIELD_NAME - 1);
        cli_print(cli,"\n\tNOTE: At max user can configure %d CallScenarios for a Rule.\
                \n\t      Type commit after you are done with the configuration.",MAX_CALL_SCENARIOS);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "Rule-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name, argv[CMD_LINE_ARG_ONE], MAX_FIELD_NAME - 1);
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        CLI_DEBUG_LOG("RuleName = %s", argv[CMD_LINE_ARG_ONE]);
    }
    else if(!strcmp("modify",argv[CMD_LINE_ARG_ZERO]) && !strcmp("rrb-rule",argv[CMD_LINE_ARG_ONE]))
    {
        init_protocolactions_config(cli);
        mode = MODE_CONFIG_RRB_CALL_SCENARIO;
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.protocol, "CAP", MAX_FIELD_NAME - 1);
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.actionId, "RRB", MAX_FIELD_NAME - 1);
        cli_print(cli,"\n\tNOTE: At max user can configure %d CallScenarios for a Rule.\
                \n\t      Type commit after you are done with the configuration.",MAX_CALL_SCENARIOS);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "Mod-Rule-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_TWO]);
        strncpy(cli->req.IWFPayload.protocolActionConfigPayload.protocolActionConfigKeyInfo.rule_name, argv[CMD_LINE_ARG_TWO], MAX_FIELD_NAME - 1);
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        CLI_DEBUG_LOG("RuleName = %s", argv[CMD_LINE_ARG_TWO]);
    }
    else if(!strcmp("call-scenario",argv[CMD_LINE_ARG_ZERO]))
    {
        if(!strcmp("MO_CAPV1",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_MO_CAP_V1;
        }
        else if(!strcmp("MO_CAPV2",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_MO_CAP_V2;
        }
        else if(!strcmp("MT_CAPV1",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_MT_CAP_V1;
        }
        else if(!strcmp("MT_CAPV2",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_MT_CAP_V2;
        }
        else if(!strcmp("SMS_CAPV3",argv[CMD_LINE_ARG_ONE]))
        {
            mode = MODE_CONFIG_SMS_CAP_V3;
        }
        cli_print(cli,"\n\tNOTE: At max user can configure %d Events for a Rule.\
                \n\t      Type exit after you are done with the configuration.",MAX_EVENT_TYPES);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "scenario-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_protocolactions_config(cli, command, argv, argc);
    }
    else if((cptr = strstr(command, "general-Config")) != NULL)
    {
        strncpy(component, "general-Config",MAX_PARAM_SIZE - 1);
        mode = MODE_IWF_GENERAL_CONFIG;
    }
#if 0
    else if(!strcmp("call-scenario",argv[CMD_LINE_ARG_ZERO]))
    {
        mode = MODE_CONFIG_RRB_EVENTS;
        cli_print(cli,"\n\tNOTE: At max user can configure %d Events for a Rule.\
                \n\t      Type exit after you are done with the configuration.",MAX_EVENT_TYPES);
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", "scenario-");
        snprintf(component + strlen(component) ,MAX_PARAM_SIZE - 1, "%s", argv[CMD_LINE_ARG_ONE]);
        cli_int_protocolactions_config(cli, command, argv, argc);
    }
#endif
    CLI_DEBUG_LOG("cli->mode = %d",mode);
    oldmode = cli_set_configmode(cli, mode, component);
    cli_track_configmode(cli, oldmode, mode, true);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_diameterbasePrompt(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int mode = MODE_CONFIG_DIABASE, oldmode;
    char component[MAX_NAME_LEN] = {0};

    if(strcmp(command, "peer-table") == 0)
    {
        strncpy(component, "peer-table",MAX_NAME_LEN - 1);
        mode = MODE_DIABASE_PTABLE;
    }
    else if(strcmp(command, "realm-table") == 0)
    {
        strncpy(component, "realm-table",MAX_NAME_LEN - 1);
        mode = MODE_DIABASE_REALMTABLE;
    }
    else if(strcmp(command, "localhost-table") == 0)
    {
        strncpy(component, "localhost-table",MAX_NAME_LEN - 1);
        mode = MODE_DIABASE_LOCALHOST;
    }

    CLI_DEBUG_LOG("cli->mode = %d",mode);
    oldmode = cli_set_configmode(cli, mode, component);
    cli_track_configmode(cli, oldmode, mode, true);

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_discoveryInterval(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_discoveryIntl_Id;

    if((argv[CMD_LINE_ARG_ZERO] == NULL) | (argv[CMD_LINE_ARG_ONE] == NULL)){
        return CLI_ERROR;
    }

    req.OP_CODE = ADD;
    CLI_DEBUG_LOG("OP_CODE - ADD");

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"default")){
        req.Payload.dreGlobalConfigPayload.PeerGlobalConfigInfo.DiscoveryInterval = DEFAULT_DISCOVER_INTERVAL;
        CLI_DEBUG_LOG("DiscoveryInterval = %d",DEFAULT_DISCOVER_INTERVAL);
    }else {
        req.Payload.dreGlobalConfigPayload.PeerGlobalConfigInfo.DiscoveryInterval = atol(argv[CMD_LINE_ARG_ONE]);
        CLI_DEBUG_LOG("DiscoveryInterval = %ld",atol(argv[CMD_LINE_ARG_ONE]));
    }
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}


/*********************************************************************************************



 *********************************************************************************************/
int cli_int_discoverPeer(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_discoverPeer_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }else {
        req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }
    while(argv[i]){
        if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.dreDynamicDiscoveryPayload.DynamicDiscoveryKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"host")){
            i++;
            strncpy(req.Payload.dreDynamicDiscoveryPayload.DynamicDiscoveryConfigInfo.peerHostNames,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }
        i++;
    }
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command); 
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
void init_staticrouting(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.Payload.staticRoutingPayload.dest_info.dest_hostname[0] = INVALID_STR;
    cli->req.Payload.staticRoutingPayload.dest_info.dest_realmname[0] = INVALID_STR;
    cli->req.Payload.staticRoutingPayload.peer_info.peername[0] = INVALID_STR;
    cli->req.Payload.staticRoutingPayload.peer_info.realmname[0] = INVALID_STR;
    cli->req.Payload.staticRoutingPayload.peer_info.appId = INVALID_NUM;
    cli->req.Payload.staticRoutingPayload.peer_info.priority = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}
int cli_int_showstaticrouting(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req; 
    memset(&req, 0, sizeof(req));
    int i = 0;
    req.cmd_id = C_cli_showstaticrouting_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"static-routing"))
    {
        if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
        {
            req.Payload.staticRoutingPayload.dest_info.dest_hostname[0] = INVALID_STR;
            req.Payload.staticRoutingPayload.dest_info.dest_realmname[0] = INVALID_STR;
            req.cmd_id = C_cli_showallstaticrouting_Id;
        }
        else if(!strcmp(argv[CMD_LINE_ARG_TWO],"dest-host")){
            i = CMD_LINE_ARG_THREE;
            req.cmd_id = C_cli_showstaticrouting_Id;
            if(argv[i])
            {
                strncpy(req.Payload.staticRoutingPayload.dest_info.dest_hostname, argv[CMD_LINE_ARG_THREE],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("dest host name = %s",argv[i]);
                i = i+2;
                if(argv[i])
                {
                    strncpy(req.Payload.staticRoutingPayload.dest_info.dest_realmname,argv[CMD_LINE_ARG_FIVE],MAX_PARAM_SIZE - 1);
                    CLI_DEBUG_LOG("dest host name = %s",argv[CMD_LINE_ARG_FIVE]);
                }
            }
        }
        else 
            return CLI_ERROR;
    }
    else
        return CLI_ERROR;

    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
int cli_int_staticrouting(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        init_staticrouting(cli);
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")) {
        i = CMD_LINE_ARG_ONE;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        cli->req.OP_CODE = MODIFY;
	init_staticrouting(cli);
    }
    else
    {
        CLI_DEBUG_LOG("OP_CODE - ADD");
        cli->req.OP_CODE = ADD;
        //initializing the values with invalid num or string
        cli->req.Payload.staticRoutingPayload.peer_info.peername[0] = INVALID_STR;
        cli->req.Payload.staticRoutingPayload.peer_info.realmname[0] = INVALID_STR;
        cli->req.Payload.staticRoutingPayload.peer_info.appId = INVALID_NUM;
        cli->req.Payload.staticRoutingPayload.peer_info.priority = INVALID_NUM;
    }

    cli->req.cmd_id = C_cli_staticrouting_Id;  

    while(argv[i]){
        if(!strcmp(argv[i],"dest-host")){
            i++;
            if(argv[i])
            {
                strncpy(cli->req.Payload.staticRoutingPayload.dest_info.dest_hostname,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("DestHostName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"dest-realm")){
            i++;
            if(argv[i])
            {
                strncpy(cli->req.Payload.staticRoutingPayload.dest_info.dest_realmname,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("DestRealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"static-peer") || !strcmp(argv[i],"peer")){
            i++;
            if(argv[i])
            {
                strncpy(cli->req.Payload.staticRoutingPayload.peer_info.peername,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("PeerHostName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                strncpy(cli->req.Payload.staticRoutingPayload.peer_info.realmname,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"app-id")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.staticRoutingPayload.peer_info.appId = atol(argv[i]);
                CLI_DEBUG_LOG("AppId = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"priority")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.staticRoutingPayload.peer_info.priority = atoi(argv[i]);
                CLI_DEBUG_LOG("Priority = %d",atoi(argv[i]));
            }
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdId = %d",cli->req.cmd_id);
    
    if(cli->req.OP_CODE == ADD)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
    
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/

void init_realm(struct cli_def *cli) 
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.Payload.dreRealmPayload.realmKeyInfo.RealmName[0]= INVALID_STR;
    cli->req.Payload.dreRealmPayload.realmKeyInfo.AppId = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmKeyInfo.PeerHostId[0] = INVALID_STR;
    cli->req.Payload.dreRealmPayload.realmInfo.AltRealmName[0] = INVALID_STR;
    cli->req.Payload.dreRealmPayload.realmInfo.LocalAction = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmInfo.VendorID = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmInfo.Priority = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmInfo.RedirectHostUsage = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmInfo.RedirectMaxCacheTime = INVALID_NUM;
    cli->req.Payload.dreRealmPayload.realmInfo.EnableProxyInfo = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}


int cli_int_configRealm(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        // to delete realm
        cli->req.cmd_id  = C_cli_configRealm_Id;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")) {
        i = CMD_LINE_ARG_ONE;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        cli->req.OP_CODE = MODIFY;
    }
    else
    {
        CLI_DEBUG_LOG("OP_CODE - ADD");
        cli->req.OP_CODE = ADD;
    }

    while(argv[i]){
        if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                strncpy(cli->req.Payload.dreRealmPayload.realmKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"app-id")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreRealmPayload.realmKeyInfo.AppId = atol(argv[i]);
                CLI_DEBUG_LOG("AppId = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"to-peer")){
            i++;
            // command-id for destination related operations
            cli->req.cmd_id  = C_cli_RealmDestination_Id;
            CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
            if(argv[i])
            {
                strncpy(cli->req.Payload.dreRealmPayload.realmKeyInfo.PeerHostId,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("to-peer = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"to-realm")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("to-realm = %s",argv[i]);
                strncpy(cli->req.Payload.dreRealmPayload.realmInfo.AltRealmName,argv[i],MAX_PARAM_SIZE - 1);
            }
        }else if(!strcmp(argv[i],"local-action")){
            i++;
            cli->req.cmd_id  = C_cli_configRealm_Id;
            CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
            if(argv[i]){
                CLI_DEBUG_LOG("local-action = %s",argv[i]);
                if(!strcmp(argv[i],"Local")){
                    cli->req.Payload.dreRealmPayload.realmInfo.LocalAction = LOCAL_ACTION_LOCAL;
                }else if(!strcmp(argv[i],"Relay")){
                    cli->req.Payload.dreRealmPayload.realmInfo.LocalAction = LOCAL_ACTION_RELAY;
                }else if(!strcmp(argv[i],"Proxy")){
                    cli->req.Payload.dreRealmPayload.realmInfo.LocalAction = LOCAL_ACTION_PROXY;
                }else if(!strcmp(argv[i],"Redirect")){
                    cli->req.Payload.dreRealmPayload.realmInfo.LocalAction = LOCAL_ACTION_REDIRECT;
                }
                // for modify realm 
                cli->req.Payload.dreRealmPayload.realmInfo.RedirectHostUsage = INVALID_NUM;
                cli->req.Payload.dreRealmPayload.realmInfo.RedirectMaxCacheTime = INVALID_NUM;
            }
        }else if(!strcmp(argv[i],"vendor-id")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("vendor-id = %ld",atol(argv[i]));
                cli->req.Payload.dreRealmPayload.realmInfo.VendorID = atol(argv[i]);
            }
        }else if(!strcmp(argv[i],"priority")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("priority = %d",atoi(argv[i]));
                cli->req.Payload.dreRealmPayload.realmInfo.Priority = atoi(argv[i]);
            }
        }else if(!strcmp(argv[i],"redirect-host-usage")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("RedirectHostUsage = %d",atoi(argv[i]));
                cli->req.Payload.dreRealmPayload.realmInfo.RedirectHostUsage = atoi(argv[i]);
            }
        }else if(!strcmp(argv[i],"redirect-max-cache-time")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("RedirectMaxCacheTime = %d",atoi(argv[i]));
                cli->req.Payload.dreRealmPayload.realmInfo.RedirectMaxCacheTime = atoi(argv[i]);
            }
        }
        i++;

    }
    if(cli->req.OP_CODE == ADD)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req,sizeof(cli->req),cli->req.cmd_id,0);
#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command); 
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_defaultRoute(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_defaultRoute_Id;

    if(!strcmp("no",argv[CMD_LINE_ARG_ZERO])){
        i = CMD_LINE_ARG_ONE;   
        req.cmd_id = C_cli_nodefaultRoute_Id;
        req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }else{
        req.OP_CODE = ADD;
        req.cmd_id = C_cli_defaultRoute_Id;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while(argv[i]){
        if(!strcmp(argv[i],"peer")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.dreDefaultRoutePayload.defaultRouteInfo.PeerHostIds,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("PeerHostId = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
                strncpy(req.Payload.dreDefaultRoutePayload.defaultRouteKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            }
        }
        i++;

    }

    CLI_DEBUG_LOG("CmdId = %d",req.cmd_id);
#ifdef SEND_ALL_REQ
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#endif

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_showdefaultRoute(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req; 
    memset(&req, 0, sizeof(req));

    req.cmd_id = C_cli_showdefaultRoute_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_modifylocalhost(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")) {
        i = CMD_LINE_ARG_TWO;
        cli->local_transport_count = 0;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }   

    cli->req.OP_CODE = MODIFY;
    cli->req.cmd_id = C_cli_modifylocalhost_Id; 
    while(argv[i]){
        if(!strcmp(argv[i],"host")){
            i++;
            if(argv[i]){
                CLI_DEBUG_LOG("HostName = %s",argv[i]);
                strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i]){
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
                strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            }
        }else if(!strcmp(argv[i],"local-transport-id")){
            int transport_Id = 0;
            bool publicIpSet = false;
            int trans_type = INVALID_NUM;
            i++;
            transport_Id = atoi(argv[i]);
            CLI_DEBUG_LOG("transport_Id = %d",atoi(argv[i]));
            i++;
            if((argv[i+CMD_LINE_ARG_FIVE]) && 
                    !(strcmp(argv[i+CMD_LINE_ARG_FIVE],"public-ip")))
            {
                strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[transport_Id-1],argv[i+CMD_LINE_ARG_SIX],MAX_IP_LEN - 1);
                CLI_DEBUG_LOG("PublicIp = %s",argv[i+CMD_LINE_ARG_SIX]);
                publicIpSet = true;
            }
            if(!strcmp(argv[i],"TCP"))
            {
                CLI_DEBUG_LOG("trans_type - TCP");
                trans_type = TRANSTYPE_TCP;
            }
            else
            {
                trans_type = TRANSTYPE_SCTP;
                CLI_DEBUG_LOG("trans_type - SCTP");
                int j = i+CMD_LINE_ARG_FIVE , k = 0;
                if(publicIpSet)
                    j = i+CMD_LINE_ARG_SEVEN;
                while(argv[j])
                {
                    j++;
                    CLI_DEBUG_LOG("secondaryIp = %s",argv[j]);
                    strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[transport_Id-1][k], argv[j],MAX_IP_LEN - 1);
                    j++; k++;
                }

            }
            cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[transport_Id-1] = trans_type;
            strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[transport_Id-1],argv[i+CMD_LINE_ARG_TWO],MAX_IP_LEN - 1);
            
            if(!strcmp(argv[i + CMD_LINE_ARG_THREE],"port"))
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[transport_Id-1] = atoi(argv[i+CMD_LINE_ARG_FOUR]);
                CLI_DEBUG_LOG("Port = %d",atoi(argv[i+CMD_LINE_ARG_FOUR]));
            }
            else
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[transport_Id-1] = atoi(argv[i+CMD_LINE_ARG_FOUR]);
                CLI_DEBUG_LOG("SecurePort = %d",atoi(argv[i+CMD_LINE_ARG_FOUR]));
            }
            CLI_DEBUG_LOG("PrimaryIp = %s",argv[i+CMD_LINE_ARG_TWO]);
            cli->local_transport_count++;
        }else if(!strcmp(argv[i],"life-time")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.LifeTime = atol(argv[i]);
                CLI_DEBUG_LOG("life-time = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"grace-time")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("grace-time = %ld",atol(argv[i]));
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.GraceTime = atol(argv[i]);
            }
        }else if(!strcmp(argv[i],"auth-time-out")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.TimeOut =  atol(argv[i]);
                CLI_DEBUG_LOG("auth-time-out = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"interim")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.Interim = atol(argv[i]);
                CLI_DEBUG_LOG("interim = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"acc-time-out")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.TimeOut = atol(argv[i]);
                CLI_DEBUG_LOG("acc-time-out = %ld",atol(argv[i]));
            }
        }
        i++;

    }
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_count = cli->local_transport_count; 
    cli->allow_exit=0;

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_localhost(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = DELETE;
        cli->req.cmd_id = C_cli_localhost_Id;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "local-host")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        cli->req.cmd_id = C_cli_localhost_Id; 
        cli->local_transport_count = 0;
        CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }
    else {
        i =0;
    }


    while(argv[i]){
        if(!strcmp(argv[i],"host")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("HostName = %s",argv[i]);
                strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
                strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            }    
        }else if(!strcmp(argv[i],"local-transport")){
            i++;
            int j = 0;
            bool found = false;
            if(cli->local_transport_count != MAX_LOCALTRANSPORT_ATTRIBUTES)
            {
                for(j=0;j<cli->local_transport_count;j++)
                {
                    int trans_type = INVALID_NUM;
                    if(!strcmp(argv[i],"TCP"))
                    {
                        CLI_DEBUG_LOG("trans_type - TCP");
                        trans_type = TRANSTYPE_TCP;
                    }
                    else
                    {
                        CLI_DEBUG_LOG("trans_type - SCTP");
                        trans_type = TRANSTYPE_SCTP;
                    }
                    if(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[j] == trans_type)
                    {
                        if(!(strcmp(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[j],argv[i+CMD_LINE_ARG_TWO])))
                        {
                            if(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[j] == atoi(argv[i+CMD_LINE_ARG_FOUR]) ||
                               cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[j] == atoi(argv[i+CMD_LINE_ARG_FOUR]))
                            {
                                found = true;
                                cli_print(cli,"\n\tERROR!! Local-Transport with values transport-type = %s ,Ip = %s, port/secureport = %d is already entered.",argv[i],argv[i+CMD_LINE_ARG_TWO],atoi(argv[i+CMD_LINE_ARG_FOUR]));
                                CLI_ERROR_LOG("ERROR!! Local-Transport with values transport-type = %s ,Ip = %s, port/secureport = %d is already entered.",argv[i],argv[i+CMD_LINE_ARG_TWO],atoi(argv[i+CMD_LINE_ARG_FOUR]));
                                break;
                            }
                        }
                    }
                }
                if(!found)
                {
                    bool publicIpSet = false;
                    if((argv[i+CMD_LINE_ARG_FIVE]) && 
                            !(strcmp(argv[i+CMD_LINE_ARG_FIVE],"public-ip")))
                    {
                        strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[cli->local_transport_count],argv[i+CMD_LINE_ARG_SIX],MAX_IP_LEN - 1);
                        CLI_DEBUG_LOG("PublicIpAddr = %s",argv[i+CMD_LINE_ARG_SIX]);
                        publicIpSet = true;
                    }
                    if(!strcmp(argv[i],"TCP"))
                        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[cli->local_transport_count] = TRANSTYPE_TCP;
                    else
                    {
                        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[cli->local_transport_count]  = TRANSTYPE_SCTP;
                        int j = i+CMD_LINE_ARG_FIVE,k=0;
                        if(publicIpSet)
                            j = i+CMD_LINE_ARG_SEVEN;
                        while(argv[j])
                        {
                            j++;
                            strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[cli->local_transport_count][k], argv[j],MAX_IP_LEN - 1);
                            CLI_DEBUG_LOG("secondaryIp = %s",argv[j]);
                            j++; k++;
                        }
                    }
                    if(!strcmp(argv[i+CMD_LINE_ARG_ONE],"ip"))
                    {
                        strncpy(cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[cli->local_transport_count],argv[i+CMD_LINE_ARG_TWO],MAX_IP_LEN - 1);
                        CLI_DEBUG_LOG("PrimaryIpAddr = %s",argv[i+CMD_LINE_ARG_TWO]);
                    }
                    if(!strcmp(argv[i+CMD_LINE_ARG_THREE],"port"))
                    {
                        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[cli->local_transport_count] = atoi(argv[i+CMD_LINE_ARG_FOUR]);
                        CLI_DEBUG_LOG("port = %d",atoi(argv[i+CMD_LINE_ARG_FOUR]));
                    }
                    if(!strcmp(argv[i+CMD_LINE_ARG_THREE],"secureport"))
                    {
                        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[cli->local_transport_count] = atoi(argv[i+CMD_LINE_ARG_FOUR]);
                        CLI_DEBUG_LOG("secureport = %d",atoi(argv[i+CMD_LINE_ARG_FOUR]));
                    }

                    cli->local_transport_count++;

                    if(cli->local_transport_count == MAX_LOCALTRANSPORT_ATTRIBUTES)
                    {
                        cli_print(cli,"\n\tNOTE: Maximum Local-Transports %d Reached.",MAX_LOCALTRANSPORT_ATTRIBUTES);
                        CLI_WARNING_LOG("NOTE: Maximum Local-Transports %d Reached.",MAX_LOCALTRANSPORT_ATTRIBUTES);
                    }
                }
            }
            else {
                cli_print(cli,"\n\tERROR!! Maximum Local-Transports already entered. First %d are considered for the configuration.",MAX_LOCALTRANSPORT_ATTRIBUTES);
                CLI_ERROR_LOG("ERROR!! Maximum Local-Transports already entered. First %d are considered for the configuration.",MAX_LOCALTRANSPORT_ATTRIBUTES);
            }
        }else if(!strcmp(argv[i],"life-time")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("life-time = %ld",atol(argv[i]));
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.LifeTime = atol(argv[i]);
            }
        }else if(!strcmp(argv[i],"grace-time")){
            i++;
            if(argv[i])
            {
                CLI_DEBUG_LOG("life-time = %ld",atol(argv[i]));
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.GraceTime = atol(argv[i]);
            }
        }else if(!strcmp(argv[i],"auth-time-out")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.TimeOut =  atol(argv[i]);
                CLI_DEBUG_LOG("auth-time-out = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"interim")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.Interim = atol(argv[i]);
                CLI_DEBUG_LOG("interim = %ld",atol(argv[i]));
            }
        }else if(!strcmp(argv[i],"acc-time-out")){
            i++;
            if(argv[i])
            {
                cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.TimeOut = atol(argv[i]);
                CLI_DEBUG_LOG("acc-time-out = %ld",atol(argv[i]));
            }
        }
        i++;

    }
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_count = cli->local_transport_count;
    cli->allow_exit=0;

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_no_localhost(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    CLI_DEBUG_LOG("OP_CODE - DELETE");
    req.OP_CODE = DELETE;
    req.cmd_id = C_cli_no_localhost_Id;

    while(argv[i])
    {
        if(!strcmp(argv[i],"host")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.dreLocalHostPayload.LocalHostKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
                CLI_DEBUG_LOG("HostName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"realm")){
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.dreLocalHostPayload.LocalHostKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
                CLI_DEBUG_LOG("RealmName = %s",argv[i]);
            }
        }else if(!strcmp(argv[i],"local-transport-id"))
        {
            req.cmd_id = C_cli_deletetransport_Id;
            i++;
            if(argv[i])
            {
                req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_id[0] = atoi(argv[i]);
                CLI_DEBUG_LOG("transport_id = %d",atoi(argv[i]));
            }
        }
        else if(!strcmp(argv[i],"ip"))
        {
            req.cmd_id = C_cli_deletesecondaryip_Id;
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[0][0],argv[i],MAX_IP_LEN - 1);
                CLI_DEBUG_LOG("secondaryIp = %s",argv[i]);
            }
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}   

void init_localhost(struct cli_def *cli) 
{
    CLI_DEBUG_LOG(" Entered ");
    int i=0;
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[0][0]= INVALID_STR;
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[0][0]= INVALID_STR;
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[0] = INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secureportno[0] = INVALID_NUM;
    for(i = 0; i<MAX_LOCALTRANSPORT_ATTRIBUTES ; i++)
    {
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transportType[i] = INVALID_NUM;
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.PublicIpAddr[i][0]= INVALID_STR;
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][0][0] = INVALID_STR;
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][1][0] = INVALID_STR;
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][2][0] = INVALID_STR;
        cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.secondaryIp[i][3][0] = INVALID_STR;
    }
    cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.transport_count = INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.LifeTime = INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.GraceTime= INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostAuthInfo.TimeOut = INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.Interim = INVALID_NUM;
    cli->req.Payload.dreLocalHostPayload.LocalHostAcctInfo.TimeOut = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_modifydefaultRoute(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_modifydefaultRoute_Id;

    if(!strcmp("no",argv[CMD_LINE_ARG_ZERO]))
    {
        req.OP_CODE = DELETE;
        return CLI_ERROR;
    }
    else
    {
        req.OP_CODE = MODIFY;

    }

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"peer"))
        {
            i++;
            strncpy(req.Payload.dreDefaultRoutePayload.defaultRouteInfo.PeerHostIds,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(req.Payload.dreDefaultRoutePayload.defaultRouteKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        i++;
    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#endif

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_resetdefault(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    char *fileString = NULL;
    FILE *fh;

    if(!argv[CMD_LINE_ARG_TWO]){
    }
    else{

        if(strcmp(argv[CMD_LINE_ARG_TWO], "default") == 0)
            fileString = CLI_STRING_DFLTFILE;
        else
            fileString = argv[CMD_LINE_ARG_TWO];
    }

    if ((fh = fopen(fileString, "r")))
    {
        // This sets a callback which just displays the cli_print() text to stdout
        // cli_print_callback(cli, pc);
        cli_file(cli, fh, PRIVILEGE_ADMIN, MODE_EXEC);
        cli_print_callback(cli, NULL);
        fclose(fh);
    }

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}


/*********************************************************************************************



 *********************************************************************************************/
int dre_addPeer(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0,j = 0,found = 0;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO], "modify")) {
        i = CMD_LINE_ARG_TWO;
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
        cli->req.cmd_id = C_cli_modifypeer_Id; 
    }   
    else if(!strcmp(argv[CMD_LINE_ARG_ZERO], "peer")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
        cli->req.cmd_id = C_cli_peer_Id; 
    }
    else {
        i=0;
    }
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    while((argv[i]))
    {

        if(!strcmp(argv[i],"host"))
        {
            i++;
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersKeyInfo.peerHostNames,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
            cli->dict_count = 0;
        }
        else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersKeyInfo.realmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"fqdn")){
            i++;
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr, argv[i],MAX_IP_LEN - 1);
            CLI_DEBUG_LOG("fqdn-name = %s",argv[i]);
        }
        else if(!strcasecmp(argv[i],"ip")){
            i++;
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr, argv[i],MAX_IP_LEN - 1);
            CLI_DEBUG_LOG("IpAddr = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"port")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber = atoi(argv[i]);
            CLI_DEBUG_LOG("PortNumber = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"secureport")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.SecurePortNumber = atoi(argv[i]);
            CLI_DEBUG_LOG("SecurePortNumber = %d",atoi(argv[i]));
        }
        else if(!strcasecmp(argv[i],"Transport")){

            i++;
            if(!strcmp(argv[i],"TCP")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType = TRANSTYPE_TCP;
                CLI_DEBUG_LOG("TransportType = %s",argv[i]);
            }else if(!strcmp(argv[i],"SCTP")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType = TRANSTYPE_SCTP;
                CLI_DEBUG_LOG("TransportType = %s",argv[i]);
                i++;
                int k = 0;
                while(argv[i])
                {
                    i++;
                    strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[k],argv[i],MAX_IP_LEN - 1);
                    CLI_DEBUG_LOG("secondaryIpAddr = %s",argv[i]);
                    i++; k++;
                }
            }
        }else if(!strcmp(argv[i],"TLS")){

            i++;
            if(!strcmp(argv[i],"enable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TLS = ENABLE;
            }else if(!strcmp(argv[i],"disable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TLS = DISABLE;
            } 
            CLI_DEBUG_LOG("TLS = %s",argv[i]);
        }else if(!strcmp(argv[i],"IsDPRDisconnectCauseSupported")){

            i++;
            if(!strcmp(argv[i],"enable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsDisconnectCauseSupported = ENABLE;
            }else if(!strcmp(argv[i],"disable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsDisconnectCauseSupported = DISABLE;
            } 
            CLI_DEBUG_LOG("IsDisconnectCauseSupported = %s",argv[i]);
        }else if(!strcmp(argv[i],"alt-peer")){
            i++;
            strncpy(cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.AltHostName,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("alt-peer = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"mate")){

            i++;
            if(!strcmp(argv[i],"enable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate = ENABLE;
            }else{
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate = DISABLE;
            }
            CLI_DEBUG_LOG("mate = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"failover")){

            i++;
            if(!strcmp(argv[i],"enable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover = ENABLE;

            }else{
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover = DISABLE;
            }
            CLI_DEBUG_LOG("failover = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"failback")){

            i++;
            if(!strcmp(argv[i],"enable")){
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failback = ENABLE;

            }else{
                cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failback = DISABLE;
            }
            CLI_DEBUG_LOG("failback = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"timers"));
        else if(!strcmp(argv[i],"watchdog")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue= atoi(argv[i]);
            CLI_DEBUG_LOG("watchdog = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"tc")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue = atoi(argv[i]);
            CLI_DEBUG_LOG("tc = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"expiry")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue = atoi(argv[i]);
            CLI_DEBUG_LOG("expiry = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"busyreconnecttimer")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.busyReconnectTimerVal = atoi(argv[i]);
            CLI_DEBUG_LOG("busyReconnectTimerVal = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"dontwanttalktimer")){
            i++;
            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.doNotWantToTalkToYouReconnectTimer = atoi(argv[i]);
            CLI_DEBUG_LOG("dontwanttalktimer = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"dictionary-name")){
            i++;
            if(cli->dict_count < MAX_DICTIONARY_NUM)
            {
                if(cli->dict_count !=0)
                    for(j=0;j<=cli->dict_count;j++)
                    {
                        // to check whether user entered same dictionary name again 
                        if(!strcmp(cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[j],argv[i]))
                            found = 1;
                    }
                if(found == 0)
                {
                    strncpy(cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[cli->dict_count],argv[i],MAX_NAME_LEN - 1);
                    CLI_DEBUG_LOG("dictionary-name = %s",argv[i]);
                    cli->dict_count++;  
                }
                else
                {
                    CLI_ERROR_LOG("ERROR!! Dictionary name %s already entered",argv[i]);
                    cli_print(cli,"\n\tERROR!! Dictionary name %s already entered.",argv[i]);
                }
                if(cli->dict_count == MAX_DICTIONARY_NUM)
                {
                    cli_print(cli,"\n\tNOTE: Max dictionary count %d reached.",MAX_DICTIONARY_NUM);
                    CLI_WARNING_LOG("NOTE: Max dictionary count %d reached",MAX_DICTIONARY_NUM);
                }
            }
            else {
                cli_print(cli,"\n\tERROR!! Max %d dictionaries are allowed to be configured. First %d dictionaries are considered for the configuration.",MAX_DICTIONARY_NUM,MAX_DICTIONARY_NUM);
                CLI_ERROR_LOG("ERROR!! Max %d dictionaries are allowed to be configured. First %d dictionaries are considered for the configuration.",MAX_DICTIONARY_NUM,MAX_DICTIONARY_NUM);
            }
            cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict = cli->dict_count;
        }
        i++;
    }
    cli->allow_exit=0;

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    cli_print(cli, "%d arguments:", argc);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
void init_peer(struct cli_def *cli) {
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.SecurePortNumber = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TLS = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failback = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue= INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.busyReconnectTimerVal = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.doNotWantToTalkToYouReconnectTimer = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsDisconnectCauseSupported = INVALID_NUM;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr[0]= INVALID_STR;
    cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.AltHostName[0]=INVALID_STR;
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[0][0] = INVALID_STR;
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict = INVALID_NUM;
    for(i = 0 ;i < MAX_LOCALTRANSPORT_ATTRIBUTES; i++)
        cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[i][0] = INVALID_STR;
    CLI_DEBUG_LOG(" Exited ");
}

int endConfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i=0;
    int cmdID=cli->req.cmd_id;
    CLI_DEBUG_LOG("cmdId = %d",cmdID);
    CLI_DEBUG_LOG("cli->allow_exit = %d",cli->allow_exit);
    CLI_DEBUG_LOG("cli->mode = %d",cli->mode);
    if(!strcmp(argv[i],"commit"))
    {
        CLI_DEBUG_LOG("cli->mode",cli->mode);  
        if(cli->mode == MODE_CONFIG_ADD_ERLBF_PEER || 
                cli->mode == MODE_PEER_DICTIONARY ||
                cli->mode == MODE_MODIFY_LOCALHOST ||
                cli->mode == MODE_STATIC_PEER_CONFIG ||
                cli->mode == MODE_CONFIG_ADD_S6A_MAP ||
                cli->mode == MODE_CONFIG_ADD_MAP_S6A ||
                (cli->mode == MODE_CONFIG_FAILURE_HANDLING && cli->req.cmd_id == C_cli_dcca_failure_handling_Id) ||
                //check if nothing is set for modifying in Sigtran Local submode if commit is given
                (cli->mode == MODE_CONFIG_LOCAL && cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_localconfig_Id)||
                //check if nothing is set for modifying in Destination submode if commit is given
                (cli->mode == MODE_CONFIG_DESTINATION && cli->req.OP_CODE == MODIFY && cli->req.cmd_id == C_cli_destination_config_Id)||
                //check if nothing is set for modifying in s6a-MAP submode if commit is given
                (cli->mode == MODE_CONFIG_MODIFY_S6A_MAP && cmdID == C_cli_s6a_map_config_Id) ||
                //check if nothing is set for modifying in MAP-s6a submode if commit is given
                (cli->mode == MODE_CONFIG_MODIFY_MAP_S6A && cmdID == C_cli_map_s6a_config_Id) ||
                //check if nothing is set for adding in realm configuration mode if commit is given
                ((cli->mode  ==  MODE_CONFIG_REALM) && 
                 ((cmdID == C_cli_RealmDestination_Id) || (cmdID == C_cli_configRealm_Id)))) {
            if(cli->allow_exit==0)
            {
                send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                // making dictionary count to zero to re-use the dictionary name structure
                if(cli->mode == MODE_PEER_DICTIONARY)
                    cli->dict_count = 0;
                // making all fileds INVALID_NUM and INVALID_STR otherthan primarykeys once modify request is sent.
                else if(cli->mode == MODE_MODIFY_LOCALHOST)
                    init_localhost(cli);                     
                else if(cli->mode == MODE_CONFIG_MODIFY_S6A_MAP)
                    init_s6a_map_config(cli);
		else if(cli->mode == MODE_CONFIG_MODIFY_MAP_S6A)
                    init_map_s6a_config(cli);
                else if(cli->mode == MODE_CONFIG_CAP_RO_IDP_SMS)
                    init_cap_ro_idp_sms_config(cli);
                else if(cli->mode == MODE_CONFIG_CAP_RO_IDP)
                    init_cap_ro_idp_config(cli);
                else if(cli->mode == MODE_CONFIG_LOCAL)
                    init_localconfig(cli);
                else if(cli->mode == MODE_CONFIG_REMOTEROUTE)
                    init_remoteroute_config(cli);
                else if(cli->mode == MODE_CONFIG_FAILURE_HANDLING)
                    init_dcca_general_config(cli);
            }
            else
            {
                cli_print(cli, "\n\tNothing to commit.");
                CLI_DEBUG_LOG("Nothing to commit.");
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
        }
        else if(cli->mode == MODE_CONFIG_LOCALHOST ||
                cli->mode == MODE_CONFIG_PEER ||
                cli->mode == MODE_CONFIG_LOCAL ||
                cli->mode == MODE_CONFIG_ADD_ASSOCIATION_SET ||
                cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET ||
                cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION ||
                cli->mode == MODE_CONFIG_DESTINATION ||
                cli->mode == MODE_CONFIG_REMOTEROUTE ||
                cli->mode == MODE_CONFIG_SCTP_PROFILE ||
                cli->mode == MODE_CONFIG_ADD_SCTP_ENDPOINT ||
                cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT ||
                cli->mode == MODE_TRANS_RULE_SS7 ||
                cli->mode == MODE_CONFIG_DCCA_DESTINATION ||
                //check if nothing is set for adding or modifying in IDP_SMS submode if commit is given
                (cli->mode == MODE_CONFIG_CAP_RO_IDP_SMS && cmdID == C_cli_cap_ro_idp_sms_config_Id) ||
                cli->mode == MODE_CONFIG_CAP_RO_IDP ||
                cli->mode == MODE_TRANS_RULE_DIAMETER ||
                cli->mode == MODE_TRANS_RULE_HTTP ||
                cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO)
        {
            if(cli->allow_exit==0) 
            {
                if(cli->req.OP_CODE == ADD)
                {
                    CLI_DEBUG_LOG("OP_CODE - ADD");   
                    //check for mandatory fields for adding peer and localhost
                    if((cli->mode == MODE_CONFIG_LOCALHOST) && (cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.IpAddr[0] ==  INVALID_STR) &&
                            (cli->req.Payload.dreLocalHostPayload.LocalHostTransportInfo.portno[0] == INVALID_NUM))
                    {               
                        cli_print(cli,"\n\tERROR: Please provide ip and port values before doing commit.");
                        CLI_ERROR_LOG("ERROR: Please provide ip and port values before doing commit.");
                        CLI_DEBUG_LOG(" Exited ");
                        return CLI_OK;
                    }
                    else if((cli->mode == MODE_CONFIG_PEER))
                    {
                        if((cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber == INVALID_NUM ||
                            cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.SecurePortNumber == INVALID_NUM) && 
                            (cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr[0]== INVALID_STR))
                        {
                            if(cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict == INVALID_NUM)
                            {
                                cli_print(cli,"\n\tERROR: Please provide ip (or) fqdn, port (or) secureport and atleast one Dictionary value before doing commit.");
                                CLI_ERROR_LOG("ERROR: Please provide ip (or) fqdn, port (or) secureport and atleast one Dictionary value before doing commit.");
                            }
                            else
                            {
                                cli_print(cli,"\n\tERROR: Please provide ip (or) fqdn, port (or) secureport values before doing commit.");
                                CLI_ERROR_LOG("ERROR: Please provide ip (or) fqdn, port (or) secureport values before doing commit.");
                            }
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else if((cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict == INVALID_NUM))
                        {
                            cli_print(cli,"\n\tERROR: Please provide atleast one Dictionary value before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide atleast one Dictionary value before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else
                        {
                            cli->dict_count = 0;
                            send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                        }

                    }
                    else if((cli->mode == MODE_CONFIG_ADD_ASSOCIATION_SET))
                    {
                        if(cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.pointcode == INVALID_NUM ||
                                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.routing_key == INVALID_NUM ||
                                cli->req.IWFPayload.associationSetConfigPayload.associationSetConfigInfo.traffic_mode[0] == INVALID_STR)
                        {
                            cli_print(cli,"\n\tERROR: Please provide all the parameters values before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide all the parameters values before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else
                        {
                            send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                        }
                    }
                    else if((cli->mode == MODE_CONFIG_DESTINATION))
                    {
                        if(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator[0] == INVALID_STR &&
                                cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode == INVALID_NUM)
                        {
                            cli_print(cli,"\n\tERROR: Please provide SCCP and PointCode Related configuration before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide SCCP and Pointcode Related configuration before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else if(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator[0] == INVALID_STR)
                        {
                            cli_print(cli,"\n\tERROR: Please provide SCCP Related configuration before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide SCCP Related configuration before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else if(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.pointcode == INVALID_NUM)
                        {
                            cli_print(cli,"\n\tERROR: Please provide PointCode Related configuration before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide Pointcode Related configuration before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }

                        if(!strcmp(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator,"PC-SSN") &&
                                cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.ssn[0] == INVALID_STR)
                        {
                            cli_print(cli,"\n\tERROR: Please provide SSN before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide SSN before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else if(!strcmp(cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.routing_indicator,"GT") &&
                                cli->req.IWFPayload.destinationConfigPayload.destinationConfigInfo.gti == INVALID_NUM)
                        {
                            cli_print(cli,"\n\tERROR: Please provide GT Configuration before doing commit.");
                            CLI_ERROR_LOG("ERROR: Please provide GT Configuration before doing commit.");
                            CLI_DEBUG_LOG(" Exited ");
                            return CLI_OK;
                        }
                        else
                        {
                            send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                        }
                    }
                    else if(((cli->mode == MODE_TRANS_RULE_SS7 &&
                                    (cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination[0] == INVALID_STR ||
                                    ((cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceContextId[0] == INVALID_STR) 
                                     && (!strcmp(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator,"CAP-Ro") || 
                                         !strcmp(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.translator,"CAP-Ro-TSL"))) ||
                                     cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn[0] == INVALID_STR)) ||
                                (cli->mode == MODE_TRANS_RULE_DIAMETER &&
                                 (cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.destination[0] == INVALID_STR ||
                                     cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.ossn[0] == INVALID_STR)) ||
                                (cli->mode == MODE_TRANS_RULE_HTTP &&
                                 (cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.http_url[0] == INVALID_STR ||
                                  cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.web_service[0] == INVALID_STR))))
                    {
                        cli_print(cli,"\n\tERROR: Please provide all the parameters under this mode before doing commit.");
                        CLI_ERROR_LOG("ERROR: Please provide all the parameters under this mode before doing commit.");
                        return CLI_OK;
                    }
                    else if(cli->mode == MODE_TRANS_RULE_SS7 && !strcmp(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.serviceKey,"*") && !strcmp(cli->req.IWFPayload.translatorRuleConfigPayload.translatorRuleConfigInfo.imsiPrefix,"*"))
                    {
                        cli_print(cli,"\n\tERROR: Both IMSI-Prefix and Service-Key are not allowed to be '*', please modify one of the parameter and commit the changes.");
                        CLI_ERROR_LOG("ERROR: Both IMSI-Prefix and Service-Key are not allowed to be '*', please modify one of the parameter and commit the changes.");
                        return CLI_OK;
                    }
                    else if(((cli->mode == MODE_CONFIG_DCCA_DESTINATION) && (cli->req.cmd_id != C_cli_dcca_dest_config_Id)) ||
                            ((cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO) && (cli->req.cmd_id != C_cli_protocol_actions_Id)))
                            
                    {
                        cli_print(cli, "\n\tNothing to commit.");
                        CLI_DEBUG_LOG("Nothing to commit.");
                        CLI_DEBUG_LOG(" Exited ");
                        return CLI_OK;
                    }
                    else
                    {
                        cli->dict_count = 0;
                        send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                        if(cli->mode == MODE_CONFIG_DCCA_DESTINATION)
                            init_dcca_dest_config(cli);
                        else if(cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO)
                            init_protocolactions_config(cli);
                    }
                }
                else {

                    CLI_DEBUG_LOG("OP_CODE - MODIFY");   
                    if((cli->mode == MODE_CONFIG_SCTP_PROFILE && cli->req.cmd_id != C_cli_modify_sctp_profile_Id) ||
                            (cli->mode == MODE_CONFIG_DESTINATION && cli->req.cmd_id != C_cli_destination_config_Id) ||
                            (cli->mode == MODE_CONFIG_LOCAL && cli->req.cmd_id != C_cli_localconfig_Id) ||
                            (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION && cli->req.cmd_id != C_cli_modify_assocation_Id) ||
                            (cli->mode == MODE_CONFIG_REMOTEROUTE && cli->req.cmd_id != C_cli_remoteroute_config_Id) ||
                            (cli->mode == MODE_CONFIG_CAP_RO_IDP && cmdID != C_cli_cap_ro_idp_config_Id) ||
                            (cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET && cli->req.cmd_id != C_cli_modify_assocation_set_Id) ||
                            (cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT && cli->req.cmd_id != C_cli_modify_sctp_endpoint_Id) ||
                            (cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO && cli->req.cmd_id != C_cli_protocol_actions_Id))
                    {
                        cli_print(cli, "\n\tNothing to commit.");
                        CLI_DEBUG_LOG("Nothing to commit.");
                        CLI_DEBUG_LOG(" Exited ");
                        return CLI_OK;
                    }
                    cli->dict_count = 0;
                    send_receive_data(cli,&cli->req, sizeof(cli->req), cmdID, 0);
                    // making all fileds INVALID_NUM and INVALID_STR otherthan primarykeys once modify request is sent.
                    if(cli->mode == MODE_CONFIG_PEER)
                        init_peer(cli);
                    else if(cli->mode == MODE_MODIFY_LOCALHOST)
                        init_localhost(cli);
                    else if(cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION)
                        init_association_config(cli);
                    else if(cli->mode == MODE_CONFIG_LOCAL)
                        init_localconfig(cli);
                    else if(cli->mode == MODE_CONFIG_MODIFY_ASSOCIATION_SET)
                        init_associationset_config(cli);
                    else if(cli->mode == MODE_CONFIG_REMOTEROUTE)
                        init_remoteroute_config(cli);
                    else if(cli->mode == MODE_CONFIG_MODIFY_SCTP_ENDPOINT)
                        init_sctp_endpoint_config(cli);
                    else if(cli->mode == MODE_CONFIG_RRB_CALL_SCENARIO)
                        init_protocolactions_config(cli);
                    else if(cli->mode == MODE_TRANS_RULE_SS7 || cli->mode == MODE_TRANS_RULE_DIAMETER || 
                            cli->mode == MODE_TRANS_RULE_HTTP)
                        init_translator_rule_config(cli);
                }
            }
            else
            {
                cli_print(cli, "\n\tNothing to commit.");
                CLI_DEBUG_LOG("Nothing to commit.");
                CLI_DEBUG_LOG(" Exited ");
                return CLI_OK;
            }
        }
        else {
            //if commit is not used in cli modes
            cli_print(cli, "\n\tInvalid command");
            CLI_DEBUG_LOG("Invalid command");
            CLI_DEBUG_LOG(" Exited ");
            return CLI_OK;
        }

    }

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    cli_print(cli, "%d arguments:", argc);
    cli_print(cli, "%s ", cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName);
    cli_print(cli, "%s ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName);
    cli_print(cli, "%s ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IpAddr);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.PortNumber);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.TransportType);
    cli_print(cli, "%s ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.AltHostName);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.IsMate);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerSwitchingInfo.Failover);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.watchdogValue);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.TCValue);
    cli_print(cli, "%d ",cli->req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersConfigInfo.expiryValue);
#endif
    cli->allow_exit='y';
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
int no_dre_addPeer(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[0][0] = INVALID_STR;
    req.OP_CODE = DELETE;
    i = CMD_LINE_ARG_ONE;
    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"peer"))
        {
            req.cmd_id = C_cli_no_peer_Id;
        }
        else if(!strcmp(argv[i],"alt-peer"))
        {
            req.cmd_id = C_cli_no_altpeer_Id;
        }
        else if(!strcmp(argv[i],"secondary-ip"))
        {
            req.cmd_id = C_cli_no_peersecondaryip_Id;
        }
        else if(!strcmp(argv[i],"host"))
        {
            i++;
            strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersKeyInfo.peerHostNames,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerTimersConfigPayload.PeerTimersKeyInfo.realmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"ip")){
            i++;
            strncpy(req.Payload.drePeerAndTimerConfigPayload.drePeerPayload.peerInfo.secondaryIp[0],argv[i],MAX_IP_LEN - 1);    
            CLI_DEBUG_LOG("secondaryIp = %s",argv[i]);
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req, sizeof(req), req.cmd_id, 0);


#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    cli_print(cli, "%d arguments:", argc);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/**************************************************************************************/


int no_dre_table(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.OP_CODE = DELETE;
    if (!strcmp(argv[CMD_LINE_ARG_ONE],"peer-table"))
    {
        req.cmd_id = C_cli_no_peer_Id;
    } 
    else if(!strcmp(argv[CMD_LINE_ARG_ONE],"realm-table"))  
    {
        req.cmd_id = C_cli_no_configRealm_Id;
    } 
    else if(!strcmp(argv[CMD_LINE_ARG_ONE],"localhost-table"))
    {

        req.cmd_id = C_cli_no_localhost_Id;
    }
    CLI_DEBUG_LOG("CmdId",req.cmd_id);
    CLI_DEBUG_LOG("OP_CODE - DELETE");
    send_receive_data(cli,&req, sizeof(req), req.cmd_id, CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    {
        int i = 0;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        cli_print(cli, "%d arguments:", argc);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }
#endif

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

/*********************************************************************************************

  ASF COMMANDS

 *********************************************************************************************/
int cli_int_add_asgroup(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_add_asgroup_Id;
    req.OP_CODE = ADD;

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"group-name"))
        {
            i++;
            strncpy(req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName, argv[i],MAX_GRP_NAME - 1);

        } else if(!strcmp(argv[i],"priority")){
            i++;
            req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.priority = atoi(argv[i]);

        } else if(!strcmp(argv[i],"app-type")){

            i++;
            if(!strcmp(argv[i],"hosted")){
                req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.appType = true;

            } else if(!strcmp(argv[i],"external")){
                req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.appType = false;
            }
        }else if(!strcmp(argv[i],"lb-algo")){

            i++;
            strncpy(req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.lbAlgorithm, argv[i],MAX_NAME_LEN - 1);

        } else if(!strcmp(argv[i],"max-as")){
            i++;
            req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.maxAppInstances = atoi(argv[i]);
        }
        i++;
    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_add_asgroup_Id, I_cli_add_asgroup_Id);
#endif


#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_modify_asgroup(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_modify_asgroup_Id;
    req.OP_CODE = MODIFY;

    //    req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName = INVALID_STR;
    req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.priority = INVALID_NUM;
    //  req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.lbAlgorithm = INVALID_STR;
    req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.maxAppInstances = INVALID_NUM;
    req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.appType = INVALID_NUM;

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"group-name"))
        {
            i++;
            strncpy(req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName, argv[i],MAX_GRP_NAME - 1);

        } else if(!strcmp(argv[i],"priority")){
            i++;
            req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.priority = atoi(argv[i]);
        }else if(!strcmp(argv[i],"lb-algo")){

            i++;
            strncpy(req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.lbAlgorithm, argv[i],MAX_NAME_LEN - 1);

        } else if(!strcmp(argv[i],"max-as")){
            i++;
            req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.maxAppInstances = atoi(argv[i]);
        }
        i++;
    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_modify_asgroup_Id, I_cli_modify_asgroup_Id);
#endif


#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_show_asgroup(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_show_asgroup_Id;

    if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
    {
        //        req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName = INVALID_STR;
    } else {
        i++;
        strncpy(req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName, argv[i],MAX_GRP_NAME - 1);
    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_show_asgroup_Id, I_cli_show_asgroup_Id);
#endif

#ifdef CLI_DEBUG
    {
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }

#endif
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_delete_asgroup(struct cli_def *cli, char *command, char *argv[], int argc)
{
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.OP_CODE = DELETE;

    req.cmd_id = C_cli_delete_asgroup_Id;
    strncpy(req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName, argv[CMD_LINE_ARG_TWO],MAX_GRP_NAME - 1);

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_delete_asgroup_Id, I_cli_delete_asgroup_Id);
#endif

#ifdef CLI_DEBUG
    {
        int i = 0;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }

#endif
    return CLI_OK;

}

int cli_int_asf_responseTimeout(struct cli_def *cli, char *command, char *argv[], int argc)
{
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_asf_responseTimeout_Id;

    req.OP_CODE = ADD;
    //req.Payload.dreASFConfigPayload.dreASFConfigKeyInfo.ComponentID = COMP_DRE_APP;
    req.Payload.dreASFConfigPayload.dreASFRespTimeout.responseTimeout = INVALID_NUM;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"as"))
    {
        req.Payload.dreASFConfigPayload.dreASFRespTimeout.responseTimeout = atoi(argv[CMD_LINE_ARG_TWO]);

    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_asf_responseTimeout_Id, I_cli_asf_responseTimeout_Id);
#endif

#ifdef CLI_DEBUG
    {
        int i = 0;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }

#endif
    return CLI_OK;

}
/*********************************************************************************************



 *********************************************************************************************/
int cli_int_asf_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_asf_config_Id;

    req.OP_CODE = ADD;
    //req.Payload.dreASFConfigPayload.dreASFConfigKeyInfo.ComponentID = COMP_DRE_APP;
    req.Payload.dreASFConfigPayload.dreASFRespTimeout.responseTimeout = INVALID_NUM;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"asf"))
    {
        if(!strcmp(argv[CMD_LINE_ARG_ONE],"enable")){
            req.Payload.dreASFConfigPayload.dreASFStatus.ASFStatus = true;

        }else if (!strcmp(argv[CMD_LINE_ARG_ONE],"disable")){
            req.Payload.dreASFConfigPayload.dreASFStatus.ASFStatus = false;
        }

    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_asf_config_Id, I_cli_asf_config_Id);
#endif

#ifdef CLI_DEBUG
    {
        int i = 0;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }

#endif
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_asf_terminate(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));
    req.cmd_id = C_cli_asf_terminate_Id;

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"asgroup"))
        {
            i++;
            strncpy(req.Payload.dreASFAppGroupPayload.dreASFKeyInfo.GroupName, argv[i],MAX_GRP_NAME - 1);

        } else if(!strcmp(argv[i],"as-instance")){
            i++;
            if(!strcmp(argv[i],"all")){
                req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.instanceId = INVALID_NUM;
            }

        }else if (!strcmp(argv[i],"instance")){
            i++;
            req.Payload.dreASFAppGroupPayload.dreASFConfigInfo.instanceId = atoi(argv[i]);
        }
        i++;

    }

#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), C_cli_asf_terminate_Id, I_cli_asf_terminate_Id);
#endif

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);
#endif
    return CLI_OK;

}



/*********************************************************************************************
  ERLBF Callback functions


 *********************************************************************************************/
int cli_int_set_erlbf_peer_group(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    int setPeerConfig =0;

    cli->req.Payload.peerGroupsPayload.peer_group.lb_algo[0] = INVALID_STR;
    cli->req.Payload.peerGroupsPayload.peer_group.pcrf_binding = INVALID_NUM;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if (!strcmp(argv[CMD_LINE_ARG_ZERO],"modify")){
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else {
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }
    int allow=0;
    cli->req.cmd_id = C_cli_set_erlbf_peer_group_Id;

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"peer-group"))
        {
            i++;
            allow=1;
            strncpy(cli->req.Payload.peerGroupsPayload.peer_group.groupname, argv[i],MAX_GRP_NAME - 1);
            CLI_DEBUG_LOG("groupname = %s",argv[i]);
        } 
        else if(!strcmp(argv[i],"lb-algo"))
        {
            i++;
            cli->req.cmd_id = C_cli_set_erlbf_peer_group_Id;              
            CLI_DEBUG_LOG("lb-algo = %s",argv[i]);
            strncpy(cli->req.Payload.peerGroupsPayload.peer_group.lb_algo, argv[i],MAX_NAME_LEN - 1);
        }
        else if (!strcmp(argv[i],"enable-pcrf-binding"))
        {
            i++;
            if (!strcmp(argv[i], "true"))
            {
                cli->req.Payload.peerGroupsPayload.peer_group.pcrf_binding = 1;
            }
            else {
                cli->req.Payload.peerGroupsPayload.peer_group.pcrf_binding = 0;
            }
            CLI_DEBUG_LOG("pcrf_binding = %s",argv[i]);
        }
        else if(!strcmp(argv[i+1],"peer-config")) 
        {
            i++;
            cli_int_configPrompt(cli, command, argv, argc);
            setPeerConfig = 1;
        }
        else{
            i++;
        }
    }
    if(allow==1)
        cli_int_configPrompt(cli, command, argv, argc);
    if(cli->req.OP_CODE == ADD) {   
        cli->allow_exit=0;
    }
    if(!setPeerConfig && cli->req.OP_CODE == MODIFY && !strcmp(cli->req.Payload.peerGroupsPayload.peer_group.lb_algo,"weighted"))
    {
        cli_print(cli,"\n\tNOTE: Configure Peer-Weight values(if not configured previously) for peers under this peer-group.");
        CLI_INFO_LOG("NOTE: Configure Peer-Weight values(if not configured previously) for peers under this peer-group.");
    }
    if(!setPeerConfig && cli->req.OP_CODE != ADD) {
        cli->req.cmd_id = C_cli_set_erlbf_peer_group_Id;
        if(cli->req.OP_CODE == DELETE)
            cli->state = STATE_DELETE_PEERGROUP;
        else
        {
            CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
            send_receive_data(cli, &cli->req, sizeof(cli->req), cli->req.cmd_id, 0);
            memset(&cli->req, 0, sizeof(SetConfigReq));
        }
    }

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);
#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

/*********************************************************************************************



 *********************************************************************************************/
int cli_int_set_erlbf_peer_config(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    memset(&cli->req.Payload.peerGroupsPayload.peer_info, 0, sizeof(ErlbfPeer));
    cli->req.Payload.peerGroupsPayload.peer_group.lb_algo[0] = INVALID_STR;
    cli->req.Payload.peerGroupsPayload.peer_group.pcrf_binding = INVALID_NUM;
    cli->req.Payload.peerGroupsPayload.peer_info.peer_weight = INVALID_NUM;
    cli->req.Payload.peerGroupsPayload.peer_info.peer_priority = INVALID_NUM;
    cli->req.cmd_id = C_cli_set_erlbf_peer_config_Id; 
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if (!strcmp(argv[CMD_LINE_ARG_ZERO],"modify")){
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else {
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while((argv[i] && argv[i + 1]))
    {
        if(!strcmp(argv[i],"peer-name"))
        {
            i++;  
            CLI_DEBUG_LOG("peer_name = %s",argv[i]);
            strncpy(cli->req.Payload.peerGroupsPayload.peer_info.peer_name, argv[i],MAX_HOST_NAME - 1);  
        } 
        else if(!strcmp(argv[i],"realm"))
        {
            i++;  
            CLI_DEBUG_LOG("realmname = %s",argv[i]);
            strncpy(cli->req.Payload.peerGroupsPayload.peer_info.realmName, argv[i],MAX_PARAM_SIZE - 1);  
        }       
        else if(!strcmp(argv[i],"weight"))
        {
            i++;              
            CLI_DEBUG_LOG("peer_weight = %d",atoi(argv[i]));
            cli->req.Payload.peerGroupsPayload.peer_info.peer_weight = atoi(argv[i]);
        }         
        else if (!strcmp(argv[i],"priority"))
        {
            i++;
            CLI_DEBUG_LOG("peer_priority = %d",atoi(argv[i]));
            cli->req.Payload.peerGroupsPayload.peer_info.peer_priority = atoi(argv[i]);
        }
        i++;
    }

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);
#endif

    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    if(cli->req.OP_CODE != ADD){ 
        send_receive_data(cli, &cli->req, sizeof(cli->req), cli->req.cmd_id, 0);
    }
    else {
        if(cli->req.Payload.peerGroupsPayload.peer_info.peer_weight == INVALID_NUM)
        {
            cli_print(cli,"\n\tNOTE: peer-weight is optional and is applicable only for the peer-groups added with \"weighted\" algorithm (lb-algo). \
                    \n\t      For rest of the peer-groups with different lb-algo values, peer-weight value is ignored in DRE. \
                    \n\t      If you want peer-weight give weight and commit, otherwise cli will set peer-weight default value as '100'.");
        }

        cli->allow_exit=0;
    }
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

/********************************************************************************************
 *
 *
 *
 *
 *********************************************************************************************/
int cli_int_show_peer_group(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    if(!strcmp(argv[CMD_LINE_ARG_ONE],"peer-group-config"))
    {
        if(!strcmp(argv[CMD_LINE_ARG_TWO],"all"))
        {
            req.Payload.peerGroupsPayload.peer_group.groupname[0] = INVALID_STR;
            req.cmd_id = C_cli_show_all_erlbf_peer_group_Id;
        }
        else if(!strcmp(argv[CMD_LINE_ARG_TWO],"group")){
            req.cmd_id = C_cli_show_erlbf_peer_group_Id;
            strncpy(req.Payload.peerGroupsPayload.peer_group.groupname, argv[CMD_LINE_ARG_THREE],MAX_GRP_NAME - 1);
            CLI_DEBUG_LOG("groupname = %s",argv[CMD_LINE_ARG_THREE]);
        }
        else 
            return CLI_ERROR;
    }
    else if(!strcmp(argv[CMD_LINE_ARG_ONE],"peer-group-peers"))
    {
        if(!strcmp(argv[CMD_LINE_ARG_TWO],"group")){
            req.cmd_id = C_cli_show_erlbf_peer_group_peers_Id;
            strncpy(req.Payload.peerGroupsPayload.peer_group.groupname, argv[CMD_LINE_ARG_THREE],MAX_GRP_NAME - 1);
            CLI_DEBUG_LOG("groupname = %s",argv[CMD_LINE_ARG_THREE]);
        }
        else 
            return CLI_ERROR;
    }
    else
        return CLI_ERROR;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
#ifdef SEND_ALL_REQ
    send_receive_data(cli, &req, sizeof(req), req.cmd_id, 0);
#endif

#ifdef CLI_DEBUG
    {
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

void init_peerdictionary(struct cli_def *cli)
{
    CLI_DEBUG_LOG(" Entered ");
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.HostName[0] = INVALID_STR;
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.RealmName[0] = INVALID_STR;
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[0][0] = INVALID_STR;
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict = INVALID_NUM;
    CLI_DEBUG_LOG(" Exited ");
}
int cli_int_configDictionary(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");

    int i = 0,j = 0,found = 0;
    char *dictPtr;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        cli->req.OP_CODE = DELETE;
        init_peerdictionary(cli);   
        cli->req.cmd_id=C_cli_deletedictionary_Id;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
    }
    else if (!strcmp(argv[CMD_LINE_ARG_ZERO],"modify")){
        cli->req.OP_CODE = MODIFY;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else {
        cli->req.OP_CODE = ADD;
        CLI_DEBUG_LOG("OP_CODE - ADD");
    }

    while((argv[i]))
    {       

        if(!strcmp(argv[i],"dictionary"));   
        else if(!strcmp(argv[i],"host")){
            i++;
            cli->dict_count = 0;
            strncpy(cli->req.Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(cli->req.Payload.drePeerPayload.peerDictionaryInfo.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        else if((dictPtr = strstr(command, "dict-name")) || (dictPtr = strstr(command, "dictionary-name")) != NULL){
            i++;
            if(cli->dict_count < MAX_DICTIONARY_NUM)
            {
                if(cli->dict_count !=0)
                    for(j=0;j<=cli->dict_count;j++)
                    {
                        // to check whether user entered same dictionary name again 
                        if(!strcmp(cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[j],argv[i]))
                            found = 1;
                    }
                if(found == 0)
                {
                    strncpy(cli->req.Payload.drePeerPayload.peerDictionaryInfo.PeerDictionaryIds[cli->dict_count],argv[i],MAX_NAME_LEN - 1);
                    CLI_DEBUG_LOG("dictionary-name = %s",argv[i]);
                    cli->dict_count++;  
                }
                else
                {
                    cli_print(cli,"\n\tERROR!! Dictionary name %s already entered.",argv[i]);
                    CLI_ERROR_LOG("ERROR!! Dictionary name %s already entered.",argv[i]);
                }
                if(cli->dict_count == MAX_DICTIONARY_NUM)
                {
                    cli_print(cli,"\n\tMax dictionary count %d reached. Type commit to apply the configuration.",MAX_DICTIONARY_NUM);
                    CLI_WARNING_LOG("Max dictionary count %d reached. Type commit to apply the configuration.",MAX_DICTIONARY_NUM);
                }
            }
            else {
                cli_print(cli,"\n\tERROR!! Max %d dictionaries are allowed to be configured. Type commit to apply the configuration.",MAX_DICTIONARY_NUM);
                CLI_ERROR_LOG("ERROR!! Max %d dictionaries are allowed to be configured. Type commit to apply the configuration.",MAX_DICTIONARY_NUM);
            }
        }
        i++;
    }
    cli->req.Payload.drePeerPayload.peerDictionaryInfo.num_dict = cli->dict_count;
    // to allow user to come out of mode if he is not adding dictionaries
    if(cli->req.OP_CODE == ADD && cli->dict_count !=0)
    { 
        cli->req.cmd_id = C_cli_peer_dictionary_Id;
    }
    CLI_DEBUG_LOG("CmdID = %d",cli->req.cmd_id);
    if(cli->req.OP_CODE == ADD)
        cli->allow_exit=0;
    else
        send_receive_data(cli,&cli->req, sizeof(cli->req), cli->req.cmd_id, 0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_showDictionary(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i=0;
    GetConfigReq req;
    memset(&req, 0, sizeof(GetConfigReq));

    req.cmd_id = C_cli_show_dictionary_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"peer-dictionary")){
        i = CMD_LINE_ARG_TWO;
    }else
        return CLI_ERROR;

    while(argv[i]){

        if(!strcmp(argv[i],"host")){
            i++;
            strncpy(req.shReqPayload.dreKeyInfo.peerKeyInfo.HostName,argv[i],MAX_HOST_NAME - 1);
            CLI_DEBUG_LOG("HostName = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"realm")){
            i++;
            strncpy(req.shReqPayload.dreKeyInfo.peerKeyInfo.RealmName,argv[i],MAX_PARAM_SIZE - 1);
            CLI_DEBUG_LOG("RealmName = %s",argv[i]);
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),C_cli_show_dictionary_Id, CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    {
        int i;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }
#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}


/************************************************************************************

 ***********************************************************************************/


int cli_int_getPeerIds(struct cli_def *cli, char *command, char *argv[], int argc)
{
    SetConfigReq req;

    memset(&req, 0, sizeof(SetConfigReq));

    req.cmd_id = C_cli_get_erlbf_peer_ids_Id;

    send_receive_data(cli,&req,sizeof(req),C_cli_get_erlbf_peer_ids_Id, 0);
    return CLI_OK;
}



/************************************************************************************
 *                      TRANSORM CALLBACK FUNCTION                                  *
 ***********************************************************************************/


int cli_int_loadDictionary(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    int cmdID;
    int interfaceID = 0;

    interfaceID = CLI_CMGR_INTERFACE_ID;

    cmdID = C_cli_load_dictionary_Id;
    req.cmd_id = C_cli_load_dictionary_Id;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        req.OP_CODE = UNLOAD;
        cmdID = C_cli_unload_dictionary_Id;
        req.cmd_id = C_cli_unload_dictionary_Id;
    }
    else {
        req.OP_CODE = LOAD;
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"dictionary"));
        else if(!strcmp(argv[i],"dictionary-name"))
        {
            i++;
            strncpy(req.Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName,argv[i],MAX_NAME_LEN - 1);
            //printf("DictionaryName = %s\n",req.Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName);
        }
        else
            return CLI_ERROR;
        i++;
    }


    //#ifdef SEND_ALL_REQ 
    send_receive_data(cli,&req,sizeof(req),cmdID,interfaceID);
    //#endif

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif

    //printf("%s:%d",__FUNCTION__,__LINE__);
    return CLI_OK;

}

int cli_int_loadTransformplugin(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    int cmdID;
    int interfaceID = 0;

    interfaceID = CLI_CMGR_INTERFACE_ID;

    cmdID = C_cli_load_transformplugin_Id;
    req.cmd_id = C_cli_load_transformplugin_Id;

    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        req.OP_CODE = UNLOAD;
        cmdID = C_cli_unload_transformplugin_Id;
        req.cmd_id = C_cli_unload_transformplugin_Id;
    }
    else {
        req.OP_CODE = LOAD;
    }

    if(!strcmp(argv[i],"plugin"))
    {
        i++;
        while(argv[i] && argv[i+1])
        {
            if(!strcmp(argv[i],"plugin-name"))
            {
                i++;
                strncpy(req.Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName,argv[i],MAX_NAME_LEN - 1);
            }
            else if(!strcmp(argv[i],"dictionary-1"))
            {
                i++;
                strncpy(req.Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary1,argv[i],MAX_NAME_LEN - 1);
            }
            else if(!strcmp(argv[i],"dictionary-2"))
            {
                i++;
                strncpy(req.Payload.dtfPayload.dreTransformPluginLoadInfo.Dictionary2,argv[i],MAX_NAME_LEN - 1);
            }
            else if(!strcmp(argv[i],"config-file"))
            {
                i++;
                strncpy(req.Payload.dtfPayload.dreTransformPluginLoadInfo.ConfigFileName,argv[i],MAX_NAME_LEN - 1);
            }
            else
            {
                return CLI_ERROR;
            }
            i++;
        }
    }
    else
    {
        return CLI_ERROR;
    }


    //#ifdef SEND_ALL_REQ 
    send_receive_data(cli,&req,sizeof(req),cmdID,interfaceID);
    //#endif

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif

    //printf("%s:%d",__FUNCTION__,__LINE__);
    return CLI_OK;

}       

int cli_int_showLoadedDictionary(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i=0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"dictionaries"))
    {
        i++;
        //  if(strcmp(argv[i],"all"))
        {
            req.cmd_id = C_cli_show_all_loaded_dictionary_Id;
            //          strcpy(req.Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName,"\0");
        }
#if 0   
        else if(!strcmp(argv[i],"dictioanry-name"))
        {

            cmdID = C_cli_show_loaded_dictionary_Id;
            req.cmd_id = C_cli_show_loaded_dictionary_Id;
            strcpy(req.Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName,argv[i]);
            printf("DictionaryName = %s\n",req.Payload.dtfPayload.dreDictionaryKeyInfo.DictionaryName);
        }
#endif

    }
    else
        return CLI_ERROR;

    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id, CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    {
        int i;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }
#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_showLoadedTransformPlugin(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i=0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    int cmdID=0;
    int interfaceID = 0;

    interfaceID = CLI_CMGR_INTERFACE_ID;

    if(!strcmp(argv[CMD_LINE_ARG_ONE],"transform-plugin"))
    {
        i++;
        if(strcmp(argv[i],"all"))
        {
            cmdID = C_cli_show_loaded_transformplugin_Id;
            req.cmd_id = C_cli_show_loaded_transformplugin_Id;
            req.Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName[0] = INVALID_STR;
        }
        else if(!strcmp(argv[i],"plugin-name"))
        {
            cmdID = C_cli_show_all_loaded_transformplugin_Id;
            req.cmd_id = C_cli_show_all_loaded_transformplugin_Id;
            strncpy(req.Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName,argv[i],MAX_NAME_LEN - 1);
            //printf("PluginName = %s\n",req.Payload.dtfPayload.dreTransformPluginLoadInfo.dreTransformPluginKeyInfo.PluginName);
        }

    }
    else
    {
        return CLI_ERROR;
    }   
    send_receive_data(cli,&req,sizeof(req),cmdID, CLI_CMGR_INTERFACE_ID);
#ifdef CLI_DEBUG
    {
        int i;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);
    }
#endif
    return CLI_OK;
}

/*********************************************************************************************
  Logging Callback functions


 *********************************************************************************************/

int cli_int_setLogging(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.loggingPayload.compName[0] = INVALID_STR;
    req.Payload.loggingPayload.logLevel[0] = INVALID_STR;
    req.Payload.loggingPayload.logChannel[0] = INVALID_STR;

    req.cmd_id = C_cli_set_log_level_Id;

    if(!strcmp(argv[i],"log-level") || (!strcmp(argv[i], "log-channel")))
    {
        i+= CMD_LINE_ARG_TWO;

        while(argv[i])
        {
            if(!strcmp(argv[i],"dre"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"DRE",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"asf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"ASF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"avamgr"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"AVAMGR",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"dtf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"DTF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"erlbf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"ERLBF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"cli"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"CLI",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"cmgr"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"CMGR",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"iwf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"IWF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"all"))
            {
                strncpy(req.Payload.loggingPayload.compName,"all",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                req.cmd_id = C_cli_setall_log_level_Id;
            }
            else if(!strcmp(argv[i],"DEBUG"))
            {   
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i], "ERROR"))
            {
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i], "INFO"))
            {
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"NOTICE"))
            {
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"WARNING"))
            {
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"CRITICAL"))
            {
                strncpy(req.Payload.loggingPayload.logLevel,argv[i],MAX_LOG_LEVEL_LEN - 1);
                CLI_DEBUG_LOG("logLevel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"syslog"))
            {
                req.cmd_id = C_cli_set_log_channel_Id;
                strncpy(req.Payload.loggingPayload.logChannel,argv[i],MAX_FILE_NAME_LEN - 1);
                CLI_DEBUG_LOG("logChannel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"file"))
            {
                strncpy(req.Payload.loggingPayload.logChannel,argv[i],MAX_FILE_NAME_LEN - 1);
                req.cmd_id = C_cli_set_log_channel_Id;
                CLI_DEBUG_LOG("logChannel = %s",argv[i]);
            }
            else if(!strcmp(argv[i],"console"))
            {
                req.cmd_id = C_cli_set_log_channel_Id;
                strncpy(req.Payload.loggingPayload.logChannel,argv[i],MAX_FILE_NAME_LEN - 1);
                CLI_DEBUG_LOG("logChannel = %s",argv[i]);
            }
            i++;
        }
    }
    else
    {
        return CLI_ERROR;
    }

    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    if(!strcmp(req.Payload.loggingPayload.compName,"all"))
    {
#if DRE
        strncpy(req.Payload.loggingPayload.compName,"ASF",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#endif
        strncpy(req.Payload.loggingPayload.compName,"AVAMGR",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

        strncpy(req.Payload.loggingPayload.compName,"CLI",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

        strncpy(req.Payload.loggingPayload.compName,"CMGR",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#if IWF
        strncpy(req.Payload.loggingPayload.compName,"IWF",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#endif
#if DRE
        strncpy(req.Payload.loggingPayload.compName,"DRE",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

        strncpy(req.Payload.loggingPayload.compName,"DTF",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

        strncpy(req.Payload.loggingPayload.compName,"ERLBF",MAX_COMP_NAME_LEN - 1);
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
#endif
    }
    else
    {
        send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
    }
#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}


int cli_int_showLogging(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = CMD_LINE_ARG_ONE;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.loggingPayload.compName[0] = INVALID_STR;
    req.cmd_id = C_cli_show_log_config_Id;
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);

    if(!strcmp(argv[i],"log-config"))
    {
        i++;

        while(argv[i])
        {
            if(!strcmp(argv[i],"dre"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"DRE",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"asf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"ASF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"dtf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"DTF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"erlbf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"ERLBF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"cli"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"CLI",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"webagent"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"WEBAGENT",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"avamgr"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"AVAMGR",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"cmgr"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"CMGR",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if(!strcmp(argv[i],"iwf"))
            {   
                strncpy(req.Payload.loggingPayload.compName,"IWF",MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            else if (!strcmp(argv[i],"all"))
            {   
                strncpy(req.Payload.loggingPayload.compName,argv[i],MAX_COMP_NAME_LEN - 1);
                CLI_DEBUG_LOG("compName = %s",argv[i]);
                i++;
            }
            i++;
        }
    }
    else
    {
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif

    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

int cli_int_showVersion(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(req));
    req.cmd_id = C_cli_show_version_Id;

    if(argv[CMD_LINE_ARG_ONE] == NULL){
        return CLI_ERROR;
    }

    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);
#endif
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}

// GENERAL CONFIG CALLBACKS
int cli_int_sctpconfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    int i = 0;
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.sctpconfig.heartbeat = INVALID_NUM;
    req.Payload.sctpconfig.heartbeattimeout = INVALID_NUM;
    req.Payload.sctpconfig.inittimeout = INVALID_NUM;
    req.Payload.sctpconfig.maxattempts = INVALID_NUM;
    req.Payload.sctpconfig.pathfailureretrycount = INVALID_NUM;
    req.Payload.sctpconfig.rtoinit = INVALID_NUM;
    req.Payload.sctpconfig.rtomin = INVALID_NUM;
    req.Payload.sctpconfig.rtomax = INVALID_NUM;
    while(argv[i])
    {
        if(!strcmp(argv[i],"heart-beat"))
        {
            i++;
            if(!strcmp(argv[i],"enable"))
                req.Payload.sctpconfig.heartbeat = ENABLE;
            else if(!strcmp(argv[i],"disable"))
                req.Payload.sctpconfig.heartbeat = DISABLE;
            CLI_DEBUG_LOG("heartbeat = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"heart-beat-timeout"))
        {
            i++;
            req.Payload.sctpconfig.heartbeattimeout = atoi(argv[i]);
            CLI_DEBUG_LOG("heartbeattimeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"init-timeout"))
        {
            i++;
            req.Payload.sctpconfig.inittimeout = atoi(argv[i]);   
            CLI_DEBUG_LOG("inittimeout = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"max-attempts"))
        {
            i++;
            req.Payload.sctpconfig.maxattempts = atoi(argv[i]);
            CLI_DEBUG_LOG("max-attempts = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"pathfail-retrycount"))
        {
            i++;
            req.Payload.sctpconfig.pathfailureretrycount = atoi(argv[i]);
            CLI_DEBUG_LOG("pathfail-retrycount = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-initial"))
        {
            i++;
            req.Payload.sctpconfig.rtoinit = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-initial = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-min"))
        {
            i++;
            req.Payload.sctpconfig.rtomin = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-min = %d",atoi(argv[i]));
        }
        else if(!strcmp(argv[i],"rto-max"))
        {
            i++;
            req.Payload.sctpconfig.rtomax = atoi(argv[i]);
            CLI_DEBUG_LOG("rto-max = %d",atoi(argv[i]));
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",C_cli_sctpconfig_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_sctpconfig_Id,0); 
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}    

int cli_int_tlsconfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.tlsconfig.identityverification = INVALID_NUM;
    req.Payload.tlsconfig.crlverification = INVALID_NUM;
    int i = CMD_LINE_ARG_ONE;
    while(argv[i])
    {
        if(!strcmp(argv[i],"id-verification"))
        {
            i++;
            if(!strcmp(argv[i],"enable"))
                req.Payload.tlsconfig.identityverification = ENABLE;
            else
                req.Payload.tlsconfig.identityverification = DISABLE;
            CLI_DEBUG_LOG("id-verification = %s",argv[i]);
        }
        else if(!strcmp(argv[i],"crl-verification"))
        {
            i++;
            if(!strcmp(argv[i],"enable"))
                req.Payload.tlsconfig.crlverification = ENABLE;
            else
                req.Payload.tlsconfig.crlverification = DISABLE;
            CLI_DEBUG_LOG("crl-verification = %s",argv[i]);
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",C_cli_tlsconfig_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_tlsconfig_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_tlsciphersuite(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.ciphersuite.ciphersuitename[0] = INVALID_STR;
    req.Payload.ciphersuite.cipherenable = INVALID_NUM;
    int i = CMD_LINE_ARG_ONE;
    if(!strcmp(argv[i],"cipher-suite"))
    {
        i++;
        strncpy(req.Payload.ciphersuite.ciphersuitename,argv[i],MAX_NAME_LEN - 1);
        CLI_DEBUG_LOG("ciphersuitename = %s",argv[i]);
        i++;
        if(!strcmp(argv[i],"enable"))
            req.Payload.ciphersuite.cipherenable = ENABLE;
        else
            req.Payload.ciphersuite.cipherenable = DISABLE;
        CLI_DEBUG_LOG("cipherenable = %s",argv[i]);
    }
    else
        return CLI_ERROR;
    CLI_DEBUG_LOG("CmdID = %d",C_cli_tlssuite_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_tlssuite_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_trustedcaconfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.trustedca.cafile[0] = INVALID_STR;    
    req.Payload.trustedca.crlfile[0] = INVALID_STR;
    int i = 0;
    req.cmd_id = C_cli_trustedca_Id;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"no")){
        i = CMD_LINE_ARG_ONE;
        req.OP_CODE = DELETE;
        CLI_DEBUG_LOG("OP_CODE - DELETE");
        if(!strcmp(argv[i],"crl-file"))
        {
            i = CMD_LINE_ARG_TWO;
            req.cmd_id = C_cli_notrustedca_Id;
        }
    }
    else if (!strcmp(argv[CMD_LINE_ARG_ZERO],"modify")){
        req.OP_CODE = MODIFY;
        i = CMD_LINE_ARG_ONE;
        CLI_DEBUG_LOG("OP_CODE - MODIFY");
    }
    else {
        CLI_DEBUG_LOG("OP_CODE - ADD");
        req.OP_CODE = ADD;
    }

    while(argv[i])
    {
        if(!strcmp(argv[i],"ca-file"))
        {
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.trustedca.cafile,argv[i],MAX_NAME_LEN - 1);
                CLI_DEBUG_LOG("cafile = %s",argv[i]);
            }
        }
        else if(!strcmp(argv[i],"crl-file"))
        {
            i++;
            if(argv[i])
            {
                strncpy(req.Payload.trustedca.crlfile,argv[i],MAX_NAME_LEN - 1);
                CLI_DEBUG_LOG("crlfile = %s",argv[i]);
            }
        }
        i++;
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}

int cli_int_showgeneralconfig(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    GetConfigReq req;
    memset(&req, 0, sizeof(GetConfigReq));
    int i = CMD_LINE_ARG_ONE;

    if(!strcmp(argv[i],"sctp-config"))
    {
        req.cmd_id = C_cli_showsctpconfig_Id;
    }
    else if(!strcmp(argv[i],"tls-config"))
    {
        req.cmd_id = C_cli_showtlsconfig_Id;
    }
    else if(!strcmp(argv[i],"trusted-ca-config"))
    {
        req.cmd_id = C_cli_showtrustedcaconfig_Id;
    }
    else if(!strcmp(argv[i],"cipher-suite-config"))
    {
        req.cmd_id = C_cli_showciphersuiteconfig_Id;
    }
    else
    {
        req.cmd_id = C_cli_showgeneralconfig_Id;
    }
    CLI_DEBUG_LOG("CmdID = %d",req.cmd_id);
    send_receive_data(cli,&req,sizeof(req),req.cmd_id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;

}
int cli_int_peerIpcheck(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.peeripcheck.ipcheck = INVALID_NUM;
    int i = CMD_LINE_ARG_ZERO;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"peer-ip-check"))
    {
        i++;
        if(!strcmp(argv[i],"enable"))
            req.Payload.peeripcheck.ipcheck = ENABLE;            
        else
            req.Payload.peeripcheck.ipcheck = DISABLE;
        CLI_DEBUG_LOG("peer-ip-check = %s",argv[i]);
    }
    else
        return CLI_ERROR;
    CLI_DEBUG_LOG("CmdID = %d",C_cli_peeripcheck_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_peeripcheck_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}


int cli_int_predectiveloopdetection(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.predictiveLoopdetection.predectiveloopdetection = INVALID_NUM;
    int i = CMD_LINE_ARG_ZERO;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"predictive-loop-detection"))
    {
        i++;
        if(!strcmp(argv[i],"enable"))
            req.Payload.predictiveLoopdetection.predectiveloopdetection = ENABLE;            
        else
            req.Payload.predictiveLoopdetection.predectiveloopdetection = DISABLE;
        CLI_DEBUG_LOG("predictive-loop-detection = %s",argv[i]);
    }
    else
        return CLI_ERROR;
    CLI_DEBUG_LOG("CmdID = %d",C_cli_predectiveloopdetection_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_predectiveloopdetection_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}


int cli_int_snaptrsupport(struct cli_def *cli, char *command, char *argv[], int argc)
{
    CLI_DEBUG_LOG(" Entered ");
    SetConfigReq req;
    memset(&req, 0, sizeof(SetConfigReq));
    req.Payload.snaptrSupport.snaptrsupport = INVALID_NUM;
    int i = CMD_LINE_ARG_ZERO;
    if(!strcmp(argv[CMD_LINE_ARG_ZERO],"snaptr-support"))
    {
        i++;
        if(!strcmp(argv[i],"enable"))
            req.Payload.snaptrSupport.snaptrsupport = ENABLE;            
        else
            req.Payload.snaptrSupport.snaptrsupport = DISABLE;
        CLI_DEBUG_LOG("snaptr-support = %s",argv[i]);
    }
    else
        return CLI_ERROR;
    CLI_DEBUG_LOG("CmdID = %d",C_cli_snaptrsupport_Id);
    send_receive_data(cli,&req,sizeof(req),C_cli_snaptrsupport_Id,0);
    CLI_DEBUG_LOG(" Exited ");
    return CLI_OK;
}
