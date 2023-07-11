/*********************************-*-C-*-************************************
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
 * LOG: $Log: dcca_common.h,v $
 * LOG: Revision 3.2.84.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.2.84.1  2014/02/12 07:11:22  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.2.74.1.2.1  2013/11/05 09:47:27  jvikram
 * LOG: Merge from TNSI
 * LOG:
 * LOG: Revision 3.2.72.1  2013/07/09 06:02:39  jvikram
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.2  2008/12/12 18:07:05  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.11  2008/03/27 12:14:07  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.9.4.1  2007/04/19 09:55:08  hbhatnagar
 * LOG: Defined range for successful result code.
 * LOG:
 * LOG: Revision 2.9  2007/01/23 07:46:56  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 * LOG: Revision 2.8  2006/11/30 13:43:33  hbhatnagar
 * LOG: removed the declaration for DCCA ERROR and shifted to dia_defines.h
 * LOG:
 * LOG: Revision 2.7  2006/11/30 10:07:08  hbhatnagar
 * LOG: made changes for the error handling
 * LOG:
 * LOG: Revision 2.6  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.5  2006/11/14 10:10:26  hbhatnagar
 * LOG: shifted the namespace in .cpp
 * LOG:
 * LOG: Revision 2.4  2006/11/06 09:32:37  hbhatnagar
 * LOG: Made changes for the separation of BCGI related functionality with core.
 * LOG:
 * LOG: Revision 2.3  2006/10/31 08:27:37  hbhatnagar
 * LOG: made changes to  ReleaseSession for BCGI
 * LOG:
 * LOG: Revision 2.2  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.5  2006/09/27 09:25:34  hbhatnagar
 * LOG: Added support for bcgi namespace (badri)
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/26 06:12:21  nvijikumar
 * LOG: Added more defines for dcca testing (badri)
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:21:05  nvijikumar
 * LOG: Added more defines for ease of testing (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_common.h,v 3.2.84.2 2014/05/06 13:09:12 jkchaitanya Exp $
 *
 ****************************************************************************/

#ifndef DCCA_COMMON_H
#define DCCA_COMMON_H

/**
 * Includes
 */
#include <its++.h>
#include <engine++.h>
#include <dia_cmn.h>
#include <dia_err.h>
#include <dia_defines.h>
#include <diameter/Command.h>
#include <diameter/base/BaseAVP.h>
#include <dcca_trace.h>
#include <dcca_api.h>
#include <dcca_defines.h>

/**
 * Defines
 */
#define DCCA_COMMAND_CCR 272
#define DCCA_COMMAND_CCA 272
#define DCCA_COMMAND_AAR 265
#define DCCA_COMMAND_AAA 265
#define DCCA_COMMAND_STR 275
#define DCCA_COMMAND_STA 275
#define DCCA_COMMAND_ASR 274
#define DCCA_COMMAND_ASA 274
#define DCCA_COMMAND_DPR 282
#define DCCA_COMMAND_DPA 282

#define DCCA_CREDIT_AUTHORIZATION                     0x00
#define DCCA_RE_AUTHORIZATION                         0x01
#define DCCA_DIRECT_DEBITING                          0x00
#define DCCA_REFUND_ACCOUNT                           0x01
#define DCCA_CHECK_BALANCE                            0x02
#define DCCA_PRICE_ENQUIRY                            0x03
#define DCCA_CCFH_TERMINATE                           0x00
#define DCCA_CCFH_CONTINUE                            0x01
#define DCCA_CCFH_RETRY_TERMINATE                     0x02
#define DCCA_DIAMETER_SUCCESS_MIN_RANGE               2000
#define DCCA_DIAMETER_SUCCESS                         2001
#define DCCA_DIAMETER_LIMITED_SUCCESS                 2002
#define DCCA_DIAMETER_SUCCESS_MAX_RANGE               2999
#define DCCA_DIAMETER_AUTHENTICATION_REJECTED         4001
#define DCCA_DIAMETER_CREDIT_CONTROL_NOT_APPLICABLE   4011
#define DCCA_DIAMETER_RESOURCES_EXCEEDED              5006
#define DCCA_DIAMETER_END_USER_SERVICE_DENIED         4010 
#define DCCA_DIAMETER_USER_UNKNOWN                    5030 

#define SESSION_ID_LENGTH                             128

#define DCCA_TYPE_NOT_SET      0
#define DCCA_INI_REQUEST       1
#define DCCA_UPD_REQUEST       2
#define DCCA_TER_REQUEST       3
#define DCCA_EVE_REQUEST       4


/**
 * The  values for ccfh AVP and Requested Action AVP that are valid or
 * is outside the specification range
*/

#define OUTSIDE_RANGE    4


/**
 * The AVP CODE values as per specifications
*/ 
#define RESULT_CODE_AVP_CODE        268
#define CC_REQUEST_TYPE_AVP_CODE    416
#define CCFH_AVP_CODE               427
#define REQUESTED_ACTION_AVP_CODE   436
/**
 * The ITS_EVENT for DCCA
 */
typedef struct _DCCA_EVENT
{
    ITS_UINT    ind; /* Is it an indication or command */
    ITS_UINT    sin; /* The session index for this diameter command */    
    ITS_UINT    app; /* The application id of the diameter command */
    ITS_UINT    dir; /* The direction of the diameter command */

    ITS_UINT    err; /* The error bit in diameter command */
    ITS_UINT    req; /* The request bit in diameter command */
    ITS_UINT    cod; /* The Result-Code in diameter command */
    ITS_UINT    cmd; /* The Connand-Code in diameter command */
    ITS_UINT    typ; /* The CC-Request-Type in diameter command */    
    ITS_UINT    ccl; /* The Credit-Control in diameter command */
    ITS_UINT    act; /* The Requested-Action in diameter command */
    ITS_UINT    ccf; /* The CCFH in diameter command */
    ITS_UINT    clientId; /* The Client Id in distributed mode */
    bool    releaseSession; /* for releasing the stack session */
    ITS_OCTET   sessId[SESSION_ID_LENGTH + 1]; /* The SessionId String. */
}
DCCA_EVENT;

/****************************************************************************
 *
 *  Interface: DCCACommon Class
 *      
 *  Purpose  : To implement DCCA common functionality
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *
 ****************************************************************************/
class DCCACommon
{
public:
    /**
     * To prepare DCCA_EVENT from diameter::Command
     */
    static ITS_INT GetDccaEvent( DIA_BASE_CMD*, DCCA_EVENT*);

    /**
     * To send an indication to the application
     */
    static ITS_INT SendIndicationToApp(ITS_UINT, ITS_OCTET*, 
                             ITS_UINT, ITS_UINT, ITS_UINT);

    /**
     * To get configuration information for this module
     */
    static ITS_INT GetDCCAConf(ITS_UINT*, ITS_UINT*, ITS_UINT*, ITS_UINT*);
};

extern ITS_INT CcDecode(DIA_BASE_CMD *gCmd, DCCA_EVENT *eve);
extern ITS_INT DCCAReleaseStackSession(DCCA_EVENT *eve);
extern ITS_INT DCCAReleaseStackSessionWithSessionId(ITS_OCTET *sessionId);

#endif
