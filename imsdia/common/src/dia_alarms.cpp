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
 *  ID: $Id: dia_alarms.cpp,v 1.13 2010/08/19 11:26:01 nvijikumar Exp $
 *                                                                          *
 *  LOG: $Log: dia_alarms.cpp,v $
 *  LOG: Revision 1.13  2010/08/19 11:26:01  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 1.12  2009/09/07 04:52:11  rajeshak
 *  LOG: Alarm Added for HMI Heartbeat.
 *  LOG:
 *  LOG: Revision 1.11  2009/08/31 05:54:26  rajeshak
 *  LOG: New Alarm for Connection close after DPA sent/receive (AlarmID:15010).
 *  LOG:
 *  LOG: Revision 1.10  2009/08/28 12:13:59  rajeshak
 *  LOG: Fix for Issue-2341 (IDS is not raising Alarm for DPA/DWA for failed
 *  LOG: result codes)
 *  LOG: Handling of new Alarm codes
 *  LOG:
 *  LOG: Revision 1.9  2009/04/17 08:50:49  rajeshak
 *  LOG: Raising an Alarm if Destination Host is not there in Peer Table.
 *  LOG:
 *  LOG: Revision 1.8  2009/03/19 13:25:52  sureshj
 *  LOG: Version mismatch Alarm added
 *  LOG:
 *  LOG: Revision 1.7  2009/03/19 05:38:31  sureshj
 *  LOG: New Alarms Added.
 *  LOG: 1) Response with result code other than success (15005)
 *  LOG: 2) No match of Origin-Host/Origin-Realm in peer tables (15006).
 *  LOG:
 *  LOG: Revision 1.6  2009/03/16 10:46:16  sureshj
 *  LOG: FeatureId: HMI implementation for diameter.
 *  LOG: Description: New Alarm definition added for HMI detected hung threads.
 *  LOG:
 *  LOG: Revision 1.5  2008/12/23 09:33:46  nvijikumar
 *  LOG: Made Alarm ID 15002 and 15052 as INFO instead of CLEAR
 *  LOG: 15002: Transport connection failure with peer
 *  LOG: 15052: Transport connection success with client application
 *  LOG:
 *  LOG: Revision 1.4  2008/12/15 05:46:25  hbhatnagar
 *  LOG: fix for compilation issue on solaris
 *  LOG:
 *  LOG: Revision 1.3  2008/12/12 07:15:52  chandrabs
 *  LOG: Updated to get proper Alarm Index
 *  LOG:
 *  LOG: Revision 1.2  2008/12/10 06:32:08  nvijikumar
 *  LOG: Changed Alarm reset value to "0" to allow simultaneous occurance of same
 *  LOG: Alarm
 *  LOG:
 *  LOG: Revision 1.1  2008/12/05 11:46:30  nvijikumar
 *  LOG: Initial draft for Alarm support
 *  LOG:
 *  LOG:
 ***************************************************************************/
#ident "$Id: dia_alarms.cpp,v 1.13 2010/08/19 11:26:01 nvijikumar Exp $"

#include <its_assertion.h>

#include <its_alarm.h> 
#include <dia_defines.h> 

ITS_UINT DIA_AlarmLevel = ALARM_LVL_CLEAR;

