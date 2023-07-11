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
 * CONTRACT: IntelliSS7                                                     *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: GSMSMS.c,v 9.2 2007/01/10 11:14:59 yranade Exp $
 *
 * LOG: $Log: GSMSMS.c,v $
 * LOG: Revision 9.2  2007/01/10 11:14:59  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:25  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:17  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:03  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:56:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/04/13 21:28:20  mmiers
 * LOG:
 * LOG:
 * LOG: More changes from Saritel integration.
 * LOG:
 * LOG: Revision 2.3  2000/04/03 21:27:46  mmiers
 * LOG:
 * LOG:
 * LOG: Tandemize this.
 * LOG:
 * LOG: Revision 2.2  2000/04/03 21:23:02  mmiers
 * LOG:
 * LOG:
 * LOG: Finish the prototypes.
 * LOG:
 * LOG: Revision 2.1  2000/03/27 15:25:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add the SMS stuff.
 * LOG:
 *
 ****************************************************************************/

#if !defined(TANDEM)

#include <stdlib.h>
#include <string.h>

#include <GSMSMS.h>

#else /* TANDEM */

#include <stdlibh>
#include <stringh>

#include <GSMSMSh>

#endif /* TANDEM */

void
GSM_SMSCB_7BitSet(ITS_OCTET *array, ITS_USHORT offset,
                  ITS_OCTET value)
{
    ITS_USHORT bit, byte;
    ITS_OCTET himask, lomask;

    byte = (offset * 7) / 8;
    bit = (offset * 7) % 8;
    lomask = 0x7FU << bit;
    himask = 0x7FU >> (8 - bit);

    array[byte] &= ~lomask;
    array[byte] |= (value << bit) & lomask;
    if (bit != 0 && bit != 1)
    {
        array[byte+1] &= ~himask;
        array[byte+1] |= (value >> (8 - bit)) & himask;
    }
}

ITS_OCTET
GSM_SMSCB_7BitGet(ITS_OCTET *array, ITS_USHORT offset)
{
    ITS_USHORT bit, byte;
    ITS_OCTET himask, lomask;
    ITS_OCTET value = 0;

    byte = (offset * 7) / 8;
    bit = (offset * 7) % 8;
    lomask = 0x7FU << bit;
    himask = 0x7FU >> (8 - bit);

    value = (array[byte] & lomask) >> bit;
    if (bit != 0 && bit != 1)
    {
        value |= (array[byte+1] & himask) << (8 - bit);
    }

    return (value);
}

