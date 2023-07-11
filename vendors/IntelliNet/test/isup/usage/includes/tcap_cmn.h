/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *     FILE: tcap.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: tcap_cmn.h,v 9.1 2005/03/23 12:55:21 cvsadmin Exp $
 *
 * LOG: $Log: tcap_cmn.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_TCAP_CMN_H_
#define _ITS_TCAP_CMN_H_

#ident "$Id: tcap_cmn.h,v 9.1 2005/03/23 12:55:21 cvsadmin Exp $"

/*
 * Quality of service indicator octet definitions:
 * (to select more than one option, OR together options)
 */
#define QOSI_RET_OPT    (0x01)          /* Return Option */
#define QOSI_SEQ_CTRL   (0x02)          /* Sequence Control */
#define QOSI_SLS_KEY    (0x04)          /* SLS key present */
#define QOSI_PRIORITY   (0x08)          /* Message priority octet present */

/*
 * TCAP_PN_TERMINATION values:
 */
#define TCAP_END_BASIC           (0)     /* Basic end */
#define TCAP_END_PREARRANGED     (1)     /* Pre-arranged end */

/*
 * TCAP_PN_CPT_PRESENT values:
 */
#define TCAP_NO_CPT              (0)     /* No component(s) present */
#define TCAP_CPT_PRESENT         (1)     /* Component(s) present */

/*
 * TCAP_PN_LAST_CPT values:
 */
#define TCAP_MORE_CPTS           (0)     /* More component(s) to follow */
#define TCAP_LAST_CPT            (1)     /* This is the last component */

#define TCPEND_BASIC            TCAP_END_BASIC
#define TCPEND_PREARRANGED      TCAP_END_PREARRANGED

#define TCP_NO_CPT              TCAP_NO_CPT
#define TCP_CPT_PRESENT         TCAP_CPT_PRESENT

#define TCP_MORE_CPTS           TCAP_MORE_CPTS
#define TCP_LAST_CPT            TCAP_LAST_CPT

/********************************************************************
 *                                                                  *
 *          Structure definitions for Component Primitives          *
 *                                                                  *
 ********************************************************************/

/*
 * Definitions for buffer sizes in the 'C' structured
 * representation of TCAP protocol primitives.
 *
 * Each value must allow space for the tag, length
 * and associated data to be stored.
 *
 * The user may need to change the values given in
 * order to support larger parameters or to reduce
 * the size of the structures if it is known that
 * certain parameters lengths will never be exceeded.
 */
#define IV_SIZE         (4)     /* space for 'invoke_id' parameter */
#define OP_SIZE         (32)    /* space for 'operation' parameter */
#define PR_SIZE         (256)   /* space for 'parameter' parameter */
#define ER_SIZE         (32)    /* space for 'error' parameter */
#define PB_SIZE         (16)    /* space for 'problem' parameter */
#define AC_SIZE         (64)    /* space for 'ac_name' parameter */
#define UI_SIZE         (256)   /* space for 'user_info' parameter */

/*
 * substructures for components
 */
typedef struct cpt_inv_id
{
    ITS_USHORT   len;
    ITS_OCTET    data[IV_SIZE];
}
CPT_INV_ID;

typedef struct cpt_op
{
    ITS_USHORT   len;
    ITS_OCTET    data[OP_SIZE];
}
CPT_OP;

typedef struct cpt_param
{
    ITS_USHORT   len;
    ITS_OCTET    data[PR_SIZE];
}
CPT_PARAM;

typedef struct cpt_error_code
{
    ITS_USHORT   len;
    ITS_OCTET    data[ER_SIZE];
}
CPT_ERROR_CODE;

typedef struct cpt_problem
{
    ITS_USHORT   len;
    ITS_OCTET    data[PB_SIZE];
}
CPT_PROBLEM;

/*
 * invoke primitive.  REQ and IND
 * invoke not last primitive.  REQ and IND
 */
typedef struct cpt_invoke
{
    CPT_INV_ID          invoke_id;
    CPT_OP              operation;
    CPT_PARAM           param;
#if defined(CCITT)
    ITS_USHORT          opClass;        /* 1, 2, 3 or 4 */
#endif
    ITS_USHORT          timeout;        /* 0 .. 409 */
    CPT_INV_ID          linked_id;
#define correlation_id  linked_id       /* FOR ANSI */
}
CPT_INVOKE;

/*
 * return result last primitive.  REQ and IND
 * return result not last primitive.  REQ and IND
 */
typedef struct cpt_result
{
    CPT_INV_ID    invoke_id;
#if defined(CCITT)
    CPT_OP        operation;
#endif
    CPT_PARAM     param;
}
CPT_RESULT;

/*
 * user error primitive.  REQ and IND
 */
typedef struct cpt_error
{
    CPT_INV_ID        invoke_id;
    CPT_ERROR_CODE    error;
    CPT_PARAM         param;
}
CPT_ERROR;

/*
 * user reject primitive.  REQ and IND
 * local reject primitive.  IND only.
 * remote reject primitive.  IND only.
 */
typedef struct cpt_reject
{
    CPT_INV_ID    invoke_id;
    CPT_PROBLEM   problem;
#if defined(ANSI)
    CPT_PARAM     param;
#endif
}
CPT_REJECT;

/*
 * user cancel primitive.  REQ only.
 * local cancel primitive.  IND only.
 */
typedef struct cpt_cancel
{
    CPT_INV_ID    invoke_id;
}
CPT_CANCEL;


/*
 * Timer Reset primitive (ITU White Book 97 only).  REQ only.
 */
#if defined(CCITT)
typedef struct cpt_timerReset
{
    CPT_INV_ID    invoke_id;
}
CPT_TIMER_RESET;
#endif


/*
 * union of all of the above
 */
