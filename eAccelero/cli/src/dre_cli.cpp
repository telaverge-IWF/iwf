
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
extern "C" {

#include "dq_cli.h"
#include "CliCallback.h"
#include "InterfaceDefs.h"
    extern void cli_log(const char *funName, int lineNo, int loglevel, const char *dataString, ...);
}

int dre_cli_init(struct cli_def *ctree)
{
    CLI_DEBUG_LOG(" Registering CLI commands to cli tree ");

    //////////////////////////////////////////Execution Mode Commands //////////////////////////////////////////
#if 0
    //help command  1
    Add_CLI(ctree, cli_int_help,
            I_cli_help_Id,
            M_cli_help_Id,
            C_cli_help_Id,
            "help",
            "show available commands"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_OPERATOR, C_cli_help_Id);
#endif

    //quit command  2
    Add_CLI(ctree, cli_int_quit,
            I_cli_quit_Id,
            M_cli_quit_Id,
            C_cli_quit_Id,
            "quit",
            "Command to disconnect the current CLI session"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_OPERATOR, C_cli_quit_Id);


    //exit command  3
    Add_CLI(ctree, cli_int_exit,
            I_cli_exit_Id,
            M_cli_exit_Id,
            C_cli_exit_Id,
            "exit",
            "Command to exit from current mode"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_OPERATOR, C_cli_exit_Id);

    //modify generic command  3
    Add_CLI(ctree, NULL,
            I_cli_modify_Id,
            M_cli_modify_Id,
            C_cli_modify_Id,
            "modify",
            "Command to Modify the configuration"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_ADMIN, C_cli_modify_Id);


    //history command   4
    Add_CLI(ctree, cli_int_history,
            I_cli_history_Id,
            M_cli_history_Id,
            C_cli_history_Id,
            "history",
            "Command to show a list of previously run commands"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_OPERATOR, C_cli_history_Id);

    Add_CLI(ctree, NULL,
            I_cli_no_Id,
            M_cli_no_Id,
            C_cli_no_Id,
            "no",
            "Command to delete the configuration"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_ADMIN, C_cli_no_Id);

    //peer command  7

    Add_CLI(ctree, cli_int_peerControl,
            I_cli_peerControl_Id,
            M_cli_peerControl_Id,
            C_cli_peerControl_Id,
            "peer-state host WORD realm WORD (enable | disable)",
            "Command to enable/disable the peer state",
            "Host name of the peer",
            "Enter host name of the peer",
            "Realm name",
            "Enter realm name",
            "Enable/start the peer",
            "Disable/stop the peer"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_peerControl_Id);

    //show peer command 8
    Add_CLI(ctree, cli_int_showpeer,
            0,
            0,
            C_cli_showpeerconfig_Id,
            "show peer-config host WORD realm WORD",
            "Command to view the configuration",
            "Peer configuration info",
            "Keyword, hostname",
            "Enter the host name",
            "Keyword, realmname",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showpeerconfig_Id);

    Add_CLI(ctree, cli_int_showpeer,
            0,
            0,
            C_cli_showpeerconfig_Id,
            "show peer-config all",
            "Command to view the configuration",
            "Peer configuration info",
            "All peers info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showpeerconfig_Id);

    Add_CLI(ctree, cli_int_showpeer,
            I_cli_showpeer_Id,
            M_cli_showpeer_Id,
            C_cli_showpeer_Id,
            "show peer-status host WORD realm WORD",
            "Command to view the configuration",
            "Peer status info",
            "Keyword, hostname",
            "Enter the host name",
            "Keyword, realmname",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showpeer_Id);

    Add_CLI(ctree, cli_int_showpeer,
            0,
            0,
            C_cli_showpeerstatus_Id,
            "show peer-status all",
            "Command to view the configuration",
            "Peer status info",
            "Show for all peers-status"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showpeerstatus_Id);

    //show realm command
    Add_CLI(ctree, cli_int_showrealm,
            0,
            0,
            C_cli_showconfigrealm_Id,
            "show realm-config realm WORD",
            "Command to view the configuration",
            "Realm configuration info",
            "Keyword-realm",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showconfigrealm_Id);

    Add_CLI(ctree, cli_int_showrealm,
            0,
            0,
            C_cli_showconfigallrealm_Id,
            "show realm-config all",
            "Command to view the configuration",
            "Realm configuration info",
            "Show all realms info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showconfigallrealm_Id);

    Add_CLI(ctree, cli_int_showrealm,
            0,
            0,
            C_cli_showroute_Id,
            "show realm-route WORD",
            "Command to view the configuration",
            "Realm routing info",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showroute_Id);

    //show realm command
#if 0
    Add_CLI(ctree, cli_int_showDiscoverPeer,
            I_cli_showDiscoverPeer_Id,
            M_cli_showDiscoverPeer_Id,
            C_cli_showDiscoverPeer_Id,
            "show discover-peers",
            "Command to view the configuration",
            "discovering peers"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showDiscoverPeer_Id);
#endif

    //show config diameter-base command
    Add_CLI(ctree, cli_int_showDiameterBaseConfig,
            I_cli_showDiameterbase_Id,
            M_cli_showDiameterbase_Id,
            C_cli_showDiameterbase_Id,
            "show diameter-base config",
            "Command to view the configuration",
            "Diameter-base configuration info",
            "Info of peer-table, realm-table and local-host"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showDiameterbase_Id);

    //Show node State
    Add_CLI(ctree, cli_int_showNodeState,
            I_cli_GetNodeState_Id,
            M_cli_GetNodeState_Id,
            C_cli_GetNodeState_Id,
            "show node-status",
            "Command to view the configuration",
            "Node status info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_GetNodeState_Id);

    Add_CLI(ctree, cli_int_showconfig,
            I_cli_showconfig_Id,
            M_cli_showconfig_Id,
            C_cli_showconfig_Id,
            "show local-host-config",
            "Command to view the configuration",
            "Local-host configuration info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showconfig_Id);

    Add_CLI(ctree, cli_int_showconfigavamgr,
            0,
            0,
            C_cli_showconfigavamgr_Id,
            "show ha config",
            "Command to view the configuration",
            "High-availability manager",
            "Configuration info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showconfigavamgr_Id);

    Add_CLI(ctree, cli_int_switchover,
            0,
            0,
            C_cli_switchover_Id,
            "activate switchover",
            "Command to activate switchover",
            "Switchover between active and standby"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_switchover_Id);

    //add user command  13
#if 0
    Add_CLI(ctree, cli_int_adduser,
            I_cli_adduser_Id,
            M_cli_adduser_Id,
            C_cli_adduser_Id,
            "user username WORD group (admin | operator)",
            "Command to add new user",
            "Keyword user-name",
            "Enter the user-name",
            "Group for the user",
            "Admin group",
            "Operator group"
           );
#endif
    Add_CLI(ctree, cli_int_adduser,
            I_cli_adduser_Id,
            M_cli_adduser_Id,
            C_cli_adduser_Id,
            "user username WORD",
            "Command to add new user",
            "Keyword user-name",
            "Enter the user-name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_adduser_Id);

    //delete user command    14
    Add_CLI(ctree, cli_int_deleteuser,
            I_cli_deleteuser_Id,
            M_cli_deleteuser_Id,
            C_cli_deleteuser_Id,
            "no user WORD",
            "Command to delete user",
            "User-name to be deleted",
            "Enter the user-name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_deleteuser_Id);

    //modify user command   13
#if 0
    Add_CLI(ctree, cli_int_adduser,
            I_cli_adduser_Id,
            M_cli_adduser_Id,
            C_cli_adduser_Id,
            "modify user username WORD group (admin | operator)",
            "modify command for modifying user details",
            "command for modifying the existing user details",
            "user-name to be modified ",
            "enter the user-name",
            "group for the user",
            "admin group",
            "operator group"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_moduser_Id);
#endif
    //modify user command   13
    Add_CLI(ctree, cli_int_adduser,
            I_cli_adduser_Id,
            M_cli_adduser_Id,
            C_cli_adduser_Id,
            "modify user username WORD password",
            "Command for modifying user details",
            "Modify the existing user details",
            "User-name to be modified",
            "Enter the user-name",
            "Password for the user"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_adduser_Id);
    //showuser command

    Add_CLI(ctree, cli_int_showuser,
            I_cli_showuser_Id,
            M_cli_showuser_Id,
            C_cli_showuser_Id,
            "show user",
            "Command to view the configuration",
            "Existing users info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_showuser_Id);


    //////////////////////////////////////Config mode commands///////////////////////////////////////////////

    //configure terminal command    13
    Add_CLI(ctree, cli_int_configTerminal,
            I_cli_config_Id,
            M_cli_config_Id,
            C_cli_config_Id,
            "configure-terminal",
            "Command to set cli to Configure-terminal mode"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_config_Id);

#if 0
    //avlmgr Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "avlmgr",
            "command sets cli to availability manager configuration mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    //config manager Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "cmgr",
            "command sets cli to config-manager configuration mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
#endif

    //diameterbase Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "diameter-base",
            "Command to set cli to diameter base mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);


#if 0
    //dre Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "dre",
            "Command to set cli to diameter routing engine mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    //erlbf Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "erlbf",
            "Command to set cli to erlbf configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DRE, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    //Static Routing Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "static-routing",
            "Command to set cli to static-routing configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DRE, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_staticrouting_Id,
            M_cli_staticrouting_Id,
            C_cli_staticrouting_Id,
            "dest-host WORD dest-realm WORD",
            "Command to add Static routing",
            "Enter the destinaton host name",
            "keyWord destination realm",
            "Enter the destinaton realm name"
            );

    cli_install(ctree, MODE_CONFIG_STATIC_ROUTING, PRIVILEGE_ADMIN, C_cli_staticrouting_Id);

    Add_CLI(ctree, cli_int_staticrouting,
            I_cli_staticrouting_Id,
            M_cli_staticrouting_Id,
            C_cli_staticrouting_Id,
            "static-peer WORD realm WORD priority <1-100> (|app-id <1-999999999>)",
            "Command to add a peer for static routing",
            "Enter the peer name",
            "Keyword realm name",
            "Enter the realm name",
            "Priority",
            "Enter the priority range",
            "Application Id",
            "Enter application id value"
           );
    cli_install(ctree, MODE_STATIC_PEER_CONFIG, PRIVILEGE_ADMIN, C_cli_staticrouting_Id);

    Add_CLI(ctree, cli_int_staticrouting,
            I_cli_staticrouting_Id,
            M_cli_staticrouting_Id,
            C_cli_staticrouting_Id,
            "modify dest-host WORD dest-realm WORD peer WORD realm WORD (|app-id <1-999999999>) priority <1-100>",
            "Command to modify the configuration",
            "Destination host to be modified",
            "Enter the destination host name",
            "keyWord destination realm",
            "Enter the destinaton realm name",
            "Keyword peer name",
            "Enter the peer name",
            "Keyword realm name",
            "Enter the realm name",
            "Application Id",
            "Enter application id value",
            "Priority",
            "Enter the priority range"
           );
    cli_install(ctree, MODE_CONFIG_STATIC_ROUTING, PRIVILEGE_ADMIN, C_cli_staticrouting_Id);

    Add_CLI(ctree, cli_int_staticrouting,
            I_cli_staticrouting_Id,
            M_cli_staticrouting_Id,
            C_cli_staticrouting_Id,
            "no dest-host WORD dest-realm WORD peer WORD realm WORD (|app-id <1-999999999>)",
            "Command to delete the configuration",
            "Destination host to be deleted",
            "Enter the destination host name",
            "keyWord destination realm",
            "Enter the destinaton realm name",
            "Keyword peer name",
            "Enter the peer name",
            "Keyword realm name",
            "Enter the realm name",
            "Application Id",
            "Enter application id value"
           );
    cli_install(ctree, MODE_CONFIG_STATIC_ROUTING, PRIVILEGE_ADMIN, C_cli_staticrouting_Id);

    Add_CLI(ctree, cli_int_showstaticrouting,
            I_cli_showstaticrouting_Id,
            M_cli_showstaticrouting_Id,
            C_cli_showstaticrouting_Id,
            "show static-routing dest-host WORD dest-realm WORD",
            "Command to view the configuration",
            "Static Routing info",
            "dest-name keyword",
            "Enter the destination host name",
            "dest-realm keyword",
            "Enter the destination realm name"
            );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showstaticrouting_Id);

    Add_CLI(ctree, cli_int_showstaticrouting,
            I_cli_showstaticrouting_Id,
            M_cli_showstaticrouting_Id,
            C_cli_showstaticrouting_Id,
            "show static-routing all",
            "Command to view the configuration",
            "Static Routing info",
            "all Routing info"
            );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showallstaticrouting_Id);
#endif
#if 0
    //transform Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "transforms",
            "set cli to transform configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DRE, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    //replication manager  Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "repl-mgr",
            "set cli to replication manager configuration mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
#endif

    //diameter base mode commands
    // PeerTable Mode Command
    Add_CLI(ctree, cli_int_diameterbasePrompt,
            I_cli_diameterbasePrompt_Id,
            M_cli_diameterbasePrompt_Id,
            C_cli_diameterbasePrompt_Id,
            "peer-table",
            "Command to set cli to peer-table configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_diameterbasePrompt_Id);


    //Realm-Table Mode Command
    Add_CLI(ctree, cli_int_diameterbasePrompt,
            I_cli_diameterbasePrompt_Id,
            M_cli_diameterbasePrompt_Id,
            C_cli_diameterbasePrompt_Id,
            "realm-table",
            "Command to set cli to realm-table configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_diameterbasePrompt_Id);


    //delete  entries in a table
#if 0
    Add_CLI(ctree, no_dre_table,
            I_cli_no_table_Id,
            M_cli_no_table_Id,
            C_cli_no_table_Id,
            "no (peer-table | realm-table | localhost-table)",
            "delete all entries from the given table ",
            "peer-table",
            "realm-table",
            "local-host table"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_no_table_Id);
#endif
    //Routing-Table Mode Command
    Add_CLI(ctree, cli_int_diameterbasePrompt,
            I_cli_diameterbasePrompt_Id,
            M_cli_diameterbasePrompt_Id,
            C_cli_diameterbasePrompt_Id,
            "localhost-table",
            "Command to set cli to local-host configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_diameterbasePrompt_Id);
#if 0
    //ASF Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "asf-mode",
            "set cli to asf mode"
           );

    cli_install(ctree, MODE_CONFIG_DRE, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    //discovery-interval Command
    Add_CLI(ctree, cli_int_discoveryInterval,
            I_cli_discoveryIntl_Id,
            M_cli_discoveryIntl_Id,
            C_cli_discoveryIntl_Id,
            "discovery-interval (default | <1-600>)",
            "set peer discovery interval period",
            "set default period ",
            "interval in seconds"
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_discoveryIntl_Id);

    //discover-peer Command
    Add_CLI(ctree, cli_int_discoverPeer,
            I_cli_discoverPeer_Id,
            M_cli_discoverPeer_Id,
            C_cli_discoverPeer_Id,
            "discover-peer realm WORD host WORD",
            "command for discovering peers",
            "realm name",
            "enter the realm name",
            "hostname",
            "enter the hostname"
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_discoverPeer_Id);
    //reset default
    Add_CLI(ctree, cli_int_resetdefault,
            I_cli_resetdefault_Id,
            M_cli_resetdefault_Id,
            C_cli_resetdefault_Id,
            "reset file (WORD | default)",
            "command to reset the configuration",
            "file name",
            "user has to enter the command file",
            "reset to default configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_resetdefault_Id);
#endif

    //default-route Command
    Add_CLI(ctree, cli_int_defaultRoute,
            I_cli_defaultRoute_Id,
            M_cli_defaultRoute_Id,
            C_cli_defaultRoute_Id,
            "default-route peer WORD realm  WORD",
            "Command to set default route",
            "Peer host-name",
            "Enter the peer name",
            "Realm name",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_defaultRoute_Id);
#if 0
    //not suppoted in CMAPI
    //modify default-route command
    Add_CLI(ctree, cli_int_modifydefaultRoute,
            I_cli_modifydefaultRoute_Id,
            M_cli_modifydefaultRoute_Id,
            C_cli_modifydefaultRoute_Id,
            "modify default-route peer WORD realm WORD",
            "command to modify configuration",
            "default-route modifications",
            "peer hostname",
            "enter peer name",
            "realm name served for peer",
            "enter realm name  "
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_modifydefaultRoute_Id);
#endif
    //delete default-route command
    Add_CLI(ctree, cli_int_defaultRoute,
            I_cli_nodefaultRoute_Id,
            M_cli_nodefaultRoute_Id,
            C_cli_nodefaultRoute_Id,
            "no default-route",
            "Command to delete configuration",
            "Default-route deletion"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_nodefaultRoute_Id);

    Add_CLI(ctree, cli_int_showdefaultRoute,
            0,
            0,
            C_cli_showdefaultRoute_Id,
            "show default-route",
            "Command to view the configuration",
            "Default-route info"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR,C_cli_showdefaultRoute_Id);
#if 0
    //Local host configuration command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "local-host host WORD realm WORD",
            "Command to add Localhost configuration",
            "Local hostname",
            "Enter host name  ",
            "Local realm name",
            "Enter realm name  "
           );
    cli_install(ctree, MODE_DIABASE_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);
#endif
    Add_CLI(ctree, cli_int_no_localhost,
            I_cli_deletetransport_Id,
            M_cli_deletetransport_Id,
            C_cli_deletetransport_Id,
            "no local-transport host WORD realm WORD local-transport-id <1-4>",
            "Command to delete a record",
            "Delete local-transport",
            "Local hostname",
            "Enter host name  ",
            "Local realm name",
            "Enter realm name",
            "Transport-id to delete",
            "Enter the transport-id value"
           );
    cli_install(ctree, MODE_DIABASE_LOCALHOST, PRIVILEGE_ADMIN, C_cli_deletetransport_Id);

    Add_CLI(ctree, cli_int_no_localhost,
            0,
            0,
            C_cli_deletesecondaryip_Id,
            "no transport-secondary-ip host WORD realm WORD local-transport-id <1-4> ip WORD",
            "Command to delete a record",
            "Secondary-ip to delete",
            "Local hostname",
            "Enter host name",
            "Local realm name",
            "Enter realm name",
            "Transport-id associated for secondary-ip",
            "Enter the transport-id value",
            "Secondary-ip to delete",
            "Enter the secondary-ip"
           );
    cli_install(ctree, MODE_DIABASE_LOCALHOST, PRIVILEGE_ADMIN, C_cli_deletesecondaryip_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_modifylocalhost_Id,
            M_cli_modifylocalhost_Id,
            C_cli_modifylocalhost_Id,
            "modify local-host host WORD realm WORD",
            "Command to Modify local-host configuration",
            "Local-host configuration",
            "Local hostname",
            "Enter host name  ",
            "Local realm name",
            "Enter realm name"
           );
    cli_install(ctree, MODE_DIABASE_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "local-transport SCTP ip WORD port <1024-65535> (|public-ip WORD) (|ip WORD) (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to add local-host transport configuration",
            "Transport-type SCTP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port",
            "Port number",
            "Public-Ip address",
            "Enter public-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address"
            );
    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);

    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "local-transport TCP ip WORD port <1024-65535> (|public-ip WORD)",
            "Commad to add local-host transport configuration",
            "Transport-type TCP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port",
            "Port number",
            "Public-Ip address",
            "Enter public-ip address"
           );
    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);
#if DRE
    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "local-transport SCTP ip WORD secureport <1024-65535> (|public-ip WORD) (|ip WORD) (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to add local-host transport configuration",
            "Transport-type SCTP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port for TLS connection",
            "TLS Port number",
            "Public-Ip address",
            "Enter public-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address"
            );
    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);

    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "local-transport TCP ip WORD secureport <1024-65535> (|public-ip WORD)",
            "Commad to add local-host transport configuration",
            "Transport-type TCP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port for TLS connection",
            "SecurePort number",
            "Public-Ip address",
            "Enter public-ip address"
           );
    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "local-transport-id <1-4> SCTP ip WORD secureport <1024-65535> (|public-ip WORD) (|ip WORD) (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to modify or add local-transport",
            "Enter the transport-id value",
            "Transport-type SCTP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port for TLS connection",
            "TLS Port number",
            "Public-Ip address",
            "Enter public-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address"
            );
    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "local-transport-id <1-4> TCP ip WORD secureport <1024-65535> (|public-ip WORD)",
            "Command to modify or add local-transport",
            "Enter the transport-id value",
            "Transport-type TCP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port for TLS connection",
            "SecurePort number",
            "Public-Ip address",
            "Enter public-ip address"
           );
    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);
