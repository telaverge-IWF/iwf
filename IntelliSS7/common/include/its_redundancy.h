/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: its_redundancy.h,v $
 * LOG: Revision 9.3.6.3.4.2.22.1  2012/12/18 16:11:58  brajappa
 * LOG: Initial IWF branch creation and linux compilation changes
 * LOG:
 * LOG: Revision 9.3.6.3.4.2  2010/07/02 15:51:09  chandrashekharbs
 * LOG: Fix for issue 3041
 * LOG:
 * LOG: Revision 9.3.6.3.4.1  2010/02/19 09:33:10  kramesh
 * LOG: Issue 2560:Any node joining already active node, should come up as standby.
 * LOG:
 * LOG: Revision 9.3.6.2  2009/04/08 11:33:19  ssodhi
 * LOG: Adding REDUNDANCY_Console and Handling of DSM_FT_GROUP_COMM_LOST
 * LOG:
 * LOG: Revision 9.3.6.1  2009/03/23 11:05:30  ssodhi
 * LOG: Node redundancy state string
 * LOG:
 * LOG: Revision 9.3  2008/06/04 06:28:43  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.2  2007/01/10 11:15:04  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.6  2007/11/22 14:04:37  haltaf
 * LOG: Fix for BugId : 226(wizible) -mshanmugam
 * LOG:
 * LOG: Revision 9.1.10.3  2006/11/21 13:07:32  dsatish
 * LOG: InterNode dump issue fixed
 * LOG:
 * LOG: Revision 9.1.10.2  2006/11/02 08:49:45  dsatish
 * LOG: Changes merged from development branch
 * LOG:
 * LOG: Revision 9.1.10.1  2006/09/10 15:45:44  dsatish
 * LOG: ChangeStateFromStandbyToActiveNode function added
 * LOG:
 * LOG: Revision 9.1.30.1  2006/08/03 07:08:37  brajappa
 * LOG: Changes for ACC-RED-0653, redundancy fixes as per ACC-RED-SDS-GEN-V1.0.02
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.4.4.3  2005/01/07 14:58:23  ssingh
 * LOG: Changes in connection with  enhancement of ACTIVE-BACKUP redundancy.
 * LOG:
 * LOG: Revision 1.1.2.4.4.2  2004/12/20 12:32:33  mmanikandan
 * LOG: Support for Windows compilation.
 * LOG:
 * LOG: Revision 1.1.2.4.4.1  2004/12/15 15:53:59  dsatish
 * LOG: changes propagated from SHIM branch
 * LOG:
 * LOG: Revision 1.1.2.4  2004/11/18 11:29:47  sjaddu
 * LOG: Configuration checks added.
 * LOG:
 * LOG: Revision 1.1.2.3  2004/02/09 05:46:24  sjaddu
 * LOG: Added extern C for c++.
 * LOG:
 * LOG: Revision 1.1.2.2  2004/01/30 06:23:34  sjaddu
 * LOG: Send notification event to app for active-active config.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/01/27 13:40:02  sjaddu
 * LOG: Added file for active-back up redundancy.
 * LOG:
 *
 ****************************************************************************/

#ifndef  _ITS_REDUNDANCY_H_
#define  _ITS_REDUNDANCY_H_

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_transports.h>
#include <its_trace.h>

#if defined(WIN32)
#if defined(REDUNDANCY_IMPLEMENTATION)
#define REDDLLAPI __declspec(dllexport)
#else
#define REDDLLAPI __declspec(dllimport)
#endif
#else
#define REDDLLAPI
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define REDUNDANCY_CLASS_NAME                   "Redundancy-Type"
#define REDUNDANCY_APP_OPTION_STRING            "redundancyType"
#define REDUNDANCY_ACTIVE_ACTIVE_STRING         "active-active"
#define REDUNDANCY_ACTIVE_BACKUP_STRING         "active-backup"
#define REDUNDANCY_ACTIVE_HOT_BACKUP_STRING     "active-hotbackup"    
#define REDUNDANCY_NODE_STATE_ACTIVE_STRING     "active"
#define REDUNDANCY_NODE_STATE_BACKUP_STRING     "backup"
#define REDUNDANCY_NODE_STATE_STRING            "nodeState"
#define REDUNDANCY_APP_SELECT_ALL               "appSelectAll"
#define REDUNDANCY_APP_SELECT_NODE              "appSelectNode"
#define REDUNDANCY_APP_TIMER_STRING              "backupInactivityTimer"
#define ITS_RED_TIMER                            20

