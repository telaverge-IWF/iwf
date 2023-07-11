
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

int iwf_cli_init(struct cli_def *ctree)
{

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "iwf",
            "Command to set cli to IWF configuration mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "sigtran",
            "Command to set cli to sigtran configuration mode"
           );

    cli_install(ctree, MODE_CONFIG, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "SCTP",
            "Command to set cli to SIGTRAN-SCTP configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "M3UA",
            "Command to set cli to SIGTRAN-M3UA configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
#if 0
    //NOTE: Currently Not Used
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "local", 
            "Command to add LocalHost Configuration"            
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
#endif
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify local",
            "Command to modify the configuration",
            "Modify Local Configuration"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "pointcode <1-65535>", 
            "Command to configure PointCode and NI"
            "Enter the PointCode for LocalHost"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "tcap-invoke-timer <1-65535>",
            "Command to configure Tcap Invoke Timer",
            "Enter timer value(in sec)"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-gt-use-from-config (Yes | No)",
            "Command to configure local Gt to use from config",
            "Yes - to use from config",
            "No - not to use from config"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "hostname1 WORD asp-id1 <1-65535>",
            "Command to configure HostName for node1 in HA setup",
            "Enter the hostname",
            "AspId for node1",
            "Enter the AspId"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "hostname2 WORD asp-id2 <1-65535>",
            "Command to configure HostName for node2 in HA setup",
            "Enter the hostname",
            "AspId for node2",
            "Enter the AspId"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);
#if 0
    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "use-sccp-cdpa-from-incomming-msg (Yes | No)",
            "Command to configure usage of sccp calledparty address",
            "Yes - to use from incomming msg",
            "No - not to use incomming msg"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);
#endif
    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "include-pc (Yes | No)",
            "Command to include PC for GT Routing",
            "Yes - to include PC",
            "No - not to include PC"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);
#if 0
    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "include-ssn (yes | no)",
            "Command to include SSN for GT Routing",
            "Yes - to include SSN",
            "No - not to include SSN"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);
#endif
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "local-SCCP routing-indicator (PC-SSN | GT)",
            "Command to configure SCCP Configuration",
            "RoutingIndicator for SCCP",
            "Routing Indicator PC-SSN",
            "Routing Indicator GT"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-ssn (HLR | CAP | SGSN)",
            "Command to configure ssn",
            "SSN-6 for HLR",
            "SSN-146 for CAP",
            "SSN-149 for SGSN"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL_PCSSN, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "selection-criteria (MCC-MNC | SERVICE-KEY | SERVICE-KEY-AND-MCC-MNC | GTT | GTT-AND-SERVICE-KEY | GTT-AND-MCC-MNC | IMSI-PREFIX-AND-SERVICE-KEY)",
            "Command to configure selection criteria",
            "selection criteria MCC-MNC",
            "selection criteria SERVICE-KEY",
            "selection criteria SERVICE-KEY and MCC-MNC",
            "selection criteria GTT",
            "selection criteria GTT and SERVICE-KEY",
            "selection criteria GTT and MCC-MNC",
            "selection criteria IMSI-PREFIX and SERVICE-KEY"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-GTI-1 nature-of-addr-indi <0-127> global-title-addr-info WORD",
            "Command to configure GTI-1 configuration",
            "Nature Of Address Indicator for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL_GT, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-GTI-2 trans-type <0-255> global-title-addr-info WORD",
            "Command to configure GTI-2 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL_GT, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-GTI-3 trans-type <0-255> num-plan <0-15> encode-scheme <0-15> global-title-addr-info WORD",
            "Command to configure GTI-3 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Numbering plan for GT",
            "Enter the value",
            "Encoding Scheme for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL_GT, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "local-GTI-4 trans-type <0-255> num-plan <0-15> encode-scheme <0-15> nature-of-addr-indi <0-127> global-title-addr-info WORD",
            "Command to configure GTI-4 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Numbering plan for GT",
            "Enter the value",
            "Encoding Scheme for GT",
            "Enter the value",
            "Nature of Addr Indicator",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information"
           );

    cli_install(ctree, MODE_CONFIG_LOCAL_GT, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_local_config,
            0,
            0,
            C_cli_localconfig_Id,
            "no local-ssn (HLR | CAP | SGSN)",
            "Command to delete the configuration",
            "Remove SSN association with local-host",
            "SSN-6 for HLR",
            "SSN-146 for CAP",
            "SSN-149 for SGSN"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_localconfig_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "sctp-end-point WORD ip WORD port <1024-65535>",
            "Command to add SCTP-End-Point configuration",
            "Enter the name of SCTP End Point",
            "Primary Ip address of SCTP End Point",
            "Enter the Primary Ip address",
            "Port of SCTP End Point",
            "Enter the port number"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_sctp_endpoint_config,
            0,
            0,
            C_cli_sctp_endpoint_Id,
            "multi-Homing ip WORD (| ip WORD) (| ip WORD) (| ip WORD)",
            "Command to configure Multi-Homing Ip's for the EndPoint",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr"
           );

    cli_install(ctree, MODE_CONFIG_ADD_SCTP_ENDPOINT, PRIVILEGE_ADMIN, C_cli_sctp_endpoint_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify sctp-end-point WORD",
            "Command to Modify the configuration",
            "Modify SCTP-End-Point configuration",
            "Enter the name of SCTP End Point"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_sctp_endpoint_config,
            0,
            0,
            C_cli_sctp_endpoint_Id,
            "Ip WORD port <1024-65535>",
            "Command to modify Ip address and Port of SCTP End Point",
            "Enter the Ip address",
            "Port of SCTP End Point",
            "Enter the port number"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_SCTP_ENDPOINT, PRIVILEGE_ADMIN, C_cli_sctp_endpoint_Id);
 
    Add_CLI(ctree, cli_int_sctp_endpoint_config,
            0,
            0,
            C_cli_sctp_endpoint_Id,
            "multi-homing ip WORD (| ip WORD) (| ip WORD) (| ip WORD)",
            "Command to configure Multi-Homing Ip's for the EndPoint",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_SCTP_ENDPOINT, PRIVILEGE_ADMIN, C_cli_sctp_endpoint_Id);

    Add_CLI(ctree, cli_int_sctp_endpoint_config,
            0,
            0,
            C_cli_sctp_endpoint_Id,
            "no sctp-end-point WORD",
            "Command to delete the configuration",
            "Delete SCTP-End-Point configuration",
            "Enter the name of SCTP End Point"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_sctp_endpoint_Id);

    Add_CLI(ctree, cli_int_sigtran_multihoming_config,
            0,
            0,
            C_cli_delete_sctpendpoint_multihoming_Id,
            "no multi-homing-ip sctp-end-point WORD ip WORD (|ip WORD) (|ip WORD) (|ip WORD)",
            "Command to delete the configuration",
            "Delete MultiHoming Ip's of an Assocaition",
            "Enter the Association name",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr",
            "Multi-Homing Ip",
            "Enter the Ip-addr"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_delete_sctpendpoint_multihoming_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "sctp-profile WORD",
            "Command to add SCTP Profile Configuration",
            "Enter the SCTP Profile name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify sctp-profile WORD",
            "Command to modify the configuration",
            "Modify SCTP Profile Configuration",
            "Enter the SCTP Profile name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "heartbeat (enable | disable) heart-beat-timeout <1-65535>",
            "Command to configure heart-beat related configuration",
            "Enable the heart-beat",
            "Disable the heart-beat",
            "Heart-beat-timeout",
            "Enter the timeout(in sec)"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "rto-Initial <0-65535> rto-min <0-65535> rto-max <0-65535> path-max-retransmit <0-65535>",
            "Command to set retransmission time configurations",
            "Enter the rto-initial value in milliseconds",
            "Key-word rto minimum",
            "Enter the value in milliseconds",
            "Key-word rto maximum",
            "Enter the value in milliseconds",
            "Key-word path max retransmission",
            "Enter the value in milliseconds"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "init-time-out <0-65535> reconnect-time-out <0-65535>",
            "Command to set different timeout configurations",
            "Enter the init-timeout in milliseconds",
            "Key-word reconnect time out",
            "Enter the value in milliseconds"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

#if 0
    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "init-time-out <0-65535> recv-time-out <0-65535> shutdown-time-out <0-65535> reconnect-time-out <0-65535>",
            "Command to set different timeout configurations",
            "Enter the init-timeout in milliseconds",
            "Key-word receive time out",
            "Enter the receive time out value in milliseconds",
            "Key-word shutdown time out",
            "Enter the value in milliseconds",
            "Key-word reconnect time out",
            "Enter the value in milliseconds"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "send-buff-size <0-65535> recv-buff-size <0-65535>",
            "Command to send and receive buffer size",
            "Enter the send buffer size value",
            "Key-word receive buffer size",
            "Enter the receive buffer size value"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);
