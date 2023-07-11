/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: sua.h,v 9.5 2008/07/17 14:06:29 ssingh Exp $
 *
 * LOG: $Log: sua.h,v $
 * LOG: Revision 9.5  2008/07/17 14:06:29  ssingh
 * LOG: Warning removal for Solaris Compilation
 * LOG:
 * LOG: Revision 9.4  2007/04/18 06:47:43  yranade
 * LOG: Fix errors compiling sua, in PRC and TTC builds.
 * LOG: Update Makefile to clean SUA libs.
 * LOG:
 * LOG: Revision 9.3  2007/01/17 09:20:30  yranade
 * LOG: Fix compilation errors.
 * LOG:
 * LOG: Revision 9.2  2005/08/03 15:47:17  randresol
 * LOG: Add some definitions for SUA RFC Implementation
 * LOG:
 * LOG: Revision 1.1.1.1.2.6  2005/05/26 20:21:15  cbascon
 * LOG: - added new message class definitions
 * LOG: - added SUA_MAX_SEQ_CTL_LEN so we don't use magic numbers
 * LOG: - added prototype for SUA_AddIE
 * LOG:
 * LOG: Revision 1.1.1.1.2.5  2005/05/13 14:56:02  cbascon
 * LOG: use the right bit masks for address indicator
 * LOG:
 * LOG: Revision 1.1.1.1.2.4  2005/05/10 23:24:12  cbascon
 * LOG: had wrong address indicator masks, added prototype for SUA_ParseAddress
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2005/05/10 21:22:04  cbascon
 * LOG: added prototype and short name definitions for SUA_ParseAddress
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2005/05/04 13:28:56  cbascon
 * LOG: - added macros for setting protocol class bits and return message on
 * LOG:   error bit
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2005/05/02 18:16:37  cbascon
 * LOG: - RFC3868 modifications
 * LOG:
 * LOG: Revision 1.1.1.1  2005/04/25 14:00:33  cbascon
 * LOG: Imported sources
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.2  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/14 13:44:52  snagesh
 * LOG: Modifications for Chinese variant
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/07/03 19:54:44  mmiers
 * LOG: China fixes
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:25:07  lbana
 * LOG: commit sua.h from PR5
 * LOG:
 * LOG: Revision 4.3.2.10  2002/04/15 16:47:31  ngoel
 * LOG: change reg res length to 24
 * LOG:
 * LOG: Revision 4.3.2.9  2002/04/15 13:58:11  ngoel
 * LOG: define common parameter local rkid
 * LOG:
 * LOG: Revision 4.3.2.8  2002/04/03 14:28:53  ngoel
 * LOG: make sua desc common for ANSI and CCITT
 * LOG:
 * LOG: Revision 4.3.2.7  2002/03/14 20:37:26  ngoel
 * LOG: add transport manager in function definition
 * LOG:
 * LOG: Revision 4.3.2.6  2002/03/11 21:54:05  ngoel
 * LOG: add transport manager to codec definition
 * LOG:
 * LOG: Revision 4.3.2.5  2002/02/25 15:30:57  ngoel
 * LOG: move to sua draft 12
 * LOG:
 * LOG: Revision 4.3.2.4  2002/02/22 19:05:45  ngoel
 * LOG: add asp label parameter
 * LOG:
 * LOG: Revision 4.3.2.3  2002/02/21 16:20:38  ngoel
 * LOG: get interworking mode in class initialize
 * LOG:
 * LOG: Revision 4.3.2.2  2002/02/21 15:17:43  ngoel
 * LOG: some additions
 * LOG:
 * LOG: Revision 4.3.2.1  2002/02/11 22:20:37  ngoel
 * LOG: move to sua v11
 * LOG:
 * LOG: Revision 4.3  2001/07/26 14:49:58  labuser
 * LOG: commit SUA v5 to current.
 * LOG:
 * LOG: Revision 1.13.2.1  2001/06/22 20:24:48  labuser
 * LOG: SUA Draft V5 Codec.
 * LOG:

 *                 
 ****************************************************************************/

#ifndef SUA_H
#define SUA_H

#include <its.h>
#include <its_object.h>
#include <its_sctp_trans.h>

#if defined(ANSI)

#if defined(USE_ITU_SCCP)

#undef ANSI
#define CCITT 1

#include <itu/sccp.h>

#undef CCITT
#define ANSI 1

#else /* USE_ITU_SCCP */

#include <ansi/sccp.h>

#endif /* USE_ITU_SCCP */

#elif defined(CCITT)

#if defined(USE_ANSI_SCCP)

#undef CCITT
#define ANSI 1

#include <ansi/sccp.h>

#undef ANSI
#define CCITT 1

#else /* USE_ANSI_SCCP */

#include <itu/sccp.h>

#endif /* USE_ANSI_SCCP */

#elif defined(PRC)

#include <china/sccp.h>

#elif defined(TTC)

#include <japan/sccp.h>

#else
#error "Protocol family not defined."
#endif

#if defined(WIN32)

#if defined(SUA_IMPLEMENTATION)
#define SUADLLAPI __declspec(dllexport)
#else
#define SUADLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define SUADLLAPI

#endif /* WIN32 */

