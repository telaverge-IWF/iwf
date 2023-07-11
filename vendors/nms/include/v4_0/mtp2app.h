/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                       by Natural MicroSystems                        **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems                          **
**                                                                      **
*************************************************************************/
#ifndef _MTP2APP_H_
#define _MTP2APP_H_

#define MTP2_ENT            0x16
#define MAXMTP2PKT          272
#define MAXMTP2DATA         272
#define MAXMTP2RXDATA       1024
#define FILLER_COUNT        8
#define MAX_LINK_NUM        15

#ifdef UNIX
#pragma pack(1)
#endif

/* The following structures are used as templates laid over the data area of the MTP2PKT */
/*******************************************************************************************/
typedef struct                          /* Bind Request */
{
    U8      userId[2];
    U8      srcEnt;
    U8      srcInst;
}
BindReq;

#define MTP2_BIND_REQ_SET_USER_ID(x, v)		\
	((x).userId[0] = ((v) >> 8) & 0xFFU,	\
     (x).userId[1] = (v) & 0xFFU)

#define MTP2_BIND_REQ_GET_USER_ID(x)		\
	(((x).userId[0] << 8) | (x).userId[1])

/*******************************************************************************************/
typedef struct                          /* Connect Request */
{
    U8      status;
} ConReq;

/* Connect Request Status Field Values */
#define CONREQSTA_LVL_1             0
#define CONREQSTA_LVL_2_EMRG        1
#define CONREQSTA_LVL_2_NORM        2
#define CONREQSTA_LVL_1_2_EMRG      3
#define CONREQSTA_LVL_1_2_NORM      4
#define CONREQSTA_POWER_ON          5
#define CONREQSTA_AFTER_POWER_ON    6

/*******************************************************************************************/
typedef struct                          /* Data Request */
{
    U8      data[MAXMTP2DATA];
} DatReq;

/*******************************************************************************************/
typedef struct                          /* Data Confirmation */
{
    U8      status;
    U8      credit;
    U8      data[MAXMTP2DATA];
} DatCfm;
/* Data Confirmation Status Field Values */
#define DATCFMSTA_MORE              0
#define DATCFMSTA_LAST              1
#define DATCFMSTA_NUM_ACKED         2

/*******************************************************************************************/
typedef struct                          /* Data Indication */
{
    U8      data[MAXMTP2DATA];
} DatInd;

/*******************************************************************************************/
typedef struct                          /* Disconnect Request */
{
    U8      reason[2];
} DisReq;

#define MTP2_DIS_REQ_SET_REASON(x, v)		\
	((x).reason[0] = ((v) >> 8) & 0xFFU,	\
     (x).reason[1] = (v) & 0xFFU)

#define MTP2_DIS_REQ_GET_REASON(x)			\
	(((x).reason[0] << 8) | (x).reason[1])

/* Disconnect Request Reason Field Values */
#define DISCREQ_MGMT_REQ            0
#define DISCREQ_LVL_1_TOO           10
#define DISCREQ_LVL_2_ONLY          13

/*******************************************************************************************/
typedef struct                          /* Disconnect Indication */
{
    U8      reason[2];
} DisInd;

#define MTP2_DIS_IND_SET_REASON(x, v)		\
	((x).reason[0] = ((v) >> 8) & 0xFFU,	\
     (x).reason[1] = (v) & 0xFFU)

#define MTP2_DIS_IND_GET_REASON(x)			\
	(((x).reason[0] << 8) | (x).reason[1])

/* Disconnect Indication Reason Field Values */
#define DISCIND_MGMT_REQ            0
#define DISCIND_ERR_RATE            1
#define DISCIND_LONG_REALIGN        2
#define DISCIND_ACK_DELAY           3
#define DISCIND_EQUIP_FAIL          4
#define DISCIND_BSN_UNREAS          5
#define DISCIND_FIB_UNREAS          6

/*******************************************************************************************/
typedef struct                          /* Flow Control Request */
{
    U8      action[2];
    U8      flcLevel;
} FlowReq;

#define MTP2_FLOW_REQ_SET_ACTION(x, v)		\
	((x).action[0] = ((v) >> 8) & 0xFFU,	\
     (x).action[1] = (v) & 0xFFU)

#define MTP2_FLOW_REQ_GET_ACTION(x)			\
	(((x).action[0] << 8) | (x).action[1])

