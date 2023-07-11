/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_gcs_handler.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/11/16 14:51:19  tpanda
 * LOG: New file added to handle Mulitcast mesg from GCS
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_gcs_handler.cpp,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_gcs_handler.cpp,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $"

#include <its_dia_config.h>
#include <dia_cmn.h>
#include <dia_trace.h>
#include <dia_utils.h>
#include <dia_connector.h>
#include <dia_gcs_handler.h>
#include <dia_session_table.h>
#include <dia_msg_router.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

/*
 * For the redundancy
 */

#define DSM_LockTable             DSM_LockTableLocal
#define DSM_UnlockTable           DSM_UnlockTableLocal
#define DSM_AllocNoLock           DSM_AllocNoLockLocal
#define DSM_FindNoLock            DSM_FindNoLockLocal
#define DSM_FreeNoLock            DSM_FreeNoLockLocal
#define DSM_CommitNoLock          DSM_CommitNoLockLocal
#define DSM_Alloc                 DSM_AllocLocal
#define DSM_Find                  DSM_FindLocal
#define DSM_Free                  DSM_FreeLocal
#define DSM_Commit                DSM_CommitLocal

int 
DiaGcsMsgHandler::HandleMessage(DIAThread *thr, its::Event &ev)
{
    ITS_USHORT nodeId;
    nodeId = DSM_GetNodeId();
    if ( nodeId != ev.GetData()[0])
    {
        SESSION_ENTRY sessionInfo;
        char *key = (char *)&ev.GetData()[2];
        ITS_UINT keyLen = strlen(key);
        memcpy (&sessionInfo, &ev.GetData()[keyLen + 3], sizeof(SESSION_ENTRY));

 
        switch (ev.GetData()[1])    
        {
        case GCS_CTX_INSERT_IND_FROM_STACK: 
        {

            void *ret;
            int error = ITS_ENOTFOUND;
            int res;

            DT_DBG(("GCS::InterEntry Indication: %s",key));

            ret = DSM_Alloc(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,
                            (ITS_OCTET *)key,
                            keyLen,
                            sizeof(SESSION_ENTRY),
                            &error);

             if (ret == NULL)
             {
                 DT_ERR(("InsertEntry: alloc failed for %s", (char *)key));
                 return ITS_DIA_ALLOCFAIL;
             }
             else
             {
                 SESSION_ENTRY *entry = (SESSION_ENTRY *)ret;
                 memcpy(entry, &sessionInfo, sizeof(SESSION_ENTRY));

                 res = DSM_Commit(SESSION_TABLE_FT_GROUP_ID,
                                  SESSION_TABLE_ID,
                                  (ITS_OCTET *)key,
                                  keyLen,
                                  ret);

                 if (res != ITS_SUCCESS)
                 {
                     DT_ERR(("InsertEntry: commit failed for %s", (char*)key));
                     return ITS_DIA_ALLOCFAIL;
                 }
                 ITS_UINT sessIdxkey = ITS_DIA_OUTBOUND_SESS_INDEX_ENTRY;
                 //check if outbound or inbound session
                 if(DIA_SE_SINDX(&sessionInfo) & 0x8000)
                 {
                     sessIdxkey = ITS_DIA_INBOUND_SESS_INDEX_ENTRY;
                 }
                 while (((ret = DSM_Find(SESSION_TABLE_FT_GROUP_ID,
                             SESSION_TABLE_ID,
                             (ITS_OCTET*)&sessIdxkey,
                             sizeof(ITS_UINT),
                             &error)) == NULL) &&
                             (error == ITS_EINUSE))
                 {
                      TIMERS_USleep(100);

                      /* Eventually either the lock will be released by the other node which
                       * will cause ret to be NON-NULL or the row will be deleted which will
                       * cause ret to be NULL and error = ITS_ENOTFOUND
                       * If the lock is not released by the other node for a specific
                       * interval it will be busted by DSM_Find and ret will be NON-NULL
                       */
                }
                if (error == ITS_ENOTFOUND)
                {
                   ret = DSM_Alloc(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,
                            (ITS_OCTET*)&sessIdxkey,
                            sizeof(ITS_UINT),
                            sizeof(ITS_UINT),
                            &error);

                }
                if (ret == NULL)
                {
                   DT_ERR(("InsertEntry Session Index: alloc failed for %d", DIA_SE_SINDX(&sessionInfo)));
                   return ITS_DIA_ALLOCFAIL;
                }
                memcpy((ITS_UINT*)ret, &DIA_SE_SINDX(&sessionInfo), sizeof(ITS_UINT));
                res = DSM_Commit(SESSION_TABLE_FT_GROUP_ID,
                          SESSION_TABLE_ID,
                          (ITS_OCTET*)&sessIdxkey,
                          sizeof(ITS_UINT),
                          ret);
                if (res != ITS_SUCCESS)
                {
                   DT_ERR(("InsertEntry Session Index: commit failed for %d", DIA_SE_SINDX(&sessionInfo)));
                   return ITS_DIA_ALLOCFAIL;
                }
            }
            return (ITS_SUCCESS);
        }
        break;
        case GCS_CTX_MODIFY_IND_FROM_STACK: 
        {
            void *ret;
            int error;
            int res;

            DT_DBG(("GCS::ModifyEntry Indication: %s",key));
            while (((ret = DSM_Find(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,        //tableId
                            (ITS_OCTET*)key,         //key
                            keyLen,                  //keylen
                            &error)) == NULL) &&
                            (error == ITS_EINUSE))
            {
                TIMERS_USleep(100);

                /* Eventually either the lock will be released by the other node                 * which will cause ret to be NON-NULL or the row will be 
                 * deleted which will cause ret to be NULL and error = 
                 * ITS_ENOTFOUND If the lock is not released by the other node 
                 * for a specific interval it will be busted by DSM_Find and 
                 * ret will be NON-NULL
                */
            }
            if (ret == NULL)
            {
               DT_ERR(("GCS ModifyEntry: SessionId %s is not present",(char*)key));
               return !ITS_SUCCESS;
            }
            else
            {
               SESSION_ENTRY *entry = (SESSION_ENTRY *)ret;
               memcpy(entry, &sessionInfo, sizeof(SESSION_ENTRY));
               res = DSM_Commit(SESSION_TABLE_FT_GROUP_ID,
                         SESSION_TABLE_ID,
                         (ITS_OCTET*)key,
                         keyLen,
                         ret);

               if (res != ITS_SUCCESS)
               {
                  DT_ERR(("ModifyEntry: commit failed for %s", (char*)key));
                  return !ITS_SUCCESS;
               }
            }
        }
        break;
        case GCS_CTX_REMOVE_IND_FROM_STACK: 
        {
            void *ret;
            int error;
            int res;
            DT_DBG(("GCS::RemoveEntry Indication: %s",key));
            while (((ret = DSM_Find(SESSION_TABLE_FT_GROUP_ID,
                            SESSION_TABLE_ID,        //tableId
                            (ITS_OCTET*)key,         //key
                            keyLen,                  //keylen
                            &error)) == NULL) &&
                            (error == ITS_EINUSE))
            {
                TIMERS_USleep(100);

                /* Eventually either the lock will be released by the other node                 * which will cause ret to be NON-NULL or the row will be 
                 * deleted which will cause ret to be NULL and error = 
                 * ITS_ENOTFOUND If the lock is not released by the other node 
                 * for a specific interval it will be busted by DSM_Find and 
                 * ret will be NON-NULL
                */
            }
            if (ret == NULL)
            {
               DT_ERR(("GCS RemoveEntry: SessionId %s is not present",(char*)key));
               return !ITS_SUCCESS;
            }
            else
            {
                 if (DIA_SE_STYPE(&sessionInfo) == DIA_AUTHORIZATION)
                 {
                     //StopAllAuthTimers(&sessionInfo);
                 }
                 else
                 {
                     //StopAllAcctTimers(&sessionInfo);
                 }

                 res = DSM_Free(SESSION_TABLE_FT_GROUP_ID,
                         SESSION_TABLE_ID,
                         (ITS_OCTET*)key,
                         keyLen,
                         ret);

                 if (res != ITS_SUCCESS)
                 {
                     DT_ERR(("RemoveEntry: commit failed for %s", (char*)key));
                     return !ITS_SUCCESS;
                 }
            }
        }
        break;
        default:
            DT_DBG(("GCS::Unknown Indication: %s",key));
        }
    }
    return (ITS_SUCCESS);
}