#if defined(__cplusplus)
extern "C"
{
#endif

#define SUA_EBADMSG                   -73
#define SUA_EWRG_SUA_PARAM            -74
#define SUA_INTERWORK_MODE_STRING      "interworkingMode"
#define SUA_SG_MODE_STRING             "sgMode"
#define SUA_ITW_SG                     0x01U
#define SUA_ITW_ASP                    0x02U




/* SUA protocol version */
#define SUA_PROT_VER1                 0x01

/* message class */
#define SUA_CL_MGMT_MSG               0x00
#define SUA_CL_SSNM_MSG               0x02
#define SUA_CL_ASP_STATE_MAINT_MSG    0x03
#define SUA_CL_ASP_TRAF_MAINT_MSG     0x04
#define SUA_CL_CL_MSG                 0x07
#define SUA_CL_CO_MSG                 0x08
#define SUA_RKEY_MGMT_MSG             0x09
/**************************************************/
/* cbascon: this would be a nicer replacement for the definitions above */
#define SUA_CL_MGMT                   0x00
#define SUA_CL_SNM                    0x02
#define SUA_CL_ASPSM                  0x03
#define SUA_CL_ASPTM                  0x04
#define SUA_CL_CL                     0x07
#define SUA_CL_CO                     0x08
#define SUA_CL_RKM                    0x09
/**************************************************/

/* SUA Management (MGMT) Messages */
#define SUA_MSG_ERR                   0x00
#define SUA_MSG_NOTIFY                0x01

/* Application Server Process State Maintenance messages (ASPSM) */
#define SUA_MSG_ASPUP                 0x01
#define SUA_MSG_ASPDN                 0x02
#define SUA_MSG_BEAT                  0x03
#define SUA_MSG_ASPUP_ACK             0x04
#define SUA_MSG_ASPDN_ACK             0x05
#define SUA_MSG_BEAT_ACK              0x06

/* Application Server Process Traffic Maintenance (ASPTM) */
#define SUA_MSG_ASPAC                 0x01
#define SUA_MSG_ASPIA                 0x02
#define SUA_MSG_ASPAC_ACK             0x03
#define SUA_MSG_ASPIA_ACK             0x04

/* Signaling network management messages (SSNM) */
#define SUA_MSG_DUNA                  0x01
#define SUA_MSG_DAVA                  0x02
#define SUA_MSG_DAUD                  0x03
#define SUA_MSG_SCON                  0x04
#define SUA_MSG_DUPU                  0x05
#define SUA_MSG_DRST                  0x06
/*#define SUA_MSG_SCMG                  0x06 removed in draft 9 */

/* Routing KeyManagement Messages */
#define SUA_REG_REQ                  0x01
#define SUA_REG_RSP                  0x02
#define SUA_DEREG_REQ                0x03
#define SUA_DEREG_RSP                0x04

/* SUA Connectionless messages */
#define SUA_MSG_CLDT                  0x01
#define SUA_MSG_CLDR                  0x02

/* SUA Connection Oriented messages */
#define SUA_MSG_CORE                  0x01
#define SUA_MSG_COAK                  0x02
#define SUA_MSG_COREF                 0x03
#define SUA_MSG_RELRE                 0x04
#define SUA_MSG_RELCO                 0x05
#define SUA_MSG_RESCO                 0x06
#define SUA_MSG_RESRE                 0x07
#define SUA_MSG_CODT                  0x08
#define SUA_MSG_CODA                  0x09
#define SUA_MSG_COERR                 0x0A
#define SUA_MSG_COIT                  0x0B


/* SUA common message Header */
typedef struct
{
    ITS_OCTET   version;
    ITS_OCTET   reserved;
    ITS_OCTET   msgClass;
    ITS_OCTET   msgType;
    ITS_UINT    msgLen;  /* msg data + sizeof(SUA_MSG_HDR) */   
}
SUA_MSG_HDR;


/* SUA Common Parameters */
#define SUA_PRM_MSG_HDR                0x0000    /* used by IntelliSS7 */
#define SUA_PRM_INFO_STR               0x0004
#define SUA_PRM_ROUT_CTX               0x0006
#define SUA_PRM_DIAG_INFO              0x0007
#define SUA_PRM_HEARTBEAT_DATA         0x0009
#define SUA_PRM_TRAFFIC_MODE           0x000B
#define SUA_PRM_ERROR_CODE             0x000C
#define SUA_PRM_STATUS                 0x000D /* RFC3868: renamed from SUA_PRM_STATUS_TYPE_ID */
#define SUA_PRM_ASP_ID                 0x0011
#define SUA_PRM_AFFECTED_PC            0x0012
#define SUA_PRM_COR_ID                 0x0013
#define SUA_PRM_REG_RES                0x0014
#define SUA_PRM_DEREG_RES              0x0015
#define SUA_PRM_REG_STATUS             0x0016
#define SUA_PRM_DEREG_STATUS           0x0017
#define SUA_PRM_LOCAL_RKID             0x0018

/* SUA Specific Parameters */
#define SUA_PRM_HOP_CNT                0x0101  /* SS7 Hop Counter */
#define SUA_PRM_SRC_ADDR               0x0102
#define SUA_PRM_DST_ADDR               0x0103
#define SUA_PRM_SRC_REF_NUM            0x0104
#define SUA_PRM_DST_REF_NUM            0x0105
#define SUA_PRM_SCCP_CAUSE             0x0106
#define SUA_PRM_SEQ_NUM                0x0107  /* SCCP seq/segment 3.9*/
#define SUA_PRM_REC_SEQ_NUM            0x0108  /* SCCP rec seq num 3.8*/
#define SUA_PRM_ASP_CAPAB              0x0109
#define SUA_PRM_CREDIT                 0x010A
#define SUA_PRM_DATA                   0x010B
#define SUA_PRM_CAUSE_USER             0x010C 
#define SUA_PRM_NET_APP                0x010D
#define SUA_PRM_RKEY                   0x010E
#define SUA_PRM_DRN_LABEL              0x010F
#define SUA_PRM_TID_LABEL              0x0110
#define SUA_PRM_ADDR_RANG              0x0111
#define SUA_PRM_SMI                    0x0112
#define SUA_PRM_IMPORTANCE             0x0113
#define SUA_PRM_MSG_PRIOR              0x0114
#define SUA_PRM_PROT_CLASS             0x0115
#define SUA_PRM_SEQ_CTL                0x0116
#define SUA_PRM_SEGMENTATION           0x0117
#define SUA_PRM_CONG_LEVEL             0x0118

/* SUA Destination/Source Address Subparameters */
#define SUA_SPRM_GT                    0x8001
#define SUA_SPRM_PC                    0x8002
#define SUA_SPRM_SSN                   0x8003
#define SUA_SPRM_IPV4_ADDR             0x8004
#define SUA_SPRM_HOSTNAME              0x8005
#define SUA_SPRM_IPV6_ADDR             0x8006



/*
 * Base Structures
 */
typedef struct
{
    ITS_USHORT param_id;
    ITS_USHORT param_len;
    ITS_UINT   param_data;
}
ITS_SUA_UINT_IE;

/* 
 * --------- Common UAL Messages --------
 */

/* 
 * Network apperance 
 */

typedef struct
{
    ITS_UINT    networkApp;
}
SUA_NET_APP;

/* 
 * Data parameter 
 */

#define SUA_MAX_DATA_SIZE   (254) 

typedef struct
{
    ITS_OCTET    data[SUA_MAX_DATA_SIZE]; 
}
SUA_DATA;


/*
 * Info String 
 */

#define SUA_MAX_INFO_STR_LEN   255 

typedef struct
{
    ITS_OCTET    infoStr[SUA_MAX_INFO_STR_LEN];
}
SUA_INFO_STR;


/* 
 * Affected PC 
 */
typedef struct
{
    ITS_OCTET           mask;
    ITS_OCTET           pc[3];
}
SUA_AFFECTED_DEST;


/* 
 * Routing Context Parameter
 */

#define SUA_MAX_ROUT_CTX_LEN    4 
#define SUA_MAX_RK_NUM          15

typedef struct 
{
	union
	{
            ITS_OCTET    routCtx[SUA_MAX_ROUT_CTX_LEN];
            ITS_UINT     _routCtx;
	}u;
}
SUA_ROUT_CTX;


/*
 * Routing Key
 */

#define SUA_MAX_ROUT_KEY_LEN        4

typedef struct
{
    ITS_OCTET    routKey[SUA_MAX_ROUT_KEY_LEN];
}
SUA_ROUT_KEY;


/*
 * DRN Label Parameter
 */
#define SUA_MAX_DRN_LABEL_LEN       4

typedef struct
{
    ITS_OCTET label[SUA_MAX_DRN_LABEL_LEN];
}
SUA_DRN_LABEL;


/*
 * TID Label Parameter
 */
#define SUA_MAX_TID_LABEL_LEN       4

typedef struct
{
    ITS_OCTET label[SUA_MAX_TID_LABEL_LEN];
}
SUA_TID_LABEL;


/*
 * Diagnostic Information Parameter
 *
 * RFC3868:
 * - parameter len can be the first 40 bytes of the offending msg
 *   or the offending parameter which can be more than 40 bytes
 *   in length
 */

#define SUA_MAX_DIAG_INFO_LEN   255

typedef struct
{
    ITS_OCTET   diagnosticInfo[SUA_MAX_DIAG_INFO_LEN];
}
SUA_DIAG_INFO;


/*
 * HeartBeat Data
 */

#define SUA_MAX_HB_DATA_LEN 254

typedef struct
{
    ITS_OCTET   HBData[SUA_MAX_HB_DATA_LEN];
}
SUA_HB_DATA;


/*
 * Cause-User
 */

typedef struct
{
    ITS_USHORT   cause;
    ITS_USHORT   user;
}
SUA_CAUSE_USER;

/* cause */
#define SUA_UNKNOWN_CAUSE           0x00
#define SUA_UNEQUIP_REMOTE_USR      0x01
#define SUA_INACCESS_REMOTE_USR     0x02

/* User Id */
#define SUA_USER_SCCP               0x03



/*
 * Reason
 */

typedef struct
{
    ITS_UINT    reason;
}
SUA_REASON;

#define SUA_UNSPEC_REASON        0x00
#define SUA_USR_UNAV_REASON      0x01
#define SUA_MGMT_BLOCK_REASON    0x02
#define SUA_ASP_FAULT            0x03


/* 
 * Traffic Mode Type
 *
 * RFC3868:
 * - Only has 3 valid Traffic Mode Types
 */

typedef struct
{
    ITS_UINT    tm;
}
SUA_TRAFFIC_MODE;

#define SUA_OVERRIDE_MODE        0x01
#define SUA_LOADSHARE_MODE       0x02
#define SUA_BROADCAST_MODE       0x03

/*
#define SUA_OVERRIDE_SB_MODE     0x03
#define SUA_LOADSHARE_SB_MODE    0x04
*/

/*
 * Error Code
 *
 * RFC3868:
 * - modified list of error codes
 */

typedef struct
{
    ITS_UINT    errCode;
}
SUA_ERR_CODE;

#define SUA_ERR_INV_VER             0x01
/* Not Used in SUA 0x02 */
#define SUA_ERR_INV_MSG_CLASS       0x03
#define SUA_ERR_INV_MSG_TYP         0x04
#define SUA_ERR_INV_THM             0x05
#define SUA_ERR_UNEXP_MSG           0x06
#define SUA_ERR_PROT_ERR            0x07
/* Not Used in SUA 0x08 */
#define SUA_ERR_INV_STREAM_ID       0x09
/* Not Used in SUA 0x0a */
/* Not Used in SUA 0x0b */
/* Not Used in SUA 0x0c */
#define SUA_ERR_REF_MGMTBLOCK       0x0d
#define SUA_ERR_ASPID_REQ           0x0e
#define SUA_ERR_INV_ASPID           0x0f
/* Not Used in SUA 0x10 */
#define SUA_ERR_INV_PARAM_VAL       0x11
#define SUA_ERR_PARAM_FIELD         0x12
#define SUA_ERR_UNEXP_PARAM         0x13
#define SUA_ERR_DEST_STAT_UNKNOWN   0x14
#define SUA_ERR_INV_NET_APP         0x15
#define SUA_ERR_MISSING_PARAM       0x16
/* Not Used in SUA 0x17 */
/* Not Used in SUA 0x18 */
#define SUA_ERR_INV_ROUT_CTX        0x19
#define SUA_ERR_NO_CFG_AS           0x1a
#define SUA_ERR_SUBSYS_STAT_UNKNOWN 0x1b
#define SUA_ERR_INV_LOADSHARE_LABEL 0x1c


/*
 * Status Type
 *
 * RFC3868:
 * - added Status ID value ASP Failure
 * - renamed SUA_ALT_ASP_ACTIVE to SUA_ST_ID_ALT_ASP_ACTIVE
 */

typedef struct
{
    ITS_USHORT  type;
    ITS_USHORT  id;
}
SUA_STATUS_TYPE;

/* Status Type */
#define SUA_ST_TYPE_AS_STAT_CHG        0x01
#define SUA_ST_TYPE_OTHER              0x02

/* Status ID when Status Type is AS_STATE_CHANGE */
#define SUA_ST_ID_AS_INACTIVE          0x02
#define SUA_ST_ID_AS_ACTIVE            0x03
#define SUA_ST_ID_AS_PENDING           0x04

/* Status ID when Status Type is Other */
#define SUA_ST_ID_INSUF_ASP_RSRC       0x01
#define SUA_ST_ID_ALT_ASP_ACTIVE       0x02
#define SUA_ST_ID_ASP_FAILURE          0x03


/*
 * ASP Identifier Parameter
 */
typedef struct
{
    ITS_UINT    id;
}
SUA_ASP_ID;


/*
 * Congestion Level Parameter
 */
typedef struct
{
    ITS_UINT    level;
}
SUA_CONG_LEVEL;

#define SUA_NO_CONG                    0x00
#define SUA_CONG_LEVEL_1               0x01
#define SUA_CONG_LEVEL_2               0x02
#define SUA_CONG_LEVEL_3               0x03




/* 
 * --------- SUA Specific Messages --------
 */

/*
 * Protocol Class Parameter (3.6 Q.713)
 */
typedef struct
{
    ITS_UINT value;
}
SUA_PROT_CLASS;

#define SUA_PC_CLASS_MASK                     0x7FU
#define SUA_PC_RETURN_MSG_ON_ERR_MASK         0x80U

#define SUA_PC_SET_CLASS(pc,cl) \
    pc.value = (pc.value & SUA_PC_RETURN_MSG_ON_ERR_MASK) | \
        (cl & SUA_PC_CLASS_MASK);

#define SUA_PC_GET_CLASS(pc) \
    pc.value = pc.value & SUA_PC_CLASS_MASK;

#define SUA_PC_SET_RETURN_MSG_ON_ERR(pc,er) \
    pc.value = (pc.value & SUA_PC_CLASS_MASK) | \
        (er & SUA_PC_RETURN_MSG_ON_ERR_MASK);

#define SUA_PC_GET_RETURN_MSG_ON_ERR(pc) \
    pc.value = pc.value & SUA_PC_RETURN_MSG_ON_ERR_MASK;

/*
 * Importance Parameter
 */
typedef struct
{
    ITS_UINT value;
}
SUA_IMPORTANCE;

/*
 * SS7 Hop Counter
 */
#define SUA_MAX_SS7_HOP_COUNT       15

typedef struct
{
    ITS_UINT value;
}
SUA_HOP_COUNT;

#define SUA_IS_SS7HOPCOUNT_VALID(hc) \
    ((hc.value > 0) && (hc.value <= SUA_MAX_SS7_HOP_COUNT)) ? 1 : 0

/*
 * Sequence Control Parameter
 */
#define SUA_MAX_SEQ_CTL_LEN        4

typedef struct
{
    ITS_UINT value;
}
SUA_SEQ_CTL;

/*
 * Reference Number
 */
typedef struct
{
    ITS_UINT   refNum;
}
SUA_REF_NUM;

/*
 * Segmentation Parameter
 */
typedef struct
{
    ITS_OCTET firstRemain;
    ITS_OCTET segRef[3];
}
SUA_SEGMENTATION;

/*
 * Message Priority Parameter
 */
typedef struct
{
    ITS_OCTET reserved[3];
    ITS_OCTET msgPrior;
}
SUA_MSG_PRIOR;

/*
 * Correlation ID parameter
 */
typedef struct
{
    ITS_UINT corId;
}
SUA_COR_ID;


/*
 * Registration Result Parameter
 */

#define SUA_MAX_REG_RES_LEN                 24
#define SUA_REG_RES_RKID_INDEX              0
#define SUA_REG_RES_STATUS_INDEX            8
#define SUA_REG_RES_ROUTCTX_INDEX           16

typedef struct
{
    union
    {
        ITS_OCTET       result[SUA_MAX_REG_RES_LEN];

        struct
        {
            ITS_SUA_UINT_IE routKeyID;
            ITS_SUA_UINT_IE regStat;
            ITS_SUA_UINT_IE routCtx;
        }ctx;
    }u;
}
SUA_REG_RESULT;

#define SUA_SET_REGRES_RKID(rr, rkid) \
    rr.routKeyID.param_id = SUA_PRM_LOCAL_RKID; \
    rr.routKeyID.param_len = 8; \
    rr.routKeyID.param_data = rkid;

#define SUA_SET_REGRES_STATUS(rr, st) \
    rr.regStat.param_id = SUA_PRM_REG_STATUS; \
    rr.regStat.param_len = 8; \
    rr.regStat.param_data = st;

#define SUA_SET_REGRES_ROUTCTX(rr, rctx) \
    rr.routCtx.param_id = SUA_PRM_ROUT_CTX; \
    rr.routCtx.param_len = 8; \
    rr.routCtx.param_data = st;

#define SUA_GET_REGRES_RKID_IE(rr, ie) \
    ie->param_id = (rr.result[SUA_REG_RES_RKID_INDEX] << 8) | \
                    rr.result[SUA_REG_RES_RKID_INDEX+1]; \
    ie->param_length = (rr.result[SUA_REG_RES_RKID_INDEX+2] << 8) | \
                        rr.result[SUA_REG_RES_RKID_INDEX+3]; \
    ie->param_data.localRKID.id[0] = rr.result[SUA_REG_RES_RKID_INDEX+4]; \
    ie->param_data.localRKID.id[1] = rr.result[SUA_REG_RES_RKID_INDEX+5]; \
    ie->param_data.localRKID.id[2] = rr.result[SUA_REG_RES_RKID_INDEX+6]; \
    ie->param_data.localRKID.id[3] = rr.result[SUA_REG_RES_RKID_INDEX+7];

#define SUA_GET_REGRES_STATUS_IE(rr, ie) \
    ie->param_id = (rr.result[SUA_REG_RES_STATUS_INDEX] << 8) | \
                    rr.result[SUA_REG_RES_STATUS_INDEX+1]; \
    ie->param_length = (rr.result[SUA_REG_RES_STATUS_INDEX+2] << 8) | \
                        rr.result[SUA_REG_RES_STATUS_INDEX+3]; \
    ie->param_data.regStat.status = \
        ((rr.result[SUA_REG_RES_STATUS_INDEX+4] & 0xFF) << 24) | \
        ((rr.result[SUA_REG_RES_STATUS_INDEX+5] & 0xFF) << 16) | \
        ((rr.result[SUA_REG_RES_STATUS_INDEX+6] & 0xFF) << 8) | \
        (rr.result[SUA_REG_RES_STATUS_INDEX+7] & 0xFF);

#define SUA_GET_REGRES_ROUTCTX_IE(rr, ie) \
    ie->param_id = (rr.result[SUA_REG_RES_ROUTCTX_INDEX] << 8) | \
                    rr.result[SUA_REG_RES_ROUTCTX_INDEX+1]; \
    ie->param_length = (rr.result[SUA_REG_RES_ROUTCTX_INDEX+2] << 8) | \
                        rr.result[SUA_REG_RES_ROUTCTX_INDEX+3]; \
    ie->param_data.routCtx.routCtx[0] = \
        rr.result[SUA_REG_RES_ROUTCTX_INDEX+4]; \
    ie->param_data.routCtx.routCtx[1] = \
        rr.result[SUA_REG_RES_ROUTCTX_INDEX+5]; \
    ie->param_data.routCtx.routCtx[2] = \
        rr.result[SUA_REG_RES_ROUTCTX_INDEX+6]; \
    ie->param_data.routCtx.routCtx[3] = \
        rr.result[SUA_REG_RES_ROUTCTX_INDEX+7];

/*
 * Deregistration Result Parameter
 */

#define SUA_MAX_DEREG_RES_LEN           16
#define SUA_DEREG_RES_ROUT_CTX_INDEX    0
#define SUA_DEREG_RES_STATUS_INDEX      8

typedef struct
{
    union
    {
        ITS_OCTET result[SUA_MAX_DEREG_RES_LEN];

        struct
        {
            ITS_SUA_UINT_IE  routCtx;
            ITS_SUA_UINT_IE  deregStat;
        }ctx;
    }u;
}
SUA_DEREG_RESULT;

#define SUA_SET_DEREGRES_ROUTCTX(dr, rctx) \
    dr.routCtx.param_id = SUA_PRM_ROUT_CTX; \
    dr.routCtx.param_len = 8; \
    dr.routCtx.param_data = rctx;

#define SUA_SET_DEREGRES_STATUS(dr, st) \
    dr.deregStat.param_id = SUA_PRM_DEREG_STATUS; \
    dr.deregStat.param_len = 8; \
    dr.deregStat.param_data = st;

#define SUA_GET_DEREGRES_ROUTCTX_IE(dr, ie) \
    ie->param_id = (dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX] << 8) | \
                    dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+1]; \
    ie->param_length = (dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+2] << 8) | \
                        dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+3]; \
    ie->param_data.routCtx.routCtx[0] = \
        dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+4]; \
    ie->param_data.routCtx.routCtx[1] = \
        dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+5]; \
    ie->param_data.routCtx.routCtx[2] = \
        dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+6]; \
    ie->param_data.routCtx.routCtx[3] = \
        dr.result[SUA_DEREG_RES_ROUT_CTX_INDEX+7];

