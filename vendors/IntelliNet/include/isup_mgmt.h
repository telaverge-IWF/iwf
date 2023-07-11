/*********************************-*-H-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: isup_mgmt.h,v 1.1.2.1 2010/06/24 08:24:54 ssingh Exp $
 *
 * LOG: $Log: isup_mgmt.h,v $
 * LOG: Revision 1.1.2.1  2010/06/24 08:24:54  ssingh
 * LOG: SMLC #3112; splitedd isup specific OSS APIs from ss7_mgmt.h
 * LOG:
 *
 ****************************************************************************/
#ifndef ISUP_MGMT_H
#define ISUP_MGMT_H

#include <its.h>
#include <its_pegs.h>
#include <its_alarm.h>
#include <its_timers.h>
#include <ss7_mgmt.h>
#include <dbc_serv.h>


/*******************************
 *
 *       ISUP OSS APIs
 *
 *******************************/

#define ISUP_CFG_MAX_TIMERS 62
#define ISUP_CFG_MAX_TIMERS_CCITT 39
#define ISUP_CFG_MAX_TIMERS_ANSI 51

#define ISUP_ALL_PEGS 255

#if defined(__cplusplus)
extern "C"
{
#endif

/* Structure for ISUP General Config */
typedef struct ISUP_GeneralCfg
{
    MGMT_AlarmLevel     alarmLevel;
    ITS_BOOLEAN         debugTrace;
    ITS_OCTET           debugTraceOutput;
    ITS_BOOLEAN         warningTrace;
    ITS_OCTET           warningTraceOutput;
    ITS_BOOLEAN         errorTrace;
    ITS_OCTET           errorTraceOutput;
    ITS_BOOLEAN         criticalTrace;
    ITS_OCTET           criticalTraceOutput;
    ITS_BOOLEAN         eventTrace;
    ITS_OCTET           eventTraceOutput;
} ISUP_GeneralCfg;

/* Structure for ISUP Configuration Key */
typedef struct
{
    ITS_UINT    opc;
    ITS_UINT    dpc;
    ITS_OCTET   sio;
}
ISUP_CFG_KEY;

#if defined(ANSI)
#define ISUP_MAX_CFG_CICS_PER_CKGP 24
#else
#define ISUP_MAX_CFG_CICS_PER_CKGP 32
#endif

/* Structure for Circuit Group Information */
typedef struct
{
    ITS_USHORT          ckgp_id;
    ITS_UINT            usable_cics[1];
    ITS_OCTET           contl[ISUP_MAX_CFG_CICS_PER_CKGP];
}
ISUP_CFG_CKGP_INFO;

/* Enumeration for Exchange Type */
typedef enum
{
    ISUP_CFG_EXCHANGE_TYPE_A =0,
    ISUP_CFG_EXCHANGE_TYPE_B,

    ISUP_CFG_EXCHANGE_TYPE_INV
}
ISUP_CFG_EXCHANGE_TYPE;

/* Enumeration for type of timer handling */
typedef enum
{
    ISUP_CFG_TMR_HNDL_STACK,
    ISUP_CFG_TMR_HNDL_APP
}
ISUP_CFG_TMR_HNDL;

/* Structure for Timer Info */
typedef struct
{
    ISUP_CFG_TMR_HNDL    tmr_cfg_hndl_layer;
    ITS_UINT             tmr_cfg_value;
}
ISUP_CFG_TMR_INFO;

/* Enumeration for Destination Status */
typedef enum
{
    ISUP_CFG_DEST_UNREACHABLE = 0,
    ISUP_CFG_DEST_REACHABLE
}
ISUP_CFG_DEST_STATUS;

/* Enumeration for Congestion Levels */
typedef enum
{
    ISUP_CFG_RMTCONGES_OFF,
    ISUP_CFG_RMTCONGES_LEVEL1,
    ISUP_CFG_RMTCONGES_LEVEL2,
    ISUP_CFG_RMTCONGES_LEVEL3
}
ISUP_CFG_CONGES;

/* Enumeration for Remote ISUP Status */
typedef enum
{
    ISUP_CFG_REMOTE_AVAILABLE = 0,
    ISUP_CFG_REMOTE_UNAVAILABLE,
    ISUP_CFG_REMOTE_UNEQUIPPED
}
ISUP_CFG_REMOTE_ISUP_STATUS;

/* Structure for Destination Info */
typedef struct
{
    ISUP_CFG_KEY                    cfg;
    ITS_INT                         variant;
    ISUP_CFG_EXCHANGE_TYPE          exchange_type;
    ISUP_CFG_CONGES                     congesInd;
    ISUP_CFG_DEST_STATUS            dest_reachable;
    ISUP_CFG_REMOTE_ISUP_STATUS     remote_isup_stat;
    ISUP_CFG_TMR_INFO               timer_info[ISUP_CFG_MAX_TIMERS];
}
ISUP_CFG_DEST_INFO;

/* Structure for ISUP Peg Info */
typedef struct
{
    ITS_UINT    pegId;
    ITS_INT     pegVal;
    char        pegDesc[ITS_PATH_MAX];
}
ISUP_CFG_PEGS;

/* Destination info struct */

typedef struct
{
    ISUP_CFG_DEST_INFO **info;
    int *noEnt;
}
ISUP_CFG_ALLDEST_INFO;

/*
 * * * * * * ANSI ISUP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGeneralCfg_ANSI(ISUP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetGeneralCfg_ANSI(ISUP_GeneralCfg* genCfg);

/*
 * CICs Add/Delete/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddCics_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_USHORT range,
                                           ITS_OCTET ctrl);
ITSSS7DLLAPI ITS_INT ISUP_OSS_DeleteCics_ANSI(ISUP_CFG_KEY cfg,
                                              ITS_USHORT cic,
                                              ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCics_ANSI(ISUP_CFG_KEY cfg,
                                           ISUP_CFG_CKGP_INFO** cics,
                                           int* numCics);

/*
 * CIC State Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicState_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET *cicState);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCicState_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET cicState);

/*
 * Dest Info Add/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddDestInfo_ANSI(ISUP_CFG_KEY cfg,
                                               ISUP_VAR_TYPE variant,
                                               ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetDestInfo_ANSI(ISUP_CFG_KEY cfg,
                                               ISUP_CFG_DEST_INFO* info);

/*
 * Exchange Type Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetExchangeType_ANSI(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetExchangeType_ANSI(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_EXCHANGE_TYPE* exchType);

/*
 * Congestion Level Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCongLevel_ANSI(ITS_OCTET congLevel,
                                                ITS_UINT congValue);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCongLevel_ANSI(ITS_OCTET congLevel,
                                                ITS_UINT* congValue);

/*
 * Variant Add
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddVariant_ANSI(ISUP_VAR_TYPE variant);

/*
 * Timers Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetTimer_ANSI(ISUP_CFG_KEY cfg,
                                            ITS_UINT timerId,
                                            ITS_UINT timerVal,
                                            ISUP_CFG_TMR_HNDL handlBy);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetTimers_ANSI(ISUP_CFG_KEY cfg,
                                             ISUP_CFG_TMR_INFO* timers);

/*
 * Gen Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGenPegs_ANSI(ISUP_CFG_PEGS* pegs,
                                              int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearGenPeg_ANSI(ITS_OCTET pegId);

/*
 * Msg Sent Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgSentPegs_ANSI(ISUP_CFG_KEY cfg,
                                                  ISUP_CFG_PEGS* pegs,
                                                  int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgSentPegs_ANSI(ISUP_CFG_KEY cfg);

/*
 * Msg Received Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg,
                                                  ISUP_CFG_PEGS* pegs,
                                                  int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg);

/*
 * CIC Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicPegs_ANSI(ISUP_CFG_KEY cfg,
                                              ITS_USHORT cic,
                                              ISUP_CFG_PEGS* pegs,
                                              ITS_OCTET* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearCicPeg_ANSI(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_OCTET pegId);

/*
 * Msg Send
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendUBL_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendBLO_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRSC_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRLC_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendGRS_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGU_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_OCTET msgType,
                                           ITS_USHORT range,
                                           ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGB_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_OCTET msgType,
                                           ITS_USHORT range,
                                           ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCQM_ANSI(ISUP_CFG_KEY cfg,
                                           ITS_USHORT cic,
                                           ITS_USHORT range);

/*
 * * * * * * CCITT ISUP OSS APIs * * * * *
 */

/*
 * General Config
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg);

/*
 * CICs Add/Delete/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddCics_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_USHORT range,
                                            ITS_OCTET ctrl);
ITSSS7DLLAPI ITS_INT ISUP_OSS_DeleteCics_CCITT(ISUP_CFG_KEY cfg,
                                               ITS_USHORT cic,
                                               ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCics_CCITT(ISUP_CFG_KEY cfg,
                                            ISUP_CFG_CKGP_INFO** cics,
                                            int* numCics);

/*
 * CIC State Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicState_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET *cicState);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCicState_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET cicState);

/*
 * Dest Info Add/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddDestInfo_CCITT(ISUP_CFG_KEY cfg,
                                                ISUP_VAR_TYPE variant,
                                                ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetDestInfo_CCITT(ISUP_CFG_KEY cfg,
                                                ISUP_CFG_DEST_INFO* info);

/* Get configuration and status information of all the destinations */
ITSSS7DLLAPI int ISUP_GetDestIterProc_ANSI(ITS_INT context, ITS_POINTER data,
                                           void *in, void *out);

ITSSS7DLLAPI int ISUP_GetDestIterProc_CCITT(ITS_INT context, ITS_POINTER data,
                                           void *in, void *out);
/*
 * Exchange Type Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetExchangeType_CCITT(ISUP_CFG_KEY cfg,
                                                    ISUP_CFG_EXCHANGE_TYPE exchType);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetExchangeType_CCITT(ISUP_CFG_KEY cfg,
                                                    ISUP_CFG_EXCHANGE_TYPE* exchType);

/*
 * Congestion Level Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetCongLevel_CCITT(ITS_OCTET congLevel,
                                                 ITS_UINT congValue);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCongLevel_CCITT(ITS_OCTET congLevel,
                                                 ITS_UINT* congValue);

/*
 * Variant Add
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_AddVariant_CCITT(ISUP_VAR_TYPE variant);

/*
 * Timers Set/Get
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SetTimer_CCITT(ISUP_CFG_KEY cfg,
                                              ITS_UINT timerId,
                                              ITS_UINT timerVal,
                                              ISUP_CFG_TMR_HNDL handlBy);
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetTimers_CCITT(ISUP_CFG_KEY cfg,
                                              ISUP_CFG_TMR_INFO* timers);

/*
 * Gen Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetGenPegs_CCITT(ISUP_CFG_PEGS* pegs,
                                               int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearGenPeg_CCITT(ITS_OCTET pegId);

/*
 * Msg Sent Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgSentPegs_CCITT(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_PEGS* pegs,
                                                   int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgSentPegs_CCITT(ISUP_CFG_KEY cfg);

/*
 * Msg Received Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg,
                                                   ISUP_CFG_PEGS* pegs,
                                                   int* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg);

/*
 * CIC Pegs Get/Clear
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_GetCicPegs_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ISUP_CFG_PEGS* pegs,
                                            ITS_OCTET* numPegs);
ITSSS7DLLAPI ITS_INT ISUP_OSS_ClearCicPeg_CCITT(ISUP_CFG_KEY cfg,
                                                ITS_USHORT cic,
                                                ITS_OCTET pegId);

/*
 * Msg Send
 */
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendUBL_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendBLO_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRSC_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendRLC_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendGRS_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_USHORT range);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGU_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_OCTET msgType,
                                            ITS_USHORT range,
                                            ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCGB_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_OCTET msgType,
                                            ITS_USHORT range,
                                            ITS_UINT status);
ITSSS7DLLAPI ITS_INT ISUP_OSS_SendCQM_CCITT(ISUP_CFG_KEY cfg,
                                            ITS_USHORT cic,
                                            ITS_USHORT range);

#if defined(__cplusplus)
}
#endif

#endif /* ISUP_MGMT_H */