#endif

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "local-transport-id <1-4> SCTP ip WORD port <1024-65535> (|public-ip WORD) (|ip WORD) (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to modify or add local-transport",
            "Enter the transport-id value",
            "Transport-type SCTP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port",
            "Port number",
            "Public-Ip address",
            "Enter public-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip address"
            );
    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "local-transport-id <1-4> TCP ip WORD port <1024-65535> (|public-ip WORD)",
            "Command to modify or add local-transport",
            "Enter the transport-id value",
            "Transport-type TCP",
            "Ip address of the peer",
            "Enter peer ip address",
            "Communication port",
            "Port number",
            "Public-Ip address",
            "Enter public-ip address"
           );
    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "auth-timer life-time <1-65535> grace-time <1-65535> auth-time-out <1-65535>",
            "Command to modify Authentication timers configuration",
            "Authentication life-time in secs",
            "Enter lifetime value(in secs)",
            "Authentication grace-time in secs",
            "Enter grace-time value(in secs)",
            "Authentication time out in secs",
            "Enter time-out value(in secs)"
           );

    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_modifylocalhost,
            0,
            0,
            C_cli_modifylocalhost_Id,
            "acct-timer interim <1-65535> acc-time-out <1-65535>",
            "Command to modify Accounting timers configuration",
            "Accounting interim in secs",
            "Enter interim value(in secs)",
            "Accounting timeout in secs",
            "Enter timeout value(in secs)"
           );

    cli_install(ctree, MODE_MODIFY_LOCALHOST, PRIVILEGE_ADMIN, C_cli_modifylocalhost_Id);

    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "auth-timers life-time <1-65535> grace-time <1-65535> auth-time-out <1-65535>",
            "Command to add Authentication timers configuration",
            "Authentication life-time in secs",
            "Enter lifetime value(in secs)",
            "Authentication grace-time in secs",
            "Enter grace-time value(in secs)",
            "Authentication time out in secs",
            "Enter time-out value(in secs)"
           );

    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);

    Add_CLI(ctree, cli_int_localhost,
            I_cli_localhost_Id,
            M_cli_localhost_Id,
            C_cli_localhost_Id,
            "acct-timers interim <1-65535> acc-time-out <1-65535>",
            "Command to add Accounting timers configuration",
            "Accounting interim in secs",
            "Enter interim value(in secs)",
            "Accounting timeout in secs",
            "Enter timeout value(in secs)"
           );

    cli_install(ctree, MODE_CONFIG_LOCALHOST, PRIVILEGE_ADMIN, C_cli_localhost_Id);

    //removing because not supported in CMAPI
    //delete a record from localhost
