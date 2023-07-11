
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
// -------------------------------------------------------------------
// Date           AUTHOR                   COMMENTS
// Jun/6/2012     Govardhan Reddy          Initial Code
// 
// Add Entries similar to above for any modifications done
// -------------------------------------------------------------------
//
extern "C" {
#include "dq_cli.h"
#include "InterfaceDefs.h"
#include "CommonStructure.h"
#include "repmgr_cfg.h"
#include "Common.h"
    extern void send_receive_data(struct cli_def *cli,void* buf,int len,int cmdID,int interfaceID);
}

int SetReplicationFlag(struct cli_def *cli, char *command, char *argv[], int argc);
int SetReplLogLevel(struct cli_def *cli, char *command, char *argv[], int argc);


//#define DEBUG 1

int SetReplicationFlag(struct cli_def *cli, char *command, char *argv[], int argc)
{

    int i = 0;
    int cmdID;
    int interfaceID;
    struct ReplFlagReq repReq;

    cmdID = SetReplicationFlag_cmd;
    interfaceID = I_REPMGR_ID;

    while(argv[i]){

        if(!strcmp(argv[i],"enable")){
            repReq.bRepl  = true; 
        }else if(!strcmp(argv[i],"disable")){
            repReq.bRepl  = false; 
        }
        i++;
    }

    send_receive_data(cli,&repReq,sizeof(repReq),cmdID,interfaceID);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}


int SetReplLogLevel(struct cli_def *cli, char *command, char *argv[], int argc)
{

    int i = 0;
    struct ReplLogLevelReq repReq;
    int cmdID;
    int interfaceID;

    cmdID = SetReplLogLevel_cmd;
    interfaceID = I_REPMGR_ID;

    while(argv[i]){

        if(!strcmp(argv[i],"DEBUG")){
            repReq.bReplLogLvl = CONFIG_LOGLEVEL_DEBUG;
        }else if(!strcmp(argv[i],"INFO")){
            repReq.bReplLogLvl = CONFIG_LOGLEVEL_INFO;
        }else if(!strcmp(argv[i],"NOTICE")){
            repReq.bReplLogLvl = CONFIG_LOGLEVEL_NOTICE;
        }else if(!strcmp(argv[i],"CRITICAL")){
            repReq.bReplLogLvl = CONFIG_LOGLEVEL_CRITICAL;
        }else if(!strcmp(argv[i],"FATAL")){
            repReq.bReplLogLvl = CONFIG_LOGLEVEL_FATAL;
        }else if(!strcmp(argv[i],"enable")){
            repReq.bLogFlag  = true; 
        }else if(!strcmp(argv[i],"disable")){
            repReq.bLogFlag  = false;
        }
        i++;
    }

    send_receive_data(cli,&repReq,sizeof(repReq),cmdID,interfaceID);

#ifdef CLI_DEBUG
    cli_print(cli, "called %s with \"%s\"", __FUNCTION__, command);
    for (i = 0; i < argc; i++)
        cli_print(cli, "        %s", argv[i]);

#endif
    return CLI_OK;

}

int repmgr_cli_init(struct cli_def *ctree) {
#if 0    
    Add_CLI(ctree, SetReplicationFlag, I_REPMGR_ID, M_REPMGR_REPLFLAG, SetReplicationFlag_cmd,
            "repmgr replication (disable|enable)", 
            "Replication manager command",
            "This Command is used to set the replication flag",
            "disable - disables the replication activity",
            "enable - enables the replication activitty");   

    cli_install(ctree, MODE_CONFIG_REPMGR, PRIVILEGE_ADMIN, SetReplicationFlag_cmd);    

    Add_CLI(ctree, SetReplLogLevel, I_REPMGR_ID, M_REPMGR_LOGLEVEL, SetReplLogLevel_cmd,
            "repmgr setLogLevel (DEBUG|INFO|NOTICE|CRITICAL|FATAL) (disable|enable)", 
            "Replication manager command",
            "This Command is used to set the replication managers loglevel",
            "DEBUG - Messages above DEBUG Level ",
            "INFO  - Messages above INFO Level ",
            "NOTICE - Messages above NOTICE Level ",
            "CRITICAL  -Messages above CRITICAL Level",
            "FATAL - Messages above FATAL Level",
            "disable - sets the selected Log Level",
            "enable -  unsets the selected log level");     

    cli_install(ctree, MODE_CONFIG_REPMGR, PRIVILEGE_OPERATOR, SetReplLogLevel_cmd);    
#endif
    return 0;
}




