/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 * CONTRACT: INTERNAL
 *
 *  ID: $Id: ual_config_mgnt.h,v 9.4.40.2.8.2.2.1 2014/11/21 06:37:47 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_config_mgnt.h,v $
 *  LOG: Revision 9.4.40.2.8.2.2.1  2014/11/21 06:37:47  jkchaitanya
 *  LOG: changes for IPSP configurations
 *  LOG:
 *  LOG: Revision 9.4.40.2.8.2  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.4.40.2.8.1  2014/09/16 09:34:54  jsarvesh
 *  LOG: Changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.4.40.2.6.1  2014/09/15 07:20:42  jsarvesh
 *  LOG: Changes done for removing Warnings
 *  LOG:
 *  LOG: Revision 9.4.40.2  2013/12/12 11:51:29  jsarvesh
 *  LOG: Changes done to send ASPINACTIVE and ASPDOWN when IWF comes down
 *  LOG:
 *  LOG: Revision 9.4.40.1  2013/11/18 11:40:20  jsarvesh
 *  LOG: Iwf_Productization Changes done for Dynamic UAL Configuration
 *  LOG:
 *  LOG: Revision 9.4  2008/06/30 14:05:02  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.3  2008/06/29 15:16:28  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.2  2008/06/20 10:37:05  mshanmugam
 *  LOG: Accelero CGI Phase I:D0260
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1.4.2  2005/01/06 04:46:13  snagesh
 *  LOG: Added memset to avoid core dump
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1.4.1  2005/01/04 14:58:45  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.1.4.1.2.1  2004/10/06 08:38:42  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.1.4.1  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 1.6  2002/07/11 20:48:51  ngoel
 *  LOG: add command
 *  LOG:
 *  LOG: Revision 1.5  2002/07/10 21:33:43  lbana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 1.4  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 1.3  2002/07/10 12:58:43  lbana
 *  LOG: make execute cmd func public
 *  LOG:
 *  LOG: Revision 1.2  2002/07/09 21:18:38  lbana
 *  LOG: Start MML procedures for UALs
 *  LOG:
 *
 ***************************************************************************/
#ifndef UAL_CONFIG_MGNT_H
#define UAL_CONFIG_MGNT_H
#include <dbc_serv.h>
#include "ual_intern.h"

/*
 * Working on user commands to configure
 * AS and ASP's
 *
 * 1.) Command to configure Routing keys.
 *
 * 2.) command to configure ASP's
 *
 */

