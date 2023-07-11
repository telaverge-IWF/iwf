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
 * LOG: Revision 3.2  2010/07/07 08:34:13  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.5  2008/03/27 11:58:27  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.3.4.1  2007/04/16 09:29:43  nvijikumar
 * LOG: If appId 3 give event to bese menu.
 * LOG:
 * LOG: Revision 1.3  2007/01/25 12:20:55  kamakshilk
 * LOG: exit changed to _exit in AppPostFunc
 * LOG:
 * LOG: Revision 1.2  2006/10/24 14:30:16  yranade
 * LOG: No SetConfigFile needed anymore. ITS-Diameter stack takes care of it
 * LOG: automatically.
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 1.12  2006/06/02 09:20:14  yranade
 * LOG: Minor update
 * LOG:
 * LOG: Revision 1.11  2006/06/02 04:47:53  kamakshilk
 * LOG: Support for RfRo
 * LOG:
 * LOG: Revision 1.10  2006/05/24 04:57:01  nvijikumar
 * LOG: including app_defines header file.
 * LOG:
 * LOG: Revision 1.9  2006/05/04 20:47:09  yranade
 * LOG: Some cleanup.
 * LOG:
 * LOG: Revision 1.8  2006/04/28 18:23:18  yranade
 * LOG: Changes for Accelero based OD tracing.
 * LOG:
 * LOG: Revision 1.7  2006/04/27 16:06:13  yranade
 * LOG: Updates to reflect changes in Diameter tracing.
 * LOG:
 * LOG: Revision 1.6  2006/04/25 15:26:00  nvijikumar
 * LOG: Code Enhancement (Documentation)(yranade)
 * LOG:
 * LOG: Revision 1.5  2006/04/17 16:08:37  yranade
 * LOG: Load Generator Support.
 * LOG:
 * LOG: Revision 1.4  2006/03/20 06:37:26  yranade
 * LOG: Moved defines to header.
 * LOG:
 * LOG: Revision 1.3  2006/03/13 16:33:10  yranade
 * LOG: Enable DiaFrame tracing.
 * LOG:
 * LOG: Revision 1.2  2006/03/09 11:47:32  tpanda
 * LOG: Encode/Decode feature provided by wei's api replaced our encode/decode
 * LOG: function.Hence dia_codec.* files are redundant
 * LOG:
 * LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 * LOG: First Version of Demo Application.
 * LOG:
 *
 * ID: $Id: app_callbacks.cpp,v 3.2 2010/07/07 08:34:13 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app_callbacks.cpp,v 3.2 2010/07/07 08:34:13 nvijikumar Exp $"

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
#include <app_defines.h>
#include <app_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

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

    /* 
     * If application ID in the header refers to base protocol, 
     *   return the Base TQ instance.
     */
    if (h->context.appId == BASE_INTERFACE_APP_ID)
    {
        return BASE_APP_TQ_INST;
    }
    if (h->context.appId == 3)
    {
        return BASE_APP_TQ_INST;
    }
    /* If is a application ID refers to SH Application, 
       return the SH TQ instance.
    */
    else if (h->context.appId == SH_INTERFACE_APP_ID)
    {
        return SH_APP_TQ_INST;
    }
    /* If is a application ID refers to CxDx Application, 
       return the CxDx TQ instance.
    */
    else if(h->context.appId == CXDX_INTERFACE_APP_ID)
    {
        return CXDX_APP_TQ_INST;
    }
    /* If is a application ID refers to GqGq' Application, 
       return the GqGq' TQ instance.
    */
    else if(h->context.appId == GQGQ_INTERFACE_APP_ID)
    {
        return GQGQ_APP_TQ_INST;
    }
    /* 
     * If application ID in the header refers to RfRo protocol, 
     *   return the RfRo TQ instance.
     */
    if (h->context.appId == RFRO_INTERFACE_APP_ID)
    {
        return RFRO_APP_TQ_INST;
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


    /* Enable Tracing of the Diameter Stack
       There are 4 Levels of Tracing that are enabled, namely
       DEBUG, CRITICAL, ERROR, WARNING

    DiaTrace::GetDiaTrace()->Enable();
    ODiaTrace::GetODiaTrace()->Enable();
    */

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
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)BaseThreadFunc, NULL);

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

    /* 
     *  Reap a thread from the Accelero Managed ThreadPool.
     */
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            /* 
             * Dispatch the thread to simulate the Sh Interface application
             */
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)ShThreadFunc, NULL);

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

    /* 
     *  Reap a thread from the Accelero Managed ThreadPool.
     */
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            /* 
             * Dispatch the thread to simulate the CxDx Interface application
             */
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)CxDxThreadFunc, NULL);

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

    /* 
     *  Reap a thread from the Accelero Managed ThreadPool.
     */
    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)GqThreadFunc, NULL);

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
             * Dispatch the thread to simulate the RfRo protocol application
             */
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)RfRoThreadFunc, NULL);

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

    /* 
     * Access the diameter stack configuration details
     * via the DiaConfig Singelton Object Pointer
     */
    DiaConfig *cfg = DiaConfig::GetDiaConfig();

    /* 
     * Access the diameter stack HANDLE 
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        if (cfg)
        {
            /* 
             * Using the diameter stack HANDLE: aka DiaFrame
             * register all the applications with the diameter stack
             */
            diaFrame->RegisterApplication(BASE_INTERFACE_APP_ID);
            diaFrame->RegisterApplication(SH_INTERFACE_APP_ID);
            diaFrame->RegisterApplication(CXDX_INTERFACE_APP_ID);
            diaFrame->RegisterApplication(GQGQ_INTERFACE_APP_ID);
            diaFrame->RegisterApplication(RFRO_INTERFACE_APP_ID);

            /* 
             * Now Initialize the Base diameter stack.
             */
            diaFrame->Initialize();
        }
    }

    if (appMode == UNIT_TEST && runMode != INITIATOR)
    {
        return ITS_SUCCESS;
    }

    /*  If appMode is LOAD_TEST or runMode is INITIATOR , start the
     *  the sender thread.
     */

    if (workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
    {
        engine::Worker* work = (engine::Worker *)ent.GetThread();

        if (work)
        {
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)SenderThreadFunc, NULL);

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
     * Terminate the diameter stack
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        diaFrame->Terminate();
    }

    /*
     * Now Delete Diameter Stack Tracing
     */

    /* 
     * Terminate the Accelero Engine 
     */
    ITS_GlobalStop();

    _exit(0);
}

