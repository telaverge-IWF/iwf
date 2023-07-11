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
 * LOG: $Log: dcca_callbacks.cpp,v $
 * LOG: Revision 3.2  2010/07/07 08:28:22  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2007/01/25 12:28:27  kamakshilk
 * LOG: exit changed to _exit in AppPostFunc
 * LOG:
 * LOG: Revision 2.2  2006/11/24 20:13:08  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:48:57  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: dcca_callbacks.cpp,v 3.2 2010/07/07 08:28:22 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dcca_callbacks.cpp,v 3.2 2010/07/07 08:28:22 nvijikumar Exp $"

#include <app.h>
#include <dcca_defines.h>
#include <app_trace.h>
#include <app_diatrace.h>
#include <iostream>
#include <its++.h>
#include <its_timers.h>
#include <engine++.h>
#include <dia_trace.h>
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
     * If application ID in the header refers to Tx protocol, 
     *   return the Tx TQ instance.
     */
    if (h->context.appId == DCCA_INTERFACE_APP_ID)
    {
        return DCCA_APP_TQ_INST;
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
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)DccaThreadFunc, NULL);

            /* 
             * If the dispatch fails, return the thread to the thread pool
             * and throw the error.
             */
            if (ret != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("In DccaThread Func"));
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
     * Using the diameter stack HANDLE: aka DiaFrame
     * register all the applications with the diameter stack
     */
    RegisterApplicationWithStack(DCCA_INTERFACE_APP_ID);
    RegisterApplicationWithStack(BASE_INTERFACE_APP_ID);

    /* 
     * Now Set XML file and Initialize the Base diameter stack.
     */
    InitializeDiaStack();

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
            ret = workerPool->DispatchOnThread(ent, (ITS_ThreadCallFunc)DccaSendThreadFunc, NULL);

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
     * AppTermination disables Diameter Stack Tracing and
     * Terminates the diameter stack
     */
    AppTerminate();


    /* 
     * Terminate the Accelero Engine 
     */
    ITS_GlobalStop();

    _exit(0);
}

