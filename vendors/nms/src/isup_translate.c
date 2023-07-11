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
 *  ID: $Id: isup_translate.c,v 9.1 2005/03/23 12:56:16 cvsadmin Exp $
 *
 * LOG: $Log: isup_translate.c,v $
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/16 15:51:09  hcho
 * LOG: Modifications for v3_6 build.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/11/21 20:18:19  hcho
 * LOG: fix previous error.
 * LOG:
 * LOG: Revision 5.4  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.3  2001/10/30 17:08:09  hcho
 * LOG: fix for UserServiceInfo.
 * LOG:
 * LOG: Revision 5.2  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.1  2001/09/05 20:35:48  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:43  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.10  2001/02/08 23:30:57  hxing
 * LOG: Debug in solaris for isup integration
 * LOG:
 * LOG: Revision 1.9  2001/02/08 23:09:32  hxing
 * LOG: Continue
 * LOG:
 * LOG: Revision 1.8  2001/02/08 23:00:28  hxing
 * LOG: Integrate test
 * LOG:
 * LOG: Revision 1.7  2001/02/06 00:14:57  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 1.6  2000/10/02 22:37:52  hxing
 * LOG: Work in solaris
 * LOG:
 * LOG: Revision 1.5  2000/09/25 14:30:16  hxing
 * LOG: More message
 * LOG:
 * LOG: Revision 1.4  2000/09/22 15:01:20  hxing
 * LOG: Add testing files
 * LOG:
 * LOG: Revision 1.3  2000/09/21 22:49:28  hxing
 * LOG: work in progress
 * LOG:
 * LOG: Revision 1.2  2000/09/20 22:58:45  hxing
 * LOG: Work in progress
 * LOG:
 * LOG: Revision 1.1  2000/09/18 15:33:25  hxing
 * LOG: Add file for nms 3.5
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <its_assertion.h>

#include <its_intern.h>

#if defined(INCLUDE_ISUP)

#include <isup_translate.h>

#if defined (UNIX)
#include <unistd.h>
#elif defined (WIN32)
#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <fcntl.h>
#endif

extern int nms_debug;
extern int nms_errno;

/**************************************************************************
**
** utility functions
**
***************************************************************************/

void 
PrintCtaEvent( CTA_EVENT *event )
{
    char format_buffer[CTA_MAX_FORMAT_SIZE];
    char *prefix = "\tNMSVendor:";  /* default demo indent */
    format_buffer[0] = '\0';
    ctaFormatEvent( prefix, event, format_buffer, CTA_MAX_FORMAT_SIZE );
    printf( "%s", format_buffer );
}


/*
** direction: ITS ---> NMS
** This funciton sets bits between "startbit" and "endbit" 
** from "octet" to "tknU8"
*/
static void
SetBitsToTknU8(TknU8 *tknU8, ITS_OCTET octet, int startbit, int endbit)
{
    ITS_OCTET   mask;
    int         len, rightShiftTimes;

    ITS_C_REQUIRE( (HIGHEST_BIT >= startbit >= LOWEST_BIT) && 
                   (HIGHEST_BIT >= endbit >= LOWEST_BIT) &&
                   (startbit <= endbit) );

    /* length of bits to set */
    len = endbit - startbit + 1;

    /* right shift times */
    rightShiftTimes = startbit - 1;

    /* compute the mask */
    mask = (1 << len) - 1;

    /* set the tknU8 */
    tknU8->pres = PRESENT;
    tknU8->val = (octet >> rightShiftTimes) & mask;
}

/*
** direction: ITS ---> NMS
** This function is just a special case of SetBitsToTknU8.
** i.e.  startbit = 1, endbit = 8
*/
static void 
SetTknU8(TknU8* tknU8, ITS_OCTET val)
{
    tknU8->pres = PRESENT;
    tknU8->val = val;
}

/*
** direction: NMS ---> ITS
** This funciton sets tknU8 to the bits in "octet" between 
** "startbit" and "endbit"
*/
static ITS_OCTET
SetTknU8ToBits(TknU8 tknU8, ITS_OCTET octet, int startbit, int endbit)
{
    ITS_OCTET   maskTemp, mask;
    int         len, leftShiftTimes;

    ITS_C_REQUIRE( (HIGHEST_BIT >= startbit >= LOWEST_BIT) && 
                   (HIGHEST_BIT >= endbit >= LOWEST_BIT) &&
                   (startbit <= endbit) );

    /* length of bits to set */
    len = endbit - startbit + 1;

    /* left shift times */
    leftShiftTimes = startbit - 1;

    /* compute the mask */
    maskTemp = (1 << len) - 1;
    mask = maskTemp << leftShiftTimes;

    /* only disturb the related bits */
    octet &= ~mask;

    /* set the bits */
    octet |= (tknU8.val << leftShiftTimes) & mask;

    return (octet);
}

/* 
** direction: ITS ---> NMS
** This function sets an array of ITS_OCTET of length "len"
** to a TknStr "tknStr"
*/
static void 
SetTknStr(TknStr* tknStr, ITS_OCTET* data, int len)
{
    tknStr->pres = PRESENT;
    tknStr->len = len;
    memcpy(tknStr->val, data, len);
}

/* 
** direction: ITS ---> NMS
** This function sets an ITS_OCTET array of length "len" to a TknU32 "tknU32"
** Note: max 4 octets can be set to a Tkn32
*/
static void
SetTknU32(TknU32* tknU32, ITS_OCTET* octets, int len)
{
    int i;

    /* make sure max 4 octets can be set to a U32 */
    ITS_C_REQUIRE(len <= sizeof(U32));

    tknU32->pres = PRESENT;

    for (i = 0; i < len; i++)
    {
        tknU32->val |= octets[i] << 8 * (len - 1 - i);
    }
}

/* 
** direction: ITS ---> NMS
** This function sets an ITS_OCTET array of length "len" to a TknU16 "tknU16"
** Note: max 2 octets can be set to a Tkn16
*/
static void
SetTknU16(TknU16* tknU16, ITS_OCTET* octets, int len)
{
    int i;

    /* make sure max 2 octets can be set to a U16 */
    ITS_C_REQUIRE(len <= sizeof(U16));

    tknU16->pres = PRESENT;

    for (i = 0; i < len; i++)
    {
        tknU16->val |= octets[i] << 8 * (len - 1 - i);
    }
}

/**************************************************************************
**
** helper functions to convert an ISUP IE between NMS format and ITS format
**
***************************************************************************/

/* Extended Element */
static void
ExtendedElement_NMS_to_ITS(SiElementExt* nmsIE, ITS_ISUP_IE* itsIE)
{
    /* ITS not handle unknown ie */
}

static void
ExtendedElement_ITS_to_NMS(SiElementExt* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
}


/* Circuit state indicator */
static void    
CircuitStateInd_NMS_to_ITS(SiCirStateInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CKT_STATE_INDICATOR;    
    
    memcpy(itsIE->param_data.circuitStateIndicators.states,
           nmsIE->cirSteInd.val, nmsIE->cirSteInd.len);

    itsIE->param_length = nmsIE->cirSteInd.len;
}

static void    
CircuitStateInd_ITS_to_NMS(SiCirStateInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetTknStr(&nmsIE->cirSteInd, 
              itsIE->param_data.circuitStateIndicators.states,
              itsIE->param_length);
}

/* Continuity indicators */
static void
ContinuityInd_NMS_to_ITS(SiContInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CONTINUITY_INDICATORS;
    itsIE->param_length = sizeof(ISUP_CONTINUITY_INDICATORS);    
      
    /* bit A */
    itsIE->param_data.continuityIndicators.indicators = 
        nmsIE->contInd.val & 0x01U;

    /* all other bits are spared */
}

static void
ContinuityInd_ITS_to_NMS(SiContInd* nmsIE, ITS_ISUP_IE* itsIE)
{    
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->contInd, 
                   itsIE->param_data.continuityIndicators.indicators,
                   1, 1);
}

/* Circuit group supervision message type indicator */
static void
CGSuperMsgTypeInd_NMS_to_ITS(SiCirGrpSupMTypInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    itsIE->param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);    
      
    /* bit B A */
    itsIE->param_data.supervisionMsgType.sup_mt = nmsIE->typeInd.val & 0x03U;

    /* all other bits are spared */
}

static void
CGSuperMsgTypeInd_ITS_to_NMS(SiCirGrpSupMTypInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->typeInd,
             itsIE->param_data.supervisionMsgType.sup_mt, 1, 2);
}
    
/* Range and status */
static void
RangeStat_NMS_to_ITS(SiRangStat* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_RANGE_STATUS;    

    itsIE->param_data.rangeAndStatus.range = nmsIE->range.val;
    
    memcpy(itsIE->param_data.rangeAndStatus.status,
           nmsIE->status.val, nmsIE->status.len);

    itsIE->param_length = sizeof(ITS_OCTET) + nmsIE->status.len;
}

static void
RangeStat_ITS_to_NMS(SiRangStat* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->range, itsIE->param_data.rangeAndStatus.range);
    
    SetTknStr(&nmsIE->status,
              itsIE->param_data.rangeAndStatus.status,
              itsIE->param_length - sizeof(ITS_OCTET));
}

/* Suspend resume indicators */
static void
SusResumeInd_NMS_to_ITS(SiSusResInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SUSP_RESUM_INDICATORS;
    itsIE->param_length = sizeof(ISUP_SUSPEND_RESUME_INDICATORS);    
      
    /* bit A */
    itsIE->param_data.suspendResumeInd.sus_res = nmsIE->susResInd.val & 0x01U;

    /* all other bits are spared */
}

static void
SusResumeInd_ITS_to_NMS(SiSusResInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->susResInd,
             itsIE->param_data.suspendResumeInd.sus_res, 1, 1);
}

/* Automatic congestion level */
static void
AutoCongestLevel_NMS_to_ITS(SiAutoCongLvl* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_AUTO_CONGEST_LEVEL;
    itsIE->param_length = sizeof(ISUP_AUTOMATIC_CONGESTION_LEVEL);    
    
    itsIE->param_data.autoCongestionLevel.level = nmsIE->auCongLvl.val;
}

static void
AutoCongestLevel_ITS_to_NMS(SiAutoCongLvl* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;  
    
    SetTknU8(&nmsIE->auCongLvl, itsIE->param_data.autoCongestionLevel.level);
}

/* Event information */
static void
EventInfo_NMS_to_ITS(SiEvntInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_EVENT_INFO;
    itsIE->param_length = sizeof(ISUP_EVENT_INFO);
    
    /* bits G F E D C B A */
    itsIE->param_data.eventInfo.evt_info = nmsIE->evntInd.val & 0x7FU;
    itsIE->param_data.eventInfo.evt_info |= 
        ((nmsIE->evntPresResInd.val << 7)  & 0x80U);
}

static void
EventInfo_ITS_to_NMS(SiEvntInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;    
    
    /* bits G F E D C B A */
    SetBitsToTknU8(&nmsIE->evntInd,
             itsIE->param_data.eventInfo.evt_info, 1, 7);
    
    /* bit H */
    SetBitsToTknU8(&nmsIE->evntPresResInd, 
                   itsIE->param_data.eventInfo.evt_info, 8, 8);
}

/* Cause indicators */
static void
CauseInd_NMS_to_ITS(SiCauseDgn* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CAUSE_INDICATORS;
    
    itsIE->param_data.causeIndicator.subfields4 = nmsIE->location.val & 0x0FU;
    itsIE->param_data.causeIndicator.subfields4 |= 
        ((nmsIE->cdeStand.val << 5)  & 0x60U);
    /* set the 1st ext to 1 */
    itsIE->param_data.causeIndicator.subfields4 |= 0x80U;

    itsIE->param_data.causeIndicator.cause_val = nmsIE->causeVal.val & 0x7FU;

    itsIE->param_length = 2 * sizeof(ITS_OCTET); /* fixed part */

    if (nmsIE->dgnVal.pres == PRESENT)
    {
        memcpy(itsIE->param_data.causeIndicator.diagnostics,
               nmsIE->dgnVal.val, nmsIE->dgnVal.len);

        itsIE->param_length += nmsIE->dgnVal.len;

        /* set the 2nd ext to 1 */
        itsIE->param_data.causeIndicator.cause_val |= 0x80U;
    }    
}

static void
CauseInd_ITS_to_NMS(SiCauseDgn* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->location,
                   itsIE->param_data.causeIndicator.subfields4, 1, 4);

    SetBitsToTknU8(&nmsIE->cdeStand,
                   itsIE->param_data.causeIndicator.subfields4, 6, 7);

    SetBitsToTknU8(&nmsIE->causeVal,
                   itsIE->param_data.causeIndicator.cause_val, 1, 7);

    if (itsIE->param_length > 2 * sizeof(ITS_OCTET))
    {
        /* diagnostic exists */
        SetTknStr(&nmsIE->dgnVal,
              itsIE->param_data.causeIndicator.diagnostics,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
    }
}

/* IE: Backward call indicators */
static void
BkwdCallInd_NMS_to_ITS(SiBckCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
    itsIE->param_length = sizeof(ISUP_BKWD_CALL_INDICATORS);

    /* bit B A */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[0] = 
        nmsIE->chrgInd.val & 0x03U;

    /* bit D C */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[0] |= 
        ((nmsIE->cadPtyStatInd.val << 2) & 0x0CU);

    /* bit F E */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[0] |= 
        ((nmsIE->cadPtyCatInd.val << 4) & 0x30U);

    /* bit H G */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[0] |= 
        ((nmsIE->end2EndMethInd.val << 6) & 0xC0U);

    /* bit I */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] = 
        nmsIE->intInd.val & 0x01U;

    /* bit J */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->end2EndInfoInd.val << 1) & 0x02U);

    /* bit K */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->isdnUsrPrtInd.val << 2) & 0x04U);

    /* bit L */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->holdInd.val << 3) & 0x08U);

    /* bit M */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->isdnAccInd.val << 4) & 0x10U);

    /* bit N */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->echoCtrlDevInd.val << 5) & 0x20U);

    /* bit P O */
    itsIE->param_data.backwardCallIndicators.bkwd_ci[1] |= 
        ((nmsIE->sccpMethInd.val << 6) & 0xC0U);
}

static void
BkwdCallInd_ITS_to_NMS(SiBckCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT; 

    /* bit B A */
    SetBitsToTknU8(&nmsIE->chrgInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[0], 1, 2);

    /* bit D C */
    SetBitsToTknU8(&nmsIE->cadPtyStatInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[0], 3, 4);

    /* bit F E */
    SetBitsToTknU8(&nmsIE->cadPtyCatInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[0], 5, 6);

    /* bit H G */
    SetBitsToTknU8(&nmsIE->end2EndMethInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[0], 7, 8);

    /* bit I */
    SetBitsToTknU8(&nmsIE->intInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 1, 1);

    /* bit J */
    SetBitsToTknU8(&nmsIE->end2EndInfoInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 2, 2);

    /* bit K */
    SetBitsToTknU8(&nmsIE->isdnUsrPrtInd, 
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 3, 3);

    /* bit L */
    SetBitsToTknU8(&nmsIE->holdInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 4, 4);

    /* bit M */
    SetBitsToTknU8(&nmsIE->isdnAccInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 5, 5);

    /* bit N */
    SetBitsToTknU8(&nmsIE->echoCtrlDevInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 6, 6);

    /* bit P O */
    SetBitsToTknU8(&nmsIE->sccpMethInd,
                   itsIE->param_data.backwardCallIndicators.bkwd_ci[1], 7, 8);
}


/* IE: Optional Backward call indicators */
static void
OpBkwdCallInd_NMS_to_ITS(SiOptBckCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_OPT_BKWD_CALL_INDICATORS;
    itsIE->param_length = sizeof(ISUP_OPT_BKWD_CALL_INDICATORS);

    /* bit A */
    itsIE->param_data.optBkwdCallIndicators.obkwd_ind = 
        nmsIE->inbndInfoInd.val & 0x01U;

    /* bit B */
    itsIE->param_data.optBkwdCallIndicators.obkwd_ind |= 
        ((nmsIE->caFwdMayOcc.val << 1) & 0x02U);

#if defined (CCITT) /* ANSI bits C,D spare */
    /* bit C */
    itsIE->param_data.optBkwdCallIndicators.obkwd_ind |= 
        ((nmsIE->segInd.val << 2) & 0x04U);

    /* bit D */
    itsIE->param_data.optBkwdCallIndicators.obkwd_ind |= 
        ((nmsIE->mlppUsrInd.val << 3) & 0x08U);
#endif

#if defined (ANSI)
    /* bit H */
    itsIE->param_data.optBkwdCallIndicators.obkwd_ind |= 
        ((nmsIE->usrNetIneractInd.val << 7) & 0x80U);
#endif

    /* other bits reserved for national use*/
}

static void
OpBkwdCallInd_ITS_to_NMS(SiOptBckCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A */
    SetBitsToTknU8(&nmsIE->inbndInfoInd,
                   itsIE->param_data.optBkwdCallIndicators.obkwd_ind, 1, 1);

    /* bit B */
    SetBitsToTknU8(&nmsIE->caFwdMayOcc,
                   itsIE->param_data.optBkwdCallIndicators.obkwd_ind, 2, 2);

#if defined (CCITT) /* ANSI bits C,D spare */
    /* bit C */
    SetBitsToTknU8(&nmsIE->segInd,
                   itsIE->param_data.optBkwdCallIndicators.obkwd_ind, 3, 3);

    /* bit D */
    SetBitsToTknU8(&nmsIE->mlppUsrInd,
                   itsIE->param_data.optBkwdCallIndicators.obkwd_ind, 4, 4);
#endif

#if defined (ANSI)
    /* bit H */
    SetBitsToTknU8(&nmsIE->usrNetIneractInd,
                   itsIE->param_data.optBkwdCallIndicators.obkwd_ind, 8, 8);
#endif

    /* other bits reserved for national use*/
}

/* IE: Information indicators */
static void
InfoIndicators_NMS_to_ITS(SiInfoInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_INFO_INDICATORS;
    itsIE->param_length = sizeof(ISUP_INFORMATION_INDICATORS);

    /* bit B A */
    itsIE->param_data.informationIndicators.indics[0] = 
        nmsIE->cgPtyAddrRespInd.val & 0x03U;

    /* bit C */
    itsIE->param_data.informationIndicators.indics[0] |= 
        ((nmsIE->holdProvInd.val << 2)  & 0x04U);

    /* bit F */
    itsIE->param_data.informationIndicators.indics[0] |= 
        ((nmsIE->cgPtyCatRespInd.val << 5)  & 0x20U);

    /* bit G */
    itsIE->param_data.informationIndicators.indics[0] |= 
        ((nmsIE->chrgInfoRespInd.val << 6)  & 0x40U);

    /* bit H */
    itsIE->param_data.informationIndicators.indics[0] |= 
        ((nmsIE->solInfoInd.val << 7)  & 0x80U);

#if defined (ANSI)
    /* bit P */
    itsIE->param_data.informationIndicators.indics[1] = 
        (nmsIE->mlbgInfoInd.val & 0x80U);
#endif

    /* all other bits are either spare or reserved */
}

static void
InfoIndicators_ITS_to_NMS(SiInfoInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit B A */
    SetBitsToTknU8(&nmsIE->cgPtyAddrRespInd,
                   itsIE->param_data.informationIndicators.indics[0], 1, 2);

    /* bit C */
    SetBitsToTknU8(&nmsIE->holdProvInd,
                   itsIE->param_data.informationIndicators.indics[0], 3, 3);

    /* bit F */
    SetBitsToTknU8(&nmsIE->cgPtyCatRespInd,
                   itsIE->param_data.informationIndicators.indics[0], 6, 6);

    /* bit G */
    SetBitsToTknU8(&nmsIE->chrgInfoRespInd,
                   itsIE->param_data.informationIndicators.indics[0], 7, 7);

    /* bit H */
    SetBitsToTknU8(&nmsIE->solInfoInd,
                   itsIE->param_data.informationIndicators.indics[0], 8, 8);

#if defined (ANSI)
    /* bit P */
    SetBitsToTknU8(&nmsIE->mlbgInfoInd,
                   itsIE->param_data.informationIndicators.indics[1], 8, 8);
#endif

    /* all other bits are either spare or reserved */
}

/* IE: Nature of connection indicators */
static void
NatConInd_NMS_to_ITS(SiNatConInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_NATURE_CONN_INDICATORS;
    itsIE->param_length = sizeof(ISUP_CONNECTION_INDICATORS);

    itsIE->param_data.connectionIndicator.subfields4 = 
        nmsIE->satInd.val & 0x03U;

    itsIE->param_data.connectionIndicator.subfields4 |= 
        ((nmsIE->contChkInd.val << 2) & 0x0CU);

    itsIE->param_data.connectionIndicator.subfields4 |= 
        ((nmsIE->echoCntrlDevInd.val << 5) & 0x10U);
}

static void
NatConInd_ITS_to_NMS(SiNatConInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->satInd,
                   itsIE->param_data.connectionIndicator.subfields4, 1, 2);

    SetBitsToTknU8(&nmsIE->contChkInd,
                   itsIE->param_data.connectionIndicator.subfields4, 3, 4);

    SetBitsToTknU8(&nmsIE->echoCntrlDevInd,
                   itsIE->param_data.connectionIndicator.subfields4, 5, 5);
}

/* IE: Forward call indicators */
static void 
FwdCallInd_NMS_to_ITS(SiFwdCallInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_FWD_CALL_INDICATORS;
    itsIE->param_length = sizeof(ISUP_FORWARD_CALL_INDICATORS);

    /* bit A */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] = 
        nmsIE->natIntCallInd.val & 0x01U;
    
    /* bit C B */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->end2EndMethInd.val << 1) & 0x06U);

    /* bit D */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->intInd.val << 3) & 0x08U);

    /* bit E */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->end2EndInfoInd.val << 4) & 0x10U);

#if defined (ANSI) /* the segInd is very unclear */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->segInd.val << 4) & 0x10U);
#endif /* (ANSI) */

    /* bit F */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->isdnUsrPrtInd.val << 5) & 0x20U);

    /* bit H G */
    itsIE->param_data.forwardCallIndicators.fwd_ci[0] |= 
        ((nmsIE->isdnUsrPrtPrfInd.val << 6) & 0xC0U);

    /* bit I */
    itsIE->param_data.forwardCallIndicators.fwd_ci[1] = 
        nmsIE->isdnAccInd.val & 0x01U;

    /* bit K J */
    itsIE->param_data.forwardCallIndicators.fwd_ci[1] |= 
        ((nmsIE->sccpMethInd.val << 1) & 0x06U);
}

