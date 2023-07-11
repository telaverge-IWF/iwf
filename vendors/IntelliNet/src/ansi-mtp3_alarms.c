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
 *  ID:$Id: ansi-mtp3_alarms.c,v 9.3 2008/06/04 10:30:24 ssingh Exp $
 *
 * LOG: $Log: ansi-mtp3_alarms.c,v $
 * LOG: Revision 9.3  2008/06/04 10:30:24  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.2.8.1  2007/05/11 10:40:10  raghavendrabk
 * LOG: Subsystem name chaged for ANSI Alarms
 * LOG:
 * LOG: Revision 9.2  2005/04/07 09:10:29  snagesh
 * LOG: Modifications for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.2.8.4.8.3  2005/01/25 11:38:02  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420 and other alarm text changes
 * LOG:
 * LOG: Revision 7.5.2.2.8.4.8.2  2005/01/04 16:06:11  snagesh
 * LOG: Changed default alarm level to OFF
 * LOG:
 * LOG: Revision 7.5.2.2.8.4.8.1  2004/12/31 06:44:19  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.2.8.4  2004/09/03 11:06:54  sswami
 * LOG: Changed text for 2119 Alert to Local uninhibit
 * LOG:
 * LOG: Revision 7.5.2.2.8.3  2004/09/03 09:55:40  sswami
 * LOG: Fix given for changing the alarm level from CLEAR to INFO for 2126 & 2128
 * LOG:
 * LOG: Revision 7.5.2.2.8.2  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.5.2.2.8.1  2004/08/06 06:43:46  sswami
 * LOG: SMLC lb-GW Alarm/Alert related changes
 * LOG:
 * LOG: Revision 7.5.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/18 02:35:01  randresol
 * LOG: Issue "Out of Service" alarm when a link goes down
 * LOG:
 * LOG: Revision 7.5  2003/02/13 10:22:04  ttipatre
 * LOG: New alarms are added
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.3  2002/12/24 07:38:39  ttipatre
 * LOG: Minor comment change.
 * LOG:
 * LOG: Revision 7.2  2002/11/20 05:07:42  ttipatre
 * LOG: Alarms code submission.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.2  2002/03/20 23:30:17  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.1  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT MTP3_AlarmLevel_ANSI = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2001,
                    "Destination Unavailable - Received MTP3-PAUSE:",
                    ALARM_LVL_MAJOR,         "MTP3_Pause",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2002,
                    "Destination Available - Received MTP3-RESUME:",
                    ALARM_LVL_INFO,        "MTP3_Pause",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2003,
                    "Remote Processor Outage:",
                    ALARM_LVL_MAJOR,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2004,
                    "Remote Processor Recovered:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2005,
                    "Failed to receive L2 data ",
                    ALARM_LVL_MAJOR,         "MTP3Thread",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2006,
                    "Unknown msg type",
                     ALARM_LVL_MAJOR, "SMH_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2007,
                    "Error in processing L2 data",
                    ALARM_LVL_MAJOR,         "HMDC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2008,
                    "Failed to route L2 message, ",
                    ALARM_LVL_MAJOR,         "HMDC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2011,
                    "Cannot send Outbound message - no route to destination:",
                    ALARM_LVL_MINOR,        "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2012,
                    "Cannot send Outbound message - Destination Unavailable:",
                    ALARM_LVL_MINOR,         "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2013,
                    "Cannot send Outbound message - Destination Restricted",
                    ALARM_LVL_MINOR,         "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2014,
                    "Destination Inaccessible for Link Management msg",
                    ALARM_LVL_MINOR,         "LinkManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2015,
                    "Destination Inaccessible for Traffic Management msg:",
                    ALARM_LVL_MINOR,         "TrafficManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2016,
                    "Destination Inaccessible for Test Control msg:",
                    ALARM_LVL_MINOR,         "TestControlMessage",
                    "Route", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2019,
                    "No route to destination",
                    ALARM_LVL_MINOR,        "HMCG_Main",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2020,
                    "Failed to send L2 data",
                    ALARM_LVL_MAJOR,         "MTP2_SendData",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2023,
                    "Activate LinkSet failed:",
                    ALARM_LVL_CRIT,         "LLSC_Main",
                    "Linkset", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2034,
                    "Link Terminal state is not ideal",
                    ALARM_LVL_MAJOR,         "LSTA_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2039,
                    "Link Allocation State not ideal",
                    ALARM_LVL_MAJOR,         "LSDA_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2040,
                    "Can't find adjacent node for connection order.",
                    ALARM_LVL_MAJOR,         "LSDA_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2048,
                    "TFP discarded:not adjacent to point code",
                    ALARM_LVL_MAJOR,         "RTPC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2051,
                    "TFA discarded:not adjacent to point code ",
                    ALARM_LVL_MAJOR,         "RTAC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2056,
                    "RouteSet Test not performed:not adjacent to point code",
                    ALARM_LVL_MAJOR,         "RSRT_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2059,
                    "TFR discarded:not adjecent to point code ",
                    ALARM_LVL_MAJOR,         "RTRC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2066,
                    "No alternate route for linkSet ",
                    ALARM_LVL_MAJOR,         "FindAlternateRoute",
                    "Linkset", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2071,
                    "Inhibit Link Trigger:",
                    ALARM_LVL_MAJOR,         "TLAC_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2077,
                    "TFC: No data for destination:",
                    ALARM_LVL_MINOR,         "TRCC_Main",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2082,
                    "COA: No data for destination:",
                    ALARM_LVL_MINOR,         "TCOC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2087,
                    "Unexpected state for Changeback",
                    ALARM_LVL_MINOR,         "GetAlternateRoute",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2089,
                    "Route Unavailable:no data for destination:",
                    ALARM_LVL_MINOR,         "TFRC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2101,
                    "Failed to Route L2 message to User Part",
                    ALARM_LVL_MAJOR,         "HMDT_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2102,
                    "Failed to Route Link Management Message",
                    ALARM_LVL_MAJOR,         "LinkManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2103,
                    "Failed to Route Traffic Management Message:",
                    ALARM_LVL_MAJOR,         "TrafficManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2104,
                    "Failed to Route Test Control Message:",
                    ALARM_LVL_MAJOR,         "TestControlMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2105,
                    "Start Link Alignment:",
                    ALARM_LVL_INFO,         "LSAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2106,
                    "Link Alignment Timer T17 Expired:",
                    ALARM_LVL_INFO,         "LSAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2107,
                    "SLT-First Attempt Failed:",
                    ALARM_LVL_MINOR,         "SLTC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2108,
                    "SLT-Second Attempt Failed:",
                    ALARM_LVL_MINOR,         "SLTC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2109,
                    "Link Out of Service:",
                    ALARM_LVL_MINOR,         "LSLD_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2110,
                    "COO Received:",
                    ALARM_LVL_MINOR,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2111,
                    "CBD Received:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2112,
                    "ECO Received:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2113,
                    "COO Transmitted:",
                    ALARM_LVL_MINOR,         "TCOC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2114,
                    "CBD Transmitted:",
                    ALARM_LVL_INFO,         "TCBC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2115,
                    "ECO Transmitted:",
                    ALARM_LVL_INFO,         "TCOC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2116,
                    "Remote Inhibit Requested:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2117,
                    "Local Inhibit Requested:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2118,
                    "Local Inhibiting Link:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2119,
                    "Local UnInhibiting Link:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2120,
                    "Local Inhibit Denied:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2121,
                    "Remote Inhibit Denied:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2122,
                    "Local Inhibit Test:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2123,
                    "Remote Inhibit Test:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2124,
                    "Remote Processor Outage",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2125,
                    "Remote Processor Recovered",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2126,
                    "Link In-Service:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2127,
                    "Layer 2 In-Service",
                    ALARM_LVL_INFO,         "SLM_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_MTP3, 2128,
                    "Start SLT:",
                    ALARM_LVL_INFO,         "SLM_Main",
                    "Link", ITS_FALSE);


