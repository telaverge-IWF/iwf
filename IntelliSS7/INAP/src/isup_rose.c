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
 *     FILE: isup_rose.c                                                    *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: isup_rose.c,v 9.1 2005/03/23 12:51:44 cvsadmin Exp $
 *
 * LOG: $Log: isup_rose.c,v $
 * LOG: Revision 9.1  2005/03/23 12:51:44  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:57  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:34  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:04  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:57:57  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:19:52  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/05/25 01:34:58  mmiers
 * LOG:
 * LOG:
 * LOG: Update to use ISUP message descriptors.
 * LOG:
 * LOG: Revision 1.10  1999/05/24 16:42:58  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize API.
 * LOG:
 * LOG: Revision 1.9  1999/03/02 22:47:47  mmiers
 * LOG:
 * LOG:
 * LOG: Update for new TCAP operation name.
 * LOG:
 * LOG: Revision 1.8  1999/03/02 22:08:39  mmiers
 * LOG:
 * LOG:
 * LOG: Update for prototypes.
 * LOG:
 * LOG: Revision 1.7.2.1  1999/03/02 21:42:08  mmiers
 * LOG:
 * LOG:
 * LOG: Continue release preparation cleanup.
 * LOG:
 * LOG: Revision 1.7  1998/07/02 14:06:22  mmiers
 * LOG: Get rid of its_debug everywhere.
 * LOG:
 * LOG: Revision 1.6  1998/06/05 20:08:55  mmiers
 * LOG: Tweaking things for the release.  Now to retag.
 * LOG:
 * LOG: Revision 1.5  1998/05/21 02:15:25  mmiers
 * LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
 * LOG: files in builds.  Update the test to include the SCCP library.  I'll
 * LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
 * LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
 * LOG: else's SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/05/04 22:57:33  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.3  1998/05/04 21:14:27  mmiers
 * LOG: Work on IS634.
 * LOG:
 * LOG: Revision 1.2  1998/04/29 23:02:02  mmiers
 * LOG: Cleanup after integration work.
 * LOG:
 * LOG: Revision 1.1  1998/02/05 16:11:00  mmiers
 * LOG: Don't forget the IP side of INAP.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <its.h>
#include <itu/isup.h>
#include <itu/sccp.h>
#include <itu/tcap.h>
#include <itu/inap.h>

#include "INAP-types.h"

extern void convert_cpt_to_ro(TCAP_CPT *cpt, ITS_ISUP_IE *ie);

static int local_debug = 0;

/*
 * ROSE tunneled over ISUP
 */
/*** PROMPT AND COLLECT USER INFORMATION ***/
int
ISUP_SendFacilityPromptAndCollectUserInformation(ITS_HANDLE handle,
                                                 ITS_HDR *hdr,
                                                 ITS_ISUP_IE *ies,
                                                 int ieCount,
                                                 TCAP_CPT *cpt,
                                                 void *data)
{
    PE pe;
    int len, i;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            if (encode_INAP_PromptAndCollectUserInformation(&pe, 1, 0,
                                                            NULL,
                                                            data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }


            if (local_debug)
            {
                print_INAP_PromptAndCollectUserInformation(pe, 1, 0,
                                                           NULL, data);
            }

            if (pe2ssdu(pe, &enc, &len) != OK)
            {
                free_INAP_PromptAndCollectUserInformation(data);

                return ITS_BADTCAPMESSAGE;
            }

            cpt->u.invoke.operation.len = 3;
            cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.invoke.operation.data[1] = 1;
            cpt->u.invoke.operation.data[2] = INAP_OP_promptAndCollectUserInformation;
            cpt->u.invoke.param.len = len;
            memcpy(cpt->u.invoke.param.data, enc, len);

            convert_cpt_to_ro(cpt, &ies[i]);

            free(enc);

            free_INAP_PromptAndCollectUserInformation(data);

            pe_free(pe);
        }
    }

    return ISUP_SendEvent(handle, ISUP_MSG_FAC, hdr,
                          ies, ieCount, &ISUP_FAC_Desc);
}

int
ISUP_DecodeFacilityPromptAndCollectUserInformation(ITS_HANDLE handle,
                                                  ITS_HDR *hdr,
                                                  ITS_ISUP_IE *ies,
                                                  int *ieCount,
                                                  TCAP_CPT *cpt,
                                                  void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err, i;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < *ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                         cpt->u.invoke.param.len,
                         NULL, &err);

            if (err != PS_ERR_NONE || pe == NULL)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (decode_INAP_PromptAndCollectUserInformation(pe, 1, NULL,
                                                            NULL,
                                                            data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_PromptAndCollectUserInformation(pe, 1, 0,
                                                           NULL, data);
            }

            pe_free(pe);
        }
    }

    return ret;
}

/*** RECEIVED INFORMATION ***/
int
ISUP_SendFacilityReceivedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                    ITS_ISUP_IE *ies, int ieCount,
                                    TCAP_CPT *cpt, void *data)
{
    PE pe;
    int len, i;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            if (encode_INAP_ReceivedInformationArg(&pe, 1, 0,
                                                   NULL, data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_ReceivedInformationArg(pe, 1, 0, NULL, data);
            }

            if (pe2ssdu(pe, &enc, &len) != OK)
            {
                free_INAP_ReceivedInformationArg(data);
 
                return ITS_BADTCAPMESSAGE;
            }

            cpt->u.result.operation.len = 3;
            cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.result.operation.data[1] = 1;
            cpt->u.result.operation.data[2] = INAP_OP_promptAndCollectUserInformation;
            cpt->u.result.param.len = len;
            memcpy(cpt->u.result.param.data, enc, len);

            convert_cpt_to_ro(cpt, &ies[i]);

            free(enc);

            free_INAP_ReceivedInformationArg(data);

            pe_free(pe);
        }
    }

    return ISUP_SendEvent(handle, ISUP_MSG_FAC, hdr,
                          ies, ieCount, &ISUP_FAC_Desc);
}

