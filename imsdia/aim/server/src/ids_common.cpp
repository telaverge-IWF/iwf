/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 * LOG: $Log: ids_common.cpp,v $
 * LOG: Revision 3.5.6.4.6.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.5.6.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.5.30.2  2012/11/20 10:16:59  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.5  2010/09/22 05:27:27  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.4  2009/03/19 12:45:22  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.3  2009/03/03 11:10:47  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.2  2008/10/31 05:35:24  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: 1. Introducing additional TQs and Threads for better
 * LOG:                 Performance on PP50 and initial stack tunning
 * LOG:              2. Unwanted code cleanup
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:04  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.10  2008/03/27 11:21:05  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.2.1  2007/04/04 05:59:56  nvijikumar
 * LOG: Decode AppIdType from IDC register event.
 * LOG:
 * LOG: Revision 2.8  2007/02/26 09:38:11  nvijikumar
 * LOG: Control HexDump Print from XML.
 * LOG:
 * LOG: Revision 2.7  2007/02/19 04:51:46  kamakshilk
 * LOG: Hex dump Print format enhanced
 * LOG:
 * LOG: Revision 2.6  2006/11/17 06:01:30  kamakshilk
 * LOG: DccaEnable byte added in RegAck msg
 * LOG:
 * LOG: Revision 2.5  2006/11/14 07:15:26  kamakshilk
 * LOG: Encoding Notifications
 * LOG:
 * LOG: Revision 2.4  2006/11/08 06:12:40  kamakshilk
 * LOG: Changes for 64-bit support. ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.3  2006/10/31 10:05:32  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:17:44  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.5  2006/09/06 11:22:00  kamakshilk
 * LOG: Fix for bug Id 3615,4287. Added the IntToData and DataToInt APIs for encode and decode
 * LOG:
 * LOG: Revision 1.4  2006/05/19 12:17:57  adutta
 * LOG: Fixed issue#3799
 * LOG:
 * LOG: Revision 1.3  2006/04/07 06:39:37  adutta
 * LOG: Error value check in Reg-encode
 * LOG:
 * LOG: Revision 1.2  2006/04/06 07:45:10  adutta
 * LOG: Modified the Reg/De-reg encoding
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:47:51  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/

#include <its++.h>
#include <engine++.h>
                                                       
#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_trace.h>
#include <ids_common.h>
#include <dia_defines.h>
#include <its_dia_config.h>

