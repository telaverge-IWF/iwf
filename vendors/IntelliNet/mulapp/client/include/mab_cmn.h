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
 * ID: $Id: mab_cmn.h,v 1.1 2005/05/25 10:13:58 mmanikandan Exp $
 *
 * LOG: $Log: mab_cmn.h,v $
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef MAB_CMN_H
#define MAB_CMN_H 

#include <its.h>
#include <its_types.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#if defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#endif
                                                                                
#if defined(WIN32)
 #if defined(MABCL_IMPLEMENTATION)
    #define MABCL_DLLAPI __declspec(dllexport)
 #else
    #define MABCL_DLLAPI __declspec(dllimport)
 #endif
#else
  #define MABCL_DLLAPI
#endif
                                                                                
/* Server Event types */
#define MABCL_TCAP_SRC     0X01
#define MABCL_ISUP_SRC     0x02
#define MABCL_APP_SRC      0x03
#define MABCL_MGMT_SRC     0x04
#define ITS_ISUP_MAX_SIZE  1000   
#define ITS_TCAP_MAX_SIZE  2000                                                                             
/*offset in msg frame */
#define DLG_ID_OFFSET    sizeof(ITS_ULONG) + sizeof(ITS_OCTET) 

#define MAX_NUM_CPT      10 

#define MAX_NUM_LID      0x8000 

#define MAX_TCAP_MSG_EVT 4000  

#define MAX_CPT_SIZE     sizeof(ITS_OCTET) + sizeof(ITS_CTXT) \
                         + sizeof(TCAP_CPT)

#define MAX_NUM_CPT_SIZE  sizeof(ITS_OCTET) \
                          + (sizeof(TCAP_CPT) * MAX_NUM_CPT)
/******************************************************************************
 * This structure will be filled depending on the routing criteria for TCAP app
 *****************************************************************************/
typedef struct 
{
    MTP3_POINT_CODE      lpc;
    MTP3_POINT_CODE      dpc;
    ITS_OCTET            ssn;
    ITS_CTXT             ltid;
    ITS_CTXT             utid;
}
MABCL_TCAP;
                                                                                
/******************************************************************************
 * This structure will be filled depending on the routing criteria for ISUP app
 *****************************************************************************/
typedef struct
{
    MTP3_POINT_CODE      lpc;
    MTP3_POINT_CODE      dpc;
    ITS_USHORT           lcic;
    ITS_USHORT           ucic;
}
MABCL_ISUP;

typedef enum
{
    MAB_MTP3_MSG_PAUSE,
    MAB_MTP3_MSG_RESUME,
    MAB_MTP3_MSG_STATUS,
    MAB_SCCP_SCMG_SS_ALLOWED,
    MAB_SCCP_SCMG_SS_PROHIBIT,
    MAB_SCCP_SCMG_SS_STATUS_TEST
} MGMT_MESSAGE;

typedef enum
{
     MABCL_TCAP_RT_DPC,
     MABCL_TCAP_RT_LPC,
     MABCL_TCAP_RT_LSSN,
     MABCL_TCAP_RT_LPC_LSSN,
     MABCL_TCAP_RT_LPC_DPC_LSSN,
     MABCL_TCAP_RT_TID_RANGE,
     MABCL_TCAP_RT_DID_EVEN,
     MABCL_TCAP_RT_DID_ODD,
     MABCL_ISUP_RT_DPC,
     MABCL_ISUP_RT_LPC,
     MABCL_ISUP_RT_DPC_CIC_RANGE,
     MABCL_ISUP_RT_LPC_CIC_RANGE
}
ROUTING_CRITERIA;

/*******************************************************************************
 * This structure will be filled when the Management message is 
 * recieved from the server. Suppose if we recieve a Management 
 * message from ISUP (PAUSE/ RESUME/STATUS ) we only fill the 
 * pc and the message name.
 ******************************************************************************/
typedef struct _mab_management 
{
     MGMT_MESSAGE mgmtMsg;
     union
     {
        MTP3_POINT_CODE pc;
        struct 
        {
             MTP3_POINT_CODE pc;
             ITS_OCTET       ssn;
        }
        TCAP_INFO;
     }
     MGMT_INFO; 
}
MAB_MANAGEMENT;