int
ISUP_DecodeFacilityReceivedInformation(ITS_HANDLE handle, ITS_HDR *hdr,
                                      ITS_ISUP_IE *ies, int *ieCount,
                                      TCAP_CPT *cpt, void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err, i;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < *ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            pe = ssdu2pe((char *)cpt->u.result.param.data,
                         cpt->u.result.param.len,
                         NULL, &err);

            if (err != PS_ERR_NONE || pe == NULL)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (decode_INAP_ReceivedInformationArg(pe, 1, NULL, NULL,
                                                   data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_ReceivedInformationArg(pe, 1, 0, NULL, data);
            }

            pe_free(pe);
        }
    }

    return ret;
}

/*** PLAY ANNOUNCEMENT ***/
int
ISUP_SendFacilityPlayAnnouncement(ITS_HANDLE handle,
                                 ITS_HDR *hdr,
                                 ITS_ISUP_IE *ies,
                                 int ieCount,
                                 TCAP_CPT *cpt,
                                 void *data)
{
    PE pe;
    int len, i;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            if (encode_INAP_PlayAnnouncementArg(&pe, 1, 0,
                                                NULL, data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_PlayAnnouncementArg(pe, 1, 0, NULL, data);
            }

            if (pe2ssdu(pe, &enc, &len) != OK)
            {
                free_INAP_PlayAnnouncementArg(data);
 
                return ITS_BADTCAPMESSAGE;
            }

            cpt->u.invoke.operation.len = 3;
            cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.invoke.operation.data[1] = 1;
            cpt->u.invoke.operation.data[2] = INAP_OP_playAnnouncement;
            cpt->u.invoke.param.len = len;
            memcpy(cpt->u.invoke.param.data, enc, len);

            convert_cpt_to_ro(cpt, &ies[i]);

            free(enc);

            free_INAP_PlayAnnouncementArg(data);

            pe_free(pe);
        }
    }

    return ISUP_SendEvent(handle, ISUP_MSG_FAC, hdr,
                          ies, ieCount, &ISUP_FAC_Desc);
}

int
ISUP_DecodeFacilityPlayAnnouncement(ITS_HANDLE handle,
                                   ITS_HDR *hdr,
                                   ITS_ISUP_IE *ies,
                                   int *ieCount,
                                   TCAP_CPT *cpt,
                                   void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err, i;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < *ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                         cpt->u.invoke.param.len,
                         NULL, &err);

            if (err != PS_ERR_NONE || pe == NULL)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (decode_INAP_PlayAnnouncementArg(pe, 1, NULL, NULL,
                                                data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_PlayAnnouncementArg(pe, 1, 0, NULL, data);
            }

            pe_free(pe);
        }
    }

    return ret;
}

/*** SPECIALIZED RESOURCE REPORT ***/
int
ISUP_SendFacilitySpecializedResourceReport(ITS_HANDLE handle,
                                          ITS_HDR *hdr,
                                          ITS_ISUP_IE *ies,
                                          int ieCount,
                                          TCAP_CPT *cpt,
                                          void *data)
{
    PE pe;
    int len, i;
    char *enc;

#ifdef DEBUG
    assert((handle != NULL && hdr != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            if (encode_INAP_SpecializedResourceReportArg(&pe, 1, 0,
                                                         NULL, data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_SpecializedResourceReportArg(pe, 1, 0, NULL, data);
            }

            if (pe2ssdu(pe, &enc, &len) != OK)
            {
                free_INAP_SpecializedResourceReportArg(data);
 
                return ITS_BADTCAPMESSAGE;
            }

            cpt->u.invoke.operation.len = 3;
            cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
            cpt->u.invoke.operation.data[1] = 1;
            cpt->u.invoke.operation.data[2] = INAP_OP_specializedResourceReport;
            cpt->u.invoke.param.len = len;
            memcpy(cpt->u.invoke.param.data, enc, len);

            convert_cpt_to_ro(cpt, &ies[i]);

            free(enc);

            free_INAP_SpecializedResourceReportArg(data);

            pe_free(pe);
        }
    }

    return ISUP_SendEvent(handle, ISUP_MSG_FAC, hdr,
                          ies, ieCount, &ISUP_FAC_Desc);
}

int
ISUP_DecodeFacilitySpecializedResourceReport(ITS_HANDLE handle,
                                            ITS_HDR *hdr,
                                            ITS_ISUP_IE *ies,
                                            int *ieCount,
                                            TCAP_CPT *cpt,
                                            void **data)
{
    PE pe;
    int ret = ITS_SUCCESS, err, i;

#ifdef DEBUG
    assert((handle != NULL && cpt != NULL && data != NULL));
#endif
    for (i = 0; i < *ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
        {
            pe = ssdu2pe((char *)cpt->u.invoke.param.data,
                         cpt->u.invoke.param.len,
                         NULL, &err);

            if (err != PS_ERR_NONE || pe == NULL)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (decode_INAP_SpecializedResourceReportArg(pe, 1, NULL, NULL,
                                                         data) == NOTOK)
            {
                return ITS_BADTCAPMESSAGE;
            }

            if (local_debug)
            {
                print_INAP_SpecializedResourceReportArg(pe, 1, 0, NULL, data);
            }

            pe_free(pe);
        }
    }

    return ret;
}