static void 
FwdCallInd_ITS_to_NMS(SiFwdCallInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A */
    SetBitsToTknU8(&nmsIE->natIntCallInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 1, 1);
    
    /* bit C B */
    SetBitsToTknU8(&nmsIE->end2EndMethInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 2, 3);

    /* bit D */
    SetBitsToTknU8(&nmsIE->intInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 4, 4);

    /* bit E */
    SetBitsToTknU8(&nmsIE->end2EndInfoInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 5, 5);

#if defined (ANSI) /* segInd is very unclear */
    SetBitsToTknU8(&nmsIE->segInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 5, 5);
#endif /* (ANSI) */

    /* bit F */
    SetBitsToTknU8(&nmsIE->isdnUsrPrtInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 6, 6);

    /* bit H G */
    SetBitsToTknU8(&nmsIE->isdnUsrPrtPrfInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[0], 7, 8);

    /* bit I */
    SetBitsToTknU8(&nmsIE->isdnAccInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[1], 1, 1);

    /* bit K J */
    SetBitsToTknU8(&nmsIE->sccpMethInd,
                   itsIE->param_data.forwardCallIndicators.fwd_ci[1], 2, 3);
}

/* IE: Calling party's category */
static void
CgPtyCategory_NMS_to_ITS(SiCgPtyCat* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALLING_PARTY_CATEGORY;
    itsIE->param_length = sizeof(ISUP_CALLING_PARTY_CATEGORY);

    itsIE->param_data.callingPartyCategory.cat = nmsIE->cgPtyCat.val;
}

static void
CgPtyCategory_ITS_to_NMS(SiCgPtyCat* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->cgPtyCat, itsIE->param_data.callingPartyCategory.cat);
}

/* IE: Called Party number */
static void
CdPtyNum_NMS_to_ITS(SiCdPtyNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALLED_PARTY_NUM;

    itsIE->param_data.calledPartyNum.addr_ind = nmsIE->natAddrInd.val & 0x7FU;
    itsIE->param_data.calledPartyNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.calledPartyNum.num_plan = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.calledPartyNum.num_plan |= 
        ((nmsIE->innInd.val << 7) & 0x80U);

    memcpy(itsIE->param_data.calledPartyNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
CdPtyNum_ITS_to_NMS(SiCdPtyNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->natAddrInd,
                   itsIE->param_data.calledPartyNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.calledPartyNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.calledPartyNum.num_plan, 5, 7);
    SetBitsToTknU8(&nmsIE->innInd,
                   itsIE->param_data.calledPartyNum.num_plan, 8, 8);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.calledPartyNum.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Transimt network selection */
static void
TransmitNwSel_NMS_to_ITS(SiTranNetSel* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_TRANSIT_NTWK_SELECT;
    itsIE->param_length = sizeof(ITS_OCTET); /* fixed part only */

    itsIE->param_data.transitNetworkSelection.network = 
        nmsIE->netIdPln.val & 0x0FU;
    itsIE->param_data.transitNetworkSelection.network |= 
        ((nmsIE->typNetId.val << 4) & 0x70U);

#if defined (CCITT)
    if (nmsIE->oddEven.pres == PRESENT) /* CCITT */
    {
        itsIE->param_data.transitNetworkSelection.network |=
            ((nmsIE->oddEven.val << 7) & 0x80U);
        
        memcpy(itsIE->param_data.transitNetworkSelection.network_id,
               nmsIE->netId.val, nmsIE->netId.len);

        itsIE->param_length += nmsIE->netId.len;
    }
#endif   
#if defined (ANSI)
    itsIE->param_data.transitNetworkSelection.digit2and1 = nmsIE->netId.val[0];
    itsIE->param_data.transitNetworkSelection.digit4and3 = nmsIE->netId.val[1];
    itsIE->param_data.transitNetworkSelection.code = 
        (nmsIE->netId.val[2] << 4) & 0xF0U;

    itsIE->param_length += 3 * sizeof(ITS_OCTET);
#endif
}

static void
TransmitNwSel_ITS_to_NMS(SiTranNetSel* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->netIdPln,
                   itsIE->param_data.transitNetworkSelection.network, 1, 4);
    SetBitsToTknU8(&nmsIE->typNetId, 
                   itsIE->param_data.transitNetworkSelection.network, 5, 7);

#if defined (CCITT)
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.transitNetworkSelection.network, 8, 8);
    
    SetTknStr(&nmsIE->netId,
              itsIE->param_data.transitNetworkSelection.network_id,
              itsIE->param_length - sizeof(ITS_OCTET));
#endif   
#if defined (ANSI)
    /* special case, do it manually */
    /* Note that there are 3-digit transit network selection code and
     * 4-digit transit network selection code. Seems IntelliNet uses the
     * 4-digit one 
     */
    nmsIE->netId.pres = PRESENT;
    nmsIE->netId.len = 3 * sizeof(ITS_OCTET);

    nmsIE->netId.val[0] = itsIE->param_data.transitNetworkSelection.digit2and1;
    nmsIE->netId.val[1] = itsIE->param_data.transitNetworkSelection.digit4and3;
    nmsIE->netId.val[2] = 
        (itsIE->param_data.transitNetworkSelection.code >> 4) & 0x0FU;
#endif
}

/* Call Reference */
static void
CallRef_NMS_to_ITS(SiCallRef* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALL_REF;

    itsIE->param_data.callRef.call_ident[0] = (U8)(nmsIE->callId.val >> 16);
    itsIE->param_data.callRef.call_ident[1] = (U8)(nmsIE->callId.val >> 8);
    itsIE->param_data.callRef.call_ident[2] = (U8)(nmsIE->callId.val);

    MTP3_PC_SET_VALUE(itsIE->param_data.callRef.point_code, nmsIE->pntCde.val);

    itsIE->param_length = 3 * sizeof(ITS_OCTET) + sizeof(MTP3_POINT_CODE);
}

static void
CallRef_ITS_to_NMS(SiCallRef* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU32(&nmsIE->callId, itsIE->param_data.callRef.call_ident, 3);

    SetTknU32(&nmsIE->pntCde, (U8 *)&itsIE->param_data.callRef.point_code,
              sizeof(MTP3_POINT_CODE));
}

/* IE: Calling Party number */
static void
CgPtyNum_NMS_to_ITS(SiCgPtyNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALLING_PARTY_NUM;

    itsIE->param_data.callingPartyNum.addr_ind = nmsIE->natAddrInd.val & 0x7FU;
    itsIE->param_data.callingPartyNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.callingPartyNum.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.callingPartyNum.subfields4 |= 
        ((nmsIE->niInd.val << 7) & 0x80U);
    itsIE->param_data.callingPartyNum.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);
    itsIE->param_data.callingPartyNum.subfields4 |= 
        ((nmsIE->scrnInd.val) & 0x03U);

    memcpy(itsIE->param_data.callingPartyNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}


static void
CgPtyNum_ITS_to_NMS(SiCgPtyNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->natAddrInd, 
                   itsIE->param_data.callingPartyNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.callingPartyNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.callingPartyNum.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->niInd,
                   itsIE->param_data.callingPartyNum.subfields4, 8, 8);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.callingPartyNum.subfields4, 3, 4);
    SetBitsToTknU8(&nmsIE->scrnInd,
                   itsIE->param_data.callingPartyNum.subfields4, 1, 2);

    SetTknStr(&nmsIE->addrSig, 
              itsIE->param_data.callingPartyNum.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Redirecting Number 
 * (same as Original called number, similar to callingPartyNumber)
 */
static void 
RedirectingNum_NMS_to_ITS(SiRedirgNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_REDIRECTING_NUM;
    
    itsIE->param_data.redirectingNum.addr_ind = nmsIE->natAddr.val & 0x7FU;
    itsIE->param_data.redirectingNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.redirectingNum.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.redirectingNum.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);

    memcpy(itsIE->param_data.redirectingNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void 
RedirectingNum_ITS_to_NMS(SiRedirgNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->natAddr,
                   itsIE->param_data.redirectingNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.redirectingNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.redirectingNum.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.redirectingNum.subfields4, 3, 4);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.redirectingNum.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Redirection Information*/
static void 
RedirectionInfo_NMS_to_ITS(SiRedirInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_REDIRECTION_INFO;
    itsIE->param_length = sizeof(ISUP_REDIRECTION_INFO); /* 2 */    
    
    /* bit C B A */
    itsIE->param_data.redirectionInfo.red_info[0] = 
        nmsIE->redirInd.val & 0x07U;

    /* bit H G F E */
    itsIE->param_data.redirectionInfo.red_info[0] |= 
        ((nmsIE->origRedirReas.val << 4) & 0xF0U);

    /* bit K J I */
    itsIE->param_data.redirectionInfo.red_info[1] = 
        nmsIE->redirCnt.val & 0x07U;

    /* bit P O N M */
    itsIE->param_data.redirectionInfo.red_info[1] |= 
        ((nmsIE->redirReas.val << 4) & 0xF0U);
}

static void 
RedirectionInfo_ITS_to_NMS(SiRedirInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    /* bit C B A */
    SetBitsToTknU8(&nmsIE->redirInd,
                   itsIE->param_data.redirectionInfo.red_info[0], 1, 3);

    /* bit H G F E */
    SetBitsToTknU8(&nmsIE->origRedirReas,
                   itsIE->param_data.redirectionInfo.red_info[0], 5, 8);

    /* bit K J I */
    SetBitsToTknU8(&nmsIE->redirCnt,
                   itsIE->param_data.redirectionInfo.red_info[1], 1, 3);

    /* bit P O N M */
    SetBitsToTknU8(&nmsIE->redirReas,
                   itsIE->param_data.redirectionInfo.red_info[1], 5, 8);
}

/* IE: Connection Request */
static void 
ConnReq_NMS_to_ITS(SiConnReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CONNECTION_REQ;      
    
    itsIE->param_data.connectionRequest.call_ident[0] = 
        (U8)(nmsIE->locRef.val >> 16);
    itsIE->param_data.connectionRequest.call_ident[1] = 
        (U8)(nmsIE->locRef.val >> 8);
    itsIE->param_data.connectionRequest.call_ident[2] = 
        (U8)(nmsIE->locRef.val);

    itsIE->param_data.connectionRequest.protocol_class = (nmsIE->protClass.val);
    itsIE->param_data.connectionRequest.credit = (nmsIE->credit.val);

    MTP3_PC_SET_VALUE(itsIE->param_data.connectionRequest.point_code,
                      nmsIE->pntCde.val);

    itsIE->param_length = 5 * sizeof(ITS_OCTET) + sizeof(MTP3_POINT_CODE);
}


static void 
ConnReq_ITS_to_NMS(SiConnReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;     
    
    SetTknU32(&nmsIE->locRef, 
              itsIE->param_data.connectionRequest.call_ident, 3);

    SetTknU8(&nmsIE->protClass, 
             itsIE->param_data.connectionRequest.protocol_class);
    SetTknU8(&nmsIE->credit, 
             itsIE->param_data.connectionRequest.credit);

    SetTknU32(&nmsIE->pntCde, 
              (U8 *)&itsIE->param_data.connectionRequest.point_code,
              sizeof(MTP3_POINT_CODE));
}

/* IE: Original called number
 * (same as Redirecting Number, similar to callingPartyNumber)
 */
static void 
OrigCdNum_NMS_to_ITS(SiOrigCdNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ORIG_CALLED_NUM;
    
    itsIE->param_data.origCalledNum.addr_ind = nmsIE->natAddr.val & 0x7FU;
    itsIE->param_data.origCalledNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.origCalledNum.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.origCalledNum.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);

    memcpy(itsIE->param_data.origCalledNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void 
OrigCdNum_ITS_to_NMS(SiOrigCdNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->natAddr,
                   itsIE->param_data.origCalledNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.origCalledNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.origCalledNum.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.origCalledNum.subfields4, 3, 4);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.origCalledNum.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Access transport */
static void 
AccessTrnspt_NMS_to_ITS(SiAccTrnspt* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ACCESS_TRANSPORT;

    memcpy(itsIE->param_data.accessTransport.acc_transport, 
           nmsIE->infoElmts.val, nmsIE->infoElmts.len);

    itsIE->param_length = nmsIE->infoElmts.len; 
}

static void 
AccessTrnspt_ITS_to_NMS(SiAccTrnspt* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknStr(&nmsIE->infoElmts,
              itsIE->param_data.accessTransport.acc_transport,
              itsIE->param_length);
}

/* IE: User Service Information */
static void 
UsrServInfo_NMS_to_ITS(SiUsrServInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_USER_SERVICE_INFO;    
    itsIE->param_length = sizeof(ISUP_USER_SERVICE_INFO);  

    itsIE->param_data.userServiceInfo.coding = 
        (nmsIE->cdeStand.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfo.coding |= 
        (nmsIE->infoTranCap.val) & 0x1FU;

    itsIE->param_data.userServiceInfo.trans_mode = 
        (nmsIE->tranMode.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfo.trans_mode |= 
        (nmsIE->infoTranRate0.val) & 0x1FU;

    itsIE->param_data.userServiceInfo.config = 
        (nmsIE->chanStruct.val << 4) & 0x70U;
    itsIE->param_data.userServiceInfo.config |= 
        (nmsIE->config.val << 2) & 0x0CU;
    itsIE->param_data.userServiceInfo.config |= 
        (nmsIE->establish.val) & 0x03U;

    itsIE->param_data.userServiceInfo.symmetry = 
        (nmsIE->symmetry.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfo.symmetry |= 
        (nmsIE->infoTranRate1.val) & 0x1FU;

    /* Seems there is no rate_multiplier (ANSI only) field in nms */

    /* layer 1 is very complicated */
    itsIE->param_data.userServiceInfo.layer1 = 
        (nmsIE->usrInfLyr1Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfo.layer1 |= 
        ((nmsIE->lyr1Ident.val << 5) & 0x60U);

    /* layer1 ext: OCTET 3A: synch/asynch, negotiation, User rate */
    itsIE->param_data.userServiceInfo.layer1_ext_user_rate = 
        ((nmsIE->usrRate.val) & 0x1FU);
    itsIE->param_data.userServiceInfo.layer1_ext_user_rate |= 
        ((nmsIE->negot.val << 5) & 0x20U);
    itsIE->param_data.userServiceInfo.layer1_ext_user_rate |= 
        ((nmsIE->syncAsync.val << 6) & 0x40U);

    /* layer1 ext: OCTET 3B: Intermediate rate etc.  */
    itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b = 
        ((nmsIE->flcOnRx.val) & 0x02U);
    itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->flcOnTx.val << 2) & 0x04U);
    itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->niClkOnRx.val << 3) & 0x08U);
    itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->niClkOnTx.val << 4) & 0x10U);
    itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->interRate.val << 5) & 0x60U);

    /* why don't have layer ext(one octet): Hdr/no Hdr, multi frame, mode.?? */

    /* layer1 ext: OCTET 3C: Parity etc.  */
    itsIE->param_data.userServiceInfo.layer1_ext_parity = 
        ((nmsIE->parity.val) & 0x07U);
    itsIE->param_data.userServiceInfo.layer1_ext_parity |= 
        ((nmsIE->nmbDatBits.val << 3) & 0x18U);
    itsIE->param_data.userServiceInfo.layer1_ext_parity |= 
        ((nmsIE->nmbStpBits.val << 5) & 0x60U);

    /* layer1 ext: OCTET 3D: Duplex mode, modem type */
    itsIE->param_data.userServiceInfo.layer1_ext_modem_type = 
        ((nmsIE->modemType.val) & 0x3FU);
    itsIE->param_data.userServiceInfo.layer1_ext_modem_type |= 
        ((nmsIE->duplexMode.val << 6) & 0x40U);

    itsIE->param_data.userServiceInfo.layer2 = 
        (nmsIE->usrInfLyr2Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfo.layer2 |= 
        ((nmsIE->lyr2Ident.val << 5) & 0x60U);

    itsIE->param_data.userServiceInfo.layer3 = 
        (nmsIE->usrInfLyr3Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfo.layer3 |= 
        ((nmsIE->lyr3Ident.val << 5) & 0x60U);
}

static void 
UsrServInfo_ITS_to_NMS(SiUsrServInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->cdeStand,
                   itsIE->param_data.userServiceInfo.coding, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranCap,
                   itsIE->param_data.userServiceInfo.coding, 1, 5);

    SetBitsToTknU8(&nmsIE->tranMode,
                   itsIE->param_data.userServiceInfo.trans_mode, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranRate0,
                   itsIE->param_data.userServiceInfo.trans_mode, 1, 5);

    SetBitsToTknU8(&nmsIE->chanStruct,
                   itsIE->param_data.userServiceInfo.config, 5, 7);
    SetBitsToTknU8(&nmsIE->config,
                   itsIE->param_data.userServiceInfo.config, 3, 4);
    SetBitsToTknU8(&nmsIE->establish,
                   itsIE->param_data.userServiceInfo.config, 1, 2);

    SetBitsToTknU8(&nmsIE->symmetry,
                   itsIE->param_data.userServiceInfo.symmetry, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranRate1,
                   itsIE->param_data.userServiceInfo.symmetry, 1, 5);

    /* Seems there is no rate_multiplier (ANSI only) field in nms */

    /*
     * ANSI T1.113.3-30 Note 1: If the transfer mode is "circuit mode"
     * and if the information capability is "unrestricted digital
     * information" or "restricted digital information" and if the
     * user information layer 1 protocol is not to be identified to the
     * network, then octet 3 shall be omitted. If the transfer mode is
     * packet mode, octet 3 may be omitted. Otherwise, octet 3 shall be
     * present.
     */
    if ((GET_USI_OCTET2_M0DE(itsIE->param_data.userServiceInfo)
         == USI_CIRCUIT_MODE) &&
        ((GET_USI_OCTET1_CAP(itsIE->param_data.userServiceInfo)
          == USI_DIGITAL_N_RES) ||
         (GET_USI_OCTET1_CAP(itsIE->param_data.userServiceInfo)
          ==  USI_DIGITAL_W_RES)))
    {
        return;
    }

    /* layer 1 is very complicated */
    SetBitsToTknU8(&nmsIE->usrInfLyr1Prot,
                   itsIE->param_data.userServiceInfo.layer1, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr1Ident,
                   itsIE->param_data.userServiceInfo.layer1, 6, 7);

    /* layer1 ext: OCTET 3A: synch/asynch, negotiation, User rate */
    SetBitsToTknU8(&nmsIE->usrRate,
                   itsIE->param_data.userServiceInfo.layer1_ext_user_rate, 
                   1, 5);
    SetBitsToTknU8(&nmsIE->negot,
                   itsIE->param_data.userServiceInfo.layer1_ext_user_rate, 
                   6, 6);
    SetBitsToTknU8(&nmsIE->syncAsync,
                   itsIE->param_data.userServiceInfo.layer1_ext_user_rate, 
                   7, 7);

    /* layer1 ext: OCTET 3B: Intermediate rate etc.  */
    SetBitsToTknU8(&nmsIE->flcOnRx,
                  itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b,                  2, 2);
    SetBitsToTknU8(&nmsIE->flcOnTx,
                  itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b,
                  3, 3);
    SetBitsToTknU8(&nmsIE->niClkOnRx,
                  itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b,
                  4, 4);
    SetBitsToTknU8(&nmsIE->niClkOnTx,
                  itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b,
                  5, 5);
    SetBitsToTknU8(&nmsIE->interRate,
                  itsIE->param_data.userServiceInfo.layer1_ext_rate_adaption_3b,
                  6, 7);

    /* why don't have layer ext(one octet): Hdr/no Hdr, multi frame, mode.?? */

    /* layer1 ext: OCTET 3C: Parity etc.  */
    SetBitsToTknU8(&nmsIE->parity,
                   itsIE->param_data.userServiceInfo.layer1_ext_parity, 1, 3);
    SetBitsToTknU8(&nmsIE->nmbDatBits,
                   itsIE->param_data.userServiceInfo.layer1_ext_parity, 4, 5);
    SetBitsToTknU8(&nmsIE->nmbStpBits,
                   itsIE->param_data.userServiceInfo.layer1_ext_parity, 6, 7);

    /* layer1 ext: OCTET 3D: Duplex mode, modem type */
    SetBitsToTknU8(&nmsIE->modemType,
                   itsIE->param_data.userServiceInfo.layer1_ext_modem_type, 
                   1, 6);
    SetBitsToTknU8(&nmsIE->duplexMode,
                   itsIE->param_data.userServiceInfo.layer1_ext_modem_type, 
                   7, 7);

    SetBitsToTknU8(&nmsIE->usrInfLyr2Prot,
                   itsIE->param_data.userServiceInfo.layer2, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr2Ident,
                   itsIE->param_data.userServiceInfo.layer2, 6, 7);

    SetBitsToTknU8(&nmsIE->usrInfLyr3Prot,
                   itsIE->param_data.userServiceInfo.layer3, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr3Ident,
                   itsIE->param_data.userServiceInfo.layer3, 6, 7);
}

/* IE: Generic digits */
static void 
GenericDgts_NMS_to_ITS(SiGenDigits* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_GENERIC_DIGITS;

    itsIE->param_data.genericDigits.type_scheme = 
        nmsIE->typeOfDigits.val & 0x1FU;
    itsIE->param_data.genericDigits.type_scheme |= 
        ((nmsIE->encodeScheme.val << 5) & 0xE0U);

    memcpy(itsIE->param_data.genericDigits.digits,
           nmsIE->digits.val, nmsIE->digits.len);

    itsIE->param_length = sizeof(ITS_OCTET) + nmsIE->digits.len;
}

static void 
GenericDgts_ITS_to_NMS(SiGenDigits* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->typeOfDigits,
                   itsIE->param_data.genericDigits.type_scheme, 1, 5);
    SetBitsToTknU8(&nmsIE->encodeScheme,
                   itsIE->param_data.genericDigits.type_scheme, 6, 8);

    SetTknStr(&nmsIE->digits,
              itsIE->param_data.genericDigits.digits,
              itsIE->param_length - sizeof(ITS_OCTET));
}

/* IE: Service activation */
static void 
ServActivation_NMS_to_ITS(SiServiceAct* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SERVICE_ACTIVATION;    
    
    memcpy(itsIE->param_data.servactivation.data,
           nmsIE->serviceAct.val, nmsIE->serviceAct.len);

    itsIE->param_length = nmsIE->serviceAct.len;
}

static void 
ServActivation_ITS_to_NMS(SiServiceAct* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;   
    
    SetTknStr(&nmsIE->serviceAct,
              itsIE->param_data.servactivation.data,
              itsIE->param_length);
}

