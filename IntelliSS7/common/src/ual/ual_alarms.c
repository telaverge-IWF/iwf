
/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: ual_alarms.c,v 9.6 2008/06/20 10:41:00 mshanmugam Exp $
 *
 *  LOG: $Log: ual_alarms.c,v $
 *  LOG: Revision 9.6  2008/06/20 10:41:00  mshanmugam
 *  LOG: Accelero CGI Phase I:D0110-D0140
 *  LOG:
 *  LOG: Revision 9.5  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.4.2.1  2007/04/30 11:16:04  pspl
 *  LOG: (PSPL, abhijeet) modified Documentation for M3UA alarm - added 4039 for invalid msgType
 *  LOG:
 *  LOG: Revision 9.4  2007/01/10 11:15:11  yranade
 *  LOG: Merge changes from 6.5.3 and Lucent branches
 *  LOG:
 *  LOG: Revision 9.3  2005/12/09 20:54:50  cbashyam
 *  LOG: Bug fixes for Bugs : 2479, 2480
 *  LOG: Changed UAL Alarm IDs since they were
 *  LOG: clashing with M3UA Alarms IDs
 *  LOG:
 *  LOG: Revision 9.2  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:18  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.10.1.4.2  2005/02/09 11:00:06  csireesh
 *  LOG: Validation Bug Fix(Alarms).
 *  LOG:
 *  LOG: Revision 7.2.10.1.4.1  2005/01/04 15:07:33  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.2.10.1  2004/10/06 08:34:00  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.2  2003/01/16 19:46:38  mmiers
 *  LOG: Change of prototype.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 1.4  2002/07/19 20:25:30  ngoel
 *  LOG: coorect function names in alarm call
 *  LOG:
 *  LOG: Revision 1.3  2002/07/08 18:18:30  ngoel
 *  LOG: add ual alarms
 *  LOG:
 *  LOG: Revision 1.2  2002/07/03 19:47:44  ngoel
 *  LOG: add ual alarm code
 *  LOG:
 *  LOG: Revision 1.1  2002/07/03 18:27:58  ngoel
 *  LOG: start ual alarms
 *  LOG:
 *  LOG:
 ****************************************************************************/

#include <its_assertion.h>

#include "ual_alarms.h"

UALDLLAPI ITS_UINT UAL_AlarmLevel = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(UAL, 4001,
                    "SCTP Lost Communication",
                    ALARM_LVL_MAJOR,         "UAL_HandleSCTPIndication",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4002,
                    "SCTP Communication UP",
                    ALARM_LVL_INFO,         "UAL_HandleSCTPIndication",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4003,
                    "SCTP Can't Start",
                    ALARM_LVL_CRIT,         "UAL_HandleSCTPIndication",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4005,
                    "SCTP Restart Indication",
                    ALARM_LVL_INFO,         "UAL_HandleSCTPIndication",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4006,
                    "AS Inactive Indication from SG",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4007,
                    "UAL Error Indication",
                    ALARM_LVL_MINOR,          "Process_NotifyMsg", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4008,
                    "ASP UP Ack",  
                    ALARM_LVL_INFO,           "ProcessASP_UP_ACK", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4009,
                    "ASP UP Indication",
                    ALARM_LVL_INFO,            "ProcessASP_UP", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4010,
                    "ASP DOWN confirm",
                    ALARM_LVL_INFO,             "ProcessASP_DOWN_ACK", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4011,
                    "ASP DOWN Indication",
                    ALARM_LVL_MINOR,             "ProcessASP_DOWN", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4012,
                    "Got ASP-ACTIVE in ASP_DOWN state",
                    ALARM_LVL_CRIT,           "UAL_HandleTrafficMaintMsg", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4013,
                    "ASP INACTIVE Confirm", 
                    ALARM_LVL_MINOR,         "ProcessASP_INACTIVE_ACK",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4014,
                    "ASP INACTIVE Indication", 
                    ALARM_LVL_MINOR,         "ProcessASP_INACTIVE",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4015,
                    "AS ACTIVE Indication",
                    ALARM_LVL_INFO,         "ProcessASP_ACTIVE",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4016,
                    "AS INACTIVE Indication",
                    ALARM_LVL_INFO,         "UpdateStaticConfigOfAS",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4017,
                    "Registration Confirm", 
                    ALARM_LVL_INFO,         "Ual_Main", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4018,
                    "Registration Indication", 
                    ALARM_LVL_INFO,          "Ual_Main", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4019,
                     "Deregistration Confirm", 
                    ALARM_LVL_INFO,          "Ual_Main", 
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4020,
                    "Deregistration Indication", 
                    ALARM_LVL_INFO,         "Ual_Main",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4021,
                     "AS ACTIVE Indication from SG", 
                    ALARM_LVL_INFO,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4022,
                     "AS pending indication from SG", 
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4023,
                    "Insufficient resources indication from SG", 
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4024,
                    "Alternate ASP active indication from SG",
                    ALARM_LVL_INFO,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4025,
                    "ASP failure indication ",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4026,
                    "Received invalid message type",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4052,
                    "Invalid Transport",
                    ALARM_LVL_MAJOR,         "UAL_EncodeMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4053,
                    "UAL Message Encode Failed",
                    ALARM_LVL_MAJOR,         "UAL_EncodeMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4054,
                    "UAL Message Decode Failed",
                    ALARM_LVL_MAJOR,         "UAL_DecodeMsg",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4055,
                    "UAL Routing Context Decode Failed",
                    ALARM_LVL_MINOR,         "UAL_DecodeRoutingContext",
                    "UAL", ITS_TRUE);