#if 0
    Add_CLI(ctree, cli_int_no_localhost,
            I_cli_no_localhost_Id,
            M_cli_no_localhost_Id,
            C_cli_no_localhost_Id,
            "no local-host host WORD realm WORD",
            "command to delete a record",
            "deletes the local-host record",
            "peer hostname",
            "enter host name  ",
            "realm name served for peer",
            "enter realm name  "
           );
    cli_install(ctree, MODE_DIABASE_LOCALHOST, PRIVILEGE_ADMIN, C_cli_no_localhost_Id);
#endif

    //realm table commands
    //realm Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "realm WORD",
            "Command to set realm configuration",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "local-action Local",
            "Command to set Local action for the realm",
            "Local action value Local"
           );

    cli_install(ctree, MODE_CONFIG_REALM, PRIVILEGE_ADMIN, C_cli_configRealm_Id);
#if DRE
    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "local-action Relay",
            "Command to set Local action for the realm",
            "Local action value Relay"
           );

    cli_install(ctree, MODE_CONFIG_REALM, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "local-action Proxy",
            "Command to set Local action for the realm",
            "Local action value Proxy"
           );

    cli_install(ctree, MODE_CONFIG_REALM, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "local-action Redirect redirect-host-usage <0-6> redirect-max-cache-time <1-500>",
            "Command to set Local action for the realm",
            "Local action value Redirect",
            "Redirect host usage ",
            "0 DONT_CACHE, 1 ALL_SESSION, 2 ALL_REALM, 3 REALM_AND_APPLICATION, 4 ALL_APPLICATION, 5 ALL_HOST, 6 ALL_USER",
            "Redirect max cache time ",
            "Enter the time in secs"
           );

    cli_install(ctree, MODE_CONFIG_REALM, PRIVILEGE_ADMIN, C_cli_configRealm_Id);
