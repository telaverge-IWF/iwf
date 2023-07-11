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
 * ID: $Id: dmc_common.h,v 1.1 2009/03/02 04:39:43 nvijikumar Exp $
 *
 * LOG: $Log: dmc_common.h,v $
 * LOG: Revision 1.1  2009/03/02 04:39:43  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dmc_common.h,v 1.1 2009/03/02 04:39:43 nvijikumar Exp $"

#ifndef DMC_COMMON_H
#define DMC_COMMON_H 

#include <its.h>
#include <its_types.h>
#include <dm_msgs.h>

#define DM_TIME_STRING_SIZE 80

static time_t now;                   /* Current time */
static struct tm *now_time, tbuf;
static char temptime[DM_TIME_STRING_SIZE];

extern ITS_BOOLEAN traceEnabled;

#define PRT_TRACE_HDR()                                                     \
    time(&now);                                                             \
    now_time = localtime_r(&now, &tbuf);                                    \
    strftime(temptime, DM_TIME_STRING_SIZE, "[%b%d %Y %H:%M:%S]: ", &tbuf); \
    printf("%s",temptime);

#define DMC_TRACE_DBG(x)                                               \
    if (traceEnabled == ITS_TRUE)                                      \
    {                                                                  \
        PRT_TRACE_HDR();                                               \
        printf("DMC: DBG: file : %s line : %d\n",__FILE__, __LINE__);  \
        printf x;                                                      \
        printf ("\n");                                                 \
        fflush(stdout);                                                \
    }

#define DMC_TRACE_CRIT(x)                                              \
    if (traceEnabled == ITS_TRUE)                                      \
    {                                                                  \
        PRT_TRACE_HDR();                                               \
        printf("DMC: CRIT: file : %s line : %d\n",__FILE__, __LINE__); \
        printf x;                                                      \
        printf ("\n");                                                 \
        fflush(stdout);                                                \
    }

#define DMC_TRACE_ERR(x)                                               \
    if (traceEnabled == ITS_TRUE)                                      \
    {                                                                  \
        PRT_TRACE_HDR();                                               \
        printf("DMC: ERR: file :%s line  : %d\n",__FILE__, __LINE__);  \
        printf x;                                                      \
        printf ("\n");                                                 \
        fflush(stdout);                                                \
    }

#define DMC_TRACE_WRN(x)                                               \
    if (traceEnabled == ITS_TRUE)                                      \
    {                                                                  \
        PRT_TRACE_HDR();                                               \
        printf("DMC: WARN: file: %s line : %d\n",__FILE__, __LINE__);  \
        printf x;                                                      \
        printf ("\n");                                                 \
        fflush(stdout);                                                \
    }

typedef enum
{
    DMC_CONNECT,
    DMC_DISCONNECT
}DMC_CB_TYPE;

typedef struct
{
    DMC_CB_TYPE type;
}DMC_CB_INFO;

/* Callback to provide indications to app */
typedef void (*DMC_CB)(DMC_CB_INFO dmcCbInfo);

class DmcCodec : public DmCodecUtils
{
public:
    DmcCodec(){};
    ~DmcCodec(){};
    static ITS_INT DecodeDmMsgStats(ITS_OCTET* inStr, DM_MSG_STATS *mStats);
    static ITS_INT Encode(DM_MSG *msg, ITS_EVENT *ev);
    static ITS_INT Decode(DM_MSG *msg, ITS_EVENT *ev);
};

#endif

