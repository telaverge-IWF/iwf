/*********************************-*-C-*-************************************
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
 * LOG: $Log: dcca_context.cpp,v $
 * LOG: Revision 3.1.70.1.8.2.2.1.4.1  2015/01/22 10:33:46  pramana
 * LOG: Unused variable warning fix
 * LOG:
 * LOG: Revision 3.1.70.1.8.2.2.1  2014/08/26 10:24:47  pramana
 * LOG: Logging related refinements
 * LOG:
 * LOG: Revision 3.1.70.1.8.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.1.70.1.8.1  2014/02/20 14:23:38  jkchaitanya
 * LOG: mh fixes
 * LOG:
 * LOG: Revision 3.1.70.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.10  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.2.1  2007/07/13 11:03:57  hbhatnagar
 * LOG: Added addtional Traces for DSM APIs Failure.
 * LOG:
 * LOG: Revision 2.8  2007/02/21 13:02:24  hbhatnagar
 * LOG: made changes for the proper return values for add,modify and remove.
 * LOG:
 * LOG: Revision 2.7  2006/11/30 10:10:19  hbhatnagar
 * LOG: made changes for return of DCCA state machine error
 * LOG:
 * LOG: Revision 2.6  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.5  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.4  2006/11/13 06:40:40  hbhatnagar
 * LOG: Proper indentation and cleanup done
 * LOG:
 * LOG: Revision 2.3  2006/10/31 08:36:11  hbhatnagar
 * LOG: Made changes for BCGI and cleanup
 * LOG:
 * LOG: Revision 2.2  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:37:33  nvijikumar
 * LOG: Added the statistics for active sessions (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_context.cpp,v 3.1.70.1.8.2.2.1.4.1 2015/01/22 10:33:46 pramana Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dcca_context.h>
#include <dcca_trace.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

#define DSM_Find          DSM_FindLocal
#define DSM_Alloc         DSM_AllocLocal  
#define DSM_Commit        DSM_CommitLocal
#define DSM_FindNoLock    DSM_FindNoLockLocal
#define DSM_Free          DSM_FreeLocal

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAContext::DCCAContext()
{
    memset(&dccaContext, 0x00, sizeof(DCCA_CONTEXT));
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAContext::~DCCAContext()
{    
    memset(&dccaContext, 0x00, sizeof(DCCA_CONTEXT));
}

/****************************************************************************
 *
 *  Purpose                : Method to get context
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: The DCCA_CONTEXT
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAContext::GetContext(DCCA_CONTEXT *ctx)
{
    memcpy(ctx, &dccaContext, sizeof(DCCA_CONTEXT));
}

/****************************************************************************
 *
 *  Purpose                : Method to set context
 *
 *  Input Parameters       : The DCCA_CONTEXT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAContext::SetContext(DCCA_CONTEXT *ctx)
{
    memcpy(&dccaContext, ctx, sizeof(DCCA_CONTEXT));
}

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAContextTable::DCCAContextTable()
{
    dccaStats = DCCAStats::GetDCCAStats();
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAContextTable::~DCCAContextTable()
{    
    dccaStats = NULL;
}

/****************************************************************************
 *
 *  Purpose                : Method to add an entry to DSM table
 *
 *  Input Parameters       : ctx - Context to add
 *                             key - key to table
 *                           len - Length of key
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAContextTable::Add(
DCCA_CONTEXT *&ctx, ITS_OCTET *key, ITS_UINT len)
{
    void *ret;
    int error;
    int res;

    DCCA_TRACE_DEBUG(("DCCAContextTable::Add SessionId %s", (char *)key));
    while (((ret = DSM_Find(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                             DCCA_CONTEXT_TABLE_ID,
                             key,
                             len,
                             &error)) == NULL) &&
           (error == ITS_EINUSE))
    {
         DCCA_TRACE_WARNING(("DCCAContextTable::DCCAContextTable Locked")); 
         DCCA_TRACE_WARNING(("DCCAContextTable::Add Waiting for release"));
         TIMERS_USleep(100);

         /* Eventually either the lock will be released by the other node which
          * will cause ret to be NON-NULL or the row will be deleted which will
          * cause ret to be NULL and error = ITS_ENOTFOUND
          * If the lock is not released by the other node for a specific
          * interval it will be busted by DSM_Find and ret will be NON-NULL
          */
         //Correcting Unused POinter Value
         (void)ret;
    }

    if (error == ITS_ENOTFOUND)
    {
         // Row is not present
         ret = DSM_Alloc(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                         DCCA_CONTEXT_TABLE_ID,
                         key,
                         len,
                         sizeof(DCCA_CONTEXT),
                         &error);

         if (ret == NULL)
         {
             DCCA_TRACE_ERROR(("DCCAContextTable::Add: Alloc Failed for %s", 
                              (char *)key));
             return (!ITS_SUCCESS);
         }
         else
         {
             DCCA_CONTEXT *entry = (DCCA_CONTEXT*)ret;
             memcpy(entry, ctx, sizeof(DCCA_CONTEXT));

             res = DSM_Commit(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                              DCCA_CONTEXT_TABLE_ID,
                              key,
                              len,
                              ret);

             if (res != ITS_SUCCESS)
             {
                 DCCA_TRACE_ERROR(("DCCAContextTable::Add: Commit failed for %s", (char*)key));
                 return res;
             }
         }
    }
    else
    {
        // Entry already present. Treat it like modify. Overwrite existing.
        DCCA_TRACE_DEBUG(("DCCAContextTable::Add: Entry exists already.")); 
        DCCA_CONTEXT *entry = (DCCA_CONTEXT*)ret;

        // If Tx timer is started stop the timer
        if (entry->timer)
        {
            TIMERS_CancelTimer(entry->timerkey);
            entry->timer = 0;
            DCCA_TRACE_DEBUG(("DCCAContextTable::Add Timer stopped for older CCR-I"));
        }

        if (ret != ctx)
        {
            memcpy(entry, ctx, sizeof(DCCA_CONTEXT));
        }

        res = DSM_Commit(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                         DCCA_CONTEXT_TABLE_ID,
                         key,
                         len,
                         ret);

        if (res != ITS_SUCCESS)
        {
            DCCA_TRACE_ERROR(("DCCAContextTable::Add: Commit failed for %s", (char*)key));
            return !ITS_SUCCESS;
        }
    }

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 *  Purpose                : Method to get an entry from DSM table
 *
 *  Input Parameters       : key - key to table
 *                           len - Length of key
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : ctx - Copy of context fetched
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT 
DCCAContextTable::Fetch(
DCCA_CONTEXT *&ctx, ITS_OCTET *key, ITS_UINT len)
{
    void *ret;
    int error;

    DCCA_TRACE_DEBUG(("DCCAContextTable::Fetch: %s", (char *)key));
    while (((ret = DSM_FindNoLock(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                                  DCCA_CONTEXT_TABLE_ID,     //tableId
                                  key,                  //key
                                  len,               //keylen
                                  &error)) == NULL) &&
           (error == ITS_EINUSE))
    {
         DCCA_TRACE_WARNING(("DCCAContextTable::DCCAContextTable Locked"));   
         DCCA_TRACE_WARNING(("DCCAContextTable::Fetch Waiting for release"));
         TIMERS_USleep(100);

         /* Eventually either the lock will be released by the other node which
          * will cause ret to be NON-NULL or the row will be deleted which will
          * cause ret to be NULL and error = ITS_ENOTFOUND
          * If the lock is not released by the other node for a specific
          * interval it will be busted by DSM_Find and ret will be NON-NULL
          */
    }
    if (ret == NULL)
    {
         // Row is not present
         DCCA_TRACE_WARNING(("DCCAContextTable::Fetch: SessionId %s is not present", 
                      (char*)key));
         ctx = NULL;
    }
    else
    {
         ctx = (DCCA_CONTEXT *)(ret);
         return (ITS_SUCCESS);

    }

    return (!ITS_SUCCESS);
}