extern "C"
{

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    06-09-06   Bug Id 3615,4287    Added IntToData() for encoding
 *   Kamakshi    14-11-06   Enhancement         Encode Notification message. 
 *
 ****************************************************************************/
IDSAPP_DLLAPI ITS_INT
IDSCL_Encode(IDS_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_OCTET* data = NULL;
    ITS_INT index = 0;
    ITS_INT len = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT allocLen = 0;

    DIA_TRACE_DEBUG(("IDSCL_Encode"));
   
    event->src = ITS_APP_SRC;
    if (msg->msg_type == DIAMETER_MSG) 
    {
        allocLen = 2*sizeof(ITS_UINT)+1+msg->u.diaInfo.len+IDS_DIA_MSG_POS;
        data = (ITS_OCTET*)calloc(1, allocLen);
    }
    else if (msg->msg_type == DIASERVER_NOTIFY_MSG)
    {
        allocLen = 2*sizeof(ITS_UINT) + 1 + msg->u.notifyInfo.length;
        data = (ITS_OCTET*)calloc(1, allocLen);
    }
    else
    {
        allocLen = sizeof(IDS_MESSAGE);
        data = (ITS_OCTET*)calloc(1, allocLen);
    }

    if (data == NULL)
    {
        //alloc failed throw exception();
        throw "Error: memory allocation failed";
    }

    IDSCL_IntToData((data+index),msg->clientID);
    index += sizeof(ITS_UINT);

    data[index++] = msg->msg_type;

    switch(msg->msg_type)
    {
        case DIAMETER_MSG:
            /* Diameter data length*/
            IDSCL_IntToData((data+index),msg->u.diaInfo.len + IDS_DIA_MSG_POS);
            index += sizeof(ITS_UINT);

            /* Copy MsgType */
            data[index] = msg->u.diaInfo.msgType;
            index += sizeof(ITS_OCTET);

            IDSCL_IntToData((data+index),msg->u.diaInfo.sessIdx);
            index += sizeof(ITS_UINT);

            /* Copy Application Id */
            IDSCL_IntToData((data+index),msg->u.diaInfo.appId);
            index += sizeof(ITS_UINT);

            /* Diameter data */ 
            memcpy(&data[index], msg->u.diaInfo.data, msg->u.diaInfo.len);
            index = index + msg->u.diaInfo.len;
        break;
        case REGISTER_ACK_MSG:

            /* Route criteria */
            data[index++] = msg->u.regAck.routing_criteria;

            /* Registration result */
            data[index++] = msg->u.regAck.result;

            data[index++] = (msg->u.regAck.errorCode);

            data[index++] = (msg->u.regAck.isDccaEnbl);

            /* Server type */
            data[index++] = msg->u.regAck.conType;

            /* Server port */
            IDSCL_IntToData((data+index),msg->u.regAck.port);
            index += sizeof(ITS_UINT);

            /* Server address */
            len = strlen(msg->u.regAck.ipAddr);
            memcpy(&data[index], msg->u.regAck.ipAddr, len);
            index = index + len; 
        break;
        case DERGISTER_ACK_MSG:

            data[index++] = msg->u.deregAck.routing_criteria;
            data[index++] = msg->u.deregAck.result;
            data[index++] = msg->u.deregAck.errorCode;
        break;
        case SERVER_STATUS_MSG:

            /* Server type */
            data[index++] = msg->u.servInfo.conType;

            /* Server port */
            IDSCL_IntToData((data+index),msg->u.servInfo.port);
            index += sizeof(ITS_UINT);

            /* Server address */
            len = strlen(msg->u.servInfo.ipAddr);
            memcpy(&data[index], msg->u.servInfo.ipAddr, len);
            index = index + len;
        break;
        case DIASERVER_NOTIFY_MSG:

            /* Message Length */
            IDSCL_IntToData((data+index),msg->u.notifyInfo.length);
            index += sizeof(ITS_UINT);

            data[index++] = msg->u.notifyInfo.indType;

            /* Diameter session Index */
            IDSCL_IntToData((data+index),msg->u.notifyInfo.sessionIndex);
            index += sizeof(ITS_UINT);

            /* Diameter application Identifier */
            IDSCL_IntToData((data+index),msg->u.notifyInfo.appId);
            index += sizeof(ITS_UINT);

            {
            /* If, session Id string present, encode */
            ITS_UINT sesIdLen = msg->u.notifyInfo.length -
                           (sizeof(ITS_OCTET) + 2*sizeof(ITS_UINT));
            if (sesIdLen)
            {
               memcpy(data+index,msg->u.notifyInfo.data,sesIdLen); 
               index += sesIdLen;
            }
            }

        break;
        case GLOBAL_UNIQ_ADDR_ACK_MSG:
        {
            data[index++] = msg->u.guaAck.action;
            data[index++] = msg->u.guaAck.result;
            break;
        }
        default:

            DIA_TRACE_ERROR(("IDSCL_Encode: Invalid message type"));
            ret = !(ITS_SUCCESS);
            //fix for resource leak issue 
            free(data);
            data = NULL;

        break;
    }

    if (ret == ITS_SUCCESS)
    {
        event->src = ITS_APP_SRC;
        event->len = index;
        event->data = data;
    } 

    return (ret); 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 * 
 *  Return Value:
 * 
 *  Notes:
 * 
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    06-09-06   Bug Id 3615,4287    Added DataToInt() for decoding
 *
 ****************************************************************************/
IDSAPP_DLLAPI ITS_INT
IDSCL_Decode(IDS_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_INT index = 0;
    ITS_INT ret = ITS_SUCCESS;

    DIA_TRACE_DEBUG(("IDSCL_Decode"));

    /* event to structure */
    msg->clientID = 0;
    msg->clientID = IDSCL_DataToInt(&event->data[index]);
    index += sizeof(ITS_UINT);

    msg->msg_type = (IDS_MESSAGE_TYPE)event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_MSG:
            msg->u.regInfo.routing_criteria = 
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            switch(msg->u.regInfo.routing_criteria)
            {
                case IDS_APP_IDENTIFIER:
                    msg->u.regInfo.appIdentifier = 0;
                
                    msg->u.regInfo.appIdentifier = 
                                       IDSCL_DataToInt(&event->data[index]);
                    index += sizeof(ITS_UINT);

                    msg->u.regInfo.connectionType = 
                                   (IDS_CONNECTION_TYPE)event->data[index++]; 

                    msg->u.regInfo.appIdType = 0;

                    msg->u.regInfo.appIdType = 
                                       IDSCL_DataToInt(&event->data[index]);
                    index += sizeof(ITS_UINT);
                break;
            }
            break;

        case DEREGISTER_MSG:
            msg->u.regInfo.routing_criteria = 
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            break;

        case HEARTBEAT_MSG:
        break;

        case DIAMETER_MSG:
        break;
        case GLOBAL_UNIQ_ADDR_MSG:
        {
            msg->u.guaInfo.action = (IDS_GUA_ACTION)event->data[index++];
            msg->u.guaInfo.count = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);
            memcpy(msg->u.guaInfo.ipAddr, &event->data[index], IDS_IP_ADDR_LEN);
            index += IDS_IP_ADDR_LEN;
            break;
         }
        default:
            DIA_TRACE_ERROR(("IDSCL_Decode: Invalid message type"));
            ret = !(ITS_SUCCESS);
        break;
    }

    return (ret);
} 

