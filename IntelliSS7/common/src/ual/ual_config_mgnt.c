
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
 *  ID: $Id: ual_config_mgnt.c,v 9.15.4.1.4.3.28.3.8.5.2.1 2014/11/21 06:37:47 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_config_mgnt.c,v $
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.5.2.1  2014/11/21 06:37:47  jkchaitanya
 *  LOG: changes for IPSP configurations
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.5  2014/11/17 04:59:50  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.4  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.3  2014/09/18 10:29:21  jsarvesh
 *  LOG: Reverted back valigrind fix
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.2  2014/09/18 10:05:19  jsarvesh
 *  LOG: changes done for Handling ASR message for Voice/SMS calls
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.8.1  2014/09/16 09:34:54  jsarvesh
 *  LOG: Changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3.6.1  2014/09/15 07:20:42  jsarvesh
 *  LOG: Changes done for removing Warnings
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.3  2013/12/12 11:51:29  jsarvesh
 *  LOG: Changes done to send ASPINACTIVE and ASPDOWN when IWF comes down
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.2  2013/12/10 13:40:10  jsarvesh
 *  LOG: IwfProductization Changes done to add Error Handling for UAL Configuration
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3.28.1  2013/11/18 11:40:19  jsarvesh
 *  LOG: Iwf_Productization Changes done for Dynamic UAL Configuration
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.3  2010/06/26 19:55:28  ssingh
 *  LOG: fixing xml persistancy issue redundant #3131
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.2  2010/06/10 13:14:27  chandrashekharbs
 *  LOG: Fix for Issue id 2946
 *  LOG:
 *  LOG: Revision 9.15.4.1.4.1  2010/02/22 12:17:40  rajeshak
 *  LOG: Fix for Issue 2490 (MML coredump Issue)
 *  LOG:
 *  LOG: Revision 9.15.4.1  2009/03/24 04:10:23  ssodhi
 *  LOG: enable_u_astbl_cmd_on_asp_side cmd
 *  LOG:
 *  LOG: Revision 9.15  2008/06/30 14:04:48  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.14  2008/06/29 15:16:19  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.13  2008/06/20 10:36:27  mshanmugam
 *  LOG: Accelero CGI Phase I:D0260-D0390
 *  LOG:
 *  LOG: Revision 9.12  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.11.2.2  2007/07/06 06:58:35  pspl
 *  LOG: (PSPL, abhijeet) Support added for get/set audTimer from/to XML for SCON-DAUD feature
 *  LOG:
 *  LOG: Revision 9.11.2.1  2007/05/25 06:24:58  pspl
 *  LOG: Added code to get(u_get_timers) and set(u_set_timers) UAL timers from MML.
 *  LOG: (Vipul)
 *  LOG:
 *  LOG: Revision 9.11  2007/01/17 09:23:21  yranade
 *  LOG: Warning removals.
 *  LOG:
 *  LOG: Revision 9.10  2005/12/09 03:49:50  clin
 *  LOG: Add SSNM pegs for M3UA.
 *  LOG:
 *  LOG: Revision 9.9  2005/12/08 03:37:20  clin
 *  LOG: fix bug #2482
 *  LOG:
 *  LOG: Revision 9.8  2005/11/30 23:48:53  clin
 *  LOG: change ITS_TRACE to UAL trace.
 *  LOG:
 *  LOG: Revision 9.7  2005/11/30 15:12:02  clin
 *  LOG: make debug flag works to display ASP/IPSP client its own routing info.
 *  LOG:
 *  LOG: Revision 9.6  2005/11/23 20:47:00  clin
 *  LOG: fix bug #2481
 *  LOG:
 *  LOG: Revision 9.5  2005/11/18 23:31:24  cbashyam
 *  LOG: Bug fix for Bug ID : 2585
 *  LOG: Changed all the text information for u_get_gen_peg
 *  LOG: so that the text information matches the help file
 *  LOG:
 *  LOG: Revision 9.4  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.3  2005/05/05 06:07:00  adutta
 *  LOG: Fix for #1769
 *  LOG:
 *  LOG: Revision 9.2  2005/04/05 10:15:43  adutta
 *  LOG: Fix for Bug# 1536/ 1542/ 1661
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.9  2005/02/22 11:09:37  adutta
 *  LOG: Fix for Bug#1541
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.8  2005/02/22 05:17:30  adutta
 *  LOG: Linux fix for mml command (u_asptbl etc.)
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.6  2005/02/09 12:41:54  adutta
 *  LOG: Bug fix for mml (#1458, #1453)
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.5  2005/02/03 09:06:00  craghavendra
 *  LOG: Fix for GetGeneralCfg.
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.4  2005/01/11 12:39:06  craghavendra
 *  LOG: Syslog Enhancements.
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.3  2005/01/06 04:46:13  snagesh
 *  LOG: Added memset to avoid core dump
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.2  2005/01/04 15:06:02  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.4.2.3.16.1  2004/12/09 15:24:24  snagesh
 *  LOG: Modifications for Chinese variant
 *  LOG:
 *  LOG: Revision 7.4.2.3  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.4.2.2  2003/10/15 20:50:57  lbana
 *  LOG: fixes for SG crash on reconnects with serveral ASPs
 *  LOG:
 *  LOG: Revision 7.4.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.4  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.3  2002/11/15 18:32:21  ngoel
 *  LOG: return error for duplicate rkey
 *  LOG:
 *  LOG: Revision 7.2.2.2  2002/12/26 23:32:27  lbana
 *  LOG: buge fixes in ual in IPSP mode testing
 *  LOG:
 *  LOG: Revision 7.2.2.1  2002/11/18 18:50:49  ngoel
 *  LOG: use default linkset/linkcode for adding rkey
 *  LOG:
 *  LOG: Revision 7.2  2002/09/06 21:04:51  yranade
 *  LOG: inline is not a C89 keyword.  Don't use it.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 1.16  2002/07/26 13:10:37  ngoel
 *  LOG: take alarm level as string
 *  LOG:
 *  LOG: Revision 1.15  2002/07/19 18:52:15  ngoel
 *  LOG: add support for dpc-ni route
 *  LOG:
 *  LOG: Revision 1.14  2002/07/18 12:59:24  ngoel
 *  LOG: add invalid argument print for MML
 *  LOG:
 *  LOG: Revision 1.13  2002/07/12 18:23:29  ngoel
 *  LOG: free memory for dumpStr
 *  LOG:
 *  LOG: Revision 1.12  2002/07/12 18:04:24  ngoel
 *  LOG: remove warnings
 *  LOG:
 *  LOG: Revision 1.11  2002/07/12 16:08:20  ngoel
 *  LOG: after some testing
 *  LOG:
 *  LOG: Revision 1.10  2002/07/11 20:43:48  ngoel
 *  LOG: work in progress
 *  LOG:
 *  LOG: Revision 1.9  2002/07/11 19:34:08  ngoel
 *  LOG: work in progress
 *  LOG:
 *  LOG: Revision 1.8  2002/07/10 21:33:43  lbana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 1.7  2002/07/10 21:32:36  ngoel
 *  LOG: work in progress
 *  LOG:
 *  LOG: Revision 1.6  2002/07/10 18:30:48  ngoel
 *  LOG: add rkey works
 *  LOG:
 *  LOG: Revision 1.5  2002/07/10 14:21:42  ngoel
 *  LOG: add ual console function
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
 ***************************************************************************/
#include <ual_config_mgnt.h>
#include <its_ual.h>
#include <its_route.h>
#include <engine.h>
#include "IwfErrorResp.h"

ITS_BOOLEAN UAL_ExecuteConfigCmd(UAL_ConfigPriv info, char **dumpStr);

/*
 * Data type to get info from user commands
 * and send it to the UAL manager.
 * 
 * NOT For The User to invoke these memebers.
 */
struct UALConfigVar 
{
    ITS_INT    configCmd;   /* Configuration Command */

    union
    {
        struct              /* For ASP_UP   asp = ASP Transport ID */
        {                   /* For Active   asp = Routing key */
            ITS_UINT asp;   /* For Inactive asp = Routing Key */  
        }                   /* For ASP_Down asp = ASP Transport ID */
        asp_info;

        struct
        {
            ITS_UINT  rStyle;    /* Set Route style */
            ITS_UINT  rkey;      /* Set Routing Key value */
            ITS_UINT  dpc;       /* Set routing key DPC */
            ITS_UINT  opc;       /* Set routing key OPC */
            ITS_UINT  ssn;       /* Set SSN */
            ITS_UINT  sio;       /* Set SIO */
            ITS_UINT  cic;       /* Set CIC */
            ITS_UINT  start;     /* Need to work on this */
            ITS_UINT  end;
            ITS_UINT  family;
            ITS_UINT  tMode;     /* AS Traffic Mode */ 
        }
        rk_info;
    }
    config;
};

#define UAL_CONFIG_PRIV_CMD(x)      (((UAL_ConfigPriv)x)->configCmd)
#define UAL_CONFIG_PRIV_EXECUTE(x)  (((UAL_ConfigPriv)x)->execute)
#define UAL_CONFIG_PRIV_ASP_INFO(x) (((UAL_ConfigPriv)x)->config.asp_info)
#define UAL_CONFIG_PRIV_RK_INFO(x)  (((UAL_ConfigPriv)x)->config.rk_info)
/*
 * Construct UAL_Config class object.
 */
ITS_BOOLEAN UAL_ConfigInit(UAL_ConfigPtr config)
{
    ITS_BOOLEAN ret = ITS_FALSE;

    config->construct = UAL_ConfigInit;  /* use less */
    config->destruct  = UAL_ConfigDest;

    config->priv = (struct UALConfigVar *)
                         calloc(1, sizeof(struct UALConfigVar));

    config->execute = UAL_ExecuteConfigCmd;

    ret = ITS_TRUE;

    return ret;
}

/*
 * Destruct UAL_Config class object.
 */
ITS_BOOLEAN UAL_ConfigDest(UAL_ConfigPtr config)
{
    ITS_BOOLEAN ret = ITS_FALSE;

    if(config->priv)
    {
        free(config->priv);
    }

    config->priv = NULL;

    ret = ITS_TRUE;

    return ret;
}

void UAL_SetASPInfo(UAL_ConfigPtr conf, UAL_CMD cmd, ITS_UINT id)
{
    UAL_CONFIG_PRIV_CMD(conf->priv)          = cmd;
    UAL_CONFIG_PRIV_ASP_INFO(conf->priv).asp = id;
}

void UAL_SetRoutingKeyRS(UAL_ConfigPtr conf, ITS_UINT rs)
{
    UAL_CONFIG_PRIV_CMD(conf->priv)  = UAL_CMD_BUILD_RTXT;  /* Routing Context */
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).rStyle = rs;        /* Route Style */
}

void UAL_SetRoutingKeyFamily(UAL_ConfigPtr conf, ITS_UINT fa)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).family = fa;
} 

void UAL_SetRoutingKeyRK(UAL_ConfigPtr conf, ITS_UINT rkey)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).rkey = rkey;
}

void UAL_SetRoutingKeyDPC(UAL_ConfigPtr conf, ITS_UINT dpc)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).dpc = dpc;                 /* Set DPC */
}

void UAL_SetRoutingKeyOPC(UAL_ConfigPtr conf, ITS_UINT opc)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).opc = opc;                 /* Set OPC */
}

void UAL_SetRoutingKeySSN(UAL_ConfigPtr conf, ITS_UINT ssn)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).ssn = ssn;
}


void UAL_SetRoutingKeySIO(UAL_ConfigPtr conf, ITS_UINT sio)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).sio = sio;
}

void UAL_SetRoutingKeyCIC(UAL_ConfigPtr conf, ITS_UINT cic)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).cic = cic;
}

void UAL_SetRoutingKeyTM(UAL_ConfigPtr conf, ITS_UINT tm)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).tMode = tm;   /* AS Traffic Mode */
}

void UAL_SetRoutingKeyRange(UAL_ConfigPtr conf, ITS_UINT s, ITS_UINT e)
{
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).start = s;
    UAL_CONFIG_PRIV_RK_INFO(conf->priv).end   = e;
}

void UAL_Set_AS_DumpCmd(UAL_ConfigPtr conf)
{
    UAL_CONFIG_PRIV_CMD(conf->priv) = UAL_CMD_DUMP_AS_INFO;
}

void UAL_Set_ASP_DumpCmd(UAL_ConfigPtr conf)
{
    UAL_CONFIG_PRIV_CMD(conf->priv) = UAL_CMD_DUMP_ASP_INFO;
}

/*
 * Set M3UA Message Header:
 *
 * Input/Output : ITS_UAL_IE ie
 * Input        : cl -Message Class
 *              : tm -Traffic Maintenance
 */
void
SetM3UA_MsgHeader(ITS_UAL_IE *ie, ITS_UINT cl, 
                  ITS_UINT tm)
{
    ie->param_id     = UAL_PRM_MSG_HDR;
    ie->param_length = sizeof(UAL_MSG_HDR);

    ie->param_data.msgHeader.msgClass = cl;
    ie->param_data.msgHeader.msgType  = tm;
    ie->param_data.msgHeader.version  = UAL_GL_VERSION;
    ie->param_data.msgHeader.reserved = 0x00;
}