#endif
    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "cookie-life <0-65535> sack-delay <0-500>",
            "Command to set cookie life and sack delay",
            "Enter the cookie life value in seconds",
            "Key-word sack delay",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "max-instreams <0-65535> num-of-outstreams <0-65535> max-init-attempts <1-50> assoc-max-attempts <1-50>",
            "Command to set max in-streams, outstreams, init-attempts and assoc-max-attempts",
            "Enter the max instream value",
            "Key-word num of out-streams",
            "Enter the value",
            "Maximum init attempts",
            "Enter the value",
            "Maximum Retransmission attempts for an Association",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_SCTP_PROFILE, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_sctp_profile_config,
            0,
            0,
            C_cli_sctp_profile_Id,
            "no sctp-profile WORD",
            "Command to delete the configuration",
            "Delete SCTP Profile configuration",
            "Enter the SCTP Profile name to be deleted"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_sctp_profile_Id);

    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "association WORD association-set WORD local-end-point WORD remote-end-point WORD asp-id <1-65535> (| sctp-Profile WORD)",
            "Command to add the association configuration",
            "Enter the Association name",
            "Association-Set to be assigned",
            "Enter the Association-Set Name",
            "Local SCTP End Point to be assigned",
            "Enter Local SCTP EndPoint Name",
            "Remote SCTP End Point to be assigned",
            "Enter Remote SCTP EndPoint Name",
            "AspId to be associated",
            "Enter the AspId value",
            "SCTP-Profile to be assigned",
            "Enter the SCTP-Profile Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_assocation_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify association WORD",
            "Command to modify the configuration",
            "Modify the Association",
            "Enter the Association name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "Sctp-Profile WORD",
            "Command to modify SCTP-Profile for an Association",
            "Enter the sctp profile name"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION, PRIVILEGE_ADMIN, C_cli_assocation_Id);

    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "local-end-point WORD",
            "Command to modify Local SCTP End Point for an Association",
            "Enter the Local SCTP End Point"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION, PRIVILEGE_ADMIN, C_cli_assocation_Id);

    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "remote-end-point WORD",
            "Command to modify Remote SCTP End Point for an Association",
            "Enter the Remote SCTP End Point"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION, PRIVILEGE_ADMIN, C_cli_assocation_Id);

    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "asp-id <1-65535>",
            "Command to configure ASP-Id",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);
    
    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "association-set WORD",
            "Command to modify Association-Set for an Association",
            "Enter the Association-set name"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION, PRIVILEGE_ADMIN, C_cli_assocation_Id);
#if 0
    Add_CLI(ctree, cli_int_activate_association,
            0,
            0,
            C_cli_activate_association_Id,
            "assoc-state WORD (enable | disable)",
            "Command to Enable or Disable Association",
            "Enter the Association Name",
            "Enable the Association to allow traffic",
            "Disable the Association to stop traffic"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_activate_association_Id);
#endif
    Add_CLI(ctree, cli_int_association_config,
            0,
            0,
            C_cli_assocation_Id,
            "no association WORD",
            "Command to delete the configuration",
            "Delete the Assocaition",
            "Enter the Association name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_SCTP, PRIVILEGE_ADMIN, C_cli_assocation_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "assoc-set WORD",
            "Command to add the association-set configuration",
            "Enter the Association-Set name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "adj-pointcode <1-65535> ni (NATIONAL | INTERNATIONAL)",
            "Command to configure Adjacent-PointCode and NI",
            "Enter the pointcode value",
            "Network Indicator",
            "Network Indicator - NATIONAL",
            "Network Indicator - INTERNATIONAL"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "routing-Context <1-65535>",
            "Command to configure Routing Context",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "traffic-mode (overRideMode | loadShareMode)",
            "Command to configure traffic-mode",
            "Traffic-Mode to be supported",
            "Over Ride Mode of Traffic",
            "Load Sharing Mode of Traffic"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "isMember (Yes | No)",
            "Command to configure IsMember",
            "IsMember - yes",
            "IsMember - no"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "homeip WORD",
            "Command to configure HomeIp for IPSP Mode",
            "Enter the Home Ip address"
           );

    cli_install(ctree, MODE_CONFIG_ADD_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify assoc-set WORD",
            "Command to modify the configuration",
            "Modify the Association-Set",
            "Enter the Association-Set name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "adj-Pointcode <1-65535> ni (NATIONAL | INTERNATIONAL)",
            "Command to configure Adjacent-PointCode and NI",
            "Enter the pointcode value",
            "Network Indicator",
            "Network Indicator - NATIONAL",
            "Network Indicator - INTERNATIONAL"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);
    
    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "asp-Id <1-65535>",
            "Command to configure ASP-Id",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);
    
    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "traffic-Mode (overRideMode | loadShareMode)",
            "Command to configure traffic-mode",
            "Traffic-Mode to be supported",
            "Over Ride Mode of Traffic",
            "Load Sharing Mode of Traffic"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);
 
    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "IsMember (Yes | No)",
            "Command to configure IsMember",
            "IsMember - yes",
            "IsMember - no"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "homeIp WORD",
            "Command to configure HomeIp for IPSP Mode",
            "Enter the Home Ip address"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "routing-context <1-65535>",
            "Command to configure Routing Context",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_ASSOCIATION_SET, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_ual_config,
            0,
            0,
            C_cli_ual_set_Id,
            "ual-config ack-timer <1-65535> sigtran-mode (ASP | IPSP)",
            "Command to add UAL Configuration",
            "Ack-Timer",
            "Enter the value(in sec)",
            "Sigtran Mode",
            "ASP - mode",
            "IPSP - mode"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_ual_set_Id);

    Add_CLI(ctree, cli_int_ual_config,
            0,
            0,
            C_cli_ual_set_Id,
            "modify ual-config ack-timer <1-65535> sigtran-mode (ASP | IPSP)",
            "Command to modify the Configuration",
            "Modify UAL Configuration",
            "Ack-Timer",
            "Enter the value(in sec)",
            "Sigtran Mode",
            "ASP - mode",
            "IPSP - mode"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_ual_set_Id);

#if 0
    Add_CLI(ctree, cli_int_activate_associationSet,
            0,
            0,
            C_cli_activate_associationSet_Id,
            "associationSet-state WORD (enable | disable)",
            "Command to Enable or Disable Association",
            "Enter the Association Name",
            "Enable the Association to allow traffic",
            "Disable the Association to stop traffic"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_activate_associationSet_Id);
