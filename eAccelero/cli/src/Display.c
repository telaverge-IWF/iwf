
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
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CommonStructure.h"
#include "LibCli.h"
#include "InterfaceDefs.h"
#include <pthread.h>
extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);
int printcli(struct cli_def *cli,void *buf)
{
    CLI_DEBUG_LOG(" Entered ");
    int i;
    int j;
    int k;

    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    char *str4 = NULL;

    char *saveptr1 = NULL;
    char *saveptr2 = NULL;
    char *saveptr3 = NULL;
    char *saveptr4 = NULL;
    char *token = NULL;
    char *subtoken;
    char *subsubtoken;
    char *subsubsubtoken;
    char delimRecord[]="\n";
    char delimParam[]= "\t";
    char delimTable[]= "\b";
    char delimSubParam[]= "}";
    char delimSubSubParam[]= ")";
    char header[MAX_HEADER_LEN][MAX_HEADER_LEN];
    char *startptr;
    AllResponses *rsp;


    rsp = (AllResponses*) buf;
    CLI_DEBUG_LOG("rsp->cmd_id = %d",rsp->cmd_id);
    CLI_DEBUG_LOG("rsp->ResponseCode = %d",rsp->ResponseCode);
    if(rsp->ResponseCode == DONT_ALLOW_STANDBY)
    {
        cli_print(cli,"\n\n\tWARNING! %s\n",rsp->payload);
        CLI_CRITICAL_LOG("WARNING! %s",rsp->payload);
        /*free cli structure */
        cli_free_history(cli);
        cli_done(cli);
        pthread_exit(NULL);
        return 0;
    }
    if(rsp->cmd_id == C_cli_GetNodeState_Id)
    {
        if(rsp->ResponseCode == CMGR_FETCH_ERROR)
        {
            cli_print(cli,"\n\tError! %s",rsp->payload);
            CLI_ERROR_LOG("Error! %s",rsp->payload);
        }
        else
        {
            cli_print(cli,"\n\t%s",rsp->payload);
            CLI_DEBUG_LOG("rsp->payload = %s",rsp->payload);
        }

        return 0;
    }

    if(rsp->cmd_id == C_cli_verify_passwd_Id)
    {
        if(rsp->ResponseCode == CMGR_FETCH_ERROR)
        {
            cli->user_found = AUTH_USER_NOT_FOUND;
            if(cli->state == STATE_MOD_USER_PASSWORD)
            {
                cli_print(cli,"\n\tError! Failed to modify user since the user %s doesn't exists",cli->user.username);
                CLI_ERROR_LOG("Error! Failed to modify user since the user %s doesn't exists",cli->user.username);
            }
            else
            {
                cli_print(cli,"\n\n\tError! %s",rsp->payload);
                CLI_ERROR_LOG("rsp->payload = %s",rsp->payload);
            }
            return 0;
        }
        cli->user_found = 0;
        //password for verification at the time of login and modify user password
        memcpy(cli->user.encryptedPassword,rsp->password,PASSWORD_LENGTH);

        startptr = (char *)rsp->payload;
        token    = strtok_r((char *)startptr, delimTable, &saveptr3);

        str2     = token;

        /*extracting the first row of usertable containing headings
         * FieldNames :- UserT  UserName  Privilege */
        subtoken = strtok_r(str2,delimRecord, &saveptr1);

        /*extracting the data related to FieldNames from Payload
         * in same order as FieldNames */
        subtoken = strtok_r(NULL,delimRecord, &saveptr1);

        if (subtoken == NULL)
        {
            CLI_ERROR_LOG("Error! subtoken");
            return 0;
        }
        /*copying the subtoken (value of fieldnames) into str3*/
        str3 = subtoken;
        token = (char* )strtok_r((char*)str3,"\t\n",&saveptr1);
        if(token)
            strncpy(cli->user.username,token,MAX_NAME_LEN - 1);
        else
        {
            cli_print(cli,"USER NOT FOUND\n");
            CLI_ERROR_LOG("USER NOT FOUND");
            return 0;
        }
        token = strtok_r(NULL,"#\t\n",&saveptr1);

        if(token != NULL)
        {
            if(!strcmp(token,"operator"))
            {
                cli->privilege = PRIVILEGE_OPERATOR;
            }
            else
            {
                cli->privilege = PRIVILEGE_ADMIN;
            }
            CLI_DEBUG_LOG("cli->privilege = %d",cli->privilege);
        }
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }

    startptr = (char *)rsp->payload;
    if(rsp->ResponseCode == DRE_CONFIG_SUCCESS)
    {
        if(rsp->cmd_id == C_cli_localhost_Id || 
                rsp->cmd_id == C_cli_modifylocalhost_Id ||
                rsp->cmd_id == C_cli_tlsconfig_Id ||
                rsp->cmd_id == C_cli_tlssuite_Id ||
                rsp->cmd_id == C_cli_notrustedca_Id ||
                rsp->cmd_id == C_cli_deletetransport_Id ||
                rsp->cmd_id == C_cli_deletesecondaryip_Id ||
                rsp->cmd_id == C_cli_trustedca_Id ||
                rsp->cmd_id == C_cli_sctpconfig_Id ||
                rsp->cmd_id == C_cli_peeripcheck_Id ||
                rsp->cmd_id == C_cli_snaptrsupport_Id ||
                rsp->cmd_id == C_cli_predectiveloopdetection_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF to apply configuration.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF to apply configuration.");
        }
        else if(rsp->cmd_id == C_cli_switchover_Id)
        {
            cli_print(cli,"\n\tSuccess! SwitchOver is Successful");
            CLI_DEBUG_LOG("Success! SwitchOver is successful.");
        }
        else if(rsp->cmd_id == C_cli_setall_log_level_Id)
        {
            cli_print(cli,"\n\tSuccess! %s",rsp->payload);
            CLI_DEBUG_LOG("Success! %s",rsp->payload);
        }
        else
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful.");
            CLI_DEBUG_LOG("Success! Configuration is successful.");
        }
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }
    if(rsp->ResponseCode == IWF_CONFIG_SUCCESS)
    {
        if(rsp->cmd_id == C_cli_localconfig_Id ||
                rsp->cmd_id == C_cli_modify_assocation_Id ||
                rsp->cmd_id == C_cli_modify_assocation_set_Id ||
                rsp->cmd_id == C_cli_no_assocation_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF to apply configuration.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF to apply configuration.");
        }
        else if(rsp->cmd_id == C_cli_modify_sctp_endpoint_Id ||
                rsp->cmd_id == C_cli_delete_sctpendpoint_multihoming_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF if SCTPEndPoint is associated to an Association.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF if SCTPEndPoint is associated to an Association.");
        }
        else if(rsp->cmd_id == C_cli_modify_sctp_profile_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF if SCTPProfile is associated to an Association.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF if SCTPProfile is associated to an Association.");
        }
#if 0
        else if(rsp->cmd_id == C_cli_modify_assocation_set_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF if any Associations are linked to AssociationSet.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF if any Associations are linked to AssociationSet.");
        }
#endif
        else if(rsp->cmd_id == C_cli_modify_destination_config_Id)
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful, Restart IWF if any Destination is linked to Route.");
            CLI_DEBUG_LOG("Success! Configuration is successful, Restart IWF if any Destination are linked to Route.");
        }
        else
        {
            cli_print(cli,"\n\tSuccess! Configuration is successful.");
            CLI_DEBUG_LOG("Success! Configuration is successful.");
        }
    }
    if(rsp->ResponseCode == DRE_DB_FAIL)
    {
        CLI_ERROR_LOG(" no records ");
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }
    if(rsp->ResponseCode == CMGR_CONFIG_ERROR ||
            rsp->ResponseCode == DRE_CONFIG_ERROR ||
            rsp->ResponseCode == IWF_CONFIG_ERROR)
    {
        cli_print(cli,"\n\tError! %s",rsp->payload);
        CLI_ERROR_LOG("Error! %s",rsp->payload);
        if(rsp->cmd_id == C_cli_assocation_Id ||
                rsp->cmd_id == C_cli_assocation_set_Id ||
                rsp->cmd_id == C_cli_modify_assocation_set_Id ||
                rsp->cmd_id == C_cli_remoteroute_config_Id)
        {
            cli_print(cli,"\n\tNOTE: If IWF is installed in HotStandBy Mode, configuration may be successful in StandByNode.");
            cli_print(cli,"\n\t\tPlease verify the configuration using Show command.");
            CLI_DEBUG_LOG("NOTE: If IWF is installed in HotStandBy Mode, configuration may be successful in StandByNode.");
        }
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }
    if(rsp->ResponseCode == DEFAULT_OPTION)
    {
        cli_print(cli,"\n\tCLI Error! No matching functionality found.");
        CLI_CRITICAL_LOG("CLI Error! No matching functionality found.");
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }
    if(rsp->ResponseCode == CMGR_FETCH_ERROR)
    {
        if(rsp->cmd_id == C_cli_showallpeer_Id ||
                rsp->cmd_id == C_cli_showlocalhost_Id ||
                rsp->cmd_id == C_cli_showrealm_Id ||
                rsp->cmd_id == C_cli_showconfigallrealm_Id ||
                rsp->cmd_id == C_cli_showallstaticrouting_Id ||
                rsp->cmd_id == C_cli_show_all_erlbf_peer_group_Id ||
                rsp->cmd_id == C_cli_show_all_sctp_profile_config_Id ||
                rsp->cmd_id == C_cli_show_all_sctp_endpoint_config_Id ||
                rsp->cmd_id == C_cli_show_all_association_config_Id ||
                rsp->cmd_id == C_cli_show_all_associationset_config_Id ||
                rsp->cmd_id == C_cli_show_all_destination_config_Id ||
                rsp->cmd_id == C_cli_show_all_remoteroute_config_Id ||
                rsp->cmd_id == C_cli_show_all_translatorrule_config_Id ||
                rsp->cmd_id == C_cli_show_maps6a_config_Id ||
                rsp->cmd_id == C_cli_show_s6amap_config_Id ||
                rsp->cmd_id == C_cli_show_capro_idpsms_config_Id ||
                rsp->cmd_id == C_cli_show_capro_idp_ext_tele_config_Id ||
                rsp->cmd_id == C_cli_show_capro_idp_ext_bearer_config_Id ||
                rsp->cmd_id == C_cli_show_ual_config_Id ||
                rsp->cmd_id == C_cli_show_capro_idp_config_Id ||
                rsp->cmd_id == C_cli_showtrustedcaconfig_Id ||
                rsp->cmd_id == C_cli_show_cap_timers_Id ||
                rsp->cmd_id == C_cli_show_log_cdr_Id ||
                rsp->cmd_id == C_cli_show_dcca_general_config_Id ||
                rsp->cmd_id == C_cli_show_protocolactions_config_Id ||
                rsp->cmd_id == C_cli_show_tAns_trigger_config_Id ||
                rsp->cmd_id == C_cli_show_congestion_management_config_Id ||
                rsp->cmd_id == C_cli_show_s6amap_sgsn_addr_config_Id ||
                rsp->cmd_id == C_cli_show_s6amap_sgsn_prefix_config_Id ||
                rsp->cmd_id == C_cli_showpeerstatus_Id)
        {
            cli_print(cli,"\n\t%s",rsp->payload);
            CLI_DEBUG_LOG("%s",rsp->payload);
            if(rsp->cmd_id == C_cli_show_capro_idp_config_Id)
                cli->has_capro_idp_config = NO;
        }
        else
        {
            //to avoid going to modify mode if loclahost is not configured.   
            if(rsp->cmd_id == C_cli_get_localhostconfig_Id)
                cli->localhost_mode = YES;
            cli_print(cli,"\n\tError! %s",rsp->payload);
            CLI_ERROR_LOG("Error! %s",rsp->payload);
        }
        CLI_DEBUG_LOG(" Exited ");
        return 0;
    }

    if(rsp->cmd_id == C_cli_showuser_Id ||
            rsp->cmd_id == C_cli_showpeer_Id ||
            rsp->cmd_id == C_cli_showpeerstatus_Id ||
            rsp->cmd_id == C_cli_showpeerconfig_Id ||
            rsp->cmd_id == C_cli_showallpeer_Id ||
            rsp->cmd_id == C_cli_get_localhostconfig_Id ||
            rsp->cmd_id == C_cli_showlocalhost_Id ||
            rsp->cmd_id == C_cli_showuser_Id ||
            rsp->cmd_id == C_cli_showrealm_Id ||
            rsp->cmd_id == C_cli_showconfigrealm_Id ||
            rsp->cmd_id == C_cli_showconfigallrealm_Id ||
            rsp->cmd_id == C_cli_showDiscoverPeer_Id ||
            rsp->cmd_id == C_cli_showDiameterbase_Id ||
            rsp->cmd_id == C_cli_showconfig_Id ||
            rsp->cmd_id == C_cli_showtask_Id ||
            rsp->cmd_id == C_cli_show_dictionary_Id ||
            rsp->cmd_id == C_cli_show_loaded_dictionary_Id ||
            rsp->cmd_id == C_cli_show_all_loaded_dictionary_Id ||
            rsp->cmd_id == C_cli_show_loaded_transformplugin_Id ||
            rsp->cmd_id == C_cli_show_all_loaded_transformplugin_Id ||
            rsp->cmd_id == C_cli_show_asgroup_Id ||
            rsp->cmd_id == C_cli_show_erlbf_peer_group_Id ||
            rsp->cmd_id == C_cli_show_erlbf_peer_group_peers_Id ||
            rsp->cmd_id == C_cli_show_all_erlbf_peer_group_Id || 
            rsp->cmd_id == C_cli_show_log_config_Id || 
            rsp->cmd_id == C_cli_show_version_Id ||
            rsp->cmd_id == C_cli_show_peerdictionary_Id ||
            rsp->cmd_id == C_cli_showroute_Id ||
            rsp->cmd_id == C_cli_showconfigavamgr_Id ||
            rsp->cmd_id == C_cli_showdefaultRoute_Id ||
            rsp->cmd_id == C_cli_showsctpconfig_Id ||
            rsp->cmd_id == C_cli_showtlsconfig_Id ||
            rsp->cmd_id == C_cli_showtrustedcaconfig_Id ||
            rsp->cmd_id == C_cli_showciphersuiteconfig_Id ||
            rsp->cmd_id == C_cli_showgeneralconfig_Id ||
            rsp->cmd_id == C_cli_showallstaticrouting_Id ||
            rsp->cmd_id == C_cli_showstaticrouting_Id ||
            rsp->cmd_id == C_cli_show_local_config_Id ||
            rsp->cmd_id == C_cli_show_capro_idp_ext_tele_config_Id ||
            rsp->cmd_id == C_cli_show_capro_idp_ext_bearer_config_Id ||
            rsp->cmd_id == C_cli_show_capro_idpsms_config_Id ||
            rsp->cmd_id == C_cli_show_capro_idp_config_Id ||
            rsp->cmd_id == C_cli_show_maps6a_config_Id ||
            rsp->cmd_id == C_cli_show_s6amap_config_Id ||
            rsp->cmd_id == C_cli_show_translatorrule_config_Id ||
            rsp->cmd_id == C_cli_show_all_translatorrule_config_Id ||
            rsp->cmd_id == C_cli_show_sctp_profile_config_Id ||
            rsp->cmd_id == C_cli_show_all_sctp_profile_config_Id ||
            rsp->cmd_id == C_cli_show_sctp_endpoint_config_Id ||
            rsp->cmd_id == C_cli_show_all_sctp_endpoint_config_Id ||
            rsp->cmd_id == C_cli_show_association_config_Id ||
            rsp->cmd_id == C_cli_show_all_association_config_Id ||
            rsp->cmd_id == C_cli_show_associationset_config_Id ||
            rsp->cmd_id == C_cli_show_all_associationset_config_Id ||
            rsp->cmd_id == C_cli_show_destination_config_Id ||
            rsp->cmd_id == C_cli_show_all_destination_config_Id ||
            rsp->cmd_id == C_cli_show_remoteroute_config_Id ||
            rsp->cmd_id == C_cli_show_all_remoteroute_config_Id ||
            rsp->cmd_id == C_cli_show_ual_config_Id ||
            rsp->cmd_id == C_cli_show_iwf_version_Id ||
            rsp->cmd_id == C_cli_show_cap_timers_Id ||
            rsp->cmd_id == C_cli_show_log_cdr_Id ||
            rsp->cmd_id == C_cli_show_dcca_general_config_Id ||
            rsp->cmd_id == C_cli_show_dcca_dest_config_Id ||
            rsp->cmd_id == C_cli_show_protocolactions_config_Id ||
            rsp->cmd_id == C_cli_show_tAns_trigger_config_Id ||
            rsp->cmd_id == C_cli_show_congestion_management_config_Id ||
            rsp->cmd_id == C_cli_show_s6amap_sgsn_addr_config_Id ||
            rsp->cmd_id == C_cli_show_s6amap_sgsn_prefix_config_Id ||
            rsp->cmd_id == C_cli_show_ciphersuites_Id)
            {
                for(k=1, str3 = (char*)startptr; ; k++,str3 = NULL)
                {
                    token = strtok_r(str3,delimTable,&saveptr3);

                    if(token == NULL)
                        break;

                    for (j = 1, str1 = token; ; j++, str1 = NULL) 
                    {
                        token = strtok_r(str1,delimRecord, &saveptr1);
                        if (token == NULL)
                            break;

                        for (i=0,str2 = token; ; i++,str2 = NULL) 
                        {
                            subtoken = strtok_r(str2,delimParam, &saveptr2);
                            if (subtoken == NULL)
                                break;

                            if(j == 1)
                            {
                                strncpy(header[i],subtoken,MAX_HEADER_LEN - 1);
                                // to avoid printing table name for showing dictionaries when user enters dictionary mode while configuring
                                if(i == 0 && 
                                        rsp->cmd_id != C_cli_show_peerdictionary_Id && 
                                        rsp->cmd_id != C_cli_show_ciphersuites_Id)
                                {
                                    cli_print(cli,"\n-------------------------------------------------");
                                    cli_print(cli,"             %s",header[i]);
                                    cli_print(cli,"-------------------------------------------------");

                                }

                            }
                            else if (j >1)
                            {
                                if(C_cli_show_protocolactions_config_Id)
                                {
                                    int l = 0;
                                    for(l = 0, str3=subtoken; ; l++,str3=NULL)
                                    {
                                        subsubtoken = strtok_r(str3,delimSubParam, &saveptr3);
                                        if (subsubtoken == NULL)
                                            break;
                                        int m=0;
                                        for(m = 0, str4=subsubtoken; ; m++,str4=NULL)
                                        {
                                            subsubsubtoken = strtok_r(str4,delimSubSubParam, &saveptr4);
                                            if(subsubsubtoken == NULL)
                                                break;
                                            if(m==0)
                                            {
                                                if(l==0)
                                                cli_print(cli,"    %-25s : %s",header[i+1],subsubsubtoken);
                                                else
                                                    cli_print(cli,"\t\t\t\t%s",subsubsubtoken);
                                            }
                                            else
                                                cli_print(cli,"\t\t\t\t\t   %s",subsubsubtoken);
                                        }
                                    }
                                }
                                else
                                {
                                    cli_print(cli,"    %-25s : %s",header[i+1],subtoken);
                                }
                            }
                        }
                        cli_print(cli," ");
                    }
                }
            }

    CLI_DEBUG_LOG(" Exited ");
    return 0;
}

