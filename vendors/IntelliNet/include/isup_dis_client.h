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
 * ID: $Id: isup_dis_client.h,v 1.2 2007/01/30 06:23:54 yranade Exp $
 *
 * LOG: $Log: isup_dis_client.h,v $
 * LOG: Revision 1.2  2007/01/30 06:23:54  yranade
 * LOG: Get things to compile.
 * LOG:
 * LOG: Revision 1.1  2005/07/07 04:59:22  mmanikandan
 * LOG: ISUP Distributed initial commit.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef ISUPDIS_CLIENTAPI_H
#define ISUPDIS_CLIENTAPI_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_thread_pool.h>

#if defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#endif

#if defined(WIN32)
 #if defined(ISUPDIS_IMPLEMENTATION)
    #define ISUPDIS_DLLAPI __declspec(dllexport)
 #else
    #define ISUPDIS_DLLAPI __declspec(dllimport)
 #endif
#else
  #define ISUPDIS_DLLAPI
#endif

/* Server Event types */
#define ISUPDIS_APP_SRC      0x03
#define ISUPDIS_MGMT_SRC     0x04
#define ISUPDIS_ISUP_SRC     0x06

typedef struct
{
    ITS_OCTET            regType; /* 1 - Primary, 0 - Backup */
    MTP3_POINT_CODE      lpc;
    MTP3_POINT_CODE      dpc;
    ITS_USHORT           lcic;
    ITS_USHORT           ucic;
}
ISUPDIS_ISUP;

typedef enum
{
    ISUPDIS_MTP3_MSG_PAUSE,
    ISUPDIS_MTP3_MSG_RESUME,
    ISUPDIS_MTP3_MSG_STATUS,
} MGMT_MESSAGE;

typedef enum
{
     ISUPDIS_ISUP_RT_DPC = 8,
     ISUPDIS_ISUP_RT_LPC,
     ISUPDIS_ISUP_RT_DPC_CIC_RANGE,
     ISUPDIS_ISUP_RT_LPC_CIC_RANGE
}
ROUTING_CRITERIA;

typedef struct _isup_management
{
     MGMT_MESSAGE mgmtMsg;
     MTP3_POINT_CODE pc;
}
MSG_MANAGEMENT;

typedef struct _isup_register
{
     ROUTING_CRITERIA     routing_criteria;
     ITS_OCTET            numOfRecords;
     ISUPDIS_ISUP         isup[10];
}
ISUPDIS_REGISTER;

typedef struct _isup_register_ack
{
    ROUTING_CRITERIA     routing_criteria;
    ITS_OCTET  result; /* If result is not success then look at errorcode */
    ITS_USHORT errorCode;
}
ISUPDIS_REGISTER_ACK;

typedef struct _isup_dergister_ack
{
    ROUTING_CRITERIA     routing_criteria;
    ITS_OCTET  result;
    ITS_USHORT errorCode;
}
ISUPDIS_DEREGISTER_ACK;

typedef enum
{
    REGISTER_MSG = 0,
    DEREGISTER_MSG = 1,
    MANAGEMENT_MSG = 4,
    REGISTER_ACK_MSG = 5,
    DERGISTER_ACK_MSG = 6,
    MTP3_MSG = 12
}
MESSAGE_TYPE;

typedef struct _msg_isup
{
    ITS_USHORT len;
    ITS_OCTET* data;
}
MSG_ISUP;

typedef struct _isup_deregister
{
    ROUTING_CRITERIA  routing_criteria;
}
ISUPDIS_DEREGISTER;

typedef struct _isup_message
{
     ITS_ULONG            clientID;
     MESSAGE_TYPE         msg_type;
     union
     {
         ISUPDIS_REGISTER          regInfo;
         ISUPDIS_DEREGISTER        deregInfo;
         MSG_ISUP                  isupInfo;
         MSG_MANAGEMENT            mgmtInfo;
         ISUPDIS_REGISTER_ACK      regAck;
         ISUPDIS_DEREGISTER_ACK    deregAck;
      }
      u;
}
ISUPDIS_MESSAGE;

/*
 * Send the event to Server
 */

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_SendMsg_ANSI(ITS_EVENT *evt);

ISUPDIS_DLLAPI ITS_INT
ISUPDIS_SendMsg_CCITT(ITS_EVENT *evt);
                                                                                
/*
 * Registration function
 */
ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Register(ISUPDIS_MESSAGE *ctxt);

/*
 * Deregister function
 */
ISUPDIS_DLLAPI ITS_INT
ISUPDIS_Deregister(ISUPDIS_MESSAGE *ctxt);

#endif
