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
 * ID: $Id: idc_common.cpp,v 3.5.46.2 2013/03/12 04:44:37 vsarath Exp $
 *
 * LOG: $Log: idc_common.cpp,v $
 * LOG: Revision 3.5.46.2  2013/03/12 04:44:37  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.5.46.1  2013/02/27 08:49:06  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.5  2010/09/22 05:22:22  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.4  2009/11/26 08:56:53  sureshj
 * LOG: Invalid memory access of 1 byte (valgrind reported). Ref Motorola
 * LOG: helpdesk ticket 2274.
 * LOG:
 * LOG: Revision 3.3  2009/04/07 14:27:29  sureshj
 * LOG: Overload control Indication handling added.
 * LOG:
 * LOG: Revision 3.2  2008/09/08 17:44:55  ssaxena
 * LOG: Fix for whizibile Issue Id 1139.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.25  2008/03/27 11:18:29  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.14.2.3  2007/04/12 10:54:42  rrath
 * LOG: Chnages to print Indication and Session-ID
 * LOG:
 * LOG: Revision 2.14.2.1  2007/04/04 06:12:34  nvijikumar
 * LOG: Send appIdType while registering with IDS.
 * LOG:
 * LOG: Revision 2.14  2007/02/19 04:50:45  kamakshilk
 * LOG: Hex dump Print format enhanced
 * LOG:
 * LOG: Revision 2.13  2007/01/19 13:01:49  kamakshilk
 * LOG: Memory leaks fixed
 * LOG:
 * LOG: Revision 2.12  2006/11/24 15:24:22  kamakshilk
 * LOG: Decode servInfo minor change
 * LOG:
 * LOG: Revision 2.11  2006/11/24 05:47:18  kamakshilk
 * LOG: DATA & IND_WITH_DATA merged
 * LOG:
 * LOG: Revision 2.10  2006/11/17 06:12:19  kamakshilk
 * LOG: ReleaseSession API and DccaEnable Added
 * LOG:
 * LOG: Revision 2.9  2006/11/16 13:38:17  kamakshilk
 * LOG: NULL checks added for strchr()
 * LOG:
 * LOG: Revision 2.8  2006/11/15 13:18:38  kamakshilk
 * LOG: Session Index set in the gcmd
 * LOG:
 * LOG: Revision 2.7  2006/11/14 13:39:42  kamakshilk
 * LOG: In GetSessionIndex change for solaris compilation
 * LOG:
 * LOG: Revision 2.6  2006/11/14 09:17:02  kamakshilk
 * LOG: Decode notification from server
 * LOG:
 * LOG: Revision 2.5  2006/11/08 06:15:46  kamakshilk
 * LOG: Changes for 64-bit support.ITS_ULONG changed to ITS_UINT
 * LOG:
 * LOG: Revision 2.4  2006/10/31 10:01:43  kamakshilk
 * LOG: IDSCL_Print function added
 * LOG:
 * LOG: Revision 2.3  2006/10/29 06:50:22  kamakshilk
 * LOG: Added print to display the received n sent buffers
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:22:50  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:39  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.11  2006/09/06 11:23:17  kamakshilk
 * LOG: Fix for bug Ids 3615,4287. Added IntToData and DataToInt APIs for encode and decode.
 * LOG:
 * LOG: Revision 1.10  2006/08/28 09:23:06  sumag
 * LOG: deleted a std::cout statement
 * LOG:
 * LOG: Revision 1.9  2006/07/25 13:42:08  sumag
 * LOG: Updates for Java.
 * LOG:
 * LOG: Revision 1.8  2006/06/14 09:37:22  kamakshilk
 * LOG: Decode ApplicationId received from the IDS.
 * LOG:
 * LOG: Revision 1.7  2006/05/23 06:20:31  adutta
 * LOG: Handling of inidication with message
 * LOG:
 * LOG: Revision 1.6  2006/04/26 10:21:57  adutta
 * LOG: Removed encoding of diameter message
 * LOG:
 * LOG: Revision 1.5  2006/04/25 15:59:42  yranade
 * LOG: Fix Compilation problem.
 * LOG:
 * LOG: Revision 1.4  2006/04/06 08:00:15  adutta
 * LOG: Reg/D-reg function modified for -ve error codes
 * LOG:
 * LOG: Revision 1.3  2006/03/14 06:39:18  adutta
 * LOG: Codec changes
 * LOG:
 * LOG: Revision 1.2  2006/03/13 05:20:53  adutta
 * LOG: Impl. changes for diameter encode/decode
 * LOG:
 * LOG: Revision 1.1  2006/03/02 12:12:34  adutta
 * LOG: First cut
 * LOG:
 ****************************************************************************/
