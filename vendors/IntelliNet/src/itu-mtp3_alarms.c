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
 *  ID:$Id: itu-mtp3_alarms.c,v 9.3 2007/01/11 12:43:37 yranade Exp $
 *
 * LOG: $Log: itu-mtp3_alarms.c,v $
 * LOG: Revision 9.3  2007/01/11 12:43:37  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2.8.1  2006/08/18 12:31:15  mshanmugam
 * LOG: Added new Alarm Object for OAM feature.
 * LOG:
 * LOG: Revision 9.2  2005/04/07 09:10:30  snagesh
 * LOG: Modifications for LPO Feature
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:45  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2.8.1.8.2  2005/01/25 11:38:02  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420 and other alarm text changes
 * LOG:
 * LOG: Revision 7.4.2.2.8.1.8.1  2004/12/31 07:26:26  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.2.8.1  2004/08/10 12:14:46  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/02/21 01:42:34  randresol
 * LOG: Add more alarms
 * LOG:
 * LOG: Revision 7.4.2.1  2003/02/18 02:35:01  randresol
 * LOG: Issue "Out of Service" alarm when a link goes down
 * LOG:
 * LOG: Revision 7.4  2003/02/13 10:36:56  ttipatre
 * LOG: New Alarms added.
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.2  2002/11/20 05:18:19  ttipatre
 * LOG: Modified to protocol specific alarms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/06/13 20:34:12  ttipatre
 * LOG: Adding MTP3 Alarms Formats
 * LOG:
 * LOG: Revision 6.3  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.2  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.1  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT MTP3_AlarmLevel_CCITT = ALARM_LVL_OFF;

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2401,
                    "Destination Unavailable - Received MTP3-PAUSE:",
                    ALARM_LVL_MAJOR,         "MTP3_Pause",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2402,
                    "Destination Available - Received MTP3-RESUME:",
                    ALARM_LVL_INFO,        "MTP3_Pause",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2403,
                    "Remote Processor Outage:",
                    ALARM_LVL_MAJOR,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2404,
                    "Remote Processor Recovered:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2405,
                    "Failed to receive L2 data ",
                    ALARM_LVL_MAJOR,         "MTP3Thread",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2406,
                    "Unknown msg type",
                     ALARM_LVL_MAJOR, "SMH_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2407,
                    "Error in processing L2 data",
                    ALARM_LVL_MAJOR,         "HMDC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2408,
                    "Failed to route L2 message,",
                    ALARM_LVL_MAJOR,         "HMDC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2411,
                    "Cannot send Outbound message - no route to destination:",
                    ALARM_LVL_MINOR,        "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2412,
                    "Cannot send Outbound message - Destination Unavailable:",
                    ALARM_LVL_MINOR,         "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2413,
                    "Cannot send Outbound message - Destination Restricted",
                    ALARM_LVL_MINOR,         "MessageForRouting",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2414,
                    "Destination Inaccessible for Link Management msg",
                    ALARM_LVL_MINOR,         "LinkManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2415,
                    "Destination Inaccessible for Traffic Management msg:",
                    ALARM_LVL_MINOR,         "TrafficManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2416,
                    "Destination Inaccessible for Test Control msg:",
                    ALARM_LVL_MINOR,         "TestControlMessage",
                    "Route", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2419,
                    "No route to destination",
                    ALARM_LVL_MINOR,        "HMCG_Main",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2420,
                    "Failed to send L2 data",
                    ALARM_LVL_MINOR,         "MTP2_SendData",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2423,
                    "Activate LinkSet failed:",
                    ALARM_LVL_CRIT,         "LLSC_Main",
                    "Linkset", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2434,
                    "Link Terminal state is not ideal",
                    ALARM_LVL_MAJOR,         "LSTA_Main",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2439,
                    "Link Allocation State not ideal",
                    ALARM_LVL_MAJOR,         "LSDA_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2440,
                    "Can't find adjacent node for connection order.",
                    ALARM_LVL_CRIT,         "LSDA_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2448,
                    "TFP discarded:not adjacent to point code ",
                    ALARM_LVL_MAJOR,         "RTPC_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2451,
                    "TFA discarded:not adjacent to point code ",
                    ALARM_LVL_MAJOR,         "RTAC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2456,
                    "RouteSet Test not performed:not adjacent to point code ",
                    ALARM_LVL_MAJOR,         "RSRT_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2459,
                    "TFR discarded:not adjacent to point code ",
                    ALARM_LVL_MAJOR,         "RTRC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2466,
                    "No alternate route for linkSet ",
                    ALARM_LVL_MAJOR,         "FindAlternateRoute",
                    "Linkset", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2471,
                    "Inhibit Link Trigger:",
                    ALARM_LVL_MAJOR,         "TLAC_Main",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2477,
                    "TFC: No data for destination:",
                    ALARM_LVL_MINOR,         "TRCC_Main",
                    "Route", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2482,
                    "COA: No data for destination:",
                    ALARM_LVL_MINOR,         "TCOC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2487,
                    "Unexpected state for Changeback",
                    ALARM_LVL_MINOR,         "GetAlternateRoute",
                    "Link", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2489,
                    "Route Unavailable:no data for destination:",
                    ALARM_LVL_MINOR,         "TFRC_Main",
                    "MTP3", ITS_TRUE);


ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2501,
                    "Failed to Route L2 message to User Part:",
                    ALARM_LVL_MAJOR,         "HMDT_Main",
                    "MTP3", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2502,
                    "Failed to Route Link Management Message:",
                    ALARM_LVL_MAJOR,         "LinkManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2503,
                    "Failed to Route Traffic Management Message:",
                    ALARM_LVL_MAJOR,         "TrafficManagementMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2504,
                    "Failed to Route Test Control Message:",
                    ALARM_LVL_MAJOR,         "TestControlMessage",
                    "Route", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2505,
                    "Start Link Alignment:",
                    ALARM_LVL_INFO,         "LSAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2506,
                    "Link Alignment Timer T17 Expired:",
                    ALARM_LVL_INFO,         "LSAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2507,
                    "SLT-First Attempt Failed:",
                    ALARM_LVL_MINOR,         "SLTC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2508,
                    "SLT-Second Attempt Failed:",
                    ALARM_LVL_MINOR,         "SLTC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2509,
                    "Link Out of Service:",
                    ALARM_LVL_MINOR,         "LSLD_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2510,
                    "COO Received:",
                    ALARM_LVL_MINOR,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2511,
                    "CBD Received:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2512,
                    "ECO Received:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2513,
                    "COO Transmitted:",
                    ALARM_LVL_MINOR,         "TCOC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2514,
                    "CBD Transmitted:",
                    ALARM_LVL_INFO,         "TCBC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2515,
                    "ECO Transmitted:",
                    ALARM_LVL_INFO,         "TCOC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2516,
                    "Remote Inhibit Requested:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2517,
                    "Local Inhibit Requested:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2518,
                    "Local Inhibiting Link:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2519,
                    "UnInhibiting Link:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2520,
                    "Local Inhibit Denied:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2521,
                    "Remote Inhibit Denied",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2522,
                    "Local Inhibit Test:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2523,
                    "Remote Inhibit Test:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2524,
                    "Remote Processor Outage",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2525,
                    "Remote Processor Recovered",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2526,
                    "Link In-Service:",
                    ALARM_LVL_INFO,         "TLAC_Main",
                    "Link", ITS_FALSE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2527,
                    "Layer 2 In-Service",
                    ALARM_LVL_INFO,         "SLM_Main",
                    "Link", ITS_TRUE);

