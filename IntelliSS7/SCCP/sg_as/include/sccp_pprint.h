/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: sccp_pprint.h,v 1.2 2007/01/10 11:15:02 yranade Exp $
 *
 * LOG: $Log: sccp_pprint.h,v $
 * LOG: Revision 1.2  2007/01/10 11:15:02  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1  2005/07/19 00:45:11  randresol
 * LOG: Add SUA Test programs for RFC Implementation
 * LOG:
 * LOG: Revision 1.1.2.2  2005/05/23 15:55:03  cbascon
 * LOG: added prototype for PrintSCCPMessageString
 * LOG:
 * LOG: Revision 1.1.2.1  2005/05/23 15:02:44  cbascon
 * LOG: initial checkin
 * LOG:
 * LOG: Revision 1.1.2.1  2005/05/23 14:12:33  cbascon
 * LOG:
 *****************************************************************************/
#ifndef __SCCP_PPRINT_H__
#define __SCCP_PPRINT_H__


void PrintSCCPIE(const its::SCCP_IEClass *ie);
void PrintSCCPMessage(its::SCCP_MessageClass *msg);
void PrintSCCPMessageString(its::SCCP_MessageClass *msg);

void PrintCredit(its::SCCP_Credit *credit);
void PrintReference(its::SCCP_RefNum* slr, char* which);
void PrintProtocolClass(its::SCCP_ProtocolClass *pc);
void PrintAddr(its::SCCP_Address* called_pa, char* which);
void PrintData(its::SCCP_UserData *ud);
void PrintCause(its::SCCP_Cause* rc, char* which);
void PrintHopCount(its::SCCP_HopCount* hc);
void PrintSegmentReassem(its::SCCP_SegmentReassem* sr);
void PrintSequenceSegment(its::SCCP_SequenceSegment* ss);
void PrintRSN(its::SCCP_ReceiveSequenceNum* ss);



#endif /* __SCCP_PPRINT_H__ */
