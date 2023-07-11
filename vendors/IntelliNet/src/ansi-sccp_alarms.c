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
 *  ID:$Id: ansi-sccp_alarms.c,v 9.2 2008/06/04 10:30:24 ssingh Exp $
 *
 * LOG: $Log: ansi-sccp_alarms.c,v $
 * LOG: Revision 9.2  2008/06/04 10:30:24  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.1.10.1  2007/05/18 09:48:32  raghavendrabk
 * LOG: Changes in Alarm Subsystem Format
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.3  2005/02/21 09:00:30  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.2  2005/01/04 16:06:11  snagesh
 * LOG: Changed default alarm level to OFF
 * LOG:
 * LOG: Revision 7.3.2.1.4.3.6.1  2004/12/29 13:29:41  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.3.2.1.4.3  2004/09/02 11:55:54  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.3.2.1.4.2  2004/08/27 09:38:47  csireesh
 * LOG: Changes in Alarm Description
 * LOG:
 * LOG: Revision 7.3.2.1.4.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/08/27 14:15:25  hcho
 * LOG: Added alarm number not present in the alarm list.
 * LOG:
 * LOG: Revision 7.3  2003/02/03 07:00:39  aganguly
 * LOG: Changes for SCCP Alarms- Clean up of unwanted alarms still to be done in Release 6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.5  2002/03/20 23:30:17  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.4  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.3  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 20:32:03  mmiers
 * LOG: These build now.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 23:28:43  mmiers
 * LOG: Add alarms.  Pegs here are going to be short-lived.
 * LOG:
 *
 ****************************************************************************/

#include <its_assertion.h>

#include "ss7_alarms.h"

ITS_UINT SCCP_AlarmLevel_ANSI = ALARM_LVL_OFF;