int
GSM_SMS_EncodeMsg(int rpType, int dir,
                  GSM_SMS_MSG *msg,
                  char *buf, int *len)
{
    *len = 0;

    buf[*len] = msg->firstOctet;
    (*len)++;

    switch (rpType)
    {
    case GSM_SMRL_RP_MO_DATA:
    case GSM_SMRL_RP_MT_DATA:
    case GSM_SMRL_RP_ALERT_SC:
    case GSM_SMRL_RP_SM_MEM_AVAIL:

        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_TO_MS:
            /* orig addr */
            memcpy(&buf[*len], &msg->sms.deliver.origAddr,
                   msg->sms.deliver.origAddr.addr_len + 1);
            *len += msg->sms.deliver.origAddr.addr_len + 1;

            /* protocol identifier */
            buf[*len] = msg->sms.deliver.protIdent;
            (*len)++;

            /* data code scheme */
            buf[*len] = msg->sms.deliver.dataCodeScheme;
            (*len)++;

            /* sc Timestamp */
            memcpy(&buf[*len], &msg->sms.deliver.scTimestamp,
                   sizeof(GSM_TIME_STAMP));
            *len += sizeof(GSM_TIME_STAMP);

            /* user data len */
            buf[*len] = msg->sms.deliver.userDataLen;
            (*len)++;

            /* user data */
            if (msg->sms.deliver.userDataLen)
            {
                memcpy(&buf[*len], msg->sms.deliver.userData,
                       msg->sms.deliver.userDataLen);
                *len += msg->sms.deliver.userDataLen;
            }
            break;

        case GSM_SMS_TP_MTI_STATUS_REPORT_TO_MS:
            if (!dir)
            {
                /* msg ref */
                buf[*len] = msg->sms.status_report.msgRef;
                (*len)++;

                /* recip addr */
                memcpy(&buf[*len], &msg->sms.status_report.recipAddr,
                       msg->sms.status_report.recipAddr.addr_len + 1);
                *len += msg->sms.status_report.recipAddr.addr_len + 1;

                /* sc timestamp */
                memcpy(&buf[*len], &msg->sms.status_report.scTimestamp,
                       sizeof(GSM_TIME_STAMP));
                *len += sizeof(GSM_TIME_STAMP);

                /* discharge time */
                memcpy(&buf[*len], &msg->sms.status_report.dischargeTime,
                       sizeof(GSM_TIME_STAMP));
                *len += sizeof(GSM_TIME_STAMP);

                /* status */
                buf[*len] = msg->sms.status_report.status;
                (*len)++;

                /* param ind */
                buf[*len] = msg->sms.status_report.paramInd;
                (*len)++;

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_PID_BIT)
                {
                    /* prot ident */
                    buf[*len] = msg->sms.status_report.protIdent;
                    (*len)++;
                }

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_DCS_BIT)
                {
                    /* data code scheme */
                    buf[*len] = msg->sms.status_report.dataCodeScheme;
                    (*len)++;
                }

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_UDL_BIT)
                {
                    /* user data len */
                    buf[*len] = msg->sms.status_report.userDataLen;
                    (*len)++;

                    /* user data */
                    if (msg->sms.status_report.userDataLen)
                    {
                        memcpy(&buf[*len], msg->sms.status_report.userData,
                               msg->sms.status_report.userDataLen);
                        *len += msg->sms.status_report.userDataLen;
                    }
                }
            }
            else
            {
                /* case GSM_SMS_TP_MTI_COMMAND_TO_SC: */
                /* msg ref */
                buf[*len] = msg->sms.command.msgRef;
                (*len)++;

                /* prot ident */
                buf[*len] = msg->sms.command.protIdent;
                (*len)++;

                /* cmd type */
                buf[*len] = msg->sms.command.cmdType;
                (*len)++;

                /* msg number */
                buf[*len] = msg->sms.command.msgNumber;
                (*len)++;

                /* dest addr */
                memcpy(&buf[*len], &msg->sms.command.destAddr,
                       msg->sms.command.destAddr.addr_len + 1);
                *len += msg->sms.command.destAddr.addr_len + 1;

                /* cmd data len */
                buf[*len] = msg->sms.command.cmdDataLen;
                (*len)++;

                /* user data */
                if (msg->sms.command.cmdDataLen)
                {
                    memcpy(&buf[*len], msg->sms.command.cmdData,
                           msg->sms.command.cmdDataLen);
                    *len += msg->sms.command.cmdDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_TO_SC:
            /* msg ref */
            buf[*len] = msg->sms.submit.msgRef;
            (*len)++;

            /* dest addr */
            memcpy(&buf[*len], &msg->sms.submit.destAddr,
                   msg->sms.submit.destAddr.addr_len + 1);
            *len += msg->sms.submit.destAddr.addr_len + 1;

            /* prot ident */
            buf[*len] = msg->sms.submit.protIdent;
            (*len)++;

            /* data code scheme */
            buf[*len] = msg->sms.submit.dataCodeScheme;
            (*len)++;

            /* valid period */
            if ((msg->firstOctet & GSM_SMS_TP_VPF_MASK) == GSM_SMS_TP_VPF_NOT_PRESENT)
            {
                /* do nothing */
            }
            else if ((msg->firstOctet & GSM_SMS_TP_VPF_MASK) == GSM_SMS_TP_VPF_RELATIVE)
            {
                /* one byte */
                buf[*len] = msg->sms.submit.validPeriod.year;
                (*len)++;
            }
            else
            {
                /* seven bytes */
                memcpy(&buf[*len], &msg->sms.submit.validPeriod,
                       sizeof(GSM_TIME_STAMP));
                *len += sizeof(GSM_TIME_STAMP);
            }

            /* user data len */
            buf[*len] = msg->sms.submit.userDataLen;
            (*len)++;

            /* user data */
            if (msg->sms.submit.userDataLen)
            {
                memcpy(&buf[*len], msg->sms.submit.userData,
                       msg->sms.submit.userDataLen);
                *len += msg->sms.submit.userDataLen;
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    case GSM_SMRL_RP_ACK:
        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_REPORT_TO_SC:
            /* param ind */
            buf[*len] = msg->sms.deliver_report.paramInd;
            (*len)++;

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                /* prot ident */
                buf[*len] = msg->sms.deliver_report.protIdent;
                (*len)++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                /* data code scheme */
                buf[*len] = msg->sms.deliver_report.dataCodeScheme;
                (*len)++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                /* user data len */
                buf[*len] = msg->sms.deliver_report.userDataLen;
                (*len)++;

                /* user data */
                if (msg->sms.deliver_report.userDataLen)
                {
                    memcpy(&buf[*len], msg->sms.deliver_report.userData,
                           msg->sms.deliver_report.userDataLen);
                    *len += msg->sms.deliver_report.userDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_REPORT_TO_MS:
            /* param ind */
            buf[*len] = msg->sms.submit_report.paramInd;
            (*len)++;

            /* sc timestamp */
            memcpy(&buf[*len], &msg->sms.submit_report.scTimestamp,
                   sizeof(GSM_TIME_STAMP));
            *len += sizeof(GSM_TIME_STAMP);

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                /* prot ident */
                buf[*len] = msg->sms.submit_report.protIdent;
                (*len)++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                /* data code scheme */
                buf[*len] = msg->sms.submit_report.dataCodeScheme;
                (*len)++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                /* user data len */
                buf[*len] = msg->sms.submit_report.userDataLen;
                (*len)++;

                /* user data */
                if (msg->sms.submit_report.userDataLen)
                {
                    memcpy(&buf[*len], msg->sms.submit_report.userData,
                           msg->sms.submit_report.userDataLen);
                    *len += msg->sms.submit_report.userDataLen;
                }
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    case GSM_SMRL_RP_ERROR:
        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_REPORT_TO_SC:
            /* fail cause */
            buf[*len] = msg->sms.deliver_report.failCause;
            (*len)++;

            /* param ind */
            buf[*len] = msg->sms.deliver_report.paramInd;
            (*len)++;

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                /* prot ident */
                buf[*len] = msg->sms.deliver_report.protIdent;
                (*len)++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                /* data code scheme */
                buf[*len] = msg->sms.deliver_report.dataCodeScheme;
                (*len)++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                /* user data len */
                buf[*len] = msg->sms.deliver_report.userDataLen;
                (*len)++;

                /* user data */
                if (msg->sms.deliver_report.userDataLen)
                {
                    memcpy(&buf[*len], msg->sms.deliver_report.userData,
                           msg->sms.deliver_report.userDataLen);
                    *len += msg->sms.deliver_report.userDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_REPORT_TO_MS:
            /* fail cause */
            buf[*len] = msg->sms.submit_report.failCause;
            (*len)++;

            /* param ind */
            buf[*len] = msg->sms.submit_report.paramInd;
            (*len)++;

            /* sc timestamp */
            memcpy(&buf[*len], &msg->sms.submit_report.scTimestamp,
                   sizeof(GSM_TIME_STAMP));
            *len += sizeof(GSM_TIME_STAMP);

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                /* prot ident */
                buf[*len] = msg->sms.submit_report.protIdent;
                (*len)++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                /* data code scheme */
                buf[*len] = msg->sms.submit_report.dataCodeScheme;
                (*len)++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                /* user data len */
                buf[*len] = msg->sms.submit_report.userDataLen;
                (*len)++;

                /* user data */
                if (msg->sms.submit_report.userDataLen)
                {
                    memcpy(&buf[*len], msg->sms.submit_report.userData,
                           msg->sms.submit_report.userDataLen);
                    *len += msg->sms.submit_report.userDataLen;
                }
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    default:
        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
}

/*
 * shorthand
 */
#define CHECK_LEN                   \
    do if (len >= ilen)             \
    {                               \
        return (ITS_EOVERFLOW);     \
    }                               \
    while (0)

int
GSM_SMS_DecodeMsg(int rpType, int dir,
                  GSM_SMS_MSG *msg,
                  char *buf, int ilen)
{
    int len = 0;

    CHECK_LEN;
    msg->firstOctet = buf[len];
    len++;

    CHECK_LEN;

    switch (rpType)
    {
    case GSM_SMRL_RP_MO_DATA:
    case GSM_SMRL_RP_MT_DATA:
    case GSM_SMRL_RP_ALERT_SC:
    case GSM_SMRL_RP_SM_MEM_AVAIL:

        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_TO_MS:
            /* orig addr */
            memcpy(&msg->sms.deliver.origAddr, &buf[len],
                   buf[len] + 1);
            len += msg->sms.deliver.origAddr.addr_len + 1;
            CHECK_LEN;

            /* protocol identifier */
            msg->sms.deliver.protIdent = buf[len];
            len++;
            CHECK_LEN;

            /* data code scheme */
            msg->sms.deliver.dataCodeScheme = buf[len];
            len++;
            CHECK_LEN;

            /* sc Timestamp */
            memcpy(&msg->sms.deliver.scTimestamp, &buf[len],
                   sizeof(GSM_TIME_STAMP));
            len += sizeof(GSM_TIME_STAMP);
            CHECK_LEN;

            /* user data len */
            msg->sms.deliver.userDataLen = buf[len];
            len++;

            /* user data */
            if (msg->sms.deliver.userDataLen)
            {
                CHECK_LEN;

                memcpy(msg->sms.deliver.userData, &buf[len],
                       msg->sms.deliver.userDataLen);
                len += msg->sms.deliver.userDataLen;
            }
            break;

        case GSM_SMS_TP_MTI_STATUS_REPORT_TO_MS:
            if (!dir)
            {
                /* msg ref */
                msg->sms.status_report.msgRef = buf[len];
                len++;
                CHECK_LEN;

                /* recip addr */
                memcpy(&msg->sms.status_report.recipAddr, &buf[len],
                       buf[len] + 1);
                len += msg->sms.status_report.recipAddr.addr_len + 1;
                CHECK_LEN;

                /* sc timestamp */
                memcpy(&msg->sms.status_report.scTimestamp, &buf[len],
                       sizeof(GSM_TIME_STAMP));
                len += sizeof(GSM_TIME_STAMP);
                CHECK_LEN;

                /* discharge time */
                memcpy(&msg->sms.status_report.dischargeTime, &buf[len],
                       sizeof(GSM_TIME_STAMP));
                len += sizeof(GSM_TIME_STAMP);
                CHECK_LEN;

                /* status */
                msg->sms.status_report.status = buf[len];
                len++;
                CHECK_LEN;

                /* param ind */
                msg->sms.status_report.paramInd = buf[len];
                len++;

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_PID_BIT)
                {
                    CHECK_LEN;

                    /* prot ident */
                    msg->sms.status_report.protIdent = buf[len];
                    len++;
                }

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_DCS_BIT)
                {
                    CHECK_LEN;

                    /* data code scheme */
                    msg->sms.status_report.dataCodeScheme = buf[len];
                    len++;
                }

                if (msg->sms.status_report.paramInd &
                    GSM_SMS_TP_PI_TP_UDL_BIT)
                {
                    CHECK_LEN;

                    /* user data len */
                    msg->sms.status_report.userDataLen = buf[len];
                    len++;

                    /* user data */
                    if (msg->sms.status_report.userDataLen)
                    {
                        CHECK_LEN;

                        memcpy(msg->sms.status_report.userData, &buf[len],
                               msg->sms.status_report.userDataLen);
                        len += msg->sms.status_report.userDataLen;
                    }
                }
            }
            else
            {
                /* case GSM_SMS_TP_MTI_COMMAND_TO_SC: */
                /* msg ref */
                msg->sms.command.msgRef = buf[len];
                len++;
                CHECK_LEN;

                /* prot ident */
                msg->sms.command.protIdent = buf[len];
                len++;
                CHECK_LEN;

                /* cmd type */
                msg->sms.command.cmdType = buf[len];
                len++;
                CHECK_LEN;

                /* msg number */
                msg->sms.command.msgNumber = buf[len];
                len++;
                CHECK_LEN;

                /* dest addr */
                memcpy(&msg->sms.command.destAddr, &buf[len],
                       buf[len] + 1);
                len += msg->sms.command.destAddr.addr_len + 1;
                CHECK_LEN;

                /* cmd data len */
                msg->sms.command.cmdDataLen = buf[len];
                len++;

                /* user data */
                if (msg->sms.command.cmdDataLen)
                {
                    CHECK_LEN;

                    memcpy(msg->sms.command.cmdData, &buf[len],
                           msg->sms.command.cmdDataLen);
                    len += msg->sms.command.cmdDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_TO_SC:
            /* msg ref */
            msg->sms.submit.msgRef = buf[len];
            len++;
            CHECK_LEN;

            /* dest addr */
            memcpy(&msg->sms.submit.destAddr, &buf[len],
                   buf[len] + 1);
            len += msg->sms.submit.destAddr.addr_len + 1;
            CHECK_LEN;

            /* prot ident */
            msg->sms.submit.protIdent = buf[len];
            len++;
            CHECK_LEN;

            /* data code scheme */
            msg->sms.submit.dataCodeScheme = buf[len];
            len++;

            /* valid period */
            if ((msg->firstOctet & GSM_SMS_TP_VPF_MASK) == GSM_SMS_TP_VPF_NOT_PRESENT)
            {
                /* do nothing */
            }
            else if ((msg->firstOctet & GSM_SMS_TP_VPF_MASK) == GSM_SMS_TP_VPF_RELATIVE)
            {
                CHECK_LEN;

                /* one byte */
                msg->sms.submit.validPeriod.year = buf[len];
                len++;
            }
            else
            {
                CHECK_LEN;

                /* seven bytes */
                memcpy(&msg->sms.submit.validPeriod, &buf[len],
                       sizeof(GSM_TIME_STAMP));
                len += sizeof(GSM_TIME_STAMP);
            }

            CHECK_LEN;

            /* user data len */
            msg->sms.submit.userDataLen = buf[len];
            len++;

            /* user data */
            if (msg->sms.submit.userDataLen)
            {
                CHECK_LEN;

                memcpy(msg->sms.submit.userData, &buf[len],
                       msg->sms.submit.userDataLen);
                len += msg->sms.submit.userDataLen;
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    case GSM_SMRL_RP_ACK:
        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_REPORT_TO_SC:
            /* param ind */
            msg->sms.deliver_report.paramInd = buf[len];
            len++;

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                CHECK_LEN;

                /* prot ident */
                msg->sms.deliver_report.protIdent = buf[len];
                len++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                CHECK_LEN;

                /* data code scheme */
                msg->sms.deliver_report.dataCodeScheme = buf[len];
                len++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                CHECK_LEN;

                /* user data len */
                msg->sms.deliver_report.userDataLen = buf[len];
                len++;

                /* user data */
                if (msg->sms.deliver_report.userDataLen)
                {
                    CHECK_LEN;

                    memcpy(msg->sms.deliver_report.userData, &buf[len],
                           msg->sms.deliver_report.userDataLen);
                    len += msg->sms.deliver_report.userDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_REPORT_TO_MS:
            /* param ind */
            msg->sms.submit_report.paramInd = buf[len];
            len++;
            CHECK_LEN;

            /* sc timestamp */
            memcpy(&msg->sms.submit_report.scTimestamp, &buf[len],
                   sizeof(GSM_TIME_STAMP));
            len += sizeof(GSM_TIME_STAMP);

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                CHECK_LEN;

                /* prot ident */
                msg->sms.submit_report.protIdent = buf[len];
                len++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                CHECK_LEN;

                /* data code scheme */
                msg->sms.submit_report.dataCodeScheme = buf[len];
                len++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                CHECK_LEN;

                /* user data len */
                msg->sms.submit_report.userDataLen = buf[len];
                len++;

                /* user data */
                if (msg->sms.submit_report.userDataLen)
                {
                    CHECK_LEN;

                    memcpy(msg->sms.submit_report.userData, &buf[len],
                           msg->sms.submit_report.userDataLen);
                    len += msg->sms.submit_report.userDataLen;
                }
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    case GSM_SMRL_RP_ERROR:
        switch (msg->firstOctet & GSM_SMS_TP_MTI_MASK)
        {
        case GSM_SMS_TP_MTI_DELIVER_REPORT_TO_SC:
            /* fail cause */
            msg->sms.deliver_report.failCause = buf[len];
            len++;
            CHECK_LEN;

            /* param ind */
            msg->sms.deliver_report.paramInd = buf[len];
            len++;

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                CHECK_LEN;

                /* prot ident */
                msg->sms.deliver_report.protIdent = buf[len];
                len++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                CHECK_LEN;

                /* data code scheme */
                msg->sms.deliver_report.dataCodeScheme = buf[len];
                len++;
            }

            if (msg->sms.deliver_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                CHECK_LEN;

                /* user data len */
                msg->sms.deliver_report.userDataLen = buf[len];
                len++;

                /* user data */
                if (msg->sms.deliver_report.userDataLen)
                {
                    CHECK_LEN;

                    memcpy(msg->sms.deliver_report.userData, &buf[len],
                           msg->sms.deliver_report.userDataLen);
                    len += msg->sms.deliver_report.userDataLen;
                }
            }
            break;

        case GSM_SMS_TP_MTI_SUBMIT_REPORT_TO_MS:
            /* fail cause */
            msg->sms.submit_report.failCause = buf[len];
            len++;
            CHECK_LEN;

            /* param ind */
            msg->sms.submit_report.paramInd = buf[len];
            len++;
            CHECK_LEN;

            /* sc timestamp */
            memcpy(&msg->sms.submit_report.scTimestamp, &buf[len],
                   sizeof(GSM_TIME_STAMP));
            len += sizeof(GSM_TIME_STAMP);

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_PID_BIT)
            {
                CHECK_LEN;

                /* prot ident */
                msg->sms.submit_report.protIdent = buf[len];
                len++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_DCS_BIT)
            {
                CHECK_LEN;

                /* data code scheme */
                msg->sms.submit_report.dataCodeScheme = buf[len];
                len++;
            }

            if (msg->sms.submit_report.paramInd &
                GSM_SMS_TP_PI_TP_UDL_BIT)
            {
                CHECK_LEN;

                /* user data len */
                msg->sms.submit_report.userDataLen = buf[len];
                len++;

                /* user data */
                if (msg->sms.submit_report.userDataLen)
                {
                    CHECK_LEN;

                    memcpy(msg->sms.submit_report.userData, &buf[len],
                           msg->sms.submit_report.userDataLen);
                    len += msg->sms.submit_report.userDataLen;
                }
            }
            break;
        default:
            return (ITS_EPROTERR);
        }
        break;

    default:
        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
}