#define SUA_GET_DEREGRES_STATUS_IE(dr, ie) \
    ie->param_id = (dr.result[SUA_DEREG_RES_STATUS_INDEX] << 8) | \
                    dr.result[SUA_DEREG_RES_STATUS_INDEX+1]; \
    ie->param_length = (dr.result[SUA_DEREG_RES_STATUS_INDEX+2] << 8) | \
                        dr.result[SUA_DEREG_RES_STATUS_INDEX+3]; \
    ie->param_data.deregStat.status[0] = \
        dr.result[SUA_DEREG_RES_STATUS_INDEX+4]; \
    ie->param_data.deregStat.status[1] = \
        dr.result[SUA_DEREG_RES_STATUS_INDEX+5]; \
    ie->param_data.deregStat.status[2] = \
        dr.result[SUA_DEREG_RES_STATUS_INDEX+6]; \
    ie->param_data.deregStat.status[3] = \
        dr.result[SUA_DEREG_RES_STATUS_INDEX+7];

/*
 * Registration Status Parameter
 *
 * RFC3868:
 * - added SUA_REG_STAT_ERR_RK_CHG_REF
 */

typedef struct
{
    ITS_UINT   status;
}
SUA_REG_STATUS;

#define SUA_REG_STAT_SUCCESS                0x00
#define SUA_REG_STAT_ERR_UNKNOWN            0x01
#define SUA_REG_STAT_ERR_INV_DPC            0x02
#define SUA_REG_STAT_ERR_INV_NA             0x03
#define SUA_REG_STAT_ERR_INV_RK             0x04
#define SUA_REG_STAT_ERR_PERM_DNY           0x05
#define SUA_REG_STAT_ERR_NO_SUP_UNI_RK      0x06
#define SUA_REG_STAT_ERR_RK_NOT_PROV        0x07
#define SUA_REG_STAT_ERR_INSUFF_RES         0x08
#define SUA_REG_STAT_ERR_NO_SUP_RK_FLD      0x09
#define SUA_REG_STAT_ERR_INVALID_THM        0x0A
#define SUA_REG_STAT_ERR_RK_CHG_REF         0x0B

