/****************************************************************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: isup_translate.h,v 9.1 2005/03/23 12:55:43 cvsadmin Exp $
 *
 * LOG: $Log: isup_translate.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:04  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:54  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.1  2001/09/05 20:35:47  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:41  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.2  2000/09/20 22:58:45  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.1  2000/09/08 21:56:16  hxing
 * LOG: Add files for version 3.5
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ifndef ISUP_TRANSLATE_H
#define ISUP_TRANSLATE_H

#if NMS_VERSION >= 3050
#include <isupmsgs.h>
#include <isupdef.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* types for the utility functions */
#define LOWEST_BIT      1
#define HIGHEST_BIT     8

/* receive NMS ISUP messages and translate it into an array of ITS_ISUP_IE */

/* Connect Event */
int ReceiveNmsANM(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsIAM(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Connect Status Event */
int ReceiveNmsACM(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsCPG(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsINF(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsINR(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsFOT(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Info Event */
int ReceiveNmsPAM(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Release Event */
int ReceiveNmsREL(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsRLC(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Resume Event */
int ReceiveNmsRES(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Status Event */
int ReceiveNmsCGB(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsCOT(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsCQR(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsGRA(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsGRS(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsCFN(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Suspend Event */
int ReceiveNmsSUS(SiAllSdus* msg, ITS_ISUP_IE* ies);

#if defined (ANSI)
int ReceiveNmsCRM(SiAllSdus* msg, ITS_ISUP_IE* ies); /* Status Event */
int ReceiveNmsEXM(SiAllSdus* msg, ITS_ISUP_IE* ies); /* Connect Status Event */
#endif /* (ANSI) */

#if defined (CCITT)
/* Connect Status Event */
int ReceiveNmsIDR(SiAllSdus* msg, ITS_ISUP_IE* ies); 
int ReceiveNmsIRS(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsNRM(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Facility Event */
int ReceiveNmsFAC(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsFAA(SiAllSdus* msg, ITS_ISUP_IE* ies);
int ReceiveNmsFRJ(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Connect Status Event */
int ReceiveNmsSAM(SiAllSdus* msg, ITS_ISUP_IE* ies);

/* Info Event */
int ReceiveNmsUSR(SiAllSdus* msg, ITS_ISUP_IE* ies);
#endif /* (CCITT) */


/* Functions uesed for sending ISUP messages */

void GetNMSConnectEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiConEvnt* conEvent);

void GetNMSConnectStatusEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiCnStEvnt* conEvent);

void GetNMSPAM(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiInfoEvnt* conEvent);

void GetNMSInfoEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiInfoEvnt* conEvent);

void GetNMSReleaseEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiRelEvnt* conEvent);

void GetNMSResumeEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiResmEvnt* conEvent);

void GetNMSSuspendEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiSuspEvnt* conEvent);

void GetNMSStatusEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiStaEvnt* conEvent);

void GetNMSFacilityEvent(ITS_ISUP_IE* ies, int ieCount, 
                        ISUP_MSG_DESC* desc, SiFacEvnt* conEvent);


void PrintCtaEvent( CTA_EVENT *event );


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* ISUP_TRANSLATE_H */