ALARM_Format *ANSI_MTP3_Alarms[] =
{
    &ALARM_ANSI_MTP32001,
    &ALARM_ANSI_MTP32002,
    &ALARM_ANSI_MTP32003,
    &ALARM_ANSI_MTP32004,
    &ALARM_ANSI_MTP32005,
    &ALARM_ANSI_MTP32006,
    &ALARM_ANSI_MTP32007,
    &ALARM_ANSI_MTP32008,
    NULL,    
    NULL, 
    &ALARM_ANSI_MTP32011,
    &ALARM_ANSI_MTP32012,
    &ALARM_ANSI_MTP32013,
    &ALARM_ANSI_MTP32014,
    &ALARM_ANSI_MTP32015,
    &ALARM_ANSI_MTP32016,
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32019,
    &ALARM_ANSI_MTP32020,
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32023,
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
    &ALARM_ANSI_MTP32034,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32039,
    &ALARM_ANSI_MTP32040,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32048,
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32051,
    NULL, 
    NULL, 
    NULL,
    NULL, 
    &ALARM_ANSI_MTP32056,
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32059,
    NULL, 
    NULL, 
    NULL,
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32066,
    NULL,  
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32071,
    NULL, 
    NULL, 
    NULL,
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32077,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32082,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_ANSI_MTP32087,
    NULL, 
    &ALARM_ANSI_MTP32089,
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
    &ALARM_ANSI_MTP32101,
    &ALARM_ANSI_MTP32102,
    &ALARM_ANSI_MTP32103,
    &ALARM_ANSI_MTP32104,
    &ALARM_ANSI_MTP32105,
    &ALARM_ANSI_MTP32106,
    &ALARM_ANSI_MTP32107,
    &ALARM_ANSI_MTP32108,
    &ALARM_ANSI_MTP32109,
    &ALARM_ANSI_MTP32110,
    &ALARM_ANSI_MTP32111,
    &ALARM_ANSI_MTP32112,
    &ALARM_ANSI_MTP32113,
    &ALARM_ANSI_MTP32114,
    &ALARM_ANSI_MTP32115,
    &ALARM_ANSI_MTP32116,
    &ALARM_ANSI_MTP32117,
    &ALARM_ANSI_MTP32118,
    &ALARM_ANSI_MTP32119,
    &ALARM_ANSI_MTP32120,
    &ALARM_ANSI_MTP32121,
    &ALARM_ANSI_MTP32122,
    &ALARM_ANSI_MTP32123,
    &ALARM_ANSI_MTP32124,
    &ALARM_ANSI_MTP32125,
    &ALARM_ANSI_MTP32126,
    &ALARM_ANSI_MTP32127,
    &ALARM_ANSI_MTP32128

};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a MTP3 alarm.
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
MTP3_Alarm_ANSI(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= ANSI_MTP3_ALARM_START &&
                 which <= ANSI_MTP3_ALARM_END);

    fmt = ANSI_MTP3_Alarms[which - ANSI_MTP3_ALARM_START];

    if (fmt->severity > MTP3_AlarmLevel_ANSI)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
