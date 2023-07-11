/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: mab_cmn.cpp,v 1.2 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: mab_cmn.cpp,v $
 * LOG: Revision 1.2  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include <iostream>
#include <mab_cmn.h>

extern "C"
{
MULAPP_DLLAPI int
MABCL_Encode(MABCL_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_OCTET data[512];
    /* structure to event */
    ITS_INT index=0;
   
    data[index++] = (ITS_OCTET)(msg->clientID & 0x000000FF);
    data[index++] = (ITS_OCTET)((msg->clientID & 0x0000FF00) >> 8);
    data[index++] = (ITS_OCTET)((msg->clientID & 0x00FF0000) >> 16);
    data[index++] = (ITS_OCTET)((msg->clientID & 0xFF000000) >> 24);

    data[index++] = msg->msg_type;

    switch(msg->msg_type)
    {
        case REGISTER_MSG:
             event->src = MABCL_APP_SRC;
             data[index++] = msg->u.regInfo.routing_criteria;
             data[index++] = msg->u.regInfo.numOfRecords & 0xff;
             /* after the routing criteria we should stuff the fields 
                based on the routing criteria. */
             for (int i = 0; i < msg->u.regInfo.numOfRecords; i++)
             {
                 switch(msg->u.regInfo.routing_criteria)
                 {
                     case MABCL_TCAP_RT_DID_EVEN:
                     case MABCL_TCAP_RT_DID_ODD:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         break;
                     case MABCL_TCAP_RT_TID_RANGE:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         data[index++] =
                            msg->u.regInfo.u.tcap[i].ltid & 0x00FF;
                         data[index++] =
                            (msg->u.regInfo.u.tcap[i].ltid & 0xFF00) >> 8;
                         data[index++] =
                            msg->u.regInfo.u.tcap[i].utid & 0x00FF;
                         data[index++] =
                            (msg->u.regInfo.u.tcap[i].utid & 0xFF00) >> 8;
                         break;
     
                     case MABCL_TCAP_RT_LPC_DPC_LSSN:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.tcap[i].lpc, 
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         memcpy(&data[index],
                                 &msg->u.regInfo.u.tcap[i].dpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);   
                         data[index++] = msg->u.regInfo.u.tcap[i].ssn;
                         break;
 
                     case MABCL_TCAP_RT_LPC_LSSN:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.tcap[i].lpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         data[index++] = msg->u.regInfo.u.tcap[i].ssn;
                         break;
 
                     case MABCL_TCAP_RT_LSSN:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         data[index++] = msg->u.regInfo.u.tcap[i].ssn;
                         break;
 
                     case MABCL_TCAP_RT_LPC:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.tcap[i].lpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;
 
                     case MABCL_TCAP_RT_DPC:
                         data[index++] = msg->u.regInfo.u.tcap[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.tcap[i].dpc,
                                sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;
                      
                     case MABCL_ISUP_RT_LPC_CIC_RANGE:
                         data[index++] = msg->u.regInfo.u.isup[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.isup[i].lpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         data[index++] =
                                msg->u.regInfo.u.isup[i].lcic & 0x00FF;
                         data[index++] =
                               (msg->u.regInfo.u.isup[i].lcic & 0xFF00) >> 8;

                         data[index++] =
                            msg->u.regInfo.u.isup[i].ucic & 0x00FF;
                         data[index++] =
                            (msg->u.regInfo.u.isup[i].ucic & 0xFF00) >> 8;
                         break;
                     case MABCL_ISUP_RT_DPC_CIC_RANGE:
                         data[index++] = msg->u.regInfo.u.isup[i].regType; 

                         memcpy(&data[index], &msg->u.regInfo.u.isup[i].dpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         data[index++] =
                            msg->u.regInfo.u.isup[i].lcic & 0x00FF;
                         data[index++] =
                            (msg->u.regInfo.u.isup[i].lcic & 0xFF00) >> 8;
    
                         data[index++] =
                            msg->u.regInfo.u.isup[i].ucic & 0x00FF;
                         data[index++] =
                            (msg->u.regInfo.u.isup[i].ucic & 0xFF00) >> 8;
                         break;
                     case MABCL_ISUP_RT_LPC:
                         data[index++] = msg->u.regInfo.u.isup[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.isup[i].lpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;
                     case MABCL_ISUP_RT_DPC:
                         data[index++] = msg->u.regInfo.u.isup[i].regType; 
                         memcpy(&data[index], &msg->u.regInfo.u.isup[i].dpc,
                                 sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;
                 }       
             }
             break;
        case DEREGISTER_MSG:
             event->src = MABCL_APP_SRC;
             data[index++] = msg->u.regInfo.routing_criteria;
             break;

        case MANAGEMENT_MSG:
             event->src = MABCL_MGMT_SRC;
             data[index] = msg->u.mgmtInfo.mgmtMsg;

             switch(msg->u.mgmtInfo.mgmtMsg)
             {
                 case MAB_MTP3_MSG_PAUSE:
                 case MAB_MTP3_MSG_RESUME:
                 case MAB_MTP3_MSG_STATUS:
                      memcpy(&data[index], &msg->u.mgmtInfo.MGMT_INFO.pc,
                             sizeof(MTP3_POINT_CODE));
                      index += sizeof(MTP3_POINT_CODE);
                      break;
                 case MAB_SCCP_SCMG_SS_ALLOWED:
                 case MAB_SCCP_SCMG_SS_PROHIBIT:
                 case MAB_SCCP_SCMG_SS_STATUS_TEST:
                      memcpy(&data[index],
                             &msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.pc,
                             sizeof(MTP3_POINT_CODE));
                      index += sizeof(MTP3_POINT_CODE);
                      data[index++] = msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.ssn;
                      break;
              }
              break; 
        case REGISTER_ACK_MSG:
             event->src = MABCL_APP_SRC;
             data[index++] = msg->u.regAck.routing_criteria;
             data[index++] = msg->u.regAck.result;
             data[index++] = msg->u.regAck.errorCode & 0x00FF;
             data[index++] =
                (msg->u.deregAck.errorCode & 0xFF00) >> 8;
             break;
        case DERGISTER_ACK_MSG: 
             event->src = MABCL_APP_SRC;
             data[index++] = msg->u.deregAck.routing_criteria;
             data[index++] = msg->u.deregAck.result;
             data[index++] = msg->u.deregAck.errorCode & 0x00FF;
             data[index++] =
                (msg->u.deregAck.errorCode & 0xFF00) >> 8;
             break;
        case ISUP_MSG:
        {
            event->src = MABCL_ISUP_SRC;
            memcpy(&data[index],
                   msg->u.isupInfo.data,
                   msg->u.isupInfo.len);

            index += msg->u.isupInfo.len;
            break;
        }
        case TCAP_MSG:
        {
            event->src = MABCL_TCAP_SRC;
            memcpy(&data[index],
                   msg->u.tcapInfo.data,
                   msg->u.tcapInfo.len);

            index += msg->u.tcapInfo.len;
            break;
        }
        case MTP3_MSG:
        {
            event->src = MABCL_MTP3_SRC;
            memcpy(&data[index],
                   msg->u.mtp3Info.data,
                   msg->u.mtp3Info.len);

            index += msg->u.mtp3Info.len;
            break;
        }
        case ISUP_RSV_CIC_MSG:
        {
            memcpy(&data[index],
                   &msg->u.rsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            data[index++] =
                msg->u.rsvInfo.cic & 0x00FF;
            data[index++] =
                (msg->u.rsvInfo.cic & 0xFF00) >> 8;
            break;
        }
        case ISUP_RSV_CIC_ACK_MSG:
        {
            event->src = MABCL_ISUP_SRC;
            memcpy(&data[index],
                   &msg->u.rsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            data[index++] =
                msg->u.rsvInfo.cic & 0x00FF;
            data[index++] =
                (msg->u.rsvInfo.cic & 0xFF00) >> 8;

            data[index++] = msg->u.rsvInfo.cic_state;

            data[index++] =
                msg->u.rsvInfo.vcic & 0x00FF;
            data[index++] =
                (msg->u.rsvInfo.vcic & 0xFF00) >> 8;

            data[index++] =
                msg->u.rsvInfo.ret & 0x000000FF;
            data[index++] =
                (msg->u.rsvInfo.ret & 0x0000FF00) >> 8;
            data[index++] =
                (msg->u.rsvInfo.ret & 0x00FF0000) >> 16;
            data[index++] =
                (msg->u.rsvInfo.ret & 0xFF000000) >> 24;

            break;
        }
        case ISUP_URSV_CIC_MSG:
        {
            event->src = MABCL_ISUP_SRC;
            memcpy(&data[index],
                   &msg->u.unrsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            data[index++] =
               msg->u.unrsvInfo.cic & 0x00FF;
            data[index++] =
               (msg->u.unrsvInfo.cic & 0xFF00) >> 8;
 
            break;
        }
        case ISUP_URSV_CIC_ACK_MSG:
        {
            event->src = MABCL_ISUP_SRC;
            memcpy(&data[index],
                   &msg->u.unrsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            data[index++] =
               msg->u.unrsvInfo.cic & 0x00FF;
            data[index++] =
               (msg->u.unrsvInfo.cic & 0xFF00) >> 8;

            data[index++] =
                msg->u.unrsvInfo.ret & 0x000000FF;
            data[index++] =
                (msg->u.unrsvInfo.ret & 0x0000FF00) >> 8;
            data[index++] =
                (msg->u.unrsvInfo.ret & 0x00FF0000) >> 16;
            data[index++] =
                (msg->u.unrsvInfo.ret & 0xFF000000) >> 24;
            break;
        }
    }/* switch end */

    event->len = index;
    event->data = (ITS_OCTET*)malloc(index);

    memcpy(event->data, data, index);
    return ITS_SUCCESS; 
}

MULAPP_DLLAPI int
MABCL_Decode(MABCL_MESSAGE *msg, ITS_EVENT *event)
{
    /* event to structure */

    ITS_INT index = 0;

    msg->clientID = 0;
    msg->clientID |= event->data[index++];
    msg->clientID |= event->data[index++] << 8;
    msg->clientID |= event->data[index++] << 16;
    msg->clientID |= event->data[index++] << 24;

    msg->msg_type = (MESSAGE_TYPE)event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_MSG:

             msg->u.regInfo.routing_criteria = (ROUTING_CRITERIA)event->data[index++];
             msg->u.regInfo.numOfRecords = event->data[index++];
             for (int i = 0; i < msg->u.regInfo.numOfRecords; i++)
             {
                 switch(msg->u.regInfo.routing_criteria)
                 {
                     case MABCL_TCAP_RT_DID_EVEN:
                     case MABCL_TCAP_RT_DID_ODD:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         break;
                     case MABCL_TCAP_RT_TID_RANGE:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         msg->u.regInfo.u.tcap[i].ltid=0;
                         msg->u.regInfo.u.tcap[i].ltid |= event->data[index++];
                         msg->u.regInfo.u.tcap[i].ltid |= event->data[index++] << 8;

                         msg->u.regInfo.u.tcap[i].utid=0;
                         msg->u.regInfo.u.tcap[i].utid |= event->data[index++];
                         msg->u.regInfo.u.tcap[i].utid |= event->data[index++] << 8;
                         break;

                     case MABCL_TCAP_RT_LPC_DPC_LSSN:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.tcap[i].lpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);

                         memcpy(&msg->u.regInfo.u.tcap[i].dpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         msg->u.regInfo.u.tcap[i].ssn = event->data[index++];
                         break;

                     case MABCL_TCAP_RT_LPC_LSSN:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.tcap[i].lpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         msg->u.regInfo.u.tcap[i].ssn = event->data[index++];
                         break;

                     case MABCL_TCAP_RT_LSSN:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         msg->u.regInfo.u.tcap[i].ssn = event->data[index++];
                         break;

                     case MABCL_TCAP_RT_LPC:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.tcap[i].lpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;

                     case MABCL_TCAP_RT_DPC:
                         msg->u.regInfo.u.tcap[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.tcap[i].dpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;

                     case MABCL_ISUP_RT_LPC_CIC_RANGE:
                         msg->u.regInfo.u.isup[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.isup[i].lpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);

                         msg->u.regInfo.u.isup[i].lcic =0;
                         msg->u.regInfo.u.isup[i].lcic |= event->data[index++];
                         msg->u.regInfo.u.isup[i].lcic |= event->data[index++] << 8;

                         msg->u.regInfo.u.isup[i].ucic =0;
                         msg->u.regInfo.u.isup[i].ucic |= event->data[index++];
                         msg->u.regInfo.u.isup[i].ucic |= event->data[index++] << 8;
printf("Register for lcic : %d ucic : %d\n",msg->u.regInfo.u.isup[i].lcic,
msg->u.regInfo.u.isup[i].ucic);
                         break;

                     case MABCL_ISUP_RT_DPC_CIC_RANGE:
                         msg->u.regInfo.u.isup[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.isup[i].dpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);

                         msg->u.regInfo.u.isup[i].lcic =0;
                         msg->u.regInfo.u.isup[i].lcic |= event->data[index++];
                         msg->u.regInfo.u.isup[i].lcic |= event->data[index++] << 8;

                         msg->u.regInfo.u.isup[i].ucic =0;
                         msg->u.regInfo.u.isup[i].ucic |= event->data[index++];
                         msg->u.regInfo.u.isup[i].ucic |= event->data[index++] << 8;
                         break;

                     case MABCL_ISUP_RT_LPC:
                         msg->u.regInfo.u.isup[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.isup[i].lpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;

                     case MABCL_ISUP_RT_DPC:
                         msg->u.regInfo.u.isup[i].regType = event->data[index++];
                         memcpy(&msg->u.regInfo.u.isup[i].dpc, 
                                &event->data[index], sizeof(MTP3_POINT_CODE));
                         index += sizeof(MTP3_POINT_CODE);
                         break;
                 }
             }
             break;

        case DEREGISTER_MSG:
             msg->u.regInfo.routing_criteria = (ROUTING_CRITERIA)event->data[index++];
             break;

        case MANAGEMENT_MSG:
             msg->u.mgmtInfo.mgmtMsg = (MGMT_MESSAGE)event->data[index++];
             switch(msg->u.mgmtInfo.mgmtMsg)
             {
                 case MAB_MTP3_MSG_PAUSE:
                 case MAB_MTP3_MSG_RESUME:
                 case MAB_MTP3_MSG_STATUS:
                      memcpy(&msg->u.mgmtInfo.MGMT_INFO.pc, &event->data[index],sizeof(MTP3_POINT_CODE));                                         index += sizeof(MTP3_POINT_CODE);
                      break;
                 case MAB_SCCP_SCMG_SS_ALLOWED:
                 case MAB_SCCP_SCMG_SS_PROHIBIT:
                 case MAB_SCCP_SCMG_SS_STATUS_TEST:
                      memcpy(&msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.pc,&event->data[index],
                             sizeof(MTP3_POINT_CODE));
                      index += sizeof(MTP3_POINT_CODE);
                      msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.ssn = event->data[index++];
                      break;
              }
              break;
        case REGISTER_ACK_MSG:
            msg->u.regAck.routing_criteria = (ROUTING_CRITERIA)event->data[index++];
            msg->u.regAck.result = event->data[index++];
            msg->u.regAck.errorCode =0;
            msg->u.regAck.errorCode |= event->data[index++];
            msg->u.regAck.errorCode |= event->data[index++] << 8;
            break;

        case DERGISTER_ACK_MSG:
            msg->u.deregAck.routing_criteria = (ROUTING_CRITERIA)event->data[index++];
            msg->u.deregAck.result = event->data[index++];
            msg->u.deregAck.errorCode =0;
            msg->u.deregAck.errorCode |= event->data[index++];
            msg->u.deregAck.errorCode |= event->data[index++] << 8;
            break;

        case ISUP_MSG:
            /* extract the length info two bytes */
            msg->u.isupInfo.len = event->len - index;
            
            msg->u.isupInfo.data = (ITS_OCTET*)malloc(msg->u.isupInfo.len);
            /* extract the isup data */
            memcpy(msg->u.isupInfo.data,&event->data[index],
                    msg->u.isupInfo.len);
            index += msg->u.isupInfo.len;
            break;
              
        case TCAP_MSG:
        {
            /* extract the length info two bytes */
            msg->u.tcapInfo.len = (event->len - index);

            /* extract the tcap data */
            msg->u.tcapInfo.data =
               (ITS_OCTET *)malloc(msg->u.tcapInfo.len);

            memcpy(msg->u.tcapInfo.data,
                   &event->data[index],
                   msg->u.tcapInfo.len);

            index += msg->u.tcapInfo.len;
            break;
        }
        case MTP3_MSG:
        {
            /* extract the length info two bytes */
            msg->u.mtp3Info.len = (event->len - index);

            /* extract the tcap data */
            msg->u.mtp3Info.data =
               (ITS_OCTET *)malloc(msg->u.mtp3Info.len);

            memcpy(msg->u.mtp3Info.data,
                   &event->data[index],
                   msg->u.mtp3Info.len);

            index += msg->u.mtp3Info.len;
            break;
        }
        case ISUP_RSV_CIC_MSG:
        {
            memcpy(&msg->u.rsvInfo.mtp3,
                 &event->data[index],
                 sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);

            msg->u.rsvInfo.cic =0 ;
            msg->u.rsvInfo.cic = event->data[index++];
            msg->u.rsvInfo.cic |= event->data[index++] << 8;

            break;
        }
        case ISUP_RSV_CIC_ACK_MSG:
        {
            memcpy(&msg->u.rsvInfo.mtp3,
                 &event->data[index],
                 sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);

            msg->u.rsvInfo.cic =0 ;
            msg->u.rsvInfo.cic = event->data[index++];
            msg->u.rsvInfo.cic |= event->data[index++] << 8;

            msg->u.rsvInfo.cic_state = event->data[index++];

            msg->u.rsvInfo.vcic =0 ;
            msg->u.rsvInfo.vcic = event->data[index++];
            msg->u.rsvInfo.vcic |= event->data[index++] << 8;
 
            msg->u.rsvInfo.ret = 0;
            msg->u.rsvInfo.ret = event->data[index++];
            msg->u.rsvInfo.ret |= event->data[index++] << 8;
            msg->u.rsvInfo.ret |= event->data[index++] << 16;
            msg->u.rsvInfo.ret |= event->data[index++] << 24;

            break;
        }
        case ISUP_URSV_CIC_MSG:
        {
            memcpy(&msg->u.unrsvInfo.mtp3,
                   &event->data[index],
                   sizeof(MTP3_HEADER));
            index += sizeof(MTP3_HEADER);

            msg->u.unrsvInfo.cic = event->data[index++];
            msg->u.unrsvInfo.cic |= event->data[index++] << 8;
            break;
        }
        case ISUP_URSV_CIC_ACK_MSG:
        {
            memcpy(&msg->u.unrsvInfo.mtp3,
                   &event->data[index],
                   sizeof(MTP3_HEADER));
            index += sizeof(MTP3_HEADER);

            msg->u.unrsvInfo.cic = event->data[index++];
            msg->u.unrsvInfo.cic |= event->data[index++] << 8;

            msg->u.unrsvInfo.ret = event->data[index++];
            msg->u.unrsvInfo.ret |= event->data[index++] << 8;
            msg->u.unrsvInfo.ret |= event->data[index++] << 16;
            msg->u.unrsvInfo.ret |= event->data[index++] << 24;
            break;
        }
    }
    return ITS_SUCCESS;

} 
}