/*
 * Set Traffic Mode IE
 *
 * Input/Output : ITS_UAL_IE ie
 *
 * Input        : Traffic Mode
 */
void
SetM3UA_TrafficModeParam(ITS_UAL_IE *ie, ITS_UINT tm)
{
    ie->param_id = UAL_PRM_TRAFFIC_MODE;
    ie->param_length = sizeof(UAL_TRAFFIC_MODE);

    ie->param_data.trafMode.tm = (tm & 0xFF);
}
 
static ITS_BOOLEAN SendASP_UP(UAL_ConfigPriv info)
{
    ITS_BOOLEAN ret = ITS_FALSE; /* Return val */
    ASP_Entry*  asp = NULL;      /* ASP_Entry info from ASP_Table */

    UAL_DEBUG(("SendASP_UP Entry"));
    if(info != NULL)
    {
        if(ASPTable_FindEntry(UAL_CONFIG_PRIV_ASP_INFO(info).asp, &asp) 
                              == ITS_SUCCESS)
        {
            UAL_DEBUG(("Find ASP Entry success"));
            if(UAL_SendASPUP(asp) == ITS_SUCCESS)
            {
                UAL_DEBUG(("Send ASP UP success"));
                ret = ITS_TRUE;
            }
        }
    }

    UAL_DEBUG(("SendASP_UP Exit"));
    return ret;
}

static ITS_BOOLEAN SendASP_ACTIVE(UAL_ConfigPriv info)
{
    UAL_DEBUG(("SendASP_ACTIVE Entry"));
    ITS_BOOLEAN ret    = ITS_FALSE;
    RK_Context  *rctxt = NULL;
    ITS_UAL_IE  m3uaIE[32];
    ITS_INT     count;
    ITS_EVENT   event;

    ITS_EVENT_INIT(&event, ITS_FIRST_USER_SRC, 256); /* Init event */
    memset(m3uaIE, 0, sizeof(ITS_UAL_IE) * 32);      /* Init m3ua ies */

    if(info == NULL)
    {
        UAL_ERROR(("UAL_ConfigPriv is NULL, SendASP_ACTIVE failed"));
        return ITS_FALSE;
    }

    ITS_EVENT_INIT(&event, ITS_FIRST_USER_SRC, 256); /* Init event */
    memset(m3uaIE, 0, sizeof(ITS_UAL_IE) * 32);      /* Init m3ua ies */
 
    if( (rctxt = RKManager_FindEntry(UAL_CONFIG_PRIV_ASP_INFO(info).asp)) != NULL)
    {
        ret = ITS_TRUE;
        UAL_DEBUG(("RoutingInfo found, setting ret to %d\n", ret));
    }

    if(ret)
    {
        ITS_UINT rkey = 0;
        ITS_INT  tmp  = 0;

        rkey  = UAL_CONFIG_PRIV_ASP_INFO(info).asp;
        count = 0;

        SetM3UA_MsgHeader(&m3uaIE[count++], UAL_CLASS_ASPTM, UAL_MSG_ASPAC);
        SetM3UA_TrafficModeParam(&m3uaIE[count++], rctxt->trafficMode);

        m3uaIE[count].param_id = UAL_PRM_ROUT_CTX;

        tmp = UAL_EncodeRoutingContext(m3uaIE[count].param_data.rCtxt.rCtxt,
                                       &m3uaIE[count].param_length, &rkey, 1);

        count++;

        if(tmp == ITS_SUCCESS) 
        {
            UAL_DEBUG(("Encoding of Routing Context Success"));
            if( (tmp = UAL_EncodeMsg(m3uaIE, count, &event, &UAL_ASPAC_Desc))
                                    == ITS_SUCCESS)
             {
                 UAL_DEBUG(("Encoding of Msg Success Passing Msg to LayerMgmt"));
                 tmp = UAL_HandleLayerMgntMsg(&event);
             }
        }


        if(tmp != ITS_SUCCESS)
        {
            ret = ITS_FALSE;
            UAL_DEBUG(("UAL_HandleLayerMgntMsg Failed, setting ret to %d\n", ret));
        }
    }

    ITS_EVENT_TERM(&event);

    UAL_DEBUG(("Return Value : %d\n", ret));
    return ret;
}

ITS_BOOLEAN SendASP_INACTIVE(UAL_ConfigPriv info)
{
    UAL_DEBUG(("SendASP_INACTIVE : Sending ASP INACTIVE"));
    ITS_BOOLEAN ret = ITS_FALSE;
    RK_Context  *rctxt = NULL;
    ITS_UAL_IE  m3uaIE[32];
    ITS_INT     count;
    ITS_EVENT   event;

    if(info == NULL)
    {
        return ITS_FALSE;
    }
    ITS_EVENT_INIT(&event, ITS_FIRST_USER_SRC, 256); /* Init event */
    memset(m3uaIE, 0, sizeof(ITS_UAL_IE) * 32);      /* Init m3ua ies */
 
    if( (rctxt = RKManager_FindEntry(UAL_CONFIG_PRIV_ASP_INFO(info).asp)) 
         != NULL)
    {
        ret = ITS_TRUE;
    }

    if(ret)
    {
        ITS_UINT rkey = 0;
        ITS_INT  tmp  = 0;

        rkey = UAL_CONFIG_PRIV_ASP_INFO(info).asp;

        SetM3UA_MsgHeader(&m3uaIE[0], UAL_CLASS_ASPTM, UAL_MSG_ASPIA);
        /*SetM3UA_TrafficModeParam(&m3uaIE[1], rctxt->trafficMode);*/

        m3uaIE[1].param_id = UAL_PRM_ROUT_CTX;

        tmp = UAL_EncodeRoutingContext(m3uaIE[1].param_data.rCtxt.rCtxt,
                                       &m3uaIE[1].param_length, &rkey, 1);

        count = 2;
        if(tmp == ITS_SUCCESS) 
        {
            if( (tmp = UAL_EncodeMsg(m3uaIE, count, &event, &UAL_ASPIA_Desc))
                 == ITS_SUCCESS)
            {
                tmp = UAL_HandleLayerMgntMsg(&event);
            }
        }

        if(tmp != ITS_SUCCESS)
        {
            ret = ITS_FALSE;
        }
    }
 
    ITS_EVENT_TERM(&event);

    return ret;
}

static ITS_BOOLEAN SendASP_DOWN(UAL_ConfigPriv info)
{
    UAL_DEBUG(("SendASP_DOWN : Sending ASP DOWN"));
    ITS_BOOLEAN ret = ITS_FALSE;
    ITS_UAL_IE  m3uaIE[1];
    ITS_EVENT   event;

    if(info == NULL)
    {
        return ITS_FALSE;
    }

    ITS_EVENT_INIT(&event, ITS_FIRST_USER_SRC, 256); /* Init event */
    memset(m3uaIE, 0, sizeof(ITS_UAL_IE) * 1);       /* Init m3ua ies */
 
    SetM3UA_MsgHeader(&m3uaIE[0], UAL_CLASS_ASPSM, UAL_MSG_ASPDN);

    if(UAL_EncodeMsg(m3uaIE, 1, &event, &UAL_ASPDN_Desc)
                    == ITS_SUCCESS)
    {
        ret = ITS_TRUE;
    }

    if(ret)
    {
        if(UAL_HandleLayerMgntMsg(&event) != ITS_SUCCESS)
        {
            ret = ITS_FALSE;
        }
    }

    ITS_EVENT_TERM(&event);

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add Routing Key Route Info to the Resource Manager.
 *
 *  Input Parameters:
 *      ROUTE_MatchInfo *rinfo.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or !ITS_SUCCESS.
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * adutta    04-05-2005  BugId:1536    Check for Is Member.
 *
 *
 *  See Also:
 *
 ****************************************************************************/
static ITS_INT 
AddRoutingKeyInfoToResMan(ROUTE_MatchInfo *rinfo, UAL_ConfigPriv info)
{
    int  ret;
    char *section = NULL; /* goes to the global section */
    char tmp[ITS_PATH_MAX];
    TRANSPORT_Control *tc   = TRANSPORT_FindTransport(UAL_MANAGER_INSTANCE);
    RESFILE_Manager *appRes = TRANSPORT_RES(tc);

    TRANSPORT_UnfindTransport(tc);

    if(appRes == NULL)
    {
        return !ITS_SUCCESS;
    }

    memset(tmp, 0, sizeof(char) * ITS_PATH_MAX);

    ret = RESFILE_AddKeyValue(appRes, section,
                               ROUTE_TYPE_STRING,
                               ROUTE_TYPE_ROUTING_KEY_STRING);

    switch(rinfo->basic.style)
    {
        case ROUTE_DPC_NI :
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ROUTE_STYLE_STRING,
                                      ROUTE_STYLE_DPC_NI_STRING);

            break;

        case ROUTE_DPC_SIO:
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ROUTE_STYLE_STRING,
                                      ROUTE_STYLE_DPC_SIO_STRING);
            break;

        case ROUTE_DPC_OPC_SIO:
             ret = RESFILE_AddKeyValue(appRes, section, 
                                      ROUTE_STYLE_STRING,
                                      ROUTE_STYLE_DPC_OPC_SIO_STRING);
              break;

        case ROUTE_DPC_SIO_SSN:
            ret = RESFILE_AddKeyValue(appRes, section, 
                                      ROUTE_STYLE_STRING,
                                      ROUTE_STYLE_DPC_OPC_SIO_STRING);
            break;

        case ROUTE_DPC_OPC_SIO_SSN:
            ret = RESFILE_AddKeyValue(appRes, section, 
                                      ROUTE_STYLE_STRING,
                                      ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING);
            break;

        default:
             ret = -1;
             UAL_ERROR(("Unsupported Routing style through DBG Console:\n"));
    }

    if(ret != ITS_SUCCESS)
    {
        return ret;
    }

    if(rinfo->basic.type == ROUTING_KEY_ROUTE)
    {
        sprintf(tmp, "0x%08x", rinfo->rkey);

        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTING_KEY_STRING,
                                  tmp);
    }

    /* add the point code */
    sprintf(tmp, "0x%08x", rinfo->basic.dpc);
    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_POINT_CODE_STRING,
                              tmp);

    if(rinfo->basic.family == FAMILY_ANSI)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_ANSI_STRING);
    }
    else if(rinfo->basic.family == FAMILY_ITU)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CCITT_STRING);
    }
    else if(rinfo->basic.family == FAMILY_CHINA)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CHINA_STRING);
    }
    else if(rinfo->basic.family == FAMILY_JAPAN)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_JAPAN_STRING);
    }

    switch(rinfo->basic.style)
    {
        case ROUTE_DPC_NI :
            sprintf(tmp, "%02x", rinfo->basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      NI_STRING,
                                      tmp);
            break;

        case ROUTE_DPC_SIO:
            sprintf(tmp, "%02x", rinfo->basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);
            break;

        case ROUTE_DPC_OPC_SIO:
            sprintf(tmp, "%08x", rinfo->basic.criteria.opc);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ORIG_POINT_CODE_STRING,
                                      tmp);

            sprintf(tmp, "0x%02x", rinfo->basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);
            break; 

        case ROUTE_DPC_SIO_SSN:
            /* sio */
            sprintf(tmp, "0x%02x", rinfo->basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);

            /* ssn */
            sprintf(tmp, "0x%02x", rinfo->basic.criteria.ssn);
            ret = RESFILE_AddKeyValue(appRes, section,
                                  SSN_STRING,
                                  tmp);

            break;

        case ROUTE_DPC_OPC_SIO_SSN:
            /* opc */
            sprintf(tmp, "0x%08x", rinfo->basic.criteria.opc);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ORIG_POINT_CODE_STRING,
                                      tmp);

            /* sio */
            sprintf(tmp, "0x%02x", rinfo->basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);

            /* ssn */
            sprintf(tmp, "0x%02x", rinfo->basic.criteria.ssn);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SSN_STRING,
                                      tmp);

            break;

        default:
            break;
    } 

    /*
     * Add AS Info to the UAL_Manager section.
     */ 
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_AS_INFO_STRING, "begin");

    sprintf(tmp, "%08x", UAL_CONFIG_PRIV_RK_INFO(info).rkey);
    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              ROUTING_KEY_STRING, tmp);

    if (UAL_CONFIG_PRIV_RK_INFO(info).tMode == UAL_OVERRIDE_MODE)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_AS_TRAFFIC_MODE_STRING, 
                                  UAL_OVERIDE_MODE_STRING);
    }
    else if (UAL_CONFIG_PRIV_RK_INFO(info).tMode == UAL_LOADSHARE_MODE)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_AS_TRAFFIC_MODE_STRING, 
                                  UAL_LOAD_SHARE_MODE_STRING );
    }
    else if (UAL_CONFIG_PRIV_RK_INFO(info).tMode == UAL_BROADCAST_MODE)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                  UAL_AS_TRAFFIC_MODE_STRING, 
                                 UAL_BROADCAST_MODE_STRING);
    }

    if (UAL_GL_ITW_MODE == UAL_ITW_ASP)
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_IS_MEMBER_STRING, "yes");
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                                      UAL_IS_MEMBER_STRING, "no");
    }


    ret = RESFILE_AddKeyValue(appRes, UAL_MGNT_CLASS_NAME,
                              UAL_AS_INFO_STRING, "end");

    return ret;
}