/* IE: Information request indicator */
static void
InfoReqInd_NMS_to_ITS(SiInfoReqInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_INFO_REQ_INDICATORS;
    itsIE->param_length = sizeof(ISUP_INFORMATION_REQUEST_INDICATORS);

    /* bit A */
    itsIE->param_data.informationRequestIndicators.indics[0] = 
        nmsIE->cgPtyAdReqInd.val & 0x01U;

    /* bit B */
    itsIE->param_data.informationRequestIndicators.indics[0] |= 
        ((nmsIE->holdingInd.val << 1) & 0x02U);

    /* bit D */
    itsIE->param_data.informationRequestIndicators.indics[0] |= 
        ((nmsIE->cgPtyCatReqInd.val << 3) & 0x08U);

    /* bit E */
    itsIE->param_data.informationRequestIndicators.indics[0] |= 
        ((nmsIE->chrgInfoReqInd.val << 4) & 0x10U);

    /* bit H */
    itsIE->param_data.informationRequestIndicators.indics[0] |= 
        ((nmsIE->malCaIdReqInd.val << 7) & 0x80U);

#if defined (ANSI)
    /* bit P */
    itsIE->param_data.informationRequestIndicators.indics[1] = 
        (nmsIE->mlbgInfoInd.val & 0x80U);
#endif
    
    /* all other bits are either spare or reserved */
}

static void
InfoReqInd_ITS_to_NMS(SiInfoReqInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A */
    SetBitsToTknU8(&nmsIE->cgPtyAdReqInd,
                   itsIE->param_data.informationRequestIndicators.indics[0], 
                   1, 1);

    /* bit B */
    SetBitsToTknU8(&nmsIE->holdingInd,
                   itsIE->param_data.informationRequestIndicators.indics[0], 
                   2, 2);

    /* bit D */
    SetBitsToTknU8(&nmsIE->cgPtyCatReqInd,
                   itsIE->param_data.informationRequestIndicators.indics[0], 
                   4, 4);

    /* bit E */
    SetBitsToTknU8(&nmsIE->chrgInfoReqInd,
                   itsIE->param_data.informationRequestIndicators.indics[0], 
                   5, 5);

    /* bit H */
    SetBitsToTknU8(&nmsIE->malCaIdReqInd,
                   itsIE->param_data.informationRequestIndicators.indics[0], 
                   8, 8);

#if defined (ANSI)
    /* bit P */
    SetBitsToTknU8(&nmsIE->mlbgInfoInd,
                   itsIE->param_data.informationRequestIndicators.indics[1], 
                   8, 8);
#endif
    
    /* all other bits are either spare or reserved */
}

/*
** CCITT specific IEs
**
*/
#if defined(CCITT)
/* Access delivery info */
static void
AccessDeliverInfo_NMS_to_ITS(SiAccDelInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ACCESS_DELIVERY_INFO;
    itsIE->param_length = sizeof(ISUP_ACCESS_DELIVERY_INFO);

    /* bit A */
    itsIE->param_data.accessDeliveryInfo.info = nmsIE->delInd.val & 0x01U;

    /* bits H-B not used */
}

static void
AccessDeliverInfo_ITS_to_NMS(SiAccDelInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A */
    SetBitsToTknU8(&nmsIE->delInd,
                   itsIE->param_data.accessDeliveryInfo.info, 1, 1);

    /* bits H-B not used */
}

/* Call diversion information */
static void
CallDiversionInfo_NMS_to_ITS(SiCllDiverInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALL_DIVERSION_INFO;
    itsIE->param_length = sizeof(ISUP_CALL_DIVERSION_INFO);
    
    /* bit C B A */
    itsIE->param_data.callDiversionInfo.div_info = 
        nmsIE->notSuscr.val & 0x07U;

    /* bit G F E D */
    itsIE->param_data.callDiversionInfo.div_info |= 
        ((nmsIE->redirRsn.val << 3) & 0x78U);
}

static void
CallDiversionInfo_ITS_to_NMS(SiCllDiverInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    /* bit C B A */
    SetBitsToTknU8(&nmsIE->notSuscr,
                   itsIE->param_data.callDiversionInfo.div_info, 1 , 3);

    /* bit G F E D */
    SetBitsToTknU8(&nmsIE->redirRsn,
                   itsIE->param_data.callDiversionInfo.div_info, 4, 7);
}

/* Call history info */
static void
CallHistoryInfo_NMS_to_ITS(SiPropDly* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CALL_HISTORY_INFO;
    itsIE->param_length = sizeof(ISUP_CALL_HISTORY_INFO);

    itsIE->param_data.callHistoryInfo.prop_delay[0] = 
        (U8)(nmsIE->delayVal.val >> 8);
    itsIE->param_data.callHistoryInfo.prop_delay[1] = 
        (U8)(nmsIE->delayVal.val);
}

static void
CallHistoryInfo_ITS_to_NMS(SiPropDly* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU16(&nmsIE->delayVal,
              itsIE->param_data.callHistoryInfo.prop_delay, 2);
}

/* Connected Number */
static void
ConnectedNum_NMS_to_ITS(SiConnectedNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CONNECTED_NUM;
    
    itsIE->param_data.connectedNum.addr_ind = nmsIE->natAddr.val & 0x7FU;
    itsIE->param_data.connectedNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.connectedNum.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.connectedNum.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);
    itsIE->param_data.connectedNum.subfields4 |= 
        ((nmsIE->scrnInd.val) & 0x03U);

    memcpy(itsIE->param_data.connectedNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
ConnectedNum_ITS_to_NMS(SiConnectedNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->natAddr,
                   itsIE->param_data.connectedNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.connectedNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.connectedNum.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.connectedNum.subfields4, 3, 4);
    SetBitsToTknU8(&nmsIE->scrnInd,
                   itsIE->param_data.connectedNum.subfields4, 1, 2);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.connectedNum.dgts, 
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Closed user group interlock code */
static void 
ClosedUserGrpInterLockCode_NMS_to_ITS(SiCugIntCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE;
    itsIE->param_length = sizeof(ISUP_CLOSED_USR_GRP_INTRLCK_CODE);    
    
    itsIE->param_data.interlockCode.digits[0] = 
        ( (nmsIE->dig2.val & 0x0FU) | ((nmsIE->dig1.val << 4) & 0xF0U) );

    itsIE->param_data.interlockCode.digits[1] = 
        ( (nmsIE->dig4.val & 0x0FU) | ((nmsIE->dig3.val << 4) & 0xF0U) );

    itsIE->param_data.interlockCode.code[0] = (U8)(nmsIE->binCde.val >> 8);
    itsIE->param_data.interlockCode.code[1] = (U8)(nmsIE->binCde.val);
}

static void 
ClosedUserGrpInterLockCode_ITS_to_NMS(SiCugIntCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->dig1,
                   itsIE->param_data.interlockCode.digits[0], 5, 8);
    SetBitsToTknU8(&nmsIE->dig2,
                   itsIE->param_data.interlockCode.digits[0], 1, 4);

    SetBitsToTknU8(&nmsIE->dig3,
                   itsIE->param_data.interlockCode.digits[1], 5, 8);
    SetBitsToTknU8(&nmsIE->dig4,
                   itsIE->param_data.interlockCode.digits[1], 1, 4);
    
    SetTknU16(&nmsIE->binCde, itsIE->param_data.interlockCode.code, 2);
}

/* Echo control info */
static void 
EchoCtrlInfo_NMS_to_ITS(SiEchoCtl* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ECHO_CTRL_INFO;
    itsIE->param_length = sizeof(ISUP_ECHO_CONTROL_INFO);

    /* bit B A */
    itsIE->param_data.echoControlInfo.info = nmsIE->outEchoRsp.val & 0x03U;

    /* bit D C */
    itsIE->param_data.echoControlInfo.info |= 
        ((nmsIE->incEchoRsp.val << 2) & 0x0CU);

    /* bit F E */
    itsIE->param_data.echoControlInfo.info |= 
        ((nmsIE->outEchoReq.val << 4) & 0x30U);

    /* bit H G */
    itsIE->param_data.echoControlInfo.info |= 
        ((nmsIE->incEchoReq.val << 6) & 0xC0U);
}

static void 
EchoCtrlInfo_ITS_to_NMS(SiEchoCtl* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit B A */
    SetBitsToTknU8(&nmsIE->outEchoRsp,
                   itsIE->param_data.echoControlInfo.info, 1, 2);

    /* bit D C */
    SetBitsToTknU8(&nmsIE->incEchoRsp,
                   itsIE->param_data.echoControlInfo.info, 3, 4);

    /* bit F E */
    SetBitsToTknU8(&nmsIE->outEchoReq,
                   itsIE->param_data.echoControlInfo.info, 5, 6);

    /* bit H G */
    SetBitsToTknU8(&nmsIE->incEchoReq,
                   itsIE->param_data.echoControlInfo.info, 7, 8);
}

/* Facility indicator */
static void
FacilityInd_NMS_to_ITS(SiFacInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_FACILITY_INDICATOR;
    itsIE->param_length = sizeof(ISUP_FACILITY_INDICATOR);    
      
    itsIE->param_data.facilityIndicator.fac_ind = nmsIE->facInd.val;
}

static void
FacilityInd_ITS_to_NMS(SiFacInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
      
    SetTknU8(&nmsIE->facInd, itsIE->param_data.facilityIndicator.fac_ind);
}

/* IE: Generic Notification indicator */
static void 
GenericNotifInd_NMS_to_ITS(SiNotifInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_GENERIC_NOTIFICATION;
    itsIE->param_length = sizeof(ISUP_GENERIC_NOTIFICATION_INDICATOR);
    
    /* the nms ie only contain one byte of notifInd */
    itsIE->param_data.genericNotificationIndicator.indicators[0] = 
        nmsIE->notifInd.val; 
    itsIE->param_data.genericNotificationIndicator.indicators[0] |= 0x80U;
}

static void 
GenericNotifInd_ITS_to_NMS(SiNotifInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    ITS_OCTET octet;

    nmsIE->eh.pres = PRESENT;
    
    /* the nms ie only contain one byte of notifInd, so ext = 1 */
    octet = 
        itsIE->param_data.genericNotificationIndicator.indicators[0] | 0x80U;

    SetTknU8(&nmsIE->notifInd, octet); 
}

/* IE: Generic number */
static void
GenericNum_NMS_to_ITS(SiGenNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_GENERIC_NUM;

    itsIE->param_data.genericNumber.qualifier = nmsIE->nmbQual.val;
    itsIE->param_data.genericNumber.nature = nmsIE->natAddrInd.val & 0x7FU;
    itsIE->param_data.genericNumber.nature |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.genericNumber.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.genericNumber.subfields4 |= 
        ((nmsIE->niInd.val << 7) & 0x80U);
    itsIE->param_data.genericNumber.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);
    itsIE->param_data.genericNumber.subfields4 |= 
        ((nmsIE->scrnInd.val) & 0x03U);

    memcpy(itsIE->param_data.genericNumber.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 3 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
GenericNum_ITS_to_NMS(SiGenNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->nmbQual, itsIE->param_data.genericNumber.qualifier);

    SetBitsToTknU8(&nmsIE->natAddrInd,
                   itsIE->param_data.genericNumber.nature, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.genericNumber.nature, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.genericNumber.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->niInd,
                   itsIE->param_data.genericNumber.subfields4, 8, 8);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.genericNumber.subfields4, 3, 4);
    SetBitsToTknU8(&nmsIE->scrnInd,
                   itsIE->param_data.genericNumber.subfields4, 1, 2);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.genericNumber.dgts,
              itsIE->param_length - 3 * sizeof(ITS_OCTET));
}

/* IE: Location number(same as calling party number) */
static void
LocationNum_NMS_to_ITS(SiLocNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_LOCATION_NUM;
    
    itsIE->param_data.locationNumber.addr_ind = nmsIE->natAddrInd.val & 0x7FU;
    itsIE->param_data.locationNumber.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.locationNumber.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.locationNumber.subfields4 |= 
        ((nmsIE->niInd.val << 7) & 0x80U);
    itsIE->param_data.locationNumber.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);
    itsIE->param_data.locationNumber.subfields4 |= 
        ((nmsIE->scrnInd.val) & 0x03U);

    memcpy(itsIE->param_data.locationNumber.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
LocationNum_ITS_to_NMS(SiLocNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->natAddrInd,
                   itsIE->param_data.locationNumber.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.locationNumber.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.locationNumber.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->niInd,
                   itsIE->param_data.locationNumber.subfields4, 8, 8);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.locationNumber.subfields4, 3, 4);
    SetBitsToTknU8(&nmsIE->scrnInd,
                   itsIE->param_data.locationNumber.subfields4, 1, 2);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.locationNumber.dgts, 
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* MCID response indicator */
static void
MCIDRspInd_NMS_to_ITS(SiMcidRspInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_MCID_RESP_INDICATOR;
    itsIE->param_length = sizeof(ISUP_MCID_RESPONSE_INDICATORS);
    
    /* bit A */
    itsIE->param_data.mcidResponseIndicators.indics = 
        nmsIE->rspInd.val & 0x01U;

    /* bit B */
    itsIE->param_data.mcidResponseIndicators.indics |= 
        ((nmsIE->hldInd.val << 1) & 0x02U);

    /* all other bits are spared */
}

static void
MCIDRspInd_ITS_to_NMS(SiMcidRspInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    /* bit A */
    SetBitsToTknU8(&nmsIE->rspInd,
                   itsIE->param_data.mcidResponseIndicators.indics, 1, 1);

    /* bit B */
    SetBitsToTknU8(&nmsIE->hldInd,
                   itsIE->param_data.mcidResponseIndicators.indics, 2, 2);

    /* all other bits are spared */
}

/* MCID request indicator */
static void
MCIDReqInd_NMS_to_ITS(SiMcidReqInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_MCID_REQ_INDICATOR;
    itsIE->param_length = sizeof(ISUP_MCID_REQUEST_INDICATORS);
    
    /* bit A */
    itsIE->param_data.mcidRequestIndicators.indics = 
        nmsIE->reqInd.val & 0x01U;

    /* bit B */
    itsIE->param_data.mcidRequestIndicators.indics |= 
        ((nmsIE->hldInd.val << 1) & 0x02U);

    /* all other bits are spared */
}

static void
MCIDReqInd_ITS_to_NMS(SiMcidReqInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    /* bit A */
    SetBitsToTknU8(&nmsIE->reqInd,
                   itsIE->param_data.mcidRequestIndicators.indics, 1, 1);

    /* bit B */
    SetBitsToTknU8(&nmsIE->hldInd,
                   itsIE->param_data.mcidRequestIndicators.indics, 2, 2);

    /* all other bits are spared */
}

/* IE: MLPP Precedence */
static void 
MLPPPrecedence_NMS_to_ITS(SiMlppPrec* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_MLPP_PRECEDENCE;    
    itsIE->param_length = sizeof(ISUP_MLPP_PRECEDENCE); /*fixed len*/
    
    itsIE->param_data.mlppPrecedence.lfbLevel = nmsIE->precdLvl.val & 0x0FU;
    itsIE->param_data.mlppPrecedence.lfbLevel |= 
        ((nmsIE->lfb.val << 5) & 0x60U);

    /* 1st and 2nd NI digit */
    itsIE->param_data.mlppPrecedence.ni[0] = 
        ((nmsIE->frstDig.val << 5) & 0xF0U) | (nmsIE->scndDig.val & 0x0FU);

    /* 3rd and 4th NI digit */
    itsIE->param_data.mlppPrecedence.ni[1] = 
        ((nmsIE->thrdDig.val << 5) & 0xF0U) | (nmsIE->frthDig.val & 0x0FU);

    itsIE->param_data.mlppPrecedence.domain[0] = 
        (U8)(nmsIE->servDomain.val >> 16);
    itsIE->param_data.mlppPrecedence.domain[1] = 
        (U8)(nmsIE->servDomain.val >> 8);
    itsIE->param_data.mlppPrecedence.domain[2] = (U8)(nmsIE->servDomain.val);
}

static void 
MLPPPrecedence_ITS_to_NMS(SiMlppPrec* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->precdLvl,
                   itsIE->param_data.mlppPrecedence.lfbLevel, 1, 4);
    SetBitsToTknU8(&nmsIE->lfb,
                   itsIE->param_data.mlppPrecedence.lfbLevel, 6, 7);

    /* 1st and 2nd NI digit */
    SetBitsToTknU8(&nmsIE->frstDig,
                   itsIE->param_data.mlppPrecedence.ni[0], 5, 8);
    SetBitsToTknU8(&nmsIE->scndDig,
                   itsIE->param_data.mlppPrecedence.ni[0], 1, 4);

    /* 3rd and 4th NI digit */
    SetBitsToTknU8(&nmsIE->thrdDig,
                   itsIE->param_data.mlppPrecedence.ni[1], 5, 8);
    SetBitsToTknU8(&nmsIE->frthDig,
                   itsIE->param_data.mlppPrecedence.ni[1], 1, 4);

    SetTknU32(&nmsIE->servDomain,
              itsIE->param_data.mlppPrecedence.domain, 3);
}

/* Message compatibilty info */
static void
MsgCompatInfo_NMS_to_ITS(SiMsgCompInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_MSG_COMPAT_INFO;
    
    itsIE->param_length = 0; /* will be updated later */
    
    /* The nms SiMsgCompInfo IE struct contains two bytes,
     * so there is no "More insturction indicators".
     * We populate two bytes(at most) in our data too.
     */
    /* The first byte exist ? */

    if (nmsIE->tranXInd.pres == PRESENT)
    {
        /* bit A */
        itsIE->param_data.msgCompatibilityInfo.data[0] = 
            nmsIE->tranXInd.val & 0x01U;

        /* bit B */
        itsIE->param_data.msgCompatibilityInfo.data[0] |= 
            ((nmsIE->relCllInd.val << 1)  & 0x02U);

        /* bit C */
        itsIE->param_data.msgCompatibilityInfo.data[0] |= 
            ((nmsIE->sndNotInd.val << 2)  & 0x04U);

        /* bit D */
        itsIE->param_data.msgCompatibilityInfo.data[0] |= 
            ((nmsIE->dcrdMsgInd.val << 3)  & 0x08U);

        /* bit E */
        itsIE->param_data.msgCompatibilityInfo.data[0] |= 
            ((nmsIE->passNotPoss.val << 4)  & 0x10U);

        /* bit G-F spare, bit H extension indicator, not used by nms */
        
        itsIE->param_length += sizeof(ITS_OCTET);
    }

    /* The second byte exist ? */

    if (nmsIE->tranXInd1.pres == PRESENT)
    {
        /* bit A */
        itsIE->param_data.msgCompatibilityInfo.data[1] = 
            nmsIE->tranXInd1.val & 0x01U;

        /* bit B */
        itsIE->param_data.msgCompatibilityInfo.data[1] |= 
            ((nmsIE->relCllInd1.val << 1)  & 0x02U);

        /* bit C */
        itsIE->param_data.msgCompatibilityInfo.data[1] |= 
            ((nmsIE->sndNotInd1.val << 2)  & 0x04U);

        /* bit D */
        itsIE->param_data.msgCompatibilityInfo.data[1] |= 
            ((nmsIE->dcrdMsgInd1.val << 3)  & 0x08U);

        /* bit E */
        itsIE->param_data.msgCompatibilityInfo.data[1] |= 
            ((nmsIE->passNotPoss1.val << 4)  & 0x10U);

        /* bit G-F spare, bit H extension indicator, not used by nms */

        itsIE->param_length += sizeof(ITS_OCTET);
    }
}

static void
MsgCompatInfo_ITS_to_NMS(SiMsgCompInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    int len = itsIE->param_length;

    nmsIE->eh.pres = PRESENT;    
    
    /* The nms SiMsgCompInfo IE struct contains two bytes,
     * so there is no "More insturction indicators".
     * We populate two bytes in our data too.
     */    
    /* The first byte exist ? */    
    if ( len >= 1)
    {
        /* bit A */
        SetBitsToTknU8(&nmsIE->tranXInd,
                       itsIE->param_data.msgCompatibilityInfo.data[0], 1, 1);

        /* bit B */
        SetBitsToTknU8(&nmsIE->relCllInd,
                       itsIE->param_data.msgCompatibilityInfo.data[0], 2, 2);

        /* bit C */
        SetBitsToTknU8(&nmsIE->sndNotInd,
                       itsIE->param_data.msgCompatibilityInfo.data[0], 3, 3);

        /* bit D */
        SetBitsToTknU8(&nmsIE->dcrdMsgInd,
                       itsIE->param_data.msgCompatibilityInfo.data[0], 4, 4);

        /* bit E */
        SetBitsToTknU8(&nmsIE->passNotPoss,
                       itsIE->param_data.msgCompatibilityInfo.data[0], 5, 5);

        /* bit G-F spare, bit H extension indicator, not used by nms */
        
        len -= sizeof(ITS_OCTET);
    }

    /* The second byte exist ? */
    if ( len >= 1)
    {
        /* bit A */
        SetBitsToTknU8(&nmsIE->tranXInd1,
                       itsIE->param_data.msgCompatibilityInfo.data[1], 1, 1);

        /* bit B */
        SetBitsToTknU8(&nmsIE->relCllInd1,
                       itsIE->param_data.msgCompatibilityInfo.data[1], 2, 2);

        /* bit C */
        SetBitsToTknU8(&nmsIE->sndNotInd1,
                       itsIE->param_data.msgCompatibilityInfo.data[1], 3, 3);

        /* bit D */
        SetBitsToTknU8(&nmsIE->dcrdMsgInd1,
                       itsIE->param_data.msgCompatibilityInfo.data[1], 4, 4);

        /* bit E */
        SetBitsToTknU8(&nmsIE->passNotPoss1,
                       itsIE->param_data.msgCompatibilityInfo.data[1], 5, 5);

        /* bit G-F spare, bit H extension indicator, not used by nms */

        /* Don't care if there is more data from itsIE 
         * because nms can only take 2 */
    }

}

/* IE: Network specific facility */
static void 
NwkSpecFac_NMS_to_ITS(SiNetSpecFacil* nmsIE, ITS_ISUP_IE* itsIE)
{
    int nwidlen = 0, nwfaclen = 0, offset = 0;

    itsIE->param_id = ISUP_PRM_NTWK_SPECIFIC_FACILITIES;

    /* This one is complicated too, nms only pass an array */
    /* the lenght of the array should >= 1 */
    if (nmsIE->netFac.len >= 1)
    {
        nwidlen = nmsIE->netFac.val[0];

        /* len of newwork identification */
        itsIE->param_data.networkSpecificFacility.length_ofNtwrkId = nwidlen;            

        if (nwidlen > 0)
        {
            /* type of network id and network identification plan */
            itsIE->param_data.networkSpecificFacility.ntwrk_type_plan = 
                nmsIE->netFac.val[1];

            /* network identification, the length is contained in  
             * nmsIE->netFac.val[0]*/
            memcpy(itsIE->param_data.networkSpecificFacility.ntwrk_id,
                   &nmsIE->netFac.val[2], nwidlen);

            offset += (2 + nwidlen);
            /* the length of network specific facility = length of the TnkStr
             *                              - length of the network iden
             *                              - 2 (the first two fixed bytes)
             */
            nwfaclen = nmsIE->netFac.len - nwidlen - 2;
        }

        /* 
         * If nwidlen == 0, then 2nd octet doesn't exist, so
         * the length of network specific facility = length of the TnkStr - 1
         */
        if (nwidlen == 0)
        {
            offset++;

            nwfaclen = nmsIE->netFac.len - 1;
        }

        if (nwfaclen > 0)
        {        
            memcpy(itsIE->param_data.networkSpecificFacility.ntwrk_facility,
                   &nmsIE->netFac.val[offset], nwfaclen);
        }

        /* since nms only pass an array, the length should be the param_length*/
        itsIE->param_length = nmsIE->netFac.len;
    }
    else
    {
        /* minimum length should be 1 */
        itsIE->param_length = sizeof(ITS_OCTET);
    }
}