#endif
    Add_CLI(ctree, cli_int_associationset_config,
            0,
            0,
            C_cli_assocation_set_Id,
            "no assoc-set WORD",
            "Command to delete the configuration",
            "Delete the Assocaition-Set",
            "Enter the Association-Set name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_assocation_set_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "destination WORD",
            "Command to add Destination Configuration",
            "Enter the Destination Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify destination WORD",
            "Command to Modify the Configuration",
            "Modify the Destination Configuration",
            "Enter the Destination Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "pointCode <1-65535> ni (NATIONAL | INTERNATIONAL)",
            "Command to configure PointCode and NI of Destination",
            "Enter the Pointcode Value",
            "Network Indicator",
            "Network Indicator - NATIONAL",
            "Network Indicator - INTERNATIONAL"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "dest-SCCP routing-indicator (PC-SSN | GT)", 
            "Command to configure SCCP Configuration",
            "RoutingIndicator for SCCP",
            "Routing Indicator PC-SSN",
            "Routing Indicator GT"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "dest-ssn (HLR | CAP | SGSN)",
            "Command to configure ssn Configuration",
            "SSN-6 for HLR",
            "SSN-146 for CAP",
            "SSN-149 for SGSN"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION_PCSSN, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "dest-GTI-1 nature-of-addr-indi <0-127> global-title-addr-info WORD dest-ssn (CAP | SGSN | HLR)",
            "Command to configure GTI-1 configuration",
            "Nature Of Address Indicator for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION_GT, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "dest-GTI-2 trans-type <0-255> global-title-addr-info WORD dest-ssn (CAP | SGSN | HLR)",
            "Command to configure GTI-2 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION_GT, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "dest-GTI-3 trans-type <0-255> num-plan <0-15> encode-scheme <0-15> global-title-addr-info WORD dest-ssn (CAP | SGSN | HLR)",
            "Command to configure GTI-3 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Numbering plan for GT",
            "Enter the value",
            "Encoding Scheme for GT",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION_GT, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "dest-GTI-4 trans-type <0-255> num-plan <0-15> encode-scheme <0-15> nature-of-addr-indi <0-127> global-title-addr-info WORD dest-ssn (CAP | SGSN | HLR)",
            "Command to configure GTI-4 configuration",
            "Translation Type for GT",
            "Enter the value",
            "Numbering plan for GT",
            "Enter the value",
            "Encoding Scheme for GT",
            "Enter the value",
            "Nature of Addr Indicator",
            "Enter the value",
            "Global Title Address Info for GT",
            "Enter the Address Information",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_CONFIG_DESTINATION_GT, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_destination_config,
            0,
            0,
            C_cli_destination_config_Id,
            "no destination WORD",
            "Command to delete the configuration",
            "Delete the Destination",
            "Enter the Destination Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN, PRIVILEGE_ADMIN, C_cli_destination_config_Id);

    Add_CLI(ctree, cli_int_remoteroute_config,
            0,
            0,
            C_cli_remoteroute_config_Id,
            "remote-route WORD dest WORD assoc-Set WORD priority <1-100>",
            "Command to add Remote Route Configuration",
            "Enter the Remote Route Name",
            "Destination to be associated",
            "Enter the destination name",
            "Association-Set to be associated",
            "Enter the Association-Set name",
            "Priority to be assigned",
            "Enter the priority"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify remote-route WORD",
            "Command to modify the configuration",
            "Modify the RemoteRoute configuration",
            "Enter the Remote Route Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_remoteroute_config,
            0,
            0,
            C_cli_remoteroute_config_Id,
            "dest WORD",
            "Command to associate destination to Remote Route",
            "Enter the destination name"
           );

    cli_install(ctree, MODE_CONFIG_REMOTEROUTE, PRIVILEGE_ADMIN, C_cli_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_remoteroute_config,
            0,
            0,
            C_cli_remoteroute_config_Id,
            "assoc-Set WORD",
            "Command to associate association-set to Remote Route",
            "Enter the association-set name"
           );

    cli_install(ctree, MODE_CONFIG_REMOTEROUTE, PRIVILEGE_ADMIN, C_cli_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_remoteroute_config,
            0,
            0,
            C_cli_remoteroute_config_Id,
            "priority <1-100>",
            "Command to change priority of Remote Route",
            "Enter the priority value"
           );

    cli_install(ctree, MODE_CONFIG_REMOTEROUTE, PRIVILEGE_ADMIN, C_cli_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_remoteroute_config,
            0,
            0,
            C_cli_remoteroute_config_Id,
            "no remote-route WORD",
            "Command to delete the configuration",
            "Delete the RemoteRoute configuration",
            "Enter the Remote Route Name"
           );

    cli_install(ctree, MODE_CONFIG_SIGTRAN_M3UA, PRIVILEGE_ADMIN, C_cli_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "trans-rule WORD trans-type SS7 translator (MAP-s6a | CAP-Ro | CAP-Ro-TSL)",
            "Command to add translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator MAP-s6a",
            "Translator CAP-Ro",
            "Translator CAP-Ro-Transatel"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "trans-rule WORD trans-type DIAMETER translator s6a-MAP",
            "Command to add translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator s6a-MAP"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "trans-rule WORD trans-type HTTP translator (s6a-MAP | MAP-s6a | CAP-Ro | CAP-Ro-TSL)",
            "Command to add translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator s6a-MAP",
            "Translator MAP-s6a",
            "Translator CAP-Ro",
            "Translator CAP-Ro-Transatel"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify trans-rule WORD trans-type SS7 translator (MAP-s6a | CAP-Ro | CAP-Ro-TSL)",
            "Command to Modify the Translator Rule Configuration",
            "Modify the translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator MAP-s6a",
            "Translator CAP-Ro",
            "Translator CAP-Ro-Transatel"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify trans-rule WORD trans-type DIAMETER translator s6a-MAP",
            "Command to Modify the Translator Rule Configuration",
            "Modify the translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator s6a-MAP"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify trans-rule WORD trans-type HTTP translator (s6a-MAP | MAP-s6a | CAP-Ro | CAP-Ro-TSL)",
            "Command to Modify the Translator Rule Configuration",
            "Modify the translation-rule",
            "Enter the translation rule name",
            "Translation Type for Rule",
            "Translation Type - SS7",
            "Translator for Rule",
            "Translator s6a-MAP",
            "Translator MAP-s6a",
            "Translator CAP-Ro",
            "Translator CAP-Ro-Transatel"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
		    0,
		    0,
		    C_cli_translation_rule_config_Id,
		    "allowed-vplmn-id WORD",
		    "Command to configure Allowed Vplmn-Id",
		    "Enter the Vplmn-Id in Hex Format"
	   );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#if 0
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "dest-name WORD (|dest-host WORD)",
            "Command to configure Destination",
            "Enter the Destination Name",
	        "Command to configure Destination host",
	        "Enter the Destination host name"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "alt-dest WORD alt-host WORD",
            "Command to configure alternate Destination",
            "Enter the Destination Name",
	        "Command to configure alternate Destination host",
	        "Enter the Destination host name"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#endif
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "primary-dest-realm WORD (|primary-dest-host WORD)",
            "Command to configure Primary Destination configuration",
            "Enter the Destination Name",
	        "Command to configure Destination host",
	        "Enter the Destination host name"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "secondary-dest-realm WORD secondary-dest-host WORD",
            "Command to configure Secondary Destination Configuration",
            "Enter the Destination Name",
	        "Command to configure alternate Destination host",
	        "Enter the Destination host name"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
        
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "service-context-id WORD",
            "Command to configure ServiceContextId",
            "Enter the Service Context Id Value"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "service-key list WORD",
            "Command to configure Service Key",
            "List of Service Keys Ex: x,y,z or * for WildCard",
            "Enter the list seperated by comma or *"
           );
    
    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#if 0
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "service-key value <0-100000>",
            "Command to configure Service Key",
            "Select Value of Service Key",
            "Enter the Value"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#endif
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "imsi-prefix WORD",
            "Command to configure IMSI Prefix",
            "Enter the imsi prefix value Ex: 40412 or * for WildCard"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "service-key range start-value <0-2147483647> end-value <0-2147483647>",
            "Command to configure Service Key",
            "Select Range of service Key",
            "Start Value of Service Key",
            "Enter the start value",
            "End Value of Service Key",
            "Enter the End Value"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "pro-action-rule WORD",
            "Command to configure ProActionRule to be associated",
            "Enter the rule name to be associated"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

