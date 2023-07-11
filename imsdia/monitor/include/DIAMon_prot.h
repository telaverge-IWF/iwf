/****************************************************************************
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
 * ID: $Id: DIAMon_prot.h,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
 *
 * LOG: $Log: DIAMon_prot.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/06/21 11:34:06  nvijikumar
 * LOG: Modifications for Copyright Info.
 * LOG:
 ***************************************************************************/
#ifndef DIA_MONITOR_PROT_H
#define DIA_MONITOR_PROT_H

#define DIA_WORK_SRC           0x80U
#define DIA_INTERDIA_SRC       0x81U
#define DIA_CONFIG_SRC         0x83U
#define DIA_MONITOR_SRC        0X84U

#define DIA_MONITOR_HEARTBEAT               0XA0U
#define DIA_MONITOR_HEARTBEAT_RESPONSE      0XA1U

#define DONT_RESTART_REQUEST                 0XA3U
#define DONT_RESTART_RESPONSE                0XA4U

#endif