static ITS_BOOLEAN SetRoutingKeyInfo(UAL_ConfigPriv info)
{
    ITS_BOOLEAN     ret = ITS_FALSE;
    ROUTE_MatchInfo rinfo;
    ITS_UINT        rkey = 0;
    TRANSPORT_Control *tc = TRANSPORT_FindTransport(UAL_MANAGER_INSTANCE);
    RESFILE_Manager   *appRes = TRANSPORT_RES(tc);

    memset(&rinfo, 0, sizeof(rinfo));

    TRANSPORT_UnfindTransport(tc);

    if(info == NULL)
    {
        return ret;
    }

    /* Building Static Routes using DBG Console.
     *
     * 1.) Add Routing key info to the Resource Manager.
     * 2.) Add AS Info to the RK Manger.
     */

    /* Set Routing Key info */
    rinfo.basic.type  = ROUTING_KEY_ROUTE;
    rinfo.rkey = UAL_CONFIG_PRIV_RK_INFO(info).rkey;

    if(UAL_CONFIG_PRIV_RK_INFO(info).rStyle)
    {
        rinfo.basic.style = UAL_CONFIG_PRIV_RK_INFO(info).rStyle;
    }

    rinfo.basic.dpc    = UAL_CONFIG_PRIV_RK_INFO(info).dpc;    /* Set DPC */
    rinfo.basic.family = UAL_CONFIG_PRIV_RK_INFO(info).family; /* Set SS7 Family */

    if(UAL_CONFIG_PRIV_RK_INFO(info).opc)
    {
        rinfo.basic.criteria.opc = UAL_CONFIG_PRIV_RK_INFO(info).opc;
    }

    if(UAL_CONFIG_PRIV_RK_INFO(info).ssn)
    {
        rinfo.basic.criteria.ssn = UAL_CONFIG_PRIV_RK_INFO(info).ssn;
    }

    if(UAL_CONFIG_PRIV_RK_INFO(info).sio)
    {
        rinfo.basic.criteria.sio = UAL_CONFIG_PRIV_RK_INFO(info).sio;
    }

    if(UAL_CONFIG_PRIV_RK_INFO(info).start && UAL_CONFIG_PRIV_RK_INFO(info).end)
    {
        rinfo.basic.criteria.range.begin = UAL_CONFIG_PRIV_RK_INFO(info).start;
        rinfo.basic.criteria.range.end   = UAL_CONFIG_PRIV_RK_INFO(info).end;
    }

    rinfo.linkSet = ITS_SS7_DEFAULT_LINK_SET;
    rinfo.linkCode = ITS_SS7_DEFAULT_LINK_CODE;

    ROUTE_Info ** pRoute = NULL;

    /* Whizible Issue 2490 fix */
    if(ROUTE_FindRoutingKeyInfo(rinfo.rkey, &pRoute) == ITS_SUCCESS)
    {
        /* Routing key is already present in Resource manager */
        UAL_WARNING(("DUPLICATE ROUTE Entry found \n"));
        return ITS_EDUPLENTRY;
    }

    if(rkey == 0)
    {
        if(ROUTE_AddRoutingKeyInfo(rinfo.rkey, &rinfo) == ITS_SUCCESS)
        {
            ret = ITS_TRUE;
        }
       
        if(AddRoutingKeyInfoToResMan(&rinfo, info) == ITS_SUCCESS)
        {
            ret = ITS_TRUE;
        }
        

        if(ret)
        {
        
            ret = RESFILE_Rewind(TRANSPORT_RES(tc), TRANSPORT_NAME(tc));
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }


            if(UAL_AddASInfoToASManager(appRes, ITS_TRUE) != ITS_SUCCESS)
            {
                ret = ITS_FALSE;
            }
            else
            {
                ret = ITS_TRUE;
            }
        }
    } 

    return ret;
}

ITS_BOOLEAN UAL_ExecuteConfigCmd(UAL_ConfigPriv info, char **dumpStr)
{
    ITS_BOOLEAN ret = ITS_FALSE;

    /* Acquire Lock for Updating UAL management info */
    if( (ret = MUTEX_AcquireMutex(&__ualGuard)) != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_ExecuteConfigCmd: Failed to acquire mutex.\n"));
    }

    switch(info->configCmd)
    {
        case UAL_CMD_ASP_UP:
            ret = SendASP_UP(info);
            break;

        case UAL_CMD_ASP_ACTIVE:
            ret = SendASP_ACTIVE(info);
            break;

        case UAL_CMD_ASP_INACTIVE:
            ret = SendASP_INACTIVE(info);
            break;
        case UAL_CMD_ASP_DOWN:
            ret = SendASP_DOWN(info);
            break;

        case UAL_CMD_BUILD_RTXT:
            ret = SetRoutingKeyInfo(info);
            break;

        case UAL_CMD_DUMP_AS_INFO:
            /*if(*dumpStr != NULL)
            {
                free(*dumpStr);
            }*/
            UAL_DumpASTable(dumpStr);
 
            break;

        case UAL_CMD_DUMP_ASP_INFO:
            /*if(*dumpStr != NULL)
            {
                free(*dumpStr);
            }*/
            UAL_DumpASPTable(dumpStr);

            break;

         case UAL_CMD_GET_CFG :
            UAL_DumpCfg(dumpStr);
            break;

        default:
            /* Print Error Message */
            break;
    }

    /* Release Lock */
    if( (MUTEX_ReleaseMutex(&__ualGuard)) != ITS_SUCCESS)
    {
        UAL_ERROR(("UAL_ExecuteConfigCmd: Failed to release mutex.\n"));
        return !ITS_SUCCESS;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
UALGeneralCfg*
UAL_GetGeneralCfg()
{
    UALGeneralCfg *ret;

    ret = calloc(1, sizeof(UALGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_DEBUG) &&
                   (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      0) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      1) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_WARNING) &&
                   (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      0) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      1) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_ERROR) &&
                   (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      0) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      1) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_CRITICAL) &&
                   (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      0) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      1) ||
                    TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      2)));
    ret->alarmLevel = UAL_AlarmLevel;


    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
UAL_SetGeneralCfg(UALGeneralCfg *data)
{
    if(UAL_TraceData == NULL)
    {
        return !ITS_SUCCESS;
    }

    UAL_AlarmLevel = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      UAL_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      UAL_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      UAL_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      UAL_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       UAL_DEBUG_STRING,
                                     data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      data->traceType, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(UAL_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
            TRACE_SetLevelOnOffByName(UAL_TraceData,
                                      data->traceType, ITS_FALSE);
        }
    }
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * adutta    04-05-2005  BugId:1542    u_reg_req/u_dereg_req for ASP only.
 *                       BugId:1661    Vaild trasport Id check. 
 *                                    
 * gdevanand 05-05-2005  BugId:1769    u_add_rkey : check for failure leg. 
 *
 *  See Also:
 *
 ****************************************************************************/