typedef struct tcap_cpt
{
    ITS_USHORT   last_component;  /* either 0 or non-zero */
    ITS_USHORT   ptype;           /* prim type (TCPPT_xxx values) */
    union
    {
        CPT_INVOKE          invoke;
        CPT_RESULT          result;
        CPT_ERROR           error;
        CPT_REJECT          reject;
        CPT_CANCEL          cancel;
#if defined(CCITT)
        CPT_TIMER_RESET     timerReset;
#endif
    }
    u;
}
TCAP_CPT;

/********************************************************************
 *                                                                  *
 *          Structure definitions for Dialogue Primitives           *
 *                                                                  *
 ********************************************************************/

/*
 * dialog substructures
 */
typedef struct dlg_qos
{
    ITS_OCTET indicator;
    ITS_OCTET sls_key;
    ITS_OCTET priority;
    ITS_OCTET pad;
}
DLG_QOS;

typedef struct ac_name
{
    ITS_USHORT           len;
    ITS_OCTET            data[AC_SIZE];
}
DLG_AC_NAME;

typedef struct usr_inf
{
    ITS_USHORT           len;
    ITS_OCTET            data[UI_SIZE];
}
DLG_USR_INF;

/*
 * ITU and ANSI UNI. REQ and IND.
 */
typedef struct dlg_uni
{
    ITS_USHORT      cpt_present;    /* 0 or 1 */
    DLG_QOS         qos;
    DLG_AC_NAME     ac_name;
    DLG_USR_INF     user_info;
    SCCP_ADDR       orig_addr;
    SCCP_ADDR       dest_addr;
    MTP3_POINT_CODE opc;            /* For use when address doesn't include */
    MTP3_POINT_CODE dpc;            /* For use when address doesn't include */
}
DLG_UNI;

/*
 * ITU BEGIN, ANSI QUERY W/PERM and WO/PERM. REQ and IND.
 */
typedef struct dlg_begin
{
    ITS_USHORT      cpt_present;    /* 0 or 1 */
    DLG_QOS         qos;
    DLG_AC_NAME     ac_name;
    DLG_USR_INF     user_info;
    SCCP_ADDR       orig_addr;
    SCCP_ADDR       dest_addr;
    MTP3_POINT_CODE opc;            /* For use when address doesn't include */
    MTP3_POINT_CODE dpc;            /* For use when address doesn't include */
}
DLG_BEGIN;

/*
 * ITU CONTINUE, ANSI CONV W/PERM and WO/PERM. REQ and IND.
 */
typedef struct dlg_continue
{
    ITS_USHORT      cpt_present;    /* 0 or 1 */
    DLG_QOS         qos;            /* Indication only.  Ignore for request */
    DLG_AC_NAME     ac_name;
    DLG_USR_INF     user_info;
    SCCP_ADDR       orig_addr;
    MTP3_POINT_CODE opc;            /* For use when address doesn't include */
}
DLG_CONTINUE;

/*
 * ITU END, ANSI RESP. REQ and IND.
 */
typedef struct dlg_end
{
    ITS_USHORT      cpt_present;    /* 0 or 1 */
    DLG_QOS         qos;            /* Indication only.  Ignore for request */
    DLG_AC_NAME     ac_name;
    DLG_USR_INF     user_info;
    ITS_OCTET       termination;    /* 0 or 1 */
}
DLG_END;

/*
 * ITU U-ABORT. REQ only.
 * ITU P-ABORT. IND only.
 * ANSI ABORT, IND only.
 */
typedef struct dlg_abort
{
    ITS_USHORT      abort_reason;
    DLG_QOS         qos;            /* Indication only.  Ignore for request */
    DLG_AC_NAME     ac_name;        /* P-ABORT does not include this */
    DLG_USR_INF     user_info;      /* P-ABORT does not include this */
}
DLG_ABORT;

/*
 * ITU NOTICE, ANSI NOTICE. IND only (based on QOS return option).
 */
typedef struct dlg_notice
{
    ITS_OCTET      report_cause;
    ITS_OCTET      user_data_len;  /* Presence depends on manufacturer */
    SCCP_ADDR      orig_addr;      /* Presence depends on manufacturer */
    SCCP_ADDR      dest_addr;      /* Presence depends on manufacturer */
    SCCP_DATA      user_data;      /* Presence depends on manufacturer */
}
DLG_NOTICE;

/*
 * union of above types
 */
typedef struct tcap_dlg
{
    ITS_USHORT   ptype;          /* primitive type (TCPPT_xxx values) */
    union
    {
        DLG_UNI             uni;
        DLG_BEGIN           begin;
        DLG_CONTINUE        cont;
        DLG_END             end;
        DLG_ABORT           abort;
        DLG_NOTICE          notice;
    }
    u;
}
TCAP_DLG;

/*
 * where to find the TCAP msg type in the event if src == ITS_TCAP
 */
#define TCAP_MSG_TYPE(ev)   ((ev)->data[0])
#define TCAP_MSG_DATA(ev)   ((ev)->data[1 + sizeof(ITS_USHORT)])
 
#define ITS_TCAP_DLG    1
#define ITS_TCAP_CPT    2

/*
 * the one define users may want to know about.  When this
 * bit is set in a dialogue id, the direction is INCOMING.
 */
#define TCAP_DIR_BIT    0x8000

/******************************** TCAP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/
/*
 * handy defines used by our implementation(s).  Users should
 * ignore this section
 */
#define MAX_NUM_INVOKES	256
#define MAX_NUM_DIALOGS 0x00010000

#define DLG_INCOMING	1
#define DLG_OUTGOING    2

#define INV_INCOMING	1
#define INV_OUTGOING	2

#define LOCAL_REJECT_MARKER             (0x80U)

#endif /* _ITS_TCAP_CMN */