static void 
NwkSpecFac_ITS_to_NMS(SiNetSpecFacil* nmsIE, ITS_ISUP_IE* itsIE)
{
    int nwidlen = 0, nwfaclen = 0, offset = 0;

    /* minimum length should be 1 */
    ITS_C_REQUIRE(itsIE->param_length >= 1);

    nmsIE->eh.pres = PRESENT;
    
    /* since itsIE->param_length >= 1, we can proceed */
    nmsIE->netFac.pres = PRESENT;

    /* since nms only pass an array, the length should be the param_length*/
    nmsIE->netFac.len = itsIE->param_length;

    nwidlen = itsIE->param_data.networkSpecificFacility.length_ofNtwrkId;
    nmsIE->netFac.val[0] = nwidlen;    

    /* network identification, the length is contained in  
     * nmsIE->netFac.val[0]*/
    if (nwidlen > 0)
    {
        /* type of network id and network identification plan */
        nmsIE->netFac.val[1] = 
            itsIE->param_data.networkSpecificFacility.ntwrk_type_plan;

        memcpy(&nmsIE->netFac.val[2], 
               itsIE->param_data.networkSpecificFacility.ntwrk_id,
               nwidlen);

        offset = 2 + nwidlen;

        /* the length of network specific facility = length of the itsIE
         *                                  - length of the network iden
         *                                  - 2 (the first two fixed bytes)
         */
        nwfaclen = itsIE->param_length - nwidlen - 2;
    }

    /* 
     * If nwidlen == 0, 2nd octet doesn't exist, so
     * the length of network specific facility = length of the itsIE - 1
     */
    if (nwidlen == 0)
    {
        offset = 1;
        nwfaclen = itsIE->param_length - 1;
    }

    if (nwfaclen > 0)
    {
        memcpy(&nmsIE->netFac.val[offset],
               itsIE->param_data.networkSpecificFacility.ntwrk_facility,
               nwfaclen);
    }
}

/* IE: Optional Forward call indicators */
static void 
OptionalFwdCallInd_NMS_to_ITS(SiOpFwdCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_OPT_FWD_CALL_INDICATORS;
    itsIE->param_length = sizeof(ISUP_OPT_FWD_CALL_INDICATORS);

    /* bit A & B */
    itsIE->param_data.optFwdCallIndicators.indics = 
        nmsIE->clsdUGrpCaInd.val & 0x03U;
    
    /* bit C */
    itsIE->param_data.optFwdCallIndicators.indics |= 
        ((nmsIE->segInd.val << 2) & 0x03U);

    /* bit H */
    itsIE->param_data.optFwdCallIndicators.indics |= 
        ((nmsIE->clidReqInd.val << 7) & 0x80U);
}

static void 
OptionalFwdCallInd_ITS_to_NMS(SiOpFwdCalInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A & B */
    SetBitsToTknU8(&nmsIE->clsdUGrpCaInd,
                   itsIE->param_data.optFwdCallIndicators.indics, 1, 2);
    
    /* bit C */
    SetBitsToTknU8(&nmsIE->segInd,
                   itsIE->param_data.optFwdCallIndicators.indics, 3, 3);

    /* bit H */
    SetBitsToTknU8(&nmsIE->clidReqInd,
                   itsIE->param_data.optFwdCallIndicators.indics, 8, 8);
}

/* IE: Originating ISC point code (MTP3_POINT_CODE) */
static void 
OrigIscPC_NMS_to_ITS(SiSigPointCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ORIG_ISC_PC;
    itsIE->param_length = sizeof(ISUP_ORIG_ISC_POINT_CODE);

    /* the point code contains two bytes */
    itsIE->param_data.origIscPointCode.data[0] = 
        (U8)(nmsIE->sigPointCode.val >> 8);
    itsIE->param_data.origIscPointCode.data[1] = (U8)(nmsIE->sigPointCode.val);
}

static void 
OrigIscPC_ITS_to_NMS(SiSigPointCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* the point code contains two bytes */
    SetTknU32(&nmsIE->sigPointCode,
              itsIE->param_data.origIscPointCode.data, 2);
}

/* IE: Paramter compatibity information */
static void 
ParmCompatInfo_NMS_to_ITS(SiParmCompInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_PARAM_COMPAT_INFO;
   
    if (nmsIE->upgrPar1.pres == PRESENT)
    {
        itsIE->param_data.paramCompatInfo.param_info[0].paramName = 
            nmsIE->upgrPar1.val;
        
        /* bit A */
        itsIE->param_data.paramCompatInfo.param_info[0].instructions[0] = 
            nmsIE->tranXInd1.val & 0x01U;

        /* bit B */
        itsIE->param_data.paramCompatInfo.param_info[0].instructions[0] |= 
            ((nmsIE->relCllInd1.val << 1)  & 0x02U);

        /* bit C */
        itsIE->param_data.paramCompatInfo.param_info[0].instructions[0] |= 
            ((nmsIE->sndNotInd1.val << 2)  & 0x04U);

        /* bit D */
        itsIE->param_data.paramCompatInfo.param_info[0].instructions[0] |= 
            ((nmsIE->dcrdMsgInd1.val << 3)  & 0x08U);

        /* bit E */
        itsIE->param_data.paramCompatInfo.param_info[0].instructions[0] |= 
            ((nmsIE->dcrdParInd1.val << 4)  & 0x10U);

        /* bit G-F spare, bit H extension indicator, not used by nms */

        itsIE->param_length = sizeof(ISUP_PARAM_COMPAT_INFO_DATA);
    }
    if (nmsIE->upgrPar2.pres == PRESENT)
    {
        itsIE->param_data.paramCompatInfo.param_info[1].paramName = 
            nmsIE->upgrPar2.val;
        
        /* bit A */
        itsIE->param_data.paramCompatInfo.param_info[1].instructions[0] = 
            nmsIE->tranXInd2.val & 0x01U;

        /* bit B */
        itsIE->param_data.paramCompatInfo.param_info[1].instructions[0] |= 
            ((nmsIE->relCllInd2.val << 1)  & 0x02U);

        /* bit C */
        itsIE->param_data.paramCompatInfo.param_info[1].instructions[0] |= 
            ((nmsIE->sndNotInd2.val << 2)  & 0x04U);

        /* bit D */
        itsIE->param_data.paramCompatInfo.param_info[1].instructions[0] |= 
            ((nmsIE->dcrdMsgInd2.val << 3)  & 0x08U);

        /* bit E */
        itsIE->param_data.paramCompatInfo.param_info[1].instructions[0] |= 
            ((nmsIE->dcrdParInd2.val << 4)  & 0x10U);

        /* bit G-F spare, bit H extension indicator, not used by nms */

        itsIE->param_length += sizeof(ISUP_PARAM_COMPAT_INFO_DATA);
    }
    if (nmsIE->upgrPar3.pres == PRESENT)
    {
        itsIE->param_data.paramCompatInfo.param_info[2].paramName = 
            nmsIE->upgrPar3.val;
        
        /* bit A */
        itsIE->param_data.paramCompatInfo.param_info[2].instructions[0] = 
            nmsIE->tranXInd3.val & 0x01U;

        /* bit B */
        itsIE->param_data.paramCompatInfo.param_info[2].instructions[0] |= 
            ((nmsIE->relCllInd3.val << 1)  & 0x02U);

        /* bit C */
        itsIE->param_data.paramCompatInfo.param_info[2].instructions[0] |= 
            ((nmsIE->sndNotInd3.val << 2)  & 0x04U);

        /* bit D */
        itsIE->param_data.paramCompatInfo.param_info[2].instructions[0] |= 
            ((nmsIE->dcrdMsgInd3.val << 3)  & 0x08U);

        /* bit E */
        itsIE->param_data.paramCompatInfo.param_info[2].instructions[0] |= 
            ((nmsIE->dcrdParInd3.val << 4)  & 0x10U);

        /* bit G-F spare, bit H extension indicator, not used by nms */

        itsIE->param_length += sizeof(ISUP_PARAM_COMPAT_INFO_DATA);
    }    
}

static void 
ParmCompatInfo_ITS_to_NMS(SiParmCompInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    int totalLen = itsIE->param_length;

    nmsIE->eh.pres = PRESENT;   
    
     /* at least one updated parameter */
    if (totalLen >= sizeof(ISUP_PARAM_COMPAT_INFO_DATA))    
    {
        SetTknU8(&nmsIE->upgrPar1, 
                 itsIE->param_data.paramCompatInfo.param_info[0].paramName);
        
        /* bit A */
        SetBitsToTknU8(&nmsIE->tranXInd1,
             itsIE->param_data.paramCompatInfo.param_info[0].instructions[0],
             1, 1);

        /* bit B */
        SetBitsToTknU8(&nmsIE->relCllInd1,
             itsIE->param_data.paramCompatInfo.param_info[0].instructions[0],
             2, 2);

        /* bit C */
        SetBitsToTknU8(&nmsIE->sndNotInd1,
             itsIE->param_data.paramCompatInfo.param_info[0].instructions[0],
             3, 3);

        /* bit D */
        SetBitsToTknU8(&nmsIE->dcrdMsgInd1,
             itsIE->param_data.paramCompatInfo.param_info[0].instructions[0],
             4, 4);

        /* bit E */
        SetBitsToTknU8(&nmsIE->dcrdParInd1,
             itsIE->param_data.paramCompatInfo.param_info[0].instructions[0],
             5, 5);

        /* bit G-F spare, bit H extension indicator, not used by nms */        
    }

    totalLen -= sizeof(ISUP_PARAM_COMPAT_INFO_DATA);

     /* check whether there is the 2nd updated parameter */
    if (totalLen >= sizeof(ISUP_PARAM_COMPAT_INFO_DATA))      
    {
        SetTknU8(&nmsIE->upgrPar2,
                 itsIE->param_data.paramCompatInfo.param_info[1].paramName);
        
        /* bit A */
        SetBitsToTknU8(&nmsIE->tranXInd2,
             itsIE->param_data.paramCompatInfo.param_info[1].instructions[0],
             1, 1);

        /* bit B */
        SetBitsToTknU8(&nmsIE->relCllInd2,
             itsIE->param_data.paramCompatInfo.param_info[1].instructions[0],
             2, 2);

        /* bit C */
        SetBitsToTknU8(&nmsIE->sndNotInd2,
             itsIE->param_data.paramCompatInfo.param_info[1].instructions[0],
             3, 3);

        /* bit D */
        SetBitsToTknU8(&nmsIE->dcrdMsgInd2,
             itsIE->param_data.paramCompatInfo.param_info[1].instructions[0],
             4, 4);

        /* bit E */
        SetBitsToTknU8(&nmsIE->dcrdParInd2,
             itsIE->param_data.paramCompatInfo.param_info[1].instructions[0],
             5, 5);

        /* bit G-F spare, bit H extension indicator, not used by nms */
    }

    totalLen -= sizeof(ISUP_PARAM_COMPAT_INFO_DATA);

    /* check whether there is the 3rd updated parameter */
    if (totalLen >= sizeof(ISUP_PARAM_COMPAT_INFO_DATA))
    {
        SetTknU8(&nmsIE->upgrPar3,
                 itsIE->param_data.paramCompatInfo.param_info[2].paramName);
        
        /* bit A */
        SetBitsToTknU8(&nmsIE->tranXInd3,
             itsIE->param_data.paramCompatInfo.param_info[2].instructions[0],
              1, 1);

        /* bit B */
        SetBitsToTknU8(&nmsIE->relCllInd3,
             itsIE->param_data.paramCompatInfo.param_info[2].instructions[0],
             2, 2);

        /* bit C */
        SetBitsToTknU8(&nmsIE->sndNotInd3,
             itsIE->param_data.paramCompatInfo.param_info[2].instructions[0],
             3, 3);

        /* bit D */
        SetBitsToTknU8(&nmsIE->dcrdMsgInd3,
             itsIE->param_data.paramCompatInfo.param_info[2].instructions[0],
             4, 4);

        /* bit E */
        SetBitsToTknU8(&nmsIE->dcrdParInd3,
             itsIE->param_data.paramCompatInfo.param_info[2].instructions[0],
             5, 5);

        /* bit G-F spare, bit H extension indicator, not used by nms */
    }  
    /* Note: we don't more possible updated parms because 
     * NMS can only support 3 */
}

/* IE: Propagation delay counter */
static void 
PropagationDelayCounter_NMS_to_ITS(SiPropDly* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_PROP_DELAY_COUNTER;
    itsIE->param_length = sizeof(ISUP_PROP_DELAY_COUNTER);

    itsIE->param_data.propDelayCounter.delay[0] = 
        (U8)(nmsIE->delayVal.val >> 8);
    itsIE->param_data.propDelayCounter.delay[1] = (U8)(nmsIE->delayVal.val);
}

static void 
PropagationDelayCounter_ITS_to_NMS(SiPropDly* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU16(&nmsIE->delayVal, itsIE->param_data.propDelayCounter.delay, 2);
}

/* IE: Redirection Number (same as called party number) */
static void 
RedirectionNum_NMS_to_ITS(SiRedirNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_REDIRECTION_NUM;

    itsIE->param_data.redirectionNum.addr_ind = nmsIE->natAddr.val & 0x7FU;
    itsIE->param_data.redirectionNum.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.redirectionNum.num_plan = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.redirectionNum.num_plan |= 
        ((nmsIE->innInd.val << 7) & 0x80U);

    memcpy(itsIE->param_data.redirectionNum.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void 
RedirectionNum_ITS_to_NMS(SiRedirNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->natAddr,
                   itsIE->param_data.redirectionNum.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.redirectionNum.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.redirectionNum.num_plan, 5, 7);
    SetBitsToTknU8(&nmsIE->innInd,
                   itsIE->param_data.redirectionNum.num_plan, 8, 8);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.redirectionNum.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* Redirection number restriction */
static void 
RedirecNumResrict_NMS_to_ITS(SiRedirRestr* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_REDIRECTION_NUM_RESTRICT;
    itsIE->param_length = sizeof(ISUP_REDIRECTION_RESTRICTION);

    /* bit B A */
    itsIE->param_data.redirectionRestriction.bits = nmsIE->presRest.val & 0x03U;

    /* all other bits are spared */
}

static void 
RedirecNumResrict_ITS_to_NMS(SiRedirRestr* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit B A */
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.redirectionRestriction.bits, 1, 2);

    /* all other bits are spared */
}

/* IE: Remote operations */
static void 
RemoteOper_NMS_to_ITS(SiRemotOper* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_REMOTE_OPS;
    
    itsIE->param_data.remoteOperation.protocol_profile = 
        nmsIE->protProf.val & 0x1FU;

    memcpy(itsIE->param_data.remoteOperation.components,
           nmsIE->compon.val, nmsIE->compon.len);

    itsIE->param_length = sizeof(ITS_OCTET) + nmsIE->compon.len;
}

static void 
RemoteOper_ITS_to_NMS(SiRemotOper* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->protProf,
                   itsIE->param_data.remoteOperation.protocol_profile, 1, 5);

    SetTknStr(&nmsIE->compon,
              itsIE->param_data.remoteOperation.components,
              itsIE->param_length - sizeof(ITS_OCTET));
}

/* Signaling point code */
static void
SingalingPC_NMS_to_ITS(SiSigPointCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SIGNALLING_POINT_CODE;
    itsIE->param_length = sizeof(ISUP_SIGNALLING_POINT_CODE);    
      
    /* the point code contains two bytes */
    itsIE->param_data.signallingPointCode.data[0] = 
        (U8)(nmsIE->sigPointCode.val >> 8);

    itsIE->param_data.signallingPointCode.data[1] = 
        (U8)(nmsIE->sigPointCode.val);
}

static void
SingalingPC_ITS_to_NMS(SiSigPointCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
      
    /* the point code contains two bytes */
    SetTknU32(&nmsIE->sigPointCode,
              itsIE->param_data.signallingPointCode.data, 2);
}

/* Subsequent number */
static void
SubsequentNum_NMS_to_ITS(SiSubNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SUBSEQUENT_NUM;      
    
    itsIE->param_data.subsequentNum.addr_ind = 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    memcpy(itsIE->param_data.subsequentNum.dgts,
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
SubsequentNum_ITS_to_NMS(SiSubNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.subsequentNum.addr_ind, 8, 8);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.subsequentNum.dgts,
              itsIE->param_length - sizeof(ITS_OCTET));
}

/* IE: Transmission medium requirement */
static void
TXMediumRequirement_NMS_to_ITS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_TX_MEDIUM_REQMNT;
    itsIE->param_length = sizeof(ISUP_TX_MEDIUM_REQUIREMENT);

    itsIE->param_data.txMediumRequirement.tmr = nmsIE->trMedReq.val;
}

static void
TXMediumRequirement_ITS_to_NMS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->trMedReq, itsIE->param_data.txMediumRequirement.tmr);
}

/* IE: Transmission medium requirement prime 
 * (same as transmission medium requirement)
 */
static void
TxMdumReqPrime_NMS_to_ITS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_TX_MEDIUM_REQMNT_PRIME;
    itsIE->param_length = sizeof(ISUP_TX_MEDIUM_REQUIREMENT_PRIME);

    itsIE->param_data.txMediumRequirementPrime.tmr = nmsIE->trMedReq.val;
}

static void
TxMdumReqPrime_ITS_to_NMS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->trMedReq, itsIE->param_data.txMediumRequirementPrime.tmr);
}

/* Transmission medium used */
static void
TXMediumUsed_NMS_to_ITS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_TX_MEDIUM_USED;
    itsIE->param_length = sizeof(ISUP_TX_MEDIUM_USED);

    itsIE->param_data.txMediumUsed.tmr = nmsIE->trMedReq.val;
}

static void
TXMediumUsed_ITS_to_NMS(SiTxMedReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->trMedReq, itsIE->param_data.txMediumUsed.tmr);
}

