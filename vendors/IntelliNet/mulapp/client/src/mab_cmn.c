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
 * ID: $Id: mab_cmn.c,v 1.2 2005/07/05 11:36:02 mmanikandan Exp $
 *
 * LOG: $Log: mab_cmn.c,v $
 * LOG: Revision 1.2  2005/07/05 11:36:02  mmanikandan
 * LOG: changes for isup distributed.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#include <mab_cmn.h>

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method encodes the structure in to the event.
 *
 *  Input Parameters:
 *
 *      msg MABCL_MESSAGE structure to be processed.
 *      event - event to be populated.
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_Encode(MABCL_MESSAGE *msg, ITS_EVENT *event)
{
    /* structure to event */
    ITS_INT index=0, i;
    ITS_CTXT tid = 0;

    if(event->data == NULL)
    {
        printf("Event pointer is null . Allocate memory\n");
        return !ITS_SUCCESS;
    }
   
    event->data[index++] = msg->clientID & 0x000000FF;
    event->data[index++] = (msg->clientID & 0x0000FF00) >> 8;
    event->data[index++] = (msg->clientID & 0x00FF0000) >> 16;
    event->data[index++] = (msg->clientID & 0xFF000000) >> 24;

    event->data[index++] = msg->msg_type;
    switch(msg->msg_type)
    {
        case REGISTER_MSG:
        {
            event->src = MABCL_APP_SRC;

            event->data[index++] = msg->u.regInfo.routing_criteria;
            event->data[index++] = 1;

            /* after the routing criteria we should stuff the fields 
               based on the routing criteria. */
            switch(msg->u.regInfo.routing_criteria)
            {
                case MABCL_TCAP_RT_DID_EVEN:
                case MABCL_TCAP_RT_DID_ODD:
                {
                    event->data[index++] = 1;
                    break;
                }
                case MABCL_TCAP_RT_TID_RANGE:
                {
                    event->data[index++] = 1;
                    tid = msg->u.regInfo.u.tcap.ltid;
                    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
                    {
                        event->data[index++] = (tid & 0xFF);
                        tid = tid >> 8;
                    }

                    tid = msg->u.regInfo.u.tcap.utid;
                    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
                    {
                        event->data[index++] = (tid & 0xFF);
                        tid = tid >> 8;
                    }
 
                    break;
                }
                case MABCL_TCAP_RT_LPC_DPC_LSSN:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                           &msg->u.regInfo.u.tcap.lpc, 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    memcpy(&event->data[index],
                           &msg->u.regInfo.u.tcap.dpc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);   

                    event->data[index++] = 
                        msg->u.regInfo.u.tcap.ssn;
                    break;
                }
                case MABCL_TCAP_RT_LPC_LSSN:
                { 
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                            &msg->u.regInfo.u.tcap.lpc,
                            sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    event->data[index++] = 
                       msg->u.regInfo.u.tcap.ssn;
                    break;
                }
                case MABCL_TCAP_RT_LSSN:
                {
                    event->data[index++] = 1;
                     event->data[index++] = 
                        msg->u.regInfo.u.tcap.ssn;
                     break;
                } 
                case MABCL_TCAP_RT_LPC:
                { 
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                           &msg->u.regInfo.u.tcap.lpc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                } 
                case MABCL_TCAP_RT_DPC:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                            &msg->u.regInfo.u.tcap.dpc,
                            sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    break; 
                } 
                case MABCL_ISUP_RT_LPC_CIC_RANGE:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                           &msg->u.regInfo.u.isup.lpc,
                           sizeof(MTP3_POINT_CODE));
          
                    index += sizeof(MTP3_POINT_CODE);

                    event->data[index++] = 
                    msg->u.regInfo.u.isup.lcic & 0x00FF;
                    event->data[index++] = 
                      (msg->u.regInfo.u.isup.lcic & 0xFF00) >> 8;

                    event->data[index++] = 
                      msg->u.regInfo.u.isup.ucic & 0x00FF;
                    event->data[index++] = 
                      (msg->u.regInfo.u.isup.ucic & 0xFF00) >> 8;
                    break;
                } 
                case MABCL_ISUP_RT_DPC_CIC_RANGE:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                          &msg->u.regInfo.u.isup.dpc,
                          sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    event->data[index++] = 
                       msg->u.regInfo.u.isup.lcic & 0x00FF;
                    event->data[index++] = 
                       (msg->u.regInfo.u.isup.lcic & 0xFF00) >> 8;

                    event->data[index++] = 
                        msg->u.regInfo.u.isup.ucic & 0x00FF;
                    event->data[index++] = 
                        (msg->u.regInfo.u.isup.ucic & 0xFF00) >> 8;
                    break;
                }
                case MABCL_ISUP_RT_LPC:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                           &msg->u.regInfo.u.isup.lpc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    break;
                }
                case MABCL_ISUP_RT_DPC:
                {
                    event->data[index++] = 1;
                    memcpy(&event->data[index], 
                           &msg->u.regInfo.u.isup.dpc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    break;
                }
            }       
            break;
        } 
        case DEREGISTER_MSG:
        {
            event->src = MABCL_APP_SRC;
            event->data[index++] = 
                    msg->u.regInfo.routing_criteria;
            break;
        }
        case MANAGEMENT_MSG:
        {
            event->src = MABCL_MGMT_SRC;
            event->data[index++] = msg->u.mgmtInfo.mgmtMsg; 
            switch(msg->u.mgmtInfo.mgmtMsg)
            {
                case MAB_MTP3_MSG_PAUSE:
                case MAB_MTP3_MSG_RESUME:
                case MAB_MTP3_MSG_STATUS:
                { 
                    memcpy(&event->data[index], 
                           &msg->u.mgmtInfo.MGMT_INFO.pc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                }
                case MAB_SCCP_SCMG_SS_ALLOWED:
                case MAB_SCCP_SCMG_SS_PROHIBIT:
                case MAB_SCCP_SCMG_SS_STATUS_TEST:
                {
                    memcpy(&event->data[index],
                           &msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.pc,
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    event->data[index++] = 
                       msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.ssn;
                    break;
                }
            }
            break; 
        }
        case REGISTER_ACK_MSG:
        {
            event->data[index++] = msg->u.regAck.routing_criteria;
            event->data[index++] = msg->u.regAck.result;
            event->data[index++] = msg->u.regAck.errorCode & 0x00FF;
            event->data[index++] = 
                (msg->u.regAck.errorCode & 0xFF00) >> 8;
            break;
        }
        case DERGISTER_ACK_MSG: 
        {
            event->data[index++] = msg->u.deregAck.routing_criteria;
            event->data[index++] = msg->u.deregAck.result;
            event->data[index++] = msg->u.deregAck.errorCode & 0x00FF;
            event->data[index++] = 
                (msg->u.deregAck.errorCode & 0xFF00) >> 8;
            break;
        }
        case ISUP_MSG:
        {
            memcpy(&event->data[index],
                   msg->u.isupInfo.data,
                   msg->u.isupInfo.len);

            index += msg->u.isupInfo.len;
            break;
        }
        case TCAP_MSG:
        {
            memcpy(&event->data[index],
                   msg->u.tcapInfo.data,
                   msg->u.tcapInfo.len);

            index += msg->u.tcapInfo.len;
            break;
        }
        case ISUP_RSV_CIC_MSG:
        {
            memcpy(&event->data[index],
                   &msg->u.rsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            event->data[index++] =
                msg->u.rsvInfo.cic & 0x00FF;
            event->data[index++] =
                (msg->u.rsvInfo.cic & 0xFF00) >> 8;
           break;
        }
        case ISUP_RSV_CIC_ACK_MSG:
        { 
            memcpy(&event->data[index],
                   &msg->u.rsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            event->data[index++] = 
                msg->u.rsvInfo.cic & 0x00FF;
            event->data[index++] = 
                (msg->u.rsvInfo.cic & 0xFF00) >> 8;

            event->data[index++] = msg->u.rsvInfo.cic_state;

            event->data[index++] = 
                msg->u.rsvInfo.vcic & 0x00FF;
            event->data[index++] = 
                (msg->u.rsvInfo.vcic & 0xFF00) >> 8;

            event->data[index++] = 
                msg->u.rsvInfo.ret & 0x000000FF;
            event->data[index++] = 
                (msg->u.rsvInfo.ret & 0x0000FF00) >> 8;
            event->data[index++] = 
                (msg->u.rsvInfo.ret & 0x00FF0000) >> 16;
            event->data[index++] = 
                (msg->u.rsvInfo.ret & 0xFF000000) >> 24;

            break;
        }
        case ISUP_URSV_CIC_MSG:
        {
            memcpy(&event->data[index],
                   &msg->u.unrsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            event->data[index++] =
               msg->u.unrsvInfo.cic & 0x00FF;
            event->data[index++] =
               (msg->u.unrsvInfo.cic & 0xFF00) >> 8;
            break;
        }
        case ISUP_URSV_CIC_ACK_MSG:
        { 
            memcpy(&event->data[index],
                   &msg->u.unrsvInfo.mtp3,
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);
            event->data[index++] = 
               msg->u.unrsvInfo.cic & 0x00FF;
            event->data[index++] = 
               (msg->u.unrsvInfo.cic & 0xFF00) >> 8;
              
            event->data[index++] = 
                msg->u.unrsvInfo.ret & 0x000000FF;
            event->data[index++] = 
                (msg->u.unrsvInfo.ret & 0x0000FF00) >> 8;
            event->data[index++] = 
                (msg->u.unrsvInfo.ret & 0x00FF0000) >> 16;
            event->data[index++] = 
                (msg->u.unrsvInfo.ret & 0xFF000000) >> 24;
            break; 
        }
            
    }/* switch end */
    
    event->len = index;
    return ITS_SUCCESS; 
}

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Decodes the event in to message structure.
 *
 *  Input Parameters:
 *      msg MABCL_MESSAGE structure.
 *      event  event to be processed.
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
MABCL_Decode(MABCL_MESSAGE *msg, ITS_EVENT *event)
{
    /* event to structure */

    ITS_INT index = 0, i = 0;

    msg->clientID = 0;
    msg->clientID |= event->data[index++];
    msg->clientID |= event->data[index++] << 8;
    msg->clientID |= event->data[index++] << 16;
    msg->clientID |= event->data[index++] << 24;

    msg->msg_type = event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_MSG:
        {
            msg->u.regInfo.routing_criteria = event->data[index++];
            switch(msg->u.regInfo.routing_criteria)
            {
                case MABCL_TCAP_RT_DID_EVEN:
                case MABCL_TCAP_RT_DID_ODD:
                { 
                    index++;
                    break;
                }
                case MABCL_TCAP_RT_TID_RANGE:
                {
                    index++;
                    msg->u.regInfo.u.tcap.ltid = 0;
                    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
                    {

                        msg->u.regInfo.u.tcap.ltid |=
                                  event->data[index++] << (8 * i);
                    }
                    
                    msg->u.regInfo.u.tcap.utid = 0;
                    for(i = 0 ;i <sizeof(ITS_CTXT);++i)
                    {

                        msg->u.regInfo.u.tcap.utid |=
                                  event->data[index++] << (8 * i);
                    }

                    break;
                } 
                case MABCL_TCAP_RT_LPC_DPC_LSSN:
                {
                    index++;
                    memcpy(&msg->u.regInfo.u.tcap.lpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    memcpy(&msg->u.regInfo.u.tcap.dpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    msg->u.regInfo.u.tcap.ssn = 
                      event->data[index++];

                    break;
                }
                case MABCL_TCAP_RT_LPC_LSSN:
                {
                    index++;
                    memcpy(&msg->u.regInfo.u.tcap.lpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);

                    msg->u.regInfo.u.tcap.ssn = 
                       event->data[index++];
                    break;
                }
                case MABCL_TCAP_RT_LSSN:
                {
                    index++;
                    msg->u.regInfo.u.tcap.ssn = 
                      event->data[index++];
                    break;
                }
                case MABCL_TCAP_RT_LPC:
                { 
                    index++;
                     memcpy(&msg->u.regInfo.u.tcap.lpc, 
                            &event->data[index], 
                            sizeof(MTP3_POINT_CODE));
                     index += sizeof(MTP3_POINT_CODE);
                     break;
                } 
                case MABCL_TCAP_RT_DPC:
                {
                    index++;
                    memcpy(&msg->u.regInfo.u.tcap.dpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));
                    index += sizeof(MTP3_POINT_CODE);
                    break;
                }
                case MABCL_ISUP_RT_LPC_CIC_RANGE:
                { 
                    index++;
                    memcpy(&msg->u.regInfo.u.isup.lpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));
                    index += sizeof(MTP3_POINT_CODE);

                    msg->u.regInfo.u.isup.lcic = 0;
                    msg->u.regInfo.u.isup.lcic |= 
                        event->data[index++];
                    msg->u.regInfo.u.isup.lcic |= 
                        event->data[index++] << 8;

                    msg->u.regInfo.u.isup.ucic = 0;
                    msg->u.regInfo.u.isup.ucic |= 
                        event->data[index++];
                    msg->u.regInfo.u.isup.ucic |= 
                        event->data[index++] << 8;
                    break;
                } 
                case MABCL_ISUP_RT_DPC_CIC_RANGE:
                {
                    index++;
                    memcpy(&msg->u.regInfo.u.isup.dpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));
                    index += sizeof(MTP3_POINT_CODE);

                    msg->u.regInfo.u.isup.lcic = 0;
                    msg->u.regInfo.u.isup.lcic |= 
                       event->data[index++];
                    msg->u.regInfo.u.isup.lcic |= 
                       event->data[index++] << 8;


                    msg->u.regInfo.u.isup.ucic =0;
                    msg->u.regInfo.u.isup.ucic |= 
                       event->data[index++];
                    msg->u.regInfo.u.isup.ucic |= 
                       event->data[index++] << 8;
                    break;
                }
                case MABCL_ISUP_RT_LPC:
                { 
                    index++;
                    memcpy(&msg->u.regInfo.u.isup.lpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                }
                case MABCL_ISUP_RT_DPC:
                {
                    index++;
                    memcpy(&msg->u.regInfo.u.isup.dpc, 
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));
                    index += sizeof(MTP3_POINT_CODE);
                    break;
                }
            }
            break;
        }
        case DEREGISTER_MSG:
        {
            msg->u.regInfo.routing_criteria = 
               event->data[index++];
            break;
        }
        case MANAGEMENT_MSG:
        {
            msg->u.mgmtInfo.mgmtMsg = event->data[index++];
            switch(msg->u.mgmtInfo.mgmtMsg)
            {
                case MAB_MTP3_MSG_PAUSE:
                case MAB_MTP3_MSG_RESUME:
                case MAB_MTP3_MSG_STATUS:
                {
                    memcpy(&msg->u.mgmtInfo.MGMT_INFO.pc, 
                           &event->data[index],
                           sizeof(MTP3_POINT_CODE)); 

                    index += sizeof(MTP3_POINT_CODE);
                    break;
                } 
                case MAB_SCCP_SCMG_SS_ALLOWED:
                case MAB_SCCP_SCMG_SS_PROHIBIT:
                case MAB_SCCP_SCMG_SS_STATUS_TEST:
                {
                    memcpy(&msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.pc,
                           &event->data[index], 
                           sizeof(MTP3_POINT_CODE));

                    index += sizeof(MTP3_POINT_CODE);
                    msg->u.mgmtInfo.MGMT_INFO.TCAP_INFO.ssn = 
                       event->data[index++];
                    break;
                }
            }
            break;
        }
        case REGISTER_ACK_MSG:
        {
            msg->u.regAck.routing_criteria = 
               event->data[index++];
            msg->u.regAck.result = event->data[index++];
            msg->u.regAck.errorCode =0;
            msg->u.regAck.errorCode |= event->data[index++];
            msg->u.regAck.errorCode |= event->data[index++] << 8;
            break;
        }
        case DERGISTER_ACK_MSG:
        {
            msg->u.deregAck.routing_criteria = event->data[index++];
            msg->u.deregAck.result = event->data[index++];
            msg->u.deregAck.errorCode =0;
            msg->u.deregAck.errorCode |= event->data[index++];
            msg->u.deregAck.errorCode |= event->data[index++] << 8;
            break;
        }
        case ISUP_MSG:
        {
            /* extract the isup data */
            msg->u.isupInfo.len = (event->len - index); 
            msg->u.isupInfo.data = 
              (ITS_OCTET *)malloc(sizeof(ITS_ISUP_MAX_SIZE));

            memcpy(msg->u.isupInfo.data, 
                   &event->data[index],
                   (event->len - index));

            index += msg->u.isupInfo.len;
            break;
        }
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
        case ISUP_RSV_CIC_ACK_MSG:
        { 
            memcpy(&msg->u.rsvInfo.mtp3, 
                   &event->data[index],
                   sizeof(MTP3_HEADER));

            index += sizeof(MTP3_HEADER);

            msg->u.rsvInfo.cic =0 ;
            msg->u.rsvInfo.cic |= event->data[index++];
            msg->u.rsvInfo.cic |= event->data[index++] << 8;
               
            msg->u.rsvInfo.cic_state = event->data[index++];

            msg->u.rsvInfo.vcic =0 ;
            msg->u.rsvInfo.vcic |= event->data[index++];
            msg->u.rsvInfo.vcic |= event->data[index++] << 8;
               
            msg->u.rsvInfo.ret = 0;
            msg->u.rsvInfo.ret |= event->data[index++];
            msg->u.rsvInfo.ret |= event->data[index++] << 8;
            msg->u.rsvInfo.ret |= event->data[index++] << 16;
            msg->u.rsvInfo.ret |= event->data[index++] << 24;
               
            break;                             
        }
        case ISUP_URSV_CIC_ACK_MSG:
        {
            memcpy(&msg->u.unrsvInfo.mtp3, 
                   &event->data[index],
                   sizeof(MTP3_HEADER));
            index += sizeof(MTP3_HEADER); 
     
            msg->u.unrsvInfo.cic =0 ;
            msg->u.unrsvInfo.cic |= event->data[index++];
            msg->u.unrsvInfo.cic |= event->data[index++] << 8;
        
            msg->u.unrsvInfo.ret = 0;
            msg->u.unrsvInfo.ret |= event->data[index++];
            msg->u.unrsvInfo.ret |= event->data[index++] << 8;
            msg->u.unrsvInfo.ret |= event->data[index++] << 16;
            msg->u.unrsvInfo.ret |= event->data[index++] << 24;
            break;
        }
    }
    return ITS_SUCCESS;
} 
