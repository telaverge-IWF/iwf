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
#include "InterfaceDefs.h"
    //#include "CommonStructure.h"
#include "LibCli.h"
#include "repmgr_cfg.h"
#include "Common.h"
    extern void send_receive_data(struct cli_def *cli,void* buf,int len,int cmdID,int interfaceID);
    extern int cli_int_configPrompt(struct cli_def *cli, char *command, char *argv[], int argc);
}


#include "CommonStructure.h"
#include "CMAPICommon.h"
#include "CMApiHA.h"
#include "AvailabilityManager_cfg.h"

//#define CLI_DEBUG
////////////////////////////////////CALLBACK FUNCTIONS///////////////////////////////////////////
#if 0
//This request goes to config manager
static int ShowConfigAvaMgr(struct cli_def *cli, char *command, char *argv[], int argc)
{ 


    send_receive_data(cli,NULL,0,ShowConfigAvaMgr_cmd,CLI_CMGR_INTERFACE_ID);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

/*
   static int SetAvaMgrLogLevel(struct cli_def *cli, char *command, char *argv[], int argc)
   {

   int i = 0;
   struct AvaMgrConfigSetLogLevelReq configLogReq;

   while(argv[i]){

   if(!strcmp(argv[i],"DEBUG")){
   configLogReq.uiConfigSetLogLevelReq = Logger::EACC_LOG_DEBUG;
   }else if(!strcmp(argv[i],"INFO")){
   configLogReq.uiConfigSetLogLevelReq = Logger::EACC_LOG_INFO;
   }else if(!strcmp(argv[i],"NOTICE")){
   configLogReq.uiConfigSetLogLevelReq = Logger::EACC_LOG_NOTICE;
   }else if(!strcmp(argv[i],"CRITICAL")){
   configLogReq.uiConfigSetLogLevelReq = Logger::EACC_LOG_CRITICAL;
   }else if(!strcmp(argv[i],"FATAL")){
   configLogReq.uiConfigSetLogLevelReq = Logger::EACC_LOG_FATAL;
   }

#if 0
else if(!strcmp(argv[i],"enable")){
configLogReq.bLogFlag  = true;
}else if(!strcmp(argv[i],"disable")){
configLogReq.bLogFlag  = false;
}
#endif
i++;
}

send_receive_data(cli,&configLogReq, sizeof(configLogReq),SetReplLogLevel_cmd,I_AVAILABILITY_MANAGER);
#ifdef CLI_DEBUG
cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
for (i = 0; i < argc; i++)
cli_print(cli, "        %s", argv[i]);

#endif
return CLI_OK;

}
*/
static int SetConfigPingPeriodicity(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigPingPeriodicityReq configPingPeriod;

    if(argv[1])
        configPingPeriod.uiConfigPingPeriodicity = atoi(argv[1]);

    send_receive_data(cli,&configPingPeriod, sizeof(configPingPeriod),SetConfigPingPeriodicity_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

static int SetConfigPingPeriodicityArbitrator(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigPingPeriodicityForArbitratorReq configArbtrPingPeriod;

    if(argv[1])
        configArbtrPingPeriod.uiConfigPingPeriodicityForArbitrator = atoi(argv[1]);

    send_receive_data(cli,&configArbtrPingPeriod, sizeof(configArbtrPingPeriod),
            SetConfigPingPeriodicityArbitrator_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

/*static int SetConfigVirtualInterfaceActivationTime(struct cli_def *cli, char *command, char *argv[], int argc)
  {

  struct AvaMgrConfigVirtualInterfaceActivationTimeReq configVirtualInterfaceActvationT;

  if(argv[1])
  configVirtualInterfaceActvationT.uiConfigVirtualInterfaceActivationTime = atoi(argv[1]);

  send_receive_data(cli,&configVirtualInterfaceActvationT, sizeof(configVirtualInterfaceActvationT),
  SetConfigVirtualInterfaceActivationTime_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
int i = 0;
cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
for (i = 0; i < argc; i++)
cli_print(cli, "        %s", argv[i]);

#endif
return CLI_OK;

}
*/
static int SetConfigPeerPingAckReceiveFailures(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeerReq
        configNoofPingAckRecFailure;

    if(argv[1])
        configNoofPingAckRecFailure.uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromPeer = atoi(argv[1]);

    send_receive_data(cli,&configNoofPingAckRecFailure, sizeof(configNoofPingAckRecFailure),
            SetConfigPingAckReceiveFailures_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

static int SetConfigArbitratorPingAckReceiveFailures(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitratorReq 
        configNoofPingAckRecFromArbtr;

    if(argv[1])
        configNoofPingAckRecFromArbtr.uiConfigNumberOfConsecutivePingAcknowledgementReceiveFailuresFromArbitrator
            = atoi(argv[1]);

    send_receive_data(cli,&configNoofPingAckRecFromArbtr, sizeof(configNoofPingAckRecFromArbtr),
            SetConfigArbitratorPingAckReceiveFailures_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

static int SetConfigProcessRestartMaxInterval(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigProcessRestartMaximumAllowedIntervalReq configProcessRestartMaxIntrl;

    if(argv[1])
        configProcessRestartMaxIntrl.uiConfigProcessRestartMaximumAllowedInterval
            = atoi(argv[1]);

    send_receive_data(cli,&configProcessRestartMaxIntrl, sizeof(configProcessRestartMaxIntrl),
            SetConfigProcessRestartMaxInterval_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}


static int SetConfigProcessRestartMaxCount(struct cli_def *cli, char *command, char *argv[], int argc)
{

    struct AvaMgrConfigProcessRestartMaximumAllowedCountReq configProcessRestartmaxCnt;

    if(argv[1])
        configProcessRestartmaxCnt.uiConfigProcessRestartMaximumAllowedCount
            = atoi(argv[1]);

    send_receive_data(cli,&configProcessRestartmaxCnt, sizeof(configProcessRestartmaxCnt),
            SetConfigProcessRestartMinCount_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}
/*
   static int SetConfigIpV6(struct cli_def *cli, char *command, char *argv[], int argc)
   {

   struct AvaMgrConfigUseIpV6Req configIpV6Req;

   if(argv[1] && !strcmp(argv[1],"true")){
   configIpV6Req.bConfigUseIpV6 = true;
   } else if(argv[1] && !strcmp(argv[1],"false")){
   configIpV6Req.bConfigUseIpV6 = false;
   }

   send_receive_data(cli,&configIpV6Req, sizeof(configIpV6Req),
   SetConfigIpV6_cmd,I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
int i = 0;
cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
for (i = 0; i < argc; i++)
cli_print(cli, "        %s", argv[i]);

#endif
return CLI_OK;

}
*/
static int SetConfigPrimaryVirtualIpAddress(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    int sendFlag = 0;
    //struct AvaMgrConfigPrimaryVirtualIpAddressReq configPrimVirtualIp;
    while(argv[i])
    {
        if(!strcmp(argv[i],"virtual-ip"))
        {
            i++;
            sprintf(cli->virtualIps.cConfigPrimaryVirtualIpAddress + strlen(cli->virtualIps.cConfigPrimaryVirtualIpAddress),"%s,",argv[i]);     
            //printf("Virtual-ips.Address : %s\n",cli->virtualIps.cConfigPrimaryVirtualIpAddress);
        }
        else if(!strcmp(argv[i],"dev"))
        {
            i++;
            sprintf(cli->virtualIps.cConfigDev + strlen(cli->virtualIps.cConfigDev),"%s,",argv[i]);
            //printf("Virtual-ips.ConfigDev : %s\n",cli->virtualIps.cConfigDev);
        }
        else if(!strcmp(argv[i],"end"))
        {
            sendFlag = 1;
        }
        i++;
    }
    if(sendFlag)
    {
        send_receive_data(cli,&cli->virtualIps, sizeof(cli->virtualIps),
                SetConfigPrimaryVirtualIpAddress_cmd, I_AVAILABILITY_MANAGER);

        memset(&cli->virtualIps,0,sizeof(AvaMgrConfigPrimaryVirtualIpAddressReq));
#ifdef CLI_DEBUG
        //int i = 0;
        cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
        for (i = 0; i < argc; i++)
            cli_print(cli, "        %s", argv[i]);

#endif
    }
    return CLI_OK;


}
/*
   static int SetConfigSecondaryVirtualIpAddress(struct cli_def *cli, char *command, char *argv[], int argc)
   {

   struct AvaMgrConfigSecondaryVirtualIpAddressReq configSecVirtualIp;

   if(argv[1])
   strcpy(configSecVirtualIp.cConfigSecondaryVirtualIpAddress, argv[1]);

   send_receive_data(cli,&configSecVirtualIp, sizeof(configSecVirtualIp),
   SetConfigSecondaryVirtualIpAddress_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
int i = 0;
cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
for (i = 0; i < argc; i++)
cli_print(cli, "        %s", argv[i]);

#endif
return CLI_OK;

}
*/
static int SetConfigGatewayIP(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    struct AvaMgrConfigGatewayIpAddressReq configGatewayIp;
    if(!strcmp(argv[i],"gateway-ip"))
    {
        i++;
    }
    if(!strcmp(argv[1],"address"))
    {
        i++;
        strcpy(configGatewayIp.cConfigGatewayIpAddress, argv[i]);
    }

    send_receive_data(cli,&configGatewayIp, sizeof(configGatewayIp),
            SetConfigGatewayIpAddress_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    //int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}
/*
   static int Restart(struct cli_def *cli, char *command, char *argv[], int argc)
   {

   int i = 0;
   struct AvaMgrConfigRestartReq configRestart;

   while(argv[i]){

   if(!strcmp(argv[i],"cli")){
   configRestart.componentId = COMP_CLI_PROC;
   }else if(!strcmp(argv[i],"cmgr")){
//configRestart.componentId = ;
}else if(!strcmp(argv[i],"repmgr")){
configRestart.componentId = COMP_REPLICATION_MANAGER;
}else if(!strcmp(argv[i],"dreapp")){
//configRestart.componentId = ;
}else if(!strcmp(argv[i],"instance-id")){
i++;
configRestart.instanceId = atoi(argv[i]);
}
i++;
}

send_receive_data(cli,&configRestart, sizeof(configRestart),
Restart_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
for (i = 0; i < argc; i++)
cli_print(cli, "        %s", argv[i]);

#endif
return CLI_OK;

}
*/
static int GetNodeStatus(struct cli_def *cli, char *command, char *argv[], int argc)
{


    send_receive_data(cli,NULL, 0,
            GetNodeStatus_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    int i = 0;
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

static int SetAvaMgrLogLevel(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    struct AvaMgrConfigSetLogLevelReq configLogLevel;

    if(!strcmp(argv[i],"log-level")){
        i=1;
    }
    else
        return CLI_ERROR;

    while(argv[i])
    {
        if(!strcmp(argv[i],"dre") || !strcmp(argv[i],"asf") || !strcmp(argv[i],"erlbf") || !strcmp(argv[i],"avamgr") || !strcmp(argv[i],"cli") || !strcmp(argv[i],"cmgr"))
        {
            strcpy(configLogLevel.componentId,argv[i]);
        }else{
            return CLI_ERROR;
        }
        i++;

        if(!strcmp(argv[i],"DEBUG") || !strcmp(argv[i],"INFO") || !strcmp(argv[i],"NOTICE") || !strcmp(argv[i],"WARNING") || !strcmp(argv[i],"ERROR") || !strcmp(argv[i],"CRITICAL") || !strcmp(argv[i],"FATAL")){
            strcpy(configLogLevel.uiConfigSetLogLevelReq,argv[i]);
        }else{
            return CLI_ERROR;   
        }
        i++;

        if(!strcmp(argv[i],"disable") || !strcmp(argv[i],"enable")){
            strcpy(configLogLevel.log_status,argv[i]);
        }
        else{
            return CLI_ERROR;
        }
    }

    send_receive_data(cli,&configLogLevel, sizeof(configLogLevel),
            SetAvaMgrLogLevel_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;
}

static int SetAvaMgrLogchannel(struct cli_def *cli, char *command, char *argv[], int argc)
{
    int i = 0;
    AvaMgrConfigSetLogChannelReq configLogChannel;
    if(!strcmp(argv[i],"log-channel")){
        i = 1;
    }else
        return CLI_ERROR;

    while(argv[i])
    {
        if(!strcmp(argv[i],"dre") || !strcmp(argv[i],"asf") || !strcmp(argv[i],"erlbf") || !strcmp(argv[i],"avamgr") || !strcmp(argv[i],"cli") || !strcmp(argv[i],"cmgr")){
            strcpy(configLogChannel.componentId,argv[i]);
        }else{
            return CLI_ERROR;
        }
        i++;

        if(!strcmp(argv[i],"syslog") || !strcmp(argv[i],"console")){
            strcpy(configLogChannel.log_channel,argv[i]);
        }else if(!strcmp(argv[i],"file")){
            i++;
            strcpy(configLogChannel.logFileName,argv[i]);
        }else{
            return CLI_ERROR;   
        }
        i++;

        if(!strcmp(argv[i],"disable") || !strcmp(argv[i],"enable")){
            strcpy(configLogChannel.log_status,argv[i]);
        }
        else{
            return CLI_ERROR;
        }

    }
    send_receive_data(cli,&configLogChannel, sizeof(configLogChannel),
            SetAvaMgrLogchannel_cmd, I_AVAILABILITY_MANAGER);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;
}

#endif  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


int avamgr_cli_init(struct cli_def *ctree)
{
#if 0

    Add_CLI(ctree,ShowConfigAvaMgr,I_AVAILABILITY_MANAGER,M_SHOW_CONFIG_AVAMGR,
            ShowConfigAvaMgr_cmd,
            "show avamgr-config",
            "show configuration information",
            "avalability manager"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_ADMIN, ShowConfigAvaMgr_cmd);

    //diameterbase Mode Command
    Add_CLI(ctree, cli_int_configPrompt,
            I_cli_configprompt_Id,
            M_cli_configprompt_Id,
            C_cli_configprompt_Id,
            "virtual-ip-mode",
            "set cli to virtual ip configuration mode"
           );

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, C_cli_configprompt_Id); 


    Add_CLI(ctree, SetConfigPrimaryVirtualIpAddress,I_AVAILABILITY_MANAGER,M_CONFIG_PRIMARY_VIRTUAL_IP_ADDRESS,
            SetConfigPrimaryVirtualIpAddress_cmd,
            "end",
            "to indiacte buffer is ready to send"
           );

    cli_install(ctree, MODE_CONFIG_VIRTUAL_IP, PRIVILEGE_ADMIN, SetConfigPrimaryVirtualIpAddress_cmd);



    Add_CLI(ctree,SetConfigPingPeriodicity,I_AVAILABILITY_MANAGER,M_CONFIG_PING_PERIODICITY,
            SetConfigPingPeriodicity_cmd,
            "ping-periodicity <1-65535>",
            "set ping periodicity for either node to its peer",
            "enter value in milli-seconds");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigPingPeriodicity_cmd);  


    Add_CLI(ctree,SetConfigPingPeriodicityArbitrator,I_AVAILABILITY_MANAGER,M_CONFIG_PING_PERIODICITY_ARBITRATOR,
            SetConfigPingPeriodicityArbitrator_cmd,
            "ping-periodicity-for-arbitrator <1-65535>",
            "set ping periodicity for either node to arbitrator",
            "enter value in milli-seconds");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigPingPeriodicityArbitrator_cmd);    


#if 0
    Add_CLI(ctree,SetConfigVirtualInterfaceActivationTime,I_AVAILABILITY_MANAGER,M_CONFIG_VIRTUAL_INTERFACE_ACTIVATION_TIME,
            SetConfigVirtualInterfaceActivationTime_cmd,
            "virtual-interface-activation-time <1-65535>",      
            "set virtual interface activation period for either node",
            "enter value in milli-seconds");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigVirtualInterfaceActivationTime_cmd);
#endif


    Add_CLI(ctree,SetConfigPeerPingAckReceiveFailures,I_AVAILABILITY_MANAGER,M_CONFIG_PEER_PINGACK_RECEIVE_FAILURES,
            SetConfigPingAckReceiveFailures_cmd,
            "ping-ack-receive-failures <1-255>",
            "set number of ping ack receive failures",
            "enter value in given range");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigPingAckReceiveFailures_cmd);       


    Add_CLI(ctree,SetConfigArbitratorPingAckReceiveFailures,I_AVAILABILITY_MANAGER,M_CONFIG_ARBITRATOR_PINGACK_RECEIVE_FAILURES,
            SetConfigArbitratorPingAckReceiveFailures_cmd,
            "arbitrator-ping-ack-receive-failures <1-255>",
            "set number of arbitrator ping ack receive failures",
            "enter value in given range");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigArbitratorPingAckReceiveFailures_cmd);     



    Add_CLI(ctree,SetConfigProcessRestartMaxInterval,I_AVAILABILITY_MANAGER,M_CONFIG_PROCESS_RESTART_MAX_INTERVAL,
            SetConfigProcessRestartMaxInterval_cmd,
            "process-restart-max-interval <1-65535>",
            "set process restart maximum interval",
            "enter value in milli-seconds");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigProcessRestartMaxInterval_cmd);    




    Add_CLI(ctree,SetConfigProcessRestartMaxCount,I_AVAILABILITY_MANAGER,M_CONFIG_PROCESS_RESTART_MAX_COUNT,
            SetConfigProcessRestartMinCount_cmd,
            "process-restart-max-count <1-255>",
            "set process restart maximum count",
            "enter value in given range");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigProcessRestartMinCount_cmd);       




#if 0
    Add_CLI(ctree,SetConfigIpV6,I_AVAILABILITY_MANAGER,M_CONFIG_IPV6,
            SetConfigIpV6_cmd,
            "ipv6 (true | false)",
            "set IPv6 enable/disable",
            "set to true",
            "set to false");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigIpV6_cmd);     
#endif




    Add_CLI(ctree,SetConfigPrimaryVirtualIpAddress,I_AVAILABILITY_MANAGER,M_CONFIG_PRIMARY_VIRTUAL_IP_ADDRESS,
            SetConfigPrimaryVirtualIpAddress_cmd,
            "virtual-ip WORD dev WORD",
            "set virtual ip address",
            "enter a valid ip address",
            "device or interface name",
            "enter the device or interface name");

    cli_install(ctree, MODE_CONFIG_VIRTUAL_IP, PRIVILEGE_ADMIN, SetConfigPrimaryVirtualIpAddress_cmd);  



    Add_CLI(ctree,SetConfigGatewayIP,I_AVAILABILITY_MANAGER,M_CONFIG_GATEWAY_IP_ADDRESS,
            SetConfigGatewayIpAddress_cmd,
            "gateway-ip-address WORD",
            "set gateway ip address on either node",
            "enter a valid ip address for the gateway");

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, SetConfigGatewayIpAddress_cmd); 



#if 0
    Add_CLI(ctree, Restart,I_AVAILABILITY_MANAGER,M_RESTART_COMPONENT,
            Restart_cmd,
            "restart ( cli | cmgr | repmgr | dreapp) instance-id <1-16383>",        
            "restart command",
            "Command Line Interface Process",
            "Config Manager",
            "Replication Manager",
            "DRE Application"
            "instance id of running process ",
            "instance id range"
           );

    cli_install(ctree, MODE_CONFIG_AVLMGR, PRIVILEGE_ADMIN, Restart_cmd);

#endif

    Add_CLI(ctree,SetAvaMgrLogLevel,I_AVAILABILITY_MANAGER,M_AVAMGR_LOGLEVEL,
            SetAvaMgrLogLevel_cmd,
            "log-level (dre |asf | erlbf | avamgr | cli | cmgr)  (DEBUG | INFO | NOTICE | WARNING | ERROR | CRITICAL | FATAL) (disable | enable)",
            "command to set the log level",
            "dre application component",
            "asf component",
            "erlbf component",
            "avamgr component",
            "cli component",
            "cmgr component",
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

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, SetAvaMgrLogLevel_cmd);

    Add_CLI(ctree,SetAvaMgrLogchannel,I_AVAILABILITY_MANAGER,M_AVAMGR_LOGCHANNEL,
            SetAvaMgrLogchannel_cmd,
            "log-channel (dre |asf | erlbf | avamgr | cli | cmgr) (syslog | console | file WORD) (disable | enable)",
            "command to set the log channel",
            "dre application component",
            "asf component",
            "erlbf component",
            "avamgr component",
            "cli component",
            "cmgr component",
            "syslog channel",
            "user console",
            "file",
            "enter the filename",
            "disable - set the selected Log Level",
            "enable - unset the selected Log Level"
           );

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, SetAvaMgrLogchannel_cmd);

    Add_CLI(ctree, GetNodeStatus,I_AVAILABILITY_MANAGER,M_MAKE_NODE_STATUS,
            GetNodeStatus_cmd,
            "show node-status",        
            "show node-status command");

    cli_install(ctree, MODE_EXEC, PRIVILEGE_OPERATOR, GetNodeStatus_cmd);   
#endif
    return 0;
}