/*
 * Deregistration Status Parameter
 */
typedef struct
{
    ITS_UINT    status;
}
SUA_DEREG_STATUS;

#define SUA_DEREG_STAT_SUCCESS              0x00
#define SUA_DEREG_STAT_ERR_UNKNOWN          0x01
#define SUA_DEREG_STAT_ERR_INV_ROUTCTX      0x02
#define SUA_DEREG_STAT_ERR_PERM_DENY        0x03
#define SUA_DEREG_STAT_ERR_NOT_REG          0x04
#define SUA_DEREG_STAT_ERR_ASP_ACT_FOR_RCTX 0x05

/*
 * Local Routing Key Identifier Parameter
 */
typedef struct
{
    ITS_UINT  id;
}
SUA_LOCAL_RKID;


/* bit 1-2 of the protocol class */
#define SUA_PROT_CLASS_0               0x00    /* connectionless service */
#define SUA_PROT_CLASS_1               0x01    /* connectionless service */
#define SUA_PROT_CLASS_2               0x02    /* connection-oriented service */
#define SUA_PROT_CLASS_3               0x03    /* connection-oriented service */

/* bit 8 of the protocol class */
#define SUA_NO_RET_OPTION              0x00
#define SUA_RET_ON_ERR_OPT             0x01    

