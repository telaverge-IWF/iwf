/*****************************************************************************
******************************************************************************
**
**   tupred.h
**      TUP Redundancy definitions, structure definitions and variables,
 *      checkpointing structure definitions.
**
**   Revision History:
**
*-----------------------------------------------------------------------------
*/
/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                    By Natural MicroSystems, Inc.                     **
**                                                                      **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/

/* Definitions for High availability states */
#define TUP_ST_HAST_STARTING             0
#define TUP_ST_HAST_STANDALONE           1
#define TUP_ST_HAST_PRIMARY              2
#define TUP_ST_HAST_BACKUP               3

/* Definitions for mate connection states */
#define TUP_ST_MCST_ISOLATED             0
#define TUP_ST_MCST_CONNECTED            1

#define MAX_RESTORE_COUNT                128  /* Maximum circuits count for
                                               * backup restoring */

/* Turn on/off automatic checkpointing from primary to backup task */
#define TUP_CHKPT_NONE  0
#define TUP_CHKPT_AUTO  1

/*Structure definition to indicate high availability state and
 * mate connection state
 */
typedef struct _TuphamcState
{
    U8  haState;        /*High availability state*/
    U8  mcState;         /*Mate connection state*/
}TuphamcState;

/* Checkpoint indication and checkpoint request */

/* Structure definitions for checkpointing the circuit state and
 * the call state of a configured circuit from primary to backup
 * TUP task
 */

/* Header */
typedef struct _TUPChkptHdr
{
    Chain chain;
    U16 start;
    U16 end;
    U8  version;                         /* Version Number */
#define TUP_CHKPT_VERSION      1
    U8  protocol;                        /* Switch type  */
    U8  msgtype;
    U8  spare1;
} TUPChkptHdr;

/*Checkpointing Message Structure*/
typedef struct _TUPcheckPointMsg
{
    TUPChkptHdr stChkptHdr;
    U32         cirId;
    U32         opc;
    U32         dpc;
    U16         circuitState;
    U16         callState;
}TUPChkPntMsg;

/* circuitState values */
#define  IDLE_STATE                      0x201
#define  IDLE_LOC_BLK                    0x202
#define  IDLE_REM_BLK                    0x203
#define  IDLE_BOTH_BLK                   0x204
#define  BUSY_IN                         0x205
#define  BUSY_IN_LOC_BLK                 0x206
#define  BUSY_IN_REM_BLK                 0x207
#define  BUSY_IN_BOTH_BLK                0x208
#define  BUSY_OUT                        0x209
#define  BUSY_OUT_LOC_BLK                0x20a
#define  BUSY_OUT_REM_BLK                0x20b
#define  BUSY_OUT_BOTH_BLK               0x20c
#define  OOS_L                           0x20d
#define  OOS_L_LOC_BLK                   0x20e
#define  OOS_L_REM_BLK                   0x20f
#define  OOS_L_BOTH_BLK                  0x210
#define  OOS_R                           0x211
#define  OOS_R_LOC_BLK                   0x212
#define  OOS_R_REM_BLK                   0x213
#define  OOS_R_BOTH_BLK                  0x214
#define  OOS_B                           0x215
#define  OOS_B_LOC_BLK                   0x216
#define  OOS_B_REM_BLK                   0x217
#define  OOS_B_BOTH_BLK                  0x218

/* callState values for inbound and outbound circuits */
#define NOT_APPL                         0
/*If an inbound busy circuit */
#define WAIT_CNI_CLF                     0x301
#define WAIT_CNI_INFO                    0x302
#define WAIT_CNI_ANSWER                  0x303
#define WAIT_CNI_ACM                     0x304
#define WAIT_CNI_LOCAL_RLG               0x305
#define WAIT_CNI_COT                     0x306
#define WAIT_CNI_CCR                     0x307
#define WAIT_CNI_CONT_CLF                0x308
#define CNI_DEAD                         0x309
/* If an outgoing busy circuit */
#define WAIT_CNO_RLG                     0x401
#define WAIT_CNO_RELEASE                 0x402
#define WAIT_CNO_INFO                    0x403
#define WAIT_CNO_ANSWER                  0x404
#define WAIT_CNO_ACM                     0x405
#define WAIT_CNO_COT                     0x406
#define WAIT_CNO_CONT_CLF                0x407
#define WAIT_CNO_CCR                     0x408
#define CNO_DEAD                         0x409

/* Data Structure to checkpoint the circuit group messages from
 * primary to backup task.
 */

typedef struct _tupgrpelmtHdr            /* element header */
{
   Bool pres;                     /* present */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
} TupgrpElmtHdr;

typedef struct _TUPgrpRange
{
    TupgrpElmtHdr eh;
    U8      range;
    U8      spare2;
    U16     spare1;
    U8      statusMap[256];
} TUPgrpRange;

typedef struct _TUPcirGrpCheckPtMsg
{
    TUPChkptHdr   chkptHdr;
    U32           dpc;
    U16           cic;
    U32           circId;
    U16           groupId;
    U16           count;
    TUPgrpRange   range;
    U8            subGroupMachine;
    U8            subGroupState;
}TUPgrpCheckPtMsg;

/*Data Structures and definitions for restoring the state information of all
 * the configured circuits from primary, whenever HMI connected is received
 * on the backup side and in case of MTP backup event(mate connection
 * state is already in TUP_ST_MCST_CONNECTED.
 */
#define TUP_CHKPT_RESTORE_REQ           1
#define TUP_CHKPT_MORE_RESTOREDATA      2
#define TUP_CHKPT_RESTORE_CONTINUE      3
#define TUP_CHKPT_RESTORE_COMPLETE      4

typedef struct _TUPrestoreHdr
{
    Chain chain;
    U16 start;
    U16 end;
    U16  msgtype;
    U16  totalCircsInPacket;
    U32  lastCirNum;
}TUPrestoreHdr;

typedef struct _TUPrestoreCircState
{
    TUPrestoreHdr  stRestoreHdr;
    U32            cirId[MAX_RESTORE_COUNT];
    U16            circuitState[MAX_RESTORE_COUNT];
    U16            callState[MAX_RESTORE_COUNT];
}TUPrestoreBkupCircs;