/* IE: User Service Information Prime (same as User Service info) */
static void 
UsrServInfoPrime_NMS_to_ITS(SiUsrServInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_USER_SERVICE_INFO_PRIME;    
    itsIE->param_length = sizeof(ISUP_USER_SERVICE_INFO_PRIME);    

    itsIE->param_data.userServiceInfoPrime.coding = 
        (nmsIE->cdeStand.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfoPrime.coding |= 
        (nmsIE->infoTranCap.val) & 0x1FU;

    itsIE->param_data.userServiceInfoPrime.trans_mode = 
        (nmsIE->tranMode.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfoPrime.trans_mode |= 
        (nmsIE->infoTranRate0.val) & 0x1FU;

    itsIE->param_data.userServiceInfoPrime.config = 
        (nmsIE->chanStruct.val << 4) & 0x70U;
    itsIE->param_data.userServiceInfoPrime.config |= 
        (nmsIE->config.val << 2) & 0x0CU;
    itsIE->param_data.userServiceInfoPrime.config |= 
        (nmsIE->establish.val) & 0x03U;

    itsIE->param_data.userServiceInfoPrime.symmetry = 
        (nmsIE->symmetry.val << 5) & 0x60U;
    itsIE->param_data.userServiceInfoPrime.symmetry |= 
        (nmsIE->infoTranRate1.val) & 0x1FU;

    /* Seems there is no rate_multiplier (ANSI only) field in nms */

    /* layer 1 is very complicated */
    itsIE->param_data.userServiceInfoPrime.layer1 = 
        (nmsIE->usrInfLyr1Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfoPrime.layer1 |= 
        ((nmsIE->lyr1Ident.val << 5) & 0x60U);

    /* layer1 ext: OCTET 3A: synch/asynch, negotiation, User rate */
    itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate = 
        ((nmsIE->usrRate.val) & 0x1FU);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate |= 
        ((nmsIE->negot.val << 5) & 0x20U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate |= 
        ((nmsIE->syncAsync.val << 6) & 0x40U);

    /* layer1 ext: OCTET 3B: Intermediate rate etc.  */
    itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b = 
        ((nmsIE->flcOnRx.val) & 0x02U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->flcOnTx.val << 2) & 0x04U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->niClkOnRx.val << 3) & 0x08U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->niClkOnTx.val << 4) & 0x10U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b |= 
        ((nmsIE->interRate.val << 5) & 0x60U);

    /* why don't have layer ext(one octet): Hdr/no Hdr, multi frame, mode?? */

    /* layer1 ext: OCTET 3C: Parity etc.  */
    itsIE->param_data.userServiceInfoPrime.layer1_ext_parity = 
        ((nmsIE->parity.val) & 0x07U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_parity |= 
        ((nmsIE->nmbDatBits.val << 3) & 0x18U);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_parity |= 
        ((nmsIE->nmbStpBits.val << 5) & 0x60U);

    /* layer1 ext: OCTET 3D: Duplex mode, modem type */
    itsIE->param_data.userServiceInfoPrime.layer1_ext_modem_type = 
        ((nmsIE->modemType.val) & 0x3FU);
    itsIE->param_data.userServiceInfoPrime.layer1_ext_modem_type |= 
        ((nmsIE->duplexMode.val << 6) & 0x40U);

    itsIE->param_data.userServiceInfoPrime.layer2 = 
        (nmsIE->usrInfLyr2Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfoPrime.layer2 |= 
        ((nmsIE->lyr2Ident.val << 5) & 0x60U);

    itsIE->param_data.userServiceInfoPrime.layer3 = 
        (nmsIE->usrInfLyr3Prot.val) & 0x1FU;
    itsIE->param_data.userServiceInfoPrime.layer3 |= 
        ((nmsIE->lyr3Ident.val << 5) & 0x60U);
}

static void 
UsrServInfoPrime_ITS_to_NMS(SiUsrServInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->cdeStand,
                   itsIE->param_data.userServiceInfoPrime.coding, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranCap,
                   itsIE->param_data.userServiceInfoPrime.coding, 1, 5);

    SetBitsToTknU8(&nmsIE->tranMode,
                   itsIE->param_data.userServiceInfoPrime.trans_mode, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranRate0,
                   itsIE->param_data.userServiceInfoPrime.trans_mode, 1, 5);

    SetBitsToTknU8(&nmsIE->chanStruct,
                   itsIE->param_data.userServiceInfoPrime.config, 5, 7);
    SetBitsToTknU8(&nmsIE->config,
                   itsIE->param_data.userServiceInfoPrime.config, 3, 4);
    SetBitsToTknU8(&nmsIE->establish,
                   itsIE->param_data.userServiceInfoPrime.config, 1, 2);

    SetBitsToTknU8(&nmsIE->symmetry,
                   itsIE->param_data.userServiceInfoPrime.symmetry, 6, 7);
    SetBitsToTknU8(&nmsIE->infoTranRate1,
                   itsIE->param_data.userServiceInfoPrime.symmetry, 1, 5);

    /* Seems there is no rate_multiplier (ANSI only) field in nms */

    /* layer 1 is very complicated */
    SetBitsToTknU8(&nmsIE->usrInfLyr1Prot,
                   itsIE->param_data.userServiceInfoPrime.layer1, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr1Ident,
                   itsIE->param_data.userServiceInfoPrime.layer1, 6, 7);

    /* layer1 ext: OCTET 3A: synch/asynch, negotiation, User rate */
    SetBitsToTknU8(&nmsIE->usrRate,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate,
                   1, 5);
    SetBitsToTknU8(&nmsIE->negot,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate,
                   6, 6);
    SetBitsToTknU8(&nmsIE->syncAsync,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_user_rate,
                   7, 7);

    /* layer1 ext: OCTET 3B: Intermediate rate etc.  */
    SetBitsToTknU8(&nmsIE->flcOnRx,
           itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b, 
           2, 2);
    SetBitsToTknU8(&nmsIE->flcOnTx,
           itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b, 
           3, 3);
    SetBitsToTknU8(&nmsIE->niClkOnRx,
           itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b, 
           4, 4);
    SetBitsToTknU8(&nmsIE->niClkOnTx,
           itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b, 
           5, 5);
    SetBitsToTknU8(&nmsIE->interRate,
           itsIE->param_data.userServiceInfoPrime.layer1_ext_rate_adaption_3b, 
           6, 7);

    /* why don't have layer ext(one octet): Hdr/no Hdr, multi frame, mode?? */

    /* layer1 ext: OCTET 3C: Parity etc.  */
    SetBitsToTknU8(&nmsIE->parity,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_parity, 
                   1, 3);
    SetBitsToTknU8(&nmsIE->nmbDatBits,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_parity, 
                   4, 5);
    SetBitsToTknU8(&nmsIE->nmbStpBits,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_parity, 
                   6, 7);

    /* layer1 ext: OCTET 3D: Duplex mode, modem type */
    SetBitsToTknU8(&nmsIE->modemType,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_modem_type,
                   1, 6);
    SetBitsToTknU8(&nmsIE->duplexMode,
                   itsIE->param_data.userServiceInfoPrime.layer1_ext_modem_type,                   7, 7);

    SetBitsToTknU8(&nmsIE->usrInfLyr2Prot,
                   itsIE->param_data.userServiceInfoPrime.layer2, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr2Ident,
                   itsIE->param_data.userServiceInfoPrime.layer2, 6, 7);

    SetBitsToTknU8(&nmsIE->usrInfLyr3Prot,
                   itsIE->param_data.userServiceInfoPrime.layer3, 1, 5);
    SetBitsToTknU8(&nmsIE->lyr3Ident,
                   itsIE->param_data.userServiceInfoPrime.layer3, 6, 7);
}

/* IE: User to user indicators */
static void 
Usr2UsrInd_NMS_to_ITS(SiUsr2UsrInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_USER_TO_USER_INDICATORS;
    itsIE->param_length = sizeof(ISUP_USER_TO_USER_INDICATORS);    

    /* bit A */
    itsIE->param_data.userToUserIndicators.utu_ind = nmsIE->type.val & 0x01U;

    /* bit C B */
    itsIE->param_data.userToUserIndicators.utu_ind |= 
        ((nmsIE->serv1.val << 1) & 0x06U);

    /* bit E D */
    itsIE->param_data.userToUserIndicators.utu_ind |= 
        ((nmsIE->serv2.val << 3) & 0x18U);

    /* bit G F */
    itsIE->param_data.userToUserIndicators.utu_ind |= 
        ((nmsIE->serv3.val << 5) & 0x60U);

    /* bit H */
    itsIE->param_data.userToUserIndicators.utu_ind |= 
        ((nmsIE->netDscrdInd.val << 7) & 0x80U);
}

static void 
Usr2UsrInd_ITS_to_NMS(SiUsr2UsrInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    /* bit A */
    SetBitsToTknU8(&nmsIE->type,
                   itsIE->param_data.userToUserIndicators.utu_ind, 1, 1);

    /* bit C B */
    SetBitsToTknU8(&nmsIE->serv1,
                   itsIE->param_data.userToUserIndicators.utu_ind, 2, 3);

    /* bit E D */
    SetBitsToTknU8(&nmsIE->serv2,
                   itsIE->param_data.userToUserIndicators.utu_ind, 4, 5);

    /* bit G F */
    SetBitsToTknU8(&nmsIE->serv3,
                   itsIE->param_data.userToUserIndicators.utu_ind, 6, 7);

    /* bit H */
    SetBitsToTknU8(&nmsIE->netDscrdInd,
                   itsIE->param_data.userToUserIndicators.utu_ind, 8, 8);
}

/* IE: User to User infomation */
static void 
Usr2UsrInfo_NMS_to_ITS(SiUsr2UsrInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_USER_TO_USER_INFO;
    itsIE->param_length = sizeof(ISUP_USER_TO_USER_INFO);    
    
    /* prot_disc is not populated(lack of info from nms), default will be 0 */

    memcpy(itsIE->param_data.userToUserInfo.utu_info, 
           nmsIE->info.val, nmsIE->info.len);

    itsIE->param_length = sizeof(ITS_OCTET) + nmsIE->info.len;    
}

static void 
Usr2UsrInfo_ITS_to_NMS(SiUsr2UsrInfo* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    /* prot_disc is not populated(lack of info from nms), default will be 0 */

    SetTknStr(&nmsIE->info,
              itsIE->param_data.userToUserInfo.utu_info,
              itsIE->param_length - sizeof(ITS_OCTET));
}

#endif /* (CCITT) */

/*
** ANSI specific IEs
**
*/
#if defined(ANSI)
/* IE: Business Group */
static void
BusinessGrp_NMS_to_ITS(SiBusinessGrp* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_BUSINESS_GROUP;
    itsIE->param_length = sizeof(ISUP_BUSINESS_GROUP); /* fixed len */

    itsIE->param_data.businessGroup.party_selector = 
        nmsIE->partySel.val & 0x0FU;
    itsIE->param_data.businessGroup.party_selector |= 
        ((nmsIE->linePrivInfInd.val << 4) & 0x10U);
    itsIE->param_data.businessGroup.party_selector |= 
        ((nmsIE->BGIDident.val << 5) & 0x20U);
    itsIE->param_data.businessGroup.party_selector |= 
        ((nmsIE->attendStat.val << 6) & 0x40U);

    itsIE->param_data.businessGroup.business_group_ident[0] = 
        (U8)(nmsIE->busiGrpIdent.val >> 16);
    itsIE->param_data.businessGroup.business_group_ident[1] = 
        (U8)(nmsIE->busiGrpIdent.val >> 8);
    itsIE->param_data.businessGroup.business_group_ident[2] = 
        (U8)(nmsIE->busiGrpIdent.val);

    itsIE->param_data.businessGroup.sub_group_ident[0] = 
        (U8)(nmsIE->subGrpIdent.val >> 8);
    itsIE->param_data.businessGroup.sub_group_ident[1] = 
        (U8)(nmsIE->subGrpIdent.val);

    itsIE->param_data.businessGroup.line_privileges = nmsIE->linePriv.val;
}

static void
BusinessGrp_ITS_to_NMS(SiBusinessGrp* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->partySel,
                   itsIE->param_data.businessGroup.party_selector, 1, 4);
    SetBitsToTknU8(&nmsIE->linePrivInfInd,
                   itsIE->param_data.businessGroup.party_selector, 5, 5);
    SetBitsToTknU8(&nmsIE->BGIDident,
                   itsIE->param_data.businessGroup.party_selector, 6, 6);
    SetBitsToTknU8(&nmsIE->attendStat,
                   itsIE->param_data.businessGroup.party_selector, 7, 7);

    SetTknU32(&nmsIE->busiGrpIdent,
              itsIE->param_data.businessGroup.business_group_ident, 3);

    SetTknU16(&nmsIE->subGrpIdent,
              itsIE->param_data.businessGroup.sub_group_ident, 2);

    SetTknU8(&nmsIE->linePriv, 
             itsIE->param_data.businessGroup.line_privileges);
}

/* IE: Carrier ID */
static void
CarrierId_NMS_to_ITS(SiCarrierId* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CARRIER_ID;
    itsIE->param_length = sizeof(ISUP_CARRIER_IDENTIFICATION); /* fixed len */

    itsIE->param_data.carrierIdentification.network = 
        nmsIE->netIdPln.val & 0x0FU;
    itsIE->param_data.carrierIdentification.network |= 
        ((nmsIE->typNetId.val << 4) & 0x70U);

    itsIE->param_data.carrierIdentification.digit2and1 = 
        ((nmsIE->CIDigit1.val) & 0x0FU);
    itsIE->param_data.carrierIdentification.digit2and1 |= 
        ((nmsIE->CIDigit2.val << 4) & 0xF0U);

    itsIE->param_data.carrierIdentification.digit4and3 = 
        ((nmsIE->CIDigit3.val) & 0x0FU);

    /* 3-digit carrier id OR 4-digit carrier id ?*/
    if (nmsIE->CIDigit4.pres == PRESENT)
    {
        itsIE->param_data.carrierIdentification.digit4and3 |= 
            ((nmsIE->CIDigit4.val << 4) & 0xF0U);
    }
}

static void
CarrierId_ITS_to_NMS(SiCarrierId* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;
    
    itsIE->param_length = sizeof(ISUP_CARRIER_IDENTIFICATION); /* fixed len */

    SetBitsToTknU8(&nmsIE->netIdPln,
                   itsIE->param_data.carrierIdentification.network, 1, 4);
    SetBitsToTknU8(&nmsIE->typNetId,
                   itsIE->param_data.carrierIdentification.network, 5, 7);

    SetBitsToTknU8(&nmsIE->CIDigit1,
                   itsIE->param_data.carrierIdentification.digit2and1, 1, 4);
    SetBitsToTknU8(&nmsIE->CIDigit2,
                   itsIE->param_data.carrierIdentification.digit2and1, 5, 8);

    SetBitsToTknU8(&nmsIE->CIDigit3,
                   itsIE->param_data.carrierIdentification.digit4and3, 1, 4);

    /* 3-digit carrier id OR 4-digit carrier id ?*/
    if (itsIE->param_data.carrierIdentification.digit4and3 & 0xF0U != 0x00U)
    {
        /* 4-digit carrier id */
        SetBitsToTknU8(&nmsIE->CIDigit4,
                       itsIE->param_data.carrierIdentification.digit4and3, 
                       5, 8);
    }
}

/* IE: Carrier Selection Info */
static void
CarrierSelInfo_NMS_to_ITS(SiCarrierSelInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CARRIER_SELECTION_INFO;
    itsIE->param_length = sizeof(ISUP_CARRIER_SELECTION_INFO); /* fixed len */

    itsIE->param_data.carrierSelectionInfo.information = 
        nmsIE->carrierSelInf.val;
}

static void
CarrierSelInfo_ITS_to_NMS(SiCarrierSelInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->carrierSelInf, 
             itsIE->param_data.carrierSelectionInfo.information);
}

/* IE: Charge Number (same as Called Party number) */
static void
ChargeNum_NMS_to_ITS(SiChargeNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_CHARGE_NUMBER;

    itsIE->param_data.chargeNumber.addr_ind = nmsIE->natAddrInd.val & 0x7FU;
    itsIE->param_data.chargeNumber.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.chargeNumber.num_plan = 
        ((nmsIE->numPlan.val << 4) & 0x70U);

    memcpy(itsIE->param_data.chargeNumber.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 2 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
ChargeNum_ITS_to_NMS(SiChargeNum* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->natAddrInd,
                   itsIE->param_data.chargeNumber.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.chargeNumber.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.chargeNumber.num_plan, 5, 7);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.chargeNumber.dgts,
              itsIE->param_length - 2 * sizeof(ITS_OCTET));
}

/* IE: Egress sevice */
static void
EgressServ_NMS_to_ITS(SiEgress* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_EGRESS_SERVICE;

    memcpy(itsIE->param_data.egressService.data, 
           nmsIE->egress.val, nmsIE->egress.len);

    itsIE->param_length = nmsIE->egress.len;
}

static void
EgressServ_ITS_to_NMS(SiEgress* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknStr(&nmsIE->egress,
              itsIE->param_data.egressService.data,
              itsIE->param_length);
}

/* IE: Generic address */
static void
GenericAddr_NMS_to_ITS(SiGenAddr* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_GENERIC_ADDR;

    itsIE->param_data.genericAddress.type_of_addr = nmsIE->typeOfAddr.val;

    itsIE->param_data.genericAddress.addr_ind = nmsIE->natAddr.val & 0x7FU;
    itsIE->param_data.genericAddress.addr_ind |= 
        ((nmsIE->oddEven.val << 7) & 0x80U);

    itsIE->param_data.genericAddress.subfields4 = 
        ((nmsIE->numPlan.val << 4) & 0x70U);
    itsIE->param_data.genericAddress.subfields4 |= 
        ((nmsIE->presRest.val << 2) & 0x0CU);

    memcpy(itsIE->param_data.genericAddress.dgts, 
           nmsIE->addrSig.val, nmsIE->addrSig.len);

    itsIE->param_length = 3 * sizeof(ITS_OCTET) + nmsIE->addrSig.len;
}

static void
GenericAddr_ITS_to_NMS(SiGenAddr* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->typeOfAddr, 
             itsIE->param_data.genericAddress.type_of_addr);

    SetBitsToTknU8(&nmsIE->natAddr,
                   itsIE->param_data.genericAddress.addr_ind, 1, 7);
    SetBitsToTknU8(&nmsIE->oddEven,
                   itsIE->param_data.genericAddress.addr_ind, 8, 8);

    SetBitsToTknU8(&nmsIE->numPlan,
                   itsIE->param_data.genericAddress.subfields4, 5, 7);
    SetBitsToTknU8(&nmsIE->presRest,
                   itsIE->param_data.genericAddress.subfields4, 3, 4);

    SetTknStr(&nmsIE->addrSig,
              itsIE->param_data.genericAddress.dgts, 
              itsIE->param_length - 3 * sizeof(ITS_OCTET));
}

/* IE: Jurisdiction Info */
static void
JurisInfo_NMS_to_ITS(SiJurisInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_JURISDICTION;
    itsIE->param_length = sizeof(ISUP_JURISDICTION); /* fixed len */

    itsIE->param_data.jurisdiction.digits[0] = nmsIE->addrSig1.val & 0x0FU;
    itsIE->param_data.jurisdiction.digits[0] |= 
        ((nmsIE->addrSig2.val << 4) & 0xF0U);

    itsIE->param_data.jurisdiction.digits[1] = nmsIE->addrSig3.val & 0x0FU;
    itsIE->param_data.jurisdiction.digits[1] |= 
        ((nmsIE->addrSig4.val << 4) & 0xF0U);

    itsIE->param_data.jurisdiction.digits[2] = nmsIE->addrSig5.val & 0x0FU;
    itsIE->param_data.jurisdiction.digits[2] |= 
        ((nmsIE->addrSig6.val << 4) & 0xF0U);
}

static void
JurisInfo_ITS_to_NMS(SiJurisInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetBitsToTknU8(&nmsIE->addrSig1,
                   itsIE->param_data.jurisdiction.digits[0], 1, 4);
    SetBitsToTknU8(&nmsIE->addrSig2,
                   itsIE->param_data.jurisdiction.digits[0], 5, 8);

    SetBitsToTknU8(&nmsIE->addrSig3,
                   itsIE->param_data.jurisdiction.digits[1], 1, 4);
    SetBitsToTknU8(&nmsIE->addrSig4,
                   itsIE->param_data.jurisdiction.digits[1], 5, 8);

    SetBitsToTknU8(&nmsIE->addrSig5,
                   itsIE->param_data.jurisdiction.digits[2], 1, 4);
    SetBitsToTknU8(&nmsIE->addrSig6,
                   itsIE->param_data.jurisdiction.digits[2], 5, 8);
}

/* IE: Network transport */
static void
NetworkTrans_NMS_to_ITS(SiNetTransport* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_NTWK_TRANSPORT;    

    memcpy(itsIE->param_data.networkTransport.data,
            nmsIE->netTransport.val, nmsIE->netTransport.len);

    itsIE->param_length = nmsIE->netTransport.len;
}

static void
NetworkTrans_ITS_to_NMS(SiNetTransport* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknStr(&nmsIE->netTransport,
              itsIE->param_data.networkTransport.data,
              itsIE->param_length);
}

/* IE: Originating line information */
static void
OrigLineInfo_NMS_to_ITS(SiOrigLineInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_ORIG_LINE_INFO;    
    itsIE->param_length = sizeof(ISUP_ORIG_LINE_INFO);

    itsIE->param_data.origLineInfo.data = nmsIE->lineInfo.val;    
}

static void
OrigLineInfo_ITS_to_NMS(SiOrigLineInf* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->lineInfo, itsIE->param_data.origLineInfo.data);
}

/* IE: Service code */
static void
ServiceCode_NMS_to_ITS(SiServiceCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SERVICE_CODE;    
    itsIE->param_length = sizeof(ISUP_SERVICE_CODE);

    itsIE->param_data.serviceCode.code = nmsIE->serviceCode.val;    
}

static void
ServiceCode_ITS_to_NMS(SiServiceCode* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->serviceCode, itsIE->param_data.serviceCode.code);
}

/* IE: Special process request */
static void
SpecialProcessReq_NMS_to_ITS(SiSpecProcReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_SPECIAL_PROCESS_REQUEST;    
    itsIE->param_length = sizeof(ISUP_SPECIAL_PROCESS_REQUEST);

    itsIE->param_data.specialProcessing.data = nmsIE->specProcReq.val;    
}

static void
SpecialProcessReq_ITS_to_NMS(SiSpecProcReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->specProcReq, itsIE->param_data.specialProcessing.data);
}

/* IE: Transaction request */
static void
TransReq_NMS_to_ITS(SiTransReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_TRANSACTION_REQUEST;

    itsIE->param_data.transactionRequest.transaction_id[0] = 
        (U8)(nmsIE->transId.val >> 24);
    itsIE->param_data.transactionRequest.transaction_id[1] = 
        (U8)(nmsIE->transId.val >> 16);
    itsIE->param_data.transactionRequest.transaction_id[2] = 
        (U8)(nmsIE->transId.val >> 8);
    itsIE->param_data.transactionRequest.transaction_id[3] = 
        (U8)(nmsIE->transId.val);

    itsIE->param_data.transactionRequest.SCCP_addr.len = nmsIE->SCCPAddr.len;
    memcpy(itsIE->param_data.transactionRequest.SCCP_addr.data,
           nmsIE->SCCPAddr.val, nmsIE->SCCPAddr.len);

    /* len = transId(4) + sccpAddr.len(1) + sccpAddr.data */
    itsIE->param_length = 
        sizeof(ITS_UINT) + sizeof(ITS_OCTET) + nmsIE->SCCPAddr.len;
}

static void
TransReq_ITS_to_NMS(SiTransReq* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU32(&nmsIE->transId, 
              itsIE->param_data.transactionRequest.transaction_id, 4);

    SetTknStr(&nmsIE->SCCPAddr,
              itsIE->param_data.transactionRequest.SCCP_addr.data,
              itsIE->param_data.transactionRequest.SCCP_addr.len);
}

/* IE: Notification */
static void
Notification_NMS_to_ITS(SiNotifInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    itsIE->param_id = ISUP_PRM_NOTIFICATION;
    itsIE->param_length = sizeof(ISUP_NOTIFICATION);

    itsIE->param_data.notification.indicator = nmsIE->notifInd.val;
}

static void
Notification_ITS_to_NMS(SiNotifInd* nmsIE, ITS_ISUP_IE* itsIE)
{
    nmsIE->eh.pres = PRESENT;

    SetTknU8(&nmsIE->notifInd, itsIE->param_data.notification.indicator);
}