#endif
    Add_CLI(ctree, cli_int_configRealm,
            I_cli_RealmDestination_Id,
            M_cli_RealmDestination_Id,
            C_cli_RealmDestination_Id,
            "route to-peer WORD to-realm WORD app-id <1-999999999> priority <1-100>",
            "Command to add route info to a realm",
            "Host name",
            "Enter the route host name",
            "Realm name associated to peer",
            "Enter the realm name",
            "Application Id",
            "Enter application id value",
            "Priority",
            "Enter the priority range"
           );

    cli_install(ctree, MODE_CONFIG_REALM, PRIVILEGE_ADMIN, C_cli_RealmDestination_Id);
#if DRE
    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "modify realm WORD local-action Local",
            "Command to modify configuration",
            "Realm to be modified",
            "Enter realm name",
            "Local action for the realm",
            "Local action value Local"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "modify realm WORD local-action Relay",
            "Command to modify configuration",
            "Realm to be modified",
            "Enter realm name",
            "Local action for the realm",
            "Local action value Realy"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "modify realm WORD local-action Proxy",
            "Command to modify configuration",
            "Realm to be modified",
            "Enter realm name",
            "Local action for the realm",
            "Local action value Proxy"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_configRealm_Id);

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_configRealm_Id,
            M_cli_configRealm_Id,
            C_cli_configRealm_Id,
            "modify realm WORD local-action Redirect redirect-host-usage <0-6> redirect-max-cache-time <1-500>",
            "Command to modify configuration",
            "Realm to be modified",
            "Local action for the realm",
            "Local action value Redirect",
            "Redirect host usage ",
            "0 DONT_CACHE, 1 ALL_SESSION, 2 ALL_REALM, 3 REALM_AND_APPLICATION, 4 ALL_APPLICATION, 5 ALL_HOST, 6 ALL_USER",
            "Redirect max cache time ",
            "Enter time in secs"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_configRealm_Id);
#endif
    Add_CLI(ctree, cli_int_configRealm,
            I_cli_RealmDestination_Id,
            M_cli_RealmDestination_Id,
            C_cli_RealmDestination_Id,
            "modify route realm WORD to-peer WORD to-realm WORD app-id <1-999999999> priority <1-100>",
            "Command to modify configuration",
            "Route info to modify",
            "Realm name",
            "Enter the realm name",
            "Host name",
            "Enter the host name",
            "Realm associated for peer",
            "Enter the realm name",
            "Application Id",
            "Enter application id value",
            "Priority",
            "Enter the priority range"
           );

    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_RealmDestination_Id);
    //delete destination in Realm
    Add_CLI(ctree, cli_int_configRealm,
            I_cli_no_configRealm_Id,
            M_cli_no_configRealm_Id,
            C_cli_no_configRealm_Id,
            "no route realm WORD to-peer WORD to-realm WORD app-id <1-999999999> ",
            "Command to delete",
            "Route info to delete",
            "Delete the realm entry",
            "Enter the realm name  ",
            "Host name",
            "enter the host name",
            "Realm associated for peer",
            "Enter the realm name",
            "Application Id",
            "Enter application id value"
           );
    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_no_configRealm_Id);
    //delete total Realm

    Add_CLI(ctree, cli_int_configRealm,
            I_cli_no_configRealm_Id,
            M_cli_no_configRealm_Id,
            C_cli_no_configRealm_Id,
            "no realm WORD",
            "Command to delete",
            "Delete the realm entry",
            "Enter the realm name "
           );
    cli_install(ctree, MODE_DIABASE_REALMTABLE, PRIVILEGE_ADMIN, C_cli_no_configRealm_Id);

    //Peer Table mode Commands
    //peer command

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "peer host WORD realm WORD",
            "Command to add a peer to the peer-table",
            "Peer host-name",
            "Enter the host name",
            "Realm name",
            "Enter the realm name"
           );
    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_peer_Id);
#if DRE
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "ip WORD (|port <1024-65535>) (|secureport <1024-65535>)",
            "Command to configure ip-addr and port/secureport for the peer",
            "Enter ip address of the peer",
            "Port number",
            "Enter port number",
            "TLS Port number",
            "Enter port number for TLS connection"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);

    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "fqdn WORD (|port <1024-65535>) (|secureport <1024-65535>)",
            "Command to configure fqdn and port/secureport for the peer",
            "Enter fully qualified domain name of the peer",
            "Port number",
            "Enter port number",
            "TLS Port number",
            "Enter port number for TLS connection"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
#else
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "ip WORD port <1024-65535>",
            "Command to configure ip-addr and port for the peer",
            "Enter ip address of the peer",
            "Port number",
            "Enter port number"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);

    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "fqdn WORD port <1024-65535>",
            "Command to configure fqdn and port for the peer",
            "Enter fully qualified domain name of the peer",
            "Port number",
            "Enter port number"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
#endif
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "transport SCTP (|ip WORD) (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to configure Peer transport",
            "Transport-type SCTP",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip",
            "Secondary-ip for multi-homing",
            "Enter secondary-ip"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "transport TCP",
            "Command to configure Peer transport",
            "Transport-type TCP"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