ALARM_FORMAT_SUBSYS(CCITT_MTP3, 2528,
                    "Start SLT:",
                    ALARM_LVL_INFO,         "SLM_Main",
                    "Link", ITS_FALSE);


ALARM_Format *CCITT_MTP3_Alarms[] =
{
    &ALARM_CCITT_MTP32401,
    &ALARM_CCITT_MTP32402,
    &ALARM_CCITT_MTP32403,
    &ALARM_CCITT_MTP32404,
    &ALARM_CCITT_MTP32405,
    &ALARM_CCITT_MTP32406,
    &ALARM_CCITT_MTP32407,
    &ALARM_CCITT_MTP32408,
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32411,
    &ALARM_CCITT_MTP32412,
    &ALARM_CCITT_MTP32413,
    &ALARM_CCITT_MTP32414,
    &ALARM_CCITT_MTP32415,
    &ALARM_CCITT_MTP32416,
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32419,
    &ALARM_CCITT_MTP32420,
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32423,
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
    &ALARM_CCITT_MTP32434,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32439,
    &ALARM_CCITT_MTP32440,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32448,
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32451,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32456,
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32459,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32466,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32471,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32477,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32482,
    NULL, 
    NULL, 
    NULL, 
    NULL, 
    &ALARM_CCITT_MTP32487,
    NULL, 
    &ALARM_CCITT_MTP32489,
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
    &ALARM_CCITT_MTP32501,
    &ALARM_CCITT_MTP32502,
    &ALARM_CCITT_MTP32503,
    &ALARM_CCITT_MTP32504,
    &ALARM_CCITT_MTP32505,
    &ALARM_CCITT_MTP32506,
    &ALARM_CCITT_MTP32507,
    &ALARM_CCITT_MTP32508,
    &ALARM_CCITT_MTP32509,
    &ALARM_CCITT_MTP32510,
    &ALARM_CCITT_MTP32511,
    &ALARM_CCITT_MTP32512,
    &ALARM_CCITT_MTP32513,
    &ALARM_CCITT_MTP32514,
    &ALARM_CCITT_MTP32515,
    &ALARM_CCITT_MTP32516,
    &ALARM_CCITT_MTP32517,
    &ALARM_CCITT_MTP32518,
    &ALARM_CCITT_MTP32519,
    &ALARM_CCITT_MTP32520,
    &ALARM_CCITT_MTP32521,
    &ALARM_CCITT_MTP32522,
    &ALARM_CCITT_MTP32523,
    &ALARM_CCITT_MTP32524,
    &ALARM_CCITT_MTP32525,
    &ALARM_CCITT_MTP32526,
    &ALARM_CCITT_MTP32527,
    &ALARM_CCITT_MTP32528

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
MTP3_Alarm_CCITT(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= CCITT_MTP3_ALARM_START &&
                 which <= CCITT_MTP3_ALARM_END);

    fmt = CCITT_MTP3_Alarms[which - CCITT_MTP3_ALARM_START];

    if (fmt->severity > MTP3_AlarmLevel_CCITT)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