#if 0
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "calling-gt-addr-digits WORD",
            "Command to configure Calling GT Address Digits",
            "Enter the Address DIgits in Hex Format"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#endif
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "ossn (CAP | SGSN | HLR) dssn (CAP | SGSN | HLR)",
            "Command to configure OSSN and DSSN",
            "Originating SSN - CAP",
            "Originating SSN - SGSN",
            "Originating SSN - HLR",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_TRANS_RULE_SS7, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "dest-Name WORD (|alt-dest WORD)",
            "Command to configure sigtran Destination",
            "Enter the Destination Name",
            "Alternate Sigtran Destination",
            "Enter the alternate Destination Name"
           );

    cli_install(ctree, MODE_TRANS_RULE_DIAMETER, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#if 0 
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "mcc WORD mnc WORD",
            "Command to configure MCC and MNC",
            "Enter the MCC value",
            "MNC for rule",
            "Enter the MNC value"
           );

    cli_install(ctree, MODE_TRANS_RULE_DIAMETER, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);
#endif
    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "imsi-Prefix WORD",
            "Command to configure IMSI Prefix",
            "Enter the imsi prefix value Ex: 40412 or * for WildCard"
           );

    cli_install(ctree, MODE_TRANS_RULE_DIAMETER, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "OSSN (CAP | SGSN | HLR) DSSN (CAP | SGSN | HLR)",
            "Command to configure OSSN and DSSN",
            "Originating SSN - CAP",
            "Originating SSN - SGSN",
            "Originating SSN - HLR",
            "Destination SSN",
            "Destination SSN - CAP",
            "Destination SSN - SGSN",
            "Destination SSN - HLR"
           );

    cli_install(ctree, MODE_TRANS_RULE_DIAMETER, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
		    0,
		    0,
		    C_cli_translation_rule_config_Id,
		    "allowed-vplmn-Id WORD",
		    "Command to configure Allowed Vplmn-Id",
		    "Enter the Vplmn-Id in Hex Format"
	   );

    cli_install(ctree, MODE_TRANS_RULE_DIAMETER, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
		    0,
		    0,
            C_cli_translation_rule_config_Id,
            "http-url WORD",
            "Command to configure HTTP-URL",
            "Enter the URL"
           );

    cli_install(ctree, MODE_TRANS_RULE_HTTP, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "web-srvc WORD",
            "Command to configure Web Service Id",
            "Enter the Web-Service"
           );

    cli_install(ctree, MODE_TRANS_RULE_HTTP, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
		    0,
		    0,
		    C_cli_translation_rule_config_Id,
		    "allowed-Vplmn-id WORD",
		    "Command to configure Allowed Vplmn-Id",
		    "Enter the Vplmn-Id in Hex Format"
	   );

    cli_install(ctree, MODE_TRANS_RULE_HTTP, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_vplmn_Id,
            "no allowed-vplmn-id trans-rule WORD vplmn-id WORD (| vplmn-id WORD) (| vplmn-id WORD) (| vplmn-id WORD)",
            "Command to delete the configuration",
            "Delete the vplmn-id configuration",
            "Translator rule",
            "Enter the Translator Rule Name",
            "vplmn-id to delete",
            "Enter the Vplmn-Id in Hex Format",
            "vplmn-id to delete",
            "Enter the Vplmn-Id in Hex Format",
            "vplmn-id to delete",
            "Enter the Vplmn-Id in Hex Format",
            "vplmn-id to delete",
            "Enter the Vplmn-Id in Hex Format"
            );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_translation_vplmn_Id);

    Add_CLI(ctree, cli_int_translator_rule_config,
            0,
            0,
            C_cli_translation_rule_config_Id,
            "no trans-rule WORD",
            "Command to delete the configuration",
            "Delete Translator rule",
            "Enter the Translator Rule Name");

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_translation_rule_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "s6a-MAP local-sgsn-num WORD routing-prefix WORD",
            "Command to Configure s6a-MAP Configuration",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "RoutingPrefix to be added for SGSN Number",
            "Enter the Routing Prefix value"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify s6a-MAP",
            "Command to Modify the Configuration",
            "Modify the s6a-MAP Configuration"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "org-host WORD ip-addr WORD",
            "Command to configure Org-Host and Ip-Addr",
            "Enter the Origin Host Name",
            "Ip Addr of Origin Host",
            "Enter the Ip Address"
           );

    cli_install(ctree, MODE_CONFIG_ADD_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);
    
    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "vplmnId WORD sgsn-prefix WORD",
            "Command to configure VplmnId-SgsnPrefix mapping",
            "Enter the VplmnId",
            "Sgsn-Prefix for VplmnId",
            "Enter the Sgsn-Prefix value"
           );

    cli_install(ctree, MODE_CONFIG_ADD_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "local-sgsn-num WORD",
            "Command to Configure Local SGSN Number",
            "Enter the SGSN Number"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "routing-prefix WORD",
            "Command to Configure RoutingPrefix to be added for SGSN Number",
            "Enter the Routing Prefix value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "org-Host WORD ip-addr WORD",
            "Command to configure Org-Host and Ip-Addr",
            "Enter the Origin Host Name",
            "Ip Addr of Origin Host",
            "Enter the Ip Address"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "vplmnID WORD sgsn-prefix WORD",
            "Command to configure VplmnId-SgsnPrefix mapping",
            "Enter the VplmnId",
            "Sgsn-Prefix for VplmnId",
            "Enter the Sgsn-Prefix value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_S6A_MAP, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "no sgsn-addr-map org-Host WORD",
            "Command to delete the configuration",
            "Command to delete sgsn-addr-map configuration",
            "Origin Host",
            "Enter the Origin Host"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_s6a_map_config,
            0,
            0,
            C_cli_s6a_map_config_Id,
            "no vplmnId-SgsnPrefix-map vplmnId WORD",
            "Command to delete the configuration",
            "Command to delete SgsnPrefixMap configuration",
            "VplmnId to be deleted",
            "Enter the VplmnId value"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_s6a_map_config_Id);

    Add_CLI(ctree, cli_int_clearsession,
            0,
            0,
            C_cli_clear_session_config_Id,
            "purge-session imsi WORD",
            "Command to clear SessionContext",
            "Subscriber IMSI",
            "Imsi of particular subscriber"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_clear_session_config_Id);

    Add_CLI(ctree, cli_int_clearsession,
            0,
            0,
            C_cli_clear_session_config_Id,
            "purge-session all",
            "Command to clear SessionContext",
            "Clear All Subscribers"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_clear_session_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "MAP-s6a hlr-num <0-99999999999999999999>",
            "Command to configure MAP-s6a Configuration",
            "HLR Number",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_map_s6a_config,
            0,
            0,
            C_cli_map_s6a_config_Id,
            "vplmn-Id WORD sgsn-number WORD (|sgsn-number WORD) (|sgsn-number WORD) (|sgsn-number WORD)",
            "Command to configure vplmnid-sgsn map",
            "Enter the value of Vplmn Id",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number"
           );

    cli_install(ctree, MODE_CONFIG_ADD_MAP_S6A, PRIVILEGE_ADMIN, C_cli_map_s6a_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify MAP-s6a hlr-num <0-99999999999999999999>",
            "Command to modify the configuration",
            "Modify MAP-s6a Configuration",
            "HLR Number",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_map_s6a_config,
            0,
            0,
            C_cli_map_s6a_config_Id,
            "hlr-num <0-99999999999999999999>",
            "Command to modify the hlr-num",
            "Enter the value"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_MAP_S6A, PRIVILEGE_ADMIN, C_cli_map_s6a_config_Id);

    Add_CLI(ctree, cli_int_map_s6a_config,
            0,
            0,
            C_cli_map_s6a_config_Id,
            "vplmn-id WORD sgsn-number WORD (|sgsn-number WORD) (|sgsn-number WORD) (|sgsn-number WORD)",
            "Command to configure vplmnid-sgsn map",
            "Enter the value of Vplmn Id",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number"
           );

    cli_install(ctree, MODE_CONFIG_MODIFY_MAP_S6A, PRIVILEGE_ADMIN, C_cli_map_s6a_config_Id);

    Add_CLI(ctree, cli_int_map_s6a_config,
            0,
            0,
            C_cli_map_s6a_vplmn_sgsn_config_Id,
            "no sgsn-vplmn-id-map vplmn-id WORD sgsn-number WORD (|sgsn-number WORD) (|sgsn-number WORD) (|sgsn-number WORD)",
            "Command to delete the configuration",
            "Delete the allowed-vplmnid-sgsn map",
            "Allowed vplmn-id",
            "Enter the value of Vplmn Id",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number",
            "Local SGSN Number",
            "Enter the SGSN Number"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_map_s6a_vplmn_sgsn_config_Id);
    
    Add_CLI(ctree, cli_delete_map_s6a_config_vplmn,
            0,
            0,
            C_cli_map_s6a_vplmn_config_Id,
            "no map-s6a-vplmn-id vplmn-id WORD (| vplmn-id WORD) (| vplmn-id WORD) (| vplmn-id WORD)",
	        "Command to delete the configuration",
            "Delete the allowed-vplmnid map",
            "Vplmn Id to be deleted",
            "Enter the Vplmn-Id value",
            "Vplmn Id to be deleted",
            "Enter the Vplmn-Id value",
            "Vplmn Id to be deleted",
            "Enter the Vplmn-Id value",
            "Vplmn Id to be deleted",
            "Enter the Vplmn-Id value"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_map_s6a_vplmn_config_Id);
    
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "CAP-Ro",
            "Command to set CLI to CAP-Ro config mode"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "idp",
            "Command to Configure IDP related configuration"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify idp",
            "Command to modify the configuration",
            "Modify IDP related configuration"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "node-func <0-65535>",
            "Command to configure Node Functionality",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "sip-method WORD",
            "Command to configure SIP Method",
            "Enter the method"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "originating-ioi <0-65535>",
            "Command to configure Originating IOI",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "terminating-ioi <0-65535>",
            "Command to configure Terminating IOI",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);
