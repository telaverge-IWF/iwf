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
 * LOG: $Log: app_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2006/10/17 09:18:40  yranade
 * LOG: Cleanup logs.
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * ID: $Id: app_defines.h,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app_defines.h,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $"

#ifndef _SAMPLE_APP_DEFINE
#define _SAMPLE_APP_DEFINE

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define SH_INTERFACE_APP_ID      16777217
#define CXDX_INTERFACE_APP_ID    16777216
#define GQGQ_INTERFACE_APP_ID    16777222
#define RFRO_INTERFACE_APP_ID    4
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id's
 * (Worker: Thread with an associated TaskQueue)
 **/
#define BASE_APP_TQ_INST      1
#define SH_APP_TQ_INST        2
#define CXDX_APP_TQ_INST      3
#define GQGQ_APP_TQ_INST      4
#define RFRO_APP_TQ_INST      5

/** 
 * Standard CommandCode's defined by IANA
 * For Base Interface
 **/
#define BASE_ACCT_MSG_CMD_CODE    271
#define BASE_CE_MSG_CMD_CODE      257
#define BASE_DWD_MSG_CMD_CODE     280
#define BASE_DP_MSG_CMD_CODE      282
#define BASE_RA_MSG_CMD_CODE      258
#define BASE_STR_MSG_CMD_CODE     275
#define BASE_AS_MSG_CMD_CODE      274

/** 
 * Standard CommandCode's defined by IANA
 * For Sh Interface
 **/
#define SH_PU_MSG_CMD_CODE        307
#define SH_PN_MSG_CMD_CODE        309
#define SH_SN_MSG_CMD_CODE        308
#define SH_UD_MSG_CMD_CODE        306

/** 
 * Standard CommandCode's defined by IANA
 * For Cxdx Interface
 **/
#define CXDX_LI_MSG_CMD_CODE        302
#define CXDX_MA_MSG_CMD_CODE        303
#define CXDX_PP_MSG_CMD_CODE        305
#define CXDX_RT_MSG_CMD_CODE        304
#define CXDX_SA_MSG_CMD_CODE        301
#define CXDX_UA_MSG_CMD_CODE        300


/** 
 * Standard CommandCode's defined by IANA
 * For Cxdx Interface
 **/
#define GQGQ_AA_MSG_CMD_CODE        265
#define GQGQ_RA_MSG_CMD_CODE        258
#define GQGQ_STR_MSG_CMD_CODE       275
#define GQGQ_AS_MSG_CMD_CODE        274

/** 
 * Standard CommandCode's defined by IANA
 * For RfRo Interface
 **/
#define RFRO_CC_MSG_CMD_CODE        272

#endif
