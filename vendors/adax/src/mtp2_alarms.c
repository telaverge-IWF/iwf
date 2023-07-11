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
 ****************************************************************************
 *
 * LOG: $Log: mtp2_alarms.c,v $
 * LOG: Revision 9.2  2007/01/11 12:43:44  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.1  2006/08/18 12:18:25  mshanmugam
 * LOG: Modified the MTP2 Alarm Objects for OAM feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.4.2.14.2  2005/01/24 10:46:50  snagesh
 * LOG: Included ss7_alarms.h since MTP2_ALARM_START and MTP2_ALARM_END moved there
 * LOG:
 * LOG: Revision 1.1.4.2.14.1  2005/01/03 15:16:55  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 1.1.4.2  2004/03/18 13:29:36  kannanp
 * LOG: Review comments added.
 * LOG:
 * LOG: Revision 1.1.4.1  2004/03/17 12:46:43  kannanp
 * LOG: For MTP2 Alarms.
 * LOG:
 *                                                                          
 * ID: $Id: mtp2_alarms.c,v 9.2 2007/01/11 12:43:44 yranade Exp $                                                                
 ****************************************************************************/

#include <its_assertion.h>
#include <mtp2_alarm.h>
#include <ss7_alarms.h>

ITS_UINT MTP2_AlarmLevel = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(MTP2, 12000,
                    "ADAX MTP2 Initialize success",
                    ALARM_LVL_INFO,    "ADAX MTP2 Initialize success",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12001,
                    "ADAX MTP2 Initialize failed ",
                    ALARM_LVL_MAJOR,   "ADAX MTP2 Initialize failed",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12002,
                    "Failed to retrieve data from board",
                    ALARM_LVL_MAJOR,   "Failed to retrieve data from board",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12003,
         "Timer T2 Expired - cannot change from not aligned to aligned state",
         ALARM_LVL_MINOR,        "Timer T2 Expired",
         "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12004,
                    "Timer T7 Expired - Link Failure indication sent to L3",
                    ALARM_LVL_MINOR,     "Timer T7 Expired",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12005,
               "Received  SIOS/SIO/SIN/SIE from network", 
                ALARM_LVL_MAJOR,    "Received SIOS/SIO/SIN/SIE",
               "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12006,
                    "Local Processor Outage Indication from L3 ",
                    ALARM_LVL_MAJOR,  "Local Processor Outage",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12007,
                    "Remote Processor Outage received from Network",
                    ALARM_LVL_MAJOR,  "Remote Processor Outage",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12008,
                    "Local Processor Recovered",
                    ALARM_LVL_INFO,    "Local processor Recovered",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12009,
                    "Remote Processor Recovered",
                    ALARM_LVL_INFO,    "Remote Processor Recovered",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12010,
                    "Failed to start MTP2 on L3 trigger",
                    ALARM_LVL_CRIT,    "Failed to start MTP2 on L3 trigger",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12011,
                    "Failed to stop MTP2 on L3 trigger",
                    ALARM_LVL_CRIT,    "Failed to stop MTP2 on L3 trigger",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12012,
                    "MTP2 started success",
                    ALARM_LVL_INFO,    "MTP2 started success",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12013,
                    "MTP2 stoped success",
                    ALARM_LVL_INFO,    "MTP2 stopped success",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12014,
               "Incorrect Forward Indicator Bit and Backward Sequence Number",
                ALARM_LVL_MINOR,       "Incorrect FIB BSN",
               "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12015,
                    "Invalid Forward Sequence Number",
                    ALARM_LVL_MAJOR,    "Invalid Forward Sequence Number",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12016,
                    "Signaling Unit Error Rate Monitor expired",
                    ALARM_LVL_MAJOR,    "SUERM Expiry",
                    "Link", ITS_TRUE);      

ALARM_FORMAT_SUBSYS(MTP2, 12017,
                    "Congestion detected",
                    ALARM_LVL_MAJOR,   "Congestion detected",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12018,
                    "Congestion recovered ",
                    ALARM_LVL_INFO,   "Congestion recovered",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12019,
                    "Failed to clear RTB MTP2 buffers",
                    ALARM_LVL_MAJOR,    "Failed to clear RTB MTP2 buffers",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12020,
                    "Trigger from L3 Emergency alignment not success",
                    ALARM_LVL_CRIT,     "Emergency alignment not success",
                    "Link", ITS_TRUE); 

ALARM_FORMAT_SUBSYS(MTP2, 12021,
                    "Failed to send data to board",
                    ALARM_LVL_MAJOR,    "Failed to send data to board",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12022,
                    "Timer T1 Expired - cannot change to Inservice or aligned r eady state",
                    ALARM_LVL_MINOR,   "Timer T1 Expired",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12023,
                    "Timer T3 Expired - cannot change from aligned to proving s tate",
                    ALARM_LVL_MINOR,    "Timer T3 Expired",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(MTP2, 12024,
                    "Current proving attemt failed",
                    ALARM_LVL_MAJOR,    "Current proving attemt failed",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12025,
                    "All proving attempts failed",
                    ALARM_LVL_CRIT,     "All proving attempts failed",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12026,
                    "Remote Congestion detected",
                    ALARM_LVL_MAJOR,    "Remote Congestion detected",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12027,
                    "Remote Congestion Recovered",
                    ALARM_LVL_INFO,    "Remote Congestion Recovered",
                    "Link", ITS_TRUE);

ALARM_Format *MTP2_Alarms[] =
{
    &ALARM_MTP212000,
    &ALARM_MTP212001,
    &ALARM_MTP212002,
    &ALARM_MTP212003,
    &ALARM_MTP212004,
    &ALARM_MTP212005,
    &ALARM_MTP212006,
    &ALARM_MTP212007,
    &ALARM_MTP212008,
    &ALARM_MTP212009,
    &ALARM_MTP212010,
    &ALARM_MTP212011,
    &ALARM_MTP212012,
    &ALARM_MTP212013,
    &ALARM_MTP212014,
    &ALARM_MTP212015,
    &ALARM_MTP212016,
    &ALARM_MTP212017,
    &ALARM_MTP212018,
    &ALARM_MTP212019,
    &ALARM_MTP212020,
    &ALARM_MTP212021,
    &ALARM_MTP212022,
    &ALARM_MTP212023,
    &ALARM_MTP212024,
    &ALARM_MTP212025,
    &ALARM_MTP212026,
    &ALARM_MTP212027
};


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a MTP2 alarm.
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
void
MTP2_Alarm_ADAX(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= MTP2_ALARM_START &&
                 which <= MTP2_ALARM_END);

    fmt = MTP2_Alarms[which - MTP2_ALARM_START];

    if (fmt->severity > MTP2_AlarmLevel)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
