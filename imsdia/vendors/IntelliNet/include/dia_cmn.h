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
 * LOG: Revision 2.6  2006/11/03 14:04:49  nvijikumar
 * LOG: 64 bit Compilation support (Yogesh).
 * LOG:
 * LOG: Revision 2.5  2006/10/17 09:53:17  nanaparthi
 * LOG: Changes for Solaris Build.
 * LOG:
 * LOG: Revision 2.4  2006/10/12 10:35:38  yranade
 * LOG: Changing timer context sessionId as static variable
 * LOG: ( due to memory leak problem in load mode)
 * LOG:
 * LOG: Revision 2.3  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
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
 * ID: $Id: dia_cmn.h,v 3.3.22.3.4.2.4.1 2013/10/26 07:42:21 ncshivakumar Exp $
 ****************************************************************************/
#ident "$Id: dia_cmn.h,v 3.3.22.3.4.2.4.1 2013/10/26 07:42:21 ncshivakumar Exp $"

#ifndef DIA_CMN_CODE_H_
#define DIA_CMN_CODE_H_

#include <dia_defines.h>
#include <dia_trace.h>
#ifdef FOR_DRE
#include <Component.h>
#endif
#include <dia_stack_stats.h>
#include <its_redundancy.h>
#include <itsdiameter.h>

#include <diameter/Implementation.h>
#include <diameter/Command.h>
#include <diameter/base/ReAuth.h>
#include <diameter/base/Accounting.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/DeviceWatchdog.h>
#include <diameter/base/DisconnectPeer.h>
#include <diameter/base/PROXYABLEERROR.h>
#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/base/BaseGenericCommand.h>
#include <diameter/base/CapabilitiesExchange.h>
#include <diameter/cua/CapabilitiesUpdate.h>


#define ITS_DIA_INBOUND_SESS_INDEX_ENTRY       0x00000000
#define ITS_DIA_OUTBOUND_SESS_INDEX_ENTRY      0xFFFFFFFF
#define ITS_DIA_MASK_FLAG      0x01


#define ITS_DIA_HDR_SIZE    9
#define ITS_DIA_HHID_LOC    12
#define ITS_DIA_EEID_LOC    16

// Please refer Accelero timer context before changing size
#define ITS_DIA_TIMER_CXT_SIZE    128

#define ITS_DIA_PTR_DATA_LEN   (sizeof(ITS_USHORT) + sizeof(ITS_ULONG))

#define DIA_FLAGS diameter::Dia_Flags
#define DIA_HDR diameter::DiaHeader
#define DIA_BASE_CMD diameter::DiaMsgFlow
#define DIA_CMD diameter::Command
#define DIA_GEN_CMD diameter::base::BaseGenericCommand
#define DIA_CER diameter::base::CapabilitiesExchangeRequest
#define DIA_CEA diameter::base::CapabilitiesExchangeAnswer
#define DIA_DWR diameter::base::DeviceWatchdogRequest
#define DIA_DWA diameter::base::DeviceWatchdogAnswer
#define DIA_STR diameter::base::SessionTerminationRequest
#define DIA_STA diameter::base::SessionTerminationAnswer
#define DIA_DPR diameter::base::DisconnectPeerRequest
#define DIA_DPA diameter::base::DisconnectPeerAnswer
#define DIA_ASR diameter::base::AbortSessionRequest
#define DIA_ASA diameter::base::AbortSessionAnswer
#define DIA_ACR diameter::base::AccountingRequest
#define DIA_ACA diameter::base::AccountingAnswer
#define DIA_RAR diameter::base::ReAuthRequest
#define DIA_RAA diameter::base::ReAuthAnswer
#define DIA_CUR diameter::cua::CapabilitiesUpdateRequest
#define DIA_CUA diameter::cua::CapabilitiesUpdateAnswer

#define DIA_CAPABILITIES_UPDATE_APPLICATION_ID 10

#ifdef FOR_DRE
#define DT_ERR(x) CLOG_ERROR x 
#define DT_DBG(x) CLOG_DEBUG x
#define DT_WRN(x) CLOG_WARNING x
#define DT_CRT(x) CLOG_CRITICAL x
#else
#define DT_ERR DIA_TRACE_ERROR
#define DT_DBG DIA_TRACE_DEBUG
#define DT_WRN DIA_TRACE_WARNING
#define DT_CRT DIA_TRACE_CRITICAL
#endif

#endif