#ident "$Id: idc_common.cpp,v 3.5.46.2 2013/03/12 04:44:37 vsarath Exp $"

#include <its++.h>

#include <idc_common.h>
#include <idc_trace.h>
#include <dia_defines.h>

#include <diameter/base/BaseGenericCommand.h>

// To satisfy the linker 

ITSDLLAPI its::ExceptionLog*    its::its_intern_exceptionLog = NULL;
ITSDLLAPI its::TraceSubSystem*  its::its_intern_trace = NULL;

using namespace diameter;

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
 * ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 * ----------------------------------------------------------------------------
 *   Kamakshi    06-09-06    Bug #3615,4287     Added IntToData() for encoding.
 *   Kamakshi    19-01-07    Enhancement        Memory leak fixed.

 ****************************************************************************/
MULAPP_DLLAPI ITS_INT
IDSCL_Encode(IDS_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_OCTET *data = event->data;
    ITS_INT index=0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT appId = 0;
    ITS_UINT appIdType = 0;

    IDS_TRACE_DEBUG(("IDSCL_Encode"));
   
    IDSCL_IntToData((data+index),msg->clientID);
    index += sizeof(ITS_UINT);

    data[index++] = msg->msg_type;

    event->src = ITS_APP_SRC;

    switch(msg->msg_type)
    {
        case REGISTER_MSG:
            appId = msg->u.regInfo.appIdentifier;
            appIdType = msg->u.regInfo.appIdType;

            data[index++] = msg->u.regInfo.routing_criteria;

            IDSCL_IntToData((data+index),appId);
            index += sizeof(ITS_UINT);

            data[index++] = msg->u.regInfo.connectionType;

            IDSCL_IntToData((data+index),appIdType);
            index += sizeof(ITS_UINT);
        break;
        case DEREGISTER_MSG:
            data[index++] = msg->u.deregInfo.routing_criteria;
        break;
        case GLOBAL_UNIQ_ADDR_MSG:
        {
            ITS_UINT count = 0;
            data[index++] = msg->u.guaInfo.action;
            count = msg->u.guaInfo.count;

            IDSCL_IntToData((data+index),count);
            index += sizeof(ITS_UINT);

            memcpy(&data[index], msg->u.guaInfo.ipAddr, IDSCL_IP_ADDR_LEN);
            index += IDSCL_IP_ADDR_LEN;

            break;
        }
        default:
            ret = !(ITS_SUCCESS);
        break;
    }/* switch end */

    if (ret == ITS_SUCCESS)
    {
        event->len = index;
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
 *   Suma        25-07-06     Enhancement       API to receive buffer:Java 
 *   Kamakshi    06-09-06    Bug #3615,4287     Added DataToInt() for decoding. 
 *   Kamakshi     14-11-06     Enhancement     1. Decode server Notification  
 *                                             2. Retrieve sesIdx from sesId
 *   Kamakshi     15-11-06     Enhancement      Set session Index in gcmd. 
 *   Kamakshi     24-11-06     Enhancement     1. sess Idx retrived for IND.
 *                                             2. DATA & IND_WITH_DATA merged.
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_decode(IDS_MESSAGE_BUFF *msg, ITS_EVENT *event)
{
    ITS_INT index = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = event->len;

    IDS_TRACE_DEBUG(("IDSCL_decode"));

    /* event to structure */
    msg->clientID = 0;

    msg->clientID = IDSCL_DataToInt(&event->data[index]);
    index += sizeof(ITS_UINT);

    msg->msg_type = (IDS_MESSAGE_TYPE)event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_ACK_MSG:
            /* Route criteria */
            msg->u.regInfo.routing_criteria =
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            /* Registration result */
            msg->u.regAck.result = (IDS_REG_STATUS)event->data[index++];

            /* Registration error */
            msg->u.regAck.errorCode = 0;
            msg->u.regAck.errorCode = event->data[index++];
            
            /* DCCA Feature Enabled at the IDS */
            msg->u.regAck.isDccaEnabled = 0;
            msg->u.regAck.isDccaEnabled = event->data[index++];

            /* Server type */
            msg->u.regAck.conType = (IDS_CONNECTION_TYPE)
                                           event->data[index++];

            /* Server port */
            msg->u.regAck.port = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Server address */
            memcpy(msg->u.regAck.ipAddr, &event->data[index], (len - index));
            msg->u.regAck.ipAddr[len - index] ='\0';

        break;

        case DEREGISTER_ACK_MSG:
            msg->u.regInfo.routing_criteria =
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            msg->u.deregAck.result = event->data[index++];
            msg->u.deregAck.errorCode =0;
            msg->u.deregAck.errorCode = (ITS_CHAR)event->data[index++];
        break;

        case SERVER_STATUS_MSG:

            /* Connection type */
            msg->u.servInfo.conType =
                                    (IDS_CONNECTION_TYPE)event->data[index++];
            /* Server port */
            msg->u.servInfo.port = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Server address */
            memcpy(msg->u.servInfo.ipAddr, &event->data[index], (len - index));
            msg->u.servInfo.ipAddr[len - index] ='\0';

        break;

        case DIAMETER_MSG:

            /* Diameter data length */
            len = 0;

            len = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_INT);

            /* Message type */
            msg->u.diaInfo.msgType = event->data[index++];

            /* Diameter session Index */
            msg->u.diaInfo.sessionIndex = 0;

            msg->u.diaInfo.sessionIndex = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Diameter app Id */
            msg->u.diaInfo.appIdentifier = 0;

            msg->u.diaInfo.appIdentifier = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);


            /* Diameter message or */
            /* Diameter indication with message */
            if ((msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_DATA) ||
               (msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA))
            {
                len -= DIA_DATA_POS;

                msg->u.diaInfo.dataLen = len;

                memcpy(&msg->u.diaInfo.data[0], &event->data[index], len);

                diameter::base::BaseGenericCommand gcmd(&event->data[index],
                                                                        len);
                /* For a client initiated session, retrieve the session 
                   Index from the session Id string. 
                   SessionId = "OH.OR;timestamp;higerbytes;clntId:sesIdx*/
                if (msg->u.diaInfo.sessionIndex < DIA_DIR_BIT)
                {
                   if (gcmd.getSessionId() != NULL)
                   {
                       std::string sessStr = gcmd.getSessionId()->value();
                       msg->u.diaInfo.sessionIndex = 
                          IDSCL_GetSessionIndex(sessStr);
                   }
                }
                gcmd.setSessionIndex(msg->u.diaInfo.sessionIndex);
            }
            /* Diameter indication */
            else if (msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_IND)
            {
                msg->u.diaInfo.indication = event->data[index];
                index++;

                if (msg->u.diaInfo.sessionIndex < DIA_DIR_BIT)
                {
                    ITS_UINT sesIdLen = len - DIA_DATA_POS - 1;
                    if (sesIdLen)
                    {
                        ITS_CHAR sesbuff[256] = "\0";
                        //Fixing Out-Of-Bounds Array Access
                        memcpy(sesbuff, &event->data[index], 
                                        ((sesIdLen > 256) ? 256 : sesIdLen));
                        sesbuff[255] = '\0';
                        std::string sessStr = sesbuff;
                        msg->u.diaInfo.sessionIndex =
                           IDSCL_GetSessionIndex(sessStr);
                    }
                }
            }
            else
            {
                ret = !(ITS_SUCCESS);
            }

        break;

        case DIASERVER_NOTIFY_MSG:

            /* Notification Data length */
            msg->u.notifyInfo.length = 0;

            msg->u.notifyInfo.length = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_INT);

            msg->u.notifyInfo.indType =
                                     (IDS_APP_IND_TYPE)event->data[index++];

            /* Diameter session Index */
            msg->u.notifyInfo.sessionIndex = 0;

            msg->u.notifyInfo.sessionIndex = 
                                       IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Diameter app Id */
            msg->u.notifyInfo.appId = 0;

            msg->u.notifyInfo.appId = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            {
            ITS_UINT sesIdLen = (msg->u.notifyInfo.length - DIA_DATA_POS);
            if (sesIdLen)
            {
                memcpy(msg->u.notifyInfo.data,&event->data[index],sesIdLen); 
            }
            else
            {
                msg->u.notifyInfo.data = NULL;
            }
            }

        break;

        default:
            ret = !(ITS_SUCCESS);
        break;

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
 * ---------------------------------------------------------------------------- 
 *   Name          Date        Reference               Description
 * ----------------------------------------------------------------------------
 *   Abhijit      14-06-06     Enhancement         Decode AppId received
 *   Kamakshi     06-09-06    Bug #3615,4287    Added DataToInt() for decoding. 
 *   Kamakshi     14-11-06     Enhancement     1. Decode server Notification  
 *                                             2. Retrieve sesIdx from sesId
 *   Kamakshi     15-11-06     Enhancement      Set session Index in gcmd. 
 *   Kamakshi     24-11-06     Enhancement     1. sess Idx retrived for IND.
 *                                             2. DATA & IND_WITH_DATA merged.
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_INT
IDSCL_Decode(IDS_MESSAGE *msg, ITS_EVENT *event)
{
    ITS_INT index = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = event->len;

    IDS_TRACE_DEBUG(("IDSCL_Decode"));

    IDS_TRACE_DEBUG(("\nIDSCL_Decode:: Received event from server. Len %d\n",
                                                                 event->len));
    IDSCL_Print(event->data, event->len);
       
    /* event to structure */
    msg->clientID = 0;

    msg->clientID = IDSCL_DataToInt(&event->data[index]);
    index += sizeof(ITS_UINT);

    msg->msg_type = (IDS_MESSAGE_TYPE)event->data[index++];

    switch(msg->msg_type)
    {
        case REGISTER_ACK_MSG:
            /* Route criteria */
            msg->u.regInfo.routing_criteria = 
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            /* Registration result */
            msg->u.regAck.result = (IDS_REG_STATUS)event->data[index++];

            /* Registration error */
            msg->u.regAck.errorCode = 0;
            msg->u.regAck.errorCode = event->data[index++];

            /* DCCA Feature Enabled at the IDS */
            msg->u.regAck.isDccaEnabled = 0;
            msg->u.regAck.isDccaEnabled = event->data[index++];

            /* Server type */           
            msg->u.regAck.conType = (IDS_CONNECTION_TYPE)
                                           event->data[index++];

            /* Server port */
            msg->u.regAck.port = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Server address */
            memcpy(msg->u.regAck.ipAddr, &event->data[index], (len - index));
            msg->u.regAck.ipAddr[len - index] ='\0';

        break;

        case DEREGISTER_ACK_MSG:
            msg->u.regInfo.routing_criteria = 
                                     (IDS_ROUTING_CRITERIA)event->data[index++];
            msg->u.deregAck.result = event->data[index++];
            msg->u.deregAck.errorCode =0;
            msg->u.deregAck.errorCode = (ITS_CHAR)event->data[index++];
        break;

        case SERVER_STATUS_MSG:

            /* Connection type */
            msg->u.servInfo.conType = 
                                    (IDS_CONNECTION_TYPE)event->data[index++];
            /* Server port */
            msg->u.servInfo.port = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Server address */
            memcpy(msg->u.servInfo.ipAddr, &event->data[index], (len - index));
            msg->u.servInfo.ipAddr[len - index] ='\0';

        break;

        case DIAMETER_MSG:

            /* Diameter data length */
            len = 0;

            len = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_INT);

            /* Message type */
            msg->u.diaInfo.msgType = event->data[index++];

            /* Diameter session Index */
            msg->u.diaInfo.sessionIndex = 0;

            msg->u.diaInfo.sessionIndex = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Diameter app Id */
            msg->u.diaInfo.appIdentifier = 0;

            msg->u.diaInfo.appIdentifier = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);


            /* Diameter message  or */
            /* Diameter indication with message */
            if ((msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_DATA) ||
               (msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA))
            {
                len -= DIA_DATA_POS;

                diameter::base::BaseGenericCommand gcmd(&event->data[index],
                                                                        len);
                /* For a client initiated session, retrieve the session 
                   Index from the session Id string. 
                   SessionId = "OH.OR;timestamp;higerbytes;clntId:sesIdx*/
                if (msg->u.diaInfo.sessionIndex < DIA_DIR_BIT)
                {
                   if (gcmd.getSessionId() != NULL)
                   {
                       std::string sessStr = gcmd.getSessionId()->value();
                       msg->u.diaInfo.sessionIndex = 
                          IDSCL_GetSessionIndex(sessStr);
                   }
                }
                gcmd.setSessionIndex(msg->u.diaInfo.sessionIndex);

                msg->u.diaInfo.cImpl = gcmd.transfer();

                if (msg->u.diaInfo.cImpl == NULL)
                {
                    ret = !(ITS_SUCCESS);
                }
            }
            /* Diameter indication */
            else if (msg->u.diaInfo.msgType == ITS_DIA_MSG_TYPE_IND)
            {
                msg->u.diaInfo.indication = event->data[index];
                msg->u.diaInfo.cImpl = NULL;
                IDS_TRACE_DEBUG(("Received Indication is: %s.",
                          INDICATION_TO_TEXT(msg->u.diaInfo.indication)));

                /**
                 * Fix for Whizibile Issue ID 1139.
                 * SessionIndex is always ZERO in below three Indication.
                 */
                if(msg->u.diaInfo.indication ==  DISCONECT_IND_FROM_STACK ||
                   msg->u.diaInfo.indication ==  FAILOVER_IND_FROM_STACK  ||
                   msg->u.diaInfo.indication ==  FAILBACK_IND_FROM_STACK  ||
                   msg->u.diaInfo.indication ==  OVERLOAD_IND_FROM_STACK  ||
                   msg->u.diaInfo.indication ==  OVLD_ABATED_IND_FROM_STACK)
                {
                    msg->u.diaInfo.sessionIndex = 0;
                    if(msg->u.diaInfo.indication == OVERLOAD_IND_FROM_STACK || 
                       msg->u.diaInfo.indication == OVLD_ABATED_IND_FROM_STACK)
                    {
                        msg->u.diaInfo.data[0] = '0';
                        msg->u.diaInfo.data[1] = '\0';
                    }
                    else 
                    { 
                        memcpy(msg->u.diaInfo.data,
                               &event->data[index],
                               len - DIA_DATA_POS);
                    }
                    break;
                }

                index++;

                if (msg->u.diaInfo.sessionIndex < DIA_DIR_BIT)
                {
                    ITS_UINT sesIdLen = len - DIA_DATA_POS - 1;
                    if (sesIdLen)
                    {
                        ITS_CHAR sesbuff[256] = "\0";
                        //Fixing Out-Of-Bounds Array Access
                        memcpy(sesbuff, &event->data[index], 
                                        ((sesIdLen > 256) ? 256 : sesIdLen));
                        sesbuff[255] = '\0';
                        std::string sessStr = sesbuff;
                        msg->u.diaInfo.sessionIndex =
                                        IDSCL_GetSessionIndex(sessStr);
                    }
                }
                memcpy(msg->u.diaInfo.data, &event->data[index],
                           len - DIA_DATA_POS);
            }
            else
            {
                ret = !(ITS_SUCCESS); 
            }

        break;

        case DIASERVER_NOTIFY_MSG:

            /* Notification Data length */
            msg->u.notifyInfo.length = 0;

            msg->u.notifyInfo.length = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_INT);

            msg->u.notifyInfo.indType =
                                     (IDS_APP_IND_TYPE)event->data[index++];

            /* Diameter session Index */
            msg->u.notifyInfo.sessionIndex = 0;

            msg->u.notifyInfo.sessionIndex = 
                                       IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            /* Diameter app Id */
            msg->u.notifyInfo.appId = 0;

            msg->u.notifyInfo.appId = IDSCL_DataToInt(&event->data[index]);
            index += sizeof(ITS_UINT);

            {
            ITS_UINT sesIdLen = (msg->u.notifyInfo.length - DIA_DATA_POS);
            if (sesIdLen)
            {
                msg->u.notifyInfo.data = (ITS_OCTET*)calloc(1,sesIdLen);
                memcpy(msg->u.notifyInfo.data,&event->data[index],sesIdLen); 
            }
            else
            {
                msg->u.notifyInfo.data = NULL;
            }
            }
        break;
        case GLOBAL_UNIQ_ADDR_ACK_MSG:
            msg->u.guaAck.action = (IDS_GUA_ACTION)event->data[index++];
            msg->u.guaAck.result = (IDS_REG_STATUS)event->data[index++];
        break;

        default:
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
IDSCL_DLLAPI ITS_UINT 
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
IDSCL_DLLAPI void
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
 * ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 * ----------------------------------------------------------------------------
 *   Kamakshi    19-02-07     Enhancement      To print in 0x00, format.
 *
 ****************************************************************************/
