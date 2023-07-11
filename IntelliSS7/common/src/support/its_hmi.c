/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: its_hmi.c,v $
 * LOG: Revision 9.1.134.1.20.1  2014/09/16 09:34:54  jsarvesh
 * LOG: Changes done for removing warnings
 * LOG:
 * LOG: Revision 9.1.134.1.16.1  2014/09/15 07:20:41  jsarvesh
 * LOG: Changes done for removing Warnings
 * LOG:
 * LOG: Revision 9.1.134.1  2011/04/13 07:36:19  nvijikumar
 * LOG: Merging diamter branch changes
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.40.1  2005/01/05 07:21:26  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.8  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.7  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.6  2001/05/16 01:19:15  mmiers
 * LOG: When cond_timedwait returns on timeout, the mutex *is* held.
 * LOG:
 * LOG: Revision 4.5  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
 * LOG:
 * LOG: Revision 4.4  2001/05/02 19:06:02  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.3  2001/05/02 00:01:51  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_assertion.h>
#include <its_hmi.h>
#include <its_trace.h>
#include <its_tq_trans.h>
#include <its_timers.h>

#ident "$Id: its_hmi.c,v 9.1.134.1.20.1 2014/09/16 09:34:54 jsarvesh Exp $"

/*
 * extern
 */
ITSDLLAPI CALLBACK_Manager   *HMI_Callbacks = NULL;
ITSDLLAPI CALLBACK_Manager   *Overload_Callbacks = NULL;
ITSDLLAPI CALLBACK_Manager   *HMI_HeartbeatCallbacks = NULL;
/*
 * locals
 */
static ITS_THREAD   hmiThread;
static ITS_HANDLE   hmiHandle = NULL;
static ITS_UINT     hmiCheckInterval = HMI_CHECK_INTERVAL;
static ITS_UINT     hmiTimeOutInterval = HMI_TIMEOUT_INTERVAL;
static ITS_UINT     hmiHBInterval      = HMI_HB_INTERVAL;
static ITS_UINT     hmiRetry = HMI_RETRY;
static ITS_MUTEX    hmiGate;

static ITS_UINT     rawThreadTimeout = 0;
static ITS_UINT     tqThreadTimeout = 0;

/* overload control thresholds */
ITS_INT  maxThreshold = LOAD_MAXTHRESHOLD;
ITS_INT  minThreshold = LOAD_MINTHRESHOLD;
ITS_BOOLEAN hmiEnabled = ITS_FALSE;
/*
 * Monitor list for raw threads (without transport).
 */
LIST_Manager* monList = NULL;
static ITS_MUTEX monListLock;


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Default transport timeout interval.
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
 *      timeout interval, in msecs
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
HMI_GetTimeOutInterval()
{
    return hmiTimeOutInterval;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set HMI timeout interval.
 *  
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      HMI Timeout Value.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
HMI_SetTimeOutInterval(ITS_UINT val)
{
    if (val)
    {
        hmiTimeOutInterval = val;

        rawThreadTimeout = hmiCheckInterval*hmiRetry;
        tqThreadTimeout = hmiCheckInterval*hmiRetry*1000;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get HMI Check interval.
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
 *      HMI Check Interval.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT 
HMI_GetCheckInterval()
{
    return hmiCheckInterval;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set HMI Check interval.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      HMI Check Interval.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
HMI_SetCheckInterval(ITS_UINT val)
{
    if (val)
    {
        hmiCheckInterval = val;

        rawThreadTimeout = hmiCheckInterval*hmiRetry;
        tqThreadTimeout = hmiCheckInterval*hmiRetry*1000;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set HMI Retry.
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters: 
 *      HMI Retry.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
HMI_SetRetry(ITS_UINT val)
{
    if (val)
    {
        hmiRetry = val;

        rawThreadTimeout = hmiCheckInterval*hmiRetry;
        tqThreadTimeout = hmiCheckInterval*hmiRetry*1000;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get HMI Retry.
 *  
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      HMI Retry.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
HMI_GetRetry()
{
    return hmiRetry;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Default health management action.  Resets the transport, maybe
 *      creates a new thread.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
HMI_Reset(TRANSPORT_Control *tc)
{
    ITS_TRACE_WARNING(("HMI detected update failure for transport %s : %d\n",
                       TRANSPORT_NAME(tc), TRANSPORT_INSTANCE(tc)));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Heartbeat interval.
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
 *      Heartbeat interval, in msecs
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
HMI_GetHBInterval()
{
    return hmiHBInterval;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set HMI Heartbeat interval.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      HMI Heartbeat Value.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
HMI_SetHBInterval(ITS_UINT val)
{
    if (val)
    {
        hmiHBInterval = val;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a new thread to monitor list.  
 *      
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI HMIThread_Info* 
HMI_AddToMonList(LIST_Manager** lm, char* tName,  ITS_THREAD  *tID)
{
    ITS_TRACE_DEBUG(("HMI_AddToMonList:"));
    HMIThread_Info* thInfo = (HMIThread_Info*)malloc(sizeof(HMIThread_Info));
    if (thInfo)
    {
        thInfo->tID = tID;
        thInfo->tName = tName;
        thInfo->hmiUpCount = 0;

        /* Acquire the mutex before accessing the list */
        MUTEX_AcquireMutex(&monListLock);
        if (*lm == NULL)
        {
            *lm = LIST_Create();
        }
    
        LIST_AddTail(*lm, (void*)thInfo, sizeof(HMIThread_Info));
        HMIThread_Info* retThreadInfo = (HMIThread_Info*)LIST_TAIL(*lm)->data;

        /* mutex unlock */
        MUTEX_ReleaseMutex(&monListLock);
        return retThreadInfo;
    }

    return NULL;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a thread from monitor list.
 *
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
HMI_RemoveFromMonList(LIST_Manager** lm, ITS_THREAD *tID)
{  
   LIST_Entry* thrEnt = NULL;
   ITS_TRACE_DEBUG(("HMI_RemoveFromMonList:"));
   if( *lm == NULL)
   {  
        ITS_TRACE_DEBUG((" List Manager is NULL \n"));
   }
   else
   {
       /* Lock the list */
       MUTEX_AcquireMutex(&monListLock);

       for (thrEnt = LIST_HEAD(*lm); 
            thrEnt !=NULL ; 
            thrEnt= thrEnt->next)
       {
           HMIThread_Info* thInfo = (HMIThread_Info*) thrEnt->data;
           if(thInfo->tID == tID)
           {
                /* remove thread from monitor list */
                LIST_Unlink(*lm, thrEnt);
                ITS_Free(thrEnt->data);
                ITS_Free(thrEnt);
                /* Release the List lock */
                MUTEX_ReleaseMutex(&monListLock);

                return;    
           }  
       }
       /* Release the List lock */
       MUTEX_ReleaseMutex(&monListLock);

   }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *    Reset HungCounter of a raw thread. 
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
HMI_ResetHMIUpCount(LIST_Manager** lm, ITS_THREAD *tID)
{
   LIST_Entry* thrEnt = NULL;
   ITS_TRACE_DEBUG(("HMI_ResetHungCount:"));
   if( *lm == NULL)
   {  
       ITS_TRACE_DEBUG(("List is Empty\n"));
   }
   else
   {
       for (thrEnt = LIST_HEAD(*lm); 
            thrEnt !=NULL ; 
            thrEnt= thrEnt->next)
       {
           HMIThread_Info* thInfo = (HMIThread_Info*) thrEnt->data;
           if(thInfo->tID ==tID)
           {
                /* Reset update counter  */
                thInfo->hmiUpCount = 0; 
                return;    
           }  
       }
   }    
}

ITSDLLAPI void
HMI_Disable(ITS_BOOLEAN enHMI)
{
   hmiEnabled = ITS_FALSE;
}

ITSDLLAPI void
HMI_Enable(ITS_BOOLEAN enHMI)
{
   hmiEnabled = ITS_TRUE;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      check for Overload from QCount value.
 *
 *  Input Parameters:
 *      QCount.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void CheckOverload(ITS_INT qcount)
{
   static ITS_UINT ovLoadCount;
   static ITS_UINT abatedCount;
   static ITS_BOOLEAN ovLoadF;

   if(qcount >= maxThreshold) 
   {
       ++ovLoadCount;
       abatedCount = 0;
       if((ovLoadCount >= NO_OF_SAMPLES) && !ovLoadF)
       {  
           ovLoadF = ITS_TRUE;
           ovLoadCount = 0;
           if (!CALLBACK_IsListEmpty(Overload_Callbacks))
           {
               CALLBACK_CallCallbackList(Overload_Callbacks,
                                        (ITS_POINTER)(intptr_t)ovLoadF,
                                        (ITS_POINTER)(intptr_t)ovLoadF);
           }
       }
   }
   else
   {
       ovLoadCount = 0;
       if(ovLoadF && (qcount <= minThreshold))
       {     
           ++abatedCount;
           if(abatedCount >= NO_OF_SAMPLES)
           {  
               ovLoadF = ITS_FALSE;
               if (!CALLBACK_IsListEmpty(Overload_Callbacks)) 
               {
                   CALLBACK_CallCallbackList(Overload_Callbacks,
                                       (ITS_POINTER)(intptr_t)ovLoadF,
                                       (ITS_POINTER)(intptr_t)ovLoadF);
               }
           }  
       }
   }
}
 
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle messages (timers or stop event).
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static THREAD_RET_TYPE
HMIThread(void *arg)
{
    static ITS_UINT intervalCount = 0;
    EMLIST_Manager *tQEntry = NULL;
    EMLIST_Manager *senderTq = NULL, *diaTq = NULL;

    ITS_EVENT hmiEvent;
    ITS_SERIAL timer;
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *ent;
    ITS_TIME curTick;
    ITS_INT qCount=0;
    ITS_BOOLEAN  qPriority = ITS_FALSE;
    ITS_BOOLEAN rawThread = ITS_FALSE;

    rawThreadTimeout = hmiCheckInterval*hmiRetry;
    tqThreadTimeout = hmiCheckInterval*hmiRetry*1000;

    memset(&hmiEvent, 0, sizeof(ITS_EVENT));

    timer = TIMERS_StartUTimer(HEALTH_MANAGER_INSTANCE,
                              hmiHBInterval*1000,
                              NULL, 0);

    ITS_C_ASSERT(timer != 0);

    tm = TRANSPORT_GetManager();

    TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_TRUE;

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(hmiHandle))
                                                        (hmiHandle,
                                                        &hmiEvent) ==
           ITS_SUCCESS)
    {
        switch (hmiEvent.src)
        {
        case HEALTH_MANAGER_INSTANCE:
            /* termination message */
            ITS_TRACE_DEBUG(("HMIThread: exiting ok\n"));

            TIMERS_CancelTimer(timer);

            TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_FALSE;

            THREAD_NORMAL_EXIT;
            break;

        default:

            /* Heartbeat */
            if (!CALLBACK_IsListEmpty(HMI_HeartbeatCallbacks))
            {
                ITS_BOOLEAN  hmiHB = ITS_TRUE; 
                CALLBACK_CallCallbackList(HMI_HeartbeatCallbacks, 
                                         (ITS_POINTER)&hmiHB,
                                         (ITS_POINTER)&hmiHB);
            }

            intervalCount += hmiHBInterval;

            if (hmiEnabled && (intervalCount < hmiCheckInterval*1000))
            {
                /* start another timer */
                timer = TIMERS_StartUTimer(HEALTH_MANAGER_INSTANCE,
                                      hmiHBInterval*1000,
                                      NULL, 0);

                ITS_C_ASSERT(timer != 0);
                continue;
            }

            intervalCount = 0;

            /* check transports */
            if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
            {
                ITS_TRACE_CRITICAL(("HMIThread: RWLOCK_LockShared Failed\n"));
                abort();
            }
            
            if (hmiEnabled || (tQEntry == NULL))
            {
                rawThread = ITS_FALSE;
                curTick = TIMERS_Time();
                for (ent = tm->listHead; ent != NULL;
                     ent = TRANSPORT_HMI_NEXT(ent))
                {
                    if (!tQEntry)
                    {
                        if(strcmp(TRANSPORT_NAME(ent),"ITSDiaSenderTQ") == 0)
                        {
                            qPriority = ITS_TRUE; 
                            TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)ent;
                            senderTq = TQUEUETRAN_EMLIST(tqM);
                        }
                        else if (strcmp(TRANSPORT_NAME(ent),"ITSDiaTQ") == 0)
                        {
                            TQUEUETRAN_Manager *tqM = (TQUEUETRAN_Manager *)ent;
                            diaTq = TQUEUETRAN_EMLIST(tqM);
                        }
                    }

                    if(hmiEnabled)
                    {
                        /* verify up to date */
                        if (TRANSPORT_IS_ACTIVE(ent) &&
                            (curTick - TRANSPORT_LAST_UPDATE(ent)) >
                                                          tqThreadTimeout)
                        {
                            /* (ITS_TIME)HMI_GetTimeOutInterval() */

                            if (!CALLBACK_IsListEmpty(HMI_Callbacks))
                            {
                                CALLBACK_CallCallbackList(HMI_Callbacks, (ITS_POINTER)&rawThread,
                                                         (ITS_POINTER)ent);

                            }
                            else
                            {
                                HMI_Reset(ent);
                            }
                        }
                    }
                }
            }  

            if (tQEntry)
            {
                qCount = LIST_COUNT((LIST_Manager *)(tQEntry));
            }
            else
            {
                if (qPriority == ITS_TRUE)
                {
                    tQEntry = senderTq;
                }
                else 
                {
                    tQEntry = diaTq;
                }
            }

            RWLOCK_UnlockShared(&tm->transportGate);

            /* check for overload for the QCount obtained*/
            CheckOverload(qCount);

            LIST_Entry* entRaw = NULL;
            if(monList && hmiEnabled)
            {
                rawThread = ITS_TRUE;
                for (entRaw = LIST_HEAD(monList);
                     entRaw !=NULL;
                     entRaw= entRaw->next)
                {
                    HMIThread_Info* thInfo = (HMIThread_Info*) entRaw->data;
                    thInfo->hmiUpCount += hmiCheckInterval; 
                    if (thInfo->hmiUpCount > rawThreadTimeout)
                    {
                        if (!CALLBACK_IsListEmpty(HMI_Callbacks))
                        {   
                             CALLBACK_CallCallbackList(HMI_Callbacks,
                                                  (ITS_POINTER)&rawThread,
                                                  (ITS_POINTER)thInfo);
                        }
                    }
                }      
            }

            /* start another timer */
            timer = TIMERS_StartUTimer(HEALTH_MANAGER_INSTANCE,
                                      hmiHBInterval*1000,
                                      NULL, 0);

            ITS_C_ASSERT(timer != 0);
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(hmiHandle) = ITS_FALSE;

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the HMI subsystem to a ready state.
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
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    RESFILE_Manager *globalRes = NULL;
    static char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    ITS_TRACE_DEBUG(("HMI_Initialize:\n"));

    /* get resources */
    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes)
    {
        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_INTERVAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiCheckInterval = RESFILE_ParseNum(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_TIMEOUT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiTimeOutInterval = RESFILE_ParseNum(value)*1000;
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_RETRY_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiRetry = RESFILE_ParseNum(value);
        }

        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  HMI_HB_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            hmiHBInterval = RESFILE_ParseNum(value);
        }
    }

    /* create mutex */
    if (MUTEX_CreateMutex(&hmiGate, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* create mutex */
    if (MUTEX_CreateMutex(&monListLock, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create mutex\n"));
        MUTEX_DeleteMutex(&hmiGate);

        return (ITS_EBADMUTEX);
    }

    /* create callback manager */
    if ((HMI_Callbacks = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create callback manager\n"));

        MUTEX_DeleteMutex(&hmiGate);
        MUTEX_DeleteMutex(&monListLock);
        return (ITS_ENOMEM);
    }

    /* create callback manager */
    if ((Overload_Callbacks = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create callback manager\n"));

        MUTEX_DeleteMutex(&hmiGate);
        MUTEX_DeleteMutex(&monListLock);

        return (ITS_ENOMEM);
    }

    /* create callback manager */
    if ((HMI_HeartbeatCallbacks = CALLBACK_InitManager()) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create callback manager\n"));

        MUTEX_DeleteMutex(&hmiGate);
        MUTEX_DeleteMutex(&monListLock);

        return (ITS_ENOMEM);
    }

    /* create transport */
    if ((hmiHandle = TQUEUETRAN_CreateTransport("Health Manager",
                                                HEALTH_MANAGER_INSTANCE,
                                                0)) == NULL)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create transport."));

        MUTEX_DeleteMutex(&hmiGate);
        MUTEX_DeleteMutex(&monListLock);

        CALLBACK_DestroyManager(HMI_Callbacks);
        CALLBACK_DestroyManager(Overload_Callbacks);

        return (ITS_ENOTRANSPORT);
    }


    /* create thread */
    if (THREAD_CreateThread(&hmiThread, 0,
                            HMIThread, NULL,
                            ITS_TRUE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("HMI_Initialize: Couldn't create thread.\n"));

        MUTEX_DeleteMutex(&hmiGate);
        MUTEX_DeleteMutex(&monListLock);

        CALLBACK_DestroyManager(HMI_Callbacks);
        CALLBACK_DestroyManager(Overload_Callbacks);

        TQUEUETRAN_DeleteTransport(hmiHandle);

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the HMI subystem.
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    void *status;
    ITS_EVENT stopEvent;

    ITS_TRACE_DEBUG(("HMI_Terminate:\n"));

    stopEvent.src = HEALTH_MANAGER_INSTANCE;
    stopEvent.len = 0;
    stopEvent.data = NULL;

    /* send stop message */
    TRANSPORT_PutEvent(HEALTH_MANAGER_INSTANCE, &stopEvent);

    /* delete thread */
    THREAD_WaitForThread(&hmiThread, &status);

    /* delete transport */
    TQUEUETRAN_DeleteTransport(hmiHandle);

    /* delete callback manager */
    CALLBACK_DestroyManager(HMI_Callbacks);
    CALLBACK_DestroyManager(Overload_Callbacks);
   
    /* Delete LIST_Manager */
    LIST_Delete(&monList); 

    /* delete mutex */
    MUTEX_DeleteMutex(&hmiGate);
    MUTEX_DeleteMutex(&monListLock);
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsHMI_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        HMI_CLASS_NAME,                 /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsHMI_Class = (ITS_Class)&itsHMI_ClassRec;