/*
 * Max size of Address parameters when routing is done by Hostname
 * should be 267 octets:
 *     Hostname len = 259 octets
 *                  = max 255 octets(RFC1123) + 4 octets (param tag & len)
 *     SSN len = 8 octets
 *
 * NOTE: Just setting it to 82 for now since it is unlikely for hostnames to
 *       reach 255 characters in the real world.
 */
#define SUA_MAX_ADDR_DATA              82

typedef struct
{
    ITS_USHORT len;   /* the len include the 2 indic + Data with padding */
    ITS_OCTET routIndic[2];
    ITS_OCTET addrIndic[2];
    ITS_OCTET addrData[SUA_MAX_ADDR_DATA];
}
SUA_ADDRS;

/*
 * Address Range Parameter
 * - Can only have pairs of Source Addresses and pairs of Destination
 *   Addresses
 */
#define SUA_MAX_ADDRS_RANGE_DATA       256

typedef struct
{
    ITS_OCTET data[SUA_MAX_ADDR_DATA];
}
SUA_ADDRS_RANGE;

/* SUA address indicator masks (RFC3868 3.10.2.2) */
#define SUA_CPA_HAS_SSN_MASK                   0x01
#define SUA_CPA_HAS_PC_MASK                    0x02
#define SUA_CPA_HAS_GT_MASK                    0x04

