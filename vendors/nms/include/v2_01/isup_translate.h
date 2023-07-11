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
 *  ID: $Id: isup_translate.h,v 9.1 2005/03/23 12:55:46 cvsadmin Exp $
 *
 * LOG: $Log: isup_translate.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:54  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/09/05 20:35:47  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:00  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.11  2000/08/09 19:55:13  hxing
 * LOG: Handle PAM and some automatically generated messages
 * LOG:
 * LOG: Revision 1.10  2000/08/01 19:52:09  hxing
 * LOG: Continue testing
 * LOG:
 * LOG: Revision 1.9  2000/07/21 16:59:43  hxing
 * LOG: Some issues with ANSI
 * LOG:
 * LOG: Revision 1.8  2000/07/11 23:18:27  hxing
 * LOG: Use its assertion
 * LOG:
 * LOG: Revision 1.7  2000/07/06 23:00:46  hxing
 * LOG: Almost done.
 * LOG:
 * LOG: Revision 1.6  2000/07/03 22:23:32  hxing
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.5  2000/06/30 22:00:12  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.4  2000/06/28 22:58:09  hxing
 * LOG: Add utility functions
 * LOG:
 * LOG: Revision 1.3  2000/06/27 23:33:18  hxing
 * LOG: Do the other way. Convert ITS event to a NMS event
 * LOG:
 * LOG: Revision 1.2  2000/06/23 22:52:38  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.1  2000/06/22 22:09:15  hxing
 * LOG: Translate NMS messages to ITS messages
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ifndef ISUP_TRANSLATE_H
#define ISUP_TRANSLATE_H

#include <isupmsgs.h>
#include <isupapi.h>

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
#endif (ANSI)

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
#endif (CCITT)


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



#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* ISUP_TRANSLATE_H */