/****************************************************************************
 *
 *  Purpose                : Method to remove an entry from DSM table
 *
 *  Input Parameters       : key - key to table
 *                           len - Length of key
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAContextTable::Remove(ITS_OCTET *key, ITS_UINT len)
{
    void *ret;
    int error;
    int res;

    DCCA_TRACE_DEBUG(("DCCAContextTable::Remove: %s", (char *)key));
    while (((ret = DSM_Find(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                            DCCA_CONTEXT_TABLE_ID,        //tableId
                            key,                     //key
                            len,                  //keylen
                            &error)) == NULL) &&
           (error == ITS_EINUSE))
    {
         DCCA_TRACE_WARNING(("DCCAContextTable::DCCAContextTable Locked"));
         DCCA_TRACE_WARNING(("DCCAContextTable::Remove Waiting for release"));
         TIMERS_USleep(100);

         /* Eventually either the lock will be released by the other node which
          * will cause ret to be NON-NULL or the row will be deleted which will
          * cause ret to be NULL and error = ITS_ENOTFOUND
          * If the lock is not released by the other node for a specific
          * interval it will be busted by DSM_Find and ret will be NON-NULL
          */
    }
    if (ret == NULL)
    {
         // Row is not present
         DCCA_TRACE_ERROR(("DCCAContextTable::Remove: SessionId %s is not present", 
                    (char*)key));
         return (!ITS_SUCCESS);
    }
    else
    {
         // Row is present, the data is in "ret"
         res = DSM_Free(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                        DCCA_CONTEXT_TABLE_ID,
                        key,
                        len,
                        ret);

         if (res != ITS_SUCCESS)
         {
             DCCA_TRACE_ERROR(("DCCAContextTable::Remove: Free failed"));
             return (res);
         }
    }

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 *  Purpose                : Method to modify an entry in DSM table
 *
 *  Input Parameters       : ctx - Context to modify
 *                             key - key to table
 *                           len - Length of key
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAContextTable::Modify(
DCCA_CONTEXT *&ctx, ITS_OCTET *key, ITS_UINT len)
{
    void *ret;
    int res, error;

    DCCA_TRACE_DEBUG(("DCCAContextTable::Modify: %s size %d", (char *)key, len));
    while (((ret = DSM_Find(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                            DCCA_CONTEXT_TABLE_ID,        //tableId
                            key,                     //key
                            len,                  //keylen
                            &error)) == NULL) &&
           (error == ITS_EINUSE))
    {
         DCCA_TRACE_WARNING(("DCCAContextTable::DCCAContextTable Locked"));
         DCCA_TRACE_WARNING(("DCCAContextTable::Modify Waiting for release"));
         TIMERS_USleep(100);

         /* Eventually either the lock will be released by the other node which
          * will cause ret to be NON-NULL or the row will be deleted which will
          * cause ret to be NULL and error = ITS_ENOTFOUND
          * If the lock is not released by the other node for a specific
          * interval it will be busted by DSM_Find and ret will be NON-NULL
          */
    }
    if (ret == NULL)
    {
        DCCA_TRACE_ERROR(("DCCAContextTable::Modify: SessionId %s is not present", 
                   (char*)key));

        return !ITS_SUCCESS;
    }
    else
    {
        DCCA_CONTEXT *entry = (DCCA_CONTEXT*)ret;

        memcpy(entry, ctx, sizeof(DCCA_CONTEXT));

        res = DSM_Commit(DCCA_CONTEXT_TABLE_FT_GROUP_ID,
                         DCCA_CONTEXT_TABLE_ID,
                         key,
                         len,
                         ret);

        if (res != ITS_SUCCESS)
        {
            DCCA_TRACE_ERROR(("DCCAContextTable::Modify: Commit failed for %s", (char*)key));
            return !ITS_SUCCESS;
        }
    }

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 *  Purpose                : Method to access the DSM table
 *
 *  Input Parameters       : act - Action on this context
 *                           ctx - Context acted upon
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAContextTable::SubmitToCtx(ITS_INT act, DCCA_CONTEXT *&ctx, ITS_OCTET* key, ITS_UINT len)
{
    ITS_INT    ret = ITS_SUCCESS;

    switch(act)
    {        
        case DCCA_CONTEXT_ADD:
        {
            ret = Add(ctx, key, len);
            if (ret != ITS_SUCCESS)
            {
                ret = ITS_DIA_DCCA_ERROR;
            }
            else
            {
                dccaStats->AddToActiveSession();
            }
            break;
        }
        case DCCA_CONTEXT_FETCH:
        {
            ret = Fetch(ctx, key, len);
            if (ret != ITS_SUCCESS)
            {
                ret = ITS_DIA_UNKNOWN_SESSION_ID;
            }
            break;
        }
        case DCCA_CONTEXT_MODIFY:
        {
            ret = Modify(ctx, key, len);
            if (ret != ITS_SUCCESS)
            {
                ret = ITS_DIA_DCCA_ERROR;
            }
            break;
        }
        case DCCA_CONTEXT_REMOVE:
        {
            ret = Remove(key, len);
            dccaStats->RemoveFromActiveSession();
            break;
        }
        case DCCA_CONTEXT_ERROR:
        {
            ret = Remove(key, len);
            ret = ITS_DIA_DCCA_ERROR;
            break;
        }
        default:
        {            
            break;
        }
    }
    
    return ret;
}
