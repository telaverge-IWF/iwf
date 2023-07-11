/******************************************************************************
 *                                                                            *
 *  Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.         *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 *  ID: $Id: its_nicmonitor.h,v 9.1 2007/01/10 11:14:58 yranade Exp $
 *  
 * LOG: $Log: its_nicmonitor.h,v $
 * LOG: Revision 9.1  2007/01/10 11:14:58  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1.2.2  2006/08/05 05:28:59  brajappa
 * LOG: Incorporated code review comments for ACC-RED-0653 redundancy enchancements
 * LOG:
 *
 ****************************************************************************/


#ifndef ITS_NICMONITOR_H
#define ITS_NICMONITOR_H

#include "its.h"
#include <net/if.h>


/* Defines */
#define MAX_IFNAME_SIZE IFNAMSIZ
#define MAX_IFS         8
#define MAX_IF_BUFFER   512
#define MAX_MANAGED_IFS 2

/* Not used now. But can be used in the future, for propogating
 * the event through GCS daemon to the DSM thread */
#define GCS_IP_LINK_UP      0xA0
#define GCS_IP_LINK_DOWN    0xA1

#define MAX_CLIENT_SOCKS    8

/* Type defs */
typedef struct _InterfaceNames
{
	ITS_INT       numInterfaces;
	ITS_CHAR      ifName[MAX_MANAGED_IFS][IFNAMSIZ];
}InterfaceNames;

typedef struct _ifInfo
{
    ITS_CHAR       name[MAX_IFNAME_SIZE];
    ITS_INT        status;
	ITS_INT        isActive;
}IfInfo;

typedef struct _config
{
    InterfaceNames ifNames;
    ITS_CHAR*      floatIP;
    ITS_INT        monDuration;
    ITS_INT        serverPort;
}Config;

/* Extern Functions */

ITS_INT ITS_ParseEthMonArg(ITS_INT* argc, ITS_CHAR** argv[]);

ITS_INT ITS_InitEthMonThread();

void ITS_TerminateEthMonThread();

#endif /* ITS_NICMONITOR_H */
