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
 *  ID: $Id: isup_translate.h,v 9.1 2005/03/23 12:55:56 cvsadmin Exp $
 *
 * LOG: $Log: isup_translate.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:56  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:19  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:59  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/16 15:53:32  hcho
 * LOG: Modifications for v3_6.
 * LOG:
 * LOG: Revision 1.1.2.1  2001/12/21 21:25:25  hcho
 * LOG: Initialize v3.6 build.
 * LOG:
 * LOG: Revision 1.2.2.1  2001/10/20 00:09:53  hcho
 * LOG: Support both families.
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

#include <isupmsgs.h>
#include <isupdef.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* types for the utility functions */
#define LOWEST_BIT      1
#define HIGHEST_BIT     8

/* receive NMS ISUP messages and translate it into an array of ITS_ISUP_IE */

#if defined(CCITT)

#define ReceiveNmsANM ReceiveNmsANM_CCITT
#define ReceiveNmsIAM ReceiveNmsIAM_CCITT
#define ReceiveNmsACM ReceiveNmsACM_CCITT
#define ReceiveNmsCPG ReceiveNmsCPG_CCITT
#define ReceiveNmsINF ReceiveNmsINF_CCITT
#define ReceiveNmsINR ReceiveNmsINR_CCITT
#define ReceiveNmsFOT ReceiveNmsFOT_CCITT
#define ReceiveNmsPAM ReceiveNmsPAM_CCITT
#define ReceiveNmsREL ReceiveNmsREL_CCITT
#define ReceiveNmsRLC ReceiveNmsRLC_CCITT
#define ReceiveNmsRES ReceiveNmsRES_CCITT
#define ReceiveNmsCGB ReceiveNmsCGB_CCITT
#define ReceiveNmsCOT ReceiveNmsCOT_CCITT
#define ReceiveNmsCQR ReceiveNmsCQR_CCITT
#define ReceiveNmsGRA ReceiveNmsGRA_CCITT
#define ReceiveNmsGRS ReceiveNmsGRS_CCITT
#define ReceiveNmsCFN ReceiveNmsCFN_CCITT
#define ReceiveNmsSUS ReceiveNmsSUS_CCITT

#elif defined(ANSI)
 
#define ReceiveNmsANM ReceiveNmsANM_ANSI
#define ReceiveNmsIAM ReceiveNmsIAM_ANSI
#define ReceiveNmsACM ReceiveNmsACM_ANSI
#define ReceiveNmsCPG ReceiveNmsCPG_ANSI
#define ReceiveNmsINF ReceiveNmsINF_ANSI
#define ReceiveNmsINR ReceiveNmsINR_ANSI
#define ReceiveNmsFOT ReceiveNmsFOT_ANSI
#define ReceiveNmsPAM ReceiveNmsPAM_ANSI
#define ReceiveNmsREL ReceiveNmsREL_ANSI
#define ReceiveNmsRLC ReceiveNmsRLC_ANSI
#define ReceiveNmsRES ReceiveNmsRES_ANSI
#define ReceiveNmsCGB ReceiveNmsCGB_ANSI
#define ReceiveNmsCOT ReceiveNmsCOT_ANSI
#define ReceiveNmsCQR ReceiveNmsCQR_ANSI
#define ReceiveNmsGRA ReceiveNmsGRA_ANSI
#define ReceiveNmsGRS ReceiveNmsGRS_ANSI
#define ReceiveNmsCFN ReceiveNmsCFN_ANSI
#define ReceiveNmsSUS ReceiveNmsSUS_ANSI

#endif

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

#if defined(CCITT)

#define GetNMSConnectEvent GetNMSConnectEvent_CCITT
#define GetNMSConnectStatusEvent GetNMSConnectStatusEvent_CCITT
#define GetNMSPAM GetNMSPAM_CCITT
#define GetNMSInfoEvent GetNMSInfoEvent_CCITT
#define GetNMSReleaseEvent GetNMSReleaseEvent_CCITT
#define GetNMSResumeEvent GetNMSResumeEvent_CCITT
#define GetNMSSuspendEvent GetNMSSuspendEvent_CCITT
#define GetNMSStatusEvent GetNMSStatusEvent_CCITT
#define GetNMSFacilityEvent GetNMSFacilityEvent_CCITT
 
#elif defined(ANSI)

#define GetNMSConnectEvent GetNMSConnectEvent_ANSI
#define GetNMSConnectStatusEvent GetNMSConnectStatusEvent_ANSI
#define GetNMSPAM GetNMSPAM_ANSI
#define GetNMSInfoEvent GetNMSInfoEvent_ANSI
#define GetNMSReleaseEvent GetNMSReleaseEvent_ANSI
#define GetNMSResumeEvent GetNMSResumeEvent_ANSI
#define GetNMSSuspendEvent GetNMSSuspendEvent_ANSI
#define GetNMSStatusEvent GetNMSStatusEvent_ANSI
#define GetNMSFacilityEvent GetNMSFacilityEvent_ANSI
 
#endif

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
