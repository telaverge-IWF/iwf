/****************************************************************************

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
 *  ID:$Id: prc-sccp_alarms.c,v 1.2 2007/02/01 13:26:38 yranade Exp $
 * 
 * LOG: $Log: prc-sccp_alarms.c,v $
 * LOG: Revision 1.2  2007/02/01 13:26:38  yranade
 * LOG: Add prc files
 * LOG:
 * LOG: Revision 1.1.2.1  2007/01/25 10:59:34  randresol
 * LOG: Modify PRC stack to allow it to run in parallel with ITU, TTC or ANSI stacks
 * LOG:
 * LOG: Revision 9.1.10.2  2006/08/28 13:47:38  mshanmugam
 * LOG: Modified the Alarm format as Route to SCCP as a part of code review change.
 * LOG:
 * LOG: Revision 9.1.10.1  2006/08/18 12:45:42  mshanmugam
 * LOG: Modified Alarm for OAM Feature.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.4.2.8.2  2005/02/21 09:13:42  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.3.2.1.4.2.8.1  2004/12/29 13:49:57  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.3.2.1.4.2  2004/08/27 09:40:26  csireesh
 * LOG: Changes in Alarm Description
 * LOG:
 * LOG: Revision 7.3.2.1.4.1  2004/06/22 11:47:53  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/08/27 14:15:26  hcho
 * LOG: Added alarm number not present in the alarm list.
 * LOG:
 * LOG: Revision 7.3  2003/02/05 17:23:21  aganguly
 * LOG: Changes for SCCP Alarms- Clean up of unwanted alarms still to be done in Release 6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.6  2002/03/22 14:40:51  ngoel
 * LOG: Add alarm
 * LOG:
 * LOG: Revision 6.5  2002/03/22 14:26:35  ngoel
 * LOG: add alarms
 * LOG:
 * LOG: Revision 6.4  2002/03/20 23:30:18  mmiers
 * LOG: Many warnings removed.
 * LOG:
 * LOG: Revision 6.3  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
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

ITS_UINT SCCP_AlarmLevel_PRC = ALARM_LVL_OFF;


/*Intermediate alarms removed between 401 to 415 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 416,
                    "SCCP failed to Initialize ",
                    ALARM_LVL_CRIT,        "Initialize",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 417 to 421 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 422,
                    "SCCP Initialized Successfully",
                    ALARM_LVL_INFO,       "Initialize",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 423,
                    "SCCP Terminating",
                    ALARM_LVL_CRIT,        "Terminate",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 424 to 426 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 427,
                    "PRC SCCP License not found.",
                    ALARM_LVL_CRIT,        "EncodeMTP3",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 428,
                    "User Out of Service (UOS) Message sent from application:",
                    ALARM_LVL_MINOR,       "SendUserOutOfService",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 429,
                    "User In Service (UIS) Message sent from application:",
                    ALARM_LVL_INFO,       "SendUserInService",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 430,
                    "User Congested Message sent from application:",
                    ALARM_LVL_INFO,        "SendSetCongestion",
                    "SCCP", ITS_FALSE);

 /*Intermediate alarms removed between 431 to 435 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 436,
                    "Signaling Point Accessible MTP3-RESUME received for remote node:",
                    ALARM_LVL_INFO,       "SCMGHandleMTP3Msg_PRC",
                    "SCCP", ITS_FALSE);
 
ALARM_FORMAT_SUBSYS(PRC_SCCP, 437,
                    "Signaling Point Inaccessible MTP3-PAUSE received for remote node:",
                    ALARM_LVL_MAJOR,       "SCMGHandleMTP3Msg_PRC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 438,
                    "Signaling Point Congested MTP3-STATUS received for remote node:",
                    ALARM_LVL_INFO,        "SCMGHandleMTP3Msg_PRC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 439,
                    "Malformed MTP3 management message received",
                    ALARM_LVL_MINOR,       "SCMGHandleMTP3Msg_PRC",
                    "SCCP", ITS_FALSE);

 /*Intermediate alarms removed between 440 to 442 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 443,
                    "Subsystem Allowed(SSA) message received from remote subsystem:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 444,
                    "Subsystem Prohibted(SSP) message received from remote subsystem:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 445,
                    "Subsystem Congested(SSC) message received from remote subsystem:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 446,
                    "Subsystem Allowed(SSA) message received ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 447,
                    "Subsystem Prohibted(SSP) message received ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 448,
                    "Subsystem Congested(SSC) message received ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 449,
                    "Unknown SCMG message received from remote:",
                    ALARM_LVL_INFO,        "SCMGHandleSCLCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 450,
                    "Malformed SCMG message received from remote",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 451,
                    "User In Service (UIS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 452,
                    "User Out Of Service (UOS) message received from application for ",
                    ALARM_LVL_INFO,        "SCMGHandleSCLC",
                    "SCCP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 453,
                    "User Out Of Service message received from remote:",
                    ALARM_LVL_MINOR,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 454,
                    "User In Service message received from remote:",
                    ALARM_LVL_INFO,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 455,
                    "Subsystem status Changed to Allowed:",
                    ALARM_LVL_INFO,       "SCMGHandleSSTTimeout",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 456,
                    "Subsystem status changed to Prohibited:",
                    ALARM_LVL_MINOR,       "SCMGHandleSCLC",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 457 to 499 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 500,
                    "SCCP Remote Subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 501,
                    "SCCP Remote Subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "SCCP", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(PRC_SCCP, 502,
                    "SCCP Remote Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 503,
                    "SCCP Remote Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 504,
                    "SCCP Concerned Point Code Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "MML", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 505,
                    "SCCP Concerned Point Code Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "MML", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(PRC_SCCP, 506,
                    "SCCP Concerned subsystem Entry added:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 507,
                    "SCCP Concerned subsystem Entry removed:",
                    ALARM_LVL_INFO,        "SCCP_Console_PRC",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 508 to 631; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 632,
                    "Message for unknown Destination- No Route to remote:",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 633,
                    "Discarding Message from Application- Missing Routing Information.",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 634,
                    "Unknown message type received from application ",
                    ALARM_LVL_MAJOR,       "SCOCHandleAPPMsg_PRC",
                    "SCCP", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(PRC_SCCP, 635,
                    "SCCP-CL Message from application- unknown message type ",
                    ALARM_LVL_MAJOR,       "SCLCHandleAPPMsg_PRC",
                    "Routing ", ITS_TRUE);
#endif

ALARM_FORMAT_SUBSYS(PRC_SCCP, 636,
                    "Unknown message type received from remote ",
                    ALARM_LVL_MAJOR,       "SCOCHandleTimer_PRC",
                    "SCCP", ITS_TRUE);

#if 0
ALARM_FORMAT_SUBSYS(PRC_SCCP, 637,
                    "SCCP-CL Message from remote- unknown ",
                    ALARM_LVL_MAJOR,       "SCLCHandleSCRCMsg",
                    "Routing", ITS_TRUE);
#endif

 /*Intermediate alarms removed between 638 to 642 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 643,
                    "Message received from remote for unavailable subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverMTP3Ind",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 644,
                    "Discarding Message - No SSN in Called Party Address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverLocal",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 645,
                    "SCCP Routing:Global Title Translation failed.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 646,
                    "GTT: Error in translated address.",
                    ALARM_LVL_MAJOR,       "SCRCDeliverByGTT",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 647,
                    "Discarding message - Called party address absent in SCCP message received from remote.",
                    ALARM_LVL_MINOR,       "SCRCHandleMTP3Msg_PRC",
                    "SCCP", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 648,
                    "Message for inaccessible remote subsystem:",
                    ALARM_LVL_MAJOR,       "SCRCDeliverRemote",
                    "SCCP", ITS_TRUE);

 /*Intermediate alarms removed between 649 to 655 ; not used in PR 6.4.1 */