IDSCL_DLLAPI void
IDSCL_Print(ITS_OCTET *buff, ITS_ULONG len)
{
    if (IDSCL_IsTraceEnabled() && IDSCL_IsEnabled(IDS_DEBUG))
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

/*.implementation:static
 ****************************************************************************
 *  Purpose: Retrieves the session Index from the session Id string. 
 *
 *  Input Parameters:
 *      Session Id string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 * 
 *  Return Value: Session Index
 * 
 *  Notes:
 * 
 *  See Also:
 *
 * Revision History:
 * ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 * ----------------------------------------------------------------------------
 *   Kamakshi    14-11-06     Enhancement      Added char* conversion.
 *   Kamakshi    16-11-06     Bug              Bug found during system test.
 *                                             NULL Checks added for ptr.
 *
 ****************************************************************************/
IDSCL_DLLAPI ITS_UINT
IDSCL_GetSessionIndex(std::string &sessStr)
{
   ITS_UINT clntId = 0;
   ITS_UINT sesIdx = 0;
   char *ptr = NULL;
   int index = 0;

   IDS_TRACE_DEBUG(("IDSCL_GetSessionIndex"));

   /* SessionId Format = "OH.OR;TS;higher4octets;clntId:sesIdx */

   ptr = (char*)(sessStr.c_str());
   for (index = 0 ; index <3; index++)
   {
       ptr = (char*)strchr(ptr,';');
       if (ptr == NULL)
       {
           IDS_TRACE_ERROR(("IDSCL_GetSessionIndex: Invalid Session Id"));
           return 0;
       }
       if (++ptr == NULL)
       {
           IDS_TRACE_ERROR(("IDSCL_GetSessionIndex: Invalid Session Id"));
           return 0;
       }
   }

   // Fixing Unchecked return value
   if (sscanf(ptr,"%u:%u",&clntId, &sesIdx) > 0 )
   {
      return sesIdx;
   }
   else
   {
       IDS_TRACE_ERROR(("IDSCL_GetSessionIndex: sscnaf failed"));
       return 0;
   }
}

}