/*Intermediate alarms removed between 01 to 15 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 16,
                    "SCCP failed to Intialize -",
                    ALARM_LVL_CRIT,         "Initialize",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 17 to 21 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 22,
                    "SCCP Initialized Successfully",
                    ALARM_LVL_INFO,         "Initialize",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 23,
                    "SCCP Terminating",
                    ALARM_LVL_CRIT,         "Terminate",
                    "SCCP", ITS_TRUE);
 
/*Intermediate alarms removed between 24 to 26 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 27,
                    "ANSI SCCP License not found.",
                    ALARM_LVL_CRIT,         "EncodeMTP3",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 28,
                    "User Out of Service (UOS) Message from application:",
                    ALARM_LVL_INFO,         "SendUserOutOfService",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 29,
                    "User In Service (UIS) Message from application:",
                    ALARM_LVL_INFO,         "SendUserInService",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 30,
                    "User Congested Message from application:",
                    ALARM_LVL_INFO,         "SendSetCongestion",
                    "SCCP", ITS_FALSE);

 /*Intermediate alarms removed between 31 to 35 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 36,
                    "Signaling Point Accessible MTP3-RESUME received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 37,
                    "Signaling Point Inaccessible MTP3-PAUSE received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 38,
                    "Signaling Point Congested MTP3-STATUS received for remote node:",
                    ALARM_LVL_INFO,         "SCMGHandleMTP3Msg_ANSI",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 39,
                    "Malformed MTP3 management message received",
                    ALARM_LVL_MINOR,         "SCMGHandleMTP3Msg_ANSI",
                    "SCCP", ITS_FALSE);

 /*Intermediate alarms removed between 40 to 42 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 43,
                    "Subsystem Allowed(SSA) message received from remote subsystem:",
                    ALARM_LVL_INFO,         "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 44,
                    "Subsystem Prohibted(SSP) message received from remote subsystem:",
                    ALARM_LVL_MAJOR,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 45,
                    "Subsystem Congested(SSC) message received from remote subsystem:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 46,
                    "Subsystem Allowed(SSA) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 47,
                    "Subsystem Prohibted(SSP) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 48,
                    "Subsystem Congested(SSC) message received",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 49,
                    "Unknown SCMG message received from remote:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 50,
                    "Malformed SCMG message received from remote",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 51,
                    "User In Service (UIS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 52,
                    "User Out Of Service (UOS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 53,
                    "User Out Of Service message received from remote:",
                    ALARM_LVL_MINOR,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 54,
                    "User In Service message received from remote:",
                    ALARM_LVL_INFO,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 55,
                    "Subsystem status Changed to Allowed:",
                    ALARM_LVL_INFO,       "SCMGHandleSSTTimeout",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 56,
                    "Subsystem status changed to Prohibited:",
                    ALARM_LVL_INFO,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 57 to 99 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 100,
                    "SCCP Remote Subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 101,
                    "SCCP Remote Subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "SCCP", ITS_TRUE);
#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 102,
                    "SCCP Remote Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 103,
                    "SCCP Remote Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 104,
                    "SCCP Concerned Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 105,
                    "SCCP Concerned Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "MML", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 106,
                    "SCCP Concerned subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 107,
                    "SCCP Concerned subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_ANSI",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 108 to 231; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 232,
                    "Message for unknown Destination- No Route to remote:",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 233,
                    "Discarding Message from Application- Missing Routing Information.",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 234,
                    "Unknown message type received form application ",
                    ALARM_LVL_MAJOR,       "SCOCHandleAPPMsg_ANSI",
                    "SCCP", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 235,
                    "SCCP-CL Message from application- unknown message type ",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_ANSI",
                    "Routing ", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 236,
                    "Unknown message type received from remote ",
                    ALARM_LVL_MAJOR,       "SCOCHandleTimer_ANSI",
                    "Routing ", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(ANSI_SCCP, 237,
                    "SCCP-CL Message from remote- unknown .",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg",
                    "Routing", ITS_TRUE);
#endif

 /*Intermediate alarms removed between 238 to 242 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 243,
                    "Message received from remote for unavailable subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverMTP3Ind",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 244,
                    "Discarding Message - No SSN in Called Party Address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverLocal",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 245,
                    "SCCP Routing:Global Title Translation failed.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 246,
                    "GTT: Error in translated address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 247,
                    "Discarding message - Called party address absent in SCCP message received from remote.",
                    ALARM_LVL_MINOR,       "SCRCHandleMTP3Msg_ANSI",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 248,
                    "Message for inaccessible remote subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverRemote",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 249 to 255 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 256,
                    "CC received from remote end  in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownCC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 257,
                    "CREF  received from remote end  in invalid state ",
                    ALARM_LVL_MINOR,       "HandleDownCREF",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 258,
                    "RLSD received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownRLSD",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 259,
                    "RLC received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownRLC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,260,
                    "DT1 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 261,
                    "DT1 received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 262,
                    "DT2 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 263,
                    "DT2 received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 264,
                    "AK received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 265,
                   "AK received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP, 266,
                    "ED received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,267,
                    "ED received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,268, 
                    "EA received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,269,
                    "EA received from remote end in invalid state.",
                    ALARM_LVL_MINOR,        "HandleDownEA",
                    "Subsystem", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,270,
                    "UDT received from remote with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "SCRCHandleMTP3Msg",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,271,
                    "RSR received from application with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "HandleAppRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,272,
                    "DT1 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,273,
                    "DT1 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,274,
                    "DT2 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,275,
                    "DT2 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,276,
                    "AK received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,277,
                    "AK received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,278,
                    "ED received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,279,
                    "EA received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,280,
                    "ED received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,281,
                    "EA received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,282,
                    "RSR received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,283,
                    "RSC received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,284,
                    "RSC received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,285,
                    "CR received from remote with invalid Protocol Class ",
                    ALARM_LVL_MAJOR,       "HandleDownCR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(ANSI_SCCP,286,
                    "CR received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppCR",
                    "SCCP-CO", ITS_TRUE);

 /* Alarms removed between 287 to 382 ; not used in PR 6.4.1 */