/*.implementation:static
 ****************************************************************************
 *  Purpose: Reads the value in the byte array(network byte order) and
 *           returns the integer value.
 *
 *  Input Parameters:
 *      Byte Arrray.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Integer.
 *
 *  Return Value: int
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *
 ****************************************************************************/
IDSAPP_DLLAPI ITS_UINT
IDSCL_DataToInt(ITS_OCTET *d, ITS_INT c)
{
 unsigned int x = 0;
    int i;
                                                                                                                             
    for (i = 0; i < c; i++)
    {
        x <<= 8;
        /*
         * for the first octet, make sure we sign-extend into
         * the upper bits.  Subsequent octets can just be OR'd
         * into the lower bytes after the shift.
         */
        if (i == 0)
        {
            x |= (signed char)d[i];
        }
        else
        {
            x |= d[i];
        }
    }
                                                                                                                             
    return x;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Copies the integer value in to the byte array in the
 *           network byte order.
 *
 *  Input Parameters:
 *      integer value
 *
 *  Input/Output Parameters:
 *      Byte Array.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: None
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *
 ****************************************************************************/
IDSAPP_DLLAPI void
IDSCL_IntToData(ITS_OCTET *d, ITS_UINT val, ITS_INT c)
{
   for(int i=0; i< c; ++i)
   {
      d[i] = (val >> ((c-i-1)<<3)) & 0xFFU;
   }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: Prints the byte buffer
 *
 *  Input Parameters:
 *      Buffer and Length
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: None
 *
 *  Notes:
 *
 *  See Also:
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date       Reference               Description
 *  ---------------------------------------------------------------------------
 *   Kamakshi    19-02-07    Enhancement    To print in 0x00, format
 *
 ****************************************************************************/
IDSAPP_DLLAPI void
IDSCL_Print(ITS_OCTET *buff, ITS_ULONG len)
{
    if (itsDiaConfig.IsHexDumpEnabled())
    {
        for(int i=0; i < len; i++)
        {
            if ((i) % 8 == 0) 
                printf("\n");
            printf("0x%02x, ",buff[i]);
        }
        printf("\n\n"); 
        fflush(stdout);
    }
}

}