/* Flow Control Request Action Field Values */
#define FLOWREQ_SETLEVEL            0           /* <3.8>  See below */
/* <3.8>  The MTP2 task only accepts the value zero for action
#define FLOWREQ_START               1
#define FLOWREQ_STOP                1
*/

/*******************************************************************************************/
typedef struct                          /* Flow Control Indication */
{
    U8		action[2];
    U8      flcLevel;
} FlowInd;

#define MTP2_FLOW_IND_SET_ACTION(x, v)		\
	((x).action[0] = ((v) >> 8) & 0xFFU,	\
     (x).action[1] = (v) & 0xFFU)

#define MTP2_FLOW_IND_GET_ACTION(x)			\
	(((x).action[0] << 8) | (x).action[1])

/* Flow Control Indication Action Field Values */
#define FLOWIND_STARTED             0
#define FLOWIND_STOPPED             1

/*******************************************************************************************/
typedef struct                          /* Status Request */
{
    U8      action[2];
    U8      status[4];
} StaReq;

#define MTP2_STA_REQ_SET_ACTION(x, v)		\
	((x).action[0] = ((v) >> 8) & 0xFFU,	\
     (x).action[1] = (v) & 0xFFU)

#define MTP2_STA_REQ_GET_ACTION(x)			\
	(((x).action[0] << 8) | (x).action[1])

#define MTP2_STA_REQ_SET_STATUS(x, v)		\
	((x).status[0] = ((v) >> 24) & 0xFFU,	\
     (x).status[1] = ((v) >> 16) & 0xFFU,	\
	 (x).status[2] = ((v) >> 8) & 0xFFU,	\
     (x).status[3] = (v) & 0xFFU)

#define MTP2_STA_REQ_GET_STATUS(x)			\
	(((x).status[0] << 24) |				\
	 ((x).status[1] << 16) |				\
	 ((x).status[1] << 8) |					\
	 (x).status[1])

/* Status Request Action Field Values */
#define STAREQ_CHANGE_STATUS        0
#define STAREQ_GET_BSN              1
#define STAREQ_GET_UNACKED          2
#define STAREQ_DROP_UNACKED         3

/* Status Request Status Field Values */
#define STAREQ_STS_LCL_DOWN         0
#define STAREQ_STS_LCL_UP           1
#define STAREQ_STS_START_EMERG      2
#define STAREQ_STS_END_EMERG        3

/*******************************************************************************************/
typedef struct                          /* Status Confirmation */
{
    U8		action[2];
    U8		status[4];
} StaCfm;

#define MTP2_STA_CFM_SET_ACTION(x, v)		\
	((x).action[0] = ((v) >> 8) & 0xFFU,	\
     (x).action[1] = (v) & 0xFFU)

#define MTP2_STA_CFM_GET_ACTION(x)			\
	(((x).action[0] << 8) | (x).action[1])

#define MTP2_STA_CFM_SET_STATUS(x, v)		\
	((x).status[0] = ((v) >> 24) & 0xFFU,	\
     (x).status[1] = ((v) >> 16) & 0xFFU,	\
	 (x).status[2] = ((v) >> 8) & 0xFFU,	\
     (x).status[3] = (v) & 0xFFU)

#define MTP2_STA_CFM_GET_STATUS(x)			\
	(((x).status[0] << 24) |				\
	 ((x).status[1] << 16) |				\
	 ((x).status[2] << 8) |					\
	 (x).status[3])

/* Status Confirmation Action Field Values */
#define STACFM_NOACTION             0
#define STACFM_BSN                  1
#define STACFM_NO_UNACKED           3

/* Status Confirm Status Field Values */
#define STACFM_STS_LCL_DOWN         0
#define STACFM_STS_LCL_UP           1

/*******************************************************************************************/
typedef struct                          /* Status Indication */
{
    U8      status;
} StaInd;

/*******************************************************************************************/
typedef struct                          /* Status Response */
{
    U8     status[4];
} StaRsp;

#define MTP2_STA_RSP_SET_STATUS(x, v)		\
	((x).status[0] = ((v) >> 24) & 0xFFU,	\
     (x).status[1] = ((v) >> 16) & 0xFFU,	\
	 (x).status[2] = ((v) >> 8) & 0xFFU,	\
     (x).status[3] = (v) & 0xFFU)

#define MTP2_STA_RSP_GET_STATUS(x)			\
	(((x).status[0] << 24) |				\
	 ((x).status[1] << 16) |				\
	 ((x).status[1] << 8) |					\
	 (x).status[1])

/* Status Indication/Response Status Field Values */
#define STAIND_REM_DOWN             0
#define STAIND_REM_UP               1


/*******************************************************************************************/
/* -----------------10/2/97 2:47PM-------------------
 * MTP2 Message Types
 * --------------------------------------------------*/
#define MTP2_BIND_REQ       0x04            /* Bind request */
#define MTP2_BIND_CFM       0x05            /* Bind confirm */

#define MTP2_UNBIND_REQ     0x08            /* Unbind request */
#define MTP2_UNBIND_CFM     0x09            /* Unbind confirm */

#define MTP2_CONN_REQ       0x0c            /* Connect request */
#define MTP2_CONN_CFM       0x0d            /* Connect confirm */

#define MTP2_DISC_REQ       0x10            /* Disconnect request */
#define MTP2_DISC_CFM       0x11            /* Disconnect confirm */
#define MTP2_DISC_IND       0x12            /* Disconnect indication */
#define MTP2_DISC_RSP       0x13            /* Disconnect response */

#define MTP2_DATA_REQ       0x14            /* Data request */
#define MTP2_DATA_CFM       0x15            /* Data confirm */
#define MTP2_DATA_IND       0x16            /* Data indication */

#define MTP2_FLOW_REQ       0x28            /* Flow ctrl request */
#define MTP2_FLOW_CFM       0x29            /* Flow ctrl confirm */
#define MTP2_FLOW_IND       0x2a            /* Flow ctrl indication */
#define MTP2_FLOW_RSP       0x2b            /* Flow ctrl response */

#define MTP2_STAT_REQ       0x78            /* Status request */
#define MTP2_STAT_CFM       0x79            /* Status confirm */
#define MTP2_STAT_IND       0x7a            /* Status indication */
#define MTP2_STAT_RSP       0x7b            /* Status response */

typedef struct
{
    CPIHDR  hdr;
    U8      start[2];
    U8      end[2];
}
MTP2HDR;

#define MTP2HDR_SET_START(x, v)				\
	((x).start[0] = ((v) >> 8) & 0xFFU,		\
	 (x).start[1] = (v) & 0xFFU)

#define MTP2HDR_GET_START(x)				\
	(((x).start[0] << 8) | (x).start[1])

#define MTP2HDR_SET_END(x, v)				\
	((x).end[0] = ((v) >> 8) & 0xFFU,		\
	 (x).end[1] = (v) & 0xFFU)

#define MTP2HDR_GET_END(x)					\
	(((x).end[0] << 8) | (x).end[1])

typedef struct
{
    MTP2HDR             hdr;
    U8                  filler[FILLER_COUNT];
    U8                  msgType;
    U8                  providerId[2];
    union
    {
        BindReq         bindReq;
        ConReq          conReq;
        DatReq          datReq;
        DisReq          disReq;
        FlowReq         flowReq;
        StaReq          staReq;
        StaRsp          staRsp;
    } data;
    U8 fill;
} MTP2TXPKT;

#define TXPKT_SET_PROVIDER_ID(x, v)				\
	((x).providerId[0] = ((v) >> 8) & 0xFFU,	\
	 (x).providerId[1] = (v) & 0xFFU)

typedef struct
{
    MTP2HDR             hdr;
    unsigned char       data[MAXMTP2RXDATA];
} MTP2RXPKT;

#define HDRSIZE             FILLER_COUNT + sizeof(MTP2HDR) + 3
#define ENDSIZE             FILLER_COUNT + 3


#define     SIO_MGMT_MSG    0x00
#define     SIO_TEST_MSG    0x01
#define     SLTM_PKT        0x11
#define     SLTA_PKT        0x21
#define     COO_PKT         0x11
#define     COA_PKT         0x21
#define     SLTM_LEN        3

typedef struct
    {
    U8      sio;
    U8      dpc[3];
    U8      opc[3];
    U8      sls;
    U8      sltype;
    U8      length;                     /* top 4 bits used */
    U8      pattern[15];
    } pktSLT;

typedef struct
    {
    U8      sio;
    U8      dpc[3];
    U8      opc[3];
    U8      sls;
    U8      sltype;
    U8      data[2];
    } pktCOO;

/* Link States */
#define     LINK_DOWN       0
#define     LINK_UP         1
#define     LINK_CHANGETO   2
#define     LINK_CHANGEFROM 3
#define     LINK_WAITCOA    4
#define     LINK_RCVDCOO    5
#define     LINK_GETUNACKED 6

#ifdef UNIX
#pragma pack()
#endif

#endif  /* _MTP2APP_H_ */