ALARM_FORMAT_SUBSYS(PRC_SCCP, 656,
                    "CC received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownCC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 657,
                    "CREF  received from remote end in invalid state ",
                    ALARM_LVL_MINOR,       "HandleDownCREF",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 658,
                    "RLSD received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownRLSD",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 659,
                    "RLC received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownRLC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 660,
                    "DT1 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 661,
                    "DT1 received from remote end in invalid state",
                    ALARM_LVL_MINOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 662,
                    "DT2 received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 663,
                    "DT2 received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 664,
                    "AK received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 665,
                    "AK received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 666,
                    "ED received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 667,
                    "ED received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 668,
                    "EA received from application in invalid state.",
                    ALARM_LVL_MINOR,       "HandleAppEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 669,
                    "EA received from remote end in invalid state.",
                    ALARM_LVL_MINOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 670,
                    "UDT received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "SCRCHandleMTP3Msg",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 671,
                    "RSR received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 672,
                    "DT1 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 673,
                    "DT1 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT1",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 674,
                    "DT2 received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 675,
                    "DT2 received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownDT2",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 676,
                    "AK received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 677,
                    "AK received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownAK",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 678,
                    "ED received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 679,
                    "EA received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 680,
                    "ED received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownED",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 681,
                    "EA received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownEA",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 682,
                    "RSR received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSR",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 683,
                    "RSC received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 684,
                    "RSC received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownRSC",
                    "SCCP-CO", ITS_TRUE);