#if DRE
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "TLS (enable | disable)",
            "Command to configure TLS option",
            "Enable TLS",
            "Disable TLS"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);

    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "IsDPRDisconnectCauseSupported (enable | disable)",
            "Command to configure DPR Disconnect cause support",
            "Enable DPR Disconnect Cause",
            "Disable DPR Disconnect Cause"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
#endif
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "alt-peer WORD mate (enable | disable) failover (enable | disable) failback (enable | disable)",
            "Command to configure Alternate-peer info",
            "Enter alternate peer name",
            "Redundant mate",
            "Redundant mate enable",
            "Redundant mate disable"
            "Failover",
            "Failover enable",
            "Failover disable",
            "Failback",
            "Failback enable",
            "Failback disable"
           );
    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);

    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "timers watchdog <6-65535> tc <1-65535> expiry <1-65535> busyreconnecttimer <0-65535> dontwanttalktimer <0-65535>",
            "Command to configure peer-timer values",
            "Watchdog timer in secs",
            "Timer range value(in secs)",
            "Termination command duartion in secs",
            "Enter the value(in secs)",
            "Expiry duration in secs",
            "Enter the value(in secs)",
            "Retry timer when DPR rcvd with cause busy in secs",
            "Enter the value(in secs)",
            "Retry timer when DPR rcvd with cause DO_NOT_WANT_TO_TALK_TO_YOU in secs",
            "Enter the value(in secs)"
           );

    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);
    //dictionary command under peer-mode(both for add and modify)
    Add_CLI(ctree, dre_addPeer,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "dictionary-name WORD",
            "Command to associate a dictionary to the peer",
            "Enter dictionary name"
           );

    cli_install(ctree, MODE_CONFIG_PEER, PRIVILEGE_ADMIN, C_cli_peer_Id);

    Add_CLI(ctree, endConfig,
            I_cli_peer_Id,
            M_cli_peer_Id,
            C_cli_peer_Id,
            "commit",
            "Command to save configuration made"
           );

    cli_install(ctree, MODE_ANY, PRIVILEGE_ADMIN, C_cli_peer_Id);

    //delete a row in peerT

    Add_CLI(ctree, no_dre_addPeer,
            I_cli_no_peer_Id,
            M_cli_no_peer_Id,
            C_cli_no_peer_Id,
            "no peer host WORD realm WORD",
            "Command to delete a entry",
            "Peer to be deleted",
            "Host name",
            "Enter the host name  ",
            "Realm name",
            "Enter the realm name  "
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_no_peer_Id);

    Add_CLI(ctree, no_dre_addPeer,
            0,
            0,
            C_cli_no_altpeer_Id,
            "no alt-peer host WORD realm WORD",
            "Command to delete a entry",
            "Alternate peer to be deleted",
            "Host name associated to alt-peer",
            "Enter the host name",
            "Realm name",
            "Enter the realm name "
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_no_altpeer_Id);

    Add_CLI(ctree, no_dre_addPeer,
            0,
            0,
            C_cli_no_peersecondaryip_Id,
            "no secondary-ip host WORD realm WORD ip WORD",
            "Command to delete a entry",
            "Delete secondary-ip",
            "Host-name associated to secondary-ip",
            "Enter the host name",
            "Realm name",
            "Enter the realm name",
            "Secondary-ip to delete",
            "Enter the secondary-ip"
           );
    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_no_peersecondaryip_Id);

    //modify peer command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_modifypeer_Id,
            M_cli_modifypeer_Id,
            C_cli_modifypeer_Id,
            "modify peer host WORD realm WORD",
            "Command to modify configuration",
            "Peer host name",
            "Enter the host name",
            "Realm name of the peer",
            "Enter the realm name"
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_modifypeer_Id);

    // Peer Dictionary commands

    Add_CLI(ctree, cli_int_configDictionary,
            I_cli_deletedictionary_Id,
            M_cli_deletedictionary_Id,
            C_cli_deletedictionary_Id,
            "no dictionary host WORD realm WORD dictionary-name WORD",
            "Delete peer dictionary id",
            "Peer dictionary",
            "Peer hostname",
            "Enter the peer hostname",
            "Peer realm",
            "Enter the realmname",
            "Dictionary-name",
            "Enter dictionary-name to be deleted "
           );

    cli_install(ctree, MODE_DIABASE_PTABLE, PRIVILEGE_ADMIN, C_cli_deletedictionary_Id);

    Add_CLI(ctree,cli_int_showDictionary,
            I_cli_show_dictionary_Id,
            M_cli_show_dictionary_Id,
            C_cli_show_dictionary_Id,
            "show peer-dictionary host WORD realm WORD",
            "Command to view the configuration",
            "Dictionary info for an existing peer",
            "Host-name of the peer",
            "Enter the hostname",
            "Relam-name of the peer",
            "Enter the realm name"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_dictionary_Id);

    // ASF Configurations
    // ADD AS Group Table
#if 0
    Add_CLI(ctree, cli_int_add_asgroup,
            I_cli_add_asgroup_Id,
            M_cli_add_asgroup_Id,
            C_cli_add_asgroup_Id,
            "asgroup group-name WORD priority <1-5> app-type (hosted | external) lb-algo (failover | round-robin | least-loaded | multicast) max-as <1-10>",
            "asgroup configuration",
            "group-name",
            "enter the user-name",
            "priority for the asgroup",
            "enter priority for the group",
            "application type",
            "app type hosted",
            "app type external",
            "load-balancing algorithm",
            "lb-algo failover",
            "lb-algo round-robin",
            "lb-algo least-loaded",
            "lb-algo multicast",
            "maximum number of as per group",
            "eneter the max as"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_add_asgroup_Id);

    // Modify AS Group priority
    Add_CLI(ctree, cli_int_modify_asgroup,
            I_cli_modify_asgroup_Id,
            M_cli_modify_asgroup_Id,
            C_cli_modify_asgroup_Id,
            "modify asgroup group-name WORD priority <1-5>",
            "command to modify  asgroup",
            "as group configuration",
            "as group-name",
            "enter the user-name",
            "as group priority",
            "enter the priority"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_modify_asgroup_Id);


    // Modify AS Group load balancing algorithm.

    Add_CLI(ctree, cli_int_modify_asgroup,
            I_cli_modify_asgroup_Id,
            M_cli_modify_asgroup_Id,
            C_cli_modify_asgroup_Id,
            "modify asgroup group-name WORD lb-algo (failover | round-robin | least-loaded | multicast)",
            "command to modify  asgroup",
            "as group configuration",
            "as group-name",
            "enter the user-name",
            "load-balancing algorithm",
            "lb-algo failover",
            "lb-algo round-robin",
            "lb-algo least-loaded",
            "lb-algo multicast"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_modify_asgroup_Id);

    // Modify  Max AS
    Add_CLI(ctree, cli_int_modify_asgroup,
            I_cli_modify_asgroup_Id,
            M_cli_modify_asgroup_Id,
            C_cli_modify_asgroup_Id,
            "modify asgroup group-name WORD max-as <1-10>",
            "command to modify  asgroup",
            "as group configuration"
            "as group-name",
            "enter the user-name",
            "as group Max as",
            "enter the max as value"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_modify_asgroup_Id);

    //Show asgroup configuration
    Add_CLI(ctree, cli_int_show_asgroup,
            I_cli_show_asgroup_Id,
            M_cli_show_asgroup_Id,
            C_cli_show_asgroup_Id,
            "show asgroup (WORD | all)",
            "Command to view the configuration",
            "asgroup info",
            "asgroup name",
            "all groups"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_show_asgroup_Id);

    //delete asgroup
    Add_CLI(ctree, cli_int_delete_asgroup,
            I_cli_delete_asgroup_Id,
            M_cli_delete_asgroup_Id,
            C_cli_delete_asgroup_Id,
            "no asgroup WORD",
            "delete info",
            "asgroup info",
            "asgroup name"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_delete_asgroup_Id);

    // ASF Timer configuration
    Add_CLI(ctree, cli_int_asf_responseTimeout,
            I_cli_asf_responseTimeout_Id,
            M_cli_asf_responseTimeout_Id,
            C_cli_asf_responseTimeout_Id,
            "as response-timeout <1-100>",
            "asf configuration",
            "response timeout",
            "enter response timeout value"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_asf_responseTimeout_Id);

    //ASF enable/disable
    Add_CLI(ctree, cli_int_asf_config,
            I_cli_asf_config_Id,
            M_cli_asf_config_Id,
            C_cli_asf_config_Id,
            "asf (enable | disable)",
            "asf configuration",
            "enable asf ",
            "disable asf"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_asf_config_Id);


    //ASF termination
    Add_CLI(ctree, cli_int_asf_terminate,
            I_cli_asf_terminate_Id,
            M_cli_asf_terminate_Id,
            C_cli_asf_terminate_Id,
            "terminate asgroup WORD as-instance instance <1-1000>",
            "asf termination command",
            "as group configuration",
            "as group-name",
            "asf instance",
            "instance id",
            "user has to enter instance id  "
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_asf_terminate_Id);

    //ASF termination
    Add_CLI(ctree, cli_int_asf_terminate,
            I_cli_asf_terminate_Id,
            M_cli_asf_terminate_Id,
            C_cli_asf_terminate_Id,
            "terminate asgroup WORD as-instance all",
            "asf termination command",
            "as group configuration",
            "as group-name",
            "asf instance",
            "all asf"
           );

    cli_install(ctree, MODE_ASF_GROUP_TABLE, PRIVILEGE_ADMIN, C_cli_asf_terminate_Id);

