
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
 * CONTRACT: Internal                                                       *
 *                                                                          *
 * FILE: mtp2_alarms.h                                                      *
 *                                                                          *
 ****************************************************************************
 *
 * ID: $Id: mtp2_alarm.h,v 9.1 2005/03/23 12:55:43 cvsadmin Exp $                                                                
 *                                                                          
 * LOG: $Log: mtp2_alarm.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.2.12.2  2005/01/24 10:52:42  snagesh
 * LOG: Moved MTP2_ALARM_START and MTP2_ALARM_END to ss7_alarms.h
 * LOG:
 * LOG: Revision 1.1.2.2.12.1  2005/01/03 15:52:12  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 1.1.2.2  2004/03/18 11:02:28  kannanp
 * LOG: Review comments added.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/03/17 13:00:22  kannanp
 * LOG: For MTP2 Alarms.
 * LOG:
 *                                                                          
 ****************************************************************************/

#ifndef _MTP2_ALARM_H
#define _MTP2_ALARM_H
#define DEBUG

#include<its_alarm.h>

/* Disconnect Indication Reasons */
#define SUERM_OVERFLOW              1
#define T2_EXPIRED                  2
#define T7_EXPIRED                  3
#define INVALID_BSN                 5
#define INVALID_FIB                 6
#define STATUS_IND_FROM_NETWORK     7
#define L2_CONG_EXCESS_PERIOD       8

extern ITS_UINT MTP2_AlarmLevel;
extern ALARM_Format *MTP2_Alarms[];

void MTP2_Alarm_NMS(int which, const char *file, const int line,
                char *format, ...);

#endif /* endif _MTP2_ALARM_H */