#define ITS_RED_MODULE_SRC                  (0X7FFEU)

#define ITS_STATE_CHANGE_EVENT              0xC7
#define ITS_NODE_LEFT_NOTIFICATION_EVENT    0xC8
#define ITS_NODE_JOIN_NOTIFICATION_EVENT    0xC9
#define ITS_COMM_ESTB_NOTIFICATION_EVENT    0xD1
#define ITS_GET_STATE_FROM_EVENT(evt)       evt->data[1]

/*Node state, only for active-back*/
typedef enum
{
    ITS_STATE_PRIMARY = 0,
    ITS_STATE_HOT_STANDBY,
    ITS_STATE_BACKUP
}
ITS_NODE_STATE;

#define ITS_NODE_STATE_STRING(s) \
        ((s==ITS_STATE_PRIMARY) ?       "PRIMARY/ACTIVE"  : \
          (s==ITS_STATE_HOT_STANDBY)  ? "HOT STANDBY"     : \
          (s==ITS_STATE_BACKUP)  ?      "BACKUP/INACTIVE" : \
                                        "ERROR/UNKNOWN") 


/*redundancy type*/
typedef enum
{
    ITS_ACTIVE_ACTIVE = 0,
    ITS_ACTIVE_STANDBY,
    ITS_ACTIVE_HOT_STANDBY
}
ITS_REDUNDANCY_TYPE;

#define ITS_REDUNDANCY_TYPE_STRING(t) \
        ((t==ITS_ACTIVE_ACTIVE) ?       REDUNDANCY_ACTIVE_ACTIVE_STRING : \
         (t==ITS_ACTIVE_STANDBY)  ?     REDUNDANCY_ACTIVE_BACKUP_STRING : \
         (t==ITS_ACTIVE_HOT_STANDBY) ?  REDUNDANCY_ACTIVE_HOT_BACKUP_STRING : \
                                        "ERROR/UNKNOWN") 

typedef ITS_NODE_STATE (*ITS_GetNodeStateProc)(void);
typedef CALLBACK_Manager* (*ITS_RedundancyCallBackMgr)(void);
typedef void (*ITS_ChangeNodeStateProc)(void);
 
void ChangeStateFromStandbyToActiveNode();
void ChangeStateFromActiveToStandbyNode();
typedef struct
{
    ITS_REDUNDANCY_TYPE              redundancyType;
    ITS_GetNodeStateProc             getNodeStateproc;   
    ITS_ChangeNodeStateProc          changeNodeStateProc; 
    ITS_RedundancyCallBackMgr        getRedundancyCallbackMgr; 
}
REDUNDANCY_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    REDUNDANCY_ClassPart    redunClass;
}
REDUNDANCY_ClassRec, *REDUNDANCY_Class;

/* 
 * interface
 */
REDDLLAPI extern REDUNDANCY_ClassRec    its_REDUNDANCYClassRec;
REDDLLAPI extern ITS_Class              itsREDUNDANCY_Class;


#define REDUNDANCY_CALLBACK_MGR(x) \
    (((REDUNDANCY_Class)(x))->redunClass.getRedundancyCallbackMgr)()

#define REDUNDANCY_CONFIGURED_TYPE(x) \
    (((REDUNDANCY_Class)(x))->redunClass.redundancyType)

#define REDUNDANCY_GET_NODE_STATE(x)\
    (((REDUNDANCY_Class)(x))->redunClass.getNodeStateproc)()

#define REDUNDANCY_CHANGE_NODE_STATE_PROC(x)\
    (((REDUNDANCY_Class)(x))->redunClass.changeNodeStateProc)

typedef struct
{
   ITS_NODE_STATE state;
}
ITS_USR_PART_STATE;

/*public API*/
REDDLLAPI int
ITS_SendStateChangeEventToStack(ITS_NODE_STATE type);
REDDLLAPI ITS_INT REDUNDANCY_GetNodeStartUpFlagAndState(ITS_NODE_STATE *state);
REDDLLAPI ITS_INT ITS_GetNodeState(ITS_NODE_STATE *state);
REDDLLAPI void ITS_SetNodeState(ITS_NODE_STATE state);
/* Callback */
REDDLLAPI extern CALLBACK_Manager  *ITS_RedundancyMgmtCallbacks;

#ifdef  __cplusplus
}
#endif

#endif