/* SUA routing indicator */
#define SUA_CPA_ROUTE_RESERVED                 0x00
#define SUA_CPA_ROUTE_ON_GT                    0x01
#define SUA_CPA_ROUTE_ON_SSN                   0x02
#define SUA_CPA_ROUTE_ON_HOSTNAME              0x03
#define SUA_CPA_ROUTE_ON_SSN_IP                0x04

#define SUA_GT_NUM_PLAN_MASK                   0x0F
#define SUA_GT_ODD_EVEN_MASK                   0x80

typedef struct
{
    ITS_OCTET           mask;
    ITS_OCTET           pc[3];
}
SUA_PC;

#if defined CCITT
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0x3FU))) 

#define SUA_PC_GET_VALUE(x)                               \
    ((((x).pc[1] & 0x3FU) << 8) | ((x).pc[2]))

#elif defined ANSI
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),       \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))

#define SUA_PC_GET_VALUE(x)                               \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[0] << 16))

#elif defined PRC
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)),       \
     ((x).pc[0] = (ITS_OCTET)(((v) >> 16) & 0xFFU)))


#define SUA_PC_GET_VALUE(x)                               \
    ((x).pc[2] | ((x).pc[1] << 8) | ((x).pc[0] << 16))

#elif defined TTC
/*
 * point code as value
 */
#define SUA_PC_SET_VALUE(x,v)                             \
    (((x).pc[2] = (ITS_OCTET)((v) & 0xFFU)),              \
     ((x).pc[1] = (ITS_OCTET)(((v) >> 8) & 0xFFU)))

#define SUA_PC_GET_VALUE(x)                               \
    ((((x).pc[1] & 0xFFU) << 8) | ((x).pc[2]))

#endif

typedef struct
{
    ITS_UINT ssn;
}
SUA_SSN;

/*
 * Gloabl Title Sub-Parameter
 */

#define SUA_MAX_GT_LEN                  255
#define SUA_GT_INDIC_MASK               0x00FF

typedef struct
{
    ITS_UINT  gti;          /* LSB only, other bits are reserved */
    ITS_OCTET numOfDgts;
    ITS_OCTET transType;
    ITS_OCTET numPlan;
    ITS_OCTET natOfAddr;
    ITS_OCTET data[SUA_MAX_GT_LEN];
}
SUA_GT;

#define SUA_SET_GT_INDICATOR(gt,i) \
    gt.gti = (i & SUA_GT_INDIC_MASK)

/*
 * IP Address Sub-Parameter
 */
#define SUA_IP_ADDR_LEN                 32

typedef struct
{
    ITS_OCTET IPAddrs[SUA_IP_ADDR_LEN];
}
SUA_IP_ADDRS;

#define SUA_MAX_HOSTNAME_LEN            32

typedef struct
{
    ITS_USHORT len;
    ITS_OCTET hostName[SUA_MAX_HOSTNAME_LEN];
}
SUA_HOSTNAME;


/* 
 * reference number 
 */


/* 
 * SCCP Cause
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET causeType;
    ITS_OCTET causeValue;
}
SUA_SCCP_CAUSE;

#define SUA_CAUSE_TYPE_RETURN           0x01
#define SUA_CAUSE_TPYE_REFUSAL          0x02
#define SUA_CAUSE_TYPE_RELEASE          0x03
#define SUA_CAUSE_TYPE_RESET            0x04
#define SUA_CAUSE_TYPE_ERROR            0x05

/* 
 * SCCP cause values are given in the SCCP specs
 * refer to that document for more information
 */

/* 
 * Sequence Number 
 */

/* 
 * this parameter is used to indicate whether more data will follow
 * in the subsequent CODT messages, and to number each CODT message 
 * sequentially for the purpose of flow control. contain the "More"
 * indicator and the P(R) and P(S) in Q713
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET recSeqNum;
    ITS_OCTET sentSenqNum;
}
SUA_SEQ_NUM;

#define SUA_SNUM_MORE_DATA_MASK        0x01


/* 
 * Receive Sequence Number 
 */

/* 
 * This parameter is used only for Protocol class 3 messages
 * It indicates the lower edge of the receiving window 
 */