/*******************************************************************************
 * This structure will be filled when we want to send the registration event.
 * For example if the routing_criteria is MABCL_ISUP_RT_LPC we only fill in lpc   
 * in isup sub structure. So depending on the routing criteria we will have 
 * appropriate isup or tcap values which will be used to form a registration
 * event.
 *******************************************************************************/ 

typedef struct _mab_register 
{
     ROUTING_CRITERIA     routing_criteria;
     union
     {
         MABCL_TCAP    tcap;
         MABCL_ISUP    isup;
     }
     u;
}
MABCL_REGISTER;

/********************************************************************************
 * This structure is filled when we get the RGISTER ACK from the server    
 ********************************************************************************/
typedef struct _mab_register_ack 
{
    ROUTING_CRITERIA     routing_criteria;
    ITS_OCTET  result; /* If result is not success then look at errorcode */
    ITS_USHORT errorCode;
}
MABCL_REGISTER_ACK;

/*******************************************************************************
 * This structure is filled when we get the DERGISTER ACK from the server     
 *******************************************************************************/
typedef struct _mab_dergister_ack
{
    ROUTING_CRITERIA     routing_criteria;
    ITS_OCTET  result;
    ITS_USHORT errorCode;
}
MABCL_DEREGISTER_ACK;

/*
 * Structure will hold the info of reserve cic api
 */
typedef struct _mab_isup_reserveCic_info
{
    MTP3_HEADER mtp3;
    ITS_USHORT  cic;
    ITS_OCTET   cic_state;
    ITS_CTXT    vcic;
    ITS_UINT    ret;
}
MABCL_ISUP_RSV_CIC_ENTRY;

/*
 * Structure will hold the info of unreserve cic api
 */
typedef struct _mab_isup_unreserveCic_info
{
    MTP3_HEADER mtp3;
    ITS_USHORT  cic;
    ITS_UINT     ret;
}
MABCL_ISUP_UNRSV_CIC_ENTRY;


typedef enum
{
    REGISTER_MSG,
    DEREGISTER_MSG,
    ISUP_MSG,
    TCAP_MSG,
    MANAGEMENT_MSG,
    REGISTER_ACK_MSG,
    DERGISTER_ACK_MSG,
    ISUP_RSV_CIC_MSG,
    ISUP_URSV_CIC_MSG,
    ISUP_RSV_CIC_ACK_MSG,
    ISUP_URSV_CIC_ACK_MSG
}
MESSAGE_TYPE;

/********************************************************************************
 * A TCAP Event structure.
 ********************************************************************************/
typedef struct _mab_tcap
{
    ITS_USHORT len;
    ITS_OCTET* data;
}
MAB_TCAP;
/********************************************************************************
 * A ISUP Event structure.
 ********************************************************************************/

typedef struct _mab_isup
{
    ITS_USHORT len;
    ITS_OCTET* data;
}
MAB_ISUP;

typedef struct _mab_deregister
{
    ROUTING_CRITERIA  routing_criteria;
} MABCL_DEREGISTER;    
/**********************************************************************************
 * This is a main structure used by the clinet layer. When a event is 
 * recived it will be decoded and put in to this structure only the 
 * required fields. The opposite process will be done when sending the
 * event out. We only stuff the required fileds out of many from the 
 * structure and form the event. For example if we are sending a 
 * register event, we only need to have the clientID, msg_type & 
 * MAB_REGISTER structure. So prepare the event with these contents 
 * and send to the server layer. 
 **********************************************************************************/ 
typedef struct _mab_message
{
     ITS_ULONG            clientID;
     MESSAGE_TYPE         msg_type;
     union
     {
         MABCL_REGISTER          regInfo;
         MABCL_DEREGISTER        deregInfo;
         MAB_ISUP                isupInfo;
         MAB_TCAP                tcapInfo;
         MAB_MANAGEMENT          mgmtInfo;  
         MABCL_REGISTER_ACK      regAck;
         MABCL_DEREGISTER_ACK    deregAck;
         MABCL_ISUP_RSV_CIC_ENTRY rsvInfo;
         MABCL_ISUP_UNRSV_CIC_ENTRY unrsvInfo;
      }
      u;
}
MABCL_MESSAGE;

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
MABCL_Decode(MABCL_MESSAGE *msg, ITS_EVENT *event);

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
MABCL_Encode(MABCL_MESSAGE *msg, ITS_EVENT *event);

#endif