ALARM_FORMAT_SUBSYS(PRC_SCCP, 685,
                    "CR received from remote with invalid ",
                    ALARM_LVL_MAJOR,       "HandleDownCR",
                    "SCCP-CO", ITS_TRUE);


ALARM_FORMAT_SUBSYS(PRC_SCCP, 686,
                    "CR received from application with invalid ",
                    ALARM_LVL_MAJOR,       "HandleAppCR",
                    "SCCP-CO", ITS_TRUE);

 /* Alarms removed between 687 to 823 ; not used in PR 6.4.1 */

ALARM_Format *PRC_SCCP_Alarms[] =
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
        NULL, //410
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP416,
        NULL,
        NULL,
        NULL,
        NULL, //420
        NULL,
        &ALARM_PRC_SCCP422,
        &ALARM_PRC_SCCP423,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP427,
        &ALARM_PRC_SCCP428,
        &ALARM_PRC_SCCP429,
        &ALARM_PRC_SCCP430,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP436,
        &ALARM_PRC_SCCP437,
        &ALARM_PRC_SCCP438,
        &ALARM_PRC_SCCP439,
        NULL, //440
        NULL,
        NULL,
        &ALARM_PRC_SCCP443,
        &ALARM_PRC_SCCP444,
        &ALARM_PRC_SCCP445,
        &ALARM_PRC_SCCP446,
        &ALARM_PRC_SCCP447,
        &ALARM_PRC_SCCP448,
        &ALARM_PRC_SCCP449,
        &ALARM_PRC_SCCP450,
        &ALARM_PRC_SCCP451,
        &ALARM_PRC_SCCP452,
        &ALARM_PRC_SCCP453,
        &ALARM_PRC_SCCP454,
        &ALARM_PRC_SCCP455,
        &ALARM_PRC_SCCP456,
        NULL,
        NULL,
        NULL,
        NULL, //460
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //470
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //480
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //490
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP500,
        &ALARM_PRC_SCCP501,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP506,
        &ALARM_PRC_SCCP507,
        NULL,
        NULL,
        NULL, //510
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //515
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //520
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //530
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //540
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //550
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //560
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //570
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //580
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //590
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //600
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //610
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //620
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL, //630
        NULL,
        &ALARM_PRC_SCCP632,
        &ALARM_PRC_SCCP633,
        &ALARM_PRC_SCCP634,
        NULL,
        &ALARM_PRC_SCCP636,
        NULL,
        NULL,
        NULL,
        NULL, //640
        NULL,
        NULL,
        &ALARM_PRC_SCCP643,
        &ALARM_PRC_SCCP644,
        &ALARM_PRC_SCCP645,
        &ALARM_PRC_SCCP646,
        &ALARM_PRC_SCCP647,
        &ALARM_PRC_SCCP648,
        NULL,
        NULL, //650
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &ALARM_PRC_SCCP656,
        &ALARM_PRC_SCCP657,
        &ALARM_PRC_SCCP658,
        &ALARM_PRC_SCCP659,
        &ALARM_PRC_SCCP660,
        &ALARM_PRC_SCCP661,
        &ALARM_PRC_SCCP662,
        &ALARM_PRC_SCCP663,
        &ALARM_PRC_SCCP664,
        &ALARM_PRC_SCCP665,
        &ALARM_PRC_SCCP666,
        &ALARM_PRC_SCCP667,
        &ALARM_PRC_SCCP668,
        &ALARM_PRC_SCCP669,
        &ALARM_PRC_SCCP670,
        &ALARM_PRC_SCCP671,
        &ALARM_PRC_SCCP672,
        &ALARM_PRC_SCCP673,
        &ALARM_PRC_SCCP674,
        &ALARM_PRC_SCCP675,
        &ALARM_PRC_SCCP676,
        &ALARM_PRC_SCCP677,
        &ALARM_PRC_SCCP678,
        &ALARM_PRC_SCCP679,
        &ALARM_PRC_SCCP680,
        &ALARM_PRC_SCCP681,
        &ALARM_PRC_SCCP682,
        &ALARM_PRC_SCCP683,
        &ALARM_PRC_SCCP684,
        &ALARM_PRC_SCCP685,
        &ALARM_PRC_SCCP686
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
SCCP_Alarm_PRC(int which, const char *file, const int line,
                 char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= PRC_SCCP_ALARM_START &&
                 which <= PRC_SCCP_ALARM_END);

    fmt = PRC_SCCP_Alarms[which - PRC_SCCP_ALARM_START]; 
   
    if (fmt != NULL)
    {
        if (fmt->severity > SCCP_AlarmLevel_PRC)
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