typedef struct
{
    ITS_OCTET spare[3];
    ITS_OCTET recSeqNum;
}
SUA_REC_SEQ_NUM;

/*
 *   ASP Label 
 */
typedef struct
{
    ITS_OCTET start;
    ITS_OCTET end;
    ITS_OCTET lvalue[2];
}SUA_ASP_LABEL;


/* 
 * ASP Capabilities 
 */

typedef struct
{
    ITS_USHORT spare;
    ITS_OCTET protClass;
    ITS_OCTET interWork;
}
SUA_ASP_CAPAB;

/*interworking types */
#define SUA_INTERWORK_NOSS7     0x00U
#define SUA_INTERWORK_SS7       0x01U
#define SUA_INTERWORK_SG        0x02U
#define SUA_INTERWORK_RELAY     0x03U

/* Protocol Class Flag */
#define SUA_PROT_CLASS0_FLAG    0x01U
#define SUA_PROT_CLASS1_FLAG    0x02U
#define SUA_PROT_CLASS2_FLAG    0x04U
#define SUA_PROT_CLASS3_FLAG    0x08U
#define SUA_PROT_CLASS_MASK     0x0FU

/*
 * x - pointer to a SUA_ASP_CAPAB struct
 * y - Protocol class flag
 */
#define SUA_SET_ASP_CAP_PROTCLASS(x,y) \
    x->protClass = y & SUA_PROT_CLASS_MASK

/* 
 * Credit 
 */

typedef struct
{
    ITS_OCTET reserved[3];
    ITS_OCTET credit;
}
SUA_CREDIT;


/* 
 * SCMG Format Identifier 
 */

typedef struct
{
    ITS_UINT formatId;
}
SUA_SCMG_FORM;

#define SUA_SCMG_FORMAT_SSA         0x01
#define SUA_SCMG_FORMAT_SSP         0x02
#define SUA_SCMG_FORMAT_SST         0x03
#define SUA_SCMG_FORMAT_SOR         0x04
#define SUA_SCMG_FORMAT_SOG         0x05
#define SUA_SCMG_FORMAT_SSC         0x06
#define SUA_SCMG_FORMAT_SNR         0xFD
#define SUA_SCMG_FORMAT_SBR         0xFE
#define SUA_SCMG_FORMAT_SRT         0xFF


/* 
 * SMI 
 */

typedef struct
{
    ITS_UINT smi;
}
SUA_SMI;

#define SUA_SMI_REPLICATED          0x01
#define SUA_SMI_SOLITARY            0x02
#define SUA_SMI_UNKNOWN             0x03



/*
 * SUA IES
 */
typedef struct
{
    ITS_USHORT   param_id;      
    ITS_USHORT   param_length;
    union
    {
        /* Common Parameters */
        SUA_INFO_STR        infoStr;
        SUA_ROUT_CTX        routeCtx;
        SUA_DIAG_INFO       diagnostic;
        SUA_HB_DATA         hbData;
        SUA_TRAFFIC_MODE    trafMd;
        SUA_ERR_CODE        errorCode;
        SUA_STATUS_TYPE     statusType;
        SUA_ASP_ID          aspId;
        SUA_AFFECTED_DEST   affectedPC;
        SUA_COR_ID          corId;
        SUA_REG_RESULT      regRes;
        SUA_DEREG_RESULT    deregRes;
        SUA_REG_STATUS      regStat;
        SUA_DEREG_STATUS    deregStat;
        SUA_LOCAL_RKID      localRKID;
        
        /* SUA-Specific Parameters */
        SUA_HOP_COUNT       hopCount;
        SUA_ADDRS           srcAddrs;
        SUA_ADDRS           dstAddrs;
        SUA_REF_NUM         srcRefNum;
        SUA_REF_NUM         dstRefNum;
        SUA_SCCP_CAUSE      cause;
        SUA_SEQ_NUM         seqNum;
        SUA_REC_SEQ_NUM     rSeqNum;
        SUA_ASP_CAPAB       capab;
        SUA_CREDIT          cr;
        SUA_DATA            data;
        SUA_CAUSE_USER      causeUsr;
        SUA_NET_APP         networkAppearance;
        SUA_ROUT_KEY        rkData;
        SUA_DRN_LABEL       drnLabel;
        SUA_TID_LABEL       tidLabel;
        SUA_ADDRS_RANGE     addrRange;
        SUA_SMI             smi;
        SUA_IMPORTANCE      importance;
        SUA_MSG_PRIOR       msgPrior;
        SUA_PROT_CLASS      pClass;
        SUA_SEQ_CTL         seqCtl;
        SUA_SEGMENTATION    segmentation;
        SUA_CONG_LEVEL      congestion;

        /********************************************/
        SUA_REASON          reason;
        /*SUA_FLAGS           flags; */
        SUA_SCMG_FORM       scmg;
        SUA_PC              pc;   /* sub parameter */
        SUA_SSN             ssn;  /* sub parameter */
        SUA_GT              gt;   /* sub parameter */
        /********************************************/

        SUA_MSG_HDR         msgHeader;  /* Used by IntelliSS7 */
    }
    param_data;
}
ITS_SUA_IE;


#define ITS_MAX_SUA_IES   32


typedef struct
{
    ITS_USHORT*    mParam;
    int           nmParam;
    ITS_USHORT*    oParam;
    int           noParam;
}
SUA_MSG_DESC;




/*********************************************************************/
/*
 * family independence
 */

#if defined(CCITT)

#if !defined(USE_ANSI_SCCP)


#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_CCITT
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_CCITT

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_CCITT
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_CCITT

#define SUA_ParseAddress                            SUA_ParseAddress_CCITT

#define SUA_CLASS_NAME     "CCITT-SUA"

#define itsSUA_Class       itsSUA_CCITT_Class

#else /* !defined(USE_ANSI_SCCP) */



#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_ANSI
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_ANSI

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_ANSI
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_ANSI

#define SUA_ParseAddress                            SUA_ParseAddress_ANSI

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_ANSI

#define SUA_CLASS_NAME  "ANSI-SUA"

#define itsSUA_Class    itsSUA_ANSI_Class

#endif /* !defined(USE_ANSI_SCCP) */

#elif defined(ANSI)

