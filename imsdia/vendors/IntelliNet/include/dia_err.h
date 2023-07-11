/*********************************-*HPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_err.h,v $
 * LOG: Revision 3.5.14.2  2013/01/04 06:56:39  millayaraja
 * LOG: modified to update Error stats
 * LOG:
 * LOG: Revision 3.5.14.1  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.5.36.1  2012/11/14 08:28:08  millayaraja
 * LOG: modified to accomdate Peer stack stats
 * LOG:
 * LOG: Revision 3.5  2009/07/24 09:22:18  rajeshak
 * LOG: Changes done for IDC-IDS Heartbeat with Custom AVP in DWR.
 * LOG:
 * LOG: Revision 3.4  2008/12/12 17:40:20  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.3  2008/12/07 09:33:08  rajeshak
 * LOG: Added the new function SendErrResToPeerNApp to handle error.
 * LOG:
 * LOG: Revision 3.2  2008/04/21 11:55:37  nanaparthi
 * LOG: Added ErrorCode for Invalid Realm
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.6  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.3.10.3  2007/05/28 14:21:50  nvijikumar
 * LOG: Provided new fun to send error response if msg failed to decode.
 * LOG:
 * LOG: Revision 2.3.10.2  2007/03/13 15:27:51  nvijikumar
 * LOG: Moved error defines to dia_define.h header file.
 * LOG:
 * LOG: Revision 2.3.10.1  2007/03/08 15:01:50  nvijikumar
 * LOG: Provided TO_TEXT macro.
 * LOG:
 * LOG: Revision 2.3  2006/10/09 13:32:30  yranade
 * LOG: Added defines.
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_err.h,v 3.5.14.2 2013/01/04 06:56:39 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: dia_err.h,v 3.5.14.2 2013/01/04 06:56:39 millayaraja Exp $"

#ifndef DIA_ERR_CODE_H_
#define DIA_ERR_CODE_H_

#include <dia_cmn.h>
#include <dia_session_table.h>
#include <dia_stack_statistics.h>

#define PERM_ERR_CODE_TO_TEXT(x) \
    ((x==ITS_DIA_AVP_UNSUPPORTED)        ? "ITS_DIA_AVP_UNSUPPORTED"      : \
    ((x==ITS_DIA_UNKNOWN_SESSION_ID)     ? "ITS_DIA_UNKNOWN_SESSION_ID"   : \
    ((x==ITS_DIA_AUTHORIZATION_REJECT)   ? "ITS_DIA_AUTHORIZATION_REJECT" : \
    ((x==ITS_DIA_INVALID_AVP_VALUE)      ? "ITS_DIA_INVALID_AVP_VALUE"    : \
    ((x==ITS_DIA_MISSING_AVP)            ? "ITS_DIA_MISSING_AVP"          : \
    ((x==ITS_DIA_RESOURCES_EXCEEDED)     ? "ITS_DIA_RESOURCES_EXCEEDED"   : \
    ((x==ITS_DIA_CONTRADICTING_AVPS)     ? "ITS_DIA_CONTRADICTING_AVPS"   : \
    ((x==ITS_DIA_AVP_NOT_ALLOWED)        ? "ITS_DIA_AVP_NOT_ALLOWED"      : \
    ((x==ITS_DIA_AVP_MULTI_OCCUR)        ? "ITS_DIA_AVP_MULTI_OCCUR"      : \
    ((x==ITS_DIA_NO_COMMON_APP)          ? "ITS_DIA_NO_COMMON_APP"        : \
    ((x==ITS_DIA_UNSUPPORTED_VERSION)    ? "ITS_DIA_UNSUPPORTED_VERSION"  : \
    ((x==ITS_DIA_UNABLE_TO_COMPLY)       ? "ITS_DIA_UNABLE_TO_COMPLY"     : \
    ((x==ITS_DIA_INVALID_BIT_IN_HDR)     ? "ITS_DIA_INVALID_BIT_IN_HDR"   : \
    ((x==ITS_DIA_INVALID_AVP_LENGTH)     ? "ITS_DIA_INVALID_AVP_LENGTH"   : \
    ((x==ITS_DIA_INVALID_MSG_LENGTH)     ? "ITS_DIA_INVALID_MSG_LENGTH"   : \
    ((x==ITS_DIA_INVALID_AVP_BIT_COMBO)  ? "ITS_DIA_INVALID_AVP_BIT_COMBO": \
    ((x==ITS_DIA_NO_COMMON_SECURITY)     ? "ITS_DIA_NO_COMMON_SECURITY"   : \
    "INVALID")))))))))))))))))

/* Local Defines */

#define ITS_DIA_LOCAL_HOST_MATCH       100
#define ITS_DIA_LOCAL_REALM_MATCH      101

#define ITS_DIA_INITFAIL              -400
#define ITS_DIA_ALLOCFAIL             -401

#define ITS_DIA_EINVALID_PEER         -500
#define ITS_DIA_EINVALID_PEER_STATE   -501


#define ITS_DIA_LOCAL_HOST_MISMATCH   -502
#define ITS_DIA_LOCAL_REALM_MISMATCH  -503

#define ITS_DIA_EINVALID_REALM        -504

typedef enum _dia_err_act_type
{
    SEND_ERROR_TO_PEER = 0,
    LOOP_TO_APP,
    HEARTBEAT
}
DIA_ERR_ACTION_TYPE;

class DiaErrHandler
{
public:
    static int HandleError(ITS_USHORT trInst,
                           DIA_BASE_CMD *inMsg,
                           DIA_ERR_ACTION_TYPE act,
                           ITS_UINT rCode);

    static int HandleError(ITS_USHORT trInst,
                           ITS_OCTET *inMsg,
                           ITS_UINT rCode);
    static int SendErrorResponse(SESSION_ENTRY* e, 
                            DIA_BASE_CMD* cmd); 
    static int UpdateErrorStats(ITS_UINT trInst,
                                ITS_UINT rCode);
};




#endif


