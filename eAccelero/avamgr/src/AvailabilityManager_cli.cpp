/*********************************-*-C++-*-************************************
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

#include "AvailabilityManager_cli.h"

int dre_AvaMgr_init(struct cli_def *ctree)
{
	Add_CLI(ctree,ShowConfigAvaMgr,I_AVAILABILITY_MANAGER,M_SHOW_CONFIG_AVAMGR,
        	ShowConfigAvaMgr_cmd,
	  	"show config avamgr",
	  	"show configuration information",
	  	"configuration information",
        	"avalability manager"
		);

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, ShowConfigAvaMgr_cmd);
	
	
	
	
	
	Add_CLI(ctree,SetAvaMgrLogLevel,I_AVAILABILITY_MANAGER,M_AVAMGR_LOGLEVEL,
        	SetAvaMgrLogLevel_cmd,
          	"avamgr set-log-level (DEBUG | INFO | NOTICE | WARNING | ERROR | CRITICAL | FATAL) (disable | enable)",
          	"avalability manager",
          	"command to set the availability manager log level",
          	"DEBUG - Messages above DEBUG Level",
          	"INFO - Messages above INFO Level",
          	"NOTICE - Messages above NOTICE Level",
			"WARNING - Messages above WARNING Level",
			"ERROR - Messages above ERROR Level",
          	"CRITICAL - Messages above CRITICAL Level",
          	"FATAL - Messages above FATAL Level",
          	"disable - set the selected Log Level",
          	"enable - unset the selected Log Level"
		);

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_OPERATOR, SetAvaMgrLogLevel_cmd);
	
	
	
	

	Add_CLI(ctree,SetConfigPingPeriodicity,I_AVAILABILITY_MANAGER,M_CONFIG_PING_PERIODICITY,
        SetConfigPingPeriodicity_cmd,
		"ping-periodicity <1-65535>",
		"set ping periodicity for either node to its peer",
		"enter value in milli-seconds");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigPingPeriodicity_cmd);
	
	
	
	
 
	Add_CLI(ctree,SetConfigPingPeriodicityArbitrator,I_AVAILABILITY_MANAGER,M_CONFIG_PING_PERIODICITY_ARBITRATOR,
        SetConfigPingPeriodicityArbitrator_cmd,
		"ping-periodicity-for-arbitrator <1-65535>",
		"set ping periodicity for either node to arbitrator",
		"enter value in milli-seconds");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigPingPeriodicityArbitrator_cmd);
	
	
	
	

	Add_CLI(ctree,SetConfigVirtualInterfaceActivationTime,I_AVAILABILITY_MANAGER,M_CONFIG_VIRTUAL_INTERFACE_ACTIVATION_TIME,
        SetConfigVirtualInterfaceActivationTime_cmd,
		"virtual-interface-activation-time <1-65535>",		
        "set virtual interface activation period for either node",
		"enter value in milli-seconds");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigVirtualInterfaceActivationTime_cmd);
	
	
	
	

	Add_CLI(ctree,SetConfigPeerPingAckReceiveFailures,I_AVAILABILITY_MANAGER,M_CONFIG_PEER_PINGACK_RECEIVE_FAILURES,
        SetConfigPingAckReceiveFailures_cmd,
		"ping-ack-receive-failures <1-255>",
        "set number of ping ack receive failures",
		"enter value in given range");

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigPingAckReceiveFailures_cmd);	



	
		

	Add_CLI(ctree,SetConfigArbitratorPingAckReceiveFailures,I_AVAILABILITY_MANAGER,M_CONFIG_ARBITRATOR_PINGACK_RECEIVE_FAILURES,
        SetConfigArbitratorPingAckReceiveFailures_cmd,
        "arbitrator-ping-ack-receive-failures <1-255>",
		"set number of arbitrator ping ack receive failures",
		"enter value in given range");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigArbitratorPingAckReceiveFailures_cmd);	
		
	
	
	

	Add_CLI(ctree,SetConfigProcessRestartMaxInterval,I_AVAILABILITY_MANAGER,M_CONFIG_PROCESS_RESTART_MAX_INTERVAL,
        SetConfigProcessRestartMaxInterval_cmd,
		"process-restart-max-interval <1-65535>",
        "set process restart maximum interval",
		"enter value in milli-seconds");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigProcessRestartMaxInterval_cmd);		
	
	
	
	
 
	Add_CLI(ctree,SetConfigProcessRestartMaxCount,I_AVAILABILITY_MANAGER,M_CONFIG_PROCESS_RESTART_MAX_COUNT,
        SetConfigProcessRestartMinCount_cmd,
		"process-restart-max-count <1-255>",
        "set process restart maximum count",
		"enter value in given range");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigProcessRestartMaxCount_cmd);		



	

	Add_CLI(ctree,SetConfigIpV6,I_AVAILABILITY_MANAGER,M_CONFIG_IPV6,
        SetConfigIpV6_cmd,
		"ipv6 (true | false)",
        "set IPv6 enable/disable",
		"set to true",
		"set to false");

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigIpV6_cmd);		
	
	
	
	

	Add_CLI(ctree,SetConfigPrimaryVirtualIpAddress,I_AVAILABILITY_MANAGER,M_CONFIG_PRIMARY_VIRTUAL_IP_ADDRESS,
        SetConfigPrimaryVirtualIpAddress_cmd,
		"primary-virtual-ip-address WORD",
        "set primary virtual ip address on either node",
		"enter valid ip address");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigPrimaryVirtualIpAddress_cmd);		
	
	
	
	

	Add_CLI(ctree,SetConfigSecondaryVirtualIpAddress,I_AVAILABILITY_MANAGER,M_CONFIG_SECONDARY_VIRTUAL_IP_ADDRESS,
        SetConfigSecondaryVirtualIpAddress_cmd,
		"secondary-virtual-ip-address WORD",
        "set secondary virtual ip address on either node",
		"enter valid ip address"); 	

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigSecondaryVirtualIpAddress_cmd);		
	
	
	
	

	Add_CLI(ctree,SetConfigGatewayIP,I_AVAILABILITY_MANAGER,M_CONFIG_GATEWAY_IP_ADDRESS,
        SetConfigGatewayIpAddress_cmd,
		"gateway-ip-address WORD",
		"set gateway ip address on either node",
		"enter valid ip address");
		
	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, SetConfigGatewayIpAddress_cmd);	
	
	
	
	
    Add_CLI(ctree, Restart,I_AVAILABILITY_MANAGER,M_RESTART_COMPONENT,
		Restart_cmd
        "restart ( cli | cmgr | repmgr | dreapp) instance-id <1-16383>",        
        "restart command",
		"Command Line Interface Process",
		"Config Manager",
		"Replication Manager",
		"DRE Application"
        "instance id of running process ",
        "instance id range"
        );

	cli_install(ctree, MODE_CONFIG_AVMGR, PRIVILEGE_ADMIN, Restart_cmd);
	
	
	
	

	Add_CLI(ctree, ShowProcess,I_AVAILABILITY_MANAGER,M_SHOW_PROCESS,
        ShowProcess_cmd,
        "show process",        
        "show process command");

        cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, ShowProcess_cmd);
	

	return 0;
}