#if defined(__cplusplus)
extern "C"
{
#endif

typedef enum
{
    UAL_CMD_UNKNOWN,
    UAL_CMD_ASP_UP,        /* Send ASP_UP */
    UAL_CMD_ASP_ACTIVE,    /* Send ASP_ACTIVE */
    UAL_CMD_ASP_INACTIVE,  /* Send ASP_INACTIVE */
    UAL_CMD_ASP_DOWN,      /* Send ASP_DOWN */
    UAL_CMD_BUILD_RTXT,    /* Build Routing Context */
    UAL_CMD_DUMP_AS_INFO,  /* Print AS Manager Table */
    UAL_CMD_DUMP_ASP_INFO,  /* Print ASP Table */
    UAL_CMD_GET_CFG,        /* Get UAL General Config */
    /* Olivier begin */
    UAL_CMD_REG_REQ,
    UAL_CMD_DREG_REQ
    /* Olivier end */
}
UAL_CMD;

typedef struct UALConfigVar *UAL_ConfigPriv;
typedef struct UAL_Config   *UAL_ConfigPtr;

typedef void (*UAL_CONSOLE_PROC)(DBC_Server *dbc, const char *cmdLine);

typedef ITS_BOOLEAN (*UAL_ConfigConstruct)(UAL_ConfigPtr);
typedef ITS_BOOLEAN (*UAL_ConfigDestruct)(UAL_ConfigPtr);
typedef ITS_BOOLEAN (*UAL_EXECUTE_CMD)(UAL_ConfigPriv info, 
                                       char **dumpStr);

struct UAL_Config 
{
    UAL_ConfigPriv      priv;     /*private variable for config*/
    UAL_ConfigConstruct construct;
    UAL_ConfigDestruct  destruct;
    UAL_EXECUTE_CMD     execute;
};

/*****************************************************************************
 *
 * Generic management data.
 *
 *****************************************************************************/
/*
 * alarm levels
 */
#ifndef ALARM
typedef enum
{
    ALARM_OFF,
    ALARM_DEFAULT,
    ALARM_DEBUG,
    ALARM_DETAIL
}
MGMT_AlarmLevel;
#else
#endif

typedef struct
{
    MGMT_AlarmLevel  alarmLevel;
    ITS_BOOLEAN      traceOn;     /* on(1), off(0) */
    ITS_CHAR         traceType[ITS_PATH_MAX];
    ITS_CHAR         traceOutput[ITS_PATH_MAX];
}
UALGeneralCfg;

#define MAX_STRING_SIZE 10

typedef struct
{
    ITS_CHAR       interworkingMode[MAX_STRING_SIZE];
    ITS_CHAR       protocolType[MAX_STRING_SIZE];
    ITS_CHAR       ipspExchangeType[MAX_STRING_SIZE];
    ITS_CHAR       ipspType[MAX_STRING_SIZE];
    ITS_CHAR       heartbeatFlag[MAX_STRING_SIZE];
    ITS_INT        heartbeatInterval;
    ITS_INT        ackTimer;
    ITS_INT        auditTimer;
    ITS_INT        pendingTimer;
    ITS_OCTET      protocolVersion;
    ITS_UINT       localPointCode;
}
UALConfigMgmt;

UALGeneralCfg* UAL_GetGeneralCfg();
int UAL_SetGeneralCfg(UALGeneralCfg *data);

/*
 * Initialize private variables, and set default member functions.
 */
UALDLLAPI ITS_BOOLEAN UAL_ConfigInit(UAL_ConfigPtr config);
UALDLLAPI ITS_BOOLEAN UAL_ConfigDest(UAL_ConfigPtr config);

/*
 * For ASP_UP/ASP_DOWN
 *    cmd = UAL_CMD_ASP_UP / UAL_CMD_ASP_DOWN
 *    id  = Transport ID
 *
 * For ASP_ACTIVE/ASP_INACTIVE
 *    cmd = UAL_CMD_ASP_ACTIVE/UAL_CMD_ASP_INACTIVE
 *    id  = Routing Key
 *
 */
UALDLLAPI void 
UAL_SetASPInfo(UAL_ConfigPtr conf, UAL_CMD cmd, ITS_UINT id);

/* 
 * Set Routing Key Route Style.
 */
UALDLLAPI void 
UAL_SetRoutingKeyRS(UAL_ConfigPtr conf, ITS_UINT rs);

/*
 * Set SS7_Family for routing info
 */
UALDLLAPI void 
UAL_SetRoutingKeyFamily(UAL_ConfigPtr conf, ITS_UINT fa);

/*
 * Set Routing Key value.
 * IN ASP the routing key value is local significance, 
 * where as in SG it has to be unique.
 */
UALDLLAPI void 
UAL_SetRoutingKeyRK(UAL_ConfigPtr conf, ITS_UINT rkey);

/*
 * Set DPC for Routing Key info
 */
UALDLLAPI void 
UAL_SetRoutingKeyDPC(UAL_ConfigPtr conf, ITS_UINT dpc);

/*
 * Set OPC for Routing Key info
 */
UALDLLAPI void 
UAL_SetRoutingKeyOPC(UAL_ConfigPtr conf, ITS_UINT opc);

/*
 * Set SSN for Routing Key Info
 */
UALDLLAPI void 
UAL_SetRoutingKeySSN(UAL_ConfigPtr conf, ITS_UINT ssn);

/*
 * Set SIO for Routing key info.
 */
UALDLLAPI void 
UAL_SetRoutingKeySIO(UAL_ConfigPtr conf, ITS_UINT sio);

/*
 * Set CIC for Routing key info.
 */
UALDLLAPI void 
UAL_SetRoutingKeyCIC(UAL_ConfigPtr conf, ITS_UINT cic);

/*
 * Set Traffic Mode for AS
 */
UALDLLAPI void 
UAL_SetRoutingKeyTM(UAL_ConfigPtr conf, ITS_UINT tm);

/*
 * Set Routing Key info With CIC Range.
 */
UALDLLAPI void 
UAL_SetRoutingKeyRange(UAL_ConfigPtr conf, ITS_UINT s, ITS_UINT e);

UALDLLAPI void 
UAL_Set_AS_DumpCmd(UAL_ConfigPtr conf);

UALDLLAPI void 
UAL_Set_ASP_DumpCmd(UAL_ConfigPtr conf);


ITS_INT 
ConfigureUalManagement(UALConfigMgmt *ualMgmt);

ITS_INT 
CreateApplicationServer(ITS_UINT rContext, ITS_CHAR *family,
                                UAL_TRAFFIC_TYPE trafficMode, ITS_UINT ni,
                                ITS_BOOLEAN isMember);

ITS_INT 
DeleteApplicationServer(ITS_UINT rContext);

ITS_INT 
CreateApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId, const char* ipAddress);

ITS_INT 
DeleteApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId);

ITS_INT 
EnableApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId);

ITS_INT 
DisableApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId);

ITS_INT 
GetApplicationServerState(ITS_UINT rContext);

ITS_INT 
GetApplicationServerProcessState(ITS_UINT rContext, ITS_INT aspId);

ITS_INT 
GetLocalApplicationServerInfo();

ITS_INT 
GetRemoteApplicationServerInfo();

ITS_INT 
GetLocalApplicationServerProcessInfo();

ITS_INT 
GetRemoteApplicationServerProcessInfo();

ITS_INT 
CreateApplicationServer(ITS_UINT rContext, ITS_CHAR *family,
                                UAL_TRAFFIC_TYPE trafficMode, ITS_UINT ni,
                                ITS_BOOLEAN isMember);

ITS_BOOLEAN SendASP_INACTIVE(UAL_ConfigPriv info);
//static ITS_BOOLEAN SendASP_DOWN(UAL_ConfigPriv info);

ITS_INT SendASPInactiveAndASPDown();
ITS_INT SendASPUP();
ITS_INT SendASPActiveFromApp();
ITS_INT SendASPACTIVE(ITS_UINT rid);
ITS_INT SendASPINACTIVE();

#if defined(__cplusplus)
}
#endif
 
#endif