#if 0
    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "service-context-Id WORD",
            "Command to configure Service Context Id",
            "Enter the Service Context Id"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);
#endif
    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "cause-code <0-65535>",
            "Command to configure Cause Code",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "msc-srvc-specific-type <0-65535>",
            "Command to configure service-specific-type mapped for mscAddress",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "gmsc-srvc-specific-type <0-65535>",
            "Command to configure service-specific-type mapped for gmscAddress",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "cpc-srvc-specific-type <0-65535>",
            "Command to configure service-specific-type mapped for CallingPartyCategory",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "multi-srvc-indi (SUPPORTED | NOT-SUPPORTED)",
            "Command to configure Multi Service Indicator",
            "Multiple Service Indicator Supported",
            "Multiple Service Indicator Not-Supported"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "ext-tele-srvc <0-65535> srvc-id <0-65535>",
            "Command to configure Extension Tele Service to ServiceId Mapping",
            "Enter the Ext-Tele-Service Value",
            "Service Id for mapping",
            "Enter the service Id Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "ext-bearer-srvc <0-65535> srvc-id <0-65535>",
            "Command to configure Extension Bearer Service to ServiceId Mapping",
            "Enter the Ext-Bearer-Service Value",
            "Service Id for mapping",
            "Enter the service Id Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "no ext-tele-srvc-id-map ext-tele-srvc <0-65535>",
            "Command to delete the configuration",
            "Command to delete Extension Tele Service to ServiceId Mapping",
            "Extension Tele Service",
            "Enter the Ext-Tele-Service Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_config,
            0,
            0,
            C_cli_cap_ro_idp_config_Id,
            "no ext-bearer-srvc-id-map ext-bearer-srvc <0-65535>",
            "Command to delete the configuration",
            "Command to delete Extension Bearer Service to ServiceId Mapping",
            "Extension Bearer Service",
            "Enter the Ext-Bearer-Service Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "idp-sms",
            "Command to Configure IDP-SMS related configuration"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify idp-sms",
            "Modify IDP-SMS related configuration"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "sms-node <0-65535>",
            "Command to Configure SMS Node",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "client-addr WORD",
            "Command to Configure Client Address",
            "Enter the Address"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "org-sccp-addr WORD",
            "Command to Configure Originating SCCP Address",
            "Enter the Address"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "reply-path-request <0-65535>",
            "Command to Configure Reply Path Request",
            "Enter the Address"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);
#if 0
    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "service-Context-id WORD",
            "Command to configure Service Context Id",
            "Enter the Service Context Id"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);