#endif

#if 0
    //ERLBF - CLI Commands
    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_set_erlbf_peer_group_Id,
            "peer-group WORD",
            "Command to Configure peer group",
            "Enter the group name for peers"
           );

    cli_install(ctree, MODE_CONFIG_ERLBF, PRIVILEGE_ADMIN, C_cli_set_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_set_erlbf_peer_group_Id,
            "lb-algo (round-robin | imsi-db | weighted | priority) enable-pcrf-binding (true | false) ",
            "Command to apply Load balancing algorithm",
            "Lb-algo round-robin",
            "Lb-algo imsi-db",
            "Lb-algo weighted",
            "Lb-algo priority-based",
            "Enable DRA session binding towards pcrf",
            "True",
            "False"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ERLBF_PEER, PRIVILEGE_ADMIN, C_cli_set_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_set_erlbf_no_peer_group_Id,
            "no peer-group WORD",
            "Command to Delete peer group",
            "Erlbf peer-group",
            "Enter the peer-group name"
           );

    cli_install(ctree, MODE_CONFIG_ERLBF, PRIVILEGE_ADMIN, C_cli_set_erlbf_no_peer_group_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_config,
            0,
            0,
            C_cli_set_erlbf_peer_config_Id,
            "peer-name WORD realm WORD priority <1-5> (|weight <1-64000>)",
            "Command to add peers under peer-group",
            "Enter the peer-name",
            "Peer-realm",
            "Enter the peer-realm",
            "Priority to be assigned to the peer",
            "Enter the priority to be assigned to the peer",
            "Optional: weight to be associated with the peer. Applicable only for peer-groups added with \"weighted\" lb-algo.",
            "Enter the peer weight value in the range specified"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ERLBF_PEER, PRIVILEGE_ADMIN, C_cli_set_erlbf_peer_config_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_modify_erlbf_peer_group_Id,
            "modify peer-group WORD lb-algo (round-robin | imsi-db | weighted | priority)",
            "Command to Modify the peer-group",
            "Group name",
            "Enter the group-name to be modified",
            "Load balancing algorithm to be followed on peer group",
            "Roun-robing load balancing algorithm",
            "IMSI-DB load balancing algorithm",
            "Weighted load balancing algorithm",
            "Priority-based load balancing algorithm"
           );

    cli_install(ctree, MODE_CONFIG_ERLBF, PRIVILEGE_ADMIN, C_cli_modify_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_modify_erlbf_peer_group_Id,
            "modify peer-group WORD enable-pcrf-binding (true | false)",
            "Command to Modify the peer-group",
            "Group name",
            "Enter name of the peer-group to be modified",
            "Enable pcrf binding",
            "True",
            "False"
           );

    cli_install(ctree, MODE_CONFIG_ERLBF, PRIVILEGE_ADMIN, C_cli_modify_erlbf_peer_group_Id);


    Add_CLI(ctree, cli_int_set_erlbf_peer_group,
            0,
            0,
            C_cli_modify_erlbf_peer_group_Id,
            "modify peer-group WORD peer-config",
            "Command to Modify the peer-group",
            "Group name",
            "Enter name of the peer-group to be modified",
            "Modify peer-config details"
           );

    cli_install(ctree, MODE_CONFIG_ERLBF, PRIVILEGE_ADMIN, C_cli_modify_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_config,
            0,
            0,
            C_cli_modify_erlbf_peer_config_Id,
            "modify peer-name WORD realm WORD priority <1-5>",
            "Command to Modify erlbf-peer",
            "Peer-name to be modified in the group",
            "Enter the peer-name",
            "Peer-realm",
            "Enter the peer-realm",
            "Priority to be assigned to the peer",
            "Enter the priority to be assigned to the peer"
           );

    cli_install(ctree, MODE_CONFIG_MOD_ERLBF_PEER, PRIVILEGE_ADMIN, C_cli_modify_erlbf_peer_config_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_config,
            0,
            0,
            C_cli_modify_erlbf_peer_config_Id,
            "modify peer-name WORD realm WORD weight <1-64000>",
            "Command to Modify erlbf-peer",
            "Peer-name to be modified in the group",
            "Enter the peer-name",
            "Peer-realm",
            "Enter the peer-realm",
            "Weight to be associated with the peer",
            "Enter the peer weight in the range specified"
           );

    cli_install(ctree, MODE_CONFIG_MOD_ERLBF_PEER, PRIVILEGE_ADMIN, C_cli_modify_erlbf_peer_config_Id);

    Add_CLI(ctree, cli_int_set_erlbf_peer_config,
            0,
            0,
            C_cli_set_erlbf_no_peer_config_Id,
            "no peer-name WORD realm WORD",
            "Command to delete peer under peer-goup",
            "Peer-name to be deleted from the group",
            "Enter the peer-name",
            "Peer-realm",
            "Enter the peer-realm"
           );

    cli_install(ctree, MODE_CONFIG_MOD_ERLBF_PEER, PRIVILEGE_ADMIN, C_cli_set_erlbf_no_peer_config_Id);

    Add_CLI(ctree, cli_int_show_peer_group,
            0,
            0,
            C_cli_show_all_erlbf_peer_group_Id,
            "show peer-group-config all",
            "Command to view the configuration",
            "Peer-group details",
            "Show all peer-group details"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_show_peer_group,
            0,
            0,
            C_cli_show_erlbf_peer_group_Id,
            "show peer-group-config group WORD",
            "Command to view the configuration",
            "Peer-group details",
            "Keyword group-name",
            "Enter the group name"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_erlbf_peer_group_Id);

    Add_CLI(ctree, cli_int_show_peer_group,
            0,
            0,
            C_cli_show_erlbf_peer_group_Id,
            "show peer-group-peers group WORD",
            "Command to view the configuration",
            "Peers under peer-group",
            "Keyword group-name",
            "Enter the group name"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_erlbf_peer_group_peers_Id);

    Add_CLI(ctree, cli_int_setLogging,
            0,
            0,
            C_cli_set_log_level_Id,
            "log-level comp (dre | dtf | asf | cmgr | cli | erlbf | avamgr | all) level (DEBUG | INFO |NOTICE | WARNING |ERROR | CRITICAL)",
            "Command to set log level",
            "Component name",
            "Dre component",
            "Dtf component",
            "Asf component",
            "Cmgr component",
            "Cli component",
            "Erlbf component",
            "Avamgr component",
            "All components in alphabetical order",
            "Log-level",
            "To DEBUG level",
            "To INFO level",
            "To NOTICE level",
            "To WARNING level",
            "To ERROR level",
            "To CRITICAL level"
                );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_set_log_level_Id);
