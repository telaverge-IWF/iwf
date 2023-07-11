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


#ifndef _CMD_HANDLER_H_
#define _CMD_HANDLER_H_
#include "cmd_utils.h"

/* Export function Declarations */
extern int cli_int_help(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));
extern int cli_int_quit(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));
extern int cli_int_exit(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_history(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));
extern int cli_int_enable(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));
extern int cli_int_disable(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));

extern int cli_int_peerControl(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showpeer(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showuser(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showrealm(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showdefaultRoute (struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showDiscoverPeer(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showDiameterBaseConfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showNodeState(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showconfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showDictionary(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_log(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_adduser(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_deleteuser(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modifyuser(struct cli_def *cli, char *command, char *argv[], int argc);
extern int no_dre_table(struct cli_def *cli, char *command, char *argv[], int argc);

extern int cli_int_configTerminal(struct cli_def *cli, UNUSED(char *command), UNUSED(char *argv[]), UNUSED(int argc));
extern int cli_int_configPrompt(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_diameterbasePrompt(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_discoveryInterval(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_discoverPeer(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_configRealm(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_defaultRoute(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_localhost(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modifypeer(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modifyrealm(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modifylocalhost(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modifydefaultRoute(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_resetdefault(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_no_configRealm(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_no_localhost(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_configDictionary(struct cli_def *cli, char *command, char *argv[], int argc);

extern int no_debug_avmgr(struct cli_def *cli, UNUSED(char *command), char *argv[], int argc);
extern int component_configure(struct cli_def *cli, char *command, char *argv[], int argc);
extern int dre_component_prompt(struct cli_def *cli, char *command, char *argv[], int argc);
extern int dre_addPeer(struct cli_def *cli, char *command, char *argv[], int argc);
void init_peer(struct cli_def *cli); 
void init_peerdictionary(struct cli_def *cli); 
void init_localhost(struct cli_def *cli); 
void init_realm(struct cli_def *cli);
void init_staticrouting(struct cli_def *cli);
extern int dre_peerConfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int no_dre_addPeer(struct cli_def *cli, char *command, char *argv[], int argc);
extern int no_dre_Peert(struct cli_def *cli, char *command, char *argv[], int argc);
extern int endConfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_staticrouting(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showstaticrouting(struct cli_def *cli, char *command, char *argv[], int argc);
//ASF CALLBACKS
extern int cli_int_add_asgroup(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_modify_asgroup(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_asgroup(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_delete_asgroup(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_asf_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_asf_terminate(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_asf_responseTimeout(struct cli_def *cli, char *command, char *argv[], int argc);

//ERLBF CALLBACKS
extern int cli_int_set_erlbf_peer_group(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_set_erlbf_peer_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_peer_group(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_getPeerIds(struct cli_def *cli, char *command, char *argv[], int argc);

//TRANSFORM CALLBACKS
extern int cli_int_loadDictionary(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_loadTransformplugin(struct cli_def *cli, char *command, char *argv[], int argc); 
extern int cli_int_showLoadedDictionary(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showLoadedTransformPlugin(struct cli_def *cli, char *command, char *argv[], int argc);

// LOGGING CALLBACKS
int cli_int_setLogging(struct cli_def *cli, char *command, char *argv[], int argc);
int cli_int_showLogging(struct cli_def *cli, char *command, char *argv[], int argc); 
int cli_int_showVersion(struct cli_def *cli, char *command, char *argv[], int argc); 

//HA CALLBACKS
int cli_int_showconfigavamgr(struct cli_def *cli, char *command, char *argv[], int argc);
int cli_int_switchover(struct cli_def *cli, char *command, char *argv[], int argc);

//GENERAL CONFIG CALLBACKS
extern int cli_int_peerIpcheck(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_sctpconfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_tlsconfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_tlsciphersuite(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_trustedcaconfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_showgeneralconfig(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_predectiveloopdetection(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_snaptrsupport(struct cli_def *cli, char *command, char *argv[], int argc);

//SIGTRAN CONFIG CALLBACKS
extern int cli_int_local_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_localconfig(struct cli_def *cli);
extern int cli_int_show_sigtran_local_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_sctp_endpoint_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_sigtran_multihoming_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_sctp_endpoint_config(struct cli_def *cli);
extern int cli_int_show_sctp_endpoint_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_sctp_profile_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_sctpprofile_config(struct cli_def *cli);
extern int cli_int_show_sctp_profile_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_association_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_association_config(struct cli_def *cli);
extern int cli_int_show_association_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_associationset_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_associationset_config(struct cli_def *cli);
extern int cli_int_show_associationset_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_destination_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_destination_config(struct cli_def *cli);
extern int cli_int_show_destination_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_remoteroute_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_remoteroute_config(struct cli_def *cli);
extern int cli_int_show_remoteroute_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_activate_associationSet(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_activate_association(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_ual_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_ual_config(struct cli_def *cli, char *command, char *argv[], int argc);

//IWF CONFIG CALLBACKS
extern int cli_int_translator_rule_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_translator_rule_config(struct cli_def *cli);
extern int cli_int_show_translatorrule_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_s6a_map_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_s6a_map_config(struct cli_def *cli);
extern int cli_int_show_S6aMAP_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_map_s6a_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_delete_map_s6a_config_vplmn(struct cli_def *cli,char *command,char *argv[], int argc);
extern void init_map_s6a_config(struct cli_def *cli);
extern int cli_int_show_MAPS6a_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_cap_ro_idp_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_cap_ro_idp_config(struct cli_def *cli);
extern int check_for_invalid_idp_config(struct cli_def *cli);
extern int cli_int_cap_ro_idp_sms_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_cap_ro_idp_sms_config(struct cli_def *cli);
extern int check_for_invalid_idp_sms_config(struct cli_def *cli);
extern int cli_int_show_CAPRo_config(struct cli_def *cli, char *command, char *argv[], int argc);
int cli_int_showIwfVersion(struct cli_def *cli, char *command, char *argv[], int argc); 
extern int cli_int_cap_timers(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_cap_timers(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_log_cdr(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_log_cdr_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_feature_config(struct cli_def *cli);
extern int cli_int_dcca_general_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_dcca_general_config(struct cli_def *cli);
extern int cli_int_failure_handling_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_dcca_dest_config(struct cli_def *cli);
extern int cli_int_dcca_dest_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_dcca_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern void init_protocolactions_config(struct cli_def *cli);
extern int cli_int_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_delete_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_protocolactions_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_show_feature_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_feature_config(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_clearsession(struct cli_def *cli, char *command, char *argv[], int argc);
extern int cli_int_dump_system_info(struct cli_def *cli, char *command, char *argv[], int argc);
#endif