#endif
    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "msc-Srvc-specific-type <0-65535>",
            "Command to Configure service-specific-type mapped for mscAddress",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);

    Add_CLI(ctree, cli_int_cap_ro_idp_sms_config,
            0,
            0,
            C_cli_cap_ro_idp_sms_config_Id,
            "sgsn-srvc-specific-type <0-65535>",
            "Command to Configure service-specific-type mapped for sgsnAddress",
            "Enter the Value"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RO_IDP_SMS, PRIVILEGE_ADMIN, C_cli_cap_ro_idp_sms_config_Id);

    Add_CLI(ctree, cli_int_show_ual_config,
            0,
            0,
            C_cli_show_ual_config_Id,
            "show ual-manager-config",
            "Command to view the configuration",
            "Sigtran UAL Manager Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_ual_config_Id);

    Add_CLI(ctree, cli_int_show_sigtran_local_config,
            0,
            0,
            C_cli_show_local_config_Id,
            "show local-sigtran-config",
            "Command to view the configuration",
            "Sigtran Local Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_local_config_Id);

    Add_CLI(ctree, cli_int_show_sctp_profile_config,
            0,
            0,
            C_cli_show_sctp_profile_config_Id,
            "show sctp-profile-config profile WORD",
            "Command to view the configuration",
            "SCTP-Profile Configuration",
            "SCTP-Profile to show",
            "Enter the SCTP Profile name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_sctp_profile_config_Id);

    Add_CLI(ctree, cli_int_show_sctp_profile_config,
            0,
            0,
            C_cli_show_all_sctp_profile_config_Id,
            "show sctp-profile-config all",
            "Command to view the configuration",
            "SCTP-Profile Configuration",
            "All the SCTP-Profiles Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_sctp_profile_config_Id);

    Add_CLI(ctree, cli_int_show_sctp_endpoint_config,
            0,
            0,
            C_cli_show_sctp_endpoint_config_Id,
            "show sctp-endpoint-config endpoint WORD",
            "Command to view the configuration",
            "SCTP-EndPoint Configuration",
            "SCTP-EndPoint to show",
            "Enter the SCTP-EndPoint name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_sctp_endpoint_config_Id);

    Add_CLI(ctree, cli_int_show_sctp_endpoint_config,
            0,
            0,
            C_cli_show_all_sctp_endpoint_config_Id,
            "show sctp-endpoint-config all",
            "Command to view the configuration",
            "SCTP-EndPoint Configuration",
            "All the SCTP-EndPoints Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_sctp_endpoint_config_Id);

    Add_CLI(ctree, cli_int_show_association_config,
            0,
            0,
            C_cli_show_association_config_Id,
            "show association-config assoc WORD",
            "Command to view the configuration",
            "Association Configuration",
            "Association to show",
            "Enter the Association name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_association_config_Id);

    Add_CLI(ctree, cli_int_show_association_config,
            0,
            0,
            C_cli_show_all_association_config_Id,
            "show association-config all",
            "Command to view the configuration",
            "Association Configuration",
            "All the Associations Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_association_config_Id);

    Add_CLI(ctree, cli_int_show_associationset_config,
            0,
            0,
            C_cli_show_associationset_config_Id,
            "show associationSet-config assoc-Set WORD",
            "Command to view the configuration",
            "Association Configuration",
            "Association-Set to show",
            "Enter the Association name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_association_config_Id);

    Add_CLI(ctree, cli_int_show_associationset_config,
            0,
            0,
            C_cli_show_all_associationset_config_Id,
            "show associationSet-config all",
            "Command to view the configuration",
            "AssociationSet Configuration",
            "All the AssociationSets Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_associationset_config_Id);

    Add_CLI(ctree, cli_int_show_destination_config,
            0,
            0,
            C_cli_show_destination_config_Id,
            "show destination-config dest WORD",
            "Command to view the configuration",
            "Destination Configuration",
            "Destination to show",
            "Enter the Destination name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_destination_config_Id);

    Add_CLI(ctree, cli_int_show_destination_config,
            0,
            0,
            C_cli_show_all_destination_config_Id,
            "show destination-config all",
            "Command to view the configuration",
            "Destination Configuration",
            "All the Destinations Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_destination_config_Id);

    Add_CLI(ctree, cli_int_show_remoteroute_config,
            0,
            0,
            C_cli_show_remoteroute_config_Id,
            "show remoteroute-config remoteroute WORD",
            "Command to view the configuration",
            "RemoteRoute Configuration",
            "RemoteRoute to show",
            "Enter the RemoteRoute name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_show_remoteroute_config,
            0,
            0,
            C_cli_show_all_remoteroute_config_Id,
            "show remoteroute-config all",
            "Command to view the configuration",
            "RemoteRoute Configuration",
            "All the RemoteRoutes Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_remoteroute_config_Id);

    Add_CLI(ctree, cli_int_show_translatorrule_config,
            0,
            0,
            C_cli_show_translatorrule_config_Id,
            "show translatorrule-config rule WORD",
            "Command to view the configuration",
            "TranslatorRule Configuration",
            "TranslatorRule to show",
            "Enter the TranslatorRule name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_translatorrule_config_Id);

    Add_CLI(ctree, cli_int_show_translatorrule_config,
            0,
            0,
            C_cli_show_all_translatorrule_config_Id,
            "show translatorrule-config all",
            "Command to view the configuration",
            "TranslatorRule Configuration",
            "All the TranslatorRules Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_all_translatorrule_config_Id);

    Add_CLI(ctree, cli_int_show_S6aMAP_config,
            0,
            0,
            C_cli_show_s6amap_config_Id,
            "show s6a-map-config",
            "Command to view the configuration",
            "IWF s6a-MAP Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_s6amap_config_Id);

    Add_CLI(ctree, cli_int_show_MAPS6a_config,
            0,
            0,
            C_cli_show_maps6a_config_Id,
            "show map-s6a-config",
            "Command to view the configuration",
            "IWF MAP-s6a Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_maps6a_config_Id);

    Add_CLI(ctree, cli_int_show_CAPRo_config,
            0,
            0,
            C_cli_show_capro_idp_config_Id,
            "show cap-ro-idp-config",
            "Command to view the configuration",
            "IWF CapRo IDP Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_capro_idp_config_Id);

    Add_CLI(ctree, cli_int_show_CAPRo_config,
            0,
            0,
            C_cli_show_capro_idpsms_config_Id,
            "show cap-ro-idpsms-config",
            "Command to view the configuration",
            "IWF CapRo IDPSMS Configuration"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_capro_idpsms_config_Id);

    Add_CLI(ctree, cli_int_showIwfVersion,
            0,
            0,
            C_cli_show_iwf_version_Id,
            "show iwf-version",
            "Command to view the configuration",
            "Installed IWF version"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_iwf_version_Id);
    
    Add_CLI(ctree, cli_int_configPrompt,
		    0,
		    0,
		    C_cli_configprompt_Id,
		    "CAP-Proto",
		    "Command to set CLI to CAP Protocol config mode"
	   );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
    
    Add_CLI(ctree, cli_int_feature_config,
            0,
            0,
            C_cli_tAns_trigger_config_Id,
            "follow-on-TAns-trigger (enable | disable)",
            "Command to set TAnswer Trigger condition for FollowOn calls",
            "Enable the configuration",
            "Disable the configuration"
           );

    cli_install(ctree, MODE_CONFIG_CAP_PROTO, PRIVILEGE_ADMIN, C_cli_tAns_trigger_config_Id);
    
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "protocol-action RRB",
            "Command to set CLI to Message specific config mode",
            "Set CLI to RequestReportBCSM Message specific config mode"
           );

    cli_install(ctree, MODE_CONFIG_CAP_PROTO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "rrb-rule WORD",
            "Command to configure RRB Rule",
            "Enter the RRb Rule Name"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "modify rrb-rule WORD",
            "Command to modify the configuration",
            "Modify the RRB Rule",
            "Enter the RRb Rule Name"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "call-scenario (MO_CAPV1 | MO_CAPV2 | MT_CAPV1 | MT_CAPV2 | SMS_CAPV3)",
            "Command to configure the call Scenario",
            "CallScenario MO CAPV1",
            "CallScenario MO CAPV2",
            "CallScenario MT CAPV1",
            "CallScenario MT CAPV2",
            "CallScenario SMS CAPV3"
           );

    cli_install(ctree, MODE_CONFIG_RRB_CALL_SCENARIO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "event-type-sms-capv3 (o-smsSubmitted | o-smsFailure) monitorMode (interrupted | transparent | notifyAndContinue)",
            "Command to configure the EventType related configuration",
            "EventType - oSmsSubmitted",
            "EventType - oSmsFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue"
           );

    cli_install(ctree, MODE_CONFIG_SMS_CAP_V3, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "event-type-mo-capv1 (oAnswer | oDisconnect) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to configure the EventType related configuration",
            "EventType - oAnswer",
            "EventType - oDisconnect",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
           );

    cli_install(ctree, MODE_CONFIG_MO_CAP_V1, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "event-type-mt-capv1 (tAnswer | tDisconnect) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to configure the EventType related configuration",
            "EventType - tAnswer",
            "EventType - tDisconnect",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
           );

    cli_install(ctree, MODE_CONFIG_MT_CAP_V1, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "event-type-mo-capv2 (oAnswer | oDisconnect | oAbandon | oNoAnswer | oCalledPartyBusy | routeSelectFailure) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to configure the EventType related configuration",
            "EventType - oAnswer",
            "EventType - oDisconnect",
            "EventType - oAbandon",
            "EventType - oNoAnswer",
            "EventType - oCalledPartyBusy",
            "EventType - routeSelectFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
           );

    cli_install(ctree, MODE_CONFIG_MO_CAP_V2, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "event-type-mt-capv2 (tAnswer | tDisconnect | tAbandon | tNoAnswer | tBusy | routeSelectFailure) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to configure the EventType related configuration",
            "EventType - tAnswer",
            "EventType - tDisconnect",
            "EventType - tAbandon",
            "EventType - tNoAnswer",
            "EventType - tBusy",
            "EventType - routeSelectFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
           );

    cli_install(ctree, MODE_CONFIG_MT_CAP_V2, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no rrb-rule WORD",
            "Command to delete the configuration",
            "Delete the RRB Rule configuration",
            "Enter the RRb Rule Name"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no call-scenario rrb-rule WORD call-scenario (MO_CAPV1 | MO_CAPV2 | MT_CAPV1 | MT_CAPV2 | SMS_CAPV3)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV1",
            "CallScenario MO CAPV2",
            "CallScenario MT CAPV1",
            "CallScenario MT CAPV2",
            "CallScenario SMS CAPV3"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-type rrb-rule WORD call-scenario MO_CAPV1 event-type (oAnswer | oDisconnect)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV1",
            "Event Type",
            "EventType - oAnswer",
            "EventType - oDisconnect"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-type rrb-rule WORD call-scenario MT_CAPV1 event-type (tAnswer | tDisconnect)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV1",
            "Event Type",
            "EventType - tAnswer",
            "EventType - tDisconnect"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-type rrb-rule WORD call-scenario MT_CAPV2 event-type (tAnswer | tDisconnect | tAbandon | tNoAnswer | tBusy | routeSelectFailure)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV2",
            "Event Type",
            "EventType - tAnswer",
            "EventType - tDisconnect",
            "EventType - tAbandon",
            "EventType - tNoAnswer",
            "EventType - tBusy",
            "EventType - routeSelectFailure"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-type rrb-rule WORD call-scenario MO_CAPV2 event-type (oAnswer | oDisconnect | oAbandon | oNoAnswer | oCalledPartyBusy | routeSelectFailure)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV2",
            "Event Type",
            "EventType - oAnswer",
            "EventType - oDisconnect",
            "EventType - oAbandon",
            "EventType - oNoAnswer",
            "EventType - oCalledPartyBusy",
            "EventType - routeSelectFailure"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-type rrb-rule WORD call-scenario SMS_CAPV3 event-type (o-smsSubmitted | o-smsFailure)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV1",
            "Event Type",
            "EventType - o-smsSubmitted",
            "EventType - o-smsFailure"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

#if 0
    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-Type rrb-rule WORD call-scenario (MO_CAPV1 | MO_CAPV2 | MT_CAPV1 | MT_CAPV2 | SMS_CAPV3) event-type WORD",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV1",
            "CallScenario MO CAPV2",
            "CallScenario MT CAPV1",
            "CallScenario MT CAPV2",
            "CallScenario SMS CAPV3"
            "Event Type",
            "Enter the Event Type"
           );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-Type-config rrb-rule WORD call-scenario (MO_CAPV1 | MO_CAPV2 | MT_CAPV1 | MT_CAPV2 | SMS_CAPV3) event-type WORD monitorMode (interrupted | transparent | notifyAndContinue) legId (01 | 02)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV1",
            "CallScenario MO CAPV2",
            "CallScenario MT CAPV1",
            "CallScenario MT CAPV2",
            "CallScenario SMS CAPV3"
            "Event Type",
            "Enter the Event Type",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "LegId - 01",
            "LegId - 02"

                );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);
#endif
    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-config rrb-rule WORD call-scenario MO_CAPV1 event-type (oAnswer | oDisconnect) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV1",
            "Event Type",
            "EventType - oAnswer",
            "EventType - oDisconnect",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
            );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-config rrb-rule WORD call-scenario MT_CAPV1 event-type (tAnswer | tDisconnect) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV1",
            "Event Type",
            "EventType - tAnswer",
            "EventType - tDisconnect",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
                );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-config rrb-rule WORD call-scenario SMS_CAPV3 event-type (o-smsSubmitted | o-smsFailure) monitorMode (interrupted | transparent | notifyAndContinue)",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario SMS CAPV3",
            "Event Type",
            "EventType - o-smsSubmitted",
            "EventType - o-smsFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue"
                );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-config rrb-rule WORD call-scenario MT_CAPV2 event-type (tAnswer | tDisconnect | tAbandon | tNoAnswer | tBusy | routeSelectFailure) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MT CAPV2",
            "Event Type",
            "EventType - tAnswer",
            "EventType - tDisconnect",
            "EventType - tAbandon",
            "EventType - tNoAnswer",
            "EventType - tBusy",
            "EventType - routeSelectFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
                );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_delete_protocolactions_config,
            0,
            0,
            C_cli_protocol_actions_Id,
            "no event-config rrb-rule WORD call-scenario MO_CAPV2 event-type (oAnswer | oDisconnect | oAbandon | oNoAnswer | oCalledPartyBusy | routeSelectFailure) monitorMode (interrupted | transparent | notifyAndContinue) legId <1-2>",
            "Command to delete the configuration",
            "Delete the RRBRule CallScenario-EventType configuration",
            "RRB Rule",
            "Enter the RRB Rule name",
            "Call Scenario",
            "CallScenario MO CAPV2",
            "Event Type",
            "EventType - oAnswer",
            "EventType - oDisconnect",
            "EventType - oAbandon",
            "EventType - oNoAnswer",
            "EventType - oCalledPartyBusy",
            "EventType - routeSelectFailure",
            "Monitor Mode",
            "MonitorMode-Interrupted",
            "MonitorMode-Transparent",
            "MonitorMode-NotifyAndContinue",
            "LegId of Event",
            "Enter LegId"
                );

    cli_install(ctree, MODE_CONFIG_CAP_RRB, PRIVILEGE_ADMIN, C_cli_protocol_actions_Id);

    Add_CLI(ctree, cli_int_show_protocolactions_config,
            0,
            0,
            C_cli_show_protocolactions_config_Id,
            "show protocol-action-rule all",
            "Command to show the configuration",
            "Show ProtocolAction Rule Configuration",
            "View all the rules"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_protocolactions_config_Id);

    Add_CLI(ctree, cli_int_show_protocolactions_config,
            0,
            0,
            C_cli_show_protocolactions_config_Id,
            "show protocol-action-rule rule WORD",
            "Command to show the configuration",
            "Show ProtocolAction Rule Configuration",
            "View specific Rule configuration",
            "Enter the Rule Name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_protocolactions_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
		    0,
		    0,
		    C_cli_configprompt_Id,
		    "cap-timers",
		    "Command to set CLI to CAP Timers config mode"
	   );

    cli_install(ctree, MODE_CONFIG_CAP_PROTO, PRIVILEGE_ADMIN, C_cli_configprompt_Id);
    
    Add_CLI(ctree, cli_int_cap_timers,
            0,
            0,
            C_cli_cap_timers_Id,
            "no-activity-timer <0-65535> retry-count <0-5> response-timeout <0-65535>",
            "Command to configure Activity-Timer configuration for Voice Calls",
            "Enter the No-Activity-Timer in seconds",
            "Retry Count Timer",
            "Enter the value",
            "AT Response TimeOut",
            "Enter the value in seconds"
           );

    cli_install(ctree, MODE_CONFIG_CAP_TIMERS, PRIVILEGE_ADMIN, C_cli_cap_timers_Id);

    Add_CLI(ctree, cli_int_cap_timers,
		    0,
		    0,
		    C_cli_cap_timers_Id,
		    "voice-no-answer-timer <0-65535>",
		    "Command to configure No-Answer-Timer for Voice Calls",
		    "Enter the value in seconds"
	   );

    cli_install(ctree, MODE_CONFIG_CAP_TIMERS, PRIVILEGE_ADMIN, C_cli_cap_timers_Id);

    Add_CLI(ctree, cli_int_cap_timers,
		    0,
		    0,
		    C_cli_cap_timers_Id,
		    "network-delay-timer <0-65535>",
		    "Command to configure Network Delay timer for Voice Calls",
		    "Enter the value in seconds"
	   );

    cli_install(ctree, MODE_CONFIG_CAP_TIMERS, PRIVILEGE_ADMIN, C_cli_cap_timers_Id);

    Add_CLI(ctree, cli_int_cap_timers,
		    0,
		    0,
		    C_cli_cap_timers_Id,
		    "sms-no-event-timer <0-65535>",
		    "Command to configure No-Event-Timer for SMS",
		    "Enter the value in seconds"
	   );

    cli_install(ctree, MODE_CONFIG_CAP_TIMERS, PRIVILEGE_ADMIN, C_cli_cap_timers_Id);

    Add_CLI(ctree, cli_int_show_cap_timers,
		    0,
		    0,
		    C_cli_show_cap_timers_Id,
		    "show cap-proto-timers",
		    "Command to view the configuration",
		    "CAP-Proto-Timers configuration"
	   );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_cap_timers_Id);

    Add_CLI(ctree, cli_int_show_log_cdr,
		    0,
		    0,
		    C_cli_show_log_cdr_Id,
		    "show log-cdr-config",
		    "Command to view the configuration",
		    "CDR configuration Status"
	   );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_log_cdr_Id);

    Add_CLI(ctree, cli_int_log_cdr_config,
		    0,
		    0,
		    C_cli_log_cdr_config_Id,
		    "log-cdr enable (failed-calls-only | all-calls)",
		    "Command to set the CDR configuration",
		    "Enable the feature",
            "Enable CDR for failed-calls only",
            "Enable CDR for all-calls"
	   );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_log_cdr_config_Id);

    Add_CLI(ctree, cli_int_log_cdr_config,
		    0,
		    0,
		    C_cli_log_cdr_config_Id,
		    "log-cdr disable (success-calls-only | all-calls)",
		    "Command to set the CDR configuration",
		    "Disable the feature",
            "Disable CDR for success-calls only",
            "Disable CDR for all-calls"
	   );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, C_cli_log_cdr_config_Id);
    
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "dcca",
            "Command to Set CLI to DCCA Configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_dcca_general_config,
		    0,
		    0,
		    C_cli_dcca_general_config_Id,
		    "tx-timeout <0-65535>",
		    "Command to configure Tx Time Out for DCCA",
		    "Enter the value in seconds"
	   );

    cli_install(ctree, MODE_CONFIG_DCCA, PRIVILEGE_ADMIN, C_cli_dcca_general_config_Id);
    
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "failure-handling",
            "Command to Configure Failure handling Configuration"
           );

    cli_install(ctree, MODE_CONFIG_DCCA, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_failure_handling_config,
            0,
            0,
            C_cli_dcca_failure_handling_Id,
            "initial-action (retry-and-terminate | continue | terminate)",
            "Command to configure Initial Action for Failure handling",
            "Initial-Action Retry and Terminate",
            "Initial-Action Continue",
            "Initial-Action Terminate"
            );

    cli_install(ctree, MODE_CONFIG_FAILURE_HANDLING, PRIVILEGE_ADMIN, C_cli_dcca_failure_handling_Id);
#if 0
    //NOTE: Used when Functionality is implemented in IWF
    Add_CLI(ctree, cli_int_failure_handling_config,
            0,
            0,
            C_cli_dcca_failure_handling_Id,
            "update-action (retry-and-terminate | continue | terminate)",
            "Command to configure Update Action for Failure handling",
            "Update-Action Retry and Terminate",
            "Update-Action Continue",
            "Update-Action Terminate"
            );

    cli_install(ctree, MODE_CONFIG_FAILURE_HANDLING, PRIVILEGE_ADMIN, C_cli_dcca_failure_handling_Id);
#endif
    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "dest-realm WORD",
            "Command to Configure OCS server pool Configuration"
           );

    cli_install(ctree, MODE_CONFIG_DCCA, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_dcca_dest_config,
            0,
            0,
            C_cli_dcca_dest_config_Id,
            "send-ccrt (Yes | No)",
            "Command to configure sending Termination Request for this realm",
            "Yes - to send CCRT",
            "No - not to send CCRT" 
            );

    cli_install(ctree, MODE_CONFIG_DCCA_DESTINATION, PRIVILEGE_ADMIN, C_cli_dcca_dest_config_Id);
    
    Add_CLI(ctree, cli_int_dcca_dest_config,
            0,
            0,
            C_cli_dcca_dest_config_Id,
            "endpoint WORD priority <1-100>",
            "Command to configure EndPoint for the Destination",
            "Enter the EndPoint name",
            "Priority for the EndPoint",
            "Enter the priority"
            );

    cli_install(ctree, MODE_CONFIG_DCCA_DESTINATION, PRIVILEGE_ADMIN, C_cli_dcca_dest_config_Id);
    
    Add_CLI(ctree, cli_int_dcca_dest_config,
            0,
            0,
            C_cli_dcca_dest_realm_config_Id,
            "no dest-realm WORD",
            "Command to Delete the Configuration",
            "Delete the Dest-Realm Config",
            "Enter the Dest Realm Name"
           );
    
    cli_install(ctree, MODE_CONFIG_DCCA, PRIVILEGE_ADMIN, C_cli_dcca_dest_realm_config_Id);

    Add_CLI(ctree, cli_int_dcca_dest_config,
            0,
            0,
            C_cli_dcca_dest_config_Id,
            "no endpoint WORD dest-realm WORD",
            "Command to Delete the Configuration",
            "Delete the EndPoint from a Dest-Realm Config",
            "Enter the EndPoint Name",
            "Destination Realm",
            "Enter the Dest Realm Name"
           );
    
    cli_install(ctree, MODE_CONFIG_DCCA, PRIVILEGE_ADMIN, C_cli_dcca_dest_config_Id);
    
    Add_CLI(ctree, cli_int_show_dcca_config,
            0,
            0,
            C_cli_show_dcca_dest_config_Id,
            "show dcca-dest-config WORD",
            "Command to view the configuration",
            "Show Dcca Destinations configurations",
            "Enter the Destination realm name"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_dcca_dest_config_Id);

    Add_CLI(ctree, cli_int_show_dcca_config,
            0,
            0,
            C_cli_show_dcca_general_config_Id,
            "show dcca-general-config",
            "Command to view the configuration",
            "Show Dcca General configurations"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_dcca_general_config_Id);

    Add_CLI(ctree, cli_int_show_feature_config,
            0,
            0,
            C_cli_show_tAns_trigger_config_Id,
            "show followOn-TAns-trigger-config",
            "Command to view the configuration",
            "Show FollowOn TAns Trigger configuration"
           );
    
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_tAns_trigger_config_Id);

    Add_CLI(ctree, cli_int_configPrompt,
            0,
            0,
            C_cli_configprompt_Id,
            "general-Config",
            "Command to set IWF to General Configuration Mode"
           );

    cli_install(ctree, MODE_CONFIG_IWF, PRIVILEGE_ADMIN, C_cli_configprompt_Id);

    Add_CLI(ctree, cli_int_feature_config,
            0,
            0,
            C_cli_congestion_management_config_Id,
            "congestion-management enable (|max-num-of-calls <1-25000>)",
            "Command to set Congestion Management configuration for IWF",
            "Enable the congestion Management feature",
            "Maximum number of sessions to hold",
            "Enter the number of sessions to hold"
           );

    cli_install(ctree, MODE_IWF_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_congestion_management_config_Id);

    Add_CLI(ctree, cli_int_feature_config,
            0,
            0,
            C_cli_congestion_management_config_Id,
            "congestion-management disable",
            "Command to set Congestion Management configuration for IWF",
            "Disable the congestion Management feature"
           );

    cli_install(ctree, MODE_IWF_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_congestion_management_config_Id);

    Add_CLI(ctree, cli_int_show_feature_config,
            0,
            0,
            C_cli_show_congestion_management_config_Id,
            "show congestion-management-config",
            "Command to view the configuration",
            "Show IWF Congestion Management configuration"
           );
    
    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, C_cli_show_tAns_trigger_config_Id);

    Add_CLI(ctree, cli_int_dump_system_info,
            0,
            0,
            C_cli_dump_system_info_config_Id,
            "dump-iwf-system-info",
            "Command to Dump IWF System Info to Log file"
           );
    
    cli_install(ctree, MODE_IWF_GENERAL_CONFIG, PRIVILEGE_ADMIN, C_cli_dump_system_info_config_Id);

    return 0;
}