#endif
    Add_CLI(ctree, cli_int_setLogging,
            0,
            0,
            C_cli_set_log_level_Id,
            "log-level comp (avamgr | cmgr | cli | iwf | all) level (DEBUG | INFO |NOTICE | WARNING |ERROR | CRITICAL)",
            "Command to set log level",
            "Component name",
            "Avamgr component",
            "Cmgr component",
            "Cli component",
            "Iwf component",
            "All components in alphabetical order",
            "Log-level",
            "To DEBUG level",
            "To INFO level",
            "To NOTICE level",
            "To WARNING level",
            "To ERROR level",
            "To CRITICAL level"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_set_log_level_Id);

    Add_CLI(ctree, cli_int_showLogging,
            0,
            0,
            C_cli_show_log_config_Id,
            "show log-config (avamgr | cmgr | cli | iwf | all)",
            "Command to view the configuration",
            "Logging configuration",
            "Avamgr component",
            "Cmgr component",
            "Cli component",
            "Iwf component",
            "All components"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_log_config_Id);

#if 0
    Add_CLI(ctree, cli_int_setLogging,
            0,
            0,
            C_cli_set_log_channel_Id,
            "log-channel comp (dre | dtf | asf | erlbf) channel (syslog | console | file)",
            "set log channel",
            "component name",
            "dre component",
            "dtf component",
            "asf component",
            "erlbf component",
            "channel name",
            "syslog channel",
            "console channel",
            "file-name channel"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_set_log_channel_Id);

    Add_CLI(ctree, cli_int_showLogging,
            0,
            0,
            C_cli_show_log_config_Id,
            "show log-config (cmgr | cli | dre | dtf | asf | erlbf | avamgr | webagent | all)",
            "Command to view the configuration",
            "Logging configuration",
            "Cmgr component",
            "Cli component",
            "Dre component",
            "Dtf component",
            "Asf component",
            "Erlbf component",
            "Avamgr component",
            "WebAgent component",
            "All components"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_log_config_Id);

#endif

    Add_CLI(ctree, cli_int_showLoadedDictionary,
            I_cli_show_loaded_dictionary_Id,
            M_cli_show_loaded_dictionary_Id,
            C_cli_show_loaded_dictionary_Id,
            "show dictionaries",
            "Command to view the configuration",
            "Supported dictionaries Information"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_loaded_dictionary_Id);