ALARM_FORMAT_SUBSYS(UAL, 4056,
                    "AS Inactive Indication from IPSP",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);
                                                                                
ALARM_FORMAT_SUBSYS(UAL, 4057,
                    "AS ACTIVE Indication from IPSP",
                    ALARM_LVL_INFO,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);
                                                                                
ALARM_FORMAT_SUBSYS(UAL, 4058,
                    "AS pending indication from IPSP",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);
                                                                                
ALARM_FORMAT_SUBSYS(UAL, 4059,
                    "Insufficient resources indication from IPSP",
                    ALARM_LVL_MINOR,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);
                                                                                
ALARM_FORMAT_SUBSYS(UAL, 4060,
                    "Alternate IPSP active indication",
                    ALARM_LVL_INFO,         "Process_NotifyMsg",
                    "UAL", ITS_TRUE);

UALDLLAPI ALARM_Format *UAL_Alarms[] =
{
    &ALARM_UAL4001,
    &ALARM_UAL4002,
    &ALARM_UAL4003,
    NULL,
    &ALARM_UAL4005,
    &ALARM_UAL4006,
    &ALARM_UAL4007,
    &ALARM_UAL4008,
    &ALARM_UAL4009,
    &ALARM_UAL4010,
    &ALARM_UAL4011,
    &ALARM_UAL4012,
    &ALARM_UAL4013,
    &ALARM_UAL4014,
    &ALARM_UAL4015,
    &ALARM_UAL4016,
    &ALARM_UAL4017,
    &ALARM_UAL4018,
    &ALARM_UAL4019,
    &ALARM_UAL4020,
    &ALARM_UAL4021,
    &ALARM_UAL4022,
    &ALARM_UAL4023,
    &ALARM_UAL4024,
    &ALARM_UAL4025,
    &ALARM_UAL4026,
    NULL,           /* Alarms 4027 to 4045 - M3UA alarms */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,          
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,          /* 4046 to 4051 left empty to add other M3UA or SUA Alarms */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &ALARM_UAL4052,
    &ALARM_UAL4053,
    &ALARM_UAL4054,
    &ALARM_UAL4055,
    &ALARM_UAL4056,
    &ALARM_UAL4057,
    &ALARM_UAL4058,
    &ALARM_UAL4059,
    &ALARM_UAL4060
};


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a UAL alarm.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UALDLLAPI void
UAL_Alarm(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= UAL_ALARM_START &&
                 which <= UAL_ALARM_END);

    fmt = UAL_Alarms[which - UAL_ALARM_START - 1];

    if (fmt->severity > UAL_AlarmLevel)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