#if !defined(USE_CCITT_SCCP)


#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_ANSI
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_ANSI

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_ANSI
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_ANSI

#define SUA_ParseAddress                            SUA_ParseAddress_ANSI

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_ANSI

#define SUA_CLASS_NAME  "ANSI-SUA"

#define itsSUA_Class    itsSUA_ANSI_Class

#else /* !defined(USE_CCITT_SCCP) */


#define SUA_SUAEvtToSCCPEvt                         SUA_SUAEvtToSCCPEvt_CCITT
#define SUA_SCCPEvtToSUAEvt                         SUA_SCCPEvtToSUAEvt_CCITT

#define SUA_To_SCCP_Codec                           SUA_To_SCCP_Codec_CCITT
#define SCCP_To_SUA_Codec                           SCCP_To_SUA_Codec_CCITT

#define SUA_ParseAddress                            SUA_ParseAddress_CCITT

#define SUA_PrintSUA_IES                            SUA_PrintSUA_IES_CCITT

#define SUA_CLASS_NAME  "CCITT-SUA"

#define itsSUA_Class    itsSUA_CCITT_Class

#endif /* !defined(USE_CCITT_SCCP) */

#elif defined (PRC)

#define SUA_CLASS_NAME  "PRC-SUA"

#elif defined (TTC)

#define SUA_CLASS_NAME  "TTC-SUA"
 
#endif /* defined(CCITT) */



/* message descriptors */
SUADLLAPI extern SUA_MSG_DESC SUA_DATA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DUNA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DAVA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DAUD_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_SCON_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DUPU_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPUP_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_UPACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPDN_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_DNACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_HEARTBEAT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_HEARTBEAT_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPAC_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPAC_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPIA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ASPIA_ACK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_NTFY_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_ERR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CLDT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CLDR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CODT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CODA_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_CORE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COAK_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COREF_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RESRE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RESCO_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RELRE_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_RELCO_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COERR_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_COIT_Desc;
SUADLLAPI extern SUA_MSG_DESC SUA_SCMG_Desc;




/*
 * Codecs
 */

SUADLLAPI int SUA_EncodeMsg(ITS_SUA_IE *ies, int ieCount,ITS_EVENT *event,
                            SUA_MSG_DESC* desc);

SUADLLAPI int SUA_DecodeMsg(ITS_SUA_IE *ies, int *ieCount, ITS_EVENT *ev,
                            SUA_MSG_DESC *desc);

SUADLLAPI int SUA_To_SCCP_Codec(SCTPTRAN_Manager *m, ITS_EVENT *evt,
                                ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);

SUADLLAPI int SCCP_To_SUA_Codec( SCTPTRAN_Manager *m, ITS_EVENT *evt,
                                ITS_BOOLEAN *isMgmt, ITS_OCTET *sls);


SUADLLAPI int SUA_EncodeAddress(SUA_ADDRS *suaAddr, ITS_OCTET routIndic, 
                                ITS_OCTET addrIndic, ITS_UINT pc, 
                                ITS_OCTET ssn, SUA_GT *gt, int gtLen);

SUADLLAPI int SUA_DecodeAddress(ITS_OCTET *suaAddr, int len, 
                                ITS_OCTET *routIndic, ITS_OCTET *addrIndic, 
                                ITS_UINT *pc, ITS_OCTET *ssn, SUA_GT *gt, 
                                int *gtLen);


/*
 * Helper functions
 */

SUADLLAPI ITS_SUA_IE* SUA_FindSUAIE(ITS_SUA_IE *ies, int ieCount, 
                                    ITS_USHORT paramId);

SUADLLAPI int SUA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, 
                                       ITS_UINT *rkList, int size);

SUADLLAPI int SUA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, 
                                       ITS_UINT *rkList, int *size);

SUADLLAPI int SUA_GetPadding(int size);

SUADLLAPI void SUA_HComHdrToN(SUA_MSG_HDR *msgHdr);

SUADLLAPI void SUA_NComHdrToH(SUA_MSG_HDR *msgHdr);

SUADLLAPI int SUA_SUAEvtToSCCPEvt(ITS_EVENT *evt, ITS_BOOLEAN toSCCP, 
                                  ITS_HDR *hdr, ITS_BOOLEAN *isMgmt);

SUADLLAPI int SUA_SCCPEvtToSUAEvt(SCTPTRAN_Manager *m, ITS_EVENT *evt, 
                                  ITS_BOOLEAN toUser, 
                                  ITS_HDR *hdr, ITS_OCTET *sls);

SUADLLAPI int
SUA_EncodeRoutingKey(SUA_ROUT_KEY *rkey, ITS_USHORT *rKeyLen, ITS_UINT rkid, 
                     SUA_TRAFFIC_MODE *tm, SUA_NET_APP *na, 
                     SUA_ADDRS *srcAddr, SUA_ADDRS *dstAddr, 
                     SUA_ADDRS_RANGE *addrRange, ITS_USHORT addrRangeLen);

SUADLLAPI int
SUA_EncodeAddressRange(SUA_ADDRS_RANGE *addrRange, ITS_OCTET *totLen, 
                       SUA_ADDRS *addr1, SUA_ADDRS *addr2, 
                       ITS_USHORT addrType);

SUADLLAPI ITS_UINT
SUA_GetRoutingContext(ITS_OCTET suaMsgType, const ITS_SUA_IE* srcAddr,
                      const ITS_SUA_IE* destAddr);

SUADLLAPI int
SUA_ParseAddress(const ITS_SUA_IE *suaAddr, int plen, ITS_USHORT *routInd, 
                 ITS_USHORT *addrInd, ITS_UINT *pc, ITS_OCTET *ssn, 
                 ITS_SUA_IE *gt);

SUADLLAPI int
SUA_AddIE(ITS_SUA_IE *ies, int *ieCount, const ITS_SUA_IE *ie);


/*
 * feature record
 */
SUADLLAPI extern ITS_Class   itsSUA_Class;

/*
 * user knows by which API they implemented with
 */
#define ITS_SUA     ITS_SCCP

#if defined(__cplusplus)
}
#endif

#endif /*SUA_H*/