#if 0
    Add_CLI(ctree, cli_int_showVersion,
            0,
            0,
            C_cli_show_version_Id,
            "show version",
            "Command to view the configuration",
            "Installed DRE version"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_version_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_general_config_Id,
            M_cli_general_config_Id,
            C_cli_general_config_Id,
            "general-config",
            "Command to set cli to General configuration mode"
           );
    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_general_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_sctp_config_Id,
            M_cli_sctp_config_Id,
            C_cli_sctp_config_Id,
            "sctp-config",
            "Command to set cli to sctp configuration mode"
           );
    cli_install(ctree, MODE_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_sctp_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_tls_config_Id,
            M_cli_tls_config_Id,
            C_cli_tls_config_Id,
            "tls-config",
            "Command to set cli to tls configuration mode"
           );
    cli_install(ctree, MODE_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_tls_config_Id);

    Add_CLI(ctree, cli_int_tlsconfig,
            I_cli_tlsconfig_Id,
            M_cli_tlsconfig_Id,
            C_cli_tlsconfig_Id,
            "tlsconfig crl-verification (enable | disable)",
            "Command to do tls configuration",
            "Crl verification",
            "Enable crl-verification",
            "Disable crl-verification"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_tlsconfig_Id);

    Add_CLI(ctree, cli_int_tlsconfig,
            I_cli_tlsconfig_Id,
            M_cli_tlsconfig_Id,
            C_cli_tlsconfig_Id,
            "tlsconfig id-verification (enable | disable)",
            "Command id-verification",
            "Identity verification",
            "Enable id-verification",
            "Disable id-verification"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_tlsconfig_Id);

    Add_CLI(ctree, cli_int_tlsciphersuite,
            I_cli_tlssuite_Id,
            M_cli_tlssuite_Id,
            C_cli_tlssuite_Id,
            "tls-cipher-suite cipher-suite WORD (enable | disable)",
            "Command to do tls-cipher-suite configuration",
            "Cipher-suite key-word",
            "Enter the cipher-suite name",
            "Enable cipher-suite",
            "Disable cipher-suite"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_tlssuite_Id);

    Add_CLI(ctree, cli_int_trustedcaconfig,
            I_cli_trustedca_Id,
            M_cli_trustedca_Id,
            C_cli_trustedca_Id,
            "trusted-ca ca-file WORD (|crl-file WORD)",
            "Command to add trusted-ca configuration",
            "Ca-file keyword",
            "Enter ca file name",
            "Crl-file keyword",
            "Enter crl file name"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_trustedca_Id);

    Add_CLI(ctree, cli_int_trustedcaconfig,
            I_cli_trustedca_Id,
            M_cli_trustedca_Id,
            C_cli_trustedca_Id,
            "modify trusted-ca ca-file WORD crl-file WORD",
            "Command to modify the configuration",
            "Trusted-ca configuration",
            "Ca-file keyword",
            "Enter ca file name",
            "Crl-file keyword",
            "Enter crl file name"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_trustedca_Id);

    Add_CLI(ctree, cli_int_trustedcaconfig,
            I_cli_notrustedca_Id,
            M_cli_notrustedca_Id,
            C_cli_notrustedca_Id,
            "no crl-file ca-file WORD",
            "Command to delete the configuration",
            "Remove crl-file association from a trusted-ca",
            "Ca-file keyword",
            "Enter ca-file name from which association should be removed"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_notrustedca_Id);

    Add_CLI(ctree, cli_int_trustedcaconfig,
            I_cli_trustedca_Id,
            M_cli_trustedca_Id,
            C_cli_trustedca_Id,
            "no trusted-ca ca-file WORD",
            "Delete command",
            "Trusted-ca configuration",
            "Ca-file keyword",
            "Enter ca file name"
           );
    cli_install(ctree, MODE_TLS_CONFIG,PRIVILEGE_ADMIN, C_cli_trustedca_Id);

    Add_CLI(ctree, cli_int_peerIpcheck,
            I_cli_peeripcheck_Id,
            M_cli_peeripcheck_Id,
            C_cli_peeripcheck_Id,
            "peer-ip-check (enable | disable)",
            "Command to configure peer-ip-check",
            "Enable ip-check",
            "Disable ip-check"
           );
    cli_install(ctree, MODE_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_peeripcheck_Id);

    Add_CLI(ctree, cli_int_predectiveloopdetection,
            I_cli_predectiveloopdetection_Id,
            M_cli_predectiveloopdetection_Id,
            C_cli_predectiveloopdetection_Id,
            "predictive-loop-detection (enable | disable)",
            "Command to configure predictive-loop-detection",
            "Enable predictive-loop-detection",
            "Disable predictive-loop-detection"
           );
    cli_install(ctree, MODE_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_predectiveloopdetection_Id);

    Add_CLI(ctree, cli_int_snaptrsupport,
            I_cli_snaptrsupport_Id,
            M_cli_snaptrsupport_Id,
            C_cli_snaptrsupport_Id,
            "snaptr-support (enable | disable)",
            "Command to configure snaptr-support",
            "Enable snaptr-support",
            "Disable snaptr-support"
           );
    cli_install(ctree, MODE_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_snaptrsupport_Id);

    Add_CLI(ctree, cli_int_sctpconfig,
            I_cli_sctpconfig_Id,
            M_cli_sctpconfig_Id,
            C_cli_sctpconfig_Id,
            "heart-beat (enable | disable) (|heart-beat-timeout <0-65535>)",
            "Command to set heart-beat configuration",
            "Enable heart-beat",
            "Disable heart-beat",
            "Key-word hear beat timeout",
            "Enter the timeout value in milliseconds"
           );
    cli_install(ctree, MODE_SCTP_CONFIG, PRIVILEGE_ADMIN, C_cli_sctpconfig_Id);

    Add_CLI(ctree, cli_int_sctpconfig,
            I_cli_sctpconfig_Id,
            M_cli_sctpconfig_Id,
            C_cli_sctpconfig_Id,
            "init-timeout <0-65535> max-attempts <1-50> pathfail-retrycount <1-50>",
            "Command to configure other SCTP configurations",
            "Enter init timeout value in milliseconds",
            "Maximum init attempts",
            "Enter the value",
            "Path failure retry count",
            "Enter the value"
           );
    cli_install(ctree, MODE_SCTP_CONFIG, PRIVILEGE_ADMIN, C_cli_sctpconfig_Id);

    Add_CLI(ctree, cli_int_sctpconfig,
            I_cli_sctpconfig_Id,
            M_cli_sctpconfig_Id,
            C_cli_sctpconfig_Id,
            "rto-initial <0-65535> rto-min <0-65535> rto-max <0-65535>",
            "Command to set retransmission time configurations",
            "Enter the rto-initial value in milliseconds",
            "Key-word rto minimum",
            "Enter the value in milliseconds",
            "Key-word rto maximum",
            "Enter the value in milliseconds"
           );
    cli_install(ctree, MODE_SCTP_CONFIG, PRIVILEGE_ADMIN, C_cli_sctpconfig_Id);

    Add_CLI(ctree, cli_int_showgeneralconfig,
            I_cli_showgeneralconfig_Id,
            M_cli_showgeneralconfig_Id,
            C_cli_showgeneralconfig_Id,
            "show sctp-config",
            "Command to view the configuration",
            "Sctp configuration"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showgeneralconfig_Id);

    Add_CLI(ctree, cli_int_showgeneralconfig,
            I_cli_showgeneralconfig_Id,
            M_cli_showgeneralconfig_Id,
            C_cli_showgeneralconfig_Id,
            "show tls-config",
            "Command to view the configuration",
            "Tls configuration"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showgeneralconfig_Id);

    Add_CLI(ctree, cli_int_showgeneralconfig,
            I_cli_showgeneralconfig_Id,
            M_cli_showgeneralconfig_Id,
            C_cli_showgeneralconfig_Id,
            "show trusted-ca-config",
            "Command to view the configuration",
            "Trusted ca configuration"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showgeneralconfig_Id);

    Add_CLI(ctree, cli_int_showgeneralconfig,
            I_cli_showgeneralconfig_Id,
            M_cli_showgeneralconfig_Id,
            C_cli_showgeneralconfig_Id,
            "show cipher-suite-config",
            "Command to view the configuration",
            "Cipher suite configuration"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showgeneralconfig_Id);

    Add_CLI(ctree, cli_int_showgeneralconfig,
            I_cli_showgeneralconfig_Id,
            M_cli_showgeneralconfig_Id,
            C_cli_showgeneralconfig_Id,
            "show general-config",
            "Command to view the configuration",
            "General configuration"
           );
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_showgeneralconfig_Id);
    //DTF-TRANSFORM CLI COMMANDS

    Add_CLI(ctree, cli_int_loadDictionary,
            I_cli_load_dictionary_Id,
            M_cli_load_dictionary_Id,
            C_cli_load_dictionary_Id,
            "dictionary load dictionary-name WORD",
            "dictinary load command",
            "load dictionary",
            "dictionary-name to be loaded",
            "enter the dictionary-name"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_load_dictionary_Id);

    Add_CLI(ctree, cli_int_loadDictionary,
            I_cli_unload_dictionary_Id,
            M_cli_unload_dictionary_Id,
            C_cli_unload_dictionary_Id,
            "no dictionary dictionary-name WORD",
            "dictinary delete command",
            "delete dictionary",
            "dictionary-name to be deleted",
            "enter the dictionary-name"
           );

    cli_install(ctree, MODE_CONFIG_DIABASE, PRIVILEGE_ADMIN, C_cli_unload_dictionary_Id);


    Add_CLI(ctree, cli_int_loadTransformplugin,
            I_cli_load_transformplugin_Id,
            M_cli_load_transformplugin_Id,
            C_cli_load_transformplugin_Id,
            "plugin plugin-name WORD dictionary-1 WORD dictionary-2 WORD config-file WORD",
            "plugin load command",
            "plugin-name to be loaded",
            "enter the plugin-name",
            "dictionary-name from which plugin to be loaded",
            "enter the dictionary-name",
            "dictionary-name to which plugin to be loaded",
            "enter the dictionary-name",
            "config-file used for plugin",
            "enter the config-file name"
           );

    cli_install(ctree, MODE_CONFIG_TRANSFORM, PRIVILEGE_ADMIN, C_cli_load_transformplugin_Id);


    Add_CLI(ctree, cli_int_loadTransformplugin,
            I_cli_unload_transformplugin_Id,
            M_cli_unload_transformplugin_Id,
            C_cli_unload_transformplugin_Id,
            "no plugin plugin-name WORD",
            "plugin delete command",
            "delete plugin",
            "plugin-name to be deleted",
            "enter the plugin-name"
           );

    cli_install(ctree, MODE_CONFIG_TRANSFORM, PRIVILEGE_ADMIN, C_cli_unload_transformplugin_Id);

    Add_CLI(ctree, cli_int_showLoadedDictionary,
            I_cli_show_loaded_dictionary_Id,
            M_cli_show_loaded_dictionary_Id,
            C_cli_show_loaded_dictionary_Id,
            "show dictionary dictionary-name (WORD | all)",
            "show Info",
            "dictionary Info",
            "dictionary-name to be shown",
            "enter the dictionary-name",
            "show all"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_show_loaded_dictionary_Id);

    Add_CLI(ctree, cli_int_showLoadedTransformPlugin,
            I_cli_show_loaded_transformplugin_Id,
            M_cli_show_loaded_transformplugin_Id,
            C_cli_show_loaded_transformplugin_Id,
            "show transform-plugin plugin-name (WORD | all)",
            "show Info",
            "transform-plugin Info",
            "plugin-name to be shown",
            "enter the plugin-name",
            "show all"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_show_loaded_transformplugin_Id);
#endif
    return 0;
}
