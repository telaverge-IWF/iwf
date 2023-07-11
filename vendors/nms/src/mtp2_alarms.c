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
 * ID: $Id: mtp2_alarms.c,v 9.1 2005/04/11 09:56:51 keshavm Exp $          
 *
 * LOG: $Log: mtp2_alarms.c,v $
 * LOG: Revision 9.1  2005/04/11 09:56:51  keshavm
 * LOG: Source propogation from PR6_4_2
 * LOG:
 * LOG: Revision 1.1.2.2.12.2  2005/01/24 10:53:45  snagesh
 * LOG: Included ss7_alarms.h since MTP2_ALARM_START and MTP2_ALARM_END moved there
 * LOG:
 * LOG: Revision 1.1.2.2.12.1  2005/01/03 16:25:00  snagesh
 * LOG: MTP2 OAM changes
 * LOG:
 * LOG: Revision 1.1.2.2  2004/03/18 10:59:55  kannanp
 * LOG: Added review comments.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/03/17 13:11:38  kannanp
 * LOG: For MTP2 Alarms.
 * LOG:
 ****************************************************************************/

#include <its_assertion.h>
#include <mtp2_alarm.h>
#include <ss7_alarms.h>

ITS_UINT MTP2_AlarmLevel = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(MTP2, 12000,
                    "NMS MTP2 Initialize success ",
                    ALARM_LVL_INFO,   "NMS MTP2 Initialize success",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12001,
                    "NMS MTP2 Initialize failed ",
                    ALARM_LVL_MAJOR,  "NMS MTP2 Initialize failed ",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12002,
                    "Failed to retrieve data from board",
                    ALARM_LVL_MAJOR,  "Failed to retrieve data from board",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12003,
          "Timer T2 Expired - cannot change from not aligned to aligned state",
          ALARM_LVL_MINOR,            "Timer T2 Expired",
          "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12004,
                    "Timer T7 Expired - Link Failure indication sent to L3",
                    ALARM_LVL_MINOR,  "Timer T7 Expired",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12005,
               "Received SIOS/SIO/SIN/SIE", 
                ALARM_LVL_MAJOR,      "Received SIOS/SIO/SIN/SIE",
               "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12006,
                    "Local Processor Outage Indication from L3",
                    ALARM_LVL_MAJOR,  "Local Processor Outage Indication",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12007,
                    "Remote Processor Outage received from Network",
                    ALARM_LVL_MAJOR,   "Remote Processor Outage",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12008,
                    "Local Processor Recovered",
                    ALARM_LVL_INFO,    "Local Processor Recovered",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12009,
                    "Remote Processor Recovered",
                    ALARM_LVL_INFO,    "Remote Processor Recovered",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12010,
                    "Failed to start MTP2 on L3 trigger",
                    ALARM_LVL_CRIT,    "Failed to start MTP2 on L3 trigger",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12011,
                    "Failed to stop MTP2 on L3 trigger",
                    ALARM_LVL_CRIT,    "Failed to stop MTP2 on L3 trigger",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12012,
                    "MTP2 started success",
                    ALARM_LVL_INFO,    "MTP2 started success",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12013,
                    "MTP2 stopped success",
                    ALARM_LVL_INFO,    "MTP2 stoped success",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12014,
                "Incorrect Forward Indicator Bit and Backward Sequence Number",
                ALARM_LVL_MINOR,       "Incorrect FIB BSN",
                "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12015,
                    "Invalid Forward Sequence Number",
                    ALARM_LVL_MAJOR,    "Invalid Forward Sequence Number",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12016,
                    "Signaling Unit Error Rate Monitor expired",
                    ALARM_LVL_MAJOR,    "SUERM expired",
                    "MTP2", ITS_TRUE);      

ALARM_FORMAT_SUBSYS(MTP2, 12017,
                    "Congestion detected",
                    ALARM_LVL_MAJOR,   "Congestion detected",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12018,
                    "Congestion recovered ",
                    ALARM_LVL_INFO,   "Congestion recovered",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12019,
                    "Failed to clear RTB MTP2 buffers",
                    ALARM_LVL_MAJOR,    "Failed to clear RTB MTP2 buffers",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12020,
                    "Trigger from L3 Emergency alignment not success",
                    ALARM_LVL_CRIT,     "Emergency alignment not success",
                    "MTP2", ITS_TRUE); 

ALARM_FORMAT_SUBSYS(MTP2, 12021,
                    "Failed to send data to board",
                    ALARM_LVL_MAJOR,    "Failed to send data to board",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12022,
                    "Excessive periods of Layer 2 Congestion",
                    ALARM_LVL_MAJOR,    "Excessive periods of Layer 2 Congestion",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12023,
                    "----",
                    ALARM_LVL_MAJOR,    "------",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12024,
                    "----",
                    ALARM_LVL_MAJOR,    "------",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12025,
                    "-----",
                    ALARM_LVL_MAJOR,    "------",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12026,
                    "------",
                    ALARM_LVL_MAJOR,    "------",
                    "MTP2", ITS_TRUE);

ALARM_FORMAT_SUBSYS(MTP2, 12027,
                    "--------",
                    ALARM_LVL_MAJOR,    "------",
                    "MTP2", ITS_TRUE);

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
    &ALARM_MTP212027,
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
MTP2_Alarm_NMS(int which, const char *file, const int line,
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