/* Peer Connection Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15000,
                    "Failed to exchange capabilities with peer",
                    ALARM_LVL_MAJOR, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15001,
                    "Transport connection failure with peer",
                    ALARM_LVL_MAJOR, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15002,
                    "Transport connection successful with peer",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15003,
                    "Failover to alternative peer",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15004,
                    "Failback to original peer",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15005,
                    "Response with result code other than success",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15006,
                    "No match of Origin-Host/Origin-Realm in peer tables",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15007,
                    "Response with result code other than success",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15008,
                    "Response with result code other than success",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15010,
                    "Transport connection closed with peer",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15011,
                    "Peer in closed state",
                    ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE);

/* Backend IDC Connectivity Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15050,
                    "Failed to register client application",
                    ALARM_LVL_MAJOR, "",
                    "IDS", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15051,
                    "Transport connection failure with client application",
                    ALARM_LVL_MAJOR, "",
                    "IDS", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15052,
                    "Transport connection success with client application",
                    ALARM_LVL_INFO, "",
                    "IDS", ITS_TRUE);

/* Message Processing Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15100,
                    "Failed to recieve message from peer",
                    ALARM_LVL_MINOR, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15101,
                    "Failed to transmit message to peer",
                    ALARM_LVL_MINOR, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15102,
                    "Failed to recieve message from client",
                    ALARM_LVL_MINOR, "",
                    "IDS", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15103,
                    "Failed to transmit message to client",
                    ALARM_LVL_MINOR, "",
                    "IDS", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15104,
                    "Failed to Forward message to Peer",
                    ALARM_LVL_MAJOR, "",
                    "STACK", ITS_TRUE);

/* Redundancy Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15150,
                    "Switch over active node failure detected by standby",
                    ALARM_LVL_CRIT, "",
                    "REDUNDANCY", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15151,
                    "GCS communication down",
                    ALARM_LVL_CRIT, "",
                    "REDUNDANCY", ITS_TRUE);

/* Startup / Shutdown Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15200,
                    "Failed to initialize",
                    ALARM_LVL_CRIT, "",
                    "STACK", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15201,
                    "Stack termination event",
                    ALARM_LVL_CRIT, "",
                    "STACK", ITS_TRUE);

/* MML Specific */
ALARM_FORMAT_SUBSYS(DIAMETER, 15250,
                    "Failed to add peer",
                    ALARM_LVL_MAJOR, "", 
                    "MML", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15251,
                    "Disabled / deleted peer",
                    ALARM_LVL_MAJOR, "",
                    "MML", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15252,
                    "Failed to add Destination",
                    ALARM_LVL_MAJOR, "",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(DIAMETER, 15253,
                    "Failed to add Realm",
                    ALARM_LVL_MAJOR, "",
                    "MML", ITS_TRUE);


/* Overload Specific for future relases*/
ALARM_FORMAT_SUBSYS(DIAMETER, 15300,
                    "Disk capacity exceeding threshold",
                    ALARM_LVL_CRIT, "",
                    "OVERLOAD", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15301,
                    "Disk capacity exceeding max capacity",
                    ALARM_LVL_MAJOR, "",
                    "OVERLOAD", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15302,
                    "CPU capacity exceeding threshold",
                    ALARM_LVL_MAJOR, "",
                    "OVERLOAD", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15303,
                    "CPU capacity exceeding max capacity",
                    ALARM_LVL_CRIT, "",
                    "OVERLOAD", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15304,
                    "Queue size exceeding threshold",
                    ALARM_LVL_CRIT, "",
                    "OVERLOAD", ITS_TRUE);
ALARM_FORMAT_SUBSYS(DIAMETER, 15305,
                    "Queue size reaching max capacity",
                    ALARM_LVL_MAJOR, "",
                    "OVERLOAD", ITS_TRUE);

ALARM_FORMAT_SUBSYS(DIAMETER, 15350,
                    "HMI detected a hung Thread",
                    ALARM_LVL_CRIT, "",
                    "STACK", ITS_TRUE);

/* Genearal Alarms */
ALARM_FORMAT_SUBSYS(DIAMETER, 15400,
                    "Version Mismatch",
                    ALARM_LVL_MINOR, "",
                    "STACK", ITS_TRUE);

/* HMI Heartbeat Alarms */
ALARM_FORMAT_SUBSYS(DIAMETER, 15450,
                    "HMI Heartbeat Msg",
                     ALARM_LVL_INFO, "",
                    "STACK", ITS_TRUE); 

ALARM_Format *DIA_Alarms[] =
{
    &ALARM_DIAMETER15000,
    &ALARM_DIAMETER15001,
    &ALARM_DIAMETER15002,
    &ALARM_DIAMETER15003,
    &ALARM_DIAMETER15004,
    &ALARM_DIAMETER15005,
    &ALARM_DIAMETER15006,
    &ALARM_DIAMETER15007,
    &ALARM_DIAMETER15008,
    &ALARM_DIAMETER15010,
    &ALARM_DIAMETER15011,
    &ALARM_DIAMETER15050,
    &ALARM_DIAMETER15051,
    &ALARM_DIAMETER15052,
    &ALARM_DIAMETER15100,
    &ALARM_DIAMETER15101,
    &ALARM_DIAMETER15102,
    &ALARM_DIAMETER15103,
    &ALARM_DIAMETER15104,
    &ALARM_DIAMETER15150,
    &ALARM_DIAMETER15151,
    &ALARM_DIAMETER15200,
    &ALARM_DIAMETER15201,
    &ALARM_DIAMETER15250,
    &ALARM_DIAMETER15251,
    &ALARM_DIAMETER15252,
    &ALARM_DIAMETER15253,
    &ALARM_DIAMETER15300,
    &ALARM_DIAMETER15301,
    &ALARM_DIAMETER15302,
    &ALARM_DIAMETER15303,
    &ALARM_DIAMETER15304,
    &ALARM_DIAMETER15305,
    &ALARM_DIAMETER15350,
    &ALARM_DIAMETER15400,
    &ALARM_DIAMETER15450
};

#define DIA_GET_ALARM_INDEX(x) \
    ((x==15000)                       ? 0                      : \
    ((x==15001)                       ? 1                      : \
    ((x==15002)                       ? 2                      : \
    ((x==15003)                       ? 3                      : \
    ((x==15004)                       ? 4                      : \
    ((x==15005)                       ? 5                      : \
    ((x==15006)                       ? 6                      : \
    ((x==15007)                       ? 7                      : \
    ((x==15008)                       ? 8                      : \
    ((x==15010)                       ? 9                      : \
    ((x==15011)                       ? 10                      : \
    ((x==15050)                       ? 11                     : \
    ((x==15051)                       ? 12                     : \
    ((x==15052)                       ? 13                     : \
    ((x==15100)                       ? 14                     : \
    ((x==15101)                       ? 15                     : \
    ((x==15102)                       ? 16                     : \
    ((x==15103)                       ? 17                     : \
    ((x==15104)                       ? 18                     : \
    ((x==15150)                       ? 19                     : \
    ((x==15151)                       ? 20                     : \
    ((x==15200)                       ? 21                     : \
    ((x==15201)                       ? 22                     : \
    ((x==15250)                       ? 23                     : \
    ((x==15251)                       ? 24                     : \
    ((x==15252)                       ? 25                     : \
    ((x==15253)                       ? 26                     : \
    ((x==15300)                       ? 27                     : \
    ((x==15301)                       ? 28                     : \
    ((x==15302)                       ? 29                     : \
    ((x==15303)                       ? 30                     : \
    ((x==15304)                       ? 31                     : \
    ((x==15305)                       ? 32                     : \
    ((x==15350)                       ? 33                     : \
    ((x==15400)                       ? 34                     : \
    ((x==15450)                       ? 35                     : \
    -1))))))))))))))))))))))))))))))))))))

/****************************************************************************
 *  Purpose:
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
 *    None.
 *
 *  Revision History:
 *  ------------------------------------------------------------------------
 *  Name     Date         Reference                 Description
 *  ------------------------------------------------------------------------
 *
 ****************************************************************************/

void
DIA_Alarm(int which, const char *file, const int line,
          const char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;
    ITS_INT tIndex = 0;

    ITS_C_ASSERT(which >= DIA_ALARM_START &&
                 which <= DIA_ALARM_END);

    if (DIA_AlarmLevel == ALARM_LVL_OFF)
    {
        return;
    }

    tIndex = DIA_GET_ALARM_INDEX(which);
    if (tIndex == -1)
    {
        return;
    }

    fmt = DIA_Alarms[tIndex];

    /* 
     * Allow simultaneous instantiate of same Alarms 
     * Note: If simultaneous occurence not required comment below statement
     */
    fmt->reset = 0;

    if (fmt->severity > DIA_AlarmLevel)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}