ALARM_Format *ANSI_SCCP_Alarms[] =
{
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //10
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP16,
        NULL,
        NULL,
        NULL,
        NULL, //20
        NULL,
        &ALARM_ANSI_SCCP22,
        &ALARM_ANSI_SCCP23,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP27,
        &ALARM_ANSI_SCCP28,
        &ALARM_ANSI_SCCP29,
        &ALARM_ANSI_SCCP30,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP36,
        &ALARM_ANSI_SCCP37,
        &ALARM_ANSI_SCCP38,
        &ALARM_ANSI_SCCP39,
        NULL, //40
        NULL,
        NULL,
        &ALARM_ANSI_SCCP43,
        &ALARM_ANSI_SCCP44,
        &ALARM_ANSI_SCCP45,
        &ALARM_ANSI_SCCP46,
        &ALARM_ANSI_SCCP47,
        &ALARM_ANSI_SCCP48,
        &ALARM_ANSI_SCCP49,
        &ALARM_ANSI_SCCP50,
        &ALARM_ANSI_SCCP51,
        &ALARM_ANSI_SCCP52,
        &ALARM_ANSI_SCCP53,
        &ALARM_ANSI_SCCP54,
        &ALARM_ANSI_SCCP55,
        &ALARM_ANSI_SCCP56,
        NULL,
        NULL,
        NULL,
        NULL, //60
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //70
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //80
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //90
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP100,
        &ALARM_ANSI_SCCP101,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP106,
        &ALARM_ANSI_SCCP107,
        NULL,
        NULL,
        NULL, //110
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //115
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //120
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //130
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //140
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //150
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //160
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //170
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //180
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //190
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //200
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //210
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //220
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //230
        NULL,
        &ALARM_ANSI_SCCP232,
        &ALARM_ANSI_SCCP233,
        &ALARM_ANSI_SCCP234,
        NULL,
        &ALARM_ANSI_SCCP236,
        NULL,
        NULL,
        NULL,
        NULL, //240
        NULL,
        NULL,
        &ALARM_ANSI_SCCP243,
        &ALARM_ANSI_SCCP244,
        &ALARM_ANSI_SCCP245,
        &ALARM_ANSI_SCCP246,
        &ALARM_ANSI_SCCP247,
        &ALARM_ANSI_SCCP248,
        NULL,
        NULL, //250
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_ANSI_SCCP256,
        &ALARM_ANSI_SCCP257,
        &ALARM_ANSI_SCCP258,
        &ALARM_ANSI_SCCP259,
        &ALARM_ANSI_SCCP260,
        &ALARM_ANSI_SCCP261,
        &ALARM_ANSI_SCCP262,
        &ALARM_ANSI_SCCP263,
        &ALARM_ANSI_SCCP264,
        &ALARM_ANSI_SCCP265,
        &ALARM_ANSI_SCCP266,
        &ALARM_ANSI_SCCP267,
        &ALARM_ANSI_SCCP268,
        &ALARM_ANSI_SCCP269,
        &ALARM_ANSI_SCCP270,
        &ALARM_ANSI_SCCP271,
        &ALARM_ANSI_SCCP272,
        &ALARM_ANSI_SCCP273,
        &ALARM_ANSI_SCCP274,
        &ALARM_ANSI_SCCP275,
        &ALARM_ANSI_SCCP276,
        &ALARM_ANSI_SCCP277,
        &ALARM_ANSI_SCCP278,
        &ALARM_ANSI_SCCP279,
        &ALARM_ANSI_SCCP280,
        &ALARM_ANSI_SCCP281,
        &ALARM_ANSI_SCCP282,
        &ALARM_ANSI_SCCP283,
        &ALARM_ANSI_SCCP284,
        &ALARM_ANSI_SCCP285,
        &ALARM_ANSI_SCCP286,
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method issues a SCCP alarm.
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
SCCP_Alarm_ANSI(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= ANSI_SCCP_ALARM_START &&
                 which <= ANSI_SCCP_ALARM_END);

    fmt = ANSI_SCCP_Alarms[which - ANSI_SCCP_ALARM_START];
    if (fmt  != NULL)
    {
        if (fmt->severity > SCCP_AlarmLevel_ANSI)
        {
            return;
        }
    }
    else
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}
