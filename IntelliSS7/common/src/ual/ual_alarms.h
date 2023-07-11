/*********************************-*-C-*-************************************
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
 ****************************************************************************
 *
 *  ID:$Id: ual_alarms.h,v 9.2 2005/12/09 20:55:46 cbashyam Exp $
 *
 * LOG: $Log: ual_alarms.h,v $
 * LOG: Revision 9.2  2005/12/09 20:55:46  cbashyam
 * LOG: Bug fixes for Bugs :2479, 2480
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:18  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.4.2  2005/01/10 07:36:50  sbabu
 * LOG:  ual alarms start &End Ranges Modified
 * LOG:
 * LOG: Revision 7.1.14.1.4.1  2005/01/04 16:43:34  sbabu
 * LOG: UAL OAM Changes
 * LOG:
 * LOG: Revision 7.1.14.1  2004/10/06 08:36:26  mmanikandan
 * LOG: Support for windows build.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/07/09 19:47:55  ngoel
 * LOG: correct start and end index
 * LOG:
 * LOG: Revision 1.2  2002/07/08 18:18:30  ngoel
 * LOG: add ual alarms
 * LOG:
 * LOG: Revision 1.1  2002/07/08 14:31:14  ngoel
 * LOG: start UAL alarms
 * LOG:
 * LOG:
 ****************************************************************************/
#ifndef UAL_ALARMS_H
#define UAL_ALARMS_H

#include <its_alarm.h>
#include <its_ual.h>

/*
 * ranges:Alarms Id 4027 to 4038 are there in m3ua.c
 */
#define UAL_ALARM_START   4000
#define UAL_ALARM_END     4100 

/*
 * formats
 */
UALDLLAPI extern ALARM_Format *UAL_Alarms[];

/*
 * levels
 */
UALDLLAPI extern ITS_UINT UAL_AlarmLevel;

/*
 * APIs
 */
UALDLLAPI void  
UAL_Alarm(int which, const char *file, const int line,
          char *format, ...);

#endif