extern ITS_BOOLEAN u_astbl_cmd_enabled_on_asp_side;
void
UAL_Console(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;
    ITS_BOOLEAN ret_val;
    ITS_UINT i; 
    int pc, ssn, ni;
    struct UAL_Config cfg;
    char *dumpStr = NULL;
    ASP_Entry*  asp = NULL;

    UAL_ConfigInit(&cfg);

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "u_get_gen_cfg", "UAL Get General Config", "", ""))
    {
        UALGeneralCfg *cfg;
        cfg =  UAL_GetGeneralCfg();

        sprintf(buf, "*********** UAL General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "    Alarm Level = MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "    Alarm Level = INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "    Alarm Level = OFF\n");
            break;

            default :
                sprintf(buf, "    Alarm Level Not Set\n");
            break;
        }
        DBC_AppendText(dbc, buf);

        strcpy(buf, "    UAL Trace -\n");
        DBC_AppendText(dbc, buf);

        if (cfg->traceOn)
        {
            if (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_DEBUG))
            {
                strcpy(buf, "        Debug     = ");
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_DEBUG,
                                      2))
                {
                    strcat(buf, " syslog");
                } 
            }
            else
            {
               strcpy(buf, "        Debug     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_CRITICAL))
            {
                strcpy(buf, "        Critical  = ");
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_CRITICAL,
                                      2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Critical  = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_WARNING))
            {
                strcpy(buf, "        Warning   = ");
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      1))
                {
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_WARNING,
                                      2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Warning   = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(UAL_TraceData,
                                    UAL_TRACE_ERROR))
            {
                strcpy(buf, "        Error     = ");
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      0))
                {
                    strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      1))
                { 
                    strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(UAL_TraceData,
                                      UAL_TRACE_ERROR,
                                      2))
                {
                    strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Error     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            strcpy(buf, "        Debug     = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Critical  = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Warning   = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Error     = null\n");
            DBC_AppendText(dbc, buf);
        }
        sprintf(buf, "*********** End of UAL General Config *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_set_gen_cfg", "UAL Set General Config", "<al> <tl>",
                      "<alarm level>, <On / Off>"))
    {
        UALGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];
           
        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType, traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL || 
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") || 
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || 
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || 
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "Invalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, UAL_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, UAL_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, UAL_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, UAL_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }
       
        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, UAL_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, UAL_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, UAL_SYSLOG_STRING);
        } 
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  UAL_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

        sprintf(buf, "***********UAL General Config Set*************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "enable_u_astbl_cmd_on_asp_side", "", "", ""))
    {
		u_astbl_cmd_enabled_on_asp_side = ITS_TRUE;
    }
    else if (DBC_Cmd(dbc, "u_asptbl", "UAL View ASP Table", "", ""))
    {
        UAL_Set_ASP_DumpCmd(&cfg);

        UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        DBC_AppendText(dbc, dumpStr);
    }
    else if (DBC_Cmd(dbc, "u_astbl", "UAL View AS Table", "", ""))
    {
        UAL_Set_AS_DumpCmd(&cfg);

        UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        DBC_AppendText(dbc, dumpStr);
		u_astbl_cmd_enabled_on_asp_side = ITS_FALSE;
    }
    else if (DBC_Cmd(dbc, "u_add_rkey", "UAL Add Routing Key", 
                     " <fm> <tm> <rkid> <style> <pc> <sio> <ssn>",""))
    {
        char style[ITS_PATH_MAX];
        char tm[ITS_PATH_MAX];
        char fm[ITS_PATH_MAX];
        ITS_INT rkid;

        ret = sscanf(cmdLine, "%s %s %s %d %s %d %d %d", buf, fm, tm, &rkid, 
                      style, &pc, &ni, &ssn);

        if (ret != 7 && ret != 8)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if (strcmp(fm, "ITU") == 0 )
        {
            UAL_SetRoutingKeyFamily(&cfg, FAMILY_ITU);
        }
        else if (strcmp(fm, "ANSI") == 0 )
        {
            UAL_SetRoutingKeyFamily(&cfg, FAMILY_ANSI);
        }
        else
        {
            sprintf(buf, "******* Invalid Routing Key Family *********\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }
        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0 )
        {
            UAL_SetRoutingKeyRS(&cfg, ROUTE_DPC_NI);
        }
        else if (strcmp(style,ROUTE_STYLE_DPC_SIO_STRING) == 0 )
        {
            UAL_SetRoutingKeyRS(&cfg, ROUTE_DPC_SIO);
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0 )
        {
            UAL_SetRoutingKeyRS(&cfg, ROUTE_DPC_SIO_SSN);
        }
        else
        {
            sprintf(buf, "********* Invalid Routing Key Style ***********\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if (strcmp(tm, UAL_LOAD_SHARE_MODE_STRING) == 0 )
        {
            UAL_SetRoutingKeyTM(&cfg, UAL_LOADSHARE_MODE);
        }
        else if (strcmp(tm,UAL_OVERIDE_MODE_STRING) == 0 )
        {
            UAL_SetRoutingKeyTM(&cfg, UAL_OVERRIDE_MODE);
        }
        else if (strcmp(tm, UAL_BROADCAST_MODE_STRING) == 0 )
        {
            UAL_SetRoutingKeyTM(&cfg, UAL_BROADCAST_MODE);
        }
        else
        {
            sprintf(buf, "*********** Invalid Traffic Mode *************\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }
        
        UAL_SetRoutingKeyRK(&cfg, (ITS_UINT)rkid);
        UAL_SetRoutingKeyDPC(&cfg, (ITS_UINT)pc);
        UAL_SetRoutingKeySIO(&cfg, (ITS_UINT)ni);
        UAL_SetRoutingKeySSN(&cfg, ssn);

        ret = UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);

        if (ret == ITS_EDUPLENTRY)
        {
            sprintf(buf, "********* Failed :Duplicate Routing Key  *******\n");
        }
        else if ( ret == ITS_FALSE )
        {
            sprintf(buf, "*********** Routing Key Failed to Add **********\n");
        }
        else if ( ret == ITS_TRUE )
        {
            sprintf(buf, "*********** Routing Key Added *************\n");
        }
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_aspup", "UAL Send ASP UP", "<id>",
                     "<routing key id>"))
    {
        ITS_UINT trid = 0;

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }
 
        ret = sscanf(cmdLine, "%s %x", buf, &trid);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if(ASPTable_FindEntry(trid, &asp) != ITS_SUCCESS)
        {
            sprintf(buf, "**** Wrong transport Id *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        UAL_SetASPInfo(&cfg, UAL_CMD_ASP_UP, trid);

        ret_val = UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        if (ret_val != ITS_TRUE)
        {
            sprintf(buf, "*********** Failed to send ASP UP **********\n");
        }
        else
        {
            sprintf(buf, "*********** ASP UP Sent *************\n");
        }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_aspdown", "UAL Send ASP DOWN", "<id>",
                     "<routing key id>"))
    {
        ITS_UINT trid = 0;

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = sscanf(cmdLine, "%s %x", buf, &trid);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if(ASPTable_FindEntry(trid, &asp) != ITS_SUCCESS)
        {
            sprintf(buf, "**** Wrong transport Id *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        UAL_SetASPInfo(&cfg, UAL_CMD_ASP_DOWN, trid);

        ret_val = UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        if (ret_val != ITS_TRUE)
        {
            sprintf(buf, "*********** Failed to send ASP DOWN **********\n");
        }
        else
        {
            sprintf(buf, "*********** ASP DOWN Sent *************\n");
        }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_aspactive", "UAL Send ASP ACTIVE", "<id>",
                     "<routing key id>"))
    {
        ITS_UINT rid;
        RK_Context *rctxt = NULL;

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = sscanf(cmdLine, "%s %x", buf, &rid);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }
        
        if((rctxt = RKManager_FindEntry(rid)) == NULL)
        {
            sprintf(buf, "**** Wrong routing context *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }
 
        UAL_SetASPInfo(&cfg, UAL_CMD_ASP_ACTIVE, rid);

        ret_val = UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        if (ret_val != ITS_TRUE)
        {
            sprintf(buf, "*********** Failed to send ASP ACTIVE **********\n");
        }
        else
        {
            sprintf(buf, "*********** ASP ACTIVE Sent *************\n");
        }
 
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_aspinactive", "UAL Send ASP INACTIVE", "<id>",
                     "<routing key id>"))
    {
        ITS_UINT rid;
        RK_Context *rctxt = NULL;

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = sscanf(cmdLine, "%s %x", buf, &rid);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if((rctxt = RKManager_FindEntry(rid)) == NULL)
        {
            sprintf(buf, "**** Wrong routing context *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        UAL_SetASPInfo(&cfg, UAL_CMD_ASP_INACTIVE, rid);

        ret_val = UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
        if (ret_val != ITS_TRUE)
        {
            sprintf(buf, "*********** Failed to send ASP INACTIVE **********\n");
        }
        else
        {
            sprintf(buf, "*********** ASP INACTIVE Sent *************\n");
        }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_reg_req", "UAL Send Registration Request",
                     "<dpc> <sio> <tm>", " "))
    {
        int dpc;
        int sio;
        char tm[ITS_PATH_MAX];
        UAL_AS_DEF newAs;
        ITS_UINT localRkId = 0;

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
        {
            sprintf(buf, "\n *** Command not for IPSP single exchange "
                         "server Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        memset(&newAs, 0, sizeof(UAL_AS_DEF));

        ret = sscanf(cmdLine, "%s %d %d %s", buf, &dpc, &sio, tm);

        if (ret != 4)
        {
            sprintf(buf, "**** Invalid Registration Parameters *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if (strcmp(tm, UAL_LOAD_SHARE_MODE_STRING) == 0)
        {
             newAs.tm = UAL_LOADSHARE_MODE;
        }
        else if (strcmp(tm,UAL_OVERIDE_MODE_STRING) == 0)
        {
             newAs.tm =  UAL_OVERRIDE_MODE;
        }
        else if (strcmp(tm, UAL_BROADCAST_MODE_STRING) == 0)
        {
             newAs.tm = UAL_BROADCAST_MODE;
        }
        else
        {
            sprintf(buf, "*********** Invalid Traffic Mode *************\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        newAs.style = ROUTE_DPC_SIO;
#if defined (CCITT)
        UAL_SET_PC_VALUE_CCITT(newAs.dpc, dpc);
#elif defined (ANSI)
        UAL_SET_PC_VALUE_ANSI(newAs.dpc, dpc);
#elif defined (PRC)
        UAL_SET_PC_VALUE_PRC(newAs.dpc, dpc);
#elif defined (TTC)
        UAL_SET_PC_VALUE_TTC(newAs.dpc, dpc);
#endif

        newAs.si.siList[0] = (ITS_OCTET)sio & 0xFF;

        newAs.numSI = 1;

        ret = UAL_RegisterApplicationServer(&newAs, 1, 1, &localRkId);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "*********** Failed to Register AS *************\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        sprintf(buf, "*********** Registration Request sent *************\n");
        DBC_AppendText(dbc, buf);

        sprintf(buf, "Note: Check AS table(u_astbl) for "
                "registration outcome, \n      make sure debug flag is ON "
                "(u_debug_flag)\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_dereg_req", "UAL Send Deregistration Request",
                     "<rCtxt>", " "))
    {
        ITS_UINT rCtxt = 0; 

        if (UAL_GL_ITW_MODE == UAL_ITW_SG)
        {
            sprintf(buf, "\n *** Command not for SG Side. *** \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = sscanf(cmdLine, "%s %d", buf, &rCtxt);

        if (ret != 2)
        {
            sprintf(buf, "**** Invalid Deregistration Parameters *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        if(!RKManager_FindEntry(rCtxt))
        {
            sprintf(buf, "**** Incorrect Routing Key ****\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        ret = UAL_DeregisterApplicationServer(&rCtxt, 1, 1);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "**** RK Deregistration failed *******\n");
            DBC_AppendText(dbc, buf);
            UAL_ConfigDest(&cfg);
            return;
        }

        sprintf(buf, "*********** Deregistration Succesfull *************\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_get_gen_peg", "UAL Get Peg Count",
                     "<transportID> <PegID> ", " "))
    {
        ITS_UINT trid;
        ITS_INT pegid;
        char pgName[ITS_PATH_MAX];
        ITS_INT value;
  
        ret = sscanf(cmdLine, "%s %x %s", buf,&trid,pgName); 
  
        if (ret != 3)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n Usage: u_get_gen_peg <trid> <pegid>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
      
        if((strncmp(pgName, "All", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_UAL_PEGS))
        {
            UAL_MIB_STATS*  data;
            data = (UAL_MIB_STATS*)malloc(sizeof(UAL_MIB_STATS));
            memset(data, 0, sizeof(UAL_MIB_STATS));

            ret = UAL_GetAllPegInfo(trid, data);
            if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf, "\n**** Transport id invalid *******\n");
                DBC_AppendText(dbc, buf);
                sprintf(buf, "To get valid transport id run command u_asptbl\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "\n**************** M3UA/SUA Pegs ****************\n"); 
            DBC_AppendText(dbc, buf);           

            sprintf(buf, "\nUAL_PEG_UP_SENT_ID             : %d\n",
			                                  data->aspUpSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_UP_RECV_ID             : %d\n",
			                                  data->aspUpRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_UPACK_SENT_ID          : %d\n",
			                                  data->aspUpAckSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_UPACK_RECV_ID          : %d\n",
			                                  data->aspUpAckRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DN_SENT_ID             : %d\n",
			                                  data->aspDnSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DN_RECV_ID             : %d\n",
			                                  data->aspDnRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DNACK_SENT_ID          : %d\n",
			                                  data->aspDnAckSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DNACK_RECV_ID          : %d\n",
			                                  data->aspDnAckRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_AC_SENT_ID             : %d\n",
			                                  data->aspAcSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_AC_RECV_ID             : %d\n",
			                                  data->aspAcRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_ACACK_SENT_ID          : %d\n",
			                                  data->aspAcAckSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_ACACK_RECV_ID          : %d\n",
			                                  data->aspAcAckRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_IA_SENT_ID             : %d\n",
			                                  data->aspIaSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_IA_RECV_ID             : %d\n",
			                                  data->aspIaRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_IAACK_SENT_ID          : %d\n",
			                                  data->aspIaAckSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_IAACK_RECV_ID          : %d\n",
			                                  data->aspIaAckRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_NOTIFY_SENT_ID         : %d\n",
			                                  data->notifySent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_NOTIFY_RECV_ID         : %d\n",
			                                  data->notifyRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_REG_REQ_SENT_ID        : %d\n",
			                                  data->regReqSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_REG_REQ_RECV_ID        : %d\n",
			                                  data->regReqRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_REG_RSP_SENT_ID        : %d\n",
			                                  data->regRspSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_REG_RSP_RECV_ID        : %d\n",
			                                  data->regRspRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DEREG_REQ_SENT_ID      : %d\n",
			                                  data->deregReqSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DEREG_REQ_RECV_ID      : %d\n",
			                                  data->deregReqRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DEREG_RSP_SENT_ID      : %d\n",
			                                  data->deregRspSent);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_DEREG_RSP_RECV_ID      : %d\n",
			                                  data->deregRspRecv);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "UAL_PEG_ERR_SENT_ID            : %d\n",
			                                  data->errSent);
            DBC_AppendText(dbc, buf);
            
            sprintf(buf, "UAL_EEG_ERR_RECV_ID            : %d\n",
			                                  data->errRecv);
            DBC_AppendText(dbc, buf);

            free(data);
            return;
        }

        pegid = atoi(pgName); 
  
        ret = UAL_GetPegInfo(trid, pegid, &value, SCTP_PAYLOAD_UNDEFINED);
        if (ret == ITS_EENDOFLIST)
        {
            sprintf(buf, "\n**** Transport id invalid *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else if (ret == ITS_ENOTFOUND)
        {
            sprintf(buf, "\n**** Peg id invalid *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get vaild peg id do help u_get_gen_peg\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "\nvalue of peg id %d is %d\n", pegid, value);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_clr_gen_peg", "UAL Clear Peg Count",
                     "<transportID> <PegID> ", " "))
    {
        char pgName[ITS_PATH_MAX];
        ITS_INT pegid;
        ITS_UINT trid;

        ret = sscanf(cmdLine, "%s %x %s", buf, &trid, pgName);

        if (ret != 3)
        {
            sprintf(buf, "\n**** Invalid number of parameters *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n Usage: u_clr_gen_peg <trid> <pegid>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        if((strncmp(pgName, "All", 3) == 0)||
           (strncmp(pgName, "all", 3) == 0)||
           (atoi(pgName) == ALL_UAL_PEGS))
        {
            ret = UAL_ClearAllPegInfo(trid, SCTP_PAYLOAD_UNDEFINED);
            if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf, "\n**** Transport id invalid *******\n");
                DBC_AppendText(dbc, buf);
                sprintf(buf, "To get valid transport id run command u_asptbl\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            sprintf(buf, "value of all peg ids set to 0 \n");
            DBC_AppendText(dbc, buf);
        } 

        pegid = atoi(pgName); 
         
        ret = UAL_ClearPegInfo(trid, pegid);

        if (ret == ITS_EENDOFLIST)
        {
            sprintf(buf, "\n**** invalid Transport id *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get valid transport id run command u_asptbl\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else if (ret == ITS_ENOTFOUND)
        {
            sprintf(buf, "\n**** invalid peg id *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "To get vaild peg id do help u_clr_gen_peg\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        sprintf(buf, "\nvalue of peg id %d set to 0 \n", pegid);
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_debug_flag", "UAL Debug Flag",
                     "<onOff>", " "))
    {
        char onOff[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, onOff);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid number of parameters *******\n");
            DBC_AppendText(dbc, buf);
            sprintf(buf, "\n Usage: u_debug_flag <onOff>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if((strncmp(onOff, "ON", 2) == 0)||
           (strncmp(onOff, "on", 2) == 0))
        {
            UAL_GL_DEBUG_FLAG = ITS_TRUE;
        }
        else if((strncmp(onOff, "OFF", 3) == 0)||
                (strncmp(onOff, "off", 3) == 0))
        {
            UAL_GL_DEBUG_FLAG = ITS_FALSE;
        }

        sprintf(buf, "\n*********** Debug flag is set ***********\n");
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "u_get_timers", "Get UAL Timer info", "", " "))
    {
       UAL_CONFIG_PRIV_CMD(cfg.priv)= UAL_CMD_GET_CFG;
       UAL_ExecuteConfigCmd(cfg.priv, &dumpStr);
       DBC_AppendText(dbc, dumpStr);
    }

    else if (DBC_Cmd(dbc, "u_set_timers", "Set UAL Timer Info", "<tmrtype> <tmrval>", " "))
    {
       ITS_OCTET cmd[10]; 
       ITS_UINT timerType, timerVal; 
       UAL_ParseInfo* tmp = NULL;
       ENGINE_ParserExtension ext =
       (ENGINE_ParserExtension) ENGINE_APP_PARSER_EXTENSIONS(application);

       ret = sscanf(cmdLine, "%s %d %d", cmd, &timerType, &timerVal);
       if (ret < 3)
       {
          sprintf(buf, "\n**** Invalid number of parameters *******\n");
          return;
       }

       while (ext)
       {
           if (strcmp(ENGINE_PE_ELEMENT_NAME(ext),"UAL_Manager") == 0)
           {
               break;
           }

           ext = (ENGINE_ParserExtensionRec*)ENGINE_PE_NEXT(ext);
       }

       tmp = ENGINE_PE_USER_DATA(ext);
       if (tmp == NULL) 
       {
          sprintf(buf, "\n***** Set UAL Timer Info Failed *******\n");
          DBC_AppendText(dbc, buf);
          return;
       }
        
       switch(timerType)
       {    
        case 1:
               UAL_GL_HB_INTER = tmp->hbInterval = timerVal;
               sprintf(buf, "\n***** hbInterval Set ******\n");
               break;
        case 2:  
               UAL_GL_ACK_TIMER = tmp->ackTimer = timerVal;
               sprintf(buf, "\n***** ackTimer Set ******\n");
               break;
        case 3:  
               UAL_GL_PEND_TIMER = tmp->pendingTimer = timerVal;
               sprintf(buf, "\n***** pendingTimer Set ******\n");
               break;
        case 4:  
               UAL_GL_AUD_TIMER = tmp->audTimer = timerVal;
	       sprintf(buf, "\n***** audTimer Set ******\n");
               break;
        default:  
               sprintf(buf, "\n***** Invalid Parameter *******\n");
       }  
       DBC_AppendText(dbc, buf);

    }  
    else if (DBC_Cmd(dbc, "u_configure_ual", "configure UAL Management",
                     " <mode> <payload> <ipspExTy> <ipspTy> <hbEn> <version> <lpc> <hbInt> <ackTi> <audTi> <pendTi>",""))
    {
        UALConfigMgmt *ualConfigMgmt;

        ualConfigMgmt = (UALConfigMgmt*)calloc(1, sizeof(UALConfigMgmt));

        ret = sscanf(cmdLine, "%s %s %s %s %s %s %s %d %d %d %d %d", buf, ualConfigMgmt->interworkingMode, 
                               ualConfigMgmt->protocolType, ualConfigMgmt->ipspExchangeType, 
                               ualConfigMgmt->ipspType, ualConfigMgmt->heartbeatFlag, 
                               &ualConfigMgmt->protocolVersion, &ualConfigMgmt->localPointCode, 
                               &ualConfigMgmt->heartbeatInterval, &ualConfigMgmt->ackTimer,
                               &ualConfigMgmt->auditTimer, &ualConfigMgmt->pendingTimer); 

        if (ret < 12)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            sprintf(buf, "Usage...\n");
            sprintf(buf, "u_configure_ual  <mode> <payload> <ipspExTy> <ipspTy> <hbEn> <version> <lpc>> <hbInt> <ackTi> <audTi> <pendTi>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        ret = ConfigureUalManagement(ualConfigMgmt);
    }
    else if (DBC_Cmd(dbc, "u_create_as", "Create Application Server",
                     " <rContext> <family> <trafficMode> <networkIndicator> <isMember>",""))
    {
        ITS_CHAR tm[20];
        ITS_CHAR fm[20];
        ITS_CHAR isMem[20];
        ITS_UINT rContext, ni;
        UAL_TRAFFIC_TYPE trafficMode;
        ITS_BOOLEAN isMember = ITS_TRUE;
        
        ret = sscanf(cmdLine, "%s %d %s %s %d %s", buf, &rContext, fm, tm, &ni, isMem);

        if(ret < 6)
        {
            sprintf(buf, "\n ** Invalid command Usage u_create_as <rContext> <family> <trafficMode> <networkIndicator> <isMember>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if(strcmp(tm, UAL_LOAD_SHARE_MODE_STRING) == 0)
        {
            trafficMode = UAL_LOADSHARE;
        }
        else if(strcmp(tm, UAL_OVERIDE_MODE_STRING) == 0)
        {
            trafficMode = UAL_OVERRIDE;
        }
        else
        {
            return;
        }

        if((strcmp(isMem, "yes") == 0) ||
           (strcmp(isMem, "YES") == 0))
        {
            isMember = ITS_TRUE;
        }
        else if((strcmp(isMem, "no") == 0) ||
                (strcmp(isMem, "NO") == 0))
        {
            isMember = ITS_FALSE;
        }

        ret = CreateApplicationServer(rContext, fm, trafficMode, ni, isMember); 
    }
    else if (DBC_Cmd(dbc, "u_delete_as", "Delete Application Server",
                     " <rContext>",""))
    {
        ITS_UINT rContext;
        ret = sscanf(cmdLine, "%s %d", buf, &rContext);

        if(ret < 2)
        {
            sprintf(buf, "\n ** Invalid command Usage u_delete_as <rContext>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = DeleteApplicationServer(rContext);
    }
    else if (DBC_Cmd(dbc, "u_create_asp", "Create Application Server Process",
                     " <rContext> <aspId> <homeValue> <homePort>",""))
    {
        ITS_UINT rContext;
        ITS_INT  aspId;
        char ipaddr[64] = {0};
        ret = sscanf(cmdLine, "%s %d %d %s", buf, &rContext, &aspId, ipaddr);

        if(ret < 3)
        {
            sprintf(buf, "\n ** Invalid command Usage u_create_asp <rContext> <aspId>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = CreateApplicationServerProcess(rContext, aspId, ipaddr);
    }
    else if (DBC_Cmd(dbc, "u_delete_asp", "Delete Application Server Process",
                     " <rContext> <aspId>",""))
    {
        ITS_UINT rContext;
        ITS_INT  aspId;
        ret = sscanf(cmdLine, "%s %d %d", buf, &rContext, &aspId);

        if(ret < 3)
        {
            sprintf(buf, "\n ** Invalid command Usage u_delete_asp <rContext> <aspId>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = DeleteApplicationServerProcess(rContext, aspId);
    }

    else if (DBC_Cmd(dbc, "u_enable_asp", "Enable Application Server Process",
                     " <rContext> <aspId>",""))
    {
        ITS_UINT rContext;
        ITS_INT  aspId;
        ret = sscanf(cmdLine, "%s %d %d", buf, &rContext, &aspId);

        if(ret < 3)
        {
            sprintf(buf, "\n ** Invalid command Usage u_enable_asp <rContext> <aspId>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = EnableApplicationServerProcess(rContext, aspId);
    }
    else if (DBC_Cmd(dbc, "u_disable_asp", "Disable Application Server Process",
                     " <rContext> <aspId>",""))
    {
        ITS_UINT rContext;
        ITS_INT  aspId;
        ret = sscanf(cmdLine, "%s %d %d", buf, &rContext, &aspId);

        if(ret < 3)
        {
            sprintf(buf, "\n ** Invalid command Usage u_disable_asp <rContext> <aspId>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = DisableApplicationServerProcess(rContext, aspId);
    }
    else if (DBC_Cmd(dbc, "u_get_as_state", "Get Application Server State",
                     " <rContext>",""))
    {
        ITS_UINT rContext;
        ret = sscanf(cmdLine, "%s %d", buf, &rContext);

        if(ret < 2)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_as_state <rContext>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetApplicationServerState(rContext);
    }
    else if (DBC_Cmd(dbc, "u_get_asp_state", "Get Application Server Process State",
                     " <rContext> <aspId>",""))
    {
        ITS_UINT rContext;
        ITS_INT  aspId;
        ret = sscanf(cmdLine, "%s %d %d", buf, &rContext, &aspId);

        if(ret < 3)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_asp_state <rContext> <aspId>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetApplicationServerProcessState(rContext, aspId);
    }
    else if (DBC_Cmd(dbc, "u_get_local_as_info", "Get Local Application Server Info",
                     "",""))
    {
        ret = sscanf(cmdLine, "%s", buf);

        if(ret < 1)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_local_as_info\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetLocalApplicationServerInfo();
    }
    else if (DBC_Cmd(dbc, "u_get_remote_as_info", "Get Remote Application Server Info",
                     "",""))
    {
        ret = sscanf(cmdLine, "%s", buf);

        if(ret < 1)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_remote_as_info\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetRemoteApplicationServerInfo();
    }
    else if (DBC_Cmd(dbc, "u_get_local_asp_info", "Get Local Application Server Process Info",
                     "",""))
    {
        ret = sscanf(cmdLine, "%s", buf);

        if(ret < 1)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_local_asp_info\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetLocalApplicationServerProcessInfo();
    }
    else if (DBC_Cmd(dbc, "u_get_remote_asp_info", "Get Remote Application Server Process Info",
                     "",""))
    {
        ret = sscanf(cmdLine, "%s", buf);

        if(ret < 1)
        {
            sprintf(buf, "\n ** Invalid command Usage u_get_remote_asp_info\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = GetRemoteApplicationServerProcessInfo();
    }

    if (dumpStr)
    {
        free(dumpStr);
    }

    UAL_ConfigDest(&cfg);

    return;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to configure the UAL Management Information.
 *     It includes:
 *     	Interworking Mode (SG, ASP, IPSP)
 *	Protocol Type (M3UA, SUA, IUA) 
 *	Heartbeat Flag (ON/OFF) 
 * 	Heartbeat Interval
 * 	Acknowledgement Timer
 * 	Audit Timer (DAUD Timer)
 *	AS Pending Timer
 * 	Protocol Version
 *  	Local (Self) Point Code
 *	IPSP Exchange Type (Single Exchange, Double Exchange)
 *	IPSP Type (Client, Server)
 *
 *  Input Parameters:
 *      Structure UALConfigMgmt 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT ConfigureUalManagement(UALConfigMgmt *ualMgmt)
{
    /* Mandatory Parameters
         - Interworking Mode (ASP, SG, IPSP)
         - Protocol Type (M3UA or SUA)

       Conditional Parameters
         - IPSP Exchange Mode (Single, Double)
         - IPSP Type (Client, Server)
         - Local Point Code

       Optional Parameters
         - M3UA Version (1 always)
         - Ack Timer
         - Pending Timer
         - Audit Timer
         - Heartbeat (on/off)
         - Heartbeat Interval
         - Number of retries
    */

    if((strcmp(ualMgmt->interworkingMode, "ASP") == 0) ||
       (strcmp(ualMgmt->interworkingMode, "asp") == 0))
    {
        UAL_GL_ITW_MODE = UAL_ITW_ASP;
    }
    else if((strcmp(ualMgmt->interworkingMode, "SG") == 0) ||
            (strcmp(ualMgmt->interworkingMode, "sg") == 0))
    {
        UAL_GL_ITW_MODE = UAL_ITW_SG;
    }
    else if((strcmp(ualMgmt->interworkingMode, "IPSP") == 0) ||
            (strcmp(ualMgmt->interworkingMode, "ipsp") == 0))
    {
        UAL_GL_ITW_MODE = UAL_ITW_IPSP;
    }
    else
    {
        printf("\n*** Invalid Interworking Mode ***\n");
        return !ITS_SUCCESS;
    }

    if((strcmp(ualMgmt->protocolType, "M3UA") == 0) ||
       (strcmp(ualMgmt->protocolType, "m3ua") == 0))
    {
        UAL_PROTOCOL_TYPE = SCTP_PAYLOAD_M3UA;
    }
    else if((strcmp(ualMgmt->protocolType, "SUA") == 0) ||
       (strcmp(ualMgmt->protocolType, "sua") == 0))
    {
        UAL_PROTOCOL_TYPE = SCTP_PAYLOAD_SUA;
    }
    else
    {
        printf("\n*** Invalid Protocol Type ***\n");
        return !ITS_SUCCESS;
    }

    if((strcmp(ualMgmt->ipspExchangeType, "DOUBLE") == 0) ||
       (strcmp(ualMgmt->ipspExchangeType, "double") == 0))
    {
        UAL_GL_IPSP_TYPE = UAL_IPSP_TYPE_DOUBLE_EXCHG;
    }
    else if((strcmp(ualMgmt->ipspExchangeType, "SINGLE") == 0) ||
            (strcmp(ualMgmt->ipspExchangeType, "single") == 0))
    {
        UAL_GL_IPSP_TYPE = UAL_IPSP_TYPE_SINGLE_EXCHG;
    }
    else if(strcmp(ualMgmt->ipspExchangeType, "-") == 0)
    {
    }
    else
    {
        printf("\n*** Invalid IPSP Exchange Type ***\n");
        return !ITS_SUCCESS;
    }

    if((strcmp(ualMgmt->ipspType, "CLIENT") == 0) ||
       (strcmp(ualMgmt->ipspType, "client") == 0))
    {
        UAL_GL_IPSP_TYPE |= UAL_IPSP_MASK_CLIENT; 
    }
    else if((strcmp(ualMgmt->ipspType, "SERVER") == 0) ||
            (strcmp(ualMgmt->ipspType, "server") == 0))
    {
        UAL_GL_IPSP_TYPE |= UAL_IPSP_MASK_SERVER;
    }
    else if(strcmp(ualMgmt->ipspType, "-") == 0)
    {
    }
    else
    {
        printf("\n*** Invalid IPSP Type ***\n");
        return !ITS_SUCCESS;
    }

    if((strcmp(ualMgmt->heartbeatFlag, "ON") == 0) ||
       (strcmp(ualMgmt->heartbeatFlag, "on") == 0))
    {
        UAL_GL_HB_FLAG = ITS_TRUE;
    }
    else if((strcmp(ualMgmt->heartbeatFlag, "OFF") == 0) ||
            (strcmp(ualMgmt->heartbeatFlag, "off") == 0))
    {
        UAL_GL_HB_FLAG = ITS_FALSE;
    }
    else
    {
        printf("\n*** Invalid Heartbeat Flag ***\n");
        return !ITS_SUCCESS;
    }

    UAL_GL_HB_INTER = ualMgmt->heartbeatInterval;

    UAL_GL_ACK_TIMER = ualMgmt->ackTimer;

    UAL_GL_AUD_TIMER = ualMgmt->auditTimer;

    UAL_GL_PEND_TIMER = ualMgmt->pendingTimer;

    UAL_GL_VERSION = ualMgmt->protocolVersion;

    UAL_GL_LOCAL_PC = ualMgmt->localPointCode;

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to create an Application Server (AS). 
 *     It is valid for SG, ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context, Family, Traffic Mode, Network Indicator, IsMember 
 *     Note: isMember is significant for ASP & IPSP interworking modes
 *           For SG Mode, the isMember is set to NO.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT CreateApplicationServer(ITS_UINT rContext, ITS_CHAR *family,
                                UAL_TRAFFIC_TYPE trafficMode, ITS_UINT ni,
                                ITS_BOOLEAN isMember)
{
    ITS_INT ret = ITS_SUCCESS;
    RK_Context *asEntry = NULL;

    UAL_DEBUG(("\nCreateAS: RC %d family %s tm %d ni %d isMem %d\n", rContext, family, trafficMode, ni, isMember));

    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP) || (UAL_GL_ITW_MODE == UAL_ITW_ASP))
    {
        asEntry = (RK_Context*)calloc(1, sizeof(RK_Context));

        if(asEntry != NULL)
        {
            ROUTE_Info **rinfo;
            asEntry->isMember = isMember;
    
            asEntry->rCtxt = rContext;
    
            ret = ROUTE_FindRoutingKeyInfo(asEntry->rCtxt, &rinfo); 
    
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("CreateApplicationServer: could not obtain rInfo "
                           "from Routing Ctxt: %u\n", asEntry->rCtxt));
                //return !ITS_SUCCESS;
                free(asEntry);
                asEntry = NULL;
                return ADD_ASSOCIATIONSET_ERR_COULD_NOT_OBTAIN_ROUTINGKEYINFO;
            }
            asEntry->asInfo = (*rinfo)->basic;
            asEntry->asInfo.type = REMOTE_ROUTE;
            asEntry->na.na = ni;
            asEntry->trafficMode = trafficMode;
            asEntry->family = strdup(family); 
    
            ret = RKManager_AddEntry(asEntry->rCtxt, asEntry);
    
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("CreateApplicationServer: Error creating AS %d\n", rContext));
                free(asEntry);
                asEntry = NULL;
                //return !ITS_SUCCESS;
                return ADD_ASSOCIATIONSET_ERR_UNABLE_TO_CREATE_APPLICATION_SERVER;
            }

            /* Add new linkset and destination (remote route) for the AS */
            ret = UAL_AddLinkSetAndDestination(asEntry);
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("CreateApplicationServer: Error adding LS & Dest for AS %d\n", rContext));
                free(asEntry);
                asEntry = NULL;
                //return !ITS_SUCCESS;
                return ADD_ASSOCIATIONSET_ERR_CREATE_APPLICATION_SERVER_FAILED_TO_ADD_LINKSET_AND_DESTINATION;
            }

            UAL_DEBUG(("CreateApplicationServer: AS Addition successful %d\n", rContext));
        }
        else
        {
            UAL_ERROR(("\nCreateApplicationServer: Error creating AS.. No memory\n"));
            free(asEntry);
            asEntry = NULL;
            //return !ITS_SUCCESS;
            return ADD_ASSOCIATIONSET_ERR_UNABLE_TO_CREATE_APPLICATION_SERVER;
        }
    }
    else
    {
    }
    return ret;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to delete an Application Server (AS).
 *     It is valid for SG, ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT DeleteApplicationServer(ITS_UINT rContext)
{
    ITS_INT ret = ITS_SUCCESS;
    RK_Context *rCtxt = NULL;

    UAL_DEBUG(("\nDeleteAS: RC %d\n", rContext));

    /* AS can be deleted under the following conditions
         1. When AS is in DOWN state
             1a. None of the ASP(s) under the AS is/are in
                 ACTIVE or INACTIVE state.
             1b. No ASP(s) are configured under the AS.
    */

    /* Delete the AS Entry from the ASP Table, which are
       part of that AS */

    rCtxt = RKManager_FindEntry(rContext);

    if(rCtxt == NULL)
    {
        UAL_ERROR(("\nDeleteAS: Routing Context %d not found...\n", rContext));
        return !ITS_SUCCESS;
    }

    /* 
       Note: If the AS is in DOWN state, then all the ASP(s) in the AS
       are in DOWN state, hence the Transport ID for all the ASP(s)
       will be ZERO (INVALID TRANSPORT)
    */
    if(rCtxt->state == UAL_AS_DOWN)
    {
        //RKListNode* rk_nd;
        ASPListNode* aspNode = NULL;
  
        /* Iterate the Routing Context Table to get all the ASP(s) */
        aspNode = ASPList_Iterate(rCtxt->aspList);
    
#if 0 
      /* 
         When the ASP(s) which are part of AS are DOWN, then the
         AS entries are removed from the ASP(s) AS entry list, during 
         the exchange of ASP DOWN/ASP_DOWN_ACK and also during
         local SCTP COMMUNICATION LOST.  Hence there is no need to
         remove the AS entries again from the ASP Table.
      */
        if(LIST_COUNT(rCtxt->aspList) == 0)
        {
            /* No ASP(s) within the AS...*/
            UAL_DEBUG(("\nDeleteAS: No ASP(s) under AS %d\n", rContext));
        }
        else
        {
            for(; aspNode; aspNode = ASPList_Iterate(NULL))
            {
                if(aspNode->entry != NULL)
                {
                    rk_nd = RKList_Iterate(aspNode->entry->asList);
                    for(; rk_nd; rk_nd = RKList_Iterate(NULL))
                    {
                        if(rk_nd->rCtxt == rContext)
                        {
                            UAL_DEBUG(("\nDeleteAS: ASP %d is part of AS %d\n", aspNode->entry->aspId, rContext));
                            ret = RKList_RemoveEntry(aspNode->entry->asList, rContext);
                            if(ret != ITS_SUCCESS)
                            {
                                UAL_ERROR(("\nDeleteAS: AS %d deletion failed in ASP %d table\n", rContext, aspNode->entry->aspId));
                                return ret; 
                            }
                            break; /* come out of the inner for..loop */
                            UAL_DEBUG(("\nDeleteAS: AS %d deleted in ASP %d table\n", rContext, aspNode->entry->aspId));
                        }
                    }    
                }
                else
                {
                    UAL_WARNING(("\nDeleteAS: AS %d Table having incorrect ASP\n", rContext));
                    return !ITS_SUCCESS;
                }
            } 
        }
#endif

        /* Delete the AS Entry (Routing Context) structure, once the AS information
           is deleted from all the ASP(s) corresponding to that AS */
        ret = RKManager_RemoveEntry(rCtxt); 

        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("\nDeleteAS: AS %d deletion failed\n", rContext));
            return !ITS_SUCCESS;
        }
        UAL_DEBUG(("\nDeleteAS: AS %d deletion successful\n", rContext));
    }
    else /* If the AS is in ACTIVE/INACTIVE/PENDING, don't delete */
    {
        UAL_ERROR(("\nDeleteAS: AS %d deletion failed...\n", rContext));
        return !ITS_SUCCESS;
    }
    return ret;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to create an Application Server Process (ASP) within
 *     an AS. It is valid for SG & IPSP Interworking Modes.  If the 
 *     Interworking mode is ASP, only the UAL_GL_ASP_ID field is set with
 *     the aspId.
 *
 *  Input Parameters:
 *     Routing Context, aspId
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT CreateApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId,const char* ipAddress)
{
    UAL_ASP_INFO aspInfoArray[16]; /* maximum of 16 ASP are present in
				      one single AS */
    SOCK_IPv4Addr ipAddrs;
    ITS_UINT numHome = 0; 
    ITS_UINT numASP = 0;
    ITS_INT ret = ITS_SUCCESS;

    UAL_DEBUG(("\nCreateASP: RC %d aspId %d\n", rContext, aspId));

    /* 
       ASP : No need to provide the IP Address and Port Number
       SG  : Need to provision the IP Address and Port # of the
             remote end (i.e. ASP)
       IPSP: For IPSP SE/DE Client, the IP Address and Port # of
             the peer IPSP should be configured
     */

    if(UAL_GL_ITW_MODE == UAL_ITW_ASP)
    {
        UAL_GL_ASP_ID = aspId; 
	/* 
           Need to confirm following
	   1. When aspId is provisioned in the UAL_Manager section, do we need
	      to add the aspId info to the asList (this is taken care when
	      SCTP COMM UP is received, Add_List_of_AS_To_ASP... is invoked
	   2. When aspId is provisioned in the AspInfo section, do we add the
	      aspId info to the asList (i.e. UAL_AddAsInfoTo... function)
	*/
        return ITS_SUCCESS;
    }
    else if(UAL_GL_ITW_MODE == UAL_ITW_SG)
    {
        ASPListNode aspEntry;
	RK_Context *rCtxt = NULL;

	memset(&aspEntry, 0, sizeof(ASPListNode));
        memset(aspInfoArray, 0, (16 * sizeof(UAL_ASP_INFO)));

	/* Find the Routing Context */
	rCtxt = RKManager_FindEntry(rContext);

	if(rCtxt == NULL)
        {
            UAL_ERROR(("\nCreateASP: Routing Context %d not present...\n", rContext));
	    return ADD_ASSOCIATIONSET_ERR_COULD_NOT_OBTAIN_ROUTINGKEYINFO;
        }

        UAL_GL_ASP_ID = aspId;    

	aspInfoArray[numASP].aspid = aspId;

#if 0
	ret = SOCK_IPv4NameToAddr(ipAddress, &homeIpAddr);
	if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("CreateASP: Error parsing ipAddress...\n"));
	    return !ITS_SUCESS;
        }

	aspInfoArray[numASP].home[numHome] = homeIpAddr;
	aspInfoArray[numASP].numHome++;
#endif

	if(rCtxt->aspList == NULL)
        {
            rCtxt->aspList = UAL_CreateList();
        }		 

	aspEntry.aspInfo = aspInfoArray[numASP];

	ret = ASPList_AddEntry(rCtxt->aspList, &aspEntry);
	if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("CreateASP: Error adding ASP Entry to AS %d...\n", rContext));
	    return ADD_ASSOCIATIONSET_ERR_CREATE_APPLICATION_SERVER_PROCESS_FAILED;
        }
    }
    else if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        ASPListNode aspEntry;
        RK_Context *rCtxt = NULL;

        memset(&aspEntry, 0, sizeof(ASPListNode));
        memset(aspInfoArray, 0, (16 * sizeof(UAL_ASP_INFO)));

        /* Find the Routing Context */
        rCtxt = RKManager_FindEntry(rContext);

        if(rCtxt == NULL)
        {
            UAL_ERROR(("\nCreateASP: Routing Context %d not present...\n", rContext));
            return ADD_ASSOCIATIONSET_ERR_COULD_NOT_OBTAIN_ROUTINGKEYINFO;
        }

        UAL_GL_ASP_ID = aspId;    

        aspInfoArray[numASP].aspid = aspId;

        //ret = SOCK_IPv4NameToAddr("10.1.30.146", &ipAddrs);
        //char ipaddr[50] = "10.1.30.146";
        UAL_DEBUG(("Incoming IpAddress %s\n", ipAddress));
        ret = SOCK_IPv4NameToAddr(ipAddress, &ipAddrs);
        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("CreateASP: Error parsing ipAddress...\n"));
            return !ITS_SUCCESS;
        }

        aspInfoArray[numASP].home[numHome] = ipAddrs;
        aspInfoArray[numASP].numHome++;

        if(rCtxt->aspList == NULL)
        {
            rCtxt->aspList = UAL_CreateList();
        }		 

        aspEntry.aspInfo = aspInfoArray[numASP];

        ret = ASPList_AddEntry(rCtxt->aspList, &aspEntry);
        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("CreateASP: Error adding ASP Entry to AS %d...\n", rContext));
            return ADD_ASSOCIATIONSET_ERR_CREATE_APPLICATION_SERVER_PROCESS_FAILED;
        }

    }
    else
    {
        UAL_ERROR(("\nCreateASP: Wrong Interworking Mode...\n"));     
	return !ITS_SUCCESS;
    }
    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to delete an Application Server Process from an
 *     Application Server. If the ASP is part of more than one AS, this 
 *     API will delete the ASP only from the mentioned AS
 *
 *  Input Parameters:
 *     Routing Context, aspId
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT DeleteApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId)
{
    RK_Context *rCtxt = NULL;
    ASPListNode *aspNode = NULL;
    ITS_BOOLEAN matchFound = ITS_FALSE;
    ITS_INT ret = ITS_SUCCESS;

    /* 
       ASP will be in DOWN state for the following reasons
         1. ASP sends out ASP_DOWN message and receives ASP_DOWN_ACK
         2. SCTP Communication Lost/Abort is received from local SCTP

       Deletion of ASP is not possible, when
         1. ASP is in DOWN state but the SCTP Association is ESTABLISHED
         2. ASP is in ACTIVE state
         3. ASP is in INACTIVE state

       Behavior for SG, ASP, IPSP modes....(to be done)
    */

    /* Find the Routing Context structure */
   rCtxt = RKManager_FindEntry(rContext);

   if(rCtxt == NULL)
   {
       UAL_ERROR(("\nDeleteASP: Routing Context %d not found...\n", rContext));
       return !ITS_SUCCESS;
   }

    aspNode = ASPList_Iterate(rCtxt->aspList);
    for(;aspNode; aspNode = ASPList_Iterate(NULL))
    {
        if(aspNode->aspInfo.aspid == aspId)
        {
            matchFound = ITS_TRUE;
            UAL_DEBUG(("\nDeleteASP: ASP ID %d found under AS %d\n", aspId, rContext));
            break;
        }
    }

    if(matchFound == ITS_TRUE)
    {
        if(aspNode->trId != 0x00)
        {
            UAL_DEBUG(("\nDeleteASP: Transport %u for ASP %d\n", aspNode->trId, aspNode->aspInfo.aspid));
            UAL_WARNING(("\nDeleteASP: Cannot delete the ASP %d in AS %d\n", aspId, rContext));
            return !ITS_SUCCESS;
        }
        else
        {
            UAL_DEBUG(("\nDeleteASP: Null Transport for ASP %d\n", aspNode->aspInfo.aspid));

            ret = ASPList_RemoveEntry(rCtxt->aspList, aspNode->trId);
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("\nDeleteASP: ASP %d in AS %d deletion failed\n", aspId, rContext));
                return !ITS_SUCCESS;
            }
            UAL_DEBUG(("\nDeleteASP: ASP %d in AS %d deletion successful\n", aspId, rContext));
        }
    }
    else
    {
        UAL_ERROR(("\nDeleteASP: ASP %d not present under AS %d\n", aspId, rContext)); 
        ret = !ITS_SUCCESS;
    }
    return ret;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to enable (i.e. sending ASP ACTIVE message) a ASP
 *     within an Application Server (AS).
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context, aspId
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT EnableApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    UAL_ConfigPriv config;

    /* 
       This API is used primarily by ASP and IPSP.
    */
    UAL_DEBUG(("\nEnableASP: AS %d ASP %d\n", rContext, aspId));

   if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
   {
       config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));

       if(config == NULL)
       {
           UAL_ERROR(("\nEnableASP: Memory Allocation failed...\n"));
           return !ITS_SUCCESS;
       }
       UAL_CONFIG_PRIV_ASP_INFO(config).asp = rContext;

       ret = SendASP_ACTIVE(config);

       if(ret == ITS_FALSE)
       {
           UAL_ERROR(("\nEnableAS: Enabling of ASP %d for AS %d failed\n", aspId, rContext));
           free(config);
           return !ITS_SUCCESS;
       }    
       free(config);
       return ITS_SUCCESS;
   }
   else
   {
       UAL_ERROR(("\nEnableASP: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
       return !ITS_SUCCESS;
   }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to disable (i.e. sending ASP INACTIVE message) a ASP
 *     within an Application Server (AS).
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context, aspId
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT DisableApplicationServerProcess(ITS_UINT rContext, ITS_INT aspId)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    UAL_ConfigPriv config;

    /*
       This API is used primarily by ASP and IPSP.
    */

    UAL_DEBUG(("\nDisableASP: AS %d ASP %d\n", rContext, aspId));


    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));
 
        if(config == NULL)
        {
            UAL_ERROR(("\nDisableASP: Memory Allocation failed...\n"));
            return !ITS_SUCCESS;
        }
        UAL_CONFIG_PRIV_ASP_INFO(config).asp = rContext;
 
        ret = SendASP_INACTIVE(config);
 
        if(ret == ITS_FALSE)
        {
            UAL_ERROR(("\nDisableAS: Disabling of ASP %d for AS %d failed\n", aspId, rContext));
            free(config);
            return !ITS_SUCCESS;
        }
        free(config);
        return ITS_SUCCESS;
    }
    else
    {
        UAL_ERROR(("\nDisableASP: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the current state of an AS.
 *     It is valid for SG & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetApplicationServerState(ITS_UINT rContext)
{
    RK_Context *rCtxt = NULL;

    UAL_DEBUG(("\nGetAsState: AS is %d\n", rContext));

    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        rCtxt = RKManager_FindEntry(rContext);

        if(rCtxt == NULL)
        {
            UAL_ERROR(("\nGetAsState: Routing Context %d not found...\n", rContext));
            return !ITS_SUCCESS;
        }

        UAL_DEBUG(("\nGetAsState: AS %d state is %d\n", rContext, rCtxt->state));
        return ITS_SUCCESS;
    }
    else
    {
        UAL_ERROR(("\nGetAsState: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the current state of a ASP within an AS.
 *     It is valid for SG & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context, aspId
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetApplicationServerProcessState(ITS_UINT rContext, ITS_INT aspId)
{
    RK_Context *rCtxt = NULL;
    ASPListNode *aspNode = NULL;
    ITS_BOOLEAN matchFound = ITS_FALSE;

    UAL_DEBUG(("\nGetAspState: ASP %d under AS %d\n", aspId, rContext));

    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        rCtxt = RKManager_FindEntry(rContext);

        if(rCtxt == NULL)
        {
            UAL_ERROR(("\nGetAspState: Routing Context %d not found...\n", rContext));
            return !ITS_SUCCESS;
        }

        aspNode = ASPList_Iterate(rCtxt->aspList);
        for(;aspNode; aspNode = ASPList_Iterate(NULL))
        {
            if(aspNode->aspInfo.aspid == aspId)
            {
                matchFound = ITS_TRUE;
                UAL_DEBUG(("\nGetAspState: ASP ID %d found under AS %d\n", aspId, rContext));
                break;
            }
        }

        if(matchFound == ITS_TRUE)
        {
            UAL_DEBUG(("\nASP %d state is %d under AS %d\n", aspId, aspNode->state, rContext));
            return ITS_SUCCESS;
        }
        else
        {
            UAL_ERROR(("\nGetAspState: ASP %d not found under AS %d...\n", aspId, rContext));
            return !ITS_SUCCESS;
        }
    }
    else
    {
        UAL_ERROR(("\nGetAspState: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the local ASP(s) information.
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetLocalApplicationServerProcessInfo()
{
    ASP_Entry* aspRec = NULL;
    ITS_USHORT trid[UAL_MAX_NUM_ASSOC];
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT num_trid, i;

    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        ret = ASPTable_GetAllTransportIds(trid, UAL_MAX_NUM_ASSOC, &num_trid);

        if((ret != ITS_SUCCESS) || (num_trid == 0))
        {
            UAL_DEBUG(("\nGetLocalAspInfo: No ASP(s) configured...\n"));
            return ITS_SUCCESS;
        }

        /* Start getting the information about all the configured ASP(s) */
        for (i = 0; i < num_trid; i++)
        {
            RKListNode* rkList = NULL;

            ret =  ASPTable_FindEntry(trid[i], &aspRec);
 
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("\nGetLocalAspInfo: No ASP Record present for TRID %d\n", trid[i]));
                continue;
            }

            UAL_DEBUG(("\nGetLocalAspInfo: ASPID %d Payload %d TRID %d\n", aspRec->aspId, aspRec->payload,
                                            aspRec->trId));

            if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
                UAL_DEBUG(("\nGetLocalAspInfo: IPSP State is %d\n", aspRec->remoteInfo.state));
            }
            else if(UAL_GL_ITW_MODE == UAL_ITW_ASP)
            {
                UAL_DEBUG(("\nGetLocalAspInfo: ASP State is %d\n", aspRec->state));
            }

            rkList = RKList_Iterate(aspRec->asList);

            if(rkList != NULL)
            {
                for(;rkList; rkList = RKList_Iterate(NULL))
                {
                    RK_Context* ctxt = rkList->entry;

                    if(ctxt != NULL)
                    {
                        ASPListNode *aspNode = NULL;
                        if(ctxt->isMember == ITS_TRUE) /* to display local ASP(s) information */
                        {
                            UAL_DEBUG(("\nGetLocalAspInfo: AS %d AS state %d TM %d\n", ctxt->rCtxt, 
                                            ctxt->state, ctxt->trafficMode));

                        }
                        aspNode = ASPList_Iterate(ctxt->aspList);

                        if(aspNode != NULL)
                        {
                            for(;aspNode; aspNode = ASPList_Iterate(NULL))
                            {
                                if(aspNode->trId != 0x00)
                                {
                                    UAL_DEBUG(("\nGetLocalAspInfo: ASP %d ASP state %d\n",aspNode->aspInfo.aspid,
                                                              aspNode->state )); 
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                UAL_WARNING(("\nGetLocalAspInfo: No AS configured for ASP %d\n", aspRec->aspId)); 
                continue;
            } 
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAspInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the remote ASP(s) information.
 *     It is valid for SG & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetRemoteApplicationServerProcessInfo()
{
    ASP_Entry* aspRec = NULL;
    ITS_USHORT trid[UAL_MAX_NUM_ASSOC];
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT num_trid, i;

    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        ret = ASPTable_GetAllTransportIds(trid, UAL_MAX_NUM_ASSOC, &num_trid);

        if((ret != ITS_SUCCESS) || (num_trid == 0))
        {
            UAL_DEBUG(("\nGetRemoteAspInfo: No ASP(s) configured...\n"));
            return ITS_SUCCESS;
        }

        /* Start getting the information about all the configured ASP(s) */
        for (i = 0; i < num_trid; i++)
        {
            RKListNode* rkList = NULL;

            ret =  ASPTable_FindEntry(trid[i], &aspRec);
 
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("\nGetRemoteAspInfo: No ASP Record present for TRID %d\n", trid[i]));
                continue;
            }

            UAL_DEBUG(("\nGetRemoteAspInfo: ASPID %d Payload %d TRID %d\n", aspRec->aspId, aspRec->payload,
                                            aspRec->trId));

            if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
                UAL_DEBUG(("\nGetRemoteAspInfo: IPSP State is %d\n", aspRec->remoteInfo.state));
            }
            else if(UAL_GL_ITW_MODE == UAL_ITW_SG)
            {
                UAL_DEBUG(("\nGetRemoteAspInfo: ASP State is %d\n", aspRec->state));
            }

            rkList = RKList_Iterate(aspRec->asList);

            if(rkList != NULL)
            {
                for(;rkList; rkList = RKList_Iterate(NULL))
                {
                    RK_Context* ctxt = rkList->entry;

                    if(ctxt != NULL)
                    {
                        ASPListNode *aspNode = NULL;
                        if(ctxt->isMember == ITS_FALSE) /* to display remote ASP(s) information */
                        {
                            UAL_DEBUG(("\nGetRemoteAspInfo: AS %d AS state %d TM %d\n", ctxt->rCtxt, 
                                            ctxt->state, ctxt->trafficMode));

                        }
                        aspNode = ASPList_Iterate(ctxt->aspList);

                        if(aspNode != NULL)
                        {
                            for(;aspNode; aspNode = ASPList_Iterate(NULL))
                            {
                                if(aspNode->trId != 0x00)
                                {
                                    UAL_DEBUG(("\nGetRemoteAspInfo: ASP %d ASP state %d\n",aspNode->aspInfo.aspid,
                                                              aspNode->state )); 
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                UAL_WARNING(("\nGetRemoteAspInfo: No AS configured for ASP %d\n", aspRec->aspId)); 
                continue;
            } 
        }
    }
    else
    {
        UAL_ERROR(("\nGetRemoteAspInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     This function is a helper function for API GetLocalApplicationServerInfo.
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

static int Dump_LocalAS_Info(ITS_INT context, ITS_POINTER data,
                             void* in, void* out)
{
    RK_Context *rCtxt = (RK_Context*)data;

    if((rCtxt != NULL) && rCtxt->isMember)
    {
        UAL_DEBUG(("\nAS %d info: state %d tm %d family %s dpc %d sio %d ssn %d\n", rCtxt->rCtxt,
                                  rCtxt->state, rCtxt->trafficMode, rCtxt->family,
                                  rCtxt->asInfo.dpc, rCtxt->asInfo.criteria.sio,
                                  rCtxt->asInfo.criteria.ssn));

        if(rCtxt->aspList && ASP_LIST_COUNT(rCtxt->aspList))
        {
            ASPListNode* nd = ASPList_Iterate(rCtxt->aspList);

            for(; nd; nd = ASPList_Iterate(NULL))
            {
                UAL_DEBUG(("\nAS %d ASP %d info: trId %d state %d \n", rCtxt->rCtxt,
                                    nd->aspInfo.aspid, nd->trId, nd->state));
            }
        }
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the local AS(s) information.
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetLocalApplicationServerInfo()
{
    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))  
    {
        if(AS_CONTEXT_COUNT != 0)
        {
            HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                               NULL, Dump_LocalAS_Info);
        }
        else
        {
            UAL_DEBUG(("\nGetLocalAsInfo: No local AS configured...\n"));
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     This function is a helper function for API GetRemoteApplicationServerInfo.
 *     It is valid for SG & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

static int Dump_RemoteAS_Info(ITS_INT context, ITS_POINTER data,
                              void* in, void* out)
{
    RK_Context *rCtxt = (RK_Context*)data;

    if((rCtxt != NULL) && !rCtxt->isMember)
    {
        UAL_DEBUG(("\nAS %d info: state %d tm %d family %s dpc %d sio %d ssn %d\n", rCtxt->rCtxt,
                                  rCtxt->state, rCtxt->trafficMode, rCtxt->family,
                                  rCtxt->asInfo.dpc, rCtxt->asInfo.criteria.sio,
                                  rCtxt->asInfo.criteria.ssn));

        if(rCtxt->aspList && ASP_LIST_COUNT(rCtxt->aspList))
        {
            ASPListNode* nd = ASPList_Iterate(rCtxt->aspList);

            for(; nd; nd = ASPList_Iterate(NULL))
            {
                UAL_DEBUG(("\nAS %d ASP %d info: trId %d state %d \n", rCtxt->rCtxt,
                                    nd->aspInfo.aspid, nd->trId, nd->state));
            }
        }
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *     This API is used to get the remote AS(s) information.
 *     It is valid for SG & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

ITS_INT GetRemoteApplicationServerInfo()
{
    if((UAL_GL_ITW_MODE == UAL_ITW_SG) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
    {
        if(AS_CONTEXT_COUNT != 0)
        {
            HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                               NULL, Dump_RemoteAS_Info);
        }
        else
        {
            UAL_DEBUG(("\nGetRemoteAsInfo: No remote AS configured...\n"));
        }
    }
    else
    {
        UAL_ERROR(("\nGetRemoteAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     This function is a helper function for API GetLocalApplicationServerInfo.
 *     It is valid for ASP & IPSP Interworking Modes.
 *
 *  Input Parameters:
 *     Routing Context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 ****************************************************************************/

static int SendASPINACTIVE_ASPDOWN_For_All_AS(ITS_INT context, ITS_POINTER data,
                             void* in, void* out)
{
    RK_Context *rCtxt = (RK_Context*)data;
    UAL_ConfigPriv config;
    int ret = ITS_SUCCESS;

    if((rCtxt != NULL) && rCtxt->isMember)
    {
        UAL_DEBUG(("\nAS %d info: state %d tm %d family %s dpc %d sio %d ssn %d\n", rCtxt->rCtxt,
                                  rCtxt->state, rCtxt->trafficMode, rCtxt->family,
                                  rCtxt->asInfo.dpc, rCtxt->asInfo.criteria.sio,
                                  rCtxt->asInfo.criteria.ssn));

        config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));

        if(config == NULL)
        {
            UAL_ERROR(("\nDisableASP: Memory Allocation failed...\n"));
            return !ITS_SUCCESS;
        }
        UAL_CONFIG_PRIV_ASP_INFO(config).asp = rCtxt->rCtxt;
        ret = SendASP_INACTIVE(config);

        if(ret == ITS_FALSE)
        {
            UAL_ERROR(("\nDisableAS: Disabling of ASP in AS %d failed\n", rCtxt->rCtxt));
            free(config);
            return !ITS_SUCCESS;
        }
        usleep(250000);
        ret = SendASP_DOWN(config);
        if(ret == ITS_FALSE)
        {
            UAL_ERROR(("Failed to send ASP Down"));
            free(config);
            return !ITS_SUCCESS;
        }
        free(config);
        //return ITS_SUCCESS;
        //
        if(rCtxt->aspList && ASP_LIST_COUNT(rCtxt->aspList))
        {
            ASPListNode* nd = ASPList_Iterate(rCtxt->aspList);

            for(; nd; nd = ASPList_Iterate(NULL))
            {
                UAL_DEBUG(("\nAS %d ASP %d info: trId %d state %d \n", rCtxt->rCtxt,
                                    nd->aspInfo.aspid, nd->trId, nd->state));
            }
        }
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}

ITS_INT SendASPInactiveAndASPDown()
{
    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))  
    {
        if(AS_CONTEXT_COUNT != 0)
        {
            HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                               NULL, SendASPINACTIVE_ASPDOWN_For_All_AS);
        }
        else
        {
            UAL_DEBUG(("\nGetLocalAsInfo: No local AS configured...\n"));
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

ITS_INT SendASPUP()
{
    ASP_Entry* aspRec = NULL;
    ITS_USHORT trid[UAL_MAX_NUM_ASSOC];
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT num_trid, i;

    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))  
    {
        ret = ASPTable_GetAllTransportIds(trid, UAL_MAX_NUM_ASSOC, &num_trid);

        if((ret != ITS_SUCCESS) || (num_trid == 0))
        {
            UAL_DEBUG(("\nGetLocalAspInfo: No ASP(s) configured...\n"));
            return ITS_SUCCESS;
        }
        /* Start getting the information about all the configured ASP(s) */
        for (i = 0; i < num_trid; i++)
        {
            RKListNode* rkList = NULL;

            ret =  ASPTable_FindEntry(trid[i], &aspRec);
            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("\nGetLocalAspInfo: No ASP Record present for TRID %d\n", trid[i]));
                continue;
            }

            ret = UAL_SendASPUP(aspRec);

            if (ret != ITS_SUCCESS)
            {    
                UAL_ERROR(("SendASPUP: Could not send "
                        "ASPUP, code %d.\n", ret));

                return !ITS_SUCCESS;
            }    
            UAL_DEBUG(("Successfully sent ASPUP Message to TRID %d\n", trid[i]));
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

static int SendASPACTIVE_For_All_AS(ITS_INT context, ITS_POINTER data,
                             void* in, void* out)
{
    RK_Context *rCtxt = (RK_Context*)data;
    UAL_ConfigPriv config;
    int ret = ITS_SUCCESS;

    if((rCtxt != NULL) && rCtxt->isMember)
    {
        UAL_DEBUG(("\nAS %d info: state %d tm %d family %s dpc %d sio %d ssn %d\n", rCtxt->rCtxt,
                                  rCtxt->state, rCtxt->trafficMode, rCtxt->family,
                                  rCtxt->asInfo.dpc, rCtxt->asInfo.criteria.sio,
                                  rCtxt->asInfo.criteria.ssn));

        if(rCtxt->state != UAL_AS_DOWN)
        {
            config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));

            if(config == NULL)
            {
                UAL_ERROR(("\nDisableASP: Memory Allocation failed...\n"));
                return !ITS_SUCCESS;
            }
            UAL_CONFIG_PRIV_ASP_INFO(config).asp = rCtxt->rCtxt;
            ret = SendASP_ACTIVE(config);

            UAL_DEBUG(("Return Value of ASP_Active : %d\n", ret));

            if(ret == ITS_FALSE)
            {
                UAL_ERROR(("\nDisableAS: Disabling of ASP in AS %d failed\n", rCtxt->rCtxt));
                free(config);
                return !ITS_SUCCESS;
            }

            if(rCtxt->aspList && ASP_LIST_COUNT(rCtxt->aspList))
            {
                ASPListNode* nd = ASPList_Iterate(rCtxt->aspList);

                for(; nd; nd = ASPList_Iterate(NULL))
                {
                    UAL_DEBUG(("\nAS %d ASP %d info: trId %d state %d \n", rCtxt->rCtxt,
                                nd->aspInfo.aspid, nd->trId, nd->state));
                }
            }
            UAL_DEBUG(("ASP Active sent successfully : %d", ret));
            return ITS_SUCCESS;
        }
        else
        {
            UAL_WARNING(("AS State is %d not initiating ASP Active", rCtxt->state));
        }
    }
    return !ITS_SUCCESS;
}

ITS_INT SendASPActiveFromApp()
{
    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))  
    {
        if(AS_CONTEXT_COUNT != 0)
        {
            HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                               NULL, SendASPACTIVE_For_All_AS);
        }
        else
        {
            UAL_DEBUG(("\nGetLocalAsInfo: No local AS configured...\n"));
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}

ITS_INT SendASPACTIVE(ITS_UINT rid)
{
    RK_Context *rctxt = NULL;
    struct UAL_Config cfg;
    int ret = ITS_SUCCESS;
    UAL_ConfigInit(&cfg);

    if((rctxt = RKManager_FindEntry(rid)) == NULL)
    {
        UAL_ERROR(("Not able to find Routing Key Entry")); 
        return !ITS_SUCCESS;
    }

    UAL_SetASPInfo(&cfg, UAL_CMD_ASP_ACTIVE, rid);

    ret = SendASP_ACTIVE(cfg.priv);
    if(ret == ITS_SUCCESS)
    {
        UAL_DEBUG(("ASP Active Sent successfully")); 
    }
    else
    {
        UAL_ERROR(("ASP Active Sent successfully")); 
    }
    return ret;
}

static int SendASPINACTIVE_For_All_AS(ITS_INT context, ITS_POINTER data,
                             void* in, void* out)
{
    RK_Context *rCtxt = (RK_Context*)data;
    UAL_ConfigPriv config;
    int ret = ITS_SUCCESS;

    if((rCtxt != NULL) && rCtxt->isMember)
    {
        UAL_DEBUG(("\nAS %d info: state %d tm %d family %s dpc %d sio %d ssn %d\n", rCtxt->rCtxt,
                                  rCtxt->state, rCtxt->trafficMode, rCtxt->family,
                                  rCtxt->asInfo.dpc, rCtxt->asInfo.criteria.sio,
                                  rCtxt->asInfo.criteria.ssn));

        config = (struct UALConfigVar *)calloc(1, sizeof(struct UALConfigVar));

        if(config == NULL)
        {
            UAL_ERROR(("\nDisableASP: Memory Allocation failed...\n"));
            return !ITS_SUCCESS;
        }
        UAL_CONFIG_PRIV_ASP_INFO(config).asp = rCtxt->rCtxt;
        ret = SendASP_INACTIVE(config);

        if(ret == ITS_FALSE)
        {
            UAL_ERROR(("\nDisableAS: Disabling of ASP in AS %d failed\n", rCtxt->rCtxt));
            free(config);
            return !ITS_SUCCESS;
        }

        if(rCtxt->aspList && ASP_LIST_COUNT(rCtxt->aspList))
        {
            ASPListNode* nd = ASPList_Iterate(rCtxt->aspList);

            for(; nd; nd = ASPList_Iterate(NULL))
            {
                UAL_DEBUG(("\nAS %d ASP %d info: trId %d state %d \n", rCtxt->rCtxt,
                                    nd->aspInfo.aspid, nd->trId, nd->state));
            }
        }
        return ITS_SUCCESS;
    }
    return !ITS_SUCCESS;
}

ITS_INT SendASPINACTIVE()
{
    if((UAL_GL_ITW_MODE == UAL_ITW_ASP) || (UAL_GL_ITW_MODE == UAL_ITW_IPSP))  
    {
        if(AS_CONTEXT_COUNT != 0)
        {
            HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
                    NULL, SendASPINACTIVE_For_All_AS);
        }
        else
        {
            UAL_DEBUG(("\nGetLocalAsInfo: No local AS configured...\n"));
        }
    }
    else
    {
        UAL_ERROR(("\nGetLocalAsInfo: Not valid for Interworking Mode %d\n", UAL_GL_ITW_MODE));
        return !ITS_SUCCESS;
    }
    return ITS_SUCCESS;
}


#if 0
ITS_UINT GetApplicationServerProcessStats()
{

}
#endif
