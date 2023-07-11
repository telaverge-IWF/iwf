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
 * ID:$Id: ISUP_ProcessMsg.h,v 9.1 2005/03/23 12:55:06 cvsadmin Exp $
 * LOG:$Log: ISUP_ProcessMsg.h,v $
 * LOG:Revision 9.1  2005/03/23 12:55:06  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 8.5  2005/03/21 13:54:17  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.3.2.2  2003/05/09 05:30:45  ssingh
 * LOG:Changes back ported from current to 6.3
 * LOG:
 * LOG:Revision 8.3  2003/04/04 05:22:53  ssingh
 * LOG:Conformation Handling removed from App as now No conformation.
 * LOG:
 * LOG:Revision 8.2  2003/02/27 06:13:35  akumar
 * LOG:Added ITU Variant
 * LOG:
 * LOG:Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG:Begin PR6.4
 * LOG:
 * LOG:Revision 1.3  2003/01/31 14:09:32  ssingh
 * LOG:CCR handling in App. New CRI state handling in App.
 * LOG:And one Macro added for getting Message type out of received Event.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/
#include <its.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#include <isup_variants.h>
#include <isup_cmn.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

#if defined (CCITT)
typedef struct _opcdpcinfo
{
    ITS_USHORT opc;
    ITS_USHORT dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#elif defined (ANSI)
typedef struct _opcdpcinfo
{
    ITS_UINT   opc;
    ITS_UINT   dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#else "Protocol Not Defined"
#endif

/* for CIC info being stored in Application
 * for its own data base
 */
typedef struct _cicInfo
{
  ushort              cic_num;
  unsigned char       cic_state;
  unsigned char       fsm_state;
} cicInfo;

cicInfo cicStatus[512];

ushort numOfCICs;

typedef enum
{
     CPC_IDLE,
     CPC_WAIT_COT_REPORT,
     CPC_WAIT_IN_ACM,
     CPC_WAIT_IN_ANM,
     CPC_RCVD_IN_ANM,
     CPC_WAIT_IN_RES,
     CPC_WAIT_IN_RLC,
     CPC_WAIT_IN_COT,
     CPC_SENT_OUT_ACM,
     CPC_SENT_OUT_ANM,
     CPC_WAIT_OUT_RES
} ISUP_STATE;

/* Functions */

void ISUP_HandleIndicationRcvd (ITS_USHORT cic, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingIAMMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingCOTMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingACMMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingANMMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingSUSMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingRESMsg (ITS_HDR *hdr, ITS_EVENT *event, 
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingCVTMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingCVRMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_HandleIncomingRELMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingCCRMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);
                   
void ISUP_ProcessIndication (ITS_USHORT cic, ITS_EVENT *event, 
                                             ITS_ISUP_IE ies);

void ISUP_ProcessErrorIndication (ITS_USHORT cic, ITS_EVENT *event, 
                                             ITS_ISUP_IE ies);

void ISUP_ProcessTimeoutIndication (ITS_USHORT cic, ITS_EVENT *event,
                                             ITS_ISUP_IE ies);

void ISUP_HandleOutgoingCPCMsg (ITS_OCTET isupMsgType, ITS_USHORT cic,
                                       ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleOutgoingGRSMsg (ITS_USHORT startCic, 
                      ITS_ISUP_IE *ies, int ieCount);
void ISUP_HandleOutgoingRSCMsg (ITS_USHORT cic);

void ISUP_HandleIncomingCONMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingBLOMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingCGBMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingCGUMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingRSCMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingGRSMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);

void ISUP_HandleIncomingUBLMsg (ITS_HDR *hdr, ITS_EVENT *event,
                                ITS_ISUP_IE *ies, int ieCount);


extern void ISUP_UpdateCicStatus (ITS_USHORT cic);
extern void ISUP_IdleCic (ITS_USHORT cic);
extern void ISUP_SetLocalBlock (ITS_USHORT cic);
extern void ISUP_SetRemoteBlock (ITS_USHORT cic);
extern void ISUP_RemoveRemoteBlock (ITS_USHORT cic);
extern void ISUP_RemoveLocalBlock (ITS_USHORT cic);
extern void ISUP_SetGroupCicBlockingState (ITS_USHORT startCic, 
                 ITS_EVENT *event, ITS_ISUP_IE *ies, int  ieCount);
extern void ISUP_SetGroupCicBlockingStat (ITS_USHORT startCic, 
                 ITS_EVENT *event, ITS_ISUP_IE *ies, int  ieCount);
extern ITS_BOOLEAN ISUP_GetCicIndex (ITS_USHORT startCic, int *index);
extern ITS_BOOLEAN ISUP_GetFreeCircuit (ITS_USHORT cic, ITS_USHORT *freeCIC);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */
