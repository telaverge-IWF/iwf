/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: app_callbacks.cpp,v $
 * LOG: Revision 1.1.2.2  2013/02/05 04:39:59  pramana
 * LOG: Checking in changes done for Displaying the menu
 * LOG:
 * LOG: Revision 3.2.18.1  2012/09/28 08:01:15  pramana
 * LOG: Checkins for the changes done for GenBand demo
 * LOG:
 * LOG: Revision 3.2  2010/07/07 08:28:22  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/25 12:22:17  kamakshilk
 * LOG: exit changed to _exit in AppPostFunc
 * LOG:
 * LOG: Revision 1.1  2006/12/19 07:59:44  kamakshilk
 * LOG: Common files required for static setup
 * LOG:
 * LOG:
 *
 * ID: $Id: app_callbacks.cpp,v 1.1.2.2 2013/02/05 04:39:59 pramana Exp $
 ****************************************************************************/
#ident "$Id: app_callbacks.cpp,v 1.1.2.2 2013/02/05 04:39:59 pramana Exp $"

#include <iostream>
#include <its++.h>
#include <its_timers.h>
#include <engine++.h>

/* Conflict Resolution on Linux
*/

#if defined(IPPROTO_SCTP)
#undef IPPROTO_SCTP
#endif

#include <dia_trace.h>
#include <dia_config.h>
#include <dia_frame.h>

#include <dia_module.h>

#include <app.h>
#include <app_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

ITS_UINT regAppId =  0;
extern RunMode GetMode();

/*implementation: public
 ****************************************************************************
 *  Purpose: Accelero ApplicationSelector Function 
 *      Used to route the events received from the diameter stack to the 
 *      correct application worker thread based on the Application ID in 
 *      the received inbound header
 *
 *  Input Parameters:
 *      ITS_HDR* h: Inbound Header Received from the stack
 *      ITS_EVENT* ev: Inbound Event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the handle for the TaskQueue instance of the particular 
 *      application level worker or ITS_NO_SRC if there is no worker 
 *      corresponding to the Application ID received.
 *
 *  Notes:
 *      Although the entire inbound event aka message can be accessed 
 *      by an application it is *not recommended* to decode the event
 *      in this function, since this is being executed in the base diameter
 *      stack thread scope. The faster this function returns, the lesser
 *      time the base diameter stack thread is blocked
 *
 *  See Also:
 ****************************************************************************/

extern "C" ITS_USHORT
ApplicationRoutingFunction(ITS_HDR* h, ITS_EVENT* ev)
{
    APP_TRACE_DEBUG(("APP Received Event\n "));

    /* If is a application ID refers to CxDx Application, 
       return the CxDx TQ instance.
    */
    if(h->context.appId == regAppId || 
          h->context.appId == BASE_INTERFACE_APP_ID)
    {
        return APP_TQ_INST;
    }
    /* If is a application ID refers to unknown Application, 
       return ITS_NO_SRC to indicate to the Base stack that
       there is no application registered for this message. 
    */
    else
    {
        APP_TRACE_ERROR(("No Application Registered"));

        return (ITS_NO_SRC);
    }

}

void sig_handler(int sigVal)
{
    exit(0);
}

/*  implementation:public
 ****************************************************************************
 *  Purpose: Accelero PreFunc Callback Implementation
 *      This is the Main entry point to the program. All the
 *      initilizations are done in this function. Such as enabling the
 *      traces, starting the application threads, registering the application
 *      with the base diameter stack and so on.
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
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *      The following are the steps that are taken in this function
 *      1. Traces (Stack and Application) are Enabled
 *      2. A Thread is reaped from the Accelero Thread Pool.
 *         Single Thread simulates 1 Application Interface i.e.
 *         BaseProtocol, Sh, CxDx, GqGq'
 *      3. Associate a ThreadFunction to each thread and dispatch
 *         the thread.
 *      4. Repeat Steps 2 and 3, for all the application level threads
 *         namely BaseProtocol, Sh, CxDx, GqGq'
 *      5. Register the Applications with the Base Protocol Stack
 *      6. Initialize the Base Protocol Stack
 *
 *  See Also:
 ****************************************************************************/
extern "C" int
AppPreFunc()
{
    int ret;

    /* Enable Demo Application Tracing 
       There are 4 Levels of Tracing that are enabled, namely
       DEBUG, CRITICAL, ERROR, WARNING
    */
    EnableAPPTracing();

    APP_TRACE_DEBUG(("In Pre-Func"));

    /* 
     * Set the application selector callback.
     */

    ROUTE_SetApplicationSelector(ApplicationRoutingFunction);

    /*
     * Using the diameter stack HANDLE: aka DiaFrame
     * register all the applications with the diameter stack
     */
//    RegisterApplicationWithStack(BASE_INTERFACE_APP_ID);
//    RegisterApplicationWithStack(regAppId);
                                                                                
    /*
     * Now Set XML file and Initialize the Base diameter stack.
     */
    InitializeDiaStack();

    /* Create an Accelero ThreadPoolEntry Object
     *
     */
    ITS_ThreadPoolEntry ent;

    /* 
     *  Reap a thread from the Accelero Managed ThreadPool.
     */
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        /* Get the thread from the thread pool
        */
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            /* 
             * Dispatch the thread to simulate the base protocol application
             */
            ret = workerPool->DispatchOnThread(ent,  (ITS_ThreadCallFunc)AppThreadFunc, NULL);

            /* 
             * If the dispatch fails, return the thread to the thread pool
             * and throw the error.
             */
            if (ret != ITS_SUCCESS)
            {
                workerPool->ReturnToAvailThreads(ent);

                ITS_THROW_ERROR(ret);
            }
        }
        else
        {
            workerPool->ReturnToAvailThreads(ent);
        }
    }

    /*  If appMode is LOAD_TEST or runMode is INITIATOR , start the
     *  the sender thread.
     */
#ifdef SEAGULL_STYLE_OUTPUT
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            ret = workerPool->DispatchOnThread(ent,  (ITS_ThreadCallFunc)DisplayThreadFunc, NULL);

            /* 
             * If the dispatch fails, return the thread to the thread pool
             * and throw the error.
             */
            if (ret != ITS_SUCCESS)
            {
                workerPool->ReturnToAvailThreads(ent);

                ITS_THROW_ERROR(ret);
            }
        }
        else
        {
            workerPool->ReturnToAvailThreads(ent);
        }
    }
#else
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            ret = workerPool->DispatchOnThread(ent,  (ITS_ThreadCallFunc)DisplayThreadFunc2, NULL);

            /* 
             * If the dispatch fails, return the thread to the thread pool
             * and throw the error.
             */
            if (ret != ITS_SUCCESS)
            {
                workerPool->ReturnToAvailThreads(ent);

                ITS_THROW_ERROR(ret);
            }
        }
        else
        {
            workerPool->ReturnToAvailThreads(ent);
        }
    }
#endif

    runMode = GetMode();

#if 0
    if (appMode == UNIT_TEST && runMode != INITIATOR)
    {
        return ITS_SUCCESS;
    }
#endif

    if (runMode == INITIATOR)
    {
        if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
        {
            engine::Worker* work = (engine::Worker *)ent.GetThread();

            if (work)
            {
                ret = workerPool->DispatchOnThread(ent,  (ITS_ThreadCallFunc)SenderThreadFunc, NULL);

                /* 
                 * If the dispatch fails, return the thread to the thread pool
                 * and throw the error.
                 */
                if (ret != ITS_SUCCESS)
                {
                    workerPool->ReturnToAvailThreads(ent);

                    ITS_THROW_ERROR(ret);
                }
            }
            else
            {
                workerPool->ReturnToAvailThreads(ent);
            }
        }
    }

    if (runMode == RECEIVER)
    {
        if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
        {
            engine::Worker* work = (engine::Worker *)ent.GetThread();

            if (work)
            {
                ret = workerPool->DispatchOnThread(ent,  (ITS_ThreadCallFunc)ReceiverThreadFunc, NULL);

                /* 
                 * If the dispatch fails, return the thread to the thread pool
                 * and throw the error.
                 */
                if (ret != ITS_SUCCESS)
                {
                    workerPool->ReturnToAvailThreads(ent);

                    ITS_THROW_ERROR(ret);
                }
            }
            else
            {
                workerPool->ReturnToAvailThreads(ent);
            }
        }
    }

    signal(SIGINT, sig_handler);

    APP_TRACE_DEBUG(("Returning from  Pre-Func"));

    return ITS_SUCCESS;
}

/* implementation:public
 ****************************************************************************
 *  Purpose: Accelero Application Termination Function
 *      cleanup activities prior to application termination are performed here. 
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
extern "C" void 
AppPostFunc()
{
    APP_TRACE_CRITICAL(("APP Post Func Called...Exiting"));

    /* 
     * Disable Application tracing
     */
    DisableAPPTracing();

    /*
     * AppTerminate Disables Diameter Stack Tracing and
     * Terminates the diameter stack
     */
    AppTerminate();

    /* 
     * Terminate the Accelero Engine 
     */
    ITS_GlobalStop();

    _exit(0);
}

void 
AppInitialize(ITS_UINT appId)
{
    int ret;

    APP_TRACE_DEBUG(("In AppInitialize"));

    regAppId = appId;

    APP_TRACE_DEBUG(("Returning from  AppInitialize"));

    return ;
}