#endif /* (ANSI) */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received IAM NMS message to an ITS IAM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCONIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsIAM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_NATURE_CONN_INDICATORS */
    if (msg->m.siConEvnt.natConInd.eh.pres == PRESENT)
    {
        NatConInd_NMS_to_ITS(&msg->m.siConEvnt.natConInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_FWD_CALL_INDICATORS */
    if (msg->m.siConEvnt.fwdCallInd.eh.pres == PRESENT)
    {    
        FwdCallInd_NMS_to_ITS(&msg->m.siConEvnt.fwdCallInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLING_PARTY_CATEGORY */
    if (msg->m.siConEvnt.cgPtyCat.eh.pres == PRESENT)
    {    
        CgPtyCategory_NMS_to_ITS(&msg->m.siConEvnt.cgPtyCat, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_SERVICE_INFO */
    if (msg->m.siConEvnt.usrServInfo.eh.pres == PRESENT)
    {    
        UsrServInfo_NMS_to_ITS(&msg->m.siConEvnt.usrServInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLED_PARTY_NUM */
    if (msg->m.siConEvnt.cdPtyNum.eh.pres == PRESENT)
    {    
        CdPtyNum_NMS_to_ITS(&msg->m.siConEvnt.cdPtyNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siConEvnt.accTrnspt.eh.pres == PRESENT)
    {    
        AccessTrnspt_NMS_to_ITS(&msg->m.siConEvnt.accTrnspt, &ies[ieCount++]);
    } 

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siConEvnt.callRef.eh.pres == PRESENT)
    {    
        CallRef_NMS_to_ITS(&msg->m.siConEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLING_PARTY_NUM */
    if (msg->m.siConEvnt.cgPtyNum.eh.pres == PRESENT)
    {    
        CgPtyNum_NMS_to_ITS(&msg->m.siConEvnt.cgPtyNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siConEvnt.connReq.eh.pres == PRESENT)
    {    
        ConnReq_NMS_to_ITS(&msg->m.siConEvnt.connReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_DIGITS */
    if (msg->m.siConEvnt.genDigits.eh.pres == PRESENT)
    {    
        GenericDgts_NMS_to_ITS(&msg->m.siConEvnt.genDigits, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTING_NUM */
    if (msg->m.siConEvnt.redirgNum.eh.pres == PRESENT)
    {    
        RedirectingNum_NMS_to_ITS(&msg->m.siConEvnt.redirgNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_INFO */
    if (msg->m.siConEvnt.redirInfo.eh.pres == PRESENT)
    {    
        RedirectionInfo_NMS_to_ITS(&msg->m.siConEvnt.redirInfo, 
                                   &ies[ieCount++]);
    }

    /* ISUP_PRM_ORIG_CALLED_NUM */
    if (msg->m.siConEvnt.origCdNum.eh.pres == PRESENT)
    {
        OrigCdNum_NMS_to_ITS(&msg->m.siConEvnt.origCdNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_SERVICE_ACTIVATION */
    if (msg->m.siConEvnt.serviceAct.eh.pres == PRESENT)
    {    
        ServActivation_NMS_to_ITS(&msg->m.siConEvnt.serviceAct, 
                                  &ies[ieCount++]);
    }

    /* ISUP_PRM_TRANSIT_NTWK_SELECT */    
    if (msg->m.siConEvnt.tranNetSel.eh.pres == PRESENT)
    {    
        TransmitNwSel_NMS_to_ITS(&msg->m.siConEvnt.tranNetSel, &ies[ieCount++]);
    }
 
    
#if defined (ANSI)
    /* ISUP_PRM_BUSINESS_GROUP */
    if (msg->m.siConEvnt.businessGrp.eh.pres == PRESENT)
    {    
        BusinessGrp_NMS_to_ITS(&msg->m.siConEvnt.businessGrp, &ies[ieCount++]);
    }

    /* ISUP_PRM_CARRIER_ID */
    if (msg->m.siConEvnt.carrierId.eh.pres == PRESENT)
    {    
        CarrierId_NMS_to_ITS(&msg->m.siConEvnt.carrierId, &ies[ieCount++]);
    }

    /* ISUP_PRM_CARRIER_SELECTION_INFO */
    if (msg->m.siConEvnt.carSelInf.eh.pres == PRESENT)
    {    
        CarrierSelInfo_NMS_to_ITS(&msg->m.siConEvnt.carSelInf, &ies[ieCount++]);
    }

    /* ISUP_PRM_CHARGE_NUMBER */
    if (msg->m.siConEvnt.chargeNum.eh.pres == PRESENT)
    {    
        ChargeNum_NMS_to_ITS(&msg->m.siConEvnt.chargeNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_EGRESS_SERVICE */
    if (msg->m.siConEvnt.egress.eh.pres == PRESENT)
    {    
        EgressServ_NMS_to_ITS(&msg->m.siConEvnt.egress, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_ADDR */
    if (msg->m.siConEvnt.genAddr.eh.pres == PRESENT)
    {    
        GenericAddr_NMS_to_ITS(&msg->m.siConEvnt.genAddr, &ies[ieCount++]);
    }

    /* ISUP_PRM_INFO_REQ_INDICATORS */
    if (msg->m.siConEvnt.infoReqInd.eh.pres == PRESENT)
    {    
        InfoReqInd_NMS_to_ITS(&msg->m.siConEvnt.infoReqInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_JURISDICTION */
    if (msg->m.siConEvnt.jurisInf.eh.pres == PRESENT)
    {    
        JurisInfo_NMS_to_ITS(&msg->m.siConEvnt.jurisInf, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_TRANSPORT */
    if (msg->m.siConEvnt.netTransport.eh.pres == PRESENT)
    {    
        NetworkTrans_NMS_to_ITS(&msg->m.siConEvnt.netTransport, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_ORIG_LINE_INFO */
    if (msg->m.siConEvnt.origLineInf.eh.pres == PRESENT)
    {    
        OrigLineInfo_NMS_to_ITS(&msg->m.siConEvnt.origLineInf, &ies[ieCount++]);
    }

    /* ISUP_PRM_SERVICE_CODE */
    if (msg->m.siConEvnt.serviceCode.eh.pres == PRESENT)
    {   
        ServiceCode_NMS_to_ITS(&msg->m.siConEvnt.serviceCode, &ies[ieCount++]);
    }

    /* ISUP_PRM_SPECIAL_PROCESS_REQUEST */
    if (msg->m.siConEvnt.specProcReq.eh.pres == PRESENT)
    {   
        SpecialProcessReq_NMS_to_ITS(&msg->m.siConEvnt.specProcReq, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_TRANSACTION_REQUEST */
    if (msg->m.siConEvnt.transReq.eh.pres == PRESENT)
    {   
        TransReq_NMS_to_ITS(&msg->m.siConEvnt.transReq, &ies[ieCount++]);
    }
#endif

#if defined (CCITT)
    /* ISUP_PRM_TX_MEDIUM_REQMNT */
    if (msg->m.siConEvnt.txMedReq.eh.pres == PRESENT)
    {   
        TXMediumRequirement_NMS_to_ITS(&msg->m.siConEvnt.txMedReq, 
                                       &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siConEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siConEvnt.usr2UsrInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siConEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siConEvnt.usr2UsrInd, &ies[ieCount++]);
    }
    
    /* ISUP_PRM_OPT_FWD_CALL_INDICATORS */
    if (msg->m.siConEvnt.opFwdCalInd.eh.pres == PRESENT)
    {   
        OptionalFwdCallInd_NMS_to_ITS(&msg->m.siConEvnt.opFwdCalInd, 
                                      &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM */
    if (msg->m.siConEvnt.redirNum.eh.pres == PRESENT)
    {   
        RedirectionNum_NMS_to_ITS(&msg->m.siConEvnt.redirNum, &ies[ieCount++]);
    }
    
    /* ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE */
    if (msg->m.siConEvnt.cugIntCode.eh.pres == PRESENT)
    {   
        ClosedUserGrpInterLockCode_NMS_to_ITS(&msg->m.siConEvnt.cugIntCode, 
                                              &ies[ieCount++]);
    }

    /* ISUP_PRM_PROP_DELAY_COUNTER */
    if (msg->m.siConEvnt.propDly.eh.pres == PRESENT)
    {   
        PropagationDelayCounter_NMS_to_ITS(&msg->m.siConEvnt.propDly, 
                                           &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_SERVICE_INFO_PRIME */
    if (msg->m.siConEvnt.usrServInfo1.eh.pres == PRESENT)
    {   
        UsrServInfoPrime_NMS_to_ITS(&msg->m.siConEvnt.usrServInfo1, 
                                    &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siConEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siConEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NUM */
    if (msg->m.siConEvnt.genNmb.eh.pres == PRESENT)
    {   
        GenericNum_NMS_to_ITS(&msg->m.siConEvnt.genNmb, &ies[ieCount++]);
    }

    /* ISUP_PRM_ORIG_ISC_PC */
    if (msg->m.siConEvnt.orgPteCde.eh.pres == PRESENT)
    {   
        OrigIscPC_NMS_to_ITS(&msg->m.siConEvnt.orgPteCde, &ies[ieCount++]);
    }

    /* ISUP_PRM_REMOTE_OPS */
    if (msg->m.siConEvnt.remotOper.eh.pres == PRESENT)
    {   
        RemoteOper_NMS_to_ITS(&msg->m.siConEvnt.remotOper, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siConEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siConEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NOTIFICATION */
    if (msg->m.siConEvnt.notifInd.eh.pres == PRESENT)
    {   
        GenericNotifInd_NMS_to_ITS(&msg->m.siConEvnt.notifInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_REF */
    /* NMS doesn't seem to support Generic reference IE */

    /* ISUP_PRM_MLPP_PRECEDENCE */
    if (msg->m.siConEvnt.mlppPrec.eh.pres == PRESENT)
    {   
        MLPPPrecedence_NMS_to_ITS(&msg->m.siConEvnt.mlppPrec, &ies[ieCount++]);
    }

    /* ISUP_PRM_TX_MEDIUM_REQMNT_PRIME */
    if (msg->m.siConEvnt.txMedReqPr.eh.pres == PRESENT)
    {   
       TxMdumReqPrime_NMS_to_ITS(&msg->m.siConEvnt.txMedReqPr, &ies[ieCount++]);
    }

    /* ISUP_PRM_LOCATION_NUM */
    if (msg->m.siConEvnt.locNum.eh.pres == PRESENT)
    {   
       LocationNum_NMS_to_ITS(&msg->m.siConEvnt.locNum, &ies[ieCount++]);
    }

#endif
    /* NMS doesn't seem to have EOP in the event */

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received ANM NMS message to an ITS ANM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCONCFM)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsANM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

#if defined (ANSI)
    /* ISUP_PRM_BUSINESS_GROUP */
    if (msg->m.siConEvnt.businessGrp.eh.pres == PRESENT)
    {   
        BusinessGrp_NMS_to_ITS(&msg->m.siConEvnt.businessGrp, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siConEvnt.connReq.eh.pres == PRESENT)
    {   
        ConnReq_NMS_to_ITS(&msg->m.siConEvnt.connReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_INFO_INDICATORS */
    if (msg->m.siConEvnt.infoInd.eh.pres == PRESENT)
    {   
        InfoIndicators_NMS_to_ITS(&msg->m.siConEvnt.infoInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_TRANSPORT */
    if (msg->m.siConEvnt.netTransport.eh.pres == PRESENT)
    {   
        NetworkTrans_NMS_to_ITS(&msg->m.siConEvnt.netTransport, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_NOTIFICATION */
    if (msg->m.siConEvnt.notifInd.eh.pres == PRESENT)
    {   
        Notification_NMS_to_ITS(&msg->m.siConEvnt.notifInd, &ies[ieCount++]);
    }

#endif
#if defined (CCITT)
    /* ISUP_PRM_ACCESS_DELIVERY_INFO */
    if (msg->m.siConEvnt.accDelInfo.eh.pres == PRESENT)
    {   
        AccessDeliverInfo_NMS_to_ITS(&msg->m.siConEvnt.accDelInfo, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_HISTORY_INFO */
    if (msg->m.siConEvnt.cllHstry.eh.pres == PRESENT)
    {   
        CallHistoryInfo_NMS_to_ITS(&msg->m.siConEvnt.cllHstry, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTED_NUM */
    if (msg->m.siConEvnt.connNum.eh.pres == PRESENT)
    {   
        ConnectedNum_NMS_to_ITS(&msg->m.siConEvnt.connNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NOTIFICATION */
    if (msg->m.siConEvnt.notifInd.eh.pres == PRESENT)
    {   
        GenericNotifInd_NMS_to_ITS(&msg->m.siConEvnt.notifInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siConEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siConEvnt.usr2UsrInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siConEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siConEvnt.usr2UsrInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siConEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siConEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_TX_MEDIUM_USED */
    if (msg->m.siConEvnt.txMedUsed.eh.pres == PRESENT)
    {   
        TXMediumUsed_NMS_to_ITS(&msg->m.siConEvnt.txMedUsed, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siConEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siConEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_REMOTE_OPS */
    if (msg->m.siConEvnt.remotOper.eh.pres == PRESENT)
    {   
        RemoteOper_NMS_to_ITS(&msg->m.siConEvnt.remotOper, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM */
    if (msg->m.siConEvnt.redirNum.eh.pres == PRESENT)
    {   
        RedirectionNum_NMS_to_ITS(&msg->m.siConEvnt.redirNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_SERVICE_ACTIVATION */
    if (msg->m.siConEvnt.serviceAct.eh.pres == PRESENT)
    {   
        ServActivation_NMS_to_ITS(&msg->m.siConEvnt.serviceAct, 
                                  &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM_RESTRICT */
    if (msg->m.siConEvnt.redirRstr.eh.pres == PRESENT)
    {   
        RedirecNumResrict_NMS_to_ITS(&msg->m.siConEvnt.redirRstr, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_ECHO_CTRL_INFO */
    if (msg->m.siConEvnt.echoControl.eh.pres == PRESENT)
    {   
        EchoCtrlInfo_NMS_to_ITS(&msg->m.siConEvnt.echoControl, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NUM */
    if (msg->m.siConEvnt.genNmb.eh.pres == PRESENT)
    {   
        GenericNum_NMS_to_ITS(&msg->m.siConEvnt.genNmb, &ies[ieCount++]);
    }
#endif /* CCITT */

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siConEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siConEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_BKWD_CALL_INDICATORS */
    if (msg->m.siConEvnt.bckCallInd.eh.pres == PRESENT)
    {   
        BkwdCallInd_NMS_to_ITS(&msg->m.siConEvnt.bckCallInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siConEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siConEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_OPT_BKWD_CALL_INDICATORS */
    if (msg->m.siConEvnt.optBckCalInd.eh.pres == PRESENT)
    {   
        OpBkwdCallInd_NMS_to_ITS(&msg->m.siConEvnt.optBckCalInd, 
                                 &ies[ieCount++]);
    }

    
    /* NMS doesn't seem to have EOP in the event */

    return ieCount;
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received ACM NMS message to an ITS ACM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsACM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_BKWD_CALL_INDICATORS */
    if (msg->m.siCnStEvnt.bckCallInd.eh.pres == PRESENT)
    {   
        BkwdCallInd_NMS_to_ITS(&msg->m.siCnStEvnt.bckCallInd, &ies[ieCount++]);
    }

#if defined (ANSI)
    /* ISUP_PRM_BUSINESS_GROUP */
    if (msg->m.siCnStEvnt.businessGrp.eh.pres == PRESENT)
    {   
        BusinessGrp_NMS_to_ITS(&msg->m.siCnStEvnt.businessGrp, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siCnStEvnt.connReq.eh.pres == PRESENT)
    {   
        ConnReq_NMS_to_ITS(&msg->m.siCnStEvnt.connReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_INFO_INDICATORS */
    if (msg->m.siCnStEvnt.infoInd.eh.pres == PRESENT)
    {   
        InfoIndicators_NMS_to_ITS(&msg->m.siCnStEvnt.infoInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_TRANSPORT */
    if (msg->m.siCnStEvnt.netTransport.eh.pres == PRESENT)
    {   
        NetworkTrans_NMS_to_ITS(&msg->m.siCnStEvnt.netTransport, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_NOTIFICATION */
    if (msg->m.siCnStEvnt.notifInd.eh.pres == PRESENT)
    {   
        Notification_NMS_to_ITS(&msg->m.siCnStEvnt.notifInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_INFO */
    if (msg->m.siCnStEvnt.redirInfo.eh.pres == PRESENT)
    {   
        RedirectionInfo_NMS_to_ITS(&msg->m.siCnStEvnt.redirInfo, 
                                   &ies[ieCount++]);
    }

#endif

#if defined (CCITT)
    /* ISUP_PRM_ACCESS_DELIVERY_INFO */
    if (msg->m.siCnStEvnt.accDelInfo.eh.pres == PRESENT)
    {   
        AccessDeliverInfo_NMS_to_ITS(&msg->m.siCnStEvnt.accDelInfo, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_DIVERSION_INFO */
    if (msg->m.siCnStEvnt.cllDivr.eh.pres == PRESENT)
    {   
        CallDiversionInfo_NMS_to_ITS(&msg->m.siCnStEvnt.cllDivr, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_ECHO_CTRL_INFO */
    if (msg->m.siCnStEvnt.echoControl.eh.pres == PRESENT)
    {   
        EchoCtrlInfo_NMS_to_ITS(&msg->m.siCnStEvnt.echoControl, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NOTIFICATION */
    if (msg->m.siCnStEvnt.notifInd.eh.pres == PRESENT)
    {   
        GenericNotifInd_NMS_to_ITS(&msg->m.siCnStEvnt.notifInd, 
                                   &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siCnStEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siCnStEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM */
    if (msg->m.siCnStEvnt.redirNum.eh.pres == PRESENT)
    {   
        RedirectionNum_NMS_to_ITS(&msg->m.siCnStEvnt.redirNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM_RESTRICT */
    if (msg->m.siCnStEvnt.redirRstr.eh.pres == PRESENT)
    {   
        RedirecNumResrict_NMS_to_ITS(&msg->m.siCnStEvnt.redirRstr, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_REMOTE_OPS */
    if (msg->m.siCnStEvnt.remotOper.eh.pres == PRESENT)
    {   
        RemoteOper_NMS_to_ITS(&msg->m.siCnStEvnt.remotOper, &ies[ieCount++]);
    }

    /* ISUP_PRM_SERVICE_ACTIVATION */
    if (msg->m.siCnStEvnt.serviceAct.eh.pres == PRESENT)
    {   
        ServActivation_NMS_to_ITS(&msg->m.siCnStEvnt.serviceAct, 
                                  &ies[ieCount++]);
    }

    /* ISUP_PRM_TX_MEDIUM_USED */
    if (msg->m.siCnStEvnt.txMedUsed.eh.pres == PRESENT)
    {   
        TXMediumUsed_NMS_to_ITS(&msg->m.siCnStEvnt.txMedUsed, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siCnStEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siCnStEvnt.usr2UsrInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siCnStEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siCnStEvnt.usr2UsrInfo, &ies[ieCount++]);
    }

#endif

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siCnStEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siCnStEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siCnStEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siCnStEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siCnStEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siCnStEvnt.causeDgn, &ies[ieCount++]);
    }

    /* ISUP_PRM_OPT_BKWD_CALL_INDICATORS */
    if (msg->m.siCnStEvnt.optBckCalInd.eh.pres == PRESENT)
    {   
        OpBkwdCallInd_NMS_to_ITS(&msg->m.siCnStEvnt.optBckCalInd, 
                                 &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received CPG NMS message to an ITS CPG message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCPG(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_EVENT_INFO */
    if (msg->m.siCnStEvnt.evntInfo.eh.pres == PRESENT)
    {   
        EventInfo_NMS_to_ITS(&msg->m.siCnStEvnt.evntInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siCnStEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siCnStEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_BKWD_CALL_INDICATORS */
    if (msg->m.siCnStEvnt.bckCallInd.eh.pres == PRESENT)
    {   
        BkwdCallInd_NMS_to_ITS(&msg->m.siCnStEvnt.bckCallInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siCnStEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siCnStEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siCnStEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siCnStEvnt.causeDgn, &ies[ieCount++]);
    }

    /* ISUP_PRM_OPT_BKWD_CALL_INDICATORS */
    if (msg->m.siCnStEvnt.optBckCalInd.eh.pres == PRESENT)
    {   
        OpBkwdCallInd_NMS_to_ITS(&msg->m.siCnStEvnt.optBckCalInd, 
                                 &ies[ieCount++]);
    }
    
#if defined (ANSI)
    /* ISUP_PRM_BUSINESS_GROUP */
    if (msg->m.siCnStEvnt.businessGrp.eh.pres == PRESENT)
    {   
        BusinessGrp_NMS_to_ITS(&msg->m.siCnStEvnt.businessGrp, &ies[ieCount++]);
    }

    /* ISUP_PRM_INFO_INDICATORS */
    if (msg->m.siCnStEvnt.infoInd.eh.pres == PRESENT)
    {   
        InfoIndicators_NMS_to_ITS(&msg->m.siCnStEvnt.infoInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_TRANSPORT */
    if (msg->m.siCnStEvnt.netTransport.eh.pres == PRESENT)
    {   
        NetworkTrans_NMS_to_ITS(&msg->m.siCnStEvnt.netTransport, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_NOTIFICATION */
    if (msg->m.siCnStEvnt.notifInd.eh.pres == PRESENT)
    {   
        Notification_NMS_to_ITS(&msg->m.siCnStEvnt.notifInd, &ies[ieCount++]);
    }

#endif

#if defined (CCITT)
    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siCnStEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siCnStEvnt.usr2UsrInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siCnStEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siCnStEvnt.usr2UsrInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM */
    if (msg->m.siCnStEvnt.redirNum.eh.pres == PRESENT)
    {   
        RedirectionNum_NMS_to_ITS(&msg->m.siCnStEvnt.redirNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NOTIFICATION */
    if (msg->m.siCnStEvnt.notifInd.eh.pres == PRESENT)
    {   
        GenericNotifInd_NMS_to_ITS(&msg->m.siCnStEvnt.notifInd, 
                                   &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siCnStEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siCnStEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_REMOTE_OPS */
    if (msg->m.siCnStEvnt.remotOper.eh.pres == PRESENT)
    {   
        RemoteOper_NMS_to_ITS(&msg->m.siCnStEvnt.remotOper, &ies[ieCount++]);
    }

    /* ISUP_PRM_TX_MEDIUM_USED */
    if (msg->m.siCnStEvnt.txMedUsed.eh.pres == PRESENT)
    {   
        TXMediumUsed_NMS_to_ITS(&msg->m.siCnStEvnt.txMedUsed, &ies[ieCount++]);
    }

    /* ISUP_PRM_ACCESS_DELIVERY_INFO */
    if (msg->m.siCnStEvnt.accDelInfo.eh.pres == PRESENT)
    {   
        AccessDeliverInfo_NMS_to_ITS(&msg->m.siCnStEvnt.accDelInfo, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_DIVERSION_INFO */
    if (msg->m.siCnStEvnt.cllDivr.eh.pres == PRESENT)
    {   
        CallDiversionInfo_NMS_to_ITS(&msg->m.siCnStEvnt.cllDivr, 
                                     &ies[ieCount++]);
    }

     /* ISUP_PRM_SERVICE_ACTIVATION */
    if (msg->m.siCnStEvnt.serviceAct.eh.pres == PRESENT)
    {   
        ServActivation_NMS_to_ITS(&msg->m.siCnStEvnt.serviceAct, 
                                  &ies[ieCount++]);
    }
    
    /* ISUP_PRM_REDIRECTION_NUM_RESTRICT */
    if (msg->m.siCnStEvnt.redirRstr.eh.pres == PRESENT)
    {   
        RedirecNumResrict_NMS_to_ITS(&msg->m.siCnStEvnt.redirRstr, 
                                     &ies[ieCount++]);
    }
    
#endif    

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received INF NMS message to an ITS INF message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsINF(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_INFO_INDICATORS */
    if (msg->m.siCnStEvnt.infoInd.eh.pres == PRESENT)
    {   
        InfoIndicators_NMS_to_ITS(&msg->m.siCnStEvnt.infoInd, &ies[ieCount++]);
    }

#if defined (ANSI)
    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siCnStEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siCnStEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_BUSINESS_GROUP */
    if (msg->m.siCnStEvnt.businessGrp.eh.pres == PRESENT)
    {   
        BusinessGrp_NMS_to_ITS(&msg->m.siCnStEvnt.businessGrp, &ies[ieCount++]);
    }

    /* ISUP_PRM_CHARGE_NUMBER */
    if (msg->m.siConEvnt.chargeNum.eh.pres == PRESENT)
    {   
        ChargeNum_NMS_to_ITS(&msg->m.siConEvnt.chargeNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_ORIG_LINE_INFO */
    if (msg->m.siConEvnt.origLineInf.eh.pres == PRESENT)
    {   
        OrigLineInfo_NMS_to_ITS(&msg->m.siConEvnt.origLineInf, &ies[ieCount++]);
    }

     /* ISUP_PRM_REDIRECTING_NUM */
    if (msg->m.siConEvnt.redirgNum.eh.pres == PRESENT)
    {   
        RedirectingNum_NMS_to_ITS(&msg->m.siConEvnt.redirgNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_INFO */
    if (msg->m.siConEvnt.redirInfo.eh.pres == PRESENT)
    {   
        RedirectionInfo_NMS_to_ITS(&msg->m.siConEvnt.redirInfo, 
                                   &ies[ieCount++]);
    }
    
#endif

#if defined (CCITT)
    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siCnStEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siCnStEvnt.netFac, &ies[ieCount++]);
    } 
#endif

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siCnStEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siCnStEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLING_PARTY_CATEGORY */
    if (msg->m.siConEvnt.cgPtyCat.eh.pres == PRESENT)
    {   
        CgPtyCategory_NMS_to_ITS(&msg->m.siConEvnt.cgPtyCat, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLING_PARTY_NUM */
    if (msg->m.siConEvnt.cgPtyNum.eh.pres == PRESENT)
    {   
        CgPtyNum_NMS_to_ITS(&msg->m.siConEvnt.cgPtyNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siConEvnt.connReq.eh.pres == PRESENT)
    {   
        ConnReq_NMS_to_ITS(&msg->m.siConEvnt.connReq, &ies[ieCount++]);
    }


    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received INR NMS message to an ITS INR message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES]-- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsINR(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_INFO_REQ_INDICATORS */
    if (msg->m.siCnStEvnt.infoReqInd.eh.pres == PRESENT)
    {   
        InfoReqInd_NMS_to_ITS(&msg->m.siCnStEvnt.infoReqInd, &ies[ieCount++]);
    }

#if defined (ANSI)
    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siCnStEvnt.connReq.eh.pres == PRESENT)
    {   
        ConnReq_NMS_to_ITS(&msg->m.siCnStEvnt.connReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_TRANSPORT */
    if (msg->m.siCnStEvnt.netTransport.eh.pres == PRESENT)
    {   
        NetworkTrans_NMS_to_ITS(&msg->m.siCnStEvnt.netTransport, 
                                &ies[ieCount++]);
    }   
#endif

#if defined (CCITT)
    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siCnStEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siCnStEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }        
#endif

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siCnStEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siCnStEvnt.callRef, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received FOT NMS message to an ITS FOT message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsFOT(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siCnStEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siCnStEvnt.callRef, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received PAM message to an ITS PAM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITDATIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] - an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsPAM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    ITS_OCTET msgTypeInPAM; /* the type of the real msg contained in PAM */
    int ieCount = 0;        /* starting from index zero */
    
    ies[0].param_id = ISUP_PRM_MSG_IN_PAM;
    ies[0].param_length = 1;
    ies[0].param_data.msgTypeInPAM = 
    msg->m.siInfoEvnt.passAlng.passAlng.val[0]; /* 0 or 8? */

    msgTypeInPAM = ies[0].param_data.msgTypeInPAM;

    /* avoid adding 1 */
    ies++;

    switch (msgTypeInPAM)
    {
    /* TODO add more  messages*/
    case ISUP_MSG_ACM:
        ieCount = ReceiveNmsACM(msg, ies);
        break;

    case ISUP_MSG_ANM:
        ieCount = ReceiveNmsANM(msg, ies);
        break;

    /*case ISUP_MSG_BLO:
        ieCount = ReceiveNmsBLO(msg, ies);
        break;

    case ISUP_MSG_BLA:
        ieCount = ReceiveNmsBLA(msg, ies);
        break;*/

    case ISUP_MSG_CPG:
        ieCount = ReceiveNmsCPG(msg, ies);
        break;

    case ISUP_MSG_CGB:
        ieCount = ReceiveNmsCGB(msg, ies);
        break;

    /*case ISUP_MSG_CGBA:
        ieCount = ReceiveNmsCGBA(msg, ies);
        break;

    case ISUP_MSG_CQM:
        ieCount = ReceiveNmsCQM(msg, ies);
        break;*/

    case ISUP_MSG_CQR:
        ieCount = ReceiveNmsCQR(msg, ies);
        break;

    case ISUP_MSG_GRS:
        ieCount = ReceiveNmsGRS(msg, ies);
        break;

    case ISUP_MSG_GRA:
        ieCount = ReceiveNmsGRA(msg, ies);
        break;

    /*case ISUP_MSG_CGU:
        ieCount = ReceiveNmsCGU(msg, ies);
        break;
   
    case ISUP_MSG_CGUA:
        ieCount = ReceiveNmsCGUA(msg, ies);
        break;

    case ISUP_MSG_CRG:
        ieCount = ReceiveNmsCRG(msg, ies);
        break;*/

    case ISUP_MSG_CFN:
        ieCount = ReceiveNmsCFN(msg, ies);
        break;

    case ISUP_MSG_COT:
        ieCount = ReceiveNmsCOT(msg, ies);
        break;

    /*case ISUP_MSG_CCR:
        ieCount = ReceiveNmsCCR(msg, ies);
        break;*/

    case ISUP_MSG_FOT:
        ieCount = ReceiveNmsFOT(msg, ies);
        break;

    case ISUP_MSG_IAM:
        ieCount = ReceiveNmsIAM(msg, ies);
        break;

    case ISUP_MSG_INF:
        ieCount = ReceiveNmsINF(msg, ies);
        break;

    case ISUP_MSG_INR:
        ieCount = ReceiveNmsINR(msg, ies);
        break;

    /*case ISUP_MSG_LPA:
        ieCount = ReceiveNmsLPA(msg, ies);
        break;*/

    case ISUP_MSG_REL:
        ieCount = ReceiveNmsREL(msg, ies);
        break;

    case ISUP_MSG_RLC:
        ieCount = ReceiveNmsRLC(msg, ies);
        break;

    /*case ISUP_MSG_RSC:
        ieCount = ReceiveNmsRSC(msg, ies);
        break;*/

    case ISUP_MSG_RES:
        ieCount = ReceiveNmsRES(msg, ies);
        break;

    case ISUP_MSG_SUS:
        ieCount = ReceiveNmsSUS(msg, ies);
        break;

    /*case ISUP_MSG_UBL:
        ieCount = ReceiveNmsUBL(msg, ies);
        break;

    case ISUP_MSG_UBA:
        ieCount = ReceiveNmsUBA(msg, ies);
        break;

    case ISUP_MSG_UCIC:
        ieCount = ReceiveNmsUCIC(msg, ies);
        break;*/

#if defined (ANSI)
    case ISUP_MSG_CRM:
        ieCount = ReceiveNmsCRM(msg, ies);
        break;

    /*case ISUP_MSG_CRA:
        ieCount = ReceiveNmsCRA(msg, ies);
        break;

    case ISUP_MSG_CVR:
        ieCount = ReceiveNmsCVR(msg, ies);
        break;

    case ISUP_MSG_CVT:
        ieCount = ReceiveNmsCVT(msg, ies);
        break;*/

    case ISUP_MSG_EXM:
        ieCount = ReceiveNmsEXM(msg, ies);
        break;
#endif /* ANSI */

#if defined (CCITT)
    /*case ISUP_MSG_CON:
        ieCount = ReceiveNmsCON(msg, ies);
        break;*/

    case ISUP_MSG_IDR:
        ieCount = ReceiveNmsIDR(msg, ies);
        break;

    case ISUP_MSG_IRS:
        ieCount = ReceiveNmsIRS(msg, ies);
        break;

    case ISUP_MSG_FAA:
        ieCount = ReceiveNmsFAA(msg, ies);
        break;

    case ISUP_MSG_FAC:
        ieCount = ReceiveNmsFAC(msg, ies);
        break;

#endif /* CCITT */


    default:
        return (ITS_BADISUPMESSAGE);

    } /* switch msgTypeInPAM */

    /* add ISUP_PRM_MSG_IN_PAM */
    ieCount++;
    
    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received REL message to an ITS REL message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is SiRelEvnt)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsREL(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siRelEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siRelEvnt.causeDgn, &ies[ieCount++]);
    }

#if defined (ANSI)
    /* ISUP_PRM_CALL_REF */
    if (msg->m.siRelEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siRelEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CHARGE_NUMBER */
    if (msg->m.siRelEvnt.chargeNum.eh.pres == PRESENT)
    {   
        ChargeNum_NMS_to_ITS(&msg->m.siRelEvnt.chargeNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_ADDR */
    if (msg->m.siRelEvnt.genAddr.eh.pres == PRESENT)
    {   
        GenericAddr_NMS_to_ITS(&msg->m.siRelEvnt.genAddr, &ies[ieCount++]);
    }   

#endif

#if defined (CCITT)
    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siRelEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siRelEvnt.usr2UsrInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siRelEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siRelEvnt.usr2UsrInfo, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_INFO */
    if (msg->m.siRelEvnt.redirInfo.eh.pres == PRESENT)
    {   
        RedirectionInfo_NMS_to_ITS(&msg->m.siRelEvnt.redirInfo, 
                                   &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM */
    if (msg->m.siRelEvnt.redirNum.eh.pres == PRESENT)
    {   
        RedirectionNum_NMS_to_ITS(&msg->m.siRelEvnt.redirNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_SIGNALLING_POINT_CODE */
    if (msg->m.siRelEvnt.sigPointCode.eh.pres == PRESENT)
    {   
        SingalingPC_NMS_to_ITS(&msg->m.siRelEvnt.sigPointCode, &ies[ieCount++]);
    }

    /* ISUP_PRM_NTWK_SPECIFIC_FACILITIES */
    if (msg->m.siRelEvnt.netFac.eh.pres == PRESENT)
    {   
        NwkSpecFac_NMS_to_ITS(&msg->m.siRelEvnt.netFac, &ies[ieCount++]);
    }

    /* ISUP_PRM_ACCESS_DELIVERY_INFO */
    if (msg->m.siRelEvnt.accDelInfo.eh.pres == PRESENT)
    {   
        AccessDeliverInfo_NMS_to_ITS(&msg->m.siRelEvnt.accDelInfo, 
                                     &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siRelEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siRelEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_REDIRECTION_NUM_RESTRICT */
    if (msg->m.siRelEvnt.redirRstr.eh.pres == PRESENT)
    {   
        RedirecNumResrict_NMS_to_ITS(&msg->m.siRelEvnt.redirRstr, 
                                     &ies[ieCount++]);
    }
#endif

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siRelEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siRelEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_AUTO_CONGEST_LEVEL */
    if (msg->m.siRelEvnt.autoCongLvl.eh.pres == PRESENT)
    {   
        AutoCongestLevel_NMS_to_ITS(&msg->m.siRelEvnt.autoCongLvl, 
                                    &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received RLC message to an ITS RLC message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is SiRelEvnt)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsRLC(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siRelEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siRelEvnt.causeDgn, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received RES message to an ITS RES message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITRESMIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsRES(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siResmEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siResmEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_SUSP_RESUM_INDICATORS */
    if (msg->m.siResmEvnt.susResInd.eh.pres == PRESENT)
    {   
        SusResumeInd_NMS_to_ITS(&msg->m.siResmEvnt.susResInd, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received SUS message to an ITS SUS message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSUSPIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsSUS(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siResmEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siResmEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_SUSP_RESUM_INDICATORS */
    if (msg->m.siSuspEvnt.susResInd.eh.pres == PRESENT)
    {   
        SusResumeInd_NMS_to_ITS(&msg->m.siSuspEvnt.susResInd, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms CFN message to ITS CFN message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCFN(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siStaEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siStaEvnt.causeDgn, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms CGB, CGBA, CGU, CGUA message to ITS CGB, CGBA
 *      CGU, CGUA messages.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCGB(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CKT_GRP_SUPRVN_MT_IND */
    if (msg->m.siStaEvnt.cgsmti.eh.pres == PRESENT)
    {   
        CGSuperMsgTypeInd_NMS_to_ITS(&msg->m.siStaEvnt.cgsmti, &ies[ieCount++]);
    }

    /* ISUP_PRM_RANGE_STATUS */
    if (msg->m.siStaEvnt.rangStat.eh.pres == PRESENT)
    {   
        RangeStat_NMS_to_ITS(&msg->m.siStaEvnt.rangStat, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms COT message to ITS COT message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCOT(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_CONTINUITY_INDICATORS */
    if (msg->m.siStaEvnt.contInd.eh.pres == PRESENT)
    {   
        ContinuityInd_NMS_to_ITS(&msg->m.siStaEvnt.contInd, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms CQR message to ITS CQR message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCQR(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_RANGE_STATUS */
    if (msg->m.siStaEvnt.rangStat.eh.pres == PRESENT)
    {   
        RangeStat_NMS_to_ITS(&msg->m.siStaEvnt.rangStat, &ies[ieCount++]);
    }

    /* ISUP_PRM_CKT_STATE_INDICATOR */
    if (msg->m.siStaEvnt.cirStateInd.eh.pres == PRESENT)
    {   
        CircuitStateInd_NMS_to_ITS(&msg->m.siStaEvnt.cirStateInd, 
                                   &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms GRA message to ITS GRA message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsGRA(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_RANGE_STATUS */
    if (msg->m.siStaEvnt.rangStat.eh.pres == PRESENT)
    {   
        RangeStat_NMS_to_ITS(&msg->m.siStaEvnt.rangStat, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms GRS message to ITS GRS message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsGRS(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_RANGE_STATUS */
    if (msg->m.siStaEvnt.rangStat.eh.pres == PRESENT)
    {   
        RangeStat_NMS_to_ITS(&msg->m.siStaEvnt.rangStat, &ies[ieCount++]);
    }

    return ieCount;
}


/***
****  ANSI only messages
***/

#if defined (ANSI)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms CRM message to ITS CRM message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsCRM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_NATURE_CONN_INDICATORS */
    if (msg->m.siStaEvnt.natConInd.eh.pres == PRESENT)
    {   
        NatConInd_NMS_to_ITS(&msg->m.siStaEvnt.natConInd, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms EXM message to ITS EXM message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTCNSTAIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsEXM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_OUTGOING_TRUNK_GRP_NUM */
    /* NMS has this IE, but it is not inside the message */

    return ieCount;
}
#endif /* ANSI */

/***
****  CCITT only messages
***/

#if defined (CCITT)
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received IDR message to an ITS IDR message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsIDR(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_MCID_REQ_INDICATOR */
    if (msg->m.siCnStEvnt.mcidReq.eh.pres == PRESENT)
    {   
        MCIDReqInd_NMS_to_ITS(&msg->m.siCnStEvnt.mcidReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_MSG_COMPAT_INFO */
    if (msg->m.siCnStEvnt.msgCom.eh.pres == PRESENT)
    {   
        MsgCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.msgCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received IRS message to an ITS IRS message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsIRS(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_MCID_RESP_INDICATOR */
    if (msg->m.siCnStEvnt.mcidRsp.eh.pres == PRESENT)
    {   
        MCIDRspInd_NMS_to_ITS(&msg->m.siCnStEvnt.mcidRsp, &ies[ieCount++]);
    }

    /* ISUP_PRM_MSG_COMPAT_INFO */
    if (msg->m.siCnStEvnt.msgCom.eh.pres == PRESENT)
    {   
        MsgCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.msgCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALLING_PARTY_NUM */
    if (msg->m.siCnStEvnt.cgPtyNum.eh.pres == PRESENT)
    {   
        CgPtyNum_NMS_to_ITS(&msg->m.siCnStEvnt.cgPtyNum, &ies[ieCount++]);
    }

    /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siCnStEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siCnStEvnt.accTrnspt, &ies[ieCount++]);
    }

    /* ISUP_PRM_GENERIC_NUM */
    if (msg->m.siCnStEvnt.genNmb.eh.pres == PRESENT)
    {   
        GenericNum_NMS_to_ITS(&msg->m.siCnStEvnt.genNmb, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received NRM message to an ITS NRM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsNRM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_MSG_COMPAT_INFO */
    if (msg->m.siCnStEvnt.msgCom.eh.pres == PRESENT)
    {   
        MsgCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.msgCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siCnStEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siCnStEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_ECHO_CTRL_INFO */
    if (msg->m.siCnStEvnt.echoControl.eh.pres == PRESENT)
    {   
        EchoCtrlInfo_NMS_to_ITS(&msg->m.siCnStEvnt.echoControl, 
                                &ies[ieCount++]);
    }

    /* ISUP_PRM_TX_MEDIUM_USED */
    if (msg->m.siCnStEvnt.txMedUsed.eh.pres == PRESENT)
    {   
        TXMediumUsed_NMS_to_ITS(&msg->m.siCnStEvnt.txMedUsed, &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms FAC message to ITS FAC message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITFACIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsFAC(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;     
    
    /* ISUP_PRM_MSG_COMPAT_INFO */
    if (msg->m.siFacEvnt.msgCom.eh.pres == PRESENT)
    {   
        MsgCompatInfo_NMS_to_ITS(&msg->m.siFacEvnt.msgCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siFacEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siFacEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_REMOTE_OPS */
    if (msg->m.siFacEvnt.remotOper.eh.pres == PRESENT)
    {   
        RemoteOper_NMS_to_ITS(&msg->m.siFacEvnt.remotOper, &ies[ieCount++]);
    }

    /* ISUP_PRM_SERVICE_ACTIVATION */
    if (msg->m.siFacEvnt.serviceAct.eh.pres == PRESENT)
    {   
        ServActivation_NMS_to_ITS(&msg->m.siFacEvnt.serviceAct, 
                                  &ies[ieCount++]);
    }

    return ieCount;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms FAA, FAR message to ITS FAC, FAR message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITFACIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsFAA(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;     
    
    /* ISUP_PRM_FACILITY_INDICATOR */
    if (msg->m.siFacEvnt.facInd.eh.pres == PRESENT)
    {   
        FacilityInd_NMS_to_ITS(&msg->m.siFacEvnt.facInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_CALL_REF */
    if (msg->m.siFacEvnt.callRef.eh.pres == PRESENT)
    {   
        CallRef_NMS_to_ITS(&msg->m.siFacEvnt.callRef, &ies[ieCount++]);
    }

    /* ISUP_PRM_CONNECTION_REQ */
    if (msg->m.siFacEvnt.connReq.eh.pres == PRESENT)
    {   
        ConnReq_NMS_to_ITS(&msg->m.siFacEvnt.connReq, &ies[ieCount++]);
    }

    /* ISUP_PRM_PARAM_COMPAT_INFO */
    if (msg->m.siFacEvnt.parmCom.eh.pres == PRESENT)
    {   
        ParmCompatInfo_NMS_to_ITS(&msg->m.siFacEvnt.parmCom, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siFacEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siFacEvnt.usr2UsrInd, &ies[ieCount++]);
    } 

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received nms FRJ message to ITS FRJ message.
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITFACIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsFRJ(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;     
    
    /* ISUP_PRM_FACILITY_INDICATOR */
    if (msg->m.siFacEvnt.facInd.eh.pres == PRESENT)
    {   
        FacilityInd_NMS_to_ITS(&msg->m.siFacEvnt.facInd, &ies[ieCount++]);
    }

    /* ISUP_PRM_CAUSE_INDICATORS */
    if (msg->m.siFacEvnt.causeDgn.eh.pres == PRESENT)
    {   
        CauseInd_NMS_to_ITS(&msg->m.siFacEvnt.causeDgn, &ies[ieCount++]);
    }

    /* ISUP_PRM_USER_TO_USER_INDICATORS */
    if (msg->m.siFacEvnt.usr2UsrInd.eh.pres == PRESENT)
    {   
        Usr2UsrInd_NMS_to_ITS(&msg->m.siFacEvnt.usr2UsrInd, &ies[ieCount++]);
    } 

    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received SAM message to an ITS SAM message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITCNSTIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsSAM(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_SUBSEQUENT_NUM */
    if (msg->m.siCnStEvnt.subNum.eh.pres == PRESENT)
    {   
        SubsequentNum_NMS_to_ITS(&msg->m.siCnStEvnt.subNum, &ies[ieCount++]);
    }
    
    return ieCount;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate received USR message to an ITS USR message
 *      It retrieve the IE from the NMS msg, translate it into an ITS IE
 *      and put it in the array ies.
 *      This function is used by the function
 *            NMSRetrieveISUPMessage(ITS_SS7_HANDLE handle) only.
 *
 *  Input Parameters:
 *      SiAllSdus msg -- received NMS message (alreday checked that 
 *                       the indType is EVTSITDATIND)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     ITS_ISUP_IE ies[ITS_MAX_ISUP_IES] -- an array of IEs that are populated, 
 *
 *  Return Value:
 *      ieCount -- the number of IEs in the message
 ****************************************************************************/
int
ReceiveNmsUSR(SiAllSdus* msg, ITS_ISUP_IE* ies)
{
    /* starting from index zero */
    int ieCount = 0;

    /* ISUP_PRM_USER_TO_USER_INFO */
    if (msg->m.siInfoEvnt.usr2UsrInfo.eh.pres == PRESENT)
    {   
        Usr2UsrInfo_NMS_to_ITS(&msg->m.siInfoEvnt.usr2UsrInfo, &ies[ieCount++]);
    }    

     /* ISUP_PRM_ACCESS_TRANSPORT */
    if (msg->m.siInfoEvnt.accTrnspt.eh.pres == PRESENT)
    {   
        AccessTrnspt_NMS_to_ITS(&msg->m.siInfoEvnt.accTrnspt, &ies[ieCount++]);
    }

    return ieCount;
}
#endif /* CCITT */



/*****
****** functions for sending ITS ISUP messages
*****/

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(ANM, IAM) into a nms Connect Event (SiConEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiConEvent.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      conEnvet ---------- a translated NMS connect event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSConnectEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiConEvnt* conEvent)
{
    int ieIdx;
    ITS_OCTET   id;
    
    memset(conEvent, 0, sizeof(SiConEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to conEvent */
        switch (id)
        {    
        case ISUP_PRM_CONNECTION_REQ:
            ConnReq_ITS_to_NMS(&conEvent->connReq, &ies[ieIdx]);
            break;

        case ISUP_PRM_INFO_INDICATORS:
            InfoIndicators_ITS_to_NMS(&conEvent->infoInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_ACCESS_TRANSPORT:
            AccessTrnspt_ITS_to_NMS(&conEvent->accTrnspt, &ies[ieIdx]);
            break;

        case ISUP_PRM_BKWD_CALL_INDICATORS:
            BkwdCallInd_ITS_to_NMS(&conEvent->bckCallInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&conEvent->callRef, &ies[ieIdx]);
            break;

        case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:
            OpBkwdCallInd_ITS_to_NMS(&conEvent->optBckCalInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_NATURE_CONN_INDICATORS:
            NatConInd_ITS_to_NMS(&conEvent->natConInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_FWD_CALL_INDICATORS:
            FwdCallInd_ITS_to_NMS(&conEvent->fwdCallInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALLING_PARTY_CATEGORY:
            CgPtyCategory_ITS_to_NMS(&conEvent->cgPtyCat, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALLED_PARTY_NUM:
            CdPtyNum_ITS_to_NMS(&conEvent->cdPtyNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALLING_PARTY_NUM:
            CgPtyNum_ITS_to_NMS(&conEvent->cgPtyNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_DIGITS:
            GenericDgts_ITS_to_NMS(&conEvent->genDigits, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTING_NUM:
            RedirectingNum_ITS_to_NMS(&conEvent->redirgNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_INFO:
            RedirectionInfo_ITS_to_NMS(&conEvent->redirInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_ORIG_CALLED_NUM:
            OrigCdNum_ITS_to_NMS(&conEvent->origCdNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_SERVICE_ACTIVATION:
            ServActivation_ITS_to_NMS(&conEvent->serviceAct, &ies[ieIdx]);
            break;

        case ISUP_PRM_TRANSIT_NTWK_SELECT:
            TransmitNwSel_ITS_to_NMS(&conEvent->tranNetSel, &ies[ieIdx]);
            break;    
   
        case ISUP_PRM_INFO_REQ_INDICATORS:
            InfoReqInd_ITS_to_NMS(&conEvent->infoReqInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_SERVICE_INFO:
            UsrServInfo_ITS_to_NMS(&conEvent->usrServInfo, &ies[ieIdx]);
            break;

#if defined (ANSI)
        case ISUP_PRM_BUSINESS_GROUP:
            BusinessGrp_ITS_to_NMS(&conEvent->businessGrp, &ies[ieIdx]);
            break;

        case ISUP_PRM_NTWK_TRANSPORT:
            NetworkTrans_ITS_to_NMS(&conEvent->netTransport, &ies[ieIdx]);
            break;

        case ISUP_PRM_NOTIFICATION:
            Notification_ITS_to_NMS(&conEvent->notifInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CARRIER_ID:
            CarrierId_ITS_to_NMS(&conEvent->carrierId, &ies[ieIdx]);
            break;

        case ISUP_PRM_CARRIER_SELECTION_INFO:
            CarrierSelInfo_ITS_to_NMS(&conEvent->carSelInf, &ies[ieIdx]);
            break;

        case ISUP_PRM_CHARGE_NUMBER:
            ChargeNum_ITS_to_NMS(&conEvent->chargeNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_EGRESS_SERVICE:
            EgressServ_ITS_to_NMS(&conEvent->egress, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_ADDR:
            GenericAddr_ITS_to_NMS(&conEvent->genAddr, &ies[ieIdx]);
            break;

        case ISUP_PRM_JURISDICTION:
            JurisInfo_ITS_to_NMS(&conEvent->jurisInf, &ies[ieIdx]);
            break;

        case ISUP_PRM_ORIG_LINE_INFO:
            OrigLineInfo_ITS_to_NMS(&conEvent->origLineInf, &ies[ieIdx]);
            break;

        case ISUP_PRM_SERVICE_CODE:
            ServiceCode_ITS_to_NMS(&conEvent->serviceCode, &ies[ieIdx]);
            break;

        case ISUP_PRM_SPECIAL_PROCESS_REQUEST:
            SpecialProcessReq_ITS_to_NMS(&conEvent->specProcReq, &ies[ieIdx]);
            break;

        case ISUP_PRM_TRANSACTION_REQUEST:
            TransReq_ITS_to_NMS(&conEvent->transReq, &ies[ieIdx]);
            break;

#endif /* ANSI */

#if defined (CCITT)
        case ISUP_PRM_ACCESS_DELIVERY_INFO:
            AccessDeliverInfo_ITS_to_NMS(&conEvent->accDelInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALL_HISTORY_INFO:
            CallHistoryInfo_ITS_to_NMS(&conEvent->cllHstry, &ies[ieIdx]);
            break;

        case ISUP_PRM_CONNECTED_NUM:
            ConnectedNum_ITS_to_NMS(&conEvent->connNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_NOTIFICATION:
            GenericNotifInd_ITS_to_NMS(&conEvent->notifInd, &ies[ieIdx]);
            break;
    
        case ISUP_PRM_USER_TO_USER_INDICATORS:
            Usr2UsrInd_ITS_to_NMS(&conEvent->usr2UsrInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_TO_USER_INFO:
            Usr2UsrInfo_ITS_to_NMS(&conEvent->usr2UsrInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            ParmCompatInfo_ITS_to_NMS(&conEvent->parmCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_TX_MEDIUM_USED:
            TXMediumUsed_ITS_to_NMS(&conEvent->txMedUsed, &ies[ieIdx]);
            break;

        case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            NwkSpecFac_ITS_to_NMS(&conEvent->netFac, &ies[ieIdx]);
            break;

        case ISUP_PRM_REMOTE_OPS:
            RemoteOper_ITS_to_NMS(&conEvent->remotOper, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_NUM:
            RedirectionNum_ITS_to_NMS(&conEvent->redirNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            RedirecNumResrict_ITS_to_NMS(&conEvent->redirRstr, &ies[ieIdx]);
            break;

        case ISUP_PRM_ECHO_CTRL_INFO:
            EchoCtrlInfo_ITS_to_NMS(&conEvent->echoControl, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_NUM:
            GenericNum_ITS_to_NMS(&conEvent->genNmb, &ies[ieIdx]);
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT:
            TXMediumRequirement_ITS_to_NMS(&conEvent->txMedReq, &ies[ieIdx]);
            break;

        case ISUP_PRM_OPT_FWD_CALL_INDICATORS:
            OptionalFwdCallInd_ITS_to_NMS(&conEvent->opFwdCalInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE:
            ClosedUserGrpInterLockCode_ITS_to_NMS(&conEvent->cugIntCode, 
                                                  &ies[ieIdx]);
            break;
   
        case ISUP_PRM_PROP_DELAY_COUNTER:
            PropagationDelayCounter_ITS_to_NMS(&conEvent->propDly, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_SERVICE_INFO_PRIME:
            UsrServInfoPrime_ITS_to_NMS(&conEvent->usrServInfo1, &ies[ieIdx]);
            break;

        case ISUP_PRM_ORIG_ISC_PC:
            OrigIscPC_ITS_to_NMS(&conEvent->orgPteCde, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_REF:
            /* NMS doesn't seem to support Generic reference IE, 
             * put it in extended element */
            conEvent->elementExt[0].eh.pres = PRESENT;

            conEvent->elementExt[0].tknExt.pres = PRESENT;
            conEvent->elementExt[0].tknExt.type = id;
            conEvent->elementExt[0].tknExt.len = ies[ieIdx].param_length;
            /* TODO: copy val */
            break;

        case ISUP_PRM_MLPP_PRECEDENCE:
            MLPPPrecedence_ITS_to_NMS(&conEvent->mlppPrec, &ies[ieIdx]);
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT_PRIME:
            TxMdumReqPrime_ITS_to_NMS(&conEvent->txMedReqPr, &ies[ieIdx]);
            break;

        case ISUP_PRM_LOCATION_NUM:
            LocationNum_ITS_to_NMS(&conEvent->locNum, &ies[ieIdx]);
            break;
       
#endif /* CCITT */

        default:
            break;
        } /* switch id */
    } /* for loop */

} /* GetNMSConnectEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(ACM, CPG, FOT, INF, INR, SAM, IDR, IRS) 
 *      into a nms Connect Status Event (SiConStEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiConStEvent.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      conStEnvet -------- a translated NMS connect status event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSConnectStatusEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiCnStEvnt* conStEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(conStEvent, 0, sizeof(SiCnStEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to conStEvent */
        switch (id)
        {  
        case ISUP_PRM_BKWD_CALL_INDICATORS:
            BkwdCallInd_ITS_to_NMS(&conStEvent->bckCallInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CONNECTION_REQ:
            ConnReq_ITS_to_NMS(&conStEvent->connReq, &ies[ieIdx]);
            break;

        case ISUP_PRM_INFO_INDICATORS:
            InfoIndicators_ITS_to_NMS(&conStEvent->infoInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_INFO:
            RedirectionInfo_ITS_to_NMS(&conStEvent->redirInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_SERVICE_ACTIVATION:
            ServActivation_ITS_to_NMS(&conStEvent->serviceAct, &ies[ieIdx]);
            break;

        case ISUP_PRM_ACCESS_TRANSPORT:
            AccessTrnspt_ITS_to_NMS(&conStEvent->accTrnspt, &ies[ieIdx]);
            break;  
            
        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&conStEvent->callRef, &ies[ieIdx]);
            break;

        case ISUP_PRM_CAUSE_INDICATORS:
            CauseInd_ITS_to_NMS(&conStEvent->causeDgn, &ies[ieIdx]);
            break;

        case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:
            OpBkwdCallInd_ITS_to_NMS(&conStEvent->optBckCalInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_EVENT_INFO:
            EventInfo_ITS_to_NMS(&conStEvent->evntInfo, &ies[ieIdx]);
            break; 
            
        case ISUP_PRM_REDIRECTING_NUM:
            RedirectingNum_ITS_to_NMS(&conStEvent->redirgNum, &ies[ieIdx]);
            break;
            
        case ISUP_PRM_CALLING_PARTY_CATEGORY:
            CgPtyCategory_ITS_to_NMS(&conStEvent->cgPtyCat, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALLING_PARTY_NUM:
            CgPtyNum_ITS_to_NMS(&conStEvent->cgPtyNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_INFO_REQ_INDICATORS:
            InfoReqInd_ITS_to_NMS(&conStEvent->infoReqInd, &ies[ieIdx]);
            break;
        
#if defined (ANSI)
        case ISUP_PRM_BUSINESS_GROUP:
            BusinessGrp_ITS_to_NMS(&conStEvent->businessGrp, &ies[ieIdx]);
            break;

        case ISUP_PRM_NTWK_TRANSPORT:
            NetworkTrans_ITS_to_NMS(&conStEvent->netTransport, &ies[ieIdx]);
            break;

        case ISUP_PRM_NOTIFICATION:
            Notification_ITS_to_NMS(&conStEvent->notifInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CHARGE_NUMBER:
            ChargeNum_ITS_to_NMS(&conStEvent->chargeNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_ORIG_LINE_INFO:
            OrigLineInfo_ITS_to_NMS(&conStEvent->origLineInf, &ies[ieIdx]);
            break;

#endif /* ANSI */

#if defined (CCITT)
        case ISUP_PRM_ACCESS_DELIVERY_INFO:
            AccessDeliverInfo_ITS_to_NMS(&conStEvent->accDelInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALL_DIVERSION_INFO:
            CallDiversionInfo_ITS_to_NMS(&conStEvent->cllDivr, &ies[ieIdx]);
            break;

        case ISUP_PRM_ECHO_CTRL_INFO:
            EchoCtrlInfo_ITS_to_NMS(&conStEvent->echoControl, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_NOTIFICATION:
            GenericNotifInd_ITS_to_NMS(&conStEvent->notifInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            NwkSpecFac_ITS_to_NMS(&conStEvent->netFac, &ies[ieIdx]);
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            ParmCompatInfo_ITS_to_NMS(&conStEvent->parmCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_NUM:
            RedirectionNum_ITS_to_NMS(&conStEvent->redirNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            RedirecNumResrict_ITS_to_NMS(&conStEvent->redirRstr, &ies[ieIdx]);
            break;

        case ISUP_PRM_REMOTE_OPS:
            RemoteOper_ITS_to_NMS(&conStEvent->remotOper, &ies[ieIdx]);
            break;

        case ISUP_PRM_TX_MEDIUM_USED:
            TXMediumUsed_ITS_to_NMS(&conStEvent->txMedUsed, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_TO_USER_INDICATORS:
            Usr2UsrInd_ITS_to_NMS(&conStEvent->usr2UsrInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_TO_USER_INFO:
            Usr2UsrInfo_ITS_to_NMS(&conStEvent->usr2UsrInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_NUM:
            GenericNum_ITS_to_NMS(&conStEvent->genNmb, &ies[ieIdx]);
            break;

        case ISUP_PRM_MSG_COMPAT_INFO:
            MsgCompatInfo_ITS_to_NMS(&conStEvent->msgCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_MCID_REQ_INDICATOR:
            MCIDReqInd_ITS_to_NMS(&conStEvent->mcidReq, &ies[ieIdx]);
            break;

        case ISUP_PRM_MCID_RESP_INDICATOR:
            MCIDRspInd_ITS_to_NMS(&conStEvent->mcidRsp, &ies[ieIdx]);
            break;

        case ISUP_PRM_SUBSEQUENT_NUM:
            SubsequentNum_ITS_to_NMS(&conStEvent->subNum, &ies[ieIdx]);
            break;
       
#endif /* CCITT */

        default:
            break;
        } /* switch id */
    } /* for loop */

} /* GetNMSConnectStatusEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(PAM) into a nms Info Event (SiInfoEvnt).  
 *      It encodes the ITS_ISUP_IE* ies array, put it in the SiInfoEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be encoded
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      infoEvent -------- a translated NMS info event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSPAM(ITS_ISUP_IE* ies, int ieCount, 
          ISUP_MSG_DESC* desc, SiInfoEvnt* infoEvent)
{
    ITS_EVENT   event;
    ITS_HDR     hdr;
    int         evoffset;

    memset(infoEvent, 0, sizeof(SiInfoEvnt));

    /* In the ISUP_Encode function, hdr is providing the CICs, 
     * we don't really care */
    memset(&hdr, 0, sizeof(ITS_HDR));

    if ( ISUP_Encode(ies, ieCount, ISUP_MSG_PAM, &event, &hdr, desc)
         != ITS_SUCCESS )
    {
        printf("Error encoding PAM message!!\n");
    }

    /* remove the header part of ITS_Event 
     * msgType + CIC + MTP3_HEADER */
    evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(MTP3_HEADER);

    /* copy the data part into infoEvent passAlng */
    infoEvent->passAlng.eh.pres = PRESENT;

    SetTknStr(&infoEvent->passAlng.passAlng, 
              &event.data[evoffset], event.len - evoffset);
    
} /* GetNMSPAM */



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(PAM, USR) into a nms Info Event (SiInfoEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiInfoEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      infoEvent -------- a translated NMS info event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSInfoEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiInfoEvnt* infoEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(infoEvent, 0, sizeof(SiInfoEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to infoEvent */
        switch (id)
        { 
        case ISUP_PRM_ACCESS_TRANSPORT:
            AccessTrnspt_ITS_to_NMS(&infoEvent->accTrnspt, &ies[ieIdx]);
            break;
            
        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&infoEvent->callRef, &ies[ieIdx]);
            break;

#if defined (CCITT)
        case ISUP_PRM_USER_TO_USER_INFO:
            Usr2UsrInfo_ITS_to_NMS(&infoEvent->usr2UsrInfo, &ies[ieIdx]);
            break;       
#endif /* CCITT */

        default:
            break;

        } /* switch id */
    } /* for loop */

} /* GetNMSInfoEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(REL, RLC) into a nms Release Event (SiRelEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiRelEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      relEvent --------- a translated NMS info event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSReleaseEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiRelEvnt* relEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(relEvent, 0, sizeof(SiRelEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to relEvent */
        switch (id)
        { 
        case ISUP_PRM_CAUSE_INDICATORS:
            CauseInd_ITS_to_NMS(&relEvent->causeDgn, &ies[ieIdx]);
            break;

        case ISUP_PRM_ACCESS_TRANSPORT:
            AccessTrnspt_ITS_to_NMS(&relEvent->accTrnspt, &ies[ieIdx]);
            break;  

        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&relEvent->callRef, &ies[ieIdx]);
            break;

        case ISUP_PRM_AUTO_CONGEST_LEVEL:
            AutoCongestLevel_ITS_to_NMS(&relEvent->autoCongLvl, &ies[ieIdx]);
            break; 
            
        case ISUP_PRM_REDIRECTION_INFO:
            RedirectionInfo_ITS_to_NMS(&relEvent->redirInfo, &ies[ieIdx]);
            break;

#if defined (ANSI)
        case ISUP_PRM_CHARGE_NUMBER:
            ChargeNum_ITS_to_NMS(&relEvent->chargeNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_GENERIC_ADDR:
            GenericAddr_ITS_to_NMS(&relEvent->genAddr, &ies[ieIdx]);
            break;
#endif
#if defined (CCITT)
        case ISUP_PRM_USER_TO_USER_INDICATORS:
            Usr2UsrInd_ITS_to_NMS(&relEvent->usr2UsrInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_TO_USER_INFO:
            Usr2UsrInfo_ITS_to_NMS(&relEvent->usr2UsrInfo, &ies[ieIdx]);
            break;        

        case ISUP_PRM_REDIRECTION_NUM:
            RedirectionNum_ITS_to_NMS(&relEvent->redirNum, &ies[ieIdx]);
            break;

        case ISUP_PRM_SIGNALLING_POINT_CODE:
            SingalingPC_ITS_to_NMS(&relEvent->sigPointCode, &ies[ieIdx]);
            break;

        case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            NwkSpecFac_ITS_to_NMS(&relEvent->netFac, &ies[ieIdx]);
            break;

        case ISUP_PRM_ACCESS_DELIVERY_INFO:
            AccessDeliverInfo_ITS_to_NMS(&relEvent->accDelInfo, &ies[ieIdx]);
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            ParmCompatInfo_ITS_to_NMS(&relEvent->parmCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            RedirecNumResrict_ITS_to_NMS(&relEvent->redirRstr, &ies[ieIdx]);
            break;

#endif /* CCITT */

        default:
            break;
        } /* switch id */
    } /* for loop */

} /* GetNMSReleaseEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(RES) into a nms Resume Event (SiResmEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiResmEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      resEvent --------- a translated NMS resume event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSResumeEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiResmEvnt* resEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(resEvent, 0, sizeof(SiResmEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to resEvent */
        switch (id)
        { 
        case ISUP_PRM_SUSP_RESUM_INDICATORS:
            SusResumeInd_ITS_to_NMS(&resEvent->susResInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&resEvent->callRef, &ies[ieIdx]);
            break;

        default:
            break;
        }
    } /* for loop */

} /* GetNMSResumeEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(SUS) into a nms Suspend Event (SiSuspEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiSuspEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      resEvent --------- a translated NMS suspend event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSSuspendEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiSuspEvnt* susEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(susEvent, 0, sizeof(SiSuspEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to susEvent */
        switch (id)
        { 
        case ISUP_PRM_SUSP_RESUM_INDICATORS:
            SusResumeInd_ITS_to_NMS(&susEvent->susResInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&susEvent->callRef, &ies[ieIdx]);
            break;

        default:
            break;
        }
    } /* for loop */

} /* GetNMSSuspendEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(BLO, BLA, CGB, CGBA, CQM, GRS, CGU, CGUA, COT, 
 *      CCR, LPA, RSC, UBL, UBA, CRM, CRA) into a nms Status Event (SiStaEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiStaEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      resEvent --------- a translated NMS status event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSStatusEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiStaEvnt* stEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(stEvent, 0, sizeof(SiStaEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to stEvent */
        switch (id)
        { 
        case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
            CGSuperMsgTypeInd_ITS_to_NMS(&stEvent->cgsmti, &ies[ieIdx]);
            break;

        case ISUP_PRM_RANGE_STATUS:
            RangeStat_ITS_to_NMS(&stEvent->rangStat, &ies[ieIdx]);
            break;

        case ISUP_PRM_CONTINUITY_INDICATORS:
            ContinuityInd_ITS_to_NMS(&stEvent->contInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_NATURE_CONN_INDICATORS:
            NatConInd_ITS_to_NMS(&stEvent->natConInd, &ies[ieIdx]);
            break;

        default:
            break;
        }
    } /* for loop */

} /* GetNMSStatusEvent */


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Translate an ITS event(FAA, FRJ, FAC, FAR) into a nms Facility Event(SiFacEvnt).  
 *      It retrieve the IE from the ITS_ISUP_IE* ies array, translate it into 
 *      a NMS ISUP IE and put it in the SiFacEvnt.
 *      The function is called after ISUP_MessageSanityCheck succeeded, so all
 *      the F & V parms are for sure present and that the ISUP msg is valid for
 *      the protocol family.
 *      This function is used by the function
 *            NMSSendISUPEvent(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR* hdr,
 *                ITS_ISUP_IE* ies, int ieCount, ISUP_MSG_DESC* desc) only.
 *
 *  Input Parameters:
 *      ITS_ISUP_IE* ies -- an array of IEs that are to be translated,
 *      ieCount ----------- number of IEs in the array ies
 *      desc -------------- message descriptor of the message to be sent 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      facEvent --------- a translated NMS facility event ready to send
 *
 *  Return Value:
 *      none
 ****************************************************************************/
void
GetNMSFacilityEvent(ITS_ISUP_IE* ies, int ieCount, 
                   ISUP_MSG_DESC* desc, SiFacEvnt* facEvent)
{
    int ieIdx;
    ITS_OCTET   id;

    memset(facEvent, 0, sizeof(SiFacEvnt));

    /* The sanity check has ensured the ISUP msg is valid */
    for (ieIdx = 0; ieIdx < ieCount; ieIdx++)
    {
        id = ies[ieIdx].param_id;
    
        /* convert an ITS_ISUP_IE itsIE to a nms ie and add it to facEvent */
        switch (id)
        {
        case ISUP_PRM_CALL_REF:
            CallRef_ITS_to_NMS(&facEvent->callRef, &ies[ieIdx]);
            break;

        case ISUP_PRM_CONNECTION_REQ:
            ConnReq_ITS_to_NMS(&facEvent->connReq, &ies[ieIdx]);
            break;
        
        case ISUP_PRM_CAUSE_INDICATORS:
            CauseInd_ITS_to_NMS(&facEvent->causeDgn, &ies[ieIdx]);
            break;
        
        case ISUP_PRM_SERVICE_ACTIVATION:
            ServActivation_ITS_to_NMS(&facEvent->serviceAct, &ies[ieIdx]);
            break;

#if defined(CCITT)
        case ISUP_PRM_FACILITY_INDICATOR:
            FacilityInd_ITS_to_NMS(&facEvent->facInd, &ies[ieIdx]);
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            ParmCompatInfo_ITS_to_NMS(&facEvent->parmCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_MSG_COMPAT_INFO:
            MsgCompatInfo_ITS_to_NMS(&facEvent->msgCom, &ies[ieIdx]);
            break;

        case ISUP_PRM_REMOTE_OPS:
            RemoteOper_ITS_to_NMS(&facEvent->remotOper, &ies[ieIdx]);
            break;

        case ISUP_PRM_USER_TO_USER_INDICATORS:
            Usr2UsrInd_ITS_to_NMS(&facEvent->usr2UsrInd, &ies[ieIdx]);
            break;
#endif 

        default:
            break;
        }
    } /* for loop */

} /* GetNMSFacilityEvent */


#endif /* INCLUDE_ISUP */
